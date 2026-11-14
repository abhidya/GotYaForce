# Ordinary-X command admission: archived source evidence

## Result and limits

Both existing local ProgramDB snapshots agree on **all 421 instructions** in
the four independently selected complete functions `80069ea4`, `8006c674`,
`8006a104`, and `8006bda8`. Every instruction has explicit operand witnesses,
including prologues, epilogues, comparisons, branches, calls and returns.

The bounded extension also represents **all 54 selected instructions** in the
two zero-yaw trig wrappers, the voice wrapper, and the voice helper's entry
gate/return. The voice helper's **66 other instructions remain unselected**.
Existing fixed sin/cos/kernel evidence is reused unchanged, with every omitted
instruction address reported. This does not promote that older partial decoder
to full libm coverage.

This establishes archived source schedules and fixed data, not unchanged
original-DOL identity, live input, descriptor/global/actor ownership, full
gameplay parity, production integration, or a complete actor tick. No runtime
pointer chooses a reader address. No archived/original instruction is executed.
Missing reached owners and callees must remain boundaries, not fabricated
successes, zeros, null actors, or skipped effects.

Artifacts:

- [Fixed reader](../tools/matching-decomp/read_archived_actor_command_admission_evidence.py).
- [All-operand and refusal tests](../tools/matching-decomp/test_archived_actor_command_admission_evidence.py).
- [Preceding input-tester evidence](actor-input-testers-evidence-2026-11-14.md).
- [Reused zero-kernel evidence](actor-matrix-traversal-evidence-2026-11-13.md).
- C markers: `ghidra-export/chunk_0009.c:489-546,603-683,1798-1861,2112-2155`;
  `chunk_0005.c:2143-2178`; `chunk_0025.c:1819-1880`.
- Symbol map: `research/symbols/GG4E-CSM-20220412.map` entries at each named
  complete function. Every primary function has a real map row of the selected
  size, the matching next C marker and an authenticated terminal `blr`.

## Authentication, fixed extents and physical provenance

Existing inputs under `GotchaForce.rep.before_force_create/idata/00/~00000000.db/`:

- `db.3.gbf`: `7b50dd2d2e17b4bfcc89a64cde27010247d0cbf0f48bd5c059f50275f40458d0`.
- `db.4.gbf`: `1f86813d91ea8e2c4564f96622ec42555e1dba2c78aa81ad654e892140d019f8`.

Unchanged `read_archived_constants.inspect` first checks the actual complete
snapshot SHA, exact schemas, big-endian Gekko/Broadway language, executable
metadata, empty File Bytes table, address maps, complete data5 hash and existing
controls. Unchanged `read_archived_command_evidence.mappings` checks exact
text1/data3/data5 mappings and all-block nonoverlap. Every new selection checks
exact integer address/width, mapping type and values, bounds/alignment, byte
count and digest or constant bits before decoding. Unknown instructions fail
closed. Shared reader allowlists are unchanged.

- Executable import-metadata SHA:
  `21454a8880c6254616662710d6ec626e43d853999da2cdfad700030960a94836`.
  This metadata is not proof of unchanged executable bytes.
- File Bytes table: version 0, root -1, count 0.
- Block size 16384, master root 1, image offset `80000000`.
- Text1: `800055e0`, length 2796416, block/subblock 1, chain root 21.
- Data3: `802bae60`, length 1000128, block/subblock 5, chain root 199.
- Data5: `80436a20`, length 27360, block/subblock 7, chain root 263.
- Data5 SHA:
  `989c794b17fc95de6e57810f5c89db23d585c85a15faafc994d9a5bd9a0e61b4`.
- Each selected mapping is subblock type 2 with starting/source offsets 0.

