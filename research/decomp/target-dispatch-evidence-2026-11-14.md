# Target dispatch: bounded archived instructions and one table cell

Date: 2026-11-14. Investigation base:
`0759f00241bf69dae336d3f2d471e470f37e5fb2`. No commit or push by this investigation.

The [fixed reader](../tools/matching-decomp/read_archived_target_dispatch_evidence.py)
authenticates **620 code bytes / 155 instructions**, plus exactly one separately
frozen four-byte dispatch cell. Both archived snapshots agree on every operand,
control edge, selected-cell target and physical span. The
[literal fixture and independent inverse](../tools/matching-decomp/test_archived_target_dispatch_evidence.py)
contains the complete instruction/address inventory, including both complete
save/restore sequences. All **16 focused tests pass**.

Key findings:

- Inactive `8006b7f4` clears `+502` with **one byte store**, then `+508` and
  `+504` with **two word stores in that order**. The decompiler's eight byte
  assignments for those pointer fields are not the instruction granularity.
- Active dispatch sign-extends actor byte `+502`, multiplies by four, loads
  a target from `802d39a0 + signed_index*4`, and makes a linked indirect call
  with r3 still the actor. There is **no bounds or null guard**.
- Only index-zero cell `802d39a0` was selected. It holds `8006b850`; this does
  not establish any table extent or other legal/implemented index.
- `8006b850` has an authentic nonzero-`+73f` early return. Otherwise it loads
  the object count **before** resetting the scratch count. Zero input count
  skips all list payload access, but still reloads scratch count before the
  return decision. C's apparent loop-header scratch-list assignment is absent
  from this instruction path.
- `8006b850..8006ba60` is a **C/index-bounded span**, not independently
  map-size-proven. There is no named map record for either address.

This is archived ProgramDB static evidence. It is not independently measured
original-DOL identity, original-code execution, `MATCH`, live dispatch, runtime
integration, a completed frame or playability. Test inversion constructs
synthetic instruction words; it does not execute them. No runtime file,
shared authenticator, shared decoder, mapping validator or shared allowlist
was changed. No estimator was imported.

## Three scope freezes before their respective selected reads

All scopes are preserved locally under
`.tmp/target-dispatch-evidence-20261114/`. None was amended after its read.

| Scope file | SHA-256 | Selection |
| --- | --- | --- |
| `scope-frozen.json` | `dbed8ccb85183c2c37a4404be4c8629d0c9152702cfd396c9004649701bc81bc` | `8006b7f4..8006b850`, 92 bytes |
| `entry-zero-scope-frozen.json` | `afeccd2c0e9c2307560b95573fa87df4235055781b1bbd7f4be539e16edb3236` | `802d39a0..802d39a4`, four bytes |
| `entry-zero-body-scope-frozen.json` | `994fb4ec6df229a72c7e48143145126995520fbc50761546d844171a6fbdb52b` | `8006b850..8006ba60`, 528 bytes |

The first body has independent C/index identity and named map-size agreement:
`ghidra-export/chunk_0009.c:1586–1606`, `_index.tsv:1393–1394`, and
`research/symbols/GG4E-CSM-20220412.map:836`, exact size `0000005c`.

The first read established the signed-index/base/stride/indirect-call sequence.
The next freeze selected only the explicitly requested index-zero cell. It did
not select the destination code, neighboring cells or all mathematically
reachable addresses. The target was reported before a separate follow-on scope.

The third selection was explicitly agreed after verifying that index zero holds
`8006b850`. Its independently fixed readable provenance is
`ghidra-export/chunk_0009.c:1610–1687` and `_index.tsv:1394–1395`. The adjacent
entry is `8006ba60`; difference `0x210` fixes the selected width. The map jumps
from `8006b7f4/0x5c` to `8006bc74/0x80`, with no named `8006b850` or
`8006ba60` record. Exact authenticated text-mapping agreement establishes the
selected addresses are in that block, not an independent function-size proof.
The complete span ends in `blr` at `8006ba5c`; every non-call direct branch
stays within it, and every selected instruction is represented. These control
facts support the bounded analysis without upgrading the extent provenance.

The final reader's addresses and widths are fixed literals, never calculated
from a pointer at read time. The pointer was used to motivate a separately
reviewed scope, not to authorize automatic code following. No additional
pointed body or data was selected.

## Authentication and exact payload reads

Unchanged `read_archived_constants.inspect` authenticates complete actual
snapshot SHA-256, schema, PowerPC identity, address maps, executable metadata,
empty File Bytes table, and its established full-data5/control reads. Unchanged
`command.mappings` validates identity, bounds, initialization and overlaps.
Unchanged `normal.mapping_evidence` checks exact typed text and data3 mappings.
All those checks precede any selected payload read. Exact width and digest
precede every selected operand or pointer decode.

Existing files are in
`research/decomp/GotchaForce.rep.before_force_create/idata/00/~00000000.db/`:

