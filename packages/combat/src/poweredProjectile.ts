/** Powered Gunman normal action 2 and charged action 3. Source: 8007db5c family,
 * table 802d6d68 (chunk_0011:4289–4609); secondary 8016d584/8016d9ac/
 * 8016db34/8016dcc0, table 80350660 (chunk_0043:4633–4980).
 * Pure source-unit, one-frame math. Caller supplies target center and source attachment
 * origin; actor root/center and static-bind approximations belong to the integration.
 * JS trig replaces source libm. Degenerate trajectories retain finite gravity and a
 * deterministic orthogonal basis: explicit numerical safeguards, not decoded behavior.
 */
export interface PoweredVec3 { x: number; y: number; z: number }
export interface PoweredLaunchSeed {
  cause: 'normal' | 'primary' | 'split';
  pos: PoweredVec3;
  basis: { right: PoweredVec3; up: PoweredVec3; forward: PoweredVec3 };
}
export type PoweredLaunchSink = (event: PoweredLaunchSeed) => void;
export interface PoweredTarget { uid: string; pos: PoweredVec3; scale: number }
export type PoweredPrimaryRow = 4 | 6 | 7 | 8 | 9;
export type PoweredNormalPort = 0 | 1 | 2 | 3;
export type PoweredSecondaryPort = PoweredNormalPort | 4 | 5 | 6 | 7;
export const POWERED_PRIMARY_ROWS = [8, 9, 6, 7] as const;
export const POWERED_PRIMARY_PORTS = { 6: 4, 7: 5, 8: 6, 9: 7 } as const;
export interface PoweredPrimaryState {
  kind: 'primary'; row: PoweredPrimaryRow; pos: PoweredVec3; vel: PoweredVec3;
  life: number; scale: number; ownerScale: number; alpha: number; spin: number;
  /** Visual source yaw is deliberately independent of fixed flight heading. */
  yaw: number; gravity: number; gravityTimer: number; targetUid: string | null;
  targetCenter: PoweredVec3 | null; alive: boolean; split: boolean;
}
export interface PoweredSecondaryState {
  kind: 'secondary'; port: PoweredSecondaryPort; pos: PoweredVec3; vel: PoweredVec3;
  direction: PoweredVec3; reference: PoweredVec3; speed: number; acceleration: number;
  life: number; scale: number; alpha: number; spin: number;
  phase: 'flight' | 'shrink' | 'expired';
}
const copy = (v: PoweredVec3): PoweredVec3 => ({ ...v });
const sub = (a: PoweredVec3, b: PoweredVec3): PoweredVec3 => ({ x:a.x-b.x,y:a.y-b.y,z:a.z-b.z });
const mul = (v: PoweredVec3, s: number): PoweredVec3 => ({x:v.x*s,y:v.y*s,z:v.z*s});
const add = (a: PoweredVec3, b: PoweredVec3): PoweredVec3 => ({x:a.x+b.x,y:a.y+b.y,z:a.z+b.z});
const cross = (a: PoweredVec3,b: PoweredVec3): PoweredVec3 => ({x:a.y*b.z-a.z*b.y,y:a.z*b.x-a.x*b.z,z:a.x*b.y-a.y*b.x});
const length = (v: PoweredVec3): number => Math.hypot(v.x,v.y,v.z);
const normalized = (v: PoweredVec3, fallback: PoweredVec3): PoweredVec3 => length(v)>1e-12 ? mul(v,1/length(v)) : copy(fallback);
const clamp = (n:number,lo:number,hi:number):number => Math.min(hi,Math.max(lo,n));
const wrap = (a:number):number => ((a+Math.PI)%(Math.PI*2)+Math.PI*2)%(Math.PI*2)-Math.PI;

