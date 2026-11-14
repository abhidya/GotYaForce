import {createActorTargetCandidatesTestFixture} from './actor-target-candidates.selftest.js';
import {createSourceBattleOuterFrameRuntime,type SourceBattleOuterFrameSources} from './battle-outer-frame.js';
import {hasIncompleteSourceActorDoubleLifecycle,isSourceActorDoubleFrameClaimed} from './actor-double-prehook.js';
import type {createBattleTargetPreparationTestFixture} from './attached-setup-animation.selftest.js';

/** Explicit offline branch/byte inputs on the real allocator and complete HIT
 * registration. No substituted callees, selector results, or copied flag table.
 * The actual registered HIT descriptor is an interior pointer into its retained
 * external byte owner. Success here is one helper return, never a whole frame. */
type Make=typeof createBattleTargetPreparationTestFixture;
type Bytes=Partial<Record<number,number>>;
type Vector={x:number;y:number;z:number};
const axes=['x','y','z'] as const;
function check(ok:boolean,why:string):void {if(!ok) throw Error(`[actor-target-storage-test] ${why}`);}
function equal(actual:unknown,expected:unknown,why:string):void {
  check(Object.is(actual,expected),`${why}: got ${String(actual)}, expected ${String(expected)}`);
}
function rejects(run:()=>unknown,fragment:string):string {
  let message='';try {run();} catch(error) {message=String(error);}
  check(message.includes(fragment),`expected ${fragment}, got ${message||'success'}`);return message;
}
function observe(run:()=>void,before:(owner:object,key:PropertyKey)=>void,after?:(owner:object,key:PropertyKey)=>void):void {
  const original=Object.getOwnPropertyDescriptor;
  Object.getOwnPropertyDescriptor=((owner:object,key:PropertyKey)=>{
    before(owner,key);const result=original(owner,key);after?.(owner,key);return result;
  }) as typeof original;
  try {run();} finally {Object.getOwnPropertyDescriptor=original;}
}
function float(bytes:Bytes,offset:number,value:number):void {
  const v=new DataView(new ArrayBuffer(4));v.setFloat32(0,value,false);
  for(let i=0;i<4;i++) bytes[offset+i]=v.getUint8(i);
}
function position(bytes:Bytes,x:number,y=0,z=0):void {float(bytes,0x64,x);float(bytes,0x68,y);float(bytes,0x6c,z);}
function half(bytes:Bytes,offset:number,value:number):void {bytes[offset]=value>>>8;bytes[offset+1]=value&255;}
function setup(make:Make,count=1,flags=0x200) {
  const x=createActorTargetCandidatesTestFixture(make,count),stack:Vector={x:91,y:92,z:93},vector:Vector={x:71,y:72,z:73};
  x.sources.projectionStack=stack;Reflect.set(x.rootSources,'processor',x.actionSources.processor);x.scalarDescriptor.byte10=1;
  const matrix=x.matrices.getMatrix(x.world.getStorage(x.actor).matrices8d4[1]!);
  matrix[3]=0;matrix[7]=0;matrix[11]=0;
  // Reuse a real registration result, including the interned aa0+remap*50
  // pointer. Only the current candidate actor and vector are synthetic inputs.
  equal(x.hits.registerHit(x.child,1),1,'genuine HIT registration returns one');
  const id=x.hitIds[0]!,bytes=x.hitBytes[0]!,descriptor=x.allocator.readPointer(id,0x28)!;
  const address=x.allocator.getInteriorAddress(descriptor)!;
  equal(address.base,x.hitTableIdentity,'real descriptor retains registered external HIT table');
  equal(address.byteOffset,0xaf0,'genuine remap1 yields aa0+1*50');
  const table=x.hitBinding.pointer3fc;
  equal(x.allocator.getPointerTarget(address.base),table,'descriptor flags use original byte owner');
  half(table,address.byteOffset+2,flags);x.allocator.writePointer(id,0x20,x.target);position(bytes,5,6,7);
  x.list[0]=id;for(let i=0;i<count;i++) x.scratch[i]=null;Reflect.set(x.sourceActor,'lockTarget',vector);
  return Object.assign(x,{stack,vector,matrix,id,bytes,descriptor,table,row:address.byteOffset});
}
type Fixture=ReturnType<typeof setup>;
function extra(x:Fixture,value:number,flags=0,actor:symbol|null=x.target) {
  const id=Symbol('explicit later target OBJECT'),bytes:Bytes={};
  for(let offset=0;offset<0x70;offset++) bytes[offset]=0;
  x.allocator.registerObject(id,bytes);x.allocator.writePointer(id,0x20,actor);position(bytes,value);
  const row=0xc00+Object.keys(x.table).length*0x10;
  half(x.table,row+2,flags);const descriptor=x.allocator.getInteriorPointer(x.hitTableIdentity,row);
  x.allocator.writePointer(id,0x28,descriptor);
  return {id,bytes,row,descriptor};
}
function suffix(x:Fixture,visit:(owner:object,key:PropertyKey)=>void) {
  let projected=false,reached=false;
  return (owner:object,key:PropertyKey):void=>{
    if(!projected) {if(owner===x.stack&&key==='z') projected=true;return;}
    if(owner===x.globals&&key==='count804361a0') reached=true;
    if(reached) visit(owner,key);
  };
}
function closed(x:Fixture):void {
  check(hasIncompleteSourceActorDoubleLifecycle(x.sourceActor),'reached fault permanently closes actual caller');
  rejects(()=>x.targetDispatch.dispatchActor(x.actor),'incomplete');rejects(()=>x.allocator.assertActorComplete(x.actor),'incomplete');
}
function stored(x:Fixture,bytes:Bytes=x.bytes,actor:object|null=x.targetActor,values:readonly number[]=[5,6,7]):void {
  equal(x.sourceActor.byte502,1,'actual canonical state502 set');
  equal(x.admissionState.pointer504,bytes,'canonical504 retains exact original OBJECT byte object, not its symbol');
  equal(x.admissionState.pointer508,actor,'canonical508 retains freshly resolved actual identity, not its symbol');
  axes.forEach((key,i)=>equal(x.vector[key],values[i],`canonical target ${key}`));
}
function outer(x:Fixture) {
  const sources:SourceBattleOuterFrameSources={scheduler:x.scheduler,systemGlobals:x.systemGlobals,
    massPreparation:x.massPreparation,targetPreparation:x.targetPreparation};
  return createSourceBattleOuterFrameRuntime(sources);
}

