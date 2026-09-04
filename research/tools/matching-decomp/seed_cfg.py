#!/usr/bin/env python3
"""seed_cfg.py -- the CONTROL-FLOW seeder tier for the matching loop.

`loop.py`'s first three seeders lift only straight-line leaves: a bare `blr`, a
one-call wrapper, and a straight-line expression evaluator.  The loop's own
measurement said what that costs: of 5,492 unmatched functions, **5,477 never
reached the compiler at all**, and its conclusion was that a better seeder --
not a better model -- moves them.  This is that seeder.

WHAT IT ADDS
    * a basic-block CFG built from the retail encodings (blocks, edges,
      dominators, back edges);
    * STRUCTURING: `if` / `if-else`, early `return`, and `&&` / `||`
      short-circuit chains recovered from the branch graph and emitted as
      structured C -- never `goto`, because MWCC's codegen for a `goto` is not
      its codegen for an `if`, and a `goto` candidate cannot match;
    * a symbolic evaluator that crosses `bl` boundaries: the argument
      registers the function WROTE become the call's arguments (r3-r10, or
      f1-f8 for an all-float call), r3 carries the result back, the callee is
      named from the link map, and the volatile registers are killed at every
      call the way the EABI says they are.  A call that mixes GPR and FPR
      arguments is refused: their interleaving in the C argument list is not
      recoverable from the registers alone.

WHAT IT REFUSES, AND WHY THE REFUSALS ARE THE POINT
    Every refusal names its own reason and is tagged with one of the three
    classes in `seed_cfg.REFUSALS`, so `loop.py run` can split the corpus-wide
    remainder into "the compiler lane's queue" and "this seeder's queue":

      integrity  r13/r2 small data, and any global whose address would need an
                 R_PPC_ADDR16_HA/LO or R_PPC_EMB_SDA21 relocation.  `match.py`
                 name-checks only R_PPC_REL24, so such a match is vacuous --
                 it would accept any global in the game.  This tier inherits
                 that refusal unchanged (loop.py s2.3); another lane owns
                 making those verifiable.
      compiler   a shape mwcc-rs is known to refuse -- measured, not assumed:
                 every loop form (`while`, `for`, `do`) returns
                 "loop codegen is not implemented yet (roadmap)".  Refusing
                 here costs nothing the compiler would not have cost anyway,
                 and it keeps those functions in the COMPILER lane's queue
                 rather than this one's.
      seeder     this tier's own envelope: an opcode it does not model, an
                 unstructured graph, a value that would need a local variable.

    Nothing here decides a match.  The oracle in `loop.py` does, byte for
    byte, and a candidate this file writes is worth exactly what the oracle
    says it is worth.

TYPE NARROWING (the `undefined8` finding, folded in)
    The compiler census (docs/matching-compiler-census.md s2a) measured that
    683 functions refused for "this long long shape is not modeled yet" compile
    once Ghidra's `undefined8` placeholder is narrowed to 32 bits -- that is a
    typing artefact, not a 64-bit value.  This seeder never reads Ghidra's
    types, so it cannot inherit that bug; it derives every width from the
    retail encoding (`lwz` is 4, `lbz` is 1, ...).  `narrow_undefined8()` is
    provided for the Ghidra-seeded path and applies the same rule with the same
    evidence: a value the retail bytes only ever move through 32-bit register
    ops is 32-bit.  See `NARROW_EVIDENCE`.
"""
from __future__ import annotations

import collections
import re
import struct
import sys
from pathlib import Path

HERE = Path(__file__).resolve().parent
if str(HERE) not in sys.path:
    sys.path.insert(0, str(HERE))

from ppcdis import disasm_word                                  # noqa: E402

try:
    import datareloc as DR                                      # noqa: E402
except ImportError:                                             # pragma: no cover
    DR = None

# One resolver and one pair of SDA bases per link map -- both parse files, and
# this seeder runs 5,000 times per corpus sweep.
_DOL = []


def _dol():
    """The retail DOL, loaded once per process.  The seeder contract passes
    only the link map, and naming a global needs the image as well (to check
    that an address lands in a real section)."""
    if not _DOL:
        from dolsym import load
        _DOL.append(load()[0])
    return _DOL[0]


def resolver_for(smap):
    """(SymbolResolver, {2: sda2, 13: sda}), or (None, None) when `datareloc`
    is absent -- in which case every global access refuses by name, exactly as
    this tier behaved before that module existed.

    The cache hangs off the map object itself.  Keying it by `id()` would be a
    latent bug: a short-lived map is collected and the next one can be handed
    the same id, so a failure cached against a throwaway would be served to a
    real map.
    """
    if DR is None:
        return None, None
    hit = getattr(smap, "_seed_cfg_resolver", None)
    if hit is None:
        try:
            dol = _dol()
            hit = (DR.SymbolResolver(dol, smap), DR.bases_only(dol, smap))
        except Exception:                                       # noqa: BLE001
            hit = (None, None)
        try:
            smap._seed_cfg_resolver = hit
        except AttributeError:                                  # pragma: no cover
            pass
    return hit


class SeedFail(Exception):
    """Raised with `.cls` in {'integrity', 'compiler', 'seeder'}."""
    cls = "seeder"


def _fail(cls, msg):
    e = SeedFail(msg)
    e.cls = cls
    return e


# ---------------------------------------------------------------------------
# 1. decode -- wide enough for the reachable envelope, and honest outside it
# ---------------------------------------------------------------------------

def _s16(v):
    return v - 0x10000 if v & 0x8000 else v


# op 31 XO -> (mnemonic, arity kind).  'rr' is rA <- rS op rB (or-form),
# 'dd' is rD <- rA op rB (add-form), 'ext' is rA <- ext(rS).
X31 = {
    266: ("add", "dd"), 40: ("subf", "dd"), 235: ("mullw", "dd"),
    104: ("neg", "d1"), 24: ("slw", "rr"), 536: ("srw", "rr"),
    792: ("sraw", "rr"), 824: ("srawi", "sh"), 28: ("and", "rr"),
    444: ("or", "rr"), 316: ("xor", "rr"), 60: ("andc", "rr"),
    124: ("nor", "rr"), 954: ("extsb", "ext"), 922: ("extsh", "ext"),
    26: ("cntlzw", "ext"),
    23: ("lwzx", "ldx"), 87: ("lbzx", "ldx"), 279: ("lhzx", "ldx"),
    343: ("lhax", "ldx"),
    151: ("stwx", "stx"), 215: ("stbx", "stx"), 407: ("sthx", "stx"),
    0: ("cmpw", "cmp"), 32: ("cmplw", "cmp"),
    339: ("mfspr", "spr"), 467: ("mtspr", "spr"),
    535: ("fsx", "ldx"), 663: ("fstx", "stx"),
}

# CR-logical forms.  MWCC emits these for the float `<=` / `>=` idiom
# (`fcmpo` then `cror cr0eq, cr0gt, cr0eq` then `bne`), so a seeder that does
# not model them cannot express any float relational operator.
CROPS = {33: "crnor", 129: "crandc", 193: "crxor", 225: "crnand",
         257: "crand", 289: "creqv", 417: "crorc", 449: "cror"}

LOADS = {32: ("lwz", 4, True, "i"), 34: ("lbz", 1, False, "i"),
         40: ("lhz", 2, False, "i"), 42: ("lha", 2, True, "i"),
         48: ("lfs", 4, None, "f"), 50: ("lfd", 8, None, "f")}
STORES = {36: ("stw", 4, "i"), 38: ("stb", 1, "i"), 44: ("sth", 2, "i"),
          52: ("stfs", 4, "f"), 54: ("stfd", 8, "f")}

A63 = {72: "fmr", 40: "fneg"}
A63_5 = {21: "fadd", 20: "fsub", 25: "fmul", 18: "fdiv"}
A59_5 = {21: "fadds", 20: "fsubs", 25: "fmuls", 18: "fdivs"}


