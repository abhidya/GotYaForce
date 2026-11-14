import {hasIncompleteSourceActorDoubleLifecycle} from './actor-double-prehook.js';
import {createSourceProjectileRootRuntime} from './projectile-root-lifecycle.js';
import type {SourceAllocationBytes, SourceDescriptorPool, SourceObjectPool} from './source-object-allocation.js';
import type {SourceProjectileRetirementTestFixture} from './projectile-retirement.selftest.js';

/** Genuine spawn/HIT-zero/retirement/cleanup composition. Current pool records,
 * descriptor type0 and branch mutations are explicit synthetic offline inputs,
 * not retail hydration, original execution, a scheduler or injected free calls. */
export interface SourceProjectileCleanupTestFixture extends SourceProjectileRetirementTestFixture {
  rootSources: SourceProjectileRetirementTestFixture['rootSources'] & {cleanupState3?: number};
  descriptorPool: SourceDescriptorPool & {releaseCallback18?: number};
  objectPool: SourceObjectPool;
}
const CELL=0x8007e678, CALLBACK=0x80006ed8;
function check(ok:boolean,why:string):void {if(!ok) throw Error(`[projectile-cleanup-test] ${why}`);}
function equal(actual:unknown,expected:unknown,why:string):void {
  check(Object.is(actual,expected),`${why}: got ${String(actual)}, expected ${String(expected)}`);
}
function rejects(run:()=>unknown,fragment:string):void {
  let message='';try {run();} catch(error) {message=String(error);}
  check(message.includes(fragment),`expected ${fragment}, got ${message || 'success'}`);
}
/** Observe real own-data loads and store preflights, never replace a callee. */
function observe(run:()=>void,before:(owner:object,key:PropertyKey)=>void,
  after?:(owner:object,key:PropertyKey)=>void):void {
  const original=Object.getOwnPropertyDescriptor;
  Object.getOwnPropertyDescriptor=((owner:object,key:PropertyKey)=>{
    before(owner,key);const descriptor=original(owner,key);after?.(owner,key);return descriptor;
  }) as typeof original;
  try {run();} finally {Object.getOwnPropertyDescriptor=original;}
}
function retained(...records:object[]):()=>void {
  const snapshots=records.map(record=>Object.getOwnPropertyDescriptors(record));
  return ()=>records.forEach((record,index)=>{
    const saved=snapshots[index]!,actual=Object.getOwnPropertyDescriptors(record);
    equal(Reflect.ownKeys(actual).length,Reflect.ownKeys(saved).length,'retained own-property count');
    for(const key of Reflect.ownKeys(saved)) {
      const a=Reflect.get(actual,key) as PropertyDescriptor|undefined,b=Reflect.get(saved,key) as PropertyDescriptor;
      check(a!==undefined && Object.is(a.value,b.value) && a.get===b.get && a.set===b.set &&
        a.writable===b.writable && a.configurable===b.configurable && a.enumerable===b.enumerable,
      `retained descriptor ${String(key)}`);
    }
  });
}
function allRecords(x:SourceProjectileCleanupTestFixture):object[] {
  return [...new Set([...x.allocator.getSourceOwners(x.actor),x.objectBytes,x.nextObjectBytes,x.drawList,
    x.objectPool,x.hitPool,x.descriptorPool,x.descriptorBytes,x.nextDescriptorBytes,...x.hitBytes,
    ...Object.values(x.groups),x.hitBinding,x.hitBinding.pointer27c,x.hitBinding.pointer3fc])];
}
function closed(x:SourceProjectileCleanupTestFixture):void {
  check(hasIncompleteSourceActorDoubleLifecycle(x.sourceActor),'failure closes the actual shared Double owner');
  const keep=retained(...allRecords(x));
  rejects(()=>x.root.dispatchStoredRoot(x.child),'incomplete');
  let completed=true;try {x.projectiles.getSpawnOwnerIdentity(x.child);} catch {completed=false;}
  rejects(()=>x.hits.registerHit(x.child,1),completed?'incomplete':'completed genuine spawn');
  rejects(()=>x.projectiles.spawn(x.actor,1),'incomplete');
  rejects(()=>x.allocator.writeU8(x.nextChild,0,1),'incomplete');keep();
}
function byte(x:SourceProjectileCleanupTestFixture,offset:number):number {return x.allocator.readU8(x.child,offset);}
function descriptor(x:SourceProjectileCleanupTestFixture):symbol {return x.allocator.getPointerIdentity(x.descriptorBytes);}
function nextDescriptor(x:SourceProjectileCleanupTestFixture):symbol {return x.allocator.getPointerIdentity(x.nextDescriptorBytes);}
function pointer(x:SourceProjectileCleanupTestFixture,id:symbol,offset:number):symbol|null {return x.allocator.readPointer(id,offset);}
function ready(x:SourceProjectileCleanupTestFixture):void {
  x.hitBinding.pointer3fc[0xa24]=255;
  x.root.dispatchStoredRoot(x.child);equal(byte(x,0x18),2,'first genuine HIT-zero invocation returns state2');
  x.root.dispatchStoredRoot(x.child);equal(byte(x,0x18),3,'second genuine retirement invocation returns state3');
  equal(byte(x,0),1,'two completed callbacks do not free the child');
}
function released(x:SourceProjectileCleanupTestFixture):void {
  equal(byte(x,0),0,'actual89814 clears active byte');equal(pointer(x,x.child,4),null,'actual89814 clears queue next4');
  equal(x.root.getObject(x.child),x.objectBytes,'released entry retains the original byte owner');
  equal(x.allocator.getObject(x.child),x.objectBytes,'allocator never replaces freed canonical bytes');
  check(!hasIncompleteSourceActorDoubleLifecycle(x.sourceActor),'normal cleanup is not an incomplete invocation');
  x.projectiles.assertActorComplete(x.actor);
  const keep=retained(...allRecords(x));
  rejects(()=>x.projectiles.getSpawnOwnerIdentity(x.child),'completed');
  rejects(()=>x.root.dispatchStoredRoot(x.child),'released');
  rejects(()=>x.root.bindProjectile(x.child),'completed');keep();
  check(!hasIncompleteSourceActorDoubleLifecycle(x.sourceActor),'stale released dispatch refuses outside the owner-poisoning scope');
}
function word(prefix:string,offset:number,width=4):string[] {
  return Array.from({length:width},(_,i)=>`${prefix}${(offset+i).toString(16)}`);
}