| Selection, end exclusive | Bytes / instructions | SHA-256 |
| --- | --- | --- |
| `80069ea4..80069fe0` | 316 / 79 | `8b0efdb5a565ee7ef2266109d0ee51d37118bcebb03821f06b9418cadaeac9d7` |
| `8006c674..8006c728` | 180 / 45 | `4381614f1242f91931948f08fe8952e48ab1ac34b5e9561a2e20f4150fd08110` |
| `8006a104..8006a3d0` | 716 / 179 | `476ca1cbad57dc6ad22dbe4c919646740f7d517f813bcc9f7da70ccb7474253f` |
| `8006bda8..8006bf80` | 472 / 118 | `175c8cf36b7dc4bb7bc5c76ce86651b067ff08ff5cfdc0eb0c394411acb28dc9` |
| `80045204..80045238` | 52 / 13 | `cd6a74d4ec3ade0be57d6c57a0a2e558dee77ab24ebd545f89543a74d162a1a5` |
| `80045238..8004526c` | 52 / 13 | `c882d317771586afa562e3243e557411e54441b86fdcd9966e2b39af9b7d120f` |
| `800ea2c8..800ea2ec` | 36 / 9 | `d32cb5a6a7828518b31b184cab5db4840a2a8c7e55c86a953d1317941bdf9966` |
| `800ea2ec..800ea324`, prefix only | 56 / 14 | `aee7a9b97ff23e93962d200216fefd082fd8d3f6b20404535842c312fcb38662` |
| `800ea42c..800ea440`, epilogue only | 20 / 5 | `972973be8074e92b0f10fc5fbbaaef6c28e2905f99007654cd735a5fd69933fc` |

The first seven selections are complete functions. The map and C markers give
`800ea2ec..800ea440` a **340-byte full extent**, not a 56- or 76-byte function.
Only 76 bytes / 19 instructions are represented; `800ea324..800ea42c` is an
explicit 264-byte / 66-instruction gap. The early path jumps over this gap.

All following text physical traces match between snapshots. Root buffer is 21,
storage is obfuscated, and offsets are decimal:

| Entry | Data buffer | Chain offset | Data offset | Physical offset | Length |
| --- | --- | --- | --- | --- | --- |
| `80069ea4` | 47 | 411844 | 2394 | 788832 | 316 |
| `8006c674` | 47 | 422036 | 12586 | 799024 | 180 |
| `8006a104` | 47 | 412452 | 3002 | 789440 | 716 |
| `8006bda8` | 47 | 419784 | 10334 | 796772 | 472 |
| `80045204` | 37 | 261156 | 15486 | 638084 | 52 |
| `80045238` | 37 | 261208 | 15538 | 638136 | 52 |
| `800ea2c8` | 79 | 937192 | 3646 | 1314372 | 36 |
| `800ea2ec` | 79 | 937228 | 3682 | 1314408 | 56 |
| `800ea42c` | 79 | 937548 | 4002 | 1314728 | 20 |

## Fixed constants and the bounded mask window

Six directly named constants are authenticated independently. These are data
values, not a raw executable dump:

| Address | Type | Bits | Value | Physical offset |
| --- | --- | --- | --- | --- |
| `8043762c` | f32 | `00000000` | +0 | 4344850 |
| `8043764c` | f32 | `bf800000` | -1 | 4344882 |
| `80437658` | f32 | `00000000` | +0 | 4344894 |
| `80437660` | f64 | `3fe0000000000000` | 0.5 | 4344902 |
| `80437668` | f64 | `4008000000000000` | 3 | 4344910 |
| `80437678` | f32 | `469c4000` | 20000 | 4344926 |

They use root 263 / data buffer 264, obfuscated storage. Chain/data offsets are
3084, 3116, 3128, 3136, 3144 and 3160 respectively. The reader emits individual
SHA-256 values as well. The SDA2 basis `r2=8043ea20` is previously recorded in
`docs/static-recompilation-spike.md:178`, not freshly authenticated startup code
or a live register capture. Actual instruction displacements remain explicit.

The single independent data3 window `802d3994..802d39a0` is 12 bytes:

- SHA `94929509e3228a6f14382e3c05d7cd38c28d1af7ee09e0ec5f36c23ca79460fc`.
- Root 199, data buffer 206, chain offset 101172, data offset 2904,
  physical offset 3394398, length 12, obfuscated in both snapshots.
- Slot 0 gives `57a=58,57b=4`; slot 1 gives `56,4`; slots 2,3,4,5 each give
  `56,0`. Values in this sentence are decimal.

These six pairs cover the explicitly selected ordinary input slots 0..5.
**The containing table's extent is not proven.** Source indexing uses signed
`584`, reloads that byte between the two cell reads, and does not range-check
it here. Negative/other indices and bytes beyond the window remain outside the
evidence; the reader never follows an index to read them.

## `80069ea4`: ordered admission and command addressing

