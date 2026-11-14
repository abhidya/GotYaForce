# First actor input machine: archived source evidence

## Scope and authentication

This note describes derived operands and fixed data fields from the two existing
local ProgramDB snapshots. It does not execute original/archive instructions,
acquire inputs, change the shared archive-reader allowlist, authenticate an
unchanged original DOL, or establish live input capture, actor ownership or
playable parity. Only the first descriptor and three dispatch entries are read.

Inputs under `GotchaForce.rep.before_force_create/idata/00/~00000000.db/`:

- `db.3.gbf`: SHA-256 `7b50dd2d2e17b4bfcc89a64cde27010247d0cbf0f48bd5c059f50275f40458d0`.
- `db.4.gbf`: SHA-256 `1f86813d91ea8e2c4564f96622ec42555e1dba2c78aa81ad654e892140d019f8`.

`read_archived_input_machine_evidence.py` first authenticates the whole snapshot,
exact schemas, executable metadata, empty File Bytes table, address maps, full
data5 digest and existing controls through the existing reader. It then checks
the exact text/data3/data5 mapping identities before any new fixed read. Each
new range must match its independently recorded length and SHA-256 before
instruction decoding or data-field interpretation. Output contains derived
operands, typed field values, target addresses, spans and provenance, not raw
instruction words or executable ranges. There are no arbitrary-address, raw or
execution options. Executable metadata remains a metadata property, not proof
that the archived executable bytes are unchanged from retail.

All operands, data fields and physical spans match between the two snapshots:

- Wrapper `80068b8c..80068c14`: 136 bytes, 34 instructions, SHA-256
  `47cba4509016e06f1bd98132a48e436013e6ff74ff62478a8efc1060eede27a2`.
- Phase 0 `80068c14..80068c84`: 112 bytes, 28 instructions, SHA-256
  `230e4f4b80234a1ff978cda142ff079bd9c11cfa0b271b7c1b3208a7339ff314`.
- Phase 1 `80068c84..80068d04`: 128 bytes, 32 instructions, SHA-256
  `178de0acf5085e37b37b6581715136703b885a808261e30c7de13395067c7ab6`.
- Phase 2 `80068d04..80068df8`: 244 bytes, 61 instructions, SHA-256
  `f077c452065b1619363a0b2190a4c35aa0b018223f9ad9c9fa144cbffe8bb923`.
- First descriptor `802d38f8..802d3904`: 12 bytes, SHA-256
  `9de63b2eeedf5a02dd167702d515058ad54ea92b8095283a3038d240bfd764ca`.
- Three dispatch entries `802d3988..802d3994`: 12 bytes, SHA-256
  `89ef779dd3c9f8f9603d38286c5124e32d7dbde2bdf60ac109e671e5a7a241ad`.

All 155 instructions are represented, with zero omitted instruction ranges.
No adjacent descriptor, fourth dispatch entry or subsequent handler is read.

### Mapping and physical-span audit

The four executable spans use `MAIN_.text1`, block/subblock 1, start
`800055e0`, length 2796416, chain root 21 and data buffer 46. All are obfuscated:

- `68b8c`: chain offset 406956, data offset 13884, physical offset 783938,
  length 136.
- `68c14`: chain offset 407092, data offset 14020, physical offset 784074,
  length 112.
- `68c84`: chain offset 407204, data offset 14132, physical offset 784186,
  length 128.
- `68d04`: chain offset 407332, data offset 14260, physical offset 784314,
  length 244.

Both data spans use `MAIN_.data3`, block/subblock 5, start `802bae60`, length
`0xf42c0`, end-exclusive `803af120`, chain root 199 and data buffer 206:

- Descriptor: chain offset 101016, data offset 2748, physical offset 3394242,
  length 12, obfuscated.
- Dispatch table: chain offset 101160, data offset 2892, physical offset 3394386,
  length 12, obfuscated.

Both maps require subblock type 2, starting offset 0 and source offset 0.

### The omitted phase-1 export and its extent

The symbol map `../symbols/GG4E-CSM-20220412.map:802–803` gives wrapper width
`0x88` and phase-2 width `0xf4`. It does not name phase 0 or phase 1.
`ghidra-export/chunk_0008.c:4890–4912` exports phase 0, and its next exported
entry at line 4916 is phase 2. The phase-1 body is missing from that C export.

