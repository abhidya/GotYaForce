#!/usr/bin/env python3
"""capture_transcript.py -- transcript_green capture for ORDINARY (returning)
functions whose behaviour has NO CAPTURABLE WRITE SET.

Why this file exists next to capture_oracle.py and capture_spine.py
-------------------------------------------------------------------
`capture_oracle.py capture` implements oracle_green: break at entry, snapshot
args and a PLAN-DECLARED read set, run to the caller's return address, snapshot
the return value and a PLAN-DECLARED write set.  Measured over the whole ROM
(research/tools/OGhidra/tools/survey_plan_tiers.py), 4455 of 10954 functions
"store nothing a capture could compare".  For those the write-comparison
standard is not hard, it is EMPTY -- and a spec built on an empty write set
would pass vacuously.

`capture_spine.py` already solved the hard half of the alternative: record the
CALLEE BOUNDARY (which callees, in which order, with which arguments, returning
what, writing what) so a function can be verified by the transcript it emits
rather than by the memory it leaves behind.  It only does so for the
NONTERMINATING spine, where the run is bounded by an iteration count.

A returning function is the easier case -- break at entry, walk the body's call
sites, close at the return -- and this file is that generalisation.  It reuses
capture_spine.py's machinery rather than forking it: the ROM reader, the
PowerPC decode primitives, the wasm import-signature parser, the EABI argument
allocator and the register/JSON value readers all now live in capture_common.py
and are imported by BOTH tools, so the two standards cannot drift apart in how
they read an argument register or bind a ROM call site to a wasm import.

What differs from the spine capture
-----------------------------------
1. **Termination is the function's own return**, not an iteration count.  The
   entry LR is breakpointed exactly as capture_oracle.py does, GUARDED BY THE
   STACK POINTER (r1 back at its entry value), so a recursive or shared return
   address cannot close a case early.
2. **The return value is part of the claim.**  Read from r3 / r3:r4 / f1 per the
   module's own declared result type.
3. **The corpus is N INDEPENDENT CASES**, not one long run.  Each hit of the
   function is its own case with its own entry args, transcript and return.
4. **The body is not straight-line.**  A spine is by definition a straight run
   of calls, so capture_spine.py can breakpoint every instruction.  A general
   function branches, so this tool breakpoints only what it needs: every
   out-of-unit call site, the instruction AFTER each (where the callee's return
   registers are still fresh), and the entry LR.
5. **In-unit calls are followed, not recorded.**  A call to another function of
   the same wasm module is an INTERNAL wasm call the harness's import shims
   never see -- but the out-of-unit calls that in-unit callee makes ARE seen.
   So `sites` computes the transitive in-unit closure and breakpoints the call
   sites of every function in it, while emitting no record for the in-unit call
   itself.

What this tool REFUSES to capture (and why that is the point)
-------------------------------------------------------------
* **Indirect calls.**  `bctrl` through a ROM function-pointer table has no
  wasm import to bind to -- emcc lowers it to `call_indirect` on the module's
  own table, which the import shims cannot observe.  A function containing one
  is refused by `sites` with that reason, never captured with a hole in it.
* **A function with an empty transcript.**  If a function makes no out-of-unit
  call and returns nothing, there is nothing to compare and `sites` says so.
  run-transcript.mjs enforces the same thing at replay time (its vacuity guard);
  refusing here just saves the emulator run.

Declared limits (recorded in the capture header as `exclusions`)
----------------------------------------------------------------
* **Memory is watch-set-scoped.**  A full MEM1 diff per boundary cannot run at
  frame rate over GDB-RSP.  The watch set is the seed windows (below); every
  other address is an explicit exclusion.
* **Seed windows are GIVEN to the port.**  The wasm arena holds the static DOL
  image, not the live console heap, so a function reading a live object would
  read zeroes.  `--watch-args` snapshots a window at each MEM1-valued pointer
  argument at entry and the capture replays those bytes into the arena.  Those
  bytes are evidence the port was HANDED, not evidence it produced; they are
  itemised in the result artifact as `seeded_bytes`.
* **Seed windows are byte-swapped FIELD-WISE, at the widths the console's own
  load instructions state.**  The arena is little-endian and the console is
  big-endian, so a seeded window must be swapped -- but a raw struct window has
  no field map, and a blind uniform swap mis-serves every field read at another
  width (a `lhz` at +0x3e8 next to a `lwz` at +0x5b4 cannot share one width).
  `sites` therefore reads the widths straight off the ROM: every `lbz/lhz/lha/
  lwz/lfs/lfd` at `disp(rA)` in the function's in-unit closure contributes
  `disp -> width` to a `field_widths` map, which the capture applies per field.
  Bytes no load touches keep the default 4-byte swap; an offset read at two
  different widths is a genuine conflict and is REPORTED in the plan, not
  silently resolved.  A width the map still gets wrong can only produce a FALSE
  RED (the port reads a wrong value, emits a wrong argument, and the run fails),
  never a false green -- the safe direction.
* **Console stack addresses are excluded** (the wasm module has its own linear
  stack at its own addresses).

Usage
-----
    # 1. derive the plan from the ROM + the built unit module
    python capture_transcript.py sites --unit auto-c0020-007 --fn zz_00c4704_ \\
        --wasm research/decomp/port-units-staging/auto-c0020-007/unit.wasm \\
        --out research/tools/dolphin-trace/plans/auto-c0020-007.zz_00c4704_.transcript.json

    # 2. boot Dolphin (capture_oracle.py launch) and reach the scenario
    # 3. capture N cases
    python capture_transcript.py capture --plan <plan> --n 8 \\
        --scenario battle-2v2-combat --out <out.transcript.jsonl>

The emitted JSONL is transcript_schema 1, replayed by
research/decomp/oracle-harness/run-transcript.mjs.
"""
from __future__ import annotations

