#!/usr/bin/env node
// Golden-trace recorder: capture per-frame (pad input, borg position/velocity/heading/state)
// from a live Dolphin Challenge battle over the GDB stub, to a JSONL "golden" file.
//
// This is workstream 3 of research/game-design/DATA-DRIVEN-REBUILD-PLAN.md: the recorded
// golden is the evidence source for replacing TUNED movement constants with trace-DERIVED
// values (fit with scripts/trace-golden-analyze.mjs).
//
// Anchors (all previously proven in research/traces/GG4E/breakpoints-watchpoints.json and
// research/decomp/behavior-notes.md / ram-trace-analysis.md §3.2):
//   0x8021379c  PADRead          — r3 = PADStatus[4] output buffer. Called once per frame;
//                                  used as the per-frame tick. NOTE: at function ENTRY the
//                                  buffer still holds the PREVIOUS frame's pads, so each
//                                  record pairs input_N with the borg state AFTER frame N —
//                                  a consistent (input, resulting state) pair.
//   0x8005d4b0  wakeup-invulnerability-init — r3  = active borg base (fires on spawn/wakeup)
//   0x80055c00  wakeup-timer-countdown      — r31 = active borg base (fires while timer runs)
//   borg struct: +0x44/48/4c pos floats, +0x58/5c/60 velocity floats, +0x72 heading s16,
//                +0x544 state s32, +0x720 invulnerability float. All code-confirmed.
//
// Usage:
//   1. Launch Dolphin with the GDB stub enabled (see research/traces/GG4E/golden-trace-runbook.md),
//      boot into a Challenge battle with the borg you want to calibrate.
//   2. node scripts/trace-golden-record.mjs --borg pl0615 --label fwd-jump-dash --frames 1800
//   3. The script waits for a wakeup-timer hit to resolve the borg base (trigger a spawn /
//      knockdown if it stalls), then records N frames while you perform the input recipe.
//
// Options: --frames N (default 1800 = 30s), --borg plXXXX, --label name, --out file,
//          --host/--port (default 127.0.0.1:5555), --base 0x… (skip base resolution).

import fs from "node:fs";
import path from "node:path";
import { fileURLToPath } from "node:url";
import { GdbRemote, isMem1 } from "./lib/gdb-remote.mjs";

const repoRoot = path.resolve(path.dirname(fileURLToPath(import.meta.url)), "..");

const args = new Map();
for (let i = 2; i < process.argv.length; i += 1) {
  const a = process.argv[i];
  if (!a.startsWith("--")) continue;
  const eq = a.indexOf("=");
  if (eq >= 0) args.set(a.slice(2, eq), a.slice(eq + 1));
  else args.set(a.slice(2), process.argv[i + 1]?.startsWith("--") ? "" : (process.argv[++i] ?? ""));
}

const FRAMES = Number.parseInt(args.get("frames") ?? "1800", 10);
const BORG = args.get("borg") ?? "unknown";
const LABEL = args.get("label") ?? "golden";
const HOST = args.get("host") ?? "127.0.0.1";
const PORT = Number.parseInt(args.get("port") ?? "5555", 10);
const BASE_OVERRIDE = args.has("base") ? Number.parseInt(args.get("base"), 16) >>> 0 : null;
const OUT =
  args.get("out") ??
  path.join(repoRoot, "user-data", "dolphin-trace", "golden", `${LABEL}-${BORG}-${Date.now()}.jsonl`);

const PAD_READ = 0x8021379c;
const BASE_ANCHORS = [
  { addr: 0x8005d4b0, regId: 3, id: "wakeup-invulnerability-init" },
  { addr: 0x80055c00, regId: 31, id: "wakeup-timer-countdown" },
];
const OFF = { posBlock: 0x40, posBlockLen: 0x40, state: 0x544, invuln: 0x720 };

// Standard GC PAD SDK button bits (PADStatus.button, u16 big-endian).
const BUTTONS = {
  0x0001: "dLeft", 0x0002: "dRight", 0x0004: "dDown", 0x0008: "dUp",
  0x0010: "Z", 0x0020: "R", 0x0040: "L",
  0x0100: "A", 0x0200: "B", 0x0400: "X", 0x0800: "Y", 0x1000: "Start",
};

function decodePad(buf, padIndex) {
  const o = padIndex * 12;
  const button = buf.readUInt16BE(o);
  return {
    raw: buf.subarray(o, o + 12).toString("hex"),
    buttons: Object.entries(BUTTONS).filter(([bit]) => button & Number(bit)).map(([, n]) => n),
    stickX: buf.readInt8(o + 2),
    stickY: buf.readInt8(o + 3),
    substickX: buf.readInt8(o + 4),
    substickY: buf.readInt8(o + 5),
    triggerL: buf.readUInt8(o + 6),
    triggerR: buf.readUInt8(o + 7),
    err: buf.readInt8(o + 10),
  };
}

