/** Bounded control-flow port of 80178394, phase table 80352b18.
 * RED action1/variant4 wrapper8018e148 selects config80365744. Source bodies:
 * research/decomp/ghidra-export/chunk_0044.c:3206–3500; wrapper chunk_0047.c.
 * Target anchors, terrain, physics clocks and authored streams remain explicit
 * host dependencies. This module does not supply geometry or claim full parity.
 */
export interface GredAirMeleeVec3 { x: number; y: number; z: number }

export interface GredAirMeleeState {
  phase: number;                 // +540
  noTargetLatch541: number;      // nonzero clears +cc on EVERY entry
  target: object | null;         // +cc; hooks must observe mutations
  rangeRow86c: number;           // +86c + (signed byte +584 % 3) * 12
  heading72: number;
  activeYaw: number;             // +5ac
  lockYaw: number;               // +5ae
  pitch54e: number;              // signed BAM16 pursuit pitch
  shift18da: number;             // independent part-pitch channel
  handlerTimer: number;          // +558
  pos: GredAirMeleeVec3;          // +20
  savedGroundPos: GredAirMeleeVec3; // +5e8 OWN position history, not target or +2c
  motion: GredAirMeleeVec3;       // +38
  hSpeed: number;                // +44
  yVel: number;                  // +48
  hDecel: number;                // +4c
  gravityCoeff: number;          // +50
  poseAccum7c: GredAirMeleeVec3;  // signed16 pose accumulators +7c/+7e/+80
  streamSlot6ea: number;         // signed byte, incremented BEFORE startStream
  dashStrength1d0f: number;      // signed stream byte
  aimMode1d10: number;           // signed stream byte; bit 2 selects part pitch
  descriptorGravity6c: number;   // descriptor+6c; RED value -1, supplied by host
  retap746: number;
  alt745: number;
  input1d9: number;
  inputEdges5d4: number;
  contactP0: number;             // signed +1cef; raw bytes accepted
  contactP1: number;             // signed +1cf0; raw bytes accepted
  streamHold1b03: number;        // stream blend mode, not a generic timing gate
  wallContact: number;           // +1cee animation completion, NOT wall collision
  actionFlag73f: number;
  controlWord: number;           // +5e0
  landingTimer694: number;
  dt: number;                   // +1dc8; physics clocks +5f4/+5f8 belong to host
}

export interface GredAirMeleeConfig {
  seedSlot: number;              // config+0
  proximityRange: number;        // config+4, full 3D test 668cc
  pursuitTimer: number;          // signed16 config+8
  recoveryTimer: number;         // signed16 config+a
  driftScale: number;            // config+c
  launchSpeed: number;           // config+10
  transitionScale: number;       // config+14, all four velocity scalars
  recoveryDamping: number;       // config+18, 6ed8c hSpeed/yVel only
}

/** Verified config80365744, RED action1/variant4 ONLY. */
export const GRED_AIR_MELEE_CONFIG: Readonly<GredAirMeleeConfig> = Object.freeze({
  seedSlot: 12,
  proximityRange: 200,
  pursuitTimer: 20,
  recoveryTimer: 0,
  driftScale: Math.fround(.95),
  launchSpeed: 60,
  transitionScale: .25,
  recoveryDamping: Math.fround(.9),
});

/** Every dependency is mandatory. Hooks may mutate state like source callees.
 * A separate RomActor must be synchronized before AND after each hook: starting
 * or ticking a stream can change contact, aim, dash and blend bytes immediately.
 * Runtime target roots/animated bones, terrain and inherited stream rate are
 * host adapters; no source collision/HP synchronization is performed here.
 */
export interface GredAirMeleeHooks {
  /** 66838: absent target -> -1 before force1dd&80 -> 1; otherwise XZ range
   * to captured +518 <= range * actor+b4. This is not the phase-2 3D test. */
  range66838(state: GredAirMeleeState, range: number): number;
  /** 668cc: absent target -> -1 before force1dd&80 -> 1; otherwise full 3D
   * distance to captured +518 <= range * actor+b4. Only >0 advances phase 2. */
  proximity668cc(state: GredAirMeleeState, range: number): number;
  face6d144(state: GredAirMeleeState, mode: 0xc0): number;
  /** Writes +54e using the descriptor AC rate * dt, NOT part-pitch rate768. */
  pitch6e514(state: GredAirMeleeState, mode: 0xc0): void;
  /** Writes +18da using part-pitch rate768. The caller decides when to copy
   * +18da to +54e; phases 0 and 1 deliberately do not perform that copy. */
  pitch6e1ac(state: GredAirMeleeState, mode: 0xc0, part: 1): void;
  tickStream(state: GredAirMeleeState, mask: 15): void;
  /** 4beb8's fixed trailing arguments are -1, -1. Rate -1 requests inherited
   * rate, which the host must resolve explicitly (the bounded RED lane uses 1). */
  startStream(state: GredAirMeleeState, mask: 15, group: 3, slot: number, rate: -1): void;
  /** Return the source probe's accepted-ground result, not generic y <= 0. */
  groundProbe677b0(state: GredAirMeleeState): number;
  physics67310(state: GredAirMeleeState, gravity: 1, yaw: number): void;
  /** 92dcc transition metadata/cosmetics; not an additional movement step. */
  transition92dcc(state: GredAirMeleeState, value: 0): void;
  landing6a750(state: GredAirMeleeState, cue: 7): void;
  /** Full 6a5a4 housekeeping/upper cue6, including stream-authored launch
   * override1d9b. Existing partial idle-return adapters must not invent values. */
  airReturn6a5a4(state: GredAirMeleeState): void;
}

