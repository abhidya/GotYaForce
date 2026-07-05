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

export interface Vec3 { x: number; y: number; z: number; }

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
  // ===== World transform (behavior-notes.md §ac, FUN_80067310) =====
  /** +0x20: world position (vec3). Live-verified 4P trace + camera chain. */
  pos: Vec3;
  /** +0x38: motion delta / accumulator (vec3). Used by family handlers (e.g. G Crash
   *  phase 0 writes `pos -= target; pos *= 0.95`; phase 2 uses +0x38 as a magnitude). */
  motion: Vec3;
  // +0x44..+0x50: the speed-model scalars (FUN_80067310).
  /** +0x44: horizontal speed scalar (magnitude, projected via sin/cos(yaw)). */
  hSpeed: number;
  /** +0x48: vertical (Y) velocity. */
  yVel: number;
  /** +0x4c: horizontal decel rate (subtracted from hSpeed each frame). */
  hDecel: number;
  /** +0x50: per-actor gravity coefficient (multiplied into yVel via the gravity param). */
  gravityCoeff: number;

  // ===== Orientation (behavior-notes.md §3.1, ram-trace) =====
  /** +0x72: heading yaw (BAM16, 0..0xFFFF). The integrator's `+0x5ae` lock-yaw is the
   *  snapshot family handlers copy here when a move starts. */
  heading: number;
  /** +0x5ae: lock yaw — the yaw the physics integrator projects hSpeed against during a
   *  move (set by family handlers at move-start, e.g. FUN_8018e888:795-803). */
  lockYaw: number;
  /** +0x5ac: active yaw (current integration target; FUN_8018e888 copies heading or lockYaw here). */
  activeYaw: number;
  /** +0x18da: phase-2 steering yaw for the sin/cos projection in descend phases
   *  (FUN_8018eb2c:907-911; ticked by FUN_8018ec34:937-940). */
  steerYaw: number;

  // ===== Identity (behavior-notes.md §z) =====
  /** +0x3e8: borg number (0x615 = G RED, 0x629 = NEO G RED, etc.). */
  borgNumber: number;
  /** +0x3e4: slot index (0..5). */
  slot: number;
  /** +0x88: team (0 = player/ally, 1 = enemy). */
  team: number;

  // ===== State machine cursors (behavior-notes.md §u, cue-script-stream-decode) =====
  /** +0x540: full-body phase cursor (the handler-table index; PTR_FUN_802d3570 for the
   *  deploy state, family virtuals for state 61). */
  fbPhase: number;
  /** +0x544..+0x547: per-handler phase-bytes (full body). Family handlers increment to advance. */
  fbPhaseSlots: [number, number, number, number];
  /** +0x5da: current full-body STATE value (the cue-table byte; -1 = no state). State 61
   *  = "attack" → calls the family virtual at +0x4b4. */
  fbState: number;
  /** +0x5db: current upper-body state value. */
  ubState: number;
  /** +0x5dc/+0x5dd: previous state values (for transition detection). */
  prevFbState: number;
  prevUbState: number;
  /** +0x5e4: upper-body CUE id (the index into +0x4f0 last dispatched by zz_006a750_). */
  ubCue: number;
  /** +0x5e5: full-body cue id. */
  fbCue: number;
  /** +0x5e0: control word (bitfield; bits 0..1 = action-mode, 0x40 = position-frozen,
   *  0xa0 = lock-yaw override, 0x5000000 = ring-out mode, etc.). FUN_8018e888:798,
   *  zz_006a104_:620/634, behavior-notes.md §u. */
  controlWord: number;

  // ===== Command dispatch (cue-script-stream-decode, zz_006a104_) =====
  /** +0x580: actionIndex (the family action-table row; 0=dash, 1=B-melee, 2=air-B/X,
   *  3=B-charge, 4=…). Set by zz_006a104_ from the command-record byte 2. */
  actionIndex: number;
  /** +0x581: variantIndex (the per-action variant; command-record byte 3). */
  variantIndex: number;
  /** +0x584: previous actionIndex (for transition gating; zz_006a104_:618). */
  prevActionIndex: number;
  /** +0x585: command-table row key (button: 0=B-far, 1=B-close, 2=X, 3=B-charge). */
  cmdButton: number;
  /** +0x586: command subtype. */
  cmdSubtype: number;
  /** +0x587: charged-ranged forced flag. */
  cmdChargedRanged: number;

  // ===== Family virtuals + descriptor (set by each family ctor) =====
  /** +0x4b4: family root action dispatcher (state 61 calls this; G RED = zz_018d24c_). */
  rootAction: ((actor: RomActor) => void) | null;
  /** +0x4b8: family upper-body virtual. */
  upperBody: ((actor: RomActor) => void) | null;
  /** +0x4bc: pre-state virtual (FUN_80055568:7793). */
  preState: ((actor: RomActor) => void) | null;
  /** +0x4c0: post-state virtual (FUN_80055568:7800). */
  postState: ((actor: RomActor) => void) | null;
  /** +0x4b0: family descriptor pointer (per-borg data page: stats, command records,
   *  variant tables; chunk_0006.c reads +0x42/+0x6c/+0x8c/+0xb8/+0xbe/+0xbf/+0xf8..). */
  descriptor: RomDescriptor | null;
  /** +0x4ec: command-move table root (per-button/subtype/direction records;
   *  commandMoveTables.json, already extracted). */
  commandTable: RomCommandTable | null;
  /** +0x4f0: cue→state table (48 entries × 2 bytes = [fullBodyState, upperBodyState];
   *  -1 = no transition. zz_006a6fc_ reads byte 0, zz_006a750_ reads byte 1). */
  cueTable: Int8Array | null;

  // ===== Action-script stream state (zz_004beb8_, zz_004cd24_) =====
  /** +0x1d80: family action-script bank pointer (group bit7 clear → this).
   *  +0x1d84: shared bank (group bit7 set). Each bank: s16 group-offsets, s16 slot-offsets. */
  familyStreamBank: Uint8Array | null;
  sharedStreamBank: Uint8Array | null;
  /** +0x1d88/+0x1d8c: family/shared anim descriptor banks (PATH-B sound lists). */
  familyAnimDescBank: Uint8Array | null;
  sharedAnimDescBank: Uint8Array | null;
  /** +0x4e8: family sound-event table (per-anim whoosh/voice index list). */
  soundEventTable: Uint8Array | null;
  /** +0x582: default stream group (group==0 → this; cue-script-stream-decode §3). */
  defaultGroup: number;
  /** +0x6ea: per-move stream slot cursor (combo follow-ups ++ this; FUN_80177e28:3027). */
  streamSlot: number;
  /** Per-part stream-state blocks at +0x1cd4, stride 0x20, 4 parts. The action-stream
   *  interpreter `zz_004cd24_` polls these each frame (chunk_0006.c:2014). */
  parts: [RomPartState, RomPartState, RomPartState, RomPartState];

  // ===== Motion clamps (per-borg data page via FUN_80067310:3816-3828) =====
  /** +0x67c: max Y rise velocity (flying clamp). */
  maxRise: number;
  /** +0x680: max Y fall velocity (terminal velocity; flyers override to FLOAT_804375f0). */
  maxFall: number;
  /** +0x678: max hSpeed (ground run clamp). */
  maxHSpeed: number;
  /** +0x6d0: step height (ground snap-up; collision zz_00677b0_). */
  stepHeight: number;

  // ===== Timescale + status (FUN_8005a378, status-effects-decode) =====
  /** +0x5f4: timescale multiplier (1.0 × burst × haste × slow; ×0.03 while frozen). */
  timescale: number;
  /** +0x5f8: tier velocity scale (param-tier; ×2.366 at tier 20). */
  tierScale: number;
  /** +0x1dc8: per-frame delta-time (the integrator's accumulation tick). */
  dt: number;

  // ===== Move contact flags (the G Crash + status-effect handlers' phase triggers) =====
  /** +0x1cef: part-0 contact flag (op 0x02 sets this; G Crash phase 1 polls >0 for hit). */
  contactP0: number;
  /** +0x1cee: wall-contact flag (G Crash phase 3 polls for ground/wall to end the move). */
  wallContact: number;
  /** +0x694: state-timer float (e.g. deploy lock, post-state cooldown; zz_005568c_ decays it). */
  stateTimer: number;
  /** +0x558: handler-local timer (G Crash phase 2 seeds 120.0; phase 3 counts down). */
  handlerTimer: number;

  // ===== Out-of-scope fields (HP, gauges, lock-on, weapon cells) are owned by the
  // existing @gf/combat BorgRuntime; the ROM runtime composes with it rather than
  // duplicating. See PORTING.md. =====
}

