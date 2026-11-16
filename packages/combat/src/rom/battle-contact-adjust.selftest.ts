import {createBattleContactHeightTestFixture} from './battle-contact-height.selftest.js';
import type {createBattleTargetPreparationTestFixture} from './attached-setup-animation.selftest.js';
type Make=typeof createBattleTargetPreparationTestFixture;
function check(ok:boolean,s:string):void{if(!ok)throw Error('[battle-contact-adjust-test] '+s);}
function refuses(f:()=>unknown,want:string):void{let got='';try{f();}catch(e){got=String(e);}check(got.includes(want),`expected ${want}, got ${got}`);}
/** Explicit collision inputs on real existing owners, not retail hydration or
 * a skipped preceding stage. The actual timer/reset/copy path reaches3a05c. */
export function runBattleContactAdjustSelfTests(make:Make):void{
 let count=0;
 const end='8002d0cc reached required80039f6c';
 for(const mode of ['zero','first','second','both','signed','freshSecond','capturedSecond','lazyZero','liveZ','height','freshSlot','nullSecond','missingFlag','missingY','missingZ','readonlyY','lateReadonlyY','readonlyZ','lateGqrXY','lateGqrZ','lateFpscrZ','lateProcessor','reentryXY','aliasXY','nan','overflowY','negativeZero']as const){
  count++;const x=createBattleContactHeightTestFixture(make),other=Symbol('collision contact'),otherOwner=Symbol('collision owner');
  const hit:Record<number,number>={},owner:Record<number,number>={};
  for(let i=0;i<0x1c0;i++)hit[i]=0;for(let i=0;i<0x1e0;i++)owner[i]=0;
  x.allocator.registerObject(other,hit);x.allocator.registerObject(otherOwner,owner);x.allocator.writePointer(other,0x20,mode==='nullSecond'?null:otherOwner);
  Object.assign(x.targetAction,{contactPointers46:{0:x.transformId},contactPointers44:{0:other}});
  for(const base of [0x803b04d0,0x803b0368])for(let i=0;i<90;i++)x.cells['word'+(base+4*i).toString(16)]=77;
  let selected=false,entered=false,armed=false,adjusting=false,changed=false,firstFlagReads=0,secondFlagReads=0;
  const visits:Record<string,number>={},native=Object.getOwnPropertyDescriptor;
  const first=x.transformMatrixBytes;
  const arm=()=>{
   armed=true;x.counters.half80436246=1;x.counters.half80436244=1;
   first[0x83]=mode==='height'||mode==='freshSlot'?0:1;first[0x3e4]=2;
   first[0x1dd]=['zero','second','lazyZero'].includes(mode)?0:mode==='signed'?128:1;
   owner[0x1dd]=['second','both','freshSecond','capturedSecond'].includes(mode)?1:0;
   [1,2,3].forEach((v,i)=>x.float(first,0x1cc+i*4,v));[-1,4,5].forEach((v,i)=>x.float(owner,0x1cc+i*4,v));
   [10,20,30].forEach((v,i)=>x.float(x.transformBytes,0x64+i*4,v));[40,50,60].forEach((v,i)=>x.float(hit,0x64+i*4,v));x.float(x.transformBytes,0x88,2);
   if(mode==='lazyZero'){delete first[0x1cc];delete owner[0x1cc];x.drawProcessor.fpscrControl=1;x.drawProcessor.gqr0=4;}
   if(mode==='missingFlag')delete owner[0x1dd];
   if(mode==='missingY')delete first[0x1d3];if(mode==='missingZ')delete first[0x1d7];
   if(mode==='nan')x.word(first,0x1cc,0x7fc00001);
   if(mode==='overflowY'){x.word(first,0x1d0,0x7f7fffff);x.word(x.transformBytes,0x68,0x7f7fffff);}
   if(mode==='negativeZero'){[0,4,8].forEach(i=>{x.word(first,0x1cc+i,0x80000000);x.word(x.transformBytes,0x64+i,0x80000000);});}
  };
  const expected=mode==='nullSecond'?'null pointer':mode==='missingFlag'||mode==='missingY'||mode==='missingZ'?'own data':mode==='readonlyY'||mode==='readonlyZ'?'writable paired':mode==='lateReadonlyY'?'destination changed':mode==='lateGqrXY'||mode==='lateGqrZ'?'GQR0':mode==='lateFpscrZ'?'FPSCR':mode==='lateProcessor'?'processor profile owner changed':mode==='reentryXY'?'reentry':mode==='aliasXY'?'competing':mode==='nan'?'finite':mode==='overflowY'?'overflow':end;
  Object.getOwnPropertyDescriptor=((o:object,k:PropertyKey)=>{
   if(!selected&&o===x.match&&k==='byte66'&&x.match.wordB0===0){selected=true;x.match.byte66=0;}
   if(!entered&&o===x.outerSources&&k==='targetAction'){entered=true;for(const id of x.physicalIdentities)(x.allocator.getPointerTarget(id)as {active0:number}).active0=0;}
   const d=native(o,k);if(!entered)return d;
   if(!armed&&o===x.slotRecords[11]&&k==='byte1e8')arm();
   if(armed&&o===first&&k===String(0x1dd)){adjusting=true;firstFlagReads++;if(mode==='capturedSecond')for(let i=0;i<4;i++)hit[0x20+i]=0;if(mode==='readonlyY'||mode==='readonlyZ')Object.defineProperty(x.cells,mode==='readonlyY'?'word803b04e0':'word803b04e4',{writable:false});}
   if(armed&&o===owner&&k===String(0x1dd))secondFlagReads++;
   if(adjusting&&o===x.cells&&['word803b04dc','word803b04e0','word803b04e4'].includes(String(k))){
    const key=String(k);visits[key]=(visits[key]??0)+1;
    if(!changed&&key==='word803b04e0'&&visits[key]===2){
     if(mode==='liveZ'){changed=true;x.float(first,0x1d4,7);}
     if(mode==='freshSecond'){changed=true;owner[0x1dd]=0;}
     if(mode==='lateReadonlyY'){changed=true;Object.defineProperty(x.cells,key,{writable:false});}
     if(mode==='lateGqrXY'){changed=true;x.drawProcessor.gqr0=4;}
     if(mode==='lateProcessor'){changed=true;Object.assign(x.rootSources,{processor:{...x.drawProcessor}});}
     if(mode==='reentryXY'){changed=true;try{x.frame.runFrame();}catch{}}
     if(mode==='aliasXY'){changed=true;x.cells.byte803b04dd=9;}
    }
    if(!changed&&key==='word803b04e4'&&visits[key]===2){
     if(mode==='lateGqrZ'){changed=true;x.drawProcessor.gqr0=4;}
     if(mode==='lateFpscrZ'){changed=true;x.drawProcessor.fpscrControl=1;}
    }
   }
   if(adjusting&&mode==='freshSlot'&&o===first&&k===String(0x3e4))first[0x3e4]=4;
   return d;
  })as typeof native;
  try{refuses(()=>x.frame.runFrame(),expected);}finally{Object.getOwnPropertyDescriptor=native;}
  const value=(address:number)=>{const v=new DataView(new ArrayBuffer(4));v.setUint32(0,x.cells['word'+address.toString(16)]!,false);return v.getFloat32(0,false);};
  const vector=(address:number)=>[0,4,8].map(i=>value(address+i)).join(',');
  if(['first','both','signed','freshSecond','capturedSecond','height','freshSlot'].includes(mode))check(vector(0x803b04dc)==='11,22,33','real first displacement Add');
  if(['second','both','capturedSecond'].includes(mode))check(vector(0x803b0374)==='39,54,65','real second displacement Add and retained owner');
  if(['zero','second','lazyZero','readonlyY','lateReadonlyY','lateGqrXY','lateProcessor','reentryXY','aliasXY','nan','overflowY','missingY'].includes(mode))check(vector(0x803b04dc)===(mode==='overflowY'?`10,${Math.fround(3.4028234663852886e38)},30`:'10,20,30'),'no partial XY store or fabricated adjustment');
  if(['missingZ','readonlyZ','lateGqrZ','lateFpscrZ'].includes(mode))check(vector(0x803b04dc)==='11,22,30','XY retained before separate Z refusal');
  if(mode==='liveZ')check(vector(0x803b04dc)==='11,22,37','Z is loaded after paired XY store');
  if(mode==='freshSecond')check(changed&&vector(0x803b0374)==='40,50,60','second signed flag is fresh after first call');
  if(mode==='height'||mode==='freshSlot')check(x.cells.float803b0710===20&&x.cells.float803b0718===77,'post-adjust height uses captured signed slot then modified scratch Y');
  if(mode==='negativeZero')check([0,4,8].every(i=>Object.is(value(0x803b04dc+i),-0)),'negative-zero paired addition preserved');
  if(['zero','lazyZero'].includes(mode))check(firstFlagReads===1&&secondFlagReads===1,'zero wrapper reads both flags once and skips vector inputs');
  check(x.allocator.readU16(x.transformId,0x48)===4,'genuine earlier callback returned');
  check(Object.values(x.slotRecords).every(r=>r.contact26f===77),'later frame stage not fabricated');
  refuses(()=>x.frame.runFrame(),'permanently incomplete');
 }
 console.log(`[battle-contact-adjust] PASS: ${count} genuine contact displacement/paired-add cases; collision predicate remains unsupported`);
}
