/** Bounded primary afbc/b03c and secondary b218/b298 only. Model-backed frsqrte seeds transfer
 * from terrain evidence, NOT its single-precision refinement. This does not
 * implement primary6d228, arbitrary estimates, FPSCR status or hardware parity.
 * Constants are authenticated by actor-command-admission evidence106–107.
 */
import {fusedMultiplyAddSourceFloat64,negatedFusedMultiplySubtractSourceFloat64} from './source-float64.js';
const nativeDescriptor=Reflect.getOwnPropertyDescriptor;
const multiply=(a:number,b:number):number=>fusedMultiplyAddSourceFloat64(a,b,0);
export interface SourceTargetDistanceRefinement {
  seed:number;
  rounds: {q:number;h:number;c:number;e:number}[];
  product:number;
  value:number;
}
/** Pure instruction trace, no observers, source callbacks or persistent stack.
 * Exactly three binary64 rounds, then fmul/frsp and a local f32 stack roundtrip.
 * Keeping intermediate words exposes the third round even where final f32 alone
 * cannot distinguish two rounds. Nonfused/reassociated mutants can coincide on
 * this power-of-two domain; numeric tests do not prove those schedule choices.
 */
export function refineSourceTargetDistance(square:number,seed:number,half:number,three:number):SourceTargetDistanceRefinement {
  let e=seed;const rounds:SourceTargetDistanceRefinement['rounds']=[];
  for(let round=0;round<3;round++) {
    const q=multiply(e,e);
    const h=multiply(half,e);
    const c=negatedFusedMultiplySubtractSourceFloat64(square,q,three);
    e=multiply(h,c);
    rounds.push({q,h,c,e});
  }
  const product=multiply(square,e),single=Math.fround(product);
  const stack=new DataView(new ArrayBuffer(4));stack.setFloat32(0,single,false);
  return {seed,rounds,product,value:stack.getFloat32(0,false)};
}
/** Model-backed bounded lookup, separately visible for exact seed witnesses. */
export function sourceTargetDistanceSeed(square:number):number|undefined {
  return square===0.25?16381/8192:square===1?16381/16384:
    square===4?16381/32768:square===16?16381/65536:square===64?16381/131072:undefined;
}
export function readSourceTargetDistance(square:number,processor:object,data:object,guard:()=>void,
  address:'8006afbc'|'8006b03c'|'8006b218'|'8006b298'):number {
  function fail(reason:string):never {throw Error(`[source-target-distance] ${address} ${reason}`);}
  // Admit the actual returned square, never an ideal norm or axis classification.
  const seed=sourceTargetDistanceSeed(square);
  if(seed===undefined) fail(`reached unsupported frsqrte ${address==='8006afbc'||address==='8006b03c'?'primary':'secondary'} ${address==='8006b298'||address==='8006b03c'?'horizontal ':''}distance estimator square`);
  const read=(owner:object,key:string):unknown=>{
    const p=Object.getOwnPropertyDescriptor(owner,key);guard();
    if(!p || !('value' in p)) fail(`${key}: own data property required`);
    return p.value;
  };
  const controls=():void=>{
    read(processor,'fpscrControl');
    // Public metadata observers may mutate the control while returning. The
    // captured intrinsic samples its final own-data value with no callbacks.
    const field=nativeDescriptor(processor,'fpscrControl');
    if(!field || !('value' in field)) fail('fpscrControl: own data property required');
    const control=field.value;
    if(typeof control!=='number' || !Number.isInteger(control) || control<0 || control>0xffffffff)
      fail('fpscrControl: explicit unsigned32 control required');
    if((control&0xff)!==0) fail('fpscrControl: requires explicit FPSCR RN00/NI0 and disabled floating exception enables');
  };
  guard();controls(); // reached frsqrte, before either lfd
  const half=read(data,'double80437660');
  if(typeof half!=='number' || !Object.is(half,0.5)) fail('double80437660: differs from authenticated binary64 bits');
  const three=read(data,'double80437668');
  if(typeof three!=='number' || !Object.is(three,3)) fail('double80437668: differs from authenticated binary64 bits');
  // Revalidate controls after observable data admissions; no application
  // callback can run during the pure binary64 schedule itself.
  guard();controls();
  const result=refineSourceTargetDistance(square,seed,half,three).value;
  guard();return result;
}
