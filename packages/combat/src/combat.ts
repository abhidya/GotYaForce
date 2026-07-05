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

export interface ProjectileContext {
  bounds: RectStageBounds;
  collision: StageCollision | null;
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
  return b.invincTimer > 0;
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
 * Reaction-anim length (frames) — T6 DERIVED MECHANISM, TUNED VALUE (see REACTION.*_FALLBACK_
 * FRAMES in constants.ts for the full citation). The ROM gates reaction release on the
 * reaction anim's OWN completion flag (`actor+0x1d0e`), not a flat hitstun constant — but this
 * port's asset pipeline does not export per-borg reaction-clip lengths (no renderer/mot-length
 * data reaches packages/combat, which is intentionally renderer-agnostic). This function is the
 * SINGLE seam: it currently always returns the labeled TUNED fallback, but every call site
 * already goes through it, so wiring a real per-borg reaction-clip length table later is a
 * one-function change, not a call-site hunt.
 */
export function reactionAnimLengthFrames(
  _borgId: string,
  kind: "ground" | "launch",
): number {
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
  //     knockbackGroundSpeedForRecord), scaled by the T5 attacker/victim SCALE RATIO (both 1.0
  //     today — no size pipeline wired yet, so this is a documented no-op multiply, not a
  //     hardcoded skip: gauges.ts knockbackScaleRatio()). Decel is -speed/20 (REACTION.
  //     GROUND_DECEL_FRAMES), integrated per-frame in movement.ts while state is a ground
  //     reaction — see reactionDecelFramesRemaining below.
  //   - LAUNCH (FUN_8005ed38): (idx+1)*8 table (gauges.ts knockbackVelocityForRecord, the
  //     table this port already had), split by the T8 pitch trim into horizontal/vertical
  //     components, decel -0.1/frame horizontal, gravity -1.2/frame (REACTION.LAUNCH_DECEL/
  //     LAUNCH_GRAVITY) for the reaction's duration.
  // Both keep KNOCKBACK.PORT_SCALE (1.0, raw-scale anchor) and the caller's per-move multiplier.
  const attackerScale = source?.attacker.paramTier ? 1 : 1; // T5: no size-scale field on
  // BorgRuntime yet (paramTier is velocity/anim-rate tier, NOT the size-scale float chain —
  // see T5's ctx+0xc4/victim+0xb4 chain). Both sides are honestly 1.0 until that pipeline
  // exists; the ratio call below is still made for real so wiring a real scale later is a
  // one-line change at the call site, not a new code path.
  const victimScale = 1;
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
 * every 0x1e frames). The steal half of the mechanic is applied in applyHit. Gate (TUNED): the
 * ROM keys the loop on state bytes +0x18==1/+0x19==2; the port bleeds whenever the vampire is
 * alive and out of the death/spawn states (the guide frames the drain as constant passive
 * behavior). No-op for non-vampires and while VAMPIRE_ENABLED is false. Called once per frame
 * from battle.ts. Uses the cooldowns map (`vampBleedFrames`) for the cadence counter — no new
 * runtime field.
 */
export function stepVampireDrain(b: BorgRuntime): void {
  if (!HEAL.VAMPIRE_ENABLED) return;
  if (!isVampireBorgId(b.borgId)) return;
  if (!b.alive || b.state === "death" || b.state === "spawn") return;
  const next = (b.cooldowns["vampBleedFrames"] ?? 0) + 1;
  if (next >= HEAL.VAMPIRE_BLEED_INTERVAL_FRAMES) {
    b.cooldowns["vampBleedFrames"] = 0;
    if (b.hp > 1) b.hp -= 1;
  } else {
    b.cooldowns["vampBleedFrames"] = next;
  }
}

// ---------------------------------------------------------------------------------------
// Post-hit gauge windows — DERIVED port of the per-frame decrement (chunk_0006.c:7982-8011):
// while the victim is NOT in a hit reaction (ROM 0x5e0 bit 0x1000000; our "hit"/"down"
// states), the three 60-frame windows armed by every hit tick down 1/frame. On expiry the
// balance gauge refills to max (chunk_0006.c:7988), the down gauge resets to base
// (zz_003d3e8_ via +0x688, chunk_0004.c:6866-6876), and the combo accumulator/rank reset
// (chunk_0006.c:8009-8010). Called once per frame from battle.ts.
// ---------------------------------------------------------------------------------------
export function stepGaugeWindows(b: BorgRuntime): void {
  if (b.state === "hit" || b.state === "down") return; // frozen while in a hit reaction
  if (b.balanceRefillDelay > 0) {
    b.balanceRefillDelay -= 1;
    if (b.balanceRefillDelay <= 0) {
      b.balanceRefillDelay = 0;
      b.balanceGauge = b.balanceGaugeMax;
    }
  }
  if (b.downResetDelay > 0) {
    b.downResetDelay -= 1;
    if (b.downResetDelay <= 0) {
      b.downResetDelay = 0;
      b.downGauge = b.downGaugeBase;
    }
  }
  if (b.comboWindow > 0) {
    b.comboWindow -= 1;
    if (b.comboWindow <= 0) {
      b.comboWindow = 0;
      b.comboAccum = 0;
      b.comboRank = 0;
    }
  }
}

/**
 * Per-frame decay pass for the hit-inflicted status fields (DERIVED, status-effects-decode-
 * 2026-07-04.md §A/§B). UNCONDITIONAL — unlike stepGaugeWindows above, none of these timers
 * freeze while the borg is in a hit reaction (FUN_8005a378/the timer decrements chunk_0007.c:
 * 2839-2893 have no state gate). Call once per frame per borg, BEFORE that frame's hits are
 * applied, so aura levels (which carry no timer — they're re-applied per contact frame) start
 * this frame at 0 and only read as "active" if a hitbox still overlaps this frame.
 */
export function stepHitStatus(b: BorgRuntime): void {
  // Aura levels: cleared every frame (chunk_0003.c:5949-5950); applyHitInflictedStatus
  // re-raises them later this same frame for anyone still overlapping an aura hitbox.
  b.slowAuraLevel = 0;
  b.hasteAuraLevel = 0;

  // Discrete slow/haste-on-hit: 900f timers, clear the level at 0 (chunk_0007.c:2839-2851).
  if ((b.slowHitTimer ?? 0) > 0) {
    b.slowHitTimer = (b.slowHitTimer ?? 0) - 1;
    if (b.slowHitTimer <= 0) {
      b.slowHitTimer = 0;
      b.slowHitLevel = 0;
    }
  }
  if ((b.hasteHitTimer ?? 0) > 0) {
    b.hasteHitTimer = (b.hasteHitTimer ?? 0) - 1;
    if (b.hasteHitTimer <= 0) {
      b.hasteHitTimer = 0;
      b.hasteHitLevel = 0;
    }
  }

  // Freeze/hitstop: u8 countdown, no clear-on-expiry field beyond reaching 0 (chunk_0007.c:
  // 2881-2893).
  if ((b.freezeFrames ?? 0) > 0) {
    b.freezeFrames = Math.max(0, (b.freezeFrames ?? 0) - 1);
  }

  // Grow/shrink 900f auto-revert (the `_63` caller's +0x750 timer, chunk_0008.c:4475): at
  // expiry the accumulated delta reverts to 0 (chunk_0007.c:3684).
  if ((b.sizeTierTimer ?? 0) > 0) {
    b.sizeTierTimer = (b.sizeTierTimer ?? 0) - 1;
    if (b.sizeTierTimer <= 0) {
      b.sizeTierTimer = 0;
      b.sizeTierDelta = 0;
    }
  }

  // STAR HERO / PLANET HERO X-special self-buff (ROM +0x144): 1200f timer; at expiry revert
  // the +4 tier delta (FUN_8010f790, chunk_0030.c:4004-4026).
  if ((b.heroTierBuffFrames ?? 0) > 0) {
    b.heroTierBuffFrames = (b.heroTierBuffFrames ?? 0) - 1;
    if (b.heroTierBuffFrames <= 0) {
      b.heroTierBuffFrames = 0;
      applyActorParamTierDelta127(b.paramTier, -HERO_X_BUFF.TIER_DELTA);
    }
  }
}

export function enterHit(b: BorgRuntime, stun: number): void {
  b.state = "hit";
  b.stateTime = 0;
  b.anim = "hit";
  b.cooldowns["hitstun"] = stun;
}

export function enterDown(b: BorgRuntime, downAnimFrames: number = STATE.DOWN_DURATION): void {
  b.state = "down";
  b.stateTime = 0;
  b.anim = "down";
  b.grounded = false; // gets knocked off the ground; lands during down
  // T6: reaction release is anim-completion-gated, not a flat STATE.DOWN_DURATION constant.
  // reactionAnimLengthFrames feeds the real per-borg length where exported, else the labeled
  // TUNED fallback — stepActionState's "down" case reads this instead of the old bare constant.
  b.cooldowns["downAnimFrames"] = downAnimFrames;
}

export function enterDeath(b: BorgRuntime): void {
  b.state = "death";
  b.stateTime = 0;
  b.anim = "death";
  b.vel.x = 0;
  b.vel.z = 0;
}

/**
 * Advance the non-locomotion combat states (hit/down/death/spawn). Returns true when a
 * death state has fully elapsed (caller removes the borg + triggers next-deploy).
 */
export function stepActionState(b: BorgRuntime): { died: boolean } {
  switch (b.state) {
    case "hit": {
      const stun = b.cooldowns["hitstun"] ?? 0;
      if (stun <= 0) {
        b.state = "idle";
        b.stateTime = 0;
        b.anim = "idle";
      }
      return { died: false };
    }
    case "down": {
      // T6: release gated on the reaction anim completing (per-borg length where exported,
      // else the labeled TUNED fallback — see enterDown/reactionAnimLengthFrames), same
      // "must also be grounded" physical requirement the port already enforced.
      const downAnimFrames = b.cooldowns["downAnimFrames"] ?? STATE.DOWN_DURATION;
      if (b.stateTime >= downAnimFrames && b.grounded) {
        // Wake up with the ported 60-frame invincibility.
        b.invincTimer = WAKE_UP_INVINCIBILITY_FRAMES;
        b.state = "idle";
        b.stateTime = 0;
        b.anim = "wake";
      }
      return { died: false };
    }
    case "death": {
      if (b.stateTime >= STATE.DEATH_DURATION) {
        b.alive = false;
        return { died: true };
      }
      return { died: false };
    }
    case "spawn": {
      if (b.stateTime >= STATE.SPAWN_DURATION) {
        b.state = "idle";
        b.stateTime = 0;
        b.anim = "idle";
      }
      return { died: false };
    }
    default:
      return { died: false };
  }
}

/** True while the borg is locked out of acting (hit/down/death/spawn). */
export function isBusy(b: BorgRuntime): boolean {
  return (
    b.state === "hit" ||
    b.state === "down" ||
    b.state === "death" ||
    b.state === "spawn"
  );
}

// ---------------------------------------------------------------------------------------
// Passive contact damage (ATK-006) — DISABLED scaffold, reserving the code path per
// findings mechanic L / behavior-notes.md (am)/(an) and open-questions Q12.
//
// Evidence gap: no ROM/asset proof of a contact-damage code path exists yet — the borg
// state handlers were read in full (behavior-notes.md (u)) with no movement-triggered
// damage side effect found. What upgraded this from wiki-only to worth-scaffolding is
// OBSERVED_BEHAVIOR: speedrunners report big borgs (plasma dragon family) stepping on
// allies and granting them hit-invincibility (i.e. contact is a REAL hit that arms the
// i-frame machinery, not cosmetic), and the guide move-lists list contact damage as an
// explicit per-borg "Special" move with concrete numbers — dragon-family stepping 22
// (Flame/Blizzard/Plasma Dragon 44), Acceleration Ninja air-dash/jump body contact 44
// (that borg has NO normal melee at all — touch attacks only). See
// research/decomp/data/guide-anchors-movelist.json `contactDamage` (OBSERVED_GUIDE) and
// behavior-notes.md (an) §5.
//
// Per (an)/(ao): contact damage is AUTHORED PER-BORG DATA (a hitbox/move attached to
// specific borg ids with specific damage values), NOT an engine-wide "any two borgs
// overlapping deal damage" rule. So the future enable path is a per-borg contact-hitbox
// data table (which ids carry one, its damage/radius/rehit-interval), not a single global
// on/off toggle with one damage number — CONTACT_DAMAGE.ENABLED only gates whether that
// (still-unbuilt) per-borg table is ever consulted at all.
//
// Plausible carrier if/when traced: a persistent attack-hitbox record (activeEnd = -1 in
// the attack region, hit-bin-format.md) combined with the existing rehit-interval
// mechanism already ported for persisting projectiles (chunk_0013.c:1175-1182,
// Projectile.rehitCounter/consumeOnHit in stepProjectiles above) — a borg's own body could
// plausibly reuse that same rehit-paced hit-application shape. This is a plausibility note
// for a future trace, NOT a decoded mechanism; nothing here implements it.
//
// See open-questions Q12 and the T2 contact-script trace extension for what would need to
// be found before this can honestly flip to per-borg data + ENABLED = true.
// ---------------------------------------------------------------------------------------
export function stepContactDamage(_b: BorgRuntime, _all: BorgRuntime[]): void {
  if (!CONTACT_DAMAGE.ENABLED) return;
  // Intentionally unreachable while disabled (the default, always, today): no damage
  // numbers, radii, or cooldowns are invented here. See the header comment above.
}

