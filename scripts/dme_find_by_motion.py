#!/usr/bin/env python3
"""Pin the active borg struct base by POSITION SMOOTHNESS + PERSISTENCE over a walk.

Why this beats the earlier value-scan and invuln approaches:
- Value-scan (still vs moved, 2 frames) drowns in render/scratch buffers that also "moved".
- Invuln countdown is not unique — many objects run 60->0 timers.
- The gameplay borg position (+0x44 x/y/z, code-confirmed) lives in a STABLE allocation and
  changes SMOOTHLY as you walk. The render pool at 0x80614xxx that fooled earlier scans is
  DOUBLE-BUFFERED — the same address flips between the real coordinate and zero/garbage every
  frame, so a "no large frame-to-frame jumps" filter rejects it. A smooth, persistent, world-
  ranged moving vec3 whose base+0x544 is a valid small-int state is essentially uniquely the borg.

Method (numpy): sample full MEM1 ~N times over a few seconds while you WALK continuously (any
direction — model-independent). Interpret as big-endian f32; find X columns that are finite,
in world range, moved a real distance, and never jump more than a small fraction of the total
in one step; require the paired Z (2 cols later) to also move smoothly; confirm base+0x544
state. Writes the best base to user-data/dolphin-trace/borg-base.txt.

Usage: python scripts/dme_find_by_motion.py [--samples 60] [--interval 0.06]
Run it while walking your borg around for the whole capture (~4s).
"""
import argparse
import os
import sys
import time

import numpy as np

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from dme_lib import hook_or_die, read_f32, read_s32
import dolphin_memory_engine as d

MEM1_LO, SIZE = 0x80000000, 0x1800000
POS_OFF, STATE_OFF = 0x44, 0x544
WORLD = 20000.0


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--samples", type=int, default=60)
    ap.add_argument("--interval", type=float, default=0.06)
    ap.add_argument("--min-move", type=float, default=80.0)
    args = ap.parse_args()

    hook_or_die()
    print(f"capturing {args.samples} snapshots over ~{args.samples*args.interval:.1f}s — "
          "WALK your borg continuously NOW", flush=True)
    snaps = []
    for _ in range(args.samples):
        snaps.append(np.frombuffer(d.read_bytes(MEM1_LO, SIZE), dtype=">f4").astype(np.float32))
        time.sleep(args.interval)
    print("scanning for a smooth, persistent, world-ranged moving position ...", flush=True)

    np.seterr(all="ignore")
    arr = np.vstack(snaps)  # [N, cols]
    N, cols = arr.shape

    finite = np.isfinite(arr).all(axis=0)
    in_range = (np.abs(arr) < WORLD).all(axis=0)
    vmax = arr.max(axis=0)
    vmin = arr.min(axis=0)
    rng = vmax - vmin
    moved = rng >= args.min_move
    jumps = np.abs(np.diff(arr, axis=0)).max(axis=0)  # largest single-step change per column
    # Smooth: no single step is more than 40% of the total range (buffers that flip to zero
    # produce a jump ~= the full range, failing this), and no absurd absolute jump.
    smooth = (jumps <= 0.4 * np.maximum(rng, 1e-6)) & (jumps < 400.0)

    xmask = finite & in_range & moved & smooth
    xcols = np.nonzero(xmask)[0]
    if xcols.size == 0:
        # Diagnostics: show the biggest finite, in-range MOVERS (ignoring the smooth filter)
        # so we can see whether anything moved at all and why it was rejected.
        movers = finite & in_range & (rng >= 10.0)
        idx = np.nonzero(movers)[0]
        print(f"DIAG: {idx.size} finite in-range columns moved >=10 units.", flush=True)
        if idx.size:
            order = idx[np.argsort(-rng[idx])][:10]
            print("DIAG top movers (addr, range, maxjump, jump/range):", flush=True)
            for c in order:
                a = MEM1_LO + int(c) * 4
                jr = float(jumps[c] / max(rng[c], 1e-6))
                print(f"  0x{a:08x}  range={rng[c]:.1f}  maxjump={jumps[c]:.1f}  jr={jr:.2f}", flush=True)
        else:
            print("DIAG: nothing moved — the borg likely wasn't walking (or game paused).", flush=True)
        sys.exit("no smooth moving X found — see DIAG above.")

    cands = []
    for xc in xcols:
        zc = xc + 2  # z sits two f32 after x (+0x44 -> +0x4c)
        if zc >= cols or not xmask[zc]:
            continue
        addr = MEM1_LO + int(xc) * 4
        base = addr - POS_OFF
        if not (MEM1_LO <= base + STATE_OFF < MEM1_LO + SIZE):
            continue
        try:
            st = read_s32(base + STATE_OFF)
            px, py, pz = read_f32(base + POS_OFF), read_f32(base + POS_OFF + 4), read_f32(base + POS_OFF + 8)
        except Exception:
            continue
        if not (-1 <= st <= 64):
            continue  # a real borg MUST have a valid small-int state field
        horiz_move = float(np.hypot(rng[xc], rng[zc]))
        smoothness = 1.0 / (1.0 + float(jumps[xc] + jumps[zc]))
        score = min(horiz_move, 2000.0) / 2000.0 * 40 + smoothness * 40 + 20  # +20 valid state
        cands.append((score, base, st, (px, py, pz), horiz_move, float(jumps[xc])))

    if not cands:
        sys.exit("smooth motion found but no valid borg struct around it — walk and re-run.")
    cands.sort(reverse=True)
    print("\ncandidates (score, base, state, pos, moved, maxjump):", flush=True)
    for score, base, st, pos, mv, jp in cands[:8]:
        print(f"  score={score:5.1f}  base=0x{base:08x}  state={st}  "
              f"pos=({pos[0]:.1f},{pos[1]:.1f},{pos[2]:.1f})  moved={mv:.0f}  maxjump={jp:.1f}", flush=True)

    top, runner = cands[0], (cands[1][0] if len(cands) > 1 else 0)
    strong = top[0] - runner >= 10 or len(cands) == 1
    best = top[1]
    out = os.path.abspath(os.path.join(os.path.dirname(os.path.abspath(__file__)), "..",
                                       "user-data", "dolphin-trace", "borg-base.txt"))
    os.makedirs(os.path.dirname(out), exist_ok=True)
    if strong:
        with open(out, "w") as f:
            f.write(f"0x{best:08x}\n")
        print(f"\nbest base = 0x{best:08x}  (STRONG) -> wrote {out}", flush=True)
    else:
        print(f"\nbest base = 0x{best:08x}  (WEAK — several close candidates; re-run with a "
              "longer, single-direction walk). NOT written.", flush=True)


if __name__ == "__main__":
    main()
