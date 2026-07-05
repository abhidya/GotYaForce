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
// Dump a large region of the actor struct, scan for MEM1 heap pointers, and dereference
// each to find the JOBJ (rendered joint tree) whose root translation = the desk world pos.
// HSD JOBJ layout has 3 consecutive f32 (trX/trY/trZ) in world-coord range; we surface any
// dereferenced pointer whose bytes contain such a triple.
const ANIM_TRIGGER = 0x80057ff8;
const SCAN_LEN = 0x800; // scan actor+0x00..+0x800 for pointer candidates
const MEM1_LO = 0x80000000;
const MEM1_HI = 0x81800000;

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
const groupSel = await gdb.readReg(4);
const animId = await gdb.readReg(5);
console.log(`halted; actor=${actor ? hex8(actor) : "?"} groupSel=${groupSel} animId=${animId}`);
if (!actor) {
  await gdb.clearBreak(ANIM_TRIGGER, bpKind);
  await gdb.send("c", 2000).catch(() => {});
  gdb.close();
  process.exit(1);
}
await gdb.clearBreak(ANIM_TRIGGER, bpKind);

const actorBuf = await gdb.readMem(actor, SCAN_LEN);
if (!actorBuf) {
  console.log("actor struct read failed");
  await gdb.send("c", 2000).catch(() => {});
  gdb.close();
  process.exit(1);
}

// Scan for MEM1 heap pointer candidates, dedupe.
const seen = new Set([actor]);
const candidates = [];
for (let off = 0; off < actorBuf.length - 4; off += 4) {
  const v = actorBuf.readUInt32BE(off) >>> 0;
  if (v >= MEM1_LO && v < MEM1_HI && !seen.has(v)) {
    seen.add(v);
    candidates.push({ off, ptr: v });
  }
}
console.log(`\n${candidates.length} distinct heap-pointer candidates in actor+0x00..+0x${SCAN_LEN.toString(16)}:`);

// Dereference each + surface any with a plausible XYZ triple (the JOBJ translation),
// scanning DEEPER (0x80 bytes, offsets 0x00..0x70 — HSD JOBJ translation lives at various
// offsets depending on the joint's parent/child ptr layout).
const jobjHits = [];
for (const c of candidates) {
  const deref = await gdb.readMem(c.ptr, 0x80);
  if (!deref) continue;
  for (let off = 0; off <= 0x70; off += 4) {
    const a = readF32(deref, off);
    const b = readF32(deref, off + 4);
    const d = readF32(deref, off + 8);
    if (plausibleCoord(a) && plausibleCoord(b) && plausibleCoord(d)) {
      jobjHits.push({ actorOff: c.off, ptr: c.ptr, derefOff: off, x: a, y: b, z: d });
      break;
    }
  }
}
console.log(`\n=== plausible XYZ triples (JOBJ translation candidates) ===`);
for (const h of jobjHits) {
  console.log(`actor+0x${h.actorOff.toString(16).padStart(3, "0")} -> ${hex8(h.ptr)} +0x${h.derefOff.toString(16).padStart(2, "0")}: X=${h.x.toFixed(2)} Y=${h.y.toFixed(2)} Z=${h.z.toFixed(2)}`);
}
if (!jobjHits.length) console.log("(none found in first 0x80 bytes of any pointer candidate)");

// Dump the full 0x80 bytes of the top 3 high-heap candidates (likely model/JOBJ roots) for
// manual inspection — the translation may sit at an offset our triple-scan missed, or the
// root joint may be at origin with placement in a parent (then we follow child/parent ptrs).
const highHeap = candidates
  .filter((c) => c.ptr >= 0x80600000 && c.ptr < 0x81800000)
  .sort((a, b) => b.ptr - a.ptr)
  .slice(0, 3);
console.log(`\n=== top high-heap candidates (full 0x80 deref) ===`);
for (const c of highHeap) {
  const deref = await gdb.readMem(c.ptr, 0x80);
  if (!deref) continue;
  const f32s = Array.from({ length: 0x20 }, (_, i) => readF32(deref, i * 4));
  const u32s = Array.from({ length: 0x20 }, (_, i) => hex8(deref.readUInt32BE(i * 4) >>> 0));
  console.log(`actor+0x${c.off.toString(16).padStart(3, "0")} -> ${hex8(c.ptr)}:`);
  for (let i = 0; i < 0x20; i += 1) {
    const f = f32s[i];
    const mark = plausibleCoord(f) ? "*" : " ";
    console.log(`    +0x${(i * 4).toString(16).padStart(2, "0")}: ${u32s[i]} f32=${f.toFixed(2).padStart(12)} ${mark}`);
  }
}

const borgBuf = await gdb.readMem(actor + 0x3e8, 2);
if (borgBuf) console.log(`\nactor+0x3e8 borgId = 0x${borgBuf.readUInt16BE(0).toString(16)}`);

await gdb.send("c", 2000).catch(() => {});
gdb.close();
console.log("done; CPU resumed.");
