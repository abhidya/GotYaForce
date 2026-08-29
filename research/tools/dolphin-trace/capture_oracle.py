#!/usr/bin/env python3
"""capture_oracle.py — per-call oracle-case capture from the real game in Dolphin.

Design contract: docs/playable-port-design.md Stage B ("Dolphin trace oracles",
v1) — an RSP client sets breakpoints at a unit function's entry, and per call
records (args, referenced memory, return, memory writes), serialized into the
existing oracle-harness corpus format (a JSONL fixture replayed by
research/decomp/oracle-harness/run-unit.mjs through a per-unit spec module).

Subcommands
-----------
  launch   Start OUR OWN Dolphin instance (never the port driver's anything)
           with the GDB stub listening and — by default — the Null video
           backend so capture cannot contend with the LLM for the GPU.
  stop     Stop the Dolphin instance previously started by `launch` (by PID
           file — never touches any other process).
  probe    Connect to the stub and prove halt/regs/mem primitives work.
  scout    Set entry breakpoints on every function of a staged unit and count
           which ones actually fire in the running game — the empirical way to
           pick a capture target.
  capture  Plan-driven per-call capture: N hits of one function, emitting the
           trace fixture JSONL.

THE ONE-CONNECTION RULE (measured on the bundled Dolphin 2606-97, 2026-08-25):
the stub accepts exactly ONE TCP client per emulator boot and never re-listens
after that client disconnects. So: never "test" the port by connecting to it
(launch --wait polls netstat instead), and probe/scout/capture each consume the
boot they attach to — relaunch Dolphin between attaching commands. The
savestate makes a relaunch cost ~15 s.

Capture plan (plans/<unit>.<fn>.json) — authored from the unit's verbatim C:
  {
    "unit": "...", "fn": "...", "addr": "0x8...",
    "args":   [{"reg": "r3"}, {"reg": "r4"}],
    "reads":  [{"id": "...", "addr": "<expr>", "width": 2|4|8,
                "capture_only": false}],
    "ret":    {"reg": "r3"} | null,
    "writes": [{"id": "...", "addr": "<expr>", "width": 2}]
  }
Address expressions may use the captured entry registers (r0..r31), hex
literals, + - * & | << >> ( ), and [e] meaning the big-endian u32 loaded from
address e in game memory. Every memory value is recorded as raw BIG-ENDIAN hex
plus its absolute address; byte order is the replay spec's job (the harness
arena is little-endian with per-element swap widths — see
gen_arena_rom_provenance.py).

Stub ground rules (see rsp_client.py): Z0 breakpoints only (Z2 rejected);
empty/duplicate stop packets are protocol noise the client filters.
"""
from __future__ import annotations

import argparse
import json
import os
import re
import subprocess
import sys
import time
from datetime import datetime, timezone
from pathlib import Path

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from rsp_client import RspClient, RspError, RspTimeout  # noqa: E402

REPO_ROOT = Path(__file__).resolve().parents[3]


def _main_checkout_root() -> Path:
    """Root of the MAIN checkout even when running from a linked worktree.

    Big untracked assets (dolphin/, the disc, savestates, user-data/) live only
    in the main checkout; code may run from an isolated worktree.
    """
    try:
        common = subprocess.run(
            ["git", "rev-parse", "--path-format=absolute", "--git-common-dir"],
            cwd=str(REPO_ROOT), capture_output=True, text=True, check=True,
        ).stdout.strip()
        root = Path(common).parent
        if (root / "dolphin").exists():
            return root
    except (subprocess.CalledProcessError, OSError):
        pass
    return REPO_ROOT


ASSET_ROOT = _main_checkout_root()
DEFAULT_PORT = 55555
MEM1_LO, MEM1_HI = 0x80000000, 0x81800000

SCENARIO_DIR = Path(__file__).resolve().parent / "scenarios"


