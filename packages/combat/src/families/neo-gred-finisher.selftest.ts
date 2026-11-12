import {
  NEO_GRED_FINISHER_CONFIG as cfg, tickNeoGredFinisher, dampNeoGredFinisher,
  type NeoGredFinisherState, type NeoGredFinisherHooks,
} from './neo-gred-finisher.js';
function assert(value: unknown, label: string): asserts value {
  if (!value) throw new Error(`neo-gred-finisher: ${label}`);
}
function near(a: number, b: number): boolean { return Math.abs(a - b) < .0001; }
function fixture(phase = 0) {
  const s: NeoGredFinisherState = {
    phase, noTargetLatch541: 0, shift18da: 0, target: {}, rangeRow868: 120,
    targetDistance760: 300, dashStrength1d0f: 32, activeYaw: 0, lockYaw: 123,
    handlerTimer: 10, pos: { x: 10, y: 8, z: 6 },
    savedGroundPos: { x: 8, y: 4, z: 0 }, motion: { x: 2, y: 4, z: 6 },
    hSpeed: 100, yVel: 20, hDecel: -3, gravityCoeff: 0, blendFloor80c: 3,
    retap746: 1, alt745: 1, input1d9: 0, inputEdges5d4: 0,
    contactP0: 0, contactP1: 0, streamHold1b03: 0, hold71c: 0,
    wallContact: 0, actionFlag73f: 1, controlWord: 0xffff, dt: 1,
  };
  const calls: string[] = [];
  const result = { range: 0, facing: 0 };
  const h: NeoGredFinisherHooks = {
    range66838: (_s, range) => { calls.push(`range:${range}`); return result.range; },
    face6d144: (_s, mode) => { calls.push(`face:${mode}`); return result.facing; },
    tickStream: (_s, mask) => { calls.push(`tick:${mask}`); },
    startStream: (_s, mask, group, slot, rate) => { calls.push(`start:${mask}:${group}:${slot}:${rate}`); },
    groundProbe677b0: () => { calls.push('probe'); },
    groundMove670dc: (_s, yaw) => { calls.push(`ground:${yaw}`); },
    physics67310: (_s, gravity, yaw) => { calls.push(`physics:${gravity}:${yaw}`); },
    setLaunch66530: (_s, value) => { calls.push(`launch:${value}`); },
    spawnTrailB2190: (_s, value) => { calls.push(`trail:${value}`); },
    syncB22f4: () => { calls.push('sync'); },
    airReturn6a5a4: () => { calls.push('airReturn'); },
  };
  return { s, h, calls, result, tick: () => tickNeoGredFinisher(s, cfg, h) };
}
export function runNeoGredFinisherSelfTest(): void {
  {
    const f = fixture(); f.s.shift18da = 0x8001; f.result.range = -1; f.tick();
    assert(f.s.shift18da === -16384, 'entry arithmetic signed16 shift');
    assert(f.s.phase === 1 && f.s.handlerTimer === 60, 'phase0 timer/advance');
    assert(f.s.target === null && f.s.noTargetLatch541 === 1 && f.s.activeYaw === 123, 'phase0 -1 target fallback');
    assert(f.s.retap746 === 0 && f.s.alt745 === 0, 'phase0 resets latches');
    assert(near(f.s.pos.x, 11.9) && near(f.s.pos.y, 11.8) && near(f.s.pos.z, 11.7), 'phase0 full XYZ saved-position drift');
    assert(f.calls.join('|') === 'range:120|face:192|probe|start:15:3:27:-1', 'phase0 source call order');
  }
  {
    const f = fixture(); f.result.range = 1; f.tick();
    assert(f.s.target !== null && f.s.noTargetLatch541 === 0, 'phase0 in-range keeps target');
    f.s.phase = 1; f.s.noTargetLatch541 = 1; f.s.target = {}; f.tick();
    assert(f.s.target === null, 'entry target suppression repeats');
  }
  for (const contact of [0, 1, 0x80, -1]) {
    const f = fixture(1); f.s.contactP0 = contact; f.tick();
    assert(f.calls.includes('tick:15') === (contact === 0), `phase1 contact ${contact} gate`);
    assert(f.s.phase === 1 && f.s.handlerTimer === 9, 'phase1 no premature advance');
    f.calls.length = 0; f.s.streamHold1b03 = 1; f.tick();
    assert(f.calls.includes('tick:15'), 'phase1 hold override ticks');
  }
  {
    const f = fixture(1); f.result.facing = 1; f.tick();
    assert(f.s.phase === 2 && f.s.handlerTimer === 20 && f.s.hSpeed === 30, 'phase1 target metric*32*.0625/20');
    assert(f.s.hDecel === 0 && f.s.blendFloor80c === 0, 'phase1 clears decel/blend');
    assert(f.calls.at(-1) === 'sync', 'phase1 sync last');
  }
  {
    const f = fixture(1); f.s.target = null; f.s.handlerTimer = .5; f.s.dt = .5; f.tick();
    assert(f.s.phase === 2 && f.s.hSpeed === 6, 'phase1 threshold equality and no-target row speed');
    assert(!f.calls.includes('face:192'), 'phase1 expired timer short circuits facing');
    assert(near(f.s.motion.x, 1.9), 'phase1 drift deliberately not dt-scaled');
  }
  {
    const f = fixture(1); f.s.dashStrength1d0f = 255; f.result.facing = 1; f.tick();
    assert(f.s.hSpeed === -.9375, 'phase1 signed dash byte');
  }
  for (const contact of [0, 1, 0x80]) {
    const f = fixture(2); f.s.contactP0 = contact; f.s.input1d9 = 1; f.s.alt745 = 0; f.tick();
    assert(f.calls.includes('tick:15') === (contact === 0), 'phase2 contact gate');
    assert(f.s.alt745 === 1 && f.s.phase === 2, 'phase2 latch and no premature advance');
    assert(near(f.s.hSpeed, 95) && near(f.s.yVel, 19), 'phase2 damping both speeds');
    f.calls.length = 0; f.s.streamHold1b03 = 1; f.result.range = -1; f.tick();
    assert(Number(f.s.phase) === 3 && f.calls.includes('tick:15'), 'phase2 -1 is nonzero transition, hold override');
    assert(near(f.s.hSpeed, 22.5625), 'phase2 transition quarter-brakes after damping');
  }
  {
    const f = fixture(2); f.s.handlerTimer = .25; f.s.dt = .5; f.tick();
    assert(f.s.phase === 3 && !f.calls.includes('range:200'), 'phase2 timer short-circuit');
    assert(near(f.s.hSpeed, 24.375) && near(f.s.yVel, 19.5), 'fractional damping and brake');
  }
  {
    const f = fixture(3); f.s.hold71c = 1; f.s.input1d9 = 1; f.s.alt745 = 0; f.tick();
    assert(f.calls.length === 0 && f.s.alt745 === 1 && f.s.hSpeed === 100, 'phase3 hold blocks all but input latch');
  }
  for (const contact of [0, 1, 127, 128, 255, -1]) {
    const f = fixture(3); f.s.contactP1 = contact; f.tick();
    const launches = contact > 0 && contact < 128;
    assert(f.s.phase === (launches ? 4 : 3), `phase3 signed contact ${contact}`);
    if (launches) {
      assert(f.s.hSpeed === 0 && f.s.hDecel === 0 && f.s.yVel === 60 && f.s.gravityCoeff === -2, 'phase3 launch seeds');
      assert(f.calls.join('|') === 'tick:15|ground:123|launch:45|trail:0|sync', 'phase3 launch call order');
    }
  }
  {
    const f = fixture(3); f.h.tickStream = (s) => { s.contactP1 = 1; }; f.tick();
    assert(f.s.phase === 4, 'phase3 uses same-tick stream mutations');
  }
  {
    const f = fixture(4); f.s.contactP1 = 0x80; f.s.inputEdges5d4 = 0x40;
    f.s.input1d9 = 1; f.s.retap746 = 0; f.s.alt745 = 0; f.tick();
    assert(f.s.phase === 4 && f.s.retap746 === 1 && f.s.alt745 === 1, 'phase4 null callback cannot invent rechain');
    assert(f.calls.join('|') === 'tick:15|physics:1:123|probe', 'phase4 null callback recovery');
    f.calls.length = 0; f.s.wallContact = 1; f.tick();
    assert(f.s.actionFlag73f === 0 && f.s.controlWord === 0xfffc && f.calls.at(-1) === 'airReturn', 'phase4 animation-end cleanup');
  }
  {
    const f = fixture(4); f.s.contactP1 = -1;
    tickNeoGredFinisher(f.s, { ...cfg, chainCallback: () => { f.calls.push('callback'); } }, f.h);
    assert(f.calls.join('|') === 'tick:15|callback', 'phase4 nonnull callback short circuits recovery');
    f.calls.length = 0; f.s.retap746 = 2; f.s.alt745 = 1;
    tickNeoGredFinisher(f.s, { ...cfg, chainCallback: () => { f.calls.push('callback'); } }, f.h);
    assert(!f.calls.includes('callback'), 'phase4 bitwise latch intersection, not boolean truthiness');
  }
  {
    const f = fixture(); f.s.dt = .25; dampNeoGredFinisher(f.s, .5);
    assert(f.s.hSpeed === 87.5 && f.s.yVel === 17.5, 'fractional dt linear damping, not exponent');
    f.s.dt = 0; dampNeoGredFinisher(f.s, .5);
    assert(f.s.hSpeed === 87.5, 'zero dt no damping');
  }
}
