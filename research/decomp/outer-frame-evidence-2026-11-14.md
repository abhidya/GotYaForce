# Outer-frame prefix: bounded archive evidence

Date: 2026-11-14. Investigation base:
`1fc4ddc5f3816ef9d7e2fd832207fa60ba46de6d` (preserved, no commit or push).

The [fixed reader](../tools/matching-decomp/read_archived_outer_frame_evidence.py)
authenticates **five complete bodies /1080 bytes /270 instructions**. The
[independent tests](../tools/matching-decomp/test_archived_outer_frame_evidence.py)
manually specify every instruction operand and inverse-encode all five payload
hashes. Both existing snapshots agree on every selected instruction, mapping
and physical span. All **17 outer-frame evidence tests pass**, plus **28 existing
object scheduler/allocator evidence regressions**.

The useful extension is a real outer-frame prefix: consume the queued mode
request, refresh four team records in source order, and stop at the first
unresolved callee. A populated burst-active record clears its charged byte
before reaching `8008b290`. If every refresh returns, mode zero reaches
`80053b30`; nonzero mode reaches `8000bef4`. **None of those paths yet authorizes
a scheduler callback or a completed frame.**

This is static archived ProgramDB evidence, not independently measured
original-DOL identity, original execution, `MATCH`, live dispatch, runtime
integration or playability. Global pointer contents and floating constants
remain unselected. No shared authenticator, mapping validator, decoder or
allowlist changed. The decompiled C supplied independent body identities and
bounds; the behavior below follows authenticated instruction operands, not an
assumption that the C is correct.

## Scope frozen before selected reads

The initial three-body proposal was recorded in ignored
`.tmp/outer-frame-evidence-20261114/scope.json` without reading any selected
archive payload. Before the first selected read, that proposal was expanded
with the two independently bounded team-refresh bodies and frozen as
`.tmp/outer-frame-evidence-20261114/scope-frozen.json`, SHA-256
`f77f0d7870d1b9965791fb63cb2d586f5618cdf57ba4cb6fcb81b3b3ed47cedb`.
The final selection remained unchanged thereafter.

| Entry | End, exclusive | Bytes | Independent readable provenance |
| --- | --- | --- | --- |
| `80029434` | `80029574` | 320 | `ghidra-export/chunk_0003.c:4304–4356`; `_index.tsv:525–526`; map365 size`140` |
| `8008b048` | `8008b08c` | 68 | `chunk_0013.c:1544–1554`; index1989–1990; map1096 size`44` |
| `8008b010` | `8008b038` | 40 | `chunk_0013.c:1515–1530`; index1987–1988; map1094 size`28` |
| `80029d48` | `80029e98` | 336 | `chunk_0003.c:4745–4803`; index538–539; map375 size`150` |
| `80029e98` | `80029fd4` | 316 | `chunk_0003.c:4807–4862`; index539–540; map376 size`13c` |

Map means `research/symbols/GG4E-CSM-20220412.map`. The C and index give the
named complete bodies and their successors; the map independently states each
size. Neither a returned code/data pointer nor a decoded call target selected
a new archive read. `8008b290`, `8008b480`, `80053b30`, `8000bef4`, all other
outer callees, globals, pointer cells and floating constants are unselected.
The already authenticated scheduler bodies `80089898` and `80089a94` are
reused by their existing widths/hashes, without rereading either body. See
[object scheduler evidence](object-scheduler-evidence-2026-11-14.md).

## Authentication and exact reads

Unchanged `read_archived_constants.inspect` verifies the complete actual file
SHA-256, supported schemas, PowerPC language, image/address map, metadata,
empty File Bytes table and full data5 hash/controls before any selected read.
Unchanged `command.mappings` validates text1/data3/data5 and their initialized
subblocks, bounds and overlaps. Exact typed text1 mapping is checked again.
Selected widths and SHA-256 hashes are checked before instruction decoding.

The two existing private snapshots are under
`GotchaForce.rep.before_force_create/idata/00/~00000000.db/`:

| Snapshot | Bytes | Complete SHA-256 |
| --- | --- | --- |
| `db.3.gbf` | 57655296 | `7b50dd2d2e17b4bfcc89a64cde27010247d0cbf0f48bd5c059f50275f40458d0` |
| `db.4.gbf` | 58802176 | `1f86813d91ea8e2c4564f96622ec42555e1dba2c78aa81ad654e892140d019f8` |

File Bytes version0/root−1/count0; image offset`80000000`; block size16384;
master root1. Executable metadata SHA-256
`21454a8880c6254616662710d6ec626e43d853999da2cdfad700030960a94836`
is import metadata, not an independently measured original-DOL hash. Full
data5 SHA-256 is
`989c794b17fc95de6e57810f5c89db23d585c85a15faafc994d9a5bd9a0e61b4`.
Text1 maps `[800055e0,802b0160)`, length2796416, block/subblock1,
initialized subblock type2, chain root21, starting/source offsets0.

