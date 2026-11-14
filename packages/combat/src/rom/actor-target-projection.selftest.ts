import {createActorTargetCandidatesTestFixture} from './actor-target-candidates.selftest.js';
import {createSourceBattleOuterFrameRuntime,type SourceBattleOuterFrameSources} from './battle-outer-frame.js';
import {hasIncompleteSourceActorDoubleLifecycle,isSourceActorDoubleFrameClaimed} from './actor-double-prehook.js';
import {requireSourceObjectSchedulerSnapshot} from './source-object-scheduler.js';
import {createSourceActorWorldMatrixRuntime} from './actor-world-matrix.js';
import type {createBattleTargetPreparationTestFixture} from './attached-setup-animation.selftest.js';

/** Synthetic ingress on the existing genuine allocator, descriptor metadata and
 * matrix owners. There is no replacement callee, nearest-target answer, second
 * descriptor or OBJECT+64 representation. The real distance call is a boundary. */
type Make=typeof createBattleTargetPreparationTestFixture;
type Joined=ReturnType<typeof createActorTargetCandidatesTestFixture>;
type Stack={x:number;y:number;z:number};
const axes=['x','y','z'] as const,lanes=[3,7,11] as const,initial=[91,92,93] as const;
function check(ok: boolean,why: string): void {if(!ok) throw Error(`[actor-target-projection-test] ${why}`);}
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
function setup(make: Make,half=1,lifecycle=0) {
  const x=createActorTargetCandidatesTestFixture(make,half,lifecycle),stack: Stack={x:91,y:92,z:93};
  x.sources.projectionStack=stack;
  const mappingActor=x.mapping.getActor(x.actor),slots=x.world.getStorage(x.actor).matrices8d4;
  const matrix=x.matrices.getMatrix(slots[1]!);
  equal(matrix,x.worldMatrix,'selector1 is the pre-existing real world matrix');
  equal(x.attributes.getDescriptorBinding(mappingActor.descriptor4b0!),x.scalarDescriptor,'metadata belongs to the existing attribute descriptor');
  x.scalarDescriptor.byte10=1;
  matrix[3]=101;matrix[7]=-202;matrix[11]=303;
  return Object.assign(x,{stack,mappingActor,slots,matrix});
}
type Projection=ReturnType<typeof setup>;
function boundary(x: Joined): void {
  const message=rejects(()=>x.targetDispatch.dispatchActor(x.actor),'8006b968');
  check(message.includes('8020bc88'),'projection stops at the actual distance-call boundary');
}
function closed(x: Joined): void {
  check(hasIncompleteSourceActorDoubleLifecycle(x.sourceActor),'projection failure closes the actual caller');
  rejects(()=>x.targetDispatch.dispatchActor(x.actor),'incomplete');
  rejects(()=>x.allocator.assertActorComplete(x.actor),'incomplete');
}
function prefix(x: Projection,completed: number,values: readonly number[]=[101,-202,303]): void {
  for(let i=0;i<3;i++) equal(x.stack[axes[i]!],i<completed?values[i]:initial[i],`only ${completed} completed stack stores survive (${axes[i]})`);
  equal(x.globals.count804361a0,1,'projection failures retain candidate increment');
  equal(x.scratch[7],x.actor,'projection preserves unused scratch tail');
}
function outer(x: Joined) {
  const sources: SourceBattleOuterFrameSources={scheduler:x.scheduler,systemGlobals:x.systemGlobals,
    massPreparation:x.massPreparation,targetPreparation:x.targetPreparation};
  return createSourceBattleOuterFrameRuntime(sources);
}

