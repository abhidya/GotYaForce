/** Teleport Ninja pl0005 ordinary X, source root146d90 and phases146dcc,
 * 146ed8,146f6c,147094 (ghidra-export/chunk_0038.c:745–883).
 * This inert control-flow engine has no input admission, actor registration,
 * projectile, HIT, renderer or Battle dependency. Terrain, feedback, ammo,
 * recovery streams and SDK normalization remain explicit host boundaries.
 * It is not an instruction-level console oracle.
 */
export interface TeleportXVec3 { x: number; y: number; z: number }

export interface TeleportXEngineState {
  phase: number;                       // signed byte +540
  dt: number;                          // current actor +1dc8, read after each hook
  pos: TeleportXVec3;                  // +20
  savedOwnPos5e8: TeleportXVec3;        // OWN position history, never target geometry
  motion: TeleportXVec3;               // +38
  destination9c: TeleportXVec3;
  capturedTargetCc: boolean;           // only whether captured pointer +cc is non-null
  target518: TeleportXVec3;            // previously captured target point, not live retargeting
  recentMeleeTimer144: number;         // melee146560's recent-hit timer, not an object pointer
  modelScaleB4: number;
  controlWord: number;                 // +5e0
  airLatch54a: number;                 // captured ushort control bit40
  timer558: number;
  flags272: number;                    // ushort; bit2 suppresses defensive HIT registration
  visibility82: number;               // byte; zero is invisible
  movementFlag87: number;
  movementCue5e4: number;
  actionFlag73f: number;
  carriedSlot96: number;               // byte added to0x41 when restoring +82
  hSpeed: number;                      // +44
  yVel: number;                        // +48
  hDecel: number;                      // +4c
  gravityCoeff: number;                // +50
  descriptorGravity6c: number;         // descriptor4ac+6c
}

/** Hooks see live state at the exact source call boundary. Actor adapters must
 * synchronize both ways at every boundary. There is no speculative cleanup or
 * interruption policy here: the owner decides whether this action dispatches.
 */
export interface TeleportXEngineHooks {
  /** In-place SDK helper6ebb4. For mag>0 normalize; otherwise write [0,1,0].
   * The SDK's reciprocal-square-root rounding is deliberately not guessed. */
  normalize6ebb4(direction: TeleportXVec3): void;
  feedback061a8(state: TeleportXEngineState, code: 9 | 10): void;
  ground677b0(state: TeleportXEngineState): void;
  ammo6dbe0(state: TeleportXEngineState, cell: 2, count: 1, debit: true): boolean;
  cueF036c(state: TeleportXEngineState, code: 0xf2): void;
  /** 4beb8 float -1 selects the authored start frame; final2/1 mean BLEND2,
   * MODE1. They are not a start-frame2 or playback-rate1 override. */
  startStream(state: TeleportXEngineState, mask: 15, group: 0, slot: 0 | 13,
    startFrameOverride: -1, blendOverride: 2, modeOverride: 1): void;
  tickStream(state: TeleportXEngineState, mask: 15): void;
  groundIdle6a474(state: TeleportXEngineState): void;
  airReturn6a5a4(state: TeleportXEngineState): void;
}

export type TeleportXEngineOutcome =
  | { type: 'continue' }
  | { type: 'cleanup'; exit: 'ground' | 'air' }
  | { type: 'unsupported'; phase: number };

const f32 = Math.fround;
const s8 = (value: number): number => (value << 24) >> 24;
const AXES = ['x', 'y', 'z'] as const;
const CONTINUE = { type: 'continue' } as const;
const INTERPOLATION = f32(.1);          // FLOAT8043a300

function setupDrift(s: TeleportXEngineState, h: TeleportXEngineHooks): TeleportXEngineOutcome {
  //146ed8 is the first movement phase, not a projectile factory.
  h.feedback061a8(s, 9);
  s.flags272 = (s.flags272 | 2) & 0xffff;
  for (const axis of AXES) s.pos[axis] = f32(s.pos[axis] + s.motion[axis]);
  h.ground677b0(s);
  s.timer558 = f32(s.timer558 - s.dt);
  if (s.timer558 <= 0) {
    s.phase = s8(s.phase + 1);
    s.timer558 = 16;                    // FLOAT8043a2fc
    h.cueF036c(s, 0xf2);
  }
  return CONTINUE;
}

