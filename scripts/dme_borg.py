"""Deterministic active-player-borg locator via the confirmed pointer chain.

Cracked from the decomp (research/decomp/behavior-notes; agent trace 2026-07-01):
  T    = *(u32*) 0x80433934                    # battle/slot table (0 => no battle)
  slot = *(s8*)  (T + 0xC0)                     # player 0's active-borg slot (fallback 0)
  base = *(u32*) (0x803C4E84 + slot*4)          # player 0 active borg struct pointer

Store-site proof: zz_005809c_ @ 0x8005809c writes each borg pointer into the 6-entry array at
0x803C4E84 and records the slot at borg+0x3e4. Player index->slot via PTR_DAT_80433934[0xC0]
(zz_000bef4_ @ 0x8000bef4). The base is the REAL gameplay struct (pos +0x44, vel +0x58,
state +0x544, invuln +0x720) and is stable across pauses/deaths/borg-switch — re-read each frame.
"""
import struct
import sys
import os

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from dme_lib import read_u32, read_s32, read_f32
import dolphin_memory_engine as d

SLOT_TABLE_PTR = 0x80433934
BORG_ARRAY = 0x803C4E84
MEM1_LO, MEM1_HI = 0x80000000, 0x81800000


def _u32(a):
    return struct.unpack(">I", d.read_bytes(a, 4))[0]


def _s8(a):
    return struct.unpack(">b", d.read_bytes(a, 1))[0]


def in_mem1(v):
    return MEM1_LO <= v < MEM1_HI


def active_borg_base():
    """Return (base, slot, diag) for player 0's active borg, or (None, None, reason)."""
    t = _u32(SLOT_TABLE_PTR)
    if not in_mem1(t):
        return None, None, f"no battle (slot table ptr=0x{t:08x})"
    slot = _s8(t + 0xC0)
    if slot < 0 or slot > 5:
        slot = 0
    base = _u32(BORG_ARRAY + slot * 4)
    if not in_mem1(base):
        return None, slot, f"borg ptr not in MEM1 (0x{base:08x}) at slot {slot}"
    return base, slot, "ok"


def borg_fields(base, pos_off=0x44):
    # pos_off: 0x44 in the classic layout; 0x20 in 4P versus (behavior-notes §ac — the vec3
    # the camera system reads). Same struct, mode-dependent live-position field.
    return dict(
        pos=dict(x=read_f32(base + pos_off), y=read_f32(base + pos_off + 4), z=read_f32(base + pos_off + 8)),
        vel=dict(x=read_f32(base + 0x58), y=read_f32(base + 0x5c), z=read_f32(base + 0x60)),
        heading=struct.unpack(">h", d.read_bytes(base + 0x72, 2))[0],
        state=read_s32(base + 0x544),
        invuln=read_f32(base + 0x720),
        slot_field=_s8(base + 0x3e4),
        team=_s8(base + 0x88),
        alive=struct.unpack(">B", d.read_bytes(base, 1))[0],
    )


def validate(base, slot):
    """True if the borg at base passes the sanity gates from the decomp."""
    try:
        f = borg_fields(base)
    except Exception:
        return False
    return (
        -1 <= f["state"] <= 64
        and all(abs(v) < 20000 for v in f["pos"].values())
        and f["slot_field"] == slot
    )
