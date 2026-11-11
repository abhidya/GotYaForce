/** Battle-work copy of a saved force; never mutate or prune the saved roster.
 * Source: chunk_0047.c:2433-2436,2568-2602 reloads each human's budget,
 * copies at most 30 slots in order, and stops BEFORE the first overflow.
 * chunk_0056.c:680-718 supplies the read-only confirmation count.
 * Supported parity scope: dense browser IDs with known positive costs. Unknown,
 * nonpositive and nonfinite costs stop defensively, without claiming ROM parity
 * for malformed/sparse saves, variants, zero-cost slots or random forces.
 */
export function deriveForceDeployment(
  savedIds: readonly string[],
  budget: number,
  costs: ReadonlyMap<string, number>,
): { borgIds: string[]; cost: number } {
  const borgIds: string[] = [];
  let cost = 0;
  if (!Number.isFinite(budget) || budget < 0) return { borgIds, cost };
  for (const id of savedIds.slice(0, 30)) {
    const next = costs.get(id);
    if (next === undefined || !Number.isFinite(next) || next <= 0 || cost + next > budget) break;
    borgIds.push(id);
    cost += next;
  }
  return { borgIds, cost };
}
