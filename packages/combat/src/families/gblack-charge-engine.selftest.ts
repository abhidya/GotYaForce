/** Isolated checks of 80179d20's two source phases. Fixtures exercise source
 * ordering, signed/f32 stores and same-dispatch hook mutations. They do not
 * prove authored stream, target geometry, projectile or PPC oracle parity. */
import {
  GBLACK_CHARGE_CONFIG as config,
  createGblackChargeState,
  tickGblackCharge,
  type GblackChargeConfig,
  type GblackChargeHooks,
  type GblackChargeState,
} from './gblack-charge-engine.js';

const f32 = Math.fround;
const s8 = (value: number): number => (value << 24) >> 24;
const s16 = (value: number): number => (value << 16) >> 16;

function assert(condition: unknown, message: string): asserts condition {
  if (!condition) throw new Error(`gblack-charge-engine: ${message}`);
}

function fixture(overrides: Partial<GblackChargeState> = {}) {
  const state = createGblackChargeState({
    subphase541: 9, streamSlot6ea: 6, lockYaw: 66,
    pos: { x: 10, y: 20, z: 30 }, savedGroundPos: { x: 8, y: 19, z: 27 },
    motion: { x: 1, y: 2, z: 3 }, hSpeed: 9, yVel: 8, hDecel: 7, gravityCoeff: 6,
    poseAccum7c: { x: 11, y: 12, z: 13 }, shift18da: 31,
    contactP0: 0, wallContact: 0, faceGate1d10: 1, dashStrength1d0f: 0,
    descriptorGravity6c: -1, actionFlag73f: 1, controlWord: 0x8000000f,
    landingTimer694: 70, dt: 1,
    ...overrides,
  });
  const calls: string[] = [];
  const result = { landing: 0 };
  const hooks: GblackChargeHooks = {
    face6d144: (_state, mode) => { calls.push(`face:${mode}`); },
    pitch6e1ac: (_state, mode, part) => { calls.push(`pitch:${mode}:${part}`); },
    setupCallback: state => {
      calls.push('setup');
      state.hDecel = 0;
      state.hSpeed = 0;
      state.yVel = 4;
      state.gravityCoeff = 0;
    },
    tickStream: (_state, mask) => { calls.push(`tick:${mask}`); },
    startStream: (state, mask, group, slot, rate) => {
      calls.push(`start:${mask}:${group}:${slot}:${rate}:${state.streamSlot6ea}`);
    },
    groundProbe677b0: () => { calls.push('probe'); return result.landing; },
    physics67310: (_state, gravity, yaw) => { calls.push(`physics:${gravity}:${yaw}`); },
    airReturn6a5a4: () => { calls.push('airReturn'); },
  };
  return { state, calls, hooks, result, tick: () => tickGblackCharge(state, config, hooks) };
}

const AIM = 'face:193|pitch:193:1';

function testVerifiedConfig(): void {
  assert(Object.isFrozen(config) && config.streamSlot === 3 && config.driftScale === f32(.95),
    'config8036586c contains immutable slot3 and f32 carry.95');
  assert(Object.keys(config).length === 2, 'config adds no RED timer, budget or air slot');
}

