#!/usr/bin/env python3
"""ppc_recomp.py -- a minimal, mechanical PowerPC -> C static recompiler.

FEASIBILITY-SPIKE SCOPE.  This is not a whole-program recompiler.  It is the
smallest thing that answers the spike's question: can a PowerPC function be
translated into C by TABLE LOOKUP -- no decompiler, no type inference, no
model, no human -- and reproduce the console's observable behaviour?

WHAT IT DOES
    1. reads boot.dol out of the retail GCM (same layout logic as
       research/tools/dolphin-trace/capture_common.py:Dol)
    2. finds the extent of one function by following its own branches
    3. decodes every word from the RAW ENCODING (not from a disassembler's
       mnemonic string, and not from Ghidra) via a translation table
    4. emits one C statement per instruction against the register file and
       memory accessors in rt/ppc_rt.h, with a `goto` label at every branch
       target

WHAT IT DELIBERATELY DOES NOT DO
    - It never guesses.  An opcode with no table entry is a hard generator
      error naming the address and the encoding.  There is no "best effort".
    - It infers no types, no parameters, no return value, no struct layout.
      A function is `void f(ppc_ctx *)`; arguments live in r3.. because the
      ABI put them there, not because anything decided a signature.
    - It performs no source rewrites.  MMIO is a range test inside the memory
      accessor at runtime, so there is no "write-gather-pipe lowering" pass and
      nothing can fail closed on an EA it could not constant-fold.

Usage:
    python ppc_recomp.py --iso "D:/GotYaForce/Gotcha Force.iso" \
        --func 0x80027c34 --name zz_0027c34_ --out generated/zz_0027c34_.c
"""
from __future__ import annotations

import argparse
import collections
import json
import struct
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from dol_inventory import Dol  # noqa: E402


class Unsupported(Exception):
    def __init__(self, addr, word, why):
        Exception.__init__(self, "0x%08x: 0x%08x -- %s" % (addr, word, why))
        self.addr, self.word, self.why = addr, word, why


# --------------------------------------------------------------------------
# field extractors (MSB-numbered PowerPC fields, expressed LSB-first)
# --------------------------------------------------------------------------

def OP(w):  return w >> 26
def RD(w):  return (w >> 21) & 0x1F
def RS(w):  return (w >> 21) & 0x1F
def RA(w):  return (w >> 16) & 0x1F
def RB(w):  return (w >> 11) & 0x1F
def RC_(w): return (w >> 6) & 0x1F          # frC in A-form
def SIMM(w):
    v = w & 0xFFFF
    return v - 0x10000 if v & 0x8000 else v
def UIMM(w): return w & 0xFFFF
def XO10(w): return (w >> 1) & 0x3FF
def XO5(w):  return (w >> 1) & 0x1F
def RCBIT(w): return w & 1
def OE(w):   return (w >> 10) & 1
def CRFD(w): return (w >> 23) & 7
def CRFS(w): return (w >> 18) & 7
def BO(w):   return (w >> 21) & 0x1F
def BI(w):   return (w >> 16) & 0x1F
def BD(w):
    v = w & 0xFFFC
    return v - 0x10000 if v & 0x8000 else v
def LI(w):
    v = w & 0x03FFFFFC
    return v - 0x04000000 if v & 0x02000000 else v
def AA(w): return (w >> 1) & 1
def LK(w): return w & 1
def MB(w): return (w >> 6) & 0x1F
def ME(w): return (w >> 1) & 0x1F
def SH(w): return (w >> 11) & 0x1F
def SPRN(w): return ((w >> 16) & 0x1F) | (((w >> 11) & 0x1F) << 5)


def spr_slot(n):
    """The C lvalue for an SPR the register file models directly, else None.

    GQR0..7 (SPR 912..919) are modelled because they are the paired-single
    load/store quantisation registers -- psq_l's scale and type come from them,
    so a recompiler that drops them cannot translate psq_* at all.
    """
    if n == 1:
        return "c->xer"
    if n == 8:
        return "c->lr"
    if n == 9:
        return "c->ctr"
    if 912 <= n <= 919:
        return "c->gqr[%d]" % (n - 912)
    return None


def ra0(w):
    """rA|0 -- register A, or the literal 0 when rA is r0 in a D/X-form EA."""
    a = RA(w)
    return "0u" if a == 0 else "c->r[%d]" % a


def ea_d(w):
    d = SIMM(w)
    return "(%s + (uint32_t)%d)" % (ra0(w), d)


def ea_x(w):
    return "(%s + c->r[%d])" % (ra0(w), RB(w))


def rc(w, res):
    return " ppc_rc(c, %s);" % res if RCBIT(w) else ""


# --------------------------------------------------------------------------
# the translation table
#
# Each handler returns (list_of_C_statements, flow) where flow is one of
#   ("fall",)                 next instruction
#   ("jmp", target)           unconditional intra-function branch
#   ("cond", target)          conditional; falls through when not taken
#   ("ret",)                  blr / rfi -- function ends
#   ("tail", target)          unconditional branch outside the function
# --------------------------------------------------------------------------

