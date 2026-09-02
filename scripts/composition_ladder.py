"""Composition-ladder rung runner (design G3 as amended by E1; V5 verdict).

Runs the SAME assembly-gate code path the live driver uses -- owner-derived
canonicalization (CanonicalizationRequest incl. sdk_seed_path + owner
snapshot) and the G2/H3 dispatch companion ENABLED -- but entirely in
SCRATCH, against COPIES of the staged artifacts and the canonical state.
It never takes the driver lock, never journals, never writes a byte into
the live pipeline tree.

Usage (from the OGhidra checkout's venv python):

    python scripts/composition_ladder.py init   --scratch <dir>
    python scripts/composition_ladder.py rung   --scratch <dir> --n 5  --tag rung0
    python scripts/composition_ladder.py rung   --scratch <dir> --n 10 --tag rung1
    python scripts/composition_ladder.py rung   --scratch <dir> --units a,b,... --tag rung1b

`init` snapshots research/decomp/port-units, research/decomp/
port-units-staging and wasm-units-state.json from the live checkout into
the scratch dir (stable-read: a torn copy of the state file under a running
driver re-reads until stat is unchanged). Every `rung` selects by the
gate's own recency/eligibility helper (select_recent_green_units, tiers
["oracle_green", "compile_only"], excluded units recorded) against the
COPIED state + artifacts, then runs run_assembly_gate with the driver's
link/smoke runners and the driver's own _canonicalization_request. The
full gate result is dumped to <scratch>/<tag>.json and folded into
<scratch>/assembly-gate.json via record_gate_result -- the same ledger
mechanics as live, pointed at scratch.

E1 budget bookkeeping (ratio computation across rungs) is done by the
`ledger` subcommand in this file, which writes the tracked rung ledger
research/decomp/data/composition-ladder.json from the per-rung dumps.
All timestamps in the ledger come from the gate results (checked_at),
never from a fresh clock.

The `frontier` subcommand re-scores that ledger under the spine-rooted
metric of docs/one-to-one-completion-spec.md section 6 (correction X1) and
rewrites it as schema `composition-ladder-2`.  It ADDS a `frontier` block
to every existing rung and a `frontier_lane` whose ring 0 is the spine
alone; it never recomputes a composition-ladder-1 field.  Two lanes, two
pass rules, both on the record:

  * recency lane -- windows from select_recent_green_units, growth by N
    doubling, E1 conflict-ratio budget.  UNCHANGED.
  * frontier lane -- ring 0 is `run_main_game_loop` alone with every
    callee bridged, a rung is a frontier prefix, growth is
    `bridged_calls_per_frame` falling.  E1 still applies, on whatever unit
    set the rung links.

The metric itself lives in scripts/spine_frontier.py; `frontier` imports it
and reads nothing but tracked corpus files plus the `select` output.
"""

from __future__ import annotations

import argparse
import json
import os
import shutil
import sys
from pathlib import Path

LIVE_REPO = Path(r"D:\GotYaForce")
OGHIDRA = LIVE_REPO / "research" / "tools" / "OGhidra"

sys.path.insert(0, str(OGHIDRA))

# The runner never publishes progress and never journals; belt-and-braces
# in case any transitively-constructed object honours these.
os.environ.setdefault("OGHIDRA_PROGRESS_DISABLE_PUSH", "1")
# G2/H3 dispatch companion: this lane runs with the companion ENABLED.
os.environ["OGHIDRA_PORT_DISPATCH_COMPANION"] = "1"


class _NullJournal:
    """Inert journal: the maintenance gate path never journals, but if any
    code path tries, it must not touch the port-progress branch from here."""

    def __getattr__(self, name):  # noqa: D105
        def _noop(*args, **kwargs):
            return None

        return _noop


def _stable_copy_file(source: Path, dest: Path, attempts: int = 5) -> None:
    """Copy a file that a live writer may be mutating: re-read until two
    stats around the read agree (same fail-closed idea as the gate's own
    load_canonical_state_snapshot)."""
    last = None
    for _ in range(attempts):
        before = source.stat()
        payload = source.read_bytes()
        after = source.stat()
        if (before.st_size, before.st_mtime_ns) == (after.st_size, after.st_mtime_ns):
            dest.parent.mkdir(parents=True, exist_ok=True)
            dest.write_bytes(payload)
            return
        last = "changed during read"
    raise RuntimeError(f"could not stable-copy {source}: {last}")


