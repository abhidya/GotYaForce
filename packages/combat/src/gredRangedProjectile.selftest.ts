/** Pure adapter fixtures. Actual ordinary-B routing and damage are tested in
 * gredShotBattle; these isolate original capture predicates and static bind data. */
import {createRomActor} from './rom/actor.js';
import type {BorgRuntime} from './types.js';
import {spawnGredRangedSource,advanceGredRangedSource,GRED_RANGED_SOURCE,prepareGredRangedEntryVisibility} from './gredRangedProjectile.js';
function assert(ok:unknown,msg:string):asserts ok{if(!ok)throw Error(`[gredRangedProjectile] ${msg}`);}
function near(a:number,b:number,msg:string){assert(Math.abs(a-b)<.0001,`${msg}: ${a} != ${b}`);}
const f=Math.fround;
function fixture(id='pl0615',scale=1){
 const actor=createRomActor();actor.actionIndex=0;actor.modelScale=scale;actor.visibilityBit=4;
 const owner={uid:'owner',borgId:id,team:0,alive:true,hp:100,state:'idle',pos:{x:0,y:0,z:0},rotY:0,lockTarget:'target'} as unknown as BorgRuntime;
 const target={uid:'target',borgId:'pl0615',team:1,alive:true,hp:100,state:'idle',pos:{x:4200,y:5600,z:0},rotY:0,
  targetEligibility83:0,targetVisibilityMask5e6:4} as unknown as BorgRuntime;
 const other={...target,uid:'other',pos:{x:-2000,y:0,z:2000}} as BorgRuntime;
 const row=id==='pl0615'?43:id==='pl0629'?101:102;
 const all=[owner,target,other],byUid=new Map(all.map(b=>[b.uid,b]));
 const spawn=()=>spawnGredRangedSource(owner,actor,0x800c3be0,row,all)![0]!;
 return {actor,owner,target,other,row,all,byUid,spawn};
}
export function runGredRangedProjectileSelfTest():void{
 {
  const actor=createRomActor();actor.visibilityBit=4;
  const selected={eligibility83:0,controlWord:0x80000000,visibilityMask5e6:0xa0};
  const other={eligibility83:0,controlWord:0,visibilityMask5e6:0xff};
  actor.visibilityRoster=[selected,other];actor.visibilityTarget=selected;
  prepareGredRangedEntryVisibility(actor);
  assert(selected.visibilityMask5e6===0xa4&&other.visibilityMask5e6===0xfb,'6a104 changes only owner bit and unlike6bf80 ignores selected highcontrol');
  selected.eligibility83=1;prepareGredRangedEntryVisibility(actor);
  assert(Number(selected.visibilityMask5e6)===0xa0&&other.visibilityMask5e6===0xfb,'nonzero83 prevents initial re-add');
  selected.eligibility83=0;prepareGredRangedEntryVisibility(actor,true);
  assert(Number(selected.visibilityMask5e6)===0xa0,'6b8 blocked capture cannot re-add visibility');
  actor.visibilityTarget=null;prepareGredRangedEntryVisibility(actor);
  assert(Number(selected.visibilityMask5e6)===0xa0,'null captured pointer leaves owner bit clear');
 }

 for(const id of ['pl0615','pl0629','pl062a'])for(const scale of [.5,1,2]){
  const t=fixture(id,scale),p=t.spawn(),s=p.gredRangedSource!;
  assert(s.captureFlags===7,'valid enemy at inclusive3D7000 retains homing, independent of model scale');
  advanceGredRangedSource(p,t.byUid);assert(s.targetUid===t.target.uid&&s.flight.targetPoint!==null,'eligible captured enemy retained at initialization');
  const [x,y,z]=GRED_RANGED_SOURCE.jointBind;
  near(s.flight.origin.x,f(f(x+(id==='pl0629'?-196.8000030517578:-106.80000305175781))*scale),'original static joint7 plus rowX');
  near(s.flight.origin.y,f(f(y-3.5999999046325684)*scale),'jointY plus row offset');
  near(s.flight.origin.z,f(f(z+30)*scale),'jointZ plus row offset');
  t.target.pos.y=5601;const beyond=t.spawn();assert(beyond.gredRangedSource!.captureFlags===3,'3D above7000 clears bit4 even whenXZ remains4200');
  advanceGredRangedSource(beyond,t.byUid);
  assert(beyond.gredRangedSource!.targetUid===null&&beyond.gredRangedSource!.flight.targetPoint===null,'beyond-range target is not homed');
  assert(beyond.vel.x>0&&beyond.vel.y>0,'beyond homing range still supplies eligible initial aim');
  t.target.pos={x:4200,y:5600,z:0};t.target.team=0;
  assert(t.spawn().gredRangedSource!.captureFlags===5,'ally capture omits enemy bit but shares source7000 range');
 }
 for(const mode of ['hidden','wrong-bit','eligible83','matching-bit'] as const){
  const t=fixture();t.target.targetVisibilityMask5e6=mode==='matching-bit'?4:mode==='wrong-bit'?1:0;
  t.target.targetEligibility83=mode==='eligible83'?1:0;
  const p=t.spawn();advanceGredRangedSource(p,t.byUid);
  const accepted=mode==='eligible83'||mode==='matching-bit';
  assert((p.gredRangedSource!.targetUid!==null)===accepted,'6ec84 uses target83 OR matching owner visibility bit');
  if(!accepted){near(p.vel.x,0,'visibility failure initial aim uses owner forwardX');near(p.vel.y,0,'visibility failure initial aim uses forwardY');near(p.vel.z,80,'visibility failure initial speed80 forward');}
 }
 {
  const t=fixture(),p=t.spawn();t.target.targetVisibilityMask5e6=0;
  advanceGredRangedSource(p,t.byUid);assert(p.gredRangedSource!.targetUid===null,'visibility is checked at init, not only allocation');
 }
 {
  const t=fixture();t.owner.sourceGredRangedCaptureBlocked6b8=true;
  const p=t.spawn();assert(p.gredRangedSource!.captureFlags===0&&p.gredRangedSource!.targetUid===null,'explicit6b8 suppression clears all captured fields');
  advanceGredRangedSource(p,t.byUid);near(p.vel.z,80,'suppression uses owner forward');near(p.vel.x,0,'suppression does not aim at selected target');
 }
 {
  const t=fixture(),p=t.spawn();advanceGredRangedSource(p,t.byUid);
  t.owner.lockTarget=t.other.uid;t.target.pos={x:4000,y:5500,z:100};advanceGredRangedSource(p,t.byUid);
  assert(p.gredRangedSource!.targetUid===t.target.uid&&p.gredRangedSource!.flight.targetPoint?.x===4000,'new selection cannot replace captured projectile target');
  t.target.hp=0;advanceGredRangedSource(p,t.byUid);assert(p.gredRangedSource!.targetUid===null,'target loss clears tracking after active update');
  t.target.hp=100;advanceGredRangedSource(p,t.byUid);assert(p.gredRangedSource!.targetUid===null,'cleared target never reacquires');
 }
 {
  const t=fixture();t.owner.rotY=Math.PI/2;t.owner.sourceGredRangedCaptureBlocked6b8=true;
  const p=t.spawn();advanceGredRangedSource(p,t.byUid);near(p.vel.x,80,'static fallback follows owner yaw');near(p.vel.z,0,'static yaw transform is not fixedworldZ');
  near(p.gredRangedSource!.flight.origin.x,f(GRED_RANGED_SOURCE.jointBind[2]+30),'static joint forward rotatesintoX');
 }
 {
  const t=fixture();assert(spawnGredRangedSource(t.owner,t.actor,0x800c3be0,101,t.all)===null,'wrong familyrow remains legacy');
  t.actor.actionIndex=3;assert(spawnGredRangedSource(t.owner,t.actor,0x800c3be0,43,t.all)===null,'unrelated action remains legacy');
 }
 console.log('[gredRangedProjectile] PASS: capture7000, family binds, visibility6ec84, suppression and retained target identity');
}
