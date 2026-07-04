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
import { createAudioManager, loadAudioManifest, type GotchaAudioManager } from "@gf/audio";
import {
  createChallengeRun,
  computeResults,
  playerIdFor,
  type ChallengeRun,
  type MissionBattleConfig,
  type BattleResults,
} from "@gf/missions";

import {
  ensureStyles,
  createTitleIntro,
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
  type TeammateMarker,
} from "./ui/index.js";

import {
  EXPORTED_STAGE_CATALOG_ADAPTER,
  inputFromKeys,
  DEFAULT_ARENA_STAGE,
  EXPORTED_STAGE_CATALOG,
  isExportedStageId,
} from "./sim/adapter.js";
import { createBattleBootstrap } from "./sim/battleBootstrap.js";
import { BattleScene } from "./sim/battleScene.js";
import { BORG_CATALOG, DEFAULT_LEAD } from "./sim/borgCatalog.js";
import { createBorgPresentationAssets } from "./sim/borgPresentationAssets.js";
import { BattleCamera } from "./sim/camera.js";
import {
  activeBorgForPlayer,
  battleEnergyMaxima,
  battleOutcomeFromState,
  battlePresentationState,
  battleSceneState,
  battleAudioEvents,
  battleVoiceCues,
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

// "land" is not a BattleEventCue/AnimSlot: it is synthesized from the air->ground slot edge in
// onSlotEnter below so the DERIVED landing sample (id 0x1e) has an event to hang off.
type CombatSfxCue = BattleEventCue | "land";

// Battle event -> SFX cue mapping. Split DERIVED / TUNED per event:
//
// DERIVED (se_<hex> keys): REAL GameCube combat samples. The decomp recovered 11 combat events
// with literal soundIds (research/decomp/data/combat-se-ids.json; dispatcher zz_00efb3c_ decodes
// id as bank=id>>7, sample=id&0x7f). Those ids resolve through the battle soundbanks
// snd_com01/02/03 (afs_data.afs members 2839..2847: TSBD id table -> CHD tone/DSP header ->
// DPK GC DSP-ADPCM data; bank->slot order proven by the DOL bank table DAT_802d0bec @ boot.dol
// 0x2cdbec). scripts/export-combat-se.py decodes them to audio/se/se_<id>.ogg with an id-keyed
// manifest that initAudio() merges into the audio manager.
//
// TUNED (se00_* keys): events with NO recovered literal id keep the older waveform-guess
// assignments (poq_adx_usa.afs members 33..37, see AUDIO-PORT-STATUS.md). Per combat-se-ids.json
// these are genuinely un-derivable from code constants: melee swings / per-move whooshes are
// PATH-B animation-data sounds (soundIds live in per-move animation blobs at actor+0x4e8, not in
// code), death audio comes from the death reaction ANIMATION's embedded events (cue id 9 is an
// anim selector, not a soundId), and charge/lockon/alert have no traced ids at all.
//
// Exported but deliberately unwired: se_013 (heavy-borg-family crash variant of se_010 — the
// real branch is on borg family, which the port does not model here yet), se_026 (actor-vs-actor
// body bump — no bump event in the sim), se_09b (grab/throw connect — no throw mechanic yet).
// Guard-break ids 0x00/0x80/0x100 turned out to be TSB-muted (volume byte 0) in all three real
// banks — the "layered break stinger" plays silence on hardware — so there is no break sample to
// wire (scripts/export-combat-se.py HONEST NOTES).
const COMBAT_SFX: Partial<Record<CombatSfxCue, string>> = {
  // melee/melee_alt are FALLBACKS only since the PATH-B extraction (2026-07-04): swings whose
  // stream resolved authored per-anim sound events play those instead (playAuthoredSwingSounds
  // below; research/decomp/anim-sound-op-decode-2026-07-04.md decodes the actor+0x4e8 table).
  melee: "se00_03", // TUNED fallback for borgs without extracted authored swing audio
  melee_alt: "se00_03", // TUNED: same
  shoot: "se_008", // DERIVED: projectile-spawn id 0x08 (zz_006ee14_, fired from weapon-FIRE handler)
  special: "se00_02", // TUNED
  // TUNED: hold-B charge build-up (edge-detected in presentation.ts battleAudioEvents when
  // chargeFrames leaves 0). se00_02's "slow build then burst" waveform (AUDIO-PORT-STATUS.md)
  // is the only exported cue whose envelope reads as a build-up, so the hold reuses it.
  charge_start: "se00_02",
  // TUNED: charge tier-1/tier-2 crossings (thresholds read from the borg's action profile in
  // presentation.ts, NOT hardcoded here). The short tonal se00_04 doubles as the tier-up
  // "tick"; no dedicated tier chime exists in the exported set.
  charge_tier1: "se00_04",
  charge_tier2: "se00_04",
  charge_release: "se00_02",
  // DERIVED: knockback crash impact id 0x10 (FUN_8005a580, light/default borg families). The
  // heavy-family variant 0x13 is exported as se_013 but unwired until the port models families.
  hit: "se_010",
  down: "se_0dd", // DERIVED: knockdown thud id 0xdd (state slot 30; ROM plays it pitched via zz_00f061c_)
  death: "se00_01", // TUNED: death audio is a reaction-animation data cue, not a literal id
  dash: "se_0f2", // DERIVED: dash/boost/warp-launch id 0xf2 (start_forced_move_to_point et al.)
  dash_fwd: "se_0f2",
  dash_back: "se_0f2",
  dash_left: "se_0f2",
  dash_right: "se_0f2",
  jump: "se_025", // DERIVED: launch-state id 0x25 (FUN_80061338) — jump was previously unmapped
  spawn: "se_0f2", // DERIVED: 0xf2 is also the deploy/warp-entrance launch (FUN_8005e868, state slot 33)
  land: "se_01e", // DERIVED id 0x1e (landing/footfall states); the TRIGGER edge below is TUNED presentation
  lockon: "se00_04", // TUNED
  alert: "se00_02", // TUNED
};

// Rate limits are keyed by EVENT (not by file), so e.g. a damage-taken cue is not swallowed by a
// just-played melee swing that happens to share the same sample.
const COMBAT_SFX_MIN_GAP_MS: Partial<Record<CombatSfxCue, number>> = {
  melee: 220,
  melee_alt: 220,
  shoot: 180,
  special: 450,
  // charge_start can only re-fire after a release zeroes chargeFrames; the gap guards a
  // rapid tap-tap-tap on a chargeable trigger from stacking the 1.07s build-up clip.
  charge_start: 450,
  // Tier crossings fire at most once per hold each (chargeFrames is capped at tier2);
  // the small gap only de-dupes a tier1 tick against an immediately following tier2 when
  // thresholds sit close together on some profile.
  charge_tier1: 300,
  charge_tier2: 300,
  charge_release: 450,
  hit: 180,
  down: 450,
  death: 700,
  dash: 400,
  dash_fwd: 400,
  dash_back: 400,
  dash_left: 400,
  dash_right: 400,
  jump: 300,
  spawn: 500,
  land: 250,
  lockon: 150,
  alert: 1500,
};
const lastCombatSfxAt = new Map<string, number>();

function playCombatSfx(cue: CombatSfxCue): void {
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
  // Authored-audio suppression (DERIVED data, TUNED routing): when the LOCAL borg's current
  // swing/charged release carries ROM-authored PATH-B sound events (BorgRuntime.meleeSounds,
  // research/decomp/anim-sound-op-decode-2026-07-04.md), the slot-enter path below plays
  // those exact samples — skip the generic TUNED cue here so the same swing/release doesn't
  // double-play (the sim edge fires in the same tick as the slot edge).
  if ((cue === "melee" || cue === "charge_release") && localActiveBorgHasAuthoredSwingAudio()) return;
  playCombatSfx(cue);
}

function localActiveBorgHasAuthoredSwingAudio(): boolean {
  if (!session) return false;
  const active = activeBorgForPlayer(session.battle, session.localPlayerId);
  return (active?.meleeSounds?.length ?? 0) > 0;
}

// Authored PATH-B swing audio (research/decomp/anim-sound-op-decode-2026-07-04.md): each
// melee swing / charged release's action-script stream plays an anim whose descriptor binds
// a list of {frame, soundId} events (ROM actor+0x4e8 table). The sim resolves them per swing
// (BorgRuntime.meleeSounds, DERIVED end-to-end) and the slot-enter edge schedules each event
// at its anim-clock frame (60fps). TUNED residue, labeled honestly: the schedule hangs off
// the renderer's slot edge + wall clock (not the ROM part-anim clock), mode-1 events play the
// base id only (no anim-rate id±1 variant select), and positional modes play flat.
const AUTHORED_SWING_SLOTS: ReadonlySet<string> = new Set(["melee", "melee_alt", "charge_shot"]);
/** Per-SAMPLE floor so 8 simultaneous AI swings can't stack the same whoosh into clipping;
 *  keys live in lastCombatSfxAt's se_* keyspace, disjoint from the per-EVENT cue keys. */
const AUTHORED_SE_MIN_GAP_MS = 150;
/** Defensive cap: swing sound frames are single-digit-to-~21 in the extracted data; anything
 *  wildly larger would be a data bug, not a real cue. */
const AUTHORED_MAX_DELAY_MS = 2000;

function seKeyForSoundId(id: number): string {
  return `se_${id.toString(16).padStart(3, "0")}`;
}

function playAuthoredSwingSounds(sounds: readonly { frame: number; id: number }[]): void {
  if (DISABLE_COMBAT_SFX) return;
  for (const sound of sounds) {
    const delayMs = Math.min((sound.frame * 1000) / 60, AUTHORED_MAX_DELAY_MS);
    window.setTimeout(() => {
      const key = seKeyForSoundId(sound.id);
      const now = performance.now();
      if (now - (lastCombatSfxAt.get(key) ?? -Infinity) < AUTHORED_SE_MIN_GAP_MS) return;
      lastCombatSfxAt.set(key, now);
      playSfx(key);
    }, delayMs);
  }
}

// Landing-cue edge detection state (see onSlotEnter below): a borg whose anim slot goes from an
// airborne slot to a grounded one just touched down. Keyed by actor uid; stale entries from a
// previous battle are harmless (worst case one spurious rate-limited land tick on re-entry).
const LANDING_FROM_SLOTS: ReadonlySet<string> = new Set(["jump", "fall", "fly"]);
const LANDING_TO_SLOTS: ReadonlySet<string> = new Set(["idle", "move"]);
const lastAnimSlotByUid = new Map<string, string>();

// Per-borg VOICE cues (behavior-notes (az)): deploy shout / death cry keyed on the borg family.
// The family→voice-group mapping is DERIVED from the asset naming; the deploy=00 / death=01 role
// binding is TUNED (no traced voice table). Rate-limited per voice key so a rapid deploy→KO→deploy
// cycle can't stack the same clip on itself. playSfx transparently resolves voice-type manifest
// keys (the audio manager falls back to its voice map) and swallows a missing/blocked key.
const VOICE_MIN_GAP_MS = 500;
const lastVoiceAt = new Map<string, number>();

function playBorgVoice(key: string): void {
  if (DISABLE_COMBAT_SFX) return;
  const now = performance.now();
  if (now - (lastVoiceAt.get(key) ?? -Infinity) < VOICE_MIN_GAP_MS) return;
  lastVoiceAt.set(key, now);
  playSfx(key);
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
  const valid = BORG_CATALOG.rosterIndex.validIds(borgIds, { fallbackId: DEFAULT_LEAD });
  flow.forceSlots[flow.selectedForceSlot] = {
    ...slot,
    borgIds: valid,
  };
}

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

const assetCatalog = createPublicAssetCatalog();
const borgPresentationAssets = createBorgPresentationAssets({
  assetLoader: renderAssets,
  defaultLeadId: DEFAULT_LEAD,
});
const battleScene = new BattleScene(battleRoot, {
  loadModel: borgPresentationAssets.loadModel,
  loadClip: borgPresentationAssets.loadClip,
  loadClipByStreamRef: borgPresentationAssets.loadClipByStreamRef,
  // Audio glue: edge-triggered per-slot cue for every actor (dash/melee/hit/down/death/...).
  // Overlaps with the sim-level edges in emitBattleAudioEdges by design; the per-event
  // min-gap map in playCombatSfx dedupes the two sources. The air->ground slot edge
  // synthesizes the "land" cue: the SAMPLE is the DERIVED landing id 0x1e (se_01e), but the
  // trigger edge itself is TUNED presentation (the ROM fires it from landing state slot 31
  // and grounded-recovery handlers, which the port's slot machine does not model 1:1).
  onSlotEnter: (_borgId, slot, uid, meleeSounds) => {
    const prev = lastAnimSlotByUid.get(uid);
    lastAnimSlotByUid.set(uid, slot);
    if (prev !== undefined && LANDING_FROM_SLOTS.has(prev) && LANDING_TO_SLOTS.has(slot)) {
      playCombatSfx("land");
    }
    // Authored per-swing audio (DERIVED — see playAuthoredSwingSounds): replaces the TUNED
    // slot cue for THIS swing/release only; borgs without authored sounds keep the fallback.
    if (AUTHORED_SWING_SLOTS.has(slot) && meleeSounds && meleeSounds.length > 0) {
      playAuthoredSwingSounds(meleeSounds);
      return;
    }
    playCombatSfx(slot);
  },
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
      // HSD stage exports include large single-sided planes/inside-facing pieces, but the
      // runtime GLB pipeline does not preserve per-material cull-mode flags yet. Render stages
      // double-sided like the borg/UI HSD imports so arena surfaces stay readable from the
      // battle camera instead of disappearing or blacking out at gameplay angles.
      materialSide: THREE.DoubleSide,
      metalness: 0,
      culling: "auto",
      // TUNED threshold (HSD PEDesc alpha-compare state is undecoded): discard near-invisible
      // texels of BLEND-mode stage props so their invisible quad corners stop writing depth
      // and punching holes into geometry behind them.
      transparentAlphaTest: 0.1,
    });
    stageRoot.add(model);
  }
  loadedStageId = stageId;
  loadedStageAssets = assets;
  return loadedStageAssets;
}

