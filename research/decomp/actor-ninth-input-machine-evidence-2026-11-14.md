# Ninth actor input machine: archived source evidence

## Scope and authentication

This bounded extension of the
[first-machine evidence](actor-input-machine-evidence-2026-11-13.md) and
[eighth-machine evidence](actor-eighth-input-machine-evidence-2026-11-14.md)
authenticates the ninth descriptor and every caller instruction after the
eighth return through the tenth call. It reuses the separately authenticated
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
[`read_archived_ninth_input_machine_evidence.py`](../tools/matching-decomp/read_archived_ninth_input_machine_evidence.py)
authenticates the full snapshot, schemas, executable metadata, empty File Bytes
table, maps, full data5 digest and existing controls before its new fixed reads.
It then validates exact text/data3/data5 mapping identities. Width and digest
checks precede decoding or descriptor interpretation. The only additions are:

- Caller `800686a4..800686d4`: 48 bytes, all 12 instructions, SHA-256
  `46cda4dacae8063b1b784e11500b4d733b5d0db253610752afc232b9baf80ad8`.
- Ninth descriptor `802d3958..802d3964`: 12 bytes, SHA-256
  `521152c5a5eb1552b6b6296d55c24ad00596a2bc0e6729e56e1a4cedfc99cb4a`.

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
chain offset 405700, data offset 12628, physical offset 782682, length 48.

Descriptor fields use `MAIN_.data3`, block/subblock 5, start `802bae60`,
end-exclusive `803af120`, length `0xf42c0` and chain root 199. The single
obfuscated span has data buffer 206, chain offset 101112, data offset 2844,
physical offset 3394338, length 12. Both mappings require subblock type 2,
starting offset 0 and source offset 0.

## Ninth descriptor and state mapping

The six decoded big-endian u16 cells at `802d3958` are:

- +0: 1, the handler's mode/count field.
- +2: **0**, flags.
- +4: 0, the phase-1 timer reload.
- +6: **1**, the successful phase-2 tail duration.
- +8: **`0x0010`**, mask index 0.
- +10: 0, mask index 1.

The ninth input mask and wrapper result mask both equal `0x10`, but they have
independent sources and roles: the input mask is descriptor+8, tested against
actor+`5bc`, while the result mask is the caller's r6 argument, ORed into
actor+`5d4`. Numeric equality does not identify a physical input or downstream
meaning. The ninth shares flags 0 and duration 1 with the eighth but uses
**`0x10`**, not the eighth's input mask `0x40` or result mask 8. It must not
inherit the sixth's flags 4/input mask `0x100`, the fifth's duration 16 or the
seventh's input mask `0x20`.

Selected descriptor storage ends at the tenth descriptor address `802d3964`,
independently formed by the caller. No bytes at that next address are read.
A bounded implementation may admit only these six halfwords even if supplied
a longer view. Mask index 2 or greater must refuse at the actual indexed read,
preserving preceding stores. This host bound is not an original range check
or proof of a complete retail structure declaration.

The ninth call at `800686b8` targets `80068b8c` with r3 actor,
r4 `802d3958`, r5 actor+`0x610`, and r6 `0x10`. The shared handlers' p[0..3]
therefore refer to actor bytes `610`, `611`, `612`, `613`:

- `610`: phase byte selecting one of the three authenticated handlers.
- `611`: timer byte, decremented and signed-byte-tested by phases 1 and 2.
- `612`: mask index byte.
- `613`: wrapper tail byte, decremented when nonzero before the edge OR.

This placement supplies no ownership or initialization provenance. The wrapper's
dispatch lookup has no original phase bound; a runtime limited to the three
authenticated targets must refuse phase values outside 0, 1 and 2 at that
reached lookup. The tenth state pointer is actor+`628`, **not actor+`614`**;
the caller does not continue the recent four-byte stride.

## Shared-handler semantics and exact source order

The following behavior comes from the separately authenticated shared-handler
evidence, not extra ranges added to this reader. Phase 0 stores p[2]=0 at
`80068c24`, reads mode 1, stores p[0]=2 at `80068c3c` and p[1]=127 at
`80068c40`, then calls phase 2 with the same arguments at `80068c44`.
Phase 2 decrements that timer to 126 in the same wrapper invocation. There is
no input snapshot or control read before those stores.

For retained or freshly entered phase 2:

1. Load the timer, subtract 1, sign-extend the low byte and store the low byte
   at `80068d10`. Zero or a negative signed result clears the phase and returns
   0 before reading flags, input, index or descriptor mask. In particular,
   timer `0x80` becomes `0x7f` and continues, but `0x81` becomes `0x80` and
   expires. Timer 0 becomes `0xff` and expires; this is not saturation.
2. On a positive timer result, load descriptor flags 0. All three conditional
   control gates are skipped. **No actor+`5e0` or actor+`5b4` read is reached**.
   The ninth must not inherit the sixth descriptor's flag-4 control gate.
3. Flags bit 0 is clear, so load the actual actor+`5bc` match word at
   `80068d90`, then p[2] at `80068d94`, then descriptor u16 at
   `8 + 2*p[2]` at `80068da4`. These are reached reads in that order,
   not input/index snapshots from before the phase-0 or timer writes.
4. Flags bit 4 (`0x10`) is clear, so match **all** mask bits. Index 0 requires
   `0x10`; index 1's zero mask matches. Index 2 or greater exceeds the
   authenticated descriptor storage and must refuse at that mask read after
   the already reached timer store, input read and index read. The numeric
   value `0x10` in the separate input-mask field does not set flags bit 4.
5. On a match, clear p[0] first at `80068de0`, then load duration 1 at
   `80068de4`, store p[3]=1 at `80068de8` and return handler 1. A late
   failure retains every preceding write.

