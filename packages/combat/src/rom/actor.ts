// ROM-faithful actor runtime — 1:1 port of the Gotcha Force (GG4E) actor struct + engine.
//
// This module ports the real decompiled state-machine system instead of the generic
// archetype combat in the parent package. Source for every field and every function is
// cited to `research/decomp/ghidra-export/*.c` + `user-data/GG4E/disc/sys/boot.dol`.
//
// STATUS: foundation. The actor struct + physics integrator + cue/command dispatch are
// complete and are the shared core every family handler plugs into. Per-family action
// handlers (the `FUN_8018e888`-shaped phase machines) port incrementally; see
// PORTING.md in this folder. The generic @gf/combat archetypes stay as the fallback
// until each family's handler is ported and registered.
//
// Naming: ROM functions keep their `zz_NNNNNNN_` / `FUN_NNNNNNNN` names so the port is
// auditable against the corpus. Fields keep their `+0xNNN` offsets in comments.
//
// @romfield annotation grammar (machine-extracted by
// research/decomp/oracle-harness/gen_actor_field_map.py into actor-field-map.json —
// the RomActor codec's single source of truth; oracle-workstream-plan.md §3.3 P1.0):
//   @romfield <tsField> port_side
//   @romfield <tsField> +0xNNN <kind>
//   @romfield <tsField> +0xA <kind>, +0xB <kind>, ...     (tuple: element i at offset i)
//   @romfield <tsField> +0xBASE struct stride=0xSS count=N elem=<kind|interface>
//   kinds: u8 s8 u16 s16 u32 s32 f32 vec3 bam16 u16be ptr bytes[N]
//   (vec3 = three LE f32 at +0/+4/+8; bam16 = u16 binary angle; u16be = big-endian
//   u16, byte order preserved at the data boundary; ptr = u32 LE pointer.)
// Widths were grounded against the decompiled corpus (dominant Ghidra cast per offset,
// research/decomp/ghidra-export/chunk_*.c) or the cited function's own access pattern.
// A field WITHOUT a tag extracts as kind "unmapped" — visible and codec-refused, never
// guessed (plan §3.3 mechanism 3).

export interface Vec3 { x: number; y: number; z: number; }

/** Battle-local physics behavior used by ROM family integration. */
export interface RomPhysicsRuntime {
  clampToGround(pos: Vec3, velY: number): { y: number; velY: number; grounded: boolean };
  /** Battle-owned floor support query used by zz_00679d0_'s no-surface revert. */
  isSupported?(x: number, z: number): boolean;
}

/**
 * The actor struct, mirroring the GG4E `object+0xNNN` layout. Every offset is cited.
 *
 * Source convention: the live-verified 4P-versus trace (behavior-notes.md §ac) confirmed
 * `+0x20` as the position vec3, superseding the earlier §3.1 hypothesis of `+0x44`. The
 * physics integrator `FUN_80067310` (chunk_0008.c:3787) and the G RED family handler
 * `FUN_8018e888` (chunk_0047.c:810-813) both corroborate: `+0x20` is integrated against
 * the speed/velocity scalars at `+0x44/+0x48/+0x4c/+0x50`.
 *
 * The speed model is a SCALAR projection, not a free vec3 velocity:
 *   pos.x += (timescale × tierScale) × (hSpeed × cos(yaw))
 *   pos.y += (timescale × tierScale) × yVel
 *   pos.z += (timescale × tierScale) × (hSpeed × sin(yaw))
 *   hSpeed += hDecel × timescale           (clamp >= FLOAT_804375d0)
 *   yVel   += timescale × (gravityCoeff × gravityParam)
 * (FUN_80067310, chunk_0008.c:3794-3828. yaw = `+0x5ae` lock-yaw passed as param_3.)
 */
