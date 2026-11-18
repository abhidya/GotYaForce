#!/usr/bin/env node
// Repository-baked assets only: this is not a comparison against the original game.
import { readFile } from 'node:fs/promises';
import { createRequire } from 'node:module';
import path from 'node:path';
import { fileURLToPath } from 'node:url';
const root = fileURLToPath(new URL('../', import.meta.url));
const require = createRequire(path.join(root, 'packages/combat/package.json'));
const { build } = require('esbuild');
const result = await build({ absWorkingDir: root, stdin: {
  contents: `export {sourceBlendQuaternion} from './packages/combat/src/rom/source-quaternion-slerp.ts';
             export {sourceReciprocalSqrtEstimate} from './packages/combat/src/rom/source-reciprocal-sqrt-estimate.ts';
             export {divideSourceAnimationFloat32} from './packages/combat/src/rom/source-float32-divide.ts';`,
  resolveDir: root, sourcefile: 'ninja-blend-entry.mjs',
}, bundle: true, platform: 'node', format: 'esm', write: false });
const { sourceBlendQuaternion, sourceReciprocalSqrtEstimate, divideSourceAnimationFloat32 } = await import(`data:text/javascript;base64,${Buffer.from(result.outputFiles[0].text).toString('base64')}`);
const readJSON = async p => JSON.parse(await readFile(path.join(root, p), 'utf8'));
let tested = 0;
for (const id of ['pl0000', 'pl000a']) {
  const dir = `apps/game/public/models/${id}`;
  const glb = await readFile(path.join(root, dir, 'model_00.glb'));
  const doc = JSON.parse(glb.subarray(20, 20 + glb.readUInt32LE(12)).toString('utf8'));
  const joints = new Set(doc.nodes.map((n, i) => /^JOBJ_\d+$/.test(n.name ?? '') ? i : -1).filter(i => i >= 0));
  const descendants = new Set([...joints].flatMap(i => (doc.nodes[i].children ?? []).filter(c => joints.has(c))));
  const roots = [...joints].filter(i => !descendants.has(i));
  const names = [];
  const visit = i => { names.push(doc.nodes[i].name); for (const c of doc.nodes[i].children ?? []) if (joints.has(c)) visit(c); };
  if (roots.length !== 1) throw Error(`${id}: expected one joint root`);
  visit(roots[0]);
  if (names.length !== 20 || names.some((n, i) => n !== `JOBJ_${i}`)) throw Error(`${id}: unexpected GLB traversal`);
  const idle = await readJSON(`${dir}/anim_g00_s00_idle.json`);
  for (const slot of [0, 1]) {
    const incoming = await readJSON(`${dir}/anim_g04_s0${slot}_special_s${slot}.json`);
    for (let joint = 0; joint < 20; joint++) {
      const old = idle.bones.find(b => b.i === joint), next = incoming.bones.find(b => b.i === joint);
      if (!old || !next || old.rot.length !== idle.frameCount * 4 || next.rot.length !== incoming.frameCount * 4) throw Error(`${id}: missing rotation tracks for ${joint}`);
      const current = next.rot.slice(0, 4).map(Math.fround);
      for (let frame = 0; frame < idle.frameCount; frame += 10) {
        const previous = old.rot.slice(frame * 4, frame * 4 + 4).map(Math.fround);
        for (let elapsed = 1; elapsed < 7; elapsed++) {
          const weight = Math.fround(1 - divideSourceAnimationFloat32(elapsed, 7));
          const blended = sourceBlendQuaternion(current, previous, weight, sourceReciprocalSqrtEstimate);
          if (blended.some(v => !Number.isFinite(v))) throw Error(`${id}: non-finite blend`);
          tested++;
        }
      }
    }
  }
}
console.log(`[ninja-source-blend-assets] PASS: ${tested} blends from checked-in GLB hierarchy and baked rotations; no original-game visual parity asserted`);
