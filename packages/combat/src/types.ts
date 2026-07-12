// Public types for the deterministic battle API. Mirrors the contract in the task brief.
// Control scheme (CONFIRMED from the game's controls screen + lock-relative movement trace):
//   A=jump, B=attack(melee/contextual), X=special, R=switch lock-on target,
//   hold Z=ally lock-on (target selection only; ally charge/power-up behavior not decoded yet),
//   stick=move in the target-relative frame while locked. Pure left/right is a dodge step
//   (surfaced as `dash`); forward+left/right is circle-strafe.

import type { StageBounds, StageCollision, Vec3 } from "@gf/physics";
export {
  normalizeStageBounds,
  type RectStageBounds,
  type StageBounds,
  type StageCollision,
  type StageCollisionCell,
  type StageCollisionTriangle,
  type SymmetricStageBounds,
} from "@gf/physics";
import type { BorgProfile } from "./stats.js";
// Re-exported here (index.ts does `export * from "./types.js"`) so the renderer can import the
// shared sim/render muzzle offset from the package root — see constants.ts MUZZLE_OFFSET.
export { MUZZLE_OFFSET } from "./constants.js";

/** One frame of intent for a single controlled borg (player OR resolved by AI). */
export interface PlayerInput {
  /** Stick X in [-1,1] (+X). */
  moveX: number;
  /** Stick Z in [-1,1] (+Z = forward, per RAM trace). */
  moveZ: number;
  /** A — jump / air-jump / hold for boost flight. */
  jump: boolean;
  /** B — melee / contextual attack. */
  attack: boolean;
  /** X — special attack. */
  special: boolean;
  /** Acquire / hold lock-on for non-player callers; human-controlled borgs auto-lock by default. */
  lockOn: boolean;
  /** R — cycle lock-on target forward/source request +0x73c=2. */
  switchLock: boolean;
  /** L — cycle lock-on target backward/source request +0x73c=3. */
  switchLockPrev: boolean;
  /** Hold Z — ally lock-on request; release restores the retained enemy lock. Ally charge behavior is still unknown. */
  allyLock: boolean;
  /** Reserved/prototype; Challenge battle core ignores manual switching until original proof exists. */
  switchBorg: boolean;
  /** Step/dodge (stick-action). */
  dash: boolean;
  /** Y — Hyper/Power Burst arm/activate input. Evidence: `FUN_80069814` chunk_0009.c:104-115
   *  (Y-family bit in transformed word +0x5d4 sets +0x6fb = 6, a 6-frame arm window). */
  hyper: boolean;
}

export function emptyInput(): PlayerInput {
  return {
    moveX: 0,
    moveZ: 0,
    jump: false,
    attack: false,
    special: false,
    lockOn: false,
    switchLock: false,
    switchLockPrev: false,
    allyLock: false,
    switchBorg: false,
    dash: false,
    hyper: false,
  };
}

/** Main borg state (maps to decomp struct+0x544 action enum: idle/move/attack/damage/down/death). */
export type BorgState =
  | "idle"
  | "move"
  | "jump"
  | "fly"
  | "attack"
  | "special"
  | "hit"
  | "down"
  | "death"
  | "spawn";

/** Live, per-frame runtime state of one borg instance. */
export interface ActorParamTier {
  /** `actor+0x74a`, reset by C `reset_actor_param_tier` to 0x10. */
  tier: number;
  /** `actor+0x74e`, signed byte accumulator touched by `apply_actor_param_tier_delta_63`. */
  deltaAccum: number;
  /** `actor+0x750`, set to 900 by `apply_actor_param_tier_delta_63` when accumulator is nonzero. */
  timerFrames: number;
}

/** ROM refill-type enum for a weapon cell's aux `+0x790` field (ATK-009, findings mechanic P):
 *  `type <= 0` = all-at-once (cur stays 0 until the refill timer expires, then jumps to max);
 *  `type === 1` = gradual (fractional grant toward max every frame the timer is running);
 *  `type 2/3` = "special" — the ROM initializes a constant timer for these but the per-frame
 *  consumer semantics are unread (chunk_0009.c:2909-2973 only handles cases 1 and <=0), so the
 *  port treats 2/3 the same as all-at-once until decoded further. */
export type WeaponRefillType = number;

/**
 * One ROM weapon-cell (struct+0x774 + weaponIdx*8, aux struct+0x78c + weaponIdx*8; ATK-009,
 * findings.md mechanic P; row source `research/decomp/data/borg-hp-stat-rows-802f2988.json`,
 * live-verified G RED/pl0615 -> ammo 5). Weapon 0 mirrors `BorgRuntime.ammo`.
 */
export interface WeaponCell {
  /** Current ammo (struct+0x774/+0x77c/+0x784). */
  cur: number;
  /** Ammo max (struct aux +0x78e/…). `0` = infinite: firing is never blocked and cur is not
   *  decremented (chunk_0002.c:7158-7165). */
  max: number;
  /** Refill type (struct aux +0x790/…). See WeaponRefillType. */
  refillType: WeaponRefillType;
  /** Refill param (struct aux +0x792/…) — refill-timer seed, ROM units (frames-ish; the exact
   *  float conversion is TUNED, see constants.ts AMMO.REFILL_RATE_PER_FRAME / open-questions Q7). */
  refillParam: number;
  /** Refill timer (struct+0x778/…, f32). Counts down; on expiry (all-at-once) or while running
   *  (gradual, fractional grant) drives the refill per stepAmmoRefill. */
  timer: number;
}

export type SourceTargetLockMode = "enemy" | "ally";
export type SourceCameraState = 2 | 3 | 4;

/** Source-shaped target state: actor +0x502/+0x503/+0x504/+0x508 plus index bytes
 * +0x73d/+0x73e, represented by runtime uids instead of raw target-entry pointers. */
export interface SourceTargetLockState {
  /** Active lock family. R selects enemies, Z selects allies. */
  mode: SourceTargetLockMode;
  /** actor+0x502 style state: 0=no target, 1=valid target, 2=invalidating target. */
  sourceState: 0 | 1 | 2;
  /** camera+0x2e6 state: 2=no-lock, 3=lock follow, 4=lock/unlock transition. */
  cameraState: SourceCameraState;
  /** Source target-list index byte for enemy cycling (+0x73d). */
  enemyIndex: number;
  /** Source target-list index byte for ally cycling (+0x73e). */
  allyIndex: number;
  /** Runtime equivalent of actor+0x508 for the currently active lock family. */
  activeTargetUid: string | null;
}

