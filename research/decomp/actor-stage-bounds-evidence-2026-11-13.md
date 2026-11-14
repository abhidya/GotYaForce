# Stage-bounds archived instruction evidence

The fixed reader `research/tools/matching-decomp/read_archived_stage_bounds_evidence.py`
authenticates the two existing allowlisted ProgramDB snapshots before parsing,
checks the existing memory maps, and represents all 65 instructions of
`80059e58..80059f5c`. The selected 260-byte span has SHA-256
`551ac855e1a74b2c56801713d0cf7c3ddf577c11214046365dec304c64206f77`.
The extent is selected from the C export next entry (`80059f5c`) and the
authenticated return epilogue, not a symbol-map entry: `80059e58` is absent
from that map. Coverage metadata therefore uses `selected_width`, not
`map_width`. Both snapshots produce identical operand evidence. No executable range is
written or emitted. No archive code is executed. Shared reader allowlists are
unchanged. There are no scalar floating-point constant loads in this function;
stage pointer and bounds remain runtime inputs.

## Source order and predicates

- `80059e6c..80059e8c`: read actor byte `4a1`, sign-extend and return when
  nonzero; read unsigned byte `18` and return unless equal to one; read byte
  `6cb`, sign-extend and return when nonzero. None of these returns resets
  `6cc` or reads stage bounds.
- `80059e90`: load stage pointer from `r13 - 21316`. The C export identifies
  this global as `DAT_8043625c`; the instruction independently preserves the
  SDA-relative displacement, not a claim about live r13 or pointer contents.
- `80059e94..80059ec8`: load actor x (`20`), compare to stage lower x (`3c`)
  using `fcmpo`, branch on LT; compare the same x register to upper x (`38`),
  branch on GT; then load actor z (`28`), compare to lower z (`44`), branch on
  LT; compare the same z register to upper z (`40`), and branch to the
  in-bounds reset when GT is false. Every taken out-of-bounds branch targets
  `80059ecc`. Comparisons short-circuit in exactly this order; equality does
  not trigger out-of-bounds. No subtraction, expansion or tolerance occurs.
- `80059ecc..80059ee0`: signed-halfword load `6cc`, add one in a register,
  halfword store, signed-halfword reload, compare to **30**, and branch to
  transition when LT is false. The C phrase `>29` is equivalent only after
  the stored 16-bit value is sign-extended again. In particular 32767 wraps
  to -32768 and does not independently meet the threshold.
- Only below the threshold: read control word `5e0`, isolate bit mask
  `02000000` with recording `rlwinm`, return if zero. Otherwise transition.
- `80059ef0..80059f20`: transition first resets `6cc` to zero, reloads control
  word `5e0`, tests `05000000` with `andis.` immediate `0500`. Zero writes
  byte `6cb=1`; nonzero writes `6cb=2`, then signed-loads halfword `272`, ORs
  immediate `0043`, and stores the halfword. Signed loading differs from the
  C export's unsigned spelling but yields identical stored low 16 bits.
- `80059f24..80059f38`: call `8006a750(actor,9)` then `8006a6fc(actor,9)`.
  These are authenticated call boundaries, not implementations or evidence
  that cue effects can be omitted safely.
- `80059f40..80059f44`: genuine in-bounds path writes halfword `6cc=0`.

Ordered `fcmpo` and its condition-register branches must not be replaced by
an inverse conjunction that treats NaNs differently. Live FPSCR exception
state is not established here; a finite-value-only adapter should refuse
nonfinite inputs rather than claim exact exceptional behavior. No stage
validity predicate (including min <= max) occurs in the selected function.

## Bounded runtime review

