# Double phase-one entry: four fixed archived selections

2026-11-14. Evidence-only checkpoint based on checkout
`0aae10173229c781c837bb3c3ee1d395d7683a84`. This promotes four selections
from the earlier bounded preparation into a dedicated reproducible reader,
independent operand tests, and this source contract. It changes no runtime or
shared archive reader and does not execute original code.

The complete `800ff418` body scales the actor's **existing** motion, then adds
it to position. It does not subtract position history. Signed positive
`actor+1cef` causes a byte increment at `actor+540` **before** the reached
callback load/call. The actual selected callback is **`800715f8`, not null**.
After the optional callback returns, magnitude `8020bb14` is called on every
continuing path; only a result greater than **3.0** calls `800b22f4`.

These are authenticated archived ProgramDB facts, not original-DOL identity,
an original execution trace, `MATCH`, full action playback, runtime integration,
or playability. A complete static body is not a complete implementation of its
callees or numerical behavior.

## Files and fixed scope

- [Dedicated reader](../tools/matching-decomp/read_archived_phase1_entry_evidence.py).
- [Independent operand fixture and tests](../tools/matching-decomp/test_archived_phase1_entry_evidence.py).
- Reused authentication: unchanged `read_archived_constants.py`,
  `read_archived_command_evidence.py` mapping validation, and exact mapping
  helpers/constants from `read_archived_actor_normal_evidence.py` and
  `read_archived_double_action_evidence.py`. No imported reader's `inspect`
  is called except the existing whole-snapshot authenticator.

The new reader makes exactly these four selections, totaling **200 bytes**:

| Selection | Width | Derived fact | SHA-256 |
| --- | ---: | --- | --- |
| `8031f004` | 4 | phase1 target `800ff418` | `21ba1af7a6b8585448a533d5cb69f0592dcae0a1c27ec6c49625f39f61f527da` |
| `800ff418..800ff4d4` | 188 | 47 instructions, terminal `blr` at `800ff4d0` | `4d7718098a024195217efd94548567af5e30aefaa970b02de985bc2566fd59e8` |
| `8043386c` | 4 | config callback `800715f8` | `91cbc2b5e1dc50f2d1d25c141235833e121cc9f3139cdc919a5b10fe6155a607` |
| `804392c8` | 4 | binary32 bits `40400000`, value 3.0 | `638354a0b185ec05318029e52610c8de48d33523e2b4854e71154187583d1037` |

Each selection is literal and independently justified; no returned pointer or
decoded call chooses another read. Excluded: command prefixes, command table,
stream bank headers, other phase cells, phase2, `715f8` and `b22f4` bodies,
the magnitude body, and a fresh read of the existing `.95` scalar. There is no
address/width/raw-dump option or archive modification.

### Independent selection and extent basis

- Phase1 cell is the prior documented shared table base `8031f000` plus slot1
  width4. The signed `540` dispatch and table base were already authenticated
  in [Double action-envelope evidence](double-action-envelope-evidence-2026-11-14.md).
  This is not a dynamically followed phase0 pointer.
- `ghidra-export/chunk_0028.c:1778–1805` independently bounds `ff418` by the
  next `ff4d4` marker. `_index.tsv:4246–4247` independently names both entries.
  `research/symbols/GG4E-CSM-20220412.map:1788` gives `000000bc` = 188 bytes.
  The selected bytes authenticate the return at `ff4d0`; all47 instructions
  and operands are represented with zero unrepresented ranges.
- Config base `80433868` is established by the prior wrapper evidence and
  [Ninja source analysis](ninja-source-x-2026-11-12.md). The C body independently
  identifies the callback field at config+4; this fixed cell is `8043386c`.
  Neither its target nor the body pointer is used to expand the read scope.
- The independently named `FLOAT_804392c8` in `chunk_0028.c:1797` selects the
  threshold. The authenticated `lfs f0,-22360(r2)` at `ff4a8` corroborates it
  using the previously recorded `r2=8043ea20`. That base is recorded context,
  not a newly measured processor/startup state.

## Authentication and physical provenance

Both existing optional local inputs reside in
`research/decomp/GotchaForce.rep.before_force_create/idata/00/~00000000.db/`:

- `db.3.gbf`: `7b50dd2d2e17b4bfcc89a64cde27010247d0cbf0f48bd5c059f50275f40458d0`.
- `db.4.gbf`: `1f86813d91ea8e2c4564f96622ec42555e1dba2c78aa81ad654e892140d019f8`.

