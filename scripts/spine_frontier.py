"""Spine-rooted frontier model (docs/one-to-one-completion-spec.md §6, correction X1).

WHAT THIS REPLACES
------------------
The composition ladder selected windows by RECENCY (`select_recent_green_units`,
last-N eligible units, oldest-first link order) and grew by DOUBLING N.  Neither
the selection nor the growth rule has any relation to `run_main_game_loop`, so no
number of doublings reaches the ROM's frame loop -- which the design's H2 gate (a)
makes a hard prerequisite of control inversion.

X1 replaced that with a FRONTIER MODEL:

  * ring 0 is the spine ALONE; every function it calls is BRIDGED, not linked;
  * the frontier is a COMPILE RANKING, not a linking ladder;
  * growth is measured by BRIDGED CALLS PER FRAME FALLING, not by unit count.

THE METRIC
----------
A *frame* is one iteration of the spine's `do { ... } while(true)` body
(`research/decomp/ghidra-export/chunk_0006.c:5790-5833`).

    B(L) = SUM over edges (f -> g) with f in L, g not in L, of rate(f -> g)

where L is the set of ROM functions linked into the composed module and
rate(f -> g) is that edge's calls per frame.  B(L) is exactly what
`packages/rom-runtime/src/ledger.ts` counts at runtime:
`BridgeLedger.recordCall` fires once per worker->main crossing and
`LedgerFrameSnapshot.bridgedCallCount` is B(L) for that frame.  This tool
predicts that number statically so the compile queue can be ordered before the
module exists.

For a candidate unit U added to L:

    eliminated(U) = SUM_{f in L, g in U} rate(f -> g)     # stop crossing
    exposed(U)    = SUM_{g in U, h not in L|U} rate(g -> h)   # start crossing
    net(U)        = eliminated(U) - exposed(U)            # the fall in B

net is the honest ranking key.  It is NOT "calls eliminated": linking a
function also publishes that function's own outbound calls to the bridge, and a
unit whose functions call more than they are called is a net LOSS.  A ranking
that reported only elimination would put such units at the top.  Both columns
are emitted for every row.

MEASUREMENT BASIS
-----------------
Every row carries a `basis`:

  measured        -- from a real capture.  The rate of every edge out of the
                     spine comes from the BOUNDARY_GREEN corpus
                     `research/decomp/oracle-harness/corpora/
                      spine-run-main-game-loop.boundary.jsonl`
                     (274 calls / 16 loop iterations, verdict pass,
                      `research/decomp/data/oracle-results/
                       spine-run-main-game-loop.boundary.json`):
                     17 loop edges at 1.0/frame, 2 prologue edges at 0.0/frame.
                     A live `window.__gf.bridgeLedger()` snapshot passed with
                     --ledger extends this to any gc_addr it covers.
  static          -- static call-site counts, scanned from the chunk corpus,
                     with freq propagated multiplicatively.  Assumes every call
                     site in a function's body executes once per invocation of
                     that function: it OVER-counts guarded calls and UNDER-counts
                     calls inside inner loops.

Unit rows split inbound into `inbound_measured_calls_per_frame` and
`inbound_static_calls_per_frame` so a row's evidence is never averaged away.

The call graph is scanned from `research/decomp/ghidra-export/chunk_*.c` over the
line ranges pinned in `research/decomp/data/oracle-registry.json`, NOT from the
registry's `external_callees` lists.  The registry lists are distinct-callee sets
(no call-site counts) and they DROP edges to renamed functions -- the spine's own
call to `dispatch_global_menu_mode` is missing from its `external_callees`, which
is the single most load-bearing edge in the whole graph.  The scan recovers it,
and cross-checks itself against the registry (both deltas are reported).

SDK/shim callees (`gnt4-*`, the registry's 996 `sdk_prefix` exclusions) are not
bridged -- they are satisfied by the shim seed at link time -- so they are not
call graph nodes and never count toward B.

NOTHING HERE COMPILES, LINKS, OR TOUCHES LIVE PIPELINE STATE.  It reads the
tracked corpus, the tracked registry, the tracked capture, and (read-only) the
unit state file for availability.  No driver lock, no model server, no GPU.
"""

