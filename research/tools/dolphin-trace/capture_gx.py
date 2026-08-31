#!/usr/bin/env python3
"""capture_gx.py -- GX CALL-STREAM capture from the real console.

The gap this closes
-------------------
`docs/gx-hle-host.md` §7.1: the GX HLE host translates 87.1% of the ROM's static
GX call sites and verifies **exactly none** of them.  Its pixel assertions are
predicted from the same understanding of GX that produced the implementation, so
they are self-consistency checks and cannot detect a shared misunderstanding.

This tool records, from the real game running in the bundled Dolphin, the actual
stream a ROM draw function emits at the SDK seam:

    * every GX (and other out-of-window SDK) CALL -- entry point, in order,
      with its arguments read out of the PowerPC EABI registers;
    * every store to the memory-mapped WRITE-GATHER PIPE (0xCC008000..0xCC008020)
      -- width and value, in order, interleaved with the calls.

That stream is what `packages/rom-runtime/src/gx/` actually receives from a
gate-lowered ROM unit, so replaying the same ROM function through the host and
comparing the two streams verifies the FIFO decoder's INPUT, the wgpipe
lowering, and argument marshalling against the console.

**It does NOT verify pixels.**  Nothing here reads a framebuffer; see
`docs/gx-hle-host.md` §6.3 and the `does_not_verify` block that
`research/decomp/oracle-harness/run-gx-callstream.mjs` writes into every result.

Why this is a THIRD capture tool and not a flag on the other two
---------------------------------------------------------------
`capture_oracle.py` (oracle_green) runs to the caller's return address and
compares a write set.  `capture_spine.py` (boundary_green) and
`capture_transcript.py` (transcript_green) compare a CALLEE boundary.  None of
them can see the write-gather pipe, because a pipe store is not a call and not a
MEM1 write -- it is a store to hardware MMIO whose only observable is its
position in a byte stream.  A GX draw function's observable behaviour is
*calls interleaved with pipe stores*, which is a fourth shape.

Everything that CAN be shared is imported from `capture_common.py` /
`capture_oracle.py` unchanged: the DOL reader, the PowerPC decode primitives,
the wasm import-signature parser, the EABI argument allocator, the register
readers, the stub driver, scenarios and pad injection.

Stack-pointer arguments
-----------------------
A ROM draw function routinely passes the address of one of its own stack locals
(`gnt4_PSMTXIdentity_bl(afStack_38)`).  The console's stack address and the wasm
module's stack address are different by construction and comparing them is
meaningless.  Such an argument is recorded as
`{"k":"sp","off":<arg - r1 at the call>}` and the harness compares it
STRUCTURALLY -- the aliasing pattern and the pairwise offsets must match, and a
stack-relative argument may never be equal to a non-stack one.  That is a real
check (it proves the port passes the same buffer to the same calls) and it is a
weaker one than value equality; the result artifact says so.

Usage
-----
    # 1. derive the plan from the ROM + the built module (no emulator)
    python capture_gx.py sites --fn 0x80027c34 \
        --wasm packages/rom-runtime/test/fixtures/gx-rom-unit/gx_rom_unit.threads.wasm \
        --export zz_0027c34_ \
        --out research/tools/dolphin-trace/plans/gx.zz_0027c34_.json

    # 2. boot Dolphin (capture_oracle.py launch), then
    python capture_gx.py scout --plan <plan> --seconds 60      # does it fire?
    python capture_gx.py capture --plan <plan> --n 8 --out <cap.jsonl>

    # 3. replay
    node research/decomp/oracle-harness/run-gx-callstream.mjs --capture <cap.jsonl>

`surface` is a fourth subcommand that answers a different question: over N
seconds of live play, WHICH GX entry points does the ROM actually call and how
often?  `docs/gx-hle-host.md` §2 says a runtime frequency ranking "requires a
Dolphin trace and does not exist".  This produces it.
"""
from __future__ import annotations

import argparse
import json
import sys
import time
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))

from capture_oracle import (  # noqa: E402
    ASSET_ROOT, DEFAULT_PORT, PAD_INJECT_BP, StubDriver, apply_scenario_setup,
    is_mem1, load_scenario, now_iso, parse_inject_arg, stop_pc,
)
from capture_common import (  # noqa: E402
    Dol, Regs, eabi_allocate, eabi_return, read_arg, s16, swap_elems,
    wasm_signatures,
)
from rsp_client import RspError  # noqa: E402

GX_PLAN_SCHEMA = 1
GX_STREAM_SCHEMA = 1

# The GameCube's write-gather pipe window.  A store whose effective address
# lands here is a FIFO byte write, not a memory write.  The window is 32 bytes
# wide and every offset in it aliases the same pipe.
WGPIPE_LO, WGPIPE_HI = 0xCC008000, 0xCC008020

STORE_OPS = {36: ("stw", 4), 38: ("stb", 1), 44: ("sth", 2), 37: ("stwu", 4)}
FSTORE_OPS = {52: ("stfs", 4), 54: ("stfd", 8)}

# The four wgpipe imports the assembly gate lowers pipe stores to.  They are not
# ROM call sites, so they are excluded when call sites are bound to imports.
WGPIPE_IMPORTS = ("__gf_gx_wgpipe_u8", "__gf_gx_wgpipe_u16",
                  "__gf_gx_wgpipe_u32", "__gf_gx_wgpipe_f32")
