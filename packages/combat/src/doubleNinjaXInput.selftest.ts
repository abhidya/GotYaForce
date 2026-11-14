import {stepDoubleNinjaXInput} from './doubleNinjaXInput.js';
import type {BorgRuntime} from './types.js';
function check(v:unknown,m:string):void{if(!v)throw Error(`[doubleNinjaXInput] ${m}`);}
const fixture=()=>({sourceAmmoRefillRate:1} as BorgRuntime);
export function runDoubleNinjaXInputSelfTest():void{
  {
    const b=fixture();
    for(let i=1;i<=10;i++){const s=stepDoubleNinjaXInput(b,true);check(s.warmup===i&&s.charge===0,'ten updates warm up without banking');check(s.pressEdge===(i===1),'one press edge per held sequence');}
    for(let i=1;i<=119;i++){const s=stepDoubleNinjaXInput(b,true);check(s.charge===i,'one bank unit per source rate');}
    check(!stepDoubleNinjaXInput(b,false).releasedReady,'129 held updates are not ready');
    check(b.doubleNinjaXInput?.charge===117&&b.doubleNinjaXInput.warmup===0,'release decays after readiness check and clears ramp');
  }
  {
    const b=fixture();for(let i=0;i<130;i++)stepDoubleNinjaXInput(b,true);
    const s=stepDoubleNinjaXInput(b,false);check(s.releasedReady&&s.charge===118,'130 held updates release before decay');
    check(!stepDoubleNinjaXInput(b,false).releasedReady,'release readiness cannot repeat after decay');
  }
  {
    const b=fixture();b.sourceAmmoRefillRate=.5;
    for(let i=0;i<249;i++)stepDoubleNinjaXInput(b,true);
    check(b.doubleNinjaXInput?.charge===119.5,'source rate independent of animationdt');
    stepDoubleNinjaXInput(b,true);check(stepDoubleNinjaXInput(b,false).releasedReady,'half rate needs250 held updates');
  }
  {
    const b=fixture();b.burstPaired=true;b.sourceAmmoRefillRate=1.5;
    for(let i=0;i<17;i++)stepDoubleNinjaXInput(b,true);
    check(b.doubleNinjaXInput?.charge===105,'paired extra10 uses already1.5 rate after warmup');
    stepDoubleNinjaXInput(b,true);const s=stepDoubleNinjaXInput(b,false);
    check(s.releasedReady&&s.charge===117,'paired18 qualifies but release decay uses base rate only');
  }
  {
    const b=fixture();b.doubleNinjaLegacyChargeActive=true;b.state='special';
    for(let i=0;i<40;i++){
      b.command=null;const s=stepDoubleNinjaXInput(b,true);
      check(s.warmup===0&&s.charge===0,'admitted legacy type5 survives per-frame command changes');
    }
    b.state='hit';const s=stepDoubleNinjaXInput(b,true);
    check(!b.doubleNinjaLegacyChargeActive&&s.warmup===1,'interruption clears retained action identity before next input sample');
  }
  for(const block of ['active','flag'] as const){
    const b=fixture();for(let i=0;i<130;i++)stepDoubleNinjaXInput(b,true);
    if(block==='flag')b.sourceDoubleNinjaInputBlock58e=0x20;
    const s=stepDoubleNinjaXInput(b,true,block==='active');
    check(s.charge===0&&s.warmup===0&&!s.releasedReady,'active type5 or58e20 reset both clocks');
    check(!stepDoubleNinjaXInput(b,false).releasedReady,'blocked bank cannot leak a release');
  }
}
