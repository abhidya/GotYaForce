import {createActorTargetCandidatesTestFixture} from './actor-target-candidates.selftest.js';
import {createSourceBattleOuterFrameRuntime,type SourceBattleOuterFrameSources} from './battle-outer-frame.js';
import {hasIncompleteSourceActorDoubleLifecycle,isSourceActorDoubleFrameClaimed} from './actor-double-prehook.js';
import {requireSourceObjectSchedulerSnapshot} from './source-object-scheduler.js';
import type {createBattleTargetPreparationTestFixture} from './attached-setup-animation.selftest.js';

/** Explicit synthetic inputs on the genuine allocator, stage, world and Double
 * lifecycle graph. Observe the selected original OBJECT+20 load, never inject a
 * distance result, alternate actor-position representation or selector callback.
 * The real nonnull/null postselection source paths remain unsupported. */
type Make=typeof createBattleTargetPreparationTestFixture;
type Bytes=Partial<Record<number,number>>;
type Stack={x:number;y:number;z:number};
const axes=['x','y','z'] as const,lanes=[3,7,11] as const;
function check(ok: boolean,why: string): void {if(!ok) throw Error(`[actor-target-distance-test] ${why}`);}
function equal(actual: unknown,expected: unknown,why: string): void {
  check(Object.is(actual,expected),`${why}: got ${String(actual)}, expected ${String(expected)}`);
}
function rejects(run: ()=>unknown,fragment: string): string {
  let message='';try {run();} catch(error) {message=String(error);}
  check(message.includes(fragment),`expected ${fragment}, got ${message || 'success'}`);return message;
}
function observe(run: ()=>void,before: (owner: object,key: PropertyKey)=>void,
  after?: (owner: object,key: PropertyKey)=>void): void {
  const original=Object.getOwnPropertyDescriptor;
  Object.getOwnPropertyDescriptor=((owner: object,key: PropertyKey)=>{
    before(owner,key);const result=original(owner,key);after?.(owner,key);return result;
  }) as typeof original;
  try {run();} finally {Object.getOwnPropertyDescriptor=original;}
}
function float(bytes: Bytes,offset: number,value: number): void {
  const view=new DataView(new ArrayBuffer(4));view.setFloat32(0,value,false);
  for(let i=0;i<4;i++) bytes[offset+i]=view.getUint8(i);
}
function position(bytes: Bytes,x: number,y=0,z=0): void {
  float(bytes,0x64,x);float(bytes,0x68,y);float(bytes,0x6c,z);
}
function setup(make: Make,half=1) {
  const x=createActorTargetCandidatesTestFixture(make,half),stack: Stack={x:91,y:92,z:93};
  x.sources.projectionStack=stack;
  const processor=x.actionSources.processor;
  Reflect.set(x.rootSources,'processor',processor);
  equal(processor.gqr0,0,'distance borrows the pre-existing genuine Double processor');
  x.scalarDescriptor.byte10=1;
  const matrix=x.matrices.getMatrix(x.world.getStorage(x.actor).matrices8d4[1]!);
  matrix[3]=0;matrix[7]=0;matrix[11]=0;
  position(x.objectBytes,5);position(x.nextObjectBytes,3);
  if(half>1) {x.list[1]=x.nextChild;x.allocator.writePointer(x.nextChild,0x20,x.target);}
  return Object.assign(x,{stack,processor,matrix});
}
type Fixture=ReturnType<typeof setup>;
function extra(x: Fixture,value: number,y=0,z=0) {
  const id=Symbol('explicit extra distance OBJECT'),bytes: Bytes={};
  for(let offset=0;offset<0x70;offset++) bytes[offset]=0;
  x.allocator.registerObject(id,bytes);x.allocator.writePointer(id,0x20,x.target);position(bytes,value,y,z);
  return {id,bytes};
}
function finish(x: Fixture,nullable=false): void {
  rejects(()=>x.targetDispatch.dispatchActor(x.actor),nullable?'8006ba18':'8006b9c4');
}
function closed(x: Fixture): void {
  check(hasIncompleteSourceActorDoubleLifecycle(x.sourceActor),'distance refusal closes actual caller');
  rejects(()=>x.targetDispatch.dispatchActor(x.actor),'incomplete');
  rejects(()=>x.allocator.assertActorComplete(x.actor),'incomplete');
}
function unchanged(x: Fixture,tail=x.actor): void {
  equal(x.sourceActor.byte502,0,'no final target state store');
  equal(x.admissionState.pointer504,null,'no final target504 store');
  equal(x.admissionState.pointer508,null,'no final target508 store');
  equal(x.scratch[7],tail,'unchanged scratch word is retained');
}
function projected(x: Fixture,tail=x.actor): void {
  axes.forEach((axis,i)=>equal(x.stack[axis],x.matrix[lanes[i]!],`completed projection ${axis} retained`));
  unchanged(x,tail);
}
function outer(x: Fixture) {
  const sources: SourceBattleOuterFrameSources={scheduler:x.scheduler,systemGlobals:x.systemGlobals,
    massPreparation:x.massPreparation,targetPreparation:x.targetPreparation};
  return createSourceBattleOuterFrameRuntime(sources);
}
/** Skip the projection's store descriptor; all subsequent source reads are live. */
function afterProjection(x: Fixture,visit: (owner: object,key: PropertyKey)=>void) {
  let reached=false;
  return (owner: object,key: PropertyKey): void=>{
    if(!reached) {if(owner===x.stack&&key==='z') reached=true;return;}
    visit(owner,key);
  };
}
function winner(x: Fixture,expected: Bytes,mutate?: (owner: object,key: PropertyKey)=>void,nullable=false): void {
  const loads: string[]=[],owners: object[]=[];let mutating=false;
  observe(()=>finish(x,nullable),afterProjection(x,(owner,key)=>{
    if(mutating) return;
    mutating=true;try {mutate?.(owner,key);} finally {mutating=false;}
    if(/^\d+$/.test(String(key))&&Number(key)>=0x20&&Number(key)<0x24 &&
      owner!==x.matrix&&owner!==x.scratch&&owner!==x.list) {owners.push(owner);loads.push(String(key));}
  }));
  equal(loads.join(','),'32,33,34,35','only the final selected OBJECT+20 is read after distances');
  owners.forEach(owner=>equal(owner,expected,'winner is the original captured OBJECT, not actor or reloaded scratch'));
  unchanged(x);
}