WIDTH_TO_WGPIPE = {1: "__gf_gx_wgpipe_u8", 2: "__gf_gx_wgpipe_u16",
                   4: "__gf_gx_wgpipe_u32"}

INVENTORY = (Path(__file__).resolve().parents[2]
             / "decomp" / "data" / "gx-call-inventory.json")


# --------------------------------------------------------------------------
# static decode
# --------------------------------------------------------------------------

def decode_function(dol: Dol, start: int, limit: int = 0x1000) -> dict:
    """Walk a TERMINATING function to its blr, collecting calls and stores.

    Unlike capture_spine's walk this does NOT require straight-line shape: a
    draw function has a guard branch.  Every call and every store is
    breakpointed and the ORDER IS OBSERVED at capture time rather than assumed,
    so a branch is not a problem -- it is data.
    """
    calls: list[dict] = []
    stores: list[dict] = []
    conditionals: list[int] = []
    indirect: list[int] = []
    returns: list[int] = []
    end = None
    for addr in range(start, start + limit, 4):
        w = dol.word(addr)
        if w is None:
            raise SystemExit(f"function walk left mapped ROM at {addr:#010x}")
        op = w >> 26
        if op == 18:                                     # b / bl
            li = w & 0x03FFFFFC
            if li & 0x02000000:
                li -= 0x04000000
            aa, lk = (w >> 1) & 1, w & 1
            target = (li if aa else addr + li) & 0xFFFFFFFF
            if lk:
                calls.append({"at": f"0x{addr:08x}", "target": f"0x{target:08x}"})
        elif op == 19:                                   # bclr / bcctr
            xo, lk = (w >> 1) & 0x3FF, w & 1
            if xo == 16 and not lk:
                returns.append(addr)
                end = addr
                break
            if lk:
                indirect.append(addr)
        elif op == 16:
            conditionals.append(addr)
        elif op in STORE_OPS or op in FSTORE_OPS:
            if addr == start:
                continue                                 # the frame push
            table = STORE_OPS if op in STORE_OPS else FSTORE_OPS
            name, width = table[op]
            rs, ra, d = (w >> 21) & 31, (w >> 16) & 31, s16(w & 0xFFFF)
            if ra == 1:
                # frame bookkeeping (the LR save slot, spilled locals). A
                # console stack address has no counterpart in the wasm module's
                # own linear stack, so it is not part of the comparable stream;
                # capture_spine.py excludes r1-based stores for the same reason.
                continue
            stores.append({"at": f"0x{addr:08x}", "op": name, "width": width,
                           "src_reg": ("f" if op in FSTORE_OPS else "r") + str(rs),
                           "base_reg": f"r{ra}", "disp": d})
    if end is None:
        raise SystemExit(
            f"no blr within {limit} bytes of {start:#010x} -- a nonterminating "
            f"function is capture_spine.py's shape, not this one")
    return {
        "start": f"0x{start:08x}", "end": f"0x{end:08x}",
        "calls": calls, "stores": stores,
        "conditional_branches": [f"0x{a:08x}" for a in conditionals],
        "indirect_calls": [f"0x{a:08x}" for a in indirect],
        "returns": [f"0x{a:08x}" for a in returns],
    }


def load_inventory() -> dict:
    """symbol -> romAddr, from the measured GX call inventory."""
    if not INVENTORY.is_file():
        return {}
    data = json.loads(INVENTORY.read_text(encoding="utf-8-sig"))
    out = {}
    for e in data.get("entries", data.get("inventory", [])):
        sym, addr = e.get("symbol"), e.get("romAddr")
        if sym and addr is not None:
            out[sym] = int(addr) if not isinstance(addr, str) else int(addr, 16)
    return out