export interface RomActor {
  /** Port-side runtime dependency. Kept on the actor so concurrent battles cannot
   *  overwrite one another's floor behavior.
   *  @romfield physicsRuntime port_side */
  physicsRuntime: RomPhysicsRuntime | null;
  // ===== World transform (behavior-notes.md §ac, FUN_80067310) =====
  /** +0x20: world position (vec3). Live-verified 4P trace + camera chain.
   *  @romfield pos +0x20 vec3 */
  pos: Vec3;
  /** +0x38: motion delta / accumulator (vec3). Used by family handlers (e.g. G Crash
   *  phase 0 writes `pos -= target; pos *= 0.95`; phase 2 uses +0x38 as a magnitude).
   *  @romfield motion +0x38 vec3 */
  motion: Vec3;
  /** +0x5e8: cached target position consumed even after +0xcc lock invalidation.
   *  @romfield targetCache5e8 +0x5e8 vec3 */
  targetCache5e8: Vec3;
  /** +0x518: host-resolved actor aim origin consumed by zz_006e514_.
   *  @romfield aimOrigin518 +0x518 vec3 */
  aimOrigin518: Vec3;
  /** +0x8e0/+0x8f0/+0x900 plus part*0x30: renderer-authored world aim anchors.
   *  Three 0x10-spaced float rows per part block; the TS field keeps one Vec3 anchor
   *  per part, so the codec refuses this record until the row semantics are pinned.
   *  @romfield partAimAnchors +0x8e0 struct stride=0x30 count=4 elem=bytes[0x30] */
  partAimAnchors: Array<Vec3 | null>;
  // +0x44..+0x50: the speed-model scalars (FUN_80067310).
  /** +0x44: horizontal speed scalar (magnitude, projected via sin/cos(yaw)).
   *  @romfield hSpeed +0x44 f32 */
  hSpeed: number;
  /** +0x48: vertical (Y) velocity.
   *  @romfield yVel +0x48 f32 */
  yVel: number;
  /** +0x4c: horizontal decel rate (subtracted from hSpeed each frame).
   *  @romfield hDecel +0x4c f32 */
  hDecel: number;
  /** +0x50: per-actor gravity coefficient (multiplied into yVel via the gravity param).
   *  @romfield gravityCoeff +0x50 f32 */
  gravityCoeff: number;

  // ===== Orientation (behavior-notes.md §3.1, ram-trace) =====
  /** +0x72: heading yaw (BAM16, 0..0xFFFF). The integrator's `+0x5ae` lock-yaw is the
   *  snapshot family handlers copy here when a move starts.
   *  @romfield heading +0x72 bam16 */
  heading: number;
  /** +0x5ae: lock yaw — the yaw the physics integrator projects hSpeed against during a
   *  move (set by family handlers at move-start, e.g. FUN_8018e888:795-803).
   *  @romfield lockYaw +0x5ae bam16 */
  lockYaw: number;
  /** +0x5ac: active yaw (current integration target; FUN_8018e888 copies heading or lockYaw here).
   *  @romfield activeYaw +0x5ac bam16 */
  activeYaw: number;
  /** +0x5aa: remaining signed yaw error consumed by FUN_80066a30.
   *  @romfield turnErrorYaw +0x5aa bam16 */
  turnErrorYaw: number;
  /** +0x18da: phase-2 steering yaw for the sin/cos projection in descend phases
   *  (FUN_8018eb2c:907-911; ticked by FUN_8018ec34:937-940).
   *  @romfield steerYaw +0x18da bam16 */
  steerYaw: number;
  /** +0x70 body pitch used by zz_006e1d0_'s exact target equation (s16 BAM, corpus cast).
   *  @romfield bodyPitch +0x70 bam16 */
  bodyPitch: number;
  /** +0x768 seek-rate scale, initialized to 1.0 by FUN_800562b8.
   *  @romfield aimRateScale +0x768 f32 */
  aimRateScale: number;
  /** +0x868/+0x874/+0x880 action-speed rows copied from descriptor +0x134/+0x140/+0x14c.
   *  @romfield actionSpeedRows +0x868 f32, +0x874 f32, +0x880 f32 */
  actionSpeedRows: [number, number, number];
  /** +0x2c/+0x30/+0x34 saved grounded position used by zz_00679d0_ revert.
   *  @romfield savedGroundPos +0x2c vec3 */
  savedGroundPos: Vec3;
  /** +0x73f and +0x80c housekeeping fields written by these machines.
   *  @romfield housekeeping73f +0x73f u8
   *  @romfield accumulator80c +0x80c f32 */
  housekeeping73f: number;
  accumulator80c: number;
  /** +0x7c/+0x7e/+0x80 signed pose/animation accumulators.
   *  @romfield poseAccum7c +0x7c s16
   *  @romfield poseAccum7e +0x7e s16
   *  @romfield poseAccum80 +0x80 s16 */
  poseAccum7c: number;
  poseAccum7e: number;
  poseAccum80: number;
  /** +0x800/+0x804/+0x808: last afterimage sample position.
   *  @romfield afterimageSamplePos +0x800 vec3 */
  afterimageSamplePos: Vec3;
  /** +0xb4 and +0x7fc scale factors used by zz_00b22f4_ (+0xb4 float confirmed by
   *  zz_003cd5c_'s defender power read).
   *  @romfield modelScale +0xb4 f32
   *  @romfield sizeScale +0x7fc f32 */
  modelScale: number;
  sizeScale: number;
  /** Monotonic host/presentation edge emitted when zz_00b2190_(actor, 1) succeeds.
   *  @romfield afterimageSerial port_side */
  afterimageSerial: number;

