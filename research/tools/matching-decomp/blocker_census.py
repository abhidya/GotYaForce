#!/usr/bin/env python3
"""blocker_census.py -- how much of Gotcha Force does each mwcc-rs gap cost?

The matching-decompilation spike (docs/matching-decompilation-spike.md 3.1.3)
recorded five non-matches and named the compiler construct that blocked each.
It did NOT say how many functions in the corpus contain that construct, so the
gaps could not be ranked and fixing them was guesswork.

SCOPE, and how this differs from `census.py`.  `census.py` measures the
COMPILER: it pushes every function's Ghidra C through mwcc-rs and tallies the
diagnostics, which is the authoritative ranking and supersedes this tool for
that purpose.  This one measures the RETAIL BYTES instead -- it never runs the
compiler and never reads decompiler output.  The two answer different
questions, and the retail-side view is what tells you which FORM of a
construct mwcc actually emitted (the `andi.` / `andis.` / materialise-and-AND
split below is what specified the AND fix; a diagnostic count cannot say that).
Read them together; where they disagree about size, `census.py` is right.

It decodes every instruction of every function in the census, classifies each
function by which known mwcc-rs gaps its retail code exhibits, and reports two
numbers per gap:

  * FUNCTIONS TOUCHED   -- functions whose retail code contains the construct.
  * FUNCTIONS UNLOCKED  -- functions for which this is the ONLY known gap, i.e.
                           the ones that become plausibly compilable when this
                           one gap closes.  This is the number that ranks the
                           work, and it is always the smaller of the two.

"Plausibly compilable" is exactly that: absence of a *known* blocker is not a
proof of matchability, and the tool prints the baseline (functions with no
known blocker at all) so the reader can see how weak that floor is.

Detection is on the RETAIL BYTES, never on decompiler output -- the same rule
the rest of this harness follows.  The one exception is the type-punning gap
(TYPEPUN), which has no instruction-level signature at all; it is measured
separately from the Ghidra C export and reported as such.

    python research/tools/matching-decomp/blocker_census.py
    python research/tools/matching-decomp/blocker_census.py --json out.json
    python research/tools/matching-decomp/blocker_census.py --sample ANDCONST 12
"""
from __future__ import annotations

import argparse
import json
import re
import struct
import sys
from collections import Counter, defaultdict
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from dolsym import load  # noqa: E402

REPO = Path("D:/GotYaForce")
CENSUS = REPO / "research" / "decomp" / "data" / "matching-decomp-census.json"
GHIDRA = REPO / "research" / "decomp" / "ghidra-export"

# ---------------------------------------------------------------- decode ---

OP = lambda w: w >> 26                      # noqa: E731
RT = lambda w: (w >> 21) & 31               # noqa: E731
RA = lambda w: (w >> 16) & 31               # noqa: E731
RB = lambda w: (w >> 11) & 31               # noqa: E731
XO10 = lambda w: (w >> 1) & 0x3FF           # noqa: E731
SIMM = lambda w: (w & 0xFFFF) - 0x10000 if w & 0x8000 else w & 0xFFFF  # noqa: E731
UIMM = lambda w: w & 0xFFFF                 # noqa: E731

# D-form load/store with update (rA is written back).  stwu with rA=r1 is the
# Metrowerks stack prologue and is NOT this gap.
LSU_DFORM = {33: "lwzu", 35: "lbzu", 37: "stwu", 39: "stbu", 41: "lhzu",
             43: "lhau", 45: "sthu", 49: "lfsu", 51: "lfdu", 53: "stfsu",
             55: "stfdu"}
LSU_XFORM = {55: "lwzux", 119: "lbzux", 183: "stwux", 247: "stbux",
             311: "lhzux", 375: "lhaux", 439: "sthux", 567: "lfsux",
             631: "lfdux", 695: "stfsux", 759: "stfdux"}

PAIRED_PRIMARY = (4, 56, 57, 60, 61)