| Body | Bytes | SHA-256 |
| --- | --- | --- |
| `80029434` | 320 | `6b951fb1955f3acb931beff0831af002d9b6ff9b108a15796a3114b5020b1b6c` |
| `8008b048` | 68 | `f301aa22755c8f9c590db04552e1461969fbdb7f0df11c62b225eed6b77c264d` |
| `8008b010` | 40 | `979ef724f8f7c5c40352c666b8676668553d3f5333961b61443f2eafbb5b7b8e` |
| `80029d48` | 336 | `cafbf7ba2143ecf749bfec6a51d4d7525da518e34836b42c07e591009d47feb0` |
| `80029e98` | 316 | `b6a32d4c3b5911b5974991cf21f060fc128e48d8116cabb0c96f146cdaeae450` |

Physical spans are identical in both snapshots. Offsets are decimal; all
selected spans are in obfuscated data buffers.

| Body | Root/buffer | Chain offset | Data offset | Physical offset | Bytes |
| --- | --- | --- | --- | --- | --- |
| `80029434` | 21/30 | 147028 | 16004 | 523914 | 320 |
| `8008b048` | 21/55 | 547432 | 6958 | 924468 | 68 |
| `8008b010` | 21/55 | 547376 | 6902 | 924412 | 40 |
| `80029d48` | 21/31 | 149352 | 1950 | 526244 | 336 |
| `80029e98` | 21/31 | 149688 | 2286 | 526580 | 316 |

Exact additional chain calls, following unchanged full authentication:

```
(21,147028,320,2796416)
(21,547432,68,2796416)
(21,547376,40,2796416)
(21,149352,336,2796416)
(21,149688,316,2796416)
```

Tests compare the complete before/after chain trace against the authenticator's
own full-data5/control reads followed by exactly these five calls. Zero selected
data cells does not mean the required authenticator data5 reads were omitted.

## Earliest request consumer and setter

Field offsets in this section and below are hexadecimal. `owner` is a pointer
loaded from **r13−31852**. C names that slot `PTR_DAT_80433934`, but these
instructions establish neither the live r13 value nor the pointer's value.

Outer `80029434` calls `8008b048` at`80029440`, then calls `80029d48` at
`80029444`. No mode check or scheduler call precedes those mandatory calls.

`8008b048` loads unsigned byte owner+15d4 into r3. `extsb.` into r0 tests the
signed byte for zero without changing r3. If nonzero, a second `extsb` into r3
sign-extends it, subtracts1 as a 32-bit integer, and calls `8008b010`. After
normal return, or immediately for a zero request, the consumer reloads the
owner pointer and clears owner+15d4 with a byte store. The clear is not credited
if the setter cannot complete.

`8008b010` loads the owner pointer, compares the signed 32-bit argument against
2, and **stores its low byte to owner+66 before branching on that comparison**.
Arguments>=2 return through `bclr BO4/BI0`. Otherwise the argument is compared
against0; negative values return through `bclr BO12/BI0`. Only arguments0 and1
reload the owner pointer and clear the halfword owner+d6. The setter does not
validate or clamp before writing mode66.

For the consumer's byte input: request1 writes mode0 and clears d6; request2
writes mode1 and clears d6. Request0 skips the setter and leaves mode/d6
unchanged. Other nonzero requests write low8(sign8(request)−1) without clearing
d6. In particular request80 yields argument−129 and mode7f, not a positive
127 argument admitted by an unsigned subtraction shortcut. Requestff yields
argument−2 and modefe. The request clear occurs afterward using a fresh owner
pointer.

## Four-team refresh `80029d48`

At entry, capture the current owner pointer once and set r31=owner+f4. Initialize
r30=0. Four iterations use the captured team bases f4,130,16c,1a8 (stride3c),
calling `80029e98(r31)` before inspecting each record. Re-reading owner pointers
inside that helper does not retarget r31. The loop is not a snapshot of all
records: each helper and all its writes occur before that record's next tests.

After a helper returns:

1. Load record+1, sign-extend with the record bit, and skip the rest of this
   record if signed count<=0. In that case record+0f is left unchanged; even a
   nonzero record+10 does not by itself reach a burst helper.
2. Load record+10 and test signed nonzero. If zero, load **unsigned16** record+32
   before unsigned16 record+30, compare with `cmpl`, and write record+0f=0 when
   32<30, otherwise1. Equality is charged. No floating operation is involved.
3. If record+10 is nonzero, first write record+0f=0 at`80029d8c`, then call
   **unselected `8008b290` at`80029d90`**. A bounded prefix must stop here,
   retaining all preceding writes. It cannot skip this call, refresh later
   records, synthesize its return, or treat the whole refresh as rolled back.
4. On an admitted path that returns normally, increment r30 by1 and r31 by3c,
   compare signed r30<4, and repeat. After all four iterations return, return to
   the outer caller and only then read the current owner mode66.

### Fully decoded, deliberately unimplemented burst suffix

Full-body evidence includes the suffix even though the prefix stops before its
first call. After a normally returning `8008b290`, the code compares its full
r3 word with0. Nonzero skips the remaining record work. Zero reaches unselected
`8008b480`; a zero return admits the decrement, as does a nonzero return whose
bitwise AND with sign-extended record+3 is nonzero. The actual call-result tests
are full-word tests, not implicit byte truncation from C's local declarations.