/** Narrow behavior exposed by the ROM-family sidecar to combat orchestration. */
export interface RomFamilyDriver {
  tick(runtime: BorgRuntime, dt: number, all: readonly BorgRuntime[], input?: PlayerInput | null): boolean;
  tryStartXSpecial(runtime: BorgRuntime, all: readonly BorgRuntime[]): boolean;
  tryStartBAttack(runtime: BorgRuntime, all: readonly BorgRuntime[]): boolean;
  drainProjectiles(): Projectile[];
}

export interface BorgRuntime {
  uid: string;
  borgId: string;
  /** Current descriptor/model form after an in-place ROM morph. `borgId` remains the
   *  original combatant identity for force progression/results ownership. */
  combatFormId?: string;
  /** Exact target-host bytes surfaced for zz_006bf80_. */
  targetEligibility83?: number;
  targetVisibilityMask5e6?: number;
  /** Battle-local posts corresponding to zz_01cb750_(0x803bfe20,&form,+0x3ec). */
  romMorphEvents?: Array<{ eventAddress: number; borgNumber: number; slot: number }>;
  /** Latest zz_00b22f4_ variant-1 presentation edge and its exact sampled transform. */
  romAfterimage?: { serial: number; pos: Vec3; rotY: number };
  /**
   * Palette/color-variant id (victim struct +0x3ed in the GET kill-registration path —
   * research/decomp/items-evidence-inventory-2026-07-05.md §2a): 0=normal, 1=alt color,
   * 2=gold, 3=silver, 4=crystal, 5=black. The port has no color-variant selection pipeline
   * yet (borg spawns are always the default palette), so this is always 0 today — TUNED
   * placeholder wired for the GET drop system (@gf/missions getSystem.ts) to read per-kill.
   * Optional so existing fakes/constructors self-heal to undefined (treated as 0/normal).
   */
  colorVariant?: number;
  team: number;
  /** Owning player id, or null for CPU-controlled. */
  ownerPlayer: string | null;
  hp: number;
  maxHp: number;
  /** World position (struct+0x44 vec3, flat ground plane). */
  pos: Vec3;
  /** Facing yaw in radians (struct+0x72 heading; +Z forward). */
  rotY: number;
  /** Velocity (struct+0x58-ish vec3). */
  vel: Vec3;
  grounded: boolean;
  /** Remaining mid-air jumps. */
  airJumps: number;
  state: BorgState;
  /** Frames spent in the current state. */
  stateTime: number;
  /** Current animation label (cosmetic; render reads it). */
  anim: string;
  /**
   * 3-phase deploy progress (ROM +0x558 state-table slots 0-2, behavior-notes.md (af); constants
   * DEPLOY): 0 = descent (20f), 1 = setup (1f — the frame FUN_8005bec8 fires ALLY reaction cue
   * id 8), 2 = pose (15f). Optional + defaults absent so external fakes self-heal; advanced in
   * combat.ts stepActionState while state === "spawn". Renderer-readable: a teammate's
   * deployPhase 0 -> 1 transition is the ally-cue-8 trigger the ROM fires (cue 8 is an index
   * into the per-borg reaction-ANIMATION-select table, NOT a soundId — see DEPLOY/ALLY_CUE_ID).
   * DERIVED.
   */
  deployPhase?: 0 | 1 | 2;
  /** Ranged ammo remaining before reload. Kept as the WEAPON-0 alias for compat: every
   *  existing reader/writer of `b.ammo` keeps working unchanged, mirroring
   *  `weaponCells[0].cur` (ATK-009, findings.md mechanic P). */
  ammo: number;
  /**
   * Per-weapon ammo cells (struct+0x774/+0x77c/+0x784, stride 8; ROM models 3). Optional and
   * lazily initialized (same convention as `meleeHitUids` below) so existing constructors/
   * fakes that only set `ammo` keep compiling — combat.ts's ammo helpers self-heal it from
   * the borg's action profile on first use. Weapon 0 mirrors `ammo` and drives B shot ammo;
   * weapon 1 drives X/special ammo where the extracted stat row supplies a max/refill cell.
   * Weapon 2 remains inert because the recovered per-borg stat row only carries two weapon
   * segments.
   */
  weaponCells?: WeaponCell[];
  /** Named cooldown timers (frames remaining). */
  cooldowns: Record<string, number>;
  /** Invincibility timer (struct+0x720, frames; counts down 1/frame). */
  invincTimer: number;
  /** Balance gauge (struct+0x6c2, u16); a hit that depletes it forces a stagger
   *  (0x6fd |= 0xa6). Init = balanceGaugeMax from the borg's pl####data.bin u16[0]
   *  (chunk_0007.c:47-52); refills to max when balanceRefillDelay expires. */
  balanceGauge: number;
  /** Balance gauge max (struct+0x6be) — per-borg VERIFIED data (data/gaugeInit.json). */
  balanceGaugeMax: number;
  /** Down gauge (struct+0x6c6, u16); a hit that drops it below 1 staggers. Init/reset =
   *  downGaugeBase (pl####data.bin u16[1]); resets to base when downResetDelay expires
   *  (zz_003d3e8_, chunk_0004.c:6866-6876) and on stagger entry. */
  downGauge: number;
  /** Down gauge base (struct+0x6c4) — per-borg VERIFIED data (data/gaugeInit.json). */
  downGaugeBase: number;
  /** Post-hit window (struct+0x684, frames): balance refills to max on expiry. Set to 60 on
   *  every hit taken; frozen while in a hit reaction (see constants.ts STAGGER). */
  balanceRefillDelay: number;
  /** Post-hit window (struct+0x688, frames): down gauge resets to base on expiry. */
  downResetDelay: number;
  /** Post-hit combo window (struct+0x68c, frames): comboAccum/comboRank reset on expiry. */
  comboWindow: number;
  /** Combo accumulator (struct+0x6c8, clamped 0-99). */
  comboAccum: number;
  /** Combo rank byte (struct+0x6ca). Reset with comboAccum; rank derivation untraced. */
  comboRank: number;
  /** Proven actor param-tier state at `+0x74a/+0x74e/+0x750`; effect table mapping still unported. */
  paramTier: ActorParamTier;
  /** Status-effect id (struct+0x71a, masked to 0x3f), 0 = none. ATK-010 shell only — no
   *  status has a gameplay effect yet; see status.ts. (research/decomp/attack-mechanics-
   *  findings.md mechanic Q, chunk_0003.c:7641-7642). OBSERVED_GUIDE (player-documented
   *  status catalog, not yet id-mapped): freeze/mash-to-recover, poison DoT, time stop,
   *  shrink/grow, aim-scramble, transform, tether, position-swap — see research/decomp/
   *  data/guide-anchors-movelist.json statusObservations. */
  statusId: number;
  /** Status duration in frames (struct+0x71c), decrements 1/frame (chunk_0007.c:2881-2883);
   *  clears statusId at 0. Application max-merges with any running timer (never shortens). */
  statusTimer: number;
  /** Per-status immunity bitmask (struct+0x5a0); bit N set blocks status N application AND
   *  (per formula step 1, chunk_0004.c:6693-6699) zeroes HP damage for that hit. Init 0
   *  (chunk_0006.c:7107-7110) — no borg grants immunity yet in this port. */
  statusImmunityMask: number;
  /** Current lock-on target uid, or null. */
  lockTarget: string | null;
  /** Current ally lock-on target uid, or null. Z control is asset-confirmed; downstream behavior is unknown. */
  allyLockTarget: string | null;
  /** Source-shaped retained lock state. Optional so external fakes self-heal on first lock step. */
  targetLockState?: SourceTargetLockState;
  /** Uids already struck by the CURRENT melee swing (enforces one hit per swing per target).
   *  Transient bookkeeping, reset on every swing start; optional so external constructors
   *  (tests/fakes) don't need to provide it. */
  meleeHitUids?: string[];
  /** The CURRENT melee swing's (or charged release's) action-script playAnim target (mot.bin
   *  bank group/slot — a DIFFERENT numbering axis than the action-script stream slot; see
   *  actionStreamData.ts's header and the pl0615 charge_shot precedent in
   *  borgPresentationAssets.ts), when the combo-ladder step / air-B leaf resolved one
   *  (actionStreamData.ts ComboStep/ExactMoveLeaf.animStreamRef). Set by startMeleeAttack on
   *  every swing start (including the TUNED-fallback opener, which clears it to null) AND by
   *  startShotAttack on a charged release (chargeMoveForBorgId's leaf, or null on an
   *  unresolved borg / a plain tap); renderers may use it to pick a per-swing/per-release clip
   *  instead of the generic "melee"/"melee_alt"/"charge_shot" slot. Optional so external fakes
   *  self-heal to undefined. */
  meleeAnimStream?: { group: number; slot: number } | null;
  /** The CURRENT melee swing's (or charged release's) PATH-B authored sound events (DERIVED —
   *  the per-anim sound-event table at ROM actor+0x4e8 joined through the anim-descriptor
   *  banks; actionStreamData.ts AuthoredSoundEvent, research/decomp/
   *  anim-sound-op-decode-2026-07-04.md). `frame` = ROM anim-clock frame (0 = anim start),
   *  `id` = literal soundId (se_<hex> manifest key axis). Set alongside meleeAnimStream by
   *  startMeleeAttack / startShotAttack; null when the swing has no resolved stream or its
   *  anim carries no sound events. Renderers may schedule these instead of the TUNED
   *  slot-keyed COMBAT_SFX fallback. Optional so external fakes self-heal to undefined. */
  meleeSounds?: readonly { frame: number; id: number; mode: number; part: number }[] | null;
  /** impactEffectId (damage record u8 +0x09) of the most recent hit applied to this borg, plus
   *  the attacker's team. DERIVED chain: resolve_hitbox_target_effects_and_damage
   *  (@0x8002e2a8, chunk_0003.c:8087-8156) gates the contact-effect spawn on the attacker
   *  record's +0x09 byte != 0xff, then zz_0019550_ (chunk_0002.c:1501) indexes the 4-byte
   *  effect-definition table at 0x802c7ed0 with it (see battleScene.ts for the decoded
   *  id -> variant/lifetime/scale-curve mapping). Written by applyHit on every connection;
   *  renderer-facing only (no sim code reads it). Optional so external fakes self-heal. */
  lastHitImpactEffectId?: number;
  /** Team of the attacker for the most recent hit (the ROM's variant-1 hit burst selects its
   *  particle texture by the ATTACKER's player index — FUN_80019a14 chunk_0002.c:1750-1758
   *  reads spawner+0x88, copied from the attacker actor in zz_001959c_). Renderer-facing. */
  lastHitAttackerTeam?: number | undefined;
  /** Owning player id of the most recent hit's attacker (null = CPU attacker). Kill
   *  attribution for the results counters mirrors the ROM's kill event (zz_002f8dc_
   *  @0x8002f8dc): the LAST damager gets the kill/costWon credit. */
  lastHitAttackerOwner?: string | null | undefined;
  /** Power Burst arm window (ROM +0x6fb), frames remaining. Y press edge sets this to
   *  BURST.ARM_WINDOW_FRAMES (6, DERIVED — `FUN_80069814` chunk_0009.c:113); decrements to 0
   *  per frame (mirrors `zz_005b2b8_` chunk_0007.c:3473-3490); a re-press re-arms it. NOTE
   *  (behavior-notes.md (aj)): the ROM also decrements +0x6fb in the fusion per-slot loop and
   *  its expiry there drives the burst/fusion END path — the audit's "6-frame arm window" and
   *  the fusion timer may be the SAME field read in two different contexts, not two fields;
   *  this still needs trace T3 to reconcile before fusion/duration semantics are final.
   *  UPDATE (behavior-notes.md (ao), official NA instruction manual, CONFIRMED_MANUAL tier):
   *  "press the button at the same time [as your partner] for simultaneous power bursts" — this
   *  gives the 6-frame window a coherent reading as a SIMULTANEITY tolerance for synchronized
   *  co-op bursts/fusion (partner's Y within the window counts as "same time"), not merely an
   *  arm/activation buffer. Manual text is still not numeric ROM truth, so the exact semantics
   *  (whose window, how it gates pairing) remain for trace T3 to reconcile. */
  burstArmFrames: number;
  /** Power Burst activation flag (ROM +0x6fc = 1, set by `zz_005b2b8_` when +0x6fb is nonzero
   *  and the borg is active). Per (ao) (official manual, CONFIRMED_MANUAL): real activation's
   *  precondition is "the burst gauge is at max". UPDATE (Q4/Q5 RESOLVED at value level): the
   *  per-player meter lives in BattleState.burstMeterByPlayer, activation consumes the charged
   *  flag, active burst drains the meter by BURST.DRAIN_PER_FRAME each frame, and movement reads
   *  this flag for BURST.SPEED_MULTIPLIER. Remaining gaps: per-action extra meter costs and the
   *  exact ROM code path carrying the speed multiplier. */
  burstActive: boolean;
  /** Power Burst "paired" flag (ROM +0x6fa = 1, set alongside +0x6fc by `zz_005b2b8_`).
   *  Records same-team simultaneous activation; not wired to fusion pairing
   *  (fusionPartnerUid/fusionState below) until a later ticket confirms the relationship.
   *  See (ao) note on burstArmFrames re: simultaneous co-op bursts — "paired" may end up
   *  meaning that, but it is UNCONFIRMED pending T3. */
  burstPaired: boolean;
  /** Power Burst fusion partner uid, or null when not fused/linked (ROM +0x4a4 partner
   *  pointer, modeled as a uid). Nothing sets this yet (ATK-018 shell only). */
  fusionPartnerUid: string | null;
  /** Power Burst fusion state (ROM +0x4a1 vocabulary): 0 = none, 1->2->3->5->6 locked,
   *  7 = ending. Nothing sets this yet (ATK-018 shell only; see behavior-notes.md (aj)). */
  fusionState: number;
  /** True once the HP-zero kill event has already removed this borg's force cost. */
  defeatAccounted: boolean;
  alive: boolean;
  /** Live-resolved ROM attack command for this frame (commandDispatch.ts): the transformed
   *  input word, tester command type (actor+0x585 model), the +0x4ec table row it selected,
   *  and the exact ROM command record where one is decoded. Set by stepAttacks each frame it
   *  runs (null-cleared when no attack bit is held); optional so external fakes self-heal. */
  command?: ResolvedCommandState | null;

