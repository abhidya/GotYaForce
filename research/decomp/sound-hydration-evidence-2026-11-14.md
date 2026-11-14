# Ordinary Double sound hydration evidence

Date: 2026-11-14. Static archived ProgramDB evidence, not original-DOL identity,
execution, hardware parity, production integration or playable-clone proof.

The new fixed reader is
[`read_archived_sound_hydration_evidence.py`](../tools/matching-decomp/read_archived_sound_hydration_evidence.py).
Its tests are
[`test_archived_sound_hydration_evidence.py`](../tools/matching-decomp/test_archived_sound_hydration_evidence.py).
No original binaries or assets are emitted or copied into source. The reader
outputs numeric fields, complete instruction operands, hashes and physical
provenance. It does not execute any source instruction or constructor.

## Results that change the composition

- Actual Double descriptor `8033af78` byte `+2` is **3**, so ordinary requested
  mask `f` reaches parts **0 and 1**, not the historical fixture's lone part1.
- Initialized rows in both banks have `auxiliary37=ff`. Ordinary ground metadata
  changes current-bank parts0/1 to **22/23**. Air changes them to **25/ff**.
  Parts2/3 remain `ff` at the explicitly supplied initialized-state boundary.
- Ground part0's complete list is frame22, window1, mode0, sound9. Ground part1's
  complete list has frame35 and frame46, both window1, mode1, sound103.
  Air part0's complete list is frame20, window1, mode0, sound9. Air part1 skips.
- Descriptor fallback bytes `+be/+bf` are **0/1**, reached by both ordinary
  part0 descriptors' `ff/ff` fallback selectors.
- With actual mode1/start0 setup, the first frame holds animation frame0.
  These positive-frame, window1 events do not yet cross their thresholds.
  A genuine scan may therefore return with **zero sound effects** without a
  null sound table or invented all-minus-one active selectors.

The last point is conditional on real setup/clock execution. This reader does
not execute the actor frame. It establishes source inputs for that separate
composition and does not supply original model/DAT assets or pose topology.

## Independently fixed selections

All addresses and widths were selected before their corresponding archive
reads. The first pass fixed the initializer, active-mask byte, group4 cell,
two independently documented descriptors and a bounded sound inspection
window. A second manually scoped selection added the two literal slot cells
after the first group's displacement was known; independently recorded
descriptor starts predicted their expected values. A third fixed selection
added the two fallback bytes named by `4d244`. The final reader contains only
literal selections. It finishes every selected data read before interpreting
any selector; no returned pointer or index chooses an archive read.

| Selection | Address / width | Independent address and extent basis |
| --- | --- | --- |
| Initializer | `8004bb14` / 756 | Adjacent named C markers `chunk_0006.c:1237` and `:1393`, `_index.tsv:919/920`; end `8004be08` exclusive. No retail map row for `4bb14`; next named `4be08` appears at map line627, size`b0`. Terminal return later authenticated at`4be04`. |
| Double active mask | `8033af7a` / 1 | Already authenticated constructor forms Double descriptor`8033af78` at`6f6d4` and stores actor4b0 at`6f6e0`; initializer reads descriptor byte+2 for579. |
| Double fallback defaults | `8033b036` / 2 | Same independently known Double descriptor plus fixed byte offsets`be/bf` in existing authenticated`4d244` and source metadata implementation. |
| Family group4 cell | `802bd788` / 2 | Independently named family metadata bank`802bd780`, fixed group4, signed16 group-index operation in`4d1f4`. |
| Group4 slots0/1 | `802bd8a4` / 2; `802bd8a6` / 2 | Separately fixed after group cell gave`0124`; bank+`0124`=`802bd8a4`. Known descriptor starts require signed offsets`04bc/04d0`; these expectations were verified, not followed dynamically. |
| Ground descriptor | `802bdd60` / 20 | Independently recorded metadata4/0 start in [Double X evidence](double-ninja-source-x-2026-11-12.md); 0x14-byte Ninja descriptor records explicitly documented in [metadata format](title-intro-residuals-decode-2026-07-06.md), section1.3. |
| Air descriptor | `802bdd74` / 20 | Independently recorded metadata4/1 start, same documented stride. |
| Sound inspection window | `802d3ca0` / 296 | Independently documented sound base, corroborated by authenticated constructor cell`802d3b48`; endpoint is independently named Normal Ninja descriptor`802d3dc8` in metadata format section1.2. This is an adjacent-object-bounded inspection window, **not proof of global sound-table extent**. |

