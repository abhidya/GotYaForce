import { createNurseStreamClock, tickNurseStream, resumeNurseStream, recoverNurseStream } from './nurseStream.js';
import { canStartNurseX, NURSE_X } from './nurseX.js';
import type { BorgRuntime } from './types.js';
function assert(value: unknown, message: string): void {
  if (!value) throw new Error(`[nurseStream] ${message}`);
}
export function runNurseStreamSelfTest(): void {
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
  assert(canStartNurseX(owner, target), '499 inside close bound');
  target.pos.z = 500;
  assert(!canStartNurseX(owner, target), '500 excluded by original >= comparison');
  target.pos.z = 0;
  // pl0615 descriptor+4c=210. SourceY=margin, targetY+height equality passes.
  target.pos.y = NURSE_X.heightMargin - 210;
  assert(canStartNurseX(owner, target), 'decoded height inclusive equality');
  target.pos.y -= .01;
  assert(!canStartNurseX(owner, target), 'below decoded height interval rejected');
  target.pos.y = 2 * NURSE_X.heightMargin;
  assert(canStartNurseX(owner, target), 'lower vertical equality accepted');
  target.pos.y += .01;
  assert(!canStartNurseX(owner, target), 'above lower vertical bound rejected');
  console.log('[nurseStream] PASS: source continuation, waits and admission');
}