  // --- Hit-inflicted status effects (research/decomp/status-effects-decode-2026-07-04.md) ---
  // resolve_hitbox_target_effects_and_damage @0x8002e2a8 writers; consumed by timescale.ts's
  // statusTimescale() rebuild (FUN_8005a378, chunk_0007.c:2817-2898). All optional so existing
  // fakeRuntime()/constructors that predate this ticket keep compiling (self-heal to 0/absent).

  /** ROM-family driver sidecar. When present, the 1:1 ported state machine
   *  owns this borg's motion for actions its family implements (currently the G RED
   *  family X-special). Null/absent for borgs whose family hasn't been ported yet —
   *  they keep the generic archetype combat logic unchanged. See packages/combat/src/rom/. */
  romDriver?: RomFamilyDriver | null;

  /** Slow-on-hit level (ROM +0x70e; discrete, flagsB&0x0004): 0 = none, else indexes the
   *  DERIVED slow table {0,0.7,0.4,0.2} in timescale.ts. Skipped for burst victims. */
  slowHitLevel?: number;
  /** Slow-on-hit s16 timer (ROM +0x710), 900f seed; decrements 1/frame, clears the level at 0. */
  slowHitTimer?: number;
  /** Haste-on-hit level (ROM +0x70f; discrete, flagsB&0x0008): 0 = none, else indexes the
   *  DERIVED haste table {0.1,1.25,1.5,1.75}. Applies even to burst victims. */
  hasteHitLevel?: number;
  /** Haste-on-hit s16 timer (ROM +0x712), 900f seed; decrements 1/frame, clears the level at 0. */
  hasteHitTimer?: number;
  /** Contact-slow AURA level (ROM +0x70c, flagsB&0x0400): max-merged per contact frame from
   *  the record's comboScoreValue; NO timer — cleared to 0 at the START of every frame and
   *  re-applied only while a slow-aura hitbox still overlaps. Divers (pl0805/pl080d/pl080e)
   *  are hard-coded exempt from receiving it. */
  slowAuraLevel?: number;
  /** Contact-haste AURA level (ROM +0x70d, flagsB&0x0800): fixed at 1 (×1.25) while overlapping;
   *  cleared every frame like slowAuraLevel. */
  hasteAuraLevel?: number;
  /** Freeze/hitstop frames (ROM +0x71c, u8): max-merged from a normal-reaction hit's
   *  `hitStrength` on BOTH attacker and victim; decrements 1/frame; overrides statusTimescale
   *  to ×0.03 (freeze table) while > 0. */
  freezeFrames?: number;
  /** Hit-inflicted grow/shrink accumulator (ROM DAT_8043612c slot, flagsA&0x0004/0x0008):
   *  ±rec.comboScoreValue per contact frame, clamped to ±63 (the `_63` tier-delta path,
   *  paramTier.ts applyActorParamTierDelta63 semantics) — kept as its OWN delta (not folded
   *  into paramTier.deltaAccum) so combat.ts can revert exactly this contribution independent
   *  of any other tier-delta source (e.g. the hero X buff below, item 4). */
  sizeTierDelta?: number;
  /** 900f auto-revert timer for sizeTierDelta (ROM +0x750 via the `_63` caller,
   *  chunk_0003.c:6248/chunk_0008.c:4475); reverts sizeTierDelta to 0 at expiry. */
  sizeTierTimer?: number;
  /** STAR HERO (pl0804) / PLANET HERO (pl080c) X-special self-buff (ROM actor+0x144,
   *  zz_011230c_/FUN_8010f790, chunk_0031.c:576-617 / chunk_0030.c:4004-4026): +4 param
   *  tiers (velocity ×2.366 via timescale.ts's tier table) applied directly via
   *  applyActorParamTierDelta127 (NOT the ±63 accumulator — this is its own flat +4/-4 with
   *  its own 1200f timer) on a connecting ramming-dash hit, reverted when the timer expires. */
  heroTierBuffFrames?: number;

