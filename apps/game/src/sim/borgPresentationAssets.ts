import * as THREE from "three";

import type { ModelManifestEntry } from "@gf/assets";
import { prepareImportedModel, type ThreeAssetLoader } from "@gf/render";

import type { AnimSlot, BorgAssets } from "./battleScene.js";

export interface BorgPresentationAssets extends BorgAssets {
  setModelManifest(manifest: readonly ModelManifestEntry[]): void;
  /**
   * Resolve a baked clip DIRECTLY by its exported mot.bin (group, slot) — bypassing the
   * SLOT_LABELS/PREFERRED_LABELS heuristic tables entirely. Used when the sim has an EXACT
   * per-combo-step action-script anim target (combat.ts's BorgRuntime.meleeAnimStream, from
   * @gf/combat's actionStreamData.ts ComboStep.animStreamRef): the action-script stream's
   * OWN playAnim op already names the (group, slot) to play, so no label matching is needed
   * or wanted. Null when the borg's anim_index.json doesn't export that exact bank (not every
   * borg's baker captured every mot.bin slot — see actionStreamData.ts's header) — callers
   * fall back to the slot-heuristic loadClip.
   */
  loadClipByStreamRef(borgId: string, ref: { group: number; slot: number }): Promise<THREE.AnimationClip | null>;
}

export interface BorgPresentationAssetsOptions {
  assetLoader: ThreeAssetLoader;
  defaultLeadId: string;
}

