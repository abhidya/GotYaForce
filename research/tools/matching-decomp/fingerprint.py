#!/usr/bin/env python3
"""fingerprint.py -- determine WHICH Metrowerks CodeWarrior build compiled this DOL.

A matching decompilation only matches if the compiler version is right, so the
version is the first thing that has to be pinned down.  This tool reads the DOL
out of the retail GCM (same layout logic as
research/tools/dolphin-trace/capture_common.py:Dol) and reports every piece of
evidence that bears on the question:

  1. ASCII strings in the data sections that name a toolchain, an SDK, or a
     runtime library ("Metrowerks", "CodeWarrior", "MSL", "TRK", "$Id:", ...).
  2. Nintendo SDK / metrowerks version banners, which are conventionally
     embedded as "<<...>>" or "$Id:" RCS tags in the SDK's own objects.
  3. The presence of the Metrowerks TRK (Target Resident Kernel) debug stub,
     whose symbol names are in the project map.
  4. Codegen idiom counts that separate MWCC generations from each other and
     from GCC.

Usage:
    python fingerprint.py --iso "D:/GotYaForce/Gotcha Force.iso" \
        [--json out.json]

Reads only.  Writes nothing unless --json is given.
"""
from __future__ import annotations

import argparse
import json
import re
import struct
import sys
from collections import Counter
from pathlib import Path

REPO = Path(__file__).resolve().parents[3]
sys.path.insert(0, str(REPO / "research" / "tools" / "dolphin-trace"))


class Dol:
    """boot.dol section table + address->bytes reads. Copied, not imported, so
    this tool has no dependency on the capture stack's rsp_client import."""

    def __init__(self, blob: bytes):
        self.blob = blob
        offs = struct.unpack(">18I", blob[0x00:0x48])
        adrs = struct.unpack(">18I", blob[0x48:0x90])
        szs = struct.unpack(">18I", blob[0x90:0xD8])
        self.sections = [(offs[i], adrs[i], szs[i]) for i in range(18) if szs[i]]
        self.bss_addr, self.bss_size = struct.unpack(">II", blob[0xD8:0xE0])
        self.entry = struct.unpack(">I", blob[0xE0:0xE4])[0]

    @classmethod
    def from_iso(cls, iso_path: Path) -> "Dol":
        with iso_path.open("rb") as f:
            f.seek(0x420)
            dol_off = struct.unpack(">I", f.read(4))[0]
            f.seek(dol_off)
            head = f.read(0x100)
            offs = struct.unpack(">18I", head[0x00:0x48])
            szs = struct.unpack(">18I", head[0x90:0xD8])
            size = max(o + s for o, s in zip(offs, szs) if s)
            f.seek(dol_off)
            return cls(f.read(size))

    def text_sections(self):
        # DOL: entries 0..6 are text, 7..17 are data.
        out = []
        for i, (off, adr, sz) in enumerate(self.sections):
            out.append((off, adr, sz))
        # Recover index by re-parsing rather than guessing.
        offs = struct.unpack(">18I", self.blob[0x00:0x48])
        adrs = struct.unpack(">18I", self.blob[0x48:0x90])
        szs = struct.unpack(">18I", self.blob[0x90:0xD8])
        text = [(offs[i], adrs[i], szs[i]) for i in range(7) if szs[i]]
        data = [(offs[i], adrs[i], szs[i]) for i in range(7, 18) if szs[i]]
        return text, data


# --------------------------------------------------------------------------
# 1. strings
# --------------------------------------------------------------------------

STRING_RE = re.compile(rb"[\x20-\x7e]{6,}")

