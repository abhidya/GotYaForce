# Control40 helpers: archived source evidence

## Result and scope

The dedicated fixed reader authenticates **768 bytes and all 192 instructions**
in six independently preselected control40 helpers. Both existing immutable
local ProgramDB snapshots agree on every operand, window digest, physical
trace, direct call and internal branch. All six terminal returns, all 46
internal branches and all seven direct calls are represented. No instruction,
prologue, epilogue, branch field or gap inside a selected extent is omitted.

Artifacts:

- [Fixed reader](../tools/matching-decomp/read_archived_control40_helper_evidence.py).
- [Operand, scope and refusal tests](../tools/matching-decomp/test_archived_control40_helper_evidence.py).
- [All 192 independently transcribed expected operands and inverse encoder](../tools/matching-decomp/control40_helper_expected_operands.py).
- Existing [cue0-tail/predicate evidence](actor-cue0-tail-evidence-2026-11-14.md)
  and [input-tester evidence](actor-input-testers-evidence-2026-11-14.md) remain
  separate. Their windows are not reselected here.

This is **archived-source authentication**, not original execution, unchanged
original-DOL identity, a matching-decompilation verdict, live numerical parity,
implemented gameplay, runtime ownership or playability. The reader imports
unchanged sibling authentication/decoder modules and never executes archived
instructions. This evidence-only integration adds no TypeScript runtime,
callback, descriptor field or permission/capability. It does not upgrade any
existing callee's evidence class.

## Fixed selections and provenance

These six address/width pairs were selected from C/index markers before their
archived bytes were read. They are now recorded below and independently fixed
in the test fixture. No archived pointer was followed to discover a selection.
Addresses and actor offsets are hexadecimal; lengths and instruction counts
are decimal. Every exclusive end is the next C/index entry, not an assumed
symbol-map extent.

| Entry | Exclusive end | Bytes / instructions | SHA-256 |
| --- | --- | --- | --- |
| `80069210` | `800692bc` | 172 / 43 | `3e71a3acd38a50573c3a0b2ab3958a687210a5971ffa61cc351e677f28560d9e` |
| `800693fc` | `800694c0` | 196 / 49 | `92cbdc2d4b6e5efc0927794ce9d7bf6c2aff94e90daa83d0fd05079622688eb9` |
| `8006965c` | `800696f4` | 152 / 38 | `57bad1581c5e8afffe9468b6b01632e9b2a95f39a98fc2437241ff0250c7c045` |
| `800695c4` | `80069624` | 96 / 24 | `f6c8236fa71531c633a42b35c6c72a55f765de4e0445343fdd73f0e68f81819f` |
| `8006952c` | `8006958c` | 96 / 24 | `9cfabeeb65dcf3d78e5577d90e69a90a5fe5a44760fc5fe9b1ac6bb589f1c32a` |
| `800691d8` | `80069210` | 56 / 14 | `56208a03f0b329ba5e1d4e531dd7b1f71d9b4e2822a5445f5245d0f611f13fed` |

Source provenance in `ghidra-export/`:

| Entry / next symbol | `_index.tsv` rows | C file | Entry / next-marker lines |
| --- | --- | --- | --- |
| `zz_0069210_` / `FUN_800692bc` | 1342 / 1343 | `chunk_0008.c` | 5185 / 5220 |
| `FUN_800693fc` / `zz_00694c0_` | 1345 / 1346 | `chunk_0008.c` | 5290 / 5335 |
| `FUN_8006965c` / `FUN_800696f4` | 1352 / 1353 | `chunk_0009.c` | 1 / 38 |
| `FUN_800695c4` / `FUN_80069624` | 1350 / 1351 | `chunk_0008.c` | 5412 / 5440 |
| `FUN_8006952c` / `FUN_8006958c` | 1348 / 1349 | `chunk_0008.c` | 5366 / 5394 |
| `FUN_800691d8` / `zz_0069210_` | 1341 / 1342 | `chunk_0008.c` | 5172 / 5185 |

**Only `80069210` has a symbol-map row**, exactly
`80069210 000000ac 80069210 0 zz_0069210_` in
`research/symbols/GG4E-CSM-20220412.map`. The other five extents use independent
C/index markers and authenticated final returns. No symbol-map corroboration
is claimed for those five. Tests recheck exact adjacent index rows, adjacent C
markers and the sole applicable map row from repository files, without a
scratch-directory or saved-report dependency.

