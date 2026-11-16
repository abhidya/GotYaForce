/** Internal read-only39f6c/8020bc88 arithmetic, not a frame entry or capability.
 * Caller binds the same canonical raw scratch cells, constant owner and root;
 * guard checks its retained source graph, never supplies a callee result.
 * Ordinary nonproxy own-data storage, finite RN00/NI0 and explicit GQR0 only.
 * Positive estimates retain the existing five-square model-backed domain. */
import {addSourceFloat32 as add,fusedMultiplyAddSourceFloat32 as fma} from './source-float.js';
import {sourceTargetDistanceSeed,refineSourceTargetDistance} from './source-target-distance.js';
import type {SourceProjectileRootRuntime} from './projectile-root-lifecycle.js';
const descriptor=Reflect.getOwnPropertyDescriptor;
const View=DataView,putWord=DataView.prototype.setUint32,getFloat=DataView.prototype.getFloat32,round=Math.fround;
function fail(s:string):never{throw Error('[source-contact-predicate] '+s);}
export function readSourceContactPredicate(cells:object,constants:object,root:SourceProjectileRootRuntime,guard:()=>void):boolean{
 if(cells===constants)fail('scratch/constant owners alias');
 let processor:object|undefined,declaration:object|undefined;
 const aliases=(owner:object,key:string,address:number,width:number):void=>{
  const names=new Set<string>();
  for(const [prefix,size]of [['byte',1],['half',2],['short',2],['word',4],['float',4],['field',4],['double',8]]as const)
   for(let at=address-size+1;at<address+width;at++){const h=at.toString(16);names.add(prefix+h);names.add(prefix+h.toUpperCase());}
  for(let i=0;i<width;i++)names.add(String(address+i));
  for(const o of [cells,constants,...(processor?[processor]:[])])for(const n of names)
   if((o!==owner||n!==key)&&descriptor(o,n))fail('competing source cell '+n);
 };
 const own=(owner:object,key:string):unknown=>{const d=Object.getOwnPropertyDescriptor(owner,key);guard();if(!d||!('value'in d))fail(key+': own data required');return d.value;};
 const field=(owner:object,key:string,address:number,width:number):unknown=>{aliases(owner,key,address,width);const v=own(owner,key);aliases(owner,key,address,width);return v;};
 const scalar=(value:unknown):number=>{if(typeof value!=='number'||!Number.isFinite(value)||!Object.is(value,round(value)))fail('finite exact float32 required');return value;};
 const terminal=(paired=false):void=>{
  if(!processor||!declaration)fail('explicit scalar processor required');
  const p=descriptor(declaration,'processor');if(!p||!('value'in p)||p.value!==processor)fail('processor owner changed');
  const f=descriptor(processor,'fpscrControl');if(!f||!('value'in f)||typeof f.value!=='number'||!Number.isInteger(f.value)||f.value<0||f.value>0xffffffff||(f.value&255)!==0)fail('FPSCR RN00/NI0 and disabled exceptions required');
  if(paired){const g=descriptor(processor,'gqr0');if(!g||!('value'in g)||g.value!==0)fail('GQR0 float scale0 required');}
 };
 const controls=(paired=false):void=>{
  const p=root.getVectorProcessorProfile();guard();if(!p)fail('explicit scalar processor required');
  if(processor&&p!==processor)fail('processor owner changed');processor=p;
  if(p===cells||p===constants)fail('processor/source storage alias');
  const declarations=root.getRetainedStorageOwners().filter(o=>{const d=descriptor(o,'processor');return d&&'value'in d&&d.value===p;});guard();
  if(declarations.length!==1||(declaration&&declaration!==declarations[0]))fail('canonical processor declaration changed');declaration=declarations[0];
  own(p,'fpscrControl');if(paired)own(p,'gqr0');terminal(paired);
 };
 const constant=(address:number,value:number,width=4):number=>{
  const v=field(constants,(width===4?'float':'double')+address.toString(16),address,width);
  if(typeof v!=='number'||!Object.is(v,value))fail('authenticated constant '+address.toString(16)+' required');return v;
 };
 const load=(address:number,paired=false):number=>{
  const bits=field(cells,'word'+address.toString(16),address,4);
  if(typeof bits!=='number'||!Number.isInteger(bits)||bits<0||bits>0xffffffff)fail('raw unsigned scratch word required');
  const view=new View(new ArrayBuffer(4));putWord.call(view,0,bits,false);const value=scalar(getFloat.call(view,0,false));
  if(processor)terminal(paired);return value;
 };
 const threshold=constant(0x80437004,0.10000000149011612);
 const radiusA=load(0x803b04f4);controls();if(radiusA<=threshold)return false;
 const radiusB=load(0x803b038c);controls();if(radiusB<=threshold)return false;
 // Exact four paired loads, including live repeated Y. The unused second
 // FMA lane still executes and can refuse overflow before the final sum.
 controls(true);const ay=load(0x803b04e0,true),az=load(0x803b04e4,true);
 controls(true);const by=load(0x803b0378,true),bz=load(0x803b037c,true);
 controls();const dyOld=add(ay,-by),dzOld=add(az,-bz);
 controls(true);const ax=load(0x803b04dc,true),ayAgain=load(0x803b04e0,true);
 controls(true);const bx=load(0x803b0374,true),byAgain=load(0x803b0378,true);
 controls();const yy=scalar(round(dyOld*dyOld)),zz=scalar(round(dzOld*dzOld));
 const dx=add(ax,-bx),dy=add(ayAgain,-byAgain),xy=fma(dx,dx,yy);fma(dy,dy,zz);
 let distance=add(xy,zz);const zero=constant(0x80436f68,0);controls();
 if(distance>zero){
  const seed=sourceTargetDistanceSeed(distance);if(seed===undefined)fail('80039fd4 unsupported frsqrte square '+distance);
  const half=constant(0x80436fd0,0.5,8),three=constant(0x80436fd8,3,8);controls();
  distance=refineSourceTargetDistance(distance,seed,half,three).value;
 }
 const finalA=load(0x803b04f4),finalB=load(0x803b038c);controls();
 const sum=add(finalA,finalB);return distance<=sum;
}
