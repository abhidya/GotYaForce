// Targeted JOBJ hunt: the bulk MEM1 scan resets Dolphin's single-client GDB stub (too
// many large reads while halted). Narrow to two small, high-signal regions:
//  (1) the actor's FULL struct (0x00..0x1e00, ~7.5KB) — the JOBJ root pointer is stored
//      somewhere in the actor; scan for pointers near the model blob's heap range.
//  (2) a narrow window around the model blob (blob-0x10000 .. blob+0x10000) — HSD
//      allocates the JOBJ/DOBJ/MOBJ/POBJ cluster together, so the owning JOBJ is nearby
//      and back-references the blob.
// Small chunks (4KB) + few reads to avoid the stub reset.

import { GdbRemote } from "./lib/gdb-remote.mjs";

const HOST = process.argv.includes("--host") ? process.argv[process.argv.indexOf("--host") + 1] : "127.0.0.1";
const PORT = Number.parseInt(
  process.argv.includes("--port") ? process.argv[process.argv.indexOf("--port") + 1] : "5555",
  10,
);

const ANIM_TRIGGER = 0x80057ff8;
const ACTOR_MODEL_PTR_OFF = 0x3fc;
const ACTOR_LEN = 0x1e00;
const CHUNK = 0x1000;

function hex8(v) {
  return "0x" + (v >>> 0).toString(16).padStart(8, "0");
}
function readF32(buf, off) {
  return buf.readFloatBE(off);
}
function plausibleCoord(v) {
  return Number.isFinite(v) && Math.abs(v) > 10 && Math.abs(v) < 20000;
}
function inHeap(v) {
  return v >= 0x80000000 && v < 0x81800000;
}

const gdb = new GdbRemote(HOST, PORT);
await gdb.connect();
console.log(`connected; halting at anim-trigger...`);
const bpKind = await gdb.setBreak(ANIM_TRIGGER);
await gdb.continueAndWaitStop(90000).catch(() => {});
const actor = await gdb.readReg(3);
const blobBuf = await gdb.readMem(actor + ACTOR_MODEL_PTR_OFF, 4);
const blob = blobBuf ? (blobBuf.readUInt32BE(0) >>> 0) : 0;
console.log(`halted; actor=${hex8(actor)} model blob=${blob ? hex8(blob) : "?"}`);
if (!blob) {
  await gdb.clearBreak(ANIM_TRIGGER, bpKind);
  await gdb.send("c", 2000).catch(() => {});
  gdb.close();
  process.exit(1);
}
await gdb.clearBreak(ANIM_TRIGGER, bpKind);

// Region 1: scan the actor struct for heap pointers near the blob's range.
const blobBase = blob & 0xfffff000; // 4KB-align down
const nearLo = blobBase - 0x10000;
const nearHi = blobBase + 0x20000;
console.log(`\n(1) scanning actor struct 0x00..0x${ACTOR_LEN.toString(16)} for pointers in [${hex8(nearLo)}..${hex8(nearHi)}]...`);
const actorPtrs = [];
for (let off = 0; off < ACTOR_LEN; off += CHUNK) {
  const len = Math.min(CHUNK, ACTOR_LEN - off);
  const buf = await gdb.readMem(actor + off, len);
  if (!buf) continue;
  for (let o = 0; o + 4 <= buf.length; o += 4) {
    const v = buf.readUInt32BE(o) >>> 0;
    if (v >= nearLo && v < nearHi) actorPtrs.push({ where: `actor+0x${(off + o).toString(16).padStart(3, "0")}`, ptr: v });
  }
}
console.log(`  ${actorPtrs.length} near-blob pointer(s) in actor struct:`);
for (const p of actorPtrs) console.log(`    ${p.where} -> ${hex8(p.ptr)}`);

// Region 2: scan the blob neighborhood for back-pointers to the blob.
console.log(`\n(2) scanning blob neighborhood [${hex8(nearLo)}..${hex8(nearHi)}] for ${hex8(blob)}...`);
const needle = Buffer.alloc(4);
needle.writeUInt32BE(blob, 0);
const refs = [];
for (let addr = nearLo; addr < nearHi; addr += CHUNK) {
  const buf = await gdb.readMem(addr, Math.min(CHUNK, nearHi - addr));
  if (!buf) continue;
  for (let o = 0; o + 4 <= buf.length; o += 4) {
    if (buf[o] === needle[0] && buf[o + 1] === needle[1] && buf[o + 2] === needle[2] && buf[o + 3] === needle[3]) {
      refs.push(addr + o);
    }
  }
}
console.log(`  ${refs.length} back-pointer site(s).`);

// Dereference each candidate (actor near-blob ptrs + back-ref sites' neighborhood) as a
// JOBJ and surface plausible world translations.
const candidates = [
  ...actorPtrs.map((p) => p.ptr),
  ...refs.map((r) => r), // the ref site itself; the JOBJ base is nearby
];
// For back-ref sites, also probe a few words before as a JOBJ base.
const jobjCandidates = new Set();
for (const c of candidates) {
  jobjCandidates.add(c);
  for (let back = 4; back <= 0x40; back += 4) jobjCandidates.add(c - back);
}
console.log(`\n=== JOBJ translation scan (${jobjCandidates.size} candidates) ===`);
let found = 0;
for (const base of jobjCandidates) {
  if (!inHeap(base)) continue;
  const jbuf = await gdb.readMem(base, 0x90);
  if (!jbuf) continue;
  for (let off = 0x10; off <= 0x70; off += 4) {
    if (off + 12 > jbuf.length) break;
    const a = readF32(jbuf, off);
    const b = readF32(jbuf, off + 4);
    const d = readF32(jbuf, off + 8);
    if (plausibleCoord(a) && plausibleCoord(b) && plausibleCoord(d)) {
      console.log(`  ${hex8(base)} +0x${off.toString(16)}: X=${a.toFixed(2)} Y=${b.toFixed(2)} Z=${d.toFixed(2)}  <-- WORLD POSITION?`);
      found += 1;
      break;
    }
  }
}
if (!found) console.log("(no plausible XYZ triple found)");

await gdb.send("c", 2000).catch(() => {});
gdb.close();
console.log("done; CPU resumed.");