function orderTests(make: Make): void {
  {
    const x=setup(make);Reflect.deleteProperty(x.rootSources,'processor');let loads=0;
    observe(()=>rejects(()=>x.targetDispatch.dispatchActor(x.actor),'8006b968'),afterProjection(x,(owner,key)=>{
      if(owner===x.objectBytes&&Number(key)>=0x64&&Number(key)<0x70) loads++;
    }));
    equal(loads,0,'absent root processor preserves previous call boundary before OBJECT coordinates');projected(x);
  }
  {
    const x=setup(make),events: string[]=[],claimed=isSourceActorDoubleFrameClaimed(x.sourceActor);
    const matrix=[...x.matrix],attached=x.joints.getBinding(x.joint).aobj7c;let work=0,profile=0,downstream=0;
    observe(()=>finish(x),afterProjection(x,(owner,key)=>{
      if(owner===x.processor&&key==='gqr0') profile++;
      if(owner===x.admissionState&&['pointer504','pointer508'].includes(String(key)) ||
        owner===x.sourceActor&&key==='byte502' || owner===x.objectBytes&&Number(key)>=0x28&&Number(key)<0x2c) downstream++;
      if(owner===x.stack&&axes.includes(key as typeof axes[number])) events.push(`a.${String(key)}`);
      if(owner===x.objectBytes&&Number(key)>=0x64&&Number(key)<0x70) events.push(`b.${Number(key).toString(16)}`);
      if(owner===x.globals&&key==='count804361a0') events.push('count');
      if(owner===x.objectBytes&&Number(key)>=0x20&&Number(key)<0x24) events.push(`winner.${Number(key).toString(16)}`);
      if(owner===x.groups || owner===x.matchGlobals&&['maskD1','maskD2'].includes(String(key))) work++;
    }));
    equal(events.join(','),'a.y,a.z,b.68,b.69,b.6a,b.6b,b.6c,b.6d,b.6e,b.6f,a.x,a.y,b.64,b.65,b.66,b.67,b.68,b.69,b.6a,b.6b,count,winner.20,winner.21,winner.22,winner.23',
      'actual paired load order, repeated Y loads, loop count and final pointer load');
    equal(profile,4,'GQR0 is freshly read at each of the four paired loads');
    equal(downstream,0,'no sibling descriptor load or target destination admission after selected pointer');
    equal(work,0,'direct distance helper does not execute scheduler mask/group work');
    equal(isSourceActorDoubleFrameClaimed(x.sourceActor),claimed,'distance helper does not create frame claim');
    equal(x.joints.getBinding(x.joint).aobj7c,attached,'distance does not advance attached animation');
    matrix.forEach((value,index)=>equal(x.matrix[index],value,'distance does not rebuild matrix'));
    rejects(()=>requireSourceObjectSchedulerSnapshot(x.scheduler,x.allocator,x.child),'private active');projected(x);closed(x);
  }
  {
    const x=setup(make,2);let reads=0;
    observe(()=>winner(x,x.nextObjectBytes),(owner,key)=>{
      if(owner===x.scratch&&key==='0') reads++;
    });
    equal(reads,2,'first pointer is read once for append admission and once before projection, never after distance');
    equal(x.globals.count804361a0,2,'distance does not rewrite scan count');projected(x);
  }
  for(const pointer of [null,Symbol('unknown OBJECT')]) {
    const x=setup(make),reads: string[]=[];
    observe(()=>rejects(()=>x.targetDispatch.dispatchActor(x.actor),pointer===null?'null':'unknown'),(owner,key)=>{
      if(owner===x.scalarDescriptor&&key==='byte10') x.scratch[0]=pointer;
      if(owner===x.stack&&axes.includes(key as typeof axes[number])) reads.push(String(key));
    });
    equal(reads.join(','),'x,y,z,y,z','unknown/null original pointer is not dereferenced until after first A paired load');projected(x);closed(x);
  }
}