// ---------------------------------------------------------------------------------------
// Attacks. Returns a (possibly empty) list of projectiles spawned this frame.
// ---------------------------------------------------------------------------------------
export interface AttackResult {
  projectiles: Projectile[];
}

let projCounter = 0;
export function resetProjectileCounter(): void {
  projCounter = 0;
}

// Per-borg family table generated from research/asset-inventory/weapon-attachment-map.json
// (scripts/gen-projectile-visual-families.mjs) — see that JSON's own "note" field and
// behavior-notes.md s4t for the full citation. TUNED, but backed by real per-borg PZZ/model/
// mot asset-family evidence (fire/beam/gun/bulletProjectile/muzzle signals, weighted by
// confidence) instead of an English name-string match. No ROM-side per-move effect/particle-ID
// field has been decoded (hit-bin-format.md's 0xF4 records and the puVar17 per-move fields
// documented in behavior-notes.md s4j/s4o/s4p are all damage/knockback fields, not visual-asset
// IDs), so this remains explicitly TUNED, not DERIVED.
const VISUAL_FAMILY_BY_BORG_ID: Readonly<Record<string, ProjectileVisualKind>> =
  projectileVisualFamilies.kinds as Record<string, ProjectileVisualKind>;

/**
 * Resolve a projectile's visual kind for a borg. Prefers the asset-family table above (real,
 * per-borg asset-inventory evidence); falls back to the original name-string heuristic only for
 * the ~half of the roster with no confident family signal in that table. Both paths are TUNED —
 * see the comment above and constants.ts's DERIVED/TUNED header for why neither can be labeled
 * DERIVED yet.
 */
export function projectileVisualKindForProfile(p: BorgProfile): ProjectileVisualKind {
  const fromAssets = VISUAL_FAMILY_BY_BORG_ID[p.id];
  if (fromAssets) return fromAssets;
  // LAST-RESORT fallback: no real per-borg asset-family signal found for this id.
  const text = `${p.id} ${p.name}`.toLowerCase();
  if (/(flame|fire|phoenix|dragon)/.test(text)) return "flame";
  if (/(beam|laser|plasma|satellite|bit)/.test(text)) return "energy";
  if (/(gun|gatling|revolver|rifle|cannon|tank|machine|bullet|missile|launcher)/.test(text)) return "muzzle";
  return "energy";
}

/**
 * X-Charge hold/release tiers. OBSERVED_WIKI selects WHO charges: 17 borgs carry an
 * "X Charge" row in data/borgMoveProperties.json (pl0504 Black Hole, pl0806 Copy Attack,
 * pl0707 Time Stop, pl0d02 Catch Crane, pl0609/pl061d A.R.B., pl0e05 Max Shot, pl0808 Hero
 * Beam, pl080f Metamorphose, pl0003 Ninpo Kage Bunshin, pl0209 Omega Cross Slash, pl0101
 * Powered Long Shot, pl0704 Shogun Slash, pl0005 Teleport Slash, pl0510 Black Hole, pl0809
 * Catch, pl0c04 Ultimate Beam — harvested by scripts/gen-borg-move-properties.mjs; runtime
 * predicate moveRuntime.ts xChargeMoveForBorgId). The thresholds/multipliers below are TUNED
 * mirrors of the B-charge tiers (actionProfiles DEFAULT_SHOT chargeTier1/2Frames 30/90 and
 * chargeTier1/2DamageMult 1.6/2.4; speed/radius/hitstun/knockback reuse the shared CHARGE.*
 * tier constants via xChargeScaling below) — no ROM per-move X-charge table is decoded (the
 * per-weapon command resolver is unread), so nothing here is promoted past TUNED.
 *
 * NOTE (presentation follow-up): HUD surfacing of the b.cooldowns["xChargeFrames"]
 * accumulator (a charge bar over the X slot) belongs to the presentation workstream — the
 * sim only owns the accumulator + release mechanics here.
 */
export const X_CHARGE = {
  /** Held frames for tier 1 / tier 2 (tier 2 is also the accumulation cap). TUNED. */
  TIER1_FRAMES: 30,
  TIER2_FRAMES: 90,
  /** Damage multipliers per tier (mirror the B-charge profile defaults). TUNED. */
  TIER1_DAMAGE_MULT: 1.6,
  TIER2_DAMAGE_MULT: 2.4,
} as const;

/** Per-tier X-charge scaling — the X-side mirror of chargeScaling below: damage from the
 *  TUNED X_CHARGE mults, speed/radius/hitstun/knockback from the shared CHARGE.* tier
 *  constants (tier 0 = all 1x, identical to an uncharged X press). */
function xChargeScaling(tier: number): {
  damage: number;
  speed: number;
  radius: number;
  hitstun: number;
  knockback: number;
} {
  if (tier >= 2) {
    return {
      damage: X_CHARGE.TIER2_DAMAGE_MULT,
      speed: CHARGE.TIER2_SPEED_MULT,
      radius: CHARGE.TIER2_RADIUS_MULT,
      hitstun: CHARGE.TIER2_HITSTUN_MULT,
      knockback: CHARGE.TIER2_KNOCKBACK_MULT,
    };
  }
  if (tier === 1) {
    return {
      damage: X_CHARGE.TIER1_DAMAGE_MULT,
      speed: CHARGE.TIER1_SPEED_MULT,
      radius: CHARGE.TIER1_RADIUS_MULT,
      hitstun: CHARGE.TIER1_HITSTUN_MULT,
      knockback: CHARGE.TIER1_KNOCKBACK_MULT,
    };
  }
  return { damage: 1, speed: 1, radius: 1, hitstun: 1, knockback: 1 };
}

type BActionKind = "melee" | "shot";

function primaryBActionOrder(actionProfile: BorgActionProfile): readonly BActionKind[] {
  return actionProfile.primary === "shot" ? (["shot", "melee"] as const) : (["melee", "shot"] as const);
}

function contextualBTarget(self: BorgRuntime, all: BorgRuntime[]): BorgRuntime | null {
  if (!self.lockTarget) return null;
  const locked = all.find((o) => o.uid === self.lockTarget) ?? null;
  return locked && isEnemyAlive(self, locked) ? locked : null;
}

/**
 * Contextual-B melee SELECTION range for a borg's melee def: the larger of its damage reach
 * (meleeDef.range) and the shared MELEE.ENGAGE_RANGE window (TUNED — the ROM's threshold
 * FLOAT_8043762c that flips the reticle red and selects battle-mode melee is T1-blocked,
 * behavior-notes.md (ai)/(av); the close=battle-attack mechanism itself is CONFIRMED_MANUAL,
 * (ao)). Exported so the app-layer reticle (presentation.ts focusHasMeleeRangeTarget) and the
 * AI (ai.ts) consume the SAME window the resolver selects with.
 */
export function meleeEngageRangeFor(meleeDef: MeleeActionDef): number {
  return Math.max(meleeDef.range, MELEE.ENGAGE_RANGE);
}

/**
 * SELECTION-only proximity test for the contextual B (and the reticle): XZ within
 * meleeEngageRangeFor, vertical within the widened MELEE.ENGAGE_Y_TOLERANCE (the per-hit
 * meleeDef.yTolerance of 50 blocked vertical engagements outright — the DAMAGE check in
 * stepAttacks keeps the tight per-borg values untouched).
 */
export function targetWithinMeleeEngage(selfPos: Vec3, targetPos: Vec3, meleeDef: MeleeActionDef): boolean {
  return (
    distXZ(selfPos, targetPos) <= meleeEngageRangeFor(meleeDef) &&
    Math.abs(targetPos.y - selfPos.y) <= Math.max(meleeDef.yTolerance, MELEE.ENGAGE_Y_TOLERANCE)
  );
}

/**
 * B-press action order. ROM evidence for proximity selection being the engine-wide B
 * dispatch: the command-move tables (data/commandMoveTables.json) decode per-borg B-far
 * (commandType 0) vs B-close (commandType 1) records, selected by the target-proximity
 * branches zz_0069a88_/zz_0069b10_ writing actor+0x585 = 0/1 — see commandMoveTables.ts
 * BUTTON_COMMAND_TYPES and moveRuntime.ts usesContextualBResolver (25 borgs / 17 decoded
 * tables, 21 with live type-1 melee records; plus 93 borgs with both catalog rows). On that
 * strength, EVERY borg whose action profile has BOTH melee and shot defs selects by
 * proximity here (the ~165 melee-capable hybrids), instead of the old static primary order
 * that never reached melee for primary:'shot' profiles while ammo > 0.
 *
 * Charge-lock fix: proximity is evaluated BEFORE honoring a held charge — shot stays first
 * only when a charge is banked AND no melee-context target exists, so holding B while
 * closing to point-blank resolves to the battle attack instead of always releasing the gun.
 */
function resolveBActionOrder(
  b: BorgRuntime,
  actionProfile: BorgActionProfile,
  meleeDef: MeleeActionDef | null,
  shotDef: ShotActionDef | null,
  meleeEngaged: boolean,
  romGates: ContextualBGates | null,
): readonly BActionKind[] {
  const fallback = primaryBActionOrder(actionProfile);
  if (!meleeDef || !shotDef) return fallback;
  // ROM +0x4ec record gating (decoded exact tables only, commandDispatch.ts): a table whose
  // B-close (type 1) row has no active records means the ROM's own per-borg command data says
  // there is NO battle attack — B selects the shot even inside the engage window. Conversely
  // a table with no active B-far (type 0) records has no far command — B out of the window
  // selects melee only (the whiff gate downstream keeps hybrids from air-swinging at range,
  // which for a shot-primary borg makes far-B a ROM-shaped no-op). Borgs without a decoded
  // table (romGates null) and single-action borgs keep the profile-driven behavior above.
  if (romGates) {
    if (meleeEngaged && !romGates.melee) return ["shot"] as const;
    if (!meleeEngaged && !romGates.shot) return ["melee"] as const;
  }
  // A held charge keeps the shot path first (stable release semantics) ONLY while no
  // melee-context target is in the engage window.
  if ((b.cooldowns["chargeFrames"] ?? 0) > 0 && !meleeEngaged) return fallback;
  return meleeEngaged ? (["melee", "shot"] as const) : (["shot", "melee"] as const);
}

/**
 * Process B (attack) and X (special) for one borg. Mutates `b` (state, cooldowns, ammo) and
 * resolves melee hits immediately against `all`. Ranged borgs spawn projectiles.
 *
 * `attackHeld` is the button's HELD state each frame (adapter/AI pass held booleans);
 * press/release edges are detected internally via the `attackHeld` cooldown latch. Three
 * profile-driven mechanics hang off it (all with generic fallbacks, all TUNED — see
 * constants.ts COMBO/CHARGE and actionProfiles.json's note):
 *   - Melee combo chains: borgs with comboHits > 1 chain follow-up swings when attack is
 *     pressed (or still held) within comboWindowFrames after a swing's recovery. Chained
 *     swings bypass the melee cooldown, start up faster, ramp damage, and the final hit
 *     forces a knockdown.
 *   - Charge shots: borgs with shot.chargeable accumulate chargeFrames while attack is held
 *     (capped at chargeTier2Frames) and fire on RELEASE, scaled by the reached tier.
 *     Non-chargeable shooters keep the fire-while-held autofire behavior.
 *   - Sword beams: borgs with melee.swordBeam emit a fast short-lived projectile on the
 *     combo finisher's first active frame, using the charge/special damage-record bridge.
 */
