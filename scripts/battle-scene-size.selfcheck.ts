import * as THREE from "three";
import { createBattle, battleStateForSelfcheck } from "../packages/combat/src/battle.js";
import { RomDriverBridge } from "../packages/combat/src/bridge.js";
import { tierSizeScale, MODEL_SIZE_STEP } from "../packages/combat/src/timescale.js";
import { emptyInput } from "../packages/combat/src/types.js";
import type { BorgStats } from "../packages/combat/src/stats.js";
import borgs from "../packages/assets/data/borgs.json";
import { BattleScene } from "../apps/game/src/sim/battleScene.js";
import { battleActorView } from "../apps/game/src/sim/battleView.js";

function assert(ok: unknown, message: string): asserts ok {
  if (!ok) throw new Error(`battleScene size: ${message}`);
}
const near = (a: number, b: number) => Math.abs(a - b) < 1e-6;

export async function runBattleSceneSizeSelfcheck(): Promise<void> {
  THREE.TextureLoader.prototype.load = function (): THREE.Texture { return new THREE.Texture(); };
  for (const id of ["pl0804", "pl080c"]) {
    const battle = createBattle({ stageId: "st00", forces: [
      { team: 0, ownerPlayer: "p1", borgIds: [id] },
      { team: 1, ownerPlayer: "p2", borgIds: [id] },
    ], bounds: { x: 2000, z: 2000 } }, borgs.borgs as BorgStats[]);
    const [hero, peer] = battleStateForSelfcheck(battle).borgs;
    assert(hero && peer, "two source-backed actors spawn");
    const bridge = hero.romDriver as RomDriverBridge;
    assert(bridge instanceof RomDriverBridge, "production hero bridge selected");
    const loads: Array<(model: THREE.Object3D) => void> = [];
    const source = new THREE.Group(); source.scale.setScalar(0.25);
    const scene = new BattleScene(new THREE.Group(), {
      loadModel: () => new Promise((resolve) => loads.push(resolve)),
      loadClip: async () => null,
    });
    const tick = () => battle.step(1 / 60, { p1: emptyInput(), p2: emptyInput() });
    const sync = () => scene.sync(battle.observe().actors.map(battleActorView));
    const actors = (scene as unknown as { actors: Map<string, { group: THREE.Group; model: THREE.Object3D | null }> }).actors;
    sync();
    const actor = actors.get(hero.uid)!;
    assert(actor.group.scale.x === 1 && actors.get(peer.uid)!.group.scale.x === 1, "default unchanged");

    // Real configured Hero X handler + bridge callback, injecting its documented
    // contact seam rather than claiming the browser collision path is verified here.
    bridge.actor.actionIndex = 2;
    bridge.actor.fbState = 61;
    bridge.actor.contactP0 = 1;
    bridge.actor.parts[0]!.streamPtr = 42;
    bridge.actor.parts[0]!.active = 1;
    bridge.actor.rootAction!(bridge.actor);
    assert(hero.paramTier.tier === 20 && hero.heroTierBuffFrames === 1200, "actual X writer reaches runtime");
    assert(near(tierSizeScale(hero), 2.6), "authored +4 tier target is 2.6");
    battle.step(1 / 60, { p1: emptyInput(), p2: emptyInput() });
    assert(near(hero.modelSizeScale!, 1 + MODEL_SIZE_STEP), "battle simulation advances one size step");
    sync(); sync(); scene.update(0.5); sync();
    assert(near(actor.group.scale.x, 1.05), "render sync and wall time do not advance/compound size");
    for (let i = 0; i < 31; i++) tick();
    sync();
    assert(near(actor.group.scale.x, 2.6), "growth clamps at exact target");
    assert(actors.get(peer.uid)!.group.scale.x === 1 && source.scale.x === 0.25, "same-form peer/source isolated");
    loads.shift()!(source.clone()); loads.shift()!(source.clone());
    await Promise.resolve(); await Promise.resolve();
    assert(actor.model?.scale.x === 0.25 && near(actor.group.scale.x, 2.6), "late model keeps normalization and latest size");

    hero.combatFormId = "pl0605"; tick(); sync();
    hero.heroTierBuffFrames = 1;
    tick(); sync();
    assert(Number(hero.paramTier.tier) === 16 && near(actor.group.scale.x, 2.55), "buff expiry begins source additive shrink");
    loads.shift()!(source.clone());
    await Promise.resolve(); await Promise.resolve();
    assert(actor.model?.scale.x === 0.25 && near(actor.group.scale.x, 2.55), "late morph uses current parent scale");
    for (let i = 0; i < 40; i++) tick();
    sync(); assert(actor.group.scale.x === 1, "expiry clamps at default without overshoot");
    hero.sizeTierDelta = -4; hero.sizeTierTimer = 100;
    for (let i = 0; i < 40; i++) tick();
    sync(); assert(near(actor.group.scale.x, tierSizeScale(hero)) && actor.group.scale.x < 1, "hit shrink state reaches authored target");
    hero.sizeTierTimer = 1; tick();
    for (let i = 0; i < 40; i++) tick();
    sync(); assert(actor.group.scale.x === 1, "hit size expiry returns to default");
    hero.sizeTierDelta = 4; hero.sizeTierTimer = 100;
    for (let i = 0; i < 40; i++) tick();
    sync(); assert(near(actor.group.scale.x, 2.6), "hit grow state reaches authored target");
    scene.sync([]);

    // Separate battle: ordinary X input must reach the shipped authored stream.
    const inputBattle = createBattle({ stageId: "st00", forces: [
      { team: 0, ownerPlayer: "p1", borgIds: [id] },
      { team: 1, ownerPlayer: "p2", borgIds: [id] },
    ], bounds: { x: 2000, z: 2000 } }, borgs.borgs as BorgStats[]);
    const inputHero = battleStateForSelfcheck(inputBattle).borgs[0]!;
    for (let i = 0; i < 40; i++) inputBattle.step(1 / 60, { p1: emptyInput(), p2: emptyInput() });
    inputBattle.step(1 / 60, { p1: { ...emptyInput(), special: true }, p2: emptyInput() });
    assert(inputHero.cooldowns["romSpecialActive"] === 1, "normal X input reaches ROM action owner");
    for (let i = 0; i < 120; i++) inputBattle.step(1 / 60, { p1: emptyInput(), p2: emptyInput() });
    assert(inputHero.paramTier.tier === 20 && near(inputHero.modelSizeScale!, 2.6), "normal X authored stream reaches tier writer and visible size");
    scene.sync(inputBattle.observe().actors.map(battleActorView));
    assert(near(actors.get(inputHero.uid)!.group.scale.x, 2.6), "ordinary X observation scales rendered actor");
    while (loads.length) loads.shift()!(source.clone());
    await Promise.resolve(); await Promise.resolve();
    scene.sync([]);

    let observed = 0;
    const observerBridge = RomDriverBridge.attach(peer, {
      onParamTierDelta: (_actor, delta) => { observed += delta; },
    });
    assert(observerBridge, "observer bridge attaches");
    const a = observerBridge.actor;
    a.actionIndex = 2; a.fbState = 61; a.contactP0 = 1;
    a.parts[0]!.streamPtr = 42; a.parts[0]!.active = 1;
    a.rootAction!(a);
    assert(observed === 4 && peer.paramTier.tier === 20, "observer and runtime each receive delta exactly once");
    a.fbPhaseSlots[0] = 1; a.contactP0 = 1;
    a.rootAction!(a);
    assert(observed === 4 && peer.paramTier.tier === 20, "repeat contact does not stack or refresh buff");
  }
  console.log("battleScene size selfcheck: PASS (Hero X writer, simulation cadence, expiry, deferred models/morphs, clone isolation)");
}
