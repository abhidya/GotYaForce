#!/usr/bin/env python3
"""capture_spine.py -- boundary_green capture for NONTERMINATING spine functions.

Design step I3 (docs/playable-port-design.md V5, "Spine verification:
oracle_green is unreachable for nonterminating functions").

Why this file exists next to capture_oracle.py
----------------------------------------------
`capture_oracle.py capture` implements the oracle_green standard: break on a
function's ENTRY, snapshot args, **run to the caller's return address**, snapshot
the return value and the write set.  That control strategy is structurally
impossible for a spine:

    zz_00527d8_ / run_main_game_loop @ 0x800527d8   do { ...17 calls... } while(true)

there is no return.  `capture_one_hit`'s `d.set_bp(lr); cont_until_stop(...)`
would sit at the LR breakpoint until `--ret-timeout` and score every attempt a
miss, forever.

The boundary_green control strategy instead
-------------------------------------------
A spine body is (by the definition that makes it a spine) a straight run of
out-of-unit calls.  Every instruction in it is therefore either a call, a
spine-owned store, or the loop's back edge -- a handful of addresses.  So:

  **breakpoint EVERY instruction of the spine body and walk the loop.**

That is cheap (21 addresses for `run_main_game_loop`) and it makes the capture a
complete instruction-level trace of the spine while the callees still run at
native JIT speed.  Each stop closes the previous instruction and opens the
current one, because the spine's instructions are contiguous:

    stop at S_i        -> callee i-1 has RETURNED (read its return regs)
                          and callee i is ABOUT TO BE CALLED (read its arg regs
                          and the owned-region bytes: the harness's `owned`
                          check fires on call arrival, before deltas apply)
    stop at the store  -> read the value the spine is about to write
    stop at the back edge -> one iteration closed; K of these ends the capture

Termination is by ITERATION COUNT, which is exactly the `call_cap` terminator
`run-spine.mjs` implements: the harness services the captured calls and cuts the
run on the next incoming call, so the wasm spine "looping onward" is itself
asserted rather than being a hang.

Where the arg register map comes from
-------------------------------------
The harness compares the wasm's actual call arguments against the capture, so
the capture must bind to the SAME ABI the wasm module declares.  We do not
hand-author that: `sites` reads the built module's import section, takes each
callee's wasm signature (which emcc induced from the VERBATIM Ghidra call site),
and runs the PowerPC EABI argument allocator over it -- f32/f64 -> f1..f8 in
order, i32 -> r3..r10 in order, i64 -> an (odd,even) GPR pair, overflow -> the
caller's outgoing parameter area at r1+8.  Both sides therefore derive from one
C declaration, and the mapping is written into the plan so it is auditable.

Endianness
----------
Console RAM is big-endian PowerPC; the wasm arena is little-endian.  Owned-region
and delta bytes are therefore emitted ELEMENT-WISE byte-swapped at the region's
declared `elem_width`, the same rule as
research/decomp/oracle-harness/gen_arena_rom_provenance.py.  Register VALUES need
no swap -- they are read as integers, not bytes.

Declared limits (recorded in the capture header as `exclusions`)
----------------------------------------------------------------
* **Memory deltas are watch-set-scoped.**  A full MEM1 diff is 24 MB per
  boundary over a GDB-RSP socket; nothing like that can run at frame rate.  The
  capture records byte deltas only over regions the plan declares.  Everything
  else is an explicit stub exclusion.  For `run_main_game_loop` this costs
  nothing measurable: its loop body contains ZERO loads, so no callee write can
  change what the spine itself does.
* **Stack is excluded.**  The wasm module has its own linear stack at its own
  addresses; console stack addresses are not comparable.
* **`K` is not owner-approved.**  I3's gate says "K owner-approved iterations".
  A capture taken without an owner in the loop records `k_owner_approved: false`.

Usage
-----
    # 1. derive the spine's instruction plan from the ROM + the built module
    python capture_spine.py sites --spine 0x800527d8 \
        --wasm research/decomp/spine-boundary/unit.wasm \
        --export zz_00527d8_ \
        --out research/tools/dolphin-trace/plans/spine.0x800527d8.json

    # 2. boot Dolphin (capture_oracle.py launch; COLD boot -- see --from-entry)
    # 3. capture K iterations
    python capture_spine.py capture --plan <plan> --iterations 16 \
        --from-entry --out <out.jsonl>

`--from-entry` is normally REQUIRED for a complete capture: a spine's entry
arguments are only observable at the one moment it is entered, which for
`run_main_game_loop` is once per boot.  Attaching to a savestate lands mid-loop,
where entry params that are not re-passed to any in-loop callee are unbound.
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
    ASSET_ROOT, DEFAULT_PORT, PAD_INJECT_BP, StubDriver, apply_scenario_setup,
    is_mem1, load_scenario, now_iso, parse_inject_arg, stop_pc,
)
from rsp_client import RspError  # noqa: E402

SPINE_SCHEMA = 1


# --------------------------------------------------------------------------
# ROM reader: the DOL straight out of the retail ISO (no extracted copy needed)
# --------------------------------------------------------------------------

class Dol:
    """boot.dol section table + address->bytes reads."""

    def __init__(self, blob: bytes):
        self.blob = blob
        offs = struct.unpack(">18I", blob[0x00:0x48])
        adrs = struct.unpack(">18I", blob[0x48:0x90])
        szs = struct.unpack(">18I", blob[0x90:0xD8])
        self.sections = [(offs[i], adrs[i], szs[i]) for i in range(18) if szs[i]]

    @classmethod
    def from_iso(cls, iso_path: Path) -> "Dol":
        """GameCube GCM: the DOL's file offset is the BE u32 at 0x420."""
        with iso_path.open("rb") as f:
            f.seek(0x420)
            dol_off = struct.unpack(">I", f.read(4))[0]
            f.seek(dol_off)
            head = f.read(0x100)
            offs = struct.unpack(">18I", head[0x00:0x48])
            szs = struct.unpack(">18I", head[0x90:0xD8])
            size = max(o + s for o, s in zip(offs, szs) if s)
            f.seek(dol_off)
            return cls(f.read(size))

    def word(self, addr: int) -> int | None:
        for off, ad, sz in self.sections:
            if ad <= addr < ad + sz:
                o = off + (addr - ad)
                return struct.unpack(">I", self.blob[o:o + 4])[0]
        return None