All internal edges are forward and stay inside their own selected extent.
Static CFG reachability accounts for every instruction and reaches the final
return **if direct calls return**. This is not a proof that callees return,
succeed or have any particular side effect. The selected helper order does
not independently authenticate a caller or a complete tick.

## Authentication and exact read scope

The existing ignored local inputs are under
`GotchaForce.rep.before_force_create/idata/00/~00000000.db/`:

- `db.3.gbf`: `7b50dd2d2e17b4bfcc89a64cde27010247d0cbf0f48bd5c059f50275f40458d0`.
- `db.4.gbf`: `1f86813d91ea8e2c4564f96622ec42555e1dba2c78aa81ad654e892140d019f8`.

Unchanged `read_archived_constants.inspect` authenticates the whole snapshot,
exact schemas, typed executable metadata, language, empty File Bytes, address
map, complete data5 digest and existing controls. Unchanged
`read_archived_command_evidence.mappings` checks exact text1/data3/data5 maps
and all-block nonoverlap. These checks precede every new text read. Each fixed
read then checks its unique address/width tuple, root, alignment, bounds,
returned length and pinned SHA-256 before decoding.

- Executable SHA metadata:
  `21454a8880c6254616662710d6ec626e43d853999da2cdfad700030960a94836`.
  This is a typed Ghidra 12.1.2 import property, not evidence of unchanged
  original executable bytes.
- File Bytes: version 0, root -1, count 0; no original file bytes are present.
- Block size 16384, master root 1, image offset `80000000`.
- `MAIN_.text1`: start `800055e0`, length 2796416, block/subblock key 1,
  chain root 21, subblock type 2, starting/source offsets 0.
- Full existing data5 digest:
  `989c794b17fc95de6e57810f5c89db23d585c85a15faafc994d9a5bd9a0e61b4`.

Chain tracing requires exactly 19 calls per snapshot: the unchanged complete
data5 authentication read and twelve existing controls, then the six fixed
text reads in the order above. No descriptor, scalar, cue table, phase table,
neighboring helper or whole text span is newly selected. Bodies `694c0`,
`696f4`, `69814` and `699d8` remain outside this reader. No raw executable dump,
runtime telemetry, original execution or dynamic pointer following occurs.

Both snapshots have identical physical provenance below. Offsets/lengths are
decimal, chain root is 21, and each span has `obfuscated=true`.

| Entry | Data buffer | Chain offset | Data offset | Physical offset | Length |
| --- | --- | --- | --- | --- | --- |
| `80069210` | 46 | 408624 | 15552 | 785606 | 172 |
| `800693fc` | 46 | 409116 | 16044 | 786098 | 196 |
| `8006965c` | 47 | 409724 | 274 | 786712 | 152 |
| `800695c4` | 47 | 409572 | 122 | 786560 | 96 |
| `8006952c`, first part | 46 | 409420 | 16348 | 786402 | 30 |
| `8006952c`, second part | 47 | 409450 | 0 | 786438 | 66 |
| `800691d8` | 46 | 408568 | 15496 | 785550 | 56 |

The `6952c` split falls inside an instruction. The unchanged chain reader
reassembles the bounded 96-byte window before big-endian decoding.

## Exact source schedules and corrections to the C-level reading

The following omits only stack/LR bookkeeping. Full operands, including every
branch and return field, are in the independent fixture and generated reports.
`lbz` zero-extends, `lhz` zero-extends, and `lha` sign-extends. Signed-byte
interpretation occurs only at an explicit `extsb`. `bc BO12` branches when the
named CR bit is set and `bc BO4` when it is clear; BI 0/1/2 means LT/GT/EQ.
All selected direct branches have AA 0; calls have LK 1 and other branches LK
0. Every selected return is BO 20, BI 0, BH 0, LK 0.

### `80069210`: retained pointer and byte, then cue `0x08`

1. `6921c`: load word `5e0`; `69220` tests mask 2. Nonzero returns 0 through
   `69228/6922c`, without reading any later actor field.
2. `69230`: load word `5d4`; `69234` tests mask 2. Zero returns 0 through
   `6923c/69240`.
3. `69244`: load byte `588`; `69248` sign-extends with CR0 recording. Zero
   returns 0 through `69250/69254`. Raw `80..ff` are nonzero, not rejected
   just because their signed interpretation is negative.
