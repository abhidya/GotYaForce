#!/usr/bin/env python3
"""ppcasm.py -- a MINIMAL PowerPC assembler, used as a STAND-IN BACKEND.

WHAT THIS IS FOR, AND WHAT IT IS NOT

The matching-decompilation loop is:

    candidate C  --[mwcceppc]-->  .o  --[objdiff]-->  MATCH / MISMATCH

`mwcceppc.exe` is proprietary Metrowerks software and is NOT PRESENT ON THIS
MACHINE (see docs/matching-decompilation-spike.md §1).  Without it the middle
step cannot run, and therefore the decisive test -- "write C, compile it, get
the retail bytes back" -- cannot be performed here.

This module exists so that the OTHER TWO STEPS can still be proven.  It
assembles a small, explicitly-listed subset of PowerPC into the same
big-endian words a compiler would emit, so the harness can be driven
end-to-end with a real target function and a real byte comparison.

**Assembling the instructions and then observing that they equal the retail
instructions PROVES NOTHING ABOUT MATCHABILITY.**  It is the same information
written twice.  Its only claim is that the extractor, the encoder, the
comparator and the negative control all work.  Read §3 of the spike doc for the
distinction, which is load-bearing.

Supported forms are exactly those needed by the spike's target functions.
Anything else raises -- silently emitting a wrong encoding would corrupt the
one thing this file is for.
"""
from __future__ import annotations

import re
import struct
from pathlib import Path


class AsmError(Exception):
    pass


def _r(tok):
    tok = tok.strip().rstrip(",")
    m = re.match(r"^[rf](\d{1,2})$", tok)
    if not m:
        raise AsmError("not a register: %r" % tok)
    v = int(m.group(1))
    if not 0 <= v <= 31:
        raise AsmError("register out of range: %r" % tok)
    return v


def _imm(tok):
    tok = tok.strip().rstrip(",")
    neg = tok.startswith("-")
    if neg:
        tok = tok[1:]
    v = int(tok, 16) if tok.lower().startswith("0x") else int(tok, 10)
    return -v if neg else v


def _dform(op, rs, ra, d):
    return ((op & 0x3F) << 26) | ((rs & 31) << 21) | ((ra & 31) << 16) | (d & 0xFFFF)


def _xform(op, rs, ra, rb, xo, rc=0):
    return ((op & 0x3F) << 26) | ((rs & 31) << 21) | ((ra & 31) << 16) | \
           ((rb & 31) << 11) | ((xo & 0x3FF) << 1) | (rc & 1)


def _xoform(op, rd, ra, rb, oe, xo, rc=0):
    return ((op & 0x3F) << 26) | ((rd & 31) << 21) | ((ra & 31) << 16) | \
           ((rb & 31) << 11) | ((oe & 1) << 10) | ((xo & 0x1FF) << 1) | (rc & 1)


# D-form: mnemonic -> primary opcode.  Operand order is (rS/rD, d(rA)) for
# loads/stores and (rD, rA, imm) for arithmetic.
DFORM_MEM = {
    "lwz": 32, "lwzu": 33, "lbz": 34, "lbzu": 35,
    "stw": 36, "stwu": 37, "stb": 38, "stbu": 39,
    "lhz": 40, "lhzu": 41, "lha": 42, "lhau": 43,
    "sth": 44, "sthu": 45, "lmw": 46, "stmw": 47,
    "lfs": 48, "lfsu": 49, "lfd": 50, "lfdu": 51,
    "stfs": 52, "stfsu": 53, "stfd": 54, "stfdu": 55,
}
DFORM_ARITH = {"addi": 14, "addic": 12, "addic.": 13, "addis": 15,
               "mulli": 7, "subfic": 8}
DFORM_LOGIC = {"ori": 24, "oris": 25, "xori": 26, "xoris": 27,
               "andi.": 28, "andis.": 29}
DFORM_CMP = {"cmpwi": 11, "cmplwi": 10}

