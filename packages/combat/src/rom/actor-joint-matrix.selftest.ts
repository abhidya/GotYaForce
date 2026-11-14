import {createSourceActorJointMatrixRuntime} from './actor-joint-matrix.js';
import {primarySineCorrection} from './actor-primary-float.js';
import {createSourceJointAnimationFeedbackRuntime} from './joint-animation-feedback.js';
import {createSourceJObjAnimationRuntime} from './jobj-animation.js';
function check(ok: boolean, why: string): void {if (!ok) throw Error(`[actor-joint-matrix-test] ${why}`);}
function rejects(run: () => void, text: string): void {
  let error = ''; try {run();} catch (e) {error = String(e);}
  check(error.includes(text), `expected ${text}, got ${error}`);
}
const identity = [1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0];
const zero = {x: 0, y: 0, z: 0}, unit = {x: 1, y: 1, z: 1};
function bits(value: number): number {
  const view = new DataView(new ArrayBuffer(4)); view.setFloat32(0, value); return view.getUint32(0);
}
function bits64(value: number): bigint {
  const view = new DataView(new ArrayBuffer(8)); view.setFloat64(0, value); return view.getBigUint64(0);
}
function fromBits(raw: number): number {
  const view = new DataView(new ArrayBuffer(4)); view.setUint32(0, raw); return view.getFloat32(0);
}
function fixture() {
  const feedback = createSourceJointAnimationFeedbackRuntime(createSourceJObjAnimationRuntime());
  const pose = feedback.createPose({translation: {x: 2, y: 3, z: 4}, quaternion: {x: 0, y: 0, z: 0, w: 1}});
  const hooks: {get?: () => void} = {};
  const adapter = {getPose(id: symbol) {check(this === adapter, 'captured receiver'); hooks.get?.(); return feedback.getPose(id);}};
  const runtime = createSourceActorJointMatrixRuntime(adapter);
  const parent = runtime.createMatrix(identity), destination = runtime.createMatrix(Array(12).fill(19));
  return {feedback, pose, runtime, parent, destination, hooks, adapter,
    output: runtime.getMatrix(destination), compose: () => runtime.composeJoint(parent, destination, pose, zero, unit)};
}
function primaryFixture() {
  const f = fixture(), current = f.runtime.createMatrix(identity), next = f.runtime.createMatrix(identity), end = f.runtime.createMatrix(identity);
  const currentMatrix = f.runtime.getMatrix(current), nextMatrix = f.runtime.getMatrix(next), endMatrix = f.runtime.getMatrix(end);
  nextMatrix[7] = 2; endMatrix[7] = 2.5;
  const translation = {...zero}, nextTranslation = {x: 0, y: 2, z: 0};
  const correction = {x: 0, y: 1, z: 0, axis0d: 2, axis0e: 1, bend0f: 1};
  const run = () => f.runtime.primaryFoldedPlacement(f.parent, current, next, end, translation, nextTranslation, correction);
  return {...f, current, next, end, currentMatrix, nextMatrix, endMatrix, translation, nextTranslation, correction, run};
}
function positivePrimaryFixture() {
  const f = primaryFixture(); f.nextMatrix[7] = 1; f.endMatrix[7] = 2; f.nextTranslation.y = 1;
  return f;
}
function positivePrimaryExpected(bend: number): {current: number[]; next: number[]} {
  // Independently rounded dyadic expectations for the two actual Concats.
  // Source cosines are3effffff/bf000001; both refined sines are3f5db3d7.
  // The second Concat's distinct lower-left sine is intentional, not an ideal
  // angle-addition matrix. No production numeric helper computes these values.
  const q = fromBits(0x3f7ffffe), c = fromBits(0x3efffffd), cc = fromBits(0x3efffffc);
  const s = fromBits(0x3f5db3d5) * (bend < 128 ? 1 : -1);
  const ss = fromBits(0x3f5db3d6) * (bend < 128 ? 1 : -1);
  switch (Math.abs((bend << 24) >> 24)) {
    case 1: return {current: [q, 0, 0, 0, 0, c, s, 0, 0, -s, c, 0],
      next: [q, 0, 0, 0, 0, cc, -s, c, 0, ss, c, -s]};
    case 2: return {current: [c, 0, -s, 0, 0, q, 0, 0, s, 0, c, 0],
      next: [cc, 0, s, 0, 0, q, 0, q, -ss, 0, c, 0]};
    default: return {current: [c, s, 0, 0, -s, c, 0, 0, 0, 0, q, 0],
      next: [cc, -s, 0, s, ss, c, 0, c, 0, 0, q, 0]};
  }
}
export function runActorJointMatrixSelfTests(): void {
  runActorJointMatrixBytesSelfTests();
  {
    // Binary64 witnesses are necessary: final frsp happens to hide the first
    // sine's stage2 split-multiply error. Exercise the production internal
    // fnmsub helper, without adding a test hook to the matrix runtime API.
    const cases = [
      {squared: 0.75, seed: 18917 / 16384, seedBits: 0x3ff2794000000000n,
        stages: [
          [0x3ff55466d9000000n, 0x3fe2794000000000n, 0x400000596ea00000n, 0x3ff279a7422e5480n],
          [0x3ff555554d85b177n, 0x3fe279a7422e5480n, 0x4000000002eddd73n, 0x3ff279a74590331bn],
          [0x3ff5555555555552n, 0x3fe279a74590331bn, 0x4000000000000001n, 0x3ff279a74590331cn],
        ], final: 0x3febb67ae8584caan},
      {squared: fromBits(0x3f3fffff), seed: 38742423 / 33554432, seedBits: 0x3ff2794cb8000000n,
        stages: [
          [0x3ff5548437cedc44n, 0x3fe2794cb8000000n, 0x4000004e75bcaf82n, 0x3ff279a74f46ddecn],
          [0x3ff555556bc40ba0n, 0x3fe279a74f46ddecn, 0x400000000241265an, 0x3ff279a751e14d56n],
          [0x3ff5555571c71c95n, 0x3fe279a751e14d56n, 0x4000000000000001n, 0x3ff279a751e14d57n],
        ], final: 0x3febb67ad5dea55fn},
    ];
    for (const test of cases) {
      let estimate = test.seed;
      check(bits64(estimate) === test.seedBits, 'canonical model-derived sine seed bits');
      for (let iteration = 0; iteration < 3; iteration++) {
        const q = estimate * estimate, h = 0.5 * estimate;
        const k = primarySineCorrection(test.squared, q); estimate = h * k;
        check([q, h, k, estimate].every((v, i) => bits64(v) === test.stages[iteration]![i]),
          `source sine binary64 stage ${iteration + 1}, square bits${bits(test.squared).toString(16)}`);
        if (test.squared === 0.75 && iteration === 1) {
          check(bits64(-(test.squared * q - 3)) === 0x4000000002eddd74n &&
            bits64(k) === 0x4000000002eddd73n, 'genuine fused fnmsub differs from split RN64 by one ULP');
        }
      }
      check(bits64(test.squared * estimate) === test.final && bits(Math.fround(test.squared * estimate)) === 0x3f5db3d7,
        'three-stage sine final double product and only then frsp');
    }
    check(primarySineCorrection(0.75, 1 + 2 ** -50) === 2.25 - 2 ** -50 &&
      primarySineCorrection(0.75, 1 + 3 * 2 ** -50) === 2.25 - 2 ** -49,
      'bounded fused correction resolves both halfway directions to an even significand');
    for (const square of [0, -0, 1, 0.75 + 2 ** -24, 0.75 - 2 ** -23, NaN, Infinity]) {
      rejects(() => primarySineCorrection(square, 1.25), 'bounded primary sine');
    }
    for (const q of [0, 1 - 2 ** -53, 2 + 2 ** -51, NaN, Infinity]) {
      rejects(() => primarySineCorrection(0.75, q), 'bounded primary sine');
    }
  }
  {
    const f = fixture(), original = identity.slice();
    const id = f.runtime.createMatrix(original); original[0] = 7;
    check(f.runtime.getMatrix(id)[0] === 1 && Object.isSealed(f.output), 'owned sealed storage');
    check(f.runtime.getMatrix(f.destination) === f.output, 'stable actual array identity');
    f.compose(); check(f.output[3] === 2 && f.output[7] === 3 && f.output[11] === 4, 'translation after both concats');
    f.feedback.getPose(f.pose).translation.y = 8;
    check(f.output[7] === 3, 'no implicit pose rebuild');
    f.compose(); check(f.output[7] === 8, 'live pose reads at explicit call');
    f.runtime.composeJoint(f.parent, f.destination, f.pose, zero, {x: 2, y: 3, z: 4});
    check(f.output[0] === 2 && f.output[5] === 3 && f.output[10] === 4 && f.output[7] === 8, 'right scale leaves translation');
  }
  {
    const f = fixture(); f.runtime.composeJoint(f.parent, f.parent, f.pose, zero, unit);
    check(f.runtime.getMatrix(f.parent)[7] === 3, 'parent destination alias');
    f.runtime.composeJoint(f.parent, f.parent, f.pose, zero, unit);
    check(f.runtime.getMatrix(f.parent)[7] === 6, 'alias reload on next explicit call');
  }
  {
    const f = fixture(), p = f.runtime.getMatrix(f.parent), t = f.feedback.getPose(f.pose).translation;
    p[0] = -1; p[1] = 1 - 2 ** -23; p[2] = 0;
    t.x = 1; t.y = 1 + 2 ** -23; t.z = 0;
    f.compose(); check(f.output[3] === -(2 ** -46), 'fused cancellation survives both concats');
  }
  {
    const f = fixture(); f.runtime.getMatrix(f.parent).fill(-0);
    f.feedback.getPose(f.pose).translation.x = -0;
    f.feedback.getPose(f.pose).translation.y = -0;
    f.feedback.getPose(f.pose).translation.z = -0;
    rejects(() => f.runtime.composeJoint(f.parent, f.destination, f.pose, {x: 1, y: 0, z: 0}, unit), 'nonzero short');
    check(Object.is(f.output[0], 0) && Object.is(f.output[1], -0) && Object.is(f.output[2], 0), 'audited quaternion zero signs affect concat');
  }
  {
    const f = fixture(), p = f.runtime.getMatrix(f.parent);
    p[0] = -0; p[1] = 0; p[2] = -0; p[3] = 0;
    rejects(() => f.runtime.composeJoint(f.parent, f.destination, f.pose, {x: 1, y: 0, z: 0}, unit), 'nonzero short');
    check(Object.is(f.output[2], 0), 'column2 includes positive-zero translation lane, changing negative-zero sum');
  }
  {
    const f = fixture(); f.feedback.getPose(f.pose).quaternion.x = -0;
    rejects(f.compose, 'exact (+0,+0,+0,1)'); check(f.output.every(v => v === 19), 'negative zero quaternion refusal before destination stores');
  }
  {
    const f = fixture();
    rejects(() => f.runtime.composeJoint(f.parent, f.destination, f.pose, {x: 1, y: 0, z: 0}, unit), 'nonzero short');
    check(f.output[7] === 3 && f.output[5] === 1, 'first concat retained before correction refusal');
    rejects(() => f.runtime.composeJoint(f.parent, f.destination, f.pose, zero, {x: 2, y: NaN, z: 1}), 'scale.y');
    check(f.output[5] === 1, 'scale refusal retains correction copy');
  }
  {
    const f = fixture();
    rejects(() => f.runtime.composeJoint(f.parent, f.destination, f.pose, zero, {x: 2, y: NaN, z: 1}), 'scale.y');
    check(f.output[0] === 1 && f.output[5] === 1 && f.output[7] === 3, 'fresh scale refusal occurs after actual first concat');
  }
  {
    const f = fixture(); Object.defineProperty(f.output, '4', {writable: false});
    rejects(f.compose, 'non-writable');
    check(f.output[0] === 1 && f.output[1] === 0 && f.output[2] === 19 && f.output[3] === 19, 'concat paired store order prefix');
  }
  {
    const f = fixture(); f.runtime.getMatrix(f.parent)[11] = Infinity;
    rejects(f.compose, 'finite source float32'); check(f.output.every(v => v === 19), 'whole input snapshot precedes writes');
  }
  {
    const f = fixture(); f.hooks.get = () => {try {f.compose();} catch { /* out-of-contract adapter fault */ }};
    rejects(f.compose, 'reentry was caught'); check(f.output.every(v => v === 19), 'caught reentry poisons outer call');
    delete f.hooks.get; f.compose(); check(f.output[7] === 3, 'runtime usable after refusal');
    f.adapter.getPose = () => {throw Error('replacement should not execute');}; f.compose();
  }
  {
    const f = fixture(); rejects(() => f.runtime.getMatrix(Symbol()), 'unknown/non-owned');
    rejects(() => f.runtime.composeJoint(f.parent, f.destination, Symbol(), zero, unit), 'unknown/non-owned pose');
    rejects(() => f.runtime.createMatrix([1]), 'exactly 12');
    rejects(() => f.runtime.createMatrix(Array(12)), 'own data');
    rejects(() => f.runtime.createMatrix([...identity.slice(0, 11), 0.1]), 'finite source float32');
    const sparse = identity.slice(); Object.defineProperty(sparse, '1', {get() {throw Error('must not execute');}});
    rejects(() => f.runtime.createMatrix(sparse), 'own data');
    const limited = createSourceActorJointMatrixRuntime(f.feedback, 1); limited.createMatrix(identity);
    rejects(() => limited.createMatrix(identity), 'capacity');
  }
  {
    const f = fixture(); f.output.fill(NaN);
    f.runtime.identity(f.destination);
    check(f.output.every((v, i) => Object.is(v, identity[i])), 'identity overwrites without reading old entries; all zeros positive');
    f.output.fill(19); Object.defineProperty(f.output, '4', {writable: false});
    rejects(() => f.runtime.identity(f.destination), 'non-writable');
    check([2, 3, 6, 7, 8, 9].every(i => Object.is(f.output[i], 0)) &&
      [0, 1, 4, 5, 10, 11].every(i => f.output[i] === 19), 'identity exact paired-store prefix');
  }
  {
    const f = fixture(); f.runtime.identity(f.destination);
    f.output[1] = -0; f.output[3] = -0; f.output[7] = -0; f.output[11] = 4;
    f.runtime.translate(f.destination, {x: 0, y: -0, z: 3});
    check(Object.is(f.output[1], -0) && Object.is(f.output[3], 0) &&
      Object.is(f.output[7], -0) && f.output[11] === 7, 'TransApply retains rotation and adds actual translation with source zero signs');
    f.output[3] = 1;
    f.runtime.translate(f.destination, {x: 2 ** -24, y: 0, z: 0});
    check(f.output[3] === 1, 'TransApply rounds add to nearest-even binary32');
  }
  {
    const f = fixture(); f.runtime.identity(f.destination);
    Object.defineProperty(f.output, '7', {writable: false});
    rejects(() => f.runtime.translate(f.destination, {x: 2, y: 3, z: 4}), 'non-writable');
    check(f.output[3] === 2 && f.output[7] === 0 && f.output[11] === 0, 'TransApply retains X store before Y store refusal');
  }
  {
    const f = fixture(); f.output[4] = NaN; Object.defineProperty(f.output, '0', {writable: false});
    rejects(() => f.runtime.translate(f.destination, zero), 'non-writable');
    check(f.output[3] === 19, 'TransApply first pair store precedes later pair4 load');
  }
  {
    const f = fixture(); f.runtime.identity(f.destination);
    f.output[8] = NaN;
    rejects(() => f.runtime.translate(f.destination, {x: 2, y: 3, z: 4}), 'matrix[8]');
    check(f.output[3] === 2 && f.output[7] === 0 && f.output[11] === 0, 'TransApply late input refusal retains X store');
  }
  {
    const f = fixture(); f.runtime.identity(f.destination);
    const largest = Math.fround(3.4028234663852886e38); f.output[11] = largest;
    rejects(() => f.runtime.translate(f.destination, {x: 2, y: 3, z: largest}), 'translated z');
    check(f.output[3] === 2 && f.output[7] === 0 && f.output[11] === largest, 'TransApply Z sum precedes Y store under host finite admission');
  }
  {
    const f = fixture(), source = f.runtime.getMatrix(f.parent); source[1] = -0;
    f.runtime.copy(f.parent, f.destination);
    check(Object.is(f.output[1], -0) && f.output[10] === 1, 'copy preserves exact source bits');
    f.runtime.copy(f.destination, f.destination);
    check(Object.is(f.output[1], -0), 'aliased copy retains source zero signs');
    f.output.fill(19); source[4] = NaN;
    rejects(() => f.runtime.copy(f.parent, f.destination), 'matrix[4]');
    check(f.output.slice(0, 4).every((v, i) => Object.is(v, source[i])) &&
      f.output.slice(4).every(v => v === 19), 'copy late load refusal retains earlier pairs');
  }
  {
    const f = fixture(); Object.defineProperty(f.output, '1', {writable: false});
    rejects(() => f.runtime.copy(f.parent, f.destination), 'non-writable');
    check(f.output[0] === 1 && f.output[1] === 19 && f.output[2] === 19, 'copy validates each store and retains completed store');
  }
  {
    const f = fixture(); f.output[4] = NaN; Object.defineProperty(f.output, '0', {writable: false});
    rejects(() => f.runtime.correctShort(f.destination, {x: -0, y: 0, z: 0}), 'non-writable');
    rejects(() => f.runtime.correctShort(f.destination, {x: 0, y: 32768, z: 0}), 'signed short');
    rejects(() => f.runtime.correctShort(f.destination, {x: 0, y: 1, z: 0}), 'nonzero short correction');
  }
  {
    const f = fixture(); f.runtime.identity(f.destination); f.output[1] = -0;
    f.runtime.scale(f.destination, unit);
    check(Object.is(f.output[1], 0), 'unit scale executes actual Concat instead of skipping');
    f.runtime.translate(f.destination, {x: 2, y: 3, z: 4});
    f.runtime.scale(f.destination, {x: 2, y: 3, z: 4});
    check(f.output[0] === 2 && f.output[5] === 3 && f.output[10] === 4 &&
      f.output[3] === 2 && f.output[7] === 3 && f.output[11] === 4, 'standalone scale is right concatenation');
  }
  {
    // Rows chosen so the audited -sin lane survives Concat's actual additions.
    // A guessed positive-zero identity rotation would change each marked result.
    const cases = [
      {axis: 'x', row: [-0, 0, -0, -0], result: [0, 0, -0, 0]},
      {axis: 'y', row: [-0, -0, 0, 0], result: [-0, 0, 0, 0]},
      {axis: 'z', row: [0, -0, -0, 0], result: [0, -0, 0, 0]},
    ] as const;
    for (const {axis, row, result} of cases) {
      const f = fixture(), source = f.runtime.createMatrix([...row, ...row, ...row]);
      f.runtime.rotateShort(axis, source, f.destination, 0);
      check(f.output.every((v, i) => Object.is(v, result[i % 4])), `${axis} rotation zero signs after actual Concat`);
      f.runtime.rotateShort(axis, source, source, -0);
      check(f.runtime.getMatrix(source).every((v, i) => Object.is(v, f.output[i])), `${axis} rotation alias and signed-short -0 normalization`);
    }
  }
  {
    const f = fixture(); f.runtime.getMatrix(f.parent)[1] = -0;
    f.runtime.rotateShort('x', f.parent, f.destination, 0);
    check(Object.is(f.output[1], 0), 'zero angle wrapper never skips Concat');
    f.output.fill(19); Object.defineProperty(f.output, '4', {writable: false});
    rejects(() => f.runtime.rotateShort('z', f.parent, f.destination, 0), 'non-writable');
    check(f.output[0] === 1 && f.output[1] === 0 && f.output[2] === 19 && f.output[3] === 19,
      'zero rotation retains Concat paired-store prefix');
    rejects(() => f.runtime.rotateShort('x', f.parent, f.destination, 0.5), 'signed short');
    rejects(() => f.runtime.rotateShort('y', f.parent, f.destination, -32768), 'nonzero short rotation');
  }
  {
    const f = fixture(), override = {x: 5, y: 6, z: 7};
    f.feedback.getPose(f.pose).translation.y = NaN;
    f.runtime.composeJoint(f.parent, f.destination, f.pose, zero, unit, override);
    check(f.output[3] === 5 && f.output[7] === 6 && f.output[11] === 7, 'explicit override avoids unused pose translation');
    override.y = 8;
    check(f.output[7] === 6, 'override mutation does not rebuild output');
    f.runtime.composeJoint(f.parent, f.destination, f.pose, zero, unit, override);
    check(f.output[7] === 8, 'override reads actual vector on each call');
    f.feedback.getPose(f.pose).quaternion.x = -0;
    rejects(() => f.runtime.composeJoint(f.parent, f.destination, f.pose, zero, unit, override), 'exact (+0,+0,+0,1)');
    check(f.output[7] === 8, 'override never replaces pose quaternion');
  }
  {
    const f = fixture();
    const override = {x: 5, get y(): number {throw Error('getter must not run');}, z: 7};
    rejects(() => f.runtime.composeJoint(f.parent, f.destination, f.pose, zero, unit, override), 'own data');
    check(f.output.every(v => v === 19), 'override accessor refusal precedes Concat stores');
    f.hooks.get = () => {try {f.runtime.identity(f.destination);} catch { /* test swallowed nested operation */ }};
    rejects(f.compose, 'reentry was caught');
    check(f.output.every(v => v === 19), 'new mutation methods share reentry poison');
    delete f.hooks.get; f.runtime.identity(f.destination); f.compose();
    check(f.output[7] === 3, 'new operation usable after reentry refusal');
  }
  {
    const f = fixture(); f.runtime.getMatrix(f.parent).fill(-0);
    f.feedback.getPose(f.pose).translation.x = -0;
    f.feedback.getPose(f.pose).translation.y = -0;
    f.feedback.getPose(f.pose).translation.z = -0;
    f.runtime.composePose(f.parent, f.destination, f.pose);
    check(Object.is(f.output[1], -0), 'composePose stops after firstConcat, before correction Copy and scale Concat');
    f.runtime.correctShort(f.destination, zero); f.runtime.scale(f.destination, unit);
    check(Object.is(f.output[1], 0), 'caller explicitly owns later correction and scale stages');
  }
  {
    const f = fixture(); f.feedback.getPose(f.pose).translation.y = NaN;
    f.runtime.composePose(f.parent, f.destination, f.pose, {x: 7, y: 8, z: 9});
    check(f.output[3] === 7 && f.output[7] === 8 && f.output[11] === 9, 'composePose override never reads unused pose translation');
    f.feedback.getPose(f.pose).quaternion.x = -0;
    rejects(() => f.runtime.composePose(f.parent, f.destination, f.pose, unit), 'exact (+0,+0,+0,1)');
    check(f.output[7] === 8, 'composePose preserves prior output on quaternion refusal');
  }
  {
    const f = fixture(); f.runtime.composePose(f.parent, f.parent, f.pose);
    f.runtime.composePose(f.parent, f.parent, f.pose);
    check(f.runtime.getMatrix(f.parent)[7] === 6, 'composePose supports actual parent/destination alias');
    Object.defineProperty(f.output, '4', {writable: false});
    rejects(() => f.runtime.composePose(f.parent, f.destination, f.pose), 'non-writable');
    check(f.output[0] === 1 && f.output[1] === 0 && f.output[2] === 19, 'composePose preserves exact firstConcat store prefix');
  }
  {
    const f = fixture(); f.hooks.get = () => {
      try {f.runtime.composePose(f.parent, f.destination, f.pose);} catch { /* swallowed reentry */ }
    };
    rejects(f.compose, 'reentry was caught');
    check(f.output.every(v => v === 19), 'composePose reentry poisons enclosing composeJoint');
    rejects(() => f.runtime.composePose(f.parent, f.destination, f.pose), 'reentry was caught');
    delete f.hooks.get; f.adapter.getPose = () => {throw Error('replacement getter');};
    f.runtime.composePose(f.parent, f.destination, f.pose);
    check(f.output[7] === 3, 'composePose shares captured receiver and recovers after refusal');
  }
  {
    const f = fixture(), point = {x: 2, y: 3, z: 4};
    const matrix = f.runtime.createMatrix([2, 0, 0, 5, 0, 3, 0, 6, 5, 0, 4, 7]);
    f.runtime.transformPoint(matrix, point, point);
    // Row2 must use original X=2, not aliased output X=9 (which yields68).
    check(point.x === 9 && point.y === 15 && point.z === 33, 'MultVec includes translation and retains loaded X through final row of aliased output');
    const output = {x: NaN, y: Infinity, z: 0.1};
    f.runtime.transformPoint(matrix, zero, output);
    check(output.x === 5 && output.y === 6 && output.z === 7, 'MultVec never reads old output values');
  }
  {
    const f = fixture(), output = {...zero}, matrix = f.runtime.createMatrix([
      -1, 0, 1 - 2 ** -23, 0, 2 ** 24, 1, -(2 ** 24), 0, 2 ** 24, -(2 ** 24), 1, 1,
    ]);
    f.runtime.transformPoint(matrix, {x: 1, y: 0, z: 1 + 2 ** -23}, output);
    check(output.x === -(2 ** -46), 'MultVec fused Z/product cancellation differs from rounded multiply then add');
    f.runtime.transformPoint(matrix, unit, output);
    check(output.y === 1 && output.z === 1, 'MultVec uses paired Z+X and translation+Y lanes rather than sequential dot sum');
    const negativeZeros = f.runtime.createMatrix(Array(12).fill(-0));
    f.runtime.transformPoint(negativeZeros, zero, output);
    check(Object.values(output).every(v => Object.is(v, -0)), 'MultVec retains both negative-zero lanes and final negative-zero sum');
  }
  {
    const f = fixture(), output = {...zero}, nearOne = 1 + 2 ** -23;
    const productRounding = f.runtime.createMatrix([
      nearOne, 0, -(1 + 2 ** -22), 0, 0, 1, 0, 0, 0, 0, 1, 0,
    ]);
    // The exact first product contains2^-46. Its required ps_mul rounding
    // removes that residue BEFORE the later fused Z addition cancels it.
    check(nearOne * nearOne - (1 + 2 ** -22) === 2 ** -46, 'initial product-rounding witness has a nonzero exact residue');
    f.runtime.transformPoint(productRounding, {x: nearOne, y: 0, z: 1}, output);
    check(Object.is(output.x, 0), 'MultVec first X-row product rounds to f32 before the fused cancellation');
    const laneOrder = f.runtime.createMatrix([
      2 ** 24, 1, -(2 ** 24), 0, 0, 1, 0, 0, 0, 0, 1, 0,
    ]);
    // Z+X cancels exactly, then translation+Y contributes1. Adding X+Y
    // first instead rounds that1 away, so the reassociated result is0.
    f.runtime.transformPoint(laneOrder, unit, output);
    check(output.x === 1, 'MultVec X-row paired lane order differs from reassociated X+Y then Z');
  }
  {
    const f = fixture(), matrix = f.runtime.getMatrix(f.parent), output = {x: 19, y: 20, z: 21};
    matrix[8] = NaN;
    rejects(() => f.runtime.transformPoint(f.parent, unit, output), 'matrix[8]');
    check(output.x === 1 && output.y === 20 && output.z === 21, 'MultVec X store precedes third-row loads');
    matrix[8] = 0; matrix[10] = NaN;
    rejects(() => f.runtime.transformPoint(f.parent, unit, output), 'matrix[10]');
    check(output.y === 20 && output.z === 21, 'MultVec final matrix pair loads before Y store');
  }
  {
    const f = fixture(), matrix = f.runtime.getMatrix(f.parent), output = {x: 19, y: 20, z: 21};
    Object.defineProperty(output, 'x', {writable: false}); matrix[4] = NaN;
    rejects(() => f.runtime.transformPoint(f.parent, unit, output), 'matrix[4]');
    matrix[4] = 0; matrix[6] = NaN;
    rejects(() => f.runtime.transformPoint(f.parent, unit, output), 'matrix[6]');
    matrix[6] = 0;
    rejects(() => f.runtime.transformPoint(f.parent, unit, output), 'non-writable');
    check(output.x === 19 && output.y === 20, 'MultVec row-one pairs load before first output writability check');
  }
  {
    const f = fixture(), output = {x: 19, y: 20, z: 21};
    Object.defineProperty(output, 'y', {writable: false});
    rejects(() => f.runtime.transformPoint(f.parent, unit, output), 'non-writable');
    check(output.x === 1 && output.y === 20 && output.z === 21, 'MultVec retains X before Y store refusal');
    const accessor = {x: 1, get y(): number {throw Error('must not execute');}, z: 1};
    rejects(() => f.runtime.transformPoint(f.parent, accessor, output), 'own data');
    rejects(() => f.runtime.transformPoint(Symbol(), unit, output), 'unknown/non-owned');
  }
  {
    const f = fixture(), output = {x: 19, y: 20, z: 21};
    const largest = Math.fround(3.4028234663852886e38), matrix = f.runtime.getMatrix(f.parent);
    matrix[4] = largest;
    rejects(() => f.runtime.transformPoint(f.parent, {x: 2, y: 1, z: 1}, output), 'single product');
    check(output.x === 19, 'MultVec second-row product overflow precedes X store');
    matrix[4] = 0; matrix[6] = largest;
    rejects(() => f.runtime.transformPoint(f.parent, {x: 1, y: 1, z: 2}, output), 'overflow');
    check(output.x === 1 && output.y === 20, 'MultVec second-row FMA overflow retains X');
    matrix[6] = 0; matrix[10] = largest;
    rejects(() => f.runtime.transformPoint(f.parent, {x: 1, y: 1, z: 2}, output), 'overflow');
    check(output.y === 1 && output.z === 21, 'MultVec final FMA overflow retains X and Y');
  }
  {
    const f = fixture();
    f.runtime.orientTerrainMatrix(f.parent, {x: 0, y: 1, z: 0}, 2, 1);
    const matrix = f.runtime.getMatrix(f.parent);
    check([0, 5, 10].every(i => bits(matrix[i]!) === 0x3f7ffffe), 'real unit Mag/refinement/Normalize/rescale is two ULPs below identity');
    check(matrix.every((value, i) => i === 0 || i === 5 || i === 10 || Object.is(value, 0)),
      'unit orientation final offdiagonals have Concat positive-zero signs');
    const completed = matrix.slice();
    rejects(() => f.runtime.orientTerrainMatrix(f.parent, {x: 0, y: 1, z: 0}, 2, 1), 'finite estimate proof domain');
    check(matrix.every((v, i) => Object.is(v, completed[i])), 'repeated correction refuses shrunken basis rather than extending estimate domain');
  }
  {
    // Independent closed-form expectation for all 5^3 scales and 2^3 signs.
    // The selected reference X determines orientation; old Y/Z signs affect
    // their saved magnitudes only. An ideal sqrt/normalize/identity would fail.
    const f = fixture(), matrix = f.runtime.getMatrix(f.parent), q2 = 1 - 2 ** -23;
    const magnitudes = [0.5, 1, 2, 4, 8];
    let samples = 0;
    for (const mx of magnitudes) for (const my of magnitudes) for (const mz of magnitudes) {
      for (const sx of [-1, 1]) for (const sy of [-1, 1]) for (const sz of [-1, 1]) {
        matrix.splice(0, 12, sx * mx, -0, 0, 5, -0, sy * my, -0, -3, 0, -0, sz * mz, 7);
        f.runtime.orientTerrainMatrix(f.parent, {x: -0, y: 1, z: -0}, 2, 1);
        check(Object.is(matrix[0], sx * mx * q2) && Object.is(matrix[5], my * q2) &&
          Object.is(matrix[10], sx * mz * q2), `finite estimate/rescale domain sample ${samples}`);
        check(matrix[3] === 5 && matrix[7] === -3 && matrix[11] === 7, 'terrain rescale preserves real translation');
        samples++;
      }
    }
    check(samples === 1000, 'finite-domain scale/sign check is nonvacuous');
  }
  {
    const f = fixture(), initial = [0, 4, 0, 6, 0, 0, 0.5, -3, 2, 0, 0, 7];
    const matrix = f.runtime.createMatrix(initial);
    f.runtime.orientTerrainMatrix(matrix, {x: 0, y: 1, z: 0}, 2, 1);
    const expected = [0, 0, -0.5 * (1 - 2 ** -23), 6, 0, 4 * (1 - 2 ** -23), 0, -3,
      2 * (1 - 2 ** -23), 0, 0, 7];
    check(f.runtime.getMatrix(matrix).every((v, i) => Object.is(v, expected[i])), 'signed permutation chooses actual reference column and restores each original magnitude');
  }
  {
    const f = fixture(), q2 = 1 - 2 ** -23;
    const id = f.runtime.createMatrix([-1, 0, 0, -0, -0, 1, 0, -0, 0, 0, 1, -0]);
    f.runtime.orientTerrainMatrix(id, {x: -0, y: 1, z: 0}, 2, 1);
    const expected = [-q2, -0, -0, -0, 0, q2, 0, 0, 0, 0, -q2, 0];
    check(f.runtime.getMatrix(id).every((v, i) => Object.is(v, expected[i])),
      'cross/normalization/Concat preserves negative-zero basis lanes and applies actual translation zero signs');
  }
  {
    const f = fixture(), matrix = f.runtime.getMatrix(f.parent), q = 1 - 2 ** -24;
    matrix[3] = NaN;
    rejects(() => f.runtime.orientTerrainMatrix(f.parent, {x: 0, y: 1, z: 0}, 2, 1), 'matrix[3]');
    const oriented = [q, 0, 0, NaN, -0, q, -0, 0, -0, 0, q, 0];
    check(matrix.every((v, i) => Object.is(v, oriented[i])), 'translation refusal retains all real normalized stores, including cross negative zeros');
    check(bits(matrix[0]!) === 0x3f7fffff && bits(matrix[5]!) === 0x3f7fffff && bits(matrix[10]!) === 0x3f7fffff,
      'intermediate normalization is one ULP below1, distinct from final rescale');
  }
  {
    const order = [0, 4, 8, 1, 5, 9, 2, 6, 10], q = 1 - 2 ** -24;
    const initial = [0, 4, 0, 6, 0, 0, 0.5, -3, 2, 0, 0, 7];
    const oriented = [0, 0, -q, 6, -0, q, -0, -3, q, 0, -0, 7];
    for (let stop = 0; stop < order.length; stop++) {
      const f = fixture(), id = f.runtime.createMatrix(initial), matrix = f.runtime.getMatrix(id);
      Object.defineProperty(matrix, String(order[stop]), {writable: false});
      rejects(() => f.runtime.orientTerrainMatrix(id, {x: 0, y: 1, z: 0}, 2, 1), 'non-writable');
      const expected = initial.slice(); for (const i of order.slice(0, stop)) expected[i] = oriented[i]!;
      check(matrix.every((v, i) => Object.is(v, expected[i])), `terrain exact column-major write prefix ${stop}`);
    }
  }
  {
    const f = fixture(), matrix = f.runtime.getMatrix(f.parent), q = 1 - 2 ** -24, q2 = 1 - 2 ** -23;
    matrix[3] = -0; Object.defineProperty(matrix, '3', {writable: false});
    rejects(() => f.runtime.orientTerrainMatrix(f.parent, {x: 0, y: 1, z: 0}, 2, 1), 'non-writable');
    check(Object.is(matrix[0], q2) && Object.is(matrix[5], q2) && Object.is(matrix[4], 0) &&
      Object.is(matrix[6], -0) && Object.is(matrix[8], -0) && matrix[10] === q && Object.is(matrix[3], -0),
      'terrain final rescale uses actual Concat store order after all orientation writes');
  }
  {
    const f = fixture(), matrix = f.runtime.getMatrix(f.parent), flat = {x: 0, y: 1, z: 0};
    for (const axes of [[1, 2], [2, -1], [-2, 1], [2, 0], [2, 1.5], [NaN, 1]]) {
      rejects(() => f.runtime.orientTerrainMatrix(f.parent, flat, axes[0]!, axes[1]!), 'positive terrain axes');
      check(matrix.every((v, i) => Object.is(v, identity[i])), 'unsupported axes refuse without a guessed constructor');
    }
    for (const normal of [{x: 0, y: 0, z: 0}, {x: 0, y: -1, z: 0}, {x: 2 ** -149, y: 1, z: 0}]) {
      rejects(() => f.runtime.orientTerrainMatrix(f.parent, normal, 2, 1), 'only flat');
    }
    for (const value of [0, 0.25, 0.5 - 2 ** -25, 1 - 2 ** -24, 1 + 2 ** -23, 16]) {
      matrix[0] = value;
      rejects(() => f.runtime.orientTerrainMatrix(f.parent, flat, 2, 1), 'proof domain');
      check(Object.is(matrix[0], value) && matrix[5] === 1 && matrix[10] === 1, 'out-of-proof magnitudes refuse without output');
    }
    matrix[0] = 1; matrix[4] = 1;
    rejects(() => f.runtime.orientTerrainMatrix(f.parent, flat, 2, 1), 'signed-axis');
    matrix[4] = 0; matrix[1] = 1; matrix[5] = 0;
    rejects(() => f.runtime.orientTerrainMatrix(f.parent, flat, 2, 1), 'three distinct');
    matrix.splice(0, 12, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0);
    const before = matrix.slice();
    rejects(() => f.runtime.orientTerrainMatrix(f.parent, flat, 2, 1), 'fallback construction');
    check(matrix.every((v, i) => Object.is(v, before[i])), 'failed first constructor never synthesizes fallback');
  }
  {
    const f = fixture(), matrix = f.runtime.getMatrix(f.parent);
    matrix[0] = 0.25; matrix[10] = NaN;
    rejects(() => f.runtime.orientTerrainMatrix(f.parent, {x: NaN, y: 1, z: 0}, 2, 1), 'matrix[10]');
    matrix[10] = 1;
    rejects(() => f.runtime.orientTerrainMatrix(f.parent, {x: NaN, y: 1, z: 0}, 2, 1), 'proof domain');
    matrix[0] = 1;
    rejects(() => f.runtime.orientTerrainMatrix(f.parent, {x: NaN, y: 1, z: 0}, 2, 1), 'normal.x');
    const normal = {x: 0, get y(): number {throw Error('must not execute');}, z: 0};
    rejects(() => f.runtime.orientTerrainMatrix(f.parent, normal, 2, 1), 'own data');
    rejects(() => f.runtime.orientTerrainMatrix(Symbol(), {x: 0, y: 1, z: 0}, 2, 1), 'unknown/non-owned');
    check(matrix.every((v, i) => Object.is(v, identity[i])), 'ordered loads, magnitude proof, then normal validation leave no output writes');
  }
  {
    const f = fixture();
    for (const nested of [() => f.runtime.transformPoint(f.parent, zero, {...zero}),
      () => f.runtime.orientTerrainMatrix(f.parent, {x: 0, y: 1, z: 0}, 2, 1)]) {
      f.hooks.get = () => {try {nested();} catch { /* out-of-contract adapter */ }};
      rejects(f.compose, 'reentry was caught');
      check(f.output.every(v => v === 19), 'new matrix primitives participate in runtime reentry poison');
    }
    delete f.hooks.get; f.compose();
    check(f.output[7] === 3, 'matrix runtime recovers after new primitive reentry refusal');
  }
  {
    // Each bend executes both real rotations/concats; the second matrix folds
    // the relevant columns while its translation uses the retained raw pose.
    const qSquared = 1 - 2 ** -23;
    for (const bend of [1, 2, 3, 255, 254, 253]) {
      const f = primaryFixture(), oldEnd = f.endMatrix.slice(); f.correction.bend0f = bend;
      f.run();
      check([0, 5, 10].every(i => bits(f.currentMatrix[i]!) === 0x3f7ffffe), 'primary retains actual orientation refinement, not an ideal identity');
      const axis = Math.abs((bend << 24) >> 24) - 1;
      for (let column = 0; column < 3; column++) {
        check(Object.is(f.nextMatrix[column * 5], column === axis ? qSquared : -qSquared), 'second real RotTrig flips two basis columns');
      }
      check(Object.is(f.nextMatrix[7], 2 * qSquared), 'second Concat consumes adjacent raw translation and rounded current scale');
      check(f.endMatrix.every((value, i) => Object.is(value, oldEnd[i])), 'primary leaves the retained end matrix unchanged');
      check(f.nextMatrix[7] !== f.correction.y, 'minimum-reach case does not falsely claim target endpoint success');
    }
  }
  {
    // Retained displacements can occupy either sign of every axis. The true
    // lengths come from SquareDistance and the three binary64 refinements.
    for (const firstAxis of [0, 1, 2]) for (const secondAxis of [0, 1, 2]) for (const sign of [-1, 1]) {
      const f = primaryFixture();
      f.nextMatrix[7] = 0; f.endMatrix[7] = 0;
      f.nextMatrix[3 + firstAxis * 4] = 2 * sign;
      f.endMatrix[3 + firstAxis * 4] = 2 * sign;
      f.endMatrix[3 + secondAxis * 4]! += -0.5 * sign;
      f.run(); check(bits(f.nextMatrix[5]!) === 0xbf7ffffe, 'signed-axis retained geometry actually measures2/.5');
    }
  }
  {
    // A negative reference axis makes the complement's and second sine's
    // zero signs observable after actual paired-single Concat cancellation.
    for (const bend of [1, 255]) {
      const f = primaryFixture(); f.currentMatrix[0] = -1; f.correction.bend0f = bend;
      f.run();
      check(Object.is(f.nextMatrix[1], bend === 1 ? -0 : 0),
        'negative reference axis exposes exact complement and negative-bend sine zero signs');
    }
    for (const bend of [1, 255]) {
      const f = primaryFixture(); f.currentMatrix[0] = -1; f.correction.z = -0; f.correction.bend0f = bend;
      f.run();
      check(Object.is(f.currentMatrix[9], bend === 1 ? -0 : 0),
        'first real Concat and positive-bend sine negation retain source signed-zero effects');
      if (bend === 1) check(Object.is(f.nextMatrix[8], -0),
        'positive first sine negation affects later second Concat signed zero');
    }
  }
  {
    const f = primaryFixture(); f.translation.x = 3; f.translation.y = 4; f.translation.z = 5;
    f.correction.x = 3; f.correction.y = 5; f.correction.z = 5;
    f.nextTranslation.x = 7; f.nextTranslation.y = 8; f.nextTranslation.z = 9;
    f.run();
    check(f.currentMatrix[3] === 3 && f.currentMatrix[7] === 4 && f.currentMatrix[11] === 5,
      'primary transforms raw current translation, not retained world origin or target height');
    check(f.nextMatrix[3] === Math.fround(3 + Math.fround(7 * (1 - 2 ** -23))) &&
      f.nextMatrix[7] === Math.fround(4 + Math.fround(8 * (1 - 2 ** -23))) &&
      f.nextMatrix[11] === Math.fround(5 + Math.fround(9 * (1 - 2 ** -23))), 'second Concat uses all three raw next pose coordinates, not measured old offset');
  }
  {
    const f = primaryFixture(); f.nextMatrix[0] = NaN; f.endMatrix[10] = NaN;
    f.run(); check(Number.isFinite(f.nextMatrix[0]!) && Number.isNaN(f.endMatrix[10]),
      'retained next/end read only translation; second Concat overwrites without reading destination basis');
  }
  {
    const f = primaryFixture(); f.currentMatrix[3] = 8; f.nextMatrix[3] = 8; f.endMatrix[3] = 8;
    f.translation.x = 3; f.translation.y = 4; f.translation.z = 5;
    Object.defineProperty(f.currentMatrix, '7', {writable: false});
    rejects(f.run, 'non-writable');
    check(f.currentMatrix[3] === 3 && f.currentMatrix[7] === 0 && f.currentMatrix[11] === 0,
      'primary retains X translation before Y translation store refusal');
  }
  {
    const f = primaryFixture(); f.translation.x = 3; f.correction.x = NaN;
    rejects(f.run, 'primary target.x');
    check(f.currentMatrix[3] === 3 && f.currentMatrix[5] === 1 && f.nextMatrix[7] === 2,
      'target read failure is late, after all current translation stores');
  }
  {
    const f = primaryFixture(); f.translation.z = 5; f.correction.z = 5; f.correction.axis0e = 255;
    rejects(f.run, 'positive terrain axes');
    check(f.currentMatrix[11] === 5 && f.currentMatrix[0] === 1 && f.nextMatrix[7] === 2,
      'signed unsupported axis preserves translation without synthesizing orientation');
  }
  {
    for (const key of ['axis0d', 'axis0e'] as const) {
      const f = primaryFixture();
      f.translation.x = 3; f.translation.y = 4; f.translation.z = 5;
      f.correction.x = 3; f.correction.y = 5; f.correction.z = 5;
      f.correction[key] = key === 'axis0d' ? NaN : 256;
      rejects(f.run, `${key}: raw byte`);
      check(f.currentMatrix[3] === 3 && f.currentMatrix[7] === 4 && f.currentMatrix[11] === 5 &&
        f.currentMatrix[0] === 1 && f.nextMatrix[7] === 2,
        'invalid raw axis byte is read only after all current translation stores');
      const accessor = primaryFixture(); accessor.translation.x = 3; accessor.correction.x = 3;
      Object.defineProperty(accessor.correction, key, {get() {throw Error('must not execute');}});
      rejects(accessor.run, 'own data');
      check(accessor.currentMatrix[3] === 3 && accessor.currentMatrix[0] === 1,
        'axis accessor refusal preserves earlier translation, without invoking accessor');
      const competing = primaryFixture(); competing.translation.x = 3;
      competing.correction[key] = NaN;
      Object.defineProperty(competing.currentMatrix, '7', {writable: false});
      rejects(competing.run, 'non-writable');
      check(competing.currentMatrix[3] === 3 && competing.currentMatrix[11] === 0,
        'translation-store refusal takes precedence over later malformed axis byte');
    }
  }
  {
    const f = primaryFixture(); f.correction.bend0f = 0;
    rejects(f.run, 'primary bend axis');
    check(bits(f.currentMatrix[0]!) === 0x3f7ffffe && f.nextMatrix[0] === 1 && f.nextMatrix[7] === 2,
      'unsupported bend refuses only after complete orientation, before either primary Concat');
    const accessor = primaryFixture();
    Object.defineProperty(accessor.correction, 'bend0f', {get() {throw Error('must not execute');}});
    rejects(accessor.run, 'own data');
    check(bits(accessor.currentMatrix[0]!) === 0x3f7ffffe, 'late bend accessor refusal retains completed orientation');
  }
  {
    const f = primaryFixture(); f.nextMatrix[7] = 4; f.endMatrix[7] = 4.5;
    f.nextTranslation.z = NaN; f.endMatrix[11] = NaN;
    rejects(f.run, 'primary next.z');
    f.nextTranslation.z = 0;
    rejects(f.run, 'matrix[11]');
    f.endMatrix[11] = 0;
    rejects(f.run, 'retained bone length');
    check(f.currentMatrix.every((value, i) => Object.is(value, identity[i])),
      'raw next loads, all retained positions, then length-domain refusal precede current output stores');
  }
  {
    const f = primaryFixture(); f.correction.y = 2;
    rejects(f.run, 'only flat'); check(f.currentMatrix[0] === 1 && f.nextMatrix[7] === 2,
      'unadmitted target direction/distance does not replace source normalization with arbitrary sqrt');
  }
  {
    const f = primaryFixture(); Object.defineProperty(f.nextMatrix, '4', {writable: false});
    rejects(f.run, 'non-writable');
    check(bits(f.currentMatrix[5]!) === 0x3f7ffffe && bits(f.nextMatrix[0]!) === 0x3f7ffffe &&
      f.nextMatrix[2] === 0 && f.nextMatrix[5] === 1 && f.nextMatrix[7] === 2,
      'second primary Concat retains first destination pair and fully completed current matrix');
  }
  {
    // The retained unit pair exercises both strictly-positive sine branches.
    // Every component is checked, including raw-pose translation and zero bits.
    for (const bend of [1, 2, 3, 255, 254, 253]) for (const x of [0, -0]) for (const z of [0, -0]) {
      const f = positivePrimaryFixture(), expected = positivePrimaryExpected(bend), oldEnd = f.endMatrix.slice();
      f.correction.bend0f = bend; f.correction.x = x; f.correction.z = z;
      f.run();
      check(f.currentMatrix.every((v, i) => Object.is(v, expected.current[i])),
        `unit-pair first real rotation/Concat for signed bend${bend}`);
      check(f.nextMatrix.every((v, i) => Object.is(v, expected.next[i])),
        `unit-pair second real rotation/Concat for signed bend${bend}`);
      check(f.endMatrix.every((v, i) => Object.is(v, oldEnd[i])), 'positive-sine placement retains end matrix');
    }
  }
  {
    // The first and second retained bones independently occupy either sign of
    // any axis. Their magnitudes are measured, not inferred from raw poses.
    for (const firstAxis of [0, 1, 2]) for (const secondAxis of [0, 1, 2]) {
      for (const firstSign of [-1, 1]) for (const secondSign of [-1, 1]) {
        const f = positivePrimaryFixture(), expected = positivePrimaryExpected(1);
        f.nextMatrix[7] = 0; f.endMatrix[7] = 0;
        f.nextMatrix[3 + firstAxis * 4] = firstSign;
        f.endMatrix[3 + firstAxis * 4] = firstSign;
        f.endMatrix[3 + secondAxis * 4]! += secondSign;
        f.run();
        check(f.currentMatrix.every((v, i) => Object.is(v, expected.current[i])) &&
          f.nextMatrix.every((v, i) => Object.is(v, expected.next[i])), 'signed-axis unit-pair SquareDistance/refinement geometry');
      }
    }
  }
  {
    // Terrain's separately exhaustive scale-domain tests remain above. Here
    // each of its five magnitudes and eight signs also reaches both new sines
    // and all six primary bends, with exact row-scaled expected nonzero values.
    const magnitudes = [0.5, 1, 2, 4, 8];
    let samples = 0;
    for (let index = 0; index < magnitudes.length; index++) {
      const mx = magnitudes[index]!, my = magnitudes[(index + 1) % 5]!, mz = magnitudes[(index + 2) % 5]!;
      for (const sx of [-1, 1]) for (const sy of [-1, 1]) for (const sz of [-1, 1]) {
        for (const bend of [1, 2, 3, 255, 254, 253]) {
          const f = positivePrimaryFixture(), expected = positivePrimaryExpected(bend), factors = [sx * mx, my, sx * mz];
          f.currentMatrix[0] = sx * mx; f.currentMatrix[5] = sy * my; f.currentMatrix[10] = sz * mz;
          f.correction.bend0f = bend; f.run();
          for (const [actual, reference] of [[f.currentMatrix, expected.current], [f.nextMatrix, expected.next]]) {
            check(actual!.every((v, i) => {
              const value = reference![i]!; return value === 0 ? v === 0 : Object.is(v, value * factors[Math.floor(i / 4)]!);
            }), 'positive-sine signed/scaled basis preserves source orientation and both real Concats');
          }
          samples++;
        }
      }
    }
    check(samples === 240, 'positive-sine scale/sign/bend coverage is nonvacuous');
    for (const sign of [-1, 1]) for (const bend of [1, 2, 3, 255, 254, 253]) {
      const f = positivePrimaryFixture(), expected = positivePrimaryExpected(bend);
      f.currentMatrix.splice(0, 12, 0, -4, 0, 0, 0, 0, -0.5, 0, sign * 2, 0, 0, 0);
      f.correction.bend0f = bend; f.run();
      for (const [actual, reference] of [[f.currentMatrix, expected.current], [f.nextMatrix, expected.next]]) {
        check(actual!.every((v, i) => {
          const row = Math.floor(i / 4), value = reference![[2, 1, 0][row]! * 4 + i % 4]!;
          return value === 0 ? v === 0 : Object.is(v, value * [-sign * 0.5, 4, sign * 2][row]!);
        }), 'positive-sine signed permutation uses the actual selected reference column');
      }
    }
    // With reference-X negative, these exact zero signs survive the second
    // Concat. Row scaling of abstract rotation matrices cannot predict them.
    for (const [bend, slot] of [[255, 1], [3, 9], [253, 8]]) {
      const f = positivePrimaryFixture();
      f.currentMatrix[0] = -2; f.currentMatrix[5] = -4; f.currentMatrix[10] = 0.5;
      f.correction.bend0f = bend!; f.run();
      check(Object.is(f.nextMatrix[slot!], -0), 'positive-sine signed basis retains exact paired Concat negative zero');
    }
  }
  {
    const order = [0, 1, 4, 5, 2, 3, 6, 7, 8, 9, 10, 11];
    for (const bend of [1, 2, 3, 255, 254, 253]) for (let stop = 0; stop < order.length; stop++) {
      const f = positivePrimaryFixture(), expected = positivePrimaryExpected(bend), priorNext = f.nextMatrix.slice();
      f.correction.bend0f = bend;
      Object.defineProperty(f.nextMatrix, String(order[stop]), {writable: false});
      rejects(f.run, 'non-writable');
      for (const i of order.slice(0, stop)) priorNext[i] = expected.next[i]!;
      check(f.currentMatrix.every((v, i) => Object.is(v, expected.current[i])) &&
        f.nextMatrix.every((v, i) => Object.is(v, priorNext[i])),
        `positive-sine second Concat exact store prefix${stop}, bend${bend}`);
    }
  }
  {
    for (const bend of [0, 4, 127, 128, 252, 256, NaN]) {
      const f = positivePrimaryFixture(), oldNext = f.nextMatrix.slice(); f.correction.bend0f = bend;
      rejects(f.run, bend >= 0 && bend <= 255 ? 'primary bend axis' : 'bend0f: raw byte');
      check([0, 5, 10].every(i => bits(f.currentMatrix[i]!) === 0x3f7ffffe) &&
        f.nextMatrix.every((v, i) => Object.is(v, oldNext[i])), 'unit-pair invalid bend is late after orientation, before primary Concats');
    }
    const accessor = positivePrimaryFixture();
    Object.defineProperty(accessor.correction, 'bend0f', {get() {throw Error('must not execute');}});
    rejects(accessor.run, 'own data');
    check(bits(accessor.currentMatrix[0]!) === 0x3f7ffffe && accessor.nextMatrix[7] === 1,
      'unit-pair late bend accessor preserves orientation without invoking getter');
    for (const target of [NaN, 2]) {
      const f = positivePrimaryFixture(); f.translation.x = 3; f.correction.x = 3; f.correction.y = target;
      rejects(f.run, Number.isNaN(target) ? 'primary target.y' : 'only flat');
      check(f.currentMatrix[3] === 3 && f.currentMatrix[0] === 1 && f.nextMatrix[7] === 1,
        'unit-pair target refusal retains translation but never invents an orientation');
    }
  }
  {
    // No accidental widening to all five power-length pairs, including pairs
    // that individually have valid estimate seeds but are not this proof case.
    let rejected = 0;
    for (const first of [0.5, 1, 2, 4, 8]) for (const second of [0.5, 1, 2, 4, 8]) {
      if ((first === 2 && second === 0.5) || (first === 1 && second === 1)) continue;
      const f = positivePrimaryFixture(); f.nextMatrix[7] = first; f.endMatrix[7] = first + second;
      f.translation.x = 3;
      const oldNext = f.nextMatrix.slice(), oldEnd = f.endMatrix.slice();
      rejects(f.run, 'primary retained bone length');
      check(f.currentMatrix.every((v, i) => Object.is(v, identity[i])) &&
        f.nextMatrix.every((v, i) => Object.is(v, oldNext[i])) && f.endMatrix.every((v, i) => Object.is(v, oldEnd[i])),
        'unadmitted length pair refuses before all output stores');
      rejected++;
    }
    check(rejected === 23, 'only two retained pairs admitted from the five-power Cartesian domain');
    const f = positivePrimaryFixture(); f.nextMatrix[7] = 2; f.endMatrix[7] = 3; // Rejected pair(2,1).
    f.endMatrix[11] = NaN; f.nextTranslation.z = NaN;
    rejects(f.run, 'primary next.z'); f.nextTranslation.z = 0;
    rejects(f.run, 'matrix[11]'); f.endMatrix[11] = 0;
    rejects(f.run, 'primary retained bone length');
    check(f.currentMatrix.every((v, i) => Object.is(v, identity[i])),
      'new pair selection retains raw next, all old positions, then distance/refinement admission order');
  }
  {
    const f = primaryFixture();
    rejects(() => f.runtime.primaryFoldedPlacement(f.parent, f.current, f.current, f.end,
      f.translation, f.nextTranslation, f.correction), 'must be distinct');
    rejects(() => f.runtime.primaryFoldedPlacement(Symbol(), f.current, f.next, f.end,
      f.translation, f.nextTranslation, f.correction), 'unknown/non-owned');
    f.hooks.get = () => {try {f.run();} catch { /* caught nested effect remains poisoned */ }};
    rejects(f.compose, 'reentry was caught');
    check(f.currentMatrix[0] === 1 && f.nextMatrix[7] === 2, 'primary entry participates in same-runtime reentry poison');
    delete f.hooks.get; f.run(); check(bits(f.currentMatrix[0]!) === 0x3f7ffffe, 'primary runtime recovers after refusal');
  }
}

