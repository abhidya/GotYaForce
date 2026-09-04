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

TWO COMPILER BACKENDS are supported and they are not interchangeable:

  * `mwcceppc.exe` -- the genuine Metrowerks binary.  Not present on this
    machine and not obtained by this project (proprietary; see the spike
    doc s1.2).  Selected automatically if it ever appears.
  * `mwcc-rs`      -- zcanann/mwcc-rs, an open-source from-scratch Rust
    reimplementation (MIT OR Apache-2.0).  Built from source under
    `.tools/mwcc-rs`; see `TOOLCHAIN.md`.  Selected with `--backend mwcc-rs`
    or automatically when mwcceppc is absent.  Takes `--build <label>`
    (1.3 / 1.3.2 / 2.0 / 2.0p1 / 2.5 / 2.6 / 2.7) instead of one binary per
    version.  It FAILS HONESTLY on constructs it does not implement -- a
    BUILD_FAILED verdict from it is a *compiler capability* statement, not a
    statement about the candidate C.
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
import datareloc  # noqa: E402

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

# Where the mwcc-rs build lands.  `.tools/` is gitignored: externally built
# tooling is NOT vendored into this repository.  See TOOLCHAIN.md.
REPO_DEFAULT = "D:/GotYaForce"
MWCC_RS_SEARCH = [
    os.environ.get("MWCC_RS"),
    str(Path(__file__).resolve().parents[3] / ".tools" / "mwcc-rs"
        / "target" / "release" / "mwcc.exe"),
    "D:/GotYaForce/.tools/mwcc-rs/target/release/mwcc.exe",
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

# mwcc-rs takes the same switch vocabulary minus the mwcceppc-only
# diagnostics flags, and adds `--build`.  `-c` is a value-taking flag here
# (`-c <file>`), so it is supplied by the driver, not the flag list.
DEFAULT_CFLAGS_RS = [
    "-proc", "gekko",
    "-fp", "hardware",
    "-O4,p",
    "-enum", "int",
    "-nodefaults",
    "-inline", "auto",
    "-sdata", "8", "-sdata2", "8",
    "-str", "reuse",
    "-func_align", "4",
]

DEFAULT_BUILD = "2.7"


def find_mwcc():
    for p in MWCC_SEARCH:
        if p and Path(p).exists():
            return Path(p)
    w = shutil.which("mwcceppc") or shutil.which("mwcceppc.exe")
    return Path(w) if w else None


def find_mwcc_rs():
    for p in MWCC_RS_SEARCH:
        if p and Path(p).exists():
            return Path(p)
    w = shutil.which("mwcc")
    return Path(w) if w else None


def pick_backend(requested=None):
    """Return (kind, path). kind is 'mwcceppc' or 'mwcc-rs'."""
    if requested == "mwcceppc":
        m = find_mwcc()
        return ("mwcceppc", m) if m else ("mwcceppc", None)
    if requested == "mwcc-rs":
        m = find_mwcc_rs()
        return ("mwcc-rs", m) if m else ("mwcc-rs", None)
    m = find_mwcc()
    if m:
        return "mwcceppc", m
    m = find_mwcc_rs()
    return ("mwcc-rs", m) if m else ("mwcceppc", None)


def detect():
    out = {"mwcceppc": None, "candidates_searched": [p for p in MWCC_SEARCH if p],
           "mwcc_rs": None,
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
    rs = find_mwcc_rs()
    if rs:
        out["mwcc_rs"] = str(rs)
        out["mwcc_rs_builds"] = ["1.3", "1.3.2", "1.3.2r", "2.0",
                                 "2.0p1", "2.5", "2.6", "2.7"]
        out["mwcc_rs_experimental"] = ["1.1", "1.1p1", "1.2.5", "1.2.5n",
                                       "3.0a3", "3.0a3p1", "Wii/1.0"]
    dk = Path("C:/devkitPro/devkitPPC/bin/powerpc-eabi-gcc.exe")
    if dk.exists():
        out["devkitppc"] = str(dk)
    out["backend"] = pick_backend()[0] if (m or rs) else None
    return out


def compile_candidate(src, mwcc, cflags, includes, workdir,
                      kind="mwcceppc", build=DEFAULT_BUILD):
    obj = Path(workdir) / "cand.o"
    if kind == "mwcc-rs":
        cmd = [str(mwcc), "-c", str(src), "-o", str(obj), "--build", build]
        cmd += list(cflags)
        for i in includes:
            cmd += ["-i", str(i)]
    else:
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
    bases = datareloc.bases_only(dol, smap)
    refs = datareloc.retail_data_addresses(retail, rec["addr"], bases)
    resolver = datareloc.SymbolResolver(dol, smap)
    # `abs-r0` rows whose address is outside the image are plain immediates
    # (`li r0, 0` decodes as `addi r0, r0, 0`); they matter to the oracle --
    # a candidate relocating there is taking a global's address where retail
    # loads a constant -- but they are noise in a prompt.
    shown = {o: v for o, v in refs.items()
             if v[1] != "abs-r0" or resolver.in_image(v[0])}
    if shown:
        lines.append("DATA REFERENCES (r2=_SDA2_BASE_=0x%08x, "
                     "r13=_SDA_BASE_=0x%08x, both derived from the ROM's own"
                     % (bases[2], bases[13]))
        lines.append("__init_registers and cross-checked against the DOL "
                     "section table -- see datareloc.py).")
        lines.append("A candidate MUST name the symbol at the stated address: "
                     "the oracle now checks it.")
        for off in sorted(shown):
            tgt, how = shown[off]
            hit = smap.lookup(tgt)
            lines.append("  0x%08x  %-8s -> 0x%08x  %s"
                         % (rec["addr"] + off, how, tgt,
                            hit["name"] if hit else
                            resolver.name_for_address(tgt)))
        lines.append("")
    prev = [r for r in smap.order if r["addr"] < rec["addr"]][-neighbours:]
    nxt = [r for r in smap.order if r["addr"] > rec["addr"]][:neighbours]
    lines.append("NEIGHBOURS IN LINK ORDER (same translation unit, probably):")
    for r in prev + [rec] + nxt:
        lines.append("  %s0x%08x %-28s %d B"
                     % ("* " if r is rec else "  ", r["addr"], r["name"], r["size"]))
    return "\n".join(lines)


def expected_symbols(smap, retail, base_addr):
    """{offset: symbol} the retail branch at that offset resolves to.

    Without this, objdiff.compare masks a relocated `bl` operand and accepts
    ANY callee -- a candidate that calls the wrong function would MATCH.
    Selftest T6b is the control for exactly this.

    This covers REL24 branch targets only.  The other half -- data references
    (ADDR16_HA/LO, ADDR32, EMB_SDA21), which the DOL's missing data symbol
    table once made unverifiable -- is `expected_data()` below.
    """
    out = {}
    for a, w, _t in disasm(retail, base_addr):
        if (w >> 26) == 18 and (w & 1):          # bl / bla
            li = w & 0x03FFFFFC
            if li & 0x02000000:
                li -= 0x04000000
            tgt = a + li if not (w & 2) else li  # absolute for bla
            hit = smap.lookup(tgt)
            if hit:
                out[a - base_addr] = hit["name"]
    return out


def expected_data(dol, smap, retail, base_addr):
    """{offset: (address, how)} the retail DATA references resolve to.

    The companion to `expected_symbols`, and the fix for the oracle's second
    hole.  A `lwz rX, d(r13)` or a `lis`/`addi` pair in the retail bytes names
    ONE absolute address; `datareloc` reads it out of the encoding, and
    `objdiff.compare` then requires the candidate's data relocation to name a
    symbol at that same address.  See `datareloc.py` for how the small-data
    bases are established (two independent derivations, cross-checked).
    """
    return datareloc.retail_data_addresses(
        retail, base_addr, datareloc.bases_only(dol, smap))


def data_resolver(dol, smap, repo=None):
    """Candidate symbol name -> absolute address.  Fail-closed; see datareloc."""
    return datareloc.SymbolResolver(dol, smap, repo=repo)


def try_one(src, includes, kind, mwcc, cflags, build, rec, retail, obj_symbol,
            expected_syms=None, retail_addrs=None, resolve_symbol=None):
    """Compile one candidate and run it through the oracle. Returns a verdict."""
    wd = tempfile.mkdtemp(prefix="mdec_")
    # The compile runs in a scratch cwd, so the source and every include path
    # must be absolute or the compiler will not find them.
    obj, log, cmd = compile_candidate(
        Path(src).resolve(), mwcc, cflags,
        [Path(i).resolve() for i in includes], wd, kind=kind, build=build)
    if obj is None:
        return {"verdict": "BUILD_FAILED", "function": rec["name"],
                "backend": kind, "build": build, "match_pct": 0.0,
                "command": cmd, "compiler_log": log[-4000:]}, None

    e = Elf32BE(obj.read_bytes())
    cand = e.data(e.section(".text"))
    relocs = e.relocs_for(".text")
    sym = obj_symbol or rec["name"]
    for sy in e.symbols():
        if sy["name"] == sym and sy["size"]:
            cand = cand[sy["value"]:sy["value"] + sy["size"]]
            relocs = [(o - sy["value"], t, n, ad) for o, t, n, ad in relocs
                      if sy["value"] <= o < sy["value"] + sy["size"]]
            break

    v = compare(retail, cand, relocs, rec["addr"], expected_syms=expected_syms,
                retail_addrs=retail_addrs, resolve_symbol=resolve_symbol)
    v["function"] = rec["name"]
    v["address"] = "0x%08x" % rec["addr"]
    v["compiler"] = str(mwcc)
    v["backend"] = kind
    v["expected_symbols"] = {("0x%03x" % k): s
                             for k, s in (expected_syms or {}).items()}
    v["expected_data"] = {("0x%03x" % k): "0x%08x (%s)" % val
                          for k, val in (retail_addrs or {}).items()}
    if kind == "mwcc-rs":
        v["build"] = build
    v["cflags"] = cflags
    v["compiler_log"] = log[-2000:]
    v["diff_text"] = render_diff(v, retail, cand, rec["addr"])
    return v, cand


# Calibration B (spike doc §2.4): exactly one (version, flags) combination
# should reproduce the retail bytes.  A candidate that matches under EVERY
# combination has no discriminating power and settles nothing.
SWEEP_BUILDS = ["1.3", "1.3.2", "2.0", "2.0p1", "2.5", "2.6", "2.7"]
SWEEP_OPTS = ["-O4,p", "-O4", "-O3", "-O2", "-O1", "-O0"]


def sweep(src, includes, kind, mwcc, rec, retail, obj_symbol, base_cflags,
          expected_syms=None, retail_addrs=None, resolve_symbol=None):
    rows = []
    for build in SWEEP_BUILDS:
        for opt in SWEEP_OPTS:
            flags = [f for f in base_cflags if not f.startswith("-O")] + [opt]
            v, _ = try_one(src, includes, kind, mwcc, flags, build,
                           rec, retail, obj_symbol, expected_syms,
                           retail_addrs, resolve_symbol)
            rows.append({"build": build, "opt": opt,
                         "verdict": v["verdict"],
                         "match_pct": v.get("match_pct", 0.0)})
    return rows


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
    ap.add_argument("--backend", choices=["mwcceppc", "mwcc-rs"],
                    help="which compiler to drive; default: mwcceppc if "
                         "present, else mwcc-rs")
    ap.add_argument("--build", default=DEFAULT_BUILD,
                    help="mwcc-rs compiler build label (default 2.7)")
    ap.add_argument("--sweep", action="store_true",
                    help="Calibration B: compile the candidate under every "
                         "supported build x optimisation level and report "
                         "which combinations reproduce the retail bytes")
    a = ap.parse_args()

    if a.detect:
        d = detect()
        print(json.dumps(d, indent=1))
        if a.json:
            Path(a.json).write_text(json.dumps(d, indent=1))
        return 0 if (d["mwcceppc"] or d["mwcc_rs"]) else 3

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

    kind, mwcc = pick_backend(a.backend)
    if mwcc is None:
        msg = {
            "verdict": "NO_COMPILER",
            "function": rec["name"],
            "backend": kind,
            "detail": ("no PowerPC compiler found. The matching oracle cannot "
                       "run without one. mwcceppc searched: %s. mwcc-rs "
                       "searched: %s"
                       % (", ".join(p for p in MWCC_SEARCH if p),
                          ", ".join(p for p in MWCC_RS_SEARCH if p))),
        }
        print(json.dumps(msg, indent=1), file=sys.stderr)
        if a.json:
            Path(a.json).write_text(json.dumps(msg, indent=1))
        return 3

    if a.cflags:
        cflags = a.cflags.split()
    else:
        cflags = DEFAULT_CFLAGS_RS if kind == "mwcc-rs" else DEFAULT_CFLAGS

    exp = expected_symbols(smap, retail, rec["addr"])
    expd = expected_data(dol, smap, retail, rec["addr"])
    resolver = data_resolver(dol, smap, repo=a.repo)

    if a.sweep:
        rows = sweep(a.src, a.include, kind, mwcc, rec, retail,
                     a.obj_symbol, cflags, exp, expd, resolver)
        hits = [r for r in rows if r["verdict"] == "MATCH"]
        print("CALIBRATION SWEEP  %s @ 0x%08x  backend=%s"
              % (rec["name"], rec["addr"], kind))
        print("%-8s %-8s %-14s %s" % ("build", "opt", "verdict", "match%"))
        for r in rows:
            print("%-8s %-8s %-14s %6.2f"
                  % (r["build"], r["opt"], r["verdict"], r["match_pct"]))
        print("\n%d of %d combinations MATCH" % (len(hits), len(rows)))
        if len(hits) == len(rows):
            print("DISCRIMINATION: NONE -- this function does not distinguish "
                  "any build or optimisation level.")
        elif hits:
            print("DISCRIMINATING: matches only " +
                  ", ".join("%s/%s" % (r["build"], r["opt"]) for r in hits))
        out = {"function": rec["name"], "address": "0x%08x" % rec["addr"],
               "backend": kind, "rows": rows, "matching": hits}
        if a.json:
            Path(a.json).write_text(json.dumps(out, indent=1))
        return 0 if hits else 1

    v, _ = try_one(a.src, a.include, kind, mwcc, cflags, a.build,
                   rec, retail, a.obj_symbol, exp, expd, resolver)
    if v["verdict"] == "BUILD_FAILED":
        print(json.dumps(v, indent=1))
        if a.json:
            Path(a.json).write_text(json.dumps(v, indent=1))
        return 2
    print(v["diff_text"])
    for r in v.get("data_relocs_verified") or []:
        print("DATA RELOC  +0x%03x %-18s %-22s -> %s  (%s, %s)  VERIFIED"
              % (r["offset"], r["type"], r["symbol"], r["retail_addr"],
                 r["retail_how"], r["symbol_source"]))
    for r in v.get("data_reloc_errors") or []:
        print("DATA RELOC  +0x%03x %-18s WRONG GLOBAL: %s"
              % (r["offset"], r["type"], r["reason"]))
    for r in v.get("unchecked_relocs") or []:
        print("UNVERIFIED  +0x%03x %-18s %s"
              % (r["offset"], r["type"], r["reason"]))
    print("\nVERDICT %s  %.2f%%" % (v["verdict"], v["match_pct"]))
    if v["verdict"] != "MATCH" and v.get("first_diff"):
        fd = v["first_diff"]
        print("FIRST DIFF %s  retail: %-30s candidate: %s"
              % (fd["addr"], fd["retail"], fd["cand"]))
    if a.json:
        Path(a.json).write_text(json.dumps(v, indent=1))
    return 0 if v["verdict"] == "MATCH" else 1


if __name__ == "__main__":
    sys.exit(main())
