// Gotcha Force (web) — entry point.
//
// This wires the three finished systems into a playable CHALLENGE-mode loop:
//   A) @gf/combat   — the deterministic battle sim (createBattle / battle.step).
//   B) @gf/missions — CHALLENGE run/progression (createChallengeRun / computeResults).
//   C) apps/game/src/ui — the framework-free screen + HUD components.
//
// Screen flow:
//   MainMenu -> (challenge) -> SelectDifficulty -> SelectPlayers -> LoadBoxData
//     -> SelectForce -> ForceBuilder/edit -> BattleIntro -> BATTLE
//     -> Results -> next battle / back to menu
//   MainMenu -> (edit-force) -> ForceBuilder -> back to menu
//   PauseMenu overlays the battle on Start/Esc.
//
// The existing three.js scene, stage rendering, lighting, camera, the centralized
// render asset loader, and the baked-clip builder are REUSED. The netcode `ws` hooks are
// preserved (defined but dormant) so multiplayer can be wired next.

import * as THREE from "three";

import {
  createPublicAssetCatalog,
  type ModelManifestEntry,
  type StageAssets,
} from "@gf/assets";
import { createScreenHost, startFixedStepLoop, startRenderLoop } from "@gf/core";
import {
  createThreeAssetLoader,
  createThreeViewport,
  prepareImportedModel,
} from "@gf/render";
import {
  emptyInput,
  type Battle,
  type BorgRuntime,
  type PlayerInput,
  type RectStageBounds,
} from "@gf/combat";
import { createAudioManager, type GotchaAudioManager } from "@gf/audio";
import {
  createChallengeRun,
  computeResults,
  playerIdFor,
  type ChallengeRun,
  type BattleConfig as MissionBattleConfig,
  type BattleResults,
} from "@gf/missions";

import {
  ensureStyles,
  createMainMenu,
  createSelectDifficulty,
  createSelectPlayers,
  createLoadBoxData,
  createSelectForce,
  createForceBuilder,
  createBattleIntro,
  createResults,
  createPauseMenu,
  createBattleHud,
  createDebugOverlay,
  type MainMenuMode,
  type ForceSlot,
  type BattleHudHandle,
  type DebugOverlayHandle,
} from "./ui/index.js";

import {
  EXPORTED_STAGE_CATALOG_ADAPTER,
  inputFromKeys,
  DEFAULT_ARENA_STAGE,
  EXPORTED_STAGE_CATALOG,
  isExportedStageId,
} from "./sim/adapter.js";
import { createBattleBootstrap } from "./sim/battleBootstrap.js";
import { BattleScene, type AnimSlot } from "./sim/battleScene.js";
import { BORG_CATALOG, DEFAULT_LEAD } from "./sim/borgCatalog.js";
import { BattleCamera } from "./sim/camera.js";
import {
  activeBorgForPlayer,
  battleEnergyMaxima,
  battleOutcomeFromState,
  battlePresentationState,
  battleSceneState,
  battleAudioEvents,
  liveActorPositions as battleLiveActorPositions,
  snapshotBattleAudio,
  type BattleEventCue,
} from "./sim/presentation.js";

// ------------------------------------------------------------------------------------------
// Data
// ------------------------------------------------------------------------------------------

const FORCE_CATALOG = BORG_CATALOG.forceCatalog;

// Exported ADX->OGG cues from poq_adx_usa.afs. Exact Challenge cue semantics
// still need DOL trace confirmation, so these are conservative asset-backed
// defaults rather than claimed final music IDs.
//
// Menu SFX note (2026-07-02): the earlier decision to mute confirm/back/edit was based on the
// se00_* exports being 3-12s clips. That turned out to be an EXPORT BUG, not a property of the
// source audio: the ADX headers in poq_adx_usa.afs give 0.47-1.86s for AFS members 33..37, and
// the re-exported OGGs match. With genuinely short one-shot cues available, menu SFX are wired
// again — still TUNED (which SE plays for which menu event is not ROM-traced), but no longer
// wrong-length. See research/game-design/AUDIO-PORT-STATUS.md for the full event->file map.
const AUDIO_CUES = {
  menuBgm: "bgm00",
  battleBgm: "bgm01",
  confirm: "se00_03",
  back: "se00_04",
  edit: "se00_04",
} as const;
// Combat SFX default ON since the export-duration fix; ?noCombatSfx=1 is the debugging opt-out
// (replaces the old opt-in ?tunedCombatSfx=1 gate, whose rationale — 12s clips — is gone).
const DISABLE_COMBAT_SFX = new URLSearchParams(window.location.search).has("noCombatSfx");

// Battle event -> SFX cue mapping. TUNED, NOT DERIVED: behavior-notes.md (v) confirms there is
// no recovered ROM per-action audio-event table to port (AnimAudioEventLookup @ 0x801a7640 is a
// generic nlQSort<T> instantiation name, not a decoded frame/sound-id table; hit.bin/comhit.bin's
// 0xF4-byte records have no identified sound-id field either). Only 5 exported SE cues exist
// (poq_adx_usa.afs members 33..37); their real durations are 0.47-1.86s (the old 3-12s manifest
// durations were a broken export, since fixed). Assignments below are guided by waveform analysis
// of the decoded PCM (documented in AUDIO-PORT-STATUS.md), not by traced sound IDs:
//   se00_00 1.35s hard-attack multi-burst -> knockdown / dash
//   se00_01 1.86s two-part long burst     -> death / explosion
//   se00_02 1.07s slow build then burst   -> special / charge release / low-energy alert
//   se00_03 0.47s instant-attack impact   -> melee swing / damage taken / menu confirm
//   se00_04 0.64s short tonal burst       -> shot / lock-on switch / menu back-edit
// jump and land stay deliberately unmapped: no plausible short jump/land sample exists in the
// exported set, and reusing an impact cue there would reintroduce the "wrong asset" bug class.
const COMBAT_SFX: Partial<Record<BattleEventCue, string>> = {
  melee: "se00_03",
  melee_alt: "se00_03",
  shoot: "se00_04",
  special: "se00_02",
  charge_release: "se00_02",
  hit: "se00_03",
  down: "se00_00",
  death: "se00_01",
  dash: "se00_00",
  dash_fwd: "se00_00",
  dash_back: "se00_00",
  dash_left: "se00_00",
  dash_right: "se00_00",
  lockon: "se00_04",
  alert: "se00_02",
};

// Rate limits are keyed by EVENT (not by file), so e.g. a damage-taken cue is not swallowed by a
// just-played melee swing that happens to share the same sample.
const COMBAT_SFX_MIN_GAP_MS: Partial<Record<BattleEventCue, number>> = {
  melee: 220,
  melee_alt: 220,
  shoot: 180,
  special: 450,
  charge_release: 450,
  hit: 180,
  down: 450,
  death: 700,
  dash: 400,
  dash_fwd: 400,
  dash_back: 400,
  dash_left: 400,
  dash_right: 400,
  lockon: 150,
  alert: 1500,
};
const lastCombatSfxAt = new Map<string, number>();

