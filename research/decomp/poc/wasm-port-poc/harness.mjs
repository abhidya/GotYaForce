#!/usr/bin/env node
// harness.mjs — POC §5 oracle diff (HANDOFF-2026-08-09).
// Drives the wasm build of the VERBATIM Ghidra C (zz_003cd5c_ / zz_003d344_ /
// zz_0066298_ / FUN_80031634) and the known-good TS oracle (sourceDamage.ts,
// esbuild-bundled to oracle.mjs) with the SAME input corpus, then diffs outputs.
import fs from "node:fs";
import path from "node:path";
import { fileURLToPath } from "node:url";
import { createHash } from "node:crypto";
import * as oracle from "./oracle.mjs";

// POC_DUMP_CORPUS=<path> — one-time audited corpus-dump hook (oracle-workstream-plan.md
// §6 Phase 1, invariant I-7's sole sanctioned PoC amendment). When set, every generated
// input (and the classification outcome per main-corpus case) is serialized to <path>
// as JSONL, with a fixture header record binding the dump to this file, the wasm, the
// arena, and the committed damage-core oracle.log. The hook is append-only observation:
// it consumes no PRNG draws, writes nothing to stdout, and touches no generation logic.
// Non-interference proof: an instrumented run must reproduce the committed oracle.log
// byte-for-byte before the dump is trusted.
const dumpPath = process.env.POC_DUMP_CORPUS ?? null;
const dumpRecords = dumpPath ? [] : null;
const dump = (r) => { if (dumpRecords) dumpRecords.push(JSON.stringify(r)); };

const here = path.dirname(fileURLToPath(import.meta.url));
const root = path.resolve(here, "..", "..", "..", "..");
const formulaData = JSON.parse(
  fs.readFileSync(path.join(root, "packages", "combat", "src", "data", "damageFormula.json"), "utf8"),
);

// ---------------------------------------------------------------------------
// wasm module + arena
// ---------------------------------------------------------------------------
const shimCounts = {};
const count = (name) => { shimCounts[name] = (shimCounts[name] ?? 0) + 1; };

let mem, u8, dv;
const f32buf = new Float32Array(1);
const fr = (x) => { f32buf[0] = x; return f32buf[0]; }; // fround via typed array

// SDK shims (design stage 1: gnt4_PS* are TS/JS imports, never ported).
// Vector ops in single precision (paired-single hardware), dot returned as double.
// NOTE: wasm i32 args arrive in JS as SIGNED ints; arena addresses are >= 0x80000000,
// so every pointer must be unsigned (>>> 0) before use.
const sdkShims = {
  gnt4_PSVECSubtract_bl: (a, b, out) => {
    count("gnt4_PSVECSubtract_bl");
    a >>>= 0; b >>>= 0; out >>>= 0;
    for (let i = 0; i < 3; i++) dv.setFloat32(out + i * 4, fr(dv.getFloat32(a + i * 4, true) - dv.getFloat32(b + i * 4, true)), true);
  },
  gnt4_PSVECAdd_bl: (a, b, out) => {
    count("gnt4_PSVECAdd_bl");
    a >>>= 0; b >>>= 0; out >>>= 0;
    for (let i = 0; i < 3; i++) dv.setFloat32(out + i * 4, fr(dv.getFloat32(a + i * 4, true) + dv.getFloat32(b + i * 4, true)), true);
  },
  gnt4_PSQUATDotProduct_bl: (a, b) => {
    count("gnt4_PSQUATDotProduct_bl");
    a >>>= 0; b >>>= 0;
    let s = 0;
    for (let i = 0; i < 3; i++) s = fr(s + fr(dv.getFloat32(a + i * 4, true) * dv.getFloat32(b + i * 4, true)));
    return s;
  },
  gnt4_PSQUATScale_bl: (s, v, out) => {
    count("gnt4_PSQUATScale_bl");
    v >>>= 0; out >>>= 0;
    for (let i = 0; i < 3; i++) dv.setFloat32(out + i * 4, fr(fr(s) * dv.getFloat32(v + i * 4, true)), true);
  },
};

