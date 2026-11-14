import {createSourceActorInputChargeRuntime, isSourceActorInputChargeRuntime,
  type SourceActorInputChargeBinding, type SourceActorInputChargeData, type SourceActorInputChargeGlobal,
  type SourceActorInputChargeSources} from './actor-input-charge.js';
import {createRomActor} from './actor.js';
import {fusedMultiplyAddSourceFloat32} from './source-float.js';
function check(ok: boolean, why: string): void {if (!ok) throw Error(`[actor-input-charge-test] ${why}`);}
function equal(a: unknown, b: unknown, why: string): void {check(Object.is(a, b), `${why}: got${String(a)}, expected${String(b)}`);}
function rejects(run: () => unknown, fragment: string): void {
  let error = ''; try {run();} catch (e) {error = String(e);}
  check(error.includes(fragment), `expected${fragment}, got${error || 'success'}`);
}
const warmups = ['field63c','field640','field644'] as const, banks = ['field648','field64c','field650'] as const;
const thresholds = ['field184','field188','field18c'] as const;
function fixture(defer = false) {
  const id = Symbol('charge actor'), descriptorId = Symbol('descriptor4b0'), parameterId = Symbol('parameter4ac');
  const actual = createRomActor(); actual.aimRateScale = 1; actual.controlWord = 0;
  actual.statusWord5b4 = 0; actual.inputEdge5d4 = 0x80000001;
  const status = {byte6fc: 0}, mapping = {descriptor4b0: descriptorId}, attribute = {parameter4ac: parameterId};
  const descriptor = Array<number>(0x32).fill(255), parameter = {field184: 100, field188: 200, field18c: 300};
  const global: SourceActorInputChargeGlobal = {byte1829: 0};
  const held = [0x200,0x200,0x400], release = [0x400,0x800,0x1000];
  const data: SourceActorInputChargeData = {float80437628: 10, float8043762c: 0,
    float80437630: 1, float80437634: 2, held3970: held, release397c: release};
  const hooks: Partial<Record<'world'|'worldMapping'|'statusActor'|'statusMapping'|'statusAttribute'|'status'|'mapping'|'descriptor'|'attributeActor'|'attribute'|'parameter', () => unknown>> = {};
  const sources: SourceActorInputChargeSources = {
    world: {
      getActualActor(key) {check(key === id, 'world actor id'); return (hooks.world ? hooks.world() : actual) as typeof actual;},
      getMappingActor(key) {check(key === id, 'world mapping id'); return (hooks.worldMapping ? hooks.worldMapping() : mapping) as object;},
    },
    status: {
      getMappingActor(key: symbol) {check(key === id, 'status mapping id'); return (hooks.statusMapping ? hooks.statusMapping() : mapping) as object;},
      getAttributeBinding(key: symbol) {check(key === id, 'status attribute id'); return (hooks.statusAttribute ? hooks.statusAttribute() : attribute) as object;},
      getActualActor(key) {check(key === id, 'status actor id'); return (hooks.statusActor ? hooks.statusActor() : actual) as typeof actual;},
      getActorBinding(key) {check(key === id, 'status binding id'); return (hooks.status ? hooks.status() : status) as typeof status;},
    },
    mapping: {
      getActor(key) {check(key === id, 'mapping actor id'); return (hooks.mapping ? hooks.mapping() : mapping) as ReturnType<SourceActorInputChargeSources['mapping']['getActor']>;},
      getDescriptor(key) {check(key === descriptorId, 'descriptor id'); return (hooks.descriptor ? hooks.descriptor() : descriptor) as number[];},
    },
    attributes: {
      getActualActor(key) {check(key === id, 'attribute actor id'); return (hooks.attributeActor ? hooks.attributeActor() : actual) as typeof actual;},
      getActorBinding(key) {check(key === id, 'attribute binding id'); return (hooks.attribute ? hooks.attribute() : attribute) as typeof attribute;},
      getParameterDescriptor(key) {check(key === parameterId, 'parameter id'); return (hooks.parameter ? hooks.parameter() : parameter) as typeof parameter;},
    }, global, data,
  };
  const initial: Partial<SourceActorInputChargeBinding> = {byte58e:0, field63c:4,field640:5,field644:6,
    field648:20,field64c:30,field650:40,byte654:255,byte655:0};
  const runtime = createSourceActorInputChargeRuntime(sources), bind = () => runtime.bindActor(id, initial);
  if (!defer) bind();
  return {id, actual,status,mapping,attribute,descriptor,parameter,global,data,held,release,hooks,sources,initial,runtime,bind,
    binding: () => runtime.getActorBinding(id), run: () => runtime.updateActor(id),
    enable(slot: number) {descriptor[0x2f+slot] = 0;}};
}
export function runActorInputChargeSelfTests(): void {
  {
    const x = fixture(); check(isSourceActorInputChargeRuntime(x.runtime) && !isSourceActorInputChargeRuntime({...x.runtime}), 'genuine runtime brand');
    check(Object.isSealed(x.binding()) && x.binding() !== x.initial, 'explicit copied sealed state');
    check(x.runtime.getActualActor(x.id) === x.actual && x.runtime.getStatusBinding(x.id) === x.status &&
      x.runtime.getMappingActor(x.id) === x.mapping && x.runtime.getAttributeBinding(x.id) === x.attribute &&
      x.runtime.getGlobal() === x.global && x.runtime.getData() === x.data, 'all canonical owners retained');
    equal(x.run(), undefined, 'all descriptors disabled genuinely returns'); equal(x.binding().byte654,255,'disabled slots untouched');
  }
  for (const gate of [1,127,128,255]) {
    const x = fixture(true); x.global.byte1829=gate;
    for (const key of Object.keys(x.initial)) delete x.initial[key as keyof SourceActorInputChargeBinding];
    delete (x.actual as Partial<typeof x.actual>).aimRateScale; delete (x.status as Partial<typeof x.status>).byte6fc;
    x.mapping.descriptor4b0 = Symbol('unresolved'); x.bind();
    equal(x.run(),undefined,'signed nonzero global skips all charge state'); equal(Object.keys(x.binding()).length,0,'global skip never hydrates');
  }
  {
    const x=fixture(true); delete (x.status as Partial<typeof x.status>).byte6fc;
    delete (x.actual as Partial<typeof x.actual>).aimRateScale; x.bind(); rejects(x.run,'byte6fc');
    const y=fixture(); delete (y.actual as Partial<typeof y.actual>).aimRateScale; rejects(y.run,'aimRateScale'); equal(y.binding().byte655,0,'rate before ready clear');
    const z=fixture(); z.status.byte6fc=1; delete z.data.float80437628; z.binding().byte655=8;
    rejects(z.run,'float80437628'); equal(z.binding().byte655,8,'burst constant before ready clear');
  }
  for (let slot=0;slot<3;slot++) {
    const x=fixture(); x.enable(slot); x.actual.controlWord=3; x.actual.prevActionIndex=slot+3;
    x.binding().byte58e=NaN; x.binding()[warmups[slot]!]=NaN; x.binding()[banks[slot]!]=NaN;
    delete x.data.held3970; x.run(); equal(x.binding()[warmups[slot]!],0,'matching584 reset warmup');
    equal(x.binding()[banks[slot]!],0,'matching584 reset bank'); equal(x.binding().byte654,255 & ~(1<<slot),'reset clears only selected654bit');
    const y=fixture(); y.enable(slot); y.binding().byte58e=1<<(slot+3);
    delete (y.actual as Partial<typeof y.actual>).prevActionIndex; delete (y.actual as Partial<typeof y.actual>).statusWord5b4;
    y.run(); equal(y.binding()[warmups[slot]!],0,'58e reset'); equal(y.binding()[banks[slot]!],0,'58e reset bank');
    const z=fixture(); z.enable(slot); z.actual.controlWord=1; z.actual.prevActionIndex=255;
    z.binding().byte58e=1<<(slot+3); z.run(); equal(z.binding()[banks[slot]!],0,'signed584 mismatch falls through58e');
  }
  {
    const x=fixture(true); x.enable(0); x.actual.controlWord=1; x.actual.prevActionIndex=3;
    delete x.initial.byte654; x.bind(); rejects(x.run,'byte654'); equal(x.binding().field63c,0,'reset warmup retained before654 read'); equal(x.binding().field648,0,'reset bank retained before654 read');
    const y=fixture(); y.enable(0); y.binding().byte58e=8; Object.defineProperty(y.binding(),'field648',{writable:false});
    rejects(y.run,'non-writable'); equal(y.binding().field63c,0,'reset warmup before readonly bank'); equal(y.binding().byte654,255,'readonly bank before654');
  }
  for (let slot=0;slot<3;slot++) for (const level of [-5,0,9,9.5]) {
    const x=fixture();x.enable(slot);x.actual.statusWord5b4=x.held[slot]!; x.binding()[warmups[slot]!]=level;
    delete (x.attribute as Partial<typeof x.attribute>).parameter4ac; x.binding().byte654=NaN;
    const oldBank=x.binding()[banks[slot]!]!;x.run();
    equal(x.binding()[warmups[slot]!],Math.min(level+1,10),'warmup adds unscaled1 then clamps strictly greater');
    equal(x.binding()[banks[slot]!],level===9.5?oldBank+0.5:oldBank,'warmup excess only when strictly greater');
  }
  {
    const x=fixture(true);x.enable(0);x.actual.statusWord5b4=0x200;x.initial.field63c=9;delete x.initial.field648;delete x.initial.byte654;
    x.bind();x.run();equal(x.binding().field63c,10,'exact10 needs neither bank nor654');
    const y=fixture();y.enable(0);y.actual.statusWord5b4=0x200;y.binding().field63c=9.5;Object.defineProperty(y.binding(),'field648',{writable:false});
    rejects(y.run,'non-writable');equal(y.binding().field63c,10.5,'excess bank failure retains overshoot before finalwarmup10');
  }
  for (let slot=0;slot<3;slot++) for (const burst of [0,1,255]) {
    const x=fixture();x.enable(slot);x.actual.statusWord5b4=x.held[slot]!;x.binding()[warmups[slot]!]=10;
    x.status.byte6fc=burst;x.actual.aimRateScale=0.5;delete (x.attribute as Partial<typeof x.attribute>).parameter4ac;
    const before=x.binding()[banks[slot]!]!;x.binding().byte654=0;
    rejects(x.run,'80068838');equal(x.binding()[banks[slot]!],before+(burst?5:0.5),'mature bank adds retained burst rate');
    equal(x.binding().byte654,1<<slot,'mature654 OR retained before unsupported effect');equal(x.binding().byte655,0,'no fake ready clamp after unsupported effect');
    equal(x.binding()[warmups[slot]!],10,'mature does not touch warmup');
  }
  {
    const x=fixture();x.enable(0);x.enable(1);x.actual.statusWord5b4=0x200;x.binding().field63c=10;
    x.binding().field640=NaN;rejects(x.run,'80068838');equal(x.binding().field640,NaN,'mature stops before later slot');
    const y=fixture(true);y.enable(0);y.actual.statusWord5b4=0x200;y.initial.field63c=10;delete y.initial.byte654;y.bind();
    rejects(y.run,'byte654');equal(y.binding().field648,21,'mature bank retained before missing654');
  }
  for (let slot=0;slot<3;slot++) for (const atThreshold of [false,true]) {
    const x=fixture();x.enable(slot);const old=atThreshold?x.parameter[thresholds[slot]!]:20;
    x.binding()[banks[slot]!]=old;x.status.byte6fc=255;x.actual.aimRateScale=1.5;
    x.run();equal(x.binding()[banks[slot]!],old-3,'release uses fresh unscaled768');equal(x.binding()[warmups[slot]!],0,'release clearswarmup');
    equal(x.binding().byte654,255 & ~(1<<slot),'release clears654');
    equal(x.actual.inputEdge5d4,atThreshold?(0x80000001|x.release[slot]!)>>>0:0x80000001,'release edge only atthreshold');
  }
  {
    const x=fixture();for(let slot=0;slot<3;slot++){x.enable(slot);x.binding()[banks[slot]!]=x.parameter[thresholds[slot]!];}
    x.run();equal(x.actual.inputEdge5d4,0x80001c01,'sequential slot release OR preserves priorbits');equal(x.binding().byte654,248,'all three bits cleared');
    const y=fixture();y.enable(0);y.binding().field648=100;delete y.data.float80437634;
    rejects(y.run,'float80437634');equal(y.actual.inputEdge5d4,0x80000401,'edge precedes releaseconstant2');equal(y.binding().field63c,4,'constant2 load precedes warmupstore');
    const z=fixture();z.enable(0);z.binding().field648=100;Object.defineProperty(z.binding(),'field63c',{writable:false});
    rejects(z.run,'non-writable');equal(z.actual.inputEdge5d4,0x80000401,'release edge retained before warmupwrite failure');equal(z.binding().field648,100,'bank unchanged before warmupwrite');
  }
  {
    const x=fixture(true);x.enable(0);delete x.initial.field648;delete (x.parameter as Partial<typeof x.parameter>).field184;
    x.bind();rejects(x.run,'field648');equal(x.binding().field63c,4,'bank load before threshold');
    const y=fixture();y.enable(0);y.binding().field648=100;delete (y.actual as Partial<typeof y.actual>).inputEdge5d4;delete y.release[0];
    rejects(y.run,'inputEdge5d4');equal(y.binding().field63c,4,'edge load before release table');
    const z=fixture();z.enable(0);z.binding().field648=20;delete z.data.release397c;z.run();equal(z.binding().field648,18,'below threshold never reads release table');
  }
  // Stop after fnmsubs store and before clamp to observe exact-zero sign.
  for (const [rate,bank,expected] of [[1,2,-0],[0,0,-0],[-0,0,0],[-0,-0,-0]] as const) {
    const x=fixture();x.enable(0);x.actual.aimRateScale=rate;x.binding().field648=bank;
    Object.defineProperty(x.binding(),'byte654',{writable:false});rejects(x.run,'non-writable');
    equal(x.binding().field648,expected,'fnmsubs negation after single rounding preserves zero sign');
  }
  {
    const x=fixture();x.enable(0);x.binding().field648=2;x.run();equal(x.binding().field648,0,'final <=+0 clamp canonicalizes negativezero');
    const y=fixture();y.enable(0);y.actual.aimRateScale=2**127;y.binding().field648=(2-2**-23)*2**127;
    Object.defineProperty(y.binding(),'byte654',{writable:false});rejects(y.run,'non-writable');
    equal(y.binding().field648,-(2**104),'fused finite cancellation avoids separate multiply overflow');
    check(!Number.isFinite(Math.fround(2*y.actual.aimRateScale)),'separate multiply witness overflows');
    equal(-fusedMultiplyAddSourceFloat32(2,1,-2),-0,'exact fusedzero witness');
  }
  for (const bank of [-5,-0,0,1,2,3]) {
    const x=fixture();x.enable(0);x.binding().field648=bank;x.run();equal(x.binding().field648,Math.max(0,bank-2),'release clampsnonpositive only');
  }
  {
    const x=fixture();x.binding().byte655=128;rejects(x.run,'80068960');equal(x.binding().byte655,0,'old signednonzero readyclear retained');
    const y=fixture();Object.defineProperty(y.binding(),'byte655',{writable:false});rejects(y.run,'non-writable');equal(y.binding().field63c,4,'readyclear before slots');
  }
  for (const key of ['world','worldMapping','statusActor','statusMapping','statusAttribute','attributeActor','status','mapping','attribute'] as const) {
    const x=fixture();x.enable(0);x.hooks[key]=()=>({});rejects(x.run,'owner changed');
  }
  {
    const x=fixture();x.enable(0);x.run();x.hooks.descriptor=()=>[...x.descriptor];rejects(x.run,'owner changed');
    const y=fixture();y.enable(0);y.run();y.hooks.parameter=()=>({...y.parameter});rejects(y.run,'owner changed');
    const z=fixture();z.enable(0);z.data.held3970=[...z.held];rejects(z.run,'owner changed');
    const r=fixture();r.hooks.world=()=>{try{r.run();}catch{}return r.actual;};rejects(r.run,'caught same-runtime');
    const duplicate=createSourceActorInputChargeRuntime(x.sources);rejects(()=>duplicate.bindActor(x.id,{}),'already claimed');
    const fake=fixture(true);fake.hooks.worldMapping=()=>({});rejects(fake.bind,'owner changed');
  }
  for (const key of ['field63c','byte58e','byte6fc','sourceAmmoRefillRate']) {
    const x=fixture(true);Object.defineProperty(x.actual,key,{value:undefined});rejects(x.bind,'competing');
    const y=fixture();Object.defineProperty(y.actual,key,{value:undefined});rejects(y.run,'competing');
  }
  {
    const x=fixture();x.enable(0);Object.defineProperty(x.actual,'statusWord5b4',{get(){throw Error('getter invoked');}});
    rejects(x.run,'own data property');
    const y=fixture();y.enable(0);y.actual.aimRateScale=0.1;rejects(y.run,'float32');
    const z=fixture();z.enable(0);z.hooks.descriptor=()=>z.held;rejects(z.run,'aliases');
  }
  {
    const x=fixture(); x.global.byte1829=1; x.data.float80437628=NaN; x.data.float8043762c=-0;
    x.run();equal(x.binding().field63c,4,'global skip does not validate any constant');
    const y=fixture(); y.data.float80437628=NaN;y.data.float8043762c=-0;y.data.float80437630=NaN;y.data.float80437634=NaN;
    y.run();equal(y.binding().field63c,4,'disabled slots withzero6fc need no constants');
    const z=fixture();z.enable(0);z.binding().byte58e=8;z.data.float8043762c=-0;
    rejects(z.run,'authenticated');equal(z.binding().field63c,4,'reset rejects negativezero before store');
    const r=fixture();r.enable(0);r.actual.statusWord5b4=0x200;r.data.float80437628=11;
    r.binding().field63c=NaN;rejects(r.run,'field63c');
    r.binding().field63c=4;rejects(r.run,'authenticated');equal(r.binding().field63c,4,'warmup source before constant validation');
    const q=fixture();q.enable(0);q.data.float80437634=3;q.binding().field648=100;
    rejects(q.run,'authenticated');equal(q.actual.inputEdge5d4,0x80000401,'release threshold edge before invalid2');
    equal(q.binding().field63c,4,'invalid2 precedes warmupstore');
  }
  {
    const x=fixture();x.sources.global={byte1829:0};rejects(x.run,'global owner changed');
    const y=fixture();y.sources.data={...y.data};rejects(y.run,'data owner changed');
    const z=fixture();z.enable(0);z.held[0]=0x100;z.actual.statusWord5b4=0x100;
    z.run();equal(z.binding().field63c,5,'selected held table word is live data');
    const r=fixture();r.enable(0);r.binding().field648=100;r.release[0]=0x20000;
    r.run();equal(r.actual.inputEdge5d4,0x80020001,'selected release table word is live data');
    const q=fixture();q.enable(0);q.global.byte1829=NaN;rejects(q.run,'integer out of bounds');
    equal(q.binding().field63c,4,'malformed global before all charge stores');
  }
  {
    const x=fixture();x.enable(0);x.hooks.descriptor=()=>Promise.resolve(x.descriptor);rejects(x.run,'synchronous');
    const y=fixture();y.enable(0);Object.defineProperty(y.parameter,'field184',{value:100,writable:false});
    Object.defineProperty(y.actual,'aimRateScale',{value:1,writable:false});y.run();equal(y.binding().field648,18,'readonly source values allowed');
    const z=fixture();z.enable(0);z.enable(1);let selected=0;
    z.hooks.descriptor=()=>{selected++;return z.descriptor;};z.run();equal(selected,3,'4b0 descriptor resolved separately inall three slots');
  }

  {
    const x=fixture();x.status.byte6fc=1;x.actual.aimRateScale=(2-2**-23)*2**127;x.binding().byte655=7;
    rejects(x.run,'fmuls rate result');equal(x.binding().byte655,7,'overflowing scaled rate precedes ready clear');
    const y=fixture();y.enable(0);y.actual.statusWord5b4=0x200;y.binding().field63c=10;
    y.actual.aimRateScale=(2-2**-23)*2**127;y.binding().field648=y.actual.aimRateScale;
    rejects(y.run,'overflow float32');equal(y.binding().field648,y.actual.aimRateScale,'mature arithmetic failure before bank store');
    equal(y.binding().byte654,255,'mature arithmetic failure before654store');
    const z=fixture();z.enable(0);delete z.descriptor[0x30];rejects(z.run,'own data property');
    equal(z.binding().field648,18,'slot0 release survives missing next descriptor byte');
    equal(z.binding().field63c,0,'slot0 warmup survives missing next descriptor byte');
  }
  {
    const x=fixture();rejects(()=>createSourceActorInputChargeRuntime({...x.sources,global:x.data as SourceActorInputChargeGlobal,data:x.data}),'owner alias');
    const y=fixture(true);y.hooks.attribute=()=>y.status;rejects(y.bind,'owner changed');
    const z=fixture();z.enable(0);z.hooks.parameter=()=>z.actual;rejects(z.run,'aliases');
  }

}