The Normal descriptor endpoint is only a window bound. It is **not** the
Double descriptor. Neither unrelated command table`4ec=8033b180` nor the
Normal command table`802d4148` is used as a sound bound.

Prior constructor facts are in
[normal lifecycle evidence](actor-normal-lifecycle-evidence-2026-11-14.md),
and the independently authenticated nonnull sound pointer is in
[frame suffix evidence](frame-suffix-evidence-2026-11-14.md).
Existing `4d1f4/4d244` instruction witnesses remain unchanged in
`read_archived_setup_metadata_evidence.py`.

## Authentication and exact hashes

Both existing snapshots agree on every selection, decoded field, instruction
and physical trace:

- `db.3.gbf`: SHA-256
  `7b50dd2d2e17b4bfcc89a64cde27010247d0cbf0f48bd5c059f50275f40458d0`.
- `db.4.gbf`: SHA-256
  `1f86813d91ea8e2c4564f96622ec42555e1dba2c78aa81ad654e892140d019f8`.

Unchanged `read_archived_constants.inspect` verifies full-file hashes, exact
schemas, program name, language`PowerPC:BE:32:Gekko_Broadway`, creation version
`12.1.2`, executable SHA metadata/type, empty File Bytes, address maps, complete
data5 digest and existing controls before selection. The imported executable
SHA metadata is not proof of unchanged original bytes. Unchanged
`read_archived_command_evidence.mappings` checks all-block overlap and exact
text1/data3/data5 identities, lengths and subblocks. The new reader separately
derives and compares its exact text1/data3 tuples:

- Text1 `800055e0..802b0160`, length2796416, block/subblock1, root21.
- Data3 `802bae60..803af120`, length1000128, block/subblock5, root199.

Each new read requires an exact integer address/width allowlist match, exact
mapping, bounds, returned width and fixed SHA-256. No common reader's allowlist
is widened. Missing snapshots are never fetched by tests.

| Address / width | SHA-256 |
| --- | --- |
| `8004bb14` / 756 | `63f0151abf89a6275e77bc14f1b6e842d74cc6b5bc2d7d27430690d5dad89c8a` |
| `8033af7a` / 1 | `084fed08b978af4d7d196a7446a86b58009e636b611db16211b65a9aadff29c5` |
| `8033b036` / 2 | `b413f47d13ee2fe6c845b2ee141af81de858df4ec549a58b7970bb96645bc8d2` |
| `802bd788` / 2 | `3f2d2a889d22530bd1abdc40ff1cbb23ca53ae3f1983e58c70d46a15c120e780` |
| `802bd8a4` / 2 | `1585c80c682bcc8c6d1e1e2436faaf76fa8cd2f447ad91b0be1fcdb59d9cb9d5` |
| `802bd8a6` / 2 | `b4eb2237d68a6a5c7b9da1353d74d901ea68dcf5727ae97a1554e5aaa0de0531` |
| `802bdd60` / 20 | `2301ecf31b1bfc0d124f0289f501ca6dc321019541be202a693e709c6134cd3a` |
| `802bdd74` / 20 | `99ee2f74daaae93c627e24d4955b95ba4c54dcc025a34828b47fa432d2d586c1` |
| `802d3ca0` / 296 | `fe09942ed6f070ce7cc9f3534d17a0e2497927e10d18de0a0aa2d2a9cf988a82` |

## Initializer producer and all four rows

All189 initializer instructions and operands decode using existing explicit
forms. No new opcode decoder was needed. A frozen expected schedule is
independently inverse-encoded to the exact756-byte hash in the tests, including
every condition, register, displacement and paired-load/store field.

Relevant order:

1. `4bcd0` loads actor4b0; `4bcd4` loads descriptor+2; `4bcd8` stores579.
2. The two-bank loop starts at`4bd14`. Each four-part iteration forms
   `actor + bank*100 + part*40 + 1ad4` and calls `8000540c` with value0,
   width40 at`4bd34`. The map names this target`gnt4-memset`.
3. `4bd38` stores bank index to row+33; `4bd48` stores part index to+34;
   `4bd4c` stores explicit`ff` to+37, after the clear call.
4. Part increments at`4bd54`; compare4 at`4bd5c`; stride40 at`4bd60`;
   inner branch`4bd64`. Bank increments at`4bd68`, stride100 at`4bd6c`,
   compare2 at`4bd70`, outer branch`4bd74`.

