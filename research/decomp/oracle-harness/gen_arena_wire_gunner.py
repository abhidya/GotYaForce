#!/usr/bin/env python3
"""gen_arena_wire_gunner.py — arena for the wire-gunner-family staged units
(auto-c0034-018, auto-c0035-002; oracle-workstream-plan.md Phase 2 pilot).

gen_arena.py lineage (I-3): everything emitted is DOL-sourced — no hand-entered
values. Byte order is converted at generation time:
  - f32 slots: swap4
  - f64 slots: swap8 (DOUBLE_80439e88 — the PPC int->double magic 2^52+2^31)
  - int tables: swap4

Segments emitted:
  0x80439e60..0x80439ea0  .sdata2 float/double constants the units read
                          (FLOAT_80439e70/78/7c/80/90/94, DOUBLE_80439e88, ...)
  0x804345c8..0x804345e8  DAT_804345c8 int table (FUN_80130330 slot indices)

NOT emitted: the PTR_FUN_80335cb8.. dispatch tables. Their cells are function
POINTERS, meaningless as wasm table indices; the specs declare the dispatch
window as an instrumented scratch region (spy table indices written through the
codec per case, mustWrite-audited) — the seam analogue of the zz_* import shims.
DOL row addresses were cross-checked against wire-gunner.ts's actionTable rows
during spec authoring (row0=0x801307c4, row1=0x80131598, row2=0x80131688,
row3=0x80131834) — see the spec comments.
"""
import base64
import json
import os
import struct
import sys

sys.path.insert(0, os.path.join(os.path.dirname(__file__), ".."))
import dol  # research/decomp/dol.py — existing DOL section mapper

OUT = os.path.join(os.path.dirname(__file__), "arena-wire-gunner.json")


def raw(addr, size):
    off = dol.addr_to_off(addr)
    assert off is not None, hex(addr)
    return dol.data[off:off + size]


def swap4(buf):
    assert len(buf) % 4 == 0
    n = len(buf) // 4
    return struct.pack("<%dI" % n, *struct.unpack(">%dI" % n, buf))


def swap8(buf):
    assert len(buf) % 8 == 0
    n = len(buf) // 8
    return struct.pack("<%dQ" % n, *struct.unpack(">%dQ" % n, buf))


segments = []


def seg(addr, data, note):
    segments.append({"addr": addr, "b64": base64.b64encode(data).decode(), "note": note})


# --- .sdata2 constants 0x80439e60..0x80439ea0 ---------------------------------
# f32 slots up to the f64 at 0x80439e88 (8 bytes), then f32 slots again.
block = swap4(raw(0x80439E60, 0x28)) + swap8(raw(0x80439E88, 8)) + swap4(raw(0x80439E90, 0x10))
seg(0x80439E60, block, "sdata2 consts 80439e60 (f32 x10, f64 @e88, f32 x4)")

# sanity: the values the wire-gunner TS port documents
f70, = struct.unpack("<f", block[0x10:0x14])
f80, = struct.unpack("<f", block[0x20:0x24])
d88, = struct.unpack("<d", block[0x28:0x30])
f90, = struct.unpack("<f", block[0x30:0x34])
assert f70 == 0.0, f70
assert abs(f80 - 0.96) < 1e-6, f80
assert d88 == 4503601774854144.0, d88  # 2^52 + 2^31
assert f90 == -1.0, f90

# --- DAT_804345c8 int table (FUN_80130330 per-borg slot indices) --------------
seg(0x804345C8, swap4(raw(0x804345C8, 0x20)), "DAT_804345c8 int table")

with open(OUT, "w") as f:
    json.dump({"generated_by": "gen_arena_wire_gunner.py (boot.dol)", "segments": segments}, f, indent=1)
print("wrote", OUT, "segments:", [(hex(s["addr"]), len(base64.b64decode(s["b64"]))) for s in segments])
