#!/usr/bin/env python3
"""match.py -- the entry point an LLM matching loop calls.

One function in, one verdict out:

    python match.py --function zz_00660b8_ --src cand.c --json v.json

    { "verdict": "MISMATCH", "match_pct": 75.0,
      "first_diff": { "addr": "0x800660bc", "retail": "or r0, r0, r4",
                      "cand": "or r0, r4, r0" }, ... }

exit 0 = MATCH, 1 = MISMATCH, 2 = did not build, 3 = no compiler.

`--detect` reports the toolchain state and exits.  `--context` prints the
prompt block for a target function (disassembly + neighbours + map facts)
without needing a compiler, which is the half of the loop that works today.
"""
from __future__ import annotations

import argparse
import json
import os
import shutil
import subprocess
import sys
import tempfile
from pathlib import Path

HERE = Path(__file__).resolve().parent
sys.path.insert(0, str(HERE))

from dolsym import load, function_bytes  # noqa: E402
from ppcdis import render, disasm  # noqa: E402
from objdiff import Elf32BE, compare, render_diff  # noqa: E402

# Where a licensed CodeWarrior for GameCube would be unpacked.  Nothing is
# downloaded by this tool; these are searched, and their absence is reported.
MWCC_SEARCH = [
    os.environ.get("MWCCEPPC"),
    "D:/GotYaForce/.tools/mwcc/GC/2.6/mwcceppc.exe",
    "D:/GotYaForce/.tools/mwcc/GC/2.5/mwcceppc.exe",
    "D:/GotYaForce/.tools/mwcc/GC/2.0/mwcceppc.exe",
    "D:/GotYaForce/.tools/mwcc/GC/1.3.2/mwcceppc.exe",
    "C:/Program Files (x86)/Metrowerks/CodeWarrior/PowerPC_EABI_Tools/Command_Line_Tools/mwcceppc.exe",
    "C:/Program Files/Metrowerks/CodeWarrior/PowerPC_EABI_Tools/Command_Line_Tools/mwcceppc.exe",
]

# The flag set 2003-era GameCube decomp projects converge on. Confirmed per
# game by calibrating against known SDK functions -- see the spike doc §2.
DEFAULT_CFLAGS = [
    "-proc", "gekko",       # Gekko, not generic 750: enables paired-single
    "-fp", "hardware",
    "-O4,p",                # -O4 with the "prefer speed" sub-flag
    "-enum", "int",
    "-nodefaults",
    "-msgstyle", "gcc",
    "-inline", "auto",
    "-sdata", "8", "-sdata2", "8",
    "-str", "reuse",
    "-func_align", "4",
    "-c",
]


def find_mwcc():
    for p in MWCC_SEARCH:
        if p and Path(p).exists():
            return Path(p)
    w = shutil.which("mwcceppc") or shutil.which("mwcceppc.exe")
    return Path(w) if w else None


def detect():
    out = {"mwcceppc": None, "candidates_searched": [p for p in MWCC_SEARCH if p],
           "objdiff_cli": shutil.which("objdiff-cli"),
           "dtk": shutil.which("dtk"),
           "devkitppc": None, "wine": shutil.which("wine")}
    m = find_mwcc()
    if m:
        out["mwcceppc"] = str(m)
        try:
            r = subprocess.run([str(m), "-version"], capture_output=True, timeout=20)
            out["mwcceppc_version"] = (r.stdout + r.stderr).decode(
                "latin1", "replace").strip()[:400]
        except Exception as ex:
            out["mwcceppc_version"] = "could not run: %s" % ex
    dk = Path("C:/devkitPro/devkitPPC/bin/powerpc-eabi-gcc.exe")
    if dk.exists():
        out["devkitppc"] = str(dk)
    return out


def compile_candidate(src, mwcc, cflags, includes, workdir):
    obj = Path(workdir) / "cand.o"
    cmd = [str(mwcc)] + list(cflags)
    for i in includes:
        cmd += ["-i", str(i)]
    cmd += ["-o", str(obj), str(src)]
    r = subprocess.run(cmd, capture_output=True, cwd=workdir)
    log = (r.stdout + r.stderr).decode("latin1", "replace")
    return (obj if (r.returncode == 0 and obj.exists()) else None), log, cmd


