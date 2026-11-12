/** Standalone control-flow port of 0x80179280, table 0x80352b40.
 * Source: docs-site/public/chunks/chunk_0044.c:3726–3930. This is not a
 * playable integration: terrain, facing, streams and idle dispatch are explicit
 * host dependencies, never substituted with the legacy shared-engine geometry.
 */
export interface FinisherVec3 { x: number; y: number; z: number }
export interface NeoGredFinisherState {
  phase: number;                 // +540
  noTargetLatch541: number;      // +541 persists; nonzero clears +cc on EVERY entry
  shift18da: number;
  target: object | null;         // +cc; host hooks must observe mutations
  rangeRow868: number;           // +868 + (signed byte +584 % 3) * 12
  targetDistance760: number;     // full 3D distance / actor scale, NOT speed
  dashStrength1d0f: number;       // signed stream byte
  activeYaw: number;             // +5ac
  lockYaw: number;               // +5ae
  handlerTimer: number;          // +558
  pos: FinisherVec3;             // +20
  savedGroundPos: FinisherVec3;   // +5e8 older own-position history (host targetCache5e8), NOT +2c ground position
  motion: FinisherVec3;          // +38
  hSpeed: number; yVel: number; hDecel: number; gravityCoeff: number;
  blendFloor80c: number;
  retap746: number; alt745: number;
  input1d9: number; inputEdges5d4: number;
  contactP0: number; contactP1: number; // signed +1cef/+1cf0 (raw bytes accepted)
  streamHold1b03: number;
  hold71c: number;
  wallContact: number;           // +1cee animation completion, NOT wall collision
  actionFlag73f: number;
  controlWord: number;
  dt: number;                   // +1dc8, not physics +5f4/+5f8
}
export interface NeoGredFinisherConfig {
  slot: number; timer: number; proximity: number;
  driftScale: number; approachDamping: number; brakeScale: number;
  recoveryDamping: number;
  launchHSpeed: number; launchHDecel: number; launchYVel: number; launchGravity: number;
  chainCallback: ((state: NeoGredFinisherState) => void) | null;
}
/** Wrapper 8018e1f4 -> config 803657c4, action1/variant6 ONLY. */
export const NEO_GRED_FINISHER_CONFIG: Readonly<NeoGredFinisherConfig> = Object.freeze({
  slot: 27, timer: 20, proximity: 200,
  driftScale: Math.fround(.95), approachDamping: Math.fround(.95),
  brakeScale: .25, recoveryDamping: Math.fround(.95),
  launchHSpeed: 0, launchHDecel: 0, launchYVel: 60, launchGravity: -2,
  chainCallback: null,
});
/** Every dependency is mandatory. Hooks may mutate state just as the source
 * callees do. An adapter must synchronize any separate RomActor before/after
 * each hook, not only once per tick (streams can change contact/yaw/hold bytes).
 * +5f4/+5f8 physics clocks and collision inputs belong to the host.
 */
export interface NeoGredFinisherHooks {
  /** 66838: -1 without target; input1dd&80 -> 1; otherwise XZ distance from
   * pos to captured +518 <= range * actor+b4. NOT full 3D or airborne test. */
  range66838(state: NeoGredFinisherState, range: number): number;
  face6d144(state: NeoGredFinisherState, mode: 0xc0): number;
  tickStream(state: NeoGredFinisherState, mask: 15): void;
  /** 4beb8 also receives the fixed trailing arguments -1, -1. Adapter must
   * preserve those defaults when invoking a fuller stream starter. */
  startStream(state: NeoGredFinisherState, mask: 15, group: 3, slot: number, rate: -1): void;
  groundProbe677b0(state: NeoGredFinisherState): void;
  groundMove670dc(state: NeoGredFinisherState, yaw: number): void;
  physics67310(state: NeoGredFinisherState, gravity: 1, yaw: number): void;
  setLaunch66530(state: NeoGredFinisherState, value: 45): void;
  /** 800b2190 allocates a cosmetic trail child in mode0; no bank-hold write. */
  spawnTrailB2190(state: NeoGredFinisherState, value: 0): void;
  syncB22f4(state: NeoGredFinisherState): void;
  /** Full 6a5a4 housekeeping and upper cue6, including stream-authored
   * +1d9b launch override. Existing romAirKnockoutReturn omits some fields. */
  airReturn6a5a4(state: NeoGredFinisherState): void;
}
const f32 = Math.fround;
const s8 = (n: number): number => (n << 24) >> 24;
const s16 = (n: number): number => (n << 16) >> 16;
/** 6ed8c: linear fractional-dt damping, not pow(scale, dt). */
export function dampNeoGredFinisher(state: NeoGredFinisherState, scale: number): void {
  if (state.dt === 1) {
    state.hSpeed = f32(state.hSpeed * scale);
    state.yVel = f32(state.yVel * scale);
  } else {
    const loss = f32(f32(1 - scale) * state.dt);
    state.hSpeed = f32(-(f32(state.hSpeed * loss) - state.hSpeed));
    state.yVel = f32(-(f32(state.yVel * loss) - state.yVel));
  }
}
function drift(s: NeoGredFinisherState, scale: number): void {
  for (const axis of ['x', 'y', 'z'] as const) {
    s.motion[axis] = f32(s.motion[axis] * scale);
    s.pos[axis] = f32(s.pos[axis] + s.motion[axis]);
  }
}
/** One dispatch only. Source callbacks may change phase; no synthetic rechain,
 * catch-up loop, idle reset or timing gate is introduced here. Arithmetic is
 * f32-rounded at field writes; not a retail instruction-level parity claim. */
