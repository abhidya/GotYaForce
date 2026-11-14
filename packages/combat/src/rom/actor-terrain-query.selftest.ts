import {hitBin, sourceTerrainGrid} from '@gf/formats';
import {createRomActor} from './actor.js';
import {createSourceActorTerrainNormalOutput, createSourceActorTerrainQueryRuntime, isSourceActorTerrainQueryRuntime,
  type SourceActorTerrainGlobals, type SourceActorTerrainNormalOutput} from './actor-terrain-query.js';
import {createSourceActorTransformHistoryRuntime} from './actor-transform-history.js';
import {createSourceActorWorldMatrixRuntime} from './actor-world-matrix.js';
import {createSourceActorJointMappingRuntime} from './actor-joint-mapping.js';
import {createSourceActorJointMatrixRuntime} from './actor-joint-matrix.js';
import {createSourceJointAnimationFeedbackRuntime} from './joint-animation-feedback.js';
import {createSourceJObjAnimationRuntime} from './jobj-animation.js';

function check(ok: boolean, why: string): void {if (!ok) throw Error(`[actor-terrain-query-test] ${why}`);}
function rejects(run: () => unknown, text: string): void {
  let message = ''; try {run();} catch (error) {message = String(error);}
  check(message.includes(text), `expected ${text}, got ${message}`);
}
const vec = (x: number, y = x, z = x) => ({x, y, z});
interface TriangleInput {vertices: [hitBin.StageHitVec3, hitBin.StageHitVec3, hitBin.StageHitVec3]; normal: hitBin.StageHitVec3}
const triangle = (y: number, x = 0, z = 0): TriangleInput => ({
  vertices: [vec(x, y, z), vec(x, y, z + 500), vec(x + 500, y, z)], normal: vec(0, 1, 0),
});
/** Synthetic source bytes, never inferred StageCollision geometry or assets. */
function layer(offset: sourceTerrainGrid.SourceTerrainLayerOffset, triangles: TriangleInput[],
  lists: number[][] = [triangles.map((_, i) => i), [], [], []], origin = vec(0), size = 500) {
  const listBase = 0x38, listBytes = lists.reduce((sum, list) => sum + 4 * (list.length + 1), 0);
  const recordBase = listBase + listBytes + 8;
  const bytes = new Uint8Array(recordBase + triangles.length * 0x38), view = new DataView(bytes.buffer);
  const u32 = (at: number, value: number) => view.setUint32(at, value, false);
  const f32 = (at: number, value: number) => view.setFloat32(at, value, false);
  u32(0, 0x53544948); u32(4, bytes.length); u32(8, size); u32(12, size);
  u32(16, 2); u32(20, 2); view.setInt32(24, origin.x, false); view.setInt32(28, origin.z, false);
  u32(0x20, 0x20); u32(0x24, recordBase - 8);
  let cursor = listBase;
  lists.forEach((list, index) => {
    u32(0x28 + index * 4, cursor - 8);
    for (const value of list) {u32(cursor, value * 0x38); cursor += 4;}
    u32(cursor, 0xffffffff); cursor += 4;
  });
  triangles.forEach((record, index) => {
    const base = recordBase + index * 0x38; u32(base, 0xabcdef00 + index);
    for (let vertex = 0; vertex < 3; vertex++) {
      const value = record.vertices[vertex]!;
      f32(base + 4 + vertex * 12, value.x); f32(base + 8 + vertex * 12, value.y); f32(base + 12 + vertex * 12, value.z);
    }
    f32(base + 0x28, record.normal.x); f32(base + 0x2c, record.normal.y); f32(base + 0x30, record.normal.z);
    // Deliberately unrelated to the plane result: source query never loads +34.
    f32(base + 0x34, NaN);
  });
  const grid = hitBin.parseStageHitGrid(bytes), source = sourceTerrainGrid.createSourceTerrainGrid(bytes, grid, offset);
  return {bytes, view, grid, source, recordBase};
}
/** Bounded source table with shared real lists, for admitted integer-wrap paths.
 * At most 32,768 cells are used below; only the explicitly supplied triangle
 * records exist. No synthetic source address or callback replaces a cell word. */
function integerLayer(offset: sourceTerrainGrid.SourceTerrainLayerOffset, nx: number, nz: number,
  originX: number, heights: number[], cellRecords: ReadonlyMap<number, number> = new Map()) {
  const count = nx * nz, listBase = 0x28 + 4 * count;
  const recordBase = listBase + 4 + 8 * heights.length + 8;
  const bytes = new Uint8Array(recordBase + 0x38 * heights.length), view = new DataView(bytes.buffer);
  const word = (at: number, value: number) => view.setInt32(at, value, false);
  word(0, 0x53544948); word(4, bytes.length); word(8, 500); word(12, 500);
  word(16, nx); word(20, nz); word(24, originX); word(28, 0);
  word(32, 0x20); word(36, recordBase - 8); word(listBase, -1);
  for (let index = 0; index < count; index++) {
    const record = cellRecords.get(index);
    word(0x28 + 4 * index, record === undefined ? listBase - 8 : listBase + 4 + 8 * record - 8);
  }
  heights.forEach((height, index) => {
    word(listBase + 4 + 8 * index, index * 0x38); word(listBase + 8 + 8 * index, -1);
    const base = recordBase + 0x38 * index; word(base, 123);
    [0, height, 0, 0, height, 500, 500, height, 0, 0, 1, 0, 77].forEach((value, component) =>
      view.setFloat32(base + 4 + 4 * component, value, false));
  });
  const grid = hitBin.parseStageHitGrid(bytes);
  return {bytes, view, grid, source: sourceTerrainGrid.createSourceTerrainGrid(bytes, grid, offset), recordBase};
}
function fixture(heights = [2], options: {floor?: ReturnType<typeof layer>; ceiling24?: ReturnType<typeof layer>;
  ceiling20?: ReturnType<typeof layer>; upper?: number; lower?: number} = {}) {
  const unexpected = (): never => {throw Error('query must not animate or update matrices');};
  const joints = createSourceJObjAnimationRuntime(), feedback = createSourceJointAnimationFeedbackRuntime(joints);
  const mapping = createSourceActorJointMappingRuntime(joints, feedback,
    {interpretAObj: unexpected, animateRObjs: unexpected, animateDObjs: unexpected}, {convertEulerToQuaternion: unexpected});
  const matrices = createSourceActorJointMatrixRuntime(feedback), world = createSourceActorWorldMatrixRuntime({mapping, feedback, matrices});
  const parts = Array.from({length: 2}, () => Array.from({length: 4}, () => mapping.createPart(
    {frame0c: 0, duration24: 0, segment2d: 0, complete2e: 0, mode2f: 0, mirror30: 0},
    {descriptor00: null, scaleIndex32: 255, jointBank33: 0, poseBuffer35: 0})));
  const id = mapping.createActor({descriptor4b0: null, jointCount1d90: 0, boundary1d91: 0, boundary1d92: 0,
    boundary1d93: 0, jointBank1db4: null, jointBank1db8: null, timestep1dc8: 1}, {parts, poses: [[], []]});
  const actual = createRomActor(); Object.assign(actual.pos, vec(0)); Object.assign(actual.savedGroundPos, vec(0)); actual.stepHeight = 0;
  world.bindActor(id, actual, {mode4a0: 0, mode4a1: 0, flags48a: 0, mask1d70: 0, roll74: 0, yawOffset6b8: 0,
    scale58: vec(1), offset1dbc: vec(0), adjusted1d54: vec(0), preRotation1d64: vec(0)},
  {matrices8d4: [], copy114: matrices.createMatrix(Array(12).fill(91)), copy1aa4: matrices.createMatrix(Array(12).fill(92)),
    scratch: matrices.createMatrix(Array(12).fill(93)), topology1994: [], corrections18d4: [], scales15d4: []});
  const history = createSourceActorTransformHistoryRuntime({world});
  history.bindActor(id, {rotation76: vec(0), preRotation1d6a: vec(0), previousStepHeight6d4: 0, aimOrigin524: vec(0)});
  const floor = options.floor ?? layer(0x1c, heights.map(value => triangle(value)));
  const ceiling24 = options.ceiling24 ?? layer(0x24, []), ceiling20 = options.ceiling20 ?? layer(0x20, []);
  const terrain: SourceActorTerrainGlobals = {floor1c: floor.source, ceiling24: ceiling24.source, ceiling20: ceiling20.source,
    upper34: options.upper ?? 100, lower68: options.lower ?? -100};
  const hooks: {actual?: () => void; history?: () => void; replaceActual?: boolean; replaceHistory?: boolean} = {};
  const events: string[] = [];
  const worldAdapter = {getActualActor(key: symbol) {
    check(this === worldAdapter, 'captured world receiver'); events.push('actual'); hooks.actual?.();
    const value = world.getActualActor(key); return hooks.replaceActual ? {...value} : value;
  }};
  const historyAdapter = {getActorBinding(key: symbol) {
    check(this === historyAdapter, 'captured history receiver'); events.push('history'); hooks.history?.();
    const value = history.getActorBinding(key); return hooks.replaceHistory ? {...value} : value;
  }};
  const sources = {world: worldAdapter, history: historyAdapter, terrain};
  const runtime = createSourceActorTerrainQueryRuntime(sources); runtime.bindActor(id); events.length = 0;
  const point = vec(100, 5, 100);
  return {id, actual, world, history, terrain, floor, ceiling24, ceiling20, runtime, point, sources,
    hooks, events, worldAdapter, historyAdapter, prior: history.getActorBinding(id),
    query: (clearance = 0) => runtime.query8003d6e4(id, point, clearance)};
}

