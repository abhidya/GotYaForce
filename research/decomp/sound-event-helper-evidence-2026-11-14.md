# Archived sound-event helper evidence, 2026-11-14

## Scope and ceiling

The fixed reader `research/tools/matching-decomp/read_archived_sound_event_evidence.py`
authenticates the **complete 300-byte / 75-instruction** function
`8005b98c..8005bab8` plus five independently named scalars, from the two
already available archived ProgramDB snapshots. All instructions and operands
are represented, including the branch at `8005ba3c` that the decompiler calls
unreachable. There are no omitted instructions or subranges.

This is static archived evidence, not original-DOL identity, a compiler `MATCH`,
original-executable execution, a console oracle, live state, numerical parity,
production integration or browser playability. It does not read the sound-table
payload, follow a constructor pointer, select phase-one instructions, run the
old port driver, collect telemetry, install software, commit or push anything.
External calls to `800f036c` and `800f061c` remain boundaries.

## Authentication and extent

The unchanged shared authenticator verifies the actual whole-file SHA-256,
exact table schemas, `boot.dol` Program name, PowerPC big-endian 32-bit
Gekko/Broadway language, Ghidra 12.1.2 metadata type/value, executable SHA
metadata type/value, empty File Bytes table, address map, complete data5 hash
and existing known controls. The new reader then verifies the unchanged strict
text1/data3/data5 mapping identities, initialized source roots, types, lengths,
offsets, address/image bounds and non-overlap. No existing allowlist changes.

| Snapshot | Whole-file SHA-256 |
| --- | --- |
| db.3.gbf | `7b50dd2d2e17b4bfcc89a64cde27010247d0cbf0f48bd5c059f50275f40458d0` |
| db.4.gbf | `1f86813d91ea8e2c4564f96622ec42555e1dba2c78aa81ad654e892140d019f8` |

The stored executable SHA remains import metadata, not proof of unchanged
original executable bytes. The File Bytes table has version0, root-1, count0.
The authenticated complete data5 SHA is
`989c794b17fc95de6e57810f5c89db23d585c85a15faafc994d9a5bd9a0e61b4`.
The complete data5 read is the unchanged authentication envelope, not a new
payload selection or an exported broad table.

Before new selections, the reader also authenticates the complete source files
used only for independent named extent:

- `research/symbols/GG4E-CSM-20220412.map`, SHA
  `7dadd7e766ca73bc0db66a9920f22e349d1c91a3d6525de3f791404f275f237d`:
  exact unique row718 is `8005b98c 0000012c 8005b98c 0 zz_005b98c_`.
- `research/decomp/ghidra-export/chunk_0007.c`, SHA
  `083e4282487e48708b0387ee4bb4c9cc7371546c2c3d4f9ad98d57316eccc3f4`:
  entry marker at line3628 is `8005b98c`; the adjacent marker at line3672
  is `8005bab8`.
- The instruction witness ends with the authenticated `blr` at `8005bab4`.
  Every non-call direct branch remains inside the selected function.

The C body is not the instruction oracle. New selections are independent
literals, never addresses obtained by following decoded pointers. The CLI
accepts only a snapshot path. Arbitrary address/width, follow, raw and execute
options are rejected.

## Fixed bytes and physical provenance

Both snapshots yield identical decoded instructions, scalars and physical
spans. Function SHA-256 is
`e2da8d687aa2b5cadc9c8159e24ec46a1bd81ad0b331d575715a359780f0ddb7`.
It occupies text1 root21, data buffer43, chain offset353196, data offset9258,
physical offset730160, length300, obfuscated=true.

| Scalar | Width | Big-endian bits | Exact decoded value | SHA-256 |
| --- | ---: | --- | --- | --- |
| `804373e4` | 4 | `00000000` | +0 | `df3f619804a92fdb4057192dc43dd748ea778adc52bc498ce80524c014b81119` |
| `80437418` | 8 | `4330000000000000` | 4503599627370496 = 2^52 | `2b2979f362d94c89fe17a6e01637f14332de063fe7a544bdc5facfc046f4169f` |
| `8043740c` | 4 | `3f333333` | 0.699999988079071 | `fe3ddc91b044dfc5ee07935a7f3e8f4cbe8e4c6af60c9ce5db25c5c81da15178` |
| `80437410` | 4 | `40000000` | 2 | `c31425b44a7ed682a3356bf6820141e1584a15c43b6d6793f552e5d4621586f7` |
| `80437404` | 4 | `3e4ccccd` | 0.20000000298023224 | `cea23fc0ff6ff5c3256ac12d2f117ac6077bc1e314894509962f9ec10ea0a269` |

All five scalars use root263, data buffer264 and obfuscated=true. Chain/data
offsets respectively are2500,2552,2540,2544,2532; physical offsets respectively
are4344266,4344318,4344306,4344310,4344298. New selections total324 bytes.

Recorded r2=`8043ea20` resolves the named scalar displacements. This is a
previously recorded base, not a new startup or live-register capture.

## Exact behavior and load order

