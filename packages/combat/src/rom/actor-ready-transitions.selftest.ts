import {createSourceActorReadyTransitionsRuntime, isSourceActorReadyTransitionsRuntime,
  type SourceActorReadyTransitionsBinding} from './actor-ready-transitions.js';
import {createSourceActorControlLifecycleRuntime} from './actor-control-lifecycle.js';
import {createSourceActorStageBoundsRuntime} from './actor-stage-bounds.js';
import {createRomActor} from './actor.js';
import type {SourceActorWorldMatrixBinding} from './actor-world-matrix.js';
import type {SourceActorStatusBorgOwner} from './actor-status-timers.js';
import type {SourceActorTerrainGlobals} from './actor-terrain-query.js';

function check(ok: boolean, why: string): void {if (!ok) throw Error(`[actor-ready-transitions-test] ${why}`);}
function equal(actual: unknown, expected: unknown, why: string): void {
  check(Object.is(actual, expected), `${why}: got ${String(actual)}, expected ${String(expected)}`);
}
function rejects(run: () => unknown, fragment: string): void {
  let error = ''; try {run();} catch (e) {error = String(e);}
  check(error.includes(fragment), `expected ${fragment}, got ${error || 'success'}`);
}
/** Genuine stage/control runtimes over receiver-checked read-only owner seams.
 * These seams never replace source callees or their effects. */
