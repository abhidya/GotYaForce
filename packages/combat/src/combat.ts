// Combat: lock-on, melee (B), ranged shot (B for ranged borgs), special (X), projectiles
// with homing, damage = f(attack/shot, defense), hitstun -> "hit", knockdown -> "down" ->
// wake with invincTimer=60 (the decomp countdown, ported exactly), cooldowns + ammo/reload.
//
// Invincibility port (behavior-notes.md s4a, struct+0x720): each frame, if timer>0 subtract
// 1.0 and clamp at 0. Entering the wake state sets it to 60. See stepInvincibility().

import {
  add,
  distXZ,
  floorSurfaceYAt,
  forwardFromYaw,
  knockbackDirectionFromPositions,
  normalize,
  scale,
  yawFromXZ,
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
  MASH,
  MELEE,
  LOCK,
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
  type DamageRecord,
} from "./gauges.js";
import {
  actionProfileForProfile,
  weaponOneCellSourceForBorgId,
  type MeleeActionDef,
  type ShotActionDef,
  type SwordBeamDef,
} from "./actionProfiles.js";
import type { BorgProfile } from "./stats.js";
import { computeSourceDamage } from "./damageFormula.js";
import { applyStatusFromRecord } from "./status.js";
import type {
  BorgRuntime,
  Projectile,
  ProjectileVisualKind,
  RectStageBounds,
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
    // jumpHeld / switchLockHeld / allyLockHeld / hyperHeld / attackHeld are 0/1 press latches,
    // boostFuel is a fuel gauge, chargeFrames is a hold-B charge accumulator, comboStep is the
    // current melee-chain index, and mashCount (ATK-017) is a press-edge COUNTER (not a
    // countdown timer) that combat.ts's mash-counting code owns entirely (increments on press
    // edges during an active swing, resets on swing start) — none of these decay 1/frame like
    // the countdown timers this loop drives, so all are skipped here.
    if (
      k === "jumpHeld" ||
      k === "boostFuel" ||
      k === "switchLockHeld" ||
      k === "allyLockHeld" ||
      k === "hyperHeld" ||
      k === "attackHeld" ||
      k === "chargeFrames" ||
      k === "comboStep" ||
      k === "mashCount"
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
// refillParam at struct+0x78c stride 8). Weapon 0 drives the existing shot path (B) and
// mirrors BorgRuntime.ammo for compat; cells 1/2 exist structurally but nothing reads them
// yet (no per-weapon command resolver in the port).
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
 *  is data-sourced but STILL STRUCTURALLY UNUSED (no per-weapon command resolver dispatches to
 *  it yet — ATK-009 "Required behavior"); weapon 2 has no stat-row data at all (the ROM's
 *  per-borg row only carries 2 weapon segments) and stays fully inert (max 0 = infinite/
 *  unused). */
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
  const weapon1Source = weaponOneCellSourceForBorgId(p.id);
  const weapon1: WeaponCell = weapon1Source
    ? {
        cur: weapon1Source.max, // weapon 1 is never fired by the port yet; start full like spawn init does.
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
// Enemy lock-on (R switch-lock) and ally lock-on (Z).
//
// TUNED, and CHECKED CLOSED (2026-07-01, behavior-notes.md s4q): this is not a partially-derived
// stand-in awaiting a future decode — a thorough corpus search (borg state-machine dispatch,
// every writer of the 6-actor-table "last enemy" globals DAT_803b06a8/object+2000/+0x7d1,
// every loop over DAT_803c4e84, every PSVEC distance-check call site, PAD/SI input symbols) found
// no button-triggered scan-and-select enemy-lock mechanic anywhere in the ROM. Every "target"
// field the decomp has is hit-REACTIVE bookkeeping (remembers who last hit whom, for a one-shot
// reaction animation via react_to_slot_target_object/start_status_reaction_by_side), never a
// scan-selective player lock system. So there is no real algorithm to port here — this heuristic
// (nearest enemy in a forward view-cone, scored by distance*angle) is an honest design choice,
// not a guess standing in for a known-but-undecoded formula. Do not re-derive without new leads.
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

function isTargetable(b: BorgRuntime): boolean {
  return b.alive && b.hp > 0 && b.state !== "death";
}

/** Acquire the nearest enemy that is in front (within the lock cone) and in range. */
export function acquireLock(self: BorgRuntime, all: BorgRuntime[]): string | null {
  const fwd = forwardFromYaw(self.rotY);
  let best: string | null = null;
  let bestScore = Infinity;
  for (const o of all) {
    if (!isEnemyAlive(self, o)) continue;
    const d = distXZ(self.pos, o.pos);
    if (d > LOCK.RANGE) continue;
    const to = normalize({ x: o.pos.x - self.pos.x, y: 0, z: o.pos.z - self.pos.z });
    const dot = fwd.x * to.x + fwd.z * to.z;
    const ang = Math.acos(Math.max(-1, Math.min(1, dot)));
    if (ang > LOCK.CONE) continue;
    // Prefer closer + more-centered targets.
    const score = d * (1 + ang);
    if (score < bestScore) {
      bestScore = score;
      best = o.uid;
    }
  }
  return best;
}

/** Cycle to the next enemy by distance (R = switch lock-on target). Enemy-only by
 * construction (isEnemyAlive filters dead borgs, self, and same-team allies); the caller
 * (battle.ts) edge-triggers this so holding R does not re-cycle every frame. */
export function cycleLock(self: BorgRuntime, all: BorgRuntime[]): string | null {
  const enemies = all
    .filter((o) => isEnemyAlive(self, o) && distXZ(self.pos, o.pos) <= LOCK.RANGE)
    .sort((a, b) => distXZ(self.pos, a.pos) - distXZ(self.pos, b.pos));
  if (enemies.length === 0) return null;
  const curIdx = enemies.findIndex((o) => o.uid === self.lockTarget);
  const next = enemies[(curIdx + 1) % enemies.length];
  return next ? next.uid : null;
}

/** Z ally-lock target selection. CONFIRMED-ASSET input, TUNED nearest-ally selection.
 * The original ally charge/power-up behavior is not decoded yet, so this only records a
 * same-team target for HUD/debug/future mechanics and never redirects enemy attacks. */
export function acquireAllyLock(self: BorgRuntime, all: BorgRuntime[]): string | null {
  let best: string | null = null;
  let bestDist = Infinity;
  for (const o of all) {
    if (!isAllyAlive(self, o)) continue;
    const d = distXZ(self.pos, o.pos);
    if (d > LOCK.RANGE || d >= bestDist) continue;
    bestDist = d;
    best = o.uid;
  }
  return best;
}

/** Cycle to the next same-team ally by distance (repeated Z presses). Ally-only by
 * construction (isAllyAlive filters dead borgs, self, and enemies). With no current
 * ally lock this selects the nearest ally, matching acquireAllyLock. TUNED — the
 * original per-press Z semantics are untraced; edge-triggering lives in battle.ts. */
export function cycleAllyLock(self: BorgRuntime, all: BorgRuntime[]): string | null {
  const allies = all
    .filter((o) => isAllyAlive(self, o) && distXZ(self.pos, o.pos) <= LOCK.RANGE)
    .sort((a, b) => distXZ(self.pos, a.pos) - distXZ(self.pos, b.pos));
  if (allies.length === 0) return null;
  const curIdx = allies.findIndex((o) => o.uid === self.allyLockTarget);
  const next = allies[(curIdx + 1) % allies.length];
  return next ? next.uid : null;
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
}

export interface DamageRuntimeContext {
  sideRankForTeam?: ((team: number) => number | undefined) | undefined;
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
  knockback: number,
  knockDir: Vec3,
  fromPos: Vec3,
  forceKnockdown = false,
  // Default = melee archetype so legacy callers keep the old always-interrupt behavior.
  record: DamageRecord = damageRecordByIndex(DAMAGE_RECORD_INDEX.MELEE),
  source?: HitSourceContext,
): number {
  if (!isTargetable(victim) || isInvincible(victim)) return 0;

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

  // Knockback DIRECTION — ROM-accurate port of zz_00300bc_ (0x800300bc), mode 1 ("attacker to
  // target" relative-position vector -> atan2 -> BAM16 yaw), the only one of the ROM's 5 vector-
  // source modes this port has enough data to compute (see packages/physics/src/knockback.ts
  // header and behavior-notes.md section (p) for the other 4 modes and why they're not wired).
  // `knockDir` lets a caller override with a more specific vector (e.g. a projectile's travel
  // direction) when the "attacker position" isn't the right source (fromPos is still passed as
  // the attacker-position input to the mode-1 calc either way).
  // Knockback MAGNITUDE remains a flat TUNED scalar (`knockback` param) — the ROM function only
  // ever computes/stores direction, never a speed/force value; see constants.ts MELEE/SHOT/SPECIAL.
  const dir =
    knockDir.x === 0 && knockDir.z === 0
      ? knockbackDirectionFromPositions(fromPos, victim.pos)
      : normalize(knockDir);
  victim.vel.x = dir.x * knockback;
  victim.vel.z = dir.z * knockback;
  if (knockback > 0) victim.vel.y = Math.max(victim.vel.y, knockback * 0.4);

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
  victim.comboAccum += record.comboScoreValue;
  if (victim.comboAccum > 99) {
    victim.comboAccum = 0;
    victim.comboRank = Math.min(0x3f, victim.comboRank + 1);
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

  // Reaction LENGTH stays the port's TUNED hitstun/down durations (animation-gated in ROM).
  const knockdown = forceKnockdown || dmg >= DAMAGE.KNOCKDOWN_DMG;
  if (knockdown) {
    enterDown(victim);
  } else {
    enterHit(victim, MELEE.HITSTUN);
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

export function enterHit(b: BorgRuntime, stun: number): void {
  b.state = "hit";
  b.stateTime = 0;
  b.anim = "hit";
  b.cooldowns["hitstun"] = stun;
}

export function enterDown(b: BorgRuntime): void {
  b.state = "down";
  b.stateTime = 0;
  b.anim = "down";
  b.grounded = false; // gets knocked off the ground; lands during down
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
      if (b.stateTime >= STATE.DOWN_DURATION && b.grounded) {
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
 * Process B (attack) and Y (special) for one borg. Mutates `b` (state, cooldowns, ammo) and
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
  pressedSpecial: boolean,
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

  // --- Special (X) -------------------------------------------------------------------
  const canStartAction = b.state !== "attack" && b.state !== "special";
  if (canStartAction && pressedSpecial && (b.cooldowns["special"] ?? 0) <= 0) {
    const specialDef = actionProfile.special;
    b.cooldowns["special"] = specialDef.cooldown;
    b.cooldowns["attackLock"] = specialDef.duration;
    b.state = "special";
    b.stateTime = 0;
    b.anim = "special";
    // AoE burst around the borg. HP damage comes from record 2 via damageFormula.ts; the
    // special multiplier remains a port-side bridge until per-special hitbox records are mapped.
    const specialRecord = damageRecordByIndex(DAMAGE_RECORD_INDEX.CHARGE_OR_SPECIAL);
    for (const o of all) {
      if (!canReceiveHit(b, o)) continue;
      if (distXZ(b.pos, o.pos) <= specialDef.radius) {
        const op = profiles.get(o.uid);
        if (op) {
          // Zero vector -> applyHit() computes the real ROM-mode-1 direction (attacker->target,
          // via the ported zz_00300bc_ atan2/BAM16 calc) instead of this raw un-ported subtract.
          applyHit(
            o,
            op,
            0,
            SPECIAL.KNOCKBACK * specialDef.knockbackMultiplier,
            { x: 0, y: 0, z: 0 },
            b.pos,
            true,
            // Specials -> record 2 (DERIVED mapping, gauges.ts DAMAGE_RECORD_INDEX).
            specialRecord,
            {
              attacker: b,
              attackerProfile: p,
              damageScale: specialDef.damageMultiplier,
              attackerSideRank: damageContext.sideRankForTeam?.(b.team),
              defenderSideRank: damageContext.sideRankForTeam?.(o.team),
            },
          );
        }
      }
    }
    return { projectiles: out };
  }

  // --- Attack (B): asset-backed per-borg primary action, generic fallback-safe -------
  if (canStartAction && (attackHeld || releasedAttack)) {
    const order =
      actionProfile.primary === "shot"
        ? (["shot", "melee"] as const)
        : (["melee", "shot"] as const);
    for (const kind of order) {
      if (kind === "melee" && meleeDef && attackHeld) {
        const window = b.cooldowns["comboWindow"] ?? 0;
        const prevStep = b.cooldowns["comboStep"] ?? 0;
        // Chain: within the combo window and more hits remain — bypass the melee cooldown.
        const canChain = window > 0 && prevStep + 1 < meleeDef.comboHits;
        const canFresh = (b.cooldowns["melee"] ?? 0) <= 0;
        if (canChain || canFresh) {
          startMeleeAttack(b, meleeDef, canChain ? prevStep + 1 : 0);
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
            startShotAttack(b, p, shotDef, tier, out);
            break;
          }
          continue;
        }
        if (attackHeld) {
          startShotAttack(b, p, shotDef, 0, out);
          break;
        }
      }
    }
  }

  // --- Resolve an active melee swing against enemies in reach ------------------------
  const meleeActive = b.cooldowns["meleeActive"] ?? 0;
  if (b.state === "attack" && b.anim === "melee" && meleeDef && meleeActive > 0 && STATE.MELEE_IFRAME_REFRESH_PER_FRAME) {
    b.invincTimer = WAKE_UP_INVINCIBILITY_FRAMES;
  }
  if (b.state === "attack" && b.anim === "melee" && meleeDef && meleeActive > 0 && meleeActive <= meleeDef.active) {
    const comboStep = b.cooldowns["comboStep"] ?? 0;
    const isFinisher = comboStep >= meleeDef.comboHits - 1;
    // Sword beam: the combo finisher's FIRST active frame emits a fast short-lived projectile
    // with melee-scaled damage (TUNED design; see actionProfiles.ts SwordBeamDef).
    if (meleeDef.swordBeam && isFinisher && meleeActive === meleeDef.active) {
      out.push(spawnSwordBeam(b, meleeDef, meleeDef.swordBeam));
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
      if (d > meleeDef.range) continue;
      if (Math.abs(o.pos.y - b.pos.y) > meleeDef.yTolerance) continue;
      const to = normalize({ x: o.pos.x - b.pos.x, y: 0, z: o.pos.z - b.pos.z });
      if (fwd.x * to.x + fwd.z * to.z < 0) continue; // behind us
      const op = profiles.get(o.uid);
      if (!op) continue;
      const knockbackMult =
        meleeDef.knockbackMultiplier * (isFinisher && meleeDef.comboHits > 1 ? COMBO.FINISHER_KNOCKBACK_MULT : 1);
      const meleeRecord = damageRecordByIndex(DAMAGE_RECORD_INDEX.MELEE);
      // Zero vector -> applyHit() computes the real ROM-mode-1 direction (attacker->target)
      // instead of the attacker's facing vector (`fwd`) used here previously.
      const dealt = applyHit(
        o,
        op,
        0,
        MELEE.KNOCKBACK * knockbackMult,
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

function startMeleeAttack(b: BorgRuntime, meleeDef: MeleeActionDef, comboStep: number): void {
  // Chained swings come out faster (COMBO.STEP_STARTUP_SCALE); the opener uses full startup.
  const startup =
    comboStep > 0 ? Math.max(2, Math.round(meleeDef.startup * COMBO.STEP_STARTUP_SCALE)) : meleeDef.startup;
  b.cooldowns["melee"] = meleeDef.duration + meleeDef.cooldown;
  b.cooldowns["meleeActive"] = startup + meleeDef.active;
  b.cooldowns["attackLock"] = meleeDef.duration;
  // The chain window covers this swing plus a grace period after its recovery. The renderer
  // alternates melee/melee_alt banks on each melee re-entry (battleScene meleeParity), and the
  // >=1 idle frame between chained swings is what lets it see the re-entry.
  b.cooldowns["comboWindow"] = meleeDef.duration + meleeDef.comboWindowFrames;
  b.cooldowns["comboStep"] = comboStep;
  b.meleeHitUids = []; // fresh swing: everyone is hittable once again
  // ATK-017 mash-counter scaffold: every new swing (opener or chained) resets the press-edge
  // counter to 0 — see the mash-counting block in stepAttacks for what increments it.
  b.cooldowns["mashCount"] = 0;
  b.state = "attack";
  b.stateTime = 0;
  b.anim = "melee";
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
  b.anim = "shoot";
  out.push(...spawnProjectiles(b, p, shotDef, chargeTier));
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

function spawnProjectiles(
  b: BorgRuntime,
  p: BorgProfile,
  shotDef: ShotActionDef,
  chargeTier = 0,
): Projectile[] {
  const count = Math.max(1, Math.floor(shotDef.projectileCount));
  const projectiles: Projectile[] = [];
  for (let i = 0; i < count; i += 1) {
    const centered = count === 1 ? 0 : i - (count - 1) / 2;
    projectiles.push(spawnProjectile(b, p, shotDef, centered * shotDef.spreadRadians, chargeTier));
  }
  return projectiles;
}

function spawnProjectile(
  b: BorgRuntime,
  p: BorgProfile,
  shotDef: ShotActionDef,
  yawOffset: number,
  chargeTier = 0,
): Projectile {
  const yaw = b.rotY + yawOffset;
  const fwd = { x: Math.sin(yaw), y: 0, z: Math.cos(yaw) };
  const tier = chargeScaling(shotDef, chargeTier);
  return {
    uid: `proj_${projCounter++}`,
    ownerUid: b.uid,
    team: b.team,
    pos: {
      x: b.pos.x + fwd.x * shotDef.muzzleForwardOffset,
      y: b.pos.y + shotDef.muzzleYOffset,
      z: b.pos.z + fwd.z * shotDef.muzzleForwardOffset,
    },
    vel: scale(fwd, shotDef.speed * tier.speed),
    damage: shotDef.damageMultiplier * tier.damage,
    hitstun: Math.max(1, Math.round(SHOT.HITSTUN * shotDef.hitstunMultiplier * tier.hitstun)),
    knockback: SHOT.KNOCKBACK * shotDef.knockbackMultiplier * tier.knockback,
    homingTurn: shotDef.homingTurn,
    homingTarget: b.lockTarget,
    life: shotDef.lifetime,
    hitRadius: shotDef.hitRadius * tier.radius,
    visualKind: shotDef.visualKind ?? projectileVisualKindForProfile(p),
    ...(shotDef.bulletDrop > 0 ? { drop: shotDef.bulletDrop } : {}),
    // DERIVED mapping (gauges.ts): normal shots are the light-hit archetype (record 0);
    // charged releases hit like the charge/special archetype (record 2).
    damageRecordIndex:
      chargeTier >= 1 ? DAMAGE_RECORD_INDEX.CHARGE_OR_SPECIAL : DAMAGE_RECORD_INDEX.SHOT,
  };
}

/** Combo-finisher sword beam: fast, short-lived projectile using charge/special record damage.
 *  The multiplier remains a port-side bridge until the real hitbox record is mapped. */
function spawnSwordBeam(
  b: BorgRuntime,
  meleeDef: MeleeActionDef,
  beam: SwordBeamDef,
): Projectile {
  const fwd = forwardFromYaw(b.rotY);
  return {
    uid: `proj_${projCounter++}`,
    ownerUid: b.uid,
    team: b.team,
    pos: {
      x: b.pos.x + fwd.x * 40,
      y: b.pos.y + 20,
      z: b.pos.z + fwd.z * 40,
    },
    vel: scale(fwd, beam.speed),
    damage: meleeDef.damageMultiplier * beam.damageMultiplier,
    hitstun: SHOT.HITSTUN,
    knockback: SHOT.KNOCKBACK * meleeDef.knockbackMultiplier,
    homingTurn: beam.homingTurn,
    homingTarget: b.lockTarget,
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
    pr.life -= 1;
    if (pr.life <= 0) continue;

    // Homing toward the locked target.
    if (pr.homingTarget) {
      const tgt = byUid.get(pr.homingTarget);
      if (tgt && isTargetable(tgt)) {
        const desired = yawFromXZ(tgt.pos.x - pr.pos.x, tgt.pos.z - pr.pos.z);
        const cur = yawFromXZ(pr.vel.x, pr.vel.z);
        let d = desired - cur;
        while (d > Math.PI) d -= Math.PI * 2;
        while (d < -Math.PI) d += Math.PI * 2;
        const step = Math.max(-pr.homingTurn, Math.min(pr.homingTurn, d));
        const newYaw = cur + step;
        const speed = Math.hypot(pr.vel.x, pr.vel.z) || SHOT.SPEED;
        pr.vel = { x: Math.sin(newYaw) * speed, y: pr.vel.y, z: Math.cos(newYaw) * speed };
      }
    }

    // Ballistic drop for bullet-kind projectiles (profile-driven; 0/absent for beams/flames).
    if (pr.drop) pr.vel.y -= pr.drop;

    pr.pos = add(pr.pos, pr.vel as Vec3);
    if (ctx && !projectileInPlayArea(pr, ctx)) continue;

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
        if (distXZ(pr.pos, o.pos) <= pr.hitRadius && Math.abs(pr.pos.y - o.pos.y) <= 60) {
          const op = profiles.get(o.uid);
          const record = damageRecordByIndex(pr.damageRecordIndex ?? DAMAGE_RECORD_INDEX.SHOT);
          if (op) {
            // Intentionally NOT the zero-vector convention: a projectile's own travel vector
            // (which may have curved via homing) is a more accurate knockback direction than
            // recomputing the ROM's mode-1 attacker->target vector from a possibly-stale shooter
            // origin. Neither is a ROM-confirmed mode for the projectile case specifically (the
            // ROM caller always passes the same hit-context wrapper regardless of melee/shot), so
            // this remains a TUNED choice between two reasonable direction sources.
            const attacker = byUid.get(pr.ownerUid);
            const attackerProfile = profiles.get(pr.ownerUid);
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
                  }
                : undefined,
            );
          }
          if (persistent) {
            // Reload the single per-object counter immediately so this same frame's loop can't
            // apply a second hit (the ROM shape: counter gates the next application, then
            // reloads on use). Interval 0 reloads to 0, so the object is still hit-ready next
            // frame (unlimited rehit while overlapping).
            pr.rehitCounter = record.rehitIntervalFrames;
            break;
          }
          consumed = true;
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

function projectileInPlayArea(projectile: Projectile, ctx: ProjectileContext): boolean {
  const { pos } = projectile;
  if (pos.x < ctx.bounds.minX || pos.x > ctx.bounds.maxX || pos.z < ctx.bounds.minZ || pos.z > ctx.bounds.maxZ) {
    return false;
  }
  if (!ctx.collision || ctx.collision.triangles.length === 0) return true;
  return floorSurfaceYAt(ctx.collision, pos.x, pos.z, pos.y) != null;
}

