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
//     the ABSOLUTE scale is a tuning choice. HP/damage offsets were NOT recoverable from the
//     ROM (behavior-notes.md s4f), so the damage formula is ours, not a port.
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
   * TUNED (no ROM formula was recoverable).
   */
  DEF_PER_STAT: 0.06,
  MIN_MULT: 0.25,
  /** A hit that brings HP to <= KNOCKDOWN_FRACTION of a big blow forces knockdown. */
  KNOCKDOWN_DMG: 40,
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
