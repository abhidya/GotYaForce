#!/usr/bin/env node
// Attack-mechanics trace harness (ATK-016): turns the T1-T10 presets in
// research/decomp/attack-mechanics-trace-plan.md into runnable per-frame Dolphin captures,
// so trace sessions produce machine-diffable JSONL instead of ad-hoc notes/video.
//
// Extends the patterns already proven in scripts/trace-golden-record.mjs (per-frame capture
// keyed on the PADRead breakpoint, JSONL with a meta first line) and
// scripts/dolphin-gdb-trace.mjs (GDB-stub watch/read plumbing, now shared via
// scripts/lib/gdb-remote.mjs). Actor base chain (behavior-notes.md §z/§aa, code-confirmed):
//
//   T    = *(u32*) 0x80433934                 # battle/slot table ptr
//   slot = *(s8*)  (T + 0xC0)                 # player 0's active-borg slot
//   base = *(u32*) (0x803C4E84 + slot*4)      # player 0 active borg struct pointer
//   (single-player fast path: base = *(u32*) 0x803C4E84)
//
// All watch offsets below are BASE-RELATIVE unless a preset field sets `absolute: true`
// (those are fixed DAT_* addresses from the trace plan, e.g. object-list counts).
//
// ── KNOWN LIMITATION: T1 command-struct pointer chase (+0x4b0) ─────────────────────────
// The trace plan asks T1 to log the 8 bytes at *(u32*)(actor+0x4b0) — i.e. dereference a
// pointer that lives IN the actor struct and read a few bytes at ITS target, every frame.
// The Dolphin GDB stub used here has no server-side "read memory at [ptr+off]" op; every
// read is a plain `m<addr>,<len>` against an address WE compute client-side between stub
// round-trips. That is fine for a single frame (read the pointer, then read its target) but
// costs an extra round-trip per frame and — because the two reads are not atomic — the
// struct can theoretically be reallocated/rewritten between them under heavy alloc churn.
// The fallback the ticket allows: this harness ALWAYS logs the raw pointer value at +0x4b0
// (field `cmdStructPtr`) plus a best-effort chased read of `cmdStructPtr+0..7` (field
// `cmdStructBytes`, null if the pointer wasn't in MEM1 that frame). If `cmdStructBytes` ever
// looks torn/inconsistent frame-to-frame, treat `cmdStructPtr` as ground truth and
// re-derive the struct contents by post-processing a raw-pointer-only capture instead.
//
// ── Usage ────────────────────────────────────────────────────────────────────────────
//   node scripts/trace-attack-mechanics.mjs --preset T1 --dry-run
//       Print the resolved watch list for a preset (no Dolphin, no file I/O). Sanity check
//       before a real session.
//
//   node scripts/trace-attack-mechanics.mjs --preset T1 --frames 1800 \
//       --scenario "B point-blank" --borg pl0615 --note "repeat 3/3 script (d)"
//       Real capture: connects to the GDB stub (see scripts/launch-dolphin-gdb.mjs), resolves
//       the active-borg base, and records one JSONL row per PADRead tick to
//       user-data/dolphin-trace/attack-mechanics/T<n>-<slug>.jsonl.
//
//   node scripts/trace-attack-mechanics.mjs --summarize <file.jsonl>
//       Print per-field change points (frame, old, new) for a captured (or fixture) JSONL —
//       no Dolphin needed. Works on both real captures and the --dry-run fixture below.
//
//   node scripts/trace-attack-mechanics.mjs --preset T1 --dry-run --summarize
//       Exercises --summarize against the canned fixture at
//       scripts/fixtures/attack-mechanics-t1-sample.jsonl WITHOUT Dolphin. This is the
//       ticket's required test: no live game, no GDB stub, deterministic output.
//
// Options: --preset T1..T10 (required unless --summarize <file> is given directly),
//          --frames N (default 1800), --host/--port (default 127.0.0.1:5555),
//          --tick-addr 0xADDR (default 0x8010d450, proven game-side per-frame input tick),
//          --borg plXXXX, --scenario "text", --note "text", --out <file> (override output
//          path), --base 0x… (skip base resolution).