def s16(v: int) -> int:
    return v - 0x10000 if v & 0x8000 else v


# --------------------------------------------------------------------------
# spine decode
# --------------------------------------------------------------------------

STORE_OPS = {36: ("stw", 4), 38: ("stb", 1), 44: ("sth", 2), 37: ("stwu", 4)}


def decode_spine(dol: Dol, start: int, limit: int = 0x400) -> dict:
    """Walk the spine's instructions to its back edge.

    Returns every call site, every store, and every control-flow instruction,
    so a spine that is NOT a straight-line loop reports itself rather than
    being silently mis-captured.
    """
    calls: list[dict] = []
    stores: list[dict] = []
    conditionals: list[int] = []
    indirect: list[int] = []
    back_edge = None
    returns: list[int] = []
    for addr in range(start, start + limit, 4):
        w = dol.word(addr)
        if w is None:
            raise SystemExit(f"spine walk left mapped ROM at {addr:#010x}")
        op = w >> 26
        if op == 18:                                    # b / bl / ba / bla
            li = w & 0x03FFFFFC
            if li & 0x02000000:
                li -= 0x04000000
            aa, lk = (w >> 1) & 1, w & 1
            target = (li if aa else addr + li) & 0xFFFFFFFF
            if lk:
                calls.append({"at": f"0x{addr:08x}", "target": f"0x{target:08x}"})
            elif target <= addr:
                back_edge = {"at": f"0x{addr:08x}", "target": f"0x{target:08x}"}
                break
            else:
                raise SystemExit(
                    f"forward unconditional branch at {addr:#010x} -- the spine "
                    f"is not a single straight-line loop; capture_spine's "
                    f"walk-every-instruction strategy does not model it")
        elif op == 19:                                  # bclr / bcctr
            xo, lk = (w >> 1) & 0x3FF, w & 1
            if xo == 16 and not lk:
                returns.append(addr)
                break
            if lk:
                indirect.append(addr)
        elif op == 16:                                  # bc
            conditionals.append(addr)
        elif op in STORE_OPS and addr != start:
            # skip the `stwu r1,-N(r1)` frame push at the entry
            name, width = STORE_OPS[op]
            rs, ra, d = (w >> 21) & 31, (w >> 16) & 31, s16(w & 0xFFFF)
            if ra == 1:
                continue                                # stack slot, not owned state
            stores.append({"at": f"0x{addr:08x}", "op": name, "width": width,
                           "src_reg": f"r{rs}",
                           "addr_expr": f"r{ra}{d:+#x}"})
    if back_edge is None:
        raise SystemExit(
            f"no backward branch within {limit} bytes of {start:#010x} -- this "
            f"function terminates, so it is an oracle_green target "
            f"(capture_oracle.py), not a boundary_green one")
    loop_head = int(back_edge["target"], 16)
    return {
        "start": f"0x{start:08x}",
        "loop_head": f"0x{loop_head:08x}",
        "back_edge": back_edge,
        "prologue_calls": [c for c in calls if int(c["at"], 16) < loop_head],
        "loop_calls": [c for c in calls if int(c["at"], 16) >= loop_head],
        "stores": stores,
        "conditional_branches": [f"0x{a:08x}" for a in conditionals],
        "indirect_calls": [f"0x{a:08x}" for a in indirect],
        "returns": [f"0x{a:08x}" for a in returns],
    }


