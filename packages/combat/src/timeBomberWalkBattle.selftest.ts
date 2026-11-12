/** Actual-input tests for bounded pl0106 established grounded running X.
 * Real movement/special edges drive admission. Positions only establish fixtures.
 * Host collision, static muzzle pose, and air physics are not full source parity. */
import { enterHit, enterDown } from './combat.js';
import { timeBomberDirectionForYaw, timeBomberTargetYaw } from './timeBomberCommand.js';
import { battleStateForSelfcheck, createBattle } from './battle.js';
import { RomDriverBridge } from './bridge.js';
import { emptyInput, type StageCollision } from './types.js';
import type { BorgStats } from './stats.js';
import { type TimeBomberAction } from './families/time-bomber.js';
import type { Vec3 } from './rom/actor.js';
import borgsData from '../../assets/data/borgs.json' with { type: 'json' };
const stats = (borgsData as { borgs: BorgStats[] }).borgs;
const v = (x: number, y: number, z: number): Vec3 => ({ x, y, z });
function assert(value: unknown, message: string): asserts value {
  if (!value) throw new Error(`[timeBomberWalkBattle] ${message}`);
}
function floor(wallZ?: number): StageCollision {
  const vertices: [Vec3, Vec3, Vec3][] = [
    [v(-20000, 0, -20000), v(20000, 0, -20000), v(20000, 0, 20000)],
    [v(-20000, 0, -20000), v(20000, 0, 20000), v(-20000, 0, 20000)],
  ];
  if (wallZ !== undefined) vertices.push([v(-5000, -1000, wallZ), v(5000, -1000, wallZ), v(0, 5000, wallZ)]);
  return { triangles: vertices.map((points, index) => ({ index, layerIndex: 0, marker: 0xcccccccc,
    vertices: points, normal: index === 2 ? v(0, 0, -1) : v(0, 1, 0), planeD: 0,
    bounds2d: { minX: -20000, maxX: 20000, minZ: -20000, maxZ: 20000 },
  })) };
}
function setup(id = 'pl0106', wallZ?: number, extraTarget = false) {
  const battle = createBattle({ stageId: 'st00', bounds: { x: 20000, z: 20000 }, collision: floor(wallZ), forces: [
    { team: 0, ownerPlayer: 'p1', borgIds: [id] },
    { team: 1, ownerPlayer: 'p2', borgIds: ['pl0615'] },
    ...(extraTarget ? [{ team: 1, ownerPlayer: 'p3', borgIds: ['pl0615'] }] : []),
  ] }, stats);
  const inputs = { p1: emptyInput(), p2: emptyInput(), p3: emptyInput() };
  for (let i = 0; i < 100; i++) battle.step(1 / 60, inputs);
  const state = battleStateForSelfcheck(battle);
  const owner = state.borgs.find(b => b.ownerPlayer === 'p1')!;
  const target = state.borgs.find(b => b.ownerPlayer === 'p2')!;
  const other = state.borgs.find(b => b.ownerPlayer === 'p3');
  assert(owner.romDriver instanceof RomDriverBridge, `${id}: live family bridge`);
  const driver = owner.romDriver;
  owner.pos = v(0, 10, 0); owner.vel = v(0, 0, 0); owner.rotY = 0; owner.grounded = true;
  target.pos = v(0, 10, 4000); target.vel = v(0, 0, 0); owner.lockTarget = target.uid;
  if (other) { other.pos = v(3000, 10, 4000); other.vel = v(0, 0, 0); }
  for (let i = 0; i < 4; i++) battle.step(1 / 60, inputs);
  let elapsed = 0;
  const cues: number[] = []; battle.onRomCue = cue => cues.push(cue);
  const events: { frame: number; address: number; row: number }[] = [];
  const allocations: { frame: number; slot: number; count: number; mode: number | undefined; accepted: boolean }[] = [];
  const spawn = driver.ctx.onFamilyProjectile!;
  driver.ctx.onFamilyProjectile = (actor, address, row) => {
    events.push({ frame: elapsed, address, row }); spawn(actor, address, row);
  };
  const allocate = driver.ctx.onAllocateResource!;
  driver.ctx.onAllocateResource = (actor, slot, count, mode) => {
    const accepted = allocate(actor, slot, count, mode);
    allocations.push({ frame: elapsed, slot, count, mode, accepted }); return accepted;
  };
  const tick = () => { elapsed++; return battle.step(1 / 60, inputs); };
  const press = () => { inputs.p1.special = true; return tick(); };
  const release = () => { inputs.p1.special = false; return tick(); };
  return { battle, state, owner, target, other, driver, inputs, events, allocations, cues, tick, press, release, get frame() { return elapsed; } };
}
type Fixture = ReturnType<typeof setup>;
function shots(t: Fixture) { return t.state.projectiles.filter(p => p.ownerUid === t.owner.uid); }