Retained phase 1 uses its separate any-bit match path, even though fresh phase
0 with mode 1 does not enter it. After the timer decrement/store and positive
signed-byte test, it reads the index at `80068ca8`, actor+`5bc` at `80068cac`,
then the indexed mask at `80068cb8`. Index 0 matches `0x10`; success loads
timer reload 0 and stores it, reloads the index at `80068ccc`, increments and
stores index 0 to 1, then compares that byte with mode 1 minus 1. The unequal
result leaves phase 1. Index 1's zero mask never matches in phase 1. Index 2
or greater refuses at the mask read after the already reached timer store,
index read and input read. Neither phase borrows the tenth descriptor to
satisfy an out-of-bounds mask index.

The wrapper ignores the handler return and then loads `613` at `80068bcc`.
Zero returns 0 without reading or writing `5d4`. Any nonzero byte, including
`0x80..0xff`, is decremented and stored at `80068be8` before the load of
actor+`5d4` at `80068bec`, OR with **`0x10`** and store at `80068bf4`.
The wrapper returns 1. This is a nonzero check, not the handler's
signed-positive timer test.

A successful ninth phase-2 match clears `610`, loads duration 1 into `613`,
then the wrapper consumes that byte to 0 and ORs `0x10`. A preexisting nonzero
`613` can still trigger the suffix after a handler no-hit or timer expiry.
A later `5d4` access failure cannot roll back the tail decrement. These source
operations do not prove a live frame duration, controller capture, actor
ownership, or any downstream interpretation of result bit `0x10`.

## Exact caller continuation and next unsupported call

After the eighth wrapper call at `800686a0` returns, all six instructions are:

1. `800686a4`: `addis r4,r0,-32723`, loading the descriptor high half.
2. `800686a8`: `or r3,r31,r31`, copying the actor and discarding return r3.
3. `800686ac`: `addi r4,r4,0x3958`, forming descriptor `802d3958`.
4. `800686b0`: `addi r5,r31,0x610`, setting the ninth state pointer.
5. `800686b4`: `addi r6,r0,0x10`, setting the ninth wrapper result mask.
6. `800686b8`: `bl 80068b8c`, making the ninth call.

After the ninth call returns, all six instructions are:

1. `800686bc`: `addis r4,r0,-32723`, loading the descriptor high half.
2. `800686c0`: `or r3,r31,r31`, copying the actor and discarding return r3.
3. `800686c4`: `addi r4,r4,0x3964`, forming descriptor `802d3964`.
4. `800686c8`: `addi r5,r31,0x628`, setting the tenth state pointer.
5. `800686cc`: `addi r6,r0,0x2000`, setting the tenth wrapper result mask.
6. `800686d0`: `bl 80068b8c`, making the tenth call.

There are **no caller return-dependent stores, loads, comparisons or
conditional branches** between the ninth and tenth calls. Either real
wrapper return 0 or return 1 reaches the tenth call with descriptor
`802d3964`, actor+`628`, mask `0x2000`. A runtime supporting only the first
nine machines should refuse at **`800686d0`**, not stop on ninth no-hit and
not re-clear `5d4`. The caller's sole earlier `5d4` zero store is at
`800685e4`, before the first machine, as established by the separate
complete-caller evidence. Effects of the first eight machines and actual
ninth-machine writes remain visible at tenth-call refusal. No tenth state
owner or descriptor contents should be preloaded to perform the first nine
machines.

The tenth pointer jumps 24 bytes from `610` to `628`. This does not authorize
reading the intervening bytes or establish their ownership. The descriptor
pointer advances 12 bytes from `802d3958` to `802d3964`, independently bounding
the selected ninth storage. The tenth result mask `0x2000` supplies no tenth
input-mask evidence.

This extension supplies no tenth descriptor data, tenth state owner, later
machine, charge function `800686f0`, physical pad capture or production wiring.
Return discard and absence of caller stores are established by all 12
authenticated instructions, not inferred from omitted C-export code.

## Validation and limits

Run from the repository root:

```
python -m unittest discover -s research/tools/matching-decomp -p 'test_archived_ninth_input_machine_evidence.py' -v
python -m unittest discover -s research/tools/matching-decomp -p 'test_archived_*evidence.py'
```

The dedicated suite passed **16 tests, no skips**. The complete archived
evidence suite passed **502 tests, no skips** in this workspace. Both standalone
reader invocations succeeded and their selected operands, fields and spans
matched. Whitespace checks passed.

Tests independently spell out all 12 instruction operands, including both
return-discarding copies, check the six expected fields and exact spans in both
archives, and derive the 12-byte descriptor bound from the two caller
addresses. They verify separate descriptor/caller sources for the two `0x10`
masks, the tenth state jump to `628` rather than `614` and the tenth mask
`0x2000`. They identify the next unsupported call at `800686d0` and reject
tenth descriptor reads; runtime refusal at that call is a separate check.

They mutate every caller and descriptor byte and verify authentication,
mapping, strict type, digest, short/long read, range, decoder-form, no-raw-output
and arbitrary-CLI refusals. Independent descriptor-value checks reject
substitutions of sixth-machine flags 4 or mask `0x100`, fifth-machine duration
16, seventh-machine mask `0x20`, eighth-machine mask `0x40` or result mask 8,
and tenth result mask `0x2000`, even with corresponding synthetic digests.
Additional checks prove exact chain read extents and that shared-reader and
eighth-reader allowlists still reject the new spans.

These are archived-source and synthetic reader tests, not runtime integration,
original-game replay, ownership provenance or playable acceptance. Contributor
and documentation aggregate checks belong to the integration task. This
evidence task changes only its new reader, test and note, with no installs,
acquisitions, archive/original execution, rig or process controls, commit or
publication.
