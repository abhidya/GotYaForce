import { createNinjaShurikenFlight, stepNinjaShurikenFlight, NINJA_SHURIKEN_FLIGHT_CONSTANTS } from './ninjaShurikenFlight.js';
import type { NinjaShurikenFlightContext, NinjaShurikenFlightState, NinjaShurikenRow } from './ninjaShurikenFlight.js';

const check = (condition: boolean, message: string): void => { if (!condition) throw new Error(message); };
const near = (actual: number, expected: number, message: string, tolerance = 1e-6): void =>
  check(Math.abs(actual - expected) <= tolerance, `${message}: ${actual} != ${expected}`);
const f = Math.fround;
const C = NINJA_SHURIKEN_FLIGHT_CONSTANTS;
const origin = { x: 0, y: 0, z: 0 };
const pending = (row: NinjaShurikenRow = 0): NinjaShurikenFlightState => createNinjaShurikenFlight(row, { origin, yaw: 0 });
const active = (row: NinjaShurikenRow = 0): NinjaShurikenFlightState => stepNinjaShurikenFlight(pending(row)).state;
const impacts = (result: ReturnType<typeof stepNinjaShurikenFlight>): number => result.events.filter(e => e.kind === 'impact').length;
const fail = (message: string): never => { throw new Error(message); };

