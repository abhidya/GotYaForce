#!/usr/bin/env python3
"""banners.py -- print the full Dolphin SDK release banners and the MWCC
prologue-order census from the retail DOL.

The Dolphin SDK embeds one NUL-terminated banner per library, of the form
    "<< Dolphin SDK - OS \trelease build: Mon Day Year Time (0xNNNN_NN) >>"
The build id in parentheses is the SDK revision, and the SDK revision is what
the decomp community maps to a specific mwcceppc build.

The prologue census distinguishes MWCC from GCC by frame-setup ORDER:
    MWCC:  stwu r1,-N(r1) ; mflr r0 ; stw r0, N+4(r1)
    GCC:   mflr r0 ; stw r0, 4(r1) ; stwu r1,-N(r1)
"""
from __future__ import annotations

import argparse
import re
import struct
from pathlib import Path

import sys
sys.path.insert(0, str(Path(__file__).resolve().parent))
from fingerprint import Dol  # noqa: E402


def cstr(blob: bytes, i: int, limit: int = 400) -> str:
    end = blob.find(b"\x00", i, i + limit)
    if end < 0:
        end = min(i + limit, len(blob))
    return blob[i:end].decode("latin1")


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--iso", required=True)
    a = ap.parse_args()
    dol = Dol.from_iso(Path(a.iso))
    text, data = dol.text_sections()

    print("== full SDK / runtime banners ==")
    pats = [b"Dolphin SDK", b"Metrowerks", b"MSL ", b"TRK ", b"release build",
            b"MetroTRK", b"__ppc", b"MWCC", b"CodeWarrior"]
    seen = set()
    for off, adr, sz in data:
        blob = dol.blob[off:off + sz]
        for p in pats:
            start = 0
            while True:
                i = blob.find(p, start)
                if i < 0:
                    break
                start = i + 1
                # back up to the start of the C string
                j = i
                while j > 0 and 0x20 <= blob[j - 1] <= 0x7E and (i - j) < 120:
                    j -= 1
                s = cstr(blob, j)
                key = (adr + j, s)
                if key in seen:
                    continue
                seen.add(key)
                print("0x%08x  %s" % (adr + j, s))

    print("\n== prologue order census ==")
    mwcc_order = 0   # stwu ; mflr r0 ; stw r0
    gcc_order = 0    # mflr r0 ; stw r0,4(r1) ; stwu
    stwu_total = 0
    for off, adr, sz in text:
        n = sz // 4
        w = struct.unpack(">%dI" % n, dol.blob[off:off + n * 4])
        for i in range(n - 2):
            a0, a1, a2 = w[i], w[i + 1], w[i + 2]
            # stwu r1, -N(r1)  == primary 37, rS=1, rA=1
            if (a0 >> 26) == 37 and ((a0 >> 21) & 31) == 1 and ((a0 >> 16) & 31) == 1:
                stwu_total += 1
                if a1 == 0x7C0802A6 and (a2 >> 26) == 36 and ((a2 >> 21) & 31) == 0 \
                        and ((a2 >> 16) & 31) == 1:
                    mwcc_order += 1
            if a0 == 0x7C0802A6 and (a1 >> 26) == 36 and ((a1 >> 21) & 31) == 0 \
                    and ((a1 >> 16) & 31) == 1 and (a1 & 0xFFFF) == 4:
                if (a2 >> 26) == 37 and ((a2 >> 21) & 31) == 1 and ((a2 >> 16) & 31) == 1:
                    gcc_order += 1
    print("stwu r1,-N(r1) sites            %d" % stwu_total)
    print("MWCC order (stwu;mflr;stw)      %d" % mwcc_order)
    print("GCC  order (mflr;stw 4;stwu)    %d" % gcc_order)

    print("\n== function alignment census (from the map) ==")


if __name__ == "__main__":
    main()
