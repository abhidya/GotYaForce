# Archived evidence for relative and percentage waits

Two authenticated local ProgramDB snapshots resolve the previously unsupported
bit 2 and bit 4 predicates in `4cd24`. Their mapped instructions identify a Gekko
quantized signed-duration load and separate single-precision arithmetic steps.
This is archived program evidence, not a fresh original-executable read, captured
live register state, or proof that the imported program was never patched.

## Constant and instruction evidence

`FLOAT_80437148` is binary32 **100**, bits `42c80000`, in both snapshots. It lies
in the previously verified `MAIN_.data5` block: chain 263, child 264, offset
`0x728` within that child's data, physical GBF offset `0x42472e`. The full data5
hash and import metadata match the [prior constant audit](archived-program-constants-2026-11-13.md).

The complete mapped function range `8004cd24..8004cff3` (720 bytes) matches
between both snapshots, SHA-256:
`0d8fdecb40f550e2003f0a28a40d4399178851ca4f1901ba73d9039701267c80`.
The startup triplet `8002a414..8002a41f` (12 bytes) also matches, SHA-256:
`47700afbd889ec8e727fc3506213596b94b94cebedaeeb6413728aca6557ee1b`.

Relevant decoded words:

| Address | Word | Instruction |
| --- | --- | --- |
| 8004ce34 | e03bd024 | psq_l f1, 36(r27), 1, 5 |
| 8004ce38 | ec21102a | fadds f1, f1, f2 |
| 8004ce68 | e05bd024 | psq_l f2, 36(r27), 1, 5 |
| 8004ce74 | ec001024 | fdivs f0, f0, f2 |
| 8004ce7c | ec010032 | fmuls f0, f1, f0 |
| 8002a414 | 38600007 | li r3, 7 |
| 8002a418 | 64630007 | oris r3, r3, 7 |
| 8002a41c | 7c75e3a6 | mtspr 917, r3 |

Register r27 points to the animation part at actor `1ad4 + index * 40` (hex),
so decimal displacement 36 is `duration24`. The paired-single load has W=1 and
I=5. SPR 917 is GQR5. The startup triplet writes `0x00070007`, selecting signed16,
scale-zero conversion. The [earlier walking audit](time-bomber-walking-2026-11-12.md)
also identifies this initialization address. This evidence establishes that
initializer, not a global invariant or a live GQR measurement.

The odd `longlong`/`double` casts in the decompiled C represent this quantized
load. They must not be replaced by the unrelated `CONCAT44` conversion idiom
merely because that idiom appears elsewhere in the function.

## Exact predicate sequences

Priority is countdown bit 8, relative bit 2, percentage bit 4, then default.

Bit 2:

1. Load `wait14`. Nonnegative values, including either signed zero, skip duration
   access and retain the threshold unchanged.
2. For a strictly negative wait, load signed16 `duration24` through GQR5, add wait
   with `fadds`, and replace a strictly negative sum with positive zero.
3. Load progress `frame0c` and test threshold <= progress. The authored `wait14`
   field is not changed by this calculation.

Bit 4:

1. Quantized-load signed16 duration, then load progress and the 100 constant.
2. `fdivs` rounds progress/duration to binary32.
3. Load `wait14`, then `fmuls` rounds 100 times that rounded quotient to binary32.
4. Test wait <= percentage. It is not multiplication before division and not a
   combined expression with just one final rounding.

The source-owned port follows these reached reads and arithmetic boundaries.
The model must explicitly select factory option `gqr5: 0x00070007` before a
quantized duration load is admitted. The option is immutable after construction
and checked lazily. A nonnegative relative wait does not require it. This is a
chosen startup-derived host profile, not a claim to have observed the register
in a running game.

The existing finite exact-f32 RN=00/NI=0 domain remains. Signed16 negative
nonzero divisors are allowed. Zero divisors, malformed operands and nonfinite
percentage results refuse before continuation; this deliberately excludes PPC
nonfinite/exception behavior. Percentage reads frame before the zero-divisor
refusal, and reads wait after quotient computation but before product validation.
Event clears and other preceding effects are not rolled back.

## Numeric validation

For finite binary32 progress and nonzero signed16 duration, a binary64 division
followed by binary32 rounding gives the correctly rounded quotient on this
bounded domain. For a normal quotient in binade `2^k`, binary32 midpoint unit is
`t = 2^(k-24)`. The input progress is an integer multiple of t. A quotient unequal
to a midpoint is therefore at least `t / |duration| >= t * 2^-15` away, whereas
binary64 rounding error is at most `t * 2^-29`. It cannot cross the midpoint.
An exact midpoint is exactly representable in binary64. For a subnormal quotient,
use `t = 2^-150`; the error bound is smaller still. Signed zero is handled directly.

Multiplying the rounded binary32 quotient by 100 requires at most 29 significant
bits and remains within binary64's exponent range, so the multiplication is exact
before the final binary32 rounding. These arguments are specific to the bounded
inputs and profile; they are not a general claim about arbitrary mixed-precision
PPC execution.

An independent BigInt rational reference passed 377,631 arithmetic cases,
including every nonzero signed16 divisor for five edge frames and 50,000 seeded
bit-pattern cases. A separate comparison through the actual owned runtimes passed
21,178 cases: 13,866 met waits, 7,036 unmet waits, 108 percentage-overflow refusals
and 168 zero-divisor refusals. It checked unchanged wait/frame/duration, selected
event clearing, untouched other parts and no completion/target changes on refusal.
These are synthetic/reference checks, not original-game replay.

A simple regression case is progress 1, duration 3. Correct staged percentage is
`33.333335876464844` (bits `42055556`). Omitting quotient rounding or multiplying
first gives `33.33333206176758` (bits `42055555`). A wait threshold with bits `42055556`
must be met by the correct source sequence.

## Reproduction and provenance limits

Run the bounded stdlib-only checker against either local snapshot:

```sh
python3 research/tools/matching-decomp/read_archived_wait_evidence.py \
  'research/decomp/GotchaForce.rep.before_force_create/idata/00/~00000000.db/db.3.gbf'
python3 research/tools/matching-decomp/read_archived_wait_evidence.py \
  'research/decomp/GotchaForce.rep.before_force_create/idata/00/~00000000.db/db.4.gbf'
```

The utility authenticates the same whole-file hashes, follows primary schemas
and address/subblock/buffer relationships, and emits only fixed evidence facts,
range hashes and bounded instruction words. No address-pattern search, arbitrary
address CLI, raw block export, emulator, download or Ghidra execution is used.
Synthetic tests contain no original game blocks.

Both code ranges map to initialized `MAIN_.text1`, block/subblock 1, base
`800055e0`, length 2,796,416, chain 21. Function chain offset is `0x47744`, child
39 offset `0x37aa`, physical `0xa37b0`. Startup chain offset is `0x24e34`, child 31
offset `0xe6a`, physical `0x80e70`. Words above are decoded values; physical GBF
storage is XOR-obfuscated as described in the prior format audit.

An independent parser reproduced these mappings, hashes and words from both
snapshots. The initial instruction audit used already-installed LLVM for ordinary
PPC instructions and the repository's `ppcdis.py` for the Gekko load fields; the
portable reproduction does not depend on LLVM. No raw payload was written or
uploaded. The snapshots' File Bytes table is empty, so the imported original
executable cannot be reconstructed and hash-verified from it. Neither the two
matching archives nor their metadata proves that every imported byte is unchanged.

Command parsing, runtime GQR invariance, original replay, instruction/ABI parity
for the whole port, NI=1 behavior and live clone activation remain unverified.
