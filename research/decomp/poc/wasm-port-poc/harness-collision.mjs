#!/usr/bin/env node
// harness-collision.mjs — oracle gate for the collision-core wasm unit.
// Drives the wasm build of the VERBATIM Ghidra C (the three collision hit-pair
// passes: collision_hit_pair_pass_active_vs_borgs chunk_0003.c:7026-7164,
// _active_vs_secondary 7168-7306, _object_lists 7310-7426) and the known-good TS
// oracle (sourceCollision.ts, esbuild-bundled to oracle-collision.mjs) with the
// SAME seeded corpus, then exact-compares. Residual diffs are classified against
// a float32-faithful reference (ref32) exactly like harness.mjs; any UNEXPLAINED
// diff exits nonzero. Prints "COLLISION ORACLE: PASS" only when fully green.
//
// STRUCTURAL-ORACLE CONTRACT (see gnt4_shim_collision.h): the four unsurfaced
// hitbox-shape functions and the per-pair resolver are stubbed IDENTICALLY on
// both sides (wasm header stubs <-> the TS SourceCollisionHooks built below +
// the pair log). What this oracle actually gates is the verbatim PASS code:
// the per-pass filter chains, immediate-vs-deferred, the closest-target search
// (sentinel FLOAT_80436f98, <= replacement), the deferred separation nudge, and
// the per-pair delegation ORDER/identity/contact point.
//
// Struct encoding is cited to the decompiled source + sourceCollision.ts docs:
//   battle object: +0x11 actionIndex, +0x20 actor ptr, +0x24 owner ptr,
//     +0x28 descriptor ptr (desc+2 u16 flags), +0x2c record base (stride 0x18,
//     rec+0x10 flagsA / rec+0x12 flagsB), +0x58 shape type int, +0x64 pos64,
//     +0x78 overlap flag byte (stub channel, inside the copied +0x54 block),
//     +0x8c origin vec (stub distance channel, DAT_803b0504 source), +0x98 pos98.
//   actor: +0x20 pos, +0x83 eligibility, +0x88 team, +0x100 callback (NULL),
//     +0x1da reaction bits, +0x1db owner flag, +0x1e4 linked owner ptr,
//     +0x3e8 family byte (*(char*)(owner+1000)).
//
// CORPUS CONSTRAINTS (documented TS-vs-ROM deltas, kept OUT of the corpus):
//   1. flagsA bit 0x800 ("skip collision"): the ROM checks it ONLY in pass 1
//      (chunk_0003.c:7067); TS runPassCore applies it to all three passes. The
//      corpus sets 0x800 only on pass-1 actives.
//   2. pairOwnersAdmissible owner-link clause: the ROM's per-side clear is
//      (ownerFlag==0 || otherFamily==0x0e || linked != other) — an OR chain
//      (chunk_0003.c:7087-7090); TS renders it (ownerFlag==0 || otherFamily==
//      0x0e) && linked !== other. The two agree when ownerFlag==0 (linked null)
//      and in the full exclusion cell (ownerFlag=1, family!=0x0e, linked==other);
//      the corpus generates only those cells for same-team borg-vs-borg owners.
import fs from "node:fs";
import path from "node:path";
import { fileURLToPath } from "node:url";
import * as oracle from "./oracle-collision.mjs";

const here = path.dirname(fileURLToPath(import.meta.url));

let mem, u8, dv;
const f32buf = new Float32Array(1);
const f32bits = new Uint32Array(f32buf.buffer);
const fr = (x) => { f32buf[0] = x; return f32buf[0]; };
const bitsOf = (x) => { f32buf[0] = x; return f32bits[0]; };

// f32-faithful square distance / square magnitude (paired-single accumulation),
// shared by the wasm SDK shims AND the TS-side hook so both sides are identical.
function d2f32(a, b) {
  const dx = fr(a.x - b.x), dy = fr(a.y - b.y), dz = fr(a.z - b.z);
  return fr(fr(fr(dx * dx) + fr(dy * dy)) + fr(dz * dz));
}

