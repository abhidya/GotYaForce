# Bounded burst-mask and timer-expiry continuation

The existing outer-frame runtime now continues zero `8008b290` results through
complete `8008b480` and the integer timer-expiry branch of `80029d48`. This is
bounded offline execution, **not a completed battle frame, runnable scheduler,
retail replay, browser activation or playability claim**.

## Existing evidence and its limits

The caller is already selected in the paired ProgramDB-derived
[outer-frame evidence](outer-frame-evidence-2026-11-14.md), including the exact
operands at `80029d9c..80029ddc`. That evidence's original statement that the
callee was unselected remains historically accurate for that archive selection.
This increment does not select or read any additional archive member, binary,
DOL or live global. It does not run `src-match/verify.py` or the retired driver.

The distinct evidence for the callee is the **existing recorded matched-source
corpus**, not a newly authenticated paired ProgramDB body:

- `src-match/game/zz_008b480_.c` records the complete end-exclusive range
  `[8008b480,8008b48c)`, three instructions: `806d8394` (`lwz r3,-31852(r13)`),
  `886300eb` (`lbz r3,235(r3)`), and `4e800020` (`blr`).
- Its C-body SHA-256 is
  `fefc8366d0fc68371afbec1e38cd03a0e947bb8c008c1c70d8223e52fef8473c`, matching
  both the source header and `src-match/matched.json` entry.
- Header and registry record verified `R_PPC_EMB_SDA21` relocation at `+0` to
  `PTR_DAT_80433934`, retail address `80433934`. Recorded `r13=8043b5a0` plus
  signed displacement `-31852` also equals `80433934`.
- `exact_bytes:false` denotes the corpus's verified relocation-masked MATCH.
  It is not compile-only/unverified evidence. The recorded relocation was
  address-checked; this increment checks integrity of that record and makes
  **no fresh retail verification claim**.

`test_recorded_burst_leaf_evidence.py` runs in the normal matching-decomp
unittest discovery gate. It reads only these checked-in text files, verifies
words/operands, C-body/header/registry hashes and relocation/SDA consistency,
and rejects altered offsets, globals, words, operands and hashes. This is a
reproducible integrity check of existing evidence, not a retail oracle.

## Canonical inputs and exact source order

Only two optional fields are added: `byteEB` on the SAME scheduler/spawn match
owner (`80433934+eb`) and raw unsigned `half18` on the SAME existing team row
(`80433934+f4+3c*i+18`). No defaults, copied rows, shadow state, source hydration,
new callbacks, host timer or fabricated frame authority are introduced.

A populated burst row still clears `charged` before fresh `8008b290`:

1. Nonzero unsigned `byteD9` skips all new work for that row. Zero reaches
   `8008b480`, freshly loading the same match owner and its unsigned `byteEB`.
2. A zero EB result skips the row `+3` load. Otherwise load signed row `+3`
   (`lbz` then `extsb`) and bitwise AND it with the captured unsigned EB result.
   No overlap skips the timer and all current-row suffix inputs.
3. Load `half18` as raw `0..65535`, interpret it as signed `lha`, subtract one,
   capture the signed `extsh` result and store its low 16 bits back to `half18`.
4. A captured positive result refuses **before `80029de0`**, without reading
   the later timer, `half1a`, or unsupported floating constants. Original raw
   `8000` is signed `-32768`, decrements/wraps to `7fff`, and takes this positive
   refusal. It is not timer expiry.
5. A nonpositive result stores `meter=0`, then `byte10=0`, then **`meter=0`
   again**, at `29dd0`, `29dd4`, `29dd8` in that exact order. The repeated store
   is not deduplicated. Continue to the next row, with fresh D9 and EB leaves
   wherever reached.

Zero and all negative initial timers except `8000` expire after the stored
wrapped decrement. Positive one expires to zero. Larger positive timers stop at
the floating boundary after retaining their decrement store. Captured source
values govern branches even if an observable host check changes a valid cell;
only a later source load observes the new value.

All previous later boundaries remain: normal `53b30`/target preparation where
explicitly supplied, mandatory `27764`, and paused `0bef4`. The unsupported
floating constants `80436f08` and `80436f00` remain unselected. This work supplies
no scheduler traversal, object snapshot, actor frame, epoch or successful outer
frame return.

## Host bounds and partial failures

The declared host domain remains stable synchronous nonproxy own-data records.
Reached EB metadata checks retain scheduler/global, captured team table,
visited rows, slot-team and system owners, reject competing EB cells and raw
aliases, and preserve lifecycle closure and caught-reentry protection. Timer
aliases are checked only for rows whose `half18` is actually reached, including
both bytes and the corresponding global-relative halfword offsets. A skipped
row's timer fields and aliases remain lazy.

Each new store checks the full graph and its final writable own-data destination
using retained native descriptor intrinsics after the last observable inventory.
A late deletion, accessor, readonly destination, owner replacement, alias,
lifecycle closure or reentry cannot allow a stale write or invoke a setter.
The reached half18 input also retains its raw-width admission check at the
store. Meter and byte10 stores do not read their overwritten scalar values.
Previously completed roster, charged, timer and expiry writes are not rolled
back on failure; the entire retained scheduler graph closes permanently.

## Verification surface

`runBattleBurstExpiryHydratedCompositionTests` is a distinct exported wrapper
in `attached-setup-animation.selftest.ts`, wired into the normal ROM aggregate.
The dedicated suite uses only explicit synthetic cells on genuine existing
shared graphs. It covers:

- all four burst-row positions; zero, signed boundaries and halfword wrapping;
- EB masks including `80`/`ff`, negative signed row masks, no-overlap skips,
  EB-zero lazy row3, exact source/store order, and repeated meter stores;
- fresh per-row D9/EB, captured leaf/mask/timer results, mixed skipped rows,
  normal/paused boundaries, and unsupported floating inputs remaining unread;
- missing/inherited/accessor/invalid fields, readonly inputs/destinations,
  partial stores, and precise later-row refusal;
- final observable-inventory source/destination mutations, late owner/alias
  changes, independent lifecycle closure and caught reentry;
- absence of scheduler traversal, object snapshots or actor frame claims.

Older outer-frame/leaf suites still omit new fields explicitly and now expect
missing `byteEB` at the reached callee, instead of claiming `8008b480` itself is
unimplemented. Focused and strict results are recorded in external checkpoint
logs; they are not represented as full contributor or retail execution gates.
