import assert from "node:assert/strict";
import { readFile } from "node:fs/promises";
import ts from "typescript";

function transpile(source, fileName) {
  return ts.transpileModule(source, {
    compilerOptions: {
      module: ts.ModuleKind.ESNext,
      target: ts.ScriptTarget.ES2022,
    },
    fileName,
  }).outputText;
}

function dataUrl(source) {
  return `data:text/javascript;base64,${Buffer.from(source).toString("base64")}`;
}

const generatedPath = new URL(
  "../apps/game/src/ui/titleIntroScript.generated.ts",
  import.meta.url,
);
const generatedUrl = dataUrl(
  transpile(await readFile(generatedPath, "utf8"), "titleIntroScript.generated.ts"),
);
const generated = await import(generatedUrl);

async function importTitleModule(path, fileName) {
  const source = await readFile(path, "utf8");
  const js = transpile(source, fileName).replace(
    /\.\.\/titleIntroScript\.generated\.js/g,
    generatedUrl,
  );
  return import(dataUrl(js));
}

const { createTitleVm } = await importTitleModule(
  new URL("../apps/game/src/ui/intro/titleVm.ts", import.meta.url),
  "titleVm.ts",
);
const { createTitlePropController } = await importTitleModule(
  new URL("../apps/game/src/ui/intro/titlePropController.ts", import.meta.url),
  "titlePropController.ts",
);
const { createPhysicalMenuController } = await importTitleModule(
  new URL("../apps/game/src/ui/intro/physicalMenuController.ts", import.meta.url),
  "physicalMenuController.ts",
);

assert.deepEqual(
  generated.TITLE_INTRO_WIDGET_DESCRIPTORS
    .filter((entry) => entry.modelId >= 0)
    .map((entry) => [entry.modelId, entry.updateKind, entry.variant]),
  [
    [55, 0, 0],
    [65, 2, 0],
    [51, 1, 0],
    [52, 1, 1],
    [53, 1, 2],
    [54, 1, 3],
    [48, 1, 4],
    [49, 1, 5],
    [50, 1, 6],
    [47, 1, 7],
  ],
  "stff title-prop rows remain byte-for-byte generated from DAT_8038a570",
);
assert.deepEqual(
  generated.TITLE_INTRO_PROP_MOTION_ROWS.map((row) => row.waitFrames),
  [0, 24, 16, 8, 20, 20, 30, 30],
  "source prop stagger table remains exact",
);
assert.deepEqual(
  generated.PHYSICAL_MENU_DIRECTION_TABLE.map((row) => [
    row.up,
    row.down,
    row.left,
    row.right,
  ]),
  [
    [1, 0, 2, 3],
    [1, 0, 4, 5],
    [4, 2, 6, 0],
    [5, 0, 1, 3],
    [4, 2, 6, 1],
    [5, 3, 1, 5],
    [6, 2, 6, 4],
  ],
  "physical-menu direction graph remains generated from DAT_80301cf0",
);
assert.equal(generated.PHYSICAL_MENU_WIDGET_DESCRIPTORS.length, 15);
assert.deepEqual(
  generated.PHYSICAL_MENU_WIDGET_DESCRIPTORS.slice(0, 7).map((row) => row.menuIndex),
  [0, 1, 2, 3, 4, 5, 6],
  "0x801cd90c retains the seven source physical-menu indices",
);
assert.deepEqual(
  generated.PHYSICAL_MENU_MODEL_TRIPLETS.map((row) => [
    row.baseModelId,
    row.selectionModelId,
    row.labelModelId,
  ]),
  [
    [41, 61, 40],
    [43, 62, 42],
    [35, 63, 44],
    [39, 59, 36],
    [45, 64, 46],
    [37, 60, 38],
    [66, 67, 68],
  ],
  "physical-menu drawable triplets remain generated from DAT_8038a760",
);
assert.deepEqual(
  generated.PHYSICAL_MENU_ANGULAR_STEPS.map((row) => row.bamStep),
  [0x0200, 0x0200, 0x0200, 0x0200, 0x0200, 0x0200, 0x0200],
  "physical-menu BAM rotation steps remain generated from DAT_8038a78c",
);
assert.equal(generated.PHYSICAL_MENU_CURSOR_MODEL_ID, 0x38);
const physicalMenu = createPhysicalMenuController(0);
assert.equal(physicalMenu.move("up"), 1, "source graph moves Story to Challenge");
assert.equal(
  physicalMenu.dispatchAddress,
  "0x80195f2c",
  "Challenge index dispatches to the original Challenge controller",
);
assert.equal(physicalMenu.move("down"), 0);

