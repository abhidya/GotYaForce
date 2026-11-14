# Two-byte RNG: bounded archive evidence

Date: 2026-11-14. Investigation base:
`c0db2c16a97e6087ee156bd995cab053371985bc` (no commit or push).

The [fixed reader](../tools/matching-decomp/read_archived_rng_evidence.py)
authenticates the complete `800055fc` body: **52 bytes / 13 instructions**.
Both existing snapshots agree on every operand, mapping and physical span.
The [independent tests](../tools/matching-decomp/test_archived_rng_evidence.py)
manually specify every operand and inverse-encode the complete body hash.
All **14 evidence tests** pass, including the complete 65,536-state two-byte
input space. The sole added payload selection is the function body; neither
initial RNG byte is selected.

For unsigned incoming bytes `high` and `low`, the function computes:

```
product = 3 * (((high << 8) + low) & 0xffff)
quotient = product arithmetic-shift-right 8
nextHigh = quotient & 0xff
nextLow = (oldLow + nextHigh) & 0xff
```

It loads `high`, then `low`; stores `nextHigh`, then `nextLow`; and returns
`nextLow` zero-extended in `r3`. These are four **one-byte** memory accesses.
There is no call and no conditional branch, only the final return. This closes
the previously unselected RNG-callee semantics used by the mass-preparation
evidence, but does not read its callers again or establish a live initial seed.

This is archived ProgramDB static evidence, not independently measured original-
DOL identity, original execution, `MATCH`, live dispatch, runtime integration or
playability. The finite-state check is a synthetic test of the independently
written operand fixture against the readable C formula, not execution of source
machine code or a runtime implementation. No runtime file, shared authenticator,
mapping validator, decoder or existing allowlist changed for this evidence.

## Frozen selection and authentication

Before the first selected archive payload read, the bounded selection was
recorded in ignored `.tmp/rng-evidence-20261114/scope-frozen.json`, SHA-256
`1376a40bb256f382782faf7de4c394d13f7dc90a49deeece09b2bdffd8ddbf3f`.
It was never expanded. Independent readable sources establish:

| Selection | Width | Independent provenance |
| --- | --- | --- |
| `800055fc` through `80005630` exclusive | `0x34` / 52 | `ghidra-export/chunk_0000.c:373–386`, index lines 17–18, `research/symbols/GG4E-CSM-20220412.map:17` exact size `00000034` |

The source C identifies `DAT_804360c7` as the high byte and `DAT_804360c6` as
the low byte. The instructions establish their **r13-relative accesses**,
respectively displacements `-21721` and `-21722`. The address labels agree
with an implied small-data base of `8043b5a0`; no runtime value of `r13` or
payload at either global address was read or established. The function reads
both incoming bytes before either store, so the low update uses the saved
incoming low byte, not a reread of state.

Unchanged `read_archived_constants.inspect` authenticates complete snapshot
SHA-256, ProgramDB structure and schemas, program/language identity, import
metadata, empty File Bytes table, address map, data mapping and the existing
data5 controls. Its existing payload reads are retained exactly, not expanded
and not counted as new selected RNG reads. Unchanged `command.mappings` validates
the relevant block/subblock identities and overlap constraints; unchanged
`normal.mapping_evidence` validates the exact typed text mapping before the
new reader can select payload.

| Snapshot | Complete SHA-256 |
| --- | --- |
| `db.3.gbf` | `7b50dd2d2e17b4bfcc89a64cde27010247d0cbf0f48bd5c059f50275f40458d0` |
| `db.4.gbf` | `1f86813d91ea8e2c4564f96622ec42555e1dba2c78aa81ad654e892140d019f8` |

Both have `boot.dol` program name, Ghidra `12.1.2` creation metadata, image
offset `80000000`, 16,384-byte archive blocks, and an empty File Bytes table
(`version=0`, `root=-1`, `count=0`). The imported executable SHA-256 metadata is
`21454a8880c6254616662710d6ec626e43d853999da2cdfad700030960a94836`;
**this import property is not proof of unchanged original executable bytes**.
The unchanged data5 authentication digest is
`989c794b17fc95de6e57810f5c89db23d585c85a15faafc994d9a5bd9a0e61b4`.

The fixed text mapping is `MAIN_.text1`, block/subblock key 1,
`800055e0..802b0160` exclusive, length 2,796,416, chain root 21, subblock type 2,
zero starting/source offsets. In both snapshots the only added selection is
`chain(21, 28, 52, 2796416)`, yielding one obfuscated span:

| Root buffer | Data buffer | Chain offset | Data offset | Physical offset | Length |
| --- | --- | --- | --- | --- | --- |
| 21 | 22 | 28 | 28 | 376866 | 52 |

The complete selected body SHA-256 is
`74fb9a01b91b2d60cd400a8a96d2781782ea688ddd992f4e5eb472d4b9426438`.
The CLI accepts a snapshot path only. It cannot request an address, width,
pointer, target, state read or raw dump. Initial bytes, neighboring functions,
globals and pointer targets remain unselected. No archive is fetched.

## Complete operands, source order and effects

All 13 instructions appear below without gaps. Operand numbers are decimal;
PCs are hexadecimal. `add` fixes OE=0 and XO=266. `srawi` fixes XO=824;
its shift, registers and Rc are represented. `blr` fixes XO=16 and all reserved
bits, with BO/BI/BH/LK represented. `lbz`/`stb` use signed 16-bit displacements;
`mulli` uses a signed 16-bit immediate. Every admitted bit is represented or
fixed, and every inverse-encoded word reproduces the selected full-body digest.

