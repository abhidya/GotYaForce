---
title: Challenge Mode
---

# Challenge mode

Stage byte → arena name decoded. 18 named arenas total.

**Source:** `research/decomp/challenge-stage-naming-2026-07-05.md`

<StatusBadge status="observed" />

## What's proven

- Stage byte resolves through `MDT` unpack to a named arena.
- Spawn pools indexed by group id at `0x80380804` (80 groups).
- Borg anim strings remain resident between battles; stage archive strings do
  not. UI must warn when reading resident strings as evidence of active state.

## Evidence

<EvidenceCard
  claim="Challenge spawn pool table — 80 groups"
  status="verified"
  addr="0x80380804"
  file="research/decomp/data/spawn-pools-80380804.json"
/>

See [Stages](../stages/) for the arena atlas and [Force → Gotcha-Box](../force/gotcha-box)
for the drop mechanic.