`packages/combat/src/rom/actor-stage-bounds.ts` retains the authenticated source
field-access order: three gates, stage owner, x/lower-x/upper-x, conditional
z/lower-z/upper-z, counter load/store/reload, conditional first control read,
reset, second control read, byte transition and optional signed-halfword OR.
Own-record/writability/owner checks are additional host admission checks and
are not source memory accesses. The explicit refusal before cue effects must
identify first call site `80059f2c`; `80059f30` is the following actor-register
move, not the call. No other source field order discrepancy was identified.

## Verification

Run the unittest file with the two pre-existing archives at the default
repository path, or set `GOTYAFORCE_ARCHIVED_PROGRAMDB_DIR` to their existing
local directory. This changes only fixture discovery, not the reader's
snapshot hashes, fixed span, mapping guards, or address surface.

The suite covers fixed extent, all decoded instruction addresses, both
snapshot identities, operand order and signedness, branch conditions, masks,
counter reload, cue ordering, schema/mapping/authentication gates, CLI rejection
of arbitrary ranges and execution, and one-bit mutation at every instruction
failing the digest before decoding. This is archived ProgramDB evidence,
not original-DOL identity, live execution parity, integrated gameplay, or
playability evidence.

## Runtime ownership and admitted behavior

`actor-stage-bounds.ts` implements this explicit helper over the same actual
RomActor and the existing source world/status/terrain records. World `mode4a1`
is the sole 4a1 owner; status `short272` remains the sole 272 owner. Actual
`pos.x/z`, `controlWord` and the promoted existing `noClamp6cb` property are
borrowed directly. The physics-extras implementation still reads that same
property. Only missing raw-byte `lifecycle18` and signed-short `short6cc` get
explicit per-actor binding storage. No values are inferred from host fusion,
death, terrain-grounded state or a default lifecycle. Competing actor fields
for18/6cc are rejected rather than synchronized as shadow copies.

`SourceActorTerrainGlobals` gains optional `maxX38`, `minX3c`, `maxZ40` and
`minZ44`. The terrain runtime exposes its retained record through a read-only
`getTerrainGlobals` accessor, without copying the fields or inventing bounds.
The fields belong to the same DAT_8043625c record as the floor/ceiling layers.
They are not layer-grid bounds. Source C at `chunk_0012.c:5388–5418`
identifies initialization by80087718, but this increment does not implement
or authenticate that initializer, source stage loading or retail values.
The fixtures supply explicit synthetic limits; missing reached fields refuse.

Own-data, finite exact-binary32 comparisons and stable synchronous non-proxy
owners are host bounds. Binding validates ownership; source fields are checked
lazily in the authenticated order. Inclusive edges, signed16 wrapping before
threshold, separate control-word loads, and signed272 low16 OR behavior are
preserved. The cue-transition prefix writes its actual fields, then refuses
at the real first unsupported6a750 call. Approximate legacy dispatch is never
invoked to manufacture a successful return. An early return or subthreshold
increment genuinely completes this helper, not a whole59068/55568/54070 tick.

The tick-prefix accepts this genuine runtime optionally. It verifies that
actual actor, world and status identities agree with its existing gauge graph.
Without a stage binding the old59e58 refusal is unchanged. With it, both distance
divisions, real5bab8 and real zero-support67a70 still execute first. A genuine
59e58 return reaches explicit685c0 refusal; a transition retains preceding
stores and stops at6a750 instead. Epoch consumption remains in the caller, so
no failed attempted prefix can be replayed with the same epoch. The helper
itself has no scheduler, automatic matrix/animation/history work or rollback.

Unit tests cover inclusive boundaries, all early gates, lazy missing/invalid
fields, signed counters, control masks, partial destination failures, owner
identity/alias/reentry controls and genuine tick-prefix composition. The full
65,536-value signed16 counter domain is exercised against an independent
modular expectation. An appended synthetic DAT/setup composition shares the
real world/status/gauge/terrain owner graph, separates stage limits from grid
extents and preserves the later explicit wait, movement, matrix and history
cadence. These are synthetic source-backed checks, not original-input replay,
continuous production ownership or playable-parity evidence.