from __future__ import annotations

import argparse
import collections
import io
import json
import re
import sys
from pathlib import Path

SPINE_FUNCTION = "zz_00527d8_"
SPINE_ADDR = "0x800527d8"
SPINE_CORPUS = (
    "research/decomp/oracle-harness/corpora/spine-run-main-game-loop.boundary.jsonl"
)
SPINE_RESULT = (
    "research/decomp/data/oracle-results/spine-run-main-game-loop.boundary.json"
)
REGISTRY = "research/decomp/data/oracle-registry.json"

# Depth cap for multiplicative frequency propagation.  Past this depth the
# estimate is dominated by accumulated call-site product error and is not
# reported as a frequency.
MAX_DEPTH = 6

_COMMENT = re.compile(r"/\*.*?\*/|//[^\r\n]*", re.S)
_STRING = re.compile(r"\"(?:\\.|[^\"\\])*\"|'(?:\\.|[^'\\])*'")
_CALLSITE = re.compile(r"\b([A-Za-z_][A-Za-z0-9_]*)\s*\(")


# ---------------------------------------------------------------- call graph


def build_call_graph(repo: Path) -> dict:
    """Scan the chunk corpus for call sites, one function body at a time.

    Returns {"edges": {caller: {callee: callsites}}, "functions": {...},
             "cross_check": {...}}.
    """
    registry = json.loads((repo / REGISTRY).read_text(encoding="utf-8"))
    functions = registry["functions"]
    names = {f["name"] for f in functions}
    by_name = {f["name"]: f for f in functions}

    chunk_cache: dict[str, list[str]] = {}

    def lines(rel: str) -> list[str]:
        if rel not in chunk_cache:
            chunk_cache[rel] = (
                (repo / rel).read_text(encoding="utf-8", errors="replace").split("\n")
            )
        return chunk_cache[rel]

    edges: dict[str, dict[str, int]] = {}
    unresolved: collections.Counter = collections.Counter()
    for fn in functions:
        start, end = fn["line_range"]
        body = "\n".join(lines(fn["chunk_file"])[start - 1 : end])
        body = _STRING.sub('""', _COMMENT.sub(" ", body))
        brace = body.find("{")
        if brace >= 0:
            body = body[brace:]
        out: dict[str, int] = {}
        for match in _CALLSITE.finditer(body):
            target = match.group(1)
            if target in names:
                out[target] = out.get(target, 0) + 1
            else:
                unresolved[target] += 1
        if out:
            edges[fn["name"]] = out

    # Cross-check against the registry's own (count-less, rename-blind) lists.
    registry_only = 0
    scan_only = 0
    registry_only_examples: list[str] = []
    for fn in functions:
        listed = set(fn["external_callees"]["list"])
        scanned = set(edges.get(fn["name"], {}))
        for miss in sorted(listed - scanned):
            registry_only += 1
            if len(registry_only_examples) < 10:
                registry_only_examples.append(f"{fn['name']} -> {miss}")
        scan_only += len(scanned - listed)

    return {
        "edges": edges,
        "by_name": by_name,
        "cross_check": {
            "registry_only_edges": registry_only,
            "registry_only_examples": registry_only_examples,
            "scan_only_edges": scan_only,
            "note": (
                "scan_only edges are overwhelmingly calls to RENAMED functions, "
                "which the registry's external_callees never lists; "
                "registry_only edges are call sites the text scan could not see "
                "(function-pointer or macro forms)"
            ),
            "unresolved_call_identifiers_distinct": len(unresolved),
            "unresolved_top": unresolved.most_common(12),
        },
    }


# ------------------------------------------------------------- measurement


