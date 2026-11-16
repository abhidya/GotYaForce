/** Internal live8020bc88 PSVECSquareDistance body, not a runtime capability.
 * The caller captures canonical A/B addresses and the existing processor owner.
 * Four paired-load admissions and repeated Y loads preserve the authenticated
 * ten-instruction order. The guard is caller ownership/completeness bookkeeping,
 * never a supplied implementation of a source callee. No scalar snapshots,
 * estimator, processor defaults, nonfinite values or hardware parity are implied.
 */
import {addSourceFloat32,fusedMultiplyAddSourceFloat32} from './source-float.js';
import type {SourceObjectAllocationRuntime} from './source-object-allocation.js';
import type {SourceProjectileRootRuntime} from './projectile-root-lifecycle.js';

interface SourceSquareDistanceCall {
  a: object;
  aName: string;
  /** Original captured pointer representation, resolved only at the first B load. */
  b: unknown;
  bRepresentation: 'identity'|'record';
  allocator: SourceObjectAllocationRuntime;
  root: SourceProjectileRootRuntime;
  processor: object;
  guard(): void;
}
function fail(reason: string): never {throw Error(`[source-square-distance] ${reason}`);}
function float(value: unknown,where: string): number {
  if(typeof value!=='number' || !Number.isFinite(value) || !Object.is(value,Math.fround(value)))
    fail(`${where}: finite exact source float32 required`);return value;
}
export function readSourceSquareDistance(call: SourceSquareDistanceCall): number {
  const {a,aName,b,bRepresentation,allocator,root,processor,guard}=call;
  const invoke=<T>(run: ()=>T): T=>{const result=run();guard();return result;};
  const read=(owner: object,key: string): unknown=>{
    const field=Object.getOwnPropertyDescriptor(owner,key);
    if(!field || !('value' in field)) fail(`${key}: own data property required`);
    const value=field.value;guard();return value;
  };
  const paired=(): void=>{
    if(invoke(()=>root.getVectorProcessorProfile())!==processor) fail('processor profile owner changed');
    const value=read(processor,'gqr0');
    if(typeof value!=='number' || !Number.isInteger(value) || value<0 || value>0xffffffff)
      fail('gqr0: raw unsigned source integer required');
    if(value!==0) fail('GQR0 must explicitly select float load/store type0 scale0');
  };
  paired();const ay=float(read(a,'y'),`${aName}.y`),az=float(read(a,'z'),`${aName}.z`);
  paired();
  if(b===null) fail('8020bc8c null OBJECT at reached vector load');
  let object: symbol;
  if(bRepresentation==='identity') {
    if(typeof b!=='symbol') fail('OBJECT source pointer identity required');object=b;
  } else {
    if(b===null || typeof b!=='object' || b instanceof Promise || ArrayBuffer.isView(b))
      fail('OBJECT source pointer record required');
    object=invoke(()=>allocator.getPointerIdentity(b));
  }
  const bytes=invoke(()=>allocator.getObject(object));
  if(bytes===a) fail('OBJECT bytes alias canonical A vector');
  const by=invoke(()=>allocator.readF32(object,0x68)),bz=invoke(()=>allocator.readF32(object,0x6c));
  const oldY=addSourceFloat32(ay,-by),oldZ=addSourceFloat32(az,-bz);guard();
  paired();const ax=float(read(a,'x'),`${aName}.x`),ayAgain=float(read(a,'y'),`${aName}.y`);
  paired();const bx=invoke(()=>allocator.readF32(object,0x64)),byAgain=invoke(()=>allocator.readF32(object,0x68));
  const yy=float(Math.fround(oldY*oldY),'square oldY'),zz=float(Math.fround(oldZ*oldZ),'square oldZ');
  const dx=addSourceFloat32(ax,-bx),dy=addSourceFloat32(ayAgain,-byAgain);guard();
  const xy=fusedMultiplyAddSourceFloat32(dx,dx,yy);guard();
  fusedMultiplyAddSourceFloat32(dy,dy,zz);guard(); // Unused paired lane still executes.
  const result=addSourceFloat32(xy,zz);guard();return result;
}
