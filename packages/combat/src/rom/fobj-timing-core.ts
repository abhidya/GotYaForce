/** Internal shared FObj timing loop. Source: chunk_0071.c:869–1207.
 * See fobj-timing.ts for the explicit callback-null boundary and fobj-callback.ts
 * for the bounded scalar boundary. No production integration or retail replay.
 * Finite binary32 operands, FPSCR RN=00/NI=0 assumptions, not captured modes.
 * Host refusals retain all completed source writes and callback effects.
 */
import {addSourceFloat32} from './source-float.js';
import {createSourceFObjRuntime, type SourceFObjHeader, type SourceFObjRuntime} from './fobj-list.js';
import type {AObjCallbackIdentity, FObjListIdentity} from './aobj-clock.js';
export interface SourceFObjTimingRuntime extends SourceFObjRuntime {
  interpretNode(node: FObjListIdentity, delta: number, callback: AObjCallbackIdentity): void;
}
function fail(reason: string): never {
  throw Error(`[fobj-timing] ${reason}; offline execution aborted, prior writes are not rolled back`);
}
/** @internal Only the bounded scalar and explicit callback-null factories use
 * this hook. A non-null callback is never silently ignored. Phase gates belong
 * to this loop; opcode gates/evaluation and handler ownership belong to dispatch.
 */
export interface SourceFObjTimingDispatch {
  validateCallback(callback: AObjCallbackIdentity): void;
  invoke(runtime: SourceFObjRuntime, node: SourceFObjHeader, callback: symbol): void;
}
/** @internal Shared clock/loader loop. Limits are host policies, not source
 * constants. Initial states7..15 are refused before clock writes. Null identities
 * return before argument validation or reentry checks. Direct state0 returns
 * before reading delta; list effects retain their finite-delta contract.
 */
export function createSourceFObjTimingRuntime(dispatch: SourceFObjTimingDispatch | null,
  maxTransitions = 65536, maxNodes = 4096): SourceFObjTimingRuntime {
  if (!Number.isSafeInteger(maxTransitions) || maxTransitions < 1) fail('invalid transition budget');
  const storeFrame = (n: SourceFObjHeader, value: number): void => {
    const rounded = Math.fround(value);
    if (!Number.isFinite(rounded)) fail('nonfinite/overflow float32 clock result');
    n.frame1c = rounded;
  };
  const interpret = (n: SourceFObjHeader, delta: number, callback: AObjCallbackIdentity): void => {
    runtime.validateNode(n);
    let state = n.flags10 & 15;
    if (state === 0) return;
    if (state > 6) fail('unsupported state');
    if (!Number.isFinite(delta)) fail('expected finite double delta');
    if (!Object.is(delta, Math.fround(delta))) fail('expected finite float32 delta operand');
    // PPC fadds followed by stfs; unsupported double operands are not coerced.
    n.frame1c = addSourceFloat32(n.frame1c, delta);
    if (n.frame1c < 0) return; // Ordered comparison; nonfinite rejected explicitly.
    let lastWait = 0; // f31 initialized from +0 at 8043d298.
    for (let transitions = 0; ; transitions++) {
      if (transitions >= maxTransitions) fail('transition budget exhausted');
      switch (state) {
        case 0: return;
        case 1:
        case 2: state = runtime.loadData(n); break;
        case 3:
          if ((n.flags10 & 0x80) !== 0) invoke(n, callback);
          // Reload stored state/cursor/length/duration after the handler. The
          // reader must still assert state3 even if the callback changed it.
          state = runtime.loadWait(n);
          break;
        case 4:
          // uint16 -> float32 conversion is exact throughout this domain.
          if (n.half1a <= n.frame1c) {
            lastWait = n.half1a;
            storeFrame(n, n.frame1c - lastWait);
            n.flags10 = (n.flags10 & 0xf0) | 3;
            state = 3;
          } else {
            invoke(n, callback);
            // Source reloads callback-mutated high flags, then overwrites state.
            // A null callback does not evaluate a slope or clear flags20/80.
            n.flags10 = (n.flags10 & 0xf0) | 5;
            return;
          }
          break;
        case 5:
          n.flags10 = (n.flags10 & 0xf0) | 4;
          state = 4;
          break;
        case 6:
          storeFrame(n, n.frame1c + lastWait);
          if ((n.flags10 & 0x40) !== 0) {
            n.byte12 = n.byte11;
            n.flags10 &= 0xbf;
            n.flags10 |= 0x80;
            n.value20 = n.value24;
          }
          invoke(n, callback);
          return; // Local state6 does not overwrite callback-mutated stored state.
        default: fail('unsupported state');
      }
    }
  };
  const runtime = createSourceFObjRuntime(interpret, maxNodes);
  const invoke = (n: SourceFObjHeader, callback: AObjCallbackIdentity): void => {
    if (callback === null) return;
    // Entry preflight proves dispatch exists and owns this callback identity.
    dispatch!.invoke(runtime, n, callback);
    if (removalRefused) fail('removal reentry was refused during interpreter');
    runtime.validateNode(n); // Refuse invalid handler writes before continuing.
  };
  let busy = false;
  // Direct interpretNode does not enter the base list guard. Poison this outer
  // boundary too, so caught removal refusals cannot resume post-handler writes.
  let removalRefused = false;
  const enter = (head: FObjListIdentity, callback: AObjCallbackIdentity, run: () => void): void => {
    if (head === null) return;
    if (busy) fail('same-runtime reentry is unsupported');
    if (dispatch === null) {
      if (callback !== null) fail('non-null callback unsupported');
    } else dispatch.validateCallback(callback);
    busy = true;
    removalRefused = false;
    try { run(); } finally { busy = false; }
  };
  return {...runtime,
    removeNode(identity) {
      if (identity === null) return;
      if (busy) {
        removalRefused = true;
        fail('same-runtime reentry is unsupported');
      }
      runtime.removeNode(identity);
    },
    removeAll(head) {
      if (head === null) return;
      if (busy) {
        removalRefused = true;
        fail('same-runtime reentry is unsupported');
      }
      runtime.removeAll(head);
    },
    loadData(node) {
      if (busy) fail('same-runtime reentry is unsupported');
      return runtime.loadData(node);
    },
    loadWait(node) {
      if (busy) fail('same-runtime reentry is unsupported');
      return runtime.loadWait(node);
    },
    effects: Object.freeze({
      requestAll(head: FObjListIdentity, frame: number) {
        enter(head, null, () => runtime.effects.requestAll(head, frame));
      },
      stopAll(head: FObjListIdentity, delta: number, callback: AObjCallbackIdentity) {
        enter(head, callback, () => runtime.effects.stopAll(head, delta, callback));
      },
      interpretAll(head: FObjListIdentity, delta: number, callback: AObjCallbackIdentity) {
        enter(head, callback, () => runtime.effects.interpretAll(head, delta, callback));
      },
    }),
    interpretNode(identity, delta, callback) {
      enter(identity, callback, () => interpret(runtime.getNode(identity!), delta, callback));
    },
  };
}
