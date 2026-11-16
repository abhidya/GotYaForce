# Object scheduler: bounded archive evidence

Date: 2026-11-14. Investigation base:
`05e983205582f83313e38539ded6b8eec99449c6` (preserved, no commit or push).

The [fixed reader](../tools/matching-decomp/read_archived_object_scheduler_evidence.py)
authenticates **three complete bodies /596 bytes /149 instructions**. The
[independent tests](../tools/matching-decomp/test_archived_object_scheduler_evidence.py)
manually specify every operand and inverse-encode all three payload hashes.
Both existing snapshots agree on every selected instruction, mapping and
physical span. All **16 scheduler tests pass**.

This is **static archived ProgramDB evidence**, not independently measured
original-DOL identity, original execution, `MATCH`, live dispatch, runtime
integration or playability. Global object ownership and live callback targets
remain unselected. No shared reader, authenticator, decoder or allowlist changed.

## Selection and provenance before access

Before either archive's first selected read, the complete fixed selection and
independent provenance were recorded in ignored
`.tmp/object-scheduler-evidence-20261114/scope.json`, SHA-256
`c92f88e9a29f37f0fa9250169e207dbf16d30773c3f6a734d6e99f44a41a8ffd`.
No read address or extent was obtained by following a returned pointer.

| Entry | End, exclusive | Width | Independent provenance |
| --- | --- | --- | --- |
| `80089898` | `8008997c` | 228 | `ghidra-export/chunk_0013.c:461–497`; `_index.tsv:1962–1963`; map1075 explicitly gives size `e4` |
| `8008997c` | `80089a94` | 280 | `chunk_0013.c:499–544`; index1963–1964; map1076 gives size `118` |
| `80089a94` | `80089aec` | 88 | `chunk_0013.c:546–562`; index1964–1965; map1077 gives size `58` |

Map means `research/symbols/GG4E-CSM-20220412.map`. The C and index identify
three adjacent complete named bodies; the map independently supplies their
sizes. The next function `80089aec` is not selected. No group-head cell,
eligibility pointer/object, pause-owner pointer/object or callback body is
selected here. Reused [cleanup evidence](projectile-cleanup-evidence-2026-11-14.md)
for `80088e50` and `80089814` is joined by its already authenticated width/hash,
without rereading either body.

## Authentication, hashes and physical spans

Unchanged `read_archived_constants.inspect` verifies the actual complete SHA-256,
supported table schemas, PowerPC language, image/address map, metadata, empty
File Bytes table and complete data5 hash/controls **before any selected read**.
Unchanged `command.mappings` validates text1/data3/data5 and their initialized
subblocks, bounds and overlaps. Exact typed text1 mapping is checked again.
Selected widths and SHA-256 hashes are checked before any instruction is decoded.

Existing snapshots are under
`GotchaForce.rep.before_force_create/idata/00/~00000000.db/`:

| Snapshot | Bytes | Complete SHA-256 |
| --- | --- | --- |
| `db.3.gbf` | 57655296 | `7b50dd2d2e17b4bfcc89a64cde27010247d0cbf0f48bd5c059f50275f40458d0` |
| `db.4.gbf` | 58802176 | `1f86813d91ea8e2c4564f96622ec42555e1dba2c78aa81ad654e892140d019f8` |

File Bytes version0/root−1/count0; image offset `80000000`; block size16384;
master root1. Executable metadata SHA-256
`21454a8880c6254616662710d6ec626e43d853999da2cdfad700030960a94836`
is import metadata, **not an independently measured original-DOL hash**.
Full data5 SHA-256:
`989c794b17fc95de6e57810f5c89db23d585c85a15faafc994d9a5bd9a0e61b4`.
Text1 maps `[800055e0,802b0160)`, length2796416, block/subblock1,
initialized subblock type2, chain root21, starting/source offsets0.

