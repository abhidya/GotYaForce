/** Atomic browser persistence for the complete Gotcha-Box state. */
import {
  GOTCHA_BOX_STATE_VERSION,
  createGotchaBoxState,
  type CollectedGetDrop,
  type GotchaBoxPersistence,
  type GotchaBoxState,
  type GetPool,
} from "@gf/missions";

export const GOTCHA_BOX_STORAGE_KEY = "gf-gotcha-box-v1";
const LEGACY_POOL_STORAGE_KEY = "gf-get-pool-v1";
const LEGACY_COLLECTION_STORAGE_KEY = "gf-get-collection-v1";

export interface StorageLike {
  getItem(key: string): string | null;
  setItem(key: string, value: string): void;
}

/**
 * Uses a cached state as the session fallback, so unavailable or failing storage never throws
 * and later commits remain visible to this adapter instance.
 */
export function createBrowserGotchaBoxPersistence(
  storage: StorageLike | null = defaultStorage(),
): GotchaBoxPersistence {
  let cached = createGotchaBoxState();
  let initialized = false;

  return {
    load(): GotchaBoxState {
      if (initialized) return cloneState(cached);
      initialized = true;
      if (!storage) return cloneState(cached);

      try {
        const current = storage.getItem(GOTCHA_BOX_STORAGE_KEY);
        if (current !== null) {
          cached = parseState(current) ?? createGotchaBoxState();
          return cloneState(cached);
        }

        const legacy = parseLegacy(
          storage.getItem(LEGACY_POOL_STORAGE_KEY),
          storage.getItem(LEGACY_COLLECTION_STORAGE_KEY),
        );
        if (legacy) {
          cached = legacy;
          trySave(storage, cached);
        }
      } catch {
        cached = createGotchaBoxState();
      }
      return cloneState(cached);
    },

    save(state): void {
      cached = cloneState(state);
      initialized = true;
      if (storage) trySave(storage, cached);
    },
  };
}

function defaultStorage(): StorageLike | null {
  try {
    return typeof window === "undefined" ? null : window.localStorage;
  } catch {
    return null;
  }
}

function trySave(storage: StorageLike, state: GotchaBoxState): void {
  try {
    storage.setItem(GOTCHA_BOX_STORAGE_KEY, JSON.stringify(state));
  } catch {
    // The adapter's cached copy continues the session when browser storage is unavailable.
  }
}

function parseState(raw: string): GotchaBoxState | null {
  try {
    const value: unknown = JSON.parse(raw);
    if (!isRecord(value) || value.version !== GOTCHA_BOX_STATE_VERSION) return null;
    if (!isPool(value.pool) || !isCollection(value.collection)) return null;
    return cloneState(value as unknown as GotchaBoxState);
  } catch {
    return null;
  }
}

function parseLegacy(poolRaw: string | null, collectionRaw: string | null): GotchaBoxState | null {
  if (poolRaw === null && collectionRaw === null) return null;
  try {
    const pool: unknown = poolRaw === null ? { entries: [] } : JSON.parse(poolRaw);
    const collection: unknown = collectionRaw === null ? [] : JSON.parse(collectionRaw);
    if (!isPool(pool) || !isCollection(collection)) return null;
    return cloneState({ version: GOTCHA_BOX_STATE_VERSION, pool, collection });
  } catch {
    return null;
  }
}

function isPool(value: unknown): value is GetPool {
  return isRecord(value) && Array.isArray(value.entries) && value.entries.every((entry) =>
    isRecord(entry) &&
    typeof entry.borgId === "string" &&
    isIntegerInRange(entry.colorVariant, 0, 5) &&
    isIntegerInRange(entry.points, 0, 65535)
  );
}

function isCollection(value: unknown): value is CollectedGetDrop[] {
  return Array.isArray(value) && value.every((drop) =>
    isRecord(drop) &&
    typeof drop.borgId === "string" &&
    isIntegerInRange(drop.colorVariant, 0, 5) &&
    typeof drop.collectedAt === "number" && Number.isFinite(drop.collectedAt) &&
    (
      (drop.kind === "unit" && drop.partIndex === 0 && drop.partsCount === undefined) ||
      (drop.kind === "parts" &&
        typeof drop.partsCount === "number" && Number.isInteger(drop.partsCount) &&
        drop.partsCount >= 2 && drop.partsCount <= 5 &&
        typeof drop.partIndex === "number" && Number.isInteger(drop.partIndex) &&
        drop.partIndex >= 1 && drop.partIndex <= drop.partsCount)
    )
  );
}

function isIntegerInRange(value: unknown, min: number, max: number): value is number {
  return typeof value === "number" && Number.isInteger(value) && value >= min && value <= max;
}

function isRecord(value: unknown): value is Record<string, unknown> {
  return typeof value === "object" && value !== null;
}

function cloneState(state: GotchaBoxState): GotchaBoxState {
  return {
    version: GOTCHA_BOX_STATE_VERSION,
    pool: { entries: state.pool.entries.map((entry) => ({ ...entry })) },
    collection: state.collection.map((drop) => ({ ...drop })),
  };
}
