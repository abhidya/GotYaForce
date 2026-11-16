import {executeSourceContactTransform} from './source-contact-transform.js';
import {createSourcePlayerContactTestFixture} from './source-player-contact.selftest.js';
import type {createBattleTargetPreparationTestFixture} from './attached-setup-animation.selftest.js';
type Make=typeof createBattleTargetPreparationTestFixture;
function check(ok:boolean,s:string):void{if(!ok)throw Error('[battle-contact-transform-test] '+s);}
function refuses(f:()=>unknown,want:string):void{let got='';try{f();}catch(e){got=String(e);}check(got.includes(want),`expected ${want}, got ${got}`);}
/** Actual existing HIT/descriptor/matrix owners, with explicit synthetic finite
 * vector inputs. This neither completes initialization nor a normal frame. */
export function runBattleContactTransformSelfTests(make:Make):void{
 let count=0;
 const fresh=(mode=0)=>{
  count++;const x=createSourcePlayerContactTestFixture(make),id=x.groups[49]!.head!;
  const bytes=x.allocator.getObject(id)as Record<number,number>;
  x.allocator.writePointer(id,0x20,x.child);bytes[0x10]=mode;bytes[0x13]=77;
  const descriptor=x.allocator.readPointer(id,0x28)!,a=x.allocator.getInteriorAddress(descriptor)!;
  check(a!==null,'actual existing descriptor interior');
  const data=x.allocator.getPointerTarget(a.base)as Record<number,number>;
  const word=(b:Record<number,number>,o:number,v:number)=>{for(let i=0;i<4;i++)b[o+i]=(v>>>(8*(3-i)))&255;};
  const float=(b:Record<number,number>,o:number,v:number)=>{const d=new DataView(new ArrayBuffer(4));d.setFloat32(0,v,false);word(b,o,d.getUint32(0,false));};
  for(let i=0;i<3;i++){float(data,a.byteOffset+0xc+4*i,i+1);float(bytes,0x30+4*i,77+i);float(bytes,0x3c+4*i,87+i);}
  Object.assign(x.outerSources,{contactCounters:Object.fromEntries(['50','4e','4c','4a','48','46','44','42','40','3e'].map(s=>['half804362'+s,77]))});
  if(x.groups[55]===undefined)x.groups[55]={head:null,tail:null};
  const matrix=x.allocator.readPointer(id,0x60)!,m=x.allocator.getInteriorAddress(matrix)!;
  check(m?.base===x.child&&m.byteOffset===0x114,'real HIT60 points into existing child114');
  return Object.assign(x,{transformId:id,transformBytes:bytes,transformData:data,transformDescriptor:descriptor,transformOffset:a.byteOffset,
   transformMatrixBytes:x.allocator.getObject(x.child)as Record<number,number>,float,word,transformMode:mode});
 };
 type Fixture=ReturnType<typeof fresh>;
 const run=(x:Fixture,want:string,hook:(o:object,k:PropertyKey)=>void=()=>{}):void=>{
  const native=Object.getOwnPropertyDescriptor;let selected=false;
  Object.getOwnPropertyDescriptor=((o:object,k:PropertyKey)=>{
   if(!selected&&o===x.match&&k==='byte66'&&x.match.wordB0===0){selected=true;x.match.byte66=0;}
   const d=native(o,k);if(selected)hook(o,k);return d;
  })as typeof native;
  try{refuses(()=>x.frame.runFrame(),want);}finally{Object.getOwnPropertyDescriptor=native;}
  check(x.groups[9]!.head===x.child&&x.groups[49]!.head===x.transformId,'actual source lists preserved');
  check(Object.values(x.slotRecords).every(r=>r.contact26f===77),'later player contact work not skipped');
  refuses(()=>x.frame.runFrame(),'permanently incomplete');
 };
 const boundary=(mode:number)=>(mode===0?'8008a744':'8008a88c')+' reached contact timer continuation';
 const vector=(x:Fixture,offset:number)=>[0,4,8].map(i=>x.allocator.readF32(x.transformId,offset+i)).join(',');
 {const x=fresh();refuses(()=>executeSourceContactTransform(x.frame,x.transformId),'private');check(vector(x,0x30)==='77,78,79','outside private invocation cannot transform');}
 for(const mode of [0,1]){
  const x=fresh(mode);delete x.transformBytes[mode===0?0x48:0x4a];
  run(x,boundary(mode));check(vector(x,0x30)==='3,5,7','captured descriptor+0c transformed through genuine child114');
  check(vector(x,0x3c)===(mode===0?'3,5,7':'77,78,79'),'mode-specific raw copy order');
 }
 for(const fault of ['capturedDescriptor','capturedMatrix','inputAlias','matrixAlias','missingM8','readonlyY','lateReadonlyY','reentryX','helperReentryX','lateInputShape','lateOutputShape','lateGqrX','lateGqrY','lateGqrZ','lateFpscrZ','gqr','fpscr','profileOwner','nullInput','nullMatrix','missingInputZ','structuredInput','fma','signedZero']as const){
  const x=fresh(1);let changed=false,afterMatrixPair=false,reads:string[]=[];
  if(fault==='inputAlias'){
   x.allocator.writePointer(x.transformId,0x28,x.allocator.getInteriorPointer(x.transformId,0x24));
   [1,2,3].forEach((v,i)=>x.float(x.transformBytes,0x30+4*i,v));
  }
  if(fault==='matrixAlias')x.allocator.writePointer(x.transformId,0x60,x.allocator.getInteriorPointer(x.transformId,0x10));
  if(fault==='readonlyY')Object.defineProperty(x.transformBytes,String(0x34),{writable:false});
  if(fault==='nullInput')x.allocator.writePointer(x.transformId,0x28,null);
  if(fault==='nullMatrix'){x.allocator.writePointer(x.transformId,0x60,null);delete x.transformData[x.transformOffset+0x14];}
  if(fault==='missingInputZ')delete x.transformData[x.transformOffset+0x14];
  if(fault==='structuredInput')Object.assign(x.transformData,{x:1});
  if(fault==='fma')[ -1.000000238418579,0,1.0000001192092896].forEach((v,i)=>x.float(x.transformData,x.transformOffset+0xc+4*i,v));
  if(fault==='signedZero')[1,1,1].forEach((v,i)=>x.float(x.transformData,x.transformOffset+0xc+4*i,v));
  const expected=fault==='missingM8'||fault==='missingInputZ'?'own byte/data':fault==='readonlyY'?'writable scalar':fault==='lateReadonlyY'?'scalar destination changed':fault==='reentryX'?'private':fault==='helperReentryX'?'private':fault==='lateInputShape'||fault==='lateOutputShape'?'structured or non-byte':fault==='gqr'||fault.startsWith('lateGqr')?'GQR0':fault==='fpscr'||fault==='lateFpscrZ'?'FPSCR':fault==='profileOwner'?'processor owner changed':fault.startsWith('null')?'null source pointer':fault==='structuredInput'?'structured or non-byte':boundary(1);
  run(x,expected,(o,k)=>{
   if(o===x.transformMatrixBytes&&k===String(0x133))afterMatrixPair=true;
   if(o===x.transformMatrixBytes&&['308','324','340'].includes(String(k)))reads.push(String(k));
   if(!changed&&fault==='capturedDescriptor'&&o===x.transformBytes&&k===String(0x2b)){changed=true;for(let i=0;i<4;i++)x.transformBytes[0x28+i]=0;}
   if(!changed&&o===x.transformBytes&&k===String(0x63)){
    if(fault==='capturedMatrix'){changed=true;for(let i=0;i<4;i++)x.transformBytes[0x60+i]=0;}
    if(fault==='missingM8'){changed=true;delete x.transformMatrixBytes[0x134];}
    if(fault==='gqr'){changed=true;x.drawProcessor.gqr0=1;}
    if(fault==='fpscr'){changed=true;x.drawProcessor.fpscrControl=1;}
    if(fault==='matrixAlias'||fault==='fma'||fault==='signedZero'){
     changed=true;const m=fault==='signedZero'?Array(12).fill(-0):fault==='fma'?[1,0,1.0000001192092896,0,0,1,0,0,0,0,1,0]:[1,0,0,2,0,1,0,3,0,0,1,4];
     m.forEach((v,i)=>x.float(fault==='matrixAlias'?x.transformBytes:x.transformMatrixBytes,(fault==='matrixAlias'?0x10:0x114)+4*i,v));
    }
   }
   if(afterMatrixPair&&!changed&&fault==='lateReadonlyY'&&o===x.transformBytes&&k===String(0x37)){changed=true;Object.defineProperty(x.transformBytes,String(0x34),{writable:false});}
   if(afterMatrixPair&&!changed&&['lateGqrX','lateGqrY','lateGqrZ','lateFpscrZ'].includes(fault)&&o===x.transformBytes&&k===String(fault==='lateGqrX'?0x33:fault==='lateGqrY'?0x37:0x3b)){changed=true;if(fault.startsWith('lateGqr'))x.drawProcessor.gqr0=4;else x.drawProcessor.fpscrControl=1;}
   if(afterMatrixPair&&!changed&&fault==='helperReentryX'&&o===x.transformBytes&&k===String(0x30)){changed=true;try{executeSourceContactTransform(x.frame,x.transformId);}catch{}}
   if(afterMatrixPair&&!changed&&fault==='lateInputShape'&&o===x.transformBytes&&k===String(0x33)){changed=true;Object.assign(x.transformData,{x:1});}
   if(afterMatrixPair&&!changed&&fault==='lateOutputShape'&&o===x.transformBytes&&k===String(0x33)){changed=true;Object.assign(x.transformBytes,{x:1});}
   if(afterMatrixPair&&!changed&&fault==='reentryX'&&o===x.transformBytes&&k===String(0x30)){changed=true;try{x.frame.runFrame();}catch{}}
   if(!changed&&fault==='profileOwner'&&o===x.drawProcessor&&k==='gqr0'&&x.transformBytes[0x13]===0){changed=true;Object.assign(x.rootSources,{processor:{...x.drawProcessor}});}
  });
  if(['capturedDescriptor','capturedMatrix','inputAlias'].includes(fault))check(vector(x,0x30)==='3,5,7','captured identities/live alias input preserved');
  if(fault==='matrixAlias')check(vector(x,0x30)==='3,5,10','X overwrites late matrix8 source before it is read');
  if(['missingM8','readonlyY','lateReadonlyY'].includes(fault))check(vector(x,0x30)==='3,78,79','only earlier X store persists');
  if(['reentryX','helperReentryX','lateInputShape','lateOutputShape'].includes(fault))check(vector(x,0x30)==='77,78,79','late refusal occurs before current transform store');
  if(fault==='lateGqrX')check(vector(x,0x30)==='77,78,79','first W1 store refuses changed GQR before outputs');
  if(fault==='lateGqrY')check(vector(x,0x30)==='3,78,79','second W1 store refuses changed GQR after X only');
  if(['lateGqrZ','lateFpscrZ'].includes(fault))check(vector(x,0x30)==='3,5,79','final W1 store refuses changed controls with prior X/Y retained');
  if(fault==='fma')check(x.allocator.readU32(x.transformId,0x30)===0x28800000,'single-round FMA residual preserved');
  if(fault==='signedZero')check(x.allocator.readU32(x.transformId,0x30)===0x80000000,'negative zero preserved');
  if(fault==='nullInput')check(reads.length===0,'null input refuses before matrix load');
 }
 console.log(`[battle-contact-transform] PASS: ${count} canonical-byte contact transform fixtures; no timer/helper/frame completion`);
}
