import {createActorTargetCandidatesTestFixture} from './actor-target-candidates.selftest.js';
import {createSourceBattleOuterFrameRuntime,type SourceBattleOuterFrameSources} from './battle-outer-frame.js';
import {hasIncompleteSourceActorDoubleLifecycle,isSourceActorDoubleFrameClaimed} from './actor-double-prehook.js';
import {requireSourceObjectSchedulerSnapshot} from './source-object-scheduler.js';
import type {createBattleTargetPreparationTestFixture} from './attached-setup-animation.selftest.js';

/** Explicit offline operands on the genuine allocator/HIT/dispatcher graph.
 * The completed6b850 stores precede every main witness. Only the primary
 * SquareDistance call is newly reached; these fixtures leave the new threshold/destinations absent, so every frame
 * still refuses before distance stores, later actor or third target pass. */
type Make=typeof createBattleTargetPreparationTestFixture;
type Bytes=Partial<Record<number,number>>;
type Vector={x:number;y:number;z:number};
const axes=['x','y','z'] as const;
function check(ok:boolean,why:string):void {if(!ok) throw Error(`[actor-primary-distance-test] ${why}`);}
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
  const view=new DataView(new ArrayBuffer(4));view.setFloat32(0,value,false);
  for(let i=0;i<4;i++) bytes[offset+i]=view.getUint8(i);
}
function position(bytes:Bytes,x:number,y=0,z=0):void {float(bytes,0x64,x);float(bytes,0x68,y);float(bytes,0x6c,z);}
function setup(make:Make) {
  const x=createActorTargetCandidatesTestFixture(make),stack:Vector={x:91,y:92,z:93},vector:Vector={x:71,y:72,z:73};
  x.sources.projectionStack=stack;Reflect.set(x.rootSources,'processor',x.actionSources.processor);x.scalarDescriptor.byte10=1;
  const processor=x.actionSources.processor,pos=x.sourceActor.pos;
  const matrix=x.matrices.getMatrix(x.world.getStorage(x.actor).matrices8d4[1]!);
  matrix[3]=0;matrix[7]=0;matrix[11]=0;
  equal(x.hits.registerHit(x.child,1),1,'genuine HIT registration completes');
  const id=x.hitIds[0]!,bytes=x.hitBytes[0]!,descriptor=x.allocator.readPointer(id,0x28)!;
  const address=x.allocator.getInteriorAddress(descriptor)!;
  equal(address.base,x.hitTableIdentity,'actual HIT descriptor retains original registered byte owner');
  const table=x.hitBinding.pointer3fc;table[address.byteOffset+2]=2;table[address.byteOffset+3]=0;
  x.allocator.writePointer(id,0x20,x.target);position(bytes,5,6,7);
  x.list[0]=id;x.scratch[0]=null;Reflect.set(x.sourceActor,'lockTarget',vector);
  Object.assign(pos,{x:1,y:2,z:3});
  const outerSources:SourceBattleOuterFrameSources={scheduler:x.scheduler,systemGlobals:x.systemGlobals,
    massPreparation:x.massPreparation,targetPreparation:x.targetPreparation};
  const frame=createSourceBattleOuterFrameRuntime(outerSources);
  return Object.assign(x,{stack,vector,processor,pos,matrix,id,bytes,frame,outerSources});
}
type Fixture=ReturnType<typeof setup>;
/** The last genuine target-vector store admission starts this observation
 * window. All subsequent primary operands remain ordinary live source cells. */
