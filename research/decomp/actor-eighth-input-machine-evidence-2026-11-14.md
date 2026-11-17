# Eighth actor input machine: archived source evidence

## Scope and authentication

This bounded extension of the
[first-machine evidence](actor-input-machine-evidence-2026-11-13.md) and
[seventh-machine evidence](actor-seventh-input-machine-evidence-2026-11-14.md)
authenticates the eighth descriptor and every caller instruction from the
seventh return through the ninth call. It reuses the separately authenticated
wrapper `80068b8c`, three handlers and dispatch table `802d3988`. It does not
execute original or archived instructions, acquire inputs, change shared reader
allowlists, authenticate an unchanged original DOL, establish actor ownership
or enable production wiring.

The existing local ProgramDB inputs are in
`GotchaForce.rep.before_force_create/idata/00/~00000000.db/`:

- `db.3.gbf`: SHA-256
  `7b50dd2d2e17b4bfcc89a64cde27010247d0cbf0f48bd5c059f50275f40458d0`.
- `db.4.gbf`: SHA-256
  `1f86813d91ea8e2c4564f96622ec42555e1dba2c78aa81ad654e892140d019f8`.

The dedicated reader
[`read_archived_eighth_input_machine_evidence.py`](../tools/matching-decomp/read_archived_eighth_input_machine_evidence.py)
authenticates the full snapshot, schemas, executable metadata, empty File Bytes
table, maps, full data5 digest and existing controls before its new fixed reads.
It then validates exact text/data3/data5 mapping identities. Width and digest
checks precede decoding or descriptor interpretation. The only additions are:

- Caller `8006868c..800686bc`: 48 bytes, all 12 instructions, SHA-256
  `691f637f2fa6c6f69883c2d0d10b1e029f6f4bc101898aa54178a3fb0f529d74`.
- Eighth descriptor `802d394c..802d3958`: 12 bytes, SHA-256
  `2f0de5694a0c0985a37ba4b182616611f99ebea8a5686b6e34657b9353824b30`.

Both archives yield identical operands, fields and physical spans. The selected
caller span has zero unrepresented instructions; this is not a complete-function
claim. The complete caller has separate
[input-prefix evidence](actor-input-prefix-evidence-2026-11-13.md).
There are no arbitrary-address, width, raw-output or execution options.
Output contains only derived operands, typed fields, hashes, provenance and
spans. The executable hash property is metadata, not original-DOL equality.

### Maps and physical spans

Caller instructions use `MAIN_.text1`, block/subblock 1, start `800055e0`,
length 2796416 and chain root 21. The single obfuscated span has data buffer 46,
chain offset 405676, data offset 12604, physical offset 782658, length 48.

Descriptor fields use `MAIN_.data3`, block/subblock 5, start `802bae60`,
end-exclusive `803af120`, length `0xf42c0` and chain root 199. The single
obfuscated span has data buffer 206, chain offset 101100, data offset 2832,
physical offset 3394326, length 12. Both mappings require subblock type 2,
starting offset 0 and source offset 0.

## Eighth descriptor and state mapping

The six decoded big-endian u16 cells at `802d394c` are:

- +0: 1, the handler's mode/count field.
- +2: **0**, flags.
- +4: 0, the phase-1 timer reload.
- +6: **1**, the successful phase-2 tail duration.
- +8: **`0x0040`**, mask index 0.
- +10: 0, mask index 1.

The eighth input mask is `0x40`, distinct from its wrapper result mask 8.
The eighth descriptor shares flags 0 and duration 1 with the seventh but uses
**`0x40`**, not the seventh's `0x20`. It must not inherit the sixth descriptor's
flags 4/input mask `0x100` or the fifth descriptor's duration 16. No physical
button, directional action, angular change or downstream consumer is identified.

Selected descriptor storage ends at the ninth descriptor address `802d3958`,
independently formed by the caller. No bytes at that next address are read.
A bounded implementation may admit only these six halfwords even if supplied
a longer view. Mask index 2 or greater must refuse at the actual indexed read,
preserving preceding stores. This host bound is not an original range check
or proof of a complete retail structure declaration.

The eighth call at `800686a0` targets `80068b8c` with r3 actor,
r4 `802d394c`, r5 actor+`0x60c`, and r6 `8`. The shared handlers' p[0..3]
therefore refer to actor bytes `60c`, `60d`, `60e`, `60f`:

- `60c`: phase byte selecting one of the three authenticated handlers.
- `60d`: timer byte, decremented and signed-byte-tested by phases 1 and 2.
- `60e`: mask index byte.
- `60f`: wrapper tail byte, decremented when nonzero before the edge OR.

This placement supplies no ownership or initialization provenance, including
for adjacent bytes. The wrapper's dispatch lookup has no original phase bound;
a runtime limited to the three authenticated targets must refuse phase values
outside 0, 1 and 2 at that reached lookup.

### Flags-zero path and exact source order

The following behavior comes from the separately authenticated shared-handler
evidence, not extra reads by this extension. Phase 0 stores p[2]=0, reads mode 1,
stores p[0]=2 and p[1]=127, then immediately calls phase 2 with the same
arguments. Phase 2 decrements that timer to 126 in the same wrapper invocation.
There is no input snapshot or control read before those stores.

For retained or freshly entered phase 2:

1. Load the timer, subtract 1, sign-extend the low byte and store the low byte.
   Zero or a negative signed result clears the phase and returns 0 before
   reading flags, input, index or descriptor mask. In particular, timer `0x80`
   becomes `0x7f` and continues, but timer `0x81` becomes `0x80` and expires.