function basicAndFlags(make:Make):void {
  {
    const x=setup(make),claimed=isSourceActorDoubleFrameClaimed(x.sourceActor),oldPool=x.descriptorPool.count;
    equal(x.targetDispatch.dispatchActor(x.actor),undefined,'completed source path returns genuine void');stored(x);
    equal(x.descriptorPool.count,oldPool,'selection never consumes pool0 descriptor records');
    check(!hasIncompleteSourceActorDoubleLifecycle(x.sourceActor),'successful helper does not close lifecycle');
    equal(isSourceActorDoubleFrameClaimed(x.sourceActor),claimed,'standalone helper grants no frame claim');
    let scans=0;observe(()=>rejects(()=>x.targetDispatch.dispatchActor(x.actor),'signed target index 1'),(owner,key)=>{
      if(owner===x.globals&&key==='half80436242') scans++;
    });
    equal(scans,0,'state1 re-dispatch refuses before replaying source850 scan');stored(x);closed(x);
  }
  // Every flag bit is varied independently, with both states of bit0200.
  for(const mask of [0,...Array.from({length:16},(_,i)=>1<<i),0xffff,0xfdff]) {
    const x=setup(make,2,mask),replacement=extra(x,100,0x200);x.list[1]=replacement.id;
    let scratch0=0;
    observe(()=>x.targetDispatch.dispatchActor(x.actor),suffix(x,(owner,key)=>{if(owner===x.scratch&&key==='0') scratch0++;}));
    const redirect=(mask&0x200)===0;
    equal(scratch0,redirect?1:0,`only bit0200 controls redirect for ${mask}`);
    stored(x,redirect?replacement.bytes:x.bytes,x.targetActor,redirect?[100,0,0]:[5,6,7]);
  }
  {
    const x=setup(make,3,0),first=extra(x,200,0x201),later=extra(x,300,0xffff);
    x.list[1]=first.id;x.list[2]=later.id;let laterFlags=0;
    observe(()=>x.targetDispatch.dispatchActor(x.actor),suffix(x,(owner,key)=>{
      if(owner===x.table&&(key===String(later.row+2)||key===String(later.row+3))) laterFlags++;
    }));
    stored(x,first.bytes,x.targetActor,[200,0,0]);equal(laterFlags,0,'first matching flagged sibling wins without looking at a later one');
  }
  {
    const x=setup(make,2,0),same=extra(x,100,0x1ff);x.list[1]=same.id;
    x.targetDispatch.dispatchActor(x.actor);stored(x);
  }
  {
    const x=setup(make,2,0),other=extra(x,100,0x200),foreign=Symbol('different registered actor identity');
    x.allocator.registerExternal(foreign,{active0:0});x.list[1]=other.id;
    let swapped=false,flags=0,mutating=false;
    observe(()=>x.targetDispatch.dispatchActor(x.actor),suffix(x,(owner,key)=>{
      if(mutating) return;
      if(!swapped&&owner===x.table&&key===String(x.row+2)) {
        swapped=true;mutating=true;try {x.allocator.writePointer(other.id,0x20,foreign);x.allocator.writePointer(other.id,0x28,null);} finally {mutating=false;}
      }
      if(owner===other.bytes&&Number(key)>=0x28&&Number(key)<0x2c) flags++;
    }));
    stored(x);equal(flags,0,'mismatched live actor skips descriptor pointer and flags entirely');
  }
}