SIMPLE_D = {
    #  op : (name, C expression template using A=ra0, I=SIMM/UIMM)
    14: ("addi",   "%(A)s + (uint32_t)%(S)d"),
    15: ("addis",  "%(A)s + (uint32_t)%(U)d"),
    7:  ("mulli",  "(uint32_t)((int32_t)c->r[%(a)d] * %(S)d)"),
}


def x_arith(w):
    """op 31 arithmetic/logical X- and XO-forms."""
    xo = XO10(w)
    d, a, b, s = RD(w), RA(w), RB(w), RS(w)
    A, B, S = "c->r[%d]" % a, "c->r[%d]" % b, "c->r[%d]" % s
    D = "c->r[%d]" % d
    # XO-form (bit 10 is OE) -- mask it off for the arithmetic group
    xo_noe = xo & 0x1FF
    if xo in (0, 32):                       # cmp / cmpl
        if xo == 0:
            return (["ppc_cmp(c, %d, (int32_t)%s, (int32_t)%s);" % (CRFD(w), A, B)], ("fall",))
        return (["ppc_cmpl(c, %d, %s, %s);" % (CRFD(w), A, B)], ("fall",))
    binop = {
        266: ("add",    "%s + %s" % (A, B)),
        40:  ("subf",   "%s - %s" % (B, A)),
        235: ("mullw",  "(uint32_t)((int32_t)%s * (int32_t)%s)" % (A, B)),
        75:  ("mulhw",  "(uint32_t)(((int64_t)(int32_t)%s * (int32_t)%s) >> 32)" % (A, B)),
        11:  ("mulhwu", "(uint32_t)(((uint64_t)%s * %s) >> 32)" % (A, B)),
        491: ("divw",   "(uint32_t)(%s ? (int32_t)%s / (int32_t)%s : 0)" % (B, A, B)),
        459: ("divwu",  "(%s ? %s / %s : 0u)" % (B, A, B)),
        28:  ("and",    "%s & %s" % (S, B)),
        444: ("or",     "%s | %s" % (S, B)),
        316: ("xor",    "%s ^ %s" % (S, B)),
        124: ("nor",    "~(%s | %s)" % (S, B)),
        476: ("nand",   "~(%s & %s)" % (S, B)),
        60:  ("andc",   "%s & ~%s" % (S, B)),
        412: ("orc",    "%s | ~%s" % (S, B)),
        284: ("eqv",    "~(%s ^ %s)" % (S, B)),
        24:  ("slw",    "((c->r[%d] & 0x20u) ? 0u : (%s << (c->r[%d] & 31)))" % (b, S, b)),
        536: ("srw",    "((c->r[%d] & 0x20u) ? 0u : (%s >> (c->r[%d] & 31)))" % (b, S, b)),
        104: ("neg",    "(uint32_t)(-(int32_t)%s)" % A),
        954: ("extsb",  "(uint32_t)(int32_t)(int8_t)%s" % S),
        922: ("extsh",  "(uint32_t)(int32_t)(int16_t)%s" % S),
        26:  ("cntlzw", "ppc_cntlzw(%s)" % S),
        144: ("mtcrf",  None),
    }
    for key in (xo, xo_noe):
        if key in binop and binop[key][1] is not None:
            name, expr = binop[key]
            tgt = D if key in (266, 40, 235, 75, 11, 491, 459, 104) else "c->r[%d]" % a
            return (["%s = %s;%s" % (tgt, expr, rc(w, tgt))], ("fall",))
    if xo == 824:                            # srawi
        n = SH(w)
        ca = ("((v < 0) && ((v & 0x%08x) != 0))" % ((1 << n) - 1)) if n else "0"
        return ([("{ int32_t v = (int32_t)%s; ppc_setca(c, %s); c->r[%d] = "
                  "(uint32_t)(v >> %d);%s }")
                 % (S, ca, a, n, rc(w, "c->r[%d]" % a))], ("fall",))
    if xo == 200:                            # subfze
        return ([("{ uint64_t t = (uint64_t)(uint32_t)(~%s) + "
                  "((c->xer & PPC_XER_CA) ? 1u : 0u); ppc_setca(c, (t >> 32) != 0); "
                  "%s = (uint32_t)t;%s }") % (A, D, rc(w, D))], ("fall",))
    if xo == 371:                            # mftb -- the 64-bit time base
        n = SPRN(w)
        return (["%s = gf_host_timebase(c, %d);" % (D, n)], ("fall",))
    if xo in (83, 146):                      # mfmsr / mtmsr
        # Supervisor state.  The OS boot path uses these; nothing a high-level
        # host runs does.  Modelled as an explicit refusal, never a guess.
        return (["ppc_supervisor(c, \"%s\");" % ("mfmsr" if xo == 83 else "mtmsr")],
                ("fall",))
    if xo == 470:                            # dcbi (supervisor cache invalidate)
        return (["/* dcbi: no-op for a recompiler */"], ("fall",))
    if xo == 792:                            # sraw
        return ([("{ uint32_t sh = c->r[%d] & 0x3F; int32_t v = (int32_t)%s; "
                  "if (sh > 31) sh = 31; ppc_setca(c, (v < 0) && ((v & (int32_t)((1u<<sh)-1u)) != 0)); "
                  "c->r[%d] = (uint32_t)(v >> sh);%s }")
                 % (b, S, a, rc(w, "c->r[%d]" % a))], ("fall",))
    if xo == 10:                             # addc
        return ([("{ uint64_t t = (uint64_t)%s + (uint64_t)%s; ppc_setca(c, (t >> 32) != 0); "
                  "%s = (uint32_t)t;%s }") % (A, B, D, rc(w, D))], ("fall",))
    if xo == 138:                            # adde
        return ([("{ uint64_t t = (uint64_t)%s + (uint64_t)%s + ((c->xer & PPC_XER_CA) ? 1u : 0u); "
                  "ppc_setca(c, (t >> 32) != 0); %s = (uint32_t)t;%s }") % (A, B, D, rc(w, D))],
                ("fall",))
    if xo == 8:                              # subfc
        return ([("{ uint64_t t = (uint64_t)(uint32_t)(~%s) + (uint64_t)%s + 1u; "
                  "ppc_setca(c, (t >> 32) != 0); %s = (uint32_t)t;%s }") % (A, B, D, rc(w, D))],
                ("fall",))
    if xo == 136:                            # subfe
        return ([("{ uint64_t t = (uint64_t)(uint32_t)(~%s) + (uint64_t)%s + "
                  "((c->xer & PPC_XER_CA) ? 1u : 0u); ppc_setca(c, (t >> 32) != 0); "
                  "%s = (uint32_t)t;%s }") % (A, B, D, rc(w, D))], ("fall",))
    if xo == 202:                            # addze
        return ([("{ uint64_t t = (uint64_t)%s + ((c->xer & PPC_XER_CA) ? 1u : 0u); "
                  "ppc_setca(c, (t >> 32) != 0); %s = (uint32_t)t;%s }") % (A, D, rc(w, D))],
                ("fall",))
    if xo == 234:                            # addme
        return ([("{ uint64_t t = (uint64_t)%s + 0xFFFFFFFFu + ((c->xer & PPC_XER_CA) ? 1u : 0u); "
                  "ppc_setca(c, (t >> 32) != 0); %s = (uint32_t)t;%s }") % (A, D, rc(w, D))],
                ("fall",))
    if xo == 19:                             # mfcr
        return (["%s = c->cr;" % D], ("fall",))
    if xo == 144:                            # mtcrf
        mask = (w >> 12) & 0xFF
        m = 0
        for i in range(8):
            if mask & (1 << (7 - i)):
                m |= 0xF << (28 - 4 * i)
        return (["c->cr = (c->cr & ~0x%08xu) | (%s & 0x%08xu);" % (m, S, m)], ("fall",))
    if xo == 339:                            # mfspr
        n = SPRN(w)
        src = spr_slot(n)
        if src is None:
            # Not a guess and not a refusal: an explicit, named seam call.  The
            # host decides what SPR n means (HID0, L2CR, DEC, ...); the
            # translation records only that the ROM asked for it.
            return (["%s = gf_host_mfspr(c, %d);" % (D, n)], ("fall",))
        return (["%s = %s;" % (D, src)], ("fall",))
    if xo == 467:                            # mtspr
        n = SPRN(w)
        dst = spr_slot(n)
        if dst is None:
            return (["gf_host_mtspr(c, %d, %s);" % (n, S)], ("fall",))
        return (["%s = %s;" % (dst, S)], ("fall",))
    if xo in (598, 854, 150, 982, 1014, 278, 246, 86, 54, 4):
        # sync / eieio / isync / icbi / dcbz / dcbt / dcbtst / dcbf / dcbst
        if xo == 1014:                       # dcbz: SEMANTIC -- zeroes 32 bytes
            return ([("{ uint32_t ea = %s & ~31u; for (int i = 0; i < 32; i++) "
                      "ppc_w8(c, ea + i, 0); }") % ea_x(w)], ("fall",))
        return (["/* cache/sync hint: no-op for a recompiler */"], ("fall",))
    raise Unsupported(0, w, "op 31 XO=%d not in the translation table" % xo)


