#!/usr/bin/env node
// Exercise the live scene with repo-baked clips and the actual GLB joint tree.
// No WebGL rendering, original-game comparison, or source pose bank is claimed.
import { readFile } from 'node:fs/promises';
import { createRequire } from 'node:module';
import path from 'node:path';
import { fileURLToPath } from 'node:url';
const root = fileURLToPath(new URL('../', import.meta.url));
const gameRequire = createRequire(path.join(root, 'apps/game/package.json'));
const { build } = createRequire(gameRequire.resolve('vite'))('esbuild');
const result = await build({absWorkingDir: root, stdin: {
  contents: `export * as THREE from 'three';
    export {BattleScene} from './apps/game/src/sim/battleScene.ts';
    export {createBorgPresentationAssets} from './apps/game/src/sim/borgPresentationAssets.ts';
    export {divideSourceAnimationFloat32} from './packages/combat/src/rom/source-float32-divide.ts';`,
  resolveDir: root, sourcefile: 'ninja-presentation-entry.mjs',
}, bundle: true, platform: 'node', format: 'esm', write: false,
  define: {'import.meta.env.BASE_URL': '"/"'}, logLevel: 'warning'});
const {THREE, BattleScene, createBorgPresentationAssets, divideSourceAnimationFloat32} = await import(`data:text/javascript;base64,${Buffer.from(result.outputFiles[0].text).toString('base64')}`);
THREE.TextureLoader.prototype.load = () => new THREE.Texture();
const previousFetch = globalThis.fetch;
globalThis.fetch = async url => {
  const file = path.join(root, 'apps/game/public', String(url).replace(/^\//, ''));
  try { return new Response(await readFile(file), {status: 200}); }
  catch (e) { if (e.code === 'ENOENT') return new Response('', {status: 404}); throw e; }
};
const waitUntil = async predicate => {
  for (let i = 0; i < 100; i++) { if (predicate()) return; await new Promise(resolve => setTimeout(resolve, 10)); }
  throw Error('animation/model load did not settle');
};
function view(id) {
  return {uid: 'actor', borgId: id, combatFormId: undefined, team: 0, ownerPlayer: 'p1', alive: true,
    state: 'idle', anim: 'idle', pos: {x:0,y:0,z:0}, vel: {x:0,y:0,z:0}, rotY: 0, modelSizeScale: 1,
    lockTarget: null, allyLockTarget: null, dashActiveFrames: 0, chargeFrames: 0, meleeAnimStream: null,
    sourceAnimSample: null, meleeSounds: null, lastHitImpactEffectId: undefined, lastHitAttackerTeam: undefined,
    slowHitTimer: 0, hasteHitTimer: 0, romAfterimage: undefined};
}
try {
  for (const id of ['pl0000', 'pl000a']) {
    const glb = await readFile(path.join(root, `apps/game/public/models/${id}/model_00.glb`));
    const doc = JSON.parse(glb.subarray(20, 20 + glb.readUInt32LE(12)).toString('utf8'));
    const ids = new Set(doc.nodes.map((n, i) => /^JOBJ_\d+$/.test(n.name ?? '') ? i : -1).filter(i => i >= 0));
    const nodes = new Map([...ids].map(i => {
      const src = doc.nodes[i], node = new THREE.Group(); node.name = src.name;
      if (src.translation) node.position.fromArray(src.translation);
      if (src.rotation) node.quaternion.fromArray(src.rotation);
      if (src.scale) node.scale.fromArray(src.scale);
      return [i, node];
    }));
    const childIds = new Set();
    for (const i of ids) for (const child of doc.nodes[i].children ?? []) if (ids.has(child)) {
      nodes.get(i).add(nodes.get(child)); childIds.add(child);
    }
    const skeleton = new THREE.Group();
    for (const i of ids) if (!childIds.has(i)) skeleton.add(nodes.get(i));
    // Production part loader uses GLB node graphs and POSITION attributes.
    // Materials are test doubles; no WebGL or visual parity is claimed.
    const assetLoader = {
      async loadGlbScene(url) {
        const bytes = await readFile(path.join(root, 'apps/game/public', String(url).replace(/^\//, '')));
        const doc = JSON.parse(bytes.subarray(20, 20 + bytes.readUInt32LE(12)).toString('utf8'));
        const jsonEnd = 20 + bytes.readUInt32LE(12);
        if (bytes.toString('ascii', jsonEnd + 4, jsonEnd + 8) !== 'BIN\0') throw Error('GLB binary chunk missing');
        const binaryStart = jsonEnd + 8;
        const objects = doc.nodes.map(n => {
          let o;
          if (n.mesh === undefined) o = new THREE.Group();
          else {
            const primitives = doc.meshes[n.mesh].primitives;
            if (primitives.length !== 1) throw Error('Unexpected part primitive count');
            const a = doc.accessors[primitives[0].attributes.POSITION], b = doc.bufferViews[a.bufferView];
            if (a.componentType !== 5126 || a.type !== 'VEC3' || a.count < 1) throw Error('Unexpected part position format');
            const stride = b.byteStride ?? 12, offset = binaryStart + (b.byteOffset ?? 0) + (a.byteOffset ?? 0);
            const values = new Float32Array(a.count * 3);
            for (let i=0;i<a.count;i++) for (let k=0;k<3;k++) values[i*3+k] = bytes.readFloatLE(offset+i*stride+k*4);
            if (!values.every(Number.isFinite)) throw Error('Non-finite part geometry');
            const geometry = new THREE.BufferGeometry(); geometry.setAttribute('position', new THREE.BufferAttribute(values, 3));
            o = new THREE.Mesh(geometry, new THREE.MeshBasicMaterial());
          }
          o.name = n.name ?? ''; if (n.translation) o.position.fromArray(n.translation); if (n.rotation) o.quaternion.fromArray(n.rotation); if (n.scale) o.scale.fromArray(n.scale); return o;
        });
        const children = new Set();
        doc.nodes.forEach((n, i) => { for (const c of n.children ?? []) { objects[i].add(objects[c]); children.add(c); } });
        const scene = new THREE.Group(); objects.forEach((o, i) => { if (!children.has(i)) scene.add(o); }); return scene;
      },
      cloneModel(source) { return source.clone(true); },
    };
    const production = createBorgPresentationAssets({assetLoader, defaultLeadId: id});
    const scene = new BattleScene(new THREE.Group(), {
      loadModel: async () => skeleton.clone(true), loadClip: production.loadClip,
      loadClipByStreamRef: production.loadClipByStreamRef, loadSourceDrawPart: production.loadSourceDrawPart,
    });
    const neutral = view(id); scene.sync([neutral]);
    const actor = () => scene.actors.get('actor');
    await waitUntil(() => actor()?.ready); scene.sync([neutral]);
    await waitUntil(() => actor()?.actions.idle);
    await waitUntil(() => actor()?.sourceDrawParts?.length === 2);
    if (actor().sourceDrawParts.some(part => !part.visible)) throw Error(`${id}: verified idle parts hidden`);
    scene.update(.1);
    const jointOrder = [2,3,4,5,6,7,8,9,10,11,12,0,1,13,14,15,16,17,18,19];
    for (const slot of [0, 1]) {
      for (let elapsed = 1; elapsed < 7; elapsed++) {
        const sample = {...neutral, state: 'special', anim: 'special', meleeAnimStream: {group:4, slot},
          sourceAnimSample: {serial: slot + 1, frame: 0, targetDrawModels:[1,7], blend: {mode:1, elapsed, duration:7,
            previousWeight: Math.fround(1 - divideSourceAnimationFloat32(elapsed, 7)), jointIndices: jointOrder}}};
        scene.sync([sample]);
        await waitUntil(() => actor()?.sourceAnimAction?.getClip().name === `${id}mot_g4s${slot}_m0`);
        scene.update(1/60);
        await waitUntil(() => actor()?.sourceDrawParts?.length === 2);
        if (actor().sourceDrawParts.some(part => part.visible !== true)) throw Error(`${id}: verified idle parts should remain through X`);
        for (const part of actor().sourceDrawParts) {const bounds = new THREE.Box3().setFromObject(part); if (bounds.isEmpty() || ![bounds.min.x,bounds.min.y,bounds.min.z,bounds.max.x,bounds.max.y,bounds.max.z].every(Number.isFinite)) throw Error(`${id}: invalid part geometry bounds`);}
        if (actor().sourceBlendPose?.length !== 20) throw Error(`${id} slot ${slot}: saved pose missing`);
        for (const joint of actor().sourceBlendPose) {
          const {position:p, quaternion:q} = joint.node;
          if (![p.x,p.y,p.z,q.x,q.y,q.z,q.w].every(Number.isFinite)) throw Error(`${id} slot ${slot}: non-finite joint`);
        }
      }
    }
    scene.clear();
    console.log(`[ninja-presentation-assets] PASS ${id}: actual baked special clips, GLB node trees and part positions in BattleScene; no WebGL or source-game parity asserted`);
  }
} finally { globalThis.fetch = previousFetch; }
