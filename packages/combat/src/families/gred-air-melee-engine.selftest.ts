/** Durable, isolated control-flow checks for the bounded 80178394 port.
 * Hook fixtures deliberately do not assert terrain, target-bone, stream or
 * original-library parity. Real input/stream coverage lives in separate tests.
 */
import {
  GRED_AIR_MELEE_CONFIG as config,
  createGredAirMeleeState,
  dampGredAirMelee,
  tickGredAirMelee,
  type GredAirMeleeHooks,
  type GredAirMeleeState,
} from './gred-air-melee-engine.js';

const f32 = Math.fround;
const BAM_RADIANS = .0000958738019107841;

function assert(condition: unknown, message: string): asserts condition {
  if (!condition) throw new Error(`gred-air-melee-engine: ${message}`);
}

function fixture(overrides: Partial<GredAirMeleeState> = {}) {
  const state = createGredAirMeleeState({
    noTargetLatch541: 0, target: {}, rangeRow86c: 1200,
    heading72: 44, activeYaw: 55, lockYaw: 66, pitch54e: 123, shift18da: 31,
    handlerTimer: 30, pos: { x: 10, y: 20, z: 30 },
    savedGroundPos: { x: 8, y: 19, z: 27 }, motion: { x: 1, y: 2, z: 3 },
    hSpeed: 9, yVel: 8, hDecel: 7, gravityCoeff: 6,
    poseAccum7c: { x: 11, y: 12, z: 13 }, streamSlot6ea: 2,
    dashStrength1d0f: 0, aimMode1d10: 0, descriptorGravity6c: -1,
    retap746: 1, alt745: 1, input1d9: 0, inputEdges5d4: 0,
    contactP0: 0, contactP1: 0, streamHold1b03: 0, wallContact: 0,
    actionFlag73f: 1, controlWord: 15, landingTimer694: 0, dt: 1,
    ...overrides,
  });
  const calls: string[] = [];
  const result = { range: 1, proximity: -1, facing: 0, landing: 0, partPitch: 1234 };
  const hooks: GredAirMeleeHooks = {
    range66838: (_state, range) => { calls.push(`range:${range}`); return result.range; },
    proximity668cc: (_state, range) => { calls.push(`proximity:${range}`); return result.proximity; },
    face6d144: (_state, mode) => { calls.push(`face:${mode}`); return result.facing; },
    pitch6e514: (_state, mode) => { calls.push(`pitch:${mode}`); },
    pitch6e1ac: (state, mode, part) => {
      calls.push(`partPitch:${mode}:${part}`);
      state.shift18da = result.partPitch;
    },
    tickStream: (_state, mask) => { calls.push(`tick:${mask}`); },
    startStream: (state, mask, group, slot, rate) => {
      calls.push(`start:${mask}:${group}:${slot}:${rate}:${state.streamSlot6ea}`);
    },
    groundProbe677b0: () => { calls.push('probe'); return result.landing; },
    physics67310: (_state, gravity, yaw) => { calls.push(`physics:${gravity}:${yaw}`); },
    transition92dcc: (_state, value) => { calls.push(`transition:${value}`); },
    landing6a750: (_state, cue) => { calls.push(`landing:${cue}`); },
    airReturn6a5a4: () => { calls.push('airReturn'); },
  };
  return { state, hooks, calls, result, tick: () => tickGredAirMelee(state, config, hooks) };
}

function testPhaseZeroOrderAndOwnCarry(): void {
  const f = fixture();
  f.tick();
  assert(f.calls.join('|') === 'range:1200|start:15:3:12:-1:13|face:192|pitch:192|probe',
    'phase0 starts stream before facing/pitch and increments slot before the hook');
  assert(f.state.phase === 1 && f.state.handlerTimer === 30, 'phase0 initial timer and advance');
  assert(f.state.pitch54e === 0 && f.state.shift18da === 31, 'phase0 resets only pursuit pitch');
  assert(f.state.alt745 === 0 && f.state.retap746 === 0, 'phase0 clears both latches');
  assert(Object.values(f.state.poseAccum7c).every(value => value === 0), 'phase0 resets all pose shorts');
  assert([f.state.hSpeed, f.state.yVel, f.state.hDecel, f.state.gravityCoeff].every(value => value === 0),
    'phase0 resets all four velocity scalars');
  for (const [axis, position, saved] of [['x', 10, 8], ['y', 20, 19], ['z', 30, 27]] as const) {
    const carry = f32(f32(position - saved) * config.driftScale);
    assert(f.state.motion[axis] === carry && f.state.pos[axis] === f32(position + carry),
      `phase0 carries own ${axis} history with field rounding`);
  }
}

