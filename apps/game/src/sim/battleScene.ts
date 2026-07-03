// BattleScene — syncs a @gf/combat Battle's BorgRuntime[] to three.js models.
//
// One three.js Group per live BorgRuntime (keyed by uid). Each frame:
//   - spawn a model for any new uid, despawn models whose uid is gone,
//   - copy pos -> position, rotY -> rotation.y,
//   - pick a baked clip from the borg's state/action and play it,
//   - advance per-borg AnimationMixers.
//
// Models + baked clips are provided by main.ts via the BorgAssets interface so we
// reuse the existing Collada loader, model normalization, and clip cache instead
// of duplicating them. Borgs without a model fall back to a simple colored capsule
// so every combatant in the sim is visible.

import * as THREE from "three";
import type { BorgRuntime, Projectile, ProjectileVisualKind } from "@gf/combat";
import {
  ARROW_MDL_BOUNDS,
  ARROW_MDL_INDICES,
  ARROW_MDL_POSITIONS,
  ARROW_MDL_SOURCE,
} from "./data/arrowMdlGeometry.generated.js";

/** Asset hooks supplied by main.ts so we reuse its loaders/caches. */
export interface BorgAssets {
  /** Resolve a cloneable source model for a borg id (cached upstream). Null if unavailable. */
  loadModel(borgId: string): Promise<THREE.Object3D | null>;
  /** Resolve a baked AnimationClip for (borgId, slot). Null if unavailable. */
  loadClip(borgId: string, slot: AnimSlot): Promise<THREE.AnimationClip | null>;
  /**
   * Optional: called exactly once per animation-slot transition (edge-triggered, same
   * pattern as the existing hit-spark VFX trigger below — NOT fired every frame and NOT
   * fired on state re-entry while already in that slot). main.ts uses this to trigger
   * combat SFX. See behavior-notes.md (v): no ROM per-action audio-event table was
   * recoverable (AnimAudioEventLookup @ 0x801a7640 is a red-herring symbol name — generic
   * nlQSort<T> plumbing, not a decoded frame/sound-id table), so slot->sound mapping here
   * is an honest TUNED placeholder, not a ROM-derived cue.
   */
  onSlotEnter?(borgId: string, slot: AnimSlot, uid: string): void;
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
  current: AnimSlot | null;
  lastSeenSlot: AnimSlot | null;
  /**
   * Alternates the melee slot between "melee" and "melee_alt" on each new melee entry so
   * borgs with several exported swing banks don't repeat the same swing every attack.
   * (melee_alt resolves to the borg's second melee-pattern bank in main.ts and falls back
   * to the plain melee bank when only one exists, so this is visual-only and fallback-safe.)
   */
  meleeParity: boolean;
  /** True once the (async) model has been attached. */
  ready: boolean;
  isPlaceholder: boolean;
  /** Charge-shot aura sprite (ptcl00.txg#7), lazily created while chargeFrames > 0. */
  chargeGlow: { sprite: THREE.Sprite; material: THREE.SpriteMaterial } | null;
}

interface ProjectileActor {
  sprite: THREE.Sprite;
  material: THREE.SpriteMaterial;
}

interface ImpactActor {
  sprite: THREE.Sprite;
  material: THREE.SpriteMaterial;
  age: number;
  ttl: number;
  startScale: THREE.Vector2;
  endScale: THREE.Vector2;
  /** Opacity at age 0 (fades linearly to 0 over ttl). */
  startOpacity: number;
  /** Optional flipbook: material.map steps through these frames over the lifetime. */
  flipbookFrames?: readonly THREE.Texture[] | undefined;
}

/** Team-tinted placeholder material colors. */
const TEAM_COLORS: Record<number, number> = { 0: 0x4cc7ff, 1: 0xff5a4d };

// ---------------------------------------------------------------------------
// Battle FX textures — the game's REAL particle art.
//
// Primary sources are the canonical HSDRaw/GXImageConverter exports of the disc's
// shared particle container ptcl00.txg (apps/game/public/ui/txg/ptcl00/image_*.png,
// see research/asset-inventory/ptcl00-txg-export-results.json) plus the efct00.tpl
// blob/ring atlas. Cell identification is documented in
// research/asset-inventory/ptcl00-cell-map.md; no ROM-side effect->texture usage
// table has been decoded (ptcl00.ptl/.ref are unparsed), so each effect->cell
// assignment below is TUNED-visual (matched by eye against battle captures), while
// the pixels themselves are real extracted assets.
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