function boundaryAndOrderTests(make: Make): void {
  {
    const x=createActorTargetCandidatesTestFixture(make);let descriptor=0;
    observe(()=>rejects(()=>x.targetDispatch.dispatchActor(x.actor),'8006b924'),(owner,key)=>{
      if(owner===x.scalarDescriptor&&key==='byte10') descriptor++;
    });
    equal(descriptor,0,'absent optional projection ingress preserves old positive-candidate boundary');
    equal(x.globals.count804361a0,1,'old boundary retains genuine scan increment');
    equal(x.scratch[0],x.child,'old boundary retains original OBJECT pointer');
  }
  for(const branch of ['zero-half','rejected','nonzero73f','inactive'] as const) {
    const x=setup(make,branch==='zero-half'?0:1,branch==='rejected'?2:0);let getter=0,byte=0;
    if(branch==='nonzero73f') x.sourceActor.housekeeping73f=1;
    if(branch==='inactive') x.sourceActor.active0=0;
    Object.defineProperty(x.sources,'projectionStack',{get() {getter++;throw Error('unreached stack');},configurable:true});
    observe(()=>x.targetDispatch.dispatchActor(x.actor),(owner,key)=>{if(owner===x.scalarDescriptor&&key==='byte10') byte++;});
    equal(getter,0,`${branch} never invokes projection ingress getter`);equal(byte,0,`${branch} never reads projection metadata`);
    check(!x.targetDispatch.getRetainedStorageOwners().includes(x.stack),`${branch} does not claim unreached stack`);
  }
  {
    const x=setup(make),events: string[]=[],claimed=isSourceActorDoubleFrameClaimed(x.sourceActor);
    let final=false,scratch=0,work=0,object64=0;
    const attached=x.joints.getBinding(x.joint).aobj7c,matrix=[...x.matrix];
    const target504=x.admissionState.pointer504,target508=x.admissionState.pointer508;
    observe(()=>boundary(x),(owner,key)=>{
      if(owner===x.scratch&&key==='0') {scratch++;if(scratch===2) events.push('scratch0');}
      if(owner===x.scalarDescriptor&&key==='byte10') {final=true;events.push('byte10');}
      if(owner===x.mappingActor&&key==='descriptor4b0') events.push('descriptor4b0');
      if(owner===x.slots&&key==='1') events.push('matrix1');
      if(owner===x.matrix&&lanes.some(lane=>String(lane)===key)) events.push(`lane${String(key)}`);
      if(owner===x.stack&&axes.some(axis=>axis===key)) events.push(`stack.${String(key)}`);
      if(owner===x.groups || owner===x.matchGlobals&&['maskD1','maskD2'].includes(String(key))) work++;
      if(final&&owner===x.objectBytes&&Number(key)>=0x64&&Number(key)<0x70) object64++;
    });
    equal(events.join(','),'descriptor4b0,byte10,scratch0,matrix1,lane3,stack.x,lane7,stack.y,lane11,stack.z',
      'single descriptor/byte capture, fresh scratch read, real matrix lookup and alternating lane/store schedule');
    prefix(x,3);equal(scratch,2,'one append and one fresh first-candidate pointer load');
    equal(work,0,'direct projection performs no scheduler mask/group work');
    equal(object64,0,'pointer arithmetic before the call never dereferences OBJECT+64');
    equal(x.joints.getBinding(x.joint).aobj7c,attached,'projection never advances attached animation');
    matrix.forEach((value,i)=>equal(x.matrix[i],value,'projection never rebuilds matrix'));
    equal(x.admissionState.pointer504,target504,'projection never selects nearest target504');
    equal(x.admissionState.pointer508,target508,'projection never selects nearest target508');
    equal(x.sourceActor.byte502,0,'projection does not invent target-state progress');
    equal(isSourceActorDoubleFrameClaimed(x.sourceActor),claimed,'projection does not create a frame claim');
    rejects(()=>requireSourceObjectSchedulerSnapshot(x.scheduler,x.allocator,x.child),'private active');closed(x);
  }
}