  // ===== Weapon/part animation host state (zz_0048d54_ @0x80048d54) =====
  /** +0x579 descriptor-owned part-enable mask. Part 1 is deliberately skipped by
   *  zz_0048d54_; startStream also intersects its requested mask with this byte.
   *  @romfield weaponPartMask +0x579 u8 */
  weaponPartMask: number;
  /** +0x1d9a mask of part-animation blocks armed by the most recent helper call.
   *  @romfield weaponAnimationActiveMask +0x1d9a u8 */
  weaponAnimationActiveMask: number;
  /** +0x1b03 + part*0x40. The helper writes 5 for each armed non-part-1 block.
   *  @romfield weaponAnimationState +0x1b03 struct stride=0x40 count=4 elem=u8 */
  weaponAnimationState: [number, number, number, number];
  /** +0x1b20..+0x1b45 inputs consumed by zz_0048d54_.
   *  @romfield weaponAnimationParams +0x1b20 struct stride=0x0 count=1 elem=RomWeaponAnimationParams */
  weaponAnimationParams: RomWeaponAnimationParams;
  /** +0x1bd4 + part*0x40 through +0x1c05 + part*0x40. Raw bytes preserve the
   *  engine-owned record layout without inventing renderer semantics.
   *  @romfield weaponAnimationBlocks +0x1bd4 struct stride=0x40 count=4 elem=bytes[0x38] */
  weaponAnimationBlocks: [Uint8Array, Uint8Array, Uint8Array, Uint8Array];
  /** +0x1aec/+0x1af0/+0x1af4 plus part*0x40. This timing record precedes and is
   *  distinct from the raw descriptor block rooted at +0x1bd4.
   *  @romfield weaponAnimationTiming +0x1aec struct stride=0x40 count=4 elem=RomWeaponAnimationTiming */
  weaponAnimationTiming: [RomWeaponAnimationTiming, RomWeaponAnimationTiming, RomWeaponAnimationTiming, RomWeaponAnimationTiming];

  // ===== Target visibility/eligibility (zz_006bf80_ @0x8006bf80) =====
  /** +0x3e5 = 1 << +0x3e4.
   *  @romfield visibilityBit +0x3e5 u8 */
  visibilityBit: number;
  /** +0xcc refreshed target pointer and the six battle actors whose +0x5e6 masks
   *  the helper updates. The bridge supplies battle-local objects.
   *  @romfield visibilityTarget +0xcc ptr
   *  @romfield visibilityRoster port_side */
  visibilityTarget: RomVisibilityTarget | null;
  visibilityRoster: RomVisibilityTarget[];

  // ===== Form-change mirrors (zz_006a8c0_ @0x8006a8c0) =====
  /** +0x94 borg-number mirror; +0x96/+0x97 carry +0x3e4/+0x3e7.
   *  @romfield borgMirror94 +0x94 u16be
   *  @romfield carriedSlot96 +0x96 u8
   *  @romfield carriedVariant97 +0x97 u8 */
  borgMirror94: number;
  carriedSlot96: number;
  carriedVariant97: number;
  /** +0x3e7 identity/palette byte carried through a morph.
   *  @romfield identityVariant +0x3e7 u8 */
  identityVariant: number;

  // ===== Identity (behavior-notes.md §z) =====
  /** +0x3e8: borg number (0x615 = G RED, 0x629 = NEO G RED, etc.). PPC big-endian
   *  byte order preserved at the data boundary (family byte at +0x3e8, variant +0x3e9).
   *  @romfield borgNumber +0x3e8 u16be */
  borgNumber: number;
  /** +0x3e4: slot index (0..5).
   *  @romfield slot +0x3e4 u8 */
  slot: number;
  /** +0x88: team (0 = player/ally, 1 = enemy).
   *  @romfield team +0x88 u8 */
  team: number;

