# Borg Animation Action Gaps

Generated: 2026-07-05T05:58:44.741Z

Scope: `apps/game/public/models/pl*/anim_index.json`
Canonical app slots: `idle`, `move`, `dash_fwd`, `dash_back`, `dash_left`, `dash_right`, `jump`, `fly`, `shoot`, `melee`, `special`, `hit`, `death`
Runtime resolver: mirrors `PREFERRED_LABELS`, `SLOT_LABELS`, `SLOT_FALLBACKS`, `pickAnimBank`, and `pickAnimBankDirect` from `apps/game/src/sim/borgPresentationAssets.ts` (runtime label tables and bank sort/pick order). `BattleScene` may still ask for `idle` after `loadClip` returns null, so `missing` below means the main runtime resolver found no canonical clip before that last idle request.

## Summary

| Metric | Count |
|---|---:|
| Animation indexes found | 208 |
| Animation indexes parsed | 208 |
| Total exported banks in parsed indexes | 8633 |
| Canonical slot checks | 2704 |
| Direct runtime matches | 2704 |
| Runtime fallbacks | 0 |
| Missing runtime matches | 0 |
| Borgs with any fallback | 0 |
| Borgs with any missing slot | 0 |
| Borgs with any gap | 0 |
| Parse errors | 0 |

## Per-Slot Coverage

| Slot | Direct | Fallback | Missing | Gap notes |
|---|---:|---:|---:|---|
| `idle` | 208 | 0 | 0 | none |
| `move` | 208 | 0 | 0 | none |
| `dash_fwd` | 208 | 0 | 0 | none |
| `dash_back` | 208 | 0 | 0 | none |
| `dash_left` | 208 | 0 | 0 | none |
| `dash_right` | 208 | 0 | 0 | none |
| `jump` | 208 | 0 | 0 | none |
| `fly` | 208 | 0 | 0 | none |
| `shoot` | 208 | 0 | 0 | none |
| `melee` | 208 | 0 | 0 | none |
| `special` | 208 | 0 | 0 | none |
| `hit` | 208 | 0 | 0 | none |
| `death` | 208 | 0 | 0 | none |

## Missing Runtime Matches

No canonical slots are fully missing from the main runtime resolver.

## Runtime Fallbacks

No canonical slots fall back through `SLOT_FALLBACKS`.

## Explorer-Known Gaps Still Present

No explorer-visible canonical action gaps are still present.

## Parse Errors

None.

## Reproduce

```bash
rtk node scripts/validate-borg-animation-actions.mjs
rtk node scripts/validate-borg-animation-actions.mjs --strict
```


## Historical Session Findings Used To Resolve Prior Fallbacks (2026-07-03)

- `pl0625` (VICTORY MACHINE, `anim: null` in borgs.json) is a layout anomaly, not an export
  miss: its export contains ONLY `idle` in group 0; all locomotion-shaped banks live in
  group 2 (`g2_s16/s17/s19` carry dash-length root spans ~100-224 units, `g2_s21` a
  224-unit forward translation). The bake heuristic (scripts/bake-all-borg-anims.mjs
  `label()`) only labels group-0 slots, so every canonical slot fell back to idle.
  Do NOT relabel by span heuristics -- that is exactly the generic-labels failure mode.
- Source-accurate path found: the original state handlers select animation banks through
  `zz_004beb8_(speed, actor, bank, 0, slotExpr, -1, -1)` -- e.g. the knockdown entry
  `zz_0060c94_` @0x80060c94 plays (2, `+0x57c` + 0x1b) and `zz_0060be8_` plays
  (0xd, `+0x57c` + 0x1b) (chunk_0007.c:6810-6871). Tracing every `zz_004beb8_` call site
  per state handler (35-slot table at 0x802d3570, extracted in behavior-notes (af)) yields
  the authored action -> (bank, slot) mapping per state, including alternate layouts for
  large/boss borgs like pl0625.
