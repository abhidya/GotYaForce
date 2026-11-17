# Normal actor callbacks and bounded lifecycle: archived evidence

## Result and limits

The fixed reader authenticates **four static pointer cells and 281 instructions
in seven independently selected spans**. Both existing local snapshots agree on
all values, operands, hashes, mappings and physical traces. It proves:

- Cue9's cell `802d3324` contains `80059138`, an immediate return with no actor
  access. Cue0's cell `802d3300` contains `8005913c`; that body's instructions
  are **not selected** and are not treated as a no-op.
- Constructor `8018ccfc` copies cell `8036554c` to actor `4c8`. That cell contains
  `8018cfe4`, another immediate return. This source is distinct from DoubleNinja.
- The previously documented Double constructor `8006f60c` instead copies cell
  `802d3b28` to actor `4c8`. That cell contains `8006f950`, whose first instruction
  is an immediate return. No GRED callback is inferred for DoubleNinja.
- `80059f5c` has genuinely returning flag and movement10 branches, but its other
  branches call a cue helper or perform rotation arithmetic. A list sentinel
  does not make the rotation branch a no-op.
- `8005a144` uses a signed16 countdown at `6bc`. It reads `4dc` only after a
  positive countdown reaches zero and after storing the decremented value.

This is archived static source evidence, **not original-DOL identity, live actor
ownership, runtime dispatch capture, retail parity, a full constructor port or
playable-game proof**. The constructor bytes identify source producers; they do
not permit manufacturing a callback field on an unrelated or incompletely
constructed actor. An explicitly observed runtime target must retain its own
identity. No unknown callback is treated as a return-only leaf.

Artifacts:
[`read_archived_actor_normal_evidence.py`](../tools/matching-decomp/read_archived_actor_normal_evidence.py)
and
[`test_archived_actor_normal_evidence.py`](../tools/matching-decomp/test_archived_actor_normal_evidence.py).
The reader accepts only one existing snapshot path. There is no address, index,
width, raw-output, execution or pointer-following CLI. Every selected instruction
must decode; unsupported forms fail rather than disappearing from the report.
Shared readers and shared allowlists are unchanged. No original or archived
instructions are executed, and no archive or executable payload is written.

## Fixed selections and extent evidence

The code selections are independent literals, not reads chosen by returned
pointer values. Each new plan was reported before its first payload selection.
The prior cue cells and cue9 leaf were promoted from the earlier fixed scratch
evidence. Constructor `8018ccfc`, its `4c8` source cell, the separate `8018cfe4`
leaf, and both postcallback spans were the initial new plan. The Double
constructor was selected next; its exact `4c8` cell address was reported before
that cell was separately selected. The cell's actual target was then reported
before the final independent 12-byte candidate span was selected.

| Entry / selection | End exclusive | Bytes | Instructions | Extent evidence |
| --- | --- | --- | --- | --- |
| Cue9 leaf `80059138` | `8005913c` | 4 | 1 | Independent four-byte selection; actual `blr`; no named map entry or C body |
| Constructor `8018ccfc` | `8018ce1c` | 288 | 72 | Map line 2419 gives `0x120`; C chunk 46 lines 4785/4823; conditional return at `8018cdfc`, final return at `8018ce18` |
| Callback `8018cfe4` | `8018cfe8` | 4 | 1 | Map line 2424 gives 4 bytes; C chunk 46 lines 4913/4923; actual `blr` |
| Postcallback `80059f5c` | `8005a144` | 488 | 122 | No map entry; C chunk 7 lines 2655/2711; all internal branch targets remain in range; single final `blr` at `8005a140` |
| Countdown `8005a144` | `8005a190` | 76 | 19 | No map entry; C chunk 7 lines 2711/2730; all conditional exits reach epilogue `8005a180`, final `blr` at `8005a18c` |
| Double constructor `8006f60c` | `8006f708` | 252 | 63 | Prior [Double boundary evidence](double-clone-reaction-boundary-2026-11-12.md) identifies this Ghidra-missed constructor; next C entry chunk 9 line 4061; no named map extent; actual final `blr` at `8006f704` |
| Double callback candidate span `8006f950` | `8006f95c` | 12 | 3 | Start authenticated by the separately read source cell; next C entry chunk 9 line 4142; no named map extent; **three immediate returns**, not one claimed 12-byte function |

