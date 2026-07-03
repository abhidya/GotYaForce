// Public types for the deterministic battle API. Mirrors the contract in the task brief.
// Control scheme (CONFIRMED from the game's controls screen + lock-relative movement trace):
//   A=jump, B=attack(melee/contextual), X=special, R=switch lock-on target,
//   Z=ally lock-on (target selection only; ally charge/power-up behavior not decoded yet),
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
  /** R — cycle lock-on target. */
  switchLock: boolean;
  /** Z — ally lock-on request. Target selection is modeled; ally charge behavior is still unknown. */
  allyLock: boolean;
  /** Reserved/prototype; Challenge battle core ignores manual switching until original proof exists. */
  switchBorg: boolean;
  /** Step/dodge (stick-action). */
  dash: boolean;
  /** Y — Hyper/Power Burst arm input. Evidence: `FUN_80069814` chunk_0009.c:104-115 (Y-family
   *  bit in transformed word +0x5d4 sets +0x6fb = 6, a 6-frame arm window). Shell only (ATK-011);
   *  no gameplay effects until ATK-012. */
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

export interface BorgRuntime {
  uid: string;
  borgId: string;
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
  /** Ranged ammo remaining before reload. Kept as the WEAPON-0 alias for compat: every
   *  existing reader/writer of `b.ammo` keeps working unchanged, mirroring
   *  `weaponCells[0].cur` (ATK-009, findings.md mechanic P). */
  ammo: number;
  /**
   * Per-weapon ammo cells (struct+0x774/+0x77c/+0x784, stride 8; ROM models 3). Optional and
   * lazily initialized (same convention as `meleeHitUids` below) so existing constructors/
   * fakes that only set `ammo` keep compiling — combat.ts's ammo helpers self-heal it from
   * the borg's action profile on first use. Weapon 0 mirrors `ammo` and drives the existing
   * shot path (B); cells 1/2 exist structurally but are unused until the per-weapon command
   * resolver lands (ATK-009 "Required behavior").
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
  /** Uids already struck by the CURRENT melee swing (enforces one hit per swing per target).
   *  Transient bookkeeping, reset on every swing start; optional so external constructors
   *  (tests/fakes) don't need to provide it. */
  meleeHitUids?: string[];
  /** Power Burst arm window (ROM +0x6fb), frames remaining. Y press edge sets this to
   *  BURST.ARM_WINDOW_FRAMES (6, DERIVED — `FUN_80069814` chunk_0009.c:113); decrements to 0
   *  per frame (mirrors `zz_005b2b8_` chunk_0007.c:3473-3490); a re-press re-arms it. NOTE
   *  (behavior-notes.md (aj)): the ROM also decrements +0x6fb in the fusion per-slot loop and
   *  its expiry there drives the burst/fusion END path — the audit's "6-frame arm window" and
   *  the fusion timer may be the SAME field read in two different contexts, not two fields;
   *  this still needs trace T3 to reconcile before ATK-012 wires any real duration/effects.
   *  UPDATE (behavior-notes.md (ao), official NA instruction manual, CONFIRMED_MANUAL tier):
   *  "press the button at the same time [as your partner] for simultaneous power bursts" — this
   *  gives the 6-frame window a coherent reading as a SIMULTANEITY tolerance for synchronized
   *  co-op bursts/fusion (partner's Y within the window counts as "same time"), not merely an
   *  arm/activation buffer. Manual text is still not numeric ROM truth, so the exact semantics
   *  (whose window, how it gates pairing) remain for trace T3 to reconcile. */
  burstArmFrames: number;
  /** Power Burst activation flag (ROM +0x6fc = 1, set by `zz_005b2b8_` when +0x6fb is nonzero
   *  and the borg is active). Gated behind constants.ts BURST.ENABLED (default false, BLOCKED-
   *  until-T3) so this is always false in real battles; has ZERO gameplay effects (ATK-011
   *  shell only — see ATK-012). Per (ao) (official manual, CONFIRMED_MANUAL): real activation's
   *  precondition is "the burst gauge is at max" — the gauge itself is still unlocated in RAM,
   *  which is exactly why BURST.ENABLED stays false until that meter is found and wired. */
  burstActive: boolean;
  /** Power Burst "paired" flag (ROM +0x6fa = 1, set alongside +0x6fc by `zz_005b2b8_`). Shell
   *  bookkeeping only; not wired to fusion pairing (fusionPartnerUid/fusionState below) until
   *  a later ticket confirms the relationship. See (ao) note on burstArmFrames re: simultaneous
   *  co-op bursts — "paired" may end up meaning that, but it is UNCONFIRMED pending T3. */
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
}

export type BattleResult = "ongoing" | "win" | "lose" | "draw";

export type ProjectileVisualKind = "energy" | "flame" | "muzzle";

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
  knockback: number;
  homingTurn: number;
  homingTarget: string | null;
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
  /** Frames remaining before this projectile may apply its next hit while persisting
   *  (`consumeOnHit === false`). Mirrors the ROM's SINGLE per-object counter at object+0x4e,
   *  reloaded from the damage record's s8+0x16 `rehitIntervalFrames` on every hit application
   *  (chunk_0013.c:1175-1182) — NOT a per-target map. Interval 0 reloads to 0, so the object
   *  stays hit-ready and can re-hit (a new target, or the same one) every frame it overlaps
   *  (chunk_0013.c:1188 gates despawn, not this counter). Absent/undefined = not yet initialized;
   *  treated as hit-ready (0) the first time stepProjectiles sees a persisting projectile. */
  rehitCounter?: number;
}

export interface BattleState {
  borgs: BorgRuntime[];
  projectiles: Projectile[];
  /** Remaining energy per team = sum of not-yet-defeated on-field + not-yet-deployed borg energy. */
  energy: Record<number, number>;
  /** Whole borgs defeated per team, counted at the source death event before auto-deploy. */
  defeated: Record<number, number>;
  /** Energy/cost defeated per team, counted from each defeated borg's profile energy. */
  defeatedEnergy: Record<number, number>;
  /** The currently-active (controllable) borg uid per player id. */
  activeUidByPlayer: Record<string, string>;
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

/** The driver object returned by createBattle. */
export interface Battle {
  state: BattleState;
  /** Advance the sim by one fixed step. `dt` is accepted for API symmetry but the sim is
   *  fixed-step (SIM.DT); pass it through for documentation/compat. */
  step(dt: number, inputs: Record<string, PlayerInput>): void;
}

/** Internal: a deploy queue entry (a borg not yet on the field). */
export interface DeployEntry {
  borgId: string;
  profile: BorgProfile;
}
