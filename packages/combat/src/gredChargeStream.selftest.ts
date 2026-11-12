import {createGRedChargeStream,tickGRedChargeStream} from './gredChargeStream.js';
function assert(ok:unknown,msg:string):asserts ok {if(!ok)throw Error(`[gredChargeStream] ${msg}`);}
/** Counts derived independently from 4cd24's pre-advance wait, blend+1 clocks,
 * mode2 lost completion update, and elapsed20 terminal wait. Not actor timing:
 * phase2 intentionally skips interpreter calls while its timer remains positive. */
export function runGRedChargeStreamSelfTest():void {
  for(const dt of [1,.5]){
    const s=createGRedChargeStream(dt);
    const expected=dt===1?[15,28,29,36,42,69,90]:[30,57,59,73,85,137,178];
    const seen:number[]=[];
    let n=0,pauseEntries=0,positivePausePasses=0;
    for(;n<200&&!s.completed;){
      n++;
      const before={...s};
      const e=tickGRedChargeStream(s,dt);
      if(Object.keys(e).length)seen.push(n);
      if(e.gate!==undefined){
        assert(before.frame>=e.gate,'wait compares previous frame');
        if(e.gate===9){pauseEntries++;assert(s.waitCount===12&&s.frame===before.frame+dt,'mode8 entry advances once');}
        if(e.gate===11)assert(JSON.stringify(e.equipment)==='[2,2]','source op07 equipment tuple');
        if(e.gate===12)assert(e.contact===1,'release authored by positive P0');
        if(e.gate===19)assert(e.contact===-1,'negative P0 begins conditional actor hold');
      }
      if(before.waitCount>dt){
        positivePausePasses++;
        assert(s.waitCount===before.waitCount-dt&&s.frame===before.frame&&s.elapsed===before.elapsed,'positive mode8 countdown freezes both clocks');
      }
      if(before.waitCount===dt)assert(s.waitCount===0&&s.frame===before.frame+dt,'countdown zero resumes exactly once');
      if(e.animation){
        assert(s.frame===0&&s.elapsed===0&&s.blendElapsed===dt,'play resets without same-call advance');
        if(e.animation[0]===4){
          assert(s.stage==='recoil'&&s.blendMode===2&&s.blendTotal===5&&s.endFrame===25,'recoil descriptor');
          assert(e.contact===-1&&e.dashStrength===-1&&e.faceGate===0,'recoil transition requests gravity');
        }else assert(s.stage==='recovery'&&s.blendMode===1&&s.blendTotal===21&&s.endFrame===1,'recovery descriptor');
      }
      if(before.stage==='recoil'&&before.blendMode===2){
        if(before.blendElapsed+dt<before.blendTotal)assert(s.frame===before.frame+dt,'mode2 advances while blending');
        else assert(s.frame===before.frame,'exact blend completion contributes no frame');
      }
      if(e.completed)assert(before.stage==='recovery'&&before.elapsed===20,'terminal tests elapsed before advance');
    }
    assert(JSON.stringify(seen)===JSON.stringify(expected),`independent dt${dt} full trace: ${seen}`);
    assert(pauseEntries===1&&positivePausePasses===12/dt-1,'exact pause length');
    assert(s.completed&&s.frame===0&&s.elapsed===20,'elapsed terminal can precede recovery animation end');
    const terminal=JSON.stringify(s);tickGRedChargeStream(s,dt);assert(JSON.stringify(s)===terminal,'completed state inert');
  }
  // The actor can suppress calls at negative P0. The clock has no external
  // wall-time driver; pausing therefore cannot skip authored recovery events.
  const s=createGRedChargeStream();
  for(let i=0;i<36;i++)tickGRedChargeStream(s,1);
  const held=JSON.stringify(s);
  for(let i=0;i<30;i++)assert(JSON.stringify(s)===held,'actor-suppressed clock remains unchanged');
  const e=tickGRedChargeStream(s,1);
  assert(s.frame===21&&s.elapsed===26&&Object.keys(e).length===0,'resume is one source tick, no catch-up');
  console.log('[gredChargeStream] PASS: two independent full traces, mode8 pause, blend2 ordering and conditional resume');
}