  // ===== State machine cursors (behavior-notes.md §u, cue-script-stream-decode) =====
  /** +0x540: full-body phase cursor (the handler-table index; PTR_FUN_802d3570 for the
   *  deploy state, family virtuals for state 61).
   *  @romfield fbPhase +0x540 u8 */
  fbPhase: number;
  /** +0x544..+0x547: per-handler phase-bytes (full body). Family handlers increment to advance.
   *  @romfield fbPhaseSlots +0x544 u8, +0x545 u8, +0x546 u8, +0x547 u8 */
  fbPhaseSlots: [number, number, number, number];
  /** +0x5da: current full-body STATE value (the cue-table byte; -1 = no state). State 61
   *  = "attack" → calls the family virtual at +0x4b4.
   *  @romfield fbState +0x5da s8 */
  fbState: number;
  /** +0x5db: current upper-body state value.
   *  @romfield ubState +0x5db s8 */
  ubState: number;
  /** +0x5dc/+0x5dd: previous state values (for transition detection).
   *  @romfield prevFbState +0x5dc s8
   *  @romfield prevUbState +0x5dd s8 */
  prevFbState: number;
  prevUbState: number;
  /** +0x5e4: upper-body CUE id (the index into +0x4f0 last dispatched by zz_006a750_).
   *  @romfield ubCue +0x5e4 u8 */
  ubCue: number;
  /** +0x5e5: full-body cue id.
   *  @romfield fbCue +0x5e5 u8 */
  fbCue: number;
  /** +0x5e0: control word (bitfield; bits 0..1 = action-mode, 0x40 = position-frozen,
   *  0xa0 = lock-yaw override, 0x5000000 = ring-out mode, etc.). FUN_8018e888:798,
   *  zz_006a104_:620/634, behavior-notes.md §u.
   *  @romfield controlWord +0x5e0 u32 */
  controlWord: number;

  // ===== Command dispatch (cue-script-stream-decode, zz_006a104_) =====
  /** +0x580: actionIndex (the family action-table row; 0=dash, 1=B-melee, 2=air-B/X,
   *  3=B-charge, 4=…). Set by zz_006a104_ from the command-record byte 2.
   *  @romfield actionIndex +0x580 u8 */
  actionIndex: number;
  /** +0x581: variantIndex (the per-action variant; command-record byte 3).
   *  @romfield variantIndex +0x581 u8 */
  variantIndex: number;
  /** +0x584: previous actionIndex (for transition gating; zz_006a104_:618).
   *  @romfield prevActionIndex +0x584 u8 */
  prevActionIndex: number;
  /** +0x585: command-table row key (button: 0=B-far, 1=B-close, 2=X, 3=B-charge).
   *  @romfield cmdButton +0x585 u8 */
  cmdButton: number;
  /** +0x586: command subtype.
   *  @romfield cmdSubtype +0x586 u8 */
  cmdSubtype: number;
  /** +0x587: charged-ranged forced flag.
   *  @romfield cmdChargedRanged +0x587 u8 */
  cmdChargedRanged: number;

  // ===== Family virtuals + descriptor (set by each family ctor) =====
  /** +0x4b4: family root action dispatcher (state 61 calls this; G RED = zz_018d24c_).
   *  @romfield rootAction +0x4b4 ptr */
  rootAction: ((actor: RomActor) => void) | null;
  /** Port-side flag (no ROM offset): true when the family's rootAction wires a B-charge
   *  handler at actionIndex 3. Set by family configure closures (G RED's
   *  createGRedRootAction, shared-engine when bCharge is wired). The bridge's
   *  tryStartBAttack reads this to decide whether to intercept B presses for the ROM
   *  phase machine instead of falling through to the generic startShotAttack/startMeleeAttack.
   *  @romfield hasBCharge port_side */
  hasBCharge: boolean;
  /** +0x4b8: family upper-body virtual.
   *  @romfield upperBody +0x4b8 ptr */
  upperBody: ((actor: RomActor) => void) | null;
  /** +0x4bc: pre-state virtual (FUN_80055568:7793).
   *  @romfield preState +0x4bc ptr */
  preState: ((actor: RomActor) => void) | null;
  /** +0x4c0: post-state virtual (FUN_80055568:7800).
   *  @romfield postState +0x4c0 ptr */
  postState: ((actor: RomActor) => void) | null;
  /** +0x4b0: family descriptor pointer (per-borg data page: stats, command records,
   *  variant tables; chunk_0006.c reads +0x42/+0x6c/+0x8c/+0xb8/+0xbe/+0xbf/+0xf8..).
   *  @romfield descriptor +0x4b0 ptr */
  descriptor: RomDescriptor | null;
  /** +0x4ec: command-move table root (per-button/subtype/direction records;
   *  commandMoveTables.json, already extracted).
   *  @romfield commandTable +0x4ec ptr */
  commandTable: RomCommandTable | null;
  /** +0x4f0: cue→state table (48 entries × 2 bytes = [fullBodyState, upperBodyState];
   *  -1 = no transition. zz_006a6fc_ reads byte 0, zz_006a750_ reads byte 1).
   *  @romfield cueTable +0x4f0 ptr */
  cueTable: Int8Array | null;

