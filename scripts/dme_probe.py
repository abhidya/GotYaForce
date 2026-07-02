#!/usr/bin/env python3
"""Prove the Dolphin Memory Engine live-read path against a running mainline Dolphin.

Read-only, non-invasive: hooks the emulator's memory over shared memory (the same interface
the Dolphin Memory Engine GUI uses) and reads known-good MEM1 values. Works at full emulation
speed and even while the CPU is paused, with NO GDB stub and NO halting.

Validation anchor: float 60.0 (bytes 42 70 00 00, big-endian) at 0x80437448 — the wake-up
invincibility constant confirmed in research/decomp/ram-trace-analysis.md.
"""
import struct
import sys

try:
    import dolphin_memory_engine as dme
except ImportError:
    sys.exit("dolphin_memory_engine not importable in this Python")


def read_f32_be(addr):
    return struct.unpack(">f", dme.read_bytes(addr, 4))[0]


def read_u32_be(addr):
    return struct.unpack(">I", dme.read_bytes(addr, 4))[0]


def main():
    dme.hook()
    if not dme.is_hooked():
        sys.exit("could not hook a running Dolphin process (is the emulator open?)")
    print("hooked Dolphin process OK")

    anchor = 0x80437448
    val = read_f32_be(anchor)
    raw = dme.read_bytes(anchor, 4).hex()
    print(f"0x{anchor:08x} = {val}  (raw {raw})")

    ok = abs(val - 60.0) < 1e-3
    # Also sanity-check MEM1 base magic: 0x80000000 holds the GameCube game id "GG4E".
    gid = dme.read_bytes(0x80000000, 4)
    print(f"0x80000000 game id = {gid!r}")
    ok = ok and gid[:3] == b"GG4"

    print("LIVE-READ CHECK:", "PASS" if ok else "FAIL")
    sys.exit(0 if ok else 1)


if __name__ == "__main__":
    main()
