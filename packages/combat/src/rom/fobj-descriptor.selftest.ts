import {createSourceFObjRuntime, type SourceFObjHeader, type SourceFObjRuntime} from './fobj-list.js';
import {createSourceFObjDescriptorRuntime, type SourceFObjDescriptor} from './fobj-descriptor.js';

function check(ok: boolean, message: string): void {
  if (!ok) throw Error(`[fobj-descriptor-test] ${message}`);
}
function rejects(run: () => unknown, text: string): void {
  let diagnostic = '';
  try { run(); } catch (error) { diagnostic = String(error); }
  check(diagnostic.includes(text), `expected ${text}, got ${diagnostic || 'success'}`);
}
function descriptor(overrides: Partial<SourceFObjDescriptor> = {}): SourceFObjDescriptor {
  return {next00: null, length04: 23, start08: -7, track0c: 9,
    format0d: 0x20, format0e: 0x40, data10: null, ...overrides};
}
const targetKeys = ['next00', 'offset18', 'track13', 'format14', 'format15', 'base08', 'length0c', 'flags10'] as const;
const sourceKeys = ['next00', 'start08', 'track0c', 'format0d', 'format0e', 'data10', 'length04'] as const;
const headerKeys: (keyof SourceFObjHeader)[] = ['next00', 'cursor04', 'base08', 'length0c', 'flags10',
  'byte11', 'byte12', 'track13', 'format14', 'format15', 'half16', 'offset18', 'half1a',
  'frame1c', 'value20', 'value24', 'value28', 'value2c'];
function isZero(node: SourceFObjHeader): boolean {
  return headerKeys.every(key => Object.is(node[key], ['next00', 'cursor04', 'base08'].includes(key) ? null : 0));
}
function sameHeader(actual: SourceFObjHeader, expected: SourceFObjHeader, where: string): void {
  check(headerKeys.every(key => Object.is(actual[key], expected[key])), where);
}
function expectedStores(input: SourceFObjDescriptor, next: symbol | null): Pick<SourceFObjHeader, typeof targetKeys[number]> {
  return {next00: next, offset18: input.start08 === 0 ? 0 : input.start08, track13: input.track0c,
    format14: input.format0d, format15: input.format0e, base08: input.data10,
    length0c: input.length04, flags10: 0};
}
function checkLoaded(node: SourceFObjHeader, input: SourceFObjDescriptor, next: symbol | null, where: string): void {
  const expected = expectedStores(input, next);
  check(targetKeys.every(key => Object.is(node[key], expected[key])), where);
  check(node.cursor04 === null, `${where}: loader must not request cursor`);
}
function poisonTargets(node: SourceFObjHeader): void {
  // Deliberately invalid OLD target values: each is overwritten without a read.
  const fields = node as unknown as Record<string, unknown>;
  for (const key of targetKeys) fields[key] = key === 'next00' || key === 'base08' ? 123 : NaN;
}
function checkPrefix(node: SourceFObjHeader, before: SourceFObjHeader,
  input: SourceFObjDescriptor, next: symbol | null, stores: number, where: string): void {
  const expected = {...before}, values = expectedStores(input, next);
  for (let i = 0; i < stores; i++) {
    const key = targetKeys[i]!;
    (expected as unknown as Record<string, unknown>)[key] = values[key];
  }
  sameHeader(node, expected, where);
}
function fixture(maxNodes = 4096) {
  const real = createSourceFObjRuntime(() => { throw Error('loader must not invoke interpreter'); });
  const allocated: symbol[] = [], allocationInputs: SourceFObjHeader[] = [], resolved: symbol[] = [];
  const hooks: {allocate?: (id: symbol, index: number) => void; resolve?: (id: symbol) => void} = {};
  const methods: Pick<SourceFObjRuntime, 'createNode' | 'getNode'> = {
    createNode(initial) {
      check(this === methods, 'captured allocator retains original this');
      allocationInputs.push({...initial});
      const id = real.createNode(initial);
      allocated.push(id);
      check(isZero(real.getNode(id)), 'actual runtime allocation starts with every modeled field zero/null');
      hooks.allocate?.(id, allocated.length - 1);
      return id;
    },
    getNode(id) {
      check(this === methods, 'captured resolver retains original this');
      resolved.push(id);
      hooks.resolve?.(id);
      return real.getNode(id);
    },
  };
  const loader = createSourceFObjDescriptorRuntime(methods, maxNodes);
  return {real, methods, loader, allocated, allocationInputs, resolved, hooks};
}

