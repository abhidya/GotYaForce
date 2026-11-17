import {createSourceDObjAnimationRuntime} from './dobj-animation.js';
import {createSourceDisplayAnimationAttachmentRuntime, type SourceDisplayAnimationAttachmentRuntime} from './display-animation-attachment.js';
function check(ok: boolean, why: string): void {if (!ok) throw Error(`[display-animation-attachment-test] ${why}`);}
function rejects(fn: () => unknown, text: string): void {
  let error = ''; try {fn();} catch (e) {error = String(e);}
  check(error.includes(text), `expected ${text}, got ${error || 'success'}`);
}
function fixture() {
  const dobjs = createSourceDObjAnimationRuntime();
  const initial = () => ({next04: null, pobj0c: Symbol('opaque foreign PObj'), mobj08: Symbol('opaque foreign MObj'), aobj10: Symbol('existing AObj'), classUpdate44: Symbol('existing callback')});
  const last = dobjs.createDObj(initial()), first = dobjs.createDObj({...initial(), next04: last});
  const visits: symbol[] = [];
  const owner = {getDObj(id: symbol) {check(this === owner, 'captured receiver'); visits.push(id); return dobjs.getDObj(id);}};
  const runtime = createSourceDisplayAnimationAttachmentRuntime(owner);
  return {dobjs, first, last, visits, owner, runtime};
}
export function runDisplayAnimationAttachmentSelfTest(): void {
  {const x = fixture(), a = x.dobjs.getDObj(x.first), b = x.dobjs.getDObj(x.last);
    const before = [Object.getOwnPropertyDescriptors(a), Object.getOwnPropertyDescriptors(b)];
    x.runtime.attachNullDescriptors(x.first);
    check(x.visits.length === 2 && x.visits[0] === x.first && x.visits[1] === x.last, 'source next traversal');
    for (const [i, record] of [a, b].entries()) for (const key of Object.keys(record)) {
      check(Object.getOwnPropertyDescriptor(record, key)?.value === before[i]![key]!.value, `preserved ${key}`);
    }
    check(Object.isFrozen(x.runtime), 'frozen API');
    x.visits.length = 0; x.runtime.attachNullDescriptors(null); check(x.visits.length === 0, 'null bypass');
    Object.freeze(a); Object.freeze(b); x.runtime.attachNullDescriptors(x.first);
    x.owner.getDObj = () => {throw Error('replacement must not run');}; x.runtime.attachNullDescriptors(x.first);
  }
  {const x = fixture(); const runtime = createSourceDisplayAnimationAttachmentRuntime({getDObj(id) {
    const record = {...x.dobjs.getDObj(id)};
    for (const key of ['aobj10', 'classUpdate44']) Object.defineProperty(record, key, {get() {throw Error('unconsumed field read');}});
    return record;
  }}); runtime.attachNullDescriptors(x.first);}
  {const x = fixture(); x.dobjs.getDObj(x.last).next04 = x.first;
    rejects(() => x.runtime.attachNullDescriptors(x.first), 'cycle/revisited'); check(x.visits.length === 2, 'late cycle');
    x.dobjs.getDObj(x.last).next04 = null; x.runtime.attachNullDescriptors(x.first);
  }
  {const x = fixture(); const runtime = createSourceDisplayAnimationAttachmentRuntime(x.owner, 1);
    rejects(() => runtime.attachNullDescriptors(x.first), 'visit budget'); check(x.visits.length === 1, 'late budget');}
  {const x = fixture(); x.dobjs.getDObj(x.last).next04 = Symbol('foreign');
    rejects(() => x.runtime.attachNullDescriptors(x.first), 'unknown/non-owned DObj'); check(x.visits.length === 3, 'late foreign identity');}
  for (const field of ['pobj0c', 'mobj08', 'next04'] as const) {
    const x = fixture(); (x.dobjs.getDObj(x.last) as unknown as Record<string, unknown>)[field] = NaN;
    rejects(() => x.runtime.attachNullDescriptors(x.first), field); check(x.visits.length === 2, 'lazy late malformed field');
    const y = fixture(); let invoked = false;
    const runtime = createSourceDisplayAnimationAttachmentRuntime({getDObj(id) {
      y.visits.push(id); const record = {...y.dobjs.getDObj(id)};
      if (id === y.last) Object.defineProperty(record, field, {get() {invoked = true; throw Error('accessor invoked');}});
      return record;
    }});
    rejects(() => runtime.attachNullDescriptors(y.first), `${field}: own data`);
    check(y.visits.length === 2 && !invoked, 'late accessor refused without invocation');
  }
  {const x = fixture(); const record = x.dobjs.getDObj(x.first) as unknown as Record<string, unknown>;
    record.pobj0c = 7; record.mobj08 = 8; record.next04 = 9;
    rejects(() => x.runtime.attachNullDescriptors(x.first), 'pobj0c'); record.pobj0c = null;
    rejects(() => x.runtime.attachNullDescriptors(x.first), 'mobj08'); record.mobj08 = null;
    rejects(() => x.runtime.attachNullDescriptors(x.first), 'next04');
    x.runtime.attachNullDescriptors(null);
  }
  {const x = fixture(); let runtime: SourceDisplayAnimationAttachmentRuntime;
    runtime = createSourceDisplayAnimationAttachmentRuntime({getDObj(id) {
      runtime.attachNullDescriptors(null);
      rejects(() => runtime.attachNullDescriptors(id), 'same-runtime reentry'); return x.dobjs.getDObj(id);
    }}); rejects(() => runtime.attachNullDescriptors(x.first), 'caught inside an adapter');}
  {const x = fixture(); const runtime = createSourceDisplayAnimationAttachmentRuntime({getDObj(id) {
    return Promise.resolve(x.dobjs.getDObj(id)) as unknown as ReturnType<typeof x.dobjs.getDObj>;
  }}); rejects(() => runtime.attachNullDescriptors(x.first), 'pobj0c: own data');}
  for (const budget of [0, -1, 1.5, Infinity]) rejects(() => createSourceDisplayAnimationAttachmentRuntime(fixture().owner, budget), 'maxNodes');
}
