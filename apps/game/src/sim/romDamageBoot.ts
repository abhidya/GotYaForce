// romDamageBoot.ts — boot the ported GameCube damage unit into the live game.
//
// Fetches the oracle-verified damage-core wasm + DOL arena (apps/game/public/rom/),
// runs a fidelity gate — the wasm and the TS port must agree on a spread of real
// inputs BEFORE the swap — and only then installs the ROM implementation into
// sourceDamage's override seam. From that moment every damage computation in the
// game runs the ROM's own compiled code.
//
// Default ON (the 1:1 port is the product); `?romwasm=0` forces the TS port.
// Any failure — fetch, instantiate, or a fidelity mismatch — logs and leaves the
// TS port active, so the game never breaks on a bad asset.

import {
  computeBaseDamage as tsComputeBaseDamage,
  lookupTypeCategory as tsLookupTypeCategory,
  applyHpDamage as tsApplyHpDamage,
  defaultSourceDamageActor,
  defaultSourceDamageContext,
  setRomDamageImplementation,
  sourceDamageCurveCounts,
  type SourceDamageActor,
  type SourceDamageTarget,
} from "@gf/combat";
import { createRomDamageCore, type RomDamageCore } from "@gf/combat";
import { publicUrl } from "../publicUrl";

export interface RomDamageBootResult {
  active: boolean;
  detail: string;
  core?: RomDamageCore;
}

/** Deterministic PRNG so the fidelity gate checks the same cases every boot. */
function mulberry32(seed: number): () => number {
  let a = seed >>> 0;
  return () => {
    a = (a + 0x6d2b79f5) >>> 0;
    let t = a;
    t = Math.imul(t ^ (t >>> 15), t | 1);
    t ^= t + Math.imul(t ^ (t >>> 7), t | 61);
    return ((t ^ (t >>> 14)) >>> 0) / 4294967296;
  };
}

// Real borg domain (DOL remap table 0x802f2e28 row lengths, family 0..15). The
// wasm reads the contiguous DOL rows, so an out-of-domain variant over-reads
// into the NEXT family's row while the TS port clamps to 0 — a divergence that
// exists only for borgs that don't exist. The oracle's own exhaustive category
// test was these same 232 real pairs.
const REMAP_ROW_LEN = [14, 12, 16, 14, 14, 24, 44, 14, 16, 14, 12, 8, 8, 8, 6, 8];
function randBorgNumber(rnd: () => number): number {
  const family = Math.floor(rnd() * 16);
  const variant = Math.floor(rnd() * REMAP_ROW_LEN[family]!);
  return (family << 8) | variant;
}

function randActor(rnd: () => number): SourceDamageActor {
  const a = defaultSourceDamageActor(randBorgNumber(rnd));
  a.team = Math.floor(rnd() * 4);
  a.heroFlag = rnd() < 0.5 ? 0 : 1;
  a.pairAttack = rnd() < 0.15 ? 1 : 0;
  a.power = 1;
  a.maxHp = 100 + Math.floor(rnd() * 190);
  a.hp = 1 + Math.floor(rnd() * a.maxHp);
  a.handicap = Math.floor(rnd() * 7);
  a.comboRank = Math.floor(rnd() * 8);
  a.forceRatioIndex = Math.floor(rnd() * 32);
  a.sideRank = Math.floor(rnd() * 32);
  return a;
}