def cmd_init(scratch: Path) -> None:
    scratch.mkdir(parents=True, exist_ok=True)
    for rel in ("port-units", "port-units-staging"):
        src = LIVE_REPO / "research" / "decomp" / rel
        dst = scratch / rel
        if dst.exists():
            shutil.rmtree(dst)
        shutil.copytree(src, dst)
        print(f"copied {src} -> {dst}")
    state_src = (
        LIVE_REPO
        / "research/decomp/generated/finish-game-port/wasm-units-state.json"
    )
    _stable_copy_file(state_src, scratch / "wasm-units-state.json")
    print(f"copied {state_src} (stable read)")


def _build_driver(scratch: Path):
    from src.port_driver import DriverEvents
    from src.port_wasm_units import WasmUnitDriver

    driver = WasmUnitDriver(repo_root=LIVE_REPO, journal=_NullJournal())
    # Redirect every read-write seam into scratch. Reads that stay live are
    # read-only by construction: the emsdk toolchain, the pinned clang, the
    # oracle registry, and the SDK seed (run_root/gnt4_shim_seed.h).
    driver.artifact_root = scratch / "port-units"
    driver.staging_root = scratch / "port-units-staging"
    driver.state_path = scratch / "wasm-units-state.json"
    driver.assembly_ledger_path = scratch / "assembly-gate.json"
    driver.events = DriverEvents(scratch / "events.jsonl", driver.run_id)
    return driver


def cmd_select(scratch: Path) -> int:
    """Print the gate's own eligibility view of the scratch snapshot: the
    ordered eligible units (oldest first, the gate's stable link order) and
    every exclusion with its reason. Rung windows are the LAST n of this
    list -- the same recency rule run_assembly_gate_now applies."""
    from src.port_assembly_gate import (
        load_canonical_state_snapshot,
        select_recent_green_units,
    )

    driver = _build_driver(scratch)
    snapshot = load_canonical_state_snapshot(driver.state_path)
    interrupted = sorted(
        name
        for name, record in snapshot.units.items()
        if record.get("status") == "porting"
    )
    prior, excluded = select_recent_green_units(
        [driver.artifact_root, driver.staging_root],
        None,
        canonical_snapshot=snapshot,
        root_tiers=["oracle_green", "compile_only"],
    )
    print(
        json.dumps(
            {
                "canonical_state_sha256": snapshot.sha256,
                "in_flight_at_snapshot": interrupted,
                "eligible_oldest_first": [
                    {
                        "name": unit.name,
                        "tier": unit.tier,
                        "generated_at": unit.generated_at,
                    }
                    for unit in prior
                ],
                "excluded": excluded,
            },
            indent=2,
            default=str,
        )
    )
    return 0


def cmd_rung(scratch: Path, tag: str, n: int | None, units_csv: str | None) -> int:
    driver = _build_driver(scratch)
    workdir = scratch / f"workdir-{tag}"
    if units_csv is None:
        result = driver.run_assembly_gate_now(n, workdir=workdir)
    else:
        # Remediation form: an explicit unit list, same helpers, same gate.
        from src.port_assembly_gate import (
            load_canonical_state_snapshot,
            record_gate_result,
            run_assembly_gate,
            select_recent_green_units,
        )

        requested = [name for name in units_csv.split(",") if name]
        snapshot = load_canonical_state_snapshot(driver.state_path)
        prior, excluded = select_recent_green_units(
            [driver.artifact_root, driver.staging_root],
            None,
            canonical_snapshot=snapshot,
            root_tiers=["oracle_green", "compile_only"],
        )
        by_name = {unit.name: unit for unit in prior}
        missing = [name for name in requested if name not in by_name]
        if missing:
            print(f"REFUSED: not eligible under gate selection: {missing}")
            print(f"exclusion reasons: { {m: excluded.get(m) for m in missing} }")
            return 2
        # Keep the gate's own stable link order (oldest first), not the
        # order the operator typed.
        window = [unit for unit in prior if unit.name in set(requested)]
        selection_evidence = {
            "canonical_state_sha256": snapshot.sha256,
            "eligible": [unit.canonical for unit in window],
            "excluded": excluded,
            "explicit_units": requested,
        }
        result = run_assembly_gate(
            window,
            workdir,
            link_runner=driver._assembly_link_runner,
            smoke_runner=driver._assembly_smoke_runner,
            selection_evidence=selection_evidence,
            canonicalization=driver._canonicalization_request(window, workdir),
            dispatch_companion=True,
        )
        record_gate_result(driver.assembly_ledger_path, result)
    out = scratch / f"{tag}.json"
    out.write_text(
        json.dumps(result, indent=2, default=str), encoding="utf-8", newline="\n"
    )
    dispatch = result.get("dispatch") or {}
    print(
        json.dumps(
            {
                "tag": tag,
                "n": result.get("n"),
                "passed": result.get("passed"),
                "stage": result.get("stage"),
                "detail": (result.get("detail") or "")[:300],
                "conflicts": len(result.get("conflicts") or []),
                "companion_functions": dispatch.get("functions"),
                "result_file": str(out),
            },
            indent=2,
        )
    )
    return 0 if result.get("passed") else 1


