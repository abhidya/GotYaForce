import {createSourceContactResetRuntime} from './source-contact-reset.js';
import {createBattleDrawOuterTestFixture} from './battle-draw-outer.selftest.js';
import type {createBattleTargetPreparationTestFixture} from './attached-setup-animation.selftest.js';
type Make=typeof createBattleTargetPreparationTestFixture;
function check(ok:boolean,s:string):void{if(!ok)throw Error('[source-contact-reset-test] '+s);}
function refuses(f:()=>unknown,s:string):void{let m='';try{f();}catch(e){m=String(e);}check(m.includes(s),`expected ${s}, got ${m}`);}
const byteOffsets=[0x1d9,0x1da,0x1db,0x1de,0x1dc,0x1dd,0x280,0x274,0x275,0x1df,0x2ae,0x2af,0x1e8];
function fields():Record<string,number>{return Object.fromEntries([...byteOffsets.map(v=>['byte'+v.toString(16),77]),...[0x270,0x286].map(v=>['half'+v.toString(16),0xabcd]),...[0x1cc,0x1d0,0x1d4].map(v=>['float'+v.toString(16),42])]);}
export function populateSourceContactResetTestFixture<T extends ReturnType<typeof createBattleDrawOuterTestFixture>>(x:T){
 const actorFields=fields();delete actorFields.byte1d9;delete actorFields.byte1db;
 Object.assign(x.sourceActor,actorFields,{supportContact1db:91,byte1df:255,byte2ae:128,byte2af:1,byte1e8:0});
 if(!x.normalLifecycle)throw Error('explicit normal lifecycle required');x.normalLifecycle.getActorBinding(x.actor).byte1d9=67;
 for(let i=0;i<13;i++)Object.assign(x.slotRecords[i]!,fields());
 for(const offset of byteOffsets)x.objectBytes[offset]=77;
 for(const offset of [0x1cc,0x1d0,0x1d4])x.allocator.writeF32(x.child,offset,42);
 for(const offset of [0x270,0x286])x.allocator.writeU16(x.child,offset,0xabcd);
 x.objectBytes[0]=1;x.objectBytes[0x86]=1;
 const resetSources={scheduler:x.scheduler,normal:x.normalLifecycle,players:x.slotStatus,constants:{float80436f68:0}};
 return Object.assign(x,{resetSources,resets:createSourceContactResetRuntime(resetSources)});
}
export function createSourceContactResetTestFixture(make:Make){return populateSourceContactResetTestFixture(createBattleDrawOuterTestFixture(make));}
export function runSourceContactResetSelfTests(make:Make):void{
 let count=0;const fresh=()=>{count++;return createSourceContactResetTestFixture(make);};
 const observe=(run:()=>void,hook:(o:object,k:PropertyKey)=>void):void=>{const native=Object.getOwnPropertyDescriptor;Object.getOwnPropertyDescriptor=((o:object,k:PropertyKey)=>{hook(o,k);return native(o,k);})as typeof native;try{run();}finally{Object.getOwnPropertyDescriptor=native;}};
 {
  const x=fresh();x.resets.resetActor(x.actor);const a=x.sourceActor as unknown as Record<string,number>;
  check(a.float1cc===0&&a.float1d0===0&&a.float1d4===0,'actual three source float stores');check(x.normalLifecycle!.getActorBinding(x.actor).byte1d9===0&&a.supportContact1db===0&&a.byte1de===91,'same canonical lifecycle/support fields');
  check(a.byte1df===254&&a.byte2ae===127&&a.byte2af===0&&a.byte1e8===0,'signed nonzero decrement is wrapped, not saturating');check(a.half270===0&&a.half286===0&&a.byte275===77&&a.byte274===0,'actual copied bytes and halfword clears');
 }
 {
  const x=fresh();for(let i=0;i<12;i++)x.resets.resetPlayer(i);for(let i=0;i<12;i++){const r=x.slotRecords[i]!as unknown as Record<string,number>;check(r.byte1de===77&&r.byte1db===0&&r.byte1d9===0&&r.byte1df===76,'same canonical player reset rows');}
  check((x.slotRecords[12] as unknown as Record<string,number>).byte1db===77,'twelfth-index row not reset by12-player caller');
 }
 {
  const x=fresh();x.resets.runGroupReset(9);check(x.allocator.readF32(x.child,0x1cc)===0&&x.objectBytes[0x1de]===77&&x.objectBytes[0x1db]===0,'populated original group9 reset');check(x.groups[9]!.head===x.child,'no reset list removal');
 }
 {
  const x=fresh(),seen:string[]=[];observe(()=>x.resets.runGroupReset(8),(o,k)=>{if(k==='head')for(const [id,g]of Object.entries(x.groups))if(o===g)seen.push(id);});
  check(seen[0]==='8'&&seen.at(-1)==='15'&&seen.includes('9'),'base first, live active slot children, last sibling');
  check(x.objectBytes[0x1db]===0,'paused match masks do not suppress genuine2cc78');
 }
 {
  const x=fresh(),a=x.sourceActor as unknown as Record<string,number>,native=Object.getOwnPropertyDescriptor;let sampled=false;
  Object.defineProperty(a,'byte1e8',{writable:false});
  Object.getOwnPropertyDescriptor=((o:object,k:PropertyKey)=>{const d=native(o,k);if(!sampled&&o===a&&k==='supportContact1db'){sampled=true;a.supportContact1db=99;}return d;})as typeof native;
  try{x.resets.resetActor(x.actor);}finally{Object.getOwnPropertyDescriptor=native;}
  check(a.byte1de===91&&a.supportContact1db===0,'captured support byte copied before source clear, not reread');
  check(a.byte1e8===0,'zero signed countdown needs no destination write');
 }
 for(const fault of ['readonly','lateAlias','supportMissing','negative','constantMissing','constantSwap','reentry','playerReplace','inactive','zero86','liveNext','nodeReadonly']as const){
  const x=fresh(),a=x.sourceActor as unknown as Record<string,number>;let changed=false;
  if(fault==='readonly')Object.defineProperty(a,'byte1da',{writable:false});
  if(fault==='supportMissing')delete a.supportContact1db;
  if(fault==='constantMissing')delete (x.resetSources as {constants?:object}).constants;
  if(fault==='negative'){a.byte1df=128;a.byte2ae=255;}
  if(fault==='inactive'){x.objectBytes[0]=0;Object.defineProperty(x.objectBytes,String(0x86),{get(){throw Error('inactive86 read');},configurable:true});}
  if(fault==='zero86'){x.objectBytes[0x86]=0;delete (x.resetSources as {constants?:object}).constants;}
  if(fault==='nodeReadonly')Object.defineProperty(x.objectBytes,String(0x1d0+3),{writable:false});
  const run=()=>fault==='playerReplace'?x.resets.resetPlayer(0):['inactive','zero86','liveNext','nodeReadonly'].includes(fault)?x.resets.runGroupReset(9):x.resets.resetActor(x.actor);
  observe(()=>{
   if(['negative','inactive','zero86'].includes(fault))run();else refuses(run,fault==='readonly'||fault==='nodeReadonly'?'writable':fault==='lateAlias'?'competing':fault==='supportMissing'?'supportContact1db':fault==='constantMissing'?'constants':fault==='constantSwap'||fault==='playerReplace'?'changed':fault==='liveNext'?'cycle':'incomplete reset');
  },(o,k)=>{
   if(!changed&&fault==='lateAlias'&&o===a&&k==='byte1da'){changed=true;Object.assign(a,{field1da:2});}
   if(!changed&&fault==='constantSwap'&&o===x.resetSources.constants&&k==='float80436f68'){changed=true;Object.assign(x.resetSources,{constants:{float80436f68:0}});}
   if(!changed&&fault==='reentry'&&o===a&&k==='float1cc'){changed=true;try{x.resets.resetActor(x.actor);}catch{}}
   if(!changed&&fault==='playerReplace'&&o===x.slotRecords[0]&&k==='float1cc'){changed=true;x.slotRecords[0]={...x.slotRecords[0]!};}
   if(!changed&&fault==='liveNext'&&o===x.resetSources.constants&&k==='float80436f68'){changed=true;x.allocator.writePointer(x.child,8,x.child);}
  });
  if(fault==='readonly'||fault==='supportMissing'||fault==='lateAlias')check(a.float1d4===0&&x.normalLifecycle!.getActorBinding(x.actor).byte1d9===0&&a.byte1de===77,'partial writes before missing/wrong byte preserved');
  if(fault==='constantSwap'||fault==='constantMissing')check(a.float1cc===42,'no writes before bad constant');
  if(fault==='negative')check(a.byte1df===127&&a.byte2ae===254,'negative raw decrements');
  if(!['negative','inactive','zero86'].includes(fault))refuses(()=>x.resets.resetActor(x.actor),'permanently incomplete');
 }
 {
  const x=fresh();let changed=false;
  observe(()=>refuses(()=>x.resets.resetPlayer(0),'alias'),(o,k)=>{if(!changed&&o===x.slotRecords[0]&&k==='float1cc'){changed=true;x.slotRecords[1]=x.slotRecords[0]!;}});
  check((x.slotRecords[0] as unknown as Record<string,number>).float1cc===42,'late row alias refused before first store');
 }
 {
  const x=fresh();Object.assign(x.sourceActor,{float80436f68:0});Object.assign(x.resetSources,{constants:x.sourceActor});
  refuses(()=>x.resets.resetActor(x.actor),'alias');
 }
 for(const fault of ['nodeReentry','nodeLateReadonly','splitAlias','splitUpperAlias']as const){
  const x=fresh(),binding=x.normalLifecycle!.getActorBinding(x.actor);let changed=false;
  observe(()=>refuses(()=>fault.startsWith('node')?x.resets.runGroupReset(9):x.resets.resetActor(x.actor),fault==='nodeReentry'?'incomplete':fault==='nodeLateReadonly'?'destination changed':'competing'),(o,k)=>{
   if(!changed&&fault==='nodeReentry'&&o===x.objectBytes&&k===String(0x1cc)){changed=true;try{x.resets.runGroupReset(9);}catch{}}
   if(!changed&&fault==='nodeLateReadonly'&&o===x.objectBytes&&k===String(0x1cc+3)){changed=true;Object.defineProperty(x.objectBytes,String(0x1cc),{writable:false});}
   if(!changed&&fault.startsWith('split')&&o===binding&&k==='byte1d9'){changed=true;Object.assign(x.sourceActor,{[fault==='splitAlias'?'half1d9':'byte1D9']:66});}
  });
  if(fault.startsWith('node'))check(x.allocator.readF32(x.child,0x1cc)===42,'poison/late readonly admits no partial scalar byte stores');
  else check(x.normalLifecycle!.getActorBinding(x.actor).byte1d9===67,'split-owner alias preserves actual lifecycle byte');
 }
 console.log(`[source-contact-reset] PASS: ${count} standalone canonical-owner reset fixtures; no2bb14/outer-frame completion claim`);
}
