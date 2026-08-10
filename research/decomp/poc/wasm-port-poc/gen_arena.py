#!/usr/bin/env python3
"""gen_arena.py — POC stage-2 arena generation (HANDOFF-2026-08-09 §4).

Reads boot.dol and emits arena.json: segments of little-endian-converted data to be
written into wasm linear memory at the ORIGINAL GameCube addresses. Byte order is
converted here, at generation time, per the design's endianness rule:
  - swap4 regions: u32 pointers and f32 floats (both 4-byte -> one generic swap)
  - swap2 regions: s16 tables (type-category remap rows)
  - raw regions:   byte tables (no swap)
  - typed pokes:   the f32/f64 scalar constants (mixed widths, done per-symbol)

Everything emitted is DOL-sourced — no hand-entered values.
"""
import base64
import json
import os
import struct
import sys

sys.path.insert(0, os.path.join(os.path.dirname(__file__), "..", ".."))
import dol  # research/decomp/dol.py — existing DOL section mapper

OUT = os.path.join(os.path.dirname(__file__), "arena.json")


def raw(addr, size):
    off = dol.addr_to_off(addr)
    assert off is not None, hex(addr)
    return dol.data[off:off + size]


def swap4(buf):
    assert len(buf) % 4 == 0
    n = len(buf) // 4
    return struct.pack("<%dI" % n, *struct.unpack(">%dI" % n, buf))


def swap2(buf):
    assert len(buf) % 2 == 0
    n = len(buf) // 2
    return struct.pack("<%dH" % n, *struct.unpack(">%dH" % n, buf))


segments = []


def seg(addr, data, note):
    segments.append({"addr": addr, "b64": base64.b64encode(data).decode(), "note": note})


# --- damage-table pointer slots + their targets --------------------------------
# 16 u32 pointer slots at 0x804335e0..0x8043361c (8 groups x hero/CPU pair).
ptr_slots = struct.unpack(">16I", raw(0x804335E0, 64))
seg(0x804335E0, swap4(raw(0x804335E0, 64)), "table pointer slots 804335e0")

# The pointed-to region: flat float tables, curve-pointer arrays and float curves,
# the 20x20 type matrix @802c5d60 and combo scale @802c7ca0 — all 4-byte values.
lo, hi = min(ptr_slots), 0x802C7CA0 + 16 * 4
# follow one level of indirection to catch curve arrays that sit below lo
inner = []
for p in ptr_slots:
    words = struct.unpack(">64I", raw(p, 256))
    inner += [w for w in words if 0x802B0000 <= w < 0x803AF000]
lo = min([lo] + inner)
seg(lo, swap4(raw(lo, hi - lo)), f"damage tables+matrix region {hex(lo)}..{hex(hi)}")

# --- type-category remap: pointer array @802f2e28 + s16 rows -------------------
remap_ptrs = struct.unpack(">16I", raw(0x802F2E28, 64))
seg(0x802F2E28, swap4(raw(0x802F2E28, 64)), "remap pointer array 802f2e28")
rlo = min(remap_ptrs)
seg(rlo, swap2(raw(rlo, 0x802F2E28 - rlo)), f"remap s16 rows {hex(rlo)}..802f2e28")

# --- runtime-struct pointer slots (values -> bss structs the harness fills) ----
seg(0x80433930, swap4(raw(0x80433930, 0x28)), "runtime struct ptrs 80433930-80433954")

# --- scalar constants (mixed f32/f64) ------------------------------------------
for addr, fmt in [(0x80436F68, "f"), (0x80436F78, "f"), (0x80436F7C, "f"),
                  (0x80436F9C, "f"), (0x80437024, "f"), (0x80437028, "f"),
                  (0x80436F88, "d"), (0x80436FB0, "d")]:
    width = 8 if fmt == "d" else 4
    val = struct.unpack(">" + fmt, raw(addr, width))[0]
    seg(addr, struct.pack("<" + fmt, val), f"const {fmt}@{hex(addr)}={val}")

# --- Unit B: DAT_802cffc8 char table (byte data, no swap) ----------------------
seg(0x802CFFC8, raw(0x802CFFC8, 0x20), "unit-b char table 802cffc8")

with open(OUT, "w") as f:
    json.dump({"segments": segments}, f)

total = sum(len(base64.b64decode(s["b64"])) for s in segments)
print(f"arena.json: {len(segments)} segments, {total} bytes")
for s in segments:
    print(f"  {hex(s['addr'])} +{len(base64.b64decode(s['b64']))}  {s['note']}")
