/** Bounded chunk_0006.c:674–698 continuation with setup bit1 already selected, including
 * an optional bounded zz_0006f98 actor pose-pool prefix. Not full 8004adc8, opcode01,
 * asset parsing or production activation. Pose matrices are explicitly decoded
 * host input, copied into owned byte-offset storage, not fabricated ROM parsing.
 * Reads part+4 -> descriptor+c, snapshots public count, then reads all three bind-pose translations at
 * index*0x30+0xc/1c/2c before branching on the unsigned comparison.
 * The four global loads belong only to the refused out-of-count branch. Out-of-count
 * reset/transform branches refuse. In-count does real archive name/address
 * lookup, reloading part/descriptor between them, real JObjAddAnim and existing
 * attached tail. Null public address is a real null attachment argument; the
 * existing tail admits a surviving old AObj or refuses its missing fallback.
 * Hydration explicitly binds an owned byte cursor to an actual owned AnimJoint,
 * never index-to-descriptor or an arbitrary callback that invents a result.
 * Own-data non-proxy records/adapters, copied sealed host bindings, captured
 * receivers, synchronous void effects and poisoned reentry are host bounds.
 * Pose displacement preserves PPC multiply modulo32; backing-coordinate addition
 * wrap is refused rather than inventing aliased RAM. Decoded tables are capped
 * at 349525 matrices (a 16MiB-equivalent host bound). Read-only operands are admitted; delegated stores keep their own checks.
 * The optional actor prefix owns only a separately bound live raw byte+97 and
 * checks actor identity through the actual mapping owner. Signed-byte arithmetic
 * derives 0x803bb4c0 + index*0xc30 modulo32. The once-bound copied pool covers
 * up to 128 nonnegative slots of exactly 65 matrices; other derived regions and
 * matrix addresses crossing a slot refuse as host ownership bounds.
 * Completed allocations/releases/writes survive any later refusal.
 */
