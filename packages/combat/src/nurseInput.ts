import type { BorgRuntime } from './types.js';
export function isNurseX(id: string): boolean { return id === 'pl0900' || id === 'pl0908' || id === 'pl090d'; }
interface NurseInput { held: boolean; pressEdge: boolean; pending: boolean }
const inputs = new WeakMap<BorgRuntime, NurseInput>();
/** Advance even during hitstun/another action; held X is never a deferred press. */
export function stepNurseInput(owner: BorgRuntime, held: boolean): NurseInput {
  const previous = inputs.get(owner);
  const next = { held, pressEdge: held && !previous?.held, pending: true };
  inputs.set(owner, next);
  return next;
}
export function consumeNurseInput(owner: BorgRuntime, held: boolean): NurseInput {
  const input = inputs.get(owner);
  const next = input?.pending ? input : stepNurseInput(owner, held);
  next.pending = false;
  return next;
}
