#!/usr/bin/env python3
"""One-shot live capture: find the borg position address, then record the movement recipe
from it in the SAME process (no gap for the render pool to reallocate).

Phase 1 (FIND, ~4s): while you WALK continuously, sample MEM1 and pick the smoothest,
  most-persistent, world-ranged moving position (the borg). Uses the same discriminator as
  dme_find_by_motion.py (rejects flipping render buffers via a no-large-jumps filter).
Phase 2 (RECORD, ~40s): poll that address every frame and log position to a golden JSONL,
  deduped per distinct frame. Flags big discontinuities (pool moved / borg swapped) so a bad
  run is obvious instead of silently corrupt.

Output schema matches scripts/trace-golden-record.mjs so the proven Node analyzer reads it.

Usage: python scripts/dme_capture_session.py --borg pl0615 --label recipe [--record-secs 40]
Prints phase markers (PHASE=find / BASE_LOCKED / PHASE=record) so the caller can relay cues.
"""
import argparse
import json
import os
import sys
import time

import numpy as np

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from dme_lib import hook_or_die, read_f32, read_s32
import dolphin_memory_engine as d

MEM1_LO, SIZE = 0x80000000, 0x1800000
POS = 0x44
WORLD = 20000.0


def find_base(find_secs, interval=0.05, min_move=40.0):
    n = max(20, int(find_secs / interval))
    snaps = [np.frombuffer(d.read_bytes(MEM1_LO, SIZE), dtype=">f4").astype(np.float32) for _ in _tick(n, interval)]
    np.seterr(all="ignore")
    arr = np.vstack(snaps)
    finite = np.isfinite(arr).all(axis=0)
    in_range = (np.abs(arr) < WORLD).all(axis=0)
    vmax, vmin = arr.max(axis=0), arr.min(axis=0)
    rng = vmax - vmin
    jumps = np.abs(np.diff(arr, axis=0)).max(axis=0)
    smooth = (jumps <= 0.4 * np.maximum(rng, 1e-6)) & (jumps < 400.0)
    xmask = finite & in_range & (rng >= min_move) & smooth
    best = None
    for xc in np.nonzero(xmask)[0]:
        zc = xc + 2
        if zc >= arr.shape[1] or not xmask[zc]:
            continue
        base = MEM1_LO + int(xc) * 4 - POS
        if not (MEM1_LO <= base + 0x544 < MEM1_LO + SIZE):
            continue
        try:
            st = read_s32(base + 0x544)
        except Exception:
            continue
        if not (-1 <= st <= 64):
            continue
        moved = float(np.hypot(rng[xc], rng[zc]))
        score = min(moved, 2000.0)
        if best is None or score > best[0]:
            best = (score, base, moved)
    return best


def _tick(n, interval):
    for _ in range(n):
        yield True
        time.sleep(interval)


def record(base, seconds, out_path, meta):
    f = open(out_path, "w")
    f.write(json.dumps(meta) + "\n")
    prev = None
    frame = 0
    jumps = 0
    deadline = time.time() + seconds
    period = 0.001
    while time.time() < deadline:
        try:
            px, py, pz = read_f32(base + 0x44), read_f32(base + 0x48), read_f32(base + 0x4c)
        except Exception:
            time.sleep(period); continue
        if not all(abs(v) < WORLD for v in (px, py, pz)):
            time.sleep(period); continue
        cur = (px, py, pz)
        if prev is None or any(abs(cur[i] - prev[i]) > 1e-4 for i in range(3)):
            if prev is not None:
                d3 = ((cur[0]-prev[0])**2 + (cur[2]-prev[2])**2) ** 0.5
                if d3 > 500.0:
                    jumps += 1  # discontinuity: pool moved or borg swapped
            f.write(json.dumps(dict(f=frame, pos=dict(x=px, y=py, z=pz))) + "\n")
            frame += 1
            prev = cur
            if frame % 300 == 0:
                print(f"  {frame} frames", flush=True)
        time.sleep(period)
    f.close()
    return frame, jumps


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--borg", default="pl0615")
    ap.add_argument("--label", default="recipe")
    ap.add_argument("--find-secs", type=float, default=4.0)
    ap.add_argument("--record-secs", type=float, default=40.0)
    args = ap.parse_args()

    hook_or_die()
    print("PHASE=find WALK your borg continuously for ~4s (any direction)", flush=True)
    best = find_base(args.find_secs)
    if best is None:
        sys.exit("FIND FAILED — no smooth moving position (borg wasn't moving / game paused). Retry.")
    score, base, moved = best
    print(f"BASE_LOCKED base=0x{base:08x} (moved {moved:.0f} during find)", flush=True)

    out_path = os.path.abspath(os.path.join(os.path.dirname(os.path.abspath(__file__)), "..",
                                            "user-data", "dolphin-trace", "golden",
                                            f"{args.label}-{args.borg}-live.jsonl"))
    os.makedirs(os.path.dirname(out_path), exist_ok=True)
    meta = dict(schema="gf-golden-trace-v1", generatedBy="scripts/dme_capture_session.py",
                recordedAt=time.strftime("%Y-%m-%dT%H:%M:%SZ", time.gmtime()), region="GG4E",
                borg=args.borg, label=args.label, borgBase=f"0x{base:08x}", borgBaseVia="dme-motion-scan",
                capture="DME full-speed, render-pool position, deduped per frame",
                note="position-only (render base); analyzer derives velocity from deltas")
    print(f"PHASE=record RECORDING ~{args.record_secs:.0f}s — DO THE RECIPE NOW", flush=True)
    frames, jumps = record(base, args.record_secs, out_path, meta)
    print(f"wrote {frames} frames ({jumps} discontinuities) to {out_path}", flush=True)
    if frames < 60:
        print("TOO FEW FRAMES — game likely paused mid-record; retry in a sustained fight.", flush=True)
    elif jumps > 5:
        print("MANY DISCONTINUITIES — the render address drifted; retry (or use the pointer-chain base).", flush=True)
    else:
        print(f"OK — analyze with: node scripts/trace-golden-analyze.mjs {out_path}", flush=True)


if __name__ == "__main__":
    main()