export function runFObjDescriptorSelfTest(): void {
  {
    const f = fixture();
    check(f.loader.loadDescriptors(null) === null && f.allocated.length === 0 && f.resolved.length === 0,
      'null head allocates, resolves and validates nothing');
    check(Object.isFrozen(f.loader), 'public method table is frozen');
    rejects(() => { f.loader.loadDescriptors = () => null; }, 'read only');
    const input = descriptor({data10: Symbol('opaque unregistered stream'), length04: 0xffffffff});
    const id = f.loader.createDescriptor(input), owned = f.loader.getDescriptor(id);
    check(Object.isSealed(owned) && owned !== input && f.loader.getDescriptor(id) === owned,
      'descriptor factory copies into stable separately owned sealed record');
    input.start08 = 123; input.data10 = null; input.next00 = Symbol('changed input');
    check(owned.start08 === -7 && owned.data10 !== null && owned.next00 === null, 'input aliases are not retained');
    const loaded = f.loader.loadDescriptors(id)!;
    check(loaded === f.allocated[0] && f.real.getNode(loaded) !== (owned as unknown),
      'returned node is the actual existing runtime allocation, not an event-only result or descriptor alias');
    checkLoaded(f.real.getNode(loaded), owned, null, 'single load copies opaque base and full u32 length without decoding');
    check(f.allocationInputs.every(isZero), 'allocator receives all-zero modeled 0x30-byte state');
    owned.track0c = 70;
    check(f.real.getNode(loaded).track13 === 9, 'post-load descriptor mutation does not alias the header');
    const second = f.loader.loadDescriptors(id)!;
    check(second !== loaded && f.real.getNode(second).track13 === 70, 'reload makes independent actual allocation');
  }
  {
    const f = fixture(), inputs: SourceFObjDescriptor[] = [], ids: symbol[] = [];
    for (let i = 5; i >= 0; i--) {
      inputs[i] = descriptor({next00: ids[i + 1] ?? null, start08: i + 1,
        track0c: i + 10, data10: Symbol(`opaque ${i}`)});
      ids[i] = f.loader.createDescriptor(inputs[i]!);
    }
    f.hooks.allocate = (_id, index) => {
      check(f.allocated.length === index + 1 && f.allocated.every(id => isZero(f.real.getNode(id))),
        'all forward allocations precede any initialization');
    };
    f.hooks.resolve = id => {
      const index = f.allocated.indexOf(id);
      check(index === 6 - f.resolved.length, 'initialization resolves tail-to-head');
      for (let j = 0; j < 6; j++) {
        const node = f.real.getNode(f.allocated[j]!);
        if (j <= index) check(isZero(node), 'uninitialized prefix remains all zero');
        else checkLoaded(node, inputs[j]!, f.allocated[j + 1] ?? null, 'already initialized tail');
      }
    };
    const head = f.loader.loadDescriptors(ids[0]!)!;
    check(head === f.allocated[0] && f.allocated.length === 6, 'five unrolled allocations do not truncate six-node list');
    for (let i = 0; i < 6; i++) checkLoaded(f.real.getNode(f.allocated[i]!), inputs[i]!, f.allocated[i + 1] ?? null,
      'allocation order corresponds to descriptor order');
    check(f.resolved.every((id, index) => id === f.allocated[5 - index]), 'reverse initialization identity sequence');
  }
  {
    const count = 12000, f = fixture(count);
    let head: symbol | null = null;
    for (let i = count - 1; i >= 0; i--) head = f.loader.createDescriptor(descriptor({next00: head, start08: i}));
    let node = f.loader.loadDescriptors(head), visited = 0;
    while (node !== null) {
      check(visited < count, 'bounded deep-result inspection never hangs on a bad link');
      const header = f.real.getNode(node);
      check(header.offset18 === visited && node === f.allocated[visited], 'deep list retains descriptor and allocation order');
      node = header.next00; visited++;
    }
    check(visited === count && f.allocated.length === count, 'deep list uses an iterative stack, not source unroll limit or JS recursion');
  }
  {
    for (const start of [-32768, -1, -0, 0, 1, 32767]) {
      const f = fixture(), id = f.loader.createDescriptor(descriptor({start08: start}));
      const head = f.loader.loadDescriptors(id)!;
      check(Object.is(f.real.getNode(head).offset18, start === 0 ? 0 : start), 'signed16 edges and negative-zero canonicalization');
    }
    // A descriptor can hold any finite binary32. Only its load conversion is bounded.
    for (const start of [-32769, 32768, -0.5, 0.5, 2 ** -149, 2 ** 100]) {
      const f = fixture(), id = f.loader.createDescriptor(descriptor({start08: start}));
      f.hooks.allocate = node => { poisonTargets(f.real.getNode(node)); };
      rejects(() => f.loader.loadDescriptors(id), 'integral signed16');
      const node = f.real.getNode(f.allocated[0]!);
      check(node.next00 === null && Number.isNaN(node.offset18) && Number.isNaN(node.track13),
        'unsupported f32 conversion refuses after next store and before offset/store suffix');
    }
    for (const start of [NaN, Infinity, -Infinity, 0.1, 1 + 2 ** -25]) {
      const f = fixture();
      rejects(() => f.loader.createDescriptor(descriptor({start08: start})), 'float32');
      const id = f.loader.createDescriptor(descriptor());
      f.loader.getDescriptor(id).start08 = start;
      rejects(() => f.loader.loadDescriptors(id), 'float32');
      check(f.allocated.length === 1 && f.resolved.length === 1 && isZero(f.real.getNode(f.allocated[0]!)),
        'mutated exceptional/non-f32 offset refuses at offset boundary without rounding');
    }
  }
  {
    // These mutations and allocator hooks are synthetic host ordering/failure
    // probes, not claims about source allocator callbacks or memory faults.
    const cases: {key: keyof SourceFObjDescriptor; value: unknown; text: string; stores: number}[] = [
      {key: 'start08', value: 0.5, text: 'integral signed16', stores: 1},
      {key: 'start08', value: NaN, text: 'float32', stores: 1},
      {key: 'track0c', value: 256, text: 'track0c', stores: 2},
      {key: 'format0d', value: -1, text: 'format0d', stores: 3},
      {key: 'format0e', value: 1.5, text: 'format0e', stores: 4},
      {key: 'data10', value: 0x80400000, text: 'data10', stores: 5},
      {key: 'length04', value: 0x100000000, text: 'length04', stores: 6},
      {key: 'length04', value: -1, text: 'length04', stores: 6},
    ];
    for (const probe of cases) {
      const f = fixture(), tailInput = descriptor({start08: 31}), tail = f.loader.createDescriptor(tailInput);
      const input = descriptor({next00: tail, data10: Symbol('valid base')}), middle = f.loader.createDescriptor(input);
      const head = f.loader.createDescriptor(descriptor({next00: middle}));
      (f.loader.getDescriptor(middle) as unknown as Record<string, unknown>)[probe.key] = probe.value;
      let before!: SourceFObjHeader;
      f.hooks.allocate = (id, index) => { if (index === 1) { poisonTargets(f.real.getNode(id)); before = {...f.real.getNode(id)}; } };
      rejects(() => f.loader.loadDescriptors(head), probe.text);
      check(f.allocated.length === 3, 'bad later-consumed field does not preflight or prevent forward allocations');
      check(isZero(f.real.getNode(f.allocated[0]!)), 'failure leaves earlier head allocated and untouched');
      checkLoaded(f.real.getNode(f.allocated[2]!), tailInput, null, 'fully initialized tail survives failure');
      checkPrefix(f.real.getNode(f.allocated[1]!), before, input, f.allocated[2]!, probe.stores,
        `deferred ${probe.key} failure preserves exactly preceding stores`);
    }
  }
  {
    // Every consumed descriptor field is checked at its own access, not in a
    // whole-record preflight. Read-only initial inputs are allowed by copying.
    for (let field = 0; field < sourceKeys.length; field++) {
      const f = fixture(), tailInput = descriptor({start08: 31}), tail = f.loader.createDescriptor(tailInput);
      const input = descriptor({next00: tail}), head = f.loader.createDescriptor(input);
      Object.defineProperty(f.loader.getDescriptor(head), sourceKeys[field]!, {writable: false});
      let before!: SourceFObjHeader;
      f.hooks.allocate = (id, index) => { if (index === 0) { poisonTargets(f.real.getNode(id)); before = {...f.real.getNode(id)}; } };
      rejects(() => f.loader.loadDescriptors(head), 'non-writable descriptor');
      check(f.allocated.length === (field === 0 ? 1 : 2), 'readonly descriptor fails only at consumption');
      checkPrefix(f.real.getNode(f.allocated[0]!), before, input, f.allocated[1] ?? null, field,
        'readonly descriptor keeps exact preceding target stores');
      if (field !== 0) checkLoaded(f.real.getNode(f.allocated[1]!), tailInput, null, 'readonly head leaves completed tail');
    }
    // Every target store checks writability, ignoring its old invalid value.
    for (let field = 0; field < targetKeys.length; field++) {
      const f = fixture(), tailInput = descriptor(), tail = f.loader.createDescriptor(tailInput);
      const input = descriptor({next00: tail, data10: Symbol('base')}), head = f.loader.createDescriptor(input);
      let before!: SourceFObjHeader;
      f.hooks.allocate = (id, index) => {
        if (index === 0) {
          const node = f.real.getNode(id); poisonTargets(node); before = {...node};
          Object.defineProperty(node, targetKeys[field]!, {writable: false});
        }
      };
      rejects(() => f.loader.loadDescriptors(head), `${targetKeys[field]}: non-writable target`);
      checkPrefix(f.real.getNode(f.allocated[0]!), before, input, f.allocated[1]!, field,
        'readonly target keeps exact source store prefix including flags last');
      checkLoaded(f.real.getNode(f.allocated[1]!), tailInput, null, 'readonly target does not roll back initialized tail');
    }
    const f = fixture(), input = descriptor({data10: Symbol('base')}), id = f.loader.createDescriptor(Object.freeze(input));
    f.hooks.allocate = nodeId => {
      const node = f.real.getNode(nodeId); poisonTargets(node);
      node.cursor04 = 17 as unknown as symbol; node.frame1c = NaN; node.byte11 = -1;
      for (const key of ['cursor04', 'frame1c', 'byte11']) Object.defineProperty(node, key, {writable: false});
    };
    const loaded = f.loader.loadDescriptors(id)!, node = f.real.getNode(loaded), expected = expectedStores(input, null);
    check(targetKeys.every(key => Object.is(node[key], expected[key])), 'all overwritten poison values are ignored');
    check(node.cursor04 === (17 as unknown as symbol) && Number.isNaN(node.frame1c) && node.byte11 === -1,
      'unrelated readonly invalid target fields are neither read nor changed');
  }
  {
    const f = fixture(), skipped = f.loader.createDescriptor(descriptor({start08: 2}));
    const replacement = f.loader.createDescriptor(descriptor({start08: 3}));
    const head = f.loader.createDescriptor(descriptor({next00: skipped, start08: 1}));
    f.hooks.allocate = (_id, index) => {
      if (index === 0) f.loader.getDescriptor(head).next00 = replacement;
      if (index === 1) {
        // next was already read. It must never be checked again on unwind.
        f.loader.getDescriptor(head).next00 = 11 as unknown as symbol;
        Object.defineProperty(f.loader.getDescriptor(head), 'next00', {writable: false});
        f.loader.getDescriptor(head).start08 = 17;
        f.loader.getDescriptor(replacement).track0c = 29;
      }
    };
    const result = f.loader.loadDescriptors(head)!;
    check(f.allocated.length === 2 && f.real.getNode(result).offset18 === 17 &&
      f.real.getNode(f.allocated[1]!).offset18 === 3 && f.real.getNode(f.allocated[1]!).track13 === 29,
      'reads next after allocation, follows mutation, and reads remaining fields only on reverse initialization');
    check(f.real.getNode(result).next00 === f.allocated[1], 'already-consumed corrupted readonly next is ignored');
  }
  {
    const f = fixture(), tailInput = descriptor(), tail = f.loader.createDescriptor(tailInput);
    const head = f.loader.createDescriptor(descriptor({next00: tail}));
    f.hooks.resolve = id => {
      if (id === f.allocated[0]) {
        const consumed = f.loader.getDescriptor(tail);
        for (const key of sourceKeys) Object.defineProperty(consumed, key, {value: NaN, writable: false});
        Object.freeze(f.real.getNode(f.allocated[1]!));
      }
    };
    check(f.loader.loadDescriptors(head) === f.allocated[0], 'already-consumed descriptor/header fields are never revalidated');
    checkLoaded(f.real.getNode(f.allocated[1]!), tailInput, null, 'frozen completed tail remains intact');
  }
  {
    for (const kind of ['self', 'two', 'budget', 'foreign', 'bad-next'] as const) {
      const f = fixture(kind === 'budget' ? 1 : 4096);
      const tail = f.loader.createDescriptor(descriptor()), head = f.loader.createDescriptor(descriptor({next00: tail}));
      if (kind === 'self') f.loader.getDescriptor(head).next00 = head;
      if (kind === 'two') f.loader.getDescriptor(tail).next00 = head;
      if (kind === 'foreign') f.loader.getDescriptor(head).next00 = Symbol('non-owned descriptor');
      if (kind === 'bad-next') f.loader.getDescriptor(head).next00 = 7 as unknown as symbol;
      // If a cycle/budget mutation disables the real guards, fail boundedly.
      f.hooks.allocate = (_id, index) => { if (index > 4) throw Error('test allocation safety cap'); };
      rejects(() => f.loader.loadDescriptors(head), kind === 'budget' ? 'budget' :
        kind === 'foreign' ? 'non-owned descriptor' : kind === 'bad-next' ? 'opaque symbol' : 'cycle/revisited');
      check(f.allocated.length === (kind === 'two' || kind === 'foreign' ? 2 : 1),
        'cycle/budget guards precede another allocation; foreign resolution follows its allocation');
      check(f.resolved.length === 0 && f.allocated.every(id => isZero(f.real.getNode(id))),
        'forward traversal failure retains allocated zero prefix with no reverse initialization');
      f.loader.getDescriptor(head).next00 = null;
      check(f.loader.loadDescriptors(head) === f.allocated[f.allocated.length - 1], 'traversal failure releases loader guard');
    }
    const f = fixture();
    rejects(() => f.loader.loadDescriptors(1 as unknown as symbol), 'opaque symbol');
    check(f.allocated.length === 0, 'invalid head type refuses before allocation');
    rejects(() => f.loader.getDescriptor(Symbol()), 'non-owned descriptor');
    const other = fixture(), foreign = other.loader.createDescriptor(descriptor());
    rejects(() => f.loader.loadDescriptors(foreign), 'non-owned descriptor');
    check(f.allocated.length === 1 && isZero(f.real.getNode(f.allocated[0]!)), 'foreign factory identity is never adopted');
  }
  {
    const f = fixture();
    let reads = 0;
    const getter = descriptor();
    Object.defineProperty(getter, 'start08', {get() { reads++; return 1; }});
    rejects(() => f.loader.createDescriptor(getter), 'own data');
    check(reads === 0, 'descriptor getter rejected without invocation');
    const inherited = Object.assign(Object.create({start08: 0}), descriptor()) as SourceFObjDescriptor;
    delete (inherited as Partial<SourceFObjDescriptor>).start08;
    rejects(() => f.loader.createDescriptor(inherited), 'own data');
    const extras = descriptor();
    Object.defineProperty(extras, 'unused', {get() { throw Error('unrelated getter must not run'); }});
    check(f.loader.loadDescriptors(f.loader.createDescriptor(extras)) !== null, 'unmodeled descriptor fields are ignored');
    for (const value of [null, 3, undefined]) rejects(() => f.loader.createDescriptor(value as unknown as SourceFObjDescriptor), 'data record');
    for (const [key, value] of [['next00', 1], ['data10', 2], ['length04', 0.5], ['length04', -1],
      ['track0c', 256], ['format0d', NaN], ['format0e', '0']] as const) {
      rejects(() => f.loader.createDescriptor({...descriptor(), [key]: value} as SourceFObjDescriptor), key);
    }
    for (const max of [0, -1, 0.5, NaN, Infinity, Number.MAX_SAFE_INTEGER + 1]) {
      rejects(() => createSourceFObjDescriptorRuntime(f.real, max), 'positive safe integer');
    }
    rejects(() => createSourceFObjDescriptorRuntime(null as unknown as SourceFObjRuntime), 'data table');
    const inheritedMethods = Object.create(f.methods) as SourceFObjRuntime;
    rejects(() => createSourceFObjDescriptorRuntime(inheritedMethods), 'own data');
    const getterMethods = {...f.methods};
    Object.defineProperty(getterMethods, 'createNode', {get() { reads++; return f.methods.createNode; }});
    rejects(() => createSourceFObjDescriptorRuntime(getterMethods), 'own data');
    check(reads === 0, 'runtime method getters rejected without invocation');
    rejects(() => createSourceFObjDescriptorRuntime({...f.methods, getNode: 1} as unknown as SourceFObjRuntime), 'data-functions');
  }
  {
    const f = fixture(), tail = f.loader.createDescriptor(descriptor()), head = f.loader.createDescriptor(descriptor({next00: tail}));
    f.methods.createNode = () => { throw Error('replaced allocator must not run'); };
    f.hooks.allocate = () => { f.methods.getNode = () => { throw Error('replaced resolver must not run'); }; };
    check(f.loader.loadDescriptors(head) === f.allocated[0] && f.allocated.length === 2 && f.resolved.length === 2,
      'both runtime methods are captured once, not at load or after allocation');
    check(f.loader.loadDescriptors(tail) === f.allocated[2], 'fixed methods survive repeat loads and preserve original receiver');
  }
  {
    for (const caught of [false, true]) {
      const f = fixture(), id = f.loader.createDescriptor(descriptor());
      f.hooks.allocate = () => {
        check(f.loader.loadDescriptors(null) === null, 'null reentry remains a true no-op');
        if (caught) {
          rejects(() => f.loader.loadDescriptors(id), 'reentry');
          f.loader.getDescriptor(id).next00 = 5 as unknown as symbol;
        } else f.loader.loadDescriptors(id);
      };
      rejects(() => f.loader.loadDescriptors(id), caught ? 'reentry was caught' : 'reentry');
      check(f.allocated.length === 1 && f.resolved.length === 0 && isZero(f.real.getNode(f.allocated[0]!)),
        'caught/uncaught reentry preserves actual allocation and aborts before descriptor next read');
      delete f.hooks.allocate; f.loader.getDescriptor(id).next00 = null;
      check(f.loader.loadDescriptors(id) === f.allocated[1], 'reentry guard recovers on next independent load');
    }
    const f = fixture(), id = f.loader.createDescriptor(descriptor());
    f.hooks.allocate = () => { check(f.loader.loadDescriptors(null) === null, 'null-only nested load succeeds'); };
    check(f.loader.loadDescriptors(id) === f.allocated[0], 'null-only nesting does not poison outer load');
    f.hooks.resolve = () => { rejects(() => f.loader.loadDescriptors(id), 'reentry'); };
    rejects(() => f.loader.loadDescriptors(id), 'reentry was caught');
    check(isZero(f.real.getNode(f.allocated[1]!)), 'caught resolver reentry refuses before stores too');
  }
  {
    // Host wrappers still perform real allocation, then deliberately misbehave.
    // These refusal probes do not emulate source allocator failure semantics.
    const real = createSourceFObjRuntime(() => {}), ids: symbol[] = [];
    const wrapper = {
      createNode(initial: SourceFObjHeader) { const id = real.createNode(initial); ids.push(id); return null as unknown as symbol; },
      getNode: real.getNode,
    };
    const bad = createSourceFObjDescriptorRuntime(wrapper), id = bad.createDescriptor(descriptor());
    rejects(() => bad.loadDescriptors(id), 'expected owned FObj identity');
    check(ids.length === 1 && isZero(real.getNode(ids[0]!)), 'invalid allocator result cannot report success or roll back real allocation');
    const throwing = createSourceFObjDescriptorRuntime({
      createNode(initial) { const allocated = real.createNode(initial); ids.push(allocated); throw Error('synthetic allocator failure'); },
      getNode: real.getNode,
    });
    rejects(() => throwing.loadDescriptors(throwing.createDescriptor(descriptor())), 'synthetic allocator failure');
    check(ids.length === 2 && isZero(real.getNode(ids[1]!)), 'throw after real allocation retains its completed effect');
  }
  console.log('[fobj-descriptor-test] PASS real allocation, ordered descriptor loading, bounded failures and reentry');
}