function liveRedirect(make:Make):void {
  {
    const x=setup(make,2,0),replacement=extra(x,100,0x200),unused=extra(x,200,0x200);x.list[1]=unused.id;
    let changed=false,counts=0;
    observe(()=>x.targetDispatch.dispatchActor(x.actor),suffix(x,(owner,key)=>{
      if(owner===x.globals&&key==='count804361a0') counts++;
      if(!changed&&owner===x.table&&key===String(x.row+2)) {
        changed=true;x.scratch[0]=replacement.id;x.globals.count804361a0=0;
        x.targetActor.active0=0;x.targetActor.team=x.sourceActor.team;x.stageBounds.getActorBinding(x.target).lifecycle18=2;
      }
      if(changed&&owner===x.targetActor&&['active0','team'].includes(String(key))) throw Error('redirect repeated candidate filter');
    }));
    check(changed,'live redirect mutation reached');equal(counts,2,'redirect consumes last saved nearest count, without reload');
    stored(x,replacement.bytes,x.targetActor,[100,0,0]);
  }
  for(const count of [0,0x80000000,0xffffffff]) {
    const x=setup(make,1,0);let reads=0,scratch=0;
    observe(()=>x.targetDispatch.dispatchActor(x.actor),suffix(x,(owner,key)=>{
      if(owner===x.globals&&key==='count804361a0') {reads++;x.globals.count804361a0=count;}
      if(owner===x.scratch&&key==='0') scratch++;
    }));
    stored(x);equal(reads,1,'nearest condition captures raw signed count once');equal(scratch,0,'nonpositive saved count skips redirect');
  }
  {
    const x=setup(make,2,0),replacement=extra(x,100,0x200);x.list[1]=replacement.id;let reads=0,redirect=0;
    observe(()=>x.targetDispatch.dispatchActor(x.actor),suffix(x,(owner,key)=>{
      if(owner===x.globals&&key==='count804361a0') {reads++;x.globals.count804361a0=reads===1?2:0xffffffff;}
      if(owner===x.scratch&&key==='0') redirect++;
    }));
    stored(x);equal(reads,2,'last nearest comparison count is captured');equal(redirect,0,'last negative count wins over initial positive count');
  }
  {
    const x=setup(make,1,0),same=extra(x,100,0x200);let changed=false;
    observe(()=>x.targetDispatch.dispatchActor(x.actor),suffix(x,(owner,key)=>{
      if(!changed&&owner===x.table&&key===String(x.row+2)) {changed=true;x.scratch[0]=same.id;}
    }));
    stored(x,same.bytes,x.targetActor,[100,0,0]);
  }
  for(const phase of ['before','after'] as const) {
    const x=setup(make,2,0),replacement=extra(x,100,0x200);x.list[1]=replacement.id;
    let hit=false;const mutate=suffix(x,(owner,key)=>{
      if(!hit&&owner===x.table&&key===String(x.row+2)) {hit=true;x.table[x.row+2]=2;x.scratch[0]=replacement.id;}
    });
    observe(()=>x.targetDispatch.dispatchActor(x.actor),phase==='before'?mutate:()=>{},phase==='after'?mutate:undefined);
    stored(x,phase==='before'?x.bytes:replacement.bytes,x.targetActor,phase==='before'?[5,6,7]:[100,0,0]);
  }
}