Incoming registers are r3=actor, r4=event record, f1=current/elapsed value and
f2=previous value. The prior caller `8005b880` passes either elapsed08/previous10
or frame0c/previous14 (with its documented single-precision wrap addition).
This helper does not choose between those channels or read the record's byte2,
byte6 or next record. Those remain the caller's responsibilities.

The following semantic simplification assumes finite inputs/results and
FPSCR RN=0, NI=0. These are bounded host preconditions, not proven live settings.
The reader preserves actual `fcmpu` versus `fcmpo` and branch fields; it does
not substitute guessed NaN/FPSCR behavior.

### Frame gate

1. Allocate a16-byte stack frame. Load bias `80437418` at `5b994` **before**
   zero `804373e4` at `5b9a0`, then load the **unsigned16-bit** frame from
   record+0 at `5b9a4`. There is exactly one record-frame load.
2. Combine high word43300000 with the zero-extended frame, load that double,
   then use **single-precision `fsubs`** at `5b9b4` to subtract2^52. Unlike
   the caller's signed duration conversion, there is no `xoris 8000`.
   Every possible u16 frame is exactly representable as f32.
3. `fcmpu zero,frame` at `5b9b8`: if unequal, skip the special zero check.
   If equal, compare current with zero using `fcmpo` at `5b9c0`; ordered
   current>0 exits at `5b9c4` without loading kind, id or actor scale.
4. If continuing, reload bias at `5b9d0` and zero at `5b9d8`, in that order.
   Rebuild the conversion at `5b9e0`; frame<=0 branches straight to kind
   dispatch. Since the frame is unsigned, this finite case is exactly frame0.
5. For positive frames, rebuild the same conversion at `5b9f8`, compare
   current with frame and exit if current<frame at `5ba00`.
6. Otherwise rebuild it again at `5ba10`, compare previous with frame,
   and compute CR0.EQ = CR0.GT OR CR0.EQ at `5ba18`. Dispatch iff this
   combined bit is clear; previous>=frame exits. Previous is not compared
   on the zero-frame path or on a positive-frame current<frame exit.

Thus under the stated finite assumptions:

- frame0: dispatch iff current<=0, independently of previous.
- frame>0: dispatch iff current>=frame **and** previous<frame.

Current equality is admitted; previous equality is excluded. This is not a
symmetric window test. The decoded schedule retains four distinct conversion
sites and the second bias/zero loads rather than inventing a single-load source.

### Kind and conditional calls

Only after the gate passes, `5ba24` loads **unsigned8-bit** kind at record+3.
The comparisons against1,0,4 are signed `cmpi` instructions, but there is no
sign extension: values128..255 remain positive and are ignored, not negative.
The `5ba3c` exit branch is unreachable for this zero-extended input but remains
part of the full function witness.

- Kind0: load **unsigned16-bit** id from record+4 at `5ba50`, then call
  `800f036c` at `5ba54` with r3=actor and r4=id. No actor-scale or pitch load.
- Kind1: load actor+`b4` **once**, at `5ba5c`, then lower threshold at
  `5ba60`. This is the model-scale field, not a facing-direction operand.
  - If scale<0.699999988079071, load id at `5ba6c`, subtract1 with32-bit
    `addi` at `5ba70`, and skip the upper-threshold load.
  - Otherwise load upper threshold2.0 at `5ba78`. If scale>2, load id at
    `5ba84` then add1 at `5ba88`. Otherwise load unchanged id at `5ba90`.
  - Call `800f036c` at `5ba94`. Equality at either threshold leaves id
    unchanged. ID arithmetic is **32-bit wrapping**, with no narrowing back
    to16 bits: input0 below the lower threshold gives `ffffffff`, and
    input`ffff` above the upper threshold gives `00010000`.
- Kind2 or3: load id at `5ba9c` **before** loading f32 `80437404` at
  `5baa0`, then call `800f061c` at `5baa4` with actor/id and
  f1=0.20000000298023224. The incoming frame-window f1 is replaced.
- Kind4..255: return without loading id, actor scale or the kind2/3 scalar.

There is at most one external call per invocation. All paths reach the single
epilogue at `5baa8` and return at `5bab4`. There are no actor/record writes;
the only stores are stack-frame bookkeeping/conversion scratch. The routine
has no evidenced scalar return contract. External calls are not proof that
sound was emitted, nor permission to ignore a blocked or failed host callee.

## Complete instruction/operand witness

The reader emits every field by name. The frozen test lists the same full
schedule and independently inverse-encodes all75 instructions, requiring the
resulting300 bytes to hash to the authenticated function digest. Operand
columns below are explicit; all arithmetic, compare, branch and return forms
retain their relevant condition/link/record fields.

- Memory: destination/source register, base register, signed displacement.
- `addi/addis`: destination, base, signed immediate. Base0 is the architectural
  zero base, not a read of r0.
