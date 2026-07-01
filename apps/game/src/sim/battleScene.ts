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

/** Asset hooks supplied by main.ts so we reuse its loaders/caches. */
export interface BorgAssets {
  /** Resolve a cloneable source model for a borg id (cached upstream). Null if unavailable. */
  loadModel(borgId: string): Promise<THREE.Object3D | null>;
  /** Resolve a baked AnimationClip for (borgId, slot). Null if unavailable. */
  loadClip(borgId: string, slot: AnimSlot): Promise<THREE.AnimationClip | null>;
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
  | "fly"
  | "attack"
  | "melee"
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
  /** True once the (async) model has been attached. */
  ready: boolean;
  isPlaceholder: boolean;
}

interface ProjectileActor {
  sprite: THREE.Sprite;
  material: THREE.SpriteMaterial;
}

/** Team-tinted placeholder material colors. */
const TEAM_COLORS: Record<number, number> = { 0: 0x4cc7ff, 1: 0xff5a4d };
const PROJECTILE_TEXTURE_URLS: Record<ProjectileVisualKind, string> = {
  energy: "/fx/energy_dot.png", // ptcl00.txg#5, exported original particle.
  flame: "/fx/flame_core.png", // ptcl00.txg#1, exported flame/explosion core.
  muzzle: "/fx/muzzle_flash.png", // ptcl00.txg#6, exported muzzle flare.
};
const PROJECTILE_COLORS: Record<ProjectileVisualKind, { ally: number; enemy: number }> = {
  energy: { ally: 0x91eaff, enemy: 0xff7a4d },
  flame: { ally: 0xffd36a, enemy: 0xff5a2e },
  muzzle: { ally: 0xfff1a8, enemy: 0xffb14a },
};

export class BattleScene {
  private actors = new Map<string, Actor>();
  private projectileActors = new Map<string, ProjectileActor>();
  private pending = new Set<string>();
  private projectileTextures = new Map<ProjectileVisualKind, THREE.Texture>();

  constructor(
    private readonly root: THREE.Group,
    private readonly assets: BorgAssets,
  ) {
    for (const kind of Object.keys(PROJECTILE_TEXTURE_URLS) as ProjectileVisualKind[]) {
      const texture = new THREE.TextureLoader().load(PROJECTILE_TEXTURE_URLS[kind]);
      texture.colorSpace = THREE.SRGBColorSpace;
      this.projectileTextures.set(kind, texture);
    }
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
    if (b.state === "jump") return "jump";
    if (b.state === "move") return "move";
    return "idle";
  }

  /** Reconcile the scene with the current list of live borgs. Call once per frame. */
  sync(borgs: readonly BorgRuntime[], projectiles: readonly Projectile[] = []): void {
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
      const slot = this.slotForBorg(b);
      if (actor.ready) this.playSlot(actor, slot);
      // Dim/hide once dead so the death pose reads (sim culls dead borgs next frame).
      if (!b.alive) actor.group.visible = true;
    }
    // Despawn actors whose borg is gone.
    for (const [uid, actor] of this.actors) {
      if (!live.has(uid)) {
        this.root.remove(actor.group);
        this.actors.delete(uid);
      }
    }
    this.syncProjectiles(projectiles);
  }

  /** Advance all per-actor animation mixers. */
  update(dt: number): void {
    for (const actor of this.actors.values()) actor.mixer?.update(dt);
  }

  /** Remove every actor (call when leaving a battle). */
  clear(): void {
    for (const actor of this.actors.values()) this.root.remove(actor.group);
    for (const actor of this.projectileActors.values()) this.disposeProjectileActor(actor);
    this.actors.clear();
    this.projectileActors.clear();
    this.pending.clear();
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
      ready: false,
      isPlaceholder: true,
    };
    void this.attachModel(b.uid, actor, b.borgId, placeholder);
    return actor;
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
