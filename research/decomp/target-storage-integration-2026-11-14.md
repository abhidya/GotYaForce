# Target sibling redirect and ordered state storage

This checkpoint completes the bounded genuine `8006b850` entry0 helper after
nearest-candidate selection. It reads canonical descriptor flags, optionally
redirects to a sibling OBJECT, performs all ordered target stores, and returns.
This completes one helper, not a battle frame or browser activation.

## Evidence and branches

The existing [target dispatch evidence](target-dispatch-evidence-2026-11-14.md)
selects `8006b850..8006ba60`, 528 bytes, SHA-256
`8a01e4c3f1a21269d2b9fb98b2d6c71ab2d46859d9670049069db7c6eafabb51`.
The extent remains C/index-bounded, not named-map-size-proven. Both fixed
snapshot reports already contain this suffix. No reader selection is widened,
original executable run, or estimator imported.

The preceding [distance lane](target-distance-integration-2026-11-14.md) now
retains the **last** raw scratch-count word loaded at `8006b9ac`, including the
load that terminates the signed nearest loop. The suffix uses that captured
word, not a newly loaded count.

- `9b8` captures the winner's actor pointer from OBJECT+20.
- Null skips descriptor and sibling reads and proceeds directly to commit.
- `9c4/9c8` load OBJECT+28 and its big-endian halfword at descriptor+2.
- If bit0200 is **set**, the selected OBJECT is already suitable and commits.
- If clear, the sibling loop runs only when the captured count is signed-positive.
- Starting at scratch index0, each iteration freshly loads the OBJECT and its
  +20 pointer. Only equality with the captured winner actor reaches descriptor
  +28/+2. The first same-actor OBJECT with0200 set becomes the winner and breaks.
- The loop uses captured CTR count, not distance ranking, a fresh count, active
  flags, teams, lifecycle or another winner-actor read. The4096 host limit is
  checked only at the reached scratch load, not as an eager count restriction.

## Canonical descriptor and pointer domains

OBJECT bytes and pointer words remain owned by the existing allocator.
A descriptor pointer can be its existing base-plus-offset interior identity.
For example, the genuine `8008ac80` HIT registration already writes OBJECT+28
as an interior pointer into the retained external pointer3fc byte table at
`aa0 + remap*50`. The suffix resolves that same base and offset, then reads
exactly the two original bytes. It does not copy a flag table or require the
unrelated pool0 allocation descriptor layout.

Descriptor byte owners cannot be canonical actors, vectors, matrices, helper
records, or their retained direct references. Metadata-only admission is repeated
after each reached byte load, so even a byte table that becomes an actor vector
between the two loads refuses before any target commit. Numeric2/3 properties
on structured records do not establish a descriptor byte owner.

Tests exercise a genuine HIT-registration result and its actual interior
pointer. Candidate-list membership, actor association and field values remain
explicit synthetic inputs; real target-list production is not established.

The source target pointer cells are the existing command-admission binding:
`pointer504` stores the exact selected OBJECT record and `pointer508` stores
the exact allocator-resolved object from the final fresh +20 load, or null.
Symbolic handles, copied objects and a second pointer registry are not stored
in those cells. Pointer508 is not required to equal the earlier captured actor:
the source explicitly reloads it at commit time.

## Exact commit order

1. `ba1c`: store byte502=1 on the actual actor.
2. `ba20`: store selected OBJECT in canonical pointer504.
3. `ba24/ba28`: freshly load selected OBJECT+20, then store pointer508.
4. `ba2c/ba30`: capture both raw words OBJECT+64 and OBJECT+68.
5. `ba34/ba38`: store those captured words to target X/Y.
6. `ba3c/ba40`: freshly load OBJECT+6c, then store target Z.
7. Return through the authenticated epilogue at `ba44..ba5c`.

These are integer word copies, not a three-component floating load or a
preloaded target-position snapshot. The bounded host vector stores decode each
captured word only when that destination is reached. Finite binary32 bit
patterns and signed zero are preserved. Nonfinite words are refused rather
than claiming preservation of arbitrary NaN payloads. If Y cannot be loaded,
X is not stored; if Y cannot be stored, X remains stored; Z is loaded only after
both preceding stores. Existing writes are never rolled back.

## Selected position and legacy naming

The existing actual-actor `lockTarget` Vec3 surface is promoted to optional
RomActor source50c/510/514 storage, with no constructor default. Helpers borrow
that same type rather than declaring a second vector owner. An explicit
nonnull own-data vector is required only when its first store is reached.
Its identity is retained, and it cannot alias existing actor vectors, other
actors, canonical records, matrices, descriptor bytes, processor profiles,
projection scratch or other helper storage. The shared ownership registry
also prevents later reuse as allocator bytes or helper scratch.

The historical field name does **not** make old host targeting source-exact.
Legacy bridge code may populate lockTarget from approximate or captured attack
aiming state. Existing audits document the separate captured518 versus
shooter-origin issue. This change establishes only the explicit selected50c
contract in the source-owned graph. It does not activate legacy aiming helpers,
change bridge target policy, complete capture518, or compute distances760/764.
Double-action storage checks now admit lockTarget only on its actual actor,
while command-admission reference checks protect the distinct selected vector.
The deterministic field map records this explicit vector at50c.

## Completion guards and next boundary

All accepted actor identities remain guarded through the suffix, including
after null or rejected candidate entries. Caught reentry, owner changes,
invalid byte data, nonwritable destinations and later failures permanently
close an incomplete caller, preserving the exact completed store prefix.

Success returns from the helper and leaves target state1. A later dispatch
still refuses unauthenticated selector1; it does not invent the8006ba60 table
cell or replay entry0. The real outer composition now refuses at `8006af8c`, immediately after the
helper returns. Source review found that the previous outer composition skipped
mandatory second-pass work and advanced to its third pass. This newly reachable
gap is closed before any primary-target pointer read, next physical actor, or
third-pass reload. No scheduler capability or complete-frame result is synthesized.

The fixed6ae60 operand reports require `af8c` to load canonical508 and branch on
null, with no global load before that branch. Nonnull then loads504 and calls
SquareDistance at `afac` with actor+20 and provider+64, before loading80437658.
Null instead loads80437678 at `b180`, stores75c then758, loads heading72 and calls
45204. The readable C hoists a constant expression and is not proof of its actual
load order. The existing full1520-byte evidence covers these predecessors; this
checkpoint neither skips them nor imports a replacement estimator.

Next work is source-backed primary-target preparation from8006af8c, followed
by later mandatory outer work. The separate third-pass target83 owner can be
reached only by rows that legitimately skip the second pass. Real target-list
production and remaining actor/projectile hydration are also unfinished. This remains bounded synthetic offline
integration, not `MATCH`, hardware parity, complete gameplay or playability.
