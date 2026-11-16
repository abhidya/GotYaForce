import {createSourcePlayerContactTestFixture} from './source-player-contact.selftest.js';
import type {createBattleTargetPreparationTestFixture} from './attached-setup-animation.selftest.js';
type Make=typeof createBattleTargetPreparationTestFixture;
function check(ok:boolean,why:string):void{if(!ok)throw Error('[battle-contact-callback-prefix-test] '+why);}
function refuses(f:()=>unknown,want:string):void{let got='';try{f();}catch(e){got=String(e);}check(got.includes(want),`expected ${want}, got ${got}`);}
/** Actual previously-created HITs with explicit synthetic owner/state inputs. No
 * object creation, model loading or callback-success replacement is supplied. */
export function runBattleContactCallbackPrefixSelfTests(make:Make):void{
 let count=0;
 const fresh=()=>{
  count++;const x=createSourcePlayerContactTestFixture(make),hits:symbol[]=[],bytes:Record<number,number>[]=[];
  let id=x.groups[49]!.head!;while(id!==null){hits.push(id);const data=x.allocator.getObject(id)as Record<number,number>;data[0x10]=3;data[0x13]=77;x.allocator.writePointer(id,0x20,x.child);bytes.push(data);id=x.allocator.readPointer(id,8)!;}
  check(hits.length>0,'genuine existing HIT list required');
  const ownerId=x.allocator.readPointer(hits[0]!,0x20)!;check(ownerId===x.child,'actual HIT points to original projectile');
  const owner=x.allocator.getObject(ownerId)as Record<number,number>;
  const counters=Object.fromEntries(['50','4e','4c','4a','48','46','44','42','40','3e'].map(s=>['half804362'+s,77]));
  Object.assign(x.outerSources,{contactCounters:counters});
  // Explicit empty final contact group is supplied input, not a runtime bypass.
  if(x.groups[55]===undefined)x.groups[55]={head:null,tail:null};
  return Object.assign(x,{contactHits:hits,contactHitBytes:bytes,firstHit:hits[0]!,hitData:bytes[0]!,contactOwnerBytes:owner,contactOwnerId:ownerId,counters});
 };
 type Fixture=ReturnType<typeof fresh>;
 const run=(x:Fixture,want:string,hook:(o:object,k:PropertyKey)=>void=()=>{}):void=>{
  const native=Object.getOwnPropertyDescriptor;let selected=false;
  Object.getOwnPropertyDescriptor=((o:object,k:PropertyKey)=>{
   if(!selected&&o===x.match&&k==='byte66'&&x.match.wordB0===0){selected=true;x.match.byte66=0;}
   const d=native(o,k);if(selected)hook(o,k);return d;
  })as typeof native;
  try{refuses(()=>x.frame.runFrame(),want);}finally{Object.getOwnPropertyDescriptor=native;}
  check(x.groups[9]!.head===x.child&&x.groups[49]!.head===x.firstHit,'no list unlink or replacement on supported prefix');
  check(Object.values(x.slotRecords).every(r=>r.contact26f===77),'later target/contact work not fabricated');
  refuses(()=>x.frame.runFrame(),'permanently incomplete');
 };
 const end='800294f4 reached required8002bb14',transform0='8008a728 reached required8020b7a8',transform1='8008a888 reached required8020b7a8';
 for(const state of [3,255]){
  const x=fresh();for(const b of x.contactHitBytes){b[0x10]=state;for(const k of [0x4a,0x4b,0x60,0x61,0x62,0x63])delete b[k];}
  run(x,end);check(x.contactHitBytes.every(b=>b[0x13]===0),'all real active callback returns clear13 and advance actualnext8');
 }
 {
  const x=fresh();x.hitData[0x10]=0;run(x,transform0);check(x.hitData[0x13]===0,'real state0 prefix precedes matrix call');
 }
 {
  const x=fresh();x.hitData[0x10]=1;
  for(const [o,v]of [[0x30,0x7fc00001],[0x34,0x80000000],[0x38,0x3f800000],[0x3c,11],[0x40,12],[0x44,13]])x.allocator.writeU32(x.firstHit,o!,v!);
  run(x,transform1);check(x.allocator.readU32(x.firstHit,0x3c)===0x7fc00001&&x.allocator.readU32(x.firstHit,0x40)===0x80000000&&x.allocator.readU32(x.firstHit,0x44)===0x3f800000,'state1 raw copies preserve payload bits before transform');
 }
 for(const owner281 of [0,128]){
  const x=fresh();x.hitData[0x10]=2;x.contactOwnerBytes[0x281]=owner281;run(x,'8008aa0c reached required8008aa40');check(x.hitData[0x10]===(owner281===0?1:2),'mode2 exact conditional state write');check(x.hitData[0x13]===0,'mode2 prior13 clear retained');
 }
 for(const fault of ['release1d8','releaseInactive','releaseMismatch','timerMinusOne','signedMatch','nullOwner','externalOwner','nullDescriptor','missingDescriptor','readonly13','reentry13','lateReadonly40','capturedOwner']as const){
  const x=fresh();let changed=false;
  if(fault==='release1d8')x.contactOwnerBytes[0x1d8]=1;
  if(fault==='releaseInactive')x.contactOwnerBytes[0]=0;
  if(['releaseMismatch','timerMinusOne','signedMatch'].includes(fault)){
   x.contactOwnerBytes[0x83]=0;x.allocator.writeU16(x.firstHit,0x4a,fault==='timerMinusOne'?65535:1);
   if(fault!=='timerMinusOne'){x.contactOwnerBytes[0x1cec]=255;x.contactOwnerBytes[0x1ced]=128;x.allocator.writeU16(x.firstHit,0x4c,fault==='signedMatch'?(-4096-128)&65535:1);}
  }
  if(fault==='nullOwner')x.allocator.writePointer(x.firstHit,0x20,null);
  if(fault==='externalOwner')x.allocator.writePointer(x.firstHit,0x20,x.actor);
  if(fault==='nullDescriptor')x.allocator.writePointer(x.firstHit,0x28,null);
  if(fault==='missingDescriptor')delete x.hitData[0x28];
  if(fault==='readonly13')Object.defineProperty(x.hitData,String(0x13),{writable:false});
  if(fault==='lateReadonly40'){
   x.hitData[0x10]=1;for(const [o,v]of [[0x30,0x01020304],[0x34,0x05060708],[0x38,0x090a0b0c],[0x3c,11],[0x40,12],[0x44,13]])x.allocator.writeU32(x.firstHit,o!,v!);
  }
  const expected=fault.startsWith('release')?'required80088e50':fault==='nullOwner'?'null contact owner':fault==='externalOwner'?'external actor owner unsupported':fault==='missingDescriptor'?'own data':fault==='readonly13'?'writable scalar':fault==='reentry13'?'reentry':fault==='lateReadonly40'?'scalar destination changed':end;
  run(x,expected,(o,k)=>{
   if(!changed&&o===x.hitData&&k==='19'&&fault==='reentry13'){changed=true;try{x.frame.runFrame();}catch{}}
   if(!changed&&o===x.hitData&&k===String(0x43)&&fault==='lateReadonly40'){changed=true;Object.defineProperty(x.hitData,String(0x40),{writable:false});}
   if(!changed&&o===x.hitData&&k===String(0x23)&&fault==='capturedOwner'){changed=true;for(let i=0;i<4;i++)x.hitData[0x20+i]=0;}
  });
  if(fault.startsWith('release')||['nullOwner','externalOwner','readonly13','reentry13'].includes(fault))check(x.hitData[0x13]===77,'refusal before13 store preserves it');
  else check(x.hitData[0x13]===0,'earlier13 source store persists');
  if(fault==='lateReadonly40')check(x.allocator.readU32(x.firstHit,0x3c)===0x01020304&&x.allocator.readU32(x.firstHit,0x40)===12&&x.allocator.readU32(x.firstHit,0x44)===13,'scalar refusal preserves previous complete store, no partial current store');
 }
 console.log(`[battle-contact-callback-prefix] PASS: ${count} canonical existing HIT callback fixtures; exact prefix and honest transform/release/validity bounds`);
}
