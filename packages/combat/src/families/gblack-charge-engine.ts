/** Bounded control-flow port of G BLACK's 80179d20, phase table804347a8.
 * Wrapper8018ee08 selects config8036586c. Source phase bodies:
 * research/decomp/ghidra-export/chunk_0044.c:4095–4191; setup8018ee30 in
 * chunk_0047.c. This two-phase engine is independent of G RED's80179814.
 * Target geometry, authored streams, projectile spawn, terrain and physics
 * remain explicit host dependencies. This is not an instruction-level oracle.
 */
export interface GblackChargeVec3 { x: number; y: number; z: number }

export interface GblackChargeState {
  phase: number;                   // signed byte +540
  subphase541: number;             // signed byte; external writer is not inferred
  streamSlot6ea: number;           // signed byte, advanced before startStream
  lockYaw: number;                 // signed16 +5ae
  pos: GblackChargeVec3;           // +20
  savedGroundPos: GblackChargeVec3; // +5e8 OWN position history, not target
  motion: GblackChargeVec3;        // +38
  hSpeed: number;                  // +44
  yVel: number;                    // +48
  hDecel: number;                  // +4c
  gravityCoeff: number;            // +50
  poseAccum7c: GblackChargeVec3;    // signed16 +7c/+7e/+80
  shift18da: number;               // independent signed16 part-pitch channel
  contactP0: number;               // signed stream byte +1cef
  wallContact: number;             // +1cee stream completion, NOT wall collision
  faceGate1d10: number;            // stream byte; nonzero permits aim in phase1
  dashStrength1d0f: number;        // signed stream byte
  descriptorGravity6c: number;    // descriptor +6c, host supplies actual data
  actionFlag73f: number;
  controlWord: number;             // +5e0
  landingTimer694: number;
  dt: number;                      // +1dc8; physics clocks belong to the host
}

export interface GblackChargeConfig {
  streamSlot: number;              // config+0 low signed byte, no air-slot branch
  driftScale: number;              // config+4 f32
}

/** Verified numeric fields of config8036586c. Its pointer8018ee30 is supplied
 * explicitly as setupCallback, rather than inferred from these fields. */
export const GBLACK_CHARGE_CONFIG: Readonly<GblackChargeConfig> = Object.freeze({
  streamSlot: 3,
  driftScale: Math.fround(.95),
});

/** Hooks may mutate state like source callees. A host backed by a separate
 * actor must synchronize before AND after each hook: stream, aiming, physics
 * and ground callbacks can change fields read later in the same dispatch. */
export interface GblackChargeHooks {
  face6d144(state: GblackChargeState, mode: 0xc1): void;
  pitch6e1ac(state: GblackChargeState, mode: 0xc1, part: 1): void;
  /** 18ee30: if actor type+3e8==0x62a, spawn16cc24(type0x10);
   * then always hDecel/hSpeed=0, yVel=4,
   * gravityCoeff=0. This is setup, not a later release callback. */
  setupCallback: ((state: GblackChargeState) => void) | null;
  tickStream(state: GblackChargeState, mask: 15): void;
  /** 4beb8 trailing args are -1,-1; rate -1 requests inherited playback. */
  startStream(state: GblackChargeState, mask: 15, group: 4, slot: number, rate: -1): void;
  /** The source ignores this probe's result in both phases. */
  groundProbe677b0(state: GblackChargeState): number;
  physics67310(state: GblackChargeState, gravity: 1, yaw: number): void;
  /** Full source return housekeeping, including action changes, is the host's
   * responsibility. The engine does not reset phase or synthesize idle. */
  airReturn6a5a4(state: GblackChargeState): void;
}

const f32 = Math.fround;
const s8 = (value: number): number => (value << 24) >> 24;
const s16 = (value: number): number => (value << 16) >> 16;
const AXES = ['x', 'y', 'z'] as const;

/** Preserve all authored fields until their source phase writes them. */
export function createGblackChargeState(
  initial: Omit<GblackChargeState, 'phase'> & { phase?: number },
): GblackChargeState {
  return {
    ...initial,
    phase: initial.phase ?? 0,
    pos: { ...initial.pos },
    savedGroundPos: { ...initial.savedGroundPos },
    motion: { ...initial.motion },
    poseAccum7c: { ...initial.poseAccum7c },
  };
}

function aim(state: GblackChargeState, hooks: GblackChargeHooks): void {
  hooks.face6d144(state, 0xc1);
  hooks.pitch6e1ac(state, 0xc1, 1);
}

function drift(state: GblackChargeState, scale: number): void {
  const factor = f32(scale);
  for (const axis of AXES) state.motion[axis] = f32(state.motion[axis] * factor);
  for (const axis of AXES) state.pos[axis] = f32(state.pos[axis] + state.motion[axis]);
}

/** Exactly one source phase dispatch. There is no beam pointer, charge timer,
 * input popcount, stream replay, release callback or inferred collision gate. */
export function tickGblackCharge(
  state: GblackChargeState,
  config: Readonly<GblackChargeConfig>,
  hooks: GblackChargeHooks,
): void {
  switch (s8(state.phase)) {
    case 0: {
      state.phase = s8(state.phase + 1);
      state.subphase541 = 0;
      state.streamSlot6ea = s8(config.streamSlot);
      aim(state, hooks);
      state.gravityCoeff = 0;
      state.yVel = 0;
      state.hDecel = 0;
      state.hSpeed = 0;
      state.poseAccum7c.z = 0;
      state.poseAccum7c.y = 0;
      state.poseAccum7c.x = 0;
      hooks.setupCallback?.(state);
      for (const axis of AXES) {
        state.motion[axis] = f32(state.pos[axis] - state.savedGroundPos[axis]);
      }
      drift(state, config.driftScale);
      hooks.groundProbe677b0(state);
      const slot = s8(state.streamSlot6ea);
      state.streamSlot6ea = s8(slot + 1);
      hooks.startStream(state, 15, 4, slot, -1);
      return;
    }
    case 1:
      hooks.tickStream(state, 15);
      if (s8(state.contactP0) < 0) {
        state.shift18da = s16(Math.trunc(f32(s16(state.shift18da) * f32(.9))));
      }
      if (s8(state.contactP0) < 1 || s8(state.subphase541) < 1) {
        if (s8(state.faceGate1d10) !== 0) aim(state, hooks);
        if (s8(state.dashStrength1d0f) < 0) {
          state.dashStrength1d0f = 0;
          state.gravityCoeff = state.descriptorGravity6c;
        }
        drift(state, config.driftScale);
        hooks.physics67310(state, 1, s16(state.lockYaw));
        hooks.groundProbe677b0(state);
        if (s8(state.wallContact) === 0) return;
      } else {
        state.gravityCoeff = state.descriptorGravity6c;
        // FLOAT_8043ae00 = 0x41f00000 (30), not G RED's landing base8.
        state.landingTimer694 = f32(30 + state.dt);
      }
      state.actionFlag73f = 0;
      state.controlWord = (state.controlWord & 0xfffffffc) >>> 0;
      state.hDecel = 0;
      state.hSpeed = 0;
      hooks.airReturn6a5a4(state);
      return;
    default:
      throw new RangeError(`Invalid G BLACK charge phase ${state.phase}`);
  }
}
