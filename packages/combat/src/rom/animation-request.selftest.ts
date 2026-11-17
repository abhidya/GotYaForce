import {createSourceAnimationRequestRuntime, type SourceAnimationRequestEffects,
  type SourceAnimationRequestRuntime, type SourceAnimationRequestSources} from './animation-request.js';
import {createSourceJObjAnimationRuntime} from './jobj-animation.js';
import {createSourceDObjAnimationRuntime} from './dobj-animation.js';
import {createSourcePObjAnimationRuntime} from './pobj-animation.js';
import {createSourceMObjAnimationRuntime} from './mobj-animation.js';
import {createSourceTObjAnimationRuntime} from './tobj-animation.js';
import {createSourceAObj, requestSourceAObj, AOBJ_REQUEST, AOBJ_STOPPED, type SourceAObjEffects} from './aobj-clock.js';

function check(ok: boolean, message: string): void {if (!ok) throw Error(`[animation-request-test] ${message}`);}
function rejects(run: () => void, expected: string): void {
  let error = ''; try {run();} catch (e) {error = String(e);}
  check(error.includes(expected), `expected ${expected}, got ${error}`);
}
const jointHeader = () => ({sibling08: null, child10: null, flags14: 0,
  rotation1c: 0, rotation20: 0, rotation24: 0, scale2c: 1, scale30: 1, scale34: 1,
  translation38: 0, translation3c: 0, translation40: 0});
const textureHeader = () => ({flags4c: 0, rotation18: 0, rotation1c: 0, rotation20: 0,
  scale28: 1, scale2c: 1, translation34: 0, translation38: 0});
