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
//   - Lock-on target state is source-shaped in combat.ts/types.ts. The old manual
//     LOCK.RANGE/CONE view-cone heuristic was removed after resolving zz_006b450_,
//     FUN_8006b850/FUN_8006ba60, and the actor +0x502/+0x508/+0x73d/+0x73e state.
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

/**
 * "landing" MovementContext window after `onLand` (movement.ts), frames. TUNED — a port-side
 * capture constant, not a ROM value (see ATK-004 / attack-mechanics-findings.md mechanics
 * D-K: the movement-context enum itself is WIKI_TAXONOMY_ONLY, so there is no ROM landing-
 * window constant to derive this from). Kept small so "landing" reads as a brief edge window
 * right after touchdown rather than a long recovery state.
 */
export const MOVEMENT_CONTEXT_LANDING_WINDOW_FRAMES = 6;

export const MOVE = {
  /**
   * FALLBACK ground speed formula (units/frame) = BASE + speed_stat * PER_STAT — used ONLY
   * for ids without a pl####data.bin page (synthetic test borgs). Real borgs get their
   * DERIVED run speed from movementData.ts groundRunSpeedForBorgId (page+0x2c RAW).
   *
   * RAW-SCALE MIGRATION (2026-07-04, research/decomp/movement-hit-decode-2026-07-04.md):
   * the full run-speed chain is now DERIVED — run start SNAPS actor+0x44 to page+0x2c
   * (zz_005f578_ chunk_0007.c:5973) and worldDelta = +0x44 × timescale(+0x5f4) ×
   * tierVelScale(+0x5f8), both ×1.0 at baseline — so ROM world units are 1:1 with the
   * port's stage geometry and G RED runs 12.0 u/f RAW. The old 22.0 backward-walk trace
   * anchor could not be reconciled with any code path (no ×1.833 exists) and is retired
   * as a mis-sample. Fallback constants rescaled so a speed-6 synthetic hits 12.0.
   */
  GROUND_BASE: 2.4,
  GROUND_PER_STAT: 1.6,
  /** Flight horizontal speed is a touch faster than ground. TUNED (ROM flight = gravity
   *  coeff 0, no distinct h-speed constant found). */
  FLY_MULT: 1.15,
  /**
   * Acceleration toward target velocity (units/frame^2). TUNED stand-in for the ROM's
   * run-start SNAP (speed jumps straight to page+0x2c) — sized to reach a 12 u/f run in
   * a few frames so it reads as the snap.
   */
  ACCEL: 2.6,
  /** Deceleration when no input (units/frame^2). TUNED stand-in for the ROM's ×0.98/frame
   *  idle decay (chunk_0008.c:383-385), rescaled with the raw migration. */
  DECEL: 3.5,
  /** Yaw turn rate toward facing target (radians/frame). */
  TURN_RATE: 0.35,
} as const;

export const JUMP = {
  /**
   * FALLBACK jump takeoff velocity (units/frame) for ids without a data page. DERIVED raw
   * scale (2026-07-04): the launch state writes +0x48 = page[+0x48] (FUN_80061f50
   * chunk_0008.c:329); G RED's page value is 15.0 and world units are 1:1 (see MOVE).
   * Real borgs read their own page via movementData.ts jumpVelocityForBorgId.
   */
  VELOCITY: 15.0,
  /** FALLBACK fall gravity (units/frame^2). DERIVED raw scale: the airborne fall slot is
   *  page+0x6c (G RED -1.0); real borgs read their own via fallGravityForBorgId. */
  GRAVITY: 1.0,
  /** Terminal fall speed (units/frame). DERIVED: global FLOAT_804375f0 = -35.0 (airborne
   *  vertical clamp, chunk_0008.c:3823-3861) — raw scale. */
  MAX_FALL: 35.0,
  /** Hold-jump-in-air boost flight: upward thrust while held (units/frame^2). Flyers only.
   *  TUNED (ROM flight = gravity-coeff-0, no thrust constant exists); rescaled with the
   *  raw migration to out-pull typical fall gravity. */
  BOOST_THRUST: 1.3,
  /** Max upward speed under boost flight (units/frame). TUNED, rescaled with the migration. */
  BOOST_MAX_RISE: 8.0,
  /** Boost flight drains over time; thrust is gated by remaining fuel (frames of boost). */
  BOOST_FUEL_FRAMES: 90,
  /** Ground Y level (RAM trace: ~10 when grounded). DERIVED. */
  GROUND_Y: 10,
} as const;