import argparse
import base64
import json
import struct
import sys
import time
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))

from capture_oracle import (  # noqa: E402
    ASSET_ROOT, DEFAULT_PORT, PAD_INJECT_BP, REPO_ROOT, StubDriver,
    apply_scenario_setup, is_mem1, load_scenario, now_iso, parse_inject_arg,
    stop_pc, unit_functions,
)
from capture_common import (  # noqa: E402  -- shared with capture_spine.py
    BCLR_OP, BC_OP, BLR_XO, BRANCH_OP, Dol, Regs, STORE_OPS, branch_target,
    eabi_allocate, eabi_return, read_arg, read_ret, s16, swap_elems,
    wasm_signatures,
)
from rsp_client import RspError  # noqa: E402

TRANSCRIPT_SCHEMA = 1
STANDARD = "transcript_green"


# --------------------------------------------------------------------------
# callee naming: ROM address -> the name the unit's wasm imports it under
# --------------------------------------------------------------------------

def addr_name_candidates(addr: int) -> list[str]:
    """The two shapes the port pipeline gives an out-of-unit callee.

    A unit's shim header declares every out-of-unit callee by ADDRESS, either as
    Ghidra's `FUN_<full addr>` or as the pipeline's `zz_<addr & 0x0fffffff>_`
    (see research/decomp/port-units-staging/*/unit.c prototypes).
    """
    return [f"zz_{addr & 0x0FFFFFFF:07x}_", f"FUN_{addr:08x}"]


def registry_names(repo_root: Path) -> dict[int, str]:
    """address -> Ghidra symbol, from the oracle registry when it is present.

    Optional: the address-derived candidates above cover the pipeline's own
    naming; the registry additionally covers symbols that were renamed.
    """
    p = repo_root / "research/decomp/data/oracle-registry.json"
    if not p.exists():
        return {}
    reg = json.loads(p.read_text(encoding="utf-8-sig"))
    out = {}
    for fn in reg.get("functions", []):
        try:
            out[int(fn["address"], 16)] = fn["name"]
        except (KeyError, ValueError):
            continue
    return out


# --------------------------------------------------------------------------
# function decode: the body of ONE returning function
# --------------------------------------------------------------------------

# PowerPC load opcodes -> (mnemonic, width). These are how the FIELD WIDTH MAP
# is derived: the console's own instructions say at what width each offset off a
# pointer is read, which is exactly what the arena byte-swap must match. Nothing
# is guessed and nothing is hand-authored.
LOAD_OPS = {
    32: ("lwz", 4), 33: ("lwzu", 4),
    34: ("lbz", 1), 35: ("lbzu", 1),
    40: ("lhz", 2), 41: ("lhzu", 2),
    42: ("lha", 2), 43: ("lhau", 2),
    48: ("lfs", 4), 49: ("lfsu", 4),
    50: ("lfd", 8), 51: ("lfdu", 8),
}


