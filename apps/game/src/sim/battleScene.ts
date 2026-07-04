// BattleScene — syncs render-facing battle actor facts to three.js models.
//
// One three.js Group per live actor (keyed by uid). Each frame:
//   - spawn a model for any new uid, despawn models whose uid is gone,
//   - copy pos -> position, rotY -> rotation.y,
//   - pick a baked clip from the borg's state/action and play it,
//   - advance per-borg AnimationMixers.
//
// Models + baked clips are provided by main.ts via the BorgAssets interface so we
// reuse the shared GLB loader, model normalization, and clip cache instead of
// duplicating them. A capsule is shown only while the production model is loading.

import * as THREE from "three";
import type { Projectile, ProjectileVisualKind } from "@gf/combat";
import { MUZZLE_OFFSET, SHOT, SPECIAL } from "@gf/combat";
import {
  ARROW_MDL_BOUNDS,
  ARROW_MDL_INDICES,
  ARROW_MDL_POSITIONS,
  ARROW_MDL_SOURCE,
} from "./data/arrowMdlGeometry.generated.js";
import efctBankJson from "./data/efctBankMeshes.json" with { type: "json" };
import type { BattleActorView } from "./battleView.js";

/** Asset hooks supplied by main.ts so we reuse its loaders/caches. */
export interface BorgAssets {
  /** Resolve a cloneable source model for a borg id (cached upstream). */
  loadModel(borgId: string): Promise<THREE.Object3D>;
  /** Resolve a baked AnimationClip for (borgId, slot). Null if unavailable. */
  loadClip(borgId: string, slot: AnimSlot): Promise<THREE.AnimationClip | null>;
  /**
   * Optional: resolve a baked clip DIRECTLY by its exported mot.bin (group, slot), bypassing
   * the slot-label heuristic. Used for per-combo-step melee anim (BattleActorView.meleeAnimStream,
   * DERIVED from @gf/combat's actionStreamData.ts ComboStep.animStreamRef — see
   * borgPresentationAssets.ts's loadClipByStreamRef doc). Absent, or null result, falls back to
   * the plain melee/melee_alt loadClip slot.
   */
  loadClipByStreamRef?(borgId: string, ref: { group: number; slot: number }): Promise<THREE.AnimationClip | null>;
  /**
   * Optional: called exactly once per animation-slot transition (edge-triggered, same
   * pattern as the existing hit-spark VFX trigger below — NOT fired every frame and NOT
   * fired on state re-entry while already in that slot). main.ts uses this to trigger
   * combat SFX. Slot->sound mapping is TUNED presentation EXCEPT where `meleeSounds` is
   * provided: the borg's CURRENT swing/release carries its ROM-authored PATH-B per-anim
   * sound events (BattleActorView.meleeSounds, DERIVED from the actor+0x4e8 sound-event
   * table — research/decomp/anim-sound-op-decode-2026-07-04.md; this CORRECTS the older
   * behavior-notes.md (v) "no per-action audio table recoverable" finding). meleeSounds is
   * only meaningful for the melee/melee_alt/charge_shot slots and is null for borgs whose
   * swing has no authored sounds — callers keep the TUNED fallback then.
   */
  onSlotEnter?(borgId: string, slot: AnimSlot, uid: string, meleeSounds?: BattleActorView["meleeSounds"]): void;
}

export type AnimSlot =
  | "idle"
  | "move"
  | "dash"
  | "dash_fwd"
  | "dash_back"
  | "dash_left"
  | "dash_right"
  | "jump"
  | "fall"
  | "fly"
  | "attack"
  | "melee"
  | "melee_alt"
  | "shoot"
  | "charge_shot"
  | "special"
  | "hit"
  | "down"
  | "death"
  | "spawn"
  | "victory";

interface Actor {
  group: THREE.Group;
  borgId: string;
  mixer: THREE.AnimationMixer | null;
  /** Cached actions per slot for this actor. */
  actions: Partial<Record<AnimSlot, THREE.AnimationAction>>;
  /** Cached actions keyed by "g{group}s{slot}" for per-combo-step melee anim (loadClipByStreamRef).
   *  Kept separate from `actions` because the slot axis ("melee"/"melee_alt") doesn't change
   *  across combo steps but the underlying clip does — see lastMeleeClipKey below. */
  streamActions: Partial<Record<string, THREE.AnimationAction>>;
  current: AnimSlot | null;
  lastSeenSlot: AnimSlot | null;
  /**
   * Alternates the melee slot between "melee" and "melee_alt" on each new melee entry so
   * borgs with several exported swing banks don't repeat the same swing every attack.
   * (melee_alt resolves to the borg's second melee-pattern bank in main.ts and falls back
   * to the plain melee bank when only one exists, so this is visual-only and fallback-safe.)
   */
  meleeParity: boolean;
  /**
   * Cache key of the last melee clip actually loaded/played — either the plain slot
   * ("melee"/"melee_alt") or "melee@g{group}s{slot}" when a per-combo-step stream ref drove
   * it. Combo steps keep `current` at "melee"/"melee_alt" across the whole chain (the slot
   * axis doesn't change), so this is the signal that a NEW clip must be loaded even though
   * `current === slot` would otherwise short-circuit playSlot.
   */
  lastMeleeClipKey: string | null;
  /** True once the (async) model has been attached. */
  ready: boolean;
  isPlaceholder: boolean;
  /** Charge-shot aura sprite (ptcl00.txg#7), lazily created while chargeFrames > 0. */
  chargeGlow: { sprite: THREE.Sprite; material: THREE.SpriteMaterial } | null;
  /** Slow/haste status auras (ROM zz_013f300_), keyed by kind; live while the timer runs. */
  statusFx: { slow: StatusAura | null; haste: StatusAura | null };
}

/**
 * One live slow/haste status aura — the ROM's zz_013f300_(target, 0|1) effect object
 * (chunk_0037.c:421; decode: research/decomp/efct-consumers-decode-2026-07-04.md).
 *
 * DERIVED structure: FOUR bank-mesh parts, texIds [48, 48, 49, 50] (s16 table
 * DAT_80434670 indexed by clamped slot [0,0,1,2]):
 *  - slot 0 x2 (texId 48, a flat 113-radius star ring): world-oriented, tumbling — random
 *    initial z/x phases (rand<<8), speeds x = +/-1024*t, z = +/-1024*(1-t) s16-angle units
 *    per frame with t = (rand&0x3f)/63 and random signs (FUN_8013f84c);
 *  - slot 1 (texId 49, a 108-long clock hand): CAMERA-FACING (draw path FUN_8013f790 builds
 *    a billboard basis), spinning in the view plane at -2184 units/f (~-12deg/f, a full turn
 *    every 30f);
 *  - slot 2 (texId 50, the short 75-long hand): billboard, -182 units/f (~-1deg/f).
 * SLOW halves every spin speed (FUN_8013f84c +0x34/+0x36 /2). Together they read as an
 * animated clock: fast hand + slow hand + orbiting sparkles.
 *
 * Color: the parts' matAnim frame is re-set EVERY tick to the pulse
 * s = clamp(sin(phase)*0.5+0.5, 0, 1) with phase += 0x222/f (slow) or 0x444/f (haste)
 * (FUN_8013f548/zz_013fa70_ -> zz_00086b8_), PLUS 2 when slow — and the extracted tracks
 * confirm the ranges: frames 0..1 pulse white<->ORANGE (haste), frames 2..3 white<->BLUE
 * (slow). Lifetime: while the sim's 900f status timer runs (FUN_8013f548 kills the object
 * when target +0x710/+0x712 hits 0).
 *
 * TUNED: the overall scale (the ROM multiplies actor scale by the undecoded per-borg float
 * +0x7fc; the port uses 1.0), the anchor height (ROM uses the actor matrix translation),
 * and the 24f-period tick SFX (zz_00f036c_ id 0x19) is not played.
 */
interface StatusAuraPart {
  node: THREE.Group;
  materials: THREE.MeshBasicMaterial[];
  layers: BankFxLayer[];
  /** True for the clock hands (texIds 49/50) — camera-facing draw path. */
  billboard: boolean;
  /** Spin phases/speeds in s16-angle units (0x10000 = full turn), advanced per 60fps frame.
   *  World parts use phaseX/phaseZ (rot z then x, FUN_8013f698); billboards spin in the
   *  view plane by phaseZ only. */
  phaseX: number;
  phaseZ: number;
  spinX: number;
  spinZ: number;
}
interface StatusAura {
  group: THREE.Group;
  parts: StatusAuraPart[];
  kind: "slow" | "haste";
  /** Pulse phase in s16-angle units (FUN_8013f548 +0x1e). */
  pulsePhase: number;
}

/** DERIVED zz_013f300_ constants (see StatusAura doc). */
const STATUS_FX_TEXIDS: ReadonlyArray<{ texId: number; slot: 0 | 1 | 2 }> = [
  { texId: 48, slot: 0 },
  { texId: 48, slot: 0 },
  { texId: 49, slot: 1 },
  { texId: 50, slot: 2 },
];
const STATUS_FX_PULSE_STEP = { slow: 0x222, haste: 0x444 } as const;
const STATUS_FX_HAND_SPIN = { 1: -2184, 2: -182 } as const; // s16 units/frame (0xf778/0xff4a)
const S16_TO_RAD = (Math.PI * 2) / 0x10000;

interface ProjectileActor {
  /** Scene node: a camera-facing Sprite for billboard kinds, the crossed-plane beam rig
   *  (long axis oriented along velocity each frame) for "energy" bolts, or (when the sim
   *  resolved a flightVisual) the efct00 bank-mesh Group attached to the moving projectile. */
  node: THREE.Object3D;
  /** Material shared by the sprite (billboards) or by BOTH crossed planes (beam rig).
   *  Unused (a dummy) for bank-mesh projectiles, which own their own `bankMaterials`. */
  material: THREE.SpriteMaterial | THREE.MeshBasicMaterial;
  /**
   * The sim's Projectile object. stepProjectiles mutates projectiles IN PLACE and writes
   * `despawnReason` on this same object the frame it is dropped from the survivors list
   * (packages/combat/src/types.ts), so holding the reference lets the despawn sweep read
   * why the uid vanished and fire impact FX only for real impacts.
   */
  sim: Projectile;
  /** True when `node` is the velocity-oriented beam rig (needs per-frame orient/stretch). */
  beam: boolean;
  /** Per-layer materials of a bank-mesh flight visual (Projectile.flightVisual resolved —
   *  research/decomp/efct-consumers-decode-2026-07-04.md §3), so opacity fade can be applied
   *  on top of the layer's own matAnim-sampled rest opacity, same convention as BankFxActor. */
  bankMaterials?: THREE.MeshBasicMaterial[];
  bankLayerOpacity?: number[];
}

interface ImpactActor {
  sprite: THREE.Sprite;
  material: THREE.SpriteMaterial;
  age: number;
  ttl: number;
  startScale: THREE.Vector2;
  endScale: THREE.Vector2;
  /** Opacity at age `delay` (fades linearly to 0 over ttl). */
  startOpacity: number;
  /** Seconds to hold the sprite invisible before its ttl window starts (the ROM's variant-2
   *  ring layer keys scale/alpha 0 until frame 3 — see IMPACT_EFFECT_STYLES). Default 0. */
  delay?: number | undefined;
  /** Optional flipbook: material.map steps through these frames over the lifetime. */
  flipbookFrames?: readonly THREE.Texture[] | undefined;
}

/** Team-tinted placeholder material colors. */
const TEAM_COLORS: Record<number, number> = { 0: 0x4cc7ff, 1: 0xff5a4d };