The decrement is `lha(record18)`, subtract1, `extsh.` of the result, then
`sth` of the low16 result back to18. A resulting signed16 value<=0 produces
`sth 0,record32`, `stb 0,record10`, then **another `sth 0,record32`**, in that
order. This is two halfword stores, not four byte stores as suggested by the C.

A positive result reaches a literal floating sequence that loads constants
from r2−31512 and r2−31520. It prepares signed halfword18 and1a using xoris8000
and the4330 high word, prepares unsigned halfword30 similarly, then uses
**fsubs, fsubs, fdivs, fsubs, fmuls, fctiwz, stfd, lwz, sth** in the represented
order. Those constants were not selected, their values are not authenticated
here, and an idealized division/multiplication substitute is not evidence.
No burst decrement, expiry or floating charge result is part of the authorized
runtime prefix merely because this whole body was statically decoded.

## Team membership refresh `80029e98`

The incoming record pointer stays in r3 throughout this leaf. First clear
bytes1,2,3 in order, then store ff to bytes4,5,6,7,8,9 in order. The code does
not reset byte0, charged0f, burst10 or any timer/charge halfword. Initialize
matched count r7=0, candidate index r6=0 and CTR=3. Each loop has two candidate
halves; r6 advances between them and again before `bdnz`, processing slots0..5.

For each candidate, in exact memory order:

1. Reload owner pointer from r13−31852, then read unsigned owner+15d9 and test
   bit(1<<slot). There are two distinct static loads per CTR iteration, hence
   six actual mask reads when the helper completes. Do not read one mask and
   use it for all candidates. Disabled candidates skip every ID/participant
   read and membership write below.
2. For an enabled candidate, read byte record0 **before** reading owner[cb+slot]
   with `lbzx`. Both are sign-extended before `cmp`. The owner is the r5
   captured for this candidate's mask read, not another owner-pointer reload.
   A mismatched ID skips all following membership writes.
3. Read unsigned record1, add1, and store the low byte back to record1.
4. Only after that count store, load the second pointer from **r13−31856**
   (C name `PTR_DAT_80433930`), read its byte2, sign-extend and test the same bit.
   If set, read record2, increment and store its low byte. There is no null
   check for either global owner pointer.
5. Read record3, form destination index matchedCount+4, increment matchedCount,
   OR the candidate bit into the loaded record3 and store its low byte, then
   use `stbx` to store slot into record[oldMatchedCount+4]. These are ordered
   loads/stores, not an atomic record update or a prefetched roster snapshot.

The first half computes its shift before reading the enable-mask byte; the
second half increments r6, reads the mask, then shifts. The appendix preserves
that instruction order as well as all memory order. Loop control is CTR-based,
not a signed comparison of a generated JavaScript index.

### Alias and memory-admission boundary

These instructions do not establish disjoint allocation of global pointer
slots, owners, participant owners, teams or any of their fields. A faithful
bounded byte-buffer model must retain the loads/stores above when regions
alias: a count store may affect a subsequent participant-pointer read; a prior
candidate store may affect the next owner-pointer or mask read. Capturing every
owner, enable mask, participant mask or team ID at function entry is unsupported.
Likewise, r31 remains the originally captured team base even if a global pointer
slot changes during the helper. No current live object addresses or values were
read from the archive for this work. Host bounds/alignment/refusal checks remain
host admission rules, not proof of original memory-fault behavior.

## Outer source order and current ceiling

After both mandatory prefix calls return, `80029448` reloads owner and reads
mode66. If zero, the next calls are53b30,6ae60,27764, followed by the always-
reached bef4. If nonzero, it branches directly to bef4. Thus the implementable
prefix ends before53b30 for mode0 or beforebef4 otherwise. The next mode check,
scheduler entry, frame counter, action dispatch and final mask copies are all
later source behavior, not completed prefix effects.

For future work, the full authenticated outer body establishes the following
conditional order, with **every continuation conditional on earlier normal
returns**:

- After bef4, reload owner and mode66. If zero: wrapper89a94(40),
  wrapper89a94(32),53a2c,87cf0, wrapper89a94(0), wrapper89a94(16),
  wrapper89a94(8), wrapper89a94(24), then single89898(56).
- Regardless of that mode branch: single89898(58), then single89898(57),
  then89554. Load current owner once, read owner+b0, add1 modulo32 and store
  it to the same owner's+b0. This is after scheduler calls, not an entry tick.
- Reload owner/mode66. If zero:8a28c,89aec,2bb14 (C's
  `battle_frame_target_action_dispatch`). Then36e24,8972c,89658 regardless.
- Reload owner/mode66. If zero:53a94, then single89898(59).
- Reload owner/mode66 and compare to1; if not1 call0bda4. Reload mode again,
  independently, and if not1 call40b94. Theneff30 unconditionally.
- Reload owner, load byte+d1, store it to+d3. **Reload owner again**, load+d2,
  store to+d4. Then restore stack/LR and return.

