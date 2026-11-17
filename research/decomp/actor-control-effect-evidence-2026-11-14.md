# Actor control and bounded charge effects: archived evidence

## Result and limits

The dedicated fixed reader authenticates **175 instructions in six complete
functions**, one +0f constant, two color-script pointer cells, the cue1 pointer
cell and only that cue record's first signed16. Both existing local ProgramDB
snapshots agree on every decoded operand, fixed value, digest and physical
trace. Every selected instruction is represented, including all stack operations
and the sound helper's C-unreachable branch at `800f01c8`.

This is archived source evidence, not original-DOL identity, live-state capture,
retail actor ownership, audio closure, gameplay parity or production integration.
The actor-control callees `8006aab0`, `80176ec0` and `8006a980` are not implemented
or authenticated by this reader. Color script contents are not read. Sound
replacement, timestamp and audio callees remain boundaries. A same-head sound
path is **not** a no-op: it still writes the actor owner and countdown.

The artifacts are
[`read_archived_control_effect_evidence.py`](../tools/matching-decomp/read_archived_control_effect_evidence.py)
and
[`test_archived_control_effect_evidence.py`](../tools/matching-decomp/test_archived_control_effect_evidence.py).
The CLI takes one existing snapshot path. It has no address, width, index,
raw-output, instruction-execution or pointer-following options. The only new
reads are the fixed spans below. No original or archived instructions are
executed; shared readers and shared allowlists are unchanged. The full operand
list is in the reader output and independent explicit expectations in the test.
The appendix below also records all 175 instruction operands in source order.

## Extents and source cross-references

| Entry | End exclusive | Size | Instructions | Extent evidence |
| --- | --- | --- | --- | --- |
| `8005a190` | `8005a298` | `0x108` | 66 | C `chunk_0007.c:2730-2772`; archived final `blr` at `8005a294`; neither start nor next entry is in the symbol map |
| `8006ab9c` | `8006abb8` | `0x1c` | 7 | symbol map line 831 gives size `0x1c`; C `chunk_0009.c:1089-1102`; final `blr` at `8006abb4` |
| `8006abb8` | `8006abd4` | `0x1c` | 7 | absent from symbol map; C `chunk_0009.c:1102-1115`; final `blr` at `8006abd0`; next entry `8006abd4` is map line 832 |
| `800061cc` | `800061f0` | `0x24` | 9 | symbol map lines 28-29; C `chunk_0000.c:871-882`; final `blr` at `800061ec` |
| `800061f0` | `80006238` | `0x48` | 18 | symbol map lines 29-30; C `chunk_0000.c:882-904`; final `blr` at `80006234` |
| `800f0104` | `800f0214` | `0x110` | 68 | symbol map lines 1679-1680; C `chunk_0026.c:685-726`; final `blr` at `800f0210` |

The map is `research/symbols/GG4E-CSM-20220412.map`. The C files are under
`research/decomp/ghidra-export/`. C and map entries guide extent selection;
whole-snapshot authentication and exact per-span digests authenticate the
selected archived instruction evidence. The misleading C/map name
`glxCopyMatrix(float` at `800061cc` does not establish matrix behavior: the
instructions show a wrapper setting argument 3 to zero and calling `800061f0`.

The full actor tick `80059068..80059138` is already authenticated by the
unchanged [tick reader](../tools/matching-decomp/read_archived_tick_prefix_evidence.py).
It is referenced, not duplicated or widened here.

## Authentication and fixed spans

Existing snapshot directory:
`GotchaForce.rep.before_force_create/idata/00/~00000000.db/`.

- `db.3.gbf`: SHA-256
  `7b50dd2d2e17b4bfcc89a64cde27010247d0cbf0f48bd5c059f50275f40458d0`.
- `db.4.gbf`: SHA-256
  `1f86813d91ea8e2c4564f96622ec42555e1dba2c78aa81ad654e892140d019f8`.

