# Third-pass canonical admission composition, 2026-11-14

## Scope and next boundary

This is regression and integration coverage of existing source-backed behavior.
It adds no production fallback, retail instruction implementation, constructor,
asset hydration, scheduler permission, or completed-frame claim.

The earlier zero-candidate fixture completes the primary and secondary null
stores but intentionally retains five inactive external physical records with
no command-admission owner. Its third-pass row 1 refusal is correct: source
`8006b360` unconditionally loads `actor+508`, even for an inactive actor. An
inactive-byte shortcut or default null would skip an observed retail read.

The new composition explicitly constructs five additional actors with the
existing registries. Each has its own mapping identity, actual actor, world,
status, attribute, charge, action, cue, dispatch, stream-start and stream
binding, all in the same runtimes as the primary actor. Admission receives an
explicit own-data `pointer508: null`; the canonical sealed binding copies the
input, rather than retaining a second pointer table. The allocator resolves
the same physical identity to that same actual actor.

The complete six-actor composition traverses all six third-pass rows and then
stops at the existing outer-frame refusal:

`80029460 reached mandatory80027764 normal-stage predecessor`

That is a later, explicit boundary, not success. Normal-stage predecessor
`80027764`, active nonnull third-pass work starting at `8006b374`, later stages,
and a completed outer/battle frame remain unimplemented on this route.

## Evidence and observable order

The derived [complete target-preparation report](target-preparation-evidence-2026-11-14.md)
authenticates the full 380-instruction, 1,520-byte `8006ae60..8006b44c` body.
This checkpoint uses its **Third pass: association flags and important read
order** section and does not obtain a new executable capture or read a private
archive. At each physical row the implemented prefix preserves:

1. Load the active byte at `8006b35c`.
2. Unconditionally load canonical `+508` at `8006b360`.
3. Test the captured active value, not a second read after the pointer load.
4. Skip an inactive actor without dereferencing a nonnull target.
5. For an active actor, skip a captured null pointer or stop before the
   unsupported nonnull continuation at `8006b374`.

Missing ownership stays a refusal. Binding one additional genuine actor
advances exactly one additional row, until all five extra records are bound.
The pre-existing sparse fixture is unchanged and still documents its earlier
natural refusal. The existing zero-candidate selector and null-direction
source stores run normally; the new tests do not replace their return values.

## Fixture limits

These are explicit synthetic host inputs, not reconstructed retail actor
construction. New actors are inactive and the mass table still has its
previously documented repeated primary identity. Distinct physical target
rows therefore do not prove a distinct six-actor mass-hydration path. No actor
frame claim is manufactured by the added owners. The scheduler is owned by
the real outer frame, and every test finishes in a source refusal.

The shared helper `createActorSecondaryNullTestFixture` selects the genuine
zero-candidate path and returns before running any outer frame. New owners and
the physical identity block are installed before its first execution. Source
methods, selector results and descriptor return values are not replaced.
Descriptor instrumentation records reads and injects explicit late faults in
adversarial cases; it always restores the intrinsic afterward.

## Regression coverage

`actor-third-pass.selftest.ts` is wired into the existing attached-setup
aggregate and exports a focused entry point. Its cases cover:

- Zero through five additional genuine owners, exact row/active/508 ordering,
  distinct canonical role records, exact allocator/world/status identity,
  sealed admission bindings, and unchanged frame-authority claims.
- Missing own `508` cells, explicit undefined cells, inherited initial cells,
  accessor and undefined first-bind inputs, and copied explicit input data.
- Inactive nonnull opaque, other-actor and readonly pointer cells. Unreached
  target/scalar accessors must never run.
- Active values changed after their load and pointer values changed after
  descriptor capture. The branch must use the value already loaded.
- Late actual-actor pointer aliases, attempted ownership by a second admission
  runtime, and caught outer-frame reentry at active/pointer reads.
- Retention of prior genuine mass writes, candidate scratch, four distance
  sentinels and primary/secondary vectors on failure; permanent incomplete
  frame state for retained physical actors; no later scheduler reads, group
  execution, root dispatch, or public access to a private active snapshot.

Validation uses the focused suite, strict combat TypeScript checks, the full
contributor aggregate, docs verification with model sync explicitly skipped,
matching/evidence tests, and oracle/codec tests. These are offline checks;
none constitutes browser, rendered-game, retail replay or completed-frame
validation.