function testNoTargetLatchAndHeading(): void {
  const f = fixture({ heading72: 0xfffe });
  f.result.range = -1;
  f.hooks.face6d144 = state => {
    assert(state.target === null, 'facing observes source target clearing');
    return 0;
  };
  f.tick();
  assert(f.state.noTargetLatch541 === 1 && f.state.target === null, 'negative initial range latches no target');
  assert(f.state.lockYaw === -2 && f.state.activeYaw === -2, 'fallback uses signed heading, not existing lock yaw');
  f.state.target = {};
  f.tick();
  assert(f.state.target === null, 'no-target latch clears a newly supplied target on every dispatch');
  const missing = fixture({ target: null });
  missing.tick();
  assert(missing.state.activeYaw === 44 && missing.state.lockYaw === 66,
    'null target separately resets active yaw even when range hook succeeds');
}

function testPhaseOneTimeoutShortCircuit(): void {
  const f = fixture({ phase: 1, handlerTimer: .5, dt: .5 });
  f.tick();
  assert(f.calls.join('|') === 'probe|pitch:192|transition:0',
    'phase1 no blend skips stream and timeout short-circuits facing');
  assert(f.state.phase === 2 && f.state.handlerTimer === 20, 'phase1 timer equality advances');
  assert(f.state.motion.x === f32(config.driftScale), 'phase1 carry is not multiplied by dt');
  const signed = fixture({ phase: 1, handlerTimer: 0 });
  tickGredAirMelee(signed.state, { ...config, pursuitTimer: 0xffff }, signed.hooks);
  assert(signed.state.handlerTimer === -1, 'phase1 loads signed16 pursuit timer');
}

function testPhaseOneBlendAndFacing(): void {
  for (const contactP0 of [0, 1, 0x80, 0xff, -1]) {
    const f = fixture({ phase: 1, contactP0, streamHold1b03: 1 });
    f.result.facing = 1;
    f.tick();
    assert(f.calls.join('|') === 'tick:15|probe|pitch:192|face:192|transition:0',
      `phase1 blend ticks independently of contact ${contactP0}`);
    assert(f.state.phase === 2, 'phase1 completed facing advances before timeout');
    const stopped = fixture({ phase: 1, contactP0 });
    stopped.tick();
    assert(!stopped.calls.includes('tick:15') && stopped.state.phase === 1,
      'phase1 without blend does not tick even at zero contact');
  }
}

function testEarlyPartPitchDoesNotCopy(): void {
  for (const phase of [0, 1]) {
    const f = fixture({ phase, aimMode1d10: 2 });
    f.tick();
    assert(f.state.shift18da === 1234, `phase${phase} invokes part-pitch helper`);
    assert(f.state.pitch54e === (phase === 0 ? 0 : 123),
      `phase${phase} deliberately does not copy part-pitch into pursuit pitch`);
  }
}

function testPhaseTwoGatesAndPositiveProximity(): void {
  for (const contactP0 of [0, 1, 0x80, 0xff, -1]) {
    const f = fixture({ phase: 2, handlerTimer: 10, pitch54e: 0, contactP0 });
    f.tick();
    assert(f.calls.includes('tick:15') === (contactP0 === 0), 'phase2 signed contact stream gate');
    assert(f.calls.slice(contactP0 === 0 ? 1 : 0).join('|') ===
      'face:192|pitch:192|physics:1:66|probe|proximity:200', 'phase2 source helper order');
    assert(f.state.phase === 2 && f.state.hSpeed === 60 && f.state.handlerTimer === 9,
      'phase2 missing-target -1 is not positive proximity');
    f.state.streamHold1b03 = 1;
    f.result.proximity = 0;
    f.calls.length = 0;
    f.tick();
    assert(f.calls.includes('tick:15') && f.state.phase === 2, 'blend overrides contact but zero proximity cannot advance');
    f.result.proximity = 1;
    f.tick();
    assert(Number(f.state.phase) === 3, 'positive proximity advances phase2');
  }
}

function testPhaseTwoTimeoutAndFourFieldBrake(): void {
  const f = fixture({ phase: 2, handlerTimer: 1, pitch54e: 0 });
  f.tick();
  assert(f.state.phase === 3 && f.state.handlerTimer === 0, 'phase2 timed transition loads zero recovery timer');
  assert(f.state.hSpeed === 15 && f.state.yVel === 0 && f.state.hDecel === 1.75 && f.state.gravityCoeff === 1.5,
    'phase2 transition brakes all four velocity fields');
  assert(!f.calls.includes('proximity:200'), 'phase2 timeout short-circuits proximity');
  const signed = fixture({ phase: 2, handlerTimer: 0 });
  tickGredAirMelee(signed.state, { ...config, recoveryTimer: 0xfffe }, signed.hooks);
  assert(signed.state.handlerTimer === -2, 'phase2 loads signed16 recovery timer');
}

