---
title: Save / GCI Format
---

# Save / GCI format

GameCube save image layout: section table, XOR scramble, keyed digest, CRC.

**Source:** `research/format-specs/save-gci-format.md`

<StatusBadge status="verified" />

## Layout

| Section | Purpose | Status |
|---|---|---|
| Header | Game ID, banner, section table | <StatusBadge status="verified" /> |
| Body | Force roster, story progress, options | <StatusBadge status="verified" /> |
| XOR scramble | Region-keyed byte transform | <StatusBadge status="verified" /> |
| Keyed digest | Tamper detection | <StatusBadge status="verified" /> |
| CRC | Final integrity check | <StatusBadge status="verified" /> |

## Color variants in save

Six color variants per borg (normal / alt / gold / silver / crystal / black)
are stored as flags in the roster section. See `save-gci-format.md:230`.

## Repo save files

- `*.gci` (3) — GameCube memory card images
- `*.sav` (5) — Dolphin emulator state files (distinct from GCI)

Dolphin `.sav` files are *not* memory card images; they are full emulator
state snapshots. Do not confuse the two columns.
