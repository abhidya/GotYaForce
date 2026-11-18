import {sourceReciprocalSqrtEstimate} from './source-reciprocal-sqrt-estimate.js';
import {sourceQuaternionSlerp} from './source-quaternion-slerp.js';
export function runSourceQuaternionSlerpSelfTest(): void {
  // Controlled GG4E 8020bf08 calls in Dolphin 2606-97; not console captures.
  const captures: Array<[number[], number[], number, string]> = [
    [[0,0,0,1], [0,0,0,1], .25, '0000000000000000000000003f800000'],
    [[0,0,0,1], [0,0,1,0], .25, '00000000000000003ec3ef163f6c835e'],
    [[0,0,0,1], [0,0,1,0], .5, '00000000000000003f3504f33f3504f3'],
    [[0,0,0,1], [0,0,-1,0], .75, '0000000000000000bf6c835e3ec3ef16'],
    [[0,0,0,1], [0,0,.6,.8], .3, '00000000000000003e44753c3f7b3e94'],
    [[0,0,0,1], [0,0,-.6,-.8], .7, '00000000000000003edee9003f6676d8'],
    [[.5,.5,.5,.5], [-.5,.5,.5,.5], .4, '3dd613023f12fdf33f12fdf33f12fdf3'],
  ];
  const view = new DataView(new ArrayBuffer(16));
  for (const [a,b,weight,expected] of captures) {
    const result = sourceQuaternionSlerp(a.map(Math.fround), b.map(Math.fround), Math.fround(weight), sourceReciprocalSqrtEstimate);
    result.forEach((value, index) => view.setFloat32(index * 4, value));
    const actual = Array.from(new Uint8Array(view.buffer), value => value.toString(16).padStart(2, '0')).join('');
    if (actual !== expected) throw Error(`Dolphin quaternion mismatch: ${actual} != ${expected}`);
  }
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
