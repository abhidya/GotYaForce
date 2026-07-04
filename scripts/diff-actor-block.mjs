#!/usr/bin/env node
// diff-actor-block.mjs — locate the Power Burst meter field (trace plan T3 "WATCH SWEEP").
//
// Dumps the active borg's actor block over Dolphin's GDB stub, twice per run (a settle
// interval of frames apart) so the diff can discard fields that churn on their own
// (timers, RNG, positions). An offset is a *candidate* only when it is stable within each
// dump but differs between the two dumps. Both snapshots are taken while halted at the
// per-frame tick breakpoint — never right after a bare interrupt (short/garbage reads).
//
// Workflow (Dolphin running with --config=Dolphin.General.GDBPort=5555):
//   1. Load the "meter empty" save state (e.g. nexthitChargesMeter.sav), then:
//        node scripts/diff-actor-block.mjs --dump user-data/dolphin-trace/meter-empty.json --label "meter empty"
//   2. In Dolphin: Emulation -> Load State from File -> "meter charged.sav", then:
//        node scripts/diff-actor-block.mjs --dump user-data/dolphin-trace/meter-full.json --label "meter full"
//   3. Diff:
//        node scripts/diff-actor-block.mjs --diff user-data/dolphin-trace/meter-empty.json user-data/dolphin-trace/meter-full.json
//
// Defaults dump actor-relative 0x0..0x2000 (covers every field the T presets reference,
// up to +0x1dd4). Override with --start/--length (hex ok), or --base to skip resolution.

import fs from "node:fs";
import path from "node:path";
import { GdbRemote, isMem1 } from "./lib/gdb-remote.mjs";

const CHUNK = 0x200; // bytes per GDB m-packet; conservative for Dolphin's stub buffer
// Proven game-side per-frame tick (same as trace-attack-mechanics.mjs). The borg base is
// only resolved while halted AT this tick — reads issued right after a bare interrupt can
// return short/garbage buffers.
const TICK_ADDR = 0x8010d450;

// ── Borg base resolution — same chain as trace-attack-mechanics.mjs (behavior-notes.md §z) ──
const SLOT_TABLE_PTR = 0x80433934;
const ACTOR_ARRAY = 0x803c4e84;

/** readMem that also rejects short replies (stub can return fewer bytes than asked). */
async function readMemExact(gdb, address, bytes) {
  const buf = await gdb.readMem(address >>> 0, bytes);
  return buf && buf.length === bytes ? buf : null;
}

async function validateBorgBase(gdb, base, slot) {
  if (!isMem1(base)) return false;
  const slotBuf = await readMemExact(gdb, (base + 0x3e4) >>> 0, 1);
  const stateBuf = await readMemExact(gdb, (base + 0x544) >>> 0, 4);
  if (!slotBuf || !stateBuf) return false;
  const slotField = slotBuf.readInt8(0);
  const state = stateBuf.readInt32BE(0);
  return slotField === slot && state >= -1 && state <= 64;
}

async function resolveBorgBase(gdb, baseOverride) {
  if (baseOverride !== null) return { base: baseOverride, via: "cli-override" };
  const tBuf = await readMemExact(gdb, SLOT_TABLE_PTR, 4);
  const t = tBuf ? tBuf.readUInt32BE(0) : 0;
  if (isMem1(t)) {
    const slotBuf = await readMemExact(gdb, (t + 0xc0) >>> 0, 1);
    const rawSlot = slotBuf ? slotBuf.readInt8(0) : 0;
    const slot = rawSlot >= 0 && rawSlot <= 5 ? rawSlot : 0;
    const baseBuf = await readMemExact(gdb, (ACTOR_ARRAY + slot * 4) >>> 0, 4);
    const base = baseBuf ? baseBuf.readUInt32BE(0) : 0;
    if (await validateBorgBase(gdb, base, slot)) return { base, via: `slot-table(slot=${slot})` };
  }
  const fastBuf = await readMemExact(gdb, ACTOR_ARRAY, 4);
  const fastBase = fastBuf ? fastBuf.readUInt32BE(0) : 0;
  if (await validateBorgBase(gdb, fastBase, 0)) return { base: fastBase, via: "fast-path-slot0" };
  throw new Error("could not resolve active borg base (no battle in progress?)");
}

async function connectWithRetry(gdb, attempts = 24, delayMs = 5000) {
  for (let i = 1; ; i += 1) {
    try {
      await gdb.connect();
      return;
    } catch (error) {
      if (i >= attempts) throw error;
      if (i === 1) console.log(`GDB stub not up yet (${error.code ?? error.message}); retrying every ${delayMs / 1000}s`);
      await new Promise((r) => setTimeout(r, delayMs));
    }
  }
}

