import fs from "node:fs";
import net from "node:net";
import path from "node:path";
import { fileURLToPath } from "node:url";

const repoRoot = path.resolve(path.dirname(fileURLToPath(import.meta.url)), "..");
const argsByName = parseArgs(process.argv.slice(2));
const planPath = argsByName.get("plan") ?? process.env.TRACE_PLAN ?? path.join(repoRoot, "research", "traces", "GG4E", "breakpoints-watchpoints.json");
const outDir = argsByName.get("out-dir") ?? process.env.TRACE_OUT_DIR ?? path.join(repoRoot, "user-data", "dolphin-trace", "traces");

const host = argsByName.get("host") ?? process.env.GDB_HOST ?? "127.0.0.1";
const port = Number.parseInt(argsByName.get("port") ?? process.env.GDB_PORT ?? "5555", 10);
const maxHits = Number.parseInt(argsByName.get("max-hits") ?? process.env.TRACE_MAX_HITS ?? "120", 10);
const timeoutMs = Number.parseInt(argsByName.get("timeout-ms") ?? process.env.TRACE_TIMEOUT_MS ?? "60000", 10);
const commandTimeoutMs = Number.parseInt(argsByName.get("command-timeout-ms") ?? process.env.TRACE_COMMAND_TIMEOUT_MS ?? "15000", 10);
const injectPadButtonsRaw = argsByName.get("inject-pad-buttons") ?? process.env.TRACE_INJECT_PAD_BUTTONS ?? "";
const injectPadFrames = Number.parseInt(argsByName.get("inject-pad-frames") ?? process.env.TRACE_INJECT_PAD_FRAMES ?? "0", 10);
const injectPadPort = Number.parseInt(argsByName.get("inject-pad-port") ?? process.env.TRACE_INJECT_PAD_PORT ?? "0", 10);
const groupsFilter = csvSet(argsByName.get("groups") ?? process.env.TRACE_GROUPS);
const skipIds = csvSet(argsByName.get("skip-ids") ?? process.env.TRACE_SKIP_IDS);
const onlyIds = csvSet(argsByName.get("only-ids") ?? process.env.TRACE_ONLY_IDS);
const dryRun = argsByName.has("dry-run") || process.env.TRACE_DRY_RUN === "1";

const PAD_STATUS_SIZE = 12;
const PAD_BUTTON_BITS = {
  dLeft: 0x0001,
  dRight: 0x0002,
  dDown: 0x0004,
  dUp: 0x0008,
  Z: 0x0010,
  R: 0x0020,
  L: 0x0040,
  A: 0x0100,
  B: 0x0200,
  X: 0x0400,
  Y: 0x0800,
  Start: 0x1000,
};

function parseArgs(argv) {
  const parsed = new Map();
  for (let i = 0; i < argv.length; i += 1) {
    const arg = argv[i];
    if (!arg.startsWith("--")) continue;
    const eq = arg.indexOf("=");
    if (eq >= 0) parsed.set(arg.slice(2, eq), arg.slice(eq + 1));
    else if (argv[i + 1] && !argv[i + 1].startsWith("--")) parsed.set(arg.slice(2), argv[++i]);
    else parsed.set(arg.slice(2), "");
  }
  return parsed;
}

function csvSet(value) {
  return new Set((value ?? "").split(",").map((v) => v.trim()).filter(Boolean));
}

function parseButtonList(value) {
  return (value ?? "")
    .split(/[,+|]/)
    .map((button) => button.trim())
    .filter(Boolean);
}

function makePadInjectionConfig() {
  const buttons = parseButtonList(injectPadButtonsRaw);
  if (buttons.length === 0 && injectPadFrames <= 0) return null;
  if (buttons.length === 0) throw new Error("--inject-pad-buttons is required when --inject-pad-frames is set");
  const unknown = buttons.filter((button) => PAD_BUTTON_BITS[button] == null);
  if (unknown.length > 0) {
    throw new Error(`unknown --inject-pad-buttons value(s): ${unknown.join(", ")}`);
  }
  if (!Number.isInteger(injectPadFrames) || injectPadFrames <= 0) {
    throw new Error("--inject-pad-frames must be a positive integer when --inject-pad-buttons is set");
  }
  if (!Number.isInteger(injectPadPort) || injectPadPort < 0 || injectPadPort > 3) {
    throw new Error("--inject-pad-port must be 0, 1, 2, or 3");
  }
  const buttonMask = buttons.reduce((mask, button) => mask | PAD_BUTTON_BITS[button], 0);
  return {
    enabled: true,
    buttons,
    buttonMask,
    buttonMaskHex: `0x${buttonMask.toString(16).padStart(4, "0")}`,
    framesRequested: injectPadFrames,
    framesRemaining: injectPadFrames,
    port: injectPadPort,
    lastPadPtr: null,
    strategy:
      "remember PADRead r3 PADStatus[4] pointer, then overwrite one PADStatus.button field and clear PADStatus.err at 0x8010d4d0 after PADRead returns and before game-side normalization consumes it",
  };
}

