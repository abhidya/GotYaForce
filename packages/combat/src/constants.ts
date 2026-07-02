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
//   - object+0x88 same-team divisor (DAMAGE.SAME_TEAM_HIT_DIVISOR): DERIVED mechanism (a 0.25x
//     friendly-fire reducer, not a "type mismatch" — see s4o, which corrected the s4m-era name).
//     Ghidra export re-read (behavior-notes.md s4m) shows +0x88 is copied from match slot/team
//     state (`PTR_DAT_80433934[slot+0xcb]`) in the active spawn paths. Wired in combat.ts for
//     melee, special, and projectile hits.
//   - The exact attack/defense-to-raw-damage coefficients (DEF_PER_STAT/MIN_MULT/DMG_BASE/
//     DMG_PER_STAT below) remain TUNED. Ghidra located and substantially decoded the real formula
//     function (`zz_003cd5c_`, behavior-notes.md s4j/s4o) — it's a multi-stage multiplicative
//     formula keyed off a per-move data pointer (`power * (1 + k*(atkStat - baseline))`, plus
//     HP-ratio "comeback" scaling, a defender/attacker-category type matrix, and a rank/handicap
//     table that appears to be keyed by team-slot, NOT by borgs.json's 0-10 attack/shot stat.
//     The category matrix piece is now DERIVED and wired in typeDamage.ts (s4w). The rest of the
//     formula still blocks replacing these tuned linear coefficients with a derived formula.
//   - Knockback DIRECTION: DERIVED (2026-07-01, behavior-notes.md s4p). `zz_00300bc_` (0x800300bc)
//     computes launch direction (yaw/pitch as BAM16 shorts) from one of 5 vector-source modes
//     selected by a per-move byte, plus a per-move angular trim. Mode 1 (attacker->target
//     relative-position vector, the only mode this port has data to compute) is now ported byte-
//     for-byte (atan2 -> BAM16 via the confirmed 65536/(2*pi) constant) in
//     packages/physics/src/knockback.ts and wired into combat.ts's applyHit(). Modes 0/2/4 need
//     sub-object fields (muzzle points, camera-aim vectors) this port doesn't model and remain
//     unported; mode 3 ("linked object") is exposed but not wired (no linked-object concept on
//     BorgRuntime yet). The per-move angle-trim VALUES are still-undecoded hit.bin data, so trim
//     is always 0 for now (mechanism DERIVED, values TUNED-absent).
//     Knockback MAGNITUDE (MELEE.KNOCKBACK/HITSTUN, SHOT.KNOCKBACK/HITSTUN, SPECIAL.KNOCKBACK/
//     HITSTUN below) remains entirely TUNED — `zz_00300bc_` only ever computes/stores a direction,
//     never a speed/force value or hitstun duration. Do not read the direction fix as license to
//     upgrade these magnitude/hitstun constants; they need a separate trace of whatever consumes
//     the stored yaw/pitch to actually apply a velocity impulse.
//   - LOCK.RANGE/CONE (manual lock-on acquisition): TUNED, CHECKED CLOSED (2026-07-01,
//     behavior-notes.md s4q) — a thorough search found no manual scan-and-select enemy-lock
//     system anywhere in the ROM; every "target" field in the decomp is hit-reactive bookkeeping,
//     not a player-driven lock/cycle mechanic. This is a confirmed absence, not an unsolved lead.
//   - Full TUNED-constants audit (2026-07-01, behavior-notes.md s4s): every remaining TUNED field
//     below (MOVE/JUMP/DASH/MELEE/SHOT/SPECIAL/STATE/AI blocks) was checked against the corpus and
//     could NOT be honestly upgraded this pass — see s4s for the per-field reasoning and dead-end
//     addresses (so future sessions don't re-grep the same ground). One real lead came out of it:
//     `resolve_hitbox_target_effects_and_damage` (0x8002e2a8) sets a trio of fields (+0x684/+0x688/
//     +0x68c) to a confirmed 60.0 on every non-lethal hit, decremented by the same +0x1dcc step as
//     the invincibility timer — structurally hitstun-shaped, but s4s found it feeds into unrelated
//     attack-flag logic (zz_005f00c_) alongside a separate 0-99 combo/rank counter, with no +0x544
//     state write anywhere nearby, so it is NOT confirmed to be "how long the victim can't act."
//     MELEE.HITSTUN/SHOT.HITSTUN stay TUNED rather than silently becoming 60 — porting that number
//     without confirming what it gates would be exactly the wrong-but-confident mistake this file's
//     convention exists to prevent. packages/physics/src and packages/ai/src were also audited:
//     physics is pure math (no constants to check), and packages/ai/src is an empty stub — the AI
//     block below isn't backed by a packages/ai implementation yet.
//   - Borg state-machine dispatch CRACKED (2026-07-01, behavior-notes.md s4u): the "+0x544 switch"
//     everyone kept hitting a wall on doesn't exist. The real dispatch is a 35-entry function-
//     pointer table (0x802d3570-0x802d35f8) indexed by object+0x6fe (primary, dispatched per-frame
//     from zz_005c694_/0x8005c694), with two aliasing index fields (+0x591, +0x540) reading the
//     SAME array at a fixed offset. +0x544 (and +0x545/546/547) is a per-handler LOCAL phase
//     counter zeroed by the transition primitive zz_005ec04_ on every state change — not a global
//     enum. One concrete, portable mechanism came out of fully reading the melee-attack-active
//     handler (table slot 23, 0x8005d494): it re-arms the confirmed WAKE_UP_INVINCIBILITY_FRAMES
//     (60.0 @ +0x720) EVERY FRAME it's active, not once on entry — i.e. attackers are continuously
//     invincible for the handler's active duration, plus ~60 more frames of decay after it exits.
//     That boolean mechanism is DERIVED and ported below as STATE.MELEE_IFRAME_REFRESH_PER_FRAME.
//     The full 35-slot table (addresses + Likely-but-not-Confirmed gameplay labels) is in s4u —
//     do not re-derive it, but also do not treat the per-slot LABELS as DERIVED, only the addresses
//     and mechanisms are. DOWN_DURATION/DEATH_DURATION/SPAWN_DURATION/MELEE.COOLDOWN/etc. below
//     remain TUNED: s4u identifies WHICH handler is Likely each state family but the actual frame
//     counts are gated by animation-completion flags (+0x1d0e/+0x1d0f) and per-borg-type data
//     tables, not a single named ROM constant — porting a guessed duration would be exactly the
//     wrong-but-confident mistake this file's convention forbids.
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
   *
   * DERIVED-provisional anchor (2026-07-01, behavior-notes §ac): live per-frame trace of
   * G RED (speed 6) walking in 4P versus measured a constant 22.0 world-units/frame
   * (golden: user-data/dolphin-trace/golden/recipe-pos20-pl0615-chain.jsonl; position read
   * from the confirmed actor chain *(u32*)0x803C4E84 → +0x20 vec3; per-frame deltas exactly
   * (-16.9, -14.1)). BASE/PER_STAT are the old TUNED values scaled 4x so speed-6 hits the
   * measured 22.0 while preserving the TUNED stat spread — the BASE/PER_STAT split itself is
   * still TUNED (one data point can't pin two constants; capture a different-speed borg to
   * derive the split). Single capture: reproduce before treating the anchor as fully DERIVED.
   * Note: measured on the BACKWARD walk — the only pure translation under lock-relative
   * controls (behavior-notes §y); forward/strafe may differ.
   */
  GROUND_BASE: 4.0,
  GROUND_PER_STAT: 3.0,
  /** Flight horizontal speed is a touch faster than ground. */
  FLY_MULT: 1.15,
  /**
   * Acceleration toward target velocity (units/frame^2). TUNED-rescaled 4x alongside the
   * DERIVED ground-speed anchor so spin-up time (frames to reach max) keeps its tuned feel.
   */
  ACCEL: 4.8,
  /** Deceleration when no input (units/frame^2). TUNED-rescaled 4x (see ACCEL). */
  DECEL: 6.4,
  /** Yaw turn rate toward facing target (radians/frame). */
  TURN_RATE: 0.35,
} as const;

