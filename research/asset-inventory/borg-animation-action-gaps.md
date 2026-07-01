# Borg Animation Action Gaps

Generated: 2026-07-01T02:59:07.702Z

Scope: `apps/game/public/models/pl*/anim_index.json`
Canonical app slots: `idle`, `move`, `dash_fwd`, `dash_back`, `dash_left`, `dash_right`, `jump`, `fly`, `shoot`, `melee`, `special`, `hit`, `death`
Runtime resolver: mirrors `PREFERRED_LABELS`, `SLOT_LABELS`, `SLOT_FALLBACKS`, `pickAnimBank`, and `pickAnimBankDirect` from `apps/game/src/main.ts` (runtime label tables and bank sort/pick order). `BattleScene` may still ask for `idle` after `loadClip` returns null, so `missing` below means the main runtime resolver found no canonical clip before that last idle request.

## Summary

| Metric | Count |
|---|---:|
| Animation indexes found | 104 |
| Animation indexes parsed | 104 |
| Total exported banks in parsed indexes | 4653 |
| Canonical slot checks | 1352 |
| Direct runtime matches | 1274 |
| Runtime fallbacks | 75 |
| Missing runtime matches | 3 |
| Borgs with any fallback | 28 |
| Borgs with any missing slot | 3 |
| Borgs with any gap | 28 |
| Parse errors | 0 |

## Per-Slot Coverage

| Slot | Direct | Fallback | Missing | Gap notes |
|---|---:|---:|---:|---|
| `idle` | 104 | 0 | 0 | none |
| `move` | 101 | 0 | 3 | missing x3 |
| `dash_fwd` | 100 | 4 | 0 | idle -> idle x3; dash -> boost x1 |
| `dash_back` | 100 | 4 | 0 | idle -> idle x3; dash -> boost x1 |
| `dash_left` | 96 | 8 | 0 | idle -> idle x3; dash -> dash_fwd x4; dash -> boost x1 |
| `dash_right` | 90 | 14 | 0 | dash -> dash_fwd x10; idle -> idle x3; dash -> boost x1 |
| `jump` | 101 | 3 | 0 | idle -> idle x3 |
| `fly` | 101 | 3 | 0 | idle -> idle x3 |
| `shoot` | 102 | 2 | 0 | idle -> idle x2 |
| `melee` | 96 | 8 | 0 | idle -> idle x3; move -> move x5 |
| `special` | 98 | 6 | 0 | idle -> idle x2; attack -> attack_s0 x4 |
| `hit` | 92 | 12 | 0 | down -> death x3; idle -> idle x9 |
| `death` | 93 | 11 | 0 | down -> guard_s0 x3; idle -> idle x8 |

## Missing Runtime Matches

| Requested slot | Count | Borgs |
|---|---:|---|
| `move` | 3 | `pl0619`, `pl061f`, `pl0628` |

## Runtime Fallbacks

| Requested slot | Runtime fallback used | Count | Borgs |
|---|---|---:|---|
| `dash_fwd` | `dash -> boost` | 1 | `pl0c04` |
| `dash_fwd` | `idle -> idle` | 3 | `pl0619`, `pl061f`, `pl0628` |
| `dash_back` | `dash -> boost` | 1 | `pl0c04` |
| `dash_back` | `idle -> idle` | 3 | `pl0619`, `pl061f`, `pl0628` |
| `dash_left` | `dash -> boost` | 1 | `pl0c04` |
| `dash_left` | `dash -> dash_fwd` | 4 | `pl0c00`, `pl0c01`, `pl0c02`, `pl0c05` |
| `dash_left` | `idle -> idle` | 3 | `pl0619`, `pl061f`, `pl0628` |
| `dash_right` | `dash -> boost` | 1 | `pl0c04` |
| `dash_right` | `dash -> dash_fwd` | 10 | `pl0400`, `pl0401`, `pl0402`, `pl0403`, `pl0404`, `pl0405`, `pl0406`, `pl0407`, `pl040b`, `pl0602` |
| `dash_right` | `idle -> idle` | 3 | `pl0619`, `pl061f`, `pl0628` |
| `jump` | `idle -> idle` | 3 | `pl0619`, `pl061f`, `pl0628` |
| `fly` | `idle -> idle` | 3 | `pl0619`, `pl061f`, `pl0628` |
| `shoot` | `idle -> idle` | 2 | `pl0619`, `pl0628` |
| `melee` | `idle -> idle` | 3 | `pl0619`, `pl061f`, `pl0628` |
| `melee` | `move -> move` | 5 | `pl0c00`, `pl0c01`, `pl0c02`, `pl0c04`, `pl0c05` |
| `special` | `attack -> attack_s0` | 4 | `pl0800`, `pl0807`, `pl0808`, `pl0a00` |
| `special` | `idle -> idle` | 2 | `pl0619`, `pl0628` |
| `hit` | `down -> death` | 3 | `pl0604`, `pl0613`, `pl0808` |
| `hit` | `idle -> idle` | 9 | `pl0610`, `pl0619`, `pl061f`, `pl0628`, `pl0c00`, `pl0c01`, `pl0c02`, `pl0c04`, `pl0c05` |
| `death` | `down -> guard_s0` | 3 | `pl0500`, `pl0503`, `pl0504` |
| `death` | `idle -> idle` | 8 | `pl0619`, `pl061f`, `pl0628`, `pl0c00`, `pl0c01`, `pl0c02`, `pl0c04`, `pl0c05` |

