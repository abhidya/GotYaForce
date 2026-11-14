/** Offline callback-NULL subset of FObjInterpretAnim (80249ac4).
 * Evidence: research/decomp/ghidra-export/chunk_0071.c:869–1207; original
 * DOL interpreter SHA256 ab8ed02d2a35df72c8d07efb7ea76805a6f6edc9cb203d53768ba0c9640195af.
 * Models clock, loader, wait and end-state writes, NOT interpolation, callback
 * dispatch, decoded-key sampling, geometry or production integration.
 * Finite binary32 headers and active-state delta; Gekko §2.2.3 single operands.
 * Assumes FPSCR RN=00, NI=0, not an observed runtime FPSCR configuration.
 * Unsupported states, overflow, malformed streams and host budget limits
 * abort with earlier writes retained; these diagnostics are NOT retail behavior.
 */
import {createSourceFObjTimingRuntime, type SourceFObjTimingRuntime} from './fobj-timing-core.js';
export interface SourceFObjNullCallbackRuntime extends SourceFObjTimingRuntime {}
/** Both limits are host policies, not retail constants. Non-null callbacks on
 * non-null nodes/lists are rejected before writes, including skipped StopAll
 * nodes. Null identities are genuine no-ops. See the shared timing core for
 * state/delta entry contracts; no callback evaluation is enabled here.
 */
export function createSourceFObjNullCallbackRuntime(maxTransitions = 65536,
  maxNodes = 4096): SourceFObjNullCallbackRuntime {
  return createSourceFObjTimingRuntime(null, maxTransitions, maxNodes);
}
