#!/usr/bin/env node
// One Ninja actor's bank-0 JObj snapshots while holding forward in Dolphin
// JIT64. Per-joint sourceFrame is inferred by exact matches at the observed
// joint-1 frame or its predecessor; joints were read during traversal, so this
// is not a simultaneous whole-body pose or independent clip-selector proof.
import {readFile} from 'node:fs/promises';
const rows = JSON.parse(await readFile('research/decomp/ninja-dash-rotation-witness-2026-11-18.json', 'utf8'));
if (rows.length !== 361 || rows.some(r => r.joint < 1 || r.joint > 19 ||
    (r.sourceFrame !== r.observedFrame && r.sourceFrame !== r.observedFrame - 1))) throw Error('invalid dash witnesses');
let count = 0;
for (const borg of ['pl0000', 'pl000a']) {
  const clip = JSON.parse(await readFile(`apps/game/public/models/${borg}/anim_g00_s02_dash_fwd.json`, 'utf8'));
  for (const {sourceFrame, joint, rot} of rows) {
    const [a, b, c] = rot.map(v => v / 2);
    const [sa, ca, sb, cb, sc, cc] = [Math.sin(a), Math.cos(a), Math.sin(b), Math.cos(b), Math.sin(c), Math.cos(c)];
    const q = [sa * cb * cc - ca * sb * sc, ca * sb * cc + sa * cb * sc,
      ca * cb * sc - sa * sb * cc, ca * cb * cc + sa * sb * sc];
    const actual = clip.bones.find(b => b.i === joint)?.rot?.slice(sourceFrame * 4, sourceFrame * 4 + 4);
    if (!actual || actual.length !== 4 || !actual.every(Number.isFinite)) throw Error(`${borg} joint ${joint}: invalid rotation`);
    const dot = Math.abs(q.reduce((sum, x, i) => sum + x * actual[i], 0));
    const angle = 2 * Math.acos(Math.min(1, dot / (Math.hypot(...q) * Math.hypot(...actual))));
    if (!Number.isFinite(angle) || angle > 1e-6) throw Error(`${borg} joint ${joint} frame ${sourceFrame}: angular error ${angle}`);
    count++;
  }
}
console.log(`Ninja dash: ${count} captured joint rotations match the baked clips within 1e-6 radians`);
