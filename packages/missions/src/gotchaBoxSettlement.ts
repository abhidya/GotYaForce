import type { BattleDefeat } from "@gf/combat";

import {
  createGetPool,
  registerKill,
  rollDrops,
  snapshotPool,
  type GetColorVariant,
  type GetDrop,
  type GetPool,
} from "./getSystem.js";

export const GOTCHA_BOX_STATE_VERSION = 1 as const;

export interface CollectedGetDrop extends GetDrop {
  collectedAt: number;
}

/** The complete durable Gotcha-Box value. Adapters must save it as one value. */
export interface GotchaBoxState {
  version: typeof GOTCHA_BOX_STATE_VERSION;
  pool: GetPool;
  collection: CollectedGetDrop[];
}

export interface GotchaBoxPersistence {
  load(): GotchaBoxState;
  save(state: GotchaBoxState): void;
}

export interface GotchaBoxSettlement {
  /** Start a battle transaction. Throws if one is already active. */
  begin(): void;
  /** Commit a won battle and return its drops. Throws if no battle is active. */
  win(defeats: readonly BattleDefeat[]): GetDrop[];
  /** Restore the exact pre-battle pool for loss or abandon. */
  revert(): void;
}

export interface GotchaBoxSettlementOptions {
  persistence: GotchaBoxPersistence;
  rng: () => number;
  clock?: () => number;
  playerTeam?: number;
  victimTeam?: number;
}

export function createGotchaBoxState(): GotchaBoxState {
  return { version: GOTCHA_BOX_STATE_VERSION, pool: createGetPool(), collection: [] };
}

export function cloneGotchaBoxState(state: GotchaBoxState): GotchaBoxState {
  return {
    version: GOTCHA_BOX_STATE_VERSION,
    pool: snapshotPool(state.pool),
    collection: state.collection.map((drop) => ({ ...drop })),
  };
}

/** In-memory adapter with copy-in/copy-out isolation, suitable for sessions and tests. */
export function createMemoryGotchaBoxPersistence(
  initial: GotchaBoxState = createGotchaBoxState(),
): GotchaBoxPersistence {
  let stored = cloneGotchaBoxState(initial);
  return {
    load: () => cloneGotchaBoxState(stored),
    save: (state) => {
      stored = cloneGotchaBoxState(state);
    },
  };
}

/**
 * Owns the complete battle transaction. A win commits accrued pool progress even when no
 * drop rolls; loss and abandon share `revert` and restore the exact begin snapshot.
 */
export function createGotchaBoxSettlement(options: GotchaBoxSettlementOptions): GotchaBoxSettlement {
  const state = cloneGotchaBoxState(options.persistence.load());
  const clock = options.clock ?? Date.now;
  const playerTeam = options.playerTeam ?? 0;
  const victimTeam = options.victimTeam ?? 1;
  let preBattlePool: GetPool | null = null;

  function requireActive(): GetPool {
    if (preBattlePool === null) throw new Error("Gotcha-Box battle transaction is not active");
    return preBattlePool;
  }

  return {
    begin(): void {
      if (preBattlePool !== null) throw new Error("Gotcha-Box battle transaction is already active");
      preBattlePool = snapshotPool(state.pool);
    },

    win(defeats): GetDrop[] {
      requireActive();
      for (const defeat of defeats) {
        if (defeat.victimTeam !== victimTeam || defeat.killerTeam !== playerTeam) continue;
        registerKill(state.pool, defeat.borgId, normalizeColorVariant(defeat.colorVariant), options.rng);
      }

      const drops = rollDrops(state.pool, options.rng);
      if (drops.length > 0) {
        const collectedAt = clock();
        state.collection.push(...drops.map((drop) => ({ ...drop, collectedAt })));
      }
      options.persistence.save(state);
      preBattlePool = null;
      return drops;
    },

    revert(): void {
      const snapshot = requireActive();
      state.pool = snapshotPool(snapshot);
      options.persistence.save(state);
      preBattlePool = null;
    },
  };
}

function normalizeColorVariant(value: number): GetColorVariant {
  return Number.isInteger(value) && value >= 0 && value <= 5 ? value as GetColorVariant : 0;
}