function afterHelper(x:Fixture,visit:(owner:object,key:PropertyKey)=>void) {
  let reached=false;
  return (owner:object,key:PropertyKey):void=>{
    if(!reached) {if(owner===x.vector&&key==='z') reached=true;return;}
    visit(owner,key);
  };
}
function retained(x:Fixture):void {
  equal(x.sourceActor.byte502,1,'earlier helper state502 store survives');
  axes.forEach((axis,i)=>equal(x.vector[axis],[5,6,7][i],`earlier helper target ${axis} store survives`));
  axes.forEach(axis=>equal(x.stack[axis],0,`earlier projection ${axis} store survives`));
  equal(x.globals.count804361a0,1,'earlier candidate count survives');
  equal(x.scratch[0],x.id,'earlier selected original OBJECT pointer survives');
  equal(x.massPreparation.orderCount.count80436260,6,'genuine mass ordering precedes primary distance');
  equal(x.massHost.sourceArrowMass204,1200,'earlier mass update survives');
}
function closed(x:Fixture):void {
  check(hasIncompleteSourceActorDoubleLifecycle(x.sourceActor),'primary refusal closes actual caller');
  rejects(()=>x.frame.runFrame(),'permanently incomplete');
  rejects(()=>x.targetDispatch.dispatchActor(x.actor),'incomplete');
  rejects(()=>x.allocator.assertActorComplete(x.actor),'incomplete');
  for(const run of [()=>x.scheduler.runGroup(9),()=>x.scheduler.runSlots(8),()=>x.scheduler.runWrapper(8)])
    rejects(run,'exclusively owned');
  rejects(()=>x.root.dispatchStoredRoot(x.child),'exclusively owned');
  rejects(()=>requireSourceObjectSchedulerSnapshot(x.scheduler,x.allocator,x.child),'private active');
}
function finish(x:Fixture):void {rejects(()=>x.frame.runFrame(),'8006afb0');}
function rawKey(key:PropertyKey):boolean {return /^\d+$/.test(String(key))&&Number(key)>=0x64&&Number(key)<0x70;}