The map is `research/symbols/GG4E-CSM-20220412.map`; C chunks are under
`research/decomp/ghidra-export/`. The last candidate span contains a `blr` at
each of `8006f950`, `8006f954`, and `8006f958`. Entry at the actual callback target
`8006f950` returns on its first instruction. Nothing here identifies which
callers, if any, own the adjacent return addresses. No neighboring pointer cell
was read to infer their identity.

## Authentication and mappings

Existing snapshots under `GotchaForce.rep.before_force_create/idata/00/~00000000.db/`:

- `db.3.gbf`: SHA-256
  `7b50dd2d2e17b4bfcc89a64cde27010247d0cbf0f48bd5c059f50275f40458d0`.
- `db.4.gbf`: SHA-256
  `1f86813d91ea8e2c4564f96622ec42555e1dba2c78aa81ad654e892140d019f8`.

Unchanged `read_archived_constants.inspect` authenticates the actual full-file
hash, exact schemas, program `boot.dol`, language
`PowerPC:BE:32:Gekko_Broadway`, Ghidra creation version `12.1.2`, executable-hash
metadata and property type, empty File Bytes, address maps, full data5 digest
and established controls **before** any selection in the new reader. Unchanged
`read_archived_command_evidence.mappings` checks all-block overlap plus exact
text1/data3/data5 block identities, encoded addresses, lengths and subblocks.
The new reader also derives actual text1/data3 tuples from authenticated rows
and requires their exact values and types before selected payload reads.

- Executable SHA-256 import metadata:
  `21454a8880c6254616662710d6ec626e43d853999da2cdfad700030960a94836`.
  This metadata is not proof that original executable bytes are unchanged.
- File Bytes: version 0, root -1, count 0. Image offset `80000000`; block size
  16384; master root 1.
- Text1: `800055e0..802b0160`, length 2796416, block/subblock 1, chain root 21.
- Data3: `802bae60..803af120`, length 1000128, block/subblock 5, chain root 199.
- Data5: `80436a20..8043d500`, length 27360, block/subblock 7, root 263;
  complete SHA-256
  `989c794b17fc95de6e57810f5c89db23d585c85a15faafc994d9a5bd9a0e61b4`.
- All three require subblock type 2, starting offset 0 and source offset 0.

Each selected range requires an exact address/width allowlist match, exact
mapping, integer types, alignment and bounds, returned width and SHA-256 before
decoding. Pointer cells additionally require their exact expected u32 target.
No raw range is emitted; output contains derived operands, values, hashes and
mapping/physical traces.

| Selection | Bytes | SHA-256 |
| --- | --- | --- |
| Cue9 cell `802d3324` | 4 | `2546ad0258f9f41c33b44ebd186e8486d9f61b7315e8494aa23a48df4777fb43` |
| Cue0 cell `802d3300` | 4 | `9580f1cc45ceb6223ad8f8413118771eee94978d6f6c1c752bab7d772c40c400` |
| Constructor source cell `8036554c` | 4 | `35f8fb00f9e6b005eabae38a3b327c8a5cfa27ce70355b05cc4041e757fbcc2e` |
| Double constructor source cell `802d3b28` | 4 | `c8e68f4fca4b823b7a7ffbe6210ccdc0041a26eed3c415fc65b553558a889157` |
| Cue9 leaf `80059138` | 4 | `f332ea5b5437103cbb6f1508679da89eec9288ad775c96c439a17fccabe3de8e` |
| Constructor `8018ccfc..8018ce1c` | 288 | `dda3561372b459527f131057a11caf6f4645b8bb0c80ac17372cb2e42ff6a58f` |
| Callback leaf `8018cfe4` | 4 | `f332ea5b5437103cbb6f1508679da89eec9288ad775c96c439a17fccabe3de8e` |
| Postcallback `80059f5c..8005a144` | 488 | `68a4b07dfea21671d8a803518f84c3a9935569931681b6116d827d7078ec3f59` |
| Countdown `8005a144..8005a190` | 76 | `fd9836eda5033e276bba22bf9d42f357c4ba31c68a3ed461a9d0def0a0975a53` |
| Double constructor `8006f60c..8006f708` | 252 | `201ead69a9e7e0cb04851db5f7498352ebdf5cbecc88be4486e68e2122e3e962` |
| Three return instructions `8006f950..8006f95c` | 12 | `26344477d6cb9e47db67286493a89c8016eaa46f7fcd67da87ddca2ec859f47a` |

