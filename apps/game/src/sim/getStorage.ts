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
/** Where an unreadable payload is parked before the empty state replaces it. */
export const GOTCHA_BOX_UNREADABLE_KEY = "gf-gotcha-box-v1.unreadable";
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
      // Guard clause: the first load owns the read; later loads serve the cache, which also
      // covers the no-storage case (the cache IS the session's state then).
      if (initialized || !storage) {
        initialized = true;
        return cloneState(cached);
      }
      initialized = true;
      try {
        cached = readState(storage);
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

/**
 * Read the persisted state: the current payload if it parses, otherwise the migrated legacy
 * pair, otherwise a fresh empty state.
 *
 * parseState is all-or-nothing (isPool/isCollection use .every, and the version is compared
 * exactly), so one malformed row -- or any future GOTCHA_BOX_STATE_VERSION bump -- discards
 * the whole collection and the next save() would write that empty state straight over it.
 * The original bytes are parked first so the loss stays recoverable.
 */
function readState(storage: StorageLike): GotchaBoxState {
  const current = storage.getItem(GOTCHA_BOX_STORAGE_KEY);
  let state: GotchaBoxState;
  if (current !== null) {
    const parsed = parseState(current);
    if (parsed) {
      state = parsed;
    } else {
      preserveUnreadable(storage, current);
      state = createGotchaBoxState();
    }
  } else {
    const legacy = parseLegacy(
      storage.getItem(LEGACY_POOL_STORAGE_KEY),
      storage.getItem(LEGACY_COLLECTION_STORAGE_KEY),
    );
    state = legacy ?? createGotchaBoxState();
    if (legacy) trySave(storage, legacy);
  }
  return state;
}

function defaultStorage(): StorageLike | null {
  try {
    return typeof window === "undefined" ? null : window.localStorage;
  } catch {
    return null;
  }
}

/** Keep the FIRST unreadable payload. A later failure must not overwrite it --
 *  the earliest copy is the one closest to the player's real collection. */
function preserveUnreadable(storage: StorageLike, raw: string): void {
  try {
    if (storage.getItem(GOTCHA_BOX_UNREADABLE_KEY) === null) {
      storage.setItem(GOTCHA_BOX_UNREADABLE_KEY, raw);
    }
  } catch {
    // Storage refused the backup; the session still continues on the empty state.
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
  let state: GotchaBoxState | null = null;
  try {
    const value: unknown = JSON.parse(raw);
    const valid =
      isRecord(value) &&
      value.version === GOTCHA_BOX_STATE_VERSION &&
      isPool(value.pool) &&
      isCollection(value.collection);
    if (valid) state = cloneState(value as unknown as GotchaBoxState);
  } catch {
    // Not JSON, or not our shape; the caller parks the bytes and starts empty.
  }
  return state;
}

function parseLegacy(poolRaw: string | null, collectionRaw: string | null): GotchaBoxState | null {
  // Guard clause: neither legacy key is present, so there is nothing to migrate.
  if (poolRaw === null && collectionRaw === null) return null;
  let state: GotchaBoxState | null = null;
  try {
    const pool: unknown = poolRaw === null ? { entries: [] } : JSON.parse(poolRaw);
    const collection: unknown = collectionRaw === null ? [] : JSON.parse(collectionRaw);
    if (isPool(pool) && isCollection(collection)) {
      state = cloneState({ version: GOTCHA_BOX_STATE_VERSION, pool, collection });
    }
  } catch {
    // Unparseable legacy payload; the caller starts from an empty state.
  }
  return state;
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