function branchAndOrderTests(make:Make):void {
  {
    const x=setup(make),events:string[]=[],claimed=isSourceActorDoubleFrameClaimed(x.sourceActor);
    let forbidden=0,profiles=0,p504=0,p508=0;
    let before:readonly {owner:object;fields:Record<string,PropertyDescriptor>}[]=[];
    observe(()=>finish(x),afterHelper(x,(owner,key)=>{
      if(owner===x.admissionState&&key==='pointer508') {
        events.push('508');p508++;
        before=[x.sourceActor,x.pos,x.bytes,x.admissionState,x.vector,x.stack,x.processor].map(owner=>
          ({owner,fields:Object.getOwnPropertyDescriptors(owner)}));
      }
      if(owner===x.admissionState&&key==='pointer504') {events.push('504');p504++;}
      if(owner===x.processor&&key==='gqr0') {events.push('gqr0');profiles++;}
      if(owner===x.pos&&axes.includes(key as typeof axes[number])) events.push(`a.${String(key)}`);
      if(owner===x.bytes&&rawKey(key)) events.push(`b.${Number(key).toString(16)}`);
      if(owner===x.physicalIdentities&&key==='1' || owner===x.slotTargets[1]&&key==='active0' ||
        owner===x.massPreparation&&key==='physicalBlock' || owner===x.groups ||
        owner===x.matchGlobals&&['maskD1','maskD2'].includes(String(key)) ||
        ['float80437658','float80437678'].includes(String(key)) ||
        owner===x.sourceActor&&['field758','field75c','distance758','distance75c','1880','1884'].includes(String(key))) forbidden++;
    }));
    equal(events.join(','),'508,504,gqr0,a.y,a.z,gqr0,b.68,b.69,b.6a,b.6b,b.6c,b.6d,b.6e,b.6f,gqr0,a.x,a.y,gqr0,b.64,b.65,b.66,b.67,b.68,b.69,b.6a,b.6b',
      'canonical508 then captured504 and four exact paired source loads');
    equal(profiles,4,'each primary paired load reads GQR0 freshly');equal(p504,1,'primary504 is captured once');
    equal(p508,1,'primary508 is read exactly once');equal(forbidden,1,'only the newly reached missing threshold load; no later actor/pass, scheduler or distance cell read');
    equal(isSourceActorDoubleFrameClaimed(x.sourceActor),claimed,'primary helper does not grant frame authority');
    equal(x.admissionState.pointer504,x.bytes,'original OBJECT504 store retained');
    equal(x.admissionState.pointer508,x.targetActor,'actual actor508 store retained');
    for(const {owner,fields} of before) {
      const after=Object.getOwnPropertyDescriptors(owner);
      equal(Object.keys(after).join(','),Object.keys(fields).join(','),'primary call creates no distance or other source cells');
      for(const [key,field] of Object.entries(fields)) equal(after[key]?.value,field.value,`primary source ${key} remains read-only`);
    }
    retained(x);closed(x);
  }
  {
    const x=setup(make);let selected=false,changed=false,primary=false,p504=0,profiles=0,scalars=0,constants=0;
    observe(()=>rejects(()=>x.frame.runFrame(),'horizontalDistance75c'),(owner,key)=>{
      if(owner===x.targetPreparation&&key==='targetDispatch') selected=true;
      if(selected&&!changed&&owner===x.admissionState&&key==='pointer504') {
        changed=true;x.allocator.writePointer(x.id,0x20,null);
      }
      if(!primary) {if(owner===x.vector&&key==='z') primary=true;return;}
      if(owner===x.admissionState&&key==='pointer504') p504++;
      if(['float80437658','float80437678'].includes(String(key))) constants++;
      if(owner===x.rootSources&&key==='processor' || owner===x.processor&&key==='gqr0') profiles++;
      if(owner===x.sourceActor&&key==='pos' || owner===x.pos&&axes.includes(key as typeof axes[number]) || owner===x.bytes&&rawKey(key)) scalars++;
    });
    check(changed,'genuine helper final actor reload changed to null');equal(x.admissionState.pointer508,null,'genuine helper stores null508');
    equal(p504,0,'null508 branches before504');equal(profiles,0,'null508 reads no processor profile');
    equal(scalars,0,'null508 reads no source position owner or coordinates');equal(constants,1,'null508 reads its one constant then refuses absent first destination');retained(x);closed(x);
  }
  {
    const x=setup(make),opaque={};let touched=0;
    Object.defineProperty(opaque,'pos',{get() {touched++;throw Error('opaque508 must never be dereferenced');}});
    observe(()=>finish(x),afterHelper(x,(owner,key)=>{
      if(owner===x.admissionState&&key==='pointer508') Reflect.set(x.admissionState,'pointer508',opaque);
      if(owner===opaque) touched++;
      if(owner===x.vector&&axes.includes(key as typeof axes[number]) || owner===x.targetActor&&key==='pos') touched++;
    }));
    equal(touched,0,'nonnull508 is only compared with null, not resolved, dereferenced, or used as A/B');retained(x);closed(x);
  }
}