def decode_function(dol: Dol, start: int, end: int) -> dict:
    """Walk one function's instructions in [start, end).

    Records every direct call, every indirect call, every return site, every
    non-stack store and every non-stack LOAD (with its width -- see LOAD_OPS).
    Unlike decode_spine this does NOT require a straight-line body -- a
    returning function branches, and the dynamic call order is what the capture
    records.
    """
    calls: list[dict] = []
    indirect: list[dict] = []
    returns: list[int] = []
    stores: list[dict] = []
    loads: list[dict] = []
    for addr in range(start, end, 4):
        w = dol.word(addr)
        if w is None:
            raise SystemExit(f"function walk left mapped ROM at {addr:#010x}")
        op = w >> 26
        if op == BRANCH_OP:
            target, is_call = branch_target(addr, w)
            if is_call:
                calls.append({"at": f"0x{addr:08x}", "target": f"0x{target:08x}"})
        elif op == BCLR_OP:
            xo, lk = (w >> 1) & 0x3FF, w & 1
            if lk:
                # bctrl / blrl -- a ROM function-pointer dispatch. emcc lowers
                # the C `(*(code *)...)()` to call_indirect on the module's OWN
                # table, so no import shim can observe it: the transcript would
                # have a hole. Refused by cmd_sites.
                indirect.append({"at": f"0x{addr:08x}",
                                 "kind": "bctrl" if xo == 528 else "blrl"})
            elif xo == BLR_XO:
                returns.append(addr)
        elif op in STORE_OPS and addr != start:
            name, width = STORE_OPS[op]
            rs, ra, d = (w >> 21) & 31, (w >> 16) & 31, s16(w & 0xFFFF)
            if ra == 1:
                continue                # stack slot, not observable state
            stores.append({"at": f"0x{addr:08x}", "op": name, "width": width,
                           "src_reg": f"r{rs}", "addr_expr": f"r{ra}{d:+#x}"})
        elif op in LOAD_OPS:
            name, width = LOAD_OPS[op]
            rd, ra, d = (w >> 21) & 31, (w >> 16) & 31, s16(w & 0xFFFF)
            if ra in (1, 2, 13):
                continue            # stack / TOC / small-data base, not an argument object
            loads.append({"at": f"0x{addr:08x}", "op": name, "width": width,
                          "base_reg": f"r{ra}", "disp": d})
    return {"start": f"0x{start:08x}", "end": f"0x{end:08x}",
            "calls": calls, "indirect_calls": indirect,
            "returns": [f"0x{a:08x}" for a in returns], "stores": stores,
            "loads": loads}


def sweep_extent(dol: Dol, start: int, limit: int = 0x4000) -> int:
    """Exclusive end of the function at `start`, by branch-aware linear sweep.

    A `blr` only ends the function if no forward branch already seen jumps PAST
    it -- an early return inside an if/else is a `blr` in the middle of the body.
    Naively taking the LAST `blr` within `limit` instead runs straight through
    the neighbouring functions, which would put THEIR call sites into the plan
    and let unrelated breakpoints corrupt a capture.
    """
    max_forward = start
    for addr in range(start, start + limit, 4):
        w = dol.word(addr)
        if w is None:
            break
        op = w >> 26
        if op == BRANCH_OP:
            target, is_call = branch_target(addr, w)
            if not is_call and target > max_forward:
                max_forward = target
        elif op == BC_OP:                       # conditional: 16-bit signed BD
            bd = w & 0xFFFC
            if bd & 0x8000:
                bd -= 0x10000
            target = ((bd if (w >> 1) & 1 else addr + bd)) & 0xFFFFFFFF
            if target > max_forward:
                max_forward = target
        elif op == BCLR_OP and ((w >> 1) & 0x3FF) == BLR_XO and not (w & 1):
            if addr >= max_forward:
                return addr + 4
    return start + limit


def function_extents(fns: list[tuple[int, str]], dol: Dol,
                     limit: int = 0x4000) -> dict[int, int]:
    """addr -> exclusive end, from the unit's own marker addresses.

    A unit's functions are normally contiguous in ROM, so the next marker is the
    end -- but that is not guaranteed, and the LAST function has no next marker
    at all. Take the TIGHTER of the two bounds: never decode past the next
    function's start, and never past this function's own terminating `blr`.
    """
    ordered = sorted(a for a, _ in fns)
    ends = {}
    for i, a in enumerate(ordered):
        swept = sweep_extent(dol, a, limit)
        ends[a] = min(ordered[i + 1], swept) if i + 1 < len(ordered) else swept
    return ends


# --------------------------------------------------------------------------
# sites
# --------------------------------------------------------------------------

