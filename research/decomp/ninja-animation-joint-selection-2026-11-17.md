# Ninja animation joint-selection evidence

Scope: GG4E, Normal Ninja (`pl0000`) and Sasuke (`pl000a`). This records
numeric facts from the user-supplied game image, not extracted game assets.

The original constructor at `8006f4f8` stores descriptor `802d3dc8` at
actor `+4b0`; for actor ID `0x000a` it stores `802d3ee0` instead. The first
`0xb0` bytes at both addresses have SHA-256
`57f57268eb4b7761258c288d68ef168657dcdc84599c8d5c47132275da0e253b`.
The constructor assignment was checked from the DOL instructions at
`8006f5c0..8006f608`; it is not a guess based on an adjacent family.

Both descriptors have signed boundary bytes `+0c..0e` of `11,20,20`.
Their first 20 signed joint-map bytes at `+8c` are:

```
2 3 4 5 6 7 8 9 10 11 12 0 1 13 14 15 16 17 18 19
```

Original setup copies the boundary bytes to actor `+1d91..1d93`.
`8004b8f4` uses those values for the first three channel boundaries; the
fourth range ends at actor `+1d90`. `8005380c` sets that count from archive
JOBJ traversal. `research/format-specs/mot-animation-format.md` records 20 JOBJ nodes in
`pl0000` model_00, and 23 AnimJoint nodes in its b00 animation tree. The
checked-in GLBs for `pl0000` and `pl000a` each have 20 named JOBJ nodes; this
is evidence about exported models, not a live actor measurement.

`8005380c` resets its counter between two `80067e18` walks and stores the
second count. `800419ec` creates both `+708` and `+788` banks by calling
`80007030` with the same model index; `80007030` loads a JOBJ root from that
model descriptor. This supports the two roots having the same topology, but
the identity of the runtime-selected model and the effects of subsequent
setup must still be verified. Do not yet treat 20 as a captured `+1d90` value
or assume the fourth range is empty.

The play instruction for Ninja ground/air X uses part mask `0xf` according to
`ninja-source-x-2026-11-12.md`; this requests all four channels, not an
unconditional assertion that the displayed GLB skeleton is an equivalent
source pose bank. Descriptor bytes `+42,+43` are `7,11`; their original
visibility stores occur after slerp. No physical-console validation or live
pose/geometry parity is implied by these static observations.