def decode(w, addr=0):
    """Structured decode.  Returns None for anything this tier does not model,
    which is how an out-of-envelope function is refused instead of guessed."""
    op = w >> 26
    rd = (w >> 21) & 31
    ra = (w >> 16) & 31
    rb = (w >> 11) & 31
    d = _s16(w & 0xFFFF)
    u = w & 0xFFFF
    xo = (w >> 1) & 0x3FF
    xo5 = (w >> 1) & 0x1F
    if w == 0x60000000:
        return {"mn": "nop"}
    if op in LOADS:
        mn, wid, sgn, k = LOADS[op]
        return {"mn": mn, "rd": rd, "ra": ra, "d": d, "width": wid,
                "signed": sgn, "kind": k}
    if op in STORES:
        mn, wid, k = STORES[op]
        return {"mn": mn, "rs": rd, "ra": ra, "d": d, "width": wid, "kind": k}
    if op == 37:
        return {"mn": "stwu", "rs": rd, "ra": ra, "d": d}
    if op == 14:
        return {"mn": "li" if ra == 0 else "addi", "rd": rd, "ra": ra, "d": d}
    if op == 15:
        return {"mn": "lis" if ra == 0 else "addis", "rd": rd, "ra": ra, "d": d}
    if op == 7:
        return {"mn": "mulli", "rd": rd, "ra": ra, "d": d}
    if op == 12:
        return {"mn": "addic", "rd": rd, "ra": ra, "d": d}
    if op == 13:
        return {"mn": "addic.", "rd": rd, "ra": ra, "d": d, "rc": True}
    if op == 8:
        return {"mn": "subfic", "rd": rd, "ra": ra, "d": d}
    if op == 24:
        return {"mn": "ori", "rd": ra, "rs": rd, "u": u}
    if op == 26:
        return {"mn": "xori", "rd": ra, "rs": rd, "u": u}
    if op == 25:
        return {"mn": "oris", "rd": ra, "rs": rd, "u": u}
    if op == 28:
        return {"mn": "andi.", "rd": ra, "rs": rd, "u": u, "rc": True}
    if op == 46:
        return {"mn": "lmw", "rd": rd, "ra": ra, "d": d}
    if op == 47:
        return {"mn": "stmw", "rs": rd, "ra": ra, "d": d}
    if op == 10:
        return {"mn": "cmplwi", "ra": ra, "u": u, "crf": rd >> 2, "signed": False}
    if op == 11:
        return {"mn": "cmpwi", "ra": ra, "d": d, "crf": rd >> 2, "signed": True}
    if op == 21:                                    # rlwinm
        sh, mb, me = (w >> 11) & 31, (w >> 6) & 31, (w >> 1) & 31
        return {"mn": "rlwinm", "rd": ra, "rs": rd, "sh": sh, "mb": mb,
                "me": me, "rc": bool(w & 1)}
    if op == 18:
        li = w & 0x03FFFFFC
        if li & 0x02000000:
            li -= 0x04000000
        return {"mn": "bl" if (w & 1) else "b", "li": li,
                "aa": bool(w & 2), "target": addr + (0 if (w & 2) else li)
                if not (w & 2) else li}
    if op == 16:
        bd = _s16(w & 0xFFFC)
        return {"mn": "bc", "bo": rd, "bi": ra, "bd": bd, "lk": bool(w & 1),
                "target": addr + bd}
    if op == 19:
        if xo == 16:
            return {"mn": "bclr", "bo": rd, "bi": ra, "lk": bool(w & 1)}
        if xo == 528:
            return {"mn": "bcctr", "bo": rd, "bi": ra, "lk": bool(w & 1)}
        if xo in CROPS:
            return {"mn": CROPS[xo], "bt": rd, "ba": ra, "bb": rb}
        return None
    if op == 31:
        ent = X31.get(xo)
        if ent is None:
            return None
        mn, kind = ent
        r = {"mn": mn, "kind": kind, "rc": bool(w & 1), "xo": xo}
        if kind == "dd":
            r.update(rd=rd, ra=ra, rb=rb)
        elif kind == "d1":
            r.update(rd=rd, ra=ra)
        elif kind == "rr":
            r.update(rd=ra, rs=rd, rb=rb)
            if mn == "or" and rd == rb:
                r["mn"] = "mr"
        elif kind == "ext":
            r.update(rd=ra, rs=rd)
        elif kind == "sh":
            r.update(rd=ra, rs=rd, sh=rb)
        elif kind in ("ldx", "stx"):
            r.update(rd=rd, rs=rd, ra=ra, rb=rb)
        elif kind == "cmp":
            r.update(ra=ra, rb=rb, crf=rd >> 2, signed=(mn == "cmpw"))
        elif kind == "spr":
            spr = ((w >> 16) & 31) | (((w >> 11) & 31) << 5)
            if spr == 8:
                r["mn"] = "mflr" if mn == "mfspr" else "mtlr"
            elif spr == 9:
                r["mn"] = "mfctr" if mn == "mfspr" else "mtctr"
            else:
                return None
            r.update(rd=rd)
        return r
    if op == 59 and xo5 in A59_5:
        return {"mn": A59_5[xo5], "kind": "fa", "fd": rd, "fa": ra,
                "fb": rb, "fc": (w >> 6) & 31}
    if op == 63:
        if xo in A63:
            return {"mn": A63[xo], "kind": "fx", "fd": rd, "fb": rb}
        if xo in (0, 32):
            return {"mn": "fcmpu" if xo == 0 else "fcmpo", "kind": "fcmp",
                    "crf": rd >> 2, "fa": ra, "fb": rb}
        if xo5 in A63_5:
            return {"mn": A63_5[xo5], "kind": "fa", "fd": rd, "fa": ra,
                    "fb": rb, "fc": (w >> 6) & 31}
        return None
    return None


def mnemonic(w):
    return disasm_word(w, 0).split()[0]


# ---------------------------------------------------------------------------
# 2. the CFG
# ---------------------------------------------------------------------------

class Block(object):
    __slots__ = ("addr", "end", "ins", "succ", "pred", "term", "idx")

    def __init__(self, addr):
        self.addr = addr
        self.end = addr
        self.ins = []          # [(addr, word, decoded)]
        self.succ = []
        self.pred = []
        self.term = None       # decoded terminator, or None for fallthrough
        self.idx = -1

    def __repr__(self):
        return "<blk %08x..%08x>" % (self.addr, self.end)


def build_cfg(retail, base):
    """Basic blocks over one function's retail bytes.

    Leaders are the entry, every branch target inside the function, and the
    instruction after every branch.  A branch that leaves the function's own
    extent is a hard refusal -- this tier does not model tail jumps into
    another function.
    """
    n = len(retail) // 4
    words = struct.unpack(">%dI" % n, retail[:n * 4])
    dec = []
    for i, w in enumerate(words):
        a = base + 4 * i
        d = decode(w, a)
        if d is None:
            raise _fail("seeder", "undecoded instruction %s @ 0x%08x"
                        % (mnemonic(w), a))
        dec.append((a, w, d))

    lo, hi = base, base + 4 * n
    leaders = {base}
    for i, (a, _w, d) in enumerate(dec):
        mn = d["mn"]
        if mn in ("b", "bc"):
            t = d["target"]
            if not (lo <= t < hi):
                raise _fail("seeder",
                            "branch to 0x%08x leaves the function extent" % t)
            leaders.add(t)
            if i + 1 < n:
                leaders.add(a + 4)
        elif mn == "bclr" or (mn == "bcctr" and not d["lk"]):
            if i + 1 < n:
                leaders.add(a + 4)
    order = sorted(leaders)
    blocks = []
    for j, s in enumerate(order):
        e = order[j + 1] if j + 1 < len(order) else hi
        b = Block(s)
        b.end = e
        b.idx = j
        b.ins = [t for t in dec if s <= t[0] < e]
        blocks.append(b)
    by_addr = {b.addr: b for b in blocks}

    for j, b in enumerate(blocks):
        last = b.ins[-1][2]
        mn = last["mn"]
        nxt = blocks[j + 1] if j + 1 < len(blocks) else None
        if mn == "b":
            b.term = last
            b.succ = [by_addr[last["target"]]]
        elif mn == "bc":
            b.term = last
            tgt = by_addr[last["target"]]
            b.succ = [tgt] + ([nxt] if nxt else [])
        elif mn == "bclr":
            b.term = last
            if last["bo"] & 0x14 == 0x14:          # unconditional blr
                b.succ = []
            else:
                b.succ = [nxt] if nxt else []
        elif mn == "bcctr" and not last["lk"]:
            b.term = last
            b.succ = []
        else:
            b.term = None
            b.succ = [nxt] if nxt else []
        for s in b.succ:
            s.pred.append(b)

    # A block that is not reachable from the entry means the link map's extent
    # covers more than one function -- the map records a SYMBOL's span, and
    # several `zz_`/`def_` symbols in this map cover a run of them.  Lifting
    # such an extent would produce C for the first function and silently drop
    # the rest, so it is refused by name.
    seen = set()
    stack = [blocks[0]]
    while stack:
        b = stack.pop()
        if b.idx in seen:
            continue
        seen.add(b.idx)
        stack.extend(b.succ)
    if len(seen) != len(blocks):
        raise _fail("seeder",
                    "%d of %d blocks are unreachable from the entry: this map "
                    "symbol spans more than one function"
                    % (len(blocks) - len(seen), len(blocks)))
    return blocks, by_addr


def dominators(blocks):
    """Classic iterative dominator sets, keyed by block index."""
    n = len(blocks)
    allb = set(range(n))
    dom = {0: {0}}
    for i in range(1, n):
        dom[i] = set(allb)
    changed = True
    while changed:
        changed = False
        for i in range(1, n):
            preds = [p.idx for p in blocks[i].pred]
            if not preds:
                new = {i}
            else:
                new = set(allb)
                for p in preds:
                    new &= dom[p]
                new |= {i}
            if new != dom[i]:
                dom[i] = new
                changed = True
    return dom


def back_edges(blocks, dom):
    """(tail, head) pairs where head dominates tail -- a natural loop."""
    out = []
    for b in blocks:
        for s in b.succ:
            if s.idx in dom[b.idx]:
                out.append((b, s))
    return out


# ---------------------------------------------------------------------------
# 3. expressions
# ---------------------------------------------------------------------------

CTYPE = {(1, True): "char", (1, False): "unsigned char",
         (2, True): "short", (2, False): "unsigned short",
         (4, True): "int", (4, False): "unsigned int"}
FTYPE = {4: "float", 8: "double"}


class E(object):
    """An expression tree.  `k` is the node kind; children in `a`."""
    __slots__ = ("k", "a")

    def __init__(self, k, *a):
        self.k = k
        self.a = a

    def __repr__(self):
        return "E(%s,%r)" % (self.k, self.a)


def Const(v):
    return E("const", v)


def Arg(i):
    return E("arg", i)


def Field(base, off, width, signed, kind):
    return E("field", base, off, width, signed, kind)


def Call(name, args, fkind):
    return E("call", name, tuple(args), fkind)


def Bin(op, a, b):
    return E("bin", op, a, b)


def Un(op, a):
    return E("un", op, a)