function liveAndSelectionTests(make: Make): void {
  for(const points of [[9,3,6],[9,3,3],[3,9,9],[3,-3,6],[0,-0,0]] as const) {
    const x=setup(make,3),third=extra(x,points[2]);
    x.list[2]=third.id;x.scratch[2]=null;position(x.objectBytes,points[0]);position(x.nextObjectBytes,points[1]);
    const distances=points.map(value=>value*value),best=Math.min(...distances),index=distances.lastIndexOf(best);
    winner(x,[x.objectBytes,x.nextObjectBytes,third.bytes][index]!);projected(x);
  }
  {
    const x=setup(make,2);position(x.objectBytes,0,0,5);position(x.nextObjectBytes,0,0,3);
    winner(x,x.nextObjectBytes); // Distinguishes all-axis distance from XY-only.
  }
  {
    const x=setup(make,2);position(x.objectBytes,0,5,0);position(x.nextObjectBytes,0,3,0);
    winner(x,x.nextObjectBytes); // Distinguishes all-axis distance from XZ-only.
  }
  {
    const x=setup(make,2),third=extra(x,1);let changed=false;
    winner(x,x.objectBytes,(owner,key)=>{
      if(!changed&&owner===x.objectBytes&&key==='104') {changed=true;x.scratch[0]=third.id;position(x.nextObjectBytes,9);}
    });
    check(changed,'first captured pointer mutation occurred');equal(x.scratch[0],third.id,'later scratch0 mutation is not undone');
  }
  {
    const x=setup(make,2),third=extra(x,1);let changed=false;
    winner(x,third.bytes,(owner,key)=>{
      if(!changed&&owner===x.globals&&key==='count804361a0') {changed=true;x.scratch[1]=third.id;}
    });
    check(changed,'fresh next pointer changes at reached loop count');
  }
  {
    const x=setup(make,2);let changed=false;
    winner(x,x.nextObjectBytes,(owner,key)=>{
      if(!changed&&owner===x.scratch&&key==='1') {changed=true;x.allocator.writePointer(x.nextChild,0x20,null);}
    },true);
    check(changed,'selected OBJECT+20 can become null after completed scan');
  }
  {
    const x=setup(make,2);position(x.objectBytes,1);position(x.nextObjectBytes,5);let changed=false;
    winner(x,x.nextObjectBytes,(owner,key)=>{
      if(!changed&&owner===x.scratch&&key==='1') {changed=true;x.stack.x=5;}
    });
    equal(x.stack.x,5,'later distance consumes current stack rather than captured projection');
  }
  {
    const x=setup(make,2);position(x.objectBytes,0,2,0);position(x.nextObjectBytes,0,3,0);let reads=0;
    winner(x,x.objectBytes,(owner,key)=>{
      if(owner===x.objectBytes&&key==='104'&&++reads===2) float(x.objectBytes,0x68,100);
      if(owner===x.scratch&&key==='1') x.stack.y=0;
    });
    equal(reads,2,'B.y is loaded independently twice; changed unused FMA Y does not replace old squared Y');
  }
  {
    const x=setup(make,2);position(x.objectBytes,0,2,0);position(x.nextObjectBytes,0,3,0);let reads=0;
    winner(x,x.objectBytes,(owner,key)=>{
      if(owner===x.stack&&key==='y'&&++reads===2) x.stack.y=100;
      if(owner===x.scratch&&key==='1') x.stack.y=0;
    });
    equal(reads,4,'A.y is independently reloaded in both calls, including unused second FMA lane');
  }
  for(const phase of ['before','after'] as const) {
    const x=setup(make,2);position(x.objectBytes,5);position(x.nextObjectBytes,3);let changed=false;
    const mutate=afterProjection(x,(owner,key)=>{
      if(!changed&&owner===x.objectBytes&&key==='100') {changed=true;position(x.objectBytes,1);}
    });
    // 5 and 1 have different first BE byte; after capture cannot change that byte.
    const selected=phase==='before'?x.objectBytes:x.nextObjectBytes;
    observe(()=>winner(x,selected),phase==='before'?mutate:()=>{},phase==='after'?mutate:undefined);
    check(changed,'BE byte mutation reached first X byte');
  }
  {
    const x=setup(make,2);let changed=false,filtered=0;
    winner(x,x.nextObjectBytes,(owner,key)=>{
      if(!changed&&owner===x.globals&&key==='count804361a0') {
        changed=true;x.targetActor.active0=0;x.targetActor.team=x.sourceActor.team;x.stageBounds.getActorBinding(x.target).lifecycle18=2;
      }
      if(owner===x.targetActor&&['active0','team'].includes(String(key))) filtered++;
    });
    equal(filtered,0,'nearest loop does not re-filter candidate actor fields after genuine scan');
  }
}