| Selection | Width | SHA-256 |
| --- | --- | --- |
| `80089898` | 228 | `126a25b8262b9ec16da7e6121fd72318cce3c39faab481f718d2a559307c1299` |
| `8008997c` | 280 | `3d628d2b7b32b3cd2c7e0816370547898bb863673bd68351246c797720e57eab` |
| `80089a94` | 88 | `dcb8bf7edce7313e0e258ee526af82153e5e35eac0987938a42cccc6a270dde4` |

The following physical spans are identical in both snapshots. Offsets are
decimal. All three selections lie in the same obfuscated data buffer.

| Selection | Root /data buffer | Chain offset | Data offset | Physical offset | Bytes |
| --- | --- | --- | --- | --- | --- |
| `80089898` | 21 /55 | 541368 | 894 | 918404 | 228 |
| `8008997c` | 21 /55 | 541596 | 1122 | 918632 | 280 |
| `80089a94` | 21 /55 | 541876 | 1402 | 918912 | 88 |

Exact additional chain calls after unchanged full authentication:

```
(21,541368,228,2796416)
(21,541596,280,2796416)
(21,541876,88,2796416)
```

Tests compare the **complete** call trace against the authenticator's own
preceding full-data5/control reads plus exactly these three calls. They do
not merely compare an isolated list of new selections.

## Source behavior

Field offsets below are hexadecimal. Group parameters are full 32-bit words;
comparisons at `898a0`, `898c0`, `89990`, `899b4` and `89aa8` are **signed**.
The source does not clamp negative groups or prove table bounds. Shift/add
address calculations retain their 32-bit PPC word semantics.

### Single-group walker `80089898`

If signed group<56 and low3(group)!=7, read the pause-owner pointer from
**r13−31852**. C names that pointer slot `PTR_DAT_80433934`, but these code
bytes do not independently establish a live r13 value or the pointer's value.
Read unsigned owner+d2 when signed group<8, otherwise owner+d1. If bit0x80
is set, return before reading a group head. Groups with signed group>=56 or
low3==7 bypass the entire pause read; this is not a general global-pause test.

If admitted, construct absolute group-head base **803c706c**, form the low32
index group*4, and load the current group's head once into r30. Preload zero
into r31. Loop until the cursor is null:

1. Load byte cursor0, sign-extend with record bit, and skip all snapshot,
   callback and post-callback work if it is zero. Any signed nonzero byte is
   active; the source does not require exactly1 or positive.
2. Copy the fields in the exact interleaved order below, call stored callback
   cursor0c with cursor in r3, then inspect live cursor86 after normal return.
3. If signed cursor86 is nonzero, clear cursor1ca with the saved zero.
4. **Reload cursor8 into the cursor register** and perform the null test.

The cursor8 read is after callback and post-callback work, not prefetched
before the callback. The source does not recheck active0 after a callback
clears it. An initially inactive node still loads its live next8. There is
no callback-null guard, cycle guard or list-membership check.

### Six eligibility groups `8008997c`

If signed base>=56, return without table/pause/list reads. Otherwise initialize
i=0 and eligibility pointer slot at absolute **803c4e84**. Each of six iterations
(i=0..5) reads the pointer in that slot and immediately reads/sign-extends its
byte0. **There is no null-pointer guard** between the pointer and byte loads.
This global eligibility object is not the current list node or a node field.

Only if eligibility byte0 is nonzero does this iteration reread the pause-owner
pointer at r13−31852. Choose unsigned owner+d2 for signed **base**<8, otherwise
owner+d1, and skip this group if bit(1<<i) is set. The choice depends on the
original base, not base+i+1. In particular, a direct call with an unaligned
base need not match a caller's assumed eight-group partition.

If eligible and unpaused, calculate low32(base+i), multiply by4 modulo32,
add base803c706c, and load at displacement4. This is head
**803c706c[base+i+1]**, equivalently C's803c7070[base+i], not head[base+i].
Load the head once for this group into r27, preload zero r28, then perform
the same active/snapshot/callback/postfield/live-next loop as `89898`.

