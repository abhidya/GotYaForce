/** Offline header/list effects for 802488b8, 8024895c and 8024a198.
 * Source: research/decomp/ghidra-export/chunk_0071.c:215–273,1210–1226.
 * This includes a bounded loader stage, NOT the per-node interpolator or live integration.
 * A callback-null timing factory is available separately in fobj-timing.ts.
 * The caller must supply the actual synchronous per-node interpreter or throw
 * for unsupported operations. No default/no-op interpreter is supplied.
 *
 * Only separately owned sealed scalar headers are modeled, not aliased RAM,
 * pointer arithmetic, unmodeled header fields or arbitrary PPC FP environments.
 * next00 is an owned node identity; cursor04/base08 are opaque data identities.
 * Request arithmetic requires finite binary32 arguments: Gekko §2.2.3
 * requires single operands. RN=00 and NI=0 are model preconditions, not an
 * observed runtime FPSCR setting. Other effects forward finite double arguments.
 * Callbacks may mutate live fields and links. Traversal reloads next AFTER the
 * callback (and stop's flag clear); it never snapshots a list. Cycles/revisits,
 * budget exhaustion and any same-runtime reentry are unsupported. Failures stop
 * execution without rolling back prior stores/callbacks. Async/deferred writes
 * are unsupported; a non-undefined callback result is rejected after invocation.
 */
import {addSourceFloat32} from './source-float.js';
import {createSourceFObjData, type SourceFObjData} from './fobj-data.js';
import type {AObjCallbackIdentity, FObjListIdentity, SourceAObjEffects} from './aobj-clock.js';
export interface SourceFObjHeader {
  next00: FObjListIdentity;
  cursor04: symbol | null;
  base08: symbol | null;
  length0c: number;
  flags10: number;
  byte11: number;
  byte12: number;
  track13: number;
  format14: number;
  format15: number;
  half16: number;
  offset18: number;
  half1a: number;
  frame1c: number;
  value20: number;
  value24: number;
  value28: number;
  value2c: number;
}
export type SourceFObjInterpreter = (node: SourceFObjHeader, delta: number,
  callback: AObjCallbackIdentity) => void;
export interface SourceFObjRuntime extends SourceFObjData {
  createNode(initial: SourceFObjHeader): symbol;
  getNode(identity: symbol): SourceFObjHeader;
  validateNode(node: SourceFObjHeader): void;
  removeNode(identity: FObjListIdentity): void;
  removeAll(head: FObjListIdentity): void;
  effects: SourceAObjEffects;
}
const keys = ['next00', 'cursor04', 'base08', 'length0c', 'flags10', 'byte11', 'byte12',
  'track13', 'format14', 'format15', 'half16',
  'offset18', 'half1a', 'frame1c', 'value20', 'value24', 'value28', 'value2c'] as const;
