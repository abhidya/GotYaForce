// probe.mjs — one-dimensional sweeps to isolate which formula stage diverges.
// Reuses harness pieces via a tiny copy (kept standalone for clarity).
import fs from "node:fs";
import path from "node:path";
import { fileURLToPath } from "node:url";
import * as oracle from "./oracle.mjs";

const here = path.dirname(fileURLToPath(import.meta.url));
const module = await WebAssembly.compile(fs.readFileSync(path.join(here, "unit_poc.wasm")));
const instance = await WebAssembly.instantiate(module, { env: new Proxy({}, { get: () => () => 0 }) });
const ex = instance.exports;
const u8 = new Uint8Array(ex.memory.buffer);
const dv = new DataView(ex.memory.buffer);
const arena = JSON.parse(fs.readFileSync(path.join(here, "arena.json"), "utf8"));
for (const s of arena.segments) u8.set(Buffer.from(s.b64, "base64"), s.addr >>> 0);

const STRUCT30 = dv.getUint32(0x80433930, true);
const STRUCT34 = dv.getUint32(0x80433934, true);
const STRUCT50 = dv.getUint32(0x80433950, true);
const HP_MIRROR = 0x803b069c, ENERGY = 0x803b068c;
const REC = 0x80600000, ATT = 0x80601000, ATTB = 0x80602000, DEF = 0x80604000, DESC = 0x80606000;
const wU8 = (a, v) => { u8[a >>> 0] = v & 0xff; };
const wU16 = (a, v) => dv.setUint16(a >>> 0, v & 0xffff, true);
const wU32 = (a, v) => dv.setUint32(a >>> 0, v >>> 0, true);
const wF32 = (a, v) => dv.setFloat32(a >>> 0, v, true);
const wI32 = (a, v) => dv.setInt32(a >>> 0, v | 0, true);
const wI16 = (a, v) => dv.setInt16(a >>> 0, v | 0, true);

function neutralCase() {
  const actor = (slot, team) => ({
    borgNumber: 0x0000, team, heroFlag: 0, pairAttack: 0, power: 1, maxHp: 200, hp: 200,
    handicap: 3, comboRank: 0, forceRatioIndex: 0, sideRank: 0, isBorg: true, isActive: true, slot,
  });
  return {
    att: actor(0, 1), def: actor(1, 2), basePower: 500,
    ctx: {
      flagsA: 0, flagsB: 0x4000, attackerHpCurveIndex: 0, attackerForceCurveIndex: 0,
      defenderDefenseCurveSelectors: [0, 0, 0], victimStatusImmune: false,
      victimResistanceMask: 0, victimSpawnProtection: false, cpuHalvingEnabled: false,
    },
  };
}

function encodeActor(base, a, container) {
  u8.fill(0, base >>> 0, (base + 0x800) >>> 0);
  wU8(base, 1); wU8(base + 0x18, a.isActive ? 1 : 0); wU8(base + 0x83, a.isBorg ? 0 : 1);
  wU8(base + 0x88, a.team); wU16(base + 0x1c4, a.maxHp); wU8(base + 0x3e4, a.slot);
  wU8(base + 0x3e6, a.heroFlag);
  wU8(base + 0x3e8, (a.borgNumber >> 8) & 0xff); wU8(base + 0x3e9, a.borgNumber & 0xff);
  wU8(base + 0x43a, a.handicap); wU8(base + 0x6ca, a.comboRank); wU8(base + 0x6fc, a.pairAttack);
  if (container != null) wF32(container + 0xc4, a.power); else wF32(base + 0xb4, a.power);
}
function encodeCase(c) {
  u8.fill(0, REC, REC + 0x20);
  wU16(REC, c.basePower); wU8(REC + 6, c.ctx.attackerHpCurveIndex); wU8(REC + 7, c.ctx.attackerForceCurveIndex);
  wU16(REC + 0x10, c.ctx.flagsA); wU16(REC + 0x12, c.ctx.flagsB);
  u8.fill(0, ATT, ATT + 0x100); wU32(ATT + 0x90, ATTB);
  encodeActor(ATTB, c.att, ATT);
  encodeActor(DEF, c.def, null);
  wU32(DEF + 0x90, 0); wU32(DEF + 0x4ac, DESC);
  wU16(DEF + 0x59c, c.ctx.victimResistanceMask);
  wU32(DEF + 0x5e0, c.ctx.victimSpawnProtection ? 0x4000000 : 0);
  wU8(DEF + 0x71a, 1); wU32(DEF + 0x5a0, c.ctx.victimStatusImmune ? 2 : 0);
  wU8(DESC + 0x9c, c.ctx.defenderDefenseCurveSelectors[0]);
  wU8(DESC + 0x9d, c.ctx.defenderDefenseCurveSelectors[1]);
  wU8(DESC + 0x9e, c.ctx.defenderDefenseCurveSelectors[2]);
  wI16(HP_MIRROR + c.att.slot * 2, c.att.hp);
  wI16(HP_MIRROR + c.def.slot * 2, c.def.hp);
  for (const a of [c.att, c.def]) {
    wI32(STRUCT34 + a.team * 0x3c + 0x114, 3200);
    wI32(ENERGY + a.team * 4, (32 - a.forceRatioIndex) * 100);
    wU8(STRUCT50 + a.team, a.sideRank);
  }
  wU8(STRUCT30 + 0x32, c.ctx.cpuHalvingEnabled ? 0 : 2);
  wU8(STRUCT34 + 0x1f, 0);
}
const run = (c) => { encodeCase(c); return ex.zz_003cd5c_(REC, ATT, DEF) | 0; };
const orc = (c) => oracle.computeBaseDamage(c.att, c.def, c.basePower, c.ctx);

