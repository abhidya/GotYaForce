import {createSourceContactTransformTestFixture} from './battle-contact-transform.selftest.js';
import type {createBattleTargetPreparationTestFixture} from './attached-setup-animation.selftest.js';
type Make=typeof createBattleTargetPreparationTestFixture;
function check(ok:boolean,s:string):void{if(!ok)throw Error('[battle-contact-timer-test] '+s);}
function refuses(f:()=>unknown,want:string):void{let got='';try{f();}catch(e){got=String(e);}check(got.includes(want),`expected ${want}, got ${got}`);}
/** Existing active HITs run their genuine transform and countdown return.
 * Explicit fixture input is not a completed initializer or normal full frame. */
export function runBattleContactTimerSelfTests(make:Make):void{
 let count=0;const fresh=(timer=5)=>{count++;const x=createSourceContactTransformTestFixture(make);x.allocator.writeU16(x.transformId,0x48,timer);return x;};
 type Fixture=ReturnType<typeof fresh>;
 const end='800294f4 reached required8002bb14',dispatch='8008a788 reached contact initialization dispatch';
 const run=(x:Fixture,want:string,hook:(o:object,k:PropertyKey)=>void=()=>{}):void=>{
  const native=Object.getOwnPropertyDescriptor;let selected=false;
  Object.getOwnPropertyDescriptor=((o:object,k:PropertyKey)=>{
   if(!selected&&o===x.match&&k==='byte66'&&x.match.wordB0===0){selected=true;x.match.byte66=0;}
   const d=native(o,k);if(selected)hook(o,k);return d;
  })as typeof native;
  try{refuses(()=>x.frame.runFrame(),want);}finally{Object.getOwnPropertyDescriptor=native;}
  for(const offset of [0x30,0x3c])check([0,4,8].map(i=>x.allocator.readF32(x.transformId,offset+i)).join(',')==='3,5,7','real transform and raw copy precede timer work');
  check(x.transformBytes[0x10]===0&&x.transformBytes[0x13]===0,'mode0 remains while flag13 clears');
  check(x.groups[9]!.head===x.child&&x.groups[49]!.head===x.transformId,'original active lists preserved');
  check(Object.values(x.slotRecords).every(r=>r.contact26f===77),'2bb14 and later contact work not fabricated');
  refuses(()=>x.frame.runFrame(),'permanently incomplete');
 };
 for(const timer of [1,2,32767])for(const owner83 of [1,128]){
  const x=fresh(timer);x.transformMatrixBytes[0x83]=owner83;let nextSeen=false;
  run(x,end,(o,k)=>{if(o===x.transformBytes&&k==='8'){nextSeen=true;check(x.transformBytes[0x48]!*256+(x.transformBytes[0x49]!)===timer-1,'countdown completes before fresh next8 load');}});
  check(nextSeen&&x.allocator.readU16(x.transformId,0x48)===timer-1,'positive signed countdown really returns to traversal');
 }
 for(const timer of [0,65535,32768]){
  const x=fresh(timer);let captured=false,late83=false;
  run(x,dispatch,(o,k)=>{if(o===x.transformBytes&&k===String(0x49)){captured=true;delete x.transformMatrixBytes[0x83];}if(captured&&o===x.transformMatrixBytes&&k===String(0x83))late83=true;});
  check(!late83&&x.allocator.readU16(x.transformId,0x48)===timer,'nonpositive signed timer skips fresh83 and preserves48');
 }
 for(const fault of ['freshZero83','freshPositive83','missingFresh83','capturedTimer','capturedOwner','missingTimer','readonlyFirst','readonlySecond','lateReadonlyFirst','reentryStore','missingNext','freshNext']as const){
  const x=fresh();let lowReads=0,changed=false,extraVisits=0;
  const extra=Symbol('explicit inactive next contact'),extraBytes:Record<number,number>={0:0,8:0,9:0,10:0,11:0};let extraPointer:number[]=[];
  if(fault==='freshNext'){
   x.allocator.registerObject(extra,extraBytes);x.allocator.writePointer(x.transformId,8,extra);extraPointer=[0,1,2,3].map(i=>x.transformBytes[8+i]!);x.allocator.writePointer(x.transformId,8,null);x.groups[49]!.tail=extra;
  }
  if(fault==='freshPositive83'){x.transformMatrixBytes[0x83]=0;x.allocator.writeU16(x.transformId,0x4a,65535);}
  if(fault==='missingTimer')delete x.transformBytes[0x48];
  if(fault==='readonlyFirst')Object.defineProperty(x.transformBytes,String(0x48),{writable:false});
  if(fault==='readonlySecond')Object.defineProperty(x.transformBytes,String(0x49),{writable:false});
  const expected=fault==='freshZero83'?'8008a75c reached owner1cdc conversion':fault==='missingFresh83'||fault==='missingTimer'||fault==='missingNext'?'own data':fault.startsWith('readonly')?'writable scalar':fault==='lateReadonlyFirst'?'scalar destination changed':fault==='reentryStore'?'reentry':end;
  run(x,expected,(o,k)=>{
   if(o===extraBytes&&k==='0')extraVisits++;
   if(o===x.transformBytes&&k===String(0x49)){
    lowReads++;
    if(lowReads===1){
     if(fault==='freshZero83'){changed=true;x.transformMatrixBytes[0x83]=0;}
     if(fault==='freshPositive83'){changed=true;x.transformMatrixBytes[0x83]=128;}
     if(fault==='missingFresh83'){changed=true;delete x.transformMatrixBytes[0x83];}
     if(fault==='capturedTimer'){changed=true;x.transformBytes[0x48]=0;x.transformBytes[0x49]=0;}
     if(fault==='capturedOwner'){changed=true;for(let i=0;i<4;i++)x.transformBytes[0x20+i]=0;}
    }
    if(lowReads===2){
     if(fault==='lateReadonlyFirst'){changed=true;Object.defineProperty(x.transformBytes,String(0x48),{writable:false});}
     if(fault==='reentryStore'){changed=true;try{x.frame.runFrame();}catch{}}
     if(fault==='missingNext'){changed=true;delete x.transformBytes[8];}
     if(fault==='freshNext'){changed=true;extraPointer.forEach((v,i)=>{x.transformBytes[8+i]=v;});}
    }
   }
  });
  if(fault!=='missingTimer')check(x.allocator.readU16(x.transformId,0x48)===(['freshPositive83','capturedTimer','capturedOwner','missingNext','freshNext'].includes(fault)?4:5),'atomic halfword or preserved failure prefix');
  if(fault==='freshNext')check(changed&&extraVisits===1,'timer-return traversal reads live next8, not cached null');
  if(['freshZero83','freshPositive83','missingFresh83','capturedTimer','capturedOwner','lateReadonlyFirst','reentryStore','missingNext'].includes(fault))check(changed,'late mutation was reached');
 }
 console.log(`[battle-contact-timer] PASS: ${count} genuine positive-countdown return fixtures; next2bb14/dispatch remain explicit boundaries`);
}
