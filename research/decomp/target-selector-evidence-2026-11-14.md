# Target selector: bounded archived instruction and switch-table evidence

Date: 2026-11-14. Investigation base:
`93d0e22f6a4096f5eee7778eafdd9503aeea7849`. No commit or push by this investigation.

The [fixed reader](../tools/matching-decomp/read_archived_target_selector_evidence.py)
authenticates complete `8006b450` and `80010514` bodies, **1092 bytes / 273
instructions**, plus a separately authorized and frozen **40-byte / ten-cell
switch table**. Both existing snapshots agree on every operand, table target,
control edge, and physical span. The [independent literal fixture and inverse](../tools/matching-decomp/test_archived_target_selector_evidence.py)
passes all **18 tests**. No existing authenticator, mapping validator, decoder,
allowlist, runtime source, or estimator was changed by this investigation.

The important correction to source-only reasoning is that `80010514` uses a
**pointer table at `802c3938`, loaded with `lwzx` and dispatched with `bctr`**.
Its case bodies are instructions, but the dispatch table is not embedded branch
instructions. The initial two-body scope could not authenticate the case-target
mapping; a distinct follow-on scope selects exactly ten table words, not their
pointed-to code or neighboring payload. All ten targets happen to lie inside
the already independently selected complete helper body.

The two C warnings about “unreachable” `8006b460` and `8006b7d8` do not describe
the authenticated instruction control flow. They are `psq_st` and `psq_l`
save/restore operations on ordinary entry/exit paths and are fully represented.
The selector also has a genuine unsupported-input hazard: signed command values
6–127 reach a dereference through incoming r30 without establishing r30/r31 in
this function. The evidence does not justify inventing defaults for that path.

This is archived ProgramDB **static evidence**, not independently measured
original-DOL identity, original-code execution, `MATCH`, live dispatch,
runtime integration, a completed frame, or playability. Fixture inversion is
synthetic construction, not execution. Actor/global payloads, live GQR/FPSCR
state and the unselected `8020bc88` callee remain outside this evidence.

## Frozen scope and its explicit follow-on

Before the first selected archive payload read, the original scope was frozen
in local `.tmp/target-selector-evidence-20261114/scope-frozen.json`, SHA-256
`152fee332f08583bdbd92a4d2456d16f22996328edcd258dade1f571c16c8fb7`.
That scope file remains unchanged and selects only:

| Complete body | Width | Independent readable provenance |
| --- | --- | --- |
| `8006b450..8006b7f4` exclusive | `0x3a4` / 932 / 233 instructions | `ghidra-export/chunk_0009.c:1441–1582`; `_index.tsv:1392–1393`; `research/symbols/GG4E-CSM-20220412.map:835`, exact named size `000003a4` |
| `80010514..800105b4` exclusive | `0xa0` / 160 / 40 instructions | `ghidra-export/chunk_0001.c:3095–3132`; `_index.tsv:201–202`; map line 150, exact named size `000000a0` |

The map size, independently of adjacent function entries, fixes each extent.
Map line 151's `def_8001056C` at `800105ac` is a default-case label within the
helper, not a separate selected function or evidence of table length.

The first read established the `mask 0x7f; compare unsigned 9; branch GT to
return; multiply index by four; load base 802c3938; lwzx; mtctr; bctr` sequence.
The table remained unselected while that finding was reported. Only after
explicit follow-on authorization was a new scope frozen, before its first
selected read, in
`.tmp/target-selector-evidence-20261114/follow-on-scope-frozen.json`, SHA-256
`e440af460a35669d9b0b34308a99eb2e7d8b3d7e4fa7d4d1c1c7d8a05a946db8`.

The second scope is exactly `802c3938..802c3960` exclusive, 40 bytes. Its bound
is **authenticated-instruction reachability**, not an independently map-proven
table allocation. Neither the C, index nor map establishes a named table extent.
Indices 0–9 can reach the indexed load; other masked indices return first.
There is no subsequent expansion, pointer-selected code read, neighboring
payload, global initial-value selection, constant selection or estimator import.

## Authentication, hashes and exact reads

Unchanged `read_archived_constants.inspect` authenticates actual complete
snapshot SHA-256, ProgramDB schema, PowerPC identity, address map, executable
metadata, empty File Bytes table, and its established full-data5/control reads.
Unchanged `command.mappings` checks mapping identity, bounds, initialization
and overlaps. Unchanged `normal.mapping_evidence` verifies the exact typed text
and data3 mappings. All complete authentication and mapping checks precede
any selected payload read. Each selected range then requires exact length and
SHA-256 before any instruction or pointer operand decoding.