import type {SourceArchivePublicRuntime} from './archive-public.js';
import type {SourceJObjAddAnimationRuntime} from './jobj-add-animation.js';
import type {SourceAttachedJointSetupRuntime} from './attached-joint-setup.js';
export interface SourceArchiveJointSetupDescriptor {archive0c: symbol}
export interface SourceArchiveJointSetupPart {descriptor04: symbol | null}
export interface SourceArchiveJointSetupPose {translation0c: number; translation1c: number; translation2c: number}
export interface SourceArchiveJointSetupActorPoseBinding {poseIndex97: number}
export interface SourceArchiveJointSetupSources {
  actors?: {getActor(actor: symbol): object};
  archives: Pick<SourceArchivePublicRuntime, 'getArchive' | 'getPublicName' | 'getPublicAddress' | 'cursorOffset'>;
  attachment: Pick<SourceJObjAddAnimationRuntime, 'getDescriptor' | 'addAnimation'>;
  tail: Pick<SourceAttachedJointSetupRuntime, 'continueAttachedSetupTail'>;
}
export interface SourceArchiveJointSetupRuntime {
  createDescriptor(initial: SourceArchiveJointSetupDescriptor): symbol;
  getDescriptor(id: symbol): SourceArchiveJointSetupDescriptor;
  bindPart(id: symbol, initial: SourceArchiveJointSetupPart): void;
  getPartBinding(id: symbol): SourceArchiveJointSetupPart;
  createPoseTable(matrices: readonly SourceArchiveJointSetupPose[]): symbol;
  getPoseTable(id: symbol): Record<number, number>;
  bindActorPoseIndex(actor: symbol, rawByte97: number): void;
  getActorPoseBinding(actor: symbol): SourceArchiveJointSetupActorPoseBinding;
  bindPosePool(tables: readonly symbol[]): void;
  setupActorJoint(actor: symbol, part: symbol, joint: symbol | null, index: number): void;
  bindAddress(base: symbol, address: symbol, descriptor: symbol): void;
  continueResolvedArchiveSetup(actor: symbol, part: symbol, joint: symbol | null, index: number, poses: symbol): void;
}
function fail(reason: string): never {throw Error(`[archive-joint-setup] ${reason}; offline execution aborted, prior effects are not rolled back`);}
function own(record: unknown, key: string): unknown {
  if (record === null || typeof record !== 'object') fail(`${key}: data record required`);
  const p = Object.getOwnPropertyDescriptor(record, key);
  if (!p || !('value' in p)) fail(`${key}: own data property required`);
  return p.value;
}
function id(value: unknown, where: string): symbol {if (typeof value !== 'symbol') fail(`${where}: owned symbol required`); return value;}
function uint(value: unknown, where: string): number {
  if (typeof value !== 'number' || !Number.isInteger(value) || value < 0 || value > 0xffffffff) fail(`${where}: uint32 required`);
  return value;
}
function float(value: unknown, where: string): number {
  if (typeof value !== 'number' || !Number.isFinite(value) || !Object.is(value, Math.fround(value))) fail(`${where}: finite float32 required`);
  return value;
}
function method(table: unknown, key: string): (...args: never[]) => unknown {
  const fn = own(table, key); if (typeof fn !== 'function') fail(`${key}: own data-function required`); return fn as (...args: never[]) => unknown;
}
export function createSourceArchiveJointSetupRuntime(sources: SourceArchiveJointSetupSources): SourceArchiveJointSetupRuntime {
  const archives = own(sources, 'archives'), attachment = own(sources, 'attachment'), tail = own(sources, 'tail');
  const archive = method(archives, 'getArchive'), name = method(archives, 'getPublicName'), address = method(archives, 'getPublicAddress');
  const offset = method(archives, 'cursorOffset'), descriptor = method(attachment, 'getDescriptor'), add = method(attachment, 'addAnimation');
  const finish = method(tail, 'continueAttachedSetupTail');
  const actorProperty = Object.getOwnPropertyDescriptor(sources, 'actors');
  const actors = actorProperty ? own(sources, 'actors') : undefined;
  const actorLookup = actors === undefined ? undefined : method(actors, 'getActor');
  const descriptors = new Map<symbol, SourceArchiveJointSetupDescriptor>(), parts = new Map<symbol, SourceArchiveJointSetupPart>();
  const poses = new Map<symbol, Record<number, number>>(), addresses = new Map<symbol, symbol>();
  const poseLengths = new Map<symbol, number>();
  const actorPoses = new Map<symbol, SourceArchiveJointSetupActorPoseBinding>();
  let pool: readonly symbol[] | undefined;
  let busy = false, poisoned = false;
  const enter = (): void => {if (busy) {poisoned = true; fail('same-runtime reentry is unsupported');} busy = true; poisoned = false;};
  const invoke = (table: unknown, fn: (...args: never[]) => unknown, args: unknown[], voidResult = false): unknown => {
    const result = Reflect.apply(fn, table, args);
    if (poisoned) fail('same-runtime reentry caught inside adapter');
    if (voidResult && result !== undefined) fail('effect must synchronously return void');
    return result;
  };
  const get = <T>(map: Map<symbol, T>, key: symbol, kind: string): T => {const value = map.get(key); if (!value) fail(`unknown/non-owned ${kind}`); return value;};
  const getDescriptor = (key: symbol) => get(descriptors, key, 'setup descriptor');
  const getPartBinding = (key: symbol) => get(parts, key, 'setup part');
  const resolveArchive = (part: symbol): symbol => id(own(getDescriptor(id(own(getPartBinding(part), 'descriptor04'), 'descriptor04')), 'archive0c'), 'archive0c');
  const byte = (value: unknown): number => {const n = uint(value, 'poseIndex97'); if (n > 255) fail('poseIndex97: byte required'); return n;};
  const getActorPoseBinding = (actor: symbol) => get(actorPoses, actor, 'actor pose binding');
  const ownedActor = (actor: symbol): void => {
    id(actor, 'actor'); if (!actorLookup) fail('actual actor ownership source required');
    const value = invoke(actors, actorLookup, [actor]);
    if (value === null || typeof value !== 'object') fail('actual owned actor required');
  };
  const continueSetup = (actor: symbol, part: symbol, joint: symbol | null, index: number, tableId: symbol, poolSlot: boolean): void => {
        const firstArchive = resolveArchive(part);
        uint(index, 'index');
        const count = uint(own(invoke(archives, archive, [firstArchive]), 'publicCount0c'), 'publicCount0c');
        const table = get(poses, tableId, 'pose table'), base = Math.imul(index, 0x30) >>> 0;
        if (poolSlot && base + 0x2c >= 0xc30) fail('pose matrix crosses owned pool slot');
        const readPose = (delta: number, where: string): void => {
          if (base + delta > 0xffffffff) fail('pose coordinate addition overflow');
          float(own(table, String(base + delta)), where);
        };
        // Values are consumed source loads even though supported tail needs no fallback.
        readPose(0xc, 'pose+0c');
        readPose(0x1c, 'pose+1c');
        readPose(0x2c, 'pose+2c');
        if (index >= count) fail('out-of-count reset/transform branch is unsupported');
        const publicName = invoke(archives, name, [firstArchive, index]);
        if (publicName !== null) id(publicName, 'public name');
        const secondArchive = resolveArchive(part);
        const publicAddress = invoke(archives, address, [secondArchive, publicName]);
        let anim: symbol | null = null;
        if (publicAddress !== null) {anim = addresses.get(id(publicAddress, 'public address')) ?? null;
          if (anim === null) fail('public address lacks explicit AnimJoint hydration binding');}
        invoke(attachment, add, [joint, anim], true);
        invoke(tail, finish, [actor, part, joint], true);
  };
  return Object.freeze({
    createDescriptor(initial: SourceArchiveJointSetupDescriptor): symbol {
      enter(); try {const archive0c = id(own(initial, 'archive0c'), 'archive0c');
        invoke(archives, archive, [archive0c]); const key = Symbol('archive setup descriptor');
        descriptors.set(key, Object.seal({archive0c})); return key;
      } finally {busy = false;}
    }, getDescriptor,
    bindPart(key: symbol, initial: SourceArchiveJointSetupPart): void {
      enter(); try {id(key, 'part'); if (parts.has(key)) fail('part already bound');
        const raw = own(initial, 'descriptor04');
        const descriptor04 = raw === null ? null : id(raw, 'descriptor04');
        if (descriptor04 !== null) getDescriptor(descriptor04);
        parts.set(key, Object.seal({descriptor04}));
      } finally {busy = false;}
    }, getPartBinding,
    createPoseTable(matrices: readonly SourceArchiveJointSetupPose[]): symbol {
      enter(); try {
        if (!Array.isArray(matrices)) fail('decoded pose array required');
        const length = uint(own(matrices, 'length'), 'pose count'), table: Record<number, number> = {};
        if (length > 349525) fail('decoded pose table exceeds host budget');
        for (let i = 0; i < length; i++) {
          const matrix = own(matrices, String(i));
          for (const [field, byte] of [['translation0c', 0xc], ['translation1c', 0x1c], ['translation2c', 0x2c]] as const) {
            table[i * 0x30 + byte] = float(own(matrix, field), field);
          }
        }
        const key = Symbol('decoded bind pose table'); poses.set(key, Object.seal(table)); poseLengths.set(key, length); return key;
      } finally {busy = false;}
    },
    getPoseTable(key: symbol): Record<number, number> {return get(poses, key, 'pose table');},
    bindActorPoseIndex(actor: symbol, rawByte97: number): void {
      enter(); try {
        if (actorPoses.has(actor)) fail('actor pose already bound');
        ownedActor(actor); const poseIndex97 = byte(rawByte97);
        actorPoses.set(actor, Object.seal({poseIndex97}));
      } finally {busy = false;}
    }, getActorPoseBinding,
    bindPosePool(tables: readonly symbol[]): void {
      enter(); try {
        if (pool !== undefined) fail('pose pool already bound');
        if (!Array.isArray(tables)) fail('decoded pose pool array required');
        const length = uint(own(tables, 'length'), 'pool count');
        if (length > 128) fail('pose pool exceeds signed positive slots');
        const copied: symbol[] = [];
        for (let i = 0; i < length; i++) {
          const key = id(own(tables, String(i)), 'pose table'); get(poses, key, 'pose table');
          if (poseLengths.get(key) !== 65) fail('pose pool requires complete 65-matrix blocks');
          copied.push(key);
        }
        pool = Object.freeze(copied);
      } finally {busy = false;}
    },
    setupActorJoint(actor: symbol, part: symbol, joint: symbol | null, index: number): void {
      enter(); try {
        ownedActor(actor);
        const raw = byte(own(getActorPoseBinding(actor), 'poseIndex97'));
        const signed = (raw << 24) >> 24;
        // zz_0006f98: extsb; mulli 0xc30; add fixed 0x803bb4c0.
        // Negative selectors are valid source arithmetic, but not owned by this
        // bounded nonnegative pool. Never alias them into a different slot.
        const sourceAddress = (0x803bb4c0 + Math.imul(signed, 0xc30)) >>> 0;
        const slot = pool?.[signed];
        if (slot === undefined) fail(`unowned pose pool region at ${sourceAddress.toString(16)}`);
        continueSetup(actor, part, joint, index, slot, true);
      } finally {busy = false;}
    },
    bindAddress(base: symbol, cursor: symbol, anim: symbol): void {
      enter(); try {
        id(base, 'byte base'); id(cursor, 'public address'); id(anim, 'AnimJoint descriptor');
        if (addresses.has(cursor)) fail('public address already bound');
        const byteOffset = invoke(archives, offset, [base, cursor]);
        if (typeof byteOffset !== 'number' || !Number.isSafeInteger(byteOffset) || byteOffset < 0) fail('invalid owned byte cursor offset');
        const actual = invoke(attachment, descriptor, [anim]);
        if (actual === null || typeof actual !== 'object') fail('actual owned AnimJoint descriptor required');
        addresses.set(cursor, anim);
      } finally {busy = false;}
    },
    continueResolvedArchiveSetup(actor: symbol, part: symbol, joint: symbol | null, index: number, tableId: symbol): void {
      enter(); try {
        continueSetup(actor, part, joint, index, tableId, false);
      } finally {busy = false;}
    },
  });
}
