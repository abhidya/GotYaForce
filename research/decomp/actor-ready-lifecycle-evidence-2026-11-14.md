# Actor ready lifecycle: archived evidence

## Result and ceiling

The fixed reader authenticates **153 instructions in three complete functions**:
`8006a980` (76), `8006aab0` (21) and `8005a298` (56). Both already available
ProgramDB snapshots agree on every instruction operand, span digest and physical
trace. This includes all stack instructions and the floating-point branch that
remains unsupported by the bounded runtime slice. No selected instruction is
omitted, and no new fixed data value is read or interpreted.

This is **offline archived evidence**, not original-DOL identity, execution of
retail code, live actor or pointer ownership, production integration, retail
parity, or playable-game proof. The nonzero-`4a0` branch in `8006a980` still calls
unsupported `80066198`. The caller of `8006aab0` still reaches `80176ec0`.
`8005a298` still contains the external `80010514` boundary. An authenticated call
site is not evidence for the callee's behavior.

Artifacts:

- [Fixed reader](../tools/matching-decomp/read_archived_ready_lifecycle_evidence.py)
- [Complete operand and guard tests](../tools/matching-decomp/test_archived_ready_lifecycle_evidence.py)
- [Earlier actor-control evidence](actor-control-effect-evidence-2026-11-14.md),
  which authenticates `8005a190` and the readiness predicates without widening
  this reader.

The CLI accepts one existing snapshot path only. It has no address, width,
index, raw-output, execution or pointer-following options. Shared readers and
shared allowlists are unchanged. No new dependency, archive input, original
executable execution, network access, installation or driver operation is used.

## Complete extents, not symbol-map claims

| Entry | End exclusive | Width | Instructions | Extent evidence |
| --- | --- | --- | --- | --- |
| `8006a980` | `8006aab0` | `0x130` | 76 | C `chunk_0009.c:991-1035`; final archived `blr` at `8006aaac`; both entries absent from symbol map |
| `8006aab0` | `8006ab04` | `0x54` | 21 | C `chunk_0009.c:1035-1056`; final archived `blr` at `8006ab00`; entry absent from map, next entry is map line 830 |
| `8005a298` | `8005a378` | `0xe0` | 56 | C `chunk_0007.c:2772-2815`; final archived `blr` at `8005a374`; both entries absent from map |

The C exports are under `research/decomp/ghidra-export/`. The map is
`research/symbols/GG4E-CSM-20220412.map`. Its `8006ab04` entry has size `0x98`,
but that proves no size for the preceding function. These selected extents use
C next-entry boundaries and authenticated final-return instructions; none is
called map-proven. Tests check the actual next C entry, final decoded `blr`,
and absence of the selected entry from the map.

## Authentication and storage

Existing local snapshot directory:
`GotchaForce.rep.before_force_create/idata/00/~00000000.db/`.

- `db.3.gbf`: SHA-256
  `7b50dd2d2e17b4bfcc89a64cde27010247d0cbf0f48bd5c059f50275f40458d0`.
- `db.4.gbf`: SHA-256
  `1f86813d91ea8e2c4564f96622ec42555e1dba2c78aa81ad654e892140d019f8`.

Before any new selected span is read, unchanged
`read_archived_constants.inspect` verifies the real whole-snapshot SHA-256
against its allowlist, exact schemas, executable metadata, big-endian
Gekko/Broadway language, address maps, empty File Bytes, the full data5 digest
and existing controls. A supplied digest alone cannot authenticate different
bytes. Unchanged `read_archived_command_evidence.mappings` then checks the
text1/data3/data5 block and subblock identities and all-block overlap. The
reader also checks the exact data5 mapping tuple.

Each selected range must have exact integer root/address/width fields, unique
membership in the three-entry allowlist, root 21, aligned in-block bounds,
exact returned byte width and the pinned span digest before any instruction
is decoded. Unsupported forms and malformed reserved fields fail closed.
The decoder emits derived operands, not raw instruction words or byte ranges.

- Import-metadata executable SHA-256:
  `21454a8880c6254616662710d6ec626e43d853999da2cdfad700030960a94836`.
  This is metadata, not an independently obtained original executable hash.