These are repeated live mode reads, not one immutable frame mode. In particular
bef4 or earlier callbacks could change which later block is taken. The final
mask copies use distinct owner reloads and must not be merged into one captured
owner object when aliases are permitted. The wrapper's previously authenticated
order is six eligibility groups, base, base+7; this outer evidence does not
change that order. It supplies source-level reachability only, not authority
to bypass unimplemented predecessors. It also supplies no stable C-style return
value or preserved incoming floating-argument API.

## Tests, reproducibility and limits

All270 literal semantic fixtures inverse-encode the five exact hashes. Every
one of **8640 instruction-bit mutations** either refuses or decodes to different
operands that inverse-encode to the exact changed word. Every one of **8640
payload-bit mutations** fails its selected hash before decode. All **65 control-
flow rows** and **311 mutations** of their mnemonic/target/BO/BI/BH/AA/LK metadata
are checked. Local-only decoder additions include unsigned halfword loads,
indexed byte stores, shifts, unsigned register comparisons, the selected
conditional LR returns, BO12/BI0 branches and single-precision division.
Every admitted bit is represented or fixed. Shared decoder behavior is unchanged.

Tests also cover fixed widths/typed mappings, duplicate allowlists, arbitrary and
neighboring selections, truncation, reserved instruction fields, all six
supported schemas (version/keytype/types/field names/missing table), whole-file
digest tampering, exact full authentication/selected-read traces, physical spans,
source extents, reused scheduler identities, signed request handling, mandatory
call order, four-record loop, unsigned charge comparison, per-candidate mask
reads, signed IDs, exact store interleaving, and arbitrary-CLI refusal.

Initial discovery exposed a selected conditional LR-return form and additional
already bounded instruction families; these were represented locally without
changing any shared reader. The first test run had one incorrect negative-test
example: it classified the actual admitted `bclr BO12/BI0` form as invalid. That
negative example was replaced with an unselected BO form. No literal operand
fixture, payload hash, archive identity or mapping changed to obtain a pass.

Completed locally, with no install/fetch, runtime/estimator import, original
execution, commit or push:

```
python -m unittest discover -s research/tools/matching-decomp -p test_archived_outer_frame_evidence.py -v
python -m unittest discover -s research/tools/matching-decomp -p 'test_archived_object*evidence.py' -v
python research/tools/matching-decomp/read_archived_outer_frame_evidence.py research/decomp/GotchaForce.rep.before_force_create/idata/00/~00000000.db/db.3.gbf
python research/tools/matching-decomp/read_archived_outer_frame_evidence.py research/decomp/GotchaForce.rep.before_force_create/idata/00/~00000000.db/db.4.gbf
```

The shared authenticator, command mapping reader, normal-actor decoder and
object-scheduler reader have no diff from the investigation base. This document
records focused static-evidence checks, not contributor/docs verification,
runtime integration tests or browser playability acceptance. Derived reports
and discovery notes remain under ignored `.tmp/outer-frame-evidence-20261114/`;
no binary/raw payload output is published.

| Derived report | SHA-256 |
| --- | --- |
| `db3.json` | `e3400f0977640af9bab36da7ebd6a58b5bcdddcb23864104b25d33928f2f8416` |
| `db4.json` | `b317df08ad441c0075d185174bef530f16af9218ca0f37204b15e7fcaf694f1b` |

## Complete decoded instruction operands

Every selected instruction appears below in source order with no gaps.
Addresses/targets are hexadecimal; all other operand numbers are decimal.
`mflr/mtlr` fix SPR8/Rc0; `mtctr` fixes SPR9/Rc0. Compare forms fix reserved
fields, indexed loads/stores fix Rc0, branch-register XO is16 and its reserved
fields/BH/LK are fixed zero. Floating forms fix their unrepresented/reserved
operands and Rc0. All other admitted bits are explicit in the operands.

### `80029434`: 80 instructions /320 bytes

