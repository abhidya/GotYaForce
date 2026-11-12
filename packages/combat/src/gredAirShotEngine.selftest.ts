/** Independent source-order observers for18d72c/7e4/8c0/dafc/dbb4/dcb0.
 * These tests do not claim terrain, lower locomotion or instruction parity. */
import { tickGRedAirShotEngine, type GRedAirShotEngineHooks,
  type GRedAirShotEngineState } from './gredAirShotEngine.js';
import type { GRedShotFamily } from './gredShotEngine.js';

function check(value: unknown, label: string): void {
  if (!value) throw new Error(`[gredAirShotEngine] ${label}`);
}
function same(actual: unknown, expected: unknown, label: string): void {
  check(JSON.stringify(actual) === JSON.stringify(expected),
    `${label}: expected ${JSON.stringify(expected)}, got ${JSON.stringify(actual)}`);
}
function fixture(family: GRedShotFamily = 'red', variant: 3 | 4 = 3) {
  const s: GRedAirShotEngineState = { family, variant, phase: 0, dt: 1,
    pos: { x: 20, y: 30, z: 40 }, savedGroundPos: { x: 10, y: 10, z: 10 },
    motion: { x: 9, y: 8, z: 7 }, poseAccum7c: { x: 1, y: 2, z: 3 },
    controlWord: 0x43, hSpeed: 4, yVel: 5, hDecel: 6, gravityCoeff: 7,
    rootAngle1900: -101, shift18da: -3, sideBlend1dfc: -5,
    latch745: 1, timer560: 9, repeatTimer558: 0, streamSlot6ee: 0,
    remaining6ef: 3, ammo774: 5, input5d4: 0, input5d8: 0,
    contactP0: 0, completed1cee: 0, actionFlag6e8: 1, actionFlag73f: 1,
    accumulator80c: 99, lockYaw5ae: 0xfffe, movementCue5e4: 0,
    faceGate1d10: 1, lowerState5db: 0, animationGroup1afc: 2, animationSlot1afd: 5 };
  const calls: unknown[][] = [];
  const h: GRedAirShotEngineHooks = {
    roll6dee8: (_s, arg) => { calls.push(['roll', arg, s.dt, s.repeatTimer558]); return 0; },
    aim6d0dc: (_s, mode, arg) => { calls.push(['aim', mode, arg, s.dt, s.timer560]); return false; },
    startStream: (_s, mask, group, slot, start, blend) => {
      calls.push(['start', mask, group, slot, start, blend]);
    },
    tickStream: (_s, mask) => { calls.push(['tick', mask, s.dt, s.latch745]); },
    primary67310: (_s, scale, yaw) => { calls.push(['primary', scale, yaw, s.dt]); },
    ground677b0: () => { calls.push(['ground', s.dt, s.accumulator80c]); },
    airReturn6a5a4: () => { calls.push(['air-return', s.controlWord, s.phase]); },
    ammo6dbe0: (_s, cell, count, debit) => {
      calls.push(['ammo', cell, count, debit, s.timer560, s.repeatTimer558, s.streamSlot6ee]);
      if (debit) s.ammo774 -= count;
      return true;
    },
    spawnC3be0: (_s, row) => { calls.push(['spawn', row, s.remaining6ef]); },
    capture6bf80: () => { calls.push(['capture', s.latch745, s.phase]); },
    carryEffectB22f4: () => { calls.push(['effect']); },
    idleTransition6a668: (_s, duration) => {
      calls.push(['transition', duration, s.actionFlag6e8, s.actionFlag73f, s.controlWord]);
    },
  };
  return { s, h, calls, tick: () => tickGRedAirShotEngine(s, h) };
}