function fixture(defer = false, missingOwner?: 'stage' | 'control') {
  const id = Symbol('ready transition'), actual = createRomActor();
  const worldState = {mode4a0: 0, mode4a1: 0, flags48a: 2};
  const statusState = {short272: -32768, byte6fc: 0};
  const borg = {hp: -17, maxHp: 0x9001, colorVariant: 201};
  const hooks: {worldActor?: () => unknown; world?: () => unknown; statusActor?: () => unknown;
    status?: () => unknown; statusWorld?: () => unknown; borg?: () => unknown} = {};
  const world = {
    getActualActor(key: symbol) {check(this === world && key === id, 'world actor receiver/id');
      return (hooks.worldActor ? hooks.worldActor() : actual) as typeof actual;},
    getActorBinding(key: symbol) {check(this === world && key === id, 'world binding receiver/id');
      return (hooks.world ? hooks.world() : worldState) as SourceActorWorldMatrixBinding;},
  };
  const status = {
    getActualActor(key: symbol) {check(this === status && key === id, 'status actor receiver/id');
      return (hooks.statusActor ? hooks.statusActor() : actual) as typeof actual;},
    getActorBinding(key: symbol) {check(this === status && key === id, 'status binding receiver/id');
      return (hooks.status ? hooks.status() : statusState) as typeof statusState;},
    getWorldBinding(key: symbol) {check(this === status && key === id, 'status world receiver/id');
      return (hooks.statusWorld ? hooks.statusWorld() : worldState) as object;},
    getActualBorg(key: symbol) {check(this === status && key === id, 'status Borg receiver/id');
      return (hooks.borg ? hooks.borg() : borg) as SourceActorStatusBorgOwner;},
  };
  const globals = {maxX38: 10, minX3c: -10, maxZ40: 10, minZ44: -10} as SourceActorTerrainGlobals;
  const terrain = {getTerrainGlobals: () => globals};
  const stageBounds = createSourceActorStageBoundsRuntime({world, status, terrain});
  stageBounds.bindActor(id, missingOwner === 'stage' ? {} : {lifecycle18: 1, short6cc: 7});
  const control = createSourceActorControlLifecycleRuntime({world, status});
  control.bindActor(id, missingOwner === 'control' ? {short49a: 1, short49c: 0} : {byte490: 2, short49a: 1, short49c: 0});
  const sources = {world, status, stageBounds, control};
  const runtime = createSourceActorReadyTransitionsRuntime(sources);
  const initial: Partial<SourceActorReadyTransitionsBinding> = {byte19: 9, byte1a: 9, byte1b: 9, byte489: 8,
    short48c: 71, byte48e: 7, byte48f: 8, short494: 31, short496: 32, short49e: -23, short3ea: -12, byte3ef: 239};
  const bind = () => runtime.bindActor(id, initial);
  if (!defer) bind();
  return {id, actual, worldState, statusState, borg, hooks, world, status, stageBounds, control, sources, runtime, initial, bind,
    stage: stageBounds.getActorBinding(id), controlState: control.getActorBinding(id),
    binding: () => runtime.getActorBinding(id), run490: () => runtime.transition490(id), run48a: () => runtime.transition48a(id),
    attach: () => control.bindReadyRuntime(runtime), runControl: () => control.updateActor(id)};
}
type Fixture = ReturnType<typeof fixture>;
function stores(x: Fixture, branch490: boolean): Array<{owner: object; key: string; after: number}> {
  const common: Array<{owner: object; key: string; after: number}> = [
    {owner: x.stage, key: 'lifecycle18', after: 2}, {owner: x.binding(), key: 'byte19', after: 2},
    {owner: x.binding(), key: 'byte1a', after: 0}, {owner: x.binding(), key: 'byte1b', after: 0},
    {owner: x.statusState, key: 'short272', after: -32768 + 0x443},
  ];
  if (!branch490) common.push({owner: x.worldState, key: 'flags48a', after: 4});
  common.push({owner: x.controlState, key: 'byte490', after: 4},
    {owner: x.binding(), key: 'short48c', after: branch490 ? -12 : -23},
    {owner: x.binding(), key: 'byte48e', after: 201});
  if (branch490) common.push({owner: x.binding(), key: 'byte48f', after: 239});
  common.push({owner: x.binding(), key: 'short494', after: -17},
    {owner: x.binding(), key: 'short496', after: 0x9001 - 65536});
  if (branch490) common.push({owner: x.worldState, key: 'mode4a1', after: 0});
  return common;
}
export function runActorReadyTransitionsSelfTests(): void {
  {
    const x = fixture();
    equal(x.runtime.getActualActor(x.id), x.actual, 'same actual actor');
    equal(x.runtime.getWorldBinding(x.id), x.worldState, 'same world modes/flags');
    equal(x.runtime.getStatusBinding(x.id), x.statusState, 'same status272');
    equal(x.runtime.getStageBinding(x.id), x.stage, 'same genuine stage18');
    equal(x.runtime.getControlBinding(x.id), x.controlState, 'same genuine control490');
    equal(x.runtime.getActualBorg(x.id), x.borg, 'same borrowed Borg');
    equal(x.runtime.getControlRuntime(), x.control, 'same genuine control runtime');
    equal(x.runtime.getStageRuntime(), x.stageBounds, 'same genuine stage runtime');
    equal(x.control.getReadyRuntime(), undefined, 'not implicitly attached');
    check(Object.isFrozen(x.runtime) && Object.isSealed(x.binding()), 'frozen runtime/sealed binding');
    check(x.binding() !== x.initial, 'input copied');
    const keys = ['byte19','byte1a','byte1b','byte489','byte48e','byte48f','byte3ef','short48c','short494','short496','short49e','short3ea'];
    equal(Object.keys(x.binding()).join(','), keys.join(','), 'only absent fields get storage');
    check(isSourceActorReadyTransitionsRuntime(x.runtime), 'genuine brand');
    for (const fake of [{...x.runtime}, Object.create(x.runtime), {}, null, () => x.runtime])
      check(!isSourceActorReadyTransitionsRuntime(fake), 'brand not forged');
    x.initial.short3ea = 12; x.run490(); equal(x.binding().short48c, -12, 'input not live');
    equal(x.binding().short494, -17, 'zero mode negative hp is not clamped');
    equal(x.binding().byte19, 2, 'leaf does not perform caller byte19 store');
    equal(x.binding().byte489, 8, 'leaf does not perform caller byte489 store');
    equal(x.worldState.flags48a, 2, '490 helper preserves48a');
    rejects(() => Object.assign(x.binding(), {newField: 0}), 'not extensible');
    rejects(() => x.bind(), 'new symbol'); rejects(() => x.runtime.transition490(Symbol()), 'unknown/non-owned');
    x.attach(); equal(x.control.getReadyRuntime(), x.runtime, 'once-only explicit attachment');
    rejects(x.attach, 'already bound');
  }
  {
    // Independent modular signed16 reference, covering every halfword bit pattern
    // for each source short and the existing rawu16 maximum HP representation.
    const x = fixture();
    for (let bits = 0; bits < 65536; bits++) {
      const signed = bits < 32768 ? bits : bits - 65536;
      x.borg.hp = signed; x.borg.maxHp = bits; x.statusState.short272 = signed;
      x.binding().short3ea = signed; x.run490();
      equal(x.binding().short494, signed, 'all signed hp, no clamp');
      equal(x.binding().short496, signed, 'all raw maxHp lha signextension');
      equal(x.binding().short48c, signed, 'all signed3ea');
      const flags = bits | 0x443;
      equal(x.statusState.short272, flags < 32768 ? flags : flags - 65536, 'all signed272 OR0443');
      x.binding().short49e = signed; x.run48a();
      equal(x.binding().short48c, signed, 'all signed49e');
      equal(x.binding().short494, signed, '48a all signed hp');
      equal(x.binding().short496, signed, '48a all raw maxHp');
    }
  }
  {
    for (let raw = 0; raw < 256; raw++) {
      const x = fixture(); x.borg.colorVariant = raw; x.binding().byte3ef = raw;
      x.run490(); equal(x.binding().byte48e, raw, 'all color raw bytes'); equal(x.binding().byte48f, raw, 'all variant raw bytes');
      const y = fixture(); y.worldState.mode4a0 = raw;
      if (raw === 0) y.run490();
      else {
        y.borg.hp = NaN; y.borg.maxHp = NaN;
        rejects(y.run490, '8006aa00 reached unsupported source call 80066198(form=65524, color=-55, variant=-17)');
        equal(y.binding().short494, 31, 'nonzero branch refuses before hp mirror');
        equal(y.binding().short496, 32, 'nonzero branch refuses before maxHp mirror');
        y.worldState.mode4a0 = 0; rejects(y.run490, 'known incomplete ready transition');
      }
      // Leaf48a does not read either mode, source3ef, source3ea or mirror48f.
      const z = fixture(true); delete z.initial.short3ea; delete z.initial.byte3ef; delete z.initial.byte48f; z.bind();
      z.worldState.mode4a0 = NaN; z.worldState.mode4a1 = NaN; z.borg.colorVariant = raw;
      z.run48a(); equal(z.binding().byte48e, raw, '48a all color bytes'); equal(z.binding().byte48f, undefined, '48f stays absent');
      equal(z.worldState.mode4a1, NaN, '48a never reads/writes4a1');
    }
  }
  {
    // Every destination is validated only at its reached store. Its failure
    // preserves every preceding store and none of the following ones.
    for (const branch490 of [true, false]) {
      const length = stores(fixture(), branch490).length;
      for (let index = 0; index < length; index++) {
        const x = fixture(); x.worldState.mode4a1 = 99;
        const writes = stores(x, branch490), before = writes.map(({owner,key}) => Reflect.get(owner, key));
        const stop = writes[index]!; Object.defineProperty(stop.owner, stop.key, {writable: false});
        const run = branch490 ? x.run490 : x.run48a;
        rejects(run, `${stop.key}: non-writable`);
        writes.forEach(({owner,key,after}, i) => equal(Reflect.get(owner,key), i < index ? after : before[i], `store prefix${index}/${key}`));
        x.worldState.mode4a0 = 1; rejects(run, 'known incomplete ready transition');
      }
      for (const key of ['byte19','byte1a','byte1b','short48c','byte48e','short494','short496', ...(branch490 ? ['byte48f'] : [])] as Array<keyof SourceActorReadyTransitionsBinding>) {
        const x = fixture(true); delete x.initial[key]; x.bind();
        rejects(branch490 ? x.run490 : x.run48a, `${key}: own data`);
        check(!Object.hasOwn(x.binding(), key), 'no missing destination hydration');
      }
    }
    for (const owner of ['stage', 'control'] as const) {
      const x = fixture(false, owner); rejects(x.run490, `${owner === 'stage' ? 'lifecycle18' : 'byte490'}: own data`);
    }
  }
  {
    const cases: Array<{key: string; owner: (x: Fixture) => object; previous: string; untouched: string}> = [
      {key: 'short3ea', owner: x => x.binding(), previous: 'byte1b', untouched: 'short48c'},
      {key: 'colorVariant', owner: x => x.borg, previous: 'short48c', untouched: 'byte48e'},
      {key: 'byte3ef', owner: x => x.binding(), previous: 'byte48e', untouched: 'byte48f'},
      {key: 'mode4a0', owner: x => x.worldState, previous: 'byte48f', untouched: 'short494'},
      {key: 'hp', owner: x => x.borg, previous: 'byte48f', untouched: 'short494'},
      {key: 'maxHp', owner: x => x.borg, previous: 'short494', untouched: 'short496'},
    ];
    for (const test of cases) {
      const x = fixture(), before = Reflect.get(x.binding(), test.untouched);
      Reflect.set(test.owner(x), test.key, NaN);
      rejects(x.run490, `${test.key}: integer`);
      const expected = stores(x, true).find(({key}) => key === test.previous)!;
      equal(Reflect.get(expected.owner, expected.key), expected.after, `${test.key} prior prefix`);
      equal(Reflect.get(x.binding(), test.untouched), before, `${test.key} no premature store`);
    }
    for (const key of ['hp','maxHp','colorVariant'] as const) {
      const x = fixture(); delete (x.borg as Partial<typeof x.borg>)[key];
      rejects(x.run490, `${key}: own data`); equal(x.controlState.byte490, 4, 'missing Borg value preserves prefix');
      const y = fixture(); let touched = false;
      Object.defineProperty(y.borg, key, {get() {touched = true; return 1;}});
      rejects(y.run48a, `${key}: own data`); check(!touched, 'Borg accessor never invoked');
    }
    for (const key of ['hp','maxHp','colorVariant'] as const) {
      const invalid = key === 'hp' ? [-32769,32768] : key === 'maxHp' ? [-1,65536] : [-1,256];
      for (const value of [...invalid, NaN, Infinity, 0.5]) {
        const x = fixture(); x.borg[key] = value; rejects(x.run490, `${key}: integer`);
      }
    }
    const x = fixture(); x.borg.hp = -0; x.borg.maxHp = -0; x.borg.colorVariant = -0; x.run490();
    equal(x.binding().short494, 0, 'hp minus zero normalized'); equal(x.binding().short496, 0, 'maxHp minus zero normalized');
  }
  {
    for (const key of ['byte19','byte1a','byte1b','byte489','byte48e','byte48f','byte3ef','short48c','short494','short496','short49e','short3ea'] as const) {
      for (const value of [NaN, Infinity, 0.5, key.startsWith('short') ? -32769 : -1, key.startsWith('short') ? 32768 : 256]) {
        const x = fixture(true); x.initial[key] = value; rejects(x.bind, `${key}: integer`);
      }
    }
    const empty = fixture(true); for (const key of Object.keys(empty.initial)) Reflect.deleteProperty(empty.initial,key);
    empty.bind(); equal(Object.keys(empty.binding()).length, 0, 'empty partial stays empty');
    rejects(empty.run490, 'byte19: own data'); equal(empty.stage.lifecycle18, 2, 'missing19 keeps first18 store');
    const x = fixture(true); Object.assign(x.initial, {lifecycle18: 7}); rejects(x.bind, 'competing');
    const y = fixture(true); let touched = false;
    Object.defineProperty(y.initial, 'byte19', {get() {touched = true; return 0;}});
    rejects(y.bind, 'byte19: own data'); check(!touched, 'initial accessor not invoked');
  }
  {
    for (const key of ['worldActor','statusActor','world','status','statusWorld','borg'] as const) {
      for (const replacement of [{}, Promise.resolve({}), null]) {
        const x = fixture(); x.hooks[key] = () => replacement;
        rejects(x.run490, 'owner changed'); equal(x.stage.lifecycle18, 1, 'owner mismatch before source stores');
        delete x.hooks[key]; rejects(x.run490, 'known incomplete ready transition');
      }
    }
    for (const value of [null, Promise.resolve({})]) {
      const x = fixture(true); x.hooks.borg = () => value;
      rejects(x.bind, 'synchronous actual');
    }
    const alias = fixture(true); alias.hooks.borg = () => alias.worldState; rejects(alias.bind, 'source owner alias');
    const x = fixture(true); x.hooks.statusWorld = () => ({}); rejects(x.bind, 'owner changed');
    for (const owner of ['stageBounds','control'] as const) {
      const x = fixture(); const sources = {...x.sources, [owner]: {...x.sources[owner]}};
      rejects(() => createSourceActorReadyTransitionsRuntime(sources), `${owner} requires genuine`);
    }
    for (const owner of ['actual','worldState','statusState','borg'] as const) {
      const x = fixture(true); Object.assign(x[owner], {byte489: 1}); rejects(x.bind, 'competing');
    }
    const shadow = fixture(); Object.assign(shadow.actual, {byte3ed: 1}); rejects(shadow.run490, 'competing');
    const x2 = fixture();
    const other = createSourceActorReadyTransitionsRuntime(x2.sources); rejects(() => other.bindActor(x2.id, x2.initial), 'already claimed');
    const captured = fixture();
    captured.sources.world = {...captured.world, getActualActor: () => {throw Error('replaced source');}};
    captured.world.getActorBinding = () => {throw Error('replaced method');}; captured.run490();
    equal(captured.binding().short494, -17, 'captured methods preserve original receiver');
  }
  {
    const x = fixture(); x.attach(); x.worldState.flags48a = 0;
    equal(x.runControl(), 1, 'complete490 caller returns1');
    equal(x.controlState.short49a, 0, 'caller decrement precedes helper');
    equal(x.binding().byte489, 4, 'caller489 store'); equal(x.binding().byte19, 3, 'caller19 overwrites leaf2');
    equal(x.runControl(), 0, 'completed caller clears incomplete guard');
    x.controlState.byte490 = 2; x.controlState.short49a = 1;
    equal(x.runControl(), 1, 'new explicit complete transition admitted');
    for (const key of ['byte489','byte19'] as const) {
      const y = fixture(); y.attach(); y.worldState.flags48a = 0;
      Object.defineProperty(y.binding(), key, {writable: false});
      rejects(y.runControl, `${key}: non-writable`);
      equal(y.controlState.short49a, 0, 'failed caller preserves decrement');
      if (key === 'byte489') equal(y.binding().byte19, 2, 'failed489 leaves leaf19=2');
      y.worldState.mode4a1 = 1; rejects(y.runControl, 'known incomplete control transition');
    }
    for (const team of [0,1,127,128,255]) {
      const y = fixture(); y.attach(); y.actual.team = team;
      rejects(y.runControl, `8005a218 reached unsupported source call 80176ec0(actor, team=${team < 128 ? team : team - 256}, 0)`);
      equal(y.worldState.flags48a, 4, '48a real leaf executes'); equal(y.binding().short496, 0x9001 - 65536, '48a leaf fully returns');
      equal(y.binding().byte489, 8, '48a caller does not write489'); equal(y.binding().byte19, 2, '48a caller does not write19=3');
      equal(y.binding().byte48f, 8, '48a preserves48f');
      y.worldState.mode4a0 = 1; rejects(y.runControl, 'known incomplete control transition');
    }
    const y = fixture(); y.attach(); y.actual.team = NaN; rejects(y.runControl, 'team: integer');
    equal(y.binding().short496, 0x9001 - 65536, 'invalid team read after complete leaf');
    const z = fixture(); z.attach(); let touched = false;
    Object.defineProperty(z.actual, 'team', {get() {touched = true; return 1;}});
    rejects(z.runControl, 'team: own data'); check(!touched, 'team accessor not invoked');
    equal(z.binding().short496, 0x9001 - 65536, 'team access remains after leaf');
    const forged = fixture(); rejects(() => forged.control.bindReadyRuntime({...forged.runtime}), 'genuine source');
    const other = fixture(); rejects(() => forged.control.bindReadyRuntime(other.runtime), 'ready control runtime');
    equal(forged.control.getReadyRuntime(), undefined, 'failed attachment remains unbound');
  }
  {
    // A direct leaf shares its completion boundary with an attached caller.
    // Gates and timers cannot hide retained partial writes, even on late attach.
    for (const late of [false, true]) {
      const x = fixture(); if (!late) x.attach();
      delete (x.borg as Partial<typeof x.borg>).hp;
      rejects(x.run490, 'hp: own data'); equal(x.controlState.byte490, 4, 'direct failure retained490');
      if (late) {
        x.worldState.flags48a = 0; rejects(x.runControl, 'known incomplete ready transition');
        x.worldState.mode4a1 = 1; rejects(x.runControl, 'known incomplete ready transition');
        x.worldState.mode4a1 = 0; x.attach();
      }
      x.borg.hp = 17; x.worldState.flags48a = 0;
      rejects(() => x.runtime.assertActorComplete(x.id), 'known incomplete ready transition');
      rejects(x.runControl, 'known incomplete ready transition');
      x.worldState.mode4a1 = 1; rejects(x.runControl, 'known incomplete ready transition');
      x.worldState.mode4a1 = 0; x.worldState.mode4a0 = 1; rejects(x.runControl, 'known incomplete ready transition');
      x.worldState.mode4a0 = 0; x.statusState.byte6fc = 1; rejects(x.runControl, 'known incomplete ready transition');
      x.controlState.short49a = 20; x.controlState.short49c = 30; x.controlState.byte490 = 2;
      x.hooks.worldActor = () => {throw Error('source owner read before completeness assertion');};
      rejects(x.runControl, 'known incomplete ready transition');
      equal(x.controlState.short49a, 20, 'shared guard before countdown');
      equal(x.controlState.short49c, 30, 'shared guard before other countdown');
      equal(x.binding().short494, 31, 'no recovery or manufactured copy');
    }
    for (const branch490 of [true, false]) {
      const x = fixture(); x.attach();
      (branch490 ? x.run490 : x.run48a)(); x.runtime.assertActorComplete(x.id);
      x.worldState.flags48a = 0; equal(x.runControl(), 0, 'genuine successful standalone leaf remains usable');
    }
  }
  {
    // Mutation reentry through an owner seam, including when its exception is
    // swallowed, poisons the outer call. Accessors/Proxy behavior is not evidence.
    for (const operation of ['transition490','transition48a','bindActor'] as const) {
      const x = fixture();
      x.hooks.borg = () => {
        try {if (operation === 'bindActor') x.runtime.bindActor(Symbol(), {}); else x.runtime[operation](x.id);} catch {}
        return x.borg;
      };
      rejects(x.run490, 'caught same-runtime reentry'); equal(x.stage.lifecycle18, 1, 'reentry before source stores');
      delete x.hooks.borg; rejects(x.run490, 'known incomplete ready transition');
    }
    const x = fixture(); x.attach(); x.worldState.flags48a = 0;
    x.hooks.borg = () => {try {x.runControl();} catch {} return x.borg;};
    rejects(x.runControl, 'caught same-runtime reentry');
    delete x.hooks.borg; x.worldState.mode4a1 = 1; rejects(x.runControl, 'known incomplete control transition');
    // An owner seam can change4a0 after the caller read0. The leaf must reload,
    // not reuse that earlier gate or silently choose its zero branch.
    const fresh = fixture(); fresh.attach(); fresh.worldState.flags48a = 0;
    fresh.hooks.borg = () => {fresh.worldState.mode4a0 = 128; return fresh.borg;};
    rejects(fresh.runControl, '80066198'); equal(fresh.binding().byte48f, 239, 'freshmode retains helper prefix');
    equal(fresh.binding().short494, 31, 'freshmode never copies hp');
    delete fresh.hooks.borg; fresh.worldState.mode4a0 = 0; rejects(fresh.runControl, 'known incomplete control transition');
  }
}