X_LOADS = {   # xo : (C reader, dest kind)
    23:  ("ppc_r32(c, %s)", "gpr"),          # lwzx
    87:  ("ppc_r8(c, %s)", "gpr"),           # lbzx
    279: ("ppc_r16(c, %s)", "gpr"),          # lhzx
    343: ("(uint32_t)(int32_t)(int16_t)ppc_r16(c, %s)", "gpr"),   # lhax
    535: ("ppc_u322f(ppc_r32(c, %s))", "fpr"),                    # lfsx
    599: ("ppc_u642d(ppc_r64(c, %s))", "fpr"),                    # lfdx
}
X_STORES = {
    151: ("ppc_w32(c, %s, c->r[%d]);", "gpr"),      # stwx
    215: ("ppc_w8(c, %s, (uint8_t)c->r[%d]);", "gpr"),   # stbx
    407: ("ppc_w16(c, %s, (uint16_t)c->r[%d]);", "gpr"),  # sthx
    663: ("ppc_stfs(c, %s, c->f[%d]);", "fpr"),     # stfsx
    727: ("ppc_w64(c, %s, ppc_d2u64(c->f[%d]));", "fpr"),  # stfdx
}

D_LOADS = {   # op : (C reader template, dest kind, update?)
    32: ("ppc_r32(c, %s)", "gpr", 0),                                  # lwz
    33: ("ppc_r32(c, %s)", "gpr", 1),                                  # lwzu
    34: ("(uint32_t)ppc_r8(c, %s)", "gpr", 0),                         # lbz
    35: ("(uint32_t)ppc_r8(c, %s)", "gpr", 1),                         # lbzu
    40: ("(uint32_t)ppc_r16(c, %s)", "gpr", 0),                        # lhz
    41: ("(uint32_t)ppc_r16(c, %s)", "gpr", 1),                        # lhzu
    42: ("(uint32_t)(int32_t)(int16_t)ppc_r16(c, %s)", "gpr", 0),      # lha
    43: ("(uint32_t)(int32_t)(int16_t)ppc_r16(c, %s)", "gpr", 1),      # lhau
    48: ("ppc_u322f(ppc_r32(c, %s))", "fpr", 0),                       # lfs
    49: ("ppc_u322f(ppc_r32(c, %s))", "fpr", 1),                       # lfsu
    50: ("ppc_u642d(ppc_r64(c, %s))", "fpr", 0),                       # lfd
    51: ("ppc_u642d(ppc_r64(c, %s))", "fpr", 1),                       # lfdu
}
D_STORES = {  # op : (C writer template, src kind, update?)
    36: ("ppc_w32(c, %s, c->r[%d]);", "gpr", 0),                       # stw
    37: ("ppc_w32(c, %s, c->r[%d]);", "gpr", 1),                       # stwu
    38: ("ppc_w8(c, %s, (uint8_t)c->r[%d]);", "gpr", 0),               # stb
    39: ("ppc_w8(c, %s, (uint8_t)c->r[%d]);", "gpr", 1),               # stbu
    44: ("ppc_w16(c, %s, (uint16_t)c->r[%d]);", "gpr", 0),             # sth
    45: ("ppc_w16(c, %s, (uint16_t)c->r[%d]);", "gpr", 1),             # sthu
    52: ("ppc_stfs(c, %s, c->f[%d]);", "fpr", 0),                      # stfs
    53: ("ppc_stfs(c, %s, c->f[%d]);", "fpr", 1),                      # stfsu
    54: ("ppc_w64(c, %s, ppc_d2u64(c->f[%d]));", "fpr", 0),            # stfd
    55: ("ppc_w64(c, %s, ppc_d2u64(c->f[%d]));", "fpr", 1),            # stfdu
}

