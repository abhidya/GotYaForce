/** Bounded genuine80029434 prefix, not a successful outer battle frame.
 * Executes8b048→8b010 and29d48→29e98 over the SAME80433934 owner and
 * existing teamRows103/charged/meter owners. The authenticated8b290 leaf reads
 * the SAME unsigned match-global byteD9 freshly for each reached burst row.
 * Nonzero continues later rows; zero calls recorded matched8b480 for fresh byteEB.
 * Its mask admits signed half18 decrement/expiry; positive timers stop before
 * unsupported80029de0 floating arithmetic. First reached
 * normal53b30 or unconditional pausedbef4 remains a hard ordered boundary unless
 * explicit mass ingress supplies the bounded53b30 prefix. That path stops before
 * missing passenger1e4 or missing RNG/ordering ingress. Explicit same-world
 * passenger pointers with allocation-owned signed nonzero83 skip propagation;
 * zero83 accumulates freshly loaded original mass through finite passengers
 * admitted by a captured canonical registry, with per-original repeat refusal.
 * The bounded ordering suffix can return53b30. Optional target ingress executes the ordered6ae60
 * clears. Optional shared10514 ingress supports6b450 early returns before
 * mandatory6b7f4. Its optional genuine target-dispatch owner continues inactive
 * clearing and entry0 bounded returns; skipped lifecycle rows and dispatch
 * returns execute the primary508/504 live SquareDistance path and ordered zero/null
 * distance stores through the next mandatory direction helper or estimator. Skipped lifecycle rows retain canonical508 bounds; active nonnull targets may
 * use the SAME allocation-owned83 byte, caller7d3, signed teams and finite
 * distance guards, then the six-position inner scan and ordered association bits.
 * Its bounded return feeds complete27764 selection/publication, then mandatorybef4.
 * No success callback, skipped predecessor, source actor hydration, epoch,
 * scheduler invocation or browser activation is manufactured.
 *
 * Owning the scheduler grants exclusivity and failure closure ONLY. Its public
 * entry points close on claim; no runnable outer scheduler capability exists.
 * Stable synchronous nonproxy own-data records are host bounds. Destinations
 * are checked at each store; prior writes survive refusal and close the whole
 * retained scheduler graph. Identity checks are host admission, not ROM reads.
 * Evidence: outer-frame-evidence-2026-11-14.md (five complete archived bodies)
 * and actor-ceiling-lifecycle-evidence-2026-11-14.md (complete8b290 leaf),
 * burst-expiry-integration-2026-11-15.md (recorded matched8b480, not a new
 * ProgramDB selection or fresh retail verification).
 */
import {isSourceObjectSchedulerRuntime, claimSourceObjectSchedulerOuterFrame,
  closeSourceObjectSchedulerOuterFrame, type SourceObjectSchedulerRuntime} from './source-object-scheduler.js';
