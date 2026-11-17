import {createDoubleNinjaChargeStream,releaseDoubleNinjaChargeStream,tickDoubleNinjaChargeStream,
  type DoubleNinjaChargeStream} from './doubleNinjaChargeStream.js';
import {tickDoubleNinjaXEngine,type DoubleNinjaXEngineHooks,type DoubleNinjaXEngineState} from './doubleNinjaXEngine.js';
const assert=(ok:unknown,msg:string):void=>{if(!ok)throw Error(`[doubleNinjaChargeStream] ${msg}`);};
export function runDoubleNinjaChargeStreamSelfTest():void {
  for(const slot of [2,3] as const)for(const dt of [.5,1,3]){
    const s=createDoubleNinjaChargeStream(slot,0x143);
    assert(s.parts.length===2&&s.parts.every(p=>p.frame===0&&p.blendMode===0&&p.endFrame===40),'descriptor mask3 admits only two unblended main parts');
    assert(s.hands.join(',')==='0,1'&&s.displayedHands.join(',')==='0,1','main ff/ff metadata resolves descriptor hand defaults0/1');
    assert(s.contact===0&&s.flags6e8===0&&s.flags6e9===0&&s.dashStrength===0&&s.control===0x143,'initial opcode writes preserve control ffff sentinel');
    const gates=[[] as number[],[] as number[]];let budget=400;
    while(!s.parts.every(p=>p.completed)&&--budget){
      const old=s.parts.map(p=>({...p}));
      for(const e of tickDoubleNinjaChargeStream(s,dt)){
        if(e.gate!==undefined){assert(old[e.part]!.frame>=e.gate,'gate uses old animation frame');gates[e.part]!.push(e.gate);}
        if(e.completed)assert(old[e.part]!.ended,'terminal hold uses old end flag');
        if(e.part===0&&e.gate!==undefined){
          const hand=e.gate===11?'1,1':'4,4';
          assert(s.hands.join(',')===hand&&s.displayedHands.join(',')===hand&&s.oldHands===null,
            'opcode7 updates target and display without changing uncaptured old hands');
        }
      }
    }
    assert(budget>0&&gates.every(g=>g.join(',')==='11,39'),'both main parts reach authored waits then completion hold');
    assert(s.hands.join(',')==='4,4'&&s.flags6e8===1&&s.contact===0,'main hand opcodes leave contact off');
    const held=JSON.stringify(s);tickDoubleNinjaChargeStream(s,dt);
    assert(JSON.stringify(s)===held,'main hold freezes both clocks');
    releaseDoubleNinjaChargeStream(s,dt);
    assert(s.hands.join(',')==='1,1'&&s.oldHands?.join(',')==='4,4','recovery metadata resets target and snapshots prior opcode hands');
    assert(s.displayedHands.join(',')===(dt>=2.5?'1,1':'4,4'),'release display follows source blend threshold');
    assert(s.parts.every(p=>!p.completed&&p.frame===0&&p.elapsed===0&&p.blendElapsed===dt&&p.blendTotal===5),'release immediately plays recovery without same-call advance');
    assert(s.parts[0].animation.join(',')===`3,${slot===2?10:11}`&&s.parts[0].motion.join(',')==='2,25','metadata slot resolves independent MOT');
    assert(s.parts[1].endFrame===(slot===2?15:60),'air upper recovery lasts60, lower15');
    while(!s.parts[0].completed&&--budget){
      const old=s.parts.map(p=>({...p}));
      const events=tickDoubleNinjaChargeStream(s,dt);
      const p=s.parts[0];
      const expected=p.blendMode&&Math.fround(1-Math.fround(p.blendElapsed/5))>.5?'4,4':'1,1';
      assert(s.displayedHands.join(',')===expected,'display switches from saved to new hands at blend weight half');
      for(const e of events)if(e.gate!==undefined)assert(e.gate===4&&old[e.part]!.frame>=4,'recovery wait uses frame4, not elapsed4');
    }
    assert(budget>0&&s.contact===1&&s.flags6e8===0&&s.flags6e9===0,'part0 recovery restores contact before completion');
    assert(s.parts[1].completed===(slot===2),'part0 ends while air part1 is still running');
  }
  let rejected=false;try{createDoubleNinjaChargeStream(2,0,1);}catch{rejected=true;}
  assert(rejected,'layered playback explicitly rejected');
  for(const slot of [2,3] as const)for(const dt of [.5,1,3]){
    const z=()=>({x:0,y:0,z:0});
    const s:DoubleNinjaXEngineState={phase:0,dt,pos:z(),savedOwnPos5e8:z(),motion:z(),
      arm7c8:0,offset7b0:z(),matrixX8d4:{x:1,y:0,z:0},timer560:0,timer558:0,magnitude55c:0,
      hSpeed:0,yVel:0,hDecel:0,gravityCoeff:0,poseAccum80:0,poseAccum7e:0,poseAccum7c:0,
      controlWord:slot===2?3:0x43,streamEnded1cee:0,actionFlag73f:1};
    let stream:DoubleNinjaChargeStream|undefined;let feedback=0,releases=0;
    const h:DoubleNinjaXEngineHooks={ground679d0:()=>{},
      startStream:(_s,_mask,_group,selected)=>{stream=createDoubleNinjaChargeStream(selected,s.controlWord);},
      tickStream:()=>{if(!stream)throw Error('missing stream');tickDoubleNinjaChargeStream(stream,dt);s.streamEnded1cee=Number(stream.parts[0].completed);},
      releaseStream4cff4:()=>{if(!stream)throw Error('missing stream');releaseDoubleNinjaChargeStream(stream,dt);s.streamEnded1cee=Number(stream.parts[0].completed);releases++;},
      feedback061a8:()=>{feedback++;},cosine45238:a=>Math.cos(a*Math.PI*2/65536),groundIdle6a474:()=>{},airReturn6a5a4:()=>{}};
    let budget=500;let finished=false;
    while(--budget){
      const before=stream?JSON.stringify(stream.parts):undefined;
      const ramp=s.phase===2&&s.timer558>dt;
      const out=tickDoubleNinjaXEngine(s,h);
      if(ramp)assert(JSON.stringify(stream?.parts)===before,'actor ramp freezes real completed main clocks');
      if(out.type==='cleanup'){
        assert(out.exit===(slot===2?'ground':'air'),'actor exit follows control');finished=true;break;
      }
    }
    assert(finished&&feedback===1&&releases===1,'real stream completion drives feedback, ramp and exactly one release');
    assert(stream?.recovery&&stream.parts[0].completed&&s.arm7c8===1,'arming and cleanup wait for real lower recovery');
    assert(stream?.parts[1].completed===(slot===2),'actor does not wait for longer air upper animation');
  }
  console.log('[doubleNinjaChargeStream] PASS: two-part clocks, completion holds, immediate recovery and actor integration');
}
