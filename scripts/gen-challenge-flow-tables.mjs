#!/usr/bin/env node
// Dumps the GG4E Challenge-flow data tables + dispatch tables straight from boot.dol.
// Mirrors the DOL-reader pattern in scripts/gen-title-intro-script.mjs. Output is
// consumed by apps/game/src/ui/challengeFlowTables.generated.ts (written below).
//
// Evidence: dispatch_challenge_flow_state @0x80195f2c reads PTR_FUN_8036f560[mode];
// poll_challenge_menu_selection @0x80196030 reads DAT_804356d0 + DAT_8036f554;
// build_challenge_battle_setup @0x801962c4 reads the PTR_DAT_8036f40c/f434/f3e4/
// f4b8/f53c pointer arrays; zz_0196dac_ @0x80196dac reads DAT_8036f548 (11-byte).
import { createHash } from "node:crypto";
import { readFileSync, writeFileSync } from "node:fs";
import path from "node:path";

const BOOT_DOL_PATH = "user-data/GG4E/disc/sys/boot.dol";
const OUT_PATH = "apps/game/src/ui/challengeFlowTables.generated.ts";

const ADDRS = {
  // Function-pointer dispatch tables.
  flowModeDispatch: 0x8036f560, // PTR_FUN_8036f560 — main Challenge-flow mode table (8 entries)
  flowSubDispatch: 0x8036f580, // PTR_FUN_8036f580 — sub-dispatch in FUN_8019688c
  actorActionDispatch: 0x8036f5a8, // PTR_FUN_8036f5a8 — actor action dispatch (FUN_8019713c)
  // Byte/word data tables.
  challengeTypeList: 0x8036f548, // DAT_8036f548 — 11-byte stage-id rotation pool (st00..st0e)
  startForceEnergy: 0x8036f554, // DAT_8036f554 — per-difficulty start force energy (3 x u32)
  battleCountByDifficulty: 0x804356d0, // DAT_804356d0 — total battles per difficulty (5/10/15)
  stageIdPairByDifficulty: 0x804356e4, // DAT_804356e4 — per-difficulty stage id pair (-> PTR_DAT_80433950)
  slotFlagByDifficulty: 0x804356ec, // DAT_804356ec — per-difficulty side flag byte (-> work+0x32)
  stageStructA: 0x804356f4, // DAT_804356f4 — referenced by FUN_80196b1c (DAT_803c1150)
  stageStructB: 0x804356fc, // DAT_804356fc — referenced by FUN_80196b1c (DAT_803c115c)
  sceneObjStruct: 0x8036f58c, // DAT_8036f58c — referenced by FUN_80196b1c (DAT_803c1140)
  // Pointer arrays (3 pointers each, one per difficulty) into battle-roster tables.
  // From build_challenge_battle_setup @0x801962c4: local_60[2]/[3]/[0]/[1] read these as
  // side count (char) / budget (int); pool groups read 4 bytes per battle (battleIdx*4+rand%4).
  allyCountByBattle: 0x8036f40c, // PTR_DAT_8036f40c — [diff] -> char[battle] ally count (local_60[2])
  enemyCountByBattle: 0x8036f434, // PTR_DAT_8036f434 — [diff] -> char[battle] enemy count (local_60[3])
  allyBudgetByBattle: 0x8036f4b8, // PTR_DAT_8036f4b8 — [diff] -> int[battle] ally budget (local_60[0])
  enemyBudgetByBattle: 0x8036f53c, // PTR_DAT_8036f53c — [diff] -> int[battle] enemy budget (local_60[1])
  allyPoolGroupTable: 0x8036f360, // PTR_DAT_8036f360 — [diff] -> char[battle*4] ally pool group id
  enemyPoolGroupTable: 0x8036f3e4, // PTR_DAT_8036f3e4 — [diff] -> char[battle*4] enemy pool group id
};

const DIFFICULTY_COUNT = 3;

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

