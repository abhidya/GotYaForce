# Bounded positive primary target distances

The nonnull-primary branch in genuine `8006ae60` now admits model-backed
`frsqrte` estimates at `8006afbc` and `8006b03c` for the **actual computed**
squares `.25, 1, 4, 16, 64` only. The existing zero path is unchanged. This is
not a general square root, hardware parity, or completion of a battle frame.
The branch always stops before the mandatory `8006b098 → 8006d228` helper.
No flags/team logic at b09c, secondary preparation, later actor, or later pass
is reached on this branch.

## Retained evidence and source schedule

No new payload selection, raw payload read or extraction was used. The retained
`.tmp/target-preparation-evidence-20261114/operands.json` and
`target-preparation-evidence-2026-11-14.md` supply the instruction operands.
`positive-secondary-distances-2026-11-15.md` documents the same authenticated
constants, independent exact binary64 refinement witnesses and model-backed
five-seed domain reused here.

- afbc estimates f2 from actual square f1; afc0 loads half into f4, afc4
  loads three into f3. afc8–afd4, afd8–afe4 and afe8–aff4 each perform
  q=e×e, h=half×e, c=−fused(s×q−three), e=h×c in binary64. The third
  result goes to f0. aff8 multiplies square by estimate; affc rounds to
  float32; b000/b004 store and reload stack+14; b008 stores actual+758.
- b00c freshly loads zero. b010/b014/b018/b01c load A.x, captured OBJECT.x,
  A.z and captured OBJECT.z. b020/b024 perform separate fsubs; b028/b02c
  perform separate fmuls; b030 performs fadds into f4. No GQR load occurs.
- b03c estimates f1 from f4; b040 loads half into f3, b044 three into f2.
  b048–b054, b058–b064 and b068–b074 repeat the same three dependencies.
  b078 multiplies; b07c rounds; b080/b084 round-trip stack+10 into f4;
  b088 stores actual+75c. Only then does b094 freshly load508.

The helper shares the exact binary64 dyadic arithmetic used by secondary
estimators. Independent seed/round/product/frsp bit tests cover all four PCs.
Two rounds already match final float32 for this domain, and nonfused correction
or some reassociations can coincide even at intermediate values. Intermediate
bit witnesses and the explicit source schedule, not final-value mutation
claims, protect the three-round and fused instruction ordering.

## Live inputs and partial writes

The initial508 selects only the branch. The separately captured504 continues
to identify the original allocation-owned OBJECT+64 even if504 changes.
Actual position components and OBJECT bytes remain live at every source load.
The same root processor used for genuine8020bc88 supplies both estimators.
FPSCR control and half/three are optional until a positive estimator is reached;
there are no constructor defaults. Controls require explicit RN00/NI0 with
floating exception enables disabled; status bits are not emulated or changed.

Unsupported total square or total estimator controls/constants leave758/75c
untouched. Failure after758 preserves758 and leaves75c untouched. Failure at
fresh508 or the mandatory6d228 boundary preserves both stores. All refusals
retain earlier genuine selector/mass writes and permanently close the caller.

A dedicated native-descriptor terminal primary guard runs after public metadata
observers before either store, without requiring unrelated c8, cc, aimOrigin518
or null-primary direction state. It verifies canonical actor/admission/data,
position and processor declaration ownership, captured provider identity,
new provider aliases, distance and constant aliases, lifecycle and reentry.
The initial provider-reference snapshot is native metadata taken before the
504 source load, so callbacks during504, position admission, GQR or square
components cannot bless a newly added provider alias as an initial reference.
This snapshot neither resolves nor reads B before its first actual paired load.
The destination descriptor is reread natively immediately before overwrite.
Legitimate distance fields on other actual actors are not competing storage.

## Regression coverage

`runActorPrimaryPositiveHydratedCompositionTests` is wired into attached setup.
It exercises all five squares at both estimators, zero/positive combinations,
multi-component actual norms, adjacent unsupported computed values, live
horizontal changes, captured504 replacement and fresh508, lazy constant and
control faults, destination/read-only/accessor faults, late aliases, lifecycle
and reentry, and replay of each final public observer before both stores.
Existing primary zero/null/refusal and secondary positive suites remain gates.
These are explicit synthetic genuine-runtime graph fixtures, not retail actor
hydration or a console capture.