def load_spine_measurement(repo: Path) -> dict:
    """Per-frame call rates for the spine's direct callees, from the
    BOUNDARY_GREEN capture.  This is the only per-frame measurement that
    exists in the repository."""
    path = repo / SPINE_CORPUS
    header = None
    per_iter: dict[str, collections.Counter] = collections.defaultdict(
        collections.Counter
    )
    for line in path.read_text(encoding="utf-8").splitlines():
        if not line.strip():
            continue
        rec = json.loads(line)
        if rec.get("kind") == "header":
            header = rec
        elif rec.get("kind") == "call":
            per_iter[rec["callee"]][rec["iter"]] += 1
    iterations = int(header["iterations"])
    rates: dict[str, dict] = {}
    for callee, counter in per_iter.items():
        total = sum(counter.values())
        iters_present = len(counter)
        # A callee seen in exactly one iteration (the first) is the spine's
        # PROLOGUE, executed before the do/while: one-time init, not per-frame.
        one_time = iters_present == 1 and 0 in counter
        rates[callee] = {
            "calls_total": total,
            "iterations_present": iters_present,
            "iterations": iterations,
            "per_frame": 0.0 if one_time else total / float(iterations),
            "one_time": one_time,
            "basis": "measured",
            "source": SPINE_CORPUS,
        }
    result = json.loads((repo / SPINE_RESULT).read_text(encoding="utf-8"))
    return {
        "rates": rates,
        "iterations": iterations,
        "capture": header.get("counts"),
        "verdict": result.get("verdict"),
        "calls_matched": result.get("calls_matched"),
        "corpus_sha256": result.get("capture", {}).get("sha256"),
    }


def load_live_ledger(path: Path, by_addr: dict[str, str]) -> dict:
    """Fold a real `window.__gf.bridgeLedger()` snapshot into the measurement
    set.  Live measurement always wins over the capture and over the estimate.

    Accepts the LedgerSnapshot shape from packages/rom-runtime/src/ledger.ts.
    Frame 0 and any frame whose mode is not yet "dtm-replay" are skipped: the
    ledger's own R2 rule says a frame with no crossing is "linked-only", and a
    partial first frame would understate the rate.
    """
    snap = json.loads(path.read_text(encoding="utf-8"))
    frames = [f for f in snap.get("frames", []) if f.get("frame", 0) > 0]
    if not frames:
        return {}
    totals: collections.Counter = collections.Counter()
    for frame in frames:
        for call in frame.get("calls", []):
            totals[call["gcAddr"].lower().lstrip("0x").rjust(8, "0")] += int(
                call["count"]
            )
    out: dict[str, dict] = {}
    for addr, count in totals.items():
        name = by_addr.get("0x" + addr)
        if name is None:
            continue
        out[name] = {
            "calls_total": count,
            "iterations": len(frames),
            "per_frame": count / float(len(frames)),
            "one_time": False,
            "basis": "measured",
            "source": str(path),
        }
    return out


# ---------------------------------------------------------------- frequency


def compute_frequency(edges, measured, root=SPINE_FUNCTION):
    """Per-frame EDGE rates and per-frame function invocation rates.

    The unit of the metric is the EDGE, not the function: `BridgeLedger`
    counts one record per crossing, so a caller that calls the same callee
    three times a frame contributes three.

        rate(f -> g) = MEASURED per-frame count where a capture covers it,
                       else freq(f) * callsites(f -> g)          [static]
        freq(g)      = SUM over depth-increasing callers f of rate(f -> g)

    Measured edge rates are attributed by CALLEE, because that is what the
    capture and the runtime ledger both key on (`gcAddr`).  For the spine's
    19 direct callees the capture gives 17 edges at 1.0/frame and 2 prologue
    edges at 0.0/frame -- so B(ring 0) is 17.0, MEASURED, not the 19 a naive
    static call-site count would report.

    freq flows only along DEPTH-INCREASING edges: back edges and cross edges
    are real calls (and are counted in B and in exposure) but propagating
    freq along them would not terminate.
    """
    depth = {root: 0}
    order = [root]
    queue = collections.deque([root])
    while queue:
        node = queue.popleft()
        if depth[node] >= MAX_DEPTH:
            continue
        for callee in edges.get(node, {}):
            if callee not in depth:
                depth[callee] = depth[node] + 1
                order.append(callee)
                queue.append(callee)

    freq = {root: 1.0}
    basis = {root: "measured (frame definition: one loop iteration)"}
    rate: dict = {}
    rate_basis: dict = {}
    for node in order:
        node_freq = freq.get(node, 0.0)
        basis.setdefault(node, "static(depth=%d)" % depth[node])
        for callee, count in edges.get(node, {}).items():
            if node == root and callee in measured:
                edge_rate = measured[callee]["per_frame"]
                edge_basis = "measured"
            else:
                edge_rate = node_freq * count
                edge_basis = "static"
            rate[(node, callee)] = edge_rate
            rate_basis[(node, callee)] = edge_basis
            if depth.get(callee, -1) == depth[node] + 1:
                freq[callee] = freq.get(callee, 0.0) + edge_rate
                if edge_basis == "measured":
                    basis[callee] = "measured"
    return depth, freq, basis, rate, rate_basis


