# ATK-009: ROM-shaped ammo/refill model (weapon cells + refill types)

## Purpose
Replace the single TUNED ammo pool with the ROM's weapon-cell model: per-weapon cur/max,
refill type (gradual / all-at-once / deploy-return), shared refill-rate, infinite-when-max-0.
The mechanism is fully ROM-evidenced; only some values remain to extract.

## Evidence
- 3 weapon cells init from the stat row (cur/prev/timer at +0x774/+0x77c/+0x784 stride 8;
  max/type/param aux cells from +0x78c): chunk_0007.c:60-94 (corpus read, audit); row source
  zz_0055f90_ @0x80055f90, weapon-0 values already extracted per borg in
  `research/decomp/data/borg-hp-stat-rows-802f2988.json` (G RED ammo 5 live-verified,
  behavior-notes (ag)).
- Fire gate `zz_006dbe0_` @0x8006dbe0 (cost check, dry-run, decrement) chunk_0009.c:2866-2905.
- Per-frame refill `zz_006dcc0_` @0x8006dcc0 chunk_0009.c:2909-2973: type 1 gradual
  fractional grant; type<=0 all-at-once on timer expiry; per-weapon disable bits +0x597;
  burst (+0x6fc) multiplies the rate.
- One-shot grant `zz_006de10_` @0x8006de10 (deploy-return, +1 clamp max); deploy handlers
  restore to max (chunk_0029.c:2270-2301).
- Infinite ammo when max==0 (chunk_0002.c:7158-7165).
- Full model: findings mechanic P; `attack-profile-port-schema.json#refillMode`.

## Dependencies
None hard. Coordinate with ATK-011 (burst flag will feed the rate multiplier later).

## Files to edit
- `packages/combat/src/types.ts` (`BorgRuntime.ammo` → keep as weapon-0 alias for compat;
  add `weaponCells: { cur; max; refillType; refillParam; timer }[]`)
- `packages/combat/src/combat.ts` (replace the reload block combat.ts:541-546 and
  `startShotAttack` decrement with cell operations; add `stepAmmoRefill(b)` called from
  battle.ts)
- `packages/combat/src/actionProfiles.ts` / `stats.ts` (source ammoMax/refill values from
  the extracted stat rows where available; keep profile values as fallback)

## Required behavior
- Weapon 0 drives the existing shot path (B); cells 1/2 exist but are unused until the
  command resolver lands (document this).
- Refill semantics per type: gradual = timer-driven stepwise grant toward max;
  all-at-once = cur stays 0 until timer expiry then cur=max; deploy-return = exposed
  `grantAmmo(b, weaponIdx)` helper (nothing calls it yet).
- max==0 → firing never blocked, no decrement below 0 weirdness.
- EXACT per-frame rate: the ROM rate float's init (+0x768) is unresolved (open-questions
  Q7) — model the rate as a named constant `AMMO.REFILL_RATE_PER_FRAME` labeled TUNED with
  the Q7 citation, defaulting so that behavior approximates the current reloadFrames feel.

## Fallbacks allowed
- TUNED refill rate constant (labeled, cited).
- Borgs missing stat-row data keep their current actionProfiles values (labeled fallback).

## Tests to add
- Gradual borg: fire to empty → ammo climbs stepwise; firing allowed as soon as cur ≥ 1.
- All-at-once borg: fire to empty → cur stays 0 for the full timer → jumps to max.
- Infinite borg (max 0): 1000 shots, never blocked.
- `grantAmmo` clamps at max.
- Regression: a default borg's shots-per-minute stays within the pre-change envelope
  (compare against an ATK-002 baseline).

## Do not change
- Damage records/formula; projectile spawning beyond the ammo source; charge-shot logic.

## Done when
All vectors pass; selfcheck green; TUNED markers added to `research/tuned-burndown.md` on
the next report run.