| PC | Complete operands |
| --- | --- |
| `80029434` | `stwu rS=1, rA=1, displacement=-16` |
| `80029438` | `mflr rD=0` |
| `8002943c` | `stw rS=0, rA=1, displacement=20` |
| `80029440` | `bl target=8008b048, AA=0, LK=1` |
| `80029444` | `bl target=80029d48, AA=0, LK=1` |
| `80029448` | `lwz rD=3, rA=13, displacement=-31852` |
| `8002944c` | `lbz rD=0, rA=3, displacement=102` |
| `80029450` | `extsb rS=0, rA=0, Rc=1` |
| `80029454` | `bc BO=4, BI=2, LK=0, target=80029464, AA=0` |
| `80029458` | `bl target=80053b30, AA=0, LK=1` |
| `8002945c` | `bl target=8006ae60, AA=0, LK=1` |
| `80029460` | `bl target=80027764, AA=0, LK=1` |
| `80029464` | `bl target=8000bef4, AA=0, LK=1` |
| `80029468` | `lwz rD=3, rA=13, displacement=-31852` |
| `8002946c` | `lbz rD=0, rA=3, displacement=102` |
| `80029470` | `extsb rS=0, rA=0, Rc=1` |
| `80029474` | `bc BO=4, BI=2, LK=0, target=800294b8, AA=0` |
| `80029478` | `addi rD=3, rA=0, immediate=40` |
| `8002947c` | `bl target=80089a94, AA=0, LK=1` |
| `80029480` | `addi rD=3, rA=0, immediate=32` |
| `80029484` | `bl target=80089a94, AA=0, LK=1` |
| `80029488` | `bl target=80053a2c, AA=0, LK=1` |
| `8002948c` | `bl target=80087cf0, AA=0, LK=1` |
| `80029490` | `addi rD=3, rA=0, immediate=0` |
| `80029494` | `bl target=80089a94, AA=0, LK=1` |
| `80029498` | `addi rD=3, rA=0, immediate=16` |
| `8002949c` | `bl target=80089a94, AA=0, LK=1` |
| `800294a0` | `addi rD=3, rA=0, immediate=8` |
| `800294a4` | `bl target=80089a94, AA=0, LK=1` |
| `800294a8` | `addi rD=3, rA=0, immediate=24` |
| `800294ac` | `bl target=80089a94, AA=0, LK=1` |
| `800294b0` | `addi rD=3, rA=0, immediate=56` |
| `800294b4` | `bl target=80089898, AA=0, LK=1` |
| `800294b8` | `addi rD=3, rA=0, immediate=58` |
| `800294bc` | `bl target=80089898, AA=0, LK=1` |
| `800294c0` | `addi rD=3, rA=0, immediate=57` |
| `800294c4` | `bl target=80089898, AA=0, LK=1` |
| `800294c8` | `bl target=80089554, AA=0, LK=1` |
| `800294cc` | `lwz rD=4, rA=13, displacement=-31852` |
| `800294d0` | `lwz rD=3, rA=4, displacement=176` |
| `800294d4` | `addi rD=0, rA=3, immediate=1` |
| `800294d8` | `stw rS=0, rA=4, displacement=176` |
| `800294dc` | `lwz rD=3, rA=13, displacement=-31852` |
| `800294e0` | `lbz rD=0, rA=3, displacement=102` |
| `800294e4` | `extsb rS=0, rA=0, Rc=1` |
| `800294e8` | `bc BO=4, BI=2, LK=0, target=800294f8, AA=0` |
| `800294ec` | `bl target=8008a28c, AA=0, LK=1` |
| `800294f0` | `bl target=80089aec, AA=0, LK=1` |
| `800294f4` | `bl target=8002bb14, AA=0, LK=1` |
| `800294f8` | `bl target=80036e24, AA=0, LK=1` |
| `800294fc` | `bl target=8008972c, AA=0, LK=1` |
| `80029500` | `bl target=80089658, AA=0, LK=1` |
| `80029504` | `lwz rD=3, rA=13, displacement=-31852` |
| `80029508` | `lbz rD=0, rA=3, displacement=102` |
| `8002950c` | `extsb rS=0, rA=0, Rc=1` |
| `80029510` | `bc BO=4, BI=2, LK=0, target=80029520, AA=0` |
| `80029514` | `bl target=80053a94, AA=0, LK=1` |
| `80029518` | `addi rD=3, rA=0, immediate=59` |
| `8002951c` | `bl target=80089898, AA=0, LK=1` |
| `80029520` | `lwz rD=3, rA=13, displacement=-31852` |
| `80029524` | `lbz rD=0, rA=3, displacement=102` |
| `80029528` | `cmpi BF=0, L=0, rA=0, immediate=1` |
| `8002952c` | `bc BO=12, BI=2, LK=0, target=80029534, AA=0` |
| `80029530` | `bl target=8000bda4, AA=0, LK=1` |
| `80029534` | `lwz rD=3, rA=13, displacement=-31852` |
| `80029538` | `lbz rD=0, rA=3, displacement=102` |
| `8002953c` | `cmpi BF=0, L=0, rA=0, immediate=1` |
| `80029540` | `bc BO=12, BI=2, LK=0, target=80029548, AA=0` |
| `80029544` | `bl target=80040b94, AA=0, LK=1` |
| `80029548` | `bl target=800eff30, AA=0, LK=1` |
| `8002954c` | `lwz rD=3, rA=13, displacement=-31852` |
| `80029550` | `lbz rD=0, rA=3, displacement=209` |
| `80029554` | `stb rS=0, rA=3, displacement=211` |
| `80029558` | `lwz rD=3, rA=13, displacement=-31852` |
| `8002955c` | `lbz rD=0, rA=3, displacement=210` |
| `80029560` | `stb rS=0, rA=3, displacement=212` |
| `80029564` | `lwz rD=0, rA=1, displacement=20` |
| `80029568` | `mtlr rS=0` |
| `8002956c` | `addi rD=1, rA=1, immediate=16` |
| `80029570` | `blr BO=20, BI=0, BH=0, LK=0` |

### `8008b048`: 17 instructions /68 bytes

