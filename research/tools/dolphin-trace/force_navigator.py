#!/usr/bin/env python3
"""force_navigator.py — make ARBITRARY borg families live in the real game.

The coverage bottleneck this exists to remove: the repo has ONE battle
savestate, it loads a fixed roster, and therefore exactly one borg family
(0x800c04c0 / pl0300) is ever live. `capture_oracle.py` can only capture a
function that actually EXECUTES, so 99 of the 104 staged units — every unit
whose exports live in some other family's address block — score zero cases no
matter how long capture runs or how cleverly the pad is driven
(measured, scenarios/README.md).

This tool drives the game's OWN force/deploy machinery, over the same GDB-RSP
connection `capture_oracle.py` uses, to put a chosen borg into a live battle.
Nothing is faked: the roster table is the table the game itself reads, the
archive load and the actor construction are the ROM's, and the "is this family
live?" answer is a breakpoint on the family's constructor firing.

Ground truth this is built on (all committed evidence, cited):
  T = *(u32*)0x80433934              battle/slot table base
  V = *(u32*)0x80433930              viewport/global table base
  T[0x10 + slot*2]   (BE u16)        slot's CURRENT borg id  (pl#### == the id)
  T[slot + 0x5a]     (u8)            slot's roster ENTRY COUNT
  T[slot + 0xa0]     (u8)            slot's costume COLOUR (0..5), NOT the id
  T[slot + 0xc0]     (s8)            player -> active borg slot   (behavior-notes §z)
  T[slot + 0xcb]     (u8)            team/side byte (0,1,0xff=absent)
  T[0x15d9]/[0x15da] (u8)            active slot mask / count
  T[slot*0x348 + 0x1e8 + k*0x1c]     roster entry k: BE u16 borg id,
                                     +0x1ea colour byte, +0x1eb level byte
  T[0x45]            (u8)            battle phase: 1 load, 3 actors-ready, 4 LIVE
  T[0x00]/T[0x01]    (u8)            battle super/sub state
  0x803c4e84                         6 active-borg struct pointers
  actor+1000 (0x3e8) (BE u16)        the borg id this actor was built from
  0x803bbac0 + slot*0xc30            slot's loaded archive record (0 = absent)
Sources: research/decomp/ghidra-export/chunk_0048.c:234 build_challenge_battle_setup,
chunk_0006.c:6999 FUN_800541ac, chunk_0007.c:1149 zz_005809c_,
chunk_0004.c:9533 zz_00410bc_, chunk_0004.c:9608 zz_0041288_,
chunk_0003.c:3533 the phase dispatch, chunk_0008.c:4589 zz_0068424_,
research/decomp/behavior-notes.md §(n) and §(z).

Borg id encoding (research/decomp/data/spawn-pools-80380804.json): a spawn id is
(family_hi << 8) | variant_lo and is LITERALLY the pl#### number in hex, so
"pl0906" <-> 0x0906. That is the join key between the roster table and
research/decomp/data/family-state-machine-coverage.json's per-family members,
which is what `src/port_family_gate.py` gates verify-sweep on.
"""
from __future__ import annotations

import argparse
import json
import os
import struct
import sys
import time
from pathlib import Path

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import capture_oracle as co  # noqa: E402
from rsp_client import RspError  # noqa: E402

REPO_ROOT = co.REPO_ROOT
ASSET_ROOT = co.ASSET_ROOT

# --- slot-table offsets (see module docstring for provenance) --------------
T_PTR = 0x80433934
V_PTR = 0x80433930
OFF_CUR_ID = 0x10        # + slot*2, u16
OFF_ROSTER_N = 0x5A      # + slot,   u8
OFF_VARIANT = 0xA0       # + slot,   u8
OFF_PLAYER_SLOT = 0xC0   # + player, s8
OFF_TEAM = 0xCB          # + slot,   u8
OFF_ACTIVE_MASK = 0x15D9
OFF_ACTIVE_COUNT = 0x15DA
ROSTER_STRIDE_SLOT = 0x348
ROSTER_BASE = 0x1E8
ROSTER_STRIDE_ENTRY = 0x1C
ROSTER_MAX = ROSTER_STRIDE_SLOT // ROSTER_STRIDE_ENTRY   # 30
ACTIVE_BORG_ARRAY = 0x803C4E84
ACTIVE_BORG_SLOTS = 6

COVERAGE_JSON = "research/decomp/data/family-state-machine-coverage.json"


# --------------------------------------------------------------------------
# family <-> borg id, from the same artifact the family gate uses
# --------------------------------------------------------------------------

def load_family_members(repo_root: Path | None = None) -> dict[str, list[str]]:
    """{'0x800c04c0': ['pl0300', 'pl030b'], ...} — 119 families."""
    root = Path(repo_root or REPO_ROOT)
    path = root / COVERAGE_JSON
    data = json.loads(path.read_text(encoding="utf-8-sig"))
    out: dict[str, list[str]] = {}
    for fam in data.get("families", []):
        addr = fam.get("constructorAddress")
        if not addr:
            continue
        out[f"0x{int(addr, 16):08x}"] = list(fam.get("members") or [])
    return out


