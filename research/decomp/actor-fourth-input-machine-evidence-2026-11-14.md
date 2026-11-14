# Fourth actor input machine: archived source evidence

## Scope and authentication

This bounded extension of the
[first-machine evidence](actor-input-machine-evidence-2026-11-13.md) and
[third-machine evidence](actor-third-input-machine-evidence-2026-11-13.md)
authenticates the fourth descriptor and all caller instructions from the third
return through the fifth call. It reuses the authenticated wrapper `80068b8c`,
three handlers and dispatch table `802d3988`. It does not execute original or
archived instructions, acquire inputs, change shared reader allowlists,
authenticate an unchanged original DOL, establish actor ownership or enable
production wiring.

The existing local ProgramDB inputs are in
`GotchaForce.rep.before_force_create/idata/00/~00000000.db/`:

- `db.3.gbf`: SHA-256
  `7b50dd2d2e17b4bfcc89a64cde27010247d0cbf0f48bd5c059f50275f40458d0`.
- `db.4.gbf`: SHA-256
  `1f86813d91ea8e2c4564f96622ec42555e1dba2c78aa81ad654e892140d019f8`.

The dedicated reader
[`read_archived_fourth_input_machine_evidence.py`](../tools/matching-decomp/read_archived_fourth_input_machine_evidence.py)
authenticates the full snapshot, schemas, executable metadata, empty File Bytes
table, maps, full data5 digest and existing controls before its new fixed reads.
It then validates exact text/data3/data5 mapping identities. Width and digest
checks precede decoding or descriptor interpretation. The only additions are:

- Caller `8006862c..8006865c`: 48 bytes, all 12 instructions, SHA-256
  `a0cd0139728c2cb2d5c27cd0ea7844dd04c5c14f2dfa3f69d91f65847d88936c`.
- Fourth descriptor `802d391c..802d3928`: 12 bytes, SHA-256
  `3f1f43204cd8a201fad7078fbd71d371157b516258ae84e1ae08dc1c29bd7caa`.

Both archives yield identical operands, fields and physical spans. This selected
caller span has zero unrepresented instructions; it is not a complete-function
claim. The complete caller has separate
[input-prefix evidence](actor-input-prefix-evidence-2026-11-13.md).
The reader has no arbitrary-address, width, raw-output or execution options.
Output contains only derived operands, typed fields, hashes, provenance and
spans. The executable hash property is metadata, not original-DOL equality.

### Maps and physical spans

Caller instructions use `MAIN_.text1`, block/subblock 1, start `800055e0`,
length 2796416 and chain root 21. The single obfuscated span has data buffer 46,
chain offset 405580, data offset 12508, physical offset 782562, length 48.

Descriptor fields use `MAIN_.data3`, block/subblock 5, start `802bae60`,
end-exclusive `803af120`, length `0xf42c0` and chain root 199. The single
obfuscated span has data buffer 206, chain offset 101052, data offset 2784,
physical offset 3394278, length 12. Both mappings require subblock type 2,
starting offset 0 and source offset 0.

## Fourth descriptor and state mapping

The six decoded big-endian u16 cells at `802d391c` are:

- +0: 1, the handler's mode/count field.
- +2: 0, flags.
- +4: 0, the phase-1 timer reload.
- +6: 1, the successful phase-2 tail duration.
- +8: `0x0800`, mask index 0.
- +10: 0, mask index 1.

The fourth input mask is **`0x800`**, not the third descriptor's `0x400` and
not the fourth wrapper's result mask `0x200`. Selected descriptor storage ends
at the fifth descriptor address `802d3928`, independently named by the caller.
No bytes at that next descriptor address are read. A bounded implementation
may admit only these six halfwords even if supplied a longer view. Mask index
2 or greater must refuse at the actual indexed read, preserving preceding
stores. This host bound is not an original range check or proof of a complete
retail structure declaration.

The fourth call at `80068640` targets `80068b8c` with r3 actor,
r4 `802d391c`, r5 actor+`0x624`, and r6 `0x200`. The shared handlers' p[0..3]
therefore refer to actor bytes `624`, `625`, `626`, `627`:

- `624`: phase byte selecting one of the three authenticated handlers.
- `625`: timer byte, decremented and signed-byte-tested by phases 1 and 2.
- `626`: mask index byte.
- `627`: wrapper tail byte, decremented when nonzero before the edge OR.