def cmd_sites(a: argparse.Namespace) -> int:
    dol = Dol.from_iso(Path(a.iso))
    fns = unit_functions(a.unit)
    if not fns:
        sys.exit(f"unit {a.unit} has no function markers")
    by_addr = {addr: name for addr, name in fns}
    by_name = {name: addr for addr, name in fns}
    if a.fn not in by_name:
        sys.exit(f"{a.fn} is not a function of unit {a.unit} "
                 f"(markers: {sorted(by_name)})")
    entry = by_name[a.fn]
    ends = function_extents(fns, dol)

    imports, exports = wasm_signatures(Path(a.wasm))
    import_by_name = {i["name"]: i for i in imports}
    if a.fn not in exports:
        sys.exit(f"{a.wasm} does not export {a.fn}")

    reg = registry_names(REPO_ROOT)

    def bind_callee(target: int) -> str | None:
        for cand in addr_name_candidates(target):
            if cand in import_by_name:
                return cand
        nm = reg.get(target)
        if nm and nm in import_by_name:
            return nm
        return None

    # transitive in-unit closure: an in-unit call is an INTERNAL wasm call the
    # shims never see, but the out-of-unit calls it makes ARE seen, so its call
    # sites must be breakpointed too.
    closure: list[int] = []
    pending = [entry]
    shapes: dict[int, dict] = {}
    while pending:
        f = pending.pop()
        if f in closure:
            continue
        closure.append(f)
        shape = decode_function(dol, f, ends[f])
        shapes[f] = shape
        for c in shape["calls"]:
            t = int(c["target"], 16)
            if t in by_addr and t not in closure:
                pending.append(t)

    refusals: list[str] = []
    sites: list[dict] = []
    unbound: list[dict] = []
    in_unit_calls: list[dict] = []
    for f in closure:
        sh = shapes[f]
        for ic in sh["indirect_calls"]:
            refusals.append(
                f"{by_addr[f]} dispatches through a ROM function-pointer table "
                f"at {ic['at']} ({ic['kind']}) -- emcc lowers that to "
                f"call_indirect on the module's own table, which no import shim "
                f"can observe, so the transcript would have a hole")
        for c in sh["calls"]:
            t = int(c["target"], 16)
            if t in by_addr:
                in_unit_calls.append({"in": by_addr[f], "at": c["at"], "callee": by_addr[t]})
                continue
            name = bind_callee(t)
            if name is None:
                unbound.append({"in": by_addr[f], "at": c["at"], "target": c["target"]})
                continue
            imp = import_by_name[name]
            sites.append({"at": c["at"], "target": c["target"], "in": by_addr[f],
                          "callee": name,
                          "wasm_params": imp["params"], "wasm_results": imp["results"],
                          "args": eabi_allocate(imp["params"]),
                          "ret": eabi_return(imp["results"])})
    if unbound:
        refusals.append(
            f"{len(unbound)} ROM call site(s) bind to no wasm import "
            f"(first: {unbound[0]['target']} from {unbound[0]['in']}) -- the "
            f"module was not built from this unit, or the callee is named "
            f"neither zz_<addr>_ nor FUN_<addr>")

    # ---- FIELD WIDTH MAP, derived from the console's own load instructions ----
    # The wasm arena is little-endian and the console is big-endian, so seeded
    # bytes must be byte-swapped -- but at WHAT element width? A blind uniform
    # swap mis-serves every field the code reads at a different width, and there
    # is no field map for arbitrary ROM objects. The ROM's own `lhz`/`lwz`/`lfd`
    # at `disp(rA)` states the width at each offset, so that is what is used.
    # A single offset read at two widths is a genuine conflict and is REPORTED,
    # not silently resolved.
    field_widths: dict[int, int] = {}
    width_conflicts: list[dict] = []
    for f in closure:
        for ld in shapes[f]["loads"]:
            if ld["disp"] < 0:
                continue
            prev = field_widths.get(ld["disp"])
            if prev is not None and prev != ld["width"]:
                width_conflicts.append({"offset": f"0x{ld['disp']:x}",
                                        "widths": sorted({prev, ld["width"]}),
                                        "at": ld["at"], "in": by_addr[f]})
                field_widths[ld["disp"]] = min(prev, ld["width"])
            else:
                field_widths[ld["disp"]] = ld["width"]

    sig = exports[a.fn]
    ret_spec = eabi_return(sig["results"])
    # Non-vacuity, checked BEFORE the emulator is ever touched: a function that
    # calls nothing out of unit and returns nothing has an empty transcript, and
    # a capture of it could only ever pass vacuously. run-transcript.mjs refuses
    # it too; refusing here saves the run.
    if not sites and ret_spec is None:
        refusals.append(
            f"{a.fn} has an EMPTY transcript: no out-of-unit call and no return "
            f"value. Nothing about it is observable at the import boundary, so "
            f"transcript_green cannot claim anything about it")

    plan = {
        "transcript_plan_schema": TRANSCRIPT_SCHEMA,
        "standard": STANDARD,
        "generated_by": "research/tools/dolphin-trace/capture_transcript.py sites",
        "generated_at": now_iso(),
        "unit": a.unit,
        "fn": {"name": a.fn, "gc_addr": f"0x{entry:08x}",
               "end": f"0x{ends[entry]:08x}",
               "params": sig["params"], "results": sig["results"],
               "entry_args": eabi_allocate(sig["params"]),
               "ret": ret_spec},
        "wasm": a.wasm,
        "in_unit_closure": [{"name": by_addr[f], "addr": f"0x{f:08x}",
                             "end": shapes[f]["end"]} for f in closure],
        "call_sites": sites,
        "in_unit_calls": in_unit_calls,
        "unbound_call_sites": unbound,
        "return_sites": sorted({r for f in closure for r in shapes[f]["returns"]}),
        "stores": [dict(st, **{"in": by_addr[f]}) for f in closure for st in shapes[f]["stores"]],
        # offset -> width, from the console's own load instructions; the seed
        # windows are byte-swapped field-wise with this map.
        "field_widths": {f"0x{off:x}": w for off, w in sorted(field_widths.items())},
        "field_width_conflicts": width_conflicts,
        "refusals": refusals,
        "capturable": not refusals,
    }
    out = Path(a.out)
    out.parent.mkdir(parents=True, exist_ok=True)
    out.write_text(json.dumps(plan, indent=1) + "\n", encoding="utf-8")
    print(json.dumps({
        "out": str(out), "fn": a.fn, "gc_addr": plan["fn"]["gc_addr"],
        "in_unit_closure": [by_addr[f] for f in closure],
        "out_of_unit_call_sites": len(sites),
        "distinct_callees": sorted({s["callee"] for s in sites}),
        "in_unit_calls": len(in_unit_calls),
        "returns_value": ret_spec is not None,
        "capturable": plan["capturable"],
        "refusals": refusals,
    }, indent=2))
    return 0 if plan["capturable"] else 2