  // ===== Action-script stream state (zz_004beb8_, zz_004cd24_) =====
  /** +0x1d80: family action-script bank pointer (group bit7 clear → this).
   *  +0x1d84: shared bank (group bit7 set). Each bank: s16 group-offsets, s16 slot-offsets.
   *  @romfield familyStreamBank +0x1d80 ptr
   *  @romfield sharedStreamBank +0x1d84 ptr */
  familyStreamBank: Uint8Array | null;
  sharedStreamBank: Uint8Array | null;
  /** +0x1d88/+0x1d8c: family/shared anim descriptor banks (PATH-B sound lists).
   *  @romfield familyAnimDescBank +0x1d88 ptr
   *  @romfield sharedAnimDescBank +0x1d8c ptr */
  familyAnimDescBank: Uint8Array | null;
  sharedAnimDescBank: Uint8Array | null;
  /** +0x4e8: family sound-event table (per-anim whoosh/voice index list).
   *  @romfield soundEventTable +0x4e8 ptr */
  soundEventTable: Uint8Array | null;
  /** +0x582: default stream group (group==0 → this; cue-script-stream-decode §3).
   *  @romfield defaultGroup +0x582 u8 */
  defaultGroup: number;
  /** +0x6ea: per-move stream slot cursor (combo follow-ups ++ this; FUN_80177e28:3027).
   *  @romfield streamSlot +0x6ea u8 */
  streamSlot: number;
  /** Per-part stream-state blocks at +0x1cd4, stride 0x20, 4 parts. The action-stream
   *  interpreter `zz_004cd24_` polls these each frame (chunk_0006.c:2014).
   *  @romfield parts +0x1cd4 struct stride=0x20 count=4 elem=RomPartState */
  parts: [RomPartState, RomPartState, RomPartState, RomPartState];

  // ===== Motion clamps (per-borg data page via FUN_80067310:3816-3828) =====
  /** +0x67c: max Y rise velocity (flying clamp).
   *  @romfield maxRise +0x67c f32 */
  maxRise: number;
  /** +0x680: max Y fall velocity (terminal velocity; flyers override to FLOAT_804375f0).
   *  @romfield maxFall +0x680 f32 */
  maxFall: number;
  /** +0x678: max hSpeed (ground run clamp).
   *  @romfield maxHSpeed +0x678 f32 */
  maxHSpeed: number;
  /** +0x6d0: step height (ground snap-up; collision zz_00677b0_).
   *  @romfield stepHeight +0x6d0 f32 */
  stepHeight: number;

  // ===== Timescale + status (FUN_8005a378, status-effects-decode) =====
  /** +0x5f4: timescale multiplier (1.0 × burst × haste × slow; ×0.03 while frozen).
   *  @romfield timescale +0x5f4 f32 */
  timescale: number;
  /** +0x5f8: tier velocity scale (param-tier; ×2.366 at tier 20).
   *  @romfield tierScale +0x5f8 f32 */
  tierScale: number;
  /** +0x1dc8: per-frame delta-time (the integrator's accumulation tick).
   *  @romfield dt +0x1dc8 f32 */
  dt: number;

