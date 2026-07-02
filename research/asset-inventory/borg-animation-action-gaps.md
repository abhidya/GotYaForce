# Borg Animation Action Gaps

Generated: 2026-07-02T04:41:56.773Z

Scope: `apps/game/public/models/pl*/anim_index.json`
Canonical app slots: `idle`, `move`, `dash_fwd`, `dash_back`, `dash_left`, `dash_right`, `jump`, `fly`, `shoot`, `melee`, `special`, `hit`, `death`
Runtime resolver: mirrors `PREFERRED_LABELS`, `SLOT_LABELS`, `SLOT_FALLBACKS`, `pickAnimBank`, and `pickAnimBankDirect` from `apps/game/src/main.ts` (runtime label tables and bank sort/pick order). `BattleScene` may still ask for `idle` after `loadClip` returns null, so `missing` below means the main runtime resolver found no canonical clip before that last idle request.

## Summary

| Metric | Count |
|---|---:|
| Animation indexes found | 108 |
| Animation indexes parsed | 108 |
| Total exported banks in parsed indexes | 4894 |
| Canonical slot checks | 1404 |
| Direct runtime matches | 1402 |
| Runtime fallbacks | 2 |
| Missing runtime matches | 0 |
| Borgs with any fallback | 2 |
| Borgs with any missing slot | 0 |
| Borgs with any gap | 2 |
| Parse errors | 0 |

## Per-Slot Coverage

| Slot | Direct | Fallback | Missing | Gap notes |
|---|---:|---:|---:|---|
| `idle` | 108 | 0 | 0 | none |
| `move` | 108 | 0 | 0 | none |
| `dash_fwd` | 108 | 0 | 0 | none |
| `dash_back` | 108 | 0 | 0 | none |
| `dash_left` | 108 | 0 | 0 | none |
| `dash_right` | 108 | 0 | 0 | none |
| `jump` | 108 | 0 | 0 | none |
| `fly` | 108 | 0 | 0 | none |
| `shoot` | 108 | 0 | 0 | none |
| `melee` | 108 | 0 | 0 | none |
| `special` | 108 | 0 | 0 | none |
| `hit` | 106 | 2 | 0 | idle -> idle x2 |
| `death` | 108 | 0 | 0 | none |

## Missing Runtime Matches

No canonical slots are fully missing from the main runtime resolver.

## Runtime Fallbacks

| Requested slot | Runtime fallback used | Count | Borgs |
|---|---|---:|---|
| `hit` | `idle -> idle` | 2 | `pl0808`, `pl0c04` |

## Explorer-Known Gaps Still Present

The rows below are generated from the same runtime resolver pass and keep the explorer-visible direct-label gaps in one place.

| Gap | Current evidence |
|---|---|
| `hit uses idle -> idle` | 2 Borgs: `pl0808`, `pl0c04` |

## Parse Errors

None.

## Reproduce

```bash
rtk node scripts/validate-borg-animation-actions.mjs
rtk node scripts/validate-borg-animation-actions.mjs --strict
```