// SDK shims (never ported). wasm i32 pointers arrive SIGNED: always >>> 0.
const rdVec = (p) => ({ x: dv.getFloat32(p >>> 0, true), y: dv.getFloat32((p >>> 0) + 4, true), z: dv.getFloat32((p >>> 0) + 8, true) });
const sdkShims = {
  gnt4_PSVECSubtract_bl: (a, b, out) => {
    a >>>= 0; b >>>= 0; out >>>= 0;
    for (let i = 0; i < 3; i++) {
      dv.setFloat32(out + i * 4, fr(dv.getFloat32(a + i * 4, true) - dv.getFloat32(b + i * 4, true)), true);
    }
  },
  gnt4_PSVECAdd_bl: (a, b, out) => {
    a >>>= 0; b >>>= 0; out >>>= 0;
    for (let i = 0; i < 3; i++) {
      dv.setFloat32(out + i * 4, fr(dv.getFloat32(a + i * 4, true) + dv.getFloat32(b + i * 4, true)), true);
    }
  },
  gnt4_PSVECSquareMag_bl: (v) => { const p = rdVec(v); return d2f32(p, { x: 0, y: 0, z: 0 }); },
  gnt4_PSVECSquareDistance_bl: (a, b) => d2f32(rdVec(a), rdVec(b)),
  gnt4_PSQUATScale_bl: (s, v, out) => {
    v >>>= 0; out >>>= 0;
    for (let i = 0; i < 3; i++) dv.setFloat32(out + i * 4, fr(dv.getFloat32(v + i * 4, true) * s), true);
  },
};

const wasmPath = process.env.POC_WASM;
if (!wasmPath) { console.error("POC_WASM must point at the built collision unit wasm"); process.exit(2); }
const module = await WebAssembly.compile(fs.readFileSync(wasmPath));
const instance = await WebAssembly.instantiate(module, {
  env: new Proxy(sdkShims, {
    get: (t, k) => t[k] ?? ((...a) => { throw new Error(`unshimmed import ${String(k)}(${a})`); }),
  }),
});
const ex = instance.exports;
mem = ex.memory;
u8 = new Uint8Array(mem.buffer);
dv = new DataView(mem.buffer);

// arena: POC damage arena (shared constants) + collision constants (DOL-sourced)
for (const file of ["arena.json", "arena-collision.json"]) {
  const arena = JSON.parse(fs.readFileSync(path.join(here, file), "utf8"));
  for (const s of arena.segments) u8.set(Buffer.from(s.b64, "base64"), s.addr >>> 0);
}
const SENTINEL = dv.getFloat32(0x80436f98, true);
console.log(`deferred sentinel FLOAT_80436f98 = ${SENTINEL} (DOL)`);

// ---------------------------------------------------------------------------
// memory layout
// ---------------------------------------------------------------------------
const LIST = {
  active: 0x803c477c, borgs: 0x803c2f7c, secondary: 0x803c417c,
  listA: 0x803c177c, listB: 0x803c117c,
};
const COUNT = {
  active: 0x80436250, borgs: 0x80436248, secondary: 0x8043624e,
  listA: 0x80436240, listB: 0x8043623e,
};
const PAIRLOG = 0x80630000;
const ACTIVE_BASE = 0x80640000, TARGET_BASE = 0x80650000, ACTOR_BASE = 0x80660000;
const OBJ_STRIDE = 0x1000, ACTOR_STRIDE = 0x800;
const MAX_ACTIVE = 4, MAX_TARGET = 5, MAX_ACTORS = 2 * (MAX_ACTIVE + MAX_TARGET);

const wU8 = (a, v) => { u8[a >>> 0] = v & 0xff; };
const wU16 = (a, v) => dv.setUint16(a >>> 0, v & 0xffff, true);
const wU32 = (a, v) => dv.setUint32(a >>> 0, v >>> 0, true);
const wF32 = (a, v) => dv.setFloat32(a >>> 0, v, true);
const wVec = (a, v) => { wF32(a, v.x); wF32(a + 4, v.y); wF32(a + 8, v.z); };

function mulberry32(seed) {
  return () => {
    seed |= 0; seed = (seed + 0x6d2b79f5) | 0;
    let t = Math.imul(seed ^ (seed >>> 15), 1 | seed);
    t = (t + Math.imul(t ^ (t >>> 7), 61 | t)) ^ t;
    return ((t ^ (t >>> 14)) >>> 0) / 4294967296;
  };
}
const rnd = mulberry32(0xc0111);
const ri = (n) => Math.floor(rnd() * n);
const rf = (lo, hi) => fr(lo + rnd() * (hi - lo)); // f32 input domain, like the DOL
const rvec = () => ({ x: rf(-100, 100), y: rf(-100, 100), z: rf(-100, 100) });

// ---------------------------------------------------------------------------
// case generation: TS object graphs first, then a byte-encoding of the same.
// ---------------------------------------------------------------------------
function makeActor() {
  const family = ri(6) === 0 ? 0x0e : ri(0x20);
  return {
    borgNumber: (family << 8) | ri(256),
    team: ri(2),
    slot: ri(6),
    eligibility83: ri(3) === 0 ? 1 : 0,
    reaction1da: ri(4) === 0 ? 2 : 0,
    ownerFlag1db: 0,
    linkedOwner1e4: null,
    pairAttack6fc: 0,
    power: 1,
    hp: 200,
    maxHp: 200,
    pos: rvec(),
    damageDealt418: 0,
    friendlyFire42c: 0,
    damageTaken41c: 0,
  };
}

