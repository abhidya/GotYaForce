import {createSourceJObjModelHydrationRuntime, type SourceJObjModelHydrationLimits, type SourceJObjModelHydrationRuntime} from './jobj-model-hydration.js';
import {createSourceJObjAnimationRuntime} from './jobj-animation.js';
function check(ok: boolean, why: string): void {if (!ok) throw Error(`[jobj-model-hydration-test] ${why}`);}
function rejects(run: () => unknown, part: string): void {
  let error = ''; try {run();} catch (e) {error = String(e);}
  check(error.includes(part), `expected ${part}, got ${error || 'success'}`);
}
/** Synthetic DAT only: root -> (child -> grandchild), sibling. No original asset. */
function dat(relocations = [8, 0x48, 0x4c]) {
  const dataSize = 0x100, relocStart = 0x20 + dataSize, publicStart = relocStart + relocations.length * 4;
  const stringStart = publicStart + 16, bytes = new Uint8Array(stringStart + 12), view = new DataView(bytes.buffer);
  const word = (at: number, value: number): void => view.setUint32(at, value, false);
  const dataWord = (at: number, value: number): void => word(0x20 + at, value);
  word(0, bytes.length); word(4, dataSize); word(8, relocations.length); word(12, 2);
  dataWord(8, 0x40); dataWord(0x48, 0x80); dataWord(0x4c, 0xc0);
  dataWord(0x84, 0x00040000); dataWord(0xc4, 0x80080000);
  for (let n = 0; n < 4; n++) for (let i = 0; i < 9; i++) view.setFloat32(0x20 + n * 64 + 20 + i * 4, n * 10 + i, false);
  dataWord(20, 0x80000000); dataWord(24, 1); // -0 and smallest positive f32 subnormal.
  relocations.forEach((at, i) => word(relocStart + i * 4, at));
  word(publicStart, 0); word(publicStart + 4, 0); word(publicStart + 8, 0xc0); word(publicStart + 12, 5);
  bytes.set([114, 111, 111, 116, 0, 111, 116, 104, 101, 114, 0, 0], stringStart);
  return {bytes, view, word, dataWord, relocStart, publicStart, stringStart};
}
function owners(limits: SourceJObjModelHydrationLimits = {}) {
  const joints = createSourceJObjAnimationRuntime(), allocated: symbol[] = [];
  const hooks: {create?: () => void} = {};
  const adapter: Pick<typeof joints, 'createJoint' | 'getJoint' | 'getBinding'> = {
    createJoint(initial, binding) {
      check(this === adapter, 'captured factory receiver');
      const id = joints.createJoint(initial, binding); allocated.push(id); hooks.create?.(); return id;
    },
    getJoint: joints.getJoint,
    getBinding(id) {check(this === adapter, 'captured getBinding receiver'); return joints.getBinding(id);},
  };
  const runtime = createSourceJObjModelHydrationRuntime(adapter, limits);
  return {joints, allocated, hooks, adapter, runtime};
}
export function runJObjModelHydrationSelfTest(): void {
  {
    const f = dat(), o = owners(), model = o.runtime.hydrateModelArchive(f.bytes, 0);
    check(model.name === 'root' && model.dataOffset === 0 && model.publicIndex === 0, 'explicit public root metadata');
    check(model.joints.map(p => p.dataOffset).join(',') === '0,64,128,192', 'preorder retains child/sibling order');
    const [r, c, g, s] = model.joints.map(p => p.joint), root = o.joints.getJoint(r!);
    check(model.root === r && root.child10 === c && root.sibling08 === null, 'actual root links');
    check(o.joints.getJoint(c!).child10 === g && o.joints.getJoint(c!).sibling08 === s, 'actual child/sibling links');
    check(o.joints.getBinding(c!).parent0c === r && o.joints.getBinding(g!).parent0c === c && o.joints.getBinding(s!).parent0c === r, 'actual parents');
    check(root.flags14 === 0x30000040 && o.joints.getJoint(c!).flags14 === 0x10000040, 'completed subtree AddChild flags');
    check(o.joints.getJoint(s!).flags14 === 0x80080040, 'unsigned original flags retained');
    check(Object.is(root.rotation1c, -0) && root.rotation20 === 2 ** -149 && root.translation40 === 8, 'bit-faithful finite copies');
    const scalarKeys = ['rotation1c', 'rotation20', 'rotation24', 'scale2c', 'scale30', 'scale34',
      'translation38', 'translation3c', 'translation40'] as const;
    model.joints.forEach((row, nodeIndex) => {
      const header = o.joints.getJoint(row.joint);
      scalarKeys.forEach((key, scalarIndex) => {
        const expected = nodeIndex === 0 && scalarIndex === 0 ? -0 :
          nodeIndex === 0 && scalarIndex === 1 ? 2 ** -149 : nodeIndex * 10 + scalarIndex;
        check(Object.is(header[key], expected), `node ${nodeIndex} exact descriptor transform ${key}`);
      });
    });
    for (const p of model.joints) {
      const b = o.joints.getBinding(p.joint);
      check(b.aobj7c === null && b.robj80 === null && b.dobj18 === null && b.classUpdate50 === null, 'no fabricated resource/callback');
    }
    check(Object.isFrozen(model) && Object.isFrozen(model.joints) && model.joints.every(Object.isFrozen), 'immutable metadata');
    const second = o.runtime.hydrateModelArchive(f.bytes, 1);
    check(second.joints.length === 1 && second.name === 'other' && second.root !== s, 'explicit other public, fresh load identity');
    o.joints.updateScalar(model.root, 5, 7);
    check(root.translation38 === 7, 'actual scalar owner accepts hydrated identity');
  }
  for (const flags of [0x20, 0x4000, 0x4020]) {
    const f = dat(), o = owners(); f.dataWord(0xc4, flags);
    const model = o.runtime.hydrateModelArchive(f.bytes, 1);
    check(o.joints.getJoint(model.root).flags14 === (flags | 0x40), 'null-payload display flags preserved');
    check(o.joints.getBinding(model.root).dobj18 === null, 'display flags do not fabricate DObj');
  }
  const invalid = (mutate: (f: ReturnType<typeof dat>) => void, part: string, relocations?: number[]): void => {
    const f = dat(relocations); mutate(f); const o = owners();
    rejects(() => o.runtime.hydrateModelArchive(f.bytes, 0), part); check(o.allocated.length === 0, 'preflight refuses before allocation');
  };
  invalid(f => f.word(0, 1), 'file size');
  invalid(f => f.word(16, 1), 'external-reference');
  invalid(f => f.word(4, 0xffffffff), 'table extents');
  invalid(f => f.word(f.relocStart, 3), 'unaligned relocation');
  invalid(f => f.word(f.relocStart + 4, 8), 'duplicate relocation');
  invalid(f => f.dataWord(8, 0x100), 'relocation target');
  invalid(f => f.word(f.publicStart + 8, 0x100), 'public target');
  invalid(f => f.word(f.publicStart + 12, 100), 'public name');
  invalid(f => f.bytes.fill(65, f.stringStart), 'unterminated');
  invalid(f => f.dataWord(0, 4), 'unrelocated nonzero');
  invalid(f => f.dataWord(0, 0), 'custom classname', [0, 8, 0x48, 0x4c]);
  invalid(f => f.dataWord(4, 0x1000), 'instance');
  invalid(f => f.dataWord(4, 0x20000), 'quaternion');
  for (const flag of [0, 0x20, 0x4000]) invalid(f => {f.dataWord(4, flag); f.dataWord(16, 0);}, 'DObj', [8, 16, 0x48, 0x4c]);
  invalid(() => {}, 'matrix', [8, 56, 0x48, 0x4c]);
  invalid(() => {}, 'RObj', [8, 60, 0x48, 0x4c]);
  invalid(f => f.dataWord(20, 0x7f800000), 'finite float32');
  invalid(f => f.dataWord(20, 0x7fc00000), 'finite float32');
  invalid(f => f.dataWord(20, 0), 'relocation on descriptor scalar', [8, 20, 0x48, 0x4c]);
  invalid(f => f.dataWord(8, 0x20), 'overlapping');
  invalid(f => f.dataWord(8, 0x41), 'unaligned JObj');
  invalid(f => f.dataWord(8, 0xe0), 'extent');
  invalid(f => f.dataWord(0x48, 0), 'repeated reachable'); // Relocated raw zero is root.
  invalid(f => f.dataWord(0x4c, 0x80), 'repeated reachable');
  invalid(f => f.dataWord(0x8c, 0x40), 'repeated reachable', [8, 0x48, 0x4c, 0x8c]);
  invalid(f => f.dataWord(0xcc, 4), 'unrelocated nonzero');
  {
    const f = dat(), o = owners(); f.dataWord(12, 0xdeadbeef);
    check(o.runtime.hydrateModelArchive(f.bytes, 0).joints.length === 4, 'unrelocated root next source-ignored');
    const relocated = dat([8, 12, 0x48, 0x4c]); relocated.dataWord(12, 0);
    check(o.runtime.hydrateModelArchive(relocated.bytes, 0).joints.length === 4, 'relocated root self-next source-ignored');
    relocated.dataWord(12, 0x100);
    rejects(() => o.runtime.hydrateModelArchive(relocated.bytes, 0), 'relocation target');
  }
  for (const limits of [{maxArchiveBytes: 32}, {maxRelocations: 2}, {maxPublics: 1}, {maxStringBytes: 2}, {maxDescriptors: 3}, {maxDepth: 2}]) {
    const o = owners(limits); rejects(() => o.runtime.hydrateModelArchive(dat().bytes, 0), 'budget');
    check(o.allocated.length === 0, 'budget preflight');
  }
  for (const index of [-1, 0.5, 2, NaN]) rejects(() => owners().runtime.hydrateModelArchive(dat().bytes, index), 'public index');
  {
    const f = dat(), o = owners(); o.hooks.create = () => f.bytes.fill(0);
    check(o.runtime.hydrateModelArchive(f.bytes, 0).joints.length === 4, 'adapter-time input overwrite cannot alter completed preflight plan');
  }
  {
    const o = owners(); o.hooks.create = () => {if (o.allocated.length === 2) throw Error('adapter stops');};
    rejects(() => o.runtime.hydrateModelArchive(dat().bytes, 0), 'adapter stops');
    check(o.allocated.length === 2 && o.joints.getJoint(o.allocated[0]!).child10 === null, 'allocated prefix survives without rollback');
  }
  {
    const o = owners(); o.hooks.create = () => {try {o.runtime.hydrateModelArchive(dat().bytes, 0);} catch { /* deliberately swallowed */ }};
    rejects(() => o.runtime.hydrateModelArchive(dat().bytes, 0), 'reentry caught'); check(o.allocated.length === 1, 'caught reentry poisons outer call');
    delete o.hooks.create; check(o.runtime.hydrateModelArchive(dat().bytes, 0).joints.length === 4, 'runtime reusable after failure');
  }
  {
    const joints = createSourceJObjAnimationRuntime(); let reads = 0;
    const adapter = {createJoint: joints.createJoint, getJoint: joints.getJoint, getBinding: joints.getBinding,
      get unused() {reads++; throw Error('irrelevant getter');}};
    const runtime = createSourceJObjModelHydrationRuntime(adapter);
    adapter.createJoint = () => {throw Error('replaced method');};
    runtime.hydrateModelArchive(dat().bytes, 0); check(reads === 0, 'captured methods, irrelevant getters untouched');
    rejects(() => createSourceJObjModelHydrationRuntime({createJoint: joints.createJoint, getBinding: joints.getBinding, get getJoint(): typeof joints.getJoint {throw Error('getter invoked');}}), 'own data property');
  }
  {
    const o = owners();
    const runtime = createSourceJObjModelHydrationRuntime({getJoint: o.joints.getJoint, getBinding: o.joints.getBinding, createJoint: (() => Promise.resolve(Symbol())) as unknown as typeof o.adapter.createJoint});
    rejects(() => runtime.hydrateModelArchive(dat().bytes, 0), 'synchronously');
    const copied = createSourceJObjModelHydrationRuntime({createJoint: o.joints.createJoint, getBinding: o.joints.getBinding, getJoint: id => ({...o.joints.getJoint(id)})});
    rejects(() => copied.hydrateModelArchive(dat().bytes, 0), 'unstable owned record');
  }
  {
    const o = owners(); let runtime: SourceJObjModelHydrationRuntime;
    const adapter = {createJoint: o.joints.createJoint, getBinding: o.joints.getBinding, getJoint(id: symbol) {
      check(this === adapter, 'captured adapter receiver'); return o.joints.getJoint(id);
    }};
    runtime = createSourceJObjModelHydrationRuntime(adapter);
    runtime.hydrateModelArchive(dat().bytes, 0);
    const f = dat(), subarray = new Uint8Array(f.bytes.length + 6); subarray.set(f.bytes, 3);
    runtime.hydrateModelArchive(subarray.subarray(3, 3 + f.bytes.length), 0);
    rejects(() => runtime.hydrateModelArchive(new Uint8Array(new SharedArrayBuffer(32)), 0), 'non-shared');
  }
  {
    // Deep source graph intentionally exceeds typical JS recursive-call comfort;
    // importer traversal and propagation are iterative and bounded.
    const count = 4096, dataSize = count * 64, relocStart = 32 + dataSize;
    const publicStart = relocStart + (count - 1) * 4, bytes = new Uint8Array(publicStart + 10);
    const view = new DataView(bytes.buffer), word = (at: number, n: number) => view.setUint32(at, n, false);
    word(0, bytes.length); word(4, dataSize); word(8, count - 1); word(12, 1);
    for (let i = 0; i < count - 1; i++) {word(32 + i * 64 + 8, (i + 1) * 64); word(relocStart + i * 4, i * 64 + 8);}
    word(32 + (count - 1) * 64 + 4, 0x00100000);
    bytes[publicStart + 8] = 120;
    const o = owners(), model = o.runtime.hydrateModelArchive(bytes, 0);
    check(model.joints.length === count && o.joints.getJoint(model.root).flags14 === 0x40000040, '4096-deep iterative subtree propagation');
    const limited = owners({maxDepth: count - 1});
    rejects(() => limited.runtime.hydrateModelArchive(bytes, 0), 'depth budget');
    check(limited.allocated.length === 0, 'deep preflight budget before effects');
  }
  {
    const o = owners(); o.hooks.create = () => {
      if (o.allocated.length === 2) o.joints.getJoint(o.allocated[0]!).translation38 = 999;
    };
    rejects(() => o.runtime.hydrateModelArchive(dat().bytes, 0), 'changed during allocation');
    check(o.allocated.length === 4 && o.joints.getJoint(o.allocated[0]!).translation38 === 999, 'earlier adapter writes retained, bad output refused');
    for (const maxDepth of [0, -1, 1.5, Infinity, 0x100000000]) rejects(() => owners({maxDepth}), 'maxDepth');
  }

}
