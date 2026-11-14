# Projectile callback8007dcec: bounded archive evidence

## Scope and independent selection

This is static archived ProgramDB evidence, not original-DOL identity,
execution, MATCH, live dispatch, runtime integration, main-loop scheduling or
playability. Exactly three additional selections total188 bytes: callback
8007dcec/152 bytes, guard helper8008aff0/32 bytes and initial-state dispatch
cell802d6f98/4 bytes. No other state cell, resolved handler body, child10c
callback, complete table, adjacent row or asset is read.

Independent sources established these bounds before targeted archive reads:

- The previously authenticated spawn body stores8007dcec to child+0c. See
  [spawn evidence](projectile-spawn-evidence-2026-11-14.md), especially
  instructions7dbc4/7dbd0/7dbec. `ghidra-export/chunk_0011.c:4264–4282`
  supplies callback8007dcec and adjacent entry8007dd84;
  `_index.tsv:1779–1780` agrees. The preceding map row at
  `../symbols/GG4E-CSM-20220412.map:979` is8007db5c/0x190, ending at8007dcec.
  **No named callback map extent exists.** The selected interval is
  `[8007dcec,8007dd84)`,0x98=152 bytes, independently bounded by adjacent
  C/index entries and confirmed by its terminal return7dd80.
- Callback C independently names table802d6f98 indexed by signed child18.
  Prior [allocator evidence](object-allocator-evidence-2026-11-14.md)
  establishes the successful pool3 type3 allocation's zeroing call over740
  bytes. Its implemented memset boundary supplies initial child18=0; the
  authenticated spawn stores do not change18. This justifies **only** cell
  `802d6f98 + 0*4 = 802d6f98`. It does not justify an entire table read or
  state2 cell. Actual dispatch remains conditional on the guard leaving18=0.
- The direct guard call8008aff0 was separately coordinated and bounded by
  `chunk_0013.c:1501–1515`, `_index.tsv:1986–1987` and map1093, size0x20.
  Thus its fixed interval is `[8008aff0,8008b010)`,32 bytes. Both its early
  conditional return and terminal return are represented.

The initial cell resolved to8007dd84 in both snapshots. That identity was
reported before any next-body selection. This reader never follows it.
The known invalid-owner guard changes18 to2, but its state2 table cell is
explicitly unselected even though that address can be computed.

## Authentication and provenance

Reader: `../tools/matching-decomp/read_archived_projectile_callback_evidence.py`.
Tests: `../tools/matching-decomp/test_archived_projectile_callback_evidence.py`.
Existing authenticators and allowlists are unchanged. Whole-snapshot SHA,
schema, language/address maps, empty File Bytes table and complete data5
identity are authenticated first by `read_archived_constants`; command mapping
checks then verify text1/data3/data5. Only the three literal selections follow.
Each selected digest is checked before instruction or pointer interpretation.
Every admitted instruction operand is explicit, including link/record bits,
signed displacements, branch targets, SPR registers and indirect-call fields.
Unsupported or reserved forms fail closed. CLI input is a snapshot path only.

| Snapshot | Whole-file SHA-256 |
| --- | --- |
| db.3.gbf | `7b50dd2d2e17b4bfcc89a64cde27010247d0cbf0f48bd5c059f50275f40458d0` |
| db.4.gbf | `1f86813d91ea8e2c4564f96622ec42555e1dba2c78aa81ad654e892140d019f8` |

Both snapshots agree on every selected operand, target, mapping and physical
span. File Bytes table is version0/root−1/count0; block size16384/master root1;
image offset80000000. Executable SHA-256 metadata
`21454a8880c6254616662710d6ec626e43d853999da2cdfad700030960a94836`
is import metadata, not independently authenticated original executable bytes.
The unchanged authenticator verifies full data5 SHA-256
`989c794b17fc95de6e57810f5c89db23d585c85a15faafc994d9a5bd9a0e61b4`.

- text1: `[800055e0,802b0160)`, length2796416, block/subblock1, root21.
- data3: `[802bae60,803af120)`, length1000128, block/subblock5, root199.
- Both selected mappings use initialized subblock type2, starting/source
  offsets0. The callback records `map_size:null`, not a fabricated named size.

| Selection | Bytes / instructions | Meaning | SHA-256 |
| --- | --- | --- | --- |
| 8007dcec | 152 /38 | complete callback | `ee9edd0cdc0d53686a872a42378eb638ee4b44fdf26e25f7259f6198f71b815a` |
| 8008aff0 | 32 /8 | complete guard helper | `8ea8cac06c446278fad05cfae1dbe3ee6b3a321f4bfd1168269ce88283bef951` |
| 802d6f98 | 4 /n/a | initial-state0 target8007dd84 | `82ff512b4b2bdffddacade1b434ca6436328ae1014d77deb3f0db087032876cd` |

All offsets in this table are decimal. Payload storage is obfuscated and
decoded through the unchanged ProgramDB chain reader; no raw extraction is
written. No selection crosses a data-buffer boundary.

| Selection | Root / data buffer | Chain offset | Data offset | Physical offset | Bytes |
| --- | --- | --- | --- | --- | --- |
| 8007dcec | 21 /52 | 493324 | 1984 | 870342 | 152 |
| 8008aff0 | 21 /55 | 547344 | 6870 | 924380 | 32 |
| 802d6f98 | 199 /207 | 115000 | 354 | 3408232 | 4 |

