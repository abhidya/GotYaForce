---
title: Execution Map
---

# Execution map

How a frame flows from disc files to player-visible behavior.

```text
ISO / FST ──► pl****_mdl.arc ──► HSD DAT ──► runtime object
                                                       │
                                                       ▼
                                            move command (input)
                                                       │
                                                       ▼
                                                attack update fn
                                                       │
                                                       ▼
                                            projectile spawn fn
                                                       │
                                                       ▼
                                                  frame result
```

## Disc → RAM pipeline

| Stage | Owner | Status |
|---|---|---|
| ISO filesystem | DVD/FST | <StatusBadge status="verified" /> |
| AFS archives | `gotcha-afs-tool` | <StatusBadge status="verified" /> |
| `.arc` (HSD DAT wrappers) | HSDLib | <StatusBadge status="verified" /> |
| JOBJ skeleton + skins | HSDLib | <StatusBadge status="verified" /> |
| Animation export (`.mot`) | HSDLib | <StatusBadge status="likely" /> TODO |
| Runtime object spawn | `battle-initialization` | <StatusBadge status="observed" /> |

## Per-frame loop

1. **Input** — `command-button-map.json` resolves GC pad to action IDs.
2. **Borg update** — reads `actor + 0x34` (BorgRuntime).
3. **Action stream / cue script** — state→anim dispatch at `0x802d3570`.
4. **Attack update** — damage formula + 20×20 type matrix at `0x802c5d60`.
5. **Knockback** — direction compute at `0x800300bc`.
6. **Camera** — ring buffer in MEM1.
7. **Render submit** — GX state per stage lighting table.

See [Memory map](./memory-map) for offsets and [Source map](./source-map) for
the decomp module layout.