import {isSourceActorAttributeRefreshRuntime, type SourceActorAttributeRefreshRuntime} from './actor-attribute-refresh.js';
import {markIncompleteSourceActorDoubleLifecycle, requireCompleteSourceActorDoubleLifecycle} from './actor-double-prehook.js';
import {addSourceFloat32} from './source-float.js';
import {readSourceSquareDistance} from './source-square-distance.js';
import {readSourceTargetDistance} from './source-target-distance.js';
import {readSourceShortTrig} from './source-short-trig.js';
import {isSourceActorMatrixUpdateRuntime, type SourceActorMatrixUpdateRuntime} from './actor-matrix-update.js';
import type {SourceActorCommandAdmissionRuntime} from './actor-command-admission.js';
import {isSourceActorTargetDispatchRuntime,type SourceActorTargetDispatchRuntime} from './actor-target-dispatch.js';
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
  /** Genuine6b7f4 on this exact scheduler/admission graph. */
  targetDispatch?: SourceActorTargetDispatchRuntime;
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
const s16=(value: number): number=>value<<16>>16;
// Final host destination check uses the native intrinsic retained at module load.
// For the declared synchronous nonproxy records it cannot invoke application
// callbacks. A stale earlier metadata snapshot cannot authorize creation or a
// setter call after the observable ownership checks have completed.
const primaryStoreDescriptor=Reflect.getOwnPropertyDescriptor;
const primaryStoreDescriptors=Object.getOwnPropertyDescriptors;
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
    teamLayout(noShadows,row,index);return row;
  };
  const teamLayout=(shadows: typeof noShadows,row: object,index: number): void=>{
    const base=0xf4+index*0x3c,offsets=[...Array.from({length:10},(_,i)=>i),0xf,0x10,0x30,0x31,0x32,0x33];
    shadows(globals,[...offsets.flatMap(offset=>{const address=base+offset,hex=address.toString(16);
      return [String(address),`byte${hex}`,`byte${hex.toUpperCase()}`];}),
      `field${(base+0xf).toString(16)}`,`word${(base+0x32).toString(16)}`,
      `half${(base+0x30).toString(16)}`,`half${(base+0x32).toString(16)}`]);
    shadows(row,['byteF','bytef','byte0F','byte0f','byte103','half30','half32','word126',
      'byte30','byte31','byte32','byte33',...Array.from({length:10},(_,i)=>String(i)),'15','16','48','49','50','51']);
  };
  // Row-relative timer aliases are admitted only once that row reaches lha+18.
  // Other rows and unrelated raw byte windows stay lazy.
  const timerRows=new Map<number,object>();
  const timerLayout=(shadows: typeof noShadows): void=>{
    for(const [index,row] of timerRows) {
      shadows(row,['24','25','byte18','byte19','short18','field18','timer18','half018','half0018']);
      const address=0xf4+index*0x3c+0x18;
      shadows(globals,[String(address),String(address+1),
        ...[address,address+1].flatMap(offset=>[`byte${offset.toString(16)}`,`byte${offset.toString(16).toUpperCase()}`]),
        ...['half','short','field'].flatMap(prefix=>[`${prefix}${address.toString(16)}`,`${prefix}${address.toString(16).toUpperCase()}`])]);
    }
  };
  const storeCharged=(row: object,value: boolean): void=>{
    if(typeof read(row,'charged')!=='boolean') fail('charged: existing boolean source0/1 owner required');
    own(row,'charged',true);check();
    // A final observable descriptor hook cannot replace this destination with
    // an accessor, missing cell or nonboolean owner and let the store through.
    const live=primaryStoreDescriptor(row,'charged');
    if(!live || !('value' in live)) fail('charged: live own data property required');
    if(!live.writable) fail('charged: live non-writable field');
    if(typeof live.value!=='boolean') fail('charged: live boolean source0/1 owner required');
    (row as {charged:boolean}).charged=value;check();
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
  const terminalRead=(record: object,key: string): unknown=>{
    const field=primaryStoreDescriptor(record,key);
    if(!field || !('value' in field)) fail(`${key}: terminal own data property required`);
    return field.value;
  };
  const teamGuard=(table: object,row: object,index: number,keys: readonly ('byteD9'|'byteEB')[]): (()=>void)=>{
    const owner=globals,callee=keys.includes('byteEB')?'8008b480':'8008b290';
    const metadata=(shadows: typeof noShadows,records: readonly object[]): void=>{
      for(const record of records) for(const key of keys) {
        if(record!==owner) shadows(record,[key]);
        const suffix=key.slice(4),lower=suffix.toLowerCase();
        shadows(record,[`byte${lower}`,`byte0${lower}`,`byte0${suffix}`,`field${suffix}`,`field${lower}`,`global${suffix}`,`global${lower}`]);
        // Decimal offsets alias the global, not unrelated raw byte windows.
        if(record===owner) shadows(record,[key==='byteD9'?'217':'235']);
      }
      if(keys.includes('byteEB')) {
        for(const [name,record] of retained) if(name.startsWith('team row'))
          teamLayout(shadows,record,Number(name.slice(8)));
        timerLayout(shadows);
      }
    };
    return (): void=>{
      const records=[sources,globals,table,row,...retained.values(),
        ...call(()=>scheduler.getRetainedStorageOwners())];
      metadata(noShadows,[...new Set(records)]);
      // After the LAST observable inventory, native snapshots cannot call
      // application code in the declared synchronous nonproxy host domain.
      const current=[...new Set([...records,...call(()=>scheduler.getRetainedStorageOwners())])];
      const nested=current.flatMap(record=>Object.values(primaryStoreDescriptors(record)).flatMap(field=>
        'value' in field && field.value!==null && typeof field.value==='object'?[field.value as object]:[]));
      const all=[...new Set([...current,...nested])];
      if(terminalRead(sources,'scheduler')!==scheduler || scheduler.getRootRuntime()!==root ||
        root.getSpawnRuntime()!==spawns || scheduler.getAllocatorRuntime()!==allocator ||
        scheduler.getMatchGlobals()!==owner || spawns.getMatchGlobals()!==owner)
        fail(`${callee} canonical scheduler/global owner changed`);
      if(terminalRead(owner,'teamRows103')!==table || terminalRead(table,String(index))!==row)
        fail(`${callee} canonical team owner changed`);
      for(const [name,record] of retained) {
        if(name.startsWith('team row') && terminalRead(table,name.slice(8))!==record)
          fail(`${callee} retained team row owner changed`);
        if(name==='slotTeam' && terminalRead(owner,'slotTeam')!==record ||
          name==='systemGlobals' && terminalRead(sources,'systemGlobals')!==record)
          fail(`${callee} ${name}: canonical owner changed`);
      }
      metadata((record,keys)=>{
        for(const key of keys) if(primaryStoreDescriptor(record,key)!==undefined)
          fail(`${key}: competing source cell owner`);
      },all);
      for(const record of all) requireCompleteSourceActorDoubleLifecycle(record);
      check();
    };
  };
  const teamRefreshLeaf=(table: object,row: object,index: number): number=>{
    // Complete8008b290: lwz r3,-31852(r13); lbz r3,217(r3); blr.
    const owner=match(),guard=teamGuard(table,row,index,['byteD9']);
    guard();const result=byte(owner,'byteD9');guard();
    unsigned(terminalRead(owner,'byteD9'),255,'byteD9');return result;
  };
  const updateBurst=(table: object,row: object,index: number): void=>{
    // Existing recorded matched-source8008b480: lwz r3,-31852(r13);
    // lbz r3,235(r3); blr. No new archive/DOL verification is claimed.
    const owner=match(),guard=teamGuard(table,row,index,['byteD9','byteEB']);
    guard();const mask=byte(owner,'byteEB');guard();
    unsigned(terminalRead(owner,'byteEB'),255,'byteEB');
    const load=(key: string,max: number): number=>{
      guard();const value=read(row,key);guard();
      unsigned(terminalRead(row,key),max,key);return unsigned(value,max,key);
    };
    const store=(key: string,value: number): void=>{
      guard();own(row,key,true);check();guard();
      const field=primaryStoreDescriptor(row,key);
      if(!field || !('value' in field)) fail(`${key}: live own data property required`);
      if(!field.writable) fail(`${key}: live non-writable field`);
      if(key==='half18') unsigned(field.value,65535,key);
      // No observable callback between final metadata/native destination check
      // and the overwrite. This is not a source read of the old destination.
      (row as Record<string,unknown>)[key]=value;guard();
    };
    //80029da0..db4: unsigned returned r3 AND signed source row+3. Zero
    // skips the row+3 load entirely; captured values survive valid mutations.
    if(mask!==0 && (mask&s8(load('byte3',255)))===0) return;
    timerRows.set(index,row);
    const timer=s16(load('half18',65535)),next=s16(timer-1);
    store('half18',next&65535); // sth uses low16, extsh sets the branch result.
    if(next>0) fail('80029de0 reached unsupported positive burst timer floating suffix');
    store('meter',0);store('byte10',0);store('meter',0); //29dd0/dd4/dd8, not deduplicated.
  };
  const updateTeams=(): void=>{
    const table=teamTable(match()); //29d60–64 captures original row base once.
    for(let i=0;i<4;i++) {
      const row=team(table,i);refresh(row);
      if(s8(byte(row,'byte1'))<=0) continue;
      if(s8(byte(row,'byte10'))!==0) {
        storeCharged(row,false);
        if(teamRefreshLeaf(table,row,i)!==0) continue; // Full returned r3,29d94..98.
        updateBurst(table,row,i);continue;
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
  const randomByte=(mass: object,where: string): number=>{
    const supplied=Object.getOwnPropertyDescriptor(mass,'rngState');check();
    if(supplied===undefined)fail(`${where} reached mandatory800055fc RNG predecessor`);
    if(read(sources,'massPreparation')!==mass || retained.get('massPreparation')!==mass)
      fail('RNG canonical mass owner changed');
    const state=retain('mass rngState',read(mass,'rngState')),
      aliases=['c6','c7','bytec6','bytec7','198','199','seed','state'];
    const guard=():void=>{
      noShadows(state,aliases);check();
      if(terminalRead(sources,'massPreparation')!==mass || terminalRead(mass,'rngState')!==state ||
        retained.get('mass rngState')!==state)fail('RNG canonical owner changed');
      for(const key of aliases)if(primaryStoreDescriptor(state,key)!==undefined)fail(`${key}: competing source cell owner`);
      check();
    };
    const load=(key:string):number=>{guard();const value=byte(state,key);guard();return value;};
    const store=(key:string,value:number):void=>{
      guard();own(state,key,true);guard();const destination=primaryStoreDescriptor(state,key);
      if(!destination || !('value'in destination))fail(`${key}: live own data property required`);
      if(!destination.writable)fail(`${key}: live non-writable field`);
      (state as Record<string,unknown>)[key]=value;guard();
    };
    // Complete existing055fc: captured high/low, high store before low store.
    const high=load('byte804360c7'),low=load('byte804360c6');
    const nextHigh=(((high*256+low)*3)>>8)&255,nextLow=(low+nextHigh)&255;
    store('byte804360c7',nextHigh);store('byte804360c6',nextLow);return nextLow;
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
    const status=spawns.getPrehookRuntime().getStatusRuntime(), stage=root.getStageRuntime(), world=spawns.getWorldRuntime();
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
    // Capture each current passenger once. Nonzero83 remains completely lazy
    // about its slot, Borg mass, contact and further chain.
    const passenger83=(id: symbol,actor: object,callerBorg: object,originalGuard: ()=>void)=>{
      const pointerAliases=['linkedOwner1E4','pointer1e4','pointer1E4','field1e4','field1E4',
        'byte1e4','byte1e5','byte1e6','byte1e7','byte1E4','byte1E5','byte1E6','byte1E7','484','485','486','487'];
      const callerWorld=call(()=>world.getActorBinding(id));
      const pointerMetadata=(shadows: typeof noShadows): void=>{
        for(const candidate of new Set([sources,globals,actor,callerWorld,callerBorg,...retained.values(),
          ...allocator.getSourceOwners(id)])) {
          // Another genuine actor's further-chain pointer is not this cell.
          if(candidate!==actor) shadows(candidate,['linkedOwner1e4']);
          shadows(candidate,pointerAliases.slice(0,-4));
          // Allocation byte buffers legitimately own numeric offset484.
          if(candidate===actor || candidate===callerWorld || candidate===callerBorg)
            shadows(candidate,pointerAliases.slice(-4));
        }
      };
      const terminalShadows=(owner: object,keys: readonly string[]): void=>{
        for(const key of keys) if(primaryStoreDescriptor(owner,key)!==undefined)
          fail(`${key}: competing source cell owner`);
      };
      const supplied=Object.getOwnPropertyDescriptor(actor,'linkedOwner1e4');check();
      if(supplied===undefined) fail('80053b30 mass propagation reached unsupported actual pointer1e4 ownership: explicit linkedOwner1e4 required');
      // Exactly one actual lwz capture, never a collision binding or symbol cast.
      if(!('value' in supplied)) fail('linkedOwner1e4: own data property required');
      pointerMetadata(noShadows);
      const pointer=record(supplied.value,'53b30 captured linkedOwner1e4');
      const targetId=call(()=>allocator.getPointerIdentity(pointer)),targetActor=actual(targetId);
      const owner=record(call(()=>allocator.getActorBinding(targetId)),'53b30 canonical passenger allocation83');
      const targetWorld=call(()=>world.getActorBinding(targetId));
      const byteMetadata=(shadows: typeof noShadows): void=>{
        for(const candidate of new Set([targetActor,targetWorld,...allocator.getSourceOwners(targetId)])) {
          if(candidate!==owner) shadows(candidate,['byte83']);
          shadows(candidate,['eligibility83','groupEligibility83','field83']);
          if(candidate===targetActor || candidate===targetWorld || candidate===owner) shadows(candidate,['131']);
        }
      };
      const finish=(): void=>{
        // Native terminal descriptors cannot invoke the observer that just ran.
        // Pointer and byte values remain captured even if their live cells change.
        if(terminalRead(sources,'scheduler')!==scheduler || scheduler.getAllocatorRuntime()!==allocator ||
          scheduler.getRootRuntime()!==root || root.getSpawnRuntime()!==spawns ||
          spawns.getWorldRuntime()!==world || terminalRead(sources,'massPreparation')!==mass ||
          allocator.getPointerTarget(id)!==actor || allocator.getActualActor(id)!==actor ||
          status.getActualActor(id)!==actor || status.getActualBorg(id)!==callerBorg ||
          world.getActualActor(id)!==actor || world.getActorBinding(id)!==callerWorld ||
          targetActor!==pointer || allocator.getPointerTarget(targetId)!==targetActor ||
          allocator.getActualActor(targetId)!==targetActor || allocator.getActorBinding(targetId)!==owner ||
          world.getActualActor(targetId)!==targetActor || world.getActorBinding(targetId)!==targetWorld)
          fail('53b30 terminal canonical caller/passenger owner changed');
        terminalRead(actor,'linkedOwner1e4');terminalRead(owner,'byte83');
        pointerMetadata(terminalShadows);byteMetadata(terminalShadows);
        requireCompleteSourceActorDoubleLifecycle(actor);requireCompleteSourceActorDoubleLifecycle(targetActor);
        allocator.assertActorComplete(id);allocator.assertActorComplete(targetId);originalGuard();check();
      };
      const guard=(): void=>{
        check();call(()=>allocator.assertActorComplete(id));call(()=>allocator.assertActorComplete(targetId));
        if(targetActor!==pointer || call(()=>allocator.getActualActor(targetId))!==targetActor ||
          call(()=>world.getActualActor(targetId))!==targetActor ||
          call(()=>allocator.getPointerTarget(targetId))!==targetActor ||
          call(()=>allocator.getActorBinding(targetId))!==owner)
          fail('53b30 canonical passenger allocator/world owner differs');
        if(!Object.isSealed(owner) || owner===targetActor || [...retained.values()].includes(owner) ||
          [...massActors.values()].includes(owner) || [...borgs.values()].includes(owner))
          fail('53b30 passenger allocation83 storage alias');
        pointerMetadata(noShadows);byteMetadata(noShadows);finish();
      };
      guard();const captured=byte(owner,'byte83');guard();
      return {captured,targetId,targetActor,owner,callerBorg,guard,finish};
    };
    const accumulatePassenger=(selected: ReturnType<typeof passenger83>,original: {
      id: symbol; actor: object; worldBinding: object; allocation: object;
    }): {contact: number; owner: object}=>{
      const {id:originalId,actor}=original;
      const {targetId,targetActor}=selected;
      let massBorg:object|undefined,slotReached=false,massReached=false,originalMassReached=false,contactReached=false;
      const terminalShadows=(owner: object,keys: readonly string[]): void=>{
        for(const key of keys) if(primaryStoreDescriptor(owner,key)!==undefined)
          fail(`${key}: competing source cell owner`);
      };
      const metadata=(shadows: typeof noShadows): void=>{
        const actuals=world.getRetainedActorOwners(),knownBorgs=[...borgs.values()];
        // Inspect reached roles only: another genuine unvisited Borg may
        // already own204, without being a shadow of this passenger.
        const records=new Set([sources,globals,mass,actor,targetActor,selected.owner,
          world.getActorBinding(targetId),original.worldBinding,original.allocation,
          ...allocator.getSourceOwners(originalId),...retained.values(),...allocator.getSourceOwners(targetId),
          ...(massBorg===undefined?[]:[status.getActorBinding(targetId),status.getWorldBinding(targetId),
            status.getMappingActor(targetId),status.getAttributeBinding(targetId),status.getMovementBinding(targetId)]),
          ...knownBorgs]);
        for(const owner of records) {
          if(slotReached) {
            if(!actuals.includes(owner)) shadows(owner,['slot']);
            shadows(owner,['slot3e4','byte3e4','byte3E4','field3e4','field3E4']);
            if(owner===targetActor) shadows(owner,['996']);
          }
          if(massReached) {
            if(!knownBorgs.includes(owner)) shadows(owner,['sourceArrowMass204']);
            shadows(owner,['mass204','field204','float204','byte204','byte205','byte206','byte207']);
            if(owner===targetActor || owner===massBorg) shadows(owner,['516','517','518','519']);
          }
          if(originalMassReached) {
            if(!actuals.includes(owner)) shadows(owner,['mass208']);
            shadows(owner,['field208','float208','byte208','byte209','byte20a','byte20b','byte20A','byte20B']);
            if(owner===actor || owner===massBorg) shadows(owner,['520','521','522','523']);
          }
          if(contactReached) {
            if(!actuals.includes(owner)) shadows(owner,['supportContact1db']);
            shadows(owner,['byte1db','byte1DB','field1db','field1DB']);
            if(owner===targetActor) shadows(owner,['475']);
          }
        }
      };
      const finish=(): void=>{
        selected.finish();
        for(const [name,owner] of retained) {
          if(name.startsWith('mass ') && name!=='mass actorSlots' && name!=='mass physical identities' &&
            terminalRead(mass,name.slice(5))!==owner)
            fail(`53b30 terminal ${name} owner changed`);
        }
        if(terminalRead(block,'identities')!==ids) fail('53b30 terminal physical identities owner changed');
        if(massBorg!==undefined && (status.getActualActor(targetId)!==targetActor ||
          status.getActualBorg(targetId)!==massBorg || massBorg===targetActor ||
          [...retained.values()].includes(massBorg) || [...massActors.values()].includes(massBorg) ||
          [...borgs].some(([id,owner])=>id!==targetId && owner===massBorg)))
          fail('53b30 terminal canonical passenger Borg owner changed or aliases storage');
        metadata(terminalShadows);
        if(slotReached) terminalRead(targetActor,'slot');
        if(massReached) terminalRead(massBorg!,'sourceArrowMass204');
        if(originalMassReached) terminalRead(actor,'mass208');
        if(contactReached) terminalRead(targetActor,'supportContact1db');
        requireCompleteSourceActorDoubleLifecycle(targetActor);
        requireCompleteSourceActorDoubleLifecycle(selected.callerBorg);
        if(massBorg!==undefined) requireCompleteSourceActorDoubleLifecycle(massBorg);
        check();
      };
      const guard=(): void=>{selected.guard();metadata(noShadows);selected.guard();finish();};
      //53cc8/53d24: raw slot is captured BEFORE either floating load. The
      // signed address and sparse local byte are used only AFTER both loads.
      slotReached=true;guard();const rawSlot=byte(targetActor,'slot');guard();
      massBorg=borg(targetId,targetActor);massReached=true;
      guard();const passengerMass=f(massBorg,'sourceArrowMass204');guard();
      originalMassReached=true;guard();const originalMass=f(actor,'mass208');guard();
      const slot=s8(rawSlot),counter=passengerCounts[slot];
      if(slot<0 || slot>=6 || counter===undefined)
        fail('53b30 reached uninitialized or out-of-domain local passenger count');
      const old=unsigned(counter,255,'local passenger count');
      const sum=addSourceFloat32(passengerMass,originalMass); // overflow before BOTH stores.
      guard();passengerCounts[slot]=(old+1)&255; //53ce4/53d40: unsigned lbzx, low-byte stb.
      own(massBorg,'sourceArrowMass204',true);guard();
      const destination=primaryStoreDescriptor(massBorg,'sourceArrowMass204');
      if(!destination || !('value' in destination)) fail('sourceArrowMass204: live own data property required');
      if(!destination.writable) fail('sourceArrowMass204: live non-writable field');
      (massBorg as {sourceArrowMass204:number}).sourceArrowMass204=sum;guard();
      contactReached=true;guard();const contact=byte(targetActor,'supportContact1db');guard();
      return {contact,owner:massBorg};
    };
    // A private identity-only snapshot bounds host work, not source depth.
    // Later registrations remain lazy: a newly reached nonzero83 still exits.
    const traversalActors=new Set<object>(world.getRetainedActorOwners());
    // Three original unrolled pairs. No active/lifecycle test or pointer
    // snapshot: every one of the six table cells is loaded when reached.
    for(let index=0;index<6;index++) {
      const id=slotPointer(index),actor=actual(id);
      if(id===null) fail('53b30 null actor'); // narrowed after reached dereference.
      const owner=borg(id,actor),total=f(owner,'sourceArrowMass204'),massValue=f(actor,'mass208');
      const accumulated=addSourceFloat32(total,massValue);
      own(owner,'sourceArrowMass204',true);check();
      // A prior passenger skip exposes the next actual table half. Refuse a
      // destination changed by the last observable preflight before invoking
      // any setter or recreating a deleted cell. Source operands stay captured.
      const destination=primaryStoreDescriptor(owner,'sourceArrowMass204');
      if(!destination || !('value' in destination)) fail('sourceArrowMass204: live own data property required');
      if(!destination.writable) fail('sourceArrowMass204: live non-writable field');
      (owner as {sourceArrowMass204:number}).sourceArrowMass204=accumulated;check();
      if(s8(byte(actor,'supportContact1db'))!==0) {
        const original={id,actor,owner,worldBinding:world.getActorBinding(id),
          allocation:allocator.getActorBinding(id)};
        // r8 remains guarded after r9 advances, including a later nonzero83
        // early exit. These native descriptor checks add no source scalar loads.
        const originalGuard=(): void=>{
          if(allocator.getPointerTarget(id)!==actor || allocator.getActualActor(id)!==actor ||
            allocator.getActorBinding(id)!==original.allocation ||
            world.getActualActor(id)!==actor || world.getActorBinding(id)!==original.worldBinding ||
            status.getActualActor(id)!==actor || status.getActualBorg(id)!==owner ||
            owner===actor || [...retained.values()].includes(owner) || [...massActors.values()].includes(owner) ||
            [...borgs].some(([other,borgOwner])=>other!==id && borgOwner===owner))
            fail('53b30 terminal canonical original contribution owner changed or aliases storage');
          for(const record of new Set([actor,owner,original.worldBinding,original.allocation,
            ...allocator.getSourceOwners(id)])) {
            const aliases=['mass204','field204','float204','byte204','byte205','byte206','byte207',
              'field208','float208','byte208','byte209','byte20a','byte20b','byte20A','byte20B'];
            if(record!==actor) aliases.push('mass208');
            if(record!==owner) aliases.push('sourceArrowMass204');
            if(record===actor || record===owner) aliases.push('516','517','518','519','520','521','522','523');
            for(const key of aliases) if(primaryStoreDescriptor(record,key)!==undefined)
              fail(`${key}: competing source cell owner`);
          }
          terminalRead(actor,'mass208');terminalRead(owner,'sourceArrowMass204');
          requireCompleteSourceActorDoubleLifecycle(actor);requireCompleteSourceActorDoubleLifecycle(owner);
          allocator.assertActorComplete(id);check();
        };
        let currentId=id,currentActor=actor,currentBorg=owner;
        // Do not seed with the original: a first self-passenger update is
        // source-visible and is admitted before a subsequent repeat refusal.
        const processed=new Set<object>();
        for(;;) {
          const selected=passenger83(currentId,currentActor,currentBorg,originalGuard);
          if(s8(selected.captured)!==0) break;
          if(!traversalActors.has(selected.targetActor))
            fail('53b30 unsupported host-domain passenger outside captured registry');
          if(processed.has(selected.targetActor))
            fail('53b30 unsupported host-domain repeated zero83 passenger');
          processed.add(selected.targetActor);
          const accumulated=accumulatePassenger(selected,original);
          if(s8(accumulated.contact)===0) break;
          currentId=selected.targetId;currentActor=selected.targetActor;currentBorg=accumulated.owner;
        }
      }
    }
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
    const worlds=new Map<symbol,object>();
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
    let selected=(randomByte(mass,'80053d60')>>>2)%6;
    const direction=(randomByte(mass,'80053d80')&8)!==0?1:-1;
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
    //Genuine53b30 return for the fully reached bounded propagation path.

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
    const primaryDistance=(id: symbol,actor: object,dispatch: SourceActorTargetDispatchRuntime): void=>{
      const binding=command(id,actor,false);
      const basicGuard=(): void=>{
        check();requireCompleteSourceActorDoubleLifecycle(actor);allocator.assertActorComplete(id);check();
        admission().assertActorComplete(id);check();
        if(root.getSpawnRuntime()!==spawns || spawns.getWorldRuntime()!==world ||
          world.getActualActor(id)!==actor || admission().getActorBinding(id)!==binding)
          fail('6ae60 primary canonical actor/command/world changed');
      };
      const load=(owner: object,key: string): unknown=>{const value=read(owner,key);basicGuard();return value;};
      let data: object|undefined;
      let estimatorProcessor: object|undefined,estimatorProcessorSource: object|undefined;
      let nullDirection=false,secondaryReached=false,ccReached=false,aimReached=false,c8Reached=false;
      let operandsGuard=basicGuard;
      let terminalRuntime: SourceActorCommandAdmissionRuntime|undefined;
      let terminalRecords: object[]=[],terminalActors: readonly object[]=[];
      let primaryReached=false,primaryProvider: object|undefined,primaryObject: symbol|undefined;
      let primaryProviderReferences: Map<object,Set<string>>|undefined;
      let terminalAim: object|undefined,terminalPosition: object|undefined,terminalSelected: object|undefined;
      const distanceKeys=['targetDistance758','horizontalDistance75c','targetDistance760','horizontalDistance764'] as const;
      const secondaryAliases=['field760','field764','float760','float764',
        ...Array.from({length:8},(_,index)=>0x760+index).flatMap(offset=>
          [String(offset),'byte'+offset.toString(16),'byte'+offset.toString(16).toUpperCase()])];
      const aimAliases=['field518','field51c','field51C','field520','position518','targetPosition518',
        ...Array.from({length:12},(_,index)=>0x518+index).flatMap(offset=>
          [String(offset),'byte'+offset.toString(16),'byte'+offset.toString(16).toUpperCase()])];
      const positionAliases20=['position20','field20','field24','field28',
        ...Array.from({length:12},(_,index)=>0x20+index).flatMap(offset=>
          [String(offset),'byte'+offset.toString(16),'byte'+offset.toString(16).toUpperCase()])];
      const selectedAliases=['field50c','field50C','field510','field514','position50c','targetPosition50c',
        ...Array.from({length:12},(_,index)=>0x50c+index).flatMap(offset=>
          [String(offset),'byte'+offset.toString(16),'byte'+offset.toString(16).toUpperCase()])];
      const shadowKeys=['field758','field75c','field75C','float758','float75c','float75C',
        ...Array.from({length:8},(_,index)=>0x758+index).flatMap(offset=>
          [String(offset),'byte'+offset.toString(16),'byte'+offset.toString(16).toUpperCase()])];
      const distanceGuard=(): void=>{
        operandsGuard();
        if(estimatorProcessor!==undefined && call(()=>root.getVectorProcessorProfile())!==estimatorProcessor)
          fail('secondary estimator processor profile owner changed');
        const commandRuntime=admission(),actionRuntime=commandRuntime.getActionRuntime();
        terminalRuntime=commandRuntime;
        if(data!==undefined && commandRuntime.getData()!==data) fail('6ae60 primary shared data owner changed');
        const actualActors=world.getRetainedActorOwners();
        if(!actualActors.includes(actor)) fail('6ae60 primary actual actor owner missing');
        const canonical=[sources,globals,root,scheduler,allocator,spawns,world,binding,
          commandRuntime.getGlobal(),commandRuntime.getWorldBinding(id),commandRuntime.getStatusBinding(id),
          commandRuntime.getMappingActor(id),commandRuntime.getAttributeBinding(id),commandRuntime.getChargeBinding(id),
          commandRuntime.getActionBinding(id),commandRuntime.getCueBinding(id),commandRuntime.getDispatchBinding(id),
          commandRuntime.getStartBinding(id),commandRuntime.getStreamBinding(id),...retained.values(),
          ...world.getRetainedMatrixOwners(),...commandRuntime.getKnownStorageOwners(),
          ...actionRuntime.getRetainedStorageOwners(),...status.getRetainedStorageOwners(),
          ...allocator.getRetainedStorageOwners(),root.getDrawList(),...dispatch.getRetainedStorageOwners(),
          ...root.getRetainedStorageOwners(),...scheduler.getRetainedStorageOwners()];
        // Host metadata inventories, not extra source scalar or target reads.
        const records=[...new Set([...canonical,...actualActors,...massActors.values(),...(data?[data]:[])])];
        terminalRecords=records;terminalActors=actualActors;
        const snapshots=records.map(owner=>({owner,fields:Object.getOwnPropertyDescriptors(owner)}));basicGuard();
        const nested=snapshots.flatMap(({fields})=>Object.values(fields).flatMap(p=>
          'value' in p && p.value!==null && typeof p.value==='object' ? [p.value as object]:[]));
        const owners=[...new Set([...records,...nested])];
        if(data!==undefined && (actualActors.includes(data) || [sources,globals,root,scheduler,allocator,spawns,world,binding,
          commandRuntime.getWorldBinding(id),commandRuntime.getStatusBinding(id),commandRuntime.getMappingActor(id),
          commandRuntime.getAttributeBinding(id),commandRuntime.getChargeBinding(id),commandRuntime.getActionBinding(id),
          commandRuntime.getCueBinding(id),commandRuntime.getDispatchBinding(id),commandRuntime.getStartBinding(id),
          commandRuntime.getStreamBinding(id),...retained.values(),...world.getRetainedMatrixOwners()].includes(data)))
          fail('6ae60 primary data aliases canonical source storage');
        for(const owner of owners) {
          const fields=Object.getOwnPropertyDescriptors(owner);basicGuard();
          for(const key of (secondaryReached?distanceKeys:distanceKeys.slice(0,2))) if(!actualActors.includes(owner) && fields[key]!==undefined)
            fail(`${key}: competing primary distance storage`);
          for(const key of shadowKeys) if(fields[key]!==undefined)
            fail(`${key}: competing primary distance storage alias`);
          for(const key of ['float80437658','float80437678','double80437660','double80437668']) if(owner!==data && fields[key]!==undefined)
            fail(`${key}: competing primary shared data storage`);
          if(ccReached) {
            if(!actualActors.includes(owner) && fields.visibilityTarget!==undefined)
              fail('visibilityTarget: competing secondary source storage');
            for(const key of ['pointerCC','pointercc','fieldcc','fieldCC','bytecc','bytecd','bytece','bytecf',
              'byteCC','byteCD','byteCE','byteCF']) if(fields[key]!==undefined)
              fail(`${key}: competing secondary pointer alias`);
            // These offsets name actual+cc only on this actor. Unrelated raw
            // byte windows may legitimately have numeric entries at204..207.
            if(owner===actor) for(const key of ['204','205','206','207']) if(fields[key]!==undefined)
              fail(`${key}: competing secondary pointer alias`);
          }
          if(secondaryReached) {
            for(const key of secondaryAliases) if(fields[key]!==undefined)
              fail(`${key}: competing secondary distance alias`);
            if(!actualActors.includes(owner) && fields.aimOrigin518!==undefined)
              fail('aimOrigin518: competing secondary aim storage');
          }
          if(c8Reached) {
            if(fields.pointerc8!==undefined && ![...commandOwners.values()].some(entry=>entry.binding===owner))
              fail('pointerc8: competing secondary canonical source storage');
            for(const key of ['pointerC8','fieldc8','fieldC8','bytec8','bytec9','byteca','bytecb',
              'byteC8','byteC9','byteCA','byteCB']) if(fields[key]!==undefined)
              fail(`${key}: competing secondary pointerc8 alias`);
            if(owner===actor) for(const key of ['pointerc8','200','201','202','203']) if(fields[key]!==undefined)
              fail(`${key}: competing secondary pointerc8 storage`);
          }
          if(aimReached) for(const key of aimAliases) if(fields[key]!==undefined)
            fail(`${key}: competing secondary aim storage alias`);
          if(nullDirection) {
            if(owner!==data && fields.float80437078!==undefined)
              fail('float80437078: competing null-direction shared data storage');
            if(!actualActors.includes(owner) && fields.heading!==undefined)
              fail('heading: competing null-direction source storage');
            for(const key of ['field72','short72','yaw72','byte72','byte73']) if(fields[key]!==undefined)
              fail(`${key}: competing null-direction source alias`);
          }
        }
        operandsGuard();
      };
      const terminalPrimary=(): void=>{
        if(!primaryReached) return;
        // Native descriptors close the last public metadata-observer window.
        // No c8/cc/null-direction state belongs to this branch.
        const nativeRead=(owner: object,key: string): unknown=>{
          const p=primaryStoreDescriptor(owner,key);
          if(!p || !('value' in p)) fail(`${key}: primary terminal own data property required`);
          return p.value;
        };
        const runtime=terminalRuntime;
        if(!runtime || nativeRead(sources,'targetPreparation')!==target || nativeRead(target,'admission')!==runtime ||
          nativeRead(sources,'scheduler')!==scheduler || spawns.getAdmissionRuntime()!==runtime ||
          runtime.getActualActor(id)!==actor || runtime.getActorBinding(id)!==binding ||
          runtime.getData()!==data || world.getActualActor(id)!==actor || status.getActualActor(id)!==actor)
          fail('primary terminal canonical actor/admission/data owner changed');
        if(terminalPosition===undefined || nativeRead(actor,'pos')!==terminalPosition ||
          world.getPositionOwner(id)!==terminalPosition) fail('primary terminal position20 owner changed');
        if(primaryProvider===undefined || primaryObject===undefined ||
          allocator.getPointerIdentity(primaryProvider)!==primaryObject || allocator.getObject(primaryObject)!==primaryProvider)
          fail('primary terminal captured OBJECT provider changed');
        if(estimatorProcessor!==undefined && (estimatorProcessorSource===undefined ||
          nativeRead(estimatorProcessorSource,'processor')!==estimatorProcessor))
          fail('primary terminal processor profile owner changed');
        const snapshots=terminalRecords.map(owner=>({owner,fields:primaryStoreDescriptors(owner)}));
        const nested=snapshots.flatMap(({fields})=>Object.values(fields).flatMap(p=>
          'value' in p && p.value!==null && typeof p.value==='object'?[p.value as object]:[]));
        for(const owner of new Set([...terminalRecords,...nested])) {
          const fields=primaryStoreDescriptors(owner);
          const ban=(keys: readonly string[]): void=>{
            for(const key of keys) if(fields[key]!==undefined) fail(`${key}: competing primary terminal storage alias`);
          };
          if(!terminalActors.includes(owner)) ban(distanceKeys.slice(0,2));
          ban(shadowKeys);
          if(owner===actor) ban(positionAliases20);
          if(owner!==data) ban(['float80437658','float80437678','double80437660','double80437668']);
          for(const [key,p] of Object.entries(fields)) if('value' in p) {
            if(estimatorProcessor!==undefined && p.value===estimatorProcessor &&
              !(owner===estimatorProcessorSource && key==='processor'))
              fail('primary terminal processor aliases canonical reference');
            if(owner!==terminalPosition && p.value===terminalPosition && !(owner===actor && key==='pos'))
              fail('primary terminal position20 aliases canonical reference');
            if(owner!==primaryProvider && p.value===primaryProvider &&
              !primaryProviderReferences?.get(owner)?.has(key) && !(owner===binding && key==='pointer504'))
              fail('primary terminal captured provider aliases canonical reference');
          }
        }
        check();requireCompleteSourceActorDoubleLifecycle(actor);
        runtime.assertActorComplete(id);allocator.assertActorComplete(id);check();
      };
      const terminalSecondary=(): void=>{
        if(!c8Reached) return;
        // Public metadata observers have finished. Rebuild nested ownership
        // from native descriptors, so a final observer cannot add an alias or
        // replace a canonical link and let the pending store slip through.
        // These are host records, not extra loads of captured source scalars.
        const nativeRead=(owner: object,key: string): unknown=>{
          const field=primaryStoreDescriptor(owner,key);
          if(!field || !('value' in field)) fail(`${key}: terminal own data property required`);
          return field.value;
        };
        const runtime=terminalRuntime;
        if(!runtime || nativeRead(sources,'targetPreparation')!==target || nativeRead(target,'admission')!==runtime ||
          nativeRead(sources,'scheduler')!==scheduler || spawns.getAdmissionRuntime()!==runtime ||
          runtime.getActualActor(id)!==actor || runtime.getActorBinding(id)!==binding ||
          runtime.getData()!==data || world.getActualActor(id)!==actor || status.getActualActor(id)!==actor)
          fail('secondary terminal canonical actor/admission/data owner changed');
        if(estimatorProcessor!==undefined && (estimatorProcessorSource===undefined ||
          nativeRead(estimatorProcessorSource,'processor')!==estimatorProcessor))
          fail('secondary terminal processor profile owner changed');
        if(terminalAim!==undefined && nativeRead(actor,'aimOrigin518')!==terminalAim)
          fail('secondary terminal aimOrigin518 owner changed');
        if(terminalSelected!==undefined && nativeRead(actor,'lockTarget')!==terminalSelected)
          fail('secondary terminal selected position owner changed');
        if(terminalPosition!==undefined && (nativeRead(actor,'pos')!==terminalPosition || world.getPositionOwner(id)!==terminalPosition))
          fail('secondary terminal position20 owner changed');
        const selectedAliasOwners=[actor,binding,terminalSelected,data,runtime.getGlobal(),runtime.getWorldBinding(id),
          runtime.getStatusBinding(id),runtime.getMappingActor(id),runtime.getAttributeBinding(id),runtime.getChargeBinding(id),
          runtime.getActionBinding(id),runtime.getCueBinding(id),runtime.getDispatchBinding(id),runtime.getStartBinding(id),runtime.getStreamBinding(id)];
        const snapshots=terminalRecords.map(owner=>({owner,fields:primaryStoreDescriptors(owner)}));
        const nested=snapshots.flatMap(({fields})=>Object.values(fields).flatMap(p=>
          'value' in p && p.value!==null && typeof p.value==='object'?[p.value as object]:[]));
        for(const owner of new Set([...terminalRecords,...nested])) {
          const fields=primaryStoreDescriptors(owner);
          const ban=(keys: readonly string[]): void=>{
            for(const key of keys) if(fields[key]!==undefined) fail(`${key}: competing secondary terminal storage alias`);
          };
          if(!terminalActors.includes(owner)) ban([...distanceKeys,'visibilityTarget','aimOrigin518','heading']);
          ban([...shadowKeys,...secondaryAliases,...aimAliases,'pointerCC','pointercc','fieldcc','fieldCC',
            'bytecc','bytecd','bytece','bytecf','byteCC','byteCD','byteCE','byteCF',
            'pointerC8','fieldc8','fieldC8','bytec8','bytec9','byteca','bytecb','byteC8','byteC9','byteCA','byteCB',
            'field72','short72','yaw72','byte72','byte73']);
          if(fields.pointerc8!==undefined && ![...commandOwners.values()].some(entry=>entry.binding===owner))
            fail('pointerc8: competing secondary terminal canonical storage');
          if(owner===actor) ban(['200','201','202','203','204','205','206','207']);
          if(owner===actor && terminalPosition!==undefined) ban(positionAliases20);
          if(terminalSelected!==undefined && selectedAliasOwners.includes(owner)) {
            ban(selectedAliases);if(owner!==actor) ban(['lockTarget']);
            if(owner===terminalSelected) ban(['active0','team','byte502','pointer504','pointer508','descriptor4b0',
              'lifecycle18','half80436242','count804361a0']);
          }
          if(owner!==data) ban(['float80437658','float80437678','float80437078','double80437660','double80437668']);
          for(const [key,p] of Object.entries(fields)) if('value' in p) {
            if(estimatorProcessor!==undefined && p.value===estimatorProcessor &&
              !(owner===estimatorProcessorSource && key==='processor'))
              fail('secondary terminal processor aliases canonical reference');
            if(terminalAim!==undefined && owner!==terminalAim && p.value===terminalAim && !(owner===actor&&key==='aimOrigin518'))
              fail('secondary terminal aimOrigin518 aliases canonical reference');
            if(terminalSelected!==undefined && owner!==terminalSelected && p.value===terminalSelected && !(owner===actor&&key==='lockTarget'))
              fail('secondary terminal selected position aliases canonical reference');
            if(terminalPosition!==undefined && owner!==terminalPosition && p.value===terminalPosition && !(owner===actor&&key==='pos'))
              fail('secondary terminal position20 aliases canonical reference');
          }
        }
        check();requireCompleteSourceActorDoubleLifecycle(actor);
        runtime.assertActorComplete(id);allocator.assertActorComplete(id);check();
      };
      const sourceFloat=(value: unknown,key: string): number=>{
        if(typeof value!=='number' || !Number.isFinite(value) || !Object.is(value,Math.fround(value)))
          fail(`${key}: finite exact source float32 required`);return value;
      };
      const constant=(key: 'float80437658'|'float80437678',expected: number,address: string): number=>{
        if(data===undefined) data=record(admission().getData(),'6ae60 primary shared data');
        distanceGuard();
        const field=Object.getOwnPropertyDescriptor(data,key);distanceGuard();
        if(!field || !('value' in field)) fail(`${address} ${key}: own data property required`);
        const value=sourceFloat(field.value,key);
        if(!Object.is(value,expected)) fail(`${address} ${key}: differs from authenticated source bits`);
        return value;
      };
      const store=(key: typeof distanceKeys[number],value: number): void=>{
        distanceGuard();
        const field=Object.getOwnPropertyDescriptor(actor,key);distanceGuard();
        if(!field || !('value' in field)) fail(`${key}: own data property required`);
        if(!field.writable) fail(`${key}: non-writable field`);
        // Host admission may discover a changed descriptor. Do not turn a
        // reached plain store into property creation or an accessor callback.
        const current=Object.getOwnPropertyDescriptors(actor)[key];distanceGuard();
        if(!current || !('value' in current)) fail(`${key}: own data property changed before store`);
        if(!current.writable) fail(`${key}: non-writable field before store`);
        terminalSecondary();terminalPrimary();
        const live=primaryStoreDescriptor(actor,key);
        if(!live || !('value' in live)) fail(`${key}: live own data property required before store`);
        if(!live.writable) fail(`${key}: live non-writable field before store`);
        // No application callback occurs between this final intrinsic and the
        // plain own-data overwrite. The old scalar is never validated or used.
        (actor as Record<string,unknown>)[key]=value;distanceGuard();
      };
      const preparePosition=(): {position: object;guard: ()=>void}=>{
      noShadows(actor,positionAliases20);
      const position=record(load(actor,'pos'),'6ae60 actual position20');
      terminalPosition=position;
      if(Array.isArray(position)) fail('6ae60 position20 requires ordinary source vector');
      if(call(()=>world.getPositionOwner(id))!==position) fail('6ae60 actual position record changed');
      const positionGuard=(): void=>{
        basicGuard();
        const field=Object.getOwnPropertyDescriptor(actor,'pos');check();
        if(!field || !('value' in field) || field.value!==position || world.getPositionOwner(id)!==position)
          fail('6ae60 actual position record changed');
        const commandRuntime=admission(),actionRuntime=commandRuntime.getActionRuntime();
        const structured=[sources,globals,root,scheduler,allocator,spawns,world,actor,binding,
          commandRuntime.getGlobal(),commandRuntime.getData(),commandRuntime.getWorldBinding(id),
          commandRuntime.getStatusBinding(id),commandRuntime.getMappingActor(id),commandRuntime.getAttributeBinding(id),
          commandRuntime.getChargeBinding(id),commandRuntime.getActionBinding(id),commandRuntime.getCueBinding(id),
          commandRuntime.getDispatchBinding(id),commandRuntime.getStartBinding(id),commandRuntime.getStreamBinding(id),
          ...retained.values(),...massActors.values(),...world.getRetainedMatrixOwners(),
          ...commandRuntime.getKnownStorageOwners(),...actionRuntime.getRetainedStorageOwners(),
          ...status.getRetainedStorageOwners(),...allocator.getRetainedStorageOwners()];
        //Only this actor's inline pos reference is admitted. The vector cannot
        //also be canonical bytes, helper data, another actor or another vector.
        const references=[...structured,root.getDrawList(),...dispatch.getRetainedStorageOwners(),
          ...root.getRetainedStorageOwners(),...scheduler.getRetainedStorageOwners()];check();
        for(const owner of references) {
          if(owner===position) continue;
          const fields=Object.getOwnPropertyDescriptors(owner);check();
          for(const [key,p] of Object.entries(fields)) if('value' in p && p.value===position && !(owner===actor && key==='pos'))
            fail('6ae60 position20 aliases canonical source reference');
        }
        if(structured.includes(position))
          fail('6ae60 position20 aliases canonical source storage');
        basicGuard();
      };
        positionGuard();return {position,guard:positionGuard};
      };
      for(const owner of [actor,binding]) noShadows(owner,['field504','field508',
        ...Array.from({length:8},(_,index)=>0x504+index).flatMap(offset=>
          [String(offset),'byte'+offset.toString(16),'byte'+offset.toString(16).toUpperCase()])]);
      noShadows(actor,['pointer504','pointer508']);
      //af8c compares this captured pointer only. It does not dereference the
      //target, infer eligibility, or recover the OBJECT from that target actor.
      const targetPointer=load(binding,'pointer508');
      if(targetPointer===null) {
        const missing=constant('float80437678',20000,'8006b180');
        store('horizontalDistance75c',missing);store('targetDistance758',missing);
        nullDirection=true;distanceGuard();
        const heading=(): number=>{
          noShadows(actor,['field72','short72','yaw72','114','115','byte72','byte73']);
          const word=load(actor,'heading');distanceGuard();
          return unsigned(word,65535,'heading')<<16>>16;
        };
        const trig=(angle: number,cosine: boolean): number=>{
          const profile=call(()=>admission().getShortTrigProfile());distanceGuard();
          return readSourceShortTrig(angle,cosine,data!,profile,distanceGuard);
        };
        const horizontal=(): number=>{
          const value=read(actor,'horizontalDistance75c');distanceGuard();
          return sourceFloat(value,'horizontalDistance75c');
        };
        let selected: object|undefined;
        const selectedGuard=(): void=>{
          basicGuard();
          if(selected!==undefined) {
            if(call(()=>dispatch.getSelectedPositionOwner(id))!==selected)
              fail('6ae60 selected position canonical owner changed');
            const owners=[sources,globals,data!,...retained.values(),...massActors.values()];
            if(owners.includes(selected)) fail('6ae60 selected position aliases outer source storage');
            for(const owner of owners) {
              const fields: PropertyDescriptorMap=Object.getOwnPropertyDescriptors(owner);basicGuard();
              for(const [key,p] of Object.entries(fields)) if('value' in p && p.value===selected && !(owner===actor && key==='lockTarget'))
                fail('6ae60 selected position aliases outer canonical reference');
            }
          }
          basicGuard();
        };
        const storeSelected=(axis: 'x'|'y'|'z',value: number): void=>{
          const borrowed=call(()=>dispatch.getSelectedPositionOwner(id));
          if(selected!==undefined && borrowed!==selected) fail('6ae60 selected position canonical owner changed');
          selected=borrowed;terminalSelected=selected;operandsGuard=selectedGuard;distanceGuard();
          const field=Object.getOwnPropertyDescriptor(selected,axis);distanceGuard();
          if(!field || !('value' in field)) fail(`selected ${axis}: own data property required`);
          if(!field.writable) fail(`selected ${axis}: non-writable field`);
          const current=Object.getOwnPropertyDescriptors(selected)[axis];distanceGuard();
          if(!current || !('value' in current)) fail(`selected ${axis}: own data property changed before store`);
          if(!current.writable) fail(`selected ${axis}: non-writable field before store`);
          const live=primaryStoreDescriptor(selected,axis);
          if(!live || !('value' in live)) fail(`selected ${axis}: live own data property required before store`);
          if(!live.writable) fail(`selected ${axis}: live non-writable field before store`);
          (selected as Record<string,unknown>)[axis]=value;distanceGuard();
        };
        //45204/45238 share the real captured GQR5/data owner with command
        //admission. Only their authenticated zero-angle domain can return.
        const sine=trig(heading(),false);
        const x=sourceFloat(Math.fround(horizontal()*sine),'primary selected X product');distanceGuard();
        storeSelected('x',x);
        const mapping=call(()=>admission().getMappingActor(id)),descriptor=read(mapping,'descriptor4b0');distanceGuard();
        if(typeof descriptor!=='symbol') fail('primary descriptor4b0: owned source identity required');
        const metadata=call(()=>admission().getDescriptorMetadata(id,descriptor));distanceGuard();
        const rawJoint=read(metadata,'byte10');distanceGuard();
        const joint=unsigned(rawJoint,255,'descriptor byte10')<<24>>24;
        const row=call(()=>world.getWorldMatrix(id,joint));distanceGuard();
        const height=read(row,'7');distanceGuard();
        storeSelected('y',sourceFloat(height,'primary selected world row7'));
        const cosine=trig(heading(),true);
        const z=sourceFloat(Math.fround(horizontal()*cosine),'primary selected Z product');distanceGuard();
        storeSelected('z',z);
        // The source reloads actualcc only after the completed primary path.
        // A nonnull value is compared, not dereferenced or substituted for c8.
        ccReached=true;distanceGuard();
        noShadows(actor,['204','205','206','207']);
        const ccField=Object.getOwnPropertyDescriptor(actor,'visibilityTarget');distanceGuard();
        if(!ccField || !('value' in ccField)) fail('8006b1d0 visibilityTarget: own data property required');
        const secondary=ccField.value;
        if(secondary!==null) record(secondary,'8006b1d0 visibilityTarget');
        secondaryReached=true;distanceGuard();
        let secondaryPositionGuard=(): void=>{};
        let aimed: object|undefined;
        const aimGuard=(): void=>{
          selectedGuard();secondaryPositionGuard();
          if(aimed!==undefined) {
            const commandRuntime=admission();
            for(const owner of [actor,binding,aimed,commandRuntime.getData(),commandRuntime.getWorldBinding(id),
              commandRuntime.getStatusBinding(id),commandRuntime.getMappingActor(id),commandRuntime.getActionBinding(id)])
              noShadows(owner,aimAliases);
            if(call(()=>commandRuntime.getAimPositionOwner(id))!==aimed)
              fail('6ae60 aimOrigin518 canonical owner changed');
            const direct=[sources,globals,data!,...retained.values(),...massActors.values()];
            if(direct.includes(aimed)) fail('6ae60 aimOrigin518 aliases outer source storage');
            const references: object[]=[...direct,...root.getRetainedStorageOwners(),...scheduler.getRetainedStorageOwners(),
              ...dispatch.getRetainedStorageOwners(),...allocator.getRetainedStorageOwners(),
              ...world.getRetainedActorOwners(),...world.getRetainedMatrixOwners(),...commandRuntime.getKnownStorageOwners(),
              ...commandRuntime.getActionRuntime().getRetainedStorageOwners(),...status.getRetainedStorageOwners()];
            for(const owner of references) {
              if(owner===aimed) continue;
              const fields: PropertyDescriptorMap=Object.getOwnPropertyDescriptors(owner);basicGuard();
              for(const [key,p] of Object.entries(fields)) if('value' in p && p.value===aimed && !(owner===actor && key==='aimOrigin518'))
                fail('6ae60 aimOrigin518 aliases canonical reference');
            }
          }
          selectedGuard();
        };
        const storeAim=(axis: 'x'|'y'|'z',value: number): void=>{
          aimReached=true;distanceGuard();
          const borrowed=call(()=>admission().getAimPositionOwner(id));
          if(aimed!==undefined && aimed!==borrowed) fail('aimOrigin518 canonical owner changed');
          aimed=borrowed;terminalAim=aimed;operandsGuard=aimGuard;distanceGuard();
          for(const owner of [actor,binding,aimed,admission().getData(),admission().getWorldBinding(id),
            admission().getStatusBinding(id),admission().getMappingActor(id),admission().getActionBinding(id)])
            noShadows(owner,aimAliases);
          const field=Object.getOwnPropertyDescriptor(aimed,axis);distanceGuard();
          if(!field || !('value' in field)) fail(`aim ${axis}: own data property required`);
          if(!field.writable) fail(`aim ${axis}: non-writable field`);
          const current=Object.getOwnPropertyDescriptors(aimed)[axis];distanceGuard();
          if(!current || !('value' in current)) fail(`aim ${axis}: own data property changed before store`);
          if(!current.writable) fail(`aim ${axis}: non-writable field before store`);
          terminalSecondary();
          const live=primaryStoreDescriptor(aimed,axis);
          if(!live || !('value' in live)) fail(`aim ${axis}: live own data property required before store`);
          if(!live.writable) fail(`aim ${axis}: live non-writable field before store`);
          (aimed as Record<string,unknown>)[axis]=value;distanceGuard();
        };
        if(secondary!==null) {
          //b1dc captures admission+c8 once. Actual+cc only selects this branch;
          //it is never dereferenced or used as the original OBJECT provider.
          c8Reached=true;distanceGuard();
          const provider=load(binding,'pointerc8');distanceGuard();
          const captured=record(provider,'8006b1dc captured secondary pointerc8');
          const object=call(()=>allocator.getPointerIdentity(captured));distanceGuard();
          //The copy dereferences an original OBJECT, not descriptor memory
          //or an external actor registered under another pointer identity.
          call(()=>allocator.getObject(object));distanceGuard();
          const word=(offset: number): number=>{
            const value=call(()=>allocator.readU32(object,offset));distanceGuard();return value;
          };
          const storeWord=(axis: 'x'|'y'|'z',bits: number): void=>{
            //The source uses lwz/stw, not lfs/stfs. The canonical numeric aim
            //owner supports every finite f32 bit pattern, including -0. Reject
            //NaN/Inf only at this reached store, not at either earlier load.
            if((bits&0x7f800000)===0x7f800000)
              fail(`secondary aim ${axis}: unsupported nonfinite integer-copy bits`);
            const view=new DataView(new ArrayBuffer(4));view.setUint32(0,bits,false);
            storeAim(axis,view.getFloat32(0,false));
          };
          const xWord=word(0x64),yWord=word(0x68);
          storeWord('x',xWord);storeWord('y',yWord);
          const zWord=word(0x6c);storeWord('z',zWord);
          //b1e0 forms an inline address, not a position operand load. Defer
          //the numeric-vector admission until the reached bc88 call.
          const {position,guard:positionGuard}=preparePosition();
          secondaryPositionGuard=positionGuard;operandsGuard=aimGuard;distanceGuard();
          const processor=call(()=>root.getVectorProcessorProfile());distanceGuard();
          if(processor===undefined) fail('8006b208 reached authenticated8020bc88 PSVECSquareDistance; explicit processor profile unavailable');
          if(processor===position) fail('6ae60 position20 aliases processor storage');
          const distance=readSourceSquareDistance({a:position,aName:'position20',b:captured,bRepresentation:'record',
            allocator,root,processor,guard:distanceGuard});
          const positiveGuard=(): void=>{
            distanceGuard();
            if(call(()=>root.getVectorProcessorProfile())!==processor) fail('secondary estimator processor profile owner changed');
            distanceGuard();
          };
          const estimate=(square: number,address: '8006b218'|'8006b298'): number=>{
            // The root owns this already captured profile. Retain its declaration
            // for a callback-free terminal link check before either result store.
            estimatorProcessor=processor;positiveGuard();
            if(estimatorProcessorSource===undefined) {
              const links=call(()=>root.getRetainedStorageOwners()).filter(owner=>{
                const field=primaryStoreDescriptor(owner,'processor');
                return field && 'value' in field && field.value===processor;
              });
              if(links.length!==1) fail('secondary estimator canonical processor declaration required');
              estimatorProcessorSource=links[0];
            }
            return readSourceTargetDistance(square,processor,data!,positiveGuard,address);
          };
          const total=distance>constant('float80437658',0,'8006b20c')
            ? estimate(distance,'8006b218'):distance;
          store('targetDistance760',total);
          const zero=constant('float80437658',0,'8006b268');
          const scalar=(axis: 'x'|'z'): number=>{
            const value=read(position,axis);distanceGuard();return sourceFloat(value,axis);
          };
          const ax=scalar('x'),bx=call(()=>allocator.readF32(object,0x64));distanceGuard();
          const az=scalar('z'),bz=call(()=>allocator.readF32(object,0x6c));distanceGuard();
          const dx=addSourceFloat32(ax,-bx),dz=addSourceFloat32(az,-bz);distanceGuard();
          const xx=sourceFloat(Math.fround(dx*dx),'secondary horizontal X square'),
            zz=sourceFloat(Math.fround(dz*dz),'secondary horizontal Z square');distanceGuard();
          const horizontal=addSourceFloat32(xx,zz);distanceGuard();
          const horizontalDistance=horizontal>zero
            ? estimate(horizontal,'8006b298'):horizontal;
          store('horizontalDistance764',horizontalDistance);
          return; //b2e8 rejoins the same b33c second-pass continuation.
        }
        const secondaryMissing=constant('float80437678',20000,'8006b2ec');
        store('horizontalDistance764',secondaryMissing);store('targetDistance760',secondaryMissing);
        const secondaryHorizontal=(): number=>{
          const value=read(actor,'horizontalDistance764');distanceGuard();return sourceFloat(value,'horizontalDistance764');
        };
        const secondarySine=trig(heading(),false);
        const sx=sourceFloat(Math.fround(secondaryHorizontal()*secondarySine),'secondary X product');distanceGuard();
        storeAim('x',sx);
        const secondaryMapping=call(()=>admission().getMappingActor(id)),secondaryDescriptor=read(secondaryMapping,'descriptor4b0');distanceGuard();
        if(typeof secondaryDescriptor!=='symbol') fail('secondary descriptor4b0: owned source identity required');
        const secondaryMetadata=call(()=>admission().getDescriptorMetadata(id,secondaryDescriptor));distanceGuard();
        const secondaryByte=read(secondaryMetadata,'byte10');distanceGuard();
        const secondaryJoint=unsigned(secondaryByte,255,'secondary descriptor byte10')<<24>>24;
        const secondaryRow=call(()=>world.getWorldMatrix(id,secondaryJoint));distanceGuard();
        const secondaryHeight=read(secondaryRow,'7');distanceGuard();
        storeAim('y',sourceFloat(secondaryHeight,'secondary world row7'));
        const secondaryCosine=trig(heading(),true);
        const sz=sourceFloat(Math.fround(secondaryHorizontal()*secondaryCosine),'secondary Z product');distanceGuard();
        storeAim('z',sz);
        //b33c..b348 advance the same second-pass loop; existing third-pass
        //canonical508 admission remains mandatory even for inactive rows.
        return;
      }
      record(targetPointer,'6ae60 primary pointer508');
      // Snapshot host references before the public504/position/GQR observers.
      // This is native metadata only: B remains unadmitted until its first
      // actual paired load. A callback must not bless a newly added alias as
      // an initial allocator/selector reference by preceding the first store.
      distanceGuard();
      const providerOwners=[...terminalRecords,...terminalRecords.flatMap(owner=>
        Object.values(primaryStoreDescriptors(owner)).flatMap(p=>'value' in p && p.value!==null && typeof p.value==='object'?[p.value as object]:[]))];
      const providerSnapshots=[...new Set(providerOwners)].map(owner=>({owner,fields:primaryStoreDescriptors(owner)}));
      //af98 captures504 before forming both vector addresses. Pointer-domain
      //admission for B is deferred until its first actual paired load.
      const provider=load(binding,'pointer504');
      primaryProviderReferences=new Map();
      for(const {owner,fields} of providerSnapshots) for(const [key,p] of Object.entries(fields))
        if('value' in p && p.value===provider) {
          const keys=primaryProviderReferences.get(owner)??new Set<string>();keys.add(key);primaryProviderReferences.set(owner,keys);
        }
      const {position,guard:positionGuard}=preparePosition();
      operandsGuard=positionGuard;positionGuard();
      const processor=call(()=>root.getVectorProcessorProfile());
      if(processor===undefined) fail('8006afac reached authenticated8020bc88 PSVECSquareDistance; explicit processor profile unavailable');
      if(processor===position) fail('6ae60 position20 aliases processor storage');
      const distance=readSourceSquareDistance({a:position,aName:'position20',b:provider,bRepresentation:'record',
        allocator,root,processor,guard:positionGuard});
      primaryProvider=record(provider,'captured primary OBJECT');
      primaryObject=call(()=>allocator.getPointerIdentity(primaryProvider!));
      if(call(()=>allocator.getObject(primaryObject!))!==primaryProvider) fail('primary captured OBJECT bytes required');
      primaryReached=true;
      const positiveGuard=(): void=>{
        distanceGuard();
        if(call(()=>root.getVectorProcessorProfile())!==processor) fail('primary estimator processor profile owner changed');
        distanceGuard();
      };
      const estimate=(square: number,address: '8006afbc'|'8006b03c'): number=>{
        estimatorProcessor=processor;positiveGuard();
        if(estimatorProcessorSource===undefined) {
          const links=call(()=>root.getRetainedStorageOwners()).filter(owner=>{
            const p=primaryStoreDescriptor(owner,'processor');return p && 'value' in p && p.value===processor;
          });
          if(links.length!==1) fail('primary estimator canonical processor declaration required');
          estimatorProcessorSource=links[0];
        }
        return readSourceTargetDistance(square,processor,data!,positiveGuard,address);
      };
      //afbc..b004: model-backed seed, half then three, three binary64
      //q/h/fnmsub/e rounds, product/frsp and stack+14 store/reload.
      const total=distance>constant('float80437658',0,'8006afb0')?estimate(distance,'8006afbc'):distance;
      store('targetDistance758',total);
      const zero=constant('float80437658',0,'8006b00c');
      //These are ordinary scalar lfs loads. No GQR read or vector snapshot.
      const scalar=(owner: object,key: string): number=>{
        const value=read(owner,key);distanceGuard();return sourceFloat(value,key);
      };
      const ax=scalar(position,'x');
      const object=call(()=>allocator.getPointerIdentity(record(provider,'captured primary OBJECT')));distanceGuard();
      const bx=call(()=>allocator.readF32(object,0x64));distanceGuard();
      const az=scalar(position,'z'),bz=call(()=>allocator.readF32(object,0x6c));distanceGuard();
      const dx=addSourceFloat32(ax,-bx),dz=addSourceFloat32(az,-bz);distanceGuard();
      const xx=sourceFloat(Math.fround(dx*dx),'primary horizontal X square'),
        zz=sourceFloat(Math.fround(dz*dz),'primary horizontal Z square');distanceGuard();
      const horizontal=addSourceFloat32(xx,zz);distanceGuard();
      //b03c..b084 repeats that schedule with stack+10, without a GQR load.
      const horizontalDistance=horizontal>zero?estimate(horizontal,'8006b03c'):horizontal;
      store('horizontalDistance75c',horizontalDistance);
      //b094 reloads508, even if an observer changed it after the initial compare.
      const fresh=read(binding,'pointer508');distanceGuard();
      if(fresh!==null) record(fresh,'6ae60 fresh primary pointer508');
      fail('8006b098 reached mandatory8006d228 primary direction helper');
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
        const dispatchPresent=Object.getOwnPropertyDescriptor(target,'targetDispatch');check();
        if(dispatchPresent===undefined) fail('8006af88 reached mandatory8006b7f4 target-dispatch predecessor');
        const dispatch=read(target,'targetDispatch');
        if(!isSourceActorTargetDispatchRuntime(dispatch) || dispatch.getSchedulerRuntime()!==scheduler)
          fail('6b7f4 exact genuine target-dispatch/scheduler owner required');
        call(()=>dispatch.dispatchActor(id));
        primaryDistance(id,actor,dispatch);
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
      //8006b374 reads the captured target, not a reloaded actor508. This
      // bounded domain accepts a genuine actor bound to this SAME allocator
      // and world; its canonical83 is already allocation-owned, not a new
      // eligibility83 field copied onto the actual actor or an ad hoc target.
      // Final metadata snapshots use the retained native intrinsic. For the
      // declared synchronous nonproxy records these checks cannot invoke the
      // observer that just ran, nor read any captured source scalar again.
      const terminalRead=(record:object,key:string):unknown=>{
        const field=primaryStoreDescriptor(record,key);
        if(!field || !('value' in field))fail(`${key}: terminal own data property required`);
        return field.value;
      };
      const terminalShadows=(record:object,keys:readonly string[]):void=>{
        for(const key of keys)if(primaryStoreDescriptor(record,key)!==undefined)fail(`${key}: competing source cell owner`);
      };
      const selected=(()=>{
        try {
          const runtime=admission();
          const targetId=call(()=>allocator.getPointerIdentity(record(pointer,'6b374 captured target')));
          const targetActor=actual(targetId);
          const owner=record(call(()=>allocator.getActorBinding(targetId)),'6b374 canonical allocation83');
          const finish=():void=>{
            if(terminalRead(sources,'targetPreparation')!==target || terminalRead(target,'admission')!==runtime ||
              spawns.getAdmissionRuntime()!==runtime || runtime.getActualActor(id)!==actor ||
              runtime.getActorBinding(id)!==binding || world.getActualActor(id)!==actor || status.getActualActor(id)!==actor ||
              allocator.getActualActor(targetId)!==targetActor || allocator.getPointerTarget(targetId)!==targetActor ||
              allocator.getActorBinding(targetId)!==owner || world.getActualActor(targetId)!==targetActor)
              fail('6b374 terminal canonical caller/target owner changed');
            terminalShadows(actor,['pointer508','field508','byte508','byte509','byte50a','byte50b','byte50A','byte50B','1288','1289','1290','1291']);
            terminalShadows(binding,['field508','byte508','byte509','byte50a','byte50b','byte50A','byte50B','1288','1289','1290','1291']);
            const worldOwner=world.getActorBinding(targetId);
            for(const candidate of new Set([targetActor,worldOwner,...allocator.getSourceOwners(targetId)])) {
              if(candidate!==owner)terminalShadows(candidate,['byte83']);
              terminalShadows(candidate,['eligibility83','groupEligibility83','field83']);
              if(candidate===targetActor || candidate===worldOwner || candidate===owner)terminalShadows(candidate,['131']);
            }
            check();requireCompleteSourceActorDoubleLifecycle(actor);requireCompleteSourceActorDoubleLifecycle(targetActor);
            runtime.assertActorComplete(id);allocator.assertActorComplete(targetId);check();
          };
          const guard=(): void=>{
            check();requireCompleteSourceActorDoubleLifecycle(actor);
            call(()=>admission().assertActorComplete(id));
            if(command(id,actor,false)!==binding)fail('6b374 captured caller admission changed');
            noShadows(actor,['pointer508','field508','byte508','byte509','byte50a','byte50b','byte50A','byte50B','1288','1289','1290','1291']);
            noShadows(binding,['field508','byte508','byte509','byte50a','byte50b','byte50A','byte50B','1288','1289','1290','1291']);
            requireCompleteSourceActorDoubleLifecycle(targetActor);
            call(()=>allocator.assertActorComplete(targetId));
            if(targetActor!==pointer || call(()=>allocator.getActualActor(targetId))!==targetActor ||
              call(()=>world.getActualActor(targetId))!==targetActor ||
              call(()=>allocator.getPointerTarget(targetId))!==targetActor ||
              call(()=>allocator.getActorBinding(targetId))!==owner)
              fail('6b374 canonical target/allocator/world owner differs');
            if(owner===targetActor || [...retained.values()].includes(owner) || [...massActors.values()].includes(owner))
              fail('6b374 allocation83 storage alias');
            const worldOwner=call(()=>world.getActorBinding(targetId));
            const records=[targetActor,worldOwner,...call(()=>allocator.getSourceOwners(targetId))];
            for(const candidate of new Set(records)) {
              if(candidate!==owner)noShadows(candidate,['byte83']);
              noShadows(candidate,['eligibility83','groupEligibility83','field83']);
              // An unrelated allocated byte buffer legitimately has offset131.
              // Numeric actor aliases apply only to these actor-role records.
              if(candidate===targetActor || candidate===worldOwner || candidate===owner)noShadows(candidate,['131']);
            }
            finish();
          };
          guard();const captured=byte(owner,'byte83');guard();return {captured,targetActor,targetId,owner,runtime,guard,finish};
        } catch(error) {fail(`8006b374 target83 ownership/load refused: ${String(error)}`);}
      })();
      if(s8(selected.captured)!==0) continue;
      let teamsReached=false,distanceReached=false,threshold:object|undefined;
      let attributeRuntime:SourceActorAttributeRefreshRuntime|undefined,attributeMass:object|undefined;
      const associationMetadata=(shadows:(owner:object,keys:readonly string[])=>void,
        peek:(owner:object,key:string)=>unknown):void=>{
        const runtime=selected.runtime;
        const records=[actor,selected.targetActor,binding,selected.owner,globals,sources,
          runtime.getWorldBinding(id),runtime.getStatusBinding(id),runtime.getMappingActor(id),
          runtime.getAttributeBinding(id),runtime.getChargeBinding(id),runtime.getActionBinding(id),
          runtime.getCueBinding(id),runtime.getDispatchBinding(id),runtime.getStartBinding(id),runtime.getStreamBinding(id),
          world.getActorBinding(selected.targetId)];
        const actuals=world.getRetainedActorOwners();
        for(const candidate of new Set(records)) {
          if(!actuals.includes(candidate))shadows(candidate,['byte7d3']);
          shadows(candidate,['byte7D3','field7d3','field7D3','flags7d3','mask7d3']);
          if(candidate===actor)shadows(candidate,['2003']);
          if(teamsReached) {
            if(!actuals.includes(candidate))shadows(candidate,['team']);
            shadows(candidate,['byte88','field88']);
            if(candidate===actor || candidate===selected.targetActor)shadows(candidate,['136']);
          }
          if(distanceReached) {
            if(!actuals.includes(candidate))shadows(candidate,['horizontalDistance75c']);
            shadows(candidate,['field75c','field75C','float75c','float75C']);
            if(candidate===actor)shadows(candidate,['1884','1885','1886','1887','byte75c','byte75d','byte75e','byte75f','byte75C','byte75D','byte75E','byte75F']);
          }
          if(threshold!==undefined) {
            if(candidate!==threshold)shadows(candidate,['field814']);
            shadows(candidate,['float814','threshold814']);
            if(candidate===actor || candidate===threshold)shadows(candidate,['2068','2069','2070','2071','byte814','byte815','byte816','byte817']);
          }
        }
        if(threshold!==undefined && (runtime.getAttributeBinding(id)!==threshold ||
          status.getAttributeBinding(id)!==threshold || !attributeRuntime || !attributeMass ||
          peek(sources,'massPreparation')!==attributeMass || peek(attributeMass,'attributes')!==attributeRuntime ||
          attributeRuntime.getActualActor(id)!==actor || attributeRuntime.getActorBinding(id)!==threshold))
          fail('6b3a8 canonical814 owner changed');
      };
      const associationGuard=():void=>{
        selected.guard();associationMetadata(noShadows,read);selected.guard();
        associationMetadata(terminalShadows,terminalRead);selected.finish();
      };
      const associationLoad=(owner:object,key:string):unknown=>{
        associationGuard();const value=read(owner,key);associationGuard();return value;
      };
      //8006b380..388: bit0 only, not a truthiness test on the whole byte.
      const flags=unsigned(associationLoad(actor,'byte7d3'),255,'byte7d3');
      if((flags&1)!==0)continue;
      //8006b38c..3a0: target team BEFORE caller team; retain captured signed
      // values even if either source cell changes during the following load.
      teamsReached=true;
      const targetTeam=s8(unsigned(associationLoad(selected.targetActor,'team'),255,'target team'));
      const callerTeam=s8(unsigned(associationLoad(actor,'team'),255,'caller team'));
      if(targetTeam===callerTeam)continue;
      //8006b3a4..3b0: finite exact-f32 host domain only. Source skips on GT,
      // not on !(LT||EQ). NaN/unordered and general FPSCR are not implemented.
      distanceReached=true;
      const finite=(value:unknown,key:string):number=>{
        if(typeof value!=='number' || !Number.isFinite(value) || !Object.is(value,Math.fround(value)))
          fail(`${key}: finite exact source float32 required`);return value;
      };
      const distance=finite(associationLoad(actor,'horizontalDistance75c'),'horizontalDistance75c');
      const mass=retained.get('massPreparation');
      if(!mass || read(sources,'massPreparation')!==mass)fail('6b3a8 canonical mass attribute ingress changed');
      const attributes=read(mass,'attributes');
      if(!isSourceActorAttributeRefreshRuntime(attributes) || call(()=>attributes.getActualActor(id))!==actor)
        fail('6b3a8 genuine same-actor attribute owner required');
      attributeRuntime=attributes;attributeMass=mass;
      threshold=record(call(()=>attributes.getActorBinding(id)),'6b3a8 canonical attribute814');
      const limit=finite(associationLoad(threshold,'field814'),'field814');
      if(distance>limit)continue;
      //8006b3bc captures a FRESH physical base for each admitted outer actor.
      // The inner index is a physical position, not actor.slot or a roster
      // entry. Only a mask hit dereferences that candidate's actual record.
      associationGuard();const inner=physical();associationGuard();
      const innerMass=retained.get('massPreparation')!,innerBlock=retained.get('mass physicalBlock')!;
      let candidate:{id:symbol;actor:object}|undefined,maskReached=false;
      const flagOwners=new Set<object>();
      const innerMetadata=(shadows:(owner:object,keys:readonly string[])=>void):void=>{
        if(terminalRead(sources,'massPreparation')!==innerMass || terminalRead(innerMass,'physicalBlock')!==innerBlock ||
          terminalRead(innerBlock,'identities')!==inner || retained.get('mass physical identities')!==inner)
          fail('6b3bc captured inner physical metadata changed');
        const records=[selected.targetActor,selected.owner,world.getActorBinding(selected.targetId),binding];
        if(candidate!==undefined) {
          if(allocator.getPointerTarget(candidate.id)!==candidate.actor ||
            world.getActualActor(candidate.id)!==candidate.actor)
            fail('6b3e8 canonical candidate actor changed');
          records.push(candidate.actor,world.getActorBinding(candidate.id));
        }
        const actuals=world.getRetainedActorOwners();
        for(const owner of new Set(records)) {
          if(maskReached) {
            if(!actuals.includes(owner))shadows(owner,['byte58a']);
            shadows(owner,['byte58A','field58a','field58A','flags58a','mask58a']);
            if(owner===selected.targetActor)shadows(owner,['1418']);
          }
          if(candidate!==undefined) {
            if(!actuals.includes(owner))shadows(owner,['team']);
            shadows(owner,['byte88','field88']);
            if(owner===candidate.actor)shadows(owner,['136']);
          }
          if(flagOwners.size!==0) {
            if(!actuals.includes(owner))shadows(owner,['byte7d3']);
            shadows(owner,['byte7D3','field7d3','field7D3','flags7d3','mask7d3']);
            if(flagOwners.has(owner))shadows(owner,['2003']);
          }
        }
      };
      const innerFinish=():void=>{
        innerMetadata(terminalShadows);
        if(candidate!==undefined) {
          requireCompleteSourceActorDoubleLifecycle(candidate.actor);
        }
        associationMetadata(terminalShadows,terminalRead);selected.finish();
      };
      const innerGuard=():void=>{
        associationGuard();innerMetadata(noShadows);associationGuard();innerFinish();
      };
      const innerLoad=(owner:object,key:string):number=>{
        innerGuard();const value=read(owner,key);innerGuard();return unsigned(value,255,key);
      };
      const storeFlag=(owner:object,value:number):void=>{
        innerGuard();const field=Object.getOwnPropertyDescriptor(owner,'byte7d3');innerGuard();
        if(!field || !('value' in field))fail('byte7d3: own data property required before association store');
        if(!field.writable)fail('byte7d3: non-writable association destination');
        const live=primaryStoreDescriptor(owner,'byte7d3');
        if(!live || !('value' in live))fail('byte7d3: live own data property required before association store');
        if(!live.writable)fail('byte7d3: live non-writable association destination');
        // No observable metadata callback between this final native snapshot
        // and the existing own-data overwrite. Earlier completed stores stay.
        (owner as Record<string,unknown>).byte7d3=value;innerGuard();
      };
      for(let position=0;position<6;position++) {
        candidate=undefined;
        if(position===index)continue; //3cc..3d0 BEFORE the target58a load.
        maskReached=true;
        const mask=s8(innerLoad(selected.targetActor,'byte58a'));
        if((mask&(1<<position))===0)continue;
        candidate=actorAt(inner,position);innerGuard();
        const candidateTeam=s8(innerLoad(candidate.actor,'team'));
        if(candidateTeam!==callerTeam)continue; // captured r8, not a fresh caller team.
        //3f8..418: three distinct fresh read/modify/store pairs. In particular
        // candidate===target must observe the preceding bit1 store before OR2.
        flagOwners.add(actor);const callerFlags=innerLoad(actor,'byte7d3');storeFlag(actor,callerFlags|1);
        flagOwners.add(candidate.actor);const candidateFlags=innerLoad(candidate.actor,'byte7d3');storeFlag(candidate.actor,candidateFlags|1);
        flagOwners.add(selected.targetActor);const targetFlags=innerLoad(selected.targetActor,'byte7d3');storeFlag(selected.targetActor,targetFlags|2);
        break; //3bc reloads again only for the next admitted outer actor.
      }
    }
    //Genuine void return only if every reached canonical508 owner completed.
  };
  /** Complete authenticated80027764. The discarded RNG result still advances
   * the SAME live byte owner. Initial row38 copies are not leader pointers.
   * Source leaders are local registers; each nonnull publication reloads base0.
   * Stable canonical records remain a host bound, not inferred source aliases. */
  const prepareLeaders=(): void=>{
    const mass=retained.get('massPreparation');
    if(!mass) fail('80027770 missing canonical mass/RNG ingress');
    randomByte(mass,'80027770');
    const world=spawns.getWorldRuntime(),actorFields=new Set<string>(),rows=new Map<number,object>();
    const capturedActors=new Map<symbol,object>();
    let capturedTable:object|undefined,blockReached=false;
    const terminalShadows=(owner:object,keys:readonly string[]):void=>{
      for(const key of keys)if(primaryStoreDescriptor(owner,key)!==undefined)fail(`${key}: competing source cell owner`);
    };
    const aliases:Record<string,readonly string[]>={
      pointer330:['word330','field330','leader330',...Array.from({length:4},(_,i)=>0x330+i).flatMap(n=>[String(n),'byte'+n.toString(16)])],
      byte334:['field334','score334','820'],byte335:['field335','leader335','821'],
      team:['byte88','field88','136'],active0:['byte0','0'],
    };
    const metadata=(shadows:typeof noShadows):void=>{
      const actuals=world.getRetainedActorOwners();
      const records=[sources,globals,...retained.values(),...massActors.values(),
        ...scheduler.getRetainedStorageOwners(),...actuals];
      for(const owner of new Set(records))for(const key of actorFields) {
        if(!actuals.includes(owner))shadows(owner,[key]);
        // Numeric actor offsets do not alias independent allocator byte buffers.
        shadows(owner,aliases[key]!.filter(alias=>!/^\d+$/.test(alias)||actuals.includes(owner)));
      }
      for(const [index,row]of rows) {
        const start=0xf4+index*0x3c+0x38;
        shadows(row,['word38','field38','leader38','56','57','58','59','byte38','byte39','byte3a','byte3b','byte3A','byte3B']);
        shadows(globals,[...Array.from({length:4},(_,i)=>start+i).flatMap(n=>[String(n),'byte'+n.toString(16),'byte'+n.toString(16).toUpperCase()]),
          ...['pointer','word','field'].flatMap(prefix=>[prefix+start.toString(16),prefix+start.toString(16).toUpperCase()])]);
      }
    };
    const finish=():void=>{
      check();metadata(terminalShadows);
      if(terminalRead(sources,'scheduler')!==scheduler || scheduler.getRootRuntime()!==root ||
        root.getSpawnRuntime()!==spawns || spawns.getWorldRuntime()!==world || scheduler.getAllocatorRuntime()!==allocator ||
        scheduler.getMatchGlobals()!==globals || spawns.getMatchGlobals()!==globals ||
        terminalRead(sources,'massPreparation')!==mass || retained.get('massPreparation')!==mass)
        fail('27764 terminal canonical graph changed');
      if(blockReached) {
        const block=retained.get('mass physicalBlock'),ids=retained.get('mass physical identities');
        if(!block || !ids || terminalRead(mass,'physicalBlock')!==block || terminalRead(block,'identities')!==ids)
          fail('27764 canonical physical metadata changed');
      }
      if(capturedTable!==undefined && terminalRead(globals,'teamRows103')!==capturedTable)
        fail('27764 canonical team table changed');
      for(const [index,row]of rows)if(terminalRead(capturedTable!,String(index))!==row)
        fail('27764 canonical team row changed');
      for(const [id,actor]of capturedActors) {
        if(allocator.getPointerTarget(id)!==actor || world.getActualActor(id)!==actor)
          fail('27764 canonical actual actor changed');
        requireCompleteSourceActorDoubleLifecycle(actor);
      }
      check();
    };
    const guard=():void=>{check();metadata(noShadows);finish();};
    const store=(owner:object,key:string,value:number|symbol|null):void=>{
      guard();own(owner,key,true);guard();
      const destination=primaryStoreDescriptor(owner,key);
      if(!destination || !('value'in destination))fail(`${key}: live own data property required`);
      if(!destination.writable)fail(`${key}: live non-writable field`);
      (owner as Record<string,unknown>)[key]=value;guard();
    };
    const rowStore=(index:number,value:symbol|null,owner:object=match()):void=>{
      const table=teamTable(owner),row=team(table,index);
      if(capturedTable!==undefined && table!==capturedTable)fail('27764 canonical team table changed');
      capturedTable=table;rows.set(index,row);store(row,'pointer38',value);
    };
    //27778..7b4: pointer copies only. Null/opaque slot2 or1 is not dereferenced.
    const firstOwner=match(),slot2=slotPointer(2);
    if(firstOwner!==globals)fail('27764 initial match owner changed');
    rowStore(0,slot2,firstOwner);
    const slot1=slotPointer(1);rowStore(1,slot1);
    rowStore(2,null);rowStore(3,null);
    const physical=():readonly symbol[]=>{
      guard();const base=slotPointer(0),block=retained.get('mass physicalBlock'),ids=retained.get('mass physical identities');
      if(!block || !ids || read(sources,'massPreparation')!==mass || read(mass,'physicalBlock')!==block ||
        read(block,'identities')!==ids || read(block,'base')!==base)
        fail('27764 physical base differs from canonical block');
      if(!Array.isArray(ids)||!Object.isFrozen(ids)||read(ids,'length')!==6)fail('27764 six frozen physical identities required');
      blockReached=true;guard();return ids as readonly symbol[];
    };
    const at=(ids:readonly symbol[],index:number):{id:symbol;actor:object}=>{
      const id=read(ids,String(index));if(typeof id!=='symbol')fail('27764 physical actor identity required');
      const actor=actual(id);capturedActors.set(id,actor);guard();return{id,actor};
    };
    const load=(actor:object,key:'active0'|'team'|'byte334'):number=>{
      if(key==='byte334')actorFields.add(key);else noShadows(actor,aliases[key]!);
      guard();const value=byte(actor,key);guard();return value;
    };
    const put=(actor:object,key:'pointer330'|'byte335',value:symbol|null|number):void=>{
      actorFields.add(key);store(actor,key,value);
    };
    const initial=physical(),leaders:({id:symbol;actor:object}|undefined)[]=[undefined,undefined],best=[0,0];
    for(let index=0;index<6;index++) {
      const selected=at(initial,index),actor=selected.actor;
      if(s8(load(actor,'active0'))===0)continue;
      put(actor,'byte335',0);put(actor,'pointer330',null);
      const group=s8(load(actor,'team'));if(group!==0&&group!==1)continue;
      const score=load(actor,'byte334');
      if(s8(score)<s8(best[group]!))continue;
      leaders[group]=selected;best[group]=score; // Equality selects the LAST physical candidate.
    }
    for(let group=0;group<2;group++) {
      const leader=leaders[group];if(leader===undefined)continue;
      put(leader.actor,'byte335',1);
      const ids=physical();
      for(let index=0;index<6;index++) {
        const {actor}=at(ids,index);
        if(s8(load(actor,'active0'))===0)continue;
        if(s8(load(actor,'team'))===group)put(actor,'pointer330',leader.id);
      }
    }
    finish(); // Genuine return; the caller still refuses mandatory8000bef4.
  };
  const close=(): void=>{
    if(incomplete) return;
    incomplete=true;closing=true;
    for(const actor of massActors.values()) markIncompleteSourceActorDoubleLifecycle(actor);
    try {closeSourceObjectSchedulerOuterFrame(scheduler,runtime);} finally {closing=false;}
  };
  const runtime: SourceBattleOuterFrameRuntime={
    getSchedulerRuntime() {return scheduler;},getMatchGlobals() {return globals;},
    runFrame(): never {
      if(busy) {poisoned=true;close();fail('same-runtime reentry unsupported');}
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
          prepareLeaders();
        }
        fail('80029464 reached mandatory8000bef4 outer-frame predecessor');
      } catch(error) {
        close();throw error;
      } finally {busy=false;}
    },
  };
  failures.set(runtime,selected=>{if(!busy || !closing || !incomplete || selected!==scheduler) fail('private exact active outer failure required');});
  runtimes.add(runtime);pendingClaims.set(runtime,scheduler);
  try {claimSourceObjectSchedulerOuterFrame(scheduler,runtime);} finally {pendingClaims.delete(runtime);}
  claimedGlobals.add(globals);return Object.freeze(runtime);
}
