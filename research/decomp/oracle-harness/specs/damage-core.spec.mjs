// damage-core.spec.mjs — unit oracle spec for the generic differential harness.
//
// Reference (I-10): reference_kind "ts_port" — packages/combat/src/damage/sourceDamage.ts,
// consumed through the SAME esbuild bundle the PoC used (poc/wasm-port-poc/oracle.mjs;
// plan §1.3 "the same bundling path serves the generic harness"). Differential green
// means "agrees with the reviewed TS port", not ground truth (F-3).
//
// Read-set (mechanism 2) authored from the verbatim C:
// research/decomp/port-units/damage-core/unit.c —
//   zz_003cd5c_: REC{+0 u16,+6,+7,+0x10 u16,+0x12 u16}; ATT{+0x90 ptr,+0xc4 f32};
//     ATTB{+0,+0x18,+0x83,+0x88,+0x1c4 s16,+0x3e4,+0x3e6,+0x3e8 u16be,+0x43a,+0x6fc};
//     DEF{+0,+0x18,+0x83,+0x88,+0x90 ptr,+0xb4 f32,+0x1c4 s16,+0x3e4,+0x3e6,+0x3e8,
//         +0x43a,+0x4ac ptr,+0x59c u16,+0x5a0 u32,+0x5e0 u32,+0x6ca,+0x6fc,+0x71a};
//     DESC{+0x9c..+0x9e}; bss: DAT_803b069c[slot] s16, DAT_803b068c[team] i32,
//     *PTR_DAT_80433934+team*0x3c+0x114 i32, PTR_DAT_80433950[team], PTR_DAT_80433930[0x32],
//     *PTR_DAT_80433934+0x1f; DOL tables 0x804335e0..0x80433618, DAT_802c7ca0,
//     type table 0x802c5d60, remap PTR_DAT_802f2e28, float consts 0x80436f68..0x80437028.
//   zz_003d344_: reads {+0x1c6 s16,+0x1c4 s16,+0x83,+0x4a0, PTR_DAT_80433934[0x1f]};
//     writes {+0x1c8 s16 = pre-hit hp, +0x1c6 s16 = clamped hp} unless hp==0 no-op.
//   zz_0066298_: CAT{+0,+1}; remap rows (arena).
//   FUN_80031634: B1{corner 12B @ +chTab[idx*4]*0xc+0x30, normal 12B @ +idx*0x18+0x90};
//     B2{+0x30 f32}; B3{24B}; B4{i32}; chTab DAT_802cffc8 (arena);
//     writes DAT_803b0720 (bss, compared as the oracle check, not region-diffed).
//
// Encoding parity note: the PoC writes PTR_DAT_80433930[0x32] as `ri(2)` when
// cpuHalvingEnabled (consuming a PRNG draw at ENCODE time). The ROM tests only
// `==0 || ==1`, so 0 and 1 are semantically identical; replay writes 0. The dumped
// corpus was produced by the original draw order, so replay-side draws are moot.
import fs from "node:fs";
import path from "node:path";
import { fileURLToPath } from "node:url";
import * as oracle from "../../poc/wasm-port-poc/oracle.mjs";
import { fr } from "../lib/wasm.mjs";

const here = path.dirname(fileURLToPath(import.meta.url));
const root = path.resolve(here, "..", "..", "..", "..");
const formulaData = JSON.parse(
  fs.readFileSync(path.join(root, "packages", "combat", "src", "data", "damageFormula.json"), "utf8"),
);
const remap = JSON.parse(
  fs.readFileSync(path.join(root, "research", "decomp", "data", "type-category-remap-802f2e28.json"), "utf8"),
);
const remapRows = remap.rows ?? remap.table ?? remap;

// scratch objects (free region above all DOL/bss sections; PoC addresses kept)
const REC = 0x80600000, ATT = 0x80601000, ATTB = 0x80602000, DEF = 0x80604000, DESC = 0x80606000;
const CAT = 0x80608000;
const B1 = 0x80609000, B2 = 0x8060a000, B3 = 0x8060b000, B4 = 0x8060c000;
const HP_MIRROR = 0x803b069c; // s16[slot]
const ENERGY = 0x803b068c;    // i32[team]

