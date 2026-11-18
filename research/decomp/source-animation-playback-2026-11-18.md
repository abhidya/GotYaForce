# Source animation playback evidence

For Normal Ninja and Sasuke, a local probe read original GG4E PZZ member 3
in memory and hydrated the group 0 slot 0 and group 4 slot 0 DAT blobs through
the offline archive and descriptor owners. Each blob has 20 public roots; the
first root reaches 19 AObjs / 57 FObjs for idle and 20 / 60 for special. The
corresponding two variants' DAT blobs had identical hashes. A constructed
20-joint target matching the checked-in GLB hierarchy attached those AObjs to
joints 1–19 and 0–19 respectively. This is not a proof that exported hierarchy
or attachment matches original running-game state, and no game bytes were
added to the repository.

The first source-frame interpretation attempt refused eligible FObj opcode 4,
an actual missing spline interpolation lane. The bounded port now uses the
80255050 Hermite instruction order for opcodes 3–5. A controlled Dolphin
JIT64 experiment directly called 80255050 with 48 sets of float32 inputs;
all 48 results matched the candidate bit-for-bit. This is sampled emulator
evidence, not physical hardware or full opcode/pose parity. Source arithmetic
assumes nearest-even and gradual-underflow behavior. The isolated emulator was
stopped, leaving the unrelated existing instance untouched. Original-data
frame playback and the playable renderer remain to be verified.
