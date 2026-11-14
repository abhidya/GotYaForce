/** Bounded genuine80029434 prefix, not a successful outer battle frame.
 * Executes8b048→8b010 and29d48→29e98 over the SAME80433934 owner and
 * existing teamRows103/charged/meter owners. First reached active-burst8b290,
 * normal53b30 or unconditional pausedbef4 remains a hard ordered boundary unless
 * explicit mass ingress supplies the bounded53b30 prefix. That path stops before
 * nonzero passenger1e4 or missing RNG/ordering ingress. The no-contact ordering
 * suffix can return53b30. Optional target ingress executes the ordered6ae60
 * clears. Optional shared10514 ingress supports6b450 early returns before
 * mandatory6b7f4; skipped lifecycle rows retain canonical508/target83 bounds.
 * Its bounded return still cannot skip mandatory27764.
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
import {isSourceActorMatrixUpdateRuntime, type SourceActorMatrixUpdateRuntime} from './actor-matrix-update.js';
import type {SourceActorCommandAdmissionRuntime} from './actor-command-admission.js';
import type {SourceActorSlotStatusRuntime} from './actor-slot-status.js';
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
  data?: {float80437250?: number; float80437254?: number; float80437258?: number};
  /** Actual global RNG bytes, not a seed/default or a host random callback. */
  rngState?: {byte804360c6?: number; byte804360c7?: number};
  /** Distinct DAT_803c4e6c six-word list and DAT_80436260 byte. The list is
   * not cleared: role1 scans count+1 and can observe its stale logical tail. */
  orderPointers?: Record<number,symbol|null>;
  orderCount?: {count80436260?: number};
  /** SAME genuine465fc binding owns4a4. Reached only by role1 parent scans. */
  matrices?: SourceActorMatrixUpdateRuntime;
}
export interface SourceBattleTargetPreparationSources {
  /** Exactly the admission runtime already retained by genuine projectile
   * spawn. Supplies the existing action7d2 and pointer508 cells, no copies. */
  admission?: SourceActorCommandAdmissionRuntime;
  /** SAME optional10514 owner retained by the canonical action runtime. */
  slotStatus?: SourceActorSlotStatusRuntime;
}
export interface SourceBattleOuterFrameSources {
  scheduler: SourceObjectSchedulerRuntime;
  /** Same explicit80433930 owner, reached only after a team/slot match. */
  systemGlobals?: SourceBattleSystemGlobals;
  /** Optional genuine53b30 prefix. Missing ingress retains the old boundary. */
  massPreparation?: SourceBattleMassPreparationSources;
  /** Optional genuine6ae60 continuation, no callback or inferred target list. */
  targetPreparation?: SourceBattleTargetPreparationSources;
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
      [...massActors.values()].includes(actual) ||
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
  const prepareMass=(): void=>{
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
    const constant=(key: 'float80437250'|'float80437254'|'float80437258',expected: number): number=>{
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
    // Sparse host representation preserves uninitialized source stack bytes.
    // Only an active physical row reaches the source stb zero at stack+8+i.
    const passengerCounts: (number|undefined)[]=Array(6);
    const physicalTargets=new Set<object>(),physicalIds=new Set<symbol>();
    for(let index=0;index<6;index++) {
      if(read(mass,'physicalBlock')!==block) fail('53b30 physical block owner changed');
      const id=read(ids,String(index));
      if(typeof id!=='symbol' || (index===0 && id!==base) || physicalIds.has(id)) fail('53b30 distinct physical base identities required');
      physicalIds.add(id);const actor=actual(id);
      if(physicalTargets.has(actor)) fail('53b30 physical targets overlap');physicalTargets.add(actor);
      if(s8(byte(actor,'active0'))===0) continue;
      const zero=constant('float80437250',0);
      passengerCounts[index]=0; //80053be8: active physical index, not actor.slot.
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
    const randomByte=(): number=>{
      const supplied=Object.getOwnPropertyDescriptor(mass,'rngState');check();
      if(supplied===undefined) fail('80053d60 reached mandatory800055fc RNG predecessor');
      const state=massOwner('rngState');
      noShadows(state,['c6','c7','bytec6','bytec7','198','199','seed','state']);
      //13 authenticated instructions: old low is captured once. The high
      // byte store precedes low; a failing low store retains updated high.
      const high=byte(state,'byte804360c7'),low=byte(state,'byte804360c6');
      const nextHigh=(((high*256+low)*3)>>8)&255,nextLow=(low+nextHigh)&255;
      write(state,'byte804360c7',nextHigh);
      write(state,'byte804360c6',nextLow);
      return nextLow;
    };
    const countOwner=(): object=>{
      const owner=massOwner('orderCount');noShadows(owner,['count','byte0','0']);return owner;
    };
    const orderCount=(): number=>byte(countOwner(),'count80436260');
    const writeOrderCount=(value: number): void=>write(countOwner(),'count80436260',value&255);
    const orderIndex=(index: number): void=>{
      // Index6 aliases the adjacent actor table in retail memory. This
      // bounded host list does not silently manufacture that alias.
      if(index<0 || index>=6) fail('53b30 order pointer outside explicit6-word owner');
    };
    const orderPointer=(index: number): symbol|null=>{
      orderIndex(index);const id=read(massOwner('orderPointers'),String(index));
      if(id!==null && typeof id!=='symbol') fail('53b30 order pointer identity required');return id;
    };
    const writeOrderPointer=(index: number,id: symbol|null): void=>{
      orderIndex(index);write(massOwner('orderPointers'),String(index),id);
    };
    const world=spawns.getWorldRuntime(),worlds=new Map<symbol,object>();
    const worldOwner=(id: symbol,actor: object): object=>{
      if(spawns.getWorldRuntime()!==world || call(()=>world.getActualActor(id))!==actor ||
        call(()=>status.getActualActor(id))!==actor) fail('53b30 canonical world actual differs');
      const owner=record(call(()=>world.getActorBinding(id)),'53b30 same world4a0');
      if(call(()=>status.getWorldBinding(id))!==owner || (worlds.has(id)&&worlds.get(id)!==owner))
        fail('53b30 canonical world binding differs');
      if(owner===actor || [...retained.values()].includes(owner) || [...borgs.values()].includes(owner))
        fail('53b30 world storage alias');
      noShadows(actor,['mode4a0','field4a0','byte4a0','byte4A0','1184']);
      noShadows(owner,['field4a0','byte4a0','byte4A0','1184']);worlds.set(id,owner);return owner;
    };
    const slot=(actor: object): number=>{
      noShadows(actor,['slot3e4','byte3e4','byte3E4','field3e4','field3E4','996']);
      return s8(byte(actor,'slot'));
    };
    const passengerCount=(index: number): number=>{
      if(index<0 || index>=6 || passengerCounts[index]===undefined)
        fail('53b30 reached uninitialized or out-of-domain local passenger count');
      return s8(passengerCounts[index]!);
    };
    const parent=(id: symbol,actor: object,worldBinding: object): symbol|null=>{
      const matrices=read(mass,'matrices');
      if(!isSourceActorMatrixUpdateRuntime(matrices) || call(()=>matrices.getActualActor(id))!==actor ||
        call(()=>matrices.getWorldBinding(id))!==worldBinding || call(()=>matrices.getGlobals())!==globals ||
        call(()=>matrices.getMappingActor(id))!==call(()=>status.getMappingActor(id)))
        fail('53b30 same genuine4a4 matrix owner required');
      const owner=record(call(()=>matrices.getActorBinding(id)),'53b30 matrix4a4 binding');
      if(call(()=>world.getCorrectedTraversalState(id))!==owner) fail('53b30 canonical corrected4a4 owner differs');
      if(owner===actor || [...retained.values()].includes(owner) || [...borgs.values()].includes(owner) ||
        [...worlds.values()].includes(owner)) fail('53b30 matrix storage alias');
      noShadows(actor,['link4a4','pointer4a4','field4a4','byte4a4','byte4a5','byte4a6','byte4a7',
        'byte4A4','byte4A5','byte4A6','byte4A7','1188','1189','1190','1191']);
      noShadows(owner,['pointer4a4','field4a4','byte4a4','byte4a5','byte4a6','byte4a7',
        'byte4A4','byte4A5','byte4A6','byte4A7','1188','1189','1190','1191']);
      const value=read(owner,'link4a4');
      if(value!==null && typeof value!=='symbol') fail('53b30 parent pointer identity required');return value;
    };
    const shift=(end: number,start: number): void=>{
      // The source unrolls groups of8 then the remainder. A bounded6-word
      // list can reach only the remainder; preserve each load/store pair.
      for(let index=end;index>start;index--) writeOrderPointer(index,orderPointer(index-1));
    };
    let selected=(randomByte()>>>2)%6;
    const direction=(randomByte()&8)!==0?1:-1;
    writeOrderCount(0); //53d9c precedes authenticated1.0 load53da4.
    const one=constant('float80437258',1);
    for(let visit=0;visit<6;visit++) {
      const id=slotPointer(selected),actor=actual(id);
      if(id===null) fail('53b30 null ordering actor');
      noShadows(actor,['float664','mass664','1636','1637','1638','1639','byte664','byte665','byte666','byte667']);
      write(actor,'field664',one);
      selected=selected+direction<0?5:(selected+direction)%6;
      if(s8(byte(actor,'active0'))===0) continue;
      if(byte(worldOwner(id,actor),'mode4a0')===1) continue;
      const captured=s8(orderCount());
      if(captured<0) continue;
      for(let index=0;index<=captured;index++) {
        if(index===captured) {
          const raw=orderCount(),destination=s8(raw);
          writeOrderCount(raw+1); //append stb BEFORE stwx.
          writeOrderPointer(destination,id);break;
        }
        const existing=orderPointer(index); //pointer load, then candidate slot, then existing slot.
        const candidateSlot=slot(actor),other=actual(existing),otherSlot=slot(other);
        const candidateCount=passengerCount(candidateSlot),otherCount=passengerCount(otherSlot);
        if(candidateCount<=otherCount) continue; //stable ties in random visit order.
        shift(captured,index);
        const fresh=orderCount();
        writeOrderPointer(index,id);writeOrderCount(fresh+1);break; //insert stwx BEFORE stb.
      }
    }
    //53f44 reloads table0 once, then returns to physical stride. This explicit
    // metadata covers the original block only; a retargeted base is refused.
    if(slotPointer(0)!==base) fail('53b30 final physical base differs from explicit block');
    for(let index=0;index<6;index++) {
      if(read(mass,'physicalBlock')!==block || read(block,'identities')!==ids)
        fail('53b30 physical block owner changed');
      const id=read(ids,String(index));
      if(typeof id!=='symbol') fail('53b30 physical identity required');
      const actor=actual(id);
      if(s8(byte(actor,'active0'))===0) continue;
      const header=worldOwner(id,actor);
      if(byte(header,'mode4a0')!==1) continue;
      const captured=s8(orderCount());
      if(captured<0) continue;
      for(let position=0;position<=captured;position++) {
        //53f80 list pointer load precedes fresh4a4 every comparison. No
        // dereference of either compared pointer and no null-parent default.
        const existing=orderPointer(position),link=parent(id,actor,header);
        if(existing!==link) continue;
        shift(captured,position);
        const fresh=orderCount();
        writeOrderPointer(position,id);writeOrderCount(fresh+1);break;
      }
    }
    //Genuine53b30 return for the fully reached bounded no-contact path.

  };
  const prepareTargets=(): void=>{
    const supplied=Object.getOwnPropertyDescriptor(sources,'targetPreparation');check();
    if(supplied===undefined) fail('8002945c reached mandatory8006ae60 normal-stage predecessor');
    const target=retain('targetPreparation',read(sources,'targetPreparation'));
    const stage=root.getStageRuntime(),world=spawns.getWorldRuntime(),status=spawns.getPrehookRuntime().getStatusRuntime();
    const admission=(): SourceActorCommandAdmissionRuntime=>{
      if(read(sources,'targetPreparation')!==target) fail('targetPreparation: canonical owner changed');
      const selected=read(target,'admission'),canonical=spawns.getAdmissionRuntime();
      if(selected!==canonical) fail('6ae60 exact retained command admission required');return canonical;
    };
    const physical=(): readonly symbol[]=>{
      // A new source load of803c4e84 occurs at every pass. The frozen block is
      // pointer-arithmetic metadata from53b30, not a source actor-table copy.
      const base=slotPointer(0),mass=retained.get('massPreparation'),block=retained.get('mass physicalBlock'),
        ids=retained.get('mass physical identities');
      if(!mass || !block || !ids || read(sources,'massPreparation')!==mass ||
        read(mass,'physicalBlock')!==block || read(block,'identities')!==ids)
        fail('6ae60 canonical physical block owner changed');
      if(read(block,'base')!==base) fail('6ae60 physical base differs from explicit block');
      if(!Array.isArray(ids) || !Object.isFrozen(ids) || read(ids,'length')!==6)
        fail('6ae60 six frozen physical identities required');
      return ids as readonly symbol[];
    };
    const actorAt=(ids: readonly symbol[],index: number): {id: symbol;actor: object}=>{
      const id=read(ids,String(index));if(typeof id!=='symbol') fail('6ae60 physical actor identity required');
      return {id,actor:actual(id)};
    };
    const actualByte=(actor: object,key: 'byte58a'|'byte58b'|'byte58c'|'byte58d'|'byte7d3'): void=>{
      const hex=key.slice(4),offset=parseInt(hex,16);
      noShadows(actor,[`byte${hex.toUpperCase()}`,`field${hex}`,`field${hex.toUpperCase()}`,
        `flags${hex}`,`mask${hex}`,String(offset)]);
      write(actor,key,0);
    };
    const commandOwners=new Map<symbol,{binding: object;action: object}>();
    const command=(id: symbol,actor: object,needAction: boolean): object=>{
      const runtime=admission();
      if(call(()=>runtime.getActualActor(id))!==actor || call(()=>world.getActualActor(id))!==actor ||
        call(()=>status.getActualActor(id))!==actor ||
        call(()=>runtime.getWorldBinding(id))!==call(()=>world.getActorBinding(id)) ||
        call(()=>runtime.getWorldBinding(id))!==call(()=>status.getWorldBinding(id)) ||
        call(()=>runtime.getMappingActor(id))!==call(()=>status.getMappingActor(id)))
        fail('6ae60 canonical command actor/world/mapping differs');
      const binding=record(call(()=>runtime.getActorBinding(id)),'6ae60 canonical508 binding');
      const actionRuntime=runtime.getActionRuntime(),action=record(call(()=>runtime.getActionBinding(id)),'6ae60 canonical7d2 binding');
      if(call(()=>actionRuntime.getActorBinding(id))!==action || call(()=>actionRuntime.getActualActor(id))!==actor ||
        call(()=>actionRuntime.getWorldBinding(id))!==call(()=>runtime.getWorldBinding(id)))
        fail('6ae60 canonical action7d2 owner differs');
      const old=commandOwners.get(id);
      if(old && (old.binding!==binding || old.action!==action)) fail('6ae60 canonical command owner changed');
      if(binding===action || [binding,action].some(owner=>owner===actor || [...retained.values()].includes(owner)))
        fail('6ae60 command source storage alias');
      commandOwners.set(id,{binding,action});return needAction?action:binding;
    };
    //8006ae78 captures base once. Signed active!=0, six unrolled physical rows.
    const initial=physical();
    for(let index=0;index<6;index++) {
      const {id,actor}=actorAt(initial,index);
      if(s8(byte(actor,'active0'))===0) continue;
      actualByte(actor,'byte58a');actualByte(actor,'byte58b');actualByte(actor,'byte58c');actualByte(actor,'byte58d');
      const action=command(id,actor,true);
      noShadows(actor,['byte7d2','byte7D2','field7d2','flags7d2','2002']);
      noShadows(action,['byte7D2','field7d2','flags7d2','2002']);
      write(action,'byte7d2',0);
      actualByte(actor,'byte7d3');
    }
    //8006af5c reload. Status is reached only after the signed active test.
    const second=physical();
    for(let index=0;index<6;index++) {
      const {id,actor}=actorAt(second,index);
      if(s8(byte(actor,'active0'))===0) continue;
      if(root.getStageRuntime()!==stage || call(()=>stage.getActualActor(id))!==actor)
        fail('6ae60 canonical stage actor differs');
      const binding=record(call(()=>stage.getActorBinding(id)),'6ae60 same lifecycle18 binding');
      if(binding===actor || [...retained.values()].includes(binding)) fail('6ae60 stage source storage alias');
      if(s8(byte(binding,'lifecycle18'))>=1) {
        const present=Object.getOwnPropertyDescriptor(target,'slotStatus');check();
        if(present===undefined) fail('8006af80 reached mandatory8006b450 target-selection predecessor');
        const helper=read(target,'slotStatus'),action=admission().getActionRuntime(),
          canonical=call(()=>action.getSlotStatusRuntime());
        if(helper!==canonical || canonical===undefined || canonical.getSchedulerRuntime()!==scheduler)
          fail('6b450 exact shared slot-status/scheduler owner required');
        call(()=>action.prepareTarget(id));
        fail('8006af88 reached mandatory8006b7f4 target-dispatch predecessor');
      }
    }
    //8006b358 reload. The active BYTE LOAD precedes the unconditional508
    // pointer load, but the active TEST follows it. Inactive rows still need
    // their genuine existing508 binding; no default-null pointer is admitted.
    const third=physical();
    for(let index=0;index<6;index++) {
      const {id,actor}=actorAt(third,index),active=byte(actor,'active0');
      const binding=command(id,actor,false);
      noShadows(actor,['pointer508','field508','byte508','byte509','byte50a','byte50b','byte50A','byte50B',
        '1288','1289','1290','1291']);
      noShadows(binding,['field508','byte508','byte509','byte50a','byte50b','byte50A','byte50B',
        '1288','1289','1290','1291']);
      const pointer=read(binding,'pointer508');
      if(pointer!==null) record(pointer,'6ae60 pointer508');
      if(s8(active)===0 || pointer===null) continue;
      fail('8006b374 reached unsupported source target83 ownership after nonnull508');
    }
    //Genuine void return only if every reached canonical508 owner completed.
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
        if(s8(byte(match(),'byte66'))===0) {
          prepareMass();
          prepareTargets();
          fail('80029460 reached mandatory80027764 normal-stage predecessor');
        }
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
