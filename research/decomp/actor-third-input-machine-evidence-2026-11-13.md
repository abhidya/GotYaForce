# Third actor input machine: archived source evidence

## Scope and authentication

This bounded extension of the
[first-machine evidence](actor-input-machine-evidence-2026-11-13.md) and
[second-machine evidence](actor-second-input-machine-evidence-2026-11-13.md)
authenticates the third descriptor and every caller instruction from the second
return through the fourth call. It reuses the already-authenticated wrapper
`80068b8c`, three handlers and dispatch table `802d3988` without changing them.
It does not execute original or archived instructions, acquire inputs, modify a
shared reader allowlist, authenticate an unchanged original DOL, or establish
live capture or ownership.

The existing local inputs are in
`GotchaForce.rep.before_force_create/idata/00/~00000000.db/`:

- `db.3.gbf`: SHA-256
  `7b50dd2d2e17b4bfcc89a64cde27010247d0cbf0f48bd5c059f50275f40458d0`.
- `db.4.gbf`: SHA-256
  `1f86813d91ea8e2c4564f96622ec42555e1dba2c78aa81ad654e892140d019f8`.

The dedicated reader
[`read_archived_third_input_machine_evidence.py`](../tools/matching-decomp/read_archived_third_input_machine_evidence.py)
authenticates the full snapshot, schemas, executable metadata, empty File Bytes
table, maps, full data5 digest and existing controls before its new reads. It
then validates the exact text/data3/data5 mapping identities. Length and digest
checks precede decoding or field interpretation. The only fixed additions are:

- Caller `80068614..80068644`: 48 bytes, all 12 instructions, SHA-256
  `fbbf9b264244ef16b4963b6bc44a48af5915fd4254f53d3b117abe4eb93293c6`.
- Third descriptor `802d3910..802d391c`: 12 bytes, SHA-256
  `104b15ebd69662e3df7689de6edbe0cf3625b45396c3f2c3b4f939854d66dac5`.

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
chain offset 405556, data offset 12484, physical offset 782538, length 48.

Descriptor fields use `MAIN_.data3`, block/subblock 5, start `802bae60`,
end-exclusive `803af120`, length `0xf42c0` and chain root 199. The single
obfuscated span is data buffer 206, chain offset 101040, data offset 2772,
physical offset 3394266, length 12. Both mappings require subblock type 2,
starting offset 0 and source offset 0.

## Third descriptor and state mapping

The six decoded big-endian u16 cells at `802d3910` are:

- +0: 1, the handler's mode/count field.
- +2: 0, flags.
- +4: 0, the phase-1 timer reload.
- +6: 1, the successful phase-2 tail duration.
- +8: `0x0400`, mask index 0.
- +10: 0, mask index 1.

The third descriptor differs from the first two in its input mask: **`0x400`,
not `0x200`**. The fixed selected storage ends at the fourth descriptor address
`802d391c` named by the caller; no bytes at that address are read. A bounded
implementation may admit only these six halfwords, even if a caller provides a
longer array. Mask index 2 or greater exceeds this evidence and must refuse at
the actual indexed read, preserving prior timer/state writes. This host bound
is not an original range check and does not establish a complete retail
structure declaration.

The third call at `80068628` targets `80068b8c` with r3 actor,
r4 `802d3910`, r5 actor+`0x61c`, and r6 `0x80`. Therefore the existing
wrapper/handlers' p[0..3] refer to actor bytes `61c`, `61d`, `61e`, `61f`:

- `61c`: phase byte used for the three-entry dispatch selection.
- `61d`: timer byte, decremented and signed-byte-tested by phases 1 and 2.
- `61e`: mask index byte.
- `61f`: wrapper tail byte, whose nonzero value triggers decrement and edge OR.