def Cmp(op, a, b, signed):
    return E("cmp", op, a, b, signed)


def Logic(op, parts):
    return E("logic", op, tuple(parts))


PREC = {"||": 1, "&&": 2, "|": 3, "^": 4, "&": 5,
        "==": 6, "!=": 6, "<": 7, "<=": 7, ">": 7, ">=": 7,
        "<<": 8, ">>": 8, "+": 9, "-": 9, "*": 10, "/": 10, "%": 10}


def _lit(v):
    if isinstance(v, float):
        s = repr(v)
        return s + "f" if s.endswith(("0", "1", "2", "3", "4", "5", "6", "7",
                                      "8", "9")) and "." in s else s
    if 0 <= v < 10:
        return str(v)
    if v < 0:
        return str(v)
    return "0x%x" % v


def render(e, names, prec=0):
    """Expression -> C text.  `names` maps a base expression to its C name."""
    k = e.k
    if k == "const":
        return _lit(e.a[0])
    if k == "arg":
        return "p%d" % e.a[0]
    if k == "field":
        base = e.a[0]
        if base.k == "gaddr":
            return "%s.%s" % (names["g", base.a[0]], _fname(e.a[1]))
        return "%s->%s" % (render(base, names, 12), _fname(e.a[1]))
    if k == "gvar":
        # An absolutely-addressed global is declared as an object bigger than
        # the small-data threshold, so its value lives in a member.
        return e.a[1] if e.a[2] == "sda" else (e.a[1] + ".v")
    if k == "gaddr":
        return "&%s" % names["g", e.a[0]]
    if k == "call":
        return "%s(%s)" % (e.a[0], ", ".join(render(x, names) for x in e.a[1]))
    if k == "icall":
        return "%s(%s)" % (render(e.a[0], names, 12),
                           ", ".join(render(x, names) for x in e.a[1]))
    if k == "un":
        return "%s%s" % (e.a[0], render(e.a[1], names, 11))
    if k == "cast":
        return "(%s)%s" % (e.a[0], render(e.a[1], names, 11))
    if k in ("bin", "cmp"):
        op = e.a[0]
        p = PREC[op]
        s = "%s %s %s" % (render(e.a[1], names, p), op,
                          render(e.a[2], names, p + 1))
        return "(%s)" % s if p < prec else s
    if k == "logic":
        op = e.a[0]
        p = PREC[op]
        s = (" %s " % op).join(render(x, names, p + 1) for x in e.a[1])
        return "(%s)" % s if p < prec else s
    raise _fail("seeder", "unrenderable expression %s" % k)


def _fname(off):
    return "field_%x" % off


def negate(c):
    """Logical negation, pushed into the leaves so no `!` survives."""
    INV = {"==": "!=", "!=": "==", "<": ">=", ">=": "<", ">": "<=", "<=": ">"}
    if c.k == "cmp":
        return Cmp(INV[c.a[0]], c.a[1], c.a[2], c.a[3])
    if c.k == "logic":
        op = "&&" if c.a[0] == "||" else "||"
        return Logic(op, [negate(x) for x in c.a[1]])
    return Un("!", c)


# ---------------------------------------------------------------------------
# 4. the lifter
# ---------------------------------------------------------------------------

VOLATILE_GPR = set([0] + list(range(3, 13)))
VOLATILE_FPR = set(range(0, 14))
ARG_GPR = list(range(3, 11))
ARG_FPR = list(range(1, 9))


class RegFile(dict):
    """A register file that remembers which registers have been WRITTEN since
    the last call boundary.

    That set is what states a callee's arity, and getting it wrong is the
    difference between `g(p0->x)` and `g(p0->x, p1, p2, p3, p4, p5, p6, p7)`.
    At entry r3..r10 all hold an argument, so "which registers hold a value"
    says nothing; "which registers this function just set up" says everything,
    because MWCC materialises exactly the arguments the call has.  A register
    below the high-water mark that was NOT written is a pass-through argument
    and keeps the value it came in with.
    """

    def __init__(self, *a, **k):
        dict.__init__(self, *a, **k)
        self.dirty = set()

    def __setitem__(self, k, v):
        dict.__setitem__(self, k, v)
        if isinstance(k, int):
            self.dirty.add(k)

    def quiet(self, k, v):
        dict.__setitem__(self, k, v)

    def copy(self):
        r = RegFile(self)
        r.dirty = set(self.dirty)
        return r


class Stmt(object):
    __slots__ = ("k", "a")

    def __init__(self, k, *a):
        self.k = k
        self.a = a


def _c_ident(name):
    return bool(re.match(r"^[A-Za-z_][A-Za-z0-9_]*$", name))