const wasmBytes = fs.readFileSync(process.env.POC_WASM ?? path.join(here, "unit_poc.wasm"));
const module = await WebAssembly.compile(wasmBytes);
const neededImports = WebAssembly.Module.imports(module).map((i) => `${i.module}.${i.name}`);
const instance = await WebAssembly.instantiate(module, {
  env: new Proxy(sdkShims, {
    get: (t, k) => t[k] ?? ((...a) => { throw new Error(`unshimmed import ${String(k)}(${a})`); }),
  }),
});
const ex = instance.exports;
mem = ex.memory;
u8 = new Uint8Array(mem.buffer);
dv = new DataView(mem.buffer);
console.log(`wasm loaded: memory ${(mem.buffer.byteLength / 1048576).toFixed(0)} MiB, imports: ${neededImports.join(", ") || "(none)"}`);

// apply arena (DOL-sourced, byte-order converted at generation time)
const arena = JSON.parse(fs.readFileSync(path.join(here, "arena.json"), "utf8"));
for (const s of arena.segments) u8.set(Buffer.from(s.b64, "base64"), s.addr >>> 0);

// resolve the DOL-initialized runtime-struct pointers
const STRUCT30 = dv.getUint32(0x80433930, true); // [0x32] challenge-mode byte
const STRUCT34 = dv.getUint32(0x80433934, true); // [team*0x3c+0x114] energy max (i32)
const STRUCT50 = dv.getUint32(0x80433950, true); // [team] side-rank byte
const HP_MIRROR = 0x803b069c;                    // s16[slot]
const ENERGY = 0x803b068c;                       // i32[team]

// scratch objects (free region above all DOL/bss sections)
const REC = 0x80600000, ATT = 0x80601000, ATTB = 0x80602000, DEF = 0x80604000, DESC = 0x80606000;

// ---------------------------------------------------------------------------
// corpus generation (seeded, oracle-domain) + memory encoding
// ---------------------------------------------------------------------------
function mulberry32(seed) {
  return () => {
    seed |= 0; seed = (seed + 0x6d2b79f5) | 0;
    let t = Math.imul(seed ^ (seed >>> 15), 1 | seed);
    t = (t + Math.imul(t ^ (t >>> 7), 61 | t)) ^ t;
    return ((t ^ (t >>> 14)) >>> 0) / 4294967296;
  };
}
const rnd = mulberry32(0x6f42);
const ri = (n) => Math.floor(rnd() * n);
const pick = (a) => a[ri(a.length)];

const remap = JSON.parse(fs.readFileSync(path.join(root, "research", "decomp", "data", "type-category-remap-802f2e28.json"), "utf8"));
const remapRows = remap.rows ?? remap.table ?? remap;
const D = formulaData;
const counts = {
  attHp: D.attackerHpCurves_804335e8.map((s) => s.curves.length),
  attForce: D.attackerForceCurves_804335f0.map((s) => s.curves.length),
  defRank: D.defenseRankCurves_80433600.map((s) => s.curves.length),
  defHp: D.defenderHpCurves_80433608.map((s) => s.curves.length),
  defForce: D.defenderForceCurves_80433610.map((s) => s.curves.length),
};

function randBorgNumber() {
  const family = ri(16);
  const row = Array.isArray(remapRows) ? remapRows[family] : null;
  const variant = row?.length ? ri(row.length) : ri(4);
  return ((family << 8) | variant) & 0xffff;
}

