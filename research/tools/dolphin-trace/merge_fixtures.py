#!/usr/bin/env python3
"""merge_fixtures.py — combine per-export trace fixtures into one spec corpus.

`capture_oracle.py capture` emits ONE fixture per function
(`corpora/<unit>.<fn>.dolphin-trace.jsonl`), because the stub gives one
connection per emulator boot and each export needs its own boot. But
`research/decomp/oracle-harness/run-unit.mjs` loads exactly one fixture per
unit (`spec.meta.fixture`) and dispatches each case record to the spec's runner
by its `fn` field. A spec that covers MORE THAN ONE export therefore needs a
merged corpus — that is all this tool makes.

The merged file keeps every case record verbatim except `n`, which is
renumbered across the whole file (run-unit.mjs keys its per-case
classification by `n`, so duplicate indices from different functions would
collide). The original per-function index survives as `fn_n`.

The merged header deliberately has NO top-level `fn`: the driver
(`port_wasm_units._trace_capture`) refreshes a spec corpus in place only when
the corpus header's `fn` matches the single export it just captured, and a
merged corpus must never be silently overwritten by one export's fixture.
Re-run this tool after a capture sweep instead.

Usage:
  python merge_fixtures.py --unit auto-c0020-007 \
      --fn FUN_800c42bc --fn FUN_800c4448 ... [--out <path>]

  python merge_fixtures.py --unit auto-c0020-007 --check

With no --fn, every `corpora/<unit>.<fn>.dolphin-trace.jsonl` that has at
least one case is merged, in filename order.

STALENESS. The merged header records each source fixture's sha256, because a
later `verify-unit --unit <u>` WITH capture rewrites the per-export fixtures but
does not re-merge -- the spec would then replay a stale corpus while the fresh
capture sat unread. `--check` compares the recorded digests against the sources
on disk and exits nonzero when the merge needs re-running; run it after any
capture sweep for a unit whose spec covers more than one export.
"""
from __future__ import annotations

import argparse
import hashlib
import json
import re
import sys
from datetime import datetime, timezone
from pathlib import Path

REPO_ROOT = Path(__file__).resolve().parents[3]
CORPORA = REPO_ROOT / "research/decomp/oracle-harness/corpora"
SUFFIX = ".dolphin-trace.jsonl"


def per_fn_path(unit: str, fn: str) -> Path:
    return CORPORA / f"{unit}.{fn}{SUFFIX}"


def discover(unit: str) -> list[str]:
    pattern = re.compile(re.escape(unit) + r"\.(.+)" + re.escape(SUFFIX) + "$")
    found = []
    for path in sorted(CORPORA.glob(f"{unit}.*{SUFFIX}")):
        match = pattern.match(path.name)
        if match:
            found.append(match.group(1))
    return found


def sha256(path: Path) -> str:
    return hashlib.sha256(path.read_bytes()).hexdigest()


def read_fixture(path: Path) -> tuple[dict, list[dict]]:
    lines = [l for l in path.read_text(encoding="utf-8").split("\n") if l]
    if not lines:
        raise SystemExit(f"{path}: empty fixture")
    header = json.loads(lines[0])
    if header.get("kind") != "header":
        raise SystemExit(f"{path}: first record is not a header")
    return header, [json.loads(l) for l in lines[1:]]


def check(unit: str, merged: Path) -> int:
    """Exit 0 iff `merged` is up to date with the per-export fixtures it names."""
    if not merged.is_file():
        print(f"STALE: no merged corpus at {merged}")
        return 1
    header, _ = read_fixture(merged)
    members = header.get("functions") or []
    if not members:
        print(f"STALE: {merged} has no `functions` list (not produced by this tool)")
        return 1
    problems = []
    for m in members:
        src = CORPORA / Path(m["fixture"]).name
        if not src.is_file():
            problems.append(f"{m['fn']}: source fixture missing ({src})")
        elif m.get("sha256") is None:
            problems.append(f"{m['fn']}: merged header predates digest recording")
        elif sha256(src) != m["sha256"]:
            problems.append(f"{m['fn']}: source fixture changed since the merge")
    if problems:
        print(f"STALE merged corpus {merged}:")
        for line in problems:
            print("  " + line)
        print("  re-run merge_fixtures.py for this unit")
        return 1
    print(json.dumps({"merged": str(merged), "fresh": True,
                      "functions": {m["fn"]: m["cases"] for m in members}}, indent=2))
    return 0


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--unit", required=True)
    ap.add_argument("--fn", action="append", default=[],
                    help="export to include (repeatable); default: all with cases")
    ap.add_argument("--out", default=None)
    ap.add_argument("--allow-empty", action="store_true",
                    help="include exports whose fixture captured 0 cases")
    ap.add_argument("--check", action="store_true",
                    help="do not write; verify the existing merged corpus still "
                         "matches its source fixtures (exit 1 if stale)")
    a = ap.parse_args()

    if a.check:
        return check(a.unit, Path(a.out) if a.out else CORPORA / f"{a.unit}{SUFFIX}")

    names = a.fn or discover(a.unit)
    if not names:
        raise SystemExit(f"no per-export fixtures for {a.unit} under {CORPORA}")

    members: list[dict] = []
    cases: list[dict] = []
    for fn in names:
        path = per_fn_path(a.unit, fn)
        if not path.is_file():
            raise SystemExit(f"missing fixture {path}")
        header, records = read_fixture(path)
        if header.get("unit") != a.unit:
            raise SystemExit(f"{path}: header unit {header.get('unit')!r} != {a.unit!r}")
        if header.get("fn") != fn:
            raise SystemExit(f"{path}: header fn {header.get('fn')!r} != {fn!r}")
        got = [r for r in records if r.get("kind") == "case"]
        if len(got) != len(records):
            raise SystemExit(f"{path}: non-case records are not supported by the merge")
        if not got and not a.allow_empty:
            print(f"  skipping {fn}: 0 cases", file=sys.stderr)
            continue
        for rec in got:
            rec["fn_n"] = rec.get("n")
            rec["n"] = len(cases)
            cases.append(rec)
        members.append({
            "fn": fn,
            "addr": header.get("addr"),
            "cases": len(got),
            "fixture": f"corpora/{path.name}",
            "sha256": sha256(path),
            "source": header.get("source", {}),
            "dumped_at": header.get("dumped_at"),
        })

    if not members:
        raise SystemExit("nothing to merge (every fixture had 0 cases)")

    merged_header = {
        "kind": "header",
        "fixture_schema": 1,
        "trace_schema": 1,
        "unit": a.unit,
        "reference_kind": "dolphin_trace",
        "merged_by": "research/tools/dolphin-trace/merge_fixtures.py",
        "dumped_at": datetime.now(timezone.utc).isoformat().replace("+00:00", "Z"),
        "counts": {"case": len(cases)},
        "functions": members,
    }
    out = Path(a.out) if a.out else CORPORA / f"{a.unit}{SUFFIX}"
    out.parent.mkdir(parents=True, exist_ok=True)
    with out.open("w", encoding="utf-8", newline="\n") as fh:
        fh.write(json.dumps(merged_header) + "\n")
        for rec in cases:
            fh.write(json.dumps(rec) + "\n")
    print(json.dumps({"out": str(out), "cases": len(cases),
                      "functions": {m["fn"]: m["cases"] for m in members}}, indent=2))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
