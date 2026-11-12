/** Switching Ninja801e29fc child, original phases1e2b4c/1e2cdc/1e2f58/1e2f94.
 * Inert lifecycle only. Placement, HIT registration and geometry are explicit
 * adapter boundaries; this module neither admits an attack nor moves fighters.
 * Timers1c and visual counters are dispatch counters, not animation dt.
 */
export interface SwitchingFieldVec3 {x:number;y:number;z:number}
export interface SwitchingFieldState {
  phase:'pending'|'active'|'retiring'|'released'|'freed';subphase:0|1;timer:number;
  pos:SwitchingFieldVec3;modelScale:number;collisionScale:number;
  yaw:number;pitch:number;visualScale:SwitchingFieldVec3;
  innerScale:number;outerScale:number;outerAlpha:number;innerStage:number;outerStage:number;
  innerCount:number;outerCount:number;flags272:number;hitActive:boolean;visible:boolean;
  reason:'expired'|'owner-dead'|'owner-changed'|null;
}
export interface SwitchingFieldContext {
  /** Source init samples linked owner's current capture pointer plus the child's
   * captured d0 flag. Adapter supplies its bounded target/pose geometry. */
  initialPosition():SwitchingFieldVec3;
  registerHit?():boolean;
  priorContact10?:boolean;
  ownerInvalid?:'owner-dead'|'owner-changed';
  /** Source BAM cosine SDK is a boundary, not an instruction-equivalent oracle. */
  cosBam?:(angle:number)=>number;
}
const f=Math.fround,s16=(v:number)=>(v<<16)>>16,s8=(v:number)=>(v<<24)>>24;
export function createSwitchingField(modelScale:number,collisionScale:number):SwitchingFieldState {
  return {phase:'pending',subphase:0,timer:0,pos:{x:0,y:0,z:0},modelScale,collisionScale,
    yaw:0,pitch:0,visualScale:{x:0,y:0,z:0},innerScale:1,outerScale:1,outerAlpha:1,
    innerStage:0,outerStage:0,innerCount:0,outerCount:0,flags272:0,hitActive:false,visible:false,reason:null};
}
/** One source dispatch; init does not fall through into warning. State is
 * replaced so earlier observations cannot mutate as simulation progresses. */
export function stepSwitchingField(input:SwitchingFieldState,ctx:SwitchingFieldContext):SwitchingFieldState {
  const s={...input,pos:{...input.pos},visualScale:{...input.visualScale}};
  if(s.phase==='freed')return s;
  //84000 only guards phases0/1. It routes through phase2 in this same pass.
  if(ctx.ownerInvalid&&(s.phase==='pending'||s.phase==='active')){
    s.reason=ctx.ownerInvalid;s.phase='released';s.hitActive=false;s.visible=false;
    return s;
  }
  if(s.phase==='pending'){
    s.phase='active';s.pos={...ctx.initialPosition()};s.visualScale={x:1,y:1,z:1};
    s.yaw=0;s.pitch=-0x8000;s.timer=60;s.visible=true;return s;
  }
  if(s.phase==='retiring'){s.phase='released';s.hitActive=false;s.visible=false;return s;}
  if(s.phase==='released'){s.phase='freed';return s;}
  if(s.subphase===0){
    s.yaw=s16(s.yaw+0x444);s.pitch=s16(s.pitch+0x444);
    const cosine=(ctx.cosBam??((angle:number)=>Math.cos(angle*Math.PI*2/65536)))(s.pitch);
    const scale=f(.5*cosine+1.5);s.visualScale.x=scale;s.visualScale.z=scale;
    // Source tests before decrement:60 updates reach0, the61st registers HIT.
    if(s.timer<1){
      if(ctx.registerHit?.()??true){
        s.subphase=1;s.timer=25;s.hitActive=true;s.visualScale={x:1,y:1,z:1};
        s.innerScale=s.outerScale=1;s.outerAlpha=1;s.innerStage=s.outerStage=0;s.innerCount=s.outerCount=0;
      }
    }else s.timer=s16(s.timer-1);
    return s;
  }
  if(ctx.priorContact10)s.flags272|=1;
  s.timer=s16(s.timer-1);
  if(s.timer<1){s.phase='retiring';s.hitActive=false;s.visible=false;s.reason='expired';return s;}
  if(s.innerStage===1){
    s.innerScale=f(s.innerScale-f(1/44));s.innerCount=s8(s.innerCount+1);
    if(s.innerCount>24){s.innerStage=2;s.innerScale=f(.05);}
  }else if(s.innerStage===0){
    s.innerScale=f(s.innerScale-f(1/6));s.innerCount=s8(s.innerCount+1);
    if(s.innerCount>2){s.innerStage=1;s.innerScale=.5;}
  }
  if(s.outerStage===0){
    s.outerScale=f(s.outerScale+f(.1));s.outerAlpha=f(s.outerAlpha-f(.1));s.outerCount=s8(s.outerCount+1);
    if(s.outerCount>9){s.outerStage=1;s.outerScale=2;s.outerAlpha=0;}
  }
  return s;
}
