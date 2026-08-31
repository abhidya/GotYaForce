#!/usr/bin/env python3
"""transcript_sweep.py -- batched transcript_green capture across a scenario.

WHY THIS EXISTS (measured 2026-08-31)
-------------------------------------
`capture_transcript.py capture` records ONE function per emulator boot, and the
stub allows exactly one client per boot (rsp_client.py docstring). Sweeping the
485 capturable exports of the 103 staged units one at a time therefore costs one
Dolphin launch each -- and for the 32 roster-reload scenarios a further ~45 s of
`setup` per launch, because the roster reload is re-derived on every boot (the
rig cannot write a savestate; see the README).

Two measured facts make the naive loop worse than slow, and this tool exists to
handle both rather than to hide them:

1. **Most staged exports never fire.**  Scouted 2026-08-31 on the base 2v2
   savestate with 33 export breakpoints installed: 5 of 33 fired at all, and 3
   of those 5 are not capturable.  Spending a boot on a function that never
   executes is the single largest waste in the sweep, so this tool SCOUTS first
   -- one boot, entry breakpoints on every capturable export of every unit the
   scenario gates, hit counts recorded -- and only then spends boots on the
   functions that actually ran.

2. **The stub connection dies mid-session.**  Reproduced 2026-08-31 on both the
   base scenario (no `setup` block) and a roster scenario, with and without pad
   injection: after 30-270 s the stub closes the TCP connection
   (`WinError 10054`) while Dolphin.exe itself keeps running.  It is not the
   roster reload and it is not the injector -- a pad-injection-only session ran
   937 stops over 300 s cleanly, while a no-breakpoint session that only polled
   memory died at 268 s.  The cause is in Dolphin's stub, not in this tooling,
   and the only reliable remedy available here is to treat a boot as a
   short-lived resource: budget each one, detect the drop, relaunch, continue.
   Every phase below is therefore restartable and reports how many boots it
   consumed.

Nothing here changes what a capture MEANS.  Phase 2 shells out to
`capture_transcript.py capture` -- the sanctioned tool -- so the corpus, its
header, its provenance and its vacuity guard are produced by exactly the code
that produced the committed corpora.  This file only decides WHICH function to
spend the next boot on, and restarts the emulator when the stub drops.

Python only (owner rule); pure stdlib.
"""
from __future__ import annotations

import argparse
import collections
import json
import subprocess
import sys
import time
from pathlib import Path

HERE = Path(__file__).resolve().parent
sys.path.insert(0, str(HERE))

import capture_oracle as co          # noqa: E402
import capture_transcript as ct      # noqa: E402
from rsp_client import RspError      # noqa: E402

REPO_ROOT = HERE.parent.parent.parent
PLANS = HERE / "plans"


# --------------------------------------------------------------------- boots

def launch(scenario: str, wait: float = 90.0, tries: int = 3) -> bool:
    """Boot our own headless Dolphin for one stub session.

    Retried, because a boot whose stub never comes up is indistinguishable at
    the caller from a boot that came up and died -- and only the first is worth
    retrying immediately.
    """
    for _ in range(tries):
        stop()
        time.sleep(1.0)
        done = subprocess.run(
            [sys.executable, str(HERE / "capture_oracle.py"), "launch",
             "--scenario", scenario, "--wait", str(wait)],
            capture_output=True, text=True, timeout=300)
        if "listening" in (done.stdout or ""):
            return True
        print(f"[launch] stub did not come up: {(done.stdout or '')[-200:]}",
              flush=True)
    return False


def stop() -> None:
    """Stop the tracked instance, then reap ORPHANS.

    `capture_oracle.py stop` kills only what its pid file tracks. A boot whose
    stub died is not stopped by anything (Dolphin.exe keeps running headless),
    and it keeps port 55555 bound -- so the NEXT launch silently fails to bind
    and the next attach lands on the previous, wrongly-staged instance. Two such
    orphans were found alive during the 2026-08-31 sweep. A sweep that reboots
    dozens of times cannot leave that to chance, so it reaps every Dolphin.exe
    it can see. Safe here because this tool owns the only Dolphin on the rig
    (the port driver never launches one; design GPU-contention rule).
    """
    subprocess.run(
        [sys.executable, str(HERE / "capture_oracle.py"), "stop"],
        capture_output=True, text=True, timeout=120)
    try:
        subprocess.run(["taskkill", "/IM", "Dolphin.exe", "/F"],
                       capture_output=True, text=True, timeout=60)
    except (OSError, subprocess.SubprocessError):
        pass


# --------------------------------------------------------------------- scout

def plan_targets(units: list[str]) -> dict[int, dict]:
    """entry address -> {unit, fn, plan, capturable} for every plan on disk."""
    out: dict[int, dict] = {}
    for unit in units:
        for path in sorted(PLANS.glob(f"{unit}.*.transcript.json")):
            try:
                plan = json.loads(path.read_text(encoding="utf-8"))
            except (OSError, json.JSONDecodeError):
                continue
            if plan.get("transcript_plan_schema") != ct.TRANSCRIPT_SCHEMA:
                continue
            out[int(plan["fn"]["gc_addr"], 16)] = {
                "unit": plan["unit"], "fn": plan["fn"]["name"],
                "plan": str(path), "capturable": bool(plan.get("capturable")),
                "call_sites": len(plan.get("call_sites") or []),
                "returns_value": plan["fn"]["ret"] is not None,
            }
    return out