XFORM = {  # mnemonic -> (primary, xo, rc)  operands (rA, rS, rB) "logical" order
    "and": (31, 28, 0), "and.": (31, 28, 1),
    "andc": (31, 60, 0), "or": (31, 444, 0), "or.": (31, 444, 1),
    "orc": (31, 412, 0), "xor": (31, 316, 0), "nand": (31, 476, 0),
    "nor": (31, 124, 0), "eqv": (31, 284, 0),
    "slw": (31, 24, 0), "srw": (31, 536, 0), "sraw": (31, 792, 0),
    "extsb": (31, 954, 0), "extsh": (31, 922, 0), "cntlzw": (31, 26, 0),
}

XOFORM = {  # (primary, oe, xo, rc)  operands (rD, rA, rB)
    "add": (31, 0, 266, 0), "add.": (31, 0, 266, 1),
    "addc": (31, 0, 10, 0), "adde": (31, 0, 138, 0),
    "subf": (31, 0, 40, 0), "subf.": (31, 0, 40, 1),
    "subfc": (31, 0, 8, 0), "subfe": (31, 0, 136, 0),
    "mullw": (31, 0, 235, 0), "divw": (31, 0, 491, 0), "divwu": (31, 0, 459, 0),
    "neg": (31, 0, 104, 0),
}

XFORM_MEM = {  # indexed loads/stores (rS, rA, rB)
    "lwzx": 23, "stwx": 151, "lbzx": 87, "stbx": 215,
    "lhzx": 279, "sthx": 407,
}

CMP_X = {"cmpw": (31, 0), "cmplw": (31, 32)}