The handler input mask is **`0x400`**, not the wrapper result mask **`0x80`**.
For the fixed flags0 descriptor, phase 2 reads actual actor+`5bc` without the
optional `5e0`/`5b4` gates. Mask index0 uses all-bit match on `0x400`; index1's
zero mask matches in all-bit mode. Phase 1 uses any-bit matching, so its zero
mask does not match. Exact timer expiry, read/store order, phase-0 delegation,
and lazy descriptor bounds remain those already authenticated for the shared
handlers. In particular, phase0/mode1 sets phase2 and timer127, and immediately
enters phase2, which decrements that timer to126 before testing input.

After the handler returns, the wrapper loads `61f`. Any nonzero byte is
decremented before the read/OR/store of actor+`5d4` with **`0x80`**, then the
wrapper returns1. Zero returns0 without reading or writing `5d4`. The wrapper
does not use the handler return. A successful fixed-descriptor phase2 match
clears phase `61c`, loads duration1 into `61f`, then the wrapper consumes it
to0 and ORs `0x80`. A preexisting nonzero tail may also trigger that suffix
after a handler no-hit or expiry. A late failure preserves earlier stores.

## Exact caller continuation and next unsupported call

After the second wrapper call at `80068610` returns, the six instructions are:

1. `80068614`: load descriptor high half into r4 with `addis r4,r0,-32723`.
2. `80068618`: copy retained actor r31 to r3 with `or r3,r31,r31`, discarding return r3.
3. `8006861c`: `addi r4,r4,0x3910`, forming descriptor `802d3910`.
4. `80068620`: `addi r5,r31,0x61c`, setting the third state pointer.
5. `80068624`: `addi r6,r0,0x80`, setting the wrapper result mask.
6. `80068628`: `bl 80068b8c`, calling the wrapper.

After that third call returns, the six instructions are:

1. `8006862c`: load descriptor high half into r4 with `addis r4,r0,-32723`.
2. `80068630`: copy retained actor r31 to r3 with `or r3,r31,r31`, discarding return r3.
3. `80068634`: `addi r4,r4,0x391c`, forming descriptor `802d391c`.
4. `80068638`: `addi r5,r31,0x624`, setting the next state pointer.
5. `8006863c`: `addi r6,r0,0x200`, setting the next wrapper result mask.
6. `80068640`: `bl 80068b8c`, making the fourth call.

There are **no caller return-dependent stores, loads, comparisons or conditional
branches** between these calls. Either real wrapper return0 or return1 reaches
the fourth call with descriptor `802d391c`, actor+`624`, mask `0x200`. A runtime
supporting only the first three machines should refuse at **`80068640`**, not
return early on a no-hit and not re-clear `5d4`. The caller's sole earlier
`5d4` zero store is at `800685e4`, before the first machine. First- and
second-machine effects and actual third-machine effects remain visible when
the fourth call refuses. The state pointer advances from `61c` to **`624`**,
not `620`; this evidence supplies no meaning or ownership for bytes `620..623`.

This extension supplies no fourth state owner, fourth descriptor data, later
machine, charge function `800686f0`, physical pad capture or production wiring.
Do not preload fourth-machine state/data to perform the first three machines.
The exact continuation and absence of caller stores are established by all 12
authenticated instructions, not an omission inferred from the C export.

## Validation and limits

Run from the repository root:

```
python -m unittest discover -s research/tools/matching-decomp -p 'test_archived_third_input_machine_evidence.py' -v
python -m unittest discover -s research/tools/matching-decomp -p 'test_archived_*evidence.py'
```

The dedicated suite passed **12 tests, no skips**. The complete archived
evidence suite in this workspace passed **401 tests, no skips**. Both standalone
reader invocations succeeded. Tests independently spell out all 12 instruction
operands, including both return-discarding register copies, check the six
expected fields and exact spans in both archives, mutate each instruction and
descriptor byte, and verify authentication, mapping, strict type, digest,
range, decoder-form, no-raw-output and arbitrary-CLI refusals.

These are archived-source and synthetic reader tests, not runtime integration,
original-game replay, ownership provenance or playable acceptance. Contributor
and documentation aggregate checks belong to the integration task. This
evidence task changed only its new reader, test and note, with no installs,
acquisitions, archive/original execution, rig or process work, commit or
publication.
