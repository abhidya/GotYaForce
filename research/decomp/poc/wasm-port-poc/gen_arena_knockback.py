#!/usr/bin/env python3
"""gen_arena_knockback.py — arena segments for the knockback-core wasm unit.

Same design as gen_arena.py (byte order converted at generation time, everything
DOL-sourced): emits arena-knockback.json with the constants and tables the
knockback unit reads (zz_00300bc_ direction, FUN_800452a0 atan2->BAM16,
zz_005ec20_ ground horizontal-speed select). harness-knockback.mjs loads this on
top of the POC arena.json.
"""
import base64
import json
import os
import struct
import sys

sys.path.insert(0, os.path.join(os.path.dirname(__file__), "..", ".."))
import dol  # research/decomp/dol.py — existing DOL section mapper

OUT = os.path.join(os.path.dirname(__file__), "arena-knockback.json")


def raw(addr, size):
    off = dol.addr_to_off(addr)
    assert off is not None, hex(addr)
    return dol.data[off:off + size]


def swap4(buf):
    assert len(buf) % 4 == 0
    n = len(buf) // 4
    return struct.pack("<%dI" % n, *struct.unpack(">%dI" % n, buf))


segments = []


def seg(addr, data, note):
    segments.append({"addr": addr, "b64": base64.b64encode(data).decode(), "note": note})


# --- scalar f32 constants (sec12 .sdata2) --------------------------------------
for addr, note in [
    (0x80436F68, "0.0 zero / mode-fallback gate"),
    (0x80436F74, "-1.0 degenerate fallback Z"),
    (0x80436FC0, "0.01 degenerate |v|^2 threshold"),
    (0x8043707C, "65536/(2*pi) radians->BAM16"),
    (0x80437440, "zz_005ec20_ scale-ratio bias"),
    (0x80437444, "zz_005ec20_ vertical seed"),
    (0x80437490, "zz_005ec20_ deceleration divisor"),
]:
    val = struct.unpack(">f", raw(addr, 4))[0]
    seg(addr, struct.pack("<f", val), f"const f@{hex(addr)}={val} ({note})")

# --- knockback ground horizontal-speed table: DAT_802dd8a0, 16 f32 (s*7.0) -----
seg(0x802DD8A0, swap4(raw(0x802DD8A0, 16 * 4)), "knockback ground h-speed table 802dd8a0")
values = struct.unpack(">16f", raw(0x802DD8A0, 64))
assert values[6] == 42.0, values  # cross-check vs knockbackStrength.json (s*7)

# --- launch velocity table: DAT_802d3664, 16 f32 ((s+1)*8.0) -------------------
# Not consumed by the extracted unit (FUN_8005ed38 excluded), dumped for audit.
seg(0x802D3664, swap4(raw(0x802D3664, 16 * 4)), "knockback launch velocity table 802d3664")
launch = struct.unpack(">16f", raw(0x802D3664, 64))
assert launch[6] == 56.0, launch

with open(OUT, "w") as f:
    json.dump({"segments": segments}, f)

total = sum(len(base64.b64decode(s["b64"])) for s in segments)
print(f"arena-knockback.json: {len(segments)} segments, {total} bytes")
for s in segments:
    print(f"  {hex(s['addr'])} +{len(base64.b64decode(s['b64']))}  {s['note']}")
