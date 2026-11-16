import {createBattleTargetActionResetTestFixture} from './battle-target-action-reset.selftest.js';
import type {createBattleTargetPreparationTestFixture} from './attached-setup-animation.selftest.js';
type Make=typeof createBattleTargetPreparationTestFixture;
function check(ok:boolean,s:string):void{if(!ok)throw Error('[battle-contact-height-test] '+s);}
function refuses(f:()=>unknown,want:string):void{let got='';try{f();}catch(e){got=String(e);}check(got.includes(want),`expected ${want}, got ${got}`);}
/** Explicit same-owner source inputs, not retail initialization or a full frame. */
export function runBattleContactHeightSelfTests(make:Make):void{
 let count=0;
 const fresh=()=>{
  count++;const x=createBattleTargetActionResetTestFixture(make);
  for(const id of x.physicalIdentities.slice(1))(x.allocator.getPointerTarget(id)as {active0:number}).active0=0;
  Object.assign(x.targetAction.constants,{float80436f6c:-10000});
  for(let i=0;i<6;i++)for(const [prefix,base,width]of [['byte',0x80436144,1],['word',0x803b06a8,4],['byte',0x8043613c,1],['byte',0x80436134,1],['float',0x803b0644,4],['byte',0x8043612c,1],['half',0x803b0638,2],['float',0x803b0708,4]]as const)x.cells[prefix+(base+i*width).toString(16)]=77;
  const counters=x.outerSources.contactCounters!as Record<string,number>;
  return Object.assign(x,{counters});
 };
 type Fixture=ReturnType<typeof fresh>;
 const end='8002bd9c reached required8002d35c',pairEnd='8002d080 reached required8003a05c';
 const run=(x:Fixture,want=end,hook:(o:object,k:PropertyKey)=>void=()=>{},inactivePhysical=false):void=>{
  const native=Object.getOwnPropertyDescriptor;let selected=false,entered=false;
  Object.getOwnPropertyDescriptor=((o:object,k:PropertyKey)=>{
   if(!selected&&o===x.match&&k==='byte66'&&x.match.wordB0===0){selected=true;x.match.byte66=0;}
   if(!entered&&o===x.outerSources&&k==='targetAction'){entered=true;if(inactivePhysical)for(const id of x.physicalIdentities)(x.allocator.getPointerTarget(id)as {active0:number}).active0=0;}
   const d=native(o,k);if(entered)hook(o,k);return d;
  })as typeof native;
  try{refuses(()=>x.frame.runFrame(),want);}finally{Object.getOwnPropertyDescriptor=native;}
  check(x.allocator.readU16(x.transformId,0x48)===4,'real contact timer returns before reset/height pass');
  check(Object.values(x.slotRecords).every(r=>r.contact26f===77),'later player-contact stage not fabricated');
  refuses(()=>x.frame.runFrame(),'permanently incomplete');
 };
 // Copy-heavy tests use the separately proved inactive-physical caller path;
 // active caller, populated same-owner and scalar-height paths remain tested.
 const pair=(x:Fixture,otherOwner:symbol|null=x.child)=>{
  const id=Symbol('explicit second contact'),b:Record<number,number>={};for(let i=0;i<0x1c0;i++)b[i]=0;
  x.allocator.registerObject(id,b);x.allocator.writePointer(id,0x20,otherOwner);
  for(let i=0;i<90;i++){x.word(x.transformBytes,0x58+4*i,0xabcd0000+i);x.word(b,0x58+4*i,0x12340000+i);}
  // Restore genuine contact matrix pointer before its earlier callback.
  x.allocator.writePointer(x.transformId,0x60,x.allocator.getInteriorPointer(x.child,0x114));
  const outer={0:x.transformId},inner={0:id};Object.assign(x.targetAction,{contactPointers46:outer,contactPointers44:inner});
  for(const base of [0x803b04d0,0x803b0368])for(let i=0;i<90;i++)x.cells['word'+(base+4*i).toString(16)]=77;
  return {id,b,outer,inner};
 };
 const arm=(x:Fixture,outer=1,inner=0)=>(o:object,k:PropertyKey)=>{if(o===x.slotRecords[11]&&k==='byte1e8'){x.counters.half80436246=outer;x.counters.half80436244=inner;}};
 {
  const x=fresh();let arrayRead=false;run(x,end,(o,k)=>{if(o===x.targetAction&&['contactPointers46','contactPointers44'].includes(String(k)))arrayRead=true;});
  check(!arrayRead&&x.counters.half80436246===0,'real zeroed count returns2cf80 without array ingress');
  check(x.cells.float803b0708===-10000&&x.cells.float803b0644===0&&x.cells.half803b0638===0&&x.cells.word803b06a8===0,'authenticated constants and eight indexed stores');
  check((x.sourceActor as unknown as Record<string,number>).byte599===0&&Array.from({length:12},(_,i)=>x.slotRecords[i]!).every(r=>(r as unknown as Record<string,number>).float1cc===0),'active actor continues through actual group and12player resets');
 }
 {
  const x=fresh();let ready=false,n=0;const wanted=[1,2,3,4,5,0,1,2];
  run(x,end,(o,k)=>{if(o===x.sourceActor&&k==='byte599'&&!ready){ready=true;x.sourceActor.slot=1;}if(ready&&o===x.sourceActor&&k==='slot'){x.sourceActor.slot=wanted[++n]??2;}});
  check(n===8&&x.cells.byte80436145===0&&x.cells.word803b06b0===0&&x.cells.byte8043613f===0&&x.cells.byte80436138===0&&x.cells.float803b0658===0&&x.cells.byte8043612c===0&&x.cells.half803b063a===0&&x.cells.float803b0710===-10000,'all8 source index loads fresh, each captured for one store');
 }
 for(const fault of ['constantWrong','constantCaptured','missing599','lateReadonly','lateAlias','lateReentry','missingFloat','shadowFloat']as const){
  const x=fresh(),a=x.sourceActor as unknown as Record<string,number>;let changed=false;
  if(fault==='constantWrong')Object.assign(x.targetAction.constants,{float80436f6c:0});
  if(fault==='missing599')delete a.byte599;
  if(fault==='missingFloat')delete x.cells.float803b0644;
  if(fault==='shadowFloat')x.cells.word803b0644=99;
  const expected=fault==='constantWrong'?'authenticated -10000':fault==='missing599'||fault==='missingFloat'?'writable2bb14':fault==='lateReadonly'?'destination changed':fault==='lateAlias'||fault==='shadowFloat'?'competing':fault==='lateReentry'?'reentry':end;
  run(x,expected,(o,k)=>{
   if(!changed&&fault==='constantCaptured'&&o===a&&k==='byte599'){changed=true;Object.assign(x.targetAction.constants,{float80436f6c:0});}
   if(!changed&&['lateReadonly','lateAlias','lateReentry'].includes(fault)&&o===x.cells&&k==='word803b06a8'){changed=true;if(fault==='lateReadonly')Object.defineProperty(x.cells,'word803b06a8',{writable:false});else if(fault==='lateAlias')x.cells.byte803b06a9=12;else try{x.frame.runFrame();}catch{}}
  });
  if(fault==='constantCaptured')check(x.cells.float803b0708===-10000,'captured constant survives later mutation');
  if(fault==='constantWrong')check(a.byte599===99&&x.targetState.byte7d4===0,'wrong constant preserves exact previous prefix');
  if(['lateReadonly','lateAlias','lateReentry'].includes(fault))check(x.cells.byte80436144===0&&x.cells.word803b06a8===77,'indexed store failure preserves previous stores');
 }
 for(const mode of ['outerOnly','sameOwner','freshOwner','capturedOwner','height','heightNegativeSlot','freshOuterCount','freshInnerCount','missingArray','nullHit','missingOwner83','badFpscr','readonlyHeight','differentOwners','copyMissingSecond','copyReadonlySecond','copyLiveSecondPair','copyReentry','lateFpscr','lateProcessor','lateCountAlias','heightNaN','heightOverflow','heightNegativeZero','scalarGqr']as const){
  const x=fresh(),p=pair(x,mode.startsWith('copy')||mode==='differentOwners'?null:x.child);let changed=false,ownerReads=0,innerLoads=0;
  const start=arm(x,1,['outerOnly','height','heightNegativeSlot','missingArray','nullHit','missingOwner83','badFpscr','readonlyHeight'].includes(mode)?0:1);
  if(mode==='missingArray')delete (x.targetAction as {contactPointers46?:object}).contactPointers46;
  if(mode==='nullHit')p.outer[0]=null as unknown as symbol;
  const height=['height','heightNegativeSlot','badFpscr','readonlyHeight','lateFpscr','lateProcessor','heightNaN','heightOverflow','heightNegativeZero','scalarGqr'].includes(mode);
  const expected=mode==='missingArray'?'contactPointers46':mode==='nullHit'?'null pointer':mode==='missingOwner83'||mode==='copyMissingSecond'?'own data':mode==='badFpscr'||mode==='lateFpscr'?'FPSCR':mode==='lateProcessor'?'processor changed':mode==='lateCountAlias'?'competing':mode==='heightNaN'?'finite':mode==='heightOverflow'?'overflow':mode==='readonlyHeight'?'writable2bb14':mode==='copyReadonlySecond'?'writable2bb14':mode==='copyReentry'?'reentry':mode.startsWith('copy')||mode==='differentOwners'?pairEnd:end;
  run(x,expected,(o,k)=>{
   start(o,k);
   if(o===x.slotRecords[11]&&k==='byte1e8'){
    if(height){x.transformMatrixBytes[0x83]=0;x.transformMatrixBytes[0x3e4]=mode==='heightNegativeSlot'?255:2;x.float(x.transformBytes,0x68,12.5);x.float(x.transformBytes,0x88,2.25);if(mode==='heightNegativeSlot')x.cells.float803b0704=77;}
    if(mode==='missingOwner83')delete x.transformMatrixBytes[0x83];
    if(mode==='badFpscr')x.drawProcessor.fpscrControl=1;
    if(mode==='scalarGqr')x.drawProcessor.gqr0=4;
    if(mode==='heightNaN')x.word(x.transformBytes,0x68,0x7fc00001);
    if(mode==='heightOverflow'){x.word(x.transformBytes,0x68,0x7f7fffff);x.word(x.transformBytes,0x88,0xff7fffff);}
    if(mode==='heightNegativeZero'){x.word(x.transformBytes,0x68,0x80000000);x.word(x.transformBytes,0x88,0);}
    if(mode==='readonlyHeight')Object.defineProperty(x.cells,'float803b0710',{writable:false});
    if(mode==='copyMissingSecond')delete x.transformBytes[0x5f];
    if(mode==='copyReadonlySecond')Object.defineProperty(x.cells,'word803b04d4',{writable:false});
   }
   if(!changed&&mode==='lateCountAlias'&&o===x.counters&&k==='half80436246'){changed=true;Object.assign(x.targetAction,{half80436246:99});}
   if(!changed&&['lateFpscr','lateProcessor'].includes(mode)&&o===x.cells&&k==='float803b0710'){changed=true;if(mode==='lateFpscr')x.drawProcessor.fpscrControl=1;else Object.assign(x.rootSources,{processor:{...x.drawProcessor}});}
   if(o===p.inner&&k==='0')innerLoads++;
   if(o===x.transformBytes&&k===String(0x23)){
    ownerReads++;
    if(mode==='freshOwner'&&ownerReads===1)for(let i=0;i<4;i++)x.transformBytes[0x20+i]=0;
    if(mode==='capturedOwner'&&ownerReads===1)for(let i=0;i<4;i++)x.transformBytes[0x20+i]=0;
   }
   if(mode==='freshOwner'&&o===p.inner&&k==='0')for(let i=0;i<4;i++)p.b[0x20+i]=0;
   if(!changed&&mode==='freshOuterCount'&&o===x.counters&&k==='half80436244'){changed=true;x.counters.half80436246=0;}
   if(!changed&&mode==='freshInnerCount'&&o===p.inner&&k==='0'){changed=true;x.counters.half80436244=0;}
   if(!changed&&mode==='copyLiveSecondPair'&&o===x.cells&&k==='word803b04d4'){changed=true;x.word(x.transformBytes,0x60,0xdeadbeef);}
   if(!changed&&mode==='copyReentry'&&o===x.cells&&k==='word803b04d0'){changed=true;try{x.frame.runFrame();}catch{}}
  },mode.startsWith('copy')||mode==='differentOwners');
  if(['height','heightNegativeSlot','scalarGqr'].includes(mode))check(x.cells[mode==='heightNegativeSlot'?'float803b0704':'float803b0710']===10.25,'actual finite scalar subtraction and signed output index');
  if(mode==='heightNegativeZero')check(Object.is(x.cells.float803b0710,-0),'scalar subtraction keeps negative zero');
  if(mode==='lateFpscr'||mode==='lateProcessor')check(changed&&x.cells.float803b0710===77,'late scalar-policy change refuses before store');
  if(mode==='outerOnly')check(innerLoads===0,'zero44 does not load inner table');
  if(mode==='differentOwners'||mode==='copyLiveSecondPair')check(x.cells.word803b04d0===0xabcd0000&&x.cells.word803b0368===0x12340000&&x.cells.word803b04cc===0x12340059,'both90wordcopies precede mandatory helper');
  if(mode==='copyMissingSecond'||mode==='copyReentry')check(x.cells.word803b04d0===77,'second source load/caught reentry precedes first pair store');
  if(mode==='copyReadonlySecond')check(x.cells.word803b04d0===0xabcd0000&&x.cells.word803b04d4===77,'separate scalar stores retain first on second failure');
  if(mode==='copyLiveSecondPair')check(x.cells.word803b04d8===0xdeadbeef,'later source pair is not snapshotted');
 }
 console.log(`[battle-contact-height] PASS: ${count} caller-index/initial-contact fixtures; real bounded returns and mandatory collision boundary`);
}
