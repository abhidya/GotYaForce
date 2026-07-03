// Single tuned CONSTANTS block for the gameplay sim.
//
// What is DERIVED from the decomp vs. TUNED:
//   - WAKE_UP_INVINCIBILITY_FRAMES = 60: DERIVED. behavior-notes.md s4a — entering the
//     wake state writes 60.0 to struct+0x720, counted down ~1.0/frame and clamped at 0.
//     We port the countdown exactly (decrement 1.0/frame, clamp 0, clear flag).
//   - SIM_HZ = 60: DERIVED. GameCube ran at 60 fps; the "60 frames ~= 1s" note confirms it.
//   - Ground plane Y and "forward = +Z": DERIVED. ram-trace-analysis.md s3.1 (Y=10 grounded,
//     holding FORWARD produced +Z movement). GROUND_Y default 10 to match the trace.
//   - Movement gravity/ranges/cooldowns and knockback magnitudes remain TUNED. Combat HP
//     damage now uses the decoded zz_003cd5c_ formula via damageFormula.ts for runtime hits;
//     MELEE/SHOT damage constants below remain only as legacy/direct-helper fallbacks.
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
//   - Runtime HP damage formula: DERIVED (2026-07-03, behavior-notes.md ag/ah). combat.ts
//     now calls damageFormula.ts for real attacker-context hits: record.hpDamage, type matrix,
//     same-team 0.25x, Challenge side ranks, HP-ratio curves, defense curve selectors, handicap
//     defaults, and combo falloff are table-backed from the decomp. Remaining formula context
//     not yet modeled: hero flag (+0x3e6), pair-attack flag (+0x6fc), force-gauge ratio, guard/
//     reflect state, and actor level/handicap init sites. MELEE/SHOT DMG_BASE/DMG_PER_STAT below
//     are retained for legacy direct applyHit callers and should not be treated as runtime truth.
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
  /** Legacy direct-helper fallback only. Runtime hits use damageFormula.ts record.hpDamage. */
  DMG_BASE: 6,
  DMG_PER_STAT: 4,
  /**
   * Reaction LENGTH after a confirmed melee stagger (frames). Still TUNED — the original's
   * stagger reaction duration is animation-gated (per-borg anim completion flags), not a ROM
   * constant, so this stays a tuned stand-in for the animation length. The stagger TRIGGER,
   * however, is now DERIVED and lives in the gauge model (combat.ts applyHit + gauges.ts +
   * STAGGER below): the original has NO flat per-hit hitstun — a hit only interrupts when the
   * down gauge (+0x6c6) drops below 1, the balance gauge (+0x6c2) depletes (0x6fd |= 0xa6),
   * or the damage record's reaction flags (+0x0b bits 2|0x80) force it
   * (chunk_0003.c:6255-6263 routes non-staggering hits straight to
   * dispatch_slot_action_update). The old s4s mystery is resolved: the +0x684/+0x688/+0x68c
   * 60-frame trio is the balance-refill / down-reset / combo-window timers (see STAGGER).
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
  /** Legacy direct-helper fallback only. Runtime shots use damageFormula.ts record.hpDamage. */
  DMG_BASE: 4,
  DMG_PER_STAT: 3,
  /** Reaction LENGTH after a confirmed shot stagger (frames). Still TUNED (animation-gated in
   *  ROM — see MELEE.HITSTUN note); the stagger TRIGGER is now DERIVED via the gauge model
   *  (combat.ts applyHit + gauges.ts). Normal shots map to damage record 0 (reactionFlags 1,
   *  no forced stagger), so a shot only interrupts once it depletes a gauge — a lone shot no
   *  longer flinches the victim at all. */
  HITSTUN: 10,
  /** Knockback imparted (units/frame). TUNED — see MELEE.KNOCKBACK note; direction is DERIVED
   *  (s4p), magnitude is not. */
  KNOCKBACK: 3,
} as const;

export const COMBO = {
  /**
   * Melee combo chain scaling, all TUNED. WHICH borgs chain (and for how many hits) comes from
   * real exported swing-bank counts (actionProfiles.json melee.comboHits, generated by
   * scripts/gen-combat-action-profiles.mjs), but the per-step damage ramp, the faster startup on
   * chained swings, and the finisher knockback bonus are design choices — the hit-bin per-move
   * records that would hold the originals remain undecoded (see constants header).
   * Damage multiplier per chain step (index = combo step, clamped to the last entry).
   */
  STEP_DAMAGE_MULT: [1, 1.08, 1.22],
  /** Chained swings start up faster than the opener (multiplier on melee startup). TUNED. */
  STEP_STARTUP_SCALE: 0.75,
  /** Extra knockback on the chain's final hit, which also forces a knockdown. TUNED. */
  FINISHER_KNOCKBACK_MULT: 1.4,
} as const;