def borg_id(member: str) -> int:
    """'pl0906' -> 0x0906 (spawn-pools-80380804.json: spawn id IS the pl number)."""
    m = member.strip().lower()
    if not m.startswith("pl") or len(m) != 6:
        raise ValueError(f"not a pl#### member name: {member!r}")
    return int(m[2:], 16)


def member_name(bid: int) -> str:
    return f"pl{bid:04x}"


# --------------------------------------------------------------------------
# live memory view of the battle/slot tables
# --------------------------------------------------------------------------

class BattleTables:
    """A halted-CPU snapshot of everything that decides which borgs exist."""

    def __init__(self, rsp):
        self.rsp = rsp
        self.T = self._u32(T_PTR)
        self.V = self._u32(V_PTR)

    # -- primitives --------------------------------------------------------
    def _u32(self, addr: int) -> int:
        return struct.unpack(">I", self.rsp.read_mem(addr, 4))[0]

    def _u16(self, addr: int) -> int:
        return struct.unpack(">H", self.rsp.read_mem(addr, 2))[0]

    def _u8(self, addr: int) -> int:
        return self.rsp.read_mem(addr, 1)[0]

    def _s8(self, addr: int) -> int:
        v = self._u8(addr)
        return v - 256 if v > 127 else v

    @property
    def live(self) -> bool:
        return co.is_mem1(self.T) and co.is_mem1(self.V)

    # -- addresses ---------------------------------------------------------
    def cur_id_addr(self, slot: int) -> int:
        return self.T + OFF_CUR_ID + slot * 2

    def roster_addr(self, slot: int, k: int) -> int:
        return (self.T + slot * ROSTER_STRIDE_SLOT + ROSTER_BASE
                + k * ROSTER_STRIDE_ENTRY)

    # -- reads -------------------------------------------------------------
    def slot_snapshot(self, slot: int) -> dict:
        n = self._u8(self.T + OFF_ROSTER_N + slot)
        roster = []
        for k in range(min(max(n, 0), ROSTER_MAX)):
            a = self.roster_addr(slot, k)
            roster.append({
                "k": k,
                "addr": f"0x{a:08x}",
                "borg_id": f"0x{self._u16(a):04x}",
                "member": member_name(self._u16(a)),
                "variant": self._u8(a + 2),
                "flag": self._u8(a + 3),
            })
        cur = self._u16(self.cur_id_addr(slot))
        return {
            "slot": slot,
            "team": self._u8(self.T + OFF_TEAM + slot),
            "current_borg_id": f"0x{cur:04x}",
            "current_member": member_name(cur),
            "variant": self._u8(self.T + OFF_VARIANT + slot),
            "roster_count": n,
            "roster": roster,
        }

    def actor_ptrs(self) -> list[int]:
        raw = self.rsp.read_mem(ACTIVE_BORG_ARRAY, 4 * ACTIVE_BORG_SLOTS)
        return list(struct.unpack(">6I", raw))

    def snapshot(self) -> dict:
        out = {
            "T": f"0x{self.T:08x}",
            "V": f"0x{self.V:08x}",
            "battle_live": self.live,
        }
        if not self.live:
            return out
        out["active_mask"] = self._u8(self.T + OFF_ACTIVE_MASK)
        out["active_count"] = self._u8(self.T + OFF_ACTIVE_COUNT)
        out["menu_mode"] = self._u8(self.V + 0x3E)
        out["controller_mask"] = self._u8(self.V + 2)
        out["player_slot"] = [self._s8(self.T + OFF_PLAYER_SLOT + p)
                              for p in range(4)]
        out["slots"] = [self.slot_snapshot(s) for s in range(ACTIVE_BORG_SLOTS)]
        ptrs = self.actor_ptrs()
        out["actors"] = []
        for i, p in enumerate(ptrs):
            rec = {"i": i, "ptr": f"0x{p:08x}", "mem1": co.is_mem1(p)}
            if co.is_mem1(p):
                rec["alive_flag"] = self._u8(p)
                rec["slot_field_0x3e4"] = self._s8(p + 0x3E4)
                rec["team_0x88"] = self._u8(p + 0x88)
                rec["state_0x544"] = struct.unpack(
                    ">i", self.rsp.read_mem(p + 0x544, 4))[0]
                rec["id_0x3e7"] = f"0x{self._u16(p + 0x3E6):04x}"
            out["actors"].append(rec)
        return out


# --------------------------------------------------------------------------
# verbs
# --------------------------------------------------------------------------

def _attach(a) -> co.StubDriver:
    d = co.StubDriver(a.port)
    d.halt()
    head = d.rsp.read_mem(0x80000000, 4)
    if head[:3] != b"GG4":
        d.cleanup()
        sys.exit(f"attached, but game id is {head!r} — not GG4E")
    return d


def cmd_inspect(a: argparse.Namespace) -> int:
    d = _attach(a)
    try:
        snap = BattleTables(d.rsp).snapshot()
        print(json.dumps(snap, indent=2))
        return 0 if snap.get("battle_live") else 1
    finally:
        d.cleanup()


