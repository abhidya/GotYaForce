# Ordinary actor envelope and mode-one playback: archived evidence

## Result and limits

Both existing authenticated ProgramDB snapshots agree on **all 553 instructions
and operands in seven independently bounded complete functions**, plus seven
fixed scalar constants. The reader includes ABI saves/restores, paired-single
instructions, branches, CR fields, direct/indirect call instructions and returns.
No instruction is omitted within a selected function. Static evidence does not
establish unchanged original-DOL bytes, live actor ownership or dispatch,
matching-decompilation `MATCH`, runtime numerical parity, clone creation, or
playable-game acceptance.

Artifacts:

- [Fixed reader](../tools/matching-decomp/read_archived_actor_mode1_evidence.py).
- [All-operand, inverse-encoding and refusal tests](../tools/matching-decomp/test_archived_actor_mode1_evidence.py).

This adds no table reads. Existing
[normal-matrix evidence](normal-actor-matrix-evidence-2026-11-13.md) already
records setup slot 1 cell `802d0d74 -> 800487ec` and playback slot 1 cell
`802d0d88 -> 8004a00c`. Its indexed window places those cells at indices 5 and
10; those window indices must not be confused with handler-table slot 1.
Existing [traversal evidence](actor-matrix-traversal-evidence-2026-11-13.md)
authenticates the entire 36-byte vector-add function `8020ba54..8020ba78`, so it
is not selected again here. No returned pointer or decoded call selects a read.

## Independent selection and extent basis

All bounds below were identified from named C markers before their payloads
were selected. None of the first five functions has a symbol-map entry. Their
bounds are **not map-derived**. The two SDK-style helpers have map sizes that
agree with the next named C marker. Every selected span ends in an authenticated
`blr`, and every non-call direct branch stays inside its span.

| Function | End exclusive | Bytes / instructions | Named source marker | Map size |
| --- | --- | --- | --- | --- |
| `FUN_80055568` | `8005568c` | 292 / 73 | `chunk_0006.c:7776`, next marker `:7813` | absent |
| `FUN_800487ec` | `8004892c` | 320 / 80 | `chunk_0005.c:4298`, next marker `:4354` | absent |
| `FUN_8004a00c` | `8004a0e0` | 212 / 53 | `chunk_0006.c:74`, next marker `:110` | absent |
| `FUN_8004b94c` | `8004bb14` | 456 / 114 | `chunk_0006.c:1160`, next marker `:1237` | absent |
| `FUN_8004a8cc` | `8004aae0` | 532 / 133 | `chunk_0006.c:415`, next marker `:501` | absent |
| `gnt4-PSQUATScale-bl` `8020ba9c` | `8020bab8` | 28 / 7 | `chunk_0064.c:1299`, next marker `:1322` | `0000001c` |
| `C_QUATSlerp` `8020bf08` | `8020c07c` | 372 / 93 | `chunk_0064.c:1551`, next marker `:1593` | `00000174` |

Map source: `research/symbols/GG4E-CSM-20220412.map`. Scale's name is misleading:
its complete source and instructions scale **three vector components**, not
four quaternion components. The caller's two actual scale targets are
`8020ba9c` at `8004a934` and `8004a944`; its add target is `8020ba54` at
`8004a954`. Independent scale marker/map identification preceded the bounded
scale payload read. Decompiler warnings about removed blocks do not remove
instructions from this evidence.

## Authentication and physical provenance

Inputs remain local, unchanged files under
`research/decomp/GotchaForce.rep.before_force_create/idata/00/~00000000.db/`:

- `db.3.gbf`: SHA-256
  `7b50dd2d2e17b4bfcc89a64cde27010247d0cbf0f48bd5c059f50275f40458d0`.
- `db.4.gbf`: SHA-256
  `1f86813d91ea8e2c4564f96622ec42555e1dba2c78aa81ad654e892140d019f8`.

