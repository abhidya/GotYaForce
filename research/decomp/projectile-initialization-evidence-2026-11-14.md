# Projectile initializer 8007dd84: bounded archive evidence

## Fixed selection and authentication

Static archived ProgramDB evidence only. This is not original execution,
original-DOL identity, MATCH, runtime integration, live scheduling or playability.
The scope is exactly **three reads, 1,717 bytes**: the complete initial handler,
the complete draw-list insertion helper it directly calls, and one signed byte
from the already-selected projectile variant1 row. No HIT body/assets, new
pointer referents, other row fields, neighboring rows or helper bodies are read.

Selections were fixed from independent C/index/map evidence before targeted
archive reads:

- `ghidra-export/chunk_0011.c:4282–4465` and `_index.tsv:1780–1781` place
  `FUN_8007dd84` immediately before8007e200. There is **no named map row**
  for8007dd84. The selected span is `[8007dd84,8007e200)`, width47c hex,
  **1,148 bytes /287 instructions**, with authenticated terminal return7e1fc.
  Its identity is independently joined by the already-authenticated state0
  cell802d6f98/4→8007dd84, SHA
  `82ff512b4b2bdffddacade1b434ca6436328ae1014d77deb3f0db087032876cd`.
  That dispatch cell is reused, not reread by this reader.
- `chunk_0011.c:4336` calls89100(child,0,1). `chunk_0013.c:65–181`,
  `_index.tsv:1953–1954` and
  `../symbols/GG4E-CSM-20220412.map:1066–1067` independently bound
  `[80089100,80089338)`, map size238 hex,
  **568 bytes /142 instructions**. All17 return sites are authenticated.
- `chunk_0011.c:4332–4333,4339` supplies unsigned child11, stride38,
  base802d6d68 and signed byte source802d6d6b for the8ac80 argument.
  Existing spawn evidence establishes variant1, so
  `802d6d68 + 1*38 + 03 = 802d6da3`. Only this **one byte** is selected.
  It has signed value1. No row-length read, pointer following or HIT remap
  selection follows from that value.

Reader: `../tools/matching-decomp/read_archived_projectile_initialization_evidence.py`.
Tests: `../tools/matching-decomp/test_archived_projectile_initialization_evidence.py`.
All existing authenticators and allowlists remain unchanged. Complete snapshot
SHA, ProgramDB schemas, language/address maps, empty File Bytes table and full
data5 identity are authenticated first by `read_archived_constants`; the existing
command mapping checks authenticate text1/data3/data5. Only the three literal
selections above then follow. The CLI accepts a snapshot path only.

| Snapshot | Whole-file SHA-256 |
| --- | --- |
| db.3.gbf | `7b50dd2d2e17b4bfcc89a64cde27010247d0cbf0f48bd5c059f50275f40458d0` |
| db.4.gbf | `1f86813d91ea8e2c4564f96622ec42555e1dba2c78aa81ad654e892140d019f8` |

Both snapshots agree on all instructions/operands, values, mappings and physical
spans. File Bytes is version0/root−1/count0; block size16384, master root1,
image offset80000000. Executable SHA-256
`21454a8880c6254616662710d6ec626e43d853999da2cdfad700030960a94836`
is import metadata, **not** independent proof of unchanged original DOL bytes.
The unchanged authenticator file SHA-256 is
`24330635afc70c5364bc07b02c303206c7cf07b12f955b6c9dc7765be2276e25`.

Text1 is `[800055e0,802b0160)`, length2796416/root21. Data3 is
`[802bae60,803af120)`, length1000128/root199. The authenticator also checks the
complete data5 hash
`989c794b17fc95de6e57810f5c89db23d585c85a15faafc994d9a5bd9a0e61b4`.

| Selection | Bytes | Interpretation | SHA-256 |
| --- | --- | --- | --- |
| 8007dd84 | 1148 | complete initial handler | `e8732a065c806b75274606baf717082e907c68db87400e1a4299b77820148ec2` |
| 80089100 | 568 | complete draw-list insertion | `aa8525094a1010f6a9580f8d8d8413754b0204b809fb9f18536f97a640d650e5` |
| 802d6da3 | 1 | signed row1 HIT kind1 | `4bf5122f344554c53bde2ebb8cd2b7e3d1600ad631c385a5d7cce23c7785459a` |

All physical/chain offsets below are decimal. These are obfuscated ProgramDB
storage spans interpreted by the unchanged reader, not raw executable output.

| Selection | Root/data buffer | Chain offset | Data offset | Physical offset | Bytes |
| --- | --- | --- | --- | --- | --- |
| 8007dd84 | 21/52 | 493476 | 2136 | 870494 | 1148 |
| 80089100 | 21/54 | 539424 | 15328 | 916454 | 568 |
| 802d6da3 | 199/206 | 114499 | 16231 | 3407725 | 1 |

## Exact initial prefix

Addresses and object offsets in this section are hexadecimal. These are
instruction-order facts; decompiler expression order is not substituted.

1. `7ddac` loads unsigned child11 **before** `7ddb4` loads canonical owner90.
   `7ddbc` sign-extends the variant into r7, but `7ddc4` immediately masks
   back to low8 bits in r4, so indexing remains unsigned0..255.
2. `7ddc8` stores child18=1. `7ddcc` multiplies the masked variant by38;
   `7ddd0` forms base802d6d68. `7ddd4` stores numeric child100=80047aa4.
   `7ddd8/7dddc` supply r4=0/r5=1; `7dde0` forms row pointer in r30;
   `7dde4` calls actual89100(child,0,1).
