/** Actual36e24 bounded player-contact pass. All physical clears and both active
 * scans execute. Zero distances take the genuine source branch; positive spans
 * stop before the required Add/Scale/contact traversal, never dispatch a no-op.
 * Endpoint words and player rows belong to canonical slot-status, not actors or
 * invented records. No source routine is callable without private294f8 entry.
 */
import {consumeSourceBattlePlayerContactInvocation,checkSourceBattlePlayerContactInvocation,
 readSourceBattlePlayerContactSystem,readSourceBattlePlayerContactZero,type SourceBattleOuterFrameRuntime} from './battle-outer-frame.js';
import {getSourcePlayerContactRow} from './actor-slot-status.js';
import {addSourceFloat32 as add,fusedMultiplyAddSourceFloat32 as fma} from './source-float.js';
const nativeDescriptor=Reflect.getOwnPropertyDescriptor;
function fail(s:string):never{throw Error('[source-player-contact] '+s);}
function uint(v:unknown,max:number,label:string):number{
 if(typeof v!=='number'||!Number.isInteger(v)||v<0||v>max)fail(label+': raw unsigned source field required');return v;
}
const endpointFields=['word2e8','word2ec','word2f0','word300','word304','word308']as const;
export function executeSourcePlayerContact36e24(outer:SourceBattleOuterFrameRuntime):void{
 const context=consumeSourceBattlePlayerContactInvocation(outer),{helper,root}=context;
 const check=():void=>checkSourceBattlePlayerContactInvocation(outer,helper);
 const own=(owner:object,key:string):unknown=>{const p=Object.getOwnPropertyDescriptor(owner,key);check();if(!p||!('value'in p))fail(key+': own data required');return p.value;};
 const systemByte=(owner:object,key:string):unknown=>{
  // Exactly the participant-view alias vocabulary, only for this reached cell.
  const base:Record<string,string[]>={byte29:['41','mode29','field29'],
   byte0c:['12','byteC','bytec','byte0C','field0c'],byte0d:['13','byteD','byted','byte0D','field0d'],
   byte0e:['14','byteE','bytee','byte0E','field0e'],byte0f:['15','byteF','bytef','byte0F','field0f']};
  const names=[...new Set(base[key]!.flatMap(alias=>[alias,alias.replace(/^(byte|pointer|word|field)([0-9a-f]+)$/i,(_m,p:string,h:string)=>p+h.toUpperCase())]))];
  for(const name of names){const p=Object.getOwnPropertyDescriptor(owner,name);check();if(p)fail(key+': competing contact system field');}
  const value=own(owner,key);
  for(const name of names)if(nativeDescriptor(owner,name))fail(key+': competing contact system field');
  return value;
 };
 const row=(i:number):object=>{const r=getSourcePlayerContactRow(helper,outer,i);check();return r;};
 const aliases=(r:object,key:string,terminal=false):void=>{
  const hex=key==='active0'?'0':key==='contact26f'?'26f':key.slice(4);
  const names=[String(parseInt(hex,16)),`byte${hex}`,`field${hex}`,`float${hex}`,`word${hex.toUpperCase()}`];
  for(const name of names)if(name!==key){const p=terminal?nativeDescriptor(r,name):Object.getOwnPropertyDescriptor(r,name);if(!terminal)check();if(p)fail(key+': competing canonical player field');}
 };
 const playerRead=(r:object,key:string):unknown=>{aliases(r,key);const value=own(r,key);aliases(r,key,true);return value;};
 const visited:number[]=[];
 for(let i=0;i<13;i++){
  const r=row(i);aliases(r,'contact26f');
  const p=Object.getOwnPropertyDescriptor(r,'contact26f');check();
  if(!p||!('value'in p)||!p.writable)fail('contact26f: writable own destination required');
  if(row(i)!==r)fail('clear player changed');
  const last=nativeDescriptor(r,'contact26f');if(!last||!('value'in last)||!last.writable)fail('contact26f destination changed');
  for(const key of ['623','byte26f','field26f','float26f','word26F'])if(nativeDescriptor(r,key))fail('contact26f: competing canonical player field');
  (r as {contact26f:number}).contact26f=0;check();visited[i]=0;
 }
 const system=readSourceBattlePlayerContactSystem(outer);
 const raw=uint(systemByte(system,'byte29'),255,'byte29'),shift=(raw<<24>>24)&63;
 const selectedCount=shift>=32?0:1<<shift; // PPC slw and signed loop comparison.
 let processor:object|undefined;
 const paired=():void=>{
  const current=root.getVectorProcessorProfile();check();
  if(!current||typeof current!=='object')fail('explicit canonical processor required');
  if(processor&&processor!==current)fail('processor owner changed');processor=current;
  own(processor,'gqr0');own(processor,'fpscrControl');
  if(root.getVectorProcessorProfile()!==processor)fail('processor owner changed');check();
  // Final sampling closes descriptor hooks before the paired local-stack load.
  const g=nativeDescriptor(processor,'gqr0'),f=nativeDescriptor(processor,'fpscrControl');
  if(!g||!('value'in g)||g.value!==0)fail('GQR0 float scale0 required');
  if(!f||!('value'in f)||typeof f.value!=='number'||!Number.isInteger(f.value)||f.value<0||f.value>0xffffffff||(f.value&255)!==0)fail('FPSCR RN00/NI0 and disabled exceptions required');
 };
 const asFloat=(bits:number):number=>{const v=new DataView(new ArrayBuffer(4));v.setUint32(0,bits,false);const x=v.getFloat32(0,false);if(!Number.isFinite(x))fail('finite local-stack float32 required');return x;};
 const mul=(a:number,b:number):number=>{const x=Math.fround(a*b);if(!Number.isFinite(x))fail('finite paired product required');return x;};
 const process=(index:number,r:object,first:boolean):void=>{
  // lwz: capture all six RAW words before first stack store or paired admission.
  const words=endpointFields.map(key=>uint(playerRead(r,key),0xffffffff,key));
  if(first)visited[index]=1;
  // Actual8020bc88: A.YZ,B.YZ,subtract; A.XY,B.XY; rounded YY/ZZ,
  // fused XY and unused second lane, then sum. No ideal-distance shortcut.
  paired();const ay=asFloat(words[1]!),az=asFloat(words[2]!);
  paired();const by=asFloat(words[4]!),bz=asFloat(words[5]!);
  const oldY=add(ay,-by),oldZ=add(az,-bz);
  paired();const ax=asFloat(words[0]!),ayAgain=asFloat(words[1]!);
  paired();const bx=asFloat(words[3]!),byAgain=asFloat(words[4]!);
  const yy=mul(oldY,oldY),zz=mul(oldZ,oldZ),dx=add(ax,-bx),dy=add(ayAgain,-byAgain);
  const xy=fma(dx,dx,yy);fma(dy,dy,zz);const square=add(xy,zz);check();
  const zero=readSourceBattlePlayerContactZero(outer);if(!Object.is(zero,0))fail('float80436f68 authenticated +0 required');
  if(square>0)fail(`${first?'80036f14':'80037160'} reached positive endpoint span: actual8020ba54 Add/8020ba9c Scale and contact dispatch unsupported`);
 };
 const active=(r:object):boolean=>(uint(playerRead(r,'active0'),255,'active0')<<24>>24)!==0;
 for(let i=0;i<selectedCount;i++){
  // Actual36e94 reloads view owner for each mapping, unlike captured count.
  const view=readSourceBattlePlayerContactSystem(outer);
  if(i>=4)fail('selected view mapping beyond explicit system0c..0f domain');
  const index=uint(systemByte(view,['byte0c','byte0d','byte0e','byte0f'][i]!),255,'view mapping')<<24>>24;
  const r=row(index);if(active(r))process(index,r,true);
 }
 for(let i=0;i<13;i++){
  if(visited[i]!==0)continue;
  const r=row(i);if(active(r))process(i,r,false);
 }
 check();
}
