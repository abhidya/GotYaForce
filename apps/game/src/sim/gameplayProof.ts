// Deterministic gameplay proofs for the browser smoke (scripts/smoke-browser-game.mjs).
//
// Each helper builds its own throwaway @gf/combat Battle from the SHIPPED bundle — the
// exact simulation code the live game runs, including the ROM-wasm damage seam when
// romDamageBoot has installed it (setRomDamageImplementation is module-global, so these
// battles compute damage through window.__romDamage exactly like the live session).
// They never touch the live battle/session; the smoke calls them through
// window.__gf.selfcheck to prove input → attack → damage, bounds clamping, and the
// jump/gravity arc inside the real production bundle.

import { createBattle, emptyInput, type Battle, type PlayerInput } from "@gf/combat";
import { BORG_CATALOG } from "./borgCatalog.js";
import { SOURCE_FRAME_SECONDS } from "../constants.js";

/** The proofs step the sim at its real fixed rate, exactly like the live battle loop. */
const DT = SOURCE_FRAME_SECONDS;
const SPAWN_SETTLE_FRAMES = 130; // both sides fully deployed + idle (spawn state ends ~35f)

interface ProofActors {
  battle: Battle;
  inputs: Record<string, PlayerInput>;
}

/** Two-force fixture: the probed borg (p1, team 0) vs a stationary dummy-owned pl0008
 *  (p2, team 1, fed empty input so no AI drives it), `separation` units apart. */
function proofBattle(borgId: string, separation: number, bounds = 4000): ProofActors {
  const battle = createBattle(
    {
      stageId: "st00",
      forces: [
        { team: 0, ownerPlayer: "p1", borgIds: [borgId] },
        { team: 1, ownerPlayer: "p2", borgIds: ["pl0008"] },
      ],
      bounds: { x: bounds, z: bounds },
      spawnPoints: [
        { pos: { x: 0, y: 10, z: 0 } },
        { pos: { x: 0, y: 10, z: separation } },
      ],
    },
    BORG_CATALOG.combatStats,
  );
  const inputs: Record<string, PlayerInput> = { p1: emptyInput(), p2: emptyInput() };
  for (let f = 0; f < SPAWN_SETTLE_FRAMES; f += 1) battle.step(DT, inputs);
  return { battle, inputs };
}

function foeHp(battle: Battle): number {
  return battle.observe().actors.find((a) => a.team === 1)?.hp ?? 0;
}

export interface AttackDamageProof {
  borgId: string;
  /** HP the dummy lost to the held B attack (0 = attack never connected). */
  attackDamage: number;
  /** HP the dummy lost to X-special presses (0 = special never connected). */
  specialDamage: number;
}

/** Prove B-attack and X-special each deal damage for every borg id given.
 *  Close-range fixture (inside melee engage) with lock-on held, mirroring a player
 *  walking up to an enemy and holding the attack button. */
export function proveAttackDamage(
  borgIds: readonly string[] = ["pl0615", "pl0102", "pl0008"],
  maxFrames = 900,
): AttackDamageProof[] {
  return borgIds.map((borgId) => {
    // B attack: hold-40 / release-20 cycles with lock — the hold covers plain melee/shot
    // borgs and accumulates charge for chargeable-B borgs, and the RELEASE is what fires
    // a charged shot (holding forever would legitimately never fire one).
    const atk = proofBattle(borgId, 150);
    const atkHp0 = foeHp(atk.battle);
    let attackDamage = 0;
    for (let f = 0; f < maxFrames; f += 1) {
      atk.inputs.p1 = { ...emptyInput(), attack: f % 60 < 40, lockOn: true };
      atk.battle.step(DT, atk.inputs);
      if (f % 10 === 0 || f === maxFrames - 1) {
        attackDamage = atkHp0 - foeHp(atk.battle);
        if (attackDamage > 0) break;
      }
    }

    // X special: the same hold-40 / release-20 cycle (fires tap specials on the press
    // edge and X-charge moves on the release edge). Close-range fixture (60 units): the
    // probed borgs' X moves are close-quarters strikes whose hit windows do not reach a
    // 150-unit standoff.
    const sp = proofBattle(borgId, 60);
    const spHp0 = foeHp(sp.battle);
    let specialDamage = 0;
    for (let f = 0; f < maxFrames; f += 1) {
      sp.inputs.p1 = { ...emptyInput(), special: f % 60 < 40, lockOn: true };
      sp.battle.step(DT, sp.inputs);
      if (f % 10 === 0 || f === maxFrames - 1) {
        specialDamage = spHp0 - foeHp(sp.battle);
        if (specialDamage > 0) break;
      }
    }
    return { borgId, attackDamage, specialDamage };
  });
}

export interface BoundsClampProof {
  bound: number;
  /** Farthest |x| reached while holding right for `frames` frames. */
  maxAbsX: number;
  /** Lowest y reached — must never sink below the fallback ground plane. */
  minY: number;
  clamped: boolean;
}

/** Prove a unit driven at the arena edge is clamped inside the stage bounds and never
 *  falls out of the world. */
export function proveBoundsClamp(bound = 1000, frames = 1200, borgId = "pl0008"): BoundsClampProof {
  const { battle, inputs } = proofBattle(borgId, 3000, bound);
  let maxAbsX = 0;
  let minY = Number.POSITIVE_INFINITY;
  for (let f = 0; f < frames; f += 1) {
    inputs.p1 = { ...emptyInput(), moveX: 1 };
    battle.step(DT, inputs);
    if (f % 5 !== 0) continue;
    const me = battle.observe().actors.find((a) => a.team === 0);
    if (!me) break;
    maxAbsX = Math.max(maxAbsX, Math.abs(me.pos.x));
    minY = Math.min(minY, me.pos.y);
  }
  return { bound, maxAbsX, minY, clamped: maxAbsX <= bound + 1e-6 && minY >= 0 };
}

export interface JumpArcProof {
  baseY: number;
  peakY: number;
  rose: boolean;
  landed: boolean;
}

/** Prove the jump arc: press A, rise off the ground, then gravity lands the borg back
 *  on its takeoff surface. */
export function proveJumpArc(borgId = "pl0008", settleFrames = 600): JumpArcProof {
  const { battle, inputs } = proofBattle(borgId, 3000);
  const me = () => battle.observe().actors.find((a) => a.team === 0);
  const baseY = me()?.pos.y ?? 0;
  let peakY = baseY;
  for (let f = 0; f < 20; f += 1) {
    inputs.p1 = { ...emptyInput(), jump: true };
    battle.step(DT, inputs);
    peakY = Math.max(peakY, me()?.pos.y ?? baseY);
  }
  let landed = false;
  for (let f = 0; f < settleFrames; f += 1) {
    inputs.p1 = emptyInput();
    battle.step(DT, inputs);
    const b = me();
    if (!b) break;
    peakY = Math.max(peakY, b.pos.y);
    if (b.grounded && Math.abs(b.pos.y - baseY) < 1.5) {
      landed = true;
      break;
    }
  }
  return { baseY, peakY, rose: peakY > baseY + 10, landed };
}
