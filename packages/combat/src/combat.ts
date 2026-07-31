// Combat: lock-on, melee (B), ranged shot (B for ranged borgs), special (X), projectiles
// with homing, damage = f(attack/shot, defense), hitstun -> "hit", knockdown -> "down" ->
// wake with invincTimer=60 (the decomp countdown, ported exactly), cooldowns + ammo/reload.
//
// Invincibility port (behavior-notes.md s4a, struct+0x720): each frame, if timer>0 subtract
// 1.0 and clamp at 0. Entering the wake state sets it to 60. See stepInvincibility().

import {
  add,
  angleTrimByteToBam16,
  candidateTrianglesForSegment,
  clamp,
  distXZ,
  floorSurfaceYAt,
  forwardFromYaw,
  isFiniteVec,
  knockbackDirectionFromPositions,
  len,
  normalize,
  scale,
  sub,
  yawFromXZ,
  type StageCollisionTriangle,
  type Vec3,
} from "@gf/physics";
import {
  AMMO,
  CHARGE,
  COMBO,
  CONTACT_DAMAGE,
  DAMAGE,
  HEAL,
  HEAL_VAMPIRE_BORG_IDS,
  HERO_X_BUFF,
  HIT_STATUS,
  HOMING,
  KNOCKBACK,
  MASH,
  MELEE,
  MUZZLE_OFFSET,
  REACTION,
  SHOT,
  SPECIAL,
  STAGGER,
  STATE,
  DEPLOY,
  WAKE_UP_INVINCIBILITY_FRAMES,
} from "./constants.js";
import {
  DAMAGE_RECORD_INDEX,
  REACTION_FORCE_STAGGER_MASK,
  damageRecordByIndex,
  knockbackGroundSpeedForRecord,
  knockbackScaleRatio,
  knockbackVelocityForRecord,
  type DamageRecord,
} from "./gauges.js";
import {
  actionProfileForProfile,
  weaponOneCellSourceForBorgId,
  type BorgActionProfile,
  type MeleeActionDef,
  type ShotActionDef,
  type SpecialActionDef,
  type SwordBeamDef,
} from "./actionProfiles.js";
import type { BorgProfile } from "./stats.js";
import { runtimeShotPenetrationForBorgId, xChargeMoveForBorgId } from "./moveRuntime.js";
import { projectileVariant } from "./projectiles.js";
import { AttackCommandType } from "./command.js";
import {
  contextualBGatesForBorgId,
  resolveLiveCommand,
  type ContextualBGates,
} from "./commandDispatch.js";
import {
  attackHitRecordsForKind,
  attackHitTableForBorgId,
  shotFlightVisualForBorgId,
  shotHitRadiusForBorgId,
  shotKindForBorgId,
} from "./attackHitData.js";
import { familyDamageRecordForBorg } from "./familyDamageData.js";
import { exactMeleeForBorgId, type ExactMeleeAttack } from "./meleeExactData.js";
import {
  airBMoveForBorgId,
  chargeMoveForBorgId,
  comboLadderForBorgId,
  xMoveForBorgId,
  type ComboStep,
  type ExactMoveLeaf,
} from "./actionStreamData.js";
import { computeSourceDamage, forceGaugeRatioIndex } from "./damageFormula.js";
import { applyStatusFromRecord } from "./status.js";
import { creditBurstFill } from "./burst.js";
import { statusImmunityMasksForBorgId } from "./movementData.js";
import { applyActorParamTierDelta127 } from "./paramTier.js";
import { tierSizeScale } from "./timescale.js";
import type {
  BorgRuntime,
  BurstMeterState,
  Projectile,
  ProjectileVisualKind,
  RectStageBounds,
  SlotTelemetry,
  SourceTargetLockMode,
  StageCollision,
  WeaponCell,
} from "./types.js";
import projectileVisualFamilies from "./data/projectileVisualFamilies.json" with { type: "json" };
import reactionAnimLengthsData from "./data/reactionAnimLengths.json" with { type: "json" };

type ReactionAnimLengthRow = { ground?: number; launch?: number };
const REACTION_ANIM_LENGTHS = (reactionAnimLengthsData as { borgs: Record<string, ReactionAnimLengthRow> }).borgs;

export interface ProjectileContext {
  bounds: RectStageBounds;
  collision: StageCollision | null;
}

// ---------------------------------------------------------------------------------------
// TRK_memcpy — DIRECT PORT of zz_0080003488 @0x80003488 (chunk_0002.c).
// Copies `len` bytes from src to dst, incrementing both pointers and decrementing len.
// Ported as a utility for any future ROM-accurate buffer operations in the browser game.
// ---------------------------------------------------------------------------------------
export function trkMemcpy(dst: Uint8Array, src: Uint8Array, len: number): void {
  if (len <= 0) return;
  let i = 0;
  while (i < len) {
    dst[i] = src[i];
    i++;
  }
}

// ---------------------------------------------------------------------------------------
// Invincibility timer — DIRECT PORT of the decompiled countdown (behavior-notes.md s4a).
// ---------------------------------------------------------------------------------------
export function stepInvincibility(b: BorgRuntime): void {
  if (b.invincTimer > 0) {
    b.invincTimer -= 1.0; // struct+0x1dcc ~= 1.0/frame
    if (b.invincTimer <= 0) b.invincTimer = 0;
  }
}

export function isInvincible(b: BorgRuntime): boolean {
  // The +0x558 3-phase deploy lock (DEPLOY, behavior-notes.md (af)) keeps a spawning borg
  // protected for the full SPAWN_DURATION — DERIVED, replaces the old flat TUNED 45f invincTimer
  // (battle.ts now inits invincTimer=0 at spawn; the spawn STATE is the protection).
  return b.invincTimer > 0 || b.state === "spawn";
}

// ---------------------------------------------------------------------------------------
// Cooldowns — tick every named cooldown down by 1 each frame.
// ---------------------------------------------------------------------------------------
export function stepCooldowns(b: BorgRuntime): void {
  for (const k of Object.keys(b.cooldowns)) {
    const v = b.cooldowns[k] ?? 0;
  // jumpHeld / switchLockHeld / switchLockPrevHeld / allyLockHeld / hyperHeld / attackHeld / specialHeld are 0/1
    // press latches, boostFuel is a fuel gauge, chargeFrames / xChargeFrames are hold-charge
    // accumulators (hold-B shot charge and hold-X special charge respectively), comboStep is
    // the current melee-chain index, mashCount (ATK-017) is a press-edge COUNTER (not a
    // countdown timer) that combat.ts's mash-counting code owns entirely (increments on press
    // edges during an active swing, resets on swing start), and meleeAirSwing is a 0/1 latch
    // set at swing start (startMeleeAttack) recording whether THIS swing began airborne with a
    // resolved air-B leaf — read by stepAttacks' swing-resolution block for the swing's whole
    // duration even if the borg lands mid-swing — none of these decay 1/frame like the
    // countdown timers this loop drives, so all are skipped here.
    if (
      k === "jumpHeld" ||
      k === "boostFuel" ||
      k === "switchLockHeld" ||
      k === "switchLockPrevHeld" ||
      k === "allyLockHeld" ||
      k === "hyperHeld" ||
      k === "attackHeld" ||
      k === "specialHeld" ||
      k === "chargeFrames" ||
      k === "xChargeFrames" ||
      k === "comboStep" ||
      k === "mashCount" ||
      k === "meleeAirSwing"
    )
      continue;
    if (v > 0) b.cooldowns[k] = v - 1;
  }
}

// ---------------------------------------------------------------------------------------
// Ammo / weapon cells (ATK-009, findings.md mechanic P; row source
// research/decomp/data/borg-hp-stat-rows-802f2988.json, live-verified G RED/pl0615 -> ammo 5).
//
// ROM shape: 3 weapon cells (struct+0x774/+0x77c/+0x784, stride 8; aux max/refillType/
// refillParam at struct+0x78c stride 8). Weapon 0 drives the B shot path and mirrors
// BorgRuntime.ammo for compat. Weapon 1 is now bound to the X/special ammo path per the
// official B/X counter split; weapon 2 has no recovered stat-row feed and remains inert.
//
// Refill semantics (zz_006dcc0_, chunk_0009.c:2909-2973):
//   - max === 0 -> infinite: the fire gate is skipped entirely (chunk_0002.c:7158-7165), cur
//     is never decremented below 0.
//   - refillType 1 (gradual): a per-frame TUNED rate (AMMO.REFILL_RATE_PER_FRAME — the ROM's
//     real rate float at actor+0x768 has an unresolved init site and a conflicting second
//     reader, open-questions Q7) grants ammo fractionally toward max every frame; firing is
//     allowed again as soon as cur >= 1 (not gated behind a full-magazine wait).
//   - refillType <= 0 (all-at-once) or 2/3 (special, unread — treated as all-at-once): cur
//     stays 0 for the full refillParam-seeded timer, then jumps straight to max.
// ---------------------------------------------------------------------------------------