function capturedAndLiveTests(make:Make):void {
  {
    const x=setup(make),other:Bytes={};let captured=false,p504=0,otherLoads=0;
    for(let i=0;i<0x70;i++) other[i]=0;
    x.allocator.registerObject(Symbol('different registered primary OBJECT'),other);position(other,NaN,NaN,NaN);
    observe(()=>finish(x),afterHelper(x,(owner,key)=>{
      if(owner===x.admissionState&&key==='pointer504') p504++;
      if(!captured&&owner===x.pos&&key==='y') {captured=true;x.admissionState.pointer504=other;}
      if(owner===other&&rawKey(key)) otherLoads++;
    }));
    equal(p504,1,'source504 never reloads after capture');equal(otherLoads,0,'later504 replacement does not retarget B');retained(x);closed(x);
  }
  for(const kind of ['null','unregistered','external','actor'] as const) {
    const x=setup(make),bad={},reads:string[]=[];let changed=false;
    if(kind==='external') x.allocator.registerExternal(Symbol('registered non-OBJECT'),bad);
    observe(()=>rejects(()=>x.frame.runFrame(),kind==='null'?'null':kind==='unregistered'?'registered':'object identity'),afterHelper(x,(owner,key)=>{
      if(!changed&&owner===x.admissionState&&key==='pointer504') {
        changed=true;x.admissionState.pointer504=kind==='null'?null:kind==='actor'?x.sourceActor:bad;
      }
      if(owner===x.pos&&axes.includes(key as typeof axes[number])) reads.push(String(key));
    }));
    equal(reads.join(','),'y,z',`${kind}504 refuses at first reached B load after A.y/A.z`);retained(x);closed(x);
  }
  for(const source of ['a','b'] as const) {
    const x=setup(make);let ys=0,xs=0;
    observe(()=>rejects(()=>x.frame.runFrame(),'float32'),afterHelper(x,(owner,key)=>{
      if(source==='a'&&owner===x.pos&&key==='y'&&++ys===2) x.pos.y=NaN;
      if(source==='b'&&owner===x.bytes&&key==='104'&&++ys===2) float(x.bytes,0x68,NaN);
      if(owner===x.pos&&key==='x') xs++;
    }));
    equal(ys,2,`${source}.y is reloaded, not snapshotted`);equal(xs,1,'fresh Y failure follows second A pair start');retained(x);closed(x);
  }
  for(const phase of ['before','after'] as const) {
    const x=setup(make);let hit=false;
    const mutate=afterHelper(x,(owner,key)=>{
      if(!hit&&owner===x.bytes&&key==='100') {hit=true;float(x.bytes,0x64,Infinity);}
    });
    // The old first byte of5 is0x40. Replacing only later bytes yields4,
    // while changing before capture exposes the new nonfinite0x7f800000.
    observe(()=>rejects(()=>x.frame.runFrame(),phase==='before'?'float32':'8006afb0'),
      phase==='before'?mutate:()=>{},phase==='after'?mutate:undefined);
    check(hit,'live BE first-byte mutation reached');retained(x);closed(x);
  }
  {
    const x=setup(make);let hit=false;
    observe(()=>finish(x),afterHelper(x,(owner,key)=>{
      if(!hit&&owner===x.admissionState&&key==='pointer508') {
        hit=true;Object.freeze(x.pos);Object.freeze(x.bytes);
        Object.defineProperty(x.processor,'gqr0',{writable:false});
        Object.defineProperty(x.admissionState,'pointer504',{writable:false});
        Object.defineProperty(x.admissionState,'pointer508',{writable:false});
      }
    }));
    check(hit,'readonly source witness reached');retained(x);closed(x);
  }
}

function arithmeticTests(make:Make):void {
  for(const values of [[-0,0,-0],[Math.fround(1e-40),Math.fround(-1e-40),Math.fround(1e-40)],[1.25,-2.5,3.75],[1+2**-23,2**-12,0]]) {
    const x=setup(make);let changed=false;
    observe(()=>finish(x),afterHelper(x,(owner,key)=>{
      if(!changed&&owner===x.admissionState&&key==='pointer508') {
        changed=true;axes.forEach((axis,i)=>{x.pos[axis]=values[i]!;});position(x.bytes,0,0,0);
      }
    }));
    check(changed,'explicit finite arithmetic vector reached');retained(x);closed(x);
  }
  for(const site of ['subtract-y','subtract-z','subtract-x','square-y','square-z','fma-x','unused-fma-y','sum'] as const) {
    const x=setup(make),max=Math.fround(3.4e38),large=Math.fround(2e19),sum=Math.fround(1.3e19);let changed=false,y=0,afterX=0,bx=0;
    observe(()=>rejects(()=>x.frame.runFrame(),site==='square-y'?'square oldY':site==='square-z'?'square oldZ':'overflow'),afterHelper(x,(owner,key)=>{
      if(!changed&&owner===x.admissionState&&key==='pointer508') {
        changed=true;Object.assign(x.pos,{x:0,y:0,z:0});position(x.bytes,0,0,0);
        if(site==='subtract-y') {x.pos.y=max;position(x.bytes,0,-max);}
        if(site==='subtract-z') {x.pos.z=max;position(x.bytes,0,0,-max);}
        if(site==='subtract-x') {x.pos.x=max;position(x.bytes,-max);}
        if(site==='square-y') position(x.bytes,0,large);
        if(site==='square-z') position(x.bytes,0,0,large);
        if(site==='fma-x') position(x.bytes,large);
        if(site==='sum') position(x.bytes,sum,sum,sum);
      }
      if(owner===x.pos&&key==='y'&&++y===2&&site==='unused-fma-y') x.pos.y=large;
      if(owner===x.pos&&key==='x') afterX++;
      if(owner===x.bytes&&key==='100') bx++;
    }));
    equal(afterX,site==='subtract-y'||site==='subtract-z'?0:1,`${site} preserves oldYZ arithmetic before freshXY`);
    equal(bx,site==='subtract-y'||site==='subtract-z'?0:1,`${site} preserves both XY loads before squares/FMA`);retained(x);closed(x);
  }
}