Unchanged `read_archived_constants.inspect` first verifies the entire snapshot,
exact schema, executable metadata, big-endian Gekko/Broadway language, address
maps, empty File Bytes table, full data5 digest and existing controls. Unchanged
`read_archived_command_evidence.mappings` verifies text1/data3/data5 block and
subblock identities and all-block overlap. New reads require exact integer
fields, exact mapping/root, exact selected address/width, byte width and SHA-256
before decoding or interpreting values. Fixed values receive an additional
independent value check, including positive-zero bits rather than numeric zero.

- Import-metadata executable SHA-256:
  `21454a8880c6254616662710d6ec626e43d853999da2cdfad700030960a94836`.
  This is metadata, not independent proof of unchanged original executable bytes.
- File Bytes: version 0, root -1, count 0.
- Block size 16384; master root 1; image offset `80000000`.
- Text1: start `800055e0`, length 2796416, block/subblock 1, chain root 21.
- Data3: `802bae60..803af120`, length `0xf42c0`, block/subblock 5, root 199.
- Data5: `80436a20..8043d500`, length 27360, block/subblock 7, root 263.
  Full data5 SHA-256:
  `989c794b17fc95de6e57810f5c89db23d585c85a15faafc994d9a5bd9a0e61b4`.
- All selected mappings require subblock type 2, starting offset 0 and source
  offset 0.

| Fixed span | Width | SHA-256 |
| --- | --- | --- |
| `8005a190..8005a298` | 264 | `38c79e7746c5dd77629b3c47c8548fb6f8e9cdb6bd1a071374eeed808095ca66` |
| `8006ab9c..8006abb8` | 28 | `84dc19c6d1c42e0aebd50aefb26c7094fdf09c8ee54db60004bf6d9ec4a79e35` |
| `8006abb8..8006abd4` | 28 | `1fcb5229a65674e661e975d13a6c7de2dfcd6272455f5cd12e7a1aef7d1c5583` |
| `800061cc..800061f0` | 36 | `89494a4a32bc20ce7acf322deb4d5857318ab1708d18d530c8982d920dedc74b` |
| `800061f0..80006238` | 72 | `8abedf63ca8b25b1c456bb4ecffa2f79e8ddd0fe0cfbaf81be0f464f80f63b6d` |
| `800f0104..800f0214` | 272 | `5d114b7dd7dc8252d474b0681d7b6fa1db756427eb0d67c68db3e00a318ec5b4` |
| `80436a20..80436a24` | 4 | `df3f619804a92fdb4057192dc43dd748ea778adc52bc498ce80524c014b81119` |
| `802c37bc..802c37c4` | 8 | `fade6764faf5058f95209d0725c28d0899d47529cb5881eadefa4cb828a8dcb6` |
| `8031b698..8031b69c` | 4 | `283ff16b0fc15610bcb5c698fd5235ab535c956de7a340c946de14e6840be646` |
| `8031b454..8031b456` | 2 | `0d1abbe3b9da7a48d463edb0a844f3a102dcf7fdea35f9c771d885027b31b322` |

Physical spans are identical between snapshots. All are obfuscated storage;
all numeric offsets below are decimal.

| Address | Root / data buffer | Chain offset | Data offset | Physical offset | Length |
| --- | --- | --- | --- | --- | --- |
| `8005a190` | 21 / 43 | 347056 | 3118 | 724020 | 264 |
| `8006ab9c` | 21 / 47 | 415164 | 5714 | 792152 | 28 |
| `8006abb8` | 21 / 47 | 415192 | 5742 | 792180 | 28 |
| `800061cc` | 21 / 22 | 3052 | 3052 | 379890 | 36 |
| `800061f0` | 21 / 22 | 3088 | 3088 | 379926 | 72 |
| `800f0104` | 21 / 80 | 961316 | 11392 | 1338502 | 272 |
| `80436a20` | 263 / 264 | 0 | 0 | 4341766 | 4 |
| `802c37bc` | 199 / 202 | 35164 | 2408 | 3328366 | 8 |
| `8031b698` | 199 / 224 | 395320 | 2248 | 3688654 | 4 |
| `8031b454` | 199 / 224 | 394740 | 1668 | 3688074 | 2 |

