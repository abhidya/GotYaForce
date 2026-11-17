# Sixth actor input machine: archived source evidence

## Scope and authentication

This bounded extension of the
[first-machine evidence](actor-input-machine-evidence-2026-11-13.md) and
[fifth-machine evidence](actor-fifth-input-machine-evidence-2026-11-14.md)
authenticates the sixth descriptor and all caller instructions from the fifth
return through the seventh call. It reuses the authenticated wrapper
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
[`read_archived_sixth_input_machine_evidence.py`](../tools/matching-decomp/read_archived_sixth_input_machine_evidence.py)
authenticates the full snapshot, schemas, executable metadata, empty File Bytes
table, maps, full data5 digest and existing controls before its new fixed reads.
It then validates exact text/data3/data5 mapping identities. Width and digest
checks precede decoding or descriptor interpretation. The only additions are:

- Caller `8006865c..8006868c`: 48 bytes, all 12 instructions, SHA-256
  `313dcf1dd549adcfd03f55647262d188f818286833997cd47ed57163dc96fcec`.
- Sixth descriptor `802d3934..802d3940`: 12 bytes, SHA-256
  `1c714deb006615ebb446ab020905dad83175889f05efc957a284e715242904ca`.

Both archives yield identical operands, fields and physical spans. This
selected caller span has zero unrepresented instructions; it is not a
complete-function claim. The complete caller has separate
[input-prefix evidence](actor-input-prefix-evidence-2026-11-13.md).
The reader has no arbitrary-address, width, raw-output or execution options.
Output contains only derived operands, typed fields, hashes, provenance and
spans. The executable hash property is metadata, not original-DOL equality.

### Maps and physical spans

Caller instructions use `MAIN_.text1`, block/subblock 1, start `800055e0`,
length 2796416 and chain root 21. The single obfuscated span has data buffer 46,
chain offset 405628, data offset 12556, physical offset 782610, length 48.

Descriptor fields use `MAIN_.data3`, block/subblock 5, start `802bae60`,
end-exclusive `803af120`, length `0xf42c0` and chain root 199. The single
obfuscated span has data buffer 206, chain offset 101076, data offset 2808,
physical offset 3394302, length 12. Both mappings require subblock type 2,
starting offset 0 and source offset 0.

## Sixth descriptor and state mapping

The six decoded big-endian u16 cells at `802d3934` are:

- +0: 1, the handler's mode/count field.
- +2: **4**, flags.
- +4: 0, the phase-1 timer reload.
- +6: **1**, the successful phase-2 tail duration.
- +8: **`0x0100`**, mask index 0.
- +10: 0, mask index 1.

The sixth input mask is `0x100`, distinct from its wrapper result mask 2.
Although the input mask equals the fifth descriptor's input mask, the sixth
has **flags 4 and duration 1**, not fifth-machine flags 0 and duration 16.
Selected descriptor storage ends at the seventh descriptor address
`802d3940`, independently formed by the caller. No bytes at that next
address are read. A bounded implementation may admit only these six halfwords
even if supplied a longer view. Mask index 2 or greater must refuse at the
actual indexed read, preserving preceding stores. This host bound is not an
original range check or proof of a complete retail structure declaration.

The sixth call at `80068670` targets `80068b8c` with r3 actor,
r4 `802d3934`, r5 actor+`0x604`, and r6 `2`. The shared handlers' p[0..3]
therefore refer to actor bytes `604`, `605`, `606`, `607`:

- `604`: phase byte selecting one of the three authenticated handlers.
- `605`: timer byte, decremented and signed-byte-tested by phases 1 and 2.
- `606`: mask index byte.
- `607`: wrapper tail byte, decremented when nonzero before the edge OR.

### Required flag-4 gate and source order

The existing shared-handler evidence supplies the following interpretation,
not additional reads by this extension. Phase 0 with mode 1 stores index 0,
phase 2 and timer 127, then immediately calls phase 2 with the same arguments.
Phase 2 decrements the timer to 126 in that same wrapper invocation. It does
not snapshot input or control before those stores.

For a retained or freshly entered phase 2:

1. Load the timer, subtract 1, sign-extend the low byte and store the low byte.
   Zero or a negative signed result clears the phase and returns 0 before
   reading flags, control, input, index or descriptor mask.
2. On a positive timer result, load descriptor flags. Flags 4 skips the bit-1
   (`0x2`) gate and reaches the bit-2 (`0x4`) gate: load actual actor+`5e0`
   **once** and require its bit `0x40` to be set. A clear bit returns handler 0
   before reading actor+`5bc`, the index or the descriptor mask.
3. Flags 4 skips the bit-3 gate and bit-0 input selection, so no actor+`5b4`
   read is reached. After the control gate passes, load actual actor+`5bc`,
   then p[2], then descriptor u16 at `8 + 2*p[2]`.
