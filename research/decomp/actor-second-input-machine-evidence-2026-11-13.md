# Second actor input machine: archived source evidence

## Scope and authentication

This is a bounded extension of the
[first-machine evidence](actor-input-machine-evidence-2026-11-13.md), using the
same already-authenticated wrapper `80068b8c`, three handlers and dispatch table
`802d3988`. It authenticates the second descriptor and the caller instructions
from the first return through the third call. It does not execute original or
archived instructions, acquire inputs, modify a shared reader allowlist,
authenticate an unchanged original DOL, or establish live capture or ownership.

The existing local inputs are in
`GotchaForce.rep.before_force_create/idata/00/~00000000.db/`:

- `db.3.gbf`: SHA-256
  `7b50dd2d2e17b4bfcc89a64cde27010247d0cbf0f48bd5c059f50275f40458d0`.
- `db.4.gbf`: SHA-256
  `1f86813d91ea8e2c4564f96622ec42555e1dba2c78aa81ad654e892140d019f8`.

The dedicated reader
[`read_archived_second_input_machine_evidence.py`](../tools/matching-decomp/read_archived_second_input_machine_evidence.py)
authenticates the full snapshot, schemas, executable metadata, empty File Bytes
table, maps, full data5 digest and existing controls before its new reads. It
then validates the exact text/data3/data5 mapping identities. Length and digest
checks precede decoding or field interpretation. The only new fixed reads are:

- Caller `800685fc..8006862c`: 48 bytes, all 12 instructions, SHA-256
  `973241f68a601d50f06c28a3689149ff9b9f80dad96ef4781521ee4c9ee0dae2`.
- Second descriptor `802d3904..802d3910`: 12 bytes, SHA-256
  `9de63b2eeedf5a02dd167702d515058ad54ea92b8095283a3038d240bfd764ca`.

Both archives yield identical operands, values and spans. The selected caller
span has zero unrepresented instructions; it is not a full-function claim.
The independently authenticated complete caller is documented in
[the input-prefix evidence](actor-input-prefix-evidence-2026-11-13.md).
There are no arbitrary-address, width, raw-output or execution options. Output
contains only derived operands, typed fields, hashes, provenance and spans.
The executable hash property remains metadata, not original-DOL equality.

### Maps and physical spans

Caller instructions use `MAIN_.text1`, block/subblock 1, start `800055e0`,
length 2796416 and chain root 21. The single obfuscated span is data buffer 46,
chain offset 405532, data offset 12460, physical offset 782514, length 48.

Descriptor fields use `MAIN_.data3`, block/subblock 5, start `802bae60`,
end-exclusive `803af120`, length `0xf42c0` and chain root 199. The single
obfuscated span is data buffer 206, chain offset 101028, data offset 2760,
physical offset 3394254, length 12. Both mappings require subblock type 2,
starting offset 0 and source offset 0.

## Second descriptor and state mapping

The six decoded big-endian u16 cells at `802d3904` are:

- +0: 1, the handler's mode/count field.
- +2: 0, flags.
- +4: 0, the phase-1 timer reload.
- +6: 1, the successful phase-2 tail duration.
- +8: `0x0200`, mask index 0.
- +10: 0, mask index 1.

These values equal the first descriptor, but the source address is different.
Equal values do not imply a shared mutable descriptor object. The fixed
selected storage ends at the third descriptor address `802d3910` named by the
caller; no bytes at that address are read. A bounded implementation may admit
only these six halfwords, even if a caller provides a longer array. Mask
index 2 or greater exceeds this evidence and must refuse at the actual indexed
read, preserving prior timer/state writes. This host bound is not an original
range check and does not establish a complete retail structure declaration.

The second call at `80068610` targets `80068b8c` with r3 actor,
r4 `802d3904`, r5 actor+`0x618`, and r6 `0x40`. Therefore the existing
wrapper/handlers' p[0..3] refer to actor bytes `618`, `619`, `61a`, `61b`:

- `618`: phase byte used for the three-entry dispatch selection.
- `619`: timer byte, decremented and signed-byte-tested by phases 1 and 2.
- `61a`: mask index byte.
- `61b`: wrapper tail byte, whose nonzero value triggers decrement and edge OR.

The handler input mask is **`0x200`**, not the wrapper result mask **`0x40`**.
For the fixed flags0 descriptor, phase 2 reads actual actor+`5bc` without the
optional `5e0`/`5b4` gates. Mask index0 uses all-bit match on `0x200`; index1's
zero mask matches in all-bit mode. Phase 1 uses any-bit matching, so its zero
mask does not match. Exact timer expiry, read/store order, phase-0 delegation,
and lazy descriptor bounds remain those already authenticated for the shared
handlers. In particular, phase0/mode1 sets phase2 and timer127, and immediately
enters phase2, which decrements that timer to126 before testing input.

After the handler returns, the wrapper loads `61b`. Any nonzero byte is
decremented before the read/OR/store of actor+`5d4` with **`0x40`**, then the
wrapper returns1. Zero returns0 without reading or writing `5d4`. The wrapper
does not use the handler return. A successful fixed-descriptor phase2 match
clears phase `618`, loads duration1 into `61b`, then the wrapper consumes it
to0 and ORs `0x40`. A preexisting nonzero tail may also trigger that suffix
after a handler no-hit or expiry. A late failure preserves earlier stores.

## Exact caller continuation and next unsupported call

After the first wrapper call at `800685f8` returns, the six instructions are:

1. `800685fc`: load descriptor high half into r4 with `addis`.
2. `80068600`: copy retained actor r31 to r3 with `or`, discarding return r3.
3. `80068604`: add descriptor low half `3904` to r4.
4. `80068608`: set r5 to actor+`618`.
5. `8006860c`: set r6 to `0x40`.
6. `80068610`: call `80068b8c`.

After that second call returns, the six instructions are:

1. `80068614`: load descriptor high half into r4 with `addis`.
2. `80068618`: copy retained actor r31 to r3 with `or`, discarding return r3.
3. `8006861c`: add descriptor low half `3910` to r4.
4. `80068620`: set r5 to actor+`61c`.
5. `80068624`: set r6 to `0x80`.
6. `80068628`: call `80068b8c`.

There are **no caller return-dependent stores, loads, comparisons or branches**
between these calls. Either real wrapper return0 or return1 reaches the third
call with descriptor `802d3910`, actor+`61c`, mask `0x80`. A runtime supporting
only the first two machines should refuse at **`80068628`**, not return early
on a no-hit and not re-clear `5d4`. The caller's sole earlier `5d4` zero store
is at `800685e4`, before the first machine. First-machine effects and actual
second-machine effects remain visible when the third call refuses.

This extension supplies no third state owner, third descriptor data, later
machine, charge function `800686f0`, physical pad capture or production wiring.
Do not preload third-machine state/data to perform the first two machines.
The C export `ghidra-export/chunk_0008.c` independently shows the ten calls,
but exact continuation and the absence of caller stores are established here
by all 12 authenticated instructions, not an omission inferred from that C.

## Validation and limits

Run from the repository root:

```
python -m unittest discover -s research/tools/matching-decomp -p 'test_archived_second_input_machine_evidence.py' -v
python -m unittest discover -s research/tools/matching-decomp -p 'test_archived_*evidence.py'
```

The dedicated suite passed **12 tests, no skips**, and the existing archived
evidence suite plus this extension passed **373 tests, no skips**. Both
standalone reader invocations succeeded. The tests independently spell out all
12 instruction operands, including the return-discarding register copies,
check the six expected fields and exact spans in both archives, mutate each
instruction and descriptor byte, and verify authentication, mapping, strict
type, digest, range, decoder-form, no-raw-output and arbitrary-CLI refusals.

These are archived-source and synthetic reader tests, not runtime integration,
original-game replay, ownership provenance or playable acceptance. Contributor
and documentation aggregate checks belong to the integration task. This
evidence task changed only its new reader, test and note, with no installs,
acquisitions, archive/original execution, rig or process work, commit or
publication.