# X-form integer ALU ops that write a GPR (used for the r0-scratch test).
XALU = {28: "and", 60: "andc", 444: "or", 412: "orc", 316: "xor",
        476: "nand", 124: "nor", 284: "eqv", 266: "add", 10: "addc",
        138: "adde", 40: "subf", 8: "subfc", 136: "subfe", 235: "mullw",
        75: "mulhw", 11: "mulhwu", 491: "divw", 459: "divwu",
        24: "slw", 536: "srw", 792: "sraw", 824: "srawi",
        26: "cntlzw", 954: "extsb", 922: "extsh", 104: "neg"}
# D-form integer ALU ops that write a GPR.
DALU = {14: "addi", 15: "addis", 12: "addic", 13: "addic.", 8: "subfic",
        7: "mulli", 24: "ori", 25: "oris", 26: "xori", 27: "xoris",
        20: "rlwimi", 21: "rlwinm", 23: "rlwnm", 28: "andi.", 29: "andis."}


def contiguous_mask(m):
    """True if m is a rotate-and-mask (rlwinm) expressible mask: a single
    contiguous run of 1s in 32 bits, including a run that wraps end-to-end."""
    m &= 0xFFFFFFFF
    if m == 0 or m == 0xFFFFFFFF:
        return True
    # a single run, possibly wrapping: rotate until bit31 is 0 then test.
    for r in range(32):
        v = ((m << r) | (m >> (32 - r))) & 0xFFFFFFFF if r else m
        if v & 1:
            continue
        # no wrap now: strip low zeros, then the run must be contiguous
        t = v
        while t and not (t & 1):
            t >>= 1
        return ((t + 1) & t) == 0
    return False


# ---------------------------------------------------------- per-function ---

