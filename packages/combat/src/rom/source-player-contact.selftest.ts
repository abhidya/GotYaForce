import {createBattleDrawOuterTestFixture} from './battle-draw-outer.selftest.js';
import {executeSourcePlayerContact36e24} from './source-player-contact.js';
import {getSourcePlayerContactRow} from './actor-slot-status.js';
import type {createBattleTargetPreparationTestFixture} from './attached-setup-animation.selftest.js';
type Make=typeof createBattleTargetPreparationTestFixture;
function check(ok:boolean,s:string):void{if(!ok)throw Error('[source-player-contact-test] '+s);}
function refuses(f:()=>unknown,s:string):void{let m='';try{f();}catch(e){m=String(e);}check(m.includes(s),`expected ${s}, got ${m}`);}
/** Explicit paused-entry player data, not retail hydration or normal frame. */
export function createSourcePlayerContactTestFixture(make:Make){
 const x=createBattleDrawOuterTestFixture(make);Object.assign(x.system,{byte0c:0,byte0d:1,byte0e:2,byte0f:3});Object.assign(x.match,{wordB0:0xffffffff});
 Object.assign(x.outerSources,{playerContact:{constants:{float80436f68:0}}});
 for(let i=0;i<13;i++)Object.assign(x.slotRecords[i]!,{byte10:i,active0:1,contact26f:77,
  word2e8:0x3f800000,word2ec:0x40000000,word2f0:0x40400000,
  word300:0x3f800000,word304:0x40000000,word308:0x40400000});
 return x;
}
export function runSourcePlayerContactSelfTests(make:Make):void{
 let count=0;const fresh=()=>{count++;return createSourcePlayerContactTestFixture(make);};
 const stop='80029500 reached required80089658';
 {
  const x=fresh();refuses(()=>executeSourcePlayerContact36e24(x.frame),'private');
  refuses(()=>getSourcePlayerContactRow(x.slotStatus,x.frame,0),'private');
 }
 {
  const x=fresh();refuses(()=>x.frame.runFrame(),stop);check(x.match.wordB0===0,'real counter wraps');
  check(Object.values(x.slotRecords).every(r=>r.contact26f===0),'all13 real clears');
  check(x.groups[9]!.head===x.child&&x.drawList.tail===x.child,'no lists cleared');
 }
 for(const fault of ['readonly7','missing11','positive','nonfinite','gqr','staleFpscr','replaceRow','reentry','inactive','countCaptured','freshMap']as const){
  const x=fresh(),native=Object.getOwnPropertyDescriptor;let armed=false,changed=false;
  if(fault==='readonly7')Object.defineProperty(x.slotRecords[7]!,'contact26f',{writable:false});
  if(fault==='missing11')delete x.slotRecords[11]!.word308;
  if(fault==='positive')x.slotRecords[0]!.word300=0;
  if(fault==='nonfinite')x.slotRecords[0]!.word308=0x7f800000;
  if(fault==='inactive')for(const r of Object.values(x.slotRecords)){r.active0=0;delete r.word2e8;}
  Object.getOwnPropertyDescriptor=((o:object,k:PropertyKey)=>{
   if(o===x.slotRecords[0]&&k==='contact26f')armed=true;
   if(armed&&!changed&&fault==='gqr'&&o===x.drawProcessor&&k==='gqr0'){changed=true;x.drawProcessor.gqr0=1;}
   if(armed&&!changed&&fault==='staleFpscr'&&o===x.drawProcessor&&k==='fpscrControl'){changed=true;const old=native(o,k);x.drawProcessor.fpscrControl=1;return old;}
   if(armed&&!changed&&['replaceRow','reentry','countCaptured','freshMap'].includes(fault)&&o===x.slotRecords[0]&&k==='word2e8'){
    changed=true;
    if(fault==='replaceRow')x.slotRecords[0]={...x.slotRecords[0]!};
    if(fault==='reentry')try{x.frame.runFrame();}catch{}
    if(fault==='countCaptured')x.system.byte29=31;
    if(fault==='freshMap')x.system.byte0d=255;
   }
   return native(o,k);
  })as typeof native;
  const error=fault==='readonly7'?'contact26f':fault==='missing11'?'word308':fault==='positive'?'positive endpoint':fault==='nonfinite'?'finite local':fault==='gqr'?'GQR0':fault==='staleFpscr'?'FPSCR':fault==='replaceRow'?'changed':fault==='reentry'?'private':fault==='freshMap'?'physical13':stop;
  try{refuses(()=>x.frame.runFrame(),error);}finally{Object.getOwnPropertyDescriptor=native;}
  if(fault==='readonly7')check(x.slotRecords[6]!.contact26f===0&&x.slotRecords[7]!.contact26f===77&&x.slotRecords[8]!.contact26f===77,'clear prefix retained');
  else check(Object.values(x.slotRecords).every(r=>r.contact26f===0),'later fault retains all13 clears');
  refuses(()=>x.frame.runFrame(),'permanently incomplete');
 }
 {
  const x=fresh(),native=Object.getOwnPropertyDescriptor,reads:number[]=[];let armed=false;
  Object.getOwnPropertyDescriptor=((o:object,k:PropertyKey)=>{
   if(o===x.slotRecords[0]&&k==='contact26f')armed=true;
   if(armed&&k==='word2e8')for(let i=0;i<13;i++)if(o===x.slotRecords[i])reads.push(i);
   return native(o,k);
  })as typeof native;
  try{refuses(()=>x.frame.runFrame(),stop);}finally{Object.getOwnPropertyDescriptor=native;}
  const mapped=[x.system.byte0c!,x.system.byte0d!,x.system.byte0e!,x.system.byte0f!];
  const expected=[...mapped,...Array.from({length:13},(_,i)=>i).filter(i=>!mapped.includes(i))];
  check(reads.join(',')===expected.join(','),'selected order including duplicates then unvisited physical order');
 }
 {
  const x=fresh(),native=Object.getOwnPropertyDescriptor;let changed=false;
  Object.getOwnPropertyDescriptor=((o:object,k:PropertyKey)=>{
   if(!changed&&o===x.match&&k==='byte66'&&x.match.wordB0===0){changed=true;x.match.byte66=0;}
   return native(o,k);
  })as typeof native;
  try{refuses(()=>x.frame.runFrame(),'800294ec reached required8008a28c');}finally{Object.getOwnPropertyDescriptor=native;}
  check(Object.values(x.slotRecords).every(r=>r.contact26f===77),'fresh normal mode cannot skip predecessor calls');
 }
 for(const counter of [false,true]){
  const x=fresh(),native=Object.getOwnPropertyDescriptor;let injected=false;
  Object.getOwnPropertyDescriptor=((o:object,k:PropertyKey)=>{
   if(!injected&&o===(counter?x.match:x.slotRecords[0])&&k===(counter?'wordB0':'contact26f')){
    injected=true;Object.defineProperty(o,counter?'fieldb0':'byte26f',{value:123,configurable:true});
   }
   return native(o,k);
  })as typeof native;
  try{refuses(()=>x.frame.runFrame(),'competing');}finally{Object.getOwnPropertyDescriptor=native;}
  check(injected,'late alias injection reached');
  check(counter?x.match.wordB0===0xffffffff:x.slotRecords[0]!.contact26f===77,'late alias refused before current source store');
 }
 for(const alias of ['field29','byte0C','field0D'])for(const late of [false,true]){
  const x=fresh(),native=Object.getOwnPropertyDescriptor;let armed=false,injected=false;
  const key=alias==='field29'?'byte29':alias==='byte0C'?'byte0c':'byte0d';
  Object.getOwnPropertyDescriptor=((o:object,k:PropertyKey)=>{
   if(o===x.slotRecords[0]&&k==='contact26f')armed=true;
   if(!injected&&armed&&(!late||(o===x.system&&k===key))){injected=true;Object.defineProperty(x.system,alias,{value:255,configurable:true});}
   return native(o,k);
  })as typeof native;
  try{refuses(()=>x.frame.runFrame(),'competing contact system');}finally{Object.getOwnPropertyDescriptor=native;}
  check(injected&&Object.values(x.slotRecords).every(r=>r.contact26f===0),'reached system alias fails after all clears');
 }
 for(const replace of ['constants','source']as const){
  const x=fresh(),native=Object.getOwnPropertyDescriptor;let armed=false,replaced=false;
  const owner=Reflect.get(x.outerSources,'playerContact') as {constants:{float80436f68:number}};
  const constants=owner.constants;
  for(let i=1;i<13;i++)x.slotRecords[i]!.active0=0;
  Object.getOwnPropertyDescriptor=((o:object,k:PropertyKey)=>{
   if(!armed&&o===x.slotRecords[0]&&k==='contact26f'){armed=true;x.system.byte29=32;}
   if(armed&&!replaced&&o===constants&&k==='float80436f68'){
    replaced=true;const old=native(o,k);
    if(replace==='constants')owner.constants={float80436f68:0};
    else Object.assign(x.outerSources,{playerContact:{constants}});
    return old;
   }
   return native(o,k);
  })as typeof native;
  try{refuses(()=>x.frame.runFrame(),replace==='constants'?'contact constants owner changed':'contact source owner changed');}finally{Object.getOwnPropertyDescriptor=native;}
  check(replaced&&x.slotRecords[0]!.contact26f===0,'last constant observer replacement refused with clears retained');
 }
 for(const key of ['active0','word308']){
  const x=fresh(),native=Object.getOwnPropertyDescriptor;let armed=false,injected=false;
  Object.getOwnPropertyDescriptor=((o:object,k:PropertyKey)=>{
   if(o===x.slotRecords[0]&&k==='contact26f')armed=true;
   if(armed&&!injected&&o===x.slotRecords[0]&&k===key){injected=true;Object.defineProperty(o,key==='active0'?'byte0':'field308',{value:255,configurable:true});}
   return native(o,k);
  })as typeof native;
  try{refuses(()=>x.frame.runFrame(),'competing canonical player field');}finally{Object.getOwnPropertyDescriptor=native;}
  check(injected&&Object.values(x.slotRecords).every(r=>r.contact26f===0),'terminal reached player alias check retains clear prefix');
 }
 for(const key of ['byte29','byte0f']){
  const x=fresh(),native=Object.getOwnPropertyDescriptor;let armed=false,replaced=false;
  Object.getOwnPropertyDescriptor=((o:object,k:PropertyKey)=>{
   if(o===x.slotRecords[0]&&k==='contact26f')armed=true;
   if(armed&&!replaced&&o===x.system&&k===key){replaced=true;const old=native(o,k);Object.assign(x.outerSources,{systemGlobals:{...x.system}});return old;}
   return native(o,k);
  })as typeof native;
  try{refuses(()=>x.frame.runFrame(),'contact system owner changed');}finally{Object.getOwnPropertyDescriptor=native;}
  check(replaced&&Object.values(x.slotRecords).every(r=>r.contact26f===0),'captured count or final mapping cannot hide changed system owner');
 }
 console.log(`[source-player-contact] PASS: ${count} genuine paused-entry contact cases; all13 clears and live scans, explicit zero-span data only, no full frame claim`);
}
