"""rsp_client.py — GDB Remote Serial Protocol client for Dolphin's GDB stub.

Targets the bundled Dolphin 2606-97 (dolphin/Dolphin.exe) with the stub enabled
via `--config Dolphin.General.GDBPort=<port>` (the key lives in [General], NOT
[Core]). Operational constraints learned from prior sessions on this rig
(scripts/dolphin-gdb-trace.mjs, .tmp/rsp_probe.py, project memory 2026-07-01):

  - Z0 (software) breakpoints work; Z2 watchpoints are REJECTED/flaky on this
    stub build — never rely on them.
  - Breakpoints only FIRE when Dolphin was launched with --debugger (measured
    2026-08-25: without it Z0 returns OK but never triggers, on every CPU
    core). With --debugger they fire under JIT64 too — full-speed emulation.
  - ONE CONNECTION PER BOOT (measured 2026-08-25): the stub accepts exactly
    one TCP client and never re-listens after that client disconnects. Never
    probe the port by connecting; hold one connection for the whole session.
  - After ^C the stub emits a spurious empty packet ($#00) and sometimes a
    duplicate stop packet; recv_packet/cmd filter both (skip_empty,
    discard_stops) or every later reply pairs shifted-by-one.
  - 'p'/'g'/'m'/'M'/'Z0'/'z0'/'s'/'c' are all served; stop packets carry pc as
    the expedited register 40:xxxxxxxx.

Pure stdlib (port-stack tooling is Python-only by owner rule).
"""
from __future__ import annotations

import re
import socket
import time

# A stop-reply packet: T<2-hex-sig> then n:r; pairs, or S<2-hex-sig>.
_STOP_RE = re.compile(rb"^(T[0-9a-fA-F]{2}([0-9a-fA-F]+:[0-9a-fA-F]+;)*|S[0-9a-fA-F]{2})$")


class RspError(RuntimeError):
    pass


class RspTimeout(RspError):
    pass


# PPC register numbers on Dolphin's stub (matches scripts/dolphin-gdb-trace.mjs):
# r0..r31 = 0..31, f0..f31 = 32..63, pc = 64, msr = 65, cr = 66, lr = 67,
# ctr = 68, xer = 69.
REG_PC = 64
REG_LR = 67
REG_CTR = 68


def _cks(payload: bytes) -> int:
    return sum(payload) & 0xFF