function arithmeticAndFaultTests(make: Make): void {
  {
    const x=setup(make,2),adjacent=1+2**-23;
    position(x.objectBytes,adjacent);position(x.nextObjectBytes,adjacent,2**-12);
    // x*x rounds to 1+2 ulps; adding y*y separately is an even tie and
    // remains there. The actual fused exact sum lies above that tie and
    // rounds to 1+3 ulps. A non-fused implementation would replace the first
    // winner on equality, while the authenticated FMA must retain it.
    winner(x,x.objectBytes);projected(x);
  }
  for(const values of [[-0,0,-0],[Math.fround(1e-40),Math.fround(-1e-40),Math.fround(1e-40)],[1.25,-2.5,3.75]]) {
    const x=setup(make);lanes.forEach((lane,i)=>{x.matrix[lane]=values[i]!;});
    position(x.objectBytes,values[0]!,values[1]!,values[2]!);finish(x);projected(x);
  }
  for(const site of ['stack-y','stack-z','stack-x','stack-y2','object-y','object-z','object-x','object-y2'] as const)
    for(const value of [NaN,Infinity,-Infinity]) {
    const x=setup(make);let yA=0,yB=0,hit=false;
    observe(()=>rejects(()=>x.targetDispatch.dispatchActor(x.actor),'float32'),afterProjection(x,(owner,key)=>{
      if(owner===x.stack&&key==='y') yA++;
      if(owner===x.objectBytes&&key==='104') yB++;
      const at=site==='stack-y'?owner===x.stack&&key==='y'&&yA===1:
        site==='stack-y2'?owner===x.stack&&key==='y'&&yA===2:
        site==='stack-z'?owner===x.stack&&key==='z':site==='stack-x'?owner===x.stack&&key==='x':
          site==='object-y'?owner===x.objectBytes&&key==='104'&&yB===1:
            site==='object-y2'?owner===x.objectBytes&&key==='104'&&yB===2:
              owner===x.objectBytes&&key===(site==='object-x'?'100':'108');
      if(at&&!hit) {hit=true;if(site.startsWith('stack')) Reflect.set(x.stack,String(key),value);else float(x.objectBytes,Number(key),value);}
    }));
    check(hit,`invalid finite operand injected at ${site}`);unchanged(x);closed(x);
  }
  for(const value of [0.1,1e40,undefined,'1',null]) {
    const x=setup(make);let hit=false;
    observe(()=>rejects(()=>x.targetDispatch.dispatchActor(x.actor),'float32'),afterProjection(x,(owner,key)=>{
      if(!hit&&owner===x.stack&&key==='y') {hit=true;Reflect.set(x.stack,'y',value);}
    }));
    check(hit,'malformed live stack operand reached');unchanged(x);
  }
  for(const site of ['subtract-y','subtract-z','subtract-x','square-y','square-z','fma-x','unused-fma-y','sum'] as const) {
    const x=setup(make),max=Math.fround(3.4e38),large=Math.fround(2e19),sum=Math.fround(1.3e19);let y=0,afterX=0;
    if(site==='subtract-y') {x.matrix[7]=max;position(x.objectBytes,0,-max);}
    if(site==='subtract-z') {x.matrix[11]=max;position(x.objectBytes,0,0,-max);}
    if(site==='subtract-x') {x.matrix[3]=max;position(x.objectBytes,-max);}
    if(site==='square-y') position(x.objectBytes,0,large);
    if(site==='square-z') position(x.objectBytes,0,0,large);
    if(site==='fma-x') position(x.objectBytes,large);
    if(site==='sum') position(x.objectBytes,sum,sum,sum);
    observe(()=>rejects(()=>x.targetDispatch.dispatchActor(x.actor),site==='square-y'?'square oldY':site==='square-z'?'square oldZ':'overflow'),afterProjection(x,(owner,key)=>{
      if(owner===x.stack&&key==='y'&&++y===2&&site==='unused-fma-y') x.stack.y=large;
      if(owner===x.stack&&key==='x') afterX++;
    }));
    equal(afterX,site==='subtract-y'||site==='subtract-z'?0:1,`${site} preserves instruction arithmetic/load order`);
    unchanged(x);closed(x);
  }
  for(const kind of ['missing','accessor','byte','inherited'] as const) for(const offset of [0x68,0x6c,0x64]) {
    const x=setup(make);let invoked=0,hit=false;
    observe(()=>rejects(()=>x.targetDispatch.dispatchActor(x.actor),kind==='byte'?'byte':'own data'),afterProjection(x,(owner,key)=>{
      if(!hit&&owner===x.objectBytes&&key===String(offset)) {
        hit=true;
        if(kind==='byte') x.objectBytes[offset]=256;
        else if(kind==='accessor') Object.defineProperty(x.objectBytes,String(offset),{get() {invoked++;return 0;},configurable:true});
        else {Reflect.deleteProperty(x.objectBytes,String(offset));if(kind==='inherited') Object.setPrototypeOf(x.objectBytes,{[offset]:0});}
      }
    }));
    check(hit,'coordinate byte fault reached');equal(invoked,0,'OBJECT byte accessors are not evaluated');projected(x);closed(x);
  }
  for(const kind of ['missing','accessor','inherited']) {
    const x=setup(make);let invoked=0,hit=false;
    observe(()=>rejects(()=>x.targetDispatch.dispatchActor(x.actor),'own data'),afterProjection(x,(owner,key)=>{
      if(!hit&&owner===x.stack&&key==='y') {
        hit=true;
        if(kind==='accessor') Object.defineProperty(x.stack,'y',{get() {invoked++;return 0;},configurable:true});
        else {Reflect.deleteProperty(x.stack,'y');if(kind==='inherited') Object.setPrototypeOf(x.stack,{y:0});}
      }
    }));
    check(hit,'stack fault reached');equal(invoked,0,'stack input accessors are not evaluated');unchanged(x);closed(x);
  }
  {
    const x=setup(make);let hit=false;
    observe(()=>finish(x),afterProjection(x,(owner,key)=>{
      if(!hit&&owner===x.processor&&key==='gqr0') {
        hit=true;Object.freeze(x.stack);Object.freeze(x.objectBytes);Object.defineProperty(x.processor,'gqr0',{writable:false});
      }
    }));
    check(hit,'readonly source test reaches profile');projected(x);
  }
}

