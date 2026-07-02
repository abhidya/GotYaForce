# Borg Animation Action Gaps

Generated: 2026-07-02T03:06:21.320Z

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
| Direct runtime matches | 1382 |
| Runtime fallbacks | 22 |
| Missing runtime matches | 0 |
| Borgs with any fallback | 18 |
| Borgs with any missing slot | 0 |
| Borgs with any gap | 18 |
| Parse errors | 0 |

## Per-Slot Coverage

| Slot | Direct | Fallback | Missing | Gap notes |
|---|---:|---:|---:|---|
| `idle` | 108 | 0 | 0 | none |
| `move` | 108 | 0 | 0 | none |
| `dash_fwd` | 107 | 1 | 0 | dash -> boost x1 |
| `dash_back` | 107 | 1 | 0 | dash -> boost x1 |
| `dash_left` | 103 | 5 | 0 | dash -> dash_fwd x4; dash -> boost x1 |
| `dash_right` | 97 | 11 | 0 | dash -> dash_fwd x10; dash -> boost x1 |
| `jump` | 106 | 2 | 0 | fly -> g2_s16 x2 |
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
| `dash_fwd` | `dash -> boost` | 1 | `pl0c04` |
| `dash_back` | `dash -> boost` | 1 | `pl0c04` |
| `dash_left` | `dash -> boost` | 1 | `pl0c04` |
| `dash_left` | `dash -> dash_fwd` | 4 | `pl0c00`, `pl0c01`, `pl0c02`, `pl0c05` |
| `dash_right` | `dash -> boost` | 1 | `pl0c04` |
| `dash_right` | `dash -> dash_fwd` | 10 | `pl0400`, `pl0401`, `pl0402`, `pl0403`, `pl0404`, `pl0405`, `pl0406`, `pl0407`, `pl040b`, `pl0602` |
| `jump` | `fly -> g2_s16` | 2 | `pl061f`, `pl0628` |
| `hit` | `idle -> idle` | 2 | `pl0808`, `pl0c04` |

## Explorer-Known Gaps Still Present

The rows below are generated from the same runtime resolver pass and keep the explorer-visible direct-label gaps in one place.

| Gap | Current evidence |
|---|---|
| `dash_fwd uses dash -> boost` | 1 Borg: `pl0c04` |
| `dash_back uses dash -> boost` | 1 Borg: `pl0c04` |
| `dash_left uses dash -> boost` | 1 Borg: `pl0c04` |
| `dash_left uses dash -> dash_fwd` | 4 Borgs: `pl0c00`, `pl0c01`, `pl0c02`, `pl0c05` |
| `dash_right uses dash -> boost` | 1 Borg: `pl0c04` |
| `dash_right uses dash -> dash_fwd` | 10 Borgs: `pl0400`, `pl0401`, `pl0402`, `pl0403`, `pl0404`, `pl0405`, `pl0406`, `pl0407`, `pl040b`, `pl0602` |
| `hit uses idle -> idle` | 2 Borgs: `pl0808`, `pl0c04` |

## Parse Errors

None.

## Reproduce

```bash
rtk node scripts/validate-borg-animation-actions.mjs
rtk node scripts/validate-borg-animation-actions.mjs --strict
```
