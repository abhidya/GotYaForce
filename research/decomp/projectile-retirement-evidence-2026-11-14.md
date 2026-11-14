# Projectile state2 retirement: bounded archive evidence

Date: 2026-11-14. Investigation base:
`24bf5d6216bf9e5288625492e20bcb97c25c6fd4` (preserved, no commit or push).

The [fixed reader](../tools/matching-decomp/read_archived_projectile_retirement_evidence.py)
authenticates exactly **two additional selections /64 bytes**: dispatch
cell`802d6fa0`/4 and independently selected handler`8007e63c`/60. The
[tests](../tools/matching-decomp/test_archived_projectile_retirement_evidence.py)
independently inverse-encode all15 instructions and cover every selected bit.
Both existing snapshots agree on every instruction, target, mapping and span.

This is **static archived ProgramDB evidence**. It is not original-DOL
identity, original execution, `MATCH`, live dispatch, runtime integration,
actual object deallocation or playability. Runtime integration is documented
separately in `projectile-retirement-integration-2026-11-14.md`. No existing
reader, authenticator or allowlist was changed.

## Selection fixed before the archive reads

The ignored `scope.json` and `probe.py` under
`.tmp/projectile-retirement-evidence-20261114` recorded the two literal
selections before either archive was opened:

1. Already-authenticated root callback`8007dcec` resolves table`802d6f98`,
   reloads signed child18, shifts it left2 and dispatches through the selected
   pointer. Its invalid-owner guard can store18=2. The separate
   [callback evidence](projectile-callback-evidence-2026-11-14.md) establishes
   this source and machine order. Hence **only** state2 cell
   `802d6f98 + (signed 2)*4 = 802d6fa0`, width4, was selected.
2. Independently of the cell's value, exported C
   `ghidra-export/chunk_0011.c:4613–4626` identifies candidate`8007e63c`
   with state18=3, helper`8aff0`, then82=0, followed immediately by entry
   `8007e678`. Adjacent `_index.tsv:1782–1783` independently corroborates
   these two identities. This fixes `[8007e63c,8007e678)`,0x3c=60 bytes.
   **There is no named candidate map extent.** The reader reports
   `map_size:null`; it authenticates the terminal return at`8007e674`.

The state2 cell equals the separately selected candidate in both snapshots.
This identity is checked explicitly. Its returned value never supplies a read
address or extent. Exactly those two selections follow existing authentication.
No state0/1/3 cell, adjacent handler, whole table, pointed-to payload or helper
is read. In particular, existing`8008aff0` evidence is reused, not reread.
The neighboring C/index identity establishes the candidate's end only; it does
not authorize a state3 table lookup or classify that neighbor as the state3
handler.

## Authentication, data hashes and physical provenance

The unchanged `read_archived_constants.inspect` authenticates the actual
complete SHA-256, supported table schemas, language/address map, executable
metadata, empty File Bytes and full data5 identity/controls before the new
parser/selected reads. Unchanged `command.mappings` authenticates
text1/data3/data5 mapping identities, subblocks and overlap constraints.
Exact typed mappings are checked again before each read. Selected payload
hashes are checked before decoding instructions or interpreting the pointer.

Archives already exist under
`GotchaForce.rep.before_force_create/idata/00/~00000000.db/`:

| Snapshot | Bytes | Complete SHA-256 |
| --- | --- | --- |
| db.3.gbf | 57655296 | `7b50dd2d2e17b4bfcc89a64cde27010247d0cbf0f48bd5c059f50275f40458d0` |
| db.4.gbf | 58802176 | `1f86813d91ea8e2c4564f96622ec42555e1dba2c78aa81ad654e892140d019f8` |

File Bytes version0/root−1/count0; image offset80000000; block size16384;
master root1. Executable metadata SHA-256
`21454a8880c6254616662710d6ec626e43d853999da2cdfad700030960a94836`
is import metadata, **not an independently measured original-DOL hash**.
Existing complete data5 SHA-256:
`989c794b17fc95de6e57810f5c89db23d585c85a15faafc994d9a5bd9a0e61b4`.

- text1: `[800055e0,802b0160)`, length2796416, block/subblock1, chain root21.
- data3: `[802bae60,803af120)`, length1000128, block/subblock5, chain root199.
- Both selected mappings: initialized subblock type2, starting/source offsets0.