def assemble_line(line, addr, labels=None, pass2=False):
    """One instruction -> a 32-bit word, or None for a blank/label/directive."""
    s = line.split("#")[0].split("/*")[0].strip()
    if not s or s.endswith(":"):
        return None
    parts = s.split(None, 1)
    m = parts[0].lower()
    ops = [o.strip() for o in parts[1].split(",")] if len(parts) > 1 else []

    if m == "nop":
        return 0x60000000
    if m == "blr":
        return 0x4E800020
    if m == "blrl":
        return 0x4E800021
    if m == "bctr":
        return 0x4E800420
    if m == "bctrl":
        return 0x4E800421
    if m == "mflr":
        return _xform(31, _r(ops[0]), 8, 0, 339)
    if m == "mtlr":
        return _xform(31, _r(ops[0]), 8, 0, 467)
    if m == "mfctr":
        return _xform(31, _r(ops[0]), 9, 0, 339)
    if m == "mtctr":
        return _xform(31, _r(ops[0]), 9, 0, 467)
    if m in ("li", "lis"):
        rd = _r(ops[0])
        v = _imm(ops[1])
        return _dform(14 if m == "li" else 15, rd, 0, v)
    if m == "mr":
        rs = _r(ops[1])
        return _xform(31, rs, _r(ops[0]), rs, 444)
    if m == "not":
        rs = _r(ops[1])
        return _xform(31, rs, _r(ops[0]), rs, 124)
    if m in DFORM_ARITH:
        return _dform(DFORM_ARITH[m], _r(ops[0]), _r(ops[1]), _imm(ops[2]))
    if m in DFORM_LOGIC:
        # ori rA, rS, imm  -- note the operand order is (rA, rS, imm)
        return _dform(DFORM_LOGIC[m], _r(ops[1]), _r(ops[0]), _imm(ops[2]))
    if m in DFORM_CMP:
        return _dform(DFORM_CMP[m], 0, _r(ops[0]), _imm(ops[1]))
    if m in DFORM_MEM:
        mm = re.match(r"^(-?(?:0x)?[0-9a-fA-F]+)\(([rf]\d{1,2})\)$", ops[1])
        if not mm:
            raise AsmError("bad memory operand: %r" % ops[1])
        return _dform(DFORM_MEM[m], _r(ops[0]), _r(mm.group(2)), _imm(mm.group(1)))
    if m in XFORM_MEM:
        mm = re.match(r"^([rf]\d{1,2})\s*,\s*([rf]\d{1,2})$", ", ".join(ops[1:]))
        return _xform(31, _r(ops[0]), _r(ops[1]), _r(ops[2]), XFORM_MEM[m])
    if m in XFORM:
        p, xo, rc = XFORM[m]
        if m in ("extsb", "extsh", "cntlzw"):
            return _xform(p, _r(ops[1]), _r(ops[0]), 0, xo, rc)
        # and rA, rS, rB
        return _xform(p, _r(ops[1]), _r(ops[0]), _r(ops[2]), xo, rc)
    if m in XOFORM:
        p, oe, xo, rc = XOFORM[m]
        if m == "neg":
            return _xoform(p, _r(ops[0]), _r(ops[1]), 0, oe, xo, rc)
        return _xoform(p, _r(ops[0]), _r(ops[1]), _r(ops[2]), oe, xo, rc)
    if m in CMP_X:
        p, xo = CMP_X[m]
        return _xform(p, 0, _r(ops[0]), _r(ops[1]), xo)
    if m in ("rlwinm", "rlwinm.", "clrlwi", "clrrwi", "srwi", "slwi", "rotlwi"):
        rc = 1 if m.endswith(".") else 0
        if m in ("rlwinm", "rlwinm."):
            ra, rs, sh, mb, me = (_r(ops[0]), _r(ops[1]), _imm(ops[2]),
                                  _imm(ops[3]), _imm(ops[4]))
        elif m == "clrlwi":
            ra, rs, n = _r(ops[0]), _r(ops[1]), _imm(ops[2])
            sh, mb, me = 0, n, 31
        elif m == "clrrwi":
            ra, rs, n = _r(ops[0]), _r(ops[1]), _imm(ops[2])
            sh, mb, me = 0, 0, 31 - n
        elif m == "srwi":
            ra, rs, n = _r(ops[0]), _r(ops[1]), _imm(ops[2])
            sh, mb, me = 32 - n, n, 31
        elif m == "slwi":
            ra, rs, n = _r(ops[0]), _r(ops[1]), _imm(ops[2])
            sh, mb, me = n, 0, 31 - n
        else:
            ra, rs, n = _r(ops[0]), _r(ops[1]), _imm(ops[2])
            sh, mb, me = n, 0, 31
        return ((21) << 26) | ((rs & 31) << 21) | ((ra & 31) << 16) | \
               ((sh & 31) << 11) | ((mb & 31) << 6) | ((me & 31) << 1) | rc
    if m in ("b", "bl"):
        if labels is None or ops[0] not in labels:
            if not pass2:
                return 0
            raise AsmError("unknown branch target %r" % ops[0])
        tgt = labels[ops[0]]
        li = (tgt - addr) & 0x03FFFFFC
        return (18 << 26) | li | (1 if m == "bl" else 0)
    if m in ("beq", "bne", "blt", "bge", "bgt", "ble"):
        bo_bi = {"beq": (12, 2), "bne": (4, 2), "blt": (12, 0), "bge": (4, 0),
                 "bgt": (12, 1), "ble": (4, 1)}[m]
        if labels is None or ops[0] not in labels:
            if not pass2:
                return (16 << 26) | (bo_bi[0] << 21) | (bo_bi[1] << 16)
            raise AsmError("unknown branch target %r" % ops[0])
        bd = (labels[ops[0]] - addr) & 0xFFFC
        return (16 << 26) | (bo_bi[0] << 21) | (bo_bi[1] << 16) | bd
    if m == ".4byte":
        return _imm(ops[0]) & 0xFFFFFFFF
    raise AsmError("unsupported mnemonic %r (line: %r)" % (m, line.strip()))


def assemble(text, base_addr=0):
    """Two-pass assemble. Returns (bytes, {label: addr})."""
    lines = text.splitlines()
    labels = {}
    addr = base_addr
    for ln in lines:
        s = ln.split("#")[0].strip()
        if not s:
            continue
        if s.endswith(":"):
            labels[s[:-1]] = addr
            continue
        addr += 4
    out = bytearray()
    addr = base_addr
    for ln in lines:
        w = assemble_line(ln, addr, labels, pass2=True)
        if w is None:
            continue
        out += struct.pack(">I", w & 0xFFFFFFFF)
        addr += 4
    return bytes(out), labels


def assemble_file(path, base_addr=0):
    return assemble(Path(path).read_text(), base_addr)


if __name__ == "__main__":
    import sys
    b, lab = assemble_file(sys.argv[1], int(sys.argv[2], 16) if len(sys.argv) > 2 else 0)
    print(b.hex())
