# Actor-tier lifecycle: fixed archived evidence

## Result and boundary

Both existing archived ProgramDB snapshots authenticate the complete
`8006817c..800681e4` tier-delta helper (**104 bytes, 26 instructions**), the
complete `8006826c..800682f8` row-refresh helper (**140 bytes, 35 instructions**),
two specifically selected pointer cells, and six independently fixed rows.
Every instruction is represented in order. Both snapshots produce identical
operands, selected data and physical traces.

The important runtime distinctions are:

- Delta helper `6817c` tests the signed byte at global pointee `1f` before
  reading actor tier `74a`. It adds the signed tier to the full 32-bit delta
  register, then signed-clamps the 32-bit result to `[-127,127]`. It stores
  `74a` before calling `6826c`. It does not read or write the tier accumulator
  or timer.
- Refresh `6826c` returns immediately for an initially null actor `4ac`.
  Otherwise it compares signed tier `74a` with signed upper `74d` first;
  lower `74c` is read only if the upper clamp was not selected. It stores
  the result into `74b` before any selector or row access.
- Refresh then **reloads** actor `4ac`, reads actor `74b`, and reads the
  retained reloaded descriptor's **unsigned** byte `a3`, in that order.
  There is no second null check. The row index is signed `74b`; the pointer
  selector is unsigned `a3`.
- Rows are transferred using **`lfs` / `stfs`**, sequentially to actor `b8`,
  `1dd0`, then `5f8`. The C export's `undefined4` rendering does not establish
  integer-copy or arbitrary-bit behavior. A later unavailable field cannot
  roll back earlier stores or justify eager validation of the whole row.

This is offline archived evidence, not original instruction execution,
unchanged original-DOL identity, live pointer ownership, production family
descriptor provenance, retail parity, or playable-game proof. Selected
finite float32 rows have exact bits. Live FPSCR, exceptions, denormal modes,
NaN payloads and arbitrary floating bit patterns are not established.

Artifacts:

- [Fixed reader](../tools/matching-decomp/read_archived_actor_tier_evidence.py)
- [Complete operand and fail-closed tests](../tools/matching-decomp/test_archived_actor_tier_evidence.py)
- [Existing gauge/scale caller evidence](actor-gauge-scale-evidence-2026-11-13.md)
- [Existing actor-rate consumer evidence](actor-rate-lifecycle-evidence-2026-11-14.md)

## Scope and authentication

The bounded plan selected both complete helper spans, pointer cells
`804339e0` and `804339e4`, and tiers **15, 16 and 17** at each of the separately
source-named bases `802dd5a0` and `802dd720`. That plan was recorded before new
archive payload reads. Unexpected pointer values fail; the reader never
follows a returned pointer to choose another address.

The shared readers and allowlists remain unchanged. The CLI accepts only an
existing snapshot path. There are no address, width, selector, tier,
pointer-following, raw-output or execution options. No new binary input,
original instruction execution, dependency installation, network request,
publication or retired port driver is involved.

| Function | C entry and next entry | Map size | Final decoded return |
| --- | --- | --- | --- |
| Delta helper | `chunk_0008.c:4410`, next `800681e4` | `0x68` | `800681e0` |
| Row refresh | `chunk_0008.c:4485`, next `800682f8` | `0x8c` | `800682f4` |

Both extents agree with the symbol-map sizes at
`research/symbols/GG4E-CSM-20220412.map:790,792`, C next entries, and final
decoded returns. Neither span includes padding or a neighboring function.

The unchanged `read_archived_constants.inspect` authenticates the actual full
snapshot SHA-256, exact schemas, executable metadata, big-endian Gekko/Broadway
language, address maps, empty File Bytes, complete data5 hash and existing
controls before any new selection. A supplied digest alone is not trusted.
The unchanged command mapping validator checks exact text1/data3/data5
identities and all-block overlap; this reader additionally checks data4's
unique block, exact address/length, and exact subblock fields.

Existing snapshots under
`GotchaForce.rep.before_force_create/idata/00/~00000000.db/`:

- `db.3.gbf`: `7b50dd2d2e17b4bfcc89a64cde27010247d0cbf0f48bd5c059f50275f40458d0`.
- `db.4.gbf`: `1f86813d91ea8e2c4564f96622ec42555e1dba2c78aa81ad654e892140d019f8`.

Program name is `boot.dol`, created with Ghidra `12.1.2`. Imported executable
SHA-256 metadata is
`21454a8880c6254616662710d6ec626e43d853999da2cdfad700030960a94836`.
This is archived metadata, not a newly acquired or hashed original executable.
File Bytes is version 0, root -1, count 0. Block size is 16384, master root 1,
image offset `80000000`. Full data5 SHA-256 remains
`989c794b17fc95de6e57810f5c89db23d585c85a15faafc994d9a5bd9a0e61b4`.

