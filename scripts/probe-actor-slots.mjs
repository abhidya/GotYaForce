#!/usr/bin/env node
// probe-actor-slots.mjs — one-shot dump of identity/state fields for every actor slot.
// Written for W17 (death-borg husk): confirms which pl#### id a force-exhausted player's
// husk uses and what +0x4a0/+0x4a1 hold. Reads while halted at the proven frame tick
// (same pattern as diff-actor-block.mjs — never right after a bare interrupt).
//
// Usage (Dolphin running with --config=Dolphin.General.GDBPort=5555, battle loaded):
//   node scripts/probe-actor-slots.mjs

import { GdbRemote, isMem1 } from "./lib/gdb-remote.mjs";

const TICK_ADDR = 0x8010d450;
const ACTOR_ARRAY = 0x803c4e84;
const SLOT_COUNT = 6;

// [name, offset, type] — type: u8/s8/u16/s16/u32/f32
const FIELDS = [
  ["active", 0x00, "u8"], // *actor != 0 gates most per-actor logic (zz_005b2b8_)
  ["playerIdx", 0x88, "s8"], // PTR_DAT_80433934 player-record index
  ["slotByte", 0x3e4, "s8"],
  ["fusionSpawnId48c", 0x48c, "u16"], // fusion result spawn id (behavior-notes 1944), NOT species
  ["heroFlag3e6", 0x3e6, "u8"],
  ["speciesByte3e7", 0x3e7, "u8"], // "object+999" species candidate (behavior-notes 517)
  ["speciesWord3e8", 0x3e8, "u16"], // actor+1000: HUD reads this u16 (chunk_0001.c:7721)
  ["hp", 0x1c6, "s16"],
  ["spawnType4a0", 0x4a0, "u8"], // W17 husk-marker candidate (chunk_0006.c:7175)
  ["pairState4a1", 0x4a1, "u8"],
  ["weaponCell774", 0x774, "u16"], // B ammo current
  ["weaponCell776", 0x776, "u16"], // B ammo max
  ["burstActive6fc", 0x6fc, "u8"],
];

function readerFor(type) {
  switch (type) {
    case "u8": return (b) => b.readUInt8(0);
    case "s8": return (b) => b.readInt8(0);
    case "u16": return (b) => b.readUInt16BE(0);
    case "s16": return (b) => b.readInt16BE(0);
    case "u32": return (b) => b.readUInt32BE(0);
    case "f32": return (b) => b.readFloatBE(0);
    default: throw new Error(`bad type ${type}`);
  }
}
const sizeFor = (t) => (t.endsWith("8") ? 1 : t.endsWith("16") ? 2 : 4);

async function readMemExact(gdb, address, bytes) {
  const buf = await gdb.readMem(address >>> 0, bytes);
  return buf && buf.length === bytes ? buf : null;
}

const gdb = new GdbRemote("127.0.0.1", 5555);
await gdb.connect();
console.log("connected to Dolphin GDB stub");
gdb.interrupt();
await gdb.waitPacket(10000).catch(() => {});

const kind = await gdb.setBreak(TICK_ADDR);
try {
  for (let i = 0; i < 600; i += 1) {
    const stop = await gdb.continueAndWaitStop(30000);
    if (stop.pc === TICK_ADDR) break;
  }
  for (let slot = 0; slot < SLOT_COUNT; slot += 1) {
    const ptrBuf = await readMemExact(gdb, ACTOR_ARRAY + slot * 4, 4);
    const base = ptrBuf ? ptrBuf.readUInt32BE(0) : 0;
    if (!isMem1(base)) {
      console.log(`slot ${slot}: <no actor> (ptr=0x${base.toString(16)})`);
      continue;
    }
    const parts = [`base=0x${base.toString(16)}`];
    for (const [name, off, type] of FIELDS) {
      const buf = await readMemExact(gdb, base + off, sizeFor(type));
      const value = buf ? readerFor(type)(buf) : null;
      const hex = typeof value === "number" && type.startsWith("u") && value > 9 ? ` (0x${value.toString(16)})` : "";
      parts.push(`${name}=${value}${hex}`);
    }
    console.log(`slot ${slot}: ${parts.join(" ")}`);
  }
} finally {
  await gdb.clearBreak(TICK_ADDR, kind).catch(() => {});
  await gdb.send("c", 2000).catch(() => {});
  gdb.close();
}
