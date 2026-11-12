# Nurse far allied X continuation

This lane extends the close-ground/air implementation to valid allied targets
that select the original far branch. It also corrects an earlier interpretation
of the source recovery condition. No original assets are included.

## Original route

`chunk_0011.c`:
- `8007bbe0`: same resource-cell-2 allocation and facing setup, branch to g4s0
  for distance >=500 or failed close vertical band.
- `8007be08`: far admission sets scalar speed and acceleration to1.
- `8007bf70`: seed motion from actor matrix third column (+8dc/8ec/8fc),
  advance authored stream, seek target with helper8006c1c8, integrate80067610.
- `8007c19c`: seek target aim minus93.69000244140625 in Y, hold the current
  animation/HIT frame for the30-tick seek timer, react to actual contact.
- `8007c350` / `8007c6b0`: recovery and exit. `8007bb6c` caps speed at30 after
  every phase handler, not before its movement calculation.

The normal actor matrix is translation × Rz × Ry × Rx × scale, built by
80046bd0. Its third column is actor forward, not animation translation.
The alternate animation-root concatenation path is not assumed here.

## Authored streams and values

Bank802c2660: g4s0@802c2b36, g4s1@802c2b8e.
- s0 arms HIT kind3, plays animationg4s0, then mode2 waits14,21,22,32.
  Part0 auxiliary events are9,10,(weapon selection1),1.
- The kind0/subtype1 opcode0a at frame21 is NOT a disarm. Source8004c6b4
  changes the hit selection only when kind>0; its subtype writes are separate.
- The family stops ticking s0 in seek phase3, retaining the authored HIT pose.
- s1 recovery plays animationg4s1, weapon selection3, and mode3/value10
  signals completion. It is not the full26-frame animation-end wait.
- Hit kind3 maps to source healing rows3/7, preserving200/400 allied HP.

Fresh original-DOL values:
- Turning multiplier8043768c=0.01745329238474369; cap is10 degrees per helper
  call, not multiplied by frame delta.
- Drift epsilon804375f4=9.99999905104687e-09; floor804375d0=0.
- Recoil slope80437978=0.699999988079071; speed8043797c=8;
  state timer80437980=80.

Nurse-local motion helpers preserve all XYZ components and write the normalized,
scaled displacement back to motion. The older shared drift compatibility helper
omits Y and is intentionally not changed globally in this lane.

## Contact-condition correction

Source actor+1d9 is an attack-contact latch, NOT grounded state. Normal-borg
contact sets0x10 in `chunk_0003.c:7589`; `zz_002cda4_` clears it each collision
cycle. Duplicate attack-history checks precede the contact resolver, so standing
overlap must not refresh it after a duplicate rejection.

The bridge receives the signed result of the actual hit resolver. An accepted
healing contact (including an already-full target) reports a negative record
amount; rejected contacts reportzero. It passes a one-step contact observation
back to the Nurse family rather than inventing sticky contact-until-recovery.
Close recovery tests the signed contact byte at its auxiliary6 decision. The
20-tick path is no-positive-contact, not inherently airborne. A positive contact
at that decision waits for auxiliary8. Exact console collision-cycle/frame
sampling remains a verification gap; an earlier successful heal does not by
itself prove the later decision must observe a positive latch.

## Validation

Passed final root typecheck, full combat lifecycle and game production build.
All post-HUD contributor stages pass separately; the aggregate still stops at
three existing missing HUD images in this sparse checkout. Oracle: 81 pass,
zero fail, one expected private-snapshot skip. Matching tools: 52 tests pass.

Actual-input coverage includes all three Nurses, ground and real-jump air:
far-700 movement, kind3 healing, one-charge debit/refill, interruption, target
loss, repeated/held/tap input and empty ammo. Moving the same ally sideways after
admission makes the path bend and reach contact while retaining captured identity.
The controlled target relocation is fixture setup, not claimed player movement.

The real-input test uses synthetic traversable triangles through the actual
stage collision pipeline, not a disabled collision guard. A floor-edge case
prevents crossing an unsupported edge or healing a distant target. This is
deterministic integration coverage, not authored-stage visual QA. Identical
fixtures against the prior runtime fail all six far cases without healing or
spending ammo. Separate isolated controller tests distinguish positive-contact
HOLD60 from no-positive-contact timer20, without making the latch sticky.

## Remaining limits

Original target-marker and animated collision transforms are still approximated
by host roots. Source pitch tilt/damping (+18da), weapon selection 1/3, FX1c,
afterimage calls and movement-mode bytes are not rendered/wired in this lane.
The initial basis uses heading/body pitch, not full roll/scale (uniform scale
cancels during normalization). The host floor guard is not the complete original
phase3 floor probe, and JavaScript double arithmetic is not full PPC rounding. Homing math and source event ordering do not establish full
trajectory or visual parity. Enemy/invalid initial-target fallback remains
unsupported. Final verified tests and deployment are recorded with the PR.