| Selection | Width | Decoded meaning | SHA-256 |
| --- | --- | --- | --- |
| 802d6fa0 | 4 | state2 target8007e63c | `7cc80c32e114c358aba4f4c0ff53230ae0c47acdf8bd9051d0fa1cd6cbc3b830` |
| 8007e63c | 60 | complete15-instruction handler | `955fe1fa85b6c60a40c7e078f9787575519bb7a4455394bc523ae78ec5c932ad` |

The unchanged obfuscated-chain decoder yields identical provenance in both
snapshots. The following offsets are decimal; neither selection crosses a
data-buffer boundary.

| Selection | Root /data buffer | Chain offset | Data offset | Physical offset | Bytes |
| --- | --- | --- | --- | --- | --- |
| 802d6fa0 | 199 /207 | 115008 | 362 | 3408240 | 4 |
| 8007e63c | 21 /52 | 495708 | 4368 | 872726 | 60 |

Exact additional chain-call trace, in order:
`(199,115008,4,1000128)`, `(21,495708,60,2796416)`.
Tests compare this with the unchanged authenticator's complete preceding trace,
not merely the two new calls in isolation.

## Complete instruction operands and source order

PCs and child field offsets below are hexadecimal. Displacements/immediates
otherwise use decimal unless prefixed`0x`. `child` is incoming r3.

| PC | Instruction and complete decoded operands |
| --- | --- |
| 8007e63c | stwu rS1,rA1,displacement−16 |
| 8007e640 | mflr rD0 (fixed SPR8,Rc0) |
| 8007e644 | stw rS0,rA1,displacement20 |
| 8007e648 | addi rD0,rA0,immediate3 |
| 8007e64c | stw rS31,rA1,displacement12 |
| 8007e650 | or rS3,rA31,rB3,Rc0 |
| 8007e654 | stb rS0,rA3,displacement0x18 |
| 8007e658 | bl target8008aff0,AA0,LK1 |
| 8007e65c | addi rD0,rA0,immediate0 |
| 8007e660 | stb rS0,rA31,displacement0x82 |
| 8007e664 | lwz rD0,rA1,displacement20 |
| 8007e668 | lwz rD31,rA1,displacement12 |
| 8007e66c | mtlr rS0 (fixed SPR8,Rc0) |
| 8007e670 | addi rD1,rA1,immediate16 |
| 8007e674 | blr BO20,BI0,BH0,LK0 (fixed branch-register XO16) |

1. After stack/LR setup,`7e648` prepares3 and`7e650` saves incoming child in
   r31. `7e654` stores low8(3) to **incoming r3+18**.
2. `7e658` calls`8008aff0` with unchanged incoming child in r3. It is the
   sole call in the handler. There are no conditional branches, indirect
   calls or table accesses inside this body.
3. **Only after the helper returns**,`7e65c` prepares0 and`7e660` stores
   low8(0) to **saved r31+82**. This is not an early clear before the helper.
   If a model cannot complete the helper boundary, the earlier state18=3
   store remains a real prefix effect; it cannot claim the later82 clear
   or a normal return.
4. `7e664–670` restores LR, r31 and stack without replacing r3. `7e674`
   returns. The helper result, not a fabricated0/boolean, remains in r3.

Reused helper evidence is the independently authenticated32-byte body at
`8008aff0`, SHA-256
`8ea8cac06c446278fad05cfae1dbe3ee6b3a321f4bfd1168269ce88283bef951`.
It loads child2; type3 or0 stores byte1 to child1d8, while all other byte values
leave1d8 unchanged. Both helper returns preserve incoming r3. Combining that
existing evidence with this complete handler establishes the unchanged
**original child pointer** as the normal machine-register return. The C
`void` declaration does not erase this register fact.

Reused root callback evidence is152 bytes at`8007dcec`, SHA-256
`ee9edd0cdc0d53686a872a42378eb638ee4b44fdf26e25f7259f6198f71b815a`.
For an initially invalid owner guard, the root first stores18=2, calls8aff0,
clears82 and reloads18 before dispatch. If that reload is2, the newly proved
state2 handler then stores18=3, calls8aff0 **a second time**, clears82 again
and returns. These two helper calls and two82 stores must not be collapsed.
If entering the root already at state2, the root still loads child90 before
its signed state comparison, but skips the later owner dereferences/guard.