function captureAndLiveTests(make: Make): void {
  for(const phase of ['before','after'] as const) {
    const x=setup(make);let changed=false;
    const change=(owner: object,key: PropertyKey): void=>{
      if(!changed&&owner===x.mappingActor&&key==='descriptor4b0') {changed=true;x.mappingActor.descriptor4b0=Symbol('unknown later descriptor');}
    };
    observe(()=>{if(phase==='after') boundary(x);else rejects(()=>x.targetDispatch.dispatchActor(x.actor),'descriptor');},
      phase==='before'?change:()=>{},phase==='after'?change:undefined);
    check(changed,`${phase} mapping pointer mutation occurred`);prefix(x,phase==='after'?3:0);
  }
  for(const phase of ['before','after'] as const) {
    const x=setup(make);let changed=false;
    const change=(owner: object,key: PropertyKey): void=>{
      if(!changed&&owner===x.scalarDescriptor&&key==='byte10') {changed=true;x.scalarDescriptor.byte10=255;}
    };
    observe(()=>{if(phase==='after') boundary(x);else rejects(()=>x.targetDispatch.dispatchActor(x.actor),'world matrix');},
      phase==='before'?change:()=>{},phase==='after'?change:undefined);
    prefix(x,phase==='after'?3:0);
  }
  for(const pointer of [null,Symbol('unknown OBJECT'),Symbol('another unknown OBJECT')]) {
    const x=setup(make);let changed=false;
    observe(()=>boundary(x),(owner,key)=>{
      if(owner===x.scalarDescriptor&&key==='byte10') {changed=true;x.scratch[0]=pointer;}
    });
    check(changed,'scratch word changed after completed append');equal(x.scratch[0],pointer,'fresh scratch word is not rewritten or resolved');prefix(x,3);
  }
  for(const phase of ['before','after'] as const) {
    const x=setup(make);let reads=0,changed=false;
    const change=(owner: object,key: PropertyKey): void=>{
      if(owner===x.scratch&&key==='0'&&++reads===2) {changed=true;Reflect.set(x.scratch,'0',7);}
    };
    let slots=0;
    observe(()=>{if(phase==='after') boundary(x);else rejects(()=>x.targetDispatch.dispatchActor(x.actor),'pointer');},
      (owner,key)=>{if(owner===x.slots&&key==='1') slots++;if(phase==='before') change(owner,key);},phase==='after'?change:undefined);
    check(changed,'fresh pointer descriptor mutation occurred');equal(slots,phase==='after'?1:0,'fresh pointer capture precedes matrix lookup');
    prefix(x,phase==='after'?3:0);
  }
  {
    const x=setup(make),seen: string[]=[];
    observe(()=>boundary(x),(owner,key)=>{
      if(owner===x.stack&&key==='x') {x.matrix[7]=404;seen.push('x');}
      if(owner===x.matrix&&key==='7') equal(x.stack.x,101,'X store completes before Y lane read');
      if(owner===x.stack&&key==='y') {x.matrix[11]=-505;seen.push('y');}
      if(owner===x.matrix&&key==='11') equal(x.stack.y,404,'Y store completes before Z lane read');
    });
    equal(seen.join(','),'x,y','each destination is admitted once');prefix(x,3,[101,404,-505]);
  }
  for(const phase of ['before','after'] as const) for(let index=0;index<3;index++) {
    const x=setup(make),lane=lanes[index]!,values=[101,-202,303];let changed=false;
    const change=(owner: object,key: PropertyKey): void=>{
      if(!changed&&owner===x.matrix&&key===String(lane)) {changed=true;x.matrix[lane]=707;}
    };
    observe(()=>boundary(x),phase==='before'?change:()=>{},phase==='after'?change:undefined);
    if(phase==='before') values[index]=707;
    prefix(x,3,values);
  }
  for(const point of ['byte10','lane7','lane11'] as const) {
    const x=setup(make),replacement: Stack={x:81,y:82,z:83};let changed=false;
    observe(()=>{
      if(point==='byte10') boundary(x);else rejects(()=>x.targetDispatch.dispatchActor(x.actor),'owner changed');
    },(owner,key)=>{
      if(!changed&&(point==='byte10'?owner===x.scalarDescriptor&&key==='byte10':owner===x.matrix&&key===point.slice(4))) {
        changed=true;x.sources.projectionStack=replacement;
      }
    });
    check(changed,'stack source replacement reached selected source load');
    if(point==='byte10') {
      prefix(x,0);axes.forEach((axis,i)=>equal(replacement[axis],[101,-202,303][i],'unreached declared owner may change before first store'));
      check(!x.targetDispatch.getRetainedStorageOwners().includes(x.stack),'unused original stack remains unclaimed');
    } else {
      prefix(x,point==='lane7'?1:2);axes.forEach((axis,i)=>equal(replacement[axis],[81,82,83][i],'late replacement stack is untouched'));
    }
  }
}