def scout_once(scenario: dict, targets: dict[int, dict],
               seconds: float, port: int) -> tuple[collections.Counter, float, str]:
    """One boot's worth of scouting. Returns (hits, live_seconds, how_it_ended)."""
    d = co.StubDriver(port)
    hits: collections.Counter = collections.Counter()
    t0 = time.monotonic()
    ended = "budget"
    ready = False
    try:
        d.halt()
        if scenario.get("setup"):
            co.apply_scenario_setup(scenario, d)
        ready = True
        t0 = time.monotonic()                    # bill only post-setup time
        injector = ct.parse_inject_arg(scenario.get("inject"))
        if injector is not None:
            d.set_bp(ct.PAD_INJECT_BP)
        for addr in targets:
            d.set_bp(addr)
        while time.monotonic() - t0 < seconds:
            stop_pkt = d.cont_until_stop(timeout=20.0)
            if stop_pkt is None:
                ended = "stop_timeout"
                break
            pc = co.stop_pc(stop_pkt) or d.rsp.read_pc()
            if injector is not None and pc == ct.PAD_INJECT_BP:
                injector.on_hit(d.rsp)
                continue
            hits[pc] += 1
    except Exception as error:                   # noqa: BLE001 - a boot that
        # dies (stub drop, StageError, socket error) costs the boot and nothing
        # else: the scout is restartable by construction.
        ended = ("stub_died" if not ready else "stub_died_live") + \
            f": {type(error).__name__}"
    finally:
        try:
            d.cleanup()
        except Exception:                        # noqa: BLE001 - best effort
            pass
    # Setup time is not scouting time: a boot that never reached the live
    # battle contributed zero observation, and billing it would silently
    # shrink the budget the caller asked for.
    return hits, (time.monotonic() - t0) if ready else 0.0, ended


def cmd_scout(a: argparse.Namespace) -> int:
    scenario = ct.load_scenario(a.scenario)
    units = [u for u in a.units.split(",") if u]
    targets = plan_targets(units)
    if not targets:
        sys.exit(f"no transcript plans on disk for {units}")
    hits: collections.Counter = collections.Counter()
    boots: list[dict] = []
    live = 0.0
    while live < a.seconds and len(boots) < a.max_boots:
        if not launch(a.scenario):
            boots.append({"seconds": 0.0, "ended": "launch_failed", "fired": 0})
            break
        try:
            got, secs, ended = scout_once(
                scenario, targets, a.seconds - live, a.port)
        except (RspError, OSError) as error:
            got, secs, ended = collections.Counter(), 0.0, f"attach_failed: {error}"
        hits.update(got)
        live += secs
        boots.append({"seconds": round(secs, 1), "ended": ended,
                      "fired": len(got)})
        print(f"[scout] boot {len(boots)}: {secs:.0f}s {ended} "
              f"{sum(got.values())} hits on {len(got)} targets", flush=True)
        if ended == "budget":
            break
    stop()
    rows = []
    for addr, meta in sorted(targets.items()):
        rows.append(dict(meta, addr=f"0x{addr:08x}", hits=hits[addr],
                         rate=round(hits[addr] / max(live, 1.0), 3)))
    report = {
        "kind": "transcript_scout", "scenario": a.scenario, "units": units,
        "live_seconds": round(live, 1), "boots": boots,
        "targets": len(targets),
        "fired": sum(1 for r in rows if r["hits"]),
        "fired_and_capturable": sum(1 for r in rows if r["hits"] and r["capturable"]),
        "rows": sorted(rows, key=lambda r: -r["hits"]),
    }
    Path(a.out).parent.mkdir(parents=True, exist_ok=True)
    Path(a.out).write_text(json.dumps(report, indent=1) + "\n", encoding="utf-8")
    print(json.dumps({k: v for k, v in report.items() if k != "rows"}, indent=1))
    for r in report["rows"]:
        if r["hits"]:
            print(f"  {r['unit']:18} {r['fn']:16} {r['addr']} "
                  f"hits={r['hits']:5} rate={r['rate']}/s "
                  f"{'CAPTURABLE' if r['capturable'] else 'refused'}")
    return 0


# ------------------------------------------------------------------- capture