function playCombatSfx(cue: BattleEventCue): void {
  if (DISABLE_COMBAT_SFX) return;
  const key = COMBAT_SFX[cue];
  if (!key) return;
  const now = performance.now();
  const minGap = COMBAT_SFX_MIN_GAP_MS[cue] ?? 250;
  const last = lastCombatSfxAt.get(cue) ?? -Infinity;
  if (now - last < minGap) return;
  lastCombatSfxAt.set(cue, now);
  playSfx(key);
}

function playBattleEventSfx(cue: BattleEventCue): void {
  playCombatSfx(cue);
}

function selectedForce(): string[] {
  return forceFromSlot(selectedForceSlot());
}

function forceFromSlot(slot: ForceSlot): string[] {
  return BORG_CATALOG.forceFromSlot(slot);
}

function selectedForceSlot(): ForceSlot {
  return flow.forceSlots[flow.selectedForceSlot] ?? flow.forceSlots[0] ?? BORG_CATALOG.defaultForceSlots[0]!;
}

function forceSlotForPlayer(playerIndex: number): ForceSlot {
  if (playerIndex <= 0) return selectedForceSlot();
  const slotCount = flow.forceSlots.length;
  if (slotCount === 0) return selectedForceSlot();
  return flow.forceSlots[(flow.selectedForceSlot + playerIndex) % slotCount] ?? selectedForceSlot();
}

function updateSelectedForceSlot(borgIds: readonly string[]): void {
  const slot = selectedForceSlot();
  const valid = borgIds.filter((id) => BORG_CATALOG.forceById.has(id));
  flow.forceSlots[flow.selectedForceSlot] = {
    ...slot,
    borgIds: valid.length > 0 ? [...valid] : [DEFAULT_LEAD],
  };
}

// Borgs that have a verified GLB model in the library (or the pl0615 special path).
const LIBRARY_IDS = new Set<string>();
// Filled from the manifest at load time.

// ------------------------------------------------------------------------------------------
// three.js scene (preserved from the original app)
// ------------------------------------------------------------------------------------------

// DERIVED: fov/near/far/fog/ambient/light values below are read directly from st00_mdl.arc's
// scene CObj/LObj/Fog tables (research/asset-inventory/stage-lighting-render-state.md — Camera
// section: eye/interest/near=10/far=80000/fov=43.191872; Fog section: start=900/end=40000).
// Per-stage render-state replaces fov/near/far at runtime; this object only seeds the scene
// before the first stage finishes loading. Camera *position* (as opposed to fov/near/far) is NOT derived
// from this table — that's the separate follow-camera logic in sim/camera.ts.
const DEFAULT_RENDER_STATE = {
  fogColor: 0xfff6e5,
  fogNear: 900,
  fogFar: 40000,
  fov: 43.191872,
  near: 10,
  far: 80000,
  ambientColor: 0xd8d0c2,
  lightColor: 0xfff0e6,
  lightPosition: new THREE.Vector3(-385.512512, 956.0448, -377.986603),
};

type StageColorRecord = { rgbHex?: string };
type ExtractedStageLight = {
  role?: string;
  color?: StageColorRecord;
  intensity?: number;
  position?: { position?: number[] } | null;
};
type LegacyStageLights = {
  ambient?: { colorRgbHex?: string; intensity?: number };
  directional?: { colorRgbHex?: string; intensity?: number; position?: number[] };
};

type StageRenderState = {
  camera?: { fovDegrees?: number; near?: number; far?: number };
  fog?: { colorRgbHex?: string; color?: StageColorRecord; start?: number; end?: number };
  lights?: ExtractedStageLight[] | LegacyStageLights;
};

const uiElement = document.getElementById("ui");
const canvas = document.getElementById("app") as HTMLCanvasElement;
if (!uiElement) throw new Error("Missing #ui");
const ui = uiElement;
const screenHost = createScreenHost(ui);
ui.style.pointerEvents = "auto"; // the UI component library uses real buttons.
const urlParams = new URLSearchParams(window.location.search);
const ENABLE_BATTLE_DEBUG_DATASET = urlParams.has("debugBattle");
const ENABLE_RENDER_DEBUG = urlParams.has("debugRender") || urlParams.has("capture");

// ATK-015: minimal read-only debug overlay (sim state readout for the focused borg). Mounted
// once at startup, hidden by default; toggled with the backtick key or ?debugOverlay=1. See
// apps/game/src/ui/hud/DebugOverlay.ts and research/tasks/attack-port/ATK-015-debug-overlay-fields.md.
const debugOverlay: DebugOverlayHandle = createDebugOverlay(ui);
if (urlParams.has("debugOverlay")) debugOverlay.setVisible(true);

const viewport = createThreeViewport(canvas, {
  debugCapture: ENABLE_RENDER_DEBUG,
  clearColor: DEFAULT_RENDER_STATE.fogColor,
  camera: {
    fov: DEFAULT_RENDER_STATE.fov,
    near: DEFAULT_RENDER_STATE.near,
    far: DEFAULT_RENDER_STATE.far,
    position: [950, 520, 1320],
  },
});
const { scene, camera, controls } = viewport;
const renderAssets = createThreeAssetLoader({
  enableFileCache: true,
});
scene.fog = new THREE.Fog(DEFAULT_RENDER_STATE.fogColor, DEFAULT_RENDER_STATE.fogNear, DEFAULT_RENDER_STATE.fogFar);

import {
  createStageLightingRig,
  applyStageRenderStateLighting,
  type StageRenderState as LightingStageRenderState,
} from "./stages/lighting";
// Real per-stage lighting rig (supports N directionals — stff carries 2); replaces the old
// single ambient+directional pair. Values/validation: research/game-design/STAGE-LIGHTING-PORT.md.
const stageLighting = createStageLightingRig(scene);

const stageRoot = new THREE.Group();
scene.add(stageRoot);

// Battle actors (sim-driven borg models) live under their own group.
const battleRoot = new THREE.Group();
scene.add(battleRoot);

let modelManifest: ModelManifestEntry[] = [];
const assetCatalog = createPublicAssetCatalog();

// --- model + clip caches (reused by the BattleScene via the asset hooks) ---
const sourceModels = new Map<string, Promise<THREE.Object3D>>();
const clipCache = new Map<string, Promise<THREE.AnimationClip | null>>();

type BakedClip = {
  name?: string;
  frameCount: number;
  fps?: number;
  bones: Array<{ i: number; pos?: number[]; rot?: number[]; scl?: number[] }>;
};

type AnimBank = {
  file: string;
  group: number;
  slot: number;
  label: string;
  frames: number;
};

type AnimIndex = {
  borg: string;
  banks: AnimBank[];
};

function buildClip(json: BakedClip): THREE.AnimationClip {
  const fps = json.fps ?? 60;
  const times = Float32Array.from({ length: json.frameCount }, (_, frame) => frame / fps);
  const tracks: THREE.KeyframeTrack[] = [];
  for (const bone of json.bones) {
    const node = `JOBJ_${bone.i}`;
    if (bone.pos?.length === json.frameCount * 3) {
      const values = Float32Array.from(bone.pos);
      if (bone.i === 0) {
        for (let i = 0; i < values.length; i += 3) {
          values[i] = 0;
          values[i + 2] = 0;
        }
      }
      tracks.push(new THREE.VectorKeyframeTrack(`${node}.position`, times, values));
    }
    if (bone.rot?.length === json.frameCount * 4) {
      tracks.push(new THREE.QuaternionKeyframeTrack(`${node}.quaternion`, times, Float32Array.from(bone.rot)));
    }
    if (bone.scl?.length === json.frameCount * 3) {
      tracks.push(new THREE.VectorKeyframeTrack(`${node}.scale`, times, Float32Array.from(bone.scl)));
    }
  }
  return new THREE.AnimationClip(json.name ?? "mot", json.frameCount / fps, tracks);
}

