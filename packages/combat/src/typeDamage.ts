// Real type/category damage multiplier from the GG4E DOL.
//
// Evidence:
// - research/decomp/data/type-category-remap-802f2e28.json:
//   zz_0066298_ maps object+1000 bytes (family, variant) to canonical category 0..19.
// - research/decomp/data/type-multiplier-matrix-802c5d60.json:
//   zz_003cd5c_ multiplies damage by matrix[defenderCategory][attackerCategory].
// - research/decomp/behavior-notes.md section (w):
//   all borgs.json ids parse as pl{family}{variant} and resolve through the remap table.

import { TYPE_CATEGORY_REMAP } from "./typeDamage.generated.js";
import { typeMultiplier } from "./damage/sourceDamage.js";

const BORG_ID_PATTERN = /^pl([0-9a-f]{2})([0-9a-f]{2})$/i;

export function typeCategoryForBorgId(borgId: string): number | null {
  const match = BORG_ID_PATTERN.exec(borgId);
  const familyText = match?.[1];
  const variantText = match?.[2];
  if (familyText === undefined || variantText === undefined) return null;

  const family = Number.parseInt(familyText, 16);
  const variant = Number.parseInt(variantText, 16);
  const category = TYPE_CATEGORY_REMAP[family]?.[variant];
  return category === undefined ? null : category;
}

/**
 * Borg-id-keyed view of the type matrix. The matrix read itself is NOT duplicated here: it
 * delegates to damage/sourceDamage.ts's `typeMultiplier`, which is the ROM-wasm interception
 * point (setRomDamageImplementation swaps lookupTypeCategory wholesale). A second local
 * TYPE_MULTIPLIER_MATRIX read would silently leave that verified path.
 *
 * The id -> borgNumber step is the identity documented in behavior-notes.md (w): "pl{family}
 * {variant}" hex digits ARE the +0x3e8 word zz_0066298_ reads. An id that does not parse (or
 * whose family/variant is outside the remap table) keeps the neutral 1.0 rather than guessing.
 */
export function typeDamageMultiplier(
  attackerBorgId: string | undefined,
  defenderBorgId: string | undefined,
): number {
  if (attackerBorgId === undefined || defenderBorgId === undefined) return 1;
  const attackerCategory = typeCategoryForBorgId(attackerBorgId);
  const defenderCategory = typeCategoryForBorgId(defenderBorgId);
  if (attackerCategory === null || defenderCategory === null) return 1;

  return typeMultiplier(borgNumberForBorgId(attackerBorgId), borgNumberForBorgId(defenderBorgId));
}

/** "pl0b00" -> 0x0b00 (the +0x3e8 word). Only called after typeCategoryForBorgId confirmed the
 *  id parses and resolves, so the parse cannot fail here. */
function borgNumberForBorgId(borgId: string): number {
  const match = BORG_ID_PATTERN.exec(borgId);
  return (Number.parseInt(match?.[1] ?? "0", 16) << 8) | Number.parseInt(match?.[2] ?? "0", 16);
}
