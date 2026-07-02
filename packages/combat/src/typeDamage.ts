// Real type/category damage multiplier from the GG4E DOL.
//
// Evidence:
// - research/decomp/data/type-category-remap-802f2e28.json:
//   zz_0066298_ maps object+1000 bytes (family, variant) to canonical category 0..19.
// - research/decomp/data/type-multiplier-matrix-802c5d60.json:
//   zz_003cd5c_ multiplies damage by matrix[defenderCategory][attackerCategory].
// - research/decomp/behavior-notes.md section (w):
//   all borgs.json ids parse as pl{family}{variant} and resolve through the remap table.

import { TYPE_CATEGORY_REMAP, TYPE_MULTIPLIER_MATRIX } from "./typeDamage.generated.js";

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

export function typeDamageMultiplier(
  attackerBorgId: string | undefined,
  defenderBorgId: string | undefined,
): number {
  if (attackerBorgId === undefined || defenderBorgId === undefined) return 1;
  const attackerCategory = typeCategoryForBorgId(attackerBorgId);
  const defenderCategory = typeCategoryForBorgId(defenderBorgId);
  if (attackerCategory === null || defenderCategory === null) return 1;

  return TYPE_MULTIPLIER_MATRIX[defenderCategory]?.[attackerCategory] ?? 1;
}