# ------------------------------------------------------------------ ranking


def bridged_calls_per_frame(edges, rate, linked) -> float:
    """B(L): the number `LedgerFrameSnapshot.bridgedCallCount` would report."""
    total = 0.0
    for caller in linked:
        for callee in edges.get(caller, {}):
            if callee not in linked:
                total += rate.get((caller, callee), 0.0)
    return total


def score_unit(edges, rate, linked, member_set):
    """Marginal effect of linking `member_set` on top of `linked`.

    eliminated: edges from ALREADY-LINKED code into the unit that stop crossing.
    exposed:    edges out of the newly linked code that start crossing.
    """
    eliminated = 0.0
    for caller in linked:
        for callee in edges.get(caller, {}):
            if callee in member_set:
                eliminated += rate.get((caller, callee), 0.0)
    exposed = 0.0
    for member in member_set:
        for callee in edges.get(member, {}):
            if callee not in linked and callee not in member_set:
                exposed += rate.get((member, callee), 0.0)
    return eliminated, exposed


def frontier_hotness(edges, rate, rate_basis, depth, member_set):
    """Unit hotness over the WHOLE spine-reachable frontier.

    inbound  = per-frame calls into this unit from any spine-reachable caller
               outside it.  This is the number of bridged calls linking the
               unit eliminates ONCE ITS CALLERS ARE LINKED, which is the
               compile-priority question (ring-1 units answer it exactly,
               because their only reachable caller is the spine itself).
    outbound = per-frame calls this unit makes to functions outside it.
    """
    inbound = 0.0
    inbound_measured = 0.0
    callers = set()
    for (caller, callee), value in rate.items():
        if callee in member_set and caller not in member_set and caller in depth:
            inbound += value
            if rate_basis.get((caller, callee)) == "measured":
                inbound_measured += value
            if value > 0.0:
                callers.add(caller)
    outbound = 0.0
    for member in member_set:
        if member not in depth:
            continue
        for callee in edges.get(member, {}):
            if callee not in member_set:
                outbound += rate.get((member, callee), 0.0)
    return inbound, inbound_measured, outbound, callers


def unit_availability(state_units: dict, unit: str) -> dict:
    record = state_units.get(unit) or {}
    status = record.get("status")
    tier = record.get("tier")
    return {
        "status": status,
        "tier": tier,
        "attempts": record.get("attempts"),
        # The gate links only units the driver has produced an artifact for and
        # whose tier is one of the assembly gate's root_tiers.
        "linkable_today": bool(
            status == "green" and tier in ("oracle_green", "compile_only")
        ),
    }


