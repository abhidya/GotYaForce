#!/usr/bin/env python3
"""verify.py -- re-prove every entry in matched.json against the retail DOL.

    python src-match/verify.py              # all entries, exit 0 iff all MATCH
    python src-match/verify.py --sweep      # additionally report which
                                            # compiler builds each one
                                            # discriminates
    python src-match/verify.py --control    # add the negative controls

This is the regression gate for the matched corpus.  A matched function is
matched forever ONLY if the toolchain is pinned, so this re-runs the compiler
rather than trusting the registry.

The controls come in two families and both must hold:

  * CONTROLS -- deliberately wrong candidates that must be REJECTED.
  * DATA_RELOC_CONTROLS -- candidates that exercise the data-relocation
    address check (`research/tools/matching-decomp/datareloc.py`).  These
    assert the exact verdict, not merely rejection, because the distinction
    between MISMATCH (the candidate names a DIFFERENT global) and
    MATCH_UNVERIFIED (nothing could resolve the symbol, so nothing is
    claimed) is the whole content of that check.  Before it existed, the
    first of these reported `MATCH 100.00%`.
"""
from __future__ import annotations

import argparse
import json
import subprocess
import sys
from pathlib import Path

HERE = Path(__file__).resolve().parent
ROOT = HERE.parent
TOOLS = ROOT / "research" / "tools" / "matching-decomp"
sys.path.insert(0, str(TOOLS))

REG = json.loads((HERE / "matched.json").read_text())

# Deliberately wrong candidates.  The oracle MUST reject each one; if it does
# not, the harness is not measuring anything.
CONTROLS = [
    ("zz_0206f8c_", "f",
     "typedef struct S { char pad[0x2d0]; int x; } S;\n"
     "int f(S *s) { return s->x; }\n",
     "wrong structure offset"),
    ("zz_00122c8_", "f",
     "extern void some_other_function(void);\n"
     "void f(void) { some_other_function(); }\n",
     "right shape, WRONG CALLEE -- caught only by the relocation symbol check"),
    # Behaviourally identical on every input the retail function can receive,
    # but the guard is a SIGNED compare (`cmpwi`) instead of the unsigned
    # pointer compare (`cmplwi`) the retail bytes carry.  This project's
    # existing behavioural standards -- transcript and callstream -- would
    # accept it.  The oracle does not.  That rejection is the whole value of
    # matching decompilation, and its whole cost.
    ("zz_02a0a6c_", "f",
     "void f(int address) { if (address == 0) return; *(int *)address = 4; }\n",
     "behaviourally identical, differently encoded (signed vs unsigned compare)"),
]

# The data-relocation control set.  `zz_000a144_` stores 0 to the two globals
# at 0x804360cc and 0x804360c8 (r13 - 0x54d4 and r13 - 0x54d8); `zz_0005984_`
# stores its argument to the global at 0x804360c0.  Each case states the
# verdict the oracle must return, and why.
DATA_RELOC_CONTROLS = [
    ("zz_000a144_", "f",
     "extern int DAT_804360cc;\nextern int DAT_804360c8;\n"
     "void f(void) { DAT_804360cc = 0; DAT_804360c8 = 0; }\n",
     "MATCH", "the globals the retail bytes actually name"),
    ("zz_000a144_", "f",
     "extern int DAT_804360c8;\nextern int DAT_804360c4;\n"
     "void f(void) { DAT_804360c8 = 0; DAT_804360c4 = 0; }\n",
     "MISMATCH",
     "DIFFERENT globals at plausible addresses -- this is the candidate that "
     "reported MATCH 100.00% before the data-relocation check existed"),
    ("zz_0005984_", "f",
     "extern int DAT_804360c4;\nvoid f(int p0) { DAT_804360c4 = p0; }\n",
     "MISMATCH", "the neighbouring global, off by four"),
    ("zz_000a144_", "f",
     "extern int g_someGlobal;\nextern int g_otherGlobal;\n"
     "void f(void) { g_someGlobal = 0; g_otherGlobal = 0; }\n",
     "MATCH_UNVERIFIED",
     "symbols that resolve to no address -- unproved, so not a match"),
    ("zz_0005984_", "f",
     "extern int DAT_deadbeef;\nvoid f(int p0) { DAT_deadbeef = p0; }\n",
     "MATCH_UNVERIFIED",
     "a name encoding an address in no DOL section and not in bss"),
]