function stream(t: Fixture): TimeBomberAction | undefined {
  return (t.driver.actor as typeof t.driver.actor & { timeBomberAction?: TimeBomberAction }).timeBomberAction;
}
function run(t: Fixture, x = 0, z = 1): void {
  t.inputs.p1.moveX=x; t.inputs.p1.moveZ=z;
  for(let i=0;i<12;i++) t.tick();
  assert(t.owner.grounded && t.owner.state==='move', `real stick establishes grounded run, got ${t.owner.state}`);
}
function admit(t: Fixture, variant = 1): void {
  t.press();
  assert(t.owner.command?.exact && t.owner.command.type===2 && t.owner.command.actionIndex===0 &&
    t.owner.command.variantIndex===variant && t.owner.command.subtype===1,
    `actual established running X selects variant${variant}, got ${JSON.stringify(t.owner.command)}`);
  assert(t.driver.actor.fbCue===44 && (t.driver.actor.controlWord&3)===(variant===1?1:3),
    'ground running record preserves cue44 and source ownership mode');
  assert(stream(t)?.stage==='windup' && (variant!==1 || stream(t)?.mask===1), 'dedicated moving source stream owns part0');
  assert(t.events.length===0 && shots(t).length===0 && t.allocations.length===0, 'no admission debit or generic shot');
}
function finishLaunch(t: Fixture): void {
  for(let i=0;i<30 && !t.events.length;i++) t.tick();
  assert(t.events.length===1 && t.events[0]!.address===0x800fe668 && t.events[0]!.row===2, 'one original row2 source launch');
  assert(shots(t).length===1 && shots(t)[0]!.timeBomberSource?.kind==='primary', 'one dedicated primary, no generic duplicate');
  assert(t.allocations.length===1 && t.allocations[0]!.slot===2 && t.allocations[0]!.count===1 && t.allocations[0]!.accepted,
    'exactly one consuming slot2 allocation');
}
function testPairedRunAndStop(): void {
  for(const [x,z] of [[0,1],[1,0],[-1,0]] as const) {
    const active=setup(), control=setup(); run(active,x,z);run(control,x,z);
    admit(active);control.tick();
    for(let i=0;i<70;i++) {
      for(const axis of ['x','y','z'] as const) {
        assert(Math.abs(active.owner.pos[axis]-control.owner.pos[axis])<1e-6, `paired run position ${axis}, tick${i}, stick${x}/${z}`);
        assert(Math.abs(active.owner.vel[axis]-control.owner.vel[axis])<1e-6, `paired run velocity ${axis}, tick${i}, stick${x}/${z}`);
      }
      assert(active.owner.grounded===control.owner.grounded, 'no duplicate gravity or floor integration');
      if(i===10) {active.inputs.p1.moveX=control.inputs.p1.moveX=0;active.inputs.p1.moveZ=control.inputs.p1.moveZ=0;}
      active.tick();control.tick();
    }
    assert(active.events.length===1 && active.allocations.length===1, 'held X only launches once while running/stopping');
    assert(!active.owner.cooldowns['romSpecialActive'] && active.owner.state!=='special', 'natural stop and source recovery release ownership');
  }
}
function testAmmoAndEdges(): void {
  const t=setup();run(t);const cell=t.owner.weaponCells![1]!, b=t.owner.weaponCells![0]!.cur;
  cell.cur=1;cell.timer=cell.refillParam*(cell.max-1);admit(t);finishLaunch(t);
  assert(cell.cur===0 && cell.timer===cell.refillParam*cell.max-4 && t.owner.weaponCells![2]===cell && t.owner.weaponCells![0]!.cur===b,
    'single remaining round consumes alias once, adds debt300 and preserves B');
  for(let i=0;i<100;i++)t.tick();
  assert(t.events.length===1, 'holding X through recovery does not repeat');
  t.release();t.press();for(let i=0;i<50;i++)t.tick();
  assert(t.events.length===1 && t.allocations.length===1, `empty re-press creates no source or generic shot: events=${t.events.length}, allocations=${JSON.stringify(t.allocations)}, cell=${cell.cur}/${cell.timer}`);
  t.release();for(let i=0;i<400 && cell.cur<1;i++)t.tick();t.press();
  for(let i=0;i<40 && t.events.length<2;i++)t.tick();
  assert(Number(t.events.length)===2 && Number(t.allocations.length)===2, 'refilled release/repress launches once more');
}
function testTargetCases(): void {
  const absent=setup();absent.target.hp=0;absent.target.state='death';absent.target.stateTime=0;
  run(absent);admit(absent);finishLaunch(absent);
  assert(absent.owner.timeBomberSavedAim?.targetUid===null && shots(absent)[0]!.aimedTargetUid===null, 'targetless running X remains unguided');
  const changed=setup('pl0106',undefined,true);run(changed);admit(changed);
  changed.inputs.p1.switchLock=true;changed.inputs.p2.moveX=1;changed.tick();changed.inputs.p1.switchLock=false;
  finishLaunch(changed);
  assert(changed.owner.targetLockState?.activeTargetUid===changed.other!.uid && shots(changed)[0]!.aimedTargetUid===changed.target.uid,
    'real lock switch during windup preserves captured source target identity');
  assert(changed.owner.timeBomberSavedAim!.pos.x===changed.target.sourceFramePose!.pos.x && changed.owner.timeBomberSavedAim!.pos.x!==0,
    'running shot refreshes captured target from shared pre-movement pose');
  const rotated=setup();rotated.owner.rotY=Math.PI/2;rotated.target.pos=v(4000,10,0);run(rotated,1,0);assert(Math.abs(rotated.owner.rotY)>1,'nonzero-heading fixture retains rotated root');admit(rotated);finishLaunch(rotated);
  for(const sign of [-1,1]) {
    const side=setup();run(side);side.target.pos=v(sign*4000,10,side.owner.pos.z);admit(side);finishLaunch(side);
  }
  const behind=setup();run(behind);behind.target.pos=v(0,10,-4000);admit(behind,0);finishLaunch(behind);
}
function testReleasedRecoveryClock(): void {
  const t=setup();run(t);const start=t.frame;admit(t);
  t.inputs.p1.moveZ=0;
  for(let age=2;age<=42;age++) {
    t.tick();
    if(age===25)assert(stream(t)?.stage==='wait' && stream(t)?.wait===8, 'released running stream retains END20 then realtime wait8');
    if(age===33)assert(stream(t)?.stage==='tail' && stream(t)?.frame===1, 'released running stream starts tail with immediate update');
    if(age===41)assert(stream(t)?.stage==='tail' && stream(t)?.frame===9, 'released running stream retains original END9');
    if(age===42)assert(!t.owner.cooldowns['romSpecialActive'], 'released running stream ends at source recovery boundary');
  }
  assert(t.frame===start+42 && t.events.length===1 && t.allocations.length===1,'release does not drop or duplicate pending shot');
}
function testDeathAndExcludedStates(): void {
  const dead=setup();run(dead);admit(dead);const before=dead.owner.weaponCells![1]!.cur;
  dead.owner.hp=0;dead.owner.state='death';dead.owner.stateTime=0;for(let i=0;i<60;i++)dead.tick();
  assert(dead.events.length===0 && dead.allocations.length===0 && shots(dead).length===0 && dead.owner.weaponCells![1]!.cur===before,
    'death during moving windup cancels pending release without ammo debit');
  assert(!dead.owner.cooldowns['romSpecialActive'] && dead.owner.state==='death','death cannot restore stale locomotion');
  const dash=setup();run(dash);dash.inputs.p1.dash=true;dash.tick();dash.press();for(let i=0;i<60;i++)dash.tick();
  assert(dash.events.length===0 && !shots(dash).some(p=>p.timeBomberSource) && stream(dash)?.mask!==1,`dash X remains outside bounded running source action: events=${JSON.stringify(dash.events)}, shots=${shots(dash).length}, command=${JSON.stringify(dash.owner.command)}`);
  const coast=setup();run(coast);coast.inputs.p1.moveZ=0;coast.tick();coast.press();
  assert(coast.owner.command?.variantIndex!==1 && stream(coast)?.mask!==1, 'released-stick coasting never enters running part0 lane');
  const first=setup();first.inputs.p1.moveZ=1;first.press();for(let i=0;i<30;i++)first.tick();
  assert(first.events.length===0 && !shots(first).some(p=>p.timeBomberSource) && stream(first)?.mask!==1,'simultaneous first movement/X remains unproven and excluded');
}
function testFollowupNeutralAndAir(): void {
  for(const air of [false,true]) {
    const t=setup();run(t);const previousMovement=t.driver.actor.controlWord&0x30;
    admit(t);finishLaunch(t);
    t.inputs.p1.moveZ=0;t.release();
    for(let i=0;i<100;i++)t.tick();
    assert(!t.owner.cooldowns['romSpecialActive'] && (t.driver.actor.controlWord&0x30)===previousMovement,
      'running source recovery restores prior movement control bits');
    if(air) {t.inputs.p1.jump=true;t.tick();t.inputs.p1.jump=false;for(let i=0;i<3;i++)t.tick();assert(!t.owner.grounded,'follow-up real jump is airborne');}
    t.press();
    assert(t.owner.command?.variantIndex===(air?3:0) && (t.driver.actor.controlWord&3)===(air?1:3),
      `running then ${air?'air':'neutral'} X does not inherit stale running command/control`);
    for(let i=0;i<30 && t.events.length<2;i++)t.tick();
    assert(Number(t.events.length)===2 && Number(t.allocations.length)===2,'follow-up source action launches once with fresh command');
  }
}
function testWindupBehindRedispatch(): void {
  const t=setup('pl0106',undefined,true), control=setup('pl0106',undefined,true);
  run(t);run(control);admit(t);control.tick();
  for(const f of [t,control]) { f.target.pos=v(0,10,-4000);f.inputs.p1.switchLock=true; }
  t.tick();control.tick();t.inputs.p1.switchLock=false;
  assert(t.driver.actor.variantIndex===0 && (t.driver.actor.controlWord&3)===3 && t.driver.actor.fbPhaseSlots[0]===0,
    'moving windup target behind redispatches ground variant0 without same-frame initialization');
  assert(t.owner.timeBomberSavedAim?.targetUid===t.other!.uid,'redispatch recaptures newly selected target after actual R switch');
  for(const axis of ['x','y','z'] as const)
    assert(Math.abs(t.owner.pos[axis]-control.owner.pos[axis])<1e-6,'redispatch frame keeps exactly one paired host movement update');
  assert(t.events.length===0 && t.allocations.length===0,'redispatch neither releases nor allocates early');
  const before={...t.owner.pos}, previous={...t.driver.actor.savedGroundPos};
  t.tick();
  for(const axis of ['x','y','z'] as const)
    assert(Math.abs(t.owner.pos[axis]-(before[axis]+(before[axis]-previous[axis])*Math.fround(.95)))<1e-6,
      `ground fallback initialization applies exactly one source carry ${axis}`);
  assert(stream(t)?.mask!==1 && Number(t.driver.actor.fbPhaseSlots[0])===1,'next update initializes whole-body ground source action');
  finishLaunch(t);
  assert(shots(t)[0]!.aimedTargetUid===t.other!.uid,'ground redispatch launch uses recaptured target identity');
}
/** Host lifecycle injection tests ownership priority, not original hit geometry. */
function testHitAndDownInterruption(): void {
  for(const kind of ['hit','down'] as const) {
    const t=setup();run(t);const movement=t.driver.actor.controlWord&0x30;admit(t);const ammo=t.owner.weaponCells![1]!.cur;
    if(kind==='hit')enterHit(t.owner,20);else enterDown(t.owner,40);
    t.inputs.p1.moveZ=0;t.tick();
    assert(t.owner.state===kind && !t.owner.cooldowns['romSpecialActive'] && (t.driver.actor.controlWord&0x30)===movement,
      `${kind} interruption keeps reaction ownership and restores scoped movement control`);
    for(let i=0;i<70;i++)t.tick();
    assert(t.events.length===0 && t.allocations.length===0 && t.owner.weaponCells![1]!.cur===ammo && !shots(t).some(p=>p.timeBomberSource),
      `${kind} interruption clears pending shot without debit or held-X replay`);
  }
}
/** Synthetic classifier adjunct, separate from the real-input tests above. */
function testExactDirectionBoundaries(): void {
  const cases: [number,number][]=[[-0x8000,2],[-0x5001,2],[-0x5000,3],[-0x4fff,3],[-0x2801,3],[-0x2800,0],[-0x27ff,0],
    [0,0],[0x27ff,0],[0x2800,0],[0x2801,1],[0x4fff,1],[0x5000,1],[0x5001,2],[0x7fff,2]];
  for(const [angle,want] of cases)assert(timeBomberDirectionForYaw(angle)===want,`strict signed direction boundary ${angle}`);
  const root={pos:v(100,10,-200),rotY:0};
  for(const sign of [-1,1]) {
    const angle=sign*(0x2800+0.75)*2*Math.PI/0x10000;
    const target={pos:v(root.pos.x+4000*Math.sin(angle),10,root.pos.z+4000*Math.cos(angle))};
    const yaw=timeBomberTargetYaw(root,target);
    assert(yaw===sign*0x2800 && timeBomberDirectionForYaw(yaw)===0,'f32 angle conversion truncates fractional BAM toward zero rather than rounding');
  }
  const rotated={pos:v(100,10,-200),rotY:Math.PI/2};
  assert(timeBomberTargetYaw(rotated,{pos:v(4100,10,-200)})===0,'inverse rotated root makes world +X target forward');
  assert(timeBomberTargetYaw(rotated,null)===0,'missing target classifier defaults forward');
  assert(timeBomberTargetYaw(root,{pos:v(100,10,-4200)})===32767,'positive pi source signed-short conversion saturates');
}
export function runTimeBomberWalkBattleSelfTest(): void {
  testExactDirectionBoundaries();testPairedRunAndStop();testAmmoAndEdges();testTargetCases();testReleasedRecoveryClock();testDeathAndExcludedStates();testFollowupNeutralAndAir();testWindupBehindRedispatch();testHitAndDownInterruption();
  console.log('Time Bomber bounded grounded running X Battle integration: passed');
}