function liveCountTests(make: Make): void {
  for(const count of [0,1,0x80000000,0xffffffff]) {
    const x=setup(make,2);let reads=0,next=0;
    winner(x,x.objectBytes,(owner,key)=>{
      if(owner===x.globals&&key==='count804361a0') {reads++;x.globals.count804361a0=count;}
      if(owner===x.scratch&&key==='1') next++;
    });
    equal(reads,1,'signed count is read at first loop condition');equal(next,0,`signed count ${count} skips next candidate`);
  }
  {
    const x=setup(make),second=extra(x,3),third=extra(x,1);let counts=0;
    x.scratch[1]=second.id;x.scratch[2]=third.id;
    winner(x,third.bytes,(owner,key)=>{
      if(owner===x.globals&&key==='count804361a0') {counts++;x.globals.count804361a0=counts===1?2:3;}
    });
    equal(counts,3,'growth is observed by each fresh loop-condition reload');
  }
  {
    const x=setup(make,2);let counts=0,third=0;
    winner(x,x.nextObjectBytes,(owner,key)=>{
      if(owner===x.globals&&key==='count804361a0') {counts++;x.globals.count804361a0=counts===1?3:2;}
      if(owner===x.scratch&&key==='2') third++;
    });
    equal(counts,2,'shrink occurs after exactly one later distance');equal(third,0,'shrunk loop never reads absent next pointer');
  }
  for(const value of [-1,0x100000000,1.5,undefined,NaN]) {
    const x=setup(make);let hit=false,next=0;
    observe(()=>rejects(()=>x.targetDispatch.dispatchActor(x.actor),'count804361a0'),afterProjection(x,(owner,key)=>{
      if(!hit&&owner===x.globals&&key==='count804361a0') {hit=true;Reflect.set(x.globals,'count804361a0',value);}
      if(owner===x.scratch&&key==='1') next++;
    }));
    check(hit,'malformed count reached only after initial distance');equal(next,0,'bad count precedes next scratch load');projected(x);
  }
  for(const pointer of [null,Symbol('unregistered next OBJECT')]) {
    const x=setup(make,2);let changed=false,stack=0;
    observe(()=>rejects(()=>x.targetDispatch.dispatchActor(x.actor),pointer===null?'null':'unknown'),afterProjection(x,(owner,key)=>{
      if(owner===x.scratch&&key==='1') {changed=true;x.scratch[1]=pointer;}
      if(changed&&owner===x.stack&&axes.includes(key as typeof axes[number])) stack++;
    }));
    equal(stack,2,'next unknown/null pointer waits for second call A.y/A.z loads');projected(x);
  }
  {
    const x=setup(make);for(let index=1;index<4096;index++) x.scratch[index]=x.child;
    let counts=0,forbidden=0;
    observe(()=>rejects(()=>x.targetDispatch.dispatchActor(x.actor),'4096'),afterProjection(x,(owner,key)=>{
      if(owner===x.globals&&key==='count804361a0') {counts++;x.globals.count804361a0=4097;}
      if(owner===x.scratch&&key==='4096') forbidden++;
    }));
    equal(counts,4096,'host bound applies at reached index4096, not to positive source count4097');
    equal(forbidden,0,'host bound refuses before nonexistent indexed pointer descriptor');projected(x,x.child);closed(x);
  }
}

