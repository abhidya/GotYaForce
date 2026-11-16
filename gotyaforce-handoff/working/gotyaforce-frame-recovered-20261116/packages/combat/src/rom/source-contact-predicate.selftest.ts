import {readSourceContactPredicate} from './source-contact-predicate.js';
import type {SourceProjectileRootRuntime} from './projectile-root-lifecycle.js';
function check(ok:boolean,s:string):void{if(!ok)throw Error('[source-contact-predicate-test] '+s);}
function refuses(f:()=>unknown,want:string):void{let got='';try{f();}catch(e){got=String(e);}check(got.includes(want),`expected ${want}, got ${got}`);}
/** Read-only arithmetic model fixtures. This root profile fixture is not used
 * by an outer frame or as a substitute for any source lifecycle. */
export function runSourceContactPredicateSelfTests():void{
 let count=0;
 const fresh=()=>{
  count++;const cells:Record<string,number>={},constants:Record<string,number>={float80437004:0.10000000149011612,float80436f68:0,double80436fd0:0.5,double80436fd8:3};
  const processor={fpscrControl:0,gqr0:0},declaration={processor};
  const root={getVectorProcessorProfile:()=>declaration.processor,getRetainedStorageOwners:()=>[declaration]}as unknown as SourceProjectileRootRuntime;
  const set=(address:number,value:number)=>{const d=new DataView(new ArrayBuffer(4));d.setFloat32(0,value,false);cells['word'+address.toString(16)]=d.getUint32(0,false);};
  for(const base of [0x803b04dc,0x803b0374])for(const i of [0,4,8])set(base+i,0);
  set(0x803b04f4,1);set(0x803b038c,1);
  return {cells,constants,processor,declaration,root,set,run:()=>readSourceContactPredicate(cells,constants,root,()=>{})};
 };
 for(const [square,distance]of [[.25,.5],[1,1],[4,2],[16,4],[64,8]]as const){const x=fresh();x.set(0x803b04dc,distance);check(x.run()===(square<=4),'bounded estimate and inclusive result');}
 for(const mode of ['zero','underflow','thresholdA','thresholdB','negative','missingThreshold','thresholdCaptured','thresholdWrong','missingZero','wrongHalf','wrongThree','unsupportedSquare','nan','gqr','fpscr','lateGqr','lateFpscr','profileSwap','liveY','unusedLaneOverflow','reloadRadius','sumOverflow','alias','constantAlias','readonly']as const){
  const x=fresh();let changed=false;const reads:string[]=[];let ayReads=0;
  if(mode==='underflow')x.set(0x803b04dc,2**-149);
  if(['thresholdA','thresholdB','negative'].includes(mode))x.set(mode==='thresholdB'?0x803b038c:0x803b04f4,mode==='negative'?-1:0.10000000149011612);
  if(mode==='thresholdA'||mode==='negative'){delete x.cells.word803b038c;x.processor.gqr0=4;}
  if(mode==='missingThreshold')delete x.constants.float80437004;
  if(mode==='thresholdWrong')x.constants.float80437004=0;
  if(mode==='missingZero')delete x.constants.float80436f68;
  if(mode==='wrongHalf'||mode==='wrongThree'||mode==='unsupportedSquare'||mode==='liveY'||mode==='unusedLaneOverflow'||mode==='reloadRadius')x.set(0x803b04dc,1);
  if(mode==='wrongHalf')x.constants.double80436fd0=1;
  if(mode==='wrongThree')x.constants.double80436fd8=2;
  if(mode==='unsupportedSquare')x.set(0x803b04e0,1);
  if(mode==='nan')x.cells.word803b04f4=0x7fc00001;
  if(mode==='gqr')x.processor.gqr0=4;if(mode==='fpscr')x.processor.fpscrControl=1;
  if(mode==='alias')x.cells.byte803b04f5=0;
  if(mode==='constantAlias')x.cells.float80437004=0.10000000149011612;
  if(mode==='sumOverflow'){x.set(0x803b04f4,3.4028234663852886e38);x.set(0x803b038c,3.4028234663852886e38);}
  if(mode==='readonly')for(const key of Object.keys(x.cells))Object.defineProperty(x.cells,key,{writable:false});
  const native=Object.getOwnPropertyDescriptor;
  Object.getOwnPropertyDescriptor=((o:object,k:PropertyKey)=>{const d=native(o,k);if(o===x.cells||o===x.constants)reads.push(String(k));
   if(o===x.cells&&k==='word803b04e0')ayReads++;
   if(!changed&&mode==='thresholdCaptured'&&o===x.cells&&k==='word803b04f4'){changed=true;x.constants.float80437004=10;}
   if(!changed&&['lateGqr','profileSwap'].includes(mode)&&o===x.cells&&k==='word803b037c'){changed=true;if(mode==='lateGqr')x.processor.gqr0=4;else x.declaration.processor={...x.processor};}
   if(!changed&&['liveY','unusedLaneOverflow'].includes(mode)&&o===x.cells&&k==='word803b04dc'){changed=true;x.set(0x803b04e0,mode==='liveY'?10:3.4028234663852886e38);}
   if(!changed&&mode==='reloadRadius'&&o===x.cells&&k==='word803b0374'){changed=true;x.set(0x803b04f4,-2);}
   if(mode==='lateFpscr'&&o===x.cells&&k==='word803b038c'&&reads.filter(v=>v===String(k)).length===2)x.processor.fpscrControl=1;
   return d;
  })as typeof native;
  const expected=mode==='missingThreshold'?'float80437004':mode==='thresholdWrong'||mode==='wrongHalf'||mode==='wrongThree'?'authenticated constant':mode==='missingZero'?'float80436f68':mode==='unsupportedSquare'?'unsupported frsqrte':mode==='nan'?'finite':mode==='gqr'||mode==='lateGqr'?'GQR0':mode==='fpscr'||mode==='lateFpscr'?'FPSCR':mode==='profileSwap'?'processor owner changed':mode==='unusedLaneOverflow'||mode==='sumOverflow'?'overflow':mode==='alias'||mode==='constantAlias'?'competing':undefined;
  try{if(expected)refuses(x.run,expected);else check(x.run()===!['thresholdA','thresholdB','negative','reloadRadius'].includes(mode),'correct bounded predicate result');}finally{Object.getOwnPropertyDescriptor=native;}
  if(mode==='thresholdA'||mode==='negative')check(!reads.includes('word803b038c')&&!reads.includes('float80436f68'),'early return has no B/zero ingress');
  if(mode==='thresholdB')check(!reads.includes('word803b04e0'),'second radius rejection skips vector');
  if(mode==='liveY')check(ayReads===2,'live repeatedY keeps old squared lane and fresh unused lane');
  if(mode==='unsupportedSquare')check(!reads.includes('double80436fd0'),'unknown estimator refuses before double loads');
  if(mode==='zero'||mode==='underflow')check(!reads.includes('double80436fd0')&&!reads.includes('double80436fd8'),'actual rounded zero avoids estimator');
  if(mode==='missingThreshold')check(reads.join(',')==='float80437004','threshold load precedes radius load');
 }
 console.log(`[source-contact-predicate] PASS: ${count} exact-order bounded read-only predicate cases`);
}