  // ===== Move contact flags (the G Crash + status-effect handlers' phase triggers) =====
  /** +0x1cef: part-0 contact flag (op 0x02 sets this; G Crash phase 1 polls >0 for hit).
   *  @romfield contactP0 +0x1cef s8 */
  contactP0: number;
  /** +0x1cee: wall/stream-contact flag used by family handlers to end moves.
   *  @romfield wallContact +0x1cee s8 */
  wallContact: number;
  /** +0x144: live low-nibble child/beam ownership mask polled by Cyber Girl.
   *  @romfield childMask144 +0x144 u8 */
  childMask144: number;
  /** +0x14c..+0x14f: per-hardpoint attachment flags. Machine Blue's action 3/4
   * handlers test bit 0 before dispatching zz_013212c_ for that hardpoint.
   *  @romfield attachmentFlags14c +0x14c u8, +0x14d u8, +0x14e u8, +0x14f u8 */
  attachmentFlags14c: [number, number, number, number];
  /** +0x1cf0: signed part-1/contact event byte.
   *  @romfield contactP1 +0x1cf0 s8 */
  contactP1: number;
  /** +0x1d0f: signed stream-authored dash-strength byte.
   *  @romfield dashStrength1d0f +0x1d0f s8 */
  dashStrength1d0f: number;
  /** +0x1d10: signed stream-authored face/reseek byte.
   *  @romfield faceGate1d10 +0x1d10 s8 */
  faceGate1d10: number;
  /** +0x1b03: stream/animation hold byte.
   *  @romfield streamHold1b03 +0x1b03 s8 */
  streamHold1b03: number;
  /** +0x6eb: signed per-move stream/repeat counter.
   *  @romfield streamCounter6eb +0x6eb s8 */
  streamCounter6eb: number;
  /** +0x5b4: live action status word.
   *  @romfield statusWord5b4 +0x5b4 u32 */
  statusWord5b4: number;
  /** +0x5d4/+0x5d8: raw edge and held input words.
   *  @romfield inputEdge5d4 +0x5d4 u32
   *  @romfield inputHeld5d8 +0x5d8 u32 */
  inputEdge5d4: number;
  inputHeld5d8: number;
  /** +0x694: state-timer float (e.g. deploy lock, post-state cooldown; zz_005568c_ decays it).
   *  @romfield stateTimer +0x694 f32 */
  stateTimer: number;
  /** +0x1d9c/+0x1db2/+0x1db3 reset by zz_006a668_ before arming shot channels.
   *  @romfield shotScalar1d9c +0x1d9c f32
   *  @romfield shotByte1db2 +0x1db2 u8
   *  @romfield shotByte1db3 +0x1db3 u8 */
  shotScalar1d9c: number;
  shotByte1db2: number;
  shotByte1db3: number;
  /** +0x558: handler-local timer (G Crash phase 2 seeds 120.0; phase 3 counts down).
   *  @romfield handlerTimer +0x558 f32 */
  handlerTimer: number;

  // ===== Out-of-scope fields (HP, gauges, lock-on, weapon cells) are owned by the
  // existing @gf/combat BorgRuntime; the ROM runtime composes with it rather than
  // duplicating. See PORTING.md. =====
}

/** Per-part stream-state block (actor+0x1cd4 + partIndex*0x20, the structure
 *  `zz_004cd24_` walks at chunk_0006.c:2014). Member offsets are block-relative. */
export interface RomPartState {
  /** +0x00: stream pointer (offset into the resolved bank; -1 = no stream).
   *  @romfield streamPtr +0x00 s32 */
  streamPtr: number;
  /** +0x04: frame clock (accumulates +dt; gates wait ops).
   *  @romfield frameClock +0x04 f32 */
  frameClock: number;
  /** +0x08/+0x0c: prev/cur integration targets.
   *  @romfield prevTarget +0x08 f32
   *  @romfield curTarget +0x0c f32 */
  prevTarget: number;
  curTarget: number;
  /** +0x10: anim-time accumulator.
   *  @romfield animTime +0x10 f32 */
  animTime: number;
  /** +0x1a: stream-active flag.
   *  @romfield active +0x1a u8 */
  active: number;
  /** +0x1b: state byte (op 0x02 writes here per part).
   *  @romfield stateByte +0x1b s8 */
  stateByte: number;
  /** +0x144/+0x145 ownership/display byte used by Panther's detached fists.
   *  (Actor-relative, not block-relative — deliberately untagged until the
   *  attribution is pinned; extracts as unmapped.) */
  ownershipFlags?: number;
}