export function runActorTerrainQuerySelfTests(): void {
  {
    const f = fixture([2, 4, 8]);
    check(f.floor.source.cells[0]!.list.entries[0] === f.floor.grid.triangles[0], 'real source triangle identities survive strict view');
    check(f.query() === 4, 'best floor below query limit is selected from actual nonempty floor cell');
    check(f.query(100) === 8 && f.query(101) === 8, 'initial clearance >= upper sentinel selects maximum including equality');
    check(f.query(-10) === 2, 'no eligible best floor falls back to minimum');
    f.point.y = 4; check(f.query() === 2, 'query ceiling is strict, equality does not update best');
    f.point.y = 8; check(f.query() === 4, 'strict limit keeps a lower best even with equal higher triangle');
    f.point.y = 5;
    check(f.actual.pos.y === 0 && f.actual.savedGroundPos.y === 0 && f.actual.stepHeight === 0 && f.prior.previousStepHeight6d4 === 0,
      'query never writes actual current/history fields');
    check(Object.keys(f.runtime).join(',') === 'getActualActor,getHistoryBinding,getTerrainGlobals,bindActor,query8003d6e4,queryNormal8003de80,queryHeightNormal8003e0a8', 'no persistent result/normal/height surface');
    check(f.runtime.getTerrainGlobals() === f.terrain, 'read-only accessor returns the same actual global owner');
    check(isSourceActorTerrainQueryRuntime(f.runtime) && Object.isFrozen(f.runtime), 'genuine terrain identity is frozen');
    for (const fake of [null, undefined, {}, {...f.runtime}, Object.create(f.runtime)])
      check(!isSourceActorTerrainQueryRuntime(fake), 'terrain brand cannot be copied or inherited');
    check(f.runtime.getActualActor(f.id) === f.actual && f.runtime.getHistoryBinding(f.id) === f.prior,
      'metadata accessors retain actual/history owners without a copied result surface');
    rejects(() => f.runtime.getActualActor(Symbol()), 'unknown/non-owned');
    rejects(() => f.runtime.getHistoryBinding(Symbol()), 'unknown/non-owned');
  }
  for (const heights of [[], [-200], [100]]) {
    const f = fixture(heights); check(f.query() === (heights[0] === -200 ? -200 : -100), 'source sentinel fallback and below-lower minimum');
  }
  {
    const f = fixture([2, 100, 120]); f.point.y = 200;
    check(f.query() === 2, 'best floor must be strictly below real empty-ceiling upper sentinel');
    check(f.query(100) === 120, 'maximum path does not filter by clearance or ceiling');
  }
  for (const maximum of [105, 120]) {
    const f = fixture([2, maximum]);
    // Entry clearance 100 selects maximum; query Y 5 makes the local limit 105.
    // Maximum is independently accumulated even at/above that query limit.
    check(f.query(100) === maximum, 'maximum accumulation is not filtered by equality with or height above the query limit');
  }
  {
    const f = fixture([2, 4]); f.actual.pos.y = 1; f.actual.savedGroundPos.y = -1;
    // The real negative displacement is -2, but clearance stays 0 and limit 5.
    // Incorrectly applying it makes limit 3 and selects 2 instead of 4.
    check(f.query() === 4, 'negative top displacement must not lower the limit and replace the best eligible floor');
  }
  {
    const f = fixture([2, 7, 15]); f.actual.pos.y = 1; f.actual.savedGroundPos.y = 6;
    const clearance = 0; check(f.query(clearance) === 7 && clearance === 0, 'positive previous-current displacement adjusts only local clearance');
    f.actual.savedGroundPos.y = -1; check(f.query() === 2, 'negative displacement does not decrease clearance');
    f.actual.savedGroundPos.y = 1; f.prior.previousStepHeight6d4 = 10;
    check(f.query() === 7, 'actual previous height is consumed');
    f.actual.stepHeight = 10; check(f.query() === 2, 'actual current height subtracts from previous top');
    f.actual.pos.y = 999; f.actual.savedGroundPos.y = 999; f.point.y = 16;
    check(f.query() === 15, 'caller-local point Y, not actor position Y, supplies query limit');
  }
  {
    const f = fixture([4, 5]); f.actual.savedGroundPos.y = 2 ** 24; f.prior.previousStepHeight6d4 = 1;
    f.actual.pos.y = 2 ** 24;
    check(f.query() === 4, 'previous top rounds at its source fadds before displacement subtraction');
    f.actual.savedGroundPos.y = 2 ** 24 + 2; f.prior.previousStepHeight6d4 = 0; f.actual.stepHeight = 1; f.point.y = 4;
    check(f.query() === 5, 'current top separately rounds before displacement subtraction');
  }
  {
    const f = fixture([-1, 0], {upper: 2 ** 25}); f.actual.savedGroundPos.y = 1; f.point.y = -(2 ** 24);
    check(f.query(2 ** 24) === -1, 'adjusted clearance rounds before source query-limit addition');
  }
  for (const height of [2 ** -149, -(2 ** -149)]) {
    const f = fixture([height]); check(Object.is(f.query(), height), 'full source plane arithmetic preserves finite subnormal heights');
  }
  {
    const f = fixture([2, 7]); let calls = 0;
    f.hooks.history = () => {if (++calls === 2) {f.prior.previousStepHeight6d4 = 10;}};
    check(f.query() === 7 && calls === 2, 'post-ceiling history/current operands reload rather than using cached first threshold');
  }
  {
    const f = fixture([2, 8, 15]); f.terrain.upper34 = 10; f.actual.savedGroundPos.y = 20;
    check(f.query(0) === 8, 'large adjusted local clearance does not recompute original maximum-selection flag');
  }
  for (const axis of ['x', 'z'] as const) for (const value of [-7500, 7500, -8000, 8000]) {
    const f = fixture(); f.point[axis] = value; f.point.y = -0;
    f.actual.stepHeight = NaN; f.actual.pos.y = NaN; f.actual.savedGroundPos.y = NaN; f.prior.previousStepHeight6d4 = NaN;
    f.terrain.upper34 = NaN; f.terrain.lower68 = NaN;
    if (axis === 'x') f.point.z = NaN;
    check(Object.is(f.query(NaN), -0) && !f.events.includes('history'), 'outside bounds return caller Y before terrain/history/clearance operands');
  }
  for (const contact of [1, 127, 128, 255]) {
    const f = fixture(); f.actual.supportContact1db = contact; f.point.x = NaN; f.terrain.upper34 = NaN;
    rejects(f.query, 'nonzero supporting contact');
  }
  for (const contact of [-1, 256, 0.5, NaN]) {
    const f = fixture(); f.actual.supportContact1db = contact; rejects(f.query, 'supportContact1db: integer');
  }
  for (const key of ['ceiling24', 'ceiling20'] as const) {
    const bad = triangle(1); bad.vertices[0].x = NaN;
    const f = fixture([2], {[key]: layer(key === 'ceiling24' ? 0x24 : 0x20, [bad])});
    f.actual.pos.y = NaN;
    rejects(f.query, `nonempty ${key} triangle body unsupported`);
  }
  {
    const f = fixture([2], {ceiling24: layer(0x24, [triangle(1)])});
    Object.defineProperty(f.terrain, 'ceiling20', {get() {throw Error('later layer read');}});
    rejects(f.query, 'nonempty ceiling24');
  }
  {
    const f = fixture([2], {ceiling20: layer(0x20, [triangle(1)])});
    Object.defineProperty(f.terrain, 'floor1c', {get() {throw Error('later floor read');}});
    rejects(f.query, 'nonempty ceiling20');
  }
  {
    const outside = triangle(88, 700, 700); outside.normal = vec(NaN); outside.vertices[0].y = NaN;
    const f = fixture([], {floor: layer(0x1c, [outside, triangle(2)])});
    check(f.query() === 2, 'edge rejection skips unsupported normal and vertex Y loads');
  }
  {
    const f = fixture(); let called = false;
    const t = f.floor.grid.triangles[0]!;
    for (const [owner, key] of [[t, 'planeD'], [t, 'marker'], [t, 'bounds2d'],
      [t.vertices[1], 'y'], [t.vertices[2], 'y'], [f.floor.grid.header, 'cellSize'],
      [f.floor.grid.header, 'bounds2d']] as const) {
      Object.defineProperty(owner, key, {get() {called = true; throw Error('unread operand getter');}});
    }
    check(f.query() === 2 && !called, 'unread source geometry/header operands remain untouched');
  }
  for (const [x, z, expected] of [[0, 0, 2], [0, 100, 2], [250, 250, 2], [400, 400, -100], [100, -100, -100]]) {
    const f = fixture(); f.point.x = x!; f.point.z = z!;
    check(f.query() === expected, 'three ordered edge branches admit equality and reject each outside edge');
  }
  {
    const f = fixture([], {floor: layer(0x1c, [triangle(88, 700, 700), triangle(2)])}); let called = false;
    Object.defineProperty(f.floor.grid.triangles[0]!, 'normal', {get() {called = true; throw Error('skipped normal getter');}});
    check(f.query() === 2 && !called, 'skipped triangle does not validate normal owner or invoke getter');
  }
  {
    const f = fixture([2], {ceiling24: layer(0x24, [triangle(9)])}); let called = false;
    Object.defineProperty(f.ceiling24.grid.triangles[0]!, 'vertices', {get() {called = true; throw Error('ceiling body getter');}});
    rejects(f.query, 'nonempty ceiling24'); check(!called, 'ceiling body refusal does not inspect triangle owner');
  }
  for (const [axis, value] of [['x', 1], ['z', 1], ['y', 0], ['y', -1], ['x', NaN]] as const) {
    const bad = triangle(2); bad.normal[axis] = value;
    const f = fixture([], {floor: layer(0x1c, [bad])}); rejects(f.query, Number.isNaN(value) ? 'finite exact source' : 'nonflat source normal');
  }
  {
    const flat = triangle(-0), f = fixture([], {floor: layer(0x1c, [flat])});
    check(Object.is(f.query(), -0), 'negative plane zero survives when all source product/add signs are negative');
    f.point.x = 0; f.point.z = 0;
    check(Object.is(f.query(), 0), 'flat plane still executes signed-zero multiply/add/divide instead of returning vertex Y');
  }
  {
    const f = fixture([], {floor: layer(0x1c, [triangle(3), triangle(9, 500)], [[0], [], [1], []], vec(0), 17),
      ceiling24: layer(0x24, [], [[], [], [], []], vec(0), 13), ceiling20: layer(0x20, [], [[], [], [], []], vec(0), 11)});
    f.point.x = 600; f.point.y = 20;
    check(f.query() === 9, 'source grid uses authenticated 500 spacing and X*Z stride, not host cell-size fields');
  }
  {
    const f = fixture([], {floor: layer(0x1c, [triangle(2, -500, -500)], [[0], [], [], []], vec(-500, 0, -500)),
      ceiling24: layer(0x24, [], [[], [], [], []], vec(-500, 0, -500)),
      ceiling20: layer(0x20, [], [[], [], [], []], vec(-500, 0, -500))});
    f.point.x = -400; f.point.z = -400; check(f.query() === 2, 'source origins are signed int32 values');
  }
  for (const test of [
    // ix=-32768, stride=32768, product=-2^30; source slwi2 wraps to cell 0.
    {nx: 1, nz: 32768, originX: 16384000, selected: 0, why: 'shifted low-word address wraps to the actual cell-zero list'},
    // The signed source origin 32767999 rounds to 32768000 before subtraction.
    {nx: 1, nz: 16384, originX: 32767999, selected: 0, why: 'signed origin converts to float32 before source coordinate subtraction'},
    // div32(131072496,500)=262145; an unrounded quotient truncates to 262144.
    {nx: 2, nz: 4096, originX: -131072496, selected: 4096, why: 'source quotient rounds before integer truncation and selects the real alternate cell'},
  ]) {
    const records = new Map([[0, 0], [test.selected, 1]]);
    const f = fixture([], {
      floor: integerLayer(0x1c, test.nx, test.nz, test.originX, [2, 7], records),
      ceiling24: integerLayer(0x24, test.nx, test.nz, test.originX, []),
      ceiling20: integerLayer(0x20, test.nx, test.nz, test.originX, []),
    });
    f.point.x = 0; f.point.z = 0; f.point.y = 10;
    check(f.query() === 7, test.why);
  }
  {
    const f = fixture(); f.point.x = -1; f.point.z = 0; check(f.query() === -100, 'negative fractional index truncates toward zero, not floor');
    f.point.x = -500; rejects(f.query, 'outside constructed storage');
  }
  {
    const a = 1 + 2 ** -23, b = 1 + 2 ** -22;
    const narrow: TriangleInput = {vertices: [vec(a, 2, 1), vec(b, 2, a), vec(-a, 2, -1)], normal: vec(0, 1, 0)};
    const f = fixture([], {floor: layer(0x1c, [narrow])}); f.point.x = 0; f.point.z = 0;
    check(1 * b < a * a && Math.fround(1 * b) === Math.fround(a * a), 'edge fixture distinguishes separate source products from unrounded products');
    check(f.query() === 2, 'edge products round separately before their comparison, including narrow equality');
  }
  {
    const f = fixture([], {floor: layer(0x1c, [triangle(2), triangle(7)], [[0], [], [1], []])});
    let calls = 0; f.hooks.history = () => {if (++calls === 2) f.point.x = 600;};
    check(f.query(100) === 7, 'floor cell uses reloaded caller X while edge scan uses saved stack X');
  }
  {
    const bad = triangle(2); bad.normal.x = 1;
    const f = fixture([], {floor: layer(0x1c, [bad])});
    f.floor.view.setUint32(f.floor.source.cells[0]!.list.sentinelOffset, 0, false);
    rejects(f.query, 'nonflat source normal X');
  }
  {
    const f = fixture(); f.floor.view.setUint32(f.floor.source.cells[3]!.list.sentinelOffset, 0, false);
    check(f.query() === 2, 'unselected source cell corruption is not inspected by query');
  }
  {
    const f = fixture(); f.floor.view.setUint32(f.floor.recordBase + 0x2c, 0, false);
    f.point.x = -1; f.point.z = -1;
    check(f.query() === -100, 'edge-rejected triangle leaves corrupt unread normal word untouched');
    f.point.x = 100; f.point.z = 100; rejects(f.query, 'source word changed');
  }
  {
    const f = fixture(); f.point.y = Math.fround(3.4028235e38); f.actual.stepHeight = Math.fround(3.4028235e38);
    rejects(f.query, 'overflow float32');
  }
  for (const bad of [NaN, Infinity, 0.1]) {
    const f = fixture(); f.point.y = bad; rejects(f.query, 'finite exact source float32');
  }
  {
    const f = fixture(); f.prior.previousStepHeight6d4 = NaN;
    rejects(f.query, 'previousStepHeight6d4');
  }
  {
    const f = fixture(); Object.defineProperty(f.point, 'z', {get() {throw Error('getter executed');}});
    rejects(f.query, 'z: own data property required');
  }
  {
    const f = fixture(); f.hooks.replaceActual = true; rejects(f.query, 'actual RomActor owner changed');
  }
  {
    const f = fixture(); f.hooks.replaceHistory = true; rejects(f.query, 'transform history owner changed');
  }
  {
    const f = fixture(); f.actual.pos = vec(0); rejects(f.query, 'pos owner changed');
  }
  {
    const f = fixture(); f.actual.savedGroundPos = vec(0); rejects(f.query, 'savedGroundPos owner changed');
  }
  {
    const f = fixture(); const oldActual = f.worldAdapter.getActualActor, oldHistory = f.historyAdapter.getActorBinding;
    f.worldAdapter.getActualActor = () => {throw Error('replacement method read');};
    f.historyAdapter.getActorBinding = () => {throw Error('replacement method read');};
    f.sources.world = {getActualActor: oldActual}; f.sources.history = {getActorBinding: oldHistory};
    check(f.query() === 2, 'original methods and receivers are captured, not mutable adapter properties');
  }
  {
    const f = fixture(); let caught = false;
    f.hooks.actual = () => {try {f.query();} catch {caught = true;}};
    rejects(f.query, 'caught same-runtime reentry'); check(caught, 'nested reentry was caught by adversarial adapter');
    delete f.hooks.actual; check(f.query() === 2, 'guard recovers for a later independent call');
  }
  {
    const f = fixture(); rejects(() => f.runtime.bindActor(f.id), 'already bound');
    rejects(() => f.runtime.query8003d6e4(Symbol('unowned'), f.point, 0), 'unknown/non-owned');
    const copy = {...f.floor.source}; Object.defineProperty(f.terrain, 'floor1c', {value: copy});
    rejects(f.query, 'not created from explicit source bytes');
  }
  {
    const f = fixture(); check(f.query() === 2, 'initial explicit layer');
    Object.defineProperty(f.terrain, 'floor1c', {value: layer(0x1c, [triangle(3)]).source});
    rejects(f.query, 'floor1c owner changed');
  }
  {
    const f = fixture(); Object.defineProperty(f.terrain, 'floor1c', {value: f.ceiling24.source});
    rejects(f.query, 'wrong source global layer identity');
  }
  {
    const f = fixture(); f.floor.view.setUint32(f.floor.source.cells[0]!.list.sentinelOffset, 0, false);
    rejects(f.query, 'source word changed');
  }
  runActorTerrainNormalQuerySelfTests();
  runActorTerrainHeightNormalQuerySelfTests();
}