def cmd_sites(a: argparse.Namespace) -> int:
    dol = Dol.from_iso(Path(a.iso))
    fn = int(a.fn, 16)
    shape = decode_function(dol, fn)

    imports, exports = wasm_signatures(Path(a.wasm))
    if a.export not in exports:
        sys.exit(f"{a.wasm} does not export {a.export}")
    fn_imports = [i for i in imports if i["name"] not in WGPIPE_IMPORTS]
    pipe_imports = [i["name"] for i in imports if i["name"] in WGPIPE_IMPORTS]

    # Bind ROM call TARGETS to wasm imports by FIRST-USE ORDER.  emcc emits
    # imports in first-use order and the ROM's call order is the source order,
    # so the two sequences are the same sequence.  Verified, not assumed: the
    # DISTINCT-target count must equal the import count, and the resulting
    # (address -> name) map is cross-checked against the measured GX inventory
    # below and written into the plan for review.
    first_use: list[str] = []
    for c in shape["calls"]:
        if c["target"] not in first_use:
            first_use.append(c["target"])
    if len(first_use) != len(fn_imports):
        sys.exit(f"{len(first_use)} distinct ROM call targets but "
                 f"{len(fn_imports)} non-wgpipe wasm imports -- the module is "
                 f"not a single-function build of this function")
    bind = {addr: imp for addr, imp in zip(first_use, fn_imports)}

    inv = load_inventory()
    checked, mismatched = [], []
    for addr, imp in bind.items():
        sym = imp["name"]
        # inventory keys are the bare GX symbol; the shim name is gnt4_<sym>_bl
        bare = sym[len("gnt4_"):-len("_bl")] if sym.startswith("gnt4_") and sym.endswith("_bl") else sym
        for key in (bare, sym):
            if key in inv:
                checked.append(sym)
                if inv[key] != int(addr, 16):
                    mismatched.append({"symbol": sym, "plan": addr,
                                       "inventory": f"0x{inv[key]:08x}"})
                break
    if mismatched:
        sys.exit("first-use binding disagrees with the measured GX inventory: "
                 + json.dumps(mismatched))

    for c in shape["calls"]:
        imp = bind[c["target"]]
        c["callee"] = imp["name"]
        c["wasm_params"] = imp["params"]
        c["args"] = eabi_allocate(imp["params"])
        c["ret"] = eabi_return(imp["results"])

    # stores: classified at CAPTURE time by resolved effective address.  The
    # static pass only records that a store exists and how wide it is; whether
    # it lands on the pipe is a runtime fact (the base register is built by a
    # preceding `addis`), and resolving it live is both simpler and stricter
    # than re-implementing constant propagation here.
    reads = json.loads(Path(a.reads).read_text(encoding="utf-8-sig")) if a.reads else []

    plan = {
        "gx_plan_schema": GX_PLAN_SCHEMA,
        "generated_by": "research/tools/dolphin-trace/capture_gx.py sites",
        "generated_at": now_iso(),
        "function": {"gc_addr": shape["start"], "end": shape["end"],
                     "export": a.export,
                     "params": exports[a.export]["params"],
                     "results": exports[a.export]["results"],
                     "entry_args": eabi_allocate(exports[a.export]["params"])},
        "wasm": a.wasm,
        "shape": shape,
        "binding": {"strategy": "first-use order of distinct ROM call targets "
                                "zipped with the module's non-wgpipe imports",
                    "map": {addr: bind[addr]["name"] for addr in first_use},
                    "cross_checked_against_gx_inventory": sorted(checked)},
        "wgpipe_imports": pipe_imports,
        "wgpipe_window": [f"0x{WGPIPE_LO:08x}", f"0x{WGPIPE_HI:08x}"],
        "reads": reads,
    }
    out = Path(a.out)
    out.parent.mkdir(parents=True, exist_ok=True)
    out.write_text(json.dumps(plan, indent=1) + "\n", encoding="utf-8")
    print(json.dumps({
        "out": str(out), "entry": shape["start"], "blr": shape["end"],
        "call_sites": len(shape["calls"]), "distinct_callees": len(first_use),
        "candidate_stores": len(shape["stores"]),
        "conditional_branches": shape["conditional_branches"],
        "indirect_calls": shape["indirect_calls"],
        "cross_checked_symbols": len(checked),
        "reads": len(reads),
    }, indent=2))
    return 0


# --------------------------------------------------------------------------
# live capture
# --------------------------------------------------------------------------

def resolve_reads(d: StubDriver, reads: list[dict]) -> list[dict]:
    """Resolve a plan's declared read set on the halted console.

    `addr` is literal; `deref` names an earlier read whose VALUE is the base,
    with an optional `+off`.  Bytes are emitted element-wise byte-swapped at
    the declared `elem_width`, the same rule as capture_spine.py -- console RAM
    is big-endian, the wasm arena is little-endian.
    """
    import base64
    out: list[dict] = []
    by_name: dict[str, int] = {}
    for r in reads:
        if "addr" in r:
            addr = int(r["addr"], 16)
        else:
            base = by_name.get(r["deref"])
            if base is None:
                raise RspError(f"read {r['name']} derefs unknown {r['deref']!r}")
            addr = (base + int(r.get("off", 0))) & 0xFFFFFFFF
        if not is_mem1(addr):
            # A deref through a pointer the game has not populated yet (cold
            # boot) is a NORMAL observation, not a capture failure: it is
            # recorded unresolved and seeds nothing.  Refusing here would make
            # every guarded draw path uncapturable from a cold boot.
            out.append({"name": r.get("name", r.get("addr")),
                        "addr": f"0x{addr:08x}", "size": r["size"],
                        "elem_width": int(r.get("elem_width", 4)),
                        "unresolved": True})
            continue
        raw = d.rsp.read_mem(addr, r["size"])
        ew = int(r.get("elem_width", 4))
        rec = {"name": r.get("name", r.get("addr")), "addr": f"0x{addr:08x}",
               "size": r["size"], "elem_width": ew,
               "b64": base64.b64encode(swap_elems(raw, ew)).decode()}
        if r["size"] == 4:
            v = int.from_bytes(raw, "big")
            rec["u32"] = v
            by_name[rec["name"]] = v
        out.append(rec)
    return out


def parse_stage_arg(spec: str | None) -> list[tuple[int, int, int]]:
    """`0x80436108=1,0x803b02c8=0x804020ff:4` -> [(addr, size, value), ..].

    Staging writes GAME STATE, never code: it opens a guard the sampled game
    state does not happen to open so the ROM's OWN draw path executes. It is
    the same move force_navigator.py makes when it re-runs the game's own
    battle load around a chosen roster. Every staged word is recorded in the
    capture header and surfaced by the harness.
    """
    if not spec:
        return []
    out = []
    for part in spec.split(","):
        lhs, _, rhs = part.partition("=")
        if not rhs:
            sys.exit(f"--stage item {part!r} is not ADDR=VALUE[:SIZE]")
        val, _, size = rhs.partition(":")
        addr = int(lhs, 0)
        if not is_mem1(addr):
            sys.exit(f"--stage address {addr:#010x} is outside MEM1")
        out.append((addr, int(size or 4), int(val, 0)))
    return out