Before any new selection, the unchanged authenticator checks the actual whole
SHA, schemas, ProgramDB metadata and language, File Bytes table, mappings,
complete data5 digest, and its established controls. File Bytes is
`version=0, root=-1, count=0`. The stored executable SHA is metadata, not a
fresh original-executable measurement. Agreement between snapshots does not
raise that ceiling.

The additional mapping checks require exact text/data3/data4/data5 identities,
lengths, roots and zero starting/source offsets, with a single initialized
data4 subblock of type2. No overlapping/duplicate/misplaced mapping is admitted.

| Mapping | Virtual interval | Length | Root |
| --- | --- | ---: | ---: |
| `MAIN_.text1`, key1 | `800055e0..802b0160` | 2796416 | 21 |
| `MAIN_.data3`, key5 | `802bae60..803af120` | 1000128 | 199 |
| `MAIN_.data4`, key6 | `804335a0..804360c0` | 11040 | 262 |
| `MAIN_.data5`, key7 | `80436a20..8043d500` | 27360 | 263 |

Both snapshots produce these identical spans. Offsets below are decimal,
physical offsets are relative to each GBF, and every span is marked obfuscated:

| Selection | Root/data buffer | Chain offset | Data offset | Length | Physical offset |
| --- | --- | ---: | ---: | ---: | ---: |
| `800ff418` | 21/84 | 1023544 | 8108 | 188 | 1400754 |
| `8031f004` | 199/225 | 410020 | 570 | 4 | 3703360 |
| `8043386c` | 262/262 | 716 | 716 | 4 | 4309718 |
| `804392c8` | 263/264 | 10408 | 10408 | 4 | 4352174 |

The tests separately trace the unchanged authenticator and require the full
reader's read list to equal that list followed by exactly four literal reads.
The existing full-data5 authentication is retained, not represented as a new
arbitrary-range selection. No raw body bytes or instruction words are emitted;
the output contains derived operand dictionaries, values, hashes, and spans.

## Complete phase-one source order

Entry ABI is actor in r3 and config in r4. Stack/LR/r30/r31 preservation and
restoration are part of the47-operand fixture, not omitted from the body.

1. `ff428` retains incoming config in r31; `ff434` retains actor in r30.
   `ff42c` sets r4=15 and `ff438` calls **`8004cd24(actor,15)`**. This is the
   actual stream update, not `animatePart`, a fabricated completion result,
   or a synthetic state write.
2. `ff43c..ff444` call **`8006d144(actor,0xc1)`**. Reuse the existing genuine
   null-target yaw behavior and keep its unsupported nonnull-target boundary.
3. `ff448..ff454` pass actor+38 as both input and output to **`8020ba9c`**,
   loading the already authenticated `.95` scalar at `804392d0`.
   Bits `3f733333` mean 0.949999988079071, not an exact decimal .95. There is
   **no** `8020ba78` subtraction or `actor+5e8` history read in this body.
4. `ff458..ff464` call **`8020ba54(pos20,motion38,pos20)`**. Keep the existing
   paired load/store ordering of scale and add, rather than a newly rounded
   convenience expression or phase0's subtract/scale/add bundle.
5. `ff468..ff46c` call **`800677b0(actor)`**; its return value is ignored here.
   Retain the actual ground runtime and its private frame invocation.
6. Only after those effects, `ff470` freshly loads unsigned byte **`1cef`**.
   `ff474` sign-extends it and records the comparison condition. `ff478`
   skips the following block unless that signed value is positive. Raw80/ff
   therefore mean negative values; this is authored state, not collision.
7. On a positive state, `ff47c` loads byte **`540`**, `ff480` adds1, and
   `ff484` stores the low byte. Only **after the increment**, `ff488` reads
   config+4 into r12. `ff48c/ff490` test null; `ff494/ff498/ff49c` invoke the
   nonnull target with actor in r3 using mtctr/bctrl. The authenticated config
   target is **`800715f8`**. Its unimplemented reached call must refuse after
   preserving earlier effects and the phase increment. Do not null this cell
   to produce a successful test.
8. `ff4a0/ff4a4` unconditionally call **`8020bb14(current motion38)`** on every
   continuing path: nonpositive state, a separately labeled synthetic null
   callback, or a successfully returned real callback. A callback may change
   motion before this point. A refused callback has not reached magnitude.