After the group's list ends or the eligibility/pause gate skips it, increment
i by1, increment eligibility slot address by4, compare signed i<6 and loop.
The next eligibility pointer, its active byte, pause-owner pointer/byte, and
admitted group head are read at their own iteration, after prior callbacks.
They are not captured as a six-element snapshot. The current group's pause
mask is not retested for each node.

### Exact snapshots and callback ordering in both walkers

The following are actual instruction operations, not five atomic assignments.
`obj` means r30 in `89898` and r27 in `8997c`; `zero` is r31 or r28 respectively.
The fixed segment begins at `80089910` or `80089a1c`:

```
lwz  r4,obj+20
mr   r3,obj
lwz  r0,obj+24
stw  r4,obj+2c
stw  r0,obj+30
lwz  r0,obj+28
stw  r0,obj+34
lwz  r0,obj+70
stw  r0,obj+76
lhz  r0,obj+74
sth  r0,obj+7a
lwz  r12,obj+0c
mtctr r12
bctrl
lbz  r0,obj+86
extsb. r0,r0
beq  next-load
stb  zero,obj+1ca
next-load: lwz obj,obj+8
```

`mr` is the decoded `or` with the same source twice. r3 remains the object
at the indirect call. The callback address itself is loaded **after all five
stores**, never taken from a factory or static replacement. Word copies are
raw32 operations, not floating-point conversions. `lhz` reads unsigned16.
The two adjacent rotation regions are source70..75 and destination76..7b;
the word store really uses displacement **76**, followed by unsigned halfword
load74 and halfword store7a. It must not be relabeled as two source halfword
stores or reordered before the preceding source loads/stores.

**Alignment ceiling:** this proves the `stw` instruction operand `obj+76`.
For a four-byte-aligned object base, that is not a four-byte-aligned address.
A browser clone may explicitly admit a bounded big-endian byte-buffer model
for this one scheduler-authorized word store, with scalar bounds preflight.
Such an admission is a host-model rule, **not proof of GameCube hardware
alignment acceptance, alignment-exception behavior, or execution of this
store on original hardware**. This evidence makes no general relaxation of
allocator word-alignment requirements and introduces no runtime code.

All post-callback claims are conditional on normal return. If the callback
faults or reaches an unresolved boundary, later86,1ca and next8 operations
cannot be credited as completed. The C signatures are void; these functions
do not establish a stable count/boolean/object return API for the clone.

### Wrapper `80089a94`

Capture original base in r31. If signed base<56 and low3(base)==0, call in
this exact order, assuming each call returns:

1. `8008997c(base)`: eligibility groups base+1 through base+6, in ascending i.
2. `80089898(base)`: restored original base, with that walker's bit0x80 gate.
3. `80089898(low32(base+7))`: last group, with that walker's low3==7 bypass.

Otherwise call only `80089898(base)`. The wrapper does not run the base
group before the six eligibility groups. All group-head/owner reads remain
inside those calls; wrapper entry does not prefetch them. There is no new
nonnegative-base guard or separate wrapper-level pause gate. Signed negative
bases therefore cannot be silently converted into source no-ops; a bounded
host admission must report unavailable/invalid memory where applicable.

### Cleanup continuation and live-data limits

Reused cleanup evidence establishes that `80088e50` can unlink the current
object and eventually call `80089814`, which clears active0 and object4 but
**does not clear object8**. Combined with these scheduler operands, a normally
returning cleanup callback still reaches post-callback86 and then reloads
that retained next8. The scheduler does not abandon the walk merely because
cleanup cleared the current object's active byte. If another callback changes
object8, the new value is observed instead. No unconditional traversal of a
saved pre-callback next is supported.

This joins static order only. It does not prove any particular live node's
callback target, that a cleanup boundary returns, current eligibility object
identities, current pause state, initial list contents, valid group indices,
absence of list cycles or frame-level parity.