# --------------------------------------------------------------------------
# capture
# --------------------------------------------------------------------------

def snapshot_windows(rsp, windows: list[dict]) -> dict[int, bytes]:
    return {w["addr"]: rsp.read_mem(w["addr"], w["size"]) for w in windows}


def swap_fields(raw: bytes, field_widths: dict[int, int], default_width: int) -> bytes:
    """Big-endian console bytes -> little-endian arena bytes.

    A uniform element-wise swap (capture_spine.py's rule, which is right for a
    region of one declared width) is WRONG for a raw struct window, where a u16
    field and a u32 field sit side by side. `field_widths` is offset -> width,
    read straight off the console's own load instructions by `sites`, so each
    field the code actually reads is swapped at the width it is read at. Bytes
    no load touches keep the default-width swap; nothing reads them, and the
    capture declares the fact rather than hiding it.
    """
    out = bytearray(swap_elems(raw, default_width))
    n = len(raw)
    for off, w in field_widths.items():
        if 0 <= off and off + w <= n and w != default_width:
            out[off:off + w] = raw[off:off + w][::-1]
    return bytes(out)


def window_bytes(raw: bytes, elem_width: int, field_widths: dict[int, int] | None = None) -> str:
    payload = swap_fields(raw, field_widths, elem_width) if field_widths \
        else swap_elems(raw, elem_width)
    return base64.b64encode(payload).decode()


def diff_windows(before: dict[int, bytes], after: dict[int, bytes],
                 elem_width: int, field_widths: dict[int, int] | None = None) -> list[dict]:
    """Byte deltas over the watch windows, emitted arena-side (swapped)."""
    out = []
    for addr, new in after.items():
        old = before.get(addr)
        if old is None or old == new:
            continue
        out.append({"addr": f"0x{addr:08x}",
                    "b64": window_bytes(new, elem_width, field_widths)})
    return out


