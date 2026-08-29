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
// render asset loader, and the baked-clip builder are REUSED.

import * as THREE from "three";
import { installRomDamageCore } from "./sim/romDamageBoot";
import { DEFAULT_PILOT_FRAMES, bootComposedModule, onGameFrame as onComposedGameFrame } from "./rom/composedBoot";

import { type StageAssets } from "@gf/assets";
import { startFixedStepLoop, startRenderLoop } from "@gf/core";
import {
  createThreeAssetLoader,
  createThreeViewport,
  prepareImportedModel,
} from "@gf/render";
import {
  cameraParamsForBorgId,
  emptyInput,
  type Battle,
  type BattleActorObservation,
  type PlayerInput,
  type RectStageBounds,
} from "@gf/combat";
import {
  collectManifestPlayKeys,
  createAudioManager,
  loadAudioManifest,
  resolveCueToAsset,
  type GotchaAudioManager,
} from "@gf/audio";
import {
  createChallengeRun,
  createGotchaBoxSettlement,
  computeResults,
  playerIdFor,
  type MissionBattleConfig,
  type GetDrop,
} from "@gf/missions";

import {
  ensureStyles,
  createMenuScreenHost,
  createTitleIntro,
  createMainMenu,
  createSelectDifficulty,
  createSelectPlayers,
  createLoadBoxData,
  createSelectForce,
  createForceBuilder,
  createBattleIntro,
  createResults,
  createGets,
  createPauseMenu,
  createBattleHud,
  createDebugOverlay,
  type ForceSlot,
  type BattleHudHandle,
  type DebugOverlayHandle,
  type TeammateMarker,
  type GetsRow,
  type PauseMenuHandle,
} from "./ui/index.js";

