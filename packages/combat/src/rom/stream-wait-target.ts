/** Shared source stream-target continuation, offline.
 * Source: chunk_0006.c:2082–2092 (4cd24 unmet non-countdown wait) and
 * 1551–1569 (4c050 fallback when no opcode1 handler ran). The caller selects
 * the reached branch; this operation implements their identical per-part body.
 * Stream base is actor+1cd4+index*20; target08 for part1 is actor+1cfc.
 * Copy target08 to previous0c, call real 49e58 updatePart (ignore its signed
 * completion), then read bank0's shared feedback part. A nonzero segment adds
 * signed duration24 to accumulator10 and stores binary32; all segments then
 * reload accumulator10 and add live frame0c with a separate binary32 store.
 * Constant evidence: research/decomp/archived-program-constants-2026-11-13.md.
 * Archived ProgramDB bits 4330000080000000 = 2^52 + 2^31 make the source
 * CONCAT44/subtraction exactly signed16 duration, including its f32 conversion
 * (all 65,536 cases checked). Use that exact integer without double bitcasting.
 * This is archived-byte evidence, not newly verified unchanged executable bytes.
 * Duration-before-accumulator validation is deterministic HOST fault ordering,
 * not a proven instruction evaluation order from the decompiled expression.
 *
 * This does not evaluate the wait predicate, parse/setup/finish a stream, run
 * full 4cd24, or use legacy frameClock/streamPtr/active/tickStream. Four parts,
 * non-proxy own-data inputs, stable actual runtime getters, no RAM aliasing and
 * finite f32 RN00/NI0 arithmetic are explicit host admission bounds. Bindings
 * are copied/sealed, source records stay shared. Methods are fixed with their
 * original receiver; no fake predicate/effect callback is accepted. Read-only
 * operands are allowed; writability is checked only at each reached store.
 * Caught same-runtime mutation reentry poisons the outer call. Failures preserve
 * prior writes/effects. No original replay or live integration claim is made.
 */
import type {SourceActorJointMappingRuntime, SourceActorJointLayout} from './actor-joint-mapping.js';
import type {SourceJointAnimationFeedbackRuntime, SourceJointAnimationPart} from './joint-animation-feedback.js';
import type {SourceActorAnimationDispatchRuntime} from './actor-animation-dispatch.js';