def apply_staging(d: StubDriver, staging: list[tuple[int, int, int]]) -> list[dict] | None:
    if not staging:
        return None
    done = []
    for addr, size, value in staging:
        before = d.rsp.read_mem(addr, size)
        d.rsp.write_mem(addr, value.to_bytes(size, "big"))
        done.append({"addr": f"0x{addr:08x}", "size": size,
                     "was": before.hex(), "now": value.to_bytes(size, "big").hex()})
    return done


def classify_arg(value: object, sp: int) -> object:
    """Tag a stack-relative pointer argument; leave everything else verbatim."""
    if isinstance(value, int) and (sp - 0x200) <= value < (sp + 0x4000):
        return {"k": "sp", "off": value - sp}
    return value


def cmd_capture(a: argparse.Namespace) -> int:
    plan = json.loads(Path(a.plan).read_text(encoding="utf-8-sig"))
    if plan.get("gx_plan_schema") != GX_PLAN_SCHEMA:
        sys.exit("plan is not gx_plan_schema 1")
    shape = plan["shape"]
    entry = int(shape["start"], 16)
    blr = int(shape["end"], 16)
    site_by_addr = {int(c["at"], 16): c for c in shape["calls"]}
    store_by_addr = {int(s["at"], 16): s for s in shape["stores"]}

    scenario = load_scenario(a.scenario) if a.scenario else None
    if scenario and not a.inject:
        a.inject = scenario.get("inject")
    injector = parse_inject_arg(a.inject)

    invocations: list[dict] = []
    notes: list[str] = []
    setup_report = None
    current: dict | None = None
    entries_seen = 0
    non_wgpipe_stores = 0
    armed_after_s = None
    staging = parse_stage_arg(a.stage)
    d = StubDriver(a.port)
    t0 = time.monotonic()
    try:
        d.halt()
        setup_report = apply_scenario_setup(scenario, d)

        if a.arm_on:
            # Run the game at FULL SPEED with no breakpoints installed and poll
            # the declared read set until the named read is non-zero.  A draw
            # function behind a guard (a fade, a mode flag) fires constantly but
            # draws nothing until the guard opens, and a breakpoint loop slows
            # emulation by ~15x, so arming by polling is the only way to reach
            # a guarded path inside one boot's single stub connection.
            deadline = time.monotonic() + a.arm_timeout
            while True:
                vals = {r["name"]: r.get("u32")
                        for r in resolve_reads(d, plan.get("reads", []))}
                if vals.get(a.arm_on):
                    armed_after_s = round(time.monotonic() - t0, 1)
                    break
                if time.monotonic() > deadline:
                    notes.append(f"arm-on {a.arm_on!r} never became non-zero in "
                                 f"{a.arm_timeout}s; captured unarmed")
                    break
                d.resume_nowait()
                time.sleep(a.arm_poll)
                d.halt()

        d.set_bp(entry)
        d.set_bp(blr)
        for addr in site_by_addr:
            d.set_bp(addr)
        for addr in store_by_addr:
            d.set_bp(addr)
        if injector is not None:
            d.set_bp(PAD_INJECT_BP)

        deadline = time.monotonic() + a.max_seconds
        while len(invocations) < a.n:
            if time.monotonic() > deadline:
                notes.append(f"capture deadline {a.max_seconds}s hit after "
                             f"{len(invocations)} complete invocation(s)")
                break
            stop = d.cont_until_stop(timeout=a.stop_timeout)
            if stop is None:
                notes.append("stub stop timeout -- the function is not executing")
                break
            pc = stop_pc(stop) or d.rsp.read_pc()
            if injector is not None and pc == PAD_INJECT_BP:
                injector.on_hit(d.rsp)
                continue
            regs = Regs(d.rsp)
            if pc == entry:
                entries_seen += 1
                if current is not None:
                    notes.append(f"re-entered at invocation {len(invocations)} "
                                 f"without reaching the blr -- previous partial "
                                 f"invocation dropped")
                staged = apply_staging(d, staging)
                current = {"kind": "invocation", "n": len(invocations),
                           "entry_sp": f"0x{regs.gpr(1):08x}",
                           "staged": staged,
                           "reads": resolve_reads(d, plan.get("reads", [])),
                           "events": []}
                continue
            if pc == blr:
                if current is None:
                    continue           # attached mid-function; ignore the tail
                current["exit_sp"] = f"0x{regs.gpr(1):08x}"
                invocations.append(current)
                current = None
                continue
            if current is None:
                continue               # events before the first entry we saw
            if pc in site_by_addr:
                site = site_by_addr[pc]
                sp = regs.gpr(1)
                current["events"].append({
                    "k": "call", "at": site["at"], "callee": site["callee"],
                    "callee_addr": site["target"],
                    "args": [classify_arg(read_arg(regs, s), sp)
                             for s in site["args"]],
                })
                continue
            if pc in store_by_addr:
                st = store_by_addr[pc]
                ea = (regs.gpr(int(st["base_reg"][1:])) + st["disp"]) & 0xFFFFFFFF
                if WGPIPE_LO <= ea < WGPIPE_HI:
                    width = st["width"]
                    if st["src_reg"].startswith("f"):
                        notes.append(f"float pipe store at {st['at']} -- not "
                                     f"modelled by this capture")
                        continue
                    raw = regs.gpr(int(st["src_reg"][1:]))
                    value = raw & ((1 << (width * 8)) - 1)
                    current["events"].append({
                        "k": "wgpipe", "at": st["at"], "width": width,
                        "import": WIDTH_TO_WGPIPE[width],
                        "value": value, "ea": f"0x{ea:08x}",
                    })
                else:
                    non_wgpipe_stores += 1
                    current["events"].append({
                        "k": "store", "at": st["at"], "addr": f"0x{ea:08x}",
                        "width": st["width"],
                        "value": (regs.gpr(int(st["src_reg"][1:]))
                                  & ((1 << (st["width"] * 8)) - 1))
                        if not st["src_reg"].startswith("f") else None,
                    })
                continue
            notes.append(f"stray stop at 0x{pc:08x}")
    except (RspError, OSError) as e:
        notes.append(f"stub session died: {e}")
    finally:
        d.cleanup()

    calls = sum(1 for iv in invocations for e in iv["events"] if e["k"] == "call")
    pipes = sum(1 for iv in invocations for e in iv["events"] if e["k"] == "wgpipe")

    header = {
        "kind": "header", "gx_stream_schema": GX_STREAM_SCHEMA,
        "name": a.name,
        "function": {"export": plan["function"]["export"],
                     "gc_addr": plan["function"]["gc_addr"]},
        "wasm": a.wasm_rel,
        "invocations": len(invocations),
        "counts": {"invocation": len(invocations), "call": calls, "wgpipe": pipes,
                   "store": non_wgpipe_stores},
        "binding": plan["binding"],
        "source": {
            "standard": "gx_callstream_green",
            "capture_tool": "research/tools/dolphin-trace/capture_gx.py",
            "control_strategy":
                "breakpoint the function entry, its blr, every bl site and every "
                "store site; each stop appends one ordered event; a store is "
                "classified as a write-gather-pipe write by its RESOLVED "
                "effective address, not by static constant propagation",
            "emulator": "bundled Dolphin 2606-97 (dolphin/Dolphin.exe), "
                        f"{a.gfx_note}, CPU only",
            "stub": f"gdb-rsp 127.0.0.1:{a.port}",
            "dumped_at": now_iso(),
            "game_state": a.game_state,
            "plan": str(Path(a.plan).as_posix()),
            "pad_injection": a.inject or None,
            "injected_frames": injector.frame if injector else 0,
            "scenario": a.scenario or None,
            "scenario_setup": setup_report,
            "entries_seen": entries_seen,
            "armed_on": a.arm_on,
            "armed_after_s": armed_after_s,
            "state_staging": [{"addr": f"0x{ad:08x}", "size": sz,
                               "value": f"0x{v:x}"} for ad, sz, v in staging]
                             or None,
            "exclusions": [
                "NO FRAMEBUFFER IS READ. This capture is the SDK-seam call "
                "stream only; it says nothing about the pixels either side "
                "produces.",
                "a stack-relative pointer argument is recorded as an offset "
                "from r1 and compared structurally, not by value -- the "
                "console stack and the wasm linear stack are different address "
                "spaces",
                "memory reads are limited to the plan's declared read set; a "
                "load the plan does not declare is neither captured nor seeded",
                "the callees themselves are not observed: what a GX entry point "
                "DID with these arguments on the console is outside this capture",
                "input is savestate + synthesized pad injection, not a DTM, so "
                "each capture is a fresh sample rather than a replayable trace",
            ],
            "notes": notes,
            "elapsed_s": round(time.monotonic() - t0, 1),
        },
    }
    out = Path(a.out)
    out.parent.mkdir(parents=True, exist_ok=True)
    with out.open("w", encoding="utf-8", newline="\n") as f:
        f.write(json.dumps(header) + "\n")
        for iv in invocations:
            f.write(json.dumps(iv) + "\n")
    print(json.dumps({"out": str(out), "invocations": len(invocations),
                      "calls": calls, "wgpipe_writes": pipes,
                      "other_stores": non_wgpipe_stores,
                      "entries_seen": entries_seen, "notes": notes,
                      "elapsed_s": round(time.monotonic() - t0, 1)}, indent=2))
    return 0 if invocations and not notes else 1


