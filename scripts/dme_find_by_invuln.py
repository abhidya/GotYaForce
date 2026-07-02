#!/usr/bin/env python3
"""Pin the active borg struct base via the invincibility-timer countdown signature.

Far more specific than a position value-scan (which drowns in render-buffer false positives):
the wake-up/knockdown invulnerability field at struct+0x720 is a float that counts DOWN from
~60 to 0 at ~1.0 per frame (research/decomp/ram-trace-analysis.md; constant 60.0 @ 0x80437448,
loaded into +0x720 per borg-struct-offsets.txt). A float monotonically decreasing through most
of the 0..60 range over ~1 second is essentially unique in MEM1.

Method (numpy-vectorized): take N MEM1 snapshots over ~1.3s while the timer runs, interpret
each as big-endian float32, and keep offsets where the value is monotonically non-increasing,
stays in (0, 61], and drops by a meaningful total. base = addr - 0x720; confirm +0x544 (small
int state) and +0x44/48/4c (sane world position).

Trigger: run this right after your borg SPAWNS or gets KNOCKED DOWN (both start the timer).

Usage: python scripts/dme_find_by_invuln.py [--samples 24] [--interval 0.05]
Writes the best base to user-data/dolphin-trace/borg-base.txt.
"""
import argparse
import os
import struct
import sys
import time

import numpy as np

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from dme_lib import hook_or_die, read_f32, read_s32
import dolphin_memory_engine as d

MEM1_LO, SIZE = 0x80000000, 0x1800000
INVULN_OFF, STATE_OFF, POS_OFF = 0x720, 0x544, 0x44


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--samples", type=int, default=24)
    ap.add_argument("--interval", type=float, default=0.05)
    args = ap.parse_args()

    hook_or_die()
    print(f"capturing {args.samples} MEM1 snapshots over ~{args.samples*args.interval:.1f}s — "
          "trigger a spawn/knockdown NOW", flush=True)
    snaps = []
    for _ in range(args.samples):
        snaps.append(np.frombuffer(d.read_bytes(MEM1_LO, SIZE), dtype=">f4").astype(np.float32))
        time.sleep(args.interval)
    print("scanning for the invulnerability countdown signature ...", flush=True)

    arr = np.vstack(snaps)  # [N, cols]
    np.seterr(invalid="ignore")  # NaN garbage floats compare false; the finite mask handles them

    # Forgiving signature (the hit may land anywhere in the window, and the timer may reach 0
    # partway): the value PEAKED high, dropped a lot, and the peak came before the trough.
    # Combined with the bounded 0..61 range this is still essentially unique to +0x720.
    finite = np.isfinite(arr).all(axis=0)
    vmax = arr.max(axis=0)
    vmin = arr.min(axis=0)
    imax = arr.argmax(axis=0)
    imin = arr.argmin(axis=0)
    bounded = (vmax <= 61.5) & (vmin >= -0.1)
    started_high = vmax >= 30.0
    dropped_flag = (vmax - vmin) >= 10.0
    peak_before_trough = imax < imin
    ends_low = arr[-1] <= vmax - 5.0  # still falling or bottomed out, not risen back up

    mask = finite & bounded & started_high & dropped_flag & peak_before_trough & ends_low
    total_drop = vmax - vmin
    first, last = vmax, vmin  # report peak/trough as the meaningful range
    cols = np.nonzero(mask)[0]
    if cols.size == 0:
        sys.exit("no countdown signature found — run this DURING the ~1s after a spawn/knockdown.")

    cands = []
    for c in cols:
        addr = MEM1_LO + int(c) * 4
        base = addr - INVULN_OFF
        if not (MEM1_LO <= base < MEM1_LO + SIZE):
            continue
        try:
            st = read_s32(base + STATE_OFF)
            px, py, pz = read_f32(base + POS_OFF), read_f32(base + POS_OFF + 4), read_f32(base + POS_OFF + 8)
        except Exception:
            continue
        valid_state = -1 <= st <= 64
        valid_pos = all(np.isfinite(v) and abs(v) < 20000 for v in (px, py, pz)) and (abs(px) + abs(pz)) > 1.0
        # A real borg struct MUST have a valid small-int state field. Reject anything else so
        # a coincidental countdown next to garbage can't score high.
        if not valid_state:
            continue
        score = float(total_drop[c]) + 20  # base + valid-state credit
        if valid_pos:
            score += 20
        cands.append((score, base, addr, float(first[c]), float(last[c]), st, (px, py, pz), valid_pos))

    if not cands:
        sys.exit("countdown floats found but none had a valid struct around them — retry.")
    cands.sort(reverse=True)
    print("\ncandidates (score, base, invuln first->last, state, pos):", flush=True)
    for score, base, addr, f0, f1, st, pos, vpos in cands[:8]:
        print(f"  score={score:5.1f}  base=0x{base:08x}  invuln {f0:.1f}->{f1:.1f}  state={st}  "
              f"pos=({pos[0]:.1f},{pos[1]:.1f},{pos[2]:.1f})", flush=True)

    best = cands[0][1]
    # STRONG only when the top pick has BOTH a valid state AND a sane non-origin position,
    # AND it's clearly ahead of the runner-up (no ambiguous tie).
    top = cands[0]
    runner = cands[1][0] if len(cands) > 1 else 0
    strong = top[7] and (top[0] - runner >= 15 or len(cands) == 1)
    if not strong:
        print("NOT STRONG — top pick lacks a clean valid-state+position lead. "
              "Re-run once the battle is live and your borg has just been hit.", flush=True)
    out = os.path.abspath(os.path.join(os.path.dirname(os.path.abspath(__file__)), "..",
                                       "user-data", "dolphin-trace", "borg-base.txt"))
    os.makedirs(os.path.dirname(out), exist_ok=True)
    if strong:
        with open(out, "w") as f:
            f.write(f"0x{best:08x}\n")
        print(f"\nbest base = 0x{best:08x}  (STRONG) -> wrote {out}", flush=True)
    else:
        print(f"\nbest base = 0x{best:08x}  (WEAK — NOT written; awaiting a clean capture)", flush=True)


if __name__ == "__main__":
    main()