# A-form floating point.  `single` selects the float-rounded variants.
A_FORM = {
    18: ("fdiv",  "%(A)s / %(B)s"),
    20: ("fsub",  "%(A)s - %(B)s"),
    21: ("fadd",  "%(A)s + %(B)s"),
    22: ("fsqrt", "__builtin_sqrt(%(A)s)"),
    25: ("fmul",  "%(A)s * %(C)s"),
    23: ("fsel",  "(%(A)s >= 0.0) ? %(C)s : %(B)s"),
    # The fused forms round ONCE on PowerPC.  Writing them as a*c+b in C rounds
    # TWICE and is a different number.  __builtin_fma is the correct spelling
    # and is the whole content of the "FMA" attention class in the inventory.
    28: ("fmsub",  "__builtin_fma(%(A)s, %(C)s, -(%(B)s))"),
    29: ("fmadd",  "__builtin_fma(%(A)s, %(C)s, %(B)s)"),
    30: ("fnmsub", "-__builtin_fma(%(A)s, %(C)s, -(%(B)s))"),
    31: ("fnmadd", "-__builtin_fma(%(A)s, %(C)s, %(B)s)"),
}


def translate(addr, w, fn_lo, fn_hi):
    op = OP(w)
    d, a, b, s = RD(w), RA(w), RB(w), RS(w)

    # ---- D-form integer -------------------------------------------------
    if op == 14:                                    # addi / li
        if a == 0:
            return (["c->r[%d] = (uint32_t)%d;" % (d, SIMM(w))], ("fall",))
        return (["c->r[%d] = c->r[%d] + (uint32_t)%d;" % (d, a, SIMM(w))], ("fall",))
    if op == 15:                                    # addis / lis
        v = (UIMM(w) << 16) & 0xFFFFFFFF
        if a == 0:
            return (["c->r[%d] = 0x%08xu;" % (d, v)], ("fall",))
        return (["c->r[%d] = c->r[%d] + 0x%08xu;" % (d, a, v)], ("fall",))
    if op == 12 or op == 13:                        # addic / addic.
        stmt = ("{ uint64_t t = (uint64_t)c->r[%d] + (uint64_t)(uint32_t)%d; "
                "ppc_setca(c, (t >> 32) != 0); c->r[%d] = (uint32_t)t;%s }"
                % (a, SIMM(w), d, " ppc_rc(c, c->r[%d]);" % d if op == 13 else ""))
        return ([stmt], ("fall",))
    if op == 8:                                     # subfic
        return ([("{ uint64_t t = (uint64_t)(uint32_t)(~c->r[%d]) + (uint64_t)(uint32_t)%d + 1u; "
                  "ppc_setca(c, (t >> 32) != 0); c->r[%d] = (uint32_t)t; }") % (a, SIMM(w), d)],
                ("fall",))
    if op == 7:                                     # mulli
        return (["c->r[%d] = (uint32_t)((int32_t)c->r[%d] * %d);" % (d, a, SIMM(w))], ("fall",))
    if op == 11:                                    # cmpi / cmpwi
        return (["ppc_cmp(c, %d, (int32_t)c->r[%d], %d);" % (CRFD(w), a, SIMM(w))], ("fall",))
    if op == 10:                                    # cmpli / cmplwi
        return (["ppc_cmpl(c, %d, c->r[%d], 0x%xu);" % (CRFD(w), a, UIMM(w))], ("fall",))
    if op in (24, 25, 26, 27, 28, 29):              # ori/oris/xori/xoris/andi./andis.
        imm = UIMM(w) if op in (24, 26, 28) else (UIMM(w) << 16) & 0xFFFFFFFF
        oper = {24: "|", 25: "|", 26: "^", 27: "^", 28: "&", 29: "&"}[op]
        stmt = "c->r[%d] = c->r[%d] %s 0x%08xu;" % (a, s, oper, imm)
        if op in (28, 29):
            stmt += " ppc_rc(c, c->r[%d]);" % a
        return ([stmt], ("fall",))

    # ---- rotate / mask --------------------------------------------------
    if op == 21:                                    # rlwinm (and every alias)
        m = mask32(MB(w), ME(w))
        return (["c->r[%d] = ppc_rotl32(c->r[%d], %d) & 0x%08xu;%s"
                 % (a, s, SH(w), m, rc(w, "c->r[%d]" % a))], ("fall",))
    if op == 23:                                    # rlwnm
        m = mask32(MB(w), ME(w))
        return (["c->r[%d] = ppc_rotl32(c->r[%d], (int)(c->r[%d] & 31)) & 0x%08xu;%s"
                 % (a, s, b, m, rc(w, "c->r[%d]" % a))], ("fall",))
    if op == 20:                                    # rlwimi
        m = mask32(MB(w), ME(w))
        return (["c->r[%d] = (c->r[%d] & ~0x%08xu) | (ppc_rotl32(c->r[%d], %d) & 0x%08xu);%s"
                 % (a, a, m, s, SH(w), m, rc(w, "c->r[%d]" % a))], ("fall",))

    # ---- D-form loads / stores -----------------------------------------
    if op in D_LOADS:
        tmpl, kind, upd = D_LOADS[op]
        if upd and a == 0:
            raise Unsupported(addr, w, "update-form load with rA=0 is invalid")
        ea = ea_d(w)
        dst = "c->r[%d]" % d if kind == "gpr" else "c->f[%d]" % d
        out = ["c->cia = 0x%08xu; { uint32_t ea = %s; %s = %s;%s }"
               % (addr, ea, dst, tmpl % "ea", (" c->r[%d] = ea;" % a) if upd else "")]
        return (out, ("fall",))
    if op in D_STORES:
        tmpl, kind, upd = D_STORES[op]
        ea = ea_d(w)
        out = ["c->cia = 0x%08xu; { uint32_t ea = %s; %s%s }"
               % (addr, ea, tmpl % ("ea", s), (" c->r[%d] = ea;" % a) if upd else "")]
        return (out, ("fall",))

    # ---- op 31 ----------------------------------------------------------
    if op == 31:
        xo = XO10(w)
        if xo in X_LOADS:
            tmpl, kind = X_LOADS[xo]
            dst = "c->r[%d]" % d if kind == "gpr" else "c->f[%d]" % d
            return (["c->cia = 0x%08xu; { uint32_t ea = %s; %s = %s; }"
                     % (addr, ea_x(w), dst, tmpl % "ea")], ("fall",))
        if xo in X_STORES:
            tmpl, kind = X_STORES[xo]
            return (["c->cia = 0x%08xu; { uint32_t ea = %s; %s }"
                     % (addr, ea_x(w), tmpl % ("ea", s))], ("fall",))
        try:
            return x_arith(w)
        except Unsupported as e:
            raise Unsupported(addr, w, e.why)

    # ---- branches -------------------------------------------------------
    if op == 18:                                    # b / bl / ba / bla
        tgt = (LI(w) if AA(w) else addr + LI(w)) & 0xFFFFFFFF
        if LK(w):
            return (["c->lr = 0x%08xu; c->cia = 0x%08xu; ppc_bl(c, 0x%08xu);"
                     % (addr + 4, addr, tgt)], ("fall",))
        if fn_lo <= tgt < fn_hi:
            return ([], ("jmp", tgt))
        # A tail branch out of the function.  Model it as a call + return; a
        # real recompiler emits a tail call.
        return (["c->cia = 0x%08xu; ppc_bl(c, 0x%08xu);" % (addr, tgt)], ("ret",))
    if op == 16:                                    # bc
        tgt = (BD(w) if AA(w) else addr + BD(w)) & 0xFFFFFFFF
        cond = bc_cond_expr(BO(w), BI(w))
        pre = bc_ctr_dec(BO(w))
        if not (fn_lo <= tgt < fn_hi):
            raise Unsupported(addr, w, "conditional branch leaves the function")
        if LK(w):
            raise Unsupported(addr, w, "bcl (conditional call) not modelled")
        return (pre, ("cond", tgt, cond))
    if op == 19:
        xo = XO10(w)
        if xo == 16:                                # bclr / blr
            if BO(w) & 0x14 == 0x14:                # BO=1z1zz: unconditional
                if LK(w):
                    # blrl: call through LR.  Same table lookup as every other
                    # call; LR is saved first because the callee overwrites it.
                    return (["{ uint32_t t = c->lr; c->lr = 0x%08xu; "
                             "c->cia = 0x%08xu; ppc_bl(c, t); }" % (addr + 4, addr)],
                            ("fall",))
                return ([], ("ret",))
            cond = bc_cond_expr(BO(w), BI(w))
            pre = bc_ctr_dec(BO(w))
            return (pre, ("condret", cond))
        if xo == 528:                               # bcctr / bctr / bctrl
            if BO(w) & 0x14 != 0x14:
                raise Unsupported(addr, w, "conditional bcctr not modelled")
            if LK(w):
                return (["c->lr = 0x%08xu; c->cia = 0x%08xu; ppc_bctrl(c);"
                         % (addr + 4, addr)], ("fall",))
            # bctr: a computed jump.  In a whole-program recompiler this is the
            # jump table (see ppc_lookup); the spike models it as a tail call.
            return (["c->cia = 0x%08xu; ppc_bctrl(c);" % addr], ("ret",))
        if xo == 150:                               # isync
            return (["/* isync: no-op */"], ("fall",))
        CR_OPS = {257: "&", 449: "|", 193: "^", 289: "==", 33: "nor",
                  225: "nand", 129: "andc", 417: "orc"}
        if xo in CR_OPS:
            o = CR_OPS[xo]
            ba, bb, bt = RA(w), RB(w), RD(w)
            expr = {"&": "(x & y)", "|": "(x | y)", "^": "(x ^ y)",
                    "==": "(x == y)", "nor": "(!(x | y))", "nand": "(!(x & y))",
                    "andc": "(x & !y)", "orc": "(x | !y)"}[o]
            return ([("{ int x = ppc_crbit(c, %d), y = ppc_crbit(c, %d); "
                      "ppc_setcrbit(c, %d, %s); }") % (ba, bb, bt, expr)], ("fall",))
        if xo == 0:                                 # mcrf
            return (["ppc_setcrf(c, %d, ppc_getcrf(c, %d));" % (CRFD(w), CRFS(w))],
                    ("fall",))
        if xo == 50:                                # rfi
            raise Unsupported(addr, w, "rfi: supervisor, needs a machine model")
        raise Unsupported(addr, w, "op 19 XO=%d not in the translation table" % xo)

    # ---- floating point --------------------------------------------------
    if op in (59, 63):
        single = (op == 59)
        xo5 = XO5(w)
        if xo5 in A_FORM:
            name, tmpl = A_FORM[xo5]
            expr = tmpl % {"A": "c->f[%d]" % a, "B": "c->f[%d]" % b, "C": "c->f[%d]" % RC_(w)}
            if single:
                expr = "(double)(float)(%s)" % expr
            return (["c->f[%d] = %s;%s" % (d, expr,
                     " /* %s%s */" % (name, "s" if single else ""))], ("fall",))
        if xo5 in (24, 26):
            # fres / frsqrte: the GameCube's estimates are TABLE-DRIVEN and are
            # NOT 1/x and 1/sqrt(x).  Refusing is the honest translation until
            # Dolphin's tables are ported in.
            raise Unsupported(addr, w,
                              "%s: non-IEEE GameCube estimate, needs Dolphin's tables"
                              % ("fres" if xo5 == 24 else "frsqrte"))
        xo = XO10(w)
        if op == 63:
            if xo == 0 or xo == 32:                 # fcmpu / fcmpo
                return (["ppc_fcmpu(c, %d, c->f[%d], c->f[%d]);" % (CRFD(w), a, b)],
                        ("fall",))
            if xo == 72:                            # fmr
                return (["c->f[%d] = c->f[%d];" % (d, b)], ("fall",))
            if xo == 40:                            # fneg
                return (["c->f[%d] = -c->f[%d];" % (d, b)], ("fall",))
            if xo == 264:                           # fabs
                return (["c->f[%d] = __builtin_fabs(c->f[%d]);" % (d, b)], ("fall",))
            if xo == 136:                           # fnabs
                return (["c->f[%d] = -__builtin_fabs(c->f[%d]);" % (d, b)], ("fall",))
            if xo == 12:                            # frsp
                return (["c->f[%d] = (double)(float)c->f[%d];" % (d, b)], ("fall",))
            if xo in (14, 15):                      # fctiw / fctiwz
                mode = "(int32_t)" if xo == 15 else "(int32_t)__builtin_nearbyint"
                return ([("{ double v = c->f[%d]; int32_t i = %s(v); "
                          "c->f[%d] = ppc_u642d((uint64_t)(uint32_t)i | 0xFFF8000000000000ull); }")
                         % (b, mode, d)], ("fall",))
            if xo in (583, 711, 38, 70, 134, 64):
                return (["/* FPSCR op: no rounding-mode model in the spike */"], ("fall",))
        raise Unsupported(addr, w, "op %d float form not in the translation table" % op)

    # ---- Gekko ----------------------------------------------------------
    if op in (4, 56, 57, 60, 61):
        return (["ppc_ps_unsupported(c, \"op%d\");" % op], ("fall",))
    if op == 17:
        raise Unsupported(addr, w, "sc: system call, needs an OS model")
    if op in (46, 47):                              # lmw / stmw
        ea = ea_d(w)
        body = []
        for i, reg in enumerate(range(d if op == 46 else s, 32)):
            if op == 46:
                body.append("c->r[%d] = ppc_r32(c, ea + %d);" % (reg, 4 * i))
            else:
                body.append("ppc_w32(c, ea + %d, c->r[%d]);" % (4 * i, reg))
        return (["c->cia = 0x%08xu; { uint32_t ea = %s; %s }"
                 % (addr, ea, " ".join(body))], ("fall",))
    if op == 3:                                     # twi -- conditional trap
        return (["/* twi: trap; the SDK uses it as an assert, host-visible only "
                 "through the OS exception path */"], ("fall",))
    raise Unsupported(addr, w, "primary opcode %d not in the translation table" % op)


