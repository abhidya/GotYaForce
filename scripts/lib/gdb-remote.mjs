// Minimal GDB remote-serial-protocol client for Dolphin's GDB stub.
// Extracted from the protocol code proven in scripts/dolphin-gdb-trace.mjs (kept standalone
// there; new trace tooling should import from here instead of re-copying).

import net from "node:net";

export function packet(payload) {
  let checksum = 0;
  for (const ch of payload) checksum = (checksum + ch.charCodeAt(0)) & 0xff;
  return `$${payload}#${checksum.toString(16).padStart(2, "0")}`;
}

export function parseHex32(raw) {
  if (!/^[0-9a-fA-F]{8}$/.test(raw ?? "")) return null;
  return Number.parseInt(raw, 16) >>> 0;
}

export function isMem1(value) {
  return Number.isInteger(value) && value >= 0x80000000 && value < 0x81800000;
}

/** Parse the PC out of a `T05…` stop packet (register 0x40 = PPC pc in Dolphin's stub). */
export function parseStopPc(payload) {
  const match = payload.match(/(?:^T[0-9a-fA-F]{2}|;)40:([0-9a-fA-F]{8});/);
  return match ? parseHex32(match[1]) : null;
}

export class GdbRemote {
  constructor(host = "127.0.0.1", port = 5555) {
    this.host = host;
    this.port = port;
    this.socket = null;
    this.buffer = "";
    this.queue = [];
    this.waiters = [];
  }

  connect() {
    this.socket = new net.Socket();
    this.socket.setEncoding("latin1");
    this.socket.on("data", (chunk) => this.onData(chunk));
    this.socket.on("error", (error) => {
      while (this.waiters.length) this.waiters.shift().reject(error);
    });
    return new Promise((resolve, reject) => {
      this.socket.once("connect", resolve);
      this.socket.once("error", reject);
      this.socket.connect(this.port, this.host);
    });
  }

  close() {
    this.socket?.end();
  }

  onData(chunk) {
    this.buffer += chunk;
    for (;;) {
      const start = this.buffer.indexOf("$");
      if (start < 0) {
        this.buffer = "";
        return;
      }
      if (start > 0) this.buffer = this.buffer.slice(start);
      const hash = this.buffer.indexOf("#", 1);
      if (hash < 0 || this.buffer.length < hash + 3) return;
      const payload = this.buffer.slice(1, hash);
      this.buffer = this.buffer.slice(hash + 3);
      this.socket.write("+");
      const waiter = this.waiters.shift();
      if (waiter) waiter.resolve(payload);
      else this.queue.push(payload);
    }
  }

  waitPacket(ms) {
    if (this.queue.length) return Promise.resolve(this.queue.shift());
    return new Promise((resolve, reject) => {
      const timer = setTimeout(() => {
        const index = this.waiters.findIndex((w) => w.resolve === resolve);
        if (index >= 0) this.waiters.splice(index, 1);
        reject(new Error(`timed out after ${ms}ms waiting for GDB packet`));
      }, ms);
      this.waiters.push({
        resolve: (payload) => {
          clearTimeout(timer);
          resolve(payload);
        },
        reject: (error) => {
          clearTimeout(timer);
          reject(error);
        },
      });
    });
  }

  async send(command, ms = 5000) {
    this.socket.write(packet(command));
    return this.waitPacket(ms);
  }

  interrupt() {
    this.socket.write(Buffer.from([0x03]));
  }

  /** Read one PPC register by stub id (0-31 = r0-r31, 0x40 = pc, 0x43 = lr). */
  async readReg(id, ms = 3000) {
    return parseHex32(await this.send(`p${id.toString(16)}`, ms));
  }

  /** Read `bytes` of memory at `address`; returns a Buffer or null on stub error. */
  async readMem(address, bytes, ms = 3000) {
    const raw = await this.send(`m${address.toString(16)},${bytes.toString(16)}`, ms);
    if (!raw || raw.startsWith("E") || /[^0-9a-fA-F]/.test(raw)) return null;
    return Buffer.from(raw, "hex");
  }

  /** Write a Buffer to memory at `address`; returns true on stub OK. */
  async writeMem(address, buffer, ms = 3000) {
    const raw = await this.send(`M${address.toString(16)},${buffer.length.toString(16)}:${buffer.toString("hex")}`, ms);
    return raw === "OK";
  }

  /** Insert a code breakpoint. Tries software (Z0) then hardware (Z1). Returns the kind used. */
  async setBreak(address) {
    for (const kind of ["0", "1"]) {
      const reply = await this.send(`Z${kind},${address.toString(16)},4`);
      if (reply === "OK") return kind;
    }
    throw new Error(`stub rejected breakpoint at 0x${address.toString(16)}`);
  }

  async clearBreak(address, kind) {
    await this.send(`z${kind},${address.toString(16)},4`).catch(() => {});
  }

  /** Continue and wait for the next stop packet; returns { payload, pc }. */
  async continueAndWaitStop(ms = 60000) {
    // Drop packets queued while no waiter was pending (e.g. a stop that raced a timeout).
    // If the CPU was already halted, the `c` below simply resumes it and the next real
    // stop arrives fresh — processing stale stops as fresh ones causes silent spin loops.
    this.queue.length = 0;
    const payload = await this.send("c", ms);
    let pc = parseStopPc(payload);
    // Dolphin's stop-reply format isn't guaranteed to carry register 0x40 — when the
    // packet doesn't parse, ask for the PC explicitly (the CPU is halted, so this is safe).
    if (pc === null) pc = await this.readReg(0x40).catch(() => null);
    return { payload, pc };
  }
}