  // --- T6 reaction knockback integration (combat-feel-gaps-decode-2026-07-05.md) ---------
  /** Which reaction family's knockback integration is active, or undefined when not in a
   *  knockback-driven reaction. "ground" = zz_005ec20_ (horizontal-only, -speed/20 decel over
   *  reactionDecelFramesRemaining); "launch" = FUN_8005ed38 (pitch-split arc, fixed -0.1
   *  horizontal decel + -1.2 gravity for the reaction's whole duration). Set by applyHit,
   *  cleared by movement.ts once the ground decel finishes or the state leaves hit/down. */
  reactionKind?: "ground" | "launch" | undefined;
  /** Ground-family decel countdown (frames): the ROM's h-accel = -speed/20 means the knockback
   *  stops in exactly REACTION.GROUND_DECEL_FRAMES frames from its initial speed, so this
   *  counts down from that constant each frame movement.ts integrates it, reaching 0 when the
   *  horizontal component is fully zeroed. undefined/absent for a launch reaction (which uses a
   *  fixed per-frame decel instead of a frames-to-stop denominator) or when not reacting. */
  reactionDecelFramesRemaining?: number | undefined;
}

/** Live-resolved ROM attack command (see commandDispatch.ts for the resolution pipeline). */
export interface ResolvedCommandState {
  /** Transformed-input-word (actor+0x5d4 model) built from this frame's buttons. */
  word: number;
  /** ROM tester command type written to actor+0x585 (command.ts AttackCommandType value). */
  type: number;
  /** +0x4ec command-table button row the type+context resolved to, or null for unmapped types. */
  button: string | null;
  /** Selected exact ROM command record address (data/commandMoveTables.json), or null. */
  recordAddress: string | null;
  /** Selected record's subtype (+0x586 model), or null. */
  subtype: number | null;
  /** Exact action-table index encoded by the selected four-byte command record. */
  actionIndex: number | null;
  /** Exact per-action variant encoded by the selected four-byte command record. */
  variantIndex: number | null;
  /** True when an exact decoded ROM record backs this command. */
  exact: boolean;
}