class Lifter(object):
    def __init__(self, rec, retail, smap, spec=None):
        self.rec = rec
        self.retail = retail
        self.smap = smap
        self.spec = spec or {}
        self.base = rec["addr"]
        self.blocks, self.by_addr = build_cfg(retail, self.base)
        self.dom = dominators(self.blocks)
        self.loops = back_edges(self.blocks, self.dom)
        # struct model: base-expression key -> {offset: (width, signed, kind)}
        self.structs = collections.OrderedDict()
        self.globals = {}          # absolute address -> (width, signed, kind,
                                   #                     address-taken)
        self.ptr_args = set()
        self.used_args = set()
        self.calls = []
        self.spent = set()
        self.fptr_fields = {}
        self.fp_args = set()
        self.returns_value = None
        self.nonvoid_kind = None
        self.frame = None
        self.pending = None       # a call statement not yet flushed

    # -- struct bookkeeping -------------------------------------------------

    def _skey(self, base):
        if base.k == "gaddr":
            return ("gbl", base.a[0])
        if base.k == "arg":
            return ("arg", base.a[0])
        if base.k == "field":
            return ("fld", self._skey(base.a[0]), base.a[1])
        raise _fail("seeder", "pointer base is not an argument or a field")

    def note_field(self, base, off, width, signed, kind):
        key = self._skey(base)
        d = self.structs.setdefault(key, {})
        prev = d.get(off)
        if prev is not None:
            pw, ps, pk = prev
            if pw != width or pk != kind:
                raise _fail("seeder",
                            "field 0x%x accessed as %s%d and %s%d"
                            % (off, pk, width, kind, width))
            signed = ps or signed
        d[off] = (width, signed, kind)
        if base.k == "arg":
            self.ptr_args.add(base.a[0])
            self.used_args.add(base.a[0])

    # -- register file ------------------------------------------------------

    def entry_state(self):
        """r3..r10 hold this function's arguments.  The FPRs are deliberately
        left EMPTY: an unwritten f1 read as a value means the function takes a
        floating-point parameter, and the position of an FP parameter in the C
        argument list is not recoverable from the registers, so reading one
        refuses by name rather than guessing an arity."""
        g = RegFile()
        for i, r in enumerate(ARG_GPR):
            g.quiet(r, Arg(i))
        return {"g": g, "f": {}, "cr": {}}

    def use_arg(self, e):
        """Record every parameter an expression mentions.

        This has to run over CONDITIONS as well as values: a parameter that
        appears only in an `if` is still a parameter, and forgetting it emits C
        that names `p1` in a function declared with one argument.
        """
        if not isinstance(e, E):
            return
        if e.k == "arg":
            self.used_args.add(e.a[0])
            return
        for x in e.a:
            if isinstance(x, E):
                self.use_arg(x)
            elif isinstance(x, (tuple, list)):
                for y in x:
                    self.use_arg(y)

    # -- the linear walk ----------------------------------------------------

    def lift_block(self, blk, st, stmts):
        """Execute one block's non-terminator instructions."""
        ins = list(blk.ins)
        if blk.term is not None:
            ins = ins[:-1]
        g, f, cr = st["g"], st["f"], st["cr"]

        for idx, (a, _w, d) in enumerate(ins):
            mn = d["mn"]
            if mn == "nop":
                continue

            # ---- frame ----------------------------------------------------
            if mn == "stwu" and d["ra"] == 1 and d["rs"] == 1:
                if self.frame is None:
                    self.frame = -d["d"]
                continue
            if mn == "addi" and d["rd"] == 1 and d["ra"] == 1:
                continue
            if mn in ("mflr", "mtlr"):
                g[d["rd"]] = E("lr")
                continue
            if mn in ("stw", "lwz") and d["ra"] == 1:
                # A callee-saved spill is frame bookkeeping; a store of a live
                # value into the frame is a stack local, which this tier does
                # not model.
                if mn == "stw" and not (d["rs"] == 0 or 13 <= d["rs"] <= 31):
                    raise _fail("seeder",
                                "store of r%d into the frame at 0x%08x is a "
                                "stack local" % (d["rs"], a))
                if mn == "lwz" and 13 <= d["rd"] <= 31:
                    pass
                elif mn == "lwz" and d["rd"] != 0:
                    raise _fail("seeder",
                                "load of a stack local at 0x%08x" % a)
                continue
            if mn in ("stmw", "lmw") and d["ra"] == 1:
                continue                       # callee-saved block save/restore
            if mn in ("stfs", "stfd", "lfs", "lfd") and d["ra"] == 1:
                raise _fail("seeder",
                            "floating-point stack local at 0x%08x" % a)
            if d.get("ra") == 1 and mn in ("addi", "addis"):
                raise _fail("seeder",
                            "the address of a stack local is taken at 0x%08x"
                            % a)

            # ---- moves and constants --------------------------------------
            if mn == "li":
                g[d["rd"]] = Const(d["d"])
                continue
            if mn == "lis":
                g[d["rd"]] = E("hi", d["d"] & 0xFFFF)
                continue
            if mn == "mr":
                g[d["rd"]] = self.get(g, d["rs"], a)
                if d.get("rc"):
                    # `mr. rD, rS` is `or. rD, rS, rS`: MWCC's spelling of
                    # "move and test", and the compare the following branch
                    # reads.
                    cr[0] = ("val", g[d["rd"]], True)
                continue
            if mn == "addi":
                src = g.get(d["ra"])
                if src is not None and src.k == "hi":
                    addr = (src.a[0] << 16) + d["d"]
                    self.note_global(addr, None, True, None, a, taken=True,
                                     mode="abs")
                    g[d["rd"]] = E("gaddr", addr)
                    continue
                if d["ra"] in (2, 13):
                    res, bases = resolver_for(self.smap)
                    if res is None:
                        raise _fail("integrity",
                                    "r%d small-data address at 0x%08x and "
                                    "`datareloc` is not available to name it"
                                    % (d["ra"], a))
                    addr = bases[d["ra"]] + d["d"]
                    self.note_global(addr, None, True, None, a, taken=True,
                                     mode="abs")
                    g[d["rd"]] = E("gaddr", addr)
                    continue
                g[d["rd"]] = Bin("+", self.get(g, d["ra"], a), Const(d["d"]))
                continue

            # ---- memory ----------------------------------------------------
            if mn in ("lwz", "lbz", "lhz", "lha", "lfs", "lfd"):
                tgt = self.mem_target(g, d, a)
                sgn = self.sign_of(ins, idx, d)
                if tgt[0] == "g":
                    nm = self.note_global(tgt[1], d["width"], sgn, d["kind"], a,
                                          mode=tgt[2])
                    e = E("gvar", tgt[1], nm, tgt[2])
                else:
                    _k, base, off, _m = tgt
                    self.note_field(base, off, d["width"], sgn, d["kind"])
                    e = Field(base, off, d["width"], sgn, d["kind"])
                if d["kind"] == "f":
                    f[d["rd"]] = e
                else:
                    g[d["rd"]] = e
                continue
            if mn in ("stw", "stb", "sth", "stfs", "stfd"):
                tgt = self.mem_target(g, d, a)
                val = (f if d["kind"] == "f" else g).get(d["rs"])
                if val is None or val.k in ("lr", "hi", "undef"):
                    raise _fail("seeder",
                                "store of an undefined register at 0x%08x" % a)
                if id(val) in self.spent:
                    raise _fail("seeder",
                                "an earlier call's result is stored at 0x%08x "
                                "after another statement; that needs a local"
                                % a)
                sgn = val.a[3] if (val.k == "field" and val.a[2] == d["width"]) \
                    else True
                self.use_arg(val)
                self.consume(val, stmts)
                if tgt[0] == "g":
                    nm = self.note_global(tgt[1], d["width"], sgn, d["kind"], a,
                                          mode=tgt[2])
                    stmts.append(Stmt("gstore",
                                      E("gvar", tgt[1], nm, tgt[2]), val))
                else:
                    _k, base, off, _m = tgt
                    self.note_field(base, off, d["width"], sgn, d["kind"])
                    stmts.append(Stmt("store", base, off, val))
                continue

            # ---- integer arithmetic ----------------------------------------
            if mn in ("add", "subf", "mullw"):
                x, y = self.get(g, d["ra"], a), self.get(g, d["rb"], a)
                g[d["rd"]] = Bin({"add": "+", "subf": "-", "mullw": "*"}[mn],
                                 y if mn == "subf" else x,
                                 x if mn == "subf" else y)
                continue
            if mn == "mulli":
                g[d["rd"]] = Bin("*", self.get(g, d["ra"], a), Const(d["d"]))
                continue
            if mn in ("addic", "addic."):
                g[d["rd"]] = Bin("+", self.get(g, d["ra"], a), Const(d["d"]))
                if d.get("rc"):
                    cr[0] = ("val", g[d["rd"]], True)
                continue
            if mn == "subfic":
                g[d["rd"]] = Bin("-", Const(d["d"]), self.get(g, d["ra"], a))
                continue
            if mn == "neg":
                g[d["rd"]] = Un("-", self.get(g, d["ra"], a))
                continue
            if mn in ("and", "or", "xor"):
                x, y = self.get(g, d["rs"], a), self.get(g, d["rb"], a)
                g[d["rd"]] = Bin({"and": "&", "or": "|", "xor": "^"}[mn], x, y)
                if d.get("rc"):
                    cr[0] = ("val", g[d["rd"]], True)
                continue
            if mn == "oris":
                x = g.get(d["rs"])
                if x is not None and x.k == "hi":
                    raise _fail("seeder",
                                "lis/oris at 0x%08x builds a constant or an "
                                "address this tier does not model" % a)
                x = self.get(g, d["rs"], a)
                g[d["rd"]] = Bin("|", x, Const(d["u"] << 16))
                continue
            if mn in ("ori", "xori", "andi."):
                pre = g.get(d["rs"])
                if mn == "ori" and pre is not None and pre.k == "hi":
                    addr = (pre.a[0] << 16) | d["u"]
                    self.note_global(addr, None, True, None, a, taken=True,
                                     mode="abs")
                    g[d["rd"]] = E("gaddr", addr)
                    continue
                x = self.get(g, d["rs"], a)
                g[d["rd"]] = Bin({"ori": "|", "xori": "^", "andi.": "&"}[mn],
                                 x, Const(d["u"]))
                if d.get("rc"):
                    cr[0] = ("val", g[d["rd"]], True)
                continue
            if mn in ("slw", "srw"):
                g[d["rd"]] = Bin("<<" if mn == "slw" else ">>",
                                 self.get(g, d["rs"], a), self.get(g, d["rb"], a))
                continue
            if mn == "srawi":
                g[d["rd"]] = Bin(">>", self.get(g, d["rs"], a), Const(d["sh"]))
                continue
            if mn == "rlwinm":
                g[d["rd"]] = self.rlwinm(self.get(g, d["rs"], a), d)
                if d.get("rc"):
                    cr[0] = ("val", g[d["rd"]], True)
                continue
            if mn in ("extsb", "extsh"):
                src = self.get(g, d["rs"], a)
                if src.k == "field" and src.a[2] == (1 if mn == "extsb" else 2):
                    g[d["rd"]] = src
                else:
                    g[d["rd"]] = E("cast", "char" if mn == "extsb" else "short",
                                   src)
                if d.get("rc"):
                    cr[0] = ("val", g[d["rd"]], True)
                continue

            # ---- floating point --------------------------------------------
            if d.get("kind") == "fa":
                x, y = self.getf(f, d["fa"], a), self.getf(f, d["fb"], a)
                if d["mn"].startswith(("fmul",)):
                    y = self.getf(f, d["fc"], a)
                f[d["fd"]] = Bin({"fadd": "+", "fadds": "+", "fsub": "-",
                                  "fsubs": "-", "fmul": "*", "fmuls": "*",
                                  "fdiv": "/", "fdivs": "/"}[d["mn"]], x, y)
                continue
            if d.get("kind") == "fx":
                x = self.getf(f, d["fb"], a)
                f[d["fd"]] = x if d["mn"] == "fmr" else Un("-", x)
                continue
            if d.get("kind") in ("ldx", "stx"):
                raise _fail("seeder",
                            "indexed access `%s` at 0x%08x: array indexing is "
                            "not modelled" % (mn, a))
            if d.get("kind") == "fcmp":
                cr[d["crf"]] = ("fcmp", self.getf(f, d["fa"], a),
                                self.getf(f, d["fb"], a))
                cr.pop(("ov", d["crf"]), None)
                continue

            # ---- CR-logical: the float `<=` / `>=` idiom ---------------------
            if mn in CROPS.values():
                bt, ba, bb = d["bt"], d["ba"], d["bb"]
                crf = bt >> 2
                if (ba >> 2) != crf or (bb >> 2) != crf:
                    raise _fail("seeder",
                                "%s at 0x%08x combines bits from different "
                                "condition registers" % (mn, a))
                if mn == "cror":
                    parts = [self.cr_bit(cr, crf, ba & 3, a),
                             self.cr_bit(cr, crf, bb & 3, a)]
                    cr[("ov", crf, bt & 3)] = Logic("||", parts)
                elif mn == "crand":
                    parts = [self.cr_bit(cr, crf, ba & 3, a),
                             self.cr_bit(cr, crf, bb & 3, a)]
                    cr[("ov", crf, bt & 3)] = Logic("&&", parts)
                elif mn == "crxor" and ba == bb:
                    cr[("ov", crf, bt & 3)] = E("false")
                else:
                    raise _fail("seeder", "%s at 0x%08x is not modelled"
                                % (mn, a))
                continue

            # ---- compares ---------------------------------------------------
            if mn in ("cmpwi", "cmplwi"):
                cr[d["crf"]] = ("cmp", self.get(g, d["ra"], a),
                                Const(d.get("d", d.get("u"))), d["signed"])
                continue
            if mn in ("cmpw", "cmplw"):
                cr[d["crf"]] = ("cmp", self.get(g, d["ra"], a),
                                self.get(g, d["rb"], a), d["signed"])
                continue

            # ---- calls -------------------------------------------------------
            if mn == "bl":
                self.do_call(a, d, st, stmts)
                continue
            if mn == "mtctr":
                g["ctr"] = self.get(g, d["rd"], a)
                continue
            if mn == "bcctr" and d["lk"]:
                self.do_indirect_call(a, st, stmts)
                continue

            raise _fail("seeder", "unmodelled instruction %s @ 0x%08x" % (mn, a))

    # -- helpers -------------------------------------------------------------

    def sign_of(self, ins, idx, d):
        if d["kind"] == "f":
            return None
        if d["width"] == 1:
            nxt = ins[idx + 1][2] if idx + 1 < len(ins) else None
            return bool(nxt and nxt["mn"] == "extsb"
                        and nxt.get("rs") == d["rd"])
        return d["signed"]

    def cr_bit(self, cr, crf, bit, a):
        return cr_bit(cr, crf, bit)

    def get(self, g, r, a):
        if r == 1:
            raise _fail("seeder",
                        "the stack pointer is used as a value at 0x%08x "
                        "(a stack local)" % a)
        e = g.get(r)
        if e is None or e.k in ("undef",):
            raise _fail("seeder", "read of an undefined register r%d @ 0x%08x"
                        % (r, a))
        if id(e) in self.spent:
            raise _fail("seeder",
                        "the result of an earlier call is read again at "
                        "0x%08x after another statement; naming it twice needs "
                        "a local variable" % a)
        if e.k == "hi":
            raise _fail("seeder",
                        "the high half of an address built by `lis` at 0x%08x "
                        "is used before its low half" % a)
        if e.k == "lr":
            raise _fail("seeder", "the link register is used as a value")
        return e

    def getf(self, f, r, a):
        e = f.get(r)
        if e is None:
            if r in ARG_FPR:
                raise _fail("seeder",
                            "f%d is read before it is written at 0x%08x: this "
                            "function takes a floating-point parameter, whose "
                            "position in the C argument list the registers do "
                            "not state" % (r, a))
            raise _fail("seeder", "read of an undefined FPR f%d @ 0x%08x" % (r, a))
        return e

    def fold_base(self, base, off, a):
        """`addi rX, rArg, k` then a load at `d(rX)` is one field access at
        `k + d`, not a pointer this tier has to name."""
        while base is not None and base.k == "bin" and base.a[0] == "+"                 and base.a[2].k == "const":
            off += base.a[2].a[0]
            base = base.a[1]
        return base, off

    # -- globals ------------------------------------------------------------

    def global_at(self, addr, a):
        """Name a global, or refuse by name.  Before the data-relocation lane
        landed this was an unconditional refusal (`match.py` name-checked only
        R_PPC_REL24, so a data relocation would have matched any global in the
        game).  `match.py` now ADDRESS-checks every data relocation, so the
        honest move is to emit the symbol and let the oracle judge it."""
        res, bases = resolver_for(self.smap)
        if res is None:
            raise _fail("integrity",
                        "a global is referenced at 0x%08x and `datareloc` is "
                        "not available to name it" % a)
        if not res.in_image(addr):
            raise _fail("seeder",
                        "the reference at 0x%08x resolves to 0x%08x, which is "
                        "in no DOL section and not in bss" % (a, addr))
        return res.name_for_address(addr)

    def note_global(self, addr, width, signed, kind, a, taken=False,
                    mode="sda"):
        """Record a global and the ADDRESSING MODE the retail bytes used.

        The mode is not cosmetic.  Measured on mwcc-rs build 2.7 with the
        project's own `-sdata 8 -sdata2 8`: an `extern` scalar of four bytes is
        addressed through the small-data area in ONE instruction
        (`R_PPC_EMB_SDA21`), while an object larger than the threshold is
        addressed absolutely in TWO (`lis`/`addi`, `R_PPC_ADDR16_HA/LO`).  So a
        global the retail reaches through `lis`/`addi` must be DECLARED large
        or the candidate is a whole instruction short, and one it reaches
        through r13 must be declared small.  The declaration is how the C says
        which the bytes did.
        """
        prev = self.globals.get(addr)
        if prev is not None:
            pw, ps, pk, pt, pm = prev
            if width is not None and pw is not None and (pw != width
                                                         or pk != kind):
                raise _fail("seeder",
                            "the global at 0x%08x is accessed as %s%s and "
                            "%s%s" % (addr, pk, pw, kind, width))
            if pm != mode:
                raise _fail("seeder",
                            "the global at 0x%08x is reached both through the "
                            "small-data area and absolutely; one declaration "
                            "cannot spell both" % addr)
            width = width if width is not None else pw
            kind = kind if kind is not None else pk
            signed = ps or signed
            taken = taken or pt
        if mode == "abs" and ABS_GLOBAL_BLOCKED:
            raise _fail("compiler", ABS_GLOBAL_REASON % a)
        self.globals[addr] = (width, signed, kind, taken, mode)
        return self.global_at(addr, a)

    def mem_target(self, g, d, a):
        """Where a D-form load/store points: ('g', absolute address) for a
        global, ('p', base expression, offset) for a pointer."""
        ra = d["ra"]
        res, bases = resolver_for(self.smap)
        if ra in (2, 13):
            if res is None:
                raise _fail("integrity",
                            "r%d small-data access at 0x%08x and `datareloc` "
                            "is not available to name it" % (ra, a))
            return ("g", bases[ra] + d["d"], "sda")
        if ra == 0:
            raise _fail("seeder",
                        "absolute r0-based address at 0x%08x" % a)
        base = g.get(ra)
        if base is None:
            raise _fail("seeder", "memory base r%d is undefined @ 0x%08x" % (ra, a))
        if base.k == "hi":
            # `lis rD, X@ha` then `lwz rT, X@l(rD)` -- the two-instruction
            # absolute access.  Measured on mwcc-rs 2.7: every absolute access
            # it emits is THREE instructions (`lis`/`addi`/load), so no C
            # spelling reaches this form.
            raise _fail("compiler",
                        "the two-instruction absolute access at 0x%08x "
                        "(`lis` then a displaced load) is a form mwcc-rs does "
                        "not emit; it always materialises the address with "
                        "`lis`/`addi` first" % a)
        if base.k == "gaddr":
            # The retail built ONE address and indexed off it, so the global
            # is an aggregate and the displacement is a member -- folding the
            # displacement into the address would name a different symbol and
            # lose the `addi`.
            return ("p", base, d["d"], None)
        return ("p",) + self.membase_ptr(base, d, a) + (None,)

    def membase_ptr(self, base, d, a):
        if id(base) in self.spent:
            raise _fail("seeder",
                        "an earlier call's result is dereferenced at 0x%08x "
                        "after another statement; that needs a local" % a)
        base, off = self.fold_base(base, d["d"], a)
        if base is None or base.k not in ("arg", "field", "gaddr"):
            raise _fail("seeder",
                        "memory base at 0x%08x is neither an argument nor a "
                        "loaded pointer" % a)
        if base.k == "field" and base.a[4] != "i":
            raise _fail("seeder", "memory base is a float field @ 0x%08x" % a)
        return base, off

    def rlwinm(self, x, d):
        sh, mb, me = d["sh"], d["mb"], d["me"]
        if mb == 0 and me == 31 - sh:                     # slwi
            return Bin("<<", x, Const(sh))
        if sh and me == 31 and mb == 32 - sh:             # srwi
            return Bin(">>", x, Const(32 - sh))
        if sh == 0 and me == 31:                          # clrlwi
            return Bin("&", x, Const((1 << (32 - mb)) - 1))
        raise _fail("seeder",
                    "rlwinm sh=%d mb=%d me=%d is not a shift or a mask"
                    % (sh, mb, me))

    def do_call(self, a, d, st, stmts):
        g, f = st["g"], st["f"]
        tgt = a + d["li"]
        hit = self.smap.lookup(tgt)
        if hit is None:
            raise _fail("seeder", "callee 0x%08x is in no link-map symbol" % tgt)
        name = hit["name"]
        if not _c_ident(name):
            raise _fail("seeder",
                        "callee name %r is not a C identifier" % name)
        args, top = self.call_args(g, name, a)
        # EABI floating-point arguments live in f1..f8 and are numbered
        # independently of the GPR arguments, so their POSITION in the C
        # argument list cannot be read off the registers.  A call that passes
        # both kinds is refused; a call that passes only FP arguments has them
        # in order.
        ftop = -1
        for i, r in enumerate(ARG_FPR):
            if f.get(r) is not None:
                ftop = i
        if ftop >= 0:
            if args:
                raise _fail("seeder",
                            "call %s at 0x%08x mixes GPR and FPR arguments; "
                            "their order in the C argument list is not "
                            "recoverable from the registers alone" % (name, a))
            for i in range(ftop + 1):
                e = f.get(ARG_FPR[i])
                if e is None:
                    raise _fail("seeder",
                                "FP argument %d to %s is undefined at 0x%08x"
                                % (i, name, a))
                self.use_arg(e)
                args.append(e)
            self.fp_args.add(name)
        for x in args:
            if self.consume(x, stmts):
                break
        else:
            self.flush(stmts)
        c = Call(name, args, "f" if ftop >= 0 else "i")
        self.calls.append((name, len(args), "f" if ftop >= 0 else "i"))
        self.pending = Stmt("call", c)
        # EABI: the volatile registers do not survive a call.
        for r in VOLATILE_GPR:
            g.quiet(r, E("undef"))
        for r in VOLATILE_FPR:
            f.pop(r, None)
        st["cr"].clear()
        g.dirty.clear()
        g.quiet(3, c)

    def call_args(self, g, name, a):
        """The argument list, from the registers this function set up for the
        call.  See `RegFile` for why the high-water mark is a WRITE mark."""
        top = -1
        for i, r in enumerate(ARG_GPR):
            if r in getattr(g, "dirty", ()):
                top = i
        args = []
        for i in range(top + 1):
            e = g.get(ARG_GPR[i])
            if e is None or e.k in ("undef", "lr", "hi"):
                raise _fail("seeder",
                            "argument %d to %s is undefined at 0x%08x"
                            % (i, name, a))
            self.use_arg(e)
            args.append(e)
        return args, top

    def do_indirect_call(self, a, st, stmts):
        """`mtctr` + `bctrl` -- a call through a function pointer held in a
        structure field.  The field is then DECLARED as a function pointer, so
        the C says what the bytes say instead of casting an `int`."""
        g, f = st["g"], st["f"]
        tgt = g.get("ctr")
        if tgt is None:
            raise _fail("seeder", "bctrl at 0x%08x with no known CTR value" % a)
        if tgt.k != "field":
            raise _fail("seeder",
                        "bctrl at 0x%08x calls through a value that is not a "
                        "structure field (a vtable or a jump table needs a "
                        "global address, which is an unverifiable data "
                        "relocation)" % a)
        args, _top = self.call_args(g, "the indirect call", a)
        if any(f.get(r) is not None for r in ARG_FPR):
            raise _fail("seeder",
                        "the indirect call at 0x%08x passes floating-point "
                        "arguments" % a)
        self.fptr_fields[(self._skey(tgt.a[0]), tgt.a[1])] = len(args)
        self.use_arg(tgt)
        for x in args:
            if self.consume(x, stmts):
                break
        else:
            self.flush(stmts)
        c = E("icall", tgt, tuple(args))
        self.pending = Stmt("call", c)
        for r in VOLATILE_GPR:
            g.quiet(r, E("undef"))
        for r in VOLATILE_FPR:
            f.pop(r, None)
        st["cr"].clear()
        g.dirty.clear()
        g.quiet(3, c)
        g.pop("ctr", None)

    def flush(self, stmts):
        """Commit the pending call as its own statement.  Its result is then
        SPENT: C has no way to name it again without a local variable, so a
        later read of r3 refuses by name instead of re-emitting the call."""
        if self.pending is not None:
            stmts.append(self.pending)
            self.spent.add(id(self.pending.a[0]))
            self.pending = None

    def consume(self, e, stmts):
        """If `e` is the pending call's own result, inline it into the use;
        otherwise the pending call is flushed as its own statement first."""
        if self.pending is not None and e is self.pending.a[0]:
            self.pending = None
            return True
        self.flush(stmts)
        return False


