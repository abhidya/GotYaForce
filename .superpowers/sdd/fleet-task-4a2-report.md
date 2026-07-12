# Fleet Task 4A2 report: Girl host-helper proof gaps

## Final status

PARTIAL at the eight-constructor level. The host-helper, afterimage child, pose housekeeping,
descriptor convergence, steering, and floor primitives are executable. Seven Girl slots are
certified after final review; action-1 and other part-anchor-dependent slots remain partial.

## Exact afterimage lifecycle

- `zz_00b22f4_` preserves `+0x80c` interval 8, displacement spacing
  `100 * +0xb4 * +0x7fc`, last sample `+0x800/+0x804/+0x808`, reset-before-spawn, and the
  unconditional `+0x768` increment.
- `zz_00b2190_(owner,1)` allocates subtype 1 and dispatches through `FUN_800b26cc` to
  `FUN_800b2708`, `FUN_800b2924`, and `FUN_800b2b20`.
- Config `0x802fc758` selects efct-bank id 69 and a 20-frame lifetime. Scale track
  `0x802fc588` is `(1,1,1)` at frame 0 to `(1.25,2.5,1.25)` at frame 20. Alpha track
  `0x802fc5b8` is `1` to `0` over the same interval.
- Initial transform uses base scale `owner +0xb4 * +0x7fc`, subtracts local forward by
  `50 * baseScale` using owner `+0x5ae` lock yaw, and seeds a discrete random BAM yaw.
- Object `+0x84=0x1e` is consumed as `FUN_80047aa4` transform flags: local X/Y/Z rotation
  bits plus authored scale. The host bank-FX renderer now consumes these flags directly;
  subtype 1 applies its Y yaw and scale tracks. No cloned actor model, inferred opacity,
  linear eight-frame fade, or eight-frame TTL remains.

## Other helper surfaces

- Surfaced and reset signed `+0x7c/+0x7e/+0x80` pose accumulators and `+0x80c` at recovered
  Girl boundaries.
- Implemented descriptor-driven `zz_006e514_`, descriptor BAM16 face convergence, target-loss
  behavior, `+0x518` aim origin, and exact `+0xac/+0xae` rate selection.
- Synced `+0xb4` from param-tier size and `+0x7fc` from
  `max(dataPage+0x4c,+0x50)/167.75999450683594`; pl0308 uses 25/3 and other Girls 9/6.
- Implemented supported snap, grounded return, unsupported saved-position revert, and
  `+0x5e0&0x40` preservation for `zz_00677b0_`/`zz_00679d0_`.

## Classification

Final promoted Girl keys:

- `0x800c04c0:0`
- `0x80106e3c:0`
- `0x80107e7c:0`
- `0x8019c380:0`
- `0x80134078:0`
- `0x8012f204:0`
- `0x8012f204:2`

The seven action-1 entries were demoted because `zz_006e514_` shares the unresolved
renderer part-row anchor. Other anchor-dependent X slots remain partial. Coverage is
119 constructors / 325 slots: ported 20, delegated 0, inactive 0, partial 234, missing 71.

## Focused evidence

- Exhaustive 182-live-route Girl handler and bridge matrix, with every exclusion.
- Afterimage interval/displacement branches and two-actor cache ownership.
- Divergent heading/lock-yaw regression proving the 50-unit child offset uses `+0x5ae`.
- Presentation tests for exact id 69 placement, `+0x84=0x1e` transform flags, authored
  frame-0/frame-10/frame-20 scale and alpha values, serial de-duplication, and disposal.
- Descriptor pitch selectors/target loss and supported/unsupported/frozen floor branches.

## Verification

- Combat build: PASS.
- Game typecheck: PASS.
- Full ROM selfcheck: PASS.
- Focused presentation selfcheck: PASS.
- Default audit: PASS with counts above.
- Strict audit: expected FAIL for remaining repository-wide partial/missing slots.
- `git diff --check`: PASS.

All task changes remain uncommitted. Existing unrelated worktree changes were preserved.