export const CHARGE = {
  /**
   * Hold-B charge shot scaling, all TUNED (same convention as COMBO above: profile data selects
   * WHO can charge — beam/heavy families + the G Red hero line — but tier thresholds live in the
   * per-borg profile and these cross-tier multipliers are design choices). Tier 0 = tap (an
   * unmodified shot), tier 1 / tier 2 = held past the profile's chargeTier1Frames /
   * chargeTier2Frames (~90f cap). Damage multipliers are per-profile
   * (chargeTier1DamageMult/chargeTier2DamageMult); speed/radius/hitstun/knockback scale here.
   */
  TIER1_SPEED_MULT: 1.1,
  TIER2_SPEED_MULT: 1.25,
  TIER1_RADIUS_MULT: 1.25,
  TIER2_RADIUS_MULT: 1.6,
  TIER1_HITSTUN_MULT: 1.2,
  TIER2_HITSTUN_MULT: 1.5,
  TIER1_KNOCKBACK_MULT: 1.2,
  TIER2_KNOCKBACK_MULT: 1.5,
} as const;

export const SPECIAL = {
  /** Special (X) damage multiplier over a melee/shot hit. TUNED. */
  DMG_MULT: 2.0,
  /** Special cooldown (frames). */
  COOLDOWN: 90,
  /** Special "burst" radius for an AoE-style special (XZ units). */
  RADIUS: 110,
  /** Special-state duration (frames). */
  DURATION: 26,
  /** Knockback (units/frame). */
  KNOCKBACK: 7,
  /** Reaction LENGTH after a confirmed special-hit stagger (frames). Still TUNED (animation-
   *  gated in ROM — see MELEE.HITSTUN note); the stagger TRIGGER is now DERIVED via the gauge
   *  model (specials map to damage record 2, reactionFlags 1 — no forced stagger). */
  HITSTUN: 18,
} as const;

export const STAGGER = {
  /**
   * DERIVED — the three post-hit victim windows are all set to the same 60.0-frame constant
   * (FLOAT_80436fac) by resolve_hitbox_target_effects_and_damage @0x8002e2a8
   * (chunk_0003.c:7995-8010) on every hit, and decremented once per frame while the victim is
   * NOT in a hit reaction (chunk_0006.c:7982-8011; frozen while 0x5e0 bit 0x1000000 is set).
   * On expiry:
   *   +0x684 -> balance gauge refills to max          (chunk_0006.c:7988)
   *   +0x688 -> down gauge resets to base (+50%/level via zz_003d3e8_, chunk_0004.c:6866-6876)
   *   +0x68c -> combo accumulator (+0x6c8, 0-99) and combo rank byte (+0x6ca) reset
   *             (chunk_0006.c:8009-8010)
   */
  BALANCE_REFILL_DELAY: 60,
  DOWN_RESET_DELAY: 60,
  COMBO_WINDOW: 60,
  /**
   * DERIVED — entering a balance-break stagger (flag bits 0x6fd |= 0xa6) grants the victim
   * 60.0 i-frames: zz_005c290_ writes FLOAT_80437448 (60.0) to +0x720 on entry
   * (chunk_0007.c:3985-4050) and sets "in hit reaction" (0x5e0 bit 0x1000000), which freezes
   * the three windows above for the reaction's duration.
   */
  STAGGER_IFRAMES: 60,
} as const;

export const DAMAGE = {
  /**
   * Legacy direct-helper fallback only. Runtime attacker-context hits use the decoded formula in
   * damageFormula.ts; this percentage model remains for tests/tools that call applyHit without a
   * source attacker context.
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
   * Runtime formula applies the original 0.25x multiplier directly in damageFormula.ts.
   * Kept as a divisor for legacy direct-helper fallback continuity.
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
  /** Spawn (deploy) controllable lock: 20f descent + 1f phase setup + 15f pose. DERIVED from
   *  behavior-notes.md (af), table slots 0-2 at 0x8005be08/0x8005bec8/0x8005bf6c. */
  SPAWN_DURATION: 36,
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
