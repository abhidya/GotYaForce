import {createSourceActorRotationDampingRuntime, isSourceActorRotationDampingRuntime,
  hasIncompleteSourceActorRotationDamping, type SourceActorRotationDampingSources} from './actor-rotation-damping.js';
import {createRomActor} from './actor.js';
import type {SourceActorWorldMatrixBinding, SourceActorWorldMatrixStorage,
  SourceActorWorldMatrixCorrection} from './actor-world-matrix.js';
import type {SourceActorJointMappingHeader} from './actor-joint-mapping.js';

function check(ok: boolean, why: string): void {if (!ok) throw Error(`[actor-rotation-damping-test] ${why}`);}
function equal(actual: unknown, expected: unknown, why: string): void {
  check(Object.is(actual, expected), `${why}: got ${String(actual)}, expected ${String(expected)}`);
}
function rejects(run: () => unknown, fragment: string): void {
  let error = ''; try {run();} catch (e) {error = String(e);}
  check(error.includes(fragment), `expected ${fragment}, got ${error || 'success'}`);
}
function readonly(record: object, key: string): void {Object.defineProperty(record, key, {writable: false});}
function absent(record: object, key: string): void {Reflect.deleteProperty(record, key);}
const bits = new DataView(new ArrayBuffer(4));
function fromBits(raw: number): number {bits.setUint32(0, raw, false); return bits.getFloat32(0, false);}
const short = (value: number): number => value << 16 >> 16;
const damp = (value: number): number => short(Math.trunc(Math.fround(value * 0.8999999761581421)));
// Independent nearest-f32 oracle: exact 2^-149 units, then binary search of
// ordered bit patterns and integer distance ties. No production float helper,
// fround intermediate, bit-length quantum or truncation conversion is reused.
function units32(value: number): bigint {
  bits.setFloat32(0, value, false); const raw = bits.getUint32(0, false);
  const field = (raw >>> 23) & 255, fraction = raw & 0x7fffff;
  const magnitude = field === 0 ? BigInt(fraction) : BigInt(fraction + 0x800000) << BigInt(field - 1);
  return raw >>> 31 ? -magnitude : magnitude;
}
function nearestBits(integer: bigint, scale: number): number {
  const negative = integer < 0n, target = negative ? -integer : integer;
  const candidate = (raw: number): bigint => {
    const field = raw >>> 23, fraction = raw & 0x7fffff;
    return BigInt(field ? fraction + 0x800000 : fraction) << BigInt((field ? field - 150 : -149) + scale);
  };
  let low = 0, high = 0x7f800000;
  while (low + 1 < high) {
    const middle = Math.floor((low + high) / 2);
    if (candidate(middle) <= target) low = middle; else high = middle;
  }
  const down = target - candidate(low), up = candidate(high) - target;
  const chosen = down < up || (down === up && (low & 1) === 0) ? low : high;
  return chosen + (negative ? 0x80000000 : 0);
}
function oracle(timestep: number, angle: number): number | 'fmuls result' | 'fctiwz signed32' {
  const delta = fromBits(nearestBits(units32(1) - units32(timestep), 149));
  const factor = fromBits(nearestBits(units32(fromBits(0x3dccccd0)) * units32(delta) +
    (units32(fromBits(0x3f666666)) << 149n), 298));
  const productBits = nearestBits(BigInt(angle) * units32(factor), 149);
  if ((productBits & 0x7fffffff) === 0x7f800000) return 'fmuls result';
  const converted = units32(fromBits(productBits)) / (1n << 149n); // BigInt division truncates toward zero.
  if (converted < -2147483648n || converted > 2147483647n) return 'fctiwz signed32';
  const low16 = (converted % 65536n + 65536n) % 65536n;
  return Number(low16 >= 32768n ? low16 - 65536n : low16);
}
/** Owner-only synchronous seams isolate the body. Genuine world/mapping/normal
 * composition is exercised separately by the attached graph selftest. */
