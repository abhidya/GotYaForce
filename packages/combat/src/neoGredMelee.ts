/** Bounded fresh grounded G RED0/1/2, NEO25/26 -> v6, BLACK13/14/15 chains.
 * Source177dd8/cfg80365634(RED)/80365664(NEO)/8036564c(BLACK), callback18ded0 and
 * 179280/cfg803657c4 for NEO only.
 * This is admission-owned state, not a replacement for every G RED variant.
 * Host target roots, terrain and the bridge's root HIT envelope remain explicit
 * approximations; state/stream/input/control flow is separately source-backed.
 */
import type { RomActor, Vec3 } from './rom/actor.js';
import { startStream, tickStream, type StreamContext } from './rom/stream-vm.js';
import { dispatchCommandRecord } from './rom/dispatch.js';
import { stepTargetYaw, stepAfterimage, toS16, type RomHelperScratch } from './rom/helpers.js';
import { integratePhysicsPrimary, projectX, projectZ } from './rom/physics.js';
import { romAirKnockoutReturn, romGroundIdleReturn } from './families/shared-idle-return.js';
import { tickNeoGredFinisher, dampNeoGredFinisher, NEO_GRED_FINISHER_CONFIG,
  type NeoGredFinisherState, type NeoGredFinisherHooks } from './families/neo-gred-finisher.js';
import { commandMoveRecordsForBorgButton } from './commandMoveTables.js';
import { G_RED_NEUTRAL_MELEE_CONFIG, gredMeleeStreamConfig } from './gredMeleeConfig.js';
import { G_BLACK_NEUTRAL_MELEE_CONFIG, gblackMeleeStreamConfig } from './gblackMeleeConfig.js';
import { createNeoMeleeStream, tickNeoMeleeStream, type NeoMeleeStream } from './neoMeleeStream.js';

const f32 = Math.fround;
const s8 = (n: number) => (n << 24) >> 24;
const NEO_CONFIG = Object.freeze({ seed: 25, timer: 20, range: 150, decel: f32(.95), redirectFinisher: true });
const RED_CONFIG = Object.freeze({ seed: G_RED_NEUTRAL_MELEE_CONFIG.seedSlot,
  timer: G_RED_NEUTRAL_MELEE_CONFIG.timerFrames, range: G_RED_NEUTRAL_MELEE_CONFIG.proximityRange,
  decel: G_RED_NEUTRAL_MELEE_CONFIG.decel, redirectFinisher: false });
const BLACK_CONFIG = Object.freeze({ seed: G_BLACK_NEUTRAL_MELEE_CONFIG.seedSlot,
  timer: G_BLACK_NEUTRAL_MELEE_CONFIG.timerFrames, range: G_BLACK_NEUTRAL_MELEE_CONFIG.proximityRange,
  decel: G_BLACK_NEUTRAL_MELEE_CONFIG.decel, redirectFinisher: false });
type Actor = RomActor & RomHelperScratch & {
  targetDistance760?: number; grounded?: boolean;
  actionMode5e4?: number; airborne87?: number; return590?: number;
  return690?: number; return71b?: number;
  movementTrailFlag1d9b?: number; launchYaw1db0?: number; launchSpeed1dac?: number;
};
/** Properties backed by RomActor are accessors, so hook writes are visible within
 * the same dispatch. Scratch and observation counters are per admitted action. */