function checkAdmissionAndWrappers(): void {
  for (const [variant, control, slot] of [[3, 0x43, 4], [3, 0xc3, 6], [4, 0x43, 6]] as const) {
    const t = fixture('red', variant);
    t.s.controlWord = control;
    const physics = JSON.stringify([t.s.pos, t.s.motion, t.s.poseAccum7c,
      t.s.hSpeed, t.s.yVel, t.s.hDecel, t.s.gravityCoeff]);
    same(t.tick(), { type: 'continue' }, 'startup does not redispatch or clean up');
    same([t.s.phase, t.s.latch745, t.s.timer560, t.s.repeatTimer558],
      [1, 0, variant === 3 ? 20 : 30, 0], 'variant-specific startup timer');
    same([t.s.rootAngle1900, t.s.shift18da, t.s.sideBlend1dfc],
      [-96, -2, variant === 3 ? -5 : -3], 'v3 preserves side roll; v4 halves signed roll');
    same(JSON.stringify([t.s.pos, t.s.motion, t.s.poseAccum7c,
      t.s.hSpeed, t.s.yVel, t.s.hDecel, t.s.gravityCoeff]), physics,
    'engine does not synthesize own physics or carry');
    if (variant === 3) {
      same(t.calls, [['roll', 1, 1, 0], ['start', 1, 2, slot, undefined, undefined]],
        'v3 roll then upper startup only');
      same([t.s.controlWord, t.s.accumulator80c], [control, 99], 'v3 preserves lower state');
    } else {
      same(t.calls, [['aim', 129, 0, 1, 30], ['primary', 1, -2, 1], ['ground', 1, 99],
        ['start', 1, 2, 6, undefined, undefined], ['start', 2, 0, 13, undefined, undefined]],
      'v4 aim/primary/ground/upper/lower order; signed16 yaw');
      same(t.s.accumulator80c, 0, 'v4 resets accumulator only after both streams');
    }
  }
  const t = fixture();
  t.s.phase = 99; t.s.dt = 0;
  t.tick(); t.tick();
  same([t.s.rootAngle1900, t.s.shift18da, t.s.sideBlend1dfc], [-92, -1, -5],
    'root signed f32/trunc and shift happen per call, even dt0/unhandled phase');
  same(t.calls, [], 'unknown phase never causes phase catch-up');
  const changed = fixture();
  changed.h.roll6dee8 = s => { s.controlWord |= 0x80; return 0; };
  changed.tick();
  same(changed.calls[0], ['start', 1, 2, 6, undefined, undefined], 'slot selection uses live post-roll state');
}

function checkAirReadinessAndRedispatch(): void {
  for (const p0 of [-1, 0, 1]) {
    const t = fixture();
    t.s.phase = 1; t.s.timer560 = 20; t.s.dt = .5; t.s.contactP0 = p0;
    t.tick();
    same(t.calls.map(c => c[0]), p0 === 0 ? ['roll', 'tick'] : ['roll'],
      'v3 roll always first; only P0zero permits stream tick');
    same([t.s.phase, t.s.timer560, t.s.dt], [1, 19.5, .5], 'unready consumes restored ordinary dt');
    t.calls.length = 0;
    t.h.roll6dee8 = () => { t.calls.push(['ready']); return 0x8444; };
    t.tick();
    same(t.s.phase, p0 === 0 ? 1 : 2, 'ready still requires nonzero signed contact');
    same(t.s.timer560, p0 === 0 ? 19.5 : 20, 'ready skips countdown; release alone resets timer');
  }
  const event = fixture();
  event.s.phase = 1; event.s.timer560 = .25; event.s.dt = .5;
  event.h.tickStream = s => { event.calls.push(['tick-write']); s.contactP0 = -1; };
  event.tick();
  same(event.calls.map(c => c[0]), ['roll', 'tick-write', 'ammo', 'spawn'],
    'same-call stream P0 mutation gates timeout release');
  same(event.s.phase, 2, 'crossing timer0 releases when P0 changed');

  for (const airborne of [false, true]) {
    const t = fixture(); t.s.phase = 1; t.s.timer560 = 17;
    t.h.roll6dee8 = () => { t.calls.push(['out-of-cone']); return -1; };
    t.h.tickStream = s => { t.calls.push(['tick']); s.controlWord = airborne ? 0x40 : 0; };
    same(t.tick(), { type: 'redispatch', action: 0, subtype: airborne ? 4 : 0, direction: 2 },
      'out-of-cone handoff reads control after stream tick');
    same(t.calls, [['out-of-cone'], ['tick']], 'negative roll does not bypass P0zero stream tick');
    same([t.s.phase, t.s.timer560, t.s.ammo774], [1, 17, 5], 'redispatch returns before timer/debit');
  }
}

