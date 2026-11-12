// Diver X child: zz_01213bc_ / FUN_8012151c / FUN_80121694 / FUN_80121860,
// chunk_0033.c:212-425. This is deliberately separate from flying projectiles.
import { attackHitRecordsForKind } from "./attackHitData.js";
import { nextRomProjectileUid } from "./projectiles.js";
import { familyDamageRecordForBorg } from "./familyDamageData.js";
import { applyContactAuraStatus } from "./combat.js";
import { JELLY_DIVER_X } from "./families/jelly-diver.js";
import type { BorgRuntime, DiverAuraChild, DiverAuraTail } from "./types.js";
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
  const initialScale = Math.fround((owner.modelSizeScale ?? 1) * row.getFloat32(20));
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
    baseScale: owner.modelSizeScale ?? 1,
    particleCountdown: 0, particleRng: 0, particles: [],
    pulsePhaseDegrees: 0,
    visualScale: { x: initialScale, y: initialScale, z: initialScale },
  });
  return true;
}

/** Contact phase after all movement. Source disables collision on expiry/owner-stop;
 * only natural expiry emits a detached tail. Root anchor and spherical overlap are
 * explicitly approximate; source table, per-frame status, refresh and lifetime are not. */
export function stepDiverAuras(children: DiverAuraChild[], all: readonly BorgRuntime[], tails: DiverAuraTail[] = []): DiverAuraChild[] {
  return children.filter((child) => {
    const owner = all.find((b) => b.uid === child.ownerUid);
    if (!owner || !owner.alive || owner.hp <= 0 || owner.state === "death" || formId(owner) !== child.ownerFormId) return false;
    // Source copies owner base scale before dispatching the lifetime state.
    child.baseScale = owner.modelSizeScale ?? 1;
    child.remainingFrames -= 1;
    if (child.remainingFrames < 1) {
      tails.push(createDiverAuraTail(child));
      return false;
    }
    const row = ROWS[child.subtype]!;
    child.pos = { ...owner.pos }; // APPROXIMATE root anchor, source follows bone 12
    child.pulsePhaseDegrees += 3;
    if (child.pulsePhaseDegrees >= 360) child.pulsePhaseDegrees -= 360;
    const baseScale = owner.modelSizeScale ?? 1;
    child.visualScale = diverAuraPulseScale(child.pulsePhaseDegrees, baseScale);
    stepDiverActiveParticles(child);
    const hit = attackHitRecordsForKind(child.ownerFormId, row.getInt16(4))[0]!;
    const record = familyDamageRecordForBorg(child.ownerFormId, hit.damageRecordIndex)!;
    child.hitRadius = Math.max(...hit.halfExtent, hit.radius) * baseScale;
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

/** FUN_80121694 and zz_0045204_: decoded f32 literals and signed-short angle.
 * Math.sin approximates the source gnt4_sin; this is NOT bit-exact libm parity.
 * See research/decomp/diver-source-pulse-2026-11-11.md for evidence/bounds. */
export function diverAuraPulseScale(phaseDegrees: number, ownerBaseScale: number): DiverAuraChild["visualScale"] {
  const f32 = Math.fround;
  const angle = Math.trunc(f32(182.04444885253906 * phaseDegrees));
  const signedAngle = (angle << 16) >> 16;
  const sine = f32(Math.sin(f32(signedAngle * 0.0000958738019107841)));
  // Source fmadds rounds the combined expression, not the product separately.
  const xz = f32(f32(1 + 0.04769999906420708 * sine) * ownerBaseScale);
  const y = f32(f32(1 - 0.11110000312328339 * sine) * ownerBaseScale);
  return { x: xz, y, z: xz };
}

/** Source zz_0121db0_ birth / FUN_80121918 init / FUN_80121990 update. Mathematical translation,
 * not PPC rounding parity. Isolated visual RNG intentionally does not reproduce
 * the source global RNG stream. Active particles use their own persistent visual stream. */
export function createDiverAuraTail(child: DiverAuraChild): DiverAuraTail {
  let rng = 2166136261;
  for (const char of child.uid) rng = Math.imul(rng ^ char.charCodeAt(0), 16777619);
  const byte = () => { rng ^= rng << 13; rng ^= rng >>> 17; rng ^= rng << 5; return rng >>> 24; };
  const particles = Array.from({ length: 32 }, (_, index) => {
    const r = Array.from({ length: 6 }, byte);
    const scale = 0.5 + r[0]! / 255;
    const radius = 760 * child.baseScale - 90 * scale;
    let x = radius * (r[1]! / 127.5 - 1);
    let y = radius * (r[2]! / 127 - 1);
    let z = radius * (r[3]! / 127.5 - 1);
    let magnitude = Math.hypot(x, y, z);
    if (magnitude < 0.00009999999747378752) { x = 0; y = 1; z = 0; magnitude = 1; }
    const distance = radius * (0.75 + r[4]! / 1020) / magnitude;
    const speed = child.baseScale * (20 + r[5]! / 51) / magnitude;
    return { index, scale, radius, offset: { x: x * distance, y: y * distance, z: z * distance },
      velocity: { x: x * speed, y: y * speed, z: z * speed }, opacity: 0.25 };
  });
  return { uid: child.uid, pos: { ...child.pos }, visualVariant: child.visualVariant, particles };
}

export function stepDiverAuraTails(tails: DiverAuraTail[]): DiverAuraTail[] {
  return tails.filter((tail) => {
    tail.particles = tail.particles.filter((p) => {
      p.offset.x += p.velocity.x; p.offset.y += p.velocity.y; p.offset.z += p.velocity.z;
      if (Math.hypot(p.offset.x, p.offset.y, p.offset.z) > p.radius)
        p.opacity = Math.max(0, p.opacity - 0.012500000186264515);
      return p.opacity > 0;
    });
    return tail.particles.length > 0;
  });
}


/** Mesh-79 particles: FUN_80121694 / zz_0121db0_ / zz_0122208_.
 * Mathematical source translation, not PPC or source-global RNG parity. */
export function stepDiverActiveParticles(child: DiverAuraChild): void {
  child.particleCountdown--;
  if (child.particleCountdown <= 0) {
    child.particleCountdown = 30;
    const index = Array.from({ length: 32 }, (_, i) => i).find((i) => !child.particles.some((p) => p.index === i));
    if (index !== undefined) {
      if (!child.particleRng) {
        child.particleRng = 2166136261;
        for (const char of child.uid) child.particleRng = Math.imul(child.particleRng ^ char.charCodeAt(0), 16777619);
        if (!child.particleRng) child.particleRng = 1;
      }
      const byte = () => {
        let state = child.particleRng;
        state ^= state << 13; state ^= state >>> 17; state ^= state << 5;
        child.particleRng = state; return state >>> 24;
      };
      const r = Array.from({ length: 6 }, byte);
      const scale = 1 + r[0]! / 255;
      const radius = 760 * child.baseScale - 90 * scale;
      const offset = { x: radius * (r[1]! / 127.5 - 1), y: radius * (r[2]! / 510 - 1), z: radius * (r[3]! / 127.5 - 1) };
      const magnitude = Math.hypot(offset.x, offset.y, offset.z);
      if (magnitude > radius && magnitude > 0) {
        const factor = radius / magnitude;
        offset.x *= factor; offset.y *= factor; offset.z *= factor;
      }
      child.particles.push({ index, scale, offset, rise: 4 + r[4]! / 127.5,
        yaw: (r[5]! << 25) >> 16, yawStep: r[5]! & 0x80 ? 0x400 : -0x400, opacity: .25 });
    }
  }
  // Source births before updating, including the newly allocated particle.
  child.particles = child.particles.filter((p) => {
    p.offset.y += p.rise;
    p.yaw = ((p.yaw + p.yawStep) << 16) >> 16;
    return Math.hypot(p.offset.x, p.offset.y, p.offset.z) < 760 * child.baseScale - 90 * p.scale;
  });
}