// ---------------------------------------------------------------------------
// efct00_mdl.arc particle bank — the ROM's REAL texId -> visual definitions.
//
// DERIVED (research/decomp/ptl-format-notes-2026-07-04.md): the effect handlers'
// texIds index the scene_data JOBJDesc array of efct00_mdl.arc (157 entries),
// resolved by zz_0006fb4_ @80006fb4 on the bank object DAT_803bb374 built from
// efct.pzz member1 by zz_0042954_/zz_0006c88_ (HSD_ArchiveParse). The entries are
// UNTEXTURED vertex-colored GX meshes (the archive holds zero TOBJ/TEX0 data), so
// the port renders them as real THREE meshes — this replaces the former TUNED
// texId->ptcl00/efct00 sprite-cell stand-ins (which remain as load-failure /
// missing-entry fallbacks). Data: apps/game/src/sim/data/efctBankMeshes.json,
// generated by scripts/gen-ptl-cell-map.mjs (provenance in its _meta).
// ---------------------------------------------------------------------------
interface EfctBankMeshJson {
  positions: number[];
  colors: number[] | null;
  indices: number[];
}
/**
 * Decoded HSD MatAnim color tracks of one DOBJ (generator: scripts/gen-ptl-cell-map.mjs).
 * Keys are [frame, value 0..1, interpCode]; `a` is already converted to OPACITY. The ROM
 * samples these at a caller-chosen frame (zz_00086b8_/zz_000726c_ attach + set frame):
 * team/player index for muzzle/launch FX and projectile visuals, the 0..1 pulse (+2 when
 * slow) for the slow/haste status FX. Impact effects do NOT attach matAnim — do not apply
 * these to spawnHitFx layers.
 */
interface EfctBankAnimJson {
  end: number;
  r?: number[][];
  g?: number[][];
  b?: number[][];
  a?: number[][];
}
interface EfctBankDobjJson {
  dif: number[];
  alpha: number;
  blend: string;
  renderFlags: number;
  mesh: EfctBankMeshJson;
  anim?: EfctBankAnimJson;
}
interface EfctBankJobjJson {
  parent: number;
  flags: number;
  r?: number[];
  s?: number[];
  t?: number[];
  dobjs: EfctBankDobjJson[];
}
interface EfctBankEntryJson {
  jobjs: EfctBankJobjJson[];
  hasMatAnim?: boolean;
}
const EFCT_BANK_ENTRIES = (efctBankJson as unknown as { entries: Record<string, EfctBankEntryJson> }).entries;

/** One drawable layer of a bank entry: shared geometry + material recipe. */
interface BankFxLayer {
  geometry: THREE.BufferGeometry;
  color: THREE.Color;
  /** Material diffuse alpha x material alpha float — the layer's rest opacity. */
  baseOpacity: number;
  /** True for the ROM's srcAlpha+ONE PE blend (the dominant bank mode). */
  additive: boolean;
  vertexColors: boolean;
  /** Decoded MatAnim color tracks (replace the material diffuse when sampled). */
  anim?: EfctBankAnimJson | undefined;
}

/**
 * Evaluate one MatAnim track at `frame`. interpCode 1 (HSD_A_OP_CON) holds the left key's
 * value (step); every other code is evaluated linearly (spline tangents were dropped by the
 * generator — documented TUNED approximation). Out-of-range frames clamp to the end keys.
 */
function evalBankTrack(keys: number[][] | undefined, frame: number, rest: number): number {
  if (!keys || keys.length === 0) return rest;
  const first = keys[0];
  if (!first || frame <= (first[0] ?? 0)) return first?.[1] ?? rest;
  for (let i = 0; i + 1 < keys.length; i++) {
    const k0 = keys[i];
    const k1 = keys[i + 1];
    if (!k0 || !k1) break;
    const f0 = k0[0] ?? 0;
    const f1 = k1[0] ?? 0;
    if (frame < f1) {
      if ((k0[2] ?? 2) === 1 || f1 <= f0) return k0[1] ?? rest; // CON = step
      const t = (frame - f0) / (f1 - f0);
      return (k0[1] ?? 0) + ((k1[1] ?? 0) - (k0[1] ?? 0)) * t;
    }
  }
  return keys[keys.length - 1]?.[1] ?? rest;
}

/**
 * Sample a layer's MatAnim color at `frame` into (color, opacity). The ROM's matAnim tracks
 * REPLACE the material diffuse/alpha (HSD AOBJ writes the MObj channels), so channels with a
 * track ignore the rest value; trackless channels keep it.
 */
function sampleBankAnim(
  layer: BankFxLayer,
  frame: number,
  outColor: THREE.Color,
): { opacity: number } {
  const anim = layer.anim;
  if (!anim) {
    outColor.copy(layer.color);
    return { opacity: layer.baseOpacity };
  }
  outColor.setRGB(
    evalBankTrack(anim.r, frame, layer.color.r),
    evalBankTrack(anim.g, frame, layer.color.g),
    evalBankTrack(anim.b, frame, layer.color.b),
  );
  return { opacity: evalBankTrack(anim.a, frame, layer.baseOpacity) };
}

/**
 * Evaluate the boot.dol effect-layer keyframe tracks (scale {frame,x,y,z} / alpha {frame,a},
 * -1-terminated in ROM, linear interpolation — the same evaluators zz_0018fd8_/zz_0019370_
 * the impact chain uses). Frames are 60fps ROM frames.
 */
function evalRomKeys(keys: ReadonlyArray<readonly number[]>, frame: number, out: number[]): void {
  const first = keys[0];
  const last = keys[keys.length - 1];
  if (!first || !last) return;
  const src = frame <= (first[0] ?? 0) ? first : frame >= (last[0] ?? 0) ? last : null;
  if (src) {
    for (let c = 1; c < src.length; c++) out[c - 1] = src[c] ?? 0;
    return;
  }
  for (let i = 0; i + 1 < keys.length; i++) {
    const k0 = keys[i];
    const k1 = keys[i + 1];
    if (!k0 || !k1) break;
    const f0 = k0[0] ?? 0;
    const f1 = k1[0] ?? 0;
    if (frame < f1) {
      const t = f1 > f0 ? (frame - f0) / (f1 - f0) : 0;
      for (let c = 1; c < k0.length; c++) out[c - 1] = (k0[c] ?? 0) + ((k1[c] ?? 0) - (k0[c] ?? 0)) * t;
      return;
    }
  }
}
/** Shared geometry cache: texId -> drawable layers (null = entry has no drawable mesh). */
const bankFxTemplates = new Map<number, BankFxLayer[] | null>();

function buildBankFxTemplate(texId: number): BankFxLayer[] | null {
  const entry = EFCT_BANK_ENTRIES[String(texId)];
  if (!entry) return null;
  const layers: BankFxLayer[] = [];
  // JOBJ local TRS composes T * Rz*Ry*Rx * S (HSD euler order); parent-relative.
  const worlds: THREE.Matrix4[] = [];
  const scratchQ = new THREE.Quaternion();
  for (const [i, jobj] of entry.jobjs.entries()) {
    const local = new THREE.Matrix4().compose(
      new THREE.Vector3(...((jobj.t as [number, number, number] | undefined) ?? [0, 0, 0])),
      scratchQ.setFromEuler(new THREE.Euler(jobj.r?.[0] ?? 0, jobj.r?.[1] ?? 0, jobj.r?.[2] ?? 0, "ZYX")),
      new THREE.Vector3(...((jobj.s as [number, number, number] | undefined) ?? [1, 1, 1])),
    );
    const parentWorld = jobj.parent >= 0 ? worlds[jobj.parent] : undefined;
    const world = parentWorld ? new THREE.Matrix4().multiplyMatrices(parentWorld, local) : local;
    worlds[i] = world;
    for (const dobj of jobj.dobjs) {
      if (dobj.mesh.indices.length === 0) continue;
      const geometry = new THREE.BufferGeometry();
      geometry.setAttribute("position", new THREE.Float32BufferAttribute(dobj.mesh.positions, 3));
      if (dobj.mesh.colors) {
        geometry.setAttribute("color", new THREE.BufferAttribute(new Uint8Array(dobj.mesh.colors), 4, true));
      }
      geometry.setIndex(dobj.mesh.indices);
      geometry.applyMatrix4(world);
      const dif = dobj.dif;
      layers.push({
        geometry,
        color: new THREE.Color((dif[0] ?? 255) / 255, (dif[1] ?? 255) / 255, (dif[2] ?? 255) / 255),
        baseOpacity: ((dif[3] ?? 255) / 255) * dobj.alpha,
        additive: dobj.blend === "add",
        vertexColors: dobj.mesh.colors !== null,
        anim: dobj.anim,
      });
    }
  }
  return layers.length > 0 ? layers : null;
}

function bankFxTemplate(texId: number): BankFxLayer[] | null {
  let tpl = bankFxTemplates.get(texId);
  if (tpl === undefined) {
    tpl = buildBankFxTemplate(texId);
    bankFxTemplates.set(texId, tpl);
  }
  return tpl;
}

/** Live bank-mesh FX instance (mesh analogue of ImpactActor's sprite fields). */
interface BankFxActor {
  node: THREE.Group;
  materials: THREE.MeshBasicMaterial[];
  /** Per-material rest opacity (the bank layer's dif.a x alpha). */
  layerOpacity: number[];
  age: number;
  ttl: number;
  /** Seconds held invisible before the ttl window starts (ROM delayed layers). */
  delay?: number | undefined;
  startScale: THREE.Vector3;
  endScale: THREE.Vector3;
  /** Whole-effect opacity multiplier at age `delay` (fades linearly to 0 over ttl). */
  startOpacity: number;
  /** ROM scale keyframes {frame,x,y,z} (60fps frames). When set they REPLACE the
   *  startScale->endScale lerp with the exact multi-key piecewise-linear curve. */
  scaleKeys?: ReadonlyArray<readonly number[]> | undefined;
  /** ROM alpha keyframes {frame,a}. When set they REPLACE the linear 1->0 fade. */
  alphaKeys?: ReadonlyArray<readonly number[]> | undefined;
}

// ---------------------------------------------------------------------------
// Battle FX textures — the game's REAL particle art.
//
// Primary sources are the canonical HSDRaw/GXImageConverter exports of the disc's
// shared particle container ptcl00.txg (apps/game/public/ui/txg/ptcl00/image_*.png,
// see research/asset-inventory/ptcl00-txg-export-results.json) plus the efct00.tpl
// blob/ring atlas. Cell identification is documented in
// research/asset-inventory/ptcl00-cell-map.md. The hit-impact effect SELECTION chain
// (damage record impactEffectId -> effect variant/lifetimes/scale-alpha curves) IS
// decoded (research/decomp/impact-effect-id-decode-2026-07-04.md), and the final
// texId hop is NOW decoded too: zz_0006fb4_'s texId indexes the scene_data JOBJDesc
// array of efct00_mdl.arc — untextured vertex-colored meshes rendered by spawnBankFx
// from efctBankMeshes.json (research/decomp/ptl-format-notes-2026-07-04.md). The
// sprite cells below remain for the OTHER effects (muzzle, death explosion, dash
// burst, charge glow, projectile puffs — chains not yet decoded to a texId) and as
// spawnHitFx fallbacks; those effect->cell assignments are still TUNED-visual.
//
// RGB565 cells have no alpha channel (black = transparent -> additive blending).
// Cells #2/#5/#6 are mirror-wrap QUADRANTS: the bright corner is the sprite centre
// and the full radial sprite is reconstructed with MirroredRepeatWrapping +
// repeat(2,2) (the GX WRAP_MIRROR sampling the original renderer used).
// The older hand-extracted /fx PNGs (same cells, earlier decode) stay as fallbacks.
// ---------------------------------------------------------------------------
interface FxTextureSource {
  /** Canonical ptcl00.txg export. */
  url: string;
  /** Older hand-extracted copy of the same cell, swapped in if the export 404s. */
  fallback: string;
  /** True when the cell is a mirror-wrap quadrant (bright corner = sprite centre). */
  quadrant: boolean;
}

const FX_SOURCES = {
  /** ptcl00.txg#5 — blue-violet energy glow quadrant (energy shots). */
  energy: { url: "/ui/txg/ptcl00/image_05_RGB565.png", fallback: "/fx/energy_dot.png", quadrant: true },
  /** ptcl00.txg#1 — orange fireball core (flame shots + death-explosion core). */
  flame: { url: "/ui/txg/ptcl00/image_01_RGB565.png", fallback: "/fx/flame_core.png", quadrant: false },
  /** ptcl00.txg#6 — orange ray-burst quadrant (muzzle flash). */
  muzzle: { url: "/ui/txg/ptcl00/image_06_RGB565.png", fallback: "/fx/muzzle_flash.png", quadrant: true },
  /** ptcl00.txg#2 — white-hot ember gradient quadrant (hit-spark core). */
  hitSpark: { url: "/ui/txg/ptcl00/image_02_RGB565.png", fallback: "/fx/hit_spark.png", quadrant: true },
  /** ptcl00.txg#0 — wispy white star burst (dash/boost burst: the white star in captures). TUNED-visual. */
  dashStar: { url: "/ui/txg/ptcl00/image_00_I4.png", fallback: "/fx/spark_star.png", quadrant: false },
  /** ptcl00.txg#7 — magenta spiral aura (charge-shot glow). TUNED-visual. */
  chargeGlow: { url: "/ui/txg/ptcl00/image_07_RGB565.png", fallback: "/fx/aura_glow.png", quadrant: false },
} as const satisfies Record<string, FxTextureSource>;

