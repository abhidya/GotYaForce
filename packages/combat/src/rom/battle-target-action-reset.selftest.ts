import {createSourceContactTransformTestFixture} from './battle-contact-transform.selftest.js';
import {populateSourceContactResetTestFixture} from './source-contact-reset.selftest.js';
import {invokeSourceContactResetOuter} from './source-contact-reset.js';
import type {createBattleTargetPreparationTestFixture} from './attached-setup-animation.selftest.js';
type Make=typeof createBattleTargetPreparationTestFixture;
function check(ok:boolean,s:string):void{if(!ok)throw Error('[battle-target-action-reset-test] '+s);}
function refuses(f:()=>unknown,want:string):void{let got='';try{f();}catch(e){got=String(e);}check(got.includes(want),`expected ${want}, got ${got}`);}
export function createBattleTargetActionResetTestFixture(make:Make){
  const x=populateSourceContactResetTestFixture(createSourceContactTransformTestFixture(make));
  x.allocator.writeU16(x.transformId,0x48,5);
  for(let i=0;i<48;i++)if(x.groups[i]===undefined)x.groups[i]={head:null,tail:null};
  const cells:Record<string,number>={byte80436128:77};
  for(let i=0;i<4;i++){Object.assign(x.teamRows103[i]!,{word24:0x100+i});cells['word'+(0x803b068c+4*i).toString(16)]=77;cells['half'+(0x80436154+2*i).toString(16)]=77;}
  for(let i=0;i<6;i++)cells['half'+(0x803b069c+2*i).toString(16)]=77;
  for(const i of [-1,0,1,2,3,4,5])cells['byte'+(0x8043614c+i).toString(16)]=77;
  // Indexed byte storage overlaps36128. One owner/cell, not a shadow map.
  cells.byte80436128=77;
  Object.assign(x.sourceActor,{byte7d1:2,byte7d0:6,half1c6:0xff80,byte436:1,half4f4:7,half4fc:5,half4f8:1,half4f6:3,half4fe:4,half4fa:0,byte599:99});
  const state=x.normalLifecycle!.getStatusBinding(x.actor),borg=x.status.getActualBorg(x.actor);
  state.byte6fd=9;state.byte7d4=8;borg.slowAuraLevel=3;borg.hasteAuraLevel=2;
  const targetAction={cells,normal:x.normalLifecycle!,constants:{float80436f68:0}};Object.assign(x.outerSources,{targetAction});
  return Object.assign(x,{cells,targetAction,targetState:state,targetBorg:borg});
}
export function runBattleTargetActionResetSelfTests(make:Make):void{
 let count=0;const fresh=()=>{count++;return createBattleTargetActionResetTestFixture(make);};
 type Fixture=ReturnType<typeof fresh>;
 const end='8002bcb0 requires explicit',inactiveEnd='8002bd9c reached required8002d35c';
 const run=(x:Fixture,want=end,hook:(o:object,k:PropertyKey)=>void=()=>{},inactive=false):void=>{
  const native=Object.getOwnPropertyDescriptor;let selected=false,entered=false;
  Object.getOwnPropertyDescriptor=((o:object,k:PropertyKey)=>{
   if(!selected&&o===x.match&&k==='byte66'&&x.match.wordB0===0){selected=true;x.match.byte66=0;}
   if(!entered&&o===x.outerSources&&k==='targetAction'){entered=true;if(inactive)for(const id of x.massPreparation.physicalBlock.identities)(x.allocator.getPointerTarget(id)as {active0:number}).active0=0;}
   const d=native(o,k);if(entered)hook(o,k);return d;
  })as typeof native;
  try{refuses(()=>x.frame.runFrame(),want);}finally{Object.getOwnPropertyDescriptor=native;}
  check(x.allocator.readU16(x.transformId,0x48)===4,'real contact callback returned before2bb14');
  check(Object.values(x.slotRecords).every(r=>r.contact26f===77),'later36e24 not fabricated');
  refuses(()=>x.frame.runFrame(),'permanently incomplete');
 };
 {
  const x=fresh();run(x);const a=x.sourceActor as unknown as Record<string,number>;
  check([0,1,2,3].map(i=>x.cells['word'+(0x803b068c+4*i).toString(16)]).join(',')==='256,257,258,259','same row+24 raw words copied');
  check([0,1,2,3].every(i=>x.cells['half'+(0x80436154+2*i).toString(16)]===0),'four header halfwords cleared');
  check(a.byte7d1===1&&a.byte7d0===6&&x.cells.byte8043614c===0,'positive countdown and signed-slot clear');
  check(a.float1cc===0&&a.byte1de===91&&a.supportContact1db===0&&x.normalLifecycle!.getActorBinding(x.actor).byte1d9===0,'genuine reset on existing canonical actor owners');
  check(x.cells.half803b069c===0xff80&&x.cells.byte80436128===1,'physical output halfword and active flag');
  check(a.half4fc===7&&a.half4f8===0&&a.half4f4===7&&a.half4fe===4&&a.half4f6===0,'unsigned max then signed countdown order');
  check(x.targetState.byte6fd===0&&x.targetState.byte7d4===0&&x.targetBorg.slowAuraLevel===0&&x.targetBorg.hasteAuraLevel===0&&a.byte599===99,'split canonical stores precede honest constant boundary');
 }
 for(const timer of [0,128,255]){
  const x=fresh();Object.assign(x.sourceActor,{byte7d1:timer});run(x);const a=x.sourceActor as unknown as Record<string,number>;check(a.byte7d1===0&&a.byte7d0===255,'signed nonpositive timer saturates and invalidates target slot');
 }
 {
  const x=fresh();x.sourceActor.slot=255;run(x);check(x.cells.byte8043614b===0&&x.cells.byte8043614c===77,'negative signed slot uses explicit source address, not clamp');
 }
 {
  const x=fresh();const a=x.sourceActor as unknown as Record<string,number>;a.half4f8=65535;let changed=false;
  run(x,end,(o,k)=>{if(!changed&&o===a&&k==='half4fc'){changed=true;a.half4f4=99;}});
  check(a.half4fc===7&&a.half4f4===99&&a.half4f8===65534,'captured unsigned max input and signed nonzero decrement');
 }
 {
  const x=fresh(),seen:number[]=[];run(x,inactiveEnd,(o,k)=>{if(k==='head')for(const [i,g]of Object.entries(x.groups))if(g===o)seen.push(Number(i));},true);
  check(seen.filter(i=>[0,8,16,24,32,40].includes(i)).join(',')==='40,32,0,16,8,24','six caller groups execute exact source order');
  for(let i=0;i<12;i++){const r=x.slotRecords[i]! as unknown as Record<string,number>;check(r.float1cc===0&&r.byte1de===77&&r.byte1db===0&&r.byte1df===76,'twelve original row-base resets');}
  check((x.slotRecords[12] as unknown as Record<string,number>).float1cc===42,'index12 excluded, unlike later13-row36e24');
  check(x.cells.half803b069c===77&&x.cells.byte80436128===0,'inactive physical rows skip actor effects');
 }
 for(const fault of ['missingHeader','flatShadow','readonlyHeader','lateHeaderReadonly','ownerSwap','missingTimer','readonlyReset','resetReentry','resetAlias','wrongNormal','missingHalf','splitStatus','splitBorg','zeroConstant','groupCycle','playerReadonly','overlapReset','overlapActor','overlapGlobal']as const){
  const x=fresh(),a=x.sourceActor as unknown as Record<string,number>;let changed=false;
  if(fault==='missingHeader')delete (x.teamRows103[1] as {word24?:number}).word24;
  if(fault==='flatShadow')Object.assign(x.match,{word118:9});
  if(fault==='readonlyHeader')Object.defineProperty(x.cells,'word803b068c',{writable:false});
  if(fault==='overlapReset')a.byte1cd=99;
  if(fault==='overlapActor')a.word4f3=99;
  if(fault==='overlapGlobal')x.cells.half80436153=99;
  if(fault==='missingTimer')delete a.byte7d1;
  if(fault==='readonlyReset')Object.defineProperty(a,'float1d0',{writable:false});
  if(fault==='missingHalf')delete a.half1c6;
  if(fault==='wrongNormal')Object.assign(x.targetAction,{normal:{}});
  if(fault==='splitStatus')a.byte6fd=77;
  if(fault==='splitBorg')a.byte70c=77;
  if(fault==='zeroConstant')x.targetAction.constants.float80436f68=1;
  if(fault==='groupCycle'){x.groups[40]={head:x.child,tail:x.child};x.allocator.writePointer(x.child,8,x.child);}
  if(fault==='playerReadonly')Object.defineProperty(x.slotRecords[2],'float1d0',{writable:false});
  const expected=fault==='missingHeader'||fault==='missingTimer'||fault==='missingHalf'?'own data':fault.startsWith('overlap')||fault==='flatShadow'||fault==='resetAlias'||fault==='splitStatus'||fault==='splitBorg'?'competing':fault==='readonlyHeader'||fault==='readonlyReset'||fault==='playerReadonly'?'writable':fault==='lateHeaderReadonly'||fault==='ownerSwap'?'changed':fault==='resetReentry'?'private active2bb14':fault==='wrongNormal'?'genuine normal':fault==='zeroConstant'?'authenticated': 'cycle';
  run(x,expected,(o,k)=>{
   if(!changed&&fault==='lateHeaderReadonly'&&o===x.cells&&k==='word803b068c'){changed=true;Object.defineProperty(x.cells,'word803b068c',{writable:false});}
   if(!changed&&fault==='ownerSwap'&&o===x.cells&&k==='word803b068c'){changed=true;x.targetAction.cells={...x.cells};}
   if(!changed&&fault==='resetReentry'&&o===a&&k==='float1d0'){changed=true;try{x.frame.runFrame();}catch{}}
   if(!changed&&fault==='resetAlias'&&o===a&&k==='float1d0'){changed=true;a.word1d0=55;}
  },fault==='groupCycle'||fault==='playerReadonly');
  if(fault==='missingHalf')check(a.float1cc===0&&a.byte1de===91&&x.cells.half803b069c===77,'earlier real reset survives late missing input');
  if(fault==='readonlyReset'||fault==='resetReentry'||fault==='resetAlias')check(a.float1cc===0&&a.float1d0===42,'reset stops at precise next store');
 }
 {const x=fresh();refuses(()=>invokeSourceContactResetOuter(x.frame,'actor',x.actor),'private');check((x.sourceActor as unknown as Record<string,number>).float1cc===42,'no public shortcut to caller reset');}
 console.log(`[battle-target-action-reset] PASS: ${count} ordered caller/reset fixtures; active constant and inactive contact-pass boundaries remain explicit`);
}
