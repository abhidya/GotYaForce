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
const groupsFilter = csvSet(argsByName.get("groups") ?? process.env.TRACE_GROUPS);
const skipIds = csvSet(argsByName.get("skip-ids") ?? process.env.TRACE_SKIP_IDS);
const onlyIds = csvSet(argsByName.get("only-ids") ?? process.env.TRACE_ONLY_IDS);
const dryRun = argsByName.has("dry-run") || process.env.TRACE_DRY_RUN === "1";

function parseArgs(argv) {
  const parsed = new Map();
  for (let i = 0; i < argv.length; i += 1) {
    const arg = argv[i];
    if (!arg.startsWith("--")) continue;
    const eq = arg.indexOf("=");
    if (eq >= 0) parsed.set(arg.slice(2, eq), arg.slice(eq + 1));
    else parsed.set(arg.slice(2), argv[++i] ?? "");
  }
  return parsed;
}

function csvSet(value) {
  return new Set((value ?? "").split(",").map((v) => v.trim()).filter(Boolean));
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
    .slice(0, 6);
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
  if (dryRun) {
    console.log(JSON.stringify({
      planPath,
      filters: {
        groups: [...groupsFilter],
        onlyIds: [...onlyIds],
        skipIds: [...skipIds],
      },
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
      if (!breakpoint && !watchpoint) {
        trace.controlStops.push({
          at: new Date().toISOString(),
          stop,
          pc: pc == null ? null : hex32(pc),
          lr: regs.lr.value == null ? null : hex32(regs.lr.value),
        });
        continue;
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
