/** Grounded G RED-family ordinary B, action0/v0. Bounded control-flow port of
 * 8018d288/18d308, 18d350/18d438/18d534 and release18dcb0. Source bodies:
 * research/decomp/ghidra-export/chunk_0046.c:5070–5243; chunk_0047.c:237–281.
 * Terrain, target capture/aim, stream interpretation and projectile allocation
 * are explicit host seams. This is not an instruction-level console oracle.
 */
export interface GRedShotVec3 { x: number; y: number; z: number }
export type GRedShotFamily = 'red' | 'neo' | 'black';
export interface GRedShotEngineState {
  family: GRedShotFamily;
  phase: number;                    // signed byte +540
  dt: number;                       // mutable actor +1dc8, restored after phase1 tick
  pos: GRedShotVec3;                 // +20
  savedGroundPos: GRedShotVec3;      // +5e8 OWN position history, not a target
  motion: GRedShotVec3;              // +38
  poseAccum7c: GRedShotVec3;
  controlWord: number;               // +5e0
  hSpeed: number;
  yVel: number;
  hDecel: number;
  gravityCoeff: number;
  rootAngle1900: number;             // independent signed16 root wrapper field
  shift18da: number;                 // signed16, not melee pursuit pitch +54e
  sideBlend1dfc: number;             // signed16, separate from +1900/+18da
  latch745: number;
  timer560: number;
  repeatTimer558: number;
  streamSlot6ee: number;
  remaining6ef: number;              // signed byte; release decrements on allocation
  ammo774: number;                   // current cell0 source count after debit
  input5d4: number;
  input5d8: number;
  contactP0: number;                 // signed stream byte +1cef, NOT stream pointer
  completed1cee: number;             // stream completion, NOT physical wall collision
  actionFlag6e8: number;
  actionFlag73f: number;
  accumulator80c: number;
}

/** Hooks mutate live state like the original callees. Adapters backed by a
 * separate actor must synchronize both ways at every hook boundary. */
export interface GRedShotEngineHooks {
  aim6d0dc(state: GRedShotEngineState, mode: 0xc1, arg: 0): boolean;
  /** Omitted startFrame/blend mean original overrides -1/-1. Rate is inherited. */
  startStream(state: GRedShotEngineState, mask: 15, group: 2, slot: number,
    startFrame?: number, blend?: number): void;
  tickStream(state: GRedShotEngineState, mask: 15): void;
  ammo6dbe0(state: GRedShotEngineState, cell: 0, count: 1, debit: boolean): boolean;
  spawnC3be0(state: GRedShotEngineState, row: 43 | 101 | 102): void;
  capture6bf80(state: GRedShotEngineState): void;
  ground679d0(state: GRedShotEngineState): void;
  carryEffectB22f4?(state: GRedShotEngineState): void;
  groundIdle6a474(state: GRedShotEngineState): void;
  /** The source action bits are already clear. Do not fabricate a 20-frame
   * attack lockout from this helper's numeric argument. */
  idleTransition6a668(state: GRedShotEngineState, duration: 20): void;
  redispatch6a3d0(state: GRedShotEngineState, action: 0, variant: 3, phase: 0): void;
}

const f32 = Math.fround;
const s8 = (value: number): number => (value << 24) >> 24;
const s16 = (value: number): number => (value << 16) >> 16;
const AXES = ['x', 'y', 'z'] as const;
const DRIFT = f32(.95);
const ROOT_DECAY = f32(.96);
const RELEASE = { red: { repeat: 12, row: 43 }, neo: { repeat: 8, row: 101 },
  black: { repeat: 16, row: 102 } } as const;

function carry(state: GRedShotEngineState, hooks: GRedShotEngineHooks, effects: boolean): void {
  for (const axis of AXES) state.motion[axis] = f32(state.motion[axis] * DRIFT);
  for (const axis of AXES) state.pos[axis] = f32(state.pos[axis] + state.motion[axis]);
  hooks.ground679d0(state);
  // FLOAT8043b128=3; this is cosmetic carry feedback, not a movement clamp.
  if (effects && Math.hypot(state.motion.x, state.motion.y, state.motion.z) > 3) {
    hooks.carryEffectB22f4?.(state);
  }
}