/** A force = an ordered list of borgs a team/player deploys one at a time. */
export interface ForceConfig {
  team: number;
  ownerPlayer: string | null;
  borgIds: string[];
  /** Optional raw level byte per `borgIds` slot (0 = display level 1, 9 = display level 10). */
  borgLevels?: readonly (number | null | undefined)[];
}

export interface SpawnPoint {
  pos: Vec3;
  /** Optional facing yaw in radians; omitted means face arena center. */
  rotY?: number;
}

export interface BattleConfig {
  stageId: string;
  forces: ForceConfig[];
  bounds?: StageBounds;
  collision?: StageCollision;
  /** Optional exact per-force spawn points from original stage/slot tables. */
  spawnPoints?: SpawnPoint[];
  /** Original battle timer in frames; omitted means no timer. */
  timeLimitFrames?: number;
  /**
   * DERIVED — model of the original timer-pause flag PTR_DAT_80433934[0x50].
   * The countdown (zz_0029b58_ @0x80029b58, chunk_0003.c:4631-4638) and BOTH
   * timeout branches of the battle-end judge (zz_00297c8_ @0x800297c8,
   * chunk_0003.c:4519-4529 and :4547-4553) run only while [0x50] == 0.
   * Challenge setup writes timeLimit=18000 AND [0x50]=1 (chunk_0048.c:390-392),
   * so original Challenge battles display a timer value but can never time out.
   * Versus with a selected limit writes seconds*60 and [0x50]=0 (chunk_0044.c:366-373).
   */
  timerFrozen?: boolean;
  /** Original Challenge mode for damage side-rank bytes: 0=NORMAL, 1=TUFF, 2=INSANE. */
  challengeMode?: 0 | 1 | 2;
  /** ROM-architecture CPU AI (romAi.ts) — DEFAULT true as of 2026-07-06 (the waypoint
   *  policy is DERIVED: rom-waypoint.ts + rom-movement.ts). Set false to opt back into
   *  the legacy heuristic stepAI. */
  useRomAi?: boolean;
}

export type BattleResult = "ongoing" | "win" | "lose" | "draw";

export type ProjectileVisualKind = "energy" | "flame" | "muzzle";

/**
 * Why a projectile left the field. Set by stepProjectiles on the projectile OBJECT in the same
 * frame it is dropped from the survivors list, so a renderer that keeps per-uid references to
 * Projectile objects can read the reason after removal and spawn impact effects only for real
 * impacts (hit-target / hit-terrain), not for expiry or bounds culls.
 *   - "hit-target":   consumed by a valid borg hit (default consumeOnHit path).
 *   - "hit-terrain":  the frame's movement segment crossed stage collision geometry — the
 *                     ROM's terrain/wall impact tests zz_0083244_/zz_0083714_ called from the
 *                     projectile fly function zz_006f268_ (chunk_0009.c:3956). pos is moved to
 *                     the impact point.
 *   - "out-of-bounds": left the stage rect or crossed into unsupported-floor space (port-side
 *                     play-area cull; the original relies on geometry + lifetime instead).
 *   - "expired":      life counter reached 0 (init FUN_8006f11c seeds 600 frames,
 *                     chunk_0009.c:3907).
 *   - "owner-dead":   owner-liveness despawn — zz_00840b8_ (chunk_0012.c:3216), called every
 *                     frame from the projectile update FUN_8006f0cc.
 */
export type ProjectileDespawnReason =
  | "hit-target"
  | "hit-terrain"
  | "out-of-bounds"
  | "expired"
  | "owner-dead";

