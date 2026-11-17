import {createSourceJObjAnimationRuntime, type SourceJObjAnimationEffects} from './jobj-animation.js';
import {createSourceDObjAnimationRuntime, type SourceDObjAnimationEffects} from './dobj-animation.js';
import {createSourcePObjAnimationRuntime, type SourcePObjAnimationEffects} from './pobj-animation.js';
import {createSourceMObjAnimationRuntime, type SourceMObjAnimationEffects} from './mobj-animation.js';
import {createSourceTObjAnimationRuntime, type SourceTObjAnimationEffects} from './tobj-animation.js';
import {createSourceAObj, interpretSourceAObj, requestSourceAObj} from './aobj-clock.js';
import {createSourceFObjScalarCallbackRuntime} from './fobj-callback.js';
function check(ok: boolean, message: string): void {if (!ok) throw Error(`[texture-animation-test] ${message}`);}
export function runTextureAnimationSelfTest(): void {
  const j = createSourceJObjAnimationRuntime(), d = createSourceDObjAnimationRuntime();
  const p = createSourcePObjAnimationRuntime(), m = createSourceMObjAnimationRuntime(), t = createSourceTObjAnimationRuntime();
  const root = j.createJoint({sibling08: null, child10: null, flags14: 0,
    rotation1c: 0, rotation20: 0, rotation24: 0, scale2c: 1, scale30: 1, scale34: 1,
    translation38: 0, translation3c: 0, translation40: 0},
  {parent0c: null, aobj7c: null, robj80: null, dobj18: null, classUpdate50: null});
  const texture = () => t.createTexture({flags4c: 0x01234567, rotation18: 0, rotation1c: 0, rotation20: 0,
    scale28: 1, scale2c: 1, translation34: 0, translation38: 0}, {next08: null, aobj64: null, classUpdate48: null});
  const texture1 = texture(), texture2 = texture(); t.getBinding(texture1).next08 = texture2;
  const polygon2 = p.createPObj({next04: null, aobj18: null, classUpdate48: null});
  const polygon1 = p.createPObj({next04: polygon2, aobj18: null, classUpdate48: null});
  const material = m.createMObj({tobj08: texture1, aobj14: null, classUpdate4c: null});
  const display = d.createDObj({next04: null, mobj08: material, pobj0c: polygon1, aobj10: null, classUpdate44: null});
  j.getBinding(root).dobj18 = display;
  const owners = [root, display, polygon1, polygon2, material, texture1, texture2];
  const names = ['joint', 'display', 'polygon1', 'polygon2', 'material', 'texture1', 'texture2'];
  const rows = owners.map((owner, index) => {
    const f = createSourceFObjScalarCallbackRuntime(owner); let node: symbol | null = null;
    // Actual source-packed linear data drives the implemented joint and texture
    // receivers. Unsupported display/polygon/material receivers remain absent.
    if (owner === root || owner === texture1 || owner === texture2) {
      const data = f.createData(Uint8Array.from([2, 10, 4, 2, 18]));
      node = f.createNode({next00: null, cursor04: data, base08: data, length0c: 5, flags10: 1,
        byte11: 0, byte12: 0, track13: owner === root ? 5 : owner === texture1 ? 2 : 8, format14: 0x80, format15: 0x80,
        half16: 0, offset18: 0, half1a: 0, frame1c: 0, value20: 0, value24: 0, value28: 0, value2c: 0});
      const callback = f.createCallback(owner === root ? j.updateScalar : t.updateScalar);
      if (owner === root) j.getBinding(owner).classUpdate50 = callback; else t.getBinding(owner).classUpdate48 = callback;
    }
    const a = createSourceAObj({flags: 0, frame: 0, rewind: 0, end: index+1, rate: 1, fobjs: node});
    const id = Symbol('owned animation');
    if (owner === root) j.getBinding(owner).aobj7c = id;
    else if (owner === display) d.getDObj(owner).aobj10 = id;
    else if (owner === material) m.getMObj(owner).aobj14 = id;
    else if (owner === texture1 || owner === texture2) t.getBinding(owner).aobj64 = id;
    else p.getPObj(owner).aobj18 = id;
    requestSourceAObj(a, 0, f.effects); return {owner, id, a, f, node, name: names[index]!};
  });
  const events: string[] = [];
  j.endCallbacks.state.head28 = j.endCallbacks.createNode({next00: null,
    callback04: j.endCallbacks.createCallback(() => {events.push('end');})});
  const interpret = (id: symbol | null, owner: symbol, callback: symbol | null): void => {
    const row = rows.find(x => x.id === id && x.owner === owner);
    if (!row) throw Error('unbound source owner/AObj');
    interpretSourceAObj(row.a, callback, row.f.effects, j.endCallbacks.counts); events.push(row.name);
  };
  const te: SourceTObjAnimationEffects = {interpretAObj: interpret};
  const pe: SourcePObjAnimationEffects = {interpretAObj: interpret};
  const me: SourceMObjAnimationEffects = {interpretAObj: interpret, animateTObjs(list) {t.animateAll(list, te);}};
  const de: SourceDObjAnimationEffects = {interpretAObj: interpret,
    animatePObjs(list) {p.animateAll(list, pe);}, animateMObj(object) {m.animate(object, me);}};
  const je: SourceJObjAnimationEffects = {interpretAObj: interpret,
    animateRObjs(list) {if (list !== null) throw Error('unsupported RObj');}, animateDObjs(list) {d.animateAll(list, de);}};
  for (let pass = 0; pass < 9; pass++) {
    events.length = 0; j.animateTree(root, je);
    const expectedRunning = Math.max(0, 7-pass), expectedStopped = pass >= 1 && pass <= 7 ? 1 : 0;
    check(j.endCallbacks.counts.running === expectedRunning && j.endCallbacks.counts.stopped === expectedStopped,
      `actual seven-owner shared completion counts at pass ${pass}`);
    const order = 'joint,display,polygon1,polygon2,material,texture1,texture2';
    check(events.join() === order+(pass === 7 ? ',end' : ''), 'source owner order and completion after final texture AObj');
  }
  check(rows.map(x => x.a.frame).join() === '1,2,3,4,5,6,7' && j.getJoint(root).translation38 === 12 &&
    t.getTexture(texture1).translation34 === 22 && t.getTexture(texture2).rotation20 === 24,
  'real scalar receivers preserve independent linear extrapolation and completion frames');
  check(t.getTexture(texture1).flags4c === 0x81234567 && t.getTexture(texture2).flags4c === 0x81234567,
    'texture scalar callbacks mark dirty while preserving all other flag bits');
  for (const gate of [0x20, 0x4000]) {
    rows.forEach(row => requestSourceAObj(row.a, 0, row.f.effects)); events.length = 0;
    j.getJoint(root).flags14 = gate; j.animateTree(root, je);
    check(events.join() === 'joint' && j.endCallbacks.counts.running === 1 && j.endCallbacks.counts.stopped === 0,
      'display gates exclude texture animations and their counts as part of the nested path');
  }
  j.getJoint(root).flags14 = 0;
  rows.forEach(row => requestSourceAObj(row.a, row.a.end, row.f.effects)); events.length = 0;
  t.getTexture(texture1).translation34 = -5; t.getTexture(texture2).rotation20 = -7;
  const last = rows[6]!; last.f.getNode(last.node!).track13 = 1; // Unsupported image-table receiver.
  let error = ''; try {j.animateTree(root, je);} catch (e) {error = String(e);}
  check(error.includes('unsupported') && j.endCallbacks.counts.stopped === 6 && !events.includes('end') &&
    t.getTexture(texture1).translation34 === 22 && t.getTexture(texture2).rotation20 === -7,
  'unsupported late receiver retains six completed AObjs and earlier texture writes, without global completion');
  last.f.getNode(last.node!).track13 = 8;
  rows.forEach(row => requestSourceAObj(row.a, row.a.end, row.f.effects)); events.length = 0;
  t.getTexture(texture2).rotation20 = -9;
  Object.defineProperty(t.getTexture(texture2), 'flags4c', {writable: false});
  error = ''; try {j.animateTree(root, je);} catch (e) {error = String(e);}
  check(error.includes('flags4c: non-writable') && t.getTexture(texture2).rotation20 === 24 &&
    j.endCallbacks.counts.stopped === 6 && !events.includes('end'),
  'dirty-flag refusal retains completed texture scalar store and preceding counts but not failing AObj count or completion');
  console.log('[texture-animation] PASS: real seven-owner animation composition and packed FObj texture transforms; synthetic, no image/palette/color receiver, texture upload or original replay');
}
