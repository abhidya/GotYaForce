/** Bounded genuine89a94/8997c/89898 scheduling, not the whole battle frame.
 * Same allocator groups and object bytes, same80433934 owner, explicit six-slot
 * pointers and active0 owners. Only active, bound completed projectile roots
 * are admitted. Frame-owned actors still require their later real frame join.
 * Source snapshots are RAW words, including one atomic-preflight stw+76; this
 * byte-record model makes no hardware alignment/exception claim. Source next8
 * is reloaded AFTER callback cleanup, even when active0 was cleared.
 * No callback injection, copied lists, fabricated active slot, default mask,
 * estimator, source actor constructor, or browser activation is supplied.
 */
import {isSourceProjectileRootRuntime, prepareSourceProjectileScheduledRoot,
  invokeSourceProjectileScheduledRoot, markIncompleteSourceProjectileScheduledRoot,
  type SourceProjectileRootRuntime} from './projectile-root-lifecycle.js';
import {markIncompleteSourceObjectAllocation, type SourceObjectAllocationRuntime} from './source-object-allocation.js';

export interface SourceObjectSchedulerSources {
  root: SourceProjectileRootRuntime;
  /** Actual803c4e84 pointer table, not a roster-derived active list. Lazy. */
  actorSlots?: Readonly<Record<number, symbol | null>>;
}
export interface SourceObjectSchedulerRuntime {
  getRootRuntime(): SourceProjectileRootRuntime;
  getAllocatorRuntime(): SourceObjectAllocationRuntime;
  getMatchGlobals(): object;
  /** Arguments are raw u32 register bits; source comparisons are signed. */
  runGroup(groupBits: number): void;
  runSlots(baseBits: number): void;
  runWrapper(baseBits: number): void;
}
type Stage = 'prepare' | 'snapshot' | 'callback' | 'after';
interface Active {child: symbol; stage: Stage; lifetime?: symbol; callback?: number}
const runtimes = new WeakSet<object>(), claims = new WeakMap<object, SourceObjectSchedulerRuntime>();
const scopes = new WeakMap<object, (root: SourceProjectileRootRuntime | undefined,
  allocator: SourceObjectAllocationRuntime | undefined, child: symbol | undefined,
  stage: Stage | 'closure', lifetime?: symbol) => void>();
