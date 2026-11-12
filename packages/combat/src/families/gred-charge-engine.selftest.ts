/** Isolated, durable checks for 80179814's source control flow. Hook fixtures
 * verify call ordering and same-dispatch mutations, not target geometry,
 * authored stream data, terrain, projectile simulation or PPC oracle parity.
 */
import {
  GRED_CHARGE_CONFIG as config,
  createGredChargeState,
  popcountGredChargeEdges,
  tickGredCharge,
  type GredChargeConfig,
  type GredChargeHooks,
  type GredChargeState,
} from './gred-charge-engine.js';

const f32 = Math.fround;
const s16 = (value: number): number => (value << 16) >> 16;

function assert(condition: unknown, message: string): asserts condition {
  if (!condition) throw new Error(`gred-charge-engine: ${message}`);
}

function fixture(overrides: Partial<GredChargeState> = {}) {
  const state = createGredChargeState({
    releaseSubphase542: 9, target: {}, heading72: 44, activeYaw: 55, lockYaw: 66,
    chargeTimer560: 99, extensionBudget54e: 98, chargeState6f7: 7, streamSlot6ea: 6,
    aimTarget524: { x: 100, y: 200, z: 300 },
    pos: { x: 10, y: 20, z: 30 }, savedGroundPos: { x: 8, y: 19, z: 27 },
    motion: { x: 1, y: 2, z: 3 }, hSpeed: 9, yVel: 8, hDecel: 7, gravityCoeff: 6,
    poseAccum7c: { x: 11, y: 12, z: 13 }, controlWord: 0x8000000f,
    freshInput5bc: 0, dashStrength1d0f: 0, descriptorGravity6c: -1,
    shift18da: 31, contactP0: 0, wallContact: 0, actionFlag73f: 1,
    landingTimer694: 70, dt: 1,
    ...overrides,
  });
  const calls: string[] = [];
  const result = { landing: 0 };
  const hooks: GredChargeHooks = {
    face6d1a8: (state, mode, target) => {
      assert(target === state.aimTarget524, 'face uses actor+524 saved target');
      calls.push(`face:${mode}`);
    },
    pitch6e39c: (state, mode, part, clamp, target) => {
      assert(target === state.aimTarget524, 'pitch uses actor+524 target');
      calls.push(`pitch:${mode}:${part}:${clamp}`);
    },
    setupCallback: state => {
      calls.push('setup');
      state.lockYaw = s16(state.heading72);
      state.yVel = 8;
      state.gravityCoeff = 0;
    },
    releaseCallback: () => { calls.push('release'); },
    tickStream: (_state, mask) => { calls.push(`tick:${mask}`); },
    startStream: (state, mask, group, slot, rate) => {
      calls.push(`start:${mask}:${group}:${slot}:${rate}:${state.streamSlot6ea}`);
    },
    groundProbe677b0: () => { calls.push('probe'); return result.landing; },
    physics67310: (_state, gravity, yaw) => { calls.push(`physics:${gravity}:${yaw}`); },
    landing6a750: (_state, cue) => { calls.push(`landing:${cue}`); },
    airReturn6a5a4: () => { calls.push('airReturn'); },
    groundReturn6a474: () => { calls.push('groundReturn'); },
  };
  return { state, hooks, calls, result, tick: () => tickGredCharge(state, config, hooks) };
}

const AIM = 'face:193|pitch:193:1:16384';

function testVerifiedNumericConfig(): void {
  assert(Object.isFrozen(config), 'verified config is immutable');
  assert(config.groundSlot === 2 && config.airSlot === 2 && config.driftScale === f32(.95) &&
    config.chargeTimer === 30 && config.extensionBudget === 30,
  'config80365854 decodes slots2/2, carry.95 and signed16 timers30/30');
}

