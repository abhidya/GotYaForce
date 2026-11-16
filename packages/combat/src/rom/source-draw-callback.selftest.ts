/** Private outer entry cannot be manufactured by a node or caller context.
 * Positive/partial-store tests use genuine89554 fixtures in the outer suite. */
import {executeSourceDrawCallback47aa4} from './source-draw-callback.js';
import type {SourceBattleOuterFrameRuntime} from './battle-outer-frame.js';
export function runSourceDrawCallbackAuthorityTests():void {
  for(const outer of [{},Object.freeze({}),{runFrame(){throw Error('must not call');}}]) {
    let rejected=false;
    try {executeSourceDrawCallback47aa4(outer as SourceBattleOuterFrameRuntime,Symbol('unowned draw object'));}
    catch(error){rejected=String(error).includes('private')||String(error).includes('outer');}
    if(!rejected)throw Error('[source-draw-callback test] forged outer authority accepted');
  }
}

import {createBattleDrawOuterTestFixture} from './battle-draw-outer.selftest.js';
import type {createBattleTargetPreparationTestFixture} from './attached-setup-animation.selftest.js';
type Make=typeof createBattleTargetPreparationTestFixture;
function check(ok:boolean,why:string):void{if(!ok)throw Error('[source-draw-callback-test] '+why);}
function refuses(f:()=>unknown,part:string):void{let text='';try{f();}catch(e){text=String(e);}check(text.includes(part),`expected ${part}, got ${text}`);}
export function runSourceDrawCallbackSelfTests(make:Make):void{
 runSourceDrawCallbackAuthorityTests();let count=0;
 const fresh=()=>{count++;return createBattleDrawOuterTestFixture(make);};
 const stop='800294cc reached outer counter continuation';
 const matrix=(x:ReturnType<typeof fresh>)=>Array.from({length:12},(_,i)=>x.allocator.readF32(x.child,0x114+4*i));
 {
  const x=fresh();refuses(()=>x.frame.runFrame(),stop);
  check(matrix(x).join(',')==='1,0,0,2,0,1,0,3,0,0,1,4','actual14 canonical matrix');
  check(x.objectBytes[0x84]===0x14&&x.drawList.tail===x.child&&x.groups[9]!.head===x.child,'real flags and lists retained');
 }
 for(const fault of ['firstPair','secondPair','gqr5','angle','scale','capturedFlags','reentry','staleGqr','staleFpscr']as const){
  const x=fresh(),native=Object.getOwnPropertyDescriptor;let changed=false;
  if(fault==='firstPair')Object.defineProperty(x.objectBytes,'288',{writable:false});
  if(fault==='secondPair')Object.defineProperty(x.objectBytes,'304',{writable:false});
  if(fault==='gqr5')x.drawProcessor.gqr5=0;
  if(fault==='angle')x.objectBytes[0x73]=1;
  Object.getOwnPropertyDescriptor=((o:object,k:PropertyKey)=>{
   if(!changed&&fault!=='staleGqr'&&fault!=='staleFpscr'&&o===x.drawConstants&&k==='float8043ca6c'){
    changed=true;
    if(fault==='capturedFlags')x.objectBytes[0x84]=0x40;
    if(fault==='reentry')try{x.frame.runFrame();}catch{}
   }
   if(fault==='scale'&&o===x.objectBytes&&k==='88'){
    // Fresh source argument, after real rotation concat: scaleX becomes2.
    x.objectBytes[88]=0x40;x.objectBytes[89]=0;x.objectBytes[90]=0;x.objectBytes[91]=0;
   }
   if(!changed&&o===x.drawProcessor&&((fault==='staleGqr'&&k==='gqr0')||(fault==='staleFpscr'&&k==='fpscrControl'))){const old=native(o,k);changed=true;if(fault==='staleGqr')x.drawProcessor.gqr0=1;else x.drawProcessor.fpscrControl=1;return old;}
   return native(o,k);
  })as typeof native;
  try{refuses(()=>x.frame.runFrame(),fault==='firstPair'||fault==='secondPair'?'paired destination':fault==='gqr5'?'gqr5':fault==='angle'?'nonzero radians':fault==='reentry'?'private exact':fault==='staleGqr'?'gqr0':fault==='staleFpscr'?'FPSCR':stop);}
  finally{Object.getOwnPropertyDescriptor=native;}
  const m=matrix(x);
  if(fault==='staleGqr'||fault==='staleFpscr')check(m.every(v=>v===37),'stale control descriptor never authorizes store');
  if(fault==='firstPair')check(m[2]===37&&m[3]===37,'first pair all-or-none admission');
  if(fault==='secondPair')check(m[2]===0&&m[3]===0&&m[6]===37&&m[7]===37,'earlier pair retained; failed second pair unchanged');
  if(fault==='gqr5'||fault==='angle')check(m.join(',')==='1,0,0,2,0,1,0,3,0,0,1,4','identity/translation survive rotation refusal');
  if(fault==='scale')check(m[0]===2&&m[5]===1&&m[10]===1&&m[3]===2,'live scale after rotation');
  if(fault==='capturedFlags')check(m[0]===1&&x.objectBytes[0x84]===0x40,'flags captured once despite helper-time mutation');
  refuses(()=>x.frame.runFrame(),'permanently incomplete');
 }
 console.log(`[source-draw-callback] PASS: ${count} genuine paused-entry draw fixtures, atomic paired admission, live source fields and closure; not normal frame completion`);
}