## Tests and reproducibility

The semantic fixtures are manually authored independently of the runtime
reader, then inverse-encoded without importing a decoder/report/archive as
expected data. All149 rows reproduce the three fixed payload hashes.
Every one of **4768 instruction-bit mutations** either refuses or decodes to
different operands that independently encode back to the exact changed word.
Every one of **4768 selected-payload bit mutations** fails the selected hash
before instruction interpretation. All **33 control-flow rows** are checked,
with **175 mutations** of their mnemonic, target and BO/BI/BH/AA/LK fields.

The16 tests also cover exact typed mappings, widths, truncation, duplicate
allowlists, neighboring/arbitrary selections, reserved decoder fields,
all six supported schemas (each schema's version/keytype/types/field names
and missing table), whole-file digest tampering, all selected payloads,
complete before/after read traces and physical spans, exact snapshot/store
interleaving, signed pause/eligibility tests, live-next order, wrapper order,
source extents, reused identities and arbitrary-CLI refusal.

Discovery found four instruction-form families beyond the reused normal-actor decoder's admitted
set: unsigned halfword `lhz`, `stmw`/`lmw`, `slw`, and BO12/BI0 conditional
branch. The local decoder admits them with every bit represented or fixed;
shared decoder behavior is unchanged. No archive identity, selected-data
hash, schema or mapping authentication failed. The initial test run found
only an incorrect expected mutation-count total (179 rather than175), fixed
before final verification; no instruction fixture or selected hash changed.

Completed locally, with no installation, fetch, original execution, runtime/
estimator import, commit or push:

```
python -m unittest discover -s research/tools/matching-decomp -p test_archived_object_scheduler_evidence.py -v
python research/tools/matching-decomp/read_archived_object_scheduler_evidence.py research/decomp/GotchaForce.rep.before_force_create/idata/00/~00000000.db/db.3.gbf
python research/tools/matching-decomp/read_archived_object_scheduler_evidence.py research/decomp/GotchaForce.rep.before_force_create/idata/00/~00000000.db/db.4.gbf
```

Additional focused regressions pass: **28 object evidence tests** (16 scheduler
plus12 allocator) and **19 projectile-cleanup tests**. The shared authenticator,
command reader, normal-actor decoder and cleanup reader have no diff from the
investigation base. These are focused evidence checks, not contributor/docs
verification, runtime integration tests or browser playability acceptance.

Derived reports remain ignored:

| Report | SHA-256 |
| --- | --- |
| `.tmp/object-scheduler-evidence-20261114/db3.json` | `a0c9bd77e2a7a91f8b112a4855a2f8408b48335f8ec19cabdb4db1d7cc7d72c9` |
| `.tmp/object-scheduler-evidence-20261114/db4.json` | `4296d3f6377c6493029f9dcb59a971796129d94b33f1b6afc5938ea20fb5a933` |

## Complete decoded instruction operands

Every selected instruction appears below, in source order, without gaps.
Addresses/targets are hexadecimal; all other numbers are decimal, including
immediates and displacements. `mflr/mtlr` fix SPR8/Rc0; `mtctr` fixes SPR9/Rc0;
`lwzx` fixes reserved Rc0; compare forms fix unrepresented reserved fields;
branch-register XO is16 for LR and528 for CTR. Every other admitted bit is
represented in the named operands or fixed by the instruction mnemonic.

### `80089898`: 57 instructions /228 bytes