# ---------------------------------------------------------------------------
# 5. structuring
# ---------------------------------------------------------------------------

def cr_bit(cr, crf, bit):
    """The C condition one CR bit carries.  A bit written by a CR-logical
    (`cror`, `crand`) overrides the compare that set the field."""
    ov = cr.get(("ov", crf, bit))
    if ov is not None:
        return ov
    rec = cr.get(crf)
    if rec is None:
        raise _fail("seeder", "branch on cr%d, which nothing in this function "
                              "set" % crf)
    op = {0: "<", 1: ">", 2: "=="}.get(bit)
    if op is None:
        raise _fail("seeder", "branch on the summary-overflow bit")
    if rec[0] == "cmp":
        return Cmp(op, rec[1], rec[2], rec[3])
    if rec[0] == "fcmp":
        return Cmp(op, rec[1], rec[2], True)
    if rec[0] == "val":
        return Cmp(op, rec[1], Const(0), rec[2])
    raise _fail("seeder", "unrecognised condition record")


def branch_cond(cr, d):
    """Recover the C condition a `bc` tests.  Returns the condition under which
    the branch is TAKEN."""
    bo, bi = d["bo"], d["bi"]
    if bo & 0x04 == 0:
        raise _fail("compiler",
                    "a CTR-decrementing branch (bdnz/bdz) is a loop; mwcc-rs "
                    "answers `loop codegen is not implemented yet (roadmap)`")
    if bo & 0x10:
        return None                                   # unconditional
    c = cr_bit(cr, bi >> 2, bi & 3)
    return c if (bo & 0x08) else negate(c)