export class NeoGredMeleeState implements NeoGredFinisherState {
  constructor(readonly actor: Actor, public targetUid: string | null) {
    this.family = actor.borgNumber === 0x615 ? 'red' : actor.borgNumber === 0x62a ? 'black' : 'neo';
    this.config = this.family === 'red' ? RED_CONFIG : this.family === 'black' ? BLACK_CONFIG : NEO_CONFIG;
  }
  readonly family: 'red' | 'neo' | 'black';
  readonly config: typeof NEO_CONFIG | typeof BLACK_CONFIG | typeof RED_CONFIG;
  groundWaveCount = 0;
  stream: NeoMeleeStream | null = null;
  streamMask = 0;
  pendingContact = 0;
  acceptedContactCount = 0;
  launchCount = 0;
  /** Raw omitted-opcode state. Full presentation/contact-slow consumers are
   * not bound by this lane, rather than assigning invented gameplay meanings. */
  flags57b = 0;
  flags6e8 = 0;
  flags6e9 = 0;
  contactFlags709 = 0;
  equipment1d74 = 0;
  equipment1d75: number | null = null;
  onRedispatchTarget: (() => void) | undefined;
  noTargetLatch541 = 0;
  retap746 = 0;
  alt745 = 0;
  input1d9 = 0;
  hold71c = 0;
  /** No live host1dd adapter yet; only explicit source callers may supply this. */
  forceRange1dd80 = false;
  get target(): object | null { return this.actor.lockTarget ?? null; }
  set target(value: object | null) { this.actor.lockTarget = value as Vec3 | null; }
  get phase() { return this.actor.fbPhaseSlots[0] ?? 0; }
  set phase(v: number) { this.actor.fbPhaseSlots[0] = v; }
  get shift18da() { return this.actor.steerYaw; }
  set shift18da(v: number) { this.actor.steerYaw = v; }
  get rangeRow868() { return this.actor.actionSpeedRows[s8(this.actor.prevActionIndex) % 3] ?? 0; }
  get targetDistance760() { return this.actor.targetDistance760 ?? 0; }
  get dashStrength1d0f() { return this.actor.dashStrength1d0f; }
  set dashStrength1d0f(v: number) { this.actor.dashStrength1d0f = v; }
  get activeYaw() { return this.actor.activeYaw; }
  set activeYaw(v: number) { this.actor.activeYaw = v; }
  get lockYaw() { return this.actor.lockYaw; }
  set lockYaw(v: number) { this.actor.lockYaw = v; }
  get handlerTimer() { return this.actor.handlerTimer; }
  set handlerTimer(v: number) { this.actor.handlerTimer = v; }
  get pos() { return this.actor.pos; }
  get savedGroundPos() { return this.actor.targetCache5e8; }
  get motion() { return this.actor.motion; }
  get hSpeed() { return this.actor.hSpeed; }
  set hSpeed(v: number) { this.actor.hSpeed = v; }
  get yVel() { return this.actor.yVel; }
  set yVel(v: number) { this.actor.yVel = v; }
  get hDecel() { return this.actor.hDecel; }
  set hDecel(v: number) { this.actor.hDecel = v; }
  get gravityCoeff() { return this.actor.gravityCoeff; }
  set gravityCoeff(v: number) { this.actor.gravityCoeff = v; }
  get blendFloor80c() { return this.actor.accumulator80c; }
  set blendFloor80c(v: number) { this.actor.accumulator80c = v; }
  get inputEdges5d4() { return this.actor.inputEdge5d4; }
  set inputEdges5d4(v: number) { this.actor.inputEdge5d4 = v; }
  get contactP0() { return this.actor.contactP0; }
  set contactP0(v: number) { this.actor.contactP0 = v; }
  get contactP1() { return this.actor.contactP1; }
  set contactP1(v: number) { this.actor.contactP1 = v; }
  get streamHold1b03() { return this.actor.streamHold1b03; }
  set streamHold1b03(v: number) { this.actor.streamHold1b03 = v; }
  get wallContact() { return this.actor.wallContact; }
  set wallContact(v: number) { this.actor.wallContact = v; }
  get actionFlag73f() { return this.actor.housekeeping73f; }
  set actionFlag73f(v: number) { this.actor.housekeeping73f = v; }
  get controlWord() { return this.actor.controlWord; }
  set controlWord(v: number) { this.actor.controlWord = v; }
  get dt() { return this.actor.dt; }
}
const states = new WeakMap<RomActor, NeoGredMeleeState>();
export function getNeoGredMeleeState(actor: RomActor): NeoGredMeleeState | undefined { return states.get(actor); }
export function prepareNeoGredMelee(actor: RomActor, targetUid: string | null): NeoGredMeleeState {
  const state = new NeoGredMeleeState(actor, targetUid); states.set(actor, state); return state;
}
export function clearNeoGredMelee(actor: RomActor): void { states.delete(actor); }
export function acceptNeoGredMeleeContact(actor: RomActor, admitted: NeoGredMeleeState): void {
  if (states.get(actor) !== admitted) return;
  admitted.pendingContact |= 0x10; admitted.acceptedContactCount++;
}
/** The source list writes transient1d9 after actor updates, consumed next tick. */
export function beginNeoGredMeleeTick(actor: RomActor): void {
  const state = states.get(actor); if (!state) return;
  state.input1d9 = state.pendingContact; state.pendingContact = 0;
}
/** Source66838/668cc: null=-1, forced1dd80=1; root target coordinates are
 * the host's bound +518/+64 surfaces, not animated console target-object bones. */