function testPhaseZeroOrderAndCarry(): void {
  const f = fixture();
  const originalFace = f.hooks.face6d1a8;
  f.hooks.face6d1a8 = (state, mode, target) => {
    assert(state.phase === 1 && state.chargeTimer560 === 30 && state.extensionBudget54e === 30 &&
      state.chargeState6f7 === 0, 'phase0 seeds phase/timer/budget/lifetime before aim');
    assert(state.hSpeed === 9 && state.hDecel === 7 && state.gravityCoeff === 6 &&
      state.poseAccum7c.z === 13, 'aim precedes physics and pose resets');
    originalFace(state, mode, target);
    state.activeYaw = 12345;
  };
  const originalSetup = f.hooks.setupCallback!;
  f.hooks.setupCallback = state => {
    assert([state.hSpeed, state.yVel, state.hDecel, state.gravityCoeff].every(value => value === 0),
      'setup observes all four velocity fields cleared');
    assert(Object.values(state.poseAccum7c).every(value => value === 0), 'setup observes pose reset');
    assert(state.activeYaw === 12345 && state.aimTarget524.x === 100,
      'aim yaw mutation remains live while saved target is unchanged');
    originalSetup(state);
  };
  f.tick();
  assert(f.calls.join('|') === `${AIM}|setup|probe|start:15:4:2:-1:3`,
    'phase0 aim/setup/carry/probe/start order with cursor increment before start');
  assert(f.state.lockYaw === 44 && f.state.yVel === 8 && f.state.gravityCoeff === 0,
    'explicit setup callback supplies authored launch fields');
  assert(f.state.releaseSubphase542 === 9 && f.state.shift18da === 31,
    'phase0 does not invent release-subphase or pitch reset');
  for (const [axis, position, saved] of [['x', 10, 8], ['y', 20, 19], ['z', 30, 27]] as const) {
    const carry = f32(f32(position - saved) * config.driftScale);
    assert(f.state.motion[axis] === carry && f.state.pos[axis] === f32(position + carry),
      `phase0 uses own ${axis} history with f32 stores`);
  }
}

function testPhaseZeroLiveCallbacksAndSlots(): void {
  const f = fixture({ controlWord: 0x40, target: null, heading72: 0xffff });
  const custom: GredChargeConfig = {
    groundSlot: 0x7f, airSlot: 0xff, driftScale: .5, chargeTimer: 0xfffe, extensionBudget: 0xffff,
  };
  f.hooks.face6d1a8 = state => {
    assert(state.activeYaw === -1 && state.lockYaw === 66,
      'absent target seeds only active yaw before setup');
  };
  f.hooks.setupCallback = state => {
    state.pos.x = 30;
    state.savedGroundPos.x = 10;
    state.controlWord = 0; // Slot choice has already happened.
  };
  tickGredCharge(f.state, custom, f.hooks);
  assert(f.state.chargeTimer560 === -2 && f.state.extensionBudget54e === -1,
    'config timers use signed16 decoding');
  assert(f.state.pos.x === 40 && f.state.motion.x === 10, 'setup mutations feed carry immediately');
  assert(f.calls.at(-1) === 'start:15:4:-1:-1:0', 'bit40 chooses signed air slot before setup');
  const ground = fixture({ controlWord: 0x80 });
  ground.hooks.setupCallback = null;
  tickGredCharge(ground.state, custom, ground.hooks);
  assert(ground.calls.at(-1) === 'start:15:4:127:-1:-128', 'other control bits cannot select air slot');
  assert(ground.state.activeYaw === 55 && ground.state.lockYaw === 66 && ground.state.yVel === 0,
    'present target retains active yaw and nullable setup has no implied effects');
}

function testPhaseZeroProbeAndStreamMutations(): void {
  const f = fixture();
  f.hooks.groundProbe677b0 = state => {
    assert(state.motion.x === f32(2 * config.driftScale), 'probe sees completed carry');
    state.streamSlot6ea = 0xff;
    return 0;
  };
  f.hooks.startStream = (state, mask, group, slot, rate) => {
    assert(mask === 15 && group === 4 && slot === -1 && rate === -1 && state.streamSlot6ea === 0,
      'start reads slot after probe and cursor increments first');
    state.contactP0 = 1;
    state.releaseSubphase542 = 5;
  };
  f.tick();
  assert(f.state.phase === 1 && f.state.contactP0 === 1 && f.state.releaseSubphase542 === 5 &&
    !f.calls.includes('release'), 'start mutations persist without synthetic phase1 dispatch');
}