function makeObject(passKind, isActive) {
  const actor = makeActor();
  const owner = ri(2) === 0 ? actor : makeActor();
  const records = [];
  for (let r = 0; r < 4; r++) {
    // Only rec+0x10/0x12 are pass inputs; the rest keep the TS resolver valid.
    let flagsA = (ri(2) ? 1 : 0) | (ri(4) === 0 ? 2 : 0);
    if (passKind === 0 && isActive && ri(5) === 0) flagsA |= 0x800; // pass-1-only skip bit
    const flagsB =
      (ri(2) ? 0x10 : 0) | (ri(2) ? 0x8000 : 0) |
      (ri(4) === 0 ? 0x40 : 0) | (ri(4) === 0 ? 0x100 : 0) | (ri(6) === 0 ? 0x200 : 0);
    records.push({
      hpDamage: 40, scalingWord: 0, priorityByte: 0, gaugeByte: 0, reactionBits: 0,
      knockbackStrength: 4, knockbackMode: 1, reactionAnimVariant: 0, flagsA, flagsB,
    });
  }
  const actionIndex = ri(4);
  return {
    actor, owner, actionIndex,
    records,
    hitRecord: records[actionIndex],
    descriptorFlags: (ri(2) ? 0x800 : 0) | (ri(2) ? 0x1000 : 0) | (ri(2) ? 0x2000 : 0) | (ri(2) ? 0x4000 : 0),
    shapeType: [2, 2, 2, 0, 5][ri(5)],
    pos98: rvec(), pos64: rvec(),
    __origin8c: rvec(), __overlap78: ri(4) < 3 ? 1 : 0,
  };
}

// Same-team borg-vs-borg owner pairs may only use link cells where the ROM's
// OR-chain and the TS &&-form agree (corpus constraint 2 in the header). A cell
// (flag=1, linked=counterpart, counterpartFamily!=0x0e) agrees for THAT pair
// (both block), but any OTHER same-team-borg counterpart reaching the link
// clause diverges (C clears via linked!=other, TS blocks). So a cell is only
// installed on an owner whose same-team-borg counterpart set is exactly {the
// linked owner} — globally safe by construction.
function constrainOwnerLinks(actives, targets) {
  const sameTeamBorg = (x, y) => x.eligibility83 === 0 && y.eligibility83 === 0 && x.team === y.team;
  const activeOwners = [...new Set(actives.map((o) => o.owner))];
  const targetOwners = [...new Set(targets.map((o) => o.owner))];
  const install = (owner, counterparts) => {
    if (counterparts.length !== 1 || ri(3) !== 0) return;
    const other = counterparts[0];
    if (((other.borgNumber >>> 8) & 0xff) === 0x0e) return;
    owner.ownerFlag1db = 1;
    owner.linkedOwner1e4 = other;
  };
  for (const to of targetOwners) {
    install(to, activeOwners.filter((ao) => sameTeamBorg(ao, to)));
  }
  for (const ao of activeOwners) {
    install(ao, targetOwners.filter((to) => sameTeamBorg(to, ao)));
  }
}

