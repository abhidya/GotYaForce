# Null-descriptor display animation attachment

Source audit: 2026-11-13. Evidence is the checked-in Ghidra export, not an
original-execution capture. No original asset, process, network source, or
production activation was used for this audit.

## Reached caller and final joint gate

`research/decomp/ghidra-export/chunk_0006.c:695–699` shows `8004adc8` invoking
single `HSD_JObjAddAnim` with null material and shape descriptors. This is not
`HSD_JObjAddAnimAll`; AnimJoint child/next traversal is not required here.

`chunk_0071.c:3989–4032` conditionally replaces the joint AObj, promotes track12,
calls RObj attachment, and sets/clears flag8 when the AnimJoint is non-null.
The display tail is outside that condition: a null AnimJoint still reaches it.
At `:4033–4049`, the function reads the current joint flags and calls
`HSD_DObjAddAnimAll` with the current DObj binding if `(flags14 & 0x4020) == 0`.
Do not cache either flags or binding before prior attachment effects. When the
gate is closed, do not resolve or inspect the DObj list.

## Actual null/null DObj behavior

`chunk_0069.c:6239–6287` (`8023d838`) implements the display-list attachment.
For each non-null DObj, with both descriptors null:

1. The shape animation argument remains null (`:6256–6257`).
2. Read DObj+0x0c and call the PObj helper with that target and null descriptor
   (`:6262–6265`).
3. Read DObj+0x08 and call MObjAddAnim with that target and null descriptor
   (`:6266–6269`).
4. Read DObj+0x04 to select the next DObj (`:6271`). Both descriptor cursors
   remain null (`:6272–6282`).

The PObj helper's export name, `HSD_PObjRemoveAnimAll`, is misleading. Its actual
outer guard at `chunk_0071.c:1447` requires both target and descriptor non-null.
With a null descriptor it neither follows the polygon list nor reads/removes
its existing AObj. The removal/loading body at `:1450–1460` is unreachable.

Likewise `HSD_MObjAddAnim` has a target-and-descriptor non-null guard at
`chunk_0070.c:1212`. With null descriptor it does not inspect the material AObj,
remove/load it, or call texture attachment (`:1214–1229`).

Consequently, null/null attachment preserves every existing PObj/MObj AObj and
FObj lifetime. It also leaves DObj AObjs untouched. Reading DObj's PObj/MObj
link fields is required; resolving those linked objects or walking their
descendants is not. Null-descriptor early returns may be implemented directly
as the proven source behavior, not as permissive stubs for non-null descriptors.

## Ownership boundary

Use the existing `SourceDObjAnimationRuntime.getDObj` identity owner and its
`next04`, `pobj0c`, and `mobj08` records. Do not construct a second display graph.
A bounded owner can admit only the null-material/null-shape path, with cycle,
visit-budget, owned-record, synchronous-call, and caught-reentry checks as host
limits. Validate fields when reached, in the order above. Read-only source
fields do not require writable destinations: this path performs no stores.

The JObj attachment owner may receive this dependency optionally. If the
dependency is unavailable and an eligible non-null DObj list is reached, retain
the explicit refusal. Null lists and gated lists need no new capability.
Failure on a later DObj must retain the earlier completed JObj removal,
allocation, binding, track-order and flag effects; no rollback is implied.

## Composition and review requirements

- Compose packed DAT hydration, actual archive lookup, opcode01 setup, JObj
  replacement, request and playback with the same existing display owners.
- Exercise multiple DObjs and non-null PObj/MObj AObjs. Attachment must retain
  their identities and lifetimes, including across repeated joint replacement.
- Distinguish attachment preservation from later request/animation effects.
  Existing display playback must perform real work or refuse unsupported
  reached receiver behavior; attachment admission does not authorize no-ops.
- Test a null AnimJoint, both gate bits, fresh final flags/binding, a missing
  optional dependency, and late invalid/cyclic/out-of-budget DObj traversal.
- Test that unused DObj AObj/callback fields and nested PObj/MObj records are
  not inspected during this tail. Preserve source read order without eagerly
  snapshotting the whole list.

This slice removes one refusal for display-bearing joint setup. It does not
hydrate models, implement non-null display attachment, infer actor joint-bank
mapping, provide original assets, complete world matrices or display receivers,
or select exclusive Battle lifecycle and source-pose presentation ownership.
Synthetic tests cannot establish original-input or live production parity.