export function createPoweredPrimary(row:PoweredPrimaryRow,pos:PoweredVec3,yaw:number,target:PoweredTarget|null,ownerScale=1,launchAim:PoweredVec3|null=target?.pos??null,onLaunch?:PoweredLaunchSink):PoweredPrimaryState {
  // Shared 8007db5c row4 differs only through decoded table fields.
  const speed=row===4?40:60, gravity=row===4?Math.fround(.3):.15;
  let heading=yaw,pitch=0;
  if(target){
    const d=sub(launchAim??target.pos,pos), horizontal=Math.max(Math.hypot(d.x,d.z),.0001);
    const q=gravity*horizontal*horizontal/(2*speed*speed);
    // Algebraically rationalized low ballistic root avoids subtractive cancellation.
    const discriminant=horizontal*horizontal-4*q*(q+d.y);
    const root=Math.sqrt(Math.max(discriminant,0));
    const tangent=discriminant>=0?2*(q+d.y)/(horizontal+root):(horizontal-root)/(2*q);
    pitch=Math.min(Math.atan(tangent),.8);
    heading=Math.atan2(d.x,d.z);
  }
  const state:PoweredPrimaryState={kind:'primary',row,pos:copy(pos),vel:{x:speed*Math.sin(heading)*Math.cos(pitch),y:speed*Math.sin(pitch),z:speed*Math.cos(heading)*Math.cos(pitch)},life:600,scale:(row===4?2:.4)*ownerScale,ownerScale,alpha:1,spin:0,yaw,gravity,gravityTimer:row===4?4:1,targetUid:target?.uid??null,targetCenter:target?copy(target.pos):null,alive:true,split:false};
  // 8007dd84 emits launch FX before the constructor's first flight update.
  if(row!==4) onLaunch?.({cause:'primary',pos:copy(pos),basis:poweredLaunchBasis(state.vel,{x:state.vel.z,y:0,z:-state.vel.x})});
  return stepPoweredPrimary(state,target).state;
}

export function stepPoweredPrimary(input:PoweredPrimaryState,target:PoweredTarget|null):{state:PoweredPrimaryState;alive:boolean;split:boolean}{
  const state={...input,pos:copy(input.pos),vel:copy(input.vel)};
  if(!state.alive)return {state,alive:false,split:state.split};
  state.life--;
  if(state.life<=0){state.alive=false;return {state,alive:false,split:false};}
  state.spin=wrap(state.spin+0x1800*Math.PI/32768);
  const validTarget=state.targetUid!==null&&target?.uid===state.targetUid?target:null;
  if(!validTarget){state.targetUid=null;state.targetCenter=null;}
  else if(--state.gravityTimer<=0){
    state.gravityTimer=state.row===4?4:1;state.targetCenter=copy(validTarget.pos);
    const d=sub(validTarget.pos,state.pos);
    if(state.row!==4&&length(d)<300*validTarget.scale){state.alive=false;state.split=true;return {state,alive:false,split:true};}
    const t=Math.hypot(d.x,d.z)/Math.hypot(state.vel.x,state.vel.z);
    const desired=2*(t*state.vel.y-d.y)/(t*t);
    if(Number.isFinite(desired))state.gravity+=clamp(clamp(desired,0,7.5)-state.gravity,-.15,.15);
  }
  state.pos=add(state.pos,{x:state.vel.x,y:state.vel.y-state.gravity*.5,z:state.vel.z});
  const vy=state.vel.y-state.gravity;
  state.vel=mul(normalized({...state.vel,y:vy},{x:0,y:0,z:1}),state.row===4?40:60);
  state.vel.y=vy;
  return {state,alive:true,split:false};
}

/** Four children per primary, not an explosion. Exactly five injected source-byte draws. */
export function createPoweredSecondaries(primary:PoweredPrimaryState,randomByte:()=>number,onLaunch?:PoweredLaunchSink):PoweredSecondaryState[]{
  if(primary.row===4)return []; // row4 signed split selector is -1
  const port=POWERED_PRIMARY_PORTS[primary.row];
  const visualYaw=primary.yaw+primary.spin;
  return createPoweredPort(port,primary.pos,
    primary.targetCenter?sub(primary.targetCenter,primary.pos):primary.vel,
    {x:Math.sin(visualYaw),y:0,z:Math.cos(visualYaw)},primary.ownerScale,randomByte,onLaunch,'split');
}

/** FUN_8016d584 rows 0..3: actor-local Z reference, saved world aim, four children. */
export function createPoweredNormalPort(port:PoweredNormalPort,pos:PoweredVec3,yaw:number,
  aim:PoweredVec3,ownerScale:number,randomByte:()=>number,onLaunch?:PoweredLaunchSink):PoweredSecondaryState[]{
  return createPoweredPort(port,pos,sub(aim,pos),{x:Math.sin(yaw),y:0,z:Math.cos(yaw)},ownerScale,randomByte,onLaunch,'normal');
}

/** Mode-5 launch basis; deterministic degenerate fallback matches existing host math. */
export function poweredLaunchBasis(aimDelta:PoweredVec3,axis:PoweredVec3):PoweredLaunchSeed['basis'] {
  const z=normalized(aimDelta,{x:0,y:0,z:1});
  let x=cross(axis,z);
  if(length(x)**2<=1e-10)x=cross(Math.abs(z.y)<.9?{x:0,y:1,z:0}:{x:1,y:0,z:0},z);
  x=normalized(x,{x:1,y:0,z:0});
  return {right:x,up:normalized(cross(z,x),{x:0,y:1,z:0}),forward:z};
}

