import {createBattleContactHeightTestFixture} from './battle-contact-height.selftest.js';
import type {createBattleTargetPreparationTestFixture} from './attached-setup-animation.selftest.js';
type Make=typeof createBattleTargetPreparationTestFixture;
function check(ok:boolean,s:string):void{if(!ok)throw Error('[battle-contact-pairing-test] '+s);}
function refuses(f:()=>unknown,want:string):void{let got='';try{f();}catch(e){got=String(e);}check(got.includes(want),`expected ${want}, got ${got}`);}
export function runBattleContactPairingSelfTests(make:Make):void{
 let count=0;
 for(const mode of ['zero','one','capturedCount','outerFlag','outer281','outer83','innerFlag','inner281','inner83','sameOwner','freshOwner','capturedOwner','outerSupport','innerSupport','freshCount','missingArray','nullDescriptor','descriptorAlias','lateDescriptorAlias','descriptorReadonly','radiusReject','distanceMiss','positive','adjustPositive','primaryReject','primaryPositive','primarySupport']as const){
  count++;const x=createBattleContactHeightTestFixture(make),other=Symbol('pair HIT'),ownerId=Symbol('pair owner'),descriptorId=Symbol('pair descriptor');
  const hit:Record<number,number>={},owner:Record<number,number>={},description:Record<number,number>={};
  for(let i=0;i<0x1c0;i++)hit[i]=0;for(let i=0;i<0x300;i++)owner[i]=0;for(let i=0;i<8;i++)description[i]=0;
  x.allocator.registerObject(other,hit);x.allocator.registerObject(ownerId,owner);x.allocator.registerObject(descriptorId,description);
  x.allocator.writePointer(other,0x20,['sameOwner','capturedOwner'].includes(mode)?x.child:ownerId);x.allocator.writePointer(other,0x28,descriptorId);
  x.allocator.writePointer(x.child,0x1e0,other);x.allocator.writePointer(ownerId,0x1e0,x.transformId);
  const table={0:x.transformId,1:other};Object.assign(x.targetAction,{contactPointers4c:table,contactPointers46:{0:x.transformId},contactPointers44:{0:other}});
  Object.assign(x.targetAction.constants,{float80437004:0.10000000149011612,double80436fd0:.5,double80436fd8:3});
  for(const base of [0x803b04d0,0x803b0368])for(let i=0;i<90;i++)x.cells['word'+(base+4*i).toString(16)]=77;
  let selected=false,entered=false,armed=false,changed=false,tableReads=0,firstOwnerReads=0,descriptorReads=0,descriptorLow=false,afterLowGuards=0;
  const first=x.transformMatrixBytes,native=Object.getOwnPropertyDescriptor;
  const arm=()=>{
   armed=true;x.counters.half8043624c=mode==='zero'?0:mode==='one'||mode==='capturedCount'?1:mode.startsWith('primary')?0:2;
   if(mode.startsWith('primary')){x.counters.half80436246=1;x.counters.half80436244=1;}
   first[0x281]=0;first[0x83]=1;first[0x1db]=0;first[0x1dd]=0;first[0x1de]=0;owner[0x83]=1;
   x.transformData[x.transformOffset+2]=0;x.transformData[x.transformOffset+3]=0;
   for(const o of [x.transformBytes,hit]){[0,4,8].forEach(i=>x.float(o,0x64+i,0));x.float(o,0x7c,['positive','adjustPositive','distanceMiss','primaryPositive','primarySupport'].includes(mode)?1:0);}
   if(mode==='outerFlag')x.transformData[x.transformOffset+2]=8;
   if(mode==='innerFlag')description[2]=8;
   if(mode==='outer281')first[0x281]=128;if(mode==='inner281')owner[0x281]=255;
   if(mode==='outer83')first[0x83]=23;if(mode==='inner83')owner[0x83]=23;
   if(mode==='outerSupport')first[0x1db]=128;if(mode==='innerSupport')owner[0x1db]=255;
   if(mode==='primarySupport'){first[0x1de]=1;x.float(first,0x48,0);}
   if(mode==='missingArray')delete (x.targetAction as {contactPointers4c?:object}).contactPointers4c;
   if(mode==='nullDescriptor')for(let i=0;i<4;i++)x.transformBytes[0x28+i]=0;
   if(mode==='descriptorAlias')Object.assign(x.transformData,{half2:0});
   if(mode==='descriptorReadonly')Object.defineProperty(x.transformData,String(x.transformOffset+2),{writable:false});
   if(mode==='distanceMiss')x.float(hit,0x64,8);
   if(mode==='adjustPositive'){first[0x1dd]=1;[1,0,0].forEach((v,i)=>x.float(first,0x1cc+4*i,v));}
  };
  const end='8002bda0 reached required8002d58c';
  const expected=mode==='missingArray'?'contactPointers4c':mode==='nullDescriptor'?'null descriptor':mode==='descriptorAlias'||mode==='lateDescriptorAlias'?'canonical descriptor bytes':mode==='positive'||mode==='adjustPositive'?'8002d4ec reached required80030348':mode==='primaryPositive'?'8002d134 reached required80030348':mode==='primarySupport'?'8002d0f4 requires unselected':end;
  Object.getOwnPropertyDescriptor=((o:object,k:PropertyKey)=>{
   if(!selected&&o===x.match&&k==='byte66'&&x.match.wordB0===0){selected=true;x.match.byte66=0;}
   if(!entered&&o===x.outerSources&&k==='targetAction'){entered=true;for(const id of x.physicalIdentities)(x.allocator.getPointerTarget(id)as {active0:number}).active0=0;}
   const d=native(o,k);if(!entered)return d;
   if(!armed&&o===x.slotRecords[11]&&k==='byte1e8')arm();
   if(armed&&o===table)tableReads++;
   if(armed&&o===x.transformData&&k===String(x.transformOffset+2)){descriptorReads++;if(mode==='freshCount')x.counters.half8043624c=1;}
   if(armed&&o===x.transformData&&k===String(x.transformOffset+3))descriptorLow=true;
   if(descriptorLow&&!changed&&mode==='lateDescriptorAlias'&&k==='slotStatus'&&++afterLowGuards===3){changed=true;Object.assign(x.transformData,{half2:99});}
   if(armed&&o===x.transformBytes&&k===String(0x23)){firstOwnerReads++;if(['freshOwner','capturedOwner'].includes(mode)&&firstOwnerReads===1)for(let i=0;i<4;i++)x.transformBytes[0x20+i]=0;}
   if(armed&&mode==='freshOwner'&&o===table&&k==='1')for(let i=0;i<4;i++)hit[0x20+i]=0;
   if(armed&&!changed&&mode==='capturedCount'&&o===x.counters&&k==='half8043624c'){changed=true;x.counters.half8043624c=2;}
   return d;
  })as typeof native;
  try{refuses(()=>x.frame.runFrame(),expected);}finally{Object.getOwnPropertyDescriptor=native;}
  if(['zero','one','capturedCount'].includes(mode))check(tableReads===0,'count0/1 captured condition returns without table ingress');
  if(mode==='outerFlag')check(firstOwnerReads===0&&descriptorReads===1,'outer descriptor gate precedes owner load');
  if(['outer281','outer83'].includes(mode))check(tableReads===1,'outer owner gate precedes inner lookup');
  if(['sameOwner','freshOwner'].includes(mode))check(x.cells.word803b04d0===77,'fresh identity equality skips copies');
  if(['capturedOwner','outerSupport','innerSupport','innerFlag','inner281','inner83'].includes(mode))check(x.cells.word803b04d0===77,'ordered captured/support gates skip copies');
  if(['radiusReject','distanceMiss','primaryReject'].includes(mode))check(x.cells.word803b04d0!==77&&x.cells.word803b0368!==77,'populated distinct pair genuinely copies, adjusts and rejects before returning');
  if(mode==='adjustPositive')check(x.cells.word803b04dc===0x3f800000,'real adjustment feeds actual predicate');
  if(mode==='descriptorReadonly')check(descriptorReads>0,'descriptor load does not require writable storage');
  if(mode==='lateDescriptorAlias')check(changed&&x.cells.word803b04d0===77,'terminal descriptor shape rejects overlay added by final observable guard');
  check(x.allocator.readU16(x.transformId,0x48)===4,'actual earlier callback returned');
  check(Object.values(x.slotRecords).every(r=>r.contact26f===77),'later frame work not fabricated');
  refuses(()=>x.frame.runFrame(),'permanently incomplete');
 }
 console.log(`[battle-contact-pairing] PASS: ${count} actual predicate/pairing integration cases; next helpers remain explicit`);
}