function fixture(list: number[] = [12, 2, 7, 11, 255, 255, 255, 255], count = 32, defer = false) {
  const id = Symbol('rotation actor'), descriptorId = Symbol('canonical4b0');
  const actual = createRomActor(); actual.steerYaw = (-1000 & 65535);
  const worldState = {mode4a0: 0, mode4a1: 0} as SourceActorWorldMatrixBinding;
  const mappingState = {timestep1dc8: 1, descriptor4b0: descriptorId} as SourceActorJointMappingHeader;
  const corrections: SourceActorWorldMatrixCorrection[] = Array.from({length: count}, (_, index) =>
    index === 1 ? {y: -2000 - index, z: 3000 + index} : {x: 1000 + index, y: -2000 - index, z: 3000 + index});
  const storage = {corrections18d4: corrections} as unknown as SourceActorWorldMatrixStorage;
  const raw = Object.seal([...Array<number>(0x24).fill(0), ...list]);
  const descriptors = new Map<symbol, number[]>([[descriptorId, raw]]);
  const hooks: Record<string, ((identity: symbol) => unknown) | undefined> = {};
  const calls: Record<string, number> = {};
  const get = (key: string, identity: symbol, value: unknown): unknown => {
    calls[key] = (calls[key] ?? 0) + 1;
    return hooks[key] === undefined ? value : hooks[key]!(identity);
  };
  const world = {
    getActualActor(identity: symbol) {check(this === world && identity === id, 'captured world receiver/id'); return get('actual', identity, actual) as typeof actual;},
    getActorBinding(identity: symbol) {check(this === world && identity === id, 'captured world receiver/id'); return get('world', identity, worldState) as typeof worldState;},
    getMappingActor(identity: symbol) {check(this === world && identity === id, 'captured world receiver/id'); return get('worldMapping', identity, mappingState) as object;},
    getStorage(identity: symbol) {check(this === world && identity === id, 'captured world receiver/id'); return get('storage', identity, storage) as typeof storage;},
  };
  const mapping = {
    getActor(identity: symbol) {check(this === mapping && identity === id, 'captured mapping receiver/id'); return get('mapping', identity, mappingState) as typeof mappingState;},
    getDescriptor(identity: symbol) {check(this === mapping, 'captured descriptor receiver'); return get('descriptor', identity, descriptors.get(identity)) as number[];},
  };
  const sources: SourceActorRotationDampingSources = {world, mapping};
  const runtime = createSourceActorRotationDampingRuntime(sources), bind = () => runtime.bindActor(id);
  if (!defer) bind();
  return {id, descriptorId, actual, worldState, mappingState, corrections, storage, raw, descriptors, hooks, calls,
    sources, world, mapping, runtime, bind, run: () => runtime.updateActor(id)};
}