const introTrace = {
  actorAnims: [],
  actorVisibility: [],
  titleWidgets: [],
  sounds: [],
  lightBars: 0,
};
let introTraceFrame = -1;
let selectedIntroResource = 0xff;
const introSceneEndFrames = new Map([
  [12, 39], [13, 23], [14, 60], [15, 49], [16, 49],
  [17, 80], [18, 31], [19, 49], [20, 29], [21, 29],
]);
const titleVm = createTitleVm({
  isArchiveReady: () => true,
  isCameraReady: () => true,
  attachDeskArchives() {},
  screenColor() {},
  selectWidgetOrEffect(resource) { selectedIntroResource = resource; },
  getSelectedSceneEndFrame() { return introSceneEndFrames.get(selectedIntroResource) ?? 0; },
  applySelectedSceneFrame() {},
  setCameraMode() {},
  setSceneAuxMode() {},
  actorPlayAnim(slot, groupSel, animId) {
    introTrace.actorAnims.push([introTraceFrame, slot, groupSel, animId]);
  },
  actorReset() {},
  actorSetVisible(slot, visible) {
    introTrace.actorVisibility.push([introTraceFrame, slot, visible]);
  },
  toggleOverlay() {},
  copyOverlayTransform() {},
  titleLightBar() {
    introTrace.lightBars += 1;
  },
  spawnTitleWidget(id) {
    introTrace.titleWidgets.push([introTraceFrame, id]);
  },
  setTitleWidgetMode() {},
  playSound(cue) {
    introTrace.sounds.push([introTraceFrame, cue]);
  },
});
const propController = createTitlePropController();
const propSounds = [];
for (let frame = 0; frame < 2400 && titleVm.state.endRequested === 0; frame += 1) {
  introTraceFrame = frame;
  titleVm.tick();
  for (const soundId of propController.tick(titleVm.state.sceneStep)) {
    propSounds.push([frame, soundId]);
  }
}

assert.equal(titleVm.state.endRequested, 1, "fixed-frame ROM title script reaches Press Start");
assert.equal(introTraceFrame, generated.TITLE_INTRO_TOTAL_FRAMES);
assert.deepEqual(titleVm.state.borgIds.slice(0, 2), [0x0615, 0x000a]);
assert.deepEqual(
  introTrace.actorAnims,
  generated.TITLE_INTRO_ACTOR_EVENTS.map((event) => [
    event.frame,
    event.slot,
    event.actionGroup,
    event.animId,
  ]),
  "actor commands execute on generated ROM-script frames",
);
assert.deepEqual(
  introTrace.actorVisibility,
  [[210, 0, false], [210, 1, false], [230, 1, true], [234, 0, true]],
  "opcode 0x0d retains source visibility-flag/actor-slot operand order",
);
assert.deepEqual(introTrace.titleWidgets, [[0, 27], [922, 29]]);
assert.deepEqual(introTrace.sounds, [[180, 0x017c]], "source title reveal cue remains exact");
assert.ok(introTrace.lightBars > 0, "source light-bar event remains present");
assert.ok(
  propSounds.some(([, soundId]) => soundId === 0x017a) &&
    propSounds.filter(([, soundId]) => soundId === 0x017b).length === 2,
  "source screw/nut impacts emit recovered 0x17a/0x17b cues",
);
assert.ok(
  propController.frames[0].destroyed && propController.frames[1].destroyed,
  "source CAPCOM plate and fade quad lifetimes end after their scene steps",
);
assert.ok(
  propController.frames.slice(2).every((prop) => prop.visible && !prop.destroyed),
  "all eight source screws/nuts complete their staggered drop",
);