function checkRelease(): void {
  for (const [family, interval, row] of [['red', 12, 43], ['neo', 8, 101], ['black', 16, 102]] as const) {
    const t = fixture(family); t.s.phase = 1; t.s.contactP0 = 1; t.s.timer560 = 0;
    t.tick();
    same(t.calls.slice(1), [['ammo', 0, 1, true, 20, interval, 1], ['spawn', row, 3]],
      `${family}: release sets interval/slot/timer before debit, count after spawn`);
    same([t.s.phase, t.s.remaining6ef, t.s.ammo774], [2, 2, 4], 'single release debit');
  }
  const empty = fixture(); empty.s.phase = 1; empty.s.contactP0 = -1; empty.s.timer560 = 0;
  empty.s.ammo774 = 1; empty.s.remaining6ef = -128;
  empty.tick();
  same([empty.s.remaining6ef, empty.s.ammo774], [0, 0], 'signed ammo exhaustion overrides signed-byte count');
  const wrap = fixture(); wrap.s.phase = 1; wrap.s.contactP0 = 1; wrap.s.timer560 = 0;
  wrap.s.remaining6ef = -128; wrap.tick();
  same(wrap.s.remaining6ef, 127, 'remaining byte wraps signed after successful spawn');
  const failed = fixture('black'); failed.s.phase = 1; failed.s.contactP0 = 1; failed.s.timer560 = 0;
  failed.h.ammo6dbe0 = () => false; failed.tick();
  same([failed.s.phase, failed.s.timer560, failed.s.repeatTimer558, failed.s.streamSlot6ee,
    failed.s.remaining6ef], [2, 20, 16, 1, 3], 'failed debit retains source release state without synthetic cleanup');
  check(!failed.calls.some(c => c[0] === 'spawn' || c[0] === 'transition'), 'failed release never spawns/cleans');
}

function checkFallbackPhysicsAndShortCircuits(): void {
  const t = fixture('red', 4); t.s.phase = 1; t.s.timer560 = 5; t.s.dt = .5; t.s.contactP0 = -1;
  t.tick();
  same(t.calls, [['tick', 15, 0, 1], ['primary', 1, -2, .5], ['ground', .5, 99],
    ['aim', 129, 0, .5, 4.5], ['effect']], 'v4 freeze all stream parts; restore dt before physics and timeout-before-aim');
  same([t.s.phase, t.s.timer560, t.s.dt], [1, 4.5, .5], 'unready v4 remains active');
  t.calls.length = 0; t.s.timer560 = .25;
  t.tick();
  same(t.calls, [['tick', 15, 0, 1], ['primary', 1, -2, .5], ['ground', .5, 99],
    ['ammo', 0, 1, true, 20, 12, 1], ['spawn', 43, 3], ['air-return', 0x41, 2], ['effect']],
  'expired v4 short-circuits aim, releases, clears control2, returns air, then dust');

  const ready = fixture('red', 4); ready.s.phase = 1; ready.s.timer560 = 8; ready.s.contactP0 = 0;
  ready.h.aim6d0dc = () => true;
  ready.tick();
  same([ready.s.phase, ready.s.timer560], [1, 7], 'ready v4 still subtracts timer and cannot fire at P0zero');
  ready.s.timer560 = -1; ready.calls.length = 0;
  ready.h.aim6d0dc = () => { throw new Error('expired timer must short-circuit aim'); };
  ready.tick();
  same(ready.s.phase, 1, 'even expired v4 needs nonzero P0');
  for (const speed of [-4, 3, 3.01]) {
    const dust = fixture('red', 4); dust.s.phase = 1;
    dust.h.ground677b0 = s => { s.hSpeed = speed; };
    dust.tick();
    same(dust.calls.some(c => c[0] === 'effect'), speed > 3, 'dust tests live signed hSpeed, not magnitude');
  }
}