import fs from "node:fs";
import path from "node:path";
import { fileURLToPath } from "node:url";
import { GdbRemote, isMem1 } from "./lib/gdb-remote.mjs";

const repoRoot = path.resolve(path.dirname(fileURLToPath(import.meta.url)), "..");
const FIXTURE_PATH = path.join(repoRoot, "scripts", "fixtures", "attack-mechanics-t1-sample.jsonl");

// ── Preset definitions (from research/decomp/attack-mechanics-trace-plan.md "Memory to
// log" sections). `fields` entries: { name, off, type, size?, absolute? }. `type` drives
// the Buffer read used against the GDB-stub memory dump. Offsets are actor-relative unless
// `absolute: true`, in which case `off` is a full 32-bit address (DAT_* statics).
const PRESETS = {
  T1: {
    slug: "command-byte-mapping",
    title: "Command-byte mapping (B/X contextual attack resolution)",
    fields: [
      { name: "cmd", off: 0x591, type: "u8" },
      { name: "stateSlotA", off: 0x6fe, type: "s32" },
      { name: "stateSlotB", off: 0x540, type: "s32" },
      { name: "buttonByteA", off: 0x660, type: "u8" },
      { name: "buttonByteB", off: 0x661, type: "u8" },
      { name: "variantSelector", off: 0x1d0f, type: "u8" },
      { name: "cmdStructPtr", off: 0x4b0, type: "u32" }, // see header limitation note
      { name: "posX", off: 0x20, type: "f32" },
      { name: "posY", off: 0x24, type: "f32" },
      { name: "posZ", off: 0x28, type: "f32" },
      { name: "localPhase", off: 0x544, type: "s32" },
    ],
    // cmdStructBytes is derived per-frame by chasing cmdStructPtr (+0..7); not a static offset.
    chase: { name: "cmdStructBytes", ptrField: "cmdStructPtr", len: 8 },
  },
  T2: {
    slug: "melee-context-variant-table",
    title: "Melee-context variant table (standing/dash/air/landing melee)",
    fields: [
      { name: "cmd", off: 0x591, type: "u8" },
      { name: "variantSelector", off: 0x1d0f, type: "u8" },
      { name: "animFrame", off: 0x1cdc, type: "s32" },
      { name: "mashCounter", off: 0x550, type: "u8" },
      { name: "objListCountA", off: 0x80436250, type: "u16", absolute: true },
      { name: "objListCountB", off: 0x8043624e, type: "u16", absolute: true },
    ],
  },
  T3: {
    slug: "hyper-power-burst-meter",
    title: "Hyper/Power Burst meter + duration",
    // Player-struct fields (meter etc.) are player-0 absolute addresses derived from
    // PTR_DAT_80433934 = *(u32*)0x80433934 = 0x803c5420 (GG4E, static across boots;
    // verified twice via scripts/diff-actor-block.mjs --base-ptr 0x80433934). Per-player
    // stride 0x3c. See attack-mechanics-findings.md §S for the field map.
    fields: [
      { name: "armWindow", off: 0x6fb, type: "u8" },
      { name: "burstActive", off: 0x6fc, type: "u8" },
      { name: "pairedFlag", off: 0x6fa, type: "u8" },
      { name: "transformedButtonWord", off: 0x5d4, type: "u32" },
      { name: "weaponCell774", off: 0x774, type: "u16" },
      { name: "weaponCell778", off: 0x778, type: "u16" },
      { name: "posX", off: 0x20, type: "f32" },
      { name: "posY", off: 0x24, type: "f32" },
      { name: "posZ", off: 0x28, type: "f32" },
      { name: "p0MeterCharged", off: 0x803c5523, type: "u8", absolute: true }, // ps+0x103
      { name: "p0BurstMode", off: 0x803c5524, type: "u8", absolute: true }, // ps+0x104
      { name: "p0BurstTimerA", off: 0x803c552c, type: "u16", absolute: true }, // ps+0x10c
      { name: "p0BurstTimerB", off: 0x803c552e, type: "u16", absolute: true }, // ps+0x10e
      { name: "p0MeterMax", off: 0x803c5544, type: "u16", absolute: true }, // ps+0x124
      { name: "p0MeterValue", off: 0x803c5546, type: "u16", absolute: true }, // ps+0x126
      { name: "p0MeterUnclamped", off: 0x803c554a, type: "u16", absolute: true }, // ps+0x12a
      // Players 1-3 (the 2v2 save has 4 combatants; victim index unconfirmed): +0x3c stride.
      { name: "p1MeterValue", off: 0x803c5582, type: "u16", absolute: true }, // ps+0x3c+0x126
      { name: "p1MeterUnclamped", off: 0x803c5586, type: "u16", absolute: true }, // ps+0x3c+0x12a
      { name: "p2MeterValue", off: 0x803c55be, type: "u16", absolute: true }, // ps+0x78+0x126
      { name: "p3MeterValue", off: 0x803c55fa, type: "u16", absolute: true }, // ps+0xb4+0x126
      // Slot-1 actor HP (actor array stride 0x1e00; base 0x805dbdc0 stable across boots of
      // the owned save states — re-derive via slot table if a trace shows it as garbage).
      { name: "slot1ActorHp", off: 0x805ddd86, type: "s16", absolute: true }, // actor1+0x1c6
    ],
  },
  T4: {
    slug: "state-slot-labels",
    title: "State-slot labels for hit reactions and attacks",
    fields: [
      { name: "stateSlotA", off: 0x6fe, type: "s32" },
      { name: "stateSlotB", off: 0x540, type: "s32" },
      { name: "localPhase", off: 0x544, type: "s32" },
      { name: "invuln", off: 0x720, type: "f32" },
      { name: "window684", off: 0x684, type: "u32" },
      { name: "window688", off: 0x688, type: "u32" },
      { name: "window68c", off: 0x68c, type: "u32" },
      { name: "gauge6c2", off: 0x6c2, type: "u16" },
      { name: "gauge6c6", off: 0x6c6, type: "u16" },
    ],
  },
  T5: {
    slug: "projectile-solidity",
    title: "Projectile solidity / projectile-vs-projectile",
    fields: [
      { name: "objListCount", off: 0x80436250, type: "u16", absolute: true },
      { name: "objStateByte", off: 0x10, type: "u8" },
      { name: "objTypeByte", off: 0x11, type: "u8" },
      { name: "objMode", off: 0x58, type: "u32" },
      { name: "posX", off: 0x20, type: "f32" },
      { name: "posY", off: 0x24, type: "f32" },
      { name: "posZ", off: 0x28, type: "f32" },
    ],
  },
  T6: {
    slug: "penetration-consume-on-hit",
    title: "Penetration / consume-on-hit",
    fields: [
      { name: "victimHp", off: 0x1c6, type: "s16" },
      { name: "objStateByte", off: 0x10, type: "u8" },
      { name: "rehitCounter", off: 0x4e, type: "u16" },
      { name: "obj4a", off: 0x4a, type: "u16" },
      { name: "objListCount", off: 0x80436250, type: "u16", absolute: true },
    ],
  },
  T7: {
    slug: "ammo-refill-constants",
    title: "Ammo refill constants per mode",
    fields: [
      { name: "weaponCell774", off: 0x774, type: "u16" },
      { name: "weaponCell776", off: 0x776, type: "u16" },
      { name: "weaponCell778", off: 0x778, type: "u16" },
      { name: "weaponCell77c", off: 0x77c, type: "u16" },
      { name: "weaponCell784", off: 0x784, type: "u16" },
      { name: "auxCells78c", off: 0x78c, type: "u16" },
      { name: "auxCells79e", off: 0x79e, type: "u16" },
      { name: "refillRateCandidate768", off: 0x768, type: "f32" },
      { name: "burstActive", off: 0x6fc, type: "u8" },
    ],
  },
  T8: {
    slug: "status-effects-id-duration",
    title: "Status effects: id semantics + durations",
    fields: [
      { name: "statusId", off: 0x71a, type: "u16" },
      { name: "statusTimer", off: 0x71c, type: "u16" },
      { name: "shrinkGrow", off: 0x70c, type: "u16" },
      { name: "shrinkGrowB", off: 0x70e, type: "u16" },
      { name: "paramTierA", off: 0x74a, type: "u16" },
      { name: "paramTierB", off: 0x74e, type: "u16" },
      { name: "paramTierC", off: 0x750, type: "u16" },
      { name: "field768", off: 0x768, type: "f32" },
      { name: "modelScaleCandidate", off: 0xc0, type: "f32" },
      { name: "victimHp", off: 0x1c6, type: "s16" },
      { name: "velX", off: 0x58, type: "f32" },
      { name: "velY", off: 0x5c, type: "f32" },
      { name: "velZ", off: 0x60, type: "f32" },
      { name: "word5e0", off: 0x5e0, type: "u32" },
    ],
  },
  T9: {
    slug: "knockback-magnitude-hitstun",
    title: "Knockback magnitude + hitstun consumer",
    fields: [
      { name: "posX", off: 0x44, type: "f32" },
      { name: "posY", off: 0x48, type: "f32" },
      { name: "posZ", off: 0x4c, type: "f32" },
      { name: "velX", off: 0x58, type: "f32" },
      { name: "velY", off: 0x5c, type: "f32" },
      { name: "velZ", off: 0x60, type: "f32" },
      { name: "pitchBam", off: 0x282, type: "s16" },
      { name: "yawBam", off: 0x284, type: "s16" },
      { name: "stateSlot", off: 0x6fe, type: "s32" },
      { name: "localPhase", off: 0x544, type: "s32" },
      { name: "attackerObjType", off: 0x11, type: "u8" },
    ],
  },
  T10: {
    slug: "friendly-fire-burst-passthrough",
    title: "Friendly fire + burst passthrough regression capture",
    fields: [
      { name: "victimHp", off: 0x1c6, type: "s16" },
      { name: "team", off: 0x88, type: "u8" },
      { name: "burstActive", off: 0x6fc, type: "u8" },
    ],
  },
};

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