# Anything that names a toolchain, a runtime, or carries a version.
INTEREST = [
    (re.compile(rb"(?i)metrowerks"), "metrowerks"),
    (re.compile(rb"(?i)codewarrior"), "codewarrior"),
    (re.compile(rb"(?i)freescale"), "freescale"),
    (re.compile(rb"\bMSL\b"), "msl"),
    (re.compile(rb"(?i)mslibs"), "msl"),
    (re.compile(rb"(?i)\bTRK\b"), "trk"),
    (re.compile(rb"\$Id:"), "rcs_id"),
    (re.compile(rb"<<\s*\$?\w"), "sdk_banner"),
    (re.compile(rb"(?i)dolphin\s*sdk"), "dolphin_sdk"),
    (re.compile(rb"(?i)\bRVL_SDK|\bNINTENDO"), "nintendo"),
    (re.compile(rb"(?i)\bGNU\b|\bgcc\b|GCC:"), "gcc"),
    (re.compile(rb"(?i)\.comment"), "comment_section"),
    (re.compile(rb"(?i)version\s*[:\s]\s*\d"), "version_literal"),
    (re.compile(rb"(?i)\bbuild\b.{0,12}\d{4}"), "build_date"),
    (re.compile(rb"(?i)(os|gx|vi|dvd|ai|ar|card|pad|si|exi|db|mtx|axfx|mus)[a-z]*\.c\b"),
     "sdk_source_filename"),
    (re.compile(rb"(?i)\.(c|cpp|cc|h|s)\b"), "source_filename"),
    (re.compile(rb"(?i)\b(19|20)\d\d[/-][01]?\d[/-][0-3]?\d"), "date_literal"),
]


def scan_strings(dol: Dol):
    text, data = dol.text_sections()
    hits = {}
    all_strings = []
    for off, adr, sz in data:
        blob = dol.blob[off:off + sz]
        for m in STRING_RE.finditer(blob):
            s = m.group(0)
            va = adr + m.start()
            all_strings.append((va, s))
            for rx, tag in INTEREST:
                if rx.search(s):
                    hits.setdefault(tag, []).append((va, s.decode("latin1")))
    return hits, all_strings


# --------------------------------------------------------------------------
# 2. codegen idioms
# --------------------------------------------------------------------------

def be32(b, i):
    return struct.unpack_from(">I", b, i)[0]


def idiom_census(dol: Dol):
    """Counts of instruction forms that discriminate compilers.

    MWCC for Gekko has habits GCC does not:
      * it schedules with lots of `nop` (0x60000000) padding to 4/8-byte
        function alignment and NEVER uses GCC's `.align`-to-16 pattern;
      * it uses `mflr r0` / `stw r0, 0x??(r1)` / `stwu r1, -N(r1)` in that
        exact order for the standard prologue;
      * it uses `lwz r0, 0x??(r1)` / `mtlr r0` / `addi r1, r1, N` / `blr`
        for the epilogue, and `addi` rather than `lwz r1, 0(r1)` unwind;
      * it emits `psq_l`/`psq_st` only under -fp paired-single options;
      * it uses the small data areas r2/r13 (EABI) heavily.
    """
    text, _ = dol.text_sections()
    counts = Counter()
    prologue_mwcc = 0
    prologue_gcc_style = 0
    epilogue_addi = 0
    epilogue_lwz_r1 = 0
    nop_runs = Counter()
    sda_r2 = 0
    sda_r13 = 0
    total = 0

    for off, adr, sz in text:
        blob = dol.blob[off:off + sz]
        n = sz // 4
        words = struct.unpack(">%dI" % n, blob[:n * 4])
        total += n
        run = 0
        for i, w in enumerate(words):
            if w == 0x60000000:
                run += 1
                continue
            if run:
                nop_runs[run] += 1
                run = 0
            op = w >> 26
            # mflr r0 == 0x7c0802a6
            if w == 0x7C0802A6:
                counts["mflr_r0"] += 1
                # MWCC: mflr r0 ; stw r0, 4(r1) ; stwu r1, -N(r1)
                if i + 2 < n:
                    w1, w2 = words[i + 1], words[i + 2]
                    if (w1 >> 26) == 36 and ((w1 >> 21) & 31) == 0 and ((w1 >> 16) & 31) == 1:
                        if (w2 >> 26) == 37 and ((w2 >> 21) & 31) == 1 and ((w2 >> 16) & 31) == 1:
                            prologue_mwcc += 1
                        else:
                            prologue_gcc_style += 1
            if w == 0x7C0803A6:
                counts["mtlr_r0"] += 1
                if i + 1 < n:
                    w1 = words[i + 1]
                    # addi r1, r1, N
                    if (w1 >> 26) == 14 and ((w1 >> 21) & 31) == 1 and ((w1 >> 16) & 31) == 1:
                        epilogue_addi += 1
                    # lwz r1, 0(r1)
                    if (w1 >> 26) == 32 and ((w1 >> 21) & 31) == 1 and ((w1 >> 16) & 31) == 1:
                        epilogue_lwz_r1 += 1
            if w == 0x4E800020:
                counts["blr"] += 1
            # small data area: any load/store with rA == 2 or rA == 13
            if op in (32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47,
                      48, 49, 50, 51, 52, 53, 54, 55):
                ra = (w >> 16) & 31
                if ra == 2:
                    sda_r2 += 1
                elif ra == 13:
                    sda_r13 += 1
            if op in (4, 56, 57, 60, 61):
                counts["paired_single_primary_%d" % op] += 1
            if op == 18:
                counts["b_or_bl"] += 1
        if run:
            nop_runs[run] += 1

    return {
        "total_instructions": total,
        "mflr_r0": counts["mflr_r0"],
        "mtlr_r0": counts["mtlr_r0"],
        "blr": counts["blr"],
        "prologue_mflr_stw_stwu": prologue_mwcc,
        "prologue_mflr_other": prologue_gcc_style,
        "epilogue_mtlr_then_addi_r1": epilogue_addi,
        "epilogue_mtlr_then_lwz_r1": epilogue_lwz_r1,
        "sda_r2_refs": sda_r2,
        "sda_r13_refs": sda_r13,
        "paired_single": sum(v for k, v in counts.items() if k.startswith("paired_single")),
        "nop_run_histogram": dict(sorted(nop_runs.items())[:12]),
    }