Relevant mappings, all subblock type 2, starting/source offsets zero:

| Block | Start | Length | Block/subblock key | Chain root |
| --- | --- | --- | --- | --- |
| MAIN_.text1 | `800055e0` | 2796416 | 1 | 21 |
| MAIN_.data3 | `802bae60` | 1000128 | 5 | 199 |
| MAIN_.data4 | `804335a0` | 11040 | 6 | 262 |

Span SHA-256 values:

- `8006817c`: `cc7a1791c3441a7767e2999ffe19791d625384942e34ec13b0ff5d0639063f2d`.
- `8006826c`: `b5984640399d2952aedfaa554a6459035788415792189757db695fe6c0b4a7bf`.

Fixed readers reject noninteger selectors/tiers/ranges, nonunique allowlist
matches, wrong roots, wrong mapping tuples, wrong widths, unaligned or
out-of-block selections, changed instruction hashes and changed selected
data. The entire code span is hashed before any instruction decoding. An
unknown instruction fails the selection rather than disappearing. Reserved
comparison, sign-extension, indexed-load and link-register encodings fail.

## Exact pointer cells and selected row data

The literal address formed by `addis` at `682b8` and `addi` at `682c0` is
`804339e0`. The selector is shifted left two before the indexed word load.

| Unsigned selector | Fixed pointer cell | Authenticated target |
| --- | --- | --- |
| 0 | `804339e0` | `802dd5a0` |
| 1 | `804339e4` | `802dd720` |

These are actual authenticated cell values, not a guess from nearby symbols.
The row selections are independent fixed addresses, checked against the
expected metadata arithmetic `base + signedTier * 12`. No returned pointer
controls an archive read.

| Selector | Tier | Row address | Float32 bits, offsets 0 / 4 / 8 |
| --- | --- | --- | --- |
| 0 | 15 | `802dd654` | `3f4f5c29` / `3f800000` / `3f4f5c29` |
| 0 | 16 | `802dd660` | `3f800000` / `3f800000` / `3f800000` |
| 0 | 17 | `802dd66c` | `3fb33333` / `3f7ae148` / `3fb33333` |
| 1 | 15 | `802dd7d4` | `3f4f5c29` / `3f800000` / `3f4f5c29` |
| 1 | 16 | `802dd7e0` | `3f800000` / `3f800000` / `3f800000` |
| 1 | 17 | `802dd7ec` | `3f99999a` / `3f7ae148` / `3f99999a` |

Exact finite values:

- `3f4f5c29` = `0.8100000023841858`.
- `3f800000` = `1.0`.
- `3fb33333` = `1.399999976158142`.
- `3f99999a` = `1.2000000476837158`.
- `3f7ae148` = `0.9800000190734863`.

The row fields feed target model scale `b8`, animation-rate factor `1dd0`, and
velocity factor `5f8` respectively. The existing generator
`scripts/gen-param-tier-tables.mjs:33` rounds floats to six decimal places, so
its JSON is not exact-bit evidence for these values and is not used here.

That generator's old “33 rows” assertion is **not an allocation bound**.
Specifically, `802dd5a0 + 32 * 12 = 802dd720`, so its 33rd row reaches the next
source-named table base. This overlap does not prove a 32-row allocation
either. The present reader establishes only the six listed rows and two
listed cells. Every other tier and selector is unsupported by this evidence
selection, even if the source arithmetic could reach it.

## Ordered delta helper behavior

All actor, descriptor and pointee offsets below are hexadecimal.

1. Save stack and LR. Load the global pointer from the identity `80433934`,
   using the recorded `r13=8043b5a0` basis and displacement `-31852`.
   This basis is recorded in `docs/static-recompilation-spike.md:178-180`,
   not a live register capture. Neither this global value nor its pointee is
   selected by the new archive reader.
2. Read byte `1f` from that pointee, sign-extend with `extsb.`, and return if
   nonzero. No actor tier, descriptor or delta arithmetic occurs on this path.
3. Read actor `74a`, sign-extend it, then add the entire r4 delta using the
   32-bit `add` at `681a0`. There is no byte/short extension of r4 and no
   overflow trap. Signed comparisons consume the wrapped 32-bit result.
4. Compare with 127. Strict GT stores 127 to `74a`; otherwise compare with
   -127. Strict LT stores -127 (byte bits `81`) to `74a`; otherwise store
   the sum's low byte. Upper and lower comparisons retain their distinct
   encoded CR predicates (`BO=4 BI=1`, then `BO=4 BI=0`).