function testPursuitCopiesSignedPartPitch(): void {
  const f = fixture({ phase: 2, handlerTimer: 9, aimMode1d10: 2, lockYaw: 0xfffe });
  f.result.partPitch = 0xf000;
  f.tick();
  assert(f.state.pitch54e === -4096, 'phase2 copies signed16 part pitch');
  const angle = f32(-4096 * BAM_RADIANS);
  assert(f.state.hSpeed === f32(60 * f32(Math.cos(angle))) &&
    f.state.yVel === f32(60 * -f32(Math.sin(angle))), 'pursuit uses cosine horizontal and negative sine vertical');
  assert(f.calls.includes('physics:1:-2'), 'primary physics receives signed lock yaw and factor1');
}

function testZeroTimerBrakeStillRunsFullPhase(): void {
  const f = fixture({ phase: 3, handlerTimer: 0, input1d9: 1, alt745: 0, contactP0: 1 });
  f.tick();
  assert(f.calls.join('|') === 'face:192|pitch:192|physics:1:66|probe',
    'zero-duration phase3 still faces, aims, integrates and probes');
  assert(f.state.phase === 4 && f.state.handlerTimer === -1 && f.state.alt745 === 1,
    'phase3 latches accepted input and advances only after its full pass');
  assert(f.state.hSpeed === f32(9 * config.recoveryDamping) &&
    f.state.yVel === f32(8 * config.recoveryDamping) && f.state.hDecel === 7 && f.state.gravityCoeff === 6,
    'phase3 damps only horizontal/vertical speeds');
  for (const contactP0 of [0, 1, 0xff]) {
    const gate = fixture({ phase: 3, contactP0, streamHold1b03: 0 });
    gate.tick();
    assert(gate.calls.includes('tick:15') === (contactP0 === 0), 'phase3 contact gate matches source');
    const blend = fixture({ phase: 3, contactP0, streamHold1b03: 1 });
    blend.tick();
    assert(blend.calls.includes('tick:15'), 'phase3 blend override ticks');
  }
}

function testDampingDtOneAndFusedNonunit(): void {
  const unit = fixture({ hSpeed: f32(12345.678), yVel: f32(-98765.432) });
  const h = unit.state.hSpeed, y = unit.state.yVel;
  dampGredAirMelee(unit.state, config.recoveryDamping);
  assert(unit.state.hSpeed === f32(h * config.recoveryDamping) &&
    unit.state.yVel === f32(y * config.recoveryDamping), 'dt1 uses ordinary f32 multiplication');
  for (const dt of [0, .25, 1.5, 2]) {
    const f = fixture({ dt, hSpeed: h, yVel: y });
    const loss = f32(f32(1 - config.recoveryDamping) * dt);
    dampGredAirMelee(f.state, config.recoveryDamping);
    assert(f.state.hSpeed === f32(h - h * loss) && f.state.yVel === f32(y - y * loss),
      `dt${dt} uses single-final-round fnmsubs expression`);
    assert(f.state.hDecel === 7 && f.state.gravityCoeff === 6, 'damping does not alter acceleration scalars');
    if (dt === 1.5) {
      assert(f.state.hSpeed !== f32(-(f32(h * loss) - h)),
        'nonunit fixture distinguishes fused subtraction from separately rounded product');
    }
    if (dt === .25) {
      assert(f.state.hSpeed !== f32(h * Math.pow(config.recoveryDamping, dt)),
        'fractional damping is linear rather than exponential');
    }
  }
}

function testPhaseFourContactShiftAndDash(): void {
  const f = fixture({ phase: 4, contactP0: 0xff, shift18da: 0xfff1, dashStrength1d0f: 24, pitch54e: 0 });
  f.tick();
  assert(f.calls.join('|') === 'tick:15|physics:1:66|probe', 'phase4 without positive aim mode skips facing');
  assert(f.state.shift18da === -8, 'negative contact arithmetic-shifts signed16 part pitch');
  assert(f.state.dashStrength1d0f === 0 && f.state.hSpeed === f32(60 * config.recoveryDamping),
    'positive dash consumes flag then resets speed before damping');
  const streamMutation = fixture({ phase: 4, contactP0: 0, aimMode1d10: 0, shift18da: 0xfff1 });
  streamMutation.hooks.tickStream = state => { state.contactP0 = 0xff; state.aimMode1d10 = 2; };
  streamMutation.result.partPitch = 0xf000;
  streamMutation.tick();
  assert(streamMutation.state.pitch54e === -4096 && streamMutation.calls.includes('partPitch:192:1'),
    'phase4 uses same-call stream mutations for contact and alternate aiming');
}

