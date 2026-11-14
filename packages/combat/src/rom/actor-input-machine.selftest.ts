import {createSourceActorInputMachineRuntime, isSourceActorInputMachineRuntime,
  type SourceActorInputMachineBinding, type SourceActorInputMachineTables} from './actor-input-machine.js';
import {createRomActor} from './actor.js';
import {loadSourceInputSignedByte} from './source-input-quantized.js';
import {createSourceActorInputPrefixRuntime} from './actor-input-prefix.js';
function check(ok: boolean, why: string): void {if (!ok) throw Error(`[actor-input-machine-test] ${why}`);}
function equal(a: unknown, b: unknown, why: string): void {check(Object.is(a, b), `${why}: got${String(a)}, expected${String(b)}`);}
function rejects(run: () => unknown, fragment: string): void {
  let error = ''; try {run();} catch (e) {error = String(e);}
  check(error.includes(fragment), `expected${fragment}, got${error || 'success'}`);
}
function fixture(defer = false, withSecond = false, withThird = false, withFourth = false, withFifth = false, withSixth = false, withSeventh = false, withEighth = false, withNinth = false, withTenth = false) {
  const id = Symbol('first input machine'), actual = Object.assign(createRomActor(), {statusWord5bc: 0});
  actual.inputEdge5d4 = 0x80000001; actual.controlWord = 0;
  const dispatch = [0x80068c14, 0x80068c84, 0x80068d04], descriptor = [1, 0, 0, 1, 0x200, 0];
  const second = [1, 0, 0, 1, 0x200, 0], third = [1, 0, 0, 1, 0x400, 0], fourth = [1, 0, 0, 1, 0x800, 0], fifth = [1, 0, 0, 16, 0x100, 0], sixth = [1, 4, 0, 1, 0x100, 0], seventh = [1, 0, 0, 1, 0x20, 0], eighth = [1, 0, 0, 1, 0x40, 0], ninth = [1, 0, 0, 1, 0x10, 0], tenth = [1, 0x10, 0, 1, 0xf, 0];
  const tables: SourceActorInputMachineTables = {dispatch3988: dispatch, descriptor38f8: descriptor,
    ...(withSecond ? {descriptor3904: second} : {}), ...(withThird ? {descriptor3910: third} : {}), ...(withFourth ? {descriptor391c: fourth} : {}), ...(withFifth ? {descriptor3928: fifth} : {}), ...(withSixth ? {descriptor3934: sixth} : {}), ...(withSeventh ? {descriptor3940: seventh} : {}), ...(withEighth ? {descriptor394c: eighth} : {}), ...(withNinth ? {descriptor3958: ninth} : {}), ...(withTenth ? {descriptor3964: tenth} : {})};
  const hooks: {actual?: () => unknown} = {};
  const world = {getActualActor(key: symbol) {check(this === world && key === id, 'world receiver/id');
    return (hooks.actual ? hooks.actual() : actual) as typeof actual;}};
  const runtime = createSourceActorInputMachineRuntime({world, tables});
  const initial: Partial<SourceActorInputMachineBinding> = {byte614: 0, byte615: 9, byte616: 7, byte617: 0,
    ...(withSecond ? {byte618: 0, byte619: 19, byte61a: 17, byte61b: 0} : {}),
    ...(withThird ? {byte61c: 0, byte61d: 29, byte61e: 27, byte61f: 0} : {}),
    ...(withFourth ? {byte624: 0, byte625: 39, byte626: 37, byte627: 0} : {}),
    ...(withFifth ? {byte600: 0, byte601: 49, byte602: 47, byte603: 0} : {}),
    ...(withSixth ? {byte604: 0, byte605: 59, byte606: 57, byte607: 0} : {}),
    ...(withSeventh ? {byte608: 0, byte609: 69, byte60a: 67, byte60b: 0} : {}),
    ...(withEighth ? {byte60c: 0, byte60d: 79, byte60e: 77, byte60f: 0} : {}),
    ...(withNinth ? {byte610: 0, byte611: 89, byte612: 87, byte613: 0} : {}),
    ...(withTenth ? {byte628: 0, byte629: 99, byte62a: 97, byte62b: 0} : {})};
  const bind = () => runtime.bindActor(id, initial); if (!defer) bind();
  return {id, actual, dispatch, descriptor, second, third, fourth, fifth, sixth, seventh, eighth, ninth, tenth, tables, hooks, world, runtime, initial, bind,
    binding: () => runtime.getActorBinding(id), run: () => runtime.updateFirstMachine(id)};
}
export function runActorInputMachineSelfTests(): void {
  {
    const x = fixture(); check(isSourceActorInputMachineRuntime(x.runtime) && !isSourceActorInputMachineRuntime({...x.runtime}), 'genuine brand');
    check(x.runtime.getActualActor(x.id) === x.actual && x.runtime.getTables() === x.tables &&
      x.binding() !== x.initial && Object.isSealed(x.binding()), 'same owners and sealed explicit state');
    equal(x.run(), 0, 'first source descriptor nohit'); equal(x.binding().byte614, 2, 'phase0 selects phase2');
    equal(x.binding().byte615, 126, 'phase0 seeds127 then real phase2 decrements'); equal(x.binding().byte616, 0, 'phase0 resets index');
    equal(x.actual.inputEdge5d4, 0x80000001, 'zero tail leaves edge alone');
    x.actual.statusWord5bc = 0x200; equal(x.run(), 1, 'subsequent real phase2 hit');
    equal(x.binding().byte614, 0, 'success clears phase'); equal(x.binding().byte615, 125, 'same timer retained');
    equal(x.binding().byte617, 0, 'new tail1 consumed by wrapper'); equal(x.actual.inputEdge5d4, 0x80000021, 'mask20 preserves high bit');
    equal(x.run(), 1, 'held raw edge reused only on explicit next call'); equal(x.binding().byte615, 126, 'newphase0 resets and decrements again');
  }
  for (const phase of [1, 2]) for (let old = 0; old < 256; old++) {
    const x = fixture(); const b = x.binding(); b.byte614 = phase; b.byte615 = old; b.byte616 = 0;
    x.actual.statusWord5bc = 0; equal(x.run(), 0, 'zero tail return');
    const next = (old - 1) & 255; equal(b.byte615, next, 'all raw timer decrements');
    equal(b.byte614, next >= 1 && next <= 127 ? phase : 0, 'signed post-decrement expiry');
    equal(x.actual.inputEdge5d4, 0x80000001, 'expired/nohit phase never manufactures edge');
  }
  for (let tail = 0; tail < 256; tail++) {
    const x = fixture(); const b = x.binding(); b.byte614 = 2; b.byte615 = 1; b.byte617 = tail;
    equal(x.run(), tail === 0 ? 0 : 1, 'wrapper ignores expired handler return');
    equal(b.byte614, 0, 'expired phase reset'); equal(b.byte617, tail === 0 ? 0 : tail - 1, 'unsigned wrapper tail decrement');
    equal(x.actual.inputEdge5d4, tail === 0 ? 0x80000001 : 0x80000021, 'tail selects edge OR');
  }
  for (const flags of [0,1,2,4,8,16,3,5,6,7,9,10,12,17,18,20,24,31,0xffff]) {
    for (const control of [0,0x40]) for (const held of [0,0x200,0x10200]) for (const edge of [0,0x200,0x600]) {
      const x = fixture(); const b = x.binding(); b.byte614 = 2; b.byte615 = 10; b.byte616 = 0;
      x.descriptor[1] = flags; x.descriptor[4] = 0x600; x.actual.controlWord = control;
      x.actual.statusWord5b4 = held; x.actual.statusWord5bc = edge;
      const gated = ((flags & 2) !== 0 && control !== 0) || ((flags & 4) !== 0 && control === 0) ||
        ((flags & 8) !== 0 && (held & 0xf0000) === 0);
      const selected = flags & 1 ? held : edge;
      const match = !gated && (flags & 16 ? (selected & 0x600) !== 0 : (selected & 0x600) === 0x600);
      equal(x.run(), match ? 1 : 0, 'phase2 flags and any/all semantics'); equal(b.byte615, 9, 'all gates follow timer write');
    }
  }
  {
    const x = fixture(); x.binding().byte614 = 2; x.binding().byte616 = 1;
    equal(x.run(), 1, 'phase2 zero mask matches all-bit comparison');
    const y = fixture(); y.binding().byte614 = 1; y.binding().byte616 = 1; y.actual.statusWord5bc = 0xffffffff;
    equal(y.run(), 0, 'phase1 zero mask never matches any-bit comparison'); equal(y.binding().byte614, 1, 'phase1 unchanged');
  }
  {
    const x = fixture(); const b = x.binding(); x.descriptor[0] = 2; x.descriptor[2] = 0x1ff; x.actual.statusWord5bc = 0x200;
    equal(x.run(), 0, 'phase0 multi-step has no seeded tail'); equal(b.byte614, 1, 'multi-step selects phase1');
    equal(b.byte616, 1, 'multi-step index1'); equal(b.byte615, 255, 'phase0 truncates descriptor timer');
    b.byte615 = 10; b.byte616 = 0; equal(x.run(), 0, 'phase1 remains wrapper0');
    equal(b.byte615, 255, 'phase1 timer reload lowbyte'); equal(b.byte616, 1, 'phase1 index increments'); equal(b.byte614, 2, 'mode-1 equality selects phase2');
  }
  {
    const x = fixture(); x.dispatch[0] = 0x80068d04; const b = x.binding(); b.byte616 = 0; b.byte615 = 1;
    equal(x.run(), 0, 'actual table target selected rather than hardcoded state switch'); equal(b.byte616, 0, 'phase0 not spuriously run');
  }
  for (const phase of [1, 2]) {
    const x = fixture(); x.binding().byte614 = phase; x.binding().byte616 = 2; x.actual.statusWord5bc = 0x200;
    x.descriptor.push(0x200); rejects(x.run, 'outside explicit12-byte'); equal(x.binding().byte615, 8, 'index refusal retains timer');
  }
  {
    const x = fixture(); x.dispatch.push(0x80068c14); x.binding().byte614 = 3;
    rejects(x.run, 'outside explicit three-entry'); equal(x.binding().byte615, 9, 'table bounds before handler');
    const y = fixture(); y.dispatch[0] = 0x80000000; rejects(y.run, '80068bc8'); equal(y.binding().byte616, 7, 'unknown code target before stores');
  }
  {
    const x = fixture(true); x.initial.byte614 = 2; x.initial.byte615 = 1; delete x.initial.byte616;
    delete (x.actual as Partial<typeof x.actual>).statusWord5bc; x.descriptor.length = 0; x.bind();
    equal(x.run(), 0, 'expired phase needs no descriptor or input word');
  }
  for (const missing of ['byte615','byte616','byte617'] as const) {
    const x = fixture(true); delete x.initial[missing]; x.bind(); rejects(x.run, missing);
    if (missing === 'byte615') {equal(x.binding().byte614, 2, 'phase select before missing timer'); equal(x.binding().byte616, 0, 'index clear retained');}
    if (missing === 'byte617') equal(x.binding().byte615, 126, 'full nohit handler before missing wrapper tail');
  }
  {
    const x = fixture(); x.actual.statusWord5bc = 0x200; Object.defineProperty(x.binding(), 'byte617', {writable: false});
    rejects(x.run, 'non-writable'); equal(x.binding().byte614, 0, 'success state clear before tail seed');
    equal(x.binding().byte615, 126, 'fulltimer prefix retained'); equal(x.actual.inputEdge5d4, 0x80000001, 'no wrapper after handler refusal');
    const y = fixture(); y.actual.statusWord5bc = 0x200; Object.defineProperty(y.actual, 'inputEdge5d4', {writable: false});
    rejects(y.run, 'non-writable'); equal(y.binding().byte617, 0, 'wrapper decremented before readonly edge');
    equal(y.binding().byte614, 0, 'handler state retained');
  }
  {
    const x = fixture(); x.actual.statusWord5bc = 0x200; delete x.descriptor[3];
    rejects(x.run, 'own data property'); equal(x.binding().byte614, 0, 'success clears state before descriptor duration read');
    const y = fixture(); y.descriptor[0] = 2; y.actual.statusWord5bc = 0x200; delete y.descriptor[2];
    rejects(y.run, 'own data property'); equal(y.binding().byte614, 1, 'phase0 select before missing timer halfword'); equal(y.binding().byte616, 1, 'phase0 index write retained');
  }
  for (const key of ['byte614','byte615','byte616','byte617','inputFlags5d4','inputEdges5bc','flags5e0']) {
    const x = fixture(true); Object.defineProperty(x.actual, key, {value: undefined}); rejects(x.bind, 'competing');
    const y = fixture(); Object.defineProperty(y.actual, key, {value: undefined}); rejects(y.run, 'competing');
  }
  {
    const x = fixture(); x.hooks.actual = () => ({}); rejects(x.run, 'owner changed');
    const y = fixture(); y.tables.descriptor38f8 = [...y.descriptor]; rejects(y.run, 'owner changed');
    const z = fixture(); z.hooks.actual = () => {try {z.run();} catch {} return z.actual;}; rejects(z.run, 'caught same-runtime');
    const duplicate = createSourceActorInputMachineRuntime({world: y.world, tables: y.tables});
    rejects(() => duplicate.bindActor(y.id, {}), 'already claimed');
  }
  {
    const x = fixture(); const y = createRomActor(), other = Symbol('shared tables actor');
    const world = {getActualActor: () => y};
    const runtime = createSourceActorInputMachineRuntime({world, tables: x.tables});
    runtime.bindActor(other, {byte614: 2, byte615: 1, byte617: 0});
    equal(runtime.updateFirstMachine(other), 0, 'shared tables serve distinct actual actors');
  }
  for (let value = -128; value < 128; value++) for (const profile of [0x00060006,0x00060000,0xc0feffff]) {
    const result = loadSourceInputSignedByte(value, profile); equal(result[0], value, 'signed8 exact f32'); equal(result[1], 1, 'W1 lane');
  }
  equal(loadSourceInputSignedByte(-0, 0x60006)[0], 0, 'byte zero canonical positive zero');
  for (const profile of [0,0x70007,0x1060006,0x3f060006,-1,0x100000000,NaN]) rejects(() => loadSourceInputSignedByte(1,profile), 'GQR4');
  for (const value of [-129,128,0.5,NaN,Infinity]) rejects(() => loadSourceInputSignedByte(value,0x60006), 'signed-byte');
  {
    const x = fixture(), borg = {downGaugeBase: 100, downGauge: 0,paramTier:{tier:16,deltaAccum:0,timerFrames:0},sourceArrowMash749:8};
    const gauges = {getActualActor: () => x.actual, getActualBorg: () => borg};
    rejects(() => createSourceActorInputPrefixRuntime({world:x.world,gauges,firstMachine:{...x.runtime}}), 'genuine');
    const processor = {gqr4:0x60006};
    const prefix = createSourceActorInputPrefixRuntime({world:x.world,gauges,firstMachine:x.runtime,processor});
    prefix.bindActor(x.id,{byte5fc:0,stickX5ca:20,stickY5cb:0});
    rejects(() => prefix.updateActor(x.id), '8008b780'); equal(x.binding().byte616,7,'angle refusal precedes machine');
    processor.gqr4=0; rejects(() => prefix.updateActor(x.id),'GQR4'); equal(x.binding().byte615,9,'live profile change observed before machine');
  }
  {
    const x = fixture(false, true), b = x.binding();
    check(x.runtime.hasSecondMachine() && x.runtime.getTables().descriptor3904 === x.second, 'explicit second descriptor identity');
    x.actual.statusWord5bc = 0x200; equal(x.run(), 1, 'first call hit before second');
    equal(x.actual.inputEdge5d4, 0x80000021, 'first mask only');
    equal(b.byte618, 0, 'first leaves second phase'); equal(b.byte619, 19, 'first leaves second timer');
    equal(x.runtime.updateSecondMachine(x.id), 1, 'second independently hits same raw edge');
    equal(x.actual.inputEdge5d4, 0x80000061, 'second OR40 retains first20 and high bits');
    equal(b.byte618, 0, 'second phase reset'); equal(b.byte619, 126, 'second nested timer');
    equal(b.byte61a, 0, 'second index clear'); equal(b.byte61b, 0, 'second tail consumed');
    equal(b.byte615, 126, 'second does not replay first timer');
    x.actual.statusWord5bc = 0; equal(x.runtime.updateSecondMachine(x.id), 0, 'second nohit');
    equal(b.byte618, 2, 'second phase waits'); equal(b.byte614, 0, 'first phase independent');
    x.second[0] = 2; x.second[2] = 7; b.byte618 = 0; x.actual.statusWord5bc = 0x200;
    equal(x.runtime.updateSecondMachine(x.id), 0, 'second phase0 sequence'); equal(b.byte61a, 1, 'second sequence index');
    b.byte61a = 0; equal(x.runtime.updateSecondMachine(x.id), 0, 'second real phase1');
    equal(b.byte618, 2, 'second phase1 advance'); equal(b.byte619, 7, 'second timer reload');
  }
  for (const phase of [1,2]) for (let timer = 0; timer < 256; timer++) {
    const x = fixture(false, true), b = x.binding(); b.byte618 = phase; b.byte619 = timer; b.byte61a = 0; b.byte61b = timer;
    const before = [b.byte614,b.byte615,b.byte616,b.byte617];
    equal(x.runtime.updateSecondMachine(x.id), timer ? 1 : 0, 'second wrapper full unsigned tail domain');
    equal(b.byte619, (timer - 1) & 255, 'second raw decrement');
    equal(b.byte618, timer >= 2 && timer <= 128 ? phase : 0, 'second signed expiry');
    equal(b.byte61b, timer ? timer - 1 : 0, 'second tail decrement');
    equal(x.actual.inputEdge5d4, timer ? 0x80000041 : 0x80000001, 'second mask never first20');
    equal(JSON.stringify([b.byte614,b.byte615,b.byte616,b.byte617]), JSON.stringify(before), 'second all states leave first cells');
  }
  {
    const x = fixture(); check(!x.runtime.hasSecondMachine(), 'second not implicitly enabled');
    rejects(() => x.runtime.updateSecondMachine(x.id), '80068610');
    x.tables.descriptor3904 = x.second;
    rejects(() => x.runtime.updateSecondMachine(x.id), '80068610');
    const y = fixture(false, true); y.tables.descriptor3904 = [...y.second];
    rejects(() => y.runtime.updateSecondMachine(y.id), 'owner changed'); equal(y.binding().byte61a,17,'changed second owner refuses before stores');
  }
  for (const key of ['byte618','byte619','byte61a','byte61b'] as const) {
    const x = fixture(true, true); delete x.initial[key]; x.bind();
    rejects(() => x.runtime.updateSecondMachine(x.id), key);
    equal(x.binding().byte615,9,'missing second cell does not mutate first');
    const y = fixture(true, true); Object.defineProperty(y.actual,key,{value:undefined}); rejects(y.bind,'competing');
    const z = fixture(false, true); Object.defineProperty(z.actual,key,{value:undefined}); rejects(z.run,'competing');
  }
  {
    const x = fixture(false, true); x.actual.statusWord5bc = 0x200; delete x.second[3];
    rejects(() => x.runtime.updateSecondMachine(x.id), 'own data property');
    equal(x.binding().byte618,0,'second success phase reset precedes missingduration');
    equal(x.binding().byte619,126,'second timer preserved'); equal(x.actual.inputEdge5d4,0x80000001,'no tail or edge on late handler failure');
    const y = fixture(false,true); y.binding().byte618=2; y.binding().byte61a=2; y.second.push(0x200);
    rejects(() => y.runtime.updateSecondMachine(y.id),'outside explicit12-byte'); equal(y.binding().byte619,18,'second descriptor bound after timer');
    const z = fixture(false,true); z.actual.statusWord5bc=0x200; Object.defineProperty(z.actual,'inputEdge5d4',{writable:false});
    rejects(() => z.runtime.updateSecondMachine(z.id),'non-writable'); equal(z.binding().byte61b,0,'second tail consumed before edge destination check');
  }
  {
    const x = fixture(true,true); x.tables.descriptor3904=x.descriptor;
    rejects(() => createSourceActorInputMachineRuntime({world:x.world,tables:x.tables}),'owner alias');
    const y=fixture(true,true); Object.defineProperty(y.tables,'descriptor3904',{value:undefined});
    rejects(() => createSourceActorInputMachineRuntime({world:y.world,tables:y.tables}),'cannot be undefined');
    const z=fixture(false,true); z.hooks.actual=()=>{try{z.runtime.updateSecondMachine(z.id);}catch{} return z.actual;};
    rejects(z.run,'caught same-runtime'); equal(z.binding().byte61a,17,'cross-machine reentry poisons before second effects');
  }
  for (const raw of [0,0x200,0x400,0x600]) {
    const x=fixture(false,true,true), b=x.binding(); x.actual.statusWord5bc=raw;
    equal(x.run(), raw&0x200?1:0, 'first handler input200');
    equal(x.runtime.updateSecondMachine(x.id), raw&0x200?1:0, 'second handler input200');
    equal(x.runtime.updateThirdMachine(x.id), raw&0x400?1:0, 'third handler input400');
    equal(x.actual.inputEdge5d4,(0x80000001|(raw&0x200?0x60:0)|(raw&0x400?0x80:0))>>>0,'three distinct output masks on same edge');
    equal(b.byte61c,raw&0x400?0:2,'third own phase'); equal(b.byte61d,126,'third own timer');
    equal(b.byte61e,0,'third own index'); equal(b.byte61f,0,'third own tail');
    equal(b.byte615,126,'third leaves first timer'); equal(b.byte619,126,'third leaves second timer');
    check(x.runtime.hasThirdMachine() && x.runtime.getTables().descriptor3910===x.third,'third explicit table identity');
  }
  for (const phase of [1,2]) for (let byte=0;byte<256;byte++) {
    const x=fixture(false,true,true),b=x.binding(); b.byte61c=phase;b.byte61d=byte;b.byte61e=0;b.byte61f=byte;
    equal(x.runtime.updateThirdMachine(x.id),byte?1:0,'third unsigned tail domain');
    equal(b.byte61d,(byte-1)&255,'third raw timer'); equal(b.byte61c,byte>=2&&byte<=128?phase:0,'third signed timer result');
    equal(b.byte61f,byte?byte-1:0,'third tail store'); equal(x.actual.inputEdge5d4,byte?0x80000081:0x80000001,'third80 not20/40');
    equal(b.byte615,9,'third preserves first'); equal(b.byte619,19,'third preserves second');
  }
  {
    const x=fixture(false,true,true),b=x.binding(); x.third[0]=2;x.third[2]=7;x.actual.statusWord5bc=0x400;
    equal(x.runtime.updateThirdMachine(x.id),0,'third phase0 sequence'); equal(b.byte61c,1,'third phase1 selected'); equal(b.byte61e,1,'third index1');
    b.byte61e=0; equal(x.runtime.updateThirdMachine(x.id),0,'third real phase1'); equal(b.byte61c,2,'third phase1 transition');
    equal(b.byte61d,7,'third phase1 timer reload');
  }
  for (const key of ['byte61c','byte61d','byte61e','byte61f'] as const) {
    const x=fixture(true,true,true);delete x.initial[key];x.bind();rejects(()=>x.runtime.updateThirdMachine(x.id),key);
    equal(x.binding().byte615,9,'missing third cells do not replay first');
    const y=fixture(true,true,true);Object.defineProperty(y.actual,key,{value:undefined});rejects(y.bind,'competing');
    const z=fixture(false,true,true);Object.defineProperty(z.actual,key,{value:undefined});rejects(z.run,'competing');
  }
  {
    const x=fixture(false,true);check(!x.runtime.hasThirdMachine(),'third absent');
    rejects(()=>x.runtime.updateThirdMachine(x.id),'80068628'); x.tables.descriptor3910=x.third;
    rejects(()=>x.runtime.updateThirdMachine(x.id),'80068628');
    const y=fixture(false,true,true);y.tables.descriptor3910=[...y.third];rejects(()=>y.runtime.updateThirdMachine(y.id),'owner changed');
    equal(y.binding().byte61e,27,'changed owner before third stores');
    const z=fixture(true,true,true);z.tables.descriptor3910=z.second;
    rejects(()=>createSourceActorInputMachineRuntime({world:z.world,tables:z.tables}),'owner alias');
  }
  {
    const x=fixture(false,true,true);x.actual.statusWord5bc=0x400;delete x.third[3];
    rejects(()=>x.runtime.updateThirdMachine(x.id),'own data property');equal(x.binding().byte61c,0,'third state reset before missing duration');
    equal(x.binding().byte61d,126,'third timer retained');equal(x.actual.inputEdge5d4,0x80000001,'no edge after failed handler');
    const y=fixture(false,true,true);y.binding().byte61c=2;y.binding().byte61e=2;y.third.push(0x400);
    rejects(()=>y.runtime.updateThirdMachine(y.id),'outside explicit12-byte');equal(y.binding().byte61d,28,'third index boundary after timer');
    const z=fixture(false,true,true);z.actual.statusWord5bc=0x400;Object.defineProperty(z.actual,'inputEdge5d4',{writable:false});
    rejects(()=>z.runtime.updateThirdMachine(z.id),'non-writable');equal(z.binding().byte61f,0,'third tail consumed before edge write');
  }
  for (let raw = 0; raw <= 0xe00; raw += 0x200) {
    const x = fixture(false, true, true, true), b = x.binding(); x.actual.statusWord5bc = raw;
    equal(x.run(), raw & 0x200 ? 1 : 0, 'first input200');
    equal(x.runtime.updateSecondMachine(x.id), raw & 0x200 ? 1 : 0, 'second input200');
    equal(x.runtime.updateThirdMachine(x.id), raw & 0x400 ? 1 : 0, 'third input400');
    equal(x.runtime.updateFourthMachine(x.id), raw & 0x800 ? 1 : 0, 'fourth input800');
    equal(x.actual.inputEdge5d4, (0x80000001 | (raw & 0x200 ? 0x60 : 0) |
      (raw & 0x400 ? 0x80 : 0) | (raw & 0x800 ? 0x200 : 0)) >>> 0, 'all four output masks accumulate');
    equal(b.byte624, raw & 0x800 ? 0 : 2, 'fourth phase624, not620');
    equal(b.byte625, 126, 'fourth own timer'); equal(b.byte626, 0, 'fourth own index'); equal(b.byte627, 0, 'fourth own tail');
    equal(b.byte615, 126, 'first timer unaffected'); equal(b.byte619, 126, 'second timer unaffected');
    equal(b.byte61d, 126, 'third timer unaffected');
    check(x.runtime.hasFourthMachine() && x.runtime.getTables().descriptor391c === x.fourth, 'fourth explicit retained table');
  }
  for (const phase of [1, 2]) for (let byte = 0; byte < 256; byte++) {
    const x = fixture(false, true, true, true), b = x.binding();
    b.byte624 = phase; b.byte625 = byte; b.byte626 = 0; b.byte627 = byte;
    equal(x.runtime.updateFourthMachine(x.id), byte ? 1 : 0, 'fourth full unsigned tail domain');
    equal(b.byte625, (byte - 1) & 255, 'fourth raw timer decrement');
    equal(b.byte624, byte >= 2 && byte <= 128 ? phase : 0, 'fourth signed timer expiry');
    equal(b.byte627, byte ? byte - 1 : 0, 'fourth tail decrement');
    equal(x.actual.inputEdge5d4, byte ? 0x80000201 : 0x80000001, 'fourth output200, not input800');
    equal(b.byte615, 9, 'first unchanged'); equal(b.byte619, 19, 'second unchanged'); equal(b.byte61d, 29, 'third unchanged');
  }
  {
    const x = fixture(false, true, true, true), b = x.binding();
    x.fourth[0] = 2; x.fourth[2] = 7; x.actual.statusWord5bc = 0x800;
    equal(x.runtime.updateFourthMachine(x.id), 0, 'fourth phase0 sequence'); equal(b.byte624, 1, 'fourth phase1 selected');
    equal(b.byte626, 1, 'fourth index1'); b.byte626 = 0;
    equal(x.runtime.updateFourthMachine(x.id), 0, 'fourth genuine phase1');
    equal(b.byte624, 2, 'fourth phase1 transition'); equal(b.byte625, 7, 'fourth phase1 reload');
  }
  for (const key of ['byte624', 'byte625', 'byte626', 'byte627'] as const) {
    const x = fixture(true, true, true, true); delete x.initial[key]; x.bind();
    rejects(() => x.runtime.updateFourthMachine(x.id), key); equal(x.binding().byte61d, 29, 'missing fourth does not replay third');
    const y = fixture(true, true, true, true); Object.defineProperty(y.actual, key, {value: undefined}); rejects(y.bind, 'competing');
    const z = fixture(false, true, true, true); Object.defineProperty(z.actual, key, {value: undefined}); rejects(z.run, 'competing');
  }
  {
    const x = fixture(false, true, true); check(!x.runtime.hasFourthMachine(), 'fourth absent without opt-in');
    rejects(() => x.runtime.updateFourthMachine(x.id), '80068640'); x.tables.descriptor391c = x.fourth;
    rejects(() => x.runtime.updateFourthMachine(x.id), '80068640');
    const y = fixture(false, true, true, true); y.tables.descriptor391c = [...y.fourth];
    rejects(() => y.runtime.updateFourthMachine(y.id), 'owner changed'); equal(y.binding().byte626, 37, 'owner replacement refuses before stores');
  }
  for (const key of ['dispatch3988', 'descriptor38f8', 'descriptor3904', 'descriptor3910'] as const) {
    const x = fixture(true, true, true, true); x.tables.descriptor391c = x.tables[key]!;
    rejects(() => createSourceActorInputMachineRuntime({world: x.world, tables: x.tables}), 'owner alias');
  }
  {
    const x = fixture(true, true, true, true); Object.defineProperty(x.tables, 'descriptor391c', {value: undefined});
    rejects(() => createSourceActorInputMachineRuntime({world: x.world, tables: x.tables}), 'cannot be undefined');
    const y = fixture(true, true, true, true); Object.defineProperty(y.tables, 'descriptor391c', {get() {throw Error('getter must not run');}});
    rejects(() => createSourceActorInputMachineRuntime({world: y.world, tables: y.tables}), 'own data property');
    const z = fixture(false, true, true, true);
    z.hooks.actual = () => {try {z.runtime.updateFourthMachine(z.id);} catch {} return z.actual;};
    rejects(z.run, 'caught same-runtime'); equal(z.binding().byte626, 37, 'cross-machine reentry before fourth effects');
  }
  {
    const x = fixture(false, true, true, true); x.actual.statusWord5bc = 0x800; delete x.fourth[3];
    rejects(() => x.runtime.updateFourthMachine(x.id), 'own data property');
    equal(x.binding().byte624, 0, 'phase clear precedes missing duration'); equal(x.binding().byte625, 126, 'timer stores retained');
    equal(x.actual.inputEdge5d4, 0x80000001, 'no edge after failed handler');
    const y = fixture(false, true, true, true); y.binding().byte624 = 2; y.binding().byte626 = 2; y.fourth.push(0x800);
    rejects(() => y.runtime.updateFourthMachine(y.id), 'outside explicit12-byte'); equal(y.binding().byte625, 38, 'index bound after decrement');
    const z = fixture(false, true, true, true); z.actual.statusWord5bc = 0x800;
    Object.defineProperty(z.actual, 'inputEdge5d4', {writable: false});
    rejects(() => z.runtime.updateFourthMachine(z.id), 'non-writable'); equal(z.binding().byte627, 0, 'tail consumed before failed edge store');
  }
  for (let raw = 0; raw <= 0xf00; raw += 0x100) {
    const x = fixture(false, true, true, true, true), b = x.binding();
    x.actual.statusWord5bc = raw; x.actual.inputEdge5d4 = 0x80000000;
    equal(x.run(), raw & 0x200 ? 1 : 0, 'five-call first');
    equal(x.runtime.updateSecondMachine(x.id), raw & 0x200 ? 1 : 0, 'five-call second');
    equal(x.runtime.updateThirdMachine(x.id), raw & 0x400 ? 1 : 0, 'five-call third');
    equal(x.runtime.updateFourthMachine(x.id), raw & 0x800 ? 1 : 0, 'five-call fourth');
    equal(x.runtime.updateFifthMachine(x.id), raw & 0x100 ? 1 : 0, 'fifth input100, not earlier input masks');
    equal(x.actual.inputEdge5d4, (0x80000000 | (raw & 0x200 ? 0x60 : 0) |
      (raw & 0x400 ? 0x80 : 0) | (raw & 0x800 ? 0x200 : 0) | (raw & 0x100 ? 1 : 0)) >>> 0, 'five distinct outputs with fifth bit initially clear');
    equal(b.byte600, raw & 0x100 ? 0 : 2, 'fifth phase600'); equal(b.byte601, 126, 'fifth timer601');
    equal(b.byte602, 0, 'fifth index602'); equal(b.byte603, raw & 0x100 ? 15 : 0, 'fifth authentic duration16 narrowed then consumed');
    check(x.runtime.hasFifthMachine() && x.runtime.getTables().descriptor3928 === x.fifth, 'fifth retained explicit table');
  }
  for (const phase of [1, 2]) for (let byte = 0; byte < 256; byte++) {
    const x = fixture(false, true, true, true, true), b = x.binding();
    x.actual.inputEdge5d4 = 0x800002e0;
    b.byte600 = phase; b.byte601 = byte; b.byte602 = 0; b.byte603 = byte;
    equal(x.runtime.updateFifthMachine(x.id), byte ? 1 : 0, 'fifth unsigned tail domain');
    equal(b.byte601, (byte - 1) & 255, 'fifth raw timer'); equal(b.byte600, byte >= 2 && byte <= 128 ? phase : 0, 'fifth signed expiry');
    equal(b.byte603, byte ? byte - 1 : 0, 'fifth tail decrement');
    equal(x.actual.inputEdge5d4, byte ? 0x800002e1 : 0x800002e0, 'fifth OR1 preserves previous four edges');
    equal(b.byte615, 9, 'fifth leaves first'); equal(b.byte619, 19, 'fifth leaves second');
    equal(b.byte61d, 29, 'fifth leaves third'); equal(b.byte625, 39, 'fifth leaves fourth');
  }
  {
    const x = fixture(false, true, true, true, true), b = x.binding(); x.actual.statusWord5bc = 0x100;
    for (let call = 0; call < 19; call++) {
      if (call === 1) x.actual.statusWord5bc = 0;
      x.actual.inputEdge5d4 = 0x800002e0;
      equal(x.runtime.updateFifthMachine(x.id), call < 16 ? 1 : 0, 'authentic fifth sixteen-call pulse');
      equal(b.byte603, Math.max(15 - call, 0), 'fifth persistent tail retains remaining calls');
      equal(x.actual.inputEdge5d4, call < 16 ? 0x800002e1 : 0x800002e0, 'caller clear exposes full pulse and expiry');
    }
    x.actual.statusWord5bc = 0x100;
    for (let call = 0; call < 3; call++) {
      x.actual.inputEdge5d4 = 0x800002e0;
      equal(x.runtime.updateFifthMachine(x.id), 1, 'repeated fifth source match');
      equal(b.byte603, 15, 'retrigger reloads actual duration16 before each wrapper decrement');
      equal(b.byte600, 0, 'retrigger clears phase'); equal(b.byte601, call === 0 ? 108 : 126, 'fresh source phase and timer preserved');
    }
  }
  for (const key of ['byte600', 'byte601', 'byte602', 'byte603'] as const) {
    const x = fixture(true, true, true, true, true); delete x.initial[key]; x.bind();
    rejects(() => x.runtime.updateFifthMachine(x.id), key); equal(x.binding().byte625, 39, 'missing fifth cannot replay fourth');
    const y = fixture(true, true, true, true, true); Object.defineProperty(y.actual, key, {value: undefined}); rejects(y.bind, 'competing');
    const z = fixture(false, true, true, true, true); Object.defineProperty(z.actual, key, {value: undefined}); rejects(z.run, 'competing');
  }
  {
    const x = fixture(false, true, true, true); check(!x.runtime.hasFifthMachine(), 'fifth absent');
    rejects(() => x.runtime.updateFifthMachine(x.id), '80068658'); x.tables.descriptor3928 = x.fifth;
    rejects(() => x.runtime.updateFifthMachine(x.id), '80068658');
    const y = fixture(false, true, true, true, true); y.tables.descriptor3928 = [...y.fifth];
    rejects(() => y.runtime.updateFifthMachine(y.id), 'owner changed'); equal(y.binding().byte602, 47, 'changed fifth owner before any store');
  }
  for (const key of ['dispatch3988', 'descriptor38f8', 'descriptor3904', 'descriptor3910', 'descriptor391c'] as const) {
    const x = fixture(true, true, true, true, true); x.tables.descriptor3928 = x.tables[key]!;
    rejects(() => createSourceActorInputMachineRuntime({world: x.world, tables: x.tables}), 'owner alias');
  }
  {
    const x = fixture(true, true, true, true, true); Object.defineProperty(x.tables, 'descriptor3928', {value: undefined});
    rejects(() => createSourceActorInputMachineRuntime({world: x.world, tables: x.tables}), 'cannot be undefined');
    const y = fixture(true, true, true, true, true); Object.defineProperty(y.tables, 'descriptor3928', {get() {throw Error('getter must not run');}});
    rejects(() => createSourceActorInputMachineRuntime({world: y.world, tables: y.tables}), 'own data property');
    const z = fixture(false, true, true, true, true);
    z.hooks.actual = () => {try {z.runtime.updateFifthMachine(z.id);} catch {} return z.actual;};
    rejects(z.run, 'caught same-runtime'); equal(z.binding().byte602, 47, 'cross-machine reentry before fifth effects');
  }
  {
    const x = fixture(false, true, true, true, true); x.actual.statusWord5bc = 0x100; delete x.fifth[3];
    rejects(() => x.runtime.updateFifthMachine(x.id), 'own data property');
    equal(x.binding().byte600, 0, 'fifth phase clear before missing duration'); equal(x.binding().byte601, 126, 'fifth prior timer retained');
    const y = fixture(false, true, true, true, true); y.binding().byte600 = 2; y.binding().byte602 = 2; y.fifth.push(0x100);
    rejects(() => y.runtime.updateFifthMachine(y.id), 'outside explicit12-byte'); equal(y.binding().byte601, 48, 'fifth index bounds after decrement');
    const z = fixture(false, true, true, true, true); z.actual.statusWord5bc = 0x100;
    Object.defineProperty(z.actual, 'inputEdge5d4', {writable: false});
    rejects(() => z.runtime.updateFifthMachine(z.id), 'non-writable'); equal(z.binding().byte603, 15, 'fifth actual16 tail consumed before failed edge store');
  }
  for (const control of [0, 0x40]) for (let raw = 0; raw <= 0xf00; raw += 0x100) {
    const x = fixture(false, true, true, true, true, true), b = x.binding();
    x.actual.controlWord = control; x.actual.statusWord5bc = raw; x.actual.inputEdge5d4 = 0x80000000;
    x.run(); x.runtime.updateSecondMachine(x.id); x.runtime.updateThirdMachine(x.id);
    x.runtime.updateFourthMachine(x.id); x.runtime.updateFifthMachine(x.id);
    const hit = control !== 0 && (raw & 0x100) !== 0;
    equal(x.runtime.updateSixthMachine(x.id), hit ? 1 : 0, 'sixth requires control40 and canonical input100');
    equal(x.actual.inputEdge5d4, (0x80000000 | (raw & 0x200 ? 0x60 : 0) |
      (raw & 0x400 ? 0x80 : 0) | (raw & 0x800 ? 0x200 : 0) | (raw & 0x100 ? 1 : 0) | (hit ? 2 : 0)) >>> 0,
      'six outputs distinguish flags4 from fifth flags0');
    equal(b.byte604, hit ? 0 : 2, 'sixth phase604'); equal(b.byte605, 126, 'sixth timer605');
    equal(b.byte606, 0, 'sixth index606'); equal(b.byte607, 0, 'sixth duration1 consumed, never fifth duration16');
    equal(b.byte603, raw & 0x100 ? 15 : 0, 'sixth leaves fifth long tail independent');
    check(x.runtime.hasSixthMachine() && x.runtime.getTables().descriptor3934 === x.sixth, 'sixth explicit retained owner');
  }
  for (const control of [0, 0x40]) for (const phase of [1, 2]) for (let byte = 0; byte < 256; byte++) {
    const x = fixture(false, true, true, true, true, true), b = x.binding();
    x.actual.controlWord = control; x.actual.inputEdge5d4 = 0x800002e1;
    b.byte604 = phase; b.byte605 = byte; b.byte606 = 0; b.byte607 = byte;
    equal(x.runtime.updateSixthMachine(x.id), byte ? 1 : 0, 'sixth unsigned tail survives gate and timer expiry');
    equal(b.byte605, (byte - 1) & 255, 'sixth raw timer'); equal(b.byte604, byte >= 2 && byte <= 128 ? phase : 0, 'sixth signed timer');
    equal(b.byte607, byte ? byte - 1 : 0, 'sixth tail decrement');
    equal(x.actual.inputEdge5d4, byte ? 0x800002e3 : 0x800002e1, 'sixth OR2 is observed with bit1 initially clear');
    equal(b.byte601, 49, 'sixth leaves fifth timer'); equal(b.byte603, 0, 'sixth leaves fifth tail');
  }
  for (const fault of ['input', 'index', 'mask'] as const) for (const control of [0, 0x40]) {
    const x = fixture(false, true, true, true, true, true), b = x.binding();
    b.byte604 = 2; b.byte605 = 2; b.byte606 = 0; x.actual.controlWord = control; x.actual.inputEdge5d4 = 0x800002e1;
    if (fault === 'input') delete (x.actual as Partial<typeof x.actual>).statusWord5bc;
    else if (fault === 'index') b.byte606 = 255;
    else delete x.sixth[4];
    if (control === 0) equal(x.runtime.updateSixthMachine(x.id), 0, 'clear control gate skips input/index/mask validation');
    else rejects(() => x.runtime.updateSixthMachine(x.id), fault === 'input' ? 'statusWord5bc' : fault === 'index' ? 'outside explicit12-byte' : 'own data property');
    equal(b.byte605, 1, 'timer store precedes gate or reached input failure');
    equal(x.actual.inputEdge5d4, 0x800002e1, 'skipped or failed source reads never fabricate output2');
  }
  {
    const x = fixture(false, true, true, true, true, true), b = x.binding();
    x.actual.controlWord = 0; delete (x.actual as Partial<typeof x.actual>).statusWord5bc; delete x.sixth[4];
    b.byte604 = 2; b.byte605 = 3; b.byte606 = 255; b.byte607 = 2; x.actual.inputEdge5d4 = 0x800002e1;
    equal(x.runtime.updateSixthMachine(x.id), 1, 'gated handler still executes live wrapper tail');
    equal(b.byte605, 2, 'gated timer retained'); equal(b.byte607, 1, 'gated tail consumed'); equal(x.actual.inputEdge5d4, 0x800002e3, 'gated tail emits2');
  }
  {
    const x = fixture(false, true, true, true, true, true), b = x.binding();
    x.actual.statusWord5bc = 0x100; x.actual.controlWord = 0x40;
    equal(x.runtime.updateFifthMachine(x.id), 1, 'fifth shares input100'); equal(x.runtime.updateSixthMachine(x.id), 1, 'sixth enabled hit');
    equal(b.byte603, 15, 'fifth duration16'); equal(b.byte607, 0, 'sixth duration1');
    x.actual.statusWord5bc = 0; x.actual.inputEdge5d4 = 0;
    equal(x.runtime.updateFifthMachine(x.id), 1, 'fifth no-hit pulse persists'); equal(x.runtime.updateSixthMachine(x.id), 0, 'sixth no-hit pulse ends');
    equal(x.actual.inputEdge5d4, 1, 'only fifth output remains on next call');
    x.actual.statusWord5bc = 0x100; x.actual.controlWord = 0; equal(x.runtime.updateSixthMachine(x.id), 0, 'clear control blocks later hit');
    x.actual.controlWord = 0x40; equal(x.runtime.updateSixthMachine(x.id), 1, 'live control transition permits hit'); equal(b.byte607, 0, 'permitted duration consumed');
  }
  for (const key of ['byte604', 'byte605', 'byte606', 'byte607'] as const) {
    const x = fixture(true, true, true, true, true, true); delete x.initial[key]; x.bind();
    rejects(() => x.runtime.updateSixthMachine(x.id), key); equal(x.binding().byte601, 49, 'missing sixth does not replay fifth');
    const y = fixture(true, true, true, true, true, true); Object.defineProperty(y.actual, key, {value: undefined}); rejects(y.bind, 'competing');
    const z = fixture(false, true, true, true, true, true); Object.defineProperty(z.actual, key, {value: undefined}); rejects(z.run, 'competing');
  }
  {
    const x = fixture(false, true, true, true, true); check(!x.runtime.hasSixthMachine(), 'sixth absent');
    rejects(() => x.runtime.updateSixthMachine(x.id), '80068670'); x.tables.descriptor3934 = x.sixth;
    rejects(() => x.runtime.updateSixthMachine(x.id), '80068670');
    const y = fixture(false, true, true, true, true, true); y.tables.descriptor3934 = [...y.sixth];
    rejects(() => y.runtime.updateSixthMachine(y.id), 'owner changed'); equal(y.binding().byte606, 57, 'replacement fails before sixth stores');
  }
  for (const key of ['dispatch3988', 'descriptor38f8', 'descriptor3904', 'descriptor3910', 'descriptor391c', 'descriptor3928'] as const) {
    const x = fixture(true, true, true, true, true, true); x.tables.descriptor3934 = x.tables[key]!;
    rejects(() => createSourceActorInputMachineRuntime({world: x.world, tables: x.tables}), 'owner alias');
  }
  {
    const x = fixture(true, true, true, true, true, true); Object.defineProperty(x.tables, 'descriptor3934', {value: undefined});
    rejects(() => createSourceActorInputMachineRuntime({world: x.world, tables: x.tables}), 'cannot be undefined');
    const y = fixture(true, true, true, true, true, true); Object.defineProperty(y.tables, 'descriptor3934', {get() {throw Error('getter must not run');}});
    rejects(() => createSourceActorInputMachineRuntime({world: y.world, tables: y.tables}), 'own data property');
    const z = fixture(false, true, true, true, true, true);
    z.hooks.actual = () => {try {z.runtime.updateSixthMachine(z.id);} catch {} return z.actual;};
    rejects(z.run, 'caught same-runtime'); equal(z.binding().byte606, 57, 'cross-machine reentry before sixth effects');
  }
  {
    const x = fixture(false, true, true, true, true, true); x.actual.statusWord5bc = 0x100; x.actual.controlWord = 0x40; delete x.sixth[3];
    rejects(() => x.runtime.updateSixthMachine(x.id), 'own data property');
    equal(x.binding().byte604, 0, 'sixth phase clear before missing duration'); equal(x.binding().byte605, 126, 'sixth timer retained');
    const y = fixture(false, true, true, true, true, true); y.actual.controlWord = 0x40;
    y.binding().byte604 = 2; y.binding().byte606 = 2; y.sixth.push(0x100);
    rejects(() => y.runtime.updateSixthMachine(y.id), 'outside explicit12-byte'); equal(y.binding().byte605, 58, 'sixth bound after timer/gate/input');
    const z = fixture(false, true, true, true, true, true); z.actual.statusWord5bc = 0x100; z.actual.controlWord = 0x40;
    Object.defineProperty(z.actual, 'inputEdge5d4', {writable: false});
    rejects(() => z.runtime.updateSixthMachine(z.id), 'non-writable'); equal(z.binding().byte607, 0, 'sixth tail consumed before failed edge store');
  }
  for (const control of [0, 0x40]) for (const low of [0, 0x20]) for (let raw = 0; raw <= 0xf00; raw += 0x100) {
    const x = fixture(false, true, true, true, true, true, true), b = x.binding();
    x.actual.controlWord = control; x.actual.statusWord5bc = raw | low; x.actual.inputEdge5d4 = 0x80000000;
    x.run(); x.runtime.updateSecondMachine(x.id); x.runtime.updateThirdMachine(x.id);
    x.runtime.updateFourthMachine(x.id); x.runtime.updateFifthMachine(x.id); x.runtime.updateSixthMachine(x.id);
    equal(x.runtime.updateSeventhMachine(x.id), low ? 1 : 0, 'seventh canonical input20 independent of control40 and prior100');
    equal(x.actual.inputEdge5d4, (0x80000000 | (raw & 0x200 ? 0x60 : 0) |
      (raw & 0x400 ? 0x80 : 0) | (raw & 0x800 ? 0x200 : 0) | (raw & 0x100 ? 1 : 0) |
      (control && (raw & 0x100) ? 2 : 0) | (low ? 4 : 0)) >>> 0, 'seven distinct outputs retain prior ORs');
    equal(b.byte608, low ? 0 : 2, 'seventh phase608'); equal(b.byte609, 126, 'seventh timer609');
    equal(b.byte60a, 0, 'seventh index60a'); equal(b.byte60b, 0, 'seventh duration1 consumed');
    equal(b.byte603, raw & 0x100 ? 15 : 0, 'seventh leaves fifth duration16 tail independent');
    check(x.runtime.hasSeventhMachine() && x.runtime.getTables().descriptor3940 === x.seventh, 'seventh explicit retained owner');
  }
  for (const control of [0, 0x40]) for (const phase of [1, 2]) for (let byte = 0; byte < 256; byte++) {
    const x = fixture(false, true, true, true, true, true, true), b = x.binding();
    x.actual.controlWord = control; x.actual.inputEdge5d4 = 0x800002e3;
    b.byte608 = phase; b.byte609 = byte; b.byte60a = 0; b.byte60b = byte;
    equal(x.runtime.updateSeventhMachine(x.id), byte ? 1 : 0, 'seventh unsigned tail survives timer expiry');
    equal(b.byte609, (byte - 1) & 255, 'seventh raw timer'); equal(b.byte608, byte >= 2 && byte <= 128 ? phase : 0, 'seventh signed timer');
    equal(b.byte60b, byte ? byte - 1 : 0, 'seventh tail decrement');
    equal(x.actual.inputEdge5d4, byte ? 0x800002e7 : 0x800002e3, 'seventh OR4 is observed with bit2 initially clear');
    equal(b.byte605, 59, 'seventh leaves sixth timer'); equal(b.byte607, 0, 'seventh leaves sixth tail');
  }
  for (const raw of [0, 0x20]) {
    const x = fixture(false, true, true, true, true, true, true), a = x.actual;
    a.statusWord5bc = raw; a.statusWord5b4 = raw ? 0 : 0xffffffff; a.inputHeld5d8 = raw ? 0 : 0x20;
    Object.defineProperty(a, 'controlWord', {get() {throw Error('control getter must not run');}});
    Object.defineProperty(a, 'statusWord5b4', {get() {throw Error('status getter must not run');}});
    equal(x.runtime.updateSeventhMachine(x.id), raw ? 1 : 0, 'seventh flags0 never loads control or status5b4');
  }
  for (const fault of ['input', 'index', 'mask'] as const) for (const control of [0, 0x40]) {
    const x = fixture(false, true, true, true, true, true, true), b = x.binding();
    b.byte608 = 2; b.byte609 = 2; b.byte60a = 0; x.actual.controlWord = control; x.actual.inputEdge5d4 = 0x800002e3;
    if (fault === 'input') delete (x.actual as Partial<typeof x.actual>).statusWord5bc;
    else if (fault === 'index') b.byte60a = 255;
    else delete x.seventh[4];
    rejects(() => x.runtime.updateSeventhMachine(x.id), fault === 'input' ? 'statusWord5bc' : fault === 'index' ? 'outside explicit12-byte' : 'own data property');
    equal(b.byte609, 1, 'timer store precedes reached seventh read failure with either control state');
    equal(x.actual.inputEdge5d4, 0x800002e3, 'failed source reads do not fabricate output4');
  }
  {
    const x = fixture(false, true, true, true, true, true, true), b = x.binding();
    b.byte608 = 2; b.byte609 = 1; b.byte60a = 255; b.byte60b = 2; x.actual.inputEdge5d4 = 0x800002e3;
    delete (x.actual as Partial<typeof x.actual>).statusWord5bc; x.seventh.length = 0;
    equal(x.runtime.updateSeventhMachine(x.id), 1, 'expired seventh skips all descriptor/input reads but reaches existing tail');
    equal(b.byte608, 0, 'expired seventh phase clear'); equal(b.byte60b, 1, 'expired seventh tail consumed');
    equal(x.actual.inputEdge5d4, 0x800002e7, 'expired seventh emits4 from retained tail');
  }
  {
    const x = fixture(false, true, true, true, true, true, true), b = x.binding();
    x.actual.statusWord5bc = 0x120; x.actual.controlWord = 0x40;
    equal(x.runtime.updateFifthMachine(x.id), 1, 'fifth100 hit'); equal(x.runtime.updateSixthMachine(x.id), 1, 'sixth gated100 hit');
    equal(x.runtime.updateSeventhMachine(x.id), 1, 'seventh independent20 hit');
    equal(b.byte603, 15, 'fifth duration16'); equal(b.byte607, 0, 'sixth duration1'); equal(b.byte60b, 0, 'seventh duration1');
    x.actual.statusWord5bc = 0; x.actual.inputEdge5d4 = 0;
    equal(x.runtime.updateFifthMachine(x.id), 1, 'fifth nohit tail persists'); equal(x.runtime.updateSixthMachine(x.id), 0, 'sixth pulse ended');
    equal(x.runtime.updateSeventhMachine(x.id), 0, 'seventh pulse ended'); equal(x.actual.inputEdge5d4, 1, 'only fifth tail persists');
    x.actual.statusWord5bc = 0x20;
    for (const control of [0, 0x40, 0]) {x.actual.controlWord = control;
      equal(x.runtime.updateSeventhMachine(x.id), 1, 'live control transitions never gate seventh20');}
    b.byte608 = 1; b.byte609 = 3; b.byte60a = 0;
    equal(x.runtime.updateSeventhMachine(x.id), 0, 'retained seventh phase1 any-bit hit stays wrapper0');
    equal(b.byte609, 0, 'phase1 reload0'); equal(b.byte60a, 1, 'phase1 index increments'); equal(b.byte608, 1, 'mode1 leaves phase1');
  }
  for (const key of ['byte608', 'byte609', 'byte60a', 'byte60b'] as const) {
    const x = fixture(true, true, true, true, true, true, true); delete x.initial[key]; x.bind();
    rejects(() => x.runtime.updateSeventhMachine(x.id), key); equal(x.binding().byte605, 59, 'missing seventh never replays sixth');
    const y = fixture(true, true, true, true, true, true, true); Object.defineProperty(y.actual, key, {value: undefined}); rejects(y.bind, 'competing');
    const z = fixture(false, true, true, true, true, true, true); Object.defineProperty(z.actual, key, {value: undefined}); rejects(z.run, 'competing');
  }
  {
    const x = fixture(false, true, true, true, true, true); check(!x.runtime.hasSeventhMachine(), 'seventh absent');
    rejects(() => x.runtime.updateSeventhMachine(x.id), '80068688'); x.tables.descriptor3940 = x.seventh;
    rejects(() => x.runtime.updateSeventhMachine(x.id), '80068688');
    const y = fixture(false, true, true, true, true, true, true); y.tables.descriptor3940 = [...y.seventh];
    rejects(() => y.runtime.updateSeventhMachine(y.id), 'owner changed'); equal(y.binding().byte60a, 67, 'replacement fails before seventh stores');
  }
  for (const key of ['dispatch3988', 'descriptor38f8', 'descriptor3904', 'descriptor3910', 'descriptor391c', 'descriptor3928', 'descriptor3934'] as const) {
    const x = fixture(true, true, true, true, true, true, true); x.tables.descriptor3940 = x.tables[key]!;
    rejects(() => createSourceActorInputMachineRuntime({world: x.world, tables: x.tables}), 'owner alias');
  }
  {
    const x = fixture(true, true, true, true, true, true, true); Object.defineProperty(x.tables, 'descriptor3940', {value: undefined});
    rejects(() => createSourceActorInputMachineRuntime({world: x.world, tables: x.tables}), 'cannot be undefined');
    const y = fixture(true, true, true, true, true, true, true); Object.defineProperty(y.tables, 'descriptor3940', {get() {throw Error('getter must not run');}});
    rejects(() => createSourceActorInputMachineRuntime({world: y.world, tables: y.tables}), 'own data property');
    const z = fixture(false, true, true, true, true, true, true);
    z.hooks.actual = () => {try {z.runtime.updateSeventhMachine(z.id);} catch {} return z.actual;};
    rejects(z.run, 'caught same-runtime'); equal(z.binding().byte60a, 67, 'cross-machine reentry before seventh effects');
  }
  {
    const x = fixture(false, true, true, true, true, true, true); x.actual.statusWord5bc = 0x20; delete x.seventh[3];
    rejects(() => x.runtime.updateSeventhMachine(x.id), 'own data property');
    equal(x.binding().byte608, 0, 'seventh phase clear before missing duration'); equal(x.binding().byte609, 126, 'seventh timer retained');
    const y = fixture(false, true, true, true, true, true, true); y.binding().byte608 = 2; y.binding().byte60a = 2; y.seventh.push(0x20);
    rejects(() => y.runtime.updateSeventhMachine(y.id), 'outside explicit12-byte'); equal(y.binding().byte609, 68, 'seventh bounds after timer/input');
    const z = fixture(false, true, true, true, true, true, true); z.actual.statusWord5bc = 0x20;
    Object.defineProperty(z.actual, 'inputEdge5d4', {writable: false});
    rejects(() => z.runtime.updateSeventhMachine(z.id), 'non-writable'); equal(z.binding().byte60b, 0, 'seventh tail consumed before failed edge store');
  }
  for (const control of [0, 0x40]) for (const low of [0, 0x20, 0x40, 0x60]) for (let raw = 0; raw <= 0xf00; raw += 0x100) {
    const x = fixture(false, true, true, true, true, true, true, true), b = x.binding();
    x.actual.controlWord = control; x.actual.statusWord5bc = raw | low; x.actual.inputEdge5d4 = 0x80000000;
    x.run(); x.runtime.updateSecondMachine(x.id); x.runtime.updateThirdMachine(x.id);
    x.runtime.updateFourthMachine(x.id); x.runtime.updateFifthMachine(x.id); x.runtime.updateSixthMachine(x.id); x.runtime.updateSeventhMachine(x.id);
    const hit = (low & 0x40) !== 0;
    equal(x.runtime.updateEighthMachine(x.id), hit ? 1 : 0, 'eighth canonical input40 is independent of control40 and seventh20');
    equal(x.actual.inputEdge5d4, (0x80000000 | (raw & 0x200 ? 0x60 : 0) |
      (raw & 0x400 ? 0x80 : 0) | (raw & 0x800 ? 0x200 : 0) | (raw & 0x100 ? 1 : 0) |
      (control && (raw & 0x100) ? 2 : 0) | (low & 0x20 ? 4 : 0) | (hit ? 8 : 0)) >>> 0, 'eight outputs retain independent prior ORs');
    equal(b.byte60c, hit ? 0 : 2, 'eighth phase60c'); equal(b.byte60d, 126, 'eighth timer60d');
    equal(b.byte60e, 0, 'eighth index60e'); equal(b.byte60f, 0, 'eighth duration1 consumed');
    equal(b.byte608, low & 0x20 ? 0 : 2, 'eighth does not reuse seventh phase');
    equal(b.byte603, raw & 0x100 ? 15 : 0, 'eighth leaves fifth long tail independent');
    check(x.runtime.hasEighthMachine() && x.runtime.getTables().descriptor394c === x.eighth, 'eighth explicit retained owner');
  }
  for (const control of [0, 0x40]) for (const phase of [1, 2]) for (let byte = 0; byte < 256; byte++) {
    const x = fixture(false, true, true, true, true, true, true, true), b = x.binding();
    x.actual.controlWord = control; x.actual.inputEdge5d4 = 0x800002e7;
    b.byte60c = phase; b.byte60d = byte; b.byte60e = 0; b.byte60f = byte;
    equal(x.runtime.updateEighthMachine(x.id), byte ? 1 : 0, 'eighth unsigned tail survives timer expiry');
    equal(b.byte60d, (byte - 1) & 255, 'eighth raw timer'); equal(b.byte60c, byte >= 2 && byte <= 128 ? phase : 0, 'eighth signed timer');
    equal(b.byte60f, byte ? byte - 1 : 0, 'eighth tail decrement');
    equal(x.actual.inputEdge5d4, byte ? 0x800002ef : 0x800002e7, 'eighth OR8 is observed with bit3 initially clear');
    equal(b.byte609, 69, 'eighth leaves seventh timer'); equal(b.byte60b, 0, 'eighth leaves seventh tail');
  }
  for (const raw of [0, 0x40]) {
    const x = fixture(false, true, true, true, true, true, true, true), a = x.actual;
    a.statusWord5bc = raw; a.inputHeld5d8 = raw ? 0 : 0x40;
    Object.defineProperty(a, 'controlWord', {get() {throw Error('control getter must not run');}});
    Object.defineProperty(a, 'statusWord5b4', {get() {throw Error('status getter must not run');}});
    equal(x.runtime.updateEighthMachine(x.id), raw ? 1 : 0, 'eighth flags0 never loads control or status5b4');
  }
  for (const fault of ['input', 'index', 'mask'] as const) for (const control of [0, 0x40]) {
    const x = fixture(false, true, true, true, true, true, true, true), b = x.binding();
    b.byte60c = 2; b.byte60d = 2; b.byte60e = 0; x.actual.controlWord = control; x.actual.inputEdge5d4 = 0x800002e7;
    if (fault === 'input') delete (x.actual as Partial<typeof x.actual>).statusWord5bc;
    else if (fault === 'index') b.byte60e = 255;
    else delete x.eighth[4];
    rejects(() => x.runtime.updateEighthMachine(x.id), fault === 'input' ? 'statusWord5bc' : fault === 'index' ? 'outside explicit12-byte' : 'own data property');
    equal(b.byte60d, 1, 'timer store precedes reached eighth read failure under either control state');
    equal(x.actual.inputEdge5d4, 0x800002e7, 'failed reads do not fabricate output8');
  }
  {
    const x = fixture(false, true, true, true, true, true, true, true), b = x.binding();
    b.byte60c = 2; b.byte60d = 1; b.byte60e = 255; b.byte60f = 2; x.actual.inputEdge5d4 = 0x800002e7;
    delete (x.actual as Partial<typeof x.actual>).statusWord5bc; x.eighth.length = 0;
    equal(x.runtime.updateEighthMachine(x.id), 1, 'expired eighth skips descriptor/input reads but reaches existing tail');
    equal(b.byte60c, 0, 'expired eighth phase clear'); equal(b.byte60f, 1, 'expired eighth tail consumed');
    equal(x.actual.inputEdge5d4, 0x800002ef, 'expired eighth emits8 from retained tail');
  }
  {
    const x = fixture(false, true, true, true, true, true, true, true), b = x.binding();
    x.actual.statusWord5bc = 0x160; x.actual.controlWord = 0x40;
    equal(x.runtime.updateFifthMachine(x.id), 1, 'fifth100 hit'); equal(x.runtime.updateSixthMachine(x.id), 1, 'sixth gated100 hit');
    equal(x.runtime.updateSeventhMachine(x.id), 1, 'seventh20 hit'); equal(x.runtime.updateEighthMachine(x.id), 1, 'eighth40 hit');
    equal(b.byte603, 15, 'fifth duration16'); equal(b.byte607, 0, 'sixth duration1'); equal(b.byte60b, 0, 'seventh duration1'); equal(b.byte60f, 0, 'eighth duration1');
    x.actual.statusWord5bc = 0; x.actual.inputEdge5d4 = 0;
    equal(x.runtime.updateFifthMachine(x.id), 1, 'fifth nohit tail persists'); equal(x.runtime.updateSixthMachine(x.id), 0, 'sixth pulse ended');
    equal(x.runtime.updateSeventhMachine(x.id), 0, 'seventh pulse ended'); equal(x.runtime.updateEighthMachine(x.id), 0, 'eighth pulse ended');
    equal(x.actual.inputEdge5d4, 1, 'only fifth tail persists'); x.actual.statusWord5bc = 0x40;
    for (const control of [0, 0x40, 0]) {x.actual.controlWord = control;
      equal(x.runtime.updateEighthMachine(x.id), 1, 'live control transitions never gate eighth canonical40');}
    b.byte60c = 1; b.byte60d = 3; b.byte60e = 0;
    equal(x.runtime.updateEighthMachine(x.id), 0, 'retained eighth phase1 any-bit hit stays wrapper0');
    equal(b.byte60d, 0, 'phase1 reload0'); equal(b.byte60e, 1, 'phase1 index increments'); equal(b.byte60c, 1, 'mode1 leaves phase1');
  }
  for (const key of ['byte60c', 'byte60d', 'byte60e', 'byte60f'] as const) {
    const x = fixture(true, true, true, true, true, true, true, true); delete x.initial[key]; x.bind();
    rejects(() => x.runtime.updateEighthMachine(x.id), key); equal(x.binding().byte609, 69, 'missing eighth never replays seventh');
    const y = fixture(true, true, true, true, true, true, true, true); Object.defineProperty(y.actual, key, {value: undefined}); rejects(y.bind, 'competing');
    const z = fixture(false, true, true, true, true, true, true, true); Object.defineProperty(z.actual, key, {value: undefined}); rejects(z.run, 'competing');
  }
  {
    const x = fixture(false, true, true, true, true, true, true); check(!x.runtime.hasEighthMachine(), 'eighth absent');
    rejects(() => x.runtime.updateEighthMachine(x.id), '800686a0'); x.tables.descriptor394c = x.eighth;
    rejects(() => x.runtime.updateEighthMachine(x.id), '800686a0');
    const y = fixture(false, true, true, true, true, true, true, true); y.tables.descriptor394c = [...y.eighth];
    rejects(() => y.runtime.updateEighthMachine(y.id), 'owner changed'); equal(y.binding().byte60e, 77, 'replacement fails before eighth stores');
  }
  for (const key of ['dispatch3988', 'descriptor38f8', 'descriptor3904', 'descriptor3910', 'descriptor391c', 'descriptor3928', 'descriptor3934', 'descriptor3940'] as const) {
    const x = fixture(true, true, true, true, true, true, true, true); x.tables.descriptor394c = x.tables[key]!;
    rejects(() => createSourceActorInputMachineRuntime({world: x.world, tables: x.tables}), 'owner alias');
  }
  {
    const x = fixture(true, true, true, true, true, true, true, true); Object.defineProperty(x.tables, 'descriptor394c', {value: undefined});
    rejects(() => createSourceActorInputMachineRuntime({world: x.world, tables: x.tables}), 'cannot be undefined');
    const y = fixture(true, true, true, true, true, true, true, true); Object.defineProperty(y.tables, 'descriptor394c', {get() {throw Error('getter must not run');}});
    rejects(() => createSourceActorInputMachineRuntime({world: y.world, tables: y.tables}), 'own data property');
    const z = fixture(false, true, true, true, true, true, true, true);
    z.hooks.actual = () => {try {z.runtime.updateEighthMachine(z.id);} catch {} return z.actual;};
    rejects(z.run, 'caught same-runtime'); equal(z.binding().byte60e, 77, 'cross-machine reentry before eighth effects');
  }
  {
    const x = fixture(false, true, true, true, true, true, true, true); x.actual.statusWord5bc = 0x40; delete x.eighth[3];
    rejects(() => x.runtime.updateEighthMachine(x.id), 'own data property');
    equal(x.binding().byte60c, 0, 'eighth phase clear before missing duration'); equal(x.binding().byte60d, 126, 'eighth timer retained');
    const y = fixture(false, true, true, true, true, true, true, true); y.binding().byte60c = 2; y.binding().byte60e = 2; y.eighth.push(0x40);
    rejects(() => y.runtime.updateEighthMachine(y.id), 'outside explicit12-byte'); equal(y.binding().byte60d, 78, 'eighth bound after timer/input');
    const z = fixture(false, true, true, true, true, true, true, true); z.actual.statusWord5bc = 0x40;
    Object.defineProperty(z.actual, 'inputEdge5d4', {writable: false});
    rejects(() => z.runtime.updateEighthMachine(z.id), 'non-writable'); equal(z.binding().byte60f, 0, 'eighth tail consumed before failed edge store');
  }
  for (const control of [0, 0x40]) for (let low = 0; low <= 0x70; low += 0x10) for (let raw = 0; raw <= 0xf00; raw += 0x100) {
    const x = fixture(false, true, true, true, true, true, true, true, true), b = x.binding();
    x.actual.controlWord = control; x.actual.statusWord5bc = raw | low; x.actual.inputEdge5d4 = 0x80000000;
    x.run(); x.runtime.updateSecondMachine(x.id); x.runtime.updateThirdMachine(x.id);
    x.runtime.updateFourthMachine(x.id); x.runtime.updateFifthMachine(x.id); x.runtime.updateSixthMachine(x.id);
    x.runtime.updateSeventhMachine(x.id); x.runtime.updateEighthMachine(x.id);
    const hit = (low & 0x10) !== 0;
    equal(x.runtime.updateNinthMachine(x.id), hit ? 1 : 0, 'ninth canonical input10 is separate from seventh20, eighth40 and control40');
    equal(x.actual.inputEdge5d4, (0x80000000 | (raw & 0x200 ? 0x60 : 0) | (raw & 0x400 ? 0x80 : 0) |
      (raw & 0x800 ? 0x200 : 0) | (raw & 0x100 ? 1 : 0) | (control && (raw & 0x100) ? 2 : 0) |
      (low & 0x20 ? 4 : 0) | (low & 0x40 ? 8 : 0) | (hit ? 0x10 : 0)) >>> 0, 'nine outputs retain independent prior ORs');
    equal(b.byte610, hit ? 0 : 2, 'ninth phase610'); equal(b.byte611, 126, 'ninth timer611');
    equal(b.byte612, 0, 'ninth index612'); equal(b.byte613, 0, 'ninth duration1 consumed');
    equal(b.byte60c, low & 0x40 ? 0 : 2, 'ninth does not reuse eighth phase');
    equal(b.byte603, raw & 0x100 ? 15 : 0, 'ninth leaves fifth long tail');
    check(x.runtime.hasNinthMachine() && x.runtime.getTables().descriptor3958 === x.ninth, 'ninth explicit retained owner');
  }
  for (const control of [0, 0x40]) for (const phase of [1, 2]) for (let byte = 0; byte < 256; byte++) {
    const x = fixture(false, true, true, true, true, true, true, true, true), b = x.binding();
    x.actual.controlWord = control; x.actual.inputEdge5d4 = 0x800002ef;
    b.byte610 = phase; b.byte611 = byte; b.byte612 = 0; b.byte613 = byte;
    equal(x.runtime.updateNinthMachine(x.id), byte ? 1 : 0, 'ninth unsigned tail survives timer expiry');
    equal(b.byte611, (byte - 1) & 255, 'ninth raw timer'); equal(b.byte610, byte >= 2 && byte <= 128 ? phase : 0, 'ninth signed timer');
    equal(b.byte613, byte ? byte - 1 : 0, 'ninth tail decrement');
    equal(x.actual.inputEdge5d4, byte ? 0x800002ff : 0x800002ef, 'ninth OR10 observed with bit4 initially clear');
    equal(b.byte60d, 79, 'ninth leaves eighth timer'); equal(b.byte60f, 0, 'ninth leaves eighth tail');
  }
  for (const raw of [0, 0x10]) {
    const x = fixture(false, true, true, true, true, true, true, true, true), a = x.actual;
    a.statusWord5bc = raw; a.inputHeld5d8 = raw ? 0 : 0x10;
    Object.defineProperty(a, 'controlWord', {get() {throw Error('control getter must not run');}});
    Object.defineProperty(a, 'statusWord5b4', {get() {throw Error('status getter must not run');}});
    equal(x.runtime.updateNinthMachine(x.id), raw ? 1 : 0, 'ninth flags0 never loads control or status5b4');
  }
  {
    const x = fixture(false, true, true, true, true, true, true, true, true);
    x.ninth[4] = 0x80; x.actual.statusWord5bc = 0x80; x.actual.inputEdge5d4 = 0x800002ef;
    equal(x.runtime.updateNinthMachine(x.id), 1, 'retained descriptor mask is read rather than hardcoded caller output10');
    equal(x.actual.inputEdge5d4, 0x800002ff, 'caller output remains10 when retained input mask changes to80');
    x.actual.statusWord5bc = 0x10; x.actual.inputEdge5d4 = 0;
    equal(x.runtime.updateNinthMachine(x.id), 0, 'same-valued canonical input/output10 were distinct source roles');
    equal(x.actual.inputEdge5d4, 0, 'output word cannot replace the changed descriptor input predicate');
  }
  for (const fault of ['input', 'index', 'mask'] as const) for (const control of [0, 0x40]) {
    const x = fixture(false, true, true, true, true, true, true, true, true), b = x.binding();
    b.byte610 = 2; b.byte611 = 2; b.byte612 = 0; x.actual.controlWord = control; x.actual.inputEdge5d4 = 0x800002ef;
    if (fault === 'input') delete (x.actual as Partial<typeof x.actual>).statusWord5bc;
    else if (fault === 'index') b.byte612 = 255; else delete x.ninth[4];
    rejects(() => x.runtime.updateNinthMachine(x.id), fault === 'input' ? 'statusWord5bc' : fault === 'index' ? 'outside explicit12-byte' : 'own data property');
    equal(b.byte611, 1, 'ninth timer store precedes reached input/index/mask failure');
    equal(x.actual.inputEdge5d4, 0x800002ef, 'failed reads do not fabricate output10');
  }
  {
    const x = fixture(false, true, true, true, true, true, true, true, true), b = x.binding();
    b.byte610 = 2; b.byte611 = 1; b.byte612 = 255; b.byte613 = 2; x.actual.inputEdge5d4 = 0x800002ef;
    delete (x.actual as Partial<typeof x.actual>).statusWord5bc; x.ninth.length = 0;
    equal(x.runtime.updateNinthMachine(x.id), 1, 'expired ninth skips descriptor/input reads but reaches existing tail');
    equal(b.byte610, 0, 'expired ninth phase clear'); equal(b.byte613, 1, 'expired ninth tail consumed');
    equal(x.actual.inputEdge5d4, 0x800002ff, 'expired ninth emits10 from retained tail');
  }
  {
    const x = fixture(false, true, true, true, true, true, true, true, true), b = x.binding();
    x.actual.statusWord5bc = 0x170; x.actual.controlWord = 0x40;
    equal(x.runtime.updateFifthMachine(x.id), 1, 'fifth100 hit'); equal(x.runtime.updateSixthMachine(x.id), 1, 'sixth gated100 hit');
    equal(x.runtime.updateSeventhMachine(x.id), 1, 'seventh20 hit'); equal(x.runtime.updateEighthMachine(x.id), 1, 'eighth40 hit');
    equal(x.runtime.updateNinthMachine(x.id), 1, 'ninth10 hit'); equal(b.byte603, 15, 'fifth duration16'); equal(b.byte613, 0, 'ninth duration1');
    x.actual.statusWord5bc = 0; x.actual.inputEdge5d4 = 0;
    equal(x.runtime.updateFifthMachine(x.id), 1, 'fifth nohit tail persists'); equal(x.runtime.updateNinthMachine(x.id), 0, 'ninth pulse ended');
    equal(x.actual.inputEdge5d4, 1, 'only fifth tail contributes'); x.actual.statusWord5bc = 0x10;
    for (const control of [0, 0x40, 0]) {x.actual.controlWord = control;
      equal(x.runtime.updateNinthMachine(x.id), 1, 'live control transitions never gate ninth10');}
    b.byte610 = 1; b.byte611 = 3; b.byte612 = 0;
    equal(x.runtime.updateNinthMachine(x.id), 0, 'retained ninth phase1 any-bit hit stays wrapper0');
    equal(b.byte611, 0, 'phase1 reload0'); equal(b.byte612, 1, 'phase1 index increments'); equal(b.byte610, 1, 'mode1 leaves phase1');
  }
  for (const key of ['byte610', 'byte611', 'byte612', 'byte613'] as const) {
    const x = fixture(true, true, true, true, true, true, true, true, true); delete x.initial[key]; x.bind();
    rejects(() => x.runtime.updateNinthMachine(x.id), key); equal(x.binding().byte60d, 79, 'missing ninth never replays eighth');
    const y = fixture(true, true, true, true, true, true, true, true, true); Object.defineProperty(y.actual, key, {value: undefined}); rejects(y.bind, 'competing');
    const z = fixture(false, true, true, true, true, true, true, true, true); Object.defineProperty(z.actual, key, {value: undefined}); rejects(z.run, 'competing');
  }
  {
    const x = fixture(false, true, true, true, true, true, true, true); check(!x.runtime.hasNinthMachine(), 'ninth absent');
    rejects(() => x.runtime.updateNinthMachine(x.id), '800686b8'); x.tables.descriptor3958 = x.ninth;
    rejects(() => x.runtime.updateNinthMachine(x.id), '800686b8');
    const y = fixture(false, true, true, true, true, true, true, true, true); y.tables.descriptor3958 = [...y.ninth];
    rejects(() => y.runtime.updateNinthMachine(y.id), 'owner changed'); equal(y.binding().byte612, 87, 'replacement fails before ninth stores');
  }
  for (const key of ['dispatch3988', 'descriptor38f8', 'descriptor3904', 'descriptor3910', 'descriptor391c', 'descriptor3928', 'descriptor3934', 'descriptor3940', 'descriptor394c'] as const) {
    const x = fixture(true, true, true, true, true, true, true, true, true); x.tables.descriptor3958 = x.tables[key]!;
    rejects(() => createSourceActorInputMachineRuntime({world: x.world, tables: x.tables}), 'owner alias');
  }
  {
    const x = fixture(true, true, true, true, true, true, true, true, true); Object.defineProperty(x.tables, 'descriptor3958', {value: undefined});
    rejects(() => createSourceActorInputMachineRuntime({world: x.world, tables: x.tables}), 'cannot be undefined');
    const y = fixture(true, true, true, true, true, true, true, true, true); Object.defineProperty(y.tables, 'descriptor3958', {get() {throw Error('getter must not run');}});
    rejects(() => createSourceActorInputMachineRuntime({world: y.world, tables: y.tables}), 'own data property');
    const z = fixture(false, true, true, true, true, true, true, true, true);
    z.hooks.actual = () => {try {z.runtime.updateNinthMachine(z.id);} catch {} return z.actual;};
    rejects(z.run, 'caught same-runtime'); equal(z.binding().byte612, 87, 'cross-machine reentry before ninth effects');
  }
  {
    const x = fixture(false, true, true, true, true, true, true, true, true); x.actual.statusWord5bc = 0x10; delete x.ninth[3];
    rejects(() => x.runtime.updateNinthMachine(x.id), 'own data property');
    equal(x.binding().byte610, 0, 'ninth phase clear before missing duration'); equal(x.binding().byte611, 126, 'ninth timer retained');
    const y = fixture(false, true, true, true, true, true, true, true, true); y.binding().byte610 = 2; y.binding().byte612 = 2; y.ninth.push(0x10);
    rejects(() => y.runtime.updateNinthMachine(y.id), 'outside explicit12-byte'); equal(y.binding().byte611, 88, 'ninth bound after timer/input');
    const z = fixture(false, true, true, true, true, true, true, true, true); z.actual.statusWord5bc = 0x10;
    Object.defineProperty(z.actual, 'inputEdge5d4', {writable: false});
    rejects(() => z.runtime.updateNinthMachine(z.id), 'non-writable'); equal(z.binding().byte613, 0, 'ninth tail consumed before failed edge store');
  }
  for (const control of [0, 0x40]) for (let low = 0; low <= 0x7f; low++) for (let raw = 0; raw <= 0xf00; raw += 0x100) {
    const x = fixture(false, true, true, true, true, true, true, true, true, true), b = x.binding();
    x.actual.controlWord = control; x.actual.statusWord5bc = raw | low; x.actual.inputEdge5d4 = 0x80000000;
    x.run(); x.runtime.updateSecondMachine(x.id); x.runtime.updateThirdMachine(x.id);
    x.runtime.updateFourthMachine(x.id); x.runtime.updateFifthMachine(x.id); x.runtime.updateSixthMachine(x.id);
    x.runtime.updateSeventhMachine(x.id); x.runtime.updateEighthMachine(x.id); x.runtime.updateNinthMachine(x.id);
    const hit = (low & 0xf) !== 0;
    equal(x.runtime.updateTenthMachine(x.id), hit ? 1 : 0, 'tenth ANY low-nibble bit from canonical input, independently of prior inputs');
    equal(x.actual.inputEdge5d4, (0x80000000 | (raw & 0x200 ? 0x60 : 0) | (raw & 0x400 ? 0x80 : 0) |
      (raw & 0x800 ? 0x200 : 0) | (raw & 0x100 ? 1 : 0) | (control && (raw & 0x100) ? 2 : 0) |
      (low & 0x20 ? 4 : 0) | (low & 0x40 ? 8 : 0) | (low & 0x10 ? 0x10 : 0) | (hit ? 0x2000 : 0)) >>> 0,
      'ten independent outputs retain earlier ORs and separate low-nibble input from fixed output2000');
    equal(b.byte628, hit ? 0 : 2, 'tenth phase628'); equal(b.byte629, 126, 'tenth timer629');
    equal(b.byte62a, 0, 'tenth index62a'); equal(b.byte62b, 0, 'tenth duration1 consumed');
    equal(b.byte610, low & 0x10 ? 0 : 2, 'tenth state does not alias ninth or noncontiguous first614');
    equal(b.byte603, raw & 0x100 ? 15 : 0, 'tenth leaves fifth long tail');
    check(x.runtime.hasTenthMachine() && x.runtime.getTables().descriptor3964 === x.tenth, 'tenth explicit retained owner');
  }
  for (const control of [0, 0x40]) for (const phase of [1, 2]) for (let byte = 0; byte < 256; byte++) {
    const x = fixture(false, true, true, true, true, true, true, true, true, true), b = x.binding();
    x.actual.controlWord = control; x.actual.inputEdge5d4 = 0x800002ff;
    b.byte628 = phase; b.byte629 = byte; b.byte62a = 0; b.byte62b = byte;
    equal(x.runtime.updateTenthMachine(x.id), byte ? 1 : 0, 'tenth unsigned tail survives no-hit or timer expiry');
    equal(b.byte629, (byte - 1) & 255, 'tenth raw timer'); equal(b.byte628, byte >= 2 && byte <= 128 ? phase : 0, 'tenth signed timer');
    equal(b.byte62b, byte ? byte - 1 : 0, 'tenth tail decrement');
    equal(x.actual.inputEdge5d4, byte ? 0x800022ff : 0x800002ff, 'tenth OR2000 starts clear and preserves earlier bits');
    equal(b.byte611, 89, 'tenth leaves ninth timer'); equal(b.byte617, 0, 'tenth leaves first tail');
  }
  for (let raw = 0; raw < 16; raw++) {
    const x = fixture(false, true, true, true, true, true, true, true, true, true), a = x.actual;
    a.statusWord5bc = raw; a.inputHeld5d8 = raw ? 0 : 0xf;
    Object.defineProperty(a, 'controlWord', {get() {throw Error('control getter must not run');}});
    Object.defineProperty(a, 'statusWord5b4', {get() {throw Error('status getter must not run');}});
    equal(x.runtime.updateTenthMachine(x.id), raw ? 1 : 0, 'tenth flags10 ANY needs neither control nor status5b4');
  }
  for (const phase of [1, 2]) for (const raw of [0, 1, 8, 0xf, 0xffffffff]) {
    const x = fixture(false, true, true, true, true, true, true, true, true, true), b = x.binding();
    b.byte628 = phase; b.byte629 = 7; b.byte62a = 1; x.actual.statusWord5bc = raw;
    equal(x.runtime.updateTenthMachine(x.id), 0, 'tenth index1 zero mask never matches phase1 or phase2 ANY');
    equal(b.byte628, phase, 'zero mask retains phase'); equal(b.byte629, 6, 'zero mask still decrements timer');
    equal(b.byte62a, 1, 'zero mask retains index'); equal(b.byte62b, 0, 'zero mask emits no tail');
  }
  {
    const x = fixture(false, true, true, true, true, true, true, true, true, true);
    x.tenth[4] = 0x30; x.actual.statusWord5bc = 0x10; x.actual.inputEdge5d4 = 0x800002ff;
    equal(x.runtime.updateTenthMachine(x.id), 1, 'retained multi-bit input mask uses ANY rather than canonical hardcoded0xf');
    equal(x.actual.inputEdge5d4, 0x800022ff, 'caller output remains2000 rather than retained input mask');
    x.tenth[1] = 0; x.actual.inputEdge5d4 = 0;
    equal(x.runtime.updateTenthMachine(x.id), 0, 'retained flag mutation switches to ALL and partial mask no longer matches');
    x.actual.statusWord5bc = 0x30; equal(x.runtime.updateTenthMachine(x.id), 1, 'ALL requires both retained mask bits');
    x.actual.statusWord5bc = 1; x.actual.inputEdge5d4 = 0;
    equal(x.runtime.updateTenthMachine(x.id), 0, 'canonical low-nibble input cannot replace changed descriptor mask');
  }
  for (const fault of ['input', 'index', 'mask'] as const) for (const control of [0, 0x40]) {
    const x = fixture(false, true, true, true, true, true, true, true, true, true), b = x.binding();
    b.byte628 = 2; b.byte629 = 2; b.byte62a = 0; x.actual.controlWord = control; x.actual.inputEdge5d4 = 0x800002ff;
    if (fault === 'input') delete (x.actual as Partial<typeof x.actual>).statusWord5bc;
    else if (fault === 'index') b.byte62a = 255; else delete x.tenth[4];
    rejects(() => x.runtime.updateTenthMachine(x.id), fault === 'input' ? 'statusWord5bc' : fault === 'index' ? 'outside explicit12-byte' : 'own data property');
    equal(b.byte629, 1, 'tenth timer precedes reached input/index/mask failure');
    equal(x.actual.inputEdge5d4, 0x800002ff, 'failed reads do not invent output2000');
  }
  {
    const x = fixture(false, true, true, true, true, true, true, true, true, true), b = x.binding();
    b.byte628 = 2; b.byte629 = 1; b.byte62a = 255; b.byte62b = 2; x.actual.inputEdge5d4 = 0x800002ff;
    delete (x.actual as Partial<typeof x.actual>).statusWord5bc; x.tenth.length = 0;
    equal(x.runtime.updateTenthMachine(x.id), 1, 'expired tenth skips all descriptor/input reads but reaches existing tail');
    equal(b.byte628, 0, 'expired tenth phase clear'); equal(b.byte62b, 1, 'expired tenth tail consumed');
    equal(x.actual.inputEdge5d4, 0x800022ff, 'expired tenth emits2000 from retained tail');
  }
  {
    const x = fixture(false, true, true, true, true, true, true, true, true, true), b = x.binding();
    x.actual.statusWord5bc = 0x17f; x.actual.controlWord = 0x40;
    equal(x.runtime.updateFifthMachine(x.id), 1, 'fifth100 hit'); equal(x.runtime.updateSixthMachine(x.id), 1, 'sixth gated100 hit');
    equal(x.runtime.updateSeventhMachine(x.id), 1, 'seventh20 hit'); equal(x.runtime.updateEighthMachine(x.id), 1, 'eighth40 hit');
    equal(x.runtime.updateNinthMachine(x.id), 1, 'ninth10 hit'); equal(x.runtime.updateTenthMachine(x.id), 1, 'tenth low-nibble ANY hit');
    equal(b.byte603, 15, 'fifth duration16'); equal(b.byte62b, 0, 'tenth duration1');
    x.actual.statusWord5bc = 0; x.actual.inputEdge5d4 = 0;
    equal(x.runtime.updateFifthMachine(x.id), 1, 'fifth nohit tail persists'); equal(x.runtime.updateTenthMachine(x.id), 0, 'tenth pulse ended');
    equal(x.actual.inputEdge5d4, 1, 'only fifth tail contributes'); x.actual.statusWord5bc = 2;
    for (const control of [0, 0x40, 0]) {x.actual.controlWord = control;
      equal(x.runtime.updateTenthMachine(x.id), 1, 'control transitions do not gate tenth low nibble');}
    b.byte628 = 1; b.byte629 = 3; b.byte62a = 0;
    equal(x.runtime.updateTenthMachine(x.id), 0, 'retained tenth phase1 any-bit hit stays wrapper0');
    equal(b.byte629, 0, 'phase1 reload0'); equal(b.byte62a, 1, 'phase1 index increments'); equal(b.byte628, 1, 'mode1 leaves phase1');
  }
  for (const key of ['byte628', 'byte629', 'byte62a', 'byte62b'] as const) {
    const x = fixture(true, true, true, true, true, true, true, true, true, true); delete x.initial[key]; x.bind();
    rejects(() => x.runtime.updateTenthMachine(x.id), key); equal(x.binding().byte611, 89, 'missing tenth does not replay ninth');
    const y = fixture(true, true, true, true, true, true, true, true, true, true); Object.defineProperty(y.actual, key, {value: undefined}); rejects(y.bind, 'competing');
    const z = fixture(false, true, true, true, true, true, true, true, true, true); Object.defineProperty(z.actual, key, {value: undefined}); rejects(z.run, 'competing');
  }
  {
    const x = fixture(false, true, true, true, true, true, true, true, true); check(!x.runtime.hasTenthMachine(), 'tenth absent');
    rejects(() => x.runtime.updateTenthMachine(x.id), '800686d0'); x.tables.descriptor3964 = x.tenth;
    rejects(() => x.runtime.updateTenthMachine(x.id), '800686d0');
    const y = fixture(false, true, true, true, true, true, true, true, true, true); y.tables.descriptor3964 = [...y.tenth];
    rejects(() => y.runtime.updateTenthMachine(y.id), 'owner changed'); equal(y.binding().byte62a, 97, 'replacement precedes tenth stores');
  }
  for (const key of ['dispatch3988', 'descriptor38f8', 'descriptor3904', 'descriptor3910', 'descriptor391c', 'descriptor3928', 'descriptor3934', 'descriptor3940', 'descriptor394c', 'descriptor3958'] as const) {
    const x = fixture(true, true, true, true, true, true, true, true, true, true); x.tables.descriptor3964 = x.tables[key]!;
    rejects(() => createSourceActorInputMachineRuntime({world: x.world, tables: x.tables}), 'owner alias');
  }
  {
    const x = fixture(true, true, true, true, true, true, true, true, true, true); Object.defineProperty(x.tables, 'descriptor3964', {value: undefined});
    rejects(() => createSourceActorInputMachineRuntime({world: x.world, tables: x.tables}), 'cannot be undefined');
    const y = fixture(true, true, true, true, true, true, true, true, true, true); Object.defineProperty(y.tables, 'descriptor3964', {get() {throw Error('getter must not run');}});
    rejects(() => createSourceActorInputMachineRuntime({world: y.world, tables: y.tables}), 'own data property');
    const z = fixture(false, true, true, true, true, true, true, true, true, true);
    z.hooks.actual = () => {try {z.runtime.updateTenthMachine(z.id);} catch {} return z.actual;};
    rejects(z.run, 'caught same-runtime'); equal(z.binding().byte62a, 97, 'cross-machine reentry before tenth effects');
  }
  {
    const x = fixture(false, true, true, true, true, true, true, true, true, true); x.actual.statusWord5bc = 1; delete x.tenth[3];
    rejects(() => x.runtime.updateTenthMachine(x.id), 'own data property');
    equal(x.binding().byte628, 0, 'tenth phase clear before missing duration'); equal(x.binding().byte629, 126, 'tenth timer retained');
    const y = fixture(false, true, true, true, true, true, true, true, true, true); y.binding().byte628 = 2; y.binding().byte62a = 2; y.tenth.push(0xf);
    rejects(() => y.runtime.updateTenthMachine(y.id), 'outside explicit12-byte'); equal(y.binding().byte629, 98, 'tenth bound after timer/input');
    const z = fixture(false, true, true, true, true, true, true, true, true, true); z.actual.statusWord5bc = 1;
    Object.defineProperty(z.actual, 'inputEdge5d4', {writable: false});
    rejects(() => z.runtime.updateTenthMachine(z.id), 'non-writable'); equal(z.binding().byte62b, 0, 'tenth tail consumed before failed edge store');
  }
  console.log('[actor-input-machine] PASS: genuine three-handler dispatch, first/optional second/third/fourth/fifth/sixth/seventh/eighth/ninth/tenth distinct descriptors and states, signed timers, any/all masks, retained stores, shared tables/exclusive actors and bounded GQR4 loads; charge/full tick remain unsupported');
}