/** One source dispatch. Only phase0 deliberately calls phase1 in the same
 * invocation. No common physics, elapsed-time catch-up, max-duration timeout,
 * target refresh or recent-melee timer decrement is synthesized here. */
export function tickTeleportXEngine(s: TeleportXEngineState,
  h: TeleportXEngineHooks): TeleportXEngineOutcome {
  switch (s8(s.phase)) {
    case 0:
      s.phase = s8(s.phase + 1);
      s.timer558 = 4;                   // FLOAT8043a2f0
      s.airLatch54a = s.controlWord & 0x40;
      for (const axis of AXES) s.motion[axis] = f32(s.pos[axis] - s.savedOwnPos5e8[axis]);
      if (s.recentMeleeTimer144 <= 0 || !s.capturedTargetCc) {
        for (const axis of AXES) s.destination9c[axis] = f32(s.motion[axis] * 50);
        for (const axis of AXES) s.destination9c[axis] = f32(s.pos[axis] + s.destination9c[axis]);
      } else {
        for (const axis of AXES) s.destination9c[axis] = f32(s.target518[axis] - s.pos[axis]);
        h.normalize6ebb4(s.destination9c);
        const distance = f32(800 * s.modelScaleB4); // FLOAT8043a2f4
        for (const axis of AXES) s.destination9c[axis] = f32(s.destination9c[axis] * distance);
        for (const axis of AXES) s.destination9c[axis] = f32(s.pos[axis] + s.destination9c[axis]);
        s.airLatch54a = 0x40;
      }
      //66530(0x2d), including preservation of control80 and all unrelated bits.
      s.movementCue5e4 = 0x2d;
      s.movementFlag87 = 1;
      s.controlWord = (s.controlWord | 0x40) >>> 0;
      h.ammo6dbe0(s, 2, 1, true);       // return intentionally ignored by146dcc
      return setupDrift(s, h);         // same-call146ed8; never same-call146f6c
    case 1:
      return setupDrift(s, h);
    case 2: {
      h.feedback061a8(s, 9);
      s.flags272 = (s.flags272 | 2) & 0xffff;
      s.visibility82 = 0;
      const scale = f32(INTERPOLATION * s.dt);
      const remaining = f32(1 - scale);
      //46588: two PSQUATScale temporaries then PSVECAdd. Do not replace with
      //current+(destination-current)*scale, fused arithmetic, or a clamped lerp.
      for (const axis of AXES) {
        const destinationPart = f32(scale * s.destination9c[axis]);
        const currentPart = f32(remaining * s.pos[axis]);
        s.pos[axis] = f32(destinationPart + currentPart);
      }
      h.ground677b0(s);
      s.timer558 = f32(s.timer558 - s.dt);
      if (s.timer558 <= 0) {
        s.phase = s8(s.phase + 1);
        s.timer558 = 2;                 // FLOAT8043a304
        s.hDecel = 0;
        s.hSpeed = 0;
        s.yVel = 0;
        s.gravityCoeff = s.descriptorGravity6c;
        s.visibility82 = (s.carriedSlot96 + 0x41) & 0xff;
        h.startStream(s, 15, 0, (s.airLatch54a & 0xffff) === 0 ? 0 : 13, -1, 2, 1);
        h.feedback061a8(s, 10);
        h.cueF036c(s, 0xf2);
      }
      return CONTINUE;
    }
    case 3:
      s.flags272 = (s.flags272 | 2) & 0xffff;
      h.tickStream(s, 15);
      s.timer558 = f32(s.timer558 - s.dt);
      if (s.timer558 <= 0) {
        s.flags272 &= 0xfffd;
        s.actionFlag73f = 0;
        s.controlWord = (s.controlWord & 0xfffffffc) >>> 0;
        if ((s.controlWord & 0x40) === 0) {
          h.groundIdle6a474(s);
          return { type: 'cleanup', exit: 'ground' };
        }
        h.airReturn6a5a4(s);
        return { type: 'cleanup', exit: 'air' };
      }
      return CONTINUE;
    default:
      return { type: 'unsupported', phase: s8(s.phase) };
  }
}