def cmd_ledger(scratch: Path, rung_specs: list[str], out_path: Path) -> int:
    """Assemble the tracked rung ledger from per-rung gate dumps.

    rung_specs: TAG[:ATTEMPT_TAG,...] entries in rung order; the FIRST tag
    is the rung's accepted result, later tags are recorded attempts whose
    contested symbols count toward the rung's conflict cost (E1: a
    substitution's conflicts are the rung's conflicts).
    """
    rungs = []
    prev_functions = 0
    prev_ratio = None
    for index, spec in enumerate(rung_specs):
        parts = spec.split(":")
        accepted_tag = parts[0]
        attempt_tags = parts[1].split(",") if len(parts) > 1 and parts[1] else []
        accepted = json.loads((scratch / f"{accepted_tag}.json").read_text("utf-8"))
        attempts = [
            json.loads((scratch / f"{tag}.json").read_text("utf-8"))
            for tag in attempt_tags
        ]
        contested: dict[str, dict] = {}
        for res in [*attempts, accepted]:
            for conflict in res.get("conflicts") or []:
                symbol = conflict.get("symbol") or conflict.get("detail", "?")[:80]
                contested[symbol] = {
                    "symbol": conflict.get("symbol"),
                    "class": conflict.get("class"),
                    "units": conflict.get("units"),
                    "detail": str(conflict.get("detail") or "")[:400],
                }
        dispatch = accepted.get("dispatch") or {}
        functions = int(dispatch.get("functions") or 0)
        # Companion evidence check against the REAL linked module: ask the
        # emsdk-pinned node (the gate's own smoke tool) which gf_dispatch
        # exports/imports the composed wasm actually carries.
        wasm_path = scratch / f"workdir-{accepted_tag}" / "assembly.wasm"
        export_check: dict[str, bool | None] = {
            "dispatch_export_present": None,
            "arity_mismatch_export_present": None,
            "miss_import_present": None,
        }
        if wasm_path.is_file():
            import subprocess

            from src.port_assembly_gate import resolve_node_executable

            node = resolve_node_executable(LIVE_REPO)
            snippet = (
                "const fs=require('fs');"
                "const m=new WebAssembly.Module(fs.readFileSync(process.argv[1]));"
                "const ex=WebAssembly.Module.exports(m).map(e=>e.name);"
                "const im=WebAssembly.Module.imports(m).map(i=>i.name);"
                "console.log(JSON.stringify({ex,im}));"
            )
            probe = subprocess.run(
                [str(node), "-e", snippet, str(wasm_path)],
                capture_output=True,
                text=True,
                timeout=120,
            )
            if probe.returncode == 0:
                names = json.loads(probe.stdout)
                export_check = {
                    "dispatch_export_present": "__gf_dispatch" in names["ex"],
                    "arity_mismatch_export_present": (
                        "__gf_dispatch_arity_mismatches" in names["ex"]
                    ),
                    "miss_import_present": "__gf_dispatch_miss" in names["im"],
                }
        new_linked = functions - prev_functions
        new_contested = len(contested)
        ratio = (new_contested / new_linked) if new_linked > 0 else None
        budget_ok = True if prev_ratio is None else (
            ratio is not None and ratio <= prev_ratio
        )
        substitution = None
        if attempts:
            first = set(attempts[0].get("units") or [])
            final = set(accepted.get("units") or [])
            substitution = {
                "dropped": sorted(first - final),
                "substituted": sorted(final - first),
            }
        rungs.append(
            {
                "rung": index,
                "n": accepted.get("n"),
                "units": accepted.get("units"),
                "substitution": substitution,
                "passed": bool(accepted.get("passed")) and budget_ok,
                "link_passed": bool(accepted.get("passed")),
                "stage": accepted.get("stage"),
                "checked_at": accepted.get("checked_at"),
                "conflicts": sorted(
                    contested.values(), key=lambda c: str(c.get("symbol"))
                ),
                "new_contested_symbols": new_contested,
                "new_symbols_linked": new_linked,
                "ratio": ratio,
                "budget_ok": budget_ok,
                "attempt_tags": [*attempt_tags, accepted_tag],
                "companion": {
                    "functions": dispatch.get("functions"),
                    "table_size": len(dispatch.get("table") or []),
                    "companion_sha256": dispatch.get("companion_sha256"),
                    "dispatch_export": dispatch.get("dispatch_export"),
                    "miss_import": dispatch.get("miss_import"),
                    "arity_export": dispatch.get("arity_export"),
                    "frame_abi_version": dispatch.get("frame_abi_version"),
                    **export_check,
                },
            }
        )
        prev_functions = functions
        prev_ratio = ratio if ratio is not None else prev_ratio
    payload = {
        "schema": "composition-ladder-1",
        "design": "docs/playable-port-design.md G3 + E1 (V5 verdict)",
        "budget_rule": (
            "a rung passes iff its window links AND "
            "new_contested_symbols/new_symbols_linked <= previous rung ratio"
        ),
        "dispatch_companion": True,
        "rungs": rungs,
    }
    out_path.parent.mkdir(parents=True, exist_ok=True)
    out_path.write_text(
        json.dumps(payload, indent=2) + "\n", encoding="utf-8", newline="\n"
    )
    print(f"wrote {out_path} ({len(rungs)} rungs)")
    return 0


