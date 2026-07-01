#!/usr/bin/env python3
"""
Continuously logs the 5 confirmed HP-mirror addresses from a running Dolphin instance
(behavior-notes.md s4f/s4h) to a CSV, so combat samples come from passive background
logging instead of manually babysitting Dolphin's built-in breakpoint UI.

Usage:
    pip install dolphin-memory-engine --break-system-packages
    python3 dolphin-hp-logger.py [--out hp_log.csv] [--interval 0.05]

Requires a running Dolphin instance with Gotcha Force (GG4E) loaded. Re-attempts the
hook every `interval` seconds until Dolphin is found, then polls and logs on any change.
"""
import argparse
import csv
import struct
import sys
import time

import dolphin_memory_engine as dme

# Confirmed live (2026-07-01): behavior-notes.md s4f/s4h. All 5 mirror the same on-screen
# HP value; logging all 5 lets us sanity-check they stay in sync (and catch it if they don't).
HP_ADDRESSES = {
    "hud_mirror_803b069c": 0x803B069C,
    "obj_field_805dbf86": 0x805DBF86,
    "mirror_805f3850": 0x805F3850,
    "mirror_805f3858": 0x805F3858,
    "mirror_805f385c": 0x805F385C,
}


def read_s16(addr: int) -> int:
    raw = dme.read_bytes(addr, 2)
    return struct.unpack(">h", raw)[0]


def wait_for_hook(interval: float) -> None:
    while not dme.is_hooked():
        dme.hook()
        if dme.is_hooked():
            return
        status = dme.get_status()
        print(f"waiting for Dolphin (status={status})...", file=sys.stderr)
        time.sleep(interval)


def main() -> None:
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--out", default="hp_log.csv")
    ap.add_argument("--interval", type=float, default=0.05, help="poll interval, seconds")
    args = ap.parse_args()

    wait_for_hook(args.interval)
    print("Hooked to Dolphin. Logging HP-address changes to", args.out)

    last = {name: None for name in HP_ADDRESSES}
    with open(args.out, "a", newline="") as f:
        writer = csv.writer(f)
        if f.tell() == 0:
            writer.writerow(["t", "address_name", "address", "old", "new"])
        t0 = time.time()
        while True:
            if not dme.is_hooked():
                print("lost hook, re-waiting...", file=sys.stderr)
                wait_for_hook(args.interval)
            for name, addr in HP_ADDRESSES.items():
                try:
                    val = read_s16(addr)
                except RuntimeError:
                    continue
                if last[name] is not None and val != last[name]:
                    row = [f"{time.time() - t0:.3f}", name, hex(addr), last[name], val]
                    writer.writerow(row)
                    f.flush()
                    print(row)
                last[name] = val
            time.sleep(args.interval)


if __name__ == "__main__":
    main()
