// probe2.mjs — delta-debug one mismatching case: neutralize fields one at a time.
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
for (const s of JSON.parse(fs.readFileSync(path.join(here, "arena.json"), "utf8")).segments)
  u8.set(Buffer.from(s.b64, "base64"), s.addr >>> 0);
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

// DIFF #2 from the 20k run
const base = {"basePower":340,"att":{"borgNumber":1026,"team":2,"heroFlag":0,"pairAttack":0,"power":0.5,"maxHp":318,"hp":131,"handicap":2,"comboRank":3,"forceRatioIndex":9,"sideRank":3,"isBorg":true,"isActive":true,"slot":0},"def":{"borgNumber":262,"team":2,"heroFlag":0,"pairAttack":0,"power":1,"maxHp":448,"hp":38,"handicap":1,"comboRank":14,"forceRatioIndex":9,"sideRank":31,"isBorg":true,"isActive":true,"slot":1},"ctx":{"flagsA":0,"flagsB":16384,"attackerHpCurveIndex":3,"attackerForceCurveIndex":4,"defenderDefenseCurveSelectors":[0,3,3],"victimStatusImmune":false,"victimResistanceMask":0,"victimSpawnProtection":false,"cpuHalvingEnabled":true}};

const clone = () => JSON.parse(JSON.stringify(base));
const c0 = clone();
console.log(`full case: wasm=${run(c0)} oracle=${orc(c0)}`);

const neutralizations = [
  ["att.power=1", (c) => { c.att.power = 1; }],
  ["att.hp=maxHp=200", (c) => { c.att.hp = 200; c.att.maxHp = 200; }],
  ["att.handicap=3", (c) => { c.att.handicap = 3; }],
  ["att.sideRank=0", (c) => { c.att.sideRank = 0; }],
  ["att.forceIdx=0 (both)", (c) => { c.att.forceRatioIndex = 0; c.def.forceRatioIndex = 0; }],
  ["att.hpCurveSel=0", (c) => { c.ctx.attackerHpCurveIndex = 0; }],
  ["att.forceSel=0", (c) => { c.ctx.attackerForceCurveIndex = 0; }],
  ["type: both borg 0", (c) => { c.att.borgNumber = 0; c.def.borgNumber = 0; }],
  ["def.sideRank=0", (c) => { c.def.sideRank = 0; }],
  ["def.rankSel=0", (c) => { c.ctx.defenderDefenseCurveSelectors[0] = 0; }],
  ["def.hp=maxHp=200", (c) => { c.def.hp = 200; c.def.maxHp = 200; }],
  ["def.hpSel=0", (c) => { c.ctx.defenderDefenseCurveSelectors[1] = 0; }],
  ["def.forceSel=0", (c) => { c.ctx.defenderDefenseCurveSelectors[2] = 0; }],
  ["def.handicap=3", (c) => { c.def.handicap = 3; }],
  ["diff teams", (c) => { c.def.team = 3; }],
  ["halving off", (c) => { c.ctx.cpuHalvingEnabled = false; }],
  ["def not borg", (c) => { c.def.isBorg = false; }],
  ["att not borg", (c) => { c.att.isBorg = false; }],
];
for (const [name, mut] of neutralizations) {
  const c = clone(); mut(c);
  const w = run(c), o = orc(c);
  console.log(`${w === o ? "RESOLVED " : "persists "} ${name}: wasm=${w} oracle=${o}`);
}