export function stepAttacks(
  b: BorgRuntime,
  p: BorgProfile,
  attackHeld: boolean,
  // The X button's HELD state each frame — battle.ts passes the raw input.special boolean,
  // exactly like attackHeld above (the old name `pressedSpecial` was a misnomer: no caller
  // ever edge-detected it). Press/release edges are detected internally via the
  // `specialHeld` latch below, mirroring the attackHeld latch.
  specialHeld: boolean,
  all: BorgRuntime[],
  profiles: Map<string, BorgProfile>,
  damageContext: DamageRuntimeContext = {},
): AttackResult {
  const out: Projectile[] = [];
  if (isBusy(b) || !isTargetable(b)) return { projectiles: out };
  const actionProfile = actionProfileForProfile(p);
  const meleeDef = actionProfile.melee;
  const shotDef = actionProfile.shot;

  // Press/release edge detection for the attack button (latch survives across frames).
  const prevAttackHeld = (b.cooldowns["attackHeld"] ?? 0) > 0;
  b.cooldowns["attackHeld"] = attackHeld ? 1 : 0;
  const releasedAttack = !attackHeld && prevAttackHeld;

  // Press/release edge detection for the special button (X). Without this latch the old code
  // treated the held boolean as a press, so holding X re-fired the special on every cooldown
  // expiry and made an X-hold charge impossible.
  const prevSpecialHeld = (b.cooldowns["specialHeld"] ?? 0) > 0;
  b.cooldowns["specialHeld"] = specialHeld ? 1 : 0;
  const pressedSpecialEdge = specialHeld && !prevSpecialHeld;
  const releasedSpecial = !specialHeld && prevSpecialHeld;

  // ATK-017 mash-counter scaffold (DISABLED consumer — MASH.ENABLED stays false, BLOCKED-
  // until-Q9): count attack-button PRESS EDGES (not held frames) into b.cooldowns["mashCount"]
  // while an active melee swing is in progress (b.state==="attack" && b.anim==="melee" — set by
  // startMeleeAttack and cleared when the swing's attackLock expires below), clamped at
  // MASH.PRESS_CAP (4, DERIVED chunk_0007.c:4809-4816). Reset to 0 on every swing start
  // (startMeleeAttack). This counting always runs (cheap: one comparison + one increment) —
  // nothing reads b.cooldowns["mashCount"] for gameplay purposes yet; it exists only for the
  // debug overlay (ATK-015 picks up all cooldowns automatically) until Q9 identifies a real
  // consumer.
  const pressedAttackEdge = attackHeld && !prevAttackHeld;
  if (pressedAttackEdge && b.state === "attack" && b.anim === "melee") {
    b.cooldowns["mashCount"] = Math.min(MASH.PRESS_CAP, (b.cooldowns["mashCount"] ?? 0) + 1);
  }

  // Drop the combo chain once its window lapses.
  if ((b.cooldowns["comboWindow"] ?? 0) <= 0) b.cooldowns["comboStep"] = 0;

  // Reload bookkeeping for ranged (ATK-009): the actual refill grant now happens once/frame
  // in stepAmmoRefill (battle.ts calls it adjacent to stepCooldowns, before stepAttacks runs
  // each frame), driven by weapon-0's cell (gradual/all-at-once/infinite — see combat.ts's
  // ammo/weapon-cells section above stepCooldowns). This just self-heals `b.weaponCells` for
  // any caller that constructed/reset the borg without going through stepAmmoRefill first, so
  // `b.ammo`/`b.weaponCells[0]` never drift out of sync before the fire-gate check below.
  if (shotDef) {
    ensureWeaponCells(b, p);
  }

  // --- Live ROM command resolution (the ATK-003 dispatch stage) -----------------------
  // Contextual-B target + engage window, computed once per frame: drives the ROM command
  // refinement (B close/far → table type 1/0), the melee-vs-shot SELECTION below, the whiff
  // gate, and the lunge target/drive.
  const contextTarget = meleeDef ? contextualBTarget(b, all) : null;
  const meleeEngaged =
    meleeDef !== null && contextTarget !== null && targetWithinMeleeEngage(b.pos, contextTarget.pos, meleeDef);
  // Charge-release edges feed the CHARGED/RANGED bits of the transformed input word — the
  // ROM's type-3 (B charge) and type-5 (X charge / ranged-forced) commands fire on release.
  const chargeRelease =
    releasedAttack && (b.cooldowns["chargeFrames"] ?? 0) > 0 && shotDef?.chargeable === true;
  const xChargeRelease =
    releasedSpecial && (b.cooldowns["xChargeFrames"] ?? 0) > 0 && xChargeMoveForBorgId(b.borgId) !== null;
  // Resolve this frame's command through the ROM tester priority (RANGED > CHARGED >
  // SECONDARY > MELEE) and attach the borg's exact +0x4ec command record where decoded.
  // Stored on the runtime for overlays/audits and the downstream HIT/animation wiring.
  b.command = resolveLiveCommand(
    b.borgId,
    { attackHeld, specialHeld, chargeRelease, xChargeRelease },
    { meleeEngaged, airborne: !b.grounded },
  );

  // --- Special (X) -------------------------------------------------------------------
  // Input binding (CONFIRMED_MANUAL, behavior-notes.md (ao), the official NA instruction manual):
  // B = contextual shot/melee (weapon 0), X = the SECOND weapon (weapon 1), Y = Power Burst. The
  // port's `specialHeld` is the X button — types.ts documents the control scheme as
  // "X=special" and this branch is the port's only X-driven attack — so per (ao) the X/special
  // must consume weapon cell 1 ("X Bullets"), separate from B's weapon cell 0 ("B Bullets").
  // The ammo decrement/re-arm now lives in startSpecialAttack (both fire paths below).
  //
  // Only borgs whose weapon-1 cell has max>0 (DERIVED per-borg data via
  // weaponOneCellSourceForBorgId / borgSourceStats weaponSlots[1]) use X-ammo. For those, the
  // X-attack additionally gates on cell-1 ammo (can't fire at 0) and decrements it by 1 per shot;
  // the SAME stepAmmoRefill path that refills cell 0 already iterates every cell, so cell 1
  // refills through it with no extra wiring. Borgs with max==0 on cell 1 (no weapon-1 row, or a
  // melee-only weapon-1) keep the pre-existing cooldown-only behavior EXACTLY — the ammo gate and
  // decrement below are both no-ops for them (the `xCell.max > 0` guards). The cooldown/ammo
  // interplay (ammo gate stacked ON TOP of the existing `special` cooldown) is TUNED — the ROM's
  // per-weapon command resolver that would sequence these is unread — but the B/X->cell binding
  // itself is CONFIRMED_MANUAL per (ao).
  const canStartAction = b.state !== "attack" && b.state !== "special";
  const xCell = ensureWeaponCells(b, p)[1];
  const xHasAmmo = !!xCell && xCell.max > 0;
  const xCanFire = !xHasAmmo || (xCell as WeaponCell).cur >= 1; // infinite/unused cell always passes
  // ROM tester priority: a same-frame B-charge release resolves to command type 3, which
  // outranks the X/secondary type 2 (FUN_800699d8 order) — the charge release below wins the
  // frame and the X press is not consumed.
  const commandPreemptsX = b.command?.type === AttackCommandType.Charged3;
  if (canStartAction && !commandPreemptsX && xCanFire && (b.cooldowns["special"] ?? 0) <= 0) {
    if (xChargeMoveForBorgId(b.borgId) !== null) {
      // X Charge (OBSERVED_WIKI — the borg has an "X Charge" row in borgMoveProperties.json;
      // see X_CHARGE above for the 17-borg roster and the TUNED tier values): hold X to
      // accumulate xChargeFrames (capped at the tier-2 threshold), release to fire the
      // special scaled by the reached tier — the exact hold/release shape of the B-charge
      // branch below. Accumulating does NOT consume the frame for B: charging the X slot
      // while working the B button stays possible (TUNED — the ROM's per-weapon command
      // sequencing is unread).
      if (specialHeld) {
        b.cooldowns["xChargeFrames"] = Math.min(
          X_CHARGE.TIER2_FRAMES,
          (b.cooldowns["xChargeFrames"] ?? 0) + 1,
        );
      } else if (releasedSpecial && (b.cooldowns["xChargeFrames"] ?? 0) > 0) {
        const frames = b.cooldowns["xChargeFrames"] ?? 0;
        b.cooldowns["xChargeFrames"] = 0;
        const tier = frames >= X_CHARGE.TIER2_FRAMES ? 2 : frames >= X_CHARGE.TIER1_FRAMES ? 1 : 0;
        startSpecialAttack(b, p, actionProfile, tier, out, all, profiles, damageContext, xMoveForBorgId(b.borgId));
        return { projectiles: out };
      }
    } else if (pressedSpecialEdge) {
      // Non-charging borgs: fire once per PRESS EDGE (the latch above), never on held
      // re-expiry — holding X across the cooldown no longer machine-guns the special.
      startSpecialAttack(b, p, actionProfile, 0, out, all, profiles, damageContext, xMoveForBorgId(b.borgId));
      return { projectiles: out };
    }
  }

  // --- Attack (B): asset-backed per-borg primary action, generic fallback-safe -------
  // contextTarget/meleeEngaged were computed above (they also feed the command resolution).
  if (canStartAction && (attackHeld || releasedAttack)) {
    const order = resolveBActionOrder(
      b,
      actionProfile,
      meleeDef,
      shotDef,
      meleeEngaged,
      contextualBGatesForBorgId(b.borgId),
    );
    for (const kind of order) {
      if (kind === "melee" && meleeDef && attackHeld) {
        // Whiff gate: a hybrid that fell through to melee (e.g. empty magazine on the shot
        // path) only swings with a target inside the engage window — out-of-ammo ranged
        // borgs no longer air-swing from 600 units. Melee-primary borgs (and melee-only,
        // shotDef null) keep their unconditional swing: swinging is their whole B action.
        if (!meleeEngaged && shotDef && actionProfile.primary !== "melee") continue;
        const window = b.cooldowns["comboWindow"] ?? 0;
        const prevStep = b.cooldowns["comboStep"] ?? 0;
        // Chain: within the combo window and more hits remain — bypass the melee cooldown.
        const canChain = window > 0 && prevStep + 1 < meleeDef.comboHits;
        const canFresh = (b.cooldowns["melee"] ?? 0) <= 0;
        if (canChain || canFresh) {
          const nextStep = canChain ? prevStep + 1 : 0;
          // Air B (actionStreamData.ts, cached lookup): pressing B airborne with a resolved,
          // ARMED (kind !== null) air-B leaf uses that leaf's exact window/reach/record for
          // the whole swing instead of reusing the ground melee ladder — see
          // airBMoveForBorgId's doc (a windup-only leaf, kind null, keeps today's ground-def
          // reuse: there's no melee hit data to prefer over it). Grounded swings, or borgs
          // without a resolved+armed air leaf, are unaffected.
          const airLeaf = !b.grounded ? airBMoveForBorgId(b.borgId) : null;
          const armedAirLeaf = airLeaf && airLeaf.kind !== null ? airLeaf : null;
          startMeleeAttack(
            b,
            meleeDef,
            nextStep,
            meleeEngaged ? contextTarget : null,
            exactMeleeForBorgId(b.borgId), // cached lookup; null keeps TUNED timing
            // Per-step exact ladder (actionStreamData.ts, cached lookup): when the borg's
            // B-melee ladder is DERIVED end-to-end, THIS step's own window/reach/record
            // replace the TUNED COMBO.STEP_STARTUP_SCALE rescale of step 0. Null (borg has
            // no resolved ladder, or this step index isn't in it) keeps that TUNED fallback.
            // Skipped entirely when an armed air leaf is driving this swing (armedAirLeaf
            // takes priority — see the param below).
            armedAirLeaf ? null : comboLadderForBorgId(b.borgId)?.[nextStep] ?? null,
            armedAirLeaf,
          );
          break;
        }
        continue; // melee gated — a hybrid may still fire its gun below
      }
      if (kind === "shot" && shotDef && (b.cooldowns["shot"] ?? 0) <= 0 && b.ammo > 0) {
        if (shotDef.chargeable) {
          if (attackHeld) {
            // Hold-to-charge: accumulate (capped) and consume the button for this frame.
            b.cooldowns["chargeFrames"] = Math.min(
              shotDef.chargeTier2Frames,
              (b.cooldowns["chargeFrames"] ?? 0) + 1,
            );
            break;
          }
          if (releasedAttack && (b.cooldowns["chargeFrames"] ?? 0) > 0) {
            const frames = b.cooldowns["chargeFrames"] ?? 0;
            b.cooldowns["chargeFrames"] = 0;
            const tier = frames >= shotDef.chargeTier2Frames ? 2 : frames >= shotDef.chargeTier1Frames ? 1 : 0;
            startShotAttack(b, p, shotDef, tier, out, all);
            break;
          }
          continue;
        }
        if (attackHeld) {
          startShotAttack(b, p, shotDef, 0, out, all);
          break;
        }
      }
    }
  }

  // --- Melee lunge drive (the signature close-range homing dash) ----------------------
  // Sim-side replacement for the attack_lunge_s* bone-0 root motion the renderer strips
  // (apps/game/src/main.ts buildClip zeroes bone-0 XZ; rootZ spans ~100-389 units per the
  // PREFERRED_LABELS comments there). While the swing's meleeLunge window (armed by
  // startMeleeAttack, decays 1/frame via stepCooldowns) is open, drive velocity toward the
  // contextual target and stop inside reach. All values TUNED (MELEE.LUNGE_*) —
  // FLOAT_8043762c, the ROM's melee-engage threshold, remains T1-blocked (behavior-notes.md
  // (ai)/(av)). stepMovement (which runs before stepAttacks each frame) integrates this
  // velocity next frame with bounds/wall/floor collision applied, so the lunge cannot carry
  // a borg off stage; it also decays it by MOVE.DECEL first — see MELEE.LUNGE_SPEED's note.
  if (b.state === "attack" && b.anim === "melee" && meleeDef && (b.cooldowns["meleeLunge"] ?? 0) > 0) {
    const lungeTarget = contextTarget && isTargetable(contextTarget) ? contextTarget : null;
    if (lungeTarget) {
      const d = distXZ(b.pos, lungeTarget.pos);
      const stop = meleeDef.range * MELEE.LUNGE_STOP_FRACTION;
      if (d > stop) {
        const dir = normalize({ x: lungeTarget.pos.x - b.pos.x, y: 0, z: lungeTarget.pos.z - b.pos.z });
        const speed = Math.min(MELEE.LUNGE_SPEED, d - stop);
        b.vel.x = dir.x * speed;
        b.vel.z = dir.z * speed;
      } else {
        // Inside reach: kill the drive so the attacker doesn't overrun through the target.
        b.cooldowns["meleeLunge"] = 0;
        b.vel.x = 0;
        b.vel.z = 0;
      }
    }
  }

  // --- Resolve an active melee swing against enemies in reach ------------------------
  const meleeActive = b.cooldowns["meleeActive"] ?? 0;
  const comboStepForSwing = b.cooldowns["comboStep"] ?? 0;
  // Air B (actionStreamData.ts, cached lookup): re-read the persisted latch (set once at
  // swing start by startMeleeAttack, NOT re-derived from current b.grounded — a mid-swing
  // landing must not swap this swing's data out from under it) to decide whether this ACTIVE
  // swing should keep using the air leaf's exact reach/record instead of the ground ladder's.
  const airExactForSwing =
    meleeDef && (b.cooldowns["meleeAirSwing"] ?? 0) > 0 ? airBMoveForBorgId(b.borgId) : null;
  // Exact per-borg swing data (meleeExactData.ts, cached lookup): first-swing active-window
  // length, authored reach, and family damage record — the fallback for borgs/steps without a
  // resolved combo ladder.
  const exactMelee = meleeDef ? exactMeleeForBorgId(b.borgId) : null;
  // Per-combo-step exact data (actionStreamData.ts, cached lookup): when the borg's B-melee
  // ladder is DERIVED end-to-end, THIS swing's step gets its OWN window/reach/record instead of
  // exactMelee's first-swing data. Null (no ladder, or this step index isn't in it) falls back
  // to exactMelee, which itself falls back to the TUNED profile. Skipped when this swing is
  // air-leaf-driven (airExactForSwing takes priority below).
  const exactStep =
    meleeDef && !airExactForSwing ? comboLadderForBorgId(b.borgId)?.[comboStepForSwing] ?? null : null;
  const meleeActiveLen =
    airExactForSwing?.activeStart != null && airExactForSwing.activeEnd != null
      ? airExactForSwing.activeEnd - airExactForSwing.activeStart + 1
      : exactStep
        ? exactStep.activeEnd - exactStep.activeStart + 1
        : exactMelee
          ? exactMelee.activeEnd - exactMelee.activeStart + 1
          : meleeDef?.active ?? 0;
  if (b.state === "attack" && b.anim === "melee" && meleeDef && meleeActive > 0 && STATE.MELEE_IFRAME_REFRESH_PER_FRAME) {
    b.invincTimer = WAKE_UP_INVINCIBILITY_FRAMES;
  }
  if (b.state === "attack" && b.anim === "melee" && meleeDef && meleeActive > 0 && meleeActive <= meleeActiveLen) {
    const comboStep = comboStepForSwing;
    const isFinisher = comboStep >= meleeDef.comboHits - 1;
    // Sword beam: the combo finisher's FIRST active frame emits a fast short-lived projectile
    // with melee-scaled damage (TUNED design; see actionProfiles.ts SwordBeamDef).
    // meleeActive counts down from startup+activeLen, so the first active frame equals the
    // resolved window length — meleeActiveLen, not the TUNED meleeDef.active, which diverges
    // once exact HIT-record windows drive the swing.
    if (meleeDef.swordBeam && isFinisher && meleeActive === meleeActiveLen) {
      out.push(spawnSwordBeam(b, meleeDef, meleeDef.swordBeam, all));
    }
    // Only the active window (after startup) deals damage; one hit per swing per target.
    const fwd = forwardFromYaw(b.rotY);
    const stepMult =
      COMBO.STEP_DAMAGE_MULT[Math.min(comboStep, COMBO.STEP_DAMAGE_MULT.length - 1)] ?? 1;
    for (const o of all) {
      if (!canReceiveHit(b, o)) continue;
      // One hit per swing per target: skip anyone this swing already struck. (This enforces
      // the long-documented contract; previously the active window re-applied damage every
      // frame, silently multiplying melee damage by the active-frame count.)
      if (b.meleeHitUids?.includes(o.uid)) continue;
      const d = distXZ(b.pos, o.pos);
      // Authored reach (hit.bin record offset+extent): the air leaf's own reach when this
      // swing is air-driven, else this step's own reach where the ground combo ladder
      // resolved it, else the first-swing exact reach, else the TUNED profile range.
      const meleeRange =
        airExactForSwing && airExactForSwing.reach > 0
          ? airExactForSwing.reach
          : exactStep && exactStep.reach > 0
            ? exactStep.reach
            : exactMelee && exactMelee.reach > 0
              ? exactMelee.reach
              : meleeDef.range;
      if (d > meleeRange) continue;
      if (Math.abs(o.pos.y - b.pos.y) > meleeDef.yTolerance) continue;
      const to = normalize({ x: o.pos.x - b.pos.x, y: 0, z: o.pos.z - b.pos.z });
      if (fwd.x * to.x + fwd.z * to.z < 0) continue; // behind us
      const op = profiles.get(o.uid);
      if (!op) continue;
      const knockbackMult =
        meleeDef.knockbackMultiplier * (isFinisher && meleeDef.comboHits > 1 ? COMBO.FINISHER_KNOCKBACK_MULT : 1);
      // Exact family record for this swing (script-armed kind → hit record → family table):
      // the air leaf's own record when this swing is air-driven, else this step's own record
      // where the ground combo ladder resolved it, else the first-swing exact record, else
      // archetype record 1 for borgs without decoded data.
      const meleeRecord =
        airExactForSwing?.damageRecord ??
        exactStep?.damageRecord ??
        exactMelee?.damageRecord ??
        damageRecordByIndex(DAMAGE_RECORD_INDEX.MELEE);
      // T3 burst ally-passthrough (zz_002fd7c_): a bursting teammate cannot be hit by this
      // swing at all — skip entirely, same as a real ROM eligibility-filter miss (no damage,
      // no combo credit, no telemetry).
      if (burstAllyPassthroughBlocks(b, o, meleeRecord)) continue;
      // Zero vector -> applyHit() computes the real ROM-mode-1 direction (attacker->target)
      // instead of the attacker's facing vector (`fwd`) used here previously.
      const dealt = applyHit(
        o,
        op,
        0,
        // Multiplier only — applyHit derives the base from record 1's strength byte.
        knockbackMult,
        { x: 0, y: 0, z: 0 },
        b.pos,
        // A multi-hit chain's finisher launches: forced knockdown (TUNED game-feel choice).
        isFinisher && meleeDef.comboHits > 1,
        // Melee -> record 1 (reactionFlags 2 -> always staggers; DERIVED mapping, gauges.ts).
        meleeRecord,
        {
          attacker: b,
          attackerProfile: p,
          damageScale: meleeDef.damageMultiplier * stepMult,
          attackerSideRank: damageContext.sideRankForTeam?.(b.team),
          defenderSideRank: damageContext.sideRankForTeam?.(o.team),
        },
        damageContext,
      );
      if (dealt > 0) (b.meleeHitUids ??= []).push(o.uid);
    }
  }

  // Return to idle when the attack animation finishes.
  if (b.state === "attack" && (b.cooldowns["attackLock"] ?? 0) <= 0) {
    b.state = "idle";
    b.stateTime = 0;
    b.anim = "idle";
  }
  if (b.state === "special" && (b.cooldowns["attackLock"] ?? 0) <= 0) {
    b.state = "idle";
    b.stateTime = 0;
    b.anim = "idle";
  }

  return { projectiles: out };
}