function selectedPointerFaultTests(make: Make): void {
  for(const kind of ['missing','accessor','unknown'] as const) {
    const x=setup(make,2);let hit=false,invoked=0,distanceLoads=0;
    observe(()=>rejects(()=>x.targetDispatch.dispatchActor(x.actor),kind==='unknown'?'opaque identity':'own data'),afterProjection(x,(owner,key)=>{
      if(owner===x.nextObjectBytes&&key==='100') distanceLoads++;
      if(!hit&&owner===x.nextObjectBytes&&key==='32') {
        hit=true;
        if(kind==='unknown') for(let i=0x20;i<0x24;i++) x.nextObjectBytes[i]=255;
        else if(kind==='missing') Reflect.deleteProperty(x.nextObjectBytes,'32');
        else Object.defineProperty(x.nextObjectBytes,'32',{get() {invoked++;return 0;},configurable:true});
      }
    }));
    check(hit,'selected OBJECT+20 fault is reached');equal(distanceLoads,1,'selected target pointer fault follows complete nearest distance');
    equal(invoked,0,'selected target pointer byte accessor is not invoked');projected(x);closed(x);
  }
  for(const kind of ['number','missing','accessor'] as const) {
    const x=setup(make,2);let hit=false,invoked=0,reads=0;
    observe(()=>rejects(()=>x.targetDispatch.dispatchActor(x.actor),kind==='number'?'pointer':'own data'),afterProjection(x,(owner,key)=>{
      if(!hit&&owner===x.scratch&&key==='1') {
        hit=true;
        if(kind==='number') Reflect.set(x.scratch,'1',0);
        else if(kind==='missing') Reflect.deleteProperty(x.scratch,'1');
        else Object.defineProperty(x.scratch,'1',{get() {invoked++;return x.nextChild;},configurable:true});
      }
      if(hit&&owner===x.stack&&axes.includes(key as typeof axes[number])) reads++;
    }));
    check(hit,'malformed later scratch pointer reached');equal(reads,0,'malformed pointer representation precedes next A loads');
    equal(invoked,0,'scratch pointer accessor is never evaluated');projected(x);closed(x);
  }
}
function profileAndOwnerTests(make: Make): void {
  for(const kind of ['missing','accessor'] as const) {
    const x=setup(make);let invoked=0,reads=0;
    if(kind==='missing') Reflect.deleteProperty(x.processor,'gqr0');
    else Object.defineProperty(x.processor,'gqr0',{get() {invoked++;return 0;},configurable:true});
    observe(()=>rejects(()=>x.targetDispatch.dispatchActor(x.actor),'own data'),afterProjection(x,(owner,key)=>{
      if(owner===x.stack&&axes.includes(key as typeof axes[number])) reads++;
    }));
    equal(invoked,0,'processor field accessor is never invoked');equal(reads,0,'bad GQR0 descriptor precedes first A load');projected(x);closed(x);
  }
  for(const value of [1,0x10000,0xffffffff,-1,NaN,undefined]) {
    const x=setup(make);Reflect.set(x.processor,'gqr0',value);let stack=0;
    observe(()=>rejects(()=>x.targetDispatch.dispatchActor(x.actor),typeof value==='number'&&Number.isInteger(value)&&value>=0?'GQR0':'gqr0'),afterProjection(x,(owner,key)=>{
      if(owner===x.stack&&axes.includes(key as typeof axes[number])) stack++;
    }));
    equal(stack,0,'unsupported GQR0 refuses before first paired source read');projected(x);
  }
  for(const point of ['first-y','first-b','second-a','second-b','next-call'] as const) {
    const x=setup(make,2);let hit=false;
    observe(()=>rejects(()=>x.targetDispatch.dispatchActor(x.actor),'GQR0'),afterProjection(x,(owner,key)=>{
      if(!hit&&(point==='first-y'?owner===x.stack&&key==='y':point==='first-b'?owner===x.objectBytes&&key==='104':
        point==='second-a'?owner===x.stack&&key==='x':point==='second-b'?owner===x.objectBytes&&key==='100':owner===x.scratch&&key==='1')) {
        hit=true;x.processor.gqr0=1;
      }
    }));
    check(hit,`profile mutation reached ${point}`);unchanged(x);closed(x);
  }
  {
    const x=setup(make,2),replacement={x:100,y:100,z:100};let changed=false,reads=0;
    winner(x,x.nextObjectBytes,(owner,key)=>{
      if(!changed&&owner===x.scratch&&key==='1') {changed=true;x.sources.projectionStack=replacement;}
      if(owner===replacement&&axes.includes(key as typeof axes[number])) reads++;
    });
    check(changed,'declared stack replacement reached later call');equal(reads,0,'captured A address does not reload stack ingress');
    equal(replacement.x,100,'unused replacement stack remains untouched');projected(x);
  }
  {
    const x=setup(make,2);let changed=false;
    observe(()=>rejects(()=>x.targetDispatch.dispatchActor(x.actor),'owner changed'),afterProjection(x,(owner,key)=>{
      if(!changed&&owner===x.scratch&&key==='1') {changed=true;Reflect.set(x.rootSources,'processor',{gqr0:0});}
    }));
    check(changed,'profile owner replacement reached later call');projected(x);closed(x);
  }
  for(const alias of ['stack','object','actual','globals','list','scratch'] as const) {
    const x=setup(make),owner=alias==='stack'?x.stack:alias==='object'?x.objectBytes:alias==='actual'?x.sourceActor:
      alias==='globals'?x.globals:alias==='list'?x.list:x.scratch;
    Reflect.set(owner,'gqr0',0);Reflect.set(x.rootSources,'processor',owner);
    rejects(()=>x.targetDispatch.dispatchActor(x.actor),'alias');unchanged(x);closed(x);
  }
  for(const shadow of ['source','actual','object']) {
    const x=setup(make);Reflect.set(shadow==='source'?x.sources:shadow==='actual'?x.sourceActor:x.objectBytes,'gqr0',1);
    finish(x);projected(x);
  }
}

