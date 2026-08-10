#!/usr/bin/env python3
"""gen_arena_collision.py — arena segments for the collision-core wasm unit.

Same design as gen_arena_knockback.py (byte order converted at generation time,
everything DOL-sourced): emits arena-collision.json with the f32 constants the
three collision hit-pair passes read (chunk_0003.c:7026-7426):
  FLOAT_80436f68  0.0  deferred-nudge |v|^2 epsilon gate
  FLOAT_80436f7c  0.5  deferred-nudge half-scale (PSQUATScale factor)
  FLOAT_80436f98       deferred-search initial best-distance sentinel

Everything else the passes touch (object lists DAT_803c477c/2f7c/417c/177c/117c,
counts DAT_80436240..50, the 0x803b04cc/0x803b0364 transform globals and the
DAT_803b0720 contact point) is runtime bss the harness writes per case.
harness-collision.mjs loads this on top of the POC arena.json.
"""
import base64
import json
import os
import struct
import sys

sys.path.insert(0, os.path.join(os.path.dirname(__file__), "..", ".."))
import dol  # research/decomp/dol.py — existing DOL section mapper

OUT = os.path.join(os.path.dirname(__file__), "arena-collision.json")


def raw(addr, size):
    off = dol.addr_to_off(addr)
    assert off is not None, hex(addr)
    return dol.data[off:off + size]


segments = []


def seg(addr, data, note):
    segments.append({"addr": addr, "b64": base64.b64encode(data).decode(), "note": note})


# --- scalar f32 constants (sec12 .sdata2) --------------------------------------
for addr, note in [
    (0x80436F68, "0.0 deferred-nudge |v|^2 epsilon gate"),
    (0x80436F7C, "0.5 deferred-nudge half-scale"),
    (0x80436F98, "deferred-search initial best-distance sentinel"),
]:
    val = struct.unpack(">f", raw(addr, 4))[0]
    seg(addr, struct.pack("<f", val), f"const f@{hex(addr)}={val} ({note})")

# Sanity: the epsilon must be 0.0 and the half-scale 0.5 (sourceCollision.ts
# cites both); the sentinel must be a large positive float (every first
# qualifying pair must satisfy dist2 <= sentinel).
vals = {s["addr"]: struct.unpack("<f", base64.b64decode(s["b64"]))[0] for s in segments}
assert vals[0x80436F68] == 0.0, vals
assert vals[0x80436F7C] == 0.5, vals
assert vals[0x80436F98] > 1.0e6, vals

with open(OUT, "w") as f:
    json.dump({"segments": segments}, f)

total = sum(len(base64.b64decode(s["b64"])) for s in segments)
print(f"arena-collision.json: {len(segments)} segments, {total} bytes")
for s in segments:
    print(f"  {hex(s['addr'])} +{len(base64.b64decode(s['b64']))}  {s['note']}")
