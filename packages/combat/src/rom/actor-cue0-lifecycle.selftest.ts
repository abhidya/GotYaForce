import {hitBin, sourceTerrainGrid} from '@gf/formats';
import {createRomActor} from './actor.js';
import {createSourceActorCue0LifecycleRuntime, isSourceActorCue0LifecycleRuntime,
  hasIncompleteSourceActorCue0Lifecycle, bindSourceActorCue0Frame, type SourceActorCue0LifecycleBinding,
  type SourceActorCue0LifecycleSources} from './actor-cue0-lifecycle.js';
import {createSourceActorTerrainQueryRuntime, type SourceActorTerrainGlobals} from './actor-terrain-query.js';
import {createSourceActorCueResetRuntime, type SourceActorCueResetBinding} from './actor-cue-reset.js';
import type {SourceActorWorldMatrixBinding} from './actor-world-matrix.js';
import type {SourceActorJointMappingHeader} from './actor-joint-mapping.js';

function check(ok: boolean, why: string): void {if (!ok) throw Error(`[actor-cue0-lifecycle-test] ${why}`);}
function equal(actual: unknown, expected: unknown, why: string): void {
  check(Object.is(actual, expected), `${why}: got ${String(actual)}, expected ${String(expected)}`);
}
function rejects(run: () => unknown, fragment: string): void {
  let error = ''; try {run();} catch (e) {error = String(e);}
  check(error.includes(fragment), `expected ${fragment}, got ${error || 'success'}`);
}
const vec = (x: number, y = x, z = x) => ({x, y, z});
const readonly = (owner: object, key: string): void => {Object.defineProperty(owner, key, {writable: false});};
function watchProperties(run: () => void, observe: (owner: object, key: PropertyKey) => void): void {
  const original = Object.getOwnPropertyDescriptor;
  Object.getOwnPropertyDescriptor = ((owner: object, key: PropertyKey) => {
    observe(owner, key); return original(owner, key);
  }) as typeof original;
  try {run();} finally {Object.getOwnPropertyDescriptor = original;}
}
/** Explicit synthetic STIH records, using the genuine strict terrain view.
 * No geometry callback or synthetic query/cue implementation participates. */
