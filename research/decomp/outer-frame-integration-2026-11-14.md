# Ordered battle-frame prelude

This checkpoint adds the bounded prefix of actual `80029434` over the existing
source-owned allocation, projectile, root and scheduler graph. It is **not a
successful outer frame, runnable actor scheduler, browser activation or
playability claim**. See [fixed archive evidence](outer-frame-evidence-2026-11-14.md).
The caller's mandatory predecessors are not substituted with successful callbacks.

## Canonical storage

`createSourceBattleOuterFrameRuntime` takes a genuine source object scheduler.
The match owner is derived from that scheduler and verified against its existing
spawn/admission/charge owner. No global snapshot, second mask object or copied
team record is made.

The new optional layout interface adds only explicitly supplied fields:

- `byte15d4`, `byte66`, and `halfD6` represent the pending request, mode and
  source halfword at those hexadecimal offsets on the same `80433934` owner.
- `activeMask` and `slotTeam` borrow the established names and storage layout
  from `battle/spawnFromSlotTables.ts` and `battle/forceSetup.ts`. The reached
  mask is a raw byte, not an inferred roster or actor-visibility bitset.
- `teamRows103` is the same existing row-reference array used by actor input,
  matrix and cue0 paths. Row byte names are relative hexadecimal offsets from
  `80433934 + f4 + 3c*i`. Existing `charged` represents row+f in the boolean0/1
  subset. Existing `meter` represents the unsigned halfword at row+32. New
  `threshold30` is explicit; `BURST.METER_MAX` is never substituted.
- The separate optional `systemGlobals` record uses the existing
  `ChallengeFlowState.controllerMask` spelling for `80433930+2`. Its constructor
  and default mask are not called or treated as source hydration.

All owners are supplied explicitly. Unknown or missing fields are checked only
when reached. Array and row references are retained by identity and checked for
aliases with already known allocator, spawn, root, HIT and scheduler storage.
The identity-only inventory also retains immediate object-valued own-data
records and the supplied actor-slot table without loading its slot scalars.
Competing raw/semantic field aliases
are refused; the interfaces do not create properties or default data.

## Executed prefix and preserved boundaries

1. `8b048` reads a signed request byte. A nonzero request calls `8b010` with
   `sign8(request)-1`. The setter first writes its low byte to mode66, then
   clears halfwordD6 only for signed arguments0 or1. The request clear is
   unconditional after that helper returns.
2. `29d48` captures the team-row base and visits exactly four rows in order.
   `29e98` clears row1/2/3 then sets row4 through9 to rawFF. It scans slots0–5
   with a fresh match-owner/mask load for each candidate. Only selected mask
   bits load the row team and corresponding slot team. A matching team updates
   row1, then reads the separate controller mask and conditionally increments
   row2, then writes the row3 membership mask and next compact roster slot.
3. Only rows with signed count1 greater than zero inspect active-burst byte10.
   Empty rows retain charged and do not require meter, threshold or burst cells.
   A nonzero burst byte clears charged, then refuses at callsite `80029d90`
   before mandatory `8008b290`. No later timer, pause-mask or floating-point
   branch is executed.
4. Nonburst rows compare unsigned meter32 against threshold30 and write charged
   true iff meter is at least the threshold. This may clear a previously true
   flag. After all four rows, the caller reloads mode66. Zero mode refuses at
   `80029458 → 80053b30`; nonzero mode refuses at `80029464 → 8000bef4`.

Reads and scalar destination preflights follow source order. This host model
requires synchronous, stable, nonproxy own-data records. Identity checks and
boolean storage admission are host-domain checks, not additional ROM reads.
The source's team base remains captured while global mask loads are live;
replacing its row table is a host-domain failure, never a retargeted source base.

## Ownership without premature execution authority

A private pending-claim transaction reserves the genuine scheduler exactly once.
Its public `runGroup`, `runSlots` and `runWrapper` entry points then refuse. There
is no outer scheduler run capability at this checkpoint, because no supported
path has reached a scheduler call. A genuine idle outer runtime or scheduler is
not authority to invoke a root, write scheduler snapshots or close another graph.

On an admitted outer failure, a private exact active failure scope permits only
closure. The scheduler enters its own closure scope, closes the allocator and
all retained root/spawn owners, then leaves that scope. Earlier scalar writes
remain visible; retrying the incomplete prefix cannot replay them. The new
runtime does not claim actor frame ownership, consume an actor epoch, clear an
incomplete-frame latch or weaken frame-owned projectile restrictions.

## Remaining work

The authenticated caller continues with real mass/target work, mandatory
`8000bef4`, ordered scheduler groups and additional intervening calls. None may
be skipped to reach group8. Full actor/slot hydration, the private source actor
callback/epoch join, positive projectile normalization/flight/collision/damage,
nonnull JObjUnref and browser activation remain separate unresolved work. This
checkpoint imports no disputed estimator and supplies no idealized substitute.

Verification results are recorded with the committed checkpoint and retained
local proof bundle, not inferred from compilation alone. The aggregate ROM
selfcheck invokes the new prefix tests through the genuine allocation/spawn/root
fixture with explicitly synthetic source records.
