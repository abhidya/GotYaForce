import {createSourceAObj, createSourceAObjCounters, setSourceAObjEndFrame, setSourceAObjRewindFrame,
  interpretSourceAObj, requestSourceAObj, AOBJ_STOPPED, type SourceAObj} from './aobj-clock.js';
import {createSourceFObjScalarCallbackRuntime} from './fobj-callback.js';
function check(ok: boolean, message: string): void {if (!ok) throw Error(`[aobj-frame-setters-test] ${message}`);}
function rejects(run: () => void, expected: string): void {
  let diagnostic = ''; try {run();} catch (e) {diagnostic = String(e);}
  check(diagnostic.includes(expected), `expected ${expected}, got ${diagnostic || 'success'}`);
}
function fixture() {return createSourceAObj({flags: 0x80000000, frame: 9, rewind: 3, end: 7, rate: 2, fobjs: null});}
export function runAObjFrameSettersSelfTest(): void {
  for (const [key, setter] of [['rewind', setSourceAObjRewindFrame], ['end', setSourceAObjEndFrame]] as const) {
    const poison = new Proxy({}, {get() {throw Error('unexpected coercion');}}) as number;
    for (const value of [poison, NaN, Infinity, -Infinity, .1, 2 ** 128]) setter(null, value);
    const a = fixture(), snapshot = {...a};
    for (const value of [0, -0, -3, 1 + 2 ** -23, 2 ** -149, -(2 ** -149), (2 - 2 ** -23) * 2 ** 127]) {
      check(setter(a, value) === undefined && Object.is(a[key], value), `${key} exact-f32 store with signed zero and no result`);
      check((Object.keys(snapshot) as (keyof SourceAObj)[]).filter(k => k !== key).every(k => Object.is(a[k], snapshot[k])),
        `${key} store leaves every other field unchanged`);
    }
    const before = a[key];
    for (const value of [poison, NaN, Infinity, -Infinity, .1, 1 + 2 ** -25, 2 ** -150, -Number.MIN_VALUE, 2 ** 128]) {
      rejects(() => setter(a, value), 'finite source float32'); check(Object.is(a[key], before), 'invalid argument leaves field unchanged');
    }
    rejects(() => setter({...a}, 0), 'factory-created');
    const proxy = new Proxy(a, {get() {throw Error('read foreign proxy');}, getOwnPropertyDescriptor() {throw Error('inspect foreign proxy');}});
    rejects(() => setter(proxy, 0), 'factory-created'); rejects(() => setter(Object.create(a) as SourceAObj, 0), 'factory-created');
    for (const frozen of [false, true]) {
      const target = fixture(); if (frozen) Object.freeze(target); else Object.defineProperty(target, key, {writable: false});
      rejects(() => setter(target, 0), `non-writable ${key}`);
    }
    const narrow = fixture();
    for (const k of Object.keys(narrow) as (keyof SourceAObj)[]) if (k !== key) {
      (narrow as unknown as Record<string, unknown>)[k] = k === 'fobjs' ? poison : NaN;
      Object.defineProperty(narrow, k, {writable: false});
    }
    for (const old of [NaN, Infinity, .1]) {narrow[key] = old; setter(narrow, -0); check(Object.is(narrow[key], -0), 'old invalid target and unrelated fields ignored');}
  }
  {
    const owner = Symbol('frame setter callback owner'), fobjs = createSourceFObjScalarCallbackRuntime(owner);
    const data = fobjs.createData(Uint8Array.from([2, 3, 4, 2, 11]));
    const node = fobjs.createNode({next00: null, cursor04: null, base08: data, length0c: 5, flags10: 0,
      byte11: 0, byte12: 0, track13: 5, format14: 0x80, format15: 0x80, half16: 0, offset18: 0,
      half1a: 0, frame1c: 0, value20: 0, value24: 0, value28: 0, value2c: 0});
    const a = createSourceAObj({flags: 0, frame: 0, rewind: 9, end: 20, rate: 1, fobjs: node});
    const counters = createSourceAObjCounters(); let calls = 0;
    const callback = fobjs.createCallback((target, track, value) => {
      check(target === owner && track === 5 && value === 7, 'actual packed scalar callback'); calls++;
      setSourceAObjRewindFrame(a, -0); setSourceAObjEndFrame(a, a.frame);
    });
    requestSourceAObj(a, 2, fobjs.effects); interpretSourceAObj(a, callback, fobjs.effects, counters);
    check(calls === 1 && Object.is(a.rewind, -0) && a.end === 2 && a.frame === 2 && a.rate === 1 &&
      a.flags === AOBJ_STOPPED && counters.stopped === 1 && counters.running === 0,
    'both stores work inside busy actual interpretation; end reload stops same pass without a guessed callback result');
  }
  console.log('[aobj-frame-setters] PASS: owned field-local rewind/end stores, finite-f32 bounds and live packed callback effects');
}