| PC | Complete operands |
| --- | --- |
| `80089898` | `stwu rS=1, rA=1, displacement=-16` |
| `8008989c` | `mflr rD=0` |
| `800898a0` | `cmpi BF=0, L=0, rA=3, immediate=56` |
| `800898a4` | `stw rS=0, rA=1, displacement=20` |
| `800898a8` | `stw rS=31, rA=1, displacement=12` |
| `800898ac` | `stw rS=30, rA=1, displacement=8` |
| `800898b0` | `bc BO=4, BI=0, LK=0, target=800898ec, AA=0` |
| `800898b4` | `rlwinm rS=3, rA=0, SH=0, MB=29, ME=31, Rc=0` |
| `800898b8` | `cmpi BF=0, L=0, rA=0, immediate=7` |
| `800898bc` | `bc BO=12, BI=2, LK=0, target=800898ec, AA=0` |
| `800898c0` | `cmpi BF=0, L=0, rA=3, immediate=8` |
| `800898c4` | `bc BO=4, BI=0, LK=0, target=800898dc, AA=0` |
| `800898c8` | `lwz rD=4, rA=13, displacement=-31852` |
| `800898cc` | `lbz rD=0, rA=4, displacement=210` |
| `800898d0` | `rlwinm rS=0, rA=0, SH=0, MB=24, ME=24, Rc=1` |
| `800898d4` | `bc BO=12, BI=2, LK=0, target=800898ec, AA=0` |
| `800898d8` | `b target=80089964, AA=0, LK=0` |
| `800898dc` | `lwz rD=4, rA=13, displacement=-31852` |
| `800898e0` | `lbz rD=0, rA=4, displacement=209` |
| `800898e4` | `rlwinm rS=0, rA=0, SH=0, MB=24, ME=24, Rc=1` |
| `800898e8` | `bc BO=4, BI=2, LK=0, target=80089964, AA=0` |
| `800898ec` | `addis rD=4, rA=0, immediate=-32708` |
| `800898f0` | `rlwinm rS=3, rA=0, SH=2, MB=0, ME=29, Rc=0` |
| `800898f4` | `addi rD=3, rA=4, immediate=28780` |
| `800898f8` | `addi rD=31, rA=0, immediate=0` |
| `800898fc` | `lwzx rD=30, rA=3, rB=0` |
| `80089900` | `b target=8008995c, AA=0, LK=0` |
| `80089904` | `lbz rD=0, rA=30, displacement=0` |
| `80089908` | `extsb rS=0, rA=0, Rc=1` |
| `8008990c` | `bc BO=12, BI=2, LK=0, target=80089958, AA=0` |
| `80089910` | `lwz rD=4, rA=30, displacement=32` |
| `80089914` | `or rS=30, rA=3, rB=30, Rc=0` |
| `80089918` | `lwz rD=0, rA=30, displacement=36` |
| `8008991c` | `stw rS=4, rA=30, displacement=44` |
| `80089920` | `stw rS=0, rA=30, displacement=48` |
| `80089924` | `lwz rD=0, rA=30, displacement=40` |
| `80089928` | `stw rS=0, rA=30, displacement=52` |
| `8008992c` | `lwz rD=0, rA=30, displacement=112` |
| `80089930` | `stw rS=0, rA=30, displacement=118` |
| `80089934` | `lhz rD=0, rA=30, displacement=116` |
| `80089938` | `sth rS=0, rA=30, displacement=122` |
| `8008993c` | `lwz rD=12, rA=30, displacement=12` |
| `80089940` | `mtctr rS=12` |
| `80089944` | `bctrl BO=20, BI=0, BH=0, LK=1` |
| `80089948` | `lbz rD=0, rA=30, displacement=134` |
| `8008994c` | `extsb rS=0, rA=0, Rc=1` |
| `80089950` | `bc BO=12, BI=2, LK=0, target=80089958, AA=0` |
| `80089954` | `stb rS=31, rA=30, displacement=458` |
| `80089958` | `lwz rD=30, rA=30, displacement=8` |
| `8008995c` | `cmpli BF=0, L=0, rA=30, immediate=0` |
| `80089960` | `bc BO=4, BI=2, LK=0, target=80089904, AA=0` |
| `80089964` | `lwz rD=0, rA=1, displacement=20` |
| `80089968` | `lwz rD=31, rA=1, displacement=12` |
| `8008996c` | `lwz rD=30, rA=1, displacement=8` |
| `80089970` | `mtlr rS=0` |
| `80089974` | `addi rD=1, rA=1, immediate=16` |
| `80089978` | `blr BO=20, BI=0, BH=0, LK=0` |

