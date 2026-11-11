import assert from "node:assert/strict";
import fs from "node:fs";
import test from "node:test";
import vm from "node:vm";
import ts from "typescript";
import * as THREE from "three";

// Execute the actual main RAF function and BattleScene.update body with a real mixer.
// Device/DOM/rendering are doubles; no user assets or WebGL are required. Keeping the
// clock delta read inside production tick catches resume catch-up as well as pose drift.
function parse(relative) {
  const url = new URL(relative, import.meta.url);
  return ts.createSourceFile(url.pathname, fs.readFileSync(url, "utf8"), ts.ScriptTarget.Latest, true, ts.ScriptKind.TS);
}
const main = parse("../apps/game/src/main.ts");
const tick = main.statements.find(n => ts.isFunctionDeclaration(n) && n.name?.text === "tick");
assert.ok(tick, "production tick must exist");
const sceneFile = parse("../apps/game/src/sim/battleScene.ts");
const sceneClass = sceneFile.statements.find(n => ts.isClassDeclaration(n) && n.name?.text === "BattleScene");
const update = sceneClass?.members.find(n => ts.isMethodDeclaration(n) && n.name.getText(sceneFile) === "update");
assert.ok(update, "production BattleScene.update must exist");
function constant(file, name) {
  const declaration = file.statements.flatMap(n => ts.isVariableStatement(n) ? [...n.declarationList.declarations] : [])
    .find(n => n.name.getText(file) === name);
  assert.ok(declaration?.initializer, `production constant ${name} must exist`);
  return `const ${declaration.getText(file)};`;
}
const constants = [constant(main, "RENDER_MAX_DELTA_SECONDS"),
  ...["CHARGE_GLOW_SPIN_RAD_PER_S", "ENEMY_RETICLE_SPIN_RAD_PER_S", "ALLY_MARKER_SPIN_RAD_PER_S"]
    .map(name => constant(sceneFile, name))].join("\n");
const emitted = ts.transpileModule(`${constants}\n${tick.getText(main)}\nclass SceneClock { ${update.getText(sceneFile)} }\nglobalThis.SceneClock = SceneClock;`, {
  compilerOptions: { target: ts.ScriptTarget.ES2022, module: ts.ModuleKind.None }, reportDiagnostics: true,
});
assert.deepEqual(emitted.diagnostics, []);

function fixture() {
  let screen = "battle", wallTime = 0, lastRead = 0;
  const calls = { clock: 0, camera: 0, controls: 0, render: 0, status: 0, impacts: 0, aura: 0, auraX: 0 };
  const pose = new THREE.Object3D();
  const mixer = new THREE.AnimationMixer(pose);
  const action = mixer.clipAction(new THREE.AnimationClip("attack", 1, [
    new THREE.NumberKeyframeTrack(".position[x]", [0, 1], [0, 10]),
  ])).setLoop(THREE.LoopOnce, 1);
  action.clampWhenFinished = true;
  action.play();
  const actor = { mixer, chargeGlow: { sprite: { visible: true }, material: { rotation: 0 } } };
  const context = {
    session: { paused: false },
    renderClock: { getDelta() { calls.clock++; const dt = wallTime - lastRead; lastRead = wallTime; return dt; } },
    challengeSession: { snapshot: () => ({ screen }) },
    followCamera() { calls.camera++; }, updateBattleDebugDataset() {}, debugOverlay: { visible: false },
    controls: { update() { calls.controls++; } }, viewport: { render() { calls.render++; } }, onComposedGameFrame() {},
  };
  vm.createContext(context);
  vm.runInContext(emitted.outputText, context);
  const scene = new context.SceneClock();
  Object.assign(scene, { actors: new Map([["actor", actor]]),
    enemyReticle: { visible: true, rotation: { y: 0 } }, allyMarker: { visible: true, rotation: { y: 0 } },
    updateDiverAuraPositions() { calls.aura++; calls.auraX = pose.position.x; },
    updateStatusAuras() { calls.status++; }, updateImpacts() { calls.impacts++; },
  });
  context.battleScene = scene;
  return { calls, action, pose, actor, scene, context,
    setScreen(value) { screen = value; },
    frame(dt = 1 / 60) { wallTime += dt; vm.runInContext("tick()", context); },
  };
}
const close = (actual, expected) => assert.ok(Math.abs(actual - expected) < 1e-10, `${actual} ≈ ${expected}`);

test("pause freezes a mid-swing pose and battle FX for 120 frames; resume uses fresh delta", () => {
  const f = fixture();
  for (let i = 0; i < 4; i++) f.frame(0.05);
  close(f.action.time, 0.2);
  const before = { time: f.action.time, x: f.pose.position.x, charge: f.actor.chargeGlow.material.rotation,
    enemy: f.scene.enemyReticle.rotation.y, ally: f.scene.allyMarker.rotation.y };
  f.context.session.paused = true;
  for (let i = 0; i < 120; i++) f.frame();
  assert.deepEqual({ time: f.action.time, x: f.pose.position.x, charge: f.actor.chargeGlow.material.rotation,
    enemy: f.scene.enemyReticle.rotation.y, ally: f.scene.allyMarker.rotation.y }, before);
  assert.equal(f.action.paused, false, "one-shot must not finish while paused");
  assert.equal(f.calls.status, 4); assert.equal(f.calls.impacts, 4);
  assert.equal(f.calls.aura, 4, "paused frames do not resample aura position");
  close(f.calls.auraX, before.x);
  for (const key of ["clock", "camera", "controls", "render"]) assert.equal(f.calls[key], 124, key);
  f.context.session.paused = false; f.frame();
  close(f.action.time, 0.2 + 1 / 60);
  assert.equal(f.calls.status, 5); assert.equal(f.calls.impacts, 5);
  assert.equal(f.calls.aura, 5);
  close(f.calls.auraX, f.pose.position.x);
  assert.ok(f.calls.auraX > before.x, "resume samples the newly advanced pose");
});

test("repeated pause/resume preserves each paused pose and advances normally afterward", () => {
  const f = fixture();
  for (let cycle = 0; cycle < 4; cycle++) {
    f.frame(); const time = f.action.time;
    f.context.session.paused = true;
    for (let i = 0; i < 30; i++) f.frame();
    close(f.action.time, time);
    f.context.session.paused = false; f.frame();
    close(f.action.time, time + 1 / 60);
  }
  close(f.action.time, 8 / 60);
});

test("results ignores a stale pause flag; menu does not advance battle clocks", () => {
  const f = fixture(); f.context.session.paused = true; f.setScreen("results");
  f.frame(); close(f.action.time, 1 / 60); assert.equal(f.calls.camera, 0);
  f.setScreen("title"); f.frame(0.5);
  close(f.action.time, 1 / 60); assert.equal(f.calls.impacts, 1);
  assert.equal(f.calls.render, 2); assert.equal(f.calls.controls, 2); assert.equal(f.calls.clock, 2);
  f.setScreen("battle"); f.context.session.paused = false; f.frame();
  close(f.action.time, 2 / 60);
});

test("running battle retains delta clamp and supports absent session during transition", () => {
  const f = fixture(); f.frame(2); close(f.action.time, 0.05);
  f.context.session = null; f.frame(); close(f.action.time, 0.05 + 1 / 60);
});