# --------------------------------------------------------------------------
# scout: does this function fire at all in the current game state?
# --------------------------------------------------------------------------

def cmd_scout(a: argparse.Namespace) -> int:
    plan = json.loads(Path(a.plan).read_text(encoding="utf-8-sig"))
    entry = int(plan["shape"]["start"], 16)
    scenario = load_scenario(a.scenario) if a.scenario else None
    if scenario and not a.inject:
        a.inject = scenario.get("inject")
    injector = parse_inject_arg(a.inject)
    hits = 0
    reads: list[dict] = []
    guard_samples: list[dict] = []
    notes: list[str] = []
    stops = 0
    last_pc = None
    d = StubDriver(a.port)
    t0 = time.monotonic()
    try:
        d.halt()
        apply_scenario_setup(scenario, d)
        d.set_bp(entry)
        if injector is not None:
            d.set_bp(PAD_INJECT_BP)
        deadline = time.monotonic() + a.seconds
        while time.monotonic() < deadline:
            stop = d.cont_until_stop(timeout=min(10.0, max(0.5, deadline - time.monotonic())))
            if stop is None:
                continue
            pc = stop_pc(stop) or d.rsp.read_pc()
            if injector is not None and pc == PAD_INJECT_BP:
                injector.on_hit(d.rsp)
                continue
            stops += 1
            last_pc = pc
            if pc == entry:
                hits += 1
                if hits <= a.sample or not reads:
                    try:
                        r = resolve_reads(d, plan.get("reads", []))
                        if not reads:
                            reads = r
                        guard_samples.append(
                            {"hit": hits,
                             "u32": {x["name"]: x.get("u32") for x in r}})
                    except RspError as e:
                        notes.append(str(e))
    except (RspError, OSError) as e:
        notes.append(f"stub session died: {e} "
                     f"(stops={stops}, last_pc={last_pc and hex(last_pc)})")
    finally:
        d.cleanup()
    print(json.dumps({"entry": plan["shape"]["start"], "hits": hits,
                      "stops": stops,
                      "seconds": round(time.monotonic() - t0, 1),
                      "guard_samples": guard_samples[-8:],
                      "first_reads": reads, "notes": notes}, indent=2))
    return 0 if hits else 1


