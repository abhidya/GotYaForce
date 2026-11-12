# Opcode03 control-write audit

Audited browser main `862900fbc0c530b13eeb916657ef51859fa50134`.
No global runtime change is justified by this audit alone.

## Original contract

Original GG4E08 handler8004c488 is absent from the decompiled text. In-place PPC
inspection confirms an 84-byte (0x54) function through 8004c4d8:
- Advance the caller's stream pointer by8 regardless of mask.
- Gate all state/control writes on part mask bit2.
- Store descriptor bytes1/2 to actor1d0f/1d10 unconditionally. FF is NOT a
  no-change sentinel for those byte fields.
- Read u16 at descriptor+6. FFFF skips only the control-word update.
- Otherwise write `(old & 0xfffff00f) | (u16 & 0xff0)` to actor5e0.
  Original words54000726 and54000536 implement the two masks.

The current generic `rom/stream-vm.ts` opcode03 uses the wrong high-bit mask,
ignores the control sentinel, and does not gate its writes to selected part1.
These are valid isolated interpreter defects, but not the current live path.

## Actual browser reachability

Battle creates `RomDriverBridge`; its actor starts with both raw banks null.
Repository assignment search finds no non-null runtime bank assignment. The
only family assignment explicitly clears both. `startStream` invokes the host
scheduler then parks selected part pointers at `Number.MAX_SAFE_INTEGER`.
`tickPart` returns on null bank before generic opcode dispatch.

Therefore installing synthetic raw banks can prove the VM defect, but cannot
serve as evidence of a current real-input gameplay failure. Nurse, Beam and
Arrow tests already exercise bespoke source-control writes, not this opcode.

## Separate live fidelity gap

`scripts/gen-melee-anim-kinds.mjs` opcode03 extraction retains only part1 state
and auxiliary bytes. It discards the original u16 control operand, with a stale
comment claiming the VM applies it. `bridge.ts` decoded-event replay likewise
only writes state/aux, so there is no general replacement for that control write.

A future fix must preserve the original operand/sentinel, selected part mask,
source animation/wait ordering and replacement-stream ownership, then demonstrate
an actual family input regression. Applying a guessed control byte to every
flattened schedule would not establish parity and could disrupt existing moves.

## Decision

No generic VM patch was represented as a live gameplay unlock. No global
scheduler control change was made. Prioritize a bounded source-backed family
path or perform a separate extractor/timing audit before wiring shared behavior.
No original executable or asset bytes are included here.