def classify(words, addr):
    """-> (set of blocker tags, dict of evidence lists)."""
    tags = set()
    ev = defaultdict(list)
    n = len(words)

    # Constant-register tracking: reg -> 32-bit value, invalidated on any other
    # definition.  Only lis/li/addi/ori/addis chains count, which is exactly
    # the MWCC constant-materialisation idiom (spike 2.1).
    const = {}
    branch_targets = set()

    def kill(r):
        const.pop(r, None)

    for i, w in enumerate(words):
        a = addr + i * 4
        op = OP(w)

        if op in PAIRED_PRIMARY:
            tags.add("PAIRED")
            ev["PAIRED"].append(a)
            const.clear()
            continue

        # ---- branches -------------------------------------------------
        if op == 18:                                   # b / bl
            li = w & 0x03FFFFFC
            if li & 0x02000000:
                li -= 0x04000000
            tgt = (a + li) if not (w & 2) else li
            if not (w & 1):
                branch_targets.add(tgt)
                if addr <= tgt <= a:
                    tags.add("LOOP")
                    ev["LOOP"].append(a)
            const.clear()
            continue
        if op == 16:                                   # bc
            bo = RT(w)
            bd = w & 0xFFFC
            if bd & 0x8000:
                bd -= 0x10000
            tgt = (a + bd) if not (w & 2) else bd
            branch_targets.add(tgt)
            # BO bit 2 clear => decrement CTR (bdnz/bdz): the counted-loop form
            if not (bo & 0x04) and tgt <= a:
                ev["_ctrloop"].append(a)
            elif tgt <= a and addr <= tgt <= addr + n * 4:
                tags.add("LOOP")
                ev["LOOP"].append(a)
            continue
        if op == 19:
            if XO10(w) == 528:                          # bcctr / bctr
                tags.add("BCTR")
                ev["BCTR"].append(a)
            const.clear()
            continue

        # ---- load/store with update ------------------------------------
        if op in LSU_DFORM:
            if not (op == 37 and RA(w) == 1):           # not the stack frame
                tags.add("LSU")
                ev["LSU"].append(a)
            kill(RA(w))
            if op in (33, 35, 41, 43):
                kill(RT(w))
            continue
        if op == 31 and XO10(w) in LSU_XFORM:
            tags.add("LSU")
            ev["LSU"].append(a)
            kill(RA(w))
            kill(RT(w))
            continue

        # ---- SPR / privileged: needs inline asm -------------------------
        # mflr/mtlr/mfctr/mtctr/mfxer ARE mfspr/mtspr and are ordinary compiler
        # output; only the SPRs a C compiler never emits count as this gap.
        if op == 31 and XO10(w) in (339, 467):
            spr = ((w >> 16) & 0x1F) | (((w >> 11) & 0x1F) << 5)
            if spr not in (1, 8, 9):
                tags.add("ASM")
                ev["ASM"].append((a, spr))
            kill(RT(w))
            continue
        if op == 31 and XO10(w) in (371, 83, 146, 210, 595, 4, 598, 982, 470):
            tags.add("ASM")
            ev["ASM"].append((a, XO10(w)))
            kill(RT(w))
            continue

        # ---- AND against a constant ------------------------------------
        if op == 28 or op == 29:                        # andi. / andis.
            m = UIMM(w) if op == 28 else (UIMM(w) << 16)
            if contiguous_mask(m):
                ev["_andi_mask"].append(a)
            else:
                tags.add("ANDCONST")
                ev["ANDCONST"].append((a, m, "andi." if op == 28 else "andis."))
            kill(RA(w))
            continue
        if op == 31 and XO10(w) in (28, 60):            # and / andc
            rb, ra = RB(w), RA(w)
            cval = None
            for r in (rb, ra):
                if r in const:
                    cval = const[r]
                    break
            if cval is not None:
                m = cval if XO10(w) == 28 else (~cval & 0xFFFFFFFF)
                if not contiguous_mask(m):
                    tags.add("ANDCONST")
                    ev["ANDCONST"].append((a, m, "and(reg-const)"))
                else:
                    ev["_and_mask"].append(a)
            kill(RT(w))
            continue

        # ---- constant materialisation ----------------------------------
        if op == 15 and RA(w) == 0:                     # lis
            const[RT(w)] = (UIMM(w) << 16) & 0xFFFFFFFF
            continue
        if op == 14:                                    # addi / li
            if RA(w) == 0:
                const[RT(w)] = SIMM(w) & 0xFFFFFFFF
            elif RA(w) in const:
                const[RT(w)] = (const[RA(w)] + SIMM(w)) & 0xFFFFFFFF
            else:
                kill(RT(w))
            continue
        if op == 24 and RA(w) in const:                 # ori
            const[RT(w)] = (const[RA(w)] | UIMM(w)) & 0xFFFFFFFF
            continue
        if op == 25 and RA(w) in const:                 # oris
            const[RT(w)] = (const[RA(w)] | (UIMM(w) << 16)) & 0xFFFFFFFF
            continue

        # ---- comparison against a materialised constant ------------------
        if op == 31 and XO10(w) in (0, 32):             # cmpw / cmplw
            if RA(w) in const or RB(w) in const:
                tags.add("CMPCONST")
                ev["CMPCONST"].append(a)
            continue

        # ---- everything else: just maintain the const map ---------------
        if op == 31:
            if XO10(w) in XALU:
                kill(RT(w))
            elif XO10(w) in (444,):                     # or (mr)
                kill(RT(w))
            else:
                # conservative: any X-form with an RT field may write it
                kill(RT(w))
            continue
        if op in DALU:
            kill(RT(w) if op in (7, 8, 12, 13, 14, 15) else RA(w))
            continue
        if op in (32, 34, 40, 42, 46):                  # plain loads
            kill(RT(w))
            continue

    # ---- r0 as an index scratch -------------------------------------------
    # The zz_0298b20_ divergence: MWCC routes a computed ARRAY INDEX through
    # the scratch register r0; mwcc-rs reuses the dead input register.  A bare
    # `li r0, n` or `addi r0, r1, n` is not that -- the signature is an ALU op
    # writing r0 whose value is then consumed by an address computation.
    ADDRUSE_X = set(LSU_XFORM) | {23, 87, 151, 215, 279, 343, 407, 439,
                                  535, 599, 663, 727, 279, 311}
    for i, w in enumerate(words):
        a = addr + i * 4
        op = OP(w)
        dst = None
        if op == 31 and XO10(w) in XALU:
            dst = RA(w) if XALU[XO10(w)] in (
                "and", "andc", "or", "orc", "xor", "nand", "nor", "eqv",
                "slw", "srw", "sraw", "srawi", "cntlzw", "extsb", "extsh"
            ) else RT(w)
        elif op in (7, 8, 12, 13):                      # mulli/subfic/addic
            dst = RT(w)
        elif op == 14 and RA(w) not in (0, 1):          # addi rD, rA, n
            dst = RT(w)
        elif op in (20, 21, 23, 24, 25, 26, 27):        # rlwinm/ori/xori...
            dst = RA(w)
        if dst != 0:
            continue
        # r0 must then feed an address computation within a short window
        for j in range(i + 1, min(i + 6, n)):
            v = words[j]
            vop = OP(v)
            if vop == 31 and (RA(v) == 0 or RB(v) == 0):
                if XO10(v) in ADDRUSE_X or XO10(v) in (266, 40, 235):
                    tags.add("R0IDX")
                    ev["R0IDX"].append(a)
                    break
            if vop in (32, 34, 36, 38, 40, 44, 48, 50, 52, 54) and RA(v) == 0:
                tags.add("R0IDX")
                ev["R0IDX"].append(a)
                break
            # r0 redefined -> stop
            if vop == 31 and XO10(v) in XALU and (RT(v) == 0 or RA(v) == 0):
                break

    return tags, ev


