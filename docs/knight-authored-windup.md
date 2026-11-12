# Sapphire/Ruby Knight X windup: bounded timing repair

The old bridge completed decoded streams at max emitted event frame + 1. The
Knight windup only emits frame-zero setup: that shortcut released X after one
frame instead of waiting for its authored local-animation threshold.

## Verified input

Read-only numeric inspection of retail DOL SHA-256
`21454a8880c6254616662710d6ec626e43d853999da2cdfad700030960a94836`
confirmed pl0208/pl020e action 2 variant 0 bank `0x80300420`, g4s2 stream
`0x80300c6c`. No assets were copied. playAnim selects g4s1, mode 1, blend 4,
signed +5=0 (preserve inherited action multiplier), signed +6=0 (local start
frame). Then part 0 state/aux=0/0, part 1 state/aux=0/1, terminal wait flags 3, value 30.

References in research/decomp/ghidra-export:
- chunk_0006.c:1609–1685, FUN_8004c298: playAnim operands and inherited rate.
- chunk_0005.c:4334, FUN_800487ec: mode 1 initializes local frame 0, blend elapsed to
  animation advance, duration blend+1=5, updater state 1.
- chunk_0006.c:90–118, FUN_8004a00c: local clock holds during blend, then adds
  overshoot. Updater table 0x802d0d84 is [80049f10,8004a00c,8004a0e0,8004a1cc,
  8004a2ec]; state 1 resolves through 0x802d0d88.
- chunk_0006.c:2039–2110: wait flags are bits, not enum modes. Mask 0x2 compares
  local frame to threshold; mask 0x1 marks terminal completion. Check occurs before
  animation advance; completion is visible before returning to the family.
- chunk_0019.c:1856–1941: setup starts g4s2; next phase ticks it, consumes
  completion, starts continuation, allocates ammo cell 2 and calls 0x800e19a8.

## Runtime scope

Only the verified borg/action/variant/bank/group/slot gets per-part local clocks.
Immediate setup is followed by a wait checked inside actual family tickStream
calls. At neutral advance 1, local frame 30 is reached after 34 advances, completion consumed on
call 35. Terminal wait executes no following data. Pending owned waits bypass the
legacy watchdog. Overlapping replacements revoke ownership even in the same
bridge frame; interrupts/new actions clear schedules. Other schedules/raw VM
wait modes remain unchanged.

This is not full animation-rate parity: live advance remains neutral 1. Source
+1dc8 combines tier animation, action and status multipliers (freeze .03); that
binding is not implemented. Fractional/held helper tests establish only the
clock arithmetic, not live binding. Global decoder +5/+6 metadata is still
missing; no generic rate/start-frame inference or wait-value wall-frame hack
was introduced.

Battle-created real-bridge tests verify no early consume/release, exactly one
allocation/release and one Battle projectile at tick 35, immediate setup, repeat,
interrupt and mask replacement. Source ammo cell 2 is infinite here (maximum 0), so
allocation-call count rather than fictitious decrement proves the boundary.
Battle still routes the Knight callback through its general per-borg shot
resolver. A projectile appearing at the corrected boundary does NOT establish
source Knight contact/beam child identity, geometry, damage or visual parity.
