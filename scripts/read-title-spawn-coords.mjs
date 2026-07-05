// One-shot GDB memory reader: resolve the title-desk-intro actor spawn coords.
// Connects to Dolphin's GDB stub, halts the CPU, reads PTR_DAT_80433934 (the front-end
// state block pointer), then reads the per-slot spawn-position table at state+0x1604
// (12 bytes per slot: f32 X/Y/Z, per FUN_80056d28 chunk_0007.c:448-451).
//
// Run while Dolphin is at/past the title desk intro (the state block persists in MEM1).
// Usage: node scripts/read-title-spawn-coords.mjs [--host 127.0.0.1] [--port 5555]

import { GdbRemote } from "./lib/gdb-remote.mjs";

const HOST = process.argv.includes("--host") ? process.argv[process.argv.indexOf("--host") + 1] : "127.0.0.1";
const PORT = Number.parseInt(
  process.argv.includes("--port") ? process.argv[process.argv.indexOf("--port") + 1] : "5555",
  10,
);

const BORG_ID_TABLE = 0x10; // state+0x10: 6 u16 borg ids (slot -> id, 0xffff = empty)
const SPAWN_TABLE = 0x1604; // state+0x1604: per-slot f32 XYZ, stride 0xc
// Inspect the actor's JOBJ root (the rendered figure's joint tree) to find its world
// translation. HSD JOBJ layout (from HSD_JObjMakeMatrix chunk_0071.c:3461-3521):
//   +0x04 child, +0x08 next, +0x0c parent, +0x14 flags,
//   +0x2c/+0x30/+0x34 scale, +0x38/+0x3c/+0x40 rotation, +0x44/+0x48/+0x4c translation,
//   +0x74 scale-cache ptr, world matrix cached further down.
// The actor's JOBJ root is reached via actor+0x3fc (the model-tree pointer found in the
// prior scan). We dump it + walk parent/child to surface any non-zero translation.
const ANIM_TRIGGER = 0x80057ff8;
const ACTOR_JOBJ_PTR_OFF = 0x3fc; // actor field holding the JOBJ root (0x80be1xxx model tree)

function readF32(buf, off) {
  return buf.readFloatBE(off);
}
function hex8(v) {
  return "0x" + (v >>> 0).toString(16).padStart(8, "0");
}
function plausibleCoord(v) {
  return Number.isFinite(v) && Math.abs(v) > 10 && Math.abs(v) < 20000;
}

const gdb = new GdbRemote(HOST, PORT);
await gdb.connect();
console.log(`connected to ${HOST}:${PORT}; halting at anim-trigger (r3 = actor)...`);
const bpKind = await gdb.setBreak(ANIM_TRIGGER);
await gdb.continueAndWaitStop(90000).catch(() => {});
const actor = await gdb.readReg(3);
console.log(`halted; actor=${actor ? hex8(actor) : "?"}`);
if (!actor) {
  await gdb.clearBreak(ANIM_TRIGGER, bpKind);
  await gdb.send("c", 2000).catch(() => {});
  gdb.close();
  process.exit(1);
}
await gdb.clearBreak(ANIM_TRIGGER, bpKind);

const borgBuf = await gdb.readMem(actor + 0x3e8, 2);
if (borgBuf) console.log(`actor+0x3e8 borgId = 0x${borgBuf.readUInt16BE(0).toString(16)}`);

// Resolve the JOBJ root from actor+0x3fc.
const jobjPtrBuf = await gdb.readMem(actor + ACTOR_JOBJ_PTR_OFF, 4);
const jobjRoot = jobjPtrBuf ? (jobjPtrBuf.readUInt32BE(0) >>> 0) : 0;
console.log(`actor+0x${ACTOR_JOBJ_PTR_OFF.toString(16)} -> JOBJ root = ${jobjRoot ? hex8(jobjRoot) : "?"}`);

// Walk the JOBJ from root, dumping each visited joint's translation + parent/child.
async function dumpJObj(ptr, label, depth = 0, seen = new Set()) {
  if (!ptr || seen.has(ptr) || depth > 4) return;
  seen.add(ptr);
  const buf = await gdb.readMem(ptr, 0x80);
  if (!buf) {
    console.log(`${label}${hex8(ptr)}: read failed`);
    return;
  }
  const child = buf.readUInt32BE(0x04) >>> 0;
  const next = buf.readUInt32BE(0x08) >>> 0;
  const parent = buf.readUInt32BE(0x0c) >>> 0;
  const flags = buf.readUInt32BE(0x14) >>> 0;
  const sc = [readF32(buf, 0x2c), readF32(buf, 0x30), readF32(buf, 0x34)];
  const rot = [readF32(buf, 0x38), readF32(buf, 0x3c), readF32(buf, 0x40)];
  const tr = [readF32(buf, 0x44), readF32(buf, 0x48), readF32(buf, 0x4c)];
  const trPlausible = tr.every(plausibleCoord) ? "  <-- WORLD POSITION?" : "";
  console.log(
    `${label}${hex8(ptr)} flags=${hex8(flags)} parent=${parent ? hex8(parent) : "-"} child=${child ? hex8(child) : "-"}\n` +
      `    scale=[${sc.map((v) => v.toFixed(2)).join(",")}] rot=[${rot.map((v) => v.toFixed(3)).join(",")}] transl=[${tr.map((v) => v.toFixed(2)).join(",")}]${trPlausible}`,
  );
  // Also scan the full 0x80 bytes for any plausible triple (matrix cache).
  for (let off = 0x50; off <= 0x70; off += 4) {
    const a = readF32(buf, off);
    const b = readF32(buf, off + 4);
    const d = readF32(buf, off + 8);
    if (plausibleCoord(a) && plausibleCoord(b) && plausibleCoord(d)) {
      console.log(`    matrix-cache @ +0x${off.toString(16)}: X=${a.toFixed(2)} Y=${b.toFixed(2)} Z=${d.toFixed(2)}  <-- candidate`);
      break;
    }
  }
  await dumpJObj(child, label + "  child.", depth + 1, seen);
  await dumpJObj(next, label + "  next.", depth + 1, seen);
  await dumpJObj(parent, label + "  parent.", depth + 1, seen);
}

if (jobjRoot) await dumpJObj(jobjRoot, "JOBJ ");

await gdb.send("c", 2000).catch(() => {});
gdb.close();
console.log("done; CPU resumed.");
