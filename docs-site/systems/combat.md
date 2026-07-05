---
title: Combat & Damage
---

# Combat & damage

Damage formula, knockback, hit reactions, attack profiles.

**Sources:**
- `research/decomp/attack-mechanics-findings.md`
- `research/decomp/attack-mechanics-open-questions.md`
- `research/decomp/combat-feel-gaps-decode-2026-07-05.md`
- `research/tasks/attack-port/` (ATK-001..020)

## Key tables

| Table | Address | Status |
|---|---|---|
| Damage formula | `0x804335e0` | <StatusBadge status="verified" /> |
| Damage records | `0x802d46e0` | <StatusBadge status="verified" /> |
| Type multiplier 20×20 matrix | `0x802c5d60` | <StatusBadge status="verified" /> |
| Knockback direction | `0x800300bc` | <StatusBadge status="verified" /> |
| Attack profile port schema | — | <StatusBadge status="verified" /> |

See [Damage formula & type matrix](./damage) for the matrix deep-dive and
[Action stream / cue script](./action-stream) for combo ladders.

## Open

- ICBM contact damage
- Suicide borg authored damage
- Owner-self damage edge cases
- Hyper input state edge cases