class Structurer(object):
    """Recursive region structuring over the block list, in address order.

    The only graph shapes accepted are the ones MWCC's own front end produces
    for structured C, because those are the only ones whose codegen can match:

        if (c) { A }                 forward branch over A
        if (c) { A } else { B }      forward branch over A, A ends in `b` past B
        if (c1 && c2) { A }          two branches to the same skip label
        if (c1 || c2) { A }          the first branch enters A, the last skips
        return / return e            `blr`, or `bXXlr`, or a branch to the
                                     epilogue

    Anything else -- a back edge, a `bctr` table, a branch into the middle of
    another region -- is refused by name.  There is deliberately no `goto`
    fallback: MWCC's codegen for a `goto` is not its codegen for an `if`, so a
    `goto` candidate cannot match and emitting one would only waste a compile.
    """

    def __init__(self, lifter):
        self.L = lifter
        self.blocks = lifter.blocks
        self.n = len(self.blocks)
        self.epilogue = self.find_epilogue()

    def find_epilogue(self):
        """The address of the block that only restores the frame and returns."""
        last = self.blocks[-1]
        d = last.ins[-1][2]
        if d["mn"] != "bclr" or not (d["bo"] & 0x14 == 0x14):
            return None
        return last.addr

    def run(self):
        st = self.L.entry_state()
        stmts = self.region(0, self.n, st)
        return stmts

    def region(self, i, end, st):
        out = []
        while i < end:
            b = self.blocks[i]
            self.L.lift_block(b, st, out)
            t = b.term
            if t is None:
                i += 1
                continue
            mn = t["mn"]
            if mn == "bclr":
                if t["bo"] & 0x14 == 0x14:
                    self.emit_return(out, st)
                    return out
                c = branch_cond(st["cr"], t)
                self.L.use_arg(c)
                inner = []
                self.emit_return(inner, self.fork(st))
                out.append(Stmt("if", c, inner, None))
                i += 1
                continue
            if mn == "bcctr":
                raise _fail("integrity" if t["lk"] else "seeder",
                            "an indirect branch through CTR (a compiler switch "
                            "table) needs the table's address, which is an "
                            "unverifiable data relocation")
            if mn == "b":
                tgt = self.by_idx(t["target"])
                if tgt <= i:
                    raise _fail("compiler",
                                "backward branch at 0x%08x is a loop; mwcc-rs "
                                "answers `loop codegen is not implemented yet "
                                "(roadmap)`" % b.ins[-1][0])
                if tgt == end:
                    return out
                if tgt > end:
                    raise _fail("seeder",
                                "branch leaves the enclosing region "
                                "(unstructured graph)")
                # a forward jump inside the region with no `if` above it
                if self.epilogue is not None and \
                        self.blocks[tgt].addr == self.epilogue:
                    self.L.flush(out)
                    self.emit_return(out, st)
                    return out
                raise _fail("seeder",
                            "unstructured forward branch at 0x%08x"
                            % b.ins[-1][0])
            if mn == "bc":
                i = self.do_if(out, i, end, st)
                continue
            raise _fail("seeder", "unhandled terminator %s" % mn)
        return out

    def by_idx(self, addr):
        for b in self.blocks:
            if b.addr == addr:
                return b.idx
        raise _fail("seeder", "branch target 0x%08x is not a block leader" % addr)

    def do_if(self, out, i, end, st):
        b = self.blocks[i]
        t = b.term
        tgt = self.by_idx(t["target"])
        if tgt <= i:
            raise _fail("compiler",
                        "backward conditional branch at 0x%08x is a loop; "
                        "mwcc-rs answers `loop codegen is not implemented yet "
                        "(roadmap)`" % b.ins[-1][0])
        if tgt > end:
            raise _fail("seeder", "conditional branch leaves the region")
        cond_taken = branch_cond(st["cr"], t)
        self.L.flush(out)

        # --- short-circuit chain: consecutive one-terminator blocks whose
        #     branches all go to the same skip label, or all but the last go
        #     to the body.
        conds = [(cond_taken, tgt)]
        j = i + 1
        while j < tgt:
            bj = self.blocks[j]
            tj = bj.term
            if tj is None or tj["mn"] != "bc":
                break
            # The block must be a PURE compare: a short-circuit operand may not
            # have a side effect, because C evaluates it conditionally and the
            # lifter would have to hoist the statement out of the condition.
            # Probe on a copy so a rejected block leaves no state behind.
            probe_st = self.fork(st)
            probe = []
            save_pending = self.L.pending
            try:
                self.L.lift_block(bj, probe_st, probe)
            except SeedFail:
                self.L.pending = save_pending
                break
            if probe or self.L.pending is not save_pending:
                self.L.pending = save_pending
                break
            tj_i = self.by_idx(tj["target"])
            if tj_i <= j:
                break
            try:
                cj = branch_cond(probe_st["cr"], tj)
            except SeedFail:
                break
            st["g"], st["f"], st["cr"] = (probe_st["g"], probe_st["f"],
                                          probe_st["cr"])
            conds.append((cj, tj_i))
            j += 1
            if conds[-1][1] != tgt:
                break

        cond, body_start, skip = self.reduce_chain(conds, i, tgt)
        if skip > end:
            raise _fail("seeder",
                        "the short-circuit chain's skip label leaves the "
                        "enclosing region")
        self.L.use_arg(cond)
        # --- else arm?
        body_end = skip
        else_end = None
        pen = self.blocks[body_end - 1]
        if pen.term is not None and pen.term["mn"] == "b":
            jt = self.by_idx(pen.term["target"])
            if jt > body_end and jt <= end:
                else_end = jt
        then_st = self.fork(st)
        then_stmts = self.region(body_start, body_end, then_st)
        self.L.flush(then_stmts)
        else_stmts = None
        if else_end is not None:
            else_st = self.fork(st)
            else_stmts = self.region(body_end, else_end, else_st)
            self.L.flush(else_stmts)
        if not then_stmts and not else_stmts:
            raise _fail("seeder", "an `if` with an empty body")
        if else_stmts is not None and not then_stmts:
            out.append(Stmt("if", negate(cond), else_stmts, None))
        else:
            out.append(Stmt("if", cond, then_stmts, else_stmts))
        nxt = else_end if else_end is not None else body_end
        # after a two-armed if, the register state is only usable if neither
        # arm defined anything the continuation reads.  Rather than guess,
        # drop the volatile registers -- a read of one then refuses by name.
        self.join(st, then_stmts, else_stmts)
        return nxt

    def reduce_chain(self, conds, i, tgt):
        """Fold a run of conditional branches into one C condition.

        Returns (condition, body-start block index, skip block index).

        `&&`  every branch jumps to the SAME label, past the body:
              `if (a) skip; if (b) skip; BODY:` is `if (!a && !b) BODY`.
        `||`  every branch but the last jumps INTO the body, and the last
              jumps past it: `if (a) body; if (!b) skip; body: BODY:` is
              `if (a || !b) BODY`.  Note the skip label is then the LAST
              branch's target, not the first's -- reading it off the first
              branch is what makes a `||` look like a mixed chain.

        Anything else is refused: a mixed chain needs parenthesised
        sub-expressions whose grouping the branch graph alone does not state.
        """
        if len(conds) == 1:
            return negate(conds[0][0]), i + 1, tgt
        skips = {c[1] for c in conds}
        if skips == {tgt}:
            return (Logic("&&", [negate(c) for c, _ in conds]),
                    i + len(conds), tgt)
        body = i + len(conds)
        skip = conds[-1][1]
        if all(c[1] == body for c in conds[:-1]) and skip > body:
            parts = [c for c, _ in conds[:-1]] + [negate(conds[-1][0])]
            return Logic("||", parts), body, skip
        raise _fail("seeder",
                    "a branch chain that is neither a pure && nor a pure || "
                    "(targets %s)" % sorted(skips))

    def fork(self, st):
        return {"g": st["g"].copy(), "f": dict(st["f"]),
                "cr": dict(st["cr"])}

    def join(self, st, then_stmts, else_stmts):
        # Neither arm's register state survives the join.  Rather than invent a
        # phi -- which would need a local variable, and MWCC's value tracking
        # for one is a separate roadmap item -- every volatile is dropped, so a
        # continuation that reads one refuses by name instead of guessing.
        g = st["g"]
        for r in VOLATILE_GPR:
            g.quiet(r, E("undef"))
        for r in list(st["f"]):
            if r in VOLATILE_FPR:
                st["f"].pop(r, None)
        st["cr"].clear()
        g.dirty.clear()

    def emit_return(self, out, st):
        self.L.flush_return(out, st)


