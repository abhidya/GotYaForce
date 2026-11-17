import {hasIncompleteSourceActorDoubleLifecycle} from './actor-double-prehook.js';
import {createSourceProjectileRootRuntime} from './projectile-root-lifecycle.js';
import type {SourceProjectileHitTestFixture} from './projectile-hit-registration.selftest.js';

/** Genuine completed-spawn/root/HIT composition with an explicit authenticated
 * state2 cell. Changed bytes and malformed records below are synthetic offline
 * test inputs, not retail hydration, a successful injected callee or scheduling.
 * State2 is one returning invocation; state3/free/draw removal stay unsupported. */
export interface SourceProjectileRetirementTestFixture extends SourceProjectileHitTestFixture {
  rootSources: SourceProjectileHitTestFixture['rootSources'] & {retirementState2?: number};
}
const CELL = 0x8007e63c;
function check(ok: boolean, why: string): void {if (!ok) throw Error(`[projectile-retirement-test] ${why}`);}
function equal(actual: unknown, expected: unknown, why: string): void {
  check(Object.is(actual,expected),`${why}: got ${String(actual)}, expected ${String(expected)}`);
}
function rejects(run: () => unknown, fragment: string): void {
  let message='';try {run();} catch(error) {message=String(error);}
  check(message.includes(fragment),`expected ${fragment}, got ${message || 'success'}`);
}
/** Inspect source loads/store preflights without replacing any genuine callee.
 * The optional after hook mutates only after the original descriptor is saved. */
function observe(run: () => void, before: (owner: object,key: PropertyKey) => void,
  after?: (owner: object,key: PropertyKey) => void): void {
  const original=Object.getOwnPropertyDescriptor;
  Object.getOwnPropertyDescriptor=((owner: object,key: PropertyKey)=>{
    before(owner,key);const result=original(owner,key);after?.(owner,key);return result;
  }) as typeof original;
  try {run();} finally {Object.getOwnPropertyDescriptor=original;}
}
function retained(record: object, except: readonly number[] = []): () => void {
  const before=Object.getOwnPropertyDescriptors(record),ignored=new Set(except.map(String));
  return ()=>{
    const after=Object.getOwnPropertyDescriptors(record);
    equal(Reflect.ownKeys(after).length,Reflect.ownKeys(before).length,'retained own-property count');
    for(const key of Reflect.ownKeys(before)) {
      if(typeof key==='string' && ignored.has(key)) continue;
      const a=Reflect.get(after,key) as PropertyDescriptor|undefined,b=Reflect.get(before,key) as PropertyDescriptor;
      check(a!==undefined && Object.is(a.value,b.value) && a.get===b.get && a.set===b.set &&
        a.writable===b.writable && a.configurable===b.configurable && a.enumerable===b.enumerable,
      `retained descriptor ${String(key)}`);
    }
  };
}
function surrounding(x: SourceProjectileRetirementTestFixture): () => void {
  // Includes actual allocator pool3/pool4/group/descriptor owners and their
  // current byte records, not merely copies of the exposed list heads.
  const records=new Set([...x.allocator.getSourceOwners(x.actor),x.nextObjectBytes,x.drawList,
    x.hitPool,x.descriptorPool,x.descriptorBytes,x.nextDescriptorBytes,...x.hitBytes,
    ...Object.values(x.groups),x.hitBinding,x.hitBinding.pointer27c,x.hitBinding.pointer3fc]);
  records.delete(x.objectBytes);
  const keep=[...records].map(record=>retained(record));return ()=>keep.forEach(assert=>assert());
}
function byte(x: SourceProjectileRetirementTestFixture,offset: number): number {
  return x.allocator.readU8(x.child,offset);
}
function closed(x: SourceProjectileRetirementTestFixture): void {
  check(hasIncompleteSourceActorDoubleLifecycle(x.sourceActor),'failure closes the same actual Double owner');
  const keep=surrounding(x),child=retained(x.objectBytes);
  rejects(()=>x.root.dispatchStoredRoot(x.child),'incomplete');
  rejects(()=>x.hits.registerHit(x.child,1),'incomplete');
  rejects(()=>x.projectiles.spawn(x.actor,1),'incomplete');
  rejects(()=>x.allocator.writeU8(x.nextChild,0,1),'incomplete');child();keep();
}
function state2(x: SourceProjectileRetirementTestFixture,type=3): void {
  x.objectBytes[0x18]=2;x.objectBytes[2]=type;x.objectBytes[0x1d8]=0x5b;x.objectBytes[0x82]=0x6a;
}
function finished(x: SourceProjectileRetirementTestFixture,type=3): void {
  equal(byte(x,0x18),3,'one actual state2 invocation stores state3');
  equal(byte(x,0x1d8),type===0 || type===3?1:0x5b,'actual8aff0 invalidates only raw type0/3');
  equal(byte(x,0x82),0,'caller clears82 only after helper return');
  check(!hasIncompleteSourceActorDoubleLifecycle(x.sourceActor),'returned state2 handler leaves the shared owner complete');
  x.projectiles.assertActorComplete(x.actor);
}

