import * as THREE from "three";
import { BattleScene, type BorgAssets } from "./battleScene.js";
import type { BattleActorView } from "./battleView.js";

function assert(ok: unknown, message: string): asserts ok {
  if (!ok) throw new Error(`source animation playhead selfcheck: ${message}`);
}

function near(actual: number, expected: number, message: string): void {
  assert(Math.abs(actual - expected) < 1e-6, `${message}: ${actual} != ${expected}`);
}

function view(serial: number, frame: number, borgId = "pl0629", slot = 3): BattleActorView {
  return {
    uid: "source-actor", borgId, combatFormId: undefined, team: 0, ownerPlayer: "p1",
    alive: true, state: "special", anim: "special", pos: { x: 0, y: 0, z: 0 },
    vel: { x: 0, y: 0, z: 0 }, rotY: 0, modelSizeScale: 1, lockTarget: null, allyLockTarget: null,
    dashActiveFrames: 0, chargeFrames: 0, meleeAnimStream: { group: slot === 3 ? 4 : 0, slot },
    sourceAnimSample: { serial, frame }, meleeSounds: null,
    lastHitImpactEffectId: undefined, lastHitAttackerTeam: undefined, slowHitTimer: 0, hasteHitTimer: 0,
    romAfterimage: undefined,
  };
}

// Match buildClip's dense per-frame tracks, with synthetic values and no original assets.
function clip(name: string, fps = 60, frameCount = 81): THREE.AnimationClip {
  const times = Float32Array.from({ length: frameCount }, (_, frame) => frame / fps);
  const values = Float32Array.from({ length: frameCount }, (_, frame) => frame);
  return new THREE.AnimationClip(name, frameCount / fps, [
    new THREE.NumberKeyframeTrack("JOBJ_1.position[x]", times, values),
  ]);
}

function model(): THREE.Group {
  const result = new THREE.Group();
  const bone = new THREE.Group(); bone.name = "JOBJ_1"; result.add(bone);
  return result;
}

type ActorState = {
  model: THREE.Object3D | null;
  mixer: THREE.AnimationMixer | null;
  actions: Record<string, THREE.AnimationAction>;
  streamActions: Record<string, THREE.AnimationAction>;
  sourceAnimSample: BattleActorView["sourceAnimSample"];
  sourceAnimAction: THREE.AnimationAction | null;
};

function actors(scene: BattleScene): Map<string, ActorState> {
  return (scene as unknown as { actors: Map<string, ActorState> }).actors;
}

function actor(scene: BattleScene): ActorState {
  const result = actors(scene).get("source-actor");
  assert(result, "source actor exists");
  return result;
}

const flush = async (): Promise<void> => { await Promise.resolve(); await Promise.resolve(); };

async function enter(scene: BattleScene, frame: BattleActorView): Promise<void> {
  scene.sync([frame]); await flush(); scene.sync([frame]); await flush();
}

