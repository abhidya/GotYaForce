#!/usr/bin/env python3
"""sda_recover.py -- recover the functions the small-data refusal cost us.

`loop.py`'s `leaf` seeder refuses every load or store through r2/r13
(`_base_fail`), and `docs/matching-loop.md` s2.3 counts the price: **104
functions corpus-wide**, including every global accessor, which is among the
easiest shapes in the binary.  That refusal was correct while a data
relocation's operand was masked and never checked -- a candidate naming the
wrong global reported MATCH.

`datareloc.py` closes that hole: the retail encoding names one absolute
address, the candidate's relocation symbol names one absolute address, and the
oracle now requires them to be equal.  So the refusal can be lifted -- BEHIND
THAT VERIFICATION AND NOWHERE ELSE.

This driver does the lifting for the recovery run without touching `loop.py`:
it re-derives C for the refused functions with a small-data-aware version of
the same symbolic evaluator, compiles it through `match.py`, and records only
what the strengthened oracle calls MATCH.  A MATCH_UNVERIFIED is still never
written.  `loop.py`'s own seeders are untouched; the seeder lane lifts its
refusal by calling `datareloc.global_symbol` / `global_decl` (documented at
the foot of `datareloc.py`).

    python research/tools/matching-decomp/sda_recover.py --list
    python research/tools/matching-decomp/sda_recover.py --dry-run
    python research/tools/matching-decomp/sda_recover.py --record
"""
from __future__ import annotations

import argparse
import json
import re
import sys
import tempfile
import time
from pathlib import Path

HERE = Path(__file__).resolve().parent
sys.path.insert(0, str(HERE))

import datareloc                                            # noqa: E402
import match as MATCH                                       # noqa: E402
import loop as LOOP                                         # noqa: E402
from dolsym import load, function_bytes                     # noqa: E402
from objdiff import Elf32BE, compare                        # noqa: E402
from ppcdis import disasm                                   # noqa: E402

SeedFail = LOOP.SeedFail
CTYPE = LOOP.CTYPE


# ---------------------------------------------------------------------------
# expressions
# ---------------------------------------------------------------------------

class E(object):
    """CONST k | ARG i | FIELD(arg) | GLOB(addr) | GFIELD(global, offset)"""

    def __init__(self, kind, **kw):
        self.kind = kind
        self.__dict__.update(kw)

    def c(self, names):
        if self.kind == "const":
            return LOOP._lit(self.k)
        if self.kind == "arg":
            return "p%d" % self.i
        if self.kind == "field":
            return "p%d->%s" % (self.i, LOOP._fname(self.off))
        if self.kind == "glob":
            return names[self.addr]
        if self.kind == "gfield":
            return "%s->%s" % (names[self.addr], LOOP._fname(self.off))
        if self.kind == "local":
            return self.name
        raise SeedFail("unrenderable expression")


def _sda_addr(ins, bases):
    """The absolute address a decoded r2/r13 load or store names."""
    if ins["ra"] in bases:
        return (bases[ins["ra"]] + ins["d"]) & 0xFFFFFFFF
    return None


# ---------------------------------------------------------------------------
# the small-data-aware leaf seeder
# ---------------------------------------------------------------------------