function testPhaseOneSignedReleaseAndSingleCallback(): void {
  for (const contact of [0, 1, 127, 0x80, 0xff, -1]) {
    const f = fixture({ phase: 1, contactP0: contact });
    let releases = 0;
    f.hooks.releaseCallback = state => {
      releases++;
      f.calls.push('release');
      assert(state.phase === 2 && state.releaseSubphase542 === 0 && state.chargeState6f7 === 2,
        'release callback sees phase advance, cleared542 and live6f7=2');
    };
    f.tick();
    const expected = contact === 1 || contact === 127;
    assert(f.calls.join('|') === `tick:15|${AIM}|probe${expected ? '|release' : ''}`,
      `phase1 source order and signed contact ${contact}`);
    assert(f.state.phase === (expected ? 2 : 1) && releases === (expected ? 1 : 0),
      'only positive signed contact triggers release');
    assert(f.state.chargeTimer560 === 99 && f.state.extensionBudget54e === 98,
      'windup does not decrement timer or spend budget');
    if (expected) {
      f.tick();
      assert(releases === 1, 'phase2 cannot call release callback again');
    }
  }
}

function testPhaseOneSameCallMutations(): void {
  const f = fixture({ phase: 1, contactP0: 0 });
  f.hooks.tickStream = state => { state.contactP0 = 1; state.motion.x = 4; };
  f.hooks.face6d1a8 = state => { assert(state.contactP0 === 1, 'aim sees freshly ticked stream'); };
  f.hooks.groundProbe677b0 = state => {
    assert(state.motion.x === f32(4 * config.driftScale), 'carry uses stream-updated motion');
    state.contactP0 = 0xff;
    return 1;
  };
  f.tick();
  assert(f.state.phase === 1 && !f.calls.includes('release'), 'probe negative contact cancels earlier positive gate');
  f.hooks.groundProbe677b0 = state => { state.contactP0 = 1; return 0; };
  f.hooks.releaseCallback = null;
  f.tick();
  assert(Number(f.state.phase) === 2 && f.state.chargeState6f7 === 2,
    'final post-probe contact advances with nullable callback');
}

function testRawEdgePopcount(): void {
  assert(popcountGredChargeEdges(0) === 0 && popcountGredChargeEdges(-1) === 8 &&
    popcountGredChargeEdges(0x0f0f00) === 8 && popcountGredChargeEdges(0xf0f0ff) === 0,
  'raw mask includes eight button/direction bits only');
  for (let bit = 0; bit < 32; bit++) {
    const raw = 1 << bit;
    assert(popcountGredChargeEdges(raw) === (((raw & 0x0f0f00) !== 0) ? 1 : 0),
      `popcount mask bit ${bit}`);
  }
}

function testPhaseTwoBudgetAndFreshInput(): void {
  const f = fixture({ phase: 2, chargeTimer560: 30, extensionBudget54e: 10, freshInput5bc: -1 });
  f.tick();
  assert(f.state.chargeTimer560 === 37 && f.state.extensionBudget54e === 2 && f.state.freshInput5bc === -1,
    'eight simultaneous edges transfer eight before the one-unit timer step without consuming input');
  f.state.freshInput5bc = 0xf00;
  f.tick();
  assert(Number(f.state.chargeTimer560) === 38 && Number(f.state.extensionBudget54e) === 0,
    'extension is capped by remaining signed budget');
  f.tick();
  assert(Number(f.state.chargeTimer560) === 37 && Number(f.state.extensionBudget54e) === 0,
    'exhausted budget cannot extend even when raw edges are nonzero');
  const noEdges = fixture({ phase: 2, chargeTimer560: 30, extensionBudget54e: 30, freshInput5bc: 0 });
  noEdges.tick();
  noEdges.tick();
  assert(noEdges.state.chargeTimer560 === 28 && noEdges.state.extensionBudget54e === 30,
    'without fresh edges there is no held-button/frame-counter extension');
}

