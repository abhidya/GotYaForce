# Shared source slot status and target/action continuations

Date: 2026-11-14. Local continuation of `93d0e22f`.

The new `actor-slot-status.ts` implements genuine `80010514` against explicit
current data and the existing scheduler's live actor table. Both `8006b450`
(target preparation) and `8005a298` (action requests) use this same helper.
The normal outer prefix can now return from bounded `6b450` early exits and
stops immediately at the next mandatory **`8006af88 → 8006b7f4`**. The zero-mode
action path can now write the genuine priority-selected request byte.

This is bounded source-backed synthetic composition, not a completed frame,
source actor constructor, scheduler invocation, actor epoch, browser activation
or playable clone. [New static evidence](target-selector-evidence-2026-11-14.md)
authenticates both complete bodies and the ten reached indirect-dispatch words.
No distance callee or disputed normalization estimator is imported or skipped.

## Canonical storage and construction

- `RomActor.slot` remains the source raw byte at `+3e4`; callers sign-extend it.
- `scheduler.getActorSlotTable()` remains the sole live `803c4e84` pointer owner.
  The helper resolves each fresh table entry with that scheduler's same allocator.
  A selected target can differ from the caller. Repeated or changed pointers are
  not replaced by a roster, caller shortcut or cached target.
- New optional actual `byte43d` is a raw source byte, with a codec annotation
  and no constructor default. It is not a Borg status or another binding's cell.
- New explicit `slotRecords[slot].state18` represents `803c73b0 + slot*3e4 +18`,
  equivalently `803c73c8 + slot*3e4`. It does not represent record offset zero.
  The source initializer clears thirteen records, but that is not evidence for
  current state or permission to fill absent fixture cells with zero.
- Explicit `dispatch3938` is the ten-word table at `802c3938`. Each reached
  entry must match its authenticated local block address. Entries not reached
  remain lazy; no implicit default table entry is supplied.
- The sealed canonical action binding still owns `7d2/73c`. Its original source
  object can receive the optional helper after scheduler construction and before
  its first reached call. That avoids the real action→admission→spawn→root→scheduler
  construction cycle without replacing any runtime. The helper identity becomes
  fixed when reached, and only one helper can own a scheduler.

The outer-frame helper must equal the canonical action runtime's helper, and
its scheduler must equal the outer's scheduler. The action join verifies the
same allocator actor and the scheduler's actual spawn/admission/action graph.
Helper storage is checked against retained scheduler and shallow action owners;
no recursive helper/scheduler inventory cycle is introduced. The action join checks
canonical allocator/actor completeness before and after10514 and at subsequent
own-data access/store boundaries until the call exits. A previously closed graph
or an interruption during the helper, edge load or destination preflight cannot
write a later request. The call-local check is cleared on exit.
Direct read-only helper queries, like metadata getters, do not grant execution
authority or reopen the graph. Stable synchronous
non-proxy own-data records remain the host boundary.

## Ordered behavior

`10514` first loads the selected player record's raw state18. Equality with two
sets bit31 of its eventual unsigned return value. It then always loads the live
actor pointer and that actual actor's raw43d, even when bit31 was set. The low
seven bits select behavior: values greater than nine return without reading the
dispatch table; values zero through nine load exactly one authenticated word.
The two default entries return the high flag alone; entries two through nine
OR bits1,2,4,8,16,32,64,128 respectively. Bit7 of43d is masked, not a signed test.

The host owner model admits thirteen player records and six actor-slot words.
A reached player index outside thirteen refuses before a player-record access;
indices six through twelve can read their explicit state18 but then refuse the
six-word table domain. Negative signed slot values are not silently wrapped into
an unrelated memory region. Missing row, pointer, actual byte or dispatch word
refuses at its reached load, with no speculative later scalar access.

`6b450` first reads and sign-extends caller.slot, then invokes10514. A nonzero
return skips housekeeping/request reads. Otherwise it reads actual73f, then
signed canonical73c. Nonzero73f or signed73c≤1 returns. Active request paths
remain explicit source boundaries: request2/3 stops at `6b544` before73d;
request4 stops at `6b4f4` before6e0; request5 stops at `6b4c0` before508 and the
later6e0 store. Values6..127 depend on incoming saved-register values not
initialized by this function and are refused rather than assigned defaults.
After any demonstrated early return, the outer caller refuses6b7f4, not the
later third-pass508 path.

For `5a298`, historical7d2 and housekeeping/request early gates remain unchanged.
In mode4a1 zero,10514's nonzero result returns without loading inputEdge5d4.
A zero result loads that actual word once and applies source priority: bit4 writes
request2, otherwise bit8 writes3, otherwise bit10 writes5; otherwise no store.
These hexadecimal bit names refer to values4,8,16. Destination writability is
checked only at the reached store. The nonzero4a1 pointer508/4a4 branch still
refuses; no pointer comparison is fabricated.

## Evidence and verification limits

The initial frozen archive selection was only the complete932-byte6b450 and
160-byte10514 bodies. The latter revealed an indirect dispatch. A separate
follow-on scope selected exactly40 bytes from the masked index, unsignedGT9
branch, stride4 and table-base instructions. The table extent is justified by
that authenticated reachable-address bound, **not** an independent map symbol.
Both scope records are retained. The two complete snapshots agree on all bodies
and table words. Shared authentication/mapping/decoder files were not changed.

The genuine opt-in fixture retains one bound actor and five inactive physical
records. Current values are explicit synthetic inputs. Tests cover source order,
all raw actor-status bytes, live target changes, input priorities, signed gates,
partial faults, identity and alias rejection, reentry and outer failure closure.
Older fixtures still omit the new ingress and retain their earlier boundaries.
No successful fake callee is used to advance the path.

Next work includes genuine `6b7f4` dispatch, active target selection and its
shared target owners. Full frame predecessors, six-actor hydration, normalization
provenance, positive flight/collision/damage and browser acceptance remain open.
Publication is coordinated separately.