const requests = ['requestJoint', 'requestDObjs', 'requestPObjs', 'requestMObj', 'requestTObjs', 'requestRObjs'] as const;
function sources() {
  return {joints: createSourceJObjAnimationRuntime(), dobjs: createSourceDObjAnimationRuntime(),
    pobjs: createSourcePObjAnimationRuntime(), mobjs: createSourceMObjAnimationRuntime(), tobjs: createSourceTObjAnimationRuntime()};
}
// Explicit synthetic adapters below test host orchestration and failure order.
// Their mutations are NOT source user callbacks or an AObj implementation.
function fixture(maxNodes = 4096) {
  const s = sources(), events: string[] = [], frames: number[] = [], labels = new Map<symbol, string>();
  const label = (name: string) => {const id = Symbol(name); labels.set(id, name); return id;};
  let hook: (id: symbol | null, frame: number) => unknown = () => {};
  const effects: SourceAnimationRequestEffects = {requestAObj(id, frame) {
    check(this === effects, 'request adapter retains original this');
    events.push(id === null ? 'null' : labels.get(id) ?? 'unknown'); frames.push(frame);
    return hook(id, frame) as void;
  }};
  const r = createSourceAnimationRequestRuntime(s, effects, maxNodes);
  const a = {j: label('j'), d: label('d'), p: label('p'), m: label('m'), t: label('t'), r: label('r')};
  const p = s.pobjs.createPObj({next04: null, aobj18: a.p, classUpdate48: null});
  const t = s.tobjs.createTexture(textureHeader(), {next08: null, aobj64: a.t, classUpdate48: null});
  const m = s.mobjs.createMObj({tobj08: t, aobj14: a.m, classUpdate4c: null});
  const d = s.dobjs.createDObj({next04: null, mobj08: m, pobj0c: p, aobj10: a.d, classUpdate44: null});
  const ro = r.createRObj({next00: null, aobj18: a.r});
  const j = s.joints.createJoint(jointHeader(), {parent0c: null, aobj7c: a.j, robj80: ro, dobj18: d, classUpdate50: null});
  const ids = {requestJoint: j, requestDObjs: d, requestPObjs: p, requestMObj: m, requestTObjs: t, requestRObjs: ro};
  return {s, r, effects, events, frames, label, a, j, d, p, m, t, ro, ids, setHook(fn: typeof hook) {hook = fn;}};
}
export function runAnimationRequestSelfTest(): void {
  for (const max of [0, -1, 1.5, NaN, Infinity, Number.MAX_SAFE_INTEGER + 1]) {
    rejects(() => createSourceAnimationRequestRuntime(sources(), {requestAObj() {}}, max), 'maxNodes');
  }
  {
    const x = fixture(), initial = {next00: null, aobj18: null};
    const id = x.r.createRObj(initial), value = x.r.getRObj(id);
    check(Object.isFrozen(x.r) && Object.isSealed(value), 'runtime frozen and owned RObj binding sealed');
    initial.next00 = Symbol('external mutation') as unknown as null;
    check(value.next00 === null, 'RObj input copied without aliasing');
    rejects(() => x.r.getRObj(Symbol('foreign')), 'non-owned RObj');
    rejects(() => x.r.createRObj(null as never), 'data record');
    for (const key of ['next00', 'aobj18'] as const) {
      let invoked = false;
      const bad = Object.defineProperty({...value}, key, {get() {invoked = true; return null;}});
      rejects(() => x.r.createRObj(bad), 'own data property'); check(!invoked, 'RObj input getter never invoked');
      rejects(() => x.r.createRObj({...value, [key]: 7}), 'opaque symbol');
    }
    for (const request of requests) {
      x.r[request](null, NaN, NaN);
      for (const flags of [-1, 0x100000000, 0.5, NaN, Infinity]) rejects(() => x.r[request](x.ids[request], NaN, flags), 'uint32');
      rejects(() => x.r[request](7 as unknown as symbol, 0, 0), 'opaque symbol');
      rejects(() => x.r[request](Symbol('foreign'), 0, 0), 'non-owned');
    }
    check(x.events.length === 0, 'null targets bypass invalid inputs, bad flags/targets precede effects');
  }
  {
    const s = sources(), effects = {requestAObj() {}};
    for (const key of ['joints', 'dobjs', 'pobjs', 'mobjs', 'tobjs'] as const) {
      let invoked = false;
      const bad = Object.defineProperty({...s}, key, {get() {invoked = true; return s[key];}});
      rejects(() => createSourceAnimationRequestRuntime(bad, effects), 'own data property'); check(!invoked, 'runtime-table accessor not invoked');
    }
    for (const [table, name] of [['joints', 'getJoint'], ['joints', 'getBinding'], ['dobjs', 'getDObj'],
      ['pobjs', 'getPObj'], ['mobjs', 'getMObj'], ['tobjs', 'getBinding']] as const) {
      let invoked = false; const bad = {...s[table]};
      Object.defineProperty(bad, name, {get() {invoked = true; return () => {};}});
      rejects(() => createSourceAnimationRequestRuntime({...s, [table]: bad}, effects), 'own data property');
      check(!invoked, 'getter-method accessor not invoked');
      rejects(() => createSourceAnimationRequestRuntime({...s, [table]: Object.create(s[table])}, effects), 'own data property');
      rejects(() => createSourceAnimationRequestRuntime({...s, [table]: {...s[table], [name]: 7}}, effects), 'own data-function');
    }
    rejects(() => createSourceAnimationRequestRuntime(s, undefined as never), 'data record');
    rejects(() => createSourceAnimationRequestRuntime(s, Object.create(effects)), 'own data property');
    rejects(() => createSourceAnimationRequestRuntime(s, {requestAObj: null} as never), 'own data-function');
    let invoked = false;
    rejects(() => createSourceAnimationRequestRuntime(s, Object.defineProperty({}, 'requestAObj', {
      get() {invoked = true; return () => {};},
    }) as SourceAnimationRequestEffects), 'own data property');
    check(!invoked, 'request-method accessor never invoked');
  }
  for (const flags of [0, 1, 2, 4, 8, 0x10, 0x20, 0x40, 0x80, 0x9d, 0xffffffff]) {
    const x = fixture(); x.r.requestJoint(x.j, -0, flags);
    const expected = [[1, 'j'], [8, 'p'], [4, 'm'], [0x10, 't'], [0x80, 'r']]
      .filter(([bit]) => (flags & (bit as number)) !== 0).map(([, name]) => name).join();
    check(x.events.join() === expected, `mask ${flags}: JObj,PObj,MObj,TObj,RObj order, never DObj AObj`);
    check(x.frames.every(frame => Object.is(frame, -0)), 'negative zero forwarded without coercion');
  }
  for (const gate of [0x20, 0x4000, 0x4020, 0x100, 0]) {
    const x = fixture(); x.s.joints.getJoint(x.j).flags14 = gate;
    if ((gate & 0x4020) !== 0) {
      x.s.joints.getBinding(x.j).dobj18 = 7 as unknown as symbol;
      Object.defineProperty(x.s.joints.getBinding(x.j), 'dobj18', {writable: false});
    }
    x.r.requestJoint(x.j, 2, 0x9d);
    check(x.events.join() === ((gate & 0x4020) !== 0 ? 'j,r' : 'j,p,m,t,r'), 'source 0x4020 gate excludes DObj read, not RObj');
  }
  for (const before of [0, 0x20]) {
    const x = fixture(); x.s.joints.getJoint(x.j).flags14 = before;
    x.setHook(id => {if (id === x.a.j) x.s.joints.getJoint(x.j).flags14 = before === 0 ? 0x4000 : 0;});
    x.r.requestJoint(x.j, 1, 0x9d);
    check(x.events.join() === (before === 0 ? 'j,r' : 'j,p,m,t,r'), 'JObj gate reloaded after request adapter');
  }
  {
    const x = fixture();
    x.s.joints.getBinding(x.j).aobj7c = null; x.s.pobjs.getPObj(x.p).aobj18 = null;
    x.s.mobjs.getMObj(x.m).aobj14 = null; x.s.tobjs.getBinding(x.t).aobj64 = null; x.r.getRObj(x.ro).aobj18 = null;
    x.r.requestJoint(x.j, NaN, 0x9d);
    check(x.events.join() === 'null,null,null,null' && x.frames.every(Number.isNaN),
      'J/P/M/T forward null AObj and invalid frame, RObj source null guard skips call');
    x.events.length = 0; x.r.requestJoint(x.j, Infinity, 0);
    check(x.events.length === 0, 'mask0 performs no numeric frame admission');
  }
  {
    const x = fixture(), binding = x.s.joints.getBinding(x.j);
    binding.aobj7c = 7 as unknown as symbol; Object.defineProperty(binding, 'aobj7c', {writable: false});
    x.r.requestJoint(x.j, NaN, 0);
    check(x.events.length === 0, 'mask0 does not read unused JObj AObj');
    const first = x.r.createRObj({next00: x.ro, aobj18: null});
    const skipped = x.r.createRObj({next00: null, aobj18: null}); Object.freeze(x.r.getRObj(skipped));
    x.r.getRObj(x.ro).next00 = skipped;
    x.setHook(id => {if (id === x.a.r) x.r.getRObj(x.ro).next00 = x.r.createRObj({next00: null, aobj18: null});});
    x.r.requestRObjs(first, 1, 0x80);
    check(x.events.join() === 'r', 'RObj null guard still follows list; live tail allocation skips unvisited frozen record');
  }
  {
    const x = fixture(), jb = x.s.joints.getBinding(x.j), jh = x.s.joints.getJoint(x.j);
    jb.parent0c = 7 as unknown as symbol; jb.classUpdate50 = 7 as unknown as symbol;
    jh.sibling08 = Symbol('unvisited sibling'); jh.child10 = Symbol('unvisited child'); jh.rotation1c = NaN;
    x.s.tobjs.getTexture(x.t).rotation18 = NaN; Object.freeze(x.s.tobjs.getTexture(x.t));
    x.s.dobjs.getDObj(x.d).aobj10 = 7 as unknown as symbol;
    for (const [record, key] of [[jb, 'parent0c'], [jb, 'classUpdate50'], [jh, 'rotation1c'],
      [x.s.dobjs.getDObj(x.d), 'aobj10'], [x.s.dobjs.getDObj(x.d), 'classUpdate44'],
      [x.s.pobjs.getPObj(x.p), 'classUpdate48'], [x.s.mobjs.getMObj(x.m), 'classUpdate4c'],
      [x.s.tobjs.getBinding(x.t), 'classUpdate48']] as const) Object.defineProperty(record, key, {writable: false});
    x.s.joints.endCallbacks.counts.running = 17; x.s.joints.endCallbacks.counts.stopped = 19;
    let ended = false;
    x.s.joints.endCallbacks.state.head28 = x.s.joints.endCallbacks.createNode({next00: null,
      callback04: x.s.joints.endCallbacks.createCallback(() => {ended = true;})});
    x.r.requestJoint(x.j, 3, 0x9d);
    check(x.events.join() === 'j,p,m,t,r' && jh.flags14 === 0 && !ended &&
      x.s.joints.endCallbacks.counts.running === 17 && x.s.joints.endCallbacks.counts.stopped === 19,
    'no unused callback/scalar/parent/tree/DObj AObj checks, dependency, interpretation or completion work');
  }
  {
    const x = fixture(), jb = x.s.joints.getBinding(x.j), d = x.s.dobjs.getDObj(x.d), p = x.s.pobjs.getPObj(x.p);
    const m = x.s.mobjs.getMObj(x.m), t = x.s.tobjs.getBinding(x.t), ro = x.r.getRObj(x.ro);
    const p2A = x.label('p2'), t2A = x.label('t2'), r2A = x.label('r2');
    const p2 = x.s.pobjs.createPObj({next04: null, aobj18: p2A, classUpdate48: null});
    const t2 = x.s.tobjs.createTexture(textureHeader(), {next08: null, aobj64: t2A, classUpdate48: null});
    const r2 = x.r.createRObj({next00: null, aobj18: r2A});
    const d2 = x.s.dobjs.createDObj({next04: null, pobj0c: null, mobj08: null, aobj10: null, classUpdate44: null});
    x.s.joints.getJoint(x.j).flags14 = NaN; jb.dobj18 = 7 as unknown as symbol; jb.robj80 = 7 as unknown as symbol;
    d.mobj08 = 7 as unknown as symbol; d.next04 = 7 as unknown as symbol;
    p.next04 = 7 as unknown as symbol; m.tobj08 = 7 as unknown as symbol; t.next08 = 7 as unknown as symbol; ro.next00 = 7 as unknown as symbol;
    x.setHook(id => {
      if (id === x.a.j) {
        x.s.joints.getJoint(x.j).flags14 = 0; jb.dobj18 = x.d;
        jb.aobj7c = 7 as unknown as symbol; Object.defineProperty(jb, 'aobj7c', {writable: false});
      } else if (id === x.a.p) {
        d.mobj08 = x.m; p.next04 = p2; p.aobj18 = 7 as unknown as symbol;
      } else if (id === x.a.m) {m.tobj08 = x.t; m.aobj14 = 7 as unknown as symbol;}
      else if (id === x.a.t) {t.next08 = t2; t.aobj64 = 7 as unknown as symbol;}
      else if (id === t2A) {d.next04 = d2; jb.robj80 = x.ro;}
      else if (id === x.a.r) {ro.next00 = r2; ro.aobj18 = 7 as unknown as symbol;}
    });
    x.r.requestJoint(x.j, 1, 0x9d);
    check(x.events.join() === 'j,p,p2,m,t,t2,r,r2', 'later source reads see repairs; live all-list links and current RObj after DObj');
  }
  for (const kind of ['PObj', 'TObj', 'RObj', 'DObj'] as const) {
    for (const mask of [0, 1]) {
      const x = fixture();
      const cases = {
        PObj: {run: () => x.r.requestPObjs(x.p, NaN, mask), node: x.s.pobjs.getPObj(x.p), next: 'next04', a: 'aobj18'},
        TObj: {run: () => x.r.requestTObjs(x.t, NaN, mask), node: x.s.tobjs.getBinding(x.t), next: 'next08', a: 'aobj64'},
        RObj: {run: () => x.r.requestRObjs(x.ro, NaN, mask), node: x.r.getRObj(x.ro), next: 'next00', a: 'aobj18'},
        DObj: {run: () => x.r.requestDObjs(x.d, NaN, mask), node: x.s.dobjs.getDObj(x.d), next: 'next04', a: 'aobj10'},
      };
      const item = cases[kind], data = item.node as unknown as Record<string, unknown>;
      data[item.a] = 7; Object.defineProperty(data, item.a, {writable: false});
      if (kind === 'RObj') rejects(item.run, 'aobj18: non-writable');
      else {item.run(); data[item.next] = Symbol('foreign tail'); rejects(item.run, 'non-owned');}
      check(x.events.length === 0, 'masks suppress only requests; RObj reads aobj before mask, other lists skip unused AObj');
    }
  }
  {
    const x = fixture(); x.s.mobjs.getMObj(x.m).aobj14 = 7 as unknown as symbol;
    Object.defineProperty(x.s.mobjs.getMObj(x.m), 'aobj14', {writable: false});
    x.r.requestMObj(x.m, 1, 0x10); check(x.events.join() === 't', 'MObj always reaches texture even without material request bit');
    x.s.tobjs.getBinding(x.t).next08 = Symbol('foreign texture');
    rejects(() => x.r.requestMObj(x.m, NaN, 0), 'non-owned');
  }
  // Every consumed field is admitted at its source boundary, preserving prefixes.
  for (const defect of ['type', 'frozen'] as const) {
    for (const field of ['aobj7c', 'flags14', 'dobj18', 'pobj0c', 'p-aobj18', 'p-next04', 'mobj08', 'aobj14',
      'tobj08', 'aobj64', 'next08', 'd-next04', 'robj80', 'r-aobj18', 'next00'] as const) {
      const x = fixture();
      const cases = {
        aobj7c: [x.s.joints.getBinding(x.j), 'aobj7c', ''], flags14: [x.s.joints.getJoint(x.j), 'flags14', 'j'],
        dobj18: [x.s.joints.getBinding(x.j), 'dobj18', 'j'], pobj0c: [x.s.dobjs.getDObj(x.d), 'pobj0c', 'j'],
        'p-aobj18': [x.s.pobjs.getPObj(x.p), 'aobj18', 'j'], 'p-next04': [x.s.pobjs.getPObj(x.p), 'next04', 'j,p'],
        mobj08: [x.s.dobjs.getDObj(x.d), 'mobj08', 'j,p'], aobj14: [x.s.mobjs.getMObj(x.m), 'aobj14', 'j,p'],
        tobj08: [x.s.mobjs.getMObj(x.m), 'tobj08', 'j,p,m'], aobj64: [x.s.tobjs.getBinding(x.t), 'aobj64', 'j,p,m'],
        next08: [x.s.tobjs.getBinding(x.t), 'next08', 'j,p,m,t'], 'd-next04': [x.s.dobjs.getDObj(x.d), 'next04', 'j,p,m,t'],
        robj80: [x.s.joints.getBinding(x.j), 'robj80', 'j,p,m,t'], 'r-aobj18': [x.r.getRObj(x.ro), 'aobj18', 'j,p,m,t'],
        next00: [x.r.getRObj(x.ro), 'next00', 'j,p,m,t,r'],
      } as const;
      const [record, key, expected] = cases[field];
      if (defect === 'frozen') Object.defineProperty(record, key, {writable: false});
      else (record as unknown as Record<string, unknown>)[key] = field === 'flags14' ? NaN : 7;
      rejects(() => x.r.requestJoint(x.j, 1, 0x9d), defect === 'frozen' ? 'non-writable' : field === 'flags14' ? 'uint32' : 'opaque symbol');
      check(x.events.join() === expected, `${field}/${defect}: exact effect prefix retained`);
    }
  }
  for (const fault of ['j', 'p', 'm', 't', 'r']) {
    for (const result of ['throw', 'promise', 'number', 'null']) {
      const x = fixture(); x.setHook(id => {if (id === x.a[fault as keyof typeof x.a]) {
        if (result === 'throw') throw Error('test effect failure');
        return result === 'promise' ? Promise.resolve() : result === 'number' ? 1 : null;
      }});
      rejects(() => x.r.requestJoint(x.j, 1, 0x9d), result === 'throw' ? 'test effect failure' : 'synchronously');
      const expected = ['j', 'p', 'm', 't', 'r'];
      check(x.events.join() === expected.slice(0, expected.indexOf(fault) + 1).join(), 'bad effect return stops exact prefix');
      x.setHook(() => {}); x.events.length = 0; x.r.requestJoint(x.j, 1, 0x9d);
      check(x.events.join() === expected.join(), 'busy state released after failure');
    }
  }
  for (const request of requests) {
    for (const caught of [false, true]) {
      const x = fixture(); x.setHook(() => {
        for (const nullRequest of requests) x.r[nullRequest](null, NaN, NaN);
        if (caught) {try {x.r[request](x.ids[request], NaN, NaN);} catch { /* poison must persist */ }}
        else x.r[request](x.ids[request], NaN, NaN);
      });
      rejects(() => x.r.requestJoint(x.j, 1, 0x9d), 'reentry');
      check(x.events.join() === 'j', 'null requests no-op, every caught non-null request reentry poisons before more work');
      x.setHook(() => {}); x.r.requestJoint(x.j, 1, 0);
    }
  }
  {
    const x = fixture(); x.setHook(() => {for (const request of requests) x.r[request](null, NaN, NaN);});
    x.r.requestJoint(x.j, 1, 0x9d);
    check(x.events.join() === 'j,p,m,t,r', 'null requests during adapters never poison outer traversal');
  }
  for (const frozenNext of [false, true]) {
    const x = fixture();
    if (frozenNext) Object.defineProperty(x.r.getRObj(x.ro), 'next00', {writable: false});
    x.setHook(() => {try {x.r.requestRObjs(x.ro, 0, 0);} catch { /* effect catches reentry */ }});
    rejects(() => x.r.requestRObjs(x.ro, 1, 0x80), 'reentry was caught inside an adapter');
    check(x.events.join() === 'r', 'effect poison checked before even the final RObj next field, without another external getter');
    x.setHook(() => {});
    const clean = x.r.createRObj({next00: null, aobj18: x.a.r});
    x.r.requestRObjs(clean, 1, 0x80);
    check(x.events.join() === 'r,r', 'terminal RObj effect-reentry failure releases busy state');
  }
  {
    const x = fixture(); let scalarReads = 0;
    const joints = {getBinding: x.s.joints.getBinding, getJoint(id: symbol) {
      scalarReads++; return x.s.joints.getJoint(id);
    }};
    const r = createSourceAnimationRequestRuntime({...x.s, joints}, x.effects);
    x.s.joints.getBinding(x.j).robj80 = r.createRObj({next00: null, aobj18: x.a.r});
    x.setHook(() => {try {r.requestPObjs(x.p, 0, 0);} catch { /* effect catches reentry */ }});
    rejects(() => r.requestJoint(x.j, 1, 0x9d), 'reentry was caught inside an adapter');
    check(scalarReads === 0 && x.events.join() === 'j', 'caught effect reentry aborts before invoking the later getJoint adapter');
    x.setHook(() => {}); x.events.length = 0; r.requestJoint(x.j, 1, 0x9d);
    check(scalarReads === 1 && x.events.join() === 'j,p,m,t,r', 'immediate effect-reentry refusal recovers for a later complete request');
  }
  {
    const x = fixture(), table = {getPObj(id: symbol) {check(this === table, 'getter retains this'); return x.s.pobjs.getPObj(id);}};
    const effect = {requestAObj(id: symbol | null) {
      check(this === effect, 'fixed request receiver'); x.events.push(id === x.a.p ? 'p' : 'other');
      table.getPObj = () => {throw Error('replacement getter');};
      effect.requestAObj = () => {throw Error('replacement request');};
    }};
    const s: SourceAnimationRequestSources = {...x.s, pobjs: table};
    const r = createSourceAnimationRequestRuntime(s, effect);
    s.pobjs = {getPObj() {throw Error('replacement source table');}};
    const tail = x.s.pobjs.createPObj({next04: null, aobj18: x.a.p, classUpdate48: null}); x.s.pobjs.getPObj(x.p).next04 = tail;
    r.requestPObjs(x.p, 1, 8); r.requestPObjs(x.p, 1, 8);
    check(x.events.join() === 'p,p,p,p', 'factory snapshots methods and tables across nodes and calls');
  }
  for (const [tableName, getter, entry] of [['joints', 'getJoint', 'requestJoint'], ['joints', 'getBinding', 'requestJoint'],
    ['dobjs', 'getDObj', 'requestDObjs'], ['pobjs', 'getPObj', 'requestPObjs'], ['mobjs', 'getMObj', 'requestMObj'],
    ['tobjs', 'getBinding', 'requestTObjs']] as const) {
    const x = fixture(); let r: SourceAnimationRequestRuntime, reads = 0;
    const original = (x.s[tableName] as unknown as Record<string, (id: symbol) => unknown>)[getter]!;
    const table = {...x.s[tableName], [getter](id: symbol) {
      check(this === table, `${tableName}.${getter} original this`); reads++;
      try {r.requestPObjs(x.p, 0, 0);} catch { /* caught getter reentry must poison outer pass */ }
      return original(id);
    }};
    r = createSourceAnimationRequestRuntime({...x.s, [tableName]: table}, x.effects);
    rejects(() => r[entry](x.ids[entry], 1, 0x9d), 'reentry');
    check(reads === 1 && x.events.join() === (getter === 'getJoint' ? 'j' : ''),
      'caught getter reentry refuses immediately before fields, next getter or effect');
  }
  for (const [tableName, getter, prefix] of [['joints', 'getJoint', 'j'], ['joints', 'getBinding', ''],
    ['dobjs', 'getDObj', 'j'], ['pobjs', 'getPObj', 'j'], ['mobjs', 'getMObj', 'j,p'],
    ['tobjs', 'getBinding', 'j,p,m']] as const) {
    const x = fixture(); let refuse = true;
    const original = (x.s[tableName] as unknown as Record<string, (id: symbol) => unknown>)[getter]!;
    const table = {...x.s[tableName], [getter](id: symbol) {if (refuse) throw Error('getter refusal'); return original(id);}};
    const r = createSourceAnimationRequestRuntime({...x.s, [tableName]: table}, x.effects);
    x.s.joints.getBinding(x.j).robj80 = r.createRObj({next00: null, aobj18: x.a.r});
    rejects(() => r.requestJoint(x.j, 1, 0x9d), 'getter refusal');
    check(x.events.join() === prefix, 'getter failure retains only earlier completed work');
    refuse = false; x.events.length = 0; r.requestJoint(x.j, 1, 0x9d);
    check(x.events.join() === 'j,p,m,t,r', 'getter failure releases busy state');
  }
  {
    const x = fixture(); let invoked = false;
    const binding = Object.defineProperty({next04: null}, 'aobj18', {get() {invoked = true; return null;}});
    const r = createSourceAnimationRequestRuntime({...x.s, pobjs: {getPObj() {return binding as never;}}}, x.effects);
    rejects(() => r.requestPObjs(x.p, 0, 8), 'own data property'); check(!invoked, 'adapter record accessor never invoked');
    r.requestPObjs(x.p, NaN, 0); // The accessor is entirely unused under mask0.
    for (const value of [null, 7, Promise.resolve()]) {
      const bad = createSourceAnimationRequestRuntime({...x.s, pobjs: {getPObj() {return value as never;}}}, x.effects);
      rejects(() => bad.requestPObjs(x.p, 1, 8), value === null || value === 7 ? 'data record' : 'own data property');
    }
  }
  for (const kind of ['PObj', 'TObj', 'RObj', 'DObj'] as const) {
    for (const defect of ['cycle', 'foreign', 'budget']) {
      const x = fixture(defect === 'budget' ? 1 : 4096);
      const nodes = {
        PObj: {first: x.p, next: 'next04', get: (id: symbol) => x.s.pobjs.getPObj(id),
          add: () => x.s.pobjs.createPObj({next04: null, aobj18: x.a.p, classUpdate48: null}), run: x.r.requestPObjs, mask: 8, event: 'p'},
        TObj: {first: x.t, next: 'next08', get: (id: symbol) => x.s.tobjs.getBinding(id),
          add: () => x.s.tobjs.createTexture(textureHeader(), {next08: null, aobj64: x.a.t, classUpdate48: null}), run: x.r.requestTObjs, mask: 0x10, event: 't'},
        RObj: {first: x.ro, next: 'next00', get: (id: symbol) => x.r.getRObj(id),
          add: () => x.r.createRObj({next00: null, aobj18: x.a.r}), run: x.r.requestRObjs, mask: 0x80, event: 'r'},
        DObj: {first: x.d, next: 'next04', get: (id: symbol) => x.s.dobjs.getDObj(id),
          add: () => x.s.dobjs.createDObj({next04: null, pobj0c: x.p, mobj08: null, aobj10: null, classUpdate44: null}), run: x.r.requestDObjs, mask: 8, event: 'p'},
      };
      const c = nodes[kind], tail = c.add();
      // Keep a deliberately broken cycle guard from making mutation tests hang.
      x.setHook(() => {if (x.events.length > 8) throw Error('test request safety cap');});
      (c.get(c.first) as unknown as Record<string, unknown>)[c.next] = tail;
      (c.get(tail) as unknown as Record<string, unknown>)[c.next] = defect === 'cycle' ? c.first : defect === 'foreign' ? Symbol('foreign') : null;
      rejects(() => c.run(c.first, 1, c.mask), defect === 'cycle' ? 'cycle/revisited' : defect === 'foreign' ? 'non-owned' : 'visit budget');
      check(x.events.join() === (defect === 'budget' ? c.event : `${c.event},${c.event}`), 'list refusal preserves visited prefix');
    }
  }
  {
    const x = fixture(2), second = x.s.dobjs.createDObj({next04: null, pobj0c: x.p, mobj08: x.m, aobj10: null, classUpdate44: null});
    x.s.dobjs.getDObj(x.d).next04 = second; x.r.requestDObjs(x.d, 1, 0x1c);
    check(x.events.join() === 'p,m,t,p,m,t', 'shared PObj/MObj/TObj requests repeat; cycle sets and budgets local to each list call');
  }
  {
    const x = fixture(12001); let last = x.ro;
    for (let i = 0; i < 12000; i++) {const next = x.r.createRObj({next00: null, aobj18: x.a.r}); x.r.getRObj(last).next00 = next; last = next;}
    x.r.requestRObjs(x.ro, 1, 0x80); check(x.events.length === 12001, 'long request list uses iterative traversal');
  }
  {
    const x = fixture(), a = createSourceAObj({flags: AOBJ_STOPPED, frame: 0, rewind: 0, end: 8, rate: 1, fobjs: null});
    let forwarded = NaN;
    const f: SourceAObjEffects = {requestAll(_list, frame) {forwarded = frame;},
      stopAll() {throw Error('unexpected stop');}, interpretAll() {throw Error('unexpected interpret');}};
    const r = createSourceAnimationRequestRuntime(x.s, {requestAObj(id, frame) {
      if (id !== null && id !== x.a.p) throw Error('unsupported AObj');
      requestSourceAObj(id === null ? null : a, frame, f);
    }});
    const wider = 1 + 2 ** -30; r.requestPObjs(x.p, wider, 8);
    check(a.frame === 1 && forwarded === wider && a.flags === AOBJ_REQUEST,
      'actual AObj stores float32 but receives and forwards original wider double');
    x.s.pobjs.getPObj(x.p).aobj18 = null; r.requestPObjs(x.p, NaN, 8);
    check(forwarded === wider, 'actual null AObj bypasses invalid frame');
    x.s.pobjs.getPObj(x.p).aobj18 = x.a.p;
    rejects(() => r.requestPObjs(x.p, NaN, 8), 'finite double');
    check(a.frame === 1 && forwarded === wider, 'actual non-null AObj controls numeric admission');
  }
  console.log('[animation-request] PASS: bounded six-owner request masks, live nested order, null/frame forwarding and fail-closed adapters; synthetic, no original replay or full setup');
}