/** Build fresh weapon cells from the borg's action-profile shot def (weapon 0: ammoMax/
 *  refillType/refillParam — DERIVED per-borg where the stat row has data, TUNED_EXISTING
 *  fallback otherwise; see actionProfiles.ts weaponZeroRowOverrides) and the stat-row's
 *  weapon-1 slot (DERIVED where available via weaponOneCellSourceForBorgId — behavior-notes.md
 *  section (am) cross-check; see that function's doc for the row-layout citation). Weapon 1
 *  drives X/special ammo gating/decrement/refill in stepAttacks/startSpecialAttack. Weapon 2
 *  has no stat-row data at all (the ROM's per-borg row only carries 2 weapon segments) and
 *  stays fully inert (max 0 = infinite/unused). */
function initWeaponCells(b: BorgRuntime, p: BorgProfile): WeaponCell[] {
  const shotDef = actionProfileForProfile(p).shot;
  const max = shotDef?.ammoMax ?? 0;
  const refillType = shotDef?.refillType ?? 0;
  const refillParam = shotDef?.refillParam ?? AMMO.DEFAULT_ALL_AT_ONCE_TIMER_FRAMES;
  const weapon0: WeaponCell = {
    cur: b.ammo,
    max,
    refillType,
    refillParam,
    timer: refillType === 1 ? 0 : refillParam,
  };
  const weapon1Source = weaponOneCellSourceForBorgId(p.id, p.level);
  const weapon1: WeaponCell = weapon1Source
    ? {
        cur: weapon1Source.max, // spawn init: weapon 1 starts full and is consumed by X/special.
        max: weapon1Source.max,
        refillType: weapon1Source.refillType,
        refillParam: weapon1Source.refillParam,
        timer: weapon1Source.refillType === 1 ? 0 : weapon1Source.refillParam,
      }
    : { cur: 0, max: 0, refillType: 0, refillParam: 0, timer: 0 };
  const weapon2: WeaponCell = { cur: 0, max: 0, refillType: 0, refillParam: 0, timer: 0 };
  return [weapon0, weapon1, weapon2];
}

/** Ensure `b.weaponCells` exists (lazy self-heal for constructors/fakes that only set `ammo`
 *  — same convention as `meleeHitUids`), and keep weapon-0's `cur` mirrored with `b.ammo` so
 *  external readers of the compat alias always see a live, consistent value. Infinite cells
 *  (max <= 0, chunk_0002.c:7158-7165) mirror `b.ammo` as `Infinity` so the pre-existing
 *  `b.ammo > 0` fire-gate downstream in stepAttacks (outside this ticket's edit zone) never
 *  blocks firing and never decrements below 0 — the cell's own `cur` stays a harmless 0 since
 *  an infinite cell has no real magazine to track. */
function ensureWeaponCells(b: BorgRuntime, p: BorgProfile): WeaponCell[] {
  if (!b.weaponCells) {
    b.weaponCells = initWeaponCells(b, p);
  }
  syncAmmoAlias(b, b.weaponCells[0]);
  return b.weaponCells;
}

function syncAmmoAlias(b: BorgRuntime, weapon0: WeaponCell | undefined): void {
  if (!weapon0) return;
  if (weapon0.max <= 0) {
    b.ammo = Number.POSITIVE_INFINITY;
    return;
  }
  if (weapon0.cur !== b.ammo) weapon0.cur = b.ammo;
}

/**
 * Per-frame ammo refill (ATK-009). Advances every weapon cell's refill timer/grant and keeps
 * `b.ammo` mirrored to weapon-0's `cur` (or `Infinity` for an infinite weapon-0). Call once
 * per frame per borg (battle.ts, adjacent to stepCooldowns).
 */
export function stepAmmoRefill(b: BorgRuntime, p: BorgProfile): void {
  const cells = ensureWeaponCells(b, p);
  for (const cell of cells) {
    stepWeaponCellRefill(cell);
  }
  const weapon0 = cells[0];
  if (weapon0 && weapon0.max > 0) b.ammo = weapon0.cur;
}

function stepWeaponCellRefill(cell: WeaponCell): void {
  if (cell.max <= 0) return; // infinite ammo: no cell state to advance.
  if (cell.cur >= cell.max) return;

  if (cell.refillType === 1) {
    // Gradual: fractional grant toward max every frame (chunk_0009.c:2909-2973 sVar4===1).
    cell.cur = Math.min(cell.max, cell.cur + AMMO.REFILL_RATE_PER_FRAME);
    return;
  }

  // All-at-once (refillType <= 0) or special (2/3, unread — treated as all-at-once): cur
  // stays put until the timer counts down 1 frame/frame, then jumps straight to max.
  // refillParam is modeled as a direct frame count — behavior-notes.md section (am)'s
  // player-guide cross-check found 180/300 lining up with round 3s/5s at 60fps
  // (strong-but-unverified, not a decoded conversion formula; see
  // AMMO.DEFAULT_ALL_AT_ONCE_TIMER_FRAMES for the fallback derivation).
  if (cell.timer > 0) {
    cell.timer -= 1;
    if (cell.timer <= 0) {
      cell.timer = 0;
      cell.cur = cell.max;
    }
  } else if (cell.cur <= 0) {
    // Timer already elapsed (e.g. freshly emptied this frame) — arm a new one.
    cell.timer = cell.refillParam > 0 ? cell.refillParam : AMMO.DEFAULT_ALL_AT_ONCE_TIMER_FRAMES;
  }
}

/**
 * Deploy-return one-shot grant (ATK-009 `grantAmmo` helper): +1 to weaponIdx's cur, clamped
 * at max (zz_006de10_, +1 clamp max — chunk_0009.c:2965-2973-adjacent one-shot path). Exposed
 * for the future deploy-return wiring; nothing calls this yet (per the ticket: "nothing calls
 * it").
 */
export function grantAmmo(b: BorgRuntime, weaponIdx: number, p: BorgProfile): void {
  const cells = ensureWeaponCells(b, p);
  const cell = cells[weaponIdx];
  if (!cell) return;
  if (cell.max <= 0) return; // infinite cells have nothing to grant toward.
  cell.cur = Math.min(cell.max, cell.cur + 1);
  if (weaponIdx === 0) b.ammo = cell.cur;
}

/** Port of zz_006dbe0_: check a weapon cell and optionally consume `count` units.
 * `consume=false` is the ROM's param_4==0 query-only arm. */
export function useWeaponCell(
  b: BorgRuntime,
  p: BorgProfile,
  weaponIdx: number,
  count: number,
  consume: boolean,
): boolean {
  const cell = ensureWeaponCells(b, p)[weaponIdx];
  if (!cell) return false;
  // The browser model represents ROM cells with max<=0 as infinite/unused.
  if (cell.max <= 0) return true;
  if (cell.cur < count) return false;
  if (!consume) return true;
  cell.cur -= count;
  if (cell.refillType === 1) {
    cell.timer += cell.refillParam;
  } else if (cell.refillType <= 0) {
    if (cell.cur === 0) cell.timer = cell.refillParam;
  } else if (cell.refillType < 4) {
    cell.timer = 0;
  }
  if (weaponIdx === 0) b.ammo = cell.cur;
  return true;
}

// ---------------------------------------------------------------------------------------
// Source target lock state (R switch-lock, Z hold-ally-lock).
//
// Port target: zz_006b450_, FUN_8006b850, FUN_8006ba60, zz_006bc74_, zz_006bcf4_
// (research/decomp/ghidra-export/chunk_0009.c). Raw source pointers are represented as uids:
// actor+0x504 = target entry, +0x508 = target actor, +0x50c/+0x510/+0x514 = target position.
// DAT_803c1d7c/DAT_80436242 target-entry order is represented by BattleState.borgs order.
// Initial source acquisition picks nearest by 3D squared distance from that ordered list
// (later equal-distance entries win, matching the source <= compare); R/Z cycling advances
// through the retained source list index instead of re-sorting by distance or camera cone.
// FUN_8005a298 writes request byte +0x73c = 5 while Z is held and 4 on release; release
// restores the retained enemy lock family instead of leaving ally mode active forever.
// ---------------------------------------------------------------------------------------
function isEnemyAlive(self: BorgRuntime, o: BorgRuntime): boolean {
  return isTargetable(o) && o.team !== self.team && o.uid !== self.uid;
}