/** efct00.tpl#0 atlas (256x64 RGB5A3, real alpha): ring / puff / smoke cells. */
const IMPACT_ATLAS_URL = "/fx/efct00_atlas.png";
/** 2x2 block of 16x16 white puff cells at (64,0)-(96,32) in efct00_atlas, read as a
 *  4-frame dissipating-puff sequence and flipbooked on projectile impacts. TUNED-visual. */
const IMPACT_PUFF_CELLS: ReadonlyArray<readonly [number, number]> = [
  [64, 0],
  [80, 0],
  [64, 16],
  [80, 16],
];
const IMPACT_PUFF_CELL_SIZE = 16;
/** White shockwave ring cell at (0,0,32,32) in efct00_atlas. */
const RING_CELL = { x: 0, y: 0, w: 32, h: 32 } as const;
/** Soft dark smoke ball at (160,0,64,64) in efct00_atlas (black RGB + alpha). */
const SMOKE_CELL = { x: 160, y: 0, w: 64, h: 64 } as const;
const PROJECTILE_COLORS: Record<ProjectileVisualKind, { ally: number; enemy: number }> = {
  energy: { ally: 0x91eaff, enemy: 0xff7a4d },
  flame: { ally: 0xffd36a, enemy: 0xff5a2e },
  muzzle: { ally: 0xfff1a8, enemy: 0xffb14a },
};

/**
 * Projectile end-of-life fade window (frames of remaining `life`). Derived from the DEFAULT
 * projectile lifetime SHOT.LIFETIME (600f, DERIVED_ROM: init FUN_8006f11c seeds the life
 * counter, chunk_0009.c:3907 — see packages/combat constants.ts) instead of the old hardcoded
 * 12 that was tuned against the pre-overhaul TUNED 40f lifetime. The 2% ratio is TUNED-visual:
 * under the corrected 600f default it reproduces the same 12-frame dissolve, so the short
 * per-borg TUNED lifetimes in data/actionProfiles.json (~40f) keep looking exactly as before,
 * while a lifetime retune moves the window with it. Fades to 0 (no 0.35 floor) so lifetime
 * expiry dissolves instead of popping; real impacts despawn early at full opacity and get
 * impact FX instead.
 */
const PROJECTILE_FADE_FRAMES = Math.max(1, Math.round(SHOT.LIFETIME * 0.02));

/**
 * Beam ("energy" visualKind) bolt stretch, in frames of travel: the rig's long axis spans the
 * distance covered over the last N frames (length = |vel| * N, floored at the billboard
 * footprint). TUNED-visual — matched by eye against captures of elongated energy bolts; no
 * ROM-side stretch/trail parameter is decoded (ptcl00.ptl/.ref are unparsed).
 */
const BEAM_STRETCH_FRAMES = 3;

/** Shared unit-plane geometries for the beam rig: two crossed planes with the long axis along
 *  local +Y (PlaneGeometry height), reused by every beam actor and never disposed per-actor. */
const BEAM_PLANE_XY = new THREE.PlaneGeometry(1, 1);
const BEAM_PLANE_ZY = new THREE.PlaneGeometry(1, 1).rotateY(Math.PI / 2);

/** +Y unit vector (the beam rig's rest long axis) for orientBeam's quaternion. */
const BEAM_REST_AXIS = new THREE.Vector3(0, 1, 0);

/** Scratch vector for orientBeam — reused every frame so the syncProjectiles hot loop stays
 *  allocation-free (same convention as the rest of the per-frame sync code). */
const BEAM_DIR_SCRATCH = new THREE.Vector3();

/** Scratch output for evalRomKeys in the per-frame FX loop (allocation-free). */
const BANK_KEY_SCRATCH: number[] = [0, 0, 0];

// ---------------------------------------------------------------------------
// Launch/muzzle FX family zz_00aedc0_ @0x800aedc0 — DERIVED
// (research/decomp/efct-consumers-decode-2026-07-04.md).
//
// The generic shot muzzle flash is family id 0: FUN_80072218 (chunk_0010.c:174) builds a
// basis from the gun joint matrix (+0xa24 block, forward negated by FLOAT_80437780 = -1.0,
// unit scale) and calls zz_00aedc0_(actor, basis, 0, teamByte) plus SFX 6. Id 0 resolves
// through the fence table 0x802fafd0 to ONE layer (row 0 of the 0xc-stride def table
// 0x802faef8): texId 35, life 4f, with the boot.dol keyframe tracks below. The layer loads
// from the SAME efct00_mdl.arc bank as the impacts and attaches the entry's matAnim at
// frame = player/team index (zz_000726c_) — entry 35's decoded tracks make that blue for
// index 0 and red-pink for index 1.
// ---------------------------------------------------------------------------
/** texId 35 scale keys {frame,x,y,z} @0x802faa08 (z = shot direction in the ROM basis). */
const MUZZLE_FLASH_SCALE_KEYS: ReadonlyArray<readonly number[]> = [
  [0, 1, 1, 1],
  [1, 0.25, 0.25, 0.25],
  [4, 0, 0, 0.25],
];
/** texId 35 alpha keys {frame,a} @0x802faa48. */
const MUZZLE_FLASH_ALPHA_KEYS: ReadonlyArray<readonly number[]> = [
  [0, 1],
  [1, 1],
  [4, 0],
];
/** texId 35 lifetime, frames (layer-def row 0 @0x802faef8). */
const MUZZLE_FLASH_LIFE_FRAMES = 4;

export class BattleScene {
  private actors = new Map<string, Actor>();
  private projectileActors = new Map<string, ProjectileActor>();
  private impactActors: ImpactActor[] = [];
  private bankFxActors: BankFxActor[] = [];
  private pending = new Set<string>();
  private projectileTextures = new Map<ProjectileVisualKind, THREE.Texture>();
  private impactPuffFrames: THREE.Texture[];
  private ringTexture: THREE.Texture;
  private smokeTexture: THREE.Texture;
  private hitSparkTexture: THREE.Texture;
  private dashStarTexture: THREE.Texture;
  private chargeGlowTexture: THREE.Texture;
  /** Render camera, provided by main.ts (setCamera) — used by the status-aura clock-hand
   *  billboards (the ROM's FUN_8013f790 draw path builds a camera-facing basis). Null-safe:
   *  without it the hands spin in the world XY plane instead of the view plane. */
  private camera: THREE.Camera | null = null;
  /** Enemy lock-on marker, shown ONLY over the local player's enemy lockTarget. */
  private enemyReticle: THREE.Group;
  private enemyReticleFill: THREE.MeshBasicMaterial;
  /** Ally lock-on marker (green arrow) — deliberately a different shape+color than the enemy reticle. */
  private allyMarker: THREE.Group;

  constructor(
    private readonly root: THREE.Group,
    private readonly assets: BorgAssets,
  ) {
    const projectileKinds: ProjectileVisualKind[] = ["energy", "flame", "muzzle"];
    for (const kind of projectileKinds) {
      this.projectileTextures.set(kind, loadFxTexture(FX_SOURCES[kind]));
    }
    this.hitSparkTexture = loadFxTexture(FX_SOURCES.hitSpark);
    this.dashStarTexture = loadFxTexture(FX_SOURCES.dashStar);
    this.chargeGlowTexture = loadFxTexture(FX_SOURCES.chargeGlow);
    this.impactPuffFrames = IMPACT_PUFF_CELLS.map(([x, y]) =>
      makeAtlasTexture(IMPACT_ATLAS_URL, x, y, IMPACT_PUFF_CELL_SIZE, IMPACT_PUFF_CELL_SIZE),
    );
    this.ringTexture = makeAtlasTexture(IMPACT_ATLAS_URL, RING_CELL.x, RING_CELL.y, RING_CELL.w, RING_CELL.h);
    this.smokeTexture = makeAtlasTexture(IMPACT_ATLAS_URL, SMOKE_CELL.x, SMOKE_CELL.y, SMOKE_CELL.w, SMOKE_CELL.h);
    const reticle = makeArrowMdlMarker({
      fillColor: RETICLE_RANGED_COLOR,
      edgeColor: 0xffffff,
      opacity: 0.78,
      scale: ENEMY_ARROW_MARKER_SCALE,
      renderOrder: 30,
    });
    this.enemyReticle = reticle.group;
    this.enemyReticleFill = reticle.fillMaterial;
    this.root.add(this.enemyReticle);
    this.allyMarker = makeArrowMdlMarker({
      fillColor: 0x35d977,
      edgeColor: 0xeafff2,
      opacity: 0.74,
      scale: ALLY_ARROW_MARKER_SCALE,
      renderOrder: 25,
    }).group;
    this.root.add(this.allyMarker);
  }

  /** Provide the render camera (billboard basis for the status-aura clock hands). */
  setCamera(camera: THREE.Camera): void {
    this.camera = camera;
  }

  /** Map a sim state/action to one of the exported game animation groups. */
  private slotForBorg(b: BattleActorView): AnimSlot {
    if (b.dashActiveFrames > 0) return dashSlotForBorg(b);
    if (b.state === "death") return "death";
    if (b.state === "down") return "down";
    if (b.state === "hit") return "hit";
    if (b.state === "spawn") return "spawn";
    if (b.state === "special") return "special";
    if (b.state === "attack") {
      if (b.anim === "charge_shot") return "charge_shot";
      if (b.anim === "shoot") return "shoot";
      if (b.anim === "melee") return "melee";
      return "attack";
    }
    if (b.state === "fly") return "fly";
    if (b.state === "jump") {
      // Rising vs falling: the sim keeps state "jump" for the whole airborne arc while
      // gravity (JUMP.GRAVITY 0.42/frame) drives vel.y negative after the apex. -0.6
      // (~1.5 frames past apex) keeps apex jitter and boost-thrust oscillation from
      // flip-flopping the slot. "fall" maps to the exported jump_land bank and falls
      // back to jump/fly for borgs without one.
      return b.vel.y < -0.6 ? "fall" : "jump";
    }
    if (b.state === "move") return "move";
    return "idle";
  }