function testPhaseTwoSignedBudgetAndRounding(): void {
  const f = fixture({ phase: 2, chargeTimer560: 10, extensionBudget54e: 0xffff, freshInput5bc: 0x100, dt: .25 });
  f.tick();
  assert(f.state.chargeTimer560 === 8.75 && f.state.extensionBudget54e === 0,
    'negative signed budget is transferred exactly, not clamped to zero');
  const rounded = fixture({ phase: 2, chargeTimer560: 0x1000000, extensionBudget54e: 1, freshInput5bc: 0x100, dt: .25 });
  rounded.tick();
  assert(rounded.state.chargeTimer560 === f32(f32(0x1000000 + 1) - .25),
    'extension addition rounds before independent subtraction store');
  const none = fixture({ phase: 2, chargeTimer560: 10, extensionBudget54e: 0xffff });
  none.tick();
  assert(none.state.extensionBudget54e === 0xffff, 'zero edges do not touch even a raw signed budget field');
}

function testPhaseTwoOrderAndNegativeDash(): void {
  const f = fixture({ phase: 2, chargeTimer560: 4, extensionBudget54e: 3, freshInput5bc: 0x300,
    dashStrength1d0f: 0x80, descriptorGravity6c: -2.5, lockYaw: 0xfffe });
  const oldFace = f.hooks.face6d1a8;
  f.hooks.face6d1a8 = (state, mode, target) => {
    assert(state.chargeState6f7 === 2 && state.chargeTimer560 === 6 && state.extensionBudget54e === 1,
      'lifetime and raw extension are applied before aim');
    oldFace(state, mode, target);
  };
  const oldPhysics = f.hooks.physics67310;
  f.hooks.physics67310 = (state, gravity, yaw) => {
    assert(state.dashStrength1d0f === 0 && state.gravityCoeff === -2.5,
      'negative signed dash clears and loads descriptor gravity before physics');
    assert(state.pos.x === f32(10 + f32(config.driftScale)), 'carry occurs before physics');
    oldPhysics(state, gravity, yaw);
  };
  f.tick();
  assert(f.calls.join('|') === `${AIM}|physics:1:-2|probe|tick:15`,
    'phase2 aims, carries, integrates, probes and conditionally ticks in source order');
  assert(f.state.chargeTimer560 === 5, 'timer decrements after physics/probe');
  for (const dash of [0, 1, 127]) {
    const positive = fixture({ phase: 2, dashStrength1d0f: dash });
    positive.tick();
    assert(positive.state.dashStrength1d0f === dash && positive.state.gravityCoeff === 6,
      'nonnegative dash preserves field and gravity');
  }
}

function testPhaseTwoTimerBoundary(): void {
  const f = fixture({ phase: 2, chargeTimer560: .25, dt: .5, contactP0: 0xff });
  f.tick();
  assert(f.state.chargeTimer560 === -.25 && f.state.phase === 2 && f.state.chargeState6f7 === 2 &&
    !f.calls.includes('tick:15'), 'positive timer branch subtracts across zero without same-call expiry');
  f.calls.length = 0;
  f.tick();
  assert(Number(f.state.phase) === 3 && Number(f.state.chargeState6f7) === 0 && f.state.chargeTimer560 === -.25,
    'next nonpositive-timer dispatch ticks and ends charge without subtracting');
  assert(f.calls.join('|') === `${AIM}|physics:1:66|probe|tick:15`, 'expired branch still runs full movement before tick');
  const zero = fixture({ phase: 2, chargeTimer560: 0, contactP0: 0 });
  zero.hooks.tickStream = state => { state.contactP0 = 0x80; };
  zero.tick();
  assert(zero.state.phase === 3 && zero.state.chargeTimer560 === 0 && zero.state.chargeState6f7 === 0,
    'timer equality uses expired branch and post-tick negative contact');
}

