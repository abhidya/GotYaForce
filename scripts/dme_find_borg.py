#!/usr/bin/env python3
"""Locate the active player borg's struct base in live RAM via a motion value-scan.

No GDB, no code breakpoints. The method is Cheat-Engine-style:
  1. Snapshot MEM1 while the borg stands STILL.
  2. Snapshot again after it MOVED horizontally.
  3. A gameplay borg position is a contiguous float vec3 at struct+0x44/48/4c
     (code-confirmed, research/decomp/borg-struct-offsets.txt). Find 4-byte-aligned
     offsets where X (+0x44) and Z (+0x4c) changed by a plausible per-move amount, Y
     (+0x48) barely changed, and the values are in a sane world range.
  4. Rank candidates and confirm the struct by checking +0x720 (invuln, 0..~60 float)
     and +0x544 (small int state). Struct base = position_addr - 0x44.

Usage:
  python scripts/dme_find_borg.py
It will prompt: stand still -> ENTER; then move -> ENTER. Prints ranked base candidates
and writes the best to user-data/dolphin-trace/borg-base.txt for the recorder to read.
"""
import struct
import sys
import os
import time

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from dme_lib import hook_or_die, read_f32, read_s32, is_mem1, MEM1_LO
import dolphin_memory_engine as dme

WORLD_LO, WORLD_HI = -50000.0, 50000.0
POS_OFF, Y_OFF, Z_OFF = 0x44, 0x48, 0x4C
INVULN_OFF, STATE_OFF = 0x720, 0x544


def snap():
    return dme.read_bytes(MEM1_LO, 0x1800000)


def f32(buf, i):
    return struct.unpack_from(">f", buf, i)[0]


def sane(v):
    return v == v and WORLD_LO < v < WORLD_HI  # v==v rejects NaN


def find(still, moved, min_move=1.0, max_move=1500.0):
    cands = []
    n = len(still)
    for i in range(0, n - 12, 4):
        try:
            x0, y0, z0 = f32(still, i), f32(still, i + 4), f32(still, i + 8)
            x1, y1, z1 = f32(moved, i), f32(moved, i + 4), f32(moved, i + 8)
        except struct.error:
            continue
        if not (sane(x0) and sane(z0) and sane(x1) and sane(z1)):
            continue
        dx, dz, dy = abs(x1 - x0), abs(z1 - z0), abs(y1 - y0)
        horiz = (dx * dx + dz * dz) ** 0.5
        if horiz < min_move or horiz > max_move:
            continue
        if dy > horiz * 0.5:  # mostly-horizontal motion
            continue
        addr = MEM1_LO + i
        base = addr - POS_OFF
        score = 0.0
        # Confirm struct fields relative to the candidate base.
        try:
            inv = read_f32(base + INVULN_OFF)
            st = read_s32(base + STATE_OFF)
        except Exception:
            continue
        if 0.0 <= inv <= 61.0:
            score += 2.0
        if -1 <= st <= 64:
            score += 1.0
        # Prefer plausible mid-arena magnitudes and clear movement.
        score += min(horiz, 400.0) / 400.0
        cands.append((score, base, addr, (x1, y1, z1), horiz, inv, st))
    cands.sort(reverse=True)
    return cands


def verify_by_velocity(bases, seconds=8.0, poll_hz=200.0):
    """Rank candidate bases by how well the velocity field (+0x58/5c/60) integrates to the
    change in the position field (+0x44/48/4c) over a live motion window. At the real borg
    struct these agree frame-to-frame; at a coincidental buffer they don't. Returns
    [(score, base, samples, moved_total)] sorted best-first."""
    import time
    series = {b: [] for b in bases}
    t_end = time.time() + seconds
    period = 1.0 / poll_hz
    while time.time() < t_end:
        for b in bases:
            try:
                px, py, pz = read_f32(b + POS_OFF), read_f32(b + Y_OFF), read_f32(b + Z_OFF)
                vx, vy, vz = read_f32(b + 0x58), read_f32(b + 0x5C), read_f32(b + 0x60)
            except Exception:
                continue
            series[b].append((px, py, pz, vx, vy, vz))
        time.sleep(period)

    ranked = []
    for b, s in series.items():
        if len(s) < 20:
            continue
        # Keep only distinct frames (position or velocity changed).
        frames = [s[0]]
        for row in s[1:]:
            p = frames[-1]
            if any(abs(row[k] - p[k]) > 1e-4 for k in range(6)):
                frames.append(row)
        if len(frames) < 8:
            continue
        agree = 0.0
        total = 0.0
        moved = 0.0
        for i in range(1, len(frames)):
            dpx, dpz = frames[i][0] - frames[i - 1][0], frames[i][2] - frames[i - 1][2]
            vx, vz = frames[i - 1][3], frames[i - 1][5]
            moved += (dpx * dpx + dpz * dpz) ** 0.5
            dmag = (dpx * dpx + dpz * dpz) ** 0.5
            vmag = (vx * vx + vz * vz) ** 0.5
            if dmag < 1e-3 and vmag < 1e-3:
                continue
            total += 1
            # velocity should point along the position delta AND match magnitude.
            if dmag > 1e-3 and vmag > 1e-3:
                cos = (dpx * vx + dpz * vz) / (dmag * vmag)
                magr = min(vmag, dmag) / max(vmag, dmag)
                if cos > 0.9 and magr > 0.6:
                    agree += 1
        score = (agree / total) if total >= 5 else 0.0
        ranked.append((score, b, len(frames), moved))
    ranked.sort(reverse=True)
    return ranked