function fail(where: string, why: string): never {
  throw Error(`[fobj-list] ${where}: ${why}; offline execution aborted, prior writes/effects are not rolled back`);
}
function integer(value: number, min: number, max: number, where: string): void {
  if (!Number.isInteger(value) || value < min || value > max) fail(where, `expected integer ${min}..${max}`);
}
function identity(value: unknown, where: string): void {
  if (value !== null && typeof value !== 'symbol') fail(where, 'expected opaque symbol or null');
}
function validate(n: SourceFObjHeader): void {
  for (const key of keys) {
    if (!Object.getOwnPropertyDescriptor(n, key)?.writable) fail(key, 'non-writable scalar field');
  }
  for (const key of ['next00', 'cursor04', 'base08'] as const) identity(n[key], key);
  for (const key of ['flags10', 'byte11', 'byte12', 'track13', 'format14', 'format15'] as const) integer(n[key], 0, 255, key);
  for (const key of ['half16', 'half1a'] as const) integer(n[key], 0, 65535, key);
  integer(n.length0c, 0, 0xffffffff, 'length0c');
  integer(n.offset18, -32768, 32767, 'offset18');
  for (const key of ['frame1c', 'value20', 'value24', 'value28', 'value2c'] as const) {
    if (!Number.isFinite(n[key]) || !Object.is(n[key], Math.fround(n[key]))) fail(key, 'expected finite source float32');
  }
}
/** maxNodes is an offline safety limit, not a retail list-length constant. */
export function createSourceFObjRuntime(interpreter: SourceFObjInterpreter, maxNodes = 4096): SourceFObjRuntime {
  if (typeof interpreter !== 'function') fail('create', 'synchronous per-node interpreter required');
  integer(maxNodes, 1, Number.MAX_SAFE_INTEGER, 'maxNodes');
  const nodes = new Map<symbol, SourceFObjHeader>();
  const ownedHeaders = new WeakSet<SourceFObjHeader>();
  const validateNode = (node: SourceFObjHeader): void => {
    if (!ownedHeaders.has(node)) fail('validateNode', 'non-owned header');
    validate(node);
  };
  const data = createSourceFObjData(validateNode);
  let busy = false;
  // A caught removal refusal must not let the outer interpreter continue stores.
  let removalRefused = false;
  const getNode = (id: symbol): SourceFObjHeader => {
    const node = nodes.get(id);
    if (!node) fail('resolve', 'unknown/non-owned node identity');
    return node;
  };
  // 8024876c/80248794 -> 8024a48c (chunk_0071.c:128–211,1367–1376).
  // Release only runtime ownership, not the source allocator pool, backing data,
  // address reuse or ABA behavior. ObjFree also writes pool links/counts
  // (chunk_0072.c:380–388); preserving JS fields is not freed-RAM parity.
  // Cached JS objects remain ordinary objects,
  // but no longer pass any runtime owned-header validation.
  const release = (id: symbol, node: SourceFObjHeader): void => {
    nodes.delete(id);
    ownedHeaders.delete(node);
  };
  const removeNode = (id: FObjListIdentity): void => {
    if (id === null) return;
    if (busy) {
      removalRefused = true;
      fail('removeNode', 'same-runtime reentry is unsupported');
    }
    identity(id, 'removeNode');
    // Source single removal reads no fields, including next00.
    release(id, getNode(id));
  };
  const removeAll = (head: FObjListIdentity): void => {
    if (head === null) return;
    if (busy) {
      removalRefused = true;
      fail('removeAll', 'same-runtime reentry is unsupported');
    }
    identity(head, 'removeAll');
    const chain: {id: symbol; node: SourceFObjHeader}[] = [];
    const seen = new Set<symbol>();
    let current: FObjListIdentity = head;
    while (current !== null) {
      if (seen.has(current)) fail('removeAll', 'cycle/revisited node is unsupported');
      if (seen.size >= maxNodes) fail('removeAll', 'node budget exhausted');
      const node = getNode(current);
      // Only the source-read next word matters. Read an own data descriptor,
      // accepting stable read-only links without invoking accessors or requiring
      // unrelated scalar fields to be valid/writable.
      const next = Object.getOwnPropertyDescriptor(node, 'next00');
      if (!next || !Object.hasOwn(next, 'value')) fail('removeAll', 'next00 must be an own data field');
      identity(next.value, 'next00');
      seen.add(current);
      chain.push({id: current, node});
      current = next.value as FObjListIdentity;
    }
    // Structured-decompilation model: recursive descent finishes before unwind.
    // The export loses recursive call arguments; no instruction/ABI accuracy
    // is claimed here. Host traversal failures therefore release nothing.
    // Its nine-node unroll is not a length limit; this explicit stack avoids
    // host recursion overflow.
    for (let i = chain.length - 1; i >= 0; i--) {
      const entry = chain[i]!;
      release(entry.id, entry.node);
    }
  };
  const walk = (head: FObjListIdentity, value: number, callback: AObjCallbackIdentity,
    operation: 'request' | 'stop' | 'interpret'): void => {
    if (head === null) return; // Real no-op, including otherwise invalid arguments.
    if (busy) fail(operation, 'same-runtime reentry is unsupported');
    identity(head, 'head');
    if (!Number.isFinite(value)) fail(operation, 'expected finite double argument');
    if (operation === 'request' && !Object.is(value, Math.fround(value))) {
      fail(operation, 'expected finite float32 request operand');
    }
    identity(callback, 'callback');
    busy = true;
    removalRefused = false;
    const seen = new Set<symbol>();
    try {
      let current: FObjListIdentity = head;
      while (current !== null) {
        if (seen.has(current)) fail(operation, 'cycle/revisited node is unsupported');
        if (seen.size >= maxNodes) fail(operation, 'node budget exhausted');
        const n = getNode(current);
        validate(n);
        seen.add(current);
        if (operation === 'request') {
          n.cursor04 = n.base08;
          // Signed short is exactly representable as float32. The original
          // request must already be single; unsupported doubles are not coerced.
          const frame = addSourceFloat32(n.offset18, value);
          n.frame1c = frame;
          n.byte11 = 0;
          n.byte12 = 0;
          n.flags10 &= 0xbf;
          n.half16 = 0;
          n.half1a = 0;
          n.value20 = 0;
          n.value24 = 0;
          n.value28 = 0;
          n.value2c = 0;
          n.flags10 = (n.flags10 & 0xf0) | 1;
        } else {
          if (operation === 'interpret' || n.byte12 === 6) {
            let result: unknown;
            try { result = interpreter(n, value, callback); }
            catch (error) { fail(operation, `interpreter threw (${String(error)})`); }
            if (result !== undefined) fail(operation, 'interpreter must complete synchronously and return undefined');
            if (removalRefused) fail(operation, 'removal reentry was refused during interpreter');
            validate(n);
          }
          if (operation === 'stop') n.flags10 &= 0xf0;
        }
        current = n.next00;
      }
    } finally { busy = false; }
  };
  return {
    createData: data.createData,
    cursorAt: data.cursorAt,
    cursorOffset: data.cursorOffset,
    loadData: data.loadData,
    loadWait: data.loadWait,
    validateNode,
    createNode(initial) {
      // Explicit copy prevents retaining input objects or accessor-backed state.
      const n = Object.seal({next00: initial.next00, cursor04: initial.cursor04, base08: initial.base08,
        length0c: initial.length0c, flags10: initial.flags10, byte11: initial.byte11, byte12: initial.byte12,
        track13: initial.track13, format14: initial.format14, format15: initial.format15,
        half16: initial.half16, offset18: initial.offset18, half1a: initial.half1a,
        frame1c: initial.frame1c, value20: initial.value20, value24: initial.value24,
        value28: initial.value28, value2c: initial.value2c});
      validate(n);
      const id = Symbol('owned FObj');
      nodes.set(id, n);
      ownedHeaders.add(n);
      return id;
    },
    getNode,
    removeNode,
    removeAll,
    // These methods implement the existing AObj boundary; no AObj code changes
    // or guessed RAM addresses/callback payloads are needed.
    effects: Object.freeze({
      requestAll: (head: FObjListIdentity, frame: number) => walk(head, frame, null, 'request'),
      stopAll: (head: FObjListIdentity, delta: number, cb: AObjCallbackIdentity) => walk(head, delta, cb, 'stop'),
      interpretAll: (head: FObjListIdentity, delta: number, cb: AObjCallbackIdentity) => walk(head, delta, cb, 'interpret'),
    }),
  };
}
