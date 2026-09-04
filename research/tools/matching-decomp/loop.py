#!/usr/bin/env python3
"""loop.py -- the matching-decompilation LOOP.

The spike (docs/matching-decompilation-spike.md s4) measured that this loop is
ITERATION-bound, not tok/s-bound: an 80x faster GPU buys 4.5x, because past
~40 tok/s the cost is iterations and prefill.  Every stage here exists to
remove iterations, and three of the four stages remove them by not calling a
model at all.

    seed       candidate 0, derived MECHANICALLY from the retail encodings.
               No model.  A function that matches here costs one 26 ms compile.
    permute    when a candidate is close, mutate the C mechanically and
               compile the mutants in parallel on CPU.  No model.
    llm-step   one model call: target disassembly + current candidate + the
               oracle's FIRST MISMATCH + a matched sibling exemplar -> a
               minimal edit.  This is the only stage that costs GPU.
    run        drive the three above over one function, a shape class, or the
               whole compilable corpus, writing a JSONL ledger so throughput
               is MEASURED rather than estimated.

The oracle is `objdiff.compare` via `match.py`'s compile path -- imported
read-only; nothing in this file modifies `match.py`, `verify.py`, or the
compiler fork.

ONE INTEGRITY RULE THIS FILE ADDS
---------------------------------
`objdiff.compare` masks every relocated operand field on both sides, and
`match.py` name-checks only R_PPC_REL24 branch targets (the only relocations
resolvable from a linked DOL plus the link map).  A candidate whose match
depends on a DATA relocation -- R_PPC_ADDR16_HA/LO, R_PPC_EMB_SDA21 -- has had
that operand masked and NEVER name-checked, so it would "match" any global in
the game.  Such a verdict is recorded as MATCH_UNVERIFIED and is NEVER written
to src-match/.  See `Oracle.check`.

Usage
-----
    python loop.py shapes                       # the shape index, measured
    python loop.py seed --function zz_0206f8c_  # print candidate 0
    python loop.py run --function zz_0206f8c_
    python loop.py run --class shape-shared     # the spike's 233
    python loop.py run --all-compilable --no-llm
    python loop.py llm-step --function X --candidate c.c --recorded fixtures/
    python loop.py selftest                     # no compiler, no network
"""
from __future__ import annotations

import argparse
import hashlib
import itertools
import json
import os
import re
import struct
import subprocess
import sys
import tempfile
import time
from pathlib import Path

HERE = Path(__file__).resolve().parent
sys.path.insert(0, str(HERE))
REPO = HERE.parents[2]

from dolsym import load, function_bytes                      # noqa: E402
from ppcdis import disasm, render                            # noqa: E402
from objdiff import Elf32BE, compare, render_diff            # noqa: E402
import match as MATCH                                        # noqa: E402

LEDGER_DEFAULT = REPO / "research" / "decomp" / "data" / "matching-loop-ledger.jsonl"
RESULTS_DEFAULT = REPO / "research" / "decomp" / "data" / "matching-loop-results.json"
SRC_MATCH = REPO / "src-match"

# Relocation types whose operand the oracle masks but CANNOT name-check from a
# linked DOL (there is no data symbol table).  A match that leans on one of
# these is vacuous -- it would accept any global.
REL24 = 10          # R_PPC_REL24, the only one match.py resolves through the map
BUILD = "2.7"


# ---------------------------------------------------------------------------
# toolchain
# ---------------------------------------------------------------------------

def find_compiler():
    """mwcc-rs, wherever it was built.  `.tools/` is gitignored and the build
    may live in the worktree that produced it, so search rather than assume."""
    cands = [os.environ.get("MWCC_RS"),
             str(REPO / ".tools" / "mwcc-rs" / "target" / "release" / "mwcc.exe"),
             "D:/GotYaForce/.tools/mwcc-rs/target/release/mwcc.exe"]
    for p in cands:
        if p and Path(p).exists():
            return Path(p)
    wt = Path("D:/GotYaForce/.claude/worktrees")
    if wt.exists():
        for d in sorted(wt.iterdir()):
            p = d / ".tools" / "mwcc-rs" / "target" / "release" / "mwcc.exe"
            if p.exists():
                return p
    return None


# ---------------------------------------------------------------------------
# instruction decode -- only what the seeder needs, and nothing inferred
# ---------------------------------------------------------------------------

def _s16(v):
    return v - 0x10000 if v & 0x8000 else v


def decode(w):
    """A minimal structured decode.  Returns None for anything the seeder
    does not model, which is how an unsupported shape gets rejected."""
    op = w >> 26
    rd = (w >> 21) & 31
    ra = (w >> 16) & 31
    rb = (w >> 11) & 31
    d = _s16(w & 0xFFFF)
    u = w & 0xFFFF
    xo = (w >> 1) & 0x3FF
    if w == 0x4E800020:
        return {"mn": "blr"}
    if w == 0x4D820020:
        return {"mn": "beqlr"}
    if w == 0x4C820020:
        return {"mn": "bnelr"}
    if w == 0x7C0802A6:
        return {"mn": "mflr", "rd": rd}
    if w == 0x7C0803A6:
        return {"mn": "mtlr", "rd": rd}
    LOADS = {32: ("lwz", 4, True), 34: ("lbz", 1, False), 40: ("lhz", 2, False),
             42: ("lha", 2, True), 48: ("lfs", 4, None)}
    STORES = {36: ("stw", 4), 38: ("stb", 1), 44: ("sth", 2), 52: ("stfs", 4)}
    if op in LOADS:
        mn, wid, sgn = LOADS[op]
        return {"mn": mn, "rd": rd, "ra": ra, "d": d, "width": wid, "signed": sgn}
    if op in STORES:
        mn, wid = STORES[op]
        return {"mn": mn, "rs": rd, "ra": ra, "d": d, "width": wid}
    if op == 37:
        return {"mn": "stwu", "rs": rd, "ra": ra, "d": d}
    if op == 14:
        return {"mn": "li" if ra == 0 else "addi", "rd": rd, "ra": ra, "d": d}
    if op == 15:
        return {"mn": "lis" if ra == 0 else "addis", "rd": rd, "ra": ra, "d": d}
    if op == 7:
        return {"mn": "mulli", "rd": rd, "ra": ra, "d": d}
    if op == 10:
        return {"mn": "cmplwi", "ra": ra, "u": u, "crf": rd >> 2}
    if op == 11:
        return {"mn": "cmpwi", "ra": ra, "d": d, "crf": rd >> 2}
    if op == 18:
        li = w & 0x03FFFFFC
        if li & 0x02000000:
            li -= 0x04000000
        return {"mn": "bl" if (w & 1) else "b", "li": li, "aa": bool(w & 2)}
    if op == 31:
        if xo == 954:
            return {"mn": "extsb", "rd": ra, "rs": rd}     # X-form: rA <- rS
        if xo == 922:
            return {"mn": "extsh", "rd": ra, "rs": rd}
        if xo == 444:                                      # or rA, rS, rB
            return {"mn": "mr" if rd == rb else "or", "rd": ra, "rs": rd, "rb": rb}
    return None


def shape_of(blob, addr):
    return tuple(t.split()[0] for _a, _w, t in disasm(blob, addr))


# ---------------------------------------------------------------------------
# the oracle, held open so the DOL is read once
# ---------------------------------------------------------------------------

class Oracle(object):
    def __init__(self, repo="D:/GotYaForce", build=BUILD, compiler=None):
        self.dol, self.smap = load(repo=repo)
        self.compiler = Path(compiler) if compiler else find_compiler()
        self.build = build
        self.cflags = list(MATCH.DEFAULT_CFLAGS_RS)
        self.compiles = 0
        self.compile_s = 0.0
        self._work = Path(tempfile.mkdtemp(prefix="mdloop_"))

    def available(self):
        return self.compiler is not None

    def target(self, name):
        rec, retail = function_bytes(self.dol, self.smap, name)
        return rec, retail

    def check(self, rec, retail, csrc, sym="f", workdir=None, want_diff=False):
        """Compile one candidate and run the oracle.  Returns a verdict dict.

        MATCH_UNVERIFIED is returned instead of MATCH when the match leans on a
        relocation the harness cannot name-check (see module docstring).
        """
        wd = Path(workdir or self._work)
        wd.mkdir(parents=True, exist_ok=True)
        src = wd / "cand.c"
        src.write_text(csrc)
        t0 = time.time()
        obj, log, cmd = MATCH.compile_candidate(
            src.resolve(), self.compiler, self.cflags, [], str(wd),
            kind="mwcc-rs", build=self.build)
        self.compile_s += time.time() - t0
        self.compiles += 1
        if obj is None:
            return {"verdict": "BUILD_FAILED", "match_pct": 0.0,
                    "compiler_log": log[-1200:], "first_diff": None}

        e = Elf32BE(obj.read_bytes())
        cand = e.data(e.section(".text"))
        relocs = e.relocs_for(".text")
        for sy in e.symbols():
            if sy["name"] == sym and sy["size"]:
                cand = cand[sy["value"]:sy["value"] + sy["size"]]
                relocs = [(o - sy["value"], t, n, ad) for o, t, n, ad in relocs
                          if sy["value"] <= o < sy["value"] + sy["size"]]
                break
        exp = MATCH.expected_symbols(self.smap, retail, rec["addr"])
        v = compare(retail, cand, relocs, rec["addr"], expected_syms=exp)

        unchecked = [{"offset": o, "type": t, "symbol": n}
                     for o, t, n, _a in relocs if o not in exp]
        v["unchecked_relocs"] = unchecked
        if v["verdict"] == "MATCH" and unchecked:
            v["verdict"] = "MATCH_UNVERIFIED"
            v["unverified_reason"] = (
                "the candidate carries %d relocation(s) at offsets the harness "
                "cannot resolve through the link map; their operands were "
                "masked and never name-checked, so this verdict would accept "
                "any target" % len(unchecked))
        if want_diff:
            v["diff_text"] = render_diff(v, retail, cand, rec["addr"])
        v["compiler_log"] = log[-1200:]
        v["mismatch_class"] = _codegen_class(retail, cand, relocs)
        return v