export const DASH = {
  /**
   * FALLBACK dash speed (units/frame) for synthetic borgs without a data page. The 2026-07-01
   * "no dash state exists in the ROM" audit is REFUTED (2026-07-04): FUN_80061560
   * (chunk_0007.c:7231-7238) and FUN_80063230 (chunk_0008.c:1220-1223) ARE dash states —
   * they seed speed/accel/v-speed/duration verbatim from the data page +0x58/+0x5c/+0x60/+0x64
   * (movementData.ts dashPhysicsForBorgId, RAW DERIVED: G RED 30 u/f ×30f, Acceleration
   * Ninja 40 u/f ×60f). Real borgs never hit these TUNED fallback values.
   */
  SPEED: 20.0,
  /** FALLBACK dash duration (frames) — see SPEED note; real borgs use page+0x64. */
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
  /** RETIRED as the applied magnitude (2026-07-04): applyHit now derives knockback from the
   *  hit record's DERIVED strength byte via gauges.ts knockbackVelocityForRecord × the
   *  KNOCKBACK.PORT_SCALE anchor below. Kept only as the historical tuned melee base that
   *  PORT_SCALE is anchored to (5 u/f at melee strength 6). */
  KNOCKBACK: 5,
  /**
   * Contextual-B melee ENGAGE window (XZ units): the SELECTION distance within which a B
   * press resolves to the battle-mode melee (combat.ts resolveBActionOrder /
   * targetWithinMeleeEngage) — the DAMAGE check keeps the per-borg meleeDef.range untouched.
   * The app-layer reticle (presentation.ts focusHasMeleeRangeTarget) should consume this same
   * window so the yellow->red cursor flip and the sim's melee selection agree.
   * TUNED — do NOT promote to DERIVED: the ROM threshold FLOAT_8043762c that flips the cursor
   * red and selects battle-mode melee is identified but UNDUMPED/untraced (behavior-notes.md
   * (ai)/(av), T1-blocked). The MECHANISM (close = battle attack, with a HUD-observable
   * yellow->red threshold) is CONFIRMED_MANUAL per behavior-notes.md (ao) (official NA
   * instruction manual); only the numeric value here is tuned. Sized so the lunge below can
   * carry the attacker from the selection edge into meleeDef.range (~60-86) within a swing's
   * startup+active frames, and to cover the old AI whiff band (64-110).
   */
  ENGAGE_RANGE: 180,
  /**
   * Vertical tolerance of the ENGAGE window (units). TUNED — intentionally wider than the
   * per-hit Y_TOLERANCE (50) so slightly-airborne/jumping targets still flip the contextual B
   * to melee (the old 50 blocked vertical engagements outright); the damage check keeps the
   * per-borg meleeDef.yTolerance.
   */
  ENGAGE_Y_TOLERANCE: 100,
  /**
   * Melee lunge (approach dash) speed, units/frame, applied by combat.ts's lunge drive during
   * a swing's startup+active frames (cooldowns["meleeLunge"] window). TUNED — the ROM carries
   * the lunge in the attack_lunge_s* animation banks' bone-0 ROOT MOTION (rootZ spans
   * ~100-389 units, documented in apps/game/src/main.ts PREFERRED_LABELS comments), which the
   * renderer strips (main.ts buildClip zeroes bone-0 XZ for all clips), so the sim drives the
   * translation instead; FLOAT_8043762c (the engage threshold that would pin the ROM's
   * lunge-trigger distance) remains T1-blocked (behavior-notes.md (ai)/(av)). Note the
   * EFFECTIVE per-frame advance is LUNGE_SPEED - MOVE.DECEL (~29.6) because stepMovement
   * decays combat-state velocity toward 0 before integrating each frame.
   */
  LUNGE_SPEED: 36,
  /**
   * Max distance a single swing's lunge may cover (units), enforced by clamping the lunge
   * window to floor(LUNGE_MAX_DIST / LUNGE_SPEED) frames. TUNED, asset-anchored: the exported
   * attack_lunge_s* rootZ spans run ~100-389 units (apps/game/src/main.ts PREFERRED_LABELS
   * comments), so a full-length lunge of ~300 sits inside the authored envelope.
   */
  LUNGE_MAX_DIST: 300,
  /**
   * The lunge stops driving once within this fraction of meleeDef.range of the target, so
   * the attacker closes into reach without overrunning through the target. TUNED.
   */
  LUNGE_STOP_FRACTION: 0.75,
} as const;