function testPhaseTwoConditionalStreamAndLiveTimer(): void {
  for (const contact of [0, 1, 127, 0x80, 0xff, -1]) {
    const f = fixture({ phase: 2, chargeTimer560: 1, contactP0: contact });
    f.tick();
    assert(f.calls.includes('tick:15') === (contact >= 0 && contact < 128),
      'positive timer ticks only with nonnegative signed contact');
    assert(f.state.phase === 2 && f.state.chargeTimer560 === 0,
      'subtraction to exact zero does not switch branches within dispatch');
  }
  const f = fixture({ phase: 2, chargeTimer560: 10, contactP0: 1 });
  f.hooks.tickStream = state => { state.contactP0 = -1; };
  f.tick();
  assert(f.state.phase === 2 && f.state.chargeTimer560 === 9,
    'negative contact authored by positive-timer tick does not end charge early');
  f.hooks.groundProbe677b0 = state => { state.chargeTimer560 = 0; return 0; };
  f.tick();
  assert(Number(f.state.phase) === 3 && Number(f.state.chargeTimer560) === 0,
    'timer condition is read after movement/probe, not cached at entry');
  const rescued = fixture({ phase: 2, chargeTimer560: 0, extensionBudget54e: 1,
    freshInput5bc: 0x100, contactP0: -1 });
  rescued.tick();
  assert(rescued.state.phase === 2 && rescued.state.chargeTimer560 === 0 && !rescued.calls.includes('tick:15'),
    'raw extension before condition rescues an initially expired timer for this dispatch');
}

function testPhaseThreePitchDamping(): void {
  for (const pitch of [0, 10, -10, 11, -11, 0x7fff, 0x8000, 0xffff]) {
    const f = fixture({ phase: 3, shift18da: pitch, dt: .25, lockYaw: 0xffff });
    const expected = s16(Math.trunc(f32(s16(pitch) * f32(.9))));
    f.hooks.physics67310 = (state, gravity, yaw) => {
      assert(state.shift18da === expected && gravity === 1 && yaw === -1,
        'phase3 rounds pitch product then truncates signed16 before primary physics');
    };
    f.tick();
    assert(f.state.shift18da === expected, 'pitch damping is independent of dt');
  }
}

function testPhaseThreeLandingBeforeTick(): void {
  const f = fixture({ phase: 3, contactP0: 0xff, wallContact: 1, dt: .25 });
  f.result.landing = -1; // Source accepts any nonzero result.
  f.hooks.landing6a750 = (state, cue) => {
    f.calls.push(`landing:${cue}`);
    assert(state.actionFlag73f === 0 && state.controlWord === 0x8000000c,
      'landing cue observes cleared action flag and low control bits only');
    assert(state.shift18da === 27 && state.landingTimer694 === 70,
      'landing timer and pitch reset occur after upper cue');
    state.dt = .5;
  };
  f.tick();
  assert(f.calls.join('|') === 'physics:1:66|probe|landing:7',
    'accepted landing with negative contact returns before stream or idle return');
  assert(f.state.landingTimer694 === 8.5 && f.state.shift18da === 0,
    'verified ae34 landing base is8 and reads post-cue dt');
  assert(f.state.hSpeed === 9 && f.state.hDecel === 7 && f.state.yVel === 8 && f.state.gravityCoeff === 6,
    'immediate landing branch adds no return-branch velocity resets');
  const fractional = fixture({ phase: 3, contactP0: -1, dt: f32(.1) });
  fractional.result.landing = 1;
  fractional.tick();
  assert(fractional.state.landingTimer694 === f32(8 + f32(.1)), 'landing timer uses an f32 addition store');
}

