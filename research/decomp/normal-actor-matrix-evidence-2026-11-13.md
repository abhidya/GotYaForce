# Normal actor matrix caller evidence, 2026-11-13

## Supported next boundary

The existing local ProgramDB snapshots support the explicit `800465fc` caller,
including real damping through `46e7c -> 46ef4`, a genuine no-entry `46914`
second traversal, `47904`'s early-return guards and `47a2c`'s matrix copy loop.
This does not establish full terrain correction, nonempty IK, the active
`47904` body, production lifecycle wiring or original-game replay parity.

The unsuppressed dispatcher also reaches the real damping handler: selector
`actor+1d98 & 0xf == 1` selects `80046ef4`. It must not be refused merely
because `controlWord & 0x20000000` is clear. For example, explicit metadata byte
`0x11` selects this damping handler and later selects `47904`'s high-nibble
early return. This is a source-supported input combination, not an inferred
default or proof that a particular retail actor uses it.

## Authentication and reproducibility

Reader: `research/tools/matching-decomp/read_archived_normal_matrix_evidence.py`.
Synthetic tests: `test_archived_normal_matrix_evidence.py` in the same folder.

The reader reuses the existing full-snapshot SHA allowlist, ProgramDB schemas,
import metadata, empty File Bytes check, address mapping checks, complete data5
digest and constant controls. It also checks the exact text1/data3/data5 block
and subblock mappings. It reads only the six fixed text spans below, one
64-byte selector window and one binary32 constant. It emits hashes, physical
traces, selected decoded instruction fields and selector targets, never raw
ranges. It has no arbitrary-address CLI and does not execute archived code.

Both existing snapshots under
`research/decomp/GotchaForce.rep.before_force_create/idata/00/~00000000.db/`
produce matching span hashes, instruction facts, selector targets and constant:

| Start | Bytes | SHA256 |
| --- | ---: | --- |
| 800465fc | 156 | 7ed4ac7350606317cb9c955ccda304c0989e84dfa9b16052184c41b33a5be24f |
| 80046914 | 700 | f794718b565c7444fe476be643a4197ee99f44ff47f5d775696a176f10249ebc |
| 80046e7c | 120 | 0d3af7347d1335ae1992342a6a7b467fcb746d25c904521df36b9e89fd4d6d0f |
| 80046ef4 | 20 | 75237b79ca27cfc01aa947b9665ecc81cbbc352c54deb64ae070a80599518717 |
| 80047904 | 296 | 79704ea5e729833d36b5d4bb4164d21d3711b0db9e51b63a6bbef9da0ffda41e |
| 80047a2c | 120 | f8d3960587cdf2e650b9b3f0fa621b411eba9611eb2acc0a6ceb2ba22c73dd1c |
| 802d0d60 | 64 | 381cc4c2e0589ece921995f02d74259465998b059357aacb1774266d9437e19c |

`8043709c` has bits `3f4ccccd`, binary32 **0.800000011920929**. The load at
`80046ef8` uses r2 displacement `-31108`, consistent with recorded basis
`8043ea20` (`docs/static-recompilation-spike.md:178`). This is not a new live
r2, FPSCR or GQR measurement. Matrix arithmetic retains the previous explicit
RN00/NI0, GQR0 floating-point, GQR5 signed16/scale0, zero-angle and exact
identity-quaternion bounds documented in
`actor-matrix-traversal-evidence-2026-11-13.md`.

Commands, from the repository root:

```sh
PYTHONDONTWRITEBYTECODE=1 python research/tools/matching-decomp/test_archived_normal_matrix_evidence.py
PYTHONDONTWRITEBYTECODE=1 python research/tools/matching-decomp/read_archived_normal_matrix_evidence.py \
  'research/decomp/GotchaForce.rep.before_force_create/idata/00/~00000000.db/db.3.gbf'
PYTHONDONTWRITEBYTECODE=1 python research/tools/matching-decomp/read_archived_normal_matrix_evidence.py \
  'research/decomp/GotchaForce.rep.before_force_create/idata/00/~00000000.db/db.4.gbf'
```

