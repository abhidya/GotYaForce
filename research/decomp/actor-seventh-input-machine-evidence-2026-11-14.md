# Seventh actor input machine: archived source evidence

## Scope and authentication

This bounded extension of the
[first-machine evidence](actor-input-machine-evidence-2026-11-13.md) and
[sixth-machine evidence](actor-sixth-input-machine-evidence-2026-11-14.md)
authenticates the seventh descriptor and every caller instruction from the
sixth return through the eighth call. It reuses the authenticated wrapper
`80068b8c`, three handlers and dispatch table `802d3988`. It does not execute
original or archived instructions, acquire inputs, change shared reader
allowlists, authenticate an unchanged original DOL, establish actor ownership
or enable production wiring.

The existing local ProgramDB inputs are in
`GotchaForce.rep.before_force_create/idata/00/~00000000.db/`:

- `db.3.gbf`: SHA-256
  `7b50dd2d2e17b4bfcc89a64cde27010247d0cbf0f48bd5c059f50275f40458d0`.
- `db.4.gbf`: SHA-256
  `1f86813d91ea8e2c4564f96622ec42555e1dba2c78aa81ad654e892140d019f8`.

The dedicated reader
[`read_archived_seventh_input_machine_evidence.py`](../tools/matching-decomp/read_archived_seventh_input_machine_evidence.py)
authenticates the full snapshot, schemas, executable metadata, empty File Bytes
table, maps, full data5 digest and existing controls before its new fixed reads.
It then validates exact text/data3/data5 mapping identities. Width and digest
checks precede decoding or descriptor interpretation. The only additions are:

- Caller `80068674..800686a4`: 48 bytes, all 12 instructions, SHA-256
  `e33cc00a8ce3a41cb92c194e0172f462ab5cc6d31926cb8363fee9ddefe7d409`.
- Seventh descriptor `802d3940..802d394c`: 12 bytes, SHA-256
  `d111611a336b6c778b5777b2adabcc30e61542dc19b3bdcb7f231376930e2911`.

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
chain offset 405652, data offset 12580, physical offset 782634, length 48.

Descriptor fields use `MAIN_.data3`, block/subblock 5, start `802bae60`,
end-exclusive `803af120`, length `0xf42c0` and chain root 199. The single
obfuscated span has data buffer 206, chain offset 101088, data offset 2820,
physical offset 3394314, length 12. Both mappings require subblock type 2,
starting offset 0 and source offset 0.

## Seventh descriptor and state mapping

The six decoded big-endian u16 cells at `802d3940` are:

- +0: 1, the handler's mode/count field.
- +2: **0**, flags.
- +4: 0, the phase-1 timer reload.
- +6: **1**, the successful phase-2 tail duration.
- +8: **`0x0020`**, mask index 0.
- +10: 0, mask index 1.

The seventh input mask is `0x20`, distinct from its wrapper result mask 4.
The seventh descriptor has **flags 0**, not the sixth descriptor's flags 4,
and input mask **`0x20`**, not the fifth or sixth descriptor's `0x100`.
Its duration is 1, not the fifth descriptor's 16. No physical button,
directional action, angular change or downstream consumer is identified here.

Selected descriptor storage ends at the eighth descriptor address `802d394c`,
independently formed by the caller. No bytes at that next address are read.
A bounded implementation may admit only these six halfwords even if supplied
a longer view. Mask index 2 or greater must refuse at the actual indexed read,
preserving preceding stores. This host bound is not an original range check
or proof of a complete retail structure declaration.

The seventh call at `80068688` targets `80068b8c` with r3 actor,
r4 `802d3940`, r5 actor+`0x608`, and r6 `4`. The shared handlers' p[0..3]
therefore refer to actor bytes `608`, `609`, `60a`, `60b`:

- `608`: phase byte selecting one of the three authenticated handlers.
- `609`: timer byte, decremented and signed-byte-tested by phases 1 and 2.
- `60a`: mask index byte.
- `60b`: wrapper tail byte, decremented when nonzero before the edge OR.

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
   This must not inherit the sixth descriptor's flag-4 control gate.
3. Flags bit 0 is clear, so load the actual actor+`5bc` match word, then p[2],
   then descriptor u16 at `8 + 2*p[2]`. These are reached reads in that order,
   not input/index snapshots from before the phase-0 or timer writes.
4. Flags bit 4 (`0x10`) is clear, so match **all** mask bits. Index 0 requires
   `0x20`; index 1's zero mask matches. Index 2 or greater exceeds the
   authenticated descriptor storage and must refuse at that mask read after
   the already reached timer store, input read and index read.
5. On a match, clear p[0] first, then load duration 1, store p[3]=1 and
   return handler 1. A late failure retains every preceding write.