- `fsubs`: fD,fA,fB,Rc; `fcmpu/fcmpo`: BF,fA,fB.
- `cmpi`: BF,L,rA,signed immediate.
- `bc`: BO,BI,LK,target,AA; `b/bl`: target,AA,LK.
- `cror`: BT,BA,BB; `blr`: BO,BI,BH,LK; `mflr/mtlr`: destination/source.

```text
8005b98c stwu  1 1 -16
8005b990 mflr  0
8005b994 lfd   3 2 -30216
8005b998 stw   0 1 20
8005b99c addis 0 0 17200
8005b9a0 lfs   4 2 -30268
8005b9a4 lhz   5 4 0
8005b9a8 stw   0 1 8
8005b9ac stw   5 1 12
8005b9b0 lfd   0 1 8
8005b9b4 fsubs 0 0 3 0
8005b9b8 fcmpu 0 4 0
8005b9bc bc    4 2 0 8005b9c8 0
8005b9c0 fcmpo 0 1 4
8005b9c4 bc    12 1 0 8005baa8 0
8005b9c8 addis 0 0 17200
8005b9cc stw   5 1 12
8005b9d0 lfd   4 2 -30216
8005b9d4 stw   0 1 8
8005b9d8 lfs   0 2 -30268
8005b9dc lfd   3 1 8
8005b9e0 fsubs 3 3 4 0
8005b9e4 fcmpo 0 3 0
8005b9e8 bc    4 1 0 8005ba24 0
8005b9ec stw   5 1 12
8005b9f0 stw   0 1 8
8005b9f4 lfd   0 1 8
8005b9f8 fsubs 0 0 4 0
8005b9fc fcmpo 0 1 0
8005ba00 bc    12 0 0 8005baa8 0
8005ba04 stw   5 1 12
8005ba08 stw   0 1 8
8005ba0c lfd   0 1 8
8005ba10 fsubs 0 0 4 0
8005ba14 fcmpo 0 2 0
8005ba18 cror  2 1 2
8005ba1c bc    4 2 0 8005ba24 0
8005ba20 b     8005baa8 0 0
8005ba24 lbz   0 4 3
8005ba28 cmpi  0 0 0 1
8005ba2c bc    12 2 0 8005ba5c 0
8005ba30 bc    4 0 0 8005ba40 0
8005ba34 cmpi  0 0 0 0
8005ba38 bc    4 0 0 8005ba50 0
8005ba3c b     8005baa8 0 0
8005ba40 cmpi  0 0 0 4
8005ba44 bc    12 2 0 8005baa8 0
8005ba48 bc    4 0 0 8005baa8 0
8005ba4c b     8005ba9c 0 0
8005ba50 lhz   4 4 4
8005ba54 bl    800f036c 0 1
8005ba58 b     8005baa8 0 0
8005ba5c lfs   1 3 180
8005ba60 lfs   0 2 -30228
8005ba64 fcmpo 0 1 0
8005ba68 bc    4 0 0 8005ba78 0
8005ba6c lhz   4 4 4
8005ba70 addi  4 4 -1
8005ba74 b     8005ba94 0 0
8005ba78 lfs   0 2 -30224
8005ba7c fcmpo 0 1 0
8005ba80 bc    4 1 0 8005ba90 0
8005ba84 lhz   4 4 4
8005ba88 addi  4 4 1
8005ba8c b     8005ba94 0 0
8005ba90 lhz   4 4 4
8005ba94 bl    800f036c 0 1
8005ba98 b     8005baa8 0 0
8005ba9c lhz   4 4 4
8005baa0 lfs   1 2 -30236
8005baa4 bl    800f061c 0 1
8005baa8 lwz   0 1 20
8005baac mtlr  0
8005bab0 addi  1 1 16
8005bab4 blr   20 0 0 0
```

## Verification

```bash
python -m unittest discover -s research/tools/matching-decomp -p test_archived_sound_event_evidence.py -v
python research/tools/matching-decomp/read_archived_sound_event_evidence.py 'research/decomp/GotchaForce.rep.before_force_create/idata/00/~00000000.db/db.3.gbf'
python research/tools/matching-decomp/read_archived_sound_event_evidence.py 'research/decomp/GotchaForce.rep.before_force_create/idata/00/~00000000.db/db.4.gbf'
```

Focused result: **18 tests passed**, including both available snapshots without
skips. Tests cover every operand's independent inverse encoding, exact hash and
extent, source identity, exact scalar bits/physical spans, full-file-before-parser
authentication, actual schema/language/metadata/File Bytes refusal, actual
mapping refusal before new reads, malformed widths/hash, unselected fields,
complete return/branch bounds, conditional calls, unsigned loads with signed
kind comparisons, eager/lazy load ordering and 32-bit id arithmetic witnesses.
No claimed execution of the original instructions is needed for these tests.

The complete archived-evidence regression command is:

```bash
python -m unittest discover -s research/tools/matching-decomp -p 'test_archived_*evidence.py'
```

Result: **859 tests passed**, including this reader and the unchanged archived
evidence readers. `git diff --check` also passed. These are evidence-reader
checks, not contributor/browser acceptance or whole-game verification.