def launch(save_state: str | None, port: int, wait: int = 150,
           user_dir: Path | None = None) -> None:
    """Boot our own Dolphin exactly like `capture_oracle.py launch` does.

    Same pid ledger, same Null backend, same --debugger. Reusing that verb
    rather than re-implementing it keeps the reap-before-relaunch contract
    (capture_oracle.reap_tracked) that stops us fighting the port driver for
    Dolphin instances.
    """
    ns = argparse.Namespace(
        dolphin=str(ASSET_ROOT / "dolphin/Dolphin.exe"),
        iso=str(ASSET_ROOT / "Gotcha Force.iso"),
        save_state=str(save_state) if save_state else None,
        user_dir=str(user_dir or ASSET_ROOT / "user-data/dolphin-oracle"),
        port=port, cpu_core=1, gfx="Null", wait=float(wait), scenario=None)
    rc = co.cmd_launch(ns)
    if rc:
        raise RuntimeError(f"launch failed rc={rc}")


def stop(user_dir: Path | None = None) -> None:
    co.cmd_stop(argparse.Namespace(
        user_dir=str(user_dir or ASSET_ROOT / "user-data/dolphin-oracle")))


def cmd_survey(a: argparse.Namespace) -> int:
    """Boot every candidate savestate and record which borgs it actually loads.

    The repo's own scenario library asserts one live family from ONE savestate;
    but the checkout carries a dozen more .sav files nobody ever read the
    roster out of. This measures them instead of assuming.
    """
    states: list[Path] = []
    for pat in a.glob:
        states.extend(sorted(Path(ASSET_ROOT).glob(pat)))
    seen: set[str] = set()
    results = []
    for sav in states:
        if str(sav) in seen:
            continue
        seen.add(str(sav))
        rec: dict = {"save_state": str(sav), "size": sav.stat().st_size}
        try:
            launch(str(sav), a.port, wait=a.wait)
            d = _attach(a)
            try:
                snap = BattleTables(d.rsp).snapshot()
            finally:
                d.cleanup()
            rec["battle_live"] = snap.get("battle_live")
            rec["menu_mode"] = snap.get("menu_mode")
            rec["active_count"] = snap.get("active_count")
            rec["borgs"] = sorted({s["current_member"]
                                   for s in snap.get("slots", [])
                                   if s["current_borg_id"] != "0xffff"})
            rec["rosters"] = [
                {"slot": s["slot"], "team": s["team"], "n": s["roster_count"],
                 "entries": [e["member"] for e in s["roster"]]}
                for s in snap.get("slots", [])]
        except Exception as exc:  # noqa: BLE001 — a bad savestate must not stop the survey
            rec["error"] = f"{type(exc).__name__}: {exc}"
        finally:
            stop()
        print(json.dumps(rec), flush=True)
        results.append(rec)
    if a.out:
        Path(a.out).write_text(json.dumps(results, indent=2), encoding="utf-8")
    return 0


# --------------------------------------------------------------------------
# the navigator proper: re-run the game's own battle load with a chosen roster
# --------------------------------------------------------------------------
#
# The battle is a 4-entry phase machine, dispatched every frame by
# `zz_0028264_` @0x80028264 as `PTR_FUN_802cfde0[T[0]]()`
# (chunk_0003.c:3533; table read live 2026-08-29 -> only indices 0..3 are code,
# 4+ is float data, so T[0] in 0..3):
#
#   0  FUN_8002844c  TEARDOWN + LOAD.  Resets the battle heap and calls
#                    zz_0041288_ (chunk_0004.c:9608) -> zz_00410bc_(slot) for
#                    slots 0..5.  zz_00410bc_ (0x800410bc, chunk_0004.c:9533)
#                    reads T[0x10+slot*2] as (family_hi, variant_lo), indexes
#                    PTR_DAT_802d0584[family] and queues the borg's archive
#                    read, whose completion callback zz_00412c4_ stores the
#                    loaded record at DAT_803bbac0 + slot*0xc30.  T[0] -> 1.
#   1  FUN_800286d8  waits for the load (zz_00295e0_), re-inits battle state,
#                    set_global_menu_mode(1).  T[0] -> 2.
#   2  FUN_800288fc  the running battle frame.
#   3  FUN_800289fc  round-start sub-machine keyed on T[1].
#
#   zz_00422d8_ (0x800422d8) gates actor construction on
#   DAT_803bbac0+slot*0xc30 being non-zero, and FUN_800541ac (0x800541ac,
#   chunk_0006.c:7055) then does `actor[1000] = T[0x10+slot*2]` — i.e. the
#   spawned borg IS whatever id the slot table held when the load ran.
#
# So: write the ids we want into the slot table, set T[0]=0/T[1]=0, and the
# ROM reloads the battle around them. Nothing is emulated or faked on our side
# — the archive read, the actor construction and the family state machine are
# all the game's.
BATTLE_FRAME_HOOK = 0x80028264  # zz_0028264_ — dispatches PTR_FUN_802cfde0[T[0]]
ARCHIVE_SLOT_BASE = 0x803BBAC0
ARCHIVE_SLOT_STRIDE = 0xC30
ACTOR_BORG_ID = 0x3E8          # actor+1000, written by FUN_800541ac
OFF_ROSTER_CURSOR = 0x15C8     # + slot, next roster index zz_0068424_ hands out
OFF_ROSTER_LAST = 0x15CE       # + slot, index zz_00684a4_ hands out
OFF_ROSTER_SEL = 0x54          # + slot, index most recently handed out
OFF_BATTLE_STATE = 0x45        # T[0x45]: 1 load, 3 actors-ready wait, 4 LIVE, 5 results
OFF_WIN_MASK = 0x1F            # T[0x1f]: 0 while the battle is still contested