Offsets below are hexadecimal; PC prefixes may be shortened for readability.

1. Load `595` at `69eb8`, sign-extend with record bit. Nonzero skips the float
   gate entirely. Zero loads `694` (`69ec4`), then +0 (`69ec8`), performs
   `fcmpo`, and returns 0 only for **ordered greater than zero**. Equality,
   negative, or unordered are not that rejection branch. This is not a host
   `<=0` replacement when unordered values are in the model's domain.
2. Load `5e0` **once** at `69edc`; all following mask tests use retained r3.
   Set `586` by this priority:
   - mask `100`: 5;
   - otherwise mask `80`: 4;
   - otherwise mask `20`: read signed `7cc`; nonzero gives 2, otherwise mask
     `40` gives 3 and clear gives 0;
   - otherwise mask `40` gives 3 without reading `5e4`; if clear, read `5e4`
     and equality to 4 also gives 3;
   - otherwise mask `10` gives 1, clear gives 0.
3. Call `6c674` at `69f88`; store its low return byte to `587` at `69f8c`.
4. Reload `585`, `586`, `587` in that order at `69f94/98/9c`, sign-extend
   all three, load `4ec` at `69fa8`, and load the pointer cell at
   `4ec + signed585*4` (`69fb8`). The record address passed to `6a104` at
   `69fc8` is that pointer + `signed586*16 + signed587*4`.
5. Propagate `6a104`'s word return unchanged. No descriptor payload, table
   pointer value, live record, or owner is established by this reader.

## `8006c674`: genuine no-target return and active direction boundary

The first actor access is `lwz 508` at `6c688`. Zero returns 0 at `6c694` and
branches to the epilogue at `6c714`. This path reads no `4ac`, transformed
point, angle, or target payload, and calls no helper.

Nonzero calls `66408(actor,0,actor+50c,stack+8)` at `6c6a8`. It then loads
stack+8 into f1 and stack+16 into f2 and calls `452a0` at `6c6b4`. After that
call it loads `4ac`, sign-extends the returned low halfword, and reads signed
halfword thresholds in order:

- `4ac+15c`: angle greater gives 2;
- otherwise `4ac+158`: angle greater gives 1;
- otherwise `4ac+15a`: angle not less gives 0;
- otherwise `4ac+15e`: angle less gives 2, otherwise 3.

Later threshold loads occur only after earlier comparisons fall through. The
angle/matrix helpers and descriptor threshold owner remain boundaries unless
implemented and supplied separately.

## `8006bda8`: capture occurs before command effects

The exact prefix is:

1. Load `504` / store `c8` at `6bdc4/c8`.
2. Load `508` / store `cc` at `6bdcc/d0`.
3. Load `7d2` / store `d0` at `6bdd4/d8`.
4. Load signed halfword `6b8`; nonzero clears `c8`, then `cc`, then `d0` at
   `6bdec/f0/f4`. These earlier copies and clears are separate source writes.
5. Reload `cc` at `6bdf8`; zero selects the no-target branch `6bf14`.

### No-target branch

- Load exact 20000f, store **`764` then `760`** at `6bf18/1c`.
- Load signed `72`; call `45204` at `6bf24`; **reload `764`**, multiply by
  returned f1 with single-rounded `fmuls`, store `518` at `6bf30`.
- Load `4b0` (`6bf34`), load descriptor byte `+10` (`6bf38`), sign-extend,
  multiply by `30`, add actor base, load float `8f0 + signedIndex*30`
  (`6bf48`), and store `51c` (`6bf4c`). This is the source indexed matrix
  field, not an invented position or added world translation.
- **Reload signed `72`**; call `45238` at `6bf54`; **reload `764`**, `fmuls`
  with returned f1, and store `520` at `6bf60`.

The two yaw reads and two distance reloads are observable and must not become
one preloaded snapshot across helpers. Missing descriptor/matrix ownership is
a reached boundary after the earlier distance and X writes, not permission to
synthesize zero height or roll back the prefix.

### Active-target branch