function layer(offset: sourceTerrainGrid.SourceTerrainLayerOffset, height?: number) {
  const count = height === undefined ? 0 : 1, recordBase = 0x58;
  const bytes = new Uint8Array(recordBase + count * 0x38), view = new DataView(bytes.buffer);
  const word = (at: number, value: number) => view.setUint32(at, value, false);
  word(0, 0x53544948); word(4, bytes.length); word(8, 500); word(12, 500);
  word(16, 2); word(20, 2); word(24, 0); word(28, 0); word(32, 0x20); word(36, recordBase - 8);
  word(0x28, 0x38 - 8); word(0x2c, 0x40 - 8); word(0x30, 0x44 - 8); word(0x34, 0x48 - 8);
  word(0x38, count ? 0 : 0xffffffff); word(0x3c, 0xffffffff);
  word(0x40, 0xffffffff); word(0x44, 0xffffffff); word(0x48, 0xffffffff);
  if (height !== undefined) {
    word(recordBase, 123);
    [0, height, 0, 0, height, 500, 500, height, 0, 0, 1, 0, 77].forEach((value, index) =>
      view.setFloat32(recordBase + 4 + 4 * index, value, false));
  }
  return sourceTerrainGrid.createSourceTerrainGrid(bytes, hitBin.parseStageHitGrid(bytes), offset);
}
function fixture(options: {defer?: boolean; height?: number; initial?: Partial<SourceActorCue0LifecycleBinding>;
  cueInitial?: Partial<SourceActorCueResetBinding>} = {}) {
  const id = Symbol('cue0 actor'), actual = Object.assign(createRomActor(), {hoverOffset668: 1, slopeMode698: 6, onLand754: null});
  delete (actual as Partial<typeof actual>).fbPhaseSlots; delete (actual as Partial<typeof actual>).shotByte1db3;
  Object.assign(actual.pos, vec(100, 5, 100)); Object.assign(actual.savedGroundPos, vec(100, 0, 100));
  actual.controlWord = 0; actual.stepHeight = 0; actual.supportContact1db = 0;
  actual.hSpeed = 4; actual.tierScale = 1; actual.lockYaw = 23;
  actual.ubCue = 0; actual.fbCue = 9; actual.ubState = -2; actual.fbState = -3;
  actual.prevUbState = -4; actual.prevFbState = -5; actual.fbPhase = 17;
  actual.cueTable = new Int8Array(56); actual.cueTable.fill(-1); actual.cueTable[54] = 8; actual.cueTable[55] = 7;
  const worldState = {mode4a0: 0} as SourceActorWorldMatrixBinding;
  const movementState = {byte661: 0, field66c: 0, field670: 0};
  const attributeState = {field674: 4};
  const mapping = {} as SourceActorJointMappingHeader;
  const historyState = {previousStepHeight6d4: 0, rotation76: vec(0), preRotation1d6a: vec(0), aimOrigin524: vec(0)};
  const dispatchState = {family1d88: null, shared1d8c: null, marker578: 0, marker1db3: 11};
  const hooks: Record<string, (() => unknown) | undefined> = {}, calls: Record<string, number> = {};
  const get = <T>(name: string, value: T): T => {
    calls[name] = (calls[name] ?? 0) + 1; return (hooks[name] ? hooks[name]!() : value) as T;
  };
  const world = {
    getActualActor(key: symbol) {check(this === world && key === id, 'captured world actor receiver'); return get('worldActual', actual);},
    getActorBinding(key: symbol) {check(this === world && key === id, 'captured world binding receiver'); return get('world', worldState);},
    getMappingActor(key: symbol) {check(this === world && key === id, 'captured world mapping receiver'); return get('mapping', mapping);},
  };
  const movement = {
    getActualActor(key: symbol) {check(this === movement && key === id, 'captured movement actor receiver'); return get('movementActual', actual);},
    getActorBinding(key: symbol) {check(this === movement && key === id, 'captured movement binding receiver'); return get('movement', movementState);},
  };
  const attribute = {
    getActualActor(key: symbol) {check(this === attribute && key === id, 'captured attribute actor receiver'); return get('attributeActual', actual);},
    getActorBinding(key: symbol) {check(this === attribute && key === id, 'captured attribute binding receiver'); return get('attribute', attributeState);},
  };
  const history = {getActorBinding(key: symbol) {
    check(this === history && key === id, 'captured history receiver'); return get('history', historyState);
  }};
  const globals: SourceActorTerrainGlobals = {floor1c: layer(0x1c, options.height ?? 2),
    ceiling20: layer(0x20), ceiling24: layer(0x24), upper34: 100, lower68: -100};
  const terrain = createSourceActorTerrainQueryRuntime({world, history, terrain: globals}); terrain.bindActor(id);
  const dispatch = {getSourceActor: () => get('dispatchMapping', mapping), getActorBinding: () => get('dispatch', dispatchState)};
  const cues = createSourceActorCueResetRuntime({world, dispatch});
  const cueInitial: Partial<SourceActorCueResetBinding> = {
    byte541: 1, byte542: 2, byte543: 3, byte544: 4, byte545: 5, byte546: 6, byte547: 7,
    byte588: 8, byte7ce: 9, byte7cf: 10,
  };
  cues.bindActor(id, options.cueInitial ?? cueInitial);
  const sources: SourceActorCue0LifecycleSources = {world, movement, attribute, terrain, cues};
  const runtime = createSourceActorCue0LifecycleRuntime(sources), initial = options.initial ?? {byte732: 0};
  const bind = () => runtime.bindActor(id, initial); if (!options.defer) bind();
  return {id, actual, worldState, movementState, attributeState, mapping, historyState, dispatchState, globals,
    world, movement, attribute, history, dispatch, terrain, cues, sources, initial, runtime, bind, hooks, calls,
    binding: () => runtime.getActorBinding(id), cueBinding: () => cues.getActorBinding(id),
    ground: () => runtime.updateTerrain(id), cue0: () => runtime.dispatchCue0(id),
    cue44: () => runtime.dispatchCue44(id), test690a0: () => runtime.test800690a0(id),
    test691d8: () => runtime.test800691d8(id)};
}
function poisoned(x: ReturnType<typeof fixture>): void {
  check(hasIncompleteSourceActorCue0Lifecycle(x.actual), 'actual identity retains incomplete lifecycle');
  x.actual.controlWord = 0x40; x.worldState.mode4a0 = 2; x.movementState.byte661 = 3; x.actual.ubCue = 9;
  rejects(x.ground, 'known incomplete cue0 lifecycle'); rejects(x.cue0, 'known incomplete cue0 lifecycle');
  x.actual.stateFlagA = 0; x.actual.inputEdge5d4 = 0; x.actual.statusWord5b4 = 0;
  rejects(x.cue44, 'known incomplete cue0 lifecycle'); rejects(x.test690a0, 'known incomplete cue0 lifecycle');
  rejects(() => x.runtime.assertActorComplete(x.id), 'known incomplete cue0 lifecycle');
  check(!hasIncompleteSourceActorCue0Lifecycle({...x.actual}), 'incomplete marker is actual identity only');
}
export function runActorCue0LifecycleSelfTests(): void {
  {
    //691d8 has one unsigned-byte gate. It must not demand any query operand
    // on mode2 and cannot fabricate a completed677b0 when the join is absent.
    const skip = fixture(); skip.worldState.mode4a0 = 2;
    skip.actual.hoverOffset668 = NaN; skip.actual.pos.y = NaN; skip.actual.stepHeight = NaN;
    skip.historyState.previousStepHeight6d4 = NaN;
    const reads: string[] = [];
    watchProperties(() => equal(skip.test691d8(), 0, 'unsigned mode2 returns native0 without ground'), (owner, key) => {
      if (owner === skip.worldState && key === 'mode4a0' || owner === skip.actual && key === 'hoverOffset668' ||
          owner === skip.actual.pos && key === 'y' || owner === skip.historyState && key === 'previousStepHeight6d4')
        reads.push(String(key));
    });
    equal(reads.join(','), 'mode4a0', '691d8 skip has no query operand load');
    check(!hasIncompleteSourceActorCue0Lifecycle(skip.actual), 'completed mode2 skip clears no source failure');
    for (const mode of [0, 1, 3, 127, 128, 255]) {
      const x = fixture(); x.worldState.mode4a0 = mode;
      rejects(x.test691d8, '800691f8 reached unsupported source call800677b0');
      check(hasIncompleteSourceActorCue0Lifecycle(x.actual), 'missing actual ground leaves caller permanently incomplete');
      x.worldState.mode4a0 = 2;
      rejects(x.test691d8, 'known incomplete cue0 lifecycle');
    }
    for (const mode of [-1, 256, NaN, 1.5]) {
      const x = fixture(); x.worldState.mode4a0 = mode;
      rejects(x.test691d8, 'mode4a0: integer out of bounds');
    }
    const fake = fixture();
    rejects(() => fake.runtime.bindGroundRuntime(fake.id, {} as never), 'ground requires genuine source runtime');
    equal(fake.runtime.getGroundRuntime(fake.id), undefined, 'forged ground never establishes a join');
    rejects(() => bindSourceActorCue0Frame({} as never, fake.runtime, fake.id, {} as never,
      {} as never, {} as never), 'private genuine frame binding');
  }

  {
    const x = fixture();
    check(isSourceActorCue0LifecycleRuntime(x.runtime), 'genuine brand');
    for (const fake of [null, undefined, {}, {...x.runtime}, Object.create(x.runtime)])
      check(!isSourceActorCue0LifecycleRuntime(fake), 'brand cannot be copied/inherited');
    check(Object.isFrozen(x.runtime) && Object.isSealed(x.binding()), 'methods frozen and explicit732 sealed');
    equal(x.runtime.getActualActor(x.id), x.actual, 'actual identity');
    equal(x.runtime.getWorldBinding(x.id), x.worldState, 'shared world');
    equal(x.runtime.getMappingActor(x.id), x.mapping, 'shared mapping');
    equal(x.runtime.getMovementBinding(x.id), x.movementState, 'shared movement');
    equal(x.runtime.getAttributeBinding(x.id), x.attributeState, 'shared674');
    equal(x.runtime.getTerrainRuntime(), x.terrain, 'genuine terrain'); equal(x.runtime.getTerrainGlobals(), x.globals, 'actual globals');
    equal(x.runtime.getHistoryBinding(x.id), x.historyState, 'shared history');
    equal(x.runtime.getCueRuntime(), x.cues, 'genuine cues'); equal(x.runtime.getCueBinding(x.id), x.cueBinding(), 'shared cue cells');
    equal(x.runtime.getDispatchBinding(x.id), x.dispatchState, 'shared dispatch');
    const owners = x.runtime.getSourceOwners(x.id);
    equal(x.runtime.getSourceOwners(x.id), owners, 'retained owner list'); check(Object.isFrozen(owners), 'frozen owner list');
    const expected = [x.binding(), x.attributeState, x.historyState, x.actual.pos, x.actual.savedGroundPos,
      x.historyState.rotation76, x.historyState.preRotation1d6a, x.historyState.aimOrigin524];
    check(owners.length === expected.length && expected.every((owner, i) => owners[i] === owner), 'only actual additional owners, no clone storage');
    equal(Object.keys(x.binding()).join(','), 'byte732', 'only missing732 cell');
    rejects(() => createSourceActorCue0LifecycleRuntime(x.sources).bindActor(x.id, {}), 'actual actor already claimed');
    rejects(x.bind, 'new symbol actor identity'); rejects(() => x.runtime.updateTerrain(Symbol()), 'unknown/non-owned');
    for (const key of ['terrain', 'cues'] as const) for (const fake of [undefined, null, {}, {...x.sources[key]}, Object.create(x.sources[key])])
      rejects(() => createSourceActorCue0LifecycleRuntime({...x.sources, [key]: fake}), `${key} requires genuine`);
  }
  {
    const x = fixture(); equal(x.ground(), 0, 'genuine ground helper completes0');
    equal(x.actual.pos.y, 2, 'real terrain height stored'); equal(x.actual.savedGroundPos.y, 0, 'saved Y not changed');
    equal(x.actual.hSpeed, 4, 'ground keeps speed'); equal(x.actual.slopeMode698, 6, 'ground keeps slope');
    equal(x.actual.ubCue, 0, 'direct helper does not dispatch cue'); equal(x.binding().byte732, 0, '732 remains unchanged');
    equal(x.runtime.assertActorComplete(x.id), undefined, 'complete ground clears host poison');
    equal(x.ground(), 0, 'completed direct helper can run again');
    const y = fixture(); rejects(y.cue0, '80059184 reached unsupported source call800699d8');
    equal(y.actual.pos.y, 2, 'dispatcher preserves real ground effect before unsupported next call'); poisoned(y);
  }
  {
    const x = fixture({initial: {}}); x.actual.controlWord = 0x40; x.worldState.mode4a0 = NaN;
    x.actual.pos.y = NaN; x.actual.hoverOffset668 = NaN; x.attributeState.field674 = NaN;
    equal(x.ground(), 0, 'control40 skips mode and every terrain scalar');
    equal(Object.keys(x.binding()).length, 0, 'no default732 added'); check(!hasIncompleteSourceActorCue0Lifecycle(x.actual), 'skip is complete');
    x.actual.controlWord = 0; x.worldState.mode4a0 = 2; equal(x.ground(), 0, 'mode2 skips terrain scalars');
    x.movementState.byte661 = 0x83; rejects(x.cue0, '800699d8');
    check(!hasIncompleteSourceActorCue0Lifecycle(x.actual), 'no-store helper before later refusal adds no poison');
    for (const bad of [-1, 256, .5, NaN, Infinity]) {
      const y = fixture(); y.movementState.byte661 = bad; rejects(y.cue0, 'byte661: integer');
      const z = fixture(); z.worldState.mode4a0 = bad; rejects(z.ground, 'mode4a0: integer');
    }
    for (const bad of [-1, 0x100000000, .5, NaN, Infinity]) {
      const y = fixture(); y.actual.controlWord = bad; rejects(y.ground, 'controlWord: integer');
    }
  }
  {
    const x = fixture({initial: {}}); x.movementState.byte661 = 3; x.actual.controlWord = NaN;
    x.worldState.mode4a0 = NaN; x.attributeState.field674 = NaN; x.actual.pos.y = NaN;
    equal(x.cue0(), undefined, 'movement3 ignores terrain and732 scalars');
    equal(x.actual.ubCue, 27, 'real upper cue1b'); equal(x.actual.fbCue, 27, 'real full cue1b');
    equal(x.actual.ubState, 7, 'actual upper table byte'); equal(x.actual.fbState, 8, 'actual full table byte');
    equal(x.actual.prevUbState, -2, 'upper prior state'); equal(x.actual.prevFbState, -3, 'full prior state');
    equal(x.cueBinding().byte7ce, 0, 'upper saves old cue'); equal(x.cueBinding().byte7cf, 9, 'full saves old cue');
    equal(x.actual.fbPhase, 0, 'real full phase clear'); equal(x.dispatchState.marker1db3, 0, 'real upper marker clear');
    check(!hasIncompleteSourceActorCue0Lifecycle(x.actual), 'both genuine returns finish dispatch');
    for (const upper of [-1, 7]) for (const full of [-1, 8]) {
      const y = fixture(); y.movementState.byte661 = 3; y.actual.cueTable![55] = upper; y.actual.cueTable![54] = full;
      y.cue0(); equal(y.actual.ubCue, upper === -1 ? 0 : 27, 'upper sentinel return ignored');
      equal(y.actual.fbCue, full === -1 ? 9 : 27, 'full call runs after either upper result');
      check(!hasIncompleteSourceActorCue0Lifecycle(y.actual), 'genuine sentinel returns complete dispatch');
    }
    const y = fixture(); y.movementState.byte661 = 3; readonly(y.cueBinding(), 'byte543');
    rejects(y.cue0, 'byte543: non-writable'); equal(y.actual.ubState, 7, 'upper completes before full failure');
    equal(y.actual.fbState, 8, 'full earlier stores retained'); equal(y.actual.fbPhase, 17, 'full later clear never executed'); poisoned(y);
    const z = fixture(); z.movementState.byte661 = 3; z.actual.cueTable = new Int8Array(1);
    rejects(z.cue0, 'indexed byte outside'); poisoned(z);
  }
  {
    const x = fixture({initial: {}}); rejects(x.ground, 'byte732: own data'); equal(x.actual.pos.y, 2, 'height stored before missing732'); poisoned(x);
    const y = fixture(); y.binding().byte732 = NaN; y.actual.savedGroundPos.y = NaN;
    // Outside-X real query avoids historyY and makes post-query read order visible.
    y.actual.pos.x = 7500; rejects(y.ground, 'byte732: integer'); equal(y.actual.pos.y, 5, 'even unchanged height store marks partial'); poisoned(y);
    const z = fixture(); z.actual.pos.x = 7500; z.actual.savedGroundPos.y = NaN; z.attributeState.field674 = NaN;
    rejects(z.ground, 'y: finite exact'); poisoned(z);
    const max = Math.fround((2 - 2 ** -23) * 2 ** 127);
    const w = fixture(); w.actual.pos.x = 7500; w.actual.pos.y = max; w.actual.savedGroundPos.y = -max;
    w.attributeState.field674 = NaN; rejects(w.ground, 'field674: finite exact'); poisoned(w);
    const v = fixture(); v.actual.pos.x = 7500; v.actual.pos.y = max; v.actual.savedGroundPos.y = -max;
    rejects(v.ground, 'overflow float32'); poisoned(v);
    const u = fixture(); readonly(u.actual.pos, 'y'); rejects(u.ground, 'y: non-writable');
    equal(u.actual.pos.y, 5, 'failed first store leaves originalY'); check(!hasIncompleteSourceActorCue0Lifecycle(u.actual), 'no successful store does not poison');
    const t = fixture(); t.actual.supportContact1db = 1; rejects(t.ground, 'nonzero supporting contact');
    check(!hasIncompleteSourceActorCue0Lifecycle(t.actual), 'real terrain pre-store failure does not poison');
    t.actual.controlWord = 0x40; equal(t.ground(), 0, 'unchanged actor can take later skipped helper');
  }
  {
    const x = fixture({height: 8}); x.actual.pos.x = 200; x.actual.pos.z = 100;
    x.actual.savedGroundPos.x = 100; x.actual.savedGroundPos.z = 120;
    equal(x.ground(), 0, 'upper-step changedXZ completes raw rollback');
    equal(x.actual.pos.x, 100, 'rollbackX'); equal(x.actual.pos.y, 0, 'rollbackY'); equal(x.actual.pos.z, 120, 'rollbackZ');
    const y = fixture({height: 8}); equal(y.ground(), 0, 'upper-step unchangedXZ completes'); equal(y.actual.pos.y, 8, 'unchangedXZ keeps groundY');
    const z = fixture({height: 8}); z.actual.pos.x = 200; readonly(z.actual.pos, 'z');
    rejects(z.ground, 'z: non-writable'); equal(z.actual.pos.x, 100, 'rollbackX precedes readonlyZ');
    equal(z.actual.pos.y, 0, 'rollbackY precedes readonlyZ'); poisoned(z);
    const w = fixture(); w.actual.pos.x = 7500; w.actual.pos.y = 8; w.actual.savedGroundPos.x = -0;
    Object.defineProperty(w.actual.savedGroundPos, 'z', {get() {throw Error('source getter must not run');}, configurable: true});
    rejects(w.ground, 'z: own data'); equal(w.actual.pos.x, -0, 'rawX preserves signed zero before laterZ failure');
    equal(w.actual.pos.y, 0, 'rawY copied before rawZ load'); poisoned(w);
    const v = fixture(); v.actual.pos.x = 7500; v.actual.pos.y = 4; v.actual.savedGroundPos.x = NaN;
    Object.defineProperty(v.actual.pos, 'z', {get() {throw Error('skippedZ getter');}, configurable: true});
    equal(v.ground(), 0, 'delta==threshold skips X/Z comparisons and copying');
    const u = fixture({height: 8}); u.actual.pos.x = 0; u.actual.savedGroundPos.x = -0;
    u.actual.pos.z = 0; u.actual.savedGroundPos.z = -0;
    equal(u.ground(), 0, 'unordered compare equality treats +0/-0 equal'); equal(u.actual.pos.x, 0, 'equal signedzeros are not rolled back');
  }
  {
    for (const raw of [1, 127, 128, 255]) {
      const x = fixture(); x.binding().byte732 = raw; x.actual.pos.x = 200; x.actual.pos.y = -0;
      rejects(x.ground, '80068eb8 reached unsupported frsqrte'); equal(x.actual.pos.y, -0, 'ledge restores originalY including negative zero');
      equal(x.actual.hSpeed, 4, 'positive distance refuses before speed read/write'); poisoned(x);
    }
    const x = fixture({height: -8}); x.actual.pos.x = 200; x.actual.tierScale = NaN;
    rejects(x.ground, '80068eb8 reached unsupported frsqrte'); equal(x.actual.pos.y, 5, 'negative delta below-threshold restores originalY'); poisoned(x);
    const y = fixture({height: -4}); y.actual.pos.x = 200; equal(y.ground(), 0, 'equal negative threshold does not activate ledge');
    equal(y.actual.pos.y, -4, 'threshold equality keeps terrainY');
    const z = fixture(); z.binding().byte732 = 128; z.actual.tierScale = NaN; z.actual.hSpeed = NaN;
    rejects(z.ground, 'tierScale: finite exact'); equal(z.actual.pos.y, 5, 'zero norm restoresY before scale load'); poisoned(z);
    const w = fixture(); w.binding().byte732 = 255; w.actual.tierScale = 0; w.actual.hSpeed = NaN;
    rejects(w.ground, 'hSpeed: finite exact'); poisoned(w);
    for (const scale of [0, -0]) {
      const v = fixture(); v.binding().byte732 = 1; v.actual.tierScale = scale;
      rejects(v.ground, '80068f0c fdivs zero divisor'); equal(v.actual.slopeMode698, 6, 'zero divisor before slope store'); poisoned(v);
    }
    for (const scale of [1, -1, 2 ** -149, -(2 ** -149)]) {
      const v = fixture(); v.binding().byte732 = 1; v.actual.tierScale = scale; v.actual.hSpeed = -1;
      rejects(v.ground, '800452a0 after hSpeed store'); equal(v.actual.hSpeed, scale < 0 ? -0 : 0, 'zero-only divide exact sign');
      equal(v.actual.lockYaw, 23, 'unsupported atan never fabricates yaw'); equal(v.actual.slopeMode698, 6, 'atan failure before slope store'); poisoned(v);
    }
    const v = fixture(); v.binding().byte732 = 1; v.actual.hSpeed = -0;
    rejects(v.ground, '8006a5a4 after slopeMode698 store'); equal(v.actual.slopeMode698, 30, 'source30 retained before helper refusal');
    equal(v.actual.hSpeed, -0, 'equal speed does not store +0'); poisoned(v);
    const u = fixture(); u.binding().byte732 = 1; readonly(u.actual, 'slopeMode698');
    rejects(u.ground, 'slopeMode698: non-writable'); poisoned(u);
    // The separately rounded square can underflow even when source deltas are
    // nonzero. Do not replace the source operations with host hypot/sqrt.
    const tiny = fixture(); tiny.binding().byte732 = 1;
    tiny.actual.pos.x = 2 ** -75; tiny.actual.savedGroundPos.x = 0;
    tiny.actual.pos.z = 0; tiny.actual.savedGroundPos.z = 0;
    rejects(tiny.ground, '8006a5a4 after slopeMode698 store');
    equal(tiny.actual.slopeMode698, 30, 'half-minimum square ties to zero before the branch'); poisoned(tiny);
    const positive = fixture(); positive.binding().byte732 = 1;
    positive.actual.pos.x = Math.fround(2 ** -75 * (1 + 2 ** -23)); positive.actual.savedGroundPos.x = 0;
    positive.actual.pos.z = 0; positive.actual.savedGroundPos.z = 0;
    rejects(positive.ground, '80068eb8 reached unsupported frsqrte'); poisoned(positive);
    // Source dz subtract precedes loading savedX, and z square precedes the
    // fused x square/add. Outside-X query avoids these operands until ledge.
    const delta = fixture(); delta.binding().byte732 = 1; delta.actual.pos.x = 7500;
    delta.actual.pos.z = Math.fround((2 - 2 ** -23) * 2 ** 127);
    delta.actual.savedGroundPos.z = -delta.actual.pos.z; delta.actual.savedGroundPos.x = NaN;
    rejects(delta.ground, 'overflow float32'); equal(delta.actual.pos.y, 5, 'overflow retains restoreY'); poisoned(delta);
    const square = fixture(); square.binding().byte732 = 1; square.actual.pos.x = 7500;
    square.actual.pos.z = 2 ** 64; square.actual.savedGroundPos.z = 0;
    rejects(square.ground, 'fmuls result: finite exact'); poisoned(square);
    const fused = fixture(); fused.binding().byte732 = 1; fused.actual.pos.x = 2 ** 64;
    fused.actual.savedGroundPos.x = 0; fused.actual.pos.z = 0; fused.actual.savedGroundPos.z = 0;
    rejects(fused.ground, 'overflow float32'); poisoned(fused);

  }
  {
    // Retained provider identities and methods, never copied binding snapshots.
    const x = fixture(); x.sources.world = {} as never; x.world.getActualActor = () => {throw Error('replacement must not run');};
    equal(x.ground(), 0, 'captured world methods/receivers survive provider method replacement');
    for (const key of ['worldActual', 'world', 'mapping', 'movementActual', 'movement', 'attributeActual', 'attribute', 'history']) {
      const y = fixture(); y.hooks[key] = () => ({}); rejects(y.ground, 'owner changed');
      equal(y.actual.pos.y, 5, 'changed owner rejected before source store');
    }
    for (const key of ['dispatchMapping', 'dispatch']) {
      const y = fixture(); y.movementState.byte661 = 3; y.hooks[key] = () => ({});
      rejects(y.cue0, 'owner changed'); poisoned(y);
    }
    const y = fixture(); y.actual.pos = {...y.actual.pos}; rejects(y.ground, 'actual position: owner changed');
    const z = fixture(); z.actual.savedGroundPos = {...z.actual.savedGroundPos}; rejects(z.ground, 'actual saved position: owner changed');
    const w = fixture(); w.historyState.rotation76 = {...w.historyState.rotation76}; rejects(w.ground, 'history rotation76: owner changed');
    const v = fixture(); v.hooks.attribute = () => {try {v.ground();} catch {} return v.attributeState;};
    rejects(v.ground, 'caught same-runtime reentry'); equal(v.actual.pos.y, 5, 'caught metadata reentry prevents first store');
    const u = fixture(); let entered = false;
    u.hooks.worldActual = () => {
      if (!entered && (u.calls.worldActual ?? 0) > 0) {entered = true; try {u.cue0();} catch {}}
      return u.actual;
    };
    rejects(u.ground, 'caught same-runtime reentry');
    const partial = fixture(); partial.movementState.byte661 = 3;
    let visits = 0;
    partial.hooks.worldActual = () => {
      if (++visits === 3) {try {partial.ground();} catch {}}
      return partial.actual;
    };
    rejects(partial.cue0, 'caught same-runtime reentry');
    equal(partial.actual.ubCue, 27, 'upper stores retained before caught full-callee reentry'); poisoned(partial);
  }
  {
    // Cue44 has its own genuine initial store and never takes cue0's movement3
    // fast path. Empty children retain their exact reached call boundaries.
    const x = fixture(); x.movementState.byte661 = 3;
    const order: string[] = [];
    watchProperties(() => rejects(x.cue44, 'unsupported source call800699d8'), (owner, key) => {
      if (owner === x.cueBinding() && key === 'byte588' || owner === x.actual && key === 'controlWord')
        order.push(String(key));
    });
    equal(order.join(','), 'byte588,controlWord,controlWord', '588 store before branch and genuine68df8 control reload');
    equal(x.cueBinding().byte588, 1, 'same canonical cue588 receives initial1');
    equal(x.actual.pos.y, 2, 'ground44 invokes actual terrain before699d8');
    equal(x.actual.ubCue, 0, 'movement3 does not dispatch upper1b in cue44');
    equal(x.actual.fbCue, 9, 'movement3 does not dispatch full1b in cue44'); poisoned(x);
    const air = fixture({initial: {}}); air.actual.controlWord = 0x40;
    air.worldState.mode4a0 = NaN; air.actual.pos.y = NaN; air.attributeState.field674 = NaN;
    air.movementState.byte661 = NaN;
    rejects(air.cue44, 'unsupported source call800699d8');
    equal(air.cueBinding().byte588, 1, 'air44 writes588 before real699d8 boundary');
    check(Number.isNaN(air.actual.pos.y), 'air44 never invents a ground call'); poisoned(air);
    const same = fixture({initial: {}}); same.cueBinding().byte588 = 1; same.worldState.mode4a0 = 2;
    rejects(same.cue44, 'unsupported source call800699d8');
    equal(same.actual.pos.y, 5, 'mode2 ground helper genuinely skips terrain'); poisoned(same);
    const invalid = fixture(); invalid.actual.controlWord = NaN;
    rejects(invalid.cue44, 'controlWord: integer'); equal(invalid.cueBinding().byte588, 1, '588 precedes failing control read'); poisoned(invalid);
    const oldInvalid = fixture(); oldInvalid.cueBinding().byte588 = NaN; oldInvalid.actual.controlWord = NaN;
    rejects(oldInvalid.cue44, 'controlWord: integer'); equal(oldInvalid.cueBinding().byte588, 1, 'stb does not load overwritten588'); poisoned(oldInvalid);
    const missing = fixture({cueInitial: {}}); missing.actual.controlWord = NaN;
    rejects(missing.cue44, 'byte588: own data');
    check(!hasIncompleteSourceActorCue0Lifecycle(missing.actual), 'first absent588 store has no effect marker');
    const ro = fixture(); readonly(ro.cueBinding(), 'byte588'); ro.actual.controlWord = NaN;
    rejects(ro.cue44, 'byte588: non-writable'); equal(ro.cueBinding().byte588, 8, 'failed first store preserves588');
    check(!hasIncompleteSourceActorCue0Lifecycle(ro.actual), 'failed first store remains retryable');
    ro.actual.stateFlagA = 0; equal(ro.test690a0(), 0, 'no-effect failed44 does not poison genuine early690a0');
    const equalReadonly = fixture(); equalReadonly.cueBinding().byte588 = 1; readonly(equalReadonly.cueBinding(), 'byte588');
    rejects(equalReadonly.cue44, 'byte588: non-writable');
    check(!hasIncompleteSourceActorCue0Lifecycle(equalReadonly.actual), 'equal588 still attempts its real store');
  }
  {
    // This helper does not read later flags, cue data or control when an actual
    // early gate fails. No absent scalar is hydrated and no fallback runs.
    for (const flag of [0, 0x38, 0x80, 0xbf]) {
      const x = fixture(); x.actual.stateFlagA = flag;
      x.actual.inputEdge5d4 = NaN; x.actual.statusWord5b4 = NaN; x.actual.controlWord = NaN;
      x.actual.cueTable = null;
      equal(x.test690a0(), 0, '690a0 absent state40 returns genuine0 lazily');
      equal(x.cueBinding().byte588, 8, 'direct early helper never stores588');
      check(!hasIncompleteSourceActorCue0Lifecycle(x.actual), 'early helper completes without poison');
    }
    const edge = fixture(); edge.actual.stateFlagA = 0x40; edge.actual.inputEdge5d4 = 0xfffffffe;
    edge.actual.statusWord5b4 = NaN; edge.actual.controlWord = NaN;
    equal(edge.test690a0(), 0, 'edge bit1 absent skips later status/control');
    const status = fixture(); status.actual.stateFlagA = 0x40; status.actual.inputEdge5d4 = 1;
    status.actual.statusWord5b4 = 0xfffffeff; status.actual.controlWord = NaN;
    equal(status.test690a0(), 0, 'status100 absent skips cue/control');
    const sentinel = fixture(); sentinel.actual.stateFlagA = 0x40; sentinel.actual.inputEdge5d4 = 1;
    sentinel.actual.statusWord5b4 = 0x100; sentinel.actual.controlWord = NaN;
    const order: string[] = [];
    watchProperties(() => equal(sentinel.test690a0(), 0, 'genuine upper5 sentinel0'), (owner, key) => {
      if (owner === sentinel.actual && ['stateFlagA', 'inputEdge5d4', 'statusWord5b4', 'cueTable', 'controlWord'].includes(String(key)))
        order.push(String(key));
    });
    equal(order.join(','), 'stateFlagA,inputEdge5d4,statusWord5b4,cueTable', '690a0 gates and upper cue precede any5e0 load');
    equal(sentinel.actual.ubCue, 0, 'sentinel never changes upper cue'); equal(sentinel.cueBinding().byte588, 8, 'sentinel never clears588');
    check(!hasIncompleteSourceActorCue0Lifecycle(sentinel.actual), 'completed sentinel clears conservative helper poison');
    equal(sentinel.test690a0(), 0, 'completed sentinel may repeat');
    for (const [key, bads] of [
      ['stateFlagA', [-1, 256, .5, NaN, Infinity]],
      ['inputEdge5d4', [-1, 0x100000000, .5, NaN, Infinity]],
      ['statusWord5b4', [-1, 0x100000000, .5, NaN, Infinity]],
    ] as const) for (const bad of bads) {
      const x = fixture(); x.actual.stateFlagA = 0x40; x.actual.inputEdge5d4 = 1; x.actual.statusWord5b4 = 0x100;
      x.actual[key] = bad; rejects(x.test690a0, `${key}: integer`);
      check(!hasIncompleteSourceActorCue0Lifecycle(x.actual), 'pre-cue invalid gate has no effect marker');
    }
    const getter = fixture(); getter.actual.stateFlagA = 0x40;
    Object.defineProperty(getter.actual, 'inputEdge5d4', {get() {throw Error('must not invoke gate getter');}, configurable: true});
    rejects(getter.test690a0, 'inputEdge5d4: own data');
    const missing = fixture(); delete missing.actual.stateFlagA;
    rejects(missing.test690a0, 'stateFlagA: own data');
  }
  {
    const active = () => {
      const x = fixture(); x.actual.stateFlagA = 0x40; x.actual.inputEdge5d4 = 1; x.actual.statusWord5b4 = 0x100;
      x.actual.cueTable![11] = -9; x.actual.controlWord = 0xfedcba98; return x;
    };
    const x = active(), order: string[] = [];
    watchProperties(() => rejects(x.test690a0, 'unsupported source call8005c080'), (owner, key) => {
      if (owner === x.actual && ['stateFlagA', 'inputEdge5d4', 'statusWord5b4', 'cueTable', 'controlWord'].includes(String(key)) ||
          owner === x.cueBinding() && key === 'byte588') order.push(String(key));
    });
    equal(order.join(','), 'stateFlagA,inputEdge5d4,statusWord5b4,cueTable,byte588,controlWord,controlWord',
      'real upper5 reset precedes control load then mask store');
    equal(x.actual.ubCue, 5, 'actual upper cue5 selected'); equal(x.actual.ubState, -9, 'actual signed cue row used');
    equal(x.actual.prevUbState, -2, 'real previous upper state'); equal(x.cueBinding().byte7ce, 0, 'real saved upper cue');
    equal(x.cueBinding().byte588, 0, 'genuine upper5 clears canonical588');
    equal(x.dispatchState.marker1db3, 0, 'genuine upper5 clears actual marker');
    equal(x.actual.controlWord, 0x00dc0000, '690a0 masks actual control; later2000 OR is forbidden before5c080 returns');
    equal(x.actual.fbCue, 9, 'helper never calls full-body cue'); poisoned(x);
    for (const control of [0, 0x00a50000, 0xffffffff]) {
      const y = active(); y.actual.controlWord = control;
      rejects(y.test690a0, 'unsupported source call8005c080');
      equal(y.actual.controlWord, control & 0x00ff0000, 'source mask includes equal-value control stores'); poisoned(y);
    }
    const bad = active(); bad.actual.controlWord = NaN;
    rejects(bad.test690a0, 'controlWord: integer'); equal(bad.actual.ubCue, 5, 'upper5 effects precede malformed control'); poisoned(bad);
    const ro = active(); readonly(ro.actual, 'controlWord');
    rejects(ro.test690a0, 'controlWord: non-writable'); equal(ro.actual.ubCue, 5, 'upper5 effects precede readonly control');
    equal(ro.actual.controlWord, 0xfedcba98, 'failed mask store keeps old control');
    check(hasIncompleteSourceActorCue0Lifecycle(ro.actual), 'readonly mask failure retains lifecycle marker');
    rejects(ro.test690a0, 'known incomplete cue0 lifecycle');
    const equalReadonly = active(); equalReadonly.actual.controlWord = 0x00a50000; readonly(equalReadonly.actual, 'controlWord');
    rejects(equalReadonly.test690a0, 'controlWord: non-writable');
    equal(equalReadonly.actual.ubCue, 5, 'equal control mask still attempts its real store after upper5');
    const partial = active(); readonly(partial.cueBinding(), 'byte546');
    rejects(partial.test690a0, 'byte546: non-writable'); equal(partial.actual.ubCue, 5, 'partial upper5 prefix retained');
    equal(partial.cueBinding().byte547, 0, 'earlier phase clear retained'); equal(partial.cueBinding().byte588, 8, 'later phase clear unreached');
    equal(partial.actual.controlWord, 0xfedcba98, 'mask not reached after partial cue failure'); poisoned(partial);
    const table = active(); table.actual.cueTable = new Int8Array(1);
    rejects(table.test690a0, 'indexed byte outside'); poisoned(table);
    const captured = active(); captured.sources.cues = {} as never; captured.sources.world = {} as never;
    captured.world.getActualActor = () => {throw Error('replacement world method must not run');};
    rejects(captured.test690a0, 'unsupported source call8005c080');
    equal(captured.actual.ubCue, 5, 'retained genuine cue5 and captured world receiver survive source replacement'); poisoned(captured);
    const reentry = active(); reentry.hooks.dispatch = () => {
      try {reentry.test690a0();} catch { /* Deliberate caught same-runtime reentry. */ }
      return reentry.dispatchState;
    };
    rejects(reentry.test690a0, 'caught same-runtime reentry'); poisoned(reentry);
  }
  {
    for (const key of ['controlWord', 'hoverOffset668', 'tierScale', 'hSpeed', 'slopeMode698', 'byte661', 'mode4a0', 'byte732', 'previousStepHeight6d4']) {
      const x = fixture(); (x.attributeState as Record<string, unknown>)[key] = 0;
      rejects(x.ground, `${key}: competing cue0-lifecycle storage`); equal(x.actual.pos.y, 5, 'shadow rejected before source store');
    }
    for (const key of ['field732', 'field668', 'flags5e0', 'field24', 'savedY30']) {
      const x = fixture(); (x.actual as unknown as Record<string, unknown>)[key] = 0;
      rejects(x.ground, `${key}: competing cue0-lifecycle storage alias`);
    }
    const x = fixture({defer: true}); x.hooks.attribute = () => x.worldState;
    rejects(x.bind, 'source owner alias');
    const y = fixture({defer: true}); y.historyState.rotation76 = y.actual.pos;
    rejects(y.bind, 'source owner alias');
    const z = fixture({defer: true}); Object.defineProperty(z.initial, 'byte732', {get() {throw Error('must not call getter');}});
    rejects(z.bind, 'byte732: own data');
  }
  for (const method of ['cue44', 'test690a0'] as const) {
    for (const key of ['byte588', 'stateFlagA', 'inputEdge5d4', 'statusWord5b4']) {
      const x = fixture(); (x.attributeState as Record<string, unknown>)[key] = 0;
      rejects(x[method], `${key}: competing cue0-lifecycle storage`);
      equal(x.cueBinding().byte588, 8, 'dynamic canonical shadow rejected before588 store');
    }
    for (const key of ['field588', 'flags588', 'command588', 'byte57a', 'field57a', 'flags57a', 'word5d4', 'field5d4', 'flags5b4']) {
      const x = fixture(); (x.actual as unknown as Record<string, unknown>)[key] = 0;
      rejects(x[method], `${key}: competing cue0-lifecycle storage alias`);
      equal(x.cueBinding().byte588, 8, 'dynamic raw alias rejected before588 store');
    }
  }
}