Matching archived ProgramDB content is not proof of unchanged imported original
DOL bytes. No new original-asset acquisition, network operation, live capture,
instruction execution or publication was performed for this evidence.

## Caller and damping order

Export: `ghidra-export/chunk_0005.c:2986–3006,3312–3338`.

`465fc` loads `4a0`; value 2 skips all following work. Otherwise it calls
`46754` once, then `46bd0(actor,0)`. Only after the first traversal does it
read signed byte `661`. Zero calls `46e7c` and then `46bd0(actor,1)`.
The second call does not repeat `46754`. Both modes perform the same root
construction and root copies; mode only selects `4679c` versus `46914`.

After this sequence, `465fc` loads the global pointer, actor byte `3e5`, then
global byte `D2` (`8004664c–80046658`). It sign-extends `3e5` and tests the
intersection. A zero intersection calls `47904`. It then reloads `4a0`; value
1 loads `4a4` and calls `47a2c`. These are separate reached gates, not choices
made before matrix work. No once-per-frame deduplication is supported here.

`46e7c` always stores zero to `1d96` at `80046e8c`, then zero to `1d97` at
`80046e90`, before loading `5e0` and testing bit `0x20000000`.

- Bit set: load descriptor pointer `4b0` at `80046ea0`; form the `1a14`,
  `1a94` and descriptor `+22` arguments; call `46ef4` directly at `80046eb0`.
  This branch never reads metadata byte `1d98`.
- Bit clear: load metadata byte `1d98` at `80046eb8`; form table base;
  load descriptor pointer `4b0` at `80046ec4`; mask and scale the low nibble
  at `80046ec8`; form `1a14`; load the indexed handler at `80046ed0`;
  form descriptor `+22` and `1a94`; `mtctr` at `80046edc`, then `bctrl`
  at `80046ee0`.

Both damping paths load the descriptor pointer but do not dereference descriptor
bytes. A symbolic host implementation must share the actual mapping pointer
field; it must not invent descriptor-memory reads or demand a descriptor
payload that the damping callee never consumes.

`46ef4` loads `1d60`, loads the constant, performs `fmuls`, and stores `1d60`.
It does **not** add that result to `1d58`. Such an addition exists in other
terrain handlers and cannot be imported into this one. Single rounding of a
finite binary32 product preserves the admitted signed-zero/underflow behavior.
Any refusal after the two count stores retains them.

The 16 consecutive words addressable by the mask are:

| Low nibble | Target |
| ---: | --- |
| 0 | 80046f08 |
| 1 | 80046ef4 |
| 2 | 80047164 |
| 3 | 80047344 |
| 4 | 8004871c |
| 5 | 800487ec |
| 6 | 8004892c |
| 7 | 80048a6c |
| 8 | 80048be0 |
| 9 | 80049f10 |
| a | 8004a00c |
| b | 8004a0e0 |
| c | 8004a1cc |
| d | 8004a2ec |
| e | 8004a41c |
| f | 8004a60c |

This window is not proof that all sixteen selectors are intended terrain modes
or that they form one separately allocated C table. Later words overlap the
region identified as setup-handler tables elsewhere. Only selector 1 and the
direct suppression branch are admitted damping paths in this bounded slice.
Other reached dispatch targets remain unsupported rather than becoming no-ops.

## Corrected traversal without entries

Export: `chunk_0005.c:3118–3216`.

`46914` first sign-extends the current topology byte and terminates when it is
negative. Otherwise it reads `1d70` and tests that joint's bit. A disabled joint
does not read either correction count: it still visits byte1 with the incoming
parent, then follows byte0 with the current joint as parent.

For an enabled joint, the function loads `1d96` at `8004694c`, sign-extends it
at `8004695c` and compares loop index zero with that signed count before any
entry load. A nonpositive count skips the first scan. After the no-match path's
topology pointer calculation, it loads `1d97` at `80046a1c`, sign-extends at
`80046a2c` and again checks the loop condition before reading entries.