function scalarAndIndexTests(make: Make): void {
  for(const selector of [0,1,11]) {
    const x=setup(make);x.scalarDescriptor.byte10=selector;
    const row=x.matrices.getMatrix(x.slots[selector]!);row[3]=selector+11;row[7]=selector+22;row[11]=selector+33;
    boundary(x);prefix(x,3,[selector+11,selector+22,selector+33]);
  }
  for(const raw of [12,127,128,129,254,255]) {
    const x=setup(make);x.scalarDescriptor.byte10=raw;let scratch=0,lanesRead=0,stackRead=0;
    observe(()=>rejects(()=>x.targetDispatch.dispatchActor(x.actor),'world matrix'),(owner,key)=>{
      if(owner===x.scratch&&key==='0') scratch++;
      if(owner===x.matrix&&lanes.some(lane=>String(lane)===key)) lanesRead++;
      if(owner===x.stack&&axes.some(axis=>axis===key)) stackRead++;
    });
    equal(scratch,2,`signed index ${raw<<24>>24} refusal follows fresh scratch load`);
    equal(lanesRead,0,'out-of-storage index does not read a matrix lane');equal(stackRead,0,'out-of-storage index does not admit stack');prefix(x,0);
  }
  for(const value of [-1,256,1.5,NaN,Infinity,undefined,'1',null]) {
    const x=setup(make);Reflect.set(x.scalarDescriptor,'byte10',value);let scratch=0,slots=0;
    observe(()=>rejects(()=>x.targetDispatch.dispatchActor(x.actor),'byte10'),(owner,key)=>{
      if(owner===x.scratch&&key==='0') scratch++;if(owner===x.slots) slots++;
    });
    equal(scratch,1,'malformed raw byte refuses before first-candidate reload');equal(slots,0,'malformed raw byte refuses before matrix lookup');prefix(x,0);
  }
  for(const value of [null,0,undefined,{},Symbol('unbound descriptor')]) {
    const x=setup(make);Reflect.set(x.mappingActor,'descriptor4b0',value);let bytes=0;
    observe(()=>rejects(()=>x.targetDispatch.dispatchActor(x.actor),'descriptor'),(owner,key)=>{if(owner===x.scalarDescriptor&&key==='byte10') bytes++;});
    equal(bytes,0,'invalid mapping pointer never reads old descriptor metadata');prefix(x,0);
  }
  for(const values of [[-0,0,-0],[0,-0,0],[Math.fround(1e-40),Math.fround(-1e-40),Math.fround(3.4e38)]]) {
    const x=setup(make);lanes.forEach((lane,i)=>{x.matrix[lane]=values[i]!;});
    // Source loads do not require writable descriptor or matrix input cells.
    Object.defineProperty(x.scalarDescriptor,'byte10',{writable:false});
    lanes.forEach(lane=>Object.defineProperty(x.matrix,String(lane),{writable:false}));
    boundary(x);prefix(x,3,values);
  }
  for(let index=0;index<3;index++) for(const value of [NaN,Infinity,-Infinity,0.1,1e40,undefined,'1']) {
    const x=setup(make);Reflect.set(x.matrix,String(lanes[index]!),value);let stackReads=0;
    observe(()=>rejects(()=>x.targetDispatch.dispatchActor(x.actor),'float32'),(owner,key)=>{
      if(owner===x.stack&&axes.some(axis=>axis===key)) stackReads++;
    });
    equal(stackReads,index,'bad source lane refuses before corresponding destination admission');prefix(x,index);closed(x);
  }
}