This supports an **explicit decoded initialized-state boundary**. The reader
does not execute the initializer or its memset/matrix/global dependencies,
and does not assert that an arbitrary later actor still has this state.
`4beb8` intersects requested mask with signed579; actual mask3 means only
parts0/1 reach setup and`4d244`. The latter writes selected descriptor+08/+10
into their respective metadata owners. It does not copy descriptor+18/+20
into inactive parts2/3.

The legacy sound extractor in`gen-melee-anim-kinds.mjs` scans all four descriptor
sections without respecting this actor mask and dedupes sound tuples. Its
apparent part2 events can come from adjacent20-byte records. It is not a
complete row/termination witness and must not hydrate these four source rows.

## Exact selected metadata and reached sound records

All descriptor bytes are represented by numeric fields in the reader output.
Both have scale`ff` and reserved bytes+1/+2/+3/+b equal0.

| Descriptor | Part | selector2a / selector2b | flags / rewind | auxiliary37 | Remaining bytes |
| --- | --- | --- | --- | --- | --- |
| `802bdd60` | 0 | 4 / 0 | 1 / 0 | 22 | +9/+a=`ff/ff`; fallback defaults0/1 |
| `802bdd60` | 1 | 4 / 0 | 1 / 0 | 23 | +11/+12/+13=`0/5/1` |
| `802bdd74` | 0 | 4 / 1 | 1 / 0 | 25 | +9/+a=`ff/ff`; fallback defaults0/1 |
| `802bdd74` | 1 | 4 / 1 | 1 / 0 | `ff` | +11/+12/+13=`3/5/0` |

Offsets in the remaining-byte column are hexadecimal. Sound indices below
are decimal. Eight-byte layout is`u16 frame, u8 windowFlag, u8 mode, u16 soundId,
u8 continuation, u8 pad`, big-endian. Only these reached records are decoded
or emitted from the already selected bounded inspection window:

| Index | Address | frame / window / mode / soundId / continuation / pad | SHA-256 |
| --- | --- | --- | --- |
| 22 | `802d3d50` | 22 / 1 / 0 / 9 / 255 / 0 | `6efdec15782a31746c3750cbf0bd50b6c17ea71e5bf299d03f386cdeebaa9c0f` |
| 23 | `802d3d58` | 35 / 1 / 1 / 103 / 0 / 0 | `8eb4d90e59ba9ff29fdf22542acbf49bc9e5117375ca8505c6e4bb6eafbbae8b` |
| 24 | `802d3d60` | 46 / 1 / 1 / 103 / 255 / 0 | `7b9babbe7055a9f627745df830a58a541037d4fba928f28e89e68eb88e4fee38` |
| 25 | `802d3d68` | 20 / 1 / 0 / 9 / 255 / 0 | `d348ac1a16d5d1d4ae6c0dcc79835ebe3e0c7a447945dadb9ba7fca05638878a` |

Ground lists terminate after indices22 and24. Air part0 terminates at25 and
part1 returns on signed index−1. No list escapes the predeclared window. This
establishes closure of these three reached lists only, not every list in the
sound table. No helper audio dispatch is implemented by this evidence reader.

Canonical integration must retain the actual actor's sound table owner,
metadata auxiliary37 owners, dispatch elapsed/previous clocks and feedback
frame/duration owners. Narrow byte-window hydration must check read coverage
so unselected prefixes or gaps cannot become zero-filled source evidence.
The four reached sound rows span table offsets176..208; other bytes are not
emitted by this reader. Descriptor bank selections likewise require coverage
for group cell, slot cells and descriptors instead of silent padding.

## Verification

Run from checkout root:

```sh
PYTHONDONTWRITEBYTECODE=1 python -m unittest discover -s research/tools/matching-decomp -p test_archived_sound_hydration_evidence.py -v
```

Tests cover the complete189-instruction schedule and inverse SHA, every
accepted single-bit instruction mutation's inverse, all descriptor bytes,
complete reached8-byte records, terminal current-record semantics, inactive
row initialization, exact active mask/fallbacks/lookup relations, missing and
malformed coverage, full authentication/schema/mapping failure ordering,
integer types, allowlists, width/hash failures, duplicate selections, arbitrary
CLI refusals and equality across both existing authenticated snapshots.
These tests do not replace separate runtime composition or browser acceptance.