def seed_leaf_sda(rec, retail, smap, bases, resolver, spec=None):
    """`loop.seed_leaf`'s envelope plus small-data globals.

    Everything `seed_leaf` handles is handled the same way and refused the same
    way; the ONLY thing added is that a base register of r2/r13 -- and a
    register holding a word loaded from such a global -- is now expressible,
    because the resulting relocation is now checkable.
    """
    spec = spec or {}
    ins = [LOOP.decode(w) for _a, w, _t in disasm(retail, rec["addr"])]
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

    regs = {r: E("arg", i=r - 3) for r in range(3, 11)}
    fields = {}          # arg index    -> {off: (width, signed)}
    gfields = {}         # global addr  -> {off: (width, signed)}
    gscalar = {}         # global addr  -> (width, signed)
    stmts, used_args, ptr_args = [], set(), set()
    locals_ = []         # [(name, ctype, expr)] for the `hoist` variant
    # A global read into a register BEFORE a store keeps the OLD value; if the
    # C spells it as a bare global read after the store, it reads the NEW one.
    # `hoist` snapshots such reads into a local at the point of the load, which
    # is what the retail `lwz old; stw new; mr r3, old` swap idiom is.
    hoist = bool(spec.get("hoist"))
    store_after = [any(j["mn"] in ("stw", "stb", "sth") for j in body[n + 1:])
                   for n in range(len(body))]

    def note(store, key, off, wid, sgn):
        store.setdefault(key, {})
        prev = store[key].get(off)
        if prev and prev != (wid, sgn):
            if prev[0] != wid:
                raise SeedFail("field 0x%x accessed at two widths" % off)
            sgn = prev[1] or sgn
        store[key][off] = (wid, sgn)

    def note_scalar(addr, wid, sgn):
        prev = gscalar.get(addr)
        if prev and prev[0] != wid:
            raise SeedFail("global 0x%08x accessed at two widths" % addr)
        gscalar[addr] = (wid, prev[1] or sgn) if prev else (wid, sgn)

    for k, i in enumerate(body):
        mn = i["mn"]
        if mn == "li":
            regs[i["rd"]] = E("const", k=i["d"])
        elif mn == "mr":
            regs[i["rd"]] = regs.get(i["rs"]) or E("arg", i=i["rs"] - 3)
        elif mn in ("lwz", "lbz", "lhz", "lha"):
            sgn = i["signed"]
            nxt = body[k + 1] if k + 1 < len(body) else None
            if i["width"] == 1:
                sgn = bool(nxt and nxt["mn"] == "extsb" and nxt["rs"] == i["rd"])
            ga = _sda_addr(i, bases)
            if ga is not None:
                if not resolver.in_image(ga):
                    raise SeedFail("small-data load resolves to 0x%08x, which "
                                   "is in no DOL section and not in bss" % ga)
                note_scalar(ga, i["width"], sgn)
                g = E("glob", addr=ga, width=i["width"], signed=sgn)
                if hoist and store_after[k]:
                    nm = "t%d" % len(locals_)
                    locals_.append((nm, CTYPE[(i["width"], sgn)], g))
                    stmts.append(("local", nm, g))
                    g = E("local", name=nm, width=i["width"], signed=sgn)
                regs[i["rd"]] = g
                continue
            base = regs.get(i["ra"])
            if base is None:
                raise SeedFail(LOOP._base_fail("load", i["ra"]))
            if base.kind == "arg":
                used_args.add(base.i)
                ptr_args.add(base.i)
                note(fields, base.i, i["d"], i["width"], sgn)
                regs[i["rd"]] = E("field", i=base.i, off=i["d"],
                                  width=i["width"], signed=sgn)
            elif base.kind == "glob" and base.width == 4:
                note(gfields, base.addr, i["d"], i["width"], sgn)
                regs[i["rd"]] = E("gfield", addr=base.addr, off=i["d"],
                                  width=i["width"], signed=sgn)
            else:
                raise SeedFail("load through a %s expression" % base.kind)
        elif mn in ("extsb", "extsh"):
            src = regs.get(i["rs"])
            if src is None or src.kind not in ("field", "glob", "gfield"):
                raise SeedFail("sign extension of a non-field")
            regs[i["rd"]] = src
        elif mn in ("stw", "stb", "sth"):
            val = regs.get(i["rs"])
            if val is None:
                raise SeedFail("store of an undefined register")
            if val.kind == "arg":
                used_args.add(val.i)
            if val.kind == "field":
                used_args.add(val.i)
            ga = _sda_addr(i, bases)
            if ga is not None:
                if not resolver.in_image(ga):
                    raise SeedFail("small-data store resolves to 0x%08x, which "
                                   "is in no DOL section and not in bss" % ga)
                sgn = val.signed if getattr(val, "width", None) == i["width"] \
                    else True
                note_scalar(ga, i["width"], sgn)
                stmts.append(("gstore", ga, val))
                continue
            base = regs.get(i["ra"])
            if base is None:
                raise SeedFail(LOOP._base_fail("store", i["ra"]))
            sgn = val.signed if val.kind in ("field", "glob", "gfield",
                                             "local") \
                and val.width == i["width"] else True
            if base.kind == "arg":
                used_args.add(base.i)
                ptr_args.add(base.i)
                note(fields, base.i, i["d"], i["width"], sgn)
                stmts.append(("fstore", (base.i, i["d"]), val))
            elif base.kind == "glob" and base.width == 4:
                note(gfields, base.addr, i["d"], i["width"], sgn)
                stmts.append(("gfstore", (base.addr, i["d"]), val))
            else:
                raise SeedFail("store through a %s expression" % base.kind)
        else:
            raise SeedFail("unmodelled instruction: %s" % mn)

    if not (gscalar or gfields):
        raise SeedFail("no small-data reference -- loop.py's own seeder owns "
                       "this shape")

    if guard:
        gi = guard[0] - 3
        if gi < 0 or gi > 7:
            raise SeedFail("guard on a non-argument register")
        used_args.add(gi)
        ptr_args.add(gi)

    ret = regs.get(3)
    returns = ret is not None and ret.kind != "arg"
    if returns and spec.get("void_return"):
        returns = False
    if not stmts and not returns and not guard and body:
        raise SeedFail("no effect")
    if returns and ret.kind == "field":
        used_args.add(ret.i)

    nargs = (max(used_args) + 1) if used_args else 0
    if nargs > 8:
        raise SeedFail("more than eight arguments")

    # ---- render -------------------------------------------------------
    names = {a: resolver.name_for_address(a)
             for a in set(gscalar) | set(gfields)}
    out = []
    for a in sorted(ptr_args):
        out.append(LOOP._struct("S%d" % a, fields.get(a, {}), spec))
        out.append("")
    for ga in sorted(gfields):
        out.append(LOOP._struct("G%08x" % ga, gfields[ga], spec))
        out.append("")
    for ga in sorted(set(gscalar) | set(gfields)):
        if ga in gfields:
            out.append("extern G%08x *%s;" % (ga, names[ga]))
        else:
            wid, sgn = gscalar[ga]
            ty = spec.get("gtype", {}).get(ga) or CTYPE[(wid, sgn)]
            out.append("extern %s %s;" % (ty, names[ga]))
    out.append("")

    params = []
    for a in range(nargs):
        params.append(("S%d *p%d" % (a, a)) if a in ptr_args
                      else ("%s p%d" % (spec.get("argtype", "int"), a)))
    rt = "void"
    if returns:
        if ret.kind in ("glob", "gfield", "local"):
            rt = spec.get("rettype") or CTYPE[(ret.width, ret.signed)]
        else:
            rt = spec.get("rettype") or "int"
    out.append("%s f(%s)" % (rt, ", ".join(params) if params else "void"))
    out.append("{")
    for nm, ty, _e in locals_:
        out.append("    %s %s;" % (ty, nm))
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
    for kind, key, val in stmts:
        if kind == "local":
            out.append("    %s = %s;" % (key, val.c(names)))
        elif kind == "gstore":
            out.append("    %s = %s;" % (names[key], val.c(names)))
        elif kind == "gfstore":
            ga, off = key
            out.append("    %s->%s = %s;"
                       % (names[ga], LOOP._fname(off), val.c(names)))
        else:
            ai, off = key
            out.append("    p%d->%s = %s;"
                       % (ai, LOOP._fname(off), val.c(names)))
    if returns:
        out.append("    return %s;" % ret.c(names))
    out.append("}")
    return "\n".join(out) + "\n", sorted(set(gscalar) | set(gfields))