function checkRepeatAndLiteralComparison(): void {
  for (const [p0, group, oldSlot, control, expectedSlot, defaults] of [
    [-1, 2, 5, 0x40, 5, false], [-1, 0, 5, 0x40, 5, true],
    [-1, 0, 7, 0xc0, 7, true], [1, 0, 5, 0x40, 5, false],
    [-1, 0, 4, 0x40, 5, false],
  ] as const) {
    const t = fixture('red', 4); t.s.phase = 2; t.s.contactP0 = p0;
    t.s.animationGroup1afc = group; t.s.animationSlot1afd = oldSlot; t.s.controlWord = control;
    t.s.latch745 = 0; t.s.input5d4 = 0x21; t.s.input5d8 = 0xf0; t.s.completed1cee = 1;
    same(t.tick(), { type: 'continue' }, 'repeat wins over exit predicates');
    same(t.calls, [['tick', 1, 1, 1], ['ammo', 0, 1, false, 9, 0, 0], ['capture', 1, 2],
      ['start', 1, 2, expectedSlot, defaults ? undefined : 4, defaults ? undefined : 1]],
    'repeat tick/check/capture/start exact order and literal animation-key comparison');
    same([t.s.variant, t.s.phase, t.s.latch745, t.s.ammo774], [3, 1, 0, 5],
      'v4 repeat selects v3, decrements phase and clears latch without debit');
  }
  const countdown = fixture(); countdown.s.phase = 2; countdown.s.repeatTimer558 = .5;
  countdown.s.dt = .5; countdown.s.input5d4 = 0x20; countdown.s.latch745 = 0;
  countdown.tick();
  same(countdown.calls, [['tick', 1, .5, 1], ['roll', 1, .5, 0]],
    'fresh B latches before tick; decrement-to-zero then roll, never same-call repeat');
  countdown.calls.length = 0; countdown.s.input5d4 = 0; countdown.tick();
  same(countdown.calls.map(c => c[0]), ['tick', 'ammo', 'capture', 'start'], 'latched B survives to next check');

  const landing = fixture(); landing.s.phase = 2; landing.s.controlWord = 0;
  same(landing.tick(), { type: 'redispatch', action: 0, subtype: 0, direction: 2 }, 'ground-neutral repeat redispatches');
  same(landing.calls.map(c => c[0]), ['tick', 'ammo', 'capture'], 'landing returns before stream/roll/cleanup');
  same([landing.s.phase, landing.s.latch745], [1, 0], 'landing handoff sees source phase decrement');
  const cue = fixture(); cue.s.phase = 2; cue.s.controlWord = 0; cue.s.movementCue5e4 = 4;
  cue.tick();
  same(cue.calls.at(-1), ['start', 1, 2, 5, 4, 1], 'movementcue4 retains source v3 despite cleared air bit');
}

function checkCleanupAndScope(): void {
  for (const reason of ['ammo', 'direction', 'completion'] as const) {
    const t = fixture(); t.s.phase = 2; t.s.controlWord = 0xc3;
    if (reason === 'ammo') t.h.ammo6dbe0 = () => false;
    else {
      t.s.latch745 = 0; t.s.repeatTimer558 = 2;
      if (reason === 'direction') t.s.input5d8 = 0x20;
      else t.s.completed1cee = 1;
    }
    same(t.tick(), { type: 'cleanup' }, `${reason}: explicit cleanup outcome`);
    same(t.calls.at(-1), ['transition', 20, 0, 0, 0xc0], 'clear source fields before transition, no ground-idle helper');
    same(t.s.timer560, 9, 'cleanup does not synthesize20 cooldown');
  }
  const a = fixture(); a.s.phase = 2; a.s.latch745 = 0; a.s.input5d4 = 1;
  same(a.tick(), { type: 'continue' }, 'fresh A does not exit airborne shared recovery');
  same(a.calls, [['tick', 1, 1, 0]], 'expired repeat without latch neither rolls nor fires');
  for (const [bits, variant, lower, slot] of [[0x10, 1, 0, 3], [0x20, 2, 0, 10], [0x20, 2, 15, 1]] as const) {
    const t = fixture(); t.s.phase = 2; t.s.controlWord = bits; t.s.lowerState5db = lower;
    same(t.tick(), { type: 'unsupported', variant, slot }, 'source locomotion branch explicitly outside port');
    same(t.calls.map(c => c[0]), ['tick', 'ammo', 'capture'], 'no guessed locomotion stream');
    same(t.s.variant, variant, 'preserve source variant selection at boundary');
  }
}

export function runGredAirShotEngineSelfTest(): void {
  checkAdmissionAndWrappers(); checkAirReadinessAndRedispatch(); checkRelease();
  checkFallbackPhysicsAndShortCircuits(); checkRepeatAndLiteralComparison(); checkCleanupAndScope();
}