# --------------------------------------------------------------------------
# wasm import signatures + PowerPC EABI argument allocation
# --------------------------------------------------------------------------

VALTYPE = {0x7F: "i32", 0x7E: "i64", 0x7D: "f32", 0x7C: "f64"}


def wasm_signatures(path: Path) -> tuple[list[dict], dict]:
    """(imported functions in module order, {export name: signature})."""
    b = path.read_bytes()
    p = 8

    def leb() -> int:
        nonlocal p
        r = s = 0
        while True:
            x = b[p]
            p += 1
            r |= (x & 0x7F) << s
            s += 7
            if not x & 0x80:
                return r

    def name() -> str:
        n = leb()
        nonlocal p
        v = b[p:p + n].decode()
        p += n
        return v

    def limits() -> None:
        f = leb()
        leb()
        if f & 1:
            leb()

    types: list[dict] = []
    imports: list[dict] = []
    funcs: list[int] = []
    exports: dict = {}
    while p < len(b):
        sid = b[p]
        p += 1
        end = leb() + p
        if sid == 1:
            for _ in range(leb()):
                assert b[p] == 0x60
                p += 1
                na = leb()
                par = [VALTYPE[b[p + i]] for i in range(na)]
                p += na
                nr = leb()
                res = [VALTYPE[b[p + i]] for i in range(nr)]
                p += nr
                types.append({"params": par, "results": res})
        elif sid == 2:
            for _ in range(leb()):
                mod, fld = name(), name()
                k = b[p]
                p += 1
                if k == 0:
                    imports.append({"module": mod, "name": fld, "type": leb()})
                elif k == 1:
                    p += 1
                    limits()
                elif k == 2:
                    limits()
                elif k == 3:
                    p += 2
        elif sid == 3:
            funcs = [leb() for _ in range(leb())]
        elif sid == 7:
            for _ in range(leb()):
                nm = name()
                k = b[p]
                p += 1
                idx = leb()
                if k == 0:
                    ti = (imports[idx]["type"] if idx < len(imports)
                          else funcs[idx - len(imports)])
                    exports[nm] = types[ti]
        p = end
    out = [{"module": i["module"], "name": i["name"], **types[i["type"]]}
           for i in imports]
    return out, exports


