import {createSourcePlayerContactTestFixture} from './source-player-contact.selftest.js';
import {consumeSourceBattleOuterDrawInvocation} from './battle-outer-frame.js';
import type {createBattleTargetPreparationTestFixture} from './attached-setup-animation.selftest.js';
type Make=typeof createBattleTargetPreparationTestFixture;
function check(ok:boolean,why:string):void{if(!ok)throw Error('[battle-late-draw-test] '+why);}
function refuses(f:()=>unknown,want:string):void{let got='';try{f();}catch(e){got=String(e);}check(got.includes(want),`expected ${want}, got ${got}`);}
/** Populated synthetic paused-entry roots, not normal initializer output. */
export function createBattleLateDrawTestFixture(make:Make){
 const x=createSourcePlayerContactTestFixture(make);
 const roots36270:{[key:number]:symbol|null}={0:x.child,1:x.child};
 Object.assign(x.objectUpdates.roots36280,{0:x.child,1:x.child});
 Object.assign(x.objectUpdates,{roots36270});
 return Object.assign(x,{roots36270});
}
export function runBattleLateDrawSelfTests(make:Make):void{
 let count=0;const fresh=()=>{count++;return createBattleLateDrawTestFixture(make);};
 const stop='80029504 reached outer post-draw continuation';
 const observe=(f:()=>void,hook:(o:object,k:PropertyKey)=>void):void=>{const native=Object.getOwnPropertyDescriptor;Object.getOwnPropertyDescriptor=((o:object,k:PropertyKey)=>{hook(o,k);return native(o,k);})as typeof native;try{f();}finally{Object.getOwnPropertyDescriptor=native;}};
 {
  const x=fresh(),seen:string[]=[];
  observe(()=>refuses(()=>x.frame.runFrame(),stop),(o,k)=>{if(k==='0'||k==='1'){if(o===x.objectUpdates.roots36280)seen.push('80:'+String(k));if(o===x.roots36270)seen.push('70:'+String(k));}});
  check(seen.join(',')==='80:0,80:1,80:0,80:1,70:0,70:1','same80 roots traversed twice then distinct70 roots');
  check(x.groups[9]!.head===x.child&&x.drawList.tail===x.child,'original populated source roots retained');
  check(x.allocator.readF32(x.child,0x120)===2,'actual callback wrote canonical matrix');
  refuses(()=>consumeSourceBattleOuterDrawInvocation(x.frame,x.child),'private');refuses(()=>x.frame.runFrame(),'permanently incomplete');
 }
 {
  const x=fresh();let visits=0;
  observe(()=>refuses(()=>x.frame.runFrame(),stop),(o,k)=>{
   if((o===x.objectUpdates.roots36280||o===x.roots36270)&&(k==='0'||k==='1')){
    check(x.allocator.readF32(x.child,0x120)===(visits===0?2:visits*10),'previous actual callback completes before fresh next root');
    visits++;x.allocator.writeF32(x.child,0x20,visits*10);
   }
  });
  check(visits===6&&x.allocator.readF32(x.child,0x120)===60,'each repeated source root executes real47aa4, no deduplication');
 }
 for(const fault of ['freshRoot','replace80','alias70','zero','unsupported','partial','reentry','normal','missing70','sameTable','liveNext','capturedHead','lateOwner','lateAlias']as const){
  const x=fresh();let contact=false,late=false,changed=false;
  if(fault==='missing70')delete (x.objectUpdates as {roots36270?:object}).roots36270;
  if(fault==='sameTable')Object.assign(x.objectUpdates,{roots36270:x.objectUpdates.roots36280});
  observe(()=>refuses(()=>x.frame.runFrame(),(fault==='replace80'||fault==='lateOwner')?'changed':(fault==='alias70'||fault==='lateAlias')?'competing':fault==='unsupported'?'unsupported callback100':fault==='partial'?'writable':fault==='liveNext'?'cyclic':fault==='reentry'?'reentry':fault==='normal'?'required8008a28c':fault==='missing70'?'explicit roots36270':fault==='sameTable'?'alias':stop),(o,k)=>{
   if(o===x.slotRecords[0]&&k==='contact26f')contact=true;
   if(fault==='normal'&&!changed&&o===x.match&&k==='byte66'&&x.match.wordB0===0){changed=true;x.match.byte66=0;}
   if(contact&&o===x.objectUpdates.roots36280&&k==='0'){
    late=true;
    if(!changed&&fault==='replace80'){changed=true;Object.assign(x.objectUpdates,{roots36280:{...x.objectUpdates.roots36280}});}
    if(!changed&&fault==='zero'){changed=true;for(let i=0;i<4;i++)x.objectBytes[0x100+i]=0;delete (x.objectUpdates.draw as {constants?:object}).constants;}
    if(!changed&&fault==='unsupported'){changed=true;x.objectBytes[0x103]=0xa5;}
   }
   if(late&&o===x.roots36270&&k==='0'&&!changed){
    if(fault==='alias70'){changed=true;Object.assign(x.objectUpdates,{'36270':x.roots36270});}
    if(fault==='freshRoot'){changed=true;x.roots36270[1]=null;}
    if(fault==='partial'){changed=true;x.allocator.writeF32(x.child,0x58,2);Object.defineProperty(x.objectBytes,String(0x114+20),{writable:false});}
    if(fault==='reentry'){changed=true;try{x.frame.runFrame();}catch{}}
   }
   if(late&&o===x.roots36270&&k==='0')late=true;
   if(late&&!changed&&o===x.drawConstants&&k==='float8043ca6c'&&['liveNext','capturedHead','lateOwner','lateAlias'].includes(fault)){
    changed=true;
    if(fault==='liveNext')x.allocator.writePointer(x.child,0x108,x.child);
    if(fault==='capturedHead')x.objectUpdates.roots36280[0]=null;
    if(fault==='lateOwner')Object.assign(x.outerSources,{objectUpdates:{...x.objectUpdates}});
    if(fault==='lateAlias')Object.assign(x.objectUpdates,{'36280':x.objectUpdates.roots36280});
   }
  });
  if(fault!=='normal')check(Object.values(x.slotRecords).every(r=>r.contact26f===0),'all earlier contact writes retained');
  else check(Object.values(x.slotRecords).every(r=>r.contact26f===77),'normal predecessors not skipped');
  if(fault==='partial')check(x.allocator.readF32(x.child,0x120)===0&&x.allocator.readF32(x.child,0x128)===1,'earlier Identity pair persists; failing pair second lane unchanged');
  if(fault==='freshRoot')check(x.roots36270[1]===null,'future source root is loaded live');
  refuses(()=>x.frame.runFrame(),'permanently incomplete');
 }
 console.log(`[battle-late-draw] PASS: ${count} populated source-root fixtures; exact mandatory late calls, no completed normal frame claim`);
}