class RspClient:
    def __init__(self, host: str = "127.0.0.1", port: int = 55555,
                 timeout: float = 10.0, connect_timeout: float = 20.0):
        self.host = host
        self.port = port
        self.timeout = timeout
        self.sock = socket.create_connection((host, port), timeout=connect_timeout)
        self.sock.settimeout(timeout)
        self._rxbuf = b""

    # ---- transport -------------------------------------------------------
    def close(self) -> None:
        try:
            self.sock.close()
        except OSError:
            pass

    def _read1(self) -> bytes:
        c = self.sock.recv(1)
        if not c:
            raise RspError("eof from stub")
        return c

    def send_packet(self, payload: bytes) -> None:
        pkt = b"$" + payload + b"#" + f"{_cks(payload):02x}".encode()
        self.sock.sendall(pkt)
        # Wait for ack (+). The stub may interleave a stray stop packet; only
        # '+'/'-' are acks.
        while True:
            c = self._read1()
            if c == b"+":
                return
            if c == b"-":
                self.sock.sendall(pkt)  # retransmit once on NAK
                continue
            # Unexpected byte (e.g. '$' of an async packet): stash it back.
            self._rxbuf = c + self._rxbuf
            return

    def recv_packet(self, timeout: float | None = None,
                    skip_empty: bool = True) -> bytes:
        """Receive one packet payload.

        Dolphin 2606-97 stub quirk: async stop notifications (after ^C) are
        followed by a spurious EMPTY packet (`$#00`) and occasionally by a
        duplicate of the stop packet. Empty packets are protocol noise and are
        skipped by default — otherwise every later reply pairs with the wrong
        request and the whole session reads shifted-by-one garbage.
        """
        if timeout is not None:
            self.sock.settimeout(timeout)
        try:
            while True:
                buf = b""
                in_pkt = False
                while True:
                    if self._rxbuf:
                        c, self._rxbuf = self._rxbuf[:1], self._rxbuf[1:]
                    else:
                        c = self._read1()
                    if not in_pkt:
                        if c == b"$":
                            in_pkt = True
                            buf = b""
                        continue
                    if c == b"#":
                        # checksum (2 bytes), then ack
                        chk = b""
                        while len(chk) < 2:
                            if self._rxbuf:
                                chk += self._rxbuf[:1]
                                self._rxbuf = self._rxbuf[1:]
                            else:
                                chk += self._read1()
                        self.sock.sendall(b"+")
                        break
                    buf += c
                if buf == b"" and skip_empty:
                    continue
                return buf
        except socket.timeout as e:
            raise RspTimeout(f"no packet within {timeout or self.timeout}s") from e
        finally:
            self.sock.settimeout(self.timeout)

    def drain_async(self, settle_s: float = 0.2) -> list[bytes]:
        """Discard queued async packets (duplicate stops, empties) after a halt
        so the next command's reply pairs correctly."""
        drained = []
        while True:
            try:
                drained.append(self.recv_packet(timeout=settle_s, skip_empty=True))
            except (RspTimeout, RspError):
                return drained

    def cmd(self, payload: bytes, timeout: float | None = None,
            discard_stops: bool = False) -> bytes:
        """Send a command and return its reply.

        discard_stops: for data commands (m/p/g), skip any stray/duplicate stop
        packet (`T..` notifications the stub sometimes re-emits after a halt)
        that would otherwise be mistaken for the reply.
        """
        self.send_packet(payload)
        while True:
            reply = self.recv_packet(timeout)
            if discard_stops and reply[:1] in (b"T", b"S") and _STOP_RE.match(reply):
                continue
            return reply

    def interrupt(self) -> None:
        """Raw 0x03 — asks the stub to halt the CPU; a stop packet follows."""
        self.sock.sendall(b"\x03")

    # ---- protocol helpers ------------------------------------------------
    def q_supported(self) -> bytes:
        return self.cmd(b"qSupported")

    def halt_reason(self) -> bytes:
        return self.cmd(b"?")

    def read_reg(self, regno: int) -> int:
        raw = self.cmd(f"p{regno:x}".encode(), discard_stops=True)
        if raw.startswith(b"E") and len(raw) <= 3:
            raise RspError(f"p{regno:x} -> {raw!r}")
        return int(raw, 16)

    def read_gpr(self, n: int) -> int:
        return self.read_reg(n) & 0xFFFFFFFF

    def read_pc(self) -> int:
        return self.read_reg(REG_PC) & 0xFFFFFFFF

    def read_lr(self) -> int:
        return self.read_reg(REG_LR) & 0xFFFFFFFF

    def read_fpr_raw(self, n: int) -> int:
        """f<n> as the raw 64-bit ieee754 bit pattern (stub returns 16 hex)."""
        return self.read_reg(32 + n) & 0xFFFFFFFFFFFFFFFF

    def read_mem(self, addr: int, length: int) -> bytes:
        raw = self.cmd(f"m{addr:x},{length:x}".encode(), discard_stops=True)
        if raw.startswith(b"E") and len(raw) <= 3:
            raise RspError(f"m{addr:x},{length:x} -> {raw!r}")
        data = bytes.fromhex(raw.decode())
        if len(data) != length:
            raise RspError(f"short mem read at {addr:#x}: {len(data)}/{length}")
        return data

    def write_mem(self, addr: int, data: bytes) -> None:
        resp = self.cmd(f"M{addr:x},{len(data):x}:".encode() + data.hex().encode(),
                        discard_stops=True)
        if resp != b"OK":
            raise RspError(f"M{addr:#x},{len(data)} -> {resp!r}")

    def set_bp(self, addr: int) -> None:
        resp = self.cmd(f"Z0,{addr:x},4".encode(), discard_stops=True)
        if resp != b"OK":
            raise RspError(f"Z0 at {addr:#x} -> {resp!r}")

    def clear_bp(self, addr: int) -> None:
        resp = self.cmd(f"z0,{addr:x},4".encode(), discard_stops=True)
        if resp != b"OK":
            raise RspError(f"z0 at {addr:#x} -> {resp!r}")

    def cont(self, timeout: float) -> bytes:
        """Continue; block until the next stop packet (breakpoint hit)."""
        return self.cmd(b"c", timeout)

    def step(self, timeout: float = 5.0) -> bytes:
        return self.cmd(b"s", timeout)

    def detach(self) -> None:
        try:
            self.send_packet(b"D")
            # stub replies OK then closes; tolerate anything
            try:
                self.recv_packet(timeout=2.0)
            except RspError:
                pass
        except OSError:
            pass
        self.close()