async function loadInitialAssets(): Promise<void> {
  const manifest = await assetCatalog.loadModelManifest();
  borgPresentationAssets.setModelManifest(manifest);
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
    audioManagerPromise = (async () => {
      const manifest = await loadAudioManifest();
      // Merge the DERIVED combat-SE manifest (real GameCube soundbank samples, id-keyed
      // se_<hex> cues, exported by scripts/export-combat-se.py from afs_data.afs
      // snd_com01/02/03). Optional: when absent, the se_* COMBAT_SFX entries simply
      // resolve to nothing and playSfx swallows them.
      try {
        const se = await loadAudioManifest("/audio/se/manifest.json");
        manifest.files = [...manifest.files, ...se.files];
      } catch {
        // combat-SE manifest not exported; fall through with the base manifest only
      }
      return createAudioManager({ manifest });
    })().catch(() => null);
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
  | "title"
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

/**
 * Title/desk-intro screen, per research/decomp/index/title-main-menu-flow.md: the real boot
 * path runs the frontend desk script (FUN_801c795c / G-Red desk-intro actor) before the
 * title/main-menu scene enter (title_main_menu_scene_enter -> set_global_menu_mode(9)). "Press
 * start" (click/any key) models that handoff into the existing menu hub.
 */
function showTitleIntro(): void {
  flow.screen = "title";
  queueBgm(AUDIO_CUES.menuBgm);
  mountScreen((root) =>
    createTitleIntro(root, {
      onEnter: () => {
        playConfirmSfx();
        showMenu();
      },
    }),
  );
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
  battleScene.sync(initialScene.actors, initialScene.projectiles, initialScene.focusUid);
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
  if (presentation) {
    const teammates = projectedTeammateMarkers(session.battle, presentation.focus);
    // Player tag ("1P"/"2P") from the local player's index in localPlayerIds — only surfaced
    // in multi-local sessions (future multi-viewport work); single-player HUD stays
    // capture-faithful with no tag. Conditional-spread keeps the keys absent (not undefined)
    // under exactOptionalPropertyTypes, matching battleHudState's optional-field style.
    const playerIndex = session.localPlayerIds.indexOf(session.localPlayerId);
    const playerLabel =
      session.localPlayerIds.length > 1 && playerIndex >= 0 ? `${playerIndex + 1}P` : undefined;
    const extras = {
      ...(teammates.length > 0 ? { teammates } : {}),
      ...(playerLabel !== undefined ? { playerLabel } : {}),
    };
    session.hud.update(
      teammates.length > 0 || playerLabel !== undefined ? { ...presentation.hud, ...extras } : presentation.hud,
    );
  }
}

const TEAMMATE_MARKER_LIMIT = 3;
const TEAMMATE_MARKER_Y_OFFSET = 125;
const TEAMMATE_MARKER_SCREEN_MARGIN = 0.04;
const _hudProject = new THREE.Vector3();

function projectedTeammateMarkers(battle: Battle, focus: BorgRuntime | null): TeammateMarker[] {
  if (!focus) return [];
  const markers: TeammateMarker[] = [];
  for (const b of battle.state.borgs) {
    if (!b.alive || b.uid === focus.uid || b.team !== focus.team) continue;
    const scenePos = battleScene.positionOf(b.uid);
    _hudProject
      .set(
        scenePos?.x ?? b.pos.x,
        (scenePos?.y ?? b.pos.y) + TEAMMATE_MARKER_Y_OFFSET,
        scenePos?.z ?? b.pos.z,
      )
      .project(camera);
    const x01 = (_hudProject.x + 1) * 0.5;
    const y01 = (1 - _hudProject.y) * 0.5;
    if (
      _hudProject.z < -1 ||
      _hudProject.z > 1 ||
      x01 < -TEAMMATE_MARKER_SCREEN_MARGIN ||
      x01 > 1 + TEAMMATE_MARKER_SCREEN_MARGIN ||
      y01 < -TEAMMATE_MARKER_SCREEN_MARGIN ||
      y01 > 1 + TEAMMATE_MARKER_SCREEN_MARGIN
    ) {
      continue;
    }
    markers.push({
      label: b.ownerPlayer === null ? "CPU" : "ALLY",
      hp01: Math.max(0, Math.min(1, b.hp / Math.max(1, b.maxHp))),
      x01: Math.max(0, Math.min(1, x01)),
      y01: Math.max(0, Math.min(1, y01)),
    });
    if (markers.length >= TEAMMATE_MARKER_LIMIT) break;
  }
  return markers;
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
    // The profile accessor lets the snapshot capture the local borg's charge tier thresholds
    // (chargeTier1Frames/chargeTier2Frames) for the charge_start/tier-up cues — read from the
    // combat package's action profiles, never hardcoded app-side.
    const audioBefore = snapshotBattleAudio(battle, session.localPlayerId, session.allyMax, (id) =>
      BORG_CATALOG.actionProfileFor(id),
    );
    battle.step(SIM_DT, inputs);
    const audioAfter = snapshotBattleAudio(battle, session.localPlayerId, session.allyMax, (id) =>
      BORG_CATALOG.actionProfileFor(id),
    );
    for (const cue of battleAudioEvents(audioBefore, audioAfter)) {
      playBattleEventSfx(cue);
    }
    // Per-borg voice cues (deploy shout / death cry), (az) — TUNED role binding.
    for (const voiceKey of battleVoiceCues(audioBefore, audioAfter)) {
      playBorgVoice(voiceKey);
    }
    simAccumulator -= SIM_DT;
    steps += 1;
    if (battle.state.result !== "ongoing") break;
  }

  // Compute the presentation once: it drives both the world scene (reticle color = melee mode)
  // and the HUD, keeping the "battle mode" signal single-sourced from battleHudState.
  const presentation = currentBattlePresentation();
  const sceneState = battleSceneState(battle, presentation?.focus ?? localFocusBorg());
  battleScene.sync(sceneState.actors, sceneState.projectiles, sceneState.focusUid, Boolean(presentation?.hud.meleeRange));
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
  const activeTargetUid = focus?.targetLockState?.activeTargetUid ?? focus?.lockTarget ?? null;
  const activeTargetScenePos = activeTargetUid ? battleScene.positionOf(activeTargetUid) : null;
  const activeTargetSim = activeTargetUid
    ? session.battle.state.borgs.find((b) => b.uid === activeTargetUid) ?? null
    : null;
  const lockTargetPos =
    activeTargetScenePos ??
    (activeTargetSim ? new THREE.Vector3(activeTargetSim.pos.x, activeTargetSim.pos.y, activeTargetSim.pos.z) : null);
  const primary =
    focus && target
      ? {
          pos: target,
          rotY: focus.rotY,
          lockTargetPos,
          lockCameraState: focus.targetLockState?.cameraState ?? 2,
        }
      : null;
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
      targetPointerUid: b.targetLockState?.activeTargetUid ?? null,
      targetListIndex:
        b.targetLockState?.mode === "ally" ? b.targetLockState.allyIndex : b.targetLockState?.enemyIndex ?? -1,
      lockMode: b.targetLockState?.mode ?? "enemy",
      sourceTargetState: b.targetLockState?.sourceState ?? 0,
      lockCameraState: b.targetLockState?.cameraState ?? 2,
      movementFrame: b.targetLockState?.activeTargetUid
        ? `${b.targetLockState.mode}:${b.targetLockState.activeTargetUid}`
        : "no-lock",
    })),
  });
}