def load_scenario(name_or_path: str) -> dict:
    """A scripted game state (scenarios/<name>.json — see scenarios/README.md):
    savestate for `launch`, default --inject / --game-state for
    `scout`/`capture`. Explicit CLI flags always override scenario defaults.
    """
    path = Path(name_or_path)
    if path.suffix != ".json":
        path = SCENARIO_DIR / f"{name_or_path}.json"
    if not path.is_file():
        known = sorted(p.stem for p in SCENARIO_DIR.glob("*.json"))
        sys.exit(f"no scenario at {path} (known: {known})")
    data = json.loads(path.read_text(encoding="utf-8-sig"))
    if data.get("scenario_schema") != 1:
        sys.exit(f"{path}: scenario_schema != 1")
    if data.get("dtm"):
        # Owner-recorded DTMs are the design's deterministic capture input
        # (playable-port-design.md G4/I3). The field is reserved so a DTM
        # slots straight into this schema; playback wiring into `launch` is
        # refused (not silently skipped) until verified on the bundled build.
        sys.exit(f"{path}: names a DTM, but DTM playback is not wired into "
                 "launch yet — see scenarios/README.md")
    return data


def scenario_save_state(scenario: dict) -> str | None:
    save = scenario.get("save_state")
    if not save:
        return None
    path = Path(save)
    if not path.is_absolute():
        path = ASSET_ROOT / save
    return str(path)


def now_iso() -> str:
    return datetime.now(timezone.utc).isoformat().replace("+00:00", "Z")


def is_mem1(v: int) -> bool:
    return MEM1_LO <= v < MEM1_HI


STOP_PC_RE = re.compile(rb"(?:^T[0-9a-fA-F]{2}|;)40:([0-9a-fA-F]{8});")


def stop_pc(payload: bytes) -> int | None:
    m = STOP_PC_RE.search(payload)
    return int(m.group(1), 16) if m else None


# --------------------------------------------------------------------------
# stub driver: one persistent connection, explicit halt windows
# --------------------------------------------------------------------------

class StubDriver:
    def __init__(self, port: int):
        self.rsp = RspClient(port=port)
        self.bps: set[int] = set()
        self.running = True  # the CPU runs when the stub accepts us

    def halt(self) -> bytes:
        self.rsp.interrupt()
        stop = self.rsp.recv_packet(timeout=5.0)
        self.rsp.drain_async(0.15)
        self.running = False
        return stop

    def ensure_halted(self) -> None:
        if self.running:
            self.halt()

    def resume_nowait(self) -> None:
        """Continue without blocking for the stop (breather / final release)."""
        self.rsp.send_packet(b"c")
        self.running = True

    def cont_until_stop(self, timeout: float) -> bytes | None:
        """Continue; block for the next stop. None on timeout (CPU left
        halted again via interrupt)."""
        self.rsp.send_packet(b"c")
        self.running = True
        try:
            stop = self.rsp.recv_packet(timeout=timeout)
        except RspTimeout:
            self.halt()
            return None
        self.rsp.drain_async(0.05)
        self.running = False
        return stop

    def set_bp(self, addr: int) -> None:
        self.rsp.set_bp(addr)
        self.bps.add(addr)

    def clear_bp(self, addr: int) -> None:
        self.rsp.clear_bp(addr)
        self.bps.discard(addr)

    def cleanup(self) -> None:
        """Best-effort: strip breakpoints and leave the game RUNNING. The
        socket close that follows kills the stub for this boot (one-connection
        rule) but the game itself keeps playing."""
        try:
            self.ensure_halted()
            for addr in list(self.bps):
                try:
                    self.clear_bp(addr)
                except RspError:
                    pass
            self.resume_nowait()
        except (RspError, OSError):
            pass
        finally:
            self.rsp.close()


# --------------------------------------------------------------------------
# pad injection (drives the game while headless — proven pattern from
# scripts/dolphin-gdb-trace.mjs: after PADRead lands the raw PADStatus[4] at
# fixed 0x803c72fc, overwrite one port's status at the 0x8010d4d0 breakpoint,
# before the game-side normalization consumes it)
# --------------------------------------------------------------------------

PAD_INJECT_BP = 0x8010d4d0     # zz_010d450_: after PADRead, before normalization
PAD_STATUS_ARRAY = 0x803c72fc  # PADStatus[4], 12 bytes per port
PAD_BUTTONS = {"left": 0x0001, "right": 0x0002, "down": 0x0004, "up": 0x0008,
               "z": 0x0010, "r": 0x0020, "l": 0x0040, "a": 0x0100, "b": 0x0200,
               "x": 0x0400, "y": 0x0800, "start": 0x1000}