const sweeps = [
  ["att.sideRank", (c, v) => { c.att.sideRank = v; }, 32],
  ["att.hp(50..200)", (c, v) => { c.att.hp = 50 + Math.floor(v * 4.6); }, 32],
  ["att.hpCurveSel", (c, v) => { c.ctx.attackerHpCurveIndex = v % 8; }, 8],
  ["att.forceIdx", (c, v) => { c.att.forceRatioIndex = v; c.def.forceRatioIndex = 0; }, 32],
  ["att.forceSel", (c, v) => { c.ctx.attackerForceCurveIndex = v % 8; }, 8],
  ["att.handicap", (c, v) => { c.att.handicap = v % 7; }, 7],
  ["att.power", (c, v) => { c.att.power = [0.5, 1, 1.5, 2][v % 4]; }, 4],
  ["att.pair", (c, v) => { c.att.pairAttack = v % 2; }, 2],
  ["att.hero", (c, v) => { c.att.heroFlag = v % 2; }, 2],
  ["type(att 0x200|def 0x300)", (c, v) => { c.att.borgNumber = 0x200 + (v % 8); c.def.borgNumber = 0x300 + (v % 4); }, 8],
  ["def.sideRank", (c, v) => { c.def.sideRank = v; }, 32],
  ["def.rankSel", (c, v) => { c.ctx.defenderDefenseCurveSelectors[0] = v % 8; }, 8],
  ["def.hp(50..200)", (c, v) => { c.def.hp = 50 + Math.floor(v * 4.6); }, 32],
  ["def.hpSel", (c, v) => { c.ctx.defenderDefenseCurveSelectors[1] = v % 8; }, 8],
  ["def.forceIdx", (c, v) => { c.def.forceRatioIndex = v; c.att.forceRatioIndex = 0; }, 32],
  ["def.forceSel", (c, v) => { c.ctx.defenderDefenseCurveSelectors[2] = v % 8; }, 8],
  ["def.handicap", (c, v) => { c.def.handicap = v % 7; }, 7],
  ["def.power", (c, v) => { c.def.power = [0.5, 1, 1.5, 2][v % 4]; }, 4],
  ["def.pair", (c, v) => { c.def.pairAttack = v % 2; }, 2],
  ["def.hero", (c, v) => { c.def.heroFlag = v % 2; }, 2],
  ["def.combo(flagsB=0)", (c, v) => { c.ctx.flagsB = 0; c.def.comboRank = v % 16; }, 16],
  ["sameTeam", (c, v) => { c.def.team = v % 2 ? c.att.team : 2; c.def.forceRatioIndex = c.att.forceRatioIndex; }, 2],
  ["guard", (c, v) => { c.ctx.flagsA = v % 2 ? 0x1000 : 0; c.ctx.victimResistanceMask = 0x1000; }, 2],
  ["cpuHalve(att t0 hero)", (c, v) => { c.ctx.cpuHalvingEnabled = !!(v % 2); c.att.team = 0; c.att.heroFlag = 1; c.def.forceRatioIndex = 0; }, 2],
  ["basePower", (c, v) => { c.basePower = 1 + v * 31; }, 32],
];
for (const [name, set, n] of sweeps) {
  let bad = 0; const ex1 = [];
  for (let v = 0; v < n; v++) {
    const c = neutralCase(); set(c, v);
    const w = run(c), o = orc(c);
    if (w !== o) { bad++; if (ex1.length < 4) ex1.push(`v=${v}:${w}vs${o}`); }
  }
  console.log(`${bad ? "MISMATCH" : "ok      "} ${name}  ${bad}/${n}  ${ex1.join(" ")}`);
}