# ------------------------------------------------------------- typepun -----

TYPEPUN_RE = re.compile(r"\*\s*\(\s*(?:u?int|uint32_t|int32_t|undefined4|float|"
                        r"u32|s32|uint|ushort|byte)\s*\*\s*\)\s*&")
ADDROF_PARAM_RE = re.compile(r"[(,]\s*&\s*(?:param_\d+|local_\w+)\b")
FUNC_HEAD_RE = re.compile(r"^[A-Za-z_][\w \*]*\s+(\w+)\s*\(", re.M)


def typepun_scan():
    """Count Ghidra-C functions exhibiting the two SDK-body refusals.

    This is a WEAK proxy and is labelled as such: Ghidra's C is not the source
    and its casts are its own invention as often as the program's.  It bounds
    the class, it does not measure it.
    """
    tp_fns = set()
    ao_fns = set()
    total_fns = 0
    for p in sorted(GHIDRA.glob("chunk_*.c")):
        text = p.read_text(errors="replace")
        # split on function headers at column 0
        heads = list(FUNC_HEAD_RE.finditer(text))
        total_fns += len(heads)
        for i, m in enumerate(heads):
            body = text[m.end():heads[i + 1].start() if i + 1 < len(heads) else len(text)]
            name = m.group(1)
            if TYPEPUN_RE.search(body):
                tp_fns.add(name)
            if ADDROF_PARAM_RE.search(body):
                ao_fns.add(name)
    return total_fns, tp_fns, ao_fns


# ---------------------------------------------------------------- main -----

TAGS = ["ANDCONST", "CMPCONST", "LOOP", "LSU", "R0IDX", "PAIRED", "BCTR", "ASM"]
TAG_DESC = {
    "ANDCONST": "AND against a constant that is not an rlwinm mask",
    "CMPCONST": "comparison against a materialised (>16-bit) constant",
    "LOOP":     "uncounted loop (backward branch that is not bdnz/bdz)",
    "LSU":      "load/store with update (lbzu/lwzu/... , not the stack frame)",
    "R0IDX":    "an index computation routed through the scratch register r0",
    "PAIRED":   "Gekko paired-single instruction",
    "BCTR":     "computed jump (bctr) -- switch table",
    "ASM":      "time-base / privileged SPR access; needs inline assembly",
}