# --------------------------------------------------------------------------
# surface: the RUNTIME GX call frequency the host doc says does not exist
# --------------------------------------------------------------------------

def cmd_surface(a: argparse.Namespace) -> int:
    """Breakpoint every measured GX entry point and count live calls.

    docs/gx-hle-host.md §2 ranks the GX surface by STATIC call sites and says a
    per-frame frequency ranking "requires a Dolphin trace and does not exist".
    This is that trace.  It also records, per entry point, the DISTINCT ARGUMENT
    TUPLES the ROM actually passes -- which is the cheapest evidence available
    about the enum values §4.1 still labels [SDK].
    """
    inv = json.loads(INVENTORY.read_text(encoding="utf-8-sig"))
    entries = inv.get("entries", inv.get("inventory", []))
    sel = {}
    for e in entries:
        sym = e["symbol"]
        addr = e["romAddr"] if not isinstance(e["romAddr"], str) else int(e["romAddr"], 16)
        if a.only and sym not in a.only.split(","):
            continue
        sel[int(addr)] = sym
    if a.max_symbols and len(sel) > a.max_symbols:
        # keep the most-called-by-static-sites first
        ranked = sorted(entries, key=lambda e: -e.get("gameCalls", 0))
        keep = set()
        for e in ranked:
            addr = e["romAddr"] if not isinstance(e["romAddr"], str) else int(e["romAddr"], 16)
            if int(addr) in sel:
                keep.add(int(addr))
            if len(keep) >= a.max_symbols:
                break
        sel = {k: v for k, v in sel.items() if k in keep}

    # argument shapes come from the SDK's decompiled prototypes only where we
    # have them; without a signature we still record the first 8 GPRs, which is
    # a superset and is labelled as such.
    scenario = load_scenario(a.scenario) if a.scenario else None
    if scenario and not a.inject:
        a.inject = scenario.get("inject")
    injector = parse_inject_arg(a.inject)

    counts: dict[str, int] = {}
    tuples: dict[str, dict[str, int]] = {}
    order: list[str] = []
    notes: list[str] = []
    d = StubDriver(a.port)
    t0 = time.monotonic()
    try:
        d.halt()
        apply_scenario_setup(scenario, d)
        for addr in sel:
            d.set_bp(addr)
        if injector is not None:
            d.set_bp(PAD_INJECT_BP)
        deadline = time.monotonic() + a.seconds
        while time.monotonic() < deadline:
            stop = d.cont_until_stop(timeout=min(10.0, max(0.5, deadline - time.monotonic())))
            if stop is None:
                continue
            pc = stop_pc(stop) or d.rsp.read_pc()
            if injector is not None and pc == PAD_INJECT_BP:
                injector.on_hit(d.rsp)
                continue
            sym = sel.get(pc)
            if sym is None:
                continue
            counts[sym] = counts.get(sym, 0) + 1
            if len(order) < a.max_order:
                order.append(sym)
            if a.args:
                regs = Regs(d.rsp)
                key = ",".join(f"0x{regs.gpr(3 + i):x}" for i in range(a.args))
                tuples.setdefault(sym, {})
                tuples[sym][key] = tuples[sym].get(key, 0) + 1
    except (RspError, OSError) as e:
        notes.append(f"stub session died: {e}")
    finally:
        d.cleanup()

    payload = {
        "gx_surface_schema": 1,
        "generated_by": "research/tools/dolphin-trace/capture_gx.py surface",
        "generated_at": now_iso(),
        "seconds": round(time.monotonic() - t0, 1),
        "game_state": a.game_state,
        "scenario": a.scenario,
        "symbols_breakpointed": len(sel),
        "total_calls": sum(counts.values()),
        "by_symbol": dict(sorted(counts.items(), key=lambda kv: -kv[1])),
        "first_calls_in_order": order,
        "arg_tuples": {k: dict(sorted(v.items(), key=lambda kv: -kv[1])[:a.max_tuples])
                       for k, v in tuples.items()},
        "arg_note": f"r3..r{2 + a.args} at entry, verbatim; a GX entry point "
                    f"taking fewer arguments carries residue in the rest",
        "claim": {
            "verifies": ["which GX entry points the ROM calls at runtime, in "
                         "this game state, and how often",
                         "the argument VALUES the ROM passes to them"],
            "does_not_verify": ["anything about what the host does with them",
                                "any pixel",
                                "coverage outside the sampled game state"],
        },
        "notes": notes,
    }
    out = Path(a.out)
    out.parent.mkdir(parents=True, exist_ok=True)
    out.write_text(json.dumps(payload, indent=1) + "\n", encoding="utf-8")
    print(json.dumps({"out": str(out), "symbols": len(sel),
                      "total_calls": payload["total_calls"],
                      "distinct": len(counts), "notes": notes,
                      "seconds": payload["seconds"]}, indent=2))
    return 0 if counts else 1



