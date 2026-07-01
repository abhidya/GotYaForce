#!/usr/bin/env python3
"""
Scans live Dolphin RAM (MEM1) for borg battle-objects using the confirmed struct signature
from behavior-notes.md (s4h/s4i/s4l):
  +0x83  == 0        (alive/active flag)
  +0x1c4 (s16)        max HP, plausible range
  +0x1c6 (s16)        current HP, plausible range, <= +0x1c4
  +0x88  (byte)       type-mismatch tag, expected small (0..19ish, per the real type matrix
                       found at ROM address 0x802c5d60 -- see research/decomp/data/)

Purpose: find real in-memory borg objects during an actual battle so we can read +0x88 (and the
+0x3e4/+0x3e5/+0x999/+0x1000 slot-index chain from s4l) for two borgs of KNOWN DIFFERENT
`type` (borgs.json), to determine whether +0x88 is genuinely per-species or just per-slot.

Usage:
    pip install dolphin-memory-engine --break-system-packages
    python dolphin-scan-borg-objects.py                  # one-shot scan, prints all candidates
    python dolphin-scan-borg-objects.py --all            # include raw near-duplicate hits
    python dolphin-scan-borg-objects.py --watch 0x80abcd00   # poll one address's fields at 5/sec

Run this while a battle is actually happening (borgs spawned, visible HP bars) so the objects
exist in RAM. Cross-check the printed current/max HP against what's on-screen to figure out
which candidate is which borg.
"""
import argparse
import math
import struct
import sys
import time

import dolphin_memory_engine as dme

MEM1_START = 0x80000000
MEM1_SIZE = 0x01800000  # 24 MiB
CHUNK = 0x200000  # 2 MiB per read call

FIELDS = {
    "alive_flag_0x83": 0x83,
    "pos_x_0x44": 0x44,
    "pos_y_0x48": 0x48,
    "pos_z_0x4c": 0x4c,
    "maxhp_0x1c4": 0x1c4,
    "hp_0x1c6": 0x1c6,
    "type_byte_0x88": 0x88,
    "state_0x544": 0x544,
    "invuln_timer_0x720": 0x720,
    "slot_idx_0x3e4": 0x3e4,
    "slot_bitmask_0x3e5": 0x3e5,
    "cached_0x3e7": 0x3e7,   # object+999
    "cat_short_0x3e8": 0x3e8,  # object+1000
}


def read_s16_from(buf, off):
    return struct.unpack_from(">h", buf, off)[0]


def read_s8_from(buf, off):
    return struct.unpack_from(">b", buf, off)[0]


def read_f32_from(buf, off):
    return struct.unpack_from(">f", buf, off)[0]


def plausible_float(v, limit):
    return math.isfinite(v) and abs(v) <= limit


def score_candidate(buf, off, align):
    """Return (score, notes). Higher is more likely to be a real borg object base."""
    notes = []
    score = 0
    addr = MEM1_START + off

    if align and addr % align == 0:
        score += 3
        notes.append(f"aligned_{align:#x}")
    if addr % 0x20 == 0:
        score += 2
        notes.append("aligned_0x20")
    elif addr % 0x10 == 0:
        score += 1
        notes.append("aligned_0x10")

    maxhp = read_s16_from(buf, off + 0x1c4)
    hp = read_s16_from(buf, off + 0x1c6)
    if 0 < hp <= maxhp <= 2000:
        score += 4
        notes.append("hp_ok")

    type_byte = buf[off + 0x88]
    if type_byte <= 19:
        score += 2
        notes.append("type_0_19")
    elif type_byte <= 40:
        score += 1
        notes.append("type_0_40")

    state = read_s8_from(buf, off + 0x544)
    if -4 <= state <= 32:
        score += 2
        notes.append("state_plausible")

    invuln = read_f32_from(buf, off + 0x720)
    if plausible_float(invuln, 600.0):
        score += 2
        notes.append("timer_plausible")

    pos = (
        read_f32_from(buf, off + 0x44),
        read_f32_from(buf, off + 0x48),
        read_f32_from(buf, off + 0x4c),
    )
    if all(plausible_float(v, 100000.0) for v in pos):
        score += 1
        notes.append("pos_finite")
        if any(abs(v) > 0.001 for v in pos) and all(abs(v) < 20000.0 for v in pos):
            score += 2
            notes.append("pos_worldish")

    return score, notes


def wait_for_hook():
    while not dme.is_hooked():
        dme.hook()
        if dme.is_hooked():
            return
        print("waiting for Dolphin...", file=sys.stderr)
        time.sleep(0.5)