The dispatch table independently points its second entry to **80068c84**.
Authenticated phase 0 restores LR and SP at `68c74..68c7c` and returns at
`68c80`. Phase 1 begins after that return, uses the original handler argument
registers, has no prologue/frame dependency or calls, and has its own returns at
`68ca4`, `68cf8` and `68d00`. All its branches stay within `68c84..68d04`.
The next independently named entry is `68d04`. This establishes the selected
phase-1 leaf extent from the authenticated target, instructions and neighboring
entry, not from an invented symbol-map size or C body.

The description of `68c84` as a post-call mid-entry inside phase 0 in
`pad-bit-binding-decode-2026-07-05.md` is incorrect for these authenticated
instructions. It is a separately callable omitted leaf, not phase 0's epilogue.
That historical note also labels the wrapper's `68bd4` branch as `beq`; its
actual BO=4, BI=2 branch goes to the decrement/store path when p[3] is nonzero.
This new note records those corrections without editing the historical note.

## Fixed descriptor and indirect entry

Treat descriptor `802d38f8` as six unsigned big-endian halfwords, all loaded by
`lhz`, not signed `lha` or a 32-bit mask read:

- +0: mode/count = 1.
- +2: flags = 0.
- +4: phase-1 timer reload = 0.
- +6: output duration = 1, narrowed by the eventual byte store.
- +8: mask for index 0 = `0x0200`.
- +10: mask for index 1 = 0.

The first caller supplies actor, this descriptor, p=actor+`0x614` and result
mask `0x20`. The four raw bytes p[0..3] are phase, timer, mask index and output
counter respectively. These names describe their demonstrated use, not a new
owner or a physical-pad mapping.

The wrapper loads unsigned p[0] at `68bb8`, multiplies it by 4 using
`rlwinm SH=2,MB=0,ME=29`, performs `lwzx r12,r7,r0`, then `mtctr r12` and
`bctrl` at `68bc8`. The authenticated targets are:

1. p[0]=0: entry `802d3988` -> `80068c14`.
2. p[0]=1: entry `802d398c` -> `80068c84`.
3. p[0]=2: entry `802d3990` -> `80068d04`.

At that indirect call r3 remains the actor, r4 the descriptor, r5 the state
pointer and r6 the caller's result mask. Copies of actor, p and result mask are
retained in r29, r30 and r31. The handlers use r3/r4/r5 arguments; r6 is volatile
scratch once they begin. The C export's argumentless indirect call does not
remove these authenticated arguments. The wrapper does not switch on, return
or otherwise use a handler's r3 return value: its next instruction overwrites
r3 with a fresh p[3] load.

There is no original table-index bounds check. A bounded runtime with only these
three authenticated targets must refuse other phase values at the reached
dispatch lookup. It must not invent extra table entries or treat a resolver
callback as handler execution.

## Phase 0: 80068c14

The source order is:

1. Store p[2]=0 at `68c24`.
2. Load descriptor+0 as u16 and compare unsigned to 1.
3. When it equals 1, store p[0]=2 at `68c3c`, then p[1]=127 at `68c40`,
   then call `80068d04` at `68c44` with the same actor/descriptor/p arguments.
   This is a genuine linked call followed by the phase-0 epilogue, not a
   tail branch. Its return value passes through phase 0 but the wrapper ignores it.
4. Otherwise, load actor+`5bc` at `68c4c` **before** loading descriptor+8
   at `68c50`. If their AND is zero, return 0. If nonzero, store p[0]=1,
   then p[2]=1, then load descriptor+4 and store its low byte to p[1]. Return 0.

The authenticated first descriptor always takes step 3. Phase 2 immediately
decrements the newly stored 127 to 126 in the same wrapper invocation. There
is no initial actor+5b4 or actor+5bc snapshot before p[2]/phase/timer stores.

## Phase 1: 80068c84

This complete previously unexported body is required if a retained p[0]=1 is
accepted, even though fresh phase 0 with the first descriptor does not create it.

1. Load p[1] unsigned, subtract 1, sign-extend its low byte with `extsb.`,
   then store its low byte to p[1] at `68c90`.
2. Only a **positive signed byte** continues. Zero or negative stores p[0]=0
   and returns 0. There is no saturation or unsigned-expiry shortcut.
3. Load p[2] at `68ca8`, then actor+`5bc` at `68cac`, then descriptor u16
   at `8+2*p[2]` at `68cb8`. Test whether any masked bit is set. No match
   returns 0 without further state stores.