The unchanged shared `read_archived_constants.inspect` authenticates the actual
whole-file SHA, exact schemas, `boot.dol`, language
`PowerPC:BE:32:Gekko_Broadway`, Ghidra creation version `12.1.2`, executable hash
metadata and property type 2, empty File Bytes, address map, whole data5 hash
and established controls before any new payload selection. Executable import
metadata `21454a8880c6254616662710d6ec626e43d853999da2cdfad700030960a94836`
is not proof that the archived memory is an unchanged original executable.

The unchanged command mapping guard checks all-block overlaps and exact text1,
data3 and data5 block/subblock identities, encoded addresses, lengths, type 2,
starting offset 0 and source offset 0. This reader additionally derives and
checks exact typed text1/data5 mapping tuples before selected reads:

- Text1 `800055e0..802b0160`: block/subblock 1, length 2796416, chain root 21.
- Data5 `80436a20..8043d500`: block/subblock 7, length 27360, chain root 263;
  SHA-256 `989c794b17fc95de6e57810f5c89db23d585c85a15faafc994d9a5bd9a0e61b4`.
- File Bytes version 0, root -1, count 0; image offset `80000000`, database
  block size 16384, master root 1.

| Code span entry | SHA-256 |
| --- | --- |
| `80055568` | `4ef4d2db70068dec76e280773b3d58c546452599966914bffd4f8cbaf56472c7` |
| `800487ec` | `89ff3f5e42d9fb00cbb2b9cd09864c30a2de70f0539ca93245827a290548571d` |
| `8004a00c` | `943a91557593db9ea74d25db6555ccde8ada24fa808aa1dbb944ec4522be2f3f` |
| `8004b94c` | `eb174f015991c8786bb609ba168c208ad41e6213bb209a9eb37e4d35512e19b3` |
| `8004a8cc` | `2da4f533bb5e7cb3ee7f530dae5f56ab60027846174ddd4824c05e5cb6077321` |
| `8020ba9c` | `e0fbf8bbb6f184d7b21d322b68975adca6dc652510963c83c95b9ceb63e0671d` |
| `8020bf08` | `30cb73d805f9a7ac73924e6898d2c8a98a36fff0a5a1a517168e9884c22af4e7` |

Both snapshots have identical physical traces for the selections below. All
are obfuscated; offsets and lengths are decimal.

| Address | Root / data buffer | Chain offset | Data offset | Physical offset | Length |
| --- | --- | --- | --- | --- | --- |
| `80055568` | 21 / 42 | 327560 | 0 | 704518 | 292 |
| `800487ec` | 21 / 38 | 274956 | 12908 | 651890 | 320 |
| `8004a00c` | 21 / 39 | 281132 | 2706 | 658072 | 212 |
| `8004b94c` | 21 / 39 | 287596 | 9170 | 664536 | 456 |
| `8004a8cc` | 21 / 39 | 283372 | 4946 | 660312 | 532 |
| `8020ba9c` | 21 / 151 | 2122940 | 10178 | 2500552 | 28 |
| `8020bf08` | 21 / 151 | 2124072 | 11310 | 2501684 | 372 |
| `804370f0` | 263 / 264 | 1744 | 1744 | 4343510 | 4 |
| `804370f4` | 263 / 264 | 1748 | 1748 | 4343514 | 4 |
| `804370f8` | 263 / 264 | 1752 | 1752 | 4343518 | 8 |
| `80437104` | 263 / 264 | 1764 | 1764 | 4343530 | 4 |
| `8043cab8` | 263 / 265 | 24728 | 8350 | 4366500 | 4 |
| `8043caa0` | 263 / 265 | 24704 | 8326 | 4366476 | 4 |
| `8043cac0` | 263 / 265 | 24736 | 8358 | 4366508 | 4 |

Only instruction-named scalar addresses are added. Their SDA2 derivation uses
the previously recorded r2 basis `8043ea20`
(`docs/static-recompilation-spike.md:178`), not an assertion about live r2:

| Address | Bits | Value | Example referring PC / r2 displacement |
| --- | --- | --- | --- |
| `804370f0` | `3f800000` | f32 1 | `8004889c` / -31024 |
| `804370f4` | `00000000` | f32 +0 | `800488c4` / -31020 |
| `804370f8` | `4330000080000000` | f64 4503601774854144 | `80048890` / -31016 |
| `80437104` | `3f000000` | f32 0.5 | `8004aa78` / -31004 |
| `8043cab8` | `3f800000` | f32 1 | `8020bf7c` / -8040 |
| `8043caa0` | `00000000` | f32 +0 | `8020bf74` / -8064 |
| `8043cac0` | `3f7fff58` | f32 0.9999899864196777 | `8020bf98` / -8032 |

The reader emits scalar bits/value/hash, instruction fields, hashes and physical
provenance, never raw code ranges. It rejects unknown whole images, schemas,
metadata, mappings, widths, digests, unsupported instructions or reserved fields,
missing terminal return, external non-call branches, duplicate selections and
noninteger addresses. The CLI accepts one snapshot pathname only, not an
address, width, raw output, follow-pointer or execution option. Shared readers
and allowlists are unchanged.

## Ordinary envelope `80055568`

The precise ordering matters when a nested call changes state or refuses:

1. Store actor byte `578=2` at `80055584`. Call `80055dcc`, `8005568c`, then
   `80059068` at `80055588/590/598`.
2. Read actor words `20`, `24`, `28` at `8005559c/5a4/5a8`, save their original
   bits on the stack, then invoke the actor `4bc` callback at `800555c0`.
3. **Read upper-body state byte `5db` at `800555c4`, then full-body state byte
   `5da` at `800555cc`**, both before storing marker `578=1` at `800555dc`.
   Sign-extend upper-body state, index base `802d37a8`, call at `800555f0`.
4. Sign-extend the previously saved full-body byte from r30 at `800555f8`,
   store marker `578=0` at `80055600`, index base `802d36a8`, and call at
   `80055618`. It is not reloaded
   after the upper-body handler. Neither state table is dumped by this reader.
5. Store `578=2` at `80055624`; invoke actor `4c0` callback at `80055630`, then
   call `80055ee4` at `80055638`.
6. Read word `5e0`. Only if bit `0x40` is clear, read/sign-extend byte `598`.
   Only if it is nonzero, restore saved `20/24/28` words, in that store order.
   Finally call `8005b880` at `80055670` and return.

The called bodies and dynamically indexed targets are external boundaries
unless separately authenticated and implemented. A refusal must preserve its
already executed prefix and must not invent the remaining suffix. Reading a
state, callback field or position earlier than the source can hide a mutation
made by a preceding callback.

## Mode-one setup `800487ec`

Input r7 is copied with record-setting `or` into r30 at `80048804`. If it is
zero, the function calls `8004871c` and exits through the shared epilogue. The
nonzero branch performs these actions:

1. Call `8004b94c(actor, bank=0, slot, skipPose=0)` at `80048834`.
2. Resolve the source via `8004d1f4` at `80048844`. Compute record
   `actor + 1ad4 + slot*40`, write record bytes `28` then `29`, and invoke
   decoder `8004d244` at `80048870`.
3. Add one to the original duration as a 32-bit integer, XOR its sign bit,
   construct the `43300000:lowWord` conversion double on the stack, and subtract
   `804370f8` with **`fsubs`** at `800488c0`. This is not an unspecified host
   double-to-float conversion; the instruction produces the source single
   result used for record `18`.
4. Record `31` receives the top bit of `2a`, then `2f=1`. The actor `1dc8`
   float is stored to record `1c`, duration+1 to `18`; both are reloaded.
   Compute `weight = fsubs(1, fdivs(record1c, record18))`, then store `20`.
5. Write byte `36=0`, float `10=0`, float `14=inputF1`, float `08=0`, and float
   `0c=inputF1`, in that order. Invoke `8004a754` at `800488fc` using the
   reloaded record `0c` as f1, then reload record `20` and invoke `8004a8cc`
   at `8004890c`.

The exact order includes register setup, scalar loads and ABI saves; the
all-operand witness is authoritative where this higher-level summary compresses
steps. In particular decoder effects occur before the transition fields above.

