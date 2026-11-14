/** Bounded offline scalar receiver of JObjUpdateFunc (8024e120), with actual
 * HSD_JObjSetMtxDirtySub (80251b80) flag writes. Source: chunk_0071.c:4367–4864,
 * 7391–7581; original-DOL audit in double-source-owned-dispatch-plan-2026-11-12.md.
 * Only tracks 1/2/3, 5/6/7 and 8/9/10 are admitted. Rotation requires nonquaternion
 * flags; track1's RObj branch is excluded, not stubbed. All other tracks are
 * outside this host domain, including retail no-ops and track4's scalar alias.
 * Explicit setFlags/clearFlags and All variants additionally model 802502dc,
 * 80250378, 80250650, 802506ec (chunk_0071.c:6306–6689). These helpers do not
 * admit scalar tracks 11/12: their threshold constant remains unresolved.
 * No matrices, geometry, AObj/path/RObj fields, original replay or live wiring.
 *
 * All nine transform scalars must be supplied as finite f32, including signed
 * zero and subnormals. These lfs/stfs copies perform no FP arithmetic; composed
 * FObj/AObj helpers retain their separate arithmetic assumptions. Headers are
 * factory-owned, sealed data records, never aliased RAM.
 * Symbols are explicit owner/link identities, not pointers. updateScalar is a
 * synchronous FObj scalar handler with no delegated effects or user callbacks.
 * Null owner returns before inspecting any other arguments.
 *
 * Host validation precedes the root scalar write; then the source writes that
 * scalar before dirty propagation. Each encountered descendant is validated
 * only when reached, before its flag test/write. Links are resolved only when
 * followed: no root sibling, no pruned child, and no skipped child's subtree.
 * Invalid/unwritable scalar fields are host refusals even on an examined child
 * that the source would skip. Link values may be edited but are checked lazily.
 * Cycles/revisits and a finite inspected-node budget (including root and skipped
 * children) are host refusals, not retail semantics. Failures retain the scalar
 * and all earlier dirty writes. There is no whole-graph preflight or rollback.
 */
import type {SourceFObjScalarHandler} from './fobj-callback.js';

export interface SourceJObjScalarHeader {
  sibling08: symbol | null;
  child10: symbol | null;
  flags14: number;
  rotation1c: number;
  rotation20: number;
  rotation24: number;
  scale2c: number;
  scale30: number;
  scale34: number;
  translation38: number;
  translation3c: number;
  translation40: number;
}
export interface SourceJObjScalarRuntime {
  createJoint(initial: SourceJObjScalarHeader): symbol;
  getJoint(identity: symbol): SourceJObjScalarHeader;
  /** Check owned header/scalars; link targets are checked only when followed. */
  validateJoint(header: SourceJObjScalarHeader): void;
  updateScalar: SourceFObjScalarHandler;
  setFlags(joint: symbol | null, mask: number): void;
  clearFlags(joint: symbol | null, mask: number): void;
  setFlagsAll(joint: symbol | null, mask: number): void;
  clearFlagsAll(joint: symbol | null, mask: number): void;
}
const scalars = ['rotation1c', 'rotation20', 'rotation24', 'scale2c', 'scale30',
  'scale34', 'translation38', 'translation3c', 'translation40'] as const;
const keys = ['sibling08', 'child10', 'flags14', ...scalars] as const;
type Scalar = typeof scalars[number];
function fail(reason: string): never {
  throw Error(`[jobj-update] ${reason}; offline execution aborted, prior writes are not rolled back`);
}
function float32(value: number, where: string): void {
  if (!Number.isFinite(value) || !Object.is(value, Math.fround(value))) fail(`${where}: expected finite source float32`);
}
function link(value: unknown): void {
  if (value !== null && typeof value !== 'symbol') fail('expected opaque joint symbol or null');
}
function logicallyDirty(flags: number): boolean {
  return (flags & 0x00800000) === 0 && (flags & 0x40) !== 0;
}
function scalarForTrack(track: number): Scalar {
  switch (track) {
    case 1: return 'rotation1c';
    case 2: return 'rotation20';
    case 3: return 'rotation24';
    case 5: return 'translation38';
    case 6: return 'translation3c';
    case 7: return 'translation40';
    case 8: return 'scale2c';
    case 9: return 'scale30';
    case 10: return 'scale34';
    default: fail('unsupported scalar track');
  }
}
/** maxNodes bounds nodes examined in one dirty traversal, not allocation or
 * retail subtree depth. A child skipped by source flags still consumes budget.
 * maxFlagNodes independently bounds root plus visited nodes per All call; each
 * nested dirtySub has its own fresh maxNodes budget and revisit set. Flag calls
 * validate whole owned headers, including finite/writable scalars, when reached.
 * Dirty writes precede the final mask store; failures preserve that exact prefix.
 * All walks prune on POST-store 0x1000, never follow the root sibling, and read
 * child siblings only after their subtree finishes. Consumed links are lazy.
 * These are sealed data records, not memory proxies or source callback hooks.
 */