/** Continue until we are halted at the frame tick AND `resolve()` yields a base. */
async function waitForTickWithBase(gdb, resolve, maxAttempts = 600) {
  for (let i = 0; i < maxAttempts; i += 1) {
    const stop = await gdb.continueAndWaitStop(30000);
    if (stop.pc !== TICK_ADDR) continue;
    try {
      return await resolve();
    } catch {
      if (i === 0) console.log("tick hit, but no valid base yet; waiting");
    }
  }
  throw new Error("no tick with a valid base (is a battle in progress?)");
}

/** Base resolver for --base-ptr: dereference a MEM1 pointer (e.g. PTR_DAT_80433934). */
async function derefBase(gdb, ptrAddr) {
  const buf = await readMemExact(gdb, ptrAddr, 4);
  const base = buf ? buf.readUInt32BE(0) : 0;
  if (!isMem1(base)) throw new Error(`*${hex(ptrAddr)} is not a MEM1 pointer (${hex(base)})`);
  return { base, via: `deref(${hex(ptrAddr)})` };
}

function parseNum(raw, label) {
  const value = Number.parseInt(raw, raw?.toLowerCase?.().startsWith("0x") ? 16 : 10);
  if (!Number.isInteger(value)) throw new Error(`${label} must be a number (hex ok)`);
  return value >>> 0;
}

function hex(value, pad = 0) {
  return `0x${(value >>> 0).toString(16).padStart(pad, "0")}`;
}

async function readBlock(gdb, address, length) {
  const parts = [];
  for (let done = 0; done < length; ) {
    const want = Math.min(CHUNK, length - done);
    const buf = await readMemExact(gdb, (address + done) >>> 0, want);
    if (!buf) {
      throw new Error(`memory read failed at ${hex(address + done)} (${want} bytes)`);
    }
    parts.push(buf);
    done += want;
  }
  return Buffer.concat(parts);
}

async function runDump(argv) {
  const outPath = argv.get("dump");
  const label = argv.get("label") ?? "";
  const host = argv.get("host") ?? "127.0.0.1";
  const port = Number.parseInt(argv.get("port") ?? "5555", 10);
  const start = argv.has("start") ? parseNum(argv.get("start"), "--start") : 0x0;
  const length = argv.has("length") ? parseNum(argv.get("length"), "--length") : 0x2000;
  const settleFrames = argv.has("settle-frames") ? parseNum(argv.get("settle-frames"), "--settle-frames") : 120;
  const baseOverride = argv.has("base") ? parseNum(argv.get("base"), "--base") : null;
  const basePtr = argv.has("base-ptr") ? parseNum(argv.get("base-ptr"), "--base-ptr") : null;

  const gdb = new GdbRemote(host, port);
  await connectWithRetry(gdb);
  console.log(`connected to Dolphin GDB stub at ${host}:${port}`);
  gdb.interrupt();
  await gdb.waitPacket(10000).catch(() => {});

  const kind = await gdb.setBreak(TICK_ADDR);
  let cleanedUp = false;
  const cleanup = async () => {
    if (cleanedUp) return;
    cleanedUp = true;
    await gdb.clearBreak(TICK_ADDR, kind).catch(() => {});
    await gdb.send("c", 2000).catch(() => {});
    gdb.close();
  };
  const onSignal = () => {
    cleanup().finally(() => process.exit(130));
  };
  process.once("SIGINT", onSignal);
  process.once("SIGTERM", onSignal);

  try {
    const resolve = basePtr !== null ? () => derefBase(gdb, basePtr) : () => resolveBorgBase(gdb, baseOverride);
    const { base, via } = await waitForTickWithBase(gdb, resolve);
    console.log(`dump base = ${hex(base)} (via ${via})`);

    const snapA = await readBlock(gdb, (base + start) >>> 0, length);
    console.log(
      `snapshot A captured (${length} bytes at base+${hex(start)}); running ${settleFrames} frames - do NOT land any hits`,
    );
    for (let i = 0; i < settleFrames; ) {
      const stop = await gdb.continueAndWaitStop(30000);
      if (stop.pc === TICK_ADDR) i += 1;
    }
    const { base: base2, via: via2 } = await resolve();
    if (base2 !== base) {
      throw new Error(`borg base moved during settle (${hex(base)} -> ${hex(base2)} via ${via2}); re-run`);
    }
    const snapB = await readBlock(gdb, (base + start) >>> 0, length);
    console.log("snapshot B captured");

    fs.mkdirSync(path.dirname(path.resolve(outPath)), { recursive: true });
    fs.writeFileSync(
      outPath,
      JSON.stringify({
        label,
        base: hex(base),
        via,
        start: hex(start),
        length,
        settleFrames,
        recordedAt: new Date().toISOString(),
        snapshots: [snapA.toString("hex"), snapB.toString("hex")],
      }),
    );
    console.log(`wrote ${outPath}`);
  } finally {
    process.removeListener("SIGINT", onSignal);
    process.removeListener("SIGTERM", onSignal);
    await cleanup();
  }
}