# ---------------------------------------------------------------------------
# the seeder: candidate 0 without a model
# ---------------------------------------------------------------------------

CTYPE = {(1, True): "char", (1, False): "unsigned char",
         (2, True): "short", (2, False): "unsigned short",
         (4, True): "int", (4, False): "unsigned int"}


class SeedFail(Exception):
    pass


def _base_fail(what, ra):
    """Name the refusal precisely.  r2/r13 are the small data areas, and a
    candidate that reached those bytes would carry an R_PPC_EMB_SDA21 whose
    operand the oracle MASKS and cannot name-check -- so such a "match" would
    accept any global in the game.  Refusing here is the honest outcome, not a
    gap to be closed by trying harder."""
    if ra == 2:
        return "%s through r2 (sdata2): would need an unverifiable data relocation" % what
    if ra == 13:
        return "%s through r13 (sdata): would need an unverifiable data relocation" % what
    if ra == 0:
        return "%s through r0/absolute address" % what
    return "%s through a non-argument base register r%d" % (what, ra)


class Expr(object):
    """CONST k | ARG i | FIELD(arg, off, width, signed)"""
    def __init__(self, kind, **kw):
        self.kind = kind
        self.__dict__.update(kw)

    def c(self, spec):
        if self.kind == "const":
            return _lit(self.k)
        if self.kind == "arg":
            return "p%d" % self.i
        if self.kind == "field":
            return "p%d->%s" % (self.i, _fname(self.off))
        raise SeedFail("unrenderable expr")


def _lit(k):
    if 0 <= k < 10:
        return str(k)
    if k < 0:
        return str(k)
    return "0x%x" % k


def _fname(off):
    return "field_%x" % off


def _struct(sname, fields, spec):
    """fields: {off: (width, signed)} -> a C struct with exact offsets."""
    lines = ["typedef struct %s {" % sname]
    cur = 0
    for off in sorted(fields):
        wid, sgn = fields[off]
        if off % wid:
            raise SeedFail("field at 0x%x is not %d-aligned" % (off, wid))
        if off < cur:
            raise SeedFail("overlapping fields")
        if off > cur:
            lines.append("    char pad_%x[0x%x];" % (cur, off - cur))
        ty = spec.get("ftype", {}).get(off) or CTYPE[(wid, sgn)]
        lines.append("    %-14s %s;" % (ty, _fname(off)))
        cur = off + wid
    lines.append("} %s;" % sname)
    return "\n".join(lines)


def seed_leaf(rec, retail, smap, spec=None):
    """Synthesise C for a straight-line leaf from the retail encodings alone.

    Handles: loads, stores, immediates, register moves, sign extension, and a
    single leading null guard compiled to `beqlr`.  Anything else raises
    SeedFail, which is how an out-of-envelope function is refused rather than
    guessed at.
    """
    spec = spec or {}
    ins = [decode(w) for _a, w, _t in disasm(retail, rec["addr"])]
    if any(i is None for i in ins):
        raise SeedFail("undecoded instruction")
    if not ins or ins[-1]["mn"] != "blr":
        raise SeedFail("does not end in blr")
    body = ins[:-1]

    guard = None
    if len(body) >= 2 and body[0]["mn"] in ("cmplwi", "cmpwi") \
            and body[1]["mn"] in ("beqlr", "bnelr"):
        if body[0].get("u", body[0].get("d")) != 0:
            raise SeedFail("guard compares against a non-zero constant")
        guard = (body[0]["ra"], body[0]["mn"], body[1]["mn"])
        body = body[2:]

    regs = {}
    for r in range(3, 11):
        regs[r] = Expr("arg", i=r - 3)
    fields = {}          # arg index -> {off: (width, signed)}
    stmts = []
    used_args = set()
    ptr_args = set()

    def note(argi, off, wid, sgn):
        fields.setdefault(argi, {})
        prev = fields[argi].get(off)
        if prev and prev != (wid, sgn):
            if prev[0] != wid:
                raise SeedFail("field 0x%x accessed at two widths" % off)
            sgn = prev[1] or sgn
        fields[argi][off] = (wid, sgn)

    for k, i in enumerate(body):
        mn = i["mn"]
        if mn == "li":
            regs[i["rd"]] = Expr("const", k=i["d"])
        elif mn == "mr":
            regs[i["rd"]] = regs.get(i["rs"]) or Expr("arg", i=i["rs"] - 3)
        elif mn in ("lwz", "lbz", "lhz", "lha"):
            base = regs.get(i["ra"])
            if base is None or base.kind != "arg":
                raise SeedFail(_base_fail("load", i["ra"]))
            sgn = i["signed"]
            nxt = body[k + 1] if k + 1 < len(body) else None
            if i["width"] == 1:
                sgn = bool(nxt and nxt["mn"] == "extsb" and nxt["rs"] == i["rd"])
            used_args.add(base.i)
            ptr_args.add(base.i)
            note(base.i, i["d"], i["width"], sgn)
            regs[i["rd"]] = Expr("field", i=base.i, off=i["d"],
                                 width=i["width"], signed=sgn)
        elif mn in ("extsb", "extsh"):
            src = regs.get(i["rs"])
            if src is None or src.kind != "field":
                raise SeedFail("sign extension of a non-field")
            regs[i["rd"]] = src
        elif mn in ("stw", "stb", "sth"):
            base = regs.get(i["ra"])
            if base is None or base.kind != "arg":
                raise SeedFail(_base_fail("store", i["ra"]))
            val = regs.get(i["rs"])
            if val is None:
                raise SeedFail("store of an undefined register")
            used_args.add(base.i)
            ptr_args.add(base.i)
            if val.kind == "arg":
                used_args.add(val.i)
            if val.kind == "field":
                used_args.add(val.i)
            sgn = val.signed if val.kind == "field" and val.width == i["width"] \
                else True
            note(base.i, i["d"], i["width"], sgn)
            stmts.append("p%d->%s = %s;" % (base.i, _fname(i["d"]), val.c(spec)))
        else:
            raise SeedFail("unmodelled instruction: %s" % mn)

    if guard:
        gi = guard[0] - 3
        if gi < 0 or gi > 7:
            raise SeedFail("guard on a non-argument register")
        used_args.add(gi)
        ptr_args.add(gi)

    ret = regs.get(3)
    returns = ret is not None and ret.kind != "arg"
    if returns:
        if ret.kind == "field":
            used_args.add(ret.i)
        if not stmts and not returns:
            raise SeedFail("no effect")
    if not stmts and not returns and not guard:
        if body:
            raise SeedFail("no effect")

    nargs = (max(used_args) + 1) if used_args else 0
    if nargs > 8:
        raise SeedFail("more than eight arguments")

    out = []
    for a in sorted(ptr_args):
        out.append(_struct("S%d" % a, fields.get(a, {}), spec))
        out.append("")
    params = []
    for a in range(nargs):
        if a in ptr_args:
            params.append("S%d *p%d" % (a, a))
        else:
            params.append("%s p%d" % (spec.get("argtype", "int"), a))
    rt = "void"
    if returns:
        rt = spec.get("rettype") or (
            "int" if ret.kind == "const" or ret.width <= 4 else "int")
    out.append("%s f(%s)" % (rt, ", ".join(params) if params else "void"))
    out.append("{")
    if guard:
        style = spec.get("guard", "eq0")
        p = "p%d" % (guard[0] - 3)
        cond = {"eq0": "%s == 0" % p, "not": "!%s" % p,
                "null": "%s == (void *)0" % p}[style]
        if guard[2] == "bnelr":
            cond = {"eq0": "%s != 0" % p, "not": "%s" % p,
                    "null": "%s != (void *)0" % p}[style]
        out.append("    if (%s)" % cond)
        out.append("        return;")
    for s in stmts:
        out.append("    " + s)
    if returns:
        out.append("    return %s;" % ret.c(spec))
    out.append("}")
    return "\n".join(out) + "\n"


def _c_ident(name):
    return bool(re.match(r"^[A-Za-z_][A-Za-z0-9_]*$", name))