5. All three store paths call `8006826c` at `800681d0`, then restore LR/stack
   and return. The C signature is void. There is no source result assignment,
   no accumulator/timer update, and no success boolean to manufacture.

The existing gauge/scale caller's reached tier-expiry path can therefore use
this helper, with explicit source-owned global byte `1f`. If refresh later
fails, the completed `74a` write remains. A caller-side accumulator clear
after the call must not happen until this helper actually returns.

## Ordered refresh behavior and partial effects

1. Read actor `4ac` into r0. Unsigned-compare it with zero and execute
   conditional LR return (`BO=12 BI=2 BH=0 LK=0`) if equal. This early path
   reads neither tier nor limits and writes nothing.
2. Read `74a` into r6, then `74d` into r5. Sign-extend copies into r4 and r0
   and compare the signed tier against the signed upper limit. If tier is
   strictly greater, store the original upper byte to `74b` and skip lower.
3. Otherwise read `74c`, sign-extend it, and compare the retained tier with
   the signed lower limit. Strict LT stores the original lower byte to `74b`;
   otherwise store the original tier byte. This helper never changes `74a`.
   An inconsistent lower/upper pair has no separate validation in the source:
   preserve the upper-first branches instead of sorting or rejecting limits.
4. Reload actor `4ac` into r5 at `682b4`. Read actor `74b` at `682bc`. Read
   unsigned byte `a3` from that retained reloaded descriptor at `682c4`.
   There is no repeat null check, so an unavailable second pointer must not
   be changed into the initial null-return behavior. Nor may it erase `74b`.
5. Sign-extend the retained `74b`, shift the unsigned selector by two,
   multiply the signed tier by 12, load the selected pointer cell, then add
   the row offset. The descriptor selector does not get sign-extended.
6. `lfs row+0; stfs actor+b8` precedes `lfs row+4; stfs actor+1dd0`, which
   precedes `lfs row+8; stfs actor+5f8`. There are no floating arithmetic
   instructions and no eager three-word read. Unsupported selector/row
   resolution follows the `74b` store; unsupported later fields retain all
   earlier completed stores. Finish with `blr` at `682f4`.

## Constructor ownership context, not a guessed descriptor

The existing C export `chunk_0006.c:8266-8269`, within `80056180`, records
initial tier `74a=16`, upper `74d=descriptor4ac+a1`, lower
`74c=descriptor4ac+a2`, then a call to refresh. It subsequently initializes
scale fields using the resulting `b8`. This is useful field ownership and
caller context only. The new reader does **not** select constructor bytes,
does not implement a partial constructor, and does not claim those C lines
establish the exact constructor access schedule.

No live or production family page has been authenticated here. Selector and
limits in bounded composition must be explicitly hydrated onto their actual
parameter/actor owners; they are not inferred from the table pointers or
silently defaulted. Supporting rows 15/16/17 does not justify inventing
constructor limits 15/17, nor does a neutral row prove a family chooses it.

## Physical traces and reproduction

Both snapshots have the identical traces below. Storage is obfuscated;
offsets and lengths are decimal.

| Selection | Root/data buffer | Chain offset | Data offset | Physical offset | Length |
| --- | --- | --- | --- | --- | --- |
| Delta `8006817c` | 21 / 46 | 404380 | 11308 | 781362 | 104 |
| Refresh `8006826c` | 21 / 46 | 404620 | 11548 | 781602 | 140 |
| Cell `804339e0` | 262 / 262 | 1088 | 1088 | 4310090 | 4 |
| Cell `804339e4` | 262 / 262 | 1092 | 1092 | 4310094 | 4 |
| Row `802dd654` | 199 / 208 | 141300 | 10276 | 3434538 | 12 |
| Row `802dd660` | 199 / 208 | 141312 | 10288 | 3434550 | 12 |
| Row `802dd66c` | 199 / 208 | 141324 | 10300 | 3434562 | 12 |
| Row `802dd7d4` | 199 / 208 | 141684 | 10660 | 3434922 | 12 |
| Row `802dd7e0` | 199 / 208 | 141696 | 10672 | 3434934 | 12 |
| Row `802dd7ec` | 199 / 208 | 141708 | 10684 | 3434946 | 12 |

From repository root, using existing stdlib Python only:

```sh
python research/tools/matching-decomp/read_archived_actor_tier_evidence.py \
  'research/decomp/GotchaForce.rep.before_force_create/idata/00/~00000000.db/db.3.gbf'
python research/tools/matching-decomp/read_archived_actor_tier_evidence.py \
  'research/decomp/GotchaForce.rep.before_force_create/idata/00/~00000000.db/db.4.gbf'
PYTHONPATH=research/tools/matching-decomp python -m unittest \
  test_archived_actor_tier_evidence -v
```

