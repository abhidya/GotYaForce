/** Bounded offline AObj end-callback globals, not a live animation adapter.
 * Source: chunk_0070.c:2540–2568, InitEndCallBack (80243b24) and
 * InvokeCallBacks (80243b34). counts.stopped/running represent 80436930/2c;
 * state.head28 represents 80436928. The counters are the actual owned records
 * accepted by interpretSourceAObj, not an independent accounting substitute.
 *
 * Identities are factory-owned symbols, never RAM pointers. Node inputs must
 * be non-proxy records with own data properties; values are copied without
 * invoking getters. Symbol targets are resolved lazily, so a non-owned link or
 * callback may be stored but fails if reached. Nodes/state are sealed mutable
 * data records; the returned method table and its bindings are frozen.
 *
 * Host checks are per accessed field: every read/write requires a writable own
 * data property. Counter reads require uint32, but init overwrites old values
 * without reading/validating them, stopped first then running. Invoke reads
 * stopped, snapshots head if stopped != 0, then reads running. The head is
 * validated/resolved only if that gate admits traversal. The selected head and
 * eligibility are not reloaded.
 * Each node's callback is checked/called before reading its current next field.
 * Fields already consumed, unvisited nodes and excluded heads are not checked.
 * These host refusals are not additional retail control-flow conditions.
 *
 * Handlers receive no arguments and an undefined this argument. They may mutate
 * owned records and register nodes/handlers, but must synchronously return
 * undefined and must not schedule deferred mutations. A returned Promise is
 * refused after its synchronous prefix; pending JS work cannot be rolled back.
 * Same-runtime init/invoke reentry (even if caught by a handler), cycles,
 * revisits and the per-invocation node budget are unsupported. Failure retains
 * all earlier writes/effects. No rollback, automatic counter reset, RAM aliasing,
 * callback registration/removal semantics or capture/retail parity is claimed.
 */
import {createSourceAObjCounters, type SourceAObjCounters} from './aobj-clock.js';

export interface SourceAObjEndCallbackNode {
  next00: symbol | null;
  callback04: symbol;
}
export interface SourceAObjEndCallbackRuntime {
  readonly counts: SourceAObjCounters;
  readonly state: {head28: symbol | null};
  createCallback(handler: () => void): symbol;
  createNode(initial: SourceAObjEndCallbackNode): symbol;
  getNode(identity: symbol): SourceAObjEndCallbackNode;
  init(): void;
  invoke(): void;
}
function fail(reason: string): never {
  throw Error(`[aobj-end-callbacks] ${reason}; offline execution aborted, prior writes/effects are not rolled back`);
}
function symbolOrNull(value: unknown, where: string): asserts value is symbol | null {
  if (value !== null && typeof value !== 'symbol') fail(`${where}: expected opaque symbol or null`);
}
function callbackSymbol(value: unknown): asserts value is symbol {
  if (typeof value !== 'symbol') fail('callback04: expected opaque callback symbol');
}
function ownValue(record: object, key: string, writable: boolean): unknown {
  const property = Object.getOwnPropertyDescriptor(record, key);
  if (!property || !('value' in property)) fail(`${key}: own data property required`);
  if (writable && !property.writable) fail(`${key}: non-writable field is unsupported`);
  return property.value;
}
/** maxNodes limits visited nodes in each invocation, not allocation or the
 * number of times the list may be invoked. Null/ineligible lists visit none.
 */
export function createSourceAObjEndCallbackRuntime(maxNodes = 4096): SourceAObjEndCallbackRuntime {
  if (!Number.isSafeInteger(maxNodes) || maxNodes < 1) fail('maxNodes must be a positive safe integer');
  const counts = createSourceAObjCounters();
  const state: SourceAObjEndCallbackRuntime['state'] = Object.seal({head28: null});
  const nodes = new Map<symbol, SourceAObjEndCallbackNode>();
  const callbacks = new Map<symbol, () => void>();
  let busy = false, reentered = false;
  const enter = (): void => {
    if (busy) {
      reentered = true;
      fail('same-runtime init/invoke reentry is unsupported');
    }
    busy = true;
    reentered = false;
  };
  const counter = (key: 'stopped' | 'running'): number => {
    const value = ownValue(counts, key, true);
    if (typeof value !== 'number' || !Number.isInteger(value) || value < 0 || value > 0xffffffff) {
      fail(`${key}: expected uint32`);
    }
    return value;
  };
  const getNode = (id: symbol): SourceAObjEndCallbackNode => {
    const node = nodes.get(id);
    if (!node) fail('unknown/non-owned node identity');
    return node;
  };
  return Object.freeze({
    counts,
    state,
    createCallback(handler: () => void): symbol {
      if (typeof handler !== 'function') fail('synchronous zero-argument handler required');
      const id = Symbol('owned AObj end callback');
      callbacks.set(id, handler);
      return id;
    },
    createNode(initial: SourceAObjEndCallbackNode): symbol {
      if (initial === null || typeof initial !== 'object') fail('initial node data record required');
      const next00 = ownValue(initial, 'next00', false);
      const callback04 = ownValue(initial, 'callback04', false);
      symbolOrNull(next00, 'next00');
      callbackSymbol(callback04);
      const id = Symbol('owned AObj end-callback node');
      nodes.set(id, Object.seal({next00, callback04}));
      return id;
    },
    getNode,
    init(): void {
      enter();
      try {
        ownValue(counts, 'stopped', true);
        counts.stopped = 0;
        ownValue(counts, 'running', true);
        counts.running = 0;
      } finally { busy = false; }
    },
    invoke(): void {
      enter();
      try {
        if (counter('stopped') === 0) return;
        // Source loads head between the two counter tests. This owned sealed
        // field cannot be an accessor; defer host validation until eligible.
        const head = state.head28;
        if (counter('running') !== 0) return;
        ownValue(state, 'head28', true);
        symbolOrNull(head, 'head28');
        let id: symbol | null = head;
        const seen = new Set<symbol>();
        while (id !== null) {
          if (seen.has(id)) fail('node cycle/revisit is unsupported');
          if (seen.size >= maxNodes) fail('visited-node budget exhausted');
          seen.add(id);
          const node = getNode(id);
          const callback = ownValue(node, 'callback04', true);
          callbackSymbol(callback);
          const handler = callbacks.get(callback);
          if (!handler) fail('unknown/non-owned callback identity');
          let result: unknown;
          try { result = Reflect.apply(handler, undefined, []); }
          catch (error) { fail(`handler threw (${String(error)})`); }
          if (reentered) fail('same-runtime init/invoke reentry is unsupported');
          if (result !== undefined) fail('handler must complete synchronously and return undefined');
          // Reload the CURRENT node's next field only after its callback returns.
          const next = ownValue(node, 'next00', true);
          symbolOrNull(next, 'next00');
          id = next;
        }
      } finally { busy = false; }
    },
  });
}