function range(s: NeoGredMeleeState, distance: number, threeD: boolean): number {
  if (!s.target) return -1;
  if (s.forceRange1dd80) return 1;
  const target = s.target as Vec3;
  return Math.hypot(target.x-s.pos.x, threeD ? target.y-s.pos.y : 0, target.z-s.pos.z)
    <= distance*s.actor.modelScale ? 1 : 0;
}
function groundProbe(a: Actor): void {
  const result = a.physicsRuntime?.probeMotion?.(a.savedGroundPos, a.pos, a.yVel)
    ?? a.physicsRuntime?.clampToGround(a.pos, a.yVel);
  if (!result) return;
  if ('y' in result && typeof result.y === 'number') a.pos.y = result.y;
  a.yVel = result.velY; a.grounded = result.grounded;
}
/** Flat/root host adapter for670dc; unlike primary physics it neither integrates
 * yVel nor applies gravity. Source slope projection remains the host floor seam. */
function groundMove(a: Actor, yaw: number): void {
  const scale = a.timescale*a.tierScale;
  a.pos.x += a.hSpeed*projectX(yaw)*scale;
  a.pos.z += a.hSpeed*projectZ(yaw)*scale;
  a.hSpeed = Math.max(0, a.hSpeed + a.hDecel*a.timescale);
  groundProbe(a);
}
function trail0(): void { /* b2190(mode0) cosmetic child allocation is not rendered here. */ }
function afterimage(a: Actor): void {
  if (Math.hypot(a.pos.x-a.targetCache5e8.x,a.pos.y-a.targetCache5e8.y,a.pos.z-a.targetCache5e8.z)>3) stepAfterimage(a);
}
function hooks(s: NeoGredMeleeState, ctx: StreamContext): NeoGredFinisherHooks {
  const a=s.actor;
  return {
    range66838: (_state, r) => range(s,r,false),
    face6d144: () => stepTargetYaw(a,0xc0,0,true) ? 1 : 0,
    tickStream: (_state,mask) => tickStream(a,mask,ctx),
    startStream: (_state,mask,group,slot,rate) => startStream(a,mask,group,slot,rate),
    groundProbe677b0: () => groundProbe(a),
    groundMove670dc: (_state,yaw) => groundMove(a,yaw),
    physics67310: (_state,g,yaw) => integratePhysicsPrimary(g,a,yaw),
    setLaunch66530: () => { a.actionMode5e4=45; a.airborne87=1; a.controlWord|=0x40; a.grounded=false; s.launchCount++; },
    spawnTrailB2190: trail0,
    syncB22f4: () => { stepAfterimage(a); },
    airReturn6a5a4: () => {
      a.return590=1; a.return690=0; a.return71b=0;
      if(a.movementTrailFlag1d9b) {a.lockYaw=toS16((a.launchYaw1db0??0)+a.heading);a.hSpeed=a.launchSpeed1dac??0;}
      romAirKnockoutReturn(a);
    },
  };
}
function lunge(s: NeoGredMeleeState): void {
  const distance=s.target===null?s.rangeRow868:f32(f32(s.targetDistance760*s8(s.dashStrength1d0f))*.0625);
  s.hSpeed=f32(distance/s.config.timer);s.dashStrength1d0f=0;
}
function latch(s: NeoGredMeleeState): void {
  if(s.inputEdges5d4&0x40)s.retap746=1;
  if(s.input1d9!==0)s.alt745=1;
}
function redirectFinisher(s: NeoGredMeleeState): void {
  // 18ded0: full6a3d0 type1/subtype1 dispatch first, THEN variant6.
  const record=commandMoveRecordsForBorgButton('pl0629','B Attack').find(r=>r.commandType===1&&r.subtype===1);
  if(!record)throw Error('Missing verified NEO command type1/subtype1');
  s.actor.cmdButton=1;s.actor.cmdSubtype=1;s.actor.cmdChargedRanged=0;
  dispatchCommandRecord(s.actor,record);
  s.actor.variantIndex=6;s.noTargetLatch541=0;
  s.onRedispatchTarget?.();
}
export function stepNeoGredMelee(actor: RomActor, ctx: StreamContext): void {
  const s=states.get(actor);if(!s)return;
  if((actor.borgNumber!==0x615&&actor.borgNumber!==0x629&&actor.borgNumber!==0x62a)||actor.actionIndex!==1)return;
  if(s.noTargetLatch541!==0)s.target=null;
  // Wrappers18de34/18de68/18de9c/18e1f4 halve signed18da. Finisher179280 also halves
  // it inside the shared engine, so variant6 intentionally receives TWO shifts.
  actor.steerYaw=toS16(actor.steerYaw)>>1;
  if(s.family==='neo'&&actor.variantIndex===6){tickNeoGredFinisher(s,NEO_GRED_FINISHER_CONFIG,hooks(s,ctx));return;}
  if(actor.variantIndex!==0)return;
  const a=s.actor;
  switch(s.phase) {
    case 0:
      s.phase++;s.retap746=s.alt745=0;a.streamSlot=s.config.seed;
      if(range(s,s.rangeRow868,false)<1){s.noTargetLatch541=1;s.target=null;a.activeYaw=a.lockYaw=a.heading;}
      s.handlerTimer=60;stepTargetYaw(a,0xc0,0,true);
      startStream(a,15,3,a.streamSlot++,-1);a.accumulator80c=0;return;
    case 1:
      if(a.streamHold1b03!==0)tickStream(a,15,ctx);
      s.handlerTimer=f32(s.handlerTimer-a.dt);
      if(s.handlerTimer<=0||stepTargetYaw(a,0xc0,0,true)){s.phase++;s.handlerTimer=s.config.timer;lunge(s);trail0();}
      return;
    case 2:
      latch(s);stepTargetYaw(a,0xc0,0,true);dampNeoGredFinisher(s,s.config.decel);groundMove(a,a.lockYaw);
      if(a.contactP0===0)tickStream(a,15,ctx);
      s.handlerTimer=f32(s.handlerTimer-a.dt);
      if(s.handlerTimer<=0||range(s,s.config.range,true)!==0)s.phase++;
      afterimage(a);return;
    case 3:
      latch(s);tickStream(a,15,ctx);
      if(s8(a.contactP1)<0&&(s.retap746&s.alt745)!==0){
        if((a.contactP1&1)===0&&s.config.redirectFinisher){redirectFinisher(s);return;}
        s.phase--;s.retap746=s.alt745=0;s.handlerTimer=s.config.timer;
        startStream(a,15,3,a.streamSlot++,-1);lunge(s);trail0();return;
      }
      if(a.faceGate1d10!==0)stepTargetYaw(a,0xc0,0,true);
      if(a.dashStrength1d0f!==0)lunge(s);
      dampNeoGredFinisher(s,s.config.decel);
      if(s.targetDistance760<s.config.range)dampNeoGredFinisher(s,0);
      groundMove(a,a.lockYaw);
      if(a.wallContact!==0){a.housekeeping73f=0;a.controlWord&=~3;romGroundIdleReturn(a);}
      afterimage(a);return;
  }
}
/** Bridge start hook: source parts0/1 only write their own authored fields. */
export function startNeoGredMeleeStream(actor: RomActor, group: number, slot: number, mask: number, ctx: StreamContext): boolean {
  const s=states.get(actor);
  if(!s||group!==3)return false;
  const red=s.family==='red'?gredMeleeStreamConfig(slot):undefined;
  const black=s.family==='black'?gblackMeleeStreamConfig(slot):undefined;
  const scoped=red??black;
  if(s.family==='red'){if(!red||actor.variantIndex!==0)return false;}
  else if(s.family==='black'){if(!black||actor.variantIndex!==0)return false;}
  else if((slot!==25&&slot!==26&&slot!==27)||(actor.variantIndex===0&&slot===27)||(actor.variantIndex===6&&slot!==27))return false;
  if(slot!==0&&slot!==1&&slot!==2&&slot!==13&&slot!==14&&slot!==15&&slot!==25&&slot!==26&&slot!==27)return false;
  s.stream=createNeoMeleeStream(slot,actor.dt);s.streamMask=mask&actor.weaponPartMask;
  if(s.streamMask&1)actor.streamHold1b03=s.stream.blendMode;
  if(s.streamMask&1){
    actor.wallContact=0;actor.contactP0=red?.initialContact??(slot===27?1:0);actor.contactP1=0;
    actor.defaultGroup=0;s.flags6e8=black||slot===27?2:0;s.flags6e9=0;
    if(red?.setFlags57b40)s.flags57b|=0x40;
    if(slot===27){s.flags57b|=0x40;s.equipment1d74=3;}
    if(black){s.equipment1d74=3;s.equipment1d75=0;}
    ctx.onArmHit?.(actor,scoped?.hitKind??(slot===25?1:slot===26?2:8),scoped?.statusId??(slot===27?127:0),255);
  }
  if(s.streamMask&2){
    actor.dashStrength1d0f=scoped?.dashStrength??(slot===27?32:24);actor.faceGate1d10=1;
    // 4beb8 clears709 before source0b010400. Negative default equipment byte
    // needs page+bf, not the spawn layer's placeholder defaultHand1=0.
    s.contactFlags709=slot===27?4:1;
  }
  ctx.onPlayAnim?.(actor,3,scoped?.animSlot??(slot===25?0:slot===26?1:18),false);
  return true;
}
export function tickNeoGredMeleeStreamPart(actor: RomActor, index: number, ctx: StreamContext): boolean {
  const s=states.get(actor);if(!s?.stream||!(s.streamMask&(1<<index)))return false;
  // All four selected parts start identically; one canonical clock dispatches the
  // writes with their source masks. Subsequent part calls must not quadruple time.
  if(index!==(31-Math.clz32(s.streamMask&-s.streamMask)))return true;
  const event=tickNeoMeleeStream(s.stream,actor.dt);
  if(s.streamMask&1){
    actor.streamHold1b03=s.stream.blendMode;
    if(event.contact!==undefined)actor.contactP0=event.contact;
    if(event.aux!==undefined)actor.contactP1=event.aux;
    if(event.completed)actor.wallContact=1;
    if(event.flags6e8!==undefined)s.flags6e8=event.flags6e8;
    if(event.flags6e9!==undefined)s.flags6e9=event.flags6e9;
  }
  if(s.streamMask&2){
    if(event.clearDash){actor.dashStrength1d0f=0;actor.faceGate1d10=0;}
    if(event.control40)actor.controlWord=(actor.controlWord&~0xff0)|0x40;
    if(event.recovery||event.clearContactFlags)s.contactFlags709&=~0x1f;
  }
  // 18d1d8: ground-control bit and supporting-actor contact are distinct gates.
  if(event.groundWave&&(s.streamMask&1)&&(actor.controlWord&0x40)===0&&actor.supportContact1db===0){
    s.groundWaveCount++;ctx.onFamilyProjectile?.(actor,0x800fc208,5);
  }
  if(event.recovery)ctx.onPlayAnim?.(actor,0,14,false);
  if(event.completed)for(let i=0;i<actor.parts.length;i++)if(s.streamMask&(1<<i))actor.parts[i]!.streamPtr=-1;
  return true;
}
