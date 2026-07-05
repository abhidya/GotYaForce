/**
 * getStorage — browser localStorage persistence for the Borg GET / Gotcha-Box drop pool
 * and the player's collected-drops log.
 *
 * PORT-ISM: the ROM persists the GET pool in the save file (GCI); the exact save-side
 * layout is undocumented (research/decomp/items-evidence-inventory-2026-07-05.md §4 —
 * "GET-pool save persistence layout ... GCI field unknown"). localStorage is this port's
 * stand-in persistence medium, following the same pattern SelectForce.ts already uses for
 * force-slot persistence (FORCE_SLOTS_STORAGE_KEY) — validated JSON parse, try/catch around
 * every localStorage call so private-mode/storage-disabled browsers degrade to in-memory-only
 * rather than throwing. The POOL SEMANTICS themselves (what's stored, how it resets) are
 * DERIVED from the doc, not invented here — see @gf/missions getSystem.ts.
 */

import { createGetPool, type GetDrop, type GetPool } from "@gf/missions";

const POOL_STORAGE_KEY = "gf-get-pool-v1";
const COLLECTION_STORAGE_KEY = "gf-get-collection-v1";

function isPoolEntryShaped(v: unknown): v is GetPool["entries"][number] {
  if (typeof v !== "object" || v === null) return false;
  const e = v as Record<string, unknown>;
  return typeof e["borgId"] === "string" && typeof e["colorVariant"] === "number" && typeof e["points"] === "number";
}

/** Load the persisted GET pool, or a fresh empty pool if none/invalid is stored. */
export function loadGetPool(): GetPool {
  try {
    const raw = window.localStorage.getItem(POOL_STORAGE_KEY);
    if (!raw) return createGetPool();
    const parsed: unknown = JSON.parse(raw);
    if (typeof parsed !== "object" || parsed === null || !Array.isArray((parsed as { entries?: unknown }).entries)) {
      return createGetPool();
    }
    const entries = (parsed as { entries: unknown[] }).entries.filter(isPoolEntryShaped);
    return { entries };
  } catch {
    return createGetPool();
  }
}

export function saveGetPool(pool: GetPool): void {
  try {
    window.localStorage.setItem(POOL_STORAGE_KEY, JSON.stringify(pool));
  } catch {
    // Storage may be unavailable (private mode); the in-memory pool still works this session.
  }
}

/** One collected drop record, kept for a simple "owned units / parts progress" log. */
export interface CollectedGetDrop extends GetDrop {
  /** Wall-clock ms timestamp when it was collected (display/debug only). */
  collectedAt: number;
}

function isCollectedDropShaped(v: unknown): v is CollectedGetDrop {
  if (typeof v !== "object" || v === null) return false;
  const d = v as Record<string, unknown>;
  return (
    typeof d["borgId"] === "string" &&
    typeof d["colorVariant"] === "number" &&
    (d["kind"] === "unit" || d["kind"] === "parts") &&
    typeof d["partIndex"] === "number" &&
    typeof d["collectedAt"] === "number"
  );
}

export function loadGetCollection(): CollectedGetDrop[] {
  try {
    const raw = window.localStorage.getItem(COLLECTION_STORAGE_KEY);
    if (!raw) return [];
    const parsed: unknown = JSON.parse(raw);
    if (!Array.isArray(parsed)) return [];
    return parsed.filter(isCollectedDropShaped);
  } catch {
    return [];
  }
}

export function saveGetCollection(collection: readonly CollectedGetDrop[]): void {
  try {
    window.localStorage.setItem(COLLECTION_STORAGE_KEY, JSON.stringify(collection));
  } catch {
    // Storage may be unavailable (private mode); the in-memory collection still works this session.
  }
}

/** Append newly rolled drops to the persisted collection log and save both stores. */
export function recordDrops(collection: CollectedGetDrop[], drops: readonly GetDrop[]): void {
  const now = Date.now();
  for (const drop of drops) collection.push({ ...drop, collectedAt: now });
  saveGetCollection(collection);
}
