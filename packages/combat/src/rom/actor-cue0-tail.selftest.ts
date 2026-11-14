import {createRomActor} from './actor.js';
import {createSourceActorInputChargeRuntime, type SourceActorInputChargeSources, type SourceActorInputChargeGlobal, type SourceActorInputChargeData} from './actor-input-charge.js';
import {createSourceActorCueResetRuntime, type SourceActorCueResetBinding} from './actor-cue-reset.js';
import {createSourceActorAttributeRefreshRuntime, type SourceActorAttributeRefreshBinding} from './actor-attribute-refresh.js';
import {createSourceActorCue0TailRuntime, isSourceActorCue0TailRuntime, hasIncompleteSourceActorCue0Tail,
  type SourceActorCue0TailBinding, type SourceActorCue0TailSources} from './actor-cue0-tail.js';
function check(ok: boolean, why: string): void {if (!ok) throw Error(`[actor-cue0-tail-test] ${why}`);}
function equal(actual: unknown, expected: unknown, why: string): void {
  check(Object.is(actual, expected), `${why}: got ${String(actual)}, expected ${String(expected)}`);
}
function rejects(run: () => unknown, fragment: string): void {
  let message = ''; try {run();} catch (error) {message = String(error);}
  check(message.includes(fragment), `expected ${fragment}, got ${message || 'success'}`);
}
function absent(record: object, key: string): void {delete (record as Record<string, unknown>)[key];}
function readonly(record: object, key: string): void {Object.defineProperty(record, key, {writable: false});}
function watchProperties(run: () => void, observe: (owner: object, key: PropertyKey) => void): void {
  const original = Object.getOwnPropertyDescriptor;
  Object.getOwnPropertyDescriptor = ((owner: object, key: PropertyKey) => {
    observe(owner, key); return original(owner, key);
  }) as typeof original;
  try {run();} finally {Object.getOwnPropertyDescriptor = original;}
}
function fixture(options: {defer?: boolean; global?: SourceActorInputChargeGlobal; data?: SourceActorInputChargeData;
  attributes?: boolean;
  proxy?: ProxyHandler<ReturnType<typeof createRomActor>>} = {}) {
  const states = new Map<symbol, ReturnType<typeof makeState>>();
  const hooks: Partial<Record<'worldActor' | 'world' | 'mapping' | 'movementActor' | 'movement' | 'statusActor' |
    'status' | 'borg' | 'statusWorld' | 'statusMapping' | 'statusMovement' | 'attribute' | 'dispatch', () => unknown>> = {};
  const get = (id: symbol) => {const x = states.get(id); if (!x) throw Error('unknown fixture identity'); return x;};
  function makeState(proxy?: ProxyHandler<ReturnType<typeof createRomActor>>) {
    const base = createRomActor(), actual = proxy ? new Proxy(base, proxy) : base;
    absent(actual, 'fbPhaseSlots'); absent(actual, 'shotByte1db3');
    actual.team = 0; actual.controlWord = 3; actual.inputEdge5d4 = 0; actual.statusWord5b4 = 0; actual.inputHeld5d8 = 0;
    actual.cueTable = new Int8Array(128).fill(-1); actual.ubCue = 201; actual.ubState = -12;
    actual.prevUbState = -21; Object.assign(actual, {onLand754: () => {throw Error('must never invoke onLand754');}});
    const id = Symbol('cue0-tail actor'), world = {mode4a0: 0, mode4a1: 0}, movement = {byte661: 0};
    const status = {short736: 0, byte593: 73, byte747: 0}, borg = {burstArmFrames: 4};
    const mapping = {}, attribute: Partial<SourceActorAttributeRefreshBinding> = {};
    const dispatch = {family1d88: Symbol(), shared1d8c: Symbol(), marker578: 1, marker1db3: 1};
    const initial: Partial<SourceActorCue0TailBinding> = {byte57c: 9, byte58f: 10, byte7cd: 0};
    const cueInitial: Partial<SourceActorCueResetBinding> = {byte541: 11, byte542: 12, byte543: 13, byte544: 14,
      byte545: 15, byte546: 16, byte547: 17, byte588: 18, byte7ce: 19, byte7cf: 20};
    return {id, actual, world, movement, status, borg, mapping, attribute, dispatch, initial, cueInitial};
  }
  const worldSource: SourceActorCue0TailSources['world'] = {
    getActualActor(id) {check(this === worldSource, 'world receiver'); return (hooks.worldActor?.() ?? get(id).actual) as ReturnType<typeof createRomActor>;},
    getActorBinding(id) {return (hooks.world?.() ?? get(id).world) as ReturnType<SourceActorCue0TailSources['world']['getActorBinding']>;},
    getMappingActor(id) {return (hooks.mapping?.() ?? get(id).mapping) as object;},
  };
  const movementSource: SourceActorCue0TailSources['movement'] = {
    getActualActor(id) {check(this === movementSource, 'movement receiver'); return (hooks.movementActor?.() ?? get(id).actual) as ReturnType<typeof createRomActor>;},
    getActorBinding(id) {return (hooks.movement?.() ?? get(id).movement) as ReturnType<SourceActorCue0TailSources['movement']['getActorBinding']>;},
  };
  const statusSource = {
    getActualActor(id: symbol) {check(this === statusSource, 'status receiver'); return (hooks.statusActor?.() ?? get(id).actual) as ReturnType<typeof createRomActor>;},
    getActorBinding(id: symbol) {return (hooks.status?.() ?? get(id).status) as ReturnType<SourceActorCue0TailSources['status']['getActorBinding']>;},
    getActualBorg(id: symbol) {return (hooks.borg?.() ?? get(id).borg) as ReturnType<SourceActorCue0TailSources['status']['getActualBorg']>;},
    getWorldBinding(id: symbol) {return (hooks.statusWorld?.() ?? get(id).world) as object;},
    getMappingActor(id: symbol) {return (hooks.statusMapping?.() ?? get(id).mapping) as object;},
    getMovementBinding(id: symbol) {return (hooks.statusMovement?.() ?? get(id).movement) as object;},
    getAttributeBinding(id: symbol) {return (hooks.attribute?.() ?? get(id).attribute) as object;},
  };
  const attributes = options.attributes ? createSourceActorAttributeRefreshRuntime({world: worldSource,
    mapping: {getActor(id) {return get(id).mapping as ReturnType<SourceActorInputChargeSources['mapping']['getActor']>;},
      getDescriptor() {throw Error('integer helpers never load descriptor4b0');}},
    movement: {getActualActor(id) {return movementSource.getActualActor(id);},
      getActorBinding(id) {return movementSource.getActorBinding(id);},
      updateActor() {throw Error('integer helpers never refresh movement');}}}) : undefined;
  const row = {charged: false}, global = options.global ?? {teamRows103: [row]};
  const chargeSources: SourceActorInputChargeSources = {world: worldSource, status: statusSource,
    mapping: {getActor(id) {return get(id).mapping as ReturnType<SourceActorInputChargeSources['mapping']['getActor']>;},
      getDescriptor() {throw Error('tail never loads descriptor4b0');}},
    attributes: {getActualActor(id) {return get(id).actual;},
      getActorBinding(id) {return get(id).attribute as ReturnType<SourceActorInputChargeSources['attributes']['getActorBinding']>;},
      getParameterDescriptor() {throw Error('tail never loads parameter4ac');}}, global, data: options.data ?? {}};
  const charge = createSourceActorInputChargeRuntime(chargeSources);
  const cues = createSourceActorCueResetRuntime({world: worldSource, dispatch: {
    getSourceActor(id) {return get(id).mapping as ReturnType<SourceActorInputChargeSources['mapping']['getActor']>;},
    getActorBinding(id) {return (hooks.dispatch?.() ?? get(id).dispatch) as ReturnType<typeof makeState>['dispatch'];},
  }});
  const sources: SourceActorCue0TailSources = {world: worldSource, movement: movementSource, status: statusSource, charge, cues,
    ...(attributes ? {attributes} : {})};
  const runtime = createSourceActorCue0TailRuntime(sources);
  const add = (defer = false, proxy?: ProxyHandler<ReturnType<typeof createRomActor>>) => {
    const x = makeState(proxy); states.set(x.id, x);
    if (attributes) {
      attributes.bindActor(x.id, {parameter4ac: attributes.createParameterDescriptor({byte9f: 1})});
      x.attribute = attributes.getActorBinding(x.id);
    }
    charge.bindActor(x.id, {byte58e: 42, byte654: 43, byte655: 44});
    cues.bindActor(x.id, x.cueInitial);
    const bind = () => runtime.bindActor(x.id, x.initial); if (!defer) bind();
    return {...x, bind, binding: () => runtime.getActorBinding(x.id), cueBinding: () => cues.getActorBinding(x.id),
      run: () => runtime.updateActor(x.id), burst: () => runtime.test80069814(x.id), gate: () => runtime.test800694c0(x.id),
      move: () => runtime.test800696f4(x.id), clear: () => runtime.test80069038(x.id),
      held: () => runtime.test80069354(x.id), statusCue: () => runtime.test80068f9c(x.id),
      jump: () => runtime.test80069210(x.id), airHeld: () => runtime.test800693fc(x.id),
      movementHeld: () => runtime.test8006965c(x.id), movementStatus: () => runtime.test800695c4(x.id),
      movementFlag: () => runtime.test8006952c(x.id)};
  };
  return {...add(options.defer, options.proxy), add, runtime, sources, worldSource, movementSource, statusSource,
    charge, cues, attributes, global, row, hooks};
}
export function runActorCue0TailSelfTests(): void {
  runControl40IntegerHelperSelfTests();
  {
    const x = fixture();
    check(isSourceActorCue0TailRuntime(x.runtime) && !isSourceActorCue0TailRuntime({...x.runtime}), 'genuine brand');
    check(Object.isFrozen(x.runtime) && Object.isSealed(x.binding()) && x.binding() !== x.initial, 'sealed copied three-cell binding');
    equal(x.runtime.getSourceOwners(x.id).length, 1, 'new binding only');
    equal(x.runtime.getSourceOwners(x.id)[0], x.binding(), 'same new binding');
    equal(x.runtime.getActualActor(x.id), x.actual, 'actual'); equal(x.runtime.getWorldBinding(x.id), x.world, 'world');
    equal(x.runtime.getMovementBinding(x.id), x.movement, 'movement'); equal(x.runtime.getStatusBinding(x.id), x.status, 'status');
    equal(x.runtime.getActualBorg(x.id), x.borg, 'actual Borg'); equal(x.runtime.getMappingActor(x.id), x.mapping, 'mapping');
    equal(x.runtime.getChargeRuntime(), x.charge, 'genuine charge'); equal(x.runtime.getGlobal(), x.global, 'same charge global');
    equal(x.runtime.getCueRuntime(), x.cues, 'genuine cues'); equal(x.runtime.getCueBinding(x.id), x.cueBinding(), 'cue binding');
    equal(x.runtime.getDispatchBinding(x.id), x.dispatch, 'dispatch owner');
    equal(x.runtime.getKnownTeamStorageOwners().length, 0, 'no eager team pointer access');
    equal(x.run(), undefined, 'outer tail is void'); equal(x.runtime.getKnownTeamStorageOwners().length, 2, 'only reached array and selected row');
    equal(x.status.byte593, 73, 'tail leaves593'); equal(x.charge.getActorBinding(x.id).byte58e, 42, 'tail leaves charge flags');
    equal(x.borg.burstArmFrames, 4, 'false charged skips burst'); equal(x.actual.ubCue, 201, 'zero input no cue');
    check(!hasIncompleteSourceActorCue0Tail(x.actual), 'successful call clears marker');
  }
  {
    const x = fixture({global: {}}); equal(x.runtime.getKnownTeamStorageOwners().length, 0, 'missing table not read at bind');
    x.runtime.assertActorComplete(x.id); rejects(x.run, 'teamRows103');
    check(!hasIncompleteSourceActorCue0Tail(x.actual), 'missing table read failure is retryable');
    x.global.teamRows103 = [{charged: false}]; x.run();
    const y = fixture({global: {}}); absent(y.actual, 'team'); rejects(y.run, 'team: own data');
    equal(y.runtime.getKnownTeamStorageOwners().length, 0, 'team load precedes global pointer');
  }
  {
    const x = fixture({defer: true}); delete x.initial.byte57c; delete x.initial.byte58f; delete x.initial.byte7cd; x.bind();
    absent(x.actual, 'inputEdge5d4'); absent(x.actual, 'statusWord5b4'); absent(x.actual, 'inputHeld5d8');
    absent(x.status, 'short736'); absent(x.borg, 'burstArmFrames'); x.run();
    equal(Object.keys(x.binding()).length, 0, 'all unreached new cells stay absent');
  }
  for (const charged of [false, true]) for (const edge of [0, 1, 0x80, 0x200, 0x201, 0xffffffff]) {
    const x = fixture(); x.row.charged = charged; x.actual.inputEdge5d4 = edge;
    equal(x.burst(), 0, '69814 always native0'); equal(x.borg.burstArmFrames, charged && (edge & 0x200) !== 0 ? 6 : 4, 'canonical6fb subset');
  }
  {
    const x = fixture(); x.row.charged = true; x.actual.inputEdge5d4 = 0x200; readonly(x.borg, 'burstArmFrames');
    rejects(x.burst, 'burstArmFrames: non-writable'); check(!hasIncompleteSourceActorCue0Tail(x.actual), 'first failed store has no marker');
    const y = fixture(); y.row.charged = true; y.actual.inputEdge5d4 = 0x200; absent(y.movement, 'byte661');
    rejects(y.run, 'byte661'); equal(y.borg.burstArmFrames, 6, 'first tail store retained on later read failure');
    check(hasIncompleteSourceActorCue0Tail(y.actual), 'burst prefix marker');
    y.row.charged = false; y.actual.controlWord = 0; rejects(y.run, 'known incomplete'); rejects(y.gate, 'known incomplete');
    rejects(() => y.runtime.assertActorComplete(y.id), 'known incomplete');
    rejects(() => createSourceActorCue0TailRuntime(y.sources).bindActor(y.id, {}), 'already claimed');
  }
  {
    const rows = Array.from({length: 128}, () => ({charged: false})); const x = fixture({global: {teamRows103: rows}});
    for (const team of [0, 1, 127]) {x.actual.team = team; equal(x.burst(), 0, 'nonnegative signed team rows');}
    for (const team of [128, 254, 255]) {x.actual.team = team; rejects(x.burst, 'signed team*60+103');}
    for (const bad of [-1, 256, 1.5, NaN, Infinity, '0']) {
      (x.actual as unknown as {team: unknown}).team = bad; rejects(x.burst, 'team: integer');
    }
    const y = fixture(); y.burst(); y.global.teamRows103 = [{charged: false}]; rejects(y.burst, 'table owner changed');
    const z = fixture(); z.burst(); (z.global.teamRows103 as {charged: boolean}[])[0] = {charged: false}; rejects(z.burst, 'row owner changed');
    const a = fixture({global: {teamRows103: new Array(1)}}); rejects(a.burst, '0: own data');
    const b = fixture(); (b.global as unknown as {teamRows103: object}).teamRows103 = {}; rejects(b.burst, 'row-reference array');
    for (const value of [0, 1, 255, 'true', null, undefined]) {
      const c = fixture(); (c.row as unknown as {charged: unknown}).charged = value; rejects(c.burst, 'boolean0/1');
    }
    const d = fixture(); Object.defineProperty(d.row, 'charged', {get() {throw Error('getter executed');}});
    rejects(d.burst, 'charged: own data');
  }
  {
    const x = fixture(); const y = x.add(); x.row.charged = true;
    x.actual.inputEdge5d4 = 0x200; y.actual.inputEdge5d4 = 0x200; x.burst(); y.burst();
    equal(x.borg.burstArmFrames, 6, 'first actor same row'); equal(y.borg.burstArmFrames, 6, 'second actor same row');
    equal(x.runtime.getKnownTeamStorageOwners().length, 2, 'shared row identity retained once');
    const z = fixture({global: x.global}); equal(z.burst(), 0, 'same existing row shared across runtimes');
    (x.global.teamRows103 as {charged: boolean}[]).push(x.row); y.actual.team = 1; y.burst();
    equal(x.runtime.getKnownTeamStorageOwners().length, 2, 'same row may back two explicit team indexes');
  }
  for (let raw = 0; raw < 256; raw++) {
    const x = fixture(); x.binding().byte7cd = raw; x.status.short736 = -1;
    equal(x.gate(), raw === 0 ? 1 : 0, 'all raw7cd signed domains'); x.status.short736 = 1; equal(x.gate(), 1, 'all positive736 gated bytes');
    const y = fixture(); y.movement.byte661 = raw; y.actual.controlWord = 0; y.actual.inputEdge5d4 = 0x80;
    y.actual.cueTable![65] = -7; equal(y.move(), raw === 2 || raw === 5 ? 1 : 0, 'all raw661 signed2/5');
  }
  for (const value of [-32768, -32767, -1, 0, 1, 32766, 32767]) {
    const x = fixture(); x.binding().byte7cd = 255; x.status.short736 = value;
    equal(x.gate(), value > 0 ? 1 : 0, 'signed halfword694c0');
    let reads = 0; watchProperties(() => x.gate(), (owner, key) => {if (owner === x.status && key === 'short736') reads++;});
    equal(reads, 1, 'exactly one lha736');
  }
  {
    const x = fixture(); x.binding().byte7cd = 0; absent(x.status, 'short736'); equal(x.gate(), 1, 'zero7cd skips736');
    const y = fixture(); y.movement.byte661 = 2; absent(y.status, 'short736'); y.binding().byte7cd = 1;
    absent(y.actual, 'controlWord'); rejects(y.move, 'short736');
    y.status.short736 = 1; rejects(y.move, 'controlWord');
    const z = fixture(); z.movement.byte661 = 2; z.binding().byte7cd = 1; z.status.short736 = 0;
    absent(z.actual, 'controlWord'); absent(z.actual, 'inputEdge5d4'); equal(z.move(), 0, '694c0 failure skips control and edge');
  }
  for (const bad of [-32769, 32768, 65535, 0.5, NaN, Infinity, '1']) {
    const x = fixture(); x.binding().byte7cd = 1; (x.status as unknown as {short736: unknown}).short736 = bad;
    rejects(x.gate, 'short736: integer');
  }
  for (let bit = 0; bit < 32; bit++) {
    const mask = (2 ** bit) >>> 0;
    const x = fixture(); x.movement.byte661 = 2; x.actual.controlWord = mask; x.actual.inputEdge5d4 = 0x80; x.actual.cueTable![65] = 2;
    equal(x.move(), bit < 2 ? 0 : 1, '696f4 control low2 mask');
    const y = fixture(); y.movement.byte661 = 5; y.actual.controlWord = 0; y.actual.inputEdge5d4 = mask; y.actual.cueTable![65] = 3;
    equal(y.move(), bit === 7 ? 1 : 0, '696f4 edge80 mask');
    const z = fixture(); z.actual.controlWord = 0; z.actual.inputEdge5d4 = 1; z.actual.statusWord5b4 = mask; z.actual.cueTable![9] = 4;
    equal(z.clear(), bit === 8 ? 1 : 0, '69038 held100 mask');
    const a = fixture(); a.actual.controlWord = 0; a.actual.statusWord5b4 = mask; a.actual.cueTable![3] = 5;
    equal(a.statusCue(), bit >= 16 && bit <= 19 ? 1 : 0, '68f9c f0000 mask');
  }
  // Each control bit independently pins the zero-continues branch polarity.
  for (let bit = 0; bit < 32; bit++) {
    const mask = (2 ** bit) >>> 0;
    const x = fixture(); x.actual.controlWord = mask; x.actual.inputEdge5d4 = 1;
    x.actual.statusWord5b4 = 0x100; x.actual.cueTable![9] = 1;
    equal(x.clear(), bit === 1 ? 0 : 1, '69038 control2 disables only on nonzero');
    const y = fixture(); y.actual.controlWord = mask; y.actual.inputHeld5d8 = 0x10; y.actual.cueTable![25] = 2;
    equal(y.held(), bit === 0 ? 0 : 1, '69354 control1 disables only on nonzero');
    const z = fixture(); z.actual.controlWord = mask; z.actual.statusWord5b4 = 0x10000; z.actual.cueTable![3] = 3;
    equal(z.statusCue(), bit === 1 ? 0 : 1, '68f9c control2 disables only on nonzero');
    const a = fixture(); a.actual.controlWord = 0; a.actual.inputEdge5d4 = mask;
    a.actual.statusWord5b4 = 0x100; a.actual.cueTable![9] = 4;
    equal(a.clear(), bit === 0 ? 1 : 0, '69038 edge1 mask');
  }
  {
    const x = fixture(); x.row.charged = true; x.actual.inputEdge5d4 = 0x200;
    const log: string[] = [], table = x.global.teamRows103!;
    watchProperties(() => x.burst(), (owner, key) => {
      if (owner === x.actual && (key === 'team' || key === 'inputEdge5d4')) log.push(String(key));
      if (owner === x.global && key === 'teamRows103') log.push('global table');
      if (owner === table && key === '0') log.push('selected row');
      if (owner === x.row && key === 'charged') log.push('charged');
      if (owner === x.borg && key === 'burstArmFrames') log.push('6fb destination');
    });
    equal(log.join(','), 'team,global table,selected row,charged,inputEdge5d4,6fb destination', '69814 source data load/store order');
    const y = fixture(); y.movement.byte661 = 2; y.binding().byte7cd = 1; y.status.short736 = 1;
    y.actual.controlWord = 0; y.actual.inputEdge5d4 = 0x80;
    const order: string[] = [];
    watchProperties(() => y.move(), (owner, key) => {
      if (owner === y.movement && key === 'byte661' || owner === y.binding() && key === 'byte7cd' ||
        owner === y.status && key === 'short736' || owner === y.actual && ['controlWord', 'inputEdge5d4', 'cueTable'].includes(String(key)))
        order.push(String(key));
    });
    equal(order.join(','), 'byte661,byte7cd,short736,controlWord,inputEdge5d4,cueTable', '696f4 calls694c0 before control/edge');
  }
  {
    const x = fixture(); x.movement.byte661 = 2; x.actual.controlWord = 0; x.actual.inputEdge5d4 = 0x80;
    let reads = 0; watchProperties(() => equal(x.move(), 0, 'real cue sentinel'), (owner, key) => {
      if (owner === x.movement && key === 'byte661') reads++;
    }); equal(reads, 1, '696f4 single retained661 load'); equal(x.actual.ubCue, 201, 'sentinel preserves state');
    check(!hasIncompleteSourceActorCue0Tail(x.actual), 'successful sentinel clears conservative marker');
    const y = fixture(); y.actual.controlWord = 0; y.actual.inputEdge5d4 = 1; y.actual.statusWord5b4 = 0x100;
    equal(y.clear(), 0, '69038 sentinel0'); equal(y.binding().byte57c, 0, '57c store before sentinel');
    const z = fixture(); z.actual.controlWord = 0; z.actual.inputEdge5d4 = 1; z.actual.statusWord5b4 = 0x100;
    absent(z.actual, 'cueTable'); rejects(z.clear, 'cueTable'); equal(z.binding().byte57c, 0, '57c retained before cue read failure');
    check(hasIncompleteSourceActorCue0Tail(z.actual), '57c prefix permanent');
  }
  for (const movement of [0, 2, 5, 6, 128, 255]) for (const successful of [false, true]) {
    const x = fixture(); x.actual.controlWord = 0; x.actual.inputHeld5d8 = 0xabf5; x.movement.byte661 = movement;
    const selected = movement === 6 ? 37 : 12; x.actual.cueTable![selected * 2 + 1] = successful ? -7 : -1;
    equal(x.held(), successful ? 1 : 0, '69354 exact chosen genuine return');
    equal(x.binding().byte58f, successful ? 15 : 10, '58f from postcue halfword');
    equal(x.actual.inputHeld5d8, successful ? 0xab05 : 0xabf5, 'clear only nibblef0');
    equal(x.actual.ubCue, successful ? selected : 201, 'real upper cue selection');
    equal(x.actual.ubState, successful ? -7 : -12, 'actual signed cue state');
    const y = fixture(); y.actual.controlWord = 0; y.actual.statusWord5b4 = 0x10000; y.movement.byte661 = movement;
    const finalCue = movement === 6 ? 29 : 1; y.actual.cueTable![finalCue * 2 + 1] = successful ? 7 : -1;
    equal(y.statusCue(), successful ? 1 : 0, '68f9c genuine return'); equal(y.actual.ubCue, successful ? finalCue : 201, '68f9c chosen cue');
  }
  for (let bit = 0; bit < 16; bit++) {
    const x = fixture(); x.actual.controlWord = 0; x.actual.inputHeld5d8 = 2 ** bit; x.actual.cueTable![25] = 1;
    equal(x.held(), bit >= 4 && bit <= 7 ? 1 : 0, 'heldf0 mask');
  }
  {
    const x = fixture(); x.actual.controlWord = 0; x.actual.inputHeld5d8 = 0x10; x.actual.cueTable![25] = 2;
    let reads = 0;
    watchProperties(() => equal(x.held(), 1, 'source reload path'), (owner, key) => {
      if (owner !== x.actual || key !== 'inputHeld5d8') return;
      reads++; if (reads === 2) x.actual.inputHeld5d8 = 0xabc0; if (reads === 3) x.actual.inputHeld5d8 = 0xdef7;
    });
    equal(reads, 4, 'three independent halfword loads plus one destination check');
    equal(x.binding().byte58f, 12, '58f uses second load'); equal(x.actual.inputHeld5d8, 0xde07, 'clear uses third load');
    const y = fixture(); y.actual.controlWord = 0; y.actual.inputHeld5d8 = 0x20;
    let sentinelReads = 0; watchProperties(() => y.held(), (owner, key) => {
      if (owner === y.actual && key === 'inputHeld5d8') sentinelReads++;
    }); equal(sentinelReads, 1, 'sentinel0 skips every postcue load');
  }
  for (const destination of ['byte58f', 'inputHeld5d8'] as const) {
    const x = fixture(); x.actual.controlWord = 0; x.actual.inputHeld5d8 = 0xb5; x.actual.cueTable![25] = 3;
    readonly(destination === 'byte58f' ? x.binding() : x.actual, destination);
    rejects(x.held, `${destination}: non-writable`); equal(x.actual.ubCue, 12, 'late refusal preserves genuine cue');
    equal(x.binding().byte58f, destination === 'byte58f' ? 10 : 11, 'late nibble prefix');
    equal(x.actual.inputHeld5d8, 0xb5, 'failed late destination retains held'); check(hasIncompleteSourceActorCue0Tail(x.actual), 'late prefix poison');
  }
  {
    const x = fixture(); x.movement.byte661 = 2; x.actual.controlWord = 0; x.actual.inputEdge5d4 = 0x80;
    x.actual.cueTable![65] = 7; readonly(x.cueBinding(), 'byte546'); rejects(x.move, 'byte546: non-writable');
    equal(x.actual.ubCue, 32, 'genuine partial upper reset retained'); equal(x.cueBinding().byte547, 0, 'preceding genuine phase store');
    equal(x.cueBinding().byte545, 15, 'later genuine phase not cleared'); check(hasIncompleteSourceActorCue0Tail(x.actual), 'genuine partial cue poison');
    const y = fixture(); y.movement.byte661 = 2; y.actual.controlWord = 0; y.actual.inputEdge5d4 = 0x80;
    absent(y.actual, 'cueTable'); rejects(y.move, 'cueTable'); check(hasIncompleteSourceActorCue0Tail(y.actual), 'conservative pre-cue marker');
  }
  for (const first of [32, 4, 12, 1]) {
    const x = fixture(); x.row.charged = true; x.actual.controlWord = 0; x.actual.inputEdge5d4 = 0x281;
    x.actual.statusWord5b4 = 0x10100; x.actual.inputHeld5d8 = 0x30; x.movement.byte661 = 2;
    x.actual.cueTable![first * 2 + 1] = first; x.run(); equal(x.actual.ubCue, first, 'ordered chain reaches first actual success');
    equal(x.borg.burstArmFrames, 6, 'burst0 never short circuits chain');
    equal(x.binding().byte57c, first === 32 ? 9 : 0, '57c only reached after32 failure');
    equal(x.binding().byte58f, first === 12 ? 3 : 10, '58f only after12 success');
    equal(x.actual.inputHeld5d8, first === 12 ? 0 : 0x30, 'only69354 consumes held nibble');
  }
  {
    const x = fixture(); const y = x.add(true); x.burst();
    (x.global.teamRows103 as {charged: boolean}[]).push(y.borg as unknown as {charged: boolean}); y.actual.team = 1; y.bind();
    rejects(y.burst, 'aliases another source owner');
    const z = fixture(); (z.global.teamRows103 as {charged: boolean}[])[0] = z.actual as unknown as {charged: boolean}; rejects(z.burst, 'aliases another source owner');
    const a = fixture(); (a.global as unknown as {teamRows103: object}).teamRows103 = a.mapping;
    rejects(a.burst, 'row-reference array');
  }
  for (const key of ['held3970', 'release397c'] as const) {
    const row = Object.assign([0, 0, 0], {charged: false});
    const x = fixture({data: {[key]: row}, global: {teamRows103: [row]}});
    rejects(x.burst, 'row aliases another source owner');
    check(!hasIncompleteSourceActorCue0Tail(x.actual), 'charge data row alias refuses before source stores');
    const table = [{charged: false}];
    const y = fixture({data: {[key]: table as unknown as readonly number[]}, global: {teamRows103: table}});
    rejects(y.burst, 'table aliases another source owner');
    const z = fixture(); z.burst();
    z.charge.getData()[key] = z.global.teamRows103 as unknown as readonly number[];
    rejects(z.burst, 'known team storage aliases');
  }
  {
    const x = fixture();
    const cueTable = Object.assign(x.actual.cueTable!, {charged: false});
    (x.global.teamRows103 as {charged: boolean}[])[0] = cueTable;
    rejects(x.burst, 'row aliases another source owner');
    check(!hasIncompleteSourceActorCue0Tail(x.actual), 'actual Int8Array cue row alias refuses before stores');
    const y = fixture();
    y.actual.cueTable = y.global.teamRows103 as unknown as Int8Array;
    rejects(y.burst, 'table aliases another source owner');
    const z = fixture(); z.burst(); z.actual.cueTable = z.row as unknown as Int8Array;
    rejects(z.gate, 'known team storage aliases');
    const a = fixture(); a.burst(); const other = a.add(); other.actual.cueTable = a.row as unknown as Int8Array;
    rejects(a.burst, 'known team storage aliases');
  }
  {
    const x = fixture(); let invoked = 0;
    for (const key of ['held3970', 'release397c']) Object.defineProperty(x.charge.getData(), key, {
      get() {invoked++; throw Error('must not invoke unused charge table accessor');}, configurable: true,
    });
    Object.defineProperty(x.actual, 'cueTable', {get() {invoked++; throw Error('must not invoke unused cue table accessor');}, configurable: true});
    x.burst(); x.gate(); equal(invoked, 0, 'alias admission inspects only own data-reference metadata');
    equal(x.runtime.getKnownTeamStorageOwners().length, 2, 'no unrelated pointers enter known team metadata');
  }
  for (const key of ['byte6fb', 'team88', 'field736', 'word5d8', 'byte103']) {
    const x = fixture({defer: true}); (x.actual as unknown as Record<string, unknown>)[key] = 0; rejects(x.bind, 'competing');
  }
  for (const key of ['byte57c', 'byte58f', 'byte7cd', 'burstArmFrames', 'short736']) {
    const x = fixture({defer: true}); (x.world as unknown as Record<string, unknown>)[key] = 0; rejects(x.bind, 'competing');
  }
  for (const hook of ['worldActor', 'world', 'mapping', 'movementActor', 'movement', 'statusActor', 'status', 'borg', 'statusWorld', 'statusMapping', 'statusMovement', 'attribute'] as const) {
    const x = fixture(); x.hooks[hook] = () => ({}); rejects(x.run, 'owner changed');
    check(!hasIncompleteSourceActorCue0Tail(x.actual), 'metadata mismatch before effects stays retryable');
  }
  {
    const x = fixture(); x.worldSource.getActualActor = () => {throw Error('replacement must not run');}; x.run();
    const y = fixture(); y.hooks.movement = () => Promise.resolve(y.movement); rejects(y.run, 'owner changed');
    const d = fixture(); d.actual.controlWord = 0; d.actual.statusWord5b4 = 0x10000;
    d.hooks.dispatch = () => ({}); rejects(d.statusCue, 'owner changed');
    const z = fixture(); rejects(() => createSourceActorCue0TailRuntime({...z.sources, charge: {...z.charge}}), 'genuine');
    rejects(() => createSourceActorCue0TailRuntime({...z.sources, cues: {...z.cues}}), 'genuine');
  }
  {
    const x = fixture(); let caught = false;
    x.hooks.movementActor = () => {try {x.run();} catch {caught = true;} return x.actual;};
    rejects(x.run, 'caught same-runtime reentry'); check(caught, 'caught callback reentry');
    check(!hasIncompleteSourceActorCue0Tail(x.actual), 'metadata reentry before stores is retryable');
    delete x.hooks.movementActor; x.run();
    let active = false, reenter: (() => void) | undefined;
    const y = fixture({proxy: {set(target, key, value, receiver) {
      const result = Reflect.set(target, key, value, receiver);
      if (active && key === 'inputHeld5d8') {try {reenter!();} catch { /* deliberate adversary */ }} return result;
    }}});
    y.actual.controlWord = 0; y.actual.inputHeld5d8 = 0x70; y.actual.cueTable![25] = 2; reenter = y.run; active = true;
    rejects(y.held, 'caught same-runtime reentry'); equal(y.actual.inputHeld5d8, 0, 'successful store occurs before reentry check');
    check(hasIncompleteSourceActorCue0Tail(y.actual), 'post-store caught reentry marker retained'); active = false;
    rejects(y.run, 'known incomplete');
  }
  for (const key of ['controlWord', 'inputEdge5d4', 'statusWord5b4'] as const) for (const bad of [-1, 0x100000000, 1.5, NaN, Infinity, '1']) {
    const x = fixture(); x.actual.controlWord = 0; x.actual.inputEdge5d4 = 1; x.actual.statusWord5b4 = 0x100;
    (x.actual as unknown as Record<string, unknown>)[key] = bad; rejects(x.clear, `${key}: integer`);
  }
  for (const bad of [-1, 0x10000, 1.5, NaN, Infinity, '1']) {
    const x = fixture(); x.actual.controlWord = 0; (x.actual as unknown as {inputHeld5d8: unknown}).inputHeld5d8 = bad;
    rejects(x.held, 'inputHeld5d8: integer');
  }
  for (const bad of [-1, 256, 1.5, NaN, Infinity, '1']) {
    const x = fixture(); (x.binding() as Record<string, unknown>).byte7cd = bad; rejects(x.gate, 'byte7cd: integer');
    const y = fixture(); (y.movement as unknown as {byte661: unknown}).byte661 = bad; rejects(y.move, 'byte661: integer');
  }
  for (const key of ['byte57c', 'byte58f', 'byte7cd'] as const) for (const bad of [-1, 256, 1.5, NaN, Infinity, '1']) {
    const x = fixture({defer: true}); (x.initial as Record<string, unknown>)[key] = bad; rejects(x.bind, `${key}: integer`);
  }
}

