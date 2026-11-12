/** Bounded control-flow port of 80179814, phase table 80352b54.
 * G RED/NEO action3 wrapper8018ed80 selects config80365854. Source bodies:
 * research/decomp/ghidra-export/chunk_0044.c:3919–4093; wrapper chunk_0047.c.
 * BLACK's 80179d20 engine is separate and is deliberately excluded. Target
 * geometry, authored streams, terrain, physics and charge-projectile lifetime
 * remain explicit host dependencies. This is not an instruction-level oracle.
 */
export interface GredChargeVec3 { x: number; y: number; z: number }

export interface GredChargeState {
  phase: number;                   // signed byte +540
  releaseSubphase542: number;
  target: object | null;           // +cc
  heading72: number;
  activeYaw: number;               // signed16 +5ac
  lockYaw: number;                 // signed16 +5ae
  chargeTimer560: number;          // FLOAT, independent of the signed budget
  extensionBudget54e: number;      // signed16, not the melee pursuit pitch
  chargeState6f7: number;          // projectile observes this live field
  streamSlot6ea: number;           // signed byte, advanced before startStream
  aimTarget524: GredChargeVec3;     // saved target input to BOTH aim helpers
  pos: GredChargeVec3;              // +20
  savedGroundPos: GredChargeVec3;   // +5e8 OWN position history, not target
  motion: GredChargeVec3;           // +38
  hSpeed: number;                  // +44
  yVel: number;                    // +48
  hDecel: number;                  // +4c
  gravityCoeff: number;            // +50
  poseAccum7c: GredChargeVec3;      // signed16 +7c/+7e/+80
  controlWord: number;             // +5e0; bit40 chooses air slot
  freshInput5bc: number;           // raw press edges, NOT synthesized input5d4
  dashStrength1d0f: number;         // signed stream byte
  descriptorGravity6c: number;     // descriptor +6c, host supplies actual data
  shift18da: number;               // independent signed16 part-pitch channel
  contactP0: number;               // signed stream byte +1cef
  wallContact: number;             // +1cee stream completion, NOT wall collision
  actionFlag73f: number;
  landingTimer694: number;
  dt: number;                      // +1dc8; physics clocks belong to the host
}

export interface GredChargeConfig {
  groundSlot: number;              // config+0 low signed byte
  airSlot: number;                 // config+4 low signed byte
  driftScale: number;              // config+8 f32
  chargeTimer: number;             // config+c signed16 -> float560
  extensionBudget: number;         // config+e signed16 -> short54e
}

/** Verified config80365854 numeric fields. Its pointers8018eda8/8018edc4
 * must be supplied through setupCallback/releaseCallback below. In particular,
 * the setup is not silently inferred from these numeric config fields.
 */
export const GRED_CHARGE_CONFIG: Readonly<GredChargeConfig> = Object.freeze({
  groundSlot: 2,
  airSlot: 2,
  driftScale: Math.fround(.95),
  chargeTimer: 30,
  extensionBudget: 30,
});

/** Hooks may mutate state like source callees. If backed by a separate actor,
 * synchronize before AND after every hook: stream/physics/ground callbacks can
 * change fields used by the rest of the same dispatch. The source config's
 * nullable callbacks are explicit here, rather than assumed host side effects.
 */
export interface GredChargeHooks {
  face6d1a8(state: GredChargeState, mode: 0xc1, target: GredChargeVec3): void;
  /** 0x4000 is the target-pitch clamp, not a per-frame angular step. */
  pitch6e39c(state: GredChargeState, mode: 0xc1, part: 1, clamp: 0x4000,
    target: GredChargeVec3): void;
  /** 18eda8: lockYaw=heading72, yVel=8, gravityCoeff=0. */
  setupCallback: ((state: GredChargeState) => void) | null;
  /** 18edc4: e19a8 row15 retaining a reference to actor+6f7 for RED/NEO.
   * The engine does not allocate a projectile or snapshot its lifetime flag. */
  releaseCallback: ((state: GredChargeState) => void) | null;
  tickStream(state: GredChargeState, mask: 15): void;
  /** 4beb8 trailing args are -1,-1; rate -1 requests inherited playback. */
  startStream(state: GredChargeState, mask: 15, group: 4, slot: number, rate: -1): void;
  /** Return 677b0's accepted-ground result, not a generic y<=0 predicate. */
  groundProbe677b0(state: GredChargeState): number;
  physics67310(state: GredChargeState, gravity: 1, yaw: number): void;
  landing6a750(state: GredChargeState, cue: 7): void;
  /** Full source return housekeeping is a host responsibility. */
  airReturn6a5a4(state: GredChargeState): void;
  groundReturn6a474(state: GredChargeState): void;
}

const f32 = Math.fround;
const s8 = (value: number): number => (value << 24) >> 24;
const s16 = (value: number): number => (value << 16) >> 16;
const AXES = ['x', 'y', 'z'] as const;

/** No authored fields are reset before phase0. Mutable vectors are copied,
 * while the target object's identity is retained. */