Storing state3 does **not** recursively dispatch state3 in this invocation.
The handler has no free-list, unlink, destructor or deallocator call. The
subsequent state3 dispatch and any actual free remain unselected boundaries.
A lifecycle label such as “retirement” does not establish those behaviors.

## Independent fixtures and verification

The tests manually author semantic operand rows, then use an independent PPC
inverse encoder. They neither load the reader's reports into expected values
nor use a decoder to build those fixtures. Fixtures reproduce the full body
and cell hashes. Every admitted instruction bit is exposed by an operand or
fixed by a checked instruction form; all480 one-bit instruction controls
reject or decode distinctly and inverse-encode to the exact changed word.
All512 one-bit selected-payload changes fail hashes before interpretation.

Completed locally, with no install, external fetch, original execution,
estimator/runtime import or raw payload output:

```
python -m unittest discover -s research/tools/matching-decomp -p test_archived_projectile_retirement_evidence.py -v
python research/tools/matching-decomp/read_archived_projectile_retirement_evidence.py research/decomp/GotchaForce.rep.before_force_create/idata/00/~00000000.db/db.3.gbf
python research/tools/matching-decomp/read_archived_projectile_retirement_evidence.py research/decomp/GotchaForce.rep.before_force_create/idata/00/~00000000.db/db.4.gbf
```

**14 tests pass**, including both archive positive controls and full operand,
source order, saved child, terminal return, target identity, exact read trace,
physical span, mapping/schema/whole-file authentication, selected hash,
width/type/address/duplicate allowlist, decoder/call/return mutation and CLI
refusal controls. An initial test incorrectly expected an unsupported
conditional-branch encoding to return`None` instead of raising; the test was
corrected to use an admitted but locally excluded conditional form. The
shared decoder was not changed. No authentication or selection failed in
positive discovery.

The complete derived reports remain ignored:

| Report | SHA-256 |
| --- | --- |
| `.tmp/projectile-retirement-evidence-20261114/db3.json` | `dcf52e2e0914ca9333ace203530d171bea22b30211a7b2b59a009c1f8dd2c6e2` |
| `.tmp/projectile-retirement-evidence-20261114/db4.json` | `42e6bec3789a5b3f9211dc1252924c9f094004264f4c4a032ead88ab244fe8f2` |

These are focused evidence tests, not the repository-wide contributor/docs
checks or a runtime/playability acceptance result. No unsupported lifecycle
stage, asset, neighboring state or scheduler behavior is promoted by them.

## Complete source-file hashes

All paths below are repository-relative. These full source hashes distinguish
this evidence revision from the data payload hashes above.

| Source | SHA-256 |
| --- | --- |
| `research/decomp/ghidra-export/chunk_0011.c` | `07ece988a66b1f5cf6f99bd92fce27d5cce80af3ff4d1fe91269bd70f66e11a6` |
| `research/decomp/ghidra-export/_index.tsv` | `da07bdec2e01aa836786e81f909268120e1a99a3f42f9f724d2472ef40738c98` |
| `research/symbols/GG4E-CSM-20220412.map` | `7dadd7e766ca73bc0db66a9920f22e349d1c91a3d6525de3f791404f275f237d` |
| `research/tools/matching-decomp/read_archived_constants.py` | `24330635afc70c5364bc07b02c303206c7cf07b12f955b6c9dc7765be2276e25` |
| `research/tools/matching-decomp/read_archived_command_evidence.py` | `f5723928b61c0a8a70d01e182dd2b09020cfc28334bd45e8beb3623af81c9d9b` |
| `research/tools/matching-decomp/read_archived_actor_normal_evidence.py` | `acbce56a139df957a7bfd3a2033b065131dc09c2ac4baed05f3d454f56048f29` |
| `research/tools/matching-decomp/read_archived_projectile_callback_evidence.py` | `a300c8231f57f4ee36baafc98aa24e384e8297e55bbcb10bd84f0a5d76c350cd` |
| `research/tools/matching-decomp/read_archived_projectile_retirement_evidence.py` | `c6c763822f5e6ac98cd34beb0bc52b00b9457a7b16b1002e4c4d694955226efd` |
| `research/tools/matching-decomp/test_archived_projectile_retirement_evidence.py` | `dee3e011e2426aaab49ae1da6f578905b22c2c4269513b157f2fe5ad5bfd8d92` |