/** Resolve the production model url for a borg id (pl0615 has a special path; others come from the library). */
function modelUrlFor(id: string): string {
  if (id === DEFAULT_LEAD) return "/models/pl0615/model_00.glb";
  if (!LIBRARY_IDS.has(id)) throw new Error(`No production model is registered for ${id}`);
  const entry = modelManifest.find((e) => e.id === id);
  if (!entry) throw new Error(`No production model manifest entry for ${id}`);
  if (!entry.glb) throw new Error(`No production GLB model file for ${id}`);
  return `/models/library/${id}/${entry.glb}`;
}

/** Load (and cache) a cloneable SOURCE model for a borg id. Returns a fresh clone per call. */
async function loadBorgModel(id: string): Promise<THREE.Object3D> {
  let sourceP = sourceModels.get(id);
  if (!sourceP) {
    const url = modelUrlFor(id);
    sourceP = renderAssets.loadGlbScene(url).then((model) => {
      prepareImportedModel(model, {
        centerXZ: true,
        groundY: true,
        materialSide: THREE.DoubleSide,
        metalness: 0,
        culling: "skinned-disabled",
      });
      return model;
    });
    sourceModels.set(id, sourceP);
  }
  const source = await sourceP;
  return renderAssets.cloneModel(source);
}

const animIndexCache = new Map<string, Promise<AnimIndex | null>>();

const SLOT_LABELS: Record<AnimSlot, RegExp[]> = {
  idle: [/^idle$/],
  move: [/^move$/, /^move_s\d+$/],
  dash: [/^dash_fwd$/, /^dash_(right|left|back)$/, /^boost$/],
  dash_fwd: [/^dash_fwd$/],
  dash_back: [/^dash_back$/],
  dash_left: [/^dash_left$/],
  dash_right: [/^dash_right$/],
  jump: [/^jump_takeoff$/, /^fly_transition$/, /^boost$/],
  // Descending part of a jump. jump_land is the exported landing/air-recovery bank
  // (g0s7 per research/format-specs/borg-animation-banks.md slot convention) — held
  // clamped it reads as the falling pose. Falls back to jump for borgs without it.
  fall: [/^jump_land$/],
  fly: [/^boost$/, /^fly_transition$/, /^move_s\d+$/],
  attack: [/^attack_s\d+$/, /^attack_lunge_s\d+$/],
  melee: [/^attack_lunge_s\d+$/, /^attack_s\d+$/],
  // Resolved via SLOT_VARIANTS (second distinct melee-pattern bank) so borgs with
  // multiple exported swings alternate; falls back to melee when only one exists.
  melee_alt: [],
  shoot: [/^attack_s\d+$/, /^special_s\d+$/],
  special: [/^special_s\d+$/],
  hit: [/^hit_react_s\d+$/, /^guard_s\d+$/],
  // g4s0 ("down_s0") is the real knockdown/getting-up pose, DERIVED from the decomp
  // cross-reference in research/format-specs/borg-animation-banks.md (high-confidence
  // knockdown=g4s0, matching the prior human-labeled `down_candidate` anchor) and
  // behavior-notes.md s4r. Previously this slot had no real match at all (the bake
  // script mislabeled g4s0 as a generic `special_s0`, so "down" silently fell back to
  // a hit/guard/death clip). hit_react/guard/death stay as TUNED fallbacks for borgs
  // whose g4s0 bank is missing or not yet re-baked with the corrected label.
  down: [/^down_s0$/, /^hit_react_s\d+$/, /^guard_s\d+$/, /^death$/],
  // down_s0 (the knockdown/fall-down pose, high-confidence per borg-animation-banks.md)
  // is a TUNED last-resort death stand-in for borgs with no death/win_or_death bank at
  // all (e.g. pl0500/pl0503/pl0504 flame dragons, pl0c00-pl0c05 fortresses) — previously
  // those borgs died standing in their idle loop.
  death: [/^death$/, /^win_or_death$/, /^down_s0$/],
  spawn: [/^pose_short$/, /^idle$/],
  victory: [/^victory$/, /^win_or_death$/],
};

const SLOT_FALLBACKS: Partial<Record<AnimSlot, AnimSlot[]>> = {
  dash_fwd: ["dash", "move", "idle"],
  dash_back: ["dash", "move", "idle"],
  dash_left: ["dash", "move", "idle"],
  dash_right: ["dash", "move", "idle"],
  dash: ["move", "idle"],
  move: ["idle"],
  jump: ["fly", "move", "idle"],
  fall: ["jump", "fly", "move", "idle"],
  fly: ["jump", "move", "idle"],
  attack: ["melee", "shoot", "move", "idle"],
  melee: ["attack", "idle"],
  melee_alt: ["melee", "attack", "idle"],
  shoot: ["attack", "special", "move", "idle"],
  special: ["attack", "idle"],
  hit: ["idle"],
  down: ["hit", "death", "idle"],
  death: ["idle"],
  spawn: ["idle"],
  victory: ["idle"],
};