function loadDump(filePath) {
  const dump = JSON.parse(fs.readFileSync(filePath, "utf8"));
  return {
    ...dump,
    buffers: dump.snapshots.map((h) => Buffer.from(h, "hex")),
    startNum: Number.parseInt(dump.start, 16),
  };
}

/** Group sorted offsets into runs of consecutive bytes. */
function groupRuns(offsets) {
  const runs = [];
  for (const off of offsets) {
    const last = runs[runs.length - 1];
    if (last && off === last.end) last.end = off + 1;
    else runs.push({ start: off, end: off + 1 });
  }
  return runs;
}

function interpret(buf, off) {
  const parts = [`u8=${buf.readUInt8(off)}`];
  if (off + 2 <= buf.length && off % 2 === 0) parts.push(`u16=${buf.readUInt16BE(off)}`);
  if (off + 4 <= buf.length && off % 4 === 0) {
    parts.push(`u32=${buf.readUInt32BE(off)}`);
    const f = buf.readFloatBE(off);
    if (Number.isFinite(f) && Math.abs(f) < 1e9) parts.push(`f32=${f.toPrecision(6)}`);
  }
  return parts.join(" ");
}

function runDiff(beforePath, afterPath) {
  const before = loadDump(beforePath);
  const after = loadDump(afterPath);
  if (before.startNum !== after.startNum || before.length !== after.length) {
    throw new Error("dumps cover different ranges; re-dump with matching --start/--length");
  }
  const [a1, a2] = before.buffers;
  const [b1, b2] = after.buffers;

  const volatileOffs = new Set();
  const candidates = [];
  for (let i = 0; i < before.length; i += 1) {
    const volA = a1[i] !== a2[i];
    const volB = b1[i] !== b2[i];
    if (volA || volB) {
      volatileOffs.add(i);
      continue;
    }
    if (a1[i] !== b1[i]) candidates.push(i);
  }

  console.log(`# diff: "${before.label || beforePath}" -> "${after.label || afterPath}"`);
  console.log(`bases: ${before.base} (${before.via}) -> ${after.base} (${after.via})`);
  console.log(`range: base+${before.start}..base+${hex(before.startNum + before.length)}`);
  console.log(`volatile bytes excluded (changed within a single state): ${volatileOffs.size}`);
  console.log(`stable candidate bytes (differ between states): ${candidates.length}`);
  console.log("");

  const runs = groupRuns(candidates);
  console.log("offset(actor-rel)\tbytes\tbefore -> after");
  for (const run of runs) {
    const off = run.start;
    const len = run.end - run.start;
    const rel = before.startNum + off;
    console.log(`+${hex(rel, 4)}\t${len}\t[${a1.subarray(off, run.end).toString("hex")}] -> [${b1.subarray(off, run.end).toString("hex")}]`);
    // Interpret at the run start and at the nearest 4-byte alignment inside the run.
    const aligned = (rel & ~3) - before.startNum;
    const at = aligned >= 0 && aligned >= off - 3 ? aligned : off;
    console.log(`\t\tbefore: ${interpret(a1, at)}`);
    console.log(`\t\tafter:  ${interpret(b1, at)}`);
  }
  if (!runs.length) {
    console.log("(no stable differences — meter field may live outside this range; retry with --start/--length or an absolute region)");
  }
}

function parseArgs(argv) {
  const parsed = new Map();
  const positional = [];
  for (let i = 0; i < argv.length; i += 1) {
    const arg = argv[i];
    if (!arg.startsWith("--")) {
      positional.push(arg);
      continue;
    }
    const eq = arg.indexOf("=");
    if (eq >= 0) {
      parsed.set(arg.slice(2, eq), arg.slice(eq + 1));
    } else {
      const next = argv[i + 1];
      if (next === undefined || next.startsWith("--")) parsed.set(arg.slice(2), "1");
      else parsed.set(arg.slice(2), argv[++i]);
    }
  }
  return { flags: parsed, positional };
}

const { flags, positional } = parseArgs(process.argv.slice(2));
try {
  if (flags.has("dump")) {
    await runDump(flags);
  } else if (flags.has("diff")) {
    const beforePath = flags.get("diff") === "1" ? positional[0] : flags.get("diff");
    const afterPath = flags.get("diff") === "1" ? positional[1] : positional[0];
    if (!beforePath || !afterPath) throw new Error("--diff needs two dump files: --diff before.json after.json");
    runDiff(beforePath, afterPath);
  } else {
    console.log("usage:");
    console.log('  dump: node scripts/diff-actor-block.mjs --dump out.json [--label "meter empty"] [--start 0x0] [--length 0x2000] [--settle-frames 120] [--base <hex>]');
    console.log("  diff: node scripts/diff-actor-block.mjs --diff before.json after.json");
    process.exitCode = 1;
  }
} catch (error) {
  console.error(`error: ${error.message}`);
  process.exitCode = 1;
}
