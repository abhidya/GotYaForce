/** Bounded offline scalar callback slice of FObjInterpretAnim (80249ac4).
 * Source: chunk_0071.c:869–1207; audited DOL call sites 80249d28 (state6),
 * 80249eb8 (state3), 8024a134 (state4). Uses the actual loader/wait/timing core,
 * not decoded-key sampling. Only eligible constant1, linear2 and key6 callbacks
 * are supported; all other eligible opcodes fail rather than synthesizing a
 * value or calling the unaudited spline. No full FObj, JObj or live integration.
 *
 * Explicit factory binding supplies the owner absent from SourceAObjEffects.
 * Owner/callback symbols are identities, never RAM pointers. The scalar is a
 * by-value copy of the source stack scalar; pointer aliasing is not modeled.
 * Handlers may mutate owned headers and AObj records via closures, but must be
 * synchronous and return undefined, without scheduling deferred writes.
 * Same-runtime direct/list reentry and invalid post-handler headers are refused.
 * Failure retains earlier writes/effects, including opcode6's pre-call flag clear.
 * Finite f32 arithmetic assumes RN=00/NI=0. A later capture report indicates
 * NI=1, pending raw-capture provenance reconciliation; no parity for that mode.
 */
import {evaluateSourceFObjLinearValue} from './fobj-linear.js';
import {createSourceFObjTimingRuntime, type SourceFObjTimingRuntime} from './fobj-timing-core.js';

export type SourceFObjCallbackOwner = symbol | null;
export type SourceFObjScalarHandler = (owner: SourceFObjCallbackOwner, track: number, value: number) => void;
export interface SourceFObjScalarCallbackRuntime extends SourceFObjTimingRuntime {
  createCallback(handler: SourceFObjScalarHandler): symbol;
}
function fail(reason: string): never {
  throw Error(`[fobj-callback] ${reason}; offline execution aborted, prior writes/effects are not rolled back`);
}
/** The owner argument is required, even when explicitly null. Callback identity
 * ownership is checked before any non-null node/list entry writes, including
 * StopAll lists that skip every interpreter. Null node/list remains a no-op.
 */
export function createSourceFObjScalarCallbackRuntime(owner: SourceFObjCallbackOwner,
  maxTransitions = 65536, maxNodes = 4096): SourceFObjScalarCallbackRuntime {
  if (owner !== null && typeof owner !== 'symbol') fail('explicit owner symbol or null required');
  const callbacks = new Map<symbol, SourceFObjScalarHandler>();
  const runtime = createSourceFObjTimingRuntime({
    validateCallback(callback) {
      if (callback !== null && !callbacks.has(callback)) fail('unknown/non-owned callback identity');
    },
    invoke(r, n, callback) {
      let value: number;
      switch (n.byte12) {
        case 1: value = n.frame1c < n.half1a ? n.value20 : n.value24; break;
        case 2: value = evaluateSourceFObjLinearValue(r, n); break;
        case 6:
          if ((n.flags10 & 0x80) === 0) return;
          value = n.value20;
          n.flags10 &= 0x7f;
          break;
        default: fail(`unsupported eligible opcode ${n.byte12}`);
      }
      let result: unknown;
      try { result = callbacks.get(callback)!(owner, n.track13, value); }
      catch (error) { fail(`handler threw (${String(error)})`); }
      if (result !== undefined) fail('handler must complete synchronously and return undefined');
    },
  }, maxTransitions, maxNodes);
  return {...runtime, createCallback(handler) {
    if (typeof handler !== 'function') fail('synchronous scalar handler required');
    const identity = Symbol('owned FObj scalar callback');
    callbacks.set(identity, handler);
    return identity;
  }};
}