# ---------------------------------------------------------------------------
# spec variants -- the same bounded idea as loop.py's permuter
# ---------------------------------------------------------------------------

def variants(rec, retail, smap, bases, resolver, limit=24):
    """Yield (spec_label, csrc, globals) candidates, most likely first."""
    seen = set()
    base_src, globs = seed_leaf_sda(rec, retail, smap, bases, resolver, {})
    yield "plain", base_src, globs
    seen.add(base_src)
    specs = [("hoist", {"hoist": True}),
             ("void-return", {"void_return": True}),
             ("hoist+void-return", {"hoist": True, "void_return": True})]
    for rt in ("int", "unsigned int", "void"):
        specs.append(("rettype=%s" % rt, {"rettype": rt}))
    for at in ("unsigned int", "void *"):
        specs.append(("argtype=%s" % at, {"argtype": at}))
    for g in ("not", "null"):
        specs.append(("guard=%s" % g, {"guard": g}))
    for label, sp in specs[:limit]:
        try:
            s, gs = seed_leaf_sda(rec, retail, smap, bases, resolver, sp)
        except SeedFail:
            continue
        if s in seen:
            continue
        seen.add(s)
        yield label, s, gs


# ---------------------------------------------------------------------------
# driving the oracle
# ---------------------------------------------------------------------------