export interface RomWeaponAnimationParams {
  /** +0x1b20, +0x1b28, +0x1b2c, +0x1b30.
   *  @romfield baseRate +0x1b20 f32
   *  @romfield descriptorWord +0x1b28 u32
   *  @romfield endFrame +0x1b2c f32 */
  baseRate: number;
  descriptorWord: number;
  endFrame: number;
  /** (+0x1b30 corpus casts are mixed int/float at this offset across structs —
   *  deliberately untagged until zz_0048d54_'s own access is pinned; unmapped.) */
  startFrame: number;
  /** +0x1b3c/+0x1b3d and +0x1b43..+0x1b45.
   *  @romfield group +0x1b3c u8
   *  @romfield slot +0x1b3d u8
   *  @romfield durationAdjust +0x1b43 s8
   *  @romfield toggle +0x1b44 u8
   *  @romfield tailByte +0x1b45 u8 */
  group: number;
  slot: number;
  durationAdjust: number;
  toggle: number;
  tailByte: number;
  /** Exact zz_004d1f4_ result used by zz_004d244_; null means the host has not
   *  loaded an animation descriptor and the copier leaves descriptor bytes alone.
   *  @romfield descriptor port_side */
  descriptor: Uint8Array | null;
}

export interface RomWeaponAnimationTiming {
  /** +0x1aec: param_10 + 1 (dominant corpus cast: int).
   *  @romfield duration +0x1aec s32 */
  duration: number;
  /** +0x1af0: actor +0x1dc8.
   *  @romfield dt +0x1af0 f32 */
  dt: number;
  /** +0x1af4: dt / duration.
   *  @romfield rate +0x1af4 f32 */
  rate: number;
}

export interface RomVisibilityTarget {
  /** target +0x83; zero is eligible. */
  eligibility83: number;
  /** target +0x5e0; high bit excludes it from the re-add branch. */
  controlWord: number;
  /** target +0x5e6 visibility mask. */
  visibilityMask5e6: number;
}

/** Family descriptor (actor+0x4b0). Layout partial — fields surface as family handlers
 *  get ported. Source: chunk_0006.c reads at +0x42/+0x6c/+0x8c/+0xb8/+0xbe/+0xbf. */
export interface RomDescriptor {
  /** +0x00: header byte (commandMode copy). */
  header: number;
  /** +0x10: main-hand bone index (op 0x07 / FUN_8018e888 reference). */
  mainHandBone: number;
  /** +0x42: per-subtype command byte (chunk_0006.c:483). */
  subtypeCommand: Int8Array;
  /** +0x6c: handler-data byte (FUN_8018eb2c:918 copies this into +0x50). */
  handlerData6c: number;
  /** +0x8c: per-(subtype,part) command byte (chunk_0006.c:379/407/451/1213). */
  subtypePartCommand: Int8Array;
  /** +0xb8: per-button live-record flag (zz_006a3d0_:690 gates the type-2/X path). */
  buttonLiveFlag: Int8Array;
  /** +0xbe/+0xbf: default hand bytes (op 0x07 fallback when stream has no hand-swap). */
  defaultHand0: number;
  defaultHand1: number;
  // Per-borg data page fields (pl####data.bin, 432 bytes)
  /** +0x2c: max horizontal speed (big-endian float). */
  maxHSpeed?: number;
  /** +0x44: ground-accel magnitude (big-endian float). */
  groundAccel?: number;
  /** +0x48: jump vertical impulse parameter (big-endian float). */
  jumpImpulse?: number;
  /** +0x50: min/turn speed (big-endian float, = guide speed-stat). */
  minSpeed?: number;
  /** +0x68: gravity slot A — ground/turn states (big-endian float). */
  gravitySlotA?: number;
  /** +0x70: gravity slot C (big-endian float). */
  gravitySlotC?: number;
  /** +0x9f: handler-data byte (anim/frame parameter). */
  handlerData9f?: number;
  /** +0x3d: handler-data byte (jump arc / timer parameter). */
  handlerData3d?: number;
  /** +0x68: handler-data float (gravity slot A — ground/turn). */
  handlerData68?: number;
  /** +0x48: handler-data float (jump vertical impulse). */
  handlerData48?: number;
  /** +0x2c: handler-data float (max horizontal speed). */
  handlerData2c?: number;
  /** +0xac/+0xae: per-frame BAM16 turn steps selected by aimType low nibble. */
  turnStep0?: number;
  turnStep1?: number;
}