const titlePath = new URL("../apps/game/src/ui/screens/TitleIntro.ts", import.meta.url);
const menuPath = new URL("../apps/game/src/ui/screens/MainMenu.ts", import.meta.url);
const menuScenePath = new URL(
  "../apps/game/src/ui/intro/physicalMenuScene.ts",
  import.meta.url,
);
const mainPath = new URL("../apps/game/src/main.ts", import.meta.url);
const [titleSource, menuSource, menuSceneSource, mainSource] = await Promise.all(
  [titlePath, menuPath, menuScenePath, mainPath].map((path) => readFile(path, "utf8")),
);

for (const forbidden of [
  "TITLE_CAPTURE_URL",
  "RUN_DIRECTION",
  "DASH_BACK_DIRECTION",
  "applyActorAnimMotion",
  "stepActorPhysics",
  "STAGE_SURFACE_Y",
  "STAGE_X_SPREAD",
  "ACTOR_YAW",
]) {
  assert.ok(!titleSource.includes(forbidden), `TitleIntro must not contain ${forbidden}`);
}
assert.ok(titleSource.includes("Float32Array.from(bone.pos)"), "root position tracks are retained");
assert.ok(titleSource.includes("createTitlePropController"), "source prop task controller is wired");
assert.ok(titleSource.includes("/stages/stff/model/"), "source stage props are loaded from stff");
assert.ok(
  titleSource.includes("[8, 364.89, 2595.134]") &&
    titleSource.includes("[-465.22455, -1003.881, 3706.802]") &&
    titleSource.includes("endFrame: 80"),
  "tdc00..09 COBJ states and recovered animation lengths remain wired",
);
assert.ok(titleSource.includes("vm.state.endRequested === 0"), "Press Start is VM-gated");

for (const falseClaim of [
  "SOURCE_TITLE_MENU_WIDGETS",
  "createSourceTitleMenuController",
]) {
  assert.ok(!menuSource.includes(falseClaim), `MainMenu must not claim ${falseClaim}`);
}
assert.ok(menuSource.includes("createPhysicalMenuController"));
assert.ok(menuSource.includes("mountPhysicalMenuScene"));
assert.ok(!menuSource.includes("moveByDirection"), "capture geometry must not drive navigation");
assert.ok(menuSource.includes('"data-controller-evidence": "source-0x800bf8d4"'));
assert.ok(menuSource.includes('"data-presentation-evidence": "source-DAT_8038a760"'));
for (const captureFallback of ["CHALLENGE_MENU_CAPTURE", "STORY_MENU_CAPTURE", "captureFor("]) {
  assert.ok(!menuSource.includes(captureFallback), `MainMenu must not retain ${captureFallback}`);
}
assert.ok(menuSceneSource.includes("PHYSICAL_MENU_MODEL_TRIPLETS"));
assert.ok(menuSceneSource.includes("PHYSICAL_MENU_CURSOR_MODEL_ID"));
assert.ok(menuSceneSource.includes("PHYSICAL_MENU_ANGULAR_STEPS"));
assert.ok(menuSceneSource.includes("0.1, 32768"), "stff near/far planes remain exact");
assert.ok(
  menuSceneSource.includes("selectionPivot.visible = drawable.menuIndex === selectedIndex"),
  "source selection drawable gating remains wired",
);
assert.ok(
  mainSource.includes('mode === "challenge"') &&
    mainSource.includes('dispatchSession({ type: "menu-select", mode })') &&
    mainSource.includes('case "difficulty"'),
  "Challenge selection enters the existing Challenge controller path",
);

console.log(
  "title frontend self-check passed: ROM VM/actors/stff props/camera, physical-menu drawables/graph, Challenge dispatch",
);