4. `69258`: load byte `7cd` into r4 **once**. `6925c` sign-extends a copy into
   r0, retaining raw r4. Its zero path executes this exact order:
   - `69264`: capture word `4ac` in r4.
   - `69268`: load byte `747` into r5.
   - `6926c`: load unsigned byte at **captured `4ac` + `9f`** into r0.
   - `69270`: sign-extend retained `747` into r4.
   - `69274`: signed-32 compare r4 with r0. `69278` permits the call only
     when signed `747` < unsigned `9f`; otherwise return 0.
5. For nonzero `7cd`, `69284` sign-extends retained raw r4 again. It does
   **not** reload actor `7cd`. Unless signed `7cd` equals 1, skip the `736`
   load and proceed to the call. When equal to 1, `69290` loads signed
   halfword `736` once and `69298` permits the call only if it is > 0.
   Raw `7cd` values `02`, `80` and `ff` all bypass `736`.
6. `692a4`: set cue 8 (`0x08`); `692a8`: call actual `8006a750` with the
   original actor. Pass the callee's native result through unchanged.
   Terminal return: `692b8`. No helper-owned actor write occurs.

The pointer must remain captured across the `747` read. A synthetic
adversarial getter that changes canonical `4ac` when reading `747` must not
redirect the subsequent `9f` access. Resolving `9f` early, re-reading `4ac`
afterward, reading `747` after `9f`, or re-reading `7cd` changes the schedule.

### `800693fc`: one movement read, real predicate, cue `0x0f`, fresh held reads

1. Save the actor in r31. `69410` loads byte `661`; `69414` sign-extends it
   **once**. The same retained r0 is compared with 2 at `69418` and 5 at
   `69428`. Either match returns 0; there is no second `661` read.
2. `69438`: call actual `800694c0`. Zero returns 0. Any nonzero result reaches
   the control read. **The real predicate precedes control1**, even when a
   later control test will reject.
3. `6944c`: load word `5e0`; `69450` tests mask 1. Nonzero returns 0.
4. `69460`: load unsigned halfword `5d8`; `69464` tests `0xf0`. Zero returns 0.
5. `69474`: restore actor r3; `69478`: set cue 15 (`0x0f`); `6947c`: call
   actual `8006a750`. `69480` compares the native result with **0, not 1**.
   Zero returns 0; any nonzero reaches storage.
6. `69490`: fresh unsigned halfword load from `5d8`, after the real cue call.
   `69494` sets helper result 1. `69498` extracts `(held >>> 4) & 15`.
   `6949c` stores the low byte to `58f`.
7. `694a0`: **another fresh unsigned halfword load from `5d8`, after the
   `58f` store**. `694a4` uses `rlwinm MB28 ME23`, whose 32-bit mask is
   `0xffffff0f`. `694a8` stores the low halfword to `5d8`, clearing `0xf0`.
   Terminal return: `694bc`.

Do not cache either post-cue read from the initial gate or across the `58f`
store. If the `58f` store fails, earlier cue effects remain. If the `5d8` store
fails, the earlier `58f` write remains too. The nonzero test does not authorize
a fake cue-result callback. A currently narrower 0/1 cue domain does not
change the authenticated branch.

### `8006965c`: direct movement equality, cue `0x16`, same ordered stores

1. Save actor r31. `69670` loads **unsigned** byte `661`; `69674` compares
   directly with 2. Other values return 0 without control, held or cue reads.
   There is no `extsb` instruction.
2. `69684`: load word `5e0`; `69688` tests mask 2. Nonzero returns 0.
3. `69698`: load unsigned halfword `5d8`; `6969c` tests `0xf0`. Zero returns 0.
4. `696ac`: set cue 22 (`0x16`); `696b0`: call actual `8006a750`, with original
   actor r3 retained through the gates. `696b4` tests the native result against
   **0, not 1**. Zero returns 0; any nonzero reaches storage.
5. `696c4`: fresh unsigned halfword load from `5d8`; `696c8` sets result 1;
   `696cc` extracts bits 4..7; `696d0` stores byte `58f`.
6. `696d4`: another fresh unsigned halfword load from `5d8`, after `58f`;
   `696d8` masks with `0xffffff0f`; `696dc` stores the low halfword to `5d8`.
   Terminal return: `696f0`.

### `800695c4`: status mask `0x000f0000`, cue `0x13`