class StageError(RuntimeError):
    pass


def _battle_status(bt: BattleTables) -> dict:
    """The ROM's own "is a battle live" bytes, read from a halted CPU.

    T[0x45] is the battle phase byte: 1 load/init (FUN_8002844c,
    chunk_0003.c:3650), 3 actors-ready wait (FUN_80029218, :4221),
    4 LIVE GAMEPLAY (FUN_80029408, :4297), 5 results (FUN_800289fc, :3923).
    T[0x1f] is the winner mask (0 while the battle is still contested,
    zz_00297c8_ chunk_0003.c:4488).
    """
    ptr = bt.actor_ptrs()[0]
    return {
        "battle_phase_T0": bt._u8(bt.T),
        "battle_state_T0x45": bt._u8(bt.T + OFF_BATTLE_STATE),
        "win_mask_T0x1f": bt._u8(bt.T + OFF_WIN_MASK),
        "actor0": f"0x{ptr:08x}",
        "actor0_alive": bt._u8(ptr) if co.is_mem1(ptr) else 0,
        "actor0_borg_id": (f"0x{bt._u16(ptr + ACTOR_BORG_ID):04x}"
                           if co.is_mem1(ptr) else None),
    }


def _is_live(status: dict) -> bool:
    return status["battle_state_T0x45"] == 4 and status["actor0_alive"] == 1


def write_roster(bt: BattleTables, assignment: dict[int, int],
                 color: int = 0, depth: int = 6) -> list[dict]:
    """Point the named slots at the named borg ids, in the game's own tables.

    `assignment` is {slot: borg_id}. Every roster entry a slot gets is THE
    SAME borg, so the deploy cursor (zz_0068424_'s modulo over T[slot+0x5a])
    can only ever hand out our borg and the family cannot be un-covered by a
    respawn. `depth` is how many of those identical entries to write: a slot
    is declared wiped once actor[0x491] (deploys used) reaches T[slot+0x5a]
    (chunk_0006.c:7658), so depth 1 ends the battle at the first death and
    with it the capture window — measured, a depth-1 pl0906 battle stopped
    feeding cases after 42. Depth costs nothing but table bytes; the block is
    0x348 bytes = 30 entries per slot, which is the hard ceiling.

    COLOUR IS NOT THE ID'S LOW BYTE. `T[slot+0xa0]` (and roster entry +0x1ea)
    is the 0..5 costume colour; the id's low byte is the member index within
    the family and is consumed separately as `T[slot*2+0x11]` to index
    PTR_DAT_802d0584[family] (zz_00410bc_, chunk_0004.c:9581-9588). Writing the
    low byte into the colour field made the load callback zz_00412c4_ publish
    `DAT_803b07bc + slot*0x38 + colour*4` from past the end of that slot's
    six-entry colour block, and the game hung the instant the actor was
    constructed from the garbage pointer (measured 2026-08-29: every per-frame
    hook went silent one stop after the family constructor fired, on pl0906
    whose low byte is 6). Colour defaults to 0.
    """
    if not 0 <= color <= 5:
        raise StageError(f"colour {color} out of range (0..5)")
    rsp = bt.rsp
    written = []
    for slot, bid in sorted(assignment.items()):
        if not 0 <= slot < ACTIVE_BORG_SLOTS:
            raise StageError(f"slot {slot} out of range")
        if not 0 <= bid <= 0x7FFF:
            # zz_00410bc_ tests `-1 < (char)T[0x10+slot*2]`, so a high byte
            # with bit 7 set reads as "empty slot" and loads nothing.
            raise StageError(f"borg id {bid:#06x} has a negative family byte")
        rsp.write_mem(bt.cur_id_addr(slot), struct.pack(">H", bid))
        rsp.write_mem(bt.T + OFF_VARIANT + slot, bytes([color]))
        n = max(1, min(int(depth), ROSTER_MAX))
        for k in range(n):
            entry = bt.roster_addr(slot, k)
            rsp.write_mem(entry, struct.pack(">H", bid))
            rsp.write_mem(entry + 2, bytes([color, 0]))
            rsp.write_mem(entry + 0x16, bytes([0, 0, 0]))   # +0x1fe/+0x1ff/+0x200
        rsp.write_mem(bt.T + OFF_ROSTER_N + slot, bytes([n]))
        rsp.write_mem(bt.T + OFF_ROSTER_CURSOR + slot, bytes([0]))
        rsp.write_mem(bt.T + OFF_ROSTER_LAST + slot, bytes([0]))
        rsp.write_mem(bt.T + OFF_ROSTER_SEL + slot, bytes([0]))
        written.append({"slot": slot, "borg_id": f"0x{bid:04x}",
                        "member": member_name(bid), "color": color,
                        "roster_depth": n})
    return written