def seed_wrapper(rec, retail, smap, spec=None):
    """Synthesise C for the Metrowerks non-leaf frame with exactly one call.

    The 8-instruction form `stwu mflr stw bl lwz mtlr addi blr` is the single
    largest short shape in the link map (115 functions) and needs nothing but
    the callee's name, which the map supplies.  Argument setup between `mflr`
    and `bl` is modelled for `li` and `mr` only; anything else is refused.
    """
    spec = spec or {}
    ins = [decode(w) for _a, w, _t in disasm(retail, rec["addr"])]
    if any(i is None for i in ins):
        raise SeedFail("undecoded instruction")
    if len(ins) < 8 or ins[0]["mn"] != "stwu" or ins[1]["mn"] != "mflr":
        raise SeedFail("not a Metrowerks non-leaf prologue")
    if ins[-1]["mn"] != "blr" or ins[-2]["mn"] != "addi" \
            or ins[-3]["mn"] != "mtlr" or ins[-4]["mn"] != "lwz":
        raise SeedFail("not a Metrowerks non-leaf epilogue")
    frame = -ins[0]["d"]
    if ins[-2]["d"] != frame:
        raise SeedFail("prologue/epilogue frame size disagree")
    mid = ins[2:-4]
    calls = [i for i in mid if i["mn"] == "bl"]
    if len(calls) != 1:
        raise SeedFail("%d calls; the wrapper seed models exactly one"
                       % len(calls))
    lr_saves = [i for i in mid if i["mn"] == "stw" and i.get("ra") == 1]
    if len(lr_saves) != 1:
        raise SeedFail("no single LR spill")
    tgt = rec["addr"] + 4 * (2 + mid.index(calls[0])) + calls[0]["li"]
    hit = smap.lookup(tgt)
    if hit is None:
        raise SeedFail("callee 0x%08x is not in the link map" % tgt)
    callee = hit["name"]
    if not _c_ident(callee):
        raise SeedFail("callee name %r is not a C identifier" % callee)

    setup = [i for i in mid if i is not calls[0] and i not in lr_saves]
    args = {}
    for i in setup:
        if i["mn"] == "li" and 3 <= i["rd"] <= 10:
            args[i["rd"]] = ("const", i["d"])
        elif i["mn"] == "mr" and 3 <= i["rd"] <= 10 and 3 <= i["rs"] <= 10:
            args[i["rd"]] = ("arg", i["rs"] - 3)
        else:
            raise SeedFail("unmodelled argument setup: %s" % i["mn"])

    # Registers the wrapper does not touch pass straight through, so the
    # callee's arity is only knowable up to the highest register set here.
    nset = max(args) - 2 if args else 0
    passthrough = sorted(set(range(3, 3 + nset)) - set(args))
    nparams = len(passthrough) + sum(1 for v in args.values() if v[0] == "arg")
    order = sorted(set(list(args) + passthrough))

    pmap = {}
    for r in passthrough:
        pmap[r] = "p%d" % (r - 3)
    actual = []
    for r in order:
        if r in args:
            kind, v = args[r]
            actual.append(_lit(v) if kind == "const" else "p%d" % v)
        else:
            actual.append(pmap[r])
    declared = sorted({int(a[1:]) for a in actual if a.startswith("p")}
                      | set(range(0, 0)))
    nd = (max(declared) + 1) if declared else 0
    params = ", ".join("int p%d" % i for i in range(nd)) or "void"
    proto = ", ".join("int" for _ in actual) or "void"
    lines = ["extern void %s(%s);" % (callee, proto), "",
             "void f(%s)" % params, "{",
             "    %s(%s);" % (callee, ", ".join(actual)), "}"]
    if frame != 0x10:
        raise SeedFail("frame size 0x%x; mwcc emits 0x10 for this shape" % frame)
    return "\n".join(lines) + "\n"


def seed_empty(rec, retail, smap, spec=None):
    ins = [decode(w) for _a, w, _t in disasm(retail, rec["addr"])]
    if len(ins) != 1 or ins[0] is None or ins[0]["mn"] != "blr":
        raise SeedFail("not a bare blr")
    return "void f(void)\n{\n}\n"


SEEDERS = [("empty", seed_empty), ("wrapper", seed_wrapper), ("leaf", seed_leaf)]


def seed(rec, retail, smap, spec=None):
    """Candidate 0.  Returns (source, seeder_name).  Raises SeedFail.

    The refusal carries `reasons` per seeder and a `primary` -- the reason
    from the seeder that SHOULD have applied, chosen by the function's own
    prologue -- because "empty: not a bare blr" tells a reader nothing about
    why an 8-instruction wrapper was refused.
    """
    why = {}
    for nm, fn in SEEDERS:
        try:
            return fn(rec, retail, smap, spec), nm
        except SeedFail as ex:
            why[nm] = str(ex)
    first = decode(struct.unpack(">I", retail[:4])[0]) if len(retail) >= 4 else None
    primary = why.get("wrapper" if (first and first["mn"] == "stwu")
                      else "leaf", "")
    e = SeedFail(primary or "; ".join("%s: %s" % kv for kv in why.items()))
    e.reasons = why
    e.primary = primary
    raise e


# ---------------------------------------------------------------------------
# the permuter: the last mile without a model
# ---------------------------------------------------------------------------

# The classic decomp-permuter move set, restricted to edits that are legal on
# any C this loop produces.  Applied mechanically, compiled in parallel, and
# diffed -- so the last few instructions cost CPU, not GPU.
SPEC_SPACE = {
    "rettype": [None, "unsigned int", "short", "unsigned short",
                "char", "unsigned char", "long", "unsigned long"],
    "argtype": ["int", "unsigned int", "long", "void *"],
    "guard": ["eq0", "not", "null"],
}

TYPE_FLIPS = [
    ("int", "unsigned int"), ("int", "long"), ("int", "short"),
    ("unsigned int", "int"), ("unsigned int", "unsigned long"),
    ("short", "int"), ("short", "unsigned short"),
    ("char", "unsigned char"), ("char", "int"),
    ("unsigned char", "char"), ("unsigned short", "short"),
]

_DECL = re.compile(r"^(\s*)(unsigned char|unsigned short|unsigned int|"
                   r"unsigned long|char|short|int|long)(\s+\w+;)$", re.M)
_STMT = re.compile(r"^(    p\d+->\w+ = [^;]+;)$", re.M)


def spec_variants(limit=64):
    """Enumerate template respellings.  Bounded: this runs per function."""
    keys = list(SPEC_SPACE)
    out = []
    for combo in itertools.product(*[SPEC_SPACE[k] for k in keys]):
        s = dict(zip(keys, combo))
        if s["rettype"] is None:
            s.pop("rettype")
        out.append(s)
        if len(out) >= limit:
            break
    return out


def text_mutations(src, limit=200):
    """Mechanical C mutations that do not depend on how the C was produced --
    so this stage also closes out an LLM's near-miss."""
    out = []

    # 1. declaration type flips, one declaration at a time
    for m in _DECL.finditer(src):
        for a, b in TYPE_FLIPS:
            if m.group(2) != a:
                continue
            out.append(src[:m.start()] + m.group(1) + b + m.group(3)
                       + src[m.end():])

    # 2. return-type flips
    for a, b in TYPE_FLIPS:
        pat = re.compile(r"^%s f\(" % re.escape(a), re.M)
        if pat.search(src):
            out.append(pat.sub("%s f(" % b, src, count=1))

    # 3. adjacent independent statement reorder
    stmts = list(_STMT.finditer(src))
    for i in range(len(stmts) - 1):
        a, b = stmts[i], stmts[i + 1]
        if src[a.end():b.start()].strip():
            continue
        out.append(src[:a.start()] + b.group(1) + src[a.end():b.start()]
                   + a.group(1) + src[b.end():])

    # 4. ++i / i++
    for m in re.finditer(r"\b(\w+)\+\+", src):
        out.append(src[:m.start()] + "++" + m.group(1) + src[m.end():])
    for m in re.finditer(r"\+\+(\w+)", src):
        out.append(src[:m.start()] + m.group(1) + "++" + src[m.end():])

    # 5. if/else inversion on a zero test
    for a, b in (("== 0", "!= 0"), ("!= 0", "== 0")):
        if a in src:
            out.append(src.replace(a, b, 1))

    # 6. while <-> for
    m = re.search(r"\bwhile \(([^)]*)\)", src)
    if m:
        out.append(src[:m.start()] + "for (; %s; )" % m.group(1) + src[m.end():])
    m = re.search(r"\bfor \(; ([^;]*); \)", src)
    if m:
        out.append(src[:m.start()] + "while (%s)" % m.group(1) + src[m.end():])

    # 7. temp-variable hoist on the return expression
    m = re.search(r"^    return (p\d+->\w+);$", src, re.M)
    if m:
        out.append(src[:m.start()]
                   + "    int tmp = %s;\n    return tmp;" % m.group(1)
                   + src[m.end():])

    seen, uniq = set(), []
    for s in out:
        if s != src and s not in seen:
            seen.add(s)
            uniq.append(s)
        if len(uniq) >= limit:
            break
    return uniq


