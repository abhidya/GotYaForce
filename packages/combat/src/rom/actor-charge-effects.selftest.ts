import {createSourceActorChargeEffectsRuntime, isSourceActorChargeEffectsRuntime,
  type SourceActorChargeEffectsBinding, type SourceActorChargeEffectsData,
  type SourceActorChargeEffectsSources, type SourceActorChargeSoundRecord,
  type SourceActorChargeSoundScript, type SourceActorChargeSoundSources} from './actor-charge-effects.js';
import {createRomActor, type RomActor} from './actor.js';

function check(ok: boolean, why: string): void {if (!ok) throw Error(`[actor-charge-effects-test] ${why}`);}
function equal(actual: unknown, expected: unknown, why: string): void {
  check(Object.is(actual, expected), `${why}: got${String(actual)}, expected${String(expected)}`);
}
function rejects(run: () => unknown, fragment: string): void {
  let message = ''; try {run();} catch (error) {message = String(error);}
  check(message.includes(fragment), `expected${fragment}, got${message || 'success'}`);
}
const CUE1 = 0x8031b454, OTHER = 0x8031b400;
const ORDER = ['byte7df','pointer7ec','field7e4','byte7f7','byte7f4','byte7f5','byte7f6'] as const;
function fixture(defer = false) {
  const id = Symbol('charge effects actor'), actual = createRomActor();
  actual.carriedSlot96 = 0;
  const actors = new Map<symbol, RomActor>([[id, actual]]);
  const hook: {world?: (id: symbol) => unknown} = {};
  const data: SourceActorChargeEffectsData = {float80436a20:0,
    colorPointer802c37bc:0x802c36b0,colorPointer802c37c0:0x802c36e0};
  const selected: SourceActorChargeSoundRecord & {timestamp50: number} = {
    script58:OTHER,owner5c:null,countdown54:37,timestamp50:0x12345678,
  };
  const records: Record<number, SourceActorChargeSoundRecord> = {64:selected};
  const current: SourceActorChargeSoundScript = {firstS16:126}, desired: SourceActorChargeSoundScript = {firstS16:126};
  const scripts: Record<number, SourceActorChargeSoundScript> = {[OTHER]:current,[CUE1]:desired};
  const sound: SourceActorChargeSoundSources = {cue1Pointer8031b698:CUE1,records3ae8:records,scripts};
  const sources: SourceActorChargeEffectsSources = {world:{getActualActor(key) {
    return (hook.world ? hook.world(key) : actors.get(key)) as RomActor;
  }},data,sound};
  const initial: Partial<SourceActorChargeEffectsBinding> = {
    byte7df:11,field7e4:1.5,pointer7ec:0x12345678,byte7f4:12,byte7f5:13,byte7f6:14,byte7f7:15,
  };
  const runtime = createSourceActorChargeEffectsRuntime(sources), bind = () => runtime.bindActor(id,initial);
  if (!defer) bind();
  return {id,actual,actors,hook,data,sound,sources,selected,records,scripts,current,desired,initial,runtime,bind,
    binding: () => runtime.getActorBinding(id), color: (cue: 0x13 | 0x14 = 0x13) => runtime.initializeReadyColor(id,cue),
    keep: () => runtime.keepChargeSound(id)};
}
export function runActorChargeEffectsSelfTests(): void {
  {
    const x = fixture();
    check(isSourceActorChargeEffectsRuntime(x.runtime) && !isSourceActorChargeEffectsRuntime({...x.runtime}), 'genuine runtime brand');
    check(Object.isFrozen(x.runtime) && Object.isSealed(x.binding()) && x.binding() !== x.initial, 'frozen runtime and copied sealed missing cells');
    equal(x.runtime.getActualActor(x.id),x.actual,'actual owner retained');
    equal(x.runtime.getData(),x.data,'color source retained'); equal(x.runtime.getSound(),x.sound,'sound source retained');
    x.initial.byte7df=99; equal(x.binding().byte7df,11,'copied binding does not alias initial');
    equal(x.keep(),undefined,'same-head path returns');
    equal(x.selected.script58,OTHER,'equal heads do not replace different pointer');
    equal(x.selected.owner5c,x.actual,'actual actor pointer store');equal(x.selected.countdown54,2,'source countdown store');
    equal(x.selected.timestamp50,0x12345678,'same-head path leaves timestamp untouched');
  }
  for (const cue of [0x13,0x14] as const) {
    const x = fixture(); delete x.sound.cue1Pointer8031b698;delete x.sound.records3ae8;delete x.sound.scripts;
    delete (x.actual as Partial<RomActor>).carriedSlot96;
    if(cue===0x13) delete x.data.colorPointer802c37c0;else delete x.data.colorPointer802c37bc;
    equal(x.color(cue),undefined,'color setter genuinely returns without sound or script inputs');
    const binding=x.binding();equal(binding.byte7df,0,'61fc first byte clear');
    equal(binding.pointer7ec,cue===0x13?0x802c36b0:0x802c36e0,'621c exact row pointer');
    equal(binding.field7e4,0,'6220 positive zero');equal(binding.byte7f7,255,'6224 ff');
    for(const key of ['byte7f4','byte7f5','byte7f6'] as const) equal(binding[key],0,'remaining color clear');
  }
  // Every source destination failure retains exactly the earlier store prefix.
  for(const cue of [0x13,0x14] as const) for(const readonly of [false,true]) for(let stop=0;stop<ORDER.length;stop++) {
    const x=fixture(true), failed=ORDER[stop]!;
    if(!readonly) delete x.initial[failed];
    x.bind();const binding=x.binding();
    if(readonly) Object.defineProperty(binding,failed,{writable:false});
    const before={...binding};rejects(()=>x.color(cue),readonly?'non-writable':`${failed}: own data property`);
    const after:SourceActorChargeEffectsBinding={byte7df:0,pointer7ec:cue===0x13?0x802c36b0:0x802c36e0,
      field7e4:0,byte7f7:255,byte7f4:0,byte7f5:0,byte7f6:0};
    for(let index=0;index<ORDER.length;index++) {
      const key=ORDER[index]!;equal(binding[key],index<stop?after[key]:before[key],`ordered color prefix through${failed}/${key}`);
    }
  }
  for(const cue of [0x13,0x14] as const) {
    const pointer=cue===0x13?'colorPointer802c37bc':'colorPointer802c37c0';
    for(const key of ['float80436a20',pointer] as const) {
      const x=fixture();delete x.data[key];rejects(()=>x.color(cue),key);
      equal(x.binding().byte7df,0,'first color store before missing constant/table');
      equal(x.binding().pointer7ec,0x12345678,'missing source read before pointer store');
    }
    const x=fixture();x.data.float80436a20=NaN;delete x.data[pointer];rejects(()=>x.color(cue),'float80436a20');
    equal(x.binding().byte7df,0,'constant failure after initial store');
    const y=fixture();y.data[pointer]=0;rejects(()=>y.color(cue),'authenticated source pointer');
    equal(y.binding().pointer7ec,0x12345678,'no fabricated substitute pointer');
  }
  for(const value of [-0,1,Infinity,NaN,0.1]) {
    const x=fixture();x.data.float80436a20=value;rejects(x.color,value===1||Object.is(value,-0)?'positive-zero':'float32');
    equal(x.binding().byte7df,0,'bad constant retains first store');
  }
  {
    const x=fixture();x.sources.data={...x.data};rejects(x.color,'color data owner changed');
    equal(x.binding().byte7df,0,'color source identity check after first store');
    const y=fixture();Object.defineProperty(y.data,'float80436a20',{get(){throw Error('getter ran');}});
    rejects(y.color,'own data property');equal(y.binding().byte7df,0,'no accessor invocation');
    const z=fixture();Object.defineProperty(z.data,'float80436a20',{writable:false});z.color();
    equal(z.binding().field7e4,0,'read-only source constant accepted');
  }
  // Signed actor+96, not slot/side or an unsigned-index substitute.
  for(const byte of [0,1,2,127,128,254,255]) {
    const x=fixture();x.actual.carriedSlot96=byte;
    const offset=(byte<<24>>24)*128+64;
    delete x.records[64];x.records[offset]=x.selected;
    Object.defineProperty(x.actual,'slot',{get(){throw Error('slot getter ran');}});
    Object.defineProperty(x.actual,'side',{get(){throw Error('side getter ran');}});
    x.keep();equal(x.selected.owner5c,x.actual,`signed96 effective byte offset${offset}`);
  }
  {
    const x=fixture();const id=Symbol('second actor'), other=createRomActor();other.carriedSlot96=0;
    x.actors.set(id,other);x.runtime.bindActor(id,{});x.keep();x.runtime.keepChargeSound(id);
    equal(x.selected.owner5c,other,'second actor refreshes exact shared source record');
    equal(x.records[64],x.selected,'same effective address keeps one record identity');
    x.keep();equal(x.selected.owner5c,x.actual,'first actor refreshes same record on next call');
    equal(Object.keys(x.runtime.getActorBinding(id)).length,0,'sound never seeds color state');
    equal(x.selected.script58,OTHER,'shared refresh retains pointer');
    equal(x.selected.timestamp50,0x12345678,'shared refresh retains timestamp');
  }
  for(const head of [-32768,-1,0,126,32767]) {
    const x=fixture(true);for(const key of ORDER)delete x.initial[key];
    for(const key of Object.keys(x.data))delete x.data[key as keyof SourceActorChargeEffectsData];
    x.current.firstS16=head;x.desired.firstS16=head;x.bind();x.keep();
    equal(x.selected.countdown54,2,'live explicit signed heads compared exactly');
    equal(Object.keys(x.binding()).length,0,'sound does not hydrate missing color binding');
  }
  {
    const x=fixture();x.keep();x.current.firstS16=-12;x.desired.firstS16=-12;x.selected.countdown54=9;x.keep();
    equal(x.selected.countdown54,2,'retained descriptor scalar values stay live');
    x.current.firstS16=-13;rejects(x.keep,'800f0180');equal(x.selected.script58,OTHER,'live unequal head no replacement');
    const y=fixture();y.selected.script58=CUE1;delete y.scripts[OTHER];y.keep();equal(y.selected.countdown54,2,'same pointer uses same explicit descriptor');
  }
  {
    const x=fixture();x.current.firstS16=125;
    delete x.selected.owner5c;delete x.selected.countdown54;Object.defineProperty(x.selected,'script58',{writable:false});
    rejects(x.keep,'800f0180 reached unsupported source call 800f02d0');
    equal(x.selected.script58,OTHER,'cleanup refusal before pointer overwrite');
    equal(x.selected.timestamp50,0x12345678,'cleanup refusal before timestamp');
  }
  {
    const x=fixture();x.selected.script58=0;delete x.sound.scripts;
    delete x.selected.owner5c;delete x.selected.countdown54;
    rejects(x.keep,'800f01a4 reached unsupported source call 80207058');
    equal(x.selected.script58,CUE1,'null activation pointer store survives timestamp refusal');
    equal(x.selected.timestamp50,0x12345678,'no substitute clock value');
    check(!Object.hasOwn(x.selected,'owner5c')&&!Object.hasOwn(x.selected,'countdown54'),'no later stores after clock refusal');
    const y=fixture();y.selected.script58=0;Object.defineProperty(y.selected,'script58',{writable:false});
    rejects(y.keep,'non-writable');equal(y.selected.script58,0,'readonly null pointer fails before timestamp call');
    const z=fixture();z.selected.script58=0;delete z.sound.cue1Pointer8031b698;
    rejects(z.keep,'cue1Pointer8031b698');equal(z.selected.script58,0,'activation table load before pointer store');
  }
  {
    const x=fixture();x.selected.script58=0;rejects(x.keep,'800f01a4');
    rejects(x.keep,'known-incomplete sound activation');equal(x.selected.owner5c,null,'later call cannot fake activation completion');
    const id=Symbol('second actor'), other=createRomActor();other.carriedSlot96=0;
    x.actors.set(id,other);x.runtime.bindActor(id,{});
    rejects(()=>x.runtime.keepChargeSound(id),'known-incomplete sound activation');
    const thirdId=Symbol('other runtime actor'), third=createRomActor();third.carriedSlot96=0;
    const second=createSourceActorChargeEffectsRuntime({world:{getActualActor(){return third;}},data:{},sound:x.sound});
    second.bindActor(thirdId,{});rejects(()=>second.keepChargeSound(thirdId),'known-incomplete sound activation');
    equal(x.selected.script58,CUE1,'refusal retains stored pointer across actors/runtimes');
    equal(x.selected.countdown54,37,'refused continuation never refreshes countdown');
    const independent:SourceActorChargeSoundRecord={script58:OTHER,owner5c:null,countdown54:23};
    x.records[192]=independent;other.carriedSlot96=1;x.runtime.keepChargeSound(id);
    equal(independent.owner5c,other,'independent admitted row still refreshes');equal(independent.countdown54,2,'independent row not poisoned');
    x.selected.script58=0;rejects(x.keep,'known-incomplete sound activation');
    equal(x.selected.script58,0,'external pointer reset does not invent an activation recovery');
    const y=fixture();y.selected.script58=0;Object.defineProperty(y.selected,'script58',{writable:false});
    rejects(y.keep,'non-writable');Object.defineProperty(y.selected,'script58',{writable:true,value:OTHER});y.keep();
    equal(y.selected.owner5c,y.actual,'failed pointer store did not mark activation incomplete');
  }
  for(const missing of ['owner5c','countdown54'] as const) for(const readonly of [false,true]) {
    const x=fixture();if(readonly)Object.defineProperty(x.selected,missing,{writable:false});else delete x.selected[missing];
    rejects(x.keep,readonly?'non-writable':`${missing}: own data property`);
    equal(x.selected.owner5c,missing==='owner5c'?(readonly?null:undefined):x.actual,'owner store precedes countdown');
    equal(x.selected.countdown54,missing==='countdown54'&&!readonly?undefined:37,'failed store does not mutate countdown');
    equal(x.selected.script58,OTHER,'destination failure keeps pointer');equal(x.selected.timestamp50,0x12345678,'destination failure keeps timestamp');
  }
  // Source reads are demanded lazily and in instruction order, never preflighted.
  {
    const x=fixture();delete (x.actual as Partial<RomActor>).carriedSlot96;delete x.sound.records3ae8;
    rejects(x.keep,'carriedSlot96');
    const y=fixture();delete y.selected.script58;delete y.sound.cue1Pointer8031b698;rejects(y.keep,'script58');
    const z=fixture();delete z.current.firstS16;delete z.sound.cue1Pointer8031b698;rejects(z.keep,'firstS16');
    const q=fixture();delete q.sound.cue1Pointer8031b698;delete q.desired.firstS16;rejects(q.keep,'cue1Pointer8031b698');
    const r=fixture();delete r.desired.firstS16;delete r.selected.owner5c;rejects(r.keep,'firstS16');
    for(const item of [x,y,z,q,r])equal(item.selected.countdown54,37,'missing sound input before effects');
  }
  for(const key of ['records3ae8','scripts','cue1Pointer8031b698'] as const) {
    const x=fixture();delete x.sound[key];rejects(x.keep,key);
    equal(x.selected.owner5c,null,'missing sound owner input never fakes refresh');
  }
  for(const byte of [-1,256,0.5,NaN]) {
    const x=fixture();x.actual.carriedSlot96=byte;rejects(x.keep,'carriedSlot96: integer');
  }
  for(const pointer of [-1,2**32,0.5,NaN]) {
    const x=fixture();x.selected.script58=pointer;rejects(x.keep,'script58: integer');
  }
  for(const head of [-32769,32768,0.5,NaN]) {
    const x=fixture();x.current.firstS16=head;rejects(x.keep,'firstS16: integer');
    const y=fixture();y.desired.firstS16=head;rejects(y.keep,'firstS16: integer');
  }
  {
    const x=fixture();x.sound.cue1Pointer8031b698=OTHER;rejects(x.keep,'authenticated source pointer');
    const y=fixture();Object.defineProperty(y.current,'firstS16',{get(){throw Error('getter ran');}});rejects(y.keep,'own data property');
    const z=fixture();Object.defineProperty(z.records,'64',{get(){throw Error('getter ran');}});rejects(z.keep,'own data property');
    const q=fixture();Object.defineProperty(q.selected,'timestamp50',{get(){throw Error('clock read');}});
    q.keep();equal(q.selected.countdown54,2,'timestamp never read on same-head path');
    const r=fixture();Object.defineProperty(r.selected,'script58',{writable:false});
    Object.defineProperty(r.current,'firstS16',{writable:false});r.keep();equal(r.selected.owner5c,r.actual,'readonly source pointer/head allowed');
  }
  // Tables and records are actual source owners, not copies returned per call.
  {
    const x=fixture();x.keep();x.sound.records3ae8={...x.records};rejects(x.keep,'owner changed');
    const y=fixture();y.keep();y.records[64]={...y.selected};rejects(y.keep,'owner changed');
    const z=fixture();z.keep();z.sound.scripts={...z.scripts};rejects(z.keep,'owner changed');
    const q=fixture();q.keep();q.scripts[OTHER]={...q.current};rejects(q.keep,'owner changed');
    const r=fixture();r.keep();r.scripts[CUE1]={...r.desired};rejects(r.keep,'owner changed');
    const s=fixture();s.sources.sound={...s.sound};rejects(s.keep,'sound source owner changed');
  }
  {
    const x=fixture();x.scripts[CUE1]=x.current;rejects(x.keep,'aliases');
    const y=fixture();y.records[64]=y.actual as unknown as SourceActorChargeSoundRecord;rejects(y.keep,'aliases');
    const z=fixture();z.scripts[OTHER]=z.selected as SourceActorChargeSoundScript;rejects(z.keep,'aliases');
    const q=fixture();q.sound.scripts=q.records as unknown as Record<number,SourceActorChargeSoundScript>;rejects(q.keep,'aliases');
    const r=fixture();r.keep();r.actual.carriedSlot96=1;r.records[192]=r.selected;rejects(r.keep,'aliases');
    const s=fixture();s.records[64]=s.binding() as SourceActorChargeSoundRecord;rejects(s.keep,'aliases');
    const t=fixture();t.records[64]=t.data as SourceActorChargeSoundRecord;rejects(t.keep,'aliases');
    const u=fixture();u.sound.records3ae8=u.sound as unknown as Record<number,SourceActorChargeSoundRecord>;rejects(u.keep,'aliases');
  }
  {
    const x=fixture(true);x.sources.sound=x.data as SourceActorChargeSoundSources;rejects(()=>createSourceActorChargeEffectsRuntime(x.sources),'aliases');
    const y=fixture();const second=createSourceActorChargeEffectsRuntime(y.sources);rejects(()=>second.bindActor(y.id,{}),'already claimed');
    rejects(()=>y.runtime.bindActor(y.id,{}),'new symbol');
    const z=fixture();z.hook.world=()=>({...z.actual});rejects(z.keep,'owner changed');
    const q=fixture();q.hook.world=()=>Promise.resolve(q.actual);rejects(q.color,'synchronous');
    const r=fixture();r.sources.world={getActualActor(){return r.actual;}};rejects(r.keep,'world owner changed');
  }
  for(const key of [...ORDER,'byte96','signedByte96']) {
    const x=fixture(true);Object.defineProperty(x.actual,key,{value:undefined});rejects(x.bind,'competing source owner');
    const y=fixture();Object.defineProperty(y.actual,key,{value:undefined});rejects(y.keep,'competing source owner');
  }
  for(const operation of ['color','keep','bind'] as const) {
    const x=fixture();x.hook.world=()=>{
      try {if(operation==='bind')x.runtime.bindActor(Symbol('nested'),{});else x[operation]();}catch{}
      return x.actual;
    };
    rejects(x.keep,'caught same-runtime reentry');equal(x.selected.owner5c,null,'caught reentry prevents source writes');
    delete x.hook.world;x.keep();equal(x.selected.owner5c,x.actual,'next independent call recovers after poisoned operation');
  }
  {
    const x=fixture(true);x.initial.field7e4=0.1;rejects(x.bind,'float32');
    const y=fixture(true);Object.defineProperty(y.initial,'byte7df',{get(){throw Error('getter ran');}});rejects(y.bind,'own data property');
    const z=fixture(true);z.initial.pointer7ec=2**32;rejects(z.bind,'pointer7ec: integer');
    const q=fixture(true);q.initial.byte7f7=-1;rejects(q.bind,'byte7f7: integer');
  }
  {
    const x=fixture(true);for(const key of ORDER)delete x.initial[key];delete x.records[64];x.bind();
    rejects(x.keep,'64: own data property');equal(Object.keys(x.records).length,0,'no auto-seeded scheduler state');
    equal(Object.keys(x.binding()).length,0,'no auto-seeded color state');
    x.records[64]=x.selected;x.keep();equal(x.selected.countdown54,2,'explicit subsequently supplied record admitted');
    rejects(()=>x.runtime.initializeReadyColor(x.id,0x12 as 0x13),'only explicit ready-color');
    rejects(()=>x.runtime.keepChargeSound(Symbol('unknown')),'unknown/non-owned');
  }
}