function startMeleeAttack(
  b: BorgRuntime,
  meleeDef: MeleeActionDef,
  comboStep: number,
  lungeTarget: BorgRuntime | null,
  // Exact per-borg first-swing data (meleeExactData.ts): frame window from the hit.bin
  // record armed by the borg's action script. Null keeps the TUNED profile timing.
  exactMelee: ExactMeleeAttack | null = null,
  // Exact per-STEP data (actionStreamData.ts): when the borg's B-melee combo ladder is
  // DERIVED end-to-end, this step's OWN window/reach/record (comboLadderForBorgId(id)[comboStep])
  // replace the TUNED COMBO.STEP_STARTUP_SCALE rescale of step 0. Null (no ladder, or this
  // step index isn't in it) keeps that TUNED fallback.
  exactStep: ComboStep | null = null,
  // Exact air-B leaf (actionStreamData.ts airBMoveForBorgId, ARMED — kind !== null — only;
  // the caller filters windup-only leaves out before passing one in). Takes priority over
  // exactStep/exactMelee for window+anim when present: an airborne swing plays its OWN
  // action-script data, not the ground ladder's. Null keeps the existing ground-reuse
  // behavior exactly (today's air-melee fallback).
  airExact: ExactMoveLeaf | null = null,
): void {
  // Exact window: activeStart..activeEnd are anim-frame numbers (the ROM clocks the hitbox
  // against actor+0x1cdc); the port's state timer stands in for the anim clock 1:1 at 60Hz.
  // A resolved ladder step (or armed air leaf) uses its OWN exact window; otherwise chain
  // steps keep the TUNED faster-startup scale of step 0's window (exactMelee / the profile
  // default). airExact's activeStart/activeEnd are non-null here by construction (the caller
  // only passes an ARMED leaf), but the `?? meleeDef.startup`-shaped fallback chain stays
  // defensive against the type's nullability.
  const baseStartup =
    airExact?.activeStart ?? (exactStep ? exactStep.activeStart : exactMelee ? exactMelee.activeStart : meleeDef.startup);
  const baseActive =
    airExact?.activeStart != null && airExact.activeEnd != null
      ? airExact.activeEnd - airExact.activeStart + 1
      : exactStep
        ? exactStep.activeEnd - exactStep.activeStart + 1
        : exactMelee
          ? exactMelee.activeEnd - exactMelee.activeStart + 1
          : meleeDef.active;
  const startup =
    comboStep > 0 && !exactStep && !airExact
      ? Math.max(2, Math.round(baseStartup * COMBO.STEP_STARTUP_SCALE))
      : baseStartup;
  // The swing/lock must outlast the exact active window when it runs longer than the
  // TUNED profile duration.
  const duration = Math.max(meleeDef.duration, startup + baseActive + 2);
  b.cooldowns["melee"] = duration + meleeDef.cooldown;
  b.cooldowns["meleeActive"] = startup + baseActive;
  b.cooldowns["attackLock"] = duration;
  // Melee is a FULL-BODY state in the ROM (cue table pair [61, 0]) — entering it replaces
  // the dash state and the attack script re-seeds velocity. Without this, the 30f-page
  // dashes carry the swing straight past the target before the active window opens.
  b.cooldowns["dashActive"] = 0;
  // Lunge (contextual-B target inside the engage window only): snap facing onto the target
  // and arm the lunge-drive window for the swing's startup+active frames, clamped so the
  // total travel stays within MELEE.LUNGE_MAX_DIST (see the lunge drive in stepAttacks and
  // the MELEE.LUNGE_* citations in constants.ts — all TUNED, root-motion-anchored). The full
  // facing snap is a TUNED stand-in for the ROM's lock-tracked attack facing; stepMovement's
  // lock-facing keeps tracking the target on subsequent frames either way.
  if (lungeTarget && distXZ(b.pos, lungeTarget.pos) > 1e-3) {
    b.rotY = yawFromXZ(lungeTarget.pos.x - b.pos.x, lungeTarget.pos.z - b.pos.z);
    b.cooldowns["meleeLunge"] = Math.min(
      startup + meleeDef.active,
      Math.max(1, Math.floor(MELEE.LUNGE_MAX_DIST / MELEE.LUNGE_SPEED)),
    );
  } else {
    b.cooldowns["meleeLunge"] = 0;
  }
  // The chain window covers this swing plus a grace period after its recovery. The renderer
  // alternates melee/melee_alt banks on each melee re-entry (battleScene meleeParity), and the
  // >=1 idle frame between chained swings is what lets it see the re-entry.
  b.cooldowns["comboWindow"] = meleeDef.duration + meleeDef.comboWindowFrames;
  b.cooldowns["comboStep"] = comboStep;
  b.meleeHitUids = []; // fresh swing: everyone is hittable once again
  // This swing's action-script anim target (renderer bridge — see the BorgRuntime field doc);
  // an armed air leaf takes priority (it's this swing's OWN data), else the ground ladder
  // step, else null — which keeps the existing generic melee/melee_alt slot selection in
  // borgPresentationAssets.ts unchanged.
  b.meleeAnimStream = airExact?.animStreamRef ?? exactStep?.animStreamRef ?? null;
  // This swing's PATH-B authored sound events (same precedence as the anim ref above — the
  // sounds belong to the SAME anim the ref names). Renderer bridge only; the sim never plays
  // audio. Empty lists are normalized to null so fallback SFX logic stays a simple null check.
  const swingSounds = airExact?.sounds ?? exactStep?.sounds ?? null;
  b.meleeSounds = swingSounds && swingSounds.length > 0 ? swingSounds : null;
  // Persisted latch (stepCooldowns skip-list): records that THIS swing is air-leaf-driven so
  // stepAttacks' swing-resolution block (which re-reads exact data every active frame from
  // b.cooldowns["comboStep"], not from this call's params) keeps using the air leaf's
  // reach/record for the swing's whole duration, even if the borg lands mid-swing.
  b.cooldowns["meleeAirSwing"] = airExact ? 1 : 0;
  // ATK-017 mash-counter scaffold: every new swing (opener or chained) resets the press-edge
  // counter to 0 — see the mash-counting block in stepAttacks for what increments it.
  b.cooldowns["mashCount"] = 0;
  b.state = "attack";
  b.stateTime = 0;
  b.anim = "melee";
}

