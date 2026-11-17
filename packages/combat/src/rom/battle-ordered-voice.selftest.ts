import {requireSourceBattleOrderedVoiceRng} from './battle-outer-frame.js';
import {createBattleOrderedActorStageTestFixture} from './battle-ordered-actor-stage.selftest.js';
import {consumeActiveSourceActorOrderedVoiceRng,checkActiveSourceActorOrderedVoiceRng} from './actor-ordered-frame.js';
import type {createBattleTargetPreparationVoiceTestFixture} from './attached-setup-animation.selftest.js';
type Make=typeof createBattleTargetPreparationVoiceTestFixture;
function check(value:boolean,why:string):void {if(!value)throw Error('[battle-ordered-voice-test] '+why);}
function refuses(run:()=>unknown,part:string):void {let message='';try{run();}catch(error){message=String(error);}check(message.includes(part),`expected ${part}, got ${message||'return'}`);}
function fixture(make:Make) {
  const x=createBattleOrderedActorStageTestFixture(make);
  x.normal.bindAttributesRuntime(x.attributes);
  Object.assign(x.matchGlobals,{byte45:0,byte15dd:1,byte1828:0,byte26Slots:[0,0,0,0,0,0]});
  const attributes=x.attributes.getActorBinding(x.actor);
  attributes.parameter4ac=x.attributes.createParameterDescriptor({...x.attributes.getParameterDescriptor(attributes.parameter4ac!),byte183:0});
  return x;
}
export function runBattleOrderedVoiceSelfTests(make:Make):void {
  {
    const x=fixture(make),rng=x.massPreparation.rngState;
    check(rng.byte804360c6===195&&rng.byte804360c7===1,'inherited seed is unchanged');
    refuses(()=>consumeActiveSourceActorOrderedVoiceRng(x.commandAdmission,x.actor,0x800ea324),'800055fc');
    refuses(()=>checkActiveSourceActorOrderedVoiceRng(x.commandAdmission,x.actor,0x800ea324,rng),'800055fc');
    refuses(()=>x.frame.runFrame(),'47904 active body');
    check(rng.byte804360c6===140&&rng.byte804360c7===223,'both actual voice steps share the outer RNG');
    check(x.orderedState.field6dc===Math.fround(x.sourceActor.pos.y+x.sourceActor.stepHeight),'normal-match55568 returns before real suffix');
    check(x.orderedState.byte1ca===5,'unsupported47904 does not fabricate later clears');
    refuses(()=>x.frame.runFrame(),'incomplete');
  }
  {
    const x=fixture(make),rng=x.massPreparation.rngState;
    Object.assign(x.matchGlobals,{byte1828:1}); // Explicit entry inhibition; RNG still runs.
    refuses(()=>x.frame.runFrame(),'47904 active body');
    check(rng.byte804360c6===173&&rng.byte804360c7===159,'inhibited voice consumes first RNG but not second');
  }
  {
    const x=fixture(make),rng=x.massPreparation.rngState,native=Object.getOwnPropertyDescriptor;let armed=false;
    Object.getOwnPropertyDescriptor=((owner:object,key:PropertyKey)=>{
      if(owner===x.commandAdmission.getActorBinding(x.actor)&&key==='byte438'&&!armed){armed=true;Object.defineProperty(rng,'byte804360c6',{writable:false});}
      return native(owner,key);
    }) as typeof native;
    try{refuses(()=>x.frame.runFrame(),'writable');}finally{Object.getOwnPropertyDescriptor=native;}
    check(armed&&rng.byte804360c6===173&&rng.byte804360c7===223,'second RNG readonly-low retains its preceding high store');
    check(x.orderedState.field6dc===99,'failed voice cannot finish55568/suffix');
  }
  {
    const x=fixture(make),rng=x.massPreparation.rngState,native=Object.getOwnPropertyDescriptor;let tried=false;
    Object.getOwnPropertyDescriptor=((owner:object,key:PropertyKey)=>{
      if(owner===x.commandAdmission.getActorBinding(x.actor)&&key==='byte438'&&!tried){tried=true;refuses(()=>consumeActiveSourceActorOrderedVoiceRng(x.commandAdmission,x.actor,0x800ea324),'invocation');}
      return native(owner,key);
    }) as typeof native;
    try{refuses(()=>x.frame.runFrame(),'47904 active body');}finally{Object.getOwnPropertyDescriptor=native;}
    check(tried&&rng.byte804360c6===140&&rng.byte804360c7===223,'no absent/replayed command invocation grants an extra RNG draw');
  }
  for(const phase of ['history','suffix'] as const) {
    const x=fixture(make),native=Object.getOwnPropertyDescriptor;let tried=false;
    Object.getOwnPropertyDescriptor=((owner:object,key:PropertyKey)=>{
      if(!tried&&((phase==='history'&&owner===x.historyState&&key==='previousStepHeight6d4')||
        (phase==='suffix'&&owner===x.orderedState&&key==='field6dc'))) {
        tried=true;refuses(()=>requireSourceBattleOrderedVoiceRng(x.frame,x.ordered,x.actor,x.commandAdmission,0x800ea324),'voice RNG scope');
      }
      return native(owner,key);
    }) as typeof native;
    try{refuses(()=>x.frame.runFrame(),'incomplete');}finally{Object.getOwnPropertyDescriptor=native;}
    check(tried&&x.orderedState.field6dc===99,'direct outer RNG helper cannot grant execution in history or suffix');
  }
  console.log('[battle-ordered-voice] PASS: 6 genuine one-active bounded-substate1 normal-match compositions; unchanged shared seed, two source RNG calls, early inhibition, partial store and private invocation denial;47904 remains explicit');
}
