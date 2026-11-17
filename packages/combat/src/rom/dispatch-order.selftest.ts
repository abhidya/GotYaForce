import {createRomActor, type RomActor} from './actor.js';
import {dispatchFullBodyCue, stepActor} from './dispatch.js';
import {createRomStateTables, stepRomActor} from './state-tables.js';
import type {StreamContext} from './stream-vm.js';

const ctx:StreamContext = {onArmHit:()=>{},onPlayAnim:()=>{},onFireChild:()=>{}};
function assert(ok:boolean,message:string):void {
  if(!ok)throw Error(`[actor dispatch order] ${message}`);
}
function withoutContext(tables:ReturnType<typeof createRomStateTables>){
  const bind=(handler:(a:RomActor,c:StreamContext)=>void)=>(a:RomActor)=>handler(a,ctx);
  return {upperBody:tables.upperBody.map(bind),fullBody:tables.fullBody.map(bind)};
}
/** 80055568, chunk_0006.c:7793–7800: pre -> save5da -> UB -> savedFB -> post. */
export function runActorDispatchOrderSelfTest():void {
  for(const mode of ['foundation','runtime'] as const){
    const tables=createRomStateTables();
    const a=createRomActor();
    const step=()=>mode==='foundation'?stepActor(a,withoutContext(tables)):stepRomActor(a,tables,ctx);
    const events:string[]=[];
    a.fbState=1;a.ubState=1;
    let first=true;
    a.preState=()=>{events.push('pre');if(first){a.fbState=2;first=false;}};
    tables.upperBody[1]=()=>{events.push('upper');a.fbState=3;a.actionIndex=7;};
    tables.fullBody[1]=()=>{throw Error('snapshot incorrectly taken before preState');};
    tables.fullBody[2]=()=>{
      events.push('full2');
      assert(a.fbState===3&&a.actionIndex===7,`${mode}: saved selection does not restore actor fields`);
    };
    tables.fullBody[3]=()=>{events.push('full3');};
    a.postState=()=>{events.push('post');};
    step();step();
    assert(events.join(',')==='pre,upper,full2,post,pre,upper,full3,post',
      `${mode}: pre-state choice runs now; upper-body choice runs next dispatch`);

    // Real cue transition, populated runtime table and state61 family trampoline.
    // The UB selects idle, but this dispatch must still run the saved state61.
    const actual=createRomStateTables();
    const b=createRomActor();
    b.fbState=61;b.ubState=1;b.cueTable=new Int8Array(4).fill(-1);b.cueTable[2]=0;
    const calls:string[]=[];
    b.rootAction=()=>{throw Error('must read the live family callback, not snapshot it');};
    actual.upperBody[1]=()=>{
      dispatchFullBodyCue(b,1);
      b.rootAction=()=>{calls.push('family');assert(b.fbState===0,`${mode}: cue write stays live`);};
    };
    b.postState=()=>{calls.push('post');};
    const run=()=>mode==='foundation'?stepActor(b,withoutContext(actual)):stepRomActor(b,actual,ctx);
    run();run();
    assert(calls.join(',')==='family,post,post',`${mode}: actual state61 then idle on next dispatch`);
  }
}