function testPhaseZeroOrderAndOwnCarry(): void {
  const f = fixture();
  const originalFace = f.hooks.face6d144;
  f.hooks.face6d144 = (state, mode) => {
    assert(state.phase === 1 && state.subphase541 === 0 && state.streamSlot6ea === 3,
      'phase0 advances and seeds541/slot before aim');
    assert(state.hSpeed === 9 && state.yVel === 8 && state.hDecel === 7 && state.gravityCoeff === 6 &&
      state.poseAccum7c.z === 13, 'aim precedes all velocity and pose resets');
    originalFace(state, mode);
  };
  const originalSetup = f.hooks.setupCallback!;
  f.hooks.setupCallback = state => {
    assert([state.hSpeed, state.yVel, state.hDecel, state.gravityCoeff].every(value => value === 0),
      'setup observes all four velocity fields cleared');
    assert(Object.values(state.poseAccum7c).every(value => value === 0), 'setup observes pose reset');
    assert(state.motion.x === 1 && state.pos.x === 10, 'setup precedes history subtraction and carry');
    originalSetup(state);
  };
  const originalProbe = f.hooks.groundProbe677b0;
  f.hooks.groundProbe677b0 = state => {
    assert(state.motion.x === f32(2 * config.driftScale) && state.pos.x === f32(10 + state.motion.x),
      'probe follows completed carry');
    return originalProbe(state);
  };
  f.tick();
  assert(f.calls.join('|') === `${AIM}|setup|probe|start:15:4:3:-1:4`,
    'phase0 source order and cursor increment before stream start');
  for (const [axis, position, saved] of [['x', 10, 8], ['y', 20, 19], ['z', 30, 27]] as const) {
    const carry = f32(f32(position - saved) * config.driftScale);
    assert(f.state.motion[axis] === carry && f.state.pos[axis] === f32(position + carry),
      `phase0 ${axis} carry derives from own previous position, not old motion or target`);
  }
  assert(f.state.yVel === 4 && f.state.gravityCoeff === 0 && f.state.lockYaw === 66 &&
    f.state.shift18da === 31 && f.state.landingTimer694 === 70 && f.state.actionFlag73f === 1,
  'setup launch fields survive, with no invented yaw/pitch/timer/action resets');
}

function testPhaseZeroNullableSetupAndLiveMutations(): void {
  const f = fixture();
  f.hooks.setupCallback = state => {
    state.pos.x = 30;
    state.savedGroundPos.x = 10;
    state.motion.x = 999;
    state.subphase541 = 5;
    state.lockYaw = -7;
  };
  tickGblackCharge(f.state, { streamSlot: 3, driftScale: .5 }, f.hooks);
  assert(f.state.motion.x === 10 && f.state.pos.x === 40 && f.state.subphase541 === 5 &&
    f.state.lockYaw === -7, 'setup mutations feed own history carry and are not overwritten later');
  const nullable = fixture();
  nullable.hooks.setupCallback = null;
  nullable.tick();
  assert(nullable.state.yVel === 0 && nullable.state.lockYaw === 66 &&
    nullable.calls.join('|') === `${AIM}|probe|start:15:4:3:-1:4`,
  'nullable setup does not imply projectile creation, yaw changes or vertical launch');
}

function testPhaseZeroSignedSlotsAndNoAirChoice(): void {
  for (const controlWord of [0, 0x40, 0x80, 0x800000ff]) {
    for (const slot of [0x7f, 0x80, 0xff, -1]) {
      const f = fixture({ controlWord });
      const custom: GblackChargeConfig = { streamSlot: slot, driftScale: .5 };
      tickGblackCharge(f.state, custom, f.hooks);
      assert(f.calls.at(-1) === `start:15:4:${s8(slot)}:-1:${s8(slot + 1)}`,
        'single signed-byte slot selection is independent of ground/air control bits');
    }
  }
}

function testPhaseZeroProbeAndStartMutations(): void {
  const f = fixture();
  f.hooks.groundProbe677b0 = state => {
    state.streamSlot6ea = 0xff;
    state.contactP0 = 1;
    state.subphase541 = 1;
    state.wallContact = 1;
    return 1;
  };
  f.hooks.startStream = (state, mask, group, slot, rate) => {
    assert(mask === 15 && group === 4 && slot === -1 && rate === -1 && state.streamSlot6ea === 0,
      'stream uses current post-probe slot and increments cursor before call');
    state.streamSlot6ea = 12;
    state.yVel = 7;
  };
  f.tick();
  assert(f.state.phase === 1 && f.state.streamSlot6ea === 12 && f.state.yVel === 7 &&
    f.state.actionFlag73f === 1 && f.state.landingTimer694 === 70 &&
    !f.calls.includes('tick:15') && !f.calls.includes('airReturn'),
  'start mutations persist without same-call phase1 catch-up or early return');
}