async function resolveBorgBase(gdb) {
  if (BASE_OVERRIDE !== null) return { base: BASE_OVERRIDE, via: "cli-override" };
  const kinds = new Map();
  for (const a of BASE_ANCHORS) kinds.set(a.addr, await gdb.setBreak(a.addr));
  console.log("waiting for a wakeup anchor to resolve the active borg base");
  console.log("(spawn into the battle, or take a knockdown, if this stalls)");
  try {
    for (;;) {
      const { pc } = await gdb.continueAndWaitStop(120000);
      const anchor = BASE_ANCHORS.find((a) => a.addr === pc);
      if (!anchor) continue; // unrelated stop; resume
      const base = await gdb.readReg(anchor.regId);
      if (isMem1(base)) return { base, via: anchor.id };
      console.warn(`anchor ${anchor.id} hit but register not in MEM1 (0x${base?.toString(16)}); retrying`);
    }
  } finally {
    for (const a of BASE_ANCHORS) await gdb.clearBreak(a.addr, kinds.get(a.addr));
  }
}

async function main() {
  if (!Number.isInteger(FRAMES) || FRAMES <= 0) throw new Error("--frames must be a positive integer");
  fs.mkdirSync(path.dirname(OUT), { recursive: true });
  const gdb = new GdbRemote(HOST, PORT);
  await gdb.connect();
  console.log(`connected to Dolphin GDB stub at ${HOST}:${PORT}`);
  gdb.interrupt();
  await gdb.waitPacket(10000).catch(() => {}); // initial stop ack, if any

  const { base, via } = await resolveBorgBase(gdb);
  console.log(`active borg base = 0x${base.toString(16)} (via ${via})`);

  const out = fs.createWriteStream(OUT);
  out.write(
    JSON.stringify({
      schema: "gf-golden-trace-v1",
      generatedBy: "scripts/trace-golden-record.mjs",
      recordedAt: new Date().toISOString(),
      region: "GG4E",
      borg: BORG,
      label: LABEL,
      borgBase: `0x${base.toString(16)}`,
      borgBaseVia: via,
      padReadAddr: `0x${PAD_READ.toString(16)}`,
      pairing: "pad buffer at PADRead entry = PREVIOUS frame's input; state = after that frame",
      offsets: { pos: "+0x44/48/4c f32", vel: "+0x58/5c/60 f32", heading: "+0x72 s16", state: "+0x544 s32", invuln: "+0x720 f32" },
    }) + "\n",
  );

  const kind = await gdb.setBreak(PAD_READ);
  console.log(`recording ${FRAMES} frames — perform the input recipe now`);
  let frames = 0;
  let padPtr = null;
  try {
    while (frames < FRAMES) {
      const { pc } = await gdb.continueAndWaitStop(30000);
      if (pc !== PAD_READ) continue;
      padPtr = await gdb.readReg(3);
      if (!isMem1(padPtr)) continue;
      const [padBuf, blk, stateBuf, invBuf] = [
        await gdb.readMem(padPtr, 0x30),
        await gdb.readMem(base + OFF.posBlock, OFF.posBlockLen),
        await gdb.readMem(base + OFF.state, 4),
        await gdb.readMem(base + OFF.invuln, 4),
      ];
      if (!padBuf || !blk) continue;
      const rec = {
        f: frames,
        pad: decodePad(padBuf, 0),
        pos: { x: blk.readFloatBE(0x44 - 0x40), y: blk.readFloatBE(0x48 - 0x40), z: blk.readFloatBE(0x4c - 0x40) },
        vel: { x: blk.readFloatBE(0x58 - 0x40), y: blk.readFloatBE(0x5c - 0x40), z: blk.readFloatBE(0x60 - 0x40) },
        heading: blk.readInt16BE(0x72 - 0x40),
        state: stateBuf ? stateBuf.readInt32BE(0) : null,
        invuln: invBuf ? invBuf.readFloatBE(0) : null,
      };
      out.write(JSON.stringify(rec) + "\n");
      frames += 1;
      if (frames % 300 === 0) console.log(`  ${frames}/${FRAMES} frames`);
    }
  } finally {
    await gdb.clearBreak(PAD_READ, kind);
    await gdb.send("c").catch(() => {}); // let the game run on
    out.end();
    gdb.close();
  }
  console.log(`wrote ${frames} frames to ${OUT}`);
  console.log(`next: node scripts/trace-golden-analyze.mjs ${OUT}`);
}

main().catch((error) => {
  console.error(error.message ?? error);
  process.exit(1);
});