/** All eight table rows share the same constructor and flight/shrink state machine. */
function createPoweredPort(port:PoweredSecondaryPort,pos:PoweredVec3,aimDelta:PoweredVec3,
  axis:PoweredVec3,ownerScale:number,randomByte:()=>number,onLaunch?:PoweredLaunchSink,cause:'normal'|'split'='normal'):PoweredSecondaryState[]{
  const {right:x,up:y,forward:z}=poweredLaunchBasis(aimDelta,axis);
  const theta=Math.PI*([2,1,4,4,2,1,4,4][port]!)/16;
  let azimuth=(Math.PI/2)*(((randomByte()&15)+1)/16);
  const result:PoweredSecondaryState[]=[];
  for(let i=0;i<4;i++){
    // Columns of baseBasis * Rz(azimuth) * Rx(theta).
    const radial=add(mul(x,-Math.sin(azimuth)),mul(y,Math.cos(azimuth)));
    const direction=add(mul(radial,-Math.sin(theta)),mul(z,Math.cos(theta)));
    const reference=add(mul(radial,Math.cos(theta)),mul(z,Math.sin(theta)));
    const factor=((randomByte()&7)+9)/16,speed=40*factor;
    result.push({kind:'secondary',port,pos:copy(pos),vel:mul(direction,speed),direction,reference,speed,acceleration:-factor,life:40,scale:ownerScale,alpha:1,spin:0,phase:'flight'});
    azimuth+=Math.PI/2;if(azimuth>Math.PI)azimuth-=Math.PI*2;
  }
  // 8016d584 copies this UNSPLAYED base into all children, then flashes before
  // 8016d9ac applies each child's Rz/Rx spread. Not the fourth child's direction.
  onLaunch?.({cause,pos:copy(pos),basis:{right:copy(x),up:copy(y),forward:copy(z)}});
  return result;
}

/** Use on source collision/bounds termination as well as natural life expiry. */
export function beginPoweredSecondaryShrink(input:PoweredSecondaryState):PoweredSecondaryState {
  return {...input,phase:input.phase==='expired'?'expired':'shrink',vel:{x:0,y:0,z:0}};
}
export function stepPoweredSecondary(input:PoweredSecondaryState):{state:PoweredSecondaryState;alive:boolean}{
  let state={...input,pos:copy(input.pos),vel:copy(input.vel)};
  if(state.phase==='expired')return {state,alive:false};
  if(state.phase==='shrink'){
    state.scale*=.8;if(state.scale<.001)state.phase='expired';
    return {state,alive:state.phase!=='expired'};
  }
  state.life--;
  if(state.life<=0)return {state:beginPoweredSecondaryShrink(state),alive:true};
  state.spin=wrap(state.spin+0x1400*Math.PI/32768);
  state.direction=normalized(state.direction,{x:0,y:1,z:0});
  state.vel=mul(state.direction,state.speed);state.pos=add(state.pos,state.vel);
  state.speed=Math.max(.05,state.speed+state.acceleration);
  return {state,alive:true};
}

/** Static bind translation only: animated attachment matrices remain an integration gap. */
export function poweredPrimaryMuzzle(row:Exclude<PoweredPrimaryRow,4>,ownerPos:PoweredVec3,yaw:number,ownerScale=1):PoweredVec3 {
  const right=row===7||row===9;
  const local={x:(right?67.59280443191528:-67.59277391433716)+(right?118:-118),y:(right?136.1260986328125:136.12603759765625)+(row>=8?-22:36),z:(right?-.00001393718:-.00000385384)+30};
  return add(ownerPos,{x:(local.x*Math.cos(yaw)+local.z*Math.sin(yaw))*ownerScale,y:local.y*ownerScale,z:(-local.x*Math.sin(yaw)+local.z*Math.cos(yaw))*ownerScale});
}

/** Rows0..3 use the same static joints as the primaries but upper y offset is16, not36. */
export function poweredNormalMuzzle(port:PoweredNormalPort,ownerPos:PoweredVec3,yaw:number,ownerScale=1):PoweredVec3 {
  const row=([6,7,8,9] as const)[port];
  const muzzle=poweredPrimaryMuzzle(row,ownerPos,yaw,ownerScale);
  if(port<2)muzzle.y-=20*ownerScale;
  return muzzle;
}
