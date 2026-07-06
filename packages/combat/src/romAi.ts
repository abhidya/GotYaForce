// ROM-faithful CPU AI — port of the statically-isolated decision brain
// (research/decomp/cpu-ai-decode-2026-07-06.md; root zz_001c9d0_ @0x8001c9d0).
//
// The ROM AI synthesizes the actor-embedded virtual pad every frame. This port emits
// the equivalent synthetic PlayerInput into the same per-borg input slot the human
// path uses (the doc's §7 port guidance).
//
// DERIVED here (addresses in the doc):
//   - retarget cadence {4,8,10,12,15,30,45,60}f (DAT_802cfaf4) + retarget-on-death
//   - nearest-eligible target select within 20000u (squared 4e8, FUN_80025944)
//   - per-borg attack-slot RANGES + params (descriptor +0xf0..+0x104/+0x10e..+0x113,
//     the zz_002347c_ queue-range floats — data/romAiParams.json)
//   - X-press range 1000.0 (FLOAT_80436e10, AI-root case 0xa)
//   - queued-attack executor shape (zz_00234e4_): press the queued button code while
//     within the stored range, charge-holds released in range
//   - difficulty idle-cadence tables (0x802cb2f0 family: lvl0 74-86f … lvl3 34-46f)
//     pacing attack initiation (+0x328), replacing the old per-uid hash stagger
//   - level-0 attack block (+0x339 bit 0x10 via zz_001c80c_)
//   - lock-cycle debounce 30f (FUN_80025a84 +0x30f)
// TUNED / labeled (not decoded — carried from the previous AI where noted):
//   - approach/strafe/retreat WAYPOINT policy (state handlers zz_001d058_… undecoded):
//     simple approach-to-range band
//   - the attack ROULETTE weighting (selector slice logic undecoded): uniform pick over
//     nonzero-range slots; slot→button mapping structured by the +0x104→0x400 anchor
//     (slots 0-2 → B 0x200, slots 3-5 → X 0x400)
//   - dash/boost traversal + vertical hop (port-isms from the previous AI, kept)
//   - LOS gate (zz_003e978_) and terrain-probe jump (FUN_80024f64) unwired
//
// RNG: deterministic LCG per borg (zz_00055fc_ stand-in) — no Math.random.

import { distXZ } from "@gf/physics";
import { actionProfileForProfile } from "./actionProfiles.js";
import { meleeEngageRangeFor, X_CHARGE } from "./combat.js";
import { AI, MOVE } from "./constants.js";
import { exactMeleeForBorgId } from "./meleeExactData.js";
import { groundRunSpeedForBorgId } from "./movementData.js";
import { xChargeMoveForBorgId } from "./moveRuntime.js";
import type { BorgProfile } from "./stats.js";
import { emptyInput, type BorgRuntime, type PlayerInput } from "./types.js";
import romAiParamsData from "./data/romAiParams.json" with { type: "json" };

interface RomAiParams {
  retargetFrames: number[];
  idleCadence: { tierPointers: string[]; tables: Record<string, number[][]> };
  constants: Record<string, number>;
  borgs: Record<string, { attackRanges?: number[]; attackParams?: number[] }>;
}
const PARAMS = romAiParamsData as unknown as RomAiParams;
const RETARGET_FRAMES = PARAMS.retargetFrames; // {4,8,10,12,15,30,45,60}
const X_PRESS_RANGE = PARAMS.constants["xPressRange_80436e10"] ?? 1000.0;
const SEARCH_RADIUS_SQ = PARAMS.constants["searchRadiusSq_80436e88"] ?? 4e8;
const LOCK_CYCLE_DEBOUNCE = 30; // FUN_80025a84 +0x30f = 0x1e

/** Per-borg AI scratch (the actor's +0x300/+0x328/+0x32a/+0x370-block equivalents).
 *  Module-level WeakMap because cooldowns[] decays 1/frame. */
interface RomAiState {
  rng: number;
  retargetTimer: number;   // +0x32a
  idleTimer: number;       // +0x328
  queuedButton: 0 | 0x200 | 0x400; // +0x370
  queuedRange: number;     // +0x378
  burstTimer: number;      // hold-window frames (cadence2/+0x320 draw — see stepRomAI)
  lockDebounce: number;    // +0x30f
  targetUid: string | null; // +0x300 (the AI's own pick; mirrored into port lock)
}
const AI_STATE = new WeakMap<BorgRuntime, RomAiState>();