export function runActorRotationDampingSelfTests(): void {
  {
    const x = fixture();
    const original = x.corrections.map(row => ({...row}));
    x.actual.controlWord = 0xffffffff; x.actual.ubCue = 255; x.actual.fbCue = 17; x.actual.dt = NaN;
    x.actual.heading = 43210; x.actual.stateFlagA = 123; x.actual.stateFlagB = 234;
    equal(x.runtime.getKnownDescriptorRecords().length, 0, 'bind does not resolve descriptor');
    equal(x.calls.descriptor, undefined, 'no eager descriptor call');
    x.run();
    for (let i = 0; i < 32; i++) for (const key of ['x', 'y', 'z'] as const) {
      const before = original[i]![key];
      if (before === undefined) continue;
      equal(x.corrections[i]![key], [1, 2, 7, 11, 12].includes(i) ? damp(before) : before, `explicit Double window joint${i}.${key}`);
    }
    equal(x.actual.steerYaw, damp(-1000) & 65535, 'joint1 X uses signed view of actual BAM16');
    check(!('x' in x.corrections[1]!), 'joint1 gains no X shadow');
    equal(x.runtime.getActualActor(x.id), x.actual, 'actual borrowed');
    equal(x.runtime.getWorldBinding(x.id), x.worldState, 'world borrowed');
    equal(x.runtime.getMappingActor(x.id), x.mappingState, 'mapping borrowed');
    equal(x.runtime.getWorldStorage(x.id), x.storage, 'world storage borrowed');
    equal(x.runtime.getStorageOwners(x.id)[0], x.storage, 'storage exclusion');
    equal(x.runtime.getStorageOwners(x.id)[1], x.corrections, 'array exclusion');
    equal(x.runtime.getStorageOwners(x.id)[3], x.corrections[1], 'row exclusion');
    equal(x.runtime.getKnownDescriptorRecords()[0], x.raw, 'same canonical raw descriptor');
    equal(x.calls.descriptor, 5, 'four list entries and sentinel each reload descriptor');
    equal(x.actual.controlWord, 0xffffffff, 'ungated body preserves control flags');
    equal(x.actual.ubCue, 255, 'preserves upper cue'); equal(x.actual.fbCue, 17, 'preserves full cue');
    equal(x.actual.heading, 43210, 'preserves unrelated BAM16');
    equal(x.actual.stateFlagA, 123, 'preserves stateFlagA'); equal(x.actual.stateFlagB, 234, 'preserves stateFlagB');
    check(Number.isNaN(x.actual.dt), 'legacy clock not read or replaced');
    check(isSourceActorRotationDampingRuntime(x.runtime), 'genuine brand');
    check(!isSourceActorRotationDampingRuntime({...x.runtime}) && !isSourceActorRotationDampingRuntime(null), 'copied methods have no brand');
    check(Object.isFrozen(x.runtime) && Object.isFrozen(x.runtime.getStorageOwners(x.id)), 'runtime and identity list are immutable');
    x.runtime.assertActorComplete(x.id); check(!hasIncompleteSourceActorRotationDamping(x.actual), 'complete return clears scoped marker');
  }
  {
    const x = fixture([0, 2, 3, 4, 5, 6, 7, 31, 128]); x.run();
    equal(x.calls.descriptor, 8, 'CTR exactly8 without requiring sentinel or reading ninth');
    for (const i of [0, 2, 3, 4, 5, 6, 7, 31]) equal(x.corrections[i]!.x, damp(1000 + i), `full8 index${i}`);
    equal(x.actual.steerYaw, damp(-1000) & 65535, 'full8 still has tail');
    const y = fixture([2, 2, 1, 1, 255]); y.run();
    equal(y.corrections[2]!.x, damp(damp(1002)), 'duplicate2 executes twice');
    equal(y.actual.steerYaw, damp(damp(damp(-1000))) & 65535, 'duplicate1 executes twice plus unconditional tail');
    equal(y.corrections[1]!.y, damp(damp(damp(-2001))), 'duplicate1 Y shares the tail owner');
    equal(y.corrections[1]!.z, damp(damp(damp(3001))), 'duplicate1 Z shares the tail owner');
    equal(y.raw[0x24], 2, 'list not rewritten');
  }
  {
    const x = fixture([255], 2); x.corrections[0]!.x = NaN; x.corrections[0]!.y = NaN;
    Object.defineProperty(x.corrections[0]!, 'z', {get() {throw Error('unreached z read');}});
    x.run(); equal(x.actual.steerYaw, damp(-1000) & 65535, 'first sentinel still executes tail');
    equal(x.calls.descriptor, 1, 'first sentinel no later byte or row');
    const y = fixture([255], 2, true); let accesses = 0;
    Object.defineProperty(y.mappingState, 'descriptor4b0', {get() {accesses++; return y.descriptorId;}});
    y.mappingState.timestep1dc8 = NaN; y.bind(); rejects(y.run, 'timestep1dc8');
    equal(accesses, 0, 'coefficient before descriptor; metadata never invokes accessors');
    check(!hasIncompleteSourceActorRotationDamping(y.actual), 'source read failure before any write remains retryable');
    const z = fixture([255], 2, true);
    z.corrections[1]!.y = NaN; z.corrections[1]!.z = NaN; z.actual.steerYaw = NaN;
    z.bind(); equal(z.runtime.getStorageOwners(z.id).length, 4, 'bind and exclusion getter do not read source scalars');
    rejects(z.run, 'steerYaw'); check(!hasIncompleteSourceActorRotationDamping(z.actual), 'first tail source failure is unmarked');
  }
  {
    const x = fixture([2, 255]); x.mappingState.timestep1dc8 = fromBits(0x349dddc4);
    x.corrections[2]!.x = -32768; x.corrections[2]!.y = 32767; x.actual.steerYaw = 32768; x.run();
    equal(x.corrections[2]!.x, -32767, 'fused coefficient3f7fffff witness; unfused would retain−32768');
    equal(x.actual.steerYaw, 32769, 'same fused witness in unsigned BAM16 owner');
    const y = fixture([2, 255]); y.mappingState.timestep1dc8 = fromBits(0x468e66fb);
    y.corrections[2]!.x = -32768; y.run();
    equal(y.corrections[2]!.x, short(59695088), 'source fused product59695088 before low16 wrapping, not59695084');
    const z = fixture([2, 255]); z.mappingState.timestep1dc8 = 0;
    z.corrections[2]!.x = -32768; z.corrections[2]!.y = 32767; z.actual.steerYaw = 65535; z.run();
    equal(z.corrections[2]!.x, -32768, 'zero timestep source coefficient exactly1');
    equal(z.corrections[2]!.y, 32767, 'signed maximum preserved'); equal(z.actual.steerYaw, 65535, 'u16 all-ones signextends to−1');
    const w = fixture([2, 255]); w.mappingState.timestep1dc8 = -0;
    w.corrections[2]!.x = -0; w.corrections[2]!.y = 1; w.run();
    equal(w.corrections[2]!.x, 0, 'signed integer store normalizes negative zero');
    const v = fixture([2, 255]); v.mappingState.timestep1dc8 = 11;
    v.corrections[2]!.x = 7; v.corrections[2]!.y = -7; v.corrections[2]!.z = 32767; v.run();
    equal(v.corrections[2]!.x, 0, 'negative fractional product truncates toward zero');
    equal(v.corrections[2]!.y, 0, 'positive fractional product truncates toward zero');
    equal(v.corrections[2]!.z, -3276, 'negative coefficients are not clamped');
  }
  {
    for (const [timestepBits, angle, expected] of [
      [0x349be9d6, -32768, -32767], // Missing the first fsubs rounding gives−32768.
      [0x461c4000, -32768, -32760], //10000: ordinary0.1f gives the wrong wrapped store.
      [0xc91fff5e, -32768, 0], // Exact signed32 minimum remains admitted.
      [0xc91fff5e, 32767, 0], // Largest16bit angle times65536 also wraps to0.
    ]) {
      const x = fixture([2, 255], 3); x.mappingState.timestep1dc8 = fromBits(timestepBits!);
      x.corrections[2]!.x = angle!; x.corrections[2]!.y = 0; x.corrections[2]!.z = 0;
      x.corrections[1]!.y = 0; x.corrections[1]!.z = 0; x.actual.steerYaw = 0;
      equal(oracle(x.mappingState.timestep1dc8, angle!), expected, 'independent arithmetic witness');
      x.run(); equal(x.corrections[2]!.x, expected, 'fsubs/constant/signed32 exact witness');
    }
    const x = fixture([2, 255], 3); x.mappingState.timestep1dc8 = fromBits(0xc91fff5f); x.corrections[2]!.x = -32768;
    rejects(x.run, 'fctiwz signed32'); equal(x.corrections[2]!.x, -32768, 'one step beyond signed32 minimum refuses without saturation/wrapping');
    check(!hasIncompleteSourceActorRotationDamping(x.actual), 'signed32 range refusal before first store remains retryable');
    const y = fixture([2, 255], 3); y.mappingState.timestep1dc8 = -fromBits(0x7f7fffff);
    for (const row of y.corrections) {if (row.x !== undefined) row.x = 0; row.y = 0; row.z = 0;}
    y.actual.steerYaw = 0; y.run(); equal(y.corrections[2]!.x, 0, 'huge finite timestep admitted when reached products are zero');
    let seed = 0x59fac;
    const random = (): number => {seed = (Math.imul(seed, 1664525) + 1013904223) >>> 0; return seed;};
    for (let index = 0; index < 180; index++) {
      const raw = random(), timestep = fromBits((raw % 0x7f800000) + (random() >>> 31 ? 0x80000000 : 0));
      const angle = index % 13 === 0 ? 0 : short(random());
      const z = fixture([2, 255], 3); z.mappingState.timestep1dc8 = timestep;
      z.corrections[2]!.x = angle; z.corrections[2]!.y = 0; z.corrections[2]!.z = 0;
      z.corrections[1]!.y = 0; z.corrections[1]!.z = 0; z.actual.steerYaw = 0;
      const expected = oracle(timestep, angle);
      if (typeof expected === 'string') {rejects(z.run, expected); equal(z.corrections[2]!.x, angle, 'oracle refusal preserves destination');}
      else {z.run(); equal(z.corrections[2]!.x, expected, 'independent distance oracle source pipeline');}
    }
  }
  {
    for (const invalid of [128, 254, 32, 127]) {
      const x = fixture([invalid, 255]); rejects(x.run, 'joint correction index');
      equal(x.actual.steerYaw, -1000 & 65535, `invalid signed address${invalid} stops before tail`);
      check(!hasIncompleteSourceActorRotationDamping(x.actual), 'prewrite addressing failure unmarked');
      x.raw[0x24] = 255; x.run(); equal(x.actual.steerYaw, damp(-1000) & 65535, 'corrected byte can retry before any store');
    }
    const x = fixture([2, 255], 2); rejects(x.run, 'addressing outside');
    equal(x.actual.steerYaw, -1000 & 65535, 'available storage bound enforced before tail');
    const y = fixture([255], 1); rejects(y.run, 'addressing outside');
    equal(y.actual.steerYaw, damp(-1000) & 65535, 'missing row1 refuses only Y, after actual X store');
    check(hasIncompleteSourceActorRotationDamping(y.actual), 'missing tail row retains scoped incomplete state');
    rejects(y.run, 'known incomplete'); rejects(() => y.runtime.assertActorComplete(y.id), 'known incomplete');
    const z = fixture([1, 255], 1); rejects(z.run, 'addressing outside');
    equal(z.actual.steerYaw, damp(-1000) & 65535, 'list index1 X also needs no row1');
    const w = fixture([255], 0, true); absent(w.storage, 'corrections18d4'); w.bind(); rejects(w.run, 'corrections18d4');
    equal(w.actual.steerYaw, damp(-1000) & 65535, 'missing correction storage also waits until Y');
  }
  {
    const x = fixture([2, 255]); readonly(x.corrections[2]!, 'x'); rejects(x.run, 'x: non-writable');
    check(!hasIncompleteSourceActorRotationDamping(x.actual), 'first readonly destination has no scoped marker');
    const y = fixture([2, 255]); readonly(y.corrections[2]!, 'y'); rejects(y.run, 'y: non-writable');
    equal(y.corrections[2]!.x, damp(1002), 'readonly Y retains X'); equal(y.corrections[2]!.z, 3002, 'readonly Y prevents Z');
    equal(y.actual.steerYaw, -1000 & 65535, 'readonly list Y prevents tail');
    check(hasIncompleteSourceActorRotationDamping(y.actual), 'partial list has permanent incomplete marker');
    y.raw[0x24] = 255; rejects(y.run, 'known incomplete'); equal(y.actual.steerYaw, -1000 & 65535, 'cannot repair partial call by changing list');
    const z = fixture([255], 2); z.corrections[1]!.z = 32768; rejects(z.run, 'z: integer');
    equal(z.actual.steerYaw, damp(-1000) & 65535, 'tail Z source refusal retains X');
    equal(z.corrections[1]!.y, damp(-2001), 'tail Z source refusal retains Y');
    const w = fixture([255], 2); readonly(w.actual, 'steerYaw'); rejects(w.run, 'steerYaw: non-writable');
    equal(w.corrections[1]!.y, -2001, 'readonly actual X stops before Y');
    const v = fixture([255], 2); v.corrections[1]!.x = 99; rejects(v.run, 'joint1 X aliases');
    equal(v.actual.steerYaw, damp(-1000) & 65535, 'competing row X is discovered at first row access, after actual X');
  }
  {
    for (const bad of [1.1, Infinity, -Infinity, NaN]) {
      const x = fixture([255], 2); x.mappingState.timestep1dc8 = bad; rejects(x.run, 'finite exact source float32');
      equal(x.calls.descriptor, undefined, 'invalid timestep before descriptor resolution');
      check(!hasIncompleteSourceActorRotationDamping(x.actual), 'invalid timestep unmarked');
    }
    const x = fixture([2, 255]); x.mappingState.timestep1dc8 = fromBits(0x7f7fffff); x.corrections[2]!.x = 32767;
    rejects(x.run, 'fmuls result'); equal(x.corrections[2]!.x, 32767, 'nonfinite product refused before store');
    const y = fixture([2, 255]); y.mappingState.timestep1dc8 = -fromBits(0x7f7fffff); y.corrections[2]!.x = 1;
    rejects(y.run, 'fctiwz signed32'); equal(y.corrections[2]!.x, 1, 'finite but unrepresentable conversion refused before store');
    const z = fixture([2, 255]); z.mappingState.timestep1dc8 = 1e9; z.corrections[2]!.x = 0; z.corrections[2]!.y = 32767;
    rejects(z.run, 'fctiwz signed32'); equal(z.corrections[2]!.x, 0, 'even unchanged successful X store starts incomplete state');
    check(hasIncompleteSourceActorRotationDamping(z.actual), 'zero-valued first store still commits prefix');
  }
  {
    const x = fixture([255], 2); x.mappingState.descriptor4b0 = null; rejects(x.run, 'null descriptor');
    equal(x.actual.steerYaw, -1000 & 65535, 'null descriptor precedes tail');
    x.mappingState.descriptor4b0 = x.descriptorId; x.run();
    const y = fixture([], 2); rejects(y.run, 'descriptor+b0: addressing');
    equal(y.actual.steerYaw, -1000 & 65535, 'short raw8c descriptor not inferred/padded');
    const z = fixture([2]); rejects(z.run, 'descriptor+b0: addressing');
    equal(z.corrections[2]!.z, damp(3002), 'short descriptor failure keeps prior complete XYZ');
    check(hasIncompleteSourceActorRotationDamping(z.actual), 'list continuation refusal remains incomplete');
    const w = fixture([255], 2); w.mappingState.descriptor4b0 = Symbol('unregistered'); rejects(w.run, 'synchronous actual owned record');
    const v = fixture([255], 2); v.raw[0x24] = -1; rejects(v.run, 'raw byte');
    equal(v.actual.steerYaw, -1000 & 65535, 'descriptor stores unsigned bytes, never decoded−1');
  }
  {
    const x = fixture([2, 255]); const next = Symbol('next4b0'), bytes = Object.seal([...Array<number>(0x24).fill(0), 7, 3, 255]);
    x.descriptors.set(next, bytes); let reads = 0;
    x.hooks.descriptor = identity => {reads++; if (reads === 1) x.mappingState.descriptor4b0 = next; return x.descriptors.get(identity);};
    x.run(); equal(x.corrections[2]!.x, damp(1002), 'first retained descriptor entry');
    equal(x.corrections[3]!.x, damp(1003), 'fresh4b0 reload consumes next descriptor at same ordinal1');
    equal(x.corrections[7]!.x, 1007, 'new descriptor not restarted at ordinal0');
    equal(x.runtime.getKnownDescriptorRecords().length, 2, 'both registered identities tracked');
    const y = fixture([255], 2); y.run(); y.descriptors.set(y.descriptorId, Object.seal([...y.raw]));
    rejects(y.run, 'raw8c: owner changed'); equal(y.actual.steerYaw, damp(-1000) & 65535, 'descriptor identity replacement cannot write');
    const z = fixture([2, 255]); const alias = Symbol('same record second identity'); z.descriptors.set(alias, z.raw); let count = 0;
    z.hooks.descriptor = identity => {count++; if (count === 1) z.mappingState.descriptor4b0 = alias; return z.descriptors.get(identity);};
    rejects(z.run, 'aliases another'); equal(z.corrections[2]!.x, damp(1002), 'second descriptor identity refusal retains first list entry');
    const w = fixture([255], 2); w.hooks.descriptor = () => [...w.raw]; rejects(w.run, 'sealed raw8c');
    const v = fixture([255], 2); v.hooks.descriptor = () => Promise.resolve(v.raw); rejects(v.run, 'synchronous actual owned record');
  }
  {
    for (const key of ['actual', 'world', 'worldMapping', 'mapping', 'storage']) {
      const x = fixture([255], 2); x.hooks[key] = () => ({}); rejects(x.run, 'owner changed');
      equal(x.actual.steerYaw, -1000 & 65535, `changed ${key} precedes source writes`);
    }
    const x = fixture([2, 255]); Object.assign(x.storage, {corrections18d4: [...x.corrections]});
    rejects(x.run, 'corrections18d4 owner changed'); equal(x.corrections[2]!.x, 1002, 'no copied array accepted');
    const y = fixture([2, 255]); y.corrections[2] = {...y.corrections[2]!}; rejects(y.run, 'joint2 correction owner changed');
    const z = fixture([255], 2); z.corrections[0] = {...z.corrections[0]!}; z.run();
    equal(z.actual.steerYaw, damp(-1000) & 65535, 'unreached row replacement is not source-preflighted');
    const w = fixture([255], 2, true); w.hooks.worldMapping = () => ({}); rejects(w.bind, 'world mapping');
    const v = fixture([255], 2, true); v.hooks.actual = () => Promise.resolve(v.actual); rejects(v.bind, 'synchronous actual owned record');
  }
  {
    const x = fixture([255], 2, true); x.corrections[0] = x.corrections[1]!; rejects(x.bind, 'source owner alias');
    const y = fixture([255], 2, true); y.corrections[0] = y.actual as unknown as SourceActorWorldMatrixCorrection; rejects(y.bind, 'source owner alias');
    const z = fixture([255], 2, true); Object.assign(z.worldState, {timestep1dc8: 1}); rejects(z.bind, 'competing rotation storage');
    const w = fixture([255], 2, true); Object.assign(w.actual, {pointer4b0: w.descriptorId}); rejects(w.bind, 'competing rotation storage alias');
    const v = fixture([255], 2); const second = createSourceActorRotationDampingRuntime(v.sources);
    rejects(() => second.bindActor(v.id), 'already claimed'); rejects(v.bind, 'new symbol');
    rejects(() => v.runtime.updateActor(Symbol('unknown')), 'unknown/non-owned');
    const q = fixture([255], 2, true); q.corrections[0] = q.raw as unknown as SourceActorWorldMatrixCorrection; q.bind();
    rejects(q.run, 'descriptor4b0 aliases another');
    equal(q.actual.steerYaw, -1000 & 65535, 'descriptor cannot alias an otherwise-unreached correction row');
  }
  {
    const x = fixture([255], 2);
    x.world.getStorage = () => {throw Error('replacement getter executed');};
    x.mapping.getDescriptor = () => {throw Error('replacement descriptor getter executed');};
    x.sources.world = {} as typeof x.world; x.sources.mapping = {} as typeof x.mapping;
    x.run(); equal(x.actual.steerYaw, damp(-1000) & 65535, 'captured methods and receiver survive external replacement');
    const y = fixture([255], 2); y.hooks.descriptor = () => {try {y.run();} catch {} return y.raw;};
    rejects(y.run, 'caught same-runtime reentry'); equal(y.actual.steerYaw, -1000 & 65535, 'caught reentry before first store poisons current call');
    check(!hasIncompleteSourceActorRotationDamping(y.actual), 'prewrite reentry is not permanent incomplete marker');
    delete y.hooks.descriptor; y.run(); equal(y.actual.steerYaw, damp(-1000) & 65535, 'fresh outer call after prewrite failure can run');
    const z = fixture([2, 255]); let seen = 0;
    z.hooks.descriptor = () => {if (++seen === 2) {try {z.run();} catch {}} return z.raw;};
    rejects(z.run, 'caught same-runtime reentry'); equal(z.corrections[2]!.z, damp(3002), 'late poison keeps completed first triple');
    check(hasIncompleteSourceActorRotationDamping(z.actual), 'late caught reentry permanently marks incomplete');
    delete z.hooks.descriptor; rejects(z.run, 'known incomplete');
    const w = fixture([255], 2, true); let invoked = false;
    Object.defineProperty(w.mapping, 'getDescriptor', {get() {invoked = true; return () => w.raw;}});
    rejects(() => createSourceActorRotationDampingRuntime(w.sources), 'own data property');
    check(!invoked, 'constructor refuses accessor methods without invocation');
  }
  console.log('[actor-rotation-damping-test] bounded canonical rotation body, ordered storage and arithmetic passed');
}