## Actor control: exact order and lazy fields

`8005a190` retains the actor in r31. The first three gates are separate lazy
loads, not one eager actor validation:

1. `8005a1a4` reads byte `4a1`, `8005a1a8` sign-extends with record bit, and
   `8005a1ac` exits if nonzero.
2. Only then `8005a1b0` reads byte `4a0`, sign-extended at `8005a1b4`, with its
   own nonzero exit at `8005a1b8`.
3. Only then `8005a1bc` reads byte `6fc`, sign-extended at `8005a1c0`.
   `8005a1c4` continues only if zero.

The shared gate exit sets r3=0 at `8005a1c8`, branches to epilogue `8005a284`,
and returns at `8005a294`. Later flags, timers and helpers are not touched.

If all gates are zero, `8005a1d0` loads **unsigned byte** `48a` and compares it
with 2. Although C describes `char`, this equality is encoded as `lbz` without
`extsb`; for value 2 the distinction does not change the branch.

### Branch `48a == 2`

- `8005a1dc` reads **signed16** `49c` once into r4. If positive, `8005a1e8`
  subtracts one and `8005a1ec` stores the low16. It then returns zero. It does
  not call readiness or inspect the alternate `490` / `49a` fields.
- For a nonpositive `49c`, `8005a1f4` calls `8006ab9c(actor)`. That function's
  only actor read is u32 `5e0` at `8006aba0`. A zero return exits with zero.
- A true predicate reaches `8005a204 -> 8006aab0(actor)`. This callee's body is
  outside this evidence. No downstream read/store may be credited before it
  returns.
- Only after it returns, `8005a208` reads actor byte `88`, `8005a214`
  sign-extends it, and `8005a218` calls `80176ec0(actor, s8[88], 0)`.
- Only after both callees return does `8005a21c` set return value 1.

### Branch `48a != 2`

- `8005a224` reads unsigned byte `490`. If it is not 2, return zero without
  reading `49a` or `5e0`.
- `8005a230` reads signed16 `49a` into r4. Nonpositive values return zero
  unchanged and without readiness.
- Positive values decrement at `8005a23c`. `8005a240` sign-extends the low16
  into r0 **and updates CR0 before** `8005a244` stores r4's low16 into `49a`.
  The branch at `8005a248` uses that retained CR0. A still-positive result
  returns zero without readiness.
- A result at or below zero reaches `8005a24c -> 8006abb8(actor)`, reading
  u32 `5e0` at `8006abbc` after the timer store.
- A false predicate sets `49a=1` at `8005a27c`, then returns zero.
- A true predicate reaches `8005a25c -> 8006a980(actor)` before the status
  stores. Only after return, `8005a268` writes byte `489=4`, then `8005a270`
  writes byte `19=3`, and the function returns 1. These stores must not appear
  on a refusal at the callee boundary.

### Readiness predicates

Both are complete seven-instruction leaf functions. They construct the mask
in registers, read actor `5e0`, AND it, execute `cntlzw`, and rotate/mask right
by five (`rlwinm r3,r0,27,5,31`). They return exactly 1 iff the masked u32 is
zero, otherwise 0:

- `8006ab9c`: mask `0x91001003` from `lis r4,0x9100` plus `addi 0x1003`.
- `8006abb8`: mask `0x91001000` from the same `lis` plus `addi 0x1000`.

The masks are instruction immediates, not unverified table values. Treating a
missing `5e0` as zero would invent a successful predicate; requiring it before
its actual call site would invent an earlier failure.

## Conditional outer-tick continuation

The unchanged tick reader covers every instruction in `80059068..80059138`.
It shows `800590bc -> 8005a190`, then compare r3 to zero at `800590c0`:

- A nonzero return branches at `800590c4` to `8005910c`. It skips both indirect
  calls and the two following direct helpers, then reaches
  `80059110 -> 8005a298`.
- A zero return reads byte `5e4` at `800590c8`, sign-extends it at `800590d8`,
  forms `s8(5e4)*4` modulo 32 bits at `800590dc`, and loads a target from
  table base `802d3300` at `800590e0`. `800590e4` sets CTR and `800590e8`
  executes `bctrl(actor)`.
- After that returns, actor's function pointer `4c8` is loaded at `800590ec`
  for the second `bctrl` at `800590f8`; then calls `80059f5c` at `80059100`
  and `8005a144` at `80059108` precede the common continuation.

This new reader does not read the `802d3300` dispatch table or resolve its
entries. The next unsupported zero-return boundary is a **conditional**
`800590e8` indirect call, not an unconditional call after actor control.

## Color-script wrapper and bounded writes

`800061cc` sets r5=0 at `800061d4`, then calls `800061f0` at `800061dc`,
preserving its actor r3 and color index r4. The actual routine can select other
channels through r5, but the authenticated charge-call wrapper selects channel0.
Only indices `0x13` and `0x14` have fixed data evidence here:

| Cell calculation | Cell | Fixed pointer |
| --- | --- | --- |
| `802c3770 + 4*0x13` | `802c37bc` | `802c36b0` |
| `802c3770 + 4*0x14` | `802c37c0` | `802c36e0` |

No bytes at either script destination are read. Pointer identity is established;
script execution, length, visual meaning and completion are not.

The exact source order for channel0 is:

1. `800061fc`: byte actor+`7df` = 0, before any constant or table load.
2. `8000620c`: load f32 +0 from `r2-32768`. The separately recorded SDA2
   basis `8043ea20` gives fixed `80436a20`; this is not a live r2 capture.
3. `80006210`: load the selected script pointer from the table.
4. `8000621c`: store that pointer at actor+`7ec`.
5. `80006220`: store retained f0 +0 at actor+`7e4`.
6. `80006224`: byte actor+`7f7` = `0xff`.
7. `80006228`, `8000622c`, `80006230`: bytes actor+`7f4`, `7f5`, `7f6` = 0
   in precisely that order.

Consequently a missing selected table owner/entry must not erase the earlier
`7df` store. A missing write destination later in the sequence must preserve
all earlier writes. These functions contain no color-playback body or host
callback that could substitute for one.

## Sound keepalive: first-head match, writes and boundaries

The charge helper calls `800f0104(actor,1,4)` at `80068838`, as authenticated by
the separate [charge helper reader](../tools/matching-decomp/read_archived_charge_helper_evidence.py).
The selected sound function computes its record base using:

- byte actor+`96` at `800f0134`, sign-extended at `800f0138`;
- signed slot contribution multiplied by `0x80` at `800f013c`;
- unsigned low8 of argument3 multiplied by `0x10` at `800f011c`;
- global base `803d3ae8` constructed at `800f010c` / `800f0118`.

Let B be that base plus the two contributions, modulo 32 bits. r29 becomes
B+`50` at `800f014c`; it is retained through calls. For the charge caller,
argument3 is4, so the second contribution is `0x40`. This evidence does not
establish a live scheduler array, allowable actor slot values, identity ownership
or pointer validity. It does establish the signed slot arithmetic; replacing
it with unsigned indexing or a per-actor private record changes semantics.

The fields are B+`50` timestamp, B+`54` countdown, B+`58` script pointer,
and B+`5c` owner actor pointer. The first instruction that reads record state is
`800f0148`, loading B+`58`. Timestamp and countdown are not read.

### Existing non-null pointer

The source requires these reads in this order:

1. `800f016c`: signed16 head through the **existing record pointer**.
2. `800f0170`: cue table pointer, indexed by argument2's unsigned low8.
3. `800f0174`: signed16 head through that selected pointer.
4. `800f0178`: signed comparison of the two loaded heads.