class PadInjector:
    """Synthesizes controller input each frame at the injection breakpoint.

    Patterns:
      circle  — stick rotates continuously (constant movement + turning; makes
                heading/turn/velocity actor helpers fire without a human).
      hold    — fixed stick vector.
      combat  — circling stick PLUS a round-robin of button
                PRESS/RELEASE edges.

    Why `combat` exists (measured 2026-08-29): `circle` and `hold` write the
    same button mask every single frame, so the game only ever sees a button
    already-held, never a fresh press. Action-table slots that transition on
    a rising edge (attacks, specials, supers) therefore cannot be reached,
    which is why `circle+b` only ever produced per-frame camera/UI hits while
    every family-gated export scouted 0 across six verified units.
    """

    def __init__(self, port_idx: int, pattern: str, buttons: int,
                 stick: tuple[int, int] = (0, 96), step_deg: float = 4.0,
                 cycle: list[int] | None = None,
                 hold_frames: int = 6, gap_frames: int = 10):
        self.port_idx = port_idx
        self.pattern = pattern
        self.buttons = buttons
        self.stick = stick
        self.step = step_deg
        self.cycle = cycle or []
        self.hold_frames = hold_frames
        self.gap_frames = gap_frames
        self.frame = 0

    def on_hit(self, rsp) -> None:
        import math
        if self.pattern in ("circle", "combat"):
            ang = math.radians(self.frame * self.step)
            sx = int(96 * math.cos(ang))
            sy = int(96 * math.sin(ang))
        else:
            sx, sy = self.stick
        buttons = self.buttons
        if self.pattern == "combat" and self.cycle:
            period = self.hold_frames + self.gap_frames
            slot = (self.frame // period) % len(self.cycle)
            if (self.frame % period) < self.hold_frames:
                buttons |= self.cycle[slot]
        buf = bytes([
            (buttons >> 8) & 0xFF, buttons & 0xFF,
            sx & 0xFF, sy & 0xFF,   # main stick
            0, 0,                   # substick
            0, 0,                   # triggers
            0, 0,                   # analog A/B
            0, 0,                   # err=0, pad
        ])
        rsp.write_mem(PAD_STATUS_ARRAY + self.port_idx * 12, buf)
        self.frame += 1


def parse_inject_arg(spec: str | None) -> PadInjector | None:
    """--inject "circle" | "hold:sx,sy" | "circle+b" (buttons by name)."""
    if not spec:
        return None
    buttons = 0
    parts = spec.split("+")
    head = parts[0]
    for b in parts[1:]:
        if b.lower() not in PAD_BUTTONS:
            sys.exit(f"unknown button {b!r} in --inject (known: {sorted(PAD_BUTTONS)})")
        buttons |= PAD_BUTTONS[b.lower()]
    if head.startswith("hold:"):
        sx, sy = (int(v) for v in head[5:].split(","))
        return PadInjector(0, "hold", buttons, stick=(sx, sy))
    if head.startswith("combat:"):
        cycle = []
        for n in head[len("combat:"):].split(","):
            if not n:
                continue
            if n.lower() not in PAD_BUTTONS:
                sys.exit(f"unknown button {n!r} in --inject combat cycle "
                         f"(known: {sorted(PAD_BUTTONS)})")
            cycle.append(PAD_BUTTONS[n.lower()])
        if not cycle:
            sys.exit("--inject combat: needs at least one button")
        return PadInjector(0, "combat", buttons, cycle=cycle)
    if head in ("circle", ""):
        return PadInjector(0, "circle", buttons)
    sys.exit(f"unknown --inject pattern {head!r}")


# --------------------------------------------------------------------------
# launch / stop
# --------------------------------------------------------------------------

def default_pid_file(user_dir: Path) -> Path:
    return user_dir / "capture-dolphin.pid"


def pid_ledger_file(user_dir: Path) -> Path:
    """Append-only ledger of every instance this tool launched for user_dir.

    The single-slot pid file is not enough: a second `launch` overwrites it and
    the previous instance becomes permanently untracked. The ledger is the
    tool's own marker and is the ONLY orphan signal this module uses.
    """
    return user_dir / "capture-dolphin.pids"


def _pid_alive(pid: int) -> bool:
    out = subprocess.run(["tasklist", "/FI", f"PID eq {pid}", "/NH", "/FO", "CSV"],
                         capture_output=True, text=True).stdout
    return f'"{pid}"' in out


def _tracked_pids(user_dir: Path) -> list[int]:
    pids: set[int] = set()
    for f in (default_pid_file(user_dir), pid_ledger_file(user_dir)):
        try:
            text = f.read_text()
        except OSError:
            continue
        for tok in text.split():
            try:
                pids.add(int(tok))
            except ValueError:
                pass
    return sorted(pids)


def reap_tracked(user_dir: Path) -> list[int]:
    """Kill every tracked instance and CONFIRM death before forgetting it.

    Two defects this closes (measured 2026-08-29, verify-sweep run):
      * the old cmd_stop unlinked the pid file whether or not taskkill worked,
        so a Dolphin that refused to die became untracked forever and then
        tripped verify-sweep's own `dolphin_contended` guard, aborting the
        remaining unit budget;
      * a second `launch` overwrote the single-slot pid file, orphaning the
        instance it replaced.

    Orphan detection is by this ledger + the user_dir marker ONLY. It must
    never be "the process has no parent": `launch` DETACHES Dolphin on purpose,
    so every healthy capture instance is parentless, and reaping on that signal
    kills live captures (observed: 8 instances killed mid-capture, turning a
    real run into a bogus `stub session died` result).
    """
    killed: list[int] = []
    survivors: list[int] = []
    for pid in _tracked_pids(user_dir):
        if not _pid_alive(pid):
            continue
        subprocess.run(["taskkill", "/PID", str(pid), "/T", "/F"],
                       capture_output=True, text=True)
        for _ in range(40):
            if not _pid_alive(pid):
                break
            time.sleep(0.25)
        (killed if not _pid_alive(pid) else survivors).append(pid)
    if survivors:
        # keep the ledger so the next launch/stop tries again; never silently
        # forget a live instance.
        pid_ledger_file(user_dir).write_text(
            "".join(str(p) + chr(10) for p in survivors))
        try:
            default_pid_file(user_dir).unlink()
        except FileNotFoundError:
            pass
        raise RuntimeError(
            f"Dolphin pid(s) {survivors} survived taskkill; still tracked")
    for f in (default_pid_file(user_dir), pid_ledger_file(user_dir)):
        try:
            f.unlink()
        except FileNotFoundError:
            pass
    return killed


def _port_listening(port: int) -> bool:
    out = subprocess.run(["netstat", "-an", "-p", "TCP"],
                         capture_output=True, text=True).stdout
    return any(f":{port} " in line and "LISTENING" in line
               for line in out.splitlines())


def cmd_launch(a: argparse.Namespace) -> int:
    if a.scenario:
        scenario = load_scenario(a.scenario)
        if not a.save_state:
            a.save_state = scenario_save_state(scenario)
    dolphin = Path(a.dolphin)
    iso = Path(a.iso)
    user_dir = Path(a.user_dir)
    if not dolphin.exists():
        sys.exit(f"no Dolphin at {dolphin}")
    if not iso.exists():
        sys.exit(f"no disc at {iso}")
    user_dir.mkdir(parents=True, exist_ok=True)

    # refuse to double-launch onto a port already served (netstat, never a
    # probe connection — the stub is single-client and a probe would eat it)
    if _port_listening(a.port):
        sys.exit(f"something already listens on 127.0.0.1:{a.port} — refusing "
                 f"(use --port for a second instance, or `stop` the old one)")

    # --debugger is LOAD-BEARING: without it the interpreter never checks
    # breakpoints — Z0 installs return OK but no bp ever fires (measured
    # 2026-08-25; the proven launcher scripts/launch-dolphin-gdb.mjs always
    # passed it).
    args = [str(dolphin), "--user", str(user_dir), "--batch", "--debugger",
            "--exec", str(iso)]
    if a.save_state:
        sav = Path(a.save_state)
        if not sav.exists():
            sys.exit(f"no save state at {sav}")
        args.append(f"--save_state={sav}")
    configs = [
        f"Dolphin.General.GDBPort={a.port}",
        f"Dolphin.Core.CPUCore={a.cpu_core}",
        "Dolphin.Core.CPUThread=False",
        f"Dolphin.Core.GFXBackend={a.gfx}",
        "Dolphin.Interface.PauseOnFocusLost=False",
        "Dolphin.Interface.ConfirmStop=False",
        # standard controllers on all 4 ports (matches user-data/dolphin-trace;
        # without them PADRead reports no-pad and injected input is ignored)
        "Dolphin.Core.SIDevice0=6",
        "Dolphin.Core.SIDevice1=6",
        "Dolphin.Core.SIDevice2=6",
        "Dolphin.Core.SIDevice3=6",
    ]
    for c in configs:
        args += ["--config", c]

    # never leave the instance we are about to replace untracked
    reap_tracked(user_dir)
    proc = subprocess.Popen(
        args, cwd=str(dolphin.parent),
        stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL,
        creationflags=getattr(subprocess, "DETACHED_PROCESS", 0)
        | getattr(subprocess, "CREATE_NEW_PROCESS_GROUP", 0),
    )
    pid_file = default_pid_file(user_dir)
    pid_file.write_text(str(proc.pid))
    with pid_ledger_file(user_dir).open("a", encoding="utf-8") as fh:
        fh.write(str(proc.pid) + chr(10))
    print(json.dumps({"pid": proc.pid, "args": args,
                      "pid_file": str(pid_file)}, indent=2))
    if a.wait:
        # IMPORTANT: never test the port by connecting — the stub accepts
        # exactly one client per boot. netstat only.
        deadline = time.monotonic() + a.wait
        while time.monotonic() < deadline:
            if _port_listening(a.port):
                print(f"gdb stub is listening on 127.0.0.1:{a.port}")
                return 0
            if proc.poll() is not None:
                sys.exit(f"Dolphin exited early with code {proc.returncode}")
            time.sleep(1.0)
        sys.exit(f"stub not listening after {a.wait}s — check the instance")
    return 0


def cmd_stop(a: argparse.Namespace) -> int:
    """Stop every instance this tool launched for --user-dir.

    Called from the driver's per-export `finally`, so "nothing to stop" is a
    normal outcome and exits 0; only a survivor is an error.
    """
    user_dir = Path(a.user_dir)
    killed = reap_tracked(user_dir)
    if killed:
        print(f"stopped {len(killed)} tracked instance(s): {killed}")
    else:
        print("nothing tracked to stop")
    return 0


# --------------------------------------------------------------------------
# probe
# --------------------------------------------------------------------------

def cmd_probe(a: argparse.Namespace) -> int:
    d = StubDriver(a.port)
    try:
        print("qSupported:", d.rsp.q_supported()[:100])
        stop = d.halt()
        print("stop:", stop[:60], "pc-from-stop:", hex(stop_pc(stop) or 0))
        pc = d.rsp.read_pc()
        lr = d.rsp.read_lr()
        r3 = d.rsp.read_gpr(3)
        print(f"pc={pc:#010x} lr={lr:#010x} r3={r3:#010x}")
        head = d.rsp.read_mem(0x80000000, 6)
        print("mem[0x80000000..6]:", head.hex(), repr(head))
        ok = head[:3] == b"GG4"
        print("game-id check (GG4):", "OK" if ok else "MISMATCH")
        return 0 if ok else 1
    finally:
        d.cleanup()
        print("NOTE: this consumed the boot's one stub connection — relaunch "
              "Dolphin before scout/capture.")


# --------------------------------------------------------------------------
# scout
# --------------------------------------------------------------------------

UNIT_MARK = re.compile(r"// ==== (8[0-9a-f]{7})\s+(\S+) ====")


def unit_functions(unit: str) -> list[tuple[int, str]]:
    src = (REPO_ROOT / "research/decomp/port-units-staging" / unit / "unit.c")
    text = src.read_text(encoding="utf-8", errors="replace")
    return [(int(addr, 16), name) for addr, name in UNIT_MARK.findall(text)]


def cmd_scout(a: argparse.Namespace) -> int:
    if a.scenario:
        scenario = load_scenario(a.scenario)
        if not a.inject:
            a.inject = scenario.get("inject")
    if a.unit:
        fns = unit_functions(a.unit)
    elif a.addrs_file:
        text = Path(a.addrs_file).read_text().strip().replace("\n", ",")
        fns = [(int(x, 16), x) for x in text.split(",") if x]
    else:
        fns = [(int(x, 16), x) for x in a.addrs.split(",")]
    if not fns:
        sys.exit("no functions to scout")
    by_addr = {addr: name for addr, name in fns}
    counts = {name: 0 for _, name in fns}
    stray = 0
    injector = parse_inject_arg(a.inject)
    d = StubDriver(a.port)
    try:
        d.halt()
        for addr in by_addr:
            d.set_bp(addr)
        if injector is not None:
            d.set_bp(PAD_INJECT_BP)
        t_end = time.monotonic() + a.seconds
        while time.monotonic() < t_end:
            stop = d.cont_until_stop(timeout=min(5.0, max(0.5, t_end - time.monotonic())))
            if stop is None:
                continue
            pc = stop_pc(stop)
            if pc is None:
                pc = d.rsp.read_pc()
            if injector is not None and pc == PAD_INJECT_BP:
                injector.on_hit(d.rsp)
                continue
            name = by_addr.get(pc)
            if name is not None:
                counts[name] += 1
            else:
                stray += 1
    finally:
        d.cleanup()
    print(json.dumps({"scouted_s": a.seconds, "hits": counts,
                      "stray_stops": stray,
                      "injected_frames": injector.frame if injector else 0}, indent=2))
    return 0


# --------------------------------------------------------------------------
# capture
# --------------------------------------------------------------------------

EXPR_TOKEN = re.compile(r"^[\sr0-9a-fA-Fx+\-*&|()<>\[\]]+$")


class ExprEval:
    """Tiny address-expression evaluator over captured registers + game memory.

    Grammar: python expression subset; `[e]` is rewritten to `M(e)` = the
    big-endian u32 at address e read from the halted game. Only registers,
    integers and arithmetic/bit operators are allowed (guarded by regex).
    """

    def __init__(self, regs: dict[str, int], readmem):
        self.ns = {**regs, "M": lambda addr: int.from_bytes(readmem(int(addr) & 0xFFFFFFFF, 4), "big")}

    def eval(self, expr: str) -> int:
        if not EXPR_TOKEN.match(expr):
            raise ValueError(f"illegal characters in address expression: {expr!r}")
        py = expr.replace("[", "M(").replace("]", ")")
        return int(eval(py, {"__builtins__": {}}, self.ns)) & 0xFFFFFFFF  # noqa: S307


def load_plan(path: Path) -> dict:
    plan = json.loads(path.read_text())
    for key in ("unit", "fn", "addr", "args", "reads", "writes"):
        if key not in plan:
            sys.exit(f"plan {path} missing key {key!r}")
    return plan


def capture_one_hit(d: StubDriver, plan: dict, entry: int, hit_timeout: float,
                    ret_timeout: float, injector: PadInjector | None = None) -> dict | None:
    """CPU halted, entry bp installed. Returns a case dict, None on no-hit.
    Leaves the CPU halted with the entry bp installed."""
    rsp = d.rsp
    deadline = time.monotonic() + hit_timeout
    while True:
        stop = d.cont_until_stop(timeout=max(0.5, deadline - time.monotonic()))
        if stop is None:
            return None
        pc = stop_pc(stop)
        if pc is None:
            pc = rsp.read_pc()
        if injector is not None and pc == PAD_INJECT_BP:
            injector.on_hit(rsp)
            if time.monotonic() >= deadline:
                return None
            continue
        break
    if pc != entry:
        return None  # stray stop

    regs = {f"r{i}": rsp.read_gpr(i) for i in range(0, 11)}
    lr = rsp.read_lr()
    args = [regs[a_["reg"]] for a_ in plan["args"]]

    ev = ExprEval(regs, rsp.read_mem)
    reads = []
    for item in plan["reads"]:
        try:
            addr = ev.eval(item["addr"])
            if not is_mem1(addr):
                raise RspError(f"address {addr:#x} outside MEM1")
            data = rsp.read_mem(addr, item["width"])
        except RspError:
            if item.get("optional"):
                continue  # e.g. a pointer chase that is invalid on this path
            raise
        reads.append({"id": item["id"], "addr": f"0x{addr:08x}",
                      "width": item["width"], "be_hex": data.hex()})

    # run to the caller's return address
    d.clear_bp(entry)
    d.set_bp(lr)
    ret_deadline = time.monotonic() + ret_timeout
    while True:
        stop2 = d.cont_until_stop(timeout=max(0.5, ret_deadline - time.monotonic()))
        pc2 = None if stop2 is None else (stop_pc(stop2) or rsp.read_pc())
        if (stop2 is not None and injector is not None and pc2 == PAD_INJECT_BP
                and time.monotonic() < ret_deadline):
            injector.on_hit(rsp)
            continue
        break
    ok = stop2 is not None and pc2 == lr
    d.clear_bp(lr)
    if not ok:
        d.set_bp(entry)
        return None

    ret = rsp.read_gpr(3) if plan.get("ret") else None
    fret = None
    if plan.get("ret") and plan["ret"].get("reg") == "f1":
        fret = f"{rsp.read_fpr_raw(1):016x}"

    writes = []
    for item in plan["writes"]:
        addr = ev.eval(item["addr"])  # entry regs — plans must address off arg regs
        data = rsp.read_mem(addr, item["width"])
        writes.append({"id": item["id"], "addr": f"0x{addr:08x}",
                       "width": item["width"], "be_hex": data.hex()})

    d.set_bp(entry)
    case = {"kind": "case", "fn": plan["fn"],
            "args": [f"0x{v:08x}" for v in args],
            "lr": f"0x{lr:08x}", "reads": reads, "writes": writes}
    if ret is not None:
        case["ret"] = f"0x{ret & 0xFFFFFFFF:08x}"
    if fret is not None:
        case["fret_bits"] = fret
    return case


def cmd_capture(a: argparse.Namespace) -> int:
    if a.scenario:
        scenario = load_scenario(a.scenario)
        if not a.inject:
            a.inject = scenario.get("inject")
        if a.game_state == "unspecified":
            a.game_state = scenario.get("game_state") or "unspecified"
    plan = load_plan(Path(a.plan))
    entry = int(plan["addr"], 16)
    n_target = a.n
    cases: list[dict] = []
    t0 = time.monotonic()
    deadline = t0 + a.max_seconds
    misses = 0

    injector = parse_inject_arg(a.inject)
    d = StubDriver(a.port)
    try:
        d.halt()
        d.set_bp(entry)
        if injector is not None:
            d.set_bp(PAD_INJECT_BP)
        while len(cases) < n_target and time.monotonic() < deadline:
            case = capture_one_hit(d, plan, entry, hit_timeout=a.hit_timeout,
                                   ret_timeout=a.ret_timeout, injector=injector)
            if case is None:
                misses += 1
                if misses >= a.max_misses:
                    print(f"{misses} consecutive no-hit windows — the function "
                          f"is not firing in this game state; stopping",
                          file=sys.stderr)
                    break
                continue
            misses = 0
            case["n"] = len(cases)
            cases.append(case)
            if len(cases) % 20 == 0:
                print(f"  {len(cases)}/{n_target} cases "
                      f"({time.monotonic()-t0:.0f}s)")
    except (RspError, OSError) as e:
        print(f"stub session died: {e} — writing what was captured",
              file=sys.stderr)
    finally:
        d.cleanup()

    header = {
        "kind": "header", "fixture_schema": 1, "trace_schema": 1,
        "unit": plan["unit"], "fn": plan["fn"], "addr": plan["addr"],
        "reference_kind": "dolphin_trace",
        "dumped_at": now_iso(),
        "counts": {"case": len(cases)},
        "source": {
            "emulator": "bundled Dolphin 2606-97 (dolphin/Dolphin.exe)",
            "stub": f"gdb-rsp 127.0.0.1:{a.port}, Z0 entry+LR breakpoints",
            "game_state": a.game_state,
            "capture_tool": "research/tools/dolphin-trace/capture_oracle.py",
            "plan": str(Path(a.plan).as_posix()),
            "pad_injection": a.inject or None,
            "injected_frames": injector.frame if injector else 0,
            "scenario": a.scenario or None,
        },
    }
    out = Path(a.out)
    out.parent.mkdir(parents=True, exist_ok=True)
    with out.open("w", encoding="utf-8", newline="\n") as f:
        f.write(json.dumps(header) + "\n")
        for c in cases:
            f.write(json.dumps(c) + "\n")
    print(json.dumps({"cases": len(cases), "out": str(out),
                      "elapsed_s": round(time.monotonic() - t0, 1)}, indent=2))
    return 0 if len(cases) >= n_target else 1


# --------------------------------------------------------------------------

def main() -> int:
    p = argparse.ArgumentParser(description=__doc__,
                                formatter_class=argparse.RawDescriptionHelpFormatter)
    sub = p.add_subparsers(dest="cmd")
    sub.required = True

    lp = sub.add_parser("launch", help="start our own Dolphin with the GDB stub")
    lp.add_argument("--dolphin", default=str(ASSET_ROOT / "dolphin/Dolphin.exe"))
    lp.add_argument("--iso", default=str(ASSET_ROOT / "Gotcha Force.iso"))
    lp.add_argument("--save-state", default=None)
    lp.add_argument("--user-dir", default=str(ASSET_ROOT / "user-data/dolphin-oracle"))
    lp.add_argument("--port", type=int, default=DEFAULT_PORT)
    lp.add_argument("--cpu-core", type=int, default=1,
                    help="1=JIT64 (bp-proven WITH --debugger, near full speed); 0=interpreter fallback")
    lp.add_argument("--gfx", default="Null",
                    help="video backend; Null keeps the GPU free for the LLM")
    lp.add_argument("--wait", type=float, default=90.0,
                    help="seconds to wait for the stub socket (0 = don't)")
    lp.add_argument("--scenario", default=None,
                    help="scenario name/path (scenarios/README.md); supplies "
                         "the savestate when --save-state is not given")
    lp.set_defaults(func=cmd_launch)

    sp = sub.add_parser("stop", help="stop the instance `launch` started")
    sp.add_argument("--user-dir", default=str(ASSET_ROOT / "user-data/dolphin-oracle"))
    sp.set_defaults(func=cmd_stop)

    pp = sub.add_parser("probe", help="prove stub primitives (consumes the boot's connection)")
    pp.add_argument("--port", type=int, default=DEFAULT_PORT)
    pp.set_defaults(func=cmd_probe)

    sc = sub.add_parser("scout", help="count which unit functions fire")
    sc.add_argument("--unit", default=None)
    sc.add_argument("--addrs", default=None,
                    help="comma-separated hex addresses (alternative to --unit)")
    sc.add_argument("--addrs-file", default=None,
                    help="file with comma/newline-separated hex addresses")
    sc.add_argument("--seconds", type=float, default=60.0)
    sc.add_argument("--inject", default=None,
                    help='synthesize P1 input each frame: "circle", "hold:sx,sy", '
         '"combat:b,x,a" (circling stick + button press/release edges), '
                         'optionally +buttons e.g. "circle+b" (dolphin-gdb-trace.mjs pattern)')
    sc.add_argument("--scenario", default=None,
                    help="scenario name/path; default for --inject")
    sc.add_argument("--port", type=int, default=DEFAULT_PORT)
    sc.set_defaults(func=cmd_scout)

    cp = sub.add_parser("capture", help="plan-driven per-call capture")
    cp.add_argument("--plan", required=True)
    cp.add_argument("--n", type=int, default=100)
    cp.add_argument("--out", required=True)
    cp.add_argument("--port", type=int, default=DEFAULT_PORT)
    cp.add_argument("--game-state", default="unspecified",
                    help="human note: savestate/attract used during capture")
    cp.add_argument("--inject", default=None,
                    help='synthesize P1 input each frame (see scout --inject)')
    cp.add_argument("--scenario", default=None,
                    help="scenario name/path; defaults for --inject and "
                         "--game-state")
    cp.add_argument("--hit-timeout", type=float, default=10.0)
    cp.add_argument("--ret-timeout", type=float, default=8.0)
    cp.add_argument("--max-seconds", type=float, default=1800.0)
    cp.add_argument("--max-misses", type=int, default=10)
    cp.set_defaults(func=cmd_capture)

    a = p.parse_args()
    if a.cmd == "scout" and not a.unit and not a.addrs and not a.addrs_file:
        p.error("scout needs --unit, --addrs, or --addrs-file")
    return a.func(a)


if __name__ == "__main__":
    raise SystemExit(main())