/** Command-move table (actor+0x4ec). Already extracted fleet-wide into
 *  packages/combat/src/data/commandMoveTables.json — the ROM runtime consumes that data. */
export interface RomCommandTable {
  /** Per-(button, subtype, direction) record: actionIndex/variantIndex + disabled flag. */
  records: ReadonlyArray<{
    button: number; subtype: number; direction: number | null;
    actionIndex: number; variantIndex: number; disabled: boolean;
  }>;
}

/** Create a blank actor (fields default to the ROM power-on state). */
export function createRomActor(): RomActor {
  return {
    physicsRuntime: null,
    pos: { x: 0, y: 0, z: 0 },
    motion: { x: 0, y: 0, z: 0 }, targetCache5e8: { x: 0, y: 0, z: 0 },
    aimOrigin518: { x: 0, y: 0, z: 0 },
    partAimAnchors: [null, null, null, null],
    hSpeed: 0, yVel: 0, hDecel: 0, gravityCoeff: 0,
    heading: 0, lockYaw: 0, activeYaw: 0, turnErrorYaw: 0, steerYaw: 0,
    bodyPitch: 0, aimRateScale: 1, actionSpeedRows: [0, 0, 0],
    savedGroundPos: { x: 0, y: 0, z: 0 }, housekeeping73f: 0, accumulator80c: 0,
    poseAccum7c: 0, poseAccum7e: 0, poseAccum80: 0,
    afterimageSamplePos: { x: 0, y: 0, z: 0 }, modelScale: 1, sizeScale: 1,
    afterimageSerial: 0,
    weaponPartMask: 0x0f,
    weaponAnimationActiveMask: 0,
    weaponAnimationState: [0, 0, 0, 0],
    weaponAnimationParams: {
      baseRate: 0, descriptorWord: 0, endFrame: 0, startFrame: 0,
      group: 0, slot: 0, durationAdjust: 0, toggle: 0, tailByte: 0,
      descriptor: null,
    },
    weaponAnimationBlocks: [new Uint8Array(0x38), new Uint8Array(0x38), new Uint8Array(0x38), new Uint8Array(0x38)],
    weaponAnimationTiming: [makeBlankWeaponTiming(), makeBlankWeaponTiming(), makeBlankWeaponTiming(), makeBlankWeaponTiming()],
    visibilityBit: 1, visibilityTarget: null, visibilityRoster: [],
    borgMirror94: 0, carriedSlot96: 0, carriedVariant97: 0, identityVariant: 0,
    borgNumber: 0, slot: 0, team: 0,
    fbPhase: 0, fbPhaseSlots: [0, 0, 0, 0],
    fbState: -1, ubState: -1, prevFbState: -1, prevUbState: -1,
    ubCue: 0, fbCue: 0, controlWord: 0,
    actionIndex: 0, variantIndex: 0, prevActionIndex: 0,
    cmdButton: 0, cmdSubtype: 0, cmdChargedRanged: 0,
    rootAction: null, hasBCharge: false, upperBody: null, preState: null, postState: null,
    descriptor: null, commandTable: null, cueTable: null,
    familyStreamBank: null, sharedStreamBank: null,
    familyAnimDescBank: null, sharedAnimDescBank: null, soundEventTable: null,
    defaultGroup: 0, streamSlot: 0,
    parts: [makeBlankPart(), makeBlankPart(), makeBlankPart(), makeBlankPart()],
    maxRise: 0, maxFall: 0, maxHSpeed: 0, stepHeight: 0,
    timescale: 1, tierScale: 1, dt: 1,
    contactP0: 0, wallContact: 0, childMask144: 0,
    attachmentFlags14c: [0, 0, 0, 0], contactP1: 0,
    dashStrength1d0f: 0, faceGate1d10: 0, streamHold1b03: 0, streamCounter6eb: 0,
    statusWord5b4: 0, inputEdge5d4: 0, inputHeld5d8: 0,
    stateTimer: 0, shotScalar1d9c: 0, shotByte1db2: 0, shotByte1db3: 0, handlerTimer: 0,
  };
}

function makeBlankPart(): RomPartState {
  return { streamPtr: -1, frameClock: 0, prevTarget: 0, curTarget: 0, animTime: 0, active: 0, stateByte: 0 };
}

function makeBlankWeaponTiming(): RomWeaponAnimationTiming {
  return { duration: 0, dt: 0, rate: 0 };
}