function readU16(buf, off) {
  return buf.readUInt16BE(off);
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

function decodeBytes(dol, address, count) {
  return Array.from(readAt(dol, address, count));
}

function decodeU32Array(dol, address, count) {
  const buf = readAt(dol, address, count * 4);
  return Array.from({ length: count }, (_, i) => readU32(buf, i * 4));
}

// Follow a 3-pointer array; each pointer targets a stride-`stride` row. The row length is
// per-difficulty (`countFor(diff)` entries) — normal/tuff/insane have 5/10/15 battles, so a
// fixed read would bleed into adjacent tables. Returns the raw pointer + the probed row.
function decodeDifficultyPointerRows(dol, tableAddr, stride, countFor, asWords) {
  const ptrBuf = readAt(dol, tableAddr, DIFFICULTY_COUNT * 4);
  return Array.from({ length: DIFFICULTY_COUNT }, (_, diff) => {
    const ptr = readU32(ptrBuf, diff * 4);
    const cols = countFor(diff);
    const row = [];
    if (ptr !== 0) {
      const buf = readAt(dol, ptr, cols * stride);
      for (let c = 0; c < cols; c += 1) {
        row.push(asWords ? readU32(buf, c * stride) : buf[c * stride]);
      }
    }
    return { difficulty: diff, pointer: hex(ptr), row };
  });
}

const dol = readFileSync(BOOT_DOL_PATH);
const bootDolSha1 = createHash("sha1").update(dol).digest("hex");

const flowModeDispatch = decodePointerTable(dol, ADDRS.flowModeDispatch, 8);
const flowSubDispatch = decodePointerTable(dol, ADDRS.flowSubDispatch, 4);
const actorActionDispatch = decodePointerTable(dol, ADDRS.actorActionDispatch, 8);

const challengeTypeList = decodeBytes(dol, ADDRS.challengeTypeList, 0x0b);
const startForceEnergy = decodeU32Array(dol, ADDRS.startForceEnergy, DIFFICULTY_COUNT);
const battleCountByDifficulty = decodeBytes(dol, ADDRS.battleCountByDifficulty, DIFFICULTY_COUNT);
const stageIdPairByDifficulty = decodeBytes(dol, ADDRS.stageIdPairByDifficulty, DIFFICULTY_COUNT * 2);
const slotFlagByDifficulty = decodeBytes(dol, ADDRS.slotFlagByDifficulty, DIFFICULTY_COUNT * 2);
const stageStructA = decodeBytes(dol, ADDRS.stageStructA, 8);
const stageStructB = decodeBytes(dol, ADDRS.stageStructB, 8);
const sceneObjStruct = decodeU32Array(dol, ADDRS.sceneObjStruct, 4);

const battleCountFor = (diff) => battleCountByDifficulty[diff] ?? 0;

const allyCountByBattle = decodeDifficultyPointerRows(dol, ADDRS.allyCountByBattle, 1, battleCountFor, false);
const enemyCountByBattle = decodeDifficultyPointerRows(dol, ADDRS.enemyCountByBattle, 1, battleCountFor, false);
const allyBudgetByBattle = decodeDifficultyPointerRows(dol, ADDRS.allyBudgetByBattle, 4, battleCountFor, true);
const enemyBudgetByBattle = decodeDifficultyPointerRows(dol, ADDRS.enemyBudgetByBattle, 4, battleCountFor, true);
const allyPoolGroupTable = decodeDifficultyPointerRows(dol, ADDRS.allyPoolGroupTable, 1, (d) => battleCountFor(d) * 4, false);
const enemyPoolGroupTable = decodeDifficultyPointerRows(dol, ADDRS.enemyPoolGroupTable, 1, (d) => battleCountFor(d) * 4, false);

function toTsConst(name, value) {
  return `export const ${name} = ${JSON.stringify(value, null, 2)} as const;\n`;
}

const source = {
  bootDolPath: BOOT_DOL_PATH,
  bootDolSha1,
  evidence:
    "dispatch_challenge_flow_state @0x80195f2c dispatches via PTR_FUN_8036f560[mode]; poll_challenge_menu_selection @0x80196030 reads DAT_804356d0 + DAT_8036f554; build_challenge_battle_setup @0x801962c4 reads the PTR_DAT_8036f40c/f434/f3e4/f4b8/f53c pointer arrays; zz_0196dac_ @0x80196dac reads DAT_8036f548 (11-byte).",
  addresses: Object.fromEntries(Object.entries(ADDRS).map(([key, value]) => [key, hex(value)])),
  generatedBy: path.basename(import.meta.url),
};

const out = `// Generated by scripts/gen-challenge-flow-tables.mjs from user-data/GG4E/disc/sys/boot.dol.
// Do not hand-edit; rerun the generator after updating DOL/decomp evidence.

${toTsConst("CHALLENGE_FLOW_TABLES_SOURCE", source)}
${toTsConst("CHALLENGE_FLOW_MODE_DISPATCH", flowModeDispatch)}
${toTsConst("CHALLENGE_FLOW_SUB_DISPATCH", flowSubDispatch)}
${toTsConst("CHALLENGE_ACTOR_ACTION_DISPATCH", actorActionDispatch)}
${toTsConst("CHALLENGE_TYPE_LIST", challengeTypeList)}
${toTsConst("CHALLENGE_START_FORCE_ENERGY", startForceEnergy)}
${toTsConst("CHALLENGE_BATTLE_COUNT_BY_DIFFICULTY", battleCountByDifficulty)}
${toTsConst("CHALLENGE_STAGE_ID_PAIR_BY_DIFFICULTY", stageIdPairByDifficulty)}
${toTsConst("CHALLENGE_SLOT_FLAG_BY_DIFFICULTY", slotFlagByDifficulty)}
${toTsConst("CHALLENGE_STAGE_STRUCT_A", stageStructA)}
${toTsConst("CHALLENGE_STAGE_STRUCT_B", stageStructB)}
${toTsConst("CHALLENGE_SCENE_OBJ_STRUCT", sceneObjStruct)}
${toTsConst("CHALLENGE_ALLY_COUNT_BY_BATTLE", allyCountByBattle)}
${toTsConst("CHALLENGE_ENEMY_COUNT_BY_BATTLE", enemyCountByBattle)}
${toTsConst("CHALLENGE_ALLY_BUDGET_BY_BATTLE", allyBudgetByBattle)}
${toTsConst("CHALLENGE_ENEMY_BUDGET_BY_BATTLE", enemyBudgetByBattle)}
${toTsConst("CHALLENGE_ALLY_POOL_GROUP_TABLE", allyPoolGroupTable)}
${toTsConst("CHALLENGE_ENEMY_POOL_GROUP_TABLE", enemyPoolGroupTable)}
`;

writeFileSync(OUT_PATH, out);
console.log(`wrote ${OUT_PATH}`);
