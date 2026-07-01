// Single tuned CONSTANTS block for the gameplay sim.
//
// What is DERIVED from the decomp vs. TUNED:
//   - WAKE_UP_INVINCIBILITY_FRAMES = 60: DERIVED. behavior-notes.md s4a — entering the
//     wake state writes 60.0 to struct+0x720, counted down ~1.0/frame and clamped at 0.
//     We port the countdown exactly (decrement 1.0/frame, clamp 0, clear flag).
//   - SIM_HZ = 60: DERIVED. GameCube ran at 60 fps; the "60 frames ~= 1s" note confirms it.
//   - Ground plane Y and "forward = +Z": DERIVED. ram-trace-analysis.md s3.1 (Y=10 grounded,
//     holding FORWARD produced +Z movement). GROUND_Y default 10 to match the trace.
//   - Everything else (speeds, gravity, damage scale, ranges, cooldowns): TUNED to feel like
//     a fast 3D arena fighter. RELATIVE values come from stats (speed/attack/shot/defense);
//     the ABSOLUTE scale is a tuning choice.
//
//   - HP field: DERIVED (2026-07-01). Confirmed live — a 16-bit uint mirrored at 5 fixed
//     addresses (0x803b069c, 0x805dbf86, 0x805f3850/58/5c) tracks the on-screen HP gauge;
//     found independently by a 6-save-state MEM1 diff AND by Dolphin's live Cheat Search,
//     converging on the same address set (behavior-notes.md s4f).
//   - Damage application mechanism: DERIVED (2026-07-01). Live disassembly at the HP write site
//     (object+0x1C6) showed a plain `HP -= raw_damage`, clamped at 0, with a secondary bound
//     check against a neighboring field at +0x1C4 (behavior-notes.md s4h). applyHit()/mitigate()
//     in combat.ts already implement subtract-then-clamp-at-zero, matching this shape exactly.
//   - object+0x88 mismatch divisor: DERIVED mechanism, but NOT wired to borgs.json display type.
//     Ghidra export re-read (behavior-notes.md s4m) shows +0x88 is copied from match slot/team
//     state (`PTR_DAT_80433934[slot+0xcb]`) in the active spawn paths. The five-value
//     borgs.json `type` string is not a safe proxy, so combat.ts intentionally does not apply
//     TYPE_MISMATCH_DIVISOR yet.
//   - The exact attack/defense-to-raw-damage coefficients (DEF_PER_STAT/MIN_MULT/DMG_BASE/
//     DMG_PER_STAT below) remain TUNED. Ghidra located the real formula function (`zz_003cd5c_`,
//     behavior-notes.md s4j) — it's a multi-stage multiplicative formula keyed off a per-move
//     data pointer (`power * (1 + k*(atkStat - baseline))`, plus further sub-object-gated
//     multipliers), not the linear BASE+stat*PER_STAT shape used here. Full decode of that
//     function (naming its float constants and the small multiplier table it indexes) is the
//     next step before these constants could be replaced with a derived formula.
//
// Units: world units per frame (or per second where noted). Stage bounds from the RAM trace
// were in the low thousands (X~3000, Z~-680..-960), so absolute speeds are scaled to that world.

export const SIM = {
  /** Frames per second the fixed-step sim assumes (GameCube native). DERIVED. */
  HZ: 60,
  /** Seconds per frame. */
  DT: 1 / 60,
} as const;

/** Wake-up / hit invincibility, in frames. DERIVED from decomp (struct+0x720 = 60.0). */
export const WAKE_UP_INVINCIBILITY_FRAMES = 60;

/** Spawn (deploy) invincibility, frames. TUNED — brief protection on auto-spawn. */
export const SPAWN_INVINCIBILITY_FRAMES = 45;

export const MOVE = {
  /**
   * Ground move speed (units/frame) = BASE + speed_stat * PER_STAT.
   * speed stat ranges 0..10; G RED (speed 6) ~= 5.5 u/frame ~= 330 u/s, in line with the
   * RAM trace where the player crossed ~284 units over the snapshot interval. TUNED scale.
   */
  GROUND_BASE: 1.0,
  GROUND_PER_STAT: 0.75,
  /** Flight horizontal speed is a touch faster than ground. */
  FLY_MULT: 1.15,
  /** Acceleration toward target velocity (units/frame^2) for snappy-but-not-instant feel. */
  ACCEL: 1.2,
  /** Deceleration when no input (units/frame^2). */
  DECEL: 1.6,
  /** Yaw turn rate toward facing target (radians/frame). */
  TURN_RATE: 0.35,
} as const;

export const JUMP = {
  /** Initial upward velocity of a jump (units/frame). TUNED. */
  VELOCITY: 4.2,
  /** Gravity pulling Y down (units/frame^2). TUNED. */
  GRAVITY: 0.42,
  /** Terminal fall speed (units/frame). */
  MAX_FALL: 8.0,
  /** Hold-jump-in-air boost flight: upward thrust while held (units/frame^2). Flyers only. */
  BOOST_THRUST: 0.55,
  /** Max upward speed under boost flight (units/frame). */
  BOOST_MAX_RISE: 3.0,
  /** Boost flight drains over time; thrust is gated by remaining fuel (frames of boost). */
  BOOST_FUEL_FRAMES: 90,
  /** Ground Y level (RAM trace: ~10 when grounded). DERIVED. */
  GROUND_Y: 10,
} as const;