### `8008997c`: 70 instructions /280 bytes

| PC | Complete operands |
| --- | --- |
| `8008997c` | `stwu rS=1, rA=1, displacement=-32` |
| `80089980` | `mflr rD=0` |
| `80089984` | `stw rS=0, rA=1, displacement=36` |
| `80089988` | `stmw rS=27, rA=1, displacement=12` |
| `8008998c` | `or rS=3, rA=29, rB=3, Rc=0` |
| `80089990` | `cmpi BF=0, L=0, rA=29, immediate=56` |
| `80089994` | `bc BO=4, BI=0, LK=0, target=80089a80, AA=0` |
| `80089998` | `addis rD=3, rA=0, immediate=-32708` |
| `8008999c` | `addi rD=30, rA=0, immediate=0` |
| `800899a0` | `addi rD=31, rA=3, immediate=20100` |
| `800899a4` | `lwz rD=3, rA=31, displacement=0` |
| `800899a8` | `lbz rD=0, rA=3, displacement=0` |
| `800899ac` | `extsb rS=0, rA=0, Rc=1` |
| `800899b0` | `bc BO=12, BI=2, LK=0, target=80089a70, AA=0` |
| `800899b4` | `cmpi BF=0, L=0, rA=29, immediate=8` |
| `800899b8` | `bc BO=4, BI=0, LK=0, target=800899d8, AA=0` |
| `800899bc` | `lwz rD=3, rA=13, displacement=-31852` |
| `800899c0` | `addi rD=0, rA=0, immediate=1` |
| `800899c4` | `slw rS=0, rA=0, rB=30, Rc=0` |
| `800899c8` | `lbz rD=3, rA=3, displacement=210` |
| `800899cc` | `and rS=3, rA=0, rB=0, Rc=1` |
| `800899d0` | `bc BO=4, BI=2, LK=0, target=80089a70, AA=0` |
| `800899d4` | `b target=800899f0, AA=0, LK=0` |
| `800899d8` | `lwz rD=3, rA=13, displacement=-31852` |
| `800899dc` | `addi rD=0, rA=0, immediate=1` |
| `800899e0` | `slw rS=0, rA=0, rB=30, Rc=0` |
| `800899e4` | `lbz rD=3, rA=3, displacement=209` |
| `800899e8` | `and rS=3, rA=0, rB=0, Rc=1` |
| `800899ec` | `bc BO=4, BI=2, LK=0, target=80089a70, AA=0` |
| `800899f0` | `add rD=0, rA=29, rB=30, Rc=0` |
| `800899f4` | `addis rD=3, rA=0, immediate=-32708` |
| `800899f8` | `rlwinm rS=0, rA=4, SH=2, MB=0, ME=29, Rc=0` |
| `800899fc` | `addi rD=28, rA=0, immediate=0` |
| `80089a00` | `addi rD=0, rA=3, immediate=28780` |
| `80089a04` | `add rD=3, rA=0, rB=4, Rc=0` |
| `80089a08` | `lwz rD=27, rA=3, displacement=4` |
| `80089a0c` | `b target=80089a68, AA=0, LK=0` |
| `80089a10` | `lbz rD=0, rA=27, displacement=0` |
| `80089a14` | `extsb rS=0, rA=0, Rc=1` |
| `80089a18` | `bc BO=12, BI=2, LK=0, target=80089a64, AA=0` |
| `80089a1c` | `lwz rD=4, rA=27, displacement=32` |
| `80089a20` | `or rS=27, rA=3, rB=27, Rc=0` |
| `80089a24` | `lwz rD=0, rA=27, displacement=36` |
| `80089a28` | `stw rS=4, rA=27, displacement=44` |
| `80089a2c` | `stw rS=0, rA=27, displacement=48` |
| `80089a30` | `lwz rD=0, rA=27, displacement=40` |
| `80089a34` | `stw rS=0, rA=27, displacement=52` |
| `80089a38` | `lwz rD=0, rA=27, displacement=112` |
| `80089a3c` | `stw rS=0, rA=27, displacement=118` |
| `80089a40` | `lhz rD=0, rA=27, displacement=116` |
| `80089a44` | `sth rS=0, rA=27, displacement=122` |
| `80089a48` | `lwz rD=12, rA=27, displacement=12` |
| `80089a4c` | `mtctr rS=12` |
| `80089a50` | `bctrl BO=20, BI=0, BH=0, LK=1` |
| `80089a54` | `lbz rD=0, rA=27, displacement=134` |
| `80089a58` | `extsb rS=0, rA=0, Rc=1` |
| `80089a5c` | `bc BO=12, BI=2, LK=0, target=80089a64, AA=0` |
| `80089a60` | `stb rS=28, rA=27, displacement=458` |
| `80089a64` | `lwz rD=27, rA=27, displacement=8` |
| `80089a68` | `cmpli BF=0, L=0, rA=27, immediate=0` |
| `80089a6c` | `bc BO=4, BI=2, LK=0, target=80089a10, AA=0` |
| `80089a70` | `addi rD=30, rA=30, immediate=1` |
| `80089a74` | `addi rD=31, rA=31, immediate=4` |
| `80089a78` | `cmpi BF=0, L=0, rA=30, immediate=6` |
| `80089a7c` | `bc BO=12, BI=0, LK=0, target=800899a4, AA=0` |
| `80089a80` | `lmw rD=27, rA=1, displacement=12` |
| `80089a84` | `lwz rD=0, rA=1, displacement=36` |
| `80089a88` | `mtlr rS=0` |
| `80089a8c` | `addi rD=1, rA=1, immediate=32` |
| `80089a90` | `blr BO=20, BI=0, BH=0, LK=0` |