function randActor(slot) {
  return {
    borgNumber: randBorgNumber(), team: ri(4), heroFlag: ri(3) === 0 ? 1 : 0,
    pairAttack: ri(4) === 0 ? 1 : 0, power: pick([1, 1, 1, 0.5, 1.5, 2]),
    maxHp: 50 + ri(450), hp: 0, handicap: ri(7), comboRank: ri(16),
    forceRatioIndex: ri(32), sideRank: ri(32),
    isBorg: ri(10) !== 0, isActive: ri(10) !== 0, slot,
  };
}

function randCase(i) {
  const att = randActor(0), def = randActor(1);
  // hp <= maxHp: the source's real domain. For hp>maxHp (impossible in-game) the ROM
  // computes a NEGATIVE curve index and reads out of table bounds; the oracle clamps.
  // maxHp up to 500 still exercises the >=201 skip branch on both sides.
  att.hp = 1 + ri(att.maxHp);
  def.hp = 1 + ri(def.maxHp);
  if (att.team === def.team) {
    // side energy AND side rank are per-team state (one slot per team in bss);
    // same-team actors must agree or the oracle receives an impossible input.
    def.forceRatioIndex = att.forceRatioIndex;
    def.sideRank = att.sideRank;
  }
  const heroA = att.heroFlag ? 1 : 0, heroD = def.heroFlag ? 1 : 0;
  return {
    n: i, att, def, basePower: 1 + ri(999),
    ctx: {
      flagsA: ri(3) === 0 ? 0x1000 : 0, flagsB: ri(3) === 0 ? 0x4000 : 0,
      attackerHpCurveIndex: ri(counts.attHp[heroA]),
      attackerForceCurveIndex: ri(counts.attForce[heroA]),
      defenderDefenseCurveSelectors: [ri(counts.defRank[heroD]), ri(counts.defHp[heroD]), ri(counts.defForce[heroD])],
      // ROM gates immunity + /40 guard on defender[0x83]==0 (is a borg); the ctx
      // flags are caller-derived FROM the borg, so non-borg defenders never carry them.
      victimStatusImmune: def.isBorg && ri(12) === 0,
      victimResistanceMask: def.isBorg && ri(3) === 0 ? 0x1000 : 0,
      victimSpawnProtection: ri(12) === 0, cpuHalvingEnabled: ri(2) === 0,
    },
  };
}

const wU8 = (a, v) => { u8[a >>> 0] = v & 0xff; };
const wU16 = (a, v) => dv.setUint16(a >>> 0, v & 0xffff, true);
const wU32 = (a, v) => dv.setUint32(a >>> 0, v >>> 0, true);
const wF32 = (a, v) => dv.setFloat32(a >>> 0, v, true);
const wI32 = (a, v) => dv.setInt32(a >>> 0, v | 0, true);
const wI16 = (a, v) => dv.setInt16(a >>> 0, v | 0, true);

function encodeActor(base, a, { container } = {}) {
  u8.fill(0, base >>> 0, (base + 0x800) >>> 0);
  wU8(base + 0x00, 1);
  wU8(base + 0x18, a.isActive ? 1 : 0);
  wU8(base + 0x83, a.isBorg ? 0 : 1);
  wU8(base + 0x88, a.team);
  wU16(base + 0x1c4, a.maxHp);
  wU8(base + 0x3e4, a.slot);
  wU8(base + 0x3e6, a.heroFlag);
  // +0x3e8 borgNumber: PPC big-endian byte order preserved at the data boundary
  wU8(base + 0x3e8, (a.borgNumber >> 8) & 0xff); // family
  wU8(base + 0x3e9, a.borgNumber & 0xff);        // variant
  wU8(base + 0x43a, a.handicap);
  wU8(base + 0x6ca, a.comboRank);
  wU8(base + 0x6fc, a.pairAttack);
  if (container != null) wF32(container + 0xc4, a.power);
  else wF32(base + 0xb4, a.power);
}