function lazyStackAndPointerTests(make: Make): void {
  for(const kind of ['number','missing','accessor'] as const) {
    const x=setup(make);let invoked=0,slots=0;
    x.scalarDescriptor.byte10=255;
    observe(()=>rejects(()=>x.targetDispatch.dispatchActor(x.actor),kind==='number'?'pointer':'own data'),(owner,key)=>{
      if(owner===x.scalarDescriptor&&key==='byte10') {
        if(kind==='number') Reflect.set(x.scratch,'0',0);
        if(kind==='missing') Reflect.deleteProperty(x.scratch,'0');
        if(kind==='accessor') Object.defineProperty(x.scratch,'0',{get() {invoked++;return x.child;},configurable:true});
      }
      if(owner===x.slots) slots++;
    });
    equal(invoked,0,'fresh scratch getter is never called');equal(slots,0,'invalid first pointer wins over out-of-range matrix index');prefix(x,0);
  }
  for(const kind of ['null','number','undefined','symbol','function','array','promise','typed-array','accessor'] as const) {
    const x=setup(make);let invoked=0,xReads=0;
    if(kind==='accessor') Object.defineProperty(x.sources,'projectionStack',{get() {invoked++;return x.stack;},configurable:true});
    else Reflect.set(x.sources,'projectionStack',kind==='null'?null:kind==='number'?1:kind==='undefined'?undefined:
      kind==='symbol'?Symbol('not stack'):kind==='function'?()=>x.stack:kind==='array'?[1,2,3]:kind==='promise'?Promise.resolve(x.stack):new Float32Array(3));
    observe(()=>rejects(()=>x.targetDispatch.dispatchActor(x.actor),'projection'),(owner,key)=>{if(owner===x.matrix&&key==='3') xReads++;});
    equal(invoked,0,'projection ingress accessor is never evaluated');equal(xReads,1,'invalid stack owner is lazy until after X source read');prefix(x,0);
  }
  for(let index=0;index<3;index++) for(const kind of ['missing','accessor','readonly','inherited'] as const) {
    const x=setup(make),axis=axes[index]!;let invoked=0,sourceReads=0;
    if(kind==='missing'||kind==='inherited') Reflect.deleteProperty(x.stack,axis);
    if(kind==='inherited') Object.setPrototypeOf(x.stack,{[axis]:-1});
    if(kind==='accessor') Object.defineProperty(x.stack,axis,{get() {invoked++;return -1;},set() {invoked++;},configurable:true});
    if(kind==='readonly') Object.defineProperty(x.stack,axis,{writable:false});
    observe(()=>rejects(()=>x.targetDispatch.dispatchActor(x.actor),`${axis}:`),(owner,key)=>{
      if(owner===x.matrix&&lanes.some(lane=>String(lane)===key)) sourceReads++;
    });
    equal(invoked,0,'stack destination accessors are not evaluated');equal(sourceReads,index+1,'destination fault follows exactly its source load');
    for(let i=0;i<3;i++) if(i!==index) equal(x.stack[axes[i]!],i<index?[101,-202,303][i]:initial[i],'destination failure preserves completed prefix and untouched suffix');
    closed(x);
  }
  {
    const x=setup(make);Reflect.set(x.stack,'x',null);Reflect.set(x.stack,'y',Symbol('stale'));Reflect.set(x.stack,'z',NaN);
    boundary(x);prefix(x,3);
  }
  {
    const x=setup(make);x.matrix[3]=NaN;
    Object.defineProperty(x.sources,'projectionStack',{get() {throw Error('must stay lazy');},configurable:true});
    rejects(()=>x.targetDispatch.dispatchActor(x.actor),'float32');prefix(x,0);
  }
  {
    const x=setup(make);let xReads=0;
    observe(()=>rejects(()=>x.targetDispatch.dispatchActor(x.actor),'projectionStack: own data'),(owner,key)=>{
      if(owner===x.scalarDescriptor&&key==='byte10') Reflect.deleteProperty(x.sources,'projectionStack');
      if(owner===x.matrix&&key==='3') xReads++;
    });
    equal(xReads,1,'removed stack ingress is consumed only after X source read');prefix(x,0);
  }
}

