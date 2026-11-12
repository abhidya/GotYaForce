import {createSwitchingField,stepSwitchingField} from './switchingField.js';
function check(value:unknown,message:string):asserts value{if(!value)throw new Error(message);}
export function runSwitchingFieldSelfTest():void{
  const ctx={initialPosition:()=>({x:1,y:2,z:3})};
  let state=stepSwitchingField(createSwitchingField(1,1),ctx);
  check(state.timer===60&&!state.hitActive&&state.visible,'initial dispatch only places warning');
  for(let i=0;i<60;i++)state=stepSwitchingField(state,ctx);
  check(state.timer===0&&!state.hitActive,'sixty warning updates do not register early');
  const failed=stepSwitchingField(state,{...ctx,registerHit:()=>false});
  check(failed.subphase===0&&!failed.hitActive,'registration failure leaves warning retryable');
  state=stepSwitchingField(failed,ctx);
  check(state.hitActive&&state.timer===25,'next dispatch registers and preserves all25 passes');
  const prior=state;
  state=stepSwitchingField(state,{...ctx,priorContact10:true});
  check((state.flags272&1)!==0&&prior.flags272===0,'prior contact disables later registration without mutating prior sample');
  for(let i=0;i<23;i++)state=stepSwitchingField(state,ctx);
  check(state.hitActive&&state.timer===1,'registration plus24 subsequent updates retain stage');
  state=stepSwitchingField(state,ctx);
  check(!state.hitActive&&!state.visible&&state.phase==='retiring','twenty-fifth following update disables and hides');
  state=stepSwitchingField(state,ctx);check(state.phase==='released','retirement dispatch releases');
  state=stepSwitchingField(state,ctx);check(state.phase==='freed','following dispatch frees');
  for(const reason of ['owner-dead','owner-changed'] as const){
    const dead=stepSwitchingField(createSwitchingField(1,1),{...ctx,ownerInvalid:reason});
    check(dead.phase==='released'&&!dead.hitActive&&!dead.visible&&dead.reason===reason,'owner invalidation retires before init');
  }
  console.log('[switchingField] PASS: warning, retry, active and retirement boundaries');
}