export function isSourceObjectSchedulerRuntime(value: unknown): value is SourceObjectSchedulerRuntime {
  return value !== null && typeof value === 'object' && runtimes.has(value);
}
/** Read-only guard; possessing a genuine scheduler is not active authority. */
export function requireSourceObjectSchedulerInvocation(scheduler: SourceObjectSchedulerRuntime,
  root: SourceProjectileRootRuntime, child: symbol | undefined, stage: 'prepare' | 'callback' | 'closure', lifetime?: symbol): void {
  const scope = scopes.get(scheduler);
  if (!isSourceObjectSchedulerRuntime(scheduler) || !scope || claims.get(root) !== scheduler)
    fail('private active scheduler invocation required');
  scope(root,undefined,child,stage,lifetime);
}
export function requireSourceObjectSchedulerSnapshot(scheduler: SourceObjectSchedulerRuntime,
  allocator: SourceObjectAllocationRuntime, child: symbol): void {
  const scope = scopes.get(scheduler);
  if (!isSourceObjectSchedulerRuntime(scheduler) || !scope) fail('private active scheduler snapshot required');
  scope(undefined,allocator,child,'snapshot');
}
export function requireStandaloneSourceProjectileRoot(root: SourceProjectileRootRuntime): void {
  if (claims.has(root)) fail('root is exclusively owned by source scheduler; standalone dispatch unsupported');
}
function fail(why: string): never {
  throw Error(`[source-object-scheduler] ${why}; offline execution aborted, prior writes/effects are not rolled back`);
}
function own(owner: unknown, key: string): unknown {
  if (owner === null || typeof owner !== 'object') fail(`${key}: own data record required`);
  const p = Object.getOwnPropertyDescriptor(owner,key);
  if (!p || !('value' in p)) fail(`${key}: own data property required`);
  return p.value;
}
function unsigned(value: unknown, max: number, where: string): number {
  if (typeof value !== 'number' || !Number.isInteger(value) || value < 0 || value > max)
    fail(`${where}: unsigned source integer required`);
  return value === 0 ? 0 : value;
}
function record(value: unknown, where: string): object {
  if (value === null || typeof value !== 'object' || ArrayBuffer.isView(value) || value instanceof Promise)
    fail(`${where}: synchronous own-data record required`);
  return value;
}
function pointer(value: unknown, where: string): symbol | null {
  if (value !== null && typeof value !== 'symbol') fail(`${where}: source pointer identity required`);
  return value;
}
export function createSourceObjectSchedulerRuntime(sources: SourceObjectSchedulerSources): SourceObjectSchedulerRuntime {
  const root = own(sources,'root');
  if (!isSourceProjectileRootRuntime(root)) fail('genuine projectile root required');
  if (claims.has(root)) fail('root already has a source scheduler');
  const spawns = root.getSpawnRuntime(), allocator = spawns.getAllocatorRuntime(), globals = record(spawns.getMatchGlobals(),'shared80433934');
  let busy = false, poisoned = false, incomplete = false, active: Active | undefined, slotsOwner: object | undefined, visits = 0;
  const check = (): void => {if (poisoned) fail('caught same-runtime reentry');};
  const read = (owner: unknown,key: string): unknown => {const value=own(owner,key);check();return value;};
  const call = <T>(run: () => T): T => {const value=run();check();return value;};
  const sourceGlobal = (): object => {
    const actual=call(()=>spawns.getMatchGlobals());if(actual!==globals) fail('canonical80433934 owner changed');return actual;
  };
  const mask = (base: number): number => unsigned(read(sourceGlobal(),(base|0)<8?'maskD2':'maskD1'),255,'source pause byte');
  const head = (index: number): symbol | null => pointer(read(call(()=>allocator.getGroup(index & 0x3fffffff)),'head'),'group head');
  const walk = (first: symbol | null): void => {
    let child=first;
    while(child!==null) {
      if (++visits>4096) fail('host list visit budget exceeded');
      active=undefined;
      const current=child;
      if (call(()=>allocator.readS8(current,0))!==0) {
        // Host domain admission only: no source fields are copied. This checks
        // the genuine completed lifetime and frame prohibition before stores.
        active={child:current,stage:'prepare'};
        const lifetime=call(()=>prepareSourceProjectileScheduledRoot(root,runtime,current));
        active={child:current,stage:'snapshot',lifetime};
        const x=call(()=>allocator.readU32(current,0x20));
        const y=call(()=>allocator.readU32(current,0x24));
        call(()=>allocator.writeU32(current,0x2c,x));
        call(()=>allocator.writeU32(current,0x30,y));
        const z=call(()=>allocator.readU32(current,0x28));call(()=>allocator.writeU32(current,0x34,z));
        const rotation=call(()=>allocator.readU32(current,0x70));
        call(()=>allocator.writeSchedulerRotation76(current,rotation,runtime));
        const roll=call(()=>allocator.readU16(current,0x74));call(()=>allocator.writeU16(current,0x7a,roll));
        const callback=call(()=>allocator.readU32(current,0x0c));
        active={child:current,stage:'callback',lifetime,callback};
        if (callback!==0x8007dcec) fail('reached unsupported stored object callback');
        call(()=>invokeSourceProjectileScheduledRoot(root,runtime,current));
        active={child:current,stage:'after',lifetime};
        // The source does not revalidate active0 or completed-spawn ownership
        // after cleanup. It reads the SAME original bytes, then the live next8.
        if (call(()=>allocator.readS8(current,0x86))!==0) call(()=>allocator.writeU8(current,0x1ca,0));
      }
      child=call(()=>allocator.readPointer(current,8));
    }
    active=undefined;
  };
  const group = (bits: number): void => {
    if ((bits|0)<0x38 && (bits&7)!==7 && (mask(bits)&0x80)!==0) return;
    walk(head(bits));
  };
  const slots = (bits: number): void => {
    if ((bits|0)>=0x38) return;
    for(let i=0;i<6;i++) {
      const actual=record(read(sources,'actorSlots'),'actual803c4e84 table');
      if(actual===sources || actual===globals || actual===root.getDrawList() ||
        call(()=>allocator.getRetainedStorageOwners()).includes(actual)) fail('actor slots alias another source owner');
      if(slotsOwner!==undefined && slotsOwner!==actual) fail('actor-slot table owner changed');
      slotsOwner=actual;
      const id=pointer(read(actual,String(i)),'actor-slot pointer');
      if(id===null) fail('null source actor slot at reached active0 dereference');
      const actor=call(()=>allocator.getPointerTarget(id));
      // No existing byte0 alias may coexist with this missing actor-header field.
      if(Object.getOwnPropertyDescriptor(actor,'0')!==undefined) fail('competing raw byte0 actor-active owner');check();
      const enabled=unsigned(read(actor,'active0'),255,'actor active0');
      if((enabled<<24>>24)!==0 && (mask(bits)&(1<<i))===0) walk(head((bits+i+1)>>>0));
    }
  };
  const run = (bits: number,operation: (bits: number) => void): void => {
    unsigned(bits,0xffffffff,'group register');
    if(busy) {poisoned=true;fail('same-runtime reentry unsupported');}
    if(incomplete) fail('permanently incomplete source scheduler');
    busy=true;poisoned=false;visits=0;
    try {
      if(read(sources,'root')!==root || call(()=>root.getSpawnRuntime())!==spawns ||
        call(()=>spawns.getAllocatorRuntime())!==allocator) fail('scheduler runtime owner changed');
      operation(bits);check();
    } catch(error) {
      incomplete=true;
      // After cleanup there may be no completedSpawns entry. The root retains
      // its original captured actors, so closure does not recover a freed token.
      markIncompleteSourceObjectAllocation(allocator);
      markIncompleteSourceProjectileScheduledRoot(root,runtime);
      throw error;
    } finally {active=undefined;busy=false;}
  };
  const runtime: SourceObjectSchedulerRuntime = {
    getRootRuntime() {return root;},getAllocatorRuntime() {return allocator;},getMatchGlobals() {return globals;},
    runGroup(bits) {run(bits,group);}, runSlots(bits) {run(bits,slots);},
    runWrapper(bits) {run(bits,value=>{
      if((value|0)<0x38 && (value&7)===0) {slots(value);group(value);group((value+7)>>>0);}
      else group(value);
    });},
  };
  scopes.set(runtime,(selectedRoot,selectedAllocator,child,stage,lifetime)=>{
    if(!busy || (stage!=='closure' && (incomplete || poisoned)) ||
      (selectedRoot!==undefined && selectedRoot!==root) || (selectedAllocator!==undefined && selectedAllocator!==allocator))
      fail('private active scheduler invocation required');
    if(stage==='closure') return;
    if(!active || active.child!==child || active.stage!==stage ||
      (stage==='callback' && (active.callback!==0x8007dcec || active.lifetime!==lifetime)))
      fail('private exact scheduler stage/child/lifetime required');
  });
  runtimes.add(runtime);claims.set(root,runtime);return Object.freeze(runtime);
}