export const JUMP = {
  /**
   * Initial upward velocity of a jump (units/frame). TUNED — audited 2026-07-01 (s4s), not
   * findable: no one-time positive-Y-velocity write gated on a "jump" state was isolated; the
   * borg struct's gameplay Y-velocity field itself isn't confirmed (candidate +0x60 collides
   * with an unrelated object type in the one decrement pattern found — see s4s).
   */
  VELOCITY: 4.2,
  /** Gravity pulling Y down (units/frame^2). TUNED — audited 2026-07-01 (s4s), not findable. */
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
  /**
   * Dash/step impulse speed (units/frame). TUNED — audited 2026-07-01 (s4s): every non-60.0
   * write to the confirmed invincibility field (+0x720) was checked (120.0 in a scripted
   * spawn-arc handler @0x8005e868, 30.0/60.0 in a respawn-reset helper @0x80060b60) and neither
   * is a dash/step state. No dash/dodge state was found anywhere in the corpus this pass.
   */
  /**
   * TUNED-rescaled 4x (2026-07-01) alongside the DERIVED ground-speed anchor in MOVE — a
   * dash must clearly outpace the measured 22.0 u/f walk. Absolute value still TUNED;
   * capture left/right dodge-dashes on the +0x20 chain to derive it.
   */
  SPEED: 36.0,
  /** Dash duration (frames). TUNED — see SPEED note; no dash state found to time. */
  DURATION: 10,
  /** Invincibility frames granted by a dash/step (dodge). TUNED — see SPEED note. */
  IFRAMES: 8,
  /** Cooldown before another dash (frames). TUNED — see SPEED note. */
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
  /** Cooldown after a swing (frames). TUNED — audited 2026-07-01 (s4s), not findable: the
   *  0x8005cc00/0x8005d494 state dispatch's per-case semantics (which +0x544 number is "melee
   *  attack") remain unmapped, so no attack-specific cooldown constant is isolable yet. */
  COOLDOWN: 10,
  /** damage = BASE + attack_stat * PER_STAT, before defense mitigation. TUNED — see constants.ts
   *  header + behavior-notes.md s4o: the real formula's per-object stat is a float on a linked
   *  sub-object at +0xc4, not confirmed to correspond to borgs.json's 0-10 int `attack` at all. */
  DMG_BASE: 6,
  DMG_PER_STAT: 4,
  /**
   * Hitstun applied to the victim (frames). TUNED — audited 2026-07-01 (s4s). A real, address-
   * cited 60-frame timer trio (object+0x684/+0x688/+0x68c, set by
   * resolve_hitbox_target_effects_and_damage @0x8002e2a8, decremented by the confirmed +0x1dcc
   * step) is set on every non-lethal hit — structurally hitstun-shaped, but its actual gameplay
   * role is unconfirmed (it feeds attack-flag logic in zz_005f00c_ @0x8005f00c alongside a
   * separate combo/rank counter, not a clean "borg can't act" gate). Do not port 60 here without
   * confirming what +0x684/688/68c actually locks out — see s4s for the exact next trace step.
   */
  HITSTUN: 14,
  /** Knockback speed imparted (units/frame). TUNED — s4p derived knockback DIRECTION fully
   *  (wired via packages/physics/src/knockback.ts), but never found a magnitude/speed value;
   *  zz_00300bc_ only ever writes angle fields, never a force/velocity. Magnitude stays TUNED. */
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
  /** damage = BASE + shot_stat * PER_STAT, before defense. TUNED — same caveat as MELEE.DMG_BASE
   *  (behavior-notes.md s4o): the real per-attacker stat term is not confirmed to be borgs.json's
   *  0-10 `shot` int. */
  DMG_BASE: 4,
  DMG_PER_STAT: 3,
  /** Hitstun applied on projectile hit (frames). TUNED — same +0x684/688/68c caveat as
   *  MELEE.HITSTUN above (behavior-notes.md s4s); the timer trio is hit-generic (set by the same
   *  resolve_hitbox_target_effects_and_damage path for both melee and shot hits), so the same
   *  "don't port 60 without confirming the gate" caution applies here too. */
  HITSTUN: 10,
  /** Knockback imparted (units/frame). TUNED — see MELEE.KNOCKBACK note; direction is DERIVED
   *  (s4p), magnitude is not. */
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
   * lookup: behavior-notes.md s4k/s4o traced the real base-damage formula (`zz_003cd5c_`) and
   * found the ROM has no single "defense percentage" at all. One table-driven piece, the
   * attacker/defender type-category multiplier, is now ported separately in typeDamage.ts (s4w).
   * The remaining rank/handicap/HP-ratio pieces are still not a flat percentage, so this
   * percentage-based defense model stays an explicit simplification.
   */
  DEF_PER_STAT: 0.06,
  MIN_MULT: 0.25,
  /** A hit that brings HP to <= KNOCKDOWN_FRACTION of a big blow forces knockdown. */
  KNOCKDOWN_DMG: 40,
  /**
   * DERIVED and RENAMED (2026-07-01, behavior-notes.md s4o): this is a SAME-TEAM (friendly-fire)
   * damage divisor, not a "type mismatch" — direct read of `zz_003cd5c_` (0x8003cd5c) shows
   * `if (attacker+0x88 == defender+0x88) damage *= 0.25` (exact ROM constant, confirmed 0.25 via
   * raw float read), and +0x88 is the match slot/team byte (s4m), not a type category. Formerly
   * named TYPE_MISMATCH_DIVISOR — that name was wrong on both counts (it's a match, not a
   * mismatch; and it's team, not type). Kept as a divisor (4 = 1/0.25) for call-site continuity.
   * Wired in combat.ts for melee, special, and projectile hits: same-team targets can be hit,
   * with raw damage divided by this value before normal defense mitigation.
   */
  SAME_TEAM_HIT_DIVISOR: 4,
  /**
   * DERIVED (2026-07-01, behavior-notes.md s4o): a second, harsher block/reflect divisor found in
   * the same formula — `damage /= 40.0` when a defender state bit (+0x59c & 0x1000) matches a
   * move-flag bit, gated on the defender not being a sub-object. Likely a guard/shield/reflect
   * mechanic. Not named, not wired — the move-flag and target-state bit meanings aren't traced
   * yet, so there's no source of truth in the port to gate this on.
   */
  BLOCK_OR_REFLECT_DIVISOR: 40,
} as const;