import {
  EXPORTED_STAGE_CATALOG_ADAPTER,
  inputFromKeys,
  DEFAULT_ARENA_STAGE,
  EXPORTED_STAGE_CATALOG,
  isExportedStageId,
} from "./sim/adapter.js";
import { initializeGotchaBoxBattle } from "./sim/gotchaBoxBattleInitialization.js";
import { initTouchControls, touchGamepad, watchViewport } from "./ui/touch/index.js";
import {
  createGameSession,
  type DeepReadonly,
  type GameSessionEffect,
  type GameSessionEvent,
} from "./gameSession.js";
import { BattleScene } from "./sim/battleScene.js";
import { BORG_CATALOG, DEFAULT_LEAD } from "./sim/borgCatalog.js";
import { proveAttackDamage, proveBoundsClamp, proveJumpArc } from "./sim/gameplayProof.js";
import { createBorgPresentationAssets } from "./sim/borgPresentationAssets.js";
import { createGameAssetCatalog } from "./assetCatalog.js";
import { publicUrl } from "./publicUrl.js";
import { BattleCamera, type CameraFollowTarget } from "./sim/camera.js";
import { createBrowserGotchaBoxPersistence } from "./sim/getStorage.js";
import { createInputEdgeLatch } from "./inputEdge.js";
import { SOURCE_FRAME_SECONDS, clamp01, framesToMilliseconds } from "./constants.js";
import {
  activeBorgForPlayer,
  battleEnergyMaxima,
  battleOutcomeFromState,
  battlePresentationState,
  battleSceneState,
  battleAudioEvents,
  battleVoiceCues,
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

// DERIVED: the stff prop controller emits 0x17a/0x17b and title opcode 0x15 invokes
// zz_00f036c_(0, 0x017c) at source frame 120. The exporter resolves all three literal
// ids through snd_com03.tsb/chd/dpk.
const TITLE_SOUND_IDS: Readonly<Record<number, string>> = {
  0x017a: "se_17a",
  0x017b: "se_17b",
  0x017c: "se_17c",
};
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
/** Rate limit for a cue with no COMBAT_SFX_MIN_GAP_MS entry of its own. TUNED. */
const DEFAULT_COMBAT_SFX_MIN_GAP_MS = 250;
const lastCombatSfxAt = new Map<string, number>();

/**
 * Play `assetKey` unless `rateKey` fired less than `minGapMs` ago, recording the play.
 * Shared by every combat/voice cue path so they cannot drift on how "too soon" is decided;
 * each caller owns which keyspace it rate-limits on (per-EVENT cue vs per-SAMPLE se_* key).
 */
function playRateLimited(
  lastPlayedAt: Map<string, number>,
  rateKey: string,
  minGapMs: number,
  assetKey: string,
): void {
  const now = performance.now();
  const elapsed = now - (lastPlayedAt.get(rateKey) ?? -Infinity);
  if (elapsed >= minGapMs) {
    lastPlayedAt.set(rateKey, now);
    playSfx(assetKey);
  }
}

function playCombatSfx(cue: CombatSfxCue): void {
  const key = COMBAT_SFX[cue];
  if (!DISABLE_COMBAT_SFX && key) {
    playRateLimited(lastCombatSfxAt, cue, COMBAT_SFX_MIN_GAP_MS[cue] ?? DEFAULT_COMBAT_SFX_MIN_GAP_MS, key);
  }
}

function playBattleEventSfx(cue: BattleEventCue): void {
  // Authored-audio suppression (DERIVED data, TUNED routing): when the LOCAL borg's current
  // swing/charged release/X-special carries ROM-authored PATH-B sound events
  // (BorgRuntime.meleeSounds, research/decomp/anim-sound-op-decode-2026-07-04.md), the
  // slot-enter path below (onSlotEnter -> AUTHORED_SWING_SLOTS) plays those exact samples —
  // skip the generic TUNED cue here so the same swing/release/special doesn't double-play (the
  // sim edge fires in the same tick as the slot edge).
  //
  // This checks the SAME set (AUTHORED_SWING_SLOTS, defined below) rather than re-listing cue
  // names here: battleAudioEvents currently only ever emits "melee"/"charge_release" (never the
  // literal "melee_alt"/"charge_shot" members of the shared AnimSlot/BattleEventCue union), so a
  // hardcoded 2-or-3-name check here looked complete but silently stopped covering
  // AUTHORED_SWING_SLOTS the moment "special" (X-special) was added to that set — exactly the
  // gap selfcheck-audio-wiring.mjs's parity check exists to catch. Sharing one Set makes the two
  // call sites impossible to drift apart again.
  const suppressed = AUTHORED_SWING_SLOTS.has(cue) && localActiveBorgHasAuthoredSwingAudio();
  if (!suppressed) playCombatSfx(cue);
}

function localActiveBorgHasAuthoredSwingAudio(): boolean {
  const active = session ? activeBorgForPlayer(session.battle, session.localPlayerId) : null;
  return (active?.meleeSounds?.length ?? 0) > 0;
}

// Authored PATH-B swing audio (research/decomp/anim-sound-op-decode-2026-07-04.md): each
// melee swing / charged release's action-script stream plays an anim whose descriptor binds
// a list of {frame, soundId} events (ROM actor+0x4e8 table). The sim resolves them per swing
// (BorgRuntime.meleeSounds, DERIVED end-to-end) and the slot-enter edge schedules each event
// at its anim-clock frame (60fps). TUNED residue, labeled honestly: the schedule hangs off
// the renderer's slot edge + wall clock (not the ROM part-anim clock), mode-1 events play the
// base id only (no anim-rate id±1 variant select), and positional modes play flat.
// "special" (X-special) added alongside melee/melee_alt/charge_shot: startSpecialAttack
// (packages/combat combat.ts) resolves the SAME xLeaf.sounds -> BorgRuntime.meleeSounds bridge
// for the X-move as the melee/charge paths use, so it was missing authored audio (falling
// through to the "special" slot-edge fallback below) until this fix — see the matching
// suppression-list fix in playBattleEventSfx above.
const AUTHORED_SWING_SLOTS: ReadonlySet<string> = new Set(["melee", "melee_alt", "charge_shot", "special"]);
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
  if (DISABLE_COMBAT_SFX) return; // guard clause: nothing below applies with SFX off
  for (const sound of sounds) {
    const delayMs = Math.min(framesToMilliseconds(sound.frame), AUTHORED_MAX_DELAY_MS);
    const key = seKeyForSoundId(sound.id);
    window.setTimeout(() => playRateLimited(lastCombatSfxAt, key, AUTHORED_SE_MIN_GAP_MS, key), delayMs);
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
  if (!DISABLE_COMBAT_SFX) playRateLimited(lastVoiceAt, key, VOICE_MIN_GAP_MS, key);
}

function forceFromSlot(slot: DeepReadonly<ForceSlot>): string[] {
  return BORG_CATALOG.forceFromSlot({ ...slot, borgIds: [...slot.borgIds] });
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
const chromeElement = document.getElementById("gf-chrome");
const canvas = document.getElementById("app") as HTMLCanvasElement;
if (!uiElement) throw new Error("Missing #ui");
// Persistent chrome layer (index.html). REQUIRED, not optional: #ui is the screen host's
// root and every mount calls replaceChildren() on it, so anything that must survive a
// screen change cannot live there. Falling back to #ui here would silently reintroduce the
// detached-overlay bug, so a missing layer is a build error, not a degraded default.
if (!chromeElement) throw new Error("Missing #gf-chrome");
const ui = uiElement;
const chromeLayer = chromeElement;
const screenHost = createMenuScreenHost(ui);
ui.style.pointerEvents = "auto"; // the UI component library uses real buttons.
const urlParams = new URLSearchParams(window.location.search);
const ENABLE_BATTLE_DEBUG_DATASET = urlParams.has("debugBattle");
const ENABLE_RENDER_DEBUG = urlParams.has("debugRender") || urlParams.has("capture");

/** Centered boot/asset-failure notice. Inline (not in styles.generated.css) because it has
 *  to render before ensureStyles' sheet can be guaranteed applied. */
const LOADING_MESSAGE_CSS =
  "position:absolute;left:50%;top:50%;transform:translate(-50%,-50%);" +
  "color:#bfeeff;font:600 16px 'Trebuchet MS',system-ui,sans-serif;" +
  "text-align:center;text-shadow:0 1px 3px #000;";

// ATK-015: minimal read-only debug overlay (sim state readout for the focused borg). Mounted
// once at startup, hidden by default; toggled with the backtick key or ?debugOverlay=1. See
// apps/game/src/ui/hud/DebugOverlay.ts and research/tasks/attack-port/ATK-015-debug-overlay-fields.md.
// Mounted into the CHROME layer, not #ui: the first screen mount replaces #ui's children, so
// an overlay parented there was detached before it could ever be toggled on.
const debugOverlay: DebugOverlayHandle = createDebugOverlay(chromeLayer);

/**
 * Persistent, unmissable notice pinned to the chrome layer.
 *
 * Used for facts a player/operator must not be able to miss — today: the damage core is not
 * the ROM's. Deliberately NOT the debug overlay, which is hidden by default: a downgrade
 * only visible behind a debug toggle is still a silent downgrade.
 */
function showChromeBanner(id: string, text: string, accent: string): void {
  const existing = chromeLayer.querySelector(`[data-gf-banner="${id}"]`);
  if (existing) existing.remove();
  const box = document.createElement("div");
  box.dataset["gfBanner"] = id;
  box.textContent = text;
  box.style.cssText =
    "position:absolute;left:50%;bottom:10px;transform:translateX(-50%);max-width:92vw;" +
    `padding:6px 12px;border-radius:4px;border:1px solid ${accent};background:rgba(0,0,0,0.82);` +
    `color:${accent};font:600 12px/1.4 'Consolas','Menlo',monospace;text-align:center;` +
    "pointer-events:none;z-index:70;";
  chromeLayer.appendChild(box);
}

// ROM-wasm damage core (the 1:1 port, live in the game): fetch + fidelity-gate
// against the TS reference + install into sourceDamage's override seam.
// Default ON; `?romwasm=0` forces the TS implementation; `?romwasm=threads`
// loads the threads-target relink (imported shared memory, step 8) — the
// exported-memory build stays the default until switching is separately
// reviewed. An unrecognised value is rejected rather than silently defaulted.
//
// The result is never swallowed: romDamageBoot publishes it to
// window.__romDamageStatus + <html data-gf-rom-damage>, and anything other than
// a live ROM core also raises a banner here and annotates the debug overlay, so
// a build serving the wrong core cannot look identical to a correct one.
const ROM_WASM_FIDELITY_CASES = 256;
void installRomDamageCore(urlParams.get("romwasm"), ROM_WASM_FIDELITY_CASES).then((status) => {
  if (status.state === "rom-live") {
    debugOverlay.setProvenance([`damage: ROM wasm (${status.variant})`]);
    return;
  }
  const forced = status.state === "ts-port-forced";
  debugOverlay.setProvenance([
    `damage: TS PORT — NOT the ROM core${forced ? " (?romwasm=0)" : ""}`,
    `reason: ${status.detail}`,
  ]);
  showChromeBanner(
    "rom-damage",
    forced
      ? "TS DAMAGE PORT (?romwasm=0) — the ROM damage core is not serving this session"
      : `ROM DAMAGE CORE NOT LIVE — running degraded on the TS port: ${status.detail}`,
    forced ? "#ffd479" : "#ff6b6b",
  );
});

// Composed-module dispatch pilot (docs/composed-pilot.md): boots the real
// assembly-gate rung-0 module in a rom-runtime worker and drives it from the
// render loop below, with every out-of-window call crossing the H2 bridge.
// OFF by default — it reserves 2GB of shared memory and parks a worker thread.
// `?composed=1` uses the default frame budget; `?composed=<n>` drives n frames.
//
// The pilot's adapters are SYNTHETIC stand-ins with no capture behind them and
// the module's units have no post-relink verification, so whenever it is up the
// app says so on screen — its numbers must never be read as gameplay evidence.
const composedFlag = urlParams.get("composed");
if (composedFlag !== null && composedFlag !== "0") {
  const requested = Number.parseInt(composedFlag, 10);
  void bootComposedModule(Number.isFinite(requested) && requested > 1 ? requested : DEFAULT_PILOT_FRAMES).then((r) => {
    if (!r.active) {
      console.warn(`[composed-rom] pilot not active (${r.detail})`);
      return;
    }
    showChromeBanner(
      "composed-pilot",
      "COMPOSED-MODULE PILOT ACTIVE — synthetic adapters, unverified units, NO behavioural claim",
      "#ffd479",
    );
  });
}

if (urlParams.has("debugOverlay")) debugOverlay.setVisible(true);

/** Where the camera sits before the first battle seeds the follow rig — an over-the-shoulder
 *  three-quarter view of the default arena, so the boot/menu frames are not staring at the
 *  origin. TUNED (framing only; the follow camera overwrites it on battle entry). */
const BOOT_CAMERA_POSITION: [number, number, number] = [950, 520, 1320];

const viewport = createThreeViewport(canvas, {
  debugCapture: ENABLE_RENDER_DEBUG,
  clearColor: DEFAULT_RENDER_STATE.fogColor,
  camera: {
    fov: DEFAULT_RENDER_STATE.fov,
    near: DEFAULT_RENDER_STATE.near,
    far: DEFAULT_RENDER_STATE.far,
    position: BOOT_CAMERA_POSITION,
  },
});
const { scene, camera, controls } = viewport;
const renderAssets = createThreeAssetLoader({
  enableFileCache: true,
});
scene.fog = new THREE.Fog(DEFAULT_RENDER_STATE.fogColor, DEFAULT_RENDER_STATE.fogNear, DEFAULT_RENDER_STATE.fogFar);

import {
  createStageLightingRig,
  resolveStageLighting,
  applyResolvedStageLighting,
  updateLightPosition,
  type StageRenderState as LightingStageRenderState,
} from "./stages/lighting";
import { applyStageReadabilityOverrides } from "./stages/readabilityOverrides";
// Real per-stage lighting rig (supports N directionals — stff carries 2); replaces the old
// single ambient+directional pair. Values/validation: research/game-design/STAGE-LIGHTING-PORT.md.
const stageLighting = createStageLightingRig(scene);

const stageRoot = new THREE.Group();
scene.add(stageRoot);

// Battle actors (sim-driven borg models) live under their own group.
const battleRoot = new THREE.Group();
scene.add(battleRoot);

const assetCatalog = createGameAssetCatalog();
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
// Billboard basis for the status-aura clock hands (ROM FUN_8013f790 camera-facing draw path).
battleScene.setCamera(camera);
const battleCamera = new BattleCamera({ camera, controlsTarget: controls.target });

// ------------------------------------------------------------------------------------------
// Stage loading (preserved)
// ------------------------------------------------------------------------------------------

function applyStageRenderState(stageId: string, rs: StageRenderState): void {
  // Delegates to the canonical module (validated 40/40 against on-disk render-state.json;
  // identical output for 39 stages, stff additionally gains its second directional). The
  // local StageRenderState type is a looser shape of the module's; same on-disk data.
  //
  // resolve -> readability override -> apply, rather than the single-call convenience wrapper,
  // so the 3 audit-flagged stages (see readabilityOverrides.ts) get their fog-far clamp BEFORE
  // it reaches the scene/rig. Authored render-state stays the only input for the other 37
  // stages: applyStageReadabilityOverrides is a referential no-op when a stage has no entry.
  const resolved = resolveStageLighting(rs as LightingStageRenderState);
  const withOverrides = applyStageReadabilityOverrides(stageId, resolved);
  applyResolvedStageLighting(scene, stageLighting, withOverrides);
  camera.fov = withOverrides.camera.fovDegrees;
  camera.near = withOverrides.camera.near;
  camera.far = withOverrides.camera.far;
  camera.updateProjectionMatrix();
}

/** TUNED threshold (HSD PEDesc alpha-compare state is undecoded) — see loadStage below. */
const STAGE_TRANSPARENT_ALPHA_TEST = 0.1;

let loadedStageId: string | null = null;
let loadedStageAssets: StageAssets<StageRenderState> | null = null;

async function loadStage(stageId: string): Promise<StageAssets<StageRenderState>> {
  if (!isExportedStageId(stageId)) throw new Error(`Stage is not exported: ${stageId}`);
  if (loadedStageId === stageId && loadedStageAssets) return loadedStageAssets;
  stageRoot.clear();
  const assets = await assetCatalog.loadStageAssets<StageRenderState>(stageId);
  applyStageRenderState(stageId, assets.renderState);
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
      transparentAlphaTest: STAGE_TRANSPARENT_ALPHA_TEST,
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
// Audio
// ------------------------------------------------------------------------------------------

let audioManagerPromise: Promise<GotchaAudioManager | null> | null = null;
let activeBgmKey: string | null = null;
let pendingBgmKey: string | null = null;
// Manifest play-keys for the ROM cue resolver (resolveCueToAsset). Built once
// from the merged audio manifest in initAudio; sfx+voice keys only. Replaces the
// hand-tuned TITLE_SOUND_IDS arithmetic at the title onSound boundary.
let sfxKeys: ReadonlySet<string> = new Set();

function initAudio(): Promise<GotchaAudioManager | null> {
  if (!audioManagerPromise) {
    audioManagerPromise = (async () => {
      // BOTH manifests are shipped assets under apps/game/public and are REQUIRED. A
      // failure here is a broken build, not a runtime condition to absorb: it silences
      // every cue in the game. It used to be swallowed whole — `.catch(() => null)` with
      // no log — so a deploy that lost /audio/manifest.json played in total silence and
      // looked exactly like a correct one. The game still continues without audio (audio
      // is not load-bearing for play), but it says so at console.error, which the
      // production smoke treats as fatal.
      const manifest = await loadAudioManifest(publicUrl("/audio/manifest.json"));
      // The DERIVED combat-SE manifest (real GameCube soundbank samples, id-keyed se_<hex>
      // cues, exported by scripts/export-combat-se.py from afs_data.afs snd_com01/02/03).
      // Also shipped, also required: without it every DERIVED combat cue resolves to
      // nothing and the battle loses its real hit/dash/shoot samples.
      const se = await loadAudioManifest(publicUrl("/audio/se/manifest.json"));
      manifest.files = [...manifest.files, ...se.files];
      // Build the resolver keyset once from the merged manifest. resolveCueToAsset
      // intersects the ROM guard (soundId < 0x180, bank/sample arithmetic from
      // zz_00efb3c_) with the exported se_* keys; TITLE_SOUND_IDS stays as the
      // last-resort fallback at the onSound call site so this never regresses.
      sfxKeys = collectManifestPlayKeys(manifest);
      return createAudioManager({ manifest });
    })().catch((error: unknown) => {
      console.error("[audio] manifest load FAILED — the session will run with NO audio:", error);
      return null;
    });
  }
  return audioManagerPromise;
}

function queueBgm(key: string): void {
  pendingBgmKey = key;
  void playPendingBgm();
}

async function playPendingBgm(): Promise<void> {
  const key = pendingBgmKey;
  if (key === activeBgmKey) {
    // Already playing (or nothing pending); clear the request either way.
    if (key) pendingBgmKey = null;
  } else if (key) {
    const audio = await initAudio();
    try {
      await audio?.playBgm(key);
      if (audio) {
        activeBgmKey = key;
        if (pendingBgmKey === key) pendingBgmKey = null;
      }
    } catch {
      // Browsers reject autoplay before the first user gesture. Keep pending and
      // retry from the next key/click/touch event.
    }
  }
}

function playSfx(key: string | null): void {
  if (key) {
    void initAudio().then((audio) => void audio?.playSfx(key).catch(() => undefined));
  }
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
  if (e.code === "Tab" && challengeSession.snapshot().screen === "battle") e.preventDefault();
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

/**
 * Resolve the pad driving `playerIndex`, preferring a real controller.
 *
 * The on-screen GameCube overlay reports itself as a standard-mapping pad (ui/touch), so
 * it drops straight into the same mapping without a second input path — but it is the LAST
 * resort, so plugging a controller into a tablet takes over immediately.
 */
function activeGamepad(playerIndex = 0, allowFallback = playerIndex === 0): Gamepad | null {
  const pads = navigator.getGamepads?.();
  const exact = pads?.[playerIndex];
  // Resolved lazily, in preference order: this player's own slot, then (for player 0) any
  // connected pad, then the overlay. touchGamepad() builds a snapshot object per call, so
  // it is only reached when no real controller answered.
  let pad = exact?.connected ? exact : null;
  if (!pad && allowFallback) pad = pads?.find((g) => g?.connected) ?? null;
  if (!pad && playerIndex === 0) pad = touchGamepad();
  return pad;
}

// ------------------------------------------------------------------------------------------
// Borg GET / Gotcha-Box drop pool (research/decomp/items-evidence-inventory-2026-07-05.md).
//
// PORT-ISM: persisted in localStorage (apps/game/src/sim/getStorage.ts); the pool/roll
// SEMANTICS are DERIVED (@gf/missions getSystem.ts). Wired into the CHALLENGE flow only —
// Adventure mode isn't wired into this app yet, and the ROM's own GET accrual is Adventure-
// only (Challenge instead logs kills for the score/kill-log side, doc §2a); applying it to
// Challenge here is a deliberate port decision so the drop pipeline is exercised at all.
//
// The settlement module brackets every Challenge battle and owns win/lose/abandon ordering.
// Its injected RNG stream outlives individual battles (the missions seeded-RNG convention).
/** "GGET" in ASCII, xored into the wall clock so each session draws a different GET stream
 *  (this is a session seed, never a save value). */
const GET_RNG_SEED_TAG = 0x47474554;
/** mulberry32 constants (the same PRNG sim/romDamageBoot.ts uses for its fidelity gate). */
const MULBERRY32_INCREMENT = 0x6d2b79f5;
const UINT32_SPAN = 4294967296;

let getRngState = (Date.now() ^ GET_RNG_SEED_TAG) >>> 0;
function getRng(): number {
  getRngState = (getRngState + MULBERRY32_INCREMENT) >>> 0;
  let t = getRngState;
  t = Math.imul(t ^ (t >>> 15), t | 1);
  t ^= t + Math.imul(t ^ (t >>> 7), t | 61);
  return ((t ^ (t >>> 14)) >>> 0) / UINT32_SPAN;
}
const gotchaBox = createGotchaBoxSettlement({
  persistence: createBrowserGotchaBoxPersistence(),
  rng: getRng,
  clock: Date.now,
});

/** Challenge only ever offers FIGHT ALONE / TEAM UP; the session clamps to the same bound. */
const MAX_LOCAL_PLAYERS = 2;

const challengeSession = createGameSession({
  initialForceSlots: BORG_CATALOG.defaultForceSlots,
  forceFromSlot,
  validForce: (borgIds) => BORG_CATALOG.rosterIndex.validIds(borgIds, { fallbackId: DEFAULT_LEAD }),
  createRun: createChallengeRun,
  borgs: BORG_CATALOG.roster as Parameters<typeof createChallengeRun>[0]["borgs"],
  stageCatalog: EXPORTED_STAGE_CATALOG_ADAPTER,
  borgStats: BORG_CATALOG.combatStats,
  loadStageAssets: loadStage,
});

function dispatchSession(event: GameSessionEvent): void {
  interpretSessionEffects(challengeSession.dispatch(event));
}

function interpretSessionEffects(effects: readonly GameSessionEffect[]): void {
  for (const effect of effects) {
    if (effect.type === "render") renderSessionScreen();
    else if (effect.type === "teardown-battle") teardownBattle();
    else enterBattleOrRecover();
  }
}

/** Battle entry is the one async effect; a failure tears the half-built battle back down
 *  and routes the session back to Select Force rather than stranding the loading screen. */
function enterBattleOrRecover(): void {
  void enterBattle().catch((error: unknown) => {
    console.error("[battle] failed to enter battle, returning to Select Force", error);
    teardownBattle();
    dispatchSession({ type: "battle-preparation-failed" });
  });
}

// Screen callbacks. Every menu action is "play its cue, then dispatch the event"; naming
// the three shapes keeps the screen builders below to the arguments that actually differ.
function confirmWith(event: GameSessionEvent): () => void {
  return () => {
    playConfirmSfx();
    dispatchSession(event);
  };
}

function editWith(event: GameSessionEvent): () => void {
  return () => {
    playEditSfx();
    dispatchSession(event);
  };
}

function goBack(): void {
  playBackSfx();
  dispatchSession({ type: "back" });
}

type SessionState = ReturnType<typeof challengeSession.snapshot>;

function mountTitle(): void {
  queueBgm(AUDIO_CUES.menuBgm);
  screenHost.mount((root) =>
    createTitleIntro(root, {
      onSound: (soundId) => playSfx(resolveCueToAsset(soundId, sfxKeys) ?? TITLE_SOUND_IDS[soundId] ?? null),
      onEnter: confirmWith({ type: "title-enter" }),
    }),
  );
}

function mountMainMenu(state: SessionState): void {
  queueBgm(AUDIO_CUES.menuBgm);
  screenHost.mount((root) =>
    createMainMenu(root, {
      initial: state.menuMode,
      onSelect: (mode) => {
        if (mode === "challenge") confirmWith({ type: "menu-select", mode })();
        else if (mode === "edit-force") editWith({ type: "menu-select", mode })();
      },
    }),
  );
}

function mountDifficulty(): void {
  screenHost.mount((root) =>
    createSelectDifficulty(root, {
      onSelect: (budget) => confirmWith({ type: "difficulty-select", budget })(),
      onBack: goBack,
    }),
  );
}

function mountPlayerCount(): void {
  screenHost.mount((root) =>
    createSelectPlayers(root, {
      maxPlayers: MAX_LOCAL_PLAYERS,
      onSelect: (playerCount) => confirmWith({ type: "players-select", playerCount })(),
      onBack: goBack,
    }),
  );
}

function mountLoadBoxData(): void {
  // The port has its roster loaded already, so SKIP and CONFIRM advance identically.
  const proceed = confirmWith({ type: "box-continue" });
  screenHost.mount((root) => createLoadBoxData(root, { onConfirm: proceed, onSkip: proceed, onBack: goBack }));
}

function mountSelectForce(state: SessionState): void {
  const slots = state.forceSlots.map((slot) => ({ ...slot, borgIds: [...slot.borgIds] }));
  screenHost.mount((root) =>
    createSelectForce(root, {
      catalog: FORCE_CATALOG,
      slots,
      selectedSlot: state.selectedForceSlot,
      limit: state.budget,
      onSlotsSynced: (synced) => dispatchSession({ type: "force-slots-synced", slots: synced }),
      onSelectSlot: (slotIndex) => confirmWith({ type: "force-slot-selected", slotIndex })(),
      onConfirm: (slot) => confirmWith({ type: "force-slot-confirm", slot })(),
      onEdit: (slot) => editWith({ type: "force-slot-edit", slot })(),
      onBack: goBack,
    }),
  );
}

function mountForceBuilder(state: SessionState): void {
  // createGameSession refuses to construct without at least one force slot, so a missing
  // slot here is a broken invariant, not a case to render around. Editing an EMPTY force
  // (the old `slot ? ... : []`) silently discards whatever the player had and looks like a
  // wiped save; failing names the real fault instead.
  const slot = state.forceSlots[state.selectedForceSlot] ?? state.forceSlots[0];
  if (!slot) throw new Error(`Force Builder has no slot to edit (selected ${state.selectedForceSlot})`);
  screenHost.mount((root) =>
    createForceBuilder(root, {
      catalog: FORCE_CATALOG,
      limit: state.budget,
      initialForce: forceFromSlot(slot),
      onConfirm: (borgIds) => confirmWith({ type: "force-editor-confirm", borgIds })(),
      onQuit: () => {
        playBackSfx();
        dispatchSession({ type: "force-editor-quit" });
      },
    }),
  );
}

function mountBriefing(state: SessionState): void {
  const config = state.pendingBattleConfig;
  if (!config) throw new Error("Briefing requires a pending battle");
  queueBgm(AUDIO_CUES.menuBgm);
  screenHost.mount((root) =>
    createBattleIntro(root, {
      config,
      catalog: FORCE_CATALOG,
      onConfirm: confirmWith({ type: "briefing-confirm" }),
      onBack: goBack,
    }),
  );
}

function mountResults(state: SessionState): void {
  const postBattle = state.postBattle;
  if (!postBattle) throw new Error("Results screen requires a settled battle");
  // The battle is over but its 3D scene stays on screen behind the panel; only the HUD and
  // any open pause overlay come down.
  session?.hud.destroy();
  closePauseMenu();
  const handle = createResults(ui, { onAdvance: () => dispatchSession({ type: "advance" }) });
  handle.render(postBattle.result, postBattle.stats);
  screenHost.set(handle);
}

function mountGets(state: SessionState): void {
  const handle = createGets(ui, { onAdvance: () => dispatchSession({ type: "advance" }) });
  handle.render(getsRowsForDrops(state.postBattle?.drops ?? []));
  screenHost.set(handle);
}

/** Mount the DOM for the session's current screen. "battle" mounts nothing: the battle IS
 *  the 3D scene plus the HUD that enterBattle already put up. */
function renderSessionScreen(): void {
  const state = challengeSession.snapshot();
  switch (state.screen) {
    case "loading":
      queueBgm(AUDIO_CUES.battleBgm);
      screenHost.clear();
      break;
    case "title": mountTitle(); break;
    case "menu": mountMainMenu(state); break;
    case "difficulty": mountDifficulty(); break;
    case "players": mountPlayerCount(); break;
    case "load-box": mountLoadBoxData(); break;
    case "select-force": mountSelectForce(state); break;
    case "force": mountForceBuilder(state); break;
    case "briefing": mountBriefing(state); break;
    case "results": mountResults(state); break;
    case "gets": mountGets(state); break;
    case "battle": break;
  }
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
  pauseHandle: PauseMenuHandle | null;
  resolved: boolean;
}

let session: BattleSession | null = null;
let simAccumulator = 0;
/** The sim runs at the source's fixed 60 Hz step. */
const SIM_DT = SOURCE_FRAME_SECONDS;
/** Longest wall-clock gap a single stepBattle call absorbs. A tab that was hidden for a
 *  minute fast-forwards this much, not the whole minute. */
const SIM_MAX_CATCHUP_SECONDS = 0.25;
/** Hard cap on sub-steps per stepBattle call, so a slow frame cannot spiral into an
 *  ever-growing catch-up loop. */
const SIM_MAX_SUBSTEPS = 15;
/** Longest render delta fed to the animation mixers, matching the sim's catch-up policy. */
const RENDER_MAX_DELTA_SECONDS = 0.05;

async function enterBattle(): Promise<void> {
  await initializeGotchaBoxBattle(
    () => challengeSession.prepareBattle(),
    gotchaBox,
    (boot) => {
      const { battle, config, localPlayerId, localPlayerIds, stageBounds } = boot;

      // Wire the ROM cue resolver into combat. Every ported family handler's ctx.onPlayCue
      // fire (STAR HERO buff 0xa5, beam-wing loops, magnet/omega/morph spawn stingers,
      // per-borg dash/voice cues, etc.) flows through bridge.ts → RomBattleRuntime.onRomCue
      // → Battle.onRomCue. We intersect the ROM's arithmetic soundId (bank=cue>>7,
      // sample=cue&0x7f, guard cue<0x180) with the exported se_* manifest keys via
      // resolveCueToAsset; missing exports honestly drop (matches the ROM's silent TSB
      // skip). This is the PRIMARY path for cues fired through the stream VM; the
      // COMBAT_SFX event-driven path below remains as fallback for cues that have NO
      // ROM cue id (melee swings, death/deploy reaction anims, charge tiers).
      battle.onRomCue = (cue) => playSfx(resolveCueToAsset(cue, sfxKeys));

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
      // The Intro confirm can still be physically held when the battle mounts.
      // Adopt that state so it cannot become a fresh Pause edge on the first
      // simulation tick; release + press is still detected normally.
      pauseInputEdge.consume(pauseControlPressed());
      simAccumulator = 0;
      battleScene.clear();
      // Prime the scene + HUD on frame 0.
      const initialScene = battleSceneState(battle, localFocusBorg());
      battleScene.sync(
        initialScene.actors,
        initialScene.projectiles,
        initialScene.focusUid,
        false,
        initialScene.projectileDespawns,
      );
      const focus = localFocusBorg();
      const focusPos = focus ? battleScene.positionOf(focus.uid) : null;
      battleCamera.snapTo(focus && focusPos ? cameraFollowTargetForBorg(focus, focusPos) : null);
      updateHud();
    },
  );
  dispatchSession({ type: "battle-started" });
}

function localActiveUid(): string | null {
  return currentBattlePresentation()?.activeUid ?? null;
}

function localFocusBorg(): BattleActorObservation | null {
  return currentBattlePresentation()?.focus ?? null;
}

function currentBattlePresentation(): ReturnType<typeof battlePresentationState> | null {
  return session
    ? battlePresentationState({
        battle: session.battle,
        localPlayerId: session.localPlayerId,
        allyMax: session.allyMax,
        enemyMax: session.enemyMax,
        defaultBorgId: DEFAULT_LEAD,
        actionProfileFor: (borgId) => BORG_CATALOG.actionProfileFor(borgId),
      })
    : null;
}

/**
 * Player tag ("1P"/"2P") for the HUD, or undefined in a single-local session.
 *
 * Only surfaced when more than one local player shares the session (future multi-viewport
 * work); the single-player HUD stays capture-faithful with no tag.
 */
function localPlayerLabel(live: BattleSession): string | undefined {
  const playerIndex = live.localPlayerIds.indexOf(live.localPlayerId);
  const multiLocal = live.localPlayerIds.length > 1 && playerIndex >= 0;
  return multiLocal ? `${playerIndex + 1}P` : undefined;
}

function updateHud(): void {
  const live = session;
  const presentation = currentBattlePresentation();
  if (live && presentation) {
    // Conditional spread keeps absent extras absent (not `undefined`) under
    // exactOptionalPropertyTypes, matching battleHudState's own optional-field style.
    const teammates = projectedTeammateMarkers(live.battle, presentation.focus);
    const playerLabel = localPlayerLabel(live);
    live.hud.update({
      ...presentation.hud,
      ...(teammates.length > 0 ? { teammates } : {}),
      ...(playerLabel !== undefined ? { playerLabel } : {}),
    });
  }
}

/** Most floating ally plates drawn at once, so a big CPU-ally squad cannot paper over the
 *  battle. TUNED (no ROM plate budget is decoded). */
const TEAMMATE_MARKER_LIMIT = 3;
/** Plate anchor above the ally's root — head height. TUNED, matching the captures. */
const TEAMMATE_MARKER_Y_OFFSET = 125;
/** Slack outside the viewport (fraction of the frame) before a plate is culled, so one
 *  half-off-screen ally does not pop its plate in and out along the edge. TUNED. */
const TEAMMATE_MARKER_SCREEN_MARGIN = 0.04;
const _hudProject = new THREE.Vector3();

/** Normalized screen position of an ally's plate anchor, or null when it projects behind
 *  the camera or too far outside the frame to be worth drawing. */
function projectTeammateAnchor(actor: BattleActorObservation): { x01: number; y01: number } | null {
  const scenePos = battleScene.positionOf(actor.uid);
  _hudProject
    .set(
      scenePos?.x ?? actor.pos.x,
      (scenePos?.y ?? actor.pos.y) + TEAMMATE_MARKER_Y_OFFSET,
      scenePos?.z ?? actor.pos.z,
    )
    .project(camera);
  const x01 = (_hudProject.x + 1) * 0.5;
  const y01 = (1 - _hudProject.y) * 0.5;
  const behindCamera = _hudProject.z < -1 || _hudProject.z > 1;
  const offFrame =
    x01 < -TEAMMATE_MARKER_SCREEN_MARGIN ||
    x01 > 1 + TEAMMATE_MARKER_SCREEN_MARGIN ||
    y01 < -TEAMMATE_MARKER_SCREEN_MARGIN ||
    y01 > 1 + TEAMMATE_MARKER_SCREEN_MARGIN;
  return behindCamera || offFrame ? null : { x01, y01 };
}

function projectedTeammateMarkers(
  battle: Battle,
  focus: BattleActorObservation | null,
): TeammateMarker[] {
  const markers: TeammateMarker[] = [];
  if (focus) {
    for (const actor of battle.observe().actors) {
      if (markers.length >= TEAMMATE_MARKER_LIMIT) break;
      const isTeammate = actor.alive && actor.uid !== focus.uid && actor.team === focus.team;
      const anchor = isTeammate ? projectTeammateAnchor(actor) : null;
      if (anchor) {
        markers.push({
          label: actor.ownerPlayer === null ? "CPU" : "ALLY",
          hp01: clamp01(actor.hp / Math.max(1, actor.maxHp)),
          x01: clamp01(anchor.x01),
          y01: clamp01(anchor.y01),
        });
      }
    }
  }
  return markers;
}

// Pause handling (Start/Esc).
//
// Only the PAUSE-OPEN edge is polled here. Once paused, PauseMenu is mounted and subscribes
// to the shared menuInput bus (menuInput.ts), which maps the same Escape/Enter/gamepad-Start
// press to a "back"/"start" action and resumes via its own onResume callback below — so a
// direct resumeBattle() call here as well would double-dispatch resume for one keypress (and,
// now that onResume/onQuit play menu SFX, would have double-played the confirm/back cue too).
const pauseInputEdge = createInputEdgeLatch();
/** Standard-mapping Start (the GameCube Start/Pause button; ui/touch publishes it here too). */
const PAD_START_BUTTON = 9;
function pauseControlPressed(): boolean {
  const pad = activeGamepad();
  return keys.has("Escape") || keys.has("Enter") || (pad?.buttons[PAD_START_BUTTON]?.pressed ?? false);
}

function pollPauseToggle(): void {
  const live = session;
  // Guard clause: with no battle (or one already resolved) the latch is deliberately NOT
  // polled, so a control held across the battle boundary cannot bank a rising edge.
  if (!live || live.resolved) return;
  if (pauseInputEdge.poll(pauseControlPressed()) && !live.paused) pauseBattle();
}

function pauseBattle(): void {
  const live = session;
  if (!live || live.paused) return; // guard clause: no battle to pause
  live.paused = true;
  live.pauseHandle = screenHost.mountOverlay((root) => createPauseMenu(root, {
    // PauseMenu treats "back"/"start" (Escape/Enter/gamepad-Start, routed through the bus) the
    // same as an explicit RESUME confirm — see PauseMenu.ts onMenuAction — so this one callback
    // covers every resume input path; playConfirmSfx here cannot double-fire against
    // pollPauseToggle above, which no longer calls resumeBattle directly.
    onResume: () => {
      playConfirmSfx();
      resumeBattle();
    },
    onQuit: () => {
      playBackSfx();
      closePauseMenu();
      if (session) session.paused = false;
      endBattleToMenu();
    },
  }));
}

function resumeBattle(): void {
  if (!session) return; // guard clause: nothing to resume
  closePauseMenu();
  session.paused = false;
  // Swallow the in-flight pause key edge: the menuInput bus resumed the game
  // SYNCHRONOUSLY inside the keydown event (well before this polled tick). The
  // physical key is still in `keys`, so without marking it consumed here the
  // next pollPauseToggle tick would see the held control as a new rising edge
  // and re-pause immediately. That traps
  // the player in the pause menu (Escape/Enter/gamepad-Start toggle the menu
  // off then right back on). Claiming the press was "previous-frame" makes the
  // next poll see no rising edge until the key is actually released.
  pauseInputEdge.consume(true);
}

function closePauseMenu(): void {
  const handle = session?.pauseHandle;
  if (handle) {
    screenHost.closeOverlay(handle);
    if (session?.pauseHandle === handle) session.pauseHandle = null;
  }
}

function endBattleToMenu(): void {
  // Abandon (pause -> quit): revert the GET pool to its pre-battle snapshot, matching the
  // ROM's lose/abandon revert (doc §2c) — an abandoned battle keeps none of its accrual.
  gotchaBox.revert();
  dispatchSession({ type: "battle-abandoned" });
}

function teardownBattle(): void {
  session?.hud.destroy();
  closePauseMenu();
  battleScene.clear();
  session = null;
}

// The sim advances on a wall-clock interval (NOT requestAnimationFrame) so a
// battle keeps progressing even when the tab is backgrounded (rAF is throttled
// to ~0 Hz while hidden). dt is clamped so returning from a long background gap
// fast-forwards a bounded number of frames instead of one giant spike.
/**
 * One PlayerInput per local player for this tick. Only player 0 reads the keyboard; every
 * local player gets their own pad slot, and a player with no deployed borg is fed empty
 * input so a dead slot cannot drive the sim.
 */
function collectLocalInputs(live: BattleSession): Record<string, PlayerInput> {
  const inputs: Record<string, PlayerInput> = {};
  const soloSession = live.localPlayerIds.length === 1;
  for (let playerIndex = 0; playerIndex < live.localPlayerIds.length; playerIndex += 1) {
    const playerId = live.localPlayerIds[playerIndex] ?? playerIdFor(playerIndex);
    const active = activeBorgForPlayer(live.battle, playerId);
    const keySource = playerIndex === 0 ? keys : NO_KEYS;
    const pad = activeGamepad(playerIndex, soloSession && playerIndex === 0);
    inputs[playerId] = active ? inputFromKeys(keySource, pad) : emptyInput();
  }
  return inputs;
}

/**
 * Advance the sim one fixed step and emit the audio edges it crossed.
 *
 * The profile accessor lets the snapshot capture the local borg's charge tier thresholds
 * (chargeTier1Frames/chargeTier2Frames) for the charge_start/tier-up cues — read from the
 * combat package's action profiles, never hardcoded app-side.
 */
function stepSimOnce(live: BattleSession, inputs: Record<string, PlayerInput>): void {
  const snapshot = (): ReturnType<typeof snapshotBattleAudio> =>
    snapshotBattleAudio(live.battle, live.localPlayerId, live.allyMax, (id) =>
      BORG_CATALOG.actionProfileFor(id),
    );
  const audioBefore = snapshot();
  live.battle.step(SIM_DT, inputs);
  const audioAfter = snapshot();
  for (const cue of battleAudioEvents(audioBefore, audioAfter)) {
    playBattleEventSfx(cue);
  }
  // Per-borg voice cues (deploy shout / death cry), (az) — TUNED role binding.
  for (const voiceKey of battleVoiceCues(audioBefore, audioAfter)) {
    playBorgVoice(voiceKey);
  }
}

/** Push this tick's sim state into the scene and HUD. The presentation is computed ONCE:
 *  it drives both the world scene (reticle color = melee mode) and the HUD, keeping the
 *  "battle mode" signal single-sourced from battleHudState. */
function syncBattlePresentation(live: BattleSession): void {
  const presentation = currentBattlePresentation();
  const sceneState = battleSceneState(live.battle, presentation?.focus ?? localFocusBorg());
  battleScene.sync(
    sceneState.actors,
    sceneState.projectiles,
    sceneState.focusUid,
    Boolean(presentation?.hud.meleeRange),
    sceneState.projectileDespawns,
  );
  updateHud();
}

function stepBattle(dt: number): void {
  const live = session;
  if (!live || live.paused || live.resolved) return; // guard clause: sim is not running

  simAccumulator += Math.min(dt, SIM_MAX_CATCHUP_SECONDS);
  // Input is sampled once per tick and replayed for every sub-step, so a catch-up burst
  // cannot read a different controller state mid-burst.
  const inputs = collectLocalInputs(live);

  let steps = 0;
  while (simAccumulator >= SIM_DT && steps < SIM_MAX_SUBSTEPS) {
    stepSimOnce(live, inputs);
    simAccumulator -= SIM_DT;
    steps += 1;
    if (live.battle.observe().result !== "ongoing") break;
  }

  syncBattlePresentation(live);
  if (live.battle.observe().result !== "ongoing") resolveBattle();
}

/** camera+0x2e6 default: state 2 = no-lock follow (sim/camera.ts header). */
const DEFAULT_LOCK_CAMERA_STATE = 2;

/**
 * World position of the focus borg's lock target for the camera's lock-follow states.
 *
 * Prefers the RENDER position (the scene node the player actually sees, already smoothed by
 * the actor sync) and falls back to the raw sim position for a target the scene has not
 * spawned a node for yet. Null when nothing is locked.
 */
function lockTargetWorldPos(live: BattleSession, targetUid: string | null): THREE.Vector3 | null {
  const scenePos = targetUid ? battleScene.positionOf(targetUid) : null;
  const simActor =
    !scenePos && targetUid
      ? live.battle.observe().actors.find((b) => b.uid === targetUid) ?? null
      : null;
  const simPos = simActor
    ? new THREE.Vector3(simActor.pos.x, simActor.pos.y, simActor.pos.z)
    : null;
  return scenePos ?? simPos;
}

// Battle-camera framing: see apps/game/src/sim/camera.ts header for the full DERIVED-vs-TUNED
// breakdown (ram-trace-analysis.md §3.1 height-offset/distance/smoothing evidence).
function followCamera(): void {
  const live = session;
  if (!live) return; // guard clause: no battle to frame

  const focus = localFocusBorg();
  const focusPos = focus ? battleScene.positionOf(focus.uid) : null;
  const targetUid = focus?.targetLockState?.activeTargetUid ?? focus?.lockTarget ?? null;
  const primary =
    focus && focusPos
      ? cameraFollowTargetForBorg(focus, focusPos, {
          lockTargetPos: lockTargetWorldPos(live, targetUid),
          lockTargetKey: targetUid,
          lockCameraState: focus.targetLockState?.cameraState ?? DEFAULT_LOCK_CAMERA_STATE,
        })
      : null;
  battleCamera.update(primary);

  // zz_000584c_ @0x8000584c: copy light source position (DAT_802c3470/74/78) into
  // light destination (DAT_803c10f4/8/10fc) each frame. The source is the first
  // directional light's position from the stage render state.
  const lightSource = live.paused ? null : stageLighting.directionals[0]?.position ?? null;
  if (lightSource) updateLightPosition(stageLighting, lightSource);
}

function cameraFollowTargetForBorg(
  borg: BattleActorObservation,
  pos: THREE.Vector3,
  lock?: Pick<CameraFollowTarget, "lockTargetPos" | "lockTargetKey" | "lockCameraState">,
): CameraFollowTarget {
  const cameraParams = cameraParamsForBorgId(borg.borgId);
  if (!cameraParams) {
    throw new Error(`Missing source camera params for ${borg.borgId}`);
  }
  return {
    pos,
    cameraParams,
    rotY: borg.rotY,
    lockTargetPos: lock?.lockTargetPos ?? null,
    lockTargetKey: lock?.lockTargetKey ?? null,
    lockCameraState: lock?.lockCameraState ?? DEFAULT_LOCK_CAMERA_STATE,
  };
}

/** One decimal place: enough to diff positions between runs without churning the dataset
 *  attribute (and the JSON blob it produces) on sub-unit float noise. */
const DEBUG_DATASET_DECIMALS = 10;

function roundedForDebug(value: number): number {
  return Math.round(value * DEBUG_DATASET_DECIMALS) / DEBUG_DATASET_DECIMALS;
}

function debugActorRow(b: BattleActorObservation): Record<string, unknown> {
  const lock = b.targetLockState;
  return {
    uid: b.uid,
    team: b.team,
    borgId: b.borgId,
    alive: b.alive,
    hp: b.hp,
    state: b.state,
    pos: [roundedForDebug(b.pos.x), roundedForDebug(b.pos.y), roundedForDebug(b.pos.z)],
    vel: [roundedForDebug(b.vel.x), roundedForDebug(b.vel.y), roundedForDebug(b.vel.z)],
    lockTarget: b.lockTarget,
    allyLockTarget: b.allyLockTarget,
    targetPointerUid: lock?.activeTargetUid ?? null,
    targetListIndex: lock?.mode === "ally" ? lock.allyIndex : lock?.enemyIndex ?? -1,
    lockMode: lock?.mode ?? "enemy",
    sourceTargetState: lock?.sourceState ?? 0,
    lockCameraState: lock?.cameraState ?? DEFAULT_LOCK_CAMERA_STATE,
    movementFrame: lock?.activeTargetUid ? `${lock.mode}:${lock.activeTargetUid}` : "no-lock",
  };
}

/** ?debugBattle: mirror the live sim/camera state onto #ui[data-gf-battle-debug] for the
 *  browser harness. Read-only over the battle. */
function updateBattleDebugDataset(): void {
  if (!ENABLE_BATTLE_DEBUG_DATASET) return; // guard clause: the dataset is opt-in

  const live = challengeSession.snapshot().screen === "battle" ? session : null;
  if (!live) {
    delete ui.dataset["gfBattleDebug"];
  } else {
    ui.dataset["gfBattleDebug"] = JSON.stringify({
      activeUid: localActiveUid(),
      focusUid: localFocusBorg()?.uid ?? null,
      camera: [
        roundedForDebug(camera.position.x),
        roundedForDebug(camera.position.y),
        roundedForDebug(camera.position.z),
      ],
      target: [
        roundedForDebug(controls.target.x),
        roundedForDebug(controls.target.y),
        roundedForDebug(controls.target.z),
      ],
      bounds: live.stageBounds,
      borgs: live.battle.observe().actors.map(debugActorRow),
    });
  }
}

/** computeResults reports ratios as 0..1; the Results screen renders percentages. */
const PERCENT_SCALE = 100;

function resolveBattle(): void {
  if (!session || session.resolved) return;
  session.resolved = true;
  // DERIVED results (results-scoring-decode-2026-07-04.md): outcome = the local player's
  // slot counters; computeResults applies the decoded ROM rows/grand-total formula.
  const outcome = battleOutcomeFromState(session.battle, session.localPlayerId);
  const results = computeResults(outcome);

  // GET pool (research/decomp/items-evidence-inventory-2026-07-05.md §2a/§2c): a WIN
  // registers every enemy kill into the pool (team 0 = player side, team 1 = enemy in every
  // Challenge battle — toCombatBattleConfig's team mapping) and rolls drops; a LOSE reverts
  // the pool to its pre-battle snapshot exactly like an abandon (§2c — the ROM makes no
  // distinction between a lose and an abandon for the revert).
  let drops: readonly GetDrop[];
  if (outcome.win) {
    drops = gotchaBox.win(session.battle.observe().defeats);
  } else {
    gotchaBox.revert();
    drops = [];
  }

  dispatchSession({
    type: "battle-resolved",
    battleResults: results,
    drops,
    stats: {
      attack: results.attack,
      hitRatio: results.hitRatio * PERCENT_SCALE,
      dodgeRatio: results.dodgeRatio * PERCENT_SCALE,
      enemyBorgsDefeated: results.enemyBorgsDefeated,
      enemyTotalCost: results.costWon,
      playerBorgsDefeated: results.playerBorgsDefeated,
      playerTotalCost: results.costLost,
      allyBorgsDefeated: results.allyBorgsDefeated,
      grandTotal: results.grandTotal,
    },
  });
}

function getsRowsForDrops(drops: readonly GetDrop[]): GetsRow[] {
  return drops.map((drop) => ({
    name: BORG_CATALOG.forceById.get(drop.borgId)?.name ?? drop.borgId,
    kind: drop.kind,
    partIndex: drop.partIndex,
    ...(drop.partsCount !== undefined ? { partsCount: drop.partsCount } : {}),
  }));
}

// ------------------------------------------------------------------------------------------
// Main loop
// ------------------------------------------------------------------------------------------

// Render loop (requestAnimationFrame): drives animation mixers, the follow
// camera, and the WebGL render. Sim stepping is handled by the interval below.
const renderClock = new THREE.Clock();
function tick(): void {
  const dt = Math.min(renderClock.getDelta(), RENDER_MAX_DELTA_SECONDS);
  const screen = challengeSession.snapshot().screen;
  if (screen === "battle" || screen === "results") {
    battleScene.update(dt);
    if (screen === "battle") followCamera();
  }
  updateBattleDebugDataset();
  if (debugOverlay.visible) {
    debugOverlay.update(screen === "battle" ? localFocusBorg() : null);
  }
  controls.update();
  viewport.render();
  // One composed-module pilot frame per rendered game frame (no-op unless the
  // pilot booted). Non-blocking: it starts at most one frame and returns.
  onComposedGameFrame();
}

// Sim loop (setInterval): fixed-cadence wall-clock stepping, runs even when the
// tab is hidden. ~60 Hz target.
startFixedStepLoop({
  step(dt) {
    if (challengeSession.snapshot().screen === "battle") {
      pollPauseToggle();
      stepBattle(dt);
    }
  },
});

window.addEventListener("resize", () => {
  viewport.resize();
});

// Rotation support. A bare "resize" listener is not enough on mobile: iOS fires it before
// the rotation settles, so the renderer would keep the pre-rotation size until something
// else resized it. watchViewport coalesces resize/orientationchange/visualViewport and
// re-measures once more after the viewport settles (see ui/touch/orientation.ts).
watchViewport(() => {
  viewport.resize();
});

// On-screen GameCube controls; shows itself on touch devices, respects a stored override.
initTouchControls();

// ------------------------------------------------------------------------------------------
// Boot
// ------------------------------------------------------------------------------------------

ensureStyles();
showLoadingMessage("Loading extracted stage + model assets…");
document.documentElement.dataset.gfRuntime = "booting";

void loadInitialAssets()
  .then(() => {
    dispatchSession({ type: "boot-ready" });
    document.documentElement.dataset.gfRuntime = "boot-ready";
  })
  .catch((error: unknown) => {
    document.documentElement.dataset.gfRuntime = "boot-failed";
    showLoadingMessage(`Asset load failed: ${error instanceof Error ? error.message : String(error)}`);
  });

startRenderLoop({ frame: tick });

function showLoadingMessage(text: string): void {
  screenHost.clear();
  const box = document.createElement("div");
  box.style.cssText = LOADING_MESSAGE_CSS;
  box.textContent = text;
  ui.appendChild(box);
}

// Expose a tiny debug handle for live verification in the preview.
(window as unknown as { __gf: unknown }).__gf = {
  get navigation() {
    return challengeSession.snapshot();
  },
  keys,
  get input() {
    return inputFromKeys(keys, activeGamepad());
  },
  get session() {
    return session;
  },
  // Deterministic gameplay proofs for the browser smoke — throwaway sim battles from
  // the shipped bundle (see sim/gameplayProof.ts). Never touches the live session.
  selfcheck: {
    attackDamage: proveAttackDamage,
    boundsClamp: proveBoundsClamp,
    jumpArc: proveJumpArc,
  },
  stages: EXPORTED_STAGE_CATALOG,
  loadStage: async (stageId: string) => {
    const normalized = stageId.trim().toLowerCase();
    if (!isExportedStageId(normalized)) throw new Error(`Stage is not exported: ${stageId}`);
    await loadStage(normalized);
    viewport.render();
    return normalized;
  },
  renderDiagnostics: () => viewport.diagnostics(),
  // Per-actor mixer state (battleScene.animationDebug): lets the browser smoke assert
  // visible borgs are actually PLAYING a clip (runningClips > 0), not stuck in bind pose.
  animationDebug: () => battleScene.animationDebug(),
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
};