function encodeCase(c) {
  // record
  u8.fill(0, REC, REC + 0x20);
  wU16(REC + 0x00, c.basePower);
  wU8(REC + 0x06, c.ctx.attackerHpCurveIndex);
  wU8(REC + 0x07, c.ctx.attackerForceCurveIndex);
  wU16(REC + 0x10, c.ctx.flagsA);
  wU16(REC + 0x12, c.ctx.flagsB);
  // attacker container -> borg sub-object
  u8.fill(0, ATT, ATT + 0x100);
  wU32(ATT + 0x90, ATTB);
  encodeActor(ATTB, c.att, { container: ATT });
  // defender: param_3 IS the borg (+0x90 null -> resolution keeps param_3)
  encodeActor(DEF, c.def, {});
  wU32(DEF + 0x90, 0);
  wU32(DEF + 0x4ac, DESC);
  wU16(DEF + 0x59c, c.ctx.victimResistanceMask);
  wU32(DEF + 0x5e0, c.ctx.victimSpawnProtection ? 0x4000000 : 0);
  wU8(DEF + 0x71a, 1);
  wU32(DEF + 0x5a0, c.ctx.victimStatusImmune ? (1 << 1) : 0);
  wU8(DESC + 0x9c, c.ctx.defenderDefenseCurveSelectors[0]);
  wU8(DESC + 0x9d, c.ctx.defenderDefenseCurveSelectors[1]);
  wU8(DESC + 0x9e, c.ctx.defenderDefenseCurveSelectors[2]);
  // bss live state
  wI16(HP_MIRROR + c.att.slot * 2, c.att.hp);
  wI16(HP_MIRROR + c.def.slot * 2, c.def.hp);
  for (const a of [c.att, c.def]) {
    wI32(STRUCT34 + a.team * 0x3c + 0x114, 3200);
    wI32(ENERGY + a.team * 4, (32 - a.forceRatioIndex) * 100);
    wU8(STRUCT50 + a.team, a.sideRank);
  }
  wU8(STRUCT30 + 0x32, c.ctx.cpuHalvingEnabled ? ri(2) : 2);
  wU8(STRUCT34 + 0x1f, 0);
}

