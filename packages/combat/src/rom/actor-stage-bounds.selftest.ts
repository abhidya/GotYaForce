import {createSourceActorStageBoundsRuntime, isSourceActorStageBoundsRuntime,
  type SourceActorStageBoundsBinding} from './actor-stage-bounds.js';
import {createRomActor} from './actor.js';
import type {SourceActorWorldMatrixRuntime} from './actor-world-matrix.js';
import type {SourceActorStatusTimersRuntime} from './actor-status-timers.js';
import type {SourceActorTerrainGlobals} from './actor-terrain-query.js';
import {createSourceActorTickPrefixRuntime} from './actor-tick-prefix.js';
import {createSourceActorGaugeScaleRuntime} from './actor-gauge-scale.js';

function check(ok: boolean, why: string): void {if (!ok) throw Error(`[actor-stage-bounds-test] ${why}`);}
function equal(actual: unknown, expected: unknown, why: string): void {
  check(Object.is(actual, expected), `${why}: got ${String(actual)}, expected ${String(expected)}`);
}
function rejects(run: () => unknown, fragment: string): void {
  let error = ''; try {run();} catch (e) {error = String(e);}
  check(error.includes(fragment), `expected ${fragment}, got ${error || 'success'}`);
}
/** Read-only actual-owner seams isolate this helper. Full source world/status/
 * terrain composition is covered separately in attached-setup-animation. */
function fixture(defer = false) {
  const id = Symbol('stage-boundary actor'), actual = Object.assign(createRomActor(), {noClamp6cb: 0, collisionScale: 1});
  const worldState = {mode4a1: 0, scale58: {x: 1, y: 1, z: 1}};
  const statusState = {short272: -32768, field7d8: 7};
  const globals = {maxX38: 10, minX3c: -10, maxZ40: 20, minZ44: -20};
  const borg = {downGaugeBase: 100, downGauge: 7, paramTier: {tier: 16, deltaAccum: 0, timerFrames: 0}};
  const hooks: {worldActor?: () => unknown; world?: () => unknown; statusActor?: () => unknown;
    status?: () => unknown; terrain?: () => unknown} = {};
  const world = {
    getActualActor(key: symbol) {check(this === world && key === id, 'world actor receiver/id');
      return (hooks.worldActor ? hooks.worldActor() : actual) as typeof actual;},
    getActorBinding(key: symbol) {check(this === world && key === id, 'world binding receiver/id');
      return (hooks.world ? hooks.world() : worldState) as ReturnType<SourceActorWorldMatrixRuntime['getActorBinding']>;},
  };
  const status = {
    getActualActor(key: symbol) {check(this === status && key === id, 'status actor receiver/id');
      return (hooks.statusActor ? hooks.statusActor() : actual) as typeof actual;},
    getActorBinding(key: symbol) {check(this === status && key === id, 'status binding receiver/id');
      return (hooks.status ? hooks.status() : statusState) as ReturnType<SourceActorStatusTimersRuntime['getActorBinding']>;},
    getActualBorg(key: symbol) {check(this === status && key === id, 'status Borg receiver/id'); return borg as unknown as ReturnType<SourceActorStatusTimersRuntime['getActualBorg']>;},
  };
  const terrain = {getTerrainGlobals() {check(this === terrain, 'terrain receiver');
    return (hooks.terrain ? hooks.terrain() : globals) as SourceActorTerrainGlobals;}};
  const sources = {world, status, terrain}, runtime = createSourceActorStageBoundsRuntime(sources);
  const initial: Partial<SourceActorStageBoundsBinding> = {lifecycle18: 1, short6cc: 7};
  const bind = () => runtime.bindActor(id, initial);
  if (!defer) bind();
  return {id, actual, worldState, statusState, globals, borg, hooks, world, status, terrain, sources, runtime, initial, bind,
    run: () => runtime.updateActor(id), binding: () => runtime.getActorBinding(id)};
}