def scaled_index_report():
    """Where does retail put a scaled array index -- r0, the index's own
    register, or a third one?

    This is the zz_0298b20_ divergence measured over the whole binary.  mwcc-rs
    reuses the index register when its value dies; retail overwhelmingly does
    not.  Counted: every `mulli` and every power-of-two `slwi` whose result is
    consumed by an address `add`/`subf` or an indexed load within four
    instructions -- i.e. the value is an ADDRESS TEMPORARY, not a program value.
    """
    dol, _sym = load()
    census = json.loads(CENSUS.read_text())["functions"]
    ADDR_X = {266, 40, 23, 87, 151, 215, 279, 343, 407, 439, 535, 599, 663, 727}
    counts = {"mulli": Counter(), "slwi": Counter()}
    fns = {"r0": set(), "same": set(), "other": set()}

    for rec in census:
        addr = int(rec["addr"], 16)
        n = rec["insns"]
        blob = dol.read(addr, n * 4)
        if blob is None or len(blob) < n * 4:
            continue
        words = struct.unpack(">%dI" % n, blob)
        for i, w in enumerate(words):
            op = OP(w)
            if op == 7:                                  # mulli rD, rA, SIMM
                kind, dst, src = "mulli", RT(w), RA(w)
            elif op == 21:                               # rlwinm, slwi form
                sh, mb, me = RB(w), (w >> 6) & 31, (w >> 1) & 31
                if sh == 0 or mb != 0 or me != 31 - sh:
                    continue
                kind, dst, src = "slwi", RA(w), RT(w)
            else:
                continue
            consumed = False
            for j in range(i + 1, min(i + 5, n)):
                v = words[j]
                if OP(v) != 31 or XO10(v) not in ADDR_X:
                    continue
                if RA(v) == dst or RB(v) == dst:
                    consumed = True
                    break
            if not consumed:
                continue
            where = "r0" if dst == 0 else ("same" if dst == src else "other")
            counts[kind][where] += 1
            fns[where].add(rec["name"])

    print("WHERE RETAIL PUTS A SCALED ARRAY INDEX")
    print("(every mulli / power-of-two slwi whose product feeds an address")
    print(" computation within four instructions -- an address temporary)")
    print()
    total = sum(sum(c.values()) for c in counts.values())
    print("%-34s %8s %8s %9s %8s" % ("destination", "mulli", "slwi", "combined", "share"))
    print("-" * 72)
    for where, label in (("r0", "r0, the scratch"),
                         ("same", "the index's own register"),
                         ("other", "a third register")):
        m, s = counts["mulli"][where], counts["slwi"][where]
        print("%-34s %8d %8d %9d %7.1f%%"
              % (label, m, s, m + s, 100.0 * (m + s) / total if total else 0.0))
    print("-" * 72)
    print("%-34s %8d %8d %9d" % ("total", sum(counts["mulli"].values()),
                                 sum(counts["slwi"].values()), total))
    print()
    print("mwcc-rs's default is `the index's own register` -- reuse it when the")
    print("value dies there.  That is the MINORITY choice in this binary, and it")
    print("is the zz_0298b20_ mismatch.  See TOOLCHAIN.md section 5.3.")
    return 0


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--json")
    ap.add_argument("--sample", nargs=2, metavar=("TAG", "N"))
    ap.add_argument("--no-typepun", action="store_true")
    ap.add_argument("--scaled-index", action="store_true",
                    help="where retail puts a scaled array index (the "
                         "zz_0298b20_ register-allocator divergence)")
    args = ap.parse_args()

    if args.scaled_index:
        return scaled_index_report()

    dol, _sym = load()
    census = json.loads(CENSUS.read_text())["functions"]

    per_tag_touch = Counter()
    per_tag_touch_insns = Counter()
    per_tag_only = Counter()
    per_tag_only_insns = Counter()
    site_counts = Counter()
    clean = 0
    clean_insns = 0
    total = 0
    total_insns = 0
    unreadable = 0
    samples = defaultdict(list)
    per_fn = {}

    for rec in census:
        addr = int(rec["addr"], 16)
        n = rec["insns"]
        blob = dol.read(addr, n * 4)
        if blob is None or len(blob) < n * 4:
            unreadable += 1
            continue
        words = struct.unpack(">%dI" % n, blob)
        tags, ev = classify(words, addr)
        total += 1
        total_insns += n
        per_fn[rec["name"]] = sorted(tags)
        for t in tags:
            per_tag_touch[t] += 1
            per_tag_touch_insns[t] += n
            site_counts[t] += len(ev[t])
            if len(samples[t]) < 40:
                samples[t].append((rec["name"], rec["addr"], n, ev[t][:3]))
        if len(tags) == 1:
            t = list(tags)[0]
            per_tag_only[t] += 1
            per_tag_only_insns[t] += n
        elif not tags:
            clean += 1
            clean_insns += n

    if args.sample:
        tag, k = args.sample[0], int(args.sample[1])
        for row in samples[tag][:k]:
            print(row)
        return

    print("BLOCKER IMPACT CENSUS  --  %d functions, %d instructions"
          % (total, total_insns))
    if unreadable:
        print("(%d census entries were not readable from the DOL and are excluded)"
              % unreadable)
    print()
    print("%-11s %8s %8s %10s %9s %10s  %s"
          % ("gap", "sites", "fns", "fn-insns", "ONLY-fns", "ONLY-insns", "construct"))
    print("-" * 118)
    rows = sorted(TAGS, key=lambda t: -per_tag_only[t])
    for t in rows:
        print("%-11s %8d %8d %10d %9d %10d  %s"
              % (t, site_counts[t], per_tag_touch[t], per_tag_touch_insns[t],
                 per_tag_only[t], per_tag_only_insns[t], TAG_DESC[t]))
    print("-" * 118)
    print("%-11s %8s %8d %10d %9s %10s  %s"
          % ("(none)", "-", clean, clean_insns, "-", "-",
             "no KNOWN gap -- the optimistic floor, not a promise"))
    print()
    print("ONLY-fns = functions whose retail code exhibits this gap and no other")
    print("known gap; those are the ones a fix plausibly unlocks.  Absence of a")
    print("known gap is not a proof of matchability.")

    if not args.no_typepun:
        print()
        tf, tp, ao = typepun_scan()
        print("TYPEPUN / ADDROF -- no instruction signature; measured on the Ghidra")
        print("C export, which is a WEAK PROXY (Ghidra invents casts of its own):")
        print("  %6d Ghidra-C functions scanned" % tf)
        print("  %6d contain a `*(T *)&...` type-punning cast" % len(tp))
        print("  %6d pass `&local` / `&param` to a callee" % len(ao))

    if args.json:
        Path(args.json).write_text(json.dumps({
            "total_functions": total, "total_instructions": total_insns,
            "unreadable": unreadable,
            "clean_functions": clean, "clean_instructions": clean_insns,
            "gaps": {t: {"sites": site_counts[t], "functions": per_tag_touch[t],
                         "function_instructions": per_tag_touch_insns[t],
                         "only_functions": per_tag_only[t],
                         "only_instructions": per_tag_only_insns[t],
                         "description": TAG_DESC[t]} for t in TAGS},
            "per_function": per_fn,
        }, indent=1))
        print("\nwrote %s" % args.json)


if __name__ == "__main__":
    main()