Only cue1 is authenticated here: `8031b694+4 = 8031b698` contains `8031b454`,
and only signed16 at `8031b454` is selected, with value **126**. The head is
read only after separately verifying that exact pointer cell and value. Its
address is hard-coded, never computed by following arbitrary data; its two-byte
span cannot be expanded to mode/adjacent fields. Different pointer values can
have matching first signed16 values. Therefore pointer identity alone is not
the source comparison, and a first-head match is not whole-record equality.
The archived head does not prove that live memory is immutable or authorize
an arbitrary live overlay.

On matching heads, `800f017c` branches to `800f0188` while r8 remains zero.
`800f018c` then branches to the common stores at `800f01ec`. It does not load
mode, read timestamp, call an audio function or overwrite the script pointer.
It **does** write actor pointer to B+`5c` at `800f01ec`, then writes countdown2
to B+`54` at `800f01f4`. Owner precedes countdown. Timestamp and existing
script pointer remain untouched. Any model must retain shared-record ownership
and sequential writes, including when different actors select the same record.

If the heads differ, `800f0180` calls `800f02d0(actor,arg2,arg3)` before the
activation block. That callee is not authenticated here. Stop at that call
rather than guessing its replacement/stop behavior or advancing to later stores.

### Null pointer and activation

A null existing pointer sets the activation flag at `800f0158` and skips all
existing-head and selected-head reads. The activation block then:

1. Loads the cue table pointer at `800f019c`.
2. Stores that pointer to B+`58` at `800f01a0`.
3. Calls timestamp helper `80207058` at `800f01a4`.
4. Only after return stores the timestamp result to B+`50` at `800f01a8`.
5. Reloads script pointer at `800f01ac`, then reads **unsigned16** record+4
   via `lhz` at `800f01b0`. This differs from the C export's signed-short
   description. The reader authenticates the instruction but does not read that
   mode field from the archive.
6. Mode1 reaches `800f01dc`, loading signed16 cue ID, then loading f32 at
   r2-22992 (`80439050` under the recorded basis) and calling `800f061c` at
   `800f01e8`. The constant and callee are outside this fixed evidence.
7. Mode0 reaches `800f01cc`, loading signed16 cue ID and calling `800f036c`
   at `800f01d4`. Other unsigned16 modes skip the audio calls.

All paths that return from the activation work eventually write owner and
countdown. A bounded implementation reaching the unimplemented timestamp call
must retain the earlier script-pointer store, but must not invent a clock
value or perform timestamp, mode/audio, owner or countdown writes afterward.
A replacement-path refusal occurs earlier, at `800f0180`.

The C warning removes `800f01c8`; its archived instruction is a branch to
`800f01ec`. It follows a signed comparison of zero-extended u16 mode against0,
so that negative-mode branch cannot be reached under the shown instruction
semantics. It is nevertheless included in the full 68-instruction evidence,
not silently omitted. All scalar stack saves/restores are included too.

## Validation

Executed against both local snapshots, without installation or network:

- `python -m unittest discover -s research/tools/matching-decomp -p 'test_archived_control_effect_evidence.py' -v`: **20 tests passed**, no skips.
- The unchanged charge-helper regression module: **16 tests passed**.
- The unchanged tick-prefix regression module: **16 tests passed**.
- Both CLI reads passed and agree on all 175 instructions and all four fixed
  data spans, including digests and physical provenance.
- `git diff --check`: passed at this evidence freeze.

Tests compare every operand of every selected instruction against explicit
expectations; verify every terminal return, fixed value and physical trace;
mutate every instruction and every selected data byte in both authenticated
archives; reject digest/width/type/root/mapping/schema changes, duplicate ranges,
reserved encodings, unsupported forms, adjacent data, arbitrary CLI options and
arbitrary pointer targets; and verify authentication and cue-pointer anchoring
precede the new reads. They also recheck the existing tick's conditional next
call and verify shared allowlists still refuse the new spans. No tests run or
emulate archived code. Focused reader tests do not establish whole-product
parity or replace contributor/browser acceptance checks.

