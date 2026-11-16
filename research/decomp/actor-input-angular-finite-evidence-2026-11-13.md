# Actor input finite signed-byte angular continuation

## Recommendation and boundary

The complete finite signed-byte input domain is a small, honest extension of
the [axis-only closure](actor-input-angular-axis-evidence-2026-11-13.md), once
binary64 fused arithmetic is independently implemented and checked. It needs
no host `atan`/`atan2`, polynomial substitute, manufactured constants, original
execution or general-purpose libm implementation.

The existing `source-float.ts` helper at baseline `a6af2c1c` only implements
nearest-even **binary32** addition and fused multiply-add. Although its internal
decomposition uses binary64 bits, its rounding target is binary32. It cannot
be used for the source double instructions here. Ordinary `a*b+c` introduces
two binary64 roundings and is not the source `fmadd` operation.

Equal-magnitude diagonals alone are a possible smaller runtime domain, but
they are not a shortcut around the source callee: ratio1 selects atan reduction
id1 and produces reduced zero, then still reaches every coefficient load,
polynomial operation, selected high/low table loads and reconstruction. A
constant pi/4 return would omit reached source operations and data ownership.
Once those facts are represented, closing all signed-byte inputs is useful and
manageable. This note authenticates the evidence needed for that closure; it
does not itself claim an implemented or oracle-verified runtime.

## Fixed authenticated reads

The new `read_archived_angular_finite_evidence.py` uses only the two existing
snapshots under `GotchaForce.rep.before_force_create/idata/00/~00000000.db/`:

- `db.3.gbf`, SHA-256 `7b50dd2d2e17b4bfcc89a64cde27010247d0cbf0f48bd5c059f50275f40458d0`.
- `db.4.gbf`, SHA-256 `1f86813d91ea8e2c4564f96622ec42555e1dba2c78aa81ad654e892140d019f8`.

Both produce identical selected instruction operands, constants, table entries
and span provenance. New reads total **928 text bytes and200 numeric data bytes**.
No shared reader or allowlist is changed.

| Text range, end exclusive | Bytes | SHA-256 |
| --- | ---: | --- |
| `80239a78..80239c00` |392| `01d37196d53d58f2abc0f975bf9e03ea5aa908352367d23ffbd5eaf8cb58579d` |
| `8023c240..8023c458` |536| `7d416d0cdc348e762435349f3617d5704066d9bad625163c07fede64447521c8` |

All232 newly selected instructions have decoded operands. Together with the
prior axis reader's264 bytes of atan2, its656-byte text function is complete.
The536-byte atan extent is also complete. Extents agree with
`research/symbols/GG4E-CSM-20220412.map`; C views are
`ghidra-export/chunk_0069.c:3304` (atan2) and`:5014` (atan). Complete text coverage
does not mean all nonfinite branches or their data are implemented.

Whole-snapshot identity, schema, metadata, empty File Bytes, address map, full
data5 digest and existing numeric controls are checked before new reads.
All selected mappings are checked before any new span or constant read.
Text uses block/subblock1, root21. Existing data5 uses block/subblock7, root263.
The new atan table uses `MAIN_.data2`, block/subblock4, root195, start`802b01a0`,
length44224, source and starting offsets0. Overlapping or altered mappings fail.
Its152 bytes begin at chain offset20424, data-buffer197 offset4046, physical
offset3248084, obfuscated. Executable metadata is not proof of unchanged DOL bytes.

## Finite domain and atan2 continuation

Inputs are the caller's actual signed8/scale0 X/Y conversions, integers in
[-128,127], with canonical positive zero. Source f2 is X and f1 is Y.
The already authenticated prefix tests **X exactly1 before all axis tests**.
That case calls atan directly with signed Y at`80239a04`, including Y=0.

For ordinary nonzero X/Y, finite high-word comparisons skip the infinity
branches at`80239a78..80239b40`. The signed difference of the positive binary64
high words, shifted right20 at`80239b44..80239b48`, is in[-7,7], so the source's
greater-than60 and less-than-60 fast returns cannot be reached.

The source then loads Y, loads X, performs binary64 `fdiv Y/X` at`80239b84`,
clears the quotient's sign with `fabs` at`80239b88`, and calls atan at`80239b8c`.
The magnitude is in[1/128,128]. It must not be computed from f32-rounded division.
After the callee result z is stored, the quadrant continuation is:

- m0: return z from`80239bb8`.
- m1: toggle z's sign bit with`xoris` at`80239bc4`, then return.
- m2: load piLo at`80239bd8`, load pi at`80239bdc`, then perform
  `fsub(z,piLo)` at`80239be0`, followed by `fsub(pi,prior)` at`80239be4`.
- m3: load piLo at`80239bf0`, load pi at`80239bf4`, then perform
  `fsub(z,piLo)` at`80239bf8`, followed by `fsub(prior,pi)` at`80239bfc`.

These are separately rounded subtractions, not algebraically reassociated.
The prior wrapper still performs frsp, single multiply by its authenticated
scale, signed16 GQR quantization, GQR0 reload, and only then the selected
direction-table byte read. Its source order and positive-pi saturation remain
as described in the axis note.

## Atan reduction and constants