- File Bytes: version 0, root -1, count 0.
- Block size 16384; master root 1; image offset `80000000`.
- Text1: `800055e0`, length 2796416, block/subblock 1, chain root 21.
- Data3 mapping: `802bae60..803af120`, length `0xf42c0`, block/subblock 5,
  root 199. No selected data3 reads are added.
- Data5 mapping: `80436a20..8043d500`, length 27360, block/subblock 7,
  root 263. Full data5 SHA-256 remains
  `989c794b17fc95de6e57810f5c89db23d585c85a15faafc994d9a5bd9a0e61b4`.
  No new selected constant is added to the existing twelve-constant reader.
- Checked mappings have subblock type 2, starting offset 0 and source offset 0.

| Selected span | Width | SHA-256 |
| --- | --- | --- |
| `8006a980..8006aab0` | 304 | `7fb393271bfa4e07dadb938b1fcdfa07432417321d93822c1ebc7b9926272f06` |
| `8006aab0..8006ab04` | 84 | `c8116ab45414d5501def81eef2c485644619d856449687742002d359ed6b7662` |
| `8005a298..8005a378` | 224 | `c9bf8af26f845365fb063252eba311929b38338f9bcf5a36421d632be6989efd` |

Physical spans are identical in both snapshots. Numeric offsets below are
decimal, and all three spans use obfuscated storage.

| Entry | Root / data buffer | Chain offset | Data offset | Physical offset | Length |
| --- | --- | --- | --- | --- | --- |
| `8006a980` | 21 / 47 | 414624 | 5174 | 791612 | 304 |
| `8006aab0` | 21 / 47 | 414928 | 5478 | 791916 | 84 |
| `8005a298` | 21 / 43 | 347320 | 3382 | 724284 | 224 |

## 8006a980: ordered prefix and fresh branch read

Actor offsets in this section are hexadecimal. The function retains the actor
in r31; it does not rely on the caller's earlier `4a0` read.

1. `6a99c`, `6a9a4`, `6a9a8`, `6a9ac` store bytes `18=2`, `19=2`,
   `1a=0`, `1b=0` in that order.
2. `6a9b0` reads **signed16** `272`; `6a9b4` ORs `0x443`; `6a9b8`
   writes its low16 back. `6a9bc` stores byte `490=4`.
3. `6a9c0` reads **signed16** `3ea`; `6a9c4` stores low16 to `48c`.
   `6a9c8` reads byte `3ed`; `6a9cc` copies it to byte `48e`.
   `6a9d0` reads byte `3ef`; `6a9d4` copies it to byte `48f`.
4. Only now `6a9d8` reads byte `4a0` again. `6a9dc` sign-extends and
   records the comparison; `6a9e0` branches to `6aa84` if zero.

A read failure at a later field must not erase earlier source writes. Nor can
an implementation eagerly validate all later fields before the prefix. A
caller gate saying `4a0==0` does not replace the fresh source read here.

### Zero 4a0 branch

- `6aa84` reads **signed16** `1c6`; `6aa88` copies low16 to `494`.
- `6aa8c` reads **signed16** `1c4`; `6aa94` copies low16 to `496`.
- `6aa98` clears byte `4a1`; epilogue returns at `6aaac`.

**There is no clamp on this zero branch.** Negative, zero and high-bit-set
16-bit source patterns are copied, not changed to one. There is no floating
load, new fixed constant or external call on this branch.

### Nonzero 4a0 branch remains a boundary

The archive represents the entire branch, even though the bounded runtime
slice does not implement it:

- `6a9e4` reloads `48c` as **unsigned16** and `6a9ec` copies it to stack+8.
- `6a9f0` and `6a9f4` reload bytes `48e` and `48f`, then `6a9f8` and
  `6a9fc` sign-extend them into arguments r4 and r5.
- `6aa00` calls `80066198`, with r3 pointing to stack+8. This is the
  external boundary before the subsequent arithmetic and tail stores.
- After the call, the instructions read signed16 `1c6` and `1c4`, sign-extend
  the returned low16, construct stack conversion operands using `addis 0x4330`
  and `xoris 0x8000`, and load f2 from r2-29648 at `6aa28`.
