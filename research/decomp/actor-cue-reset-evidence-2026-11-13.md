# Actor cue-reset pair: archived source evidence

## Scope and provenance

This is derived instruction evidence from the two existing immutable local
ProgramDB snapshots, not execution, original-DOL matching, a live oracle,
production ownership, or playable parity. No new input, raw executable range,
shared-reader allowlist change, external transfer, or rig access is needed.

Inputs under `GotchaForce.rep.before_force_create/idata/00/~00000000.db/`:

- `db.3.gbf`: SHA-256 `7b50dd2d2e17b4bfcc89a64cde27010247d0cbf0f48bd5c059f50275f40458d0`.
- `db.4.gbf`: SHA-256 `1f86813d91ea8e2c4564f96622ec42555e1dba2c78aa81ad654e892140d019f8`.

`read_archived_cue_reset_evidence.py` first uses the existing snapshot,
schema, executable-metadata, empty File Bytes, mapping, data5 digest and
control authentication. It then verifies the fixed function digests and emits
only decoded instruction operands, spans and authentication metadata. It has
no arbitrary-address or execution options. The executable metadata is not
proof of an unchanged original DOL.

The C export is `ghidra-export/chunk_0009.c:833–884`. The checked symbol map
`../symbols/GG4E-CSM-20220412.map:823–825` independently lists:

- `8006a6fc`, width `0x54` (84 bytes), next entry `8006a750`.
- `8006a750`, width `0x64` (100 bytes), next entry `8006a7b4`.

Both snapshots yield the same ranges and operands, including terminal `blr`
instructions at `8006a74c` and `8006a7b0`. Complete coverage is 21 and 25
instructions; none are omitted.

Range SHA-256 values:

- `8006a6fc`: `4efe53e520303e6ad0cf238f8a53d503a8f6ad394e161cc93649b7484b847b0c`.
- `8006a750`: `0512ba29e89a10d5dc9786ce20496633ed39f7b752b7c0313fa5afa0673e7233`.

Both use authenticated `MAIN_.text1`, block/subblock 1, chain root 21, data
buffer 47, obfuscated. The first span has chain offset 413980, data offset
4530, physical offset 790968, length 84. The second has chain offset 414064,
data offset 4614, physical offset 791052, length 100.

## Exact input addressing and sentinel

The actor is in r3, the cue index in r4. Both load the 32-bit table pointer
from actor+0x4f0 before any writes. `rlwinm r0,r4,1,0,30` computes the low
32 bits of index times two: the index is not truncated to a byte for lookup,
and its high bit is discarded by the shift. Address arithmetic is modulo
2^32. The first routine uses `lbzx` at table plus that offset. The second
adds the offset to the table pointer then uses `lbz` at the result plus one.
There is no bounds check, pointer validation or cue-table-content guarantee.

The selected byte is zero-extended into r6. `extsb` sign-extends a copy into
r0 for a signed comparison with -1. Consequently exactly byte 0xff is the
sentinel; bytes 0x80–0xfe are not rejected. r6 retains the original byte.
The sentinel path writes no actor memory and returns integer 0 in r3.
The accepted path stores the low eight bits of the original r4 as the cue
index, stores the original selected byte, and returns integer 1 in r3.
Both are leaf routines with no calls and no stack writes.

## Accepted-path memory order

The lookup load and sentinel comparison precede every following operation.
No source byte is preloaded ahead of the order below. This matters for an
implementation that models observable reads or overlapping memory.

For `8006a6fc`, after loading the old actor+0x5e5 byte and setting r0 to zero:

1. Store that old byte to actor+0x7cf (decimal 1999).
2. Store low eight index bits to actor+0x5e5.
3. Load the old actor+0x5da byte.
4. Store that old byte to actor+0x5dc.
5. Store the selected table byte to actor+0x5da.
6. Store zero bytes at actor+0x543, +0x542, +0x541, +0x540, in that order.
7. Set r3 to 1 and return.

For `8006a750`, after loading the old actor+0x5e4 byte and setting r0 to zero:

1. Store that old byte to actor+0x7ce.
2. Store low eight index bits to actor+0x5e4.
3. Load the old actor+0x5db byte.
4. Store that old byte to actor+0x5dd.
5. Store the selected table byte to actor+0x5db.
6. Store zero bytes at actor+0x547, +0x546, +0x545, +0x544, +0x588, in that order.
7. Store the 32-bit zero register using `stw` at actor+0x754.
8. Store a zero byte at actor+0x1db3.
9. Set r3 to 1 and return.

The actor+0x754 operation writes four raw zero bytes. It is not `stfs`, does
not load a scalar float constant, and does not perform floating-point
conversion or depend on FPSCR. Interpreting those bits later as binary32
would yield positive zero, but this function does not establish a field type.
The +0x1db3 clear follows that word write; +0x1db2 is not cleared here.
The first routine writes neither +0x754 nor +0x1db3.

## Validation and limits

Run from the repository root:

```
python -m unittest discover -s research/tools/matching-decomp -p 'test_archived_cue_reset_evidence.py' -v
```

Result: 8 tests passed, including both local snapshots (no skips). Checks
assert every instruction operand in sequence, full function extents, matching
snapshot results, no raw range fields, snapshot and mapping failures before
fixed reads, range digest failures before decoding, mutation rejection at
every instruction, strict input types, selected decoder forms, and rejection
of arbitrary CLI options.

These tests authenticate source evidence only. They do not test a runtime
cue implementation, establish current production owners or simulate a valid
retail cue table. Contributor and documentation aggregate checks belong to
the parent integration run; they were not run for this isolated evidence task.

## Explicit runtime ownership and integration

`actor-cue-reset.ts` implements the pair only for explicitly exclusive offline
source actors. The existing actual `cueTable`, cue/state/previous-state fields
and `fbPhase` at540 remain their owners. The runtime retains no copied table;
each invocation reloads the actual pointer. Table input is an explicitly owned
non-shared Int8Array. Unsigned32 cue-register bits are shifted modulo2^32 for
lookup, separately from the low-byte cue store. Missing tables, missing entries,
invalid source values and missing/readonly reached destinations refuse. These
are host bounds, not extra source sentinel cases or retail table provenance.

The ownership conflict is real: legacy `fbPhaseSlots` is annotated544..547 in
actor.ts, but executable family readers use its indices as540..543 (for example
samurai.ts and cosmic-dragon.ts). It cannot honestly supply upper-body storage,
and its first element also competes with actual `fbPhase`. This bounded route
requires the legacy property absent. Only otherwise missing541..543,544..547,
588 and previous-cue7ce/7cf receive explicit binding cells. Legacy family
`animState` is another588 claimant and is likewise refused.

The existing source animation-dispatch `marker1db3` is retained by identity as
the sole1db3 owner. Competing legacy actual `shotByte1db3` must be absent.
The runtime never deletes or migrates either legacy property, substitutes an
accessor, or copies values to keep two owners synchronized. Fixtures explicitly
construct this exclusive domain; normal createRomActor/live-family actors are
not admitted unchanged. World and dispatch expose their retained mapping
header via read-only getters, allowing the helper to verify their shared
mapping identity in addition to actual-actor and dispatch-binding stability.

Actual `onLand754` is the pre-existing physics-extras callback pointer, as
confirmed by the source land path in chunk_0008.c:4042–4044. Its zero word is
represented as null on that same owner. No timer shadow is added and the
callback is never invoked by reset. The subsequent1db3 store goes to the real
dispatch binding. Full-body reset leaves upper phases,754 and1db3 unchanged.

Stage-boundary runtime may late-bind one genuine cue-reset runtime. It checks
actual-actor identity and calls upper9 then full9, including when upper returns
the real sentinel0. Without that binding the historical6a750 refusal remains.
With it a complete stage transition reaches the existing explicit685c0 refusal
in the enclosing tick prefix. Late failures keep all earlier stage, upper or
full stores; the prefix epoch remains consumed. This is not a full tick,
source input closure, ordinary family execution or production activation.

Checked-in tests exercise every selected byte in both functions, high-bit
index wrapping and index256 distinct from cue0,19 individual readonly-store
prefixes, missing late owners, source alias/reentry guards and sentinel/no-table
distinction. The appended synthetic DAT/setup composition proves that the same
cleared marker changes the real animation-dispatch gate. Subsequent actual
setup/playback, wait, movement, matrix/linked-copy and history calls remain
explicit and keep their own cadence. No original-game replay is claimed.