function packet(payload) {
  let checksum = 0;
  for (const ch of payload) checksum = (checksum + ch.charCodeAt(0)) & 0xff;
  return `$${payload}#${checksum.toString(16).padStart(2, "0")}`;
}

function hex32(value) {
  return `0x${(value >>> 0).toString(16).padStart(8, "0")}`;
}

function parseHex32(raw) {
  if (!/^[0-9a-fA-F]{8}$/.test(raw ?? "")) return null;
  return Number.parseInt(raw, 16) >>> 0;
}

function isMem1(value) {
  return Number.isInteger(value) && value >= 0x80000000 && value < 0x81800000;
}

function parseStopPc(payload) {
  const match = payload.match(/(?:^T[0-9a-fA-F]{2}|;)40:([0-9a-fA-F]{8});/);
  return match ? parseHex32(match[1]) : null;
}

function parseWatchAddress(payload) {
  const match = payload.match(/(?:^|;)(?:watch|rwatch|awatch):([0-9a-fA-F]+);/);
  return match ? Number.parseInt(match[1], 16) >>> 0 : null;
}

function loadBreakpoints() {
  const plan = JSON.parse(fs.readFileSync(planPath, "utf8"));
  const byAddress = new Map();
  for (const group of plan.groups) {
    if (groupsFilter.size && !groupsFilter.has(group.name)) continue;
    for (const bp of group.breakpoints ?? []) {
      if (bp.type !== "execute") continue;
      if (skipIds.has(bp.id)) continue;
      if (onlyIds.size && !onlyIds.has(bp.id)) continue;
      const address = Number.parseInt(bp.address, 16) >>> 0;
      const existing = byAddress.get(address) ?? {
        address,
        ids: [],
        groups: [],
        symbols: [],
        events: [],
      };
      existing.ids.push(bp.id);
      existing.groups.push(group.name);
      existing.symbols.push(bp.symbol);
      existing.events.push(bp.event);
      byAddress.set(address, existing);
    }
  }
  return [...byAddress.values()].sort((a, b) => a.address - b.address);
}

function loadStaticWatchpoints() {
  const plan = JSON.parse(fs.readFileSync(planPath, "utf8"));
  const byKey = new Map();
  for (const group of plan.groups) {
    if (groupsFilter.size && !groupsFilter.has(group.name)) continue;
    for (const wp of group.breakpoints ?? []) {
      if (wp.type === "execute") continue;
      if (skipIds.has(wp.id)) continue;
      if (onlyIds.size && !onlyIds.has(wp.id)) continue;
      if (typeof wp.address !== "string" || !wp.address.startsWith("0x")) continue;
      const address = Number.parseInt(wp.address, 16) >>> 0;
      const size = Number.isInteger(wp.size) ? wp.size : 4;
      const key = `${wp.type}:${address.toString(16)}:${size}`;
      const existing = byKey.get(key) ?? {
        id: wp.id,
        type: wp.type,
        address,
        size,
        sourceAddress: wp.address,
        ids: [],
        groups: [],
        symbols: [],
        events: [],
      };
      existing.ids.push(wp.id);
      existing.groups.push(group.name);
      existing.symbols.push(wp.symbol);
      existing.events.push(wp.event);
      byKey.set(key, existing);
    }
  }
  return [...byKey.values()].sort((a, b) => a.address - b.address);
}