- That constant load's instruction is authenticated. Its value is **not
  selected or interpreted here**. Under the previously recorded, non-live
  r2 basis `8043ea20`, the displacement names `80437650`. No constant-read
  expansion is needed for the zero branch and none is made.
- The actual arithmetic is three **single-precision** `fsubs`, one `fdivs`,
  one `fmuls`, then `fctiwz`. Do not replace the instruction sequence with
  the decompiler's apparent double-expression evaluation order.
- `6aa68` stores low16 of the conversion result to `494`, then `6aa6c`
  reloads it as **signed16**. Only on this branch, a nonpositive value is
  replaced with one at `6aa7c`. The shared tail then copies `1c4` to `496`
  and clears `4a1`.

No callee result, FPSCR mode, arithmetic behavior, runtime source values or
successful nonzero-branch completion is claimed from these operands.

## 8006aab0: complete source-write leaf

This function has no stack frame, branch, floating instruction or call.

1. `6aab8`, `6aac0`, `6aac4`, `6aac8` store bytes `18=2`, `19=2`,
   `1a=0`, `1b=0` in that order.
2. `6aacc` reads signed16 `272`; `6aad0` ORs `0x443`; `6aad4` stores
   low16 back. `6aad8` and `6aadc` store bytes `48a=4`, then `490=4`.
3. `6aae0` reads signed16 `49e`; `6aae4` stores low16 to `48c`.
4. `6aae8` reads byte `3ed`; `6aaec` stores byte `48e`.
5. `6aaf0` reads signed16 `1c6`; `6aaf4` stores low16 to `494`.
6. `6aaf8` reads signed16 `1c4`; `6aafc` stores low16 to `496`.
7. `6ab00` returns.

It does **not** write `48f` or `4a1`. These leaves' similar prefixes are not
permission to invent identical write sets. The signed16 load versus low16
store distinction also matters when mapping existing typed owners.

### Caller 8005a190 is not fully closed by the leaf

The separately authenticated control reader shows:

- After `8005a204 -> 8006aab0` returns, `5a208` reads actor byte `88`,
  `5a214` sign-extends it, and `5a218` calls
  `80176ec0(actor, s8[88], 0)`. That call remains unsupported. Return value
  one is assigned only at `5a21c`, after the external call returns.
- After `8005a25c -> 8006a980` returns, `5a268` stores byte `489=4`,
  `5a26c` sets the return register to one, and `5a270` stores byte `19=3`.
  These caller stores must not run if the callee stops at a missing field or
  unsupported nonzero branch.

This reader references those earlier facts and does not add caller ranges.

## 8005a298: actual lazy action-request gates

1. `5a2ac` loads byte `7d2`; `5a2b0` masks its low two bits.
2. If the result equals one, `5a2bc` reads u32 `5b4` and `5a2c0` tests
   bit `0x10`. If clear, `5a2cc` writes byte `73c=4`; otherwise no actor
   write occurs. Both alternatives return without reading `73f`, `73c`,
   `4a1`, `3e4`, `508` or `4a4`.
3. Otherwise `5a2d4` loads byte `73f`, sign-extended with record bit at
   `5a2d8`; nonzero returns. Only zero reaches `5a2e0`, which loads byte
   `73c` and similarly exits if nonzero.
4. Only after both zero gates, `5a2ec` loads byte `4a1`, sign-extended at
   `5a2f0`. This determines which remaining path is reached.

### Nonzero 4a1, pointer identity gate

`5a34c` reads u32 `508` **first**, then `5a350` reads u32 `4a4`. `5a354`
compares them as unsigned words; equal writes byte `73c=2` at `5a360`.
Unequal leaves `73c` untouched. No pointer dereference or external call occurs
on this path, but both exact pointer identities still require evidence. A
synthetic object identity or arbitrary default zero cannot stand in for an
unowned source pointer. If `508` is unsupported, stop at that first read
rather than reaching `4a4` or claiming the comparison passed.

### Zero 4a1, external predicate gate