def permute(oracle, rec, retail, base_src, seeder=None, threshold=0.0,
            workers=8, budget=400):
    """Try mechanical mutants until one MATCHes.  Returns (src, verdict, n)."""
    try:
        from concurrent.futures import ThreadPoolExecutor
    except ImportError:
        ThreadPoolExecutor = None

    cands = []
    if seeder in ("leaf",):
        for sp in spec_variants():
            try:
                cands.append(seed_leaf(rec, retail, oracle.smap, sp))
            except SeedFail:
                pass
    cands += text_mutations(base_src)
    # a mutant of a spec variant closes cases a single move cannot
    for c in list(cands[:24]):
        cands += text_mutations(c, limit=12)

    seen, uniq = set([base_src]), []
    for c in cands:
        if c not in seen:
            seen.add(c)
            uniq.append(c)
    uniq = uniq[:budget]
    if not uniq:
        return None, None, 0

    def one(idx_src):
        # A distinct scratch directory per mutant: `cand.c` and `cand.o` are
        # fixed names, so sharing one would let two workers clobber each other.
        i, s = idx_src
        wd = oracle._work / ("perm%05d" % i)
        return s, oracle.check(rec, retail, s, workdir=wd)

    steps = 0
    if ThreadPoolExecutor is not None and workers > 1:
        with ThreadPoolExecutor(max_workers=workers) as ex:
            for s, v in ex.map(one, enumerate(uniq)):
                steps += 1
                if v["verdict"] == "MATCH":
                    return s, v, steps
    else:
        for i, s in enumerate(uniq):
            steps += 1
            s, v = one((i, s))
            if v["verdict"] == "MATCH":
                return s, v, steps
    return None, None, steps


# ---------------------------------------------------------------------------
# the model step -- the only stage that costs GPU
# ---------------------------------------------------------------------------

SYSTEM_PROMPT = (
    "You are a matching-decompilation assistant for a 2003 GameCube title "
    "compiled with Metrowerks CodeWarrior (GC/2.7, -proc gekko -fp hardware "
    "-O4,p). You are given a retail function's authoritative disassembly, a "
    "candidate C source that does not yet compile to those exact bytes, and "
    "the FIRST instruction where the compiled candidate differs. Reply with "
    "the COMPLETE corrected C function and nothing else, inside one ```c "
    "fence. Cite the line number of every line you change as a // comment on "
    "that line. Do not add commentary outside the fence."
)

# The plan-derive profile, not the compile-fix profile.  Measured on this rig
# 2026-08-29 (src/port_plan_derive.py:828): the compile-fix profile's
# presence_penalty=1.5 punishes every structural token that MUST repeat, and
# the model stops mid-output with finish_reason="stop".  Structured extraction
# wants no presence penalty and a low temperature.
SAMPLING = {"temperature": 0.2, "top_p": 0.9, "top_k": 20,
            "presence_penalty": 0.0}
MAX_TOKENS = 1536