### `80089a94`: 22 instructions /88 bytes

| PC | Complete operands |
| --- | --- |
| `80089a94` | `stwu rS=1, rA=1, displacement=-16` |
| `80089a98` | `mflr rD=0` |
| `80089a9c` | `stw rS=0, rA=1, displacement=20` |
| `80089aa0` | `stw rS=31, rA=1, displacement=12` |
| `80089aa4` | `or rS=3, rA=31, rB=3, Rc=0` |
| `80089aa8` | `cmpi BF=0, L=0, rA=31, immediate=56` |
| `80089aac` | `bc BO=4, BI=0, LK=0, target=80089ab8, AA=0` |
| `80089ab0` | `rlwinm rS=31, rA=0, SH=0, MB=29, ME=31, Rc=1` |
| `80089ab4` | `bc BO=12, BI=2, LK=0, target=80089ac4, AA=0` |
| `80089ab8` | `or rS=31, rA=3, rB=31, Rc=0` |
| `80089abc` | `bl target=80089898, AA=0, LK=1` |
| `80089ac0` | `b target=80089ad8, AA=0, LK=0` |
| `80089ac4` | `bl target=8008997c, AA=0, LK=1` |
| `80089ac8` | `or rS=31, rA=3, rB=31, Rc=0` |
| `80089acc` | `bl target=80089898, AA=0, LK=1` |
| `80089ad0` | `addi rD=3, rA=31, immediate=7` |
| `80089ad4` | `bl target=80089898, AA=0, LK=1` |
| `80089ad8` | `lwz rD=0, rA=1, displacement=20` |
| `80089adc` | `lwz rD=31, rA=1, displacement=12` |
| `80089ae0` | `mtlr rS=0` |
| `80089ae4` | `addi rD=1, rA=1, immediate=16` |
| `80089ae8` | `blr BO=20, BI=0, BH=0, LK=0` |
