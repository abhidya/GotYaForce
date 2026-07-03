# ATK-010: Status-effect runtime shell (framework only, no effects)

## Purpose
Port the ROM's status FRAMEWORK (id, timer, immunity, application gates) so future
per-status tickets are data fills, not architecture. No status changes gameplay in this
ticket.

## Evidence
- Application: victim+0x71a = hitboxRecord[1] & 0x3f; timer victim+0x71c max-merged from
  record[4]; gates: immunity word victim+0x5a0 bit N, status-blocked 0x5e0 & 0x20000000
  (chunk_0003.c:7638-7651, corpus read, audit).
- Immunity bit also zeroes HP damage for that hit — ALREADY implied by formula step 1
  (behavior-notes (ah)); currently unmodeled in computeSourceDamage.
- Tick: +0x71c decrements 1/frame (chunk_0007.c:2881-2883).
- Param tier trio +0x74a/+0x74e/+0x750 already typed on BorgRuntime (types.ts:73-80).
- Findings mechanic Q; schema `attack-profile-port-schema.json#statusEffects`.

## Dependencies
None.

## Files to edit
- `packages/combat/src/types.ts` (BorgRuntime: `statusId: number` (0 = none), `statusTimer:
  number`, `statusImmunityMask: number`)
- new `packages/combat/src/status.ts` (`applyStatusFromRecord`, `stepStatus` — plumbing only)
- `packages/combat/src/combat.ts` (applyHit calls applyStatusFromRecord; battle.ts calls
  stepStatus)
- `packages/combat/src/damageFormula.ts` (optional param `victimStatusImmune: boolean` →
  returns 0, mirroring formula step 1; default false)

## Required behavior
- `applyStatusFromRecord(victim, statusId, duration)`: masked to 0x3f; rejected when the
  immunity bit is set; timer max-merge (never shorten a running status) — each rule cites
  its chunk_0003.c line.
- `stepStatus`: timer decrements to 0; statusId clears at 0.
- NO status has any gameplay effect yet — the shell only tracks state (render/debug may
  read it).
- DamageRecord/hit-record plumbing: today's 3 archetype records carry no status bytes, so
  applyHit passes statusId 0 — the parameter exists for future per-move records.

## Fallbacks allowed
- statusId 0 everywhere (no statuses fire) — that IS this ticket.

## Tests to add
- Apply status 5 for 60 → id/timer set; ticks to 0 and clears.
- Max-merge: apply 30 over a running 60 → stays 60.
- Immunity bit 5 set → application rejected AND (with the formula param wired) damage 0.
- Mask: id 0x45 → stored as 0x05.

## Do not change
- Stagger/gauge model, param-tier fields, reaction states.

## Done when
Shell tests pass; zero behavior change in existing selfcheck battles.