// ---------------------------------------------------------------------------
// oracle32 — float32-faithful reference used ONLY to classify diffs.
// Mirrors zz_003cd5c_'s exact float/double op structure (fround at every point
// the source performs a single-precision op or (float) cast). If wasm == oracle32
// on a diff case, the wasm/oracle divergence is PPC-float32-vs-JS-float64 rounding,
// not a semantic difference.
// ---------------------------------------------------------------------------
// Tables are fround()ed: the DOL stores f32 bit values; damageFormula.json stores
// decimal-shortened doubles (1.02 vs f32(1.02)) — the ROM's true multiplier is the f32.
const flat = (sets, hero, i) => fr(sets[hero].values[i]);
const curveT = (sets, hero, sel, i) => fr(sets[hero].curves[sel][i]);
const hpIdx = (hp, maxHp) => {
  const den = maxHp < 200 ? maxHp : 200;
  let i = 32 - Math.trunc((hp * 32) / den);
  return i > 31 ? 31 : i;
};
function oracle32(c) {
  const { att, def, basePower: bp, ctx } = c;
  if (!(bp > 0)) return 0;
  if (ctx.victimStatusImmune) return 0;
  const hA = att.heroFlag ? 1 : 0, hD = def.heroFlag ? 1 : 0;
  const D2 = formulaData;
  let d = fr(fr(bp) + fr(fr(fr(bp) * 0.5) * fr(att.power - 1)));
  if (att.isBorg && att.isActive) {
    if (att.pairAttack) d = fr(d * 2);
    let f = fr(d * flat(D2.attackRankBySideRank_804335e0, hA, att.sideRank));
    if (ctx.cpuHalvingEnabled && att.heroFlag && att.team === 0) f = fr(0.5 * f);
    if (att.hp < 201) f = fr(f * curveT(D2.attackerHpCurves_804335e8, hA, ctx.attackerHpCurveIndex, hpIdx(att.hp, att.maxHp)));
    d = fr(fr(f * curveT(D2.attackerForceCurves_804335f0, hA, ctx.attackerForceCurveIndex, att.forceRatioIndex)) *
           flat(D2.attackHandicap_804335f8, hA, att.handicap));
    if (def.isBorg && def.isActive) d = fr(d * oracle.typeMultiplier(att.borgNumber, def.borgNumber));
  }
  if (def.isBorg && def.isActive) {
    if (def.pairAttack) d = fr(d * 0.5);
    const sel = ctx.defenderDefenseCurveSelectors;
    let f = fr(d * curveT(D2.defenseRankCurves_80433600, hD, sel[0], def.sideRank));
    if (ctx.cpuHalvingEnabled && def.heroFlag && def.team === 0) f = fr(0.5 * f);
    f = fr(f * fr(1 / fr(1 + fr(0.5 * fr(def.power - 1)))));
    const postHit = Math.max(0, (def.hp - bp) << 16 >> 16);
    if (postHit < 201) f = fr(f * curveT(D2.defenderHpCurves_80433608, hD, sel[1], hpIdx(postHit, def.maxHp)));
    d = fr(fr(f * curveT(D2.defenderForceCurves_80433610, hD, sel[2], def.forceRatioIndex)) *
           flat(D2.defenseHandicap_80433618, hD, def.handicap));
    if ((ctx.flagsB & 0x4000) === 0) d = fr(d * D2.comboRankScale_802c7ca0[def.comboRank]);
    if (ctx.victimSpawnProtection) d = fr(d * 0.5);
  }
  if (att.team === def.team && (ctx.flagsA & 0x1000) === 0) d = fr(d * 0.25);
  if ((ctx.flagsA & 0x1000) !== 0 && (ctx.victimResistanceMask & 0x1000) !== 0) d = fr(d / 40);
  if (d < 1) d = 1;
  return Math.trunc(d);
}

// ---------------------------------------------------------------------------
// Unit A diff: zz_003cd5c_ vs computeBaseDamage
// ---------------------------------------------------------------------------
const N = Number(process.argv[2] ?? 20000);
let match = 0, roundingExplained = 0;
const unexplained = [];
for (let i = 0; i < N; i++) {
  const c = randCase(i);
  encodeCase(c);
  const w = ex.zz_003cd5c_(REC, ATT, DEF) | 0;
  const o = oracle.computeBaseDamage(c.att, c.def, c.basePower, c.ctx);
  let cls; // dump-only classification mirror; oracle32 is pure (no PRNG), so the extra call cannot perturb generation
  if (w === o) { match++; cls = "exact"; }
  else if (oracle32(c) === w) { roundingExplained++; cls = "rounding"; }
  else { if (unexplained.length < 8) unexplained.push({ n: i, wasm: w, oracle: o, o32: oracle32(c), case: c }); cls = "unexplained"; }
  dump({ kind: "case", n: i, att: c.att, def: c.def, basePower: c.basePower, ctx: c.ctx });
  dump({ kind: "class", n: i, class: cls });
}
console.log(`\nUnit A [zz_003cd5c_ damage formula]  corpus=${N}`);
console.log(`  exact match vs f64 oracle          : ${match}/${N} (${((match / N) * 100).toFixed(3)}%)`);
console.log(`  f32-rounding-explained (wasm==o32) : ${roundingExplained}`);
console.log(`  UNEXPLAINED                        : ${N - match - roundingExplained}`);
for (const d of unexplained) console.log(`  DIFF #${d.n}: wasm=${d.wasm} oracle=${d.oracle} oracle32=${d.o32} ${JSON.stringify({ bp: d.case.basePower, att: d.case.att, def: d.case.def, ctx: d.case.ctx })}`);