`695d0` loads unsigned byte `661`; `695d4` compares directly with 2, with no
sign extension. Unequal returns 0. `695e4` loads word `5e0`; nonzero mask 2 at
`695e8` returns 0. `695f8` loads word `5b4`; `695fc` tests `0x000f0000`.
Zero returns 0 through `69610`. Nonzero sets cue 19 (`0x13`) at `69604` and
calls actual `8006a750` at `69608`. Native result passes through unchanged.
Terminal return: `69620`. No actor writes outside the actual callee occur.

### `8006952c`: status mask `0x00000100`, cue `0x12`

`69538` loads unsigned byte `661`; `6953c` compares directly with 2, with no
sign extension. Unequal returns 0. `6954c` loads word `5e0`; nonzero mask 2 at
`69550` returns 0. `69560` loads word `5b4`; `69564` tests `0x00000100`.
Zero returns 0 through `69578`. Nonzero sets cue 18 (`0x12`) at `6956c` and
calls actual `8006a750` at `69570`. Native result passes through unchanged.
Terminal return: `69588`. No actor writes outside the actual callee occur.

### `800691d8`: actual ground probe unless world mode is 2

`691e4` loads unsigned byte `4a0`; `691e8` compares directly with 2, with no
sign extension. Equality sets result 0 at `691f0` and skips the call.
Otherwise `691f8` calls actual `800677b0` on the original actor; `691fc` then
overwrites r3 with 0 regardless of the **completed** callee's return.
Terminal return: `6920c`.

A thrown, unsupported or incomplete ground operation is not a completed return
and cannot be swallowed as 0. Reusing a prior query, installing a fake ground
callback, substituting a no-op or forcing world mode 2 is not equivalent.
Equality with 2 is numerically equivalent under signed-byte interpretation,
but that does not justify inventing an `extsb` in any of these four helpers.

## Canonical ownership and remaining integration dependencies

These are existing-source cross-references at base `d73035ba`, not newly
implemented behavior or authenticated live object identity.

| Cell/callee | Required existing owner or identity |
| --- | --- |
| `5e0` / `5d4` / `5b4` | Actual `RomActor.controlWord` / `inputEdge5d4` / `statusWord5b4`, raw 32-bit |
| `5d8` | Same actual `RomActor.inputHeld5d8`, raw unsigned 16-bit for these helpers |
| `588` | Genuine `SourceActorCueResetBinding.byte588`, raw byte |
| `661` | Genuine `SourceActorMovementFollowupBinding.byte661`, raw byte |
| `7cd` / `58f` | Existing `SourceActorCue0TailBinding.byte7cd` / `byte58f` |
| `747` / `736` | Existing `SourceActorStatusTimersBinding.byte747` / `short736`; signed interpretation only at source instructions |
| `4ac` | Existing `SourceActorAttributeRefreshBinding.parameter4ac`, retaining the identity returned by its canonical property read |
| pointed `9f` | The same `4ac` descriptor registry record returned by the genuine attribute runtime; its current interface/factory has no canonical `9f` field |
| `4a0` | Existing `SourceActorWorldMatrixBinding.mode4a0`, raw byte |
| `6a750` | Genuine cue-reset runtime, same actor/cue owners and actual native result |
| `694c0` | Genuine cue0-tail predicate; reuse existing evidence rather than a looser callback |
| `677b0` | Same actual ground-probe runtime already joined to frame/action owners, including actor/Borg/gauge `7c9`/world/status/history/terrain/position |

`packages/combat/src/rom/actor-attribute-refresh.ts:49–59` lacks `9f`;
`createParameterDescriptor` starts at line 205. Legacy `4b0.handlerData9f`
must **not** stand in for `4ac + 9f`. A future implementation may add explicit
optional raw-u8 `byte9f` on the existing `4ac` record with no default and a
genuine checked resolver, or retain a precise lazy boundary at the active
`9f` access. This evidence selects no descriptor and establishes no live
value. Pointer capture, `747` access and `9f` resolution must keep their
source order.

`actor-cue0-tail.ts:159–176` protects most canonical owners/aliases, but not
new `588`, `747` or `4ac` access. Any extension must check actual existing
owners without creating scalar mirrors or eagerly reading guarded data.