`5a2f8` loads byte `3e4`; `5a2fc` sign-extends it into r3; `5a300` calls
`80010514(s8[3e4])`. That is a boundary before `5d4` is read. A nonzero
return would exit, but this reader does not establish the return or callee
behavior and cannot assume it is zero.

If that call were supported and returned zero, `5a30c` would load u32 `5d4`
**once**. Tests show the later masks use that retained r3 value in order:
bit `0x4` wins and writes byte `73c=2` at `5a31c`; otherwise bit `0x8`
writes three at `5a330`; otherwise bit `0x10` writes five at `5a344`.
With none set the byte is unchanged. No eager `5d4` read belongs before the
predicate, and the full-return path remains unimplemented without its callee.
All paths share the epilogue at `5a364` and return at `5a374`.

## Reproduction and focused tests

From the repository root, using existing Python dependencies only:

```sh
python research/tools/matching-decomp/read_archived_ready_lifecycle_evidence.py \
  'research/decomp/GotchaForce.rep.before_force_create/idata/00/~00000000.db/db.3.gbf'
python research/tools/matching-decomp/read_archived_ready_lifecycle_evidence.py \
  'research/decomp/GotchaForce.rep.before_force_create/idata/00/~00000000.db/db.4.gbf'
PYTHONPATH=research/tools/matching-decomp python -m unittest \
  test_archived_ready_lifecycle_evidence -v
```

The 13 focused tests pass with **no skipped local archive tests**. They cover
all 153 explicit operand expectations in both archives, complete coverage,
C/map/return boundaries, ordered writes, fresh/lazy reads, both external calls,
all floating instructions, unchanged shared constant scope, malformed decoder
fields, range/root/type/alignment guards, schema/snapshot/map authentication
before selected reads, forbidden CLI options and one rejected mutation of
every selected instruction in both snapshots before decoding. Only synthetic instructions are
used as stored byte fixtures; archived bytes remain in existing ignored inputs.
A broader run of this reader plus the existing constants, command, actor-status,
control-effect and cue-reset suites passes all **88 tests**, with no skips.
These are evidence-reader tests, not a full contributor/build/retail pass.

## Appendix: every selected instruction operand

The following derived operands are listed in source order. Numbers other than
addresses are decimal. `rS`/`fS` are store sources; `rD`/`fD` are load or result
destinations. `BO`, `BI`, `AA`, `LK`, masks and record bits remain explicit.
No executable bytes or raw instruction words are included.

### 8006a980..8006aab0