The existing shared-handler evidence supplies the following interpretation,
not additional reads by this extension. With flags0, phase 2 reads actual
actor+`5bc` without optional `5e0`/`5b4` gates. Index0 requires an all-bit match
on `0x800`; index1's zero mask matches in all-bit mode. Phase 1 uses any-bit
matching, so its zero mask does not match. Phase0/mode1 sets phase2 and
timer127, then immediately enters phase2, which decrements the timer to126
before testing input. Timer expiry, read/store order and lazy bounds remain
those authenticated for the shared handlers.

The wrapper ignores the handler return and then loads `627`. A nonzero byte
is decremented before the read/OR/store of actor+`5d4` with **`0x200`**, and
the wrapper returns1. Zero returns0 without reading or writing `5d4`.
A successful fixed-descriptor phase2 match clears `624`, loads duration1 into
`627`, then the wrapper consumes that byte to0 and ORs `0x200`. A preexisting
nonzero tail can also trigger this suffix after handler no-hit or expiry.
Late failures retain earlier writes.

## Exact caller continuation and next unsupported call

After the third wrapper call at `80068628` returns, the six instructions are:

1. `8006862c`: `addis r4,r0,-32723`, loading the descriptor high half.
2. `80068630`: `or r3,r31,r31`, copying the actor and discarding return r3.
3. `80068634`: `addi r4,r4,0x391c`, forming descriptor `802d391c`.
4. `80068638`: `addi r5,r31,0x624`, setting the fourth state pointer.
5. `8006863c`: `addi r6,r0,0x200`, setting the wrapper result mask.
6. `80068640`: `bl 80068b8c`, making the fourth call.

After the fourth call returns, the six instructions are:

1. `80068644`: `addis r4,r0,-32723`, loading the descriptor high half.
2. `80068648`: `or r3,r31,r31`, copying the actor and discarding return r3.
3. `8006864c`: `addi r4,r4,0x3928`, forming descriptor `802d3928`.
4. `80068650`: `addi r5,r31,0x600`, setting the fifth state pointer.
5. `80068654`: `addi r6,r0,1`, setting the fifth wrapper result mask.
6. `80068658`: `bl 80068b8c`, making the fifth call.

There are **no caller return-dependent stores, loads, comparisons or conditional
branches** between the fourth and fifth calls. Either real wrapper return0 or
return1 reaches the fifth call with descriptor `802d3928`, actor+`600`, mask1.
A runtime supporting only the first four machines should refuse at
**`80068658`**, not stop on fourth no-hit and not re-clear `5d4`. The caller's
sole earlier `5d4` zero store is at `800685e4`, before the first machine, as
established by the separate complete-caller evidence. Effects of the first
three machines and actual fourth-machine writes remain visible at fifth-call
refusal. No fifth state owner or descriptor contents should be preloaded to
perform the first four machines.

This extension supplies no fifth descriptor data, fifth state owner, later
machine, charge function `800686f0`, physical pad capture or production
wiring. Fourth state placement supplies no meaning or ownership for adjacent
actor bytes. Return discard and absence of caller stores are established by
all 12 authenticated instructions, not inferred from omitted C-export code.

## Validation and limits

Run from the repository root:

```
python -m unittest discover -s research/tools/matching-decomp -p 'test_archived_fourth_input_machine_evidence.py' -v
python -m unittest discover -s research/tools/matching-decomp -p 'test_archived_*evidence.py'
```

The dedicated suite passed **12 tests, no skips**. The complete archived
evidence suite in this workspace passed **430 tests, no skips**. Both standalone
reader invocations succeeded. Tests independently spell out all 12 instruction
operands, including both return-discarding copies, check the six expected
fields and exact spans in both archives, mutate every caller and descriptor
byte, and verify authentication, mapping, strict type, digest, range,
decoder-form, no-raw-output and arbitrary-CLI refusals.

These are archived-source and synthetic reader tests, not runtime integration,
original-game replay, ownership provenance or playable acceptance. Contributor
and documentation aggregate checks belong to the integration task. This
evidence task changes only its new reader, test and note, with no installs,
acquisitions, archive/original execution, rig or process work, commit or
publication.