/**
 * Fire the X special (possibly X-charge-scaled): consumes X-ammo (weapon cell 1), sets
 * cooldowns/state/anim, then resolves per the wave-1 SpecialActionDef archetype:
 *   - archetype "projectile" (59 borgs whose OBSERVED_WIKI X move reads as a fired attack,
 *     e.g. G Red's G Crash — data selection in actionProfiles.json, TUNED params): spawns
 *     projectiles into `out`, which battle.ts pushes into state.projectiles — the NORMAL
 *     projectile pipeline, so terrain/owner/bounds despawn reasons, burst-meter crediting via
 *     applyHit `source`, and the CHARGE_OR_SPECIAL damage-record accounting all apply
 *     unchanged (no parallel bookkeeping).
 *   - archetype "aoe"/absent (default/fallback, unchanged semantics): the pre-existing radial
 *     burst around the borg.
 * chargeTier 0 = plain press (identical to the pre-X-charge behavior for every borg); tiers
 * 1/2 only reachable via the X-charge hold/release path (X_CHARGE, TUNED).
 * `xLeaf` (actionStreamData.ts xMoveForBorgId, resolved once by the caller): when non-null,
 * sets the exact anim stream ref + authored sounds (same meleeAnimStream/meleeSounds renderer
 * bridge startMeleeAttack/startShotAttack's charge release use) and, when the leaf's kind has
 * real records in the borg's OWN hit remap, replaces the generic CHARGE_OR_SPECIAL record with
 * the exact one (xDamageRecordSpread — same guarded pattern as chargeDamageRecordSpread). This
 * ONLY makes the record/anim/sounds exact; every TUNED mechanic below (AoE radius, projectile
 * archetypes, the hero X ram buff) is unchanged.
 */
function startSpecialAttack(
  b: BorgRuntime,
  p: BorgProfile,
  actionProfile: BorgActionProfile,
  chargeTier: number,
  out: Projectile[],
  all: BorgRuntime[],
  profiles: Map<string, BorgProfile>,
  damageContext: DamageRuntimeContext,
  xLeaf: ExactMoveLeaf | null = null,
): void {
  const specialDef = actionProfile.special;
  // Consume one X-bullet from weapon cell 1 (only when the borg actually has X-ammo; max==0
  // cells stay untouched -> cooldown-only behavior). Mirrors startShotAttack's cell-0
  // decrement + all-at-once re-arm (see that function): decrement, then arm the refill timer
  // the instant the cell empties for non-gradual (refillType!==1) cells; gradual cells refill
  // fractionally each frame via stepWeaponCellRefill and don't use `timer`.
  const xCell = ensureWeaponCells(b, p)[1];
  if (xCell && xCell.max > 0) {
    xCell.cur = Math.max(0, xCell.cur - 1);
    if (xCell.cur <= 0 && xCell.refillType !== 1) {
      xCell.timer = xCell.refillParam > 0 ? xCell.refillParam : AMMO.DEFAULT_ALL_AT_ONCE_TIMER_FRAMES;
    }
  }
  b.cooldowns["special"] = specialDef.cooldown;
  b.cooldowns["attackLock"] = specialDef.duration;
  b.state = "special";
  b.stateTime = 0;
  b.anim = "special";
  // Exact X-special anim stream ref + PATH-B authored sounds (actionStreamData.ts
  // xMoveForBorgId), same renderer bridge fields startMeleeAttack/startShotAttack's charge
  // release set. Null leaf (unresolved) clears both exactly like today — no ref/sounds ever
  // leaked from a stale prior swing/charge into a special press.
  b.meleeAnimStream = xLeaf?.animStreamRef ?? null;
  b.meleeSounds = xLeaf && xLeaf.sounds.length > 0 ? xLeaf.sounds : null;

  const tier = xChargeScaling(chargeTier);

  // Projectile-archetype special: fired attack instead of the generic radial burst.
  if (specialDef.archetype === "projectile") {
    out.push(...spawnSpecialProjectiles(b, p, specialDef, tier, all, xLeaf));
    return;
  }

  // AoE burst around the borg (default/fallback archetype — bit-for-bit the pre-existing
  // behavior at tier 0). HP damage comes from record 2 via damageFormula.ts; the special
  // multiplier remains a port-side bridge until per-special hitbox records are mapped. Tier
  // scaling (X-charge releases only) widens the burst and scales damage/knockback via the
  // same TUNED tier mults as a charged shot. An armed xLeaf's own exact record
  // (xDamageRecordSpread) replaces the generic archetype record where the borg's remap
  // actually carries it.
  const specialRecord = xDamageRecordSpread(b.borgId, xLeaf).damageRecord ?? damageRecordByIndex(DAMAGE_RECORD_INDEX.CHARGE_OR_SPECIAL);
  for (const o of all) {
    if (!canReceiveHit(b, o)) continue;
    // T3 burst ally-passthrough (zz_002fd7c_) — see the melee-loop citation above.
    if (burstAllyPassthroughBlocks(b, o, specialRecord)) continue;
    if (distXZ(b.pos, o.pos) <= specialDef.radius * tier.radius) {
      const op = profiles.get(o.uid);
      if (op) {
        // Zero vector -> applyHit() computes the real ROM-mode-1 direction (attacker->target,
        // via the ported zz_00300bc_ atan2/BAM16 calc) instead of this raw un-ported subtract.
        const dealt = applyHit(
          o,
          op,
          0,
          // Multiplier only — applyHit derives the base from record 2's strength byte.
          specialDef.knockbackMultiplier * tier.knockback,
          { x: 0, y: 0, z: 0 },
          b.pos,
          true,
          // Specials -> record 2 (DERIVED mapping, gauges.ts DAMAGE_RECORD_INDEX).
          specialRecord,
          {
            attacker: b,
            attackerProfile: p,
            damageScale: specialDef.damageMultiplier * tier.damage,
            attackerSideRank: damageContext.sideRankForTeam?.(b.team),
            defenderSideRank: damageContext.sideRankForTeam?.(o.team),
          },
          damageContext,
        );
        // STAR HERO (pl0804) / PLANET HERO (pl080c) X-special self-buff (DERIVED,
        // status-effects-decode-2026-07-04.md §A, zz_011230c_ chunk_0031.c:576-617): their X
        // is a ramming dash — on a connecting hit, if not already buffed, gain +4 param tiers
        // for 1200f. Only the FIRST connection of this X starts the buff (guarded by
        // heroTierBuffFrames <= 0, mirroring the ROM's "+0x144 <= 0" check); a hit while
        // already buffed just connects normally with no re-buff/refresh.
        if (dealt > 0 && applyHeroXBuff(b)) break;
      }
    }
  }
}

/**
 * Apply the STAR HERO / PLANET HERO X ramming-dash self-buff to the attacker on a connecting
 * hit: +4 param tiers (velocity ×2.366) for HERO_X_BUFF.DURATION_FRAMES, reverted by
 * stepHitStatus when the timer expires. No-op (returns false) for every other borg id or when
 * already buffed (ROM "+0x144 <= 0" gate — chunk_0031.c:583). Returns true when the buff
 * (newly) applied, so the caller can stop after the dash's first connection.
 */
function applyHeroXBuff(b: BorgRuntime): boolean {
  if (!(HERO_X_BUFF.BORG_IDS as readonly string[]).includes(b.borgId.toLowerCase())) return false;
  if ((b.heroTierBuffFrames ?? 0) > 0) return false;
  b.heroTierBuffFrames = HERO_X_BUFF.DURATION_FRAMES;
  applyActorParamTierDelta127(b.paramTier, HERO_X_BUFF.TIER_DELTA);
  return true;
}

/** TUNED spread between the muzzles of a multi-projectile special (radians between adjacent
 *  shots) — same fan shape as spawnProjectiles' spreadRadians; no ROM per-special muzzle
 *  table is decoded (see the multi-muzzle note above spawnProjectiles). */
const SPECIAL_PROJECTILE_SPREAD_RADIANS = 0.14;

/**
 * Spawn the projectile(s) of a projectile-archetype special. Mirrors spawnProjectile's shape
 * so the result flows through stepProjectiles' normal pipeline (homing gate, terrain/owner
 * despawn reasons, burst-meter crediting via the applyHit `source` built from ownerUid, and
 * record-2 gauge accounting via damageRecordIndex). All params TUNED from the wave-1
 * SpecialActionDef fields (OBSERVED_WIKI only selects WHO fires a projectile special);
 * generic SHOT/SPECIAL/MUZZLE_OFFSET constants fill any absent field.
 */