function loadRuntimeWatchpoints() {
  const plan = JSON.parse(fs.readFileSync(planPath, "utf8"));
  const templates = (plan.runtime_field_watchpoints ?? [])
    .filter((wp) => typeof wp.address === "string" && wp.address.startsWith("runtime:active_borg_base+"))
    .filter((wp) => !onlyIds.size || onlyIds.has(wp.id))
    .map((wp) => {
      const offset = Number.parseInt(wp.address.slice("runtime:active_borg_base+".length), 16);
      return {
        id: wp.id,
        type: wp.type,
        offset,
        size: wp.size,
        sourceAddress: wp.address,
      };
    })
    .filter((wp) => Number.isInteger(wp.offset) && Number.isInteger(wp.size))
    .slice(0, 8);
  if (templates.length > 0 || !onlyIds.size) return templates;
  return (plan.runtime_field_watchpoints ?? [])
    .filter((wp) => typeof wp.address === "string" && wp.address.startsWith("runtime:active_borg_base+"))
    .map((wp) => {
      const offset = Number.parseInt(wp.address.slice("runtime:active_borg_base+".length), 16);
      return {
        id: wp.id,
        type: wp.type,
        offset,
        size: wp.size,
        sourceAddress: wp.address,
      };
    })
    .filter((wp) => Number.isInteger(wp.offset) && Number.isInteger(wp.size))
    .slice(0, 8);
}

async function installStaticWatchpoints(gdb, trace, staticWatchpoints, installed) {
  for (const template of staticWatchpoints) {
    const command = watchpointCommand(template.type, template.address, template.size);
    const response = await gdb.send(command, commandTimeoutMs);
    if (response.startsWith("E")) {
      trace.errors.push({ where: "installStaticWatchpoint", id: template.id, address: hex32(template.address), response });
      continue;
    }
    const initial = await readMem(gdb, template.address, template.size);
    const record = {
      ...template,
      address: hex32(template.address),
      command,
      response,
      initial,
      last: initial,
    };
    installed.set(template.address, record);
    trace.installedStaticWatchpoints.push({
      id: record.id,
      ids: record.ids,
      groups: record.groups,
      sourceAddress: record.sourceAddress,
      address: record.address,
      size: record.size,
      type: record.type,
      command: record.command,
      response: record.response,
      initial: record.initial,
    });
  }
}