Thus raw counts 0 or 128–255 genuinely scan no entries. A positive count requires
entry storage, and matching entries require the `47368` or `4784c` effect. A
bounded no-entry implementation may refuse at the first entered scan, preserving root
and earlier joint writes. It must not eagerly validate counts for disabled or
unreached nodes. Both genuine damping paths leave the counts zero.

Without a match, joint 1 performs its z/x/y parent wrappers and uses translation
`1d54`; other joints use the ordinary bank-zero pose. The recursive branch and
continuation order is the same as `4679c`. The second pass must actually rebuild
and traverse; reusing first-pass output is not the source call sequence.

## Postprocessing guards and receiver copy

Export: `chunk_0005.c:3659–3714`.

`47904` reads and returns at these ordered gates:

1. `741 != 0` (`80047918–80047920`).
2. If still reached, `660 != 0` (`80047924–8004792c`).
3. If still reached, `(1d98 & 0xf0) == 0x10` (`80047930–8004793c`).

Only after all three allow entry does it read lifecycle byte `18`. A bounded
guard-only implementation refuses before that body, without clearing correction
shorts or reading later fields. The active body's call to `6c728` also supplies
`r8=1` at `800479a8`, a sixth argument absent from the simplified C signature.
This body remains a separate implementation requirement.

`47a2c` computes destination/source matrix base pointers and starts with index
zero. Every loop condition reloads the **source** `1d90` (`80047a74`), sign-extends
it (`80047a78`) and performs the signed comparison (`80047a7c`). Each entered
iteration calls `PSMTXCopy` from the source slot to the destination slot, then
advances both addresses by `0x30`, increments the index and reloads the count.

Zero or a negative signed count performs no matrix dereference. The caller
still loaded `4a4`, but no target matrix storage is required until a positive
iteration is reached. The copy loop reads no target mode or target count and
does not rebuild either actor. It copies only `8d4` slots, not `114`, `1aa4`,
scratch, poses or topology. A late failure retains earlier slot copies and the
paired-store prefix within the current `PSMTXCopy`.

## Shared field ownership and the joint-1 short alias

Existing owners must remain live:

- `RomActor.controlWord`, `visibilityBit`, position, pitch, heading and stepHeight.
- Movement's `byte661`; metadata's `byte1d98`; mapping's `descriptor4b0` and
  `jointCount1d90`; existing world matrices, topology and correction storage.
- `RomPhysicsExtrasScratch.flyer741` is already the optional actual actor field
  for `+741` (`packages/combat/src/rom/physicsExtras.ts:73–74`). A reached source
  read needs an explicit own byte; the legacy helper's default-zero behavior
  does not authorize a default in this path.

The new controller may own previously missing `1d96`, `1d97`, `1d60`, `660` and
link `4a4`; the global D2 byte needs an explicit shared battle record. Corrected
traversal must reference the controller's actual count record, not a copy.

`RomActor.steerYaw` is annotated `+18da`, and `18d4 + 1*6 == 18da`. Despite its
historical field name, that address is joint 1's **X correction short**, not its
Y correction. `46dd4` calls the quaternion helper and first concatenation before
loading correction X/Y/Z at `80046e2c`, `80046e34` and `80046e3c`. The existing
`read_archived_world_matrix_evidence.py` authenticates those instructions.
`45838` consumes its first short as X (axis `0x78`), second as Y (`0x79`) and
third as Z (`0x7a`); see `chunk_0005.c:2440–2474` and the existing traversal audit.

Consequently joint 1 must read actual `steerYaw` as signed BAM16 bits **after**
quaternion construction and first concatenation, with no copied X shadow. A
split pose-composition primitive followed by the real short-correction and
scale operations preserves that completed prefix. Other joints retain their
explicit correction X/Y/Z records. Future active `47904` stores to `191c` and
`191e` must share correction slot 12's X/Y (`18d4 + 12*6`), not new fields.

## Verification scope

This evidence work is separate from runtime implementation. Synthetic decoder,
allowlist, width/hash, table-target and authentication tests exercise the new
reader. All 22 synthetic tests passed. Both authenticated local snapshots passed
the six text spans, sixteen indexed table words and damping constant. Their
decoded facts and physical source traces matched exactly. No runtime tests or
aggregate gates are implied by these checks.