export function runActorTerrainNormalQuerySelfTests(): void {
  const marked = (height: number, bits: number, x = 0, z = 0): TriangleInput => {
    const value = triangle(height, x, z); value.normal = vec(bits & 1 ? -0 : 0, 1, bits & 2 ? -0 : 0); return value;
  };
  const outputIs = (output: {x: number; y: number; z: number}, bits: number, why: string): void => {
    check(Object.is(output.x, bits & 1 ? -0 : 0) && output.y === 1 && Object.is(output.z, bits & 2 ? -0 : 0), why);
  };
  const withFloors = (triangles: TriangleInput[], upper = 100, lower = -100) => {
    const f = fixture([], {floor: layer(0x1c, triangles), upper, lower}), output = vec(71, 72, 73);
    return {...f, output, normal: (clearance = 0) => f.runtime.queryNormal8003de80(f.id, f.point, clearance, output)};
  };
  {
    const f = withFloors([marked(4, 1), marked(2, 2), marked(8, 3)]);
    check(f.normal() === 1, 'normal query returns in-range success');
    outputIs(f.output, 1, 'real best height wins instead of first/last triangle or default normal');
    f.point.y = 10; check(f.normal() === 1, 'normal query reruns explicit caller output');
    outputIs(f.output, 3, 'later higher eligible height replaces the actual output');
    check(f.actual.pos.y === 0 && f.actual.savedGroundPos.y === 0 && f.actual.stepHeight === 0 && f.prior.previousStepHeight6d4 === 0,
      'normal query writes no actual current/history scalar');
    const other = vec(99); f.point.y = 3;
    check(f.runtime.queryNormal8003de80(f.id, f.point, 0, other) === 1, 'second caller-local output accepted');
    outputIs(other, 2, 'second caller receives its own selected normal');
    outputIs(f.output, 3, 'earlier caller output is not a persistent result shadow');
  }
  {
    const f = withFloors([marked(4, 1), marked(4, 2)]);
    f.normal(); outputIs(f.output, 2, 'equal best height overwrites with the later actual normal');
  }
  for (const triangles of [[], [marked(-101, 3)], [marked(5, 3)], [marked(100, 3)]]) {
    const f = withFloors(triangles);
    check(f.normal() === 1, 'no eligible floor still returns one, not false/no-hit');
    outputIs(f.output, 0, 'no eligible floor retains real default stores, with no minimum fallback');
  }
  {
    const f = withFloors([marked(-100, 3)]);
    f.normal(); outputIs(f.output, 3, 'height equal to real lower sentinel remains eligible');
  }
  {
    const f = withFloors([marked(2, 1), marked(5, 2)]);
    f.normal(); outputIs(f.output, 1, 'strict query height limit excludes equality');
    f.point.y = 6; f.normal(); outputIs(f.output, 2, 'eligible height becomes selected after fresh caller Y load');
  }
  {
    const f = withFloors([marked(2, 1), marked(10, 2), marked(12, 3)], 10);
    f.point.y = 20; f.normal(); outputIs(f.output, 1, 'strict real ceiling excludes equal and higher floors');
    f.normal(100); outputIs(f.output, 1, 'normal query never selects height-query maximum fallback, even with clearance above upper');
  }
  {
    const f = withFloors([marked(2, 1), marked(7, 2), marked(15, 3)]);
    f.actual.pos.y = 1; f.actual.savedGroundPos.y = 6;
    f.normal(); outputIs(f.output, 2, 'positive actual previous-current top adjusts local clearance');
    f.actual.savedGroundPos.y = -1; f.normal(); outputIs(f.output, 1, 'negative top displacement leaves clearance unchanged');
    f.actual.savedGroundPos.y = 1; f.prior.previousStepHeight6d4 = 10;
    f.normal(); outputIs(f.output, 2, 'actual previous step is consumed');
    f.actual.stepHeight = 10; f.normal(); outputIs(f.output, 1, 'actual current step subtracts from previous top');
  }
  {
    const f = withFloors([marked(2, 1), marked(4, 2)]);
    f.actual.pos.y = 1; f.actual.savedGroundPos.y = -1;
    // The real delta is -2. The source leaves the limit at 5, selecting 4;
    // incorrectly adding that delta lowers the limit to 3 and selects 2.
    f.normal(); outputIs(f.output, 2, 'negative top delta must not change which actual floor normal is selected');
  }
  {
    const f = withFloors([marked(4, 1), marked(5, 2)]);
    f.actual.savedGroundPos.y = 2 ** 24; f.prior.previousStepHeight6d4 = 1; f.actual.pos.y = 2 ** 24;
    f.normal(); outputIs(f.output, 1, 'normal previous top rounds before displacement subtraction');
    f.actual.savedGroundPos.y = 2 ** 24 + 2; f.prior.previousStepHeight6d4 = 0; f.actual.stepHeight = 1; f.point.y = 4;
    f.normal(); outputIs(f.output, 2, 'normal current top separately rounds before displacement subtraction');
  }
  {
    const f = withFloors([marked(-1, 1), marked(0, 2)], 2 ** 25);
    f.actual.savedGroundPos.y = 1; f.point.y = -(2 ** 24);
    f.normal(2 ** 24); outputIs(f.output, 1, 'normal adjusted clearance rounds before caller-Y addition');
  }
  {
    const f = withFloors([marked(2, 1), marked(7, 2)]); let histories = 0;
    f.hooks.history = () => {
      outputIs(f.output, 0, 'default stores precede history and ceiling reads');
      if (++histories === 2) {f.prior.previousStepHeight6d4 = 10; f.terrain.upper34 = NaN;}
    };
    f.normal(); outputIs(f.output, 2, 'post-ceiling history is freshly read and no extra upper sentinel read follows floor scan');
    check(histories === 2, 'normal query reads both source history operands');
  }
  {
    const f = withFloors([marked(2, 1), marked(7, 2)]); let histories = 0, savedReloads = 0;
    f.hooks.history = () => {
      if (++histories === 1) f.hooks.actual = () => {
        // This first actual-owner reload follows both real ceiling lists.
        // The initial ceiling threshold already captured saved Y = 0.
        f.actual.savedGroundPos.y = 6; savedReloads++; delete f.hooks.actual;
      };
    };
    f.normal(); outputIs(f.output, 2, 'fresh post-ceiling saved Y raises the limit to 11 and selects height 7, not height 2');
    check(histories === 2 && savedReloads === 1, 'actual saved-Y change occurs at the one post-ceiling owner reload');
  }
  {
    const f = withFloors([marked(2, 3)]), largestFloat = Math.fround(3.4028235e38);
    f.point.y = largestFloat; f.actual.stepHeight = largestFloat;
    rejects(f.normal, 'overflow float32');
    outputIs(f.output, 0, 'caller Y plus actual step overflows after default stores even with both ceilings empty');
    check(!f.events.includes('history'), 'ceiling-point Y addition refuses before first history and ceiling lookup');
  }
  {
    const f = withFloors([marked(2, 3)]); f.terrain.upper34 = NaN;
    f.hooks.history = () => {f.terrain.upper34 = 100;};
    f.normal(); outputIs(f.output, 3, 'normal query has no height-query upper load before building ceiling arguments');
  }
  for (const displacement of [0, 1]) {
    const f = withFloors([]); let histories = 0, getterCalled = false;
    f.actual.savedGroundPos.y = displacement;
    f.hooks.history = () => {if (++histories === 2) Object.defineProperty(f.point, 'y', {
      get() {getterCalled = true; throw Error('late point Y accessor');},
    });};
    rejects(() => f.normal(NaN), displacement > 0 ? 'saved clearance' : 'y: own data property');
    check(!getterCalled, 'normal clearance admission follows its first reached arithmetic and own-data Y load');
    outputIs(f.output, 0, 'late caller/clearance refusal keeps source default stores');
  }
  {
    const f = fixture([], {floor: layer(0x1c, [marked(2, 1), marked(7, 2)], [[0], [], [1], []])}), output = vec(99);
    let histories = 0;
    f.hooks.history = () => {if (++histories === 2) {f.point.x = 600; f.point.y = 8;}};
    check(f.runtime.queryNormal8003de80(f.id, f.point, 0, output) === 1, 'normal lookup reaches real second source cell');
    outputIs(output, 2, 'floor lookup reloads caller X/Y while triangle edges retain saved local X/Z');
  }
  for (const [x, z, expected] of [[0, 0, 3], [0, 100, 3], [250, 250, 3], [-100, 100, 0], [400, 400, 0], [100, -100, 0]]) {
    const f = withFloors([marked(2, 3)]); f.point.x = x!; f.point.z = z!;
    f.normal(); outputIs(f.output, expected!, 'normal scan admits edge equality and rejects all three outside edge directions');
  }
  for (const axis of ['x', 'z'] as const) for (const bound of [-7500, 7500, -8000, 8000]) {
    const f = withFloors([marked(2, 3)]); f.point[axis] = bound;
    f.point.y = NaN; if (axis === 'x') f.point.z = NaN;
    f.actual.pos.y = NaN; f.actual.stepHeight = NaN; f.actual.savedGroundPos.y = NaN;
    f.prior.previousStepHeight6d4 = NaN; f.terrain.upper34 = NaN; f.terrain.lower68 = NaN;
    check(f.normal(NaN) === 0 && !f.events.includes('history'), 'out-of-bounds normal path does not load Y/clearance/history/terrain');
    outputIs(f.output, 0, 'outside bounds writes actual default before returning zero');
  }
  for (const support of [1, 127, 128, 255]) {
    const f = withFloors([]); f.actual.supportContact1db = support; f.point.x = NaN;
    rejects(f.normal, 'nonzero supporting contact normal-copy branch');
    check(f.output.x === 71 && f.output.y === 72 && f.output.z === 73, 'excluded support path refuses before zero-path output stores');
  }
  for (const key of ['ceiling24', 'ceiling20'] as const) {
    const f = fixture([], {[key]: layer(key === 'ceiling24' ? 0x24 : 0x20, [triangle(1)])}), output = vec(44);
    f.actual.pos.y = NaN;
    Object.defineProperty(f.terrain, 'floor1c', {get() {throw Error('floor must not be reached');}});
    if (key === 'ceiling24') Object.defineProperty(f.terrain, 'ceiling20', {get() {throw Error('second ceiling must not be reached');}});
    rejects(() => f.runtime.queryNormal8003de80(f.id, f.point, NaN, output), `nonempty ${key}`);
    outputIs(output, 0, 'reached ceiling refusal preserves earlier default stores and precedes later clearance/floor loads');
  }
  {
    const bad = marked(3, 0); bad.normal.x = 1;
    const f = withFloors([marked(2, 3), bad]);
    rejects(f.normal, 'nonflat source normal X');
    outputIs(f.output, 3, 'later unsupported triangle preserves the earlier real selected normal');
  }
  for (const [axis, value] of [['x', 1], ['z', 1], ['y', 0], ['y', -1], ['x', NaN]] as const) {
    const bad = marked(200, 0); bad.normal[axis] = value;
    const f = withFloors([bad]);
    rejects(f.normal, Number.isNaN(value) ? 'finite exact source' : 'nonflat source normal');
    outputIs(f.output, 0, 'reached unsupported normal refuses before height filtering and retains default');
  }
  {
    const skipped = marked(88, 0, 700, 700); skipped.normal.x = NaN; skipped.vertices[0].y = NaN;
    const f = withFloors([skipped, marked(2, 3)]);
    f.normal(); outputIs(f.output, 3, 'edge rejection skips malformed normal and vertexY but scans the next real pointer');
  }
  {
    const f = withFloors([marked(2, 3)]);
    f.floor.view.setUint32(f.floor.recordBase + 0x10, 0xffffffff, false);
    f.floor.view.setUint32(f.floor.recordBase + 0x0c, 0xffffffff, false);
    rejects(f.normal, `source word changed at 0x${(f.floor.recordBase + 0x10).toString(16)}`);
    outputIs(f.output, 0, 'normal query loads v2X before v1Z, preserving its own source schedule');
  }
  {
    const f = withFloors([marked(2, 3)]); let getterCalled = false;
    const t = f.floor.grid.triangles[0]!;
    for (const [owner, key] of [[t, 'planeD'], [t, 'marker'], [t.vertices[1], 'y'], [t.vertices[2], 'y'],
      [f.floor.grid.header, 'cellSize'], [f.floor.grid.header, 'bounds2d']] as const)
      Object.defineProperty(owner, key, {get() {getterCalled = true; throw Error('unread normal-query operand');}});
    f.normal(); outputIs(f.output, 3, 'normal query uses actual plane arithmetic and source spacing');
    check(!getterCalled, 'normal query never inspects unrelated geometry or grid fields');
  }
  for (const axis of ['x', 'y', 'z'] as const) {
    const f = withFloors([]); Object.defineProperty(f.output, axis, {writable: false}); f.point.x = NaN;
    rejects(f.normal, `normal output ${axis}: non-writable`);
    check(Object.is(f.output.x, axis === 'x' ? 71 : 0) && f.output.y === (axis === 'z' ? 1 : 72) && f.output.z === 73,
      'default normal stores preserve exact X/Y/Z refusal prefix before bounds');
  }
  {
    const f = withFloors([marked(2, 3)]); let histories = 0;
    f.hooks.history = () => {if (++histories === 2) Object.defineProperty(f.output, 'y', {writable: false});};
    rejects(f.normal, 'normal output y: non-writable');
    check(Object.is(f.output.x, -0) && f.output.y === 1 && Object.is(f.output.z, 0),
      'selected normal X store survives Y refusal; later Z store does not occur');
  }
  {
    const f = withFloors([marked(2, 3)]); let getterCalled = false;
    Object.defineProperty(f.output, 'y', {get() {getterCalled = true; return 72;}});
    rejects(f.normal, 'normal output y: own data property');
    check(!getterCalled && Object.is(f.output.x, 0) && f.output.z === 73, 'output accessor refused without calling it after X prefix');
  }
  {
    const f = withFloors([marked(2, 3)]);
    rejects(() => f.runtime.queryNormal8003de80(f.id, f.point, 0, f.point), 'aliased caller-local');
    rejects(() => f.runtime.queryNormal8003de80(f.id, f.point, 0, f.actual.pos), 'aliased caller-local');
    rejects(() => f.runtime.queryNormal8003de80(f.id, f.point, 0, f.actual.savedGroundPos), 'aliased caller-local');
    check(f.point.x === 100 && f.actual.pos.y === 0, 'known output aliases refuse before corrupting source/input records');
  }
  {
    const f = withFloors([marked(2, 3)]);
    f.floor.view.setUint32(f.floor.source.cells[0]!.list.sentinelOffset, 0, false);
    rejects(f.normal, 'source word changed'); outputIs(f.output, 3, 'real sentinel failure preserves completed selected output stores');
  }
  {
    const f = withFloors([marked(2, 3)]); f.hooks.replaceActual = true;
    rejects(f.normal, 'actual RomActor owner changed');
    check(f.output.x === 71, 'replaced actual owner refuses before default stores');
    f.hooks.replaceActual = false; f.hooks.replaceHistory = true;
    rejects(f.normal, 'transform history owner changed'); outputIs(f.output, 0, 'history owner replacement preserves earlier default');
  }
  {
    const f = withFloors([marked(2, 3)]); let caught = false;
    f.hooks.history = () => {try {f.normal();} catch {caught = true;}};
    rejects(f.normal, 'caught same-runtime reentry'); check(caught, 'nested normal query refused');
    outputIs(f.output, 0, 'caught reentry leaves only prior source stores');
    delete f.hooks.history; f.normal(); outputIs(f.output, 3, 'normal query guard recovers on next independent call');
  }
}

