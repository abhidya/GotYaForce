---
title: Anim-Coupled SFX
---

# Anim-coupled SFX

Per-animation sound-event table attached to each borg actor.

<EvidenceCard
  claim="Per-anim SFX event table"
  status="verified"
  addr="actor+0x4e8"
  file="research/decomp/anim-sound-op-decode-2026-07-04.md"
/>

Each animation frame can fire a sound-event op that resolves through
`research/decomp/data/combat-se-ids.json` to a SE id, which then streams from
ADX audio banks (see [Tooling](../tooling/) for ADX key brute-force).