export const DASH = {
  /** Dash/step impulse speed (units/frame). TUNED. */
  SPEED: 9.0,
  /** Dash duration (frames). */
  DURATION: 10,
  /** Invincibility frames granted by a dash/step (dodge). TUNED. */
  IFRAMES: 8,
  /** Cooldown before another dash (frames). */
  COOLDOWN: 24,
} as const;

export const MELEE = {
  /** Reach of a melee swing (XZ units). TUNED. */
  RANGE: 60,
  /** Vertical tolerance for a melee hit (units). */
  Y_TOLERANCE: 50,
  /** Active-hit window opens this many frames into the swing. */
  STARTUP: 4,
  /** Active-hit window length (frames). */
  ACTIVE: 6,
  /** Total swing length / recovery (frames) — also the attack-state duration. */
  DURATION: 18,
  /** Cooldown after a swing (frames). */
  COOLDOWN: 10,
  /** damage = BASE + attack_stat * PER_STAT, before defense mitigation. TUNED. */
  DMG_BASE: 6,
  DMG_PER_STAT: 4,
  /** Hitstun applied to the victim (frames). */
  HITSTUN: 14,
  /** Knockback speed imparted (units/frame). */
  KNOCKBACK: 5,
} as const;

export const SHOT = {
  /** Projectile speed (units/frame). TUNED. */
  SPEED: 22,
  /** Projectile lifetime (frames) -> max range ~= SPEED*LIFETIME. */
  LIFETIME: 40,
  /** Homing turn rate toward lockTarget (radians/frame); 0 = straight. */
  HOMING_TURN: 0.08,
  /** Hit radius (XZ units) for projectile-vs-borg. */
  HIT_RADIUS: 35,
  /** Frames between shots while firing. */
  FIRE_COOLDOWN: 12,
  /** Magazine size before a reload. */
  AMMO_MAX: 6,
  /** Reload time (frames) when ammo hits 0. */
  RELOAD_FRAMES: 60,
  /** damage = BASE + shot_stat * PER_STAT, before defense. TUNED. */
  DMG_BASE: 4,
  DMG_PER_STAT: 3,
  /** Hitstun applied on projectile hit (frames). */
  HITSTUN: 10,
  /** Knockback imparted (units/frame). */
  KNOCKBACK: 3,
} as const;

export const SPECIAL = {
  /** Special (Y) damage multiplier over a melee/shot hit. TUNED. */
  DMG_MULT: 2.0,
  /** Special cooldown (frames). */
  COOLDOWN: 90,
  /** Special "burst" radius for an AoE-style special (XZ units). */
  RADIUS: 110,
  /** Special-state duration (frames). */
  DURATION: 26,
  /** Knockback (units/frame). */
  KNOCKBACK: 7,
  /** Hitstun (frames). */
  HITSTUN: 18,
} as const;

export const DAMAGE = {
  /**
   * Defense mitigation: incoming damage is multiplied by (1 - defense*DEF_PER_STAT),
   * floored at MIN_MULT so high-defense borgs still take chip damage. defense 0..10.
   * TUNED, and now confirmed to be a deliberately-simplified stand-in rather than a missing
   * lookup: behavior-notes.md s4k traced the real base-damage formula (`zz_003cd5c_`) to its end
   * and found the ROM has no single "defense percentage" at all — mitigation is spread across
   * several attacker/defender rank+category table lookups (indexed by fields at object+0x43a,
   * +0x6ca, +0x88, and a HP-ratio-derived index) plus a per-attacker "rank" table. There is no
   * flat percentage to extract from that; a percentage-based model is a reasonable simplification
   * of a system whose real shape is table-driven, not a not-yet-found formula.
   */
  DEF_PER_STAT: 0.06,
  MIN_MULT: 0.25,
  /** A hit that brings HP to <= KNOCKDOWN_FRACTION of a big blow forces knockdown. */
  KNOCKDOWN_DMG: 40,
  /**
   * DERIVED constant for the special +0x88 mismatch branch in `zz_002e2a8_`: when that branch
   * uses the object+0x88 byte, mismatch quarters the value via rounded /4 before HP subtract.
   * Not currently applied in combat.ts because +0x88 is a match slot/team byte in spawn paths,
   * not borgs.json's five-value display type (behavior-notes.md s4m).
   */
  TYPE_MISMATCH_DIVISOR: 4,
} as const;

export const STATE = {
  /** Knockdown (down) lie-time before the wake-up i-frames kick in (frames). */
  DOWN_DURATION: 30,
  /** Death state duration before the borg is removed / next deploys (frames). */
  DEATH_DURATION: 30,
  /** Spawn (deploy) animation lock (frames). */
  SPAWN_DURATION: 20,
} as const;

export const LOCK = {
  /** Max lock-on acquisition range (XZ units). TUNED. */
  RANGE: 1200,
  /** Lock-on cone half-angle (radians) — must be "in front" to acquire. */
  CONE: Math.PI * 0.55,
} as const;

export const AI = {
  /** AI desired engage distance for melee borgs (XZ units). */
  MELEE_RANGE: 50,
  /** AI desired engage distance for ranged borgs. */
  RANGED_RANGE: 600,
  /** Slack around the desired range before AI stops advancing. */
  RANGE_SLACK: 60,
  /** AI re-evaluates its target every N frames. */
  RETARGET_FRAMES: 30,
} as const;

/** Default stage half-extent if a BattleConfig omits bounds (XZ units from origin). */
export const DEFAULT_BOUNDS = { x: 4000, z: 4000 } as const;
