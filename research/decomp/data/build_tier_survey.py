"""Generate verification-tier-survey.json: the durable record of how much of the
ROM corpus is verifiable AT ALL, and by which standard.

Why this file exists
--------------------
The tier ceiling is measured by `research/tools/OGhidra/tools/survey_plan_tiers.py`,
which lives in the OGhidra tool checkout -- a separate repository that is NOT
vendored here (see README "The workflow, with real commands"). Until 2026-08-30 the
survey's numbers existed ONLY as that script's stdout: they were quoted into design
documents by hand, could not be diffed, and could not be re-derived from a clone
without knowing the exact invocation. Numbers that drive project decisions and live
only in a terminal scrollback are numbers the project is in the process of losing.

This wrapper is the tracked half. It runs the survey, computes the digests of every
input that produced the answer, and writes a schema'd artifact next to the other
generated data. The artifact is the citable source; the survey stays authoritative
for the CLASSIFICATION LOGIC, this file is authoritative for WHAT WAS MEASURED, WHEN,
AND FROM WHAT.

What the artifact does and does not claim
-----------------------------------------
This is a CEILING measurement, not a progress measurement. It is model-free and
static: it asks, of each function's decompiled C, "could a spec of this standard be
built for it at all", never "has one been built" or "did it pass". A function counted
`transcript_green` here has NOT been verified; it has been found ELIGIBLE. Actual
verified units are counted from committed result artifacts, not from this file.

The two standards are reported separately and then combined, never merged into one
number that hides which claim a function can actually reach:

  oracle_green     byte-exact write comparison, per call (run-unit.mjs)
  transcript_green callee-boundary call sequence + arguments + return value, per
                   call (run-transcript.mjs) -- STRICTLY WEAKER: no write comparison

`combined` names, per function, the STRONGEST standard it can reach.

Usage
-----
    python research/decomp/data/build_tier_survey.py
    python research/decomp/data/build_tier_survey.py --check   # drift check, no write

`--check` re-derives the survey and compares it against the committed artifact,
ignoring only the `generated_utc` timestamp; a non-zero exit means the tracked
numbers no longer match the tree that produced them.

The OGhidra checkout is required. Without it the script exits 2 and explains why --
it never writes a partial or stale artifact.
"""

from __future__ import annotations

import argparse
import hashlib
import json
import os
import subprocess
import sys
import tempfile
from datetime import datetime, timezone
from pathlib import Path

DATA_DIR = Path(__file__).resolve().parent
PRODUCT_ROOT = DATA_DIR.parents[2]
REGISTRY_PATH = DATA_DIR / "oracle-registry.json"
OUTPUT_PATH = DATA_DIR / "verification-tier-survey.json"

SCHEMA = "gf.verification-tier-survey.v1"

# Relative to the OGhidra checkout. These four files are the whole classification
# logic; a change to any of them can move the numbers, so all four are digested.
SURVEY_RELPATH = "tools/survey_plan_tiers.py"
LOGIC_RELPATHS = (
    SURVEY_RELPATH,
    "src/port_c_evidence.py",
    "src/port_spec_emit.py",
    "src/port_plan_derive.py",
    # dispatch_green's eligibility predicate IS the lowering's own parser: a
    # function is reachable exactly when every indirect call site in its
    # closure can be rewritten. A change to the parser moves the number.
    "src/port_indirect_lowering.py",
)

# Refusal strings emitted by survey_plan_tiers.transcript_tier_of, mapped to stable
# keys. Mapping by prefix so a wording tweak upstream does not silently drop a
# bucket -- an unmapped refusal raises instead.
REFUSAL_KEYS = {
    "dispatches through a ROM function-pointer table":
        "rom_function_pointer_dispatch",
    "empty transcript":
        "empty_transcript",
}


def sha256_file(path: Path) -> str:
    digest = hashlib.sha256()
    with path.open("rb") as handle:
        for block in iter(lambda: handle.read(1 << 20), b""):
            digest.update(block)
    return digest.hexdigest()


def file_stamp(path: Path, root: Path) -> dict:
    return {
        "path": path.relative_to(root).as_posix(),
        "bytes": path.stat().st_size,
        "sha256": sha256_file(path),
    }