function finalReloads(make:Make):void {
  for(const target of ['null','caller','external'] as const) {
    const x=setup(make),external={marker:17},identity=Symbol('registered actual target');x.allocator.registerExternal(identity,external);
    let changed=false;
    observe(()=>x.targetDispatch.dispatchActor(x.actor),suffix(x,(owner,key)=>{
      if(!changed&&owner===x.admissionState&&key==='pointer504') {
        changed=true;x.allocator.writePointer(x.id,0x20,target==='null'?null:target==='caller'?x.actor:identity);
      }
    }));
    stored(x,x.bytes,target==='null'?null:target==='caller'?x.sourceActor:external);
  }
  {
    const x=setup(make,2,0),replacement=extra(x,100,0x200),external={marker:18},identity=Symbol('captured winner actor replacement');
    x.allocator.registerExternal(identity,external);x.list[1]=replacement.id;let changed=false;
    observe(()=>x.targetDispatch.dispatchActor(x.actor),suffix(x,(owner,key)=>{
      if(!changed&&owner===x.table&&key===String(x.row+2)) {changed=true;x.allocator.writePointer(x.id,0x20,identity);}
    }));
    stored(x,replacement.bytes,x.targetActor,[100,0,0]);
  }
  {
    const x=setup(make);let changed=false,flags=0;
    observe(()=>x.targetDispatch.dispatchActor(x.actor),suffix(x,(owner,key)=>{
      if(!changed&&owner===x.bytes&&key==='32') {changed=true;for(let i=0x20;i<0x24;i++) x.bytes[i]=0;}
      if(owner===x.bytes&&Number(key)>=0x28&&Number(key)<0x2c || owner===x.table&&Number(key)===x.row+2) flags++;
    }));
    stored(x,x.bytes,null);equal(flags,0,'captured null winner actor bypasses descriptor entirely and commits');
  }
  {
    const x=setup(make);let captured=false,restored=false,flags=0;
    observe(()=>x.targetDispatch.dispatchActor(x.actor),suffix(x,(owner,key)=>{
      if(!captured&&owner===x.bytes&&key==='32') {captured=true;for(let i=0x20;i<0x24;i++) x.bytes[i]=0;}
      if(!restored&&owner===x.admissionState&&key==='pointer504') {restored=true;x.allocator.writePointer(x.id,0x20,x.target);}
      if(owner===x.bytes&&Number(key)>=0x28&&Number(key)<0x2c) flags++;
    }));
    stored(x);equal(flags,0,'initial null actor still bypasses descriptors when the final fresh actor becomes nonnull');
  }
  for(const values of [[-0,0,-0],[Math.fround(1e-40),Math.fround(-1e-40),1.25],[1,-2,3]]) {
    const x=setup(make);let changed=false;
    observe(()=>x.targetDispatch.dispatchActor(x.actor),suffix(x,(owner,key)=>{
      if(!changed&&owner===x.admissionState&&key==='pointer508') {changed=true;position(x.bytes,values[0]!,values[1]!,values[2]!);}
    }));
    stored(x,x.bytes,x.targetActor,values);
  }
  {
    const x=setup(make);let changed=false;
    observe(()=>x.targetDispatch.dispatchActor(x.actor),suffix(x,(owner,key)=>{
      if(!changed&&owner===x.vector&&key==='x') {changed=true;position(x.bytes,100,200,300);}
    }));
    stored(x,x.bytes,x.targetActor,[5,6,300]);
  }
}

