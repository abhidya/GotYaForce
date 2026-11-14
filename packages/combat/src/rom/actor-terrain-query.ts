/** Bounded source 8003d6e4, 8003de80, 8003f320, 8003fa68 and 8003fb00.
 * Uses actual actor/history records and strict, byte-backed source cell lists.
 * No physics floor callback, inferred StageCollision geometry, default layer,
 * cached height/normal, persistent query result, or implicit refresh exists.
 *
 * Evidence: read_archived_terrain_query_evidence.py authenticates both archived
 * ProgramDB snapshots; chunk_0004.c:6993–7047,8246–8261,8288–8296,8502–8526.
 * read_archived_terrain_orientation_evidence.py fixes the distinct 8003de80
 * instruction order and normal stores (chunk_0004.c:7262–7343).
 * Host bounds: finite exact f32 inputs/intermediates, RN=00, NI=0; synchronous
 * stable non-proxy own-data owners; source pointer arithmetic must address an
 * explicitly owned cell. Nonzero support refuses before its matrix/copy branch;
 * reached nonempty ceiling cells refuse before their triangle bodies. Floor
 * triangles execute the actual edge and plane arithmetic, within explicit
 * flat normals (+/-0,1,+/-0). Other normals refuse only when reached.
 * Source loads and arithmetic remain ordered, including local clearance
 * adjustment, current/history reloads, and all three height-query accumulators.
 * The normal query writes only its explicit caller-local output, with no
 * minimum/maximum fallback. Caller-local records must not alias source storage.
 * This is not general terrain, live FPSCR/RAM or original-game replay parity.
 */
import {sourceTerrainGrid, type hitBin} from '@gf/formats';
import type {SourceActorWorldMatrixRuntime} from './actor-world-matrix.js';
import type {SourceActorTransformHistoryRuntime} from './actor-transform-history.js';
import type {SourceJointVector} from './joint-animation-feedback.js';
import {addSourceFloat32} from './source-float.js';

export interface SourceActorTerrainGlobals {
  readonly floor1c: sourceTerrainGrid.SourceTerrainGrid;
  readonly ceiling20: sourceTerrainGrid.SourceTerrainGrid;
  readonly ceiling24: sourceTerrainGrid.SourceTerrainGrid;
  upper34: number;
  lower68: number;
}
export interface SourceActorTerrainQuerySources {
  world: Pick<SourceActorWorldMatrixRuntime, 'getActualActor'>;
  history: Pick<SourceActorTransformHistoryRuntime, 'getActorBinding'>;
  /** Actual shared DAT_8043625c record; no copied/default global fields. */
  terrain: SourceActorTerrainGlobals;
}
export interface SourceActorTerrainQueryRuntime {
  bindActor(identity: symbol): void;
  /** Explicit caller-local point; clearance is a value, never an actor shadow. */
  query8003d6e4(identity: symbol, point: Readonly<SourceJointVector>, savedClearance: number): number;
  /** Direct source normal query. Writes caller output in source order; 0 means
   * outside X/Z bounds, not no eligible floor. No result is retained here. */
  queryNormal8003de80(identity: symbol, callerLocalPoint: Readonly<SourceJointVector>, savedClearance: number,
    callerLocalNormalOutput: SourceJointVector): 0 | 1;
}
function fail(reason: string): never {
  throw Error(`[actor-terrain-query] ${reason}; offline execution aborted, prior writes/effects are not rolled back`);
}
function own(record: unknown, key: string): unknown {
  if (record === null || typeof record !== 'object') fail(`${key}: own data record required`);
  const descriptor = Object.getOwnPropertyDescriptor(record, key);
  if (!descriptor || !('value' in descriptor)) fail(`${key}: own data property required`);
  return descriptor.value;
}
function record(value: unknown, where: string): object {
  if (value === null || typeof value !== 'object' || value instanceof Promise) fail(`${where}: synchronous actual record required`);
  return value;
}
function integer(value: unknown, min: number, max: number, where: string): number {
  if (typeof value !== 'number' || !Number.isInteger(value) || value < min || value > max) fail(`${where}: integer out of bounds`);
  return value;
}
function float(value: unknown, where: string): number {
  if (typeof value !== 'number' || !Number.isFinite(value) || !Object.is(value, Math.fround(value))) fail(`${where}: finite exact source float32 required`);
  return value;
}
const sub32 = (a: number, b: number): number => addSourceFloat32(a, -b);
// A binary32 product has at most 48 significant bits, so binary64 represents
// it exactly before the single rounding. Preserve signed zero and underflow.
const mul32 = (a: number, b: number): number => float(Math.fround(a * b), 'fmuls result');
const floatBits = new DataView(new ArrayBuffer(4));
function dyadic(value: number): {mantissa: bigint; exponent: number; negative: boolean} {
  floatBits.setFloat32(0, value, false);
  const bits = floatBits.getUint32(0, false), e = (bits >>> 23) & 255;
  return {mantissa: BigInt((bits & 0x7fffff) | (e === 0 ? 0 : 0x800000)),
    exponent: e === 0 ? -149 : e - 150, negative: (bits >>> 31) !== 0};
}
/** Exact rational nearest-even fdivs, including gradual underflow/signed zero.
 * No binary64 quotient or reciprocal approximation is rounded a second time. */