function isAllyAlive(self: BorgRuntime, o: BorgRuntime): boolean {
  return isTargetable(o) && o.team === self.team && o.uid !== self.uid;
}

function canReceiveHit(self: BorgRuntime, o: BorgRuntime): boolean {
  return isTargetable(o) && o.uid !== self.uid;
}

/** flagsB bit that EXEMPTS a hit from the T3 burst ally-passthrough rule below (the "barrier
 *  bits" exemption the doc's census found on 107/1530 records). */
const FLAGS_B_BURST_PASSTHROUGH_EXEMPT = 0x0010;

/**
 * T3 burst ally-passthrough — DERIVED (combat-feel-gaps-decode-2026-07-05.md, `zz_002fd7c_`
 * @0x8002fd7c, chunk_0003.c:8519-8525): teammates cannot hit a bursting ally. The ROM's gate is
 * "defender has +0x6fc (burstActive) set, attacker is on the SAME side, the attacker's record
 * flagsB bit 0x10 is clear, and the defender's record has no barrier bits" — the port has no
 * per-defender-record barrier-bit concept at the hit-check callsite (that's the ATTACKER's
 * record, resolved once per swing/shot), so this only ports the attacker-side flagsB 0x10
 * exemption explicitly named in the doc; a record that sets that bit still lands on a bursting
 * ally exactly like the ROM's 107/1530 exempted rows. Overturns the earlier (al) negative
 * ("no ally-passthrough exists") — this is a real, decoded rule.
 */
function burstAllyPassthroughBlocks(
  attacker: BorgRuntime,
  defender: BorgRuntime,
  record: DamageRecord,
): boolean {
  return (
    defender.burstActive === true &&
    attacker.team === defender.team &&
    attacker.uid !== defender.uid &&
    (record.flagsB & FLAGS_B_BURST_PASSTHROUGH_EXEMPT) === 0
  );
}

function isTargetable(b: BorgRuntime): boolean {
  return b.alive && b.hp > 0 && b.state !== "death";
}

interface SourceTargetEntry {
  borg: BorgRuntime;
  /** Compact index inside the filtered source target list (actor +0x73d/+0x73e). */
  sourceIndex: number;
}

export interface SourceTargetSelection {
  mode: SourceTargetLockMode;
  targetUid: string | null;
  targetIndex: number;
  sourceState: 0 | 1 | 2;
  cameraState: 2 | 3 | 4;
  changed: boolean;
}

export type SourceTargetCycleDirection = "next" | "prev";

export function ensureSourceTargetLockState(b: BorgRuntime): NonNullable<BorgRuntime["targetLockState"]> {
  if (!b.targetLockState) {
    b.targetLockState = {
      mode: "enemy",
      sourceState: b.lockTarget ? 1 : 0,
      cameraState: b.lockTarget ? 3 : 2,
      enemyIndex: -1,
      allyIndex: -1,
      activeTargetUid: b.lockTarget,
    };
  }
  return b.targetLockState;
}

export function activeSourceTargetUid(b: BorgRuntime): string | null {
  return b.targetLockState?.activeTargetUid ?? b.lockTarget ?? null;
}

export function refreshSourceTargetLock(self: BorgRuntime, all: BorgRuntime[]): SourceTargetSelection {
  const state = ensureSourceTargetLockState(self);
  if (state.mode === "ally" && targetUidStillValid(self, all, "ally", self.allyLockTarget)) {
    const entry = sourceTargetEntries(self, all, "ally").find((candidate) => candidate.borg.uid === self.allyLockTarget);
    return applySourceTarget(self, all, "ally", entry ?? null, 3);
  }

  state.mode = "enemy";
  if (targetUidStillValid(self, all, "enemy", self.lockTarget)) {
    const entry = sourceTargetEntries(self, all, "enemy").find((candidate) => candidate.borg.uid === self.lockTarget);
    return applySourceTarget(self, all, "enemy", entry ?? null, 3);
  }

  return sourceInitialEnemyLock(self, all);
}

export function sourceInitialEnemyLock(self: BorgRuntime, all: BorgRuntime[]): SourceTargetSelection {
  const entries = sourceTargetEntries(self, all, "enemy");
  return applySourceTarget(self, all, "enemy", chooseNearestSourceEntry(self, entries), 3);
}

export function sourceSwitchEnemyLock(
  self: BorgRuntime,
  all: BorgRuntime[],
  direction: SourceTargetCycleDirection = "next",
): SourceTargetSelection {
  return cycleSourceTarget(self, all, "enemy", direction);
}

export function sourceSwitchAllyLock(self: BorgRuntime, all: BorgRuntime[]): SourceTargetSelection {
  return cycleSourceTarget(self, all, "ally", "next");
}

export function sourceReleaseAllyLock(self: BorgRuntime, all: BorgRuntime[]): SourceTargetSelection {
  const state = ensureSourceTargetLockState(self);
  const previousActive = state.activeTargetUid;
  const enemyUid = self.lockTarget;
  if (targetUidStillValid(self, all, "enemy", enemyUid)) {
    const entry = sourceTargetEntries(self, all, "enemy").find((candidate) => candidate.borg.uid === enemyUid);
    if (entry) state.enemyIndex = entry.sourceIndex;
    state.mode = "enemy";
    // FUN_8006b450 request 4 restores actor+0x508 from the saved enemy actor and writes
    // actor+0x502 = 2. Keep the active target as the retained enemy uid and let the next
    // refresh promote it back to state 1 after position/state refresh.
    state.sourceState = 2;
    state.cameraState = 4;
    state.activeTargetUid = enemyUid;
    return {
      mode: state.mode,
      targetUid: state.activeTargetUid,
      targetIndex: state.enemyIndex,
      sourceState: state.sourceState,
      cameraState: state.cameraState,
      changed: previousActive !== state.activeTargetUid,
    };
  }

  state.mode = "enemy";
  return sourceInitialEnemyLock(self, all);
}

function sourceTargetEntries(
  self: BorgRuntime,
  all: BorgRuntime[],
  mode: SourceTargetLockMode,
): SourceTargetEntry[] {
  const entries: SourceTargetEntry[] = [];
  for (let listIndex = 0; listIndex < all.length; listIndex += 1) {
    const candidate = all[listIndex];
    if (!candidate) continue;
    if (mode === "enemy" ? isEnemyAlive(self, candidate) : isAllyAlive(self, candidate)) {
      entries.push({ borg: candidate, sourceIndex: entries.length });
    }
  }
  return entries;
}

function chooseNearestSourceEntry(self: BorgRuntime, entries: readonly SourceTargetEntry[]): SourceTargetEntry | null {
  let best: SourceTargetEntry | null = null;
  let bestDist = Infinity;
  for (const entry of entries) {
    const d = sourceTargetDistanceSq(self.pos, entry.borg.pos);
    if (d > bestDist) continue;
    best = entry;
    bestDist = d;
  }
  return best;
}

function sourceTargetDistanceSq(a: Vec3, b: Vec3): number {
  const dx = a.x - b.x;
  const dy = a.y - b.y;
  const dz = a.z - b.z;
  return dx * dx + dy * dy + dz * dz;
}

function cycleSourceTarget(
  self: BorgRuntime,
  all: BorgRuntime[],
  mode: SourceTargetLockMode,
  direction: SourceTargetCycleDirection,
): SourceTargetSelection {
  const entries = sourceTargetEntries(self, all, mode);
  if (entries.length === 0) return applySourceTarget(self, all, mode, null, 4);

  const currentUid = mode === "enemy" ? self.lockTarget : self.allyLockTarget;
  const currentEntryIndex = entries.findIndex((entry) => entry.borg.uid === currentUid);
  if (currentEntryIndex < 0) {
    return applySourceTarget(self, all, mode, chooseNearestSourceEntry(self, entries), 3);
  }

  const step = direction === "prev" ? -1 : 1;
  const nextIndex = (currentEntryIndex + step + entries.length) % entries.length;
  return applySourceTarget(self, all, mode, entries[nextIndex] ?? null, 4);
}