Retained phase 1 uses its separate any-bit match path. After the timer decrement
and positive signed-byte test, it reads the index, actor+`5bc`, then the indexed
mask. Index 0 matches `0x20`; success loads timer reload 0 and stores it, reloads
the index, increments/stores index 0 to 1, then compares that byte with
mode 1 minus 1. The unequal result leaves phase 1. Index 1's zero mask never
matches in phase 1. Index 2 or greater refuses at the mask read after the
already reached timer store, index read and input read. Neither phase borrows
the eighth descriptor to satisfy an out-of-bounds mask index.

The wrapper ignores the handler return and then loads `60b`. Zero returns 0
without reading or writing `5d4`. Any nonzero byte, including `0x80..0xff`,
is decremented and stored before the read/OR/store of actor+`5d4` with **4**,
and the wrapper returns 1. This is a nonzero check, not the handler's
signed-positive timer test.

A successful seventh phase-2 match clears `608`, loads duration 1 into `60b`,
then the wrapper consumes that byte to 0 and ORs 4. A preexisting nonzero
`60b` can still trigger the suffix after a handler no-hit or timer expiry.
A later `5d4` access failure cannot roll back the tail decrement. These source
operations do not prove a live frame duration, controller capture, actor
ownership, or any downstream interpretation of result bit 4.

## Exact caller continuation and next unsupported call

After the sixth wrapper call at `80068670` returns, all six instructions are:

1. `80068674`: `addis r4,r0,-32723`, loading the descriptor high half.
2. `80068678`: `or r3,r31,r31`, copying the actor and discarding return r3.
3. `8006867c`: `addi r4,r4,0x3940`, forming descriptor `802d3940`.
4. `80068680`: `addi r5,r31,0x608`, setting the seventh state pointer.
5. `80068684`: `addi r6,r0,4`, setting the seventh wrapper result mask.
6. `80068688`: `bl 80068b8c`, making the seventh call.

After the seventh call returns, all six instructions are:

1. `8006868c`: `addis r4,r0,-32723`, loading the descriptor high half.
2. `80068690`: `or r3,r31,r31`, copying the actor and discarding return r3.
3. `80068694`: `addi r4,r4,0x394c`, forming descriptor `802d394c`.
4. `80068698`: `addi r5,r31,0x60c`, setting the eighth state pointer.
5. `8006869c`: `addi r6,r0,8`, setting the eighth wrapper result mask.
6. `800686a0`: `bl 80068b8c`, making the eighth call.

There are **no caller return-dependent stores, loads, comparisons or
conditional branches** between the seventh and eighth calls. Either real
wrapper return 0 or return 1 reaches the eighth call with descriptor
`802d394c`, actor+`60c`, mask 8. A runtime supporting only the first seven
machines should refuse at **`800686a0`**, not stop on seventh no-hit and not
re-clear `5d4`. The caller's sole earlier `5d4` zero store is at `800685e4`,
before the first machine, as established by the separate complete-caller
evidence. Effects of the first six machines and actual seventh-machine writes
remain visible at eighth-call refusal. No eighth state owner or descriptor
contents should be preloaded to perform the first seven machines.

This extension supplies no eighth descriptor data, eighth state owner,
later machine, charge function `800686f0`, physical pad capture or production
wiring. Return discard and absence of caller stores are established by all
12 authenticated instructions, not inferred from omitted C-export code.

## Validation and limits

Run from the repository root:

```
python -m unittest discover -s research/tools/matching-decomp -p 'test_archived_seventh_input_machine_evidence.py' -v
python -m unittest discover -s research/tools/matching-decomp -p 'test_archived_*evidence.py'
```

The dedicated suite passed **15 tests, no skips**. The complete archived
evidence suite passed **471 tests, no skips** in this workspace. Both standalone
reader invocations succeeded and their selected operands, fields and spans
matched. Whitespace checks passed.

Tests independently spell out all 12 instruction operands, including both
return-discarding copies, check the six expected fields and exact spans in both
archives, derive the 12-byte descriptor bound from the two caller addresses,
and distinguish flags 0/duration 1/input mask `0x20`/result mask 4. They mutate
every caller and descriptor byte and verify authentication, mapping, strict
type, digest, short/long read, range, decoder-form, no-raw-output and
arbitrary-CLI refusals. Independent descriptor-value checks reject substitutions
of sixth-machine flags 4 or mask `0x100`, fifth-machine duration 16, and seventh
result mask 4 even with corresponding synthetic digests. Additional checks
prove exact chain read extents and that shared-reader allowlists still reject
the new spans.

These are archived-source and synthetic reader tests, not runtime integration,
original-game replay, ownership provenance or playable acceptance. Contributor
and documentation aggregate checks belong to the integration task. This
evidence task changes only its new reader, test and note, with no installs,
acquisitions, archive/original execution, rig or process controls, commit or
publication.