| PC | Complete operands |
| --- | --- |
| `8008b048` | `stwu rS=1, rA=1, displacement=-16` |
| `8008b04c` | `mflr rD=0` |
| `8008b050` | `stw rS=0, rA=1, displacement=20` |
| `8008b054` | `lwz rD=3, rA=13, displacement=-31852` |
| `8008b058` | `lbz rD=3, rA=3, displacement=5588` |
| `8008b05c` | `extsb rS=3, rA=0, Rc=1` |
| `8008b060` | `bc BO=12, BI=2, LK=0, target=8008b070, AA=0` |
| `8008b064` | `extsb rS=3, rA=3, Rc=0` |
| `8008b068` | `addi rD=3, rA=3, immediate=-1` |
| `8008b06c` | `bl target=8008b010, AA=0, LK=1` |
| `8008b070` | `lwz rD=3, rA=13, displacement=-31852` |
| `8008b074` | `addi rD=0, rA=0, immediate=0` |
| `8008b078` | `stb rS=0, rA=3, displacement=5588` |
| `8008b07c` | `lwz rD=0, rA=1, displacement=20` |
| `8008b080` | `mtlr rS=0` |
| `8008b084` | `addi rD=1, rA=1, immediate=16` |
| `8008b088` | `blr BO=20, BI=0, BH=0, LK=0` |

### `8008b010`: 10 instructions /40 bytes

| PC | Complete operands |
| --- | --- |
| `8008b010` | `lwz rD=4, rA=13, displacement=-31852` |
| `8008b014` | `cmpi BF=0, L=0, rA=3, immediate=2` |
| `8008b018` | `stb rS=3, rA=4, displacement=102` |
| `8008b01c` | `bclr BO=4, BI=0, BH=0, LK=0` |
| `8008b020` | `cmpi BF=0, L=0, rA=3, immediate=0` |
| `8008b024` | `bclr BO=12, BI=0, BH=0, LK=0` |
| `8008b028` | `lwz rD=3, rA=13, displacement=-31852` |
| `8008b02c` | `addi rD=0, rA=0, immediate=0` |
| `8008b030` | `sth rS=0, rA=3, displacement=214` |
| `8008b034` | `blr BO=20, BI=0, BH=0, LK=0` |

### `80029d48`: 84 instructions /336 bytes