def build_prompt(rec, retail, candidate, verdict, exemplar=None, context=None):
    """The diff, not the whole world.  Everything here is either retail
    ground truth or the oracle's own output; nothing is inferred, and Ghidra's
    C is deliberately absent (spike doc s4.1)."""
    p = []
    p.append("TARGET %s @ 0x%08x, %d instructions"
             % (rec["name"], rec["addr"], rec["size"] // 4))
    p.append("")
    p.append("RETAIL DISASSEMBLY (authoritative):")
    p.append(render(retail, rec["addr"], "  "))
    if context:
        p.append("")
        p.append(context)
    p.append("")
    if not candidate.strip():
        p.append("THERE IS NO CANDIDATE YET. Write the first one.")
        if verdict.get("seed_fail"):
            p.append("The mechanical seeder refused this function: %s"
                     % verdict["seed_fail"])
    else:
        p.append("CURRENT CANDIDATE (line-numbered; cite these numbers):")
        for i, line in enumerate(candidate.splitlines(), 1):
            p.append("%3d| %s" % (i, line))
    p.append("")
    if verdict.get("verdict") == "NO_CANDIDATE":
        pass
    elif verdict.get("verdict") == "BUILD_FAILED":
        p.append("IT DOES NOT COMPILE. The compiler said:")
        p.append(verdict.get("compiler_log", "")[-800:])
    else:
        p.append("IT COMPILES BUT DOES NOT MATCH: %.2f%% of instructions agree."
                 % verdict.get("match_pct", 0.0))
        fd = verdict.get("first_diff")
        if fd:
            p.append("FIRST MISMATCH at %s:" % fd["addr"])
            p.append("  retail   : %s" % fd["retail"])
            p.append("  candidate: %s" % fd["cand"])
        if verdict.get("diff_text"):
            p.append("")
            p.append("SIDE BY SIDE (retail | candidate):")
            p.append(verdict["diff_text"])
    if exemplar:
        p.append("")
        p.append("A FUNCTION OF THE SAME SHAPE THAT ALREADY MATCHES "
                 "BYTE-IDENTICALLY -- use its idiom:")
        p.append(exemplar)
    p.append("")
    p.append("Reply with the complete corrected C function in one ```c fence.")
    return "\n".join(p)


_FENCE = re.compile(r"```(?:c|C)?\s*\n(.*?)```", re.S)


def extract_c(reply):
    """Structured output: reject anything that is not a complete function."""
    m = _FENCE.search(reply or "")
    body = m.group(1) if m else (reply or "")
    body = re.sub(r"//.*$", "", body, flags=re.M)
    if not re.search(r"\b\w[\w \*]*\bf\s*\(", body):
        raise ValueError("reply contains no function named f")
    if body.count("{") != body.count("}") or body.count("{") == 0:
        raise ValueError("reply is not a complete function (brace mismatch)")
    return body.strip() + "\n"


class ModelClient(object):
    """Wraps the driver's OpenAI-compatible client.  `recorded` replays fixture
    responses so every path here is testable with the GPU leased away."""

    def __init__(self, recorded=None, oghidra=None):
        self.recorded = Path(recorded) if recorded else None
        self.calls = 0
        self.prompt_chars = 0
        self.reply_chars = 0
        self.seconds = 0.0
        self._client = None
        self._oghidra = Path(oghidra or "D:/GotYaForce/research/tools/OGhidra")

    def _live(self):
        if self._client is not None:
            return self._client
        sys.path.insert(0, str(self._oghidra / "src"))
        sys.path.insert(0, str(self._oghidra))
        from custom_api_client import CustomAPIClient      # read-only import
        env = {}
        for line in (self._oghidra / ".env").read_text().splitlines():
            if "=" in line and not line.strip().startswith("#"):
                k, v = line.split("=", 1)
                env[k.strip()] = v.strip()

        class _Cfg(object):
            api_url = env.get("CUSTOM_API_URL", "").rsplit("/chat/completions", 1)[0]
            api_key = env.get("CUSTOM_API_KEY", "")
            model = env.get("CUSTOM_API_MODEL", "")
            timeout = 900
            temperature = SAMPLING["temperature"]
            max_tokens = MAX_TOKENS
        self._client = CustomAPIClient(_Cfg())
        return self._client

    def ask(self, prompt):
        self.calls += 1
        self.prompt_chars += len(prompt)
        t0 = time.time()
        if self.recorded is not None:
            h = hashlib.sha256(prompt.encode("utf-8")).hexdigest()[:16]
            f = self.recorded / ("%s.json" % h)
            if not f.exists():
                cands = sorted(self.recorded.glob("*.json"))
                if not cands:
                    raise RuntimeError("no recorded response in %s" % self.recorded)
                f = cands[self.calls % len(cands) - 1]
            reply = json.loads(f.read_text())["response"]
        else:
            reply = self._live().generate(
                prompt=prompt,
                system_prompt=SYSTEM_PROMPT + " /no_think",
                max_tokens=MAX_TOKENS,
                chat_template_kwargs={"enable_thinking": False},
                **SAMPLING)
        self.seconds += time.time() - t0
        self.reply_chars += len(reply or "")
        return reply

    def stats(self):
        # The OpenAI-compatible reply this client returns is a bare string, so
        # token counts are ESTIMATED at 4 chars/token and labelled as such.
        return {"model_calls": self.calls,
                "prompt_tokens_est": self.prompt_chars // 4,
                "reply_tokens_est": self.reply_chars // 4,
                "model_seconds": round(self.seconds, 2)}


# ---------------------------------------------------------------------------
# exemplars: the matched sibling whose shape this target shares
# ---------------------------------------------------------------------------

def load_exemplars(oracle):
    reg = json.loads((SRC_MATCH / "matched.json").read_text())
    out = {}
    for e in reg["functions"]:
        rec, retail = oracle.target(e["name"])
        if rec is None:
            continue
        sh = shape_of(retail, rec["addr"])
        src = (SRC_MATCH / e["src"]).read_text()
        out.setdefault(sh, (e["name"], src))
    return out


# ---------------------------------------------------------------------------
# ledger
# ---------------------------------------------------------------------------

class Ledger(object):
    def __init__(self, path):
        self.path = Path(path)
        self.path.parent.mkdir(parents=True, exist_ok=True)
        self.rows = []

    def write(self, row):
        self.rows.append(row)
        with self.path.open("a") as f:
            f.write(json.dumps(row, sort_keys=True) + "\n")


# ---------------------------------------------------------------------------
# recording a match
# ---------------------------------------------------------------------------

def _safe(name):
    return re.sub(r"[^A-Za-z0-9_.-]", "_", name)


def record_match(rec, retail, src, meta):
    """Write src-match/<name>.c with a provenance header and register it.

    A non-match is never written here under any name.  MATCH_UNVERIFIED is a
    non-match for this purpose.
    """
    reg_path = SRC_MATCH / "matched.json"
    reg = json.loads(reg_path.read_text())
    names = {e["name"] for e in reg["functions"]}
    if rec["name"] in names:
        return None
    # Keep the SDK/MetroTRK half of the corpus separate from game code: those
    # are the 1,065 functions the spike's s5.3 says should be OBTAINED from a
    # licensed decomp, not derived, and a reader must be able to tell at a
    # glance which directory a file is in.
    sdk = rec["name"].startswith("gnt4-") or rec["name"].startswith("TRK_") \
        or rec["name"].startswith("__TRK")
    rel = "%s/%s.c" % ("sdk" if sdk else "game", _safe(rec["name"]))
    body = src if src.endswith("\n") else src + "\n"
    sha = hashlib.sha256(body.encode("utf-8")).hexdigest()
    head = ["/* MATCHED  %s @ 0x%08x  (%d instructions)"
            % (rec["name"], rec["addr"], rec["size"] // 4), " *"]
    for line in render(retail, rec["addr"], "").splitlines():
        head.append(" *   " + line)
    head += [
        " *",
        " * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.",
        " *   candidate source : %s" % meta["seed"],
        " *   iterations       : %d" % meta["iterations"],
        " *   model calls      : %d" % meta["model_calls"],
        " *   permuter steps   : %d" % meta["permuter_steps"],
        " *   shape            : %s" % " ".join(meta["shape"]),
        " *   exact_bytes      : %s" % str(meta["exact_bytes"]).lower(),
        " *   source sha256    : %s" % sha,
        " *",
        " * Re-proved by src-match/verify.py against the retail DOL; the hash",
        " * above covers the C below this header only.",
        " */",
        "",
    ]
    (SRC_MATCH / rel).parent.mkdir(parents=True, exist_ok=True)
    (SRC_MATCH / rel).write_text("\n".join(head) + body)

    entry = {"name": rec["name"], "addr": "0x%08x" % rec["addr"],
             "insns": rec["size"] // 4, "src": rel, "sym": "f",
             "iterations": meta["iterations"],
             "exact_bytes": meta["exact_bytes"],
             "shape": " ".join(meta["shape"]),
             "produced_by": "loop.py",
             "seed": meta["seed"],
             "model_calls": meta["model_calls"],
             "permuter_steps": meta["permuter_steps"],
             "source_sha256": sha}
    reg["functions"].append(entry)
    reg_path.write_text(json.dumps(reg, indent=1) + "\n")
    return entry


# ---------------------------------------------------------------------------
# the loop
# ---------------------------------------------------------------------------

def _shape_field(sh, outcome):
    """The shape as the ledger stores it.

    The shape is what the seeder keys on, so it is worth recording -- but a
    400-instruction function the seeder never touched contributes 3 KB of
    mnemonics nobody will read.  Full shape when the row reached the compiler,
    a prefix otherwise.  `matched.json` always keeps the full shape.
    """
    keep = 24 if (outcome or "").startswith(("MATCH", "UNMATCHED")) else 8
    if len(sh) <= keep:
        return " ".join(sh)
    return " ".join(sh[:keep]) + " ...(+%d)" % (len(sh) - keep)


def run_one(oracle, name, exemplars, model=None, budget=3, do_permute=True,
            record=True):
    t0 = time.time()
    rec, retail = oracle.target(name)
    if rec is None:
        return {"function": name, "outcome": "NOT_IN_MAP"}
    sh = shape_of(retail, rec["addr"])
    row = {"function": name, "addr": "0x%08x" % rec["addr"],
           "insns": rec["size"] // 4, "shape": _shape_field(sh, None),
           "_shape_full": list(sh),
           "iterations": 0, "model_calls": 0, "permuter_steps": 0,
           "compiles": 0, "seed": None, "outcome": None,
           "best_match_pct": 0.0, "first_diff": None,
           "first_diff_class": None, "wall_s": 0.0}
    c0 = oracle.compiles

    try:
        src, seeder = seed(rec, retail, oracle.smap)
    except SeedFail as ex:
        row["seed_fail"] = str(ex)
        if model is None:
            # Seed-only mode: a refusal is the result, not a failure to try.
            row["outcome"] = "NO_SEED"
            row["wall_s"] = round(time.time() - t0, 3)
            return row
        # With a model available the seeder's refusal is where the model earns
        # its keep: it writes candidate 0 from the disassembly instead.
        row["seed"] = "model (seeder refused: %s)" % str(ex)[:80]
        src, v = "", {"verdict": "NO_CANDIDATE", "match_pct": 0.0,
                      "seed_fail": str(ex)}
        return _llm_phase(oracle, rec, retail, sh, row, src, v, model,
                          exemplars, budget, do_permute, record, t0, c0)
    row["seed"] = seeder

    row["iterations"] = 1
    v = oracle.check(rec, retail, src, want_diff=True)
    row["best_match_pct"] = v.get("match_pct", 0.0)
    if v["verdict"] == "MATCH":
        row["outcome"] = "MATCH_SEED"
        row["exact_bytes"] = v["exact_bytes"]
        row["compiles"] = oracle.compiles - c0
        row["wall_s"] = round(time.time() - t0, 3)
        if record:
            record_match(rec, retail, src, {
                "seed": "seed/%s (iteration 0, no model call)" % seeder,
                "iterations": 1, "model_calls": 0, "permuter_steps": 0,
                "shape": sh, "exact_bytes": v["exact_bytes"]})
        return row
    if v["verdict"] == "MATCH_UNVERIFIED":
        row["outcome"] = "MATCH_UNVERIFIED"
        row["note"] = v["unverified_reason"]
        row["compiles"] = oracle.compiles - c0
        row["wall_s"] = round(time.time() - t0, 3)
        return row

    row["first_diff"] = (v.get("first_diff") or {}).get("addr")
    row["first_diff_class"] = classify(v)

    if do_permute:
        psrc, pv, steps = permute(oracle, rec, retail, src, seeder=seeder)
        row["permuter_steps"] = steps
        if psrc is not None:
            row["outcome"] = "MATCH_PERMUTER"
            row["exact_bytes"] = pv["exact_bytes"]
            row["best_match_pct"] = 100.0
            row["compiles"] = oracle.compiles - c0
            row["wall_s"] = round(time.time() - t0, 3)
            if record:
                record_match(rec, retail, psrc, {
                    "seed": "seed/%s then permuter (%d mechanical mutants, "
                            "no model call)" % (seeder, steps),
                    "iterations": 1, "model_calls": 0,
                    "permuter_steps": steps,
                    "shape": sh, "exact_bytes": pv["exact_bytes"]})
            return row

    return _llm_phase(oracle, rec, retail, sh, row, src, v, model, exemplars,
                      budget, do_permute, record, t0, c0)


def _llm_phase(oracle, rec, retail, sh, row, src, v, model, exemplars,
               budget, do_permute, record, t0, c0):
    """The only stage that costs GPU.  Entered either with a seed the oracle
    rejected, or -- when the seeder refused outright -- with no candidate at
    all, which is where a model is actually needed."""
    def finish(outcome, source, verdict, note=None):
        row["outcome"] = outcome
        row["exact_bytes"] = verdict["exact_bytes"]
        row["compiles"] = oracle.compiles - c0
        row["wall_s"] = round(time.time() - t0, 3)
        if record:
            record_match(rec, retail, source, {
                "seed": note, "iterations": row["iterations"],
                "model_calls": row["model_calls"],
                "permuter_steps": row["permuter_steps"],
                "shape": sh, "exact_bytes": verdict["exact_bytes"]})
        return row

    if model is not None:
        ex = exemplars.get(sh)
        exsrc = ex[1] if ex else None
        for _ in range(budget):
            prompt = build_prompt(rec, retail, src, v, exemplar=exsrc)
            try:
                reply = model.ask(prompt)
                src = extract_c(reply)
            except Exception as e:               # noqa: BLE001
                row["model_error"] = str(e)[:300]
                break
            row["model_calls"] += 1
            row["iterations"] += 1
            v = oracle.check(rec, retail, src, want_diff=True)
            row["best_match_pct"] = max(row["best_match_pct"],
                                        v.get("match_pct", 0.0))
            if v["verdict"] == "MATCH":
                return finish("MATCH_LLM", src, v,
                              "%s then %d model call(s)"
                              % (row["seed"], row["model_calls"]))
            if v["verdict"] == "MATCH_UNVERIFIED":
                row["outcome"] = "MATCH_UNVERIFIED"
                row["note"] = v["unverified_reason"]
                row["compiles"] = oracle.compiles - c0
                row["wall_s"] = round(time.time() - t0, 3)
                return row
            if do_permute and v.get("match_pct", 0) >= 90.0:
                psrc, pv, steps = permute(oracle, rec, retail, src)
                row["permuter_steps"] += steps
                if psrc is not None:
                    return finish("MATCH_LLM_PERMUTER", psrc, pv,
                                  "%s, %d model call(s), permuter"
                                  % (row["seed"], row["model_calls"]))

    row["outcome"] = "UNMATCHED" if row["iterations"] else "NO_SEED"
    row["first_diff"] = (v.get("first_diff") or {}).get("addr")
    row["first_diff_class"] = classify(v) if row["iterations"] else None
    row["compiles"] = oracle.compiles - c0
    row["wall_s"] = round(time.time() - t0, 3)
    return row


COMPILER_MARKERS = [
    ("loop codegen is not implemented", "compiler: loops"),
    ("general register was requested for a non-leaf", "compiler: constant materialisation"),
    ("pointer leaf access needs a pointer variable", "compiler: pointer leaf access"),
    ("branchless compare idioms", "compiler: branchless compare"),
    ("not implemented", "compiler: unimplemented lowering"),
    ("roadmap", "compiler: roadmap"),
]


def _codegen_class(retail, cand, relocs=None):
    """Separate a CODE GENERATOR difference from a C difference.

    This distinction decides whether a function is worth a model call at all,
    and getting it wrong is how a loop burns GPU on something no C spelling can
    reach.  Three cases are detectable from the bytes alone:

      scheduling         the two objects contain the SAME instructions in a
                         different order -- real MWCC hoists constant setup
                         above the stores it feeds; mwcc-rs does not.
      colouring          the same instruction MIX in a different order and/or
                         different registers.  mwcc-rs's own README names
                         matching MWCC's register colouring as its core
                         research target.
      rematerialisation  the candidate is longer, and the surplus is duplicate
                         `li`s of a constant the retail loads once and reuses.

    None is reachable from the source, so all three are compiler statements.
    Relocated operand fields are zeroed on both sides first: an unlinked `bl`
    carries 0 where the retail carries a real displacement, and comparing those
    raw would hide the very permutation being looked for.
    """
    if retail == cand:
        return None
    rw = list(struct.unpack(">%dI" % (len(retail) // 4), retail))
    cw = list(struct.unpack(">%dI" % (len(cand) // 4), cand))
    for off, rtype, _n, _a in (relocs or []):
        _nm, mask = __import__("objdiff").PPC_RELOC.get(rtype, (None, 0xFFFFFFFF))
        i = off // 4
        if i < len(cw):
            cw[i] &= ~mask
        if i < len(rw):
            rw[i] &= ~mask
    if len(rw) == len(cw) and sorted(rw) == sorted(cw):
        return ("compiler: instruction scheduling -- same %d instructions in a "
                "different order" % len(rw))
    if len(rw) == len(cw):
        import ppcdis as _p
        rm = sorted(_p.disasm_word(w, 0).split()[0] for w in rw)
        cm = sorted(_p.disasm_word(w, 0).split()[0] for w in cw)
        if rm == cm:
            return ("compiler: scheduling and/or register colouring -- the same "
                    "%d-instruction mix, differently ordered or allocated"
                    % len(rw))
    if len(cw) > len(rw):
        import collections
        extra = collections.Counter(cw) - collections.Counter(rw)
        lis = [w for w in extra.elements() if (w >> 26) == 14 and not ((w >> 16) & 31)]
        if lis and len(lis) == sum(extra.values()):
            return ("compiler: constant rematerialised -- %d extra `li`, retail "
                    "loads the constant once and reuses it" % len(lis))
        # The same case one level coarser: identical instruction SEQUENCE once
        # the surplus `li`s are removed.  Retail differs only by which register
        # each constant lands in -- register colouring, which mwcc-rs's own
        # README calls its core research target.  Not reachable from the C.
        def mn(ws):
            return [t.split()[0] for t in
                    (__import__("ppcdis").disasm_word(w, 0) for w in ws)]
        rm, cm = mn(rw), mn(cw)
        if [m for m in rm if m != "li"] == [m for m in cm if m != "li"]:
            return ("compiler: constant rematerialised / register colouring -- "
                    "%d extra `li`, the rest of the sequence is identical"
                    % (cm.count("li") - rm.count("li")))
    return None


def classify(v):
    """Is the first mismatch a COMPILER capability limit or a genuine C
    difference?  The spike's s3.1.3 found all five of its non-matches were the
    former, and that distinction decides whether a function is worth a model
    call at all."""
    if v["verdict"] == "BUILD_FAILED":
        log = (v.get("compiler_log") or "").lower()
        for k, label in COMPILER_MARKERS:
            if k in log:
                return label
        return "compiler: build failed (other)"
    if v.get("mismatch_class"):
        return v["mismatch_class"]
    if not v.get("size_match", True):
        return "C: instruction count differs (%d retail vs %d candidate)" \
            % (v.get("retail_insns", 0), v.get("cand_insns", 0))
    fd = v.get("first_diff")
    if not fd:
        return "unknown"
    r, c = fd["retail"].split()[0], fd["cand"].split()[0]
    if r != c:
        return "C: different opcode (%s vs %s)" % (r, c)
    return "C: same opcode %s, different operands" % r


# ---------------------------------------------------------------------------
# target selection
# ---------------------------------------------------------------------------

def corpus(oracle, max_insns=None):
    """Map-resident .text functions -- the set the harness can address, because
    a function absent from the link map has no extent and no callee names."""
    out = []
    for r in oracle.smap.text_functions():
        if r["size"] % 4 or r["size"] == 0:
            continue
        if max_insns and r["size"] // 4 > max_insns:
            continue
        if oracle.dol.read(r["addr"], r["size"]) is None:
            continue
        out.append(r)
    return out


def shape_shared(oracle, exemplars, max_insns=16):
    """The spike s3.1.5 class: functions sharing an EXACT matched shape with an
    already-matched exemplar."""
    have = {e["name"] for e in
            json.loads((SRC_MATCH / "matched.json").read_text())["functions"]}
    out = []
    for r in corpus(oracle, max_insns):
        if r["name"] in have:
            continue
        b = oracle.dol.read(r["addr"], r["size"])
        if shape_of(b, r["addr"]) in exemplars:
            out.append(r)
    return out


# ---------------------------------------------------------------------------
# CLI
# ---------------------------------------------------------------------------

def cmd_shapes(a, oracle):
    import collections
    hist = collections.Counter()
    ex = {}
    for r in corpus(oracle, a.max_insns):
        b = oracle.dol.read(r["addr"], r["size"])
        sh = shape_of(b, r["addr"])
        hist[sh] += 1
        ex.setdefault(sh, r["name"])
    exm = load_exemplars(oracle)
    print("map .text functions <= %d insns: %d, distinct shapes: %d"
          % (a.max_insns, sum(hist.values()), len(hist)))
    print()
    print("%5s %5s %-28s %s" % ("count", "insns", "exemplar/first", "shape"))
    tot_f = tot_i = 0
    for sh, c in hist.most_common(a.top):
        mark = "*" if sh in exm else " "
        print("%5d %5d %s%-27s %s"
              % (c, len(sh), mark, exm.get(sh, (ex[sh],))[0], " ".join(sh)))
    for sh, c in hist.items():
        if sh in exm:
            tot_f += c
            tot_i += c * len(sh)
    print()
    print("* = a matched exemplar of this shape already exists")
    print("shape-shared with a matched exemplar: %d functions, %d instructions"
          % (tot_f, tot_i))
    return 0


def cmd_seed(a, oracle):
    rec, retail = oracle.target(a.function)
    if rec is None:
        print("not in the link map: %s" % a.function, file=sys.stderr)
        return 2
    try:
        src, nm = seed(rec, retail, oracle.smap)
    except SeedFail as ex:
        print("NO SEED (%s)" % ex, file=sys.stderr)
        return 1
    print("/* seeder: %s */" % nm)
    print(src, end="")
    if a.check:
        v = oracle.check(rec, retail, src, want_diff=True)
        print("\n" + (v.get("diff_text") or ""))
        print("VERDICT %s  %.2f%%" % (v["verdict"], v.get("match_pct", 0.0)))
        return 0 if v["verdict"] == "MATCH" else 1
    return 0


def cmd_permute(a, oracle):
    rec, retail = oracle.target(a.function)
    src = Path(a.candidate).read_text() if a.candidate else \
        seed(rec, retail, oracle.smap)[0]
    s, v, n = permute(oracle, rec, retail, src, workers=a.workers)
    print("permuter: %d mutants compiled" % n)
    if s is None:
        print("no mutant matched")
        return 1
    print(s)
    return 0


def cmd_llm_step(a, oracle):
    rec, retail = oracle.target(a.function)
    src = Path(a.candidate).read_text()
    v = oracle.check(rec, retail, src, want_diff=True) if oracle.available() \
        else json.loads(Path(a.verdict).read_text())
    exm = load_exemplars(oracle) if oracle.available() else {}
    sh = shape_of(retail, rec["addr"])
    prompt = build_prompt(rec, retail, src, v,
                          exemplar=(exm.get(sh) or (None, None))[1])
    if a.print_prompt:
        print(prompt)
        return 0
    m = ModelClient(recorded=a.recorded)
    reply = m.ask(prompt)
    print(extract_c(reply))
    print("/* %s */" % json.dumps(m.stats()))
    return 0


def cmd_run(a, oracle):
    if not oracle.available():
        print("no compiler: build mwcc-rs per "
              "research/tools/matching-decomp/TOOLCHAIN.md, or set MWCC_RS",
              file=sys.stderr)
        return 3
    exm = load_exemplars(oracle)
    if a.function:
        targets = [oracle.target(a.function)[0]]
    elif a.klass == "shape-shared":
        targets = shape_shared(oracle, exm, a.max_insns)
    elif a.all_compilable:
        have = {e["name"] for e in json.loads(
            (SRC_MATCH / "matched.json").read_text())["functions"]}
        targets = [r for r in corpus(oracle, a.max_insns)
                   if r["name"] not in have]
    else:
        print("give --function, --class shape-shared, or --all-compilable",
              file=sys.stderr)
        return 2
    if a.limit:
        targets = targets[:a.limit]

    model = None
    if not a.no_llm:
        model = ModelClient(recorded=a.recorded)

    led = Ledger(a.ledger or LEDGER_DEFAULT)
    t0 = time.time()
    import collections
    outcome = collections.Counter()
    insns = collections.Counter()
    classes = collections.Counter()
    for i, rec in enumerate(targets):
        if rec is None:
            continue
        row = run_one(oracle, rec["name"], exm, model=model,
                      do_permute=not a.no_permute, record=not a.dry_run,
                      budget=a.budget)
        row["ts"] = time.strftime("%Y-%m-%dT%H:%M:%S")
        row["run"] = a.tag
        full = row.pop("_shape_full", None)
        if full:
            row["shape"] = _shape_field(full, row["outcome"])
        led.write(row)
        outcome[row["outcome"]] += 1
        insns[row["outcome"]] += row.get("insns", 0)
        if row["outcome"] in ("UNMATCHED", "NO_SEED", "MATCH_UNVERIFIED"):
            if row["outcome"] == "NO_SEED":
                lbl = "seeder refused: " + row.get("seed_fail", "?")[:70]
            else:
                lbl = row.get("first_diff_class") or row["outcome"]
            classes[lbl] += 1
        if a.progress and (i + 1) % a.progress == 0:
            print("  ... %d/%d  %s" % (i + 1, len(targets), dict(outcome)),
                  file=sys.stderr)

    wall = time.time() - t0
    total = sum(outcome.values())
    matched = sum(v for k, v in outcome.items() if k.startswith("MATCH")
                  and k != "MATCH_UNVERIFIED")
    print()
    print("RUN %s  targets=%d  wall=%.1fs  compiles=%d  compile_s=%.1f"
          % (a.tag, total, wall, oracle.compiles, oracle.compile_s))
    print("-" * 72)
    for k in sorted(outcome):
        print("  %-22s %5d functions  %6d instructions"
              % (k, outcome[k], insns[k]))
    print("-" * 72)
    print("  MATCHED TOTAL          %5d functions  %6d instructions"
          % (matched, sum(v for k, v in insns.items()
                          if k.startswith("MATCH") and k != "MATCH_UNVERIFIED")))
    if total:
        print("  throughput             %.1f functions/minute (CPU only)"
              % (60.0 * total / max(wall, 1e-9)))
    if classes:
        print()
        print("FIRST-MISMATCH / REFUSAL CLASSES")
        for k, c in classes.most_common(25):
            print("  %5d  %s" % (c, k))
    if model is not None:
        print()
        print("MODEL: %s" % json.dumps(model.stats()))

    res = {"run": a.tag, "targets": total, "wall_s": round(wall, 2),
           "compiles": oracle.compiles, "compile_s": round(oracle.compile_s, 2),
           "outcomes": dict(outcome), "instructions": dict(insns),
           "classes": dict(classes),
           "model": model.stats() if model else None,
           "ledger": str(a.ledger or LEDGER_DEFAULT)}
    out = Path(a.results or RESULTS_DEFAULT)
    prev = json.loads(out.read_text()) if out.exists() else {"runs": []}
    prev["runs"] = [r for r in prev.get("runs", []) if r.get("run") != a.tag]
    prev["runs"].append(res)
    out.parent.mkdir(parents=True, exist_ok=True)
    out.write_text(json.dumps(prev, indent=1) + "\n")
    return 0


# ---------------------------------------------------------------------------
# selftest -- runs with no compiler and no network
# ---------------------------------------------------------------------------

# The MODEL SERVER COULD NOT BE RUN: it answers on 127.0.0.1:8888 but reports
# `"loaded": false` for every model, so a completion would force a 27B load
# onto a GPU that is leased to another tenant.  The two replies below are
# therefore RECONSTRUCTED, not captured -- the EDIT each one makes is the real
# one from the record (src-match/game/zz_02650c0_.c: the first candidate
# returned `char` and lost the retail's `extsb`; widening to `int` restored
# it), the prose around it is not.  They exercise every line of the model path
# except the socket.
RECORDED_WIDEN_RETURN = (
    "The first mismatch is at 0x802650c4: retail has `extsb r3, r3` and the "
    "candidate goes straight to `blr`.\n\n"
    "```c\n"
    "typedef struct S {\n"
    "    char pad0;\n"
    "    char flag;\n"
    "} S;\n"
    "\n"
    "int f(S *s)   // 6: was `char f`, widened so the return is sign-extended\n"
    "{\n"
    "    return s->flag;\n"
    "}\n"
    "```\n"
)

FIXTURE_REPLY = (
    "Looking at the first mismatch, the return type is too narrow.\n\n"
    "```c\n"
    "typedef struct S {\n"
    "    char pad[0x2d4];\n"
    "    int  field_2d4;\n"
    "} S;\n"
    "\n"
    "int f(S *s)   // 7: was `char f`, widened so the extsb is not emitted\n"
    "{\n"
    "    return s->field_2d4;\n"
    "}\n"
    "```\n"
)


def cmd_selftest(a, oracle):
    ok = bad = 0

    def chk(label, cond, detail=""):
        nonlocal ok, bad
        print("  [%s] %s%s" % ("ok  " if cond else "FAIL", label,
                               ("  -- " + detail) if detail and not cond else ""))
        ok += bool(cond)
        bad += not cond

    print("== S1  decoder ==")
    chk("lwz r3, 0x2d4(r3)", decode(0x806302D4) ==
        {"mn": "lwz", "rd": 3, "ra": 3, "d": 0x2d4, "width": 4, "signed": True})
    chk("extsb r3, r3 is X-form rA<-rS", decode(0x7C630774)["mn"] == "extsb")
    chk("blr", decode(0x4E800020)["mn"] == "blr")
    chk("beqlr", decode(0x4D820020)["mn"] == "beqlr")
    chk("li r0, 3", decode(0x38000003) ==
        {"mn": "li", "rd": 0, "ra": 0, "d": 3})
    chk("stwu r1, -0x10(r1) is negative", decode(0x9421FFF0)["d"] == -0x10)
    chk("unmodelled returns None", decode(0x7C000026) is None)

    print("== S2  seeder reproduces the committed exemplars ==")
    cases = [
        # (name, bytes, addr, expected substring)
        ("accessor", b"\x80\x63\x02\xd4\x4e\x80\x00\x20", 0x80206F8C,
         "return p0->field_2d4;"),
        ("const return", b"\x38\x60\x01\x00\x4e\x80\x00\x20", 0x8008B900,
         "return 0x100;"),
        ("setter", b"\x90\x83\x00\x18\x4e\x80\x00\x20", 0x80009C28,
         "p0->field_18 = p1;"),
        ("signed char", b"\x88\x63\x00\x01\x7c\x63\x07\x74\x4e\x80\x00\x20",
         0x802650C0, "char           field_1;"),
        ("guarded store",
         b"\x28\x03\x00\x00\x4d\x82\x00\x20\x38\x00\x00\x04"
         b"\x90\x03\x00\x00\x4e\x80\x00\x20", 0x802A0A6C,
         "if (p0 == 0)"),
        ("empty", b"\x4e\x80\x00\x20", 0x80156A8, "void f(void)"),
    ]

    class _FakeMap(object):
        def lookup(self, a):
            return None
    for label, blob, addr, want in cases:
        rec = {"name": label, "addr": addr, "size": len(blob)}
        try:
            src, nm = seed(rec, blob, _FakeMap())
            chk("seed %-14s" % label, want in src, "got:\n" + src)
        except SeedFail as ex:
            chk("seed %-14s" % label, False, str(ex))

    print("== S3  seeder REFUSES what it cannot model ==")
    for label, blob in [
            ("lis+addi+and", b"\x3c\x60\x00\xff\x38\x03\x1f\x7f"
                             b"\x7c\x83\x00\x38\x4e\x80\x00\x20"),
            ("mftb", b"\x7c\x6d\x42\xe6\x4e\x80\x00\x20")]:
        rec = {"name": label, "addr": 0x80000000, "size": len(blob)}
        try:
            seed(rec, blob, _FakeMap())
            chk("refuse %s" % label, False, "it produced a seed")
        except SeedFail:
            chk("refuse %s" % label, True)

    print("== S4  wrapper seeder names the callee through the map ==")

    class _Map(object):
        def lookup(self, a):
            return {"name": "zz_0012308_"} if a == 0x80012308 else None
    blob = (b"\x94\x21\xff\xf0\x7c\x08\x02\xa6\x90\x01\x00\x14"
            b"\x48\x00\x00\x35\x80\x01\x00\x14\x7c\x08\x03\xa6"
            b"\x38\x21\x00\x10\x4e\x80\x00\x20")
    rec = {"name": "zz_00122c8_", "addr": 0x800122C8, "size": 32}
    src, nm = seed(rec, blob, _Map())
    chk("seeder chosen", nm == "wrapper")
    chk("declares the callee", "extern void zz_0012308_(void);" in src)
    chk("calls it", "zz_0012308_();" in src)
    rec2 = dict(rec)
    blob2 = blob[:12] + b"\x48\x00\x10\x01" + blob[16:]   # unknown callee
    try:
        seed(rec2, blob2, _Map())
        chk("refuses an unmapped callee", False)
    except SeedFail:
        chk("refuses an unmapped callee", True)

    print("== S5  permuter move set ==")
    base = ("typedef struct S {\n    char pad[0x4];\n    int  field_4;\n} S;\n"
            "\nint f(S *p0)\n{\n    return p0->field_4;\n}\n")
    muts = text_mutations(base)
    chk("produces mutants", len(muts) >= 5, str(len(muts)))
    chk("flips the return type",
        any(m.startswith("typedef") and "unsigned int f(" in m for m in muts))
    chk("flips a field type",
        any(re.search(r"^\s+(unsigned int|short|long)\s+field_4;$", m, re.M)
            for m in muts))
    chk("never returns the input", base not in muts)
    two = ("void f(S *p0, S *p1)\n{\n    p0->field_0 = p1;\n"
           "    p0->field_4 = p1;\n}\n")
    chk("reorders adjacent statements",
        any(m.index("field_4") < m.index("field_0")
            for m in text_mutations(two)))
    chk("spec space is bounded", len(spec_variants()) <= 64)

    print("== S6  model step, against a RECORDED response (no network) ==")
    d = Path(tempfile.mkdtemp(prefix="mdfix_"))
    (d / "fix.json").write_text(json.dumps({"response": FIXTURE_REPLY}))
    m = ModelClient(recorded=d)
    reply = m.ask("any prompt")
    c = extract_c(reply)
    chk("extracts the fenced C", "int f(S *s)" in c)
    chk("strips the line-number citation", "//" not in c)
    chk("counts the call", m.stats()["model_calls"] == 1)
    chk("estimates tokens", m.stats()["reply_tokens_est"] > 0)
    for bad_reply, why in [
            ("here is the fix", "no fence, no function"),
            ("```c\nint f(S *s) {\n    return s->x;\n```", "unbalanced braces"),
            ("```c\n/* nothing */\n```", "no function f")]:
        try:
            extract_c(bad_reply)
            chk("rejects %s" % why, False)
        except ValueError:
            chk("rejects %s" % why, True)

    print("== S7  prompt carries the diff, not the world ==")
    v = {"verdict": "MISMATCH", "match_pct": 66.67,
         "first_diff": {"addr": "0x802650c4", "retail": "extsb r3, r3",
                        "cand": "blr"},
         "diff_text": "..."}
    p = build_prompt({"name": "t", "addr": 0x802650C0, "size": 12},
                     b"\x88\x63\x00\x01\x7c\x63\x07\x74\x4e\x80\x00\x20",
                     "int f(void) { return 0; }\n", v, exemplar="EXEMPLAR")
    chk("names the first mismatch", "0x802650c4" in p)
    chk("line-numbers the candidate", "  1| int f(void)" in p)
    chk("carries the exemplar", "EXEMPLAR" in p)
    chk("no Ghidra C", "undefined4" not in p and "FUN_80" not in p)
    chk("asks for one fence", "```c fence" in p)

    print("== S8  the unchecked-relocation guard ==")
    chk("REL24 is the only name-checkable type", REL24 == 10)
    chk("classify: build failure is a compiler statement",
        classify({"verdict": "BUILD_FAILED",
                  "compiler_log": "loop codegen is not implemented yet"})
        == "compiler: loops")
    chk("classify: opcode difference is a C statement",
        classify({"verdict": "MISMATCH", "size_match": True,
                  "first_diff": {"retail": "extsb r3, r3", "cand": "or r3, r3"}})
        .startswith("C: different opcode"))
    sched_r = b"\x90\x83\x13\x18\x38\x00\x00\x00\x90\xa3\x13\x1c\x90\x03\x13\x20"
    sched_c = b"\x90\x83\x13\x18\x90\xa3\x13\x1c\x38\x00\x00\x00\x90\x03\x13\x20"
    chk("codegen class: scheduling",
        (_codegen_class(sched_r, sched_c) or "").startswith(
            "compiler: instruction scheduling"))
    remat_r = b"\x38\x00\x00\x00\x98\x03\x02\xe5\x98\x03\x02\xe6"
    remat_c = (b"\x38\x00\x00\x00\x98\x03\x02\xe5"
               b"\x38\x00\x00\x00\x98\x03\x02\xe6")
    chk("codegen class: rematerialisation",
        (_codegen_class(remat_r, remat_c) or "").startswith(
            "compiler: constant rematerialised"))
    chk("codegen class: silent when the bytes agree",
        _codegen_class(sched_r, sched_r) is None)
    chk("classify: size difference is named",
        classify({"verdict": "MISMATCH", "size_match": False,
                  "retail_insns": 3, "cand_insns": 2}).startswith("C: instruction count"))

    print("== S9  end to end: wrong candidate -> oracle -> model -> MATCH ==")
    comp = find_compiler()
    iso = Path("D:/GotYaForce/Gotcha Force.iso")
    if comp is None or not iso.exists():
        print("  [skip] no compiler or no GCM on this machine "
              "(the eight groups above need neither)")
    else:
        o = Oracle()
        rec, retail = o.target("zz_02650c0_")
        # The spike's own recorded two-iteration case: the first candidate for
        # zz_02650c0_ returned `char` and lost the retail's `extsb`; widening
        # the return type to `int` put it back (src-match/game/zz_02650c0_.c).
        wrong = ("typedef struct S { char pad0; char flag; } S;\n"
                 "char f(S *s) { return s->flag; }\n")
        v0 = o.check(rec, retail, wrong, want_diff=True)
        chk("the wrong candidate is rejected", v0["verdict"] == "MISMATCH",
            v0["verdict"])
        chk("the oracle localises the loss of extsb",
            (v0.get("first_diff") or {}).get("retail", "").startswith("extsb"),
            json.dumps(v0.get("first_diff")))
        prompt = build_prompt(rec, retail, wrong, v0)
        d2 = Path(tempfile.mkdtemp(prefix="mdfix2_"))
        (d2 / (hashlib.sha256(prompt.encode("utf-8")).hexdigest()[:16] + ".json")
         ).write_text(json.dumps({"response": RECORDED_WIDEN_RETURN}))
        row = {"function": rec["name"], "insns": 3, "iterations": 1,
               "model_calls": 0, "permuter_steps": 0, "seed": "seed/leaf",
               "best_match_pct": v0["match_pct"], "outcome": None}
        out = _llm_phase(o, rec, retail, shape_of(retail, rec["addr"]), row,
                         wrong, v0, ModelClient(recorded=d2), {}, 2,
                         True, False, time.time(), o.compiles)
        chk("the loop reaches MATCH through the model",
            out["outcome"] == "MATCH_LLM", str(out.get("outcome")))
        chk("one model call, two iterations",
            out["model_calls"] == 1 and out["iterations"] == 2,
            "%s/%s" % (out["model_calls"], out["iterations"]))

    print()
    print("%d ok, %d failed" % (ok, bad))
    return 0 if bad == 0 else 1


def main():
    ap = argparse.ArgumentParser(prog="loop.py")
    ap.add_argument("--repo", default="D:/GotYaForce")
    ap.add_argument("--build", default=BUILD)
    ap.add_argument("--compiler")
    sub = ap.add_subparsers(dest="cmd")

    s = sub.add_parser("shapes")
    s.add_argument("--max-insns", type=int, default=16)
    s.add_argument("--top", type=int, default=40)
    s.set_defaults(fn=cmd_shapes, needs_dol=True)

    s = sub.add_parser("seed")
    s.add_argument("--function", required=True)
    s.add_argument("--check", action="store_true")
    s.set_defaults(fn=cmd_seed, needs_dol=True)

    s = sub.add_parser("permute")
    s.add_argument("--function", required=True)
    s.add_argument("--candidate")
    s.add_argument("--workers", type=int, default=8)
    s.set_defaults(fn=cmd_permute, needs_dol=True)

    s = sub.add_parser("llm-step")
    s.add_argument("--function", required=True)
    s.add_argument("--candidate", required=True)
    s.add_argument("--verdict")
    s.add_argument("--recorded")
    s.add_argument("--print-prompt", action="store_true")
    s.set_defaults(fn=cmd_llm_step, needs_dol=True)

    s = sub.add_parser("run")
    s.add_argument("--function")
    s.add_argument("--class", dest="klass")
    s.add_argument("--all-compilable", action="store_true")
    s.add_argument("--max-insns", type=int, default=16)
    s.add_argument("--limit", type=int)
    s.add_argument("--budget", type=int, default=3)
    s.add_argument("--no-llm", action="store_true")
    s.add_argument("--no-permute", action="store_true")
    s.add_argument("--dry-run", action="store_true")
    s.add_argument("--recorded")
    s.add_argument("--ledger")
    s.add_argument("--results")
    s.add_argument("--tag", default="run")
    s.add_argument("--progress", type=int, default=100)
    s.set_defaults(fn=cmd_run, needs_dol=True)

    s = sub.add_parser("selftest")
    s.set_defaults(fn=cmd_selftest, needs_dol=False)

    a = ap.parse_args()
    if not getattr(a, "fn", None):
        ap.print_help()
        return 2
    oracle = Oracle(repo=a.repo, build=a.build, compiler=a.compiler) \
        if a.needs_dol else None
    return a.fn(a, oracle)


if __name__ == "__main__":
    sys.exit(main())