function testPhaseOneStreamFirstAndSignedBranchGates(): void {
  const values = [-1, 0, 1, 127, 0x80, 0xff, 0x100];
  for (const contact of values) {
    for (const gate of values) {
      const f = fixture({ phase: 1, contactP0: 0, subphase541: 0 });
      f.hooks.tickStream = (state, mask) => {
        f.calls.push(`tick:${mask}`);
        assert(state.shift18da === 31 && state.gravityCoeff === 6 && state.pos.x === 10,
          'phase1 stream tick is before damping, gravity restore and carry');
        state.contactP0 = contact;
        state.subphase541 = gate;
      };
      f.tick();
      const earlyExit = s8(contact) > 0 && s8(gate) > 0;
      assert(f.calls.join('|') === (earlyExit ? 'tick:15|airReturn' : `tick:15|${AIM}|physics:1:66|probe`),
        `both signed bytes must be positive for early exit (${contact},${gate})`);
      assert(f.state.shift18da === (s8(contact) < 0 ? 27 : 31),
        'only negative post-stream P0 damps pitch');
      assert(f.state.subphase541 === gate && f.state.phase === 1,
        'phase1 does not infer541, advance phase or reset it');
    }
  }
}

function testPhaseOnePitchDampingAndSignedYaw(): void {
  for (const pitch of [0, 10, -10, 11, -11, 0x7fff, 0x8000, 0xffff]) {
    for (const dt of [0, .25, 2]) {
      const f = fixture({ phase: 1, contactP0: 0xff, shift18da: pitch, dt, lockYaw: 0xffff });
      const expected = s16(Math.trunc(f32(s16(pitch) * f32(.9))));
      f.hooks.face6d144 = state => {
        assert(state.shift18da === expected, 'signed16/f32/truncating damping happens before aim');
      };
      f.hooks.physics67310 = (state, gravity, yaw) => {
        assert(state.shift18da === expected && gravity === 1 && yaw === -1,
          'physics receives gravity1 and current signed16 yaw');
      };
      f.tick();
      assert(f.state.shift18da === expected, 'damping is not multiplied by dt');
    }
  }
}

function testPhaseOneFaceGateAndLiveAim(): void {
  for (const faceGate of [0, 1, -1, 127, 0x80, 0xff, 0x100]) {
    const f = fixture({ phase: 1, faceGate1d10: faceGate });
    f.tick();
    assert(f.calls.join('|') === `tick:15|${s8(faceGate) !== 0 ? `${AIM}|` : ''}physics:1:66|probe`,
      'phase1 face gate uses nonzero byte, including negative values');
  }
  const f = fixture({ phase: 1, faceGate1d10: 0, contactP0: 0, subphase541: 0 });
  f.hooks.tickStream = state => { state.faceGate1d10 = 1; };
  f.hooks.face6d144 = state => {
    state.faceGate1d10 = 0;
    state.contactP0 = 1;
    state.subphase541 = 1;
    state.lockYaw = 0x8000;
  };
  f.hooks.pitch6e1ac = (state, mode, part) => {
    assert(mode === 0xc1 && part === 1 && state.lockYaw === 0x8000,
      'pitch runs after face despite face clearing gate and sees face mutations');
    f.calls.push('pitch');
    state.dashStrength1d0f = 0xff;
    state.descriptorGravity6c = -2.5;
    state.motion.x = 4;
  };
  f.tick();
  assert(f.calls.join('|') === 'pitch|physics:1:-32768|probe' && f.state.gravityCoeff === -2.5 &&
    f.state.dashStrength1d0f === 0 && f.state.motion.x === f32(4 * config.driftScale) &&
    f.state.landingTimer694 === 70 && f.state.actionFlag73f === 1,
  'live aim mutations feed dash/carry/physics without rechecking early-exit gate');
}

function testPhaseOneDashGravityBeforeCarry(): void {
  for (const dash of [0, 1, 127, 0x80, 0xff, -1, 0x100]) {
    const f = fixture({ phase: 1, dashStrength1d0f: dash, descriptorGravity6c: -2.5 });
    const originalPhysics = f.hooks.physics67310;
    f.hooks.physics67310 = (state, gravity, yaw) => {
      assert(state.dashStrength1d0f === (s8(dash) < 0 ? 0 : dash) &&
        state.gravityCoeff === (s8(dash) < 0 ? -2.5 : 6),
      'only negative signed dash clears and restores descriptor gravity before physics');
      assert(state.motion.x === f32(config.driftScale) && state.pos.x === f32(10 + state.motion.x),
        'primary physics observes completed carry');
      originalPhysics(state, gravity, yaw);
    };
    f.tick();
    assert(f.state.yVel === 8 && f.state.landingTimer694 === 70,
      'normal movement does not synthesize vertical resets or timer changes');
  }
}