def rewind_battle_phase(bt: BattleTables) -> None:
    """Send the battle phase machine back to its LOAD step (T[0]=0, T[1]=0)."""
    bt.rsp.write_mem(bt.T + 1, bytes([0]))
    bt.rsp.write_mem(bt.T, bytes([0]))


def stage_borgs(d: co.StubDriver, assignment: dict[int, int],
                expect_families: list[str] | None = None,
                timeout_s: float = 240.0, settle_s: float = 60.0,
                color: int = 0, depth: int = 6, progress=print) -> dict:
    """Reload the live battle around `assignment` and prove what came up.

    `constructors_hit` is the load-bearing evidence: a Z0 on each expected
    family's constructorAddress that actually FIRES is proof the ROM built
    that family's actor — exactly the claim a scenario's `live_families`
    makes to verify-sweep's family gate.

    Control-flow note (measured 2026-08-29, and the reason this is not a
    resume/^C poll loop): on this stub, a raw 0x03 interrupt sent while the
    CPU is genuinely free-running does NOT reliably produce a stop packet —
    the first integrated run wedged there. Every control point below is a
    breakpoint instead. `BATTLE_FRAME_HOOK` (0x80028264, zz_0028264_, the
    ROM's own per-frame battle dispatch, chunk_0003.c:3533) fires once a frame
    for as long as the battle scene is running, so it is the guaranteed
    per-frame halt window — but it is only installed AFTER the load, because
    a hook that halts every frame costs the reload ~15x in wall clock.
    """
    bt = BattleTables(d.rsp)
    if not bt.live:
        raise StageError("no live battle in this state (T/V do not point into MEM1)")
    before = bt.snapshot()

    fam_addrs = [int(f, 16) for f in (expect_families or [])]
    for addr in fam_addrs:
        d.set_bp(addr)
    hits: dict[str, int] = {}

    written = write_roster(bt, assignment, color=color, depth=depth)
    progress(f"roster written: {written}")
    rewind_battle_phase(bt)
    progress("battle phase rewound to 0 (load step)")

    deadline = time.monotonic() + timeout_s
    frames = 0
    fired = not fam_addrs
    status: dict = {}
    if fired:
        d.set_bp(BATTLE_FRAME_HOOK)
    while time.monotonic() < deadline:
        # While the reload streams four borg archives off the emulated DVD no
        # per-frame hook is installed: every breakpoint costs an RSP round
        # trip, and hooking each frame drops the emulator to ~3 fps, which
        # stretched that read from seconds to ~45 s of wall clock.
        stop = d.cont_until_stop(timeout=max(1.0, deadline - time.monotonic()))
        if stop is None:
            progress("no stop before the deadline — nothing we watch ever ran")
            break
        pc = co.stop_pc(stop)
        if pc in fam_addrs:
            key = f"0x{pc:08x}"
            hits[key] = hits.get(key, 0) + 1
            # One fire is the whole proof, and a constructor breakpoint left
            # installed keeps re-halting the CPU inside the reload it is meant
            # to observe. Retire it as soon as it has spoken.
            try:
                d.clear_bp(pc)
            except RspError:
                pass
            if not fired and len(hits) == len(fam_addrs):
                fired = True
                progress(f"family constructor(s) fired: {sorted(hits)}")
                d.set_bp(BATTLE_FRAME_HOOK)   # per-frame control point
                deadline = min(deadline, time.monotonic() + settle_s)
            continue
        if pc != BATTLE_FRAME_HOOK:
            continue
        frames += 1
        if frames % 10:
            continue
        status = _battle_status(bt)
        if frames % 200 == 0:
            progress(f"...frame {frames}: {status}")
        if _is_live(status):
            progress(f"battle live again after {frames} frames: {status}")
            break

    for addr in list(d.bps):
        try:
            d.clear_bp(addr)
        except RspError:
            pass
    d.rsp.drain_async(0.2)

    after = BattleTables(d.rsp)
    status = _battle_status(after)
    actor_ids = []
    for ptr in after.actor_ptrs():
        actor_ids.append(f"0x{after._u16(ptr + ACTOR_BORG_ID):04x}"
                         if co.is_mem1(ptr) else None)
    archive_slots = [
        f"0x{after._u32(ARCHIVE_SLOT_BASE + s * ARCHIVE_SLOT_STRIDE):08x}"
        for s in range(ACTIVE_BORG_SLOTS)]
    want = {f"0x{b:04x}" for b in assignment.values()}
    return {
        "assignment": {str(k): member_name(v) for k, v in sorted(assignment.items())},
        "expect_families": expect_families or [],
        "constructors_hit": hits,
        "constructors_fired": fired,
        "battle_live": _is_live(status),
        "settled": (fired or not fam_addrs) and _is_live(status),
        "status": status,
        "frames_run": frames,
        "slot_ids_before": [s["current_member"] for s in before.get("slots", [])],
        "slot_ids_after": [s["current_member"]
                           for s in after.snapshot().get("slots", [])],
        "actor_borg_ids": actor_ids,
        "actors_on_target": sum(1 for a in actor_ids if a in want),
        "archive_slot_records": archive_slots,
    }