The exact additional chain-call trace is
`(21,493324,152,2796416)`, `(21,547344,32,2796416)`,
`(199,115000,4,1000128)`, after the unchanged authenticator's reads.
There is no dynamically selected chain call.

## Ordered callback facts

PCs and object-field offsets below are hexadecimal. These are instruction
ordering facts, not decompiler expression ordering or runtime proof.

1. `7dd00` loads byte child18. **Before testing it**, `7dd04` loads the
   pointer at child90 into r3. `7dd08` sign-extends the saved state byte;
   `7dd0c/7dd10` compare signed state with2 and skip the owner dereferences
   when state≥2. The child90 pointer load itself is not skipped.
2. For state<2, `7dd14` loads byte parent18 through that pointer, followed by
   signed extension7dd18 and comparison7dd1c. Parent state≥2 branches to
   the guard at7dd34, without reading either borg identifier.
3. Otherwise `7dd24` reads signed parent3e8 and `7dd28` reads signed child94.
   Equality branches from7dd30 to dispatch setup7dd4c. Mismatch reaches
   the guard. These are signed16 loads, even though the spawn copy used
   unsigned16 to preserve the original child94 bits.
4. Guard7dd34 sets r0=2,7dd38 restores child to r3, and7dd3c stores child18=2.
   `7dd40` calls8008aff0(child). **Only after that call returns**,7dd44/7dd48
   store child82=0. These effects precede any subsequent table access.
5. `7dd4c` reloads child18 after the guard. `7dd50/7dd54` resolve table base
   802d6f98,7dd58 restores child in r3,7dd5c sign-extends the reloaded byte,
   and7dd60 shifts it left2 with `rlwinm SH2,MB0,ME29`. There is no source
   clamp or bounds check on this signed index.
6. `7dd64` loads the function pointer via `lwzx r12,r4,r0`;7dd68 moves r12
   to CTR;7dd6c performs `bctrl BO20,BI0,BH0,LK1`. Initial state0 selects the
   authenticated cell802d6f98, whose target is8007dd84. A guard-induced
   state2 does **not** use that cell. Unknown states must remain an explicit
   boundary rather than fall back to initial state0.
7. Epilogue7dd70..7dd7c restores LR, saved r31 and stack;7dd80 returns.
   Neither the guard return nor the indirect call return is overwritten
   in r3 by the epilogue. C's `void` label does not erase the register result.

The reader fixes sole direct call8008aff0, sole indirect-call site7dd6c and
terminal return7dd80, and checks that every conditional branch stays inside
the152-byte callback span. All38 instructions have complete operands.

## Ordered guard-helper facts

The helper has eight instructions and does not write r3:

1. `8aff0` loads **unsigned byte** child2 into r4. `8aff4` compares r4 to3.
   Equal branches at8aff8 directly to8b004.
2. Otherwise8affc sign-extends r4 into r0 **with record bit1**. Conditional
   LR return8b000 (`BO4,BI2,BH0,LK0`) returns when that signed byte is nonzero.
3. Type0 or3 reaches8b004, which puts1 in r0;8b008 stores byte1 at child1d8;
   terminal8b00c returns. Every other byte leaves1d8 unchanged.
4. Both returns preserve incoming r3, so the helper returns its input child
   pointer unchanged. This is not a fabricated zero/boolean return.

The C comment at `chunk_0013.c:1503` correctly describes the preserved r3,
but its early-return PC is stale: **8affc is `extsb.`; the conditional return
is8b000**. This note records the authenticated correction without editing the
exported corpus.

## Checks and limits

`python -m unittest discover -s research/tools/matching-decomp -p
 'test_archived_projectile_callback_evidence.py' -v` passes **15 tests**.

- Manually authored semantic fixtures independently inverse-encode all46
  instruction rows to both fixed body hashes and compare every decoded field.
- All1,472 single-instruction bit mutations reject or remain semantically
  distinct and inverse-encode to the exact changed word.
- All1,504 selected-payload bit mutations fail digest checks before decoding.
- All three exact selected reads, physical spans and absence of raw output
  are checked against both existing authenticated snapshots.
- Mapping/type/address/width/duplicate/CLI failures occur before selected reads.
  Whole-file SHA, schema, truncated payload, wrong target, missing return,
  outside branch, changed direct call and missing indirect call fail closed.
- Positive controls pass on both snapshots; there were no authentication,
  read or decoder failures in the bounded discovery. Negative failures are
  intentional controls. A stale C-comment address is the only source correction.
- No original executable or original-code execution, network fetch, installs,
  estimator/runtime import, broad dump, shared authenticator edit, commit or
  push occurred. Other concurrent worktree changes are outside this deliverable.

This establishes a stored callback identity, its actual guard effects and one
initial dispatch target. It does not prove that a real gameplay scheduler calls
the callback, that owner fields are correctly bound, or that the selected
handler is implemented. Successful initial-state dispatch needs a genuine
allocated child, canonical owner pointer/state and a matching child94 copy;
it cannot be established by null/zero owner shortcuts or hidden field repair.
