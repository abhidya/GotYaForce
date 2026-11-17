import {createSourceJObjAnimationRuntime, type SourceJObjAnimationEffects} from './jobj-animation.js';
import {createSourceDObjAnimationRuntime, type SourceDObjAnimationEffects} from './dobj-animation.js';
import {createSourcePObjAnimationRuntime, type SourcePObjAnimationEffects} from './pobj-animation.js';
import {createSourceMObjAnimationRuntime, type SourceMObjAnimationEffects} from './mobj-animation.js';
import {createSourceAObj, interpretSourceAObj, requestSourceAObj} from './aobj-clock.js';
import {createSourceFObjScalarCallbackRuntime} from './fobj-callback.js';
function check(ok: boolean, message: string): void {if (!ok) throw Error(`[display-animation-test] ${message}`);}
export function runDisplayAnimationSelfTest(): void {
  const j = createSourceJObjAnimationRuntime(), d = createSourceDObjAnimationRuntime();
  const p = createSourcePObjAnimationRuntime(), m = createSourceMObjAnimationRuntime();
  const root = j.createJoint({sibling08: null, child10: null, flags14: 0,
    rotation1c: 0, rotation20: 0, rotation24: 0, scale2c: 1, scale30: 1, scale34: 1,
    translation38: 0, translation3c: 0, translation40: 0},
  {parent0c: null, aobj7c: null, robj80: null, dobj18: null, classUpdate50: null});
  const polygon2 = p.createPObj({next04: null, aobj18: null, classUpdate48: null});
  const polygon1 = p.createPObj({next04: polygon2, aobj18: null, classUpdate48: null});
  const material = m.createMObj({tobj08: null, aobj14: null, classUpdate4c: null});
  const display = d.createDObj({next04: null, mobj08: material, pobj0c: polygon1, aobj10: null, classUpdate44: null});
  j.getBinding(root).dobj18 = display;
  const owners = [root, display, polygon1, polygon2, material];
  const names = ['joint', 'display', 'polygon1', 'polygon2', 'material'];
  const rows = owners.map((owner, index) => {
    const f = createSourceFObjScalarCallbackRuntime(owner); let node: symbol | null = null;
    // Only the joint has an implemented scalar receiver. Other real AObjs use
    // empty FObj lists to isolate owner dispatch and shared completion accounting.
    if (owner === root) {
      const data = f.createData(Uint8Array.from([2, 10, 4, 2, 18]));
      node = f.createNode({next00: null, cursor04: data, base08: data, length0c: 5, flags10: 1,
        byte11: 0, byte12: 0, track13: 5, format14: 0x80, format15: 0x80,
        half16: 0, offset18: 0, half1a: 0, frame1c: 0, value20: 0, value24: 0, value28: 0, value2c: 0});
      j.getBinding(root).classUpdate50 = f.createCallback(j.updateScalar);
    }
    const a = createSourceAObj({flags: 0, frame: 0, rewind: 0, end: index+1, rate: 1, fobjs: node});
    const id = Symbol('owned animation');
    if (owner === root) j.getBinding(owner).aobj7c = id;
    else if (owner === display) d.getDObj(owner).aobj10 = id;
    else if (owner === material) m.getMObj(owner).aobj14 = id;
    else p.getPObj(owner).aobj18 = id;
    requestSourceAObj(a, 0, f.effects); return {owner, id, a, f, name: names[index]!};
  });
  const events: string[] = [];
  j.endCallbacks.state.head28 = j.endCallbacks.createNode({next00: null,
    callback04: j.endCallbacks.createCallback(() => {events.push('end');})});
  const interpret = (id: symbol | null, owner: symbol, callback: symbol | null): void => {
    const row = rows.find(x => x.id === id && x.owner === owner);
    if (!row) throw Error('unbound source owner/AObj');
    interpretSourceAObj(row.a, callback, row.f.effects, j.endCallbacks.counts); events.push(row.name);
  };
  const pe: SourcePObjAnimationEffects = {interpretAObj: interpret};
  const me: SourceMObjAnimationEffects = {interpretAObj: interpret,
    animateTObjs(list) {if (list !== null) throw Error('unsupported texture animation'); events.push('textures');}};
  const de: SourceDObjAnimationEffects = {interpretAObj: interpret,
    animatePObjs(list) {p.animateAll(list, pe);}, animateMObj(object) {m.animate(object, me);}};
  const je: SourceJObjAnimationEffects = {interpretAObj: interpret,
    animateRObjs(list) {if (list !== null) throw Error('unsupported RObj');}, animateDObjs(list) {d.animateAll(list, de);}};
  for (let pass = 0; pass < 7; pass++) {
    events.length = 0; j.animateTree(root, je);
    const expected = [[5, 0], [4, 1], [3, 1], [2, 1], [1, 1], [0, 1], [0, 0]][pass]!;
    check(j.endCallbacks.counts.running === expected[0] && j.endCallbacks.counts.stopped === expected[1],
      `actual five-owner shared completion counts at pass ${pass}`);
    const order = 'joint,display,polygon1,polygon2,material,textures';
    check(events.join() === order+(pass === 5 ? ',end' : ''), 'source owner order, texture call and final completion boundary');
  }
  check(rows.map(x => x.a.frame).join() === '1,2,3,4,5' && j.getJoint(root).translation38 === 12,
    'independent AObj completions plus real joint FObj scalar effect');
  for (const gate of [0x20, 0x4000]) {
    rows.forEach(row => requestSourceAObj(row.a, 0, row.f.effects)); events.length = 0;
    j.clearFlags(root, 0xffffffff); j.setFlags(root, gate); j.animateTree(root, je);
    check(events.join() === 'joint' && j.endCallbacks.counts.running === 1 && j.endCallbacks.counts.stopped === 0,
      'JObj display gate excludes the entire polygon/material path and its counts');
  }
  j.clearFlagsAll(root, 0xffffffff);
  rows.forEach(row => requestSourceAObj(row.a, row.a.end, row.f.effects)); events.length = 0;
  m.getMObj(material).tobj08 = Symbol('unsupported texture');
  let error = ''; try {j.animateTree(root, je);} catch (e) {error = String(e);}
  check(error.includes('unsupported texture animation') && j.endCallbacks.counts.stopped === 5 && !events.includes('end'),
    'late required texture refusal preserves five real AObj completions but prevents global callback');
  console.log('[display-animation] PASS: real five-owner AObj/FObj composition across JObj, DObj, PObj and MObj; synthetic, no polygon/material/texture receiver or live integration');
}
