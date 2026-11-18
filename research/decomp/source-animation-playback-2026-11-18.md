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

## Original-game joint rotation comparison (2026-11-18)

An isolated Dolphin JIT64 instance ran the original GG4E game with two Ninja and two Sasuke actors. At the `HSD_JObjAnim` return boundary (`8004b76c`), the capture read each animated joint's three raw float32 rotation components and its AObj frame. The per-public-root offline playback evaluated original group 0, slot 0 data against a host-created 20-joint hierarchy. At frame 17, all 19 animated joints matched on all four actors (228/228 float32 words); at frame 18, all 19 joints matched on one captured actor (57/57 words). Total: 285/285 sampled rotation words.

The clip identity is inferred from this match and the investigated setup, not independently observed from the live selector. This is bounded emulator evidence for rotations, not an exhaustive animation test, translation/matrix comparison, physical-console proof, or playable-game visual parity. The original archive was read locally in memory and was not copied into this repository. The isolated emulator was stopped without stopping the pre-existing Dolphin instance.

## Playable idle rotation correction

The existing Ninja and Sasuke group-0 slot-0 baked clips were compared with the captured local JObj rotations at frames 17 and 18. Converting the captured Euler rotations with the existing exporter's rotation convention exposed 24 of 38 sampled joint poses per variant differing by more than 0.001 radians; the largest observed difference was about 1.637 radians. This comparison assumes that the original joint-table index corresponds to the exported `JOBJ_n` index; it is not a full rendered-scene comparison.

The rotation tracks for joints 1–19 were regenerated for all 121 frames using the composed source playback runtime and the locally supplied DAT with SHA-256 `78208675afecbddd89dd9b506d2bf43b31a6539e3aaa58ce517b44a7f293271b`. The reference clips' root rotation, translation and scale tracks are preserved. `scripts/bake-ninja-source-idle.mjs` reproduces this limited conversion from a user-supplied matching DAT. The checked-in numeric witness and `scripts/check-ninja-idle-source-witness.mjs` compare the two sampled frames for both variants (76 joint poses). Source clip selection remains inferred, other frames and translations are not independently compared with the original, and no WebGL visual parity is claimed.
