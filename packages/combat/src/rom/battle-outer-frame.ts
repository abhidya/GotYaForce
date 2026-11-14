/** Bounded genuine80029434 prefix, not a successful outer battle frame.
 * Executes8b048→8b010 and29d48→29e98 over the SAME80433934 owner and
 * existing teamRows103/charged/meter owners. First reached active-burst8b290,
 * normal53b30 or unconditional pausedbef4 remains a hard ordered boundary unless
 * explicit mass ingress supplies the bounded53b30 prefix. That path stops before
 * nonzero passenger1e4 or first55fc, never skips a scheduler predecessor.
 * No success callback, skipped predecessor, source actor hydration, epoch,
 * scheduler invocation or browser activation is manufactured.
 *
 * Owning the scheduler grants exclusivity and failure closure ONLY. Its public
 * entry points close on claim; no runnable outer scheduler capability exists.
 * Stable synchronous nonproxy own-data records are host bounds. Destinations
 * are checked at each store; prior writes survive refusal and close the whole
 * retained scheduler graph. Identity checks are host admission, not ROM reads.
 * Evidence: outer-frame-evidence-2026-11-14.md (five complete archived bodies).
 */
import {isSourceObjectSchedulerRuntime, claimSourceObjectSchedulerOuterFrame,
  closeSourceObjectSchedulerOuterFrame, type SourceObjectSchedulerRuntime} from './source-object-scheduler.js';
import {isSourceActorAttributeRefreshRuntime, type SourceActorAttributeRefreshRuntime} from './actor-attribute-refresh.js';
import {markIncompleteSourceActorDoubleLifecycle, requireCompleteSourceActorDoubleLifecycle} from './actor-double-prehook.js';
import {addSourceFloat32} from './source-float.js';
import type {SourceBattleOuterGlobalFields, SourceBattleSystemGlobals} from './battle-global-layout.js';

/** Explicit metadata for source pointer arithmetic, not a copied actor table.
 * Source536b0 constructs six contiguous1e00 records;53b30 captures table[0]
 * once, then advances through this immutable identity map. The live pointer
 * table remains separate and may use a different/repeated order. */
export interface SourceBattlePhysicalActorBlock {
  readonly base: symbol;
  readonly identities: readonly symbol[];
}
export interface SourceBattleMassPreparationSources {
  /** Separate DAT_803c6dec[24] and80436264[4] storage, retained by identity. */
  teamPointers?: Record<number,symbol|null>;
  teamCounts?: Record<number,number>;
  physicalBlock?: SourceBattlePhysicalActorBlock;
  /** SAME4ac registry used by the reached canonical status binding. */
  attributes?: SourceActorAttributeRefreshRuntime;
  data?: {float80437250?: number; float80437254?: number};
}
export interface SourceBattleOuterFrameSources {
  scheduler: SourceObjectSchedulerRuntime;
  /** Same explicit80433930 owner, reached only after a team/slot match. */
  systemGlobals?: SourceBattleSystemGlobals;
  /** Optional genuine53b30 prefix. Missing ingress retains the old boundary. */
  massPreparation?: SourceBattleMassPreparationSources;
}
export interface SourceBattleOuterFrameRuntime {
  getSchedulerRuntime(): SourceObjectSchedulerRuntime;
  getMatchGlobals(): SourceBattleOuterGlobalFields;
  /** This bounded prefix always refuses at its first unimplemented callee. */
  runFrame(): never;
}
const runtimes=new WeakSet<object>(), pendingClaims=new WeakMap<object,SourceObjectSchedulerRuntime>(),
  claimedGlobals=new WeakSet<object>();