// zz_0066298_ vs lookupTypeCategory over the whole borg space
let catMatch = 0, catTotal = 0;
const CAT = 0x80608000;
for (let family = 0; family < 16; family++) {
  const row = Array.isArray(remapRows) ? remapRows[family] : [];
  for (let variant = 0; variant < (row?.length ?? 0); variant++) {
    wU8(CAT, family); wU8(CAT + 1, variant);
    dump({ kind: "cat", family, variant });
    const w = ex.zz_0066298_(CAT) | 0;
    const o = oracle.lookupTypeCategory((family << 8) | variant);
    catTotal++; if (w === o) catMatch++;
    else if (catTotal - catMatch < 6) console.log(`  CAT DIFF fam=${family} var=${variant}: wasm=${w} oracle=${o}`);
  }
}
console.log(`  type category (zz_0066298_): ${catMatch}/${catTotal} exact`);

// zz_003d344_ vs applyHpDamage
let hpMatch = 0;
const HPN = 4000;
for (let i = 0; i < HPN; i++) {
  const maxHp = 1 + ri(500), hp = ri(maxHp + 50), amount = ri(600) - 100;
  dump({ kind: "hp", n: i, maxHp, hp, amount });
  u8.fill(0, DEF, DEF + 0x800);
  wU16(DEF + 0x1c4, maxHp); wI16(DEF + 0x1c6, hp); wU8(DEF + 0x83, 0); wU8(DEF + 0x4a0, 0);
  wU8(STRUCT34 + 0x1f, 0);
  const lethal = ex.zz_003d344_(DEF, amount) | 0;
  const t = { hp, maxHp, prevHp: undefined };
  oracle.applyHpDamage(t, amount);
  const wHp = dv.getInt16(DEF + 0x1c6, true), wPrev = dv.getInt16(DEF + 0x1c8, true);
  const oPrev = t.prevHp ?? 0;
  if (wHp === t.hp && wPrev === oPrev && lethal === (hp !== 0 && t.hp === 0 ? 1 : 0)) hpMatch++;
  else if (HPN - hpMatch < 6) console.log(`  HP DIFF hp=${hp} max=${maxHp} amt=${amount}: wasm=${wHp}/${wPrev}/${lethal} oracle=${t.hp}/${oPrev}`);
}
console.log(`  hp subtract+clamp (zz_003d344_): ${hpMatch}/${HPN} exact (incl. lethal flag)`);

