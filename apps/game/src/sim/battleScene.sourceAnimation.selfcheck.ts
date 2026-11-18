import * as THREE from "three";
import { attachSourceDrawPart } from "./sourceDrawPart.js";
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
  sourceDrawParts: THREE.Group[] | null;
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
    // The martial B route must request its stream clip, not generic attack fallback.
    for (const id of ["pl0800", "pl0801"]) {
      const requests: string[] = [];
      const scene = create({
        async loadModel() { return model(); },
        async loadClip() { return clip("fallback"); },
        async loadClipByStreamRef(borg, ref) { requests.push(`${borg}:g${ref.group}s${ref.slot}`); return clip("source-melee"); },
      });
      const melee: BattleActorView = { ...view(0, 0, id), state: "attack", anim: "melee",
        meleeAnimStream: { group: 3, slot: 1 }, sourceAnimSample: undefined };
      await enter(scene, melee);
      assert(requests.includes(`${id}:g3s1`), `${id} melee lane requests its source stream clip`);
      scene.clear();
    }
    // The source exporter bakes the part root's bind matrix into mesh coordinates.
    // Synthetic points prove the inverse is applied once and follows the target.
    {
      const target = new THREE.Group(); target.position.set(10, 20, 0);
      const part = new THREE.Group(); const bind = new THREE.Group(); bind.name = 'JOBJ_0'; bind.position.set(5, 2, 0);
      const vertex = new THREE.Object3D(); vertex.position.set(7, 3, 0); part.add(bind, vertex);
      const attached = attachSourceDrawPart(target, part); target.updateMatrixWorld(true);
      const world = new THREE.Vector3(); vertex.getWorldPosition(world);
      near(world.x, 12, 'attachment removes exported bind translation');
      near(world.y, 21, 'attachment keeps local geometry offset');
      target.position.x = 30; target.updateMatrixWorld(true); vertex.getWorldPosition(world);
      near(world.x, 32, 'attachment follows animated target');
      target.rotation.z = Math.PI / 2; target.updateMatrixWorld(true); vertex.getWorldPosition(world);
      near(world.x, 29, 'attachment follows target rotation x');
      near(world.y, 22, 'attachment follows target rotation y');
      target.remove(attached);
      const invalid = new THREE.Group();
      let refused = false; try { attachSourceDrawPart(target, invalid); } catch { refused = true; }
      assert(refused && invalid.parent === null, 'invalid part is rejected without reparenting');
      const singular = new THREE.Group(), root = new THREE.Group(); root.name = 'JOBJ_0'; root.scale.x = 0; singular.add(root);
      refused = false; try { attachSourceDrawPart(target, singular); } catch { refused = true; }
      assert(refused && singular.parent === null, 'singular bind is rejected without reparenting');
    }
    // The live presentation retains (but does not yet render from) the Ninja
    // source-owned mode-1 clock and does not alias the caller's mutable sample.
    {
      const scene = create({
        async loadModel() { return model(); },
        async loadClip() { return clip('generic'); },
        async loadClipByStreamRef() { return clip('ninja'); },
      });
      const blend = { mode: 1 as const, elapsed: 2, duration: 7, previousWeight: Math.fround(5 / 7), jointIndices: [2, 3, 0] };
      const sample: BattleActorView = { ...view(99, 0, 'pl0000'),
        sourceAnimSample: { serial: 99, frame: 0, blend, targetDrawModels: [1, 7] } };
      await enter(scene, sample);
      assert(actor(scene).sourceAnimSample?.blend?.elapsed === 2, 'source blend clock reaches the live actor');
      assert(actor(scene).sourceAnimSample?.targetDrawModels?.join(',') === '1,7', 'target models reach presentation');
      blend.elapsed = 5;
      blend.jointIndices[0] = 99;
      assert(actor(scene).sourceAnimSample?.blend?.jointIndices[0] === 2, 'live actor copies the selected joints');
      assert(actor(scene).sourceAnimSample?.blend?.elapsed === 2, 'live actor copies the blend sample');
      scene.clear();
    }

    // Source-timed pose blending uses a saved rendered pose, not the original
    // source pose bank. Synthetic hierarchy tests non-accumulation and exit.
    {
      let releaseClip: ((value: THREE.AnimationClip) => void) | undefined;
      const scene = create({
        async loadModel() {
          const root = new THREE.Group(), joint0 = new THREE.Group(); joint0.name = 'JOBJ_0'; root.add(joint0);
          for (let i = 1; i < 20; i++) { const joint = new THREE.Group(); joint.name = `JOBJ_${i}`; joint0.add(joint); }
          return root;
        },
        async loadClip() { return clip('idle'); },
        async loadClipByStreamRef(_id, ref) {
          if (ref.slot === 1) return new Promise<THREE.AnimationClip>(resolve => { releaseClip = resolve; });
          const result = clip('ninja');
          result.tracks.push(new THREE.QuaternionKeyframeTrack('JOBJ_1.quaternion', [0, 1], [0, 0, 1, 0, 0, 0, 1, 0]));
          return result;
        },
      });
      const neutral: BattleActorView = { ...view(1, 0, 'pl0000'), state: 'idle', anim: 'idle', meleeAnimStream: null, sourceAnimSample: null };
      await enter(scene, neutral);
      const modelRoot = actor(scene).model!;
      const moving = modelRoot.getObjectByName('JOBJ_1')!, untouched = modelRoot.getObjectByName('JOBJ_2')!;
      moving.position.x = 10; untouched.position.x = 7;
      const joints = [2,3,4,5,6,7,8,9,10,11,12,0,1,13,14,15,16,17,18,19];
      const make = (weight: number): BattleActorView => ({ ...view(8, 0, 'pl0000', 0),
        sourceAnimSample: { serial: 8, frame: 0, blend: {mode: 1, elapsed: 1, duration: 2,
          previousWeight: weight, jointIndices: joints} } });
      await enter(scene, make(.5));
      near(moving.position.x, 5, 'source weight blends saved and sampled poses');
      near(moving.quaternion.z, Math.SQRT1_2, 'source blend interpolates rotation');
      near(moving.quaternion.w, Math.SQRT1_2, 'source blend preserves quaternion hemisphere');
      near(untouched.position.x, 7, 'unanimated joint stays fixed');
      for (let i = 0; i < 4; i++) { scene.update(.1); near(moving.position.x, 5, 'render ticks do not accumulate'); }
      scene.sync([make(.25)]); near(moving.position.x, 2.5, 'new source weight replaces previous blend');
      const prior = make(.5);
      const interrupted: BattleActorView = { ...prior, sourceAnimSample: { ...prior.sourceAnimSample!, serial: 9 } };
      scene.sync([interrupted]); near(moving.position.x, 1.25, 'new epoch captures interrupted visible pose');
      scene.sync([{ ...interrupted, sourceAnimSample: {serial: 9, frame: 0, blend: null} }]);
      near(moving.position.x, 0, 'blend completion restores current sample');
      moving.position.x = 8;
      const delayed = make(.5);
      scene.sync([{...delayed, meleeAnimStream: {group: 0, slot: 1},
        sourceAnimSample: {...delayed.sourceAnimSample!, serial: 10}}]);
      assert(releaseClip, 'new exact clip is pending');
      moving.position.x = 20; // Rendering continued while the new clip loaded.
      releaseClip(clip('delayed')); await flush();
      near(moving.position.x, 4, 'deferred load uses pose captured at transition start');
      scene.clear();
    }

    // Two source-selected Ninja parts attach only after the known-target
    // threshold, remain across a same-target restart, and hide on source exit.
    {
      const pending: Array<(part: THREE.Object3D) => void> = [];
      const scene = create({
        async loadModel() {
          const model = new THREE.Group(), root = new THREE.Group(); root.name = 'JOBJ_0'; model.add(root);
          for (let i = 1; i < 20; i++) { const joint = new THREE.Group(); joint.name = `JOBJ_${i}`; root.add(joint); }
          return model;
        },
        async loadClip() { return clip('idle'); },
        async loadClipByStreamRef() { return clip('ninja'); },
        loadSourceDrawPart() { return new Promise(resolve => pending.push(resolve)); },
      });
      const neutral: BattleActorView = {...view(1, 0, 'pl0000'), state: 'idle', anim: 'idle', meleeAnimStream: null, sourceAnimSample: null};
      await enter(scene, neutral);
      const joints = [2,3,4,5,6,7,8,9,10,11,12,0,1,13,14,15,16,17,18,19];
      const sample = (serial: number, previousWeight: number): BattleActorView => ({...view(serial, 0, 'pl0000', 0),
        sourceAnimSample: {serial, frame: 0, targetDrawModels: [1,7], blend: {mode:1, elapsed: 1, duration: 7, previousWeight, jointIndices: joints}}});
      scene.sync([sample(9, .75)]); await flush();
      assert(pending.length === 2, 'source parts load once');
      for (const resolve of pending) { const part = new THREE.Group(), root = new THREE.Group(); root.name = 'JOBJ_0'; part.add(root); resolve(part); }
      await flush(); await flush();
      const parts = actor(scene).sourceDrawParts;
      assert(parts?.length === 2 && parts.every(part => !part.visible), 'unknown previous selection stays hidden');
      assert(parts[0]!.parent?.name === 'JOBJ_7' && parts[1]!.parent?.name === 'JOBJ_11', 'parts attach to source-selected joints');
      scene.sync([sample(9, .5)]);
      assert(parts.every(part => part.visible), 'target parts appear at source threshold');
      scene.sync([sample(10, .75)]);
      assert(parts.every(part => part.visible), 'known same target survives recovery transition');
      scene.sync([neutral]);
      assert(parts.every(part => part.visible), 'known recovery target remains through idle');
      scene.sync([{...neutral, state: 'hit', anim: 'hit'}]);
      assert(parts.every(part => !part.visible), 'parts hide when source target is no longer known');
      scene.clear();
    }
    // A part load completing during verified movement must use the current clip,
    // not the idle/source-only state that existed when the request began.
    {
      const pending: Array<(part: THREE.Object3D) => void> = [];
      const scene = create({
        async loadModel() { const m = new THREE.Group(), r = new THREE.Group(); r.name = 'JOBJ_0'; m.add(r); for (let i=1;i<20;i++){const n=new THREE.Group(); n.name=`JOBJ_${i}`; r.add(n);} return m; },
        async loadClip(_id, slot) { return clip(`pl0000mot_g0s${slot === 'move' ? 1 : 0}_m0`); },
        loadSourceDrawPart() { return new Promise(resolve => pending.push(resolve)); },
      });
      const neutral: BattleActorView = {...view(1, 0, 'pl0000'), state:'idle', anim:'idle', meleeAnimStream:null, sourceAnimSample:null};
      await enter(scene, neutral);
      const movement: BattleActorView = {...neutral, state:'move', anim:'move'};
      scene.sync([movement]); await flush();
      assert(pending.length === 2, 'movement part loads started');
      for (const resolve of pending) {const p=new THREE.Group(), r=new THREE.Group(); r.name='JOBJ_0'; p.add(r); resolve(p);}
      await flush(); await flush();
      assert(actor(scene).sourceDrawParts?.every(part => part.visible), 'late parts appear immediately during verified movement');
      scene.clear();
    }
    // Stale async part loads cannot attach to a cleared presentation.
    {
      const pending: Array<(part: THREE.Object3D) => void> = [];
      let disposed = 0;
      const scene = create({
        async loadModel() { const m = new THREE.Group(), r = new THREE.Group(); r.name = 'JOBJ_0'; m.add(r); for (let i=1;i<20;i++){const n=new THREE.Group(); n.name=`JOBJ_${i}`; r.add(n);} return m; },
        async loadClip() { return clip('idle'); }, async loadClipByStreamRef() { return clip('ninja'); },
        loadSourceDrawPart() { return new Promise(resolve => pending.push(resolve)); },
      });
      const neutral: BattleActorView = {...view(1, 0, 'pl0000'), state:'idle', anim:'idle', meleeAnimStream:null, sourceAnimSample:null};
      await enter(scene, neutral);
      scene.sync([{...view(11, 0, 'pl0000', 0), sourceAnimSample:{serial:11,frame:0,targetDrawModels:[1,7],blend:null}}]);
      assert(pending.length === 2, 'stale part loads started'); scene.clear();
      for (const resolve of pending) {const p=new THREE.Group(), r=new THREE.Group();r.name='JOBJ_0';p.add(r);const geo=new THREE.BufferGeometry();geo.addEventListener('dispose',()=>disposed++);p.add(new THREE.Mesh(geo,new THREE.MeshBasicMaterial()));resolve(p);}
      await flush(); await flush();
      assert(disposed === 2 && actors(scene).size === 0, 'stale part resources are disposed');
    }

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

    // Normal Ninja/Sasuke exact resolved X refs. Ground recovery descriptor5
    // loops at120, but its source terminal is elapsed4; no rate5 inference.
    for(const id of ['pl0000','pl000a']){
      const scene=create({async loadModel(){return model();},async loadClip(){return clip('generic');},
        async loadClipByStreamRef(_id,ref){return clip(`g${ref.group}s${ref.slot}`,60,
          ref.group===4?(ref.slot===0?46:41):ref.slot===0?121:2);}});
      let serial=400;
      for(const [group,slot,sampleFrame] of [[4,0,14],[4,1,14],[0,0,0],[0,24,0]]){
        const sample:BattleActorView={...view(serial++,0,id),meleeAnimStream:{group:group!,slot:slot!}};
        await enter(scene,sample);const action=actor(scene).sourceAnimAction;
        assert(action?.paused&&action.getClip().name===`g${group}s${slot}`,'Ninja source-owned resolved clip');
        scene.sync([{...sample,sourceAnimSample:{serial:serial-1,frame:sampleFrame!}}]);scene.update(.5);
        near(action.time,sampleFrame!/60,'Ninja authored sample never render-runs');
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
