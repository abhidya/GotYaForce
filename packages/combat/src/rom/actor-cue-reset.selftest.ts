import {createSourceActorCueResetRuntime, isSourceActorCueResetRuntime,
  type SourceActorCueResetBinding} from './actor-cue-reset.js';
import {createRomActor} from './actor.js';
import type {SourceActorJointMappingHeader} from './actor-joint-mapping.js';
function check(ok: boolean, why: string): void {if (!ok) throw Error(`[actor-cue-reset-test] ${why}`);}
function equal(a: unknown, b: unknown, why: string): void {check(Object.is(a,b), `${why}: ${String(a)} != ${String(b)}`);}
function rejects(run: () => unknown, text: string): void {
  let caught=''; try {run();} catch(e) {caught=String(e);} check(caught.includes(text),`expected ${text}, got ${caught || 'success'}`);
}
function fixture(defer=false) {
  const id=Symbol('cue actor'), actual=Object.assign(createRomActor(),{onLand754:(() => {throw Error('callback must not execute');}) as (() => void) | null});
  // Explicit synthetic exclusive source construction, not runtime migration.
  delete (actual as Partial<typeof actual>).fbPhaseSlots; delete (actual as Partial<typeof actual>).shotByte1db3;
  actual.cueTable=new Int8Array(1024); actual.cueTable.fill(-1); actual.cueTable[18]=-8; actual.cueTable[19]=-7;
  actual.ubCue=201; actual.fbCue=202; actual.ubState=-12; actual.fbState=-13;
  actual.prevUbState=-21; actual.prevFbState=-22; actual.fbPhase=23;
  actual.shotByte1db2=77;
  const header={} as SourceActorJointMappingHeader;
  const gates={family1d88:Symbol('family'),shared1d8c:Symbol('shared'),marker578:1,marker1db3:1};
  const hooks:{actual?:()=>unknown;worldMapping?:()=>unknown;dispatchMapping?:()=>unknown;gates?:()=>unknown}={};
  const world={getActualActor(key:symbol){check(this===world&&key===id,'world actor receiver');return (hooks.actual?hooks.actual():actual) as typeof actual;},
    getMappingActor(key:symbol){check(this===world&&key===id,'world mapping receiver');return (hooks.worldMapping?hooks.worldMapping():header) as object;}};
  const dispatch={getSourceActor(key:symbol){check(this===dispatch&&key===id,'dispatch mapping receiver');return (hooks.dispatchMapping?hooks.dispatchMapping():header) as SourceActorJointMappingHeader;},
    getActorBinding(key:symbol){check(this===dispatch&&key===id,'dispatch gates receiver');return (hooks.gates?hooks.gates():gates) as typeof gates;}};
  const sources={world,dispatch},runtime=createSourceActorCueResetRuntime(sources);
  const initial:Partial<SourceActorCueResetBinding>={byte541:11,byte542:12,byte543:13,byte544:14,byte545:15,byte546:16,byte547:17,byte588:18,byte7ce:19,byte7cf:20};
  const bind=()=>runtime.bindActor(id,initial); if(!defer)bind();
  return {id,actual,header,gates,hooks,sources,runtime,initial,bind,binding:()=>runtime.getActorBinding(id),
    upper:(cue=9)=>runtime.dispatchUpperBodyCue(id,cue),full:(cue=9)=>runtime.dispatchFullBodyCue(id,cue)};
}
export function runActorCueResetSelfTests():void {
  {
    const x=fixture(); equal(x.runtime.getActualActor(x.id),x.actual,'actual actor'); equal(x.runtime.getDispatchBinding(x.id),x.gates,'source marker owner');
    check(isSourceActorCueResetRuntime(x.runtime)&&!isSourceActorCueResetRuntime({...x.runtime}),'genuine brand');
    equal(x.upper(),1,'upper success'); equal(x.binding().byte7ce,201,'stash old upper cue'); equal(x.actual.ubCue,9,'new upper cue');
    equal(x.actual.prevUbState,-12,'old signed upper state');equal(x.actual.ubState,-7,'selected signed upper state');
    for(const k of ['byte547','byte546','byte545','byte544','byte588'] as const)equal(x.binding()[k],0,'upper clear');
    equal(x.actual.onLand754,null,'source zero callback pointer');equal(x.gates.marker1db3,0,'same marker byte');
    equal(x.actual.shotByte1db2,77,'source upper reset does not clear adjacent1db2');
    equal(x.actual.fbState,-13,'upper leaves full state'); equal(x.actual.fbPhase,23,'upper leaves full phase');equal(x.binding().byte543,13,'upper leaves full subphase');
    equal(x.full(),1,'full success');equal(x.binding().byte7cf,202,'stash full cue');equal(x.actual.fbCue,9,'full cue');
    equal(x.actual.prevFbState,-13,'old full state');equal(x.actual.fbState,-8,'selected full state');
    for(const k of ['byte543','byte542','byte541'] as const)equal(x.binding()[k],0,'full clear');equal(x.actual.fbPhase,0,'full final clear');
    x.actual.cueTable![19]=7;equal(x.upper(),1,'repeated explicit cue reload');equal(x.binding().byte7ce,9,'second stash uses last cue');equal(x.actual.prevUbState,-7,'second state previous');
    equal(x.initial.byte547,17,'binding input is not mirrored');
  }
  {
    const x=fixture(true); for(const key of Object.keys(x.initial))delete (x.initial as Record<string,unknown>)[key];x.bind();
    x.actual.cueTable!.fill(-1);x.actual.ubCue=NaN;x.actual.fbState=NaN;Object.freeze(x.gates);
    equal(x.upper(),0,'upper sentinel no late loads');equal(x.full(),0,'full sentinel no late loads');equal(Object.keys(x.binding()).length,0,'no missing destinations manufactured');
    const y=fixture(); const before=JSON.stringify([y.actual,y.binding(),y.gates]);y.actual.cueTable![19]=-1;
    const sentinelBefore=JSON.stringify([y.actual,y.binding(),y.gates]);equal(y.upper(),0,'sentinel');equal(JSON.stringify([y.actual,y.binding(),y.gates]),sentinelBefore,'sentinel has zero mutations');check(before!==sentinelBefore,'nonvacuous table edit');
    // All256 source bytes, independent signed interpretation; onlyff skips.
    for(let raw=0;raw<256;raw++)for(const upper of [false,true]) {
      const a=fixture();a.actual.cueTable![upper?19:18]=raw;
      const result=upper?a.upper():a.full();equal(result,raw===255?0:1,'all-byte sentinel');
      equal(upper?a.actual.ubState:a.actual.fbState,raw===255?(upper?-12:-13):(raw<128?raw:raw-256),'all-byte state bits');
    }
  }
  {
    const x=fixture();x.actual.cueTable![512]=31;x.actual.cueTable![513]=32;x.actual.cueTable![0]=41;x.actual.cueTable![1]=42;
    equal(x.full(256),1,'full index not early truncated');equal(x.actual.fbState,31,'selected512');equal(x.actual.fbCue,0,'stored low8 bits');
    equal(x.upper(256),1,'upper index not early truncated');equal(x.actual.ubState,32,'selected513');equal(x.actual.ubCue,0,'upper low8');
    equal(x.upper(0x80000009),1,'high-bit slwi wrap');equal(x.actual.ubState,-7,'wrap addresses19');equal(x.actual.ubCue,9,'wrap cue low8');
    equal(x.full(0x80000009),1,'full high-bit slwi wrap');equal(x.actual.fbState,-8,'wrap addresses18');
    rejects(()=>x.full(0xffffffff),'outside explicitly owned');
    for(const bad of [-1,0x100000000,NaN,Infinity,1.5])rejects(()=>x.upper(bad),'cue register bits');
    const old=x.actual.cueTable;x.actual.cueTable=new Int8Array(20);x.actual.cueTable[19]=66;equal(x.upper(),1,'fresh source pointer each call');equal(x.actual.ubState,66,'replacement table not cached');check(old!==x.actual.cueTable,'distinct table');
    for(const bad of [null,new Uint8Array(20),new Int8Array(new SharedArrayBuffer(20))]) {
      const y=fixture();y.actual.cueTable=bad as Int8Array|null;rejects(y.upper,'actual non-shared Int8Array');equal(y.binding().byte7ce,19,'invalid table no stores');
    }
    const z=fixture();z.actual.cueTable=new Int8Array(19);rejects(z.upper,'outside explicitly owned');equal(z.binding().byte7ce,19,'missing entry does not mean sentinel');
  }
  {
    // The operation lists independently pin each source destination and value.
    const operations=(x:ReturnType<typeof fixture>,upper:boolean):[object,string,unknown][]=>upper?
      [[x.binding(),'byte7ce',201],[x.actual,'ubCue',9],[x.actual,'prevUbState',-12],[x.actual,'ubState',-7],
       [x.binding(),'byte547',0],[x.binding(),'byte546',0],[x.binding(),'byte545',0],[x.binding(),'byte544',0],
       [x.binding(),'byte588',0],[x.actual,'onLand754',null],[x.gates,'marker1db3',0]]:
      [[x.binding(),'byte7cf',202],[x.actual,'fbCue',9],[x.actual,'prevFbState',-13],[x.actual,'fbState',-8],
       [x.binding(),'byte543',0],[x.binding(),'byte542',0],[x.binding(),'byte541',0],[x.actual,'fbPhase',0]];
    for(const upper of [false,true])for(let stop=0;stop<(upper?11:8);stop++) {
      const x=fixture(),ops=operations(x,upper),original=ops.map(([r,k])=>(r as Record<string,unknown>)[k]);
      const [target,key]=ops[stop]!;Object.defineProperty(target,key,{writable:false});
      rejects(upper?x.upper:x.full,`${key}: non-writable`);
      ops.forEach(([r,k,v],index)=>equal((r as Record<string,unknown>)[k],index<stop?v:original[index],`retained${upper?'upper':'full'} prefix${stop}:${k}`));
    }
    const x=fixture();x.actual.ubState=NaN;rejects(x.upper,'ubState: integer');equal(x.binding().byte7ce,201,'state load follows stash');equal(x.actual.ubCue,9,'state load follows cue store');equal(x.actual.prevUbState,-21,'failed old-state read precedes previous store');
    const y=fixture();y.actual.fbCue=256;rejects(y.full,'fbCue: integer');equal(y.binding().byte7cf,20,'invalid first source no stores');
    const z=fixture(true);delete z.initial.byte545;z.bind();rejects(z.upper,'byte545: own data');equal(z.binding().byte547,0,'missing phase preserves547');equal(z.binding().byte546,0,'missing phase preserves546');equal(z.binding().byte544,14,'missing phase stops544');
    const w=fixture();delete (w.actual as Partial<typeof w.actual>).onLand754;rejects(w.upper,'onLand754: own data');equal(w.binding().byte588,0,'missing callback keeps bytes');equal(w.gates.marker1db3,1,'missing callback blocks marker');
  }
  {
    for(const key of ['fbPhaseSlots','shotByte1db3','animState']) {
      const x=fixture(true);Object.defineProperty(x.actual,key,{value:undefined});rejects(x.bind,'competing legacy');
      const y=fixture();Object.defineProperty(y.actual,key,{value:undefined});rejects(y.upper,'competing legacy');
    }
    for(const hook of ['actual','worldMapping','dispatchMapping','gates'] as const) {
      const x=fixture();x.hooks[hook]=()=>({});rejects(x.full,'owner changed');equal(x.binding().byte7cf,20,'owner mismatch no stores');
    }
    const x=fixture();const second=createSourceActorCueResetRuntime(x.sources);rejects(()=>second.bindActor(x.id,x.initial),'already claimed');
    const y=fixture();let nested=false;y.hooks.actual=()=>{if(!nested){nested=true;try{y.upper();}catch{/* caught reentry */}}return y.actual;};
    rejects(y.full,'caught same-runtime');equal(y.binding().byte7cf,20,'reentry poisons before writes');delete y.hooks.actual;equal(y.full(),1,'later independent call allowed');
    const z=fixture();let invoked=false;Object.defineProperty(z.actual,'fbCue',{get(){invoked=true;return 202;}});rejects(z.full,'fbCue: own data');check(!invoked,'no source accessor execution');
    const w=fixture(true);w.hooks.dispatchMapping=()=>({});rejects(w.bind,'dispatch mapping: owner changed');
  }
  console.log('[actor-cue-reset-test] actual cue/table owners,512 signed-byte cases,32-bit indexing and19 retained-store refusal prefixes passed');
}