/** A homing/straight projectile in flight. */
export interface Projectile {
  uid: string;
  ownerUid: string;
  team: number;
  pos: Vec3;
  vel: Vec3;
  /** Source damage scale for real combat callers; legacy direct callers may still treat it as raw damage. */
  damage: number;
  hitstun: number;
  /** Per-move knockback MULTIPLIER (applyHit derives the base magnitude from the hit's
   *  damage record strength byte — see gauges.ts knockbackVelocityForRecord). */
  knockback: number;
  /** EXACT per-borg family damage record (familyDamageData.ts), bound at spawn from the
   *  shooter's kind-0 hitbox record. When absent, stepProjectiles falls back to the
   *  archetype `damageRecordIndex` below. */
  damageRecord?: import("./gauges.js").DamageRecord;
  homingTurn: number;
  homingTarget: string | null;
  /** The shooter's active lock target at spawn — the ROM attack object's target pointer
   *  (+0xcc), which drives the results DODGE counters (aimed-at-victim vs stray hits;
   *  zz_008a5d0_ chunk_0013.c:1115, resolver chunk_0003.c:7887-7894). Independent of
   *  `homingTarget` (a straight shot is still "aimed" at the lock target). */
  aimedTargetUid?: string | null;
  life: number;
  hitRadius: number;
  visualKind: ProjectileVisualKind;
  /** Ballistic drop subtracted from vel.y each frame (bullet kinds only). Optional; 0/absent = none. */
  drop?: number;
  /** Damage-record index into gauges.ts DAMAGE_RECORDS for the gauge/stagger model
   *  (DERIVED mapping — see gauges.ts DAMAGE_RECORD_INDEX). Absent = normal shot (record 0). */
  damageRecordIndex?: number;
  /** Consumption policy on a valid borg hit (ATK-008). `!== false` (including absent) is the
   *  default: first valid hit consumes the projectile — today's behavior, unchanged bit-for-bit.
   *  `false` means the projectile persists through hits and re-hits are paced by
   *  `rehitCounter`/`record.rehitIntervalFrames` instead of being destroyed. The ROM's
   *  structural default is persistence (object death is actor-gated, not collision-coded:
   *  chunk_0013.c:1188); despawn-on-hit is what the port's stepProjectiles has always modeled,
   *  so it stays the default here. No gameplay caller sets this to `false` yet — that flip is
   *  T6's outcome (research/decomp/attack-mechanics-findings.md mechanic O). */
  consumeOnHit?: boolean;
  /** ROM projectile variant visual scale [X, Y, Z] from DAT_802f3dda +0x1a/+0x1e/+0x22.
   *  The renderer reads this to size the projectile sprite/mesh. Absent = default scale
   *  (1.0 × 1.0 × 1.0). Source: projectiles.ts ProjectileVariant.scale. */
  romScale?: [number, number, number];
  /** Frames remaining before this projectile may apply its next hit while persisting
   *  (`consumeOnHit === false`). Mirrors the ROM's SINGLE per-object counter at object+0x4e,
   *  reloaded from the damage record's s8+0x16 `rehitIntervalFrames` on every hit application
   *  (chunk_0013.c:1175-1182) — NOT a per-target map. Interval 0 reloads to 0, so the object
   *  stays hit-ready and can re-hit (a new target, or the same one) every frame it overlaps
   *  (chunk_0013.c:1188 gates despawn, not this counter). Absent/undefined = not yet initialized;
   *  treated as hit-ready (0) the first time stepProjectiles sees a persisting projectile. */
  rehitCounter?: number;
  /** Why this projectile despawned (see ProjectileDespawnReason). Written by stepProjectiles
   *  the frame the projectile is dropped from the survivors list; absent while in flight.
   *  Additive/back-compat: no sim code reads it — it exists for the renderer. */
  despawnReason?: ProjectileDespawnReason;
  /** True when this projectile applied at least one damage hit during the most recent
   *  stepProjectiles frame (covers BOTH the consuming hit-target despawn and persisting
   *  ATK-008 re-hits, which never despawn). Reset to false at the start of each projectile
   *  step. Additive/back-compat: renderer-facing only (impact-puff trigger). */
  hitConfirmedThisFrame?: boolean;
  /** impactEffectId (u8 +0x09) of the damage record this projectile applied on its most recent
   *  confirmed borg hit (the same record stepProjectiles passed to applyHit). DERIVED field +
   *  consumption chain: chunk_0003.c:8087-8156 spawns the contact effect from this byte via
   *  zz_0019550_ / effect-def table 0x802c7ed0 (0xff = no effect). Written alongside
   *  `hitConfirmedThisFrame`; absent until the first confirmed hit. Renderer-facing only. */
  lastImpactEffectId?: number;
  /**
   * Resolved efct00-bank FLIGHT visual for this shot (research/decomp/
   * efct-consumers-decode-2026-07-04.md §3, FUN_8007dd84's shot-init row +0x00): set only
   * when the borg's guarded shot-variant row proves the shot uses the efct00 particle bank
   * (texId|flags bit 0x4000 or 0x8000) rather than the per-player weapon bank (neither bit —
   * honest unknown, no port visual change). `attackHitData.ts` shotFlightVisualForBorgId
   * resolves this from the SAME borgShotKinds/firedBy guarded attribution as the HIT-kind
   * resolver; absent/undefined means "keep today's visualKind sprite" (unattributed or
   * weapon-bank rows). Renderer-facing only (battleScene.ts syncProjectiles), no sim-side
   * gameplay effect. */
  flightVisual?: {
    /** efct00_mdl.arc bank texId (0..156, apps/game/src/sim/data/efctBankMeshes.json). */
    bankTexId: number;
    /** True when the row's 0x4000 bit is set: the ROM attaches the entry's matAnim at the
     *  shooter's TEAM frame (1.0 team 0 / 3.0 team 1 — FLOAT_804379d0/d4). False (0x8000
     *  alone) draws the bank mesh's plain material, no matAnim. */
    teamTint: boolean;
    /** s8 +0x34 launch-FX id into the muzzle/launch fence table (zz_00aedc0_,
     *  0x802fafd0/0x802faef8) or null when the row's byte is -1 (no launch flash). */
    launchFxId: number | null;
  };
}