function release(state: GRedShotEngineState, hooks: GRedShotEngineHooks): void {
  const family = RELEASE[state.family];
  state.timer560 = 20;
  state.streamSlot6ee = 1;
  state.repeatTimer558 = family.repeat;
  if (hooks.ammo6dbe0(state, 0, 1, true)) {
    hooks.spawnC3be0(state, family.row);
    state.remaining6ef = s8(state.remaining6ef - 1);
  }
  if (s16(state.ammo774) < 1) state.remaining6ef = 0;
}

function cleanup(state: GRedShotEngineState, hooks: GRedShotEngineHooks): void {
  state.actionFlag6e8 = 0;
  state.actionFlag73f = 0;
  state.controlWord = (state.controlWord & 0xfffffffc) >>> 0;
  hooks.groundIdle6a474(state);
  hooks.idleTransition6a668(state, 20);
}

/** One wrapper update and exactly one source phase dispatch. No common timer
 * decrement, speculative release, physics integration or phase catch-up. */
export function tickGRedShotEngine(state: GRedShotEngineState, hooks: GRedShotEngineHooks): void {
  state.rootAngle1900 = s16(Math.trunc(f32(s16(state.rootAngle1900) * ROOT_DECAY)));
  state.shift18da = s16(state.shift18da) >> 1;
  state.sideBlend1dfc = s16(state.sideBlend1dfc) >> 1;
  switch (s8(state.phase)) {
    case 0:
      state.phase = s8(state.phase + 1);
      state.latch745 = 0;
      state.timer560 = 30;
      hooks.aim6d0dc(state, 0xc1, 0);
      hooks.startStream(state, 15, 2, s8(state.streamSlot6ee));
      state.controlWord = (state.controlWord & 0xffffff4f) >>> 0;
      state.gravityCoeff = 0;
      state.yVel = 0;
      state.hDecel = 0;
      state.hSpeed = 0;
      state.poseAccum7c.z = 0;
      state.poseAccum7c.y = 0;
      state.poseAccum7c.x = 0;
      for (const axis of AXES) state.motion[axis] = f32(state.pos[axis] - state.savedGroundPos[axis]);
      carry(state, hooks, false);
      state.accumulator80c = 0;
      return;
    case 1: {
      const dt = state.dt;
      if (s8(state.contactP0) !== 0) state.dt = 0;
      hooks.tickStream(state, 15);
      state.dt = dt;
      const ready = hooks.aim6d0dc(state, 0xc1, 0);
      // Preserve source || short circuit: readiness does not consume timer560.
      if (!ready) state.timer560 = f32(state.timer560 - state.dt);
      if ((ready || state.timer560 <= 0) && s8(state.contactP0) !== 0) {
        state.phase = s8(state.phase + 1);
        release(state, hooks);
      }
      carry(state, hooks, true);
      return;
    }
    case 2:
      if ((state.input5d4 & 0x20) !== 0) state.latch745 = 1;
      hooks.tickStream(state, 15);
      if (state.repeatTimer558 <= 0) {
        if (s8(state.latch745) !== 0) {
          if (!hooks.ammo6dbe0(state, 0, 1, false)) {
            cleanup(state, hooks);
            return;
          }
          hooks.capture6bf80(state);
          state.latch745 = 0;
          if ((state.controlWord & 0x40) !== 0) {
            hooks.redispatch6a3d0(state, 0, 3, 0);
            return;
          }
          state.phase = s8(state.phase - 1);
          if (s8(state.contactP0) < 0) hooks.startStream(state, 15, 2, 1);
          else hooks.startStream(state, 15, 2, 1, 4, 1);
          return;
        }
      } else state.repeatTimer558 = f32(state.repeatTimer558 - state.dt);
      if ((state.input5d8 & 0xf0) !== 0 || (state.input5d4 & 1) !== 0 || s8(state.completed1cee) !== 0) {
        cleanup(state, hooks);
        return;
      }
      carry(state, hooks, true);
      return;
  }
}