function testPhaseOneEarlyExitSkipsMovement(): void {
  const f = fixture({ phase: 1, contactP0: 1, subphase541: 1,
    dashStrength1d0f: 0xff, descriptorGravity6c: -2.5, dt: f32(.1) });
  f.hooks.airReturn6a5a4 = state => {
    f.calls.push('airReturn');
    assert(state.gravityCoeff === -2.5 && state.landingTimer694 === f32(30 + f32(.1)),
      'early exit restores gravity and stores verified base30+dt before return');
    assert(state.actionFlag73f === 0 && state.controlWord === 0x8000000c &&
      state.hSpeed === 0 && state.hDecel === 0, 'air return observes common action/control/horizontal resets');
    assert(state.motion.x === 1 && state.pos.x === 10 && state.yVel === 8 &&
      state.shift18da === 31 && state.dashStrength1d0f === 0xff && state.streamSlot6ea === 6,
    'early exit skips aim/carry/physics/probe and negative-dash consumption');
  };
  f.tick();
  assert(f.calls.join('|') === 'tick:15|airReturn', 'positive P0 and541 exit even with incomplete stream');
  assert(f.state.phase === 1 && f.state.subphase541 === 1, 'return housekeeping is not invented by engine');
  const live = fixture({ phase: 1 });
  live.hooks.tickStream = state => {
    state.contactP0 = 1;
    state.subphase541 = 1;
    state.dt = .5;
    state.descriptorGravity6c = -4;
  };
  live.tick();
  assert(live.state.landingTimer694 === 30.5 && live.state.gravityCoeff === -4,
    'early exit reads post-stream dt and descriptor gravity');
}

function testPhaseOneOrdinaryCompletion(): void {
  for (const landing of [0, 1, -1]) {
    for (const completion of [1, 0x80, 0xff, -1]) {
      const f = fixture({ phase: 1, contactP0: 0, subphase541: 0 });
      f.hooks.groundProbe677b0 = state => {
        f.calls.push('probe');
        state.wallContact = completion;
        state.contactP0 = 1;
        state.subphase541 = 1;
        state.controlWord = 0x800001ff;
        return landing;
      };
      f.hooks.airReturn6a5a4 = state => {
        f.calls.push('airReturn');
        assert(state.actionFlag73f === 0 && state.controlWord === 0x800001fc &&
          state.hSpeed === 0 && state.hDecel === 0, 'ordinary completion clears only low control bits');
        assert(state.landingTimer694 === 70 && state.yVel === 8 && state.gravityCoeff === 6,
          'ordinary completion leaves timer and vertical physics fields unchanged');
      };
      f.tick();
      assert(f.calls.join('|') === `tick:15|${AIM}|physics:1:66|probe|airReturn`,
        'all nonzero completion bytes return through air helper regardless of probe result');
      assert(f.state.shift18da === 31 && f.state.phase === 1,
        'post-probe P0 changes do not rerun damping or early-exit branch');
    }
  }
}

function testPhaseOneIncompleteAndCompletionMutation(): void {
  const f = fixture({ phase: 1, contactP0: -1, subphase541: 1, wallContact: 1 });
  f.hooks.physics67310 = (state, gravity, yaw) => {
    f.calls.push(`physics:${gravity}:${yaw}`);
    state.motion.y = 123;
    state.pos.y = 456;
    state.wallContact = 0xff;
  };
  f.hooks.groundProbe677b0 = state => {
    f.calls.push('probe');
    assert(state.motion.y === 123 && state.pos.y === 456,
      'probe sees primary-physics mutations without second carry');
    state.wallContact = 0x100;
    return 1;
  };
  f.tick();
  assert(f.calls.join('|') === `tick:15|${AIM}|physics:1:66|probe` &&
    f.state.actionFlag73f === 1 && f.state.controlWord === 0x8000000f &&
    f.state.hSpeed === 9 && f.state.hDecel === 7,
  'post-probe zero completion byte stays active despite earlier completion and accepted ground');
}