function spawnSpecialProjectiles(
  b: BorgRuntime,
  p: BorgProfile,
  specialDef: SpecialActionDef,
  tier: ReturnType<typeof xChargeScaling>,
  all: BorgRuntime[],
  // Exact X-special leaf (actionStreamData.ts xMoveForBorgId), resolved once by the caller
  // (startSpecialAttack). Threaded through so its damage record can replace the generic
  // CHARGE_OR_SPECIAL archetype on the fired projectile — see xDamageRecordSpread's gating.
  xLeaf: ExactMoveLeaf | null = null,
): Projectile[] {
  const count = Math.max(1, Math.floor(specialDef.projectileCount ?? 1));
  const projectiles: Projectile[] = [];
  for (let i = 0; i < count; i += 1) {
    const centered = count === 1 ? 0 : i - (count - 1) / 2;
    const yaw = b.rotY + centered * SPECIAL_PROJECTILE_SPREAD_RADIANS;
    const fwd = { x: Math.sin(yaw), y: 0, z: Math.cos(yaw) };
    // Muzzle: the shared sim/render default (see spawnProjectile's muzzle note) — no
    // per-special muzzle data exists yet.
    const muzzlePos = {
      x: b.pos.x + fwd.x * MUZZLE_OFFSET.forward,
      y: b.pos.y + MUZZLE_OFFSET.up,
      z: b.pos.z + fwd.z * MUZZLE_OFFSET.forward,
    };
    // TUNED floor (2026-07-04 playtest): several generated profiles carry projectileSpeed
    // below the borg's own bullet speed (G RED's G Crash was 24 vs his 28 u/f shots), which
    // read as broken. A special is never slower than 1.4x the generic shot speed until the
    // per-move speed params (shot variant table row bytes, undecoded) replace this.
    const specialSpeed = Math.max(specialDef.projectileSpeed ?? SHOT.SPEED, SHOT.SPEED * 1.4);
    projectiles.push({
      uid: `proj_${projCounter++}`,
      ownerUid: b.uid,
      team: b.team,
      pos: muzzlePos,
      vel: scale(fwd, specialSpeed * tier.speed),
      // `damage` is the damageScale fed to computeSourceDamage by stepProjectiles (same
      // convention as gun projectiles); the AoE path passes the same multiplier as its
      // damageScale, so both special archetypes hit with identical record-2 strength.
      damage: specialDef.damageMultiplier * tier.damage,
      hitstun: Math.max(1, Math.round(SPECIAL.HITSTUN * tier.hitstun)),
      // Per-move MULTIPLIER (applyHit derives the base from the projectile's damage record).
      knockback: specialDef.knockbackMultiplier * tier.knockback,
      homingTurn: SHOT.HOMING_TURN,
      // Same spawn-time aim-cone gate as gun projectiles (FUN_8006c334, chunk_0009.c:1995/3841).
      homingTarget: homingTargetForSpawn(b, all, muzzlePos, fwd),
      // ROM attack-object target +0xcc for the results DODGE counters (aimed vs stray).
      aimedTargetUid: activeSourceTargetUid(b),
      life: SHOT.LIFETIME,
      hitRadius: (specialDef.projectileHitRadius ?? SHOT.HIT_RADIUS) * tier.radius,
      // TUNED-visual from the OBSERVED_WIKI X move name (actionProfiles generator), falling
      // back to the borg's asset-family kind.
      visualKind: specialDef.projectileVisualKind ?? projectileVisualKindForProfile(p),
      // Specials -> record 2 (DERIVED mapping, gauges.ts DAMAGE_RECORD_INDEX) — the same
      // record the AoE path and charged releases use, UNLESS the exact X-special leaf's own
      // record resolved (xDamageRecordSpread below), in which case its damageRecord spread wins
      // on top of this fallback index/no-op.
      damageRecordIndex: DAMAGE_RECORD_INDEX.CHARGE_OR_SPECIAL,
      ...xDamageRecordSpread(b.borgId, xLeaf),
    });
  }
  return projectiles;
}

/** Fire a (possibly charge-scaled) shot: consumes ammo, sets cooldowns/anim, spawns projectiles.
 *  chargeTier 0 = normal shot; tiers 1/2 scale damage per-profile and speed/radius/hitstun/
 *  knockback via the TUNED CHARGE constants. */
function startShotAttack(
  b: BorgRuntime,
  p: BorgProfile,
  shotDef: ShotActionDef,
  chargeTier: number,
  out: Projectile[],
  all: BorgRuntime[],
): void {
  b.cooldowns["shot"] = shotDef.cooldown;
  // ATK-009: consume from weapon-0's cell, not a flat pool. Fire-gate cost is a flat 1 (the
  // ROM's zz_006dbe0_ cost check/decrement — chunk_0009.c:2866-2905 — takes a per-call cost
  // param; every stepAttacks call site here always passes the implicit cost of 1 shot). max
  // <= 0 (infinite) never decrements, matching the ROM's max==0 gate skip
  // (chunk_0002.c:7158-7165); b.ammo stays mirrored to Infinity by ensureWeaponCells in that
  // case, so this early-return is just belt-and-suspenders against stale callers.
  const cell = ensureWeaponCells(b, p)[0];
  if (cell && cell.max > 0) {
    cell.cur = Math.max(0, cell.cur - 1);
    b.ammo = cell.cur;
    // Arm the all-at-once timer the instant the cell empties (mirrors zz_006dcc0_'s
    // sVar4<1 branch re-arming on cur===0; gradual cells don't use this timer path at all —
    // stepWeaponCellRefill only reads `timer` for refillType<=0/2/3).
    if (cell.cur <= 0 && cell.refillType !== 1) {
      cell.timer = cell.refillParam > 0 ? cell.refillParam : AMMO.DEFAULT_ALL_AT_ONCE_TIMER_FRAMES;
    }
  }
  b.cooldowns["attackLock"] = shotDef.recovery;
  b.state = "attack";
  b.stateTime = 0;
  // Charged releases carry their own anim label: the charge-fire animation is a distinct
  // clip in source (action index 3's group-4 stream — see actionStreamData.ts
  // chargeMoveForBorgId; G RED's leaf plays anim group 3 slot 18, the chest-beam hop, per
  // meleeAnimKinds.json bank 0x80366220 — the borg's stream is windup-only, arming no kind,
  // per the decode note's corrected reading). The renderer maps "charge_shot" per borg and
  // falls back to the plain shoot clip.
  b.anim = chargeTier >= 1 ? "charge_shot" : "shoot";
  // Exact charge leaf (actionStreamData.ts, cached lookup): generalizes the pl0615/pl0629/
  // pl062a PREFERRED_LABELS hardcode in borgPresentationAssets.ts to every borg with a
  // resolved leaf — set the same renderer bridge field startMeleeAttack uses for melee
  // (BorgRuntime.meleeAnimStream), so loadClipByStreamRef fires for "charge_shot" too. Only
  // meaningful on a charged release; a plain tap keeps this cleared so a stale charge stream
  // ref never leaks into the next plain "shoot" anim.
  const chargeLeaf = chargeTier >= 1 ? chargeMoveForBorgId(b.borgId) : null;
  b.meleeAnimStream = chargeLeaf?.animStreamRef ?? null;
  // Charged release's PATH-B authored sounds (see startMeleeAttack's twin assignment).
  b.meleeSounds = chargeLeaf && chargeLeaf.sounds.length > 0 ? chargeLeaf.sounds : null;
  out.push(...spawnProjectiles(b, p, shotDef, chargeTier, all, chargeLeaf));
}

/** Per-tier charge scaling (tier 0 = all 1x). Damage mults come from the profile; the rest
 *  from the TUNED CHARGE constants. */
function chargeScaling(shotDef: ShotActionDef, tier: number): {
  damage: number;
  speed: number;
  radius: number;
  hitstun: number;
  knockback: number;
} {
  if (tier >= 2) {
    return {
      damage: shotDef.chargeTier2DamageMult,
      speed: CHARGE.TIER2_SPEED_MULT,
      radius: CHARGE.TIER2_RADIUS_MULT,
      hitstun: CHARGE.TIER2_HITSTUN_MULT,
      knockback: CHARGE.TIER2_KNOCKBACK_MULT,
    };
  }
  if (tier === 1) {
    return {
      damage: shotDef.chargeTier1DamageMult,
      speed: CHARGE.TIER1_SPEED_MULT,
      radius: CHARGE.TIER1_RADIUS_MULT,
      hitstun: CHARGE.TIER1_HITSTUN_MULT,
      knockback: CHARGE.TIER1_KNOCKBACK_MULT,
    };
  }
  return { damage: 1, speed: 1, radius: 1, hitstun: 1, knockback: 1 };
}

// Multi-muzzle note (ROM, fx-cluster-2026-07-03): the fire handler zz_0070558_
// (chunk_0009.c:4650) selects WHICH muzzle(s) of the weapon-param table fire based on the
// weapon FAMILY — family 3 fires dual muzzles 0 AND 2 in one trigger pull, others fire a
// single indexed muzzle. The port's projectileCount/spreadRadians fan below is the TUNED
// stand-in for that per-family muzzle layout until DAT_802d39dc (per-muzzle position/velocity
// table, identified but UNDUMPED) is dumped; restructuring the per-borg data lives with
// actionProfiles, not here.
function spawnProjectiles(
  b: BorgRuntime,
  p: BorgProfile,
  shotDef: ShotActionDef,
  chargeTier = 0,
  all: BorgRuntime[] = [],
  // Exact charge leaf (actionStreamData.ts chargeMoveForBorgId), resolved once by the caller
  // (startShotAttack) for chargeTier>=1 releases. Threaded through to spawnProjectile so its
  // damage record can replace the generic CHARGE_OR_SPECIAL archetype — see
  // chargeDamageRecordSpread's gating doc.
  chargeLeaf: ExactMoveLeaf | null = null,
): Projectile[] {
  const count = Math.max(1, Math.floor(shotDef.projectileCount));
  const projectiles: Projectile[] = [];
  for (let i = 0; i < count; i += 1) {
    const centered = count === 1 ? 0 : i - (count - 1) / 2;
    projectiles.push(
      spawnProjectile(b, p, shotDef, centered * shotDef.spreadRadians, chargeTier, all, chargeLeaf),
    );
  }
  return projectiles;
}

/** Spawn-time homing gate — FUN_8006c334 (chunk_0009.c:1995), called from the projectile
 *  spawn path at chunk_0009.c:3841: a projectile only receives a homing lock if the shooter's
 *  locked target lies inside an aim cone around the projectile's INITIAL flight direction;
 *  otherwise it flies straight (homingTarget = null). Previously the port granted
 *  homingTarget = b.lockTarget unconditionally. The cone half-angle is TUNED
 *  (HOMING.AIM_CONE_HALF_ANGLE_RAD) — the ROM compares against FLOAT_8043768c, identified but
 *  UNDUMPED. `dir` must be a unit vector. */
function homingTargetForSpawn(
  b: BorgRuntime,
  all: BorgRuntime[],
  muzzlePos: Vec3,
  dir: Vec3,
): string | null {
  if (!b.lockTarget) return null;
  const tgt = all.find((o) => o.uid === b.lockTarget);
  if (!tgt || !isTargetable(tgt)) return null;
  const to = sub(tgt.pos, muzzlePos);
  const dist = len(to);
  if (dist <= 1e-6) return b.lockTarget; // muzzle on top of the target: trivially in-cone
  const cos = (to.x * dir.x + to.y * dir.y + to.z * dir.z) / dist;
  return cos >= Math.cos(HOMING.AIM_CONE_HALF_ANGLE_RAD) ? b.lockTarget : null;
}

