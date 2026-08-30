#!/usr/bin/env python3
"""capture_common.py -- machinery shared by the two CALLEE-BOUNDARY capture tools.

Two capture tools record a function's callee boundary from the live game rather
than its write set:

    capture_spine.py       standard boundary_green    NONTERMINATING spine fns
    capture_transcript.py  standard transcript_green  ORDINARY (returning) fns

They differ only in how the run is bounded (iteration count vs. the function's
own return) and in whether a return value is part of the claim.  Everything
below is IDENTICAL between them, and lives here so the two standards cannot
drift apart in how they read a PowerPC argument register, how they bind a ROM
call site to a wasm import, or how they byte-swap a memory region.

This module was factored OUT of capture_spine.py, whose boundary_green capture
is the proven original; capture_spine.py imports every name from here and its
behaviour is unchanged.

Nothing in this file decides a verdict, opens a socket, or writes a capture --
it reads the ROM, parses wasm, allocates registers, and formats values.
"""
from __future__ import annotations

import struct
from pathlib import Path


# --------------------------------------------------------------------------
# ROM reader: the DOL straight out of the retail ISO (no extracted copy needed)
# --------------------------------------------------------------------------

class Dol:
    """boot.dol section table + address->bytes reads."""

    def __init__(self, blob: bytes):
        self.blob = blob
        offs = struct.unpack(">18I", blob[0x00:0x48])
        adrs = struct.unpack(">18I", blob[0x48:0x90])
        szs = struct.unpack(">18I", blob[0x90:0xD8])
        self.sections = [(offs[i], adrs[i], szs[i]) for i in range(18) if szs[i]]

    @classmethod
    def from_iso(cls, iso_path: Path) -> "Dol":
        """GameCube GCM: the DOL's file offset is the BE u32 at 0x420."""
        with iso_path.open("rb") as f:
            f.seek(0x420)
            dol_off = struct.unpack(">I", f.read(4))[0]
            f.seek(dol_off)
            head = f.read(0x100)
            offs = struct.unpack(">18I", head[0x00:0x48])
            szs = struct.unpack(">18I", head[0x90:0xD8])
            size = max(o + s for o, s in zip(offs, szs) if s)
            f.seek(dol_off)
            return cls(f.read(size))

    def word(self, addr: int) -> int | None:
        for off, ad, sz in self.sections:
            if ad <= addr < ad + sz:
                o = off + (addr - ad)
                return struct.unpack(">I", self.blob[o:o + 4])[0]
        return None


def s16(v: int) -> int:
    return v - 0x10000 if v & 0x8000 else v

# --------------------------------------------------------------------------
# PowerPC instruction decoding primitives
# --------------------------------------------------------------------------



STORE_OPS = {36: ("stw", 4), 38: ("stb", 1), 44: ("sth", 2), 37: ("stwu", 4)}

BRANCH_OP = 18       # b / bl / ba / bla
BCLR_OP = 19         # bclr / bcctr (+ lk forms: blrl / bctrl)
BC_OP = 16           # bc (conditional)
BLR_XO = 16          # extended opcode of bclr within op 19


def branch_target(addr: int, w: int) -> tuple[int, bool]:
    """(target, is_call) for an op-18 branch word at `addr`."""
    li = w & 0x03FFFFFC
    if li & 0x02000000:
        li -= 0x04000000
    aa, lk = (w >> 1) & 1, w & 1
    return (li if aa else addr + li) & 0xFFFFFFFF, bool(lk)


# --------------------------------------------------------------------------
# wasm import signatures + PowerPC EABI argument allocation
#
# The harness compares the wasm's actual call arguments against the capture, so
# the capture must bind to the SAME ABI the wasm module declares.  We do not
# hand-author that: the capture tools read the built module's import section,
# take each callee's wasm signature (which emcc induced from the VERBATIM Ghidra
# call site), and run the PowerPC EABI argument allocator over it.  Both sides
# therefore derive from one C declaration, and the mapping is written into the
# plan so it is auditable.
# --------------------------------------------------------------------------