function testCarryF32StoresAndNoReplay(): void {
  const f = fixture({ pos: { x: f32(12345.678), y: f32(.1), z: f32(-.2) },
    savedGroundPos: { x: f32(-.3333), y: f32(-.7), z: f32(.1) } });
  const positions = { ...f.state.pos };
  const saved = { ...f.state.savedGroundPos };
  f.tick();
  for (const axis of ['x', 'y', 'z'] as const) {
    const expected = f32(f32(positions[axis] - saved[axis]) * f32(.95));
    assert(f.state.motion[axis] === expected && f.state.pos[axis] === f32(positions[axis] + expected),
      'subtraction, scale and addition each have separate f32 stores');
  }
  const lastPos = { ...f.state.pos };
  const lastMotion = { ...f.state.motion };
  f.state.savedGroundPos = { x: -999, y: -999, z: -999 };
  f.state.dt = 100;
  f.calls.length = 0;
  f.tick();
  for (const axis of ['x', 'y', 'z'] as const) {
    const expected = f32(lastMotion[axis] * config.driftScale);
    assert(f.state.motion[axis] === expected && f.state.pos[axis] === f32(lastPos[axis] + expected),
      'phase1 decays stored carry without reinitializing from history or scaling by dt');
  }
  f.tick();
  assert(f.calls.every(call => !call.startsWith('start:') && call !== 'setup') &&
    f.calls.filter(call => call === 'tick:15').length === 2 && f.state.streamSlot6ea === 4 &&
    f.state.subphase541 === 0 && f.state.landingTimer694 === 70,
  'active phase1 ticks once per call without replay, setup/release, timer countdown or inferred541');
}

function testFactoryAndInvalidPhases(): void {
  const original = fixture().state;
  const copied = createGblackChargeState(original);
  for (const key of ['pos', 'savedGroundPos', 'motion', 'poseAccum7c'] as const) {
    assert(copied[key] !== original[key], `factory clones ${key}`);
    copied[key].x = 999;
    assert(original[key].x !== 999, `factory isolates ${key} storage`);
  }
  assert(copied.phase === 0 && copied.subphase541 === 9 && copied.streamSlot6ea === 6 &&
    copied.hSpeed === 9 && copied.landingTimer694 === 70, 'factory performs no phase0 writes');
  for (const phase of [2, 3, -1, 0x80]) {
    const f = fixture({ phase });
    let error: unknown;
    try { f.tick(); } catch (caught) { error = caught; }
    assert(error instanceof RangeError && f.calls.length === 0, 'invalid signed phase fails before hooks');
  }
  const bytePhase = fixture({ phase: 0x100 });
  bytePhase.tick();
  assert(bytePhase.state.phase === 1, 'phase dispatch and increment use signed-byte storage');
}

/** Fourteen focused groups, including independent signed gates, live stream
 * mutation, early/ordinary exits and one-dispatch-only setup/carry ordering. */
export function runGblackChargeEngineSelfTest(): void {
  testVerifiedConfig();
  testPhaseZeroOrderAndOwnCarry();
  testPhaseZeroNullableSetupAndLiveMutations();
  testPhaseZeroSignedSlotsAndNoAirChoice();
  testPhaseZeroProbeAndStartMutations();
  testPhaseOneStreamFirstAndSignedBranchGates();
  testPhaseOnePitchDampingAndSignedYaw();
  testPhaseOneFaceGateAndLiveAim();
  testPhaseOneDashGravityBeforeCarry();
  testPhaseOneEarlyExitSkipsMovement();
  testPhaseOneOrdinaryCompletion();
  testPhaseOneIncompleteAndCompletionMutation();
  testCarryF32StoresAndNoReplay();
  testFactoryAndInvalidPhases();
}