type Site={name:string;owner:object;key:string;store?:'state'|'p504'|'p508'|'x'|'y'|'z';occurrence?:number};
function sites(x:Fixture):Site[] {
  const word=(offset:number,prefix:string,occurrence=1):Site[]=>Array.from({length:4},(_,i)=>({
    name:`${prefix}${(offset+i).toString(16)}`,owner:x.bytes,key:String(offset+i),occurrence}));
  return [...word(0x20,'a'),...word(0x28,'d'),
    {name:'flaghi',owner:x.table,key:String(x.row+2)},{name:'flaglo',owner:x.table,key:String(x.row+3)},
    {name:'state',owner:x.sourceActor,key:'byte502',store:'state'},
    {name:'p504',owner:x.admissionState,key:'pointer504',store:'p504'},...word(0x20,'fresh',2),
    {name:'p508',owner:x.admissionState,key:'pointer508',store:'p508'},...word(0x64,'raw'),...word(0x68,'raw'),
    {name:'x',owner:x.vector,key:'x',store:'x'},{name:'y',owner:x.vector,key:'y',store:'y'},...word(0x6c,'raw'),
    {name:'z',owner:x.vector,key:'z',store:'z'}];
}
function eventReader(x:Fixture,all:Site[],visit:(site:Site,index:number)=>void) {
  const seen=new Map<object,Map<string,number>>();
  return suffix(x,(owner,key)=>{
    const matches=all.filter(site=>site.owner===owner&&site.key===String(key));if(matches.length===0) return;
    let ownerSeen=seen.get(owner);if(!ownerSeen) {ownerSeen=new Map();seen.set(owner,ownerSeen);}
    const n=(ownerSeen.get(String(key))??0)+1;ownerSeen.set(String(key),n);
    const site=matches.find(site=>(site.occurrence??1)===n);if(site) visit(site,all.indexOf(site));
  });
}
function prefixState(x:Fixture,all:Site[],index:number,skip?:string):void {
  const done=(name:string)=>all.findIndex(site=>site.name===name)<index;
  if(skip!=='state') equal(x.sourceActor.byte502,done('state')?1:0,'state fault prefix');
  if(skip!=='p504') equal(x.admissionState.pointer504,done('p504')?x.bytes:null,'pointer504 fault prefix');
  if(skip!=='p508') equal(x.admissionState.pointer508,done('p508')?x.targetActor:null,'pointer508 fault prefix');
  axes.forEach((key,i)=>{if(skip!==key) equal(x.vector[key],done(key)?[5,6,7][i]:[71,72,73][i],`coordinate ${key} fault prefix`);});
}
function orderAndFaults(make:Make):void {
  {
    const x=setup(make),all=sites(x),events:string[]=[];
    observe(()=>x.targetDispatch.dispatchActor(x.actor),eventReader(x,all,site=>events.push(site.name)));
    equal(events.join(','),all.map(site=>site.name).join(','),'exact winner descriptor, ordered pointer stores, captured XY then X/Y then Z load/store schedule');stored(x);
  }
  // Fault every source byte and every destination, not just one representative
  // per word. Read-only source bytes remain legal; destination stores are lazy.
  for(let index=0;index<32;index++) {
    const x=setup(make),all=sites(x),target=all[index]!;let hit=false;
    const events:string[]=[];
    observe(()=>rejects(()=>x.targetDispatch.dispatchActor(x.actor),target.store?'non-writable':'own data'),eventReader(x,all,(site,i)=>{
      events.push(site.name);if(i===index&&!hit) {hit=true;if(target.store) Object.defineProperty(target.owner,target.key,{writable:false});else Reflect.deleteProperty(target.owner,target.key);}
    }));
    check(hit,`fault reached ${target.name}`);equal(events.join(','),all.slice(0,index+1).map(site=>site.name).join(','),`no later operation after ${target.name}`);
    prefixState(x,all,index);closed(x);
  }
  for(const name of ['flaghi','flaglo','state','x','y','z']) for(const kind of ['accessor','missing','inherited'] as const) {
    const x=setup(make),all=sites(x),index=all.findIndex(site=>site.name===name),target=all[index]!;let invoked=0,hit=false;
    observe(()=>rejects(()=>x.targetDispatch.dispatchActor(x.actor),'own data'),eventReader(x,all,(_site,i)=>{
      if(i!==index||hit) return;hit=true;
      if(kind==='accessor') Object.defineProperty(target.owner,target.key,{get(){invoked++;return 0;},set(){invoked++;},configurable:true});
      else {Reflect.deleteProperty(target.owner,target.key);if(kind==='inherited') Object.setPrototypeOf(target.owner,{[target.key]:0});}
    }));
    check(hit,`own-data fault reached ${name}`);equal(invoked,0,'accessor is not evaluated');prefixState(x,all,index,target.store);closed(x);
  }
  for(const axis of axes) for(const value of [NaN,Infinity,-Infinity]) {
    const x=setup(make),all=sites(x);let hit=false;
    observe(()=>rejects(()=>x.targetDispatch.dispatchActor(x.actor),'float32'),suffix(x,(owner,key)=>{
      if(!hit&&owner===x.admissionState&&key==='pointer508') {hit=true;float(x.bytes,0x64+axes.indexOf(axis)*4,value);}
    }));
    prefixState(x,all,all.findIndex(site=>site.name===axis));closed(x);
  }
  for(const kind of ['missing','null','accessor'] as const) {
    const x=setup(make);let invoked=0,loads=0;
    if(kind==='missing') Reflect.deleteProperty(x.sourceActor,'lockTarget');
    else if(kind==='null') Reflect.set(x.sourceActor,'lockTarget',null);
    else Object.defineProperty(x.sourceActor,'lockTarget',{get(){invoked++;return x.vector;},configurable:true});
    observe(()=>rejects(()=>x.targetDispatch.dispatchActor(x.actor),kind==='null'?'record':'8006ba34'),suffix(x,(owner,key)=>{
      if(owner===x.bytes&&Number(key)>=0x64&&Number(key)<0x6c) loads++;
    }));
    equal(loads,8,'absent vector fails only after both complete raw XY loads');equal(invoked,0,'target ingress accessor is never evaluated');
    equal(x.sourceActor.byte502,1,'missing vector retains state');equal(x.admissionState.pointer504,x.bytes,'missing vector retains chosen object');
    equal(x.admissionState.pointer508,x.targetActor,'missing vector retains actual target');closed(x);
  }
}

