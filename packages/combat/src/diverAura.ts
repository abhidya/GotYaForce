// Diver X child: zz_01213bc_ / FUN_8012151c / FUN_80121694 / FUN_80121860,
// chunk_0033.c:212-425. This is deliberately separate from flying projectiles.
import { attackHitRecordsForKind } from "./attackHitData.js";
import { nextRomProjectileUid } from "./projectiles.js";
import { familyDamageRecordForBorg } from "./familyDamageData.js";
import { applyContactAuraStatus } from "./combat.js";
import { JELLY_DIVER_X } from "./families/jelly-diver.js";
import type { BorgRuntime, DiverAuraChild } from "./types.js";
import shotTables from "./data/shotVariantKinds.json" with { type: "json" };

const rows = shotTables.tables["0x8032c6a0"].rows;
function childRow(subtype: number): DataView {
  const row = rows.find((r) => r.variant === subtype)!;
  const bytes = Uint8Array.from(row.rawBytes.match(/../g)!, (b) => Number.parseInt(b, 16));
  return new DataView(bytes.buffer);
}
const ROWS = [childRow(0), childRow(1), childRow(2)];
const FORMS = ["pl0805", "pl080e", "pl080d"] as const;
const formId = (owner: BorgRuntime) => owner.combatFormId ?? owner.borgId;

/** Returns true only for this dedicated source spawner. Refresh preserves child identity.
 * Source owner+0x6f4 state is represented by child presence, avoiding two mutable owners. */
export function spawnOrRefreshDiverAura(
  children: DiverAuraChild[], owner: BorgRuntime, address: number, subtype: number,
): boolean {
  if (address !== JELLY_DIVER_X.CHILD_SPAWNER_ADDR) return false;
  if (!owner.alive || owner.hp <= 0 || owner.state === "death") return true;
  const row = ROWS[subtype];
  if (!row || FORMS[subtype] !== formId(owner)) return true;
  const existing = children.find((c) => c.ownerUid === owner.uid && c.ownerFormId === formId(owner));
  if (existing) {
    existing.remainingFrames = row.getInt16(6); // source refresh before the update decrement
    return true;
  }
  const hit = attackHitRecordsForKind(formId(owner), row.getInt16(4))[0];
  if (!hit || !familyDamageRecordForBorg(formId(owner), hit.damageRecordIndex)) return true;
  children.push({
    uid: `diver-aura-${nextRomProjectileUid()}`,
    ownerUid: owner.uid, ownerFormId: formId(owner), team: owner.team,
    subtype: subtype as 0 | 1 | 2, pos: { ...owner.pos },
    remainingFrames: row.getInt16(6),
    // APPROXIMATE: same max-extent spherical abstraction used by browser shots.
    // The source row's shapeKind=0 is not a proven sphere; bone-12 world matrices
    // are unavailable to Battle. No invented bone offset or generic muzzle is used.
    hitRadius: Math.max(...hit.halfExtent, hit.radius),
    bankTexId: row.getInt16(0), visualVariant: row.getFloat32(28),
    visualScale: (owner.modelSizeScale ?? 1) * row.getFloat32(20),
  });
  return true;
}

/** Contact phase after all movement. Source disables collision on expiry/owner-stop;
 * visual particle teardown is not modeled here. Root anchor and spherical overlap are
 * explicitly approximate; source table, per-frame status, refresh and lifetime are not. */
export function stepDiverAuras(children: DiverAuraChild[], all: readonly BorgRuntime[]): DiverAuraChild[] {
  return children.filter((child) => {
    const owner = all.find((b) => b.uid === child.ownerUid);
    if (!owner || !owner.alive || owner.hp <= 0 || owner.state === "death" || formId(owner) !== child.ownerFormId) return false;
    child.remainingFrames -= 1;
    if (child.remainingFrames < 1) return false;
    const row = ROWS[child.subtype]!;
    child.pos = { ...owner.pos }; // APPROXIMATE root anchor, source follows bone 12
    // Base scale only: source additionally applies an anisotropic visual pulse.
    // Undecoded pulse literals are deliberately not guessed here.
    child.visualScale = owner.modelSizeScale ?? 1;
    const hit = attackHitRecordsForKind(child.ownerFormId, row.getInt16(4))[0]!;
    const record = familyDamageRecordForBorg(child.ownerFormId, hit.damageRecordIndex)!;
    child.hitRadius = Math.max(...hit.halfExtent, hit.radius) * child.visualScale;
    for (const target of all) {
      // No invented team protection: record flagsB 0x480 lacks source same-team
      // exemption 0x10. The aura writer excludes Divers, burst/carried and immunity.
      // Target-body shape/mask geometry remains an approximation in this field port.
      if (!target.alive || target.hp <= 0 || target.state === "death") continue;
      if (Math.hypot(target.pos.x - child.pos.x, target.pos.y - child.pos.y, target.pos.z - child.pos.z) > child.hitRadius) continue;
      // The source aura branches return before ordinary damage/reaction processing.
      applyContactAuraStatus(target, record);
    }
    return true;
  });
}