def mask32(mb, me):
    if mb <= me:
        m = 0
        for i in range(mb, me + 1):
            m |= 1 << (31 - i)
    else:
        m = 0xFFFFFFFF
        for i in range(me + 1, mb):
            m &= ~(1 << (31 - i))
    return m & 0xFFFFFFFF


def bc_ctr_dec(bo):
    """The CTR decrement half of `bc`, emitted before the test."""
    if not ((bo >> 2) & 1):
        return ["c->ctr--;"]
    return []


def bc_cond_expr(bo, bi):
    """The taken-condition of `bc`, as a C expression."""
    parts = []
    if not ((bo >> 2) & 1):
        parts.append("(c->ctr %s 0)" % ("==" if ((bo >> 1) & 1) else "!="))
    if not ((bo >> 4) & 1):
        want = (bo >> 3) & 1
        parts.append("(ppc_crbit(c, %d) == %d)" % (bi, want))
    if not parts:
        return "1"
    return " && ".join(parts)


# --------------------------------------------------------------------------
# function extent + emission
# --------------------------------------------------------------------------

def function_extent(dol_word, entry, limit=0x4000):
    """Follow the function's own branches to find where it ends.

    A `blr` ends a block; the function ends at the first `blr`/tail branch
    beyond which no earlier branch reaches.  This is the standard recompiler
    heuristic and it REPORTS rather than guesses: if the walk leaves mapped
    ROM, that is an error.
    """
    end = entry
    furthest = entry
    addr = entry
    while addr < entry + limit:
        w = dol_word(addr)
        if w is None:
            raise Unsupported(addr, 0, "walk left mapped ROM")
        op = OP(w)
        if op == 18 and not LK(w):
            t = (LI(w) if AA(w) else addr + LI(w)) & 0xFFFFFFFF
            if t > furthest and entry <= t < entry + limit:
                furthest = t
            if addr >= furthest:
                end = addr + 4
                break
        elif op == 16:
            t = (BD(w) if AA(w) else addr + BD(w)) & 0xFFFFFFFF
            if t > furthest:
                furthest = t
        elif op == 19 and XO10(w) == 16 and not LK(w) and (BO(w) & 0x14) == 0x14:
            if addr >= furthest:
                end = addr + 4
                break
        elif op == 19 and XO10(w) == 528 and not LK(w):
            if addr >= furthest:
                end = addr + 4
                break
        addr += 4
    else:
        raise Unsupported(entry, 0, "no function end within %d bytes" % limit)
    return entry, end