def chunk_corpus_stamp(registry: dict, repo_root: Path) -> dict:
    """A rolled digest over every decompiled-C chunk the survey actually reads.

    The survey slices each function's verbatim C out of its chunk file, so the chunk
    corpus is as much an input as the registry is. Rolling one digest over the sorted
    (relpath, sha256) pairs keeps the artifact small while still failing loudly if any
    chunk changes.
    """
    seen: set[str] = set()
    for entry in registry.get("functions") or []:
        chunk = entry.get("chunk_file")
        if chunk:
            seen.add(chunk)
    rolled = hashlib.sha256()
    present = 0
    missing = []
    for relpath in sorted(seen):
        path = repo_root / relpath
        if not path.is_file():
            missing.append(relpath)
            continue
        present += 1
        rolled.update(relpath.encode("utf-8"))
        rolled.update(sha256_file(path).encode("ascii"))
    stamp = {
        "files_referenced": len(seen),
        "files_present": present,
        "sha256_rolled": rolled.hexdigest(),
    }
    if missing:
        # Recorded, not hidden: a missing chunk means those functions were counted
        # `no_source` and the ceiling is measured against an incomplete corpus.
        stamp["files_missing"] = sorted(missing)
    return stamp


def oghidra_commit(oghidra_root: Path) -> str:
    """Best-effort commit of the tool checkout, for human traceability only.

    Deliberately NOT part of the --check comparison: the digests above are what
    actually determine the numbers, and a tool commit that does not touch them must
    not be reported as drift.
    """
    try:
        proc = subprocess.run(["git", "-C", str(oghidra_root), "rev-parse", "HEAD"],
                              capture_output=True, text=True)
    except OSError:
        return "unknown"
    return proc.stdout.strip() if proc.returncode == 0 else "unknown"


def default_python(oghidra_root: Path) -> str:
    for candidate in (".venv/Scripts/python.exe", ".venv/bin/python"):
        path = oghidra_root / candidate
        if path.is_file():
            return str(path)
    return sys.executable


def run_survey(python: str, oghidra_root: Path, repo_root: Path) -> tuple[dict, dict]:
    """Returns (summary payload, per-function dump). Raises on a non-zero exit."""
    with tempfile.TemporaryDirectory(prefix="gf-tier-survey-") as tmp:
        summary_path = Path(tmp) / "summary.json"
        dump_path = Path(tmp) / "fn-tiers.json"
        cmd = [
            python, SURVEY_RELPATH,
            "--repo-root", str(repo_root),
            "--json", str(summary_path),
            "--dump-fn-tiers", str(dump_path),
        ]
        proc = subprocess.run(cmd, cwd=str(oghidra_root), capture_output=True,
                              text=True)
        if proc.returncode != 0:
            sys.stderr.write(proc.stdout)
            sys.stderr.write(proc.stderr)
            raise SystemExit(
                f"survey_plan_tiers.py exited {proc.returncode}; artifact not written")
        summary = json.loads(summary_path.read_text(encoding="utf-8"))
        dump = json.loads(dump_path.read_text(encoding="utf-8"))
    return summary, dump


def pct(count: int, total: int) -> float:
    return round(100.0 * count / total, 1) if total else 0.0


def unverifiable_breakdown(dump: dict) -> dict:
    """Split the combined-`unverifiable` set by WHY it is unverifiable.

    The survey's own transcript refusal counts are NOT this number: a function can
    have an empty transcript and still be `oracle_green`-eligible (it writes, it just
    neither calls out nor returns). Only the functions that reach NEITHER standard
    belong here, so the split is computed from the per-function dump.
    """
    out = {"rom_function_pointer_dispatch": 0, "empty_transcript": 0}
    for record in dump.values():
        if record.get("combined") != "unverifiable":
            continue
        key = ("rom_function_pointer_dispatch" if record.get("indirect")
               else "empty_transcript")
        out[key] += 1
    return out


def dispatch_breakdown(dump: dict) -> dict:
    """What became of the ROM-function-pointer-dispatch class.

    Before dispatch_green existed the whole class was unverifiable. It is now
    split: the functions whose every indirect call site the gate's lowering can
    rewrite, and the residue it refuses -- overwhelmingly because the call's
    RESULT IS USED, which the uniform frame's i32 return view cannot carry
    without silently narrowing it (design C8).
    """
    reachable = sum(1 for r in dump.values() if r.get("combined") == "dispatch_green")
    residue = sum(1 for r in dump.values()
                  if r.get("combined") == "unverifiable" and r.get("indirect"))
    sites = sum(int(r.get("dispatch_sites") or 0) for r in dump.values())
    return {
        "class_size": reachable + residue,
        "reachable": reachable,
        "still_unverifiable": residue,
        "lowerable_call_sites": sites,
    }


def map_refusals(refusals: dict) -> dict:
    out: dict[str, int] = {}
    for text, count in refusals.items():
        for prefix, key in REFUSAL_KEYS.items():
            if text.startswith(prefix):
                out[key] = out.get(key, 0) + count
                break
        else:
            raise SystemExit(
                "unrecognised transcript refusal reason from survey_plan_tiers.py: "
                f"{text!r} -- add it to REFUSAL_KEYS rather than dropping it")
    return out


