/** Internal ownership bookkeeping only: no source data or execution capability.
 * Late target helpers cannot reuse a record in a separate canonical domain.
 * Canonical world matrices and allocator pointer targets are reserved against
 * helper storage. Pointer targets may be shared across allocator identity domains
 * (for example immutable export metadata), but never used as helper storage. */
import {requireSourceActorPlayerTableAddressability,type SourceActorSlotStatusRuntime} from './actor-slot-status.js';
import type {SourceObjectAllocationRuntime} from './source-object-allocation.js';
const claims=new WeakMap<object,object>(),pointerTargets=new WeakSet<object>();
const playerTables=new WeakMap<object,{helper:SourceActorSlotStatusRuntime;allocator:SourceObjectAllocationRuntime}>();
export function isSourceHelperStorageClaimed(storage:object):boolean{return claims.has(storage);}
export function claimSourceHelperStorage(storage: object,owner: object): boolean {
  const existing=claims.get(storage);
  if((pointerTargets.has(storage) && playerTables.get(storage)?.helper!==owner) ||
    (existing!==undefined && existing!==owner)) return false;
  claims.set(storage,owner);return true;
}
/** Addressable canonical records may be referenced by multiple identity domains.
 * Existing owner rules separately govern writable matrices/object/descriptor bytes. */
export function reserveSourcePointerStorage(storage: object): boolean {
  if(claims.has(storage)) return false;
  pointerTargets.add(storage);return true;
}
/** Only the active canonical player-table address formation may join domains.
 * Generic pointer registration remains unable to claim ANY helper storage. */
export function reserveSourcePlayerTableStorage(storage:object,helper:SourceActorSlotStatusRuntime,
  allocator:SourceObjectAllocationRuntime):boolean {
  requireSourceActorPlayerTableAddressability(helper,allocator,storage);
  const prior=playerTables.get(storage);
  if(claims.get(storage)!==helper || (prior!==undefined && (prior.helper!==helper || prior.allocator!==allocator)) ||
    (pointerTargets.has(storage) && prior===undefined))return false;
  playerTables.set(storage,{helper,allocator});pointerTargets.add(storage);return true;
}
/** Metadata only, never a grant or a mutation. */
export function isSourcePlayerTableStorage(storage:object,helper:SourceActorSlotStatusRuntime,
  allocator:SourceObjectAllocationRuntime):boolean {
  const entry=playerTables.get(storage);return entry?.helper===helper && entry.allocator===allocator;
}
/** This table's row references stay owned by its genuine helper, not by the
 * allocator/root that now retains a symbolic base address for the table. */
export function isSourcePlayerTableAddressStorage(storage:object,allocator:SourceObjectAllocationRuntime):boolean {
  return playerTables.get(storage)?.allocator===allocator;
}