export const meta = {
  unit: "damage-core",
  reference_kind: "ts_port",
  references: [
    "packages/combat/src/damage/sourceDamage.ts (via research/decomp/poc/wasm-port-poc/oracle.mjs esbuild bundle)",
  ],
  arena: "../poc/wasm-port-poc/arena.json",
  wasmDefault: "../port-units/damage-core/unit.wasm",
  fixture: "corpora/damage-core-poc.jsonl",
  // F-5: rounding_bound is per-spec, declared and reviewed. zz_003cd5c_ is a
  // truncating integer formula (integer-formula class ≈ 0.1%); the PoC baseline is
  // 2/20,000 = 0.01%, each satisfying the oracle32 witness. The other three
  // functions expect no rounding divergence and get none for free (default 0).
  functions: [
    { name: "zz_003cd5c_", rounding_bound: 0.001,
      note: "integer damage formula; PoC baseline 2/20000 f32-rounding-explained" },
    { name: "zz_0066298_", rounding_bound: 0 },
    { name: "zz_003d344_", rounding_bound: 0 },
    { name: "FUN_80031634", rounding_bound: 0 },
  ],
  regions: [
    { name: "REC", base: REC, size: 0x20 },
    { name: "ATT", base: ATT, size: 0x100 },
    { name: "ATTB", base: ATTB, size: 0x800 },
    { name: "DEF", base: DEF, size: 0x800 },
    { name: "DESC", base: DESC, size: 0xa0 },
    { name: "CAT", base: CAT, size: 0x2 },
    { name: "B1", base: B1, size: 0x200 },
    { name: "B2", base: B2, size: 0x40 },
    { name: "B3", base: B3, size: 0x20 },
    { name: "B4", base: B4, size: 0x8 },
  ],
};

// SDK shims (stage-1 seam: gnt4_PS* are JS imports, never ported). Single-precision
// via fround — identical to the PoC's proven shims.
export function makeShims(memCtx) {
  const count = (name) => { memCtx.counts[name] = (memCtx.counts[name] ?? 0) + 1; };
  return {
    gnt4_PSVECSubtract_bl: (a, b, out) => {
      count("gnt4_PSVECSubtract_bl");
      a >>>= 0; b >>>= 0; out >>>= 0;
      const dv = memCtx.dv;
      for (let i = 0; i < 3; i++) dv.setFloat32(out + i * 4, fr(dv.getFloat32(a + i * 4, true) - dv.getFloat32(b + i * 4, true)), true);
    },
    gnt4_PSVECAdd_bl: (a, b, out) => {
      count("gnt4_PSVECAdd_bl");
      a >>>= 0; b >>>= 0; out >>>= 0;
      const dv = memCtx.dv;
      for (let i = 0; i < 3; i++) dv.setFloat32(out + i * 4, fr(dv.getFloat32(a + i * 4, true) + dv.getFloat32(b + i * 4, true)), true);
    },
    gnt4_PSQUATDotProduct_bl: (a, b) => {
      count("gnt4_PSQUATDotProduct_bl");
      a >>>= 0; b >>>= 0;
      const dv = memCtx.dv;
      let s = 0;
      for (let i = 0; i < 3; i++) s = fr(s + fr(dv.getFloat32(a + i * 4, true) * dv.getFloat32(b + i * 4, true)));
      return s;
    },
    gnt4_PSQUATScale_bl: (s, v, out) => {
      count("gnt4_PSQUATScale_bl");
      v >>>= 0; out >>>= 0;
      const dv = memCtx.dv;
      for (let i = 0; i < 3; i++) dv.setFloat32(out + i * 4, fr(fr(s) * dv.getFloat32(v + i * 4, true)), true);
    },
  };
}

