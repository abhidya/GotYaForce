import {createSourceTObjScalarRuntime, type SourceTObjScalarHeader, type SourceTObjScalarRuntime} from './tobj-update.js';

function check(ok: boolean, message: string): void { if (!ok) throw Error(`[tobj-update] ${message}`); }
function rejects(run: () => void, expected: string): void {
  let diagnostic = ''; try { run(); } catch (error) { diagnostic = String(error); }
  check(diagnostic.includes(expected), `expected ${expected}, got ${diagnostic}`);
}
function fields(patch: Partial<SourceTObjScalarHeader> = {}): SourceTObjScalarHeader {
  return {flags4c: 0, rotation18: -0, rotation1c: 2, rotation20: 3, scale28: 4,
    scale2c: -0, translation34: 6, translation38: 7, ...patch};
}
function texture(r: SourceTObjScalarRuntime, patch: Partial<SourceTObjScalarHeader> = {}) {
  const id = r.createTexture(fields(patch)); return {id, n: r.getTexture(id)};
}
function same(actual: SourceTObjScalarHeader, expected: SourceTObjScalarHeader, message: string): void {
  check((Object.keys(expected) as (keyof SourceTObjScalarHeader)[]).every(key => Object.is(actual[key], expected[key])), message);
}
const trackFields = [[2, 'translation34'], [3, 'translation38'], [4, 'scale28'],
  [5, 'scale2c'], [6, 'rotation18'], [7, 'rotation1c'], [8, 'rotation20']] as const;
const allKeys = Object.keys(fields()) as (keyof SourceTObjScalarHeader)[];
const finiteValues = [13.25, 0, -0, 2 ** -149, -(2 ** -149), 2 ** -126 - 2 ** -149,
  -(2 ** -126 - 2 ** -149), 2 ** -126, -(2 ** -126),
  (2 - 2 ** -23) * 2 ** 127, -((2 - 2 ** -23) * 2 ** 127)];
const invalidScalars: unknown[] = [NaN, Infinity, -Infinity, 0.1, 2 ** 128, 2 ** -150,
  -(2 ** -150), undefined, null, '1', false, 1n, Symbol('scalar')];
const invalidFlags: unknown[] = [-1, 1.5, NaN, Infinity, -Infinity, 0x100000000,
  undefined, null, '1', false, 1n, Symbol('flags')];