  /** Reconcile the scene with the current list of live borgs. Call once per frame. */
  sync(
    borgs: readonly BattleActorView[],
    projectiles: readonly Projectile[] = [],
    localActiveUid: string | null = null,
    meleeMode = false,
  ): void {
    const live = new Set<string>();
    for (const b of borgs) {
      live.add(b.uid);
      let actor = this.actors.get(b.uid);
      if (!actor) {
        actor = this.spawn(b);
        this.actors.set(b.uid, actor);
      }
      // Position + facing (sim units map 1:1 to the existing world scale).
      actor.group.position.set(b.pos.x, b.pos.y, b.pos.z);
      actor.group.rotation.y = b.rotY;
      // Animation slot from state.
      let slot = this.slotForBorg(b);
      if (slot === "melee") {
        const wasMelee = actor.lastSeenSlot === "melee" || actor.lastSeenSlot === "melee_alt";
        if (!wasMelee) actor.meleeParity = !actor.meleeParity;
        if (actor.meleeParity) slot = "melee_alt";
      }
      const slotChanged = actor.lastSeenSlot !== slot;
      // Contact effect on hit-reaction entry, styled by the DERIVED impactEffectId of the
      // record that caused it (spawnHitFx). +82 lift = the old hit-spark torso height (TUNED).
      if (slot === "hit" && slotChanged) {
        // yaw = the victim's facing (locked victims usually face their attacker) — TUNED
        // stand-in for the ROM's attacker->contact orientation basis (zz_0045ef4_).
        this.spawnHitFx(
          new THREE.Vector3(b.pos.x, b.pos.y + 82, b.pos.z),
          b.lastHitImpactEffectId,
          b.lastHitAttackerTeam,
          b.rotY,
        );
      }
      // Edge-triggered battle FX (same pattern as the hit spark above).
      if (slot === "death" && slotChanged) this.spawnDeathExplosion(actor.group.position);
      if (slotChanged && slot.startsWith("dash")) this.spawnDashBurst(actor.group.position);
      if (slot === "special" && slotChanged) this.spawnSpecialBurst(actor.group.position);
      if ((slot === "shoot" || slot === "charge_shot") && slotChanged) this.spawnMuzzleFlash(actor.group.position, b.rotY, b.team);
      this.syncChargeGlow(actor, b);
      this.syncStatusFx(actor, b);
      if (slotChanged) this.assets.onSlotEnter?.(actor.borgId, slot, b.uid, b.meleeSounds);
      actor.lastSeenSlot = slot;
      if (actor.ready) this.playSlot(actor, slot, b.meleeAnimStream);
      // Dim/hide once dead so the death pose reads (sim culls dead borgs next frame).
      if (!b.alive) actor.group.visible = true;
    }
    // Despawn actors whose borg is gone.
    for (const [uid, actor] of this.actors) {
      if (!live.has(uid)) {
        actor.chargeGlow?.material.dispose();
        this.disposeActorStatusFx(actor);
        this.root.remove(actor.group);
        this.actors.delete(uid);
      }
    }
    this.syncLockMarkers(borgs, localActiveUid, meleeMode);
    this.syncProjectiles(projectiles);
  }

  /** Advance all per-actor animation mixers. */
  update(dt: number): void {
    for (const actor of this.actors.values()) {
      actor.mixer?.update(dt);
      // Spin the charge aura spiral in the view plane so the swirl reads as building energy.
      if (actor.chargeGlow?.sprite.visible) {
        actor.chargeGlow.material.rotation += dt * CHARGE_GLOW_SPIN_RAD_PER_S;
      }
    }
    if (this.enemyReticle.visible) {
      this.enemyReticle.rotation.y -= dt * ENEMY_RETICLE_SPIN_RAD_PER_S;
    }
    if (this.allyMarker.visible) {
      this.allyMarker.rotation.y += dt * ALLY_MARKER_SPIN_RAD_PER_S;
    }
    this.updateStatusAuras(dt);
    this.updateImpacts(dt);
  }

  /** Remove every actor (call when leaving a battle). */
  clear(): void {
    for (const actor of this.actors.values()) {
      actor.chargeGlow?.material.dispose();
      this.disposeActorStatusFx(actor);
      this.root.remove(actor.group);
    }
    for (const actor of this.projectileActors.values()) this.disposeProjectileActor(actor);
    for (const actor of this.impactActors) this.disposeImpactActor(actor);
    for (const actor of this.bankFxActors) this.disposeBankFxActor(actor);
    this.actors.clear();
    this.projectileActors.clear();
    this.impactActors = [];
    this.bankFxActors = [];
    this.pending.clear();
    this.enemyReticle.visible = false;
    this.allyMarker.visible = false;
  }

  /** World position of an actor (for the camera to follow). */
  positionOf(uid: string): THREE.Vector3 | null {
    return this.actors.get(uid)?.group.position ?? null;
  }

  private spawn(b: BattleActorView): Actor {
    const group = new THREE.Group();
    group.position.set(b.pos.x, b.pos.y, b.pos.z);
    group.rotation.y = b.rotY;
    // Start with a temporary placeholder so the borg is visible immediately;
    // production GLB load failures are allowed to reject loudly.
    const placeholder = this.makePlaceholder(b.team);
    group.add(placeholder);
    this.root.add(group);
    const actor: Actor = {
      group,
      borgId: b.borgId,
      mixer: null,
      actions: {},
      streamActions: {},
      current: null,
      lastSeenSlot: null,
      meleeParity: true, // first melee entry flips this to false => plain "melee" first
      lastMeleeClipKey: null,
      ready: false,
      isPlaceholder: true,
      chargeGlow: null,
      statusFx: { slow: null, haste: null },
    };
    void this.attachModel(b.uid, actor, b.borgId, placeholder).catch((error: unknown) => {
      this.root.remove(group);
      this.actors.delete(b.uid);
      throw error;
    });
    return actor;
  }

  /**
   * Enemy reticle + ally marker for the LOCAL HUMAN player only.
   *
   * Bug history (self-marking): main.ts passes the presentation FOCUS uid, which falls back to
   * a CPU ally while the player waits to respawn, and the old single lock marker trusted that
   * uid (and, with no uid, "any human-owned borg with a lock") with no ownership/team guard on
   * either end — so the one orange marker could render some other combatant's lock and read as
   * marking the player's own team. Now both markers derive strictly from a HUMAN-owned borg
   * (`ownerPlayer !== null`), the enemy reticle additionally requires `target.team !== self.team`
   * and `target.uid !== self.uid`, and the ally marker is a different shape+color, so an enemy
   * reticle can never appear over the player's own borg or an ally.
   */
  private syncLockMarkers(
    borgs: readonly BattleActorView[],
    localActiveUid: string | null,
    meleeMode = false,
  ): void {
    const byUid = localActiveUid ? borgs.find((b) => b.uid === localActiveUid) : undefined;
    const fallback = localActiveUid ? undefined : borgs.find((b) => b.alive && b.ownerPlayer !== null);
    const candidate = byUid ?? fallback ?? null;
    // Only a live, human-owned borg may drive the markers. A CPU-ally focus fallback (player
    // dead, waiting on auto-deploy) hides them; they re-appear on the next deployed borg
    // because activeUidByPlayer/focus switches to its uid.
    const self = candidate && candidate.alive && candidate.ownerPlayer !== null ? candidate : null;

    const enemy = self?.lockTarget ? borgs.find((b) => b.uid === self.lockTarget) : undefined;
    const showEnemy = !!(self && enemy && enemy.alive && enemy.uid !== self.uid && enemy.team !== self.team);
    this.enemyReticle.visible = showEnemy;
    if (showEnemy && enemy) {
      // Centered on the target's torso like the original ring, not floating above the head.
      this.enemyReticle.position.set(enemy.pos.x, enemy.pos.y + 80, enemy.pos.z);
      // Reticle color = "battle mode" cue (behavior-notes (ao), NA manual): the cursor is yellow
      // at ranged distance and flips RED when the locked enemy is within melee reach. The exported
      // arrow mesh is tinted at runtime until the original GX material block is traced.
      this.enemyReticleFill.color.set(meleeMode ? RETICLE_MELEE_COLOR : RETICLE_RANGED_COLOR);
    }

    const ally = self?.allyLockTarget ? borgs.find((b) => b.uid === self.allyLockTarget) : undefined;
    const showAlly = !!(self && ally && ally.alive && ally.uid !== self.uid && ally.team === self.team);
    this.allyMarker.visible = showAlly;
    if (showAlly && ally) {
      this.allyMarker.position.set(ally.pos.x, ally.pos.y + 145, ally.pos.z);
    }
  }

  private makePlaceholder(team: number): THREE.Mesh {
    const geo = new THREE.CapsuleGeometry(28, 64, 4, 8);
    const mat = new THREE.MeshLambertMaterial({ color: TEAM_COLORS[team] ?? 0xcccccc });
    const mesh = new THREE.Mesh(geo, mat);
    mesh.position.y = 60; // sit the capsule on the ground plane
    return mesh;
  }

  private async attachModel(
    uid: string,
    actor: Actor,
    borgId: string,
    placeholder: THREE.Object3D,
  ): Promise<void> {
    const model = await this.assets.loadModel(borgId);
    // The actor may have been despawned while loading.
    if (!this.actors.has(uid)) return;
    actor.group.remove(placeholder);
    disposeMesh(placeholder);
    actor.group.add(model);
    actor.mixer = new THREE.AnimationMixer(model);
    actor.current = null;
    actor.isPlaceholder = false;
    actor.ready = true;
  }

  private playSlot(actor: Actor, slot: AnimSlot, meleeAnimStream?: { group: number; slot: number } | null): void {
    // Per-combo-step melee anim (and, since the air-B/charge exact-data pass, charged
    // releases): the slot axis ("melee"/"melee_alt"/"charge_shot") stays constant across a
    // whole combo chain or charge, but a resolved stream ref should still swap the clip on
    // every step/release. Track the last CLIP actually played (lastMeleeClipKey) separately
    // from `current` so this case bypasses the plain slot-unchanged short-circuit below
    // without disturbing every other slot's existing behavior. combat.ts sets
    // BorgRuntime.meleeAnimStream for BOTH the melee ladder/air-B leaf AND a charged
    // release's charge leaf (startMeleeAttack / startShotAttack respectively) — same field,
    // reused per the renderer bridge's original design (borgPresentationAssets.ts doc).
    const streamRef =
      (slot === "melee" || slot === "melee_alt" || slot === "charge_shot") && meleeAnimStream ? meleeAnimStream : null;
    const streamKey = streamRef ? `${slot}@g${streamRef.group}s${streamRef.slot}` : null;
    const clipKey = streamKey ?? slot;
    if (actor.current === slot && actor.lastMeleeClipKey === clipKey) return;
    if (!actor.mixer) {
      return; // placeholder has no animation
    }
    actor.current = slot;
    actor.lastMeleeClipKey = clipKey;

    if (streamKey) {
      const existingStream = actor.streamActions[streamKey];
      if (existingStream) {
        this.crossfadeTo(actor, existingStream, slot);
        return;
      }
      const loader = this.assets.loadClipByStreamRef;
      if (loader && streamRef) {
        void loader(actor.borgId, streamRef).then((clip) => {
          if (!actor.mixer || actor.lastMeleeClipKey !== clipKey) return;
          if (clip) {
            const action = actor.mixer.clipAction(clip);
            actor.streamActions[streamKey] = action;
            this.crossfadeTo(actor, action, slot);
            return;
          }
          // The exact bank isn't in this borg's baked anim_index — fall back to the plain
          // slot-heuristic clip below rather than leaving the actor frozen on its last pose.
          this.playSlotByLabel(actor, slot, clipKey);
        });
        return;
      }
    }
    this.playSlotByLabel(actor, slot, clipKey);
  }

  /** Slot-label-heuristic clip load/play (the pre-existing behavior), keyed by `clipKey` so it
   *  composes with playSlot's per-combo-step stream-ref bypass above. */
  private playSlotByLabel(actor: Actor, slot: AnimSlot, clipKey: string): void {
    if (!actor.mixer) return;
    const existing = actor.actions[slot];
    if (existing) {
      this.crossfadeTo(actor, existing, slot);
      return;
    }
    // Lazily load the clip; apply when ready if still current.
    void this.assets.loadClip(actor.borgId, slot).then((clip) => {
      if (!actor.mixer || actor.lastMeleeClipKey !== clipKey) return;
      if (!clip) {
        // No clip for this slot; try idle as a fallback.
        if (slot !== "idle") {
          void this.assets.loadClip(actor.borgId, "idle").then((idle) => {
            if (!actor.mixer || actor.lastMeleeClipKey !== clipKey || !idle) return;
            const a = actor.mixer.clipAction(idle);
            actor.actions[slot] = a;
            this.crossfadeTo(actor, a, slot);
          });
        }
        return;
      }
      const action = actor.mixer.clipAction(clip);
      actor.actions[slot] = action;
      this.crossfadeTo(actor, action, slot);
    });
  }

  private crossfadeTo(actor: Actor, action: THREE.AnimationAction, slot: AnimSlot): void {
    const looping = slot === "idle" || slot === "move" || slot === "fly";
    action
      .reset()
      .setLoop(looping ? THREE.LoopRepeat : THREE.LoopOnce, looping ? Infinity : 1)
      .play();
    action.clampWhenFinished = !looping;
    // Fade out any other playing action (both the plain slot cache and the per-combo-step
    // stream-ref cache, since a melee chain may cross between the two).
    for (const [s, a] of Object.entries(actor.actions)) {
      if (s !== slot && a !== action && a.isRunning()) a.crossFadeTo(action, 0.18, false);
    }
    for (const a of Object.values(actor.streamActions)) {
      if (a && a !== action && a.isRunning()) a.crossFadeTo(action, 0.18, false);
    }
  }