# --------------------------------------------------------------------------
# batch coverage: one measured scenario per blocked borg family
# --------------------------------------------------------------------------

OGHIDRA_DIR = "research/tools/OGhidra"
UNITS_STATE = "research/decomp/generated/finish-game-port/wasm-units-state.json"
# zz_0068570_ @0x80068570 (chunk_0008.c:4658) answers "does member M of family F
# exist?" as `1 << M & *(u64*)(DAT_802f29c8 + F*8)`. Reading that same table
# lets us reject an id BEFORE staging it instead of discovering it the hard way
# (a nonexistent member yields a garbage archive pointer and hangs the game).
BORG_EXISTS_TABLE = 0x802F29C8


def borg_exists(rsp, bid: int) -> bool:
    """Exactly zz_0068570_'s test, and it is TWO u32 words, not one u64:

        member < 0x20 : 1 << member          & *(u32*)(0x802f29c8 + family*8)
        member >= 0x20: 1 << (member - 0x20) & *(u32*)(0x802f29cc + family*8)

    Reading the pair as a single big-endian u64 and shifting by the member
    index gets the halves backwards and rejects almost every real borg — it
    scored 36 false negatives out of 38 families on the first cover sweep.
    """
    hi, lo = bid >> 8, bid & 0xFF
    if hi > 0x1F or lo > 0x3F:
        return False
    w0, w1 = struct.unpack(">II", rsp.read_mem(BORG_EXISTS_TABLE + hi * 8, 8))
    return bool((w0 >> lo) & 1) if lo < 0x20 else bool((w1 >> (lo - 0x20)) & 1)


def _oghidra_gate(repo_root: Path):
    """The family gate itself (pure stdlib) — the authority on which family
    gates which unit. Imported rather than re-derived, so this tool and
    verify-sweep can never disagree about a unit's family.

    OGhidra is a nested repo that exists only in the MAIN checkout, so it is
    resolved against ASSET_ROOT the same way the disc and savestates are.
    """
    for root in (Path(repo_root), ASSET_ROOT):
        if (root / OGHIDRA_DIR / "src" / "port_family_gate.py").is_file():
            sys.path.insert(0, str(root / OGHIDRA_DIR))
            break
    else:
        raise StageError(f"no {OGHIDRA_DIR}/src/port_family_gate.py under "
                         f"{repo_root} or {ASSET_ROOT}")
    from src.port_family_gate import FamilyIndex  # noqa: E402
    from src.port_trace_verify import load_registry_functions  # noqa: E402
    return FamilyIndex.load(Path(repo_root)), load_registry_functions(Path(repo_root))


def staged_units(repo_root: Path) -> list[str]:
    """The staged compile-only greens — the population the coverage claim is
    about. Taken from the driver's own state file rather than a directory
    listing (the staging tree also holds units that are no longer greens)."""
    data = json.loads((Path(repo_root) / UNITS_STATE).read_text(encoding="utf-8-sig"))
    records = data.get("units", data) if isinstance(data, dict) else data
    items = (records.items() if isinstance(records, dict)
             else ((r.get("unit") or r.get("name"), r) for r in records))
    return sorted(name for name, rec in items
                  if isinstance(rec, dict) and rec.get("status") == "green"
                  and rec.get("tier") == "compile_only")


def blocked_inventory(repo_root: Path) -> list[dict]:
    """[{family, members, units, exports}] for every family the staged greens
    are gated on, biggest blocker first."""
    index, registry = _oghidra_gate(repo_root)
    if index is None:
        raise StageError("family-state-machine-coverage.json is unusable; "
                         "refusing to guess a family for any unit")
    tally: dict[str, dict] = {}
    for unit in staged_units(repo_root):
        prov = (Path(repo_root) / "research/decomp/port-units-staging" / unit
                / "provenance.json")
        if not prov.is_file():
            continue
        exports = json.loads(prov.read_text(encoding="utf-8-sig")).get(
            "exported_functions") or []
        for fam in sorted(index.unit_families(exports, registry).families):
            rec = tally.setdefault(fam, {
                "family": fam,
                "members": list(index.members_by_family.get(fam, ())),
                "units": [], "exports": 0})
            rec["units"].append(unit)
            rec["exports"] += len(exports)
    rows = sorted(tally.values(), key=lambda r: (-len(r["units"]), r["family"]))
    for r in rows:
        r["unit_count"] = len(r["units"])
    return rows


def _write_json(path: Path, doc: dict) -> None:
    """LF-terminated pretty JSON. (Path.write_text(newline=...) is 3.10+, and
    the interpreter this rig runs the trace tools with is older.)"""
    with path.open("w", encoding="utf-8", newline=chr(10)) as fh:
        fh.write(json.dumps(doc, indent=2) + chr(10))


def scenario_name_for(family: str) -> str:
    return f"battle-roster-{family}"


def scenario_covered_families(scenario_dir: Path) -> set[str]:
    covered: set[str] = set()
    for path in scenario_dir.glob("*.json"):
        try:
            doc = json.loads(path.read_text(encoding="utf-8-sig"))
        except (json.JSONDecodeError, OSError):
            continue
        for fam in doc.get("live_families") or []:
            try:
                covered.add(f"0x{int(fam, 16):08x}")
            except (TypeError, ValueError):
                continue
    return covered