def eabi_allocate(params: list[str]) -> list[dict]:
    """PowerPC EABI outgoing-argument allocation for one signature.

    f32/f64 -> f1..f8 in declaration order; i32 -> r3..r10 in declaration
    order; i64 -> an (odd,even) GPR pair (r3:r4, r5:r6, r7:r8, r9:r10), hi
    first; anything that overflows goes to the caller's outgoing parameter
    area, which begins at r1+8 in the caller's own frame.
    """
    gpr, fpr, stk = 3, 1, 8
    out = []
    for i, t in enumerate(params):
        if t in ("f32", "f64"):
            if fpr <= 8:
                out.append({"i": i, "t": t, "src": f"f{fpr}"})
                fpr += 1
            else:
                stk = (stk + 7) & ~7
                out.append({"i": i, "t": t, "src": f"stack+{stk}"})
                stk += 8
        elif t == "i64":
            if gpr % 2 == 0:
                gpr += 1
            if gpr + 1 <= 10:
                out.append({"i": i, "t": t, "src": f"r{gpr}:r{gpr + 1}"})
                gpr += 2
            else:
                stk = (stk + 7) & ~7
                out.append({"i": i, "t": t, "src": f"stack+{stk}"})
                stk += 8
        else:
            if gpr <= 10:
                out.append({"i": i, "t": t, "src": f"r{gpr}"})
                gpr += 1
            else:
                out.append({"i": i, "t": t, "src": f"stack+{stk}"})
                stk += 4
    return out


def eabi_return(results: list[str]) -> dict | None:
    if not results:
        return None
    t = results[0]
    if t in ("f32", "f64"):
        return {"t": t, "src": "f1"}
    if t == "i64":
        return {"t": t, "src": "r3:r4"}
    return {"t": t, "src": "r3"}


# --------------------------------------------------------------------------
# sites
# --------------------------------------------------------------------------

def cmd_sites(a: argparse.Namespace) -> int:
    dol = Dol.from_iso(Path(a.iso))
    spine = int(a.spine, 16)
    shape = decode_spine(dol, spine)

    imports, exports = wasm_signatures(Path(a.wasm))
    by_name = {i["name"]: i for i in imports}
    if a.export not in exports:
        sys.exit(f"{a.wasm} does not export {a.export}")

    # bind each ROM call site to the module import at the same ordinal --
    # emcc emits imports in first-use order, which for a straight-line spine is
    # exactly the ROM's call order.  Verified rather than assumed: the counts
    # must agree, and the sequence is written into the plan for review.
    ordered = shape["prologue_calls"] + shape["loop_calls"]
    if len(ordered) != len(imports):
        sys.exit(f"{len(ordered)} ROM call sites but {len(imports)} wasm "
                 f"imports -- the module is not a single-function spine build")
    for site, imp in zip(ordered, imports):
        site["callee"] = imp["name"]
        site["wasm_params"] = imp["params"]
        site["wasm_results"] = imp["results"]
        site["args"] = eabi_allocate(imp["params"])
        site["ret"] = eabi_return(imp["results"])

    owned = []
    for st in shape["stores"]:
        owned.append({"store_at": st["at"], "addr_expr": st["addr_expr"],
                      "src_reg": st["src_reg"], "size": st["width"],
                      "elem_width": st["width"]})

    plan = {
        "spine_plan_schema": SPINE_SCHEMA,
        "generated_by": "research/tools/dolphin-trace/capture_spine.py sites",
        "generated_at": now_iso(),
        "spine": {"gc_addr": shape["start"], "export": a.export,
                  "params": exports[a.export]["params"],
                  "results": exports[a.export]["results"],
                  "entry_args": eabi_allocate(exports[a.export]["params"])},
        "wasm": a.wasm,
        "shape": shape,
        "calls_per_iteration": len(shape["loop_calls"]),
        "prologue_calls": len(shape["prologue_calls"]),
        "owned_writes": owned,
        "watch": [],   # extra non-owned regions to diff; see --watch on capture
    }
    out = Path(a.out)
    out.parent.mkdir(parents=True, exist_ok=True)
    out.write_text(json.dumps(plan, indent=1) + "\n", encoding="utf-8")
    print(json.dumps({
        "out": str(out),
        "loop_head": shape["loop_head"],
        "back_edge": shape["back_edge"]["at"],
        "prologue_calls": len(shape["prologue_calls"]),
        "calls_per_iteration": len(shape["loop_calls"]),
        "owned_writes": [o["addr_expr"] for o in owned],
        "conditional_branches": shape["conditional_branches"],
        "indirect_calls": shape["indirect_calls"],
        "straight_line": not shape["conditional_branches"] and not shape["indirect_calls"],
    }, indent=2))
    return 0