`actor-ground-probe.ts:125–127` requires the private invocation capability for
the exact genuine runtime. `actor-double-prehook.ts:87–89` presently permits
nested ground/stream only from the genuine full-action stage.
`actor-frame-lifecycle.ts:217–228` joins the actual ground and issues private
access during frame claim; the ordinary tick/normal stage runs before the
later Double action. Thus `691d8` still needs a narrowly scoped genuine
normal-stage ground capability on that same runtime. Public replay guards
must not be relaxed; ground must not be cloned, replaced by zero callbacks or
made accessible through stale private access. This is an integration
dependency, not uncertainty about the archived wrapper instructions.

Under the unchanged earlier fixture facts (`control=0x43`, `661=0`, `7cd=0`,
`4a0=0`), `69210` returns 0 at its first gate; `693fc` calls real `694c0` before
control1 rejects; `6965c`, `695c4` and `6952c` return 0 at movement; and `691d8`
must call real `677b0`. This is a source-backed conditional implication, **not
a new composed runtime execution**. Other helpers, caller coverage and later
normal/action/rate/ceiling stages remain outside these selections. No
next-frame phase1, phase table, complete tick or playability is established.

## Validation and reproduction

Validation on 2026-11-14:

- Dedicated reader tests: **20/20 passed**, including both existing snapshots.
- All **192 independent explicit operand records** inverse-encode to the six
  pinned window hashes. These fixtures are not generated from the production
  decoder or a saved JSON report.
- **6,144/6,144** single-bit selected-byte mutations are rejected.
- Exact map/index/C markers, complete coverage, direct targets, AA/LK,
  conditional fields, terminal return fields, interior returns, reachability,
  reserved decoder fields, displacements, wrong roots/extents/types,
  truncated/extra reads and unselected old bodies/scalars fail closed.
- Whole-hash and spoofed-digest failures precede parsing. Schema, typed
  metadata, empty File Bytes, address/text/data maps, full data5 hash and
  control mutations refuse before any new selection.
- Chain-call tracing proves the exact unchanged authentication reads followed
  by only the six new fixed windows; physical spans are pinned, including the
  instruction split across two archive buffers.
- Unchanged shared constants tests: **16/16 passed**.
- Archived-reader regression discovery (`test_archived_*.py`): **926/926
  passed**, including the new suite. Existing reader selections are unchanged.
- Simulated clean-checkout absence of archives: **12 synthetic/source tests
  passed**, with the local-archive class explicitly skipped. No archive is
  fetched or synthesized. A skipped class is not archive verification.

From the repository root:

```sh
PYTHONDONTWRITEBYTECODE=1 python research/tools/matching-decomp/test_archived_control40_helper_evidence.py
PYTHONDONTWRITEBYTECODE=1 python -m unittest discover -s research/tools/matching-decomp -p test_archived_constants.py -v
PYTHONDONTWRITEBYTECODE=1 python -m unittest discover -s research/tools/matching-decomp -p 'test_archived_*.py' -v
mkdir -p .tmp
PYTHONDONTWRITEBYTECODE=1 python research/tools/matching-decomp/read_archived_control40_helper_evidence.py research/decomp/GotchaForce.rep.before_force_create/idata/00/~00000000.db/db.3.gbf > .tmp/control40-helper-evidence-db3.json
PYTHONDONTWRITEBYTECODE=1 python research/tools/matching-decomp/read_archived_control40_helper_evidence.py research/decomp/GotchaForce.rep.before_force_create/idata/00/~00000000.db/db.4.gbf > .tmp/control40-helper-evidence-db4.json
```

The CLI accepts only a snapshot path and refuses address, width, pointer,
target, dump, raw or execute options. Tests optionally accept an existing
snapshot directory through `GOTYAFORCE_ARCHIVED_PROGRAMDB_DIR`; the CLI has no
such selection override. Shared readers and their allowlists are unchanged.
The generated JSON files contain only derived operands, hashes and provenance;
they are ignored local audit outputs, not committed executable bytes.

The integrated reader's reports are byte-identical to the independently
reviewed pre-integration authentication reports:

- db3 report SHA-256: `40c01838eac828d1e0b00f2041e0981158bd9755b6986c9c50abf226858f735f`.
- db4 report SHA-256: `f7eddbb7340cca5d722ef00336e1987fc2d83155b6824d2ba8b6849797ab7213`.
- Independent fixture SHA-256, unchanged from its authenticated input:
  `deda32a7df5311f1833339d0996454170adaaa0c8a9a1d5c020c2fdc83f39400`.

No runtime file, old reader, old allowlist, original input or authentication
rule was edited for this integration. No original executable was run; no
telemetry, broad dump, commit or publication was produced.