export function runTObjUpdateSelfTest(): void {
  for (const [track, field] of trackFields) {
    for (const value of finiteValues) {
      for (const flags of [0, 0x7fffffff, 0x12345678, 0x80000000, 0x92345678, 0xffffffff]) {
        const r = createSourceTObjScalarRuntime(), t = texture(r, {flags4c: flags}), before = {...t.n};
        check(r.updateScalar(t.id, track, value) === undefined, 'scalar handler returns undefined synchronously');
        same(t.n, {...before, [field]: value, flags4c: (flags | 0x80000000) >>> 0},
          `track${track} copies finite f32 exactly, preserves unrelated fields and all flag bits`);
        r.updateScalar(t.id, track, -0);
        same(t.n, {...before, [field]: -0, flags4c: (flags | 0x80000000) >>> 0},
          `track${track} updates an already-dirty texture`);
      }
    }
    for (let bit = 0; bit < 32; bit++) {
      const r = createSourceTObjScalarRuntime(), flags = (1 << bit) >>> 0, t = texture(r, {flags4c: flags});
      r.updateScalar(t.id, track, 19);
      check(t.n.flags4c === ((flags | 0x80000000) >>> 0), `track${track} preserves flag bit${bit}`);
    }
  }
  {
    const r = createSourceTObjScalarRuntime(), initial = fields(), id = r.createTexture(initial), n = r.getTexture(id);
    initial.rotation18 = 99; initial.flags4c = 123; n.translation38 = 321;
    check(Object.is(n.rotation18, -0) && n.flags4c === 0 && initial.translation38 === 7 &&
      Object.isSealed(n) && !Object.isFrozen(n), 'factory owns an independent sealed mutable record');
    const frozenInput = Object.freeze(fields()), frozenId = r.createTexture(frozenInput);
    r.updateScalar(frozenId, 6, 9);
    check(r.getTexture(frozenId).rotation18 === 9 && Object.is(frozenInput.rotation18, -0),
      'frozen input creates independent writable fields');
    check(Object.isFrozen(r), 'method table is frozen');
    for (const key of ['createTexture', 'getTexture', 'updateScalar'] as const) {
      const method = r[key];
      check(!Reflect.set(r, key, () => undefined) && r[key] === method, `method ${key} cannot be replaced`);
    }
    check(!Reflect.set(r, 'extra', 1) && !Reflect.set(n, 'extra', 1), 'method table and header cannot be extended');
    check(r.getTexture(id) === n && r.createTexture(fields()) !== id, 'identities have stable distinct owned records');
    const other = createSourceTObjScalarRuntime(), foreign = texture(other);
    for (const owner of [foreign.id, Symbol('foreign'), n, {}, undefined, 0, 'texture']) {
      const before = {...n};
      rejects(() => r.getTexture(owner as symbol), 'non-owned texture identity');
      rejects(() => r.updateScalar(owner as symbol, 2, 11), 'non-owned texture identity');
      same(n, before, 'foreign and non-symbol owner refusals have no writes');
    }
    const ignored = {valueOf() { throw Error('null owner inspected an argument'); }} as unknown as number;
    r.updateScalar(null, ignored, ignored); r.updateScalar(null, NaN, Infinity);
    check(n.flags4c === 0, 'null owner returns without inspecting other arguments');
  }
  for (const key of allKeys) {
    const r = createSourceTObjScalarRuntime();
    let getterRead = false;
    const accessor = fields();
    Object.defineProperty(accessor, key, {get() { getterRead = true; return 1; }});
    rejects(() => r.createTexture(accessor), `${key}: own data property`);
    check(!getterRead, `factory does not invoke accessor ${key}`);
    const missing = fields() as Partial<SourceTObjScalarHeader>;
    delete missing[key];
    rejects(() => r.createTexture(missing as SourceTObjScalarHeader), `${key}: own data property`);
    const inherited = Object.assign(Object.create({[key]: 1}) as SourceTObjScalarHeader, missing);
    rejects(() => r.createTexture(inherited), `${key}: own data property`);
    for (const value of key === 'flags4c' ? invalidFlags : invalidScalars) {
      rejects(() => r.createTexture(fields({[key]: value})), key === 'flags4c' ? 'uint32' : 'finite source float32');
    }
    if (key !== 'flags4c') {
      for (const value of finiteValues) {
        const n = r.getTexture(r.createTexture(fields({[key]: value})));
        check(Object.is(n[key], value), `factory preserves exact finite f32 ${key}`);
      }
    }
  }
  {
    const r = createSourceTObjScalarRuntime(), initial = fields();
    Object.defineProperty(initial, 'extra', {get() { throw Error('unrelated input getter invoked'); }});
    r.createTexture(initial);
    for (const input of [null, undefined, 1, false, 'texture', Symbol('texture'), () => fields()]) {
      rejects(() => r.createTexture(input as unknown as SourceTObjScalarHeader), 'data record required');
    }
    const poison = {valueOf() { throw Error('scalar coerced'); }};
    rejects(() => r.createTexture(fields({scale28: poison as unknown as number})), 'finite source float32');
    const t = texture(r);
    rejects(() => r.updateScalar(t.id, 4, poison as unknown as number), 'finite source float32');
    rejects(() => r.updateScalar(t.id, poison as unknown as number, 9), 'unsupported scalar track');
  }
  for (const track of [0, 1, ...Array.from({length: 17}, (_, i) => i + 9), 50, 255, -1,
    2.5, NaN, Infinity, -Infinity, '2', null, undefined, 2n, Symbol('track')]) {
    const r = createSourceTObjScalarRuntime(), t = texture(r), before = {...t.n};
    rejects(() => r.updateScalar(t.id, track as number, 9), 'unsupported scalar track');
    same(t.n, before, 'unsupported tracks refuse before writing any field');
  }
  for (const [track, field] of trackFields) {
    for (const value of invalidScalars) {
      const r = createSourceTObjScalarRuntime(), t = texture(r), before = {...t.n};
      rejects(() => r.updateScalar(t.id, track, value as number), 'finite source float32');
      same(t.n, before, `track${track} refuses invalid new scalar before writes`);
    }
    for (const old of invalidScalars) {
      const r = createSourceTObjScalarRuntime(), t = texture(r);
      t.n[field] = old as number;
      const before = {...t.n};
      r.updateScalar(t.id, track, -0);
      same(t.n, {...before, [field]: -0, flags4c: 0x80000000},
        `track${track} overwrites invalid old target without validating its value`);
    }
    for (const value of invalidFlags) {
      const r = createSourceTObjScalarRuntime(), t = texture(r);
      t.n.flags4c = value as number;
      const before = {...t.n};
      rejects(() => r.updateScalar(t.id, track, 91), 'flags4c: expected uint32');
      same(t.n, {...before, [field]: 91}, `track${track} retains completed scalar store on flags-value refusal`);
    }
    for (const flags of [0, 0x92345678]) {
      const r = createSourceTObjScalarRuntime(), t = texture(r, {flags4c: flags}), before = {...t.n};
      Object.defineProperty(t.n, 'flags4c', {writable: false});
      rejects(() => r.updateScalar(t.id, track, 91), 'flags4c: non-writable');
      same(t.n, {...before, [field]: 91}, `track${track} stores before readonly flags, even already dirty`);
    }
    for (const frozen of ['target', 'all'] as const) {
      const r = createSourceTObjScalarRuntime(), t = texture(r);
      t.n.flags4c = -1;
      const before = {...t.n};
      if (frozen === 'all') Object.freeze(t.n); else Object.defineProperty(t.n, field, {writable: false});
      rejects(() => r.updateScalar(t.id, track, 91), `${field}: non-writable`);
      same(t.n, before, `track${track} readonly target refuses before inspecting invalid flags or writing`);
      rejects(() => r.updateScalar(t.id, track, NaN), 'finite source float32');
      same(t.n, before, 'new scalar validation precedes target validation');
    }
    for (const [, unrelated] of trackFields) {
      if (unrelated === field) continue;
      for (const old of invalidScalars) {
        const r = createSourceTObjScalarRuntime(), t = texture(r);
        t.n[unrelated] = old as number;
        Object.defineProperty(t.n, unrelated, {writable: false});
        const before = {...t.n};
        r.updateScalar(t.id, track, 29);
        same(t.n, {...before, [field]: 29, flags4c: 0x80000000},
          `track${track} ignores unrelated invalid readonly ${unrelated}`);
      }
    }
    {
      const r = createSourceTObjScalarRuntime(), t = texture(r);
      const poison = {valueOf() { throw Error('old scalar coerced'); }} as unknown as number;
      for (const [, key] of trackFields) {
        t.n[key] = poison;
        if (key !== field) Object.defineProperty(t.n, key, {writable: false});
      }
      const before = {...t.n};
      r.updateScalar(t.id, track, 31);
      same(t.n, {...before, [field]: 31, flags4c: 0x80000000},
        `track${track} never coerces old target or unrelated values, even with every unrelated field readonly`);
    }
  }
}