| PC | Complete operands |
| --- | --- |
| `80029d48` | `stwu rS=1, rA=1, displacement=-48` |
| `80029d4c` | `mflr rD=0` |
| `80029d50` | `stw rS=0, rA=1, displacement=52` |
| `80029d54` | `stw rS=31, rA=1, displacement=44` |
| `80029d58` | `stw rS=30, rA=1, displacement=40` |
| `80029d5c` | `addi rD=30, rA=0, immediate=0` |
| `80029d60` | `lwz rD=3, rA=13, displacement=-31852` |
| `80029d64` | `addi rD=31, rA=3, immediate=244` |
| `80029d68` | `or rS=31, rA=3, rB=31, Rc=0` |
| `80029d6c` | `bl target=80029e98, AA=0, LK=1` |
| `80029d70` | `lbz rD=0, rA=31, displacement=1` |
| `80029d74` | `extsb rS=0, rA=0, Rc=1` |
| `80029d78` | `bc BO=4, BI=1, LK=0, target=80029e70, AA=0` |
| `80029d7c` | `lbz rD=0, rA=31, displacement=16` |
| `80029d80` | `extsb rS=0, rA=0, Rc=1` |
| `80029d84` | `bc BO=12, BI=2, LK=0, target=80029e4c, AA=0` |
| `80029d88` | `addi rD=0, rA=0, immediate=0` |
| `80029d8c` | `stb rS=0, rA=31, displacement=15` |
| `80029d90` | `bl target=8008b290, AA=0, LK=1` |
| `80029d94` | `cmpi BF=0, L=0, rA=3, immediate=0` |
| `80029d98` | `bc BO=4, BI=2, LK=0, target=80029e70, AA=0` |
| `80029d9c` | `bl target=8008b480, AA=0, LK=1` |
| `80029da0` | `cmpi BF=0, L=0, rA=3, immediate=0` |
| `80029da4` | `bc BO=12, BI=2, LK=0, target=80029db8, AA=0` |
| `80029da8` | `lbz rD=0, rA=31, displacement=3` |
| `80029dac` | `extsb rS=0, rA=0, Rc=0` |
| `80029db0` | `and rS=3, rA=0, rB=0, Rc=1` |
| `80029db4` | `bc BO=12, BI=2, LK=0, target=80029e70, AA=0` |
| `80029db8` | `lha rD=3, rA=31, displacement=24` |
| `80029dbc` | `addi rD=3, rA=3, immediate=-1` |
| `80029dc0` | `extsh rS=3, rA=0, Rc=1` |
| `80029dc4` | `sth rS=3, rA=31, displacement=24` |
| `80029dc8` | `bc BO=12, BI=1, LK=0, target=80029de0, AA=0` |
| `80029dcc` | `addi rD=0, rA=0, immediate=0` |
| `80029dd0` | `sth rS=0, rA=31, displacement=50` |
| `80029dd4` | `stb rS=0, rA=31, displacement=16` |
| `80029dd8` | `sth rS=0, rA=31, displacement=50` |
| `80029ddc` | `b target=80029e70, AA=0, LK=0` |
| `80029de0` | `lha rD=3, rA=31, displacement=24` |
| `80029de4` | `addis rD=4, rA=0, immediate=17200` |
| `80029de8` | `lha rD=0, rA=31, displacement=26` |
| `80029dec` | `xoris rS=3, rA=3, immediate=32768` |
| `80029df0` | `lhz rD=5, rA=31, displacement=48` |
| `80029df4` | `xoris rS=0, rA=0, immediate=32768` |
| `80029df8` | `stw rS=3, rA=1, displacement=20` |
| `80029dfc` | `lfd fD=2, rA=2, displacement=-31512` |
| `80029e00` | `stw rS=4, rA=1, displacement=16` |
| `80029e04` | `lfd fD=3, rA=2, displacement=-31520` |
| `80029e08` | `lfd fD=0, rA=1, displacement=16` |
| `80029e0c` | `stw rS=0, rA=1, displacement=28` |
| `80029e10` | `fsubs fD=1, fA=0, fB=2` |
| `80029e14` | `stw rS=4, rA=1, displacement=24` |
| `80029e18` | `lfd fD=0, rA=1, displacement=24` |
| `80029e1c` | `stw rS=5, rA=1, displacement=12` |
| `80029e20` | `fsubs fD=0, fA=0, fB=2` |
| `80029e24` | `stw rS=4, rA=1, displacement=8` |
| `80029e28` | `fdivs fD=0, fA=1, fB=0` |
| `80029e2c` | `lfd fD=1, rA=1, displacement=8` |
| `80029e30` | `fsubs fD=1, fA=1, fB=3` |
| `80029e34` | `fmuls fD=0, fA=1, fC=0` |
| `80029e38` | `fctiwz fD=0, fB=0` |
| `80029e3c` | `stfd fS=0, rA=1, displacement=32` |
| `80029e40` | `lwz rD=0, rA=1, displacement=36` |
| `80029e44` | `sth rS=0, rA=31, displacement=50` |
| `80029e48` | `b target=80029e70, AA=0, LK=0` |
| `80029e4c` | `lhz rD=3, rA=31, displacement=50` |
| `80029e50` | `lhz rD=0, rA=31, displacement=48` |
| `80029e54` | `cmpl BF=0, L=0, rA=3, rB=0` |
| `80029e58` | `bc BO=12, BI=0, LK=0, target=80029e68, AA=0` |
| `80029e5c` | `addi rD=0, rA=0, immediate=1` |
| `80029e60` | `stb rS=0, rA=31, displacement=15` |
| `80029e64` | `b target=80029e70, AA=0, LK=0` |
| `80029e68` | `addi rD=0, rA=0, immediate=0` |
| `80029e6c` | `stb rS=0, rA=31, displacement=15` |
| `80029e70` | `addi rD=30, rA=30, immediate=1` |
| `80029e74` | `addi rD=31, rA=31, immediate=60` |
| `80029e78` | `cmpi BF=0, L=0, rA=30, immediate=4` |
| `80029e7c` | `bc BO=12, BI=0, LK=0, target=80029d68, AA=0` |
| `80029e80` | `lwz rD=0, rA=1, displacement=52` |
| `80029e84` | `lwz rD=31, rA=1, displacement=44` |
| `80029e88` | `lwz rD=30, rA=1, displacement=40` |
| `80029e8c` | `mtlr rS=0` |
| `80029e90` | `addi rD=1, rA=1, immediate=48` |
| `80029e94` | `blr BO=20, BI=0, BH=0, LK=0` |

### `80029e98`: 79 instructions /316 bytes