def cmd_rank(args) -> int:
    repo = Path(args.repo).resolve()
    graph = build_call_graph(repo)
    edges = graph["edges"]
    by_name = graph["by_name"]
    by_addr = {f["address"].lower(): f["name"] for f in by_name.values()}

    spine_meas = load_spine_measurement(repo)
    measured = dict(spine_meas["rates"])
    live = {}
    if args.ledger:
        live = load_live_ledger(Path(args.ledger), by_addr)
        measured.update(live)

    depth, freq, basis, rate, rate_basis = compute_frequency(edges, measured)

    state_units = {}
    if args.state:
        state_units = json.loads(
            Path(args.state).read_text(encoding="utf-8")
        ).get("units", {})

    members = collections.defaultdict(set)
    for name, fn in by_name.items():
        members[fn["unit"]].add(name)

    # ---- ring 0: the spine alone; every callee bridged ----------------------
    ring0 = {SPINE_FUNCTION}
    baseline = bridged_calls_per_frame(edges, rate, ring0)

    reachable_units = sorted(
        {by_name[f]["unit"] for f in depth if f in by_name}
    )

    def function_rows(unit):
        rows = []
        for f in sorted(members[unit]):
            if f not in depth:
                continue
            rows.append(
                {
                    "name": f,
                    "addr": by_name[f]["address"],
                    "depth": depth[f],
                    "freq_per_frame": round(freq.get(f, 0.0), 4),
                    "freq_basis": basis.get(f, "static"),
                    "outbound_callsites_static": sum(edges.get(f, {}).values()),
                }
            )
        rows.sort(key=lambda r: -r["freq_per_frame"])
        return rows

    # ---- ranking A: frontier hotness over the whole reachable graph ---------
    hotness = []
    for unit in reachable_units:
        member_set = members[unit]
        inbound, inbound_measured, outbound, callers = frontier_hotness(
            edges, rate, rate_basis, depth, member_set
        )
        if inbound <= 0.0:
            continue
        caller_bases = {
            rate_basis.get((c, g), "static")
            for c in callers
            for g in edges.get(c, {})
            if g in member_set
        }
        elim_basis = (
            "measured"
            if caller_bases == {"measured"}
            else ("mixed" if "measured" in caller_bases else "static")
        )
        reach = [f for f in member_set if f in depth]
        hotness.append(
            {
                "unit": unit,
                "functions_total": len(member_set),
                "functions_reachable_from_spine": len(reach),
                "min_depth": min(depth[f] for f in reach),
                "inbound_calls_per_frame": round(inbound, 4),
                "inbound_measured_calls_per_frame": round(inbound_measured, 4),
                "inbound_static_calls_per_frame": round(
                    inbound - inbound_measured, 4
                ),
                "outbound_calls_per_frame": round(outbound, 4),
                "net_calls_per_frame": round(inbound - outbound, 4),
                "elimination_basis": elim_basis,
                "exposure_basis": "static",
                "callers_reachable": sorted(callers)[:12],
                "functions": function_rows(unit)[:8],
                "availability": unit_availability(state_units, unit),
            }
        )
    hotness.sort(
        key=lambda r: (-r["inbound_calls_per_frame"], r["min_depth"], r["unit"])
    )
    for index, row in enumerate(hotness):
        row["rank"] = index + 1

    # ---- ranking B: marginal against ring 0 (exact, measured) --------------
    marginal = []
    for unit in reachable_units:
        member_set = members[unit]
        eliminated, exposed = score_unit(edges, rate, ring0, member_set)
        if eliminated <= 0.0:
            continue
        marginal.append(
            {
                "unit": unit,
                "eliminated_calls_per_frame": round(eliminated, 4),
                "exposed_calls_per_frame": round(exposed, 4),
                "net_calls_per_frame": round(eliminated - exposed, 4),
                "bridged_calls_per_frame_after": round(
                    bridged_calls_per_frame(edges, rate, ring0 | member_set), 4
                ),
                "elimination_basis": "measured",
                "exposure_basis": "static",
                "spine_callees_owned": sorted(
                    g for g in edges.get(SPINE_FUNCTION, {}) if g in member_set
                ),
                "availability": unit_availability(state_units, unit),
            }
        )
    marginal.sort(
        key=lambda r: (
            -r["eliminated_calls_per_frame"],
            -r["net_calls_per_frame"],
            r["unit"],
        )
    )
    for index, row in enumerate(marginal):
        row["rank"] = index + 1

    # ---- the monotonicity check the metric needs ---------------------------
    # X1 asserts ring 0 "starts the shrink metric at its maximum".  Test it:
    # link every ring-1 unit and see whether B falls or rises.
    ring1_units = [r["unit"] for r in marginal]
    ring1_linked = set(ring0)
    for unit in ring1_units:
        ring1_linked |= members[unit]
    b_ring1 = bridged_calls_per_frame(edges, rate, ring1_linked)

    # ---- greedy queue by NET (the literal "B falls" objective) -------------
    greedy = []
    linked = set(ring0)
    linked_units = set()
    current = baseline
    for step in range(args.greedy_steps):
        best = None
        for unit in reachable_units:
            if unit in linked_units:
                continue
            member_set = members[unit]
            eliminated, exposed = score_unit(edges, rate, linked, member_set)
            if eliminated <= 0.0:
                continue
            net = eliminated - exposed
            if best is None or net > best[1]:
                best = (unit, net, eliminated, exposed)
        if best is None or best[1] <= 0.0:
            break
        unit, net, eliminated, exposed = best
        linked_units.add(unit)
        linked |= members[unit]
        after = bridged_calls_per_frame(edges, rate, linked)
        greedy.append(
            {
                "step": step + 1,
                "unit": unit,
                "eliminated_calls_per_frame": round(eliminated, 4),
                "exposed_calls_per_frame": round(exposed, 4),
                "net_calls_per_frame": round(net, 4),
                "bridged_calls_per_frame_before": round(current, 4),
                "bridged_calls_per_frame_after": round(after, 4),
                "availability": unit_availability(state_units, unit),
            }
        )
        current = after

    linkable = [
        r["unit"] for r in hotness if r["availability"]["linkable_today"]
    ]

    # ---- the compile queue: depth first, then hotness ----------------------
    # "the order that shrinks the bridged-call count fastest" is NOT raw
    # hotness: a depth-3 unit's inbound calls only stop crossing once its
    # callers are linked, so a hot deep unit compiled first shrinks nothing.
    # Order by (min_depth, -inbound) -- ring 1 first, hottest within a ring.
    compile_queue = sorted(
        hotness,
        key=lambda r: (r["min_depth"], -r["inbound_calls_per_frame"], r["unit"]),
    )
    compile_queue_rows = [
        {
            "position": index + 1,
            "unit": row["unit"],
            "min_depth": row["min_depth"],
            "inbound_calls_per_frame": row["inbound_calls_per_frame"],
            "inbound_measured_calls_per_frame": row[
                "inbound_measured_calls_per_frame"
            ],
            "inbound_static_calls_per_frame": row["inbound_static_calls_per_frame"],
            "outbound_calls_per_frame": row["outbound_calls_per_frame"],
            "net_calls_per_frame": row["net_calls_per_frame"],
            "elimination_basis": row["elimination_basis"],
            "availability": row["availability"],
        }
        for index, row in enumerate(compile_queue)
    ]

    # ---- ring-0 evidence: which spine loop callees the queue unit bundles ---
    spine_unit = by_name[SPINE_FUNCTION]["unit"]
    loop_callees = [
        g
        for g in edges.get(SPINE_FUNCTION, {})
        if measured.get(g, {}).get("per_frame", 0.0) > 0.0
    ]
    bundled = sorted(g for g in loop_callees if g in members[spine_unit])

    payload = {
        "schema": "spine-frontier-1",
        "design": (
            "docs/one-to-one-completion-spec.md section 6, correction X1: "
            "ring 0 is the spine alone, everything it calls is bridged; the "
            "frontier is a COMPILE RANKING, not an N-doubling ladder; growth is "
            "bridged-calls-per-frame falling, not unit count rising"
        ),
        "generated_from": {
            "registry": REGISTRY,
            "chunks": (
                "research/decomp/ghidra-export/chunk_*.c "
                "(line ranges pinned by the registry)"
            ),
            "spine_capture": SPINE_CORPUS,
            "spine_result": SPINE_RESULT,
            "live_ledger": args.ledger,
            "unit_state": args.state,
        },
        "frame_definition": (
            "one iteration of the spine's do{...}while(true) body at "
            "research/decomp/ghidra-export/chunk_0006.c:5790-5833; the capture's "
            "16 iterations are 16 frames"
        ),
        "root": {
            "function": SPINE_FUNCTION,
            "gc_addr": SPINE_ADDR,
            "queue_unit": by_name[SPINE_FUNCTION]["unit"],
            "queue_unit_status": unit_availability(
                state_units, by_name[SPINE_FUNCTION]["unit"]
            ),
            "ring0_module": "research/decomp/spine-boundary/",
            "ring0_module_verdict": spine_meas["verdict"],
            "loop_callees_measured": sorted(loop_callees),
            "loop_callees_bundled_into_queue_unit": bundled,
            "ring0_decision": (
                "ring 0 is research/decomp/spine-boundary/ (the single-function "
                "module), NOT the queue unit %s.  %s owns %d of the spine's own "
                "loop callees (%s), so linking it makes those calls INTERNAL: "
                "the ledger would read %d bridged calls per frame instead of the "
                "measured %d, and boundary_green could not be reproduced against "
                "it.  The queue unit is also status=%s -- never compiled -- so it "
                "is not an available artifact either."
            )
            % (
                spine_unit,
                spine_unit,
                len(bundled),
                ", ".join(bundled) or "none",
                len(loop_callees) - len(bundled),
                len(loop_callees),
                unit_availability(state_units, spine_unit)["status"],
            ),
        },
        "measurement": {
            "spine_capture": {
                "calls": spine_meas["capture"],
                "iterations": spine_meas["iterations"],
                "verdict": spine_meas["verdict"],
                "calls_matched": spine_meas["calls_matched"],
                "corpus_sha256": spine_meas["corpus_sha256"],
            },
            "live_ledger_functions": sorted(live),
            "measured_edges": sorted(measured),
        },
        "graph_cross_check": graph["cross_check"],
        "baseline_bridged_calls_per_frame": round(baseline, 4),
        "baseline_basis": "measured",
        "monotonicity": {
            "bridged_calls_per_frame_ring0": round(baseline, 4),
            "bridged_calls_per_frame_ring0_plus_all_ring1_units": round(
                b_ring1, 4
            ),
            "ring1_units": ring1_units,
            "finding": (
                "B is NOT maximal at ring 0.  Linking the units that own the "
                "spine's 17 loop callees replaces 17 crossings with those "
                "callees' own outbound calls, so B rises before it falls.  "
                "'bridged calls per frame falling' is a TERMINAL objective "
                "(B -> 0 iff the per-frame graph is closed), not a monotone "
                "greedy one; a rung must therefore be scored on NET and the "
                "ladder must accept rungs that raise B when they raise it by "
                "less than the static bound predicts."
            ),
        },
        "estimator": {
            "edge_rate_rule": (
                "rate(f->g) = MEASURED per-frame count where a capture covers "
                "the edge, else freq(f) * static call sites (f->g)"
            ),
            "freq_rule": (
                "freq(spine) = 1/frame by the frame definition; the spine's 19 "
                "direct callees are MEASURED (17 at 1.0/frame; 2 prologue calls "
                "at 0.0/frame -- they appear only in iteration 0 of the "
                "capture); deeper freq is STATIC, propagated along "
                "depth-increasing edges only, capped at depth %d"
            )
            % MAX_DEPTH,
            "static_assumption": (
                "every call site in a body executes once per invocation: "
                "OVER-counts guarded calls, UNDER-counts calls in inner loops"
            ),
            "sdk_calls": (
                "gnt4-* SDK callees (the registry's 996 sdk_prefix exclusions) "
                "are satisfied by the shim seed at link time, never bridged; "
                "they are not graph nodes and never count toward B"
            ),
        },
        "availability_summary": {
            "reachable_units": len(reachable_units),
            "reachable_unit_names": reachable_units,
            "reachable_depth_cap": MAX_DEPTH,
            "ranked_units": len(hotness),
            "linkable_today": linkable,
            "note": (
                "linkable_today means the unit has a green artifact in a tier "
                "the assembly gate links (oracle_green or compile_only).  An "
                "empty list means the whole frontier is uncompiled and the "
                "ranking is a COMPILE queue only -- no rung above ring 0 can "
                "be linked until the driver produces these units."
            ),
        },
        "compile_queue": compile_queue_rows,
        "ranking_frontier_hotness": hotness,
        "ranking_marginal_against_ring0": marginal,
        "greedy_compile_queue_by_net": greedy,
    }
    out = Path(args.out)
    out.parent.mkdir(parents=True, exist_ok=True)
    with io.open(str(out), "w", encoding="utf-8", newline="\n") as handle:
        handle.write(json.dumps(payload, indent=2) + "\n")
    print(
        json.dumps(
            {
                "out": str(out),
                "baseline_bridged_calls_per_frame": baseline,
                "b_after_all_ring1_units": round(b_ring1, 4),
                "reachable_units": len(reachable_units),
                "ranked_units": len(hotness),
                "linkable_today": linkable,
                "top10_hotness": [
                    (
                        r["rank"],
                        r["unit"],
                        r["inbound_calls_per_frame"],
                        r["net_calls_per_frame"],
                        r["elimination_basis"],
                        r["availability"]["status"],
                    )
                    for r in hotness[:10]
                ],
            },
            indent=2,
        )
    )
    return 0