All selections have one physical span in each snapshot, with identical traces.
Offsets and lengths below are decimal; every span has `obfuscated: true`.

| Address | Root / data buffer | Chain offset | Data offset | Physical offset | Length |
| --- | --- | --- | --- | --- | --- |
| `802d3324` | 199 / 206 | 99524 | 1256 | 3392750 | 4 |
| `802d3300` | 199 / 206 | 99488 | 1220 | 3392714 | 4 |
| `8036554c` | 199 / 242 | 698092 | 10216 | 3991534 | 4 |
| `802d3b28` | 199 / 206 | 101576 | 3308 | 3394802 | 4 |
| `80059138` | 21 / 42 | 342872 | 15312 | 719830 | 4 |
| `8018ccfc` | 21 / 119 | 1603356 | 14690 | 1980776 | 288 |
| `8018cfe4` | 21 / 119 | 1604100 | 15434 | 1981520 | 4 |
| `80059f5c` | 21 / 43 | 346492 | 2554 | 723456 | 488 |
| `8005a144` | 21 / 43 | 346980 | 3042 | 723944 | 76 |
| `8006f60c` | 21 / 48 | 434220 | 8392 | 811214 | 252 |
| `8006f950` | 21 / 48 | 435056 | 9228 | 812050 | 12 |

## Constructor producer schedules

Both constructors begin with `li r0,0`, compare r0 with 16, and conditionally
branch around a sequence of sixteen load/store pairs. Because the comparison
uses the freshly loaded zero, ordinary entry takes the copy path. The pairs
copy source offsets `0..3c` to actor offsets `4b4..4f0`. Their *instruction*
operands are decoded, but the reader selects only the one agreed source cell
in each table; it does not read or dump the rest of either table.

For `8018ccfc`:

1. `8018cd00` is `addis r4,0,-32714`; `8018cd08` adds `0x5538`, producing
   base `80365538`.
2. `8018cd38` is `lwz r0,0x14(r4)`, the exact static source `8036554c`.
3. `8018cd3c` is `stw r0,0x4c8(r3)`.
4. The separately selected source cell contains `8018cfe4`. Its independently
   selected instruction is `blr` with BO=20, BI=0, BH=0, LK=0.

For `8006f60c`:

1. `8006f610` is `addis r4,0,-32723`; `8006f618` adds `0x3b14`, producing
   base `802d3b14`.
2. `8006f648` is `lwz r0,0x14(r4)`, the exact static source `802d3b28`.
3. `8006f64c` is `stw r0,0x4c8(r3)`.
4. The separately selected source cell contains `8006f950`. The independently
   selected candidate span proves that entry returns immediately, with the
   same unconditional `blr` fields.
5. The prior Double descriptor producer is corroborated: `8006f6a8` sets the
   high part of r9 to `8034`; `8006f6d4` adds signed `-20616`, producing
   `8033af78`; `8006f6e0` stores that value to actor `4b0`.

The other constructor operations are represented in the reader output. They
are not claimed to be implemented, and none of their data pointers is followed.
In particular, authenticating these bytes does not produce a fully initialized
DoubleNinja actor or show that any browser actor already owns this callback.

## Normal tick context