export function createSourceJObjScalarRuntime(maxNodes = 4096, maxFlagNodes = 4096): SourceJObjScalarRuntime {
  if (!Number.isSafeInteger(maxNodes) || maxNodes < 1) fail('maxNodes must be a positive safe integer');
  if (!Number.isSafeInteger(maxFlagNodes) || maxFlagNodes < 1) fail('maxFlagNodes must be a positive safe integer');
  const joints = new Map<symbol, SourceJObjScalarHeader>();
  const headers = new WeakSet<SourceJObjScalarHeader>();
  const getJoint = (identity: symbol): SourceJObjScalarHeader => {
    const joint = joints.get(identity);
    if (!joint) fail('unknown/non-owned joint identity');
    return joint;
  };
  const validateJoint = (joint: SourceJObjScalarHeader): void => {
    if (!headers.has(joint)) fail('non-owned joint header');
    for (const key of keys) {
      if (!Object.getOwnPropertyDescriptor(joint, key)?.writable) fail(`${key}: non-writable scalar field`);
    }
    if (!Number.isInteger(joint.flags14) || joint.flags14 < 0 || joint.flags14 > 0xffffffff) fail('flags14: expected uint32');
    for (const key of scalars) float32(joint[key], key);
  };
  const dirtySub = (rootId: symbol, root: SourceJObjScalarHeader): void => {
    const seen = new Set<symbol>([rootId]);
    root.flags14 = (root.flags14 | 0x40) >>> 0;
    if ((root.flags14 & 0x1000) !== 0) return;
    // Keep entered ancestors, not snapshots of their sibling links. The root
    // is deliberately absent: its own sibling is never part of this subtree.
    const ancestors: SourceJObjScalarHeader[] = [];
    let current = root.child10;
    for (;;) {
      if (current === null) {
        if (ancestors.length === 0) return;
        current = ancestors.pop()!.sibling08;
        continue;
      }
      link(current);
      if (seen.has(current)) fail('cycle/revisited joint is unsupported');
      if (seen.size >= maxNodes) fail('inspected-node budget exhausted');
      const joint = getJoint(current);
      validateJoint(joint);
      seen.add(current);
      if ((joint.flags14 & 0x01000000) === 0 && !logicallyDirty(joint.flags14)) {
        joint.flags14 = (joint.flags14 | 0x40) >>> 0;
        if ((joint.flags14 & 0x1000) === 0) {
          ancestors.push(joint);
          current = joint.child10;
          continue;
        }
      }
      current = joint.sibling08;
    }
  };
  const flags = (rootId: symbol | null, mask: number, clear: boolean, all: boolean): void => {
    if (rootId === null) return;
    const root = getJoint(rootId);
    validateJoint(root);
    if (!Number.isInteger(mask) || mask < 0 || mask > 0xffffffff) fail('mask: expected uint32');
    const apply = (id: symbol, joint: SourceJObjScalarHeader): void => {
      // Both source helpers use oldFlags XOR mask, NOT old XOR resulting flags.
      // In particular mask zero can dirty, and clearing an existing 8 need not.
      if (((joint.flags14 ^ mask) & 8) !== 0 && !logicallyDirty(joint.flags14)) dirtySub(id, joint);
      // Reload after dirtySub: its writes must survive unless explicitly masked.
      joint.flags14 = (clear ? joint.flags14 & ~mask : joint.flags14 | mask) >>> 0;
    };
    apply(rootId, root);
    if (!all || (root.flags14 & 0x1000) !== 0) return;
    const seen = new Set<symbol>([rootId]);
    const ancestors: SourceJObjScalarHeader[] = [];
    let current = root.child10;
    for (;;) {
      if (current === null) {
        if (ancestors.length === 0) return;
        current = ancestors.pop()!.sibling08;
        continue;
      }
      link(current);
      if (seen.has(current)) fail('flag traversal cycle/revisited joint is unsupported');
      if (seen.size >= maxFlagNodes) fail('flag inspected-node budget exhausted');
      const joint = getJoint(current);
      validateJoint(joint);
      seen.add(current);
      apply(current, joint);
      if ((joint.flags14 & 0x1000) === 0) {
        ancestors.push(joint);
        current = joint.child10;
      } else {
        current = joint.sibling08;
      }
    }
  };
  return {
    createJoint(initial) {
      if (initial === null || typeof initial !== 'object') fail('initial joint data record required');
      // Copy only own data properties, without retaining input or invoking its
      // accessors. All fields are explicit; there are no guessed transform defaults.
      const copied: Partial<SourceJObjScalarHeader> = {};
      for (const key of keys) {
        const property = Object.getOwnPropertyDescriptor(initial, key);
        if (!property || !('value' in property)) fail(`${key}: initial own data property required`);
        Object.defineProperty(copied, key, {value: property.value, writable: true, enumerable: true});
      }
      const joint = Object.seal(copied) as SourceJObjScalarHeader;
      link(joint.sibling08); link(joint.child10);
      headers.add(joint);
      validateJoint(joint);
      const identity = Symbol('owned scalar JObj');
      joints.set(identity, joint);
      return identity;
    },
    getJoint,
    validateJoint,
    setFlags: (joint, mask) => flags(joint, mask, false, false),
    clearFlags: (joint, mask) => flags(joint, mask, true, false),
    setFlagsAll: (joint, mask) => flags(joint, mask, false, true),
    clearFlagsAll: (joint, mask) => flags(joint, mask, true, true),
    updateScalar(owner, track, value) {
      if (owner === null) return;
      const joint = getJoint(owner);
      validateJoint(joint);
      const field = scalarForTrack(track);
      float32(value, 'callback value');
      if (track >= 1 && track <= 3 && (joint.flags14 & 0x00020000) !== 0) fail('quaternion rotation is unsupported');
      if (track === 1 && (joint.flags14 & 0x00200000) !== 0) fail('track1 RObj write is unsupported');
      joint[field] = value;
      if ((joint.flags14 & 0x02000000) === 0 && !logicallyDirty(joint.flags14)) dirtySub(owner, joint);
    },
  };
}
