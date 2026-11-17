# Actor rotation damping: bounded archived inputs

## Result and limits

Both existing authenticated snapshots agree on four floating-point constants,
one independent eight-byte descriptor window, and every operand in the two
previously selected code spans. The newly bounded inputs support the real
rotation branch of `80059f5c`; they do not turn that branch into a no-op.

- `804373c4` is **`3dccccd0`**, or `0.10000002384185791`. It is not ordinary
  `0.1f`, whose bits would be `3dcccccd`.
- The coefficient calculation uses a single `fsubs` followed by **single fused
  `fmadds`**. Each rotation uses a separate `fsubs`, `fmuls`, and truncating
  `fctiwz` before a low-16-bit store.
- The fixed descriptor window `8033b028..8033b030` has signed bytes
  `[12, 2, 7, 11, -1, -1, -1, -1]`. The source visits positions 0 through 4,
  processing the first four indices and stopping at the first `-1`.
- The sentinel exits the list loop, not the function. Signed16 actor fields
  `18da`, `18dc`, and `18de` are still processed in order.
- Source list indices are signed and processed in order without deduplication.
  Each loop iteration reloads actor `4b0`. The fixed eight-byte selection is
  **not proof of a general descriptor allocation extent**.

This is archived ProgramDB static evidence, not unchanged original-DOL identity,
live actor ownership, captured processor state, retail parity, or playable-game
proof. The Double constructor's descriptor producer does not establish a fully
initialized browser actor. A runtime implementation must preserve explicit
actor ownership, memory availability, instruction ordering, and its declared
numeric domain rather than infer missing data from these constants.

Artifacts:
[`read_archived_actor_rotation_evidence.py`](../tools/matching-decomp/read_archived_actor_rotation_evidence.py)
and
[`test_archived_actor_rotation_evidence.py`](../tools/matching-decomp/test_archived_actor_rotation_evidence.py).
The new reader reuses the unchanged normal reader's fixed span authentication
and strict decoder. Neither shared readers nor their allowlists are extended.
There is no address, width, pointer-following, raw-output or execution CLI. No
original or archived instructions are executed and no binary payload is saved.

## Selection plan and authentication

The source instruction schedule and exact proposed data selections were
reported before their first new payload reads. The independent literals are:

| Selection | Width | Basis |
| --- | --- | --- |
| `80059f5c..8005a144` | 488 bytes / 122 instructions | Already authenticated complete postcallback span in the normal reader |
| `8006f60c..8006f708` | 252 bytes / 63 instructions | Already authenticated Double constructor span in the normal reader |
| `804373c0` | 4 bytes | Source C constant name and authenticated load at `80059fc8` |
| `804373c4` | 4 bytes | Source C constant name and authenticated load at `80059fbc` |
| `804373c8` | 4 bytes | Source C constant name and authenticated load at `80059fac` |
| `804373d0` | 8 bytes | Source C bias name and authenticated loads at `80059fcc` / `8005a094` |
| `8033b028` | 8 bytes | Independently bounded descriptor selection, not a read selected by a pointer value |

Source C is `research/decomp/ghidra-export/chunk_0007.c`, lines 2655–2707.
The neighboring C entry starts at line 2711. The code span ends with its sole
`blr` at `8005a140`, and all non-call branch targets stay within the span.
The C expression alone cannot establish the floating-point fusion or access
schedule; the strict instruction decoding does. See the
[normal actor evidence](actor-normal-lifecycle-evidence-2026-11-14.md) for the
existing span extent and constructor evidence.

Only the two existing local snapshots under
`GotchaForce.rep.before_force_create/idata/00/~00000000.db/` were used:

- `db.3.gbf`: SHA-256
  `7b50dd2d2e17b4bfcc89a64cde27010247d0cbf0f48bd5c059f50275f40458d0`.
- `db.4.gbf`: SHA-256
  `1f86813d91ea8e2c4564f96622ec42555e1dba2c78aa81ad654e892140d019f8`.