4. On a match, load descriptor+4, then store its low byte to p[1].
5. **Reload** p[2] at `68ccc`, increment, store its low byte at `68cd4`,
   then retain the increment masked to a byte.
6. Load descriptor+0 at `68cdc` and subtract 1 as a 32-bit integer.
   Compare that value to the retained increment byte with signed `cmpw`.
   Equality stores p[0]=2. Both outcomes return 0.

For the fixed descriptor, index 0 tests mask `0x0200`. A match reloads timer0,
increments index0 to1, and leaves phase1 because 1 != mode1-1. Index1 tests
mask0 and never matches in phase1. Index>=2 exceeds the authenticated descriptor
storage: a bounded runtime must stop at that mask read, after retaining the
already performed timer store, p[2] read and actor+5bc read. It must not borrow
bytes from the next descriptor.

## Phase 2: 80068d04

Phase 2 starts with the same unsigned load, subtract, signed-byte test and byte
store as phase 1. Its timer store is at `68d10`, before the branch. A result
<=0 stores p[0]=0 and returns0, skipping descriptor flags and all actor status
reads. Initial timer0 becomes `0xff` and expires; 1 becomes0 and expires;
`0x80` becomes`0x7f` and continues; `0x81` becomes`0x80` and expires;
`0xff` becomes`0xfe` and expires.

On a positive result, load descriptor+2 once into flags. The authenticated
source supports these gates, in order:

1. If flags bit1 (`0x2`) is set, load actor+`5e0`. If its bit`0x40` is set,
   return0.
2. If flags bit2 (`0x4`) is set, separately load actor+`5e0` again. If its
   bit`0x40` is clear, return0. This is a separate reached load, not reuse.
3. If flags bit3 (`0x8`) is set, load actor+`5b4`. If its mask`0x000f0000`
   is zero, return0.
4. If flags bit0 is set, load actor+`5b4` into the match word. Otherwise,
   load actor+`5bc` at `68d90`.
5. Only **after** that match-word load, load p[2] at `68d94`, then load
   descriptor u16 at `8+2*p[2]` at `68da4`. Testing flags bit4 occurs between
   those loads but does not change the retained match word or index.

Flags bit4 selects any-bit versus all-bit matching. For any-bit, the exact
integer sequence is AND, `neg`, OR with the unnegated AND result, then
`rlwinm SH=1,MB=31,ME=31`, yielding 1 iff any masked bit is set. For all-bit,
it is AND, subtract mask from that AND result, `cntlzw`, then
`rlwinm SH=27,MB=5,ME=31`, yielding 1 iff every mask bit is present.
A zero mask therefore **matches in all-bit mode**, unlike phase 1's any-bit
check. These are integer operations, not floating-point arithmetic.

On no match, return0. On a match, **store p[0]=0 first** at `68de0`, then
load descriptor+6 at `68de4`, then store its low byte to p[3] at `68de8`,
and return1. A late descriptor/store failure must retain the prior p[0] clear.

For first descriptor flags0, no actor+5e0 or actor+5b4 read is reached. The
match word is the actual actor+5bc value. Index0 succeeds iff bit`0x200` is
present; index1 mask0 succeeds unconditionally. Index>=2 is outside these
12 bytes and must refuse lazily at the descriptor mask read, after the timer
store and the reached actor+5bc/p[2] reads.

## Wrapper suffix and caller continuation

After any real handler returns, the wrapper loads p[3] at `68bcc` and uses
`extsb.` only for a **nonzero** test. Both positive and negative signed bytes
are nonzero. Zero returns0 and never reads or writes actor+5d4.

For any initial p[3] byte1..255, it computes byte-1, prepares return1,
**stores the decremented low byte at `68be8`**, then **loads actor+5d4 at
`68bec`**, ORs the retained result mask, and stores the full u32 at `68bf4`.
There is no signed-positive expiry condition here. An actor+5d4 access failure
occurs after the p[3] decrement and cannot roll that store back. This suffix
runs even if the handler returned0, including after phase/timer expiry, and a
successful handler with descriptor duration0 does not make the wrapper return1.

