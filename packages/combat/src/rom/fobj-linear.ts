/** Offline opcode-2 value stage of FObjInterpretAnim (80249ac4).
 * Evidence: research/decomp/ghidra-export/chunk_0071.c:869–1207; the DOL
 * uses fsubs then fdivs for a dirty slope and fmadds for the returned scalar
 * (80249cb0, 80249e40, 8024a0cc). This is NOT an interpreter or callback.
 * The caller must already establish an eligible phase and non-null callback,
 * including any preceding frame/end-flush writes. No phase gating, dispatch,
 * spline interpolation, geometry or production integration is supplied here.
 * Owned sealed finite-f32 headers, RN=00 (nearest-even) and NI=0 (gradual
 * underflow) assumptions only; a later capture report indicates NI=1, pending
 * raw-capture provenance reconciliation. This model does not implement NI=1. Domain
 * preflight and overflow rejection are host policy, not source memory faults
 * or FPSCR emulation. Completed source writes survive arithmetic rejection.
 */
import type {SourceFObjHeader, SourceFObjRuntime} from './fobj-list.js';
import {addSourceFloat32, fusedMultiplyAddSourceFloat32} from './source-float.js';

/** Requires the source's prior opcode byte12 to be exactly 2. Does not infer
 * callback eligibility from flags10: local interpreter state can differ from
 * its stored low nibble, and the three source call sites have different gates.
 */
export function evaluateSourceFObjLinearValue(runtime: SourceFObjRuntime,
  node: SourceFObjHeader): number {
  runtime.validateNode(node);
  if (node.byte12 !== 2) {
    throw Error('[fobj-linear] opcode2 required; no value evaluation or header writes performed');
  }
  if ((node.flags10 & 0x20) !== 0) {
    node.flags10 &= 0xdf;
    if (node.half1a === 0) {
      node.value28 = 0;
      node.value20 = node.value24;
    } else {
      // Preserve the separate fsubs rounding/overflow before division. uint16
      // conversion is exact; division by 1..65535 cannot double-round at f32
      // precision through binary64 (including subnormal results).
      const numerator = addSourceFloat32(node.value24, -node.value20);
      node.value28 = Math.fround(numerator / node.half1a);
    }
  }
  // Loaded f32 operands; do not split into multiply then add or round through
  // binary64. The returned scalar models the source stack value, not dispatch.
  return fusedMultiplyAddSourceFloat32(node.value28, node.frame1c, node.value20);
}