function storageTests(make: Make): void {
  for(const role of ['candidateList1d7c','scratchCandidates2208'] as const)
    for(const storage of ['root','selected','last','copy114','copy1aa4','scratch'] as const) {
    const x=setup(make),owned=x.world.getStorage(x.actor);
    const id=storage==='root'?x.slots[0]!:storage==='selected'?x.slots[1]!:storage==='last'?x.slots.at(-1)!:owned[storage];
    const row=x.matrices.getMatrix(id),matrix=[...row];
    Reflect.set(x.sources,role,row);
    rejects(()=>x.targetDispatch.dispatchActor(x.actor),'alias');
    matrix.forEach((value,i)=>equal(row[i],value,`${role} cannot overwrite a retained ${storage} matrix lane`));
    equal(x.globals.count804361a0,role==='candidateList1d7c'?0:1,'matrix alias retains only completed source count writes');
    equal(x.scratch[0],null,'rejected matrix scratch alias never appends a pointer');
    axes.forEach((axis,i)=>equal(x.stack[axis],initial[i],'matrix list alias never reaches projection stores'));
    closed(x);
  }
  {
    const x=setup(make),identity=x.matrices.createMatrix(Array(12).fill(0)),row=x.matrices.getMatrix(identity);
    // This genuine matrix is not yet bound to any world. A null list word
    // admits it to the helper without selecting a candidate or closing caller.
    Reflect.set(row,'0',null);Reflect.set(x.sources,'candidateList1d7c',row);
    x.targetDispatch.dispatchActor(x.actor);equal(x.globals.count804361a0,0,'unbound matrix-shaped null list returns');
    row[0]=0;
    const later=createSourceActorWorldMatrixRuntime({mapping:x.mapping,feedback:x.feedback,matrices:x.matrices});
    const owned=x.world.getStorage(x.actor),matrices8d4=[...owned.matrices8d4];matrices8d4[1]=identity;
    rejects(()=>later.bindActor(x.actor,x.sourceActor,x.header,{...owned,matrices8d4}),'already claimed');
    rejects(()=>later.getWorldMatrix(x.actor,1),'unknown');
    equal(x.world.getWorldMatrix(x.actor,1),x.matrix,'failed later world bind cannot replace original matrix graph');
    check(!hasIncompleteSourceActorDoubleLifecycle(x.sourceActor),'metadata-only failed later bind does not fabricate a frame failure');
  }
  for(const alias of ['sources','table','globals','list','scratch','actual','candidate','mapping','metadata','matrix','world','position','aim','slot-records','slot-row'] as const) {
    const x=setup(make);
    const owner=alias==='sources'?x.sources:alias==='table'?x.dispatch39a0:alias==='globals'?x.globals:
      alias==='list'?x.list:alias==='scratch'?x.scratch:alias==='actual'?x.sourceActor:alias==='candidate'?x.targetActor:
        alias==='mapping'?x.mappingActor:alias==='metadata'?x.scalarDescriptor:alias==='matrix'?x.matrix:
          alias==='world'?x.header:alias==='position'?x.sourceActor.pos:alias==='aim'?x.sourceActor.aimOrigin518:
            alias==='slot-records'?x.slotRecords:x.slotRecords[0]!;
    Reflect.set(x.sources,'projectionStack',owner);let xReads=0;
    observe(()=>rejects(()=>x.targetDispatch.dispatchActor(x.actor),alias==='matrix'?'ordinary own-data':'alias'),(observed,key)=>{if(observed===x.matrix&&key==='3') xReads++;});
    equal(xReads,1,`${alias} stack alias is rejected only after X source read`);prefix(x,0);
  }
  for(const key of ['descriptor4b0','pointer4b0','byte10','active0','pointer504','count804361a0','lifecycle18']) {
    const x=setup(make);Object.assign(x.stack,{[key]:0});let xReads=0;
    observe(()=>rejects(()=>x.targetDispatch.dispatchActor(x.actor),'competing'),(owner,property)=>{if(owner===x.matrix&&property==='3') xReads++;});
    equal(xReads,1,`stack shadow ${key} admitted lazily`);prefix(x,0);
  }
  for(const location of ['source','actual','scratch','list'] as const) {
    const x=setup(make),owner=location==='source'?x.sources:location==='actual'?x.sourceActor:location==='scratch'?x.scratch:x.list;
    Object.assign(owner,{byte10:255});
    boundary(x);prefix(x,3);
    equal(x.scalarDescriptor.byte10,1,'unrelated byte10 names cannot override canonical descriptor metadata');
  }
  for(const field of ['targetStack','initializationStack','processor','displacement'] as const) {
    const x=setup(make);let invoked=0;
    const owner=field==='displacement'?{}:x.rootSources;
    Object.defineProperty(owner,field,{get() {invoked++;throw Error('metadata-only accessor');},configurable:true});
    if(field==='displacement') Reflect.set(x.rootSources,'targetStack',owner);
    boundary(x);prefix(x,3);equal(invoked,0,`unreached root ${field} accessor is never executed by ownership inventory`);
  }
  {
    const x=setup(make),y=setup(make);boundary(x);y.sources.projectionStack=x.stack;
    rejects(()=>y.targetDispatch.dispatchActor(y.actor),'already claimed');
    prefix(x,3);prefix(y,0);
  }
  for(const method of ['external','object','descriptor','slot-records','slot-row','slot-dispatch','scheduler-slots'] as const) {
    const x=setup(make);boundary(x);const id=Symbol('late projection storage alias');
    rejects(()=>{
      if(method==='external') x.allocator.registerExternal(id,x.stack);
      else if(method==='object') x.allocator.registerObject(id,x.stack as unknown as Record<number,number>);
      else if(method==='descriptor') x.allocator.registerDescriptor(id,x.stack as unknown as Record<number,number>);
      else if(method==='scheduler-slots') {Reflect.set(x.schedulerSources,'actorSlots',x.stack);x.scheduler.getActorSlotTable();}
      else {
        if(method==='slot-records') Reflect.set(x.slotStatusSources,'slotRecords',x.stack);
        if(method==='slot-row') Reflect.set(x.slotRecords,'0',x.stack);
        if(method==='slot-dispatch') {x.sourceActor.byte43d=0;Reflect.set(x.slotStatusSources,'dispatch3938',x.stack);}
        x.slotStatus.readSlot(0);
      }
    },'already claimed');
    prefix(x,3);
    if(['external','object','descriptor'].includes(method)) rejects(()=>x.allocator.getPointerTarget(id),'unknown');
  }
  for(const method of ['external','object','descriptor'] as const) {
    const x=setup(make),id=Symbol('previous pointer owner');
    if(method==='external') x.allocator.registerExternal(id,x.stack);
    if(method==='object') x.allocator.registerObject(id,x.stack as unknown as Record<number,number>);
    if(method==='descriptor') x.allocator.registerDescriptor(id,x.stack as unknown as Record<number,number>);
    rejects(()=>x.targetDispatch.dispatchActor(x.actor),'storage');prefix(x,0);
  }
  for(const declared of ['target-stack','displacement','initialization-stack','processor'] as const) {
    const x=setup(make);let xReads=0;
    if(declared==='displacement') Reflect.set(x.rootSources,'targetStack',{displacement:x.stack});
    else Reflect.set(x.rootSources,declared==='target-stack'?'targetStack':declared==='initialization-stack'?'initializationStack':'processor',x.stack);
    observe(()=>rejects(()=>x.targetDispatch.dispatchActor(x.actor),'alias'),(owner,key)=>{if(owner===x.matrix&&key==='3') xReads++;});
    equal(xReads,1,`declared root ${declared} owner is excluded only at reached stack store`);prefix(x,0);
  }
  for(const late of ['target-stack','displacement','initialization-stack'] as const) {
    const x=setup(make),y=make();boundary(x);
    if(late==='initialization-stack') {
      Object.assign(x.stack,{rotationX:y.matrices.createMatrix(Array(12).fill(1)),rotationY:y.matrices.createMatrix(Array(12).fill(2))});
      Reflect.set(y.rootSources,'initializationStack',x.stack);
    } else {
      y.admissionState.pointerc8={};Reflect.set(y.rootSources,'processor',y.actionSources.processor);
      if(late==='target-stack') {Object.assign(x.stack,{displacement:{x:1,y:2,z:3}});Reflect.set(y.rootSources,'targetStack',x.stack);}
      else Reflect.set(y.rootSources,'targetStack',{displacement:x.stack});
    }
    rejects(()=>y.root.dispatchStoredRoot(y.child),'already claimed');prefix(x,3);
    check(hasIncompleteSourceActorDoubleLifecycle(y.sourceActor),'late root alias failure closes its real caller');
  }
}

