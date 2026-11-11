# Diver X source ammo binding and refill

## Recovered source contract

Committed C is in `docs-site/public/chunks/` (also readable using `git show`
when omitted by sparse checkout).

- `FUN_800562b8`, chunk_0007.c:60–100: the two stat-row segments map to ROM
  cells **0 and 2**, not 0 and 1. Its loop computes
  `(~-(countLeadingZeros(i) >> 5 & 1) & 2) * 8`, yielding offsets 0 and 16.
- The second segment initializes current at +0x784, companion at +0x786,
  timer at +0x788, and initial/max/type/parameter at +0x79c/+0x79e/+0x7a0/+0x7a2.
  `borgSourceStats.json` calls this segment `weaponSlots[1]`; that array index
  is not the ROM cell index.
- The raw `borg-hp-stat-rows-802f2988.json` and generated `borgSourceStats.json`
  agree: all 20 exported rows for pl0805/pl080d/pl080e carry
  `[initial=1, max=1, refillType=1, refillParam=1200]` in this segment.
- `FUN_80116944`, chunk_0031.c:3427–3483, calls
  `zz_006dbe0_(actor,2,1,1)` on the positive stream cue, before child create/refresh.
- `zz_006dbe0_`, chunk_0009.c:2866–2905, checks current >= cost, consumes one,
  and **adds** 1200 to the timer for refill type 1. Initiation itself does not spend it.
- `zz_006dcc0_`, chunk_0009.c:2909–2973, skips a cell when +0x597's corresponding
  bit is set or timer <= 0. Type 1 subtracts a rate from timer and sets current to
  max when timer <= 0; otherwise current is `max - (trunc(timer / param) + 1)`.
  This is integer ammunition derived from timer debt, not fractional grants.
  Negative timer overshoot remains, as in the source.

## Rate and frame order

`FUN_80055568`, chunk_0006.c:7788–7789, calls `zz_005568c_` (refill at :8058)
**before** `zz_0059068_` (rate rebuild at chunk_0007.c:2104). Thus refill consumes
cached +0x768; then the status pass rebuilds the following frame's rate.

`FUN_8005a378`, chunk_0007.c:2817–2900, rebuilds +0x768 from baseline 1,
known burst base 1.5, haste and eligible slow tables. Existing committed
`paramTierTables.json` contains these constants. Freeze replaces +0x5f4 and
+0x1dc8, **not +0x768**. Tier movement multipliers do not belong in refill.
Discrete slow/haste timers expire before the new rate is computed. Contact
inputs use Battle's existing immutable previous-contact snapshot, preventing
same-frame actor-order contamination.

+0x4a1 nonzero resets the base rate to 1. Only exact +0x4a0 role 2 copies a
partner's cached +0x768. A coarse nonzero carried flag is not proof of role 2.

## Bounded browser integration

For Divers only, browser X/HUD `weaponCells[1]` and source `weaponCells[2]`
reference the **same cell**. It is ticked once. Existing UI and X initiation
checks therefore read the charge consumed at the actual ROM cue. The source
refill lane applies only to this shared cell; B and every other family retain
existing policies. The satellite slot-2 path and morph descriptor initialization
are not exercised by Diver registration and are not globally remapped.

A denied Diver consumption is a valid no-payload outcome. The bridge records
that denial for that action only and does not latch its generic-X fallback.
Ordinary family fallback behavior is unchanged.

At unmodified baseline, the charge returns after 1200 refill steps following
consumption. Child life is 0x474 = 1140 frames, so a normal charge cannot refresh
that same child before expiry. A verified haste modifier permits overlap and
refresh; the old test's unconditional second deployment after 150 frames was
an artifact of the unbound/infinite cell, not a source contract.

## Explicit remaining limitations

- The extra burst refill multiplier `FLOAT_804376c8` is not in available committed
  exports. The source applies it in addition to the cached rate's known 1.5
  burst term. `UNRESOLVED_EXTRA_BURST_REFILL_MULTIPLIER=1` is an explicitly named
  neutral fallback, **not a decoded literal**. Exact burst refill timing is not claimed.
- Source pause-mask plumbing defaults to zero. The explicit +0x597 writer audit
  found no writer in Diver X phases, recovery, or stream VM. No pause is invented
  from being busy or from having a deployed child. Whole-actor zero-init is not
  established by that writer audit alone.
- `sourceAmmoSlowImmune` exposes the +0x5e0 bit0x1000000 condition; its upstream
  writers are not newly integrated. `sourceFusionRole`/partner-rate seams honor
  supplied exact state, but live fusion-role writers remain absent. A missing
  partner cache falls back to baseline, not a synthesized partner rate.
- Status levels outside the exported 0..3 tables use the existing port's clamping
  convention. No out-of-bounds retail memory behavior is claimed.
- Other families still use the preexisting tuned refill model. This change is not
  a global correction of all ammo slots, recharge modes, or burst/fusion mechanics.

## Regression coverage

`diverAura.selftest.ts`, run by `node packages/combat/scripts/run-lifecycle-tests.mjs`:
actual X initiation/cue timing for all three forms; one shared charge and immutable
HUD observation; repeated empty X; exact 1199/1200 baseline boundary with input
on the refill frame; baseline child expiry; haste-assisted real refresh; failed
cue allocation followed by a successful ROM retry; source pause bit2 versus
browser bit1; freeze exclusion; cached-rate status expiry/contact onset; explicit
fusion-role and partner-cache handling; unrelated family's tuned refill control.
Existing aura contact/cleanup tests remain in the same suite.

A semantic negative control restores only the generic refill call in an in-memory
bundle, retaining all imports. It fails `empty X refreshed or emitted generic
fallback`, demonstrating that the suite detects premature recharge.
