import type { ForceSlot } from "./ui/screens/SelectForce.js";

// ---------------------------------------------------------------------------
// Force-slot persistence (browser stand-in for the memory-card "BOX DATA").
//
// App startup restores slots before either editor route can modify them.
// Confirmed edits persist immediately, before navigation. SelectForce retains
// its mount sync for standalone callers and subsequent visits; the startup
// restore flag prevents stale storage from replacing edits on its first mount.
// ---------------------------------------------------------------------------

const FORCE_SLOTS_STORAGE_KEY = "gf-force-slots-v1";
/** Where an unreadable payload is parked before defaults overwrite it. */
export const FORCE_SLOTS_UNREADABLE_KEY = "gf-force-slots-v1.unreadable";
let restoredThisPageLoad = false;

/** Keep the FIRST unreadable payload; a later failure must not clobber the copy
 *  closest to the player's real forces. */
function preserveUnreadableForceSlots(raw: string): void {
  try {
    if (window.localStorage.getItem(FORCE_SLOTS_UNREADABLE_KEY) !== null) return;
    window.localStorage.setItem(FORCE_SLOTS_UNREADABLE_KEY, raw);
  } catch {
    // Storage refused the backup; the session still continues on the defaults.
  }
}

function loadStoredForceSlots(): ForceSlot[] | null {
  // Rejection is all-or-nothing: one bad entry discards every slot, and
  // syncForceSlots then writes the defaults straight over all 30 saved forces.
  // Park the original bytes first so that loss is recoverable.
  let raw: string | null = null;
  try {
    raw = window.localStorage.getItem(FORCE_SLOTS_STORAGE_KEY);
    if (!raw) return null;
    const parsed: unknown = JSON.parse(raw);
    if (!Array.isArray(parsed)) {
      preserveUnreadableForceSlots(raw);
      return null;
    }
    const slots: ForceSlot[] = [];
    for (const entry of parsed) {
      if (typeof entry !== "object" || entry === null) {
        preserveUnreadableForceSlots(raw);
        return null;
      }
      const slot = entry as Partial<ForceSlot>;
      if (typeof slot.no !== "number" || typeof slot.name !== "string" || !Array.isArray(slot.borgIds)) {
        preserveUnreadableForceSlots(raw);
        return null;
      }
      slots.push({
        no: slot.no,
        name: slot.name,
        borgIds: slot.borgIds.filter((id): id is string => typeof id === "string"),
      });
    }
    return slots;
  } catch {
    if (raw) preserveUnreadableForceSlots(raw);
    return null;
  }
}

export function saveForceSlots(slots: readonly { readonly no: number; readonly name: string; readonly borgIds: readonly string[] }[]): void {
  try {
    window.localStorage.setItem(FORCE_SLOTS_STORAGE_KEY, JSON.stringify(slots));
  } catch {
    // Storage may be unavailable (private mode); the in-memory slots still work.
  }
}

/** Restore once per page load, then persist on every later visit. */
export function syncForceSlots(slots: ForceSlot[]): void {
  if (!restoredThisPageLoad) {
    restoredThisPageLoad = true;
    const stored = loadStoredForceSlots();
    if (stored) {
      for (let i = 0; i < slots.length; i++) {
        const saved = stored.find((s) => s.no === slots[i]!.no);
        if (saved) slots[i] = { ...slots[i]!, name: saved.name, borgIds: [...saved.borgIds] };
      }
      return;
    }
  }
  saveForceSlots(slots);
}