/** Instruction-authenticated helper schedules, synthetic explicit scalar/table
 * values, genuine694c0 and genuine6a750 throughout. No fake helper returns. */
function runControl40IntegerHelperSelfTests(): void {
  const activeJump = (attributes = false) => {
    const x = fixture({attributes}); x.actual.controlWord = 0; x.actual.inputEdge5d4 = 2;
    x.binding().byte7cd = attributes ? 0 : 2; x.actual.cueTable![17] = -7; return x;
  };
  const activeHeld = (movement: boolean) => {
    const x = fixture(); x.movement.byte661 = movement ? 2 : 0; x.actual.controlWord = 0;
    x.actual.inputHeld5d8 = 0xabf5; x.actual.cueTable![(movement ? 22 : 15) * 2 + 1] = -7;
    return {...x, selected: movement ? 22 : 15, invoke: movement ? x.movementHeld : x.airHeld};
  };
  {
    const x = fixture(); absent(x.actual, 'inputEdge5d4'); absent(x.status, 'byte747');
    absent(x.status, 'short736'); equal(x.jump(), 0, '69210 control2 skips all later fields and absent resolver');
    x.actual.controlWord = 0; rejects(x.jump, 'inputEdge5d4');
    x.actual.inputEdge5d4 = 0; equal(x.jump(), 0, '69210 edge2 skips588 and beyond');
    x.actual.inputEdge5d4 = 2; x.cueBinding().byte588 = 0; equal(x.jump(), 0, '69210 signed588zero skips7cd');
    x.cueBinding().byte588 = 1; rejects(x.jump, 'parameter4ac');
    x.attribute.parameter4ac = Symbol('missing resolver'); rejects(x.jump, 'byte747');
    x.status.byte747 = 0; rejects(x.jump, 'active4ac+9f requires genuine attribute');
    check(!hasIncompleteSourceActorCue0Tail(x.actual), 'unresolved9f read has no effects');
    const y = fixture({defer: true}); delete y.initial.byte7cd; y.bind();
    y.actual.controlWord = 0; y.actual.inputEdge5d4 = 2; y.cueBinding().byte588 = 0;
    equal(y.jump(), 0, '588zero does not demand7cd'); y.cueBinding().byte588 = 255; rejects(y.jump, 'byte7cd: own data');
  }
  for (let bit = 0; bit < 32; bit++) {
    const mask = (2 ** bit) >>> 0;
    const x = activeJump(); x.actual.controlWord = mask;
    equal(x.jump(), bit === 1 ? 0 : 1, '69210 control mask2');
    const y = activeJump(); y.actual.inputEdge5d4 = mask;
    equal(y.jump(), bit === 1 ? 1 : 0, '69210 edge mask2');
    for (const movement of [false, true]) {
      const z = activeHeld(movement); z.actual.controlWord = mask;
      equal(z.invoke(), bit === (movement ? 1 : 0) ? 0 : 1, 'held helper exact control mask');
    }
    for (const flag of [false, true]) {
      const z = fixture(); z.actual.controlWord = 0; z.movement.byte661 = 2; z.actual.statusWord5b4 = mask;
      const selected = flag ? 18 : 19; z.actual.cueTable![selected * 2 + 1] = 3;
      equal((flag ? z.movementFlag : z.movementStatus)(), flag ? (bit === 8 ? 1 : 0) : (bit >= 16 && bit <= 19 ? 1 : 0),
        '6952c/695c4 distinct status masks');
      const c = fixture(); c.actual.controlWord = mask; c.movement.byte661 = 2; c.actual.statusWord5b4 = 0xf0100;
      c.actual.cueTable![selected * 2 + 1] = 3;
      equal((flag ? c.movementFlag : c.movementStatus)(), bit === 1 ? 0 : 1, 'status helper exact control2 mask');
    }
  }
  for (let raw = 0; raw < 256; raw++) {
    const x = activeJump(raw === 0); x.binding().byte7cd = raw;
    if (raw === 1) x.status.short736 = 1; else absent(x.status, 'short736');
    equal(x.jump(), 1, 'all raw7cd branches use exact zero/one semantics');
    equal(x.actual.ubCue, 8, '69210 genuine upper8'); equal(x.actual.ubState, -7, '69210 real selected state');
    const y = activeJump(); y.cueBinding().byte588 = raw;
    equal(y.jump(), raw === 0 ? 0 : 1, 'all raw588 sign extensions retain nonzero');
    const a = activeHeld(false); a.movement.byte661 = raw;
    equal(a.invoke(), raw === 2 || raw === 5 ? 0 : 1, '693fc all raw661 excludes signed2/5 only');
    const b = activeHeld(true); b.movement.byte661 = raw;
    equal(b.invoke(), raw === 2 ? 1 : 0, '6965c all raw unsigned661');
    const c = fixture(); c.actual.controlWord = 0; c.movement.byte661 = raw; c.actual.statusWord5b4 = 0xf0100;
    c.actual.cueTable![39] = 1; c.actual.cueTable![37] = 2;
    equal(c.movementStatus(), raw === 2 ? 1 : 0, '695c4 all unsigned661');
    equal(c.movementFlag(), raw === 2 ? 1 : 0, '6952c all unsigned661');
  }
  for (const raw747 of [0, 1, 126, 127, 128, 129, 254, 255]) for (const limit of [0, 1, 126, 127, 128, 254, 255]) {
    const x = activeJump(true); x.status.byte747 = raw747;
    x.attributes!.getParameterDescriptor(x.attribute.parameter4ac!).byte9f = limit;
    equal(x.jump(), (raw747 << 24 >> 24) < limit ? 1 : 0, 'signed747 strictly less than unsigned9f');
  }
  for (const short736 of [-32768, -1, 0, 1, 32767]) {
    const x = activeJump(); x.binding().byte7cd = 1; x.status.short736 = short736;
    equal(x.jump(), short736 > 0 ? 1 : 0, '69210 signed736>0 only for retained7cd==1');
    const y = activeHeld(false); y.binding().byte7cd = 255; y.status.short736 = short736;
    equal(y.invoke(), short736 > 0 ? 1 : 0, '693fc reuses real694c0 signed736');
  }
  {
    const x = activeJump(true), first = x.attribute.parameter4ac!;
    const second = x.attributes!.createParameterDescriptor({byte9f: 0});
    const parameter = x.attributes!.getParameterDescriptor(first), order: string[] = [];
    x.actual.cueTable![17] = -1;
    watchProperties(() => equal(x.jump(), 0, '69210 sentinel after retained pointer threshold passes'), (owner, key) => {
      if (owner === x.actual && ['controlWord', 'inputEdge5d4'].includes(String(key)) ||
        owner === x.cueBinding() && key === 'byte588' || owner === x.binding() && key === 'byte7cd' ||
        owner === x.attribute && key === 'parameter4ac' || owner === x.status && key === 'byte747' ||
        owner === parameter && key === 'byte9f') order.push(String(key));
      if (owner === x.status && key === 'byte747') x.attribute.parameter4ac = second;
    });
    equal(order.join(','), 'controlWord,inputEdge5d4,byte588,byte7cd,parameter4ac,byte747,byte9f', '69210 authenticated source read order');
    equal(x.attribute.parameter4ac, second, '747 mutation was applied');
    // A captured limit0 would reject, but the captured first descriptor1 reaches actual cueTable.
    let calls = 0; x.attribute.parameter4ac = first;
    watchProperties(() => rejects(x.jump, 'cueTable: own data'), (owner, key) => {
      if (owner === x.status && key === 'byte747') {x.attribute.parameter4ac = second; absent(x.actual, 'cueTable');}
      if (owner === parameter && key === 'byte9f') calls++;
    });
    equal(calls, 1, 'captured descriptor read once');
  }
  {
    const x = activeJump(); x.binding().byte7cd = 1; x.status.short736 = 1; let reads = 0;
    watchProperties(() => equal(x.jump(), 1, '7cd retained across736 mutation'), (owner, key) => {
      if (owner === x.binding() && key === 'byte7cd') reads++;
      if (owner === x.status && key === 'short736') x.binding().byte7cd = 0;
    }); equal(reads, 1, '69210 reads7cd once');
    const y = activeHeld(false); const order: string[] = []; y.binding().byte7cd = 1; y.status.short736 = 1;
    y.actual.controlWord = 1;
    watchProperties(() => equal(y.invoke(), 0, '693fc late control1 refusal'), (owner, key) => {
      if (owner === y.movement && key === 'byte661' || owner === y.binding() && key === 'byte7cd' ||
        owner === y.status && key === 'short736' || owner === y.actual && key === 'controlWord') order.push(String(key));
    }); equal(order.join(','), 'byte661,byte7cd,short736,controlWord', '693fc real694c0 before control1');
    const z = activeHeld(false); let movementReads = 0;
    watchProperties(() => equal(z.invoke(), 1, '693fc retains661 before694c0'), (owner, key) => {
      if (owner === z.movement && key === 'byte661') movementReads++;
      if (owner === z.binding() && key === 'byte7cd') z.movement.byte661 = 5;
    }); equal(movementReads, 1, '693fc retained661 read once');
    const a = activeHeld(false); a.binding().byte7cd = 1; a.status.short736 = 0;
    absent(a.actual, 'controlWord'); absent(a.actual, 'inputHeld5d8'); equal(a.invoke(), 0, 'failed694c0 skips later reads');
    const b = activeHeld(false); b.binding().byte7cd = 1; absent(b.status, 'short736'); b.actual.controlWord = 1;
    rejects(b.invoke, 'short736');
  }
  for (const method of ['airHeld', 'movementHeld', 'movementStatus', 'movementFlag'] as const) {
    const x = fixture(); x.movement.byte661 = method === 'airHeld' ? 2 : 0;
    absent(x.actual, 'controlWord'); absent(x.actual, 'inputHeld5d8'); absent(x.actual, 'statusWord5b4');
    absent(x.status, 'short736'); x.binding().byte7cd = 1;
    equal(x[method](), 0, '661 rejects lazily before all helper-specific operands');
    const y = fixture(); y.movement.byte661 = method === 'airHeld' ? 0 : 2; y.actual.controlWord = 3;
    absent(y.actual, 'inputHeld5d8'); absent(y.actual, 'statusWord5b4'); equal(y[method](), 0, 'control gate skips later source fields');
    const z = fixture(); z.movement.byte661 = method === 'airHeld' ? 0 : 2; z.actual.controlWord = 0;
    absent(z.actual, 'cueTable'); equal(z[method](), 0, 'held/status zero skips realcue access');
    const a = fixture(); a.movement.byte661 = method === 'airHeld' ? 0 : 2; a.actual.controlWord = 0;
    a.actual.inputHeld5d8 = 0x10; a.actual.statusWord5b4 = 0xf0100;
    const order: string[] = [];
    watchProperties(() => equal(a[method](), 0, 'ordered real sentinel'), (owner, key) => {
      if (owner === a.movement && key === 'byte661' || owner === a.binding() && key === 'byte7cd' ||
        owner === a.actual && ['controlWord', 'inputHeld5d8', 'statusWord5b4', 'cueTable'].includes(String(key))) order.push(String(key));
    });
    equal(order.join(','), method === 'airHeld' ? 'byte661,byte7cd,controlWord,inputHeld5d8,cueTable' :
      method === 'movementHeld' ? 'byte661,controlWord,inputHeld5d8,cueTable' : 'byte661,controlWord,statusWord5b4,cueTable',
      'complete source gate order before genuine sentinel');
  }
  for (const movement of [false, true]) {
    for (let bit = 0; bit < 16; bit++) {
      const x = activeHeld(movement); x.actual.inputHeld5d8 = 2 ** bit;
      equal(x.invoke(), bit >= 4 && bit <= 7 ? 1 : 0, 'held gate masks only bits4..7');
    }
    const x = activeHeld(movement), order: string[] = []; let reads = 0;
    watchProperties(() => equal(x.invoke(), 1, 'native nonzero cue consumes freshheld'), (owner, key) => {
      if (owner === x.actual && key === 'inputHeld5d8') {
        order.push('held'); reads++; if (reads === 2) x.actual.inputHeld5d8 = 0xabc0;
        if (reads === 3) x.actual.inputHeld5d8 = 0xdef7;
      }
      if (owner === x.binding() && key === 'byte58f') order.push('58f store');
      if (owner === x.actual && key === 'ubCue') order.push('cue');
    });
    equal(reads, 4, 'three separate held loads and final store check');
    equal(x.binding().byte58f, 12, '58f comes from postcue second read');
    equal(x.actual.inputHeld5d8, 0xde07, 'held clear comes from third read after58f');
    check(order.indexOf('cue') > order.indexOf('held') && order.indexOf('58f store') > order.lastIndexOf('cue'), 'realcue before58f store');
    equal(order.slice(-4).join(','), 'held,58f store,held,held', 'postcue exact ordered reads and stores');
    const y = activeHeld(movement); y.actual.cueTable![y.selected * 2 + 1] = -1; let sentinelReads = 0;
    watchProperties(() => equal(y.invoke(), 0, 'genuine sentinel0'), (owner, key) => {
      if (owner === y.actual && key === 'inputHeld5d8') sentinelReads++;
    }); equal(sentinelReads, 1, 'sentinel skips all postcue loads and stores');
    equal(y.binding().byte58f, 10, 'sentinel retains58f'); equal(y.actual.inputHeld5d8, 0xabf5, 'sentinel retainsheld');
    for (const destination of ['byte58f', 'inputHeld5d8'] as const) {
      const z = activeHeld(movement); readonly(destination === 'byte58f' ? z.binding() : z.actual, destination);
      rejects(z.invoke, `${destination}: non-writable`); equal(z.actual.ubCue, z.selected, 'late failure retains actualcue');
      equal(z.binding().byte58f, destination === 'byte58f' ? 10 : 15, 'earlier58f prefix retained');
      equal(z.actual.inputHeld5d8, 0xabf5, 'failed store does not clearheld');
      check(hasIncompleteSourceActorCue0Tail(z.actual), 'effectful prefix blocks replay');
      rejects(z.invoke, 'known incomplete'); rejects(z.jump, 'known incomplete');
    }
  }
  for (const method of ['jump', 'airHeld', 'movementHeld', 'movementStatus', 'movementFlag'] as const) {
    const selected = {jump: 8, airHeld: 15, movementHeld: 22, movementStatus: 19, movementFlag: 18}[method];
    for (const success of [false, true]) {
      const x = activeJump(); x.movement.byte661 = method === 'airHeld' ? 0 : 2;
      x.status.short736 = 1; x.actual.inputHeld5d8 = 0x20; x.actual.statusWord5b4 = 0xf0100;
      x.actual.cueTable![selected * 2 + 1] = success ? -128 : -1;
      equal(x[method](), success ? 1 : 0, 'all helpers return realcue sentinel/success');
      equal(x.actual.ubCue, success ? selected : 201, 'exact genuineupper cue requested');
      equal(x.actual.ubState, success ? -128 : -12, 'actual source-selected state applied');
      check(!hasIncompleteSourceActorCue0Tail(x.actual), 'completed native outcome not incomplete');
    }
    const x = activeJump(); x.movement.byte661 = method === 'airHeld' ? 0 : 2;
    x.status.short736 = 1; x.actual.inputHeld5d8 = 0x20; x.actual.statusWord5b4 = 0xf0100; x.actual.cueTable![selected * 2 + 1] = 2;
    readonly(x.cueBinding(), 'byte546'); rejects(x[method], 'byte546: non-writable');
    equal(x.actual.ubCue, selected, 'real partialcue prefix preserved'); equal(x.cueBinding().byte547, 0, 'phase547 before failed546');
    check(hasIncompleteSourceActorCue0Tail(x.actual), 'partial realcue permanently poisons tail'); rejects(x[method], 'known incomplete');
  }
  {
    const x = activeJump(true); x.attribute.parameter4ac = x.attributes!.createParameterDescriptor({});
    Object.assign(x.actual, {descriptor: {handlerData9f: 255}}); rejects(x.jump, 'byte9f: own data');
    for (const invalid of [null, undefined, 1, {}, Promise.resolve(Symbol())]) {
      const y = activeJump(true); (y.attribute as Record<string, unknown>).parameter4ac = invalid;
      absent(y.status, 'byte747'); rejects(y.jump, 'byte747: own data');
      y.status.byte747 = 0; rejects(y.jump, 'non-null decoded symbol');
    }
    const y = activeJump(true); y.attribute.parameter4ac = Symbol('foreign'); rejects(y.jump, 'explicitly owned parameter descriptor');
    const z = fixture(); rejects(() => createSourceActorCue0TailRuntime({...z.sources, attributes: {} as never}), 'genuine source runtime');
    const a = fixture({attributes: true}); rejects(() => createSourceActorCue0TailRuntime({...a.sources, attributes: {...a.attributes!}}), 'genuine source runtime');
    const b = fixture({attributes: true, defer: true}); b.hooks.attribute = () => ({}); rejects(b.bind, 'owner changed');
    const c = activeJump(true), other = fixture({attributes: true}); c.sources.attributes = other.attributes!;
    equal(c.jump(), 1, 'captured genuine attribute runtime cannot be replaced through sources');
    const d = fixture({attributes: true}), parameter = d.attributes!.getParameterDescriptor(d.attribute.parameter4ac!);
    d.global.teamRows103 = [parameter as unknown as {charged: boolean}];
    rejects(d.burst, 'row aliases another source owner');
    const e = fixture({attributes: true}); e.actual.cueTable = e.attributes!.getParameterDescriptor(e.attribute.parameter4ac!) as unknown as Int8Array;
    rejects(e.jump, 'parameter descriptor aliases another source owner');
  }
  for (const key of ['byte588', 'byte747', 'parameter4ac', 'byte9f', 'field4ac', 'field747', 'field588']) {
    const x = fixture({defer: true}); (x.world as unknown as Record<string, unknown>)[key] = 0; rejects(x.bind, 'competing');
    const y = fixture({attributes: true}); (y.actual as unknown as Record<string, unknown>)[key] = 0; rejects(y.jump, 'competing');
  }
  for (const key of ['byte588', 'byte747', 'byte9f'] as const) for (const bad of [-1, 256, 1.5, NaN, Infinity, '1']) {
    const x = activeJump(true), parameter = x.attributes!.getParameterDescriptor(x.attribute.parameter4ac!);
    const owner = key === 'byte588' ? x.cueBinding() : key === 'byte747' ? x.status : parameter;
    (owner as Record<string, unknown>)[key] = bad; rejects(x.jump, `${key}: integer`);
  }
  for (const movement of [false, true]) {
    let active = false, reenter: (() => unknown) | undefined;
    const x = fixture({proxy: {set(target, key, value, receiver) {
      const result = Reflect.set(target, key, value, receiver);
      if (active && key === 'inputHeld5d8') {try {reenter!();} catch { /* caught adversary */ }} return result;
    }}});
    x.movement.byte661 = movement ? 2 : 0; x.actual.controlWord = 0; x.actual.inputHeld5d8 = 0x70;
    x.actual.cueTable![(movement ? 22 : 15) * 2 + 1] = 2;
    reenter = movement ? x.movementHeld : x.airHeld; active = true;
    rejects(reenter, 'caught same-runtime reentry'); equal(x.actual.inputHeld5d8, 0, 'held store precedes caught reentry');
    equal(x.binding().byte58f, 7, '58f prefix retained on reentry'); check(hasIncompleteSourceActorCue0Tail(x.actual), 'reentry blocks retry');
  }
}