  private syncProjectiles(projectiles: readonly Projectile[]): void {
    const live = new Set<string>();
    for (const projectile of projectiles) {
      live.add(projectile.uid);
      let actor = this.projectileActors.get(projectile.uid);
      if (!actor) {
        actor = this.spawnProjectile(projectile);
        this.projectileActors.set(projectile.uid, actor);
      }
      actor.sim = projectile; // keep the stable sim reference fresh for the despawn sweep
      actor.node.position.set(projectile.pos.x, projectile.pos.y, projectile.pos.z);
      const fade = Math.min(1, projectile.life / PROJECTILE_FADE_FRAMES);
      if (actor.bankMaterials) {
        // Bank-mesh flight visual: fade multiplies each layer's OWN rest opacity (the
        // matAnim-sampled/authored value), same convention as BankFxActor's tween.
        for (let i = 0; i < actor.bankMaterials.length; i++) {
          actor.bankMaterials[i]!.opacity = (actor.bankLayerOpacity?.[i] ?? 1) * fade;
        }
        actor.node.rotation.y = Math.atan2(projectile.vel.x, projectile.vel.z);
      } else {
        actor.material.opacity = fade;
      }
      if (actor.beam) orientBeam(actor.node, projectile);
      // Persisting projectiles (consumeOnHit === false, ATK-008) apply re-hits WITHOUT
      // despawning; the sim flags each applied hit for exactly one frame
      // (hitConfirmedThisFrame, combat.ts stepProjectiles). Borg hits get the record's
      // DERIVED contact effect (lastImpactEffectId, written alongside the flag).
      if (projectile.hitConfirmedThisFrame) {
        // yaw from the projectile's flight direction — the closest available stand-in for
        // the ROM's attacker->contact basis on projectile hits.
        this.spawnHitFx(
          actor.node.position,
          projectile.lastImpactEffectId,
          projectile.team,
          Math.atan2(projectile.vel.x, projectile.vel.z),
        );
      }
    }

    for (const [uid, actor] of this.projectileActors) {
      if (!live.has(uid)) {
        // Impact FX only for REAL impacts: stepProjectiles writes despawnReason on the
        // projectile OBJECT the same frame it drops it from the survivors list
        // (packages/combat/src/types.ts). Lifetime expiry (600f seed, FUN_8006f11c
        // chunk_0009.c:3907), out-of-bounds culls, and owner-death despawns
        // (zz_00840b8_, chunk_0012.c:3216) vanish without a hit-puff.
        const reason = actor.sim.despawnReason;
        if (reason === "hit-target" || reason === "hit-terrain") {
          // Use the sim's final pos: for hit-terrain it was moved to the geometry impact
          // point (zz_0083244_/zz_0083714_ via zz_006f268_, chunk_0009.c:3956).
          actor.node.position.set(actor.sim.pos.x, actor.sim.pos.y, actor.sim.pos.z);
          if (reason === "hit-target") {
            // Borg hit: the damage record's DERIVED contact effect (chunk_0003.c:8152-8155),
            // carried on the projectile by stepProjectiles as lastImpactEffectId.
            this.spawnHitFx(
              actor.node.position,
              actor.sim.lastImpactEffectId,
              actor.sim.team,
              Math.atan2(actor.sim.vel.x, actor.sim.vel.z),
            );
          } else {
            // Terrain impact: a different ROM path (terrain hit, not the damage-record effect
            // spawner) — keep the generic efct00 puff.
            this.spawnImpact(actor.node.position);
          }
        }
        this.disposeProjectileActor(actor);
        this.projectileActors.delete(uid);
      }
    }
  }

  /**
   * Bank-mesh flight visual (Projectile.flightVisual, research/decomp/
   * efct-consumers-decode-2026-07-04.md §3): the shot's efct00_mdl.arc bank entry attached to
   * the projectile itself instead of the generic sprite/beam stand-in, reusing the SAME cached
   * geometry-template machinery spawnBankFx uses for muzzle flashes and hit impacts. teamTint
   * rows sample the entry's matAnim at the shooter's team frame (1.0 team 0 / 3.0 team 1 —
   * FLOAT_804379d0/d4, same convention as spawnMuzzleFlash) ONCE at spawn (the ROM attaches the
   * matAnim at a fixed frame at init, not a per-frame re-sample — same policy as the muzzle
   * flash). Plain (0x8000-only) rows draw the bank's authored material with no matAnim sample.
   * Returns null when the texId has no drawable bank entry so the caller keeps the sprite.
   */
  private buildBankProjectileActor(projectile: Projectile): ProjectileActor | null {
    const visual = projectile.flightVisual;
    if (!visual) return null;
    const layers = bankFxTemplate(visual.bankTexId);
    if (!layers) return null;
    const node = new THREE.Group();
    const bankMaterials: THREE.MeshBasicMaterial[] = [];
    const bankLayerOpacity: number[] = [];
    const animColor = new THREE.Color();
    const matAnimFrame = visual.teamTint ? (projectile.team === 1 ? 3 : 1) : undefined;
    for (const layer of layers) {
      let color = layer.color;
      let restOpacity = layer.baseOpacity;
      if (matAnimFrame !== undefined && layer.anim) {
        restOpacity = sampleBankAnim(layer, matAnimFrame, animColor).opacity;
        color = animColor.clone();
      }
      const material = new THREE.MeshBasicMaterial({
        color,
        vertexColors: layer.vertexColors,
        transparent: true,
        opacity: restOpacity,
        blending: layer.additive ? THREE.AdditiveBlending : THREE.NormalBlending,
        depthWrite: false,
        side: THREE.DoubleSide,
      });
      node.add(new THREE.Mesh(layer.geometry, material));
      bankMaterials.push(material);
      bankLayerOpacity.push(restOpacity);
    }
    node.position.set(projectile.pos.x, projectile.pos.y, projectile.pos.z);
    node.rotation.y = Math.atan2(projectile.vel.x, projectile.vel.z);
    this.root.add(node);
    // `material` is unused for the bank-mesh path (bankMaterials drives opacity instead); a
    // throwaway MeshBasicMaterial keeps ProjectileActor's shared field non-optional.
    return { node, material: new THREE.MeshBasicMaterial(), sim: projectile, beam: false, bankMaterials, bankLayerOpacity };
  }

  private spawnProjectile(projectile: Projectile): ProjectileActor {
    const bankActor = this.buildBankProjectileActor(projectile);
    if (bankActor) return bankActor;
    const kind = projectile.visualKind;
    const colors = PROJECTILE_COLORS[kind];
    const color = projectile.team === 0 ? colors.ally : colors.enemy;
    if (kind === "energy") {
      // Beam/energy bolts: crossed-plane rig stretched along the flight direction instead of
      // a fixed round billboard, so homing curves read as an oriented bolt. Both planes share
      // one material; geometry is the shared module-level unit plane. TUNED-visual composition
      // (no ROM effect->geometry table is decoded; ptcl00.ptl/.ref are unparsed).
      const material = new THREE.MeshBasicMaterial({
        map: this.projectileTextures.get(kind) ?? null,
        color,
        transparent: true,
        opacity: 1,
        blending: THREE.AdditiveBlending,
        depthWrite: false,
        side: THREE.DoubleSide,
      });
      const node = new THREE.Group();
      node.add(new THREE.Mesh(BEAM_PLANE_XY, material));
      node.add(new THREE.Mesh(BEAM_PLANE_ZY, material));
      node.position.set(projectile.pos.x, projectile.pos.y, projectile.pos.z);
      orientBeam(node, projectile);
      this.root.add(node);
      return { node, material, sim: projectile, beam: true };
    }
    const material = new THREE.SpriteMaterial({
      map: this.projectileTextures.get(kind),
      color,
      transparent: true,
      opacity: 1,
      blending: THREE.AdditiveBlending,
      depthWrite: false,
    });
    const sprite = new THREE.Sprite(material);
    sprite.position.set(projectile.pos.x, projectile.pos.y, projectile.pos.z);
    sprite.scale.setScalar(Math.max(42, projectile.hitRadius * 1.8));
    this.root.add(sprite);
    return { node: sprite, material, sim: projectile, beam: false };
  }

  private disposeProjectileActor(actor: ProjectileActor): void {
    this.root.remove(actor.node);
    if (actor.bankMaterials) {
      // Bank-mesh projectile: geometries are the shared module-level bankFxTemplate cache
      // (never disposed here, same convention as BankFxActor); only per-instance materials
      // + the unused placeholder `material` need disposing.
      for (const material of actor.bankMaterials) material.dispose();
    }
    // Beam rigs share ONE material across both planes and use the shared module-level unit
    // plane geometries (never disposed here) — a single material.dispose covers both paths.
    actor.material.dispose();
  }

  /** Shared short-lived FX sprite: lerps from startScale to endScale while fading out.
   *  Scales accept a scalar or per-axis {x,y} (the ROM's variant-3 slash layer keys X and Y
   *  independently — see IMPACT_EFFECT_STYLES). `delay` holds the sprite invisible first. */
  private spawnBurstSprite(
    map: THREE.Texture | null,
    position: THREE.Vector3,
    opts: {
      ttl: number;
      startScale: number | { x: number; y: number };
      endScale: number | { x: number; y: number };
      opacity: number;
      blending?: THREE.Blending;
      color?: number;
      delay?: number;
      flipbookFrames?: readonly THREE.Texture[];
    },
  ): void {
    if (!map) return;
    const start = typeof opts.startScale === "number" ? { x: opts.startScale, y: opts.startScale } : opts.startScale;
    const end = typeof opts.endScale === "number" ? { x: opts.endScale, y: opts.endScale } : opts.endScale;
    const material = new THREE.SpriteMaterial({
      map,
      color: opts.color ?? 0xffffff,
      transparent: true,
      opacity: opts.opacity,
      blending: opts.blending ?? THREE.NormalBlending,
      depthWrite: false,
    });
    const sprite = new THREE.Sprite(material);
    sprite.position.copy(position);
    sprite.scale.set(start.x, start.y, 1);
    if ((opts.delay ?? 0) > 0) sprite.visible = false;
    this.root.add(sprite);
    this.impactActors.push({
      sprite,
      material,
      age: 0,
      ttl: opts.ttl,
      startScale: new THREE.Vector2(start.x, start.y),
      endScale: new THREE.Vector2(end.x, end.y),
      startOpacity: opts.opacity,
      delay: opts.delay,
      flipbookFrames: opts.flipbookFrames,
    });
  }

