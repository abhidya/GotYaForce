---
title: Stat Growth
---

# Borg stat growth

HP, ammo, refill, and level-up schedules.

**Sources:**
- `research/format-specs/pl-data-bin-layout.md`
- `research/decomp/data/borg-hp-stat-rows-802f2988.json`
- `research/decomp/data/level-row-offsets-804339e8.json`
- `research/tasks/attack-port/ATK-020-level-plumbing.md`

<StatusBadge status="verified" />

Each borg carries a `pl####data.bin` row that fixes HP at level 1 and level 10,
plus a level-up schedule key from `NTSC_Borgs.csv`. See [Borg Atlas](../borgs/)
for the per-borg HP bounds.
