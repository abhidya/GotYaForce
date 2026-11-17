# Existing-evidence association inner scan, 2026-11-15

## Bounded continuation

This checkpoint continues the finite third-pass guards through the remaining
integer-only inner scan of `8006ae60`. The existing selected operands establish
`8006b3bc..8006b438`; no new archive payload or pointer-selected source data is
read. The full 380-instruction body remains the one authenticated by the
[target-preparation report](target-preparation-evidence-2026-11-14.md), with digest
`6b725b93ac0755d146b4a67fe61ec81127d98afccc77ca5c3fcd990fa199b50a`.

For every outer actor admitted by the preceding target83, flag, team and finite
distance gates:

1. Reload the physical base once at `8006b3bc`. Retain the same frozen six-record
   identity map for source pointer arithmetic.
2. Visit positions zero through five. Compare the candidate's physical index
   with the outer index before any mask or candidate scalar access. Self skips.
3. Load the captured target's actual `byte58a` freshly for each remaining
   position. Sign-extend the raw byte and test `1 << position`.
4. Only a mask hit resolves the candidate's actual actor and loads its raw team
   byte. Compare the signed value with the caller team captured before the
   distance comparison. There is no candidate active or lifecycle-state test.
5. On the first team match, perform three separate fresh read/modify/store pairs:
   caller `byte7d3 | 1`, candidate `byte7d3 | 1`, captured target `byte7d3 | 2`.
   Exit the scan immediately after the third store.

No match completes after six positions. Both outcomes continue with the next
outer row. A fully admitted target-preparation path returns to its caller and
still refuses at the mandatory `80027764` predecessor. This is not a completed
outer battle frame and does not grant scheduler authority.

## Ownership and partial effects

`byte58a`, team and `byte7d3` remain on the actual actors. No copied mask, flag
record, default value or alternate candidate roster is introduced. Candidate
resolution remains lazy and uses the same allocator pointer identity and world
actor. A candidate need not have an allocation-owned byte83 binding: the scan
does not read candidate83. The captured target retains its existing allocation83
and lifecycle guards.

Every reached scalar has pre/post owner and lifecycle checks. Frozen physical
metadata is checked without reloading the live global pointer. Canonical field
aliases, including numeric target58a and reached candidate flag/team aliases,
refuse. Final native descriptor checks close late metadata windows before an
existing own-data destination is overwritten. Accessors, missing cells,
nonwritable destinations and malformed raw bytes never become implicit defaults.

The three destination flags are not preflighted or snapshotted together. A later
load or store failure retains earlier completed stores. Subsequent flag loads
see prior writes when actual roles alias. In particular, a candidate that is
also the captured target observes its bit0 store before the final bit1 update.
Caller/target aliasing also retains source-ordered captured team values and
fresh flag values. Scalar mutation does not retarget the captured target or
retroactively change the captured caller team.

Failure preserves all preceding mass, candidate, distance, direction and
association effects, closes the retained graph, and makes retry unsupported.
These are the established synchronous nonproxy own-data host bounds, not a
claim about arbitrary JavaScript proxies or live concurrent processor memory.

## Verification and limits

The focused scan suite is wired into the existing attached-setup aggregate.
It covers zero/high masks, self-before-mask ordering, all reachable candidate
positions, signed raw teams, lazy team access, first-hit exit, fresh masks,
captured operands, fresh and alias-sensitive flag pairs, malformed bytes,
partial failures, late destination mutation, aliases, lifecycle closure,
reentry and fresh-base refusal. The earlier guard suite retains its unhydrated
target58a boundary rather than inventing a mask for existing fixtures.

The fixtures use the same genuine six-actor composition with explicit source
cell inputs. Their caller is activated only at the third-pass load. They do not
establish retail constructors, full active-actor predecessor hydration or
six-actor mass hydration; the documented repeated-primary mass-table caveat
remains. The preceding finite exact-f32 comparison domain is unchanged. NaN,
infinity, unordered execution and FPSCR exception behavior are not added.

`80027764` remains closed because its complete body is not authenticated in the
permitted selected evidence. No original asset, binary input, private capture
or generated artifact is published. Original execution, hardware parity,
sustained gameplay and browser playability remain outside this checkpoint.