  /**
   * Spawn one particle-bank entry (efct00_mdl.arc JOBJDesc[texId]) as a real THREE mesh
   * group — the DERIVED replacement for the sprite-cell stand-ins. Scale keys are the
   * ROM's own multipliers (the meshes are authored in world units, so scale 1 = ROM
   * footprint); opacity fades linearly like spawnBurstSprite (the multi-key alpha curves
   * stay linearly approximated, same as before). `yaw` orients the group (the ROM builds
   * a basis from the attacker->contact direction — the port only has a yaw heuristic at
   * its call sites, which stays TUNED). Returns false when the texId has no drawable
   * entry so callers can keep the sprite fallback.
   */
  private spawnBankFx(
    texId: number,
    position: THREE.Vector3,
    opts: {
      ttl: number;
      startScale: number | { x: number; y: number; z: number };
      endScale: number | { x: number; y: number; z: number };
      opacity: number;
      delay?: number;
      yaw?: number;
      /** ROM scale keyframes {frame,x,y,z}: exact multi-key curve (overrides start/end lerp). */
      scaleKeys?: ReadonlyArray<readonly number[]>;
      /** ROM alpha keyframes {frame,a}: exact fade curve (overrides the linear 1->0 fade). */
      alphaKeys?: ReadonlyArray<readonly number[]>;
      /** Static MatAnim sample frame (the ROM's team/player-index color select — zz_00086b8_/
       *  zz_000726c_ attach the entry's matAnim at this frame). Layers without tracks keep
       *  their material diffuse. */
      matAnimFrame?: number;
    },
  ): boolean {
    const layers = bankFxTemplate(texId);
    if (!layers) return false;
    const start = typeof opts.startScale === "number" ? { x: opts.startScale, y: opts.startScale, z: opts.startScale } : opts.startScale;
    const end = typeof opts.endScale === "number" ? { x: opts.endScale, y: opts.endScale, z: opts.endScale } : opts.endScale;
    const node = new THREE.Group();
    const materials: THREE.MeshBasicMaterial[] = [];
    const layerOpacity: number[] = [];
    const animColor = new THREE.Color();
    for (const layer of layers) {
      let color = layer.color;
      let restOpacity = layer.baseOpacity;
      if (opts.matAnimFrame !== undefined && layer.anim) {
        restOpacity = sampleBankAnim(layer, opts.matAnimFrame, animColor).opacity;
        color = animColor.clone();
      }
      const material = new THREE.MeshBasicMaterial({
        color,
        vertexColors: layer.vertexColors,
        transparent: true,
        opacity: restOpacity * opts.opacity,
        blending: layer.additive ? THREE.AdditiveBlending : THREE.NormalBlending,
        depthWrite: false,
        side: THREE.DoubleSide,
      });
      const mesh = new THREE.Mesh(layer.geometry, material);
      node.add(mesh);
      materials.push(material);
      layerOpacity.push(restOpacity);
    }
    node.position.copy(position);
    if (opts.yaw !== undefined) node.rotation.y = opts.yaw;
    node.scale.set(Math.max(start.x, 1e-4), Math.max(start.y, 1e-4), Math.max(start.z, 1e-4));
    if ((opts.delay ?? 0) > 0) node.visible = false;
    this.root.add(node);
    this.bankFxActors.push({
      node,
      materials,
      layerOpacity,
      age: 0,
      ttl: opts.ttl,
      delay: opts.delay,
      startScale: new THREE.Vector3(start.x, start.y, start.z),
      endScale: new THREE.Vector3(end.x, end.y, end.z),
      startOpacity: opts.opacity,
      scaleKeys: opts.scaleKeys,
      alphaKeys: opts.alphaKeys,
    });
    return true;
  }

  private disposeBankFxActor(actor: BankFxActor): void {
    this.root.remove(actor.node);
    for (const material of actor.materials) material.dispose();
    // Geometries are the shared module-level templates — never disposed here.
  }

  /** Projectile impact: efct00_atlas white puff, flipbooked over its 4-cell sequence. */
  private spawnImpact(position: THREE.Vector3): void {
    this.spawnBurstSprite(this.impactPuffFrames[0] ?? null, position, {
      ttl: 0.28,
      startScale: 54,
      endScale: 110,
      opacity: 0.9,
      flipbookFrames: this.impactPuffFrames,
    });
  }

  /**
   * Hit-impact effect, selected by the damage record's impactEffectId (u8 +0x09).
   *
   * DERIVED selection chain (research/decomp/impact-effect-id-decode-2026-07-04.md):
   * resolve_hitbox_target_effects_and_damage @0x8002e2a8 gates the contact-effect spawn on
   * `record[+0x09] != 0xff` (chunk_0003.c:8087) and calls zz_0019550_(attacker, contactPoint,
   * impactEffectId) (:8154). zz_0019550_ (chunk_0002.c:1501) reads the 4-byte entry at
   * 0x802c7ed0 + id*4 = [unused, variantHandler->+0x11, subVariant->+0x12, kind->+0x13] and
   * spawns an effect object whose init/update handlers are PTR_FUN_802c8174/802c8184[variant].
   * Per-variant defs (PTR_DAT_802c8154) + keyframe tracks dumped from boot.dol:
   *
   *   id 0     -> variant 0: ONE sprite (texId 21), life 20f; scale keys 1@f0 -> 2@f4 -> 3@f20;
   *               alpha keys 1@f0 -> 1@f10 -> 0@f20 (a big slow swelling flash).
   *   id 1     -> variant 1: BURST of (8..11)+(8..11) random particles, life 10f, particle
   *               texId selected by the ATTACKER's player index (texId 2 / 3 for players 0/1 —
   *               FUN_80019a14 chunk_0002.c:1750-1758). 66.7% of all family damage records.
   *   ids 2..7 -> variant 2: THREE layers oriented by the attacker->contact direction
   *               (FUN_8001a288): flash texId 144 life 7f scale 1->0.25->0; core texId 145
   *               life 10f scale 1->0; ring texId 146 life 13f scale 0 until f3 -> 1@f3 ->
   *               1.5@f13, alpha 0/0/1@f3/1@f8/0@f13. The subVariant byte (0..5) is stored at
   *               effect+0x12 but its consumer was NOT located — ids 2-7 render identically
   *               here (honest unknown).
   *   id 8     -> variant 3: TWO layers (FUN_8001a71c): texId 53 life 10f scale 0.5->1@f2->0;
   *               texId 54 life 6f ANISOTROPIC scale (x,y) (0,1.5)->(1,1)@f2->(1.5,0) — a
   *               collapsing/expanding cross, reads as a slash flash.
   *   id 0xff  -> NO contact effect (DERIVED suppression, chunk_0003.c:8087-8088).
   *   other    -> out-of-table ids only appear on familyDamageRecords rows that are table-extent
   *               overshoot (the same corrupt rows combat.ts's isSaneStatusRecord filters);
   *               fall back to the id-1 burst.
   *
   * DERIVED here: the id, its consumption chain, layer counts, lifetimes, scale/alpha keyframe
   * endpoints, the 0xff suppression, the attacker-index texId split of id 1, AND (new) the
   * texId -> visual hop: each texId is rendered from its REAL efct00_mdl.arc bank entry
   * (scene_data JOBJDesc[texId], resolved by zz_0006fb4_ — see spawnBankFx and
   * research/decomp/ptl-format-notes-2026-07-04.md), an untextured vertex-colored GX mesh
   * drawn at ROM scale (the scale keys below are the ROM's own multipliers).
   * TUNED here: the linear approximation of multi-key scale/alpha curves (unchanged), the
   * burst's scatter offsets (the ROM gives each particle a random velocity seed), the yaw
   * heuristic standing in for the ROM's attacker->contact orientation basis, and the sprite
   * fallbacks used only if a texId is missing from the generated bank data.
   */
  private spawnHitFx(
    position: THREE.Vector3,
    impactEffectId: number | undefined,
    attackerTeam: number | undefined,
    yaw?: number,
  ): void {
    const id = impactEffectId ?? 1;
    if (id === 0xff) return; // DERIVED: -1 suppresses the contact effect entirely.
    const at = position;
    if (id === 0) {
      // Variant 0 — single swelling flash: texId 21 (bank spike-star mesh), 20f, scale
      // keys 1 -> 2@f4 -> 3@f20 approximated linearly 1 -> 3 (same policy as before).
      if (
        !this.spawnBankFx(21, at, {
          ttl: 20 / 60,
          startScale: 1,
          endScale: 3,
          opacity: 1,
        })
      ) {
        this.spawnBurstSprite(this.hitSparkTexture, at, {
          ttl: 20 / 60,
          startScale: 36,
          endScale: 108,
          opacity: 1,
          blending: THREE.AdditiveBlending,
        });
      }
      return;
    }
    if (id >= 2 && id <= 7) {
      // Variant 2 — three-layer directional impact: texIds 144 (flash shell) / 145 (core
      // shell) / 146 (delayed flat ring). The ROM orients the layer basis by the
      // attacker->contact direction; `yaw` is the port's TUNED stand-in for that basis.
      const okFlash = this.spawnBankFx(144, at, { ttl: 7 / 60, startScale: 1, endScale: 0, opacity: 1, ...(yaw !== undefined ? { yaw } : {}) });
      const okCore = this.spawnBankFx(145, at, { ttl: 10 / 60, startScale: 1, endScale: 0, opacity: 1, ...(yaw !== undefined ? { yaw } : {}) });
      const okRing = this.spawnBankFx(146, at, {
        ttl: 10 / 60,
        startScale: 1,
        endScale: 1.5,
        opacity: 1,
        delay: 3 / 60,
        ...(yaw !== undefined ? { yaw } : {}),
      });
      if (!okFlash) {
        this.spawnBurstSprite(this.hitSparkTexture, at, {
          ttl: 7 / 60,
          startScale: 52,
          endScale: 0,
          opacity: 1,
          blending: THREE.AdditiveBlending,
        });
      }
      if (!okCore) {
        this.spawnBurstSprite(this.hitSparkTexture, at, {
          ttl: 10 / 60,
          startScale: 40,
          endScale: 0,
          opacity: 0.9,
          blending: THREE.AdditiveBlending,
        });
      }
      if (!okRing) {
        this.spawnBurstSprite(this.ringTexture, at, {
          ttl: 10 / 60,
          startScale: 0,
          endScale: 66,
          opacity: 0.9,
          delay: 3 / 60,
        });
      }
      return;
    }
    if (id === 8) {
      // Variant 3 — two-layer slash flash: texId 53 (spike-star core, scale 0.5 -> 1@f2 ->
      // 0@f10 approximated 1 -> 0) + texId 54 (the cross mesh) with the ROM's ANISOTROPIC
      // keys (x,y,z) (0,1.5,1.5) -> (1,1,1)@f2 -> (1.5,0,0)@f6 approximated linearly.
      const okCore = this.spawnBankFx(53, at, { ttl: 10 / 60, startScale: 1, endScale: 0, opacity: 1, ...(yaw !== undefined ? { yaw } : {}) });
      const okCross = this.spawnBankFx(54, at, {
        ttl: 6 / 60,
        startScale: { x: 0, y: 1.5, z: 1.5 },
        endScale: { x: 1.5, y: 0, z: 0 },
        opacity: 1,
        ...(yaw !== undefined ? { yaw } : {}),
      });
      if (!okCore) {
        this.spawnBurstSprite(this.dashStarTexture, at, {
          ttl: 10 / 60,
          startScale: 44,
          endScale: 0,
          opacity: 1,
          blending: THREE.AdditiveBlending,
        });
      }
      if (!okCross) {
        this.spawnBurstSprite(this.hitSparkTexture, at, {
          ttl: 6 / 60,
          startScale: { x: 0, y: 66 },
          endScale: { x: 66, y: 0 },
          opacity: 1,
          blending: THREE.AdditiveBlending,
        });
      }
      return;
    }
    // Variant 1 (id 1, the dominant record effect) + out-of-table fallback: particle burst,
    // 16..22 particles (DERIVED (8..11)+(8..11)), life 10f. Particle visual = bank texId 2
    // (white-core disc, BLUE rim) for attacker row 0 or texId 3 (PINK rim) for row 1 —
    // the ROM keys the row by the attacker's player index (+0x88); the port maps team 0/1
    // onto rows 0/1 (closest available fact). The rim colors now come from the REAL bank
    // vertex colors, replacing the old TUNED tint constants.
    const count = 16 + Math.floor(Math.random() * 7);
    const burstTexId = attackerTeam === 1 ? 3 : 2;
    for (let i = 0; i < count; i++) {
      const jitter = new THREE.Vector3(
        at.x + (Math.random() - 0.5) * 52,
        at.y + (Math.random() - 0.5) * 52,
        at.z + (Math.random() - 0.5) * 52,
      );
      if (
        !this.spawnBankFx(burstTexId, jitter, {
          ttl: 10 / 60,
          startScale: 0.7 + Math.random() * 0.7,
          endScale: 1.8,
          opacity: 1,
        })
      ) {
        const tint = attackerTeam === undefined ? 0xffffff : attackerTeam === 0 ? 0xbfe4ff : 0xffc9a1;
        this.spawnBurstSprite(this.hitSparkTexture, jitter, {
          ttl: 10 / 60,
          startScale: 10 + Math.random() * 10,
          endScale: 26,
          opacity: 1,
          blending: THREE.AdditiveBlending,
          color: tint,
        });
      }
    }
  }

