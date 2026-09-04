#!/usr/bin/env python3
"""dolsym.py -- the retail side of the matching-decompilation harness.

Loads boot.dol out of the retail GCM and the project's CodeWarrior-style link
map, and hands back the EXACT retail bytes of any named function.  This is the
ground truth a matching decompilation is diffed against; nothing here infers
anything.

The map is `research/symbols/GG4E-CSM-20220412.map`, whose `.text section
layout` block has the CodeWarrior map format:

    <vaddr> <size> <loadaddr> <align> <name>

so a function's extent is stated, not guessed.
"""
from __future__ import annotations

import re
import struct
from pathlib import Path

REPO_DEFAULT = Path("D:/GotYaForce")
ISO_DEFAULT = REPO_DEFAULT / "Gotcha Force.iso"


class Dol(object):
    def __init__(self, blob):
        self.blob = blob
        offs = struct.unpack(">18I", blob[0x00:0x48])
        adrs = struct.unpack(">18I", blob[0x48:0x90])
        szs = struct.unpack(">18I", blob[0x90:0xD8])
        self.text = [(offs[i], adrs[i], szs[i]) for i in range(7) if szs[i]]
        self.data = [(offs[i], adrs[i], szs[i]) for i in range(7, 18) if szs[i]]
        self.sections = self.text + self.data
        self.bss_addr, self.bss_size = struct.unpack(">II", blob[0xD8:0xE0])
        self.entry = struct.unpack(">I", blob[0xE0:0xE4])[0]

    @classmethod
    def from_iso(cls, iso_path):
        with open(str(iso_path), "rb") as f:
            f.seek(0x420)
            dol_off = struct.unpack(">I", f.read(4))[0]
            f.seek(dol_off)
            head = f.read(0x100)
            offs = struct.unpack(">18I", head[0x00:0x48])
            szs = struct.unpack(">18I", head[0x90:0xD8])
            size = max(o + s for o, s in zip(offs, szs) if s)
            f.seek(dol_off)
            return cls(f.read(size))

    def read(self, addr, size):
        """Exact bytes at a virtual address, or None if unmapped."""
        for off, adr, sz in self.sections:
            if adr <= addr and addr + size <= adr + sz:
                o = off + (addr - adr)
                return self.blob[o:o + size]
        return None

    def is_text(self, addr):
        for off, adr, sz in self.text:
            if adr <= addr < adr + sz:
                return True
        return False


MAP_LINE = re.compile(
    r"^\s*([0-9a-fA-F]{8})\s+([0-9a-fA-F]{8})\s+([0-9a-fA-F]{8})\s+(\d+)\s+(\S+)")


class SymbolMap(object):
    """CodeWarrior-format link map: name -> (vaddr, size, align)."""

    def __init__(self, path):
        self.by_name = {}
        self.by_addr = {}
        self.order = []
        section = None
        for line in Path(path).read_text(errors="replace").splitlines():
            m = re.match(r"^(\S+) section layout", line.strip())
            if m:
                section = m.group(1)
                continue
            m = MAP_LINE.match(line)
            if not m or section is None:
                continue
            va = int(m.group(1), 16)
            size = int(m.group(2), 16)
            align = int(m.group(4))
            name = m.group(5)
            rec = {"name": name, "addr": va, "size": size,
                   "align": align, "section": section}
            self.by_name[name] = rec
            self.by_addr[va] = rec
            self.order.append(rec)
        self.order.sort(key=lambda r: r["addr"])

    def text_functions(self):
        return [r for r in self.order if r["section"] == ".text" and r["size"] > 0]

    def lookup(self, addr):
        best = None
        for r in self.order:
            if r["addr"] <= addr < r["addr"] + r["size"]:
                best = r
        return best


def load(iso=None, mapfile=None, repo=None):
    repo = Path(repo) if repo else REPO_DEFAULT
    iso = Path(iso) if iso else (repo / "Gotcha Force.iso")
    mapfile = Path(mapfile) if mapfile else (
        repo / "research" / "symbols" / "GG4E-CSM-20220412.map")
    return Dol.from_iso(iso), SymbolMap(mapfile)


def function_bytes(dol, sym, name_or_addr):
    """(rec, bytes) for a function named in the map."""
    if isinstance(name_or_addr, str) and not name_or_addr.startswith("0x"):
        rec = sym.by_name.get(name_or_addr)
    else:
        addr = int(name_or_addr, 16) if isinstance(name_or_addr, str) else name_or_addr
        rec = sym.by_addr.get(addr)
    if rec is None:
        return None, None
    return rec, dol.read(rec["addr"], rec["size"])


if __name__ == "__main__":
    import sys
    d, s = load()
    fns = s.text_functions()
    print("dol entry 0x%08x, text sections %d" % (d.entry, len(d.text)))
    print("map: %d symbols, %d .text functions" % (len(s.order), len(fns)))
    if len(sys.argv) > 1:
        rec, b = function_bytes(d, s, sys.argv[1])
        print(rec)
        print(b.hex() if b else None)