function readerFor(type) {
  switch (type) {
    case "u8":
      return (buf) => buf.readUInt8(0);
    case "s8":
      return (buf) => buf.readInt8(0);
    case "u16":
      return (buf) => buf.readUInt16BE(0);
    case "s16":
      return (buf) => buf.readInt16BE(0);
    case "u32":
      return (buf) => buf.readUInt32BE(0);
    case "s32":
      return (buf) => buf.readInt32BE(0);
    case "f32":
      return (buf) => buf.readFloatBE(0);
    default:
      throw new Error(`unknown field type: ${type}`);
  }
}

function sizeFor(type) {
  switch (type) {
    case "u8":
    case "s8":
      return 1;
    case "u16":
    case "s16":
      return 2;
    case "u32":
    case "s32":
    case "f32":
      return 4;
    default:
      throw new Error(`unknown field type: ${type}`);
  }
}

function resolvePreset(id) {
  const preset = PRESETS[id];
  if (!preset) {
    throw new Error(`unknown preset "${id}" (expected one of ${Object.keys(PRESETS).join(", ")})`);
  }
  return preset;
}

function hex(value) {
  return value === null || value === undefined ? null : `0x${(value >>> 0).toString(16)}`;
}

/** Build the resolved watch list for a preset: [{name, address|offset, absolute, type, size}] */
function buildWatchList(preset) {
  return preset.fields.map((f) => ({
    name: f.name,
    offset: f.absolute ? null : f.off,
    offsetHex: f.absolute ? null : hex(f.off),
    address: f.absolute ? f.off : null,
    addressHex: f.absolute ? hex(f.off) : null,
    absolute: !!f.absolute,
    type: f.type,
    size: sizeFor(f.type),
  }));
}

