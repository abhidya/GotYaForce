#!/usr/bin/env python3
"""Verify which caught source matrix belongs to Player 1's borg.

Input: persistent source-matrix addresses from scripts/gdb-catch-matrix-src.mjs.
Each is (presumably) a 3x4 row-major transform whose translation column sits at
+0x0c/+0x1c/+0x2c. Samples all candidates for N seconds while the game runs; reports
per-candidate translation ranges. Run it once while everything stands still, then again
while ONLY P1 moves (or drive P1 during the window) — the candidate whose translation
tracks the movement is P1's persistent world transform.

Usage: python scripts/dme_verify_sources.py 0x805xxxx 0x805yyyy ... [--seconds 10]
"""
import struct
import sys
import os
import time

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from dme_lib import hook_or_die
import dolphin_memory_engine as d


def main():
    addrs = [int(a, 16) for a in sys.argv[1:] if a.startswith("0x")]
    secs = 10.0
    if "--seconds" in sys.argv:
        secs = float(sys.argv[sys.argv.index("--seconds") + 1])
    if not addrs:
        sys.exit("usage: python scripts/dme_verify_sources.py 0x... 0x... [--seconds 10]")

    hook_or_die()
    series = {a: [] for a in addrs}
    t0 = time.time()
    while time.time() - t0 < secs:
        for a in addrs:
            try:
                blk = d.read_bytes(a, 0x30)
                tx = struct.unpack_from(">f", blk, 0x0C)[0]
                ty = struct.unpack_from(">f", blk, 0x1C)[0]
                tz = struct.unpack_from(">f", blk, 0x2C)[0]
                series[a].append((tx, ty, tz))
            except Exception:
                pass
        time.sleep(0.03)

    print("candidate  samples  Tx-range           Ty-range           Tz-range          last")
    for a in addrs:
        s = series[a]
        if not s:
            print(f"0x{a:08x}  unreadable")
            continue
        xs, ys, zs = [v[0] for v in s], [v[1] for v in s], [v[2] for v in s]
        def rng(vals):
            return f"{min(vals):8.1f}..{max(vals):8.1f}"
        print(f"0x{a:08x}  {len(s):5d}  {rng(xs)}  {rng(ys)}  {rng(zs)}  "
              f"({xs[-1]:.1f},{ys[-1]:.1f},{zs[-1]:.1f})")


if __name__ == "__main__":
    main()
