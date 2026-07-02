"""Shared Dolphin Memory Engine helpers for the golden-trace tooling.

Full-speed, read-only access to a running mainline Dolphin over the DME shared-memory
interface. No GDB stub, no CPU halt. Big-endian (GameCube MEM1) throughout.
"""
import struct
import time
import sys

import dolphin_memory_engine as dme

MEM1_LO = 0x80000000
MEM1_HI = 0x81800000


def hook_or_die(retries=20, delay=1.0):
    for _ in range(retries):
        dme.hook()
        if dme.is_hooked():
            # Guard against hooking an idle instance (no game in RAM).
            if dme.read_bytes(0x80000000, 3) == b"GG4":
                return
            dme.un_hook()
        time.sleep(delay)
    sys.exit("could not hook a Dolphin running GG4E (is a battle loaded and running?)")


def read_f32(addr):
    return struct.unpack(">f", dme.read_bytes(addr, 4))[0]


def read_u32(addr):
    return struct.unpack(">I", dme.read_bytes(addr, 4))[0]


def read_s32(addr):
    return struct.unpack(">i", dme.read_bytes(addr, 4))[0]


def read_s16(addr):
    return struct.unpack(">h", dme.read_bytes(addr, 2))[0]


def is_mem1(v):
    return isinstance(v, int) and MEM1_LO <= v < MEM1_HI


def snapshot_mem1(step=4):
    """Return the whole MEM1 as bytes (24 MB). One call ~ instant over shared memory."""
    return dme.read_bytes(MEM1_LO, MEM1_HI - MEM1_LO)