export function runProjectileRetirementSelfTests(make: () => SourceProjectileRetirementTestFixture): void {
  for(const mode of ['negative-remap','empty-pool','negative-descriptors'] as const) {
    const x=make(),a=x.allocator;
    equal(x.rootSources.retirementState2,CELL,'factory explicitly supplies authenticated state2 cell');
    equal(x.root.getObject(x.child),x.objectBytes,'root retains canonical completed child bytes');
    equal(a.getObject(x.child),x.objectBytes,'allocator shares the identical canonical byte record');
    equal(x.root.getSpawnRuntime(),x.projectiles,'retirement uses the original genuine spawn graph');
    if(mode==='negative-remap') x.hitBinding.pointer3fc[0xa24]=255;
    else if(mode==='empty-pool') x.hitPool.head=null;
    else x.descriptorPool.count=0x8000;
    let cells=0;
    const untouchedHits=x.hitBytes.map(record=>retained(record));
    observe(()=>x.root.dispatchStoredRoot(x.child),(owner,key)=>{
      if(owner===x.rootSources && key==='retirementState2') cells++;
    });
    equal(cells,0,'zero-HIT initializer returns without inline state2 dispatch or metadata admission');
    equal(byte(x,0x18),2,`genuine ${mode} HIT result0 reaches initial epilogue`);
    equal(byte(x,0x1d8),0,'initial zero-HIT path has not yet called retirement invalidation');
    equal(x.hitPool.count,4,'zero-result path consumes no HIT object');
    equal(x.groups[49]!.head,null,'zero-result path never inserts HIT group');untouchedHits.forEach(assert=>assert());
    equal(x.drawList.head,x.child,'first invocation already inserted the genuine draw node');
    equal(x.drawList.tail,x.child,'real draw tail remains the original child');
    equal(a.readU32(x.child,0xc),0x8007dcec,'stored root callback is retained, not replaced with state2 address');
    equal(a.readU32(x.child,0x100),0x80047aa4,'real draw callback remains stored');
    const keep=surrounding(x),child=retained(x.objectBytes,[0x18,0x1d8,0x82]);
    observe(()=>x.root.dispatchStoredRoot(x.child),(owner,key)=>{
      if(owner===x.rootSources && key==='retirementState2') cells++;
    });
    equal(cells,1,'only the later root invocation admits the selected state2 cell');finished(x);child();keep();
    equal(x.root.getObject(x.child),x.objectBytes,'completion never replaces or frees child storage');
    equal(byte(x,0),1,'state2 does not execute object freeing');
    const noLaterEffects=retained(x.objectBytes);
    rejects(()=>x.root.dispatchStoredRoot(x.child),'state3 dispatch');noLaterEffects();keep();closed(x);
  }
  for(const reason of ['life','family'] as const) for(const initial of [0,1,128,255]) {
    const x=make();x.objectBytes[0x18]=initial;x.objectBytes[0x82]=0x6a;x.objectBytes[0x1d8]=0x5b;
    if(reason==='life') {x.stageState.lifecycle18=2;x.sourceActor.borgNumber=Number.NaN;delete x.objectBytes[0x94];}
    else x.allocator.writeU16(x.child,0x94,0xffff);
    const events:string[]=[],keep=surrounding(x),child=retained(x.objectBytes,[0x18,0x1d8,0x82]);
    observe(()=>x.root.dispatchStoredRoot(x.child),(owner,key)=>{
      if(owner===x.objectBytes && ['24','2','472','130'].includes(String(key)))
        events.push(`${Number(key).toString(16)}:${String(x.objectBytes[0x18])}`);
      if(reason==='life' && ((owner===x.sourceActor && key==='borgNumber') ||
        (owner===x.objectBytes && (key==='148' || key==='149')))) throw Error('retired owner must skip family loads');
    });
    equal(events.join(','),[`18:${initial}`,`18:${initial}`,'2:2','1d8:2','82:2','18:2','18:2','2:3','1d8:3','82:3'].join(','),
      'signed initial guard retires first, fresh state2 selection invokes a second ordered invalidation');
    finished(x);child();keep();equal(x.drawList.head,null,'same-call owner retirement does not initialize draw membership');
    equal(x.allocator.readU32(x.child,0x100),0,'same-call retirement never stores an initializer draw callback');
  }
  for(const type of [0,1,2,3,4,127,128,255]) {
    const x=make();state2(x,type);const events:string[]=[],keep=surrounding(x),child=retained(x.objectBytes,[0x18,0x1d8,0x82]);
    observe(()=>x.root.dispatchStoredRoot(x.child),(owner,key)=>{
      if(owner===x.objectBytes) events.push(`c${Number(key).toString(16)}`);
      if(owner===x.rootSources && key==='retirementState2') events.push('cell');
      if(owner===x.objectBytes && key==='2') equal(x.objectBytes[0x18],3,'state3 store precedes actual helper type load');
      if(owner===x.objectBytes && key==='472') equal(x.objectBytes[0x82],0x6a,'helper store precedes caller82');
    });
    equal(events.join(','),['cc','cd','ce','cf','c18','c90','c91','c92','c93','c18','cell','c18','c2',
      ...(type===0 || type===3?['c1d8']:[]),'c82'].join(','),'complete reached load and scalar-store-preflight source order');
    finished(x,type);child();keep();
  }
  for(const [first,second] of [[3,255],[255,0]] as const) {
    const x=make();x.objectBytes[2]=first;x.objectBytes[0x82]=0x6a;x.objectBytes[0x1d8]=0x5b;
    x.stageState.lifecycle18=2;let types=0,invalidations=0,clears=0;
    observe(()=>x.root.dispatchStoredRoot(x.child),(owner,key)=>{
      if(owner!==x.objectBytes) return;
      if(key==='2') types++;
      if(key==='472') invalidations++;
      if(key==='130' && ++clears===1) x.objectBytes[2]=second;
    });
    equal(types,2,'guard and handler independently reload actual raw helper type');
    equal(invalidations,1,'each separate helper invocation follows its own captured type');
    equal(clears,2,'both caller82 stores execute even if one helper does not invalidate');
    equal(byte(x,0x18),3,'same-call second helper returns');equal(byte(x,0x1d8),1,'only reached invalidation survives');
  }
  for(const owner of [null,'other'] as const) {
    const x=make();state2(x);x.allocator.writePointer(x.child,0x90,owner===null?null:x.nextChild);
    x.stageState.lifecycle18=Number.NaN;x.sourceActor.borgNumber=Number.NaN;delete x.objectBytes[0x94];
    const keep=surrounding(x),child=retained(x.objectBytes,[0x18,0x1d8,0x82]);
    observe(()=>x.root.dispatchStoredRoot(x.child),(record,key)=>{
      if((record===x.stageState && key==='lifecycle18') || (record===x.sourceActor && key==='borgNumber'))
        throw Error('saved state2 must not dereference pointer90 owner fields');
    });
    finished(x);child();keep();
  }
  for(const offset of [0x90,0x91,0x92,0x93]) {
    const x=make();state2(x);delete x.objectBytes[offset];let cells=0;
    observe(()=>rejects(()=>x.root.dispatchStoredRoot(x.child),`${offset}: own data property`),(owner,key)=>{
      if(owner===x.rootSources && key==='retirementState2') cells++;
    });
    equal(cells,0,'every byte of pointer90 is loaded before skipped-owner state2 selection');
    equal(byte(x,0x18),2,'pointer90 fault precedes handler state3');closed(x);
  }
  {
    const x=make();state2(x);x.stageState.lifecycle18=2;let changed=false;
    observe(()=>rejects(()=>x.root.dispatchStoredRoot(x.child),'state1 dispatch'),(owner,key)=>{
      if(!changed && owner===x.objectBytes && key==='144') {changed=true;x.objectBytes[0x18]=1;}
      if(owner===x.rootSources && key==='retirementState2') throw Error('fresh selected1 cannot admit state2');
    });
    check(changed,'pointer90 load observed');equal(byte(x,0x1d8),0x5b,'saved2 skips guard despite changed raw1');closed(x);
  }
  {
    const x=make();let changed=false;
    observe(()=>x.root.dispatchStoredRoot(x.child),(owner,key)=>{
      if(!changed && owner===x.objectBytes && key==='148') {changed=true;x.objectBytes[0x18]=2;}
    });
    check(changed,'matching guard family load observed');finished(x);
    equal(x.allocator.readU32(x.child,0x100),0,'fresh selected2 never substitutes saved state0 initialization');
  }
  for(const [original,replacement] of [[3,255],[255,0]] as const) {
    const x=make();state2(x,original);let loads=0;
    observe(()=>x.root.dispatchStoredRoot(x.child),(owner,key)=>{
      if(owner===x.objectBytes && key==='2') loads++;
    },(owner,key)=>{if(owner===x.objectBytes && key==='2') x.objectBytes[2]=replacement;});
    equal(loads,1,'helper compares and sign-extends exactly one captured raw byte');finished(x,original);
    equal(byte(x,2),replacement,'explicit post-load host mutation remains, without a helper type reread');
  }
  for(const type of [1,2,4,127,128,255]) {
    const x=make();state2(x,type);delete x.objectBytes[0x1d8];
    x.root.dispatchStoredRoot(x.child);
    equal(byte(x,0x18),3,'noninvalidating helper return completes state3');equal(byte(x,0x82),0,'caller82 still clears');
    check(!Object.hasOwn(x.objectBytes,'472'),'unreached1d8 is neither required nor fabricated');
  }
  for(const absent of ['missing','undefined','inherited'] as const) {
    const x=make();state2(x);delete x.rootSources.retirementState2;
    if(absent==='undefined') Object.defineProperty(x.rootSources,'retirementState2',{value:undefined,configurable:true});
    if(absent==='inherited') Object.setPrototypeOf(x.rootSources,{retirementState2:CELL});
    const keep=surrounding(x),child=retained(x.objectBytes);
    rejects(()=>x.root.dispatchStoredRoot(x.child),'state2 dispatch');child();keep();closed(x);
  }
  {
    const x=make();x.stageState.lifecycle18=2;x.objectBytes[0x82]=0x6a;delete x.rootSources.retirementState2;
    rejects(()=>x.root.dispatchStoredRoot(x.child),'state2 dispatch');
    equal(byte(x,0x18),2,'missing selected cell preserves earlier real guard state2 store');
    equal(byte(x,0x1d8),1,'missing selected cell does not roll back guard invalidation');
    equal(byte(x,0x82),0,'guard clear82 precedes the later missing-cell failure');
    x.rootSources.retirementState2=CELL;closed(x);
  }
  {
    const x=make();state2(x);Object.defineProperty(x.rootSources,'retirementState2',{writable:false});
    x.objectBytes[0x1d8]=Number.NaN;x.objectBytes[0x82]=Number.NaN;
    x.root.dispatchStoredRoot(x.child);finished(x);
    equal(x.rootSources.retirementState2,CELL,'read-only own-data cell is valid and never written');
  }
  for(const value of [-1,2**32,Number.NaN,Infinity,1.5,null,'2148009532',{},()=>CELL]) {
    const x=make();state2(x);Object.defineProperty(x.rootSources,'retirementState2',{value});
    rejects(()=>x.root.dispatchStoredRoot(x.child),'unsigned source integer');
    equal(byte(x,0x18),2,'malformed reached cell never executes handler');closed(x);
  }
  for(const value of [0,0x8007dd84,0x8007e63d,0x8007e678,0xffffffff]) {
    const x=make();state2(x);x.rootSources.retirementState2=value;
    rejects(()=>x.root.dispatchStoredRoot(x.child),'authenticated dispatch target differs');
    equal(byte(x,0x18),2,'different valid code word cannot substitute another handler');closed(x);
  }
  for(const malformed of ['missing','accessor','mismatch'] as const) {
    const x=make();let getter=false,reads=0;x.hitBinding.pointer3fc[0xa24]=255;
    if(malformed==='missing') delete x.rootSources.retirementState2;
    else if(malformed==='accessor') Object.defineProperty(x.rootSources,'retirementState2',{get(){getter=true;return CELL;},configurable:true});
    else x.rootSources.retirementState2=0;
    observe(()=>x.root.dispatchStoredRoot(x.child),(owner,key)=>{if(owner===x.rootSources && key==='retirementState2') reads++;});
    equal(reads,0,'initial-state zero-HIT return never validates optional retirement metadata');
    equal(byte(x,0x18),2,'first invocation still completes through real zero result');check(!getter,'unreached accessor is never invoked');
    rejects(()=>x.root.dispatchStoredRoot(x.child),malformed==='missing'?'state2 dispatch':malformed==='accessor'?'own data dispatch cell':'authenticated dispatch target differs');
    check(!getter,'reached dispatch accessor is rejected without invocation');
    Object.defineProperty(x.rootSources,'retirementState2',{value:CELL,writable:true,configurable:true});closed(x);
  }
  for(const selected of [1,3,127,128,255]) {
    const x=make();x.objectBytes[0x18]=selected;
    Object.defineProperty(x.rootSources,'retirementState2',{get(){throw Error('unselected metadata accessor must never run');}});
    observe(()=>rejects(()=>x.root.dispatchStoredRoot(x.child),`state${selected<<24>>24} dispatch`),(owner,key)=>{
      if(owner===x.rootSources && key==='retirementState2') throw Error('unselected optional metadata must not even be inspected');
    });closed(x);
  }
  {
    const x=make(),sources={...x.rootSources,drawList0:{head:null,tail:null}};let metadata=0;
    Object.defineProperty(sources,'retirementState2',{get(){throw Error('constructor must not invoke optional dispatch accessor');}});
    observe(()=>{createSourceProjectileRootRuntime(sources);},(owner,key)=>{
      if(owner===sources && key==='retirementState2') metadata++;
    });equal(metadata,0,'constructor defers optional dispatch metadata until fresh state2 is actually selected');
  }
  for(const target of [0x18,0x1d8,0x82]) {
    const x=make();state2(x);Object.defineProperty(x.objectBytes,String(target),{writable:false});
    const keep=surrounding(x),child=retained(x.objectBytes,[0x18,0x1d8,0x82]);
    rejects(()=>x.root.dispatchStoredRoot(x.child),`${target}: non-writable`);
    equal(byte(x,0x18),target===0x18?2:3,'handler destination fault preserves exactly the reached state store');
    equal(byte(x,0x1d8),target===0x82?1:0x5b,'helper invalidation is not reordered past a failed earlier store');
    equal(byte(x,0x82),0x6a,'clear82 does not precede a failed source store');child();keep();
    Object.defineProperty(x.objectBytes,String(target),{writable:true});closed(x);
  }
  for(const target of [2,0x1d8,0x82]) for(const mode of ['missing','accessor'] as const) {
    const x=make();state2(x);let getter=false;
    if(mode==='missing') delete x.objectBytes[target];
    else Object.defineProperty(x.objectBytes,String(target),{get(){getter=true;return 0;},configurable:true});
    rejects(()=>x.root.dispatchStoredRoot(x.child),`${target}: own data property`);
    equal(byte(x,0x18),3,'late source property fault keeps completed state3 store');
    if(target!==0x1d8) equal(byte(x,0x1d8),target===0x82?1:0x5b,'helper effect survives only a later82 fault');
    if(target!==0x82) equal(byte(x,0x82),0x6a,'unreached caller clear remains untouched');
    check(!getter,'source accessor is rejected rather than evaluated');closed(x);
  }
  for(const type of [-1,256,Number.NaN,Infinity,1.5]) {
    const x=make();state2(x,type);rejects(()=>x.root.dispatchStoredRoot(x.child),'byte2: unsigned integer');
    equal(byte(x,0x18),3,'invalid raw type fails after the state3 store');
    equal(byte(x,0x1d8),0x5b,'invalid raw type is never normalized to type0/3');equal(byte(x,0x82),0x6a,'failed helper never returns');closed(x);
  }
  {
    const x=make();state2(x);x.allocator.writeU32(x.child,0xc,0x8007e63c);
    const keep=retained(x.objectBytes);
    rejects(()=>x.root.dispatchStoredRoot(x.child),'unsupported stored projectile root callback');keep();closed(x);
  }
  for(const point of ['cell','state-store','type','invalidation','clear'] as const) {
    const x=make();state2(x);let injected=false,states=0;
    observe(()=>rejects(()=>x.root.dispatchStoredRoot(x.child),'reentry'),(owner,key)=>{
      if(owner===x.objectBytes && key==='24') states++;
      const reached=point==='cell'?owner===x.rootSources && key==='retirementState2':owner===x.objectBytes &&
        (point==='state-store'?key==='24' && states===3:key===String(point==='type'?2:point==='invalidation'?0x1d8:0x82));
      if(!injected && reached) {
        injected=true;try {x.root.dispatchStoredRoot(x.child);} catch {/* Catching cannot repair the outer root invocation. */}
      }
    });
    check(injected,'caught root reentry attempted at reached descriptor boundary');
    equal(byte(x,0x18),point==='cell'?2:3,'root reentry retains only the completed state-store prefix');
    equal(byte(x,0x1d8),point==='invalidation' || point==='clear'?1:0x5b,'entered scalar store completes before caller reentry check');
    equal(byte(x,0x82),point==='clear'?0:0x6a,'reentry after final scalar still closes completed source prefix');closed(x);
  }
  for(const target of [0x18,0x1d8,0x82]) {
    const x=make();state2(x);let injected=false,states=0;
    observe(()=>rejects(()=>x.root.dispatchStoredRoot(x.child),'reentry'),(owner,key)=>{
      if(owner===x.objectBytes && key==='24') states++;
      if(!injected && owner===x.objectBytes && key===String(target) && (target!==0x18 || states===3)) {
        injected=true;try {x.allocator.readU8(x.child,0);} catch {/* Allocator preflight must latch its own caught reentry. */}
      }
    });
    check(injected,'caught allocator reentry attempted during handler scalar preflight');
    equal(byte(x,0x18),target===0x18?2:3,'allocator reentry prevents the current scalar, not preceding stores');
    equal(byte(x,0x1d8),target===0x82?1:0x5b,'invalidation store is indivisible on allocator reentry');
    equal(byte(x,0x82),0x6a,'failed allocator preflight never commits final scalar');closed(x);
  }
  {
    const x=make();state2(x);x.frame.bindActor(x.actor);const child=retained(x.objectBytes),keep=surrounding(x);
    observe(()=>rejects(()=>x.root.dispatchStoredRoot(x.child),'frame-owned actor'),(owner,key)=>{
      if(owner===x.rootSources && key==='retirementState2') throw Error('direct frame-owned call must not reach dispatch metadata');
    });child();keep();
    check(!hasIncompleteSourceActorDoubleLifecycle(x.sourceActor),'scheduler refusal is not an invented failed root invocation');
  }
  console.log('[projectile-retirement-test] PASS: genuine zero-HIT and guarded state2 invocation, ordered state3/real8aff0/clear82 return, canonical byte and pool/list retention, lazy authenticated cell, partial faults and permanent shared reentry closure; state3/free/draw removal and frame-owned scheduling remain unsupported');
}