// ── --summarize: per-field change points from a JSONL trace (real capture or fixture) ──
function summarizeFile(filePath) {
  const raw = fs.readFileSync(filePath, "utf8");
  const lines = raw.split("\n").filter((l) => l.trim().length > 0);
  if (!lines.length) throw new Error(`${filePath} has no lines`);

  const meta = JSON.parse(lines[0]);
  if (meta.type !== "meta") {
    throw new Error(`${filePath}: first line must be a {"type":"meta",...} record`);
  }

  const changes = []; // { field, frame, old, new }
  const last = new Map();
  let frameCount = 0;

  for (const line of lines.slice(1)) {
    const rec = JSON.parse(line);
    if (rec.type && rec.type !== "frame") continue; // skip non-frame records (e.g. footer)
    frameCount += 1;
    const frame = rec.f;
    const fields = rec.fields ?? {};
    for (const [key, value] of Object.entries(fields)) {
      const serialized = JSON.stringify(value);
      const prev = last.get(key);
      if (prev !== undefined && prev.serialized !== serialized) {
        changes.push({ field: key, frame, old: prev.value, new: value });
      }
      last.set(key, { serialized, value });
    }
  }

  return { meta, frameCount, changes };
}

function printSummary(filePath, { meta, frameCount, changes }) {
  console.log(`# summary: ${filePath}`);
  console.log(`preset=${meta.preset ?? "?"} (${meta.title ?? ""})`);
  console.log(`scenario=${meta.scenario ?? "?"} borg=${meta.borg ?? "?"} recordedAt=${meta.recordedAt ?? "?"}`);
  console.log(`frames=${frameCount} changePoints=${changes.length}`);
  console.log("");
  if (!changes.length) {
    console.log("(no field changes recorded)");
    return;
  }
  console.log("frame\tfield\told -> new");
  for (const c of changes) {
    console.log(`${c.frame}\t${c.field}\t${JSON.stringify(c.old)} -> ${JSON.stringify(c.new)}`);
  }
}

