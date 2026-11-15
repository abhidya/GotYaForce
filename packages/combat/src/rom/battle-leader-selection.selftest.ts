import {createActorThirdPassTestFixture} from './actor-third-pass.selftest.js';
import {hasIncompleteSourceActorDoubleLifecycle,isSourceActorDoubleFrameClaimed,markIncompleteSourceActorDoubleLifecycle} from './actor-double-prehook.js';
import {requireSourceObjectSchedulerSnapshot} from './source-object-scheduler.js';
import type {RomActor} from './actor.js';
import type {createBattleTargetPreparationTestFixture} from './attached-setup-animation.selftest.js';
type Make=typeof createBattleTargetPreparationTestFixture;
type Visit=(owner:object,key:PropertyKey)=>void;
const NEXT='byte40: own data property required',HIGH='byte804360c7',LOW='byte804360c6';
let fixtures=0;
function check(ok:boolean,why:string):void {if(!ok)throw Error(`[battle-leader-selection-test] ${why}`);}
function equal(a:unknown,b:unknown,why:string):void {check(Object.is(a,b),`${why}: got ${String(a)}, expected ${String(b)}`);}
function refuses(run:()=>unknown,part:string):string {let message='';try{run();}catch(e){message=String(e);}check(message.includes(part),`expected ${part}, got ${message||'success'}`);return message;}
/** Six distinct active actors from ENTRY, each in the same genuine world,
 * status, stage, action and admission registries. Lifecycle0 legitimately skips
 * target selection while still executing all six mass/target preparation rows.
 * No activation hook, successful callback or retail constructor is supplied. */