def capture_once(plan: str, scenario: str, n: int, out: Path, unit: str,
                 max_seconds: float, port: int) -> dict:
    """One boot, one `capture_transcript.py capture`. Never raises.

    ``--wasm-rel``/``--arena-rel`` are passed explicitly: the header records the
    module path RELATIVE TO THE CAPTURE FILE and the tool's default still holds
    the literal placeholder ``UNIT``, so a corpus written without them replays
    against a path that does not exist.
    """
    launch(scenario)
    proc = subprocess.run(
        [sys.executable, str(HERE / "capture_transcript.py"), "capture",
         "--plan", plan, "--n", str(n), "--scenario", scenario,
         "--max-seconds", str(max_seconds), "--port", str(port),
         "--wasm-rel", f"../../port-units-staging/{unit}/unit.wasm",
         "--arena-rel", "../../oracle-harness/arena-trace-empty.json",
         "--out", str(out)],
        capture_output=True, text=True, timeout=max_seconds + 400)
    tail = (proc.stdout or "").strip().splitlines()
    payload = {}
    for start in range(len(tail)):
        try:
            payload = json.loads("\n".join(tail[start:]))
            break
        except json.JSONDecodeError:
            continue
    payload.setdefault("cases", 0)
    payload["rc"] = proc.returncode
    if proc.returncode != 0 and not payload.get("notes"):
        payload["notes"] = [(proc.stderr or "")[-300:]]
    return payload


def cmd_capture(a: argparse.Namespace) -> int:
    scout = json.loads(Path(a.scout).read_text(encoding="utf-8"))
    # Re-read each plan rather than trusting the scout's copy of `capturable`:
    # plans are regenerated whenever the binder learns a new callee shape, and a
    # scout recorded before that would permanently hide the newly reachable
    # exports it already proved were firing.
    rows = []
    skipped: list[dict] = []
    for row in scout["rows"]:
        if not row["hits"]:
            continue
        try:
            plan = json.loads(Path(row["plan"]).read_text(encoding="utf-8"))
        except (OSError, json.JSONDecodeError):
            continue
        if not plan.get("capturable"):
            continue
        # A target the scout measured at, say, 0.007 hits/s cannot produce
        # --min-cases within --max-seconds no matter how many boots are spent on
        # it; attempting it burns a full launch (and a roster reload) to record
        # zero cases. Skipped explicitly and counted, never silently.
        if row["rate"] * a.max_seconds < a.min_cases:
            skipped.append({"unit": row["unit"], "fn": row["fn"],
                            "rate": row["rate"],
                            "why": "measured rate cannot reach --min-cases "
                                   "within --max-seconds"})
            continue
        rows.append(dict(row, capturable=True,
                         call_sites=len(plan.get("call_sites") or [])))
    rows.sort(key=lambda r: -r["hits"])
    if a.limit:
        rows = rows[:a.limit]
    out_dir = Path(a.out_dir)
    out_dir.mkdir(parents=True, exist_ok=True)
    results = []
    for row in rows:
        out = out_dir / f"{row['unit']}.{row['fn']}.transcript.jsonl"
        best: dict = {"cases": 0}
        for attempt in range(a.attempts):
            got = capture_once(row["plan"], scout["scenario"], a.n, out,
                               row["unit"], a.max_seconds, a.port)
            print(f"[capture] {row['unit']}.{row['fn']} attempt {attempt + 1}: "
                  f"cases={got.get('cases')} calls={got.get('calls')} "
                  f"notes={got.get('notes')}", flush=True)
            if got.get("cases", 0) > best["cases"]:
                best = got
            if got.get("cases", 0) >= a.min_cases:
                break
        results.append({"unit": row["unit"], "fn": row["fn"],
                        "hits": row["hits"], "cases": best.get("cases", 0),
                        "calls": best.get("calls"), "out": str(out),
                        "notes": best.get("notes")})
    stop()
    Path(a.report).write_text(
        json.dumps({"kind": "transcript_capture_sweep",
                    "scenario": scout["scenario"], "results": results},
                   indent=1) + "\n", encoding="utf-8")
    print(json.dumps({"captured": sum(1 for r in results if r["cases"]),
                      "attempted": len(results),
                      "skipped_too_rare": len(skipped)}, indent=1))
    return 0


def main() -> int:
    p = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    sub = p.add_subparsers(dest="cmd", required=True)

    s = sub.add_parser("scout", help="which staged exports actually FIRE here")
    s.add_argument("--scenario", required=True)
    s.add_argument("--units", required=True, help="comma-separated unit names")
    s.add_argument("--seconds", type=float, default=180.0,
                   help="total LIVE (post-setup) seconds to accumulate")
    s.add_argument("--max-boots", type=int, default=6)
    s.add_argument("--port", type=int, default=55555)
    s.add_argument("--out", required=True)
    s.set_defaults(func=cmd_scout)

    c = sub.add_parser("capture", help="spend boots on the functions that fired")
    c.add_argument("--scout", required=True, help="a scout report")
    c.add_argument("--out-dir", required=True)
    c.add_argument("--report", required=True)
    c.add_argument("--n", type=int, default=24)
    c.add_argument("--min-cases", type=int, default=8)
    c.add_argument("--attempts", type=int, default=2)
    c.add_argument("--max-seconds", type=float, default=120.0)
    c.add_argument("--limit", type=int, default=0)
    c.add_argument("--port", type=int, default=55555)
    c.set_defaults(func=cmd_capture)

    a = p.parse_args()
    return a.func(a)


if __name__ == "__main__":
    raise SystemExit(main())
