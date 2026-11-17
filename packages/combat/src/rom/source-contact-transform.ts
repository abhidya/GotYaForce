/** Internal8020b7a8 join over captured canonical source addresses, not a matrix
 * snapshot or a new matrix owner. Evidence: terrain-orientation reader's84B
 * SDK body and contact-callback-prefix reader's996B caller. Only ordinary
 * nonproxy BE byte records and explicit finite RN00/NI0/GQR0 inputs are admitted.
 * Exact outer-callsite admission is private and single-use. */
import {addSourceFloat32,fusedMultiplyAddSourceFloat32 as fma} from './source-float.js';
import {consumeSourceBattleOuterContactTransformInvocation,checkSourceBattleOuterContactTransformInvocation,
 type SourceBattleOuterFrameRuntime} from './battle-outer-frame.js';

const descriptor=Reflect.getOwnPropertyDescriptor,descriptors=Object.getOwnPropertyDescriptors,keys=Reflect.ownKeys;
const View=DataView,setWord=DataView.prototype.setUint32,getFloat=DataView.prototype.getFloat32;
const setFloat=DataView.prototype.setFloat32,getWord=DataView.prototype.getUint32,round=Math.fround;
function fail(s:string):never{throw Error('[source-contact-transform] '+s);}
function float(v:unknown):number{
 if(typeof v!=='number'||!Number.isFinite(v)||!Object.is(v,round(v)))fail('finite exact float32 required');return v;
}
export function executeSourceContactTransform(outer:SourceBattleOuterFrameRuntime,node:symbol):void{
 const {allocator,root,matrix,input,output}=consumeSourceBattleOuterContactTransformInvocation(outer,node);
 const guard=():void=>checkSourceBattleOuterContactTransformInvocation(outer,node);
 const checked=<T>(f:()=>T):T=>{const v=f();guard();return v;};
 const own=(o:object,k:string):unknown=>{const d=Object.getOwnPropertyDescriptor(o,k);guard();if(!d||!('value'in d))fail(k+': own byte/data property required');return d.value;};
 const processor=checked(()=>root.getVectorProcessorProfile());if(!processor)fail('explicit processor profile required');
 const declarations=checked(()=>root.getRetainedStorageOwners()).filter(o=>{const d=descriptor(o,'processor');return d&&'value'in d&&d.value===processor;});
 if(declarations.length!==1)fail('canonical processor declaration required');
 const terminal=(paired=false):void=>{
  const p=descriptor(declarations[0]!,'processor');if(!p||!('value'in p)||p.value!==processor)fail('processor owner changed');
  const f=descriptor(processor,'fpscrControl');if(!f||!('value'in f)||typeof f.value!=='number'||!Number.isInteger(f.value)||f.value<0||f.value>0xffffffff||(f.value&255)!==0)fail('explicit FPSCR RN00/NI0 and disabled exceptions required');
  if(paired){const g=descriptor(processor,'gqr0');if(!g||!('value'in g)||g.value!==0)fail('explicit GQR0 float scale0 required');}
 };
 const controls=(paired=false):void=>{if(checked(()=>root.getVectorProcessorProfile())!==processor)fail('processor owner changed');own(processor,'fpscrControl');if(paired)own(processor,'gqr0');terminal(paired);};
 interface Address{base:symbol;offset:number;bytes:object}
 const addresses=new Map<symbol,Address>();
 const terminalByteShape=(bytes:object):void=>{
  // Host admission only: reject structured actors, vectors, slot tables and
  // overlays. This does not copy or eagerly use any scalar source operand.
  if(Array.isArray(bytes)||ArrayBuffer.isView(bytes))fail('ordinary canonical byte record required');
  const fields=descriptors(bytes);
  for(const key of keys(fields)){
   if(typeof key!=='string')fail('symbol byte overlay unsupported');const d=fields[key]!;
   if(!/^(0|[1-9][0-9]*)$/.test(key)||Number(key)>65535||!('value'in d)||typeof d.value!=='number'||!Number.isInteger(d.value)||d.value<0||d.value>255)
    fail('structured or non-byte source owner unsupported');
  }
 };
 const byteShape=(bytes:object):void=>{terminalByteShape(bytes);guard();};
 const terminalBytes=():void=>{for(const a of addresses.values())terminalByteShape(a.bytes);};
 const address=(id:symbol|null,relative:number):{a:Address;offset:number}=>{
  if(id===null)fail('null source pointer at reached float load');
  let a=addresses.get(id);
  if(!a){const interior=checked(()=>allocator.getInteriorAddress(id));const base=interior?.base??id;
   a={base,offset:interior?.byteOffset??0,bytes:checked(()=>allocator.getPointerTarget(base))};addresses.set(id,a);}
  if(checked(()=>allocator.getPointerTarget(a!.base))!==a.bytes)fail('canonical byte owner changed');byteShape(a.bytes);
  const offset=a.offset+relative;if(!Number.isSafeInteger(offset)||offset<0||offset>65532||offset%4)fail('aligned canonical float address required');
  return {a,offset};
 };
 const encoding=new View(new ArrayBuffer(4));
 const load=(id:symbol|null,relative:number):number=>{
  const {a,offset}=address(id,relative);let word=0;
  for(let i=0;i<4;i++){const v=own(a.bytes,String(offset+i));if(typeof v!=='number'||!Number.isInteger(v)||v<0||v>255)fail('raw byte required');word=word*256+v;}
  terminalBytes();terminal(true);setWord.call(encoding,0,word,false);return float(getFloat.call(encoding,0,false));
 };
 const pair=(id:symbol|null,relative:number):[number,number]=>{controls(true);const x=load(id,relative),y=load(id,relative+4);return [x,y];};
 const store=(offset:number,value:number):void=>{
  const bytes=checked(()=>allocator.getObject(output));byteShape(bytes);setFloat.call(encoding,0,float(value),false);const word=getWord.call(encoding,0,false);
  for(let i=0;i<4;i++){const d=Object.getOwnPropertyDescriptor(bytes,String(offset+i));guard();if(!d||!('value'in d)||!d.writable)fail('writable scalar destination required');}
  controls(true);guard();if(allocator.getObject(output)!==bytes)fail('output byte owner changed');
  for(let i=0;i<4;i++){const d=descriptor(bytes,String(offset+i));if(!d||!('value'in d)||!d.writable)fail('scalar destination changed');}
  terminalBytes();terminalByteShape(bytes);terminal(true);for(let i=0;i<4;i++)bytes[offset+i]=(word>>>(8*(3-i)))&255;guard();
 };
 const mul=(a:number,b:number):number=>{controls();return float(round(a*b));};
 const madd=(a:number,b:number,c:number):number=>{controls();return fma(a,b,c);};
 const add=(a:number,b:number):number=>{controls();return addSourceFloat32(a,b);};
 const [x,y]=pair(input,0x0c),[m0,m1]=pair(matrix,0);controls(true);const z=load(input,0x14);
 const p0=mul(m0,x),p1=mul(m1,y),[m2,m3]=pair(matrix,8),q0=madd(m2,z,p0),q1=madd(m3,1,p1);
 const [m4,m5]=pair(matrix,16),resultX=add(q0,q1),[m6,m7]=pair(matrix,24),p4=mul(m4,x),p5=mul(m5,y);
 store(0x30,resultX);const q4=madd(m6,z,p4),q5=madd(m7,1,p5),[m8,m9]=pair(matrix,32),resultY=add(q4,q5);
 const [m10,m11]=pair(matrix,40),p8=mul(m8,x),p9=mul(m9,y);store(0x34,resultY);
 const q8=madd(m10,z,p8),q9=madd(m11,1,p9);store(0x38,add(q8,q9));guard();
}