def cmd_frontier(repo: Path, ledger_path: Path, frontier_path: Path,
                 eligible_path: Path, out_path: Path) -> int:
    """Re-score the tracked rung ledger under the X1 frontier metric.

    Reads the schema `composition-ladder-1` ledger produced by `ledger`, adds
    the spine-rooted metric to every rung WITHOUT changing any existing field
    or any existing number, prepends the ring-0 rung of the frontier lane, and
    writes it back as schema `composition-ladder-2`.

    Two lanes, two rules, both recorded:

      recency lane (`rungs`)  -- unchanged.  Windows selected by
        `select_recent_green_units`, growth by N doubling, pass rule is E1:
        new_contested_symbols / new_symbols_linked <= previous rung ratio.
        The E1 budget keeps operating on exactly the unit set each rung links.

      frontier lane (`frontier_lane.rungs`) -- ring 0 is the spine alone, every
        callee bridged; a rung is a FRONTIER PREFIX (nested, so rung-to-rung
        comparison is valid); growth is `bridged_calls_per_frame` falling.
        E1 applies here too, on whatever unit set the rung links.

    Every rung in BOTH lanes gets a `frontier` block, so the recency lane's
    relationship to the ROM's frame loop is on the record rather than assumed.
    """
    import io as _io

    sys.path.insert(0, str(Path(__file__).resolve().parent))
    from spine_frontier import (
        SPINE_FUNCTION,
        bridged_calls_per_frame,
        build_call_graph,
        compute_frequency,
        load_spine_measurement,
    )

    graph = build_call_graph(repo)
    edges = graph["edges"]
    by_name = graph["by_name"]
    measured = load_spine_measurement(repo)["rates"]
    depth, freq, basis, rate, rate_basis = compute_frequency(edges, measured)
    members: dict = {}
    for name, fn in by_name.items():
        members.setdefault(fn["unit"], set()).add(name)

    ring0 = {SPINE_FUNCTION}
    baseline = bridged_calls_per_frame(edges, rate, ring0)

    frontier = json.loads(frontier_path.read_text("utf-8"))
    reachable_units = set(frontier["availability_summary"]["reachable_unit_names"])

    # Gate-eligibility evidence: the `select` subcommand's own output, run in
    # scratch against a copy of the canonical state.  This is what makes
    # "no frontier unit is linkable" a MEASUREMENT rather than an inference.
    eligibility = {
        "gate_eligible_units_on_frontier": None,
        "eligibility_evidence": None,
    }
    if eligible_path is not None and eligible_path.is_file():
        raw = eligible_path.read_text("utf-8")
        selection = json.loads(raw[raw.index("{"):])
        eligible = {u["name"] for u in selection["eligible_oldest_first"]}
        eligibility = {
            "gate_eligible_units_total": len(eligible),
            "gate_eligible_units_on_frontier": sorted(eligible & reachable_units),
            "eligibility_evidence": {
                "source": "scripts/composition_ladder.py select (scratch copy)",
                "canonical_state_sha256": selection["canonical_state_sha256"],
                "excluded_units": len(selection.get("excluded") or {}),
            },
        }

    def score(units, include_ring0):
        linked = set(ring0) if include_ring0 else set()
        for unit in units:
            linked |= members.get(unit, set())
        value = bridged_calls_per_frame(edges, rate, linked)
        touching = sorted(u for u in units if u in reachable_units)
        return {
            "metric": "bridged_calls_per_frame",
            "ring0_baseline": round(baseline, 4),
            "bridged_calls_per_frame": round(value, 4) if include_ring0 else None,
            "bridged_calls_per_frame_eliminated": (
                round(baseline - value, 4) if include_ring0 else 0.0
            ),
            "units_intersecting_spine_frontier": touching,
            "functions_linked_reachable_from_spine": sorted(
                f
                for unit in units
                for f in members.get(unit, set())
                if f in depth
            ),
            "reaches_run_main_game_loop": SPINE_FUNCTION in {
                f for unit in units for f in members.get(unit, set())
            },
            "basis": "measured ring-0 baseline (274 calls / 16 iterations); static delta",
        }

    ledger = json.loads(ledger_path.read_text("utf-8"))
    for rung in ledger.get("rungs", []):
        units = rung.get("units") or []
        block = score(units, include_ring0=False)
        block["note"] = (
            "recency-selected window; the spine is not in it, so this rung is "
            "not composed with ring 0 and B is undefined for it. "
            "bridged_calls_per_frame_eliminated is the fall it would cause if "
            "it WERE composed with ring 0."
        )
        rung["frontier"] = block

    ring0_rung = {
        "rung": "F0",
        "lane": "frontier",
        "n": 1,
        "units": [],
        "module": "research/decomp/spine-boundary/",
        "module_sha256": _sha256_file(
            repo / "research/decomp/spine-boundary/unit.wasm"
        ),
        "module_is_queue_unit": False,
        "queue_unit_for_spine": by_name[SPINE_FUNCTION]["unit"],
        "substitution": None,
        "passed": True,
        "link_passed": True,
        "stage": "pass",
        "checked_at": json.loads(
            (
                repo
                / "research/decomp/data/oracle-results/"
                  "spine-run-main-game-loop.boundary.json"
            ).read_text("utf-8")
        )["generated_at"],
        "conflicts": [],
        "new_contested_symbols": 0,
        "new_symbols_linked": 1,
        "ratio": 0.0,
        "budget_ok": True,
        "attempt_tags": ["spine-boundary"],
        "verdict": "boundary_green",
        "verdict_evidence": (
            "research/decomp/data/oracle-results/"
            "spine-run-main-game-loop.boundary.json (274/274 calls matched)"
        ),
        "frontier": score([], include_ring0=True),
    }

    ledger["schema"] = "composition-ladder-2"
    ledger["schema_note"] = (
        "v2 = v1 plus a `frontier` block on every rung and a `frontier_lane`. "
        "Every composition-ladder-1 field keeps its v1 meaning and its v1 value; "
        "no v1 number was recomputed."
    )
    ledger["metrics"] = {
        "e1_conflict_budget": {
            "rule": ledger.get("budget_rule"),
            "applies_to": "the unit set each rung actually links, in either lane",
            "status": "unchanged from composition-ladder-1",
        },
        "frontier_shrink": {
            "rule": (
                "a frontier rung passes iff its window links AND "
                "bridged_calls_per_frame falls relative to the previous "
                "frontier rung"
            ),
            "baseline": round(baseline, 4),
            "baseline_basis": "measured",
            "source": "research/decomp/data/spine-frontier.json",
            "caveat": (
                "B is not monotone under greedy unit addition: linking a loop "
                "callee replaces one crossing with that callee's own outbound "
                "calls.  Linking ALL of ring 1 takes B from 17 to 46 by the "
                "static bound.  B falling is a TERMINAL objective; per-rung "
                "scoring must use net = eliminated - exposed."
            ),
        },
    }
    ledger["frontier_lane"] = {
        "design": (
            "docs/one-to-one-completion-spec.md section 6, correction X1: ring 0 "
            "is the spine alone, everything it calls is bridged; a rung is a "
            "frontier prefix"
        ),
        "root": {
            "function": SPINE_FUNCTION,
            "gc_addr": "0x800527d8",
            "module": "research/decomp/spine-boundary/",
        },
        "ranking": "research/decomp/data/spine-frontier.json",
        "rungs": [ring0_rung],
        "blocked": {
            "reason": (
                "no unit on the spine frontier has ever been compiled, so no "
                "frontier rung above F0 can be linked"
            ),
            "frontier_units_reachable": len(reachable_units),
            "frontier_units_linkable_today": frontier["availability_summary"][
                "linkable_today"
            ],
            **eligibility,
        },
    }
    out_path.parent.mkdir(parents=True, exist_ok=True)
    with _io.open(str(out_path), "w", encoding="utf-8", newline="\n") as handle:
        handle.write(json.dumps(ledger, indent=2) + "\n")
    print(
        json.dumps(
            {
                "out": str(out_path),
                "schema": ledger["schema"],
                "recency_rungs": len(ledger.get("rungs", [])),
                "frontier_rungs": len(ledger["frontier_lane"]["rungs"]),
                "ring0_bridged_calls_per_frame": round(baseline, 4),
                "recency_rungs_eliminating_bridged_calls": [
                    r.get("rung")
                    for r in ledger.get("rungs", [])
                    if r["frontier"]["bridged_calls_per_frame_eliminated"]
                ],
            },
            indent=2,
        )
    )
    return 0