const PREFERRED_LABELS: Partial<Record<string, Partial<Record<AnimSlot, string[]>>>> = {
  pl0615: {
    // G RED (borgs.json name "G RED", id pl0615 — the game's box-art mascot borg,
    // NOT pl0000 "NORMAL NINJA"). This is the DEFAULT_LEAD / most fully-animated borg.
    shoot: ["attack_s4"],
    melee: ["attack_lunge_s1"],
    hit: ["hit_react_s0"],
    // g4s0 ("special_s0" in the old mislabeled bake, now "down_s0") is actually the
    // knockdown/down pose, not a special move — see the `down` slot override below and
    // research/format-specs/borg-animation-banks.md's decomp cross-reference
    // (behavior-notes.md s4r). g4s1 (26f) is the real short special-move candidate;
    // g4s0 (81f) was previously wrongly used for "special" here, meaning G Red's special
    // attack was silently playing its own knockdown pose. DERIVED that g4s0 != special;
    // g4s1 as "the" special move is a reasonable TUNED pick among g4s1-4 (not individually
    // decomp-confirmed which of s1-s4 maps to the X-button special specifically).
    special: ["special_s1"],
    down: ["down_s0"],
    death: ["death"],
    victory: ["victory"],
  },
  // pl0008/pl000c/pl0105/pl0109 all had the same g4s0-as-"special" bug as pl0615
  // (their old special_s0 override pointed at the knockdown pose, now down_s0 — see
  // research/format-specs/borg-animation-banks.md + behavior-notes.md s4r). Each has
  // a distinct special_s1+ bank confirmed present in its anim_index.json, used here
  // instead. TUNED which of s1-s4 is "the" X-button special where multiple exist.
  pl0008: {
    melee: ["attack_lunge_s1"],
    hit: ["hit_react_s0"],
    special: ["special_s1"],
    down: ["down_s0"],
    death: ["death", "win_or_death"],
    victory: ["victory"],
  },
  pl000c: {
    melee: ["attack_lunge_s1"],
    hit: ["hit_react_s0"],
    special: ["special_s1"],
    down: ["down_s0"],
    death: ["death", "win_or_death"],
    victory: ["victory"],
  },
  pl0105: {
    melee: ["attack_lunge_s1"],
    hit: ["hit_react_s0"],
    special: ["special_s1"],
    down: ["down_s0"],
    death: ["death", "win_or_death"],
  },
  pl0109: {
    melee: ["attack_lunge_s1"],
    hit: ["guard_s11"],
    special: ["special_s1"],
    down: ["down_s0"],
    death: ["death", "win_or_death"],
  },
  // ---- Alt-mode-only borgs: whole moveset lives in unlabeled group-2 banks -------------
  // pl0619/pl061f/pl0628 export only `idle` plus g2_s* banks (no g0 locomotion, no g1
  // attacks), so every slot silently fell back to idle. Mappings DERIVED from a Rosetta
  // comparison verified across anim_index.json files: pl0c00/pl0c01's LABELED banks match
  // pl0619's g2 banks one-for-one on frames AND rootSpan (move 31f; dash 59f/rootZ 389;
  // g6_s0 61f/rootZ 104; g7 attack-length 37f; g7 flinch-length 13f; down 76f), and the
  // labeled siblings pl0604/pl0610/pl0613 embed byte-identical g2 sets (same frames and
  // root spans) to pl0619/pl061f/pl0628 respectively. Which 37f bank is shoot vs melee,
  // and dash sign (fwd-vs-back, left-vs-right; rootSpan is unsigned), are TUNED.
  pl0619: {
    move: ["g2_s1"], // 31f = pl0c00 `move` (31f)
    dash_fwd: ["g2_s4"], // 59f rootZ 389 = pl0c00 `dash_fwd` (59f, rootZ 389)
    dash_back: ["g2_s5"], // 59f = pl0c00 `dash_back`
    dash_left: ["g2_s7"], // 59f = pl0c00 `dash_right` (mirrored; no left bank exported)
    dash_right: ["g2_s7"],
    jump: ["g2_s24"], // 61f, the only bank with vertical root motion (rootY 100)
    fly: ["g2_s16"], // 61f rootZ 104 = pl0c00 `g6_s0` sustained-drift bank
    shoot: ["g2_s20"], // 37f, pl0c00-g7 attack-length
    melee: ["g2_s21"], // 37f
    hit: ["g2_s22"], // 13f flinch (= pl0c00 g7_s5 length)
    special: ["g2_s25"], // 81f rootZ 182, biggest action bank
    down: ["g2_s15"], // 76f = pl0c00 `down_s0` (76f)
    death: ["g2_s15"], // TUNED: knockdown pose held as death (no death bank exported)
  },
  pl061f: {
    move: ["g2_s1"], // 31f
    dash_fwd: ["g2_s4"], // 59f (structural analogy with pl0619; no rootSpan recorded)
    dash_back: ["g2_s5"],
    dash_left: ["g2_s7"],
    dash_right: ["g2_s7"],
    jump: ["g2_s16"], // no g2_s24 vertical jump bank; keep the existing airborne fallback explicit
    fly: ["g2_s16"], // 61f rootZ 104
    shoot: ["g2_s30"], // 37f (this borg's attack-length pair sits at s30/s31)
    melee: ["g2_s31"], // 37f
    hit: ["g2_s32"], // 13f flinch
    death: ["g2_s15"], // 76f knockdown-pose stand-in; its labeled down_s0 is only 15f
  },
  pl0628: {
    move: ["g2_s2"], // 31f family walk convention (its g2_s1 is a 12f stub)
    dash_fwd: ["g2_s4"], // 31f rootZ 500
    dash_back: ["g2_s5"], // 31f rootZ 500
    dash_left: ["g2_s7"], // 31f rootX 500 (mirrored for both sides)
    dash_right: ["g2_s7"],
    jump: ["g2_s24"], // 61f, same vertical-root jump slot convention as pl0619
    fly: ["g2_s16"], // 61f rootZ 100
    shoot: ["g2_s30"], // 37f
    melee: ["g2_s31"], // 37f
    hit: ["g2_s35"], // 13f flinch
    special: ["g2_s41"], // 63f (= pl0c00 g8_s1 length)
    death: ["g2_s44"], // 77f rootX 290, longest bank = death-per-convention; TUNED
  },
  // ---- One-sided lateral dash exports ------------------------------------------------
  // These families export only one lateral dash label. Use it as the mirrored opposite
  // side instead of falling through to dash_fwd, which made a side-step animate forward.
  pl0400: { dash_right: ["dash_left"] },
  pl0401: { dash_right: ["dash_left"] },
  pl0402: { dash_right: ["dash_left"] },
  pl0403: { dash_right: ["dash_left"] },
  pl0404: { dash_right: ["dash_left"] },
  pl0405: { dash_right: ["dash_left"] },
  pl0406: { dash_right: ["dash_left"] },
  pl0407: { dash_right: ["dash_left"] },
  pl040b: { dash_right: ["dash_left"] },
  pl0602: { dash_right: ["dash_left"] },
  // ---- pl0c00-pl0c05 fortress family: attacks/flinches live in unlabeled group 7 -------
  // No group-1 attacks or group-3 reacts are exported; g7 carries 37f attack-length and
  // 13f flinch-length banks (verified in each borg's anim_index.json — same Rosetta as
  // the pl0619 comment above). melee/hit previously fell back to idle.
  pl0c00: { dash_left: ["dash_right"], melee: ["g7_s0"], hit: ["g7_s5"] },
  pl0c01: { dash_left: ["dash_right"], melee: ["g7_s0"], hit: ["g7_s5"] },
  pl0c02: { dash_left: ["dash_right"], melee: ["g7_s0"], hit: ["g7_s5"] },
  pl0c05: {
    dash_left: ["dash_right"],
    melee: ["g7_s0"], // 37f
    shoot: ["g7_s1"], // 37f; unlike its siblings pl0c05 has no special_s* for shoot to use
    hit: ["g7_s5"], // 13f
    special: ["g8_s2"], // 77f (rootZ 290 on sibling pl0c00), biggest action bank; TUNED
  },
  pl0c04: {
    // No directional dash banks are exported. The 31f boost bank is the only short
    // locomotion burst and was already selected through generic dash fallback.
    dash_fwd: ["boost"],
    dash_back: ["boost"],
    dash_left: ["boost"],
    dash_right: ["boost"],
    melee: ["g7_s0"], // 61f; only attack-plausible bank (no g1/g3 exported)
  },
  // ---- Borgs with no group-3 hit reacts: short group-4 launch flinches instead ---------
  // pl0604/pl0610/pl0613 export no hit_react/guard banks; their g4 sets carry 10-15f
  // clips with pure vertical root motion (rootY 161/215/182 per anim_index.json) — the
  // launch/knock-up flinch. Previously hit fell back to idle (no reaction at all).
  pl0604: { hit: ["special_s2"] }, // 11f rootY 161
  pl0610: { hit: ["special_s1"] }, // 15f rootY 215
  pl0613: { hit: ["special_s2"] }, // 10f rootY 182
  // ---- Borgs whose only group-4 bank is the knockdown pose (down_s0) -------------------
  // After the g4s0 relabel (behavior-notes.md s4r) these have no special_s* left, so
  // "special" fell back through attack to attack_s0 — a 2-frame placeholder on several.
  // Use the longest exported lunge/attack bank instead (TUNED pick, banks verified in
  // each borg's anim_index.json).
  pl0301: { special: ["attack_lunge_s10"] }, // 54f
  pl0800: { special: ["attack_lunge_s18"] }, // 50f
  pl0805: { special: ["attack_lunge_s2"] }, // 71f
  pl0807: { special: ["attack_lunge_s13"] }, // 51f
  pl0808: { special: ["attack_lunge_s12"] }, // 50f
  pl0a00: { special: ["attack_s7"] }, // 71f
  pl0a01: { special: ["attack_s7"] }, // 51f
  pl0a02: { special: ["attack_s7"] }, // 56f
};