```text
8006a980 stwu rS=1 rA=1 displacement=-64
8006a984 mflr rD=0
8006a988 addi rD=4 rA=0 immediate=2
8006a98c stw rS=0 rA=1 displacement=68
8006a990 addi rD=0 rA=0 immediate=4
8006a994 stw rS=31 rA=1 displacement=60
8006a998 or rS=3 rA=31 rB=3 Rc=0
8006a99c stb rS=4 rA=3 displacement=24
8006a9a0 addi rD=3 rA=0 immediate=0
8006a9a4 stb rS=4 rA=31 displacement=25
8006a9a8 stb rS=3 rA=31 displacement=26
8006a9ac stb rS=3 rA=31 displacement=27
8006a9b0 lha rD=3 rA=31 displacement=626
8006a9b4 ori rS=3 rA=3 immediate=1091
8006a9b8 sth rS=3 rA=31 displacement=626
8006a9bc stb rS=0 rA=31 displacement=1168
8006a9c0 lha rD=0 rA=31 displacement=1002
8006a9c4 sth rS=0 rA=31 displacement=1164
8006a9c8 lbz rD=0 rA=31 displacement=1005
8006a9cc stb rS=0 rA=31 displacement=1166
8006a9d0 lbz rD=0 rA=31 displacement=1007
8006a9d4 stb rS=0 rA=31 displacement=1167
8006a9d8 lbz rD=0 rA=31 displacement=1184
8006a9dc extsb rS=0 rA=0 Rc=1
8006a9e0 bc BO=12 BI=2 LK=0 target=8006aa84 AA=0
8006a9e4 lhz rD=0 rA=31 displacement=1164
8006a9e8 addi rD=3 rA=1 immediate=8
8006a9ec sth rS=0 rA=1 displacement=8
8006a9f0 lbz rD=4 rA=31 displacement=1166
8006a9f4 lbz rD=5 rA=31 displacement=1167
8006a9f8 extsb rS=4 rA=4 Rc=0
8006a9fc extsb rS=5 rA=5 Rc=0
8006aa00 bl target=80066198 AA=0
8006aa04 lha rD=4 rA=31 displacement=454
8006aa08 addis rD=5 rA=0 immediate=17200
8006aa0c lha rD=0 rA=31 displacement=452
8006aa10 extsh rS=3 rA=6 Rc=0
8006aa14 xoris rS=4 rA=3 immediate=32768
8006aa18 stw rS=5 rA=1 displacement=24
8006aa1c xoris rS=0 rA=0 immediate=32768
8006aa20 xoris rS=6 rA=4 immediate=32768
8006aa24 stw rS=3 rA=1 displacement=28
8006aa28 lfd fD=2 rA=2 displacement=-29648
8006aa2c lfd fD=0 rA=1 displacement=24
8006aa30 stw rS=0 rA=1 displacement=36
8006aa34 fsubs fD=1 fA=0 fB=2
8006aa38 stw rS=5 rA=1 displacement=32
8006aa3c lfd fD=0 rA=1 displacement=32
8006aa40 stw rS=4 rA=1 displacement=20
8006aa44 fsubs fD=0 fA=0 fB=2
8006aa48 stw rS=5 rA=1 displacement=16
8006aa4c fdivs fD=0 fA=1 fB=0
8006aa50 lfd fD=1 rA=1 displacement=16
8006aa54 fsubs fD=1 fA=1 fB=2
8006aa58 fmuls fD=0 fA=1 fC=0
8006aa5c fctiwz fD=0 fB=0
8006aa60 stfd fS=0 rA=1 displacement=40
8006aa64 lwz rD=0 rA=1 displacement=44
8006aa68 sth rS=0 rA=31 displacement=1172
8006aa6c lha rD=0 rA=31 displacement=1172
8006aa70 cmpi BF=0 L=0 rA=0 immediate=0
8006aa74 bc BO=12 BI=1 LK=0 target=8006aa8c AA=0
8006aa78 addi rD=0 rA=0 immediate=1
8006aa7c sth rS=0 rA=31 displacement=1172
8006aa80 b target=8006aa8c AA=0
8006aa84 lha rD=0 rA=31 displacement=454
8006aa88 sth rS=0 rA=31 displacement=1172
8006aa8c lha rD=3 rA=31 displacement=452
8006aa90 addi rD=0 rA=0 immediate=0
8006aa94 sth rS=3 rA=31 displacement=1174
8006aa98 stb rS=0 rA=31 displacement=1185
8006aa9c lwz rD=31 rA=1 displacement=60
8006aaa0 lwz rD=0 rA=1 displacement=68
8006aaa4 mtlr rS=0
8006aaa8 addi rD=1 rA=1 immediate=64
8006aaac blr
```

### 8006aab0..8006ab04

```text
8006aab0 addi rD=5 rA=0 immediate=2
8006aab4 addi rD=4 rA=0 immediate=0
8006aab8 stb rS=5 rA=3 displacement=24
8006aabc addi rD=0 rA=0 immediate=4
8006aac0 stb rS=5 rA=3 displacement=25
8006aac4 stb rS=4 rA=3 displacement=26
8006aac8 stb rS=4 rA=3 displacement=27
8006aacc lha rD=4 rA=3 displacement=626
8006aad0 ori rS=4 rA=4 immediate=1091
8006aad4 sth rS=4 rA=3 displacement=626
8006aad8 stb rS=0 rA=3 displacement=1162
8006aadc stb rS=0 rA=3 displacement=1168
8006aae0 lha rD=0 rA=3 displacement=1182
8006aae4 sth rS=0 rA=3 displacement=1164
8006aae8 lbz rD=0 rA=3 displacement=1005
8006aaec stb rS=0 rA=3 displacement=1166
8006aaf0 lha rD=0 rA=3 displacement=454
8006aaf4 sth rS=0 rA=3 displacement=1172
8006aaf8 lha rD=0 rA=3 displacement=452
8006aafc sth rS=0 rA=3 displacement=1174
8006ab00 blr
```