# ---------------------------------------------------------------------------
# 6. emission
# ---------------------------------------------------------------------------

def _struct_name(key):
    if key[0] == "gbl":
        return "G%08x" % key[1]
    if key[0] == "arg":
        return "S%d" % key[1]
    return "%s_%x" % (_struct_name(key[1]), key[2])


def _struct_text(key, fields, ptr_fields, spec, fptr_fields=None):
    lines = ["typedef struct %s {" % _struct_name(key)]
    cur = 0
    for off in sorted(fields):
        wid, sgn, kind = fields[off]
        if off < cur:
            raise _fail("seeder", "overlapping fields at 0x%x" % off)
        if off % wid:
            raise _fail("seeder", "field 0x%x is not %d-aligned" % (off, wid))
        if off > cur:
            lines.append("    char pad_%x[0x%x];" % (cur, off - cur))
        if fptr_fields and (key, off) in fptr_fields:
            n = fptr_fields[(key, off)]
            lines.append("    int (*%s)(%s);"
                         % (_fname(off),
                            ", ".join("int" for _ in range(n)) or "void"))
        elif (key, off) in ptr_fields:
            ty = "%s *" % _struct_name(("fld", key, off))
            lines.append("    %-20s %s;" % (ty, _fname(off)))
        elif kind == "f":
            lines.append("    %-20s %s;" % (FTYPE[wid], _fname(off)))
        else:
            ty = spec.get("ftype", {}).get((key, off)) or CTYPE[(wid, sgn)]
            lines.append("    %-20s %s;" % (ty, _fname(off)))
        cur = off + wid
    lines.append("} %s;" % _struct_name(key))
    return "\n".join(lines)


def emit(lifter, stmts, spec):
    names = {}
    for addr in lifter.globals:
        names["g", addr] = lifter.global_at(addr, addr)
    keys = list(lifter.structs)
    ptr_fields = set()
    for k in keys:
        if k[0] == "fld":
            ptr_fields.add((k[1], k[2]))

    out = []
    # Deepest struct first, so a pointer field always names a type that is
    # already complete and no forward declaration is needed -- mwcc-rs will not
    # take a typedef that arrives as an incomplete type.
    ordered = sorted(keys, key=lambda k: -len(_struct_name(k)))
    for k in ordered:
        out.append(_struct_text(k, lifter.structs[k], ptr_fields, spec,
                                lifter.fptr_fields))
        out.append("")

    # `extern` declarations for every global the bytes touch.  The NAME is
    # what the oracle checks -- `match.py` resolves the relocation's symbol back
    # to an address and compares it with the address the retail encoding names
    # -- so a wrong name is a MISMATCH, not a silent pass.
    # Globals the retail reached through `lis`/`addi` AND indexed off are
    # aggregates: their layout is a struct like any other, and declaring them
    # that way is what makes mwcc address them absolutely.
    aggregate = {k[1] for k in keys if k[0] == "gbl"}
    gdecls = []
    for addr in sorted(lifter.globals):
        width, signed, kind, taken, mode = lifter.globals[addr]
        nm = names["g", addr]
        if addr in aggregate:
            gdecls.append("extern %s %s;"
                          % (_struct_name(("gbl", addr)), nm))
            continue
        if kind == "f":
            ty = FTYPE[width]
        elif width is None:
            ty = "int"
        else:
            ty = spec.get("gtype", {}).get(addr) or CTYPE[(width, bool(signed))]
        if mode == "sda":
            gdecls.append("extern %s %s;" % (ty, nm))
        else:
            # Larger than `-sdata 8`, so mwcc addresses it with `lis`/`addi`
            # the way the retail bytes do.  The padding is what makes the
            # object large; it is never read.
            gdecls.append("extern struct { %s v; char pad_[8]; } %s;"
                          % (ty, nm))
    out.extend(gdecls)
    if gdecls:
        out.append("")

    protos = {}
    for name, n, kind in lifter.calls:
        prev = protos.get(name)
        protos[name] = (max(prev[0], n), kind) if prev else (n, kind)
    for name in sorted(protos):
        n, kind = protos[name]
        aty = "float" if kind == "f" else "int"
        args = ", ".join(aty for _ in range(n)) or "void"
        rt = spec.get("calltype", {}).get(name, "int")
        out.append("extern %s %s(%s);" % (rt, name, args))
    if protos:
        out.append("")

    nargs = (max(lifter.used_args) + 1) if lifter.used_args else 0
    params = []
    for a in range(nargs):
        if a in lifter.ptr_args:
            params.append("%s *p%d" % (_struct_name(("arg", a)), a))
        else:
            params.append("%s p%d" % (spec.get("argtype", "int"), a))
    rt = lifter.return_type(spec)
    out.append("%s f(%s)" % (rt, ", ".join(params) if params else "void"))
    out.append("{")
    body = render_stmts(stmts, names, 1)
    out.extend(body)
    out.append("}")
    return "\n".join(out) + "\n"


def render_stmts(stmts, names, depth):
    ind = "    " * depth
    out = []
    for s in stmts:
        if s.k == "gstore":
            out.append("%s%s = %s;" % (ind, render(s.a[0], names),
                                       render(s.a[1], names)))
        elif s.k == "store":
            # via the field renderer, so a member of a global aggregate comes
            # out as `G.field` and a member through a pointer as `p->field`
            out.append("%s%s = %s;"
                       % (ind,
                          render(Field(s.a[0], s.a[1], None, None, None), names),
                          render(s.a[2], names)))
        elif s.k == "call":
            out.append("%s%s;" % (ind, render(s.a[0], names)))
        elif s.k == "return":
            if s.a[0] is None:
                out.append("%sreturn;" % ind)
            else:
                out.append("%sreturn %s;" % (ind, render(s.a[0], names)))
        elif s.k == "if":
            out.append("%sif (%s)" % (ind, render(s.a[0], names)))
            then = render_stmts(s.a[1], names, depth + 1)
            if len(s.a[1]) == 1 and s.a[1][0].k != "if":
                out.extend(then)
            else:
                out.append("%s{" % ind)
                out.extend(then)
                out.append("%s}" % ind)
            if s.a[2]:
                out.append("%selse" % ind)
                els = render_stmts(s.a[2], names, depth + 1)
                if len(s.a[2]) == 1 and s.a[2][0].k != "if":
                    out.extend(els)
                else:
                    out.append("%s{" % ind)
                    out.extend(els)
                    out.append("%s}" % ind)
        else:
            raise _fail("seeder", "unrenderable statement %s" % s.k)
    return out


# ---------------------------------------------------------------------------
# 7. the entry point
# ---------------------------------------------------------------------------

