#!/usr/bin/env python3
"""dol_inventory.py -- whole-DOL PowerPC instruction inventory for the static
recompilation spike.

Reads boot.dol straight out of the retail GCM (the DOL file offset is the BE u32
at 0x420, exactly as research/tools/dolphin-trace/capture_common.py:Dol does),
disassembles every text section word with capstone PPC32-BE, and classifies each
mnemonic into a translation-difficulty class.

The output is a JSON artifact + a printed histogram.  The number that matters is
the count of instructions in the HARD classes -- the ones a mechanical PPC->C
translator cannot emit as one line of portable C.

Usage:  python dol_inventory.py --iso "D:/GotYaForce/Gotcha Force.iso" \
                                --out research/decomp/data/static-recomp-inventory.json
"""
from __future__ import annotations

import argparse
import collections
import json
import struct
import sys
from pathlib import Path

try:
    from capstone import Cs, CS_ARCH_PPC, CS_MODE_32, CS_MODE_BIG_ENDIAN
except ImportError:
    sys.exit("capstone is required: pip install capstone")


# --------------------------------------------------------------------------
# DOL reader (same layout logic as capture_common.Dol, kept standalone so this
# tool has no dependency on the live capture stack)
# --------------------------------------------------------------------------

class Dol:
    def __init__(self, blob):
        self.blob = blob
        offs = struct.unpack(">18I", blob[0x00:0x48])
        adrs = struct.unpack(">18I", blob[0x48:0x90])
        szs = struct.unpack(">18I", blob[0x90:0xD8])
        # sections 0..6 are text, 7..17 are data
        self.text = [(offs[i], adrs[i], szs[i]) for i in range(7) if szs[i]]
        self.data = [(offs[i], adrs[i], szs[i]) for i in range(7, 18) if szs[i]]
        self.bss_addr, self.bss_size = struct.unpack(">II", blob[0xD8:0xE0])
        self.entry = struct.unpack(">I", blob[0xE0:0xE4])[0]

    @classmethod
    def from_iso(cls, iso_path):
        with open(str(iso_path), "rb") as f:
            f.seek(0x420)
            dol_off = struct.unpack(">I", f.read(4))[0]
            f.seek(dol_off)
            head = f.read(0x100)
            offs = struct.unpack(">18I", head[0x00:0x48])
            szs = struct.unpack(">18I", head[0x90:0xD8])
            size = max(o + s for o, s in zip(offs, szs) if s)
            f.seek(dol_off)
            return cls(f.read(size))


# --------------------------------------------------------------------------
# Difficulty classification
#
# EASY      one-to-one with a C expression over the register file
# BRANCH    intra-function control flow -> goto / switch; trivial once blocks
#           are known
# CALL      direct call -> C call; needs a symbol table but no inference
# INDIRECT  bctr/bctrl/blrl -> needs a jump table over all function entries
# FPU_IEEE  ordinary IEEE-754 float ops -> C double/float, but see FMA note
# FP_NONIEEE  frsqrte/fres: GameCube estimates are table-driven and NOT the same
#           as 1/sqrt(x) computed exactly.  Needs Dolphin's tables.
# FMA       fused multiply-add: PPC rounds ONCE, C's a*b+c rounds TWICE unless
#           fma() is used.  Mechanical, but must be spelled correctly.
# PAIRED_SINGLE  ps_*/psq_*: GameCube-only SIMD over the second half of each FPR.
# SUPERVISOR  mtmsr/rfi/tlb*/mtsr/... : requires a machine model, not a C stmt
# SPR       mfspr/mtspr/mftb/mfmsr : per-register decision (some are easy, some
#           are supervisor state)
# CACHE     dcbz/dcbf/icbi/... : dcbz is SEMANTIC (zeroes 32 bytes, games use it
#           as memset); the rest are no-ops for a recompiler
# ATOMIC    lwarx/stwcx. : needs a reservation model
# SYSCALL   sc / trap
# UNKNOWN   capstone could not decode -- data in text, or a bad walk
# --------------------------------------------------------------------------