export function tickNeoGredFinisher(
  s: NeoGredFinisherState,
  c: Readonly<NeoGredFinisherConfig>,
  h: NeoGredFinisherHooks,
): void {
  s.shift18da = s16(s.shift18da) >> 1;
  if (s.noTargetLatch541 !== 0) s.target = null;
  switch (s.phase) {
    case 0:
      s.phase++;
      s.retap746 = 0; s.alt745 = 0;
      if ((h.range66838(s, s.rangeRow868) | 0) < 1) {
        s.noTargetLatch541 = 1; s.target = null; s.activeYaw = s16(s.lockYaw);
      }
      s.handlerTimer = 60; // FLOAT_8043ae20
      h.face6d144(s, 0xc0);
      for (const axis of ['x', 'y', 'z'] as const) {
        s.motion[axis] = f32(s.pos[axis] - s.savedGroundPos[axis]);
      }
      drift(s, c.driftScale);
      h.groundProbe677b0(s);
      h.startStream(s, 15, 3, s16(c.slot), -1); // FLOAT_8043ae04
      return;
    case 1:
      if (s8(s.contactP0) === 0 || s.streamHold1b03 !== 0) h.tickStream(s, 15);
      drift(s, c.driftScale);
      h.groundProbe677b0(s);
      s.handlerTimer = f32(s.handlerTimer - s.dt);
      if (s.handlerTimer <= 0 || h.face6d144(s, 0xc0) !== 0) {
        s.phase++;
        s.handlerTimer = s16(c.timer);
        const distance = s.target === null ? s.rangeRow868
          : f32(f32(s.targetDistance760 * s8(s.dashStrength1d0f)) * .0625); // ae28
        s.hSpeed = f32(distance / s16(c.timer));
        s.hDecel = 0; s.blendFloor80c = 0;
      }
      h.syncB22f4(s);
      return;
    case 2:
      if (s.input1d9 !== 0) s.alt745 = 1;
      if (s8(s.contactP0) === 0 || s.streamHold1b03 !== 0) h.tickStream(s, 15);
      h.face6d144(s, 0xc0);
      dampNeoGredFinisher(s, c.approachDamping);
      h.groundMove670dc(s, s16(s.lockYaw));
      s.handlerTimer = f32(s.handlerTimer - s.dt);
      if (s.handlerTimer <= 0 || h.range66838(s, c.proximity) !== 0) {
        s.phase++;
        s.hSpeed = f32(s.hSpeed * c.brakeScale);
      }
      h.syncB22f4(s);
      return;
    case 3:
      if (s.input1d9 !== 0) s.alt745 = 1;
      if (s.hold71c === 0) {
        h.tickStream(s, 15);
        dampNeoGredFinisher(s, c.recoveryDamping);
        h.groundMove670dc(s, s16(s.lockYaw));
        if (s8(s.contactP1) > 0) {
          s.phase++;
          s.hSpeed = c.launchHSpeed; s.hDecel = c.launchHDecel;
          s.yVel = c.launchYVel; s.gravityCoeff = c.launchGravity;
          h.setLaunch66530(s, 45);
          h.spawnTrailB2190(s, 0);
        }
        h.syncB22f4(s);
      }
      return;
    case 4:
      if ((s.inputEdges5d4 & 0x40) !== 0) s.retap746 = 1;
      if (s.input1d9 !== 0) s.alt745 = 1;
      h.tickStream(s, 15);
      if (s8(s.contactP1) < 0 && (s.retap746 & s.alt745) !== 0 && c.chainCallback !== null) {
        c.chainCallback(s);
        return;
      }
      h.physics67310(s, 1, s16(s.lockYaw)); // FLOAT_8043ae1c
      h.groundProbe677b0(s);
      if (s.wallContact !== 0) {
        s.actionFlag73f = 0;
        s.controlWord = (s.controlWord & 0xfffffffc) >>> 0;
        h.airReturn6a5a4(s);
      }
      return;
    default:
      throw new RangeError(`Invalid 80179280 phase ${s.phase}`);
  }
}
