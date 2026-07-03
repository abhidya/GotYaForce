import { actionProfileForProfile, type PrimaryAttackKind } from "./actionProfiles.js";
import { moveByButton, moveProfileForBorgId, type BorgMove, type Penetration } from "./moveProperties.js";
import { sourceStatsForBorgId, type BorgSourceWeaponSlot } from "./sourceBorgStats.js";
import type { BorgProfile } from "./stats.js";

export type RuntimeMoveButton = "B Shot" | "B Attack" | "B Charge" | "X" | "X Charge";
export type RuntimeMoveAction = "shot" | "melee" | "shot-charge" | "special" | "special-charge";
export type RuntimeMoveCommandStatus =
  | "direct-b"
  | "contextual-b"
  | "charge-release"
  | "direct-x"
  | "x-charge-blocked";
export type RuntimeMoveHitboxStatus =
  | "projectile-radius"
  | "generic-melee-volume"
  | "generic-special-aoe"
  | "unmapped";

export interface RuntimeMoveAmmo {
  weaponSlot: 0 | 1 | null;
  currentLevel: number | null;
  current: number | null;
  lv1: number | null;
  lv10: number | null;
  refillType: number | null;
  refillParam: number | null;
}

export interface RuntimeMoveBinding {
  button: RuntimeMoveButton;
  move: BorgMove | null;
  action: RuntimeMoveAction;
  weaponSlot: 0 | 1 | null;
  ammo: RuntimeMoveAmmo;
  penetration: Penetration | null;
  commandStatus: RuntimeMoveCommandStatus;
  actionStatus: "profile-backed" | "profile-missing";
  hitboxStatus: RuntimeMoveHitboxStatus;
  exactHitbox: boolean;
}

const BUTTONS: readonly RuntimeMoveButton[] = ["B Shot", "B Attack", "B Charge", "X", "X Charge"];

export function usesContextualBResolver(id: string): boolean {
  return moveByButton(id, "B Shot") !== null && moveByButton(id, "B Attack") !== null;
}

export function runtimeShotPenetrationForBorgId(id: string, charged: boolean): Penetration | null {
  return runtimeMoveBindingForBorgId(id, charged ? "B Charge" : "B Shot")?.penetration ?? null;
}

export function runtimeMoveBindingForBorgId(id: string, button: RuntimeMoveButton): RuntimeMoveBinding | null {
  const move = moveByButton(id, button);
  if (!move) return null;
  return buildBinding(id, undefined, button, move, null);
}

export function runtimeMoveBindingsForProfile(profile: BorgProfile): RuntimeMoveBinding[] {
  const moveProfile = moveProfileForBorgId(profile.id);
  if (!moveProfile) return [];
  const actionProfile = actionProfileForProfile(profile);
  const seen = new Set<string>();
  const bindings: RuntimeMoveBinding[] = [];
  for (const button of BUTTONS) {
    const move = moveByButton(profile.id, button);
    if (!move || seen.has(button)) continue;
    seen.add(button);
    bindings.push(buildBinding(profile.id, profile.level, button, move, actionProfile));
  }
  return bindings;
}

export function runtimeMoveCoverage(): {
  borgsWithMoves: number;
  moves: number;
  contextualBProfiles: number;
} {
  let borgsWithMoves = 0;
  let moves = 0;
  let contextualBProfiles = 0;
  for (const id of allMoveProfileIds()) {
    const profile = moveProfileForBorgId(id);
    if (!profile) continue;
    borgsWithMoves += 1;
    moves += profile.moves.length;
    if (usesContextualBResolver(id)) contextualBProfiles += 1;
  }
  return { borgsWithMoves, moves, contextualBProfiles };
}