def write_family_scenario(scenario_dir: Path, family: str, members: list[str],
                          member: str, slots: list[int], report: dict,
                          depth: int) -> Path:
    name = scenario_name_for(family)
    doc = {
        "scenario_schema": 1,
        "name": name,
        "description": (
            f"The owner 2v2 savestate, re-loaded by the ROM around a {member} "
            f"roster so borg family {family} ({'/'.join(members)}) is the live "
            "family instead of the savestate's pl0615. Generated by "
            "research/tools/dolphin-trace/force_navigator.py cover."),
        "save_state": "2v2 gred cotrolled players no cpu.sav",
        "inject": "combat:b,x,a",
        "game_state": (f"2v2 sav reloaded with a {member} roster in slots "
                       f"{slots} (roster depth {depth}) + B/X/A press-release edges"),
        "dtm": None,
        "setup": {
            "kind": "battle_roster_reload",
            "borgs": [member],
            "slots": slots,
            "roster_depth": depth,
            "expect_families": [family],
            "timeout_s": 300,
        },
        "live_families": [family],
        "live_families_basis": (
            f"MEASURED by force_navigator.py cover: after writing {member} into "
            "the game's own slot table (T[0x10+slot*2] plus the per-slot roster "
            "at T[slot*0x348+0x1e8]) and rewinding the battle phase machine to "
            "its load step, a Z0 breakpoint on this family's constructorAddress "
            "FIRED, and the battle then reported live gameplay (T[0x45]==4) with "
            f"{report.get('actors_on_target')} of 6 DAT_803c4e84 actors carrying "
            f"borg id 0x{borg_id(member):04x} at actor+1000. Only this family is "
            "asserted: the reload replaces the whole roster, so nothing the base "
            "savestate used to exercise survives it."),
    }
    path = scenario_dir / f"{name}.json"
    _write_json(path, doc)
    return path


def cmd_cover(a: argparse.Namespace) -> int:
    """Produce one measured, ready-to-use scenario per blocked borg family."""
    repo = Path(a.repo_root or ASSET_ROOT)
    scenario_dir = Path(a.scenario_dir or co.SCENARIO_DIR)
    scenario_dir.mkdir(parents=True, exist_ok=True)
    rows = blocked_inventory(repo)
    if a.families:
        want = {f"0x{int(f.strip(), 16):08x}" for f in a.families.split(",") if f.strip()}
        rows = [r for r in rows if r["family"] in want]
    elif not a.include_covered:
        covered = scenario_covered_families(scenario_dir)
        rows = [r for r in rows if r["family"] not in covered]
    if a.top:
        rows = rows[:a.top]
    slots = [int(x) for x in (a.slots.split(",") if a.slots else ["0", "1", "2", "3"])]

    results: list[dict] = []

    def flush_manifest() -> None:
        if not a.manifest:
            return
        Path(a.manifest).parent.mkdir(parents=True, exist_ok=True)
        _write_json(Path(a.manifest), {
            "generated_at": co.now_iso(),
            "generated_by": "research/tools/dolphin-trace/force_navigator.py cover",
            "base_save_state": a.save_state,
            "slots": slots,
            "roster_depth": a.depth,
            "note": ("Dolphin on this rig cannot WRITE a savestate (see the "
                     "dolphin-trace README), so each covered family is delivered "
                     "as a scenario whose `setup` block re-derives its state "
                     "from the one base savestate, not as a .sav file."),
            "results": results,
        })

    for i, row in enumerate(rows, 1):
        family, members = row["family"], row["members"]
        rec: dict = {"family": family, "members": members,
                     "blocked_units": row["unit_count"],
                     "blocked_exports": row["exports"],
                     "attempted_at": co.now_iso()}
        print(f"=== [{i}/{len(rows)}] {family} {members} "
              f"({row['unit_count']} blocked units)", flush=True)
        chosen = None
        try:
            launch(str(ASSET_ROOT / a.save_state), a.port, wait=a.wait)
            d = _attach(a)
            try:
                for m in members:
                    if borg_exists(d.rsp, borg_id(m)):
                        chosen = m
                        break
                if chosen is None:
                    rec["outcome"] = "no_valid_member"
                    rec["detail"] = ("no member of this family is flagged present "
                                     "in the ROM's own id table at 0x802f29c8")
                else:
                    rep = stage_borgs(
                        d, {s: borg_id(chosen) for s in slots},
                        expect_families=[family], timeout_s=a.timeout,
                        depth=a.depth,
                        progress=lambda m_, f=family: print(f"  [{f}] {m_}", flush=True))
                    rec["member_used"] = chosen
                    rec["report"] = rep
                    rec["outcome"] = ("covered" if rep["settled"] else
                                      "constructor_only" if rep["constructors_fired"]
                                      else "not_reached")
            finally:
                d.cleanup()
        except Exception as exc:  # noqa: BLE001 — one bad family must not stop the sweep
            rec["outcome"] = "error"
            rec["detail"] = f"{type(exc).__name__}: {exc}"
        finally:
            stop()
        if rec.get("outcome") == "covered":
            path = write_family_scenario(scenario_dir, family, members, chosen,
                                         slots, rec["report"], a.depth)
            rec["scenario_name"] = scenario_name_for(family)
            rec["scenario_path"] = str(path)
        results.append(rec)
        flush_manifest()
        print(json.dumps({k: v for k, v in rec.items() if k != "report"}), flush=True)

    covered = [r for r in results if r.get("outcome") == "covered"]
    print(f"COVER SUMMARY: {len(covered)}/{len(results)} families covered; "
          f"{sum(r['blocked_units'] for r in covered)} previously-blocked units "
          "now have a scenario", flush=True)
    return 0 if covered or not results else 1