## Complete derived instruction operands

The following are decoded fields, not executable words. Registers use the
reader's explicit operand names; displacements and immediates are decimal,
branch targets are hexadecimal addresses. `AA=0`, `LK=0`, `Rc=0` remain explicit
where applicable. This preserves source/destination direction, CR conditions,
record bits and all stack instructions.

### 8005a190..8005a298

```text
8005a190 stwu rA=1 displacement=-16 rS=1
8005a194 mflr rD=0
8005a198 stw rA=1 displacement=20 rS=0
8005a19c stw rA=1 displacement=12 rS=31
8005a1a0 or rS=3 rA=31 rB=3 Rc=0
8005a1a4 lbz rD=0 rA=3 displacement=1185
8005a1a8 extsb rS=0 rA=0 Rc=1
8005a1ac bc BO=4 BI=2 LK=0 target=8005a1c8 AA=0
8005a1b0 lbz rD=0 rA=31 displacement=1184
8005a1b4 extsb rS=0 rA=0 Rc=1
8005a1b8 bc BO=4 BI=2 LK=0 target=8005a1c8 AA=0
8005a1bc lbz rD=0 rA=31 displacement=1788
8005a1c0 extsb rS=0 rA=0 Rc=1
8005a1c4 bc BO=12 BI=2 LK=0 target=8005a1d0 AA=0
8005a1c8 addi rD=3 rA=0 immediate=0
8005a1cc b target=8005a284 AA=0
8005a1d0 lbz rD=0 rA=31 displacement=1162
8005a1d4 cmpi BF=0 L=0 rA=0 immediate=2
8005a1d8 bc BO=4 BI=2 LK=0 target=8005a224 AA=0
8005a1dc lha rD=4 rA=31 displacement=1180
8005a1e0 cmpi BF=0 L=0 rA=4 immediate=0
8005a1e4 bc BO=4 BI=1 LK=0 target=8005a1f4 AA=0
8005a1e8 addi rD=0 rA=4 immediate=-1
8005a1ec sth rA=31 displacement=1180 rS=0
8005a1f0 b target=8005a280 AA=0
8005a1f4 bl target=8006ab9c AA=0
8005a1f8 cmpi BF=0 L=0 rA=3 immediate=0
8005a1fc bc BO=12 BI=2 LK=0 target=8005a280 AA=0
8005a200 or rS=31 rA=3 rB=31 Rc=0
8005a204 bl target=8006aab0 AA=0
8005a208 lbz rD=4 rA=31 displacement=136
8005a20c or rS=31 rA=3 rB=31 Rc=0
8005a210 addi rD=5 rA=0 immediate=0
8005a214 extsb rS=4 rA=4 Rc=0
8005a218 bl target=80176ec0 AA=0
8005a21c addi rD=3 rA=0 immediate=1
8005a220 b target=8005a284 AA=0
8005a224 lbz rD=0 rA=31 displacement=1168
8005a228 cmpi BF=0 L=0 rA=0 immediate=2
8005a22c bc BO=4 BI=2 LK=0 target=8005a280 AA=0
8005a230 lha rD=4 rA=31 displacement=1178
8005a234 cmpi BF=0 L=0 rA=4 immediate=0
8005a238 bc BO=4 BI=1 LK=0 target=8005a280 AA=0
8005a23c addi rD=4 rA=4 immediate=-1
8005a240 extsh rS=4 rA=0 Rc=1
8005a244 sth rA=31 displacement=1178 rS=4
8005a248 bc BO=12 BI=1 LK=0 target=8005a280 AA=0
8005a24c bl target=8006abb8 AA=0
8005a250 cmpi BF=0 L=0 rA=3 immediate=0
8005a254 bc BO=12 BI=2 LK=0 target=8005a278 AA=0
8005a258 or rS=31 rA=3 rB=31 Rc=0
8005a25c bl target=8006a980 AA=0
8005a260 addi rD=3 rA=0 immediate=4
8005a264 addi rD=0 rA=0 immediate=3
8005a268 stb rS=3 rA=31 displacement=1161
8005a26c addi rD=3 rA=0 immediate=1
8005a270 stb rS=0 rA=31 displacement=25
8005a274 b target=8005a284 AA=0
8005a278 addi rD=0 rA=0 immediate=1
8005a27c sth rA=31 displacement=1178 rS=0
8005a280 addi rD=3 rA=0 immediate=0
8005a284 lwz rD=0 rA=1 displacement=20
8005a288 lwz rD=31 rA=1 displacement=12
8005a28c mtlr rS=0
8005a290 addi rD=1 rA=1 immediate=16
8005a294 blr
```