The independently authenticated caller in
[actor-input-prefix-evidence-2026-11-13.md](actor-input-prefix-evidence-2026-11-13.md)
clears actor+5d4 at `800685e4` before the first wrapper call at `800685f8`.
If this call returns, it ignores the wrapper return, reloads the next descriptor
base, prepares actor in r3, descriptor `802d3904` in r4, actor+`618` in r5 and
mask`0x40` in r6, then calls the same wrapper at `80068610`.

A first-machine-only runtime can stop at that second call. It must not repeat
the 5d4 clear, preload later state owners, call the remaining nine machines or
claim their descriptor data are authenticated here. The preprocessing writes,
first-machine state stores and first-machine 5d4 OR remain visible when the
next call refuses. The later charge function `800686f0` remains outside scope.

## Validation and limits

Run from the repository root:

```
python -m unittest discover -s research/tools/matching-decomp -p 'test_archived_input_machine_evidence.py' -v
```

Result: **15 tests passed, no skips**, using both existing local archives.
Both standalone reader invocations also completed successfully.
The broader `test_archived_*evidence.py` regression passed **361 tests, no skips**
in the shared working tree, and `git diff --check` passed. Contributor and
documentation aggregate checks are owned by the integration task, not this
isolated evidence check.

The tests independently spell out all 155 instructions and operands in order,
including every branch condition, signed-byte record form, load/store order,
rotation mask, indirect target/argument preservation and phase-1 instructions
absent from the C export. They verify both archives, descriptor/table values,
physical spans, coverage, no raw output keys, strict types, narrow decoder
forms, authentication/mapping failures before new fixed reads, range/digest
failures before decoding, each instruction's mutation, every descriptor/table
byte's mutation, independent expected-value guards, and arbitrary-CLI refusal.

These checks authenticate archived source evidence, not runtime implementation,
exclusive field ownership, live machine state, physical pad capture, original
DOL equality or retail traces. Runtime integration and its synthetic adversarial
checks are separate work. The evidence task did not install software, inspect
the rig, execute archived/original code, acquire inputs, commit or publish.

## Implemented bounded owner graph

`actor-input-machine.ts` implements the wrapper and all three real handlers.
The retained table contains numeric source addresses, never host callbacks.
The runtime reads the selected entry and admits only the three authenticated
handler bodies. It bounds the explicit table to three entries and the first
descriptor to six halfwords even if a caller supplies longer arrays. Unknown
indices/targets or missing reached cells refuse at their actual use, preserving
prior stores. This is a host storage bound, not an original range check.

The caller explicitly supplies own-data arrays and keeps their identities;
there is no hidden default or claimed retail runtime hydration. The verified
archived descriptor/table values above can be supplied as decoded inputs.
Shared global table/descriptor records can serve distinct actors, while actual
actor ownership is permanently exclusive per machine runtime. Only missing
614..617 bytes receive copied, sealed partial storage. `statusWord5b4`, optional
`statusWord5bc`, `controlWord` and `inputEdge5d4` remain their canonical actual
RomActor fields. Competing aliases, including own undefined properties, refuse.
The runtime neither deletes nor mirrors legacy fields.

Optional `firstMachine` integration in the existing input prefix verifies a
genuine runtime and the same retained actor/binding. It runs only after real
68980 and the actual5d4 zero store. A real wrapper0 or1 advances to an explicit
second68b8c refusal at80068610; no618 bytes, later descriptor or charge686f0
behavior is supplied. Without the optional runtime the historical first-call
refusal remains. Prior distance, gauge, support, stage, cue and input effects,
including a consumed tick epoch, survive every later failure.

Standalone machine binding is offline. It does not claim to disable all browser
writers. The genuine enclosing tick claim supplies the existing bridge.syncIn
exclusion, and input-prefix claims exclude the approximate Borg mash producer.
The active-direction boundary is separate: an explicit supported GQR4 profile
now performs both quantized loads but still refuses before800452a0. See
[input GQR evidence](actor-input-gqr-evidence-2026-11-13.md).

Checked-in runtime tests cover all256 timer bytes in both timer-bearing phases,
all256 wrapper tail bytes, input gates and any/all matching, independent zero
mask semantics, source-table target selection, bounded indices, late store and
read failures, shared globals versus per-actor exclusivity, genuine branding,
reentry and retained processor state. Synthetic DAT/setup/stage/cue composition
proves real first-machine hit/no-hit continuation, repeated explicit epochs,
partial failures and separate downstream cadence. These are bounded synthetic
and source-operand checks, not original-game replay or playable acceptance.