### 8005a298..8005a378

```text
8005a298 stwu rS=1 rA=1 displacement=-16
8005a29c mflr rD=0
8005a2a0 stw rS=0 rA=1 displacement=20
8005a2a4 stw rS=31 rA=1 displacement=12
8005a2a8 or rS=3 rA=31 rB=3 Rc=0
8005a2ac lbz rD=0 rA=3 displacement=2002
8005a2b0 rlwinm rS=0 rA=0 SH=0 MB=30 ME=31 Rc=0
8005a2b4 cmpi BF=0 L=0 rA=0 immediate=1
8005a2b8 bc BO=4 BI=2 LK=0 target=8005a2d4 AA=0
8005a2bc lwz rD=0 rA=31 displacement=1460
8005a2c0 rlwinm rS=0 rA=0 SH=0 MB=27 ME=27 Rc=1
8005a2c4 bc BO=4 BI=2 LK=0 target=8005a364 AA=0
8005a2c8 addi rD=0 rA=0 immediate=4
8005a2cc stb rS=0 rA=31 displacement=1852
8005a2d0 b target=8005a364 AA=0
8005a2d4 lbz rD=0 rA=31 displacement=1855
8005a2d8 extsb rS=0 rA=0 Rc=1
8005a2dc bc BO=4 BI=2 LK=0 target=8005a364 AA=0
8005a2e0 lbz rD=0 rA=31 displacement=1852
8005a2e4 extsb rS=0 rA=0 Rc=1
8005a2e8 bc BO=4 BI=2 LK=0 target=8005a364 AA=0
8005a2ec lbz rD=0 rA=31 displacement=1185
8005a2f0 extsb rS=0 rA=0 Rc=1
8005a2f4 bc BO=4 BI=2 LK=0 target=8005a34c AA=0
8005a2f8 lbz rD=3 rA=31 displacement=996
8005a2fc extsb rS=3 rA=3 Rc=0
8005a300 bl target=80010514 AA=0
8005a304 cmpi BF=0 L=0 rA=3 immediate=0
8005a308 bc BO=4 BI=2 LK=0 target=8005a364 AA=0
8005a30c lwz rD=3 rA=31 displacement=1492
8005a310 rlwinm rS=3 rA=0 SH=0 MB=29 ME=29 Rc=1
8005a314 bc BO=12 BI=2 LK=0 target=8005a324 AA=0
8005a318 addi rD=0 rA=0 immediate=2
8005a31c stb rS=0 rA=31 displacement=1852
8005a320 b target=8005a364 AA=0
8005a324 rlwinm rS=3 rA=0 SH=0 MB=28 ME=28 Rc=1
8005a328 bc BO=12 BI=2 LK=0 target=8005a338 AA=0
8005a32c addi rD=0 rA=0 immediate=3
8005a330 stb rS=0 rA=31 displacement=1852
8005a334 b target=8005a364 AA=0
8005a338 rlwinm rS=3 rA=0 SH=0 MB=27 ME=27 Rc=1
8005a33c bc BO=12 BI=2 LK=0 target=8005a364 AA=0
8005a340 addi rD=0 rA=0 immediate=5
8005a344 stb rS=0 rA=31 displacement=1852
8005a348 b target=8005a364 AA=0
8005a34c lwz rD=3 rA=31 displacement=1288
8005a350 lwz rD=0 rA=31 displacement=1188
8005a354 cmpl BF=0 L=0 rA=3 rB=0
8005a358 bc BO=4 BI=2 LK=0 target=8005a364 AA=0
8005a35c addi rD=0 rA=0 immediate=2
8005a360 stb rS=0 rA=31 displacement=1852
8005a364 lwz rD=0 rA=1 displacement=20
8005a368 lwz rD=31 rA=1 displacement=12
8005a36c mtlr rS=0
8005a370 addi rD=1 rA=1 immediate=16
8005a374 blr
```
