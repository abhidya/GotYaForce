/** Bounded zz_004beb8_ stream start and zz_004c020_ reset (:1430–1530),
 * zz_004cd24_ actor update (chunk_0006.c:1995–2121) and
 * bounded zz_004c050_ parsing (:1538–1603), opcode01 (:1615–1675), opcode02/03 (8004c424/8004c488), and opcode0x10 (:1850–1970), offline only.
 * Covers entry/null/selection/block/finished routing and default/countdown/relative/percentage waits.
 * Actual mapping, feedback, dispatch and target runtimes retain their fields;
 * these sidecars own gates, copied command bytes/cursors and stream controls.
 * Opcode01 reaches actual setup gates and optional bound mode0 setup. Other
 * modes, blocked setup and byte5 factor remain explicit refusals. Part1 requires
 * a real bound movement follow-up. Opcode0x10 modes1/2 and terminal opcode0 are bounded.
 * No RAM alias or live replay. Public start/parse argument defaults are fixtures,
 * not universal source call defaults; update explicitly supplies its source defaults.
 * +0 (804370f4), signed conversion (804370f8), and -1 (80437128) evidence is
 * archived ProgramDB bytes, NOT newly verified unchanged executable bytes:
 * research/decomp/archived-program-constants-2026-11-13.md. Quantized duration
 * loads and 100 (80437148): archived-wait-predicates-2026-11-13.md in that folder.
 * Opcode0x10 table/handler and unsigned conversion (80437140):
 * archived-stream-command-2026-11-13.md. Opcode01/parser/setup gate words:
 * archived-setup-command-2026-11-13.md. The positive command budget is a host
 * bound; unsupported command modes never fall back to legacy handlers.
 * Bank selection, signed byte/index loads and ordered reset stores:
 * archived-stream-start-2026-11-13.md. Start uses actual copied bank cursors;
 * fixture defaults are not source allocation, and no virtual-address wrap is invented.
 * Explicit GQR5=0x00070007 selects a startup-evidenced signed16/scale0 host
 * profile, not a measured live register or a claim that it remains unchanged.
 * Opcode0 records use immutable copied byte snapshots (16MiB host cap), owned
 * uint32 cursors and deferred bounds checks. No retail memory-fault claim. All
 * selected target fallbacks (suppressed after a completed opcode01) precede
 * current00/next04/signed-BE16-wait/finished stores. Opcode0x10 admits only modes1/2; other opcodes/modes and nonfinite percentage outcomes refuse.
 * Start banks are owned cursors, including nonzero backing offsets. Archived
 * lbz/extsb byte loads and 32-bit slwi index arithmetic precede signed BE16
 * offsets. Signed local displacements are added within copied-backing uint32
 * coordinates; no emulated address wrapping, RAM aliases or retail provenance.
 * Four parts, non-proxy own-data records, stable actual runtime getters, finite
 * exact-f32 RN00/NI0 arithmetic are host admission bounds. Countdown admits wait
 * before timestep: deterministic HOST fault order, not proven C operand order.
 * Bindings are copied/sealed; methods fixed with original receivers. Readonly
 * operands are accepted, writability checked only at reached stores. Caught
 * same-runtime mutation reentry poisons the outer operation; prior effects stand.
 * Opcode02/03 follow authenticated8004c424/100 and8004c488/84 instruction
 * windows, not legacy partState event labels. State bytes remain raw u8 and
 * uninitialized until explicit input/store. Actual6e8/6e9 and5e0 come from a
 * once-bound genuine movement join; source582 remains the start owner,584 is
 * untouched. Opcode03 retains both5e0 stores and both operand/current loads.
 * Joined execution uses the existing private frame stream capability and
 * permanent actor/mapping failure guards. Even unjoined state-command failures
 * poison the canonical mapping so a later join cannot replay partial effects.
 */
import {isSourceActorJointMappingRuntime, type SourceActorJointMappingRuntime, type SourceActorJointMappingHeader} from './actor-joint-mapping.js';
import type {RomActor} from './actor.js';
import {isSourceActorMovementFollowupRuntime, type SourceActorMovementFollowupRuntime} from './actor-movement-followup.js';
import {markIncompleteSourceActorDoubleLifecycle, requireCompleteSourceActorDoubleLifecycle, requireSourceActorDoubleInvocation} from './actor-double-prehook.js';
import {markIncompleteSourceActorAnimationTransition, requireCompleteSourceActorAnimationTransition} from './actor-animation-transition.js';
import type {SourceJointAnimationFeedbackRuntime} from './joint-animation-feedback.js';
import type {SourceActorAnimationDispatchRuntime} from './actor-animation-dispatch.js';
import type {SourceStreamWaitTargetRuntime} from './stream-wait-target.js';
export interface SourceStreamWaitCommand {flags01: number;}
export interface SourceStreamWaitActorBinding {activeMask579: number; blockedMask1d9a: number; marker71d: number;}
export type SourceStreamWaitActorInitial = Omit<SourceStreamWaitActorBinding, 'marker71d'> & {marker71d?: number};
export interface SourceStreamWaitStartBinding {familyBank1d80: symbol | null; sharedBank1d84: symbol | null; defaultSelector582: number; marker709: number;}
/** 1b/1c are raw unsigned bytes on the genuine retained part owner. Undefined
 * means no initialized source value, not a retail allocation default. The sealed
 * shape reserves slots so a reached source store can initialize them. */