export function createBorgPresentationAssets(options: BorgPresentationAssetsOptions): BorgPresentationAssets {
  const { assetLoader, defaultLeadId } = options;
let modelManifest: readonly ModelManifestEntry[] = [];
  const libraryIds = new Set<string>();

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
        // Root-motion strip: zero bone-0 XZ for ALL clips so authored root translation never
        // fights the sim (the sim owns world position). NOTE for the attack_lunge_s* banks
        // specifically (rootZ spans ~100-389 units — see the PREFERRED_LABELS comments
        // below): that stripped root motion IS the melee lunge, and the sim now drives the
        // equivalent translation itself (packages/combat/src/combat.ts melee lunge drive,
        // MELEE.LUNGE_* in constants.ts). If a future exporter/playback change re-enables
        // root XZ here, the sim lunge must be disabled first or the dash double-translates.
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
  if (id === defaultLeadId) return "/models/pl0615/model_00.glb";
  if (!libraryIds.has(id)) throw new Error(`No production model is registered for ${id}`);
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
    sourceP = assetLoader.loadGlbScene(url).then((model) => {
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
  return assetLoader.cloneModel(source);
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
  // Melee prefers the attack_lunge_s* banks. Their bone-0 root motion (the actual dash,
  // rootZ ~100-389 units in the per-borg notes below) is stripped in buildClip above; the
  // sim's melee lunge drive (packages/combat/src/combat.ts + MELEE.LUNGE_* constants)
  // supplies that translation instead. Playback-duration note: many lunge banks run ~37f
  // while per-borg meleeDef.duration can be shorter (e.g. pl0615: 17f), so the clip is cut
  // by the next state's crossfade before its last frames — a timeScale sync
  // (bankFrames / meleeDef.duration) would live in battleScene's melee playback, not here.
  melee: [/^attack_lunge_s\d+$/, /^attack_s\d+$/],
  // Resolved via SLOT_VARIANTS (second distinct melee-pattern bank) so borgs with
  // multiple exported swings alternate; falls back to melee when only one exists.
  melee_alt: [],
  shoot: [/^attack_s\d+$/, /^special_s\d+$/],
  // Charge-release fire animation. No generic pattern: the exact clip is per-borg action-
  // script data (the charge stream's playAnim target — e.g. G RED bank 0x80366220 stream
  // g3 s27 plays anim g3 s18); borgs without a PREFERRED_LABELS entry fall back to shoot.
  charge_shot: [],
  special: [/^special_s\d+$/],
  // DERIVED_ROM: state dispatch `zz_004beb8_` plays hit-react through group0 slot 13/14
  // (see research/decomp/data/state-anim-dispatch-802d3570.json). The bake labels g0s14 as
  // pose_short; older g3 hit_react/guard banks stay as fallbacks for borgs where exported DAT
  // remaps make them the only non-placeholder reaction.
  hit: [/^pose_short$/, /^hit_react_s\d+$/, /^guard_s\d+$/],
  // DERIVED_ROM: knockdown/down handler plays group0 slot 15. The exporter labels that slot
  // move_s15; down_s0 remains a fallback for the old high-confidence g4s0 convention when it
  // is the only non-placeholder exported down pose.
  down: [/^move_s15$/, /^down_s0$/, /^hit_react_s\d+$/, /^guard_s\d+$/, /^death$/],
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
  charge_shot: ["shoot", "attack", "special", "idle"],
  special: ["attack", "idle"],
  hit: ["idle"],
  down: ["hit", "death", "idle"],
  death: ["idle"],
  spawn: ["idle"],
  victory: ["idle"],
};

const PREFERRED_LABELS: Partial<Record<string, Partial<Record<AnimSlot, string[]>>>> = {
  // NEO G RED / G BLACK share G RED's family action-script bank (ctor 0x8018ccfc), so the
  // same charge-fire stream (g3 s27 → anim g3 s18) applies — see the pl0615 entry's note.
  pl0629: { charge_shot: ["hit_react_s18"] },
  pl062a: { charge_shot: ["hit_react_s18"] },
  pl0615: {
    // G RED (borgs.json name "G RED", id pl0615 — the game's box-art mascot borg,
    // NOT pl0000 "NORMAL NINJA"). This is the defaultLeadId / most fully-animated borg.
    shoot: ["attack_s4"],
    // DERIVED (meleeAnimKinds.json bank 0x80366220 stream g3 s27): the charge-fire script
    // arms the beam HIT kind 8 (bone-7 chest sweep records f7..16) and plays anim group 3
    // slot 18 — exported as the mislabeled "hit_react_s18" clip. This is the G Buster
    // chest-beam hop animation.
    charge_shot: ["hit_react_s18"],
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
    //
    // Command-table cross-check (validation only, 2026-07-03): pl0615 has an EXACT decoded
    // command table (ctor_8018ccfc, root 0x80365ea8, chunk_0046.c:4804-4807 — packages/combat
    // data/commandMoveTables.json). Its X-path records (commandType 2) are all actionIndex=2
    // with variantIndex {0,2,3,1,4} keyed by subtype 0-4. A NAIVE actionIndex/variantIndex ->
    // exported-anim_index reading (variantIndex -> g4 slot) would put the default subtype-0
    // X record on g4s0 — the knockdown pose, i.e. exactly the g4s0-as-special bug
    // (behavior-notes.md s4r) this override fixed. The record is therefore NOT consistent
    // with the known-good special_s1 under the naive mapping: either the runtime subtype is
    // nonzero here, or actionIndex/variantIndex address a different anim space than the
    // exported group/slot bake. The record->anim mapping stays UNPROVEN and these records
    // are FUTURE EVIDENCE only (needs a live trace of zz_006a104_ consuming a record against
    // the animation actually played) — do not rewrite special overrides from them.
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
  //
  // Command-table notes (validation only — the record->anim mapping is UNPROVEN, see the
  // pl0615 cross-check above): pl0008 and pl000c are among the 25 exact-table borgs in
  // packages/combat data/commandMoveTables.json; pl0105/pl0109 have no exact table.
  pl0008: {
    melee: ["attack_lunge_s1"],
    hit: ["hit_react_s0"],
    // Exact table ctor_8019e9a4 (chunk_0049.c:1169-1172) marks the X path (commandType 2)
    // DISABLED (mode -1; only B types 0/1 carry records), so the table offers NO X-anim
    // evidence for this borg — special_s1 stays a TUNED pick.
    special: ["special_s1"],
    down: ["down_s0"],
    death: ["death", "win_or_death"],
    victory: ["victory"],
  },
  pl000c: {
    melee: ["attack_lunge_s1"],
    hit: ["hit_react_s0"],
    // Exact table ctor_8019e9a4_alt_000c (chunk_0049.c:1178-1181): X records (commandType 2)
    // are actionIndex=2, variantIndex 0-4 by subtype — the same shape as the pl0615 anchor
    // whose naive variantIndex->g4-slot reading is contradicted by its known-good override,
    // so this stays FUTURE EVIDENCE only; special_s1 remains the TUNED pick.
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
  pl0625: {
    // VICTORY MACHINE is the same alt-mode group-2 bank family as pl061f (frames/slots match
    // one-for-one in anim_index.json); only g0s0 is labeled, so use the family Rosetta here too.
    move: ["g2_s1"],
    dash_fwd: ["g2_s4"],
    dash_back: ["g2_s5"],
    dash_left: ["g2_s7"],
    dash_right: ["g2_s7"],
    jump: ["g2_s16"],
    fly: ["g2_s16"],
    shoot: ["g2_s30"],
    melee: ["g2_s31"],
    hit: ["g2_s32"],
    death: ["g2_s15"],
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
  pl0408: { dash_right: ["dash_left"] },
  pl0409: { dash_right: ["dash_left"] },
  pl040a: { dash_right: ["dash_left"] },
  pl040b: { dash_right: ["dash_left"] },
  pl040c: { dash_right: ["dash_left"] },
  pl040d: { dash_right: ["dash_left"] },
  pl0602: { dash_right: ["dash_left"] },
  pl060a: { dash_right: ["dash_left"] },
  pl060c: { dash_right: ["dash_left"] },
  pl060e: { dash_right: ["dash_left"] },
  // ---- pl0c00-pl0c06 fortress family: attacks/flinches live in unlabeled group 7 -------
  // No group-1 attacks or group-3 reacts are exported; g7 carries 37f attack-length and
  // 13f flinch-length banks (verified in each borg's anim_index.json — same Rosetta as
  // the pl0619 comment above). melee/hit previously fell back to idle.
  pl0c00: { dash_left: ["dash_right"], melee: ["g7_s0"], hit: ["g7_s5"] },
  pl0c01: { dash_left: ["dash_right"], melee: ["g7_s0"], hit: ["g7_s5"] },
  pl0c02: { dash_left: ["dash_right"], melee: ["g7_s0"], hit: ["g7_s5"] },
  pl0c06: { dash_left: ["dash_right"], melee: ["g7_s0"], hit: ["g7_s5"] },
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
    // DERIVED_ROM hit state = g0s14. Ultimate Cannon exports that as an 11f pose_short.
    hit: ["pose_short"],
  },
  // ---- Borgs whose only group-4 bank is the knockdown pose (down_s0) -------------------
  // After the g4s0 relabel (behavior-notes.md s4r) these have no special_s* left, so
  // "special" fell back through attack to attack_s0 — a 2-frame placeholder on several.
  // Use the longest exported lunge/attack bank instead (TUNED pick, banks verified in
  // each borg's anim_index.json).
  // pl0301: exact command table ctor_80106e3c (chunk_0029.c:1927-1930, packages/combat
  // data/commandMoveTables.json) marks the X path (commandType 2) DISABLED — only types
  // 0/1/3 (B shot / B attack / B charge) carry records — so it offers no X-anim evidence;
  // the pick below stays TUNED (record->anim mapping UNPROVEN, see pl0615 cross-check).
  pl0301: { special: ["attack_lunge_s10"] }, // 54f
  pl0800: { special: ["attack_lunge_s18"] }, // 50f
  pl0805: { special: ["attack_lunge_s2"] }, // 71f
  // pl0807: exact command table ctor_801a04f0 (chunk_0049.c:2356-2359) has records ONLY on
  // type 1 (B attack); the X path is DISABLED — no X-anim evidence, pick stays TUNED.
  pl0807: { special: ["attack_lunge_s13"] }, // 51f
  // Cyber Hero exports ROM-cited g0s14 as a 2f pose_short; use it instead of the old
  // jump_land visual stand-in.
  pl0808: { hit: ["pose_short"], special: ["attack_lunge_s12"] }, // special 50f
  pl080d: { special: ["attack_lunge_s2"] }, // 71f
  pl080e: { special: ["attack_lunge_s2"] }, // 71f
  pl0a00: { special: ["attack_s7"] }, // 71f
  pl0a01: { special: ["attack_s7"] }, // 51f
  pl0a02: { special: ["attack_s7"] }, // 56f
  pl0a05: { special: ["attack_s7"] }, // 71f
  pl0a07: { special: ["attack_s7"] }, // 56f
  pl0a0a: { special: ["attack_s7"] }, // 71f
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

async function loadBorgClipByStreamRef(
  id: string,
  ref: { group: number; slot: number },
): Promise<THREE.AnimationClip | null> {
  const key = `${id}:g${ref.group}s${ref.slot}`;
  let p = clipCache.get(key);
  if (!p) {
    p = loadAnimIndex(id)
      .then((index) => {
        const bank = index?.banks.find((b) => b.group === ref.group && b.slot === ref.slot) ?? null;
        return bank ? fetch(`/models/${id}/${bank.file}`) : null;
      })
      .then((r) => (r?.ok ? (r.json() as Promise<BakedClip>) : null))
      .then((json) => (json ? buildClip(json) : null))
      .catch(() => null);
    clipCache.set(key, p);
  }
  return p;
}

  return {
    loadModel: loadBorgModel,
    loadClip: loadBorgClip,
    loadClipByStreamRef: loadBorgClipByStreamRef,
    setModelManifest(manifest: readonly ModelManifestEntry[]): void {
      modelManifest = [...manifest];
      libraryIds.clear();
      for (const entry of manifest) libraryIds.add(entry.id);
      libraryIds.add(defaultLeadId);
    },
  };
}