function redirectFaultsAndBounds(make:Make):void {
  for(const kind of ['null','number','missing','accessor','unknown'] as const) {
    const x=setup(make,1,0);let entered=false,invoked=0;
    observe(()=>rejects(()=>x.targetDispatch.dispatchActor(x.actor),kind==='missing'||kind==='accessor'?'own data':kind==='unknown'?'unknown':kind==='null'?'null':'pointer'),suffix(x,(owner,key)=>{
      if(!entered&&owner===x.table&&key===String(x.row+2)) {
        entered=true;
        if(kind==='missing') Reflect.deleteProperty(x.scratch,'0');
        else if(kind==='accessor') Object.defineProperty(x.scratch,'0',{get(){invoked++;return x.id;},configurable:true});
        else Reflect.set(x.scratch,'0',kind==='null'?null:kind==='number'?0:Symbol('unknown redirect object'));
      }
    }));
    equal(invoked,0,'redirect scratch accessor never runs');equal(x.sourceActor.byte502,0,'redirect pointer failure precedes state store');closed(x);
  }
  {
    const x=setup(make,1,0);for(let i=1;i<4096;i++) x.scratch[i]=x.id;
    let counts=0,redirect=false,forbidden=0;
    observe(()=>rejects(()=>x.targetDispatch.dispatchActor(x.actor),'4096'),suffix(x,(owner,key)=>{
      if(owner===x.globals&&key==='count804361a0') {counts++;x.globals.count804361a0=counts<4096?4096:4097;}
      if(owner===x.table&&key===String(x.row+2)) redirect=true;
      if(redirect&&owner===x.scratch&&/^\d+$/.test(String(key))) {if(key==='4096') forbidden++;}
    }));
    // The nearest loop itself reaches index4096 if its terminal count grows.
    equal(forbidden,0,'4096 bound precedes the reached indexed source descriptor');
    equal(x.sourceActor.byte502,0,'bound failure retains uncommitted state');closed(x);
  }
}


function savedRedirectLimit(make:Make):void {
  const x=setup(make,1,0);for(let i=1;i<4096;i++) x.scratch[i]=x.id;
  let counts=0,redirect=false,visits=0;
  observe(()=>x.targetDispatch.dispatchActor(x.actor),suffix(x,(owner,key)=>{
    if(owner===x.globals&&key==='count804361a0') {counts++;x.globals.count804361a0=4096;}
    if(owner===x.table&&key===String(x.row+2)) redirect=true;
    if(redirect&&owner===x.scratch&&/^\d+$/.test(String(key))) {
      visits++;x.globals.count804361a0=0; // Does not shorten the saved CTR loop.
    }
  }));
  equal(counts,4096,'last nearest comparison is the only count retained by maximum redirect');
  equal(visits,4096,'saved positive count4096 permits every in-bound live scratch load');stored(x);
}

function descriptorFaults(make:Make):void {
  for(const site of ['winner','sibling'] as const) for(const kind of ['null','unknown','byte','missing','accessor'] as const) {
    const x=setup(make,site==='sibling'?2:1,site==='sibling'?0:0x200),other=site==='sibling'?extra(x,100,0x200):undefined;
    if(other) x.list[1]=other.id;
    const target=other??x,bytes=target.bytes,row=target.row;let entered=false,invoked=0;
    observe(()=>rejects(()=>x.targetDispatch.dispatchActor(x.actor),kind==='null'?(other?'8006b9fc':'8006b9c8'):
      kind==='unknown'?'opaque identity':kind==='byte'?'source integer':'own data'),suffix(x,(owner,key)=>{
      if(entered) return;
      if(kind==='null'||kind==='unknown') {
        if(owner!==bytes||key!=='40') return;entered=true;
        for(let i=0x28;i<0x2c;i++) bytes[i]=kind==='null'?0:255;
      } else {
        if(owner!==x.table||key!==String(row+2)) return;entered=true;
        if(kind==='byte') x.table[row+2]=256;
        else if(kind==='missing') Reflect.deleteProperty(x.table,String(row+2));
        else Object.defineProperty(x.table,String(row+2),{get(){invoked++;return 2;},configurable:true});
      }
    }));
    check(entered,`${site} ${kind} descriptor fault reached`);equal(invoked,0,'descriptor byte getter is never evaluated');
    equal(x.sourceActor.byte502,0,'descriptor fault is before target writes');equal(x.admissionState.pointer504,null,'descriptor fault retains null504');closed(x);
  }
  {
    const x=setup(make),bytes:Bytes={2:2,3:0},id=Symbol('explicit base byte descriptor');
    x.allocator.registerExternal(id,bytes);x.allocator.writePointer(x.id,0x28,id);
    Object.freeze(bytes);x.targetDispatch.dispatchActor(x.actor);stored(x);
  }
}