function profileTests(make:Make):void {
  {
    const x=setup(make);x.globals.half80436242=0;x.admissionState.pointer504=x.bytes;Reflect.set(x.admissionState,'pointer508',x.targetActor);
    Reflect.deleteProperty(x.rootSources,'processor');let selected=false,reads=0;
    observe(()=>rejects(()=>x.frame.runFrame(),'8006afac'),(owner,key)=>{
      if(owner===x.targetPreparation&&key==='targetDispatch') selected=true;
      if(selected&&(owner===x.pos&&axes.includes(key as typeof axes[number]) || owner===x.bytes&&rawKey(key))) reads++;
    });
    equal(reads,0,'initially absent profile refuses at call boundary before source scalars');
    equal(x.sourceActor.byte502,0,'genuine zero-candidate helper return does not forge target state');closed(x);
  }
  for(const kind of ['missing','accessor','bad','replace','remove'] as const) {
    const x=setup(make);let invoked=0,reads=0,changed=false;
    observe(()=>rejects(()=>x.frame.runFrame(),kind==='replace'||kind==='remove'?'owner changed':kind==='bad'?'GQR0':'own data'),afterHelper(x,(owner,key)=>{
      if(!changed&&owner===x.admissionState&&key==='pointer508') {
        changed=true;
        if(kind==='missing') Reflect.deleteProperty(x.processor,'gqr0');
        if(kind==='accessor') Object.defineProperty(x.processor,'gqr0',{get() {invoked++;return 0;},configurable:true});
        if(kind==='bad') x.processor.gqr0=1;
        if(kind==='replace') Reflect.set(x.rootSources,'processor',{gqr0:0});
        if(kind==='remove') Reflect.deleteProperty(x.rootSources,'processor');
      }
      if(owner===x.pos&&axes.includes(key as typeof axes[number])) reads++;
    }));
    equal(reads,0,'missing/bad/changed profile refuses before primary A scalar reads');equal(invoked,0,'profile accessor is never invoked');retained(x);closed(x);
  }
  for(const pair of [1,2,3,4]) {
    const x=setup(make);let n=0,a=0,b=0;
    observe(()=>rejects(()=>x.frame.runFrame(),'GQR0'),afterHelper(x,(owner,key)=>{
      if(owner===x.processor&&key==='gqr0'&&++n===pair) x.processor.gqr0=1;
      if(owner===x.pos&&axes.includes(key as typeof axes[number])) a++;
      if(owner===x.bytes&&rawKey(key)) b++;
    }));
    equal(n,pair,'GQR0 is live at each paired load');equal(a,pair===1?0:pair===2||pair===3?2:4,'bad profile stops before its A/B pair');
    equal(b,pair<=2?0:8,'B coordinate bytes remain lazy after bad profile');retained(x);closed(x);
  }
}