const failures=new WeakMap<object,(scheduler: SourceObjectSchedulerRuntime)=>void>();
export function isSourceBattleOuterFrameRuntime(value: unknown): value is SourceBattleOuterFrameRuntime {
  return value!==null && typeof value==='object' && runtimes.has(value);
}
export function isPendingSourceBattleOuterFrameClaim(outer: unknown,scheduler: SourceObjectSchedulerRuntime): boolean {
  return isSourceBattleOuterFrameRuntime(outer) && pendingClaims.get(outer)===scheduler;
}
export function requireSourceBattleOuterFrameFailure(outer: SourceBattleOuterFrameRuntime,scheduler: SourceObjectSchedulerRuntime): void {
  const scope=failures.get(outer);
  if(!isSourceBattleOuterFrameRuntime(outer) || !scope) fail('private active outer failure required');
  scope(scheduler);
}
function fail(reason: string): never {
  throw Error(`[battle-outer-frame] ${reason}; offline execution aborted, prior writes/effects are not rolled back`);
}
function own(value: unknown,key: string,writable=false): unknown {
  if(value===null || typeof value!=='object') fail(`${key}: own data record required`);
  const p=Object.getOwnPropertyDescriptor(value,key);
  if(!p || !('value' in p)) fail(`${key}: own data property required`);
  if(writable && !p.writable) fail(`${key}: non-writable field`);
  return p.value;
}
function record(value: unknown,where: string): object {
  if(value===null || typeof value!=='object' || value instanceof Promise || ArrayBuffer.isView(value))
    fail(`${where}: synchronous own-data record required`);
  return value;
}
function unsigned(value: unknown,max: number,where: string): number {
  if(typeof value!=='number' || !Number.isInteger(value) || value<0 || value>max) fail(`${where}: raw unsigned source integer required`);
  return value===0 ? 0 : value;
}
const s8=(value: number): number=>value<<24>>24;
export function createSourceBattleOuterFrameRuntime(sources: SourceBattleOuterFrameSources): SourceBattleOuterFrameRuntime {
  const scheduler=own(sources,'scheduler');
  if(!isSourceObjectSchedulerRuntime(scheduler)) fail('genuine source scheduler required');
  const root=scheduler.getRootRuntime(), spawns=root.getSpawnRuntime(), allocator=scheduler.getAllocatorRuntime();
  const globals=record(scheduler.getMatchGlobals(),'canonical80433934');
  if(spawns.getMatchGlobals()!==globals || spawns.getAllocatorRuntime()!==allocator) fail('canonical scheduler graph differs');
  if(globals===sources || claimedGlobals.has(globals)) fail('battle globals alias sources or are already outer-owned');
  let busy=false,poisoned=false,incomplete=false,closing=false;
  const retained=new Map<string,object>(), massActors=new Map<symbol,object>();
  const check=(): void=>{if(poisoned) fail('caught same-runtime reentry');};
  const read=(owner: unknown,key: string): unknown=>{const value=own(owner,key);check();return value;};
  const call=<T>(run: ()=>T): T=>{const result=run();check();return result;};
  const write=(owner: object,key: string,value: number|boolean|symbol|null): void=>{
    own(owner,key,true);check();(owner as Record<string,unknown>)[key]=value;check();
  };
  const byte=(owner: object,key: string): number=>unsigned(read(owner,key),255,key);
  const half=(owner: object,key: string): number=>unsigned(read(owner,key),65535,key);
  const noShadows=(owner: object,keys: readonly string[]): void=>{
    for(const key of keys) {const p=Object.getOwnPropertyDescriptor(owner,key);check();if(p!==undefined) fail(`${key}: competing source cell owner`);}
  };
  const retain=(name: string,value: unknown): object=>{
    const actual=record(value,name), previous=retained.get(name);
    const mass=retained.get('massPreparation');
    if(mass!==undefined) {
      const p=Object.getOwnPropertyDescriptor(mass,'attributes');check();
      if(p && 'value' in p && isSourceActorAttributeRefreshRuntime(p.value) &&
        call(()=>p.value.getKnownParameterDescriptors()).includes(actual)) fail(`${name}: parameter storage alias`);
    }
    if(previous!==undefined && previous!==actual) fail(`${name}: canonical owner changed`);
    if(actual===sources || actual===globals || actual===root.getDrawList() ||
      call(()=>scheduler.getRetainedStorageOwners()).includes(actual) ||
      [...retained].some(([key,owner])=>key!==name && owner===actual)) fail(`${name}: source storage alias`);
    retained.set(name,actual);return actual;
  };
  const match=(): object=>{
    const current=call(()=>spawns.getMatchGlobals());if(current!==globals) fail('canonical80433934 owner changed');return current;
  };
  const system=(): object=>{
    const actual=retain('systemGlobals',read(sources,'systemGlobals'));
    noShadows(actual,['byte2','2']);return actual;
  };
  const teamTable=(owner: object): object=>{
    const table=retain('teamRows103',read(owner,'teamRows103'));
    if(!Array.isArray(table)) fail('teamRows103: existing row-reference array required');return table;
  };
  const team=(table: object,index: number): object=>{
    // The source captured owner+f4 once. Never retarget a later row to a
    // replacement table; retain the existing row-reference representation.
    if(read(globals,'teamRows103')!==table) fail('teamRows103: canonical owner changed');
    const row=retain(`team row${index}`,read(table,String(index)));
    const base=0xf4+index*0x3c,offsets=[...Array.from({length:10},(_,i)=>i),0xf,0x10,0x30,0x31,0x32,0x33];
    noShadows(globals,[...offsets.flatMap(offset=>{const address=base+offset,hex=address.toString(16);
      return [String(address),`byte${hex}`,`byte${hex.toUpperCase()}`];}),
      `field${(base+0xf).toString(16)}`,`word${(base+0x32).toString(16)}`,
      `half${(base+0x30).toString(16)}`,`half${(base+0x32).toString(16)}`]);
    noShadows(row,['byteF','bytef','byte0F','byte0f','byte103','half30','half32','word126',
      'byte30','byte31','byte32','byte33',...Array.from({length:10},(_,i)=>String(i)),'15','16','48','49','50','51']);
    return row;
  };
  const storeCharged=(row: object,value: boolean): void=>{
    if(typeof read(row,'charged')!=='boolean') fail('charged: existing boolean source0/1 owner required');
    write(row,'charged',value);
  };
  const applyPending=(): void=>{
    const request=s8(byte(match(),'byte15d4'));
    if(request!==0) {
      const next=request-1;
      write(match(),'byte66',next&255); //8b010 store precedes both signed exits.
      if(next<2 && next>=0) write(match(),'halfD6',0);
    }
    write(match(),'byte15d4',0); //Unconditional even when request was0.
  };
  const refresh=(row: object): void=>{
    write(row,'byte1',0);write(row,'byte2',0);write(row,'byte3',0);
    for(let i=4;i<=9;i++) write(row,`byte${i}`,255);
    let count=0;
    // Original has three unrolled pairs. Each of the six candidates reloads
    // the global owner/mask; its matched roster index remains a local register.
    for(let slot=0;slot<6;slot++) {
      const owner=match(),bit=1<<slot;
      noShadows(owner,['byte15d9','activeMask15d9','5593',
        ...Array.from({length:6},(_,i)=>String(0xcb+i)),
        ...['CB','CC','CD','CE','CF','D0','cb','cc','cd','ce','cf','d0'].map(key=>`byte${key}`)]);
      if((byte(owner,'activeMask')&bit)===0) continue;
      const rowTeam=s8(byte(row,'byte0'));
      const slots=retain('slotTeam',read(owner,'slotTeam'));
      if(!Array.isArray(slots)) fail('slotTeam: existing slot-reference array required');
      const slotTeam=s8(unsigned(read(slots,String(slot)),255,'slotTeam byte'));
      if(slotTeam!==rowTeam) continue;
      write(row,'byte1',(byte(row,'byte1')+1)&255);
      if((s8(byte(system(),'controllerMask'))&bit)!==0) write(row,'byte2',(byte(row,'byte2')+1)&255);
      const mask=byte(row,'byte3'),destination=4+count;count++;
      write(row,'byte3',mask|bit);write(row,`byte${destination}`,slot);
    }
  };
  const updateTeams=(): void=>{
    const table=teamTable(match()); //29d60–64 captures original row base once.
    for(let i=0;i<4;i++) {
      const row=team(table,i);refresh(row);
      if(s8(byte(row,'byte1'))<=0) continue;
      if(s8(byte(row,'byte10'))!==0) {
        storeCharged(row,false);
        fail('80029d90 reached mandatory8008b290 active-burst predecessor');
      }
      const meter=half(row,'meter'),threshold=half(row,'threshold30');
      storeCharged(row,meter>=threshold);
    }
  };
  const prepareMass=(): never=>{
    const supplied=Object.getOwnPropertyDescriptor(sources,'massPreparation');check();
    if(supplied===undefined) fail('80029458 reached mandatory80053b30 normal-stage predecessor');
    const mass=retain('massPreparation',read(sources,'massPreparation'));
    const massOwner=(key: string): object=>{
      if(read(sources,'massPreparation')!==mass) fail('massPreparation: canonical owner changed');
      return retain(`mass ${key}`,read(mass,key));
    };
    const pointers=(): object=>massOwner('teamPointers');
    const counts=(): object=>massOwner('teamCounts');
    const storePointer=(index: number,id: symbol|null): void=>{
      // Host bounded24-word storage; source signed indices are never clamped.
      if(index<0 || index>=24) fail('53b30 team pointer index outside explicit24-word owner');
      write(pointers(),String(index),id);
    };
    const storeCount=(index: number,value: number): void=>{
      if(index<0 || index>=4) fail('53b30 team count index outside explicit4-byte owner');
      write(counts(),String(index),value&255);
    };
    const slotPointer=(index: number): symbol|null=>{
      const table=call(()=>scheduler.getActorSlotTable());
      // Getter retains this very source table; no new roster or alias is made.
      const old=retained.get('mass actorSlots');
      if(old!==undefined && old!==table) fail('mass actorSlots: canonical owner changed');
      if([...retained].some(([role,value])=>role!=='mass actorSlots' && value===table)) fail('mass actorSlots: source storage alias');
      retained.set('mass actorSlots',table);
      const id=read(table,String(index));
      if(id!==null && typeof id!=='symbol') fail('53b30 actor slot: source pointer identity required');
      return id;
    };
    const actual=(id: symbol|null): object=>{
      if(id===null) fail('53b30 null actor at reached dereference');
      if(call(()=>allocator.getInteriorAddress(id))!==null) fail('53b30 actual actor base identity required');
      const value=record(call(()=>allocator.getPointerTarget(id)),'53b30 actual actor');
      const old=massActors.get(id);
      if(old!==undefined && old!==value) fail('53b30 actual actor changed');
      if([...retained.values()].includes(value)) fail('53b30 actual actor aliases mass/global storage');
      // Retain the resolved actual before fallible field admission so a new
      // physical actor with an alias/missing cell cannot escape failure closure.
      massActors.set(id,value);
      noShadows(value,['0','byte0','mass204','sourceArrowMass204','field204','float204','516',
        'field208','float208','520','byte204','byte205','byte206','byte207','byte208','byte209','byte20a','byte20b',
        'byte20A','byte20B','byte88','field88','136','floatB4','fieldB4','floatb4','fieldb4',
        '180','181','182','183','byteb4','byteb5','byteb6','byteb7','byteB4','byteB5','byteB6','byteB7',
        'byte1db','byte1DB','field1db','field1DB','475','lifecycle18','byte18','field18','state18',
        'parameter4ac','pointer4ac','1196','24','517','518','519','521','522','523']);
      call(()=>requireCompleteSourceActorDoubleLifecycle(value));return value;
    };
    const status=spawns.getPrehookRuntime().getStatusRuntime(), stage=root.getStageRuntime();
    const borg=(id: symbol,actor: object): object=>{
      if(call(()=>status.getActualActor(id))!==actor) fail('53b30 canonical status actual differs');
      const value=record(call(()=>status.getActualBorg(id)),'53b30 same Borg204');
      // Identities are keyed by actual actor, not the symbol description.
      const prior=borgs.get(id);
      if(prior!==undefined && prior!==value) fail('53b30 canonical Borg changed');
      if(value===actor || [...retained.values()].includes(value) ||
        [...borgs].some(([other,owner])=>other!==id && owner===value) || [...massActors.values()].includes(value))
        fail('53b30 Borg aliases another source owner');
      noShadows(value,['mass204','field204','float204','516','byte204','byte205','byte206','byte207',
        'mass208','field208','float208','520','517','518','519',
        'byte208','byte209','byte20a','byte20b','byte20A','byte20B','521','522','523']);
      borgs.set(id,value);return value;
    };
    const borgs=new Map<symbol,object>();
    const f=(owner: object,key: string): number=>{
      const value=read(owner,key);
      if(typeof value!=='number' || !Number.isFinite(value) || !Object.is(value,Math.fround(value)))
        fail(`${key}: finite exact source float32 required`);
      return value;
    };
    const constant=(key: 'float80437250'|'float80437254',expected: number): number=>{
      const value=f(massOwner('data'),key);
      if(!Object.is(value,expected)) fail(`${key}: differs from authenticated source bits`);return value;
    };
    const life=(id: symbol,actor: object): number=>{
      if(root.getStageRuntime()!==stage || call(()=>stage.getActualActor(id))!==actor) fail('53b30 canonical stage actual differs');
      const binding=record(call(()=>stage.getActorBinding(id)),'53b30 stage binding');
      if([...retained.values()].includes(binding) || binding===actor || [...borgs.values()].includes(binding)) fail('53b30 stage storage alias');
      return byte(binding,'lifecycle18');
    };
    //80053b5c first clear precedes the captured first actor pointer at53b60.
    storePointer(0,null);
    const base=slotPointer(0);
    for(let i=1;i<20;i++) storePointer(i,null);
    storeCount(0,0);storePointer(20,null);storeCount(1,0);
    storePointer(21,null);storeCount(2,0);storePointer(22,null);storePointer(23,null);storeCount(3,0);
    // Immutable metadata is a host admission bound. It neither loads actor
    // scalar fields nor claims that the caller has hydrated a retail arena.
    const block=massOwner('physicalBlock');
    if(!Object.isFrozen(block)) fail('53b30 physical block metadata must be frozen');
    if(read(block,'base')!==base) fail('53b30 physical base differs from captured table[0]');
    const ids=retain('mass physical identities',read(block,'identities'));
    if(!Array.isArray(ids) || !Object.isFrozen(ids) || read(ids,'length')!==6) fail('53b30 six frozen physical identities required');
    const physicalTargets=new Set<object>(),physicalIds=new Set<symbol>();
    for(let index=0;index<6;index++) {
      if(read(mass,'physicalBlock')!==block) fail('53b30 physical block owner changed');
      const id=read(ids,String(index));
      if(typeof id!=='symbol' || (index===0 && id!==base) || physicalIds.has(id)) fail('53b30 distinct physical base identities required');
      physicalIds.add(id);const actor=actual(id);
      if(physicalTargets.has(actor)) fail('53b30 physical targets overlap');physicalTargets.add(actor);
      if(s8(byte(actor,'active0'))===0) continue;
      const zero=constant('float80437250',0);
      // Source initializes local_18[index] here. It is not observable before
      // the unsupported passenger/RNG suffix; no fabricated stack is exposed.
      const owner=borg(id,actor);write(owner,'sourceArrowMass204',zero);
      const state=s8(life(id,actor));
      if(state===1 || state===2) {
        const binding=record(call(()=>status.getAttributeBinding(id)),'53b30 canonical4ac binding');
        const parameter=read(binding,'parameter4ac');
        if(parameter!==null && typeof parameter!=='symbol') fail('parameter4ac: source pointer identity required');
        const threshold=constant('float80437254',50000);
        const attributes=read(mass,'attributes');
        if(!isSourceActorAttributeRefreshRuntime(attributes) || call(()=>attributes.getActualActor(id))!==actor ||
          call(()=>attributes.getActorBinding(id))!==binding) fail('53b30 same genuine4ac registry required');
        if(parameter===null) fail('53b30 null4ac at reached parameter98 load');
        const descriptor=record(call(()=>attributes.getParameterDescriptor(parameter)),'53b30 same parameter descriptor');
        if([...retained.values()].includes(descriptor) || [...massActors.values()].includes(descriptor) ||
          [...borgs.values()].includes(descriptor)) fail('53b30 parameter storage alias');
        noShadows(descriptor,['mass98','float98','152','153','154','155','byte98','byte99','byte9a','byte9b','byte9A','byte9B']);
        const baseMass=f(descriptor,'field98');
        if(baseMass<threshold) {
          const scale=f(actor,'modelScale'),product=Math.fround(baseMass*scale);
          if(!Number.isFinite(product)) fail('53b30 scaled mass overflows finite float32');
          write(actor,'mass208',product);
        } else write(actor,'mass208',baseMass);
      } else write(actor,'mass208',zero);
      // Actual second load is UNSIGNED, not reuse of the earlier signed load.
      if(life(id,actor)===1) {
        const team=s8(byte(actor,'team'));
        if(team<0 || team>=4) fail('53b30 team outside explicit4-byte count owner');
        const count=byte(counts(),String(team));
        storeCount(team,count+1); // source stb precedes pointer store/admission.
        storePointer(team*6+s8(count),id);
      }
    }
    // Three original unrolled pairs. No active/lifecycle test or pointer
    // snapshot: every one of the six table cells is loaded when reached.
    for(let index=0;index<6;index++) {
      const id=slotPointer(index),actor=actual(id);
      if(id===null) fail('53b30 null actor'); // narrowed after reached dereference.
      const owner=borg(id,actor),total=f(owner,'sourceArrowMass204'),massValue=f(actor,'mass208');
      write(owner,'sourceArrowMass204',addSourceFloat32(total,massValue));
      if(s8(byte(actor,'supportContact1db'))!==0)
        fail('80053b30 mass propagation reached unsupported actual pointer1e4 ownership');
    }
    fail('80053d60 reached mandatory800055fc RNG predecessor');
  };
  const runtime: SourceBattleOuterFrameRuntime={
    getSchedulerRuntime() {return scheduler;},getMatchGlobals() {return globals;},
    runFrame(): never {
      if(busy) {poisoned=true;fail('same-runtime reentry unsupported');}
      if(incomplete) fail('permanently incomplete outer frame');
      busy=true;poisoned=false;
      try {
        if(read(sources,'scheduler')!==scheduler || scheduler.getRootRuntime()!==root ||
          root.getSpawnRuntime()!==spawns || scheduler.getAllocatorRuntime()!==allocator) fail('canonical scheduler graph changed');
        noShadows(globals,['5588','102','214','215','byteD6','byteD7','byted6','byted7','half214']);
        applyPending();updateTeams();
        if(s8(byte(match(),'byte66'))===0) prepareMass();
        fail('80029464 reached mandatory8000bef4 outer-frame predecessor');
      } catch(error) {
        incomplete=true;closing=true;
        for(const actor of massActors.values()) markIncompleteSourceActorDoubleLifecycle(actor);
        try {closeSourceObjectSchedulerOuterFrame(scheduler,runtime);} finally {closing=false;}
        throw error;
      } finally {busy=false;}
    },
  };
  failures.set(runtime,selected=>{if(!busy || !closing || !incomplete || selected!==scheduler) fail('private exact active outer failure required');});
  runtimes.add(runtime);pendingClaims.set(runtime,scheduler);
  try {claimSourceObjectSchedulerOuterFrame(scheduler,runtime);} finally {pendingClaims.delete(runtime);}
  claimedGlobals.add(globals);return Object.freeze(runtime);
}