PAIRED_SINGLE_PREFIXES = ("ps_", "psq_")

FP_NONIEEE = {"frsqrte", "frsqrtes", "fres", "fresx", "frsqrtex"}

FMA = {"fmadd", "fmadds", "fmsub", "fmsubs", "fnmadd", "fnmadds",
       "fnmsub", "fnmsubs"}

SUPERVISOR = {
    "mtmsr", "mfmsr", "rfi", "rfid", "mtsr", "mfsr", "mtsrin", "mfsrin",
    "tlbie", "tlbia", "tlbsync", "tlbld", "tlbli", "eciwx", "ecowx",
    "mtsrr0", "mtsrr1", "hrfid",
}

CACHE = {"dcbz", "dcbz_l", "dcbf", "dcbst", "dcbt", "dcbtst", "icbi",
         "dcba", "dcbi"}

ATOMIC = {"lwarx", "stwcx.", "ldarx", "stdcx."}

SYNC = {"sync", "isync", "eieio", "msync", "lwsync"}

SYSCALL = {"sc", "tw", "twi", "trap", "td", "tdi"}

SPR = {"mfspr", "mtspr", "mftb", "mftbu", "mfdec", "mtdec", "mfpvr",
       "mfhid0", "mthid0", "mfhid1", "mthid1", "mfdar", "mfdsisr",
       "mfibatu", "mtibatu", "mfibatl", "mtibatl", "mfdbatu", "mtdbatu",
       "mfdbatl", "mtdbatl", "mtfsb0", "mtfsb1", "mtfsf", "mtfsfi",
       "mffs", "mcrfs", "mtcr", "mfcr", "mtcrf", "mtlr", "mflr",
       "mtctr", "mfctr", "mtxer", "mfxer", "mcrxr", "mfsprg", "mtsprg",
       "mfmsr"}

BRANCH_UNCOND = {"b", "ba"}
BRANCH_COND = {"bc", "bca", "bdnz", "bdz", "bdnzf", "bdnzt", "bdzf", "bdzt",
               "beq", "bne", "blt", "bgt", "ble", "bge", "bso", "bns",
               "bdnza", "bdza", "beqa", "bnea", "blta", "bgta", "blea",
               "bgea", "bt", "bf", "bta", "bfa", "bun", "bnu"}
CALL_DIRECT = {"bl", "bla"}
RETURN = {"blr", "bclr", "bcr", "beqlr", "bnelr", "bltlr", "bgtlr", "blelr",
          "bgelr", "bsolr", "bnslr", "btlr", "bflr", "bdnzlr", "bdzlr"}
INDIRECT = {"bctr", "bctrl", "blrl", "bcctr", "bcctrl", "bclrl",
            "beqctr", "bnectr", "beqctrl", "bnectrl"}


def classify(mn):
    m = mn.strip()
    base = m.rstrip("+-")
    if any(base.startswith(p) for p in PAIRED_SINGLE_PREFIXES):
        return "PAIRED_SINGLE"
    if base in FP_NONIEEE or base.rstrip(".") in FP_NONIEEE:
        return "FP_NONIEEE"
    if base in FMA or base.rstrip(".") in FMA:
        return "FMA"
    if base in SUPERVISOR:
        return "SUPERVISOR"
    if base in ATOMIC:
        return "ATOMIC"
    if base in SYSCALL:
        return "SYSCALL"
    if base in CACHE:
        return "CACHE"
    if base in SYNC:
        return "SYNC"
    if base in INDIRECT:
        return "INDIRECT"
    if base in RETURN:
        return "RETURN"
    if base in CALL_DIRECT:
        return "CALL"
    if base in BRANCH_UNCOND or base in BRANCH_COND:
        return "BRANCH"
    if base in SPR:
        return "SPR"
    if base.startswith("f"):
        return "FPU_IEEE"
    return "EASY"


