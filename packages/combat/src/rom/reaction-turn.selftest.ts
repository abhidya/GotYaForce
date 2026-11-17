import {createRomActor} from './actor.js';
import {seedReactionTurn,stepReactionTurn} from './helpers.js';
function check(ok:boolean,message:string):void {if(!ok)throw Error(`[reaction-turn] ${message}`);}
export function runReactionTurnSelfTest():void {
  for(const direction of [-1,1]) {
    const a=createRomActor();a.heading=32760;a.turnErrorYaw=direction*101;a.activeYaw=1234;
    seedReactionTurn(a,4);check(a.poseAccum7e===direction*25,'signed division truncates toward zero');
    for(let i=0;i<4;i++)check(!stepReactionTurn(a),'remainder keeps turn active');
    check(stepReactionTurn(a),'overshoot settles');
    const expected=((32760+direction*101+32768)&65535)-32768;
    check(a.heading===expected&&a.turnErrorYaw===0&&a.poseAccum7e===0,'settlement restores remainder across heading wrap');
    check(a.activeYaw===1234,'does not overwrite active target');
  }
  const a=createRomActor();a.poseAccum7e=17;a.turnErrorYaw=3;
  seedReactionTurn(a,0);check(a.poseAccum7e===17,'zero duration preserves velocity');
  seedReactionTurn(a,4);check(a.poseAccum7e===0,'integer division may yield zero');
  a.heading=91;check(stepReactionTurn(a)&&a.heading===91&&a.turnErrorYaw===0,'zero velocity clears error without heading correction');
  a.poseAccum7e=1;a.turnErrorYaw=10;a.dt=.25;
  check(stepReactionTurn(a)&&a.heading===101,'zero rounded step uses nonpositive branch and settles positive error');
  a.poseAccum7e=-1;a.turnErrorYaw=-10;a.dt=.25;
  check(!stepReactionTurn(a)&&a.turnErrorYaw===-10,'zero rounded step does not settle negative error');
  a.poseAccum7e=-32768;a.turnErrorYaw=-32768;seedReactionTurn(a,-1);
  check(a.poseAccum7e===-32768,'division result stores as signed short');
  a.heading=0;a.dt=2;a.poseAccum7e=20000;a.turnErrorYaw=30000;
  check(!stepReactionTurn(a)&&a.heading===-25536&&a.turnErrorYaw===-10000,'scaled step wraps to signed short before branch');
  // Float32 product, not JS double: this product rounds exactly up to integer1.
  a.heading=0;a.turnErrorYaw=10;a.poseAccum7e=25;a.dt=Math.fround(1/25);
  check(!stepReactionTurn(a)&&a.heading===1&&a.turnErrorYaw===9,'float32 step product');
  a.heading=44;a.turnErrorYaw=9;a.poseAccum7e=3;a.dt=Infinity;
  let rejected=false;try{stepReactionTurn(a);}catch{rejected=true;}
  check(rejected&&a.heading===44&&a.turnErrorYaw===9,'unsupported conversion fails before mutation');
  // Deterministic integer-rate oracle: exact arithmetic throughout this domain.
  let cases=0;
  for(const error of [-32768,-100,-1,0,1,100,32767])for(const duration of [-8,-1,1,3,16])for(const dt of [0,1,2]){
    const b=createRomActor();b.heading=30000;b.turnErrorYaw=error;b.dt=dt;
    const short=(x:number)=>((Math.trunc(x)&65535)^32768)-32768;
    const velocity=short(Math.trunc(error/duration));seedReactionTurn(b,duration);
    check(b.poseAccum7e===velocity,'oracle seed');
    const step=short(velocity*dt),remaining=short(error-step);
    const done=velocity===0||(step<=0?remaining>=0:remaining<=0);
    const heading=velocity===0?30000:short(30000+step+(done?remaining:0));
    check(stepReactionTurn(b)===done&&b.heading===heading&&b.turnErrorYaw===(done?0:remaining),'integer oracle');cases++;
  }
  console.log(`[reaction-turn] PASS: ${cases} oracle cases and signed/zero/wrap/conversion boundaries`);
}