VALTYPE = {0x7F: "i32", 0x7E: "i64", 0x7D: "f32", 0x7C: "f64"}


def wasm_signatures(path: Path) -> tuple[list[dict], dict]:
    """(imported functions in module order, {export name: signature})."""
    b = path.read_bytes()
    p = 8

    def leb() -> int:
        nonlocal p
        r = s = 0
        while True:
            x = b[p]
            p += 1
            r |= (x & 0x7F) << s
            s += 7
            if not x & 0x80:
                return r

    def name() -> str:
        n = leb()
        nonlocal p
        v = b[p:p + n].decode()
        p += n
        return v

    def limits() -> None:
        f = leb()
        leb()
        if f & 1:
            leb()

    types: list[dict] = []
    imports: list[dict] = []
    funcs: list[int] = []
    exports: dict = {}
    while p < len(b):
        sid = b[p]
        p += 1
        end = leb() + p
        if sid == 1:
            for _ in range(leb()):
                assert b[p] == 0x60
                p += 1
                na = leb()
                par = [VALTYPE[b[p + i]] for i in range(na)]
                p += na
                nr = leb()
                res = [VALTYPE[b[p + i]] for i in range(nr)]
                p += nr
                types.append({"params": par, "results": res})
        elif sid == 2:
            for _ in range(leb()):
                mod, fld = name(), name()
                k = b[p]
                p += 1
                if k == 0:
                    imports.append({"module": mod, "name": fld, "type": leb()})
                elif k == 1:
                    p += 1
                    limits()
                elif k == 2:
                    limits()
                elif k == 3:
                    p += 2
        elif sid == 3:
            funcs = [leb() for _ in range(leb())]
        elif sid == 7:
            for _ in range(leb()):
                nm = name()
                k = b[p]
                p += 1
                idx = leb()
                if k == 0:
                    ti = (imports[idx]["type"] if idx < len(imports)
                          else funcs[idx - len(imports)])
                    exports[nm] = types[ti]
        p = end
    out = [{"module": i["module"], "name": i["name"], **types[i["type"]]}
           for i in imports]
    return out, exports


def eabi_allocate(params: list[str]) -> list[dict]:
    """PowerPC EABI outgoing-argument allocation for one signature.

    f32/f64 -> f1..f8 in declaration order; i32 -> r3..r10 in declaration
    order; i64 -> an (odd,even) GPR pair (r3:r4, r5:r6, r7:r8, r9:r10), hi
    first; anything that overflows goes to the caller's outgoing parameter
    area, which begins at r1+8 in the caller's own frame.
    """
    gpr, fpr, stk = 3, 1, 8
    out = []
    for i, t in enumerate(params):
        if t in ("f32", "f64"):
            if fpr <= 8:
                out.append({"i": i, "t": t, "src": f"f{fpr}"})
                fpr += 1
            else:
                stk = (stk + 7) & ~7
                out.append({"i": i, "t": t, "src": f"stack+{stk}"})
                stk += 8
        elif t == "i64":
            if gpr % 2 == 0:
                gpr += 1
            if gpr + 1 <= 10:
                out.append({"i": i, "t": t, "src": f"r{gpr}:r{gpr + 1}"})
                gpr += 2
            else:
                stk = (stk + 7) & ~7
                out.append({"i": i, "t": t, "src": f"stack+{stk}"})
                stk += 8
        else:
            if gpr <= 10:
                out.append({"i": i, "t": t, "src": f"r{gpr}"})
                gpr += 1
            else:
                out.append({"i": i, "t": t, "src": f"stack+{stk}"})
                stk += 4
    return out


def eabi_return(results: list[str]) -> dict | None:
    if not results:
        return None
    t = results[0]
    if t in ("f32", "f64"):
        return {"t": t, "src": "f1"}
    if t == "i64":
        return {"t": t, "src": "r3:r4"}
    return {"t": t, "src": "r3"}