The unchanged [tick reader](../tools/matching-decomp/read_archived_tick_prefix_evidence.py)
already authenticates `80059068..80059138`, including its final return at
`80059134`. The separate cue9 return at `80059138` is not padding attributed to
that caller, and the caller is not widened or reclassified here.

At the caller's normal boundary, signed cue indexing selects the table load at
`800590e0`, with indirect call at `800590e8`. Cue9's authentic return permits
continuation to the *actual* actor `4c8` load at `800590ec` and indirect call at
`800590f8`. The newly authenticated callback sources cannot replace that
load, establish a missing actor field or grant a generic callback registry.
After a supported actual callback returns, the caller proceeds through
`80059f5c` and `8005a144`; earlier helpers or unsupported paths still block later
effects. See the [control/tick evidence](actor-control-effect-evidence-2026-11-14.md)
for the existing outer schedule.

## `80059f5c`: real return branches and unimplemented work

The source first forms mask `0x81000003`: `addis` at `80059f64`, then `addi 3`
at `80059f6c`. It reads actor u32 `5e0` at `80059f78`, executes `and.` at
`80059f7c`, and branches at `80059f80` to `8005a114` if any masked bit is set.

### Flagged path

- `8005a114` reads actor byte `1d9`.
- `8005a118` uses `rlwinm` SH=0, MB=24, ME=27, Rc=1, testing its high nibble
  (`0xf0`). `8005a11c` exits to `8005a130` if it is zero.
- Otherwise, `8005a120` reads byte `57a`, **then** `8005a124` reads byte `57b`.
  `8005a128` ORs the loaded bytes; `8005a12c` stores the low byte to `57a`.
- Both alternatives return through the epilogue and `blr` at `8005a140`.
  Neither reads cues, `661`, rotation constants, `1dc8` or `4b0`.

### Unflagged path

- `80059f84` reads byte `5e4`; `80059f88` reads byte `5e5`. They are separately
  sign-extended at `80059f8c`/`80059f90` before comparison at `80059f94`.
- Equality branches at `80059f98` to `80059fa0`. Inequality reaches the direct
  call to **unselected helper `8006a6fc` at `80059f9c`**, with r3 retaining the
  actor and r4 holding signed cue `5e4`. Refusal there must occur before later
  `661` loads or any countdown effects.
- Only after equality or that helper's return does `80059fa0` read byte `661`.
  `80059fa4` compares the unsigned loaded byte with 10. `80059fa8` branches to
  the epilogue if equal. This is a genuine no-rotation return, but it does not
  bypass an earlier mismatching-cue helper.
- Otherwise, the first rotation-side constant load is `lfs` at `80059fac`
  (`r2-30296`); actor float `1dc8` is read at `80059fb4`. Other coefficient/bias
  loads occur at `80059fbc`, `80059fc8`, `80059fcc`; `80059fc4` is `fsubs`, and
  `80059fd0` is **single fused `fmadds`**, not an unfused multiply/add pair.
  These constants are not newly selected by this reader. The float environment
  and complete rotation behavior are not established by this evidence.
- The loop initializes CTR=8 and first reads actor `4b0` at `80059fd8`.
  It reads the signed byte at descriptor `b0 + index`, stops the loop on `-1`,
  and otherwise scales signed16 rotations at actor `18d4/18d6/18d8 + 6*index`.
  The descriptor payload is not selected. `8005a080` branches back while CTR
  remains nonzero.
- Crucially, the `-1` branch at `80059fec` goes to `8005a084`, **not the return**.
  The source still scales actor signed16 `18da`, `18dc`, and `18de`, storing
  them at `8005a0bc`, `8005a0e4`, and `8005a10c`. An empty descriptor list does
  not permit treating this path as completed without those effects.

All non-call branch targets remain within the selected function span. The only
direct call is `8006a6fc`; its body is not selected. The sole unconditional
return is `8005a140`.

## `8005a144`: signed countdown and lazy callback boundary

The complete nineteen-instruction schedule is asserted independently in the
test, including the prologue and epilogue:

1. `8005a150` loads actor **signed16** `6bc` into r4. `8005a154` compares with
   zero. The branch at `8005a158` exits if the value is nonpositive, without a
   timer store and without reading `4dc`.
2. A positive value is decremented at `8005a15c`. `8005a160` sign-extends the
   result into r0 and records CR0 **before** `8005a164` stores r4's low16 to
   actor `6bc`. `8005a168` uses the retained signed condition to exit if the
   new value is still positive. It does not read the timer a second time.
3. Only an original value of 1 can reach `8005a16c` under these signed16
   conditions. The countdown is already stored as zero before this instruction
   loads actor u32 `4dc` into r12.
4. `8005a170` compares that target with zero; `8005a174` exits if null.
5. A nonnull target reaches `mtctr r12` at `8005a178` and **indirect call
   `bctrl` at `8005a17c`**. The source retains the actor argument in r3. No `4dc`
   target body is selected here. The preceding timer store is real and must not
   be rolled back or omitted merely because the later call is unsupported.
6. All exits share epilogue `8005a180` and return at `8005a18c`.

Missing `4dc` cannot be silently replaced with null. Requiring `4dc` on a
nonpositive or still-positive timer path would be an invented earlier access.

## Reproduction and checks

From the repository root, using the existing local snapshots only:

```sh
PYTHONDONTWRITEBYTECODE=1 python -m unittest discover \
  -s research/tools/matching-decomp -p test_archived_actor_normal_evidence.py -v
PYTHONDONTWRITEBYTECODE=1 python research/tools/matching-decomp/read_archived_actor_normal_evidence.py \
  'research/decomp/GotchaForce.rep.before_force_create/idata/00/~00000000.db/db.3.gbf'
PYTHONDONTWRITEBYTECODE=1 python research/tools/matching-decomp/read_archived_actor_normal_evidence.py \
  'research/decomp/GotchaForce.rep.before_force_create/idata/00/~00000000.db/db.4.gbf'
```

The focused suite passes 20 tests with both snapshots present: fourteen
synthetic checks and six source checks. If the private snapshots are absent,
the six source tests are explicitly skipped; nothing is downloaded or fetched.
Synthetic checks cover input types, exact mappings, allowlists before payload
reads, hash/width rejection before decoding, unknown/reserved instruction
forms, CR and signedness fields, store direction, callback forms, whole-snapshot
authentication before selection, no pointer following and no selection/raw CLI.
Source checks cover all 281 instruction addresses, snapshot equality, each
constructor copy pair, actual return leaves, early gates, the rotation sentinel
trap and the complete countdown schedule. These tests decode static evidence;
they are not original execution, a behavioral oracle or product integration.

The broader `test_archived*.py` suite also passes all 659 tests in this checkout.


## Runtime admission and retained failures

The bounded TypeScript normal lifecycle selects only cue9 and the two exact
`4c8` return targets established above. Cue0's body, other cue cells, active
rotation damping and nonnull `4dc` calls remain reached refusals. Its normal
branch can join the same action/rate/ceiling continuation as the existing
ready branch only after all four intervening source calls return.

Existing actual flag fields are declared without defaults and mapped as
unsigned bytes at `57a` and `57b`; the actor codec map is regenerated from those
annotations. Movement, mapping, world, status and genuine cue-reset owners are
shared by identity. Only absent callback, countdown and metadata cells receive
new explicit partial storage.

Two host-only guards preserve honest incompleteness across attempts. An expiry
that has stored `6bc=0` remains incomplete until its explicit null callback
branch has returned. A reached genuine full-body cue reset is marked before
calling it and cleared only on a verified native0/1 return. A thrown reset may
already have changed `fbCue`, so equal cues on the next attempt cannot silently
skip the rest of that reset. Missing callees do not mark this latter guard.
Both guards block later normal work and ticks before raw ingestion, including
ready-branch bypasses. This conservative failure admission does not invent
source state, rollback, recovery, production activation or browser acceptance.
