import type { BorgRuntime } from "./types.js";

/** Shared active actor (+0x508), not the enemy saved for Z release (+0x6e0).
 * zz_006bda8_ copies +0x508 to attack +0xcc (chunk_0009.c:1810-1811).
 * Preserve the existing fallback for legacy actors without an active target state.
 */
export function activeSourceTargetUid(b: BorgRuntime): string | null {
  return b.targetLockState?.activeTargetUid ?? b.lockTarget ?? null;
}

export function activeSourceTarget(b: BorgRuntime, all: readonly BorgRuntime[]): BorgRuntime | null {
  const uid = activeSourceTargetUid(b);
  const target = uid ? all.find((candidate) => candidate.uid === uid) : undefined;
  return target && target.uid !== b.uid && target.alive && target.hp > 0 && target.state !== "death"
    ? target
    : null;
}
