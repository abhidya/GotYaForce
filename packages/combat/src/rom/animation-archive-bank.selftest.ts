import {createSourceAnimationArchiveBankRuntime, type SourceAnimationArchiveBankRuntime} from './animation-archive-bank.js';
import {createSourceActorJointMappingRuntime} from './actor-joint-mapping.js';
import {createSourceJObjAnimationRuntime} from './jobj-animation.js';
import {createSourceJointAnimationFeedbackRuntime} from './joint-animation-feedback.js';
import {createSourceAttachedJointSetupRuntime} from './attached-joint-setup.js';
import {createSourceAnimationSetupMetadataRuntime} from './animation-setup-metadata.js';
import {createSourceAnimationDescriptorBankRuntime} from './animation-descriptor-bank.js';
import {createSourceArchiveJointSetupRuntime} from './archive-joint-setup.js';
import {createSourceArchivePublicRuntime} from './archive-public.js';
function check(ok: boolean, why: string): void {if (!ok) throw Error(`[archive-bank-test] ${why}`);}
function rejects(run: () => unknown, expected: string): void {
  let error = ''; try {run();} catch (e) {error = String(e);} check(error.includes(expected), `expected ${expected}, got ${error || 'success'}`);
}
function fixture() {
  const unsupported = (): never => {throw Error('unreachable animation/parsing effect');};
  const joints = createSourceJObjAnimationRuntime(), feedback = createSourceJointAnimationFeedbackRuntime(joints);
  const effects = {interpretAObj: unsupported, animateRObjs: unsupported, animateDObjs: unsupported};
  const mapping = createSourceActorJointMappingRuntime(joints, feedback, effects, {convertEulerToQuaternion: unsupported});
  const part = mapping.createPart({frame0c: 0, duration24: -1, segment2d: 0, complete2e: 0, mode2f: 0, mirror30: 0},
    {descriptor00: null, scaleIndex32: 0, jointBank33: 0, poseBuffer35: 0});
  const attached = createSourceAttachedJointSetupRuntime({joints, feedback, actors: mapping,
    requests: {requestJoint: unsupported}, fobjs: {getFObj: unsupported}}, effects);
  attached.bindPart(part, {rewind26: 0, loop2c: 0});
  const metadata = createSourceAnimationSetupMetadataRuntime({descriptors: createSourceAnimationDescriptorBankRuntime(), actors: mapping, feedback, attached});
  metadata.bindPart(part, {selector2a: 1, selector2b: 0, auxiliary37: 0});
  const publicRuntime = createSourceArchivePublicRuntime(), base = publicRuntime.createBytes(new Uint8Array(1));
  const archive = publicRuntime.createArchive({publicCount0c: 0, data20: base, publicTable28: base, stringTable30: base});
  const archives = createSourceArchiveJointSetupRuntime({archives: publicRuntime,
    attachment: {getDescriptor: unsupported, addAnimation: unsupported}, tail: attached});
  const fallback = archives.createDescriptor({archive0c: archive}), selected = archives.createDescriptor({archive0c: archive});
  archives.bindPart(part, {descriptor04: null});
  const events: string[] = [], hooks: {mapping?: () => void; metadata?: () => void; archive?: () => void; descriptor?: () => void} = {};
  const ma = {getPartBinding(id: symbol) {check(this === ma, 'mapping receiver'); events.push('mapping'); hooks.mapping?.(); return mapping.getPartBinding(id);}};
  const me = {getPartBinding(id: symbol) {check(this === me, 'metadata receiver'); events.push('metadata'); hooks.metadata?.(); return metadata.getPartBinding(id);}};
  const ar = {getPartBinding(id: symbol) {check(this === ar, 'archive receiver'); events.push('part04'); hooks.archive?.(); return archives.getPartBinding(id);},
    getDescriptor(id: symbol) {check(this === ar, 'wrapper receiver'); events.push('wrapper'); hooks.descriptor?.(); return archives.getDescriptor(id);}};
  const runtime = createSourceAnimationArchiveBankRuntime({mapping: ma, metadata: me, archives: ar});
  const fallbackGroup = runtime.createPointerTable([fallback]);
  const group = runtime.createPointerTable([selected, null]);
  const bank = runtime.createPointerTable([fallbackGroup, group, null]);
  const actual = mapping.getPartBinding(part), side = metadata.getPartBinding(part), binding = archives.getPartBinding(part);
  actual.descriptor00 = bank;
  return {runtime, part, fallback, selected, fallbackGroup, group, bank, actual, side, binding, events, hooks, ma, me, ar};
}
export function runAnimationArchiveBankSelfTests(): void {
  {
    const x = fixture(); check(x.runtime.resolveArchive(x.part) === 0 && x.binding.descriptor04 === x.selected, 'selected owned wrapper');
    check(x.events.join() === 'mapping,metadata,metadata,part04,part04,part04,wrapper', 'machine-backed selector once and descriptor reload sequence');
    x.side.selector2a = 0x81; check(x.runtime.resolveArchive(x.part) === 0, 'selector masks high bit');
    x.runtime.getPointerTable(x.group)[0] = x.fallback; x.runtime.resolveArchive(x.part);
    check(x.binding.descriptor04 === x.fallback, 'live cells');
  }
  {
    const x = fixture(); x.actual.descriptor00 = null;
    x.hooks.metadata = x.hooks.archive = () => {throw Error('must not reach');};
    check(x.runtime.resolveArchive(x.part) === -1 && x.binding.descriptor04 === null, 'null bank skips all metadata and descriptor04');
  }
  {
    const x = fixture(); x.side.selector2a = 2; x.side.selector2b = NaN;
    check(x.runtime.resolveArchive(x.part) === 1 && x.binding.descriptor04 === x.fallback, 'missing group ignores selector2b and falls back');
    check(x.events.join() === 'mapping,metadata,part04,part04,wrapper', 'missing group reload sequence');
  }
  {
    const x = fixture(); x.side.selector2b = 1;
    const other = x.runtime.createPointerTable([x.runtime.createPointerTable([x.selected])]);
    let calls = 0; x.hooks.mapping = () => {if (++calls === 2) x.actual.descriptor00 = other;};
    check(x.runtime.resolveArchive(x.part) === 1 && x.binding.descriptor04 === x.selected, 'null selection reloads descriptor00 before fallback');
    check(x.events.join() === 'mapping,metadata,metadata,part04,part04,mapping,part04,part04,wrapper', 'null selected reload sequence');
  }
  {
    const x = fixture(); x.runtime.getPointerTable(x.bank)[1] = x.runtime.pointerAt(x.group, 1); x.side.selector2b = 255;
    check(x.runtime.pointerAt(x.group, 0) === x.group && x.runtime.pointerAt(x.runtime.pointerAt(x.group, 1), -1) === x.group, 'canonical cursor identities');
    check(x.runtime.resolveArchive(x.part) === 0 && x.binding.descriptor04 === x.selected, 'negative signed selector within owned backing');
    x.side.selector2b = 254; rejects(() => x.runtime.resolveArchive(x.part), 'reached table cell');
  }
  {
    const x = fixture(); Object.freeze(x.actual); Object.freeze(x.side); Object.freeze(x.runtime.getPointerTable(x.group));
    check(x.runtime.resolveArchive(x.part) === 0, 'readonly source operands admitted');
  }
  {
    const x = fixture(); const unknown = Symbol('unhydrated'); x.runtime.getPointerTable(x.group)[0] = unknown;
    rejects(() => x.runtime.resolveArchive(x.part), 'unknown/non-owned setup descriptor');
    check(x.binding.descriptor04 === unknown, 'unknown selected wrapper preserves source store before refusal');
  }
  {
    const x = fixture(); x.side.selector2b = 1; x.runtime.getPointerTable(x.bank)[0] = null;
    rejects(() => x.runtime.resolveArchive(x.part), 'unknown/non-owned table cursor');
    check(x.binding.descriptor04 === null, 'selected null store survives fallback dereference fault');
  }
  {
    const x = fixture(); x.binding.descriptor04 = Symbol(); Object.freeze(x.binding);
    rejects(() => x.runtime.resolveArchive(x.part), 'non-writable');
  }
  {
    const x = fixture(); x.ma.getPartBinding = x.me.getPartBinding = x.ar.getPartBinding = () => {throw Error('replacement called');};
    check(x.runtime.resolveArchive(x.part) === 0, 'methods captured');
  }
  {
    const x = fixture(); x.hooks.archive = () => {try {x.runtime.resolveArchive(x.part);} catch { /* caught reentry still poisons */ }};
    rejects(() => x.runtime.resolveArchive(x.part), 'reentry'); check(x.binding.descriptor04 === null, 'reentry stops before store');
    delete x.hooks.archive; check(x.runtime.resolveArchive(x.part) === 0, 'later invocation recovers');
  }
  {
    const x = fixture(), initial = [x.selected]; const table = x.runtime.createPointerTable(Object.freeze(initial));
    check(x.runtime.getPointerTable(table) !== initial && Object.isSealed(x.runtime.getPointerTable(table)), 'copied sealed tables');
    rejects(() => x.runtime.createPointerTable(new Array(4097).fill(null)), 'pointer table length');
    rejects(() => x.runtime.createPointerTable(new Array(1)), 'own data property');
    rejects(() => x.runtime.pointerAt(table, 1), 'table cursor');
    const other: SourceAnimationArchiveBankRuntime = fixture().runtime;
    rejects(() => other.getPointerTable(table), 'unknown/non-owned');
    const empty = x.runtime.createPointerTable([]); x.actual.descriptor00 = empty;
    rejects(() => x.runtime.resolveArchive(x.part), 'reached table cell');
  }
  {
    const x = fixture(); x.side.selector2a = 2; x.runtime.getPointerTable(x.fallbackGroup)[0] = null;
    check(x.runtime.resolveArchive(x.part) === 1 && x.binding.descriptor04 === null, 'null fallback is untagged zero, no fake wrapper');
  }
  {
    const x = fixture(); let reads = 0;
    x.hooks.metadata = () => {if (++reads === 2) x.runtime.getPointerTable(x.bank)[1] = null;};
    check(x.runtime.resolveArchive(x.part) === 0 && x.binding.descriptor04 === x.selected,
      'retains group loaded before signed selector; no invented second group load');
  }
  {
    const x = fixture(); let reads = 0;
    x.hooks.archive = () => {if (++reads === 3) x.binding.descriptor04 = x.fallback;};
    check(x.runtime.resolveArchive(x.part) === 0 && x.binding.descriptor04 === x.fallback,
      'final descriptor04 reload resolves replacement actual wrapper');
  }
  {
    const x = fixture(); let reads = 0;
    x.hooks.archive = () => {if (++reads === 2) x.binding.descriptor04 = null;};
    check(x.runtime.resolveArchive(x.part) === 1 && x.binding.descriptor04 === x.fallback,
      'post-store descriptor04 reread controls null fallback');
  }
  {
    const x = fixture(); x.side.selector2b = 1;
    x.hooks.mapping = () => {if (x.events.filter(e => e === 'mapping').length === 2) x.actual.descriptor00 = null;};
    rejects(() => x.runtime.resolveArchive(x.part), 'unknown/non-owned table cursor');
    check(x.binding.descriptor04 === null, 'null reloaded bank faults after completed selected store');
  }

}
