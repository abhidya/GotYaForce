import type {BorgRuntime} from './types.js';
import {stepTeleportXInput,prepareTeleportX,stepTeleportX,clearTeleportX,getTeleportXState} from './teleportX.js';
import {createRomActor} from './rom/actor.js';
function assert(ok:unknown,msg:string):asserts ok{if(!ok)throw Error(`[teleportX] ${msg}`);}
const f=Math.fround;
export function runTeleportXSelfTest():void{
  const b={sourceAmmoRefillRate:1,burstPaired:false} as BorgRuntime;
  for(let n=1;n<=130;n++){
    const s=stepTeleportXInput(b,true);
    assert(s.pressEdge===(n===1),'press edge is one update');
    assert(s.warmup===Math.min(n,10)&&s.charge===Math.max(0,n-10),'ten ramp updates then one-unit bank');
  }
  const release=stepTeleportXInput(b,false);
  assert(release.releasedReady&&release.charge===118,'readiness precedes release decay');
  assert(!stepTeleportXInput(b,false).releasedReady,'post-decay idle cannot emit another charge');
  stepTeleportXInput(b,true,true);assert(Number(b.teleportXInput?.charge)===0&&b.teleportXInput?.warmup===0,'active type5 clears bank');
  b.sourceAmmoRefillRate=.25;
  for(let n=0;n<11;n++)stepTeleportXInput(b,true);
  assert(Number(b.teleportXInput?.charge)===.25,'charge uses768 rate, not animationdt or literal768');
  b.sourceTeleportInputBlock58e=0x20;stepTeleportXInput(b,true);
  assert(Number(b.teleportXInput?.charge)===0&&b.teleportXInput?.warmup===0,'58e bit20 resets charge');
  b.sourceTeleportInputBlock58e=0;b.burstPaired=true;b.sourceAmmoRefillRate=1.5;
  for(let n=0;n<18;n++)stepTeleportXInput(b,true);
  assert(Number(b.teleportXInput?.charge)===120,'paired source7681.5 times6fc10 reaches cap after8 bank updates');
  stepTeleportXInput(b,false);assert(Number(b.teleportXInput?.charge)===117,'release decay uses base768, no extra burst10');
  const a=createRomActor();a.pos={x:10,y:20,z:30};a.targetCache5e8={x:9,y:18,z:27};a.dt=1;
  a.physicsRuntime={clampToGround:(pos,velY)=>({y:pos.y,velY,grounded:false})};
  b.deathFlags=0x80;b.sourceTeleportRecentMeleeTimer144=8;
  const s=prepareTeleportX(a,b,'captured',{...a.pos});let debit=0;
  stepTeleportX(a,{onAllocateResource:()=>{debit++;return false;}});
  assert(debit===1&&s.phase===1&&s.timer558===3,'body ignores denied debit and enters same-callP1');
  assert(s.destination9c.x===10&&s.destination9c.y===820&&s.destination9c.z===30,'zero target delta follows6ebb4 upward fallback');
  assert(a.motion.x===1&&a.motion.y===2&&a.motion.z===3&&a.pos.x===11,'target destination never overwrites own carry');
  assert(s.flags272===0x82,'source defense bit preserves other status bits');
  for(let n=0;n<4;n++)stepTeleportX(a,{});
  assert(s.visibility82===0&&a.pos.y===f(f(f(.1)*820)+f(f(1-f(.1))*28)),'first hidden movement uses separate f32 weighted products');
  b.sourceDefenseDisabled=true;b.sourceHidden=true;clearTeleportX(a,b);
  assert(!getTeleportXState(a)&&b.sourceDefenseDisabled===undefined&&b.sourceHidden===undefined&&b.deathFlags===0x80,'interruption clears only owned exposure and preserves death flags');
  for(const dt of [1,.5]){
    const a=createRomActor();a.dt=dt;
    const s=prepareTeleportX(a,b,null,null);s.phase=2;s.timer558=dt;s.airLatch54a=0;
    s.flags6e8=2;s.flags6e9=2;s.stateMode71d=1;
    stepTeleportX(a,{});
    assert(s.stream?.blendTotal===f(2+dt)&&s.stream.frame===0,'recovery blend total uses actual entrydt');
    assert(s.flags6e8===0&&s.flags6e9===0&&s.stateMode71d===0&&(a.controlWord&0xff0)===0,'verified ground recovery state and posture reset');
    for(let n=0;n<2/dt;n++){stepTeleportX(a,{});assert(s.stream.frame===0,'source recovery never escapes blend before actor exit');}
    assert(s.exitKind==='ground','ground recovery posture selects source ground return');
  }
  console.log('[teleportX] PASS: source charge ramp/rate/release/reset, explicit target fixture, ignored body debit and isolated cleanup');
}