# --------------------------------------------------------------------------
# Gekko fallback decoder.
#
# capstone knows generic PowerPC, not the GameCube's Gekko core, so it rejects
# every paired-single word.  It also (capstone 5.0.1, PPC32-BE) rejects `fcmpo`
# -- primary opcode 63, XO 32 -- which MWCC emits for every ordered float
# comparison and which is therefore one of the most common FP forms in this DOL.
# Without this fallback the inventory would report ~7.4k "undecodable"
# instructions and would silently miss the paired-single count, which is the
# single most load-bearing number in the go/no-go.
# --------------------------------------------------------------------------

OP4_XO5 = {6: "psq_lx", 7: "psq_lux", 38: "psq_stx", 39: "psq_stux",
           10: "ps_sum0", 11: "ps_sum1", 12: "ps_muls0", 13: "ps_muls1",
           14: "ps_madds0", 15: "ps_madds1", 18: "ps_div", 20: "ps_sub",
           21: "ps_add", 23: "ps_sel", 24: "ps_res", 25: "ps_mul",
           26: "ps_rsqrte", 28: "ps_msub", 29: "ps_madd", 30: "ps_nmsub",
           31: "ps_nmadd"}
OP4_XO10 = {0: "ps_cmpu0", 32: "ps_cmpo0", 40: "ps_neg", 64: "ps_cmpu1",
            72: "ps_mr", 96: "ps_cmpo1", 136: "ps_nabs", 264: "ps_abs",
            528: "ps_merge00", 560: "ps_merge01", 592: "ps_merge10",
            624: "ps_merge11", 1014: "dcbz_l"}


def gekko_override(word):
    """Name a word whose primary opcode is Gekko-only, or None.

    capstone decodes generic PowerPC, which on a 64-bit server core assigns
    primary opcodes 4 / 56 / 57 / 60 / 61 to AltiVec and VSX.  The GameCube's
    Gekko has neither: those encodings are the paired-single unit.  capstone
    therefore silently renders `psq_st` as `xxsel`, `ps_sel` as `vsel` and so
    on -- 1,087 instructions in this DOL -- so the primary opcode MUST be
    checked before the disassembler is believed.  This override is why the
    paired-single count in this artifact is 2,883 and not 1,796.
    """
    if (word >> 26) in (4, 56, 57, 60, 61):
        return gekko_fallback(word) or "ps.op%d.xo=%d" % (word >> 26, (word >> 1) & 0x3FF)
    return None


def gekko_fallback(word):
    """Name a word capstone rejected, or None if it is not code we know."""
    op = word >> 26
    if op == 4:
        xo5 = (word >> 1) & 0x1F
        if xo5 in OP4_XO5:
            return OP4_XO5[xo5]
        return OP4_XO10.get((word >> 1) & 0x3FF)
    if op == 56:
        return "psq_l"
    if op == 57:
        return "psq_lu"
    if op == 60:
        return "psq_st"
    if op == 61:
        return "psq_stu"
    if op == 63 and ((word >> 1) & 0x3FF) == 32:
        return "fcmpo"
    if word == 0:
        return "<padding>"
    return None


HARD_CLASSES = {"PAIRED_SINGLE", "FP_NONIEEE", "SUPERVISOR", "ATOMIC",
                "SYSCALL", "UNKNOWN"}
