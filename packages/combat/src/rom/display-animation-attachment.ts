/** Bounded null-material/null-shape HSD_DObjAddAnimAll (8023d838).
 * chunk_0069.c:6239–6291 reads pobj0c, mobj08, then current next04.
 * The misleading PObjRemoveAnimAll name does NOT imply removal here:
 * chunk_0071.c:1447 and chunk_0070.c:1212 require non-null descriptors.
 * Both helpers return without touching their targets for this caller's null
 * descriptors. Existing PObj/MObj animations, DObj aobj10 and class callbacks
 * are preserved. No descendant identity is resolved and no descriptor loaded.
 *
 * Own-data non-proxy records and synchronous owner methods are host bounds.
 * Only consumed fields are admitted, lazily and read-only. The owner method is
 * captured with its receiver. Cycles, visit budgets and poisoned reentry are
 * host refusals, not retail control flow. Null lists bypass consumed fields.
 * There is no general non-null descriptor API or rollback of prior effects.
 */
import type {SourceDObjAnimationRuntime} from './dobj-animation.js';
export interface SourceDisplayAnimationAttachmentRuntime {
  attachNullDescriptors(list: symbol | null): void;
}
function fail(reason: string): never {throw Error(`[display-animation-attachment] ${reason}; offline execution aborted, prior effects are not rolled back`);}
function own(record: unknown, key: string): unknown {
  if (record === null || typeof record !== 'object') fail(`${key}: data record required`);
  const p = Object.getOwnPropertyDescriptor(record, key);
  if (!p || !('value' in p)) fail(`${key}: own data property required`);
  return p.value;
}
function identity(value: unknown, where: string): asserts value is symbol | null {
  if (value !== null && typeof value !== 'symbol') fail(`${where}: opaque symbol or null required`);
}
function link(record: unknown, key: string): symbol | null {const v = own(record, key); identity(v, key); return v;}
export function createSourceDisplayAnimationAttachmentRuntime(
  dobjs: Pick<SourceDObjAnimationRuntime, 'getDObj'>, maxNodes = 4096,
): SourceDisplayAnimationAttachmentRuntime {
  if (!Number.isSafeInteger(maxNodes) || maxNodes < 1) fail('maxNodes must be a positive safe integer');
  const get = own(dobjs, 'getDObj');
  if (typeof get !== 'function') fail('getDObj: own data-function required');
  let busy = false, reentered = false;
  return Object.freeze({
    attachNullDescriptors(list: symbol | null): void {
      if (list === null) return;
      if (busy) {reentered = true; fail('same-runtime reentry is unsupported');}
      busy = true; reentered = false;
      try {
        const seen = new Set<symbol>();
        let current: symbol | null = list;
        while (current !== null) {
          identity(current, 'DObj list');
          if (seen.has(current)) fail('cycle/revisited DObj is unsupported');
          if (seen.size >= maxNodes) fail('DObj visit budget exhausted');
          const object: unknown = Reflect.apply(get, dobjs, [current]);
          if (reentered) fail('same-runtime reentry was caught inside an adapter');
          // Promises and other non-record results fail at the first consumed
          // own field, without probing then/accessors or traversing descendants.
          seen.add(current);
          link(object, 'pobj0c');
          link(object, 'mobj08');
          current = link(object, 'next04');
        }
      } finally {busy = false;}
    },
  });
}
