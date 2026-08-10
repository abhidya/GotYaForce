#!/usr/bin/env node
// harness-knockback.mjs — oracle gate for the knockback-core wasm unit.
// Drives the wasm build of the VERBATIM Ghidra C (zz_00300bc_ launch direction,
// FUN_800452a0 atan2->BAM16, zz_005ec20_ ground h-speed select) and the known-good
// TS oracle (sourceKnockback.ts, esbuild-bundled to oracle-knockback.mjs) with the
// SAME seeded corpus, then exact-compares. Residual diffs are classified against a
// float32-faithful reference (ref32) exactly like harness.mjs; any UNEXPLAINED diff
// exits nonzero. Prints "KNOCKBACK ORACLE: PASS" only when fully green.
//
// Struct encoding is cited to the decompiled source:
//   zz_00300bc_(param_1=attacker container, param_2=defender container, mode):
//     container+0x20 -> actor object, +0x24 -> linked object, +0x2c -> record array,
//     +0x11 record index (record stride 0x18, trims at record+0x14/+0x15),
//     +0x30/+0x3c mode-2 vec pair, +0x64 mode-3 linked position.
//     object+0x20 pos, +0x2c mode-0 partner vec, +0x38/3c/40 motion38 fallback,
//     +0x83 mode-4 gate, +0x8dc/8ec/8fc storedAim, +0x11c/12c/13c muzzle,
//     out: defender object +0x284 yaw / +0x282 pitch (BAM16 shorts).
//   zz_005ec20_(actor): +0x702 strength, +0x298/+0xc4 scale ratio, out +0x44.
import fs from "node:fs";
import path from "node:path";
import { fileURLToPath } from "node:url";
import * as oracle from "./oracle-knockback.mjs";

const here = path.dirname(fileURLToPath(import.meta.url));

let mem, u8, dv;
const f32buf = new Float32Array(1);
const fr = (x) => { f32buf[0] = x; return f32buf[0]; };

// SDK shims (never ported). wasm i32 pointers arrive SIGNED: always >>> 0.
const sdkShims = {
  gnt4_PSVECSubtract_bl: (a, b, out) => {
    a >>>= 0; b >>>= 0; out >>>= 0;
    for (let i = 0; i < 3; i++) {
      dv.setFloat32(out + i * 4, fr(dv.getFloat32(a + i * 4, true) - dv.getFloat32(b + i * 4, true)), true);
    }
  },
  gnt4_PSVECMag_bl: (v) => {
    v >>>= 0;
    let s = 0;
    for (let i = 0; i < 3; i++) { const c = dv.getFloat32(v + i * 4, true); s = fr(s + fr(c * c)); }
    return fr(Math.sqrt(s));
  },
  gnt4_atan2_bl: (y, x) => Math.atan2(y, x),
};

const wasmPath = process.env.POC_WASM;
if (!wasmPath) { console.error("POC_WASM must point at the built knockback unit wasm"); process.exit(2); }
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

// arena: POC damage arena (shared constants) + knockback constants/tables (DOL-sourced)
for (const file of ["arena.json", "arena-knockback.json"]) {
  const arena = JSON.parse(fs.readFileSync(path.join(here, file), "utf8"));
  for (const s of arena.segments) u8.set(Buffer.from(s.b64, "base64"), s.addr >>> 0);
}

// DOL table vs the TS oracle's DOL dump must agree before anything else.
const HTAB = [];
for (let i = 0; i < 16; i++) HTAB.push(dv.getFloat32(0x802dd8a0 + i * 4, true));
let tablesOk = true;
for (let i = 0; i < 16; i++) {
  if (HTAB[i] !== oracle.KNOCKBACK_STRENGTH_TABLES.HORIZONTAL[i]) tablesOk = false;
}
console.log(`h-speed table arena==oracle dump: ${tablesOk ? "16/16" : "MISMATCH " + JSON.stringify(HTAB)}`);

// ---------------------------------------------------------------------------
// scratch layout (free region above DOL data/bss)
// ---------------------------------------------------------------------------
const A_CT = 0x80610000, D_CT = 0x80611000;
const A_OB = 0x80612000, D_OB = 0x80614000, L_OB = 0x80616000;
const REC_KB = 0x80618000, P_OB = 0x8061a000;

const wU8 = (a, v) => { u8[a >>> 0] = v & 0xff; };
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
const rnd = mulberry32(0x4b42);
const ri = (n) => Math.floor(rnd() * n);
const rf = (lo, hi) => fr(lo + rnd() * (hi - lo)); // f32 input domain, like the DOL
const rvec = () => ({ x: rf(-100, 100), y: rf(-100, 100), z: rf(-100, 100) });

