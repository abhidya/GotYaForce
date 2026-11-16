import {createProjectileNormalizeOuterTestFixture} from './projectile-normalize-outer.selftest.js';
import type {createProjectileInitializerTailBaseTestFixture} from './attached-setup-animation.selftest.js';
type Make=typeof createProjectileInitializerTailBaseTestFixture;
const ROW={speed10:40,word14:4,field28:Math.fround(.3),field30:2,descriptor00:14};
function check(ok:boolean,why:string):void{if(!ok)throw Error('[projectile-initializer-tail-test] '+why);}
function refuses(f:()=>unknown,part:string):void{let m='';try{f();}catch(e){m=String(e)}check(m.includes(part),`expected ${part}, got ${m}`);}
export function createProjectileInitializerTailTestFixture(make:Make,tail:Partial<typeof ROW>=ROW){
 return createProjectileNormalizeOuterTestFixture(()=>make(tail));
}
export function runProjectileInitializerTailSelfTests(make:Make):void{
 let count=0;const fresh=(tail:Partial<typeof ROW>=ROW)=>{count++;return createProjectileInitializerTailTestFixture(make,tail);};
 const stop='80006f78';
 {
  const x=fresh();refuses(()=>x.frame.runFrame(),stop);
  check(x.allocator.readF32(x.child,0x40)===Math.fround(Math.fround(0.9999999403953552)*40),'actual Normalize output scaled by real row40');
  check(x.allocator.readF32(x.child,0x44)===40&&Object.is(x.allocator.readF32(x.child,0x48),0),'fresh speed then decoded positive-zero stores');
  check(x.allocator.readF32(x.child,0x50)===ROW.field28&&x.allocator.readF32(x.child,0x154)===2,'same row tail floats');
  check(x.allocator.readU16(x.child,0x1e)===4&&x.allocator.readU8(x.child,0x19)===1&&x.allocator.readU16(x.child,0x1c)===600,'source lowhalf and lifetime stores');
  check(x.groups[9]!.head===x.child&&x.drawList.tail===x.child,'same genuine projectile stays in actual group/draw lists');
 }
 for(const absent of ['word14','field28','field30','descriptor00']as const){
  const row={...ROW};delete (row as Partial<typeof ROW>)[absent];const x=fresh(row);
  refuses(()=>x.frame.runFrame(),absent);
  check(x.allocator.readF32(x.child,0x44)===40&&x.allocator.readF32(x.child,0x48)===0,'missing later row preserves scale and earlier scalar prefix');
  if(absent==='descriptor00')check(x.allocator.readF32(x.child,0x154)===2,'descriptor missing only after actual154 store');
 }
 for(const fault of ['readonlyY','readonlyZ','readonly48','reentry','staleGqr']as const){
  const x=fresh(),row=x.projectiles.getSpawnRow1(),native=Object.getOwnPropertyDescriptor;
  let armed=false,visits=0,profileReads=0;
  Object.getOwnPropertyDescriptor=((o:object,k:PropertyKey)=>{
   const d=native(o,k);
   if(!armed&&o===row&&k==='speed10'){
    armed=true;
    if(fault==='readonlyY')Object.defineProperty(x.objectBytes,'60',{writable:false});
    if(fault==='readonlyZ'){const b=new DataView(new ArrayBuffer(4));b.setFloat32(0,1,false);for(let i=0;i<4;i++)x.objectBytes[0x38+i]=b.getUint8(i);Object.defineProperty(x.objectBytes,'64',{writable:false});}
    if(fault==='readonly48')Object.defineProperty(x.objectBytes,'72',{writable:false});
   }
   if(armed&&fault==='reentry'&&o===x.objectBytes&&k==='56'&&++visits===2)try{x.frame.runFrame();}catch{}
   if(armed&&fault==='staleGqr'&&o===x.normalizeProcessor&&k==='gqr0'&&++profileReads===3)x.normalizeProcessor.gqr0=1;
   return d;
  })as typeof native;
  try{refuses(()=>x.frame.runFrame(),fault==='staleGqr'?'Scale requires GQR0':fault==='reentry'?'private active scheduler invocation required':'non-writable');}finally{Object.getOwnPropertyDescriptor=native;}
  check(armed,'fault occurs after Normalize at real row speed load');
  if(fault==='readonlyY'||fault==='readonlyZ'||fault==='reentry'||fault==='staleGqr')check(x.allocator.readF32(x.child,0x40)===0.9999999403953552,'failed Scale preserves prior normalized Z');
  if(fault==='readonlyZ')check(x.allocator.readF32(x.child,0x38)===40,'late Z fault retains completed scaled XY pair');
  if(fault==='readonly48')check(x.allocator.readF32(x.child,0x44)===40,'later zero-store fault retains fresh speed store');
 }
 {
  const x=fresh(),row=x.projectiles.getSpawnRow1(),native=Object.getOwnPropertyDescriptor,seen:string[]=[];
  Object.getOwnPropertyDescriptor=((o:object,k:PropertyKey)=>{if(o===row&&Object.hasOwn(ROW,k)){seen.push(String(k));if(k==='speed10')x.objectBytes[0x11]=2;}return native(o,k);})as typeof native;
  try{refuses(()=>x.frame.runFrame(),stop);}finally{Object.getOwnPropertyDescriptor=native;}
  check(seen.join(',')==='speed10,speed10,field28,word14,field30,descriptor00','captured row and fresh second speed read retain source order despite later child11 mutation');
  check(x.allocator.readF32(x.child,0x154)===2&&x.objectBytes[0x11]===2,'later variant mutation does not replace captured row');
 }
 console.log(`[projectile-initializer-tail] PASS: ${count} genuine normal-entry Scale/store fixtures; mandatory resource helpers remain unsupported`);
}