def cmd_capture(a: argparse.Namespace) -> int:
    plan = json.loads(Path(a.plan).read_text(encoding="utf-8"))
    if plan.get("transcript_plan_schema") != TRANSCRIPT_SCHEMA:
        sys.exit("plan is not transcript_plan_schema 1")
    if not plan.get("capturable") and not a.force:
        sys.exit("plan is marked NOT capturable:\n  - "
                 + "\n  - ".join(plan.get("refusals", []))
                 + "\n(pass --force only to produce evidence you will NOT promote)")

    entry = int(plan["fn"]["gc_addr"], 16)
    field_widths = {int(k, 16): v for k, v in (plan.get("field_widths") or {}).items()}
    site_by_addr = {int(s["at"], 16): s for s in plan["call_sites"]}
    # the instruction AFTER a call site: where the callee's return registers are
    # still fresh. A back-to-back `bl` pair makes one address both, so a stop
    # closes the pending call first and then opens the new one.
    after_by_addr = {int(s["at"], 16) + 4: s for s in plan["call_sites"]}

    scenario = load_scenario(a.scenario) if a.scenario else None
    if scenario and not a.inject:
        a.inject = scenario.get("inject")
    if scenario and a.game_state == "unspecified":
        a.game_state = scenario.get("game_state") or "unspecified"
    injector = parse_inject_arg(a.inject)

    cases: list[dict] = []
    notes: list[str] = []
    misses = 0
    watch_meta: list[dict] = []
    d = StubDriver(a.port)
    setup_report = None
    t0 = time.monotonic()
    deadline = t0 + a.max_seconds
    try:
        d.halt()
        setup_report = apply_scenario_setup(scenario, d)
        d.set_bp(entry)
        if injector is not None:
            d.set_bp(PAD_INJECT_BP)
        for addr in list(site_by_addr) + list(after_by_addr):
            d.set_bp(addr)

        while len(cases) < a.n and time.monotonic() < deadline:
            # ---- wait for an entry hit ----
            hit = False
            while time.monotonic() < deadline:
                stop = d.cont_until_stop(timeout=min(a.stop_timeout, max(0.5, deadline - time.monotonic())))
                if stop is None:
                    notes.append("stub stop timeout waiting for entry")
                    break
                pc = stop_pc(stop) or d.rsp.read_pc()
                if injector is not None and pc == PAD_INJECT_BP:
                    injector.on_hit(d.rsp)
                    continue
                if pc == entry:
                    hit = True
                    break
                # a call site of a DIFFERENT invocation (the function is not on
                # the stack yet) -- ignore until our own entry arrives
            if not hit:
                break

            regs = Regs(d.rsp)
            entry_args = [read_arg(regs, s) for s in plan["fn"]["entry_args"]]
            lr = d.rsp.read_lr()
            entry_sp = regs.gpr(1)

            # ---- watch windows: a window at each MEM1-valued pointer argument ----
            windows = []
            if a.watch_args > 0:
                seen = set()
                for spec in plan["fn"]["entry_args"]:
                    if spec["t"] != "i32" or not spec["src"].startswith("r"):
                        continue
                    v = regs.gpr(int(spec["src"][1:]))
                    base = v & ~(a.seed_elem_width - 1)
                    if is_mem1(base) and is_mem1(base + a.watch_args - 1) and base not in seen:
                        seen.add(base)
                        windows.append({"addr": base, "size": a.watch_args,
                                        "arg": spec["i"]})
            seed = []
            for w in windows:
                raw = d.rsp.read_mem(w["addr"], w["size"])
                seed.append({"addr": f"0x{w['addr']:08x}",
                             "b64": window_bytes(raw, a.seed_elem_width, field_widths)})
            # UNION across cases, with the count: a window is derived from a
            # POINTER ARGUMENT, so different cases legitimately watch different
            # addresses. Recording only the first case's set would overstate what
            # every case checked; the per-case `seed`/`owned_end` records remain
            # the authoritative addresses, and run-transcript.mjs counts the
            # bytes it ACTUALLY verified from those, not from this header.
            for w in windows:
                key = f"0x{w['addr']:08x}"
                hit = next((m for m in watch_meta if m["addr"] == key), None)
                if hit is None:
                    watch_meta.append({"addr": key, "size": w["size"],
                                       "from_arg": w["arg"], "cases": 1})
                else:
                    hit["cases"] += 1

            # ---- walk the body to the return ----
            d.set_bp(lr)
            calls: list[dict] = []
            pending = None
            pre = snapshot_windows(d.rsp, windows) if windows else {}
            ret_val = None
            closed = False
            case_deadline = min(deadline, time.monotonic() + a.case_timeout)
            while time.monotonic() < case_deadline:
                stop = d.cont_until_stop(timeout=min(a.stop_timeout, max(0.5, case_deadline - time.monotonic())))
                if stop is None:
                    notes.append(f"case {len(cases)}: stub stop timeout mid-body")
                    break
                pc = stop_pc(stop) or d.rsp.read_pc()
                if injector is not None and pc == PAD_INJECT_BP:
                    injector.on_hit(d.rsp)
                    continue
                r = Regs(d.rsp)

                # close a pending call first: `after` is where its return
                # registers are fresh, and a back-to-back bl makes one address
                # both an `after` and a new call site.
                if pending is not None and (pc in after_by_addr or pc == lr):
                    pending["ret"] = read_ret(r, pending.pop("_ret_spec"))
                    if windows:
                        post = snapshot_windows(d.rsp, windows)
                        pending["deltas"] = diff_windows(pre, post, a.seed_elem_width, field_widths)
                        pre = post
                    calls.append(pending)
                    pending = None

                if pc == lr:
                    # STACK-POINTER GUARD: a shared or recursive return address
                    # must not close the case early. r1 is back at its entry
                    # value only when OUR frame has been popped.
                    if r.gpr(1) != entry_sp:
                        continue
                    ret_val = read_ret(r, plan["fn"]["ret"])
                    closed = True
                    break
                if pc in site_by_addr:
                    site = site_by_addr[pc]
                    if pending is not None:
                        notes.append(f"case {len(cases)}: call at {site['at']} opened "
                                     f"while another was pending (unreturned callee)")
                        calls.append(pending)
                        pending = None
                    pending = {"i": len(calls), "callee": site["callee"],
                               "callee_addr": site["target"],
                               "args": [read_arg(r, s) for s in site["args"]],
                               "ret": None, "deltas": [], "owned": [],
                               "_ret_spec": site["ret"]}
            d.clear_bp(lr)
            if not closed:
                misses += 1
                continue
            for c in calls:
                c.pop("_ret_spec", None)
            case = {"kind": "case", "n": len(cases), "args": entry_args,
                    "calls": calls, "ret": ret_val}
            if seed:
                case["seed"] = seed
            if windows:
                case["owned_end"] = [
                    {"addr": f"0x{addr:08x}", "b64": window_bytes(raw, a.seed_elem_width, field_widths)}
                    for addr, raw in snapshot_windows(d.rsp, windows).items()]
            cases.append(case)
    except (RspError, OSError) as e:
        notes.append(f"stub session died: {e}")
    finally:
        d.cleanup()

    call_total = sum(len(c["calls"]) for c in cases)
    header = {
        "kind": "header", "transcript_schema": TRANSCRIPT_SCHEMA,
        "unit": plan["unit"],
        "fn": {"export": plan["fn"]["name"], "gc_addr": plan["fn"]["gc_addr"],
               "params": plan["fn"]["params"], "results": plan["fn"]["results"]},
        "wasm": a.wasm_rel,
        "arena": a.arena_rel,
        # ADVISORY. The watch windows double as owned regions -- bytes the port
        # must leave byte-exact at the return -- but they are derived per case
        # from that case's pointer arguments, so this is the UNION over the
        # corpus with a per-address case count, not a set every case checked.
        # The authoritative per-case addresses are in each case's `owned_end`.
        # They are NOT a write set -- see the exclusions.
        "owned_regions": watch_meta,
        "watch_policy": {
            "rule": f"one {a.watch_args}-byte window at each MEM1-valued i32 "
                    f"pointer argument of the entry signature, per case",
            "note": "addresses vary per case; `owned_regions` is the union with "
                    "a case count, and the replay counts only the bytes it "
                    "actually verified",
        },
        "counts": {"case": len(cases), "call": call_total},
        "source": {
            "standard": STANDARD,
            "capture_tool": "research/tools/dolphin-trace/capture_transcript.py",
            "control_strategy": "breakpoint the function entry, every out-of-unit "
                                "call site in its in-unit closure, the instruction "
                                "after each, and the entry LR; terminate the case "
                                "at the return with a stack-pointer guard",
            "emulator": "bundled Dolphin 2606-97 (dolphin/Dolphin.exe), Null video, CPU only",
            "stub": f"gdb-rsp 127.0.0.1:{a.port}",
            "dumped_at": now_iso(),
            "game_state": a.game_state,
            "plan": str(Path(a.plan).as_posix()),
            "in_unit_closure": [c["name"] for c in plan["in_unit_closure"]],
            "watch_args_bytes": a.watch_args,
            "seed_elem_width": a.seed_elem_width,
            "field_widths": plan.get("field_widths") or {},
            "field_width_conflicts": plan.get("field_width_conflicts") or [],
            "pad_injection": a.inject or None,
            "injected_frames": injector.frame if injector else 0,
            "scenario": a.scenario or None,
            "scenario_setup": setup_report,
            "misses": misses,
            "exclusions": [
                "transcript_green is STRICTLY WEAKER than oracle_green: it "
                "compares the observable call transcript and the return value, "
                "not the function's memory write set",
                "memory is watch-set-scoped: only the seed/watch windows are "
                "read; a full MEM1 diff cannot run at frame rate over GDB-RSP",
                "seed bytes are GIVEN to the port, not derived by it -- the wasm "
                "arena holds the static DOL image, not the live console heap",
                f"seed windows are byte-swapped FIELD-WISE using the width map "
                f"the console's own load instructions state (see source.field_widths); "
                f"bytes no load in the function touches keep the default "
                f"{a.seed_elem_width}-byte swap. A width the map gets wrong can only "
                f"cause a FALSE RED, never a false green",
                "console stack addresses are excluded (the wasm module has its "
                "own linear stack)",
                "in-unit calls are followed but NOT recorded: they are internal "
                "wasm calls no import shim can observe",
                "the claim is bounded by this corpus -- N recorded cases, never "
                "all inputs",
            ],
            "notes": notes,
            "elapsed_s": round(time.monotonic() - t0, 1),
        },
    }
    out = Path(a.out)
    out.parent.mkdir(parents=True, exist_ok=True)
    with out.open("w", encoding="utf-8", newline="\n") as f:
        f.write(json.dumps(header) + "\n")
        for c in cases:
            f.write(json.dumps(c) + "\n")
        f.write(json.dumps({"kind": "end",
                            "counts": {"case": len(cases), "call": call_total}}) + "\n")
    print(json.dumps({"out": str(out), "cases": len(cases), "calls": call_total,
                      "misses": misses, "notes": notes,
                      "elapsed_s": round(time.monotonic() - t0, 1)}, indent=2))
    return 0 if cases and not notes else 1