# --------------------------------------------------------------------------
# framebuffer: the console's EXTERNAL FRAMEBUFFER, out of emulated RAM
# --------------------------------------------------------------------------

# gnt4_VISetNextFrameBuffer @0x80212284 -- the SDK call that hands the video
# interface the next XFB. Its r3 IS the framebuffer address, which matters
# because Dolphin's GDB stub REFUSES the hardware window (measured on this rig:
# `m cc00201c,4 -> E00`), so the VI registers that normally hold it cannot be
# read. The ROM knows the address; ask the ROM.
VI_SET_NEXT_FRAMEBUFFER = 0x80212284


def cmd_framebuffer(a: argparse.Namespace) -> int:
    """Dump one console XFB.

    REQUIRES the Software Renderer video backend. Measured on this rig: with the
    default/Null backends both XFBs read back as 4096/4096 ZERO bytes, because
    Dolphin keeps XFB copies host-side; with
    `--config Dolphin.Core.GFXBackend="Software Renderer"` the same addresses
    hold real YUYV 4:2:2. The software renderer is a CPU rasterizer, so this
    respects the rig's GPU-lease rule exactly as the Null backend does.
    """
    import base64
    scenario = load_scenario(a.scenario) if a.scenario else None
    if scenario and not a.inject:
        a.inject = scenario.get("inject")
    injector = parse_inject_arg(a.inject)
    staging = parse_stage_arg(a.stage)
    fn = int(a.fn, 16) if a.fn else None

    notes: list[str] = []
    hits = 0
    dump = None
    staged_report = None
    stage_hits = 0
    d = StubDriver(a.port)
    t0 = time.monotonic()
    try:
        d.halt()
        apply_scenario_setup(scenario, d)
        d.set_bp(VI_SET_NEXT_FRAMEBUFFER)
        if fn is not None:
            d.set_bp(fn)
        if injector is not None:
            d.set_bp(PAD_INJECT_BP)
        deadline = time.monotonic() + a.max_seconds
        while dump is None and time.monotonic() < deadline:
            stop = d.cont_until_stop(timeout=a.stop_timeout)
            if stop is None:
                notes.append("stub stop timeout waiting for a frame")
                break
            pc = stop_pc(stop) or d.rsp.read_pc()
            if injector is not None and pc == PAD_INJECT_BP:
                injector.on_hit(d.rsp)
                continue
            if fn is not None and pc == fn:
                rep = apply_staging(d, staging)
                if rep and staged_report is None:
                    staged_report = rep
                stage_hits += 1
                continue
            if pc != VI_SET_NEXT_FRAMEBUFFER:
                continue
            hits += 1
            if hits <= a.settle:
                continue
            base = d.rsp.read_gpr(3)
            if not is_mem1(base):
                notes.append(f"XFB pointer {base:#010x} is outside MEM1")
                break
            size = a.width * a.height * 2
            buf = bytearray()
            while len(buf) < size:
                n = min(a.chunk, size - len(buf))
                buf += d.rsp.read_mem(base + len(buf), n)
            dump = {"addr": f"0x{base:08x}", "vi_hit": hits,
                    "width": a.width, "height": a.height,
                    "format": "YUY2 4:2:2, 2 bytes per pixel, BT.601 studio swing",
                    "b64": base64.b64encode(bytes(buf)).decode()}
    except (RspError, OSError) as e:
        notes.append(f"stub session died: {e}")
    finally:
        d.cleanup()

    payload = {
        "gx_framebuffer_schema": 1,
        "generated_by": "research/tools/dolphin-trace/capture_gx.py framebuffer",
        "generated_at": now_iso(),
        "label": a.label,
        "frame": dump,
        "source": {
            "emulator": "bundled Dolphin 2606-97 (dolphin/Dolphin.exe), "
                        "Software Renderer (CPU), CPU only",
            "xfb_located_via": "gnt4_VISetNextFrameBuffer @0x80212284, r3 -- "
                               "Dolphin's GDB stub refuses the 0xCC000000 "
                               "hardware window, so the VI registers are not readable",
            "save_state": a.save_state,
            "scenario": a.scenario,
            "game_state": a.game_state,
            "settle_frames": a.settle,
            "state_staging": [{"addr": f"0x{ad:08x}", "size": sz, "value": f"0x{v:x}"}
                              for ad, sz, v in staging] or None,
            "staged_at": f"0x{fn:08x}" if fn is not None else None,
            "staging_applications": stage_hits,
            "first_staging_report": staged_report,
            "elapsed_s": round(time.monotonic() - t0, 1),
            "notes": notes,
        },
    }
    out = Path(a.out)
    out.parent.mkdir(parents=True, exist_ok=True)
    out.write_text(json.dumps(payload, indent=1) + chr(10), encoding="utf-8")
    print(json.dumps({"out": str(out), "captured": dump is not None,
                      "addr": dump and dump["addr"], "vi_hits": hits,
                      "staging_applications": stage_hits, "notes": notes,
                      "elapsed_s": round(time.monotonic() - t0, 1)}, indent=2))
    return 0 if dump else 1