const f32 = Math.fround;
const s8 = (value: number): number => (value << 24) >> 24;
const s16 = (value: number): number => (value << 16) >> 16;
const BAM_RADIANS = .0000958738019107841; // FLOAT_80437078
const AXES = ['x', 'y', 'z'] as const;

/** The host supplies every field; only a fresh engine's phase defaults to 0.
 * Clone mutable vectors while retaining the source target object's identity.
 * This does not run phase 0 or reset source fields before their authored writes.
 */
export function createGredAirMeleeState(
  initial: Omit<GredAirMeleeState, 'phase'> & { phase?: number },
): GredAirMeleeState {
  return {
    ...initial,
    phase: initial.phase ?? 0,
    pos: { ...initial.pos },
    savedGroundPos: { ...initial.savedGroundPos },
    motion: { ...initial.motion },
    poseAccum7c: { ...initial.poseAccum7c },
  };
}

function drift(state: GredAirMeleeState, scale: number): void {
  for (const axis of AXES) {
    state.motion[axis] = f32(state.motion[axis] * scale);
    state.pos[axis] = f32(state.pos[axis] + state.motion[axis]);
  }
}

/** 6ed8c uses linear fractional-dt loss, not pow(scale, dt). Original PPC
 * edc4/edd0 are fnmsubs: do not separately f32-round the product before the
 * subtraction. JS arithmetic here is not an instruction-level PPC parity claim.
 */
export function dampGredAirMelee(state: GredAirMeleeState, scale: number): void {
  if (state.dt === 1) {
    state.hSpeed = f32(state.hSpeed * scale);
    state.yVel = f32(state.yVel * scale);
  } else {
    const loss = f32(f32(1 - scale) * state.dt);
    state.hSpeed = f32(state.hSpeed - state.hSpeed * loss);
    state.yVel = f32(state.yVel - state.yVel * loss);
  }
}

function pitch(state: GredAirMeleeState, hooks: GredAirMeleeHooks, copyPart: boolean): void {
  if ((state.aimMode1d10 & 2) === 0) {
    hooks.pitch6e514(state, 0xc0);
  } else {
    hooks.pitch6e1ac(state, 0xc0, 1);
    if (copyPart) state.pitch54e = s16(state.shift18da);
  }
}

/** 45238/45204 round the signed-BAM angle and trig result to f32. Math.cos/sin
 * substitute for the source math library, not instruction-level libm parity.
 */
function chaseVelocity(state: GredAirMeleeState, speed: number): void {
  const angle = f32(s16(state.pitch54e) * BAM_RADIANS);
  state.hSpeed = f32(speed * f32(Math.cos(angle)));
  state.yVel = f32(speed * -f32(Math.sin(angle)));
}

function startNextStream(state: GredAirMeleeState, hooks: GredAirMeleeHooks): void {
  const slot = s8(state.streamSlot6ea);
  state.streamSlot6ea = s8(slot + 1);
  hooks.startStream(state, 15, 3, slot, -1);
}

function clearAction(state: GredAirMeleeState): void {
  state.actionFlag73f = 0;
  state.controlWord = (state.controlWord & 0xfffffffc) >>> 0;
}

/** One source phase dispatch. No synthetic catch-up loop, common pitch shift,
 * rechain, idle reset, animation wait or added gameplay timing is introduced.
 */