  /**
   * Death explosion: ptcl00.txg#1 fireball core + efct00_atlas white shockwave ring and
   * dark smoke ball. Composition/timing TUNED-visual (matched by eye against captures);
   * the textures are the real extracted sheets.
   */
  private spawnDeathExplosion(position: THREE.Vector3): void {
    const at = new THREE.Vector3(position.x, position.y + 70, position.z);
    this.spawnBurstSprite(this.projectileTextures.get("flame") ?? null, at, {
      ttl: 0.5,
      startScale: 80,
      endScale: 200,
      opacity: 1,
      blending: THREE.AdditiveBlending,
    });
    this.spawnBurstSprite(this.ringTexture, at, {
      ttl: 0.4,
      startScale: 60,
      endScale: 270,
      opacity: 0.85,
    });
    this.spawnBurstSprite(this.smokeTexture, new THREE.Vector3(at.x, at.y + 24, at.z), {
      ttl: 0.7,
      startScale: 90,
      endScale: 170,
      opacity: 0.8,
    });
  }

  /** Dash/boost burst: ptcl00.txg#0 wispy white star, edge-triggered on dash entry. */
  private spawnDashBurst(position: THREE.Vector3): void {
    this.spawnBurstSprite(this.dashStarTexture, new THREE.Vector3(position.x, position.y + 55, position.z), {
      ttl: 0.26,
      startScale: 62,
      endScale: 132,
      opacity: 0.95,
      blending: THREE.AdditiveBlending,
    });
  }

  /**
   * Caster-side X-special burst, edge-triggered on entry into the "special" anim slot (the
   * same one-shot pattern as spawnDashBurst on dash entry above) so the AoE special reads at
   * its SOURCE — previously only the victims' hit sparks were visible and the burst itself
   * was invisible. Reuses the existing extracted cells: efct00_atlas white shockwave ring
   * (RING_CELL) expanding to the sim's actual AoE reach, plus a ptcl00.txg#1 fireball core.
   * The ring's end scale tracks SPECIAL.RADIUS (packages/combat constants.ts, the TUNED
   * 110-unit XZ burst radius stepSpecials hits against) so the visual footprint matches the
   * hit volume; every other size/color/timing here is TUNED-visual (no ROM effect->texture
   * usage table is decoded — ptcl00.ptl/.ref are unparsed), the pixels are real assets.
   */
  private spawnSpecialBurst(position: THREE.Vector3): void {
    const at = new THREE.Vector3(position.x, position.y + 70, position.z); // torso height, TUNED
    this.spawnBurstSprite(this.projectileTextures.get("flame") ?? null, at, {
      ttl: 0.3, // TUNED-visual: quicker than the 0.5s death fireball so it reads as a pulse
      startScale: 50, // TUNED-visual
      endScale: 140, // TUNED-visual
      opacity: 1,
      blending: THREE.AdditiveBlending,
      color: 0xaad4ff, // TUNED-visual: cool blue-white so it does not read as the death explosion
    });
    this.spawnBurstSprite(this.ringTexture, at, {
      ttl: 0.35, // TUNED-visual
      startScale: 40, // TUNED-visual
      // Sprite scale is the full quad edge, so 2x the sim's XZ burst radius spans the
      // actual AoE diameter (SPECIAL.RADIUS = 110, packages/combat constants.ts).
      endScale: SPECIAL.RADIUS * 2,
      opacity: 0.9, // TUNED-visual
    });
  }

  /**
   * Muzzle flash — DERIVED visual: the ROM's generic shot-launch flash is launch-FX family
   * id 0 (FUN_80072218 chunk_0010.c:174 -> zz_00aedc0_(actor, gunBasis, 0, team) + SFX 6):
   * ONE bank mesh, texId 35 (efct00_mdl.arc JOBJDesc[35], a z-elongated flash cone), life
   * 4f, ROM scale keys (1,1,1) -> (0.25,0.25,0.25)@f1 -> (0,0,0.25)@f4 and alpha 1/1@f1/0@f4
   * (tables 0x802faef8/0x802faa08/0x802faa48 — research/decomp/
   * efct-consumers-decode-2026-07-04.md). The entry's matAnim is attached at frame =
   * player/team index (zz_000726c_), tinting it BLUE for index 0 / RED-PINK for index 1 —
   * the port passes the attacker team (closest available fact, same mapping as the id-1
   * hit burst).
   *
   * TUNED here: the spawn POSITION (the ROM anchors the flash to the gun joint matrix
   * +0xa24; the port has no per-borg joint transforms at FX level, so it keeps the shared
   * sim/render MUZZLE_OFFSET used by combat.ts spawnProjectile), the yaw-only stand-in for
   * the ROM's full launch-direction basis (zz_0045ef4_ mode 5; the mesh z-axis is the shot
   * axis, so yaw covers the grounded-fire case), the trigger heuristic (every shoot/
   * charge_shot slot entry — the ROM triggers per fire function; most projectile-table rows
   * carry launch-FX id -1 = none, but the generic gun path DOES flash via FUN_80072218),
   * and the sprite fallback when the bank entry is missing.
   */
  private spawnMuzzleFlash(position: THREE.Vector3, rotY: number, team: number | undefined): void {
    const at = new THREE.Vector3(
      position.x + Math.sin(rotY) * MUZZLE_OFFSET.forward,
      position.y + MUZZLE_OFFSET.up,
      position.z + Math.cos(rotY) * MUZZLE_OFFSET.forward,
    );
    if (
      this.spawnBankFx(35, at, {
        ttl: MUZZLE_FLASH_LIFE_FRAMES / 60,
        startScale: 1,
        endScale: 0,
        opacity: 1,
        yaw: rotY,
        scaleKeys: MUZZLE_FLASH_SCALE_KEYS,
        alphaKeys: MUZZLE_FLASH_ALPHA_KEYS,
        matAnimFrame: team === 1 ? 1 : 0,
      })
    ) {
      return;
    }
    this.spawnBurstSprite(this.projectileTextures.get("muzzle") ?? null, at, {
      ttl: 0.12,
      startScale: 46,
      endScale: 76,
      opacity: 1,
      blending: THREE.AdditiveBlending,
    });
  }

  /**
   * Charge-shot glow: chargeable shooters accumulate cooldowns["chargeFrames"] while the
   * attack button is held (packages/combat combat.ts stepAttacks) and fire on release.
   * The glow is the real ptcl00.txg#7 magenta spiral aura ramped by charge progress.
   * Tier thresholds mirror the actionProfiles defaults (chargeTier1Frames 30 /
   * chargeTier2Frames 90) — presentation-only TUNED values; per-profile overrides are
   * not visible from BattleActorView (charge frames are the only cooldown fact exposed).
   */
  private syncChargeGlow(actor: Actor, b: BattleActorView): void {
    const frames = b.chargeFrames;
    if (frames <= 0 || !b.alive) {
      if (actor.chargeGlow) actor.chargeGlow.sprite.visible = false;
      return;
    }
    if (!actor.chargeGlow) {
      const material = new THREE.SpriteMaterial({
        map: this.chargeGlowTexture,
        color: 0xffffff,
        transparent: true,
        opacity: 0,
        blending: THREE.AdditiveBlending,
        depthWrite: false,
      });
      const sprite = new THREE.Sprite(material);
      sprite.position.set(0, 82, 0); // torso height, rides the actor group
      sprite.renderOrder = 20;
      actor.group.add(sprite);
      actor.chargeGlow = { sprite, material };
    }
    const glow = actor.chargeGlow;
    const t = Math.min(1, frames / CHARGE_GLOW_TIER2_FRAMES);
    glow.sprite.visible = true;
    glow.material.opacity = 0.35 + 0.6 * t;
    const size = 55 + 90 * t;
    glow.sprite.scale.set(size, size, 1);
    // Tint shifts toward white-hot as tiers are reached (multiplies the magenta sheet).
    glow.material.color.setHex(
      frames >= CHARGE_GLOW_TIER2_FRAMES ? 0xffffff : frames >= CHARGE_GLOW_TIER1_FRAMES ? 0xffd9f5 : 0xdda8ff,
    );
  }

  /**
   * Slow/haste status auras — DERIVED from the ROM's zz_013f300_ status-FX object (see the
   * StatusAura interface doc for the full decode + TUNED ledger). Created while the sim's
   * slow/haste 900f timer runs (the ROM's object also lives exactly while target +0x710/
   * +0x712 is nonzero), destroyed at 0; both kinds can coexist (the ROM spawns independent
   * objects). Anchored to the borg position, parented to the scene root so the clock-hand
   * billboards can copy the camera quaternion without inheriting the actor's yaw.
   */
  private syncStatusFx(actor: Actor, b: BattleActorView): void {
    const wants: ReadonlyArray<["slow" | "haste", boolean]> = [
      ["slow", b.alive && (b.slowHitTimer ?? 0) > 0],
      ["haste", b.alive && (b.hasteHitTimer ?? 0) > 0],
    ];
    for (const [kind, active] of wants) {
      let aura = actor.statusFx[kind];
      if (!active) {
        if (aura) {
          this.disposeStatusAura(aura);
          actor.statusFx[kind] = null;
        }
        continue;
      }
      if (!aura) {
        aura = this.buildStatusAura(kind);
        actor.statusFx[kind] = aura;
      }
      if (aura) aura.group.position.set(b.pos.x, b.pos.y, b.pos.z);
    }
  }

  /** Build one zz_013f300_ aura: 4 bank-mesh parts (texIds 48/48/49/50) with the ROM's
   *  random spin seeding (FUN_8013f84c). Returns null if the bank entries are missing. */
  private buildStatusAura(kind: "slow" | "haste"): StatusAura | null {
    const group = new THREE.Group();
    const parts: StatusAuraPart[] = [];
    for (const def of STATUS_FX_TEXIDS) {
      const layers = bankFxTemplate(def.texId);
      if (!layers) continue;
      const node = new THREE.Group();
      const materials: THREE.MeshBasicMaterial[] = [];
      for (const layer of layers) {
        const material = new THREE.MeshBasicMaterial({
          color: layer.color,
          vertexColors: layer.vertexColors,
          transparent: true,
          opacity: layer.baseOpacity,
          blending: layer.additive ? THREE.AdditiveBlending : THREE.NormalBlending,
          depthWrite: false,
          side: THREE.DoubleSide,
        });
        node.add(new THREE.Mesh(layer.geometry, material));
        materials.push(material);
      }
      // FUN_8013f84c seeding: slot 0 gets random phases + random +/- speeds split by
      // t = (rand&0x3f)/63 across x/z; slots 1/2 (the clock hands) start at phase 0 with
      // the fixed hand speeds. SLOW halves every speed.
      const slowDiv = kind === "slow" ? 2 : 1;
      let part: StatusAuraPart;
      if (def.slot === 0) {
        const t = Math.random();
        part = {
          node,
          materials,
          layers,
          billboard: false,
          phaseX: Math.random() * 0x10000,
          phaseZ: Math.random() * 0x10000,
          spinX: ((Math.random() < 0.5 ? -1 : 1) * 1024 * t) / slowDiv,
          spinZ: ((Math.random() < 0.5 ? -1 : 1) * 1024 * (1 - t)) / slowDiv,
        };
      } else {
        part = {
          node,
          materials,
          layers,
          billboard: true,
          phaseX: 0,
          phaseZ: 0,
          spinX: 0,
          spinZ: STATUS_FX_HAND_SPIN[def.slot] / slowDiv,
        };
      }
      parts.push(part);
      group.add(node);
    }
    if (parts.length === 0) return null;
    this.root.add(group);
    return { group, parts, kind, pulsePhase: 0 };
  }

  private disposeStatusAura(aura: StatusAura): void {
    this.root.remove(aura.group);
    for (const part of aura.parts) for (const material of part.materials) material.dispose();
  }

  private disposeActorStatusFx(actor: Actor): void {
    for (const kind of ["slow", "haste"] as const) {
      const aura = actor.statusFx[kind];
      if (aura) {
        this.disposeStatusAura(aura);
        actor.statusFx[kind] = null;
      }
    }
  }