export function createGredChargeState(
  initial: Omit<GredChargeState, 'phase'> & { phase?: number },
): GredChargeState {
  return {
    ...initial,
    phase: initial.phase ?? 0,
    aimTarget524: { ...initial.aimTarget524 },
    pos: { ...initial.pos },
    savedGroundPos: { ...initial.savedGroundPos },
    motion: { ...initial.motion },
    poseAccum7c: { ...initial.poseAccum7c },
  };
}

/** 6de44(actor,0x0f0f00): count ALL fresh raw button/direction edges. This
 * neither mutates the input word nor substitutes a held-button frame counter. */
export function popcountGredChargeEdges(rawEdges: number): number {
  let bits = rawEdges & 0x0f0f00;
  let count = 0;
  while (bits !== 0) {
    bits &= bits - 1;
    count++;
  }
  return count;
}

function aim(state: GredChargeState, hooks: GredChargeHooks): void {
  hooks.face6d1a8(state, 0xc1, state.aimTarget524);
  hooks.pitch6e39c(state, 0xc1, 1, 0x4000, state.aimTarget524);
}

function drift(state: GredChargeState, scale: number): void {
  const factor = f32(scale);
  for (const axis of AXES) state.motion[axis] = f32(state.motion[axis] * factor);
  for (const axis of AXES) state.pos[axis] = f32(state.pos[axis] + state.motion[axis]);
}

function advance(state: GredChargeState): void {
  state.phase = s8(state.phase + 1);
}

function clearAction(state: GredChargeState): void {
  state.actionFlag73f = 0;
  state.controlWord = (state.controlWord & 0xfffffffc) >>> 0;
}

/** Exactly one source phase dispatch: no catch-up loop, synthetic stream wait,
 * speculative release, common timer decrement or idle reset is introduced. */
export function tickGredCharge(
  state: GredChargeState,
  config: Readonly<GredChargeConfig>,
  hooks: GredChargeHooks,
): void {
  switch (s8(state.phase)) {
    case 0: {
      advance(state);
      state.chargeTimer560 = s16(config.chargeTimer);
      state.extensionBudget54e = s16(config.extensionBudget);
      state.streamSlot6ea = s8(config.groundSlot);
      if ((state.controlWord & 0x40) !== 0) state.streamSlot6ea = s8(config.airSlot);
      state.chargeState6f7 = 0;
      if (state.target === null) state.activeYaw = s16(state.heading72);
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
      aim(state, hooks);
      drift(state, config.driftScale);
      hooks.groundProbe677b0(state);
      if (s8(state.contactP0) > 0) {
        advance(state);
        state.releaseSubphase542 = 0;
        state.chargeState6f7 = 2;
        hooks.releaseCallback?.(state);
      }
      return;
    case 2: {
      state.chargeState6f7 = 2;
      const count = popcountGredChargeEdges(state.freshInput5bc);
      if (count !== 0) {
        // Source signed comparison permits a negative configured budget. Do
        // not silently clamp it to zero or consume more than the raw popcount.
        const amount = Math.min(count, s16(state.extensionBudget54e));
        state.extensionBudget54e = s16(state.extensionBudget54e - amount);
        state.chargeTimer560 = f32(state.chargeTimer560 + amount);
      }
      aim(state, hooks);
      drift(state, config.driftScale);
      if (s8(state.dashStrength1d0f) < 0) {
        state.dashStrength1d0f = 0;
        state.gravityCoeff = state.descriptorGravity6c;
      }
      hooks.physics67310(state, 1, s16(state.lockYaw));
      hooks.groundProbe677b0(state);
      if (state.chargeTimer560 <= 0) {
        hooks.tickStream(state, 15);
        if (s8(state.contactP0) < 0) {
          advance(state);
          state.chargeState6f7 = 0;
        }
      } else {
        state.chargeTimer560 = f32(state.chargeTimer560 - state.dt);
        if (s8(state.contactP0) >= 0) hooks.tickStream(state, 15);
      }
      return;
    }
    case 3: {
      state.shift18da = s16(Math.trunc(f32(s16(state.shift18da) * f32(.9))));
      hooks.physics67310(state, 1, s16(state.lockYaw));
      const landing = hooks.groundProbe677b0(state);
      if (landing !== 0 && s8(state.contactP0) < 0) {
        clearAction(state);
        hooks.landing6a750(state, 7);
        // FLOAT_8043ae34 = 0x41000000 (8), NOT air-melee's ae1c (1).
        state.landingTimer694 = f32(8 + state.dt);
        state.shift18da = 0;
        return;
      }
      hooks.tickStream(state, 15);
      if (s8(state.wallContact) !== 0) {
        clearAction(state);
        state.hDecel = 0;
        state.hSpeed = 0;
        if (landing === 0) hooks.airReturn6a5a4(state);
        else hooks.groundReturn6a474(state);
      }
      return;
    }
    default:
      throw new RangeError(`Invalid G RED charge phase ${state.phase}`);
  }
}