class Oracle(object):
    def __init__(self, repo):
        self.dol, self.smap = load(repo=repo)
        self.bases = datareloc.bases_only(self.dol, self.smap)
        self.resolver = datareloc.SymbolResolver(self.dol, self.smap, repo=repo)
        self.kind, self.compiler = MATCH.pick_backend("mwcc-rs")
        self.cflags = MATCH.DEFAULT_CFLAGS_RS
        self.build = MATCH.DEFAULT_BUILD
        self.work = Path(tempfile.mkdtemp(prefix="sdarec_"))
        self.compiles = 0

    def check(self, rec, retail, csrc):
        src = self.work / "cand.c"
        src.write_text(csrc)
        obj, log, _cmd = MATCH.compile_candidate(
            src.resolve(), self.compiler, self.cflags, [], str(self.work),
            kind="mwcc-rs", build=self.build)
        self.compiles += 1
        if obj is None:
            return {"verdict": "BUILD_FAILED", "match_pct": 0.0,
                    "compiler_log": log[-600:]}
        e = Elf32BE(obj.read_bytes())
        cand = e.data(e.section(".text"))
        relocs = e.relocs_for(".text")
        for sy in e.symbols():
            if sy["name"] == "f" and sy["size"]:
                cand = cand[sy["value"]:sy["value"] + sy["size"]]
                relocs = [(o - sy["value"], t, n, ad) for o, t, n, ad in relocs
                          if sy["value"] <= o < sy["value"] + sy["size"]]
                break
        exp = MATCH.expected_symbols(self.smap, retail, rec["addr"])
        expd = MATCH.expected_data(self.dol, self.smap, retail, rec["addr"])
        v = compare(retail, cand, relocs, rec["addr"], expected_syms=exp,
                    retail_addrs=expd, resolve_symbol=self.resolver)
        return v


# ---------------------------------------------------------------------------
# the refused set
# ---------------------------------------------------------------------------

SDA_REFUSAL = re.compile(r"through r(?:2 \(sdata2\)|13 \(sdata\))")


def refused_set(dol, smap):
    """Every function `loop.seed_leaf` refuses for small-data access.

    This is the 104 of `docs/matching-loop.md` s5.1, recomputed rather than
    quoted, so the number in the report is measured.
    """
    out = []
    for rec in smap.text_functions():
        b = dol.read(rec["addr"], rec["size"])
        if b is None:
            continue
        try:
            LOOP.seed_leaf(rec, b, smap)
        except SeedFail as ex:
            if SDA_REFUSAL.search(str(ex)):
                out.append((rec, b, str(ex)))
        except Exception:
            continue
    return out


# ---------------------------------------------------------------------------
# recording
# ---------------------------------------------------------------------------

PROV = " * DATA-RELOCATION VERIFICATION (datareloc.py)"


def add_provenance(entry, v, globals_used, resolver):
    """Add the data-relocation evidence to the recorded .c header and registry.

    `loop.record_match` writes the standard provenance block; this appends the
    facts that make THIS class of match verifiable at all -- the small-data
    bases, and for every data relocation the address the retail bytes name and
    the symbol the candidate used.  `loop.py` itself is not modified.
    """
    p = LOOP.SRC_MATCH / entry["src"]
    text = p.read_text()
    rows = []
    for r in v.get("data_relocs_verified") or []:
        rows.append(" *   +0x%03x %-16s %-24s retail %s  (%s, via %s)"
                    % (r["offset"], r["type"], r["symbol"], r["retail_addr"],
                       r["retail_how"], r["symbol_source"]))
    text = text.replace(
        " * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.",
        " * PROVENANCE -- produced by "
        "research/tools/matching-decomp/sda_recover.py,\n"
        " * recorded through loop.py's record_match.", 1)
    block = [PROV + " -- every data relocation below was",
             " * checked against the address the RETAIL encoding names, not "
             "merely masked:"]
    block += rows
    block += [" * _SDA_BASE_ (r13) = 0x%08x, _SDA2_BASE_ (r2) = 0x%08x, "
              "derived from" % (v["_bases"][13], v["_bases"][2]),
              " * __init_registers and cross-checked against the DOL section "
              "table."]
    marker = " * Re-proved by src-match/verify.py"
    text = text.replace(marker, "\n".join(block) + "\n" + marker, 1)
    p.write_text(text)

    entry["produced_by"] = "sda_recover.py"
    entry["data_relocs_verified"] = [
        {"offset": "0x%03x" % r["offset"], "type": r["type"],
         "symbol": r["symbol"], "retail_addr": r["retail_addr"],
         "retail_how": r["retail_how"], "symbol_source": r["symbol_source"]}
        for r in (v.get("data_relocs_verified") or [])]
    entry["globals"] = ["%s @ 0x%08x" % (resolver.name_for_address(a), a)
                        for a in globals_used]
    reg_path = LOOP.SRC_MATCH / "matched.json"
    reg = json.loads(reg_path.read_text())
    for i, e in enumerate(reg["functions"]):
        if e["name"] == entry["name"]:
            reg["functions"][i] = entry
            break
    reg_path.write_text(json.dumps(reg, indent=1) + "\n")


# ---------------------------------------------------------------------------