export class BattleScene {
  private actors = new Map<string, Actor>();
  private projectileActors = new Map<string, ProjectileActor>();
  private impactActors: ImpactActor[] = [];
  private pending = new Set<string>();
  private projectileTextures = new Map<ProjectileVisualKind, THREE.Texture>();
  private impactPuffFrames: THREE.Texture[];
  private ringTexture: THREE.Texture;
  private smokeTexture: THREE.Texture;
  private hitSparkTexture: THREE.Texture;
  private dashStarTexture: THREE.Texture;
  private chargeGlowTexture: THREE.Texture;
  /** Enemy lock-on reticle (spinning ring), shown ONLY over the local player's enemy lockTarget. */
  private enemyReticle: THREE.Group;
  private enemyReticleRing: THREE.SpriteMaterial;
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
    const reticle = makeEnemyReticle();
    this.enemyReticle = reticle.group;
    this.enemyReticleRing = reticle.ringMaterial;
    this.root.add(this.enemyReticle);
    this.allyMarker = makeAllyMarker();
    this.root.add(this.allyMarker);
  }

  /** Map a sim state/action to one of the exported game animation groups. */
  private slotForBorg(b: BorgRuntime): AnimSlot {
    if ((b.cooldowns["dashActive"] ?? 0) > 0) return dashSlotForBorg(b);
    if (b.state === "death") return "death";
    if (b.state === "down") return "down";
    if (b.state === "hit") return "hit";
    if (b.state === "spawn") return "spawn";
    if (b.state === "special") return "special";
    if (b.state === "attack") {
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
    borgs: readonly BorgRuntime[],
    projectiles: readonly Projectile[] = [],
    localActiveUid: string | null = null,
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
      if (slot === "hit" && slotChanged) this.spawnHitSpark(actor.group.position);
      // Edge-triggered battle FX (same pattern as the hit spark above).
      if (slot === "death" && slotChanged) this.spawnDeathExplosion(actor.group.position);
      if (slotChanged && slot.startsWith("dash")) this.spawnDashBurst(actor.group.position);
      if (slot === "shoot" && slotChanged) this.spawnMuzzleFlash(actor.group.position, b.rotY);
      this.syncChargeGlow(actor, b);
      if (slotChanged) this.assets.onSlotEnter?.(actor.borgId, slot, b.uid);
      actor.lastSeenSlot = slot;
      if (actor.ready) this.playSlot(actor, slot);
      // Dim/hide once dead so the death pose reads (sim culls dead borgs next frame).
      if (!b.alive) actor.group.visible = true;
    }
    // Despawn actors whose borg is gone.
    for (const [uid, actor] of this.actors) {
      if (!live.has(uid)) {
        actor.chargeGlow?.material.dispose();
        this.root.remove(actor.group);
        this.actors.delete(uid);
      }
    }
    this.syncLockMarkers(borgs, localActiveUid);
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
      // Continuous screen-plane spin, matching the original's rotating lock ring
      // (reference/captures/challenge-8-in-battle-hud.png). Sprite rotation = view-plane roll.
      this.enemyReticleRing.rotation -= dt * ENEMY_RETICLE_SPIN_RAD_PER_S;
    }
    if (this.allyMarker.visible) {
      this.allyMarker.rotation.y += dt * ALLY_MARKER_SPIN_RAD_PER_S;
    }
    this.updateImpacts(dt);
  }

  /** Remove every actor (call when leaving a battle). */
  clear(): void {
    for (const actor of this.actors.values()) {
      actor.chargeGlow?.material.dispose();
      this.root.remove(actor.group);
    }
    for (const actor of this.projectileActors.values()) this.disposeProjectileActor(actor);
    for (const actor of this.impactActors) this.disposeImpactActor(actor);
    this.actors.clear();
    this.projectileActors.clear();
    this.impactActors = [];
    this.pending.clear();
    this.enemyReticle.visible = false;
    this.allyMarker.visible = false;
  }

  /** World position of an actor (for the camera to follow). */
  positionOf(uid: string): THREE.Vector3 | null {
    return this.actors.get(uid)?.group.position ?? null;
  }

  private spawn(b: BorgRuntime): Actor {
    const group = new THREE.Group();
    group.position.set(b.pos.x, b.pos.y, b.pos.z);
    group.rotation.y = b.rotY;
    // Start with a placeholder so the borg is visible immediately; swap in the
    // real model when it finishes loading.
    const placeholder = this.makePlaceholder(b.team);
    group.add(placeholder);
    this.root.add(group);
    const actor: Actor = {
      group,
      borgId: b.borgId,
      mixer: null,
      actions: {},
      current: null,
      lastSeenSlot: null,
      meleeParity: true, // first melee entry flips this to false => plain "melee" first
      ready: false,
      isPlaceholder: true,
      chargeGlow: null,
    };
    void this.attachModel(b.uid, actor, b.borgId, placeholder);
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
  private syncLockMarkers(borgs: readonly BorgRuntime[], localActiveUid: string | null): void {
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
    const model = await this.assets.loadModel(borgId).catch(() => null);
    // The actor may have been despawned while loading.
    if (!this.actors.has(uid)) return;
    if (model) {
      actor.group.remove(placeholder);
      disposeMesh(placeholder);
      actor.group.add(model);
      actor.mixer = new THREE.AnimationMixer(model);
      actor.current = null;
      actor.isPlaceholder = false;
    }
    actor.ready = true;
  }

  private playSlot(actor: Actor, slot: AnimSlot): void {
    if (actor.current === slot) return;
    if (!actor.mixer) {
      return; // placeholder has no animation
    }
    actor.current = slot;
    const existing = actor.actions[slot];
    if (existing) {
      this.crossfadeTo(actor, existing, slot);
      return;
    }
    // Lazily load the clip; apply when ready if still current.
    void this.assets.loadClip(actor.borgId, slot).then((clip) => {
      if (!actor.mixer || actor.current !== slot) return;
      // Fall back to idle clip if the requested slot has no baked clip.
      const useClip = clip ?? (slot !== "idle" ? null : null);
      const finalClip = useClip ?? clip;
      if (!finalClip) {
        // No clip for this slot; try idle as a fallback.
        if (slot !== "idle") {
          void this.assets.loadClip(actor.borgId, "idle").then((idle) => {
            if (!actor.mixer || actor.current !== slot || !idle) return;
            const a = actor.mixer.clipAction(idle);
            actor.actions[slot] = a;
            this.crossfadeTo(actor, a, slot);
          });
        }
        return;
      }
      const action = actor.mixer.clipAction(finalClip);
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
    // Fade out any other playing action.
    for (const [s, a] of Object.entries(actor.actions)) {
      if (s !== slot && a.isRunning()) a.crossFadeTo(action, 0.18, false);
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
      actor.sprite.position.set(projectile.pos.x, projectile.pos.y, projectile.pos.z);
      actor.material.opacity = Math.max(0.35, Math.min(1, projectile.life / 12));
    }

    for (const [uid, actor] of this.projectileActors) {
      if (!live.has(uid)) {
        this.spawnImpact(actor.sprite.position);
        this.disposeProjectileActor(actor);
        this.projectileActors.delete(uid);
      }
    }
  }

  private spawnProjectile(projectile: Projectile): ProjectileActor {
    const kind = projectile.visualKind;
    const colors = PROJECTILE_COLORS[kind];
    const material = new THREE.SpriteMaterial({
      map: this.projectileTextures.get(kind),
      color: projectile.team === 0 ? colors.ally : colors.enemy,
      transparent: true,
      opacity: 1,
      blending: THREE.AdditiveBlending,
      depthWrite: false,
    });
    const sprite = new THREE.Sprite(material);
    sprite.position.set(projectile.pos.x, projectile.pos.y, projectile.pos.z);
    sprite.scale.setScalar(Math.max(42, projectile.hitRadius * 1.8));
    this.root.add(sprite);
    return { sprite, material };
  }

  private disposeProjectileActor(actor: ProjectileActor): void {
    this.root.remove(actor.sprite);
    actor.material.dispose();
  }

  /** Shared short-lived FX sprite: expands from startScale to endScale while fading out. */
  private spawnBurstSprite(
    map: THREE.Texture | null,
    position: THREE.Vector3,
    opts: {
      ttl: number;
      startScale: number;
      endScale: number;
      opacity: number;
      blending?: THREE.Blending;
      color?: number;
      flipbookFrames?: readonly THREE.Texture[];
    },
  ): void {
    if (!map) return;
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
    sprite.scale.set(opts.startScale, opts.startScale, 1);
    this.root.add(sprite);
    this.impactActors.push({
      sprite,
      material,
      age: 0,
      ttl: opts.ttl,
      startScale: new THREE.Vector2(opts.startScale, opts.startScale),
      endScale: new THREE.Vector2(opts.endScale, opts.endScale),
      startOpacity: opts.opacity,
      flipbookFrames: opts.flipbookFrames,
    });
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

  /** Hit spark: ptcl00.txg#2 white-hot ember quadrant, mirror-wrapped to a radial flash. */
  private spawnHitSpark(position: THREE.Vector3): void {
    this.spawnBurstSprite(this.hitSparkTexture, new THREE.Vector3(position.x, position.y + 82, position.z), {
      ttl: 0.16,
      startScale: 34,
      endScale: 58,
      opacity: 1,
      blending: THREE.AdditiveBlending,
    });
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
   * Muzzle flash: ptcl00.txg#6 ray-burst quadrant at the borg's gun height, offset along
   * facing. No per-borg muzzle node is decoded yet, so the offset is TUNED (forward =
   * (sin rotY, cos rotY), same convention as dashSlotForBorg).
   */
  private spawnMuzzleFlash(position: THREE.Vector3, rotY: number): void {
    const at = new THREE.Vector3(
      position.x + Math.sin(rotY) * 46,
      position.y + 86,
      position.z + Math.cos(rotY) * 46,
    );
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
   * not visible from BorgRuntime (read-only cooldowns is all the sim exposes).
   */
  private syncChargeGlow(actor: Actor, b: BorgRuntime): void {
    const frames = b.cooldowns["chargeFrames"] ?? 0;
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

  private updateImpacts(dt: number): void {
    for (let i = this.impactActors.length - 1; i >= 0; i--) {
      const actor = this.impactActors[i];
      if (!actor) continue;
      actor.age += dt;
      const t = Math.min(1, actor.age / actor.ttl);
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
  }

  private disposeImpactActor(actor: ImpactActor): void {
    this.root.remove(actor.sprite);
    actor.material.dispose();
  }
}

function dashSlotForBorg(b: BorgRuntime): AnimSlot {
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

/** Spin speed of the enemy lock ring (view-plane, rad/s). TUNED to read like the original's
 *  steadily rotating ring in reference/captures/challenge-8-in-battle-hud.png. */
const ENEMY_RETICLE_SPIN_RAD_PER_S = 2.6;
/** Slow yaw spin of the green ally arrow (rad/s). TUNED, presentation only. */
const ALLY_MARKER_SPIN_RAD_PER_S = 2.2;
/** World size of the enemy reticle sprites (borgs are ~120-150 units tall). */
const ENEMY_RETICLE_WORLD_SIZE = 210;

/**
 * Enemy lock-on reticle: a camera-facing red-orange ring with four lugs (drawn on the spinning
 * sprite) plus four static inward-pointing blue triangles, reproducing the original battle
 * reticle in reference/captures/challenge-8-in-battle-hud.png. No extracted texture/model for
 * the original reticle exists in the exported assets yet (ui/manifest.json has no lock/reticle
 * entry), so the two canvas textures are a TUNED visual stand-in transcribed from that capture.
 * ENEMY-ONLY by contract: syncLockMarkers never positions this over a same-team borg.
 */
function makeEnemyReticle(): { group: THREE.Group; ringMaterial: THREE.SpriteMaterial } {
  const group = new THREE.Group();
  group.visible = false;

  const ringMaterial = new THREE.SpriteMaterial({
    map: drawReticleRingTexture(),
    transparent: true,
    depthTest: false, // the original ring reads as a HUD overlay: never hidden by stage geometry
    depthWrite: false,
  });
  const ring = new THREE.Sprite(ringMaterial);
  ring.scale.setScalar(ENEMY_RETICLE_WORLD_SIZE);
  ring.renderOrder = 30;
  group.add(ring);

  const trianglesMaterial = new THREE.SpriteMaterial({
    map: drawReticleTrianglesTexture(),
    transparent: true,
    depthTest: false,
    depthWrite: false,
  });
  const triangles = new THREE.Sprite(trianglesMaterial);
  triangles.scale.setScalar(ENEMY_RETICLE_WORLD_SIZE);
  triangles.renderOrder = 31;
  group.add(triangles);

  return { group, ringMaterial };
}

/** Red-orange ring + 4 lugs with a white outline (the spinning layer of the reticle). */
function drawReticleRingTexture(): THREE.CanvasTexture {
  const size = 256;
  const canvas = document.createElement("canvas");
  canvas.width = size;
  canvas.height = size;
  const ctx = canvas.getContext("2d");
  if (ctx) {
    const c = size / 2;
    const radius = 88;
    // White underlay ring, then the red ring on top -> white outline on both edges.
    ctx.beginPath();
    ctx.arc(c, c, radius, 0, Math.PI * 2);
    ctx.strokeStyle = "#ffffff";
    ctx.lineWidth = 30;
    ctx.stroke();
    ctx.beginPath();
    ctx.arc(c, c, radius, 0, Math.PI * 2);
    ctx.strokeStyle = "#ff3c14";
    ctx.lineWidth = 18;
    ctx.stroke();
    // Four lugs riding the ring (their off-axis placement makes the spin visible).
    for (let i = 0; i < 4; i++) {
      const a = (i / 4) * Math.PI * 2 + Math.PI / 12;
      const x = c + Math.cos(a) * radius;
      const y = c + Math.sin(a) * radius;
      ctx.save();
      ctx.translate(x, y);
      ctx.rotate(a);
      ctx.fillStyle = "#ffffff";
      ctx.fillRect(-17, -17, 34, 34);
      ctx.fillStyle = "#ff3c14";
      ctx.fillRect(-12, -12, 24, 24);
      ctx.restore();
    }
  }
  const texture = new THREE.CanvasTexture(canvas);
  texture.colorSpace = THREE.SRGBColorSpace;
  return texture;
}

/** Four static blue triangles pointing inward at the locked enemy. */
function drawReticleTrianglesTexture(): THREE.CanvasTexture {
  const size = 256;
  const canvas = document.createElement("canvas");
  canvas.width = size;
  canvas.height = size;
  const ctx = canvas.getContext("2d");
  if (ctx) {
    const c = size / 2;
    for (let i = 0; i < 4; i++) {
      const a = (i / 4) * Math.PI * 2 + Math.PI / 4;
      ctx.save();
      ctx.translate(c + Math.cos(a) * 56, c + Math.sin(a) * 56);
      ctx.rotate(a + Math.PI / 2); // tip toward the center
      ctx.beginPath();
      ctx.moveTo(0, -18);
      ctx.lineTo(14, 12);
      ctx.lineTo(-14, 12);
      ctx.closePath();
      ctx.fillStyle = "#2f6bff";
      ctx.strokeStyle = "#ffffff";
      ctx.lineWidth = 4;
      ctx.fill();
      ctx.stroke();
      ctx.restore();
    }
  }
  const texture = new THREE.CanvasTexture(canvas);
  texture.colorSpace = THREE.SRGBColorSpace;
  return texture;
}

/**
 * Ally lock-on (Z) marker: the extracted arrow_mdl geometry tinted GREEN, floating overhead.
 * Deliberately a different shape (3D arrow vs billboard ring) AND color (green vs red) than
 * the enemy reticle so the two lock indicators can never be mistaken for each other.
 */
function makeAllyMarker(): THREE.Group {
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

  // arrow_mdl.arc has geometry but no decoded texture; colors are a tuned stand-in
  // for the original runtime vertex colors until the GX material block is decoded.
  const fill = new THREE.MeshBasicMaterial({
    color: 0x35d977,
    transparent: true,
    opacity: 0.74,
    side: THREE.DoubleSide,
    depthWrite: false,
  });
  const mesh = new THREE.Mesh(geometry, fill);
  mesh.renderOrder = 25;
  mesh.scale.setScalar(44);
  group.add(mesh);

  const edgeGeometry = new THREE.EdgesGeometry(geometry, 24);
  const edgeMaterial = new THREE.LineBasicMaterial({
    color: 0xeafff2,
    transparent: true,
    opacity: 0.9,
    depthWrite: false,
  });
  const edges = new THREE.LineSegments(edgeGeometry, edgeMaterial);
  edges.renderOrder = 26;
  edges.scale.copy(mesh.scale);
  group.add(edges);

  return group;
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
