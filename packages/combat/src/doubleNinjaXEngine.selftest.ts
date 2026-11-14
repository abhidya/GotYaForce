import {tickDoubleNinjaXEngine, type DoubleNinjaXEngineHooks, type DoubleNinjaXEngineState} from './doubleNinjaXEngine.js';
const f = Math.fround;
function assert(value: unknown, message: string): void {
  if (!value) throw Error(`[doubleNinjaXEngine] ${message}`);
}
function fixture() {
  const s: DoubleNinjaXEngineState = {
    phase:0,dt:1,pos:{x:10,y:20,z:30},savedOwnPos5e8:{x:8,y:17,z:34},motion:{x:90,y:91,z:92},
    arm7c8:1,offset7b0:{x:150,y:0,z:0},matrixX8d4:{x:.5,y:1,z:-2},
    timer560:99,timer558:99,magnitude55c:99,hSpeed:8,yVel:9,hDecel:10,gravityCoeff:-1,
    poseAccum80:1,poseAccum7e:2,poseAccum7c:3,controlWord:3,streamEnded1cee:0,actionFlag73f:1,
  };
  const calls: string[] = []; const angles: number[] = [];
  const h: DoubleNinjaXEngineHooks = {
    ground679d0:()=>calls.push('ground'),
    startStream:(_s,mask,group,slot,frame,blend,mode)=>calls.push(`start:${mask},${group},${slot},${frame},${blend},${mode}`),
    tickStream:()=>calls.push('tick'),releaseStream4cff4:()=>calls.push('release'),
    feedback061a8:(_s,code)=>calls.push(`feedback:${code}`),
    cosine45238:angle=>{angles.push(angle);return Math.cos(angle*Math.PI*2/65536);},
    groundIdle6a474:()=>calls.push('ground-idle'),airReturn6a5a4:()=>calls.push('air-return'),
  };
  return {s,h,calls,angles,tick:()=>tickDoubleNinjaXEngine(s,h)};
}
export function runDoubleNinjaXEngineSelfTest(): void {
  {
    const t=fixture();t.tick();
    assert(t.calls.join('|')==='ground|start:15,4,2,-1,-1,-1|ground|tick','phase0 probes then starts then invokes phase1 in the same dispatch');
    assert(t.s.phase===1&&t.s.timer558===15&&t.s.timer560===0&&t.s.arm7c8===2,'entry maps old arm1 to2 with independent15 and0 clocks');
    assert(t.s.offset7b0.x===f(150*f(.92)),'existing double decays only in phase1');
    const first=f(2*f(.95)),second=f(first*f(.95));
    assert(t.s.motion.x===second&&t.s.pos.x===f(f(10+first)+second),'source own-history drift runs twice at entry');
    assert(t.s.hSpeed===0&&t.s.yVel===0&&t.s.poseAccum7c===0,'no actor dash speed is invented');
  }
  for (const arm of [0,2,255]) {
    const t=fixture();t.s.arm7c8=arm;t.s.controlWord=0x43;t.tick();
    assert(t.s.arm7c8===0&&t.s.offset7b0.x===0,'only prior arm1 survives entry');
    assert(t.calls.includes('start:15,4,3,-1,-1,-1'),'airborne selects source group4 slot3');
  }
  for (const dt of [1,.5,3]) {
    const t=fixture();t.s.dt=dt;t.tick();t.s.streamEnded1cee=1;
    let updates=0;while(t.s.phase===1){t.tick();updates++;assert(updates<30,'bounded setup fixture');}
    assert(updates===Math.ceil(10/dt)&&t.calls.filter(c=>c==='feedback:5').length===1,'stream-end starts exactly one10-duration feedback wait');
    assert(t.s.arm7c8===0&&t.s.offset7b0.x===0&&t.s.timer558===15,'setup clears double without falling through to ramp');
    t.calls.length=0;
    for(let i=0;i<Math.ceil(15/dt);i++)t.tick();
    assert(t.s.timer558===0&&t.s.arm7c8===2&&t.s.magnitude55c===150,'zero crossing reaches full displacement while still arm2');
    assert(!t.calls.includes('tick')&&t.calls.filter(c=>c==='release').length===1,'ramp freezes stream until one hold release');
    assert(t.s.offset7b0.x===75&&t.s.offset7b0.y===150&&t.s.offset7b0.z===-300,'displacement uses supplied full matrix X basis');
    t.s.matrixX8d4.x=999;
    const out=t.tick();
    assert(out.type==='cleanup'&&out.exit==='ground'&&Number(t.s.arm7c8)===1,'following dispatch arms1 and exits only after stream tick');
    assert(t.s.offset7b0.x===75&&t.s.controlWord===0&&t.s.actionFlag73f===0,'cleanup returns before rewriting displacement and clears only action bits');
  }
  {
    const t=fixture();t.s.phase=2;t.s.timer558=15;t.s.dt=.75;t.tick();
    assert(t.angles[0]===Math.trunc(f(16384*f(f(15-.75)/15))),'source angle truncates rather than rounds');
    t.s.timer558=0;t.s.streamEnded1cee=0;t.tick();
    assert(t.s.arm7c8===1&&t.s.offset7b0.x===75,'armed actor retains action until stream completion');
    t.s.controlWord=0x143;t.s.streamEnded1cee=1;
    const out=t.tick();assert(out.type==='cleanup'&&out.exit==='air'&&t.s.controlWord===0x140,'air exit preserves unrelated control bits');
  }
  {
    const t=fixture();t.s.phase=0;t.h.ground679d0=s=>{s.controlWord|=0x40;};t.tick();
    assert(t.calls.includes('start:15,4,3,-1,-1,-1'),'entry rereads source control after ground hook');
    t.s.phase=1;t.s.streamEnded1cee=0;t.h.tickStream=s=>{s.streamEnded1cee=1;s.dt=2;};t.tick();
    assert(t.s.timer560===8,'phase1 rereads stream completion and dt after tick');
    t.s.phase=255;assert(t.tick().type==='unsupported','signed unsupported phase does not dispatch another action');
  }
}