export function runActorStageBoundsSelfTests(): void {
  {
    const x = fixture();
    equal(x.runtime.getActualActor(x.id), x.actual, 'same actual actor');
    equal(x.runtime.getWorldBinding(x.id), x.worldState, 'same4a1 owner');
    equal(x.runtime.getStatusBinding(x.id), x.statusState, 'same272 owner');
    equal(x.runtime.getTerrainGlobals(), x.globals, 'same shared stage owner');
    equal(Object.keys(x.binding()).join(','), 'lifecycle18,short6cc', 'only absent fields get storage');
    check(isSourceActorStageBoundsRuntime(x.runtime) && !isSourceActorStageBoundsRuntime({...x.runtime}), 'genuine runtime brand cannot be copied');
    const before = JSON.stringify(x.actual), status = JSON.stringify(x.statusState), world = JSON.stringify(x.worldState);
    x.run(); equal(x.binding().short6cc, 0, 'active inbounds resets counter');
    equal(JSON.stringify(x.actual), before, 'inbounds does not mutate actor'); equal(JSON.stringify(x.statusState), status, 'status unchanged');
    equal(JSON.stringify(x.worldState), world, 'world unchanged'); equal(x.initial.short6cc, 7, 'input not a second mutable owner');
    for (const [px, pz] of [[-10, -20], [-10, 20], [10, -20], [10, 20], [-0, 0], [0, -0]]) {
      x.actual.pos.x = px!; x.actual.pos.z = pz!; x.binding().short6cc = 11; x.run();
      equal(x.binding().short6cc, 0, 'all boundaries inclusive including signed zero');
    }
    x.globals.maxX38 = -1; x.actual.pos.x = 0; x.run();
    equal(x.binding().short6cc, 1, 'bound owner mutations are observed, not cached');
  }
  {
    for (const gate of ['mode', 'lifecycle', 'exit'] as const) {
      const x = fixture(true);
      if (gate === 'mode') {x.worldState.mode4a1 = 255; delete x.initial.lifecycle18;}
      x.bind();
      if (gate === 'lifecycle') {x.binding().lifecycle18 = 255; delete (x.actual as {noClamp6cb?: number}).noClamp6cb;}
      if (gate === 'exit') x.actual.noClamp6cb = 128;
      x.hooks.terrain = () => {throw Error('unreached stage getter');}; x.actual.pos.x = NaN;
      x.run(); equal(x.binding().short6cc, 7, `early${gate} preserves counter and bypasses later owners`);
    }
    const x = fixture(true); delete x.initial.lifecycle18; delete x.initial.short6cc; x.bind();
    x.worldState.mode4a1 = 1; x.run(); equal(Object.keys(x.binding()).length, 0, 'missing unneeded fields stay absent');
    x.worldState.mode4a1 = 0; rejects(x.run, 'lifecycle18: own data');
  }
  {
    // Different missing later bounds prove lazy comparison order, without
    // executing getters or admitting Proxy side effects as source evidence.
    const x = fixture(); x.actual.pos.x = -11; x.globals.maxX38 = NaN; x.actual.pos.z = NaN; x.run();
    equal(x.binding().short6cc, 8, 'lowerX short circuit');
    const y = fixture(); y.actual.pos.x = 11; y.globals.minZ44 = NaN; y.actual.pos.z = NaN; y.run();
    equal(y.binding().short6cc, 8, 'upperX short circuit');
    const z = fixture(); z.actual.pos.z = -21; z.globals.maxZ40 = NaN; z.run();
    equal(z.binding().short6cc, 8, 'lowerZ short circuit');
    const w = fixture(); w.actual.pos.z = 21; w.run(); equal(w.binding().short6cc, 8, 'upperZ branch');
    const inverted = fixture(); inverted.globals.minX3c = 2; inverted.globals.maxX38 = -2; inverted.run();
    equal(inverted.binding().short6cc, 8, 'no invented min/max validity gate');
    for (const field of ['minX3c', 'maxX38', 'minZ44', 'maxZ40'] as const) {
      const a = fixture(); a.globals[field] = NaN; rejects(a.run, `${field}: finite`);
      equal(a.binding().short6cc, 7, 'reached invalid bound retains prior counter');
    }
    for (const value of [NaN, Infinity, -Infinity, 1.1]) {
      const a = fixture(); a.actual.pos.x = value; rejects(a.run, 'x: finite');
      equal(a.binding().short6cc, 7, 'nonfinite and nonf32 positions refused');
    }
    const a = fixture(); let touched = false; Object.defineProperty(a.globals, 'minX3c', {get() {touched = true; return -10;}});
    rejects(a.run, 'minX3c: own data'); check(!touched, 'bound accessor never invoked');
  }
  {
    const x = fixture(); x.actual.pos.x = 11; x.binding().short6cc = 28;
    x.run(); equal(x.binding().short6cc, 29, '29 does not transition'); equal(x.actual.noClamp6cb, 0, '29 keeps byte');
    rejects(x.run, '8006a750'); equal(x.binding().short6cc, 0, '30 transitions and resets');
    equal(x.actual.noClamp6cb, 1, 'ordinary transition byte1'); equal(x.statusState.short272, -32768, 'ordinary branch skips272');
    x.run(); equal(x.binding().short6cc, 0, 'next explicit call gates on actual6cb without redoing cues');
    for (const flags of [0x02000000, 0x03000000, 0x06000000, 0x87000000]) {
      const a = fixture(); a.actual.pos.z = 21; a.actual.controlWord = flags; a.binding().short6cc = -100;
      rejects(a.run, '8006a750'); equal(a.binding().short6cc, 0, 'forced transition below threshold');
      equal(a.actual.noClamp6cb, (flags & 0x05000000) ? 2 : 1, 'both transition masks distinct');
      equal(a.statusState.short272, (flags & 0x05000000) ? -32701 : -32768, 'signed272 OR43 preserves high bit');
    }
    const wrap = fixture(); wrap.actual.pos.x = 11; wrap.binding().short6cc = 32767; wrap.run();
    equal(wrap.binding().short6cc, -32768, 'signed16 wrap precedes threshold');
    // Exhaustive signed16 domain uses real helper and reset actual owners on
    // each explicit call. Reference is a width-independent modular formula.
    const e = fixture(); e.actual.pos.x = 11;
    for (let value = -32768; value <= 32767; value++) {
      e.binding().short6cc = value; e.actual.noClamp6cb = 0;
      const next = value === 32767 ? -32768 : value + 1;
      if (next >= 30) rejects(e.run, '8006a750'); else e.run();
      equal(e.binding().short6cc, next >= 30 ? 0 : next, 'exhaustive signed counter');
      equal(e.actual.noClamp6cb, next >= 30 ? 1 : 0, 'exhaustive threshold byte');
    }
  }
  {
    const a = fixture(); a.binding().short6cc = NaN; a.actual.controlWord = NaN; a.run();
    equal(a.binding().short6cc, 0, 'inbounds writes counter without loading old value or flags');
    const b = fixture(); b.actual.pos.x = 11; b.actual.controlWord = NaN; b.binding().short6cc = 28;
    rejects(b.run, 'controlWord: integer'); equal(b.binding().short6cc, 29, 'subthreshold flag load fails after increment');
    const c = fixture(); c.actual.pos.x = 11; c.actual.controlWord = NaN; c.binding().short6cc = 29;
    rejects(c.run, 'controlWord: integer'); equal(c.binding().short6cc, 0, 'threshold skips first flags read, reset precedes second');
    const d = fixture(); Object.defineProperty(d.binding(), 'short6cc', {writable: false});
    rejects(d.run, 'short6cc: non-writable'); equal(d.binding().short6cc, 7, 'readonly reset destination retains value');
    const f = fixture(); f.actual.pos.x = 11; f.binding().short6cc = 29;
    Object.defineProperty(f.actual, 'noClamp6cb', {writable: false}); rejects(f.run, 'noClamp6cb: non-writable');
    equal(f.binding().short6cc, 0, 'readonly6cb retains reset'); equal(f.actual.noClamp6cb, 0, 'readonly6cb untouched');
    const g = fixture(); g.actual.pos.x = 11; g.binding().short6cc = 29; g.actual.controlWord = 0x01000000;
    Object.defineProperty(g.statusState, 'short272', {writable: false}); rejects(g.run, 'short272: non-writable');
    equal(g.binding().short6cc, 0, 'readonly272 retains reset'); equal(g.actual.noClamp6cb, 2, 'readonly272 retains6cb');
    equal(g.statusState.short272, -32768, 'readonly272 retains old value');
    const h = fixture(); h.actual.pos.x = 11; h.binding().short6cc = 29; h.statusState.short272 = NaN;
    rejects(h.run, '8006a750'); equal(h.actual.noClamp6cb, 1, 'ordinary transition never reads272');
    const i = fixture(); i.actual.pos.x = 11; i.binding().short6cc = -32769;
    rejects(i.run, 'short6cc: integer'); equal(i.binding().short6cc, -32769, 'invalid old signed counter not wrapped into validity');
  }
  {
    for (const owner of ['worldActor', 'statusActor', 'world', 'status', 'terrain'] as const) {
      const x = fixture(); x.hooks[owner] = () => ({}); rejects(x.run, 'owner changed'); equal(x.binding().short6cc, 7, 'replacement owner fails without writes');
    }
    const p = fixture(); p.actual.pos = {...p.actual.pos}; rejects(p.run, 'position: owner changed');
    const x = fixture(true); x.hooks.statusActor = () => createRomActor(); rejects(x.bind, 'status actor: owner changed');
    const y = fixture(); rejects(() => y.runtime.bindActor(Symbol('second'), y.initial), 'receiver/id');
    const again = createSourceActorStageBoundsRuntime(y.sources); rejects(() => again.bindActor(y.id, y.initial), 'already claimed');
    for (const name of ['lifecycle18', 'short6cc', 'field6cc']) {
      const z = fixture(true); Object.defineProperty(z.actual, name, {value: undefined}); rejects(z.bind, 'competing stage-boundary storage');
      const w = fixture(); Object.defineProperty(w.actual, name, {value: undefined}); rejects(w.run, 'competing stage-boundary storage');
    }
    const r = fixture(); let nested = false;
    r.hooks.worldActor = () => {if (!nested) {nested = true; try {r.run();} catch { /* caught reentry still poisons */ }} return r.actual;};
    rejects(r.run, 'caught same-runtime reentry'); equal(r.binding().short6cc, 7, 'caught nested call does not permit later writes');
    delete r.hooks.worldActor; r.run(); equal(r.binding().short6cc, 0, 'later independent call can run');
    const missing = fixture(true); Object.defineProperty(missing.initial, 'lifecycle18', {get() {throw Error('accessor invoked');}});
    rejects(missing.bind, 'lifecycle18: own data');
  }
  {
    const x = fixture();
    const gauges = createSourceActorGaugeScaleRuntime({world: x.world, status: x.status});
    gauges.bindActor(x.id, x.borg, {short7d6: 1, short7dc: 1, targetScaleB8: 1, byte7c9: 0, fieldC4: 1});
    const sources = {world: x.world, gauges, stageBounds: x.runtime};
    rejects(() => createSourceActorTickPrefixRuntime({...sources, stageBounds: {...x.runtime}}), 'genuine source runtime');
    const prefix = createSourceActorTickPrefixRuntime(sources); prefix.bindActor(x.id, x.borg, {byte598: 4});
    const run = (epoch: number) => prefix.ingestRawDistancesAndRun(x.id, epoch,
      {boundary: 'externally-decoded-pre59068-raw', targetDistance760: 30, horizontalDistance764: 12});
    x.actual.controlWord = 0x100000; rejects(() => run(0), '800685c0');
    equal(x.binding().short6cc, 0, 'prefix invokes real stage reset'); equal(x.actual.controlWord, 0, 'support still precedes stage');
    x.actual.pos.x = 11; x.binding().short6cc = 29; rejects(() => run(1), '8006a750');
    equal(x.actual.noClamp6cb, 1, 'real prefix reaches transition'); rejects(() => run(1), 'epoch already consumed');
    equal(x.binding().short6cc, 0, 'failed epoch does not repeat stage');
  }
  console.log('[actor-stage-bounds-test] actual stage owners, inclusive bounds,65536 signed counters and retained refusal prefixes passed');
}
