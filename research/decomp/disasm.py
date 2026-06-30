#!/usr/bin/env python3
import struct, sys, re
from capstone import *
import os; sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from dol import data, sections, addr_to_off, read_u32, read_f32

# Parse symbol map: lines like "80003100 00000040 80003100 0 name"
SYMS = {}   # addr -> name
SYM_SIZE = {}
with open(r"D:\GotYaForce\research\symbols\GG4E-CSM-20220412.map", encoding="utf-8", errors="replace") as f:
    for line in f:
        m = re.match(r"^([0-9a-fA-F]{8})\s+([0-9a-fA-F]{8})\s+([0-9a-fA-F]{8})\s+\d+\s+(.*)$", line.rstrip("\n"))
        if m:
            addr = int(m.group(1), 16)
            size = int(m.group(2), 16)
            name = m.group(4).strip()
            SYMS[addr] = name
            SYM_SIZE[addr] = size

def sym_for(a):
    return SYMS.get(a)

def nearest_sym(a):
    best=None
    for sa in SYMS:
        if sa<=a and (best is None or sa>best):
            best=sa
    if best is None: return None
    return (best, SYMS[best], a-best)

md = Cs(CS_ARCH_PPC, CS_MODE_32 | CS_MODE_BIG_ENDIAN)
md.detail = True

def disasm_range(start, length, annotate=True):
    o = addr_to_off(start)
    if o is None:
        return f"; addr 0x{start:08x} not mapped\n"
    code = data[o:o+length]
    out = []
    for ins in md.disasm(code, start):
        line = f"  {ins.address:08x}:  {ins.bytes.hex():<8}  {ins.mnemonic:<8} {ins.op_str}"
        if annotate:
            # annotate branch targets with symbols
            for tok in re.findall(r"0x[0-9a-fA-F]+", ins.op_str):
                t = int(tok,16)
                s = SYMS.get(t)
                if s:
                    line += f"   <{s}>"
        out.append(line)
    return "\n".join(out)

def disasm_func(addr):
    name = SYMS.get(addr, f"sub_{addr:08x}")
    size = SYM_SIZE.get(addr, 0x100)
    hdr = f"; ===== {name} @ 0x{addr:08x} (size 0x{size:x}) ====="
    return hdr + "\n" + disasm_range(addr, size)

if __name__ == "__main__":
    cmd = sys.argv[1] if len(sys.argv)>1 else "help"
    if cmd == "func":
        print(disasm_func(int(sys.argv[2],16)))
    elif cmd == "range":
        print(disasm_range(int(sys.argv[2],16), int(sys.argv[3],16)))
    elif cmd == "near":
        print(nearest_sym(int(sys.argv[2],16)))
    elif cmd == "grepsym":
        pat = sys.argv[2]
        for a in sorted(SYMS):
            if re.search(pat, SYMS[a], re.I):
                print(f"{a:08x} {SYM_SIZE[a]:6x} {SYMS[a]}")
    elif cmd == "count":
        print(len(SYMS), "symbols")
