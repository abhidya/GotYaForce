#!/usr/bin/env node
// Dolphin JIT64 GG4E, one Ninja actor, special-pose frames 0–15.
// The clip selection is inferred by exact source playback, not captured directly.
import {readFile} from 'node:fs/promises';
const rows = JSON.parse(await readFile('research/decomp/ninja-special-rotation-witness-2026-11-18.json', 'utf8'));
if (rows.length !== 16 || rows.some((r, i) => r.frame !== i || r.rot.length !== 20)) throw Error('incomplete special witnesses');
let count = 0;
for (const borg of ['pl0000', 'pl000a']) {
  const clip = JSON.parse(await readFile(`apps/game/public/models/${borg}/anim_g04_s00_special_s0.json`, 'utf8'));
  for (const {frame, rot} of rows) for (let joint = 0; joint < 20; joint++) {
    const [a, b, c] = rot[joint].map(v => v / 2);
    const [sa, ca, sb, cb, sc, cc] = [Math.sin(a), Math.cos(a), Math.sin(b), Math.cos(b), Math.sin(c), Math.cos(c)];
    const q = [sa * cb * cc - ca * sb * sc, ca * sb * cc + sa * cb * sc,
      ca * cb * sc - sa * sb * cc, ca * cb * cc + sa * sb * sc];
    const actual = clip.bones.find(b => b.i === joint)?.rot?.slice(frame * 4, frame * 4 + 4);
    if (!actual || actual.length !== 4 || !actual.every(Number.isFinite)) throw Error(`${borg} joint ${joint} frame ${frame}: invalid rotation`);
    const dot = Math.abs(q.reduce((sum, x, i) => sum + x * actual[i], 0));
    const angle = 2 * Math.acos(Math.min(1, dot / (Math.hypot(...q) * Math.hypot(...actual))));
    if (!Number.isFinite(angle) || angle > 1e-6) throw Error(`${borg} joint ${joint} frame ${frame}: angular error ${angle}`);
    count++;
  }
}
console.log(`Ninja special: ${count} captured joint rotations match the baked clips within 1e-6 radians`);