export function tickGredAirMelee(
  state: GredAirMeleeState,
  config: Readonly<GredAirMeleeConfig>,
  hooks: GredAirMeleeHooks,
): void {
  if (state.noTargetLatch541 !== 0) state.target = null;
  switch (state.phase) {
    case 0:
      state.phase++;
      state.handlerTimer = 30; // FLOAT_8043ae00
      state.pitch54e = 0;
      state.alt745 = 0;
      state.retap746 = 0;
      if ((hooks.range66838(state, state.rangeRow86c) | 0) < 1) {
        state.noTargetLatch541 = 1;
        state.target = null;
        state.lockYaw = s16(state.heading72);
        state.activeYaw = s16(state.heading72);
      }
      if (state.target === null) state.activeYaw = s16(state.heading72);
      state.hSpeed = 0;
      state.yVel = 0;
      state.hDecel = 0;
      state.gravityCoeff = 0;
      state.poseAccum7c = { x: 0, y: 0, z: 0 };
      state.streamSlot6ea = s8(config.seedSlot);
      startNextStream(state, hooks);
      hooks.face6d144(state, 0xc0);
      pitch(state, hooks, false);
      for (const axis of AXES) {
        state.motion[axis] = f32(state.pos[axis] - state.savedGroundPos[axis]);
      }
      drift(state, config.driftScale);
      hooks.groundProbe677b0(state);
      return;
    case 1:
      if (state.streamHold1b03 !== 0) hooks.tickStream(state, 15);
      drift(state, config.driftScale);
      hooks.groundProbe677b0(state);
      pitch(state, hooks, false);
      state.handlerTimer = f32(state.handlerTimer - state.dt);
      // Preserve the source's short-circuit: timeout does not call face6d144.
      if (state.handlerTimer <= 0 || hooks.face6d144(state, 0xc0) !== 0) {
        state.phase++;
        state.handlerTimer = s16(config.pursuitTimer);
        hooks.transition92dcc(state, 0);
      }
      return;
    case 2:
      if (s8(state.contactP0) === 0 || state.streamHold1b03 !== 0) hooks.tickStream(state, 15);
      hooks.face6d144(state, 0xc0);
      pitch(state, hooks, true);
      chaseVelocity(state, config.launchSpeed);
      hooks.physics67310(state, 1, s16(state.lockYaw));
      hooks.groundProbe677b0(state);
      state.handlerTimer = f32(state.handlerTimer - state.dt);
      if (state.handlerTimer <= 0 || (hooks.proximity668cc(state, config.proximityRange) | 0) > 0) {
        state.phase++;
        state.handlerTimer = s16(config.recoveryTimer);
        state.hSpeed = f32(state.hSpeed * config.transitionScale);
        state.hDecel = f32(state.hDecel * config.transitionScale);
        state.yVel = f32(state.yVel * config.transitionScale);
        state.gravityCoeff = f32(state.gravityCoeff * config.transitionScale);
      }
      return;
    case 3:
      if (state.input1d9 !== 0) state.alt745 = 1;
      if (s8(state.contactP0) === 0 || state.streamHold1b03 !== 0) hooks.tickStream(state, 15);
      hooks.face6d144(state, 0xc0);
      pitch(state, hooks, true);
      dampGredAirMelee(state, config.recoveryDamping);
      hooks.physics67310(state, 1, s16(state.lockYaw));
      hooks.groundProbe677b0(state);
      state.handlerTimer = f32(state.handlerTimer - state.dt);
      if (state.handlerTimer <= 0) state.phase++;
      return;
    case 4: {
      if ((state.inputEdges5d4 & 0x40) !== 0) state.retap746 = 1;
      if (state.input1d9 !== 0) state.alt745 = 1;
      hooks.tickStream(state, 15);
      if (s8(state.contactP0) < 0) state.shift18da = s16(state.shift18da) >> 1;
      // NEO streams33/34 use this continuation. RED, BLACK and NEO's final
      // stream keep auxiliary P1=0, so they cannot add another strike.
      if (s8(state.contactP1) < 0 && state.retap746 !== 0 && state.alt745 !== 0) {
        state.retap746 = 0;
        state.alt745 = 0;
        startNextStream(state, hooks);
        if (s8(state.dashStrength1d0f) < 1) return;
        state.dashStrength1d0f = 0;
        chaseVelocity(state, config.launchSpeed);
        return;
      }
      if (s8(state.aimMode1d10) > 0) {
        hooks.face6d144(state, 0xc0);
        pitch(state, hooks, true);
      }
      if (s8(state.dashStrength1d0f) > 0) {
        state.dashStrength1d0f = 0;
        chaseVelocity(state, config.launchSpeed);
      }
      if (s8(state.dashStrength1d0f) < 0) {
        state.dashStrength1d0f = 0;
        state.gravityCoeff = state.descriptorGravity6c;
      }
      dampGredAirMelee(state, config.recoveryDamping);
      hooks.physics67310(state, 1, s16(state.lockYaw));
      const landed = hooks.groundProbe677b0(state);
      if (landed !== 0 && s8(state.contactP0) < 0) {
        clearAction(state);
        hooks.landing6a750(state, 7);
        state.landingTimer694 = f32(1 + state.dt);
        return;
      }
      if (state.wallContact !== 0) {
        clearAction(state);
        hooks.airReturn6a5a4(state);
      }
      return;
    }
    default:
      throw new RangeError(`Invalid 80178394 phase ${state.phase}`);
  }
}