function encodeCase(actives, targets) {
  // zero object/actor scratch + pair log + all list counts
  for (let i = 0; i < MAX_ACTIVE; i++) u8.fill(0, ACTIVE_BASE + i * OBJ_STRIDE, ACTIVE_BASE + (i + 1) * OBJ_STRIDE);
  for (let i = 0; i < MAX_TARGET; i++) u8.fill(0, TARGET_BASE + i * OBJ_STRIDE, TARGET_BASE + (i + 1) * OBJ_STRIDE);
  u8.fill(0, ACTOR_BASE, ACTOR_BASE + MAX_ACTORS * ACTOR_STRIDE);
  wU32(PAIRLOG, 0);
  for (const key of Object.keys(COUNT)) wU16(COUNT[key], 0);

  const actorPtr = new Map();
  let nextActor = 0;
  const encodeActor = (a) => {
    if (actorPtr.has(a)) return actorPtr.get(a);
    const base = ACTOR_BASE + nextActor++ * ACTOR_STRIDE;
    actorPtr.set(a, base);
    wVec(base + 0x20, a.pos);
    wU8(base + 0x83, a.eligibility83);
    wU8(base + 0x88, a.team);
    wU32(base + 0x100, 0); // +0x100 callback NULL: the nudge callback never fires
    wU8(base + 0x1da, a.reaction1da);
    wU8(base + 0x1db, a.ownerFlag1db);
    wU8(base + 0x3e8, (a.borgNumber >>> 8) & 0xff); // *(char*)(owner+1000) family byte
    return base;
  };
  const encodeObject = (o, base) => {
    wU8(base + 0x11, o.actionIndex);
    wU32(base + 0x20, encodeActor(o.actor));
    wU32(base + 0x24, encodeActor(o.owner));
    wU32(base + 0x28, base + 0x800);
    wU16(base + 0x800 + 2, o.descriptorFlags);
    wU32(base + 0x2c, base + 0x900);
    for (let r = 0; r < 4; r++) {
      wU16(base + 0x900 + r * 0x18 + 0x10, o.records[r].flagsA);
      wU16(base + 0x900 + r * 0x18 + 0x12, o.records[r].flagsB);
    }
    wU32(base + 0x58, o.shapeType);
    wVec(base + 0x64, o.pos64);
    wU8(base + 0x78, o.__overlap78);
    wVec(base + 0x8c, o.__origin8c);
    wVec(base + 0x98, o.pos98);
  };
  // linked-owner pointers need every actor encoded first
  actives.forEach((o, i) => encodeObject(o, ACTIVE_BASE + i * OBJ_STRIDE));
  targets.forEach((o, i) => encodeObject(o, TARGET_BASE + i * OBJ_STRIDE));
  for (const [a, base] of actorPtr) {
    wU32(base + 0x1e4, a.linkedOwner1e4 ? (actorPtr.get(a.linkedOwner1e4) ?? 0) : 0);
  }
}

// TS-side hooks: the EXACT mirror of the header stubs.
const hooks = {
  broadPhase: () => true,
  shapeCompat: () => true,
  transformAndOverlap: (active, target) => ({
    overlap: target.__overlap78 !== 0,
    contactPoint: { x: target.pos64.x, y: target.pos64.y, z: target.pos64.z },
    squareDistance: d2f32(target.pos64, active.__origin8c),
  }),
};

// ref32 mirror of the deferred nudge (the wasm side runs it through the f32 SDK
// shims; TS applyDeferredNudge runs f64 JS arithmetic). Used ONLY to classify.
function ref32Nudge(pre, cp) {
  const d = { x: fr(cp.x - pre.pos98.x), y: fr(cp.y - pre.pos98.y), z: fr(cp.z - pre.pos98.z) };
  const mag2 = d2f32(d, { x: 0, y: 0, z: 0 });
  if (!(mag2 > dv.getFloat32(0x80436f68, true))) return pre; // FLOAT_80436f68 gate
  const add = (v, w) => ({ x: fr(v.x + w.x), y: fr(v.y + w.y), z: fr(v.z + w.z) });
  const half = { x: fr(d.x * 0.5), y: fr(d.y * 0.5), z: fr(d.z * 0.5) };
  return { pos98: add(pre.pos98, d), actorPos: add(pre.actorPos, d), pos64: add(pre.pos64, half) };
}

const PASSES = [
  { name: "active_vs_borgs", wasm: () => ex.collision_hit_pair_pass_active_vs_borgs(), ts: oracle.collisionHitPairPassActiveVsBorgs, lists: ["active", "borgs"] },
  { name: "object_lists", wasm: () => ex.collision_hit_pair_pass_object_lists(), ts: oracle.collisionHitPairPassObjectLists, lists: ["listA", "listB"] },
  { name: "active_vs_secondary", wasm: () => ex.collision_hit_pair_pass_active_vs_secondary(), ts: oracle.collisionHitPairPassActiveVsSecondary, lists: ["active", "secondary"] },
];

const N = Number(process.argv[2] ?? 20000);
const passCases = [0, 0, 0];
let pairSeqExact = 0, pairsTotal = 0;
let vecExact = 0, vecExplained = 0, vecTotal = 0;
const unexplained = [];

