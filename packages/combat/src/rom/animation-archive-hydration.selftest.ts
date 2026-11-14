import {createSourceAnimationArchiveHydrationRuntime, type SourceAnimationArchiveHydrationLimits, type SourceAnimationArchiveHydrationRuntime} from './animation-archive-hydration.js';
import {createSourceArchivePublicRuntime} from './archive-public.js';
import {createSourceArchiveJointSetupRuntime} from './archive-joint-setup.js';
import {createSourceFObjRuntime} from './fobj-list.js';
import {createSourceFObjDescriptorRuntime} from './fobj-descriptor.js';
import {createSourceAllocatedAObjDescriptorRuntime} from './allocated-aobj-descriptor.js';
import {createSourceJObjAddAnimationRuntime} from './jobj-add-animation.js';
import {createSourceJObjAnimationRuntime} from './jobj-animation.js';
import {createSourceJointAnimationFeedbackRuntime} from './joint-animation-feedback.js';
import {createSourceAObjLifecycleRuntime} from './aobj-lifecycle.js';
import {createSourceJObjTrackOrderRuntime} from './jobj-track-order.js';
function check(ok: boolean, why: string): void {if (!ok) throw Error(`[animation-archive-hydration-test] ${why}`);}
function rejects(run: () => unknown, part: string): void {
  let error = ''; try {run();} catch (e) {error = String(e);}
  check(error.includes(part), `expected ${part}, got ${error || 'success'}`);
}
/** Synthetic bare DAT bytes, not an original asset or a production-provenance
 * substitute. Two leaf roots share an AObj, two FObjs share a packed pointer
 * but have different declared lengths, and two publics alias the first root. */