/** Source-order and negative controls, with no Battle/actor/ROM asset dependency. */
export function runSelfTest(): void {
  for (const row of [0, 1, 2, 3] as const) {
    const seed = createNinjaShurikenFlight(row, { origin, yaw: 0, ownerScale: 3, collisionScale: 4, collisionScaleRatio: .75 });
    check(seed.phase === 'pending' && !seed.hitActive && !seed.visible, 'allocation remains pending');
    near(seed.life, 0, 'life not initialized at allocation'); near(seed.pos.z, 0, 'allocation has no movement');
    near(seed.speed, 0, 'allocation has no flight speed'); near(seed.spinAngleS16, 0, 'allocation has no spin');
    Object.freeze(seed.pos); Object.freeze(seed.velocity); Object.freeze(seed.previousPos); Object.freeze(seed);
    const before = JSON.stringify(seed);
    const initialized = stepNinjaShurikenFlight(seed);
    const state = initialized.state;
    check(JSON.stringify(seed) === before, 'step never mutates input or input vectors');
    check(state.phase === 'active' && state.hitActive && state.visible, 'init enables drawing and HIT');
    check(initialized.events.length === 1 && initialized.events[0]?.kind === 'initialized', 'init emits no launch flash, impact or sound');
    check(initialized.events[0]?.kind === 'initialized' && initialized.events[0].row === row, 'row preserved');
    near(state.life, 599, 'successful init invokes active same pass'); near(state.pos.z, 40, 'init includes exactly one speed40 move');
    near(state.pos.y, f(-C.initialGravity * .5), 'same-pass half gravity displacement');
    near(state.velocity.y, -C.initialGravity, 'same-pass vertical acceleration');
    near(state.velocity.z, f(f(40 / Math.hypot(40, C.initialGravity)) * 40), 'full-vector normalize before restoring Y');
    near(state.previousPos.z, 0, 'first segment begins at resolved origin');
    near(state.spinAngleS16, 0x1800, 'same-pass spin'); near(state.gravityTimer, 4, 'no-target timer stays unchanged');
    near(state.modelScale, 3, 'inherited model scale'); near(state.visualScale, 6, 'drawing includes extra table scale2');
    near(state.collisionScale, 4, 'draw multiplier does not inflate HIT'); near(state.collisionScaleRatio, .75, 'inherited collision ratio independent');
    const second = stepNinjaShurikenFlight(state);
    near(second.state.life, 598, 'one decrement per later dispatch');
    near(second.state.pos.z, f(40 + state.velocity.z), 'next move uses previous normalized XZ');
    near(second.state.previousPos.z, 40, 'previous position follows segment start');
    check(second.events.length === 0, 'initialization event only once');
  }
  let unsupportedRowRejected = false;
  try { createNinjaShurikenFlight(4 as NinjaShurikenRow, { origin, yaw: 0 }); } catch { unsupportedRowRejected = true; }
  check(unsupportedRowRejected, 'Powered row4 cannot enter scoped rows0–3 engine');

  // Row2 alone adds the current owner offset. Reinitialization replaces the
  // allocation position, rather than adding the offset twice or banking it.
  for (const row of [0,1,2,3] as const) {
    const seed=createNinjaShurikenFlight(row,{origin:{x:10,y:20,z:30},yaw:0,ownerOffset7b0:{x:150,y:1,z:2}});
    near(seed.pos.x,row===2?160:10,'row2 allocation offset gate');
    const next=stepNinjaShurikenFlight(seed,{initPose:()=>({origin:{x:11,y:22,z:33},yaw:0,ownerOffset7b0:{x:-70,y:3,z:4}})}).state;
    near(next.previousPos.x,row===2?-59:11,'init samples new offset rather than old allocation offset');
    near(next.previousPos.y,row===2?25:22,'full three-axis offset at phase0');
    near(next.previousPos.z,row===2?37:33,'offset remains world-space rather than yaw transformed');
  }

  // Pose is recomputed at phase0, but saved launch aim can differ from live target.
  {
    let resolutions = 0;
    const seed = createNinjaShurikenFlight(0, { origin, yaw: 0, ownerScale: 2, initialAimPoint: { x: 1010, y: 20, z: 30 } });
    const ctx: NinjaShurikenFlightContext = { initPose: () => {
      resolutions++; return { origin: { x: 10, y: 20, z: 30 }, yaw: Math.PI };
    } };
    const state = stepNinjaShurikenFlight(seed, ctx).state;
    near(state.previousPos.x, 10, 'phase0 samples animated muzzle X'); near(state.previousPos.y, 20, 'phase0 samples muzzle Y');
    near(state.previousPos.z, 30, 'phase0 samples muzzle Z');
    check(state.pos.x > 49 && Math.abs(state.pos.z - 30) < .0001, 'saved launch point determines aimed heading');
    check(state.velocity.y > 0, 'low ballistic root gives upward initial velocity');
    near(state.yaw, f(Math.PI), 'drawing yaw remains owner yaw, not aimed flight direction');
    near(state.visualScale, 4, 'allocation model scale survives later pose resolution');
    near(state.collisionScale, 2, 'init does not recopy inherited collision scale');
    stepNinjaShurikenFlight(state, ctx); check(resolutions === 1, 'muzzle only resolved at init');
    const noAim = stepNinjaShurikenFlight(seed, { initPose: () => ({ origin, yaw: Math.PI / 2, initialAimEnabled: false }) }).state;
    near(noAim.pos.x, 40, 'absent owner target launches along owner yaw'); near(noAim.pos.y, -C.initialGravity * .5, 'absent target uses pitch0');
    near(noAim.initialAimPoint!.x, 1010, 'disabled owner target gate does not overwrite saved aim');
  }

  // HIT registration failure precedes pose, life600 and same-pass active.
  {
    const result = stepNinjaShurikenFlight(pending(), { hitRegistrationSucceeds: false,
      initPose: () => fail('failed registration must not resolve pose'),
      outsideBounds: () => fail('failed registration must not run active'),
    });
    check(result.state.phase === 'retiring' && result.state.reason === 'hit-registration', 'failure enters phase2');
    check(!result.state.hitActive && !result.state.visible && result.events.length === 0, 'failure has no live HIT/drawing/launch');
    near(result.state.life, 0, 'registration failure has not written600'); near(result.state.pos.z, 0, 'registration failure has no move');
    const released = stepNinjaShurikenFlight(result.state);
    check(released.state.phase === 'released', 'next dispatch phase2 releases');
    const freed = stepNinjaShurikenFlight(released.state);
    check(freed.state.phase === 'freed' && freed.events[0]?.kind === 'freed', 'phase3 frees next dispatch');
    check(stepNinjaShurikenFlight(freed.state).events.length === 0, 'no repeated free');
  }

  // Life/bounds/contact precedence: all occur before visual spin or movement.
  for (const reason of ['lifetime', 'bounds', 'contact'] as const) {
    const seed = { ...active(), life: reason === 'lifetime' ? 1 : 40 };
    const result = stepNinjaShurikenFlight(seed, {
      outsideBounds: () => reason === 'lifetime' ? fail('expired life skips bounds') : reason === 'bounds',
      priorContact: true,
      targetOwner833a4: () => fail('early retirement skips target notification'),
      scale833ec: () => fail('early retirement skips shared scale'),
      speedGravity83610: () => fail('early retirement skips shared speed/gravity'),
      attraction83714: () => fail('early retirement skips attraction'),
      terrain84170: () => fail('early retirement skips terrain'),
    });
    check(result.state.phase === 'retiring' && result.state.reason === reason, 'early retirement precedence');
    check(!result.state.hitActive && result.state.visible, 'early retirement HIT-off now, hide next dispatch');
    near(result.state.life, seed.life - 1, 'all early paths decrement life');
    near(result.state.pos.z, seed.pos.z, 'early retirement does not move');
    near(result.state.spinAngleS16, seed.spinAngleS16, 'early retirement does not spin');
    check(impacts(result) === (reason === 'contact' ? 1 : 0), 'only contact creates impact');
    if (reason === 'contact') {
      const impact = result.events[0];
      check(impact?.kind === 'impact' && impact.row === 0 && impact.pos.z === seed.pos.z, 'impact85e00 row0 at old position, before HIT-off');
    }
    const release = stepNinjaShurikenFlight(result.state, { terrain84170: () => fail('retirement does not query terrain') });
    check(release.state.phase === 'released' && !release.state.visible, 'phase2 hides without fade/shrink');
    near(release.state.pos.z, seed.pos.z, 'phase2 does not move'); near(release.state.life, result.state.life, 'phase2 does not age');
    check(stepNinjaShurikenFlight(release.state).state.phase === 'freed', 'phase3 frees');
  }
  {
    let boundsZ = NaN;
    const result = stepNinjaShurikenFlight(active(), { outsideBounds: p => { boundsZ = p.z; return false; } });
    near(boundsZ, 40, 'bounds uses pre-motion position'); check(result.state.pos.z > boundsZ, 'motion follows successful bounds');
    const firstContact = stepNinjaShurikenFlight(pending(3), { priorContact: true });
    near(firstContact.state.pos.z, 0, 'init same-pass contact preempts first move');
    near(firstContact.state.life, 599, 'init same-pass contact still predecrements600');
    check(firstContact.events[0]?.kind === 'initialized' && impacts(firstContact) === 1, 'init/contact events preserve source order');
  }

  // Owner guard phase0/1 skips their handlers and dispatches phase2 immediately.
  for (const ownerInvalid of ['owner-dead', 'owner-changed'] as const) {
    for (const seed of [pending(), active()]) {
      const result = stepNinjaShurikenFlight(seed, { ownerInvalid,
        initPose: () => fail('owner invalid skips init'), outsideBounds: () => fail('owner invalid skips active') });
      check(result.state.phase === 'released' && result.state.reason === ownerInvalid, 'owner guard dispatches phase2 same call');
      check(!result.state.visible && !result.state.hitActive && impacts(result) === 0, 'owner loss hides/disables without impact');
      near(result.state.life, seed.life, 'owner guard precedes life decrement'); near(result.state.pos.z, seed.pos.z, 'owner guard has no motion');
      check(stepNinjaShurikenFlight(result.state).state.phase === 'freed', 'owner loss frees next dispatch');
    }
    const alreadyRetiring = stepNinjaShurikenFlight(active(), { priorContact: true }).state;
    const result = stepNinjaShurikenFlight(alreadyRetiring, { ownerInvalid });
    check(result.state.reason === 'contact', 'owner guard does not reroute phases2/3');
  }

  // Exactly599 moves across600 active invocations; first active is init's call.
  for (const row of [0, 1, 2, 3] as const) {
    let state = pending(row), calls = 0, changes = 0, impactCount = 0;
    while (state.phase === 'pending' || state.phase === 'active') {
      const result = stepNinjaShurikenFlight(state); calls++;
      if (result.state.pos.z !== state.pos.z || result.state.pos.y !== state.pos.y) changes++;
      impactCount += impacts(result); state = result.state;
      if (calls > 601) fail('natural source life must terminate');
    }
    check(calls === 600 && changes === 599 && state.life === 0, 'natural life boundary and same-pass init count');
    check(state.phase === 'retiring' && state.reason === 'lifetime' && impactCount === 0, 'natural expiry never creates impact');
  }

  // Retargeting only adjusts gravity every4 targeted ticks. Never XZ homing.
  {
    const point = { x: 1000, y: 1000, z: 1000 };
    let state = createNinjaShurikenFlight(0, { origin, yaw: 0, targetUid: 'a', targetPoint: point });
    let notifications = 0;
    const ctx: NinjaShurikenFlightContext = { currentTarget: { uid: 'a', point, valid: true },
      targetOwner833a4: () => { notifications++; } };
    for (let i = 1; i <= 4; i++) {
      state = stepNinjaShurikenFlight(state, ctx).state;
      near(state.gravityTimer, i === 4 ? 4 : 4 - i, 'signed-short target timer cadence');
      near(state.gravity, i === 4 ? f(C.initialGravity - C.gravityChange) : C.initialGravity, 'gravity changes only fourth targeted tick');
      near(state.pos.x, 0, 'target refresh does not turn horizontal heading'); near(state.velocity.x, 0, 'no X velocity from lateral target');
    }
    check(notifications === 4, '833a4 runs every targeted motion, not every gravity refresh');
    near(state.spinAngleS16, 0x6000, 'visual spin independent of flight heading');
    state = stepNinjaShurikenFlight(stepNinjaShurikenFlight(state, ctx).state, ctx).state;
    near(state.spinAngleS16, -0x7000, 'source visual spin wraps signed16');
  }
  for (const currentTarget of [null, { uid: 'a', point: origin, valid: false }, { uid: 'b', point: origin, valid: true }]) {
    const seed = { ...active(), targetUid: 'a', targetPoint: { x: 0, y: 10, z: 1000 }, gravityTimer: 1 };
    const lost = stepNinjaShurikenFlight(seed, { currentTarget,
      targetOwner833a4: () => fail('lost target must not notify') }).state;
    check(lost.targetUid === null && lost.targetPoint === null, 'target invalidation clears retained target');
    near(lost.gravityTimer, 1, 'loss precedes target countdown'); near(lost.gravity, seed.gravity, 'loss retains current gravity');
    check(lost.pos.z > seed.pos.z, 'target loss still performs ballistic movement');
    const later = stepNinjaShurikenFlight(lost, { currentTarget: { uid: 'a', point: origin, valid: true } }).state;
    check(later.targetUid === null, 'a new valid context cannot reacquire a cleared target');
  }
  for (const high of [false, true]) {
    const gravity = high ? f(7.45) : f(.1);
    const seed = { ...active(), gravity, gravityTimer: 1, targetUid: 'a',
      targetPoint: { x: 0, y: high ? -100000 : 100000, z: 1000 } };
    const result = stepNinjaShurikenFlight(seed).state;
    near(result.gravity, high ? 7.5 : 0, 'desired gravity is clamped0..7.5 before change cap');
    near(result.pos.y, f(seed.pos.y + f(seed.velocity.y - f(result.gravity * .5))), 'fresh gravity applies to same frame motion');
  }
  {
    const seed = { ...active(), targetUid: 'a', targetPoint: { x: 0, y: 0, z: 41 }, gravityTimer: 1 };
    const result = stepNinjaShurikenFlight(seed);
    check(result.state.phase === 'active' && impacts(result) === 0, 'rows0/3 never create Powered proximity children');
  }

  // Explicit shared seams: notification, scale, speed+gravity, normalize, attract, terrain.
  {
    const order: string[] = [];
    const seed = { ...active(), targetUid: 'a', targetPoint: { x: 0, y: 0, z: 1000 },
      velocity: { x: 3, y: 4, z: 0 }, gravityTimer: 2 };
    const result = stepNinjaShurikenFlight(seed, {
      outsideBounds: () => { order.push('bounds'); return false; },
      targetOwner833a4: s => { order.push('target'); near(s.pos.x, 3, 'notification after motion'); near(s.velocity.y, f(4 - C.initialGravity), 'notification after vertical acceleration'); },
      scale833ec: s => { order.push('scale'); near(s.speed, 40, 'scale precedes speed modifier'); return { modelScale: 5, collisionScale: 6, collisionScaleRatio: 7 }; },
      speedGravity83610: s => { order.push('speed-gravity'); near(s.visualScale, 10, 'shared scale reflected first'); return { speed: 20, gravity: .8 }; },
      attraction83714: s => {
        order.push('attraction'); near(s.gravity, f(.8), 'modifier gravity retained'); near(s.velocity.y, f(4 - C.initialGravity), 'vertical velocity restored after normalize');
        const expectedX = f(f(3 / Math.hypot(3, f(4 - C.initialGravity))) * 20);
        near(s.velocity.x, expectedX, 'normalize uses full vector and new scalar speed');
        check(Math.abs(Math.hypot(s.velocity.x, s.velocity.y) - 20) > 1, 'restoredY does not force total speed to scalar20');
        return { consumed: false, pos: { x: 8, y: 9, z: 10 } };
      },
      terrain84170: s => { order.push('terrain'); near(s.pos.x, 8, 'terrain sees attraction-adjusted position'); return { x: 2, y: 3, z: 4 }; },
    });
    check(order.join(',') === 'bounds,target,scale,speed-gravity,attraction,terrain', 'exact shared-hook source order');
    check(result.state.phase === 'retiring' && result.state.reason === 'terrain' && result.state.hitActive && result.state.visible, 'terrain returns phase2 with HIT still active');
    check(impacts(result) === 1 && !result.events.some(e => e.kind === 'hit-disabled'), 'terrain emits impact but defers HIT disable');
    near(result.state.pos.z, 4, 'terrain contact snap retained'); near(result.state.collisionScale, 6, 'scale hook collision scale');
    near(result.state.collisionScaleRatio, 7, 'scale hook collision ratio'); near(seed.velocity.y, 4, 'callbacks did not mutate original');
    const released = stepNinjaShurikenFlight(result.state);
    check(released.state.phase === 'released' && !released.state.hitActive && !released.state.visible, 'next phase2 disables HIT and hides');
    check(released.events.map(e => e.kind).join(',') === 'hit-disabled,hidden', 'terrain disable timing differs from contact');
    check(stepNinjaShurikenFlight(released.state).state.phase === 'freed', 'terrain phase3 frees without moving tail');
  }
  {
    const result = stepNinjaShurikenFlight(active(), {
      attraction83714: () => ({ consumed: true, pos: { x: 1, y: 2, z: 3 } }),
      terrain84170: () => fail('83714 consumption short-circuits terrain'),
    });
    check(result.state.phase === 'retiring' && result.state.reason === 'attraction' && !result.state.hitActive, 'attraction disables immediately');
    near(result.state.pos.z, 3, 'attraction point retained'); check(impacts(result) === 0, '83714 disappearance never creates terrain/contact impact');
    const unbound = stepNinjaShurikenFlight(active()).state;
    check(unbound.phase === 'active' && unbound.hitActive, 'omitted probes inject no phantom collision or attraction');
  }
}
