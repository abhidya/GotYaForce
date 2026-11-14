# Bounded source mass/team preparation

The normal `80029434` branch now admits an explicit `80053b30` prefix after the
already authenticated `8b048 → 29d48` request/team update. This remains a bounded
offline source integration. It cannot complete an outer frame, invoke the
scheduler, select an actor epoch, or activate the browser clone.

Evidence: [mass-preparation-evidence-2026-11-14.md](mass-preparation-evidence-2026-11-14.md).
The complete selected body is 1344 bytes / 336 instructions. Its first RNG call
at `80053d60 → 800055fc` is not implemented. No source callback is injected.

## Source owners

- The same scheduler owns the `803c4e84` slot-pointer table. A read-only getter
  exposes its retained identity without loading slot cells.
- Separate explicit owners hold the 24 pointer words at `803c6dec` and four
  count bytes at `80436264`. They are not `80433934.teamRows103`, draw lists,
  allocator group lists, or a copied roster.
- Frozen physical-block metadata identifies a base and six distinct identities
  at successive `0x1e00` offsets. It is explicit host address metadata, not a
  source constructor or proof that retail memory was hydrated. Pointer-table
  entries need not have the physical order and may repeat a target.
- `RomActor.active0`, `team`, `modelScale`, and `supportContact1db` remain their
  canonical source cells. Only missing `mass208` is added, with no constructor
  default. The codec field map records its `f32 +0x208` location.
- Accumulated `+0x204` remains the existing **same Borg**
  `sourceArrowMass204` property, obtained through the root's genuine prehook
  status owner. No second `RomActor.mass204` is created and no
  `arrowCaptureMass` fallback or tier-size estimate is called.
- `+0x18` is the same root stage runtime's `lifecycle18`. `+0x4ac` is the same
  status/attribute binding. The genuine attribute registry supplies optional
  `field98` on the existing parameter descriptor, never the `4b0` descriptor.
- The explicit data owner must supply authenticated positive zero and `50000`
  when their source loads are reached. The authenticated suffix constant `1`
  is evidence only and is not consumed by this prefix.

## Implemented order and bounds

1. Clear pointer word 0, then capture table slot 0. Clear pointer words 1–19,
   count 0, pointer 20, count 1, pointer 21, count 2, pointers 22–23, count 3.
2. Walk six physical records from the captured base. Signed active byte zero
   skips the record's other scalar loads and stores. For an active record,
   load zero, clear its local stack count, reset canonical mass204, and load
   signed lifecycle18. The internal local count has no exposed host substitute;
   all uses of it remain beyond an explicit unsupported passenger/RNG boundary.
3. States 1 and 2 load parameter4ac, then threshold50000, then parameter98.
   Only a finite value below the threshold reads modelScale and multiplies.
   Other states store zero into mass208. Reload **unsigned** lifecycle18;
   only value1 appends to its signed team index. Increment the raw count byte
   before writing the actor pointer using the signed old count.
4. Independently reload all six slot pointers in the original three-pair
   order. Each target receives a nearest-even single-rounded mass204+mass208
   before its signed supportContact1db load. There is no active/state filter.
   A nonzero contact refuses before unimplemented actual pointer1e4 ownership.
5. After all six no-contact additions, refuse the mandatory first55fc RNG call.
   No shuffled order, global actor count, or subsequent scheduler call is made.

Finite exact binary32 operands/results, nearest-even/gradual-underflow
arithmetic, stable synchronous non-proxy own-data records, frozen address
metadata, and the explicitly supplied 24-word/four-byte storage domains are
host bounds. Signed indices are not clamped. A pointer index outside that owner
refuses after the earlier count store. These checks do not emulate arbitrary
FPSCR exceptions, unordered NaN comparisons, invalid-memory effects, or retail
execution.

## Ownership and failure

All reached records stay live. Per-source-width destination admission retains
prior completed writes. Known aliases, descriptor/owner substitution, accessor
storage, invalid pointers, and caught reentry refuse. Identity-only inventories
include retained status/Borg/slot/cell owners and genuine parameter descriptors;
these are host admission probes, not extra source scalar loads.

Every reached physical or pointer-table actor is retained for permanent
Double-lifecycle closure on failure, in addition to the existing scheduler,
allocator, and projectile graph closure. Closure never resolves a new pointer.
The outer runtime does not grant a scheduler invocation capability, clear an
incomplete latch, claim an actor epoch, or resume a failed frame.

## Validation scope

The focused fixture supplies one genuinely composed actor and five separate
inactive physical records. For the all-six accumulation path it explicitly
repeats the genuine actor's pointer; later tests mutate live pointer cells.
This demonstrates traversal/order and canonical-owner behavior on synthetic
inputs. It is not six hydrated retail actors, an authored successful battle
frame, hardware parity, or playability.

Source RNG55fc and shuffled actor ordering, nonzero passenger ownership, later
`6ae60 → 27764 → bef4` predecessors, full frame/epoch scheduling, positive
projectile flight/collision, the unresolved estimator, JObjUnref, and browser
activation remain unfinished.