9. `ff4a8` loads threshold3, and `ff4ac` performs ordered `fcmpo f1,f0`.
   `ff4b0` skips the effect unless the comparison is greater. Only then do
   `ff4b4/ff4b8` call **`800b22f4(actor)`**. Do not turn this into `>=3`, skip
   magnitude on an inactive authored state, or assume the effect returns.
10. `ff4bc..ff4d0` restore the saved registers and stack, then return.

## Numerical and execution boundaries

The magnitude helper is **already independently authenticated** by
[terrain-orientation evidence](terrain-orientation-evidence-2026-11-13.md):
`8020bb14/68`, SHA-256
`492e3d053ee6336c226ad94d8947492f358b1941ca2292029efea8a6d4d382bb`.
It is not reread here. That source proves a zero-square return and the exact
paired multiply/fused-add/sum, reciprocal-square-root estimate, and refinement
tree. It does **not** establish a general exact numerical implementation from
the function name or the availability of a host square root.

The existing private signed-axis domain is restricted to magnitudes
`{0.5,1,2,4,8}` under its stated finite/FPSCR/GQR assumptions. Even motion1
decays to approximately .95 here and leaves that domain. Do not substitute
`Math.sqrt`, `Math.hypot`, `1/Math.sqrt`, or unrelated primary-sine estimate
fixtures. A genuinely reached zero squared norm may use the separately
evidenced zero path; manufacturing position, history, or motion to create that
case would not establish progress through the actual state.

For unsupported nonzero numerical inputs, retain the preceding stream, aim,
motion, ground, and reached phase/callback effects and report the precise
`8020bb14` boundary. The real callback `715f8` and conditional effect `b22f4`
remain separate boundaries. These source requirements do not themselves prove
that an earlier full-frame lifecycle reaches this phase; earlier cues and
handlers still have their own source gates. This checkpoint makes no runtime,
collision, projectile, clone, or playable-route claim.

## Verification

From `research/tools/matching-decomp`, with installed Python and no downloads:

```sh
PYTHONDONTWRITEBYTECODE=1 python -m unittest -v test_archived_phase1_entry_evidence.py
PYTHONDONTWRITEBYTECODE=1 python -m unittest -v \
  test_archived_phase1_entry_evidence.py test_archived_constants.py \
  test_archived_command_evidence.py test_archived_actor_normal_evidence.py \
  test_archived_double_action_evidence.py test_archived_terrain_orientation_evidence.py \
  test_source_contracts.py
PYTHONDONTWRITEBYTECODE=1 python read_archived_phase1_entry_evidence.py \
  '../../decomp/GotchaForce.rep.before_force_create/idata/00/~00000000.db/db.3.gbf'
```

Use `db.4.gbf` for the second reader run. The sole argument is a known snapshot
path; the CLI rejects selection, pointer, and raw-dump options.

Results: **18 focused tests passed**, including four optional archive tests;
the focused/shared/source-contract command passed **99 tests**. With only
snapshot availability mocked absent during import, the same suite passes its
14 synthetic tests and skips exactly four archive tests. No input is fetched
and no on-disk snapshot is moved or modified.

Coverage includes:

- Frozen independent semantic operands for all47 instructions, a separate PPC
  inverse encoder, exact188-byte reconstructed hash, and all1504 single-bit
  instruction perturbations either refused or decoded with changed operands
  that independently re-encode to the perturbed word.
- Every bit of all200 selected bytes: **1600 mutations** all refuse before
  interpretation. Three numeric data fixtures are independently packed.
- Exact four-read inventory, mapping identities/types, complete physical
  provenance, both snapshots, and no raw instruction-word output.
- Wrong/spoofed whole hashes, schema failures, wrong/duplicate/missing maps,
  bad roots/offsets/lengths/types, duplicate selections, truncated or oversized
  payloads, cell/constant semantic disagreement, reserved opcode bits,
  incomplete decode, bad terminal return, and branches outside the fixed body.
- Stream mask15 and aimc1, motion-in-place scale/add without subtraction,
  signed state load after ground, phase store before callback load, real
  nonnull callback, unconditional later magnitude, and strictly greater
  threshold/effect order as explicit source contracts.

Repository-wide contributor/docs gates and runtime acceptance belong to the
parent integration checkpoint; the focused result is not a substitute for them.
