// Real type/category damage multiplier from the GG4E DOL.
//
// Evidence:
// - research/decomp/data/type-category-remap-802f2e28.json:
//   zz_0066298_ maps object+1000 bytes (family, variant) to canonical category 0..19.
// - research/decomp/data/type-multiplier-matrix-802c5d60.json:
//   zz_003cd5c_ multiplies damage by matrix[defenderCategory][attackerCategory].
// - research/decomp/behavior-notes.md section (w):
//   all 208 borgs.json ids parse as pl{family}{variant} and resolve through the remap table.

const TYPE_CATEGORY_REMAP: readonly (readonly number[])[] = [
  [0, 0, 0, 0, 0, 0, 0, 0, 19, 0, 0, 0, 19, 0],
  [1, 1, 1, 1, 1, 19, 1, 1, 1, 19, 19, 0],
  [2, 2, 2, 2, 2, 2, 19, 11, 2, 2, 2, 2, 2, 2, 2, 19],
  [3, 3, 3, 19, 3, 3, 3, 3, 3, 3, 3, 3, 19, 19],
  [4, 4, 4, 4, 4, 4, 19, 4, 4, 4, 4, 19, 19, 19],
  [5, 11, 5, 5, 5, 5, 5, 5, 5, 5, 5, 11, 5, 11, 5, 5, 5, 5, 5, 5, 5, 5, 5, 11],
  [
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 16, 4, 17, 4, 4, 4, 16, 17, 4, 4, 4, 4, 16, 16, 4, 16, 4, 4, 0,
  ],
  [6, 12, 2, 6, 6, 19, 6, 6, 12, 6, 2, 19, 19, 19],
  [7, 7, 13, 13, 13, 7, 7, 19, 13, 7, 13, 13, 13, 7, 7, 19],
  [9, 8, 8, 8, 10, 8, 19, 8, 9, 8, 8, 19, 8, 9],
  [14, 13, 12, 14, 14, 19, 14, 12, 14, 14, 19, 0],
  [15, 15, 15, 15, 15, 19, 15, 19],
  [16, 16, 16, 16, 16, 16, 16, 0],
  [17, 17, 17, 17, 17, 17, 19, 19],
  [18, 18, 18, 18, 18, 18],
  [19, 19, 19, 19, 19, 11, 19, 19],
];

const TYPE_MULTIPLIER_MATRIX: readonly (readonly number[])[] = [
  [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1],
  [1, 1, 1, 1.1, 1, 1, 1, 1, 1.1, 1.1, 1, 1, 1, 1, 1, 1.1, 1, 1, 1, 1],
  [1, 1, 1, 1, 1, 0.99, 1.1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1],
  [1, 0.9, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1],
  [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0.9],
  [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1],
  [1, 1, 0.9, 1, 1, 1, 0.95, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1],
  [1, 1, 1, 1, 1, 1, 1, 0.95, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1],
  [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1],
  [1, 0.95, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1],
  [1, 0.95, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1],
  [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0.95, 1, 1, 1, 1, 1, 1, 1],
  [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1.1, 1, 1, 1.25, 1, 1, 1, 1],
  [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1.1, 1, 1, 1, 1, 1, 1, 1, 1],
  [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1.1, 1, 1, 1],
  [1, 0.9, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0.75, 1, 1, 1, 1.1, 1, 1, 1],
  [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1.1, 1.1, 1, 1.2, 1, 1],
  [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1.1, 1, 1, 1],
  [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1],
  [1, 1, 1, 1, 1.1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1],
];

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