for (let caseIndex = 0; caseIndex < N; caseIndex++) {
  const passKind = ri(3);
  const pass = PASSES[passKind];
  passCases[passKind]++;
  const nActive = ri(MAX_ACTIVE + 1) === 0 ? 0 : 1 + ri(MAX_ACTIVE - 1);
  const nTarget = ri(MAX_TARGET + 1) === 0 ? 0 : 1 + ri(MAX_TARGET - 1);
  const actives = Array.from({ length: nActive }, () => makeObject(passKind, true));
  const targets = Array.from({ length: nTarget }, () => makeObject(passKind, false));
  constrainOwnerLinks(actives, targets);
  // occasionally force a zero-delta nudge (pos98 exactly at the contact point)
  if (nActive && nTarget && ri(8) === 0) actives[0].pos98 = { ...targets[ri(nTarget)].pos64 };

  encodeCase(actives, targets);
  const [activeKey, targetKey] = pass.lists;
  actives.forEach((_, i) => wU32(LIST[activeKey] + i * 4, ACTIVE_BASE + i * OBJ_STRIDE));
  targets.forEach((_, i) => wU32(LIST[targetKey] + i * 4, TARGET_BASE + i * OBJ_STRIDE));
  wU16(COUNT[activeKey], nActive);
  wU16(COUNT[targetKey], nTarget);

  const pre = actives.map((o) => ({
    pos98: { ...o.pos98 }, actorPos: { ...o.actor.pos }, pos64: { ...o.pos64 },
  }));

  pass.wasm();
  const tsPairs = pass.ts(actives, targets, { hooks });

  // --- pair sequence: identity + order + contact point (bit-exact f32) ---
  const logged = dv.getUint32(PAIRLOG, true);
  let seqOk = logged === tsPairs.length;
  for (let i = 0; seqOk && i < logged; i++) {
    const rec = PAIRLOG + 4 + i * 20;
    const activeIdx = (dv.getUint32(rec, true) - ACTIVE_BASE) / OBJ_STRIDE;
    const targetIdx = (dv.getUint32(rec + 4, true) - TARGET_BASE) / OBJ_STRIDE;
    const p = tsPairs[i];
    seqOk =
      actives[activeIdx] === p.active && targets[targetIdx] === p.target &&
      dv.getUint32(rec + 8, true) === bitsOf(p.contactPoint.x) &&
      dv.getUint32(rec + 12, true) === bitsOf(p.contactPoint.y) &&
      dv.getUint32(rec + 16, true) === bitsOf(p.contactPoint.z);
  }
  pairsTotal += tsPairs.length;
  if (seqOk) pairSeqExact++;
  else if (unexplained.length < 8) {
    unexplained.push({ caseIndex, pass: pass.name, kind: "pair-seq", logged, expected: tsPairs.length });
  }

  // --- post-pass nudge state: exact vs TS(f64), else ref32-explained ---
  for (let i = 0; i < nActive; i++) {
    const base = ACTIVE_BASE + i * OBJ_STRIDE;
    const w = { pos98: rdVec(base + 0x98), actorPos: rdVec(dv.getUint32(base + 0x20, true) + 0x20), pos64: rdVec(base + 0x64) };
    const t = { pos98: actives[i].pos98, actorPos: actives[i].actor.pos, pos64: actives[i].pos64 };
    const eq = (a, b) => a.x === b.x && a.y === b.y && a.z === b.z;
    vecTotal++;
    if (eq(w.pos98, t.pos98) && eq(w.actorPos, t.actorPos) && eq(w.pos64, t.pos64)) { vecExact++; continue; }
    // classify: the deferred pair for this active (at most one) supplies cp
    const deferredPair = tsPairs.find((p) => p.active === actives[i]);
    const r = deferredPair ? ref32Nudge(pre[i], deferredPair.contactPoint) : pre[i];
    if (eq(w.pos98, r.pos98) && eq(w.actorPos, r.actorPos) && eq(w.pos64, r.pos64)) { vecExplained++; continue; }
    if (unexplained.length < 8) {
      unexplained.push({ caseIndex, pass: pass.name, kind: "nudge", i, wasm: w, ts: t, ref32: r });
    }
  }
}

console.log(`\ncollision hit-pair passes  cases=${N} (borgs=${passCases[0]} objlists=${passCases[1]} secondary=${passCases[2]})`);
console.log(`  pair sequences exact (identity+order+contact): ${pairSeqExact}/${N}  (${pairsTotal} pairs total)`);
console.log(`  active post-state exact vs f64 oracle : ${vecExact}/${vecTotal}`);
console.log(`  f32-rounding-explained (wasm==ref32)  : ${vecExplained}`);
console.log(`  UNEXPLAINED : ${N - pairSeqExact + (vecTotal - vecExact - vecExplained)}`);
for (const d of unexplained) console.log(`  DIFF ${JSON.stringify(d)}`);

const green =
  pairSeqExact === N &&
  vecExact + vecExplained === vecTotal &&
  unexplained.length === 0;
console.log(`\nCOLLISION ORACLE: ${green ? "PASS" : "FAIL"}`);
process.exit(green ? 0 : 1);
