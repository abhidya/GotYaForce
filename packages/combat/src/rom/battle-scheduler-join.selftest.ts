import {createBattleParticipantViewTestFixture} from './battle-participant-view.selftest.js';
import {invokeSourceObjectSchedulerOuterFrame,requireSourceObjectSchedulerSnapshot} from './source-object-scheduler.js';
import {markIncompleteSourceProjectileScheduledRoot} from './projectile-root-lifecycle.js';
import {hasIncompleteSourceActorDoubleLifecycle,isSourceActorDoubleFrameClaimed} from './actor-double-prehook.js';
import type {SourceAllocationBytes} from './source-object-allocation.js';
import type {createBattleTargetPreparationTestFixture} from './attached-setup-animation.selftest.js';
type Make=typeof createBattleTargetPreparationTestFixture;
type Fixture=ReturnType<typeof createBattleParticipantViewTestFixture>;
type Visit=(owner:object,key:PropertyKey)=>void;
const NORMAL='80029488 reached mandatory80053a2c',NONZERO='800294c8 reached mandatory80089554';
const ORDER=[41,42,43,44,45,46,40,47,33,34,35,36,37,38,32,39];
let fixtures=0;
function check(ok:boolean,why:string):void{if(!ok)throw Error('[battle-scheduler-join-test] '+why);}
function equal(a:unknown,b:unknown,why:string):void{check(Object.is(a,b),`${why}: got ${String(a)}, expected ${String(b)}`);}
function refuses(run:()=>unknown,part:string):string{let message='';try{run();}catch(error){message=String(error);}check(message.includes(part),`expected ${part}, got ${message||'success'}`);return message;}
function makeFixture(make:Make,nonzero=false):Fixture{fixtures++;return createBattleParticipantViewTestFixture(make,nonzero);}
function closed(x:Fixture):void{
 check(hasIncompleteSourceActorDoubleLifecycle(x.sourceActor),'whole retained projectile owner closes');
 for(const actor of x.actors)check(!isSourceActorDoubleFrameClaimed(actor),'scheduler does not grant55568 actor lifecycle authority');
 refuses(()=>x.frame.runFrame(),'incomplete');refuses(()=>x.allocator.writeU8(x.nextChild,0,1),'incomplete');
 refuses(()=>x.root.dispatchStoredRoot(x.child),'exclusively owned');
 refuses(()=>requireSourceObjectSchedulerSnapshot(x.scheduler,x.allocator,x.child),'private active');
}
function run(x:Fixture,expected=x.paused?NONZERO:NORMAL,visit:Visit=()=>{}){
 const native=Object.getOwnPropertyDescriptor,groups:number[]=[],slots:number[]=[],masks:string[]=[];
 let inParticipant=false,started=false;
 Object.getOwnPropertyDescriptor=((owner:object,key:PropertyKey)=>{
  if(owner===x.system&&key==='byte40')inParticipant=true;
  if(inParticipant&&owner===x.match&&key==='byte66')started=true;
  if(started){
   if(owner===x.groups&&/^\d+$/.test(String(key)))groups.push(Number(key));
   if(owner===x.actorSlots&&/^[0-5]$/.test(String(key)))slots.push(Number(key));
   if(owner===x.match&&['maskD1','maskD2'].includes(String(key)))masks.push(String(key));
   visit(owner,key);
  }
  return native(owner,key);
 }) as typeof native;
 let message='';try{message=refuses(()=>x.frame.runFrame(),expected);}finally{Object.getOwnPropertyDescriptor=native;}
 check(started,'fresh mode load reached after real participant binding');closed(x);
 equal(x.match.halfD6,0x1234,'unrequested mode-counter reset is not manufactured');
 equal(x.groups[9]!.head,x.child,'genuinely allocated projectile remains in source group9');
 return{groups,slots,masks,message};
}
function normal(make:Make):void{
 const x=makeFixture(make),before=[x.objectBytes,x.nextObjectBytes].map(bytes=>JSON.stringify(bytes)),r=run(x);
 [x.objectBytes,x.nextObjectBytes].forEach((bytes,i)=>equal(JSON.stringify(bytes),before[i],'unreached projectile bytes unchanged: no snapshot, callback or latch reset'));
 equal(r.groups.join(','),ORDER.join(','),'genuine89a94 wrapper order');
 equal(r.slots.join(','),'0,1,2,3,4,5,0,1,2,3,4,5','both wrappers reread all six slots');
 equal(r.masks.length,14,'live per-active-slot and base pause reads');
 check(r.masks.every(mask=>mask==='maskD1'),'these wrappers use D1 only');
 equal(x.massPreparation.orderCount.count80436260,6,'genuine earlier mass returns preserved');
 for(let i=0;i<6;i++)equal(x.actors[i]!.pointer330,x.physicalIdentities[4+(i&1)],'completed leader stores survive scheduler boundary');
 for(let i=0;i<4;i++)equal(x.actors[i]!.byte487,i,'completed participant stores survive scheduler boundary');
}
function nonzero(make:Make):void{
 for(const mode of [1,127,128,255]){
  const x=makeFixture(make,true);x.match.byte66=mode;
  const r=run(x,NONZERO,(o,k)=>{if(o===x.match&&k==='byte66'){
   // After bef4, neither89898 call may read pause masks or slot pointers.
   for(const key of ['maskD1','maskD2'])Object.defineProperty(x.match,key,{get(){throw Error('nonzero mask read');},configurable:true});
   for(let i=0;i<6;i++)Object.defineProperty(x.actorSlots,String(i),{get(){throw Error('nonzero slot read');},configurable:true});
  }});
  equal(r.groups.join(','),'58,57','genuine89898 source order');equal(r.slots.length,0,'nonzero no slot scalar reads');equal(r.masks.length,0,'nonzero no pause scalar reads');
 }
}
function live(make:Make):void{
 {
  const x=makeFixture(make);x.match.maskD1=0x80;
  const r=run(x);equal(r.groups.join(','),ORDER.filter(group=>group!==40&&group!==32).join(','),'global pause alone preserves eligible slot groups and +7');
 }
 {
  const x=makeFixture(make);let changed=false;
  const r=run(x,NORMAL,(o,k)=>{if(!changed&&o===x.groups&&k==='41'){changed=true;x.match.maskD1=0xff;}});
  equal(r.groups.join(','),'41,47,39','live slot and global pause suppress later slot groups and both bases, not +7');
 }
 {
  const x=makeFixture(make);let changed=false;
  const r=run(x,NORMAL,(o,k)=>{if(!changed&&o===x.groups&&k==='41'){changed=true;x.actors[1]!.active0=0;x.match.maskD1=4;}});
  equal(r.groups.join(','),'41,44,45,46,40,47,33,36,37,38,32,39','fresh inactive and per-slot pause skip only eligible groups');
 }
 {
  const x=makeFixture(make);let changed=false;
  run(x,'head: own data property',(o,k)=>{if(!changed&&o===x.groups&&k==='41'){changed=true;delete x.groups[41]!.head;}});
  check(changed,'missing explicit source head is not defaulted');
 }
}
function inactiveAndUnsupported(make:Make):void{
 {
  const x=makeFixture(make),first=Symbol('explicit inactive list record'),second=Symbol('explicit inactive next record');
  const a:SourceAllocationBytes={0:0,8:0,9:0,10:0,11:0},b:SourceAllocationBytes={0:0,8:0,9:0,10:0,11:0};
  x.allocator.registerObject(first,a);x.allocator.registerObject(second,b);x.groups[41]!.head=first;x.groups[41]!.tail=second;
  x.allocator.writePointer(first,8,second);const next=[8,9,10,11].map(offset=>a[offset]!);for(const offset of [8,9,10,11])a[offset]=0;
  let activeReads=0,switched=false;
  const r=run(x,NORMAL,(o,k)=>{if(o===a&&k==='0'){activeReads++;if(!switched){switched=true;for(let i=0;i<4;i++)a[8+i]=next[i]!;}}if(o===b&&k==='0')activeReads++;});
  equal(activeReads,2,'inactive nodes traverse fresh live next without callback or snapshot fields');equal(r.groups.join(','),ORDER.join(','),'inactive lists return to next wrapper');
  check(!Object.hasOwn(a,0x20)&&!Object.hasOwn(b,0x20),'inactive missing snapshot fields remain absent');
 }
 {
  const x=makeFixture(make),id=Symbol('explicit unsupported active object'),bytes:SourceAllocationBytes={0:1};
  x.allocator.registerObject(id,bytes);x.groups[41]!.head=id;x.groups[41]!.tail=id;
  const r=run(x,'unknown/non-owned projectile');equal(r.groups.join(','),'41','unsupported active callback stops before later groups');
  check(!Object.hasOwn(bytes,0x2c),'domain refusal precedes any snapshot store');
 }
}
function authority(make:Make):void{
 for(const variant of ['idle','copied-outer','copied-scheduler','foreign'] as const){
  const x=makeFixture(make,true),y=variant==='foreign'?makeFixture(make,true):undefined;
  refuses(()=>invokeSourceObjectSchedulerOuterFrame(variant==='copied-scheduler'?{...x.scheduler}:x.scheduler,
   variant==='copied-outer'?{...x.frame}:y?.frame??x.frame,0x800294bc,58),variant==='copied-scheduler'?'genuine scheduler':variant==='idle'?'private':'exact outer-owned scheduler');
 }
 for(const operation of ['public','outer','root','root-closure','snapshot','copied-scheduler','copied-outer','replayed','out-of-order','wrong-group','foreign'] as const){
  const x=makeFixture(make,true),other=operation==='foreign'?makeFixture(make,true):undefined;let attempted=false;
  run(x,'reentry',(o,k)=>{if(!attempted&&o===x.groups&&k==='58'){
   attempted=true;try{
    if(operation==='public')x.scheduler.runGroup(57);
    else if(operation==='outer')x.frame.runFrame();
    else if(operation==='root')x.root.dispatchStoredRoot(x.child);
    else if(operation==='root-closure')markIncompleteSourceProjectileScheduledRoot(x.root,x.scheduler);
    else if(operation==='snapshot')requireSourceObjectSchedulerSnapshot(x.scheduler,x.allocator,x.child);
    else invokeSourceObjectSchedulerOuterFrame(operation==='copied-scheduler'?{...x.scheduler}:x.scheduler,
     operation==='copied-outer'?{...x.frame}:other?.frame??x.frame,
     operation==='out-of-order'?0x800294c4:0x800294bc,operation==='wrong-group'||operation==='out-of-order'?57:58);
   }catch{/* Deliberately caught: the enclosing graph still must close. */}
  }});check(attempted,'active misuse exercised');
 }
}
function aliases(make:Make):void{
 for(const target of ['row','table'] as const){
  const x=makeFixture(make),row=x.groups[47]!;let changed=false;
  const r=run(x,'canonical owner changed',(o,k)=>{if(!changed&&o===row&&k==='head'){
   changed=true;if(target==='row')x.groups[47]={head:null,tail:null};else x.allocatorSources.groups={...x.groups};
  }});
  check(changed,'late retained group '+target+' replacement exercised');
  equal(r.groups.join(','),'41,42,43,44,45,46,40,47','stale head cannot authorize continuation into second wrapper');
 }

 for(const kind of ['system','leader-row','participant-row'] as const){
  const x=makeFixture(make,true),alias=kind==='system'?x.system:kind==='leader-row'?x.teamRows103[0]!:x.slotRecords[0]!;
  // Source lists may not reinterpret a retained distinct semantic owner.
  const group=Object.assign(alias,{head:null,tail:null});
  run(x,'alias',(o,k)=>{if(o===x.match&&k==='byte66')x.groups[58]=group;});
 }
}
export function runBattleSchedulerJoinSelfTests(make:Make):void{
 fixtures=0;normal(make);nonzero(make);live(make);inactiveAndUnsupported(make);authority(make);aliases(make);
 console.log(`[battle-scheduler-join] PASS (${fixtures} explicit shared-owner fixtures): real40/32 wrappers and58/57 groups; live pause/eligibility/next, absent-input and active-domain refusal, exact private authority and cross-layer closure;53a2c/89554, actor55568 and full frame remain unsupported`);
}