  /** Per-render advance of the status auras: spins, pulse phase and the pulse-driven
   *  matAnim color sample (frame = pulse, +2 when slow — zz_013fa70_/zz_00086b8_). */
  private updateStatusAuras(dt: number): void {
    const frames = dt * 60; // ROM ticks these per 60fps frame
    const camQ = this.camera?.quaternion ?? null;
    for (const actor of this.actors.values()) {
      for (const kind of ["slow", "haste"] as const) {
        const aura = actor.statusFx[kind];
        if (!aura) continue;
        aura.pulsePhase = (aura.pulsePhase + STATUS_FX_PULSE_STEP[kind] * frames) % 0x10000;
        const pulse = Math.min(1, Math.max(0, Math.sin(aura.pulsePhase * S16_TO_RAD) * 0.5 + 0.5));
        const animFrame = pulse + (kind === "slow" ? 2 : 0);
        for (const part of aura.parts) {
          part.phaseX += part.spinX * frames;
          part.phaseZ += part.spinZ * frames;
          if (part.billboard) {
            // Clock hands: camera-facing basis (FUN_8013f790), spun in the view plane.
            if (camQ) part.node.quaternion.copy(camQ);
            else part.node.quaternion.identity();
            part.node.rotateZ(part.phaseZ * S16_TO_RAD);
          } else {
            // Star ring: world rot z first then x (FUN_8013f698 zz_00457d4_ order) —
            // three.js Euler "XYZ" composes Rx*Ry*Rz, i.e. z applied first in world space.
            part.node.rotation.set(part.phaseX * S16_TO_RAD, 0, part.phaseZ * S16_TO_RAD, "XYZ");
          }
          for (let m = 0; m < part.materials.length; m++) {
            const material = part.materials[m];
            const layer = part.layers[m];
            if (!material || !layer) continue;
            material.opacity = sampleBankAnim(layer, animFrame, material.color).opacity;
          }
        }
      }
    }
  }

  private updateImpacts(dt: number): void {
    for (let i = this.impactActors.length - 1; i >= 0; i--) {
      const actor = this.impactActors[i];
      if (!actor) continue;
      actor.age += dt;
      // Delayed layers (e.g. the variant-2 ring, keyed to appear at frame 3) stay hidden
      // until their delay elapses; the ttl window then runs from that point.
      const delay = actor.delay ?? 0;
      if (actor.age < delay) {
        actor.sprite.visible = false;
        continue;
      }
      actor.sprite.visible = true;
      const t = Math.min(1, (actor.age - delay) / actor.ttl);
      actor.material.opacity = actor.startOpacity * (1 - t);
      actor.sprite.scale.set(
        THREE.MathUtils.lerp(actor.startScale.x, actor.endScale.x, t),
        THREE.MathUtils.lerp(actor.startScale.y, actor.endScale.y, t),
        1,
      );
      // Sprite-sheet flipbook: step the material through the atlas frames over the lifetime.
      if (actor.flipbookFrames && actor.flipbookFrames.length > 0) {
        const idx = Math.min(actor.flipbookFrames.length - 1, Math.floor(t * actor.flipbookFrames.length));
        const frame = actor.flipbookFrames[idx];
        if (frame && actor.material.map !== frame) actor.material.map = frame;
      }
      if (t >= 1) {
        this.disposeImpactActor(actor);
        this.impactActors.splice(i, 1);
      }
    }
    // Bank-mesh FX: same delay/lerp/fade contract as the sprites above, but scale is
    // per-axis (the ROM's variant-3 cross keys x/y/z independently) and opacity fades
    // each layer from its OWN rest opacity (dif.a x material alpha).
    for (let i = this.bankFxActors.length - 1; i >= 0; i--) {
      const actor = this.bankFxActors[i];
      if (!actor) continue;
      actor.age += dt;
      const delay = actor.delay ?? 0;
      if (actor.age < delay) {
        actor.node.visible = false;
        continue;
      }
      actor.node.visible = true;
      const t = Math.min(1, (actor.age - delay) / actor.ttl);
      // ROM keyframe tracks (60fps frames) take precedence over the legacy linear lerp/fade
      // when the spawner provided them (currently the muzzle-flash family — DERIVED curves).
      const frame = (actor.age - delay) * 60;
      let fade = actor.startOpacity * (1 - t);
      if (actor.alphaKeys) {
        evalRomKeys(actor.alphaKeys, frame, BANK_KEY_SCRATCH);
        fade = actor.startOpacity * (BANK_KEY_SCRATCH[0] ?? 0);
      }
      for (let m = 0; m < actor.materials.length; m++) {
        const material = actor.materials[m];
        if (material) material.opacity = (actor.layerOpacity[m] ?? 1) * fade;
      }
      if (actor.scaleKeys) {
        evalRomKeys(actor.scaleKeys, frame, BANK_KEY_SCRATCH);
        actor.node.scale.set(
          Math.max(BANK_KEY_SCRATCH[0] ?? 0, 1e-4),
          Math.max(BANK_KEY_SCRATCH[1] ?? 0, 1e-4),
          Math.max(BANK_KEY_SCRATCH[2] ?? 0, 1e-4),
        );
      } else {
        actor.node.scale.set(
          Math.max(THREE.MathUtils.lerp(actor.startScale.x, actor.endScale.x, t), 1e-4),
          Math.max(THREE.MathUtils.lerp(actor.startScale.y, actor.endScale.y, t), 1e-4),
          Math.max(THREE.MathUtils.lerp(actor.startScale.z, actor.endScale.z, t), 1e-4),
        );
      }
      if (t >= 1) {
        this.disposeBankFxActor(actor);
        this.bankFxActors.splice(i, 1);
      }
    }
  }

  private disposeImpactActor(actor: ImpactActor): void {
    this.root.remove(actor.sprite);
    actor.material.dispose();
  }
}

/**
 * Orient + stretch a beam rig along the projectile's velocity: the rig's rest long axis is
 * local +Y (BEAM_REST_AXIS), rotated onto the normalized velocity; length spans the distance
 * covered over BEAM_STRETCH_FRAMES frames (TUNED-visual), floored at the round billboard
 * footprint so a near-stalled bolt still reads. Near-zero velocity (below the sim's
 * HOMING.MIN_STEER_SPEED-style epsilon) keeps the previous orientation rather than snapping
 * to +Y. Allocation-free (module scratch vector) — runs in the per-frame sync hot loop.
 */
function orientBeam(node: THREE.Object3D, projectile: Projectile): void {
  const width = Math.max(42, projectile.hitRadius * 1.8); // same footprint as billboard kinds
  const speed = BEAM_DIR_SCRATCH.set(projectile.vel.x, projectile.vel.y, projectile.vel.z).length();
  node.scale.set(width, Math.max(width, speed * BEAM_STRETCH_FRAMES), width);
  if (speed > 1e-4) {
    BEAM_DIR_SCRATCH.divideScalar(speed);
    node.quaternion.setFromUnitVectors(BEAM_REST_AXIS, BEAM_DIR_SCRATCH);
  }
}

function dashSlotForBorg(b: BattleActorView): AnimSlot {
  const vx = b.vel.x;
  const vz = b.vel.z;
  const speedSq = vx * vx + vz * vz;
  if (speedSq < 0.0001) return "dash_fwd";

  const sin = Math.sin(b.rotY);
  const cos = Math.cos(b.rotY);
  const forwardDot = vx * sin + vz * cos;
  const rightDot = vx * cos - vz * sin;

  if (Math.abs(forwardDot) >= Math.abs(rightDot)) {
    return forwardDot >= 0 ? "dash_fwd" : "dash_back";
  }
  return rightDot >= 0 ? "dash_right" : "dash_left";
}

function disposeMesh(obj: THREE.Object3D): void {
  obj.traverse((node) => {
    if (node instanceof THREE.Mesh) {
      node.geometry.dispose();
      const mats = Array.isArray(node.material) ? node.material : [node.material];
      for (const m of mats) m.dispose();
    }
  });
}

/** Spin speed of the enemy lock marker (yaw, rad/s). TUNED, presentation only. */
const ENEMY_RETICLE_SPIN_RAD_PER_S = 2.6;
/** Slow yaw spin of the green ally arrow (rad/s). TUNED, presentation only. */
const ALLY_MARKER_SPIN_RAD_PER_S = 2.2;
const ENEMY_ARROW_MARKER_SCALE = 68;
const ALLY_ARROW_MARKER_SCALE = 44;

// Reticle "battle mode" tints (behavior-notes (ao), NA instruction manual): the target cursor is
// yellow at ranged distance and flips RED when the locked enemy is within melee reach. Applied as
// a runtime tint over exported arrow_mdl geometry until the original GX material block is traced.
const RETICLE_RANGED_COLOR = 0xffd21e; // yellow (default lock)
const RETICLE_MELEE_COLOR = 0xff3c14; // red-orange (battle/melee mode)

interface ArrowMdlMarker {
  group: THREE.Group;
  fillMaterial: THREE.MeshBasicMaterial;
}

/**
 * Lock-on marker backed by exported arrow_mdl geometry. The original GX material block is not
 * decoded yet, so fill/edge colors remain runtime tints over source geometry.
 */
function makeArrowMdlMarker(options: {
  fillColor: number;
  edgeColor: number;
  opacity: number;
  scale: number;
  renderOrder: number;
}): ArrowMdlMarker {
  const group = new THREE.Group();
  group.visible = false;
  group.userData = {
    sourceArchive: ARROW_MDL_SOURCE.archivePath,
    sourceArchiveSha1: ARROW_MDL_SOURCE.archiveSha1,
    sourceObj: ARROW_MDL_SOURCE.objPath,
  };

  const geometry = new THREE.BufferGeometry();
  geometry.setAttribute("position", new THREE.BufferAttribute(new Float32Array(ARROW_MDL_POSITIONS), 3));
  geometry.setIndex(new THREE.BufferAttribute(new Uint16Array(ARROW_MDL_INDICES), 1));
  geometry.translate(-ARROW_MDL_BOUNDS.center[0], -ARROW_MDL_BOUNDS.center[1], -ARROW_MDL_BOUNDS.center[2]);
  geometry.computeVertexNormals();

  const fillMaterial = new THREE.MeshBasicMaterial({
    color: options.fillColor,
    transparent: true,
    opacity: options.opacity,
    side: THREE.DoubleSide,
    depthWrite: false,
  });
  const mesh = new THREE.Mesh(geometry, fillMaterial);
  mesh.renderOrder = options.renderOrder;
  mesh.scale.setScalar(options.scale);
  group.add(mesh);

  const edgeGeometry = new THREE.EdgesGeometry(geometry, 24);
  const edgeMaterial = new THREE.LineBasicMaterial({
    color: options.edgeColor,
    transparent: true,
    opacity: 0.9,
    depthWrite: false,
  });
  const edges = new THREE.LineSegments(edgeGeometry, edgeMaterial);
  edges.renderOrder = options.renderOrder + 1;
  edges.scale.copy(mesh.scale);
  group.add(edges);

  return { group, fillMaterial };
}

function makeAtlasTexture(url: string, x: number, y: number, w: number, h: number): THREE.Texture {
  const texture = new THREE.TextureLoader().load(url);
  texture.colorSpace = THREE.SRGBColorSpace;
  texture.repeat.set(w / 256, h / 64);
  texture.offset.set(x / 256, 1 - (y + h) / 64);
  return texture;
}

/**
 * Load a battle-FX sprite texture: prefers the canonical ptcl00.txg export and swaps in
 * the older hand-extracted /fx PNG of the same cell if the export fails to load.
 * Quadrant cells are mirror-wrapped (MirroredRepeatWrapping + repeat 2x2) so the bright
 * corner of the stored quadrant lands at the sprite centre, reconstructing the full
 * radial sprite exactly as the GameCube's GX WRAP_MIRROR sampling did.
 */
function loadFxTexture(source: FxTextureSource): THREE.Texture {
  const texture = new THREE.TextureLoader().load(source.url, undefined, undefined, () => {
    new THREE.ImageLoader().load(source.fallback, (image) => {
      texture.image = image;
      texture.needsUpdate = true;
    });
  });
  texture.colorSpace = THREE.SRGBColorSpace;
  if (source.quadrant) {
    texture.wrapS = THREE.MirroredRepeatWrapping;
    texture.wrapT = THREE.MirroredRepeatWrapping;
    texture.repeat.set(2, 2);
  }
  return texture;
}

/** Charge-glow tier thresholds (frames). Mirrors actionProfiles.ts defaults
 *  (chargeTier1Frames 30 / chargeTier2Frames 90); presentation-only. */
const CHARGE_GLOW_TIER1_FRAMES = 30;
const CHARGE_GLOW_TIER2_FRAMES = 90;
/** View-plane spin of the charge aura spiral (rad/s). TUNED-visual. */
const CHARGE_GLOW_SPIN_RAD_PER_S = 5.2;