function testNegativeDashLoadsDescriptorGravity(): void {
  for (const dashStrength1d0f of [-1, 0x80, 0xff]) {
    const f = fixture({ phase: 4, dashStrength1d0f, descriptorGravity6c: -1 });
    f.tick();
    assert(f.state.dashStrength1d0f === 0 && f.state.gravityCoeff === -1,
      'signed negative dash consumes flag and restores host descriptor gravity');
    assert(f.state.hSpeed === f32(9 * config.recoveryDamping), 'negative dash does not reset launch speed');
  }
}

function testLandingPrecedesStreamCompletion(): void {
  const f = fixture({ phase: 4, contactP0: 0xff, wallContact: 1, dt: .5 });
  f.result.landing = 1;
  f.hooks.landing6a750 = (state, cue) => {
    f.calls.push(`landing:${cue}`);
    assert(state.actionFlag73f === 0 && state.controlWord === 12, 'landing hook observes cleared action/control flags');
    assert(state.landingTimer694 === 0, 'landing timer is written after the cue hook');
  };
  f.tick();
  assert(f.calls.join('|') === 'tick:15|physics:1:66|probe|landing:7',
    'accepted negative-contact landing short-circuits completed-stream air return');
  assert(f.state.landingTimer694 === 1.5, 'landing timer is f32 one plus current dt');
}

function testCompletionWithoutAcceptedNegativeContact(): void {
  for (const [contactP0, landing] of [[0, 1], [1, 1], [0xff, 0]] as const) {
    const f = fixture({ phase: 4, wallContact: 1, contactP0 });
    f.result.landing = landing;
    f.tick();
    assert(f.calls.join('|') === 'tick:15|physics:1:66|probe|airReturn',
      'stream completion handles nonnegative contact or absent accepted landing');
    assert(f.state.landingTimer694 === 0 && f.state.controlWord === 12 && f.state.actionFlag73f === 0,
      'completion clears action flags without writing landing timer');
  }
}

function testAuxiliaryContinuationEarlyReturn(): void {
  for (const nextDash of [0, 1]) {
    const f = fixture({ phase: 4, contactP1: 0xff, input1d9: 1, inputEdges5d4: 0x40,
      streamSlot6ea: 127, retap746: 0, alt745: 0 });
    f.hooks.startStream = (state, mask, group, slot, rate) => {
      f.calls.push(`start:${mask}:${group}:${slot}:${rate}:${state.streamSlot6ea}`);
      assert(state.retap746 === 0 && state.alt745 === 0, 'continuation clears latches before starting');
      state.dashStrength1d0f = nextDash;
    };
    f.tick();
    assert(f.calls.join('|') === 'tick:15|start:15:3:127:-1:-128',
      'negative auxiliary contact starts signed-byte next slot and skips physics');
    const angle = f32(123 * BAM_RADIANS);
    assert(f.state.hSpeed === (nextDash > 0 ? f32(60 * f32(Math.cos(angle))) : 9),
      'continuation reads newly started stream dash flag and returns before damping');
    assert(f.state.dashStrength1d0f === 0, 'positive continuation dash is consumed');
  }
  const booleanLatches = fixture({ phase: 4, contactP1: -1, retap746: 2, alt745: 1 });
  booleanLatches.tick();
  assert(booleanLatches.calls.some(call => call.startsWith('start:')),
    'source continuation checks both latches nonzero, not bitwise intersection');
}

function testFactoryAndInvalidPhase(): void {
  const original = fixture().state;
  const copy = createGredAirMeleeState(original);
  for (const key of ['pos', 'savedGroundPos', 'motion', 'poseAccum7c'] as const) {
    assert(copy[key] !== original[key], `factory clones ${key}`);
  }
  copy.pos.x = 999;
  assert(original.pos.x === 10 && copy.target === original.target, 'factory retains target identity but not vector storage');
  const invalid = fixture({ phase: 5 });
  let error: unknown;
  try { invalid.tick(); } catch (caught) { error = caught; }
  assert(error instanceof RangeError, 'invalid engine phase is rejected');
}

/** Sixteen focused groups, with signed-field/contact/dt boundary matrices. */
export function runGredAirMeleeEngineSelfTest(): void {
  testPhaseZeroOrderAndOwnCarry();
  testNoTargetLatchAndHeading();
  testPhaseOneTimeoutShortCircuit();
  testPhaseOneBlendAndFacing();
  testEarlyPartPitchDoesNotCopy();
  testPhaseTwoGatesAndPositiveProximity();
  testPhaseTwoTimeoutAndFourFieldBrake();
  testPursuitCopiesSignedPartPitch();
  testZeroTimerBrakeStillRunsFullPhase();
  testDampingDtOneAndFusedNonunit();
  testPhaseFourContactShiftAndDash();
  testNegativeDashLoadsDescriptorGravity();
  testLandingPrecedesStreamCompletion();
  testCompletionWithoutAcceptedNegativeContact();
  testAuxiliaryContinuationEarlyReturn();
  testFactoryAndInvalidPhase();
}
