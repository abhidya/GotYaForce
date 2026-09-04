#!/usr/bin/env python3
"""leaf_census.py -- size and shape distribution of every entry point in the DOL,
scored for "how hard is this to MATCH".

Matching decompilation's cost is not uniform across functions.  A 6-instruction
leaf accessor is a one-shot; a 400-instruction function with a jump table, a
float spill and inlined callees is a research problem.  This tool measures the
actual distribution so the scope arithmetic in
docs/matching-decompilation-spike.md is grounded rather than asserted.

Entry points come from research/decomp/data/oracle-registry.json (10,954
`functions` + 1,018 `excluded` = 11,972), unioned with the .text symbols of
research/symbols/GG4E-CSM-20220412.map.  A function's extent is capped at the
next entry point -- the same convention batch_recomp.py uses.

Classification per function (all from the encodings, nothing inferred):

  leaf            no bl / bctrl / blrl        -> no callee signature to get right
  n_calls         count of bl                 -> each is a symbol the linker must resolve
  jump_table      contains bctr               -> switch; MWCC's table layout must match
  float           any primary 48..55 / 59 / 63
  paired_single   any primary 4 / 56 / 57 / 60 / 61  (Gekko; needs -fp fmadd + ps)
  loop            any backward branch
  frame           has stwu r1                 -> non-trivial stack frame
  sda             loads/stores off r2 or r13  -> needs the SDA symbol assignment to match

Usage:
    python leaf_census.py --json out.json [--top 40]
"""
from __future__ import annotations

import argparse
import json
import struct
from collections import Counter
from pathlib import Path

import sys
sys.path.insert(0, str(Path(__file__).resolve().parent))
from dolsym import Dol, SymbolMap, REPO_DEFAULT  # noqa: E402

FLOAT_PRIMARY = set([48, 49, 50, 51, 52, 53, 54, 55, 59, 63])
PS_PRIMARY = set([4, 56, 57, 60, 61])
LOADSTORE_PRIMARY = set(range(32, 56))


def classify(words, base):
    n = len(words)
    n_calls = 0
    leaf = True
    jump_table = False
    has_float = False
    has_ps = False
    loop = False
    frame = False
    sda = 0
    blr = 0
    nops = 0
    forms = set()
    for i, w in enumerate(words):
        if w == 0x60000000:
            nops += 1
            continue
        op = w >> 26
        forms.add(op)
        if op == 18:  # b/bl/ba/bla
            lk = w & 1
            li = w & 0x03FFFFFC
            if li & 0x02000000:
                li -= 0x04000000
            tgt = (0 if (w & 2) else base + i * 4) + li
            if lk:
                n_calls += 1
                leaf = False
            elif tgt < base + i * 4:
                loop = True
        elif op == 16:  # bc
            bd = w & 0xFFFC
            if bd & 0x8000:
                bd -= 0x10000
            if w & 1:
                n_calls += 1
                leaf = False
            elif bd < 0:
                loop = True
        elif op == 19:
            xo = (w >> 1) & 0x3FF
            if xo == 528:  # bcctr
                if w & 1:
                    n_calls += 1
                    leaf = False
                else:
                    jump_table = True
            elif xo == 16:  # bclr
                if w & 1:
                    n_calls += 1
                    leaf = False
                else:
                    blr += 1
        if op in FLOAT_PRIMARY:
            has_float = True
        if op in PS_PRIMARY:
            has_ps = True
        if op == 37 and ((w >> 21) & 31) == 1 and ((w >> 16) & 31) == 1:
            frame = True
        if op in LOADSTORE_PRIMARY:
            ra = (w >> 16) & 31
            if ra in (2, 13):
                sda += 1
    return {
        "insns": n, "nops": nops, "leaf": leaf, "n_calls": n_calls,
        "jump_table": jump_table, "float": has_float, "paired_single": has_ps,
        "loop": loop, "frame": frame, "sda_refs": sda, "blr": blr,
        "n_forms": len(forms),
    }