### 8006ab9c..8006abb8

```text
8006ab9c addis rD=4 rA=0 immediate=-28416
8006aba0 lwz rD=3 rA=3 displacement=1504
8006aba4 addi rD=0 rA=4 immediate=4099
8006aba8 and rS=3 rA=0 rB=0 Rc=0
8006abac cntlzw rS=0 rA=0 Rc=0
8006abb0 rlwinm rS=0 rA=3 SH=27 MB=5 ME=31 Rc=0
8006abb4 blr
```

### 8006abb8..8006abd4

```text
8006abb8 addis rD=4 rA=0 immediate=-28416
8006abbc lwz rD=3 rA=3 displacement=1504
8006abc0 addi rD=0 rA=4 immediate=4096
8006abc4 and rS=3 rA=0 rB=0 Rc=0
8006abc8 cntlzw rS=0 rA=0 Rc=0
8006abcc rlwinm rS=0 rA=3 SH=27 MB=5 ME=31 Rc=0
8006abd0 blr
```

### 800061cc..800061f0

```text
800061cc stwu rA=1 displacement=-16 rS=1
800061d0 mflr rD=0
800061d4 addi rD=5 rA=0 immediate=0
800061d8 stw rA=1 displacement=20 rS=0
800061dc bl target=800061f0 AA=0
800061e0 lwz rD=0 rA=1 displacement=20
800061e4 mtlr rS=0
800061e8 addi rD=1 rA=1 immediate=16
800061ec blr
```

### 800061f0..80006238

```text
800061f0 add rD=7 rA=3 rB=5 Rc=0
800061f4 addi rD=8 rA=0 immediate=0
800061f8 addis rD=6 rA=0 immediate=-32724
800061fc stb rS=8 rA=7 displacement=2015
80006200 rlwinm rS=4 rA=0 SH=2 MB=0 ME=29 Rc=0
80006204 rlwinm rS=5 rA=5 SH=2 MB=0 ME=29 Rc=0
80006208 addi rD=4 rA=6 immediate=14192
8000620c lfs fD=0 rA=2 displacement=-32768
80006210 lwzx rD=4 rA=4 rB=0
80006214 add rD=3 rA=3 rB=5 Rc=0
80006218 addi rD=0 rA=0 immediate=255
8000621c stw rA=3 displacement=2028 rS=4
80006220 stfs rA=3 displacement=2020 fS=0
80006224 stb rS=0 rA=3 displacement=2039
80006228 stb rS=8 rA=3 displacement=2036
8000622c stb rS=8 rA=3 displacement=2037
80006230 stb rS=8 rA=3 displacement=2038
80006234 blr
```

### 800f0104..800f0214