type Point='profile'|'a-y'|'a-z'|'b-y'|'b-z'|'a-x'|'a-y2'|'b-x'|'b-y2'|'count'|'next'|'winner';
const points: readonly Point[]=['profile','a-y','a-z','b-y','b-z','a-x','a-y2','b-x','b-y2','count','next','winner'];
function detector(x: Fixture,point: Point) {
  let yA=0,yB=0;
  return (owner: object,key: PropertyKey): boolean=>{
    if(owner===x.stack&&key==='y') yA++;
    if(owner===x.objectBytes&&key==='104') yB++;
    return point==='profile'?owner===x.processor&&key==='gqr0':point==='a-y'?owner===x.stack&&key==='y'&&yA===1:
      point==='a-y2'?owner===x.stack&&key==='y'&&yA===2:point==='a-z'?owner===x.stack&&key==='z':
        point==='a-x'?owner===x.stack&&key==='x':point==='b-y'?owner===x.objectBytes&&key==='104'&&yB===1:
          point==='b-y2'?owner===x.objectBytes&&key==='104'&&yB===2:point==='b-z'?owner===x.objectBytes&&key==='108':
            point==='b-x'?owner===x.objectBytes&&key==='100':point==='count'?owner===x.globals&&key==='count804361a0':
              point==='next'?owner===x.scratch&&key==='1':owner===x.nextObjectBytes&&key==='32';
  };
}
function interruptionTests(make: Make): void {
  for(const kind of ['reentry','candidate','caller'] as const) for(const point of points) for(const phase of ['before','after'] as const) {
    const x=setup(make,2),hit=detector(x,point);let entered=false;
    if(kind==='candidate') x.control.bindActualActor(x.target,x.movement);

    const inject=afterProjection(x,(owner,key)=>{
      if(!entered&&hit(owner,key)) {
        entered=true;
        if(kind==='reentry') rejects(()=>x.targetDispatch.dispatchActor(x.actor),'same-runtime reentry');
        else if(kind==='candidate') {
          x.control.getActorBinding(x.target).activeMask579=256;
          rejects(()=>x.control.update(x.target,1),'activeMask579');
          check(hasIncompleteSourceActorDoubleLifecycle(x.targetActor),'real candidate stream failure closes candidate');
        } else {
          x.control.getActorBinding(x.actor).activeMask579=256;
          rejects(()=>x.control.update(x.actor,1),'activeMask579');
          check(hasIncompleteSourceActorDoubleLifecycle(x.sourceActor),'real caller stream failure closes caller');
        }
      }
    });
    observe(()=>rejects(()=>x.targetDispatch.dispatchActor(x.actor),kind==='reentry'?'caught same-runtime reentry':'incomplete'),
      phase==='before'?inject:()=>{},phase==='after'?inject:undefined);
    check(entered,`${kind} ${phase} interruption reaches ${point}`);projected(x);closed(x);
  }
}
function acceptedCandidateClosureTests(make: Make): void {
  const x=setup(make,2);x.list[1]=null;x.control.bindActualActor(x.target,x.movement);let entered=false,objectLoads=0;
  observe(()=>rejects(()=>x.targetDispatch.dispatchActor(x.actor),'incomplete'),afterProjection(x,(owner,key)=>{
    if(!entered&&owner===x.stack&&key==='y') {
      entered=true;x.control.getActorBinding(x.target).activeMask579=256;
      rejects(()=>x.control.update(x.target,1),'activeMask579');
    }
    if(owner===x.objectBytes&&Number(key)>=0x64&&Number(key)<0x70) objectLoads++;
  }));
  check(entered,'accepted target closes after following null list word');equal(objectLoads,0,'all accepted actors remain closure witnesses during distance');
  equal(x.globals.count804361a0,1,'later null candidate did not erase accepted scratch entry');projected(x);closed(x);
}
function outerTests(make: Make): void {
  const x=setup(make,2),frame=outer(x);let distance=0,selected=false;
  observe(()=>rejects(()=>frame.runFrame(),'8006b9c4'),(owner,key)=>{
    if(owner===x.targetPreparation&&key==='targetDispatch') selected=true;
    if(selected&&owner===x.objectBytes&&key==='100') distance++;
  });
  equal(distance,1,'genuine outer target dispatch reaches initial OBJECT X load');
  equal(x.massPreparation.orderCount.count80436260,6,'distance follows complete genuine mass ordering');
  equal(x.massHost.sourceArrowMass204,1200,'distance preserves actual mass update');
  for(const key of ['byte58a','byte58b','byte58c','byte58d','byte7d3'] as const)
    equal(x.sourceActor[key],0,'distance follows actual target preparation clears');
  projected(x);closed(x);rejects(()=>frame.runFrame(),'permanently incomplete');
  for(const run of [()=>x.scheduler.runGroup(9),()=>x.scheduler.runSlots(8),()=>x.scheduler.runWrapper(8)]) rejects(run,'exclusively owned');
  rejects(()=>x.root.dispatchStoredRoot(x.child),'exclusively owned');
  rejects(()=>x.projectiles.spawn(x.actor,1),'incomplete');rejects(()=>x.hits.registerHit(x.child,1),'incomplete');
}

export function runActorTargetDistanceSelfTests(make: Make): void {
  orderTests(make);liveAndSelectionTests(make);arithmeticAndFaultTests(make);
  profileAndOwnerTests(make);selectedPointerFaultTests(make);interruptionTests(make);acceptedCandidateClosureTests(make);outerTests(make);liveCountTests(make);
  console.log('[actor-target-distance] PASS: genuine8020bc88 paired load and finite f32 arithmetic order, live BE OBJECT/stack repeated Y reads and shared processor, signed fresh loop counts/growth/shrink/host bound, nearest and later ties with captured original pointers, late selected OBJECT+20 null/nonnull boundaries, faults/aliases/reentry/independently closed caller and candidate, real outer integration; explicit synthetic offline inputs only, no final target stores or completed-frame/console/full-game claim');
}