The absolute high-word thresholds encode exact values2^66,0.4375,2^-29,
1.1875,0.6875 and2.4375. Only the zero direct-input case reaches the tiny branch.
At X=1,Y=0, atan loads huge at`8023c2e8`, one at`8023c2ec`, performs `fadd`
at`8023c2f0`, compares at`8023c2f4`, then returns the input at`8023c2fc`.
Do not replace this reached path with an early zero before its source reads.

For other finite inputs, reduction uses the following source sequences. Each
ordinary arithmetic instruction rounds to binary64 under the declared RN00
profile; fused operations have a single final rounding of their exact result.

- |v|<0.4375: id=-1, reduced input v unchanged, including direct-input sign.
- 0.4375<=|v|<0.6875: load two, load one, add two+|v| at`c334`,
  `fmsub(two,|v|,one)` at`c338`, divide at`c33c`, id0.
- 0.6875<=|v|<1.1875: load one, subtract |v|-one at`c350`, add
  one+|v| at`c354`, divide at`c358`, id1.
- 1.1875<=|v|<2.4375: load1.5, load one, subtract |v|-1.5 at`c380`,
  `fmadd(1.5,|v|,one)` at`c384`, divide at`c388`, id2.
- |v|>=2.4375 within this finite domain: load minus-one, divide by |v|
  at`c39c`, id3.

`fmsub(a,c,b)` means round(a*c-b); `fmadd(a,c,b)` means round(a*c+b).
The source uses full double forms, not their single-precision suffix variants.

| Data5 address | Exact f64 bits | Role |
| --- | --- | --- |
| `8043cdc8` | `3ca1a62633145c07` | atan2 piLo |
| `8043d128` | `7e37e43c8800759c` | huge1e300, reached only by direct zero |
| `8043d130` | `3ff0000000000000` | one |
| `8043d138` | `4000000000000000` | two |
| `8043d140` | `3ff8000000000000` |1.5 |
| `8043d148` | `bff0000000000000` | minus-one |

The complete19-entry f64 table at`802b5168..802b5200` has SHA-256
`d2300c1fe150ba73b6aed6f9d794851581a2851f55926bb7c6a87593a0f9681e`.
Entries0..3 are atanHi,4..7 atanLo,8..18 the eleven polynomial coefficients.
The reader records every individual address, exact bits and decoded value.
In atan, r5=`802b5168`; r3 is set to r5+64=`802b51a8` for coefficient loads.

## Polynomial operation and load order

The derived reader output, not C-expression reassociation, is authoritative for
operand order. From`8023c3a4`, the source does:

1. Load reduced value into f9. Set coefficient base. Load coefficient10 into f4.
2. Square f9 into f11 at`c3b4`. Load coefficients8,6,9,7 into f1,f7,f3,f0.
3. Square f11 into f10 at`c3c8`. Load coefficients4,5,2 into f6,f2,f5.
4. `fmadd f8=f10*f4+f1` at`c3d8`; load coefficient3 into f1 and0 into f4.
5. `fmadd f3=f10*f3+f0` at`c3e4`; load coefficient1 into f0.
6. Fused chain in exact order:
   `c3ec f7=f10*f8+f7`, `c3f0 f2=f10*f3+f2`,
   `c3f4 f3=f10*f7+f6`, `c3f8 f1=f10*f2+f1`,
   `c3fc f2=f10*f3+f5`, `c400 f0=f10*f1+f0`,
   `c404 f1=f10*f2+f4`.
7. Separate multiplication `c408 f2=f10*f0`, then`c40c f0=f11*f1`.

For id=-1, add f0+f2 at`c414`, then `fnmsub` at`c418` computes
**-round(f9*f0-f9)**, with negation after rounding. For id>=0, add f0+f2
at`c428`, load only selected atanLo[id] at`c42c`, load only selected
atanHi[id] at`c438`, then `fmsub` at`c43c`, subtract reduced value at`c440`,
subtract that result from atanHi at`c444`, and negate at`c44c` if the original
atan input's sign was negative. No other high/low table entry is reached.

Constants and table contents remain explicit source-owned data. Their
authentication does not authorize defaulting missing source records, reading
unselected high/low entries, replacing record identities, or moving a reached
load ahead of earlier arithmetic. Processor RN00/NI0 and disabled floating
exception enables remain explicit preconditions, not an observed live FPSCR.
Scratch stack, FPR state, FPSCR status/exception flags and unrelated processor
state remain outside the return/actor projection.

## Checks and claim ceiling

Both standalone reader invocations succeed. The new suite passes17 tests on
both existing archives, with no skips:

`python -m unittest discover -s research/tools/matching-decomp -p 'test_archived_angular_finite_evidence.py' -v`

Tests cover complete cross-snapshot text coverage, branch/reduction/quadrant
operands, binary64 vs binary32 instruction forms, fused order, strict reserved
fields, exact constants/table bits, snapshot and mapping refusal before new
reads, CLI arbitrary-read refusal, every7424 selected text-bit mutation before
decoding, and every1600 selected data-bit mutation. Raw executable bytes are
never emitted or stored; fixed spans are held in test memory only for mutations.

These checks authenticate archived source evidence and the representation of
its operands. They do not run archived instructions, prove hardware arithmetic,
verify runtime integration, produce a new DOL match, establish retail state,
or show gameplay parity. Runtime/arithmetic checks must be reported separately.
No original/archive execution, acquisition, install, publication, shared
allowlist edit, rig or process operation was performed.
