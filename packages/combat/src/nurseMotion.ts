/** Nurse-local ports of 8006c1c8 and 80067610. The older shared drift
 * compatibility helper omits Y and the motion writeback; do not use it here. */
import type { RomActor, Vec3 } from './rom/actor.js';
const normalize = (v: Vec3): void => {
  const n = Math.hypot(v.x, v.y, v.z);
  if (n > 0) { v.x /= n; v.y /= n; v.z /= n; }
};
/** Source angular cap is ten degrees per call, not multiplied by dt. */
export function steerNurseMotion(actor: RomActor, target: Vec3): void {
  const m = actor.motion;
  normalize(m);
  const v = { x: target.x - actor.pos.x, y: target.y - actor.pos.y, z: target.z - actor.pos.z };
  const n = Math.hypot(v.x, v.y, v.z);
  if (n <= 0) return;
  const angle = Math.min(Math.fround(10 * 0.01745329238474369),
    Math.acos(Math.max(-1, Math.min(1, (m.x * v.x + m.y * v.y + m.z * v.z) / n))));
  const axis = { x: m.y * v.z - m.z * v.y, y: m.z * v.x - m.x * v.z, z: m.x * v.y - m.y * v.x };
  if (axis.x * axis.x + axis.y * axis.y + axis.z * axis.z <= 0) axis.y = 1;
  normalize(axis);
  const c = Math.cos(angle), s = Math.sin(angle), d = (axis.x * m.x + axis.y * m.y + axis.z * m.z) * (1 - c);
  const x = m.x * c + (axis.y * m.z - axis.z * m.y) * s + axis.x * d;
  const y = m.y * c + (axis.z * m.x - axis.x * m.z) * s + axis.y * d;
  const z = m.z * c + (axis.x * m.y - axis.y * m.x) * s + axis.z * d;
  Object.assign(m, { x, y, z });
}
export function integrateNurseDrift(actor: RomActor): void {
  const m = actor.motion;
  const mag2 = m.x * m.x + m.y * m.y + m.z * m.z;
  if (mag2 <= 9.99999905104687e-9) return; // FLOAT_804375f4
  const scale = actor.hSpeed * actor.timescale * actor.tierScale / Math.sqrt(mag2);
  m.x *= scale; m.y *= scale; m.z *= scale;
  actor.pos.x += m.x; actor.pos.y += m.y; actor.pos.z += m.z;
  actor.hSpeed = Math.max(0, actor.hSpeed + actor.hDecel * actor.timescale);
}
