# Actor input axis-only angular evidence

## Fixed archive scope

`read_archived_angular_axis_evidence.py` authenticates the two existing snapshots
under `GotchaForce.rep.before_force_create/idata/00/~00000000.db/`:

- `db.3.gbf`: SHA-256 `7b50dd2d2e17b4bfcc89a64cde27010247d0cbf0f48bd5c059f50275f40458d0`.
- `db.4.gbf`: SHA-256 `1f86813d91ea8e2c4564f96622ec42555e1dba2c78aa81ad654e892140d019f8`.

Both snapshots produce identical selected operands, constants, table entries and
span provenance. New selected reads total 364 text bytes, 36 constant bytes and
8 direction-table bytes. No shared reader or allowlist is changed.

| Text selection, end exclusive | Bytes | SHA-256 |
| --- | ---: | --- |
| `800452a0..800452e4` | 68 | `cda6ef97281052cb1f03422007ce4b07056ec9232342bd6e0c2fd6c07fdd38b8` |
| `8023cb78..8023cb98` | 32 | `cf8c2fc8d1d538e2582ef7c59421fab6a440e19e32eed3354320b6bd5da843dd` |
| `80239984..80239a78` | 244 | `a7d7c189206c510355f928043bc10a7d103275746bec7bc3125ce08f352abc2e` |
| `80239c00..80239c14` | 20 | `632aad066b44b80b2d4062eea6c08624bbb761e3dc516c09c839ff0258eb5fe3` |

All 91 selected instructions have decoded operands; none are silently omitted.
The first wrapper extent is bounded by C-export entries in `chunk_0005.c`.
The shim and atan2 extents match symbol-map entries at
`../symbols/GG4E-CSM-20220412.map:4497` and `:4476`.
The complete atan2 function is 656 bytes. This reader covers 264 of them and
**does not read or represent `80239a78..80239c00` (392 bytes)**. Its selected
prefix includes the NaN dispatch and the call to atan for x=1, but authenticating
these operands does not implement those paths or the atan callee.

Full snapshot identity, exact schemas, executable metadata, empty File Bytes,
address map, full data5 digest and existing constant controls are checked first.
All selected memory mappings are checked before new reads. Text uses block and
subblock 1, chain root21; data5 uses block/subblock7, root263. The table uses
`MAIN_.data4`, block/subblock6, start`804335a0`, length11040, root262, source and
starting offsets0. All memory-block overlaps and mapping changes are rejected.
The table lies at chain/data offset904, physical offset4309906, length8,
obfuscated. Executable metadata is not proof of unchanged original-DOL bytes.

## Call order and exact operands

The existing [input-prefix evidence](actor-input-prefix-evidence-2026-11-13.md)
authenticates the caller: `8008b778` loads X into f2, then `8008b77c` loads Y
into f1, both W1/I4. The call at `8008b780` therefore passes **atan2(Y,X)**.
The [GQR initializer evidence](actor-input-gqr-evidence-2026-11-13.md) supports
an explicit signed8/scale0 load profile; it does not establish current registers.

The full `800452a0` wrapper performs:

1. Allocate32 stack bytes, save LR at stack+36, and `stfd f31,16(r1)`.
2. `800452b0`: `psq_st f31,24(r1),W0,I0`.
3. `800452b4`: call`8023cb78`. That shim calls`80239984` at`8023cb84`,
   with f1/f2 unchanged, then restores its stack/LR and returns.
4. `800452b8`: `frsp f1,f1`.
5. `800452bc`: `lfs f0,-31140(r2)`.
6. `800452c0`: `fmuls f31,f0,f1`. This is separate single-precision
   multiplication, not a double multiply or fused operation.
7. `800452c4`: `psq_st f31,8(r1),W1,I5`.
8. `800452c8`: `lha r3,8(r1)` returns a sign-extended halfword.
9. `800452cc`: `psq_l f31,24(r1),W0,I0`, followed by LR reload,
   `lfd f31,16(r1)`, LR restoration, stack restoration and return.

