# Nurse close-air X continuation

Extends the grounded close-allied route from PR #46 to airborne Angel Nurse,
Angel Rescue and Nao. Far-target homing, invalid-target fallback, exact animated
joint collision and exact reaction animation are still not implemented.

## Evidence

- `chunk_0011.c`, `8007bbe0`: close ground selects bank `802c2660` stream g4s2;
  close air selects g4s5. Both enter the same phases 1→5→6→8.
- Actual command records `802d6908` and `802d6910` are `[45,3,2,1]`:
  cue45, action2, variant1. Ground records are `[44,3,2,0]`.
- In-place GG4E08 ISO verification: s2@802c2bc2 and s5@802c2c36 differ only
  at byte31 (`00` vs `40`). Both play animation group4 slot2 with the same
  blend/park timing. Continuation s3@802c2bea and s6@802c2c5e are identical.
- Opcode03 handler `8004c488` is absent from the decompiled text. Original PPC
  confirms a `u16` load from descriptor+6, a `ffff` no-change sentinel, and
  `rlwinm` words `54000726` at8004c4bc / `54000536` at8004c4cc. These implement
  `(controlWord & ~0xff0) | (u16 & 0xff0)`, preserving all other bits.
  Thus air entry sets bit40, and ground entry clears it.
- `8007c4b8` stops motion at auxiliary6. If airborne, it uses the decoded20-tick
  timer instead of waiting for grounded auxiliary8. Both recovery branches
  explicitly choose stream g4s4, animation g4s3, end16. Its opcode03 clears40.
  The similar s7 descriptor sets40 but is NOT selected by this source route.
- Empty-ammo phase1 returns through the variant-appropriate idle/fall helper.

The implementation intentionally applies this verified control-word behavior
only to the Nurse path. It does not silently change the general stream VM,
whose existing opcode03 mapping needs a separate cross-family audit.

## Validation and limitations

Actual-input regressions pass for all three IDs using jump, held ally-lock and
X rather than forcing an airborne flag: cue45/variant1, entry40/recovery0,
healing while airborne at frame9–10, exactly20 ticks until airborne recovery,
ammo debit/refill, held/repress/tap, and interruption after HIT arming. Ground
and air cap/no-revive/empty-ammo/vertical-miss and far/enemy/busy negatives pass.
An isolated pre-change nurseX baseline fails the positive airborne tests for all
three IDs. No shared working files were changed for that negative control.

Full combat lifecycle, combat build, root typecheck and game build pass.
Contributor aggregate still stops at the existing three missing HUD assets in
this sparse checkout; every downstream stage was run separately and passes.
Original assets are not included. Deployment is recorded in the PR.

Source animation/HP/ammo rules are verified; browser root-sphere contact and
host airborne collision/fall remain approximations, not console-frame parity.
