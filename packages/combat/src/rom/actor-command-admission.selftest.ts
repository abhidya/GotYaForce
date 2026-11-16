import {createRomActor, type RomVisibilityTarget} from './actor.js';
import {createSourceActorInputChargeRuntime, type SourceActorInputChargeSources,
  type SourceActorInputChargeGlobal, type SourceActorInputChargeData} from './actor-input-charge.js';
import {createSourceStreamWaitRuntime} from './stream-wait.js';
import {createSourceActorActionRequestRuntime} from './actor-action-request.js';
import {createSourceActorCueResetRuntime} from './actor-cue-reset.js';
import {createSourceActorCommandAdmissionRuntime, isSourceActorCommandAdmissionRuntime,
  hasIncompleteSourceActorCommandAdmission, type SourceActorCommandAdmissionBinding,
  type SourceActorCommandAdmissionSources} from './actor-command-admission.js';
function check(ok: boolean, why: string): void {if (!ok) throw Error(`[actor-command-admission-test] ${why}`);}
function equal(actual: unknown, expected: unknown, why: string): void {
  check(Object.is(actual, expected), `${why}: got ${String(actual)}, expected ${String(expected)}`);
}
function rejects(run: () => unknown, fragment: string): void {
  let message = ''; try {run();} catch (error) {message = String(error);}
  check(message.includes(fragment), `expected ${fragment}, got ${message || 'success'}`);
}
function absent(owner: object, key: string): void {delete (owner as Record<string, unknown>)[key];}
function readonly(owner: object, key: string): void {Object.defineProperty(owner, key, {writable: false});}
function watch(run: () => void, observe: (owner: object, key: PropertyKey) => void): void {
  const original = Object.getOwnPropertyDescriptor;
  Object.getOwnPropertyDescriptor = ((owner: object, key: PropertyKey) => {
    observe(owner, key); return original(owner, key);
  }) as typeof original;
  try {run();} finally {Object.getOwnPropertyDescriptor = original;}
}
function fixture(options: {defer?: boolean; global?: SourceActorInputChargeGlobal; data?: SourceActorInputChargeData;
  gqr5?: number | null} = {}) {
  const actual = createRomActor(), id = Symbol('admission actor'), descriptorId = Symbol('descriptor');
  const extras = new Map<symbol, Record<string, object>>();
  const part = <T extends object>(selected: symbol, key: string, fallback: T): T => (extras.get(selected)?.[key] ?? fallback) as T;
  absent(actual, 'fbPhaseSlots'); absent(actual, 'shotByte1db3');
  Object.assign(actual, {cmdButton: 2, cmdSubtype: 0, cmdChargedRanged: 91, prevActionIndex: 71,
    actionIndex: 99, variantIndex: 98, controlWord: 0, stateTimer: 19,
    targetDistance760: 111, horizontalDistance764: 222, stateFlagA: 13, stateFlagB: 14,
    fbCue: 21, fbState: -12, prevFbState: -11, ubCue: 22, ubState: -14, prevUbState: -13, fbPhase: 8,
    heading: 0, visibilityBit: 4, onLand754: null});
  actual.aimOrigin518.x = 11; actual.aimOrigin518.y = 12; actual.aimOrigin518.z = 13;
  const cueTable = new Int8Array(512).fill(-1); cueTable[88] = 2; cueTable[89] = 6;
  cueTable[1] = 8; cueTable[13] = 9; actual.cueTable = cueTable;
  const row = new Array<number>(6 * 16).fill(255); row.splice(0, 4, 44, 3, 2, 0);
  const root = {records: [], sourceTables: [row, row, row, row, row, row]}; actual.commandTable = root;
  const targets: RomVisibilityTarget[] = Array.from({length: 6}, () => ({eligibility83: 0, controlWord: 0, visibilityMask5e6: 255}));
  actual.visibilityRoster = targets;
  const world = {mode4a0: 0, mode4a1: 0, yawOffset6b8: 0}, mapping = {descriptor4b0: descriptorId}, status = {};
  const attribute = {}, meta = {byte10: 0};
  const matrix = [1,0,0,3,0,1,0,17,0,0,1,4], raw8c = new Array<number>(0x40).fill(1);
  const unavailable = () => {throw Error('unreached stream dependency');};
  const streams = createSourceStreamWaitRuntime({
    mapping: {getActor(selected: symbol) {return part(selected,'mapping',mapping);}, getLayout: unavailable}, feedback: {getPart: unavailable},
    dispatch: {getPartBinding: unavailable, updatePart: unavailable, setupPart: unavailable},
    targets: {continueUnmetNonCountdownWait: unavailable, getStreamPart: unavailable},
  } as unknown as Parameters<typeof createSourceStreamWaitRuntime>[0]);
  streams.bindActor(id, {activeMask579:0,blockedMask1d9a:34,marker71d:0}, Array.from({length:4},()=>({
    group18:0,action19:0,status1d:0,current00:null,next04:null,wait14:0,finished1a:1,event1e:0})));
  streams.bindStartActor(id, {familyBank1d80:null,sharedBank1d84:null,defaultSelector582:0,marker709:33});
  const start = streams.getStartActorBinding(id), stream = streams.getActorBinding(id);
  const cells = Array.from({length: 3}, () => ({max: 0, refillType: 0}));
  const slots = cells.map(cell => ({cell}));
  const dispatch = {family1d88: Symbol(), shared1d8c: Symbol(), marker578: 1, marker1db3: 35};
  const initial: Partial<SourceActorCommandAdmissionBinding> = {pointer504: null, pointer508: null, pointerc8: {}, byteD0: 17};
  const global = options.global ?? {byte45: 5}, data = options.data ?? {
    float8043762c: 0, float80437678: 20000, float80437078: 0.0000958738019107841,
    flags3994: [58,4,56,4,56,0,56,0,56,0,56,0],
  };
  const hooks: {world?: () => unknown; matrix?: (index: number) => unknown; meta?: () => unknown; start?: () => unknown;
    stream?: () => unknown; slot?: (index: number) => unknown; actual?: () => unknown} = {};
  const worldSource: SourceActorCommandAdmissionSources['world'] = {
    getActualActor(selected) {check(this === worldSource, 'captured world receiver'); return (hooks.actual?.() ?? part(selected,'actual',actual)) as typeof actual;},
    getActorBinding(selected) {return (hooks.world?.() ?? part(selected,'world',world)) as ReturnType<SourceActorCommandAdmissionSources['world']['getActorBinding']>;},
    getMappingActor(selected) {return part(selected,'mapping',mapping);},
    getWorldMatrix(selected, index) {check(this === worldSource, 'captured matrix receiver');
      if (hooks.matrix) return hooks.matrix(index) as number[];
      if (index !== 0) throw Error('matrix index not owned'); return part(selected,'matrix',matrix);},
  };
  const statusSource: SourceActorCommandAdmissionSources['status'] = {
    getActualActor(selected) {return part(selected,'actual',actual);}, getActorBinding(selected) {return part(selected,'status',status);}, getWorldBinding(selected) {return part(selected,'world',world);},
    getMappingActor(selected) {return part(selected,'mapping',mapping);}, getAttributeBinding(selected) {return part(selected,'attribute',attribute);},
    getStartBinding(selected) {return streams.getStartActorBinding(selected);},
    getAmmoSlot(_id, index) {check(this === statusSource, 'captured ammo receiver');
      return (hooks.slot?.(index) ?? slots[index]) as ReturnType<SourceActorCommandAdmissionSources['status']['getAmmoSlot']>;},
  };
  const attributes: SourceActorCommandAdmissionSources['attributes'] = {getActualActor(selected) {return part(selected,'actual',actual);},
    getActorBinding(selected) {return part(selected,'attribute',attribute);}, getDescriptorBinding(selected) {check(selected === descriptorId, 'same descriptor identity');
      return hooks.meta?.() ?? meta;}};
  const chargeSources: SourceActorInputChargeSources = {world: worldSource, status: statusSource,
    mapping: {getActor(selected) {return part(selected,'mapping',mapping) as ReturnType<SourceActorInputChargeSources['mapping']['getActor']>;}, getDescriptor(selected) {
      check(selected === descriptorId, 'charge descriptor identity'); return raw8c;}},
    attributes: {...attributes, getParameterDescriptor() {throw Error('unreached parameter');}}, global, data};
  const charge = createSourceActorInputChargeRuntime(chargeSources);
  charge.bindActor(id, {byte58e: 41, field63c: 51, field640: 52, field644: 53, field648: 61, field64c: 62, field650: 63});
  const action = createSourceActorActionRequestRuntime({world: worldSource}); action.bindActor(id, {byte7d2: 231});
  const cues = createSourceActorCueResetRuntime({world: worldSource, dispatch: {
    getSourceActor(selected) {return part(selected,'mapping',mapping) as ReturnType<SourceActorInputChargeSources['mapping']['getActor']>;},
    getActorBinding(selected) {return part(selected,'dispatch',dispatch);},
  }});
  cues.bindActor(id, {byte541: 1, byte542: 2, byte543: 3, byte544: 4, byte545: 5, byte546: 6,
    byte547: 7, byte588: 8, byte7ce: 9, byte7cf: 10});
  const sources: SourceActorCommandAdmissionSources = {world: worldSource, status: statusSource, attributes,
    charge, actionRequest: action, cues, streams,
    ...(options.gqr5 === null ? {} : {gqr5: options.gqr5 ?? 0x00070007})};
  const runtime = createSourceActorCommandAdmissionRuntime(sources);
  const bind = () => runtime.bindActor(id, initial); if (!options.defer) bind();
  const addSentinelActor = (table: typeof root) => {
    const nextId=Symbol('shared table actor'), nextActual=createRomActor();
    absent(nextActual,'fbPhaseSlots'); absent(nextActual,'shotByte1db3');
    nextActual.commandTable=table; nextActual.cmdButton=2; nextActual.cmdSubtype=0; nextActual.cmdChargedRanged=73;
    extras.set(nextId,{actual:nextActual,world:{...world},mapping:{...mapping},status:{},attribute:{},dispatch:{...dispatch},matrix:[...matrix]});
    streams.bindActor(nextId,{activeMask579:0,blockedMask1d9a:0,marker71d:0},Array.from({length:4},()=>({
      group18:0,action19:0,status1d:0,current00:null,next04:null,wait14:0,finished1a:1,event1e:0})));
    streams.bindStartActor(nextId,{familyBank1d80:null,sharedBank1d84:null,defaultSelector582:0,marker709:0});
    charge.bindActor(nextId,{}); action.bindActor(nextId,{}); cues.bindActor(nextId,{});
    runtime.bindActor(nextId,{pointer508:null});
    return {actual:nextActual,run:()=>runtime.dispatchSubtypeDirection(nextId)};
  };
  return {actual,id,descriptorId,world,mapping,status,attribute,meta,matrix,raw8c,start,stream,cells,slots,dispatch,initial,
    global,data,hooks,sources,charge,action,cues,cueTable,row,root,targets,runtime,bind,addSentinelActor,
    binding: () => runtime.getActorBinding(id), run: () => runtime.dispatchSubtypeDirection(id)};
}
export function runActorCommandAdmissionSelfTests(): void {
  {
    const x = fixture();
    check(isSourceActorCommandAdmissionRuntime(x.runtime) && !isSourceActorCommandAdmissionRuntime({...x.runtime}), 'genuine brand');
    check(Object.isFrozen(x.runtime) && Object.isSealed(x.binding()) && x.binding() !== x.initial, 'sealed partial binding');
    equal(x.runtime.getSourceOwners(x.id).length, 1, 'one new binding owner');
    equal(x.runtime.getSourceOwners(x.id)[0], x.binding(), 'canonical new binding');
    equal(x.runtime.getActualActor(x.id), x.actual, 'actual'); equal(x.runtime.getWorldBinding(x.id), x.world, 'world');
    equal(x.runtime.getStatusBinding(x.id), x.status, 'status'); equal(x.runtime.getMappingActor(x.id), x.mapping, 'mapping');
    equal(x.runtime.getAttributeBinding(x.id), x.attribute, 'attribute'); equal(x.runtime.getChargeRuntime(), x.charge, 'charge');
    equal(x.runtime.getActionRuntime(), x.action, 'action'); equal(x.runtime.getCueRuntime(), x.cues, 'cues');
    equal(x.runtime.getStartBinding(x.id), x.start, 'start'); equal(x.runtime.getStreamBinding(x.id), x.stream, 'stream');
    equal(x.runtime.getGlobal(), x.global, 'global'); equal(x.runtime.getData(), x.data, 'data');
    equal(x.runtime.getKnownStorageOwners().length, 0, 'no eager source pointers');
    equal(x.run(), 1, 'ground X [44,3,2,0] native one');
    equal(x.actual.cmdChargedRanged, 0, 'actual direction zero'); equal(x.actual.prevActionIndex, 2, 'actual previous command');
    equal(x.actual.actionIndex, 2, 'actual action'); equal(x.actual.variantIndex, 0, 'actual variant');
    equal(x.actual.controlWord, 3, 'mode byte'); equal(x.actual.stateTimer, 0, 'mandatory timer zero');
    equal(x.binding().pointerc8, null, 'snapshot object copied'); equal(x.actual.visibilityTarget, null, 'snapshot target copied');
    equal(x.binding().byteD0, 231, 'snapshot action request byte');
    equal(x.actual.targetDistance760, 20000, 'full distance'); equal(x.actual.horizontalDistance764, 20000, 'horizontal distance');
    equal(x.actual.aimOrigin518.x, 0, 'source sine zero'); equal(x.actual.aimOrigin518.y, 17, 'matrix lane7 not position');
    equal(x.actual.aimOrigin518.z, 20000, 'source cosine one'); equal(x.start.marker709, 0, 'canonical709');
    equal(x.actual.stateFlagA, 56, 'source57a'); equal(x.actual.stateFlagB, 0, 'source57b zero store');
    equal(x.stream.blockedMask1d9a, 0, 'canonical1d9a'); check(x.targets.every(t => t.visibilityMask5e6 === 251), 'all six visibility effects');
    equal(x.actual.fbCue, 44, 'full cue44'); equal(x.actual.ubCue, 44, 'upper cue44');
    equal(x.actual.fbState, 2, 'full state selected'); equal(x.actual.ubState, 6, 'upper state selected');
    equal(x.cues.getActorBinding(x.id).byte7cf, 21, 'prior full cue retained'); equal(x.cues.getActorBinding(x.id).byte7ce, 22, 'prior upper cue retained');
    equal(x.actual.fbPhase, 0, 'real full reset'); equal(x.dispatch.marker1db3, 0, 'real upper reset');
    check(!hasIncompleteSourceActorCommandAdmission(x.actual), 'complete clears marker');
    equal(x.run(), 1, 'completed invocation can repeat genuine stores');
  }
  {
    const x = fixture({defer: true, global: {}, data: {}, gqr5: null});
    x.initial.pointer508 = null; absent(x.initial,'pointer504'); absent(x.initial,'pointerc8'); absent(x.initial,'byteD0');
    x.row[0] = 255; x.bind(); absent(x.actual,'controlWord'); absent(x.actual,'heading'); absent(x.actual,'aimOrigin518');
    equal(x.run(), 0, 'sentinel before unrelated source cells'); equal(x.actual.prevActionIndex, 71, 'sentinel no584');
    equal(Object.keys(x.binding()).length, 1, 'missing fields stay missing');
    check(!hasIncompleteSourceActorCommandAdmission(x.actual), 'sentinel successfully clears direction marker');
  }
  {
    const x = fixture({defer:true}); absent(x.initial,'pointer508'); x.bind(); rejects(x.run,'pointer508: own data');
    equal(x.actual.cmdChargedRanged,91,'missing508 before first store'); check(!hasIncompleteSourceActorCommandAdmission(x.actual),'missing508 retryable');
    const y = fixture(); y.binding().pointer508 = y.targets[0]!; rejects(y.run,'80066408'); equal(y.actual.cmdChargedRanged,91,'active target refuses before587');
    y.binding().pointer508 = null; equal(y.run(),1,'pre-effect direction failure retryable');
  }
  for (const key of ['pointerc8','byteD0'] as const) {
    const x = fixture(); readonly(x.binding(),key); rejects(x.run,`${key}: non-writable`);
    equal(x.actual.prevActionIndex,2,'584 stored before capture readonly'); check(hasIncompleteSourceActorCommandAdmission(x.actual),'prefix poisoned');
    rejects(x.run,'known incomplete');
  }
  for (let raw=0;raw<256;raw++) {
    const x = fixture(); x.action.getActorBinding(x.id).byte7d2=raw; equal(x.run(),1,'raw action byte'); equal(x.binding().byteD0,raw,'raw action copied');
  }
  for (const yaw of [-32768,-1,0,1,32767]) {
    const x = fixture(); const selected={}; x.binding().pointer504=selected; x.world.yawOffset6b8=yaw; equal(x.run(),1,'signed yaw offset domain');
    equal(x.binding().pointerc8,yaw===0?selected:null,'yaw clearc8'); equal(x.binding().byteD0,yaw===0?231:0,'yaw cleard0');
  }
  for (const raw of [1,32767,32768,65535]) {
    const x=fixture(); x.actual.heading=raw; rejects(x.run,'nonzero source trig');
    equal(x.actual.horizontalDistance764,20000,'distance stored before unsupported trig'); equal(x.actual.aimOrigin518.x,11,'trig boundary beforex');
  }
  for (const profile of [null,0,0x00060006]) {
    const x=fixture({gqr5:profile}); rejects(x.run,'GQR5'); equal(x.actual.targetDistance760,20000,'profile late');
  }
  for (const key of ['float80437678','float80437078','float8043762c'] as const) {
    const x=fixture(); absent(x.data,key); rejects(x.run,key); check(hasIncompleteSourceActorCommandAdmission(x.actual),'missing constant retains prefix');
  }
  {
    const x=fixture(); x.meta.byte10=255; let selected=0; x.hooks.matrix=index=>{selected=index;throw Error('selected matrix boundary');};
    rejects(x.run,'selected matrix boundary'); equal(selected,-1,'signed descriptor joint index'); equal(x.actual.aimOrigin518.x,0,'x store precedes selected matrix');
    equal(x.actual.aimOrigin518.y,12,'y not invented');
    const y=fixture(); readonly(y.actual.aimOrigin518,'y'); rejects(y.run,'y: non-writable'); equal(y.actual.aimOrigin518.x,0,'readonlyy keepsx');
    equal(y.actual.aimOrigin518.z,13,'readonlyy blocksz');
  }
  for (let raw=0;raw<256;raw++) {
    const x=fixture({global:{byte45:raw}});
    if(raw>=5&&raw<=127) equal(x.run(),1,'signed45 native early return');
    else {rejects(x.run,'800055fc'); equal(x.actual.fbCue,44,'RNG boundary after genuine cues'); check(hasIncompleteSourceActorCommandAdmission(x.actual),'voice failure poisons');}
  }
  for (let button=0;button<256;button++) {
    const x=fixture(); x.actual.cmdButton=button; x.root.sourceTables=new Array<number[]>(128).fill([255]);
    if(button<128) equal(x.run(),0,'signed positive585 table pointer'); else rejects(x.run,'signed585');
  }
  for (let subtype=0;subtype<256;subtype++) {
    const x=fixture(); x.actual.cmdSubtype=subtype; const bytes=new Array<number>(128*16).fill(255); x.root.sourceTables=[bytes,bytes,bytes];
    if(subtype<128) equal(x.run(),0,'signed positive586 record offset'); else rejects(x.run,'command record address');
  }
  for (let mode=0;mode<256;mode++) {
    const x=fixture(); x.row[1]=mode; x.actual.controlWord=0x800001fc; equal(x.run(),1,'unsigned record mode');
    equal(x.actual.controlWord,(0x800001fc|mode)>>>0,'full unsigned mode OR not low2 truncation');
    equal(x.start.marker709,mode===3?0:33,'mode3-only709'); equal(x.actual.ubCue,mode===3?44:22,'mode3-onlyupper');
  }
  {
    const x=fixture(); x.row[1]=1; x.actual.controlWord=3; rejects(x.run,'8004beb8');
    equal(x.actual.ubCue,0,'real cue0 before stream boundary'); equal(x.actual.actionIndex,99,'stream boundary before580');
    const y=fixture(); y.row[1]=1; y.actual.controlWord=0x43; equal(y.run(),1,'mode3 retained40 cue6 branch'); equal(y.actual.ubCue,6,'real cue6');
  }
  for (let button=0;button<6;button++) {
    const x=fixture(); x.actual.cmdButton=button; equal(x.run(),1,'all fixed flag table selectors');
    equal(x.actual.stateFlagA,[58,56,56,56,56,56][button],'flagA'); equal(x.actual.stateFlagB,button<2?4:0,'flagB');
    const charge=x.charge.getActorBinding(x.id);
    for(let slot=0;slot<3;slot++) {
      equal(charge[['field63c','field640','field644'][slot] as 'field63c'],button===slot+3?0:51+slot,'canonical warmup');
      equal(charge[['field648','field64c','field650'][slot] as 'field648'],button===slot+3?0:61+slot,'canonical bank');
    }
  }
  {
    const x=fixture(); x.actual.cmdButton=6; x.root.sourceTables.push(x.row); rejects(x.run,'authenticated twelve-byte');
    equal(x.actual.stateTimer,0,'unsupported flags after694'); equal(x.stream.blockedMask1d9a,34,'unsupported flags before1d9a');
    const y=fixture(); (y.data.flags3994 as number[])[4]=99; rejects(y.run,'authenticated selected byte'); equal(y.actual.stateFlagA,13,'bad flag never stored');
  }
  for (const maximum of [-32768,-1,0,1,32767]) for(const refillType of [-32768,-1,0,3,32767]) {
    const x=fixture(); Object.assign(x.cells[2]!,{max:maximum,refillType});
    if(maximum===0||refillType===3) equal(x.run(),1,'signed ammo bypass branches'); else rejects(x.run,'8006dbe0');
    equal(x.actual.fbCue,44,'ammo access after cue');
  }
  {
    const x=fixture(); absent(x.cells[2]!,'refillType'); equal(x.run(),1,'max0 skips refillType');
    const y=fixture(); y.cells[2]!.max=65535; rejects(y.run,'max: integer out of bounds');
    const z=fixture(); readonly(z.targets[3]!,'visibilityMask5e6'); rejects(z.run,'visibilityMask5e6: non-writable');
    equal(z.targets[2]!.visibilityMask5e6,251,'earlier visibility target committed'); equal(z.targets[3]!.visibilityMask5e6,255,'failed store untouched');
    equal(z.targets[4]!.visibilityMask5e6,255,'later visibility target untouched'); equal(z.actual.fbCue,21,'visibility failure before cue');
  }
  {
    const x=fixture(); absent(x.targets[5]!,'eligibility83'); equal(x.run(),1,'null captured target never reads eligibility');
    const y=fixture(); y.actual.visibilityRoster=y.targets.slice(0,5); rejects(y.run,'six explicit source pointer'); equal(y.actual.fbCue,21,'six pointer representation required');
  }
  {
    const x=fixture(); x.cueTable[88]=-1; x.cueTable[89]=-1; equal(x.run(),1,'genuine cue sentinel results ignored by source');
    equal(x.actual.fbCue,21,'sentinel full cue untouched'); equal(x.actual.ubCue,22,'sentinel upper cue untouched');
    const y=fixture(); readonly(y.cues.getActorBinding(y.id),'byte542'); rejects(y.run,'byte542: non-writable');
    equal(y.actual.fbCue,44,'genuine cue failure retains earlier cue writes'); equal(y.cues.getActorBinding(y.id).byte543,0,'genuine cue first reset retained');
    check(hasIncompleteSourceActorCommandAdmission(y.actual),'pre-delegation poison');
  }
  {
    const x=fixture(); x.row[0]=255; equal(x.run(),0,'first sentinel'); x.root.sourceTables=[x.row,x.row,x.row]; rejects(x.run,'sourceTables4ec: owner changed');
    const y=fixture(); y.row[0]=255; equal(y.run(),0,'first row retained'); y.root.sourceTables[2]=[255]; rejects(y.run,'selected4ec command byte row: owner changed');
    const z=fixture(); z.actual.commandTable={records:[]}; rejects(z.run,'sourceTables'); equal(z.actual.cmdChargedRanged,0,'legacy normalized records cannot substitute');
  }
  {
    const x=fixture({defer:true}); Object.assign(x.initial,{marker709:5}); rejects(x.bind,'competing command-admission');
    const y=fixture(); Object.defineProperty(y.actual,'commandTable',{get(){throw Error('getter must not execute');}}); rejects(y.run,'commandTable: own data');
    const z=fixture(); z.hooks.matrix=()=>Promise.resolve(z.matrix); rejects(z.run,'synchronous actual');
  }
  {
    const x=fixture(); x.hooks.world=()=>{try{x.run();}catch{} return x.world;}; rejects(x.run,'caught same-runtime reentry');
    equal(x.actual.cmdChargedRanged,91,'getter reentry before first write'); check(!hasIncompleteSourceActorCommandAdmission(x.actual),'pre-write reentry no effect marker');
    delete x.hooks.world; equal(x.run(),1,'fresh pre-effect call can retry');
  }
  {
    const x=fixture(); let fired=false;
    watch(()=>rejects(x.run,'caught same-runtime reentry'),(owner,key)=>{
      if(owner===x.actual&&key==='actionIndex'&&x.actual.targetDistance760===20000&&!fired) {fired=true;try{x.run();}catch{}}
    });
    check(fired&&hasIncompleteSourceActorCommandAdmission(x.actual),'caught mutation reentry poison'); equal(x.actual.actionIndex,99,'reentry before reached destination store');
  }
  {
    const x=fixture(); const seen:string[]=[]; let active=false;
    watch(()=>equal(x.run(),1,'source order'),(owner,key)=>{
      if(owner===x.actual&&key==='cmdButton'&&x.actual.cmdChargedRanged===0) active=true;
      if(active&&owner===x.actual&&['cmdButton','cmdSubtype','cmdChargedRanged','commandTable'].includes(String(key))) seen.push(String(key));
    });
    equal(seen.slice(0,4).join(','),'cmdButton,cmdSubtype,cmdChargedRanged,commandTable','585/586/587 all before4ec');
  }
  for (let value=0;value<256;value++) {
    const x=fixture(); x.row[2]=value; x.row[3]=255-value; x.actual.visibilityBit=value; equal(x.run(),1,'raw action/variant/visibility domains');
    equal(x.actual.actionIndex,value,'raw action byte'); equal(x.actual.variantIndex,255-value,'raw variant byte');
    check(x.targets.every(target=>target.visibilityMask5e6===(255^value)),'all visibility-bit masks');
  }
  for (let value=0;value<256;value++) {
    const x=fixture(); x.row[0]=value;
    if(value===255) {equal(x.run(),0,'only signed-minus-one record sentinel');equal(x.actual.prevActionIndex,71,'sentinel no capture');}
    else if(value<128) equal(x.run(),1,'nonnegative genuine cue indices');
    else {rejects(x.run,'cueTable: indexed byte'); equal(x.actual.stateTimer,0,'negative cue refuses after command stores');}
  }
  for (let value=0;value<256;value++) {
    const x=fixture(); x.meta.byte10=value; let selected=999;
    x.hooks.matrix=index=>{selected=index;return x.matrix;}; equal(x.run(),1,'signed descriptor byte domain');
    equal(selected,value<128?value:value-256,'descriptor10 sign extension');
  }
  {
    const x=fixture(); x.row[0]=256; rejects(x.run,'0: integer out of bounds'); equal(x.actual.prevActionIndex,71,'invalid record head before584');
    const y=fixture(); y.row[2]=256; rejects(y.run,'2: integer out of bounds'); equal(y.actual.aimOrigin518.z,20000,'invalid action byte after snapshot');
    const z=fixture(); z.row[3]=-1; rejects(z.run,'3: integer out of bounds'); equal(z.actual.actionIndex,2,'invalid variant after action store');
  }
  {
    const x=fixture({defer:true}); absent(x.initial,'pointer504'); x.bind(); rejects(x.run,'pointer504: own data');
    equal(x.actual.prevActionIndex,2,'missing snapshot source retains584');
    const y=fixture({defer:true}); absent(y.initial,'byteD0'); y.bind(); rejects(y.run,'byteD0: own data');
    equal(y.actual.visibilityTarget,null,'missingd0 keeps cc store');
    const z=fixture(); absent(z.data,'float8043762c'); z.row[0]=255; equal(z.run(),0,'sentinel does not read zero constant');
  }
  {
    const x=fixture(); const fake={...x.sources.streams};
    rejects(()=>createSourceActorCommandAdmissionRuntime({...x.sources,streams:fake}),'genuine source runtime');
    const y=fixture(); y.actual.commandTable=y.actual.actionSpeedRows as unknown as typeof y.root;
    rejects(y.run,'storage aliases actionSpeedRows');
    const z=fixture(); z.hooks.matrix=()=>z.row; rejects(z.run,'aliases another source owner');
  }
  {
    const x=fixture(); x.run(); const entries=x.runtime.getKnownStorageEntries();
    check(Object.isFrozen(entries)&&entries.every(Object.isFrozen),'frozen kind snapshots');
    check(entries.some(e=>e.owner===x.targets[0]&&e.kind==='visibility-target'),'target kind');
    check(entries.some(e=>e.owner===x.matrix&&e.kind==='matrix-row'),'matrix kind');
    check(entries.some(e=>e.owner===x.cells[2]&&e.kind==='ammo-cell'),'ammo kind');
  }
  {
    const x=fixture(); x.actual.cmdChargedRanged=0; readonly(x.actual,'cmdChargedRanged');
    rejects(x.run,'cmdChargedRanged: non-writable'); check(!hasIncompleteSourceActorCommandAdmission(x.actual),'failed first zero store has no effect marker');
    const y=fixture(); y.start.marker709=0; readonly(y.start,'marker709'); rejects(y.run,'marker709: non-writable');
    equal(y.actual.stateTimer,0,'709 zero store is mandatory after694');
    const z=fixture(); z.stream.blockedMask1d9a=0; readonly(z.stream,'blockedMask1d9a'); rejects(z.run,'blockedMask1d9a: non-writable');
    equal(z.actual.stateFlagB,0,'1d9a zero store after both flags'); equal(z.targets[0]!.visibilityMask5e6,255,'1d9a failure before visibility');
  }
  {
    const x=fixture(); x.hooks.matrix=()=>{x.actual.heading=1;return x.matrix;}; rejects(x.run,'80045238');
    equal(x.actual.aimOrigin518.x,0,'sin prefix retained'); equal(x.actual.aimOrigin518.y,17,'Y precedes fresh cosine heading');
    equal(x.actual.aimOrigin518.z,13,'nonzero cosine boundary beforeZ');
  }
  {
    const x=fixture(); x.row[0]=255; let fired=false;
    watch(()=>equal(x.run(),0,'retained table selectors'),(owner,key)=>{
      if(owner===x.actual&&key==='commandTable'&&!fired) {fired=true;x.actual.cmdButton=127;x.actual.cmdSubtype=127;}
    });
    check(fired,'selector retention mutation reached'); equal(x.actual.prevActionIndex,71,'table selection used pre4ec selector values');
  }
  {
    const x=fixture(); let fired=false;
    watch(()=>equal(x.run(),1,'fresh584 flag reads'),(owner,key)=>{
      if(owner===x.actual&&key==='stateFlagA'&&x.actual.stateTimer===0&&!fired) {fired=true;x.actual.prevActionIndex=1;}
    });
    check(fired,'flag reload mutation reached'); equal(x.actual.stateFlagA,56,'flagA selected prior584'); equal(x.actual.stateFlagB,4,'flagB reloads584');
  }
  {
    const x=fixture(); let fired=false;
    watch(()=>equal(x.run(),1,'record mode reload'),(owner,key)=>{
      if(owner===x.actual&&key==='controlWord'&&x.actual.actionIndex===2&&!fired) {fired=true;x.row[1]=255;}
    });
    check(fired,'record reload mutation reached'); equal(x.actual.controlWord,255,'unsigned record mode reread');
    equal(x.start.marker709,33,'separate mode reload skips709'); equal(x.actual.ubCue,22,'separate final mode reload skipsupper');
  }
  {
    const x=fixture(); let first=false,later=false;
    watch(()=>equal(x.run(),1,'visibility load order'),(owner,key)=>{
      if(owner===x.targets[0]&&key==='visibilityMask5e6'&&!first) {first=true;x.actual.visibilityBit=8;}
      if(owner===x.targets&&key==='1'&&!later) {later=true;x.actual.visibilityBit=16;}
    });
    check(first&&later,'both visibility reload mutations reached'); equal(x.targets[0]!.visibilityMask5e6,251,'first actorbit retained before targetmask');
    equal(x.targets[1]!.visibilityMask5e6,239,'later actorbit after pointer');
  }
  {
    const x=fixture(); x.row[0]=255; const shared=x.addSentinelActor(x.root);
    equal(x.run(),0,'first shared command-root sentinel'); equal(shared.run(),0,'second actor uses same root and table');
    const competing=x.addSentinelActor({records:[],sourceTables:x.root.sourceTables});
    rejects(competing.run,'competing command-root identities');
    equal(competing.actual.cmdChargedRanged,0,'competing wrapper failure retains direction store');
    check(hasIncompleteSourceActorCommandAdmission(competing.actual),'competing wrapper effect prefix marked');
  }
  {
    const x=fixture(); const other=createSourceActorCommandAdmissionRuntime(x.sources); rejects(()=>other.bindActor(x.id,x.initial),'already claimed');
  }
}