| Snapshot | Bytes | Actual complete SHA-256 |
| --- | --- | --- |
| `db.3.gbf` | 57655296 | `7b50dd2d2e17b4bfcc89a64cde27010247d0cbf0f48bd5c059f50275f40458d0` |
| `db.4.gbf` | 58802176 | `1f86813d91ea8e2c4564f96622ec42555e1dba2c78aa81ad654e892140d019f8` |

Both report `boot.dol`, Ghidra `12.1.2`, File Bytes version 0/root −1/count 0,
and image offset `80000000`. Executable SHA-256
`21454a8880c6254616662710d6ec626e43d853999da2cdfad700030960a94836`
is import metadata, not independently measured original-DOL identity. Existing
full-data5 authentication hash remains
`989c794b17fc95de6e57810f5c89db23d585c85a15faafc994d9a5bd9a0e61b4`.
No new global payload selection does not mean those authenticator reads vanish.

Exact typed mapping tuples:

- Text: `(800055e0,802b0160,1,MAIN_.text1,1,2796416,21)`.
- Data3: `(802bae60,803af120,5,MAIN_.data3,5,1000128,199)`.
- Both selected subblocks have type 2, starting offset 0 and source offset 0.

| Selection | SHA-256 |
| --- | --- |
| `8006b7f4`, 92 bytes | `227945853f20b8b08ef9f71c6dde02a0ea8136652eb1e4e5d034fdab962d5b12` |
| `802d39a0`, four bytes | `a1f65fe8b7d29bda8e482aabf099797030ea8959dbd1559665487fb793a5b9ad` |
| `8006b850`, 528 bytes | `8a01e4c3f1a21269d2b9fb98b2d6c71ab2d46859d9670049069db7c6eafabb51` |

| Selection | Root / data buffer | Chain offset | Buffer data offset | Physical offset | Bytes |
| --- | --- | --- | --- | --- | --- |
| `8006b7f4` | 21 / 47 | 418324 | 8874 | 795312 | 92 |
| `8006b850` | 21 / 47 | 418416 | 8966 | 795404 | 528 |
| `802d39a0` | 199 / 206 | 101184 | 2916 | 3394410 | 4 |

All are obfuscated buffers. The entire additional read trace of the final fixed
reader, after the separately traced unchanged authenticator, is exactly:

```
(21, 418324, 92, 2796416)
(21, 418416, 528, 2796416)
(199, 101184, 4, 1000128)
```

Reports contain derived operands, hashes, spans and provenance, not raw selected
binary or instruction-word output. No input was acquired or changed.

## `8006b7f4`: complete dispatch semantics

Entry allocates 16 stack bytes, saves LR at stack+20, loads actor byte zero at
`8006b800`, and sign-extends with record at `8006b804`. BO4/BI2 at `8006b808`
branches on nonzero to active dispatch. All nonzero byte encodings, including
negative signed encodings, use that path.

For zero actor byte, set r0=0 and perform precisely:

1. `8006b810`: `stb r0,1282(r3)` clears actor+`502`.
2. `8006b814`: `stw r0,1288(r3)` clears actor+`508` as one word.
3. `8006b818`: `stw r0,1284(r3)` clears actor+`504` as one word.
4. `8006b81c`: branch to the common epilogue.

It does not read actor+`502` on the inactive branch or clear other actor fields.
Pointer-null updates in a clone must preserve both word granularity and order;
there is no need to invent a numeric address for a partially cleared pointer.

Active dispatch reads actor+`502` at `8006b820`. `addis r4,0,-32723` and
`addi r4,r4,14752` form `802d39a0`. `extsb r0,r0` at `8006b82c` makes the
index signed. `rlwinm r0,r0,2,0,29` at `8006b830` is a low-32-bit left shift
by two; `lwzx r12,r4,r0` loads the indexed word. `mtctr r12` and
`bctrl` BO20/BI0/BH0/LK1 at `8006b83c` call it. r3 has not been changed and
still holds the actor. No instruction validates index, target or actor pointer.

Signed indices range −128..127; address arithmetic reaches base−512 through
base+508, but this is **not** evidence that all those words belong to a table
or are valid destinations. Only base cell/index zero is authenticated, holding
`8006b850`. Other indices must remain unsupported without separate evidence.

Both routes restore LR from stack+20, release the frame and return. This body
does not define a useful return value from the indirect callee.

## `8006b850`: early return and zero-object path

The 64-byte frame saves LR, f31, paired-single f31, and r27–r31. Source actor
is copied to r30. C's warnings about unreachable `8006b860` and `8006ba44`
refer to the ordinary `psq_st` and `psq_l` save/restore sites. Both are present
on normal paths; a direct-edge CFG reaches every instruction in the selected
span. No live GQR0 or floating-point state is inferred.

At `8006b86c`, load actor+`73f`, sign-extend with record, then branch NE at
`8006b874` to `8006ba44`. For any nonzero encoding this path accesses no
object count, scratch count, list or target fields. It still performs the
complete stack/register save and restoration sequence.

If `+73f` is zero, the exact order is:

1. `8006b878`: load **unsigned halfword** into r4 from `r13-21342`.
2. Form object-list address `803c1d7c`, set r0=0.
3. `8006b888`: store zero word at `r13-21504`.
4. Load CTR from r4, compare r4 to zero, branch not-GT at `8006b894` to
   `8006b918`. Since r4 is an unsigned halfword, this skips only for zero.
