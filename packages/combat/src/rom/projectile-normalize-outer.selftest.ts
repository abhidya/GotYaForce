import {createBattleStageDispatchTestFixture} from './battle-stage-dispatch.selftest.js';
import type {createBattleTargetPreparationTestFixture} from './attached-setup-animation.selftest.js';
type Make=typeof createBattleTargetPreparationTestFixture;
function check(ok:boolean,why:string):void{if(!ok)throw Error('[projectile-normalize-outer-test] '+why);}
function refuses(f:()=>unknown,part:string):void{let message='';try{f();}catch(e){message=String(e);}check(message.includes(part),`expected ${part}, got ${message}`);}
export function createProjectileNormalizeOuterTestFixture(make:Make){
 const x=createBattleStageDispatchTestFixture(make),processor=Object.assign(x.actionSources.processor,{fpscrControl:0});
 Object.assign(x.rootSources,{processor});return Object.assign(x,{normalizeProcessor:processor});
}
export function runProjectileNormalizeOuterSelfTests(make:Make):void{
 let count=0;const fresh=()=>{count++;return createProjectileNormalizeOuterTestFixture(make);};
 const setVector=(x:ReturnType<typeof fresh>,v:number[])=>{const b=new DataView(new ArrayBuffer(12));v.forEach((n,i)=>b.setFloat32(i*4,n,false));for(let i=0;i<12;i++)x.objectBytes[0x38+i]=b.getUint8(i);};
 {
  const x=fresh();refuses(()=>x.frame.runFrame(),'8007e078 initializer tail missing explicit row1.speed10');
  check(x.allocator.readU32(x.child,0x40)===0x3f7fffff,'unit input follows actual model estimate/refinement, not identity shortcut');
  check(x.allocator.readU32(x.child,0x38)===0&&x.allocator.readU32(x.child,0x3c)===0,'source XY paired result');
 }
 for(const fault of ['zero','square2','gqr','fpscr','readonlyY','readonlyZ','reentryXY','reentryZ'] as const){
  const x=fresh(),native=Object.getOwnPropertyDescriptor;let armed=false,visits=0;
  Object.getOwnPropertyDescriptor=((o:object,k:PropertyKey)=>{
   if(!armed&&o===x.rootSources&&k==='processor'){
    armed=true;
    if(fault==='zero')setVector(x,[0,0,0]);
    if(fault==='square2')setVector(x,[1,1,0]);
    if(fault==='gqr')x.normalizeProcessor.gqr0=1;
    if(fault==='fpscr')x.normalizeProcessor.fpscrControl=1;
    if(fault.startsWith('readonly')||fault.startsWith('reentry'))setVector(x,[1,0,0]);
    if(fault==='readonlyY')Object.defineProperty(x.objectBytes,'60',{writable:false});
    if(fault==='readonlyZ')Object.defineProperty(x.objectBytes,'64',{writable:false});
   }
   if(armed&&fault.startsWith('reentry')&&o===x.objectBytes&&k===(fault==='reentryXY'?'56':'64')&&++visits===2)try{x.frame.runFrame();}catch{}
   return native(o,k);
  }) as typeof native;
  const expected=fault==='zero'||fault==='square2'?'unsupported model-backed estimator':fault==='gqr'?'explicit GQR0':fault==='fpscr'?'explicit FPSCR':fault.startsWith('readonly')?'non-writable':'private active scheduler invocation required';
  try{refuses(()=>x.frame.runFrame(),expected);}finally{Object.getOwnPropertyDescriptor=native;}
  check(armed,'fault reaches actual Normalize profile boundary');
  if(fault==='readonlyY'||fault==='reentryXY')check(x.allocator.readU32(x.child,0x38)===0x3f800000,'failed paired XY admission preserves both destinations');
  if(fault==='readonlyZ'||fault==='reentryZ')check(x.allocator.readU32(x.child,0x38)===0x3f7fffff&&x.allocator.readU32(x.child,0x40)===0,'later Z failure preserves normalized XY prefix');
 }
 console.log(`[projectile-normalize-outer] PASS: ${count} actual outer/root Normalize fixtures; model-backed finite domain only`);
}