export const SHOT = {
  /** Projectile speed (units/frame). TUNED — the ROM's per-muzzle speed comes from the weapon-
   *  param table DAT_802d39dc scaled by DAT_802d39c0 (spawn zz_006ee14_ 0x8006ee14,
   *  chunk_0009.c:3769 + init FUN_8006f11c chunk_0009.c:3907); both tables are identified but
   *  UNDUMPED, and raw ROM speeds would not transfer anyway across the port's ~4x world rescale
   *  (behavior-notes.md section (bc)). */
  SPEED: 22,
  /** Projectile lifetime (frames). DERIVED_ROM — projectile init FUN_8006f11c seeds the life
   *  counter to 600 frames (chunk_0009.c:3907). Frame counts transfer 1:1 across the port's
   *  ~4x world rescale (behavior-notes.md (bc)), unlike speeds/gravity. Raised from the old
   *  TUNED 40 together with the owner-liveness despawn (zz_00840b8_, chunk_0012.c:3216) and
   *  the terrain/wall impact despawn (zz_0083244_/zz_0083714_ via zz_006f268_,
   *  chunk_0009.c:3956) so long-lived shots still die on geometry/bounds/owner death instead
   *  of flooding the arena. NOTE: per-borg shot lifetimes in data/actionProfiles.json are
   *  separate TUNED values owned by that dataset; this constant is the default/fallback. */
  LIFETIME: 600,
  /** Homing turn rate toward lockTarget (radians/frame); 0 = straight. TUNED magnitude — the
   *  MECHANISM (per-frame angle-clamped 3D steer) is the ROM's FUN_8006c1c8
   *  (chunk_0009.c:1947); the per-projectile clamp value comes from undumped params. */
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
  /** RETIRED as the applied magnitude (2026-07-04) — see MELEE.KNOCKBACK note; applyHit now
   *  derives shot knockback from record 0's strength byte (4 -> 40 ROM u/f) × PORT_SCALE
   *  ≈ 3.6 u/f, close to this old tuned 3. Kept for historical reference only. */
  KNOCKBACK: 3,
} as const;

/**
 * Knockback magnitude model (behavior-notes (bc), T9 resolved statically): the ROM's knockback
 * speed is STRENGTH-INDEXED, not flat — the hit record's +0x0d severity byte is copied to the
 * victim's actor+0x702 and indexes DAT_802d3664[s]=(s+1)*8 (velocity, FUN_8005ed38; see
 * gauges.ts KNOCKBACK_STRENGTH_TABLE / knockbackVelocityForRecord). applyHit applies
 *   magnitude = knockbackVelocityForRecord(record) × PORT_SCALE × perMoveMultiplier.
 */
export const KNOCKBACK = {
  /**
   * DERIVED = 1.0 since the 2026-07-04 raw-scale migration (research/decomp/
   * movement-hit-decode-2026-07-04.md): the port's velocities are ROM world units 1:1, so
   * the strength-indexed table velocities (melee 56 > shot 40 > charge/special 24 u/f)
   * apply RAW. The port's MOVE.DECEL stands in for the ROM's knockdown decel model
   * (h-decel -0.10 / denom 20.0, FLOAT_804374cc/_490 — unported); tune decay THERE, never
   * this scale, and do not add per-record tuning here.
   */
  PORT_SCALE: 1.0,
  /** TUNED vertical pop applied ONLY on forced knockdowns (combo finishers/launch hits) so
   *  the launch reads. Standard knockback vertical is DERIVED ZERO (FLOAT_80437444 = 0.0,
   *  falling under gravity — behavior-notes (bc)); the real per-borg knockdown launch model
   *  (+0x58 h-speed / +0x5c accel, data/movementPhysics.json) is the follow-up consumer.
   *  Kept small: a large pop under raw scale launched victims over stage wall collision. */
  KNOCKDOWN_POP: 6,
} as const;

/**
 * Projectile homing (fx-cluster-2026-07-03, research/decomp/data/identified-functions.json).
 * The ROM's homing trio:
 *   - FUN_8006c334 (chunk_0009.c:1995), called from the spawn path at chunk_0009.c:3841 —
 *     spawn-time aim-cone gate: the homing lock is granted ONLY when the locked target lies
 *     inside a cone around the projectile's initial flight direction; otherwise it flies
 *     straight.
 *   - FUN_8006c1c8 (chunk_0009.c:1947) — per-frame angle-clamped 3D axis-angle steer of the
 *     FULL velocity vector (not yaw-only).
 *   - zz_006c440_ (chunk_0009.c:2033) — steer + advance by normalized(vel) * speed (+0x44).
 */
export const HOMING = {
  /** Aim-cone half-angle (radians) for the spawn-time lock gate (FUN_8006c334). The ROM
   *  compares against FLOAT_8043768c — address identified, value UNDUMPED — so this stays
   *  TUNED (30 degrees) until that float is dumped. */
  AIM_CONE_HALF_ANGLE_RAD: Math.PI / 6,
  /** Speed floor below which the per-frame steer is skipped entirely. TUNED epsilon — replaces
   *  the old `|| SHOT.SPEED` fallback that silently re-accelerated stalled projectiles with no
   *  ROM basis (the ROM keeps speed in a separate +0x44 field and never re-seeds it in the
   *  steer, zz_006c440_ chunk_0009.c:2033). */
  MIN_STEER_SPEED: 1e-4,
} as const;