| Existing snapshot | Bytes | Actual complete SHA-256 |
| --- | --- | --- |
| `db.3.gbf` | 57655296 | `7b50dd2d2e17b4bfcc89a64cde27010247d0cbf0f48bd5c059f50275f40458d0` |
| `db.4.gbf` | 58802176 | `1f86813d91ea8e2c4564f96622ec42555e1dba2c78aa81ad654e892140d019f8` |

Inputs are existing files in
`research/decomp/GotchaForce.rep.before_force_create/idata/00/~00000000.db/`.
No input was acquired, changed, republished or saved as a raw selected-payload
artifact. Reports contain derived operands, hashes, coverage and provenance.

Both snapshots identify `boot.dol`, Ghidra `12.1.2`, File Bytes
version 0/root −1/count 0, and image offset `80000000`. Executable SHA-256
`21454a8880c6254616662710d6ec626e43d853999da2cdfad700030960a94836`
is import metadata, not independently measured original-DOL identity.
Unchanged data5 authentication SHA-256 is
`989c794b17fc95de6e57810f5c89db23d585c85a15faafc994d9a5bd9a0e61b4`.
“No global payloads selected” does not hide or remove that authenticator's
existing full-data5 reads.

Exact mapping tuples, also checked for type identity:

- Text: `(800055e0,802b0160,1,MAIN_.text1,1,2796416,21)`.
- Data3: `(802bae60,803af120,5,MAIN_.data3,5,1000128,199)`.
- Both selected subblocks have type 2, starting offset 0 and source offset 0.

| Selection | SHA-256 |
| --- | --- |
| Selector body | `cfc8c375b1bce3d53cbfe9f1d3283341bc7c8ca09ff463b1afaed3a838eca0a7` |
| Slot-status helper body | `0064cd5dc8e78221bbe059631e699e5d62ce30994743b870fbf0f4ade60803da` |
| Ten switch-table words | `7464e12255e4f6c2c50b0cd2d2545500fe0a00ac82237ee4343c83dcb572ba11` |

| Selection | Root / data buffer | Chain offset | Buffer data offset | Physical offset | Bytes |
| --- | --- | --- | --- | --- | --- |
| `8006b450` | 21 / 47 | 417392 | 7942 | 794380 | 932 |
| `80010514` | 21 / 24 | 44852 | 12096 | 421702 | 160 |
| `802c3938` | 199 / 202 | 35544 | 2788 | 3328746 | 40 |

All three buffers are obfuscated. The **entire additional read trace**, after
the unchanged authenticator's own reads, is exactly:

```
(21, 417392, 932, 2796416)
(21, 44852, 160, 2796416)
(199, 35544, 40, 1000128)
```

Tests compare complete traces against separately traced authenticator reads
plus these exact three reads. Table destinations never determine a read.

## `80010514`: slot-status helper and bounded dispatch

The caller loads actor byte `+3e4`, sign-extends it and passes it in r3. The
helper itself accepts that integer without range checks or normalization:

1. `80010514..80010528`: form `803c73b0 + input*0x3e4`, load byte `+18`
   (`803c73c8 + input*0x3e4`). Initialize r5=0 before that load. If the byte
   equals 2, `oris r5,r5,0x8000` sets return bit 31.
2. `80010538..80010548`: form `803c4e84 + input*4`, load a pointer, then load
   pointed byte `+43d`. There is no null guard on that pointer.
3. `8001054c`: mask the byte to seven bits (`rlwinm` SH0/MB25/ME31).
   `80010550`: unsigned compare against 9. `80010554`: BO12/BI1 returns via
   `800105ac` on GT. This guard is before the switch-table read.
4. `80010558`: form high half `802c0000`; `8001055c`: shift index by two;
   `80010560`: add `3938`; `80010564`: `lwzx r0,r3,r0` loads the table word;
   `80010568`: `mtctr r0`; `8001056c`: `bctr` BO20/BI0/BH0/LK0.
5. The return path copies r5 to r3 at `800105ac`, then `blr` at `800105b0`.
   The helper writes no memory and makes no linked call.

Authenticated table correspondence:

| Masked index | Cell | Target | OR into r5 |
| --- | --- | --- | --- |
| 0 | `802c3938` | `800105ac` | none |
| 1 | `802c393c` | `800105ac` | none |
| 2 | `802c3940` | `80010570` | `01` |
| 3 | `802c3944` | `80010578` | `02` |
| 4 | `802c3948` | `80010580` | `04` |
| 5 | `802c394c` | `80010588` | `08` |
| 6 | `802c3950` | `80010590` | `10` |
| 7 | `802c3954` | `80010598` | `20` |
| 8 | `802c3958` | `800105a0` | `40` |
| 9 | `802c395c` | `800105a8` | `80` |

