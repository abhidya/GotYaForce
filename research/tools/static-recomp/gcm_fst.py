#!/usr/bin/env python3
"""gcm_fst.py -- list the GameCube disc's filesystem.

The reason this is in a static-recompilation spike: DVD-loaded CODE OVERLAYS
(GameCube `.rel` modules) are the classic thing that kills a static recompiler,
because code that is not in boot.dol at build time cannot be translated at build
time.  The only way to answer "does this game overlay code?" is to look at the
disc.  Extension counts and the presence/absence of `.rel` is the answer.
"""
from __future__ import annotations

import argparse
import collections
import json
import struct
from pathlib import Path


def read_fst(path):
    with open(str(path), "rb") as f:
        f.seek(0x0420)
        dol_off = struct.unpack(">I", f.read(4))[0]
        fst_off, fst_size = struct.unpack(">II", f.read(8))
        f.seek(fst_off)
        fst = f.read(fst_size)
    n_entries = struct.unpack(">I", fst[8:12])[0]
    strings = fst[n_entries * 12:]
    out = []
    for i in range(n_entries):
        e = fst[i * 12:(i + 1) * 12]
        kind = e[0]
        name_off = struct.unpack(">I", b"\x00" + e[1:4])[0]
        a, b = struct.unpack(">II", e[4:12])
        end = strings.find(b"\x00", name_off)
        name = strings[name_off:end].decode("latin-1")
        out.append({"i": i, "dir": bool(kind), "name": name,
                    "offset": a, "size": b})
    return dol_off, fst_off, fst_size, out


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--iso", required=True)
    ap.add_argument("--out", required=True)
    a = ap.parse_args()
    dol_off, fst_off, fst_size, entries = read_fst(Path(a.iso))
    files = [e for e in entries if not e["dir"] and e["name"]]
    ext = collections.Counter()
    for e in files:
        ext["." + e["name"].rsplit(".", 1)[-1].lower() if "." in e["name"] else "<none>"] += 1
    rels = [e["name"] for e in files if e["name"].lower().endswith(".rel")]
    biggest = sorted(files, key=lambda e: -e["size"])[:15]
    res = {"dol_offset": "0x%x" % dol_off, "fst_offset": "0x%x" % fst_off,
           "fst_size": fst_size, "entries": len(entries), "files": len(files),
           "extension_histogram": dict(ext.most_common()),
           "rel_modules": rels,
           "largest_files": [{"name": e["name"], "size": e["size"]} for e in biggest],
           "total_file_bytes": sum(e["size"] for e in files)}
    Path(a.out).write_text(json.dumps(res, indent=2))
    print("files: %d  total bytes: %d" % (len(files), res["total_file_bytes"]))
    print("REL code overlays on the disc: %d %s" % (len(rels), rels[:10]))
    print("extensions:", dict(ext.most_common(20)))
    print("largest:")
    for e in biggest[:10]:
        print("   %-28s %12d" % (e["name"], e["size"]))


if __name__ == "__main__":
    main()