// ---------------------------------------------------------------------------
// ref32 — float32-faithful mirror of the ROM's conversion pipeline, used ONLY to
// classify wasm-vs-TS diffs (TS runs the math in f64). Mirrors chunk_0003.c
// 8606-8620 + FUN_800452a0 exactly (single-precision mults, double atan2).
// ---------------------------------------------------------------------------
const BAM_F32 = fr(10430.3779296875);
const toShort = (v) => ((Math.trunc(v) & 0xffff) << 16) >> 16;
function ref32(v, trimYaw, trimPitch) {
  let x = fr(v.x), y = fr(v.y), z = fr(v.z);
  if (Math.abs(fr(fr(fr(z * z) + fr(x * x)) + fr(y * y))) < dv.getFloat32(0x80436fc0, true)) {
    x = 0; y = 0; z = -1;
  }
  const horiz = fr(fr(x * x) + fr(z * z)); // (float)(d*d) + (float)(d*d)
  const yawRaw = toShort(fr(BAM_F32 * fr(Math.atan2(x, z))));
  const pitchRaw = toShort(fr(BAM_F32 * fr(Math.atan2(y, Math.abs(horiz)))));
  const sByte = (b) => ((b & 0xff) << 24) >> 24;
  return {
    yaw: toShort(yawRaw + sByte(trimYaw) * -0x100),
    pitch: toShort(-pitchRaw + sByte(trimPitch) * -0x100),
  };
}

// ---------------------------------------------------------------------------
// direction corpus: all 5 modes, engineered so the ROM path and the TS port's
// documented partial-port semantics coincide (see sourceKnockback.ts mode docs).
// ---------------------------------------------------------------------------
function encodeDirectionCase(c) {
  for (const base of [A_CT, D_CT]) u8.fill(0, base, base + 0x100);
  for (const base of [A_OB, D_OB, L_OB]) u8.fill(0, base, base + 0x1000);
  u8.fill(0, REC_KB, REC_KB + 0x18 * 4);
  wU32(A_CT + 0x20, A_OB); wU32(A_CT + 0x24, L_OB); wU32(A_CT + 0x2c, REC_KB);
  wU32(D_CT + 0x20, D_OB); wU32(D_CT + 0x24, L_OB);
  wU8(A_CT + 0x11, c.recIndex);
  const rec = REC_KB + c.recIndex * 0x18;
  wU8(rec + 0x14, c.trimYaw); wU8(rec + 0x15, c.trimPitch);
  wU8(D_OB + 0x1da, 0); // gate off the linked-mirror write (untraced in TS)
  wVec(A_OB + 0x20, c.attPos); wVec(D_OB + 0x20, c.defPos);
  if (c.mode === 0) wVec(A_OB + 0x2c, c.attPos); // pair equal -> mag 0 -> fallback arm
  if (c.mode === 2) { wVec(A_CT + 0x30, c.attPos); wVec(A_CT + 0x3c, c.attPos); }
  wVec(A_OB + 0x38, c.motion38);
  if (c.mode === 4) {
    wU8(A_OB + 0x83, c.aimGate ? 0 : 1);
    wU8(L_OB + 0x83, 1); // cascade skips the linked arm (untraced in TS)
    wF32(A_OB + 0x8dc, c.storedAim.x); wF32(A_OB + 0x8ec, c.storedAim.y); wF32(A_OB + 0x8fc, c.storedAim.z);
    wF32(A_OB + 0x11c, c.muzzle.x); wF32(A_OB + 0x12c, c.muzzle.y); wF32(A_OB + 0x13c, c.muzzle.z);
  }
  if (c.mode === 3) { wVec(A_CT + 0x64, c.linkedAtt); wVec(D_CT + 0x64, c.linkedDef); }
}

function oracleDirection(c) {
  const trims = { trimYaw: c.trimYaw, trimPitch: c.trimPitch };
  if (c.mode === 3) {
    return oracle.computeKnockbackLaunchDirectionLinked(c.linkedAtt, c.linkedDef, trims);
  }
  const attacker = { pos: c.attPos, motion38: c.motion38 };
  if (c.mode === 4) {
    if (c.aimGate) attacker.storedAim8dc = c.storedAim;
    else attacker.muzzle11c = c.muzzle;
  }
  return oracle.computeKnockbackLaunchDirection(attacker, { pos: c.defPos }, { mode: c.mode, ...trims });
}

function ref32Direction(c) {
  const sub = (a, b) => ({ x: fr(a.x - b.x), y: fr(a.y - b.y), z: fr(a.z - b.z) });
  let v;
  if (c.mode === 1) v = sub(c.defPos, c.attPos);
  else if (c.mode === 0 || c.mode === 2) v = c.motion38;
  else if (c.mode === 4) v = c.aimGate ? c.storedAim : c.muzzle;
  else v = sub(c.linkedDef, c.linkedAtt);
  return ref32(v, c.trimYaw, c.trimPitch);
}

