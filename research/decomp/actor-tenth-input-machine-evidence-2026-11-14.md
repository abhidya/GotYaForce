# Tenth actor input machine: archived source evidence

## Scope and authentication

This bounded extension of the
[first-machine evidence](actor-input-machine-evidence-2026-11-13.md) and
[ninth-machine evidence](actor-ninth-input-machine-evidence-2026-11-14.md)
authenticates the tenth descriptor, every caller instruction from tenth setup
through the subsequent charge call, and four instructions forming the adjacent
charge input-mask table address. The latter establishes a conservative descriptor
storage bound, not charge behavior. Shared wrapper `80068b8c`, its three handlers
and dispatch table `802d3988` retain their separately authenticated evidence.
No original or archived instructions are executed, shared-reader allowlists
changed, new inputs acquired, or production wiring enabled.

The existing local ProgramDB inputs are in
`GotchaForce.rep.before_force_create/idata/00/~00000000.db/`:

- `db.3.gbf`: SHA-256
  `7b50dd2d2e17b4bfcc89a64cde27010247d0cbf0f48bd5c059f50275f40458d0`.
- `db.4.gbf`: SHA-256
  `1f86813d91ea8e2c4564f96622ec42555e1dba2c78aa81ad654e892140d019f8`.

The dedicated reader
[`read_archived_tenth_input_machine_evidence.py`](../tools/matching-decomp/read_archived_tenth_input_machine_evidence.py)
authenticates the entire snapshot, schemas, executable metadata, empty File Bytes
table, maps, full data5 digest and existing controls before new fixed reads.
It then validates exact text/data3/data5 mapping identities. Exact width and
SHA-256 checks precede instruction decoding or descriptor interpretation.
Only three fixed spans are admitted:

- Caller `800686bc..800686dc`: 32 bytes, all eight instructions, SHA-256
  `b3f8753f8e804506c11f8526c07fb9342f3d6c73d027d09f97eb1bc1c5926910`.
- Adjacent table address constructor `8006873c..8006874c`: 16 bytes,
  all four instructions, SHA-256
  `799ae73e3ca0635845461e1a27808be23d7c0c6a9315d364e90cc69e00d5ea88`.
- Tenth descriptor `802d3964..802d3970`: 12 bytes, SHA-256
  `41b4ea8d72d6fe7021bbd9244afb1994333dd286eb483a0b60a573bfafb2cc26`.

Both archives yield identical operands, fields and physical spans. Each selected
span has zero unrepresented instructions, but neither is a complete-function
claim. The complete caller has separate
[input-prefix evidence](actor-input-prefix-evidence-2026-11-13.md).
Output contains derived operands, typed fields, hashes, provenance and spans,
with no raw-byte output or arbitrary-address/width/execution options. The
executable hash property remains metadata, not unchanged original-DOL equality.

### Maps and physical spans

Instructions use `MAIN_.text1`, block/subblock 1, start `800055e0`, length
2796416 and chain root 21. Both selected spans are obfuscated in data buffer 46:

- Caller: chain offset 405724, data offset 12652, physical offset 782706,
  length 32.
- Address constructor: chain offset 405852, data offset 12780,
  physical offset 782834, length 16.

Descriptor fields use `MAIN_.data3`, block/subblock 5, start `802bae60`,
end-exclusive `803af120`, length `0xf42c0` and chain root 199. The single
obfuscated span has data buffer 206, chain offset 101124, data offset 2856,
physical offset 3394350, length 12. Both block mappings require subblock type 2,
starting offset 0 and source offset 0.

## Descriptor extent without an inferred stride

The caller explicitly forms descriptor address `802d3964` at
`800686bc/800686c4`. Its next call is charge `800686f0`, not an eleventh input
machine. A twelve-byte stride inferred from earlier descriptors would therefore
be insufficient evidence for this final descriptor's selected storage bound.

The existing C export
[`chunk_0008.c`](ghidra-export/chunk_0008.c), lines 4719–4720, explicitly places
charge tables at `802d3970` and `802d397c`. The symbol map
[`GG4E-CSM-20220412.map`](../symbols/GG4E-CSM-20220412.map), lines 799–801,
places the caller at `800685c0`, size `0x130`, and charge at `800686f0`,
size `0x290`, ending at the next function `80068980`.

Within that mapped charge function, the authenticated four-instruction span is:

1. `8006873c`: `addis r4,r0,-32723`.
2. `80068740`: `addis r3,r0,-32723`.
3. `80068744`: `stb r29,0x655(r25)`.
4. `80068748`: `addi r30,r4,0x3970`.

The first and fourth instructions form **`802d3970`**. The intervening
instructions do not alter r4. The C export identifies this address as the
separate charge input-mask table; `802d3970 - 802d3964 = 12` therefore bounds
this selected descriptor storage without guessing an array stride.

No bytes of either charge table are read. The isolated `655` store is represented
only to avoid omitting an intervening instruction; this span does not establish
its earlier register values, reachability, charge control flow, charge writes or
ownership. It must not be executed as a substitute for the charge function.
The chosen twelve-byte host bound is not an original range check or proof of a
complete retail structure declaration. Index 2 or greater remains unsupported
at the actual reached indexed-mask read, even if a longer host view is supplied.

## Tenth descriptor and state mapping

The six decoded big-endian u16 cells at `802d3964` are:

- +0: **1**, mode/count.
- +2: **`0x0010`**, flags selecting the phase-2 any-bit path.
- +4: **0**, phase-1 timer reload.
- +6: **1**, successful phase-2 tail duration.
- +8: **`0x000f`**, mask index 0.
- +10: **0**, mask index 1.

These are three separate sources: flags `0x10`, input mask `0x0f` and caller
result mask `0x2000`. The tenth must not inherit the ninth's flags 0 or input
mask `0x10`, the eighth's input mask `0x40` or result mask 8, the seventh's
input mask `0x20`, the sixth's flags 4/input mask `0x100`, or the fifth's
duration 16. No physical controller meaning is established by these numbers.

The tenth call at `800686d0` targets `80068b8c` with r3 actor,
r4 `802d3964`, r5 actor+`0x628`, and r6 `0x2000`. The shared handlers' p[0..3]
therefore refer to actor bytes `628`, `629`, `62a`, `62b`:

- `628`: phase selecting one of the three authenticated handlers.
- `629`: timer, decremented and signed-byte-tested by phases 1 and 2.
- `62a`: mask index.
- `62b`: wrapper tail, decremented when nonzero before the output OR.

The state jumps from the ninth's `610` to `628`, not `614`. This supplies no
ownership, initialization, or intervening-memory provenance. The wrapper's
original dispatch lookup has no phase bound. A bounded runtime supporting only
three authenticated handlers must refuse phase values outside 0, 1 and 2 at the
reached lookup, without pre-reading later state, charge inputs or actor fields.

## Shared-handler behavior and reached order

The following semantics come from the separately authenticated wrapper and
handler evidence, not additional reads in this extension.

Phase 0 stores p[2]=0 at `80068c24`, reads mode 1, stores p[0]=2 at
`80068c3c`, stores p[1]=127 at `80068c40`, and calls phase 2 at `80068c44`.
Phase 2 decrements the timer to 126 in that same invocation. Input and controls
must not be snapshotted before those writes.

For fresh or retained phase 2:

1. Load the timer, subtract 1, sign-extend the low byte, and store that byte
   at `80068d10`. Zero or negative signed results clear the phase and return
   0 before flags, input, index or descriptor-mask reads. Timer `0x80` becomes
   `0x7f` and continues; `0x81` becomes `0x80` and expires. Timer 0 becomes
   `0xff` and expires, not saturates.
2. Load descriptor flags `0x10`. Control gates 0x2/0x4 and 0x8 are clear,
   so **neither actor+`5e0` nor actor+`5b4` is read**. Match-word selector
   flag 0x1 is also clear.
3. Load the actual actor+`5bc` match word at `80068d90`, then p[2] at
   `80068d94`, then descriptor u16 at `8 + 2*p[2]` at `80068da4`.
   These reads follow the prior stores; they are not earlier snapshots.
4. Flag 0x10 is set, so the handler accepts **any** overlapping mask bit.
   For index 0, each of `1`, `2`, `4` and `8` individually matches `0x0f`;
   `0x10` and `0x2000` alone do not. Index 1's zero mask **never matches**,
   unlike the zero-mask all-bits path of the ninth. Index 2 or greater refuses
   at the mask read after the timer store, input read and index read.
5. On a match, clear p[0] at `80068de0`, load duration 1 at `80068de4`, store
   p[3]=1 at `80068de8`, and return handler 1. Any later failure preserves
   all preceding stores.