function allMoveProfileIds(): string[] {
  // moveProperties intentionally exposes coverage, not raw ids. This small loop keeps the
  // runtime overlay API self-contained without leaking the JSON schema from moveProperties.
  const known: string[] = [];
  for (let family = 0; family <= 0x0f; family += 1) {
    for (let idx = 0; idx <= 0xff; idx += 1) {
      const id = `pl${family.toString(16).padStart(2, "0")}${idx.toString(16).padStart(2, "0")}`;
      if (moveProfileForBorgId(id)) known.push(id);
    }
  }
  return known;
}

function buildBinding(
  id: string,
  level: number | undefined,
  button: RuntimeMoveButton,
  move: BorgMove | null,
  actionProfile: ReturnType<typeof actionProfileForProfile> | null,
): RuntimeMoveBinding {
  const action = actionForButton(button);
  const weaponSlot = weaponSlotForButton(button);
  return {
    button,
    move,
    action,
    weaponSlot,
    ammo: ammoFor(id, level, weaponSlot),
    penetration: move?.penetration ?? null,
    commandStatus: commandStatusForButton(id, button),
    actionStatus: actionProfile ? actionStatusFor(actionProfile, action) : "profile-backed",
    hitboxStatus: hitboxStatusForAction(action),
    exactHitbox: false,
  };
}

function actionForButton(button: RuntimeMoveButton): RuntimeMoveAction {
  if (button === "B Shot") return "shot";
  if (button === "B Attack") return "melee";
  if (button === "B Charge") return "shot-charge";
  if (button === "X Charge") return "special-charge";
  return "special";
}

function weaponSlotForButton(button: RuntimeMoveButton): 0 | 1 | null {
  if (button === "B Shot" || button === "B Charge") return 0;
  if (button === "X" || button === "X Charge") return 1;
  return null;
}

function commandStatusForButton(id: string, button: RuntimeMoveButton): RuntimeMoveCommandStatus {
  if (button === "B Shot" || button === "B Attack") return usesContextualBResolver(id) ? "contextual-b" : "direct-b";
  if (button === "B Charge") return "charge-release";
  if (button === "X Charge") return "x-charge-blocked";
  return "direct-x";
}

function actionStatusFor(
  profile: ReturnType<typeof actionProfileForProfile>,
  action: RuntimeMoveAction,
): "profile-backed" | "profile-missing" {
  if (action === "melee") return profile.melee ? "profile-backed" : "profile-missing";
  if (action === "shot" || action === "shot-charge") return profile.shot ? "profile-backed" : "profile-missing";
  return profile.special ? "profile-backed" : "profile-missing";
}

function hitboxStatusForAction(action: RuntimeMoveAction): RuntimeMoveHitboxStatus {
  if (action === "shot" || action === "shot-charge") return "projectile-radius";
  if (action === "melee") return "generic-melee-volume";
  if (action === "special" || action === "special-charge") return "generic-special-aoe";
  return "unmapped";
}

function ammoFor(id: string, level: number | undefined, slot: 0 | 1 | null): RuntimeMoveAmmo {
  if (slot === null) {
    return {
      weaponSlot: null,
      currentLevel: level ?? null,
      current: null,
      lv1: null,
      lv10: null,
      refillType: null,
      refillParam: null,
    };
  }

  const current = slotForLevel(id, slot, level);
  const lv1 = slotForLevel(id, slot, 0);
  const lv10 = slotForLevel(id, slot, 9);
  return {
    weaponSlot: slot,
    currentLevel: level ?? null,
    current: current?.ammoCount ?? null,
    lv1: lv1?.ammoCount ?? null,
    lv10: lv10?.ammoCount ?? null,
    refillType: current?.chargeType ?? lv1?.chargeType ?? null,
    refillParam: current?.chargeCount ?? lv1?.chargeCount ?? null,
  };
}

function slotForLevel(id: string, slot: 0 | 1, level: number | undefined): BorgSourceWeaponSlot | null {
  return sourceStatsForBorgId(id, level)?.weaponSlots[slot] ?? null;
}

export type RuntimePrimaryAttackKind = PrimaryAttackKind;