/** Per-part stream-state block (actor+0x1cd4 + partIndex*0x20, the structure
 *  `zz_004cd24_` walks at chunk_0006.c:2014). */
export interface RomPartState {
  /** +0x00: stream pointer (offset into the resolved bank; -1 = no stream). */
  streamPtr: number;
  /** +0x04: frame clock (accumulates +dt; gates wait ops). */
  frameClock: number;
  /** +0x08/+0x0c: prev/cur integration targets. */
  prevTarget: number;
  curTarget: number;
  /** +0x10: anim-time accumulator. */
  animTime: number;
  /** +0x1a: stream-active flag. */
  active: number;
  /** +0x1b: state byte (op 0x02 writes here per part). */
  stateByte: number;
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
    pos: { x: 0, y: 0, z: 0 },
    motion: { x: 0, y: 0, z: 0 },
    hSpeed: 0, yVel: 0, hDecel: 0, gravityCoeff: 0,
    heading: 0, lockYaw: 0, activeYaw: 0, steerYaw: 0,
    borgNumber: 0, slot: 0, team: 0,
    fbPhase: 0, fbPhaseSlots: [0, 0, 0, 0],
    fbState: -1, ubState: -1, prevFbState: -1, prevUbState: -1,
    ubCue: 0, fbCue: 0, controlWord: 0,
    actionIndex: 0, variantIndex: 0, prevActionIndex: 0,
    cmdButton: 0, cmdSubtype: 0, cmdChargedRanged: 0,
    rootAction: null, upperBody: null, preState: null, postState: null,
    descriptor: null, commandTable: null, cueTable: null,
    familyStreamBank: null, sharedStreamBank: null,
    familyAnimDescBank: null, sharedAnimDescBank: null, soundEventTable: null,
    defaultGroup: 0, streamSlot: 0,
    parts: [makeBlankPart(), makeBlankPart(), makeBlankPart(), makeBlankPart()],
    maxRise: 0, maxFall: 0, maxHSpeed: 0, stepHeight: 0,
    timescale: 1, tierScale: 1, dt: 1,
    contactP0: 0, wallContact: 0, stateTimer: 0, handlerTimer: 0,
  };
}

function makeBlankPart(): RomPartState {
  return { streamPtr: -1, frameClock: 0, prevTarget: 0, curTarget: 0, animTime: 0, active: 0, stateByte: 0 };
}