3. After89100 returns, `7ddf0` stores child84=14. `7ddf4` reads signed
   owner72 with `lha`, then `7ddf8` writes its low16 bits to child72 with
   `sth`. The source owner is child90, not an inferred child8c alias.
4. `7ddfc` loads row+3 with `lbz`; `7de00` sign-extends into r4;
   `7de04` calls8ac80(child,signed-kind). For variant1 this argument is1.
   The8ac80 body and its HIT dependencies remain unselected here.
5. If8ac80 returns zero, `7de14` stores child18=2 and `7de18` branches to
   the shared epilogue7e1dc. A genuine successful HIT setup is required to
   take7de1c and perform the rest. Missing data is not evidence of a null
   return or permission to manufacture an empty HIT remap.

Consequently, a bounded runtime can preserve the real completed18,100,draw-list,
84 and72 mutations and refuse before the unsupported8ac80 dependency. It cannot
claim completed initialization. Registration does not itself invoke80047aa4.
The handler's explicit80047aa4 call is much later at7e1d0.

## Exact draw-list call89100(child,0,1)

This is a **separate** list with object104/108 links, not the allocator's object4/8
scheduling list. Numeric callback100 is only checked, not invoked by89100.

- `89100` loads child100; `89104` compares with zero; `89108` conditionally
  returns when null. That path performs no stores.
- `8910c` tests flag40; `89110` stores child85=the low byte of r4.
  For supplied group0 this stores0. Flag40,20,10 tests fall through to892b8.
- `892b8` compares insertion r5 with zero; insertion1 takes892bc→892fc.
  `892fc` scales the **full** group by4 (no low-nibble mask on this branch).
- `89300` forms head address from r13−5318; `89304` loads oldHead once.
  `89308` sets r0=0; `8930c` stores head=child; `89310` compares oldHead
  with zero; **`89314` stores child108=0 before branching on oldHead**.
- If oldHead is null, `8931c` forms tail from r13−5310;
  `89320` stores tail=child; `89324` stores child104=0; `89328` returns.
- Otherwise, `89318` branches to8932c; `8932c` stores child104=oldHead;
  `89330` stores oldHead108=child; `89334` returns. Tail is unchanged.

C names head/tail as80436288/80436290. These agree with r13 displacements using
the previously recorded r13 basis8043b5a0; this is not fresh startup or live
processor-state authentication. Neither global's contents are read here. There
is no head reload,104 load or callback invocation. r3 stays the original child.

The complete helper also represents the alternate flag40,20,10 families and
opposite insertion direction, with exact operands and returns. Those code paths
do not authenticate any corresponding global contents or request their runtime
implementation. In the first two flagged families, index is low-nibble group*4;
flag10 uses named globals803c6f3c/803c6f54. None of these pointers is followed.

## Complete-body coverage and limits

The reader represents all429 instructions, all18 returns, every selected direct
call and all in-span branches. PPC FP precision and operands are retained:
`fmuls/fdivs` are single precision, `fmul/fnmsub` double precision; `frsp`,
`frsqrte`, `fcmpo`, `fmr`, `fneg`, and CR `cror` remain distinct. Quantized paired
loads/stores retain displacement, W and I fields, including the four prologue/
epilogue instructions the C export labeled unreachable. Reserved or unknown
forms fail closed, rather than being dropped from the span.

Past8ac80 success, the handler calls actual joint-vector transform8020b7a8,
optional vector-add8020ba54, target-vector subtraction8020ba78, atan8023c240,
atan2 8023cb78, rotation8020b238 twice, concatenation8020af5c, normalize8020bab8,
and scale8020ba9c. It then performs row-dependent motion/lifetime/descriptor
stores and model setup through6fb4/6f78, conditional86b8/7c30/7d40, optional
45ef4/aedc0 effects, actual47aa4 and finally7e200. Call identities are represented
operands, **not** permission to read or claims to implement those bodies/assets.
Only row+3 is newly authenticated; no other post-HIT row value is claimed.

The complete handler extent does not mean initialization is runnable. The
canonical allocator identity, owner lifecycle/yaw bindings, separate head/tail
list storage and eventual genuine HIT registration remain runtime obligations.
The source scheduler and production/browser activation are outside this reader.

## Checks

`python -m unittest discover -s research/tools/matching-decomp -p
 'test_archived_projectile_initialization_evidence.py' -v` passes **18 tests**.

- Independently authored semantic fixtures inverse-encode all429 instructions
  to the fixed body hashes and compare every decoder field. Fixtures are not
  produced by the tested decoder or loaded from its reports.
- All13,728 single-instruction bit mutations either refuse or remain distinct
  and independently invert to the exact changed word.
- All13,736 selected-payload bit mutations refuse before interpretation.
- Exact three-read traces, physical spans, complete body/return coverage,
  row arithmetic/signedness, prefix order and draw-list104/108 order are checked.
- Explicit swapped-prefix-instruction control refuses. Unknown/reserved FP/CR
  forms, changed returns/calls/branches, malformed mappings/types/widths,
  duplicate allowlists and non-allowlisted addresses refuse.
- Whole-file, schema and selected-payload tampering refuse. Authentication
  precedes parser/selection work. The read trace is exactly unchanged
  authenticator reads plus the three fixed selections above for both snapshots.
- No raw payload output, arbitrary-address CLI, new pointer referents, external
  fetch/install, original execution, estimator import, commits or pushes.

Ignored local diagnostic reports are under
`.tmp/projectile-initialization-evidence-20261114/` and are not required by the
synthetic tests.

The archive-evidence aggregate, `python -m unittest discover -s
research/tools/matching-decomp -p 'test_archived_*evidence.py' -q`, passes
**1,008 tests**. Its log is saved beside the two derived snapshot reports.
