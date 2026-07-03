# Borg Animation Action Gaps

Generated: 2026-07-03T01:55:58.240Z

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
| Direct runtime matches | 2372 |
| Runtime fallbacks | 33 |
| Missing runtime matches | 0 |
| Borgs with any fallback | 23 |
| Borgs with any missing slot | 0 |
| Borgs with any gap | 23 |
| Parse errors | 0 |

## Per-Slot Coverage

| Slot | Direct | Fallback | Missing | Gap notes |
|---|---:|---:|---:|---|
| `idle` | 185 | 0 | 0 | none |
| `move` | 184 | 1 | 0 | idle -> idle x1 |
| `dash_fwd` | 184 | 1 | 0 | idle -> idle x1 |
| `dash_back` | 184 | 1 | 0 | idle -> idle x1 |
| `dash_left` | 183 | 2 | 0 | idle -> idle x1; dash -> dash_fwd x1 |
| `dash_right` | 176 | 9 | 0 | dash -> dash_fwd x8; idle -> idle x1 |
| `jump` | 184 | 1 | 0 | idle -> idle x1 |
| `fly` | 184 | 1 | 0 | idle -> idle x1 |
| `shoot` | 185 | 0 | 0 | none |
| `melee` | 183 | 2 | 0 | idle -> idle x2 |
| `special` | 180 | 5 | 0 | attack -> attack_s4 x2; attack -> attack_s0 x3 |
| `hit` | 175 | 10 | 0 | idle -> idle x10 |
| `death` | 185 | 0 | 0 | none |

## Missing Runtime Matches

No canonical slots are fully missing from the main runtime resolver.

## Runtime Fallbacks

| Requested slot | Runtime fallback used | Count | Borgs |
|---|---|---:|---|
| `move` | `idle -> idle` | 1 | `pl0625` |
| `dash_fwd` | `idle -> idle` | 1 | `pl0625` |
| `dash_back` | `idle -> idle` | 1 | `pl0625` |
| `dash_left` | `dash -> dash_fwd` | 1 | `pl0c06` |
| `dash_left` | `idle -> idle` | 1 | `pl0625` |
| `dash_right` | `dash -> dash_fwd` | 8 | `pl0408`, `pl0409`, `pl040a`, `pl040c`, `pl040d`, `pl060a`, `pl060c`, `pl060e` |
| `dash_right` | `idle -> idle` | 1 | `pl0625` |
| `jump` | `idle -> idle` | 1 | `pl0625` |
| `fly` | `idle -> idle` | 1 | `pl0625` |
| `melee` | `idle -> idle` | 2 | `pl0625`, `pl0c06` |
| `special` | `attack -> attack_s0` | 3 | `pl0a05`, `pl0a07`, `pl0a0a` |
| `special` | `attack -> attack_s4` | 2 | `pl080d`, `pl080e` |
| `hit` | `idle -> idle` | 10 | `pl0618`, `pl061e`, `pl0620`, `pl0621`, `pl0623`, `pl0625`, `pl0627`, `pl0808`, `pl0c04`, `pl0c06` |

## Explorer-Known Gaps Still Present

The rows below are generated from the same runtime resolver pass and keep the explorer-visible direct-label gaps in one place.

| Gap | Current evidence |
|---|---|
| `dash_fwd uses idle -> idle` | 1 Borg: `pl0625` |
| `dash_back uses idle -> idle` | 1 Borg: `pl0625` |
| `dash_left uses dash -> dash_fwd` | 1 Borg: `pl0c06` |
| `dash_left uses idle -> idle` | 1 Borg: `pl0625` |
| `dash_right uses dash -> dash_fwd` | 8 Borgs: `pl0408`, `pl0409`, `pl040a`, `pl040c`, `pl040d`, `pl060a`, `pl060c`, `pl060e` |
| `dash_right uses idle -> idle` | 1 Borg: `pl0625` |
| `melee uses idle -> idle` | 2 Borgs: `pl0625`, `pl0c06` |
| `special uses attack -> attack_s0` | 3 Borgs: `pl0a05`, `pl0a07`, `pl0a0a` |
| `special uses attack -> attack_s4` | 2 Borgs: `pl080d`, `pl080e` |
| `hit uses idle -> idle` | 10 Borgs: `pl0618`, `pl061e`, `pl0620`, `pl0621`, `pl0623`, `pl0625`, `pl0627`, `pl0808`, `pl0c04`, `pl0c06` |

## Parse Errors

None.

## Reproduce

```bash
rtk node scripts/validate-borg-animation-actions.mjs
rtk node scripts/validate-borg-animation-actions.mjs --strict
```
