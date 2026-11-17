import {createSourceActorInputPrefixRuntime, isSourceActorInputPrefixRuntime, isSourceActorInputPrefixClaimedBorg,
  type SourceActorInputPrefixBinding, type SourceActorInputBorgOwner} from './actor-input-prefix.js';
import {createRomActor} from './actor.js';
import {stepArrowMashInput} from '../arrowProjectile.js';
import type {BorgRuntime, PlayerInput} from '../types.js';
function check(ok: boolean, why: string): void {if (!ok) throw Error(`[actor-input-prefix-test] ${why}`);}
function equal(a: unknown, b: unknown, why: string): void {check(Object.is(a, b), `${why}: got ${String(a)}, expected ${String(b)}`);}
function rejects(run: () => unknown, fragment: string): void {
  let error = ''; try {run();} catch (e) {error = String(e);}
  check(error.includes(fragment), `expected ${fragment}, got ${error || 'success'}`);
}
function fixture(defer = false) {
  const id = Symbol('input actor'), actual = Object.assign(createRomActor(), {statusWord5bc: 0});
  actual.inputEdge5d4 = 0xffffffff; actual.inputHeld5d8 = 0xabcd;
  const borg: SourceActorInputBorgOwner = {downGaugeBase: 100, downGauge: 7,
    paramTier: {tier: 16, deltaAccum: 0, timerFrames: 0}, sourceArrowMash749: 99};
  const initial: Partial<SourceActorInputPrefixBinding> = {ushort5b8: 0xf00a, stickX5ca: 0, stickY5cb: 0,
    byte5fc: 3, byte5fd: 0, byte5fe: 0, byte5ff: 0};
  const hooks: {world?: () => unknown; actor?: () => unknown; borg?: () => unknown} = {};
  const world = {getActualActor(key: symbol) {check(this === world && key === id, 'world receiver/id');
    return (hooks.world ? hooks.world() : actual) as typeof actual;}};
  const gauges = {getActualActor(key: symbol) {check(this === gauges && key === id, 'gauge actor receiver/id');
    return (hooks.actor ? hooks.actor() : actual) as typeof actual;},
    getActualBorg(key: symbol) {check(this === gauges && key === id, 'gauge Borg receiver/id');
      return (hooks.borg ? hooks.borg() : borg) as typeof borg;}};
  const sources = {world, gauges}, runtime = createSourceActorInputPrefixRuntime(sources);
  const bind = () => runtime.bindActor(id, initial); if (!defer) bind();
  return {id, actual, borg, initial, hooks, world, gauges, sources, runtime, bind,
    binding: () => runtime.getActorBinding(id), run: () => runtime.updateActor(id)};
}
export function runActorInputPrefixSelfTests(): void {
  {
    const x = fixture(); const binding = x.binding();
    check(isSourceActorInputPrefixRuntime(x.runtime) && !isSourceActorInputPrefixRuntime({...x.runtime}), 'genuine brand');
    check(x.runtime.getActualActor(x.id) === x.actual && x.runtime.getActualBorg(x.id) === x.borg &&
      x.runtime.getActorBinding(x.id) === binding && binding !== x.initial, 'single actual owners and sealed missing cells');
    check(Object.isSealed(binding) && isSourceActorInputPrefixClaimedBorg(x.borg), 'permanent Borg claim');
    const before = JSON.stringify(binding); rejects(x.run, '800685f8');
    equal(x.actual.inputEdge5d4, 0, 'edge cleared only after genuine input return');
    equal(x.borg.sourceArrowMash749, 0, 'masked popcount zero'); equal(JSON.stringify(binding), before, 'zero timers untouched');
    equal(x.actual.inputHeld5d8, 0xabcd, 'held untouched by no input');
    const borgBefore = JSON.stringify(x.borg);
    rejects(() => stepArrowMashInput(x.borg as BorgRuntime, {} as PlayerInput), 'legacy mash producer excluded');
    equal(JSON.stringify(x.borg), borgBefore, 'legacy producer blocked before reads/writes');
    const again = createSourceActorInputPrefixRuntime(x.sources);
    rejects(() => again.bindActor(Symbol(), {}), 'receiver/id');
    rejects(() => again.bindActor(x.id, {}), 'already claimed');
  }
  // Every signed timer byte: raw80 ->7f does NOT clear, raw81 ->80 does.
  for (const key of ['byte5fd', 'byte5ff', 'byte5fe'] as const) for (let value = 0; value < 256; value++) {
    const x = fixture(), b = x.binding(); b[key] = value; rejects(x.run, '80068b8c');
    const next = value === 0 ? 0 : (value - 1) & 255;
    equal(b[key], next, `${key}/${value} byte decrement`);
    const clear = value !== 0 && (key === 'byte5fe' ? next === 0 : (next < 1 || next > 127));
    const mask = key === 'byte5fd' ? 0xff00 : key === 'byte5ff' ? 0xf0ff : 0x0fff;
    equal(x.actual.inputHeld5d8, clear ? 0xabcd & mask : 0xabcd, `${key}/${value} exact clear predicate`);
  }
  // Exhaust the eight selected press bits, with all unselected bits already set.
  for (let combo = 0; combo < 256; combo++) {
    const x = fixture(); const mask = ((combo & 15) << 8) | ((combo >>> 4) << 16);
    x.actual.statusWord5bc = (mask | (~0xf0f00)) >>> 0; rejects(x.run, '80068b8c');
    equal(x.borg.sourceArrowMash749, combo.toString(2).replaceAll('0', '').length, 'all masked popcounts');
  }
  for (const [flags, radius] of [[0, 20], [1, 52]] as const) for (const sign of [-1, 1]) {
    for (const delta of [-1, 0, 1]) {
      const x = fixture(); x.binding().byte5fc = flags; x.binding().stickX5ca = sign * (radius + delta);
      rejects(x.run, delta < 0 ? '80068b8c' : '8008b778');
      equal(x.actual.inputEdge5d4, delta < 0 ? 0 : 0xffffffff, 'strict radius boundary before edge clear');
      equal(x.borg.sourceArrowMash749, delta < 0 ? 0 : 99, 'outside radius no fabricated direction result');
    }
  }
  {
    const x = fixture(true); delete x.initial.stickX5ca; delete x.initial.stickY5cb; delete x.initial.ushort5b8;
    x.bind(); rejects(x.run, '80068b8c'); // Both set bits skip stick loads, no release skips5b8.
  }
  {
    const x = fixture(); const b = x.binding(); x.actual.statusWord5b4 = 0x60000;
    x.actual.statusWord5bc = 0x80050a01; b.byte5fd = 1; b.byte5fe = 1; b.byte5ff = 9;
    const fb = x.actual.fbState, ub = x.actual.ubState;
    rejects(x.run, '80068b8c');
    equal(b.byte5fc, 11, 'onset sets bit8 without replacing latch');
    equal(b.byte5ff, 19, 'new20 timer decremented in same call'); equal(b.byte5fd, 0, 'first timer clears');
    equal(b.byte5fe, 0, 'release timer last'); equal(x.actual.inputHeld5d8, 0x200, 'reload-after-mask expression and timer order');
    equal(x.borg.sourceArrowMash749, 4, 'real raw word popcount, no browser edge generation');
    equal(x.actual.fbState, fb, '5d8 does not own5da'); equal(x.actual.ubState, ub, '5d8 does not own5db');
  }
  {
    const x = fixture(); const b = x.binding(); b.byte5fc = 0xff; b.ushort5b8 = 0xabc5;
    rejects(x.run, '80068b8c'); equal(b.byte5fc, 0, 'release clears whole latch');
    equal(x.actual.inputHeld5d8, 0x5bcd, 'release uses low nibble of explicitly decoded high halfword');
    equal(b.byte5fe, 15, 'new16 release timer decremented immediately');
  }
  // Late failures leave all source prefix effects, and never clear input edge early.
  for (const fault of ['ushort5b8', 'byte5fe', 'byte5fd', 'byte5ff', 'statusWord5bc', 'sourceArrowMash749', 'inputEdge5d4'] as const) {
    const x = fixture(true); x.initial.byte5fc = 11; x.initial.byte5fd = 2; x.initial.byte5ff = 2;
    if (fault === 'ushort5b8') delete x.initial.ushort5b8;
    x.bind(); const b = x.binding();
    if (fault === 'byte5fe' || fault === 'byte5fd' || fault === 'byte5ff') Object.defineProperty(b, fault, {writable: false});
    if (fault === 'statusWord5bc') Object.defineProperty(x.actual, fault, {value: undefined});
    if (fault === 'sourceArrowMash749') Object.defineProperty(x.borg, fault, {writable: false});
    if (fault === 'inputEdge5d4') Object.defineProperty(x.actual, fault, {writable: false});
    rejects(x.run, fault === 'ushort5b8' || fault === 'statusWord5bc' ? fault : 'non-writable');
    equal(b.byte5fc, 0, `${fault} retains full latch clear`);
    equal(x.actual.inputHeld5d8, fault === 'ushort5b8' ? 0xbcd : 0xabcd, `${fault} retains reached halfword stores`);
    equal(x.actual.inputEdge5d4, 0xffffffff, `${fault} no early edge clear`);
    equal(x.borg.sourceArrowMash749, fault === 'inputEdge5d4' ? 0 : 99, `${fault} late popcount store order`);
  }
  {
    const x = fixture(); x.binding().byte5fc = 11; Object.defineProperty(x.actual, 'inputHeld5d8', {writable: false});
    rejects(x.run, 'non-writable'); equal(x.binding().byte5fc, 0, 'latch write before readonly held');
    equal(x.binding().byte5fe, 0, 'no release timer before held store');
  }
  for (const key of ['inputFlags5d4', 'inputFlags5d8', 'inputEdges5bc', 'sourceArrowMash749', 'byte749', 'ushort5b8', 'stickX5ca', 'byte5fc']) {
    const x = fixture(true); Object.defineProperty(x.actual, key, {value: undefined}); rejects(x.bind, 'competing');
    check(!isSourceActorInputPrefixClaimedBorg(x.borg), 'failed bind does not claim Borg');
    const y = fixture(); Object.defineProperty(y.actual, key, {value: undefined}); rejects(y.run, 'competing');
    equal(y.actual.inputEdge5d4, 0xffffffff, 'late alias fails before writes');
  }
  for (const hook of ['world', 'actor', 'borg'] as const) {
    const x = fixture(); x.hooks[hook] = () => ({}); rejects(x.run, 'owner changed'); equal(x.actual.inputEdge5d4, 0xffffffff, 'identity failure no writes');
  }
  {
    const x = fixture(); x.hooks.world = () => {try {x.run();} catch { /* caught reentry must poison outer */ } return x.actual;};
    rejects(x.run, 'caught same-runtime reentry'); equal(x.borg.sourceArrowMash749, 99, 'no swallowed reentry success');
  }
  {
    const x = fixture(true); x.initial.byte5fc = 0; delete x.initial.stickX5ca; delete x.initial.stickY5cb; x.bind();
    rejects(x.run, 'stickX5ca'); // Source loads X before Y.
  }
  console.log('[actor-input-prefix] PASS: bounded real68980 direction-zero domain, signed timer bytes, all256 masked popcounts, same Borg749, halfword5d8, retained late failures, exclusive owners and legacy-producer exclusion; real5d4 clear then68b8c refusal, never full tick');
}