# --------------------------------------------------------------------------
# capture
# --------------------------------------------------------------------------

def swap_elems(raw: bytes, elem_width: int) -> bytes:
    if elem_width <= 1:
        return raw
    return b"".join(raw[i:i + elem_width][::-1]
                    for i in range(0, len(raw), elem_width))


class Regs:
    """Lazily-read register file for one halted stop."""

    def __init__(self, rsp):
        self.rsp = rsp
        self._g: dict[int, int] = {}
        self._f: dict[int, int] = {}

    def gpr(self, n: int) -> int:
        if n not in self._g:
            self._g[n] = self.rsp.read_gpr(n) & 0xFFFFFFFF
        return self._g[n]

    def fpr_bits(self, n: int) -> int:
        if n not in self._f:
            self._f[n] = self.rsp.read_fpr_raw(n)
        return self._f[n]


def box_float(v: float, t: str) -> object:
    """JSON has no NaN/Infinity, and a PPC argument register full of residue is
    routinely one of them.  A non-finite float is therefore carried BOXED and
    bit-exact -- {"t":"f64","bits":"<hex>"} -- which spine_schema 1 defines and
    run-spine.mjs unboxes.  Finite values stay plain JSON numbers so a capture
    is still readable."""
    if v == v and v not in (float("inf"), float("-inf")):
        return v
    if t == "f32":
        return {"t": "f32", "bits": f"{struct.unpack('>I', struct.pack('>f', v))[0]:08x}"}
    return {"t": "f64", "bits": f"{struct.unpack('>Q', struct.pack('>d', v))[0]:016x}"}


def read_arg(regs: Regs, spec: dict) -> object:
    src, t = spec["src"], spec["t"]
    if src.startswith("stack+"):
        off = int(src.split("+")[1])
        raw = regs.rsp.read_mem((regs.gpr(1) + off) & 0xFFFFFFFF,
                                8 if t in ("f64", "i64") else 4)
        if t == "f64":
            return box_float(struct.unpack(">d", raw)[0], "f64")
        if t == "f32":
            return box_float(struct.unpack(">f", raw[:4])[0], "f32")
        if t == "i64":
            return str(struct.unpack(">Q", raw)[0])
        return struct.unpack(">I", raw[:4])[0]
    if src.startswith("f"):
        bits = regs.fpr_bits(int(src[1:]))
        dv = struct.unpack(">d", struct.pack(">Q", bits))[0]
        if t == "f32":
            # a PPC FPR always holds a double; a single-precision arg is that
            # double rounded to f32 by the callee's own convention
            return box_float(struct.unpack(">f", struct.pack(">f", dv))[0], "f32")
        return box_float(dv, "f64")
    if ":" in src:                                   # i64 register pair, hi:lo
        hi, lo = (int(x[1:]) for x in src.split(":"))
        return str(((regs.gpr(hi) << 32) | regs.gpr(lo)) & 0xFFFFFFFFFFFFFFFF)
    return regs.gpr(int(src[1:]))