function div32(a: number, b: number): number {
  const x = dyadic(a), y = dyadic(b), negative = x.negative !== y.negative;
  if (y.mantissa === 0n) fail('fdivs zero divisor outside finite domain');
  if (x.mantissa === 0n) return negative ? -0 : 0;
  let power = x.mantissa.toString(2).length - y.mantissa.toString(2).length;
  if (power >= 0 ? x.mantissa < (y.mantissa << BigInt(power)) :
    (x.mantissa << BigInt(-power)) < y.mantissa) power--;
  const exponent = x.exponent - y.exponent;
  const quantum = Math.max(-149, power + exponent - 23), scale = exponent - quantum;
  const numerator = scale >= 0 ? x.mantissa << BigInt(scale) : x.mantissa;
  const denominator = scale < 0 ? y.mantissa << BigInt(-scale) : y.mantissa;
  let rounded = numerator / denominator;
  const remainderTwice = (numerator % denominator) * 2n;
  if (remainderTwice > denominator || (remainderTwice === denominator && (rounded & 1n) !== 0n)) rounded++;
  const result = Number(rounded) * 2 ** quantum;
  return float(negative ? -result : result, 'fdivs result');
}

export function createSourceActorTerrainQueryRuntime(sources: SourceActorTerrainQuerySources): SourceActorTerrainQueryRuntime {
  let busy = false, poisoned = false;
  const check = (): void => {if (poisoned) fail('caught same-runtime reentry');};
  const read = (value: unknown, key: string): unknown => {const result = own(value, key); check(); return result;};
  const f = (value: unknown, key: string): number => float(read(value, key), key);
  const writeNormal = (output: object, key: 'x' | 'y' | 'z', next: number): void => {
    const descriptor = Object.getOwnPropertyDescriptor(output, key); check();
    if (!descriptor || !('value' in descriptor)) fail(`normal output ${key}: own data property required`);
    if (!descriptor.writable) fail(`normal output ${key}: non-writable field unsupported`);
    (output as SourceJointVector)[key] = next; check();
  };
  const capture = (name: 'world' | 'history', key: string) => {
    const receiver = own(sources, name), method = own(receiver, key);
    if (typeof method !== 'function') fail(`${name}.${key}: own data-function required`);
    return (id: symbol): unknown => {const value = Reflect.apply(method, receiver, [id]); check(); return value;};
  };
  const getActual = capture('world', 'getActualActor'), getHistory = capture('history', 'getActorBinding');
  const terrain = record(own(sources, 'terrain'), 'actual terrain globals');
  const guard = <T>(run: () => T): T => {
    if (busy) {poisoned = true; fail('same-runtime reentry unsupported');}
    busy = true; poisoned = false;
    try {const result = run(); check(); return result;} finally {busy = false;}
  };
  interface Entry {actual: object; position: object; savedPosition: object; history: object}
  const actors = new Map<symbol, Entry>(), assigned = new WeakSet<object>();
  const stable = (get: (id: symbol) => unknown, id: symbol, expected: object, where: string): object => {
    const value = record(get(id), where); if (value !== expected) fail(`${where} owner changed its actual record`); return value;
  };
  const actual = (actor: Entry, id: symbol): object => stable(getActual, id, actor.actual, 'actual RomActor');
  const actorVector = (actor: Entry, id: symbol, key: 'pos' | 'savedGroundPos'): object => {
    const value = record(read(actual(actor, id), key), key);
    if (value !== (key === 'pos' ? actor.position : actor.savedPosition)) fail(`${key} owner changed its actual record`);
    return value;
  };
  const history = (actor: Entry, id: symbol): object => stable(getHistory, id, actor.history, 'transform history');
  const layers = new Map<string, object>();
  function layer(key: 'floor1c' | 'ceiling20' | 'ceiling24', offset: 0x1c | 0x20 | 0x24): sourceTerrainGrid.SourceTerrainGrid {
    const value = record(read(terrain, key), key);
    sourceTerrainGrid.assertSourceTerrainGrid(value); check();
    if (read(value, 'globalLayerOffset') !== offset) fail(`${key}: wrong source global layer identity`);
    const previous = layers.get(key);
    if (previous && previous !== value) fail(`${key} owner changed its actual record`);
    layers.set(key, value); return value;
  }
  // 3fb00 checks only X then Z; an outside X must not read even point.Z.
  // Authenticated bounds bits: c5ea6000 (-7500), 45ea6000 (+7500).
  function inBounds(point: unknown): boolean {
    const x = f(point, 'x');
    if (x <= -7500 || x >= 7500) return false;
    const z = f(point, 'z'); return z > -7500 && z < 7500;
  }
  // The three instruction sequences differ in load/round timing. Preserve the
  // +34 load between the Z-origin conversion and first division in +24 only.
  type SelectedCell = {view: sourceTerrainGrid.SourceTerrainGrid; list: sourceTerrainGrid.SourceTerrainList; ceiling: number | undefined};
  const headerInt = (view: sourceTerrainGrid.SourceTerrainGrid, field: sourceTerrainGrid.SourceTerrainHeaderField): number => {
    const value = sourceTerrainGrid.readSourceTerrainHeader(view, field); check();
    return integer(value, -2147483648, 2147483647, `source ${field}`) | 0;
  };
  const cellTable = (view: sourceTerrainGrid.SourceTerrainGrid): void => {
    sourceTerrainGrid.readSourceTerrainCellTable(view); check();
  };
  const listEntry = (selected: SelectedCell, index: number): hitBin.StageHitTriangle | -1 => {
    const value = sourceTerrainGrid.readSourceTerrainListEntry(selected.view, selected.list, index); check(); return value;
  };
  const triangleFloat = (view: sourceTerrainGrid.SourceTerrainGrid, triangle: hitBin.StageHitTriangle,
    offset: sourceTerrainGrid.SourceTerrainTriangleFloatOffset): number => {
    const value = sourceTerrainGrid.readSourceTerrainTriangleFloat(view, triangle, offset); check();
    return float(value, `triangle+${offset.toString(16)}`);
  };
  function cell(key: 'floor1c' | 'ceiling20' | 'ceiling24', offset: 0x1c | 0x20 | 0x24,
    point: unknown): SelectedCell {
    const view = layer(key, offset);
    const originX = headerInt(view, 'originX'), originZ = headerInt(view, 'originZ');
    const x = f(point, 'x'), roundedOriginX = Math.fround(originX), z = f(point, 'z');
    let rowStride: number, dx: number, roundedOriginZ: number;
    if (key === 'ceiling20') {
      dx = sub32(x, roundedOriginX); rowStride = headerInt(view, 'rowStride');
      roundedOriginZ = Math.fround(originZ); cellTable(view);
    } else {
      rowStride = headerInt(view, 'rowStride'); dx = sub32(x, roundedOriginX);
      cellTable(view); roundedOriginZ = Math.fround(originZ);
    }
    const ceiling = key === 'ceiling24' ? f(terrain, 'upper34') : undefined;
    // Authenticated 80436ffc bits43fa0000 = 500, not STIH header cell size.
    const qx = div32(dx, 500), dz = sub32(z, roundedOriginZ);
    const ix = integer(Math.trunc(qx), -2147483648, 2147483647, 'fctiwz X') | 0;
    const qz = div32(dz, 500), product = Math.imul(ix, rowStride);
    const iz = integer(Math.trunc(qz), -2147483648, 2147483647, 'fctiwz Z') | 0;
    // mullw/add low words, then slwi2 (32-bit wrap), not an unbounded JS index.
    const byteOffset = ((iz + product) << 2) >>> 0;
    const selected = sourceTerrainGrid.readSourceTerrainCell(view, byteOffset / 4); check();
    return {view, list: selected.list, ceiling};
  }
  function ceilingQuery(point: unknown, threshold: number): number {
    // threshold is a loaded source argument, even for empty ceiling lists.
    float(threshold, 'ceiling threshold');
    if (!inBounds(point)) return f(point, 'y');
    const first = cell('ceiling24', 0x24, point);
    if (listEntry(first, 0) !== -1) fail('nonempty ceiling24 triangle body unsupported');
    const second = cell('ceiling20', 0x20, point);
    if (listEntry(second, 0) !== -1) fail('nonempty ceiling20 triangle body unsupported');
    return first.ceiling!;
  }
  return Object.freeze({
    bindActor(id: symbol): void {guard(() => {
      if (typeof id !== 'symbol') fail('actual actor symbol required');
      if (actors.has(id)) fail('terrain-query actor already bound');
      const actor = record(getActual(id), 'actual RomActor'), prior = record(getHistory(id), 'transform history');
      const position = record(read(actor, 'pos'), 'pos'), savedPosition = record(read(actor, 'savedGroundPos'), 'savedGroundPos');
      const records = [actor, position, savedPosition, prior], seen = new Set<object>();
      for (const value of records) {
        if (seen.has(value) || assigned.has(value) || value === terrain) fail('aliased terrain-query owner unsupported');
        seen.add(value);
      }
      actors.set(id, {actual: actor, position, savedPosition, history: prior});
      for (const value of records) assigned.add(value);
    });},
    query8003d6e4(id: symbol, point: Readonly<SourceJointVector>, savedClearance: number): number {return guard(() => {
      const actor = actors.get(id); if (!actor) fail('unknown/non-owned terrain-query actor');
      const contact = integer(read(actual(actor, id), 'supportContact1db'), 0, 255, 'supportContact1db');
      if (contact !== 0) fail('nonzero supporting contact matrix branch unsupported');
      if (!inBounds(point)) return f(point, 'y');
      const upper = f(terrain, 'upper34');
      let clearance = float(savedClearance, 'saved clearance');
      const selectMaximum = clearance >= upper;
      const x = f(point, 'x'), y = f(point, 'y'), step = f(actual(actor, id), 'stepHeight');
      const stackY = addSourceFloat32(y, step), z = f(point, 'z');
      const savedY = f(actorVector(actor, id, 'savedGroundPos'), 'y'), previousStep = f(history(actor, id), 'previousStepHeight6d4');
      const ceiling = ceilingQuery({x, y: stackY, z}, addSourceFloat32(savedY, previousStep));
      // These four scalar loads are fresh, after both genuine ceiling lists.
      const oldY = f(actorVector(actor, id, 'savedGroundPos'), 'y'), oldStep = f(history(actor, id), 'previousStepHeight6d4');
      const currentY = f(actorVector(actor, id, 'pos'), 'y'), currentStep = f(actual(actor, id), 'stepHeight');
      const previousTop = addSourceFloat32(oldY, oldStep), currentTop = addSourceFloat32(currentY, currentStep);
      const displacement = sub32(previousTop, currentTop);
      if (displacement > 0) clearance = addSourceFloat32(clearance, displacement);
      const pointY = f(point, 'y'), limit = addSourceFloat32(clearance, pointY);
      const selected = cell('floor1c', 0x1c, point);
      let best = f(terrain, 'lower68'), minimum = f(terrain, 'upper34'), maximum = best;
      for (let cursor = 0; ; cursor++) {
        const item = listEntry(selected, cursor);
        if (item === -1) break;
        const tf = (offset: sourceTerrainGrid.SourceTerrainTriangleFloatOffset): number => triangleFloat(selected.view, item, offset);
        const dx1 = sub32(tf(0x04), x), dz1 = sub32(tf(0x0c), z);
        const vx2 = tf(0x10), vz2 = tf(0x18), dx2 = sub32(vx2, x);
        const vx3 = tf(0x1c), dz2 = sub32(vz2, z), vz3 = tf(0x24), dx3 = sub32(vx3, x);
        const edge1a = mul32(dz1, dx2), edge1b = mul32(dx1, dz2), dz3 = sub32(vz3, z);
        if (edge1a < edge1b) continue;
        if (mul32(dz2, dx3) < mul32(dx2, dz3)) continue;
        if (mul32(dz3, dx1) < mul32(dx3, dz1)) continue;
        const nx = tf(0x28);
        if (nx !== 0) fail('nonflat source normal X unsupported');
        const nz = tf(0x30); if (nz !== 0) fail('nonflat source normal Z unsupported');
        const ny = tf(0x2c); if (ny !== 1) fail('nonflat source normal Y unsupported');
        const xProduct = mul32(nx, dx1), zProduct = mul32(nz, dz1), vertexY = tf(0x08);
        const xz = addSourceFloat32(xProduct, zProduct), yProduct = mul32(ny, vertexY);
        const height = div32(addSourceFloat32(xz, yProduct), ny);
        if (limit > height && ceiling > height && best <= height) best = height;
        if (minimum >= height) minimum = height;
        if (maximum <= height) maximum = height;
      }
      if (selectMaximum) return maximum;
      const lower = f(terrain, 'lower68'); if (best !== lower) return best;
      const finalUpper = f(terrain, 'upper34'); return minimum === finalUpper ? lower : minimum;
    });},
    queryNormal8003de80(id: symbol, callerLocalPoint: Readonly<SourceJointVector>, savedClearance: number,
      callerLocalNormalOutput: SourceJointVector): 0 | 1 {return guard(() => {
      const actor = actors.get(id); if (!actor) fail('unknown/non-owned terrain-query actor');
      const support = integer(read(actual(actor, id), 'supportContact1db'), 0, 255, 'supportContact1db');
      if (support !== 0) fail('nonzero supporting contact normal-copy branch unsupported');
      const output = record(callerLocalNormalOutput, 'caller-local normal output');
      if (output === callerLocalPoint || assigned.has(output) || output === terrain || output === sources)
        fail('aliased caller-local normal output unsupported');
      writeNormal(output, 'x', 0); writeNormal(output, 'y', 1); writeNormal(output, 'z', 0);
      if (!inBounds(callerLocalPoint)) return 0;
      const localX = f(callerLocalPoint, 'x'), localY = f(callerLocalPoint, 'y');
      const localStep = f(actual(actor, id), 'stepHeight');
      const ceilingPointY = addSourceFloat32(localY, localStep), localZ = f(callerLocalPoint, 'z');
      const firstSavedY = f(actorVector(actor, id, 'savedGroundPos'), 'y');
      const firstPreviousStep = f(history(actor, id), 'previousStepHeight6d4');
      const ceilingHeight = ceilingQuery({x: localX, y: ceilingPointY, z: localZ}, addSourceFloat32(firstSavedY, firstPreviousStep));
      const historyY = f(actorVector(actor, id, 'savedGroundPos'), 'y');
      const historyStep = f(history(actor, id), 'previousStepHeight6d4');
      const positionY = f(actorVector(actor, id, 'pos'), 'y'), positionStep = f(actual(actor, id), 'stepHeight');
      const historyTop = addSourceFloat32(historyY, historyStep), positionTop = addSourceFloat32(positionY, positionStep);
      const topDelta = sub32(historyTop, positionTop);
      let localClearance = savedClearance;
      if (topDelta > 0) localClearance = addSourceFloat32(float(localClearance, 'saved clearance'), topDelta);
      const reloadedY = f(callerLocalPoint, 'y'), normalLimit = addSourceFloat32(float(localClearance, 'saved clearance'), reloadedY);
      const floorCell = cell('floor1c', 0x1c, callerLocalPoint);
      let bestHeight = f(terrain, 'lower68');
      for (let index = 0; ; index++) {
        const candidate = listEntry(floorCell, index);
        if (candidate === -1) break;
        const load = (offset: sourceTerrainGrid.SourceTerrainTriangleFloatOffset): number => triangleFloat(floorCell.view, candidate, offset);
        // 3de80 loads v2X before v1Z, unlike the height-query scan above.
        const vertex1X = load(0x04), vertex2X = load(0x10), vertex1Z = load(0x0c);
        const delta1X = sub32(vertex1X, localX), delta2X = sub32(vertex2X, localX), vertex2Z = load(0x18);
        const delta1Z = sub32(vertex1Z, localZ), vertex3X = load(0x1c), delta2Z = sub32(vertex2Z, localZ);
        const vertex3Z = load(0x24), delta3X = sub32(vertex3X, localX);
        const firstLeft = mul32(delta1Z, delta2X), firstRight = mul32(delta1X, delta2Z), delta3Z = sub32(vertex3Z, localZ);
        if (firstLeft < firstRight) continue;
        if (mul32(delta2Z, delta3X) < mul32(delta2X, delta3Z)) continue;
        if (mul32(delta3Z, delta1X) < mul32(delta3X, delta1Z)) continue;
        const normalX = load(0x28); if (normalX !== 0) fail('nonflat source normal X unsupported');
        const normalZ = load(0x30); if (normalZ !== 0) fail('nonflat source normal Z unsupported');
        const normalY = load(0x2c); if (normalY !== 1) fail('nonflat source normal Y unsupported');
        const productX = mul32(normalX, delta1X), productZ = mul32(normalZ, delta1Z), planeY = load(0x08);
        const productXZ = addSourceFloat32(productX, productZ), productY = mul32(normalY, planeY);
        const candidateHeight = div32(addSourceFloat32(productXZ, productY), normalY);
        if (candidateHeight < normalLimit && candidateHeight < ceilingHeight && bestHeight <= candidateHeight) {
          // Source stores the preserved raw X/Y/Z words, without reloading the
          // triangle. The best scalar changes between the X and Y stores.
          writeNormal(output, 'x', normalX);
          bestHeight = candidateHeight;
          writeNormal(output, 'y', normalY); writeNormal(output, 'z', normalZ);
        }
      }
      return 1;
    });},
  });
}
