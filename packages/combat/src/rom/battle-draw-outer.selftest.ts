import {consumeSourceBattleOuterDrawInvocation,checkSourceBattleOuterDrawInvocation} from './battle-outer-frame.js';
import {createBattleParticipantViewTestFixture} from './battle-participant-view.selftest.js';
import type {createBattleTargetPreparationTestFixture} from './attached-setup-animation.selftest.js';
type Make=typeof createBattleTargetPreparationTestFixture;
/** Explicit paused-entry draw input, NOT output of the unfinished projectile
 * initializer and NOT a normal completed battle frame. Original group9 stays. */
export function createBattleDrawOuterTestFixture(make:Make){
 const x=createBattleParticipantViewTestFixture(make,true);
 const processor=Object.assign(x.actionSources.processor,{fpscrControl:0,gqr5:0x00070007});
 Object.assign(x.rootSources,{processor});
 const scratch=new Float32Array(12),factor=new DataView(new ArrayBuffer(4));factor.setUint32(0,0x38c90fdb,false);
 const constants={float8043ca6c:0,float8043ca68:1,float804370e0:factor.getFloat32(0,false),double8043d030:1,float80435ca0:0,float80435ca4:1};
 const objectUpdates={roots36290:{1:null},roots36280:{0:null,1:null},roots6f54:{0:null,1:null,2:null,3:null,4:null,5:null},draw:{constants,scratch}};
 Object.assign(x.outerSources,{objectUpdates});
 const write=(offset:number,value:number,float=false,width=4)=>{const data=new DataView(new ArrayBuffer(4));if(float)data.setFloat32(0,value,false);else if(width===2)data.setUint16(0,value,false);else data.setUint32(0,value,false);for(let i=0;i<width;i++)x.objectBytes[offset+i]=data.getUint8(i);};
 x.objectBytes[0x84]=0x14;write(0x100,0x80047aa4);write(0x108,0);write(0x72,0,false,2);
 for(const [offset,value]of [[0x20,2],[0x24,3],[0x28,4],[0x58,1],[0x5c,1],[0x60,1]]as const)write(offset,value,true);
 for(let i=0;i<12;i++)write(0x114+i*4,37,true);
 x.drawList.head=x.child;x.drawList.tail=x.child;
 return Object.assign(x,{drawProcessor:processor,drawConstants:constants,drawScratch:scratch,objectUpdates});
}
function check(ok:boolean,why:string):void{if(!ok)throw Error('[battle-draw-outer-test] '+why);}
function refuses(f:()=>unknown,part:string):void{let m='';try{f();}catch(e){m=String(e)}check(m.includes(part),`expected ${part}, got ${m}`);}
export function runBattleDrawOuterSelfTests(make:Make):void{
 let count=0;const fresh=()=>{count++;return createBattleDrawOuterTestFixture(make);};
 const stop='800294cc reached outer counter continuation';
 {
  const x=fresh();refuses(()=>x.frame.runFrame(),stop);
  check(Array.from({length:12},(_,i)=>x.allocator.readF32(x.child,0x114+4*i)).join(',')==='1,0,0,2,0,1,0,3,0,0,1,4','actual flags14 output in same allocated114');
  check(x.groups[9]!.head===x.child&&x.drawList.tail===x.child,'no relocation or emptied source draw list');
 }
 {
  const x=fresh(),native=Object.getOwnPropertyDescriptor,seen:string[]=[];
  Object.getOwnPropertyDescriptor=((o:object,k:PropertyKey)=>{for(const name of ['roots36290','roots36280','roots6f54']as const)if(o===x.objectUpdates[name]&&/^\d+$/.test(String(k))&&!(name==='roots36290'&&k==='0'))seen.push(name+':'+String(k));return native(o,k);})as typeof native;
  try{refuses(()=>x.frame.runFrame(),stop);}finally{Object.getOwnPropertyDescriptor=native;}
  check(seen.join(',')==='roots36290:1,roots36280:0,roots36280:1,roots6f54:0,roots6f54:1,roots6f54:2,roots6f54:3,roots6f54:4,roots6f54:5','source root load order');
 }
 {
  const x=fresh();for(let i=0;i<4;i++)x.objectBytes[0x100+i]=0;
  Object.assign(x.objectUpdates.roots36280,{0:x.child});refuses(()=>x.frame.runFrame(),stop);
  check(x.allocator.readF32(x.child,0x114)===37,'nullcallback no-op at both reached roots without global dedup');
 }
 {
  const x=fresh();x.objectBytes[0x103]=0xa5;Object.defineProperty(x.objectBytes,'264',{get(){throw Error('next must not be read');},configurable:true});
  refuses(()=>x.frame.runFrame(),'unsupported callback100');check(x.allocator.readF32(x.child,0x114)===37,'unknown callback refuses before matrix and next');
 }
 {
  const x=fresh(),native=Object.getOwnPropertyDescriptor;let changed=false;
  Object.getOwnPropertyDescriptor=((o:object,k:PropertyKey)=>{if(!changed&&o===x.drawConstants&&k==='float8043ca6c'){changed=true;Object.assign(x.objectUpdates.roots36290,{1:x.child});}return native(o,k);})as typeof native;
  try{refuses(()=>x.frame.runFrame(),stop);}finally{Object.getOwnPropertyDescriptor=native;}
  check(changed&&x.allocator.readF32(x.child,0x120)===2,'later root accepts actual callback-time update and repeats same node');
 }
 {
  const x=fresh();Object.assign(x.objectUpdates.roots36290,{0:null});refuses(()=>x.frame.runFrame(),'0: competing source cell owner');
 }
 {
  const x=fresh();refuses(()=>consumeSourceBattleOuterDrawInvocation(x.frame,x.child),'private');refuses(()=>checkSourceBattleOuterDrawInvocation(x.frame,x.child),'private');
  refuses(()=>x.frame.runFrame(),stop);refuses(()=>x.frame.runFrame(),'permanently incomplete');
 }
 console.log(`[battle-draw-outer] PASS: ${count} explicit paused-entry source traversal fixtures; not normal frame completion`);
}
