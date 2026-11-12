# Collision HP gate audit

## Result

Do not add a generic one-hit-per-victim-per-frame gate to `applyHit`.
Actor+0x1da mask0x02 is conditional collision state, not a successful-hit latch.
The prior Beam audit's suggestion that ordinary overlapping pulses necessarily
need same-frame suppression was unsupported. Existing pulse identity deduplication
must remain separate from this flag.

## Checked source

All references are to `docs-site/public/chunks/` in this repository.

- `chunk_0003.c:7799-7827`, `resolve_hitbox_target_effects_and_damage`:
  target descriptor (`param_2+0x28`)+2 mask0x40 sets mask0x02 when actor status
  +0x5e0 mask0x01000000 is absent or mask0x10000000 is present. Non-borg
  targets instead consult their owner and additional conditions. A special
  projectile branch propagates an existing flag/status, not successful damage.
- `chunk_0003.c:7829-7831,8190-8191`: linked target/owner propagation.
- `chunk_0003.c:7945-7972`: ordinary HP calculation requires the flag clear OR
  target eligibility83 nonzero. Healing (attack flagsA mask2) has a separate
  branch, so an unconditional early return would also be incorrect.
- `chunk_0004.c:6672-6859`: damage calculation and HP application do not set
  the collision flag after a successful hit.
- `chunk_0003.c:6576`: `zz_002cda4_` clears the byte. Frame dispatch resets
  actors and object lists at 5923,5968-5977 before collision passes 5981-5986.
- `chunk_0003.c:7627-7632`: attack identity enters the victim's 48-entry ring
  before flag setters and HP application. `zz_002fd7c_` rejects repeated attack
  identities at 8453-8517. This is separate from the transient contact flag.
- Status/effect bookkeeping precedes HP eligibility; additional reaction and
  visual handling follows it. Suppressed HP does not mean discard all contact.

## Current port limitation and next safe work

`borgToCollisionActor` in `packages/combat/src/combat.ts` currently infers this
flag from host hit/down state. That inference is unsupported. This adapter is
currently audit-only: its HP mutations are not synchronized into live actors.
Changing that proxy alone therefore would not improve live gameplay.

A proper implementation needs actual defensive collision descriptor/status
bindings, linked owner handling, and contact ordering. Neither a host hit/down
state proxy nor a blanket frame cooldown is an acceptable substitute. The
ordinary Beam pulse path is intentionally unchanged by this audit.

No original executable bytes or assets are included. This is a static source
review, not an original-console trace or a claim of full collision parity.