```text
800f0104 stwu rA=1 displacement=-32 rS=1
800f0108 mflr rD=0
800f010c addis rD=6 rA=0 immediate=-32707
800f0110 addi rD=8 rA=0 immediate=0
800f0114 stw rA=1 displacement=36 rS=0
800f0118 addi rD=6 rA=6 immediate=15080
800f011c rlwinm rS=5 rA=0 SH=4 MB=20 ME=27 Rc=0
800f0120 stw rA=1 displacement=28 rS=31
800f0124 or rS=4 rA=31 rB=4 Rc=0
800f0128 stw rA=1 displacement=24 rS=30
800f012c or rS=3 rA=30 rB=3 Rc=0
800f0130 stw rA=1 displacement=20 rS=29
800f0134 lbz rD=7 rA=3 displacement=150
800f0138 extsb rS=7 rA=7 Rc=0
800f013c rlwinm rS=7 rA=7 SH=7 MB=0 ME=24 Rc=0
800f0140 add rD=6 rA=6 rB=7 Rc=0
800f0144 add rD=6 rA=6 rB=0 Rc=0
800f0148 lwz rD=7 rA=6 displacement=88
800f014c addi rD=29 rA=6 immediate=80
800f0150 cmpli BF=0 L=0 rA=7 immediate=0
800f0154 bc BO=4 BI=2 LK=0 target=800f0160 AA=0
800f0158 addi rD=8 rA=0 immediate=1
800f015c b target=800f0188 AA=0
800f0160 addis rD=6 rA=0 immediate=-32718
800f0164 rlwinm rS=31 rA=0 SH=2 MB=22 ME=29 Rc=0
800f0168 addi rD=6 rA=6 immediate=-18796
800f016c lha rD=7 rA=7 displacement=0
800f0170 lwzx rD=6 rA=6 rB=0
800f0174 lha rD=0 rA=6 displacement=0
800f0178 cmp BF=0 L=0 rA=7 rB=0
800f017c bc BO=12 BI=2 LK=0 target=800f0188 AA=0
800f0180 bl target=800f02d0 AA=0
800f0184 addi rD=8 rA=0 immediate=1
800f0188 cmpi BF=0 L=0 rA=8 immediate=1
800f018c bc BO=4 BI=2 LK=0 target=800f01ec AA=0
800f0190 addis rD=3 rA=0 immediate=-32718
800f0194 rlwinm rS=31 rA=0 SH=2 MB=22 ME=29 Rc=0
800f0198 addi rD=3 rA=3 immediate=-18796
800f019c lwzx rD=0 rA=3 rB=0
800f01a0 stw rA=29 displacement=8 rS=0
800f01a4 bl target=80207058 AA=0
800f01a8 stw rA=29 displacement=0 rS=3
800f01ac lwz rD=3 rA=29 displacement=8
800f01b0 lhz rD=0 rA=3 displacement=4
800f01b4 cmpi BF=0 L=0 rA=0 immediate=1
800f01b8 bc BO=12 BI=2 LK=0 target=800f01dc AA=0
800f01bc bc BO=4 BI=0 LK=0 target=800f01ec AA=0
800f01c0 cmpi BF=0 L=0 rA=0 immediate=0
800f01c4 bc BO=4 BI=0 LK=0 target=800f01cc AA=0
800f01c8 b target=800f01ec AA=0
800f01cc lha rD=4 rA=3 displacement=0
800f01d0 or rS=30 rA=3 rB=30 Rc=0
800f01d4 bl target=800f036c AA=0
800f01d8 b target=800f01ec AA=0
800f01dc lha rD=4 rA=3 displacement=0
800f01e0 or rS=30 rA=3 rB=30 Rc=0
800f01e4 lfs fD=1 rA=2 displacement=-22992
800f01e8 bl target=800f061c AA=0
800f01ec stw rA=29 displacement=12 rS=30
800f01f0 addi rD=0 rA=0 immediate=2
800f01f4 stw rA=29 displacement=4 rS=0
800f01f8 lwz rD=31 rA=1 displacement=28
800f01fc lwz rD=30 rA=1 displacement=24
800f0200 lwz rD=29 rA=1 displacement=20
800f0204 lwz rD=0 rA=1 displacement=36
800f0208 mtlr rS=0
800f020c addi rD=1 rA=1 immediate=32
800f0210 blr
```