def context_block(dol, smap, rec, retail, neighbours=2):
    """Everything a model needs about the target, and nothing inferred."""
    lines = []
    lines.append("FUNCTION %s @ 0x%08x, %d bytes, %d instructions"
                 % (rec["name"], rec["addr"], rec["size"], rec["size"] // 4))
    lines.append("")
    lines.append("RETAIL DISASSEMBLY (authoritative; Gekko-correct):")
    lines.append(render(retail, rec["addr"], "  "))
    lines.append("")
    calls = []
    for a, w, t in disasm(retail, rec["addr"]):
        if (w >> 26) == 18 and (w & 1):
            li = w & 0x03FFFFFC
            if li & 0x02000000:
                li -= 0x04000000
            tgt = a + li
            r2 = smap.lookup(tgt)
            calls.append((a, tgt, r2["name"] if r2 else "?"))
    if calls:
        lines.append("CALL TARGETS (each becomes an R_PPC_REL24 relocation):")
        for a, t, n in calls:
            lines.append("  0x%08x  bl -> 0x%08x  %s" % (a, t, n))
        lines.append("")
    sda = []
    for a, w, t in disasm(retail, rec["addr"]):
        op = w >> 26
        if 32 <= op <= 55:
            ra = (w >> 16) & 31
            if ra in (2, 13):
                d = w & 0xFFFF
                if d & 0x8000:
                    d -= 0x10000
                base = 0x8043EA20 if ra == 2 else 0x8043B5A0
                sda.append((a, ra, base + d))
    if sda:
        lines.append("SMALL-DATA-AREA REFERENCES (r2=0x8043EA20, r13=0x8043B5A0,")
        lines.append("from the ROM's own __init_registers @ 0x800032b0):")
        for a, ra, tgt in sda:
            r2 = smap.lookup(tgt)
            lines.append("  0x%08x  r%-2d -> 0x%08x %s"
                         % (a, ra, tgt, r2["name"] if r2 else ""))
        lines.append("")
    prev = [r for r in smap.order if r["addr"] < rec["addr"]][-neighbours:]
    nxt = [r for r in smap.order if r["addr"] > rec["addr"]][:neighbours]
    lines.append("NEIGHBOURS IN LINK ORDER (same translation unit, probably):")
    for r in prev + [rec] + nxt:
        lines.append("  %s0x%08x %-28s %d B"
                     % ("* " if r is rec else "  ", r["addr"], r["name"], r["size"]))
    return "\n".join(lines)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--function")
    ap.add_argument("--src")
    ap.add_argument("--repo", default="D:/GotYaForce")
    ap.add_argument("--detect", action="store_true")
    ap.add_argument("--context", action="store_true")
    ap.add_argument("--obj-symbol")
    ap.add_argument("--include", action="append", default=[])
    ap.add_argument("--cflags")
    ap.add_argument("--json")
    a = ap.parse_args()

    if a.detect:
        d = detect()
        print(json.dumps(d, indent=1))
        if a.json:
            Path(a.json).write_text(json.dumps(d, indent=1))
        return 0 if d["mwcceppc"] else 3

    if not a.function:
        ap.error("--function is required")
    dol, smap = load(repo=a.repo)
    rec, retail = function_bytes(dol, smap, a.function)
    if rec is None:
        print("error: %s not in the link map" % a.function, file=sys.stderr)
        return 2

    if a.context or not a.src:
        print(context_block(dol, smap, rec, retail))
        if not a.src:
            return 0

    mwcc = find_mwcc()
    if mwcc is None:
        msg = {
            "verdict": "NO_COMPILER",
            "function": rec["name"],
            "detail": ("mwcceppc.exe was not found. The matching oracle cannot "
                       "run without it. Searched: %s"
                       % ", ".join(p for p in MWCC_SEARCH if p)),
        }
        print(json.dumps(msg, indent=1), file=sys.stderr)
        if a.json:
            Path(a.json).write_text(json.dumps(msg, indent=1))
        return 3

    cflags = a.cflags.split() if a.cflags else DEFAULT_CFLAGS
    wd = tempfile.mkdtemp(prefix="mdec_")
    obj, log, cmd = compile_candidate(Path(a.src), mwcc, cflags, a.include, wd)
    if obj is None:
        v = {"verdict": "BUILD_FAILED", "function": rec["name"],
             "command": cmd, "compiler_log": log[-4000:]}
        print(json.dumps(v, indent=1))
        if a.json:
            Path(a.json).write_text(json.dumps(v, indent=1))
        return 2

    e = Elf32BE(obj.read_bytes())
    sec = e.section(".text")
    cand = e.data(sec)
    relocs = e.relocs_for(".text")
    sym = a.obj_symbol or rec["name"]
    for sy in e.symbols():
        if sy["name"] == sym and sy["size"]:
            cand = cand[sy["value"]:sy["value"] + sy["size"]]
            relocs = [(o - sy["value"], t, n, ad) for o, t, n, ad in relocs
                      if sy["value"] <= o < sy["value"] + sy["size"]]
            break

    v = compare(retail, cand, relocs, rec["addr"])
    v["function"] = rec["name"]
    v["address"] = "0x%08x" % rec["addr"]
    v["compiler"] = str(mwcc)
    v["cflags"] = cflags
    v["compiler_log"] = log[-2000:]
    v["diff_text"] = render_diff(v, retail, cand, rec["addr"])
    print(v["diff_text"])
    print("\nVERDICT %s  %.2f%%" % (v["verdict"], v["match_pct"]))
    if a.json:
        Path(a.json).write_text(json.dumps(v, indent=1))
    return 0 if v["verdict"] == "MATCH" else 1


if __name__ == "__main__":
    sys.exit(main())
