import {createSourcePlayerContactTestFixture} from './source-player-contact.selftest.js';
import type {createBattleTargetPreparationTestFixture} from './attached-setup-animation.selftest.js';
type Make=typeof createBattleTargetPreparationTestFixture;
const keys=['50','4e','4c','4a','48','46','44','42','40','3e'].map(s=>'half804362'+s);
function check(ok:boolean,why:string):void{if(!ok)throw Error('[battle-contact-count-reset-test] '+why);}
function refuses(f:()=>unknown,want:string):void{let got='';try{f();}catch(e){got=String(e);}check(got.includes(want),`expected ${want}, got ${got}`);}
/** Explicit synthetic late mode transition after the populated paused prefix.
 * This is not a complete normal frame or output of the unfinished initializer. */
export function runBattleContactCountResetSelfTests(make:Make):void{
 let count=0;
 const fresh=()=>{count++;const x=createSourcePlayerContactTestFixture(make),counters:Record<string,number>=Object.fromEntries(keys.map((key,i)=>[key,70+i]));Object.assign(x.outerSources,{contactCounters:counters});return Object.assign(x,{counters});};
 type Fixture=ReturnType<typeof fresh>;
 const observe=(x:Fixture,run:()=>void,hook:(o:object,k:PropertyKey)=>void=()=>{},normal=true):void=>{
  const native=Object.getOwnPropertyDescriptor;let selected=false;
  Object.getOwnPropertyDescriptor=((o:object,k:PropertyKey)=>{
   if(normal&&!selected&&o===x.match&&k==='byte66'&&x.match.wordB0===0){selected=true;x.match.byte66=0;}
   const d=native(o,k);hook(o,k);return d;
  })as typeof native;
  try{run();}finally{Object.getOwnPropertyDescriptor=native;}
 };
 const stop='800294f0 reached required80089aec';
 {
  const x=fresh(),seen:string[]=[];
  observe(x,()=>refuses(()=>x.frame.runFrame(),stop),(o,k)=>{if(o===x.counters&&keys.includes(String(k))){check(keys.slice(0,seen.length).every(key=>x.counters[key]===0),'previous stores complete before fresh destination');seen.push(String(k));}});
  check(seen.join(',')===keys.join(',')&&keys.every(key=>x.counters[key]===0),'all ten exact descending stores');
  check(x.groups[9]!.head===x.child&&x.drawList.tail===x.child,'original populated lists remain');
  check(Object.values(x.slotRecords).every(r=>r.contact26f===77),'89aec and2bb14 not skipped to contact helper');
  refuses(()=>x.frame.runFrame(),'permanently incomplete');
 }
 {
  const x=fresh();Object.defineProperty(x.outerSources,'contactCounters',{get(){throw Error('paused must not load counters');}});
  observe(x,()=>refuses(()=>x.frame.runFrame(),'80029500 reached required80089658'),()=>{},false);
  check(keys.every((key,i)=>x.counters[key]===70+i),'paused branch never admits reset owner');
 }
 for(const alias of ['byte80436251','half8043624f','word8043624e','word8043624d',String(0x80436251)]){
  const x=fresh();Object.assign(x.counters,{[alias]:99});
  observe(x,()=>refuses(()=>x.frame.runFrame(),'competing'));
  check(keys.every((key,i)=>x.counters[key]===70+i),'overlapping early representation refuses before first store');
 }
 {
  const x=fresh();let changed=false;
  observe(x,()=>refuses(()=>x.frame.runFrame(),'competing'),(o,k)=>{
   if(!changed&&o===x.counters&&k===keys[2]){changed=true;Object.assign(x.counters,{byte8043624d:99});}
  });
  check(changed&&x.counters[keys[0]!]===0&&x.counters[keys[1]!]===0&&x.counters[keys[2]!]===72,'late second-byte alias preserves earlier stores, not current one');
 }
 for(const fault of ['missingOwner','ownerAlias','missingThird','readonlyThird','getterThird','lateReadonly','lateDelete','ownerSwap','lateAlias','upperAlias','globalAlias','reentry','modeChange']as const){
  const x=fresh();let changed=false,getterRan=false;
  if(fault==='missingOwner')delete(x.outerSources as {contactCounters?:object}).contactCounters;
  if(fault==='ownerAlias')Object.assign(x.outerSources,{contactCounters:x.groups[9]});
  if(fault==='missingThird')delete x.counters[keys[2]!];
  if(fault==='readonlyThird')Object.defineProperty(x.counters,keys[2]!,{writable:false});
  if(fault==='getterThird')Object.defineProperty(x.counters,keys[2]!,{get(){getterRan=true;throw Error('getter must not run');},configurable:true});
  const expected=fault==='missingOwner'?'explicit contactCounters':fault==='ownerAlias'?'alias':fault==='ownerSwap'?'owner changed':['lateAlias','upperAlias','globalAlias'].includes(fault)?'competing':fault==='reentry'?'reentry':fault==='modeChange'?stop:['lateReadonly','lateDelete'].includes(fault)?'destination changed':'writable own counter';
  observe(x,()=>refuses(()=>x.frame.runFrame(),expected),(o,k)=>{
   if(!changed&&o===x.counters&&k===keys[2]){
    changed=true;
    if(fault==='lateReadonly')Object.defineProperty(x.counters,keys[2]!,{writable:false});
    if(fault==='lateDelete')delete x.counters[keys[2]!];
    if(fault==='ownerSwap')Object.assign(x.outerSources,{contactCounters:{...x.counters}});
    if(fault==='lateAlias')Object.assign(x.counters,{word8043624c:66});
    if(fault==='upperAlias')Object.assign(x.counters,{half8043624C:66});
    if(fault==='globalAlias')Object.assign(x.match,{half8043624c:66});
    if(fault==='reentry')try{x.frame.runFrame();}catch{}
    if(fault==='modeChange')x.match.byte66=1;
   }
  });
  if(fault==='missingOwner'||fault==='ownerAlias')check(keys.every((key,i)=>x.counters[key]===70+i),'no writes before owner admission');
  else{
   check(x.counters[keys[0]!]===0&&x.counters[keys[1]!]===0,'earlier two source stores persist');
   if(fault==='modeChange')check(keys.every(key=>x.counters[key]===0),'mode not reread inside selected reset');
   else check(x.counters[keys[3]!]===73,'later counter untouched after refusal');
   if(!['missingThird','getterThird','lateDelete','modeChange'].includes(fault))check(x.counters[keys[2]!]===72,'failing destination not stored');
  }
  check(!getterRan,'data admission never executes getter');
  check(Object.values(x.slotRecords).every(r=>r.contact26f===77),'later player-contact clears not fabricated');
  refuses(()=>x.frame.runFrame(),'permanently incomplete');
 }
 console.log(`[battle-contact-count-reset] PASS: ${count} exact ordered-counter fixtures; stops before89aec, not normal frame completion`);
}