def main():
    import argparse
    ap = argparse.ArgumentParser()
    ap.add_argument("--still-secs", type=float, default=6.0, help="seconds to hold still before snap 1")
    ap.add_argument("--move-secs", type=float, default=6.0, help="seconds to move before snap 2")
    args = ap.parse_args()

    hook_or_die()
    sys.stdout.reconfigure(line_buffering=True) if hasattr(sys.stdout, "reconfigure") else None
    print("PHASE=hooked", flush=True)
    print(f"PHASE=stand-still HOLD STILL for {args.still_secs:.0f}s", flush=True)
    time.sleep(args.still_secs)
    still = snap()
    print("SNAP1 captured", flush=True)
    print(f"PHASE=move MOVE THE BORG NOW for {args.move_secs:.0f}s (hold one direction)", flush=True)
    time.sleep(args.move_secs)
    moved = snap()
    print("SNAP2 captured — scanning MEM1 for a moving position vec3 ...", flush=True)
    cands = find(still, moved)
    if not cands:
        sys.exit("no candidate found — try a larger, cleaner movement and re-run.")
    print(f"scan found {len(cands)} motion candidates; verifying by velocity correlation ...", flush=True)
    # De-duplicate to unique bases, cap the pool, then live-verify.
    seen = set()
    pool = []
    for c in cands:
        if c[1] in seen:
            continue
        seen.add(c[1])
        pool.append(c[1])
        if len(pool) >= 400:
            break
    print(f"PHASE=verify KEEP MOVING AND TURNING for 8s (walk + change direction)", flush=True)
    ranked = verify_by_velocity(pool, seconds=8.0)
    if not ranked or ranked[0][0] < 0.5:
        print("VELOCITY CHECK inconclusive — best correlation was "
              f"{ranked[0][0]:.2f} at 0x{ranked[0][1]:08x}" if ranked else "no verifiable candidate", flush=True)
        print("re-run and move MORE (bigger walk + clear turns) so velocity is unambiguous.", flush=True)
        # still write the best guess, but flag it
    print("\nverified candidates (velocity-correlation, base, frames, moved):", flush=True)
    for score, base, nf, moved in ranked[:8]:
        pos = (read_f32(base + POS_OFF), read_f32(base + Y_OFF), read_f32(base + Z_OFF))
        print(f"  corr={score:4.2f}  base=0x{base:08x}  frames={nf}  moved={moved:.0f}  pos=({pos[0]:.1f},{pos[1]:.1f},{pos[2]:.1f})", flush=True)

    if not ranked:
        sys.exit("no verifiable candidate.")
    best = ranked[0][1]
    out = os.path.join(os.path.dirname(os.path.abspath(__file__)), "..", "user-data", "dolphin-trace", "borg-base.txt")
    out = os.path.abspath(out)
    os.makedirs(os.path.dirname(out), exist_ok=True)
    with open(out, "w") as f:
        f.write(f"0x{best:08x}\n")
    conf = "STRONG" if ranked[0][0] >= 0.8 else "WEAK" if ranked[0][0] >= 0.5 else "UNRELIABLE"
    print(f"\nbest base = 0x{best:08x}  (velocity-correlation {ranked[0][0]:.2f} = {conf}) -> wrote {out}", flush=True)


if __name__ == "__main__":
    main()
