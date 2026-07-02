#!/usr/bin/env python3
"""Full-speed golden-trace recorder via Dolphin Memory Engine (no GDB, no CPU halt).

Polls the active borg struct as fast as the shared-memory interface allows while you play
the game normally, and emits one JSONL record per *distinct game frame* (dedup by detecting
a change in position or velocity — the external poll runs faster than 60 Hz, so raw samples
would double-count frames). Output schema matches scripts/trace-golden-record.mjs, so the
proven Node analyzer (scripts/trace-golden-analyze.mjs) reads it unchanged.

Base address comes from scripts/dme_find_borg.py (user-data/dolphin-trace/borg-base.txt) or
--base 0x....

Struct offsets (code-confirmed, research/decomp/borg-struct-offsets.txt):
  +0x44/48/4c pos f32   +0x58/5c/60 vel f32   +0x72 heading s16
  +0x544 state s32      +0x720 invuln f32

Usage:
  python scripts/dme_record.py --borg pl0615 --label movement-recipe --seconds 30
Play the recipe (stand / forward-run x2 / 3 jumps / 3 dashes / stand) during the window.
Pads are NOT read here (no code hook); the analyzer infers motion phases from the trajectory
itself, which is sufficient for gravity/jump/speed/dash fits.
"""
import argparse
import json
import os
import sys
import time

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from dme_lib import hook_or_die, read_f32, read_s32, read_s16
import dolphin_memory_engine as dme

OFF = dict(px=0x44, py=0x48, pz=0x4C, vx=0x58, vy=0x5C, vz=0x60, heading=0x72, state=0x544, invuln=0x720)


def read_state(base):
    return dict(
        pos=dict(x=read_f32(base + OFF["px"]), y=read_f32(base + OFF["py"]), z=read_f32(base + OFF["pz"])),
        vel=dict(x=read_f32(base + OFF["vx"]), y=read_f32(base + OFF["vy"]), z=read_f32(base + OFF["vz"])),
        heading=read_s16(base + OFF["heading"]),
        state=read_s32(base + OFF["state"]),
        invuln=read_f32(base + OFF["invuln"]),
    )


def changed(a, b, eps=1e-4):
    # Dedup on POSITION only. When tracking a render-pool copy the velocity field is not a
    # real per-frame velocity, so keying on it would over-sample; position change = new frame.
    if a is None:
        return True
    for k in ("x", "y", "z"):
        if abs(a["pos"][k] - b["pos"][k]) > eps:
            return True
    return False


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--borg", default="unknown")
    ap.add_argument("--label", default="golden")
    ap.add_argument("--seconds", type=float, default=30.0)
    ap.add_argument("--base", default=None, help="borg struct base, e.g. 0x805dc430")
    ap.add_argument("--out", default=None)
    ap.add_argument("--poll-hz", type=float, default=1000.0)
    args = ap.parse_args()

    base = None
    if args.base:
        base = int(args.base, 16)
    else:
        p = os.path.join(os.path.dirname(os.path.abspath(__file__)), "..", "user-data", "dolphin-trace", "borg-base.txt")
        if os.path.exists(p):
            base = int(open(p).read().strip(), 16)
    if base is None:
        sys.exit("no --base and no borg-base.txt; run scripts/dme_find_borg.py first")

    hook_or_die()
    out_path = args.out or os.path.abspath(
        os.path.join(os.path.dirname(os.path.abspath(__file__)), "..", "user-data", "dolphin-trace", "golden",
                     f"{args.label}-{args.borg}-{int(time.time())}.jsonl")
    )
    os.makedirs(os.path.dirname(out_path), exist_ok=True)

    meta = dict(
        schema="gf-golden-trace-v1", generatedBy="scripts/dme_record.py",
        recordedAt=time.strftime("%Y-%m-%dT%H:%M:%SZ", time.gmtime()), region="GG4E",
        borg=args.borg, label=args.label, borgBase=f"0x{base:08x}", borgBaseVia="dme-value-scan",
        capture="DME full-speed poll, deduped per distinct frame (no CPU halt)",
        offsets={"pos": "+0x44/48/4c f32", "vel": "+0x58/5c/60 f32", "heading": "+0x72 s16",
                 "state": "+0x544 s32", "invuln": "+0x720 f32"},
        note="no pad field (external poll has no code hook); analyzer infers phases from trajectory",
    )
    f = open(out_path, "w")
    f.write(json.dumps(meta) + "\n")

    print(f"recording ~{args.seconds:.0f}s from base 0x{base:08x} — play the recipe now")
    period = 1.0 / args.poll_hz
    deadline = time.time() + args.seconds
    prev = None
    frame = 0
    err_streak = 0
    while time.time() < deadline:
        try:
            s = read_state(base)
            err_streak = 0
        except Exception:
            err_streak += 1
            if err_streak > 200:
                print("read errors (emulator closed?) — stopping early")
                break
            time.sleep(period)
            continue
        if changed(prev, s):
            rec = dict(f=frame, pos=s["pos"], vel=s["vel"], heading=s["heading"], state=s["state"], invuln=s["invuln"])
            f.write(json.dumps(rec) + "\n")
            frame += 1
            prev = s
            if frame % 300 == 0:
                print(f"  {frame} frames")
        time.sleep(period)

    f.close()
    print(f"wrote {frame} frames to {out_path}")
    print(f"next: node scripts/trace-golden-analyze.mjs {out_path}")


if __name__ == "__main__":
    main()