| PC | Complete operands | Effect |
| --- | --- | --- |
| `800055fc` | `lbz rD=0, rA=13, displacement=-21721` | Read high byte, zero-extend into r0. |
| `80005600` | `lbz rD=4, rA=13, displacement=-21722` | Read low byte, zero-extend into r4. |
| `80005604` | `rlwinm rS=0, rA=0, SH=8, MB=0, ME=23, Rc=0` | Shift high left by 8 with 32-bit rotate/mask. |
| `80005608` | `add rD=0, rA=0, rB=4, Rc=0` | Add saved low byte. |
| `8000560c` | `rlwinm rS=0, rA=0, SH=0, MB=16, ME=31, Rc=0` | Keep low 16 bits. |
| `80005610` | `mulli rD=0, rA=0, immediate=3` | Multiply by signed immediate 3, retaining low 32 bits. |
| `80005614` | `srawi rS=0, rA=3, SH=8, Rc=0` | Arithmetic right shift by 8; set XER.CA as specified below. |
| `80005618` | `rlwinm rS=3, rA=0, SH=0, MB=24, ME=31, Rc=0` | Copy quotient low byte into r0. |
| `8000561c` | `stb rS=3, rA=13, displacement=-21721` | Store quotient low byte to high state FIRST. |
| `80005620` | `add rD=0, rA=4, rB=0, Rc=0` | Add saved incoming low to masked quotient byte. |
| `80005624` | `stb rS=0, rA=13, displacement=-21722` | Store sum low byte to low state SECOND. |
| `80005628` | `rlwinm rS=0, rA=3, SH=0, MB=24, ME=31, Rc=0` | Return low byte zero-extended in r3. |
| `8000562c` | `blr BO=20, BI=0, BH=0, LK=0` | Return via LR, no link update. |

The two loads give `0..255` each, the assembled value is `0..65535`, the
product is `0..196605`, and the shifted quotient is `0..767`. Thus the signed
multiply and arithmetic shift receive a nonnegative value, without 32-bit
overflow. `srawi` sets XER.CA to zero for every admitted state. All explicit
record bits are zero, so no CR result is recorded; no other instruction here
updates carry, overflow, LR or CTR. The source overwrites r0, r3 and r4, leaves
r13 unchanged, and performs no stack access. The outgoing low sum is `0..510`
before the byte store/return mask. No 16-bit state write may replace the two
separate byte writes if source access order matters.

Representative carry/wrap boundaries, with state ordered `(high, low)`:

| Before | After | Return |
| --- | --- | --- |
| `(0, 0)` | `(0, 0)` | 0 |
| `(0, 255)` | `(2, 1)` | 1 |
| `(1, 0)` | `(3, 3)` | 3 |
| `(85, 85)` | `(255, 84)` | 84 |
| `(85, 86)` | `(0, 86)` | 86 |
| `(255, 255)` | `(255, 254)` | 254 |

These establish semantics for supplied bytes, not which incoming state a live
game uses. Any later runtime fixture must supply its own explicit bytes and
must not claim an archive-derived seed or RNG stream.

## Verification and reproduction

All 14 focused tests passed on the first run. Coverage includes:

- Independent readable C/index/map identity and full extent.
- All 13 complete operand fixtures, independent inverse encoding and exact
  52-byte SHA-256; 416 one-bit instruction mutations must be rejected or decode
  differently and inverse-encode to that changed word.
- All 416 selected payload-bit mutations rejected by the digest before decode.
- All 65,536 possible incoming byte pairs checked against the independent
  readable-source arithmetic, including exact load/store order, one-byte
  widths, return zero-extension and carry=0.
- Address, width, type, duplicate-range, exact typed mapping, wrong payload
  length, unsupported forms, reserved bits and terminal-flow metadata refusal.
- Authentication before parsing/selection, 43 mapping corruption cases before
  selection, and 30 real schema corruption cases before selection.
- Both real snapshots, full coverage and evidence ceiling, identical physical
  span, no raw payload output, and exactly the unchanged authentication read
  list followed by the single 52-byte selection.
- Real snapshot/hash and selected-payload corruption rejection, CLI absence of
  arbitrary selection/dump options, and missing-file refusal.

Reproduction (existing snapshots only; no install/fetch):

```
python -m unittest discover -s research/tools/matching-decomp -p test_archived_rng_evidence.py -v
python research/tools/matching-decomp/read_archived_rng_evidence.py research/decomp/GotchaForce.rep.before_force_create/idata/00/~00000000.db/db.3.gbf
python research/tools/matching-decomp/read_archived_rng_evidence.py research/decomp/GotchaForce.rep.before_force_create/idata/00/~00000000.db/db.4.gbf
```

Focused static evidence verification is not contributor/docs aggregate
verification or browser acceptance. The prior mass-body payload was not reread.
Private discovery and reports remain in ignored `.tmp/rng-evidence-20261114/`.

| Derived report | SHA-256 |
| --- | --- |
| `db3.json` | `1ea6d93ddaee029e2972ebe33a0fd366030535ee6a24ca4f5feac961f707df23` |
| `db4.json` | `dd2c533a8b1a2c7f12ad4b35da0bfbc9908b3d8c2aa56119580bbf89fb57139c` |
