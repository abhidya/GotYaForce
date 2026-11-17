# Actor input GQR initializer evidence

## Fixed archived scope

`read_archived_input_gqr_evidence.py` reads only `8002a408..8002a420`
(24 bytes, six instructions) from the two existing immutable ProgramDB
snapshots in `GotchaForce.rep.before_force_create/idata/00/~00000000.db/`:

- `db.3.gbf`: SHA-256 `7b50dd2d2e17b4bfcc89a64cde27010247d0cbf0f48bd5c059f50275f40458d0`.
- `db.4.gbf`: SHA-256 `1f86813d91ea8e2c4564f96622ec42555e1dba2c78aa81ad654e892140d019f8`.

Both produce identical operands and span provenance. The selected range hash is
`9b36820166852b72b71cd34c91a379644b1b9dc97aca1e7e6c078cc74933efce`.
It is within map entry `8002a3e4`, width `0xcc`, at
`../symbols/GG4E-CSM-20220412.map:380`; the whole function is not covered.
The span is in `MAIN_.text1`, block/subblock 1, chain root 21, data buffer 31,
chain offset 151080, data offset 3678, physical offset 527972, length 24,
obfuscated. The authenticated instructions are:

1. `8002a408`: `li r3,6`.
2. `8002a40c`: `oris r3,r3,6`.
3. `8002a410`: `mtspr 916,r3`.
4. `8002a414`: `li r3,7`.
5. `8002a418`: `oris r3,r3,7`.
6. `8002a41c`: `mtspr 917,r3`.

The first triplet establishes an initializer write of `00060006` to GQR4.
The second writes `00070007` to GQR5 and exactly matches the existing
wait-reader control. No existing reader or allowlist is changed.

The reader first reuses full snapshot, schema, executable-metadata, empty
File Bytes, data5-digest and control authentication, then validates the text
mapping and non-overlap. It checks the fixed range digest and every selected
instruction before reporting operands and derived settings. Output contains no
raw executable range; CLI accepts only a snapshot path. It neither executes
instructions nor reads angle constants or direction-table contents.

## Processor documentation

The public [IBM Gekko User's Manual v1.2](https://fenixfox-studios.com/manual/powerpc/IBMGekkoManual.pdf#page=78)
was inspected on 2026-11-13. Section 2.1.2.9, printed pages 2-23–2-24,
Tables 2-16/2-17, identifies SPR 912–919 as GQR0–7. With PowerPC bit numbering,
LD_TYPE occupies 13–15 and LD_SCALE 2–7; type 6 is signed8. Thus conventional
integer extraction is `(gqr4 >>> 16) & 7` and `(gqr4 >>> 24) & 63`.

[Section 2.3.4.3.12, pages 2-55–2-56](https://fenixfox-studios.com/manual/powerpc/IBMGekkoManual.pdf#page=109)
defines conversion as integer times two raised to the negated signed scale.
Scale 0 therefore preserves every signed-byte value exactly in binary32.
Integer zero has no negative-zero encoding.

The [psq_l entry, page 12-157](https://fenixfox-studios.com/manual/powerpc/IBMGekkoManual.pdf#page=493)
specifies that W=1 reads one operand into PS0 and sets PS1 to 1.0. Nonindexed
`psq_l` requires HID2 PSE and LSQE enabled; quantized accesses assume
big-endian mode. These requirements are execution-domain preconditions, not
state established by this initializer audit.

## Runtime boundary and provenance limits

The existing input-prefix audit authenticates `psq_l f2,8(r1),W1,I4`
at `8008b778`, followed by `psq_l f1,9(r1),W1,I4` at `8008b77c`.
These load the previously stored X and Y bytes, respectively. An explicit
caller-owned GQR4 record can support a signed8/load-scale 0 conversion domain,
read lazily at each reached load, with no default or implicit hardware state.
The radius-zero paths and already-latched direction paths do not require it.
Successful conversion still stops before the angular call at `8008b780`;
it does not supply a direction result or implement the caller's nonzero branches.

This evidence proves source initializer instructions, not that startup ran,
the current register value, invariance across later code/context switches,
HID2/MSR state, retail-input provenance or exclusive production ownership.
Import metadata is not proof of unchanged original-DOL bytes. No original
game execution, gameplay parity, angle implementation or table authentication
is claimed. The public lookup concerned processor documentation only; no new
original-game data or executable source was acquired.

## Validation

`python -m unittest discover -s research/tools/matching-decomp -p 'test_archived_input_gqr_evidence.py' -v`
passes all 10 tests with both existing archives and no skips. Tests cover every
operand, matching snapshots, full selected-span coverage, the unchanged GQR5
control, strict types/forms, exact triplet recognition, authentication/mapping
failures before fixed reads, range and per-word rejection, all 192 single-bit
mutations before decoding, absence of raw output and arbitrary CLI refusal.
Both standalone reader invocations also succeeded. The new suite together with
the existing input-prefix and wait-reader suites passes all 31 tests. Broader runtime and
contributor checks are separate from this evidence-reader validation.

## Implemented explicit conversion profile

`source-input-quantized.ts` implements only signed8 load type6 at scale0.
It returns the exact binary32 signed integer and the W1 secondary lane1;
zero becomes positive zero. Store-type/scale and reserved bits in GQR4 do not
change this load. Other load types/scales refuse rather than using a generic
number conversion or saturation rule.

`actor-input-prefix.ts` may retain an explicit `processor` record. It does not
clone, default or refresh that record from browser input. It reads actual gqr4
at each reached X/Y load, after the original stick bytes have been captured,
and performs these conversions in source order. Missing profile retains the
historical8b778 refusal. A supported profile reaches the explicit8b780 angular
call refusal without changing latches, timers, edges or machine state. The
processor record must not alias the mutable actor/Borg/machine owner. The
HID2 and big-endian preconditions above remain explicit host assumptions, not
unverified assertions that a live console currently satisfies them.