function spawnProjectile(
  b: BorgRuntime,
  p: BorgProfile,
  shotDef: ShotActionDef,
  yawOffset: number,
  chargeTier = 0,
  all: BorgRuntime[] = [],
  chargeLeaf: ExactMoveLeaf | null = null,
): Projectile {
  const yaw = b.rotY + yawOffset;
  const fwd = { x: Math.sin(yaw), y: 0, z: Math.cos(yaw) };
  const tier = chargeScaling(shotDef, chargeTier);
  // Muzzle world position: the ROM reads it per-muzzle from the weapon-param table
  // DAT_802d39dc (spawn zz_006ee14_ 0x8006ee14, chunk_0009.c:3769) — identified but UNDUMPED,
  // so offsets stay TUNED. Per-borg values come from actionProfiles data; the shared
  // constants.ts MUZZLE_OFFSET is the sim/render default (the renderer's muzzle flash uses
  // the same constant so flash and projectile agree).
  const muzzlePos = {
    x: b.pos.x + fwd.x * (shotDef.muzzleForwardOffset ?? MUZZLE_OFFSET.forward),
    y: b.pos.y + (shotDef.muzzleYOffset ?? MUZZLE_OFFSET.up),
    z: b.pos.z + fwd.z * (shotDef.muzzleForwardOffset ?? MUZZLE_OFFSET.forward),
  };
  const flightVisual = shotFlightVisualForBorgId(b.borgId);
  return {
    uid: `proj_${projCounter++}`,
    ownerUid: b.uid,
    team: b.team,
    pos: muzzlePos,
    vel: scale(fwd, shotDef.speed * tier.speed),
    damage: shotDef.damageMultiplier * tier.damage,
    hitstun: Math.max(1, Math.round(SHOT.HITSTUN * shotDef.hitstunMultiplier * tier.hitstun)),
    // Per-move MULTIPLIER (applyHit derives the base from the projectile's damage record).
    knockback: shotDef.knockbackMultiplier * tier.knockback,
    homingTurn: shotDef.homingTurn,
    // Spawn-time aim-cone gate (FUN_8006c334) — no longer unconditional.
    homingTarget: homingTargetForSpawn(b, all, muzzlePos, fwd),
    // ROM attack-object target +0xcc for the results DODGE counters (aimed vs stray).
    aimedTargetUid: activeSourceTargetUid(b),
    life: shotDef.lifetime,
    // DERIVED where present: the borg's B-shot HIT kind resolves via shotKindForBorgId — the
    // guarded fire-site attribution (shotVariantKinds.json borgShotKinds) when the borg's fire
    // fn was traced to a proven table row, else the ROM's generic shot-child kind-0 heuristic
    // (FUN_80099bb4 chunk_0015.c:1263 etc. — movement-hit-decode-2026-07-04.md). Either way the
    // resolved kind's hit.bin record carries the authored projectile hit volume; its largest
    // extent/radius replaces the TUNED per-profile hitRadius 1:1 (raw world units).
    hitRadius: (shotHitRadiusForBorgId(b.borgId) ?? shotDef.hitRadius) * tier.radius,
    // Charged releases (tier>=1) switch to the profile's distinct charged visual family when
    // one is sourced (ShotActionDef.chargedVisualKind, TUNED-visual from the OBSERVED_WIKI
    // "B Charge" move name — the renderer already draws per-visualKind, so no render change
    // is needed). Tap shots and profiles without the field keep the existing kind.
    visualKind:
      chargeTier >= 1 && shotDef.chargedVisualKind
        ? shotDef.chargedVisualKind
        : shotDef.visualKind ?? projectileVisualKindForProfile(p),
    ...(shotDef.bulletDrop > 0 ? { drop: shotDef.bulletDrop } : {}),
    // OBSERVED_WIKI (moveProperties, ATK-008 consume-vs-persist): a shot whose cataloged move
    // penetrates borgs ("borgs" or "total") passes THROUGH borg hits instead of despawning on the
    // first — set consumeOnHit=false so stepProjectiles paces re-hits via rehitCounter. Default
    // (penetration "none"/null) keeps the structural despawn-on-hit, bit-for-bit. Terrain
    // penetration (the finer "total"-also-ignores-stage-geometry gate) is NOT modeled here and
    // stays subject to the play-area despawn; trace T6 remains the arbiter of the engine mechanism.
    ...(isPenetratingShot(p.id, chargeTier) ? { consumeOnHit: false } : {}),
    // DERIVED mapping (gauges.ts): normal shots are the light-hit archetype (record 0);
    // charged releases hit like the charge/special archetype (record 2), UNLESS the exact
    // charge leaf's own record resolved (chargeDamageRecordSpread below), in which case its
    // damageRecord spread wins on top of this fallback index/no-op.
    damageRecordIndex:
      chargeTier >= 1 ? DAMAGE_RECORD_INDEX.CHARGE_OR_SPECIAL : DAMAGE_RECORD_INDEX.SHOT,
    // EXACT per-borg record for plain shots (the ROM path: the borg's resolved-kind hitbox
    // record's u16+0x04 indexes the FAMILY damage table bound at actor+0x27c —
    // familyDamageData.ts; resolved kind is shotKindForBorgId's proven attribution when present,
    // else kind 0).
    // Charged releases prefer the exact charge-leaf record (chargeDamageRecordSpread) when the
    // borg's remap actually carries it; otherwise they keep the CHARGE_OR_SPECIAL archetype.
    ...(chargeTier === 0 ? shotFamilyRecordSpread(b.borgId) : chargeDamageRecordSpread(b.borgId, chargeLeaf)),
    // DERIVED where present: the borg's B-shot flight visual (efct00 bank texId/team-tint/
    // launch-FX) resolved from the SAME guarded fire-site attribution as shotKindForBorgId,
    // restricted to the one row shape proven to carry this field layout (attackHitData.ts
    // shotFlightVisualForBorgId — research/decomp/efct-consumers-decode-2026-07-04.md §3).
    // undefined (the common case today — no borg has a provable attribution landing on a bank
    // row yet) keeps the renderer's existing sprite/mesh visualKind exactly as before.
    ...(flightVisual ? { flightVisual } : {}),
  };
}

/** Resolve the borg's exact plain-shot damage record: the borg's resolved B-shot HIT kind
 *  (shotKindForBorgId — the guarded fire-site attribution when proven, else the kind-0
 *  heuristic) hitbox record → family table. Empty spread when either half is missing
 *  (archetype fallback stays in effect). */
function shotFamilyRecordSpread(borgId: string): { damageRecord?: DamageRecord } {
  const kind = shotKindForBorgId(borgId) ?? 0;
  const hitRecords = attackHitRecordsForKind(borgId, kind);
  const first = hitRecords[0];
  if (!first) return {};
  const record = familyDamageRecordForBorg(borgId, first.damageRecordIndex);
  return record ? { damageRecord: record } : {};
}

/**
 * Resolve a charged release's exact damage record from its charge leaf (actionStreamData.ts
 * chargeMoveForBorgId), gated to ONLY apply when the leaf's kind has real records in the
 * borg's OWN hit-remap (attackHitTableForBorgId(id).kinds) — task requirement: many charge
 * streams are windup-only (kind null, e.g. G RED's chest-beam stream, whose real hit is a
 * spawned projectile child, not this shot projectile) or arm a kind the borg's remap never
 * populated, and in both cases the generic CHARGE_OR_SPECIAL archetype set above must stand.
 * Empty spread whenever the gate fails or the leaf/record itself didn't resolve.
 */
function chargeDamageRecordSpread(borgId: string, chargeLeaf: ExactMoveLeaf | null): { damageRecord?: DamageRecord } {
  if (!chargeLeaf || chargeLeaf.kind === null || !chargeLeaf.damageRecord) return {};
  const remapHasKind = (attackHitTableForBorgId(borgId)?.kinds[String(chargeLeaf.kind)]?.length ?? 0) > 0;
  if (!remapHasKind) return {};
  return { damageRecord: chargeLeaf.damageRecord };
}

/**
 * Resolve an X special's exact damage record from its resolved leaf (actionStreamData.ts
 * xMoveForBorgId), gated EXACTLY like chargeDamageRecordSpread: only apply when the leaf's
 * kind has real records in the borg's OWN hit-remap (attackHitTableForBorgId(id).kinds) — many
 * X leaves are windup-only (kind null) or arm a kind the borg's remap never populated, and in
 * both cases the generic CHARGE_OR_SPECIAL archetype record must stand. Empty spread whenever
 * the gate fails or the leaf/record itself didn't resolve. Shared by both special archetypes
 * (AoE burst reads `.damageRecord` directly; the projectile archetype spreads this object the
 * same way spawnProjectile spreads chargeDamageRecordSpread).
 */
function xDamageRecordSpread(borgId: string, xLeaf: ExactMoveLeaf | null): { damageRecord?: DamageRecord } {
  if (!xLeaf || xLeaf.kind === null || !xLeaf.damageRecord) return {};
  const remapHasKind = (attackHitTableForBorgId(borgId)?.kinds[String(xLeaf.kind)]?.length ?? 0) > 0;
  if (!remapHasKind) return {};
  return { damageRecord: xLeaf.damageRecord };
}

/** OBSERVED_WIKI: whether a borg's primary shot (B Shot, or B Charge when chargeTier>=1) is
 *  cataloged as penetrating borgs ("borgs"/"total"). Drives spawnProjectile's consumeOnHit. */
function isPenetratingShot(borgId: string, chargeTier: number): boolean {
  const pen = runtimeShotPenetrationForBorgId(borgId, chargeTier >= 1);
  return pen === "borgs" || pen === "total";
}

/** Combo-finisher sword beam: fast, short-lived projectile using charge/special record damage.
 *  The multiplier remains a port-side bridge until the real hitbox record is mapped. */
function spawnSwordBeam(
  b: BorgRuntime,
  meleeDef: MeleeActionDef,
  beam: SwordBeamDef,
  all: BorgRuntime[],
): Projectile {
  const fwd = forwardFromYaw(b.rotY);
  // TUNED spawn offsets (forward 40 / up 20): a port-side design value for the beam's launch
  // point — no ROM anchor (the sword-beam emitter is not one of the dumped muzzle params).
  const spawnPos = {
    x: b.pos.x + fwd.x * 40,
    y: b.pos.y + 20,
    z: b.pos.z + fwd.z * 40,
  };
  return {
    uid: `proj_${projCounter++}`,
    ownerUid: b.uid,
    team: b.team,
    pos: spawnPos,
    vel: scale(fwd, beam.speed),
    damage: meleeDef.damageMultiplier * beam.damageMultiplier,
    hitstun: SHOT.HITSTUN,
    // Per-move MULTIPLIER (applyHit derives the base from the beam's damage record).
    knockback: meleeDef.knockbackMultiplier,
    homingTurn: beam.homingTurn,
    // Same spawn-time aim-cone gate as gun projectiles (FUN_8006c334, chunk_0009.c:1995/3841).
    homingTarget: homingTargetForSpawn(b, all, spawnPos, fwd),
    // ROM attack-object target +0xcc for the results DODGE counters (aimed vs stray).
    aimedTargetUid: activeSourceTargetUid(b),
    life: beam.lifetime,
    hitRadius: beam.hitRadius,
    visualKind: beam.visualKind,
    // Combo-finisher beam hits like the charge/special archetype (DERIVED mapping, gauges.ts):
    // heavier than a normal shot but not the always-stagger melee record — the beam is a
    // projectile, and the melee finisher itself already forces the knockdown.
    damageRecordIndex: DAMAGE_RECORD_INDEX.CHARGE_OR_SPECIAL,
  };
}

