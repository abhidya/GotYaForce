/** Actual56900 predecessor of observed54cbc, with shared mixed-width5b8.
 * Explicit live pad rows and source cells are required, never zero-input or AI
 * substitutes. The bounded human/mode2 paths return only after real edge stores.
 */
import {isSourceActorInputPrefixRuntime,type SourceActorInputPrefixRuntime} from './actor-input-prefix.js';
import {isSourceActorWorldMatrixRuntime,type SourceActorWorldMatrixRuntime} from './actor-world-matrix.js';
import {isPendingSourceActorOrderedSamplerClaim,requireSourceActorOrderedSamplerInvocation,
  checkSourceActorOrderedSamplerInvocation,rejectSourceActorOrderedFrameReentry,type SourceActorOrderedFrameRuntime} from './actor-ordered-frame.js';
export interface SourceActorInputSamplerBinding {
  byte3e6:number;byte5c9:number;byte5cc:number;byte5cd:number;byte5ce:number;byte5cf:number;
  word5c0:number;word5c4:number;
}
export interface SourceActorInputSamplerSources {
  world:SourceActorWorldMatrixRuntime;input:SourceActorInputPrefixRuntime;
  view:object;globals:object;
  /** Canonical fixed32-byte source row identities; signed source indexes stay signed. */
  pads?:Readonly<Record<number,object>>;
}
export interface SourceActorInputSamplerRuntime {
  bindActor(id:symbol,initial:Readonly<Partial<SourceActorInputSamplerBinding>>):void;
  getActorBinding(id:symbol):Partial<SourceActorInputSamplerBinding>;
  getInputRuntime():SourceActorInputPrefixRuntime;getWorldRuntime():SourceActorWorldMatrixRuntime;
  getViewGlobals():object;getMatchGlobals():object;
}
const runtimes=new WeakSet<object>();
const claims=new WeakMap<object,{claim(stage:SourceActorOrderedFrameRuntime):void;run(stage:SourceActorOrderedFrameRuntime,id:symbol):void}>();
export function isSourceActorInputSamplerRuntime(value:unknown):value is SourceActorInputSamplerRuntime {
  return value!==null&&typeof value==='object'&&runtimes.has(value);
}
export function claimSourceActorInputSamplerForOrdered(stage:SourceActorOrderedFrameRuntime,sampler:SourceActorInputSamplerRuntime):void {
  if(!isSourceActorInputSamplerRuntime(sampler)||!isPendingSourceActorOrderedSamplerClaim(stage,sampler))fail('private genuine sampler claim required');
  claims.get(sampler)!.claim(stage);
}
export function invokeSourceActorInputSamplerFromOrdered(stage:SourceActorOrderedFrameRuntime,sampler:SourceActorInputSamplerRuntime,id:symbol):void {
  if(!isSourceActorInputSamplerRuntime(sampler))fail('genuine56900 sampler required');claims.get(sampler)!.run(stage,id);
}
function fail(why:string):never {throw Error(`[actor-input-sampler] ${why}; prior source effects are not rolled back`);}
const native=Reflect.getOwnPropertyDescriptor;
function record(value:unknown,where:string):object {if(value===null||typeof value!=='object'||ArrayBuffer.isView(value)||value instanceof Promise)fail(`${where}: synchronous source record required`);return value;}
function own(owner:unknown,key:string):unknown {const p=Object.getOwnPropertyDescriptor(record(owner,key),key);if(!p||!('value'in p))fail(`${key}: own data property required`);return p.value;}
function uint(value:unknown,max:number,key:string):number {if(typeof value!=='number'||!Number.isInteger(value)||value<0||value>max)fail(`${key}: raw unsigned source integer required`);return value===0?0:value;}
const s8=(x:number):number=>x<<24>>24;
export function createSourceActorInputSamplerRuntime(sources:SourceActorInputSamplerSources):SourceActorInputSamplerRuntime {
  const world=own(sources,'world'),input=own(sources,'input'),view=record(own(sources,'view'),'80433930'),globals=record(own(sources,'globals'),'80433934');
  if(!isSourceActorWorldMatrixRuntime(world)||!isSourceActorInputPrefixRuntime(input))fail('genuine shared world/input owners required');
  const actors=new Map<symbol,{actual:object;world:object;input:object;binding:Partial<SourceActorInputSamplerBinding>}>();
  let ordered:SourceActorOrderedFrameRuntime|undefined,active:symbol|undefined,incomplete=false;
  let pads:object|undefined;const rows=new Map<number,object>();
  const check=():void=>{if(incomplete)fail('incomplete input sampler');if(ordered&&active!==undefined)checkSourceActorOrderedSamplerInvocation(ordered,runtime,active);};
  const read=(owner:unknown,key:string):unknown=>{const value=own(owner,key);check();return value;};
  const byte=(owner:object,key:string):number=>uint(read(owner,key),255,key);
  const word=(owner:object,key:string):number=>uint(read(owner,key),0xffffffff,key);
  const entry=(id:symbol)=>{const e=actors.get(id);if(!e)fail('unknown/non-owned sampler actor');return e;};
  const owners=(id:symbol):void=>{
    const e=entry(id);if(read(sources,'world')!==world||read(sources,'input')!==input||read(sources,'view')!==view||read(sources,'globals')!==globals||
      world.getActualActor(id)!==e.actual||world.getActorBinding(id)!==e.world||input.getActualActor(id)!==e.actual||input.getActorBinding(id)!==e.input)
      fail('canonical sampler owner changed');check();
  };
  const aliases:Record<string,readonly string[]>={byte3e6:['field3e6','998'],byte5c9:['field5c9','1481'],
    byte5cc:['field5cc','1484'],byte5cd:['field5cd','1485'],byte5ce:['field5ce','1486'],byte5cf:['field5cf','1487'],
    word5c0:['statusWord5c0','field5c0','1472'],word5c4:['statusWord5c4','field5c4','1476'],
    statusWord5b4:['word5b4','field5b4','1460'],statusWord5bc:['word5bc','field5bc','1468'],
    ushort5b8:['word5b8','statusWord5b8','field5b8','inputWord5b8','priorWord5b8','half5ba','short5ba','field5ba','byte5ba','byte5bb','1464','1466','1467'],ushort5ba:['word5ba','half5ba','short5ba','field5ba','byte5ba','byte5bb','1466','1467'],
    stickX5ca:['byte5ca','field5ca','1482'],stickY5cb:['byte5cb','field5cb','1483'],byte488:['field488','1160']};
  const guard=(id:symbol,key:string,expected:object):void=>{
    owners(id);const e=entry(id),records=[sources,view,globals,e.actual,e.world,e.input,e.binding,input.getActualBorg(id),ordered!.getActorBinding(id)],extra=aliases[key]??[];
    for(const owner of records)for(const alias of owner===expected?extra:[key,...extra]) {const p=Object.getOwnPropertyDescriptor(owner,alias);check();if(p!==undefined)fail(`${alias}: competing sampler source owner`);}
    for(const owner of records)for(const alias of owner===expected?extra:[key,...extra])if(native(owner,alias)!==undefined)fail(`${alias}: competing sampler source owner`);
  };
  const put=(id:symbol,owner:object,key:string,value:number):void=>{
    guard(id,key,owner);own(owner,key);check();guard(id,key,owner);
    const p=native(owner,key);if(!p||!('value'in p)||!p.writable)fail(`${key}: live writable source cell required`);
    (owner as Record<string,unknown>)[key]=value;check();
  };
  const prior=(id:symbol,value?:number):number=>{
    const owner=entry(id).input;
    for(const key of ['ushort5b8','ushort5ba']){guard(id,key,owner);own(owner,key);check();}
    guard(id,'ushort5b8',owner);guard(id,'ushort5ba',owner);
    const hi=native(owner,'ushort5b8'),lo=native(owner,'ushort5ba');
    if(!hi||!lo||!('value'in hi)||!('value'in lo))fail('whole5b8 requires both existing canonical halves');
    if(value===undefined)return ((uint(hi.value,65535,'ushort5b8')<<16)|uint(lo.value,65535,'ushort5ba'))>>>0;
    if(!hi.writable||!lo.writable)fail('whole5b8 requires both writable halves before its atomic store');
    // One source stw: after final native checks there is no observable gap.
    (owner as Record<string,unknown>).ushort5b8=value>>>16;(owner as Record<string,unknown>).ushort5ba=value&65535;check();return value;
  };
  const body=(id:symbol):void=>{
    const e=entry(id),control=ordered!.getActorBinding(id);owners(id);
    guard(id,'byte488',control);const original=byte(control,'byte488');guard(id,'byte488',control);
    guard(id,'byte3e6',e.binding);const discriminator=byte(e.binding,'byte3e6');guard(id,'byte3e6',e.binding);
    let mode=original;const reset=original===3;if(reset){put(id,control,'byte488',0);mode=0;}
    if(s8(byte(record(read(sources,'view'),'80433930'),'byte32'))===0&&s8(byte(record(read(sources,'globals'),'80433934'),'byte1829'))!==0)mode=2;
    if(s8(byte(record(read(sources,'globals'),'80433934'),'byte45'))>=5)mode=2;
    let analog:object|undefined;
    const row=(index:number):object=>{
      const table=record(read(sources,'pads'),'803c727c');if(pads&&pads!==table)fail('canonical pad table changed');pads=table;
      const selected=record(read(table,String(index)),'fixed32-byte pad row');
      if(rows.has(index)&&rows.get(index)!==selected||[...rows].some(([other,owner])=>other!==index&&owner===selected))fail('pad row address identity changed or overlapped');
      if([sources,globals,view,e.actual,e.world,e.input,e.binding,control,table].includes(selected))fail('pad row aliases a canonical owner');
      rows.set(index,selected);return selected;
    };
    if(s8(discriminator)===0){analog=row(s8(byte(e.actual,'slot'))%4);put(id,e.binding,'byte5c9',byte(analog,'byte15'));}
    guard(id,'statusWord5b4',e.actual);const previous=word(e.actual,'statusWord5b4');guard(id,'statusWord5b4',e.actual);prior(id,previous);
    if(s8(mode)===0) {
      const digital=row(s8(byte(e.actual,'slot'))),buttons=word(digital,'word0');
      put(id,e.actual,'statusWord5b4',(buttons&0x00ff1f7f)>>>0); //actual8bbc0
      if(!analog)fail('56900 incoming actor16 analog ownership unsupported before AI');
      const targets:[[object,string],...[object,string][]]=[[e.input,'stickX5ca'],[e.input,'stickY5cb'],[e.binding,'byte5cc'],[e.binding,'byte5cd'],[e.binding,'byte5ce'],[e.binding,'byte5cf']];
      for(let i=0;i<6;i++){const raw=byte(analog,`byte${(0x16+i).toString(16)}`),[owner,key]=targets[i]!;put(id,owner,key,i<2?s8(raw):raw);}
    } else if(s8(mode)!==1) {
      for(const [owner,key]of [[e.binding,'byte5cf'],[e.binding,'byte5ce'],[e.binding,'byte5cd'],[e.binding,'byte5cc'],[e.input,'stickY5cb'],[e.input,'stickX5ca']] as const)put(id,owner,key,0);
      put(id,e.actual,'statusWord5b4',0);
    }
    if(s8(discriminator)!==0&&s8(mode)!==2)fail('56900 reached mandatory AI8001c9d0');
    put(id,e.binding,'word5c4',0);
    guard(id,'statusWord5b4',e.actual);const current=word(e.actual,'statusWord5b4'),old=prior(id);
    put(id,e.actual,'statusWord5bc',(current&~old)>>>0);
    const previousAgain=prior(id);guard(id,'statusWord5b4',e.actual);const currentAgain=word(e.actual,'statusWord5b4');
    put(id,e.binding,'word5c0',(previousAgain&~currentAgain)>>>0);
    if(reset){put(id,e.binding,'word5c0',0);put(id,e.actual,'statusWord5bc',0);}
  };
  const runtime:SourceActorInputSamplerRuntime={
    bindActor(id,initial){
      if(ordered){rejectSourceActorOrderedFrameReentry(ordered);fail('sampler exclusively ordered-owned');}
      if(actors.has(id))fail('sampler actor already bound');
      const actual=world.getActualActor(id);if(input.getActualActor(id)!==actual)fail('input sampler actual differs');
      const binding:Partial<SourceActorInputSamplerBinding>={};
      for(const key of ['byte3e6','byte5c9','byte5cc','byte5cd','byte5ce','byte5cf','word5c0','word5c4'] as const)
        if(native(initial,key)!==undefined)binding[key]=uint(own(initial,key),key.startsWith('word')?0xffffffff:255,key);
      actors.set(id,{actual,world:world.getActorBinding(id),input:input.getActorBinding(id),binding:Object.seal(binding)});
    },
    getActorBinding(id){return entry(id).binding;},getInputRuntime(){return input;},getWorldRuntime(){return world;},getViewGlobals(){return view;},getMatchGlobals(){return globals;},
  };
  runtimes.add(runtime);claims.set(runtime,{
    claim(stage){if(ordered||active!==undefined)fail('sampler already ordered-owned or active');ordered=stage;},
    run(stage,id){
      if(ordered!==stage||active!==undefined||incomplete){if(ordered)rejectSourceActorOrderedFrameReentry(ordered);fail('exclusive single active sampler owner required');}
      requireSourceActorOrderedSamplerInvocation(stage,runtime,id);active=id;
      try{body(id);check();}catch(error){incomplete=true;rejectSourceActorOrderedFrameReentry(stage);throw error;}finally{active=undefined;}
    },
  });return Object.freeze(runtime);
}