def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--repo", default=str(datareloc.REPO_DEFAULT))
    ap.add_argument("--list", action="store_true")
    ap.add_argument("--dry-run", action="store_true")
    ap.add_argument("--record", action="store_true")
    ap.add_argument("--function", action="append", default=[])
    ap.add_argument("--json")
    a = ap.parse_args()

    orc = Oracle(a.repo)
    if orc.compiler is None and not a.list:
        print("no mwcc-rs backend; nothing can be proved", file=sys.stderr)
        return 3

    if a.function:
        targets = []
        for n in a.function:
            rec, b = function_bytes(orc.dol, orc.smap, n)
            targets.append((rec, b, "explicit"))
    else:
        targets = refused_set(orc.dol, orc.smap)

    print("SMALL-DATA RECOVERY  targets=%d  (loop.seed_leaf refuses each for "
          "r2/r13 access)" % len(targets))
    print("_SDA_BASE_ (r13) = 0x%08x   _SDA2_BASE_ (r2) = 0x%08x"
          % (orc.bases[13], orc.bases[2]))
    print("-" * 78)
    if a.list:
        for rec, _b, why in targets:
            print("  %-26s 0x%08x %3d insns  %s"
                  % (rec["name"], rec["addr"], rec["size"] // 4, why))
        return 0

    t0 = time.time()
    rows = []
    counts = {}
    for rec, retail, _why in targets:
        row = {"function": rec["name"], "addr": "0x%08x" % rec["addr"],
               "insns": rec["size"] // 4}
        best = None
        try:
            for label, src, globs in variants(rec, retail, orc.smap,
                                              orc.bases, orc.resolver):
                v = orc.check(rec, retail, src)
                if best is None or v.get("match_pct", 0) > best[2].get(
                        "match_pct", 0):
                    best = (label, src, v, globs)
                if v["verdict"] == "MATCH":
                    best = (label, src, v, globs)
                    break
        except SeedFail as ex:
            row["outcome"] = "NO_SEED"
            row["reason"] = str(ex)
            counts["NO_SEED"] = counts.get("NO_SEED", 0) + 1
            rows.append(row)
            continue
        if best is None:
            row["outcome"] = "NO_SEED"
            row["reason"] = "no variant produced C"
            counts["NO_SEED"] = counts.get("NO_SEED", 0) + 1
            rows.append(row)
            continue
        label, src, v, globs = best
        row["outcome"] = v["verdict"]
        row["variant"] = label
        row["match_pct"] = v.get("match_pct", 0.0)
        row["globals"] = ["0x%08x" % g for g in globs]
        if v["verdict"] == "MATCH":
            row["verified_relocs"] = len(v.get("data_relocs_verified") or [])
        elif v["verdict"] == "MATCH_UNVERIFIED":
            row["reason"] = v.get("unverified_reason")
        elif v.get("first_diff"):
            row["first_diff"] = "%s: retail %s | cand %s" % (
                v["first_diff"]["addr"], v["first_diff"]["retail"],
                v["first_diff"]["cand"])
        counts[v["verdict"]] = counts.get(v["verdict"], 0) + 1
        rows.append(row)

        if a.record and v["verdict"] == "MATCH":
            meta = {"seed": "sda-leaf (small-data globals, data relocations "
                            "address-checked by datareloc.py)",
                    "iterations": 1, "model_calls": 0, "permuter_steps": 0,
                    "shape": LOOP.shape_of(retail, rec["addr"]),
                    "exact_bytes": v["exact_bytes"]}
            entry = LOOP.record_match(rec, retail, src, meta)
            if entry is not None:
                v["_bases"] = orc.bases
                add_provenance(entry, v, globs, orc.resolver)
                row["recorded"] = entry["src"]

    print("%-26s %-6s %-18s %s" % ("function", "insns", "outcome", "detail"))
    for r in rows:
        det = r.get("recorded") or r.get("first_diff") or r.get("reason") or ""
        print("%-26s %-6d %-18s %s" % (r["function"], r["insns"],
                                       r["outcome"], det[:70]))
    print("-" * 78)
    tot = 0
    for k in sorted(counts):
        print("  %-20s %4d" % (k, counts[k]))
        tot += counts[k]
    print("  %-20s %4d   compiles=%d  wall=%.1fs"
          % ("TOTAL", tot, orc.compiles, time.time() - t0))
    if a.json:
        Path(a.json).write_text(json.dumps(
            {"bases": {"r2": "0x%08x" % orc.bases[2],
                       "r13": "0x%08x" % orc.bases[13]},
             "counts": counts, "rows": rows}, indent=1))
    return 0


if __name__ == "__main__":
    sys.exit(main())