def cmd_inventory(a: argparse.Namespace) -> int:
    print(json.dumps(blocked_inventory(Path(a.repo_root or ASSET_ROOT)), indent=2))
    return 0


def parse_assignment(borgs: str, slots: str | None) -> dict[int, int]:
    ids = [borg_id(b) for b in borgs.split(",") if b.strip()]
    if not ids:
        raise StageError("--borgs is empty")
    slot_list = ([int(s) for s in slots.split(",") if s.strip()] if slots
                 else list(range(min(4, ACTIVE_BORG_SLOTS))))
    return {s: ids[i % len(ids)] for i, s in enumerate(slot_list)}


def cmd_stage(a: argparse.Namespace) -> int:
    assignment = parse_assignment(a.borgs, a.slots)
    fams = a.expect_family.split(",") if a.expect_family else []
    d = _attach(a)
    try:
        rep = stage_borgs(d, assignment, fams, timeout_s=a.timeout)
    finally:
        d.cleanup()
    print(json.dumps(rep, indent=2))
    return 0 if rep["settled"] or not fams else 2


def cmd_families(a: argparse.Namespace) -> int:
    fams = load_family_members()
    rows = [{"family": f, "members": m,
             "borg_ids": [f"0x{borg_id(x):04x}" for x in m]}
            for f, m in sorted(fams.items())]
    print(json.dumps(rows, indent=2))
    return 0


def build_parser() -> argparse.ArgumentParser:
    p = argparse.ArgumentParser(description=__doc__,
                                formatter_class=argparse.RawDescriptionHelpFormatter)
    sub = p.add_subparsers(dest="cmd", required=True)

    ins = sub.add_parser("inspect", help="dump the live battle/slot tables")
    ins.add_argument("--port", type=int, default=co.DEFAULT_PORT)
    ins.set_defaults(func=cmd_inspect)

    sv = sub.add_parser("survey", help="boot each savestate, record its roster")
    sv.add_argument("--port", type=int, default=co.DEFAULT_PORT)
    sv.add_argument("--wait", type=int, default=150)
    sv.add_argument("--glob", action="append",
                    default=None, help="glob under the main checkout root")
    sv.add_argument("--out")
    sv.set_defaults(func=cmd_survey,
                    glob_default=["*.sav", "dolphin/*.sav"])

    st = sub.add_parser("stage", help="reload the live battle around chosen borgs")
    st.add_argument("--port", type=int, default=co.DEFAULT_PORT)
    st.add_argument("--borgs", required=True,
                    help="comma-separated pl#### members, cycled over --slots")
    st.add_argument("--slots", default=None, help="default 0,1,2,3")
    st.add_argument("--expect-family", default=None,
                    help="comma-separated family constructor addresses; a Z0 "
                         "that FIRES on one is the proof the family went live")
    st.add_argument("--timeout", type=float, default=240.0)
    st.set_defaults(func=cmd_stage)

    cv = sub.add_parser("cover", help="one measured scenario per blocked family")
    cv.add_argument("--port", type=int, default=co.DEFAULT_PORT)
    cv.add_argument("--wait", type=int, default=150)
    cv.add_argument("--repo-root", default=None)
    cv.add_argument("--scenario-dir", default=None)
    cv.add_argument("--manifest", default=None)
    cv.add_argument("--families", default=None,
                    help="comma-separated constructor addresses; default is "
                         "every blocked family that has no scenario yet")
    cv.add_argument("--include-covered", action="store_true")
    cv.add_argument("--top", type=int, default=None)
    cv.add_argument("--slots", default=None)
    cv.add_argument("--depth", type=int, default=6)
    cv.add_argument("--timeout", type=float, default=300.0)
    cv.add_argument("--save-state", default="2v2 gred cotrolled players no cpu.sav")
    cv.set_defaults(func=cmd_cover)

    inv = sub.add_parser("inventory", help="blocked families, biggest first")
    inv.add_argument("--repo-root", default=None)
    inv.set_defaults(func=cmd_inventory)

    fam = sub.add_parser("families", help="family -> borg id table (offline)")
    fam.set_defaults(func=cmd_families)

    return p


def main(argv=None) -> int:
    a = build_parser().parse_args(argv)
    if getattr(a, "glob", "unset") is None:
        a.glob = a.glob_default
    return a.func(a)


if __name__ == "__main__":
    sys.exit(main())