function dat() {
  const dataSize = 0x70, relocations = [8, 0x1c, 0x30, 0x38, 0x48, 0x5c];
  const relocStart = 0x20 + dataSize, publicStart = relocStart + relocations.length * 4, stringStart = publicStart + 3 * 8;
  const bytes = new Uint8Array(stringStart + 14), view = new DataView(bytes.buffer);
  const word = (at: number, value: number) => view.setUint32(at, value, false);
  const dataWord = (at: number, value: number) => word(0x20 + at, value);
  word(0, bytes.length); word(4, dataSize); word(8, relocations.length); word(12, 3);
  word(0x14, 0x76303031); word(0x18, 0xaabbccdd); word(0x1c, 0x01020304); // Uninterpreted header words.
  dataWord(8, 0x28); dataWord(0x10, 1); dataWord(0x1c, 0x28);
  dataWord(0x28, 0x40000000); view.setFloat32(0x20 + 0x2c, 20, false); dataWord(0x30, 0x38);
  dataWord(0x38, 0x4c); dataWord(0x3c, 6); view.setFloat32(0x20 + 0x40, -0, false);
  bytes[0x20 + 0x44] = 5; bytes[0x20 + 0x47] = 0xab; dataWord(0x48, 0x60);
  dataWord(0x50, 1); bytes[0x20 + 0x58] = 6; dataWord(0x5c, 0x60);
  bytes.set([1, 0, 0, 0x40, 0x41, 5], 0x20 + 0x60); // op1, LE float32 12, wait5.
  relocations.forEach((slot, i) => word(relocStart + i * 4, slot));
  word(publicStart, 0); word(publicStart + 4, 0);
  word(publicStart + 8, 0); word(publicStart + 12, 4);
  word(publicStart + 16, 0x14); word(publicStart + 20, 10);
  bytes.set([111, 110, 101, 0, 97, 108, 105, 97, 115, 0, 116, 119, 111, 0], stringStart);
  return {bytes, view, word, dataWord, relocStart, publicStart, stringStart};
}
function owners(limits: SourceAnimationArchiveHydrationLimits = {}) {
  const archives = createSourceArchivePublicRuntime(), joints = createSourceJObjAnimationRuntime();
  const feedback = createSourceJointAnimationFeedbackRuntime(joints);
  const fobjs = createSourceFObjRuntime(() => {throw Error('unexpected interpreter');});
  const fobjDescs = createSourceFObjDescriptorRuntime(fobjs);
  const aobjDescs = createSourceAllocatedAObjDescriptorRuntime({feedback, fobjs: fobjDescs, removal: fobjs});
  const life = createSourceAObjLifecycleRuntime({feedback, fobjs, descriptors: aobjDescs});
  const order = createSourceJObjTrackOrderRuntime({joints, feedback, fobjs: {getFObj(_aobj, node) {return fobjs.getNode(node);}}});
  const attachment = createSourceJObjAddAnimationRuntime({joints, lifecycle: life, order});
  const setup = createSourceArchiveJointSetupRuntime({archives, attachment, tail: {
    continueAttachedSetupTail() {throw Error('unreached tail: importer only binds real owned descriptors');},
  }});
  const joint = joints.createJoint({sibling08: null, child10: null, flags14: 0,
    rotation1c: 0, rotation20: 0, rotation24: 0, scale2c: 1, scale30: 1, scale34: 1,
    translation38: 0, translation3c: 0, translation40: 0},
  {parent0c: null, aobj7c: null, robj80: null, dobj18: null, classUpdate50: null});
  const events: string[] = [];
  const hooks: {archive?: (bytes: Uint8Array) => unknown; data?: () => unknown; fobj?: () => unknown; bind?: () => unknown} = {};
  const archiveAdapter = {
    createBytes(bytes: Uint8Array) {check(this === archiveAdapter, 'archive receiver captured'); events.push('bytes');
      const result = archives.createBytes(bytes); const override = hooks.archive?.(bytes); return override === undefined ? result : override as symbol;},
    createArchive: archives.createArchive, cursorAt: archives.cursorAt,
  };
  const dataAdapter = {createData(bytes: Uint8Array) {check(this === dataAdapter, 'data receiver captured'); events.push('data');
    const result = fobjs.createData(bytes); hooks.data?.(); return result;}};
  const fobjAdapter = {createDescriptor: ((initial) => {events.push('fobj'); const result = fobjDescs.createDescriptor(initial); hooks.fobj?.(); return result;}) as typeof fobjDescs.createDescriptor};
  const setupAdapter = {createDescriptor: setup.createDescriptor,
    bindAddress(base: symbol, address: symbol, descriptor: symbol) {check(this === setupAdapter, 'setup receiver captured');
      events.push('bind'); setup.bindAddress(base, address, descriptor); return hooks.bind?.() as void;}};
  const sources = {archives: archiveAdapter, fobjData: dataAdapter, fobjs: fobjAdapter, aobjs: aobjDescs, joints: attachment, setup: setupAdapter};
  const runtime = createSourceAnimationArchiveHydrationRuntime(sources, limits);
  return {runtime, archives, joints, feedback, fobjs, fobjDescs, aobjDescs, attachment, setup, joint, events, hooks,
    sources, archiveAdapter, dataAdapter, setupAdapter};
}
export function runAnimationArchiveHydrationSelfTest(): void {
  {const x = owners(), d = dat(), result = x.runtime.hydrateAnimationArchive(d.bytes, [0, 1, 2]);
    check(Object.isFrozen(result) && Object.isFrozen(result.roots) && Object.isFrozen(result.roots[0]), 'frozen import report');
    check(result.roots.length === 3 && result.aobjDescriptors.length === 1 && result.fobjDescriptors.length === 2 && result.packedData.length === 1, 'actual counts and exact aliases');
    const [first, alias, other] = result.roots;
    check(first!.descriptor === alias!.descriptor && first!.address === alias!.address && first!.descriptor !== other!.descriptor, 'public offset0 and distinct roots retain identity');
    check(x.attachment.getDescriptor(first!.descriptor).aobj08 === x.attachment.getDescriptor(other!.descriptor).aobj08, 'shared AObj descriptor');
    check(x.setup.getDescriptor(result.setupDescriptor).archive0c === result.archive, 'actual setup wrapper owns actual archive');
    check(x.aobjDescs.getDescriptor(result.aobjDescriptors[0]!.descriptor).flags00 === 0x40000000 &&
      x.attachment.getDescriptor(first!.descriptor).flags10 === 1, 'AObj and AnimJoint descriptor flags preserved exactly');
    const archive = x.archives.getArchive(result.archive);
    check(archive.publicCount0c === 3 && x.archives.cursorOffset(result.byteBase, archive.data20!) === 0x20 &&
      x.archives.cursorOffset(result.byteBase, archive.publicTable28!) === d.publicStart &&
      x.archives.cursorOffset(result.byteBase, archive.stringTable30!) === d.stringStart &&
      x.archives.cursorOffset(result.byteBase, x.archives.getPublicName(result.archive, 2)!) === d.stringStart + 10,
      'actual archive layout and public names use original DAT offsets');
    const desc = result.fobjDescriptors.find(p => p.dataOffset === 0x38)!, tail = result.fobjDescriptors.find(p => p.dataOffset === 0x4c)!;
    const head = x.fobjDescs.getDescriptor(desc.descriptor), end = x.fobjDescs.getDescriptor(tail.descriptor);
    check(head.next00 === tail.descriptor && head.data10 === end.data10 && head.length04 === 6 && end.length04 === 1, 'actual FObj links/base alias and individual declared lengths');
    check(Object.is(head.start08, -0), 'finite float32 minus zero preserved until loader');
    d.bytes.fill(0);
    check(x.archives.getPublicAddress(result.archive, x.archives.getPublicName(result.archive, 0)) === first!.address, 'copied original header/table bytes');
    x.attachment.addAnimation(x.joint, first!.descriptor);
    const aobj = x.feedback.getAObj(x.joints.getBinding(x.joint).aobj7c!), node = x.fobjs.getNode(aobj.fobjs!);
    check(aobj.end === 20 && aobj.flags === 0x40000000 && node.base08 === result.packedData[0]!.data, 'real AObj/FObj loading from imported descriptors');
    check(Object.is(node.offset18, 0), 'actual loader converts negative zero to positive offset');
    node.cursor04 = node.base08; node.flags10 = 1;
    check(x.fobjs.loadData(node) === 3 && node.value24 === 12 && x.fobjs.cursorOffset(node.base08!, node.cursor04!) === 5, 'original packed bytes decode in actual owner');
    check(x.fobjs.loadWait(node) === 2 && node.half1a === 5, 'actual packed wait reader');
    const shorter = x.fobjs.getNode(node.next00!); shorter.cursor04 = shorter.base08; shorter.flags10 = 1;
    rejects(() => x.fobjs.loadData(shorter), 'truncated stream');
    check(x.fobjs.cursorOffset(shorter.base08!, shorter.cursor04!) === 1, 'shared backing does not bypass shorter declared length');
  }
  // Distinct AObjs can share a descriptor suffix while allocation still creates
  // independent runtime FObj lists for their actual owner lifetimes.
  {const x = owners(), d = dat(), bytes = new Uint8Array(d.bytes.length + 20), v = new DataView(bytes.buffer);
    bytes.set(d.bytes.subarray(0, d.relocStart));
    bytes.set(d.bytes.subarray(d.relocStart, d.publicStart), d.relocStart + 16);
    bytes.set(d.bytes.subarray(d.publicStart), d.publicStart + 20);
    v.setUint32(0, bytes.length); v.setUint32(4, 0x80); v.setUint32(8, 7);
    v.setUint32(0x20 + 0x1c, 0x70); v.setFloat32(0x20 + 0x74, 7);
    v.setUint32(0x20 + 0x78, 0x4c); v.setUint32(d.publicStart + 16, 0x78);
    const r = x.runtime.hydrateAnimationArchive(bytes, [0, 2]);
    const first = x.attachment.getDescriptor(r.roots[0]!.descriptor).aobj08!, other = x.attachment.getDescriptor(r.roots[1]!.descriptor).aobj08!;
    const head = x.aobjDescs.getDescriptor(first).fobj08!, suffix = x.aobjDescs.getDescriptor(other).fobj08!;
    check(first !== other && x.fobjDescs.getDescriptor(head).next00 === suffix &&
      r.aobjDescriptors.length === 2 && r.fobjDescriptors.length === 2 && r.packedData.length === 1,
      'distinct AObjs retain one shared descriptor suffix and packed data base');
    x.attachment.addAnimation(x.joint, r.roots[0]!.descriptor);
    const oldId = x.joints.getBinding(x.joint).aobj7c!, oldNode = x.feedback.getAObj(oldId).fobjs!;
    x.attachment.addAnimation(x.joint, r.roots[1]!.descriptor);
    const current = x.feedback.getAObj(x.joints.getBinding(x.joint).aobj7c!), node = x.fobjs.getNode(current.fobjs!);
    check(current.end === 7 && current.fobjs !== oldNode && node.track13 === 6 && node.next00 === null &&
      node.base08 === r.packedData[0]!.data, 'shared descriptors allocate distinct actual replacement FObjs');
    rejects(() => x.feedback.getAObj(oldId), 'unknown/non-owned');
  }
  {const x = owners(), d = dat(); x.hooks.archive = bytes => {bytes.fill(0xff);};
    const result = x.runtime.hydrateAnimationArchive(d.bytes, [0]);
    x.attachment.addAnimation(x.joint, result.roots[0]!.descriptor);
    const node = x.fobjs.getNode(x.feedback.getAObj(x.joints.getBinding(x.joint).aobj7c!).fobjs!);
    node.cursor04 = node.base08; node.flags10 = 1; x.fobjs.loadData(node);
    check(node.value24 === 12 && x.archives.getPublicName(result.archive, 0) !== null, 'mutating factory argument cannot corrupt private preflight bytes');
  }
  {const x = owners(), d = dat(); d.word(d.publicStart + 20, 0); // root2 is shadowed by root0 name.
    rejects(() => x.runtime.hydrateAnimationArchive(d.bytes, [2]), 'first-match'); check(x.events.length === 0, 'shadowed selected target preflight');
    const r = x.runtime.hydrateAnimationArchive(d.bytes, [0, 2]);
    check(x.archives.getPublicAddress(r.archive, x.archives.getPublicName(r.archive, 2)) === r.roots[0]!.address, 'original duplicate name first match survives hydration');
  }
  {const x = owners(), d = dat(); d.bytes[d.stringStart] = 0xff; d.bytes[d.stringStart + 10] = 0xfe;
    const r = x.runtime.hydrateAnimationArchive(d.bytes, [2]);
    check(r.roots[0]!.name.charCodeAt(0) === 0xfe, 'different high-byte names do not collapse through replacement Unicode');
    check(x.archives.getPublicAddress(r.archive, x.archives.getPublicName(r.archive, 2)) === r.roots[0]!.address, 'raw name comparison uses original bytes');
  }
  // Relocated raw zero is a valid AObj address, not null. Offset0 AObj is empty;
  // a different public points to the leaf root at20. No magic root inference.
  {const x = owners(), bytes = new Uint8Array(0x20 + 0x40 + 4 + 8 + 2), v = new DataView(bytes.buffer);
    v.setUint32(0, bytes.length); v.setUint32(4, 0x40); v.setUint32(8, 1); v.setUint32(12, 1);
    v.setFloat32(0x24, 7); v.setUint32(0x60, 0x28); v.setUint32(0x64, 0x20); bytes.set([97, 0], 0x6c);
    const r = x.runtime.hydrateAnimationArchive(bytes, [0]);
    const a = x.attachment.getDescriptor(r.roots[0]!.descriptor).aobj08;
    check(a !== null && r.aobjDescriptors[0]!.dataOffset === 0 && x.aobjDescs.getDescriptor(a!).end04 === 7, 'relocated offset zero is actual AObj owner');
    v.setUint32(0x60, 0x24); // Unrelated relocation on null next becomes non-null child/next.
    rejects(() => x.runtime.hydrateAnimationArchive(bytes, [0]), 'child/next');
  }
  const malformed: [string, (d: ReturnType<typeof dat>) => void][] = [
    ['file size', d => d.word(0, d.bytes.length + 1)],
    ['table extents', d => d.word(4, 0xffffffff)],
    ['external-reference', d => d.word(16, 1)],
    ['relocation budget', d => d.word(8, 0xffffffff)],
    ['public entry budget', d => d.word(12, 0xffffffff)],
    ['unaligned relocation', d => d.word(d.relocStart, 9)],
    ['relocation slot: data extent', d => d.word(d.relocStart, 0x70)],
    ['duplicate relocation', d => d.word(d.relocStart + 4, 8)],
    ['relocation target', d => d.dataWord(8, 0x70)],
    ['public target', d => d.word(d.publicStart, 0x70)],
    ['name offset', d => d.word(d.publicStart + 4, 0xffffffff)],
    ['unterminated', d => d.bytes[d.bytes.length - 1] = 65],
    ['unrelocated nonzero', d => d.dataWord(0, 0x14)],
    ['child/next', d => {d.word(d.relocStart + 4, 0); d.dataWord(0, 0);}],
    ['RObj', d => {d.word(d.relocStart + 4, 12); d.dataWord(12, 0);}],
    ['joint reference', d => {d.word(d.relocStart + 4, 0x34); d.dataWord(0x34, 0);}],
    ['finite float32', d => d.view.setFloat32(0x20 + 0x2c, Infinity)],
    ['finite float32', d => d.view.setFloat32(0x20 + 0x40, NaN)],
    ['type conflict', d => d.dataWord(8, 0)],
    ['unaligned descriptor', d => d.dataWord(8, 0x29)],
    ['overlapping descriptor', d => d.dataWord(8, 4)],
    ['relocation on descriptor scalar', d => {d.word(d.relocStart + 4, 0x10); d.dataWord(0x10, 0);}],
    ['FObj descriptor cycle', d => d.dataWord(0x38, 0x38)],
    ['FObj descriptor cycle', d => {d.word(d.relocStart + 4, 0x4c); d.dataWord(0x4c, 0x38);}],
    ['packed data: data extent', d => d.dataWord(0x3c, 0xffffffff)],
    ['null packed data', d => {d.word(d.relocStart + 4, 0x68); d.word(d.relocStart + 4 * 4, 0x6c); d.dataWord(0x48, 0);}],
    ['packed data overlaps descriptor', d => d.dataWord(0x48, 0x44)],
    ['relocation overlaps packed data', d => {d.word(d.relocStart + 4, 0x60); d.dataWord(0x60, 0);}],
  ];
  for (const [error, mutate] of malformed) {const x = owners(), d = dat(); mutate(d);
    rejects(() => x.runtime.hydrateAnimationArchive(d.bytes, [0]), error);
    check(x.events.length === 0, `no owner effects before ${error} refusal`);
  }
  for (const [limits, error] of [
    [{maxArchiveBytes: 32}, 'archive byte budget'], [{maxRelocations: 5}, 'relocation budget'],
    [{maxPublics: 2}, 'public entry budget'], [{maxDescriptors: 3}, 'descriptor budget'],
    [{maxStringBytes: 3}, 'string byte budget'], [{maxPackedBytes: 5}, 'aggregate packed byte budget'],
  ] as const) {const x = owners(limits); rejects(() => x.runtime.hydrateAnimationArchive(dat().bytes, [0]), error); check(x.events.length === 0, `${error} before owner effects`);}
  for (const indices of [[], [3], [0, 0], [-1], [NaN], [0x100000000], new Array<number>(1)]) {
    const x = owners(); rejects(() => x.runtime.hydrateAnimationArchive(dat().bytes, indices), 'animation-archive-hydration'); check(x.events.length === 0, 'invalid selection has no owner effects');
  }
  {const x = owners(); let getter = false; const indices = [0]; Object.defineProperty(indices, '0', {get() {getter = true; return 0;}});
    rejects(() => x.runtime.hydrateAnimationArchive(dat().bytes, indices), 'own data'); check(!getter && x.events.length === 0, 'selection accessor never invoked');
    rejects(() => x.runtime.hydrateAnimationArchive(dat().bytes, {} as number[]), 'public-index array');
    rejects(() => x.runtime.hydrateAnimationArchive(new Uint8Array(10), [0]), 'truncated DAT header');
    rejects(() => x.runtime.hydrateAnimationArchive(new Proxy(dat().bytes, {}), [0]), 'Uint8Array');
    rejects(() => x.runtime.hydrateAnimationArchive(new Uint16Array(5) as unknown as Uint8Array, [0]), 'Uint8Array');
    if (typeof SharedArrayBuffer !== 'undefined') rejects(() => x.runtime.hydrateAnimationArchive(new Uint8Array(new SharedArrayBuffer(100)), [0]), 'non-shared');
    if (typeof structuredClone === 'function') {const detached = dat().bytes; structuredClone(detached, {transfer: [detached.buffer]});
      rejects(() => x.runtime.hydrateAnimationArchive(detached, [0]), 'detached');}
    check(x.events.length === 0, 'invalid byte sources have no owner effects');
  }
  {const x = owners(), d = dat(); let fired = false;
    const indices = new Proxy([0], {getOwnPropertyDescriptor(target, key) {if (!fired) {fired = true;
      rejects(() => x.runtime.hydrateAnimationArchive(d.bytes, [0]), 'reentry');} return Object.getOwnPropertyDescriptor(target, key);}});
    rejects(() => x.runtime.hydrateAnimationArchive(d.bytes, indices), 'reentry caught'); check(x.events.length === 0, 'caught input reentry poisons preflight');
    check(x.runtime.hydrateAnimationArchive(d.bytes, [0]).roots.length === 1, 'runtime recovers after refused import');
  }
  {const x = owners(), d = dat(); x.hooks.data = () => {rejects(() => x.runtime.hydrateAnimationArchive(d.bytes, [0]), 'reentry');};
    rejects(() => x.runtime.hydrateAnimationArchive(d.bytes, [0]), 'reentry caught');
    check(x.events.join() === 'bytes,data', 'caught factory reentry stops before descriptor effects');
  }
  {const x = owners(); x.hooks.archive = () => Promise.resolve(Symbol());
    rejects(() => x.runtime.hydrateAnimationArchive(dat().bytes, [0]), 'synchronously return'); check(x.events.join() === 'bytes', 'async factory return rejected before next owner');
  }
  {const x = owners(); x.hooks.bind = () => Promise.resolve();
    rejects(() => x.runtime.hydrateAnimationArchive(dat().bytes, [0]), 'synchronously return void'); check(x.events.includes('fobj'), 'bind refusal retains earlier real descriptor work');
  }
  {const x = owners(); x.archiveAdapter.createBytes = () => {throw Error('replacement method must not execute');};
    x.dataAdapter.createData = () => {throw Error('replacement method must not execute');};
    x.setupAdapter.bindAddress = () => {throw Error('replacement method must not execute');};
    check(x.runtime.hydrateAnimationArchive(dat().bytes, [0]).roots.length === 1, 'methods captured with receivers');
  }
  {const x = owners(), d = dat(); d.view.setFloat32(0x20 + 0x40, 1.5);
    const r = x.runtime.hydrateAnimationArchive(d.bytes, [0]);
    rejects(() => x.attachment.addAnimation(x.joint, r.roots[0]!.descriptor), 'integral signed16');
    check(r.fobjDescriptors.length === 2, 'finite fractional start belongs to later actual loader refusal');
  }
  // Distinct overlapping packed starts are separate immutable host bases, capped
  // by aggregate copies, never falsely represented as aliased retail RAM.
  {const x = owners(), d = dat(); d.dataWord(0x5c, 0x61); d.dataWord(0x50, 5);
    const r = x.runtime.hydrateAnimationArchive(d.bytes, [0]);
    check(r.packedData.length === 2 && r.packedData[0]!.data !== r.packedData[1]!.data, 'distinct starts use explicit independent host backings');
    const bounded = owners({maxPackedBytes: 10}); rejects(() => bounded.runtime.hydrateAnimationArchive(d.bytes, [0]), 'aggregate packed byte budget');
    check(bounded.events.length === 0, 'overlapping spans cannot multiply memory past budget');
  }
  {const x = owners(); const limited = {maxPackedBytes: 0}; rejects(() => createSourceAnimationArchiveHydrationRuntime(x.sources, limited), 'maxPackedBytes');
    rejects(() => createSourceAnimationArchiveHydrationRuntime(x.sources, {maxArchiveBytes: 0xffffffff}), 'maxArchiveBytes');
    const bad = {...x.sources, archives: {get createBytes(): never {throw Error('not invoked');}, cursorAt: x.archives.cursorAt, createArchive: x.archives.createArchive}};
    rejects(() => createSourceAnimationArchiveHydrationRuntime(bad), 'own data');
  }
  // Typed view boundaries, rather than its surrounding ArrayBuffer, are imported.
  {const x = owners(), d = dat(), whole = new Uint8Array(d.bytes.length + 10); whole.set(d.bytes, 5);
    const runtime: SourceAnimationArchiveHydrationRuntime = x.runtime;
    check(runtime.hydrateAnimationArchive(whole.subarray(5, -5), Object.freeze([0])).roots.length === 1, 'bounded typed subarray and readonly indices accepted');
  }
}