export function runProjectileCleanupSelfTests(make:()=>SourceProjectileCleanupTestFixture):void {
  {
    const x=make(),a=x.allocator,d=descriptor(x),dn=nextDescriptor(x);
    equal(x.rootSources.cleanupState3,CELL,'factory explicitly supplies authenticated state3 cell');
    equal(x.descriptorPool.releaseCallback18,CALLBACK,'factory explicitly supplies real nonnull descriptor callback');
    equal(x.descriptorBytes[8],0,'descriptor source row0 is explicit, not a fabricated default');
    equal(a.getDescriptor(d),x.descriptorBytes,'genuine allocated descriptor is the canonical record');
    let cells=0;
    observe(()=>ready(x),(owner,key)=>{if(owner===x.rootSources && key==='cleanupState3') cells++;});
    equal(cells,0,'initial and retirement invocations never inspect state3 metadata');
    equal(x.groups[9]!.head,x.child,'genuine spawn inserted group9');
    equal(x.drawList.head,x.child,'genuine initialization inserted draw0');
    const keep=retained(x.hitPool,...x.hitBytes,x.hitBinding.pointer3fc,x.hitBinding.pointer27c);
    const events:string[]=[];
    observe(()=>x.root.dispatchStoredRoot(x.child),(owner,key)=>{
      if(owner===x.objectBytes && Number.isInteger(Number(key))) events.push(`c${Number(key).toString(16)}`);
      if(owner===x.nextObjectBytes && Number.isInteger(Number(key))) events.push(`n${Number(key).toString(16)}`);
      if(owner===x.descriptorBytes && Number.isInteger(Number(key))) events.push(`d${Number(key).toString(16)}`);
      if(owner===x.rootSources && key==='cleanupState3') events.push('cell');
      if(owner===x.groups[9] && (key==='head'||key==='tail')) events.push(`g.${String(key)}`);
      if(owner===x.drawList) events.push(`draw.${String(key)}`);
      if(owner===x.descriptorPool && ['activeHead','freeHead','count','releaseCallback18'].includes(String(key))) events.push(`dp.${String(key)}`);
      if(owner===x.objectPool && ['head','tail','count'].includes(String(key))) events.push(`p.${String(key)}`);
    });
    equal(events.join(','),[
      ...word('c',0xc),'c18',...word('c',0x90),'c18','cell',
      'c1',...word('c',4),...word('c',8),'g.head','c1','g.tail','c2',
      'c85',...word('c',0x104),...word('c',0x108),'draw.tail','draw.head',...word('c',0x100),'c85',
      'c99',...word('c',0xe0),...word('d',0xc),'d8','dp.releaseCallback18',...word('d',0xc),
      ...word('d',0),...word('d',4),'dp.activeHead','dp.freeHead',...word('d',0),'dp.freeHead','d9','dp.count','dp.count',
      'c99','c3','p.tail',...word('n',4),'c3','p.tail','c3','p.count','p.count','c0',...word('c',4),
    ].join(','),'complete reached source loads and scalar-store preflights follow independent PPC evidence');
    equal(x.groups[9]!.head,null,'single group node removed');equal(x.groups[9]!.tail,null,'group tail removed');
    equal(x.drawList.head,null,'draw head removed');equal(x.drawList.tail,null,'draw tail removed');
    equal(a.readU32(x.child,0x100),0,'draw callback clears after unlink');equal(byte(x,0x85),255,'draw class reset after callback');
    equal(x.descriptorPool.activeHead,null,'descriptor active head unlinked');equal(x.descriptorPool.freeHead,d,'descriptor prepended to actual free list');
    equal(pointer(x,d,0),dn,'descriptor points at old free head');equal(x.descriptorBytes[9],0,'descriptor active flag cleared');
    equal(x.descriptorPool.count,2,'descriptor signed-count increment stored as source halfword');
    equal(x.objectPool.head,x.nextChild,'nonempty object queue retains oldest head');equal(x.objectPool.tail,x.child,'released child appended to tail');
    equal(pointer(x,x.nextChild,4),x.child,'old tail receives original child');equal(x.objectPool.count,2,'object pool count restored');
    equal(pointer(x,x.child,0xe0),d,'cleanup does not invent a descriptor-slot clear');
    equal(a.readU32(x.child,0xc),0x8007dcec,'cleanup does not clear stored root callback');
    equal(byte(x,0x18),3,'cleanup does not invent a new state');keep();released(x);
  }
  {
    const x=make();ready(x);x.root.dispatchStoredRoot(x.child);released(x);
    equal(x.projectiles.spawn(x.actor,1),x.nextChild,'real pool3 queue allocates older free object first');
    equal(x.projectiles.spawn(x.actor,1),x.child,'second genuine allocation reuses the identical released bytes');
    equal(x.allocator.getObject(x.child),x.objectBytes,'real allocator memset reuses canonical record');
    const keep=retained(...allRecords(x));rejects(()=>x.root.dispatchStoredRoot(x.child),'released');keep();
    check(!hasIncompleteSourceActorDoubleLifecycle(x.sourceActor),'new spawn alone cannot revive the old root entry');
    x.root.bindProjectile(x.child);
    ready(x);x.root.dispatchStoredRoot(x.child);released(x);
    equal(x.groups[9]!.head,x.nextChild,'second cleanup preserves independently live next projectile');
    equal(x.groups[9]!.tail,x.nextChild,'live neighbor remains group tail after reused child removal');
    equal(x.objectPool.head,x.child,'empty pool receives recycled child as head');
    equal(x.objectPool.tail,x.child,'empty pool receives recycled child as tail');
  }
  for(const topology of ['none','head','tail','middle'] as const) {
    const x=make();ready(x);const a=x.allocator,g=x.groups[9]!,previous=x.hitIds[0]!,next=x.hitIds[1]!;
    const p=topology==='tail'||topology==='middle'?previous:null,n=topology==='head'||topology==='middle'?next:null;
    a.writePointer(x.child,4,p);a.writePointer(x.child,8,n);
    g.head=p??x.child;g.tail=n??x.child;
    if(p!==null) a.writePointer(p,8,x.child);if(n!==null) a.writePointer(n,4,x.child);
    const events:string[]=[];let mutated=false;
    observe(()=>x.root.dispatchStoredRoot(x.child),(owner,key)=>{
      const headTail=owner===g && (key==='head'||key==='tail'),
        previousStore=owner===x.hitBytes[0] && Number(key)>=8 && Number(key)<12,
        nextStore=owner===x.hitBytes[1] && Number(key)>=4 && Number(key)<8;
      if(headTail) events.push(String(key));if(previousStore) events.push(`p${String(key)}`);if(nextStore) events.push(`n${String(key)}`);
      if(!mutated && (headTail||previousStore||nextStore)) {
        mutated=true;for(let i=4;i<12;i++) x.objectBytes[i]=0;
      }
    });
    equal(events.join(','),topology==='none'?'head,tail':topology==='head'?'head,n4,n5,n6,n7':
      topology==='tail'?'tail,p8,p9,p10,p11':'p8,p9,p10,p11,n4,n5,n6,n7','group unlink store order');
    equal(g.head,p??n,'group head after unlink');equal(g.tail,n??p,'group tail after unlink');
    if(p!==null) equal(pointer(x,p,8),n,'captured group previous links to captured next');
    if(n!==null) equal(pointer(x,n,4),p,'captured group next links to captured previous');released(x);
  }
  {
    const x=make();ready(x);let changed=false;
    observe(()=>x.root.dispatchStoredRoot(x.child),(owner,key)=>{
      if(owner===x.groups[9] && key==='head' && !changed) {changed=true;x.objectBytes[1]=10;}
    });
    check(changed,'first group store observed');equal(x.groups[9]!.head,null,'first store uses captured signed group');
    equal(x.groups[9]!.tail,x.child,'old group tail is not substituted for fresh index');equal(x.groups[10]!.tail,null,'second sole-node store reloads group index');
  }
  for(const topology of ['none','head','tail','middle'] as const) {
    const x=make();ready(x);const a=x.allocator,previous=x.hitIds[2]!,next=x.hitIds[3]!;
    // Draw104 points toward the tail,108 toward the head, unlike group4/8.
    const p=topology==='tail'||topology==='middle'?previous:null,n=topology==='head'||topology==='middle'?next:null;
    a.writePointer(x.child,0x104,n);a.writePointer(x.child,0x108,p);
    x.drawList.head=p??x.child;x.drawList.tail=n??x.child;
    if(p!==null) a.writePointer(p,0x104,x.child);if(n!==null) a.writePointer(n,0x108,x.child);
    const events:string[]=[];let mutated=false;
    observe(()=>x.root.dispatchStoredRoot(x.child),(owner,key)=>{
      const headTail=owner===x.drawList,
        previousStore=owner===x.hitBytes[2] && Number(key)>=0x104 && Number(key)<0x108,
        nextStore=owner===x.hitBytes[3] && Number(key)>=0x108 && Number(key)<0x10c;
      if(headTail) events.push(String(key));if(previousStore) events.push(`p${Number(key).toString(16)}`);
      if(nextStore) events.push(`n${Number(key).toString(16)}`);
      if(!mutated && (headTail||previousStore||nextStore)) {
        mutated=true;for(let i=0x104;i<0x10c;i++) x.objectBytes[i]=0;x.objectBytes[0x85]=255;
      }
    });
    equal(events.join(','),topology==='none'?'tail,head':topology==='head'?'head,n108,n109,n10a,n10b':
      topology==='tail'?'tail,p104,p105,p106,p107':'n108,n109,n10a,n10b,p104,p105,p106,p107','draw unlink tail/head and neighbor store order');
    equal(x.drawList.head,p??n,'draw head after unlink');equal(x.drawList.tail,n??p,'draw tail after unlink');
    if(p!==null) equal(pointer(x,p,0x104),n,'draw previous links to captured next');
    if(n!==null) equal(pointer(x,n,0x108),p,'draw next links to captured previous');released(x);
  }
  for(const topology of ['none','head','tail','middle'] as const) {
    const x=make();ready(x);const a=x.allocator,d=descriptor(x),other=nextDescriptor(x);
    // A third canonical test record supplies a proper three-node active list.
    // It is an explicit synthetic input, never a copy/replacement of live bytes.
    const third=Symbol('synthetic third active descriptor'),thirdBytes:SourceAllocationBytes={};
    for(let offset=0;offset<0x2c;offset++) thirdBytes[offset]=0;
    a.registerDescriptor(third,thirdBytes);
    const p=topology==='tail'||topology==='middle'?other:null,n=topology==='head'?other:topology==='middle'?third:null;
    a.writePointer(d,0,p);a.writePointer(d,4,n);x.descriptorPool.activeHead=p??d;
    if(p!==null) a.writePointer(p,4,d);if(n!==null) a.writePointer(n,0,d);
    x.descriptorPool.freeHead=null;
    x.root.dispatchStoredRoot(x.child);
    equal(x.descriptorPool.activeHead,p??n,'descriptor active head replacement');
    if(p!==null) equal(pointer(x,p,4),n,'descriptor previous4 takes captured next');
    if(n!==null) equal(pointer(x,n,0),p,'descriptor next0 takes captured previous');
    equal(pointer(x,d,0),null,'released descriptor takes captured free head');
    equal(pointer(x,d,4),n,'source release preserves own next4');released(x);
  }
  for(const count of [0,0x7fff,0x8000,0xffff]) {
    const x=make();ready(x);x.descriptorPool.count=count;x.objectPool.count=count;
    x.root.dispatchStoredRoot(x.child);
    equal(x.descriptorPool.count,(count+1)&0xffff,'descriptor signed load plus truncating halfword store');
    equal(x.objectPool.count,(count+1)&0xffff,'object unsigned count increment wraps');released(x);
  }
  for(const empty of [false,true]) {
    const x=make();ready(x);
    if(empty) {x.objectPool.head=null;x.objectPool.tail=null;}
    let loads=0;
    observe(()=>x.root.dispatchStoredRoot(x.child),(owner,key)=>{
      if(owner===x.objectBytes && key==='3' && ++loads===2) x.objectBytes[3]=4;
    });
    equal(loads,3,'return queue independently reloads signed pool3 for second store and count');
    equal(x.objectPool.count,1,'fresh pool4 count does not change pool3 count');equal(x.hitPool.count,5,'third fresh pool index chooses pool4 count');
    if(empty) {equal(x.objectPool.tail,x.child,'first empty queue store uses captured pool3 tail');equal(x.hitPool.head,x.child,'fresh pool4 receives second empty queue head');}
    else {equal(pointer(x,x.nextChild,4),x.child,'captured original tail still receives child');equal(x.hitPool.tail,x.child,'fresh pool4 receives nonempty tail store');}
  }
  for(const mode of ['group-minus-one','type4','draw-minus-one','zero-descriptors','negative-descriptors'] as const) {
    const x=make();ready(x);
    if(mode==='group-minus-one') x.objectBytes[1]=255;
    else if(mode==='type4') x.objectBytes[2]=4;
    else if(mode==='draw-minus-one') x.objectBytes[0x85]=255;
    else x.objectBytes[0x99]=mode==='zero-descriptors'?0:128;
    const skipDescriptors=mode!=='draw-minus-one',skipDraw=mode==='group-minus-one'||mode==='type4'||mode==='draw-minus-one';
    if(skipDescriptors) {delete x.descriptorPool.releaseCallback18;delete x.objectBytes[0xe0];}
    if(mode==='group-minus-one'||mode==='type4') delete x.objectBytes[0x99];
    if(mode==='group-minus-one') {delete x.objectBytes[2];delete x.objectBytes[8];delete x.objectBytes[0x85];}
    if(skipDraw) {delete x.objectBytes[0x104];delete x.objectBytes[0x108];}
    const keep=retained(x.descriptorBytes,x.nextDescriptorBytes,x.descriptorPool),draw=retained(x.drawList);
    x.root.dispatchStoredRoot(x.child);
    if(skipDescriptors) keep();if(skipDraw) draw();
    equal(byte(x,0),0,'source skip branches still reach actual object queue return');released(x);
  }
  for(const raw of [1,16,32,64,128,254]) {
    const x=make();ready(x);x.objectBytes[0x85]=raw;const events:string[]=[];
    observe(()=>rejects(()=>x.root.dispatchStoredRoot(x.child),'draw'),(owner,key)=>{
      if(owner===x.objectBytes && Number(key)>=0x104 && Number(key)<0x10c) events.push(String(key));
      if(owner===x.descriptorPool && ['activeHead','freeHead','count','releaseCallback18'].includes(String(key))) throw Error('unsupported draw class must precede all descriptor source accesses');
    });
    equal(events.join(','),Array.from({length:8},(_,i)=>String(0x104+i)).join(','),'unsupported draw classification still loads both source links before refusal');
    equal(x.groups[9]!.head,null,'unsupported draw leaves prior group unlink');equal(x.drawList.head,x.child,'unsupported draw never invents list removal');closed(x);
  }
  for(const raw of [0,1,3,127,128,255]) {
    const x=make();ready(x);x.objectBytes[2]=raw;
    x.root.dispatchStoredRoot(x.child);equal(x.descriptorPool.count,2,'only exact raw type4 skips descriptor cleanup');released(x);
  }
  {
    const x=make();ready(x);let changed=false;
    observe(()=>x.root.dispatchStoredRoot(x.child),(owner,key)=>{
      if(owner===x.descriptorPool && key==='releaseCallback18') {changed=true;x.descriptorBytes[8]=255;}
    });
    check(changed,'descriptor callback metadata reached');equal(x.descriptorBytes[8],255,'post-capture type mutation remains');
    equal(x.descriptorPool.count,2,'197bec/197bd8 use captured descriptor row, not a fresh type8');released(x);
  }
  for(const raw of [1,127,128,255]) {
    const x=make();ready(x);x.descriptorBytes[8]=raw;
    const keep=retained(x.descriptorPool,x.descriptorBytes,x.nextDescriptorBytes,x.objectPool);
    rejects(()=>x.root.dispatchStoredRoot(x.child),`descriptor row${raw<<24>>24}`);keep();
    equal(x.drawList.head,null,'unbounded descriptor row refuses after real draw unlink');closed(x);
  }
  for(const raw of [128,255]) {
    const x=make();ready(x);x.objectBytes[3]=raw;
    rejects(()=>x.root.dispatchStoredRoot(x.child),`${raw<<24>>24}: own data property`);
    equal(x.descriptorPool.count,2,'signed unknown object-pool row is reached after genuine descriptor release');
    equal(x.objectPool.tail,x.nextChild,'unknown signed pool cannot default to pool3');equal(byte(x,0),1,'unknown pool refuses before final active clear');closed(x);
  }
  for(const absent of ['missing','undefined','inherited','accessor','wrong'] as const) {
    const x=make();ready(x);let invoked=false;delete x.rootSources.cleanupState3;
    if(absent==='undefined') Object.defineProperty(x.rootSources,'cleanupState3',{value:undefined});
    if(absent==='inherited') Object.setPrototypeOf(x.rootSources,{cleanupState3:CELL});
    if(absent==='accessor') Object.defineProperty(x.rootSources,'cleanupState3',{get(){invoked=true;return CELL;}});
    if(absent==='wrong') x.rootSources.cleanupState3=0;
    const keep=retained(x.objectBytes,x.groups[9]!,x.drawList,x.descriptorPool,x.descriptorBytes,x.objectPool);
    rejects(()=>x.root.dispatchStoredRoot(x.child),absent==='accessor'?'own data dispatch cell':absent==='wrong'?'authenticated dispatch target differs':'state3 dispatch');
    check(!invoked,'cleanup metadata accessor is never invoked');keep();closed(x);
  }
  for(const value of [-1,2**32,Number.NaN,Infinity,1.5,null,'2148009592',{},()=>CELL]) {
    const x=make();ready(x);Object.defineProperty(x.rootSources,'cleanupState3',{value});
    const keep=retained(x.objectBytes,x.groups[9]!,x.drawList,x.objectPool);
    rejects(()=>x.root.dispatchStoredRoot(x.child),'unsigned source integer');keep();closed(x);
  }
  for(const selected of [1,127,128,255]) {
    const x=make();x.objectBytes[0x18]=selected;
    Object.defineProperty(x.rootSources,'cleanupState3',{get(){throw Error('wrong selected state reads cleanup metadata');}});
    observe(()=>rejects(()=>x.root.dispatchStoredRoot(x.child),`state${selected<<24>>24} dispatch`),(owner,key)=>{
      if(owner===x.rootSources && key==='cleanupState3') throw Error('unselected cleanup metadata inspected');
    });closed(x);
  }
  {
    const x=make();ready(x);Object.defineProperty(x.rootSources,'cleanupState3',{writable:false});
    Object.defineProperty(x.descriptorPool,'releaseCallback18',{writable:false});
    x.root.dispatchStoredRoot(x.child);released(x);
  }
  {
    const x=make(),sources={...x.rootSources,drawList0:{head:null,tail:null}};
    Object.defineProperty(x.rootSources,'cleanupState3',{get(){throw Error('unselected cleanup cell');}});
    observe(()=>ready(x),(owner,key)=>{if(owner===x.rootSources && key==='cleanupState3') throw Error('unselected cleanup metadata inspected');});
    // Construct from an explicit own-data record, then replace only its optional
    // cell so constructor admission is independently tested without spreading it.
    Object.defineProperty(sources,'cleanupState3',{get(){throw Error('constructor invoked optional cell');}});
    observe(()=>{createSourceProjectileRootRuntime(sources);},(owner,key)=>{
      if(owner===sources && key==='cleanupState3') throw Error('constructor inspected optional cleanup cell');
    });
  }
  for(const mode of ['missing','undefined','inherited','accessor','zero','mismatch'] as const) {
    const x=make();ready(x);let getter=false;delete x.descriptorPool.releaseCallback18;
    if(mode==='undefined') Object.defineProperty(x.descriptorPool,'releaseCallback18',{value:undefined});
    if(mode==='inherited') Object.setPrototypeOf(x.descriptorPool,{releaseCallback18:CALLBACK});
    if(mode==='accessor') Object.defineProperty(x.descriptorPool,'releaseCallback18',{get(){getter=true;return CALLBACK;}});
    if(mode==='zero'||mode==='mismatch') x.descriptorPool.releaseCallback18=mode==='zero'?0:0x80006f60;
    const descriptors=retained(x.descriptorPool,x.descriptorBytes,x.nextDescriptorBytes),pool=retained(x.objectPool,x.nextObjectBytes);
    rejects(()=>x.root.dispatchStoredRoot(x.child),mode==='zero'||mode==='mismatch'?'80006ed8':'releaseCallback18');
    descriptors();pool();check(!getter,'callback accessor is never executed');equal(x.drawList.head,null,'real draw unlink precedes callback admission');
    equal(byte(x,0),1,'callback admission failure precedes object release');closed(x);
  }
  for(const atCallback of [false,true]) {
    const x=make();ready(x);const d=descriptor(x);let loads=0;
    const encoded:number[]=[];x.allocator.writePointer(d,0xc,x.actor);
    for(let i=0;i<4;i++) encoded.push(x.descriptorBytes[0xc+i]!);
    if(atCallback) x.allocator.writePointer(d,0xc,null);
    observe(()=>rejects(()=>x.root.dispatchStoredRoot(x.child),'8024fd74'),(owner,key)=>{
      if(owner===x.descriptorBytes && key==='12') loads++;
      if(atCallback && owner===x.descriptorPool && key==='releaseCallback18') encoded.forEach((v,i)=>{x.descriptorBytes[0xc+i]=v;});
    });
    equal(loads,atCallback?2:1,'actual06d80 and nonnull06ed8 independently load descriptor+c');
    equal(pointer(x,d,0xc),x.actor,'unsupported JObjUnref refuses before source+c clear');
    equal(x.descriptorPool.activeHead,d,'JObjUnref boundary precedes descriptor unlink');
    equal(x.descriptorBytes[9],1,'JObjUnref boundary preserves active flag');closed(x);
  }
  {
    const x=make();ready(x);x.objectBytes[0x99]=2;x.allocator.writePointer(x.child,0xe4,null);let reads=0;
    observe(()=>x.root.dispatchStoredRoot(x.child),(owner,key)=>{if(owner===x.objectBytes && key==='153') reads++;});
    equal(reads,3,'descriptor loop fresh signed count is loaded at each condition including exit');
    equal(x.descriptorPool.count,2,'null second descriptor is skipped without an injected release');released(x);
  }
  {
    const x=make();ready(x);let reads=0;
    observe(()=>x.root.dispatchStoredRoot(x.child),(owner,key)=>{
      if(owner===x.objectBytes && key==='153' && ++reads===2) x.objectBytes[0x99]=255;
    });
    equal(reads,2,'fresh negative descriptor count exits after genuine first release');released(x);
  }
  for(const [record,offset] of [['child',5],['child',11],['child',0x107],['child',0x10b],
    ['child',0xe3],['descriptor',0xf],['descriptor',8],['descriptor',3],['descriptor',7]] as const) {
    const x=make();ready(x);const raw=record==='child'?x.objectBytes:x.descriptorBytes;
    delete raw[offset];let invoked=false;
    if(offset===8) Object.defineProperty(raw,String(offset),{get(){invoked=true;return 0;},configurable:true});
    rejects(()=>x.root.dispatchStoredRoot(x.child),`${offset}: own data property`);
    check(!invoked,'reached byte accessor is rejected without invocation');
    equal(byte(x,0),1,'partial scalar read fault never returns child to pool');
    equal(x.objectPool.count,1,'source read fault retains object availability');
    equal(x.descriptorBytes[9],1,'descriptor link read fault precedes descriptor active clear');
    equal(x.groups[9]!.head,record==='child' && offset<12?x.child:null,'only completed group unlink survives read fault');
    equal(x.drawList.head,record==='child' && (offset<12||offset===0x107||offset===0x10b)?x.child:null,'only completed draw unlink survives later scalar read fault');closed(x);
  }
  for(const point of ['group-tail','draw-head','draw-callback','descriptor-active','descriptor-free','descriptor-flag','descriptor-count','pool-tail','pool-count','active','next'] as const) {
    const x=make();ready(x);const d=descriptor(x);
    const [owner,key]=point==='group-tail'?[x.groups[9]!,'tail']:point==='draw-head'?[x.drawList,'head']:
      point==='draw-callback'?[x.objectBytes,'257']:point==='descriptor-active'?[x.descriptorPool,'activeHead']:
      point==='descriptor-free'?[x.descriptorPool,'freeHead']:point==='descriptor-flag'?[x.descriptorBytes,'9']:
      point==='descriptor-count'?[x.descriptorPool,'count']:point==='pool-tail'?[x.objectPool,'tail']:
      point==='pool-count'?[x.objectPool,'count']:point==='active'?[x.objectBytes,'0']:[x.objectBytes,'5'];
    Object.defineProperty(owner,key,{writable:false});
    rejects(()=>x.root.dispatchStoredRoot(x.child),`${key}: non-writable`);
    equal(x.groups[9]!.head,null,'every tested late fault retains first group-head clear');
    if(point==='group-tail') {equal(x.groups[9]!.tail,x.child,'failed group-tail retains old value');equal(x.drawList.head,x.child,'draw unreached after group fault');}
    if(point==='draw-head') {equal(x.drawList.tail,null,'draw tail clear commits before failed head');equal(x.drawList.head,x.child,'failed draw-head remains');}
    if(point==='draw-callback') {equal(x.allocator.readU32(x.child,0x100),0x80047aa4,'word preflight is atomic');equal(byte(x,0x85),0,'draw classification remains until whole callback word clears');}
    if(point.startsWith('descriptor-')) {
      equal(x.drawList.head,null,'descriptor fault follows completed draw unlink');equal(byte(x,0),1,'descriptor fault precedes object queue');
      if(point==='descriptor-active') equal(x.descriptorPool.activeHead,d,'failed descriptor head store remains old');
      if(point==='descriptor-free') {equal(x.descriptorPool.activeHead,null,'active unlink precedes free head');equal(pointer(x,d,0),nextDescriptor(x),'descriptor next store precedes free-head store');}
      if(point==='descriptor-flag'||point==='descriptor-count') equal(x.descriptorPool.freeHead,d,'descriptor free insertion survives late fault');
      if(point==='descriptor-count') equal(x.descriptorBytes[9],0,'descriptor flag clear precedes count store');
    }
    if(point==='pool-tail'||point==='pool-count'||point==='active'||point==='next') {
      equal(x.descriptorPool.count,2,'whole descriptor release precedes object queue effects');
      equal(pointer(x,x.nextChild,4),x.child,'old free tail next store precedes later object faults');
    }
    if(point==='active'||point==='next') equal(x.objectPool.count,2,'count increment survives final child failures');
    equal(byte(x,0),point==='next'?0:1,'active-byte store occurs only before final next-word failure');
    equal(x.projectiles.getSpawnOwnerIdentity(x.child),x.actor,'failed cleanup never revokes completed-spawn claim');
    Object.defineProperty(owner,key,{writable:true});closed(x);
  }
  for(const reenter of ['root','allocator','spawn'] as const) {
    const x=make();ready(x);let attempted=false;
    observe(()=>rejects(()=>x.root.dispatchStoredRoot(x.child),'reentry'),(owner,key)=>{
      if(!attempted && owner===x.descriptorPool && key==='releaseCallback18') {
        attempted=true;
        try {
          if(reenter==='root') x.root.dispatchStoredRoot(x.child);
          else if(reenter==='allocator') x.allocator.readU8(x.child,0);
          else x.projectiles.spawn(x.actor,1);
        } catch {/* A caught inner refusal must still latch the outer failure. */}
      }
    });
    check(attempted,'same owner reentry reached actual descriptor callback metadata');
    equal(x.drawList.head,null,'caught reentry retains earlier source unlink');
    equal(x.descriptorBytes[9],reenter==='allocator'?1:0,'allocator preflight stops immediately; outer guards check after entered helper returns');
    equal(byte(x,0),reenter==='allocator'?1:0,'root/spawn caught reentry retains completed allocator release prefix');closed(x);
  }
  {
    const x=make();ready(x);const keep=retained(...allRecords(x));
    rejects(()=>x.projectiles.cleanupProjectile(x.child,x.root),'private active state3 cleanup invocation');keep();
    check(!hasIncompleteSourceActorDoubleLifecycle(x.sourceActor),'genuine idle root cannot authorize cleanup or poison owner');
    rejects(()=>x.allocator.releaseProjectile(x.actor,Symbol('not private caller'),x.child,x.drawList),'exclusive actor caller');keep();
    x.root.dispatchStoredRoot(x.child);released(x);
  }
  {
    const x=make();ready(x);x.frame.bindActor(x.actor);const keep=retained(...allRecords(x));
    rejects(()=>x.root.dispatchStoredRoot(x.child),'frame-owned actor');keep();
    check(!hasIncompleteSourceActorDoubleLifecycle(x.sourceActor),'scheduler refusal does not invent cleanup');
  }
  console.log('[projectile-cleanup-test] PASS: genuine third state3 callback unlinks canonical group/draw/descriptor records and returns original bytes to pool3; actual nonnull06ed8, ordered faults, lazy metadata, queue reuse with explicit new root entry, stale release refusal and shared permanent closure; synthetic offline pool inputs, no scheduler/retail hydration/browser completion claim');
}
