/** Genuine existing graph inputs for the bounded46f08 sentinel/masked lane. */
import {createBattleOrderedActorStageTestFixture} from './battle-ordered-actor-stage.selftest.js';
import type {createBattleTargetPreparationTestFixture} from './attached-setup-animation.selftest.js';
import {addSourceFloat32} from './source-float.js';
function check(ok:boolean,why:string):void{if(!ok)throw Error('[actor-matrix-spring-test] '+why);}
function refuses(run:()=>unknown,part:string):void{let m='';try{run();}catch(e){m=String(e);}check(m.includes(part),`expected ${part}, got ${m||'success'}`);}
export function runActorMatrixSpringSelfTests(make:typeof createBattleTargetPreparationTestFixture):void{
 let count=0;
 const fresh=(bind=true)=>{
  count++;const x=createBattleOrderedActorStageTestFixture(make);
  if(bind)x.normal.bindAttributesRuntime(x.attributes);
  x.sourceActor.controlWord=0;x.sourceActor.modelScale=1;
  x.metadata.getActorBinding(x.actor).byte1d98=0x10;
  const descriptor=x.movement.getDescriptorBinding(x.mapping.getActor(x.actor).descriptor4b0!);descriptor.joint22=255;
  x.movement.getActorBinding(x.actor).byte661=0;x.attributeState.field674=8;x.normalState.field1d60=4;
  return Object.assign(x,{springDescriptor:descriptor});
 };
 const observe=(x:ReturnType<typeof fresh>,visit:(o:object,k:PropertyKey)=>void)=>{
  const native=Object.getOwnPropertyDescriptor;
  Object.getOwnPropertyDescriptor=((o:object,k:PropertyKey)=>{visit(o,k);return native(o,k);}) as typeof native;
  try{x.normal.updateActor(x.actor);}finally{Object.getOwnPropertyDescriptor=native;}
 };
 {
  const x=fresh();let prior=NaN;
  observe(x,(o,k)=>{if(o===x.normalState&&k==='field1d60'&&Number.isNaN(prior))prior=x.header.adjusted1d54.y;});
  check(x.normalState.field1d60===3&&x.header.adjusted1d54.y===addSourceFloat32(prior,3),'sentinel mandatory spring and freshY stores');
  check(x.normalState.count1d96===0&&x.normalState.count1d97===0,'real count clears preserved');
 }
 {
  const x=fresh();x.attributeState.field674=-8;x.sourceActor.modelScale=2;let prior=NaN;
  observe(x,(o,k)=>{if(o===x.normalState&&k==='field1d60'&&Number.isNaN(prior))prior=x.header.adjusted1d54.y;});
  check(x.normalState.field1d60===3.125&&x.header.adjusted1d54.y===addSourceFloat32(prior,3.125),'negative674 clamp division and fused suffix');
 }
 {
  const x=fresh();Object.assign(x.springDescriptor,{joint22:0,joint2a:0,joint32:0,joint3a:0});x.metadata.getActorBinding(x.actor).byte1d99=255;
  x.normal.updateActor(x.actor);check(x.normalState.field1d60===3,'all four signed-mask skips still spring');
 }
 {
  const x=fresh();x.springDescriptor.joint22=0;
  refuses(()=>x.normal.updateActor(x.actor),'nonempty contact matrix load');check(x.normalState.field1d60===4,'no invented contact or spring after unsupported reached branch');
 }
 {
  const x=fresh(false);refuses(()=>x.normal.updateActor(x.actor),'genuine shared attribute674');check(x.normalState.field1d60===4,'missing674 owner before spring');
  refuses(()=>x.normal.bindAttributesRuntime(x.attributes),'before execution');
 }
 {
  const x=fresh(false);refuses(()=>x.normal.bindAttributesRuntime({...x.attributes}),'genuine attribute674');
  x.normal.bindAttributesRuntime(x.attributes);refuses(()=>x.normal.bindAttributesRuntime(x.attributes),'once');
 }
 {
  const x=fresh(false),other=fresh();x.normal.bindAttributesRuntime(other.attributes);
  refuses(()=>x.normal.updateActor(x.actor),'unknown');check(x.normalState.field1d60===4,'foreign actual owner cannot supply674');
 }
 {
  const x=fresh();x.sourceActor.modelScale=0;
  refuses(()=>x.normal.updateActor(x.actor),'zero divisor');check(x.normalState.field1d60===4,'zero divisor no spring stores');
 }
 {
  const x=fresh();x.sourceActor.modelScale=NaN;
  refuses(()=>x.normal.updateActor(x.actor),'modelScale');check(x.normalState.count1d96===0&&x.normalState.field1d60===4,'mandatory entry scale before sentinel');
 }
 {
  const x=fresh();Object.defineProperty(x.normalState,'field1d60',{writable:false});
  refuses(()=>x.normal.updateActor(x.actor),'field1d60');check(x.normalState.field1d60===4,'readonly spring field');
 }
 {
  const x=fresh();let armed=false;
  refuses(()=>observe(x,(o,k)=>{if(o===x.normalState&&k==='field1d60'&&!armed){armed=true;Object.defineProperty(x.header.adjusted1d54,'y',{writable:false});}}),'y:');
  check(armed&&x.normalState.field1d60===3,'spring store retained before readonly freshY destination');
 }
 {
  const x=fresh();let changed=false,prior=NaN;
  observe(x,(o,k)=>{if(o===x.header.adjusted1d54&&k==='y'&&x.normalState.field1d60===3&&!changed){changed=true;prior=x.header.adjusted1d54.y;x.normalState.field1d60=99;}});
  check(changed&&x.normalState.field1d60===99&&x.header.adjusted1d54.y===addSourceFloat32(prior,3),'source register next retained without1d60 reload');
 }
 {
  const x=fresh();let reentered=false;
  refuses(()=>observe(x,(o,k)=>{if(o===x.attributeState&&k==='field674'&&!reentered){reentered=true;try{x.normal.updateActor(x.actor);}catch{}}}),'reentry');
  check(reentered&&x.normalState.field1d60===4,'caught inner reentry prevents later spring stores');
 }
 {
  const x=fresh();Object.assign(x.sourceActor,{field674:8});
  refuses(()=>x.normal.updateActor(x.actor),'competing674');check(x.normalState.field1d60===4,'shadow674 refuses');
 }
 {
  const x=fresh();x.normalState.field1d60=0.061623089015483856;x.attributeState.field674=-0.08616212755441666;
  x.normal.updateActor(x.actor);
  check(x.normalState.field1d60===0.048909883946180344,'single-round fused witness, not unfused0.048909880220890045');
 }
 {
  const x=fresh();x.attributeState.field674=-8;let changed=false;
  observe(x,(o,k)=>{if(o===x.attributeState&&k==='field674'&&!changed){changed=true;x.sourceActor.modelScale=2;}});
  check(changed&&x.normalState.field1d60===3.125,'fresh suffix scale not captured entry scale');
 }
 {
  const x=fresh();Object.assign(x.sourceActor,{field1d60:4});
  refuses(()=>x.normal.updateActor(x.actor),'spring owner');check(x.normalState.field1d60===4,'competing spring owner rejected');
 }
 {
  const x=fresh();let injected=false;
  refuses(()=>observe(x,(o,k)=>{if(o===x.attributeState&&k==='7520'&&!injected){injected=true;Object.assign(x.sourceActor,{field674:8});}}),'competing674');
  check(injected&&x.normalState.field1d60===4,'native final checks catch late earlier-owner shadow injection');
 }
 for(const selector of [1,3]){
  const x=fresh(false);x.metadata.getActorBinding(x.actor).byte1d98=0x10|selector;
  x.normal.updateActor(x.actor);check(x.normalState.field1d60===Math.fround(4*Math.fround(0.8)),'old damping selector unaffected without674');
 }
 console.log(`[actor-matrix-spring] PASS: ${count} genuine fixtures; sentinel/masked46f08, source spring order, shared674, finite precision, partial writes and honest contact boundary`);
}
