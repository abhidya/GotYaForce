/** Bounded psq_l W1/I4 scalar conversion for input8b73c.
 * IBM Gekko User Manual v1.2 §2.1.2.9 Tables2-16/17, §2.3.4.3.12
 * and psq_l p12-157. Type6 is signed8; loadScale0 gives an exact binary32
 * integer. W1 sets the unused paired lane to1. HID2[PSE/LSQE]=1 and
 * big-endian execution are explicit host preconditions, not captured state.
 * Only the low stack byte is converted. This models neither the address load
 * nor GQR initialization/invariance, angular evaluation or source provenance.
 */
export function loadSourceInputSignedByte(value: number, gqr4: number): readonly [number, 1] {
  if (!Number.isInteger(value) || value < -128 || value > 127)
    throw Error('[source-input-quantized] decoded signed-byte operand required');
  if (!Number.isInteger(gqr4) || gqr4 < 0 || gqr4 > 0xffffffff)
    throw Error('[source-input-quantized] raw unsigned32 GQR4 required');
  if (((gqr4 >>> 16) & 7) !== 6 || ((gqr4 >>> 24) & 63) !== 0)
    throw Error('[source-input-quantized] GQR4 requires signed8 load type6, scale0');
  return [value === 0 ? 0 : value, 1];
}

/** Validate the separate GQR0 W0 spill/reload envelope at452b0/452cc.
 * Float type0 ignores its scale. No opaque f31 lanes, stack bytes, denormal
 * flushing or FPR restoration are modeled here: this only admits the caller's
 * actor/return projection under an explicit float-paired ABI precondition.
 */
export function requireSourceInputFloatPairGqr(gqr0: number, operation: 'store' | 'load'): void {
  if (operation !== 'store' && operation !== 'load')
    throw Error('[source-input-quantized] explicit float-pair store/load operation required');
  if (!Number.isInteger(gqr0) || gqr0 < 0 || gqr0 > 0xffffffff)
    throw Error('[source-input-quantized] raw unsigned32 GQR0 required');
  const type = operation === 'store' ? gqr0 & 7 : (gqr0 >>> 16) & 7;
  if (type !== 0)
    throw Error(`[source-input-quantized] GQR0 requires float ${operation} type0 (scale ignored)`);
}

/** Bounded psq_st W1/I5 followed by lha at452c4/452c8. Type7 stores
 * signed16; scale0 truncates toward zero and SATURATES, rather than wrapping.
 * The quantizer is independent of FPSCR RN. Finite exact binary32 only; no
 * memory write, second lane, NaN/Infinity behavior or GQR initialization.
 */
export function storeSourceInputSignedShort(value: number, gqr5: number): number {
  if (!Number.isFinite(value) || !Object.is(value, Math.fround(value)))
    throw Error('[source-input-quantized] finite exact binary32 store operand required');
  if (!Number.isInteger(gqr5) || gqr5 < 0 || gqr5 > 0xffffffff)
    throw Error('[source-input-quantized] raw unsigned32 GQR5 required');
  if ((gqr5 & 7) !== 7 || ((gqr5 >>> 8) & 63) !== 0)
    throw Error('[source-input-quantized] GQR5 requires signed16 store type7, scale0');
  const result = Math.trunc(Math.max(-32768, Math.min(32767, value)));
  return result === 0 ? 0 : result;
}
