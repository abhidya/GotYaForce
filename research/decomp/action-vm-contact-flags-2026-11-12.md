# Action VM contact flag byte correction

Local-only follow-up to `gred-family-crash-2026-11-12.md`. This repairs the generic
stream interpreter's actor byte at +0x709, not the specialized G RED family clocks.
No original assets or executable bytes are included.

## Verified source behavior

Original GG4E08 `FUN_8004c75c` gates opcode 0x0b on part mask 0x2. A nonzero
operand byte1 sets the byte2 mask (OR at 0x8004c784); zero clears it (ANDC at
0x8004c798). Both paths advance the instruction by four bytes. The host walks
individual parts, so only part index1 applies the write; other parts still advance.

`zz_004beb8_` in rea `chunk_0006.c:1441–1444` intersects the requested part mask
with actor +0x579 and clears +0x709 if the effective mask includes 0x2. This occurs
before bank lookup, including absent or invalid stream paths. The host reset now
also precedes `onStartStream`, preserving any subsequent authored startup writes.
Source was independently checked against the original PPC during the preceding
G Crash investigation and reconfirmed for this bounded change.

## Scope and limitations

The existing dynamically attached `contactFlags` backing is now an initialized
RomActor field. Generic opcode0b previously reversed set/clear, wrote from any
part, and omitted the start reset. All three are corrected. Unrelated bits survive
masked writes and results remain an unsigned byte.

A repository TypeScript consumer audit finds no gameplay reader of this generic
field. Specialized G Crash, melee, and beam routes retain their separate, already
admitted source shadows. This change therefore establishes correct interpreter
state; it does not claim a visible damage, hitstop or collision effect. Connecting
consumers requires independent source evidence. Opcode0c, other part gates,
shared-bank selection and generic wait/animation semantics are not changed.
No full-game or whole-interpreter 1:1 claim is made.

## Verification

`stream-flags.selftest.ts`, called by the existing ROM aggregate, checks 160
set/clear input combinations, all four part gates, 32 combinations of requested
mask/permitted mask/bank availability, invalid-stream reset, host callback ordering,
and a sequential set/clear script dispatched across all four parts. Tests exercise
public `startStream`/`tickStream`, not a duplicate helper implementation.

Full `verify:contributor` passed after the correction: repository policy,
TypeScript, frontend/session/input/Challenge gates, renderer checks, ROM aggregate,
combat lifecycle regression suite, importer checks and production build. Only the
existing bundle-size warning remains. Independent source review found no blocker
in this scope. This checkpoint remains local and has not been deployed.
