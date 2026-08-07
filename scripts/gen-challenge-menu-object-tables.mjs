#!/usr/bin/env node
// Dumps the GG4E Challenge-menu-object data tables + dispatch tables straight from boot.dol.
// Mirrors the DOL-reader pattern in scripts/gen-challenge-flow-tables.mjs. Output is
// consumed by apps/game/src/ui/challengeMenuObjectTables.generated.ts (written below).
//
// Evidence (chunk_0048.c):
// spawn_challenge_menu_object @0x80199b60 reads 16-byte records at DAT_80370f28:
//   allocKind = (&DAT_80370f31)[type*0x10], modelCount = (&DAT_80370f30)[type*0x10],
//   initFn    = (&PTR_FUN_80370f34)[type*4]  (pointer element => byte offset type*0x10);
//   record layout: +0..7 modelIds (signed bytes), +8 modelCount, +9 allocKind, +0xc initFn.
// challenge_menu_object_load_models_and_init @0x80199c74 walks modelIds[0..modelCount)
//   from &DAT_80370f28 + type*0x10, loading via zz_0006fb4_(DAT_803bb384, ...).
// dispatch_challenge_menu_object_state @0x80199c0c dispatches (&PTR_FUN_80370fa8)[state]
//   (states 0..3; finish_challenge_menu_object sets state 3).
// challenge_menu_object_load_models_and_init tail calls (&PTR_FUN_80370fb8)[type].
// update_challenge_menu_object_animation @0x80199d30 calls (&PTR_FUN_80370fd8)[type].
// init/update_challenge_menu_object_0 @0x80199dc0/0x80199ea8 read FLOAT_8043b370..b390 +
//   DOUBLE_8043b388 timing/layout constants.
import { createHash } from "node:crypto";
import { readFileSync, writeFileSync } from "node:fs";
import path from "node:path";

const BOOT_DOL_PATH = "user-data/GG4E/disc/sys/boot.dol";
const OUT_PATH = "apps/game/src/ui/challengeMenuObjectTables.generated.ts";

const ADDRS = {
  objectRecords: 0x80370f28, // 7 x 16-byte records (types 0..6)
  stateDispatch: 0x80370fa8, // PTR_FUN_80370fa8 — per-state handlers (4 entries)
  loadModelsDispatch: 0x80370fb8, // PTR_FUN_80370fb8 — per-type post-load handlers (8 slots)
  updateAnimDispatch: 0x80370fd8, // PTR_FUN_80370fd8 — per-type anim handlers (8 slots)
  floatBlock: 0x8043b370, // FLOAT_8043b370..8043b384 (6 x f32 layout/timing constants)
  timingDouble: 0x8043b388, // DOUBLE_8043b388
  blinkFloat: 0x8043b390, // FLOAT_8043b390 — blink-off alpha in update_challenge_menu_object_0
};

const OBJECT_TYPE_COUNT = 7;
const RECORD_STRIDE = 0x10;

function hex(value, width = 8) {
  return `0x${value.toString(16).padStart(width, "0")}`;
}

function runtimeToFileOffset(dol, addr) {
  for (let index = 0; index < 18; index += 1) {
    const fileOffset = dol.readUInt32BE(index * 4);
    const runtimeAddress = dol.readUInt32BE(0x48 + index * 4);
    const size = dol.readUInt32BE(0x90 + index * 4);
    if (size > 0 && addr >= runtimeAddress && addr < runtimeAddress + size) {
      return fileOffset + (addr - runtimeAddress);
    }
  }
  throw new Error(`DOL address ${hex(addr)} is outside mapped sections`);
}

function readAt(dol, addr, len) {
  const off = runtimeToFileOffset(dol, addr);
  return dol.subarray(off, off + len);
}

function readU32(buf, off) {
  return buf.readUInt32BE(off);
}

function decodePointerTable(dol, address, count) {
  const buf = readAt(dol, address, count * 4);
  return Array.from({ length: count }, (_, index) => ({
    index,
    address: hex(readU32(buf, index * 4)),
  }));
}