## Playback `8004a00c`

First update record `08` with `fadds(record08, actor1dc8)` and store it. Then
reload actor `1dc8`, update record `1c` with `fadds(record1c, actor1dc8)`, and
store it. Reload record `1c` and `18`, perform `fcmpo(1c,18)` at `8004a058`.

- If `1c < 18`: compute `fdivs(1c,18)` then `fsubs(1,quotient)`, store record
  `20`; call `8004a830` with bank 0, secondary argument 0, slot and completion
  flag 0; reload `20`, call blend `8004a8cc`; return.
- Otherwise for ordinary finite inputs: compute `fsubs(1c,18)` and then
  `fadds(oldRecord0c,delta)`, store record `0c`; call `8004a830` with completion
  flag 1; **only after that call returns** store record byte `2f=0`; return.
  There is no blend call on this path.

The branch tests CR less-than clear, so unordered input also reaches the latter
branch at the instruction level. A finite-domain implementation must refuse
unsupported NaNs at the actual reached arithmetic boundary rather than claiming
it implements all FPSCR behavior.

## Bank copy `8004b94c`

Destination bank is `sourceBank XOR 1`. Source and destination records are
`actor + 1ad4 + bank*100 + slot*40`. The 64-byte record is copied in eight pairs:
**load two u32 words, then store those two words**, before the next pair is read.
After all pairs, set destination byte `33` to destination bank. This is not one
all-record snapshot or a generic memcpy if inputs alias.

For slot 0, copy actor `1d74+sourceBank*2` then its next byte to the destination
bank pair, each load followed by its store. Only when `skipPose==0` call
`8004b8f4` for the selected start/end. The signed loop tests start < end before
reading descriptor `4b0` or any joint-list payload.

For each joint, sign-extend descriptor byte `8c+index`. Quaternion bank stride
is `200`, joint stride `10`, base `ed4`; translation bank stride is `180`, joint
stride `0c`, base `12d4`. Copy quaternion first: load components 0/4, store 0/4,
then load 8/c, store 8/c. Next translation: load 0/4, store 0/4, then load 8,
store 8. Increment the list index and retest against end. Empty ranges require
no joint lookup and perform no pose-bank copies.

## Blend `8004a8cc`

Let `t` be input f1. Compute `1-t` with `fsubs` before calling `8004b8f4`.
For each selected signed joint index:

1. Scale bank-zero translation `12d4+joint*0c` by `1-t` into a local vector.
2. Scale bank-one translation `1454+joint*0c` by `t` into another local vector.
3. Call the existing vector add into bank-zero translation. This write occurs
   **before quaternion comparison or any slerp refusal**.
4. Copy bank-zero quaternion `ed4+joint*10` and bank-one quaternion
   `10d4+joint*10` into local four-component values. Compute each component's
   rounded single sum and difference, and their rounded single squares.
   For both square sums, the addition tree is `(z² + (x² + y²)) + w²`, with
   actual operand order `w² + (z² + (x² + y²))` for the final `fadds`. The
   exact interleaved instruction order appears in the witness at
   `8004a9a8..8004aa14`; this is separate multiplies/adds, not fused arithmetic.
5. Compare squared difference against squared sum at `8004aa18`. Only when
   difference > sum negate the **local bank-one quaternion** xyzw, storing its
   four negations to the stack. No source bank-one quaternion is overwritten.
6. Call `C_QUATSlerp(t, localBank0, localBank1, bank0Destination)` at `8004aa50`.
7. Only after that call returns, scan exactly two signed descriptor IDs at
   `42` and `43`, stopping at the first match. For matching index i, if
   `t > 0.5` copy byte `actor+1d76+i` to `actor+1d94+i`; otherwise copy
   `actor+1d74+i`. At exactly 0.5 use the latter. No match means no such store.
8. Increment the joint-list index and test against end again.

### Three-component scale `8020ba9c`

Complete schedule, using caller f1.PS0 as the scale:

