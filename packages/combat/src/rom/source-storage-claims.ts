/** Internal ownership bookkeeping only: no source data or execution capability.
 * The two late-joined target helpers must not admit the same record in separate
 * domains merely because one helper reaches its optional data later. */
const claims=new WeakMap<object,object>();
export function claimSourceHelperStorage(storage: object,owner: object): boolean {
  const existing=claims.get(storage);
  if(existing!==undefined && existing!==owner) return false;
  claims.set(storage,owner);return true;
}