5. `8006b918`: **reload** scratch-count word from `r13-21504`, compare zero,
   and branch EQ at `8006b920` to the common epilogue.

The C names the count sources `DAT_80436242` and `DAT_804361a0`. Instructions
retain r13-relative offsets; no selected body initializes r13 or establishes
its live value. The zero-input-count path does not load or write
`DAT_803b2208`, contrary to a literal reading of the decompiler's loop header.
It writes the scratch count before reloading it, touches no actor target fields
and makes no distance call. This is source order, not permission to synthesize
live count values, owners or alias behavior.

Common epilogue at `8006ba44` executes `psq_l f31,56(r1),W0,I0`, `lfd f31`,
`lmw r27`, LR reload/restore, stack release, then `blr` at `8006ba5c`.

## Remaining selected path, without claiming its dependencies

The nonzero-count scan visits object pointers from `803c1d7c` in ascending
four-byte order, with original CTR count. It skips null object, null object+`20`
actor, zero signed actor byte, self, same signed team, team 4, or signed actor
status `+18 >= 2`. Unlike the selector's scan, it does **not** inspect an
object+`28` flag before admitting a candidate. Negative status-byte encodings
pass the signed `<2` comparison. On admission it loads scratch count, computes
`803b2208 + count*4`, increments/stores count at `8006b908`, then stores the
object with `stwx` at `8006b90c`.

After the scan, reload scratch count and return if zero. Otherwise load
actor+`4b0`, then its byte+`10`, sign-extend and multiply by `0x30`; read floats
at actor plus that stride plus `8e0`, `8f0`, `900`. Each load is immediately
stored at stack+8/+c/+10. There is no null guard on actor+`4b0`. Initial
scratch object is the winner. Calls at `8006b968` and `8006b990` go to still
unselected `8020bc88`, with r3=stack+8 and r4=candidate+`64`. Loop count is
freshly reloaded at `8006b9ac`.

`fcmpo f1,f31` followed by BO12/BI1 at `8006b998` skips replacement only
for GT; equality and unordered both replace winner and f31. Neither a C-style
ordered `<=` nor an assumed distance implementation establishes those semantics.

The selected winner's actor pointer at +`20` is loaded. If non-null and its
object+`28` pointed halfword+2 lacks bit `0x200`, and final scratch count is
positive, scan the scratch objects for the first sharing that actor pointer
and having `0x200`. Adopt that object when found; otherwise keep the winner.
The selected actor pointer is retained in r6 rather than reloaded per candidate.
The flag-pointer reads have no null guards. No live list/flag payload is selected.

Commit order beginning `8006ba1c`:

1. Store byte 1 to actor+`502`, then winner word to actor+`504`.
2. Load winner+`20`, then store to actor+`508`.
3. Load winner+`64`, then winner+`68`; store actor+`50c`, then actor+`510`.
4. Load winner+`6c`, then store actor+`514`.
5. Enter full common epilogue.

It does not write selector fields `+503`, `+73c`, `+3f1` or slot records.
Loads paired before stores and the later fresh `+6c` read are observable if
memory aliases. The code does not justify atomic bulk replacement.

## Validation and remaining ceiling

From repository root:

```
python -m unittest discover -s research/tools/matching-decomp -p 'test_archived_target_dispatch_evidence.py' -v
```

All 16 focused tests pass with both local snapshots present. The broader archived
evidence regression command, `python -m unittest discover -s
research/tools/matching-decomp -p 'test_archived_*evidence.py'`, also passes
**1184 tests** (38.916 seconds). `py_compile` for both new Python files and
`git diff --check` pass. These are not full contributor/build gates. Coverage includes:

- All 155 literal instruction/address/operand records and an independent bit
  inverse reconstructing both selected SHA-256 values.
- All 4960 instruction-bit mutations either refused or decoded differently
  and independently re-encoded to the changed word.
- All 4960 code-payload bit mutations refused before decoding; all 32 pointer
  payload bit mutations refused before pointer decoding; wrong target refused.
- Complete 28-control-instruction inventory and 155 individual mutable-flow
  metadata corruptions refused.
- Exact inactive store widths/order; signed index, no guard and retained actor
  argument; `+73f` guard; count-load/reset/reload order; zero-count absence of
  list access; both PSQ warning sites; full return and CFG coverage.
- Candidate signed comparisons, count-before-pointer write, unordered nearest
  replacement, redirection prerequisites and alias-sensitive commit order.
- C/index boundaries and map presence for `8006b7f4`, explicit absence of named
  map sizes for `8006b850`/`8006ba60`, typed mapping/range/width refusal.
- Authentication failure before parser/selection, 43 mapping refusal cases,
  schema/digest refusals, exact complete authentication-plus-selection traces,
  physical spans, no raw output, and no arbitrary-address CLI.

Tests do not execute original instructions, authenticate live actor/global/list
payloads or r13, establish other table entries, prove the distance callee or
GQR/FPSCR behavior, or promote runtime behavior. These remain explicit limits.
