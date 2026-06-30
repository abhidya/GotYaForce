#!/usr/bin/env python3
import struct, sys, re

DOL = r"D:\GotYaForce\user-data\GG4E\disc\sys\boot.dol"
MAP = r"D:\GotYaForce\research\symbols\GG4E-CSM-20220412.map"

with open(DOL, "rb") as f:
    data = f.read()

# DOL header: 7 text + 11 data sections
# offsets[18] (0x00), addrs[18] (0x48), sizes[18] (0x90), bss_addr(0xD8), bss_size(0xDC), entry(0xE0)
offsets = struct.unpack(">18I", data[0x00:0x48])
addrs   = struct.unpack(">18I", data[0x48:0x90])
sizes   = struct.unpack(">18I", data[0x90:0xD8])
bss_addr, bss_size, entry = struct.unpack(">3I", data[0xD8:0xE4])

sections = []
for i in range(18):
    if sizes[i] == 0:
        continue
    kind = "text" if i < 7 else "data"
    sections.append((i, kind, offsets[i], addrs[i], sizes[i]))

def addr_to_off(a):
    for i, kind, off, ad, sz in sections:
        if ad <= a < ad + sz:
            return off + (a - ad)
    return None

def read_u32(a):
    o = addr_to_off(a)
    if o is None: return None
    return struct.unpack(">I", data[o:o+4])[0]

def read_f32(a):
    o = addr_to_off(a)
    if o is None: return None
    return struct.unpack(">f", data[o:o+4])[0]

if __name__ == "__main__":
    print("=== DOL SECTIONS ===")
    print(f"entry=0x{entry:08x} bss_addr=0x{bss_addr:08x} bss_size=0x{bss_size:x}")
    for i, kind, off, ad, sz in sections:
        print(f"  sec{i:2d} {kind:4s} file=0x{off:06x} addr=0x{ad:08x} size=0x{sz:06x} end=0x{ad+sz:08x}")

    print("\n=== SEED ANCHOR VALIDATION ===")
    f = read_f32(0x80437448)
    print(f"  0x80437448 float = {f}  (expect 60.0)  -> {'OK' if f==60.0 else 'MISMATCH'}")
    for a in (0x8005d4b0, 0x8005c7d8, 0x80055c00):
        w = read_u32(a)
        print(f"  0x{a:08x} word = 0x{w:08x}  (off 0x{addr_to_off(a):06x})")