Unchanged `read_archived_constants.inspect` checks the actual complete file
digest, exact schemas, `boot.dol` program name, language
`PowerPC:BE:32:Gekko_Broadway`, Ghidra creation version `12.1.2`, executable
hash metadata and property type, empty File Bytes, address maps, entire data5
hash and established controls before the new selections. The executable SHA
metadata is
`21454a8880c6254616662710d6ec626e43d853999da2cdfad700030960a94836`;
it is import metadata, not independent original executable authentication.
File Bytes has version 0, root -1 and count 0. Image offset is `80000000`,
block size 16384 and master root 1.

Unchanged `read_archived_command_evidence.mappings` checks all-block overlap,
encoded addresses, identities, lengths and subblocks. Before any selection,
the new reader also requires exact typed mappings derived from those rows:

| Mapping | Range | Block / subblock | Length | Chain root |
| --- | --- | --- | --- | --- |
| `MAIN_.text1` | `800055e0..802b0160` | 1 / 1 | 2796416 | 21 |
| `MAIN_.data3` | `802bae60..803af120` | 5 / 5 | 1000128 | 199 |
| `MAIN_.data5` | `80436a20..8043d500` | 7 / 7 | 27360 | 263 |

All require subblock type 2, starting offset 0 and source offset 0. Complete
data5 SHA-256 is
`989c794b17fc95de6e57810f5c89db23d585c85a15faafc994d9a5bd9a0e61b4`.
Each new data read requires the exact independent address/width, exact mapping,
bounds and returned width; constants must match their exact bit patterns and
the descriptor must match its digest and signed values. Code spans retain
their prior complete digest checks and strict decoding of every instruction.

## Constants, r2 basis and physical traces

| Address | Type | Bits | Exact value | SHA-256 |
| --- | --- | --- | --- | --- |
| `804373c0` | f32 | `3f666666` | 0.89999997615814208984375 | `df62b97a90ebc75cc2c9bcbd4cbbaf8985bf0d1e7ae111c40d8df86df760b4de` |
| `804373c4` | f32 | `3dccccd0` | 0.10000002384185791015625 | `8e906b2c25daa46ef8d675b5c7c6c5bccb0017130d89903a05f71d09124fe7e9` |
| `804373c8` | f32 | `3f800000` | 1 | `de620abd6d3615746360c1d15ce3a56291236d37424124054a49d25e947ffc4d` |
| `804373d0` | f64 | `4330000080000000` | 4503601774854144 = 2^52 + 2^31 | `07af8387624cf8f36152797d2f561246f21237d1d22b5c13006eacfa6f475e43` |

The helper's previously recorded SDA2 basis is `r2 = 8043ea20`, sourced from
`docs/static-recompilation-spike.md:178`. The authenticated displacements give:

- `8043ea20 - 30304 = 804373c0`.
- `8043ea20 - 30300 = 804373c4`.
- `8043ea20 - 30296 = 804373c8`.
- `8043ea20 - 30288 = 804373d0`.

This establishes the arithmetic relation to the recorded r2, not a newly
authenticated startup instruction span or a live r2 capture. No startup span
was added. The source C names agree with those addresses.

The descriptor window SHA-256 is
`65fc8a2905ebfd7f8fbe4a7f74fed48be279cecf265ffba74f2414edd840e538`.
Code hashes remain `68a4b07dfea21671d8a803518f84c3a9935569931681b6116d827d7078ec3f59`
for `80059f5c/488` and
`201ead69a9e7e0cb04851db5f7498352ebdf5cbecc88be4486e68e2122e3e962`
for `8006f60c/252`.

All selections have one physical span in each snapshot and identical traces.
Offsets and widths below are decimal; all spans are obfuscated in the archive.