2. On a positive timer result, load descriptor flags 0. All three conditional
   control gates are skipped. **No actor+`5e0` or actor+`5b4` read is reached**.
   The eighth must not inherit the sixth descriptor's flag-4 control gate.
3. Flags bit 0 is clear, so load the actual actor+`5bc` match word, then p[2],
   then descriptor u16 at `8 + 2*p[2]`. These are reached reads in that order,
   not input/index snapshots from before the phase-0 or timer writes.
4. Flags bit 4 (`0x10`) is clear, so match **all** mask bits. Index 0 requires
   `0x40`; index 1's zero mask matches. Index 2 or greater exceeds the
   authenticated descriptor storage and must refuse at that mask read after
   the already reached timer store, input read and index read.
5. On a match, clear p[0] first, then load duration 1, store p[3]=1 and
   return handler 1. A late failure retains every preceding write.

Retained phase 1 uses its separate any-bit match path. After the timer decrement
and positive signed-byte test, it reads the index, actor+`5bc`, then the indexed
mask. Index 0 matches `0x40`; success loads timer reload 0 and stores it, reloads
the index, increments/stores index 0 to 1, then compares that byte with
mode 1 minus 1. The unequal result leaves phase 1. Index 1's zero mask never
matches in phase 1. Index 2 or greater refuses at the mask read after the
already reached timer store, index read and input read. Neither phase borrows
the ninth descriptor to satisfy an out-of-bounds mask index.

The wrapper ignores the handler return and then loads `60f`. Zero returns 0
without reading or writing `5d4`. Any nonzero byte, including `0x80..0xff`,
is decremented and stored before the read/OR/store of actor+`5d4` with **8**,
and the wrapper returns 1. This is a nonzero check, not the handler's
signed-positive timer test.

A successful eighth phase-2 match clears `60c`, loads duration 1 into `60f`,
then the wrapper consumes that byte to 0 and ORs 8. A preexisting nonzero
`60f` can still trigger the suffix after a handler no-hit or timer expiry.
A later `5d4` access failure cannot roll back the tail decrement. These source
operations do not prove a live frame duration, controller capture, actor
ownership, or any downstream interpretation of result bit 8.

## Exact caller continuation and next unsupported call

After the seventh wrapper call at `80068688` returns, all six instructions are:

1. `8006868c`: `addis r4,r0,-32723`, loading the descriptor high half.
2. `80068690`: `or r3,r31,r31`, copying the actor and discarding return r3.
3. `80068694`: `addi r4,r4,0x394c`, forming descriptor `802d394c`.
4. `80068698`: `addi r5,r31,0x60c`, setting the eighth state pointer.
5. `8006869c`: `addi r6,r0,8`, setting the eighth wrapper result mask.
6. `800686a0`: `bl 80068b8c`, making the eighth call.

After the eighth call returns, all six instructions are:

1. `800686a4`: `addis r4,r0,-32723`, loading the descriptor high half.
2. `800686a8`: `or r3,r31,r31`, copying the actor and discarding return r3.
3. `800686ac`: `addi r4,r4,0x3958`, forming descriptor `802d3958`.
4. `800686b0`: `addi r5,r31,0x610`, setting the ninth state pointer.
5. `800686b4`: `addi r6,r0,16`, setting the ninth wrapper result mask.
6. `800686b8`: `bl 80068b8c`, making the ninth call.

There are **no caller return-dependent stores, loads, comparisons or
conditional branches** between the eighth and ninth calls. Either real
wrapper return 0 or return 1 reaches the ninth call with descriptor
`802d3958`, actor+`610`, mask 16. A runtime supporting only the first eight
machines should refuse at **`800686b8`**, not stop on eighth no-hit and not
re-clear `5d4`. The caller's sole earlier `5d4` zero store is at `800685e4`,
before the first machine, as established by the separate complete-caller
evidence. Effects of the first seven machines and actual eighth-machine writes
remain visible at ninth-call refusal. No ninth state owner or descriptor
contents should be preloaded to perform the first eight machines.

This extension supplies no ninth descriptor data, ninth state owner,
later machine, charge function `800686f0`, physical pad capture or production
wiring. Return discard and absence of caller stores are established by all
12 authenticated instructions, not inferred from omitted C-export code.

## Validation and limits

Run from the repository root:

```
python -m unittest discover -s research/tools/matching-decomp -p 'test_archived_eighth_input_machine_evidence.py' -v
python -m unittest discover -s research/tools/matching-decomp -p 'test_archived_*evidence.py'
```

The dedicated suite passed **15 tests, no skips**. The complete archived
evidence suite passed **486 tests, no skips** in this workspace. Both standalone
reader invocations succeeded and their selected operands, fields and spans
matched. Whitespace checks passed.

Tests independently spell out all 12 instruction operands, including both
return-discarding copies, check the six expected fields and exact spans in both
archives, derive the 12-byte descriptor bound from the two caller addresses,
and distinguish flags 0/duration 1/input mask `0x40`/result mask 8. They mutate
every caller and descriptor byte and verify authentication, mapping, strict
type, digest, short/long read, range, decoder-form, no-raw-output and
arbitrary-CLI refusals. Independent descriptor-value checks reject substitutions
of sixth-machine flags 4 or mask `0x100`, fifth-machine duration 16,
seventh-machine mask `0x20` and eighth result mask 8 even with corresponding
synthetic digests. Additional checks prove exact chain read extents and that
shared-reader and seventh-reader allowlists still reject the new spans.

These are archived-source and synthetic reader tests, not runtime integration,
original-game replay, ownership provenance or playable acceptance. Contributor
and documentation aggregate checks belong to the integration task. This
evidence task changes only its new reader, test and note, with no installs,
acquisitions, archive/original execution, rig or process controls, commit or
publication.