4. Flags bit 4 (`0x10`) is clear, so match **all** mask bits. Index 0 requires
   `0x100`; index 1's zero mask matches, but only after the control gate has
   passed. Index 2 or greater exceeds the authenticated descriptor storage
   and must refuse at that read after the already reached timer store,
   control read, input read and index read.
5. On a match, clear p[0] first, then load duration 1, store p[3]=1 and
   return handler 1. A late failure preserves every preceding write.

Retained phase 1 uses its separate any-bit match path and does not apply the
phase-2 flag-4 control gate. After its timer decrement and positive signed-byte
test, it reads the index, actor+`5bc`, then the indexed mask. Index 0 matches
`0x100`; success reloads timer 0 and increments index 0 to 1, which does not
match mode 1 minus 1, leaving phase 1. Index 1's zero mask never matches in
this phase. Its lazy descriptor-bound refusal also retains earlier writes.

The wrapper ignores the handler return and then loads `607`. Any nonzero
byte is decremented before the read/OR/store of actor+`5d4` with **2**, and
the wrapper returns 1. Zero returns 0 without reading or writing `5d4`.
A successful sixth phase-2 match therefore clears `604`, loads duration 1
into `607`, then the wrapper consumes that byte to 0 and ORs 2. It must not
retain the fifth descriptor's duration-16 behavior. A preexisting nonzero
`607` can still trigger this suffix after a handler no-hit, control-gate
failure or timer expiry. This is not proof of one live frame, physical-button
mapping, input capture or any angular effect.

## Exact caller continuation and next unsupported call

After the fifth wrapper call at `80068658` returns, the six instructions are:

1. `8006865c`: `addis r4,r0,-32723`, loading the descriptor high half.
2. `80068660`: `or r3,r31,r31`, copying the actor and discarding return r3.
3. `80068664`: `addi r4,r4,0x3934`, forming descriptor `802d3934`.
4. `80068668`: `addi r5,r31,0x604`, setting the sixth state pointer.
5. `8006866c`: `addi r6,r0,2`, setting the wrapper result mask.
6. `80068670`: `bl 80068b8c`, making the sixth call.

After the sixth call returns, the six instructions are:

1. `80068674`: `addis r4,r0,-32723`, loading the descriptor high half.
2. `80068678`: `or r3,r31,r31`, copying the actor and discarding return r3.
3. `8006867c`: `addi r4,r4,0x3940`, forming descriptor `802d3940`.
4. `80068680`: `addi r5,r31,0x608`, setting the seventh state pointer.
5. `80068684`: `addi r6,r0,4`, setting the seventh wrapper result mask.
6. `80068688`: `bl 80068b8c`, making the seventh call.

There are **no caller return-dependent stores, loads, comparisons or
conditional branches** between the sixth and seventh calls. Either real
wrapper return 0 or return 1 reaches the seventh call with descriptor
`802d3940`, actor+`608`, mask 4. A runtime supporting only the first six
machines should refuse at **`80068688`**, not stop on sixth no-hit and not
re-clear `5d4`. The caller's sole earlier `5d4` zero store is at `800685e4`,
before the first machine, as established by the separate complete-caller
evidence. Effects of the first five machines and actual sixth-machine writes
remain visible at seventh-call refusal. No seventh state owner or descriptor
contents should be preloaded to perform the first six machines.

This extension supplies no seventh descriptor data, seventh state owner,
later machine, charge function `800686f0`, physical pad capture or production
wiring. Sixth state placement supplies no meaning or ownership for adjacent
actor bytes. Return discard and absence of caller stores are established by
all 12 authenticated instructions, not inferred from omitted C-export code.

## Validation and limits

Run from the repository root:

```
python -m unittest discover -s research/tools/matching-decomp -p 'test_archived_sixth_input_machine_evidence.py' -v
python -m unittest discover -s research/tools/matching-decomp -p 'test_archived_*evidence.py'
```

The dedicated suite passed **13 tests, no skips**. The complete archived
evidence suite passed **456 tests, no skips** in this workspace. Both standalone
reader invocations succeeded; whitespace checks passed. Tests independently spell out all 12 instruction
operands, including both return-discarding copies, check the six expected
fields and exact spans in both archives, derive the 12-byte descriptor bound
from the two caller addresses, distinguish flags 4/duration 1/input mask
`0x100`/result mask 2, mutate every caller and descriptor byte, and verify
authentication, mapping, strict type, digest, range, decoder-form,
no-raw-output and arbitrary-CLI refusals. Independent descriptor-value checks
also reject substitutions of fifth-machine flags 0 and duration 16 even when
a corresponding synthetic digest is supplied.

These are archived-source and synthetic reader tests, not runtime integration,
original-game replay, ownership provenance or playable acceptance. Contributor
and documentation aggregate checks belong to the integration task. This
evidence task changes only its new reader, test and note, with no installs,
acquisitions, archive/original execution, rig or process work, commit or
publication.