def read_all_mem1():
    buf = bytearray()
    addr = MEM1_START
    end = MEM1_START + MEM1_SIZE
    while addr < end:
        n = min(CHUNK, end - addr)
        buf += dme.read_bytes(addr, n)
        addr += n
    return bytes(buf)


def scan(buf, align):
    candidates = []
    n = len(buf)
    for off in range(0, n - 0x1c8, 4):
        if buf[off + 0x83] != 0:
            continue
        maxhp = read_s16_from(buf, off + 0x1c4)
        hp = read_s16_from(buf, off + 0x1c6)
        if not (0 < hp <= maxhp <= 2000):
            continue
        type_byte = buf[off + 0x88]
        if type_byte > 40:
            continue
        addr = MEM1_START + off
        score, notes = score_candidate(buf, off, align)
        candidates.append({"address": addr, "score": score, "notes": notes})
    return candidates


def collapse_candidates(candidates, window):
    if not candidates:
        return []
    ordered = sorted(candidates, key=lambda c: c["address"])
    clusters = []
    cluster = [ordered[0]]
    for candidate in ordered[1:]:
        if candidate["address"] - cluster[-1]["address"] <= window:
            cluster.append(candidate)
        else:
            clusters.append(cluster)
            cluster = [candidate]
    clusters.append(cluster)
    winners = []
    for cluster in clusters:
        winner = max(cluster, key=lambda c: (c["score"], -(c["address"] % 0x20), -c["address"]))
        if len(cluster) > 1:
            winner = dict(winner)
            winner["collapsed_count"] = len(cluster)
            winner["cluster_start"] = cluster[0]["address"]
            winner["cluster_end"] = cluster[-1]["address"]
        winners.append(winner)
    return winners


def dump_fields(addr):
    row = {"address": hex(addr)}
    for name, off in FIELDS.items():
        a = addr + off
        if name in ("maxhp_0x1c4", "hp_0x1c6", "cat_short_0x3e8"):
            row[name] = struct.unpack(">h", dme.read_bytes(a, 2))[0]
        elif name in ("state_0x544",):
            row[name] = struct.unpack(">b", dme.read_bytes(a, 1))[0]
        elif name.startswith("pos_") or name == "invuln_timer_0x720":
            row[name] = round(struct.unpack(">f", dme.read_bytes(a, 4))[0], 4)
        else:
            row[name] = dme.read_bytes(a, 1)[0]
    return row


def print_candidate(candidate):
    row = dump_fields(candidate["address"])
    row["score"] = candidate["score"]
    row["notes"] = ",".join(candidate["notes"])
    if "collapsed_count" in candidate:
        row["collapsed_count"] = candidate["collapsed_count"]
        row["cluster"] = f"{hex(candidate['cluster_start'])}..{hex(candidate['cluster_end'])}"
    print(row)


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--watch", default=None, help="address (hex, e.g. 0x80abcd00) to poll continuously instead of scanning")
    ap.add_argument("--interval", type=float, default=0.2)
    ap.add_argument("--all", action="store_true", help="print raw candidates instead of collapsing near-duplicate hits")
    ap.add_argument("--align", type=lambda s: int(s, 0), default=0x10, help="preferred base alignment used for scoring")
    ap.add_argument("--cluster-window", type=lambda s: int(s, 0), default=0x400, help="collapse hits this close together")
    args = ap.parse_args()

    wait_for_hook()
    print("Hooked to Dolphin.")

    if args.watch:
        addr = int(args.watch, 16)
        print(f"Polling {hex(addr)} @ {1/args.interval:.1f} Hz -- Ctrl+C to stop")
        last = None
        try:
            while True:
                if not dme.is_hooked():
                    wait_for_hook()
                row = dump_fields(addr)
                if row != last:
                    print(row)
                    last = row
                time.sleep(args.interval)
        except KeyboardInterrupt:
            pass
        return

    print("Reading MEM1 (24 MiB) ...")
    buf = read_all_mem1()
    print("Scanning for borg-object signature ...")
    candidates = scan(buf, args.align)
    shown = candidates if args.all else collapse_candidates(candidates, args.cluster_window)
    shown = sorted(shown, key=lambda c: (-c["score"], c["address"]))
    suffix = "raw" if args.all else "collapsed"
    print(f"Found {len(candidates)} raw candidate(s), showing {len(shown)} {suffix} candidate(s):\n")
    for candidate in shown:
        print_candidate(candidate)
    print("\nRe-run periodically (borgs move in memory across spawns) or use --watch <addr> once")
    print("you've matched a candidate to a specific borg by its HP numbers on screen.")


if __name__ == "__main__":
    main()
