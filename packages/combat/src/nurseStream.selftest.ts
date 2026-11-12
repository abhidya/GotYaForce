import { createRomActor } from './rom/actor.js';
import { steerNurseMotion, integrateNurseDrift } from './nurseMotion.js';
import { createNurseFarStreamClock, recoverNurseFarStream, createNurseStreamClock, tickNurseStream, resumeNurseStream, recoverNurseStream } from './nurseStream.js';
import { isCloseNurseX, NURSE_X } from './nurseX.js';
import type { BorgRuntime } from './types.js';
function assert(value: unknown, message: string): void {
  if (!value) throw new Error(`[nurseStream] ${message}`);
}
export function runNurseStreamSelfTest(): void {
  const a = createRomActor();
  Object.assign(a.motion, { x: 0, y: 3, z: 4 });
  a.hSpeed = 10; a.hDecel = -2; a.timescale = 0.5; a.tierScale = 2;
  integrateNurseDrift(a);
  assert(a.pos.y === 6 && a.pos.z === 8 && a.motion.y === 6 && a.motion.z === 8,
    '80067610 writes scaled XYZ motion and adds vertical displacement');
  assert(a.hSpeed === 9, 'drift decays speed after motion with status scale only');
  Object.assign(a.motion, { x: 0, y: 0, z: 0 });
  integrateNurseDrift(a); assert(a.hSpeed === 9, 'zero drift skips decay');
  Object.assign(a.pos, { x: 0, y: 0, z: 0 });
  Object.assign(a.motion, { x: 0, y: 0, z: 1 }); a.dt = 0.5;
  steerNurseMotion(a, { x: 10, y: 0, z: 0 });
  const cap = Math.fround(10 * 0.01745329238474369);
  assert(Math.abs(Math.atan2(a.motion.x, a.motion.z) - cap) < 1e-12,
    'source ten-degree steering is per call, not dt-scaled');
  Object.assign(a.motion, { x: 0, y: 0, z: 1 });
  steerNurseMotion(a, { x: 0, y: 0, z: -1 });
  assert(Math.abs(a.motion.x - Math.sin(cap)) < 1e-12,
    'opposite-vector steering uses source positive-Y fallback axis');
  Object.assign(a.motion, { x: 0, y: 1, z: 0 });
  steerNurseMotion(a, a.pos);
  assert(a.motion.y === 1, 'coincident target preserves normalized direction');
  const far = createNurseFarStreamClock(), events: number[] = [];
  for (let i = 0; i < 33; i++) {
    const e = tickNurseStream(far, 1);
    if (e.aux !== undefined) events.push(e.aux);
  }
  assert(events.join(',') === '9,10,1' && far.frame === 33,
    'far source absolute waits14/21/22/32 retain kind3 through frame33');
  recoverNurseFarStream(far);
  for (let i = 0; i < 10; i++) assert(!tickNurseStream(far, 1).completed, 'far recovery not early');
  assert(tickNurseStream(far, 1).completed, 'far s1 mode3 ends at frame10');
  for (const dt of [1, 0.5]) {
    const c = createNurseStreamClock(16);
    for (let i = 0; i < 30 / dt; i++) tickNurseStream(c, dt);
    assert(c.stage === 'parked' && c.frame === 6, `${dt}: mode3 parks at6`);
    const parked = c.frame;
    resumeNurseStream(c, dt);
    assert(c.frame === parked + dt, `${dt}: continuation retains frame and advances once`);
    let sawNine = false, sawTen = false;
    while (c.stage === 'hit') {
      sawNine ||= c.frame === 9; sawTen ||= c.frame === 10;
      const e = tickNurseStream(c, dt);
      if (e.aux !== undefined) assert(e.aux === 6, `${dt}: frame10 aux6`);
    }
    assert(sawNine && sawTen, `${dt}: exact9..10 HIT window traversed`);
    const heldFrame = c.frame;
    for (let i = 0; i < 60 / dt - 1; i++) {
      assert(tickNurseStream(c, dt).aux === undefined, `${dt}: no early hold completion`);
      assert(c.frame === heldFrame, `${dt}: mode8 freezes animation`);
    }
    assert(tickNurseStream(c, dt).aux === 8, `${dt}: 60 ticks publish aux8`);
    recoverNurseStream(c);
    assert(c.frame === 0 && c.blendDuration === 7, `${dt}: recovery starts distinct anim with blend6+1`);
    for (let i = 0; i < 100 / dt && c.stage !== 'done'; i++) {
      const before = c.frame;
      const e = tickNurseStream(c, dt);
      if (e.completed) assert(before === 16, `${dt}: terminal waits for original AOBJ16`);
    }
    assert(c.stage === 'done', `${dt}: recovery exits`);
  }
  // Structural fixtures exercise admission only; real input and allocation have
  // separate Battle tests, rather than substituting these for gameplay coverage.
  const owner = { borgId: 'pl0900', uid: 'owner', team: 0, grounded: true,
    pos: { x: 0, y: 0, z: 0 }, command: { exact: true, type: 2, actionIndex: 2, variantIndex: 0 } } as unknown as BorgRuntime;
  const target = { borgId: 'pl0615', uid: 'target', team: 0, alive: true, hp: 100,
    state: 'idle', paramTier: 16, pos: { x: 0, y: 0, z: 499 } } as unknown as BorgRuntime;
  assert(isCloseNurseX(owner, target), '499 inside close bound');
  target.pos.z = 500;
  assert(!isCloseNurseX(owner, target), '500 excluded by original >= comparison');
  target.pos.z = 0;
  // pl0615 descriptor+4c=210. SourceY=margin, targetY+height equality passes.
  target.pos.y = NURSE_X.heightMargin - 210;
  assert(isCloseNurseX(owner, target), 'decoded height inclusive equality');
  target.pos.y -= .01;
  assert(!isCloseNurseX(owner, target), 'below decoded height interval rejected');
  target.pos.y = 2 * NURSE_X.heightMargin;
  assert(isCloseNurseX(owner, target), 'lower vertical equality accepted');
  target.pos.y += .01;
  assert(!isCloseNurseX(owner, target), 'above lower vertical bound rejected');
  console.log('[nurseStream] PASS: source continuation, waits and admission');
}
