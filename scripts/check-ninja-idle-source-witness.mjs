#!/usr/bin/env node
// Original-game local JObj rotation capture, Dolphin JIT64, frames 17 and 18.
// This checks two poses only; it does not establish visual or hardware parity.
import {readFile} from 'node:fs/promises';
const witnesses = JSON.parse(await readFile('research/decomp/ninja-idle-rotation-witness-2026-11-18.json', 'utf8'));
if (witnesses.length !== 2 || witnesses.some(w => w.joints.length !== 19)) throw Error('incomplete rotation witnesses');
let checked = 0;
for (const borg of ['pl0000', 'pl000a']) {
  const clip = JSON.parse(await readFile(`apps/game/public/models/${borg}/anim_g00_s00_idle.json`, 'utf8'));
  for (const {frame, joints} of witnesses) for (const {joint, rot} of joints) {
    const [a, b, c] = rot.map(v => v / 2);
    const [sa, ca, sb, cb, sc, cc] = [Math.sin(a), Math.cos(a), Math.sin(b), Math.cos(b), Math.sin(c), Math.cos(c)];
    const q = [sa * cb * cc - ca * sb * sc, ca * sb * cc + sa * cb * sc,
      ca * cb * sc - sa * sb * cc, ca * cb * cc + sa * sb * sc];
    const bone = clip.bones.find(b => b.i === joint);
    const actual = bone?.rot?.slice(frame * 4, frame * 4 + 4);
    if (!actual || actual.length !== 4 || !actual.every(Number.isFinite)) throw Error(`${borg} joint ${joint} frame ${frame}: invalid rotation`);
    const dot = Math.abs(q.reduce((sum, x, i) => sum + x * actual[i], 0));
    const angle = 2 * Math.acos(Math.min(1, dot / (Math.hypot(...q) * Math.hypot(...actual))));
    if (!Number.isFinite(angle) || angle > 1e-6) throw Error(`${borg} joint ${joint} frame ${frame}: angular error ${angle}`);
    checked++;
  }
}
console.log(`Ninja idle: ${checked} captured joint rotations match the baked clips within 1e-6 radians`);