def _sha256_file(path: Path) -> str:
    import hashlib

    return hashlib.sha256(path.read_bytes()).hexdigest()



def main(argv: list[str] | None = None) -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    sub = parser.add_subparsers(dest="command", required=True)
    p_init = sub.add_parser("init")
    p_init.add_argument("--scratch", required=True)
    p_select = sub.add_parser("select")
    p_select.add_argument("--scratch", required=True)
    p_rung = sub.add_parser("rung")
    p_rung.add_argument("--scratch", required=True)
    p_rung.add_argument("--tag", required=True)
    p_rung.add_argument("--n", type=int, default=None)
    p_rung.add_argument("--units", default=None)
    p_ledger = sub.add_parser("ledger")
    p_ledger.add_argument("--scratch", required=True)
    p_ledger.add_argument("--rungs", required=True, help="TAG[:ATTEMPTS] csv")
    p_ledger.add_argument("--out", required=True)
    p_frontier = sub.add_parser("frontier")
    p_frontier.add_argument(
        "--ledger",
        default=str(LIVE_REPO / "research/decomp/data/composition-ladder.json"),
    )
    p_frontier.add_argument(
        "--frontier",
        default=str(LIVE_REPO / "research/decomp/data/spine-frontier.json"),
    )
    p_frontier.add_argument(
        "--repo",
        default=str(Path(__file__).resolve().parent.parent),
        help="checkout to read the tracked corpus/registry/capture from",
    )
    p_frontier.add_argument(
        "--eligible",
        default=None,
        help="output of `composition_ladder.py select` (gate eligibility evidence)",
    )
    p_frontier.add_argument("--out", required=True)
    args = parser.parse_args(argv)
    if args.command == "frontier":
        return cmd_frontier(
            Path(args.repo).resolve(),
            Path(args.ledger).resolve(),
            Path(args.frontier).resolve(),
            Path(args.eligible).resolve() if args.eligible else None,
            Path(args.out).resolve(),
        )
    scratch = Path(args.scratch).resolve()
    if args.command == "init":
        cmd_init(scratch)
        return 0
    if args.command == "select":
        return cmd_select(scratch)
    if args.command == "rung":
        return cmd_rung(scratch, args.tag, args.n, args.units)
    if args.command == "ledger":
        return cmd_ledger(scratch, args.rungs.split(";"), Path(args.out).resolve())
    return 2


if __name__ == "__main__":
    raise SystemExit(main())