| Address | Root / data buffer | Chain offset | Data offset | Physical offset | Width |
| --- | --- | --- | --- | --- | --- |
| `80059f5c` | 21 / 43 | 346492 | 2554 | 723456 | 488 |
| `8006f60c` | 21 / 48 | 434220 | 8392 | 811214 | 252 |
| `804373c0` | 263 / 264 | 2464 | 2464 | 4344230 | 4 |
| `804373c4` | 263 / 264 | 2468 | 2468 | 4344234 | 4 |
| `804373c8` | 263 / 264 | 2472 | 2472 | 4344238 | 4 |
| `804373d0` | 263 / 264 | 2480 | 2480 | 4344246 | 8 |
| `8033b028` | 199 / 232 | 524744 | 648 | 3818126 | 8 |

## Exact source order

The preexisting flag, cue and movement gates remain in force. Flags masked by
`81000003` take the separately documented flagged path. Unequal signed cue
bytes `5e4` and `5e5` first call unselected helper `8006a6fc` at `80059f9c`.
Movement byte `661 == 10` returns only after that cue boundary. Nothing in this
new evidence supplies the unknown helper or makes a later rotation path legal
when an earlier boundary remains unsupported.

### Coefficient

1. `80059fac`: load f32 `c8` into f1.
2. `80059fb0`: set r0 to 8; `80059fb4`: load actor f32 `1dc8` into f0;
   `80059fb8`: set list position r5 to 0.
3. `80059fbc`: load f32 `c4` into f3; `80059fc0`: set r3 to `43300000`.
4. `80059fc4`: single `fsubs f2,f1,f0`.
5. `80059fc8`: load f32 `c0` into f0; `80059fcc`: load f64 bias `d0` into f1.
6. `80059fd0`: single fused `fmadds f2,f3,f2,f0`; `80059fd4`: CTR receives 8.

With a separately declared nearest-even numeric model, the intended expression
is a binary32-rounded subtraction followed by one fused binary32-rounded
multiply/add using the exact constants above. It is not a multiply rounded to
binary32 followed by a separately rounded addition, and it is not computed
using decimal `0.1`. Captured FPSCR state is absent; an implementation must not
claim that its chosen numeric model proves all processor modes or exceptional
inputs.

### List loop

`80059fd8` reloads actor `4b0` on each iteration. `80059fdc` adds `b0` to the
current list position; `80059fe0` loads that byte; `80059fe4` sign-extends it.
`80059fe8` compares it with `-1`; equality at `80059fec` branches to `8005a084`.
No list-position increment, rotation access or CTR decrement occurs on that
sentinel branch.

For a non-sentinel signed index, `80059ff0` multiplies by 6. `80059ff4` writes
the double-construction high word at stack+8; `80059ff8` increments list
position; `80059ffc` writes the high word at stack+24. `8005a000` forms
`actor + signed_index * 6` in r4. `8005a004` loads signed16 `18d4(r4)`, and
`8005a008` supplies the third conversion high word at stack+40.

Every component then follows this schedule, without batching loads or stores:

| Component | Signed16 load | `xoris` / low stack store / `lfd` | `fsubs` / `fmuls` / `fctiwz` | `stfd` / low32 load / low16 store |
| --- | --- | --- | --- | --- |
| `18d4 + 6*index` | `8005a004` | `8005a00c / 8005a010 / 8005a014` | `8005a018 / 8005a01c / 8005a020` | `8005a024 / 8005a028 / 8005a02c` |
| `18d6 + 6*index` | `8005a030` | `8005a034 / 8005a038 / 8005a03c` | `8005a040 / 8005a044 / 8005a048` | `8005a04c / 8005a050 / 8005a054` |
| `18d8 + 6*index` | `8005a058` | `8005a05c / 8005a060 / 8005a064` | `8005a068 / 8005a06c / 8005a070` | `8005a074 / 8005a078 / 8005a07c` |

The high word `43300000` and `xoris 8000` on the sign-extended integer construct
the biased double. Subtracting authenticated `d0` recovers the signed integer
with a single-precision result. All signed16 integers are exactly representable
in binary32. The separate single multiply uses the previously computed factor;
`fctiwz` truncates toward zero. `stfd` plus a load of the low word then feeds
`sth`, which stores low16 rather than saturating signed16. Exceptional or
out-of-range float-to-int behavior must be explicitly bounded by a runtime
implementation; it is not established from synthetic numeric examples.