async function loadAnimIndex(id: string): Promise<AnimIndex | null> {
  let p = animIndexCache.get(id);
  if (!p) {
    p = fetch(`/models/${id}/anim_index.json`)
      .then((r) => (r.ok ? (r.json() as Promise<AnimIndex>) : null))
      .catch(() => null);
    animIndexCache.set(id, p);
  }
  return p;
}

// Variant slots reuse another slot's label tables but pick the Nth distinct matching
// bank, so the renderer can alternate between several exported swings/reacts. When a
// borg has fewer matches than the index needs, the variant resolves to null and
// SLOT_FALLBACKS (melee_alt -> melee) reproduces today's behavior exactly.
const SLOT_VARIANTS: Partial<Record<AnimSlot, { base: AnimSlot; index: number }>> = {
  melee_alt: { base: "melee", index: 1 },
};

// Banks shorter than this are placeholder poses (2-frame T-poses like pl0800's
// attack_s0), not playable actions — skip them when a longer bank also matches.
// idle/spawn are exempt: some borgs' real exported idle IS a 2f pose (pl0c00-pl0c05)
// and spawn's pose_short is intentionally 2f.
const MIN_ACTION_FRAMES = 5;
const PLACEHOLDER_OK_SLOTS = new Set<AnimSlot>(["idle", "spawn"]);

function pickAnimBank(index: AnimIndex, slot: AnimSlot): AnimBank | null {
  const direct = pickAnimBankDirect(index, slot);
  if (direct) return direct;
  for (const fallback of SLOT_FALLBACKS[slot] ?? []) {
    const bank = pickAnimBankDirect(index, fallback);
    if (bank) return bank;
  }
  return null;
}

function pickAnimBankDirect(index: AnimIndex, slot: AnimSlot): AnimBank | null {
  const variant = SLOT_VARIANTS[slot];
  const baseSlot = variant?.base ?? slot;
  const matches = collectAnimBankMatches(index, baseSlot);
  if (matches.length === 0) return null;
  const usable = PLACEHOLDER_OK_SLOTS.has(baseSlot)
    ? matches
    : matches.filter((bank) => bank.frames >= MIN_ACTION_FRAMES);
  const pool = usable.length > 0 ? usable : matches;
  return pool[variant?.index ?? 0] ?? null;
}

/** Every bank matching the slot's preferred labels + patterns, in pick-priority order. */
function collectAnimBankMatches(index: AnimIndex, slot: AnimSlot): AnimBank[] {
  const banks = [...index.banks].sort((a, b) => a.group - b.group || a.slot - b.slot || a.frames - b.frames);
  const matches: AnimBank[] = [];
  const seen = new Set<AnimBank>();
  const push = (bank: AnimBank | undefined): void => {
    if (bank && !seen.has(bank)) {
      seen.add(bank);
      matches.push(bank);
    }
  };
  for (const label of PREFERRED_LABELS[index.borg]?.[slot] ?? []) {
    push(banks.find((bank) => bank.label === label));
  }
  for (const pattern of SLOT_LABELS[slot]) {
    for (const bank of banks) {
      if (pattern.test(bank.label)) push(bank);
    }
  }
  return matches;
}

async function loadBorgClip(id: string, slot: AnimSlot): Promise<THREE.AnimationClip | null> {
  const key = `${id}:${slot}`;
  let p = clipCache.get(key);
  if (!p) {
    p = loadAnimIndex(id)
      .then((index) => {
        const bank = index ? pickAnimBank(index, slot) : null;
        return bank ? fetch(`/models/${id}/${bank.file}`) : null;
      })
      .then((r) => (r?.ok ? (r.json() as Promise<BakedClip>) : null))
      .then((json) => (json ? buildClip(json) : null))
      .catch(() => null);
    clipCache.set(key, p);
  }
  return p;
}

const battleScene = new BattleScene(battleRoot, {
  loadModel: loadBorgModel,
  loadClip: loadBorgClip,
  // Audio glue: edge-triggered per-slot cue for every actor (dash/melee/hit/down/death/...).
  // Overlaps with the sim-level edges in emitBattleAudioEdges by design; the per-event
  // min-gap map in playCombatSfx dedupes the two sources.
  onSlotEnter: (_borgId, slot) => playCombatSfx(slot),
});
const battleCamera = new BattleCamera({ camera, controlsTarget: controls.target });

// ------------------------------------------------------------------------------------------
// Stage loading (preserved)
// ------------------------------------------------------------------------------------------

function applyStageRenderState(rs: StageRenderState): void {
  // Delegates to the canonical module (validated 40/40 against on-disk render-state.json;
  // identical output for 39 stages, stff additionally gains its second directional). The
  // local StageRenderState type is a looser shape of the module's; same on-disk data.
  const resolved = applyStageRenderStateLighting(scene, stageLighting, rs as LightingStageRenderState);
  camera.fov = resolved.camera.fovDegrees;
  camera.near = resolved.camera.near;
  camera.far = resolved.camera.far;
  camera.updateProjectionMatrix();
}

let loadedStageId: string | null = null;
let loadedStageAssets: StageAssets<StageRenderState> | null = null;

async function loadStage(stageId: string): Promise<StageAssets<StageRenderState>> {
  if (!isExportedStageId(stageId)) throw new Error(`Stage is not exported: ${stageId}`);
  if (loadedStageId === stageId && loadedStageAssets) return loadedStageAssets;
  stageRoot.clear();
  const assets = await assetCatalog.loadStageAssets<StageRenderState>(stageId);
  applyStageRenderState(assets.renderState);
  const models = await Promise.all(assets.modelUrls.map((u) => renderAssets.loadGlbScene(u)));
  for (const model of models) {
    prepareImportedModel(model, {
      materialSide: THREE.FrontSide,
      metalness: 0,
      culling: "auto",
    });
    stageRoot.add(model);
  }
  loadedStageId = stageId;
  loadedStageAssets = assets;
  return loadedStageAssets;
}

