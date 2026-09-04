#!/usr/bin/env python3
"""mwcc_fork.py -- apply this project's mwcc-rs changes to the pinned checkout.

The compiler lives in gitignored `.tools/mwcc-rs`, extracted from the tarball of
`zcanann/mwcc-rs` commit 7c093483f9c6c5775eb856a1a343a5dc6671233b (see
TOOLCHAIN.md).  It is NOT vendored.  What IS committed is this file plus
`mwcc-rs-fork/`, which together reconstruct the fork exactly:

  * `mwcc-rs-fork/**` holds the source files this project wrote in full,
    dropped over the pinned tree;
  * `INSERTIONS` below holds every other change as an exact string replacement,
    each anchored on text unique in the pinned file.

Both are idempotent and both are checked, so a run either reproduces the fork
byte for byte or says exactly which anchor no longer matches.

    python research/tools/matching-decomp/mwcc_fork.py --check
    python research/tools/matching-decomp/mwcc_fork.py --apply
    python research/tools/matching-decomp/mwcc_fork.py --capture   # dev: pull
                                                                   # the live
                                                                   # tree back
                                                                   # into git
"""
from __future__ import annotations

import argparse
import shutil
import sys
from pathlib import Path

HERE = Path(__file__).resolve().parent
REPO = HERE.parent.parent.parent
FORK = HERE / "mwcc-rs-fork"
DEFAULT_TREE = REPO / ".tools" / "mwcc-rs"

CODEGEN = "crates/pipeline/mwcc-syntax-trees-to-machine-code/src"
MACHINE = "crates/representations/mwcc-machine-code/src"
VREG = "crates/representations/mwcc-vreg/src"

# Whole files this project authored or rewrote, copied over the pinned tree.
WHOLE_FILES = [
    CODEGEN + "/expressions/materialized_bitand_constant.rs",
]

# (path, anchor, replacement).  The anchor must appear EXACTLY ONCE in the
# pinned file; the replacement contains the anchor, so applying twice is a
# no-op that `--check` reports as already-applied.
INSERTIONS = [
    # ---- fix 1: `andis.` had no instruction ---------------------------------
    (
        MACHINE + "/instruction.rs",
        "    /// `andi. rA, rS, UIMM` — AND immediate, ALWAYS record (no plain andi).\n"
        "    AndImmediateRecord { a: u8, s: u8, immediate: u16 },\n",
        "    /// `andi. rA, rS, UIMM` — AND immediate, ALWAYS record (no plain andi).\n"
        "    AndImmediateRecord { a: u8, s: u8, immediate: u16 },\n"
        "    /// `andis. rA, rS, UIMM` — AND the high half, ALWAYS record (no plain andis).\n"
        "    AndImmediateShiftedRecord { a: u8, s: u8, immediate: u16 },\n",
    ),
    (
        MACHINE + "/encoding.rs",
        "            Instruction::AndImmediateRecord { a, s, immediate } => "
        "(28 << 26) | ((s as u32) << 21) | ((a as u32) << 16) | (immediate as u32),\n",
        "            Instruction::AndImmediateRecord { a, s, immediate } => "
        "(28 << 26) | ((s as u32) << 21) | ((a as u32) << 16) | (immediate as u32),\n"
        "            Instruction::AndImmediateShiftedRecord { a, s, immediate } => "
        "(29 << 26) | ((s as u32) << 21) | ((a as u32) << 16) | (immediate as u32),\n",
    ),
    (
        VREG + "/description.rs",
        "| XorImmediate { a, s, .. } | AndImmediateRecord { a, s, .. } "
        "| XorImmediateShifted { a, s, .. }",
        "| XorImmediate { a, s, .. } | AndImmediateRecord { a, s, .. } "
        "| AndImmediateShiftedRecord { a, s, .. } | XorImmediateShifted { a, s, .. }",
    ),
]


def read(path):
    # newline="" so Python does not translate the pinned tree's LF endings into
    # CRLF on this Windows host -- that alone would make every rewritten file
    # differ from the reference copy.
    with open(str(path), "r", encoding="utf-8", newline="") as f:
        return f.read()


def write(path, text):
    with open(str(path), "w", encoding="utf-8", newline="") as f:
        f.write(text)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--tree", default=str(DEFAULT_TREE),
                    help="the extracted mwcc-rs checkout (default .tools/mwcc-rs)")
    ap.add_argument("--apply", action="store_true")
    ap.add_argument("--check", action="store_true")
    ap.add_argument("--capture", action="store_true",
                    help="copy the live WHOLE_FILES back into mwcc-rs-fork/")
    args = ap.parse_args()
    tree = Path(args.tree)
    if not tree.is_dir():
        print("no mwcc-rs checkout at %s -- see TOOLCHAIN.md" % tree)
        return 3

    if args.capture:
        for rel in WHOLE_FILES:
            dst = FORK / rel
            dst.parent.mkdir(parents=True, exist_ok=True)
            shutil.copyfile(tree / rel, dst)
            print("captured %s" % rel)
        return 0

    problems = 0
    for rel in WHOLE_FILES:
        src, dst = FORK / rel, tree / rel
        same = dst.exists() and read(dst) == read(src)
        if same:
            print("[ok      ] %s" % rel)
            continue
        if args.apply:
            dst.parent.mkdir(parents=True, exist_ok=True)
            write(dst, read(src))
            print("[written ] %s" % rel)
        else:
            print("[DIFFERS ] %s" % rel)
            problems += 1

    for rel, anchor, replacement in INSERTIONS:
        path = tree / rel
        text = read(path)
        if replacement in text:
            print("[ok      ] %s  (%s...)" % (rel, anchor.strip()[:40]))
            continue
        count = text.count(anchor)
        if count != 1:
            print("[ANCHOR  ] %s  anchor appears %d times, expected 1" % (rel, count))
            problems += 1
            continue
        if args.apply:
            write(path, text.replace(anchor, replacement, 1))
            print("[patched ] %s" % rel)
        else:
            print("[MISSING ] %s  (%s...)" % (rel, anchor.strip()[:40]))
            problems += 1

    if problems:
        print("\n%d item(s) not applied.  Run with --apply." % problems)
        return 1
    print("\nfork is fully applied to %s" % tree)
    return 0


if __name__ == "__main__":
    sys.exit(main())