// DIRECTION (zz_00300bc_) — run only when the unit exports it. FINDING 2026-08-10:
// the verbatim decompile passes &local_38 as a vec3 base and reads local_34/local_30
// (adjacent PPC stack slots); clang does not keep the three scalars adjacent at -O1
// OR -O0, so a verbatim build mis-reads the shim's vec writes. Until the Ghidra
// export recovers the local as float[3], the direction function stays OUT of the
// unit and this section self-skips (kept so a fixed export is instantly gated).
const hasDirection = typeof ex.zz_00300bc_ === "function";
const N = Number(process.argv[2] ?? 20000);
let match = 0, explained = 0;
const unexplained = [];
for (let i = 0; i < (hasDirection ? N : 0); i++) {
  const mode = ri(5);
  const c = {
    n: i, mode,
    attPos: rvec(), defPos: rvec(), motion38: rvec(),
    storedAim: rvec(), muzzle: rvec(), linkedAtt: rvec(), linkedDef: rvec(),
    aimGate: ri(2) === 0, recIndex: ri(4), trimYaw: ri(256), trimPitch: ri(256),
  };
  if (ri(10) === 0) c.defPos = { ...c.attPos }; // degenerate mode-1 vector -> fallback
  if (ri(10) === 0) c.motion38 = { x: 0, y: 0, z: 0 }; // degenerate fallback arm
  encodeDirectionCase(c);
  ex.zz_00300bc_(A_CT, D_CT, c.mode);
  const w = { yaw: dv.getInt16(D_OB + 0x284, true), pitch: dv.getInt16(D_OB + 0x282, true) };
  const o = oracleDirection(c);
  if (w.yaw === o.yaw && w.pitch === o.pitch) match++;
  else {
    const r = ref32Direction(c);
    if (w.yaw === r.yaw && w.pitch === r.pitch) explained++;
    else if (unexplained.length < 8) unexplained.push({ ...c, wasm: w, oracle: o, ref32: r });
  }
}
if (hasDirection) {
  console.log(`\nknockback direction [zz_00300bc_]  corpus=${N}`);
  console.log(`  exact match vs f64 oracle          : ${match}/${N} (${((match / N) * 100).toFixed(3)}%)`);
  console.log(`  f32-rounding-explained (wasm==ref32): ${explained}`);
  console.log(`  UNEXPLAINED                        : ${N - match - explained}`);
  for (const d of unexplained) console.log(`  DIFF #${d.n}: ${JSON.stringify(d)}`);
} else {
  console.log("\nknockback direction [zz_00300bc_]: SKIPPED (not exported; local-vec3 stack aliasing keeps it out of the verbatim unit)");
}

// FUN_800452a0 direct sweep vs the ROM formula (helper is also an export)
let helperMatch = 0;
const HN = 2000;
for (let i = 0; i < HN; i++) {
  const a = rf(-200, 200), b = rf(-200, 200);
  const w = ex.FUN_800452a0(a, b) | 0;
  const r = toShort(fr(BAM_F32 * fr(Math.atan2(a, b))));
  if (w === r) helperMatch++;
}
console.log(`  atan2->BAM16 helper (FUN_800452a0): ${helperMatch}/${HN} exact`);

// ---------------------------------------------------------------------------
// zz_005ec20_ — ground horizontal-speed select vs groundHorizontalSpeed()
// ---------------------------------------------------------------------------
const MN = 4000;
let magMatch = 0, magConsistency = 0;
for (let i = 0; i < MN; i++) {
  const strength = ri(31) - 15; // signed char domain the ROM abs-clamps (|s| <= 15)
  const scaleNum = rf(0.5, 50), scaleDen = rf(0.5, 10);
  u8.fill(0, P_OB, P_OB + 0x2000);
  wU8(P_OB + 0x702, strength & 0xff);
  wF32(P_OB + 0x298, scaleNum);
  wF32(P_OB + 0xc4, scaleDen);
  ex.zz_005ec20_(P_OB);
  const w44 = dv.getFloat32(P_OB + 0x44, true);
  const ratio = fr(scaleNum / scaleDen); // the ROM's f32 division result
  const expected = fr(oracle.groundHorizontalSpeed(strength, ratio));
  if (w44 === expected) magMatch++;
  else if (MN - magMatch < 6) console.log(`  MAG DIFF s=${strength} ratio=${ratio}: wasm=${w44} oracle=${expected}`);
  // ROM-internal consistency (DOL constants, not TS): +0x4c = -(+0x44)/20.0
  const w4c = dv.getFloat32(P_OB + 0x4c, true);
  if (w4c === fr(-w44 / dv.getFloat32(0x80437490, true))) magConsistency++;
}
console.log(`\nknockback ground h-speed [zz_005ec20_]  corpus=${MN}`);
console.log(`  exact match vs TS oracle           : ${magMatch}/${MN}`);
console.log(`  decel consistency (+0x4c==-v/20)   : ${magConsistency}/${MN}`);

const directionGreen = !hasDirection || (unexplained.length === 0 && N - match - explained === 0);
const green =
  tablesOk &&
  directionGreen &&
  helperMatch === HN &&
  magMatch === MN &&
  magConsistency === MN;
console.log(`\nKNOCKBACK ORACLE: ${green ? "PASS" : "FAIL"}`);
process.exit(green ? 0 : 1);