// ---------------------------------------------------------------------------
// oracle32 — the f32-faithful witness (I-6). Copied intact from the frozen PoC
// harness (poc/wasm-port-poc/harness.mjs): mirrors zz_003cd5c_'s exact float/double
// op structure; tables fround'ed because the DOL stores f32 bit patterns while
// damageFormula.json stores decimal-shortened doubles.
// ---------------------------------------------------------------------------
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
// Runner
// ---------------------------------------------------------------------------
export function createRunner({ ex, u8, dv }) {
  // Resolve the DOL-initialized runtime-struct pointers by READING the arena (I-3).
  const STRUCT30 = dv.getUint32(0x80433930, true); // [0x32] challenge-mode byte
  const STRUCT34 = dv.getUint32(0x80433934, true); // [team*0x3c+0x114] energy max; [0x1f] borg gate
  const STRUCT50 = dv.getUint32(0x80433950, true); // [team] side-rank byte

  // Encode one PoC-domain actor into GC-address memory. RomActor-mapped fields
  // (borgNumber/slot/team/controlWord) go through the codec's field map; the
  // remaining offsets are spec-declared (non-RomActor state: hp/gauge fields are
  // BorgRuntime-owned per actor.ts's out-of-scope note) using the same tracked
  // primitives — plan §3.3 "per-unit encoders in the unit spec".
  function encodeActor(codec, base, a, { container = null } = {}) {
    codec.wU8(base + 0x00, 1);                       // live marker (*pcVar != 0 gate)
    codec.wU8(base + 0x18, a.isActive ? 1 : 0);      // isActive gate byte
    codec.wU8(base + 0x83, a.isBorg ? 0 : 1);        // 0 = borg (ROM polarity)
    codec.encodeField(base, "team", a.team);         // +0x88 via field map
    codec.wU16(base + 0x1c4, a.maxHp);               // maxHp s16
    codec.encodeField(base, "slot", a.slot);         // +0x3e4 via field map
    codec.wU8(base + 0x3e6, a.heroFlag);             // hero flag
    codec.encodeField(base, "borgNumber", a.borgNumber); // +0x3e8 u16be via field map
    codec.wU8(base + 0x43a, a.handicap);             // handicap byte
    codec.wU8(base + 0x6ca, a.comboRank);            // combo rank byte
    codec.wU8(base + 0x6fc, a.pairAttack);           // pair-attack flag
    if (container != null) codec.wF32(container + 0xc4, a.power);
    else codec.wF32(base + 0xb4, a.power);           // RomActor.modelScale offset (defender power read)
  }

  function encodeCase(codec, c) {
    codec.beginCase();
    // record
    codec.wU16(REC + 0x00, c.basePower);
    codec.wU8(REC + 0x06, c.ctx.attackerHpCurveIndex);
    codec.wU8(REC + 0x07, c.ctx.attackerForceCurveIndex);
    codec.wU16(REC + 0x10, c.ctx.flagsA);
    codec.wU16(REC + 0x12, c.ctx.flagsB);
    // attacker container -> borg sub-object
    codec.wU32(ATT + 0x90, ATTB);
    encodeActor(codec, ATTB, c.att, { container: ATT });
    // defender: param_3 IS the borg (+0x90 null -> resolution keeps param_3)
    encodeActor(codec, DEF, c.def, {});
    codec.wU32(DEF + 0x90, 0);
    codec.wU32(DEF + 0x4ac, DESC);
    codec.wU16(DEF + 0x59c, c.ctx.victimResistanceMask);
    // +0x5e0 control word: spawn-protection bit 0x4000000 — RomActor-mapped field
    codec.encodeField(DEF, "controlWord", c.ctx.victimSpawnProtection ? 0x4000000 : 0);
    codec.wU8(DEF + 0x71a, 1);
    codec.wU32(DEF + 0x5a0, c.ctx.victimStatusImmune ? (1 << 1) : 0);
    codec.wU8(DESC + 0x9c, c.ctx.defenderDefenseCurveSelectors[0]);
    codec.wU8(DESC + 0x9d, c.ctx.defenderDefenseCurveSelectors[1]);
    codec.wU8(DESC + 0x9e, c.ctx.defenderDefenseCurveSelectors[2]);
    // bss live state
    codec.wI16(HP_MIRROR + c.att.slot * 2, c.att.hp);
    codec.wI16(HP_MIRROR + c.def.slot * 2, c.def.hp);
    for (const a of [c.att, c.def]) {
      codec.wI32(STRUCT34 + a.team * 0x3c + 0x114, 3200);
      codec.wI32(ENERGY + a.team * 4, (32 - a.forceRatioIndex) * 100);
      codec.wU8(STRUCT50 + a.team, a.sideRank);
    }
    codec.wU8(STRUCT30 + 0x32, c.ctx.cpuHalvingEnabled ? 0 : 2); // see parity note above
    codec.wU8(STRUCT34 + 0x1f, 0);
  }

  function caseReadSet(c) {
    const mustWrite = [
      [REC + 0x00, 2], [REC + 0x06, 1], [REC + 0x07, 1], [REC + 0x10, 2], [REC + 0x12, 2],
      [ATT + 0x90, 4], [ATT + 0xc4, 4],
      [ATTB + 0x00, 1], [ATTB + 0x18, 1], [ATTB + 0x83, 1], [ATTB + 0x88, 1],
      [ATTB + 0x1c4, 2], [ATTB + 0x3e4, 1], [ATTB + 0x3e6, 1], [ATTB + 0x3e8, 2],
      [ATTB + 0x43a, 1], [ATTB + 0x6fc, 1],
      [DEF + 0x00, 1], [DEF + 0x18, 1], [DEF + 0x83, 1], [DEF + 0x88, 1], [DEF + 0x90, 4],
      [DEF + 0xb4, 4], [DEF + 0x1c4, 2], [DEF + 0x3e4, 1], [DEF + 0x3e6, 1], [DEF + 0x3e8, 2],
      [DEF + 0x43a, 1], [DEF + 0x4ac, 4], [DEF + 0x59c, 2], [DEF + 0x5a0, 4], [DEF + 0x5e0, 4],
      [DEF + 0x6ca, 1], [DEF + 0x6fc, 1], [DEF + 0x71a, 1],
      [DESC + 0x9c, 3],
      [HP_MIRROR + c.att.slot * 2, 2], [HP_MIRROR + c.def.slot * 2, 2],
      [STRUCT34 + c.att.team * 0x3c + 0x114, 4], [STRUCT34 + c.def.team * 0x3c + 0x114, 4],
      [ENERGY + c.att.team * 4, 4], [ENERGY + c.def.team * 4, 4],
      [STRUCT50 + c.att.team, 1], [STRUCT50 + c.def.team, 1],
      [STRUCT30 + 0x32, 1], [STRUCT34 + 0x1f, 1],
    ];
    const arenaOk = [
      [0x80433930, 4], [0x80433934, 4], [0x80433950, 4], // struct pointer cells
      [0x80436f68, 4], [0x80436f78, 4], [0x80436f7c, 4], [0x80436f9c, 4],
      [0x80437024, 4], [0x80437028, 4], [0x80436fb0, 8],
      [0x804335e0, 0x40], // damage table pointer block
      [0x802c7ca0, 0x40], // combo-rank scale
      [0x802f2e28, 0x40], // type-category remap row pointers
      [0x802c5d60, 0x50 * 16], // type multiplier matrix
    ];
    return { mustWrite, arenaOk };
  }

  return {
    unit: meta.unit,
    // Dispatch one fixture record. Returns a per-function outcome or a check result.
    handleRecord(codec, rec) {
      switch (rec.kind) {
        case "case": {
          const c = rec;
          encodeCase(codec, c);
          const audit = codec.auditReads(caseReadSet(c));
          codec.snapshotExpected();
          const w = ex.zz_003cd5c_(REC, ATT, DEF) | 0;
          const o = oracle.computeBaseDamage(c.att, c.def, c.basePower, c.ctx);
          const post = codec.diffPostState([]); // pure function: no modeled write-backs
          let cls;
          if (w === o) cls = "exact";
          else if (oracle32(c) === w) cls = "rounding";
          else cls = "unexplained";
          return { fn: "zz_003cd5c_", n: c.n, cls, audit, post,
                   dump: cls === "unexplained" ? { n: c.n, wasm: w, oracle: o, o32: oracle32(c), case: { att: c.att, def: c.def, basePower: c.basePower, ctx: c.ctx } } : null };
        }
        case "cat": {
          codec.beginCase();
          codec.wU8(CAT, rec.family); codec.wU8(CAT + 1, rec.variant);
          const audit = codec.auditReads({ mustWrite: [[CAT, 2]], arenaOk: [[0x802f2e28, 0x40]] });
          codec.snapshotExpected();
          const w = ex.zz_0066298_(CAT) | 0;
          const o = oracle.lookupTypeCategory((rec.family << 8) | rec.variant);
          const post = codec.diffPostState([]);
          const cls = w === o ? "exact" : "unexplained";
          return { fn: "zz_0066298_", n: (rec.family << 8) | rec.variant, cls, audit, post,
                   dump: cls === "unexplained" ? { family: rec.family, variant: rec.variant, wasm: w, oracle: o } : null };
        }
        case "hp": {
          const { maxHp, hp, amount } = rec;
          codec.beginCase();
          codec.wU16(DEF + 0x1c4, maxHp);
          codec.wI16(DEF + 0x1c6, hp);
          codec.wU8(DEF + 0x83, 0);
          codec.wU8(DEF + 0x4a0, 0);
          codec.wU8(STRUCT34 + 0x1f, 0);
          const audit = codec.auditReads({
            mustWrite: [[DEF + 0x1c4, 2], [DEF + 0x1c6, 2], [DEF + 0x83, 1], [DEF + 0x4a0, 1], [STRUCT34 + 0x1f, 1]],
            arenaOk: [[0x80433934, 4]],
          });
          codec.snapshotExpected();
          const lethal = ex.zz_003d344_(DEF, amount) | 0;
          const t = { hp, maxHp, prevHp: undefined };
          oracle.applyHpDamage(t, amount);
          // Declared write-backs with reference-predicted values (hp==0 => ROM no-op).
          const writeBacks = [];
          if (hp !== 0) {
            writeBacks.push({ addr: DEF + 0x1c6, bytes: [t.hp & 0xff, (t.hp >> 8) & 0xff] });
            const prev = t.prevHp ?? 0;
            writeBacks.push({ addr: DEF + 0x1c8, bytes: [prev & 0xff, (prev >> 8) & 0xff] });
          }
          const post = codec.diffPostState(writeBacks);
          const lethalOk = lethal === (hp !== 0 && t.hp === 0 ? 1 : 0);
          const cls = (lethalOk && post.writeBackMismatches.length === 0) ? "exact" : "unexplained";
          return { fn: "zz_003d344_", n: rec.n, cls, audit, post,
                   dump: cls === "unexplained" ? { n: rec.n, hp, maxHp, amount, lethal, oracle: t } : null };
        }
        case "unitb": {
          codec.beginCase();
          codec.wBytes(B1, Buffer.from(rec.b1, "base64"));
          codec.wBytes(B2 + 0x30, Buffer.from(rec.b2_30, "base64"));
          codec.wBytes(B3, Buffer.from(rec.b3, "base64"));
          codec.wI32(B4, rec.idx);
          const audit = codec.auditReads({
            mustWrite: [[B1, 0x200], [B2 + 0x30, 4], [B3, 24], [B4, 4]],
            arenaOk: [[0x802cffc8, 0x20]],
          });
          codec.snapshotExpected();
          const refOut = jsRef(B1, B2, B3, rec.idx); // reference FIRST (wasm writes DAT_803b0720)
          const hit = ex.FUN_80031634(B1, B2, B3, B4) & 1;
          const post = codec.diffPostState([]); // out-vec lands in bss DAT_803b0720, outside scratch
          let ok = hit === (refOut.hit ? 1 : 0);
          if (ok && hit) {
            for (let k = 0; k < 3; k++) ok = ok && dv.getFloat32(0x803b0720 + k * 4, true) === refOut.out[k];
          }
          const cls = ok ? "exact" : "unexplained";
          return { fn: "FUN_80031634", n: rec.n, cls, audit, post,
                   dump: cls === "unexplained" ? { n: rec.n, idx: rec.idx, hit, refHit: refOut.hit } : null };
        }
        default:
          throw new Error(`unknown fixture record kind: ${rec.kind}`);
      }
    },
  };

  // Unit-B JS reference (copied intact from the frozen PoC harness).
  function jsRef(p1, p2, p3, p4idx) {
    const rd = (a) => dv.getFloat32(a >>> 0, true);
    const chTab = (i) => (u8[0x802cffc8 + i] << 24) >> 24;
    const vsub = (a, b) => [fr(rd(a) - rd(b)), fr(rd(a + 4) - rd(b + 4)), fr(rd(a + 8) - rd(b + 8))];
    const vsubv = (a, v) => [fr(rd(a) - v[0]), fr(rd(a + 4) - v[1]), fr(rd(a + 8) - v[2])];
    const dotv = (v, b) => fr(fr(fr(fr(v[0] * rd(b))) + fr(v[1] * rd(b + 4))) + fr(v[2] * rd(b + 8)));
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
  }
}