export function createBattleLeaderSelectionTestFixture(make:Make) {
 fixtures++;const x=createActorThirdPassTestFixture(make,undefined,true),actors=x.physicalActors as RomActor[];
 for(const [i,id]of x.physicalIdentities.entries()) {
  x.actorSlots[i]=id;
  const actor=actors[i]!,borg=x.status.getActualBorg(id);
  if(i===0)x.stageState.lifecycle18=0;else x.stageBounds.bindActor(id,{lifecycle18:0});
  borg.sourceArrowMass204=70+i;
  Object.assign(actor,{active0:1,mass208:80+i,supportContact1db:0,field664:90+i,slot:i,
   team:i&1,byte58a:91,byte58b:92,byte58c:93,byte58d:94,byte7d3:95,
   byte334:i,byte335:77,pointer330:Symbol('old leader word')});
  x.world.getActorBinding(id).mode4a0=2;
 }
 for(const row of x.teamRows103)Object.assign(row,{pointer38:Symbol('old row word')});
 return Object.assign(x,{actors});
}
type Fixture=ReturnType<typeof createBattleLeaderSelectionTestFixture>;
function seed(low:number,high:number):[number,number] {const h=Math.floor((high*256+low)*3/256)&255;return[(low+h)&255,h];}
function afterDraws(x:Fixture,n:number):[number,number] {let state:[number,number]=[x.massPreparation.rngState[LOW],x.massPreparation.rngState[HIGH]];for(let i=0;i<n;i++)state=seed(...state);return state;}
function closed(x:Fixture):void {
 for(const actor of x.actors) {check(hasIncompleteSourceActorDoubleLifecycle(actor),'all six retained actors close');check(!isSourceActorDoubleFrameClaimed(actor),'no actor frame authority');}
 refuses(()=>x.frame.runFrame(),'permanently incomplete');
 for(const f of [()=>x.scheduler.runGroup(9),()=>x.scheduler.runSlots(8),()=>x.scheduler.runWrapper(8),()=>x.root.dispatchStoredRoot(x.child)])refuses(f,'exclusively owned');
 refuses(()=>requireSourceObjectSchedulerSnapshot(x.scheduler,x.allocator,x.child),'private active');
}
function run(x:Fixture,expected=NEXT,before:Visit=()=>{},after:Visit=()=>{}) {
 const native=Object.getOwnPropertyDescriptor,events:string[]=[];let highReads=0,started=false,schedulerReads=0;
 Object.getOwnPropertyDescriptor=((owner:object,key:PropertyKey)=>{
  if(owner===x.massPreparation.rngState&&key===HIGH&&++highReads===5)started=true;
  if(started) {
   if(owner===x.massPreparation.rngState&&(key===HIGH||key===LOW))events.push('rng.'+String(key));
   if(owner===x.actorSlots&&/^[0-5]$/.test(String(key)))events.push('slot'+String(key));
   const row=x.teamRows103.indexOf(owner as typeof x.teamRows103[number]);
   if(row>=0&&key==='pointer38')events.push('row'+row+'.38');
   const actor=x.actors.indexOf(owner as RomActor);
   if(actor>=0&&['active0','team','byte334','byte335','pointer330'].includes(String(key)))events.push('a'+actor+'.'+String(key));
   if(owner===x.groups&&/^\d+$/.test(String(key))||owner===x.matchGlobals&&['maskD1','maskD2'].includes(String(key)))schedulerReads++;
   before(owner,key);
  }
  const result=native(owner,key);if(started)after(owner,key);return result;
 }) as typeof native;
 let message='';try{message=refuses(()=>x.frame.runFrame(),expected);}finally{Object.getOwnPropertyDescriptor=native;}
 check(started,'genuine mass and target returns reach third RNG call');equal(schedulerReads,0,'no scheduler read');closed(x);return{events,message};
}
function upstream(x:Fixture):void {
 equal(new Set(Object.values(x.actorSlots)).size,6,'six DISTINCT live pointers from entry');
 equal(x.massPreparation.orderCount.count80436260,6,'real six-actor mass ordering completed');
 equal(new Set(Object.values(x.massPreparation.orderPointers)).size,6,'ordering keeps all six identities');
 for(const [i,id]of x.physicalIdentities.entries()) {
  equal(x.status.getActualBorg(id).sourceArrowMass204,0,'each genuine mass owner cleared and accumulated');
  equal(x.actors[i]!.mass208,0,'lifecycle0 supplies real zero mass');equal(x.actors[i]!.field664,1,'all six ordering resets');
  for(const key of ['byte58a','byte58b','byte58c','byte58d','byte7d3'])equal(Reflect.get(x.actors[i]!,key),0,'all six target clears');
  equal(x.commandAdmission.getActionBinding(id).byte7d2,0,'sealed genuine action7d2 cleared');
  equal(x.commandAdmission.getActorBinding(id).pointer508,null,'genuine null508 remains');
 }
}
function baseline(make:Make):void {
 const x=createBattleLeaderSelectionTestFixture(make),finalSeed=afterDraws(x,3),r=run(x);upstream(x);
 equal(x.massPreparation.rngState[LOW],finalSeed[0],'third discarded RNG return still advances low');equal(x.massPreparation.rngState[HIGH],finalSeed[1],'shared high advances');
 const expected=['rng.'+HIGH,'rng.'+LOW,'rng.'+HIGH,'rng.'+LOW,'slot2','row0.38','slot1','row1.38','row2.38','row3.38','slot0'];
 for(let i=0;i<6;i++)expected.push(`a${i}.active0`,`a${i}.byte335`,`a${i}.pointer330`,`a${i}.team`,`a${i}.byte334`);
 for(const group of [0,1]) {
  expected.push(`a${group+4}.byte335`,'slot0');
  for(let i=0;i<6;i++)expected.push(`a${i}.active0`,`a${i}.team`,...(i%2===group?[`a${i}.pointer330`]:[]));
 }
 equal(r.events.join(','),expected.join(','),'complete source scalar/store order');
 for(let i=0;i<6;i++){equal(x.actors[i]!.byte335,i>=4?1:0,'last best leader marker');equal(x.actors[i]!.pointer330,x.physicalIdentities[4+(i&1)],'pointer330 holds same canonical identity, including self');}
 for(const [i,value]of [x.physicalIdentities[2],x.physicalIdentities[1],null,null].entries())equal(Reflect.get(x.teamRows103[i]!,'pointer38'),value,'row38 is initial copy, not leader');
}
function branches(make:Make):void {
 for(const scores of [[0,0,0,0,0,0],[127,255,126,128,0,0],[255,128,254,129,128,255],[1,2,1,2,1,2]]) {
  const x=createBattleLeaderSelectionTestFixture(make);x.actors.forEach((a,i)=>a.byte334=scores[i]!);run(x);
  const selected:(number|undefined)[]=[undefined,undefined],best=[0,0];
  for(let i=0;i<6;i++){const group=i&1,score=scores[i]!<<24>>24;if(score>=best[group]!){selected[group]=i;best[group]=score;}}
  for(let i=0;i<6;i++){const n=selected[i&1];equal(x.actors[i]!.pointer330,n===undefined?null:x.physicalIdentities[n],'signed score and last tie');equal(x.actors[i]!.byte335,selected.includes(i)?1:0,'selected marker only');}
 }
 for(const team of [2,127,128,255]) {
  const x=createBattleLeaderSelectionTestFixture(make);let getters=0;
  for(const a of x.actors){a.team=team;Object.defineProperty(a,'byte334',{get(){getters++;throw Error('unreached score');},configurable:true});}
  const r=run(x);equal(getters,0,'other signed teams never load334');equal(r.events.filter(e=>e==='slot0').length,1,'null leaders skip publication base reloads');
  for(const a of x.actors){equal(a.byte335,0,'all active non-team markers clear');equal(a.pointer330,null,'all active non-team pointer words clear');}
 }
 for(const active of [128,255]) {
  const x=createBattleLeaderSelectionTestFixture(make);for(const a of x.actors)a.active0=active;run(x);upstream(x);equal(x.actors[4]!.byte335,1,'signed negative active byte still active');
 }
 {
  const x=createBattleLeaderSelectionTestFixture(make);x.actors[5]!.active0=0;delete x.actors[5]!.byte334;delete x.actors[5]!.byte335;delete x.actors[5]!.pointer330;
  run(x);check(!Object.hasOwn(x.actors[5]!,'pointer330'),'inactive actor gets no synthesized pointer');equal(x.actors[3]!.byte335,1,'inactive higher score is not a candidate');
 }
 for(const mode of [1,128,255]) {
  const x=createBattleLeaderSelectionTestFixture(make),before=afterDraws(x,0);x.matchGlobals.byte66=mode;
  refuses(()=>x.frame.runFrame(),NEXT);equal(x.massPreparation.rngState[LOW],before[0],'paused branch does not advance RNG');equal(x.massPreparation.rngState[HIGH],before[1],'paused high unchanged');
  for(const a of x.actors){equal(a.byte335,77,'paused branch leaves leader cells');check(typeof a.pointer330==='symbol','paused pointer unchanged');}
 }
}
function failures(make:Make):void {
 // Each store's failure keeps the exact preceding writes and never later rows.
 for(let row=0;row<4;row++)for(const fault of ['missing','readonly','accessor'] as const) {
  const x=createBattleLeaderSelectionTestFixture(make),seed3=afterDraws(x,3);let getter=0;
  if(fault==='missing')Reflect.deleteProperty(x.teamRows103[row]!,'pointer38');
  else Object.defineProperty(x.teamRows103[row]!,'pointer38',fault==='readonly'?{writable:false}:{get(){getter++;throw Error('setter/getter');},configurable:true});
  run(x,fault==='readonly'?'pointer38: non-writable':'pointer38: own data');equal(getter,0,'destination accessor never executes');
  equal(x.massPreparation.rngState[LOW],seed3[0],'RNG complete before first row destination');
  for(let i=0;i<row;i++)equal(Reflect.get(x.teamRows103[i]!,'pointer38'),i===0?x.physicalIdentities[2]:i===1?x.physicalIdentities[1]:null,'prior row copy survives');
  for(const a of x.actors)equal(a.byte335,77,'no actor clear before four row stores');
 }
 for(const field of ['byte335','pointer330','byte334'] as const)for(const fault of ['missing','readonly','accessor'] as const) {
  if(field==='byte334'&&fault==='readonly')continue;
  const x=createBattleLeaderSelectionTestFixture(make),a=x.actors[2]!;let getter=0;
  if(fault==='missing')Reflect.deleteProperty(a,field);
  else Object.defineProperty(a,field,fault==='readonly'?{writable:false}:{get(){getter++;throw Error('uninvoked field');},configurable:true});
  const r=run(x,field+': '+(fault==='readonly'?'non-writable':'own data'));equal(getter,0,'own-data refusal does not call accessor');
  equal(x.actors[0]!.pointer330,null,'earlier actor clear survives');equal(x.actors[3]!.byte335,77,'later actor never cleared');
  if(field!=='byte335')equal(a.byte335,0,'335 clear survives later refusal');
  if(field==='byte334')equal(a.pointer330,null,'word clear survives missing score');
  check(!r.events.includes('slot0',r.events.indexOf('slot0')+1),'failed scan never publishes');
 }
 for(const value of [-1,256,0.5,NaN,Infinity,undefined,'0']) {
  const x=createBattleLeaderSelectionTestFixture(make);Reflect.set(x.actors[2]!,'byte334',value);run(x,'byte334: raw unsigned');equal(x.actors[2]!.pointer330,null,'bad score retains both clears');
 }
 for(const field of [HIGH,LOW]) {
  const x=createBattleLeaderSelectionTestFixture(make),before=afterDraws(x,2),after3=afterDraws(x,3);let accesses=0;
  run(x,field+': non-writable',(owner,key)=>{if(owner===x.massPreparation.rngState&&key===field&&++accesses===2)Object.defineProperty(owner,key,{writable:false});});
  equal(x.massPreparation.rngState[LOW],before[0],'failed third RNG keeps low before store');equal(x.massPreparation.rngState[HIGH],field===LOW?after3[1]:before[1],'high store precedes low failure');
  check(typeof Reflect.get(x.teamRows103[0]!,'pointer38')==='symbol','failed RNG precedes row copy');equal(x.actors[0]!.byte335,77,'failed RNG precedes actor writes');
 }
}
function publicationFailures(make:Make):void {
 for(const row of [0,2,4,1,3,5]) {
  const x=createBattleLeaderSelectionTestFixture(make),order=[0,2,4,1,3,5];let stores=0;
  run(x,'pointer330: non-writable',(o,k)=>{if(o===x.actors[row]&&k==='pointer330'&&++stores===2)Object.defineProperty(o,k,{writable:false});});
  for(let i=0;i<6;i++)equal(x.actors[i]!.pointer330,order.indexOf(i)<order.indexOf(row)?x.physicalIdentities[4+(i&1)]:null,'exact publication write prefix retained');
  equal(x.actors[4]!.byte335,1,'group0 marker precedes every publication');equal(x.actors[5]!.byte335,row%2===1?1:0,'group1 marker waits for group0 completion');
 }
 for(const row of [4,5]) {
  const x=createBattleLeaderSelectionTestFixture(make);let stores=0;
  run(x,'byte335: non-writable',(o,k)=>{if(o===x.actors[row]&&k==='byte335'&&++stores===2)Object.defineProperty(o,k,{writable:false});});
  equal(x.actors[row]!.byte335,0,'failed leader mark retains prior clear');
  for(let i=0;i<6;i++)equal(x.actors[i]!.pointer330,row===5&&i%2===0?x.physicalIdentities[4]:null,'leader marker failure precedes that group base reload/publication');
 }
 {
  const x=createBattleLeaderSelectionTestFixture(make);for(const a of x.actors)Object.defineProperty(a,'byte334',{writable:false});run(x);equal(x.actors[4]!.byte335,1,'readonly priority sources valid');
 }
 {
  const x=createBattleLeaderSelectionTestFixture(make);
  for(const a of x.actors){Reflect.set(a,'byte335','overwritten');Reflect.set(a,'pointer330','overwritten');}
  for(const row of x.teamRows103)Reflect.set(row,'pointer38','overwritten');
  run(x);equal(x.actors[4]!.byte335,1,'stores do not validate dead destination values');
 }
 for(const second of [null,Symbol('opaque table word')]) {
  const x=createBattleLeaderSelectionTestFixture(make),first=Symbol('other opaque table word');let armed=false;
  run(x,NEXT,(o,k)=>{if(!armed&&o===x.massPreparation.rngState&&k===HIGH){armed=true;x.actorSlots[2]=second;x.actorSlots[1]=first;}});
  equal(Reflect.get(x.teamRows103[0]!,'pointer38'),second,'initial table2 is copied without dereference');equal(Reflect.get(x.teamRows103[1]!,'pointer38'),first,'opaque table1 copy is preserved');
  equal(x.actors[4]!.byte335,1,'physical scan ignores changed non-base live table entries');
 }
 {
  const x=createBattleLeaderSelectionTestFixture(make);let stores=0;
  run(x,NEXT,()=>{},(o,k)=>{if(o===x.teamRows103[0]&&k==='pointer38'&&++stores===1)x.actorSlots[1]=null;});
  equal(Reflect.get(x.teamRows103[1]!,'pointer38'),null,'row0 store precedes fresh table1 load');
 }
 for(const trigger of ['rng-owner','physical','graph','global-alias','row-alias','binding-alias'] as const) {
  const x=createBattleLeaderSelectionTestFixture(make);let changed=false;
  const expected=trigger==='rng-owner'?'RNG canonical owner changed':trigger==='physical'?'canonical physical metadata changed':trigger==='graph'?'canonical graph changed':'competing source cell owner';
  run(x,expected,()=>{},(o,k)=>{
   if(changed||!(trigger==='rng-owner'?o===x.massPreparation.rngState&&k===LOW:o===x.actors[0]&&k==='byte334'))return;changed=true;
   if(trigger==='rng-owner')x.massPreparation.rngState={...x.massPreparation.rngState};
   if(trigger==='physical')x.massPreparation.physicalBlock=Object.freeze({...x.massPreparation.physicalBlock});
   if(trigger==='graph')x.outerSources.scheduler={...x.scheduler};
   if(trigger==='global-alias')Reflect.set(x.matchGlobals,'word12c',null);
   if(trigger==='row-alias')Reflect.set(x.teamRows103[0]!,'byte3A',0);
   if(trigger==='binding-alias')Reflect.set(x.status.getActualBorg(x.actor),'pointer330',null);
  });check(changed,'late canonical mutation exercised');
 }
}
function mutations(make:Make):void {
 {
  const x=createBattleLeaderSelectionTestFixture(make);let reads=0;
  run(x,NEXT,()=>{},(o,k)=>{if(o===x.actors[4]&&k==='byte334'&&++reads===1)x.actors[4]!.byte334=0;});
  equal(x.actors[0]!.pointer330,x.physicalIdentities[4],'captured score selects actor despite later change');
 }
 {
  const x=createBattleLeaderSelectionTestFixture(make);let clears=0;
  run(x,NEXT,(o,k)=>{if(o===x.actors[4]&&k==='byte335'&&++clears===2)x.actors[2]!.team=1;});
  equal(x.actors[2]!.pointer330,x.physicalIdentities[5],'publication freshly rereads team');
 }
 {
  const x=createBattleLeaderSelectionTestFixture(make);let slots=0;
  run(x,'27764 physical base differs',(o,k)=>{if(o===x.actorSlots&&k==='0'&&++slots===2)x.actorSlots[0]=x.physicalIdentities[1]!;});
  equal(x.actors[4]!.byte335,1,'selected marker precedes changed publication base refusal');equal(x.actors[0]!.pointer330,null,'no publication before valid base');equal(x.actors[5]!.byte335,0,'second leader marking has not run');
 }
 for(const where of ['pointer38','byte335','pointer330','byte334'] as const) {
  const x=createBattleLeaderSelectionTestFixture(make);let reentered=false;
  run(x,'caught same-runtime reentry',(o,k)=>{if(!reentered&&k===where&&(o===x.teamRows103[0]||o===x.actors[0])){reentered=true;refuses(()=>x.frame.runFrame(),'same-runtime reentry');}});
  check(reentered,'reentry at exact reached operation');
 }
 for(const key of ['word330','field330','byte332','field334','820','field335','821'])for(const late of [false,true]) {
  const x=createBattleLeaderSelectionTestFixture(make);let inserted=false;
  if(!late)Reflect.set(x.actors[0]!,key,1);
  run(x,'competing source cell owner',()=>{},(o,k)=>{if(late&&!inserted&&o===x.actors[0]&&k==='byte334'){inserted=true;Reflect.set(o,key,1);}});
 }
 {
  const x=createBattleLeaderSelectionTestFixture(make);let inserted=false;
  run(x,'incomplete',()=>{},(o,k)=>{if(!inserted&&o===x.actors[0]&&k==='byte334'){inserted=true;markIncompleteSourceActorDoubleLifecycle(x.actors[0]!);}});
 }
 {
  const x=createBattleLeaderSelectionTestFixture(make);let replaced=false;
  run(x,'canonical team row changed',()=>{},(o,k)=>{if(!replaced&&o===x.actors[0]&&k==='byte334'){replaced=true;x.teamRows103[0]={...x.teamRows103[0]!};}});
 }
 {
  const x=createBattleLeaderSelectionTestFixture(make);let replaced=false;
  run(x,'live own data property',()=>{},(o,k)=>{if(!replaced&&o===x.actors[0]&&k==='pointer330'){replaced=true;Object.defineProperty(o,k,{get(){throw Error('must not invoke');},configurable:true});}});
  equal(x.actors[0]!.byte335,0,'terminal destination replacement retains earlier byte clear');
 }
}
export function runBattleLeaderSelectionSelfTests(make:Make):void {
 fixtures=0;baseline(make);branches(make);failures(make);publicationFailures(make);mutations(make);
 console.log(`[battle-leader-selection] PASS (${fixtures} genuine shared-graph fixtures): six distinct active canonical actors from entry complete real mass/target preparation and27764; shared third RNG, opaque row38 copies, signed last-tie leaders, byte335 then word330, fresh ordered publication, lazy/partial effects, owner/alias/reentry closure; bef4 stops at absent current byte40, no scheduler/frame/browser claim`);
}