# FMA and INDIRECT and SPR are "attention" classes: mechanical, but each needs a
# named decision in the translator.  They are counted separately.
ATTENTION_CLASSES = {"FMA", "INDIRECT", "SPR", "CACHE"}


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--iso", required=True)
    ap.add_argument("--out", required=True)
    a = ap.parse_args()

    dol = Dol.from_iso(Path(a.iso))
    md = Cs(CS_ARCH_PPC, CS_MODE_32 | CS_MODE_BIG_ENDIAN)
    md.detail = False
    md.skipdata = True

    hist = collections.Counter()
    cls_hist = collections.Counter()
    cls_examples = collections.defaultdict(list)
    per_mn_class = {}
    total = 0
    undecoded = 0

    sections_out = []
    for off, addr, size in dol.text:
        blob = dol.blob[off:off + size]
        sections_out.append({"file_off": off, "addr": "0x%08x" % addr,
                             "size": size, "instructions": size // 4})
        # capstone with skipdata emits ".byte" for undecodable words; walk word
        # by word so a single bad word cannot desynchronise the stream.
        for i in range(0, size - 3, 4):
            word = blob[i:i + 4]
            pc = addr + i
            raw = struct.unpack(">I", word)[0]
            total += 1
            ovr = gekko_override(raw)
            if ovr is not None:
                # Gekko-only primary opcode: never trust capstone here.
                hist[ovr] += 1
                per_mn_class[ovr] = classify(ovr)
                cls_hist[per_mn_class[ovr]] += 1
                if len(cls_examples[per_mn_class[ovr]]) < 6:
                    cls_examples[per_mn_class[ovr]].append(
                        {"addr": "0x%08x" % pc, "mn": ovr})
                continue
            got = list(md.disasm(word, pc, count=1))
            if not got or got[0].mnemonic in (".byte", ".long", ""):
                undecoded += 1
                mn = gekko_fallback(raw)
                if mn is None:
                    mn = "<undecoded>"
                    c = "UNKNOWN"
                elif mn == "<padding>":
                    c = "PADDING"
                else:
                    c = classify(mn)
            else:
                mn = got[0].mnemonic
                c = classify(mn)
            hist[mn] += 1
            per_mn_class[mn] = c
            cls_hist[c] += 1
            if len(cls_examples[c]) < 6:
                cls_examples[c].append({"addr": "0x%08x" % pc, "mn": mn})

    hard = sum(cls_hist[c] for c in HARD_CLASSES)
    attention = sum(cls_hist[c] for c in ATTENTION_CLASSES)
    code_total = total - cls_hist["PADDING"]

    out = {
        "schema": 1,
        "iso": str(a.iso),
        "entry": "0x%08x" % dol.entry,
        "bss": {"addr": "0x%08x" % dol.bss_addr, "size": dol.bss_size},
        "text_sections": sections_out,
        "data_sections": [{"file_off": o, "addr": "0x%08x" % ad, "size": s}
                          for o, ad, s in dol.data],
        "total_text_words": total,
        "padding_words": cls_hist["PADDING"],
        "total_text_instructions": code_total,
        "distinct_mnemonics": len(hist),
        "capstone_rejected_words": undecoded,
        "class_histogram": dict(sorted(cls_hist.items(),
                                       key=lambda kv: -kv[1])),
        "hard_instruction_count": hard,
        "hard_classes": sorted(HARD_CLASSES),
        "attention_instruction_count": attention,
        "attention_classes": sorted(ATTENTION_CLASSES),
        "mnemonic_histogram": [
            {"mnemonic": m, "count": n, "class": per_mn_class[m]}
            for m, n in hist.most_common()],
        "class_examples": {k: v for k, v in cls_examples.items()},
    }
    Path(a.out).parent.mkdir(parents=True, exist_ok=True)
    Path(a.out).write_text(json.dumps(out, indent=2))

    print("text sections: %d  words: %d  padding: %d  instructions: %d  "
          "distinct mnemonics: %d"
          % (len(dol.text), total, cls_hist["PADDING"], code_total, len(hist)))
    print("")
    print("%-16s %10s %7s" % ("CLASS", "COUNT", "SHARE"))
    for c, n in sorted(cls_hist.items(), key=lambda kv: -kv[1]):
        print("%-16s %10d %6.2f%%" % (c, n, 100.0 * n / code_total))
    print("")
    print("HARD (no straightforward C translation): %d (%.3f%%)"
          % (hard, 100.0 * hard / code_total))
    print("ATTENTION (mechanical but needs a named decision): %d (%.3f%%)"
          % (attention, 100.0 * attention / code_total))
    print("")
    print("top 40 mnemonics:")
    for m, n in hist.most_common(40):
        print("  %-12s %8d  %s" % (m, n, per_mn_class[m]))


if __name__ == "__main__":
    main()