function descriptorOwnerAliases(make:Make):void {
  for(const kind of ['actor','lockTarget','pos','motion','aim','matrix'] as const) {
    const x=setup(make),owner=kind==='actor'?x.targetActor:kind==='lockTarget'?x.vector:kind==='pos'?x.sourceActor.pos:
      kind==='motion'?x.sourceActor.motion:kind==='aim'?x.sourceActor.aimOrigin518:x.matrix;
    // Explicit malicious host aliases: ordinary pointer registration cannot
    // make an existing scalar/vector/matrix owner into descriptor byte memory.
    Reflect.set(owner,'2',2);Reflect.set(owner,'3',0);
    const identity=kind==='actor'?x.target:Symbol(`registered ${kind} descriptor masquerade`);
    if(kind!=='actor') x.allocator.registerExternal(identity,owner);
    x.allocator.writePointer(x.id,0x28,identity);let flagReads=0;
    observe(()=>rejects(()=>x.targetDispatch.dispatchActor(x.actor),'descriptor byte owner aliases'),suffix(x,(actual,key)=>{
      if(actual===owner&&(key==='2'||key==='3')) flagReads++;
    }));
    equal(flagReads,0,`${kind} masquerade rejected before flag bytes`);
    equal(x.sourceActor.byte502,0,'descriptor owner alias leaves state uncommitted');
    equal(x.admissionState.pointer504,null,'descriptor owner alias leaves504 uncommitted');
    equal(x.admissionState.pointer508,null,'descriptor owner alias leaves508 uncommitted');closed(x);
  }
  {
    const x=setup(make);let entered=false,lowReads=0;
    observe(()=>rejects(()=>x.targetDispatch.dispatchActor(x.actor),'descriptor byte owner aliases'),()=>{},suffix(x,(owner,key)=>{
      if(!entered&&owner===x.table&&key===String(x.row+2)) {entered=true;Reflect.set(x.sourceActor,'lockTarget',x.table);}
      if(owner===x.table&&key===String(x.row+3)) lowReads++;
    }));
    check(entered,'canonical alias introduced after captured high flag byte');equal(lowReads,0,'late high-byte alias refuses before low flag byte');
    equal(x.sourceActor.byte502,0,'late descriptor alias refuses before state');
    equal(x.admissionState.pointer504,null,'late descriptor alias refuses before504');
    equal(x.admissionState.pointer508,null,'late descriptor alias refuses before508');closed(x);
  }
}

