#!/usr/bin/env python3
"""Golden-trace recorder using the DETERMINISTIC pointer chain (dme_borg.py).

Resolves player 0's active borg base FROM THE POINTER CHAIN every poll, so it follows the
real gameplay struct through pauses/deaths/borg-switches — no fragile RAM-scanned address.
Records the real struct fields (pos +0x44, vel +0x58, heading +0x72, state +0x544, invuln
+0x720), one JSONL row per distinct game frame. Schema matches the Node analyzer.

Usage: python scripts/dme_record_chain.py --borg pl0615 --label recipe --seconds 60
Only records while a valid borg is resolvable and moving (pauses add nothing). Flags a base
change (borg switch/death) as a discontinuity so the analyzer can segment.
"""
import argparse
import json
import os
import sys
import time

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from dme_lib import hook_or_die
from dme_borg import active_borg_base, borg_fields, validate


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--borg", default="pl0615")
    ap.add_argument("--label", default="recipe")
    ap.add_argument("--seconds", type=float, default=60.0)
    ap.add_argument("--out", default=None)
    ap.add_argument("--pos-off", default="0x44",
                    help="position vec3 offset in the actor struct (0x44 classic; 0x20 in 4P versus — behavior-notes §ac)")
    args = ap.parse_args()
    pos_off = int(args.pos_off, 16)

    hook_or_die()
    out_path = args.out or os.path.abspath(os.path.join(
        os.path.dirname(os.path.abspath(__file__)), "..", "user-data", "dolphin-trace", "golden",
        f"{args.label}-{args.borg}-chain.jsonl"))
    os.makedirs(os.path.dirname(out_path), exist_ok=True)

    meta = dict(schema="gf-golden-trace-v1", generatedBy="scripts/dme_record_chain.py",
                recordedAt=time.strftime("%Y-%m-%dT%H:%M:%SZ", time.gmtime()), region="GG4E",
                borg=args.borg, label=args.label, borgBaseVia="pointer-chain 0x80433934/0x803C4E84",
                capture="DME full-speed, deterministic gameplay struct, deduped per frame",
                offsets={"pos": "+0x44/48/4c f32", "vel": "+0x58/5c/60 f32", "heading": "+0x72 s16",
                         "state": "+0x544 s32", "invuln": "+0x720 f32"})
    f = open(out_path, "w")
    f.write(json.dumps(meta) + "\n")

    print(f"recording ~{args.seconds:.0f}s via pointer chain — DO THE RECIPE NOW", flush=True)
    prev_pos = None
    prev_base = None
    frame = 0
    switches = 0
    invalid_streak = 0
    deadline = time.time() + args.seconds
    period = 0.001
    while time.time() < deadline:
        base, slot, _ = active_borg_base()
        if base is None or not validate(base, slot):
            invalid_streak += 1
            time.sleep(period)
            continue
        invalid_streak = 0
        try:
            fld = borg_fields(base, pos_off=pos_off)
        except Exception:
            time.sleep(period); continue
        p = fld["pos"]
        moved = prev_pos is None or any(abs(p[k] - prev_pos[k]) > 1e-4 for k in ("x", "y", "z"))
        base_changed = prev_base is not None and base != prev_base
        if moved or base_changed:
            if base_changed:
                switches += 1
            rec = dict(f=frame, pos=p, vel=fld["vel"], heading=fld["heading"],
                       state=fld["state"], invuln=fld["invuln"],
                       **({"switch": True} if base_changed else {}))
            f.write(json.dumps(rec) + "\n")
            frame += 1
            prev_pos = p
            prev_base = base
            if frame % 300 == 0:
                print(f"  {frame} frames", flush=True)
        time.sleep(period)

    f.close()
    print(f"wrote {frame} frames ({switches} borg-switch discontinuities) to {out_path}", flush=True)
    if frame < 60:
        print("TOO FEW FRAMES — game was paused most of the window; retry in a sustained fight.", flush=True)
    else:
        print(f"OK — analyze: node scripts/trace-golden-analyze.mjs {out_path}", flush=True)


if __name__ == "__main__":
    main()