# --------------------------------------------------------------------------

def main() -> int:
    p = argparse.ArgumentParser(
        description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    sub = p.add_subparsers(dest="cmd")
    sub.required = True

    sp = sub.add_parser("sites", help="decode the function + bind it to the module ABI")
    sp.add_argument("--fn", required=True, help="hex GC address, e.g. 0x80027c34")
    sp.add_argument("--wasm", required=True)
    sp.add_argument("--export", required=True)
    sp.add_argument("--reads", default=None,
                    help="JSON list of the function's declared read set")
    sp.add_argument("--iso", default=str(ASSET_ROOT / "Gotcha Force.iso"))
    sp.add_argument("--out", required=True)
    sp.set_defaults(func=cmd_sites)

    sc = sub.add_parser("scout", help="does the function fire in this game state?")
    sc.add_argument("--plan", required=True)
    sc.add_argument("--seconds", type=float, default=60.0)
    sc.add_argument("--sample", type=int, default=64,
                    help="resolve the declared read set on this many hits")
    sc.add_argument("--inject", default=None)
    sc.add_argument("--scenario", default=None)
    sc.add_argument("--port", type=int, default=DEFAULT_PORT)
    sc.set_defaults(func=cmd_scout)

    cp = sub.add_parser("capture", help="record N invocations of the call stream")
    cp.add_argument("--plan", required=True)
    cp.add_argument("--n", type=int, default=8)
    cp.add_argument("--out", required=True)
    cp.add_argument("--name", default="gx-rom-unit")
    cp.add_argument("--wasm-rel",
                    default="../../../../packages/rom-runtime/test/fixtures/gx-rom-unit/gx_rom_unit.threads.wasm",
                    help="header `wasm`: path RELATIVE TO THE CAPTURE FILE, whose home is research/decomp/oracle-harness/corpora/")
    cp.add_argument("--arm-on", default=None,
                    help="run at full speed until this named read is non-zero, "
                         "THEN install breakpoints (for guarded draw paths)")
    cp.add_argument("--arm-poll", type=float, default=0.2)
    cp.add_argument("--arm-timeout", type=float, default=240.0)
    cp.add_argument("--stage", default=None,
                    help="ADDR=VALUE[:SIZE] words poked at every function "
                         "entry, e.g. 0x80436108=1. DISCLOSED in the capture "
                         "header as source.state_staging and reported by the "
                         "harness -- a staged capture is a weaker observation "
                         "than an unstaged one")
    cp.add_argument("--stop-timeout", type=float, default=30.0)
    cp.add_argument("--max-seconds", type=float, default=600.0)
    cp.add_argument("--game-state", default="unspecified")
    cp.add_argument("--gfx-note", default="Null video backend")
    cp.add_argument("--inject", default=None)
    cp.add_argument("--scenario", default=None)
    cp.add_argument("--port", type=int, default=DEFAULT_PORT)
    cp.set_defaults(func=cmd_capture)

    su = sub.add_parser("surface", help="live GX entry-point frequency + argument tuples")
    su.add_argument("--seconds", type=float, default=60.0)
    su.add_argument("--out", required=True)
    su.add_argument("--only", default=None, help="comma-separated symbol allowlist")
    su.add_argument("--max-symbols", type=int, default=0)
    su.add_argument("--args", type=int, default=0,
                    help="record this many GPR arguments per call (0 = none)")
    su.add_argument("--max-tuples", type=int, default=40)
    su.add_argument("--max-order", type=int, default=4000)
    su.add_argument("--game-state", default="unspecified")
    su.add_argument("--inject", default=None)
    su.add_argument("--scenario", default=None)
    su.add_argument("--port", type=int, default=DEFAULT_PORT)
    su.set_defaults(func=cmd_surface)

    fb = sub.add_parser("framebuffer", help="dump one console XFB out of emulated RAM")
    fb.add_argument("--out", required=True)
    fb.add_argument("--label", default="control")
    fb.add_argument("--settle", type=int, default=4,
                    help="skip this many VISetNextFrameBuffer hits before dumping")
    fb.add_argument("--width", type=int, default=640)
    fb.add_argument("--height", type=int, default=480)
    fb.add_argument("--chunk", type=int, default=4096)
    fb.add_argument("--fn", default=None,
                    help="also breakpoint this function and apply --stage at its entry")
    fb.add_argument("--stage", default=None)
    fb.add_argument("--save-state", default=None, help="recorded in the artifact only")
    fb.add_argument("--game-state", default="unspecified")
    fb.add_argument("--stop-timeout", type=float, default=30.0)
    fb.add_argument("--max-seconds", type=float, default=180.0)
    fb.add_argument("--inject", default=None)
    fb.add_argument("--scenario", default=None)
    fb.add_argument("--port", type=int, default=DEFAULT_PORT)
    fb.set_defaults(func=cmd_framebuffer)

    a = p.parse_args()
    return a.func(a)


if __name__ == "__main__":
    raise SystemExit(main())
