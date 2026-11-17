/** Bounded actual47aa4, never a no-op draw callback. The private outer call
 * owns entry/closure; matrix114 always lives in the original allocated bytes.
 * Evidence: draw-callback reader (404B) and prior matrix/traversal proofs.
 * Copy/MultVec and nonzero RotRad remain explicit reached boundaries.
 */
import {consumeSourceBattleOuterDrawInvocation,checkSourceBattleOuterDrawInvocation,
  type SourceBattleOuterFrameRuntime} from './battle-outer-frame.js';
import {fusedMultiplyAddSourceFloat32 as fma} from './source-float.js';

const nativeDescriptor=Reflect.getOwnPropertyDescriptor;
function fail(s:string):never {throw Error(`[source-draw-callback] ${s}`);}
function float(x:unknown):number {
  if(typeof x!=='number'||!Number.isFinite(x)||!Object.is(x,Math.fround(x)))fail('finite exact float32 required');
  return x;
}
const factorBits=new DataView(new ArrayBuffer(4));factorBits.setUint32(0,0x38c90fdb,false);
const angleFactor=factorBits.getFloat32(0,false);
const identityOrder=[2,3,6,7,8,9,4,5,0,1,10,11] as const;
const concatOrder=[0,1,4,5,2,3,6,7,8,9,10,11] as const;
const rotateGroups={x:[[0],[1,2],[3,4],[7,8],[11],[9,10],[5,6]],y:[[6,7],[0,1],[10,11],[4,5],[2,3],[8,9]],z:[[2,3],[6,7],[8,9],[4,5],[0,1],[10,11]]};