type Point='descriptor'|'byte10'|'scratch'|'matrix-slot'|'lane3'|'x'|'lane7'|'y'|'lane11'|'z';
const points: readonly Point[]=['descriptor','byte10','scratch','matrix-slot','lane3','x','lane7','y','lane11','z'];
function pointDetector(x: Projection,point: Point): (owner: object,key: PropertyKey)=>boolean {
  let scratch=0;
  return (owner,key)=>{
    if(owner===x.scratch&&key==='0') scratch++;
    return point==='descriptor'?owner===x.mappingActor&&key==='descriptor4b0':
      point==='byte10'?owner===x.scalarDescriptor&&key==='byte10':
        point==='scratch'?owner===x.scratch&&key==='0'&&scratch===2:
          point==='matrix-slot'?owner===x.slots&&key==='1':
            point.startsWith('lane')?owner===x.matrix&&key===point.slice(4):owner===x.stack&&key===point;
  };
}
function completedBefore(point: Point): number {
  return point==='lane11'||point==='z'?2:point==='lane7'||point==='y'?1:0;
}
function candidateFailure(x: Joined): ()=>void {
  x.control.bindActualActor(x.target,x.movement);
  return ()=>{
    x.control.getActorBinding(x.target).activeMask579=256;
    rejects(()=>x.control.update(x.target,1),'activeMask579');
    check(hasIncompleteSourceActorDoubleLifecycle(x.targetActor),'real candidate stream fault closes candidate');
  };
}
function interruptionTests(make: Make): void {
  for(const kind of ['reentry','candidate','caller'] as const) for(const point of points) for(const phase of ['before','after'] as const) {
    const x=setup(make),hit=pointDetector(x,point);let entered=false;
    const failCandidate=kind==='candidate'?candidateFailure(x):undefined;
    let frame: ReturnType<typeof outer>|undefined;
    if(kind==='caller') {Reflect.deleteProperty(x.targetPreparation,'slotStatus');frame=outer(x);}
    const inject=(owner: object,key: PropertyKey): void=>{
      if(!entered&&hit(owner,key)) {
        entered=true;
        if(kind==='reentry') rejects(()=>x.targetDispatch.dispatchActor(x.actor),'same-runtime reentry');
        else if(kind==='candidate') failCandidate!();
        else rejects(()=>frame!.runFrame(),'mandatory8006b450');
      }
    };
    observe(()=>rejects(()=>x.targetDispatch.dispatchActor(x.actor),kind==='reentry'?'caught same-runtime reentry':'incomplete'),
      phase==='before'?inject:()=>{},phase==='after'?inject:undefined);
    check(entered,`${kind} ${phase} interruption reached ${point}`);prefix(x,completedBefore(point));closed(x);
    if(frame) rejects(()=>frame!.runFrame(),'permanently incomplete');
  }
}