def read_ret(regs: Regs, spec: dict | None) -> object:
    if spec is None:
        return None
    if spec["t"] in ("f32", "f64"):
        return box_float(struct.unpack(">d", struct.pack(">Q", regs.fpr_bits(1)))[0],
                         spec["t"])
    if spec["t"] == "i64":
        return {"t": "i64", "v": str(((regs.gpr(3) << 32) | regs.gpr(4))
                                     & 0xFFFFFFFFFFFFFFFF)}
    return regs.gpr(3)


def cmd_capture(a: argparse.Namespace) -> int:
    plan = json.loads(Path(a.plan).read_text(encoding="utf-8"))
    if plan.get("spine_plan_schema") != SPINE_SCHEMA:
        sys.exit("plan is not spine_plan_schema 1")
    shape = plan["shape"]
    spine_entry = int(shape["start"], 16)
    loop_head = int(shape["loop_head"], 16)
    back_edge = int(shape["back_edge"]["at"], 16)
    ordered = shape["prologue_calls"] + shape["loop_calls"]
    site_by_addr = {int(c["at"], 16): c for c in ordered}
    store_by_addr = {int(s["at"], 16): s for s in shape["stores"]}
    n_loop = len(shape["loop_calls"])
    n_prologue = len(shape["prologue_calls"])

    scenario = load_scenario(a.scenario) if a.scenario else None
    if scenario and not a.inject:
        a.inject = scenario.get("inject")
    injector = parse_inject_arg(a.inject)

    # every instruction from the first call site through the back edge
    first = int(ordered[0]["at"], 16)
    body = list(range(first, back_edge + 4, 4))

    records: list[dict] = []
    owned_regions: list[dict] = []
    entry_args: list | None = None
    end_owned: list | None = None
    notes: list[str] = []
    iters_done = 0
    d = StubDriver(a.port)
    setup_report = None
    t0 = time.monotonic()
    try:
        d.halt()
        setup_report = apply_scenario_setup(scenario, d)

        if a.from_entry:
            d.set_bp(spine_entry)
            if injector is not None:
                d.set_bp(PAD_INJECT_BP)
            deadline = time.monotonic() + a.entry_timeout
            while True:
                if time.monotonic() > deadline:
                    sys.exit(f"spine entry {spine_entry:#010x} never reached in "
                             f"{a.entry_timeout}s -- with a savestate the spine "
                             f"was entered before the state was taken; use a COLD "
                             f"boot for --from-entry")
                stop = d.cont_until_stop(timeout=min(10.0, max(0.5, deadline - time.monotonic())))
                if stop is None:
                    continue
                pc = stop_pc(stop) or d.rsp.read_pc()
                if injector is not None and pc == PAD_INJECT_BP:
                    injector.on_hit(d.rsp)
                    continue
                if pc == spine_entry:
                    break
            regs = Regs(d.rsp)
            entry_args = [read_arg(regs, s) for s in plan["spine"]["entry_args"]]
            d.clear_bp(spine_entry)

        for addr in body:
            d.set_bp(addr)
        if injector is not None:
            d.set_bp(PAD_INJECT_BP)

        # resolve the owned-write addresses from live registers (r13 is the
        # small-data base and is not knowable statically)
        regs0 = Regs(d.rsp)
        for ow in plan["owned_writes"]:
            base, _, disp = ow["addr_expr"].partition("+" if "+" in ow["addr_expr"] else "-")
            sign = 1 if "+" in ow["addr_expr"] else -1
            addr = (regs0.gpr(int(base[1:])) + sign * int(disp, 16)) & 0xFFFFFFFF
            if not is_mem1(addr):
                sys.exit(f"owned write {ow['addr_expr']} resolved to {addr:#010x}, outside MEM1")
            owned_regions.append({"addr": f"0x{addr:08x}", "size": ow["size"],
                                  "elem_width": ow["elem_width"],
                                  "store_at": ow["store_at"],
                                  "resolved_from": ow["addr_expr"]})

        def snapshot() -> list[dict]:
            out = []
            for r in owned_regions:
                raw = d.rsp.read_mem(int(r["addr"], 16), r["size"])
                out.append({"addr": r["addr"],
                            "b64": base64.b64encode(
                                swap_elems(raw, r["elem_width"])).decode()})
            return out

        if not a.from_entry:
            n_prologue = 0
        target_calls = n_prologue + n_loop * a.iterations
        pending: dict | None = None
        idx = 0
        started = a.from_entry            # mid-loop attach waits for loop_head
        deadline = time.monotonic() + a.max_seconds
        while True:
            if time.monotonic() > deadline:
                notes.append(f"capture deadline {a.max_seconds}s hit after {len(records)} calls")
                break
            stop = d.cont_until_stop(timeout=a.stop_timeout)
            if stop is None:
                notes.append("stub stop timeout -- spine not executing")
                break
            pc = stop_pc(stop) or d.rsp.read_pc()
            if injector is not None and pc == PAD_INJECT_BP:
                injector.on_hit(d.rsp)
                continue
            if pc not in site_by_addr and pc not in store_by_addr and pc != back_edge:
                notes.append(f"stray stop at 0x{pc:08x}")
                continue
            regs = Regs(d.rsp)

            # close the previous call at this stop (instructions are contiguous)
            if pending is not None:
                pending["ret"] = read_ret(regs, pending.pop("_ret_spec"))
                records.append(pending)
                pending = None
                if len(records) >= target_calls:
                    end_owned = snapshot()
                    break

            if pc == back_edge:
                iters_done += 1
                continue
            if pc in store_by_addr:
                st = store_by_addr[pc]
                # value the spine is about to write; recorded for evidence --
                # the harness verifies the write through `owned` bytes, not this
                records[-1]["spine_store"] = {
                    "at": st["at"], "addr_expr": st["addr_expr"],
                    "value": f"0x{regs.gpr(int(st['src_reg'][1:])):08x}"}
                continue

            if not started:
                if pc != loop_head:
                    continue
                started = True

            site = site_by_addr[pc]
            rec = {"kind": "call", "i": len(records),
                   "iter": iters_done, "callee": site["callee"],
                   "callee_addr": site["target"],
                   "args": [read_arg(regs, s) for s in site["args"]],
                   "ret": None, "deltas": [],
                   "owned": snapshot(),
                   "_ret_spec": site["ret"]}
            pending = rec
    except (RspError, OSError) as e:
        notes.append(f"stub session died: {e}")
    finally:
        d.cleanup()

    if end_owned is None and records:
        end_owned = records[-1]["owned"]
        notes.append("end-of-capture owned bytes reused from the last boundary "
                     "(the run was cut before the next call arrived)")
    for r in records:
        r.pop("_ret_spec", None)

    header = {
        "kind": "header", "spine_schema": SPINE_SCHEMA,
        "unit": a.unit,
        "spine": {"export": plan["spine"]["export"],
                  "gc_addr": plan["spine"]["gc_addr"],
                  "args": entry_args if entry_args is not None else []},
        "wasm": a.wasm_rel,
        "arena": a.arena_rel,
        # iterations the capture COVERS (a full set of loop calls), not the
        # number of back edges retired -- the cut lands on the last call of the
        # final iteration, before its back edge executes
        "iterations": (len(records) - n_prologue) // n_loop if n_loop else 0,
        "back_edges_retired": iters_done,
        "terminator": {"mode": "call_cap"},
        "owned_regions": [{"addr": r["addr"], "size": r["size"]} for r in owned_regions],
        "counts": {"call": len(records)},
        "source": {
            "standard": "boundary_green",
            "capture_tool": "research/tools/dolphin-trace/capture_spine.py",
            "control_strategy": "breakpoint every instruction of the spine body; "
                                "each stop closes the previous callee and opens "
                                "the next; terminate by iteration count",
            "emulator": "bundled Dolphin 2606-97 (dolphin/Dolphin.exe), Null video, CPU only",
            "stub": f"gdb-rsp 127.0.0.1:{a.port}",
            "dumped_at": now_iso(),
            "game_state": a.game_state,
            "from_entry": bool(a.from_entry),
            "k_owner_approved": False,
            "plan": str(Path(a.plan).as_posix()),
            "pad_injection": a.inject or None,
            "injected_frames": injector.frame if injector else 0,
            "scenario": a.scenario or None,
            "scenario_setup": setup_report,
            "owned_regions_detail": owned_regions,
            "exclusions": [
                "memory deltas are watch-set-scoped: only the declared owned "
                "regions are diffed, a full MEM1 diff cannot run at frame rate "
                "over GDB-RSP",
                "console stack addresses are excluded (the wasm module has its "
                "own linear stack)",
                "K is not owner-approved (I3's gate requires owner-approved K)",
                "a non-finite float argument is carried boxed and bit-exact, but "
                "JS canonicalises NaN, so a boxed NaN can only be compared as "
                "\"both are NaN\" -- the payload bits are not observable through "
                "the wasm/JS import boundary",
            ],
            "notes": notes,
            "elapsed_s": round(time.monotonic() - t0, 1),
        },
    }
    out = Path(a.out)
    out.parent.mkdir(parents=True, exist_ok=True)
    with out.open("w", encoding="utf-8", newline="\n") as f:
        f.write(json.dumps(header) + "\n")
        for r in records:
            f.write(json.dumps(r) + "\n")
        f.write(json.dumps({"kind": "end", "owned": end_owned or []}) + "\n")
    print(json.dumps({"out": str(out), "calls": len(records),
                      # iterations the capture COVERS (a full set of loop calls), not the
        # number of back edges retired -- the cut lands on the last call of the
        # final iteration, before its back edge executes
        "iterations": (len(records) - n_prologue) // n_loop if n_loop else 0,
        "back_edges_retired": iters_done, "notes": notes,
                      "elapsed_s": round(time.monotonic() - t0, 1)}, indent=2))
    return 0 if records and not notes else 1