Indices 10–127 use the guarded return without touching the table. Input byte
bit 7 is ignored by the seven-bit mask, not interpreted as signed state.
This establishes static table association only, not live memory contents.
The two global-region payloads and pointed `+43d` byte remain unselected.

## `8006b450`: entry, command selection and fast return

The 64-byte frame saves LR, f31 and r27–r31. `8006b460` is
`psq_st f31,56(r1),W0,I0`; it follows `stfd f31,48(r1)` directly. The exit at
`8006b7d8` starts `psq_l f31,56(r1),W0,I0`, then `lfd f31,48(r1)`, restores
integer registers and LR, releases the frame and returns. No GQR0 value,
quantization configuration or live floating-point state is inferred.
The two export warnings do not license dropping these instructions. A simple
direct-edge CFG reaches both; it leaves only `8006b680` unreachable because
its predecessor is an unconditional branch and no local edge targets it.
That redundant branch is still represented in the complete-body fixture.
This CFG check is not dynamic execution or proof of every data-dependent path.

The actor pointer is saved in r29. Call `80010514` at `8006b474` comes before
the actor's `+73f` and `+73c` guards. Nonzero helper return exits. Otherwise
load/sign-extend `+73f` and exit if nonzero; then load/sign-extend `+73c` and
exit unless signed value is greater than one. All 128–255 byte encodings are
negative after sign extension and exit, rather than becoming large commands.

| Signed `+73c` | Selected byte pointer r30 | Mode r31 | Additional behavior |
| --- | --- | --- | --- |
| 2 | actor+`73d` | 1 | enter candidate scan |
| 3 | actor+`73d` | 2 | enter candidate scan |
| 4 | actor+`73d` | 1 | try fast actor restoration first |
| 5 | actor+`73e` | 0 | load +`508`, store +`6e0`, then load +`504`, store +`6e4` |
| 6–127 | incoming r30 | incoming r31 | no local assignment before `lbz 0(r30)` at `8006b544` |

Command 4 loads actor+`6e0` into r3, then requires non-null, nonzero signed
candidate byte 0, candidate byte `+18` exactly 1, and signed byte `+83` zero,
in that order. Success stores candidate to actor+`508`, writes 2 to `+502`,
then zero to `+73c` and branches to the common epilogue. It does **not** write
actor+`504`, copy target coordinates, or enter the general candidate scan.
A failed check uses normal mode 1 selection.

## Candidate scan, exact ordering and alias-sensitive operations

At `8006b544`, load the selected index byte through r30 **before** clearing
actor+`73c`, then sign-extend that byte into r5. Form list base `803c1d7c`.
Load an unsigned halfword from `r13-21342`, then zero the count word at
`r13-21504`, load CTR and guard against zero count. The C names these cells
`DAT_80436242` and `DAT_804361a0`; this body does not initialize r13 or
establish its live value, so the operand evidence preserves the r13 offsets.

For each initial list entry, in ascending four-byte order:

1. Load object pointer; skip null. Load pointer at object+`28`, then halfword
   at that pointer+2; require mask `0x200`. There is **no** null check on the
   object+`28` pointer before its halfword read.
2. Load object+`20` actor pointer; skip null. Load/sign-extend its byte 0;
   require nonzero. Compare actor pointers; skip self.
3. For nonzero mode r31, reload source and candidate team bytes `+88`,
   sign-extend both and require different teams. For mode zero require equal
   teams; then, if source signed `+4a0` is nonzero, load source+`4a4` and
   exclude a candidate equal to that pointer. These loads are not eagerly
   performed for all modes or candidates.
4. Reload candidate byte `+88`, reject exactly 4. Load/sign-extend candidate
   `+18`, require signed value less than 2. Thus negative byte encodings are
   admitted by this comparison; it is not an unsigned `status <= 1` test.
5. Reload source object pointer `+504`, compare against the current object.
   If equal, load the current count word into saved index r5. Independently
   reload count into r8, form `803b2208 + count*4`, increment and **store the
   count first** at `8006b640`; only afterward store the object pointer into
   the scratch list with `stwx` at `8006b644`.
6. Increment input-list pointer and use the original CTR countdown. The loop
   count is not reloaded per iteration. Team, current object and scratch count
   loads occur at their shown sites and should not be cached across mutations.

After the loop, reload count and exit if zero. Reload source+`504` to choose
cycling versus nearest candidate. These are actual reads, not inferred from
whether a candidate was found earlier. Initial list, scratch-list payload,
count, actor and object payloads are not selected archive data.

## Cycling, nearest selection and commit