All **18 focused tests pass**, with both local snapshots present and no skips.
Both CLI runs succeed. Tests cover every operand in both complete spans,
map/C/return extents, signed gates and clamps, full delta register use,
null-gate and reload ordering, unsigned selector versus signed row, sequential
floating transfers, exact data bits, and constructor C-only boundaries.
They also cover authentication/schema/map failure order, bounds and reserved
encodings, every selected instruction mutation, every pointer/row byte
mutation, unexpected pointer values, unsupported rows/selectors, and rejected
CLI expansion options. A combined constants, command, actor-status, actor-rate,
actor-ceiling, actor-tier and tick-prefix evidence run passes **117 tests**,
with no skips. Both new Python files compile; the three new files pass
whitespace checks. These are evidence-reader tests, not retail execution or
gameplay acceptance checks.

## Appendix: complete derived operands

All 61 instructions follow in source order. Numbers other than addresses are
decimal. Raw instruction words and executable byte ranges are not included.

```text
8006817c stwu rA=1 displacement=-16 rS=1
80068180 mflr rD=0
80068184 stw rA=1 displacement=20 rS=0
80068188 lwz rD=5 rA=13 displacement=-31852
8006818c lbz rD=0 rA=5 displacement=31
80068190 extsb rS=0 rA=0 Rc=1
80068194 bc BO=4 BI=2 LK=0 target=800681d4 AA=0
80068198 lbz rD=0 rA=3 displacement=1866
8006819c extsb rS=0 rA=0 Rc=0
800681a0 add rD=0 rA=0 rB=4 Rc=0
800681a4 cmpi BF=0 L=0 rA=0 immediate=127
800681a8 bc BO=4 BI=1 LK=0 target=800681b8 AA=0
800681ac addi rD=0 rA=0 immediate=127
800681b0 stb rS=0 rA=3 displacement=1866
800681b4 b target=800681d0 AA=0
800681b8 cmpi BF=0 L=0 rA=0 immediate=-127
800681bc bc BO=4 BI=0 LK=0 target=800681cc AA=0
800681c0 addi rD=0 rA=0 immediate=-127
800681c4 stb rS=0 rA=3 displacement=1866
800681c8 b target=800681d0 AA=0
800681cc stb rS=0 rA=3 displacement=1866
800681d0 bl target=8006826c AA=0
800681d4 lwz rD=0 rA=1 displacement=20
800681d8 mtlr rS=0
800681dc addi rD=1 rA=1 immediate=16
800681e0 blr
8006826c lwz rD=0 rA=3 displacement=1196
80068270 cmpli BF=0 L=0 rA=0 immediate=0
80068274 bclr BO=12 BI=2 BH=0 LK=0
80068278 lbz rD=6 rA=3 displacement=1866
8006827c lbz rD=5 rA=3 displacement=1869
80068280 extsb rS=6 rA=4 Rc=0
80068284 extsb rS=5 rA=0 Rc=0
80068288 cmp BF=0 L=0 rA=4 rB=0
8006828c bc BO=4 BI=1 LK=0 target=80068298 AA=0
80068290 stb rS=5 rA=3 displacement=1867
80068294 b target=800682b4 AA=0
80068298 lbz rD=5 rA=3 displacement=1868
8006829c extsb rS=5 rA=0 Rc=0
800682a0 cmp BF=0 L=0 rA=4 rB=0
800682a4 bc BO=4 BI=0 LK=0 target=800682b0 AA=0
800682a8 stb rS=5 rA=3 displacement=1867
800682ac b target=800682b4 AA=0
800682b0 stb rS=6 rA=3 displacement=1867
800682b4 lwz rD=5 rA=3 displacement=1196
800682b8 addis rD=4 rA=0 immediate=-32701
800682bc lbz rD=0 rA=3 displacement=1867
800682c0 addi rD=4 rA=4 immediate=14816
800682c4 lbz rD=5 rA=5 displacement=163
800682c8 extsb rS=0 rA=0 Rc=0
800682cc rlwinm rS=5 rA=5 SH=2 MB=0 ME=29 Rc=0
800682d0 mulli rD=0 rA=0 immediate=12
800682d4 lwzx rD=4 rA=4 rB=5
800682d8 add rD=4 rA=4 rB=0 Rc=0
800682dc lfs fD=0 rA=4 displacement=0
800682e0 stfs rA=3 displacement=184 fS=0
800682e4 lfs fD=0 rA=4 displacement=4
800682e8 stfs rA=3 displacement=7632 fS=0
800682ec lfs fD=0 rA=4 displacement=8
800682f0 stfs rA=3 displacement=1528 fS=0
800682f4 blr
```
