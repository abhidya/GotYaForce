# Double Ninja clone reaction boundary

This records the bounded source evidence used by the charged-clone draft. It does not claim that live collision aggregation or clone activation is integrated.

## Verified dispatch, not command-type inference

Original read-only inspection confirmed that constructor 8006f60c installs descriptor 8033af78 as actor4b0. Its byte+4 is zero, initializing actor591 to zero. This is a descriptor-selected reaction class, not the current command type584. Its gate table entry at 802d3580 is 8005c4a4, which invokes 8005f00c.

The checked-in older dispatch interpretation is not a reliable source for this lane: 802d35a4 minus 802d3570 is 0x34, or thirteen pointer slots, not nine. Fresh original pointer reads independently confirmed these reaction handlers:

- 1: 5c810; 2: 5c95c; 3/4: 5ca80.
- 5/6: 5cc00; 7: 5ce14; 8: 5d0a8; 9: 5d224.
- 18: 5dffc (healing); 20: 5e5a8; 21: 5e868.

Only the bounded classifier cases are implemented. The other entries are evidence for exclusions, not a claim of corresponding browser handlers.

## Ordered reset decision

The family post-dispatch function 6f88c clears arm7c8 when control5e0 has bit0x02000000. It leaves offset7b0 unchanged. The function was omitted from the local C export and was checked directly in the original.

For an ordinary first-entry Double reaction, raw1da bit0 first gates the collision tail. Admission then requires a depleted down gauge, or both raw6fd bits2 and0x80. The full source has further branches that the bounded classifier excludes. Function5c290 also requires nonzero6fd. Host hit/down state is not this admission test.

Function5f00c selects reactions1 through8. The upper selection bit depends on raw6fd bit2 or prior control bits0x02000040. Function5c694 then calls5c15c on first entry, clearing reset bit0x02000000 before the selected handler executes. Handlers5 through8 set it again in their first phase. Light handlers1 through4 can instead acquire it through5ee0c, whose5ef08 terrain probe checks whether resolved vertical displacement is less than negative actor674. Unknown terrain-probe results cannot be treated as a clear bit.

Healing is a concrete counterexample to clearing a clone on every browser down state. Source1da bit0x10 selects reaction18 and clears the bit; the host currently approximates that reaction as down. Repeated reactions, heavy/status overrides, paired states and alternate handler phases require separate proof.

## Integration still required

The original clears reaction accumulation once per collision frame, ORs accepted record reaction bytes into6fd, and adds0xa6 on balance depletion. Classification occurs after that accumulation. The browser applies reactions per hit and resets its down gauge immediately, so reading its final state would lose source evidence.

Live activation needs an ordered source reaction accumulator, rejection/deduplication handling and the actual owner post-dispatch hook. The classifier remains inert until those are supported. No blanket interrupt hook, arbitrary clone lifetime, second combat fighter or unverified damage threshold is introduced.

Sources: research/decomp/ghidra-export/chunk_0003.c collision reset, accepted-record and tail paths; chunk_0007.c functions5c290,5c694,5c15c,5f00c and the named handlers; original DOL pointer/function inspection. No original binary or asset payload is included here.

## Current classifier verification

The pure classifier explicitly requires completed frame aggregation, a living ordinary unpaired Double, descriptor class0, first-entry phases and an immediate dispatch opportunity. Healing/status/heavy overrides, existing reactions, falling-rehit history and unknown required terrain results return unsupported. A no-admission result preserves the prior reset bit; it is not a guarantee that the clone survives the later owner post-hook.

Tests sweep all256 raw reaction-byte values across admission flags, gauge boundaries, prior control bits and terrain results, plus every collision-flag override and heavy-byte value. The lifecycle aggregate and focused strict TypeScript check pass. These are source-boundary fixture tests, not live gameplay verification.