Nonzero `cc` loads `c8` once and uses that retained pointer's `64/68/6c` fields
to store `518/51c/520`. It calls `8020bc88(actor+20,target+64)` at `6be30`.
Positive ordered squared distance enters `frsqrte`, double multiplies and
three fused `fnmsub` refinement steps, then `frsp`, stack store/reload, and
store `760`. Nonpositive/unordered skips refinement and stores the returned
value. It separately reloads own/target X and Z, uses single `fsubs`, two
single `fmuls`, single `fadds`, and a second ordered gate/refinement before
storing `764`. The full operands are witnessed, but neither host `sqrt` nor
split multiply/subtract is exact evidence for this sequence.

## `8006a104`: sentinel, masks, visibility and mandatory cue/sound work

1. Read record[0], sign-extend, compare to -1. Equality returns 0 before any
   actor-field load/store or capture helper. Otherwise reload `585`, store it
   to `584` (`6a138/13c`), and call `6bda8` (`6a140`).
2. After capture, load `5e0` once at `6a144`. If low two bits are 3, read
   record[1] unsigned and compare to 1. Only then test mask `40` of the
   **retained** `5e0`. Set calls `6a750(actor,6)`; clear calls
   `6a750(actor,0)`, then `4beb8(actor,2,0,0,-1,-1)` with f1=-1f.
3. Read record[2], load +0f, store `580`; read record[3], store `581`.
   Load `5e0`, clear low two bits, store it. **Reload `5e0`**, read record[1]
   unsigned, OR the **entire byte** into the word, and store it again. Store
   retained +0f to `694`. Reload record[1]; equality to 3 stores `709=0`.
4. Read signed `584` for the first fixed mask cell and store `57a`. **Reload
   signed `584`** for the second cell and store `57b`. Store `1d9a=0`.
5. Reload signed `584`; if at least 3, load +0f and store `630+index*4`.
   **Reload signed `584`** and store the retained +0f at `63c+index*4`.
6. Construct global reference-array base `803c4e84`; all six entries at
   offsets 0,4,8,c,10,14 are mandatory and have **no null check** here.
   - First read actor `3e5` (`6a260`), then slot0 pointer (`6a268`), then that
     actor's `5e6`; `andc` clears the loaded mask and stores the low byte.
   - Each later slot loads its pointer first, **reloads actor `3e5`**, loads
     that actor's `5e6`, clears and stores. Pointer load PCs are
     `6a278,6a28c,6a2a0,6a2b4,6a2c8`; mask loads follow them by 4 bytes.
   - Reference-array addresses are constructed by source instructions; the
     reader does not read their pointers or follow any pointee. Aliases and
     earlier stores may affect later reads. Missing owners cannot be skipped.
7. Reload `cc` (`6a2dc`). If nonzero, read signed target byte `83`; zero
   loads target `5e6`, reloads actor `3e5`, ORs and stores target `5e6`.
8. Reload signed record[0], call `6a6fc(actor,id)` at `6a310`. Reload
   record[1]; equality to 3 reloads signed record[0] again and calls
   `6a750(actor,id)` at `6a32c`. Cue reset is mandatory, not an optional hook.
9. Reload signed `584`. Only values 0 or 2 access `actor+index*8+78e`;
   a zero halfword bypasses the next read. Otherwise read `+790`; equality
   to 3 bypasses the helper. Otherwise call `6dbe0(actor,index,1,0)`.
   Its zero result reloads signed `3e4` and `584` and calls `11cc4`, which
   suppresses the final voice wrapper. Other paths call `ea2c8(actor,2)`.
10. Return 1 **after all reached work completes**. Reaching a missing helper
    is not success, even when earlier stores have already happened.

## Approved narrow support: zero yaw and non-normal-match voice

### Source zero-yaw wrappers

`45204/45238` do not have a short-zero branch. Each stores r3 as a halfword at
stack+8, performs `psq_l f1` with **W=1,I=5**, loads factor `80437078`, and
executes single `fmuls`. `45204` calls sin `8023c9e8` at `45220`; `45238`
calls cos `8023c480` at `45254`. Both execute `frsp` on the result and return.
The decompiled C's unreachable-block warning is not permission to omit the
quantized load or treat its scale as unknown-but-zero.

Reuse of existing `read_archived_actor_traversal_evidence` selections:

| Span | Represented / total instructions | Unrepresented |
| --- | --- | --- |
| `8023c9e8..8023cac0`, sin | 51 / 54 | 3 |
| `8023c480..8023c554`, cos | 50 / 53 | 3 |
| `8023bf8c..8023c02c`, kernel_sin | 27 / 40 | 13 |
| `8023b044..8023b138`, kernel_cos | 44 / 61 | 17 |