class GdbRemote {
  constructor() {
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
      this.socket.connect(port, host);
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
}

async function connectWithRetry(gdb, ms) {
  const deadline = Date.now() + ms;
  let lastError = null;
  while (Date.now() < deadline) {
    try {
      await gdb.connect();
      return;
    } catch (error) {
      lastError = error;
      await new Promise((resolve) => setTimeout(resolve, 500));
    }
  }
  throw lastError ?? new Error(`failed to connect to ${host}:${port}`);
}

async function readRegs(gdb) {
  const regs = {};
  const ids = [...Array.from({ length: 32 }, (_, i) => i), 64, 66, 67, 68, 69];
  for (const id of ids) {
    const raw = await gdb.send(`p${id.toString(16)}`, 3000);
    const name =
      id < 32 ? `r${id}` : id === 64 ? "pc" : id === 66 ? "cr" : id === 67 ? "lr" : id === 68 ? "ctr" : "xer";
    regs[name] = { raw, value: parseHex32(raw) };
  }
  return regs;
}

async function readMem(gdb, address, bytes) {
  const raw = await gdb.send(`m${address.toString(16)},${bytes.toString(16)}`, 3000);
  return raw.startsWith("E") ? { error: raw } : { raw };
}

async function writeMem(gdb, address, bytes) {
  const rawBytes = Buffer.isBuffer(bytes) ? bytes : Buffer.from(bytes);
  const raw = await gdb.send(`M${address.toString(16)},${rawBytes.length.toString(16)}:${rawBytes.toString("hex")}`, 3000);
  return raw.startsWith("E") ? { error: raw } : { raw };
}

async function maybeInjectPad(gdb, trace, injection, reason, hitIndex) {
  if (!injection?.enabled || injection.framesRemaining <= 0 || !isMem1(injection.lastPadPtr)) return;
  const address = (injection.lastPadPtr + injection.port * PAD_STATUS_SIZE) >>> 0;
  if (!isMem1(address) || !isMem1(address + PAD_STATUS_SIZE - 1)) return;
  const before = await readMem(gdb, address, PAD_STATUS_SIZE);
  const bytes = Buffer.alloc(PAD_STATUS_SIZE);
  if (typeof before.raw === "string" && before.raw.length >= PAD_STATUS_SIZE * 2 && !/[^0-9a-fA-F]/.test(before.raw)) {
    Buffer.from(before.raw.slice(0, PAD_STATUS_SIZE * 2), "hex").copy(bytes);
  }
  bytes.writeUInt16BE(injection.buttonMask, 0);
  bytes.writeInt8(0, 10);
  const write = await writeMem(gdb, address, bytes);
  const after = await readMem(gdb, address, PAD_STATUS_SIZE).catch((error) => ({ error: error.message }));
  const record = {
    hitIndex,
    reason,
    port: injection.port,
    address: hex32(address),
    buttons: injection.buttons,
    buttonMask: injection.buttonMaskHex,
    before,
    write,
    after,
    framesRemainingBefore: injection.framesRemaining,
  };
  if (write.error) {
    trace.errors.push({ where: "padInjection", ...record });
  } else {
    injection.framesRemaining -= 1;
    record.framesRemainingAfter = injection.framesRemaining;
  }
  trace.padInjectionWrites.push(record);
}

async function installDerivedWatchpoints(gdb, trace, templates, activeBase, installed, installedDerived) {
  if (!isMem1(activeBase) || installedDerived.size > 0) return;
  for (const template of templates) {
    const address = (activeBase + template.offset) >>> 0;
    if (installed.has(address)) continue;
    const command = watchpointCommand(template.type, address, template.size);
    const response = await gdb.send(command, commandTimeoutMs);
    if (response.startsWith("E")) {
      trace.errors.push({ where: "installWatchpoint", id: template.id, address: hex32(address), response });
      continue;
    }
    const initial = await readMem(gdb, address, template.size);
    const record = {
      ...template,
      activeBase: hex32(activeBase),
      address: hex32(address),
      command,
      response,
      initial,
      last: initial,
    };
    installed.set(address, record);
    installedDerived.set(address, record);
    trace.derivedWatchpoints.push({
      id: record.id,
      sourceAddress: record.sourceAddress,
      activeBase: record.activeBase,
      address: record.address,
      size: record.size,
      type: record.type,
      command: record.command,
      response: record.response,
      initial: record.initial,
    });
  }
}

function watchpointCommand(type, address, size) {
  const kind = type === "write" ? "Z2" : type === "read" ? "Z3" : "Z4";
  return `${kind},${address.toString(16)},${size.toString(16)}`;
}

async function removeWatchpoints(gdb, trace, installed) {
  for (const record of installed.values()) {
    try {
      const response = await gdb.send(watchpointCommand(record.type, Number.parseInt(record.address, 16), record.size).replace(/^Z/, "z"), 1000);
      trace.setup.push({ address: record.address, watchpoint: record.id, removeResponse: response });
    } catch (error) {
      trace.errors.push({ where: "removeWatchpoint", id: record.id, address: record.address, message: error.message });
    }
  }
}

async function snapshotWatchpoint(gdb, record) {
  const current = await readMem(gdb, Number.parseInt(record.address, 16), record.size);
  const previous = record.last;
  record.last = current;
  return {
    id: record.id,
    type: record.type,
    address: record.address,
    sourceAddress: record.sourceAddress,
    size: record.size,
    previous,
    current,
    ids: record.ids,
    groups: record.groups,
    symbols: record.symbols,
    events: record.events,
  };
}

function summarizeHit(hit) {
  return {
    pc: hit.pc,
    lr: hit.lr,
    group: hit.breakpoint?.groups?.[0] ?? hit.watchpoint?.groups?.[0] ?? null,
    id: hit.breakpoint?.ids?.[0] ?? hit.watchpoint?.ids?.[0] ?? hit.watchpoint?.id ?? null,
    symbol: hit.breakpoint?.symbols?.[0] ?? hit.watchpoint?.symbols?.[0] ?? null,
    watchpoint: hit.watchpoint
      ? {
          type: hit.watchpoint.type,
          address: hit.watchpoint.address,
          previous: hit.watchpoint.previous,
          current: hit.watchpoint.current,
        }
      : null,
  };
}

function activeBorgBaseFromHit(breakpoint, regs) {
  const ids = new Set(breakpoint?.ids ?? []);
  if (
    ids.has("borg-state-dispatch") ||
    ids.has("state-transition-primitive") ||
    ids.has("active-action-handler-invuln") ||
    ids.has("action-helper-cluster") ||
    ids.has("actor-update-spawn-entry") ||
    ids.has("actor-update-no-input-54c78") ||
    ids.has("player-input-update-simple") ||
    ids.has("player-input-update-with-69960") ||
    ids.has("actor-update-transition-entry") ||
    ids.has("actor-common-update") ||
    ids.has("player-input-bridge") ||
    ids.has("post-input-actor-command-update") ||
    ids.has("z-command-state-candidate") ||
    ids.has("x-table-dispatch-803188e8") ||
    ids.has("x-pressed-action-transition-candidate") ||
    ids.has("bx-pressed-borg-action-candidate") ||
    ids.has("bx-table-dispatch-803448b0") ||
    ids.has("bx-borg-conditional-action-061e") ||
    ids.has("audio-sfx-request-wrapper") ||
    ids.has("param-tier-reset") ||
    ids.has("param-tier-delta-127") ||
    ids.has("param-tier-delta-63") ||
    ids.has("param-tier-refresh")
  ) {
    return regs.r3?.value ?? null;
  }
  if (ids.has("wakeup-invulnerability-init") || ids.has("secondary-wakeup-timer-init")) {
    return regs.r3?.value ?? null;
  }
  if (ids.has("wakeup-timer-countdown")) {
    return regs.r31?.value ?? null;
  }
  return null;
}

async function main() {
  fs.mkdirSync(outDir, { recursive: true });

  const breakpoints = loadBreakpoints();
  const staticWatchpoints = loadStaticWatchpoints();
  if (!breakpoints.length && !staticWatchpoints.length) {
    throw new Error("No execute breakpoints or static watchpoints selected.");
  }
  const runtimeWatchpointTemplates = loadRuntimeWatchpoints();
  const padInjection = makePadInjectionConfig();
  if (dryRun) {
    console.log(JSON.stringify({
      planPath,
      filters: {
        groups: [...groupsFilter],
        onlyIds: [...onlyIds],
        skipIds: [...skipIds],
      },
      padInjection: padInjection
        ? {
            buttons: padInjection.buttons,
            buttonMask: padInjection.buttonMaskHex,
            framesRequested: padInjection.framesRequested,
            port: padInjection.port,
            strategy: padInjection.strategy,
          }
        : null,
      breakpoints,
      staticWatchpoints: staticWatchpoints.map((wp) => ({
        ...wp,
        address: hex32(wp.address),
      })),
      runtimeWatchpointTemplates,
    }, null, 2));
    return;
  }

  const byAddress = new Map(breakpoints.map((bp) => [bp.address, bp]));
  const gdb = new GdbRemote();
  const installedWatchpoints = new Map();
  const installedDerivedWatchpoints = new Map();
  const startedAt = new Date();
  const trace = {
    schema: "gotyaforce.dolphinGdbTrace.v1",
    startedAt: startedAt.toISOString(),
    host,
    port,
    planPath,
    filters: {
      groups: [...groupsFilter],
      onlyIds: [...onlyIds],
      skipIds: [...skipIds],
      maxHits,
      timeoutMs,
    },
    padInjection: padInjection
      ? {
          buttons: padInjection.buttons,
          buttonMask: padInjection.buttonMaskHex,
          framesRequested: padInjection.framesRequested,
          port: padInjection.port,
          strategy: padInjection.strategy,
        }
      : null,
    padInjectionWrites: [],
    breakpoints,
    staticWatchpoints,
    runtimeWatchpointTemplates,
    installedStaticWatchpoints: [],
    derivedWatchpoints: [],
    setup: [],
    initialStop: null,
    controlStops: [],
    hits: [],
    errors: [],
  };

  await connectWithRetry(gdb, 20000);

  try {
    try {
      gdb.interrupt();
      trace.initialStop = await gdb.waitPacket(commandTimeoutMs);
    } catch {
      trace.initialStop = await gdb.send("?", commandTimeoutMs);
    }

    for (const bp of breakpoints) {
      const response = await gdb.send(`Z0,${bp.address.toString(16)},4`, commandTimeoutMs);
      trace.setup.push({ address: hex32(bp.address), response });
    }
    await installStaticWatchpoints(gdb, trace, staticWatchpoints, installedWatchpoints);

    const deadline = Date.now() + timeoutMs;
    while (trace.hits.length < maxHits && Date.now() < deadline) {
      let stop;
      try {
        stop = await gdb.send("c", Math.max(1000, deadline - Date.now()));
      } catch (error) {
        trace.errors.push({ where: "continue", message: error.message });
        try {
          gdb.interrupt();
          trace.errors.push({ where: "continueInterrupt", stop: await gdb.waitPacket(commandTimeoutMs) });
        } catch (interruptError) {
          trace.errors.push({ where: "continueInterrupt", message: interruptError.message });
        }
        break;
      }

      const regs = await readRegs(gdb);
      const pc = regs.pc.value ?? parseStopPc(stop);
      const breakpoint = byAddress.get(pc) ?? byAddress.get((pc - 4) >>> 0) ?? null;
      const watchAddress = parseWatchAddress(stop);
      const watched = watchAddress == null ? null : installedWatchpoints.get(watchAddress) ?? null;
      const watchpoint = watched ? await snapshotWatchpoint(gdb, watched) : null;
      const breakpointIds = new Set(breakpoint?.ids ?? []);
      if (!breakpoint && !watchpoint) {
        trace.controlStops.push({
          at: new Date().toISOString(),
          stop,
          pc: pc == null ? null : hex32(pc),
          lr: regs.lr.value == null ? null : hex32(regs.lr.value),
        });
        continue;
      }
      if (breakpointIds.has("pad-read")) {
        padInjection && (padInjection.lastPadPtr = regs.r3?.value ?? null);
      }
      if (breakpointIds.has("pad-post-read-normalization")) {
        await maybeInjectPad(gdb, trace, padInjection, "after-pad-read-before-game-normalization", trace.hits.length);
      }
      const pointers = {};
      for (const name of ["r1", "r3", "r4", "r5", "r6", "r31"]) {
        const value = regs[name]?.value;
        if (!isMem1(value)) continue;
        pointers[name] = {
          address: hex32(value),
          bytes: await readMem(gdb, value, name === "r1" ? 0x80 : 0x40),
        };
      }
      const fixedMemory = {};
      if (breakpointIds.has("pad-post-read-normalization") || breakpointIds.has("pad-normalization-complete")) {
        fixedMemory.padStatus = {
          address: "0x803c72fc",
          bytes: await readMem(gdb, 0x803c72fc, 0x30),
        };
        fixedMemory.normalizedPad = {
          address: "0x803c727c",
          bytes: await readMem(gdb, 0x803c727c, 0x80),
        };
      }

      const activeBase = activeBorgBaseFromHit(breakpoint, regs);
      if (isMem1(activeBase)) {
        try {
          await installDerivedWatchpoints(gdb, trace, runtimeWatchpointTemplates, activeBase, installedWatchpoints, installedDerivedWatchpoints);
        } catch (error) {
          trace.errors.push({ where: "installDerivedWatchpoints", activeBase: hex32(activeBase), message: error.message });
        }
      }

      // Wide struct dump for HP-hunting: known accesses on the active-borg struct span at
      // least 0x000-0x8c4 (borg-struct-offsets.txt) with a second cluster out to ~0x1dd4, so
      // the 0x40-byte per-register snapshots above are too narrow to ever contain the HP
      // field. When this hit resolves an active_borg_base, also grab a single large
      // contiguous dump of the whole struct so two hits (e.g. pre-hit vs. post-hit, or two
      // successive knockdowns) can be diffed offset-by-offset to spot which field dropped by
      // a plausible damage amount.
      let activeBaseStruct = null;
      if (isMem1(activeBase)) {
        activeBaseStruct = { base: hex32(activeBase), size: 0x1e00, bytes: await readMem(gdb, activeBase, 0x1e00) };
      }

      trace.hits.push({
        index: trace.hits.length,
        at: new Date().toISOString(),
        stop,
        pc: pc == null ? null : hex32(pc),
        lr: regs.lr.value == null ? null : hex32(regs.lr.value),
        ctr: regs.ctr.value == null ? null : hex32(regs.ctr.value),
        breakpoint,
        watchpoint,
        regs,
        pointers,
        fixedMemory,
        activeBaseStruct,
      });
    }

    await removeWatchpoints(gdb, trace, installedWatchpoints);

    for (const bp of breakpoints) {
      try {
        await gdb.send(`z0,${bp.address.toString(16)},4`, 1000);
      } catch (error) {
        trace.errors.push({ where: "removeBreakpoint", address: hex32(bp.address), message: error.message });
      }
    }
  } finally {
    trace.finishedAt = new Date().toISOString();
    if (trace.padInjection && padInjection) trace.padInjection.framesRemaining = padInjection.framesRemaining;
    const safeTime = startedAt.toISOString().replace(/[:.]/g, "-");
    const outPath = path.join(outDir, `gdb-trace-${safeTime}.json`);
    fs.writeFileSync(outPath, `${JSON.stringify(trace, null, 2)}\n`);
    console.log(JSON.stringify({
      outPath,
      hits: trace.hits.length,
      firstHits: trace.hits.slice(0, 10).map(summarizeHit),
      controlStops: trace.controlStops.length,
      errors: trace.errors,
    }, null, 2));
    gdb.close();
  }
}

main().catch((error) => {
  console.error(error.stack || error.message);
  process.exitCode = 1;
});
