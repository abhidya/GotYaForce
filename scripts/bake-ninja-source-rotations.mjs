#!/usr/bin/env node
// Rebuild bounded Ninja idle or special rotations from a user-supplied GG4E DAT.
// No original archive is shipped. The remaining tracks come from the existing
// baked reference; this is not a source-matrix or full visual-parity exporter.
import {readFile, writeFile} from 'node:fs/promises';
import {createHash} from 'node:crypto';
import {createRequire} from 'node:module';
import path from 'node:path';
import {fileURLToPath} from 'node:url';
const root = path.resolve(path.dirname(fileURLToPath(import.meta.url)), '..');
const [input, reference, output] = process.argv.slice(2);
if (!input || !reference || !output || process.argv.length !== 5 || path.resolve(output) === path.resolve(input)) {
  throw Error('usage: node scripts/bake-ninja-source-rotations.mjs <original-animation.dat> <reference.json> <output.json>');
}
const bytes = await readFile(input);
const sha = createHash('sha256').update(bytes).digest('hex');
const clips = {
  '78208675afecbddd89dd9b506d2bf43b31a6539e3aaa58ce517b44a7f293271b': {frames: 121, first: 1, name: /mot_g0s0_m0$/},
  'eb07929cb4294682c08a79c61e99309fefee22cbe9d695d242dd28ae7a4ad18f': {frames: 46, first: 0, name: /mot_g4s0_m0$/},
  'ca3d836c4ee9c5b40afa290edd967e70d9241b8ad071aa08db042b12635e6c3f': {frames: 31, first: 1, name: /mot_g0s2_m0$/},
};
const clip = clips[sha];
if (!clip) throw Error('unsupported animation archive hash');
const baked = JSON.parse(await readFile(reference, 'utf8'));
if (baked.frameCount !== clip.frames || !clip.name.test(baked.name) || baked.fps !== 60 || baked.rotFormat !== 'quat_xyzw' ||
    !Array.isArray(baked.bones) || baked.bones.length !== 20 ||
    baked.bones.some((b, i) => b.i !== i || !Array.isArray(b.rot) || b.rot.length !== clip.frames * 4)) {
  throw Error('unsupported reference clip layout');
}
const require = createRequire(path.join(root, 'packages/combat/package.json'));
const {build} = require('esbuild');
const result = await build({entryPoints: [path.join(root, 'packages/combat/src/rom/animation-pose-runtime.ts')],
  bundle: true, platform: 'node', format: 'esm', write: false, logLevel: 'silent'});
const {createSourceAnimationPoseRuntime} = await import('data:text/javascript;base64,' + Buffer.from(result.outputFiles[0].contents).toString('base64'));
const runtime = createSourceAnimationPoseRuntime();
const archive = runtime.hydrate(bytes, Array.from({length: 20}, (_, i) => i));
const joints = archive.roots.map((entry, i) => {
  if (!entry.name.endsWith(`_b${String(i).padStart(2, '0')}_animjoint`)) throw Error(`unexpected public root ${i}`);
  const joint = runtime.createJoint({sibling08: null, child10: null, flags14: 0,
    rotation1c: 0, rotation20: 0, rotation24: 0, scale2c: 1, scale30: 1, scale34: 1,
    translation38: 0, translation3c: 0, translation40: 0},
  {parent0c: null, aobj7c: null, robj80: null, dobj18: null, classUpdate50: null});
  runtime.attach(joint, entry.descriptor);
  return joint;
});
for (let frame = 0; frame < baked.frameCount; frame++) {
  for (const joint of joints) {runtime.request(joint, frame); runtime.animate(joint);}
  for (let i = clip.first; i < joints.length; i++) {
    const p = runtime.getJoint(joints[i]);
    const [a, b, c] = [p.rotation1c, p.rotation20, p.rotation24].map(v => v / 2);
    const [sa, ca, sb, cb, sc, cc] = [Math.sin(a), Math.cos(a), Math.sin(b), Math.cos(b), Math.sin(c), Math.cos(c)];
    const q = [sa * cb * cc - ca * sb * sc, ca * sb * cc + sa * cb * sc,
      ca * cb * sc - sa * sb * cc, ca * cb * cc + sa * sb * sc];
    baked.bones[i].rot.splice(frame * 4, 4, ...q);
  }
}
await writeFile(output, JSON.stringify(baked));
console.log(`Wrote ${output}; rotations ${clip.first}–19 were regenerated from ${sha}`);