1. `psq_l f0,0(r3),W=0,I=0`: load xy.
2. `psq_l f2,8(r3),W=1,I=0`: load z (the paired second lane is implicit 1).
3. `ps_muls0 f0,f0,f1`: multiply xy by scale.PS0.
4. `psq_st f0,0(r4),W=0,I=0`: store xy.
5. `ps_muls0 f0,f2,f1`: multiply the saved z pair by scale.PS0.
6. `psq_st f0,8(r4),W=1,I=0`: store z only.
7. `blr`.

All xyz source components are loaded before any destination store. Paired
arithmetic is single precision; it is not a fused multiply-add. Float load/store
interpretation requires **GQR0 float format, scale 0** as an execution-domain
precondition. Neither archive proves the machine's live GQR0, FPSCR rounding
mode, non-IEEE mode, exception enables or flags. A runtime that models ordinary
finite round-to-nearest behavior must say so and retain narrower refusals where
it does not implement Gekko exceptional/denormal behavior.

### Quaternion slerp `8020bf08`

The archived instructions contradict any assumption of a fused dot product.
They compute four **`fmuls`** products, then **`fadds`** in this order:

- `px=mul(ax,bx)`; `py=mul(ay,by)`; `pz=mul(az,bz)`;
- `xy=add(px,py)`; `pw=mul(aw,bw)`;
- `xyz=add(pz,xy)`; `dot=add(pw,xyz)`.

Initialize sign to 1. If dot < 0, negate dot and sign. Compare the resulting
dot against `8043cac0` (`0.9999899864196777`). Instruction `8020bfa0` is
`cror cr0.eq,cr0.lt,cr0.eq`; the following branch goes to the linear path only
when neither less-than nor equality is set. Thus **finite dot must be strictly
greater than the threshold**, not equal. Unordered also clears both flags; it
is not evidence that a finite-only implementation handles NaN behavior.

Linear path `8020bfe0..8020bfec` computes `signWeight=fmuls(sign,t)` and
`otherWeight=fsubs(1,t)`. For x, y, z, then w: load that A component and B
component, multiply them separately by otherWeight and signWeight with
`fmuls`, add with `fadds`, and store **before loading the next pair**. No
normalization and no `fmadds` occurs anywhere in this function.

The other path calls `8023cc8c` at `8020bfa8`, then `8023cc44` at
`8020bfb0`, `8020bfc4` and `8020bfd0`, with intervening `fsubs`, `fmuls` and
`fdivs` as recorded in the full witness. These are only identified call
boundaries here; this reader does not select their bodies. A linear-only
implementation must refuse the nonlinear path without erasing preceding real
translation writes or pretending that the call was a no-op. Decompiler names
for these calls do not establish their mathematical behavior.

## Reproduction and test ceiling

Run from the repository root:

```sh
python3 -m unittest discover -s research/tools/matching-decomp -p test_archived_actor_mode1_evidence.py -v
python3 research/tools/matching-decomp/read_archived_actor_mode1_evidence.py 'research/decomp/GotchaForce.rep.before_force_create/idata/00/~00000000.db/db.3.gbf'
python3 research/tools/matching-decomp/read_archived_actor_mode1_evidence.py 'research/decomp/GotchaForce.rep.before_force_create/idata/00/~00000000.db/db.4.gbf'
```

The focused suite has **18 synthetic/source tests and 3 local-archive tests**.
The frozen witnesses contain all 553 decoded operand rows; an independent
inverse encoder reconstructs each span's exact digest without calling the
decoder. Synthetic tests cover field directions, signed immediates, SPR/CR,
conditional branches, single and paired floating forms, reserved-bit guards,
fixed selection/mapping failures, schema/authentication order and narrow CLI.
Local tests authenticate both complete snapshots and compare all operands,
constants, mappings, provenance and zero-omission coverage. If either local
archive is missing, local tests skip rather than fetch another input.

A passing suite establishes the fixed archived evidence and guards. It does
not upgrade runtime work to behavioral parity, matching `MATCH`, a real clone
producer, or browser playability. Other callees, stream/descriptor payloads,
live state, original executable and arbitrary pointers remain outside this
reader's scope.