function targetUidStillValid(
  self: BorgRuntime,
  all: readonly BorgRuntime[],
  mode: SourceTargetLockMode,
  uid: string | null,
): boolean {
  if (!uid) return false;
  const target = all.find((candidate) => candidate.uid === uid);
  if (!target) return false;
  return mode === "enemy" ? isEnemyAlive(self, target) : isAllyAlive(self, target);
}

function applySourceTarget(
  self: BorgRuntime,
  all: BorgRuntime[],
  mode: SourceTargetLockMode,
  entry: SourceTargetEntry | null,
  cameraStateForValidTarget: 2 | 3 | 4,
): SourceTargetSelection {
  const state = ensureSourceTargetLockState(self);
  const previousActive = state.activeTargetUid;

  if (!entry) {
    if (mode === "enemy") {
      self.lockTarget = null;
      state.enemyIndex = -1;
    } else {
      self.allyLockTarget = null;
      state.allyIndex = -1;
    }

    const enemyStillValid = targetUidStillValid(self, all, "enemy", self.lockTarget);
    if (mode === "ally" && enemyStillValid) {
      state.mode = "enemy";
      state.sourceState = 1;
      state.cameraState = 3;
      state.activeTargetUid = self.lockTarget;
      return {
        mode: state.mode,
        targetUid: state.activeTargetUid,
        targetIndex: state.enemyIndex,
        sourceState: state.sourceState,
        cameraState: state.cameraState,
        changed: previousActive !== state.activeTargetUid,
      };
    }

    state.mode = mode;
    state.sourceState = 0;
    state.cameraState = previousActive ? 4 : 2;
    state.activeTargetUid = null;
    return {
      mode: state.mode,
      targetUid: state.activeTargetUid,
      targetIndex: state.mode === "ally" ? state.allyIndex : state.enemyIndex,
      sourceState: state.sourceState,
      cameraState: state.cameraState,
      changed: previousActive !== state.activeTargetUid,
    };
  }

  const targetUid = entry.borg.uid;
  // Camera transition state (4) models a retarget WITHIN one lock family (R re-cycling
  // enemies, or Z re-cycling allies) — it must be compared against that family's own
  // previously-retained target (+0x508 is shared, but +0x73d/+0x73e are per-family index
  // bytes, per types.ts SourceTargetLockState). Comparing against state.activeTargetUid
  // (whichever family was active last, enemy OR ally) wrongly fired a transition on the
  // FIRST-EVER acquisition of the other family (e.g. pressing Z for the first time while an
  // enemy was already R-locked): the stale enemy uid in activeTargetUid never equals the new
  // ally uid, so it always looked like a "different" target. A same-family retarget is a real
  // ROM camera transition; a family switch is a fresh lock-on (camera state 3), matching
  // sourceInitialEnemyLock's fresh-acquisition behavior above.
  const previousSameFamily = mode === "enemy" ? self.lockTarget : self.allyLockTarget;
  state.mode = mode;
  state.sourceState = 1;
  state.cameraState = previousSameFamily && previousSameFamily !== targetUid ? 4 : cameraStateForValidTarget;
  state.activeTargetUid = targetUid;
  if (mode === "enemy") {
    self.lockTarget = targetUid;
    state.enemyIndex = entry.sourceIndex;
  } else {
    self.allyLockTarget = targetUid;
    state.allyIndex = entry.sourceIndex;
  }
  return {
    mode,
    targetUid,
    targetIndex: entry.sourceIndex,
    sourceState: state.sourceState,
    cameraState: state.cameraState,
    changed: previousActive !== targetUid,
  };
}




// ---------------------------------------------------------------------------------------
// Damage application.
// Runtime combat callers use the decoded zz_003cd5c_ formula in damageFormula.ts. The legacy
// mitigate() path stays only for direct helper/test callers that do not provide an attacker
// context. The subtract-then-clamp-at-0 shape below remains DERIVED from the live HP write trace
// at object+0x1c6 (behavior-notes.md s4h).
// ---------------------------------------------------------------------------------------
function mitigate(raw: number, defenderDef: number): number {
  const mult = Math.max(DAMAGE.MIN_MULT, 1 - defenderDef * DAMAGE.DEF_PER_STAT);
  return Math.max(1, Math.round(raw * mult));
}

export interface HitSourceContext {
  attacker: BorgRuntime;
  attackerProfile: BorgProfile;
  /** Multiplier for still-unmapped hitbox/action variants. Source exact value is 1. */
  damageScale?: number | undefined;
  attackerSideRank?: number | undefined;
  defenderSideRank?: number | undefined;
  /** The attack's aimed target (ROM attack object +0xcc): projectiles bind it at spawn
   *  (Projectile.aimedTargetUid), melee/specials pass the attacker's live lock. Drives the
   *  DODGE RATIO split — hit-while-aimed (+0x410) vs stray hit (+0x414). `undefined` lets
   *  applyHit fall back to the attacker's current lock; `null` = explicitly unaimed. */
  aimedTargetUid?: string | null | undefined;
}

export interface DamageRuntimeContext {
  sideRankForTeam?: ((team: number) => number | undefined) | undefined;
  /**
   * Battle-level per-player Power Burst meter map (BattleState.burstMeterByPlayer). When
   * present, every hit CONNECTION with an attacker context credits the attacker's player
   * meter (+50 flat — Q4 T3 live traces; see BURST.FILL_PER_HIT and creditBurstFill in
   * burst.ts). Optional so legacy/synthetic callers (selfchecks, fixtures) keep compiling
   * and simply never fill.
   */
  burstMeters?: Record<string, BurstMeterState> | undefined;
  /** Battle-level Results telemetry sink (BattleState.telemetry). Hit connections credit
   *  the attacker team's damage/hits here plus the DERIVED per-slot ROM counters (see
   *  SlotTelemetry, types.ts); optional so legacy callers never count. */
  telemetry?:
    | {
        damageByTeam: Record<number, number>;
        hitsByTeam: Record<number, number>;
        attemptsByTeam: Record<number, number>;
        slots?: Record<string, SlotTelemetry>;
        firstStrikeBy?: string | null;
      }
    | undefined;
  /**
   * T4 FORCE-GAUGE: BattleState.energy/energyMax, keyed by team. When present, applyHit derives
   * attackerForceRatioIndex/defenderForceRatioIndex from the hitting sides' own team energy pool
   * via damageFormula.ts's forceGaugeRatioIndex() (idx = 32 - floor(energy*32/energyMax)).
   * Optional so legacy/synthetic callers keep the pre-T4 default (full gauge, index 0).
   */
  energyByTeam?: Record<number, number> | undefined;
  energyMaxByTeam?: Record<number, number> | undefined;
  /**
   * T4 item 3 / T2: enables the CPU-controlled ×0.5 halvings (Challenge modes 0/1, side 0 only
   * — see damageFormula.ts's attackerIsCpuSide0/defenderIsCpuSide0 doc). The doc scopes this to
   * Challenge specifically; battle.ts sets this from `cfg.challengeMode !== undefined` so Versus
   * damage stays byte-for-byte unchanged. Absent/false = no halving (pre-T4 behavior).
   */
  cpuHalvingEnabled?: boolean | undefined;
}

/** Lazily materialize a player slot's results counters (ROM actor +0x404 block). */
export function slotTelemetryFor(
  slots: Record<string, SlotTelemetry>,
  playerId: string,
): SlotTelemetry {
  return (slots[playerId] ??= {
    attempts: 0,
    hits: 0,
    incomingAimed: 0,
    hitsTakenAimed: 0,
    hitsTakenOther: 0,
    kills: 0,
    costWon: 0,
    costLost: 0,
  });
}

/** ROM damage-record flagsA bit 0x20 — "untracked" attacks: excluded from the attempt
 *  count (FUN_8008a65c chunk_0013.c:1219-1224) and from the attacker's hit count; their
 *  connections land in the victim's stray bucket +0x414 (chunk_0003.c:7894-7898). */
const FLAGS_A_STAT_UNTRACKED = 0x20;

// ---------------------------------------------------------------------------------------
// Hit-inflicted status effects — DERIVED, research/decomp/status-effects-decode-2026-07-04.md.
// All writers below port resolve_hitbox_target_effects_and_damage @0x8002e2a8's status/freeze
// block (chunk_0003.c:7621-8157) from the resolved DamageRecord's flagsA/flagsB, applied on
// every hit connection (melee + projectile, via applyHit below).
// ---------------------------------------------------------------------------------------