# --------------------------------------------------------------------------
# register reads + JSON value boxing
#
# Endianness: console RAM is big-endian PowerPC; the wasm arena is
# little-endian.  Memory bytes are therefore emitted ELEMENT-WISE byte-swapped
# at the region's declared `elem_width`, the same rule as
# research/decomp/oracle-harness/gen_arena_rom_provenance.py.  Register VALUES
# need no swap -- they are read as integers, not bytes.
# --------------------------------------------------------------------------

def swap_elems(raw: bytes, elem_width: int) -> bytes:
    if elem_width <= 1:
        return raw
    return b"".join(raw[i:i + elem_width][::-1]
                    for i in range(0, len(raw), elem_width))


class Regs:
    """Lazily-read register file for one halted stop."""

    def __init__(self, rsp):
        self.rsp = rsp
        self._g: dict[int, int] = {}
        self._f: dict[int, int] = {}

    def gpr(self, n: int) -> int:
        if n not in self._g:
            self._g[n] = self.rsp.read_gpr(n) & 0xFFFFFFFF
        return self._g[n]

    def fpr_bits(self, n: int) -> int:
        if n not in self._f:
            self._f[n] = self.rsp.read_fpr_raw(n)
        return self._f[n]


def box_float(v: float, t: str) -> object:
    """JSON has no NaN/Infinity, and a PPC argument register full of residue is
    routinely one of them.  A non-finite float is therefore carried BOXED and
    bit-exact -- {"t":"f64","bits":"<hex>"} -- which spine_schema 1 defines and
    run-spine.mjs unboxes.  Finite values stay plain JSON numbers so a capture
    is still readable."""
    if v == v and v not in (float("inf"), float("-inf")):
        return v
    if t == "f32":
        return {"t": "f32", "bits": f"{struct.unpack('>I', struct.pack('>f', v))[0]:08x}"}
    return {"t": "f64", "bits": f"{struct.unpack('>Q', struct.pack('>d', v))[0]:016x}"}


def read_arg(regs: Regs, spec: dict) -> object:
    src, t = spec["src"], spec["t"]
    if src.startswith("stack+"):
        off = int(src.split("+")[1])
        raw = regs.rsp.read_mem((regs.gpr(1) + off) & 0xFFFFFFFF,
                                8 if t in ("f64", "i64") else 4)
        if t == "f64":
            return box_float(struct.unpack(">d", raw)[0], "f64")
        if t == "f32":
            return box_float(struct.unpack(">f", raw[:4])[0], "f32")
        if t == "i64":
            return str(struct.unpack(">Q", raw)[0])
        return struct.unpack(">I", raw[:4])[0]
    if src.startswith("f"):
        bits = regs.fpr_bits(int(src[1:]))
        dv = struct.unpack(">d", struct.pack(">Q", bits))[0]
        if t == "f32":
            # a PPC FPR always holds a double; a single-precision arg is that
            # double rounded to f32 by the callee's own convention
            return box_float(struct.unpack(">f", struct.pack(">f", dv))[0], "f32")
        return box_float(dv, "f64")
    if ":" in src:                                   # i64 register pair, hi:lo
        hi, lo = (int(x[1:]) for x in src.split(":"))
        return str(((regs.gpr(hi) << 32) | regs.gpr(lo)) & 0xFFFFFFFFFFFFFFFF)
    return regs.gpr(int(src[1:]))

def read_ret(regs: Regs, spec: dict | None) -> object:
    if spec is None:
        return None
    if spec["t"] in ("f32", "f64"):
        return box_float(struct.unpack(">d", struct.pack(">Q", regs.fpr_bits(1)))[0],
                         spec["t"])
    if spec["t"] == "i64":
        return {"t": "i64", "v": str(((regs.gpr(3) << 32) | regs.gpr(4))
                                     & 0xFFFFFFFFFFFFFFFF)}
    return regs.gpr(3)