export function executeSourceDrawCallback47aa4(outer:SourceBattleOuterFrameRuntime,node:symbol):void {
  const scope=consumeSourceBattleOuterDrawInvocation(outer,node);
  const {allocator,root,processor}=scope;
  const check=():void=>checkSourceBattleOuterDrawInvocation(outer,node);
  const call=<T>(f:()=>T):T=>{const value=f();check();return value;};
  const own=(o:object,key:string):unknown=>{
    const d=Object.getOwnPropertyDescriptor(o,key);check();
    if(!d||!('value'in d))fail(`${key}: own data required`);return d.value;
  };
  const finalControls=(gqr?:'gqr0'|'gqr5'):void=>{
    if(!processor)fail('explicit processor owner required');
    const f=nativeDescriptor(processor,'fpscrControl');
    if(!f||!('value'in f)||typeof f.value!=='number'||!Number.isInteger(f.value)||f.value<0||f.value>0xffffffff||(f.value&255)!==0)
      fail('explicit FPSCR RN00/NI0 and disabled floating exception enables required');
    if(gqr){const g=nativeDescriptor(processor,gqr);
      if(!g||!('value'in g)||g.value!==(gqr==='gqr0'?0:0x00070007))fail(`${gqr}: explicit float/signed16 scale0 profile required`);}
  };
  const controls=():void=>{
    if(!processor)fail('explicit processor owner required');
    if(call(()=>root.getVectorProcessorProfile())!==processor)fail('processor owner changed');
    own(processor,'fpscrControl');finalControls();
  };
  const paired=(gqr:'gqr0'|'gqr5'='gqr0'):void=>{
    controls();if(!processor)fail('explicit processor owner required');own(processor,gqr);finalControls(gqr);
  };
  const constant=(key:string,expected:number):number=>{
    if(!scope.constants||typeof scope.constants!=='object'||ArrayBuffer.isView(scope.constants))fail('explicit constants owner required');
    const x=own(scope.constants,key);if(typeof x!=='number'||!Object.is(x,expected))fail(`${key}: authenticated constant required`);return x;
  };
  const read=(offset:number):number=>float(call(()=>allocator.readF32(node,offset)));
  const store=(offset:number,first:number,second?:number):void=>{
    const destination=call(()=>allocator.getObject(node)),buffer=new ArrayBuffer(second===undefined?4:8),view=new DataView(buffer);
    view.setFloat32(0,float(first),false);if(second!==undefined)view.setFloat32(4,float(second),false);
    for(let i=0;i<buffer.byteLength;i++){
      const field=Object.getOwnPropertyDescriptor(destination,String(offset+i));check();
      if(!field||!('value'in field)||!field.writable)fail('paired destination requires writable own bytes');
    }
    if(second===undefined)controls();else paired();
    // Final intrinsic admission closes observable descriptor/control hooks before
    // the single emulated paired store; no first-lane write on second-lane fault.
    for(let i=0;i<buffer.byteLength;i++){
      const field=nativeDescriptor(destination,String(offset+i));
      if(!field||!('value'in field)||!field.writable)fail('paired destination changed before store');
    }
    finalControls(second===undefined?undefined:'gqr0');
    for(let i=0;i<buffer.byteLength;i++)destination[offset+i]=view.getUint8(i);
    check();
  };
  const write=(offset:number,value:number):void=>store(offset,value);
  const writePair=(offset:number,x:number,y:number):void=>store(offset,x,y);
  const flags=call(()=>allocator.readU8(node,0x84)); // Capture once, never re-read after helpers.
  if(flags&0x40)fail('47ae4 bone matrix Copy is unsupported');
  if(flags&0x20)fail('47b00 parent matrix Copy is unsupported');
  const zero=constant('float8043ca6c',0),one=constant('float8043ca68',1);
  for(let p=0;p<identityOrder.length;p+=2){const i=identityOrder[p]!,j=identityOrder[p+1]!;writePair(0x114+4*i,i===0||i===5||i===10?one:zero,j===0||j===5||j===10?one:zero);}
  if(flags&1)fail('47b24 actual MultVec local64 is unsupported');
  if(!(flags&0x80))for(const [from,to]of [[0x20,0x120],[0x24,0x130],[0x28,0x140]]as const)write(to,read(from));
  let scratch:Float32Array|undefined;
  const stack=():Float32Array=>{
    check();const s=scope.scratch;
    if(!(s instanceof Float32Array)||s.length!==12||!(s.buffer instanceof ArrayBuffer))fail('explicit private twelve-float draw stack required');
    if(scratch&&scratch!==s)fail('draw stack owner changed');scratch=s;return s;
  };
  const concat=():void=>{
    const s=stack(),a:number[]=[],b:number[]=[];
    const loadA=(i:number):void=>{paired();a[i]=read(0x114+4*i);a[i+1]=read(0x118+4*i);};
    const loadB=(i:number):void=>{paired();b[i]=float(s[i]);b[i+1]=float(s[i+1]);check();};
    // Retained af5c paired source order, all operands before first output store.
    loadA(0);loadB(0);loadB(2);loadB(4);loadA(4);
    paired();const c0=constant('float80435ca0',0),c1=constant('float80435ca4',1);
    loadB(6);loadA(2);loadA(6);loadB(8);loadB(10);loadA(8);loadA(10);
    const compute=(i:number):number=>{
      const row=i-i%4,col=i%4;controls();
      let v=float(Math.fround(b[col]!*a[row]!));
      v=fma(b[4+col]!,a[row+1]!,v);v=fma(b[8+col]!,a[row+2]!,v);
      if(col>=2)v=fma(col===3?c1:c0,a[row+3]!,v);return v;
    };
    for(let p=0;p<concatOrder.length;p+=2){const i=concatOrder[p]!,j=concatOrder[p+1]!;
      const x=compute(i),y=compute(j);writePair(0x114+4*i,x,y);}
  };
  for(const [mask,offset,axis]of [[8,0x74,'z'],[4,0x72,'y'],[2,0x70,'x']]as const){
    if(!(flags&mask))continue;
    paired('gqr5');const angle=call(()=>allocator.readS16(node,offset));
    const factor=constant('float804370e0',angleFactor);
    controls();const radians=float(Math.fround(angle*factor));
    if(radians!==0)fail('8020b260 sinf: nonzero radians unsupported');
    const cosine=constant('double8043d030',1),sine=radians;
    const z=constant('float8043ca6c',0),o=constant('float8043ca68',1),s=stack();
    const values=axis==='x'?[o,z,z,z,z,cosine,-sine,z,z,sine,cosine,z]:
      axis==='y'?[cosine,z,sine,z,z,o,z,z,-sine,z,cosine,z]:[cosine,-sine,z,z,sine,cosine,z,z,z,z,o,z];
    // Temporary RotTrig stores retain signed sine and actual instruction order.
    for(const group of rotateGroups[axis]){paired();if(s.length!==12)fail('draw stack detached before stores');finalControls('gqr0');for(const i of group)s[i]=values[i]!;check();if(s.length!==12)fail('draw stack detached during stores');}
    concat();
  }
  if(flags&0x10){
    const x=read(0x58),y=read(0x5c),z=read(0x60),zero=constant('float8043ca6c',0),s=stack();
    const values=[x,zero,zero,zero,zero,y,zero,zero,zero,zero,z,zero];
    for(const group of [[0],[1,2],[3,4],[5],[6,7],[8,9],[10],[11]]){paired();if(s.length!==12)fail('draw stack detached before stores');finalControls('gqr0');for(const i of group)s[i]=values[i]!;check();if(s.length!==12)fail('draw stack detached during stores');}
    concat();
  }
  check();
}