function positionOwnerTests(make:Make):void {
  for(const at of ['508','a-y','a-z','b-y','a-x','b-x'] as const) for(const phase of ['before','after'] as const) {
    const x=setup(make),replacement={x:101,y:102,z:103};let changed=false,replacementReads=0;
    const inject=afterHelper(x,(owner,key)=>{
      const hit=at==='508'?owner===x.admissionState&&key==='pointer508':at.startsWith('a')?
        owner===x.pos&&key===at.slice(2):owner===x.bytes&&key===(at==='b-y'?'104':'100');
      if(!changed&&hit) {changed=true;x.sourceActor.pos=replacement;}
      if(owner===replacement&&axes.includes(key as typeof axes[number])) replacementReads++;
    });
    observe(()=>rejects(()=>x.frame.runFrame(),'position'),phase==='before'?inject:()=>{},phase==='after'?inject:undefined);
    check(changed,`canonical pos replacement at ${at} ${phase} reached`);
    equal(replacementReads,0,'replacement position never supplies source scalars');retained(x);closed(x);
  }
  for(const field of ['motion','lockTarget','aimOrigin518','targetCache5e8'] as const) {
    const x=setup(make);let changed=false;
    observe(()=>rejects(()=>x.frame.runFrame(),'alias'),afterHelper(x,(owner,key)=>{
      if(!changed&&owner===x.admissionState&&key==='pointer508') {changed=true;Reflect.set(x.sourceActor,field,x.pos);}
    }));
    check(changed,`canonical pos alias with ${field} reached`);retained(x);closed(x);
  }
  for(const site of ['projectionStack','candidateGlobals','targetStack','draw-head','target-displacement'] as const) {
    const x=setup(make),targetStack={displacement:{x:71,y:72,z:73}};let changed=false,ay=0,az=0,b=0;
    // This fixture normally omits the root target stack. Supply its real
    // optional record before execution, so nested identity admission uses the
    // existing root's own metadata inventory rather than a forged callee.
    if(site==='target-displacement') Reflect.set(x.rootSources,'targetStack',targetStack);
    const count=afterHelper(x,(owner,key)=>{
      if(owner===x.pos&&key==='y') ay++;
      if(owner===x.pos&&key==='z') az++;
      if(owner===x.bytes&&rawKey(key)) b++;
    });
    const inject=afterHelper(x,(owner,key)=>{
      if(!changed&&owner===x.pos&&key==='y') {
        changed=true;
        if(site==='projectionStack'||site==='candidateGlobals') Reflect.set(x.sources,site,x.pos);
        else if(site==='targetStack') Reflect.set(x.rootSources,'targetStack',x.pos);
        else if(site==='draw-head') Reflect.set(x.root.getDrawList(),'head',x.pos);
        else targetStack.displacement=x.pos;
      }
    });
    observe(()=>rejects(()=>x.frame.runFrame(),'alias'),count,inject);
    check(changed,`late ${site} reference alias reached after primary A.y`);
    equal(ay,1,`${site} mutation follows the first actual A.y descriptor`);
    equal(az,0,`${site} host alias admission precedes A.z`);
    equal(b,0,`${site} host alias admission precedes every B scalar byte`);
    equal(x.admissionState.pointer504,x.bytes,`${site} retains original OBJECT504 store`);
    equal(x.admissionState.pointer508,x.targetActor,`${site} retains actual actor508 store`);
    retained(x);closed(x);
  }
  for(const key of ['32','36','40','field20','field24','field28','byte20','byte24','byte28'] as const) {
    const x=setup(make);let changed=false,reads=0;
    observe(()=>rejects(()=>x.frame.runFrame(),'competing'),afterHelper(x,(owner,field)=>{
      if(!changed&&owner===x.admissionState&&field==='pointer508') {changed=true;Reflect.set(x.sourceActor,key,123);}
      if(owner===x.pos&&axes.includes(field as typeof axes[number])) reads++;
    }));
    equal(reads,0,`raw actual20/24/28 shadow ${key} refuses before scalar reads`);retained(x);closed(x);
  }
  for(const kind of ['missing','accessor','inherited'] as const) {
    const x=setup(make);let changed=false,invoked=0;
    observe(()=>rejects(()=>x.frame.runFrame(),'own data'),afterHelper(x,(owner,key)=>{
      if(!changed&&owner===x.admissionState&&key==='pointer508') {
        changed=true;
        if(kind==='accessor') Object.defineProperty(x.sourceActor,'pos',{get() {invoked++;return x.pos;},configurable:true});
        else {Reflect.deleteProperty(x.sourceActor,'pos');if(kind==='inherited') Object.setPrototypeOf(x.sourceActor,{pos:x.pos});}
      }
    }));
    equal(invoked,0,'position owner accessor is never invoked');retained(x);closed(x);
  }
}