function seedFor(uid: string): number {
  let h = 2166136261;
  for (let i = 0; i < uid.length; i += 1) {
    h ^= uid.charCodeAt(i);
    h = Math.imul(h, 16777619);
  }
  return h >>> 0 || 1;
}

function stateFor(b: BorgRuntime): RomAiState {
  let s = AI_STATE.get(b);
  if (!s) {
    s = { rng: seedFor(b.uid), retargetTimer: 0, idleTimer: 0, queuedButton: 0, queuedRange: 0, burstTimer: 0, lockDebounce: 0, targetUid: null };
    AI_STATE.set(b, s);
  }
  return s;
}

/** Deterministic LCG (numerical-recipes constants) standing in for zz_00055fc_. */
function nextRand(s: RomAiState): number {
  s.rng = (Math.imul(s.rng, 1664525) + 1013904223) >>> 0;
  return s.rng;
}

function isEnemy(self: BorgRuntime, other: BorgRuntime): boolean {
  return other.alive && other.hp > 0 && other.state !== "death" && other.team !== self.team && other.uid !== self.uid;
}

/** FUN_80025944 — nearest eligible enemy within the squared search radius (4e8). */
function nearestEnemy(self: BorgRuntime, all: BorgRuntime[]): BorgRuntime | null {
  let best: BorgRuntime | null = null;
  let bestSq = SEARCH_RADIUS_SQ;
  for (const o of all) {
    if (!isEnemy(self, o)) continue;
    const dx = o.pos.x - self.pos.x;
    const dy = o.pos.y - self.pos.y;
    const dz = o.pos.z - self.pos.z;
    const sq = dx * dx + dy * dy + dz * dz;
    if (sq <= bestSq) {
      bestSq = sq;
      best = o;
    }
  }
  return best;
}

/** The borg's DERIVED attack-slot ranges (nonzero slots only) as [slotIndex, range]. */
function attackSlots(borgId: string): Array<[number, number]> {
  const rec = PARAMS.borgs[borgId];
  if (!rec?.attackRanges) return [];
  const out: Array<[number, number]> = [];
  rec.attackRanges.forEach((r, i) => {
    if (r && r > 0) out.push([i, r]);
  });
  return out;
}

export interface RomAiOptions {
  /** AI level 0-3 (the +0x439 byte): indexes the idle-cadence rows; level 0 BLOCKS
   *  attack initiation entirely (zz_001c80c_ +0x339 bit 0x10). Default 2. */
  level?: number;
  /** AI tier 0-5 (the +0x438 byte): picks the cadence table pointer. Default 0. */
  tier?: number;
}

/** Idle-cadence draw: (&PTR_802cb2f0)[tier] row [level*8 + rand&7]. */
function idleCadenceDraw(s: RomAiState, tier: number, level: number): number {
  const ptr = PARAMS.idleCadence.tierPointers[Math.max(0, Math.min(5, tier))]!;
  const table = PARAMS.idleCadence.tables[ptr];
  if (!table) return 60;
  const row = table[Math.max(0, Math.min(3, level))]!;
  return row[nextRand(s) & 7] ?? 60;
}

/**
 * One frame of ROM-architecture CPU AI. Pure against the world; owns its per-borg
 * scratch. Replaces ai.ts stepAI (which remains the fallback for borgs without
 * extracted AI params).
 */
