/** Inert Double Ninja render-child lifecycle, not a second combat actor.
 * 141a40/141b3c/141b90/141c30/141c6c: chunk_0037.c:2177–2286;
 * owner guard660e8: chunk_0008.c:2874–2896.
 * Original table8033af68:141b90,141c30,141c5c,141c6c.
 * 141c5c (omitted by C export): lbz18; addi1; stb18; blr.
 * Render resources, allocator and scheduler remain explicit host boundaries.
 * This child reads owner arm; actor-side reset/normalization policy is separate.
 */
export interface DoubleCloneOwner {
  borg3e8: number;
  invalid662: number;
  arm7c8: number;
}
export interface DoubleCloneAllocationSource {
  borg3e8: number;
  borg94: number;
  player96: number;
  /** Source actor90, not necessarily the allocating actor itself. */
  owner90: DoubleCloneOwner;
}
export interface DoubleCloneLifecycleState {
  readonly owner90: DoubleCloneOwner;
  readonly capturedBorg94: number;
  readonly capturedPlayer96: number;
  readonly variant11: number;
  phase18: number;
  visibility82: number;
}
export interface DoubleCloneLifecycleHooks {
  /** 141b90's model/resource setup. Called after phase18 becomes1. */
  initialize141b90(state: DoubleCloneLifecycleState): void;
  retire89444(state: DoubleCloneLifecycleState): void;
  retire8aff0(state: DoubleCloneLifecycleState): void;
  free88e50(state: DoubleCloneLifecycleState): void;
}
export type DoubleCloneLifecycleOutcome = {type:'continue'} | {type:'disposed'} |
  {type:'unsupported';phase:number};
const s8 = (n: number): number => (n << 24) >> 24;
const s16 = (n: number): number => (n << 16) >> 16;

/** Allocation request88aa0(actor,2,0,0,6). The hook supplies success only;
 * model pointers/copy fields are deliberately outside this lifecycle subset.
 * A successful fresh allocator entry starts at phase0. No arm is required.
 */
export function createDoubleCloneLifecycle(source: DoubleCloneAllocationSource,
  variant11: number, allocate88aa0: () => boolean): DoubleCloneLifecycleState | null {
  if (s16(source.borg3e8) !== 3 || !allocate88aa0()) return null;
  return {
    owner90:source.owner90, capturedBorg94:s16(source.borg94),
    capturedPlayer96:source.player96 & 0xff, variant11:variant11 & 0xff,
    phase18:0, visibility82:0,
  };
}

/** 660e8 does not re-retire an entry whose signed phase is already >1.
 * Returning true means the two invalidation hooks ran, not that dispatch ends.
 */
export function guardDoubleCloneOwner(state: DoubleCloneLifecycleState,
  hooks: DoubleCloneLifecycleHooks): boolean {
  const owner = state.owner90;
  if ((s8(owner.invalid662) === 0 && s16(owner.borg3e8) === s16(state.capturedBorg94)) ||
    s8(state.phase18) > 1) return false;
  state.phase18 = 2;
  state.visibility82 = 0;
  hooks.retire89444(state);
  hooks.retire8aff0(state);
  return true;
}

function updateVisibility(state: DoubleCloneLifecycleState): void {
  state.visibility82 = s8(state.owner90.arm7c8) !== 0 ? (state.capturedPlayer96 + 0x41) & 0xff : 0;
}

/** One141b3c dispatch: validate first, then dispatch the resulting phase.
 * Dispose means the caller must remove the child from scheduling, as88e50 does.
 * No HP, lifetime, action timer, independent borg or offset copy is introduced.
 * This module never writes owner arm/displacement; it does not model actor6f88c's
 * reset predicate or6f7c0's offset normalization.
 */
export function tickDoubleCloneLifecycle(state: DoubleCloneLifecycleState,
  hooks: DoubleCloneLifecycleHooks): DoubleCloneLifecycleOutcome {
  guardDoubleCloneOwner(state, hooks);
  switch (s8(state.phase18)) {
    case 0:
      state.phase18 = 1;
      hooks.initialize141b90(state);
      updateVisibility(state); // 141b90 calls141c30 in the same dispatch.
      return {type:'continue'};
    case 1:
      updateVisibility(state);
      return {type:'continue'};
    case 2:
      state.phase18 = (state.phase18 + 1) & 0xff; // 141c5c; no same-dispatch free.
      return {type:'continue'};
    case 3:
      hooks.free88e50(state);
      return {type:'disposed'};
    default: return {type:'unsupported',phase:s8(state.phase18)};
  }
}