async function loadInitialAssets(): Promise<void> {
  const manifest = await assetCatalog.loadModelManifest();
  modelManifest = manifest;
  for (const e of manifest) LIBRARY_IDS.add(e.id);
  LIBRARY_IDS.add(DEFAULT_LEAD);
  await loadStage(DEFAULT_ARENA_STAGE);
}

// ------------------------------------------------------------------------------------------
// Netcode hooks (preserved, dormant). Multiplayer is wired next; do not delete.
// ------------------------------------------------------------------------------------------

let ws: WebSocket | null = null;
function closeSocket(): void {
  ws?.close();
  ws = null;
}
void closeSocket; // referenced so the dormant hook isn't tree-shaken/flagged.

// ------------------------------------------------------------------------------------------
// Audio
// ------------------------------------------------------------------------------------------

let audioManagerPromise: Promise<GotchaAudioManager | null> | null = null;
let activeBgmKey: string | null = null;
let pendingBgmKey: string | null = null;

function initAudio(): Promise<GotchaAudioManager | null> {
  if (!audioManagerPromise) {
    audioManagerPromise = createAudioManager().catch(() => null);
  }
  return audioManagerPromise;
}

function queueBgm(key: string): void {
  pendingBgmKey = key;
  void playPendingBgm();
}

async function playPendingBgm(): Promise<void> {
  const key = pendingBgmKey;
  if (!key) return;
  if (key === activeBgmKey) {
    pendingBgmKey = null;
    return;
  }
  const audio = await initAudio();
  if (!audio) return;
  try {
    await audio.playBgm(key);
    activeBgmKey = key;
    if (pendingBgmKey === key) pendingBgmKey = null;
  } catch {
    // Browsers reject autoplay before the first user gesture. Keep pending and
    // retry from the next key/click/touch event.
  }
}

function playSfx(key: string | null): void {
  if (!key) return;
  void initAudio().then((audio) => {
    if (!audio) return;
    void audio.playSfx(key).catch(() => undefined);
  });
}

function playConfirmSfx(): void {
  playSfx(AUDIO_CUES.confirm);
}

function playBackSfx(): void {
  playSfx(AUDIO_CUES.back);
}

function playEditSfx(): void {
  playSfx(AUDIO_CUES.edit);
}

// ------------------------------------------------------------------------------------------
// Input
// ------------------------------------------------------------------------------------------

const keys = new Set<string>();
window.addEventListener("keydown", (e) => {
  if (isTextInputTarget(e.target)) return;
  void playPendingBgm();
  // Tab would move focus; capture it for switch-lock during battle.
  if (e.code === "Tab" && flow.screen === "battle") e.preventDefault();
  // Backquote toggles the ATK-015 debug overlay (sim-state readout for the focused borg).
  if (e.code === "Backquote") debugOverlay.setVisible(!debugOverlay.visible);
  keys.add(e.code);
});
window.addEventListener("keyup", (e) => keys.delete(e.code));
window.addEventListener("pointerdown", () => {
  void playPendingBgm();
});

function isTextInputTarget(target: EventTarget | null): boolean {
  return (
    target instanceof HTMLInputElement ||
    target instanceof HTMLSelectElement ||
    target instanceof HTMLTextAreaElement
  );
}

const NO_KEYS: ReadonlySet<string> = new Set();

function activeGamepad(playerIndex = 0, allowFallback = playerIndex === 0): Gamepad | null {
  const pads = navigator.getGamepads?.();
  if (!pads) return null;
  const exact = pads[playerIndex];
  if (exact?.connected) return exact;
  return allowFallback ? pads.find((g) => g?.connected) ?? null : null;
}

// ------------------------------------------------------------------------------------------
// Challenge flow state machine
// ------------------------------------------------------------------------------------------

type Screen =
  | "menu"
  | "difficulty"
  | "players"
  | "load-box"
  | "select-force"
  | "force"
  | "briefing"
  | "battle"
  | "results"
  | "loading";

interface Flow {
  screen: Screen;
  budget: number;
  playerCount: number;
  selectedForceSlot: number;
  forceSlots: ForceSlot[];
  run: ChallengeRun | null;
}

const flow: Flow = {
  screen: "loading",
  budget: 2000,
  playerCount: 1,
  selectedForceSlot: 0,
  forceSlots: BORG_CATALOG.defaultForceSlots.map((slot) => ({ ...slot, borgIds: [...slot.borgIds] })),
  run: null,
};

function mountScreen(build: (root: HTMLElement) => { destroy(): void }): void {
  screenHost.mount(build);
}

function showMenu(initial: MainMenuMode = "challenge"): void {
  flow.screen = "menu";
  queueBgm(AUDIO_CUES.menuBgm);
  mountScreen((root) =>
    createMainMenu(root, {
      initial,
      onSelect: (mode) => {
        if (mode === "challenge") {
          playConfirmSfx();
          showDifficulty();
        } else if (mode === "edit-force") {
          playEditSfx();
          showForceBuilder("menu");
        }
      },
    }),
  );
}

function showDifficulty(): void {
  flow.screen = "difficulty";
  mountScreen((root) =>
    createSelectDifficulty(root, {
      onSelect: (budget) => {
        playConfirmSfx();
        flow.budget = budget;
        showPlayers();
      },
      onBack: () => {
        playBackSfx();
        showMenu();
      },
    }),
  );
}

function showPlayers(): void {
  flow.screen = "players";
  mountScreen((root) =>
    createSelectPlayers(root, {
      maxPlayers: 2,
      onSelect: (count) => {
        playConfirmSfx();
        flow.playerCount = count;
        showLoadBoxData();
      },
      onBack: () => {
        playBackSfx();
        showDifficulty();
      },
    }),
  );
}

function showLoadBoxData(): void {
  flow.screen = "load-box";
  mountScreen((root) =>
    createLoadBoxData(root, {
      onConfirm: () => {
        playConfirmSfx();
        showSelectForce();
      },
      onSkip: () => {
        playConfirmSfx();
        showSelectForce();
      },
      onBack: () => {
        playBackSfx();
        showPlayers();
      },
    }),
  );
}

function showSelectForce(): void {
  flow.screen = "select-force";
  mountScreen((root) =>
    createSelectForce(root, {
      catalog: FORCE_CATALOG,
      slots: flow.forceSlots,
      selectedSlot: flow.selectedForceSlot,
      limit: flow.budget,
      onSelectSlot: (slotIndex) => {
        playSfx(AUDIO_CUES.confirm);
        flow.selectedForceSlot = slotIndex;
      },
      onConfirm: (slot) => {
        playConfirmSfx();
        flow.selectedForceSlot = Math.max(0, flow.forceSlots.findIndex((candidate) => candidate.no === slot.no));
        startRun();
      },
      onEdit: (slot) => {
        playEditSfx();
        flow.selectedForceSlot = Math.max(0, flow.forceSlots.findIndex((candidate) => candidate.no === slot.no));
        showForceBuilder("select-force");
      },
      onBack: () => {
        playBackSfx();
        showLoadBoxData();
      },
    }),
  );
}