## Explorer-Known Gaps Still Present

The rows below are generated from the same runtime resolver pass and keep the explorer-visible direct-label gaps in one place.

| Gap | Current evidence |
|---|---|
| `move unresolved` | 3 Borgs: `pl0619`, `pl061f`, `pl0628` |
| `dash_fwd uses dash -> boost` | 1 Borg: `pl0c04` |
| `dash_fwd uses idle -> idle` | 3 Borgs: `pl0619`, `pl061f`, `pl0628` |
| `dash_back uses dash -> boost` | 1 Borg: `pl0c04` |
| `dash_back uses idle -> idle` | 3 Borgs: `pl0619`, `pl061f`, `pl0628` |
| `dash_left uses dash -> boost` | 1 Borg: `pl0c04` |
| `dash_left uses dash -> dash_fwd` | 4 Borgs: `pl0c00`, `pl0c01`, `pl0c02`, `pl0c05` |
| `dash_left uses idle -> idle` | 3 Borgs: `pl0619`, `pl061f`, `pl0628` |
| `dash_right uses dash -> boost` | 1 Borg: `pl0c04` |
| `dash_right uses dash -> dash_fwd` | 10 Borgs: `pl0400`, `pl0401`, `pl0402`, `pl0403`, `pl0404`, `pl0405`, `pl0406`, `pl0407`, `pl040b`, `pl0602` |
| `dash_right uses idle -> idle` | 3 Borgs: `pl0619`, `pl061f`, `pl0628` |
| `shoot uses idle -> idle` | 2 Borgs: `pl0619`, `pl0628` |
| `melee uses idle -> idle` | 3 Borgs: `pl0619`, `pl061f`, `pl0628` |
| `melee uses move -> move` | 5 Borgs: `pl0c00`, `pl0c01`, `pl0c02`, `pl0c04`, `pl0c05` |
| `special uses attack -> attack_s0` | 4 Borgs: `pl0800`, `pl0807`, `pl0808`, `pl0a00` |
| `special uses idle -> idle` | 2 Borgs: `pl0619`, `pl0628` |
| `hit uses down -> death` | 3 Borgs: `pl0604`, `pl0613`, `pl0808` |
| `hit uses idle -> idle` | 9 Borgs: `pl0610`, `pl0619`, `pl061f`, `pl0628`, `pl0c00`, `pl0c01`, `pl0c02`, `pl0c04`, `pl0c05` |
| `death uses down -> guard_s0` | 3 Borgs: `pl0500`, `pl0503`, `pl0504` |
| `death uses idle -> idle` | 8 Borgs: `pl0619`, `pl061f`, `pl0628`, `pl0c00`, `pl0c01`, `pl0c02`, `pl0c04`, `pl0c05` |

## Parse Errors

None.

## Reproduce

```bash
rtk node scripts/validate-borg-animation-actions.mjs
rtk node scripts/validate-borg-animation-actions.mjs --strict
```