/**
 * Shared sim/render muzzle offset (world units, relative to the borg origin along its facing).
 * ONE constant used by BOTH combat.ts spawnProjectile (sim spawn point) and the renderer's
 * muzzle flash so the projectile appears where the flash renders (they previously disagreed:
 * sim forward 30 / up 20 vs renderer forward 46 / up 86).
 *
 * TUNED — the ROM's real muzzle world position comes from the per-muzzle weapon-param table
 * DAT_802d39dc read by the spawn function zz_006ee14_ (0x8006ee14, chunk_0009.c:3769); the
 * table is identified but its values are UNDUMPED, so these numbers remain tuned defaults.
 * Per-borg TUNED overrides in data/actionProfiles.json (muzzleForwardOffset/muzzleYOffset)
 * take precedence in the sim; renderers should prefer the projectile's actual spawn position
 * (or the borg's shot def) when available and fall back to this constant.
 */
export const MUZZLE_OFFSET = {
  forward: 30,
  up: 20,
} as const;

export const AMMO = {
  /**
   * Per-frame ammo-refill rate (ammo units/frame), consumed by stepAmmoRefill (combat.ts,
   * ATK-009) for gradual-type weapon cells and as the "how fast does the timer run down"
   * scale for all-at-once cells. TUNED — the ROM's real rate float lives at actor+0x768
   * (`zz_006dcc0_`, chunk_0009.c:2909-2973), but its INIT SITE is unresolved and the offset
   * has a conflicting second reader (a status/scale-related float read at the same offset by
   * a separate corpus pass) — see research/decomp/attack-mechanics-open-questions.md Q7
   * ("What is actor+0x768 really — ammo refill rate, scale-related float, or both consumers
   * misread?"). Until Q7 resolves which struct/site is authoritative, this stays a named
   * TUNED constant rather than a guessed DERIVED value.
   *
   * Default derivation: chosen so a default borg's effective shots-per-minute stays within
   * the port's PRE-ATK-009 feel. The old model fired SHOT.AMMO_MAX (6) shots at
   * SHOT.FIRE_COOLDOWN (12f) spacing, then waited SHOT.RELOAD_FRAMES (60f) for an instant
   * full refill — a full magazine (6 ammo) took 60 frames to come back. Gradual refill grants
   * fractionally every frame (see stepAmmoRefill), so setting the rate to
   * AMMO_MAX / RELOAD_FRAMES = 6/60 = 0.1 ammo/frame reproduces the same "empty-to-full in
   * ~60 frames" envelope for a default-shaped borg, keeping shots-per-minute within the
   * pre-change baseline (ATK-002).
   */
  REFILL_RATE_PER_FRAME: SHOT.AMMO_MAX / SHOT.RELOAD_FRAMES,
  /**
   * All-at-once cells (refillType <= 0) don't grant fractionally; they wait out a timer then
   * jump straight to max (chunk_0009.c:2909-2973, sVar4 < 1 branch). Per-borg refillParam
   * (weapon aux +0x792, row source borg-hp-stat-rows-802f2988.json u16[4]/u16[8]) seeds that
   * timer. A player-guide cross-check (behavior-notes.md section (am): G RED refillParam 180,
   * Flame/Cyber Death Dragon 300, Death Head 180) found refillParam values of 180/300 lining
   * up suspiciously well with round 3s/5s at 60fps — the port treats refillParam as a direct
   * frame count on that strength, but the interpretation is STRONG-BUT-UNVERIFIED (data-level
   * inference from (am), not a decoded conversion formula) rather than DERIVED. This constant
   * is only the FALLBACK frame count for borgs without a usable refillParam (falls back to
   * SHOT.RELOAD_FRAMES so they still reload in roughly the pre-ATK-009 envelope).
   */
  DEFAULT_ALL_AT_ONCE_TIMER_FRAMES: SHOT.RELOAD_FRAMES,
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
  // TUNED-visual (2026-07-04 playtest feedback): a full charge (G Buster class) previously
  // fired a bolt visually indistinguishable from a plain shot (radius 20→32 at the same
  // "energy" family). The renderer scales bolt footprint by hitRadius, so the tier-2 radius
  // is sized to read as the big charged beam; speed up so the release feels like a cannon.
  // Real per-move charged hitboxes are hit.bin kinds not yet mapped to the charge command —
  // these stay TUNED multipliers over the borg's own base radius until that mapping lands.
  TIER1_SPEED_MULT: 1.3,
  TIER2_SPEED_MULT: 1.6,
  TIER1_RADIUS_MULT: 1.8,
  TIER2_RADIUS_MULT: 3.2,
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
  /** RETIRED as the applied magnitude (2026-07-04) — applyHit derives special knockback from
   *  record 2's strength byte (2 -> 24 ROM u/f) × KNOCKBACK.PORT_SCALE ≈ 2.1 u/f. The ROM says
   *  specials push LESS than melee/shots (they pressure via down-gauge instead); the old tuned
   *  7 overshot. Kept for historical reference only. */
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

export const AI = {
  /**
   * AI desired engage distance for melee borgs (XZ units). TUNED — audited 2026-07-01 (s4s):
   * no packages/ai implementation exists yet (packages/ai/src/index.ts is an empty stub), and no
   * isolated "CPU decision" function was found in the corpus — research/decomp/index/
   * cpu-ai-evidence.md independently reached the same conclusion (CPU and player-controlled
   * actors share the same low-level dispatch, no separate AI brain function identified).
   */
  MELEE_RANGE: 50,
  /**
   * NOTE (melee workstream): ai.ts no longer reads MELEE_RANGE — melee/mixed AI now uses the
   * borg's actual per-borg meleeDef.range for its desired distance and the shared
   * MELEE.ENGAGE_RANGE window (combat.ts meleeEngageRangeFor) for its attack gate, fixing the
   * 64-110 whiff band the flat 50+RANGE_SLACK window produced. Kept (still TUNED, still NOT
   * promotable to DERIVED — FLOAT_8043762c is T1-blocked) for any legacy/debug readers.
   */
  /** AI desired engage distance for ranged borgs. TUNED — see MELEE_RANGE note. */
  RANGED_RANGE: 600,
  /** Slack around the desired range before AI stops advancing. TUNED — see MELEE_RANGE note. */
  RANGE_SLACK: 60,
  /** AI re-evaluates its target every N frames. TUNED — see MELEE_RANGE note. */
  RETARGET_FRAMES: 30,
  /**
   * RAW-SCALE RETUNE (2026-07-04 movement migration, research/decomp/
   * movement-hit-decode-2026-07-04.md §1): TUNED port-ism, NOT ROM-derived — the ROM CPU
   * brain (zz_001c9d0_) is unread, so every field below is a port-side pacing choice, not a
   * decoded decision function.
   *
   * Ground speeds moved to per-borg DERIVED raw values (G RED 12 u/f) from the old
   * 22 u/f trace anchor (~0.55x as fast). Walking alone from stage-scale spawn separations
   * (several thousand XZ units on the larger Challenge stages) now takes far longer, so the
   * CPU dashes to close ground when it is well outside its engage range. Expressed as a
   * multiple of the borg's OWN groundRunSpeedForBorgId (movementData.ts) rather than a flat
   * distance so faster/slower borgs get a proportionally-scaled trigger instead of a
   * one-size-fits-all threshold tuned for the retired 22 u/f world.
   */
  DASH_APPROACH_SPEED_MULT: 30,
  /**
   * Kite/hold-range slack, expressed as a fraction of the borg's own ground run speed
   * (units/frame) rather than the flat absolute RANGE_SLACK (60, sized for the old 22 u/f
   * world). At the DERIVED raw scale (G RED 12 u/f) this keeps the dead-band roughly
   * proportional to how far the borg can drift in a single retarget window instead of being
   * a relatively huge, slow-to-cross band for a 12 u/f mover. TUNED port-ism.
   */
  KITE_SLACK_SPEED_MULT: 5,
  /**
   * Attack decision pacing: after a swing/special recovers, the CPU waits a per-borg
   * staggered reaction delay before pressing again, instead of holding the attack button
   * every single frame while in range. TUNED port-ism — fixes a mutual-invincibility
   * phase-lock: two symmetric CPUs (matched range/timing) that both spam attack the instant
   * they're in range enter their swings on the SAME frame, and the melee-active i-frame
   * refresh (STATE.MELEE_IFRAME_REFRESH_PER_FRAME, constants.ts) keeps each one invincible
   * for the other's entire active window every cycle — verified live via
   * scripts/selfcheck-challenge-stages.mjs (st02/st04/st08/st0b/st0c all showed two CPUs
   * locked at ~52 units, alternating attack/special forever with hp never moving). Staggering
   * the reaction delay per-uid desynchronizes the swing cycles so each side's active window
   * eventually lands on the other's non-invincible frames.
   */
  ATTACK_REACTION_MIN_FRAMES: 4,
  ATTACK_REACTION_JITTER_FRAMES: 26,
} as const;

/** Default stage half-extent if a BattleConfig omits bounds (XZ units from origin). */
export const DEFAULT_BOUNDS = { x: 4000, z: 4000 } as const;

export const MASH = {
  /**
   * BLOCKED-until-Q9 (ATK-017): the counter's downstream CONSUMER is UNKNOWN — attack-active
   * handler slot 23 (`FUN_8005d494`) advances a phase once `4 < +0x550` or `+0x552 != 0`
   * (chunk_0007.c:4809-4816, corpus read, audit), but nothing in the corpus was found to gate
   * on the counter besides that phase advance itself, and what that phase transition actually
   * DOES in gameplay terms is still open (research/decomp/attack-mechanics-open-questions.md
   * Q9). Also (behavior-notes.md (an) §5): freeze status duration is guide-documented to
   * SHORTEN with button/stick mashing — a second, still-unconfirmed candidate consumer for
   * this same counter shape. Stays false (counting-only, no gameplay effect) until Q9
   * resolves which consumer (if any) this feeds.
   */
  ENABLED: false,
  /**
   * DERIVED — chunk_0007.c:4809-4816: the phase-advance condition is `4 < +0x550`, i.e. the
   * counter caps its gameplay-relevant range at 5 distinct values (0-4) before the phase
   * advances; ported as a hard clamp at 4 (count never exceeds 4, matching "more than 4"
   * being the trigger threshold rather than continuing to climb unbounded).
   */
  PRESS_CAP: 4,
} as const;

export const HEAL = {
  /**
   * ENABLED (ATK-019, vampire lifesteal) — the full path is now traced end to end
   * (behavior-notes.md (ay)). For ids 0x702/0x70a (VAMPIRE KNIGHT pl0702, VLAD pl070a):
   *  - STEAL: on every hit the vampire deals, the ROM banks `damage/2` into a per-slot
   *    accumulator DAT_803b0638[slot] (writer FOUND at chunk_0003.c:7982-7986), then drains
   *    that bank into its own HP capped at max (apply chunk_0003.c:6318-6323). Ported as an
   *    immediate heal-on-hit of floor(dmg/2) (equivalent in sum to bank-then-apply).
   *  - BLEED: a passive self-drain of 1 HP every 30 frames, floored at 1 HP (never self-kills)
   *    — drain loop FOUND at chunk_0006.c:7900-7912 (`if 1 < HP: HP -= 1` every 0x1e frames).
   *    1 HP / 30f = 2 HP/sec at 60fps, matching the guide's "~2-3 HP/sec"
   *    (research/decomp/data/guide-anchors-movelist.json lifestealVampire).
   * The one TUNED element is the bleed GATE: the ROM keys it on state bytes +0x18==1/+0x19==2
   * (an active-normal state) and the steal on a +0x83==0 byte; lacking a proven mapping for
   * those, the port applies steal on any hit the vampire lands and bleed whenever it is alive
   * and out of death/spawn (the guide frames both as constant passive behavior).
   */
  VAMPIRE_ENABLED: true,
  /** Vampire steal divisor: banked HP = floor(damageDealt / this) (ROM `dmg/2`, (ay)). */
  VAMPIRE_STEAL_DIVISOR: 2,
  /** Vampire passive-bleed cadence: 1 HP lost every N frames, floored at 1 HP (ROM 0x1e, (ay)). */
  VAMPIRE_BLEED_INTERVAL_FRAMES: 30,
  /**
   * BLOCKED (ATK-019, nurse heal). Nurse healing is a SEPARATE mechanism from the vampire path
   * above (corrected by (an) §2) — an X-attack that dashes to a target and heals a FIXED
   * amount. No ROM code path has been isolated for it at all (OBSERVED_GUIDE only — see
   * NURSE_HEAL_HP below and research/decomp/data/guide-anchors-movelist.json nurseHeals).
   * Stays false until a real trace lands.
   */
  NURSE_ENABLED: false,
  /**
   * OBSERVED_GUIDE (an) §2 / guide-anchors-movelist.json `nurseHeals` — fixed X-attack heal
   * amounts, data only (no active behavior while NURSE_ENABLED is false). Keys are the nurse
   * borg ids from HEAL_NURSE_BORG_IDS below.
   */
  NURSE_HEAL_HP: {
    pl0906: 37, // DEATH BORG THETA
    pl0900: 50, // ANGEL NURSE
    pl0908: 100, // ANGEL RESCUE
    // pl090d (NAO) has no fixed guide amount — "heals ally or enemy; blocked while target's
    // heal animation runs" (an §2) — intentionally absent from this data map.
  },
} as const;

/**
 * Vampire-lifesteal borg ids (family 7 = Nurse-adjacent variants per the corpus id check,
 * behavior-notes.md (an) §1/§2 — roster-validated via the 20th-Force glitch-code cross-check:
 * Vampire Knight {2,9,10,11} = 0x702 = pl0702 exact match, Vlad {2,4,9,10,11} = 0x70a = pl070a
 * exact match against packages/assets/data/borgs.json).
 */
export const HEAL_VAMPIRE_BORG_IDS = ["pl0702", "pl070a"] as const;

/**
 * Nurse-heal borg ids (0x9xx / "family 09" per (an) §2's id-prefix grouping). Death Borg
 * Theta's roster id was looked up by NAME per the ticket (expected family-09 variant) —
 * packages/assets/data/borgs.json confirms pl0906's NAME is an EXACT match ("DEATH BORG
 * THETA"), so no name-mismatch STOP was triggered. NOTE: pl0906's roster `tribe` field is
 * "Death Borg", NOT "Nurse Borg" like its 09xx siblings (pl0900/pl0908/pl090d are all tribe
 * "Nurse Borg") — a non-blocking discrepancy between (an)'s "family 09 = nurse family"
 * id-prefix framing and the roster's actual tribe grouping; logged in NOTES-ATK-019.md
 * (generated by healing.selftest.ts) rather than treated as the ticket's name-mismatch stop
 * condition, since the name itself resolved correctly.
 */
export const HEAL_NURSE_BORG_IDS = ["pl0906", "pl0900", "pl0908", "pl090d"] as const;

export const CONTACT_DAMAGE = {
  /**
   * WIKI_TAXONOMY_ONLY (ATK-006) — no ROM/asset proof of a contact-damage code path has been
   * found (findings mechanic L; the state handlers were read in full in behavior-notes.md (u)
   * with no movement-triggered damage side effects). Upgraded to OBSERVED_BEHAVIOR-adjacent
   * status by (am)/(an): speedrunners document big borgs (the plasma dragon family) stepping
   * on allies and granting them hit-invincibility (contact is a real hit that arms the i-frame
   * machinery), and the guide move-lists document contact damage as an explicit per-borg
   * "Special" move — dragon-family stepping 22 (Flame/Blizzard/Plasma Dragon 44), Acceleration
   * Ninja air-dash/jump body contact 44 with NO normal melee at all (research/decomp/data/
   * guide-anchors-movelist.json contactDamage; behavior-notes.md (an) §5). Contact damage is
   * therefore AUTHORED PER-BORG DATA (a move/hitbox attached to specific borgs), not an
   * engine-wide "any overlap deals damage" rule — so the eventual enable path is a per-borg
   * data table (which borg ids carry a contact hitbox, and its damage/radius), not a single
   * global constant here. See open-questions Q12 and the T2 contact-script trace extension.
   * Stays false until that per-borg trace lands; this scaffold never invents damage numbers,
   * radii, or cooldowns for the general case.
   */
  ENABLED: false,
} as const;

export const BURST = {
  /**
   * DERIVED — `FUN_80069814` (chunk_0009.c:104-115): the Y-family input bit in the
   * transformed input word (+0x5d4) sets object+0x6fb = 6 on the press edge. Ported as the
   * exact 6-frame arm window (press edge -> burstArmFrames = 6, decrement 1/frame, re-press
   * re-arms), mirroring `zz_005b2b8_` (chunk_0007.c:3354-3494) consuming +0x6fb while nonzero.
   * NOTE (behavior-notes.md (aj)): +0x6fb is ALSO read/decremented in the fusion per-slot loop
   * (chunk_0007.c:3473-3490) where its expiry drives the burst/fusion end path — the "6-frame
   * arm window" reading and that fusion-timer reading may be the same field seen in two
   * contexts, not two separate constants. Needs trace T3 to reconcile; do not assume either
   * reading supersedes the other yet.
   * UPDATE (behavior-notes.md (ao), official NA instruction manual, CONFIRMED_MANUAL tier —
   * still not numeric ROM truth): the manual describes simultaneous-press co-op bursts ("press
   * the button at the same time for simultaneous power bursts"), which gives 6 a coherent
   * reading as the SIMULTANEITY tolerance window for a partner's paired Y press, not just a
   * solo activation buffer. Reconcile the exact semantics (whose window, how pairing is judged)
   * in trace T3 before ATK-012 depends on either interpretation.
   */
  ARM_WINDOW_FRAMES: 6,
  /**
   * ENABLED (ATK-012 core slice). Per (ao) (official NA instruction manual,
   * CONFIRMED_MANUAL): activation's real precondition is "press when the burst gauge is at
   * max" — a full Power Burst meter, officially named in the manual and corroborated by
   * StrategyWiki's interface page.
   * UPDATE (Q4 RESOLVED 2026-07-03 — research/decomp/attack-mechanics-open-questions.md Q4
   * lines 51-79, attack-mechanics-findings.md §S): the meter is LOCATED (per-PLAYER, player
   * struct +i*0x3c: +0x126 clamped u16 / +0x124 max / +0x12a unclamped / +0x103 charged) and
   * its fill model is PORTED (METER_MAX / FILL_PER_HIT below; state in
   * BattleState.burstMeterByPlayer, fill in combat.ts applyHit, charged sweep in battle.ts).
   * UPDATE (Q5 RESOLVED at value level 2026-07-04): charged Y activation, same-team paired
   * activation, -5/frame drain, and x1.5 movement speed are wired. Remaining gaps: the exact
   * ROM code path carrying the speed multiplier and the per-action extra burst meter costs.
   */
  ENABLED: true,
  /**
   * DERIVED — Q4 RESOLVED (2026-07-03): the per-player burst meter's max, player struct
   * +0x124 = 3000 (save-state diff scripts/diff-actor-block.mjs; research/decomp/
   * attack-mechanics-open-questions.md Q4 lines 53-58, attack-mechanics-findings.md §S).
   * The clamped meter +0x126 (u16) caps here while the +0x12a accumulator keeps counting
   * (live: 2929 -> 3079 -> 3129).
   */
  METER_MAX: 3000,
  /**
   * DERIVED — T3 live traces (2026-07-03, research/decomp/attack-mechanics-open-questions.md
   * Q4 lines 59-74): the meter fills +50 per hit CONNECTION, ATTACKER only, flat/damage-
   * independent — B shot 16 HP dmg -> +50 (reproduced 3x); Plasma Knuckle melee 25 HP dmg ->
   * +50; one penetrating beam through a dead borg husk -> +150 = 3 hit connections x 50 (dead
   * borgs still register hits). Victim side: NONE of the other three players' meters moved on
   * any hit taken — taking damage does NOT fill the victim's meter.
   * CAVEAT (mandatory, Q4): 50 is confirmed for two different G Red moves (shot + melee), but
   * a per-move or per-damage-record override elsewhere cannot be fully excluded yet. NOTE the
   * damage-record field `forceGaugeCurveIndex` is NOT this — that keys a damage multiplier to
   * the TEAM GF-energy gauge (+0x114), a separate gauge; the damage pipeline
   * (chunk_0004.c:6672-6828) never writes +0x126.
   */
  FILL_PER_HIT: 50,
  /**
   * DERIVED — Q5/duration RESOLVED at value level (live T3 trace 2026-07-03/04,
   * T3-q5-speed-final.jsonl): on paired Y activation (versus needs BOTH teammates armed —
   * zz_005b2b8_ requires >1 candidate unless player flag +0xf5 == 1) the burst timer pair
   * +0x10c/+0x10e is set to 600 AND the meter itself drains DRAIN_PER_FRAME per frame from
   * 3000 (343 measured -5 frames; 3000/5 = the same 600-frame/10s ceiling). The burst ends
   * when the meter empties — measured 437 frames with movement, because ACTIONS SPEND EXTRA
   * meter: discrete -45/-50/-60 events (dash-shaped) and two large -350/-470 events, with the
   * full drain ledger summing to exactly 3000. Per-action cost mapping is TUNED/unmapped —
   * needs a controlled per-action trace before porting costs individually.
   */
  DRAIN_PER_FRAME: 5,
  /**
   * DERIVED — Q5 RESOLVED at value level (same trace): median moving speed during burst =
   * 33.0 world-units/frame vs the proven 22.0 u/f ground-walk baseline (behavior-notes (ac))
   * = exactly x1.5. The CODE PATH carrying the multiplier is still unlocated (no +0x6fc-gated
   * speed modifier exists in the read corpus; moveMult/param-tier candidate fields did NOT
   * change at activation), so this is a measured value, not a code-anchored one.
   */
  SPEED_MULTIPLIER: 1.5,
} as const;

/**
 * Hit-inflicted status effects — DERIVED, research/decomp/status-effects-decode-2026-07-04.md.
 * All writers live in resolve_hitbox_target_effects_and_damage @0x8002e2a8; magnitudes/timers
 * below are the exact ROM constants (chunk_0003.c:7621-8157), not tuned anchors.
 */
export const HIT_STATUS = {
  /** Discrete slow/haste-on-hit timer seed (ROM +0x710/+0x712 s16), chunk_0003.c:8103/8141. */
  DISCRETE_TIMER_FRAMES: 900,
  /** Discrete slow/haste-on-hit level (ROM +0x70e/+0x70f), both always write level 2. */
  DISCRETE_LEVEL: 2,
  /** Contact-haste AURA fixed level (ROM +0x70d, flagsB&0x0800), chunk_0003.c:7681. */
  AURA_HASTE_LEVEL: 1,
  /** Grow/shrink accumulator clamp (the `_63` tier-delta path's ±0x3f range). */
  SIZE_TIER_CLAMP: 0x3f,
  /** Grow/shrink 900f auto-revert timer (ROM +0x750, chunk_0008.c:4475). */
  SIZE_TIER_TIMER_FRAMES: 900,
  /**
   * Diver borg ids hard-coded EXEMPT from receiving the contact-slow aura they themselves
   * project (chunk_0003.c:7665-7669 id-compare): pl0805 JELLY DIVER (lvl1, ×0.7), pl080e
   * JACK (lvl2, ×0.4), pl080d TAR DIVER (lvl3, ×0.2).
   */
  SLOW_AURA_EXEMPT_BORG_IDS: ["pl0805", "pl080d", "pl080e"] as readonly string[],
  /** Shared immunity bit (immunityB) that blocks BOTH aura types at once (chunk_0003.c:7654). */
  AURA_SHARED_IMMUNITY_BIT: 0x400,
} as const;

/**
 * STAR HERO (pl0804) / PLANET HERO (pl080c) X-special ramming-dash self-buff — DERIVED,
 * status-effects-decode-2026-07-04.md §A (zz_011230c_ chunk_0031.c:576-617, revert
 * FUN_8010f790 chunk_0030.c:4004-4026). On a connecting dash hit, if not already buffed, the
 * ATTACKER gains +4 param tiers (tier 16->20, velocity ×2.366 via timescale.ts's tier table)
 * for 1200 frames, then reverts.
 */
export const HERO_X_BUFF = {
  BORG_IDS: ["pl0804", "pl080c"] as readonly string[],
  TIER_DELTA: 4,
  DURATION_FRAMES: 1200,
} as const;