/**
 * Per-PLAYER Power Burst circle-gauge meter state (Q4 RESOLVED 2026-07-03 —
 * research/decomp/attack-mechanics-open-questions.md Q4 lines 51-79, attack-mechanics-
 * findings.md §S, save-state diff scripts/diff-actor-block.mjs + T3 live traces). ROM fields,
 * all in the PLAYER struct at `PTR_DAT_80433934 + i*0x3c` (NOT the borg/actor struct — the
 * meter persists across borg deploys/switches of the same player):
 *   - `meter`     = +0x126 (u16), the displayed value, clamped at +0x124 max (BURST.METER_MAX
 *                   = 3000);
 *   - `unclamped` = +0x12a, keeps accumulating past max (live: 2929 -> 3079 -> 3129; read by
 *                   the results screen min/max scan, chunk_0022.c:1671/1737);
 *   - `charged`   = +0x103, the FUN_80069814 arm precondition; flips to 1 ONE frame AFTER
 *                   +0x126 reaches max (live-observed delay — ported as the check-before-fill
 *                   sweep in battle.ts step()).
 * Distinct from the per-BORG burstArmFrames/burstActive/burstPaired state on BorgRuntime.
 */
export interface BurstMeterState {
  /** Clamped meter (ROM +0x126 u16), 0..BURST.METER_MAX. */
  meter: number;
  /** Unclamped accumulator (ROM +0x12a) — keeps counting past METER_MAX. */
  unclamped: number;
  /** Charged flag (ROM +0x103) — set one frame after `meter` reaches METER_MAX. */
  charged: boolean;
}

export interface BattleState {
  borgs: BorgRuntime[];
  projectiles: Projectile[];
  /** Remaining energy per team = sum of not-yet-defeated on-field + not-yet-deployed borg energy.
   *  This IS the ROM's side force-gauge current value (`side[+0x118]`, combat-feel-gaps-decode-
   *  2026-07-05.md T4) — it already depletes on death exactly like the ROM's `zz_002f8dc_`. */
  energy: Record<number, number>;
  /**
   * Side force-gauge MAX (ROM `side[+0x114]`, T4): the team's total energy at battle start,
   * rounded DOWN to a multiple of 10 (chunk_0000.c:1076-1079) — snapshotted once at battle
   * creation (before any deaths can reduce `energy`). Used as the force-gauge ratio's
   * denominator (damageFormula.ts attackerForceRatioIndex/defenderForceRatioIndex recipe:
   * `idx = 32 - floor(energy[team] * 32 / energyMax[team])`). Optional so pre-existing state
   * constructors/fakes stay valid; absent/0 means "no force-gauge ratio available" (callers
   * should treat it the same as full gauge, i.e. curve index 0).
   */
  energyMax?: Record<number, number>;
  /** Whole borgs defeated per team, counted at the source death event before auto-deploy. */
  defeated: Record<number, number>;
  /** Energy/cost defeated per team, counted from each defeated borg's profile energy. */
  defeatedEnergy: Record<number, number>;
  /** The currently-active (controllable) borg uid per player id. */
  activeUidByPlayer: Record<string, string>;
  /**
   * Per-player Power Burst meter, keyed by player id (ForceConfig.ownerPlayer). PER-PLAYER
   * like the ROM (player struct +i*0x3c — see BurstMeterState above): it persists across
   * borg deaths/deploys/switches and is never reset by deployNext. CPU-owned forces
   * (ownerPlayer === null) get no entry in this wave — see creditBurstFill in burst.ts for
   * the documented decision. Drained by active Power Burst once a human player activates.
   */
  burstMeterByPlayer: Record<string, BurstMeterState>;
  /**
   * Battle telemetry feeding the Results screen. Two layers:
   *
   *  - Team aggregates (damage/hits/attempts) — kept for debug/HUD use; damage is credited
   *    on hit connection (applyHit, same point that credits burst fill).
   *  - `slots` — DERIVED per-player-slot counters mirroring the ROM's per-actor stat block
   *    (actor struct +0x404..+0x437, results-scoring-decode-2026-07-04.md). The ROM keeps
   *    these on the persistent player-slot actor (they survive borg swaps within the
   *    battle), so the port keys them by player id (ForceConfig.ownerPlayer). CPU-owned
   *    forces get no slot (their stats are never displayed).
   *
   * Optional so pre-existing state constructors stay valid.
   */
  telemetry?: {
    damageByTeam: Record<number, number>;
    hitsByTeam: Record<number, number>;
    attemptsByTeam: Record<number, number>;
    slots?: Record<string, SlotTelemetry>;
    /**
     * First-strike claim (ROM DAT_80436128 gate + attacker+0x436, chunk_0003.c:7882-7885):
     * the FIRST cross-team hit connection of the battle stamps its attacker here.
     * `undefined` = not yet claimed; `null` = claimed by a CPU-owned attacker; a string =
     * claimed by that player id. Worth 5000 (DAT_80433b58) on the results screen.
     */
    firstStrikeBy?: string | null;
  };
  /** Team-0 defeat split for the Results screen: player-owned vs CPU-ally borgs. */
  defeatedPlayerBorgs?: number;
  defeatedAllyBorgs?: number;
  /**
   * Ordered list of every kill accounted this battle (one entry per accountPendingDefeats
   * kill, in kill order) — additive, optional so existing state constructors keep
   * compiling. Feeds the Borg GET drop pool (@gf/missions getSystem.ts registerKill):
   * research/decomp/items-evidence-inventory-2026-07-05.md §2a needs the VICTIM's borgId +
   * colorVariant, which BorgRuntime now carries. `killerTeam`/`killerOwner` mirror the same
   * cross-team-kill attribution accountPendingDefeats already uses for the slot counters
   * (lastHitAttackerTeam/lastHitAttackerOwner); a defeat with no cross-team damager (e.g. a
   * husk's own bookkeeping death) still appends an entry with killerTeam/killerOwner
   * undefined so callers can filter it out explicitly rather than have it silently missing.
   */
  defeats?: BattleDefeat[];
  frame: number;
  /** Frames remaining on the battle timer, or null when untimed. */
  timeRemainingFrames: number | null;
  result: BattleResult;
  /**
   * ROM winner mask (behavior-notes (ae), PTR_DAT_80433934[0x1f], judge zz_00297c8_): bit0 =
   * side 0 won, bit1 = side 1 won, 3 = mutual simultaneous destruction, 4 = timeout no-winner,
   * 0 = ongoing. `result` is derived from it via the ROM's equality/advance test. Optional so
   * pre-existing state constructors stay valid; absent === 0 (ongoing).
   */
  winnerMask?: number;
}

