import { createGredRangedFlight, stepGredRangedFlight, GRED_RANGED_FLIGHT_CONSTANTS } from './gredRangedFlight.js';
import type { GredRangedFlightContext, GredRangedFlightState, GredRangedRow } from './gredRangedFlight.js';

const check = (condition: boolean, message: string): void => { if (!condition) throw new Error(message); };
const near = (actual: number, expected: number, message: string, tolerance = 1e-6): void =>
  check(Math.abs(actual - expected) <= tolerance, `${message}: ${actual} != ${expected}`);
const origin = { x: 0, y: 0, z: 0 };
const direction = { x: 0, y: 0, z: 1 };
const f = Math.fround;
const C = GRED_RANGED_FLIGHT_CONSTANTS;
const active = (row: GredRangedRow = 43, scale = 1): GredRangedFlightState =>
  stepGredRangedFlight(createGredRangedFlight(row, origin, direction, scale)).state;

/** Durable source-order and boundary tests. No actor, renderer or ROM assets needed. */
export function runSelfTest(): void {
  for (const row of [43, 101, 102] as const) {
    const pending = createGredRangedFlight(row, origin, { x: 0, y: 0, z: 7 }, 2);
    check(pending.phase === 'pending' && !pending.hitActive && !pending.visible, 'allocation is pending');
    near(pending.pos.z, 0, 'allocation does not move');
    near(pending.life, 0, 'life belongs to init, not allocation');
    const before = JSON.stringify(pending);
    const first = stepGredRangedFlight(pending);
    const state = first.state;
    check(JSON.stringify(pending) === before, 'init leaves input untouched');
    check(state.phase === 'active' && state.hitActive && state.visible, 'init enables HIT and visibility');
    check(first.events.length === 1 && first.events[0]?.kind === 'initialized', 'init event is emitted once');
    check(first.events[0]?.kind === 'initialized' && first.events[0].sound === 185, 'source cue185');
    near(state.pos.z, 1, 'init advances exactly one normalized unit');
    near(state.previousPos.z, 0, 'init retains segment start');
    near(state.origin.z, 0, 'init saves fixed origin');
    near(state.velocity.z, 80, 'init velocity is source speed80');
    near(state.speed, 80, 'no init acceleration');
    near(state.life, 300, 'no init life decrement or active fallthrough');
    near(state.distance, 1, 'init distance');
    near(state.length, 1, 'init drawing length');
    near(state.visualScale.z, f(1 / 22), 'source longitudinal normalizer22');
    const width = f(f(40 / 36.959999084472656) * 2);
    near(state.widthScale, width, 'width uses original model normalizer and inherited scale');
    near(state.baseWidth, width, 'baseline width');
    near(state.collisionScale, width, 'HIT sphere scale uses width');
    near(state.collisionScaleRatio, 1, 'initial width ratio');
    near(state.visualScale.x, width, 'visual X width');
    near(state.visualScale.y, width, 'visual Y width');
    const moved = stepGredRangedFlight(state).state;
    near(moved.pos.z, 81, 'first active frame moves80 before acceleration');
    near(moved.previousPos.z, 1, 'previousPos is old tip, not old origin');
    near(moved.speed, 80.5, 'active increments speed after movement');
    near(moved.velocity.z, 80, 'stored velocity remains current movement speed');
    near(moved.life, 299, 'active decrements life once');
    near(stepGredRangedFlight(moved).state.pos.z, 161.5, 'next movement uses accelerated speed');
    near(moved.collisionScale, width, 'drawing length never stretches HIT sphere');
    check(moved.visualScale.z !== moved.collisionScale, 'visual and collision scales are independent');
    const capped = stepGredRangedFlight({ ...state, pos: { x: 0, y: 0, z: 2000 }, speed: 160 }).state;
    near(capped.speed, 160, 'speed upper cap');
    near(capped.pos.z, 2160, 'cap applies after source motion');
    near(capped.length, row === 101 ? 500 : 1000, 'exact row drawing length cap');
    near(capped.collisionScale, width, 'drawing cap does not change collision extent');
  }

  // Resolve pose at phase0, not when the constructor allocates the child.
  {
    const launch = { x: 10, y: 20, z: 30 };
    let resolves = 0;
    const poseContext: GredRangedFlightContext = {
      initPose: () => { resolves++; return { origin: launch, direction: { x: 4, y: 0, z: 0 }, ownerModelScale: 3, targetPoint: null }; },
    };
    const initialized = stepGredRangedFlight(createGredRangedFlight(43, origin, direction), poseContext).state;
    near(initialized.pos.x, 11, 'delayed pose origin and aim'); near(initialized.pos.y, 20, 'delayed pose Y');
    near(initialized.pos.z, 30, 'delayed pose Z'); near(initialized.origin.x, 10, 'saved launch origin');
    near(initialized.previousPos.x, 10, 'delayed segment origin');
    near(initialized.baseWidth, f(f(40 / C.widthNormalizer) * 3), 'delayed inherited scale');
    stepGredRangedFlight(initialized, poseContext);
    check(resolves === 1, 'pose only resolved at init');
    near(launch.x, 10, 'launch pose vectors are not mutated');
  }

  // Registration failure dispatches state2/sub0 on the NEXT update.
  {
    const pending = createGredRangedFlight(43, origin, direction);
    const failure = stepGredRangedFlight(pending, {
      hitRegistrationSucceeds: false,
      initPose: () => { throw new Error('HIT failure precedes pose resolution'); },
    });
    check(failure.state.phase === 'retiring' && failure.state.reason === 'hit-registration', 'failed HIT enters state2/sub0');
    check(!failure.state.hitActive && !failure.state.visible && failure.events.length === 0, 'failed HIT emits no launch');
    near(failure.state.life, 300, 'source life set before failed registration');
    near(failure.state.pos.z, 0, 'failed registration does not move');
    const released = stepGredRangedFlight(failure.state);
    check(released.state.phase === 'released', 'state2/sub0 sets phase3');
    const freed = stepGredRangedFlight(released.state);
    check(freed.state.phase === 'freed' && freed.events[0]?.kind === 'freed', 'phase3 frees only on subsequent dispatch');
    check(stepGredRangedFlight(freed.state).events.length === 0, 'free event occurs once');
  }

  // Accepted previous-pass bits 0x02/0x20/0x80 each retire, other bits do not.
  for (const flag of [2, 0x20, 0x80]) {
    const initial = active();
    const result = stepGredRangedFlight(initial, { priorContactBits: flag });
    check(result.state.phase === 'contact-tail' && !result.state.hitActive && result.state.visible, 'accepted contact disables HIT and retains drawing');
    check(result.state.reason === 'contact', 'contact reason');
    near(result.state.pos.z, 81, 'accepted contact still performs this frame motion');
    near(result.state.life, 300, 'contact bypasses life decrement');
    near(result.state.length, 81, 'contact does not shorten in same frame');
    near(result.state.speed, 80.5, 'contact speed increment precedes retirement');
    check(result.events.filter(e => e.kind === 'hit-disabled').length === 1, 'one HIT disable on contact');
    const firstTail = stepGredRangedFlight(result.state).state;
    near(firstTail.pos.z, 81, 'contact tail is stationary'); near(firstTail.length, .5, 'contact tail subtracts current scalar speed');
    near(firstTail.speed, 80.5, 'contact tail does not accelerate'); near(firstTail.life, 300, 'contact tail does not age life');
    const release = stepGredRangedFlight(firstTail);
    check(release.state.phase === 'released' && !release.state.visible, 'contact tail releases at nonpositive visual length');
    near(release.state.length, -80, 'source negative terminal length is not clamped');
    check(release.events[0]?.kind === 'hidden', 'terminal contact tail hides once');
    check(stepGredRangedFlight(release.state).state.phase === 'freed', 'contact tail next-pass free');
  }
  for (const flag of [0, 1, 4, 8, 0x10, 0x40]) {
    check(stepGredRangedFlight(active(), { priorContactBits: flag }).state.phase === 'active', 'unaccepted contact bit does not retire');
  }

  // Shared hooks preserve source order, short circuits, and terrain point snapping.
  {
    const order: string[] = [];
    const seed = { ...active(), targetPoint: { x: 0, y: 0, z: 1000 } };
    const result = stepGredRangedFlight(seed, {
      afterHoming: s => { order.push('home'); near(s.pos.z, 81, 'homing hook after exactly one motion'); near(s.speed, 80, 'homing before acceleration'); },
      validateTarget: s => { order.push('validate'); near(s.pos.z, 81, 'validation after motion'); near(s.speed, 80.5, 'validation after acceleration'); return false; },
      attraction83714: s => { order.push('attract'); check(s.targetPoint === null, 'validation clears before attraction'); return false; },
      terrain84170: s => { order.push('terrain'); s.pos = { x: 0, y: 0, z: 44 }; return true; },
      outsideBounds: () => { throw new Error('terrain short-circuits bounds'); },
      scale834b0: s => { order.push('scale'); check(s.phase === 'contact-tail' && !s.hitActive, 'scale hook follows retirement'); s.widthScale = 2; },
      speed83524: s => { order.push('speed'); s.speed = 90; },
    });
    check(order.join(',') === 'home,validate,attract,terrain,scale,speed', 'source callback order');
    near(result.state.pos.z, 44, 'terrain snap retained'); near(result.state.distance, 44, 'terrain recomputes distance');
    near(result.state.length, 44, 'terrain snapped length'); near(result.state.life, 300, 'terrain bypasses lifetime');
    near(result.state.collisionScale, 2, 'scale seam updates HIT c0 after retirement');
    near(result.state.collisionScaleRatio, f(2 / result.state.baseWidth), 'scale seam updates c4 ratio');
    near(result.state.visualScale.x, 2, 'scale seam updates drawing'); near(result.state.speed, 90, 'speed seam executes last');
    near(stepGredRangedFlight(result.state).state.length, -46, 'contact tail uses postmodifier speed');
    near(seed.pos.z, 1, 'all hooks mutate clone only'); near(seed.visualScale.x, seed.baseWidth, 'nested vectors remain unchanged');
  }
  {
    const order: string[] = [];
    const result = stepGredRangedFlight(active(), {
      priorContactBits: 2,
      attraction83714: () => { order.push('attraction'); return true; },
      terrain84170: () => { throw new Error('attraction/contact short-circuits terrain'); },
      outsideBounds: () => { throw new Error('attraction/contact short-circuits bounds'); },
      scale834b0: () => { order.push('scale'); }, speed83524: () => { order.push('speed'); },
    });
    check(result.state.reason === 'attraction', 'attraction checked even with previous contact');
    check(order.join(',') === 'attraction,scale,speed', 'attraction short-circuit preserves modifiers');
    check(stepGredRangedFlight(active(), { priorContactBits: 2, attraction83714: () => false }).state.reason === 'contact', 'contact remains when attraction returns false');
  }

  // Bounds short-circuit life; lifetime predecrements after successful motion.
  for (const reason of ['bounds', 'lifetime'] as const) {
    const initial = { ...active(), life: 1 };
    const end = stepGredRangedFlight(initial, reason === 'bounds' ? { outsideBounds: () => true } : {}).state;
    check(end.phase === 'expire-tail' && end.reason === reason && !end.hitActive && end.visible, 'expiry enters moving width tail');
    near(end.pos.z, 81, 'expiry occurs after motion'); near(end.life, reason === 'bounds' ? 1 : 0, 'bounds versus lifetime decrement');
    near(end.widthScale, initial.widthScale, 'no same-frame shrink');
    const tail = stepGredRangedFlight(end, {
      terrain84170: () => { throw new Error('tail never queries terrain'); },
      scale834b0: () => { throw new Error('tail never invokes incoming scale modifier'); },
      speed83524: () => { throw new Error('tail never invokes incoming speed modifier'); },
    }).state;
    near(tail.pos.z, 161, 'width tail moves by stored velocity80, not speed80.5');
    near(tail.speed, 81, 'width tail increments scalar speed'); near(tail.velocity.z, 80, 'width tail never rebuilds velocity');
    near(tail.widthScale, f(end.widthScale * f(.9)), 'width multiplier is original f32(.9)');
    near(tail.collisionScale, end.collisionScale, 'disabled HIT c0 is unchanged in width tail');
    near(tail.collisionScaleRatio, end.collisionScaleRatio, 'disabled HIT c4 is unchanged in width tail');
    near(tail.visualScale.x, tail.widthScale, 'tail drawing follows shrink'); near(tail.distance, 161, 'tail distance recomputed');
    const again = stepGredRangedFlight(tail).state;
    near(again.pos.z, 241, 'second width tail retains original velocity'); near(again.speed, 81.5, 'second width tail scalar acceleration');
    let current = again, frames = 2;
    while (current.phase === 'expire-tail' && frames < 100) { current = stepGredRangedFlight(current).state; frames++; }
    check(current.phase === 'released' && !current.visible, 'finite width tail reaches release');
    check(current.widthScale <= f(.05), 'inclusive original f32(.05) width threshold');
    const freed = stepGredRangedFlight(current);
    check(freed.state.phase === 'freed' && freed.events.length === 1, 'width tail final free event');
  }
  {
    const tail: GredRangedFlightState = { ...active(), phase: 'expire-tail', reason: 'lifetime', hitActive: false,
      widthScale: f(.05) / f(.9), speed: 160 };
    const release = stepGredRangedFlight(tail).state;
    check(release.phase === 'released', 'width exactly threshold releases inclusively');
    near(release.speed, 160, 'width tail scalar speed caps');
    const contact: GredRangedFlightState = { ...active(), phase: 'contact-tail', reason: 'contact', hitActive: false, length: 80 };
    check(stepGredRangedFlight(contact).state.phase === 'released', 'length exactly zero releases inclusively');
  }

  // Owner death/form invalidation precedes dispatch but cannot replace a running tail.
  for (const reason of ['owner-dead', 'owner-changed'] as const) {
    for (const initial of [createGredRangedFlight(43, origin, direction), active()]) {
      const result = stepGredRangedFlight(initial, {
        ownerInvalid: reason,
        initPose: () => { throw new Error('owner invalidation must precede initialization'); },
        attraction83714: () => { throw new Error('owner invalidation must precede active motion'); },
      });
      check(result.state.phase === 'released' && !result.state.hitActive && !result.state.visible, 'owner invalidation dispatches state2/sub0 immediately');
      check(result.state.reason === reason, 'owner invalidation reason');
      near(result.state.pos.z, initial.pos.z, 'invalid owner does not move child');
      const next = stepGredRangedFlight(result.state, { ownerInvalid: reason });
      check(next.state.phase === 'freed' && next.events[0]?.kind === 'freed', 'invalid owner frees on next dispatch');
    }
    const contact = stepGredRangedFlight(active(), { priorContactBits: 2 }).state;
    const continuedContact = stepGredRangedFlight(contact, { ownerInvalid: reason }).state;
    check(continuedContact.phase === 'contact-tail' && continuedContact.reason === 'contact', 'owner invalidation leaves phase2 contact tail alone');
    const expiry = stepGredRangedFlight(active(), { outsideBounds: () => true }).state;
    check(stepGredRangedFlight(expiry, { ownerInvalid: reason }).state.phase === 'expire-tail', 'owner invalidation leaves phase2 width tail alone');
  }

  // c4540 uses transformed target geometry, inclusive clear radius, signed-byte
  // cadence, and at most .35 DEGREES per turning update, not .35 radians.
  {
    const seed = active();
    const turnSeed = { ...seed, targetPoint: { x: 1000, y: 0, z: 1000 } };
    const snapshot = JSON.stringify(turnSeed);
    let notifications = 0;
    const turned = stepGredRangedFlight(turnSeed, { afterHoming: () => { notifications++; } }).state;
    const cap = f(C.radiansPerDegree * f(.35));
    near(Math.atan2(turned.velocity.x, turned.velocity.z), cap, 'homing cap converts degrees to radians', 1e-8);
    near(Math.hypot(turned.pos.x - 0, turned.pos.y, turned.pos.z - 1), 80, 'homing advances exactly one speed-length', 1e-5);
    check(notifications === 1 && turned.trackingCountdown === 1, 'counter reload and homing notification');
    check(JSON.stringify(turnSeed) === snapshot, 'homing leaves target and input vectors unchanged');
    const delayed = stepGredRangedFlight({ ...turnSeed, trackingCountdown: 2 }).state;
    near(delayed.pos.x, 0, 'nonzero countdown moves straight'); near(delayed.pos.z, 81, 'nonzero countdown moves exactly once');
    check(delayed.trackingCountdown === 1, 'countdown decremented once');
    const wrapped = stepGredRangedFlight({ ...turnSeed, trackingCountdown: -128 }).state;
    check(wrapped.trackingCountdown === 127, 'source countdown signed-byte wrap');
    for (const z of [1, 21]) {
      const cleared = stepGredRangedFlight({ ...seed, targetPoint: { x: 0, y: 0, z } }).state;
      check(cleared.targetPoint === null, 'distance at or inside20 clears target'); near(cleared.pos.z, 81, 'clear path still moves once');
    }
    check(stepGredRangedFlight({ ...seed, targetPoint: { x: 0, y: 0, z: 21.01 } }).state.targetPoint !== null, 'just outside20 retains target before validation');
    const behind = stepGredRangedFlight({ ...seed, targetPoint: { x: 0, y: 0, z: -100 } }).state;
    check(behind.targetPoint === null, 'negative dot clears target'); near(behind.pos.z, 81, 'behind-target path stays straight');
    const perpendicular = stepGredRangedFlight({ ...seed, targetPoint: { x: 100, y: 0, z: 1 } }).state;
    check(perpendicular.targetPoint !== null && perpendicular.pos.x > 0, 'zero dot does not clear target');
    const smallAim = { x: Math.tan(cap / 2) * 1000, y: 0, z: 1001 };
    const small = stepGredRangedFlight({ ...seed, targetPoint: smallAim }).state;
    check(Math.atan2(small.velocity.x, small.velocity.z) < cap, 'small requested angle is not forced up to turn cap');
    const refreshed = stepGredRangedFlight(turnSeed, { targetPoint: { x: -1000, y: 0, z: 1000 } }).state;
    check(refreshed.pos.x < 0, 'refresh target point before tracking motion');
    const noReacquire = stepGredRangedFlight(seed, { targetPoint: { x: 1000, y: 0, z: 1000 } }).state;
    check(noReacquire.targetPoint === null, 'fresh point cannot silently reacquire cleared pointer');
    const noTarget = stepGredRangedFlight(seed, { validateTarget: () => { throw new Error('no target needs no geometry validation'); } });
    check(noTarget.state.phase === 'active', 'targetless source path');
    const x = stepGredRangedFlight({ ...seed, pos: { x: 100, y: 0, z: 0 }, velocity: { x: 0, y: 0, z: 80 } }).state;
    near(x.distance, f(Math.hypot(100, 80)), 'distance is Euclidean origin-to-tip, not sum of movement');
  }

  // Durable full-lifetime trace: no accidental actor-action expiry or frame skip.
  {
    let state = active();
    let expectedPosition = 1;
    let speed = 80;
    for (let tick = 1; tick <= 300; tick++) {
      expectedPosition = f(expectedPosition + speed);
      speed = Math.min(f(speed + .5), 160);
      state = stepGredRangedFlight(state).state;
      near(state.pos.z, expectedPosition, `lifetime trace position ${tick}`);
      near(state.speed, speed, `lifetime trace speed ${tick}`);
      near(state.life, 300 - tick, `lifetime trace count ${tick}`);
      check(state.phase === (tick === 300 ? 'expire-tail' : 'active'), `lifetime trace phase ${tick}`);
    }
    check(state.reason === 'lifetime' && state.velocity.z === 160, 'source lifetime boundary uses last speed');
  }
  console.log('G RED ranged flight source lifecycle: passed');
}