/** The byte sink has the same authenticated 8020b7a8 arithmetic/load schedule
 * as the vector sink. Expected words below are independent dyadic witnesses,
 * not values obtained by invoking transformPoint or a production FP helper.
 * Evidence: terrain-orientation-evidence-2026-11-13.md, "Secondary effect and
 * point transformation". These are bounded host tests, not console parity. */
export function runActorJointMatrixBytesSelfTests(): void {
  const base = 0x20, sentinel = 0xa5;
  const normal = [2, 0, 0, 5, 0, 3, 0, 6, 5, 0, 4, 7];
  const expected = [0x41100000, 0x41700000, 0x42040000]; // 9,15,33.
  const point = {x: 2, y: 3, z: 4};
  type Bytes = Partial<Record<number, number>>;
  function bytes(offset = base, old = sentinel): Bytes {
    const result: Bytes = Object.create(null) as Bytes;
    for (let i = -1; i <= 12; i++) result[offset + i] = old;
    return result;
  }
  function expectWords(output: Bytes, words: readonly number[], why: string, offset = base): void {
    for (let i = 0; i < words.length * 4; i++) {
      check(output[offset + i] === ((words[i >>> 2]! >>> ((3 - i % 4) * 8)) & 255), `${why}, byte${i}`);
    }
  }
  function expectPrefix(output: Bytes, before: ReturnType<typeof Object.getOwnPropertyDescriptors>,
    completed: number, why: string, words: readonly number[] = expected): void {
    expectWords(output, words.slice(0, completed), why);
    for (const key of Object.keys(before)) {
      const offset = Number(key);
      if (offset >= base && offset < base + completed * 4) continue;
      const old = before[key]!, current = Object.getOwnPropertyDescriptor(output, key);
      check(current !== undefined && current.value === old.value && current.get === old.get &&
        current.set === old.set && current.writable === old.writable &&
        current.configurable === old.configurable && current.enumerable === old.enumerable,
      `${why}, retained descriptor${key}`);
    }
  }
  {
    const f = fixture(), matrix = f.runtime.createMatrix(normal), output = bytes();
    const held = output, before = Object.getOwnPropertyDescriptors(output);
    f.runtime.transformPointBytes(matrix, point, output, base);
    check(output === held, 'byte transform keeps the canonical backing identity');
    expectPrefix(output, before, 3, 'normal transform exact BE bytes and untouched guards');
    check(f.runtime.getMatrix(matrix).every((v, i) => Object.is(v, normal[i])), 'byte transform leaves source matrix intact');
    // Existing destination bytes are stores, not source values to be validated.
    for (let i = 0; i < 12; i++) output[base + i] = [NaN, Infinity, -1, 0.1][i % 4]!;
    f.runtime.transformPointBytes(matrix, zero, output, base);
    expectWords(output, [0x40a00000, 0x40c00000, 0x40e00000], 'old destination values are never loaded');
  }
  {
    const f = fixture(), output = bytes(), nearOne = 1 + 2 ** -23;
    const cases = [
      {row: [-1, 0, 1 - 2 ** -23, 0], input: {x: 1, y: 0, z: nearOne}, word: 0xa8800000,
        why: 'fused cancellation retains exact -2^-46'},
      {row: [nearOne, 0, -(1 + 2 ** -22), 0], input: {x: nearOne, y: 0, z: 1}, word: 0,
        why: 'first product rounds before the later fused cancellation'},
      {row: [2 ** 24, 1, -(2 ** 24), 0], input: unit, word: 0x3f800000,
        why: 'Z+X and translation+Y paired lanes are not reassociated'},
      {row: [2 ** 24, -(2 ** 24), 1, 1], input: unit, word: 0x3f800000,
        why: 'each fused lane rounds before the final sum'},
      {row: [1, 0, 0, 2 ** -24], input: unit, word: 0x3f800000,
        why: 'final halfway sum rounds down to even'},
      {row: [nearOne, 0, 0, 2 ** -24], input: unit, word: 0x3f800002,
        why: 'final halfway sum rounds up to even'},
      {row: [-0, -0, -0, -0], input: zero, word: 0x80000000,
        why: 'two negative-zero lanes retain a negative-zero result'},
      {row: [-0, 0, -0, 0], input: zero, word: 0,
        why: 'opposite zero signs produce positive zero'},
    ];
    for (const {row, input, word, why} of cases) {
      const matrix = f.runtime.createMatrix([...row, ...row, ...row]);
      f.runtime.transformPointBytes(matrix, input, output, base);
      expectWords(output, [word, word, word], why);
    }
    f.runtime.transformPointBytes(f.parent, {x: 2 ** -149, y: -(2 ** -149), z: fromBits(0x7f7fffff)}, output, base);
    expectWords(output, [1, 0x80000001, 0x7f7fffff], 'identity preserves admitted finite extremes and gradual underflow');
    f.runtime.transformPointBytes(f.parent, {x: -0, y: -0, z: -0}, output, base);
    expectWords(output, [0, 0, 0], 'identity still executes source zero-sign arithmetic');
  }
  {
    const f = fixture(), matrix = f.runtime.createMatrix(normal);
    const aliased = Object.assign(bytes(), point);
    f.runtime.transformPointBytes(matrix, aliased, aliased, base);
    expectWords(aliased, expected, 'input and destination may be the same own-data record');
    check(aliased.x === 2 && aliased.y === 3 && aliased.z === 4, 'numeric byte stores leave aliased XYZ fields intact');
    aliased.x = 3;
    f.runtime.transformPointBytes(matrix, aliased, aliased, base);
    expectWords(aliased, [0x41300000, 0x41700000, 0x42180000], 'next explicit call reloads live aliased input');
    // A matrix array is also ordinary own-data byte storage. Rows that the
    // first word overwrites were already loaded; later rows are loaded lazily.
    const source = f.runtime.getMatrix(matrix);
    f.runtime.transformPointBytes(matrix, point, source, 0);
    expectWords(source, expected, 'matrix and byte destination alias follows loaded-source schedule', 0);
    check(f.runtime.getMatrix(matrix) === source, 'matrix byte alias retains its owned array identity');
  }
  {
    // Every byte participates in whole-word admission. An invalid fourth byte
    // cannot leave three new bytes, and an invalid later word cannot undo X/Y.
    for (const fault of ['missing', 'inherited', 'readonly', 'accessor'] as const) {
      for (let i = 0; i < 12; i++) {
        const f = fixture(), matrix = f.runtime.createMatrix(normal), output = bytes(), key = base + i;
        let accessorCalls = 0;
        if (fault === 'missing' || fault === 'inherited') delete output[key];
        if (fault === 'inherited') Object.setPrototypeOf(output, {[key]: sentinel});
        if (fault === 'readonly') Object.defineProperty(output, key, {writable: false});
        if (fault === 'accessor') Object.defineProperty(output, key, {
          get() {accessorCalls++; return sentinel;}, set(_value: number) {accessorCalls++;}, configurable: true,
        });
        const before = Object.getOwnPropertyDescriptors(output);
        rejects(() => f.runtime.transformPointBytes(matrix, point, output, base),
          fault === 'readonly' ? 'non-writable' : 'own data');
        expectPrefix(output, before, i >>> 2, `${fault} byte${i} rejects its entire word`);
        if (fault === 'missing' || fault === 'inherited') check(!Object.hasOwn(output, key), 'failed admission never invents missing byte');
        check(accessorCalls === 0, 'byte admission never invokes destination accessors');
      }
    }
  }
  {
    for (let i = 0; i < 12; i++) {
      const f = fixture(), matrix = f.runtime.createMatrix(normal), output = bytes();
      const before = Object.getOwnPropertyDescriptors(output);
      f.runtime.getMatrix(matrix)[i] = NaN;
      rejects(() => f.runtime.transformPointBytes(matrix, point, output, base), `matrix[${i}]`);
      expectPrefix(output, before, i < 8 ? 0 : 1, `matrix${i} load fault preserves only source-scheduled words`);
    }
    for (const i of [4, 5, 6, 7, 8, 9, 10, 11]) {
      const f = fixture(), matrix = f.runtime.createMatrix(normal), output = bytes();
      // Second-row loads precede X admission; third-row loads follow it but
      // precede Y admission, including the final pair at b7e0.
      const blockedWord = i < 8 ? 0 : 1;
      Object.defineProperty(output, base + blockedWord * 4, {writable: false});
      f.runtime.getMatrix(matrix)[i] = Infinity;
      const before = Object.getOwnPropertyDescriptors(output);
      rejects(() => f.runtime.transformPointBytes(matrix, point, output, base), `matrix[${i}]`);
      expectPrefix(output, before, blockedWord, `matrix${i} is reached before its competing destination fault`);
    }
    const f = fixture(), output = bytes();
    Object.defineProperty(output, base, {writable: false});
    f.runtime.getMatrix(f.parent)[8] = NaN;
    rejects(() => f.runtime.transformPointBytes(f.parent, unit, output, base), 'non-writable');
    check(output[base] === sentinel && output[base + 4] === sentinel, 'X admission precedes any third-row load');
  }
  {
    const largest = fromBits(0x7f7fffff);
    const cases = [
      {row: 0, lane: 'product', completed: 0}, {row: 1, lane: 'product', completed: 0},
      {row: 2, lane: 'product', completed: 1}, {row: 0, lane: 'fma', completed: 0},
      {row: 1, lane: 'fma', completed: 1}, {row: 2, lane: 'fma', completed: 2},
      {row: 0, lane: 'sum', completed: 0}, {row: 1, lane: 'sum', completed: 1},
      {row: 2, lane: 'sum', completed: 2},
    ];
    for (const {row, lane, completed} of cases) {
      const f = fixture(), matrix = f.runtime.createMatrix(normal), source = f.runtime.getMatrix(matrix), output = bytes();
      source[row * 4] = lane === 'product' ? largest : 0;
      source[row * 4 + 1] = lane === 'sum' ? largest / 2 : 0;
      source[row * 4 + 2] = lane === 'fma' ? largest : 0;
      source[row * 4 + 3] = lane === 'sum' ? largest / 2 : 0;
      // Y=3 makes the sum witness's second product overflow instead. Use
      // unit Y for that witness, preserving the known earlier-row values.
      const input = lane === 'sum' ? {x: 2, y: 1, z: 4} : point;
      if (lane === 'sum') source[row * 4] = largest / 2;
      const before = Object.getOwnPropertyDescriptors(output);
      rejects(() => f.runtime.transformPointBytes(matrix, input, output, base),
        lane === 'product' ? 'single product' : lane === 'fma' ? 'overflow' : 'single sum');
      expectPrefix(output, before, completed, `row${row} ${lane} fault keeps exact store prefix`,
        lane === 'sum' ? [0x41100000, 0x41100000, 0x42040000] : expected);
    }
  }
  {
    for (const key of ['x', 'y', 'z'] as const) {
      const f = fixture(), input = {...point}, output = bytes(), before = Object.getOwnPropertyDescriptors(output);
      let reads = 0;
      Object.defineProperty(input, key, {get() {reads++; throw Error('must not execute');}});
      rejects(() => f.runtime.transformPointBytes(f.parent, input, output, base), 'own data');
      expectPrefix(output, before, 0, `input${key} accessor refuses before byte stores`);
      check(reads === 0, 'point accessors are rejected without execution');
    }
    const f = fixture(), input = {...point}, output = bytes();
    input.y = NaN; f.runtime.getMatrix(f.parent)[0] = Infinity;
    rejects(() => f.runtime.transformPointBytes(f.parent, input, output, base), 'point.y');
    input.y = 3; input.z = NaN;
    rejects(() => f.runtime.transformPointBytes(f.parent, input, output, base), 'matrix[0]');
    f.runtime.getMatrix(f.parent)[0] = 1; f.runtime.getMatrix(f.parent)[1] = Infinity;
    rejects(() => f.runtime.transformPointBytes(f.parent, input, output, base), 'matrix[1]');
    f.runtime.getMatrix(f.parent)[1] = 0;
    rejects(() => f.runtime.transformPointBytes(f.parent, input, output, base), 'point.z');
    check(Object.values(output).every(v => v === sentinel), 'XY, first matrix pair, Z source schedule refuses without stores');
  }
  {
    const f = fixture(), output = bytes(), before = Object.getOwnPropertyDescriptors(output);
    for (const offset of [NaN, Infinity, -Infinity, -4, 0.5, 2, 0xfffffff8, 2 ** 32, Number.MAX_SAFE_INTEGER]) {
      rejects(() => f.runtime.transformPointBytes(Symbol('unknown'), {x: NaN, y: NaN, z: NaN}, output, offset), 'aligned uint32');
      expectPrefix(output, before, 0, 'range admission precedes source access or destination changes');
    }
    rejects(() => f.runtime.transformPointBytes(Symbol('unknown'), unit, output, base), 'unknown/non-owned');
    rejects(() => f.runtime.transformPointBytes(fixture().parent, unit, output, base), 'unknown/non-owned');
    expectPrefix(output, before, 0, 'foreign and unknown matrix identities retain destination');
    for (const offset of [0, -0, 0xfffffff4]) {
      const boundary = bytes(offset);
      f.runtime.transformPointBytes(f.parent, unit, boundary, offset);
      expectWords(boundary, [0x3f800000, 0x3f800000, 0x3f800000], 'aligned inclusive uint32 boundary', offset);
      check(boundary[offset - 1] === sentinel && boundary[offset + 12] === sentinel, 'boundary stores preserve neighbors');
    }
  }
  {
    const f = fixture(), output = bytes(), before = Object.getOwnPropertyDescriptors(output);
    f.hooks.get = () => {
      try {f.runtime.transformPointBytes(f.parent, point, output, base);} catch { /* swallowed adapter reentry */ }
    };
    rejects(f.compose, 'reentry was caught');
    expectPrefix(output, before, 0, 'nested byte transform does not start stores');
    check(f.output.every(value => value === 19), 'caught nested byte transform poisons enclosing compose');
    delete f.hooks.get;
    f.runtime.transformPointBytes(f.parent, unit, output, base);
    expectWords(output, [0x3f800000, 0x3f800000, 0x3f800000], 'byte route recovers after caught reentry');
  }
  {
    // Hostile proxies are fault injection ONLY. The runtime's successful-input
    // contract remains non-proxy own-data records, never arbitrary callbacks.
    for (const phase of ['admission', 'store'] as const) {
      for (let i = 0; i < 12; i++) {
        const f = fixture(), matrix = f.runtime.createMatrix(normal), target = bytes();
        const before = Object.getOwnPropertyDescriptors(target);
        let nested = 0;
        const attempt = (): void => {
          nested++;
          try {f.runtime.identity(matrix);} catch { /* adversarial trap catches nested refusal */ }
        };
        const output = new Proxy(target, {
          getOwnPropertyDescriptor(record, key) {
            if (phase === 'admission' && key === String(base + i)) attempt();
            return Reflect.getOwnPropertyDescriptor(record, key);
          },
          set(record, key, value: number) {
            if (phase === 'store' && key === String(base + i)) attempt();
            return Reflect.set(record, key, value);
          },
        });
        rejects(() => f.runtime.transformPointBytes(matrix, point, output, base), 'caught same-runtime reentry');
        check(nested === 1, 'hostile trap performs exactly one caught nested attempt');
        expectPrefix(target, before, (i >>> 2) + (phase === 'store' ? 1 : 0),
          `${phase} reentry at byte${i} stops after the current admitted word`);
        check(f.runtime.getMatrix(matrix).every((v, j) => Object.is(v, normal[j])), 'reentrant matrix mutation never executes');
        f.runtime.transformPointBytes(matrix, point, target, base);
        expectWords(target, expected, 'runtime recovers after hostile byte trap refusal');
      }
    }
    for (const key of ['x', 'y', 'z']) {
      const f = fixture(), output = bytes(), before = Object.getOwnPropertyDescriptors(output);
      const input = new Proxy(point, {getOwnPropertyDescriptor(record, field) {
        if (field === key) {
          try {f.runtime.transformPointBytes(f.parent, point, output, base);} catch { /* swallowed source-trap reentry */ }
        }
        return Reflect.getOwnPropertyDescriptor(record, field);
      }});
      rejects(() => f.runtime.transformPointBytes(f.parent, input, output, base), 'caught same-runtime reentry');
      expectPrefix(output, before, 0, `point${key} reentry is checked before byte stores`);
    }
  }
}