function outerTests(make: Make): void {
  const x=setup(make),frame=outer(x);let selected=false,bytes=0;
  observe(()=>rejects(()=>frame.runFrame(),'8006b968'),(owner,key)=>{
    if(owner===x.targetPreparation&&key==='targetDispatch') selected=true;
    if(selected&&owner===x.scalarDescriptor&&key==='byte10') bytes++;
  });
  equal(bytes,1,'actual outer target dispatch reaches exactly one projection byte read');prefix(x,3);
  equal(x.massPreparation.orderCount.count80436260,6,'projection follows genuine complete mass ordering');
  equal(x.massHost.sourceArrowMass204,1200,'projection retains genuine mass update');
  for(const key of ['byte58a','byte58b','byte58c','byte58d','byte7d3'] as const)
    equal(x.sourceActor[key],0,'projection follows genuine target preparation clears');
  closed(x);rejects(()=>frame.runFrame(),'permanently incomplete');
  for(const run of [()=>x.scheduler.runGroup(9),()=>x.scheduler.runSlots(8),()=>x.scheduler.runWrapper(8)]) rejects(run,'exclusively owned');
  rejects(()=>x.root.dispatchStoredRoot(x.child),'exclusively owned');
  rejects(()=>x.projectiles.spawn(x.actor,1),'incomplete');rejects(()=>x.hits.registerHit(x.child,1),'incomplete');
}

export function runActorTargetProjectionSelfTests(make: Make): void {
  boundaryAndOrderTests(make);captureAndLiveTests(make);scalarAndIndexTests(make);lazyStackAndPointerTests(make);
  storageTests(make);interruptionTests(make);outerTests(make);
  console.log('[actor-target-projection] PASS: same canonical descriptor byte10 and retained real matrix rows; fresh captured first OBJECT pointer before signed index bounds, lazy ordered XYZ stack stores, exact finite f32/signed-zero and mutation-fault prefixes, aliases/storage reservations, caught reentry and independently closed caller/candidate guards, genuine outer integration; explicit synthetic offline inputs only, stop before actual8020bc88 at8006b968, no OBJECT+64 read, distance result, nearest target, matrix refresh or full-frame claim');
}