export interface SourceStreamWaitPartBinding {state1b?: number | undefined; auxiliary1c?: number | undefined; group18: number; action19: number; status1d: number; current00: symbol | null; next04: symbol | null; wait14: number; finished1a: number; event1e: number;}
export type SourceStreamWaitPartInitial = Omit<SourceStreamWaitPartBinding, 'next04' | 'group18' | 'action19' | 'status1d'> & {next04?: symbol | null; group18?: number; action19?: number; status1d?: number};
export interface SourceStreamWaitRuntime {
  /** Once-bound identity join via genuine movement, after movement.bindActor. */
  bindActualActor(actor: symbol, movement: SourceActorMovementFollowupRuntime): void;
  hasActualActorBinding(actor: symbol): boolean;
  getActualActor(actor: symbol): RomActor;
  getMappingActor(actor: symbol): SourceActorJointMappingHeader;
  bindStartActor(actor: symbol, initial: Readonly<SourceStreamWaitStartBinding>): void;
  getStartActorBinding(actor: symbol): SourceStreamWaitStartBinding;
  startStream(actor: symbol, mask: number, selector: number, actionIndex: number, startFrame?: number, transition?: number, mode?: number): void;
  createStream(bytes: Uint8Array): symbol;
  cursorAt(base: symbol, offset: number): symbol;
  cursorOffset(base: symbol, cursor: symbol): number;
  parseWaitRecord(actor: symbol, mask: number, cursor: symbol, startFrame?: number, transition?: number, mode?: number): void;
  createCommand(initial: Readonly<SourceStreamWaitCommand>): symbol;
  getCommand(command: symbol): SourceStreamWaitCommand;
  bindActor(actor: symbol, initial: Readonly<SourceStreamWaitActorInitial>, parts: readonly Readonly<SourceStreamWaitPartInitial>[]): void;
  getActorBinding(actor: symbol): SourceStreamWaitActorBinding;
  getPartBinding(actor: symbol, index: number): SourceStreamWaitPartBinding;
  update(actor: symbol, mask: number): 0 | 1;
}
const sourceStreamWaitRuntimes = new WeakSet<object>(), assignedActualActors = new WeakSet<object>();
export function isSourceStreamWaitRuntime(value: unknown): value is SourceStreamWaitRuntime {
  return value !== null && typeof value === 'object' && sourceStreamWaitRuntimes.has(value);
}
function fail(reason: string): never {throw Error(`[stream-wait] ${reason}; offline execution aborted, prior writes/effects are not rolled back`);}
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
function byte(record: object, key: string): number {const value = own(record, key); integer(value, 255, key); return value;}
function f32(value: unknown, where: string): asserts value is number {
  if (!Number.isFinite(value) || !Object.is(value, Math.fround(value as number))) fail(`${where}: expected finite source float32`);
}
function readFloat(record: object, key: string): number {const value = own(record, key); f32(value, key); return value;}
function signedDuration(record: object): number {
  const value = own(record, 'duration24');
  if (typeof value !== 'number' || !Number.isInteger(value) || value < -32768 || value > 32767) fail('duration24: expected signed16 integer');
  return value === 0 ? 0 : value; // An integer psq_l zero is positive, including host -0.
}
function write(record: object, key: string, value: number | symbol | null): void {own(record, key, true); (record as Record<string, unknown>)[key] = value;}
function method(table: object, key: string): (...args: never[]) => unknown {
  const fn = own(table, key); if (typeof fn !== 'function') fail(`${key}: own data-function required`); return fn as (...args: never[]) => unknown;
}
export function createSourceStreamWaitRuntime({mapping, feedback, dispatch, targets, gqr5, maxCommands = 4096}: {
  mapping: SourceActorJointMappingRuntime; feedback: SourceJointAnimationFeedbackRuntime;
  dispatch: SourceActorAnimationDispatchRuntime; targets: SourceStreamWaitTargetRuntime;
  /** Immutable selected host profile, checked only on a reached quantized load. */
  gqr5?: number;
  /** Immutable positive safe-integer host execution bound, excluding terminal opcode0. */
  maxCommands?: number;
}): SourceStreamWaitRuntime {
  if (!Number.isSafeInteger(maxCommands) || maxCommands <= 0) fail('maxCommands: positive safe integer required');
  const requireDurationProfile = (): void => {
    if (gqr5 !== 0x00070007) fail('GQR5: quantized duration load requires explicit startup host profile 0x00070007 (signed16, scale0)');
  };
  const actorGet = method(mapping, 'getActor'), layoutGet = method(mapping, 'getLayout');
  const feedbackGet = method(feedback, 'getPart'), dispatchGet = method(dispatch, 'getPartBinding');
  const dispatchUpdate = method(dispatch, 'updatePart'), targetUpdate = method(targets, 'continueUnmetNonCountdownWait');
  const targetGet = method(targets, 'getStreamPart'), dispatchSetup = method(dispatch, 'setupPart');
  type Stream = {bytes: Uint8Array; cursors: Map<number, symbol>};
  const streams = new Map<symbol, Stream>();
  const cursors = new Map<symbol, {stream: Stream; offset: number}>();
  const ownedCursor = (id: symbol) => {const found = cursors.get(id); if (!found) fail('owned byte cursor required'); return found;};
  const intern = (stream: Stream, offset: number): symbol => {
    integer(offset, 0xffffffff, 'cursor offset');
    let id = stream.cursors.get(offset);
    if (id === undefined) {id = Symbol('stream cursor'); stream.cursors.set(offset, id); cursors.set(id, Object.freeze({stream, offset}));}
    return id;
  };
  const readByte = (id: symbol, delta: number): number => {
    const {stream, offset} = ownedCursor(id), at = offset + delta;
    if (at > 0xffffffff || at >= stream.bytes.length) fail('stream byte read out of bounds');
    return stream.bytes[at]!;
  };
  const relativeCursor = (base: symbol, displacement: number): symbol => {
    const {stream, offset} = ownedCursor(base);
    // Deliberate host bound: no source-address wrapping or invented RAM aliases.
    return intern(stream, offset + displacement);
  };
  const signedOffset = (cursor: symbol): number => {
    const raw = readByte(cursor, 0) * 256 + readByte(cursor, 1);
    return raw >= 0x8000 ? raw - 0x10000 : raw;
  };
  const starts = new Map<symbol, SourceStreamWaitStartBinding>();
  const startRecord = (id: symbol): SourceStreamWaitStartBinding => {
    const found = starts.get(id); if (!found) fail('unknown/non-owned start binding'); return found;
  };
  const bankPointer = (record: object, key: string): symbol | null => {
    const value = own(record, key);
    if (value !== null && typeof value !== 'symbol') fail(`${key}: cursor identity required`);
    return value;
  };
  const commands = new Map<symbol, SourceStreamWaitCommand>();
  const actors = new Map<symbol, {source: SourceActorJointMappingHeader; binding: SourceStreamWaitActorBinding;
    parts: readonly SourceStreamWaitPartBinding[]; actual?: RomActor; movement?: SourceActorMovementFollowupRuntime; stateCommandsUsed?: boolean}>();
  let busy = false, reentered = false;
  const enter = (): void => {if (busy) {reentered = true; fail('same-runtime reentry is unsupported');} busy = true; reentered = false;};
  const invoke = (fn: (...args: never[]) => unknown, receiver: object, args: unknown[]): unknown => {
    const result = Reflect.apply(fn, receiver, args); if (reentered) fail('same-runtime reentry was caught inside an adapter'); return result;
  };
  const actorRecord = (id: symbol) => {const found = actors.get(id); if (!found) fail('unknown/non-owned actor binding'); return found;};
  const check = (): void => {if (reentered) fail('same-runtime reentry was caught inside an adapter');};
  const read = (record: object, key: string): unknown => {const value = own(record, key); check(); return value;};
  const readByteField = (record: object, key: string): number => {const value = read(record, key); integer(value, 255, key); return value;};
  const readWord = (record: object, key: string): number => {const value = read(record, key); integer(value, 0xffffffff, key); return value;};
  const store = (record: object, key: string, value: number): void => {
    own(record, key, true); check(); (record as Record<string, unknown>)[key] = value; check();
  };
  const actualActor = (id: symbol): RomActor => {
    const actor = actorRecord(id);
    if (actor.actual === undefined || actor.movement === undefined) fail('genuine movement actual-actor join required');
    if (actor.movement.getActualActor(id) !== actor.actual || actor.movement.getMappingActor(id) !== actor.source ||
        actor.movement.getWaitBinding(id) !== actor.binding || invoke(actorGet, mapping, [id]) !== actor.source)
      fail('canonical actual-actor owners changed');
    check(); return actor.actual;
  };
  // A proved byte store may create missing actual storage. No read/validation of
  // an overwritten value, no constructor zeros, and no duplicate stream mirror.
  const storeActualByte = (actual: RomActor, key: 'byte6e8' | 'byte6e9', value: number): void => {
    const property = Object.getOwnPropertyDescriptor(actual, key); check();
    if (property === undefined) {
      if (!Object.isExtensible(actual)) fail(`${key}: absent actual byte storage is non-extensible`);
      check(); Object.defineProperty(actual, key, {value, writable: true, enumerable: true, configurable: true}); check();
    } else store(actual, key, value);
  };
  const sourceOperation = <T>(id: symbol, run: () => T): T => {
    const actor = actorRecord(id);
    if (actor.actual !== undefined) {
      requireSourceActorDoubleInvocation(actor.actual, 'stream', runtime);
    }
    if (actor.actual !== undefined || actor.stateCommandsUsed) requireCompleteSourceActorAnimationTransition(actor.source);
    try {
      if (actor.actual !== undefined) actualActor(id);
      const result = run(); check(); return result;
    } catch (error) {
      if (actor.actual !== undefined) {
        markIncompleteSourceActorDoubleLifecycle(actor.actual);
      }
      if (actor.actual !== undefined || actor.stateCommandsUsed) markIncompleteSourceActorAnimationTransition(actor.source);
      throw error;
    }
  };
  const getCommand = (id: symbol): SourceStreamWaitCommand => {const found = commands.get(id); if (!found) fail('unknown/non-owned command'); return found;};
  const commandFlags = (part: SourceStreamWaitPartBinding): number => {
    const id = own(part, 'current00'); if (typeof id !== 'symbol') fail('current00: owned command identity required'); return cursors.has(id) ? readByte(id, 1) : byte(getCommand(id), 'flags01');
  };
  const partId = (id: symbol, index: number): symbol => {
    const layout = invoke(layoutGet, mapping, [id]) as object;
    const rows = own(layout, 'parts') as object, row = own(rows, '0') as object;
    const part = own(row, String(index)); if (typeof part !== 'symbol') fail('part: owned identity required'); return part;
  };
  const animate = (id: symbol, index: number): void => {
    const result = invoke(dispatchUpdate, dispatch, [id, index]);
    if (typeof result !== 'number' || !Number.isInteger(result) || result < -128 || result > 127) fail('updatePart must complete synchronously and return a signed byte');
  };
  const fallback = (id: symbol, index: number): void => {
    const returned = invoke(targetUpdate, targets, [id, index]);
    if (returned !== undefined) fail('continueUnmetNonCountdownWait must complete synchronously and return undefined');
  };
  const parse = (id: symbol, mask: number, cursor: symbol, startFrame: number, transitionOverride: number, modeOverride: number): void => {
    integer(mask, 0xffffffff, 'mask');
    const actor = actorRecord(id);
    let count = 0, setupCompleted = false;
    for (let opcode = readByte(cursor, 0); opcode !== 0; opcode = readByte(cursor, 0)) {
      if (count >= maxCommands) fail('maxCommands: nonzero command budget exceeded');
      count++;
      if (opcode === 1) {
        const record = cursor, position = ownedCursor(record);
        cursor = intern(position.stream, position.offset + 8);
        // Each handler receives the original parser arguments, not the preceding
        // handler's mutable frame. Admission is lazy until this opcode is reached.
        let frame = startFrame;
        f32(frame, 'startFrame');
        if (frame < 0) frame = signedOffset(relativeCursor(record, 6));
        const override = (value: number, where: string): number => {
          if (!Number.isInteger(value) || value < -0x80000000 || value > 0xffffffff) fail(`${where}: signed32/uint32 integer required`);
          return value >>> 0;
        };
        let mode = override(modeOverride, 'mode');
        if ((mode | 0) < 0) mode = readByte(record, 3);
        let transition = override(transitionOverride, 'transition');
        if ((transition | 0) < 0) transition = readByte(record, 4);
        for (let i = 0; i < 4; i++) {
          if (!(mask & (1 << i))) continue;
          const control = actor.parts[i]!;
          const target = invoke(targetGet, targets, [id, i]) as object;
          write(target, 'previous0c', readFloat(target, 'target08'));
          if (byte(control, 'status1d') !== 0) {
            const part = invoke(feedbackGet, feedback, [partId(id, i)]) as object;
            // The archived lha precedes lfs: admit signed duration before the
            // accumulator. This integer conversion is not a quantized load.
            const duration = signedDuration(part);
            const accumulator = readFloat(target, 'accumulator10');
            const sum = Math.fround(accumulator + duration);
            f32(sum, 'accumulator10 result'); write(target, 'accumulator10', sum);
          }
          if (frame < 0) {
            const part = invoke(feedbackGet, feedback, [partId(id, i)]) as object;
            frame = Math.fround(readFloat(part, 'frame0c') + readFloat(actor.source, 'timestep1dc8'));
            f32(frame, 'startFrame result');
          }
          const group = readByte(record, 1), action = readByte(record, 2);
          const returned = invoke(dispatchSetup, dispatch, [id, i, actor.binding, {frame, group, action, transition, mode}]);
          if (returned !== undefined) fail('setupPart must complete synchronously and return undefined');
          write(control, 'status1d', 1);
          const accumulator = readFloat(target, 'accumulator10');
          const part = invoke(feedbackGet, feedback, [partId(id, i)]) as object;
          const next = Math.fround(accumulator + readFloat(part, 'frame0c'));
          f32(next, 'target08 result'); write(target, 'target08', next);
        }
        if (mask & 2) write(actor.binding, 'marker71d', 0);
        if (readByte(record, 5) !== 0) fail('opcode01 byte5: unverified 8043712c factor');
        setupCompleted = true;
        continue;
      }
      if (opcode === 2 || opcode === 3) {
        const record = cursor, position = ownedCursor(record);
        // Authenticated stackless handlers advance the parser-local cursor by8
        // even for an unselected mask. Operands/destinations remain lazy.
        cursor = intern(position.stream, position.offset + 8);
        if (opcode === 2) {
          if (!(mask & 1)) continue;
          requireCompleteSourceActorAnimationTransition(actor.source); actor.stateCommandsUsed = true;
          store(actor.parts[0]!, 'state1b', readByte(record, 2));
          store(actor.parts[0]!, 'auxiliary1c', readByte(record, 3));
          const byte6e8 = readByte(record, 4);
          const actual = actualActor(id);
          storeActualByte(actual, 'byte6e8', byte6e8);
          storeActualByte(actual, 'byte6e9', readByte(record, 5));
          // b1 is loaded after all four preceding stores. ff never accesses582;
          // fe XORs its current raw byte; other values overwrite without a read.
          const selector = readByte(record, 1);
          if (selector !== 255) {
            const start = startRecord(id);
            store(start, 'defaultSelector582', selector === 254 ? readByteField(start, 'defaultSelector582') ^ 1 : selector);
          }
        } else {
          if (!(mask & 2)) continue;
          requireCompleteSourceActorAnimationTransition(actor.source); actor.stateCommandsUsed = true;
          store(actor.parts[1]!, 'state1b', readByte(record, 1));
          store(actor.parts[1]!, 'auxiliary1c', readByte(record, 2));
          const operand = (): number => readByte(record, 6) * 256 + readByte(record, 7);
          if (operand() !== 0xffff) {
            const actual = actualActor(id);
            store(actual, 'controlWord', (readWord(actual, 'controlWord') & 0xfffff00f) >>> 0);
            // c4c4 reloads the halfword, then c4c8 reloads the now-current5e0.
            // Preserve both observable stores, including a failing second one.
            const reloaded = operand(), current = readWord(actual, 'controlWord');
            store(actual, 'controlWord', (current | (reloaded & 0x0ff0)) >>> 0);
          }
        }
        continue;
      }
      if (opcode !== 0x10) fail('unsupported zz_004c050_ opcode');
      const record = cursor, position = ownedCursor(record);
      // Source advances its local cursor before the handler reads record+2.
      // Controls remain untouched until terminal opcode0 installation below.
      cursor = intern(position.stream, position.offset + 4);
      const mode = readByte(record, 2);
      if (mode !== 1 && mode !== 2) fail('unsupported opcode0x10 mode');
      for (let i = 0; i < 4; i++) {
        if (!(mask & (1 << i))) continue;
        const operand = readByte(record, 3);
        if (mode === 1) {
          // Archived ProgramDB 80437140 = 2^52 makes CONCAT44/subtraction exactly u8;
          // every value is exactly f32. This conversion does not use GQR5.
          const target = invoke(targetGet, targets, [id, i]) as object;
          write(target, 'accumulator10', operand);
        } else if (operand >= 1 && operand <= 3) {
          const shared = invoke(feedbackGet, feedback, [partId(id, i)]) as object;
          // Clear/set overwrite stale values without reading/validating them.
          write(shared, 'mirror30', operand === 3 ? byte(shared, 'mirror30') ^ 1 : operand - 1);
        }
      }
    }
    if (!setupCompleted) for (let i = 0; i < 4; i++) if (mask & (1 << i)) fallback(id, i);
    const {stream, offset} = ownedCursor(cursor), next = intern(stream, offset + 4);
    for (let i = 0; i < 4; i++) {
      if (!(mask & (1 << i))) continue;
      const part = actor.parts[i]!;
      write(part, 'current00', cursor);
      write(part, 'next04', next);
      const raw = readByte(cursor, 2) * 256 + readByte(cursor, 3);
      write(part, 'wait14', raw >= 0x8000 ? raw - 0x10000 : raw);
      write(part, 'finished1a', 0);
    }
  };
  const reset = (id: symbol, index: number): void => {
    const part = actorRecord(id).parts[index]!;
    const target = invoke(targetGet, targets, [id, index]) as object;
    write(target, 'previous0c', 0);
    write(target, 'accumulator10', 0);
    write(target, 'target08', 0);
    write(part, 'status1d', 0);
    write(part, 'event1e', 0);
    write(part, 'next04', null);
    write(part, 'current00', null);
    write(part, 'wait14', 0);
    write(part, 'finished1a', 0);
  };
  const runtime: SourceStreamWaitRuntime = Object.freeze({
    bindActualActor(id: symbol, movement: SourceActorMovementFollowupRuntime): void {
      enter(); try {
        const actor = actorRecord(id);
        if (actor.actual !== undefined) fail('actual actor is already bound');
        if (!isSourceActorJointMappingRuntime(mapping) || !isSourceActorMovementFollowupRuntime(movement))
          fail('genuine mapping and movement runtimes required');
        if (movement.getMappingActor(id) !== actor.source || movement.getWaitBinding(id) !== actor.binding ||
            invoke(actorGet, mapping, [id]) !== actor.source) fail('matched canonical mapping and wait owners required');
        const actual = movement.getActualActor(id);
        if (actual === null || typeof actual !== 'object') fail('actual RomActor data record required');
        if (assignedActualActors.has(actual)) fail('actual actor already assigned to a stream identity');
        requireCompleteSourceActorDoubleLifecycle(actual); requireCompleteSourceActorAnimationTransition(actor.source);
        actor.actual = actual; actor.movement = movement; assignedActualActors.add(actual);
      } finally {busy = false;}
    },
    hasActualActorBinding(id: symbol) {return actorRecord(id).actual !== undefined;},
    getActualActor(id: symbol) {
      const actual = actorRecord(id).actual;
      if (actual === undefined) fail('genuine movement actual-actor join required');
      return actual;
    },
    getMappingActor(id: symbol) {return actorRecord(id).source;},
    bindStartActor(id: symbol, initial: Readonly<SourceStreamWaitStartBinding>): void {
      enter(); try {
        actorRecord(id);
        if (starts.has(id)) fail('start is already bound');
        const familyBank1d80 = bankPointer(initial, 'familyBank1d80'), sharedBank1d84 = bankPointer(initial, 'sharedBank1d84');
        const defaultSelector582 = byte(initial, 'defaultSelector582'), marker709 = byte(initial, 'marker709');
        starts.set(id, Object.seal({familyBank1d80, sharedBank1d84, defaultSelector582, marker709}));
      } finally {busy = false;}
    },
    getStartActorBinding: startRecord,
    startStream(id: symbol, mask: number, selector: number, actionIndex: number, startFrame = -1, transition = 0xffffffff, mode = 0xffffffff): void {
      enter(); try {sourceOperation(id, () => {
        // Argument-domain checks are host admission, not emulated source instructions.
        integer(mask, 0xffffffff, 'mask'); integer(selector, 0xffffffff, 'selector');
        if (!Number.isInteger(actionIndex) || actionIndex < -0x80000000 || actionIndex > 0x7fffffff) fail('actionIndex: signed32 integer required');
        const actor = actorRecord(id), start = startRecord(id);
        const effective = (mask & ((byte(actor.binding, 'activeMask579') << 24) >> 24)) >>> 0;
        if (effective & 2) write(start, 'marker709', 0);
        const shared = (selector & 0x80) !== 0;
        const bank = bankPointer(start, shared ? 'sharedBank1d84' : 'familyBank1d80');
        if (bank === null) {
          for (let i = 0; i < 4; i++) {reset(id, i); write(actor.parts[i]!, 'finished1a', 1);}
          return;
        }
        // Choose the bank before substitution; a default with bit7 set stays family.
        if (!shared && selector === 0) selector = ((byte(start, 'defaultSelector582') << 24) >> 24) >>> 0;
        const group = relativeCursor(bank, signedOffset(relativeCursor(bank, (shared ? selector & 0x7f : selector) << 1)));
        const displacement = signedOffset(relativeCursor(group, actionIndex << 1));
        const stream = relativeCursor(group, displacement);
        for (let i = 0; i < 4; i++) if (effective & (1 << i)) {
          write(actor.parts[i]!, 'group18', selector & 255);
          write(actor.parts[i]!, 'action19', actionIndex & 255);
          reset(id, i);
        }
        // Resolve the pointer before stores (archived bfbc); parse after all resets.
        parse(id, effective, stream, startFrame, transition, mode);
      });} finally {busy = false;}
    },
    createStream(bytes: Uint8Array): symbol {
      enter(); try {
        // Intrinsic accessors and set bypass caller overrides and reject proxies.
        const typed = Object.getPrototypeOf(Uint8Array.prototype) as object;
        const tag = Reflect.apply(Object.getOwnPropertyDescriptor(typed, Symbol.toStringTag)!.get!, bytes, []);
        if (tag !== 'Uint8Array') fail('stream requires a non-shared Uint8Array');
        const buffer = Reflect.apply(Object.getOwnPropertyDescriptor(typed, 'buffer')!.get!, bytes, []);
        try {Reflect.apply(Object.getOwnPropertyDescriptor(ArrayBuffer.prototype, 'byteLength')!.get!, buffer, []);}
        catch {fail('stream requires a non-shared Uint8Array');}
        const length = Reflect.apply(Object.getOwnPropertyDescriptor(typed, 'length')!.get!, bytes, []) as number;
        if (length > 16 * 1024 * 1024) fail('stream exceeds 16MiB host cap');
        const copy = new Uint8Array(length);
        Reflect.apply(Uint8Array.prototype.set, copy, [bytes]);
        const stream: Stream = {bytes: copy, cursors: new Map()};
        const base = intern(stream, 0); streams.set(base, stream); return base;
      } finally {busy = false;}
    },
    cursorAt(base: symbol, offset: number): symbol {
      enter(); try {
        const stream = streams.get(base); if (!stream) fail('owned stream base required');
        return intern(stream, offset);
      } finally {busy = false;}
    },
    cursorOffset(base: symbol, cursor: symbol): number {
      const stream = streams.get(base), found = ownedCursor(cursor);
      if (!stream || stream !== found.stream) fail('cursor does not belong to stream base');
      return found.offset;
    },
    parseWaitRecord(id: symbol, mask: number, cursor: symbol, startFrame = -1, transition = 0xffffffff, mode = 0xffffffff): void {
      enter(); try {sourceOperation(id, () => parse(id, mask, cursor, startFrame, transition, mode));} finally {busy = false;}
    },
    createCommand(initial: Readonly<SourceStreamWaitCommand>): symbol {
      enter(); try {const flags01 = byte(initial, 'flags01'), id = Symbol('stream command'); commands.set(id, Object.seal({flags01})); return id;} finally {busy = false;}
    },
    getCommand,
    bindActor(id: symbol, initial: Readonly<SourceStreamWaitActorInitial>, inputs: readonly Readonly<SourceStreamWaitPartInitial>[]): void {
      enter(); try {
        if (actors.has(id)) fail('actor is already bound');
        const source = invoke(actorGet, mapping, [id]) as SourceActorJointMappingHeader;
        const activeMask579 = byte(initial, 'activeMask579'), blockedMask1d9a = byte(initial, 'blockedMask1d9a');
        const marker71d = Object.getOwnPropertyDescriptor(initial, 'marker71d') === undefined ? 0 : byte(initial, 'marker71d');
        if (!Array.isArray(inputs) || own(inputs, 'length') !== 4) fail('exactly four stream parts required');
        const parts: SourceStreamWaitPartBinding[] = [];
        for (let i = 0; i < 4; i++) {
          const input = own(inputs, String(i)) as object, current00 = own(input, 'current00');
          if (current00 !== null) {if (typeof current00 !== 'symbol') fail('current00: owned command identity required');}
          const nextProperty = Object.getOwnPropertyDescriptor(input, 'next04');
          const next04 = nextProperty === undefined ? null : own(input, 'next04');
          if (next04 !== null && typeof next04 !== 'symbol') fail('next04: cursor identity required');
          const wait14 = readFloat(input, 'wait14'), finished1a = byte(input, 'finished1a'), event1e = byte(input, 'event1e');
          // Compatibility fixture defaults only, not evidence of source allocation state.
          const optionalByte = (key: string): number => Object.getOwnPropertyDescriptor(input, key) === undefined ? 0 : byte(input, key);
          const group18 = optionalByte('group18'), action19 = optionalByte('action19'), status1d = optionalByte('status1d');
          const initializedByte = (key: string): number | undefined =>
            Object.getOwnPropertyDescriptor(input, key) === undefined ? undefined : byte(input, key);
          const state1b = initializedByte('state1b'), auxiliary1c = initializedByte('auxiliary1c');
          parts.push(Object.seal({current00, next04, wait14, finished1a, event1e, group18, action19, status1d, state1b, auxiliary1c}));
        }
        actors.set(id, {source, binding: Object.seal({activeMask579, blockedMask1d9a, marker71d}), parts: Object.freeze(parts)});
      } finally {busy = false;}
    },
    getActorBinding(id: symbol) {return actorRecord(id).binding;},
    getPartBinding(id: symbol, index: number) {const actor = actorRecord(id); integer(index, 3, 'index'); return actor.parts[index]!;},
    update(id: symbol, mask: number): 0 | 1 {
      enter(); try {return sourceOperation(id, () => {
        integer(mask, 0xffffffff, 'mask');
        const actor = actorRecord(id), active = byte(actor.binding, 'activeMask579');
        if (own(actor.parts[0]!, 'current00') === null) {
          for (const part of actor.parts) write(part, 'finished1a', 1);
          return 1;
        }
        let result: 0 | 1 = 0;
        for (let i = 0; i < 4; i++) {
          if (!(mask & active & (1 << i))) continue;
          const part = actor.parts[i]!;
          write(part, 'event1e', 0);
          if (byte(actor.binding, 'blockedMask1d9a') & (1 << i)) {animate(id, i); continue;}
          if (byte(part, 'finished1a') !== 0) {
            result = 1;
            const shared = invoke(dispatchGet, dispatch, [partId(id, i)]) as object;
            if (byte(shared, 'linked36') === 1) animate(id, i);
            continue;
          }
          const flags = commandFlags(part);
          let met: boolean;
          if (flags & 8) {
            const wait = readFloat(part, 'wait14'), timestep = readFloat(actor.source, 'timestep1dc8');
            const next = Math.fround(wait - timestep); f32(next, 'wait14 result'); write(part, 'wait14', next);
            if (readFloat(part, 'wait14') > 0) continue;
            write(part, 'wait14', 0); met = true;
          } else {
            if (flags & 2) {
              const wait = readFloat(part, 'wait14');
              let threshold = wait, shared: object;
              if (wait < 0) {
                requireDurationProfile();
                shared = invoke(feedbackGet, feedback, [partId(id, i)]) as object;
                threshold = Math.fround(signedDuration(shared) + wait);
                f32(threshold, 'relative threshold result');
                if (threshold < 0) threshold = 0;
              } else shared = invoke(feedbackGet, feedback, [partId(id, i)]) as object;
              met = threshold <= readFloat(shared, 'frame0c');
            } else if (flags & 4) {
              requireDurationProfile();
              const shared = invoke(feedbackGet, feedback, [partId(id, i)]) as object;
              const duration = signedDuration(shared), frame = readFloat(shared, 'frame0c');
              // Deliberate host narrowing of PPC zero/nonfinite behavior, after
              // both source operands. Two separate single-precision operations.
              if (duration === 0) fail('duration24: zero percentage divisor is unsupported');
              const quotient = Math.fround(frame / duration); f32(quotient, 'percentage quotient result');
              const wait = readFloat(part, 'wait14');
              const percent = Math.fround(100 * quotient); f32(percent, 'percentage result');
              met = wait <= percent;
            } else {
              const wait = readFloat(part, 'wait14');
              if (wait >= 0) {
                const shared = invoke(dispatchGet, dispatch, [partId(id, i)]) as object;
                met = wait <= readFloat(shared, 'elapsed08');
              } else {
                const shared = invoke(feedbackGet, feedback, [partId(id, i)]) as object;
                met = ((byte(shared, 'complete2e') << 24) >> 24) > 0;
                if (!met && (flags & 1)) met = ((byte(shared, 'segment2d') << 24) >> 24) > 0;
              }
            }
            if (!met) {
              fallback(id, i);
              continue;
            }
          }
          if (!(commandFlags(part) & 1)) {
            const next = own(part, 'next04');
            if (typeof next !== 'symbol' || !cursors.has(next)) fail('unsupported zz_004c050_ continuation: owned byte next04 required');
            parse(id, 1 << i, next, -1, 0xffffffff, 0xffffffff);
            continue;
          }
          write(part, 'finished1a', 1); result = 1;
        }
        return result;
      });} finally {busy = false;}
    },
  });
  sourceStreamWaitRuntimes.add(runtime);
  return runtime;
}