function faultsAndClosureTests(make:Make):void {
  for(const kind of ['missing','accessor','inherited','invalid'] as const) for(const site of ['508','504','a-y','a-z','a-x','b-y','b-z','b-x'] as const) {
    // Canonical admission cells are sealed by their genuine runtime. Their
    // values remain live, but descriptor removal/accessors are not representable.
    if((site==='508'||site==='504')&&kind!=='invalid') continue;
    const x=setup(make);let hit=false,invoked=0;
    const owner=site==='508'||site==='504'?x.admissionState:site.startsWith('a')?x.pos:x.bytes;
    const key=site==='508'?'pointer508':site==='504'?'pointer504':site.startsWith('a')?site.slice(2):site==='b-y'?'104':site==='b-z'?'108':'100';
    observe(()=>{try {rejects(()=>x.frame.runFrame(),kind==='invalid'?(site.startsWith('b')?'byte':site.startsWith('a')?'float32':'pointer'):'own data');} catch(error) {throw Error(`${kind} ${site}: ${String(error)}`);}},afterHelper(x,(at,field)=>{
      if(!hit&&at===owner&&field===key) {
        hit=true;
        if(kind==='invalid') Reflect.set(owner,key,site.startsWith('b')?256:site.startsWith('a')?NaN:17);
        else if(kind==='accessor') Object.defineProperty(owner,key,{get() {invoked++;return 0;},configurable:true});
        else {const prior=Reflect.get(owner,key);Reflect.deleteProperty(owner,key);if(kind==='inherited') Object.setPrototypeOf(owner,{[key]:prior});}
      }
    }));
    check(hit,`${kind} ${site} fault reached`);equal(invoked,0,'source accessor never invoked');retained(x);closed(x);
  }
  for(const kind of ['reentry','caller'] as const) for(const site of ['508','504','profile','a-y','a-z','b-y','b-z','a-x','b-x'] as const)
    for(const phase of ['before','after'] as const) {
    const x=setup(make);let entered=false;
    const inject=afterHelper(x,(owner,key)=>{
      const hit=site==='508'?owner===x.admissionState&&key==='pointer508':site==='504'?owner===x.admissionState&&key==='pointer504':
        site==='profile'?owner===x.processor&&key==='gqr0':site.startsWith('a')?owner===x.pos&&key===site.slice(2):
          owner===x.bytes&&key===(site==='b-y'?'104':site==='b-z'?'108':'100');
      if(!entered&&hit) {
        entered=true;
        if(kind==='reentry') rejects(()=>x.frame.runFrame(),'same-runtime reentry');
        else {x.control.getActorBinding(x.actor).activeMask579=256;rejects(()=>x.control.update(x.actor,1),'activeMask579');}
      }
    });
    observe(()=>rejects(()=>x.frame.runFrame(),kind==='reentry'?'reentry':'incomplete'),
      phase==='before'?inject:()=>{},phase==='after'?inject:undefined);
    check(entered,`${kind} ${phase} ${site} interruption reached`);retained(x);closed(x);
  }
}

export function runActorPrimaryDistanceSelfTests(make:Make):void {
  branchAndOrderTests(make);capturedAndLiveTests(make);arithmeticTests(make);profileTests(make);positionOwnerTests(make);faultsAndClosureTests(make);
  console.log('[actor-primary-distance] PASS: genuine post6b7f4 canonical508 null/opaque gates, captured original OBJECT504 and actual pos, live four-pair8020bc88 load/byte/GQR0 order, float32 arithmetic and unused-lane refusal, lazy profile/source faults, readonly sources and permanent outer closure retaining earlier stores; missing-threshold or absent-first-destination boundaries before distance stores, next actor/pass or scheduler authority; explicit offline operands only, no completed-frame/console/playability claim');
}