def run(function, src, sym, build, extra=()):
    out = subprocess.run(
        [sys.executable, str(TOOLS / "match.py"),
         "--function", function, "--src", str(src), "--obj-symbol", sym,
         "--build", build, "--backend", "mwcc-rs"] + list(extra),
        capture_output=True, cwd=str(ROOT))
    return out.returncode, (out.stdout + out.stderr).decode("latin1", "replace")


def verdict_of(rc, log):
    for line in log.splitlines():
        if line.startswith("VERDICT "):
            return line.split()[1]
    return "BUILD_FAILED" if rc == 2 else ("NO_COMPILER" if rc == 3 else "?")


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--sweep", action="store_true")
    ap.add_argument("--control", action="store_true")
    a = ap.parse_args()

    build = REG["compiler"]["build_label"]
    ok = bad = 0
    print("MATCHED CORPUS  backend=%s  commit=%s  build=%s"
          % (REG["compiler"]["backend"], REG["compiler"]["commit"][:12], build))
    print("-" * 72)
    for e in REG["functions"]:
        rc, log = run(e["name"], HERE / e["src"], e["sym"], build)
        verdict = "MATCH" if rc == 0 else ("BUILD_FAILED" if rc == 2 else "MISMATCH")
        flag = "ok  " if rc == 0 else "FAIL"
        print("[%s] %-26s %-4d insns  %-12s  iters=%d  exact=%s"
              % (flag, e["name"], e["insns"], verdict, e["iterations"],
                 str(e["exact_bytes"]).lower()))
        ok += rc == 0
        bad += rc != 0

    if a.control:
        print()
        print("NEGATIVE CONTROLS (each MUST be rejected)")
        print("-" * 72)
        tmp = HERE / "work"
        tmp.mkdir(exist_ok=True)
        for i, (fn, sym, src, why) in enumerate(CONTROLS):
            p = tmp / ("control_%d.c" % i)
            p.write_text(src)
            rc, _ = run(fn, p, sym, build)
            good = rc != 0
            print("[%s] %-26s rejected=%s  (%s)"
                  % ("ok  " if good else "FAIL", fn, rc != 0, why))
            ok += good
            bad += not good

        print()
        print("DATA-RELOCATION CONTROLS (the verdict must be EXACTLY as stated)")
        print("-" * 72)
        for i, (fn, sym, src, want, why) in enumerate(DATA_RELOC_CONTROLS):
            p = tmp / ("datareloc_%d.c" % i)
            p.write_text(src)
            rc, log = run(fn, p, sym, build)
            got = verdict_of(rc, log)
            good = got == want
            print("[%s] %-22s want %-17s got %-17s"
                  % ("ok  " if good else "FAIL", fn, want, got))
            print("       %s" % why)
            ok += good
            bad += not good

    if a.sweep:
        print()
        print("CALIBRATION SWEEP -- which (build, -O level) pairs reproduce each")
        print("-" * 72)
        for e in REG["functions"]:
            j = HERE / "work" / ("sweep_%s.json" % e["name"].replace("-", "_"))
            j.parent.mkdir(exist_ok=True)
            subprocess.run(
                [sys.executable, str(TOOLS / "match.py"),
                 "--function", e["name"], "--src", str(HERE / e["src"]),
                 "--obj-symbol", e["sym"], "--backend", "mwcc-rs",
                 "--sweep", "--json", str(j)],
                capture_output=True, cwd=str(ROOT))
            d = json.loads(j.read_text())
            builds = sorted({r["build"] for r in d["matching"]})
            total = len({r["build"] for r in d["rows"]})
            note = "no discrimination" if len(builds) == total \
                else "EXCLUDES " + ", ".join(
                    sorted({r["build"] for r in d["rows"]} - set(builds)))
            print("  %-26s %d/%d rows match   %s"
                  % (e["name"], len(d["matching"]), len(d["rows"]), note))

    print()
    print("%d ok, %d failed" % (ok, bad))
    return 0 if bad == 0 else 1


if __name__ == "__main__":
    sys.exit(main())
