/** Internal ownership bookkeeping only: no source data or execution capability.
 * Late target helpers cannot reuse a record in a separate canonical domain.
 * Allocator pointer targets may be shared across allocator identity domains
 * (for example immutable export metadata), but never used as helper storage. */
const claims=new WeakMap<object,object>(),pointerTargets=new WeakSet<object>();
export function claimSourceHelperStorage(storage: object,owner: object): boolean {
  const existing=claims.get(storage);
  if(pointerTargets.has(storage) || (existing!==undefined && existing!==owner)) return false;
  claims.set(storage,owner);return true;
}
/** A read-only external target is not exclusive to one allocator. Existing
 * allocator rules still separately own writable object/descriptor backing. */
export function reserveSourcePointerStorage(storage: object): boolean {
  if(claims.has(storage)) return false;
  pointerTargets.add(storage);return true;
}
