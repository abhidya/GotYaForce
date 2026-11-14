/** Bounded genuine80029434 prefix, not a successful outer battle frame.
 * Executes8b048→8b010 and29d48→29e98 over the SAME80433934 owner and
 * existing teamRows103/charged/meter owners. First reached active-burst8b290,
 * normal53b30 or unconditional pausedbef4 remains a hard ordered boundary.
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
import type {SourceBattleOuterGlobalFields, SourceBattleSystemGlobals} from './battle-global-layout.js';

export interface SourceBattleOuterFrameSources {
  scheduler: SourceObjectSchedulerRuntime;
  /** Same explicit80433930 owner, reached only after a team/slot match. */
  systemGlobals?: SourceBattleSystemGlobals;
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
  const retained=new Map<string,object>();
  const check=(): void=>{if(poisoned) fail('caught same-runtime reentry');};
  const read=(owner: unknown,key: string): unknown=>{const value=own(owner,key);check();return value;};
  const call=<T>(run: ()=>T): T=>{const result=run();check();return result;};
  const write=(owner: object,key: string,value: number|boolean): void=>{
    own(owner,key,true);check();(owner as Record<string,unknown>)[key]=value;check();
  };
  const byte=(owner: object,key: string): number=>unsigned(read(owner,key),255,key);
  const half=(owner: object,key: string): number=>unsigned(read(owner,key),65535,key);
  const noShadows=(owner: object,keys: readonly string[]): void=>{
    for(const key of keys) {const p=Object.getOwnPropertyDescriptor(owner,key);check();if(p!==undefined) fail(`${key}: competing source cell owner`);}
  };
  const retain=(name: string,value: unknown): object=>{
    const actual=record(value,name), previous=retained.get(name);
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
        if(s8(byte(match(),'byte66'))===0) fail('80029458 reached mandatory80053b30 normal-stage predecessor');
        fail('80029464 reached mandatory8000bef4 outer-frame predecessor');
      } catch(error) {
        incomplete=true;closing=true;
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