/** wasm vs TS on `n` deterministic cases; any disagreement blocks the swap. */
function fidelityGate(core: RomDamageCore, n: number): { ok: boolean; detail: string } {
  const rnd = mulberry32(0x6f42);
  const counts = sourceDamageCurveCounts();
  for (let i = 0; i < n; i++) {
    const att = randActor(rnd);
    const def = randActor(rnd);
    // Side energy and side rank are PER-TEAM bss slots (one value per team):
    // same-team actors must agree, or the wasm reads the shared slot while the
    // TS port reads each actor's own field — an impossible in-game input.
    if (att.team === def.team) {
      def.forceRatioIndex = att.forceRatioIndex;
      def.sideRank = att.sideRank;
    }
    const heroA = att.heroFlag ? 1 : 0;
    const heroD = def.heroFlag ? 1 : 0;
    const ctx = {
      ...defaultSourceDamageContext(),
      flagsA: rnd() < 0.2 ? 0x1000 : 0,
      flagsB: rnd() < 0.2 ? 0x4000 : 0,
      attackerHpCurveIndex: Math.floor(rnd() * counts.attHp[heroA]!),
      attackerForceCurveIndex: Math.floor(rnd() * counts.attForce[heroA]!),
      defenderDefenseCurveSelectors: [
        Math.floor(rnd() * counts.defRank[heroD]!),
        Math.floor(rnd() * counts.defHp[heroD]!),
        Math.floor(rnd() * counts.defForce[heroD]!),
      ] as [number, number, number],
      cpuHalvingEnabled: rnd() < 0.5,
    };
    // Cover FRACTIONAL basePower, not just integers: in real combat
    // combat.ts forms basePower as record.hpDamage * damageScale, and
    // damageScale is routinely fractional (combo steps 1.08/1.22, charge tiers,
    // projectile scales). An integer-only gate would certify wasm==TS while they
    // diverge on exactly the inputs that occur in play (the ROM record field is
    // u16, so the fraction is truncated on hardware and in the wasm).
    const scale = [1, 1, 1.08, 1.22, 0.5, 1.5][Math.floor(rnd() * 6)]!;
    const basePower = (1 + Math.floor(rnd() * 400)) * scale;
    const w = core.computeBaseDamage(att, def, basePower, ctx);
    const t = tsComputeBaseDamage(att, def, basePower, ctx);
    if (w !== t) {
      return { ok: false, detail: `computeBaseDamage diverged on case ${i}: wasm=${w} ts=${t}` };
    }
    const cat = randBorgNumber(rnd);
    if (core.lookupTypeCategory(cat) !== tsLookupTypeCategory(cat)) {
      return { ok: false, detail: `lookupTypeCategory diverged on 0x${cat.toString(16)}` };
    }
    const hpT: SourceDamageTarget = { hp: att.hp, maxHp: att.maxHp };
    const hpW: SourceDamageTarget = { hp: att.hp, maxHp: att.maxHp };
    const amount = Math.floor(rnd() * 300) - 20;
    tsApplyHpDamage(hpT, amount);
    core.applyHpDamage(hpW, amount);
    if (hpT.hp !== hpW.hp || hpT.prevHp !== hpW.prevHp) {
      return {
        ok: false,
        detail: `applyHpDamage diverged on case ${i}: wasm=${hpW.hp}/${hpW.prevHp} ts=${hpT.hp}/${hpT.prevHp}`,
      };
    }
  }
  return { ok: true, detail: `${n} cases agreed across all three functions` };
}

/**
 * Fetch, instantiate, fidelity-check, and install the ROM damage core.
 * Never throws: a failure leaves the TS implementation active.
 */
export async function bootRomDamage(fidelityCases = 256): Promise<RomDamageBootResult> {
  try {
    const [wasmRes, arenaRes] = await Promise.all([
      fetch(publicUrl("/rom/damage-core.wasm")),
      fetch(publicUrl("/rom/arena.json")),
    ]);
    if (!wasmRes.ok || !arenaRes.ok) {
      return { active: false, detail: `rom assets unavailable (${wasmRes.status}/${arenaRes.status})` };
    }
    const core = await createRomDamageCore(await wasmRes.arrayBuffer(), await arenaRes.json());
    const gate = fidelityGate(core, fidelityCases);
    if (!gate.ok) {
      console.error(`[rom-wasm] fidelity gate FAILED — staying on TS port: ${gate.detail}`);
      return { active: false, detail: gate.detail, core };
    }
    setRomDamageImplementation(core);
    // Expose for proof/diagnostics: window.__romDamage.callCounts shows the ROM
    // path serving real gameplay (smoke scripts and humans both read this).
    (globalThis as Record<string, unknown>).__romDamage = core;
    console.info(`[rom-wasm] damage-core LIVE — ${gate.detail}`);
    return { active: true, detail: gate.detail, core };
  } catch (error) {
    console.error("[rom-wasm] boot failed — staying on TS port:", error);
    return { active: false, detail: String(error) };
  }
}