/** flagsB bit — discrete slow-on-hit (chunk_0003.c:8099-8107). */
const FLAGS_B_SLOW_HIT = 0x0004;
/** flagsB bit — discrete haste-on-hit (chunk_0003.c:8138-8145). */
const FLAGS_B_HASTE_HIT = 0x0008;
/** flagsB bit — contact-slow aura, reapplied per contact frame (chunk_0003.c:7653-7677). */
const FLAGS_B_SLOW_AURA = 0x0400;
/** flagsB bit — contact-haste aura (chunk_0003.c:7679-7684). */
const FLAGS_B_HASTE_AURA = 0x0800;
/** flagsB mask — normal-reaction gate for the freeze/hitstop write (chunk_0003.c:7621-7625). */
const FLAGS_B_NON_NORMAL_REACTION_MASK = 0xfc0;
/** flagsA bit — grow (chunk_0003.c:7772-7776). */
const FLAGS_A_GROW = 0x0004;
/** flagsA bit — shrink, only when the grow bit is clear (chunk_0003.c:7758-7770). */
const FLAGS_A_SHRINK = 0x0008;

/**
 * Sanity filter (report's honest caveat): many high-index familyDamageRecords rows are
 * table-extent overshoot (contradictory grow+shrink+slow+haste combos, magnitudes 128/147/255)
 * — not real design data. A record with BOTH flagsA grow (0x4) and shrink (0x8) bits set is
 * one of these corrupt rows; skip ALL status application for it (trust low-index/clean cases).
 */
function isSaneStatusRecord(record: DamageRecord): boolean {
  return (record.flagsA & (FLAGS_A_GROW | FLAGS_A_SHRINK)) !== (FLAGS_A_GROW | FLAGS_A_SHRINK);
}

/** Divers are hard-coded exempt from receiving the contact-slow aura (they project it, not
 *  receive it) — chunk_0003.c:7665-7669 id-compare. */
function isSlowAuraExempt(borgId: string): boolean {
  return (HIT_STATUS.SLOW_AURA_EXEMPT_BORG_IDS as readonly string[]).includes(borgId.toLowerCase());
}

/**
 * Apply the hit-inflicted status writes from `record`'s flagsA/flagsB to `victim` (and, for
 * freeze only, to `attacker` too). Called once per hit CONNECTION from applyHit, mirroring the
 * ROM's per-connection status block. `victimIsBurst` gates the slow-on-hit/grow-shrink guards
 * (the report's "skip if victim is burst"); haste and freeze apply regardless of burst state.
 */
function applyHitInflictedStatus(
  victim: BorgRuntime,
  record: DamageRecord,
  attacker: BorgRuntime | undefined,
): void {
  if (!isSaneStatusRecord(record)) return;

  const { immunityA, immunityB } = statusImmunityMasksForBorgId(victim.borgId);
  const victimIsBurst = victim.burstActive === true;

  // --- Discrete slow-on-hit (flagsB & 0x0004) — skip for burst victims. ------------------
  if (
    (record.flagsB & FLAGS_B_SLOW_HIT) !== 0 &&
    !victimIsBurst &&
    (immunityB & FLAGS_B_SLOW_HIT) === 0
  ) {
    victim.slowHitLevel = HIT_STATUS.DISCRETE_LEVEL;
    victim.slowHitTimer = HIT_STATUS.DISCRETE_TIMER_FRAMES;
  }

  // --- Discrete haste-on-hit (flagsB & 0x0008) — applies even to burst victims. ----------
  if ((record.flagsB & FLAGS_B_HASTE_HIT) !== 0 && (immunityB & FLAGS_B_HASTE_HIT) === 0) {
    victim.hasteHitLevel = HIT_STATUS.DISCRETE_LEVEL;
    victim.hasteHitTimer = HIT_STATUS.DISCRETE_TIMER_FRAMES;
  }

  // --- Contact-slow aura (flagsB & 0x0400) — per-contact-frame max-merge, no timer. ------
  // The shared bit 0x400 of immunityB blocks BOTH aura types.
  const auraBlocked = (immunityB & HIT_STATUS.AURA_SHARED_IMMUNITY_BIT) !== 0;
  if (
    (record.flagsB & FLAGS_B_SLOW_AURA) !== 0 &&
    !auraBlocked &&
    !isSlowAuraExempt(victim.borgId)
  ) {
    victim.slowAuraLevel = Math.max(victim.slowAuraLevel ?? 0, record.comboScoreValue);
  }

  // --- Contact-haste aura (flagsB & 0x0800) — fixed level 1. -----------------------------
  if ((record.flagsB & FLAGS_B_HASTE_AURA) !== 0 && !auraBlocked) {
    victim.hasteAuraLevel = HIT_STATUS.AURA_HASTE_LEVEL;
  }

  // --- Grow/shrink (flagsA & 0x0004 / 0x0008) — shrink only when grow bit is clear. ------
  if (!victimIsBurst) {
    const grow = (record.flagsA & FLAGS_A_GROW) !== 0;
    const shrink = !grow && (record.flagsA & FLAGS_A_SHRINK) !== 0;
    if ((grow && (immunityA & FLAGS_A_GROW) === 0) || (shrink && (immunityA & FLAGS_A_SHRINK) === 0)) {
      const signed = grow ? record.comboScoreValue : -record.comboScoreValue;
      const clamp = HIT_STATUS.SIZE_TIER_CLAMP;
      const next = Math.max(-clamp, Math.min(clamp, (victim.sizeTierDelta ?? 0) + signed));
      victim.sizeTierDelta = next;
      victim.sizeTierTimer = HIT_STATUS.SIZE_TIER_TIMER_FRAMES;
    }
  }

  // --- Freeze/hitstop (record.hitStrength, u8 +0x08) — normal-reaction hits only, BOTH parties.
  if ((record.flagsB & FLAGS_B_NON_NORMAL_REACTION_MASK) === 0) {
    const freezeFrames = record.hitStrength;
    if (freezeFrames > 0) {
      victim.freezeFrames = Math.max(victim.freezeFrames ?? 0, freezeFrames);
      if (attacker) attacker.freezeFrames = Math.max(attacker.freezeFrames ?? 0, freezeFrames);
    }
  }
}

/**
 * BAM16-per-unit conversion for the T8 knockback pitch trim (record u8+0x15, signed):
 * `combat-feel-gaps-decode-2026-07-05.md` T8 — the ROM adds `trim * -256` BAM to the computed
 * launch pitch (1 unit = 256 BAM = 1.40625 degrees, pitch itself stored negated so a POSITIVE
 * trim pitches the launch UP in FUN_8005ed38's `sin(-pitch)` sense). Converts straight to
 * radians for this port's math (2*pi/65536 per BAM, matching packages/physics/src/knockback.ts's
 * existing BAM16 convention).
 *
 * SIGN ASSUMPTION (labeled per the doc's own caveat, not Confirmed by a live trace): the doc
 * says "assert the net sign in one live trace before locking UI-level signs" — this port takes
 * the reading stated in T8's own prose (positive trim = upward pitch) since that is the only
 * sign this port can act on today; selfcheck.ts's assertPitchedKnockbackRises exists specifically
 * to make this assumption visible and easy to flip in one place if a future trace contradicts it.
 */
const BAM16_PER_TRIM_UNIT = 256;
const RADIANS_PER_BAM16 = (2 * Math.PI) / 65536;
export function knockbackPitchTrimRadians(record: DamageRecord): number {
  const trim = record.knockbackPitchTrim ?? 0;
  return trim * BAM16_PER_TRIM_UNIT * RADIANS_PER_BAM16;
}

/**
 * Reaction-anim length (frames) — DERIVED MECHANISM + DERIVED per-borg VALUE where exported.
 * The ROM gates reaction release on the reaction anim's OWN completion flag (`actor+0x1d0e`),
 * not a flat hitstun constant (T6, combat-feel-gaps-decode-2026-07-05.md). Per-borg clip
 * lengths are read from data/reactionAnimLengths.json, extracted (READ-ONLY) from the baked
 * animation banks at apps/game/public/models/pl####/anim_index.json:
 *   - ground = group 3 hit_react clip (the ground-stagger family, ROM anim slots 0xd/0xe),
 *   - launch = group 4 slot 0 down_s0 (the launch/knockdown family, FUN_8005ed38 anim
 *     0x13/0x17+dir).
 * Borgs whose bake lacks the clip (or exports a degenerate placeholder — the 23 render-frozen
 * borgs) are OMITTED and fall back to the labeled TUNED constants (REACTION.*_FALLBACK_FRAMES).
 * Coverage: 111/208 ground, 175/208 launch — the honest count of borgs with a real exported
 * reaction clip (the rest substitute/idle per PORT-1TO1-STATUS.md:859).
 */