Retained phase 1 has its separate any-bit path. It first decrements/stores and
tests the timer. On a positive signed result, it reads p[2] at `80068ca8`,
actor+`5bc` at `80068cac`, then the indexed mask at `80068cb8`. Index 0 matches
any low-nibble bit. Success loads and stores timer reload 0, rereads the index
at `80068ccc`, increments/stores it from 0 to 1, and compares it with mode 1
minus 1. The unequal result leaves phase 1; the next timer decrement expires.
Index 1's zero mask never matches. Index 2 or greater refuses at its actual
mask read after the timer store, index read and input read. Neither phase may
borrow charge-table bytes to satisfy an out-of-bounds index.

The wrapper ignores the handler result and loads `62b` at `80068bcc`. Zero
returns 0 without a `5d4` read/write. A nonzero byte, including `0x80..0xff`,
is decremented/stored at `80068be8` before actor+`5d4` is loaded at `80068bec`,
ORed with **`0x2000`**, and stored at `80068bf4`. The wrapper returns 1.
This is a nonzero tail check, not the signed-positive timer check.

A successful tenth phase-2 match clears `628`, loads tail 1 into `62b`, then
consumes it to 0 and ORs `0x2000`. A preexisting nonzero `62b` can produce
that output even after handler no-hit or expiry. A later `5d4` failure cannot
roll back the tail decrement. This proves neither a live frame duration nor
actor ownership, physical pad capture or downstream result-bit behavior.

## Complete tenth-to-charge caller continuation

Immediately after the ninth return, the authenticated instructions are:

1. `800686bc`: `addis r4,r0,-32723`.
2. `800686c0`: `or r3,r31,r31`, discarding the ninth return.
3. `800686c4`: `addi r4,r4,0x3964`.
4. `800686c8`: `addi r5,r31,0x628`.
5. `800686cc`: `addi r6,r0,0x2000`.
6. `800686d0`: `bl 80068b8c`, tenth wrapper call.
7. `800686d4`: `or r3,r31,r31`, discarding the tenth return.
8. `800686d8`: `bl 800686f0`, charge call with actor in r3.

There are **no caller stores, loads, comparisons or conditional branches**
between the tenth return and charge call. Both real tenth wrapper returns,
0 and 1, reach charge. A runtime supporting only ten input machines should
refuse at **call site `800686d8`, target `800686f0`**, not stop on tenth no-hit,
report caller completion, re-clear `5d4`, or execute any charge side effect.
The sole earlier `5d4` zero store is at `800685e4`, before the first machine,
as established by separate complete-caller evidence. All reached effects of
the first nine machines and tenth state/output writes remain visible at the
charge boundary. No charge owner, table data, charge input or later state may
be preloaded merely to perform these ten machines.

The caller epilogue after charge is outside this narrow span and independently
covered by the complete-caller evidence. Authentication of the charge call and
adjacent table address is not implementation of charge. Charge remains a
separate unsupported continuation.

## Validation and limits

Run from the repository root:

```
python -m unittest discover -s research/tools/matching-decomp -p 'test_archived_tenth_input_machine_evidence.py' -v
python -m unittest discover -s research/tools/matching-decomp -p 'test_archived_*evidence.py'
```

The dedicated suite passed **18 tests, no skips**. The complete archived
evidence suite passed **520 tests, no skips**. Both standalone reader
invocations succeeded and matched in selected operands, fields and spans.
Whitespace checks passed.

Tests spell out every selected instruction operand independently, verify each
field and exact physical span in both archives, and derive the 12-byte storage
bound from the caller descriptor address and separately formed charge-table
address. They distinguish flags/input/result masks and zero-mask any-bit
behavior; runtime lifecycle behavior is tested separately by integration.

Synthetic cases cover snapshot authentication before parsing, invalid schema
before fixed reads, map identity/overlap/offset/length/type refusals, strict
integer fields, unknown ranges, duplicate allowlist entries, decoder-form
refusals, short/long reads, digests before interpretation, independent field
checks under synthetic digests, no raw output and arbitrary-CLI refusal.
Every selected instruction and descriptor byte is mutation-tested. Exact chain
read extents are asserted. Shared and ninth-reader allowlists continue to
reject the new spans. Charge-table data and full charge-function reads refuse.

These are archived-source and synthetic reader tests, not original-game replay,
runtime integration, ownership provenance or playable acceptance. Contributor
and documentation aggregate checks belong to integration. Only this new reader,
its test and this evidence note are changed by this evidence task. No installs,
acquisitions, original/archive execution, rig controls, commits or publication
are performed.
