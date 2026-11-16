import {createSourceActorProjectileSpawnRuntime, isSourceActorProjectileSpawnRuntime,
  type SourceActorProjectileSpawnSources, type SourceActorProjectileSpawnRuntime,
  type SourceActorProjectileSpawnBinding} from './actor-projectile-spawn.js';
import type {SourceAllocationBytes, SourceObjectAllocationRuntime, SourceObjectPool, SourceDescriptorPool} from './source-object-allocation.js';
import {hasIncompleteSourceActorDoubleLifecycle} from './actor-double-prehook.js';
import type {RomActor} from './actor.js';

/** Supplied exclusively by the genuine attached composition test factory. This
 * test-only builder is not accepted by any executable source runtime. It avoids
 * recreating the graph with successful stand-in callees in a second fixture. */
export interface SourceActorProjectileSpawnTestFixture {
  id: symbol; actual: RomActor;
  spawn: SourceActorProjectileSpawnRuntime;
  allocator: SourceObjectAllocationRuntime;
  child: symbol; childBytes: SourceAllocationBytes;
  objectPool: SourceObjectPool; descriptorPool: SourceDescriptorPool;
  sources: SourceActorProjectileSpawnSources;
  setupPart0: {group28: number; action29: number};
  initial: Partial<SourceActorProjectileSpawnBinding>;
}
function check(ok: boolean, why: string): void {if (!ok) throw Error(`[actor-projectile-spawn-test] ${why}`);}
function equal(actual: unknown, expected: unknown, why: string): void {
  check(Object.is(actual,expected),`${why}: got ${String(actual)}, expected ${String(expected)}`);
}
function rejects(run: () => unknown, fragment: string): void {
  let message = ''; try {run();} catch (error) {message = String(error);}
  check(message.includes(fragment),`expected ${fragment}, got ${message || 'success'}`);
}
function observe(run: () => void, onRead: (owner: object, key: PropertyKey) => void): void {
  const original = Object.getOwnPropertyDescriptor;
  Object.getOwnPropertyDescriptor = ((owner: object,key: PropertyKey) => {
    onRead(owner,key); return original(owner,key);
  }) as typeof original;
  try {run();} finally {Object.getOwnPropertyDescriptor = original;}
}
function closed(x: SourceActorProjectileSpawnTestFixture): void {
  check(hasIncompleteSourceActorDoubleLifecycle(x.actual),'partial spawn closes canonical Double lifecycle');
  rejects(() => x.spawn.spawn(x.id,1),'incomplete');
  rejects(() => x.allocator.writeU8(x.child,0,0),'incomplete');
}
export function runActorProjectileSpawnSelfTests(make: () => SourceActorProjectileSpawnTestFixture): void {
  {
    const x = make();
    check(isSourceActorProjectileSpawnRuntime(x.spawn) && Object.isFrozen(x.spawn),'genuine frozen runtime');
    for (const forged of [{...x.spawn},Object.create(x.spawn),{},null])
      check(!isSourceActorProjectileSpawnRuntime(forged),'copied methods cannot forge runtime');
    equal(x.spawn.getActualActor(x.id),x.actual,'same actual actor');
    equal(x.spawn.getAllocatorRuntime(),x.allocator,'same genuine allocator');
    equal(x.spawn.getPrehookRuntime(),x.sources.prehook,'same genuine prehook');
    check(x.spawn.getActorBinding(x.id) !== x.initial && Object.isSealed(x.spawn.getActorBinding(x.id)),'missing90 copied/sealed');
    const initial90 = x.spawn.getActorBinding(x.id).pointer90;
    x.initial.pointer90 = null;
    equal(x.spawn.getActorBinding(x.id).pointer90,initial90,'caller initial cannot rewrite canonical90');
    const row = x.sources.row1;
    (row as {family2e:number}).family2e = -1;
    (row.local04 as {x:number}).x = -99;
    equal(x.spawn.spawn(x.id,1),x.child,'copied authenticated row survives caller mutation');
    equal(x.allocator.readU8(x.child,0x11),1,'authentic variant stored');
    check(!hasIncompleteSourceActorDoubleLifecycle(x.actual),'completed standalone spawn remains usable');
  }
  {
    const x = make(), a = x.actual, m = x.sources.world.getWorldMatrix(x.id,11);
    const matrixId = x.sources.world.getStorage(x.id).matrices8d4[11]!;
    const expected = {x:0,y:0,z:0};
    x.sources.world.getMatricesRuntime().transformPoint(matrixId,x.sources.row1.local04,expected);
    check(m === x.sources.world.getMatricesRuntime().getMatrix(matrixId),'one canonical joint matrix');
    const poolCount=x.objectPool.count!, descriptorCount=x.descriptorPool.count!;
    equal(x.spawn.spawn(x.id,0x101),x.child,'row index and stored variant use actual low8 bits');
    equal(x.allocator.getObject(x.child),x.childBytes,'allocation backing not copied/replaced');
    equal(x.objectPool.count,(poolCount-1)&65535,'real object pop');
    equal(x.descriptorPool.count,(descriptorCount-1)&65535,'real descriptor pop');
    for (const [offset,value] of [[0,1],[0x10,15],[0x11,1],[0x96,a.carriedSlot96],[0x97,a.carriedVariant97],[0x88,a.team],
      [0xd0,x.sources.admission.getActorBinding(x.id).byteD0!],[0x150,x.setupPart0.group28],[0x151,x.setupPart0.action29]] as const)
      equal(x.allocator.readU8(x.child,offset),value,`source byte${offset.toString(16)}`);
    equal(x.allocator.readU16(x.child,0x94),a.borgMirror94,'source identity halfword');
    equal(x.allocator.readU32(x.child,0xc),0x8007dcec,'numeric future root callback');
    equal(x.allocator.readU32(x.child,0x10c),0x8007e698,'numeric future child callback');
    equal(x.allocator.readPointer(x.child,0x8c),x.id,'canonical owner pointer');
    for (const [offset,target] of [[0x90,x.spawn.getActorBinding(x.id).pointer90!],
      [0xc8,x.sources.admission.getActorBinding(x.id).pointerc8!],[0xcc,a.visibilityTarget]] as const) {
      const value=x.allocator.readPointer(x.child,offset);
      equal(value===null?null:x.allocator.getPointerTarget(value),target,`same pointer owner${offset.toString(16)}`);
    }
    for (const offset of [0xb4,0x58,0x5c,0x60]) equal(x.allocator.readF32(x.child,offset),a.modelScale,'fresh source model scale');
    equal(x.allocator.readF32(x.child,0xb8),x.sources.gauges.getActorBinding(x.id).targetScaleB8,'same gaugeB8');
    equal(x.allocator.readF32(x.child,0xc0),a.collisionScale,'actual collision scale without fallback');
    equal(x.allocator.readF32(x.child,0xc4),x.sources.gauges.getActorBinding(x.id).fieldC4,'same gaugeC4');
    for (const [axis,offset] of [['x',0x20],['y',0x24],['z',0x28]] as const)
      equal(x.allocator.readF32(x.child,offset),expected[axis],`exact transformed ${axis}`);
    for (const [axis,offset] of [['x',0x144],['y',0x148],['z',0x14c]] as const)
      equal(x.allocator.readF32(x.child,offset),a.aimOrigin518[axis],`raw source aim ${axis}`);
  }
  {
    const x=make(),before=x.objectPool.count;
    x.actual.borgNumber=4;
    Object.defineProperty(x.descriptorPool,'count',{get(){throw Error('unreached descriptor count');}});
    (x.sources.gauges.getActorBinding(x.id) as {targetScaleB8:unknown}).targetScaleB8=undefined;
    equal(x.spawn.spawn(x.id,1),null,'source family mismatch returns before allocator and scalar metadata');
    equal(x.objectPool.count,before,'mismatch no object pop');
    check(!hasIncompleteSourceActorDoubleLifecycle(x.actual),'genuine family mismatch not failure');
  }
  for(const variant of [0,2,3,255]) {
    const x=make(),before=x.objectPool.count;
    rejects(()=>x.spawn.spawn(x.id,variant),`row${variant} is not authenticated`);
    equal(x.objectPool.count,before,'unread source row never allocates'); closed(x);
  }
  {
    const x=make();
    (x.spawn.getActorBinding(x.id) as {pointer90:unknown}).pointer90=undefined;
    rejects(()=>x.spawn.spawn(x.id,1),'pointer90');
    equal(x.allocator.readU8(x.child,0),1,'allocation and first activation survive missing90');
    equal(x.allocator.readPointer(x.child,0x8c),x.id,'8c precedes90 load');
    equal(x.allocator.readU16(x.child,0x94),0,'missing90 before identity copy'); closed(x);
  }
  {
    const x=make(),a=x.actual;
    (a as unknown as {collisionScale:unknown}).collisionScale=undefined;
    rejects(()=>x.spawn.spawn(x.id,1),'collisionScale');
    for(const offset of [0xb4,0x58,0x5c,0x60])equal(x.allocator.readF32(x.child,offset),a.modelScale,'preceding model-scale stores retained');
    equal(x.allocator.readU8(x.child,0xd0),0,'missingc0 beforeD0'); closed(x);
  }
  {
    const x=make();let injected=false;
    observe(()=>rejects(()=>x.spawn.spawn(x.id,1),'non-writable'),(owner,key)=>{
      if(!injected&&owner===x.actual&&key==='borgMirror94'){
        // Host adversarial mutation AFTER allocation memset, at the first source
        //94 load. The reached halfword store must not write just its first byte.
        injected=true;Object.defineProperty(x.childBytes,String(0x95),{writable:false});
      }
    });
    check(injected,'fault injected after positive allocation');
    equal(x.allocator.readPointer(x.child,0x8c),x.id,'earlier owner stores retained');
    equal(x.allocator.readU16(x.child,0x94),0,'scalar destination preflight avoids half-written94');
    equal(x.allocator.readU8(x.child,0x96),0,'96 not reached'); closed(x);
  }
  {
    const x=make(),matrix=x.sources.world.getWorldMatrix(x.id,11) as number[];
    matrix[11]=Number.NaN;
    rejects(()=>x.spawn.spawn(x.id,1),'finite');
    // Source m11 is read after X is stored, before Y is stored. The fixture's
    // nonzero X proves this is not a detached successful-transform snapshot.
    check(x.allocator.readF32(x.child,0x20)!==0,'exact matrix X prefix retained');
    equal(x.allocator.readF32(x.child,0x24),0,'matrix m11 fault precedes Y store');
    equal(x.allocator.readF32(x.child,0x28),0,'matrix fault precedes Z store');
    equal(x.allocator.readF32(x.child,0x144),0,'matrix fault precedes saved aim'); closed(x);
  }
  {
    const x=make();(x.setupPart0 as {group28:unknown}).group28=undefined;
    rejects(()=>x.spawn.spawn(x.id,1),'group28');
    equal(x.allocator.readF32(x.child,0x14c),x.actual.aimOrigin518.z,'entire saved aim precedes setup group');
    equal(x.allocator.readU8(x.child,0x150),0,'missing group has not been invented'); closed(x);
  }
  {
    const x=make();let sawSource=false,loadedY=false;
    observe(()=>equal(x.spawn.spawn(x.id,1),x.child,'saved aim stores finish'),(owner,key)=>{
      if(owner===x.actual.aimOrigin518&&key==='x')sawSource=true;
      if(sawSource&&owner===x.actual.aimOrigin518&&key==='y')loadedY=true;
      if(sawSource&&owner===x.childBytes&&key===String(0x144))check(loadedY,'source aim X/Y loaded before first destination store');
    });
    check(loadedY,'actual source aim pair observed');
  }
  {
    const x=make();let injected=false;
    observe(()=>rejects(()=>x.spawn.spawn(x.id,1),'reentry'),(owner,key)=>{
      if(!injected&&owner===x.actual&&key==='modelScale'){
        injected=true;try{x.spawn.spawn(x.id,1);}catch{/* adversarial catcher must not restore the outer operation */}
      }
    });
    check(injected,'reentry was attempted at reached source scale');
    equal(x.allocator.readU8(x.child,0),1,'reentry preserves earlier real allocated activation'); closed(x);
  }
  {
    const x=make(),values=[1.25,2.5,3.75,4.5];let reads=0;
    observe(()=>equal(x.spawn.spawn(x.id,1),x.child,'fresh B4 load sequence completes'),(owner,key)=>{
      if(owner===x.actual&&key==='modelScale')x.actual.modelScale=values[reads++]!;
    });
    equal(reads,4,'four actual B4 source loads, not one cached scale');
    for(const [i,offset]of[0xb4,0x58,0x5c,0x60].entries())
      equal(x.allocator.readF32(x.child,offset),values[i],'source B4 reload observed at each separate store');
  }
  {
    const x=make();let injected=false,sawZ=false;
    observe(()=>rejects(()=>x.spawn.spawn(x.id,1),'non-writable'),(owner,key)=>{
      if(!injected&&owner===x.actual.aimOrigin518&&key==='y'){
        injected=true;Object.defineProperty(x.childBytes,String(0x149),{writable:false});
      }
      if(owner===x.actual.aimOrigin518&&key==='z')sawZ=true;
    });
    check(injected&&!sawZ,'aim XY precede stores; failed second store does not read Z');
    equal(x.allocator.readF32(x.child,0x144),x.actual.aimOrigin518.x,'first saved aim store retained');
    equal(x.allocator.readU32(x.child,0x148),0,'failed second aim word has no partial bytes');
    equal(x.allocator.readU32(x.child,0x14c),0,'later aim Z untouched');closed(x);
  }
  {
    const x=make(),matrix=x.sources.world.getWorldMatrix(x.id,11);let injected=false;
    observe(()=>rejects(()=>x.spawn.spawn(x.id,1),'non-writable'),(owner,key)=>{
      if(!injected&&owner===matrix&&key==='0'){
        injected=true;Object.defineProperty(x.childBytes,String(0x25),{writable:false});
      }
    });
    check(injected&&x.allocator.readF32(x.child,0x20)!==0,'same-child transform X store survives destination Y fault');
    equal(x.allocator.readU32(x.child,0x24),0,'Y stfs preflights all bytes');
    equal(x.allocator.readU32(x.child,0x28),0,'Z store not reached');closed(x);
  }
  {
    const x=make(),clone=x.sources.prehook.getCloneOwner(x.id);
    check(clone!==undefined,'genuine composed Double owner exists');
    clone!.arm7c8=255;clone!.offset7b0.x=Number.NaN;
    equal(x.spawn.spawn(x.id,1),x.child,'row1 flag0 never reads clone arm or offset scalar');
    check(!hasIncompleteSourceActorDoubleLifecycle(x.actual),'unread clone fields do not invent a spawn failure');
  }
  {
    const x=make();Object.defineProperty(x.actual,'modelScale',{writable:false});
    equal(x.spawn.spawn(x.id,1),x.child,'readonly input source modelScale is allowed');
  }
  {
    const x=make(),before=x.objectPool.count;
    Object.defineProperty(x.actual,'pointer90',{value:x.actual,configurable:true});
    rejects(()=>x.spawn.spawn(x.id,1),'pointer90: competing source storage');
    equal(x.objectPool.count,before,'duplicate owner rejected before allocation');closed(x);
  }
  {
    const x=make();rejects(()=>createSourceActorProjectileSpawnRuntime({...x.sources,row1:{...x.sources.row1,offset2c:1}}),'authenticated');
    equal(x.spawn.spawn(x.id,1),x.child,'invalid new configuration does not poison existing genuine runtime');
  }
  for(const key of ['prehook','world','admission','gauges','setup','allocator'] as const) {
    const x=make();rejects(()=>createSourceActorProjectileSpawnRuntime({...x.sources,[key]:{...x.sources[key]}}),'genuine');
  }
  console.log('[actor-projectile-spawn-test] PASS: genuine allocation, exact same-child metadata/matrix stores, copied row1, lazy missing/readonly/matrix faults, source order and permanent shared failure; no flight/clone or original execution claim');
}
