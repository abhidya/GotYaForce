import { battleStateForSelfcheck, createBattle } from "./battle.js";
import { RomDriverBridge } from "./bridge.js";
import { STATE } from "./constants.js";
import type { AccelerationNinjaScratch } from "./families/acceleration-ninja.js";
import { emptyInput, type StageCollision, type StageCollisionTriangle } from "./types.js";
import type { BorgStats } from "./stats.js";
import borgsData from "../../assets/data/borgs.json" with { type: "json" };

function assert(value: unknown, message: string): asserts value {
  if (!value) throw new Error(`[romCollision.selftest] ${message}`);
}
const v = (x: number, y: number, z: number) => ({ x, y, z });
function triangle(index: number, vertices: StageCollisionTriangle["vertices"], normal: StageCollisionTriangle["normal"]): StageCollisionTriangle {
  return { index, layerIndex: 0, marker: 0xcccccccc, vertices, normal, planeD: 0,
    bounds2d: { minX: -1000, maxX: 1000, minZ: -1000, maxZ: 1000 } };
}
function geometry(wall: number | null = null, ceiling = false): StageCollision {
  const triangles = [
    triangle(0, [v(-1000, 0, -1000), v(1000, 0, -1000), v(1000, 0, 1000)], v(0, 1, 0)),
    triangle(1, [v(-1000, 0, -1000), v(1000, 0, 1000), v(-1000, 0, 1000)], v(0, 1, 0)),
  ];
  if (wall !== null) triangles.push(triangle(2, [v(-500, -500, wall), v(500, -500, wall), v(0, 1000, wall)], v(0, 0, -1)));
  if (ceiling) triangles.push(triangle(3, [v(-1000, 30, -1000), v(1000, 30, -1000), v(0, 30, 1000)], v(0, -1, 0)));
  return { triangles };
}
function setup(collision: StageCollision, id = "pl0004") {
  const battle = createBattle({ stageId: "st00", forces: [
    { team: 0, ownerPlayer: "p1", borgIds: [id] },
    { team: 1, ownerPlayer: "p2", borgIds: ["pl0008"] },
  ], bounds: { x: 1000, z: 1000 }, collision }, (borgsData as { borgs: BorgStats[] }).borgs);
  const inputs = { p1: emptyInput(), p2: emptyInput() };
  for (let i = 0; i <= STATE.SPAWN_DURATION; i++) battle.step(1 / 60, inputs);
  const state = battleStateForSelfcheck(battle);
  const borg = state.borgs.find(b => b.team === 0)!;
  const enemy = state.borgs.find(b => b.team === 1)!;
  borg.pos = v(0, 10, 0); borg.rotY = 0; borg.vel = v(0, 0, 0); borg.grounded = true;
  enemy.pos = v(0, 10, 800); borg.lockTarget = enemy.uid;
  assert(borg.romDriver instanceof RomDriverBridge, "live family bridge attached");
  const driver = borg.romDriver;
  const press = () => { inputs.p1.special = true; battle.step(1 / 60, inputs); inputs.p1.special = false; };
  const tick = () => battle.step(1 / 60, inputs);
  return { battle, borg, driver, press, tick, actors: state.borgs };
}

export function runRomCollisionSelfTest(): void {
  // Real Battle input and shipped action routing, not an injected phase/handler.
  for (const wall of [10, 50]) {
    const t = setup(geometry(wall));
    t.press();
    assert(t.borg.cooldowns["romSpecialActive"] === 1, "X takes ROM ownership");
    assert(t.borg.pos.z <= wall - 0.24, "entry does not cross wall");
    for (let i = 0; i < 8; i++) t.tick();
    assert(t.borg.pos.z <= wall - 0.24, "owned ticks do not cross wall");
    assert((t.driver.actor as typeof t.driver.actor & AccelerationNinjaScratch).grounded77b0 === true,
      "live probe reports floor contact to family");
    assert(t.driver.actor.yVel === 0, "grounded probe clears vertical velocity");
  }
  const open = setup(geometry());
  open.press();
  assert(Math.abs(open.borg.pos.z - 39) < 1e-6, "open entry integrates exactly once");
  open.tick();
  assert(Math.abs(open.borg.pos.z - 78) < 1e-6, "open owned frame integrates exactly once");
  const roof = setup(geometry(null, true));
  roof.press();
  // The dash can inherit vertical motion later in its phase. Exercise the live host
  // ceiling seam without pretending phase 0 (which explicitly zeros yVel) launches.
  roof.driver.actor.yVel = 30;
  roof.tick();
  assert(roof.borg.pos.y <= 19.75, "ascending owned dash stops below ceiling/body clearance");
  assert(roof.driver.actor.yVel === 0, "ceiling removes upward velocity");

  // Negative control: the old missing-probe path crosses the exact same wall.
  const oldPath = setup(geometry(10));
  delete oldPath.driver.actor.physicsRuntime!.probeMotion;
  oldPath.press();
  assert(oldPath.borg.pos.z > 10, "negative control crosses interior wall on real X entry");
  oldPath.tick();
  assert(oldPath.borg.pos.z > 70, "negative control keeps moving behind wall");

  const unsupported = setup(geometry());
  delete unsupported.driver.actor.physicsRuntime!.probeMotion;
  unsupported.press(); unsupported.tick();
  assert(Math.abs(unsupported.borg.pos.z - 78) < 1e-6, "optional probe absence preserves legacy motion");

  const noGeometry = setup({ triangles: [] });
  const noGeometryOld = setup({ triangles: [] });
  delete noGeometryOld.driver.actor.physicsRuntime!.probeMotion;
  noGeometry.press(); noGeometry.tick();
  noGeometryOld.press(); noGeometryOld.tick();
  assert(JSON.stringify(noGeometry.borg.pos) === JSON.stringify(noGeometryOld.borg.pos),
    "no collision geometry retains existing floor/off-mesh behavior");

  // Switching ordinary X now owns source677b0 on entry and windup. Keep the
  // probe boundary observable through actual input instead of asserting that
  // the formerly unadmitted legacy path never probes.
  const switching=setup(geometry(),"pl0009");
  let switchingProbes=0;
  const switchingProbe=switching.driver.actor.physicsRuntime!.probeMotion!;
  switching.driver.actor.physicsRuntime!.probeMotion=(...args)=>{switchingProbes++;return switchingProbe(...args);};
  switching.press();switching.tick();
  assert(switching.borg.command?.exact&&switching.driver.actor.actionIndex===2&&switchingProbes===2,
    "actual pl0009 ordinary X probes once per source dispatch");
  // The newly admitted pl0005 route follows original677b0 after both setup
  // carry and interpolated travel. Observe the existing host motion probe, not
  // a claim that its swept stage geometry is console-equivalent.
  const teleport = setup(geometry(), "pl0005");
  let teleportProbes=0;
  const teleportProbe=teleport.driver.actor.physicsRuntime!.probeMotion!;
  teleport.driver.actor.physicsRuntime!.probeMotion=(...args)=>{teleportProbes++;return teleportProbe(...args);};
  teleport.press();teleport.tick();
  assert(teleport.driver.actor.actionIndex===2&&teleportProbes===2,"actual pl0005 X setup probes once per source dispatch");
  const recovery = setup(geometry());
  recovery.press();
  recovery.driver.actor.fbPhaseSlots[0] = 2;
  recovery.driver.actor.physicsRuntime!.probeMotion = () => { throw new Error("recovery entered phase-1 probe"); };
  recovery.tick();
  console.log("[romCollision.selftest] PASS: live dash entry/ticks, wall, floor, ceiling, optional host, teleport and recovery isolation");
}