const dol = readFileSync(BOOT_DOL_PATH);
const bootDolSha1 = createHash("sha1").update(dol).digest("hex");

const recordsBuf = readAt(dol, ADDRS.objectRecords, OBJECT_TYPE_COUNT * RECORD_STRIDE);
const objectRecords = Array.from({ length: OBJECT_TYPE_COUNT }, (_, type) => {
  const base = type * RECORD_STRIDE;
  const modelCount = recordsBuf.readInt8(base + 8);
  return {
    type,
    modelIds: Array.from({ length: 8 }, (_, i) => recordsBuf.readInt8(base + i)),
    modelCount,
    allocKind: recordsBuf.readInt8(base + 9),
    initFn: hex(readU32(recordsBuf, base + 0xc)),
  };
});

const stateDispatch = decodePointerTable(dol, ADDRS.stateDispatch, 4);
const loadModelsDispatch = decodePointerTable(dol, ADDRS.loadModelsDispatch, 8);
const updateAnimDispatch = decodePointerTable(dol, ADDRS.updateAnimDispatch, 8);

const floatBuf = readAt(dol, ADDRS.floatBlock, 6 * 4);
const layoutFloats = Array.from({ length: 6 }, (_, i) => floatBuf.readFloatBE(i * 4));
const timingDouble = readAt(dol, ADDRS.timingDouble, 8).readDoubleBE(0);
const blinkFloat = readAt(dol, ADDRS.blinkFloat, 4).readFloatBE(0);

function toTsConst(name, value) {
  return `export const ${name} = ${JSON.stringify(value, null, 2)} as const;\n`;
}

const source = {
  bootDolPath: BOOT_DOL_PATH,
  bootDolSha1,
  evidence:
    "spawn_challenge_menu_object @0x80199b60 reads 16-byte records at DAT_80370f28 (modelIds +0..7, modelCount +8, allocKind +9, initFn +0xc); dispatch_challenge_menu_object_state @0x80199c0c uses PTR_FUN_80370fa8[state]; load_models tail-calls PTR_FUN_80370fb8[type]; update_animation uses PTR_FUN_80370fd8[type]; obj0 init/update read FLOAT_8043b370..b390 + DOUBLE_8043b388.",
  addresses: Object.fromEntries(Object.entries(ADDRS).map(([key, value]) => [key, hex(value)])),
  generatedBy: path.basename(import.meta.url),
};

const out = `// Generated by scripts/gen-challenge-menu-object-tables.mjs from user-data/GG4E/disc/sys/boot.dol.
// Do not hand-edit; rerun the generator after updating DOL/decomp evidence.

${toTsConst("CHALLENGE_MENU_OBJECT_TABLES_SOURCE", source)}
${toTsConst("CHALLENGE_MENU_OBJECT_RECORDS", objectRecords)}
${toTsConst("CHALLENGE_MENU_OBJECT_STATE_DISPATCH", stateDispatch)}
${toTsConst("CHALLENGE_MENU_OBJECT_LOAD_MODELS_DISPATCH", loadModelsDispatch)}
${toTsConst("CHALLENGE_MENU_OBJECT_UPDATE_ANIM_DISPATCH", updateAnimDispatch)}
/** DAT_803bb384 is RUNTIME state (.bss, not a DOL constant): the archive/scene id the
 * model loader reads at call time. Ports must take it from the runtime work block. */
${toTsConst("CHALLENGE_MENU_OBJECT_MODEL_ARCHIVE_ID_ADDR", "0x803bb384")}
${toTsConst("CHALLENGE_MENU_OBJECT_LAYOUT_FLOATS", layoutFloats)}
${toTsConst("CHALLENGE_MENU_OBJECT_TIMING_DOUBLE", timingDouble)}
${toTsConst("CHALLENGE_MENU_OBJECT_BLINK_FLOAT", blinkFloat)}
`;

writeFileSync(OUT_PATH, out);
console.log(`wrote ${OUT_PATH}`);