The reader returns the original fixed span hashes/physical provenance and all
omitted addresses. It only normalizes the older decoder's store-register field
names to rS/fS in its own returned copy. Sin omissions are `c9ec,ca2c,cab4`;
cos omissions are `c484,c4c0,c548`. These include ABI instructions, so **full
represented-function coverage is not claimed**. Existing kernel zero-path
prefixes and kernel epilogues are represented; dormant polynomial omissions
are not filled with inferred instructions.

The existing fixed constant controls provide positive factor bits `38c90fdb`
at `80437078`, positive-zero f64 tails at `8043d198/8043d150`, and exact f64 1
at `8043d030`. Under the explicit execution-domain conditions **GQR5 signed16,
load scale 0**, and FPSCR RN=00/NI=0, short zero becomes +0 and remains
+0 after multiplying by the positive factor.

Sin/cos mask the high double word's sign and compare to `3fe921fb`, selecting
direct kernel calls for +0. The kernels compare against `3e400000`, convert
with `fctiwz`, and observe integer zero. Kernel_sin branches from `8023bfbc`
to `8023c024` without changing f1, so returns +0. Kernel_cos loads the
authenticated 1 at `8023b074` and branches to `8023b130`. Wrapper `frsp`
preserves both exact results. No polynomial or general nonzero libm parity is
claimed, and no live GQR/FPSCR value is established.

Thus in the specifically supplied, genuine no-target/zero-yaw domain, the
capture path stores `518=+0`, uses the supplied indexed matrix field for
`51c`, and stores `520=20000f`. This is not a general no-target angle model.

### Genuine voice early return

`ea2c8` supplies r5=-1, leaves actor/category in r3/r4, and calls `ea2ec` at
`ea2d8`. The helper saves its ABI state, loads r13-relative pointer cell
`-31852` at `ea308`, reads byte `+45` (`ea30c`), sign-extends it (`ea310`),
and compares to **4** (`ea314`). Only **signed greater than 4** reaches
`r3=-1` (`ea31c`) and the jump to the authenticated epilogue `ea42c`.

This path performs no actor reads, RNG call, audio dispatch, voice-table read,
or further global read. Bytes `80..ff` are negative and **do not** satisfy it.
Signed `<=4` branches to the explicit unselected boundary `ea324`.

The previously recorded `r13=8043b5a0` yields named cell `80433934`; this is
recorded SDA provenance, not a fresh startup/live-register proof. The reader
does not read that cell or pointee. A runtime must supply the actual named
shared-global owner; absence is not permission to default the mode to 5.

## Verification and remaining boundaries

Focused command:

```sh
python -m unittest discover -s research/tools/matching-decomp \
  -p test_archived_actor_command_admission_evidence.py -v
```

Result: **16 tests pass**, including both local archives, all 475 newly
selected instruction operands, exact physical traces, truthful map/C/return
extents, source-order/reload witnesses, reused zero-kernel path/omission
checks, six constants and the fixed mask window. Adversarial checks reject
wrong snapshot/hash/schema/maps, wrong types, duplicate/shifted/widened code
selections, altered constants/masks, unsupported/reserved forms, and
arbitrary-address/raw/execute CLI options. Rejection occurs before instruction
decoding for wrong width or digest. This focused result is not a full repository
verification or a runtime behavioral claim.

The broader `test_archived_actor*_evidence.py` selection also passes **252
tests**. The snapshot-only CLI succeeds for db.4 and reports 421 primary,
54 new support and 172 reused represented instructions, with the 66-instruction
voice-body gap explicit. `git diff --check` passes. Parent-owned runtime work
and the repository aggregate checks are outside this evidence-only result.

Boundaries still include active target transform/angle/squared-distance work,
nonzero trig, descriptor and matrix payload ownership, all six global actors,
target ownership, cue/reset/launch work, ammo helpers, and normal-match voice.
The fixed mask window is neither a generic descriptor importer nor an index
validator. The source evidence permits a runtime to complete only genuinely
reached, explicitly supported branches while preserving earlier effects when
a later boundary is encountered. No files were installed, no original code
was executed, and no commit or publication is part of this evidence work.