export function reactionAnimLengthFrames(
  borgId: string,
  kind: "ground" | "launch",
): number {
  const row = REACTION_ANIM_LENGTHS[borgId.toLowerCase()];
  if (row) {
    const v = kind === "launch" ? row.launch : row.ground;
    if (typeof v === "number" && v >= 2) return v;
  }
  return kind === "launch" ? REACTION.LAUNCH_FALLBACK_FRAMES : REACTION.GROUND_STAGGER_FALLBACK_FRAMES;
}

/**
 * Apply a hit to `victim`. Respects invincibility. HP damage and knockback velocity always
 * land, but whether the victim is INTERRUPTED is decided by the DERIVED gauge-based stagger
 * model (see gauges.ts header): the original has no flat per-hit hitstun — a hit staggers
 * only via down-gauge depletion, balance-gauge break, or the damage record's reaction flags
 * (chunk_0003.c:6255-6263). On a confirmed stagger the existing reaction path runs (hitstun
 * -> "hit", big/lethal blows -> "down" -> wake). Returns dmg dealt.
 */
export function applyHit(
  victim: BorgRuntime,
  victimProfile: BorgProfile,
  rawDamage: number,
  // Per-move knockback MULTIPLIER (1 = the record's derived magnitude; 0 = no knockback).
  // The BASE magnitude is derived from the hit record's strength byte — see the knockback
  // block below. Callers must NOT pre-multiply a flat base constant in (double-counting).
  knockbackMult: number,
  knockDir: Vec3,
  fromPos: Vec3,
  forceKnockdown = false,
  // Default = melee archetype so legacy callers keep the old always-interrupt behavior.
  record: DamageRecord = damageRecordByIndex(DAMAGE_RECORD_INDEX.MELEE),
  source?: HitSourceContext,
  // Battle-level plumbing (burst meters etc.); optional so every legacy call site keeps
  // compiling. Legacy paths without `source` can never fill (the fill below requires both).
  damageContext?: DamageRuntimeContext,
): number {
  if (!isTargetable(victim) || isInvincible(victim)) return 0;

  // Contact-effect selector for the renderer (DERIVED): the record's u8 +0x09 impactEffectId is
  // what resolve_hitbox_target_effects_and_damage feeds to the impact-spark spawner zz_0019550_
  // at the contact point (chunk_0003.c:8152-8155; 0xff = spawn suppressed, :8087). Recorded on
  // every connection; the renderer maps id -> effect style (battleScene.ts spawnHitFx).
  victim.lastHitImpactEffectId = record.impactEffectId;
  victim.lastHitAttackerTeam = source?.attacker.team;
  victim.lastHitAttackerOwner = source ? source.attacker.ownerPlayer : victim.lastHitAttackerOwner;

  const dmg = source
    ? computeSourceDamage({
        attacker: source.attacker,
        attackerProfile: source.attackerProfile,
        victim,
        victimProfile,
        record,
        damageScale: source.damageScale ?? 1,
        attackerSideRank: source.attackerSideRank,
        defenderSideRank: source.defenderSideRank,
        // GUARD/40 DATA RULE (T1): the victim's static per-borg resistance mask (pldata+0xa8),
        // the SAME statusImmunityMasksForBorgId() the status-effect gate above already reads —
        // see damageFormula.ts's victimStatusImmunityA doc for the full citation.
        victimStatusImmunityA: statusImmunityMasksForBorgId(victim.borgId).immunityA,
        // T4 FORCE-GAUGE: side energy ratio, when the battle wired BattleState.energy/energyMax
        // through damageContext (see DamageRuntimeContext.energyByTeam/energyMaxByTeam doc).
        // Absent damageContext/energy data keeps the pre-T4 default (full gauge, index 0).
        attackerForceRatioIndex: forceGaugeRatioIndex(
          damageContext?.energyByTeam?.[source.attacker.team] ?? 0,
          damageContext?.energyMaxByTeam?.[source.attacker.team],
        ),
        defenderForceRatioIndex: forceGaugeRatioIndex(
          damageContext?.energyByTeam?.[victim.team] ?? 0,
          damageContext?.energyMaxByTeam?.[victim.team],
        ),
        // T4 item 3 / T2: CPU-controlled x0.5 halvings, Challenge modes 0/1, side 0 only.
        attackerIsCpuSide0:
          damageContext?.cpuHalvingEnabled === true &&
          source.attacker.team === 0 &&
          source.attacker.ownerPlayer === null,
        defenderIsCpuSide0:
          damageContext?.cpuHalvingEnabled === true && victim.team === 0 && victim.ownerPlayer === null,
      })
    : mitigate(rawDamage, victimProfile.defense);
  victim.hp -= dmg;

  // Vampire lifesteal STEAL (ATK-019, behavior-notes (ay)): a vampire (ids 0x702/0x70a) banks
  // half of every damage point it deals and drains it into its own HP, capped at max. The ROM
  // banks dmg/2 into a per-slot accumulator (chunk_0003.c:7982) then applies+caps it
  // (chunk_0003.c:6318); collapsed here to an immediate heal-on-hit (equivalent in sum). Fires
  // on the killing blow too (before the lethal-return below).
  if (HEAL.VAMPIRE_ENABLED && source && isVampireBorgId(source.attacker.borgId)) {
    const steal = Math.floor(dmg / HEAL.VAMPIRE_STEAL_DIVISOR);
    if (steal > 0 && source.attacker.alive && source.attacker.state !== "death") {
      source.attacker.hp = Math.min(source.attacker.maxHp, source.attacker.hp + steal);
    }
  }

  // Power Burst meter fill (Q4 RESOLVED 2026-07-03, T3 live traces — research/decomp/
  // attack-mechanics-open-questions.md Q4 lines 59-74, findings §S): +50 per hit CONNECTION,
  // credited to the ATTACKER'S player only, flat/damage-independent. applyHit runs once per
  // connection per victim, matching the ROM's per-connection semantics (a penetrating beam
  // through a dead husk credited 3 x 50). Placed BEFORE the lethal early-return below so the
  // killing blow's connection also credits (the ROM counts connections, and dead borgs still
  // register hits per the husk trace). The victim is never credited ("none of the other three
  // players' meters moved"); source-less legacy calls never fill (no attacker to credit —
  // `source &&` is the structural assert). CPU attackers: see creditBurstFill (burst.ts).
  if (source && damageContext?.burstMeters) {
    creditBurstFill(damageContext.burstMeters, source.attacker.ownerPlayer);
  }

  // Results telemetry: every hit CONNECTION with an attacker context credits the attacker
  // team's damage/hit counters (attempts are counted by the battle step loop at attack
  // initiation). Same placement rationale as the burst fill above — the killing blow counts.
  if (source && damageContext?.telemetry) {
    const t = damageContext.telemetry;
    const team = source.attacker.team;
    t.damageByTeam[team] = (t.damageByTeam[team] ?? 0) + dmg;
    t.hitsByTeam[team] = (t.hitsByTeam[team] ?? 0) + 1;

    // DERIVED per-slot results counters — hit-resolver accounting, resolve_hitbox_target_
    // effects_and_damage @0x8002e2a8 (chunk_0003.c:7834-7898), decoded in
    // research/decomp/results-scoring-decode-2026-07-04.md:
    //  - cross-team + tracked record  -> attacker hits (+0x408); victim splits into
    //    hit-while-aimed (+0x410, the attack's target was the victim) vs stray (+0x414).
    //  - untracked record (flagsA 0x20) or same-team -> victim stray bucket only.
    //  - first cross-team hit of the battle stamps the attacker's first-strike flag
    //    (+0x436 / DAT_80436128) worth 5000 on the results screen.
    // Port deviation (documented): the ROM counts one hit per (attack event, victim) via a
    // per-event victim bitmask (+0x2ad); the port counts connections. Today's callers only
    // diverge for persisting rehit beams (consumeOnHit === false), which no gameplay caller
    // sets yet.
    if (t.slots) {
      const crossTeam = victim.team !== source.attacker.team;
      const tracked = (record.flagsA & FLAGS_A_STAT_UNTRACKED) === 0;
      // First strike is claimed on ANY cross-team connection — the ROM's gate
      // (chunk_0003.c:7883-7886) sits BEFORE the tracked/dedup split.
      if (crossTeam && t.firstStrikeBy === undefined) {
        t.firstStrikeBy = source.attacker.ownerPlayer;
      }
      if (crossTeam && tracked && source.attacker.ownerPlayer !== null) {
        slotTelemetryFor(t.slots, source.attacker.ownerPlayer).hits += 1;
      }
      if (victim.ownerPlayer !== null) {
        const vs = slotTelemetryFor(t.slots, victim.ownerPlayer);
        const aimedUid =
          source.aimedTargetUid !== undefined
            ? source.aimedTargetUid
            : activeSourceTargetUid(source.attacker);
        if (crossTeam && tracked && aimedUid === victim.uid) {
          vs.hitsTakenAimed = Math.min(vs.hitsTakenAimed + 1, vs.incomingAimed);
        } else {
          vs.hitsTakenOther += 1;
        }
      }
    }
  }

  // Hit-inflicted status effects (DERIVED, status-effects-decode-2026-07-04.md; see the
  // applyHitInflictedStatus block above applyHit): slow/haste (discrete + aura), grow/shrink,
  // and freeze all resolve off THIS record's flagsA/flagsB on every hit connection, including
  // the killing blow (freeze applies to the ATTACKER too, and a dead victim's fields are
  // harmless to write). Runs before the lethal early-return below so attacker-side freeze
  // always lands.
  applyHitInflictedStatus(victim, record, source?.attacker);

  // Knockback DIRECTION — ROM-accurate port of zz_00300bc_ (0x800300bc), mode 1 ("attacker to
  // target" relative-position vector -> atan2 -> BAM16 yaw), the only one of the ROM's 5 vector-
  // source modes this port has enough data to compute (see packages/physics/src/knockback.ts
  // header and behavior-notes.md section (p) for the other 4 modes and why they're not wired).
  // `knockDir` lets a caller override with a more specific vector (e.g. a projectile's travel
  // direction) when the "attacker position" isn't the right source (fromPos is still passed as
  // the attacker-position input to the mode-1 calc either way).
  // T8 ANGLE TRIMS (yaw half): record byte +0x14 (knockbackYawTrim), converted the same way the
  // ROM does (byte * -0x100 -> BAM16, angleTrimByteToBam16) and only applied on the mode-1
  // attacker->target path (a caller-supplied knockDir override bypasses the whole BAM16 angle
  // calc, so there is no yaw to trim there — unchanged from before T8). Yaw trims are rare in
  // the census (mostly ±128 = 180 degrees, "launch away-side") but wired for real now rather
  // than hardcoded to 0.
  const yawTrimBam16 = angleTrimByteToBam16(record.knockbackYawTrim ?? 0);
  const dir =
    knockDir.x === 0 && knockDir.z === 0
      ? knockbackDirectionFromPositions(fromPos, victim.pos, yawTrimBam16)
      : normalize(knockDir);

  // Knockdown determination moved up (was computed after the knockback block below): the T6
  // ground-vs-launch table SELECTION depends on it (a launch reaction uses the pitch-split
  // FUN_8005ed38 table; a ground stagger uses the flat zz_005ec20_ table), so it must be known
  // before the knockback magnitude is picked. Value/order unchanged from the original — only
  // moved earlier.
  const knockdown = forceKnockdown || dmg >= DAMAGE.KNOCKDOWN_DMG;
  // T8 ANGLE TRIMS: a record with a nonzero pitch trim wants a real pitched arc even on a
  // ground-reaction hit (893/1530 records carry the modal (0,24) ~=33.75-degree-up trim) — see
  // combat-feel-gaps-decode-2026-07-05.md T8. Treat "has a pitch trim" as an additional launch
  // trigger so those records get the pitched FUN_8005ed38 table instead of the flat ground one.
  const pitchTrimUnits = record.knockbackPitchTrim ?? 0;
  const useLaunchTable = knockdown || pitchTrimUnits !== 0;

  // Knockback MAGNITUDE + INTEGRATION MODEL — DERIVED, T6 (combat-feel-gaps-decode-2026-07-05.md,
  // replacing the earlier flat-table-only T9 read). Two ROM reaction families, selected by
  // useLaunchTable above:
  //   - GROUND (zz_005ec20_): idx*7 horizontal-only table (gauges.ts
  //     knockbackGroundSpeedForRecord), scaled by the T5 attacker/victim SIZE-SCALE RATIO
  //     (timescale.ts tierSizeScale — DERIVED end-to-end; ×1.0 at default tier, diverges under
  //     grow/shrink status + hero X buff). Decel is -speed/20 (REACTION.
  //     GROUND_DECEL_FRAMES), integrated per-frame in movement.ts while state is a ground
  //     reaction — see reactionDecelFramesRemaining below.
  //   - LAUNCH (FUN_8005ed38): (idx+1)*8 table (gauges.ts knockbackVelocityForRecord, the
  //     table this port already had), split by the T8 pitch trim into horizontal/vertical
  //     components, decel -0.1/frame horizontal, gravity -1.2/frame (REACTION.LAUNCH_DECEL/
  //     LAUNCH_GRAVITY) for the reaction's duration.
  // Both keep KNOCKBACK.PORT_SCALE (1.0, raw-scale anchor) and the caller's per-move multiplier.
  // T5 size-scale (combat-feel-gaps-decode-2026-07-05.md §T5): ctx+0xc4 (attacker) /
  // victim+0xb4 are the actor SIZE-SCALE floats, init by zz_0056180_ (chunk_0006.c:8250-8293)
  // from the param-tier table row [sizeScale,...] (data/paramTierTables.json 0x802dd5a0) at the
  // effective tier (paramTier.tier + sizeTierDelta, both on BorgRuntime). timescale.ts
  // tierSizeScale() is the full DERIVED chain: ×1.0 at the default tier 16 for EVERY borg (no
  // per-borg base variation exists at spawn; actor+0x3ec is the LEVEL byte that feeds HP/ammo
  // row select + force cost — NOT a size/scale class — so PORT-1TO1-STATUS.md:753's "+0x3ec is
  // size/scale class 0-4" is STALE, resolved by the T5 decode). The ratio diverges under
  // grow/shrink hit-status (sizeTierDelta, the _63 path) or the STAR/PLANET HERO X +4-tier
  // self-buff (applyActorParamTierDelta127). Projectiles inherit the owner's scale at spawn
  // (chunk_0006.c:2472-2478), so the attacker's CURRENT scale is the right input for in-flight
  // shots too. No separate BorgRuntime.sizeScale field is added — it would duplicate
  // tierSizeScale(b) which already reads paramTier.tier (the +0xb4/+0xc4 source).
  const attackerScale = source?.attacker ? tierSizeScale(source.attacker) : 1;
  const victimScale = tierSizeScale(victim);
  const scaleRatio = knockbackScaleRatio(attackerScale, victimScale);
  const baseSpeed = useLaunchTable
    ? knockbackVelocityForRecord(record)
    : knockbackGroundSpeedForRecord(record, scaleRatio);
  const knockback = baseSpeed * KNOCKBACK.PORT_SCALE * knockbackMult;

  if (useLaunchTable) {
    // Pitch split (FUN_8005ed38): h = s*cos(-pitch), v = s*sin(-pitch), where "pitch" is the
    // ROM's STORED pitch field (+0x282) — which the doc says is "itself stored negated" versus
    // the conceptual/UI-facing angle. knockbackPitchTrimRadians() returns the trim in the
    // conceptual sense the doc states in plain English ("positive trim pitches the launch UP"):
    // stored = -conceptual, so sin(-stored) = sin(conceptual) — a positive trim yields positive
    // vel.y directly (the two negations cancel; written out here rather than simplified away so
    // the ROM's own -pitch shape stays visible next to this port's sign choice). (SIGN
    // ASSUMPTION, per knockbackPitchTrimRadians's own doc — labeled, not Confirmed by a live
    // trace.) A trimless forced knockdown (pitch trim 0) falls back to the port's old flat
    // KNOCKDOWN_POP so pre-T8 callers without trim data still read as a launch.
    const conceptualPitch = knockbackPitchTrimRadians(record);
    const storedPitch = -conceptualPitch;
    const cosP = Math.cos(-storedPitch);
    const sinP = Math.sin(-storedPitch);
    victim.vel.x = dir.x * knockback * cosP;
    victim.vel.z = dir.z * knockback * cosP;
    if (knockback > 0 && pitchTrimUnits !== 0) {
      victim.vel.y = knockback * sinP;
    } else if (knockback > 0 && forceKnockdown) {
      // Fallback for trimless forced knockdowns (T8 recipe: "keep the pop only as fallback for
      // trimless forced knockdowns") — the old TUNED vertical pop.
      victim.vel.y = Math.max(victim.vel.y, KNOCKBACK.KNOCKDOWN_POP);
    }
    victim.reactionDecelFramesRemaining = undefined; // launch uses the fixed LAUNCH_DECEL/frame, not a frames-to-stop denominator
    victim.reactionKind = "launch";
  } else {
    victim.vel.x = dir.x * knockback;
    victim.vel.z = dir.z * knockback;
    // Standard ground knockback vertical is DERIVED ZERO (FLOAT_80437444 = 0.0) — falls under
    // normal gravity, no special vertical handling for the ground family.
    // Ground-family decel denominator (T6): h-accel = -speed/20, i.e. it stops in exactly
    // REACTION.GROUND_DECEL_FRAMES frames regardless of the initial speed. movement.ts reads
    // this each frame while the reaction is active.
    victim.reactionDecelFramesRemaining = REACTION.GROUND_DECEL_FRAMES;
    victim.reactionKind = "ground";
  }

  if (victim.hp <= 0) {
    victim.hp = 0;
    enterDeath(victim);
    return dmg;
  }

  // --- Gauge-based stagger model (DERIVED — see gauges.ts header) -----------------------
  // Every non-lethal hit arms the three 60-frame post-hit windows (all FLOAT_80436fac,
  // chunk_0003.c:7995-8010); they tick down in stepGaugeWindows() while out of a reaction.
  victim.balanceRefillDelay = STAGGER.BALANCE_REFILL_DELAY;
  victim.downResetDelay = STAGGER.DOWN_RESET_DELAY;
  victim.comboWindow = STAGGER.COMBO_WINDOW;

  // Down-gauge damage (record u16+0x02; the ROM scales it x(1+0.5*(attackerLevel-1)) —
  // x1 at the port's default level 0/1). Out of a reaction the ROM subtracts
  // unconditionally (chunk_0003.c:8002); while IN a hit reaction it only re-depletes when
  // the hit's down damage reaches the victim's base (:8004-8006, level-1 form) — the
  // juggle limiter.
  const inReaction = victim.state === "hit" || victim.state === "down";
  if (!inReaction || record.downGaugeDamage >= victim.downGaugeBase) {
    victim.downGauge -= record.downGaugeDamage;
  }

  // Balance-gauge damage (record u8+0x04). Depletion refills the gauge to max IMMEDIATELY,
  // resets the combo counters, and flags the forced stagger (0x6fd |= 0xa6) —
  // chunk_0003.c:8011-8019.
  let balanceBroke = false;
  victim.balanceGauge -= record.balanceGaugeDamage;
  if (victim.balanceGauge < 1) {
    victim.balanceGauge = victim.balanceGaugeMax;
    victim.comboAccum = 0;
    victim.comboRank = 0;
    balanceBroke = true;
  }

  // Combo accumulator (+0x6c8, chunk_0003.c:8021-8029): add the record's combo score; past
  // 99 the accumulator wraps to 0 and the rank byte (+0x6ca) increments, capped at 0x3f.
  // GUARD/40 DATA RULE (T1) exemption: a blast-flagged record (flagsA & 0x1000) skips combo
  // score entirely (chunk_0003.c:7934) — "blast hits teammates at full damage and awards
  // nothing", per the doc.
  if ((record.flagsA & 0x1000) === 0) {
    victim.comboAccum += record.comboScoreValue;
    if (victim.comboAccum > 99) {
      victim.comboAccum = 0;
      victim.comboRank = Math.min(0x3f, victim.comboRank + 1);
    }
  }

  // Status-effect application (ATK-010 shell, chunk_0003.c:7638-7651): today's 3 archetype
  // DamageRecords carry no status bytes, so statusId is always 0 here — the parameter exists
  // for a future per-move hit-record. See status.ts; NO gameplay effect is applied.
  applyStatusFromRecord(victim, 0, 0);

  // Stagger gate (chunk_0003.c:6255-6263): the hit interrupts the victim ONLY when the down
  // gauge dropped below 1, the balance gauge broke, or the record's reaction flags force it
  // (byte +0x0b bits 2|0x80). Otherwise the victim keeps acting normally — the ROM routes
  // straight to dispatch_slot_action_update: HP damage and the knockback velocity above
  // still land, but there is NO hitstun and NO state change.
  const staggered =
    victim.downGauge < 1 ||
    balanceBroke ||
    (record.reactionFlags & REACTION_FORCE_STAGGER_MASK) !== 0;
  if (!staggered) return dmg;

  // Stagger entry: reset the down gauge to base (zz_003d3e8_, chunk_0004.c:6866-6876 —
  // +50%/level, x1 at the port's default level).
  victim.downGauge = victim.downGaugeBase;
  // DERIVED — the 60 stagger i-frames are BALANCE-BREAK ONLY: zz_005c290_ gates the
  // +0x720 = FLOAT_80437448 (60.0) write on the balance-depletion flag (0x6fd & 0x80,
  // chunk_0007.c:3985-4050; the 0xa6 mask including 0x80 is set at chunk_0003.c:8011-8019).
  // Flag-forced staggers (record byte +0x0b, e.g. every melee hit) and down-gauge staggers
  // do NOT grant them — otherwise melee chains would be throttled to one damaging hit per
  // stagger, which is neither the ROM's behavior nor the game's feel.
  if (balanceBroke) {
    victim.invincTimer = Math.max(victim.invincTimer, STAGGER.STAGGER_IFRAMES);
  }

  // Reaction LENGTH — T6 DERIVED MECHANISM (combat-feel-gaps-decode-2026-07-05.md): the ROM
  // holds the victim in its reaction handler until the reaction ANIM completes
  // (`actor+0x1d0e` flag), not for a flat hitstun constant. `reactionAnimLengthFrames` below is
  // the single seam for that: it returns a real per-borg reaction-clip length where one is
  // exported, else the labeled TUNED fallback (REACTION.GROUND_STAGGER_FALLBACK_FRAMES /
  // LAUNCH_FALLBACK_FRAMES) — see that function's own header for why no real per-borg length
  // exists in this port yet. `knockdown`/`useLaunchTable` (computed above, before the knockback
  // block) already carry the launch-vs-ground selection, so the SAME condition picks the
  // matching reaction-anim family here.
  if (knockdown) {
    enterDown(victim, reactionAnimLengthFrames(victim.borgId, "launch"));
  } else {
    enterHit(victim, reactionAnimLengthFrames(victim.borgId, useLaunchTable ? "launch" : "ground"));
  }
  return dmg;
}