function showForceBuilder(returnTo: "select-force" | "menu" = "select-force"): void {
  flow.screen = "force";
  mountScreen((root) =>
    createForceBuilder(root, {
      catalog: FORCE_CATALOG,
      limit: flow.budget,
      initialForce: selectedForce(),
      onConfirm: (force) => {
        playConfirmSfx();
        updateSelectedForceSlot(force);
        if (returnTo === "menu") showMenu("edit-force");
        else showSelectForce();
      },
      onQuit: () => {
        playBackSfx();
        if (returnTo === "menu") showMenu("edit-force");
        else showSelectForce();
      },
    }),
  );
}

function startRun(): void {
  const force = selectedForce();
  updateSelectedForceSlot(force);
  const humanPlayerCount = Math.max(1, Math.min(flow.playerCount, 2));
  const playerForces = Array.from({ length: humanPlayerCount }, (_, player) => ({
    player,
    borgIds: player === 0 ? force : forceFromSlot(forceSlotForPlayer(player)),
  }));
  flow.run = createChallengeRun({
    budget: flow.budget,
    playerCount: humanPlayerCount,
    playerForces,
    borgs: BORG_CATALOG.roster as Parameters<typeof createChallengeRun>[0]["borgs"],
  });
  const battle = flow.run.getCurrentBattle();
  if (!battle) {
    showMenu();
    return;
  }
  showBattleIntro(battle);
}

function showBattleIntro(config: MissionBattleConfig): void {
  flow.screen = "briefing";
  queueBgm(AUDIO_CUES.menuBgm);
  mountScreen((root) =>
    createBattleIntro(root, {
      config,
      catalog: FORCE_CATALOG,
      onConfirm: () => {
        playConfirmSfx();
        void enterBattle(config);
      },
      onBack: () => {
        playBackSfx();
        showSelectForce();
      },
    }),
  );
}

// ------------------------------------------------------------------------------------------
// Battle
// ------------------------------------------------------------------------------------------

interface BattleSession {
  battle: Battle;
  config: MissionBattleConfig;
  hud: BattleHudHandle;
  localPlayerId: string;
  localPlayerIds: string[];
  stageBounds: RectStageBounds;
  allyMax: number;
  enemyMax: number;
  paused: boolean;
  pauseHandle: { destroy(): void } | null;
  resolved: boolean;
}

let session: BattleSession | null = null;
let simAccumulator = 0;
const SIM_DT = 1 / 60;

async function enterBattle(config: MissionBattleConfig): Promise<void> {
  flow.screen = "loading";
  queueBgm(AUDIO_CUES.battleBgm);
  screenHost.clear();

  const boot = await createBattleBootstrap({
    config,
    playerCount: flow.playerCount,
    stageCatalog: EXPORTED_STAGE_CATALOG_ADAPTER,
    borgStats: BORG_CATALOG.combatStats,
    loadStageAssets: loadStage,
  });
  const { battle, localPlayerId, localPlayerIds, stageBounds } = boot;

  // Energy maxima for the HUD meters (team 0 = ally, team 1 = enemy).
  const { allyMax, enemyMax } = battleEnergyMaxima(battle);

  // Mount the HUD.
  const hud = createBattleHud(ui, { showBanner: false });

  session = {
    battle,
    config,
    hud,
    localPlayerId,
    localPlayerIds,
    stageBounds,
    allyMax,
    enemyMax,
    paused: false,
    pauseHandle: null,
    resolved: false,
  };
  simAccumulator = 0;
  battleScene.clear();
  flow.screen = "battle";
  // Prime the scene + HUD on frame 0.
  const initialScene = battleSceneState(battle, localFocusBorg());
  battleScene.sync(initialScene.borgs, initialScene.projectiles, initialScene.focusUid);
  const focus = localFocusBorg();
  const focusPos = focus ? battleScene.positionOf(focus.uid) : null;
  battleCamera.snapTo(focus && focusPos ? { pos: focusPos, rotY: focus.rotY } : null);
  updateHud();
}

function localActiveUid(): string | null {
  return currentBattlePresentation()?.activeUid ?? null;
}

function localFocusBorg(): BorgRuntime | null {
  return currentBattlePresentation()?.focus ?? null;
}

function currentBattlePresentation(): ReturnType<typeof battlePresentationState> | null {
  if (!session) return null;
  return battlePresentationState({
    battle: session.battle,
    localPlayerId: session.localPlayerId,
    allyMax: session.allyMax,
    enemyMax: session.enemyMax,
    defaultBorgId: DEFAULT_LEAD,
    actionProfileFor: (borgId) => BORG_CATALOG.actionProfileFor(borgId),
  });
}

function updateHud(): void {
  if (!session) return;
  const presentation = currentBattlePresentation();
  if (presentation) session.hud.update(presentation.hud);
}

// Pause handling (Start/Esc).
let pausePressedLast = false;
function pollPauseToggle(): void {
  if (!session || session.resolved) return;
  const pad = activeGamepad();
  const startPressed = keys.has("Escape") || keys.has("Enter") || (pad?.buttons[9]?.pressed ?? false);
  if (startPressed && !pausePressedLast) {
    if (session.paused) resumeBattle();
    else pauseBattle();
  }
  pausePressedLast = startPressed;
}

function pauseBattle(): void {
  if (!session || session.paused) return;
  session.paused = true;
  session.pauseHandle = createPauseMenu(ui, {
    onResume: resumeBattle,
    onQuit: () => {
      session?.pauseHandle?.destroy();
      if (session) session.paused = false;
      endBattleToMenu();
    },
  });
}

function resumeBattle(): void {
  if (!session) return;
  session.pauseHandle?.destroy();
  session.pauseHandle = null;
  session.paused = false;
}

function endBattleToMenu(): void {
  teardownBattle();
  showMenu();
}

function teardownBattle(): void {
  session?.hud.destroy();
  session?.pauseHandle?.destroy();
  battleScene.clear();
  session = null;
}

// The sim advances on a wall-clock interval (NOT requestAnimationFrame) so a
// battle keeps progressing even when the tab is backgrounded (rAF is throttled
// to ~0 Hz while hidden). dt is clamped so returning from a long background gap
// fast-forwards a bounded number of frames instead of one giant spike.
function stepBattle(dt: number): void {
  if (!session || session.paused || session.resolved) return;
  const { battle } = session;

  simAccumulator += Math.min(dt, 0.25);
  // Fixed 60 Hz; collect local input once and apply for each sub-step.
  const inputs: Record<string, PlayerInput> = {};
  for (let playerIndex = 0; playerIndex < session.localPlayerIds.length; playerIndex += 1) {
    const playerId = session.localPlayerIds[playerIndex] ?? playerIdFor(playerIndex);
    const active = activeBorgForPlayer(battle, playerId);
    const keySource = playerIndex === 0 ? keys : NO_KEYS;
    const pad = activeGamepad(playerIndex, session.localPlayerIds.length === 1 && playerIndex === 0);
    inputs[playerId] = active ? inputFromKeys(keySource, pad) : emptyInput();
  }

  let steps = 0;
  while (simAccumulator >= SIM_DT && steps < 15) {
    const audioBefore = snapshotBattleAudio(battle, session.localPlayerId, session.allyMax);
    battle.step(SIM_DT, inputs);
    for (const cue of battleAudioEvents(audioBefore, snapshotBattleAudio(battle, session.localPlayerId, session.allyMax))) {
      playBattleEventSfx(cue);
    }
    simAccumulator -= SIM_DT;
    steps += 1;
    if (battle.state.result !== "ongoing") break;
  }

  const sceneState = battleSceneState(battle, localFocusBorg());
  battleScene.sync(sceneState.borgs, sceneState.projectiles, sceneState.focusUid);
  updateHud();

  if (battle.state.result !== "ongoing") resolveBattle();
}

