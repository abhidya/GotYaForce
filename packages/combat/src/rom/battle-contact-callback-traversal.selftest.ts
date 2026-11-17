import {createSourcePlayerContactTestFixture} from './source-player-contact.selftest.js';
import type {createBattleTargetPreparationTestFixture} from './attached-setup-animation.selftest.js';
type Make=typeof createBattleTargetPreparationTestFixture;
function check(ok:boolean,why:string):void{if(!ok)throw Error('[battle-contact-callback-traversal-test] '+why);}
function refuses(f:()=>unknown,want:string):void{let got='';try{f();}catch(e){got=String(e);}check(got.includes(want),`expected ${want}, got ${got}`);}
/** Explicit input nodes registered in the real allocator domain. Not retail
 * hydration, completed initialization, callback success, or a normal full frame. */
export function runBattleContactCallbackTraversalSelfTests(make:Make):void{
 let count=0;
 const fresh=()=>{
  count++;const x=createSourcePlayerContactTestFixture(make),nodes:symbol[]=[],bytes:Record<number,number>[]=[];
  const counters=Object.fromEntries(['50','4e','4c','4a','48','46','44','42','40','3e'].map(s=>['half804362'+s,77]));
  Object.assign(x.outerSources,{contactCounters:counters});
  for(let i=0;i<9;i++){
   const id=Symbol('explicit contact node '+i),data:Record<number,number>={0:0,8:0,9:0,10:0,11:0,12:0x80,13:8,14:0xa6,15:0x5c};
   x.allocator.registerObject(id,data);nodes.push(id);bytes.push(data);
   if(i<8){
    const group=x.groups[48+i]??(x.groups[48+i]={head:null,tail:null}),old=group.head;
    if(old!==null&&old!==undefined){
     // Preserve the already-created HIT list and its canonical group owner.
     // Explicit inactive input is a fixture choice, never a runtime shortcut.
     x.allocator.writePointer(id,8,old);
     let current:symbol|null=old;const seen=new Set<symbol>();
     while(current!==null){if(seen.has(current))throw Error('fixture cycle');seen.add(current);x.allocator.writeU8(current,0,0);current=x.allocator.readPointer(current,8);}
    }
    group.head=id;if(group.tail===null)group.tail=id;
   }
  }
  x.allocator.writePointer(nodes[8]!,8,nodes[8]!);
  const extraPointer=Array.from({length:4},(_,i)=>bytes[8]![8+i]!);
  x.allocator.writePointer(nodes[8]!,8,null);
  return Object.assign(x,{contactNodes:nodes,contactBytes:bytes,counters,extraPointer});
 };
 type Fixture=ReturnType<typeof fresh>;
 const run=(x:Fixture,want:string,hook:(o:object,k:PropertyKey)=>void=()=>{}):void=>{
  const native=Object.getOwnPropertyDescriptor;let selected=false,armed=false;
  Object.getOwnPropertyDescriptor=((o:object,k:PropertyKey)=>{
   if(!selected&&o===x.match&&k==='byte66'&&x.match.wordB0===0){selected=true;x.match.byte66=0;}
   if(o===x.groups&&k==='48'&&!armed){armed=true;for(const a of x.actors)a.active0=1;}
   const d=native(o,k);if(armed)hook(o,k);return d;
  })as typeof native;
  try{refuses(()=>x.frame.runFrame(),want);}finally{Object.getOwnPropertyDescriptor=native;}
  check(Object.values(x.counters).every(v=>v===0),'authentic earlier counter stores complete');
  check(x.groups[9]!.head===x.child&&x.drawList.tail===x.child,'original projectile lists untouched');
  check(Object.values(x.slotRecords).every(row=>row.contact26f===77),'2bb14/contact helpers not skipped');
  refuses(()=>x.frame.runFrame(),'permanently incomplete');
 };
 const stop='800294f4 reached required8002bb14';
 {
  const x=fresh(),heads:number[]=[],visits:number[]=[];
  for(const bytes of x.contactBytes)Object.defineProperty(bytes,'12',{get(){throw Error('inactive callback must stay unread');},configurable:true});
  run(x,stop,(o,k)=>{if(k==='head')for(let i=48;i<56;i++)if(o===x.groups[i])heads.push(i);if(k==='0'){const i=x.contactBytes.indexOf(o as Record<number,number>);if(i>=0)visits.push(i);}});
  check(heads.join(',')==='48,49,50,51,52,53,54,55'&&visits.join(',')==='0,1,2,3,4,5,6,7','real populated inactive lists traverse in source order');
 }
 for(const [index,active,callback,site]of [[0,1,0x8008a65d,'80089b30'],[2,1,0x8008a65d,'80089b84'],[7,1,0x8008a65d,'80089bd0'],[0,128,0x8008a65d,'80089b30'],[0,1,0,'80089b30']]as const){
  const x=fresh();x.contactBytes[index]![0]=active;x.allocator.writeU32(x.contactNodes[index]!,0xc,callback);let nextRead=false;
  run(x,site+' reached required contact callback0c '+callback.toString(16),(o,k)=>{if(o===x.contactBytes[index]&&k==='8')nextRead=true;});
  check(!nextRead,'active mandatory callback refuses before next8');
 }
 for(const fault of ['inactiveSlot','nullSlot','groupAlias','groupSwap','tableSwap','actorAlias','cycle','missingNext','liveNext','capturedHead','repeat','futureHead','ignoreMasks']as const){
  const x=fresh();let changed=false,extraVisits=0;
  if(fault==='cycle')x.allocator.writePointer(x.contactNodes[0]!,8,x.contactNodes[0]!);
  if(fault==='missingNext')delete x.contactBytes[0]![8];
  if(fault==='repeat')x.groups[50]!.head=x.contactNodes[1]!;
  const expected=fault==='nullSlot'?'null actor slot':fault==='groupAlias'?'alias':fault==='groupSwap'||fault==='tableSwap'?'changed':fault==='actorAlias'?'competing':fault==='cycle'?'cyclic':fault==='missingNext'?'own data':stop;
  run(x,expected,(o,k)=>{
   if(o===x.contactBytes[8]&&k==='0')extraVisits++;
   if(!changed&&o===x.groups[48]&&k==='head'){
    if(fault==='inactiveSlot'){changed=true;x.actors[1]!.active0=0;Object.defineProperty(x.groups[50]!,'head',{get(){throw Error('inactive actor group must stay unread');},configurable:true});}
    if(fault==='nullSlot'){changed=true;x.actorSlots[0]=null;}
    if(fault==='groupAlias'){changed=true;x.groups[55]=x.counters;}
    if(fault==='groupSwap'){changed=true;x.groups[48]={...x.groups[48]!};}
    if(fault==='tableSwap'){changed=true;x.schedulerSources.actorSlots={...x.actorSlots};}
    if(fault==='actorAlias'){changed=true;Object.assign(x.actors[0]!,{byte0:1});}
    if(fault==='capturedHead'){changed=true;x.groups[48]!.head=null;}
    if(fault==='ignoreMasks'){changed=true;x.match.maskD1=128;x.match.maskD2=128;}
   }
   if(!changed&&o===x.contactBytes[0]&&k==='0'){
    if(fault==='liveNext'){changed=true;x.extraPointer.forEach((v,i)=>{x.contactBytes[0]![8+i]=v;});}
    if(fault==='futureHead'){changed=true;x.groups[55]!.head=x.contactNodes[8]!;}
   }
  });
  if(fault==='liveNext'||fault==='futureHead')check(extraVisits===1,'later source pointer is read live');
 }
 console.log(`[battle-contact-callback-traversal] PASS: ${count} canonical contact-list fixtures; active callbacks remain explicit unsupported calls`);
}