function resolveBattle(): void {
  if (!session || session.resolved) return;
  session.resolved = true;
  // DERIVED results (results-scoring-decode-2026-07-04.md): outcome = the local player's
  // slot counters; computeResults applies the decoded ROM rows/grand-total formula.
  const outcome = battleOutcomeFromState(session.battle, session.localPlayerId);
  const results = computeResults(outcome);

  showResults(outcome.win ? "win" : "lose", {
    attack: results.attack,
    hitRatio: results.hitRatio * 100,
    dodgeRatio: results.dodgeRatio * 100,
    enemyBorgsDefeated: results.enemyBorgsDefeated,
    enemyTotalCost: results.costWon,
    playerBorgsDefeated: results.playerBorgsDefeated,
    playerTotalCost: results.costLost,
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
    showTitleIntro();
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
  // Debug: jump back to the title/desk-intro screen or straight to the menu hub, for preview
  // verification of the Slice 6 title-intro flow without a full reload.
  showTitle: () => showTitleIntro(),
  showMenu: () => showMenu(),
  renderDiagnostics: () => viewport.diagnostics(),
  // Read-only scene readout for preview debugging: current stage, lights, and a per-material
  // summary (color/map/side/transparent) of everything under the stage and battle roots.
  sceneInfo: () => {
    const summarize = (root: THREE.Object3D, label: string) => {
      const mats: Record<string, unknown>[] = [];
      root.traverse((o) => {
        const mesh = o as THREE.Mesh;
        if (!mesh.isMesh) return;
        const list = Array.isArray(mesh.material) ? mesh.material : [mesh.material];
        for (const m of list) {
          const std = m as THREE.MeshStandardMaterial;
          mats.push({
            label,
            mesh: mesh.name || "(unnamed)",
            type: m.type,
            color: std.color ? `#${std.color.getHexString()}` : null,
            map: !!std.map,
            metalness: std.metalness,
            roughness: std.roughness,
            transparent: m.transparent,
            opacity: m.opacity,
            visible: mesh.visible,
          });
        }
      });
      return mats;
    };
    return {
      stageId: loadedStageId,
      background: scene.background instanceof THREE.Color ? `#${scene.background.getHexString()}` : String(scene.background),
      fog: scene.fog ? { color: `#${(scene.fog as THREE.Fog).color.getHexString()}`, near: (scene.fog as THREE.Fog).near, far: (scene.fog as THREE.Fog).far } : null,
      lights: [stageLighting.ambient, ...stageLighting.directionals].map((l) => ({
        type: l.type,
        color: `#${l.color.getHexString()}`,
        intensity: l.intensity,
        visible: l.visible,
      })),
      toneMapping: viewport.renderer.toneMapping,
      stageMaterials: summarize(stageRoot, "stage"),
      battleMaterials: summarize(battleRoot, "battle"),
    };
  },
  // Raw three.js handles for interactive preview debugging only.
  three: { scene, stageRoot, battleRoot, camera, viewport },
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