HEADER = """/* GENERATED by research/tools/static-recomp/ppc_recomp.py -- do not edit.
 *
 * Static recompilation of %(name)s @ %(entry)s from
 * "%(iso)s" (boot.dol, %(count)d instructions).
 *
 * NOTHING IN THIS FILE IS AN INFERENCE.  Every statement below is the
 * mechanical image of one PowerPC instruction word, shown in the comment above
 * it as `address  encoding  disassembly`.  No decompiler, no type recovery, no
 * signature, no human read this function.
 */
#include "ppc_rt.h"

void %(cname)s(ppc_ctx *c)
{
"""


def emit(dol_word, entry, name, iso, disasm_text):
    lo, hi = function_extent(dol_word, entry)
    count = (hi - lo) // 4

    # pass 1: branch targets that need labels
    labels = set()
    for addr in range(lo, hi, 4):
        w = dol_word(addr)
        op = OP(w)
        if op == 18 and not LK(w):
            t = (LI(w) if AA(w) else addr + LI(w)) & 0xFFFFFFFF
            if lo <= t < hi:
                labels.add(t)
        elif op == 16:
            t = (BD(w) if AA(w) else addr + BD(w)) & 0xFFFFFFFF
            if lo <= t < hi:
                labels.add(t)

    cname = "fn_%08x" % entry
    out = [HEADER % {"name": name, "entry": "0x%08x" % entry, "iso": iso,
                     "count": count, "cname": cname}]
    forms = collections.Counter()
    for addr in range(lo, hi, 4):
        w = dol_word(addr)
        if addr in labels:
            out.append("L_%08x:;\n" % addr)
        stmts, flow = translate(addr, w, lo, hi)
        forms[disasm_text(addr, w).split()[0]] += 1
        out.append("    /* %08x  %08x  %s */\n" % (addr, w, disasm_text(addr, w)))
        for st in stmts:
            out.append("    %s\n" % st)
        if flow[0] == "jmp":
            out.append("    goto L_%08x;\n" % flow[1])
        elif flow[0] == "cond":
            out.append("    if (%s) goto L_%08x;\n" % (flow[2], flow[1]))
        elif flow[0] == "condret":
            out.append("    if (%s) return;\n" % flow[1])
        elif flow[0] == "ret":
            out.append("    return;\n")
    out.append("}\n")
    return "".join(out), {"entry": "0x%08x" % entry, "end": "0x%08x" % hi,
                          "instructions": count, "cname": cname,
                          "labels": ["0x%08x" % x for x in sorted(labels)],
                          "forms_used": dict(forms.most_common())}


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--iso", required=True)
    ap.add_argument("--func", required=True)
    ap.add_argument("--name", required=True)
    ap.add_argument("--out", required=True)
    ap.add_argument("--manifest")
    a = ap.parse_args()

    dol = Dol.from_iso(Path(a.iso))
    secs = dol.text + dol.data

    def word(addr):
        for off, ad, sz in secs:
            if ad <= addr < ad + sz:
                return struct.unpack(">I", dol.blob[off + (addr - ad):off + (addr - ad) + 4])[0]
        return None

    from capstone import Cs, CS_ARCH_PPC, CS_MODE_32, CS_MODE_BIG_ENDIAN
    from dol_inventory import gekko_fallback
    md = Cs(CS_ARCH_PPC, CS_MODE_32 | CS_MODE_BIG_ENDIAN)
    md.skipdata = True

    def disasm_text(addr, w):
        g = list(md.disasm(struct.pack(">I", w), addr, count=1))
        if g and g[0].mnemonic not in (".byte", ".long", ""):
            return ("%s %s" % (g[0].mnemonic, g[0].op_str)).strip()
        return gekko_fallback(w) or "<undecoded>"

    entry = int(a.func, 0)
    src, manifest = emit(word, entry, a.name, a.iso, disasm_text)
    Path(a.out).parent.mkdir(parents=True, exist_ok=True)
    Path(a.out).write_text(src)
    manifest["source"] = a.out
    manifest["rom_name"] = a.name
    if a.manifest:
        Path(a.manifest).write_text(json.dumps(manifest, indent=2))
    print("recompiled %s @ 0x%08x: %d instructions, %d labels -> %s"
          % (a.name, entry, manifest["instructions"], len(manifest["labels"]), a.out))
    print("forms used:", ", ".join("%s x%d" % (k, v)
                                   for k, v in manifest["forms_used"].items()))


if __name__ == "__main__":
    main()