export const STATE = {
  /**
   * DERIVED (2026-07-01, behavior-notes.md s4u). The real borg state dispatch is a 35-entry
   * function-pointer table on object+0x6fe (not a switch on +0x544 — see s4u for the full
   * table). Table slot 23 (0x8005d494), the Likely melee-attack-active handler, writes the
   * confirmed invincibility field (object+0x720) to the confirmed 60.0 constant as the FIRST
   * statement of every call while that handler is active — not just once on entry. Combined
   * with the already-ported (timer, decrement ~1.0/frame, clamp-at-0) countdown (s4a), the net
   * effect is: an active melee attack keeps its owner invincible continuously for the handler's
   * whole active window, plus ~60 more frames of decay afterward. This is a mechanism toggle,
   * not a numeric guess, so it's DERIVED even though the exact handler-duration (how many
   * frames slot 23 stays active) is still TUNED — see MELEE.DURATION-adjacent notes below.
   */
  MELEE_IFRAME_REFRESH_PER_FRAME: true,
  /** Knockdown (down) lie-time before the wake-up i-frames kick in (frames). TUNED — s4u
   *  identifies the Likely knockdown/getting-up handler family (table slots 27-30, dispatched
   *  via +0x6fe values 18-21) but the actual frame count is gated by animation-completion flags
   *  (+0x1d0e/+0x1d0f) and per-borg-type data tables, not a single named ROM constant. */
  DOWN_DURATION: 30,
  /** Death state duration before the borg is removed / next deploys (frames). TUNED — see
   *  DOWN_DURATION note; same "which handler, but no fixed duration constant" situation per s4u. */
  DEATH_DURATION: 30,
  /** Spawn (deploy) animation lock (frames). TUNED — s4u identifies table slots 0-2
   *  (0x8005be08/bec8/bf6c, dispatched via +0x540 0-2) as the Likely spawn drop-in sequence, but
   *  its phase transitions are timer-driven from computed/per-borg fields, not one fixed constant. */
  SPAWN_DURATION: 20,
} as const;

