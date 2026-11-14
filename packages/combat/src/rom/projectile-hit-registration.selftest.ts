import {createSourceProjectileHitRuntime, isSourceProjectileHitRuntime,
  type SourceProjectileHitRuntime, type SourceProjectileHitOwnerBinding} from './projectile-hit-registration.js';
import {createDoubleProjectileHitExportSlice} from './projectile-hit-export-slice.js';
import {createSourceProjectileRootRuntime} from './projectile-root-lifecycle.js';
import {hasIncompleteSourceActorDoubleLifecycle} from './actor-double-prehook.js';
import type {SourceAllocationBytes, SourceDescriptorPool, SourceObjectPool} from './source-object-allocation.js';
import type {SourceProjectileRootTestFixture} from './projectile-root-lifecycle.selftest.js';

/** A caller supplies the completed genuine composition, not successful stand-in
 * callees. Synthetic host mutations below expose source reads and failure order.
 * Only the default eight-byte export slice is losslessly derived asset evidence;
 * extra rows, branch bytes and current free lists are explicit test inputs. */
export interface SourceProjectileHitTestFixture extends SourceProjectileRootTestFixture {
  hits: SourceProjectileHitRuntime;
  hitBinding: SourceProjectileHitOwnerBinding & {pointer27c: object; pointer3fc: SourceAllocationBytes};
  hitTableIdentity: symbol; damageIdentity: symbol;
  hitIds: symbol[]; hitBytes: SourceAllocationBytes[]; hitPool: SourceObjectPool;
  descriptorPool: SourceDescriptorPool; descriptorBytes: SourceAllocationBytes; nextDescriptorBytes: SourceAllocationBytes;
}
const NEXT = 'positive HIT continuation before actual8020b7a8 position refresh';
function check(ok: boolean, why: string): void {if (!ok) throw Error(`[projectile-hit-test] ${why}`);}
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
function retained(...records: object[]): () => void {
  const before = records.map(record => Object.getOwnPropertyDescriptors(record));
  return () => records.forEach((record,index) => {
    const after = Object.getOwnPropertyDescriptors(record), saved = before[index]!;
    equal(Reflect.ownKeys(after).length,Reflect.ownKeys(saved).length,'retained property count');
    for (const key of Object.keys(saved)) {
      const a = after[key], b = saved[key]!;
      check(a !== undefined && Object.is(a.value,b.value) && a.get === b.get && a.set === b.set &&
        a.writable === b.writable && a.configurable === b.configurable && a.enumerable === b.enumerable,
      `retained descriptor ${key}`);
    }
  });
}
function closed(x: SourceProjectileHitTestFixture): void {
  check(hasIncompleteSourceActorDoubleLifecycle(x.sourceActor),'failure closes the shared actual Double owner');
  const unchanged = retained(x.objectBytes,x.nextObjectBytes,x.hitPool,x.descriptorPool,...x.hitBytes);
  rejects(() => x.hits.registerHit(x.child,1),'incomplete');
  rejects(() => x.projectiles.spawn(x.actor,1),'incomplete');
  rejects(() => x.allocator.writeU8(x.nextChild,0,1),'incomplete');
  rejects(() => x.root.dispatchStoredRoot(x.child),'incomplete');
  unchanged();
}
function pointer(x: SourceProjectileHitTestFixture,id: symbol,offset: number): symbol | null {
  return x.allocator.readPointer(id,offset);
}
function alias(x: SourceProjectileHitTestFixture,id: symbol,offset: number,base: symbol,displacement: number): void {
  const p = pointer(x,id,offset); check(p !== null,'interior pointer exists');
  const address = x.allocator.getInteriorAddress(p!);
  check(address !== null && Object.isFrozen(address) && address.base === base && address.byteOffset === displacement,
    `actual symbolic base+${displacement.toString(16)} at ${offset.toString(16)}`);
  const target = x.allocator.getPointerTarget(p!) as {base: object; byteOffset: number};
  check(Object.isFrozen(target) && target.base === x.allocator.getPointerTarget(base) && target.byteOffset === displacement,
    'interior target retains actual base object without copying or reading it');
}
function syntheticRow(table: SourceAllocationBytes,index: number,damage = 0x1234,start = 0x8001,end = 0x7ffe): void {
  const row = 0xaa0+index*0x50;
  for (const [offset,value] of [[4,damage],[6,start],[8,end]] as const) {
    table[row+offset] = value >>> 8; table[row+offset+1] = value & 255;
  }
}
function rawPointer(x: SourceProjectileHitTestFixture,id: symbol | null): number[] {
  x.allocator.writePointer(x.nextChild,0x27c,id);
  return [0,1,2,3].map(i => x.nextObjectBytes[0x27c+i]!);
}
function replacePointer(bytes: SourceAllocationBytes,offset: number,encoded: number[]): void {
  encoded.forEach((value,i) => {bytes[offset+i] = value;});
}
function successfulHit(x: SourceProjectileHitTestFixture,index = 0): void {
  const id = x.hitIds[index]!, a = x.allocator;
  equal(a.getObject(id),x.hitBytes[index],'same canonical type4 object bytes');
  equal(a.readU8(id,0),1,'actual8008acfc active byte');
  equal(a.readU8(id,1),49,'actual group48 plus main-actor slot0+1');
  equal(a.readU8(id,2),4,'actual source type4'); equal(a.readU8(id,3),4,'actual source pool4');
  equal(a.readU8(id,0x83),26,'actual group classification26'); equal(a.readU8(id,0x85),255,'allocator draw class');
  equal(a.readU32(id,0xc),0x8008a65c,'future callback stored, never invoked');
  equal(pointer(x,id,0x20),x.child,'HIT points to original completed projectile');
  equal(pointer(x,id,0x24),x.actor,'actual reloaded parent90');
  equal(pointer(x,id,0x2c),x.damageIdentity,'child27c reload retains real opaque derived table');
  equal(pointer(x,id,0x5c),id,'source self5c store');
  alias(x,id,0x28,x.hitTableIdentity,0xaf0); alias(x,id,0x60,x.child,0x114);
  equal(a.readU8(id,0x14),1,'actual kind low byte'); equal(a.readU8(id,0x12),1,'final remap reload');
  equal(a.readU8(id,0x11),1,'lossless damage index'); equal(a.readU16(id,0x48),0,'lossless active start');
  equal(a.readS16(id,0x4a),-1,'lossless active end'); equal(a.readU16(id,0x4c),0,'nonzero83 leaves memset4c');
  equal(a.readU8(id,0x99),0,'type4 skips descriptor count store');
  for (let i=0;i<8;i++) equal(pointer(x,id,0xe0+i*4),null,'type4 retains cleared descriptor slots');
  equal(a.readU8(x.child,0x86),1,'actual child86 set'); equal(a.readU8(x.child,0x1d8),0,'actual child1d8 cleared');
}
export function runProjectileHitRegistrationSelfTests(make: () => SourceProjectileHitTestFixture): void {
  {
    const x = make(), projection = createDoubleProjectileHitExportSlice(), table = x.hitBinding.pointer3fc;
    check(isSourceProjectileHitRuntime(x.hits) && Object.isFrozen(x.hits),'genuine frozen HIT runtime');
    equal(x.hits.getSpawnRuntime(),x.projectiles,'same genuine spawn owner');
    equal(x.hits.getActorBinding(x.actor),x.hitBinding,'explicit binding retained, not copied');
    equal(x.hits.getActualActor(x.actor),x.sourceActor,'same actual actor');
    equal(projection.pointer27c,x.hitBinding.pointer27c,'actual derived damage object retained between projections');
    check(projection.pointer3fc !== table,'each explicit sparse byte owner is distinct');
    equal(Object.keys(table).join(','),[0xa24,0xa25,0xaf4,0xaf5,0xaf6,0xaf7,0xaf8,0xaf9].join(','),'only eight lossless integer bytes supplied');
    equal(Object.values(table).join(','),'1,255,0,1,0,0,255,255','exact selected remap and integer row projection');
    equal(x.allocator.readU8(x.child,0x83),16,'untouched actual completed child83 is nonzero');
    const noDescriptors = retained(x.descriptorPool,x.descriptorBytes,x.nextDescriptorBytes), reads: number[] = [];
    observe(() => equal(x.hits.registerHit(x.child,1),1,'direct real registration returns success'),(owner,key) => {
      if (owner === table) reads.push(Number(key));
      if (owner === x.objectBytes && Number(key)>=0x114 && Number(key)<0x144)
        throw Error('registration must not dereference a child matrix');
    });
    equal(reads.join(','),[0xa24,0xa24,0xaf4,0xaf5,0xaf6,0xaf7,0xaf8,0xaf9,0xa24,0xa25].join(','),
      'condition, fresh row index, halfwords, final remap and next condition source schedule');
    successfulHit(x); noDescriptors();
    equal(Object.keys(x.hitBytes[0]!).length,0x1c0,'actual type4 extent448');
    equal(x.hitPool.count,3,'one real pool4 pop'); equal(x.hitPool.head,x.hitIds[1],'real next free object');
    equal(x.groups[49]!.head,x.hitIds[0],'real group49 head'); equal(x.groups[49]!.tail,x.hitIds[0],'real group49 tail');
    equal(pointer(x,x.hitIds[0]!,4),null,'first group previous link'); equal(pointer(x,x.hitIds[0]!,8),null,'first group next link');
    equal(pointer(x,x.child,0x27c),x.damageIdentity,'original owner27c copied to child');
    check(!hasIncompleteSourceActorDoubleLifecycle(x.sourceActor),'completed direct call is not a failed frame');
  }
  {
    const x=make(),raw=x.hitBytes[0]!,table=x.hitBinding.pointer3fc,events:string[]=[];let body=false;
    observe(()=>equal(x.hits.registerHit(x.child,1),1,'ordered positive body'),(owner,key)=>{
      if(!body && owner===raw && key==='0' && x.groups[49]!.head===x.hitIds[0] && raw[0x83]===26) body=true;
      if(!body) return;
      if(owner===raw) events.push(`h${Number(key).toString(16)}`);
      if(owner===x.objectBytes) events.push(`c${Number(key).toString(16)}`);
      if(owner===table) events.push(`t${Number(key).toString(16)}`);
    });
    const word=(prefix:string,offset:number,width=4):string[]=>Array.from({length:width},(_,i)=>`${prefix}${(offset+i).toString(16)}`);
    equal(events.join(','),[
      'h0',...word('h',0xc),...word('h',0x20),'h14',...word('c',0x90),...word('h',0x24),
      'ta24',...word('h',0x28),'c83',...word('h',0x60),...word('h',0x5c),...word('c',0x27c),...word('h',0x2c),
      'taf4','taf5','h11','taf6','taf7',...word('h',0x48,2),'taf8','taf9',...word('h',0x4a,2),
      'c86','c1d8','ta24','h12','ta25',
    ].join(','),'all reached source body loads and scalar-store preflights preserve the independent PPC schedule');
  }
  {
    const x = make(), a = x.allocator, before = [0x20,0x24,0x28].map(o => a.readU32(x.child,o));
    x.sourceActor.heading = 0x8123;
    rejects(() => x.root.dispatchStoredRoot(x.child),NEXT); successfulHit(x);
    equal(a.readU8(x.child,0x18),1,'positive root remains actual state1');
    equal(a.readU32(x.child,0x100),0x80047aa4,'prior genuine draw callback stored');
    equal(x.drawList.head,x.child,'prior genuine89100 draw registration'); equal(x.drawList.tail,x.child,'actual draw tail');
    equal(a.readU8(x.child,0x84),20,'prior category store'); equal(a.readU16(x.child,0x72),0x8123,'prior owner yaw copy');
    check(before.every((v,i) => a.readU32(x.child,[0x20,0x24,0x28][i]!)===v),'positive boundary precedes8020b7a8 position refresh');
    closed(x);
  }
  for (const mode of ['parent-null','negative-remap','empty-pool','negative-descriptors'] as const) {
    const x = make(), table = x.hitBinding.pointer3fc;
    const bytesBefore = retained(...x.hitBytes), descriptorBefore = retained(x.descriptorBytes,x.nextDescriptorBytes);
    if (mode === 'parent-null') {
      x.allocator.writePointer(x.child,0x90,null);
      delete (x.hitBinding as Partial<SourceProjectileHitOwnerBinding>).pointer27c;
      delete (x.hitBinding as Partial<SourceProjectileHitOwnerBinding>).pointer3fc;
    } else if (mode === 'negative-remap') table[0xa24] = 0x80;
    else if (mode === 'empty-pool') {x.hitPool.head=null;x.hitPool.tail=null;x.hitPool.count=Number.NaN;}
    else x.descriptorPool.count = 0xffff;
    const reads: number[] = [];
    observe(() => equal(x.hits.registerHit(x.child,1),0,`genuine ${mode} zero return`),(owner,key) => {
      if (owner === table) reads.push(Number(key));
      if (mode === 'negative-descriptors' && owner === x.hitPool) throw Error('negative signed descriptor count must precede pool4');
    });
    equal(reads.join(','),mode==='parent-null'?'':mode==='negative-remap'?String(0xa24):[0xa24,0xa25].join(','),
      'zero branches read only reached condition bytes, never rows');
    bytesBefore(); descriptorBefore(); equal(x.groups[49]!.head,null,'zero path inserts no group node');
    check(!hasIncompleteSourceActorDoubleLifecycle(x.sourceActor),'actual zero return remains complete');
    if (mode !== 'parent-null') equal(pointer(x,x.child,0x27c),x.damageIdentity,'zero branch still preserves preceding owner27c copy');
  }
  for (const mode of ['negative-remap','empty-pool','negative-descriptors'] as const) {
    const x = make();
    if (mode==='negative-remap') x.hitBinding.pointer3fc[0xa24]=255;
    else if (mode==='empty-pool') x.hitPool.head=null;
    else x.descriptorPool.count=0x8000;
    x.root.dispatchStoredRoot(x.child);
    equal(x.allocator.readU8(x.child,0x18),2,'actual7de10/14 zero-result retirement returns normally');
    equal(x.drawList.head,x.child,'zero result follows genuine draw registration');
    equal(x.hitPool.count,4,'zero result consumes no HIT object');
    check(!hasIncompleteSourceActorDoubleLifecycle(x.sourceActor),'root zero epilogue is a completed invocation');
    rejects(() => x.root.dispatchStoredRoot(x.child),'state2 dispatch'); closed(x);
  }
  {
    const x = make(); x.descriptorPool.count=0;
    delete x.descriptorPool.freeHead; delete x.descriptorPool.activeHead; delete x.descriptorPool.initCallback14;
    const descriptors = retained(x.descriptorPool,x.descriptorBytes,x.nextDescriptorBytes);
    equal(x.hits.registerHit(x.child,1),1,'requested descriptor count0 succeeds with actual availability0');
    descriptors(); successfulHit(x);
  }
  for (const fifth of [0,127,128,255]) {
    const x=make(), table=x.hitBinding.pointer3fc;
    for(let i=0;i<4;i++) table[0xa24+i]=1; table[0xa28]=fifth;
    const reads:number[]=[];
    observe(()=>equal(x.hits.registerHit(x.child,1),1,'four real source attempts return success'),(owner,key)=>{
      if(owner===table && Number(key)>=0xa24 && Number(key)<=0xa28) reads.push(Number(key));
    });
    equal(reads.join(','),[0xa24,0xa24,0xa24,0xa25,0xa25,0xa25,0xa26,0xa26,0xa26,0xa27,0xa27,0xa27,0xa28].join(','),
      'fifth remap load/sign test occurs before count4 cap even when nonnegative');
    equal(x.hitPool.count,0,'exactly four pool objects consumed'); equal(x.hitPool.head,null,'fourth object exhausts head');
    equal(x.hitPool.tail,null,'fourth object exhausts tail'); equal(x.groups[49]!.head,x.hitIds[3],'latest group node');
    equal(x.groups[49]!.tail,x.hitIds[0],'oldest group node retained');
    for(let i=0;i<4;i++) {
      successfulHit(x,i); equal(pointer(x,x.hitIds[i]!,4),x.hitIds[i+1]??null,'actual previous4 linkage');
      equal(pointer(x,x.hitIds[i]!,8),x.hitIds[i-1]??null,'actual next8 linkage');
    }
  }
  {
    const x=make(),table=x.hitBinding.pointer3fc;
    for(let i=0;i<4;i++) table[0xa24+i]=1;
    rejects(()=>x.hits.registerHit(x.child,1),`${0xa28}: own data property`);
    equal(x.hitPool.count,0,'missing fifth condition faults after all four effects');
    equal(x.allocator.readU8(x.hitIds[3]!,0x12),1,'fourth final store survives later fifth-read failure'); closed(x);
  }
  {
    const x=make(),table=x.hitBinding.pointer3fc; x.hitPool.head=null;
    for(let i=0;i<=4;i++) table[0xa24+i]=1;
    const reads:number[]=[];
    observe(()=>equal(x.hits.registerHit(x.child,1),0,'four null allocations preserve result0'),(owner,key)=>{
      if(owner===table) reads.push(Number(key));
    });
    equal(reads.join(','),[0xa24,0xa25,0xa26,0xa27,0xa28].join(','),'failed attempts advance cursor and count without row/final reads');
  }
  for(const kind of [-1,0,0x101]) {
    const x=make(),cursor=0xa20+kind*4; x.hitBinding.pointer3fc[cursor]=1;x.hitBinding.pointer3fc[cursor+1]=255;
    equal(x.hits.registerHit(x.child,kind),1,'full signed kind selects its source remap');
    equal(x.allocator.readU8(x.hitIds[0]!,0x14),kind&255,'kind14 store truncates only at actual byte store');
  }
  {
    const x=make(),table=x.hitBinding.pointer3fc,foreign:SourceAllocationBytes={};
    const foreignId=Symbol('test replacement table');x.allocator.registerExternal(foreignId,foreign);
    let reads=0;
    observe(()=>equal(x.hits.registerHit(x.child,1),1,'captured3fc retained across caller replacement'),(owner,key)=>{
      if(owner===table && key===String(0xa24) && ++reads===1) x.hitBinding.pointer3fc=foreign;
      if(owner===foreign) throw Error('must not reread replacement owner3fc table');
    });
    alias(x,x.hitIds[0]!,0x28,x.hitTableIdentity,0xaf0);
    equal(reads,3,'saved cursor still supports all three reads of the original entry');
  }
  {
    const x=make(),table=x.hitBinding.pointer3fc; syntheticRow(table,2);
    let reads=0;
    observe(()=>equal(x.hits.registerHit(x.child,1),1,'fresh signed row and final remap loads'),(owner,key)=>{
      if(owner===table && key===String(0xa24)) {
        reads++; if(reads===2) {equal(x.hitPool.count,3,'row load follows actual allocation');table[0xa24]=2;}
        if(reads===3) table[0xa24]=0xfe;
      }
    });
    const hit=x.hitIds[0]!; alias(x,hit,0x28,x.hitTableIdentity,0xb40);
    equal(x.allocator.readU8(hit,0x11),0x34,'row04 reads full16 then stores low8');
    equal(x.allocator.readS16(hit,0x48),-32767,'row06 signed halfword bit pattern');
    equal(x.allocator.readS16(hit,0x4a),32766,'row08 signed halfword bit pattern');
    equal(x.allocator.readU8(hit,0x12),0xfe,'final remap reload is an unsigned byte, not cached row index');
  }
  {
    const x=make(),table=x.hitBinding.pointer3fc; syntheticRow(table,-1,0x1234,0xffff,0x8000);
    let reads=0;
    observe(()=>equal(x.hits.registerHit(x.child,1),1,'post-allocation negative row index is sign-extended without rechecking condition'),(owner,key)=>{
      if(owner===table && key===String(0xa24) && ++reads===2) table[0xa24]=255;
    });
    alias(x,x.hitIds[0]!,0x28,x.hitTableIdentity,0xa50);
    equal(x.allocator.readU16(x.hitIds[0]!,0x4a),0x8000,'signed negative end bits retained');
  }
  for(const nullParent of [false,true]) {
    const x=make(),table=x.hitBinding.pointer3fc,replacement=rawPointer(x,nullParent?null:x.nextChild);
    const fallback=rawPointer(x,x.hitIds[3]!);replacePointer(x.objectBytes,0x8c,fallback);
    let changed=false;
    observe(()=>equal(x.hits.registerHit(x.child,1),1,'allocator retains original main actor but hit24 reloads child90'),(owner,key)=>{
      if(!changed && owner===table && key===String(0xa24)) {
        changed=true;replacePointer(x.objectBytes,0x90,replacement);
      }
    });
    equal(pointer(x,x.hitIds[0]!,0x24),nullParent?x.hitIds[3]:x.nextChild,'90 changed after saved allocation owner; null alone reaches8c fallback');
    equal(x.groups[49]!.head,x.hitIds[0],'saved source owner still supplies actual allocation group');
  }
  {
    const x=make(),replacement=rawPointer(x,x.hitIds[3]!);let changed=false;
    observe(()=>equal(x.hits.registerHit(x.child,1),1,'child27c freshly reloaded at actual8adac'),(owner,key)=>{
      if(!changed && owner===x.objectBytes && key===String(0x83)) {changed=true;replacePointer(x.objectBytes,0x27c,replacement);}
    });
    equal(pointer(x,x.hitIds[0]!,0x2c),x.hitIds[3],'hit2c uses changed child27c, not cached original damage owner');
  }
  for(const nonzero of [1,16,127,128,255]) {
    const x=make();x.objectBytes[0x83]=nonzero;
    for(let i=0x114;i<0x144;i++) delete x.objectBytes[i];
    equal(x.hits.registerHit(x.child,1),1,'every signed nonzero83 branch only aliases child114');
    alias(x,x.hitIds[0]!,0x60,x.child,0x114);
    check(!Object.hasOwn(x.hitBinding.pointer3fc,String(0xaf1)) && !Object.hasOwn(x.objectBytes,String(0x1cec)),
      'nonzero83 never requires missing bone/group/action byte backing');
  }
  for(const [bone,group,action] of [[0,0,0],[1,1,127],[127,0x80,0x80],[128,0xff,0xff],[255,0x7f,0x80]]) {
    const x=make();x.objectBytes[0x83]=0;x.objectBytes[0x1cec]=group!;x.objectBytes[0x1ced]=action!;
    x.hitBinding.pointer3fc[0xaf1]=bone!; const reads:number[]=[];
    observe(()=>equal(x.hits.registerHit(x.child,1),1,'explicit synthetic zero83 backing enters source bone path'),(owner,key)=>{
      if(owner===x.objectBytes && [0x1cec,0x1ced].includes(Number(key))) reads.push(Number(key));
    });
    alias(x,x.hitIds[0]!,0x60,x.child,bone!&0x80?0x1aa4:0x8d4+bone!*0x30);
    equal(reads.join(','),[0x1cec,0x1ced].join(','),'actual group byte is loaded before action byte');
    equal(x.allocator.readU16(x.hitIds[0]!,0x4c),(((group!<<24>>24)*0x1000)+(action!<<24>>24))&65535,
      'signed byte sum stored modulo16, no inferred matrix or animation defaults');
  }
  for(const missing of [0xaf4,0xaf5,0xaf6,0xaf7,0xaf8,0xaf9,0xa25]) {
    const x=make();delete x.hitBinding.pointer3fc[missing];
    rejects(()=>x.hits.registerHit(x.child,1),`${missing}: own data property`);
    equal(x.hitPool.count,3,'late table fault preserves genuine allocation');
    equal(pointer(x,x.hitIds[0]!,0x5c),x.hitIds[0],'late table fault preserves earlier self store');
    if(missing===0xaf5) equal(x.allocator.readU8(x.hitIds[0]!,0x11),0,'row04 high byte alone does not partially write byte11');
    if(missing===0xaf7) equal(x.allocator.readU16(x.hitIds[0]!,0x48),0,'row06 full load precedes48 store');
    if(missing===0xaf9) equal(x.allocator.readU16(x.hitIds[0]!,0x4a),0,'row08 full load precedes4a store');
    closed(x);
  }
  for(const [offset,width] of [[0xc,4],[0x20,4],[0x24,4],[0x28,4],[0x60,4],[0x5c,4],[0x2c,4],[0x48,2],[0x4a,2]] as const) {
    const x=make(),raw=x.hitBytes[0]!;let armed=false;
    observe(()=>rejects(()=>x.hits.registerHit(x.child,1),'non-writable'),(owner,key)=>{
      // The first remap reread starts after allocation/memset, but early stores
      // need arming before allocator returns. Its final type load is after all
      // group links and before any HIT body store.
      if(!armed && owner===raw && key==='2' && x.groups[49]!.head===x.hitIds[0] && raw[0x83]===26) {
        armed=true;Object.defineProperty(raw,String(offset+width-1),{writable:false});
      }
    });
    check(armed,'fault installed after real allocation cleared the canonical bytes');
    equal(x.hitPool.count,3,'post-allocation store failure preserves pop');
    check(Array.from({length:width},(_,i)=>raw[offset+i]===0).every(Boolean),'one failed scalar/pointer store preserves every destination byte');
    equal(raw[0],1,'earlier active-byte store survives'); closed(x);
  }
  {
    const x=make(),raw=x.hitBytes[0]!;x.objectBytes[0x83]=0;x.objectBytes[0x1cec]=1;x.objectBytes[0x1ced]=2;
    x.hitBinding.pointer3fc[0xaf1]=0x80;let armed=false;
    observe(()=>rejects(()=>x.hits.registerHit(x.child,1),'non-writable'),(owner,key)=>{
      if(!armed && owner===raw && key==='2' && x.groups[49]!.head===x.hitIds[0] && raw[0x83]===26) {
        armed=true;Object.defineProperty(raw,String(0x4d),{writable:false});
      }
    });
    check(armed,'zero83 halfword fault installed after memset');
    equal(x.allocator.readU16(x.hitIds[0]!,0x4c),0,'failed4c store does not commit its high byte');
    alias(x,x.hitIds[0]!,0x60,x.child,0x1aa4);
    equal(pointer(x,x.hitIds[0]!,0x5c),null,'4c failure precedes self5c');closed(x);
  }
  {
    const x=make();Object.defineProperty(x.objectBytes,String(0x27f),{writable:false});
    const old=[0,1,2,3].map(i=>x.objectBytes[0x27c+i]);
    rejects(()=>x.hits.registerHit(x.child,1),'non-writable');
    check(old.every((v,i)=>x.objectBytes[0x27c+i]===v),'owner27c pointer store is full-width atomic');
    equal(x.hitPool.count,4,'owner27c store precedes table capture and allocation');closed(x);
  }
  for(const offset of [0x86,0x1d8]) {
    const x=make();x.objectBytes[0x1d8]=7;Object.defineProperty(x.objectBytes,String(offset),{writable:false});
    rejects(()=>x.hits.registerHit(x.child,1),'non-writable');
    equal(x.allocator.readU16(x.hitIds[0]!,0x4a),0xffff,'row writes precede child flag stores');
    equal(x.allocator.readU8(x.hitIds[0]!,0x12),0,'final remap/store not reached after child flag fault');
    equal(x.objectBytes[0x86],offset===0x86?0:1,'86 store precedes1d8'); equal(x.objectBytes[0x1d8],7,'failed flag store retained');closed(x);
  }
  for(const bad of [-1,256,NaN,1.5]) {
    const x=make();x.hitBinding.pointer3fc[0xa24]=bad;
    rejects(()=>x.hits.registerHit(x.child,1),'source integer');equal(x.hitPool.count,4,'invalid remap never allocates');closed(x);
  }
  for(const bad of [-0x80000001,0x80000000,NaN,1.5]) {
    const x=make();rejects(()=>x.hits.registerHit(x.child,bad),'kind register');equal(x.hitPool.count,4,'invalid kind never allocates');closed(x);
  }
  for(const key of ['pointer27c','pointer3fc'] as const) {
    const x=make();let ran=false;
    Object.defineProperty(x.hitBinding,key,{get(){ran=true;throw Error('getter must not run');}});
    rejects(()=>x.hits.registerHit(x.child,1),`${key}: own data property`);
    check(!ran,'HIT pointer accessors are refused without invocation');equal(x.hitPool.count,4,'pointer admission precedes allocation');closed(x);
  }
  for(const offset of [0x90,0x91,0x92,0x93]) {
    const x=make();delete x.objectBytes[offset];const before=retained(...x.hitBytes);
    rejects(()=>x.hits.registerHit(x.child,1),`${offset}: own data property`);
    equal(x.hitPool.count,4,'initial parent pointer requires every source byte before allocation');before();closed(x);
  }
  {
    const x=make();x.allocator.writePointer(x.child,0x90,x.nextChild);
    rejects(()=>x.hits.registerHit(x.child,1),'outside genuine original main-actor domain');
    equal(x.hitPool.count,4,'registered nonparent cannot replace the genuine saved owner');closed(x);
  }
  {
    const x=make();x.hitBinding.pointer27c={};
    rejects(()=>x.hits.registerHit(x.child,1),'actual pointer owner has not been registered');
    equal(x.hitPool.count,4,'unregistered actual damage owner is not copied or assigned a guessed identity');closed(x);
  }
  {
    const x=make();let ran=false;
    Object.defineProperty(x.hitBinding.pointer3fc,String(0xaf5),{get(){ran=true;return 1;}});
    rejects(()=>x.hits.registerHit(x.child,1),`${0xaf5}: own data property`);
    check(!ran,'reached row accessor never executes');
    equal(x.allocator.readU8(x.hitIds[0]!,0x11),0,'full row04 load precedes byte11 store');closed(x);
  }
  {
    const x=make();(x.hitBinding as SourceProjectileHitOwnerBinding).pointer3fc=null;
    rejects(()=>x.hits.registerHit(x.child,1),'null source3fc');equal(pointer(x,x.child,0x27c),x.damageIdentity,'copy27c precedes null3fc dereference');closed(x);
  }
  {
    const x=make();(x.hitBinding as SourceProjectileHitOwnerBinding).pointer27c=null;
    equal(x.hits.registerHit(x.child,1),1,'explicit null damage pointer is copied without reading a damage body');
    equal(pointer(x,x.hitIds[0]!,0x2c),null,'null child27c copied to hit2c');
  }
  for(const offset of [0x1cec,0x1ced]) {
    const x=make();x.objectBytes[0x83]=0;x.hitBinding.pointer3fc[0xaf1]=0x80;x.objectBytes[0x1cec]=1;
    x.objectBytes[0x1ced]=2;delete x.objectBytes[offset];
    rejects(()=>x.hits.registerHit(x.child,1),`${offset}: own data property`);
    alias(x,x.hitIds[0]!,0x60,x.child,0x1aa4);equal(pointer(x,x.hitIds[0]!,0x5c),null,'missing explicit zero83 byte stops before self5c');closed(x);
  }
  {
    const x=make();let attempted=false;
    observe(()=>rejects(()=>x.hits.registerHit(x.child,1),'reentry'),(owner,key)=>{
      if(!attempted && owner===x.hitBinding.pointer3fc && key===String(0xa24)) {
        attempted=true;rejects(()=>x.hits.registerHit(x.child,1),'reentry');
      }
    });
    check(attempted,'same-runtime caught reentry reached actual condition read');
    equal(x.hitPool.count,4,'poisoned call stops before allocation despite inner exception being caught');closed(x);
  }
  {
    const x=make();
    for(const fake of [{...x.hits},Object.create(x.hits),{},null,()=>x.hits]) check(!isSourceProjectileHitRuntime(fake),'copied methods/prototype cannot forge HIT brand');
    rejects(()=>createSourceProjectileHitRuntime({...x.projectiles}),'genuine spawn runtime');
    rejects(()=>x.hits.bindActor(x.actor,{}),'new HIT owner identity');
    rejects(()=>x.hits.registerHit(x.nextChild,1),'no completed genuine spawn');
    const counterfeit=Symbol('registered bytes but no completed spawn');x.allocator.registerObject(counterfeit,{...x.objectBytes});
    rejects(()=>x.hits.registerHit(counterfeit,1),'no completed genuine spawn');
    rejects(()=>createSourceProjectileHitRuntime(x.projectiles).bindActor(x.actor,x.hitBinding),'already claimed');
    rejects(()=>createSourceProjectileHitRuntime(x.projectiles).bindActor(x.actor,{...x.hitBinding}),'actual actor already claimed');
    for(const fake of [{...x.hits},Object.create(x.hits)])
      rejects(()=>createSourceProjectileRootRuntime({...x.rootSources,drawList0:{head:null,tail:null},hits:fake}),'genuine HIT runtime');
    check(!hasIncompleteSourceActorDoubleLifecycle(x.sourceActor),'rejected counterfeit identities never execute source calls');
  }
  for(const bad of [null,[],new Uint8Array(2),Promise.resolve({})]) {
    const x=make();rejects(()=>createSourceProjectileHitRuntime(x.projectiles).bindActor(x.actor,bad as unknown as SourceProjectileHitOwnerBinding),'synchronous HIT');
  }
  {
    const x=make();
    for(const source of x.projectiles.getSourceOwners(x.actor))
      rejects(()=>createSourceProjectileHitRuntime(x.projectiles).bindActor(x.actor,source as SourceProjectileHitOwnerBinding),'aliases source owner');
    rejects(()=>createSourceProjectileHitRuntime(x.projectiles).bindActor(x.actor,{pointer27c:null,pointer3fc:null,damageTable27c:{}} as SourceProjectileHitOwnerBinding),'not missing HIT');
  }
  for(const key of ['pointer27c','pointer3fc','damageTable27c','hitTable3fc']) {
    const x=make();Object.defineProperty(x.sourceActor,key,{value:null,configurable:true});
    rejects(()=>x.hits.registerHit(x.child,1),'competing source pointer storage');
    equal(x.hitPool.count,4,'shadow alias refused before source execution');closed(x);
  }
  {
    const x=make(),y=make();
    rejects(()=>createSourceProjectileRootRuntime({...x.rootSources,drawList0:{head:null,tail:null},hits:y.hits}),'same completed-spawn owner');
    x.frame.bindActor(x.actor);const before=retained(x.objectBytes,x.hitPool,...x.hitBytes);
    rejects(()=>x.hits.registerHit(x.child,1),'frame-owned actor');
    rejects(()=>x.root.dispatchStoredRoot(x.child),'frame-owned actor');before();
    check(!hasIncompleteSourceActorDoubleLifecycle(x.sourceActor),'unsupported scheduler admission is not a partial frame');
  }
  console.log('[projectile-hit-test] PASS: genuine pool4/type4/group49 HIT registration, exact integer export slice, source reload/loop/width schedule, true zero branches, interior aliases and permanent partial-failure closure; positive root stops before8020b7a8; no retail hydration, matrix evaluation, flight, scheduler or original-runtime claim');
}