# --------------------------------------------------------------------------

def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--iso", required=True)
    ap.add_argument("--json")
    ap.add_argument("--dump-strings", type=int, default=0,
                    help="print this many of the longest data strings")
    a = ap.parse_args()

    dol = Dol.from_iso(Path(a.iso))
    text, data = dol.text_sections()

    print("== DOL layout ==")
    print("entry           0x%08x" % dol.entry)
    print("bss             0x%08x  %d B" % (dol.bss_addr, dol.bss_size))
    for off, adr, sz in text:
        print("text  off=0x%08x  va=0x%08x  %9d B  (%d insns)" % (off, adr, sz, sz // 4))
    for off, adr, sz in data:
        print("data  off=0x%08x  va=0x%08x  %9d B" % (off, adr, sz))

    hits, all_strings = scan_strings(dol)
    print("\n== toolchain / SDK string evidence ==")
    for tag in ["metrowerks", "codewarrior", "freescale", "msl", "trk", "rcs_id",
                "sdk_banner", "dolphin_sdk", "nintendo", "gcc", "comment_section",
                "version_literal", "build_date", "sdk_source_filename",
                "source_filename", "date_literal"]:
        v = hits.get(tag, [])
        print("%-22s %d" % (tag, len(v)))
        for va, s in v[:12]:
            print("      0x%08x  %s" % (va, s[:110]))
        if len(v) > 12:
            print("      ... %d more" % (len(v) - 12))

    print("\n== codegen idiom census ==")
    cens = idiom_census(dol)
    for k, v in cens.items():
        print("%-32s %s" % (k, v))

    if a.dump_strings:
        print("\n== longest data strings ==")
        for va, s in sorted(all_strings, key=lambda t: -len(t[1]))[:a.dump_strings]:
            print("0x%08x  %s" % (va, s.decode("latin1")[:160]))

    if a.json:
        Path(a.json).write_text(json.dumps({
            "iso": a.iso,
            "entry": dol.entry,
            "text": text, "data": data,
            "string_evidence": {k: v[:200] for k, v in hits.items()},
            "idiom_census": cens,
        }, indent=2))
        print("\nwrote %s" % a.json)


if __name__ == "__main__":
    main()