/** Real mixers, cached actions and deferred clip I/O. No browser or original asset data. */
export async function runSourceAnimationPlayheadSelfcheck(): Promise<void> {
  const originalLoad = THREE.TextureLoader.prototype.load;
  THREE.TextureLoader.prototype.load = function load(): THREE.Texture { return new THREE.Texture(); };
  const scenes: BattleScene[] = [];
  const create = (assets: BorgAssets): BattleScene => {
    const scene = new BattleScene(new THREE.Group(), assets); scenes.push(scene); return scene;
  };
  try {
    // Neutral-combo and family airborne B refs after the metadata hop. Synthetic clips
    // test pose ownership, not original asset fidelity or crossfade equivalence.
    for (const [id, slots] of [
      ["pl0615", [1, 2, 16, 23]], ["pl0629", [1, 2, 19, 20, 21, 22]], ["pl062a", [25, 5, 24, 22]],
    ] as const) {
      const scene = create({
        async loadModel() { return model(); },
        async loadClip() { return clip("generic"); },
        async loadClipByStreamRef(_id, ref) { return clip(`g${ref.group}s${ref.slot}`); },
      });
      let serial = 100;
      for (const slot of slots) {
        const sample = { ...view(serial++, 0, id), meleeAnimStream: { group: 1, slot } };
        await enter(scene, sample);
        const action = actor(scene).sourceAnimAction;
        assert(action?.paused && action.getClip().name === `g1s${slot}`, `${id}: combo clip source-owned`);
        scene.update(0.4);
        near(action.time, 0, `${id}/${slot}: startup hold does not render-run`);
        scene.sync([{ ...sample, sourceAnimSample: { serial: serial - 1, frame: 3.5 } }]);
        near(action.time, 3.5 / 60, `${id}/${slot}: fractional source advance`);
        scene.update(0.2);
        near(action.time, 3.5 / 60, `${id}/${slot}: source remains authoritative between ticks`);
      }
      scene.clear();
    }

    // Ordinary B opcode0d uses its grounded and airborne-fallback middle clips.
    // This checks source clock ownership, not the unimplemented side-clip blend.
    for (const id of ["pl0615", "pl0629", "pl062a"]) {
      const scene = create({
        async loadModel() { return model(); },
        async loadClip() { return clip("generic"); },
        async loadClipByStreamRef(_id, ref) { return clip(`g${ref.group}s${ref.slot}`, 60, ref.slot === 0 || ref.slot === 5 ? 12 : ref.slot === 16 ? 16 : 36); },
      });
      let serial = 300;
      for (const slot of [0, 11, 5, 16]) {
        const sample: BattleActorView = { ...view(serial++, 0, id), state: "attack", anim: "charge_shot", meleeAnimStream: { group: 3, slot } };
        await enter(scene, sample);
        const action = actor(scene).sourceAnimAction;
        assert(action?.paused && action.getClip().name === `g3s${slot}`, `${id}: ordinary B center clip source-owned`);
        scene.sync([{ ...sample, sourceAnimSample: { serial: serial - 1, frame: 4 } }]);
        scene.update(0.5);
        near(action.time, 4 / 60, `${id}/${slot}: ordinary shot hold cannot render-run`);
      }
      scene.clear();
    }

    // Charged B keeps its actual charge_shot label while all three exact source
    // clips remain seekable, including the authored pause and recovery reset.
    for (const id of ["pl0615", "pl0629", "pl062a"]) {
      const scene = create({
        async loadModel() { return model(); },
        async loadClip() { return clip("generic"); },
        async loadClipByStreamRef(_id, ref) { return clip(`g${ref.group}s${ref.slot}`, 60, ref.group === 0 ? 2 : id === "pl062a" ? 39 : 26); },
      });
      let serial = 200;
      const refs = id === "pl062a" ? [[4, 2, 19], [0, 24, 0]] as const
        : [[4, 1, 10], [4, 4, 3], [0, 24, 0]] as const;
      for (const [group, slot, heldFrame] of refs) {
        const sample: BattleActorView = { ...view(serial++, 0, id), state: "attack", anim: "charge_shot", meleeAnimStream: { group, slot } };
        await enter(scene, sample);
        const action = actor(scene).sourceAnimAction;
        assert(action?.paused && action.getClip().name === `g${group}s${slot}`, `${id}: charged B clip source-owned`);
        near(action.time, 0, "charge clip transition starts at zero");
        scene.sync([{ ...sample, sourceAnimSample: { serial: serial - 1, frame: heldFrame } }]);
        scene.update(0.5);
        near(action.time, heldFrame / 60, "charge pause cannot render-run");
      }
      scene.clear();
    }

    // All admitted actors, plus a non-60 Hz bake to reject assumed frame conversion.
    for (const [id, fps, start] of [
      ["pl0615", 60, 0], ["pl0629", 60, 36], ["pl062a", 60, 36], ["pl0629", 30, 36],
    ] as const) {
      let requests = 0;
      const scene = create({
        async loadModel() { return model(); },
        async loadClip() { return clip("generic", fps); },
        async loadClipByStreamRef(_id, ref) {
          requests += 1;
          return clip(`g${ref.group}s${ref.slot}`, fps, ref.slot === 24 ? 2 : 81);
        },
      });
      await enter(scene, view(1, start, id));
      const current = actor(scene);
      const action = current.sourceAnimAction;
      assert(action?.paused, `${id}/${fps}: exact action is source-owned`);
      near(action.time, start / fps, `${id}/${fps}: source start frame`);
      near(current.model!.getObjectByName("JOBJ_1")!.position.x, start, "source pose evaluated on load");
      for (let i = 0; i < 16; i += 1) {
        scene.sync([view(1, start, id)]); scene.update(0.2);
        near(action.time, start / fps, "start hold cannot drift with render delta");
      }
      scene.sync([view(1, 40.5, id)]);
      near(action.time, 40.5 / fps, "sim frame, including fractional frame, seeks cached action");
      near(current.model!.getObjectByName("JOBJ_1")!.position.x, 40.5, "sim pose is evaluated without render time");
      scene.sync([view(1, 63, id)]);
      for (let i = 0; i < 9; i += 1) {
        scene.update(0.1); near(action.time, 63 / fps, "mode-8 frame-63 hold");
      }
      scene.update(0); scene.update(0);
      near(action.time, 63 / fps, "paused app updates retain source frame");
      near(current.model!.getObjectByName("JOBJ_1")!.position.x, 63, "held displayed pose");
      scene.sync([view(2, start, id)]);
      assert(current.sourceAnimAction === action && requests === 1, "new epoch reuses cached exact action");
      near(action.time, start / fps, "same-clip new epoch resets to new source start");

      // The bridge's resolved export for source recovery metadata g0s14 is g0s24.
      scene.sync([view(3, 0, id, 24)]); await flush();
      const recovery = current.sourceAnimAction;
      assert(recovery?.getClip().name === "g0s24" && recovery.paused, "exact recovery is source-owned");
      near(recovery.time, 0, "recovery starts at frame zero");
      scene.update(0.5); near(recovery.time, 0, "recovery cannot render-run while source holds");
      scene.sync([view(3, 20, id, 24)]);
      near(recovery.time, 1 / fps, "source sampling clamps to last available baked pose");

      // Clearing ownership on the SAME exact clip must undo source pause as well.
      scene.sync([{ ...view(3, 0, id, 24), sourceAnimSample: null }]);
      assert(current.sourceAnimAction === null && !recovery.paused, "clear restores ordinary exact-clip playback");
      scene.update(0.005); near(recovery.time, 0.005, "ordinary exact action advances independently again");
      scene.sync([view(4, start, id)]);
      near(action.time, start / fps, "cached source action seeks after recovery");
      scene.sync([{ ...view(4, 63, id), state: "idle", anim: "idle", sourceAnimSample: null, meleeAnimStream: null }]);
      await flush();
      assert(current.sourceAnimAction === null && current.sourceAnimSample === null, "interruption releases source ownership");
      const idle = current.actions.idle!;
      scene.update(0.1); near(idle.time, 0.1, "generic idle retains ordinary mixer playback");
      scene.clear();
      assert(current.sourceAnimAction === null && current.sourceAnimSample === null && current.mixer === null,
        "cleanup drops source state and mixer references");
    }

    // Source facts are never applied to an approximate label fallback.
    for (const exactLoader of ["missing", "unavailable"] as const) {
      const assets: BorgAssets = {
        async loadModel() { return model(); },
        async loadClip() { return clip("heuristic"); },
      };
      if (exactLoader === "missing") assets.loadClipByStreamRef = async () => null;
      const scene = create(assets);
      await enter(scene, view(10, 36)); await flush();
      const current = actor(scene);
      const fallback = current.actions.special!;
      assert(fallback && !fallback.paused && current.sourceAnimAction === null, "heuristic fallback never gains source ownership");
      scene.update(0.1); near(fallback.time, 0.1, "heuristic fallback remains ordinary playback");
      scene.sync([view(10, 63)]); near(fallback.time, 0.1, "source sample cannot seek fallback");
      scene.clear();
    }

    type Pending = { id: string; ref: string; resolve: (value: THREE.AnimationClip | null) => void };
    const pending: Pending[] = [];
    let labelRequests = 0;
    const scene = create({
      async loadModel() { return model(); },
      async loadClip() { labelRequests += 1; return clip("fallback"); },
      loadClipByStreamRef(id, ref) {
        return new Promise(resolve => pending.push({ id, ref: `g${ref.group}s${ref.slot}`, resolve }));
      },
    });
    await enter(scene, view(20, 36));
    const first = pending[0]!;
    scene.sync([view(20, 45)]);
    first.resolve(clip("delayed-latest")); await flush();
    near(actor(scene).sourceAnimAction!.time, 45 / 60, "delayed completion uses latest source sample");

    // Discard uncached previous epochs, including null completions that would start fallback I/O.
    scene.clear(); pending.length = 0;
    await enter(scene, view(21, 36));
    scene.sync([view(22, 36)]);
    scene.sync([view(22, 48)]);
    assert(pending.length === 2, "same-clip new epoch has an independent pending request");
    const activeMixer = actor(scene).mixer!;
    pending[0]!.resolve(null); await flush();
    assert(labelRequests === 0 && actor(scene).sourceAnimAction === null, "stale epoch cannot load fallback or bind action");
    const latest = clip("latest-epoch");
    pending[1]!.resolve(latest); await flush();
    near(actor(scene).sourceAnimAction!.time, 48 / 60, "new epoch uses latest frame rather than initial callback frame");

    // Resolve an old SAME-stream epoch after its replacement is already displayed.
    scene.sync([view(26, 0, "pl0629", 24)]);
    const lateEpoch = pending[pending.length - 1]!;
    scene.sync([view(27, 0, "pl0629", 24)]);
    const replacement = clip("same-stream-new-epoch", 60, 2);
    pending[pending.length - 1]!.resolve(replacement); await flush();
    const oldEpochClip = clip("same-stream-old-epoch", 60, 2);
    lateEpoch.resolve(oldEpochClip); await flush();
    assert(!activeMixer.existingAction(oldEpochClip) && actor(scene).sourceAnimAction!.getClip() === replacement,
      "late same-stream prior epoch cannot overwrite an already displayed replacement");

    scene.sync([view(23, 0, "pl0629", 14)]);
    const previousClip = pending[pending.length - 1]!;
    scene.sync([view(24, 36)]);
    const staleClip = clip("stale-other-stream"); previousClip.resolve(staleClip); await flush();
    assert(!activeMixer.existingAction(staleClip), "stale different-stream completion never binds");
    near(actor(scene).sourceAnimAction!.time, 36 / 60, "stale different stream cannot replace cached current source action");

    // Source -> generic -> same source identity also changes the local animation epoch.
    scene.sync([view(25, 0, "pl0629", 14)]);
    const interrupted = pending[pending.length - 1]!;
    scene.sync([{ ...view(25, 0), state: "idle", anim: "idle", meleeAnimStream: null, sourceAnimSample: null }]);
    await flush();
    const staleInterrupted = clip("stale-interrupted"); interrupted.resolve(staleInterrupted); await flush();
    assert(!activeMixer.existingAction(staleInterrupted) && actor(scene).sourceAnimAction === null,
      "interruption invalidates outstanding source clip completion");

    // Same-clip old form completions and retired actors must never gain source ownership.
    for (const lifetime of ["morph", "morph-back", "despawn", "clear"] as const) {
      scene.clear(); pending.length = 0;
      await enter(scene, view(30, 36));
      const before = actor(scene); const oldMixer = before.mixer!; const stale = pending[0]!;
      let nextView = view(31, 40);
      if (lifetime === "morph" || lifetime === "morph-back") {
        nextView = { ...nextView, combatFormId: "pl062a" }; await enter(scene, nextView);
        if (lifetime === "morph-back") { nextView = view(32, 42); await enter(scene, nextView); }
      } else {
        if (lifetime === "despawn") scene.sync([]); else scene.clear();
        await enter(scene, nextView);
      }
      const current = actor(scene); const fresh = pending[pending.length - 1]!;
      assert(current.mixer !== oldMixer, `${lifetime}: new presentation mixer`);
      const late = clip(`${lifetime}-stale`); stale.resolve(late); await flush();
      assert(!oldMixer.existingAction(late) && !current.mixer!.existingAction(late), `${lifetime}: stale completion cannot bind`);
      assert(current.sourceAnimAction === null, `${lifetime}: stale completion cannot take source ownership`);
      const next = clip(`${lifetime}-fresh`); fresh.resolve(next); await flush();
      const freshAction = actor(scene).sourceAnimAction;
      assert(freshAction?.getClip() === next, `${lifetime}: fresh completion owns source action`);
      near(freshAction.time, nextView.sourceAnimSample!.frame / 60, `${lifetime}: current frame applied`);
      scene.clear();
      assert(current.sourceAnimSample === null && current.sourceAnimAction === null
        && current.mixer === null && Object.keys(current.streamActions).length === 0, `${lifetime}: cleanup releases ownership`);
    }
  } finally {
    for (const scene of scenes) scene.clear();
    THREE.TextureLoader.prototype.load = originalLoad;
  }
  console.log("source animation playhead selfcheck: source holds, cached epochs, fallback, async races and cleanup PASS");
}