/**
 * One accounted kill (BattleState.defeats entry) — additive telemetry for the GET drop
 * pipeline. See the `defeats` field doc above for provenance.
 */
export interface BattleDefeat {
  /** The victim's borg id (pl####). */
  borgId: string;
  /** The victim's palette/color-variant id (0..5; see BorgRuntime.colorVariant). */
  colorVariant: number;
  /** The victim's team. */
  victimTeam: number;
  /** The killer's team, when the last damager was cross-team (accountPendingDefeats'
   *  b.lastHitAttackerTeam !== b.team gate); undefined for a same-team/no-damager death. */
  killerTeam?: number;
  /** The killer's owning player id, or null for a CPU-owned killer; undefined when there
   *  was no qualifying cross-team damager (mirrors killerTeam's undefined case). */
  killerOwner?: string | null;
}

/**
 * DERIVED per-player-slot results counters — 1:1 with the ROM per-actor stat block
 * (research/decomp/results-scoring-decode-2026-07-04.md; increment sites: zz_008a5d0_
 * @0x8008a5d0 chunk_0013.c:1085-1122, hit resolver chunk_0003.c:7834-7898, kill event
 * zz_002f8dc_ @0x8002f8dc chunk_0003.c:8287-8312).
 */
export interface SlotTelemetry {
  /** ROM +0x404 — attacks initiated (one per attack-object activation; rehits excluded).
   *  This IS the results screen's "ATTACK" number, and the HIT RATIO denominator. */
  attempts: number;
  /** ROM +0x408 — cross-team hit connections, once per (attack event, victim). */
  hits: number;
  /** ROM +0x40c — enemy attacks AIMED at this slot's borg at activation (the attack
   *  object's target pointer +0xcc == us), whether or not they later connect. */
  incomingAimed: number;
  /** ROM +0x410 — hits taken from attacks that were aimed at us; clamped to incomingAimed
   *  at increment (chunk_0003.c:7888-7891). DODGE RATIO numerator = incomingAimed − this. */
  hitsTakenAimed: number;
  /** ROM +0x414 — hits taken that were NOT aimed at us (stray/AoE, untracked-record and
   *  same-team hits). DODGE RATIO denominator = incomingAimed + this. */
  hitsTakenOther: number;
  /** ROM +0x434 (byte) — enemy borgs this slot's borgs finished off. */
  kills: number;
  /** ROM +0x420 — summed cost of those victims ("TOTAL COST" under ENEMY BORGS DEFEATED). */
  costWon: number;
  /** ROM +0x424 — summed cost of this slot's OWN defeated borgs (ally losses excluded —
   *  those are +0x430/+0x437 and never enter the grand total). */
  costLost: number;
}

/** Recursively read-only view used at the Battle boundary. */
export type DeepReadonly<T> = T extends (...args: never[]) => unknown
  ? T
  : T extends readonly (infer U)[]
    ? readonly DeepReadonly<U>[]
    : T extends object
      ? { readonly [K in keyof T]: DeepReadonly<T[K]> }
      : T;

/**
 * Structured actor snapshot for one fixed-step boundary. Its identity is stable only within
 * the cached observation for that boundary; driver internals deliberately stay inside the sim.
 */
export type BattleActorObservation = DeepReadonly<Omit<BorgRuntime, "romDriver">>;
export type BattleProjectileObservation = DeepReadonly<Projectile>;

/** Final immutable facts for a projectile removed during this fixed step. */
export interface ProjectileDespawnObservation {
  readonly uid: string;
  readonly pos: DeepReadonly<Vec3>;
  readonly vel: DeepReadonly<Vec3>;
  readonly team: number;
  readonly reason: ProjectileDespawnReason;
  readonly impactEffectId?: number;
}

/**
 * Cohesive read model for one fixed-step boundary. Arrays and nested records are typed
 * read-only. Actors and current projectiles are structured snapshots whose identity lasts
 * only for this cached boundary observation. Removed-projectile lifecycle facts are supplied
 * separately by `projectileDespawns`.
 */
export interface BattleObservation {
  readonly actors: readonly BattleActorObservation[];
  readonly projectiles: readonly BattleProjectileObservation[];
  readonly projectileDespawns: readonly ProjectileDespawnObservation[];
  readonly activeUidByPlayer: Readonly<Record<string, string>>;
  readonly energy: Readonly<Record<number, number>>;
  readonly energyMax: Readonly<Record<number, number>>;
  readonly defeated: Readonly<Record<number, number>>;
  readonly defeatedEnergy: Readonly<Record<number, number>>;
  readonly burstMeterByPlayer: DeepReadonly<Record<string, BurstMeterState>>;
  readonly telemetry: DeepReadonly<NonNullable<BattleState["telemetry"]>>;
  readonly defeatedPlayerBorgs: number;
  readonly defeatedAllyBorgs: number;
  readonly defeats: readonly DeepReadonly<BattleDefeat>[];
  readonly frame: number;
  readonly timeRemainingFrames: number | null;
  readonly result: BattleResult;
  readonly winnerMask: number;
}

/** The driver object returned by createBattle. */
export interface Battle {
  /** Observe all public facts at the current fixed-step boundary. */
  observe(): BattleObservation;
  /** Look up the actor currently controlled by a player/force key. */
  activeActor(playerId: string): BattleActorObservation | undefined;
  /** Look up an observed actor by stable uid. */
  actor(uid: string): BattleActorObservation | undefined;
  /** Advance the sim by one fixed step. `dt` is accepted for API symmetry but the sim is
   *  fixed-step (SIM.DT); pass it through for documentation/compat. */
  step(dt: number, inputs: Record<string, PlayerInput>): BattleObservation;
}

/** Internal: a deploy queue entry (a borg not yet on the field). */
export interface DeployEntry {
  borgId: string;
  profile: BorgProfile;
}