export function stepRomAI(
  self: BorgRuntime,
  p: BorgProfile,
  all: BorgRuntime[],
  opts: RomAiOptions = {},
): PlayerInput {
  const s = stateFor(self);
  const input = emptyInput(); // (1) zero the virtual pad
  const level = opts.level ?? 2;
  const tier = opts.tier ?? 0;

  // ---- (2) target maintenance — zz_00252bc_ / zz_002532c_ ----
  if (s.lockDebounce > 0) s.lockDebounce -= 1;
  s.retargetTimer -= 1;
  const currentTarget = s.targetUid ? all.find((o) => o.uid === s.targetUid) ?? null : null;
  const targetInvalid = !currentTarget || !isEnemy(self, currentTarget);
  if (s.retargetTimer <= 0 || targetInvalid) {
    const pick = nearestEnemy(self, all);
    s.targetUid = pick?.uid ?? null;
    s.retargetTimer = RETARGET_FRAMES[nextRand(s) & 7] ?? 15;
  }
  const target = s.targetUid ? all.find((o) => o.uid === s.targetUid) ?? null : null;
  if (!target) return input;

  // Mirror the AI's pick into the port lock system: hold lockOn (the port's shared
  // source-target acquisition doubles as the ROM's +0x300 read; explicit cycle-press
  // mirroring (FUN_80025a84's 0x20/0x10) is deferred — exact 2P pairing is trace-gated).
  input.lockOn = true;
  void LOCK_CYCLE_DEBOUNCE;

  const d = distXZ(self.pos, target.pos);
  const actionProfile = actionProfileForProfile(p);
  const meleeDef = actionProfile.melee;
  const meleeEngage = meleeDef ? meleeEngageRangeFor(meleeDef) : 0;

  // ---- (4) attack: roulette pick + queued executor (zz_0021f7c_/zz_00234e4_) ----
  const slots = attackSlots(self.borgId);
  const attackBlocked = level < 1; // level-0 block (+0x339 & 0x10)
  if (s.idleTimer > 0) s.idleTimer -= 1;
  if (!attackBlocked && s.queuedButton === 0 && s.idleTimer <= 0) {
    if (slots.length > 0) {
      // Roulette: WEIGHTING undecoded — uniform over nonzero-range slots (labeled TUNED).
      // Slot→button mapping anchored by the +0x104(slot5)→0x400 evidence: 0-2 → B, 3-5 → X.
      const [slot, range] = slots[nextRand(s) % slots.length]!;
      s.queuedButton = slot >= 3 ? 0x400 : 0x200;
      s.queuedRange = range;
    } else if (d <= X_PRESS_RANGE) {
      // AI-root case 0xa inline X-press: within 1000u, press 0x400.
      s.queuedButton = 0x400;
      s.queuedRange = X_PRESS_RANGE;
    }
    // The held-B autofire tables (0x802d3970: HELD masks feed +0x5d4 autofire bits)
    // prove the ROM HOLDS attack buttons across frames — so a queued B is a held BURST,
    // its duration drawn from the second cadence table (+0x320; exact consumer
    // undecoded — structured-TUNED use of DERIVED row values, capped at 180f).
    if (s.queuedButton !== 0) {
      s.burstTimer = Math.min(180, cadence2Draw(s, tier, level));
    }
  }

  // Effective press range: the queue range is where the ROM STARTS the executor; the
  // class-byte melee state handlers (undecoded) do the actual closing, so melee-def
  // borgs press within the port's proven engage window instead of the raw queue range.
  const pressRange =
    s.queuedButton === 0x200 && meleeDef && p.rangePref !== "ranged"
      ? meleeEngage
      : s.queuedRange;

  // Wake-up i-frame whiff gate — kept from the previous AI (a port-model necessity:
  // the MELEE_IFRAME_REFRESH deadlock documented in ai.ts; TUNED).
  const exactSwing = meleeDef ? exactMeleeForBorgId(p.id) : null;
  const swingLandsBy = meleeDef ? (exactSwing ? exactSwing.activeEnd : meleeDef.startup + meleeDef.active) : 0;
  const meleeWhiffsOnIframes =
    s.queuedButton === 0x200 && meleeDef !== null && d <= meleeEngage && target.invincTimer > swingLandsBy;

  let burstDone = false;
  if (s.queuedButton !== 0) {
    const inRange = d <= pressRange;
    if (s.queuedButton === 0x200) {
      const shot = actionProfile.shot;
      if (shot?.chargeable) {
        // Charge-hold executor (3-phase +0x374 shape): hold B while closing, release
        // once charged (release-edge fires in combat.ts).
        const charged = (self.cooldowns["chargeFrames"] ?? 0) >= shot.chargeTier1Frames + 10;
        input.attack = !(charged && inRange);
        if (charged && inRange) burstDone = true;
      } else if (inRange && !meleeWhiffsOnIframes) {
        // HELD burst: keep attack down while the burst window runs (autofire/combo
        // continuation), then rest for the idle cadence.
        input.attack = true;
        s.burstTimer -= 1;
        if (s.burstTimer <= 0) burstDone = true;
      }
    } else {
      // X / 0x400 — special press-edge semantics (specialHeld latch).
      if (inRange && (self.cooldowns["special"] ?? 0) <= 0) {
        if (xChargeMoveForBorgId(self.borgId) !== null) {
          if ((self.cooldowns["xChargeFrames"] ?? 0) < X_CHARGE.TIER1_FRAMES + 10) {
            input.special = true;
          } else {
            input.special = (self.cooldowns["specialHeld"] ?? 0) <= 0;
            if (input.special) burstDone = true;
          }
        } else {
          input.special = (self.cooldowns["specialHeld"] ?? 0) <= 0;
          if (input.special) burstDone = true;
        }
      } else if (!inRange && (self.cooldowns["special"] ?? 0) > 0) {
        // Special on cooldown — abandon the queue rather than stalling the brain.
        burstDone = true;
      }
    }
    if (burstDone) {
      // Post-burst idle cadence: the DERIVED difficulty pacing (+0x328 seed). Different
      // rand draws per borg desync symmetric CPUs structurally (replaces the old
      // per-uid hash stagger for pacing; the i-frame gate above stays).
      s.queuedButton = 0;
      s.idleTimer = idleCadenceDraw(s, tier, level);
    }
  }

  // ---- (3) steering — motor DERIVED, waypoint policy TUNED (state handlers
  // zz_001d058_… undecoded, so the approach/kite band keeps the previous AI's proven
  // shape). Melee-B keeps meleeDef.range as the HOLD distance (the press gate above
  // uses the wider engage window; the sim lunge covers engage → reach — using the
  // engage range here made the CPU backstep out of its own reach mid-swing). ----
  const desired =
    meleeDef && p.rangePref !== "ranged" && (s.queuedButton === 0 || s.queuedButton === 0x200)
      ? meleeDef.range
      : s.queuedButton !== 0
        ? Math.min(pressRange, AI.RANGED_RANGE)
        : AI.RANGED_RANGE;
  const ownSpeed = groundRunSpeedForBorgId(self.borgId) ?? MOVE.GROUND_BASE + p.speed * MOVE.GROUND_PER_STAT;
  const kiteSlack = Math.max(AI.RANGE_SLACK, ownSpeed * AI.KITE_SLACK_SPEED_MULT);
  const farFromDesired = d > desired + kiteSlack;
  if (farFromDesired) {
    input.moveZ = 1; // stick toward target (54×0.8 ≈ full deflection past the 0x1e deadzone)
  } else if (d < desired - kiteSlack && !input.attack) {
    input.moveZ = -1; // never backstep while holding an attack burst
  }
  // Dash/boost traversal + vertical hop: kept port-isms (ROM dash decision undecoded;
  // terrain-probe jump FUN_80024f64 needs a collision probe the AI can't reach yet).
  if (
    farFromDesired &&
    self.grounded &&
    d > desired + ownSpeed * AI.DASH_APPROACH_SPEED_MULT &&
    (self.cooldowns["dash"] ?? 0) <= 0 &&
    (self.cooldowns["dashActive"] ?? 0) <= 0
  ) {
    input.dash = true;
  }
  if (target.pos.y - self.pos.y > 40 && self.grounded) input.jump = true;
  if (!self.grounded && farFromDesired && (self.cooldowns["boostFuel"] ?? 0) > 0) input.jump = true;

  return input;
}

/** Second-cadence draw (+0x320 seed, table family 0x802cc138) — used here as the
 *  held-burst duration (structured-TUNED application of DERIVED rows). */
function cadence2Draw(s: RomAiState, tier: number, level: number): number {
  const fam = (romAiParamsData as unknown as { cadence2: { tierPointers: string[]; tables: Record<string, number[][]> } }).cadence2;
  const ptr = fam.tierPointers[Math.max(0, Math.min(5, tier))]!;
  const table = fam.tables[ptr];
  if (!table) return 90;
  const row = table[Math.max(0, Math.min(3, level))]!;
  return row[nextRand(s) & 7] ?? 90;
}

/** True when the borg has extracted ROM AI params (195/208) — callers fall back to the
 *  legacy heuristic stepAI otherwise. */
export function hasRomAiParams(borgId: string): boolean {
  return attackSlots(borgId).length > 0;
}