`8005a080` decrements CTR and branches to `80059fd8` while nonzero. Thus at most
eight entries are read without a sentinel. There is no deduplication, unsigned
reinterpretation, index/count validation or table search in this loop. Other
negative signed indices are not `-1` and proceed in the source; unsupported
memory for them must remain unsupported rather than be silently skipped.

### Trailing triple

The sentinel branch and exhausted-loop path both reach `8005a084`, which first
loads actor signed16 `18da`. `8005a088` rebuilds the high word; `8005a08c` stores
it at stack+48; `8005a090` xors the sign bit; **only then** `8005a094` reloads
the static double bias. Stack stores at `8005a098`, `8005a0a0`, and `8005a0a8`
prepare the three conversions. The first trailing `lfd` is `8005a09c` and its
single subtraction is `8005a0a4`.

| Field | Signed16 load | `fsubs` / `fmuls` / `fctiwz` | Low16 store |
| --- | --- | --- | --- |
| `18da` | `8005a084` | `8005a0a4 / 8005a0ac / 8005a0b0` | `8005a0bc` |
| `18dc` | `8005a0c0` | `8005a0d0 / 8005a0d4 / 8005a0d8` | `8005a0e4` |
| `18de` | `8005a0e8` | `8005a0f8 / 8005a0fc / 8005a100` | `8005a10c` |

The last two axes use the same ordered sign-bit conversion, stack transfer,
separate arithmetic and truncation sequence. `8005a110` branches to the return
epilogue `8005a130`. Even an immediate first list sentinel must not suppress
these three stores. Since `18d4 + 6 == 18da`, a list entry of index 1 processes
the same triple once in the loop and again here. Repeated list entries likewise
read the already-updated component and apply another conversion/store cycle.

## Descriptor provenance and bounded domain

The already authenticated constructor `8006f60c` forms `8033af78` with
`addis r9,0,-32716` at `8006f6a8` and `addi r0,r9,-20616` at `8006f6d4`.
`8006f6e0` stores that address to actor `4b0`. The new selection is the separate
literal `8033b028/8`, whose address equals `8033af78 + b0`; no returned pointer
determines the read.

The first four source indices map to actor offsets as follows, then the source
reads a sentinel at descriptor position 4:

| List position | Signed index | Actor component offsets |
| --- | --- | --- |
| 0 | 12 | `191c / 191e / 1920` |
| 1 | 2 | `18e0 / 18e2 / 18e4` |
| 2 | 7 | `18fe / 1900 / 1902` |
| 3 | 11 | `1916 / 1918 / 191a` |

The remaining three selected bytes are `-1` but are not read after the first
sentinel during an ordinary unmodified traversal. This selection neither
authorizes reading other descriptor data nor proves all actors use this list.
Source behavior for eight entries, duplicate indices, index 1 overlap or other
signed indices must be distinguished from this particular static list.

## Verification

`python research/tools/matching-decomp/test_archived_actor_rotation_evidence.py -v`
passes **18 tests**, including both local snapshots. Tests check full digest
authentication before selections; all mappings before selections; exact typed
address/width gates; altered mappings, widths, values, hashes and unsupported
instructions; unusual coefficient bits; signed window interpretation; no
pointer following; absent arbitrary-selection/raw/execution CLI; both full
instruction spans; the constructor producer; and every instruction in the
rotation schedule `80059fac..8005a110`.

`python -m unittest discover -s research/tools/matching-decomp -p 'test_archived_actor_*evidence.py' -v`
passes **175 tests**, including the unchanged actor evidence suites and the new
rotation suite. `git diff --check` is clean. These are focused research checks,
not the repository's contributor or documentation build aggregates.

These checks authenticate the static inputs and derived schedule. They do not
execute original code or by themselves verify a browser runtime, a matching
recompile, a retail oracle, a complete constructor, or playable integration.