// ---------------------------------------------------------------------------
// Unit B: FUN_80031634 through the SDK seam vs a JS reference
// ---------------------------------------------------------------------------
const B1 = 0x80609000, B2 = 0x8060a000, B3 = 0x8060b000, B4 = 0x8060c000;
const jsRef = (p1, p2, p3, p4idx) => {
  const rd = (a) => dv.getFloat32(a >>> 0, true);
  const chTab = (i) => (u8[0x802cffc8 + i] << 24) >> 24;
  const vsub = (a, b) => [fr(rd(a) - rd(b)), fr(rd(a + 4) - rd(b + 4)), fr(rd(a + 8) - rd(b + 8))];
  const vsubv = (a, v) => [fr(rd(a) - v[0]), fr(rd(a + 4) - v[1]), fr(rd(a + 8) - v[2])];
  const dotv = (v, b) => fr(fr(fr(fr(v[0] * rd(b)) ) + fr(v[1] * rd(b + 4))) + fr(v[2] * rd(b + 8)));
  const corner = p1 + chTab(p4idx * 4) * 0xc + 0x30;
  const normal = p1 + p4idx * 0x18 + 0x90;
  const d1 = dotv(vsub(p3, corner), normal);
  const d2 = dotv(vsub(p3 + 12, corner), normal);
  const a1 = Math.abs(fr(d1)), a2 = Math.abs(fr(d2));
  const dMin = Math.min(a1, a2);
  const hit = dMin <= rd(p2 + 0x30);
  let out = null;
  if (hit) {
    const scaled = [fr(fr(dMin) * rd(normal)), fr(fr(dMin) * rd(normal + 4)), fr(fr(dMin) * rd(normal + 8))];
    out = vsubv(p3 + (a2 < a1 ? 12 : 0), scaled);
  }
  return { hit, out };
};
let bMatch = 0;
const BN = 2000;
const shimBase = Object.values(shimCounts).reduce((a, b) => a + b, 0);
for (let i = 0; i < BN; i++) {
  for (let k = 0; k < 0x200; k += 4) wF32(B1 + k, (rnd() - 0.5) * 100);
  wF32(B2 + 0x30, rnd() * 20);
  for (let k = 0; k < 24; k += 4) wF32(B3 + k, (rnd() - 0.5) * 100);
  const idx = ri(6);
  wI32(B4, idx);
  dump({
    kind: "unitb", n: i, idx,
    b1: Buffer.from(mem.buffer, B1 >>> 0, 0x200).toString("base64"),
    b2_30: Buffer.from(mem.buffer, (B2 + 0x30) >>> 0, 4).toString("base64"),
    b3: Buffer.from(mem.buffer, B3 >>> 0, 24).toString("base64"),
  });
  const refOut = jsRef(B1, B2, B3, idx); // reference FIRST (wasm writes DAT_803b0720)
  const hit = ex.FUN_80031634(B1, B2, B3, B4) & 1;
  let ok = hit === (refOut.hit ? 1 : 0);
  if (ok && hit) {
    for (let k = 0; k < 3; k++) ok = ok && dv.getFloat32(0x803b0720 + k * 4, true) === refOut.out[k];
  }
  if (ok) bMatch++;
  else if (BN - bMatch < 4) console.log(`  B DIFF #${i} idx=${idx} hit=${hit}/${refOut.hit}`);
}
const shimCalls = Object.values(shimCounts).reduce((a, b) => a + b, 0) - shimBase;
console.log(`\nUnit B [FUN_80031634 SDK seam]  corpus=${BN}`);
console.log(`  exact match (bool + out-vec bytes): ${bMatch}/${BN} (${((bMatch / BN) * 100).toFixed(3)}%)`);
console.log(`  shim calls: ${shimCalls} total (${(shimCalls / BN).toFixed(2)}/case) across ${Object.keys(shimCounts).length} SDK fns: ${JSON.stringify(shimCounts)}`);

// expectations snapshot for the browser step
const expectations = [];
for (let i = 0; i < 32; i++) {
  const c = randCase(100000 + i);
  encodeCase(c);
  expectations.push({ case: c, expect: ex.zz_003cd5c_(REC, ATT, DEF) | 0 });
}
fs.writeFileSync(path.join(here, "browser-expectations.json"), JSON.stringify(expectations));
console.log(`\nbrowser-expectations.json: 32 cases snapshotted`);

// POC_DUMP_CORPUS fixture write (see hook note at top). Header record first: binds the
// dump to the instrumented harness, wasm, arena, and the committed oracle.log the replay
// must reproduce. Written after all logging so nothing here can precede or reorder stdout.
if (dumpPath) {
  const sha = (buf) => createHash("sha256").update(buf).digest("hex");
  const header = {
    kind: "header",
    fixture_schema: 1,
    unit: "damage-core",
    dumped_at: new Date().toISOString(),
    harness_sha256: sha(fs.readFileSync(fileURLToPath(import.meta.url))),
    wasm_sha256: sha(wasmBytes),
    arena_sha256: sha(fs.readFileSync(path.join(here, "arena.json"))),
    oracle_log_sha256: sha(fs.readFileSync(path.join(root, "research", "decomp", "port-units", "damage-core", "oracle.log"))),
    counts: { case: N, cat: catTotal, hp: HPN, unitb: BN },
  };
  fs.writeFileSync(dumpPath, [JSON.stringify(header), ...dumpRecords, ""].join("\n"));
}