# --------------------------------------------------------------------------

def main() -> int:
    p = argparse.ArgumentParser(
        description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    sub = p.add_subparsers(dest="cmd")
    sub.required = True

    sp = sub.add_parser("sites", help="decode the spine + bind it to the module ABI")
    sp.add_argument("--spine", required=True, help="hex GC address, e.g. 0x800527d8")
    sp.add_argument("--wasm", required=True, help="the built single-function spine module")
    sp.add_argument("--export", required=True, help="the spine's wasm export name")
    sp.add_argument("--iso", default=str(ASSET_ROOT / "Gotcha Force.iso"))
    sp.add_argument("--out", required=True)
    sp.set_defaults(func=cmd_sites)

    cp = sub.add_parser("capture", help="walk K loop iterations and record the boundary")
    cp.add_argument("--plan", required=True)
    cp.add_argument("--iterations", type=int, default=8)
    cp.add_argument("--out", required=True)
    cp.add_argument("--unit", default="spine-run-main-game-loop")
    cp.add_argument("--wasm-rel", default="../spine-boundary/unit.wasm",
                    help="header `wasm`: path RELATIVE TO THE CAPTURE FILE")
    cp.add_argument("--arena-rel", default="../oracle-harness/arena-trace-empty.json",
                    help="header `arena`: path RELATIVE TO THE CAPTURE FILE")
    cp.add_argument("--from-entry", action="store_true",
                    help="break the spine's ENTRY first (cold boot) so entry "
                         "args and the prologue calls are captured")
    cp.add_argument("--entry-timeout", type=float, default=240.0)
    cp.add_argument("--stop-timeout", type=float, default=20.0)
    cp.add_argument("--max-seconds", type=float, default=900.0)
    cp.add_argument("--game-state", default="unspecified")
    cp.add_argument("--inject", default=None)
    cp.add_argument("--scenario", default=None)
    cp.add_argument("--port", type=int, default=DEFAULT_PORT)
    cp.set_defaults(func=cmd_capture)

    a = p.parse_args()
    return a.func(a)


if __name__ == "__main__":
    raise SystemExit(main())