def _lifter_return(self, out, st):
    """Emit the return for one exit path.  Determining void-ness is the one
    place where the bytes are genuinely ambiguous -- a function that leaves r3
    alone is void, and a function whose r3 is a value it computed is not -- so
    the rule is stated rather than guessed: r3 counts as a return value only if
    THIS function wrote it."""
    g = st["g"]
    e = g.get(3)
    val = None
    if e is not None and e.k not in ("undef", "lr", "hi"):
        if not (e.k == "arg" and e.a[0] == 0):
            val = e
    if val is not None and id(val) in self.spent:
        # r3 still carries a call's result, but that call has already been
        # emitted as its own statement.  The function did not return it -- it
        # simply never wrote r3 again -- and `void` is byte-identical here,
        # because the value is already in the register either way.
        val = None
    if val is not None:
        self.consume(val, out)
        self.use_arg(val)
        out.append(Stmt("return", val))
        kind = "f" if (val.k == "field" and val.a[4] == "f") else "i"
        if self.returns_value is False:
            raise _fail("seeder",
                        "one path returns a value and another does not")
        self.returns_value = True
        self.nonvoid_kind = kind
        self.ret_expr = val
    else:
        self.flush(out)
        if self.returns_value:
            raise _fail("seeder",
                        "one path returns a value and another does not")
        self.returns_value = False
        out.append(Stmt("return", None))


def _lifter_return_type(self, spec):
    if not self.returns_value:
        return "void"
    if spec.get("rettype"):
        return spec["rettype"]
    e = getattr(self, "ret_expr", None)
    if e is not None and e.k == "field" and e.a[4] == "f":
        return FTYPE[e.a[2]]
    return "int"


Lifter.flush_return = _lifter_return
Lifter.return_type = _lifter_return_type


def _strip_trailing_return(stmts):
    """A `return;` as the very last statement of a void function is what the
    bytes say and what C implies, but MWCC does not emit anything for it and
    neither does a human -- and the two spellings compile the same.  Drop it so
    the candidate reads like source."""
    while stmts and stmts[-1].k == "return" and stmts[-1].a[0] is None:
        stmts.pop()
    return stmts


def seed_cfg(rec, retail, smap, spec=None):
    """Candidate 0 for a function WITH control flow.  Raises SeedFail."""
    spec = spec or {}
    if len(retail) < 4:
        raise _fail("seeder", "empty function")
    L = Lifter(rec, retail, smap, spec)
    if L.loops:
        raise _fail("compiler",
                    "%d back edge(s): this is a loop, and mwcc-rs answers "
                    "`loop codegen is not implemented yet (roadmap)` for every "
                    "loop form" % len(L.loops))
    S = Structurer(L)
    stmts = S.run()
    L.flush(stmts)
    if L.returns_value is None:
        raise _fail("seeder", "no return path was reached")
    if not L.returns_value:
        _strip_trailing_return(stmts)
    if not stmts:
        raise _fail("seeder", "no effect")
    if max(L.used_args, default=-1) >= 8:
        raise _fail("seeder", "more than eight arguments")
    return emit(L, stmts, spec)


# ---------------------------------------------------------------------------
# 8. the `undefined8` narrowing rule, for the Ghidra-seeded path
# ---------------------------------------------------------------------------

NARROW_EVIDENCE = """\
Ghidra types an EABI argument register it cannot resolve as `undefined8`, and
the port's shim contract makes that a 64-bit integer; mwcc-rs then refuses the
function for a long-long shape the retail code does not contain.  The compiler
census (docs/matching-compiler-census.md s2a) measured 683 functions -- 13,628
instructions -- that compile the moment that placeholder is narrowed to 32 bits.

The retail bytes are the evidence, and they are checked here rather than
assumed: a value is 64-bit only if the function contains an operation only a
64-bit value would need -- a true 64-bit opcode (`ld`, `std`, `rldicl`,
`sradi`; a 32-bit Gekko executes none of them, so this half of the test exists
to catch a mis-decode, not to fire), or the CARRY CHAIN a 32-bit target uses
for `long long` arithmetic (`addc`/`adde`, `subfc`/`subfe`, `addze`/`addme`).

Measured over the whole link map: 133 of 5,897 `.text` functions carry such
evidence; 5,764 do not.  The test is deliberately CONSERVATIVE in the safe
direction -- `addze` also appears in MWCC's constant-division idiom
(`mulhw`/`srawi`/`addze`), which is not a `long long` -- so some of those 133
are refused when they need not be.  Refusing to narrow costs a compile that
would have failed anyway; narrowing a value that really is 64-bit would
silently mistype it, and that is the error worth avoiding.
"""

# Two independent kinds of evidence, because only one of them exists on this
# CPU and a rule that rested on the other would be vacuous:
#
#   * a genuine 64-bit instruction (`ld`, `std`, `rldicl`, `sradi`, ...).  A
#     Gekko cannot execute one, so on real retail code this never fires -- and
#     saying so is the point: it is the check that would catch a mis-decode.
#   * the CARRY CHAIN.  A 32-bit target implements `long long` arithmetic as
#     paired 32-bit operations threaded through XER[CA]: `addc`/`adde`,
#     `subfc`/`subfe`, `addze`/`addme`.  THIS is what a real `long long`
#     looks like in this binary, and it is the half of the rule that does the
#     work.
PPC64_PRIMARY = {58, 62}                       # ld/ldu/lwa, std/stdu
PPC64_X31 = {21, 53, 149, 181, 341, 373, 9, 457, 489, 794, 826, 986}
CARRY_X31 = {10: "addc", 138: "adde", 8: "subfc", 136: "subfe",
             202: "addze", 234: "addme", 200: "subfze", 232: "subfme"}


def has_64bit_evidence(retail):
    """True iff the retail bytes contain an operation only a 64-bit value would
    need.  Returns (bool, reason)."""
    n = len(retail) // 4
    for w in struct.unpack(">%dI" % n, retail[:n * 4]):
        op = w >> 26
        if op in PPC64_PRIMARY:
            return True, "primary opcode %d is a 64-bit load/store" % op
        if op == 30:
            return True, "primary opcode 30 is the 64-bit rotate group"
        if op == 31:
            xo = (w >> 1) & 0x3FF
            if xo in PPC64_X31:
                return True, "op31 XO %d is a 64-bit form" % xo
            if xo in CARRY_X31:
                return True, ("`%s` threads a carry between two 32-bit halves "
                              "-- this is a real 64-bit value" % CARRY_X31[xo])
    return False, ("no 64-bit load, store or rotate and no carry chain "
                   "(addc/adde/subfc/subfe/addze): every value in this "
                   "function moves through 32-bit register operations")


_U8 = re.compile(r"\bundefined8\b")


def narrow_undefined8(csrc, retail):
    """Rewrite `undefined8` to a 32-bit type when the retail bytes carry no
    64-bit operation.  Returns (source, note) or raises SeedFail.

    This is the ONE typing decision this file makes on someone else's C, and it
    is made from the bytes, not from the decompiler's guess.  Where the evidence
    is ambiguous the function is refused by name and counted, exactly like every
    other refusal here.
    """
    if not _U8.search(csrc):
        return csrc, None
    wide, why = has_64bit_evidence(retail)
    if wide:
        raise _fail("seeder",
                    "undefined8 kept: the retail bytes carry a real 64-bit "
                    "operation (%s)" % why)
    return _U8.sub("undefined4", csrc), \
        "undefined8 -> undefined4 (%s)" % why


REFUSALS = ("integrity", "compiler", "seeder")


# ---------------------------------------------------------------------------
# 9. one measured compiler blocker, stated so flipping it back is one line
# ---------------------------------------------------------------------------

# mwcc-rs build 2.7 emits the WRONG RELOCATION TYPES for an absolutely
# addressed global.  Measured directly out of the object file:
#
#     extern int G;                        -> (0, 109 R_PPC_EMB_SDA21, G)   OK
#     extern void h(void); h();            -> (12, 10 R_PPC_REL24,     h)   OK
#     struct {char p[8]; int v;} G; G.v    -> (2,  6  R_PPC_ADDR14,    G)   WRONG
#                                             (6,  4  R_PPC_ADDR16_HI, G)   WRONG
#
# The `lis @ha` should carry R_PPC_ADDR16_HA (5) and the `addi @l`
# R_PPC_ADDR16_LO (3); both come out exactly one higher, and the offsets point
# at the immediate halfword rather than the instruction.  Two consequences,
# and neither is reachable from the C:
#
#   * `objdiff` masks R_PPC_ADDR14 with 0xFFFC, so two bits of the `lis`
#     immediate stay unmasked and the word compares unequal no matter what the
#     candidate says;
#   * `datareloc.check_data_relocs` cannot address-check a type it does not
#     model, so even a byte-equal candidate would only be MATCH_UNVERIFIED.
#
# So an absolutely addressed global is a COMPILER refusal today, in exactly the
# sense loops are: attempting it costs a compile to be told the same thing.
# Small-data (r13/r2) globals are unaffected -- their R_PPC_EMB_SDA21 is
# correct -- and they are emitted normally.
ABS_GLOBAL_BLOCKED = True
ABS_GLOBAL_REASON = (
    "an absolutely addressed global (`lis`/`addi`) at 0x%08x: mwcc-rs 2.7 tags "
    "the pair R_PPC_ADDR14 + R_PPC_ADDR16_HI instead of ADDR16_HA + ADDR16_LO, "
    "so the operand can be neither masked nor address-checked -- see "
    "seed_cfg.ABS_GLOBAL_BLOCKED")