function testPhaseThreeCompletionAndCachedGround(): void {
  for (const landing of [0, 1]) {
    for (const contact of [0, 1, 0x80]) {
      if (landing !== 0 && contact === 0x80) continue;
      const f = fixture({ phase: 3, contactP0: contact, wallContact: 0 });
      f.result.landing = landing;
      f.hooks.tickStream = state => {
        f.calls.push('tick:15');
        state.wallContact = 0xff;
        state.contactP0 = -1;
        f.result.landing = 1 - landing;
      };
      const exit = (state: GredChargeState) => {
        f.calls.push(landing === 0 ? 'airReturn' : 'groundReturn');
        assert(state.actionFlag73f === 0 && state.controlWord === 0x8000000c &&
          state.hSpeed === 0 && state.hDecel === 0,
        'return helper observes action/control/horizontal resets');
        assert(state.yVel === 8 && state.gravityCoeff === 6 && state.landingTimer694 === 70,
          'stream-complete branch leaves vertical velocity, gravity and landing timer alone');
      };
      f.hooks.airReturn6a5a4 = exit;
      f.hooks.groundReturn6a474 = exit;
      f.tick();
      assert(f.calls.join('|') === `physics:1:66|probe|tick:15|${landing === 0 ? 'airReturn' : 'groundReturn'}`,
        'completion after tick uses cached probe, with no second landing check');
      assert(f.state.shift18da === 27 && f.state.phase === 3,
        'return housekeeping and phase mutation belong to explicit host helper');
    }
  }
}

function testPhaseThreeNoCompletionAndPostProbeContact(): void {
  const f = fixture({ phase: 3, contactP0: 0, wallContact: 0 });
  f.result.landing = 1;
  f.tick();
  assert(f.calls.join('|') === 'physics:1:66|probe|tick:15' && f.state.actionFlag73f === 1 &&
    f.state.hSpeed === 9 && f.state.hDecel === 7, 'nonnegative contact and incomplete stream remain active');
  f.calls.length = 0;
  f.hooks.groundProbe677b0 = state => { f.calls.push('probe'); state.contactP0 = -1; return 1; };
  f.tick();
  assert(f.calls.join('|') === 'physics:1:66|probe|landing:7',
    'landing branch observes contact authored by ground callback in the same dispatch');
}

function testFactoryAndInvalidPhase(): void {
  const original = fixture().state;
  const copied = createGredChargeState(original);
  for (const key of ['aimTarget524', 'pos', 'savedGroundPos', 'motion', 'poseAccum7c'] as const) {
    assert(copied[key] !== original[key], `factory clones ${key}`);
  }
  copied.pos.x = 999;
  assert(original.pos.x === 10 && copied.target === original.target,
    'factory isolates vector storage while retaining target identity');
  for (const phase of [4, -1, 0x80]) {
    const f = fixture({ phase });
    let error: unknown;
    try { f.tick(); } catch (caught) { error = caught; }
    assert(error instanceof RangeError && f.calls.length === 0, 'invalid signed phase is rejected before hooks');
  }
}

/** Seventeen focused groups, including signed-byte, signed-budget, source-clock
 * boundaries and callback/stream mutations within one dispatched phase. */
export function runGredChargeEngineSelfTest(): void {
  testVerifiedNumericConfig();
  testPhaseZeroOrderAndCarry();
  testPhaseZeroLiveCallbacksAndSlots();
  testPhaseZeroProbeAndStreamMutations();
  testPhaseOneSignedReleaseAndSingleCallback();
  testPhaseOneSameCallMutations();
  testRawEdgePopcount();
  testPhaseTwoBudgetAndFreshInput();
  testPhaseTwoSignedBudgetAndRounding();
  testPhaseTwoOrderAndNegativeDash();
  testPhaseTwoTimerBoundary();
  testPhaseTwoConditionalStreamAndLiveTimer();
  testPhaseThreePitchDamping();
  testPhaseThreeLandingBeforeTick();
  testPhaseThreeCompletionAndCachedGround();
  testPhaseThreeNoCompletionAndPostProbeContact();
  testFactoryAndInvalidPhase();
}