def cmd_metric(args) -> int:
    """B(L) for an explicit unit set -- the ladder's new rung metric.

    Reports the bridged calls per frame the composed module would make if the
    named units were linked on top of ring 0, and the fall from the measured
    ring-0 baseline.  This is what `composition_ladder.py ledger` records for
    every rung alongside the E1 conflict ratio.
    """
    repo = Path(args.repo).resolve()
    graph = build_call_graph(repo)
    edges = graph["edges"]
    by_name = graph["by_name"]
    measured = load_spine_measurement(repo)["rates"]
    depth, freq, basis, rate, rate_basis = compute_frequency(edges, measured)
    members = collections.defaultdict(set)
    for name, fn in by_name.items():
        members[fn["unit"]].add(name)

    ring0 = {SPINE_FUNCTION}
    baseline = bridged_calls_per_frame(edges, rate, ring0)
    units = [u for u in (args.units or "").split(",") if u]
    linked = set(ring0)
    for unit in units:
        linked |= members.get(unit, set())
    value = bridged_calls_per_frame(edges, rate, linked)
    intersecting = sorted(
        u for u in units if any(f in depth for f in members.get(u, set()))
    )
    out = {
        "metric": "bridged_calls_per_frame",
        "ring0": sorted(ring0),
        "units_linked_on_top_of_ring0": units,
        "ring0_baseline_bridged_calls_per_frame": round(baseline, 4),
        "bridged_calls_per_frame": round(value, 4),
        "bridged_calls_per_frame_eliminated": round(baseline - value, 4),
        "units_intersecting_spine_frontier": intersecting,
        "functions_linked_reachable_from_spine": sorted(
            f for u in units for f in members.get(u, set()) if f in depth
        ),
        "basis": "measured ring-0 baseline; static delta",
    }
    if args.json_out:
        with io.open(args.json_out, "w", encoding="utf-8", newline="\n") as handle:
            handle.write(json.dumps(out, indent=2) + "\n")
    print(json.dumps(out, indent=2))
    return 0



def main(argv=None) -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    sub = parser.add_subparsers(dest="command", required=True)
    p_rank = sub.add_parser("rank")
    p_rank.add_argument("--repo", default=".")
    p_rank.add_argument("--state", default=None)
    p_rank.add_argument("--ledger", default=None)
    p_rank.add_argument("--greedy-steps", type=int, default=25)
    p_rank.add_argument("--out", required=True)
    p_rank.set_defaults(func=cmd_rank)
    p_metric = sub.add_parser("metric")
    p_metric.add_argument("--repo", default=".")
    p_metric.add_argument("--units", default="")
    p_metric.add_argument("--json-out", default=None)
    p_metric.set_defaults(func=cmd_metric)
    args = parser.parse_args(argv)
    return args.func(args)


if __name__ == "__main__":
    raise SystemExit(main())