// ---------------------------------------------------------------------------------------
// Projectiles — advance, home toward target, resolve hits. Returns survivors.
// ---------------------------------------------------------------------------------------
export function stepProjectiles(
  projectiles: Projectile[],
  all: BorgRuntime[],
  profiles: Map<string, BorgProfile>,
  byUid: Map<string, BorgRuntime>,
  ctx?: ProjectileContext,
  damageContext: DamageRuntimeContext = {},
): Projectile[] {
  const survivors: Projectile[] = [];
  for (const pr of projectiles) {
    pr.hitConfirmedThisFrame = false;
    pr.life -= 1;
    if (pr.life <= 0) {
      pr.despawnReason = "expired"; // life seed: FUN_8006f11c, 600 frames (chunk_0009.c:3907)
      continue;
    }

    // Owner-liveness despawn — zz_00840b8_ (chunk_0012.c:3216), called every frame from the
    // projectile update FUN_8006f0cc: a projectile whose owner actor is dead is removed.
    // battle.ts's byUid map retains defeated borgs (alive === false) rather than deleting
    // them, so "found && !alive" covers the ROM's dead-or-gone case in real battles; a
    // MISSING uid only occurs for synthetic callers (selfchecks/fixtures passing empty maps)
    // and is treated as "no liveness info" so those fixtures keep working.
    const owner = byUid.get(pr.ownerUid);
    if (owner && !owner.alive) {
      pr.despawnReason = "owner-dead";
      continue;
    }

    // Homing toward the locked target: full 3D angle-clamped steer (FUN_8006c1c8,
    // chunk_0009.c:1947 — axis-angle rotation of the WHOLE velocity vector with a per-frame
    // angle clamp; zz_006c440_, chunk_0009.c:2033 then advances by normalized(vel) * speed).
    // Replaces the old yaw-only XZ rotation, whose `|| SHOT.SPEED` fallback also silently
    // re-accelerated stalled projectiles with no ROM basis — a ~zero-speed projectile now
    // simply skips steering (HOMING.MIN_STEER_SPEED).
    if (pr.homingTarget && pr.homingTurn > 0) {
      const tgt = byUid.get(pr.homingTarget);
      if (tgt && isTargetable(tgt)) steerProjectile3d(pr, tgt.pos);
    }

    // Ballistic drop for bullet-kind projectiles (profile-driven; 0/absent for beams/flames).
    // ROM mechanism: the fly function zz_006f268_ integrates gravity/drag every frame (via
    // FUN_80083874/FUN_80083ad4, chunk_0009.c:3956) from seeds set at init (FUN_8006f11c).
    // The per-projectile magnitude here stays TUNED: the param values are undumped, and raw
    // ROM gravity would not transfer across the port's ~4x world rescale anyway
    // (behavior-notes.md section (bc)).
    if (pr.drop) pr.vel.y -= pr.drop;

    const prevPos = pr.pos;
    pr.pos = add(pr.pos, pr.vel as Vec3);
    if (ctx) {
      const impact = projectileImpactReason(pr, prevPos, ctx);
      if (impact) {
        pr.despawnReason = impact;
        continue;
      }
    }

    // Hit test against any non-owner borg. Same-team hits use the derived 0.25x reducer.
    //
    // Consumption policy (ATK-008, research/decomp/attack-mechanics-findings.md mechanic O):
    //   - Default (`pr.consumeOnHit !== false`, including absent): FIRST valid hit consumes the
    //     projectile — unchanged from the pre-ATK-008 behavior, bit-for-bit.
    //   - Persist (`pr.consumeOnHit === false`): the projectile survives hits; re-hits are paced
    //     by a SINGLE per-object counter (`pr.rehitCounter`), mirroring the ROM's one counter per
    //     object at object+0x4e (NOT a per-target map) reloaded from the damage record's s8+0x16
    //     `rehitIntervalFrames` (chunk_0013.c:1175-1182). The counter gates the NEXT damage
    //     application: if it's > 0 this frame, it only ticks down and no hit is applied (even if
    //     overlapping a valid target); once it reaches 0 the object is hit-ready, applies at most
    //     ONE hit this frame (first valid target found), then reloads — so it can't double-fire
    //     against multiple overlapping targets on the same frame. Interval 0 reloads to 0, so a
    //     hit-ready object stays hit-ready next frame too (unlimited rehit while overlapping,
    //     matching the ROM's interval-0 semantics).
    const persistent = pr.consumeOnHit === false;
    let consumed = false;
    if (persistent && (pr.rehitCounter ?? 0) > 0) {
      // Counter still cooling down: tick it, no hit test this frame.
      pr.rehitCounter = (pr.rehitCounter ?? 0) - 1;
    } else {
      for (const o of all) {
        if (!isTargetable(o) || o.uid === pr.ownerUid) continue;
        if (isInvincible(o)) continue;
        // Vertical hit band |dy| <= 60: TUNED — the ROM's projectile-vs-borg overlap is a real
        // 3D hitbox record test (chunk_0013.c hit pipeline), not a cylinder; this flat band is
        // the port's stand-in until per-move hitbox records are dumped.
        if (distXZ(pr.pos, o.pos) <= pr.hitRadius && Math.abs(pr.pos.y - o.pos.y) <= 60) {
          const op = profiles.get(o.uid);
          // A projectile carrying an exact per-borg FAMILY record (familyDamageData.ts, bound
          // at spawn from the borg's kind-0 hitbox record) uses it; others keep the archetype.
          const record = pr.damageRecord ?? damageRecordByIndex(pr.damageRecordIndex ?? DAMAGE_RECORD_INDEX.SHOT);
          if (op) {
            // Intentionally NOT the zero-vector convention: a projectile's own travel vector
            // (which may have curved via homing) is a more accurate knockback direction than
            // recomputing the ROM's mode-1 attacker->target vector from a possibly-stale shooter
            // origin. Neither is a ROM-confirmed mode for the projectile case specifically (the
            // ROM caller always passes the same hit-context wrapper regardless of melee/shot), so
            // this remains a TUNED choice between two reasonable direction sources.
            const attacker = byUid.get(pr.ownerUid);
            const attackerProfile = profiles.get(pr.ownerUid);
            // T3 burst ally-passthrough (zz_002fd7c_ — the doc's zz_002fd7c_ finding): a
            // bursting teammate's own team's projectile passes through them entirely. Skipped
            // (fail-open, unchanged behavior) when the owner is already gone — there is no
            // attacker to compare teams against.
            if (attacker && burstAllyPassthroughBlocks(attacker, o, record)) continue;
            applyHit(
              o,
              op,
              pr.damage,
              pr.knockback,
              pr.vel as Vec3,
              pr.pos,
              false,
              // Per-projectile record (charge/special = 2, normal shot = 0; gauges.ts).
              record,
              attacker && attackerProfile
                ? {
                    attacker,
                    attackerProfile,
                    damageScale: pr.damage,
                    attackerSideRank: damageContext.sideRankForTeam?.(attacker.team),
                    defenderSideRank: damageContext.sideRankForTeam?.(o.team),
                    // The spawn-time aim (ROM attack object +0xcc), NOT the attacker's
                    // current lock — the shooter may have re-locked mid-flight.
                    aimedTargetUid: pr.aimedTargetUid ?? null,
                  }
                : undefined,
              damageContext,
            );
          }
          pr.hitConfirmedThisFrame = true; // renderer impact-puff trigger (persisting re-hits too)
          // DERIVED: the record's u8 +0x09 impactEffectId selects the contact effect
          // (chunk_0003.c:8152-8155 -> zz_0019550_ -> table 0x802c7ed0); carried for the renderer.
          pr.lastImpactEffectId = record.impactEffectId;
          if (persistent) {
            // Reload the single per-object counter immediately so this same frame's loop can't
            // apply a second hit (the ROM shape: counter gates the next application, then
            // reloads on use). Interval 0 reloads to 0, so the object is still hit-ready next
            // frame (unlimited rehit while overlapping).
            pr.rehitCounter = record.rehitIntervalFrames;
            break;
          }
          consumed = true;
          pr.despawnReason = "hit-target";
          break;
        }
      }
    }
    // Persisting projectiles are never removed by a hit (only life expiry / out-of-bounds
    // above can drop them); the counter above already governs re-hit pacing.
    if (persistent || !consumed) survivors.push(pr);
  }
  return survivors;
}

/** Per-frame 3D homing steer — FUN_8006c1c8 (chunk_0009.c:1947): rotate the FULL velocity
 *  vector toward the target point by an angle clamped to `homingTurn` per frame (axis-angle
 *  about cur x desired), then keep flying at the SAME speed (zz_006c440_, chunk_0009.c:2033:
 *  advance by normalized(vel) * speed(+0x44)). Implemented as a slerp between the current and
 *  desired unit directions — mathematically identical to the clamped axis-angle rotation.
 *  Aim point: the target's tracked origin (the ROM's exact aim-point offset inside the target
 *  comes from undumped params — zero offset is the TUNED choice; the |dy|<=60 TUNED hit band
 *  in stepProjectiles absorbs the residual). */
function steerProjectile3d(pr: Projectile, targetPos: Vec3): void {
  const speed = len(pr.vel as Vec3);
  if (speed <= HOMING.MIN_STEER_SPEED) return; // stalled: no ROM re-acceleration (see HOMING)
  const cur = scale(pr.vel as Vec3, 1 / speed);
  const toTarget = sub(targetPos, pr.pos);
  const dist = len(toTarget);
  if (dist <= 1e-6) return; // on top of the target: no defined steer direction
  const desired = scale(toTarget, 1 / dist);
  const dot = clamp(cur.x * desired.x + cur.y * desired.y + cur.z * desired.z, -1, 1);
  const angle = Math.acos(dot);
  if (angle <= 1e-6) return; // already aligned
  if (angle <= pr.homingTurn) {
    pr.vel = scale(desired, speed); // clamp not binding: snap onto the target direction
    return;
  }
  const sinAngle = Math.sin(angle);
  if (sinAngle <= 1e-6) {
    // Anti-parallel: the rotation axis (cur x desired) degenerates to zero — the ROM builds
    // its axis from the same cross product and its tie-break is unread, so TUNED: turn the
    // horizontal component by the clamp in the +yaw direction this frame (deterministic).
    const horiz = Math.hypot(cur.x, cur.z);
    if (horiz <= 1e-6) return; // straight up/down reversal: leave it for the hit/impact tests
    const newYaw = yawFromXZ(cur.x, cur.z) + pr.homingTurn;
    pr.vel = {
      x: Math.sin(newYaw) * horiz * speed,
      y: cur.y * speed,
      z: Math.cos(newYaw) * horiz * speed,
    };
    return;
  }
  // Slerp cur -> desired by t = homingTurn/angle (equivalent to rotating cur about the
  // cur x desired axis by exactly homingTurn radians).
  const t = pr.homingTurn / angle;
  const w0 = Math.sin((1 - t) * angle) / sinAngle;
  const w1 = Math.sin(t * angle) / sinAngle;
  const dir = normalize({
    x: cur.x * w0 + desired.x * w1,
    y: cur.y * w0 + desired.y * w1,
    z: cur.z * w0 + desired.z * w1,
  });
  pr.vel = scale(dir, speed);
}

/**
 * Despawn test for one projectile frame, with the REASON (null = keep flying):
 *   - "out-of-bounds": outside the stage rect, or no supporting floor beneath the new
 *     position (the pre-existing play-area cull, unchanged semantics).
 *   - "hit-terrain": the frame's movement segment crossed stage collision geometry — the
 *     ROM's terrain/wall impact tests zz_0083244_ (terrain) / zz_0083714_ (wall) called from
 *     the projectile fly function zz_006f268_ (chunk_0009.c:3956). Both floor and wall
 *     triangles are tested with one segment-vs-triangle crossing (no normal filter), and the
 *     projectile position is moved to the impact point so the renderer can place the puff.
 */
function projectileImpactReason(
  projectile: Projectile,
  prevPos: Vec3,
  ctx: ProjectileContext,
): "hit-terrain" | "out-of-bounds" | null {
  const { pos } = projectile;
  if (pos.x < ctx.bounds.minX || pos.x > ctx.bounds.maxX || pos.z < ctx.bounds.minZ || pos.z > ctx.bounds.maxZ) {
    return "out-of-bounds";
  }
  if (!ctx.collision || ctx.collision.triangles.length === 0) return null;
  // Terrain/wall impact: earliest crossing along prev->new (zz_0083244_/zz_0083714_ shape).
  let best: { point: Vec3; t: number } | null = null;
  for (const tri of candidateTrianglesForSegment(ctx.collision, prevPos, pos)) {
    const hit = segmentTriangleImpact(tri, prevPos, pos);
    if (hit && (!best || hit.t < best.t)) best = hit;
  }
  if (best) {
    projectile.pos = best.point;
    return "hit-terrain";
  }
  // Pre-existing floor-presence cull: flying over space with no floor at all counts as
  // leaving the play area (port-side; the original relies on geometry + the 600f lifetime).
  if (floorSurfaceYAt(ctx.collision, pos.x, pos.z, pos.y) == null) return "out-of-bounds";
  return null;
}

/** Segment-vs-triangle crossing for projectile impact. Same solid-geometry filters as the
 *  movement port (marker 0xcccccccc, finite normal/vertices — movement.ts
 *  segmentTriangleWallHit / physics bestFloorFromCandidates), but with NO normal-direction
 *  filter: floors, walls, and ceilings all stop a projectile (zz_006f268_ runs both the
 *  terrain and wall tests, chunk_0009.c:3956). */
function segmentTriangleImpact(
  tri: StageCollisionTriangle,
  p0: Vec3,
  p1: Vec3,
): { point: Vec3; t: number } | null {
  if (tri.marker !== 0xcccccccc) return null;
  if (!isFiniteVec(tri.normal) || !tri.vertices.every(isFiniteVec)) return null;
  const a = tri.vertices[0];
  const n = tri.normal;
  const d0 = (p0.x - a.x) * n.x + (p0.y - a.y) * n.y + (p0.z - a.z) * n.z;
  const d1 = (p1.x - a.x) * n.x + (p1.y - a.y) * n.y + (p1.z - a.z) * n.z;
  if (!Number.isFinite(d0) || !Number.isFinite(d1)) return null;
  if (Math.abs(d0 - d1) < 1e-5) return null; // parallel to the plane
  if (d0 === 0 || d0 * d1 > 0) return null; // no crossing (start-on-plane skipped, as movement.ts)
  const t = d0 / (d0 - d1);
  if (t < -1e-4 || t > 1 + 1e-4) return null;
  const point = {
    x: p0.x + (p1.x - p0.x) * t,
    y: p0.y + (p1.y - p0.y) * t,
    z: p0.z + (p1.z - p0.z) * t,
  };
  return pointInTriangleByDominantAxis(point, tri) ? { point, t } : null;
}

/** Point-in-triangle via barycentric weights on the plane's dominant-axis 2D projection
 *  (pure fixed-step math; tolerances mirror physics yAtTriangleXZ). */
function pointInTriangleByDominantAxis(p: Vec3, tri: StageCollisionTriangle): boolean {
  const [a, b, c] = tri.vertices;
  const n = tri.normal;
  const ax = Math.abs(n.x);
  const ay = Math.abs(n.y);
  const az = Math.abs(n.z);
  let pu: number, pv: number, u0: number, v0: number, u1: number, v1: number, u2: number, v2: number;
  if (ay >= ax && ay >= az) {
    pu = p.x; pv = p.z; u0 = a.x; v0 = a.z; u1 = b.x; v1 = b.z; u2 = c.x; v2 = c.z;
  } else if (ax >= az) {
    pu = p.y; pv = p.z; u0 = a.y; v0 = a.z; u1 = b.y; v1 = b.z; u2 = c.y; v2 = c.z;
  } else {
    pu = p.x; pv = p.y; u0 = a.x; v0 = a.y; u1 = b.x; v1 = b.y; u2 = c.x; v2 = c.y;
  }
  const denom = (v1 - v2) * (u0 - u2) + (u2 - u1) * (v0 - v2);
  if (Math.abs(denom) < 1e-8) return false; // degenerate projection
  const wa = ((v1 - v2) * (pu - u2) + (u2 - u1) * (pv - v2)) / denom;
  const wb = ((v2 - v0) * (pu - u2) + (u0 - u2) * (pv - v2)) / denom;
  const wc = 1 - wa - wb;
  return wa >= -1e-4 && wb >= -1e-4 && wc >= -1e-4;
}

