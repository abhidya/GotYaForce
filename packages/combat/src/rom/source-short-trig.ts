/** Internal authenticated45204/45238 wrapper in the existing zero-angle domain.
 * Caller supplies its canonical charge-data owner and captured explicit GQR5
 * profile, under the existing RN00/NI0 finite arithmetic domain. This is not a frame/command capability or an all-angle libm port.
 * Source sth/psq_l signed16 scale0, factor lfs, fmuls and zero-kernel/frsp order
 * is preserved; the guard performs caller ownership/failure bookkeeping only.
 */
export function readSourceShortTrig(heading: number,cosine: boolean,data: object,
  gqr5: unknown,guard: ()=>void): number {
  const fail=(reason: string): never=>{throw Error(`[source-short-trig] ${reason}`);};
  if(gqr5!==0x00070007) fail('GQR5: explicit signed16/scale0 profile0x00070007 required');
  if(!Number.isInteger(heading) || heading< -32768 || heading>32767)
    fail('signed source halfword heading required');
  const field=Object.getOwnPropertyDescriptor(data,'float80437078');guard();
  if(!field || !('value' in field)) fail('float80437078: own data property required');
  const factor=field!.value;
  if(typeof factor!=='number' || !Number.isFinite(factor) || !Object.is(factor,Math.fround(factor)))
    fail('float80437078: finite exact source float32 required');
  if(!Object.is(factor,0.0000958738019107841)) fail('float80437078: authenticated constant required');
  // A stored zero halfword quantizes to positive zero, including a host -0.
  const angle=Math.fround(factor*(heading===0?0:heading));guard();
  if(angle!==0) fail(`${cosine?'80045238':'80045204'} reached unsupported nonzero source trig`);
  // Existing selected direct-kernel evidence proves these two exact results.
  // Nonzero polynomial/range-reduction instructions remain outside this model.
  return cosine?1:0;
}
