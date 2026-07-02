#!/usr/bin/env python3
"""Golden-trace recorder reading a FIXED-ADDRESS per-player transform matrix.

The gdb-catch-matrix-src session (behavior-notes §aa follow-up) proved the four players'
persistent world transforms live in static memory at stride 0x3E4:
  P? 0x803c7744, 0x803c7b28, 0x803c7f0c, 0x803c82f0   (identify which is P1 by driving input)
Each is a GC 3x4 row-major matrix; world translation at +0x0C (x), +0x1C (y), +0x2C (z).

Records one JSONL row per distinct frame (position change), schema-compatible with
scripts/trace-golden-analyze.mjs.

Usage: python scripts/dme_record_matrix.py --matrix 0x803c7744 --borg pl0615 --label recipe --seconds 60
"""
import argparse
import json
import os
import struct
import sys
import time

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from dme_lib import hook_or_die
import dolphin_memory_engine as d


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--matrix", required=True, help="fixed matrix address, e.g. 0x803c7744")
    ap.add_argument("--borg", default="pl0615")
    ap.add_argument("--label", default="recipe")
    ap.add_argument("--seconds", type=float, default=60.0)
    ap.add_argument("--out", default=None)
    args = ap.parse_args()
    base = int(args.matrix, 16)

    hook_or_die()
    out_path = args.out or os.path.abspath(os.path.join(
        os.path.dirname(os.path.abspath(__file__)), "..", "user-data", "dolphin-trace", "golden",
        f"{args.label}-{args.borg}-matrix.jsonl"))
    os.makedirs(os.path.dirname(out_path), exist_ok=True)

    meta = dict(schema="gf-golden-trace-v1", generatedBy="scripts/dme_record_matrix.py",
                recordedAt=time.strftime("%Y-%m-%dT%H:%M:%SZ", time.gmtime()), region="GG4E",
                borg=args.borg, label=args.label, borgBase=args.matrix,
                borgBaseVia="fixed static per-player transform (gdb-catch-matrix-src)",
                capture="DME full-speed, matrix translation +0x0C/+0x1C/+0x2C, deduped per frame")
    f = open(out_path, "w")
    f.write(json.dumps(meta) + "\n")

    print(f"recording ~{args.seconds:.0f}s from matrix 0x{base:08x} — DO THE RECIPE NOW", flush=True)
    prev = None
    frame = 0
    deadline = time.time() + args.seconds
    while time.time() < deadline:
        try:
            blk = d.read_bytes(base, 0x30)
        except Exception:
            time.sleep(0.001)
            continue
        tx = struct.unpack_from(">f", blk, 0x0C)[0]
        ty = struct.unpack_from(">f", blk, 0x1C)[0]
        tz = struct.unpack_from(">f", blk, 0x2C)[0]
        if not all(abs(v) < 50000 and v == v for v in (tx, ty, tz)):
            time.sleep(0.001)
            continue
        cur = (tx, ty, tz)
        if prev is None or any(abs(cur[i] - prev[i]) > 1e-4 for i in range(3)):
            f.write(json.dumps(dict(f=frame, pos=dict(x=tx, y=ty, z=tz))) + "\n")
            frame += 1
            prev = cur
            if frame % 300 == 0:
                print(f"  {frame} frames", flush=True)
        time.sleep(0.001)

    f.close()
    print(f"wrote {frame} frames to {out_path}", flush=True)
    print(f"analyze: node scripts/trace-golden-analyze.mjs {out_path}", flush=True)


if __name__ == "__main__":
    main()
