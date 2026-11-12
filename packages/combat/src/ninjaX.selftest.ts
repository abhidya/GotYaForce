import {createRomActor,type Vec3} from './rom/actor.js';
import type {StreamContext} from './rom/stream-vm.js';
import {prepareNinjaX,stepNinjaX,startNinjaXStream,tickNinjaXStreamPart,releaseNinjaX} from './ninjaX.js';
const f=Math.fround,v=(x:number,y:number,z:number):Vec3=>({x,y,z});
function assert(ok:unknown,msg:string):asserts ok{if(!ok)throw Error(`[ninjaX] ${msg}`);}
function same(a:unknown,b:unknown,msg:string){assert(JSON.stringify(a)===JSON.stringify(b),`${msg}: ${JSON.stringify(a)} != ${JSON.stringify(b)}`);}
function fixture(air=false){
 const a=Object.assign(createRomActor(),{grounded:false,lockTarget:null as Vec3|null,onStartStream:(_g:number,_s:number,_m:number):boolean=>true,onTickStreamPart:(_i:number):boolean=>true});
 a.borgNumber=0;a.actionIndex=2;a.variantIndex=air?4:0;a.controlWord=air?0x40:0;a.pos=v(100,200,300);a.savedGroundPos={...a.pos};a.targetCache5e8=v(99,198,296);a.dt=1;a.timescale=1;
 a.physicsRuntime={clampToGround:(_p,vy)=>({y:_p.y,velY:vy,grounded:false})};
 const s=prepareNinjaX(a,null,null),events:string[]=[];
 const ctx:StreamContext={onAllocateResource:(_a,i,n,c)=>{events.push(`ammo:${i}/${n}/${c}`);return true;},
  onFamilyProjectile:(_a,address,row)=>events.push(`child:${address.toString(16)}/${row}`),onPlayAnim:(_a,g,slot)=>events.push(`anim:${g}/${slot}`)};
 a.onStartStream=(g,slot,mask)=>startNinjaXStream(a,g,slot,mask,ctx);
 a.onTickStreamPart=i=>tickNinjaXStreamPart(a,i,ctx);return {a,s,ctx,events};
}
export function runNinjaXSelfTest():void{
 for(const air of [false,true]){
  const {a,s,ctx,events}=fixture(air);a.poseAccum7c=1;a.poseAccum7e=2;a.poseAccum80=3;a.accumulator80c=4;
  stepNinjaX(a,ctx);same(a.motion,v(f(.95),f(2*f(.95)),f(4*f(.95))),'source own-history startup');
  same([a.poseAccum7c,a.poseAccum7e,a.poseAccum80,a.accumulator80c],[0,0,0,0],'startup resets');
  assert(s.stream?.slot===(air?1:0)&&a.fbPhaseSlots[0]===1,'control40 chooses stream');
  for(let n=1;n<=20;n++){stepNinjaX(a,ctx);assert(s.callbackCount===0,'no release before authored14');}
  stepNinjaX(a,ctx);assert(s.callbackCount===1&&s.fireCount===1&&Number(a.fbPhaseSlots[0])===2,'exact authored release');
  same(events.filter(e=>!e.startsWith('anim')),['ammo:2/1/1','child:8007db5c/0'],'debit precedes source allocation');
  same([a.hSpeed,a.yVel,a.gravityCoeff],air?[10,15,-1]:[0,0,0],'only air dash32 triggers backflip');
  assert(s.stateMode71d===1&&s.supportHeight6d0===0,'opcode08 support override shadow');
  a.inputHeld5d8=0;a.physicsRuntime={clampToGround:(_p,vy)=>({y:_p.y,velY:vy,grounded:false})};
  for(let n=0;n<70&&s.exitKind===null;n++)stepNinjaX(a,ctx);
  assert(s.exitKind==='stream-end'&&Number(s.stateMode71d)===0&&s.supportHeight6d0===null,'recovery play clears71d and completion exits');
 }
 {
  const {a,s,events}=fixture();a.dashStrength1d0f=32;a.activeYaw=123;a.heading=456;
  releaseNinjaX(a,s,{onAllocateResource:()=>false,onFamilyProjectile:()=>events.push('bad')});
  assert(a.lockYaw===456-32768&&a.activeYaw===123&&a.yVel===15&&s.resourceDenied&&s.fireCount===0,'failed ammo still conditional backflip, activeYaw unchanged');
 }
 {
  const {a,s,ctx}=fixture();a.borgNumber=0xa;releaseNinjaX(a,s,ctx);assert(s.fireCount===1,'Sasuke callback allocated');
 }
 console.log('[ninjaX] PASS: own-history startup, authored trigger, conditional recoil, ammo order, support reset and completion');
}