// ---------------------------------------------------------------------------------------
// Healing & lifesteal shells (ATK-019, REWRITTEN after behavior-notes.md (an) corrected the
// (al)-era misread of chunk_0003.c:6318-6323 as nurse healing — that site is VAMPIRE
// LIFESTEAL, gated on ids 0x702/0x70a). Two independently-flagged, currently-disabled
// mechanisms; see constants.ts HEAL for the evidence/citations.
// ---------------------------------------------------------------------------------------

/**
 * Apply a flat HP heal to `b`. Clamps to maxHp, is a no-op on a dead/departed borg (hp <= 0 or
 * state "death" — healing never revives), and never routes through applyHit/mitigate/the
 * damage formula (ATK-019 "Do not change": healing is a dedicated HP-increment path in the
 * ROM, not a damage-formula effect — behavior-notes.md (al)). Returns the ACTUAL amount
 * healed (may be less than `amount` if clamped by maxHp, or 0 if the no-op guard applies).
 */
export function applyHeal(b: BorgRuntime, amount: number): number {
  if (b.hp <= 0 || b.state === "death") return 0;
  if (amount <= 0) return 0;
  const healed = Math.min(amount, b.maxHp - b.hp);
  if (healed <= 0) return 0;
  b.hp += healed;
  return healed;
}

/** True for the two vampire-lifesteal borg ids (0x702 Vampire Knight, 0x70a Vlad). */
export function isVampireBorgId(borgId: string): boolean {
  return (HEAL_VAMPIRE_BORG_IDS as readonly string[]).includes(borgId);
}

/**
 * Vampire passive self-BLEED (ATK-019, behavior-notes (ay)). For a vampire borg (ids
 * 0x702/0x70a), lose 1 HP every HEAL.VAMPIRE_BLEED_INTERVAL_FRAMES (30) frames, floored at
 * 1 HP so it never self-kills — the ROM drain loop chunk_0006.c:7900-7912 (`if 1 < HP: HP -= 1`
 * every 0x1e frames). The steal half of the mechanic is applied in applyHit. Gate (T
 */
