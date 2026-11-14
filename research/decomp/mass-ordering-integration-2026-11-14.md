# Source mass ordering and explicit byte RNG

Date: 2026-11-14. Local continuation of `c0db2c16`.

The normal branch of `battle-outer-frame.ts` now continues the genuine no-contact
`80053b30` path through both `800055fc` calls, cyclic ordering, and the physical
role1 insertion pass. A completed bounded call returns to `80029434`, which
immediately refuses its next mandatory predecessor, **`8006ae60` at `8002945c`**.
This does not grant a scheduler invocation, actor epoch, completed outer frame,
ordinary actor hydration, browser activation, or playability.

Evidence is the existing complete
[mass-preparation body](mass-preparation-evidence-2026-11-14.md) and newly selected
[52-byte RNG body](rng-evidence-2026-11-14.md). The latter is identical in both
archived snapshots; no initial RNG state bytes or additional caller bytes were
selected. No third-party estimator code, `Math.random`, default seed, or idealized
normalization is introduced.

## Canonical source owners

- Existing actor `slot` remains +3e4; the source loads its raw byte and then
  sign-extends it. Existing world binding `mode4a0` remains +4a0 and must agree
  between the genuine projectile-spawn world and retained status runtime.
- New optional actual-actor `field664` is the missing four-byte source reset
  destination. It has an explicit codec annotation and no constructor default.
- Existing genuine matrix-update binding `link4a4` remains +4a4. The optional
  `massPreparation.matrices` must agree on actual/world/mapping/global identities and be the exact
  correction owner already retained by the genuine world runtime.
  There is no new parent pointer on the actor, status record, or mass record.
- Explicit `rngState.byte804360c6/c7` is one retained mutable global-byte record.
  Both source calls use that same owner. The legacy generic `prng.ts` module's
  implicitly initialized singleton is neither imported nor used by this source
  path. This explicit ingress is not a boot initializer or a measured live seed.
- `orderPointers` is a separate six-word `DAT_803c4e6c` record;
  `orderCount.count80436260` is a separate raw global byte. Neither aliases the
  live actor table, compact team lists/counts, match globals, draw lists, retained
  actor records, or other reached source storage.

All newly supplied owners are retained by identity only when reached. Stable
synchronous non-proxy own-data records remain a host admission bound. Missing,
nonwritable, wrong-width, replaced or competing owners refuse at the reached
operation; earlier source effects are retained. Outer failure closes the retained
scheduler graph and every additionally reached actual actor. It does not execute
or manufacture a successful source callback.

## Source order, including uncommon cases

Each RNG call loads unsigned high then low, computes the three-times recurrence,
stores high first, stores low second and returns the low byte. The old low byte
is captured once. A low-store failure leaves the completed high store intact.
Both calls finish before ordering count is cleared; count is cleared before the
single authenticated +1.0 load. Initial index is `(first >> 2) % 6`; second-result
bit3 selects +1 or -1. Six live slot pointers are loaded in that cyclic order.
Every visited actor receives +664=1.0 before the active and mode gates, including
inactive actors. No roster snapshot or deduplication replaces those loads.

Private stack counters are initialized to zero only at **active physical indices**
in the earlier captured six-record traversal, not at `actor.slot`. Inactive bytes
remain uninitialized. Comparisons load the existing list pointer, candidate slot,
existing slot, candidate local counter, then existing local counter. A reached
negative/out-of-domain slot or uninitialized local byte is refused. No-contact
counters stay zero, so normal ties preserve cyclic order. Strict descending
passenger-count insertion remains unreachable within the admitted no-contact
subset; its order-preserving shift implementation is not evidence of a completed
passenger graph. Nonzero +1db still refuses before unsupported +1e4 ownership.

Append reloads count, stores its wrapped increment, then stores the actor pointer.
Insertion shifts backward using the captured count; after a fresh count load it
stores the actor pointer **before** the wrapped count increment. Each shift is a
source pointer read followed by its destination store. List pointers are never
cleared. The final physical pass freshly loads actor-table[0], then uses the
explicit contiguous block mapping. A changed base without a matching explicit
mapping is refused, not silently treated as the original block.

An active role1 actor scans `capturedCount + 1` entries, including its stale logical
tail. Each comparison loads the list pointer before freshly loading canonical
+4a4. Neither pointer is dereferenced merely for equality. Thus an explicit null
parent can match an explicit stale null list word and insert; a nonnull guard
would invent source behavior. No match means no insertion. The bounded six-word
host list refuses a reached index6: retail address arithmetic would overlap the
adjacent actor-slot table there, and this implementation does not invent a seventh
independent word or silently emulate that overlapping storage.

## Verification and coverage ceiling

The aggregate ROM selfcheck includes a new genuine composition suite. It retains
the earlier mass-only fixture unchanged, then adds explicit RNG/order/664 inputs
in a separate fixture. The ordinary positive fixture has one genuinely bound actor,
five inactive physical records and six repeated live slot pointers. It is not six
retail-hydrated active actors. Tests can observe source access boundaries and make
explicit synthetic interruptions, but do not replace mandatory callees with
successful mocks or manufacture a source scheduler epoch.

Reproduction:

```
node node_modules/typescript/bin/tsc -p packages/combat/tsconfig.json --noEmit --pretty false
pnpm verify:contributor
GF_ATLAS_SKIP_MODELS=1 pnpm verify:docs
python -m unittest discover -s research/tools/matching-decomp
python -m unittest discover -s research/tools/matching-decomp -p test_archived_rng_evidence.py -v
```

The 14 RNG evidence tests independently cover all 13 operands, full inverse hash,
416 instruction-bit controls, 416 payload-bit refusals, all 65,536 raw input-byte
pairs, mapping/schema failures and exactly one added payload selection per snapshot.
These are static and synthetic source-semantic checks, not original execution,
original-DOL identity, `MATCH`, hardware parity or browser acceptance.

Remaining work includes +1e4 passenger ownership, full actor/slot hydration, actual
`8006ae60`, `80027764`, `8000bef4` predecessors and their shared globals, then the
real scheduler/frame authority join. Existing normalization estimator provenance,
nonnull Unref, positive projectile flight, collision/damage and browser activation
gaps remain unchanged. Publication is coordinated separately.