export function runActorTerrainHeightNormalQuerySelfTests(): void {
  const marked = (height: number, bits: number, x = 0, z = 0): TriangleInput => {
    const value = triangle(height, x, z); value.normal = vec(bits & 1 ? -0 : 0, 1, bits & 2 ? -0 : 0); return value;
  };
  const outputIs = (output: SourceActorTerrainNormalOutput, bits: number, why: string): void => {
    check(Object.is(output.x, bits & 1 ? -0 : 0) && output.y === 1 && Object.is(output.z, bits & 2 ? -0 : 0), why);
  };
  const withFloors = (triangles: TriangleInput[], upper = 100, lower = -100) => {
    const f = fixture([], {floor: layer(0x1c, triangles), upper, lower}), output = createSourceActorTerrainNormalOutput();
    Object.assign(output, vec(71, 72, 73));
    return {...f, output, heightNormal: (clearance = 0) => f.runtime.queryHeightNormal8003e0a8(f.id, f.point, clearance, output)};
  };
  {
    const scratch = createSourceActorTerrainNormalOutput();
    check(Number.isNaN(scratch.x) && Number.isNaN(scratch.y) && Number.isNaN(scratch.z),
      'new output is uninitialized scratch, not a default successful normal');
    check(scratch !== createSourceActorTerrainNormalOutput(), 'each caller receives a distinct fresh output owner');
  }
  {
    const f = withFloors([marked(4, 1), marked(2, 2), marked(8, 3)]);
    check(f.heightNormal() === 4, 'height-normal returns eligible best height');
    outputIs(f.output, 1, 'height-normal retains eligible best normal, not last triangle');
    check(f.heightNormal(-10) === 2, 'height-normal returns minimum fallback');
    outputIs(f.output, 2, 'minimum fallback copies its own normal unlike normal-only query');
    check(f.heightNormal(100) === 8, 'height-normal selects maximum on initial clearance equality');
    outputIs(f.output, 3, 'maximum fallback copies its own normal');
    const other = createSourceActorTerrainNormalOutput(); f.point.y = 3;
    check(f.runtime.queryHeightNormal8003e0a8(f.id, f.point, 0, other) === 2, 'new caller-local output accepted');
    outputIs(other, 2, 'new caller owns its selected normal'); outputIs(f.output, 3, 'earlier output is not overwritten or retained');
    check(f.actual.pos.y === 0 && f.actual.savedGroundPos.y === 0 && f.actual.stepHeight === 0 && f.prior.previousStepHeight6d4 === 0,
      'height-normal only writes the explicit caller output');
  }
  for (const clearance of [0, -10, 100]) {
    const f = withFloors([marked(4, 1), marked(4, 2)]);
    check(f.heightNormal(clearance) === 4, 'all height-normal accumulation modes preserve equal heights');
    outputIs(f.output, 2, 'eligible/minimum/maximum ties replace with later normal');
  }
  for (const test of [
    {triangles: [] as TriangleInput[], clearance: 0, height: -100, bits: 0},
    {triangles: [], clearance: 100, height: -100, bits: 0},
    {triangles: [marked(-200, 3)], clearance: 0, height: -200, bits: 3},
    {triangles: [marked(-200, 3)], clearance: 100, height: -100, bits: 0},
    {triangles: [marked(100, 3)], clearance: 0, height: -100, bits: 3},
    {triangles: [marked(120, 3)], clearance: 0, height: -100, bits: 0},
    {triangles: [marked(-100, 3)], clearance: 0, height: -100, bits: 3},
  ]) {
    const f = withFloors(test.triangles);
    check(f.heightNormal(test.clearance) === test.height, 'sentinel and unfiltered fallback heights match source');
    outputIs(f.output, test.bits, 'fallback normal copied even if selected height equals a source sentinel');
  }
  {
    const f = withFloors([marked(2, 1), marked(5, 2), marked(100, 3), marked(120, 3)]);
    check(f.heightNormal() === 2, 'eligible height limit excludes equality'); outputIs(f.output, 1, 'equality does not replace best normal');
    f.point.y = 200;
    check(f.heightNormal() === 5, 'eligible ceiling excludes equal and higher floors'); outputIs(f.output, 2, 'ceiling filtering retains lower normal');
    check(f.heightNormal(100) === 120, 'maximum is independent of query and ceiling limits'); outputIs(f.output, 3, 'maximum normal passes no eligibility filter');
  }
  {
    const f = withFloors([marked(2, 1), marked(7, 2), marked(15, 3)]);
    f.actual.pos.y = 1; f.actual.savedGroundPos.y = 6;
    check(f.heightNormal() === 7, 'positive previous-current top increases local clearance'); outputIs(f.output, 2, 'adjusted best normal follows height');
    f.actual.savedGroundPos.y = -1;
    check(f.heightNormal() === 2, 'negative displacement leaves clearance unchanged'); outputIs(f.output, 1, 'negative delta does not alter output selection');
    f.actual.savedGroundPos.y = 1; f.prior.previousStepHeight6d4 = 10;
    check(f.heightNormal() === 7, 'actual history step is consumed');
    f.actual.stepHeight = 10; check(f.heightNormal() === 2, 'actual current step subtracts from previous top');
  }
  {
    const f = withFloors([marked(2, 1), marked(8, 2), marked(15, 3)], 10);
    f.actual.savedGroundPos.y = 20;
    check(f.heightNormal() === 8, 'maximum flag uses entry clearance, not adjusted local limit');
    outputIs(f.output, 2, 'large positive delta does not turn eligible best into maximum');
  }
  {
    const f = withFloors([marked(4, 1), marked(5, 2)]);
    f.actual.savedGroundPos.y = 2 ** 24; f.prior.previousStepHeight6d4 = 1; f.actual.pos.y = 2 ** 24;
    check(f.heightNormal() === 4, 'previous top rounds before subtraction');
    f.actual.savedGroundPos.y = 2 ** 24 + 2; f.prior.previousStepHeight6d4 = 0; f.actual.stepHeight = 1; f.point.y = 4;
    check(f.heightNormal() === 5, 'current top rounds before subtraction'); outputIs(f.output, 2, 'rounding affects normal selection');
  }
  {
    const f = withFloors([marked(-1, 1), marked(0, 2)], 2 ** 25);
    f.actual.savedGroundPos.y = 1; f.point.y = -(2 ** 24);
    check(f.heightNormal(2 ** 24) === -1, 'clearance adjustment rounds before caller-Y sum'); outputIs(f.output, 1, 'rounded limit excludes zero');
  }
  for (const height of [2 ** -149, -(2 ** -149), -0]) {
    const f = withFloors([marked(height, 0)]);
    check(Object.is(f.heightNormal(), height), 'separate plane operations retain subnormal and signed-zero result');
    if (Object.is(height, -0)) {
      f.point.x = 0; f.point.z = 0;
      check(Object.is(f.heightNormal(), 0), 'plane zero comes from real multiply/add/divide rather than vertex Y shortcut');
    }
  }
  {
    const f = withFloors([marked(2, 1), marked(7, 2)]); let histories = 0;
    f.hooks.history = () => {
      outputIs(f.output, 0, 'default source stores precede both history reads');
      if (++histories === 2) f.prior.previousStepHeight6d4 = 10;
    };
    check(f.heightNormal() === 7 && histories === 2, 'post-ceiling history step is freshly read'); outputIs(f.output, 2, 'fresh history affects selected normal');
  }
  {
    const f = fixture([], {floor: layer(0x1c, [marked(2, 1), marked(7, 2)], [[0], [], [1], []])});
    const output = createSourceActorTerrainNormalOutput(); let histories = 0;
    f.hooks.history = () => {if (++histories === 2) {f.point.x = 600; f.point.y = 8;}};
    check(f.runtime.queryHeightNormal8003e0a8(f.id, f.point, 0, output) === 7,
      'cell and limit reload caller point while edges retain original local X/Z'); outputIs(output, 2, 'second cell normal is selected');
  }
  {
    const f = withFloors([marked(4, 3)]); Object.assign(f.actual.pos, f.point);
    check(f.runtime.queryHeightNormal8003e0a8(f.id, f.actual.pos, 0, f.output) === 4,
      'actual actor.pos is an admitted point owner, as passed by 677b0'); outputIs(f.output, 3, 'actual point query writes separate local output');
  }
  for (const axis of ['x', 'z'] as const) for (const bound of [-7500, 7500, -8000, 8000]) {
    const f = withFloors([marked(2, 3)]); f.point[axis] = bound;
    f.point.y = NaN; if (axis === 'x') f.point.z = NaN;
    f.actual.pos.y = NaN; f.actual.stepHeight = NaN; f.actual.savedGroundPos.y = NaN;
    f.prior.previousStepHeight6d4 = NaN; f.terrain.upper34 = NaN; f.terrain.lower68 = NaN;
    check(f.heightNormal(NaN) === -5000 && !f.events.includes('history'),
      'outside height-normal returns authenticated -5000 before caller Y/clearance/terrain/history');
    outputIs(f.output, 0, 'outside return still performs genuine default stores');
  }
  for (const support of [1, 127, 128, 255]) {
    const f = withFloors([]); f.actual.supportContact1db = support; f.point.x = NaN;
    rejects(f.heightNormal, 'nonzero supporting contact height-normal transform');
    check(f.output.x === 71 && f.output.y === 72 && f.output.z === 73, 'support refusal precedes zero-support output stores');
  }
  for (const key of ['ceiling24', 'ceiling20'] as const) {
    const f = fixture([], {[key]: layer(key === 'ceiling24' ? 0x24 : 0x20, [triangle(1)])}), output = createSourceActorTerrainNormalOutput();
    f.actual.pos.y = NaN;
    Object.defineProperty(f.terrain, 'floor1c', {get() {throw Error('unreached floor getter');}});
    if (key === 'ceiling24') Object.defineProperty(f.terrain, 'ceiling20', {get() {throw Error('unreached ceiling getter');}});
    rejects(() => f.runtime.queryHeightNormal8003e0a8(f.id, f.point, 0, output), `nonempty ${key}`);
    outputIs(output, 0, 'ceiling refusal retains default and skips later floor/current-position loads');
  }
  {
    const f = withFloors([]); f.terrain.upper34 = NaN; f.actual.stepHeight = NaN;
    rejects(() => f.heightNormal(NaN), 'upper34'); outputIs(f.output, 0, 'initial global upper read precedes clearance comparison');
    f.terrain.upper34 = 100; rejects(() => f.heightNormal(NaN), 'saved clearance');
    check(!f.events.includes('history'), 'height-normal validates original clearance before ceiling arguments, unlike 3de80');
  }
  {
    const skipped = marked(88, 0, 700, 700); skipped.normal.x = NaN; skipped.vertices[0].y = NaN;
    const f = withFloors([skipped, marked(2, 3)]);
    check(f.heightNormal() === 2, 'edge-rejected malformed triangle is not a normal/height fallback candidate'); outputIs(f.output, 3, 'scan continues to real eligible pointer');
  }
  {
    const bad = marked(3, 0); bad.normal.x = 1;
    const f = withFloors([marked(2, 3), bad]); rejects(f.heightNormal, 'nonflat source normal X');
    outputIs(f.output, 3, 'later unsupported normal retains earlier completed candidate stores');
  }
  for (const [axis, value] of [['x', 1], ['z', 1], ['y', 0], ['y', -1], ['x', NaN]] as const) {
    const bad = marked(200, 0); bad.normal[axis] = value;
    const f = withFloors([bad]); rejects(f.heightNormal, Number.isNaN(value) ? 'finite exact source' : 'nonflat source normal');
    outputIs(f.output, 0, 'unsupported normal refuses before height-based eligibility filtering');
  }
  {
    const f = withFloors([marked(2, 3)]);
    f.floor.view.setUint32(f.floor.recordBase + 0x10, 0xffffffff, false);
    f.floor.view.setUint32(f.floor.recordBase + 0x0c, 0xffffffff, false);
    rejects(f.heightNormal, `source word changed at 0x${(f.floor.recordBase + 0x0c).toString(16)}`);
    outputIs(f.output, 0, 'height-normal loads v1Z before v2X, unlike normal-only query');
  }
  {
    const bad = marked(2, 0); bad.normal.x = 1;
    const f = withFloors([bad]); f.floor.view.setUint32(f.floor.recordBase + 0x2c, 0xffffffff, false);
    rejects(f.heightNormal, `source word changed at 0x${(f.floor.recordBase + 0x2c).toString(16)}`);
    outputIs(f.output, 0, 'normal X/Z/Y captures precede first unsupported X arithmetic');
  }
  for (const axis of ['x', 'y', 'z'] as const) {
    const f = withFloors([]); Object.defineProperty(f.output, axis, {writable: false}); f.point.x = NaN;
    rejects(f.heightNormal, `normal output ${axis}: non-writable`);
    check(Object.is(f.output.x, axis === 'x' ? 71 : 0) && f.output.y === (axis === 'z' ? 1 : 72) && f.output.z === 73,
      'initial height-normal stores retain exact X/Y/Z refusal prefix before bounds');
  }
  for (const clearance of [0, -10, 100]) {
    const f = withFloors([marked(clearance === 100 ? 120 : 4, 3)]); let histories = 0;
    f.hooks.history = () => {if (++histories === 2) Object.defineProperty(f.output, 'y', {writable: false});};
    rejects(() => f.heightNormal(clearance), 'normal output y: non-writable');
    check(Object.is(f.output.x, -0) && f.output.y === 1 && Object.is(f.output.z, 0),
      'candidate/minimum/maximum output X survives a Y refusal, with Z left at default');
  }
  {
    const f = withFloors([]); let histories = 0;
    f.hooks.history = () => {if (++histories === 2) Object.defineProperty(f.output, 'x', {writable: false});};
    rejects(f.heightNormal, 'normal output x: non-writable');
    outputIs(f.output, 0, 'empty minimum fallback performs real stores instead of returning default success');
  }
  {
    const f = withFloors([marked(2, 3)]); let getterCalled = false;
    Object.defineProperty(f.output, 'y', {get() {getterCalled = true; return 72;}});
    rejects(f.heightNormal, 'normal output y: own data property');
    check(!getterCalled && Object.is(f.output.x, 0) && f.output.z === 73, 'output accessor refuses without invoking it after X prefix');
  }
  {
    const f = withFloors([marked(2, 3)]);
    for (const output of [vec(1), {...f.output}, Object.create(f.output), f.floor.grid.triangles[0]!.normal])
      rejects(() => f.runtime.queryHeightNormal8003e0a8(f.id, f.point, 0, output as SourceActorTerrainNormalOutput), 'fresh branded');
    for (const output of [f.point, f.actual.pos, f.actual.savedGroundPos])
      rejects(() => f.runtime.queryHeightNormal8003e0a8(f.id, f.point, 0, output as SourceActorTerrainNormalOutput), 'aliased caller-local');
    rejects(() => f.runtime.queryHeightNormal8003e0a8(f.id, f.output, 0, f.output), 'aliased caller-local');
    check(f.point.x === 100 && f.actual.pos.y === 0 && Object.is(f.floor.grid.triangles[0]!.normal.x, -0),
      'unbranded/known aliases refuse before corrupting source or caller input');
  }
  for (const key of ['motion', 'targetCache5e8', 'pos', 'savedGroundPos'] as const) {
    const f = withFloors([]); f.actual[key] = f.output; f.point.x = 7500;
    rejects(f.heightNormal, 'aliased caller-local height-normal output adopted');
    check(f.output.x === 71 && f.output.y === 72 && f.output.z === 73,
      'branded output adopted as actual vector is rejected before even outside default stores');
  }
  for (const where of ['history', 'terrain'] as const) {
    const f = withFloors([]); f.point.x = 7500;
    // The canonical history record is sealed, but its scalar storage remains
    // writable. An object adopted into that slot is an alias, not a scalar read.
    if (where === 'history') Object.defineProperty(f.prior, 'previousStepHeight6d4', {value: f.output});
    else Object.defineProperty(f.terrain, 'adoptedOutput', {value: f.output});
    rejects(f.heightNormal, 'aliased caller-local height-normal output adopted');
    check(f.output.x === 71 && f.output.y === 72 && f.output.z === 73, 'output adopted by known history/global owner is rejected before stores');
  }
  for (const key of ['pos', 'savedGroundPos'] as const) {
    const f = withFloors([]); f.actual[key] = vec(NaN); f.point.x = 7500;
    rejects(f.heightNormal, `${key} owner changed`);
    check(f.output.x === 71 && f.output.y === 72 && f.output.z === 73,
      'replacement vector identity is reconciled before outside stores without inspecting its numeric fields');
  }
  {
    const f = withFloors([marked(2, 3)]); let getterCalled = false;
    for (const owner of [f.actual, f.terrain]) Object.defineProperty(owner, 'unreadOwner', {
      get() {getterCalled = true; throw Error('metadata scan invoked getter');},
    });
    check(f.heightNormal() === 2 && !getterCalled, 'output ownership admission reads descriptors without invoking unrelated owner accessors');
    outputIs(f.output, 3, 'metadata-only ownership check leaves source arithmetic intact');
  }
  for (const clearance of [0, -10, 100]) {
    const f = withFloors([marked(clearance === 100 ? 120 : 4, 3)]); let histories = 0;
    f.hooks.history = () => {if (++histories === 2) f.actual.motion = f.output;};
    rejects(() => f.heightNormal(clearance), 'aliased caller-local height-normal output adopted');
    outputIs(f.output, 0, 'adoption after default is rejected before subsequent candidate/minimum/maximum normal stores');
  }
  {
    const f = withFloors([marked(2, 3)]); f.floor.view.setUint32(f.floor.source.cells[0]!.list.sentinelOffset, 0, false);
    rejects(f.heightNormal, 'source word changed'); outputIs(f.output, 3, 'sentinel refusal retains completed candidate stores');
  }
  {
    const f = withFloors([marked(2, 3)]); f.hooks.replaceActual = true;
    rejects(f.heightNormal, 'actual RomActor owner changed'); check(f.output.x === 71, 'actual owner refusal precedes output default');
    f.hooks.replaceActual = false; f.hooks.replaceHistory = true;
    rejects(f.heightNormal, 'transform history owner changed'); outputIs(f.output, 0, 'history replacement keeps prior default stores');
    rejects(() => f.runtime.queryHeightNormal8003e0a8(Symbol(), f.point, 0, f.output), 'unknown/non-owned');
  }
  {
    const f = withFloors([marked(2, 3)]); let caught = false;
    f.hooks.history = () => {try {f.heightNormal();} catch {caught = true;}};
    rejects(f.heightNormal, 'caught same-runtime reentry'); check(caught, 'nested height-normal query refused');
    outputIs(f.output, 0, 'caught reentry leaves prior default, never reports success');
    delete f.hooks.history; check(f.heightNormal() === 2, 'height-normal guard recovers for independent call'); outputIs(f.output, 3, 'independent result succeeds');
  }
}