// Battle-camera framing: see apps/game/src/sim/camera.ts header for the full DERIVED-vs-TUNED
// breakdown (ram-trace-analysis.md §3.1 height-offset/distance/smoothing evidence, plus a TUNED
// multi-actor widen-to-fit heuristic since no ROM multi-actor framing algorithm was found).
function followCamera(): void {
  if (!session) return;
  const focus = localFocusBorg();
  const target = focus ? battleScene.positionOf(focus.uid) : null;
  const primary = focus && target ? { pos: target, rotY: focus.rotY } : null;
  const positions = battleLiveActorPositions(session.battle, (uid) => battleScene.positionOf(uid));
  battleCamera.update(primary, positions, session.stageBounds);
}

function updateBattleDebugDataset(): void {
  if (!ENABLE_BATTLE_DEBUG_DATASET) return;
  if (!session || flow.screen !== "battle") {
    delete ui.dataset["gfBattleDebug"];
    return;
  }
  const activeUid = localActiveUid();
  const focusUid = localFocusBorg()?.uid ?? null;
  const rounded = (v: number): number => Math.round(v * 10) / 10;
  ui.dataset["gfBattleDebug"] = JSON.stringify({
    activeUid,
    focusUid,
    camera: [rounded(camera.position.x), rounded(camera.position.y), rounded(camera.position.z)],
    target: [rounded(controls.target.x), rounded(controls.target.y), rounded(controls.target.z)],
    bounds: session.stageBounds,
    borgs: session.battle.state.borgs.map((b) => ({
      uid: b.uid,
      team: b.team,
      borgId: b.borgId,
      alive: b.alive,
      hp: b.hp,
      state: b.state,
      pos: [rounded(b.pos.x), rounded(b.pos.y), rounded(b.pos.z)],
      vel: [rounded(b.vel.x), rounded(b.vel.y), rounded(b.vel.z)],
      lockTarget: b.lockTarget,
      allyLockTarget: b.allyLockTarget,
    })),
  });
}

function resolveBattle(): void {
  if (!session || session.resolved) return;
  session.resolved = true;
  const outcome = battleOutcomeFromState(session.battle);
  const results = computeResults(outcome);

  showResults(outcome.win ? "win" : "lose", {
    attack: results.attack,
    hitRatio: results.hitRatio * 100,
    dodgeRatio: results.dodgeRatio * 100,
    enemyBorgsDefeated: results.enemyBorgsDefeated,
    enemyTotalCost: Math.round(outcome.costWon),
    playerBorgsDefeated: results.playerBorgsDefeated,
    playerTotalCost: Math.round(outcome.costLost),
    allyBorgsDefeated: results.allyBorgsDefeated,
    grandTotal: results.grandTotal,
  }, results);
}

function showResults(
  result: "win" | "lose",
  stats: Parameters<ReturnType<typeof createResults>["render"]>[1],
  battleResults: BattleResults,
): void {
  // Tear down HUD but keep the battle scene visible behind the results.
  session?.hud.destroy();
  session?.pauseHandle?.destroy();
  flow.screen = "results";

  const handle = createResults(ui, {
    onAdvance: () => {
      handle.destroy();
      advanceRun(battleResults);
    },
  });
  handle.render(result, stats);
  screenHost.set(handle);
}

function advanceRun(lastResult: BattleResults): void {
  const run = flow.run;
  battleScene.clear();
  session = null;

  if (!run) {
    showMenu();
    return;
  }
  const progress = run.next(lastResult);
  if (progress.action === "advance" && progress.nextBattle) {
    showBattleIntro(progress.nextBattle);
  } else {
    // "complete" (won the whole run) or "title" (lost) -> back to menu.
    showMenu();
  }
}

// ------------------------------------------------------------------------------------------
// Main loop
// ------------------------------------------------------------------------------------------

// Render loop (requestAnimationFrame): drives animation mixers, the follow
// camera, and the WebGL render. Sim stepping is handled by the interval below.
const renderClock = new THREE.Clock();
function tick(): void {
  const dt = Math.min(renderClock.getDelta(), 0.05);
  if (flow.screen === "battle" || flow.screen === "results") {
    battleScene.update(dt);
    if (flow.screen === "battle") followCamera();
  }
  updateBattleDebugDataset();
  if (debugOverlay.visible) {
    debugOverlay.update(flow.screen === "battle" ? localFocusBorg() : null);
  }
  controls.update();
  viewport.render();
}

// Sim loop (setInterval): fixed-cadence wall-clock stepping, runs even when the
// tab is hidden. ~60 Hz target.
startFixedStepLoop({
  step(dt) {
    if (flow.screen === "battle") {
      pollPauseToggle();
      stepBattle(dt);
    }
  },
});

window.addEventListener("resize", () => {
  viewport.resize();
});

// ------------------------------------------------------------------------------------------
// Boot
// ------------------------------------------------------------------------------------------

ensureStyles();
showLoadingMessage("Loading extracted stage + model assets…");

void loadInitialAssets()
  .then(() => {
    showMenu();
  })
  .catch((error: unknown) => {
    showLoadingMessage(`Asset load failed: ${error instanceof Error ? error.message : String(error)}`);
  });

startRenderLoop({ frame: tick });

function showLoadingMessage(text: string): void {
  flow.screen = "loading";
  screenHost.clear();
  const box = document.createElement("div");
  box.style.cssText =
    "position:absolute;left:50%;top:50%;transform:translate(-50%,-50%);color:#bfeeff;font:600 16px 'Trebuchet MS',system-ui,sans-serif;text-align:center;text-shadow:0 1px 3px #000;";
  box.textContent = text;
  ui.appendChild(box);
}

// Expose a tiny debug handle for live verification in the preview.
(window as unknown as { __gf: unknown }).__gf = {
  flow,
  keys,
  get input() {
    return inputFromKeys(keys, activeGamepad());
  },
  get session() {
    return session;
  },
  stages: EXPORTED_STAGE_CATALOG,
  loadStage: async (stageId: string) => {
    const normalized = stageId.trim().toLowerCase();
    if (!isExportedStageId(normalized)) throw new Error(`Stage is not exported: ${stageId}`);
    await loadStage(normalized);
    viewport.render();
    return normalized;
  },
  startChallenge: () => showDifficulty(),
  renderDiagnostics: () => viewport.diagnostics(),
  renderNow: () => {
    return viewport.captureFrame();
  },
  forceBattle: (force: string[] = [DEFAULT_LEAD]) => {
    flow.budget = 2000;
    flow.playerCount = 1;
    updateSelectedForceSlot(force);
    startRun();
  },
};