The wrapper's saved f31 value is not an input to its angular arithmetic. A
return-value/actor-field projection may leave that prior value opaque, provided
it does not claim complete scratch-stack, FPR, FPSCR or exception equivalence.
That is a scope decision, not evidence that every saved lane is unchanged.

## Axis branches and exact constants

The prefix splits f2 (X) and f1 (Y) into their binary64 high/low words, rejects
NaNs through a separate path, then tests **X exactly +1 before testing axes**.
At `80239a00`, the unequal branch skips to`80239a0c`; equality instead reaches
`bl 8023c240` at`80239a04`. This atan callee is outside the closure, including
when Y=0. Do not return zero for that case by algebraic simplification.

At`80239a0c`, the absolute Y words are ORed with Rc=1. Quadrant construction
preserves that CR result: `rlwinm` extracts twice X's sign, `or` copies it,
then `rlwimi r31,r5,1,31,31` inserts Y's sign without updating CR. Therefore
`80239a1c` branches to`80239a58` only for nonzero Y. For zero Y:

- m0/m1, nonnegative-sign X: `80239a30` goes to the epilogue with original
  f1 unchanged, preserving +0 or -0 before the later integer quantization.
- m2: `lfd f1,-7336(r2)` at`80239a48`, positive pi.
- m3: `lfd f1,-7328(r2)` at`80239a50`, negative pi.

For nonzero Y, `80239a58` ORs absolute X words. Nonzero X branches at`80239a5c`
to the first unrepresented instruction`80239a78`; refuse there rather than
substitute host atan2. Zero X, including -0, compares Y's signed high word at
`80239a60`: negative Y loads `-pi/2` at`80239a68`; otherwise `+pi/2` at`80239a70`.
Each constant-load branch then jumps to`80239c00` and returns unchanged f1.

| Address | Type | Exact bits | Value / role |
| --- | --- | --- | --- |
| `8043707c` | f32 | `4622f983` | `10430.3779296875`, angular multiplier |
| `8043cd78` | f64 | `400921fb54442d18` | `3.141592653589793`, positive pi |
| `8043cd80` | f64 | `c00921fb54442d18` | `-3.141592653589793`, negative pi |
| `8043cd88` | f64 | `bff921fb54442d18` | `-1.5707963267948966`, negative half-pi |
| `8043cd90` | f64 | `3ff921fb54442d18` | `1.5707963267948966`, positive half-pi |

The r2 basis`8043ea20` and r13 basis`8043b5a0` are recorded in
`../../docs/static-recompilation-spike.md:178-180`, not newly authenticated by
this reader. These bases resolve the observed displacements to the stated
constant/table addresses. Explicit decoded address owners are not proof of
live r2/r13 or permission to manufacture arbitrary memory contents.

## Quantization and processor domain