function aliasesAndInterruptions(make:Make):void {
  for(const owner of ['stack','object','actor','binding','globals','table'] as const) {
    const x=setup(make),selected=owner==='stack'?x.stack:owner==='object'?x.bytes:owner==='actor'?x.sourceActor:
      owner==='binding'?x.admissionState:owner==='globals'?x.globals:x.table;
    Reflect.set(x.sourceActor,'lockTarget',selected);for(const axis of axes) Reflect.set(selected,axis,17);
    rejects(()=>x.targetDispatch.dispatchActor(x.actor),'alias');closed(x);
  }
  {
    const x=setup(make),replacement:Vector={x:81,y:82,z:83};let hit=false;
    observe(()=>rejects(()=>x.targetDispatch.dispatchActor(x.actor),'canonical owner changed'),suffix(x,(owner,key)=>{
      if(!hit&&owner===x.vector&&key==='x') {hit=true;Reflect.set(x.sourceActor,'lockTarget',replacement);}
    }));
    equal(x.vector.x,5,'owner replacement after X admission preserves completed X store');
    equal(x.vector.y,72,'owner change fails before old Y store');equal(replacement.y,82,'new vector is not substituted mid-copy');closed(x);
  }
  {
    const x=setup(make);Object.freeze(x.bytes);Object.freeze(x.table);x.targetDispatch.dispatchActor(x.actor);stored(x);
  }
  for(const key of ['field50c','field510','field514','position50c','targetPosition50c',
    ...Array.from({length:12},(_,i)=>String(0x50c+i)),
    ...Array.from({length:12},(_,i)=>`byte${(0x50c+i).toString(16)}`),
    ...Array.from({length:12},(_,i)=>`byte${(0x50c+i).toString(16).toUpperCase()}`)]) {
    const x=setup(make);Reflect.set(x.sourceActor,key,5);rejects(()=>x.targetDispatch.dispatchActor(x.actor),key);closed(x);
  }
  for(const name of ['flaghi','flaglo','state','p504','fresh20','p508','raw64','raw68','x','y','raw6c','z'])
    for(const kind of ['reentry','caller','candidate'] as const) for(const phase of ['before','after'] as const) {
    const x=setup(make),all=sites(x),index=all.findIndex(site=>site.name===name);let hit=false;
    if(kind==='candidate') x.control.bindActualActor(x.target,x.movement);
    const inject=eventReader(x,all,(_site,i)=>{
      if(i!==index||hit) return;hit=true;
      if(kind==='reentry') rejects(()=>x.targetDispatch.dispatchActor(x.actor),'same-runtime reentry');
      else {const id=kind==='caller'?x.actor:x.target;x.control.getActorBinding(id).activeMask579=256;
        rejects(()=>x.control.update(id,1),'activeMask579');}
    });
    observe(()=>rejects(()=>x.targetDispatch.dispatchActor(x.actor),kind==='reentry'?'caught same-runtime reentry':'incomplete'),
      phase==='before'?inject:()=>{},phase==='after'?inject:undefined);
    check(hit,`${kind} interruption ${phase} ${name} is reached`);prefixState(x,all,index);closed(x);
  }
}
function outerTests(make:Make):void {
  for(const nullable of [false,true]) {
    const x=setup(make),frame=outer(x);let selected=false,finalStore=false,captured=false;
    let pointer508=0,afterFinal508=0,physicalReloads=0,nextIdentity=0,nextActive=0;
    const nullWinner=suffix(x,(owner,key)=>{
      if(nullable&&!captured&&owner===x.bytes&&key==='32') {
        captured=true;for(let i=0x20;i<0x24;i++) x.bytes[i]=0;
      }
    });
    observe(()=>rejects(()=>frame.runFrame(),nullable?'8006b180':'8006afb0'),(owner,key)=>{
      nullWinner(owner,key);
      if(owner===x.targetPreparation&&key==='targetDispatch') selected=true;
      if(!selected) return;
      if(owner===x.admissionState&&key==='pointer508') {pointer508++;if(finalStore) afterFinal508++;}
      if(owner===x.massPreparation&&key==='physicalBlock') physicalReloads++;
      if(owner===x.physicalIdentities&&key==='1') nextIdentity++;
      if(owner===x.slotTargets[1]&&key==='active0') nextActive++;
    },(owner,key)=>{if(owner===x.vector&&key==='z') finalStore=true;});
    stored(x,x.bytes,nullable?null:x.targetActor);
    check(finalStore,'genuine helper reaches its final coordinate-store admission');
    equal(pointer508,2,'helper508 destination admission precedes one genuine primary af8c load');
    equal(afterFinal508,1,'completed selected-target copy is followed by one captured primary508 load');
    equal(physicalReloads,0,'successful helper never skips mandatory continuation to third-pass reload');
    equal(nextIdentity,0,'successful helper never skips mandatory continuation to next second-pass identity');
    equal(nextActive,0,'successful helper never reads next second-pass actor');
    equal(x.massPreparation.orderCount.count80436260,6,'outer completes genuine mass order before target helper');
    equal(x.massHost.sourceArrowMass204,1200,'actual mass update retained');
    closed(x);rejects(()=>frame.runFrame(),'permanently incomplete');
    for(const run of [()=>x.scheduler.runGroup(9),()=>x.scheduler.runSlots(8),()=>x.scheduler.runWrapper(8)]) rejects(run,'exclusively owned');
    rejects(()=>x.root.dispatchStoredRoot(x.child),'exclusively owned');
  }
}

export function runActorTargetStorageSelfTests(make:Make):void {
  basicAndFlags(make);liveRedirect(make);finalReloads(make);orderAndFaults(make);redirectFaultsAndBounds(make);savedRedirectLimit(make);descriptorFaults(make);descriptorOwnerAliases(make);aliasesAndInterruptions(make);outerTests(make);
  console.log('[actor-target-storage] PASS: genuine HIT interior descriptor reuse, live BE0200 sibling selection and saved signed count, original OBJECT/actual identity stores and raw XY-before-stores/Z-after-Y order, lazy failures and partial writes, aliases/reentry/independent closure, state1 refusal and real outer primary null-constant/SquareDistance-threshold boundaries before next-actor or third-pass reads; explicit offline synthetic operands only, no completed-frame/console/full-game claim');
}