// ── --dry-run: print resolved watch list only, no Dolphin/file I/O; or, combined with
// --summarize, run --summarize against the canned fixture so the whole pipeline is
// exercised without a live game. ──
function runDryRun(presetId) {
  const preset = resolvePreset(presetId);
  const watchList = buildWatchList(preset);
  console.log(
    JSON.stringify(
      {
        preset: presetId,
        title: preset.title,
        slug: preset.slug,
        watchList,
        chase: preset.chase ?? null,
        outPathTemplate: `user-data/dolphin-trace/attack-mechanics/${presetId}-${preset.slug}.jsonl`,
      },
      null,
      2,
    ),
  );
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

const DEFAULT_TICK_ADDR = 0x8010d450;
const PAD_READ = 0x8021379c;
// Battle/slot-table chain (behavior-notes.md §z, code-confirmed). Single-player fast path
// reads *(u32*)0x803C4E84 directly; we use the full chain so this also works when the
// player isn't in slot 0.
const SLOT_TABLE_PTR = 0x80433934;
const ACTOR_ARRAY = 0x803c4e84;

async function validateBorgBase(gdb, base, slot) {
  if (!isMem1(base)) return false;
  const slotBuf = await gdb.readMem((base + 0x3e4) >>> 0, 1);
  const stateBuf = await gdb.readMem((base + 0x544) >>> 0, 4);
  if (!slotBuf || !stateBuf) return false;
  const slotField = slotBuf.readInt8(0);
  const state = stateBuf.readInt32BE(0);
  return slotField === slot && state >= -1 && state <= 64;
}

async function resolveBorgBase(gdb, baseOverride) {
  if (baseOverride !== null) return { base: baseOverride, via: "cli-override" };
  const tBuf = await gdb.readMem(SLOT_TABLE_PTR, 4);
  const t = tBuf ? tBuf.readUInt32BE(0) : 0;
  if (isMem1(t)) {
    const slotBuf = await gdb.readMem((t + 0xc0) >>> 0, 1);
    const rawSlot = slotBuf ? slotBuf.readInt8(0) : 0;
    const slot = rawSlot >= 0 && rawSlot <= 5 ? rawSlot : 0;
    const baseBuf = await gdb.readMem((ACTOR_ARRAY + slot * 4) >>> 0, 4);
    const base = baseBuf ? baseBuf.readUInt32BE(0) : 0;
    if (await validateBorgBase(gdb, base, slot)) return { base, via: `slot-table(slot=${slot})` };
  }
  // Single-player fast path fallback.
  const fastBuf = await gdb.readMem(ACTOR_ARRAY, 4);
  const fastBase = fastBuf ? fastBuf.readUInt32BE(0) : 0;
  if (await validateBorgBase(gdb, fastBase, 0)) return { base: fastBase, via: "fast-path-slot0" };
  throw new Error("could not resolve active borg base (no battle in progress?)");
}

async function readField(gdb, base, field) {
  const relativeOffset = field.off ?? field.offset;
  const address = field.absolute ? field.offset ?? field.address ?? field.off : (base + relativeOffset) >>> 0;
  const buf = await gdb.readMem(address >>> 0, field.size);
  if (!buf) return null;
  return readerFor(field.type)(buf);
}

function parseAddress(raw, label) {
  const value = Number.parseInt(raw, raw?.startsWith("0x") ? 16 : 10);
  if (!Number.isInteger(value)) throw new Error(`${label} must be an address`);
  return value >>> 0;
}

async function runCapture(argv) {
  const presetId = argv.get("preset");
  if (!presetId) throw new Error("--preset T1..T10 is required for a real capture");
  const preset = resolvePreset(presetId);

  const frames = Number.parseInt(argv.get("frames") ?? "1800", 10);
  const host = argv.get("host") ?? "127.0.0.1";
  const port = Number.parseInt(argv.get("port") ?? "5555", 10);
  const tickAddr = parseAddress(argv.get("tick-addr") ?? `0x${DEFAULT_TICK_ADDR.toString(16)}`, "--tick-addr");
  const borg = argv.get("borg") ?? "unknown";
  const scenario = argv.get("scenario") ?? "";
  const note = argv.get("note") ?? "";
  const baseOverride = argv.has("base") ? Number.parseInt(argv.get("base"), 16) >>> 0 : null;
  const outPath =
    argv.get("out") ??
    path.join(repoRoot, "user-data", "dolphin-trace", "attack-mechanics", `${presetId}-${preset.slug}.jsonl`);

  fs.mkdirSync(path.dirname(outPath), { recursive: true });

  const gdb = new GdbRemote(host, port);
  await connectWithRetry(gdb);
  console.log(`connected to Dolphin GDB stub at ${host}:${port}`);
  gdb.interrupt();
  await gdb.waitPacket(10000).catch(() => {});

  const out = fs.createWriteStream(outPath, { flags: "w" });
  let metaWritten = false;

  const watchList = buildWatchList(preset);
  const kind = await gdb.setBreak(tickAddr);
  let cleanedUp = false;
  const cleanup = async () => {
    if (cleanedUp) return;
    cleanedUp = true;
    await gdb.clearBreak(tickAddr, kind).catch(() => {});
    await gdb.send("c").catch(() => {});
    out.end();
    gdb.close();
  };
  const onSignal = () => {
    cleanup().finally(() => process.exit(130));
  };
  process.once("SIGINT", onSignal);
  process.once("SIGTERM", onSignal);
  console.log(
    `recording ${frames} frames for ${presetId} (${preset.title}) at tick 0x${tickAddr.toString(16)} - perform the input recipe now`,
  );
  let recorded = 0;
  let quietStreak = 0;
  try {
    while (recorded < frames) {
      let stop;
      try {
        stop = await gdb.continueAndWaitStop(30000);
        quietStreak = 0;
      } catch {
        quietStreak += 1;
        console.log(`  no tick hits for 30s (game paused/menus?) - ${recorded} recorded so far`);
        if (quietStreak >= 6) throw new Error("no tick hits for 3 minutes; stopping with what we have");
        continue;
      }
      if (stop.pc !== tickAddr) continue;

      let base;
      let via;
      try {
        ({ base, via } = await resolveBorgBase(gdb, baseOverride));
      } catch (error) {
        if (recorded === 0) console.log(`  tick hit, but no valid active borg base yet (${error.message}); waiting`);
        continue;
      }
      if (!metaWritten) {
        console.log(`active borg base = 0x${base.toString(16)} (via ${via})`);
        const meta = {
          type: "meta",
          schema: "gotyaforce.attackMechanicsTrace.v1",
          generatedBy: "scripts/trace-attack-mechanics.mjs",
          preset: presetId,
          title: preset.title,
          recordedAt: new Date().toISOString(),
          region: "GG4E",
          borg,
          scenario,
          note,
          borgBase: `0x${base.toString(16)}`,
          borgBaseVia: via,
          tickAddr: `0x${tickAddr.toString(16)}`,
          tickKind: tickAddr === DEFAULT_TICK_ADDR ? "game-pad-normalization-cluster" : tickAddr === PAD_READ ? "pad-read" : "custom",
          padReadAddr: `0x${PAD_READ.toString(16)}`,
          pairing:
            tickAddr === PAD_READ
              ? "pad buffer at PADRead entry = PREVIOUS frame's input; fields = state after that frame"
              : "fields sampled on the proven game-side per-frame input/normalization tick at 0x8010d450",
          watchList: buildWatchList(preset),
          chase: preset.chase ?? null,
          limitations:
            presetId === "T1"
              ? "cmdStructBytes is chased via two sequential (non-atomic) GDB-stub reads per frame " +
                "(read cmdStructPtr, then read cmdStructPtr+0..7); treat cmdStructPtr as ground truth " +
                "if the chased bytes look torn. See script header for detail."
              : null,
        };
        out.write(JSON.stringify(meta) + "\n");
        metaWritten = true;
      }

      const fields = {};
      for (const field of watchList) {
        fields[field.name] = await readField(gdb, base, field);
      }
      if (preset.chase) {
        const ptr = fields[preset.chase.ptrField];
        if (isMem1(ptr)) {
          const chaseBuf = await gdb.readMem(ptr >>> 0, preset.chase.len);
          fields[preset.chase.name] = chaseBuf ? chaseBuf.toString("hex") : null;
        } else {
          fields[preset.chase.name] = null;
        }
      }

      out.write(JSON.stringify({ type: "frame", f: recorded, borgBase: `0x${base.toString(16)}`, borgBaseVia: via, fields }) + "\n");
      recorded += 1;
      if (recorded % 300 === 0) console.log(`  ${recorded}/${frames} frames`);
    }
  } finally {
    process.removeListener("SIGINT", onSignal);
    process.removeListener("SIGTERM", onSignal);
    await cleanup();
  }
  console.log(`wrote ${recorded} frames to ${outPath}`);
  console.log(`next: node scripts/trace-attack-mechanics.mjs --summarize ${outPath}`);
}

async function main() {
  const { flags } = parseArgs(process.argv.slice(2));
  const dryRun = flags.has("dry-run");
  const summarize = flags.has("summarize");
  const summarizeArg = flags.get("summarize");

  if (dryRun && summarize) {
    // Ticket-required test path: exercise --summarize against the canned fixture, no
    // Dolphin, no live game. Uses the explicit fixture path unless --summarize=<file> or
    // --out was given.
    const target = summarizeArg && summarizeArg !== "1" ? summarizeArg : flags.get("out") ?? FIXTURE_PATH;
    printSummary(target, summarizeFile(target));
    return;
  }

  if (summarize) {
    const target = summarizeArg && summarizeArg !== "1" ? summarizeArg : null;
    if (!target) throw new Error("--summarize requires a file path (--summarize <file.jsonl>) unless combined with --dry-run");
    printSummary(target, summarizeFile(target));
    return;
  }

  if (dryRun) {
    const presetId = flags.get("preset");
    if (!presetId) throw new Error("--dry-run requires --preset T1..T10");
    runDryRun(presetId);
    return;
  }

  await runCapture(flags);
}

main().catch((error) => {
  console.error(error.stack || error.message);
  process.exitCode = 1;
});