# --------------------------------------------------------------------------

def main() -> int:
    p = argparse.ArgumentParser(
        description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    sub = p.add_subparsers(dest="cmd")
    sub.required = True

    sp = sub.add_parser("sites", help="decode the function + bind it to the module ABI")
    sp.add_argument("--unit", required=True)
    sp.add_argument("--fn", required=True, help="the function's wasm export name")
    sp.add_argument("--wasm", required=True, help="the built unit module")
    sp.add_argument("--iso", default=str(ASSET_ROOT / "Gotcha Force.iso"))
    sp.add_argument("--out", required=True)
    sp.set_defaults(func=cmd_sites)

    cp = sub.add_parser("capture", help="record N cases of the function's transcript")
    cp.add_argument("--plan", required=True)
    cp.add_argument("--n", type=int, default=8, help="cases to record")
    cp.add_argument("--out", required=True)
    cp.add_argument("--wasm-rel", default="../port-units-staging/UNIT/unit.wasm",
                    help="header `wasm`: path RELATIVE TO THE CAPTURE FILE")
    cp.add_argument("--arena-rel", default="../oracle-harness/arena-trace-empty.json",
                    help="header `arena`: path RELATIVE TO THE CAPTURE FILE")
    cp.add_argument("--watch-args", type=int, default=0x200,
                    help="bytes to seed/watch at each MEM1-valued pointer argument "
                         "(0 disables; the bytes are GIVEN to the port and are "
                         "itemised in the result artifact)")
    cp.add_argument("--seed-elem-width", type=int, default=4)
    cp.add_argument("--stop-timeout", type=float, default=20.0)
    cp.add_argument("--case-timeout", type=float, default=60.0)
    cp.add_argument("--max-seconds", type=float, default=600.0)
    cp.add_argument("--game-state", default="unspecified")
    cp.add_argument("--inject", default=None)
    cp.add_argument("--scenario", default=None)
    cp.add_argument("--port", type=int, default=DEFAULT_PORT)
    cp.add_argument("--force", action="store_true",
                    help="capture despite plan refusals -- produces evidence that "
                         "must NOT be promoted")
    cp.set_defaults(func=cmd_capture)

    a = p.parse_args()
    return a.func(a)


if __name__ == "__main__":
    raise SystemExit(main())