With nonzero source+`504`, mode 2 decrements signed index r5. Mode 0 or 1
increments it; other incoming modes leave it unchanged. A negative index is
replaced with `count-1`; otherwise reload count and wrap to zero only if index
is greater than `count-1`. Load the selected object from `803b2208 + index*4`,
then store the low byte of index through r30 **before** reloading source+`504`
and comparing it with the selected object. Equal object exits without the
commit sequence, but retains this index-byte write and prior scan effects.

With zero source+`504`, load source+`4b0`, then its byte `+10`, then load the
first scratch object. Sign-extend the saved byte, multiply by `0x30`, and save
the first object as initial winner. There is no null check on source+`4b0`. At source plus the computed
stride, read floats at `+8e0`, `+8f0`, `+900`, storing each to stack `+8`,
`+c`, `+10` immediately after its read. Call unselected `8020bc88` at
`8006b720`, with r3=stack+8 and r4=first object+`64`; save returned f1 in f31.
For subsequent scratch objects, call the same unselected target at `8006b748`
with r4=current object+`64`. The loop reloads count at `8006b764` each time.

The `fcmpo f1,f31` / BO12/BI1 branch at `8006b74c/750` skips replacement only
for **GT**. LT, EQ and **unordered** all replace object and f31. Consequently
later equal-distance candidates win; a C-style ordered `new <= old` condition
would wrongly omit unordered replacement. Neither callee semantics nor live
FPSCR effects are established by this body. No distance constant or reciprocal
estimate implementation is selected here. The nearest branch does not write
the selected index byte through r30.

The commit beginning `8006b770` has this exact relevant memory order:

1. Store 1 to source+`502`.
2. Store selected object to source+`504`.
3. Load selected object+`20`; store to source+`508`.
4. Load object+`64`, then +`68`; store to source+`50c`, then +`510`.
5. Load object+`6c`; store to source+`514`.
6. Store 1 to source+`503`, then +`73c`.
7. Reload/sign-extend source byte `+3e4`, **then** store 1 to source+`3f1`.
8. Form `803c73b0 + signed_slot*0x3e4`; store 3 at `+2e6`, then zero at
   `+1b`, `+1a`, `+19`, in descending offset order.
9. Execute the complete common epilogue, including paired-single restore.

The paired coordinate loads before stores, later fresh `+6c` load, index
reload before `+3f1` write and scratch count-before-pointer store are
observable ordering distinctions if memory aliases. This evidence does not
permit atomic bulk replacement or eager evaluation across those boundaries.

## Validation and remaining ceiling

From the repository root:

```
cd research/tools/matching-decomp
python -m unittest -v test_archived_target_selector_evidence test_archived_target_preparation_evidence
```

All **34 tests pass** with both local snapshots present: 18 new selector tests
and 16 unchanged preparation regressions. The archived-evidence regression
command `python -m unittest discover -s research/tools/matching-decomp -p
'test_archived_*evidence.py'` also passes **1168 tests** (38.457 seconds).
This is not the full matching-tool or contributor/build gate. New checks include:

- Complete independent literal operand/address inventory for all 273
  instructions, and C/index/map controls for both exact complete extents.
- Independent inverse bit placement reconstructing both body SHA-256 values,
  including PSQ signed12/W/I fields and every branch operand.
- All **8736 instruction-bit mutations** refused or decoded to changed operands
  that independently re-encode to the exact mutated instruction.
- All **8736 code-payload bit mutations** refused by SHA before decoding.
- An independent ten-pointer fixture reconstructing table SHA; all **320 table
  payload bit mutations** refused before pointer decoding; all ten expected
  target mutations separately refused.
- Complete **64-control-instruction** inventory, with all **337 mutable flow
  metadata fields** corrupted individually and refused; exactly three direct
  calls, two of them to still-unselected `8020bc88`.
- Switch mask/guard/stride/base, all 256 input-byte masks, PSQ warning sites,
  complete retained unreachable branch, entry guard order, cue initialization
  limits, fast-return stores, signed candidate status, scratch count ordering,
  cycle write-before-compare, unordered nearest replacement and commit order.
- Invalid selections, widths and typed mappings rejected before reads;
  unsupported CLI options and missing/short/long input refusal.
- Whole-snapshot digest/schema refusal before any selection, all three selected
  payload corruption checks, complete unchanged authentication traces, exact
  physical spans and no raw instruction or binary payload output.

These tests do not execute original instructions, prove `8020bc88`, supply
live global/object payloads, infer valid actor-slot bounds, remove incoming
register dependence for unknown commands, establish GQR0/FPSCR behavior,
or promote a runtime. Unsupported behavior remains partial rather than guessed.