export const LOCK = {
  /**
   * TUNED — and CHECKED CLOSED, not an open TODO (2026-07-01, behavior-notes.md s4q). A
   * thorough corpus search (borg state-machine dispatch 0x8005cc00/0x8005d494, every writer of
   * the "last enemy" globals DAT_803b06a8/object+2000/+0x7d1, every loop over the 6-actor table
   * DAT_803c4e84, every PSVEC distance-check call site, PAD/SI input symbols) found no
   * button-triggered scan-and-select enemy-lock mechanic in the ROM at all — every "target" field
   * that exists is hit-REACTIVE bookkeeping (who last hit whom, for a one-shot reaction
   * animation), never a scan-selective player lock system. RANGE/CONE below are an honest design
   * choice with no ROM formula to replace them; do not re-derive without new leads.
   */
  RANGE: 1200,
  /** Lock-on cone half-angle (radians) — must be "in front" to acquire. TUNED (see note above). */
  CONE: Math.PI * 0.55,
} as const;

export const AI = {
  /**
   * AI desired engage distance for melee borgs (XZ units). TUNED — audited 2026-07-01 (s4s):
   * no packages/ai implementation exists yet (packages/ai/src/index.ts is an empty stub), and no
   * isolated "CPU decision" function was found in the corpus — research/decomp/index/
   * cpu-ai-evidence.md independently reached the same conclusion (CPU and player-controlled
   * actors share the same low-level dispatch, no separate AI brain function identified).
   */
  MELEE_RANGE: 50,
  /** AI desired engage distance for ranged borgs. TUNED — see MELEE_RANGE note. */
  RANGED_RANGE: 600,
  /** Slack around the desired range before AI stops advancing. TUNED — see MELEE_RANGE note. */
  RANGE_SLACK: 60,
  /** AI re-evaluates its target every N frames. TUNED — see MELEE_RANGE note. */
  RETARGET_FRAMES: 30,
} as const;

/** Default stage half-extent if a BattleConfig omits bounds (XZ units from origin). */
export const DEFAULT_BOUNDS = { x: 4000, z: 4000 } as const;
