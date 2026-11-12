/** Direct ff30c startup fixtures. They verify own-history arithmetic and call
 * order, not complete family X timing, callbacks, projectile or terrain parity. */
import {createSharedXSpecial, SHARED_X} from './families/shared-x-special.js';
import {createRomActor, type Vec3} from './rom/actor.js';
const f = Math.fround;
const v = (x: number, y: number, z: number): Vec3 => ({x, y, z});
function assert(ok: unknown, message: string): asserts ok {
  if (!ok) throw Error(`[sharedXCarry] ${message}`);
}
function same(actual: unknown, expected: unknown, message: string): void {
  assert(JSON.stringify(actual) === JSON.stringify(expected),
    `${message}: ${JSON.stringify(actual)} != ${JSON.stringify(expected)}`);
}
function fixture() {
  const a = Object.assign(createRomActor(), {
    lockTarget: null as Vec3 | null,
    grounded: true,
    onStartStream: (_g: number, _s: number, _m: number) => true,
  });
  a.actionIndex = 2;
  a.pos = v(100, 200, 300);
  a.targetCache5e8 = v(99, 198, 296);
  a.savedGroundPos = v(90, 190, 290);
  a.hSpeed = 9; a.hDecel = 8; a.yVel = 7; a.gravityCoeff = 6;
  a.poseAccum7c = 5; a.poseAccum7e = 4; a.poseAccum80 = 3;
  a.accumulator80c = 2;
  return a;
}
export function runSharedXCarrySelfTest(): void {
  let callbacks = 0;
  const drive = createSharedXSpecial({groundSlot: 0, airSlot: 1,
    onHit: () => { callbacks++; }}, {});
  for (const target of [null, v(1, 2, 3), v(90000, -5000, 70000)]) {
    const a = fixture(); a.lockTarget = target; drive(a);
    const motion = v(f(f(100 - 99) * f(.95)), f(f(200 - 198) * f(.95)), f(f(300 - 296) * f(.95)));
    same(a.motion, motion, 'own5e8 carry does not depend on target presence or distance');
    same(a.pos, v(f(100 + motion.x), f(200 + motion.y), f(300 + motion.z)), 'f32 carry is added once');
    same([a.hSpeed, a.hDecel, a.yVel, a.gravityCoeff, a.poseAccum7c, a.poseAccum7e, a.poseAccum80, a.accumulator80c],
      Array(8).fill(0), 'source startup resets scalars, pose and afterimage accumulator');
    assert(a.fbPhaseSlots[0] === 1 && a.streamSlot === 1, 'phase and stream cursor advance');
  }
  assert(callbacks === 0, 'phase0 does not invoke the phase1 callback');
  for (const target of [null, v(10000, 200, -10000)]) {
    const a = fixture(); a.lockTarget = target; a.targetCache5e8 = {...a.pos};
    a.motion = v(100, -200, 300); drive(a);
    same(a.motion, v(0, 0, 0), 'stationary own history clears stale motion even with no target');
    same(a.pos, v(100, 200, 300), 'stationary entry cannot teleport toward or away from a target');
  }
  {
    const a = fixture(), events: string[] = [];
    const previous = {...a.savedGroundPos};
    a.physicsRuntime = {
      clampToGround: () => { throw Error('explicit motion probe takes precedence'); },
      probeMotion: (old, pos, vy) => {
        events.push('probe'); same(old, previous, '677b0 host probe receives saved own position');
        same([a.hSpeed, a.hDecel, vy, a.gravityCoeff, a.poseAccum7c, a.poseAccum7e, a.poseAccum80],
          Array(7).fill(0), 'source resets precede terrain probe');
        assert(pos.z > 300 && a.accumulator80c === 2 && a.fbPhaseSlots[0] === 1,
          'phase increment and carry precede probe;80c remains until after stream');
        pos.x = 80; pos.y = 150; return {velY: 0, grounded: true};
      },
    };
    a.onStartStream = (group, slot, mask) => {
      events.push('stream'); same([group, slot, mask], [4, 0, 15], 'existing config stream selection retained');
      same(a.pos, v(80, 150, f(300 + f(4 * f(.95)))), 'stream observes terrain-adjusted carry');
      assert(a.accumulator80c === 2, 'stream starts before80c reset'); return true;
    };
    drive(a); same(events, ['probe', 'stream'], 'source terrain-before-stream order');
    assert(a.accumulator80c === 0, '80c resets after stream callback');
  }
  {
    const a = fixture(); a.grounded = false;
    a.physicsRuntime = {clampToGround: (pos, vy) => {
      assert(pos.z > 300 && vy === 0, 'fallback clamp observes carried position');
      return {y: 123, velY: -2, grounded: false};
    }};
    a.onStartStream = (g, slot, mask) => {
      same([g, slot, mask], [4, 1, 15], 'existing live-air slot adapter retained'); return true;
    };
    drive(a); same([a.pos.y, a.yVel, a.grounded, a.streamSlot], [123, -2, false, 2], 'host clamp result and air cursor retained');
  }
  {
    const a = fixture(); a.pos = v(f(1e7), f(.000123), f(-98765.5));
    a.targetCache5e8 = v(f(-.3), f(-.000001), f(1.125));
    const before = {...a.pos}, history = {...a.targetCache5e8}; drive(a);
    for (const axis of ['x', 'y', 'z'] as const) {
      const expected = f(f(before[axis] - history[axis]) * f(.95));
      same(a.motion[axis], expected, 'stored subtract and scale round separately');
      same(a.pos[axis], f(before[axis] + expected), 'stored position addition rounds separately');
    }
  }
  {
    const a = fixture(); drive(a);
    const before = {...a.pos}, motion = {...a.motion};
    a.contactP0 = 0; drive(a);
    for (const axis of ['x', 'y', 'z'] as const) {
      same(a.motion[axis], motion[axis] * .95, 'phase1 retains legacy double decay');
      same(a.pos[axis], before[axis] + motion[axis] * .95, 'phase1 behavior is outside startup change');
    }
  }
  assert(SHARED_X.REPOSITION_SCALE === .95 && SHARED_X.ENTRY_CARRY === f(.95) &&
    SHARED_X.ENTRY_CARRY !== SHARED_X.REPOSITION_SCALE, 'dedicated phase0 constant does not alter later phases');
  console.log('[sharedXCarry] PASS: own-history f32 startup, no-target, pose/probe/stream/reset order and later-phase isolation');
}
