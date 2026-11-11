# Hit-inflicted drain status: bounded browser integration

The timer previously cited as vampire passive bleeding is not evidence for that
attribution. The cited source is a victim status countdown, with a direct hit-record
writer. Vampire lifesteal remains separately supported and unchanged.

## Source evidence

- `docs-site/public/chunks/chunk_0003.c:8121-8127`: damage flagsA bit `0x100`
  writes victim `+0x6ba` to `0x0258` (600 frames). The enclosing branch requires
  victim `+0x6fc == 0` and `+0x4a0 == 0`; an existing timer is refreshed.
- `chunk_0003.c:7780-7788`: victim resistance `+0x59c & 0x100` blocks the effect.
- `chunk_0003.c:8087-8091`: the effect writer also requires a non-255 impact
  effect ID and the normal hit-reaction gates.
- `chunk_0006.c:7899-7911`: while lifecycle bytes `+0x18 == 1` and `+0x19 == 2`,
  decrement the nonzero timer; if its new value is divisible by 30, subtract
  one HP only when HP exceeds one. Zero therefore receives the final tick.
- `chunk_0007.c:1252-1253` (`FUN_80058244`) initializes this active lifecycle.
  Action hit/down states are distinct from these lifecycle bytes.
- `chunk_0003.c:7952-7967`: healing-contact flagsA bit `2` reduces an existing
  drain timer to one, not zero. That contact-healing route is not implemented
  by the live browser `applyHit` path. This patch does not pretend to add it,
  and does not make general healing or vampire lifesteal cleanse the status.

## Browser scope

`hitDrainFrames` represents the countdown independently of cooldown counters.
Battle ticks previous-frame status before any actor attacks, so actor-list order
cannot subtract a frame from a newly applied status. Spawn/death/departed actors
pause; active hit/down reactions still tick. Application checks the existing
paired-burst lane (`burstPaired`, corresponding to `+0x6fc`) and carried role
(`sourceFusionRole`, with the established boolean fallback for `+0x4a0`).

The application path is intentionally bounded to exact committed family-record
objects for Venom Worm (`pl050b`) and Poison Worm (`pl0517`), indices 0, 2, 3, 4,
with non-255 impact effect IDs. These are clean source rows with flagsA `0x101`
and flagsB zero. Other families contain apparent table-extent overshoot records
with the same flag; the bit alone is insufficient provenance. This does not claim
that every poison cloud or every source collision gate has been ported.

The dormant vampire-only counter path is retired as a compatibility no-op. Its
old counter never progressed in normal Battle stepping because generic cooldown
decay canceled each increment. Enabling that counter would have introduced an
unsupported permanent drain rather than fixing the sourced status.

## Verification

`hitDrain.selftest.ts`, included in the combat lifecycle suite, uses actual Battle
B attacks for both Worms and repeats Venom Worm with reversed actor order. It
checks 600-frame seeding, no early loss, first loss after 30 frames, 20 total HP
lost through expiry, and no further loss. Additional cases cover refresh,
paired-burst/carried-role/resistance rejection, final tick, one-HP floor,
inactive lifecycle, and actual Battle controls with two vampires and a non-Worm.

No new visual effect, Windows memory dump, healing-contact implementation, or
cloud collision geometry is claimed.

A semantic negative-control bundle omits only the 600-frame writer, preserving
imports and all other behavior. The actual B test fails with `pl050b actual B
never seeded drain`, rather than failing to compile. Healing regression checks
pass 44/44; broader lifecycle, typecheck, ROM, menu/session, input/pause, camera,
Challenge, disposal, import and production-build checks pass. The oracle regression
suite passes 81 tests with one expected private-MEM1 skip; this is not an independent
retail-runtime comparison. Local contributor aggregate remains blocked only on
three HUD images omitted from this sparse checkout.
