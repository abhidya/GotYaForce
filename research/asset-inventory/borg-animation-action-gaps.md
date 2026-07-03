# Borg Animation Action Gaps

Generated: 2026-07-03T20:31:50.353Z

Scope: `apps/game/public/models/pl*/anim_index.json`
Canonical app slots: `idle`, `move`, `dash_fwd`, `dash_back`, `dash_left`, `dash_right`, `jump`, `fly`, `shoot`, `melee`, `special`, `hit`, `death`
Runtime resolver: mirrors `PREFERRED_LABELS`, `SLOT_LABELS`, `SLOT_FALLBACKS`, `pickAnimBank`, and `pickAnimBankDirect` from `apps/game/src/main.ts` (runtime label tables and bank sort/pick order). `BattleScene` may still ask for `idle` after `loadClip` returns null, so `missing` below means the main runtime resolver found no canonical clip before that last idle request.

## Summary

| Metric | Count |
|---|---:|
| Animation indexes found | 185 |
| Animation indexes parsed | 185 |
| Total exported banks in parsed indexes | 8242 |
| Canonical slot checks | 2405 |
| Direct runtime matches | 2405 |
| Runtime fallbacks | 0 |
| Missing runtime matches | 0 |
| Borgs with any fallback | 0 |
| Borgs with any missing slot | 0 |
| Borgs with any gap | 0 |
| Parse errors | 0 |

## Per-Slot Coverage

| Slot | Direct | Fallback | Missing | Gap notes |
|---|---:|---:|---:|---|
| `idle` | 185 | 0 | 0 | none |
| `move` | 185 | 0 | 0 | none |
| `dash_fwd` | 185 | 0 | 0 | none |
| `dash_back` | 185 | 0 | 0 | none |
| `dash_left` | 185 | 0 | 0 | none |
| `dash_right` | 185 | 0 | 0 | none |
| `jump` | 185 | 0 | 0 | none |
| `fly` | 185 | 0 | 0 | none |
| `shoot` | 185 | 0 | 0 | none |
| `melee` | 185 | 0 | 0 | none |
| `special` | 185 | 0 | 0 | none |
| `hit` | 185 | 0 | 0 | none |
| `death` | 185 | 0 | 0 | none |

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
