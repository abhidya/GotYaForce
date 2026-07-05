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
// zz_0057ff8_ (actor anim trigger) fires only during the desk-intro montage with r3 = the
// actor struct pointer. Dumping the actor struct here finds the live world-position floats
// (the menu transition re-zeroes the state+0x1604 spawn table, so the actor struct is the
// durable source). The state base (0x803d5d78, deterministic) is read via a dispatcher hit.
const DISPATCHER = 0x801c7de4;
const ANIM_TRIGGER = 0x80057ff8;

function readF32(buf, off) {
  return buf.readFloatBE(off);
}
function hex8(v) {
  return "0x" + v.toString(16).padStart(8, "0");
}

const gdb = new GdbRemote(HOST, PORT);
await gdb.connect();
console.log(`connected to ${HOST}:${PORT}; halting at anim-trigger (r3 = actor)...`);
const bpKind = await gdb.setBreak(ANIM_TRIGGER);
const stop = await gdb.continueAndWaitStop(90000).catch(() => {});
// r3 (stub id 3) = actor base; r4 = groupSel (expect 5); r5 = animId.
const actor = await gdb.readReg(3);
const groupSel = await gdb.readReg(4);
const animId = await gdb.readReg(5);
console.log(`halted at anim-trigger; r3/actor=${actor ? hex8(actor) : "?"} groupSel=${groupSel} animId=${animId}`);
if (!actor) {
  await gdb.clearBreak(ANIM_TRIGGER, bpKind);
  await gdb.send("c", 2000).catch(() => {});
  gdb.close();
  process.exit(1);
}
await gdb.clearBreak(ANIM_TRIGGER, bpKind);

// Dump the actor struct's first 0x100 bytes; surface plausible world-position floats
// (the desk scene is in thousands of units, so |v| in 50..20000 is a position candidate).
const buf = await gdb.readMem(actor, 0x100);
if (!buf) {
  console.log("actor struct read failed");
} else {
  console.log(`\=== actor struct @ ${hex8(actor)} (first 0x100 bytes), f32 scan ===`);
  for (let off = 0; off < buf.length; off += 4) {
    const v = readF32(buf, off);
    const u = buf.readUInt32BE(off) >>> 0;
    const plausible = Number.isFinite(v) && Math.abs(v) > 50 && Math.abs(v) < 20000;
    console.log(`  +0x${off.toString(16).padStart(3, "0")}: f32=${v.toFixed(2).padStart(12)} u32=${hex8(u)}${plausible ? "  <- position candidate" : ""}`);
  }
}

// Also read the borg id at actor+0x3e8 to confirm which actor this is.
const borgBuf = await gdb.readMem(actor + 0x3e8, 2);
if (borgBuf) console.log(`actor+0x3e8 borgId = 0x${borgBuf.readUInt16BE(0).toString(16)}`);

// Resume the CPU so the game doesn't stay halted.
await gdb.send("c", 2000).catch(() => {});
gdb.close();
console.log("\ndone; CPU resumed.");
