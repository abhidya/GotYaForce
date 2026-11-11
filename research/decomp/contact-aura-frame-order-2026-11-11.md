# Contact aura lifetime across battle frames

## Proven source ordering

Read from the committed `research/decomp/ghidra-export/chunk_*.c` files, including
when these files are omitted by a sparse checkout (`git show HEAD:<path>`):

1. `zz_0029434_` runs `zz_0053a2c_` (actor update) at chunk_0003.c:4322,
   before `battle_frame_target_action_dispatch` at :4337.
2. The actor loop calls `FUN_80054070` (chunk_0006.c:6672-6687), which dispatches
   through the actor phase table (:6958-6968). The existing phase-table decode is
   in `cpu-ai-decode-2026-07-06.md` section 4; raw table bytes were not re-extracted
   for this change. Active-state wrappers call `FUN_80055568` (:7423-7468).
3. `FUN_80055568` calls `zz_0059068_` before its family/state handlers
   (chunk_0006.c:7778-7806). That status pass calls `FUN_8005a378`
   (chunk_0007.c:2104), which reads aura levels +0x70c/+0x70d into +0x768 and
   +0x5f4 (:2853-2898). `FUN_80067310` consumes +0x5f4 times +0x5f8 for position
   integration (chunk_0008.c:3787 onward).
4. The later `battle_frame_target_action_dispatch` clears +0x70c/+0x70d for
   all actors (chunk_0003.c:5949-5950), then runs contact passes (:6213-6215).
5. The contact resolver's flagsB 0x400 branch max-merges +0x70c and returns;
   its 0x800 branch writes +0x70d=1 and returns (:7653-7685).

The lifetime is therefore **contact N -> actor movement N+1 -> clear N+1 ->
contact N+1**. Neither aura branch writes a duration timer. The "300f aura"
phrase in `status-velocity-writers-closure-2026-10-20.md` is not supported by
these branches; it must not be used to add an aura timer. The discrete slow/haste
+0x710/+0x712 timers are different fields and remain unchanged.

## Port defect and bounded correction

Previously `Battle.step` called `stepHitStatus` (clearing aura levels) immediately
before the same actor's movement. Projectile contacts ran later. Every prior
projectile aura was erased before its movement consumer. A full Battle repro
with twenty confirmed synthetic slow-aura projectile contacts moved exactly the
same distance as a no-aura control, even though the aura level was written.

Battle interleaves each actor's movement and attacks, unlike the source's global
phases. Simply moving each reset after its own movement would make actor-phase
contacts depend on roster order. Instead Battle snapshots the previous contact
levels for **all** actors and clears all accumulators before any actor attacks.
The movement context carries that immutable frame snapshot. Contacts continue to
write the normal runtime fields, which become next frame's snapshot. This is a
narrow double buffer for aura levels, not a reordering of the entire battle loop.
`stepHitStatus(b, false)` avoids a second per-actor clear; the one-argument helper
retains its existing clear behavior for standalone callers.

Scope: only the existing ordinary, non-dashing horizontal movement multiplier
consumes this snapshot. ROM-owned movement, dash, vertical physics and animation
clocks are **not** newly integrated. This does not claim a complete live Tar Diver
emitter port, nor change hit resolver damage/knockback/resistance semantics.
This is **shared contact-lifetime plumbing with synthetic-contact integration
coverage**, not a completed Diver ability. The separate emitter audit found that
live Diver X still selects an ordinary kind-0 record (flagsB=0): `addRomProjectile`
ignores `spawnerAddr` and mode-votes kind 0 over kind 9. The actual kind-9 aura
child has source 0x801213bc / table 0x8032c6a0 and a separate follow-owner lifecycle.
That emitter selection/lifecycle work is explicitly outside this change.

## Regression evidence

`packages/combat/src/contactAura.selftest.ts` runs from the existing combat
lifecycle entry point, already included in `verify:contributor`:

- Real Battle projectile collisions with synthetic zero-damage aura records prove
  next-frame slow onset, five-frame continuous contact, expiration after the last
  carried frame, max merge in both
  overlap orders, haste onset/expiry, and both actor roster orders.
- Tests measure actual position deltas. Input geometry and initial velocity are
  reset to isolate the multiplier from acceleration history and unrelated hit
  knockback writes. They do not merely assert fields or a timescale helper.
- An actor-phase driver callback invokes the real `applyHit` writer before/after
  the victim's turn, proving same-frame isolation and next-frame retention in both
  orders. It restores only the unrelated hit velocity write to compare movement.
- Helper checks preserve burst slow immunity, freeze precedence, and standalone
  aura clearing.

Validation: `pnpm --filter @gf/combat test:lifecycle` passes. A semantic negative
control bundles the same tests with only movement's
`actorVelocityScale(b, ctx.auraLevels)` replaced by `actorVelocityScale(b)`.
All symbols/imports remain intact; it fails at the behavior assertion:
`prior contact slows the next movement frame ... got 5, expected 2.4`.