export interface SourceStreamWaitTargetPart {
  target08: number;
  previous0c: number;
  accumulator10: number;
}
export interface SourceStreamWaitTargetRuntime {
  bindActor(actor: symbol, initial: readonly Readonly<SourceStreamWaitTargetPart>[]): void;
  getStreamPart(actor: symbol, index: number): SourceStreamWaitTargetPart;
  continueUnmetNonCountdownWait(actor: symbol, index: number): void;
}
function fail(reason: string): never {
  throw Error(`[stream-wait-target] ${reason}; offline execution aborted, prior writes/effects are not rolled back`);
}
function own(record: object, key: string, writable = false): unknown {
  if (record === null || typeof record !== 'object') fail(`${key}: data record required`);
  const p = Object.getOwnPropertyDescriptor(record, key);
  if (!p || !('value' in p)) fail(`${key}: own data property required`);
  if (writable && !p.writable) fail(`${key}: non-writable field is unsupported`);
  return p.value;
}
function integer(value: unknown, max: number, where: string): asserts value is number {
  if (typeof value !== 'number' || !Number.isInteger(value) || value < 0 || value > max) fail(`${where}: unsigned integer out of range`);
}
function f32(value: unknown, where: string): asserts value is number {
  if (!Number.isFinite(value) || !Object.is(value, Math.fround(value as number))) fail(`${where}: expected finite source float32`);
}
function readFloat(record: object, key: string): number {const value = own(record, key); f32(value, key); return value;}
function write(record: object, key: string, value: number): void {own(record, key, true); (record as Record<string, unknown>)[key] = value;}
function method(table: object, key: string): (...args: never[]) => unknown {
  const fn = own(table, key); if (typeof fn !== 'function') fail(`${key}: own data-function required`);
  return fn as (...args: never[]) => unknown;
}
export function createSourceStreamWaitTargetRuntime(mapping: SourceActorJointMappingRuntime,
  feedback: SourceJointAnimationFeedbackRuntime, dispatch: SourceActorAnimationDispatchRuntime): SourceStreamWaitTargetRuntime {
  const actorGet = method(mapping, 'getActor'), layoutGet = method(mapping, 'getLayout');
  const partGet = method(feedback, 'getPart'), update = method(dispatch, 'updatePart');
  const actors = new Map<symbol, readonly SourceStreamWaitTargetPart[]>();
  let busy = false, reentered = false;
  const enter = (): void => {if (busy) {reentered = true; fail('same-runtime reentry is unsupported');} busy = true; reentered = false;};
  const invoke = (fn: (...args: never[]) => unknown, receiver: object, args: unknown[]): unknown => {
    const result = Reflect.apply(fn, receiver, args);
    if (reentered) fail('same-runtime reentry was caught inside an adapter');
    return result;
  };
  const getStreamPart = (id: symbol, index: number): SourceStreamWaitTargetPart => {
    const parts = actors.get(id); if (!parts) fail('unknown/non-owned actor binding');
    integer(index, 3, 'index'); return parts[index]!;
  };
  return Object.freeze({
    bindActor(id: symbol, initial: readonly Readonly<SourceStreamWaitTargetPart>[]): void {
      enter(); try {
        if (actors.has(id)) fail('actor is already bound');
        invoke(actorGet, mapping, [id]);
        if (!Array.isArray(initial) || own(initial, 'length') !== 4) fail('exactly four stream parts required');
        const copied: SourceStreamWaitTargetPart[] = [];
        for (let i = 0; i < 4; i++) {
          const input = own(initial, String(i)) as object;
          const target08 = readFloat(input, 'target08'), previous0c = readFloat(input, 'previous0c');
          const accumulator10 = readFloat(input, 'accumulator10');
          copied.push(Object.seal({target08, previous0c, accumulator10}));
        }
        actors.set(id, Object.freeze(copied));
      } finally {busy = false;}
    },
    getStreamPart,
    continueUnmetNonCountdownWait(id: symbol, index: number): void {
      enter(); try {
        const stream = getStreamPart(id, index);
        write(stream, 'previous0c', readFloat(stream, 'target08'));
        // Source ignores the signed completion value, including readiness/freeze returns.
        const completion = invoke(update, dispatch, [id, index]);
        // Host synchronous contract only; the signed value never gates source flow.
        if (typeof completion !== 'number' || !Number.isInteger(completion) || completion < -128 || completion > 127) {
          fail('updatePart must complete synchronously and return a signed byte');
        }
        const layout = invoke(layoutGet, mapping, [id]) as SourceActorJointLayout;
        const rows = own(layout, 'parts') as object, bank0 = own(rows, '0') as object;
        const partId = own(bank0, String(index));
        if (typeof partId !== 'symbol') fail('part: owned identity required');
        const part = invoke(partGet, feedback, [partId]) as SourceJointAnimationPart;
        const segment = own(part, 'segment2d'); integer(segment, 255, 'segment2d');
        if (segment !== 0) {
          // Host admission order only; source C does not establish operand order.
          const duration = own(part, 'duration24');
          if (typeof duration !== 'number' || !Number.isInteger(duration) || duration < -32768 || duration > 32767) {
            fail('duration24: signed integer out of range');
          }
          // A source signed short zero converts to +0 (even if host input is -0).
          const wrapped = Math.fround(readFloat(stream, 'accumulator10') + (duration === 0 ? 0 : duration));
          f32(wrapped, 'accumulator10 result');
          write(stream, 'accumulator10', wrapped);
        }
        // Fresh load after the reached accumulator store; do not fuse the sums.
        const accumulator = readFloat(stream, 'accumulator10');
        const frame = readFloat(part, 'frame0c');
        const target = Math.fround(accumulator + frame); f32(target, 'target08 result');
        write(stream, 'target08', target);
      } finally {busy = false;}
    },
  });
}