def build(oghidra_root: Path, repo_root: Path, python: str) -> dict:
    registry = json.loads(REGISTRY_PATH.read_text(encoding="utf-8-sig"))
    summary, dump = run_survey(python, oghidra_root, repo_root)

    total_fn = summary["functions"]
    total_units = summary["units"]
    combined_fn = summary["combined_per_function"]
    combined_unit = summary["combined_per_unit"]
    write_tiers = summary["per_function_tier"]

    oracle_auto = combined_fn.get("oracle_green_auto", 0)
    transcript = combined_fn.get("transcript_green", 0)
    dispatch = combined_fn.get("dispatch_green", 0)
    unverifiable = combined_fn.get("unverifiable", 0)
    verifiable = total_fn - unverifiable

    breakdown = unverifiable_breakdown(dump)
    if sum(breakdown.values()) != unverifiable:
        raise SystemExit("unverifiable breakdown does not sum to the combined total")

    covered_units = total_units - combined_unit.get("has_unverifiable_export", 0)

    return {
        "schema": SCHEMA,
        "generated_utc": datetime.now(timezone.utc).strftime("%Y-%m-%dT%H:%M:%SZ"),
        "survey_tool_commit": oghidra_commit(oghidra_root),
        "generator": "research/decomp/data/build_tier_survey.py",
        "survey_tool": f"research/tools/OGhidra/{SURVEY_RELPATH}",
        "measurement_kind": "ceiling",
        "claims": {
            "is": "Static, model-free eligibility: could a spec of this standard be "
                  "built for this function at all.",
            "is_not": "Not a verification result. A function counted here has NOT "
                      "been verified; verified units are counted from committed "
                      "result artifacts, never from this file.",
            "oracle_green": "Byte-exact per-call write comparison "
                            "(research/decomp/oracle-harness/run-unit.mjs).",
            "transcript_green": "Callee-boundary call sequence, arguments and return "
                                "value (research/decomp/oracle-harness/"
                                "run-transcript.mjs). STRICTLY WEAKER than "
                                "oracle_green: no write set is compared. It never "
                                "upgrades into an oracle_green claim.",
            "dispatch_green": "ROM function-pointer dispatch stream: the site, the "
                              "RESOLVED GameCube target, the uniform-frame arguments "
                              "and the return of every indirect call "
                              "(research/decomp/oracle-harness/run-dispatch.mjs), "
                              "against the address the console's own branch register "
                              "held. ORTHOGONAL to the two above, not a rung of the "
                              "same ladder: it observes a channel they cannot see and "
                              "is blind to channels they check, and it is never "
                              "totalled with either. It requires the module to be "
                              "built with the gate's indirect-call lowering.",
            "combined": "Per function, the STRONGEST standard it can reach. A unit "
                        "whose exports land on a MIX of standards is reported mixed, "
                        "never rounded up to the stronger one.",
        },
        "inputs": {
            "oracle_registry": file_stamp(REGISTRY_PATH, repo_root),
            "chunk_corpus": chunk_corpus_stamp(registry, repo_root),
            "classification_logic": [
                file_stamp(oghidra_root / rel, oghidra_root) for rel in LOGIC_RELPATHS
                if (oghidra_root / rel).is_file()
            ],
        },
        "totals": {"functions": total_fn, "units": total_units},
        "per_function": {
            "oracle_green": {"count": oracle_auto, "pct": pct(oracle_auto, total_fn)},
            "transcript_green": {"count": transcript,
                                 "pct": pct(transcript, total_fn)},
            "dispatch_green": {"count": dispatch, "pct": pct(dispatch, total_fn)},
            "verifiable_by_some_tier": {"count": verifiable,
                                        "pct": pct(verifiable, total_fn)},
            "unverifiable": {
                "count": unverifiable,
                "pct": pct(unverifiable, total_fn),
                "reasons": breakdown,
            },
        },
        "per_unit": {
            "all_exports_oracle_green":
                combined_unit.get("all_exports_oracle_green", 0),
            "all_exports_transcript_green":
                combined_unit.get("all_exports_transcript_green", 0),
            "all_exports_covered_mixed_tiers":
                combined_unit.get("all_exports_covered_mixed_tiers", 0),
            "has_unverifiable_export":
                combined_unit.get("has_unverifiable_export", 0),
            "full_export_coverage": {"count": covered_units,
                                     "pct": pct(covered_units, total_units)},
        },
        "write_set_ceiling": {
            "note": "The ORIGINAL oracle_green-only ceiling, before transcript_green "
                    "existed. Kept because its dominant refusal -- 'stores nothing a "
                    "capture could compare' -- is the fact that motivated the second "
                    "standard: for those functions a write comparison is not hard, "
                    "it is EMPTY, and a spec over them passes vacuously.",
            "per_function_tier": dict(sorted(write_tiers.items())),
            "human_reasons": dict(sorted(summary["human_reasons"].items())),
            "per_unit_rollup": dict(sorted(summary["per_unit_rollup"].items())),
        },
        "transcript_eligibility_raw": {
            "note": "Transcript eligibility taken ALONE, before combining with the "
                    "write-set ceiling. These refusal counts are deliberately larger "
                    "than per_function.unverifiable.reasons: a function can have an "
                    "empty transcript and still be oracle_green-eligible.",
            "eligible": summary["transcript_green"]["verifiable"],
            "refused": map_refusals(summary["transcript_green"]["refusals"]),
        },
        "dispatch_eligibility": {
            "note": "What dispatch_green did to the class that had no route at all. "
                    "The residue is functions whose indirect call RESULT IS USED: the "
                    "uniform frame's i32 result is only a VIEW of the return slot and "
                    "an indirect site has no callee prototype to derive the true "
                    "return class from, so the lowering refuses them rather than "
                    "narrowing a return silently.",
            "requires": "a module built with the gate's indirect-call lowering "
                        "(research/tools/OGhidra/src/port_indirect_lowering.py) and "
                        "the dispatch companion in trace mode; a standalone unit "
                        "built the ordinary way is still unobservable.",
            "not_checked_statically": "the capture plan also audits the ROM's bctrl "
                                      "count against the lowered C's site count per "
                                      "function. That needs the DOL, so a function "
                                      "counted eligible here can still be refused at "
                                      "plan time.",
            **dispatch_breakdown(dump),
        },
        "plan_size": dict(sorted(summary["plan_size"].items())),
    }