The public [IBM Gekko User's Manual v1.2](https://fenixfox-studios.com/manual/powerpc/IBMGekkoManual.pdf)
was inspected on2026-11-13. [Printed2-57/2-58](https://fenixfox-studios.com/manual/powerpc/IBMGekkoManual.pdf#page=111)
specifies integer quantization by scaling, truncation toward zero and overflow
clamping. Type7/scale0 therefore yields signed16 in[-32768,32767]. The GQR5
initializer writes`00070007`; runtime must still supply its reached store state.

[Printed12-161](https://fenixfox-studios.com/manual/powerpc/IBMGekkoManual.pdf#page=497)
uses only store type/scale and stores PS0 for W1, both lanes for W0. Type0 ignores
scale. [Printed2-30](https://fenixfox-studios.com/manual/powerpc/IBMGekkoManual.pdf#page=84)
and2-58 warn that a denormal stored through type0 becomes zero. Thus GQR0
float spill/reload is not unconditional bitwise lane preservation.

[frsp12-82](https://fenixfox-studios.com/manual/powerpc/IBMGekkoManual.pdf#page=418)
and [fmuls12-73](https://fenixfox-studios.com/manual/powerpc/IBMGekkoManual.pdf#page=409)
use FPSCR.RN. The [Motorola/IBM PowerPC Programming Environments, revision1,
Table2-4](https://www.nxp.com/docs/en/user-guide/MPCFPE_AD_R1.pdf#page=72)
assigns RN to bits30–31 and encodes nearest as00.
[Table3-8, printed3-26](https://www.nxp.com/docs/en/user-guide/MPCFPE_AD_R1.pdf#page=132)
specifies ties-to-even. The same register table identifies exception enables
in bits24–28 and NI in bit29. Thus a narrow profile can require low byte0:
nearest, IEEE mode and disabled enables. These documented meanings are not
archived live state. HID2 PSE/LSQE and big-endian operation remain host
preconditions. FPSCR exception/status effects are outside this projection.

Under that declared profile, rounding the exact archive constants to f32 before
multiplication produces `+0`, `-0`, `+16384`, `-16384`, `+32768` or`-32768`.
**Positive pi returns32767 after signed16 saturation, not-32768 by wraparound.**
Negative pi returns-32768. Both zero signs become integer0. This arithmetic
cross-check is derived host arithmetic, not original instruction execution.

## Direction table and smallest useful implementation

The 8 byte entries at`80433928` are `[2,10,8,9,1,5,4,6]`, with SHA-256
`6f804bbb73c4b8d418ef3ae69153dc5cde7bf4eb989b44c6ae082a5122108fec`.
The existing input-prefix reader authenticates the post-call tail:

- `8008b784`: mask return r3 to low16 in r4.
- `8008b788`: compute table base r13-31864.
- `8008b78c`: add4096 to the masked angle.
- `8008b790`: `rlwinm SH19,MB29,ME31`, equivalent to extracting
  index`(((angle & 65535)+4096) >>> 13) & 7`.
- `8008b794`: load only the indexed byte with`lbzx`.

Consequently right/up/left/down return2/8/1/4. The table read belongs after the
complete angular return, including the GQR0 reload check. It must not be eager.

The smallest useful input profile accepts finite signed-byte axes under the
existing explicit GQR4 conversion; those conversions always produce +0 for
integer zero. At thresholds20 and52 there are respectively434 and306 nonzero
axis pairs, including equality with the radial threshold. All avoid X=1.
General non-axis inputs remain unsupported. A standalone angular helper that
admits signed zeros needs the exact sign cases above, not just numeric `<0`.

Retain explicit constant/table and processor owners. Read GQR0-store at452b0,
only the reached axis constant, FPSCR at452b8, multiplier at452bc, FPSCR again at
452c0, GQR5-store at452c4, GQR0-load at452cc, and the table entry at8b794. Missing
angular runtime must retain the old8b780 refusal. No owner values are invented,
refreshed from browser input, or read before their source operation is reached.

The caller's nonzero-direction stores also need source order. The first gate
reloads flags, sets bit0, writes it, separately clears then reloads/ORs the low
nibble of actor+5d8, reloads again to choose timer3 or2. The second gate sets
bit1, separately clears bits4..7 of5d8, reloads H, then stores low16 of
`H | ((H & directionByte) << 4)` and timer20. Neither uses one cached halfword
for all operations. These operands are in the existing input-prefix audit.

## Validation and claim ceiling

The new suite passes16 tests on both archives, no skips:

`python -m unittest discover -s research/tools/matching-decomp -p 'test_archived_angular_axis_evidence.py' -v`

It covers complete selected-span decoding, wrapper operand order, axis branches,
exact constants/table values, cross-snapshot identity, source span coverage,
strict operand forms/types, authentication and mapping failures before reads,
CLI arbitrary-read refusal, all2912 selected text-bit mutations before decoding,
and all352 selected data-bit mutations. Both standalone reader invocations pass.
No raw executable range is emitted or stored by the reader. The tests hold
fixed authenticated spans in memory only for corruption checks.

This is archived source evidence plus arithmetic checks, not a new DOL match,
retail-state sample, console oracle, complete atan2, FPR/FPSCR emulator, animation,
movement, production input ownership or gameplay-parity result. No original or
archived executable was run. No archive acquisition, install, publication,
shared allowlist modification or rig/process work was performed.
