# ATK-018: Power Burst fusion — pair data + link/state shell

**BLOCKED UNTIL (for full behavior)**: trace T3 reconciles the +0x6fb timer semantics and
confirms the fused-form control/visual behavior live. The pair DATA extraction and the
link/state scaffolding below are corpus-evidenced and can be built now.

## Purpose
Model the ROM's fusion structure: extract the real pair table, and add the actor-link +
fusion-state fields so the burst ticket (ATK-012) can trigger fusion when its blockers
clear. No fused-form gameplay in this ticket.

## Evidence
All in behavior-notes.md section (aj) (corpus read, single-pass):
- Pair table DAT_802d352c: 17 entries by family byte (+0x3e8); only families 5 and 6
  non-null (lists at 0x802d3420 / 0x802d3480); list = base + variant*4, entries
  (s16 partnerSpawnId, s16 resultSpawnId), -1 terminated. WARNING: reads at family >= 17
  overflow into the 35-slot state table (0x802d3570) — bound the extraction at 17.
- Match: zz_005b678_ chunk_0007.c:3518-3574 — in-place transform (result id -> +0x48c,
  head -> +0x48e, roles -> +0x4a9), bidirectional link +0x4a4, NO new actor spawn.
- State machine +0x4a1: 1->2->3->5->6 locked; 7,7 -> unfuse (chunk_0007.c:3170-3272).

## Dependencies
ATK-011 (burst shell). Blocks nothing.

## Files to edit
- new `scripts/gen-fusion-pairs.mjs` (dol.py-style raw extraction — follow the pattern of
  existing research/decomp/data/*.json generators; read boot.dol via research/decomp/dol.py
  helpers ported to the script's existing conventions)
- new `research/decomp/data/fusion-pairs-802d352c.json` (generated; provenance block
  citing (aj); spawn ids ALSO rendered as pl#### strings via the family<<8|variant packing
  from behavior-notes (n))
- `packages/combat/src/types.ts` (BorgRuntime: `fusionPartnerUid: string | null`,
  `fusionState: number` (ROM +0x4a1 vocabulary, 0 = none) — ADD only)

## Required behavior
- Extraction script dumps the two family lists exactly, bounded at 17 table entries;
  validates the -1 terminators; fails loudly if the pointers don't match (aj).
- Runtime fields default inert (null/0); nothing sets them yet (ATK-012 follow-up will).
- Do NOT implement fused movement/attacks/visuals.

## Fallbacks allowed
- None needed — data extraction + inert fields only.

## Tests to add
- JSON sanity in selfcheck or a small script test: every resultSpawnId parses to a known
  roster pl#### id (cross-check packages/assets/data/borgs.json); every partnerSpawnId
  likewise; list count > 0 for families 5 and 6 and 0 elsewhere.

## Do not change
- Burst damage/refill effects (ATK-012), command resolution, stepAttacks.

## Done when
fusion-pairs JSON exists with provenance and passes the roster cross-check; types compile;
no behavior change in selfcheck battles.
