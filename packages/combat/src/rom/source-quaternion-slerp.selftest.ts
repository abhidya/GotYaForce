import {sourceQuaternionSlerp} from './source-quaternion-slerp.js';
export function runSourceQuaternionSlerpSelfTest(): void {
  const estimate = (x: number): number => 1 / Math.sqrt(x); // synthetic fixture only
  const identity = [0, 0, 0, 1], quarter = [0, 0, 1, 0];
  for (let i = 0; i <= 100; i++) {
    const w = Math.fround(i / 100), result = sourceQuaternionSlerp(identity, quarter, w, estimate);
    if (Math.abs(result[2] - Math.sin(w * Math.PI / 2)) > 3e-7 || Math.abs(result[3] - Math.cos(w * Math.PI / 2)) > 3e-7) throw Error(`slerp mismatch at ${w}`);
  }
  const inverse = sourceQuaternionSlerp(identity, [0, 0, 0, -1], 0.5, estimate);
  if (inverse[3] !== 1) throw Error('shortest arc sign');
  console.log('[source-quaternion-slerp] synthetic mathematical checks pass; retail parity not yet verified');
}
