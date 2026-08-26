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
    args = parser.parse_args(argv)
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