def serialise(payload: dict) -> str:
    return json.dumps(payload, indent=2, sort_keys=False) + "\n"


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    parser.add_argument(
        "--oghidra-root",
        default=os.environ.get("OGHIDRA_ROOT",
                               str(PRODUCT_ROOT / "research" / "tools" / "OGhidra")),
        help="OGhidra tool checkout (not vendored; clone it separately)")
    parser.add_argument("--repo-root", default=str(PRODUCT_ROOT),
                        help="product checkout the registry and chunks are read from")
    parser.add_argument("--python", default="",
                        help="interpreter to run the survey with "
                             "(default: OGhidra's .venv, else this interpreter)")
    parser.add_argument("--out", default=str(OUTPUT_PATH))
    parser.add_argument("--check", action="store_true",
                        help="re-derive and diff against the tracked artifact; "
                             "exit 1 on drift, write nothing")
    args = parser.parse_args()

    oghidra_root = Path(args.oghidra_root).resolve()
    repo_root = Path(args.repo_root).resolve()
    survey = oghidra_root / SURVEY_RELPATH
    if not survey.is_file():
        sys.stderr.write(
            f"OGhidra checkout not found: {survey}\n"
            "The survey lives in the OGhidra tool repository, which is not vendored "
            "into this repo. Clone it to research/tools/OGhidra or pass "
            "--oghidra-root / set OGHIDRA_ROOT.\n")
        return 2

    payload = build(oghidra_root, repo_root, args.python or default_python(oghidra_root))
    text = serialise(payload)
    out_path = Path(args.out)

    if args.check:
        if not out_path.is_file():
            sys.stderr.write(f"missing artifact: {out_path}\n")
            return 1
        old = json.loads(out_path.read_text(encoding="utf-8"))
        new = json.loads(text)
        for key in ("generated_utc", "survey_tool_commit"):
            old.pop(key, None)
            new.pop(key, None)
        if old != new:
            sys.stderr.write(
                f"{out_path.name} is STALE: the tree no longer produces these "
                "numbers. Re-run without --check and commit the result.\n")
            return 1
        print(f"{out_path.name}: up to date")
        return 0

    out_path.write_text(text, encoding="utf-8", newline="\n")
    fn = payload["per_function"]
    unit = payload["per_unit"]["full_export_coverage"]
    print(f"wrote {out_path}")
    print(f"  functions {payload['totals']['functions']}  "
          f"units {payload['totals']['units']}")
    print(f"  oracle_green      {fn['oracle_green']['count']:6d}  "
          f"{fn['oracle_green']['pct']:5.1f}%")
    print(f"  transcript_green  {fn['transcript_green']['count']:6d}  "
          f"{fn['transcript_green']['pct']:5.1f}%")
    print(f"  verifiable        {fn['verifiable_by_some_tier']['count']:6d}  "
          f"{fn['verifiable_by_some_tier']['pct']:5.1f}%")
    print(f"  unverifiable      {fn['unverifiable']['count']:6d}  "
          f"{fn['unverifiable']['pct']:5.1f}%  {fn['unverifiable']['reasons']}")
    print(f"  units w/ full export coverage {unit['count']}  {unit['pct']:5.1f}%")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