def difficulty(c):
    """A blunt 0..n score: how much beyond 'transcribe the obvious C' this needs."""
    s = 0
    if c["insns"] > 24:
        s += 1
    if c["insns"] > 64:
        s += 1
    if c["insns"] > 160:
        s += 2
    if not c["leaf"]:
        s += 1
    if c["n_calls"] > 4:
        s += 1
    if c["jump_table"]:
        s += 2
    if c["float"]:
        s += 1
    if c["paired_single"]:
        s += 2
    if c["loop"]:
        s += 1
    if c["sda_refs"]:
        s += 1
    return s


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--repo", default=str(REPO_DEFAULT))
    ap.add_argument("--json")
    ap.add_argument("--top", type=int, default=30)
    a = ap.parse_args()
    repo = Path(a.repo)

    dol = Dol.from_iso(repo / "Gotcha Force.iso")
    smap = SymbolMap(repo / "research" / "symbols" / "GG4E-CSM-20220412.map")
    reg = json.loads((repo / "research" / "decomp" / "data" /
                      "oracle-registry.json").read_text())

    entries = {}
    for f in reg["functions"]:
        entries[int(f["address"], 16)] = f["name"]
    for f in reg["excluded"]:
        entries.setdefault(int(f["address"], 16), f["name"])
    for r in smap.text_functions():
        entries.setdefault(r["addr"], r["name"])

    addrs = sorted(a2 for a2 in entries if dol.is_text(a2))
    print("entry points in .text: %d (registry %d + %d, map %d)" % (
        len(addrs), len(reg["functions"]), len(reg["excluded"]),
        len(smap.text_functions())))

    # section end lookup
    def sect_end(addr):
        for off, adr, sz in dol.text:
            if adr <= addr < adr + sz:
                return adr + sz
        return addr

    out = []
    size_hist = Counter()
    diff_hist = Counter()
    tot_insns = 0
    for i, addr in enumerate(addrs):
        nxt = addrs[i + 1] if i + 1 < len(addrs) else sect_end(addr)
        end = min(nxt, sect_end(addr))
        size = end - addr
        if size <= 0 or size % 4:
            size -= size % 4
        if size <= 0:
            continue
        b = dol.read(addr, size)
        if b is None:
            continue
        n = size // 4
        words = struct.unpack(">%dI" % n, b)
        c = classify(words, addr)
        c["addr"] = "0x%08x" % addr
        c["name"] = entries[addr]
        c["difficulty"] = difficulty(c)
        out.append(c)
        tot_insns += n
        # bucket
        for lo, hi, lbl in [(1, 8, "1-8"), (9, 16, "9-16"), (17, 32, "17-32"),
                            (33, 64, "33-64"), (65, 128, "65-128"),
                            (129, 256, "129-256"), (257, 512, "257-512"),
                            (513, 10 ** 9, "513+")]:
            if lo <= n <= hi:
                size_hist[lbl] += 1
                break
        diff_hist[c["difficulty"]] += 1

    print("\n== size distribution (instructions per function) ==")
    order = ["1-8", "9-16", "17-32", "33-64", "65-128", "129-256", "257-512", "513+"]
    cum = 0
    for lbl in order:
        cum += size_hist[lbl]
        print("%-10s %6d  %5.1f%%  cum %5.1f%%" % (
            lbl, size_hist[lbl], 100.0 * size_hist[lbl] / len(out),
            100.0 * cum / len(out)))
    print("total functions %d, total instructions %d, mean %.1f" % (
        len(out), tot_insns, float(tot_insns) / len(out)))

    print("\n== shape ==")
    for k in ["leaf", "jump_table", "float", "paired_single", "loop", "frame"]:
        n = sum(1 for c in out if c[k])
        print("%-16s %6d  %5.1f%%" % (k, n, 100.0 * n / len(out)))
    n = sum(1 for c in out if c["sda_refs"])
    print("%-16s %6d  %5.1f%%" % ("sda_refs", n, 100.0 * n / len(out)))

    print("\n== difficulty score histogram ==")
    cum = 0
    for d in sorted(diff_hist):
        cum += diff_hist[d]
        print("score %2d  %6d  %5.1f%%  cum %5.1f%%" % (
            d, diff_hist[d], 100.0 * diff_hist[d] / len(out), 100.0 * cum / len(out)))

    print("\n== easiest matching candidates (leaf, no float/ps/jt, <= 16 insns) ==")
    cands = [c for c in out
             if c["leaf"] and not c["float"] and not c["paired_single"]
             and not c["jump_table"] and c["insns"] <= 16 and c["blr"] >= 1]
    cands.sort(key=lambda c: (c["insns"], c["sda_refs"], c["n_forms"]))
    print("%d candidates" % len(cands))
    for c in cands[:a.top]:
        print("  %-28s %s  %3d insns  sda=%d loop=%d frame=%d forms=%d" % (
            c["name"][:28], c["addr"], c["insns"], c["sda_refs"],
            c["loop"], c["frame"], c["n_forms"]))

    if a.json:
        Path(a.json).write_text(json.dumps({
            "entry_points": len(out),
            "total_instructions": tot_insns,
            "size_histogram": dict(size_hist),
            "difficulty_histogram": dict(diff_hist),
            "shape": {k: sum(1 for c in out if c[k])
                      for k in ["leaf", "jump_table", "float", "paired_single",
                                "loop", "frame"]},
            "functions": out,
        }, indent=1))
        print("\nwrote %s" % a.json)


if __name__ == "__main__":
    main()
