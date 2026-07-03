// Status-effect runtime SHELL (ATK-010) — id/timer/immunity plumbing only. NO status has any
// gameplay effect yet; this module exists so future per-status tickets are data fills against
// an already-proven architecture, not new plumbing.
//
// ROM evidence (research/decomp/attack-mechanics-findings.md mechanic Q; behavior-notes.md
// (al)/(an) corrections folded in — the chunk_0003.c:6318 HP-increment is VAMPIRE LIFESTEAL,
// not a status/heal mechanism, and is deliberately NOT modeled here):
//   - Application: victim+0x71a = hitboxRecord[1] & 0x3f (chunk_0003.c:7641-7642); timer
//     victim+0x71c max-merged from record[4] (chunk_0003.c:7638-7639).
//   - Immunity gate: victim+0x5a0 (u32) bit N blocks status N; the same bit ALSO zeroes HP
//     damage for that hit (formula step 1, chunk_0004.c:6693-6699) — wired optionally via
//     damageFormula.ts's `victimStatusImmune` context param.
//   - Status-blocked flag: victim+0x5e0 & 0x20000000 (chunk_0003.c:7644-7649).
//   - Tick: victim+0x71c decrements 1/frame (chunk_0007.c:2881-2883); statusId clears at 0.
//
// OBSERVED_GUIDE (player-documented status catalog; see research/decomp/data/
// guide-anchors-movelist.json statusObservations — none of these are implemented here):
// freeze (mash-to-recover), poison/DoT, time stop, shrink/grow, aim-scramble, transform,
// slow field, speed buff/debuff, tether, position swap.

import type { BorgRuntime } from "./types.js";

/** Mask applied to any incoming status id — the ROM stores only the low 6 bits at +0x71a
 *  (chunk_0003.c:7641-7642). */
export const STATUS_ID_MASK = 0x3f;

/** Bit test against the victim's per-status immunity word (+0x5a0). Bit N gates status id N. */
function isImmune(victim: BorgRuntime, maskedId: number): boolean {
  if (maskedId === 0) return false;
  return (victim.statusImmunityMask & (1 << maskedId)) !== 0;
}

/**
 * Apply a status application record to `victim` (chunk_0003.c:7638-7651).
 *
 * - `statusId` is masked to 0x3f before anything else.
 * - Rejected entirely (no id/timer change) when the victim's immunity bit for the masked id
 *   is set.
 * - Otherwise the id is (re)written and the duration is MAX-MERGED with any timer already
 *   running — a shorter incoming duration never shortens an active status.
 *
 * Today's three archetype DamageRecords (melee/shot/special) carry no status bytes, so
 * combat.ts's applyHit always calls this with `statusId = 0` — the parameter exists so a
 * future per-move hit-record can plumb real ids/durations without touching this function.
 */
export function applyStatusFromRecord(victim: BorgRuntime, statusId: number, duration: number): void {
  const maskedId = statusId & STATUS_ID_MASK;
  if (maskedId === 0) return;
  if (isImmune(victim, maskedId)) return;

  victim.statusId = maskedId;
  victim.statusTimer = Math.max(victim.statusTimer, duration);
}

/** Per-frame status timer tick (chunk_0007.c:2881-2883): decrement 1/frame, clamp at 0, and
 *  clear the status id once the timer reaches 0. NO gameplay effect is applied while the
 *  status is active — render/debug code may read `statusId`/`statusTimer`, nothing else does. */
export function stepStatus(b: BorgRuntime): void {
  if (b.statusTimer <= 0) {
    b.statusTimer = 0;
    b.statusId = 0;
    return;
  }
  b.statusTimer -= 1;
  if (b.statusTimer <= 0) {
    b.statusTimer = 0;
    b.statusId = 0;
  }
}