| PC | Complete operands |
| --- | --- |
| `80029e98` | `addi rD=5, rA=0, immediate=0` |
| `80029e9c` | `addi rD=4, rA=0, immediate=-1` |
| `80029ea0` | `stb rS=5, rA=3, displacement=1` |
| `80029ea4` | `addi rD=0, rA=0, immediate=3` |
| `80029ea8` | `addi rD=7, rA=0, immediate=0` |
| `80029eac` | `addi rD=6, rA=0, immediate=0` |
| `80029eb0` | `stb rS=5, rA=3, displacement=2` |
| `80029eb4` | `stb rS=5, rA=3, displacement=3` |
| `80029eb8` | `stb rS=4, rA=3, displacement=4` |
| `80029ebc` | `stb rS=4, rA=3, displacement=5` |
| `80029ec0` | `stb rS=4, rA=3, displacement=6` |
| `80029ec4` | `stb rS=4, rA=3, displacement=7` |
| `80029ec8` | `stb rS=4, rA=3, displacement=8` |
| `80029ecc` | `stb rS=4, rA=3, displacement=9` |
| `80029ed0` | `mtctr rS=0` |
| `80029ed4` | `lwz rD=5, rA=13, displacement=-31852` |
| `80029ed8` | `addi rD=4, rA=0, immediate=1` |
| `80029edc` | `slw rS=4, rA=8, rB=6, Rc=0` |
| `80029ee0` | `lbz rD=0, rA=5, displacement=5593` |
| `80029ee4` | `and rS=0, rA=0, rB=8, Rc=1` |
| `80029ee8` | `bc BO=12, BI=2, LK=0, target=80029f4c, AA=0` |
| `80029eec` | `addi rD=4, rA=6, immediate=203` |
| `80029ef0` | `lbz rD=0, rA=3, displacement=0` |
| `80029ef4` | `lbzx rD=4, rA=5, rB=4` |
| `80029ef8` | `extsb rS=0, rA=0, Rc=0` |
| `80029efc` | `extsb rS=4, rA=4, Rc=0` |
| `80029f00` | `cmp BF=0, L=0, rA=4, rB=0` |
| `80029f04` | `bc BO=4, BI=2, LK=0, target=80029f4c, AA=0` |
| `80029f08` | `lbz rD=4, rA=3, displacement=1` |
| `80029f0c` | `addi rD=0, rA=4, immediate=1` |
| `80029f10` | `stb rS=0, rA=3, displacement=1` |
| `80029f14` | `lwz rD=4, rA=13, displacement=-31856` |
| `80029f18` | `lbz rD=0, rA=4, displacement=2` |
| `80029f1c` | `extsb rS=0, rA=0, Rc=0` |
| `80029f20` | `and rS=0, rA=0, rB=8, Rc=1` |
| `80029f24` | `bc BO=12, BI=2, LK=0, target=80029f34, AA=0` |
| `80029f28` | `lbz rD=4, rA=3, displacement=2` |
| `80029f2c` | `addi rD=0, rA=4, immediate=1` |
| `80029f30` | `stb rS=0, rA=3, displacement=2` |
| `80029f34` | `lbz rD=4, rA=3, displacement=3` |
| `80029f38` | `addi rD=0, rA=7, immediate=4` |
| `80029f3c` | `addi rD=7, rA=7, immediate=1` |
| `80029f40` | `or rS=4, rA=4, rB=8, Rc=0` |
| `80029f44` | `stb rS=4, rA=3, displacement=3` |
| `80029f48` | `stbx rS=6, rA=3, rB=0` |
| `80029f4c` | `lwz rD=5, rA=13, displacement=-31852` |
| `80029f50` | `addi rD=4, rA=0, immediate=1` |
| `80029f54` | `addi rD=6, rA=6, immediate=1` |
| `80029f58` | `lbz rD=0, rA=5, displacement=5593` |
| `80029f5c` | `slw rS=4, rA=8, rB=6, Rc=0` |
| `80029f60` | `and rS=0, rA=0, rB=8, Rc=1` |
| `80029f64` | `bc BO=12, BI=2, LK=0, target=80029fc8, AA=0` |
| `80029f68` | `addi rD=4, rA=6, immediate=203` |
| `80029f6c` | `lbz rD=0, rA=3, displacement=0` |
| `80029f70` | `lbzx rD=4, rA=5, rB=4` |
| `80029f74` | `extsb rS=0, rA=0, Rc=0` |
| `80029f78` | `extsb rS=4, rA=4, Rc=0` |
| `80029f7c` | `cmp BF=0, L=0, rA=4, rB=0` |
| `80029f80` | `bc BO=4, BI=2, LK=0, target=80029fc8, AA=0` |
| `80029f84` | `lbz rD=4, rA=3, displacement=1` |
| `80029f88` | `addi rD=0, rA=4, immediate=1` |
| `80029f8c` | `stb rS=0, rA=3, displacement=1` |
| `80029f90` | `lwz rD=4, rA=13, displacement=-31856` |
| `80029f94` | `lbz rD=0, rA=4, displacement=2` |
| `80029f98` | `extsb rS=0, rA=0, Rc=0` |
| `80029f9c` | `and rS=0, rA=0, rB=8, Rc=1` |
| `80029fa0` | `bc BO=12, BI=2, LK=0, target=80029fb0, AA=0` |
| `80029fa4` | `lbz rD=4, rA=3, displacement=2` |
| `80029fa8` | `addi rD=0, rA=4, immediate=1` |
| `80029fac` | `stb rS=0, rA=3, displacement=2` |
| `80029fb0` | `lbz rD=4, rA=3, displacement=3` |
| `80029fb4` | `addi rD=0, rA=7, immediate=4` |
| `80029fb8` | `addi rD=7, rA=7, immediate=1` |
| `80029fbc` | `or rS=4, rA=4, rB=8, Rc=0` |
| `80029fc0` | `stb rS=4, rA=3, displacement=3` |
| `80029fc4` | `stbx rS=6, rA=3, rB=0` |
| `80029fc8` | `addi rD=6, rA=6, immediate=1` |
| `80029fcc` | `bc BO=16, BI=0, LK=0, target=80029ed4, AA=0` |
| `80029fd0` | `blr BO=20, BI=0, BH=0, LK=0` |
