# ATK-020: Borg level plumbing (level byte + row table; formula floats stay defaulted)

**PARTIALLY BLOCKED**: the damage-formula level floats' init sites (+0xc4/+0xb4) are still
unfound (behavior-notes (ak)); until then the formula's `attackerPower`/`defenderPower`
params KEEP their 1.0 defaults. This ticket ports only what is evidenced: the level byte,
the level→row indexing, and their effect on HP/ammo via the already-extracted stat rows.

## Purpose
Let a borg's level select its real stat row (HP/ammo values) the way the ROM does, and
carry a level field through the sim so the formula floats can be wired the moment their
init rule is found.

## Evidence
- Row formula: `row = (subIdx + variant*0x14 + DAT_804339e8[level]) * 0x12` into the
  family table (zz_0055f90_ @0x80055f90, behavior-notes (ag); rows extracted per borg in
  research/decomp/data/borg-hp-stat-rows-802f2988.json).
- Level byte +0x3ec writers + story setter zz_005814c_ (behavior-notes (ak)).
- DAT_804339e8 single-pass dump in (ak) — MUST be re-verified with a dol.py read and
  persisted to research/decomp/data/level-row-offsets-804339e8.json as part of this ticket
  (follow the existing generator pattern; cite (ak)).
- Formula reads: dmg *= 1 + 0.5*(attackerFloat@+0xc4 - 1) and inverse for victim +0xb4
  (behavior-notes (ah) steps 2/13) — ALREADY implemented as attackerPower/defenderPower in
  packages/combat/src/damageFormula.ts:96,116; leave defaults at 1.0.

## Dependencies
None hard; coordinates with ATK-009 (ammo values come from the same rows).

## Files to edit
- new `scripts/gen-level-row-offsets.mjs` + `research/decomp/data/level-row-offsets-804339e8.json`
- `packages/combat/src/stats.ts` (BorgProfile gains `level?: number`, default the ROM's
  challenge/battle default — determine it from how borg-hp-stat-rows-802f2988.json was
  extracted (it used DAT_804339e8[0]=2 per (ag)); document)
- `packages/combat/src/sourceBorgStats.ts` / wherever HP+ammo rows are selected (make row
  selection level-aware using the verified table)

## Required behavior
- Level defaults reproduce today's extracted values exactly (G RED level-default row → HP
  200, ammo 5 — the live-verified anchor in (ag)). A different level selects a different
  row per the ROM arithmetic, clamped to the table's 32 entries.
- Do NOT feed level into attackerPower/defenderPower — add a comment in damageFormula.ts
  pointing at (ak): "level float init unfound; defaults stay 1.0".

## Fallbacks allowed
- Borgs without multi-level row data: keep default row (labeled).

## Tests to add
- G RED at default level → HP 200 / ammo 5 (anchor).
- Level variation changes the selected row exactly per DAT_804339e8 (table-driven test
  against the verified JSON).
- damageFormula output is UNCHANGED by level (floats not wired) — regression guard.

## Do not change
- attackerPower/defenderPower defaults; down-gauge scaling (a victim-vs-attacker-level
  conflict is open in (ak) — leave gauges.ts as is).

## Done when
Verified table JSON exists; row selection is level-aware with anchors green; formula
regression guard passes.
