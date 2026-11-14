# Fifth actor input machine: archived source evidence

## Scope and authentication

This bounded extension of the
[first-machine evidence](actor-input-machine-evidence-2026-11-13.md) and
[fourth-machine evidence](actor-fourth-input-machine-evidence-2026-11-14.md)
authenticates the fifth descriptor and all caller instructions from the fourth
return through the sixth call. It reuses the authenticated wrapper `80068b8c`,
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
[`read_archived_fifth_input_machine_evidence.py`](../tools/matching-decomp/read_archived_fifth_input_machine_evidence.py)
authenticates the full snapshot, schemas, executable metadata, empty File Bytes
table, maps, full data5 digest and existing controls before its new fixed reads.
It then validates exact text/data3/data5 mapping identities. Width and digest
checks precede decoding or descriptor interpretation. The only additions are:

- Caller `80068644..80068674`: 48 bytes, all 12 instructions, SHA-256
  `26d9fd8a4592e0916d07c404e216ecb134f22965cd8324693fe43ab9e58e55b3`.
- Fifth descriptor `802d3928..802d3934`: 12 bytes, SHA-256
  `07abdf873b6c9636ed48f7c66275a3e367edd7ca66620c3afae6713f95bb456a`.

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
chain offset 405604, data offset 12532, physical offset 782586, length 48.

Descriptor fields use `MAIN_.data3`, block/subblock 5, start `802bae60`,
end-exclusive `803af120`, length `0xf42c0` and chain root 199. The single
obfuscated span has data buffer 206, chain offset 101064, data offset 2796,
physical offset 3394290, length 12. Both mappings require subblock type 2,
starting offset 0 and source offset 0.

## Fifth descriptor and state mapping

The six decoded big-endian u16 cells at `802d3928` are:

- +0: 1, the handler's mode/count field.
- +2: 0, flags.
- +4: 0, the phase-1 timer reload.
- +6: **16**, the successful phase-2 tail duration.
- +8: **`0x0100`**, mask index 0.
- +10: 0, mask index 1.

The fifth input mask is `0x100`, distinct from its wrapper result mask1. Its
duration is16, unlike the fourth descriptor's duration1. Selected descriptor
storage ends at the sixth descriptor address `802d3934`, independently formed
by the caller. No bytes at that next descriptor address are read. A bounded
implementation may admit only these six halfwords even if supplied a longer
view. Mask index2 or greater must refuse at the actual indexed read, preserving
preceding stores. This host bound is not an original range check or proof of a
complete retail structure declaration.

The fifth call at `80068658` targets `80068b8c` with r3 actor,
r4 `802d3928`, r5 actor+`0x600`, and r6 `1`. The shared handlers' p[0..3]
therefore refer to actor bytes `600`, `601`, `602`, `603`:

- `600`: phase byte selecting one of the three authenticated handlers.
- `601`: timer byte, decremented and signed-byte-tested by phases1 and2.
- `602`: mask index byte.
- `603`: wrapper tail byte, decremented when nonzero before the edge OR.

The existing shared-handler evidence supplies the following interpretation,
not additional reads by this extension. With flags0, phase2 reads actual
actor+`5bc` without optional `5e0`/`5b4` gates. Index0 requires an all-bit match
on `0x100`; index1's zero mask matches in all-bit mode. Phase1 uses any-bit
matching, so its zero mask does not match. Phase0/mode1 sets index0, phase2 and
timer127, then immediately enters phase2, which decrements the timer to126
before testing input. Timer expiry, read/store order and lazy bounds remain
those authenticated for the shared handlers.

The wrapper ignores the handler return and then loads `603`. A nonzero byte
is decremented before the read/OR/store of actor+`5d4` with **1**, and the
wrapper returns1. Zero returns0 without reading or writing `5d4`.
A successful fixed-descriptor phase2 match clears `600`, loads duration16 into
`603`, then the wrapper consumes that byte to15 and ORs1. It must not consume
the entire duration or reuse the fourth machine's duration1. A preexisting
nonzero tail can also trigger this suffix after handler no-hit or expiry.
Future reached wrapper invocations can decrement or refresh that retained
tail, depending on their real handler effects. This is not proof of sixteen
live frames, input capture, an angular effect or a physical-button mapping.
Late failures retain earlier writes.

## Exact caller continuation and next unsupported call

After the fourth wrapper call at `80068640` returns, the six instructions are:

1. `80068644`: `addis r4,r0,-32723`, loading the descriptor high half.
2. `80068648`: `or r3,r31,r31`, copying the actor and discarding return r3.
3. `8006864c`: `addi r4,r4,0x3928`, forming descriptor `802d3928`.
4. `80068650`: `addi r5,r31,0x600`, setting the fifth state pointer.
5. `80068654`: `addi r6,r0,1`, setting the wrapper result mask.
6. `80068658`: `bl 80068b8c`, making the fifth call.

After the fifth call returns, the six instructions are:

1. `8006865c`: `addis r4,r0,-32723`, loading the descriptor high half.
2. `80068660`: `or r3,r31,r31`, copying the actor and discarding return r3.
3. `80068664`: `addi r4,r4,0x3934`, forming descriptor `802d3934`.
4. `80068668`: `addi r5,r31,0x604`, setting the sixth state pointer.
5. `8006866c`: `addi r6,r0,2`, setting the sixth wrapper result mask.
6. `80068670`: `bl 80068b8c`, making the sixth call.

There are **no caller return-dependent stores, loads, comparisons or conditional
branches** between the fifth and sixth calls. Either real wrapper return0 or
return1 reaches the sixth call with descriptor `802d3934`, actor+`604`, mask2.
A runtime supporting only the first five machines should refuse at
**`80068670`**, not stop on fifth no-hit and not re-clear `5d4`. The caller's
sole earlier `5d4` zero store is at `800685e4`, before the first machine, as
established by the separate complete-caller evidence. Effects of the first
four machines and actual fifth-machine writes remain visible at sixth-call
refusal. No sixth state owner or descriptor contents should be preloaded to
perform the first five machines.

This extension supplies no sixth descriptor data, sixth state owner, later
machine, charge function `800686f0`, physical pad capture or production
wiring. Fifth state placement supplies no meaning or ownership for adjacent
actor bytes. Return discard and absence of caller stores are established by
all 12 authenticated instructions, not inferred from omitted C-export code.

## Validation and limits

Run from the repository root:

```
python -m unittest discover -s research/tools/matching-decomp -p 'test_archived_fifth_input_machine_evidence.py' -v
python -m unittest discover -s research/tools/matching-decomp -p 'test_archived_*evidence.py'
```

The dedicated suite passed **13 tests, no skips**. The complete archived
evidence suite in this workspace passed **443 tests, no skips**. Both standalone
reader invocations succeeded. Tests independently spell out all 12 instruction
operands, including both return-discarding copies, check the six expected
fields and exact spans in both archives, derive the 12-byte descriptor bound
from the two caller addresses, distinguish duration16/input mask`0x100`/result
mask1, mutate every caller and descriptor byte, and verify authentication,
mapping, strict type, digest, range, decoder-form, no-raw-output and arbitrary-CLI
refusals.

These are archived-source and synthetic reader tests, not runtime integration,
original-game replay, ownership provenance or playable acceptance. Contributor
and documentation aggregate checks belong to the integration task. This
evidence task changes only its new reader, test and note, with no installs,
acquisitions, archive/original execution, rig or process work, commit or
publication.
