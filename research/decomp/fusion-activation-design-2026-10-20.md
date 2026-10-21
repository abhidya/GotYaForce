# Power Burst fusion activation — design (2026-10-20)

Round-2 wiring pass, item #10 activation. **Deliverable: design only, no
runtime code.** The activation state machine turns out to be FULLY decoded
in the corpus (this doc assembles it from primary reads, and reconciles
the +0x6fb question that trace T3 was supposed to settle). What blocks
implementation is not missing ROM knowledge — it is three port-side gaps
named precisely at the end. The data layer (`fusionPairs.ts`, PR #4) and
the runtime fields (`BorgRuntime.fusionPartnerUid` / `fusionState`,
types.ts) are already in place for the future slice.

## The decoded machine (all citations primary)

### Trigger & match — `zz_005b2b8_` per-player loop (chunk_0007.c:3354-3494)

Per player slot, per frame, the engine counts the player's ACTIVE borgs
whose arm byte `+0x6fb != 0` (the 6-frame Y-press window set by
`FUN_80069814`, chunk_0009.c:104-115). A match is attempted when the
player's charged flag is set and ≥ 1 borg is armed, or when ≥ 2 borgs are
armed. The match runs BEFORE any burst assignment:

- **Match found** (`zz_005b678_`, below): both actors' link state is
  cleared (`zz_005c15c_`), `+0x8c4` bit 1 cleared on both, `+0x4a1 = 1` on
  both, and action **0x19** is triggered on both (`zz_006a750_`).
  No burst flags are set in this branch.
- **No match**: the fallback is the ordinary burst — player burst timers
  set to 600, every active borg of the player gets `+0x6fc = 1` (burst
  active) and `+0x6fa = 1` (paired). This is the branch the port's
  `tryActivateBurst` / side-wide activation already models.

### Match — `zz_005b678_` (chunk_0007.c:3518-3574)

Iterates ordered pairs (i < j) of the player's borg list. For borg A:
family byte `+0x3e8` indexes the pair table `DAT_802d352c`; the variant
byte `+0x3e9` selects A's sub-list of (partnerSpawnId, resultSpawnId)
s16 pairs, -1-terminated. The first later borg B whose spawn id appears
in A's sub-list wins. On a match:

- `+0x4a4` (partner pointer) is set bidirectionally — in-place link, no
  new actor is spawned.
- Result ids: in the role-split branch (one actor flagged `+0x3e6`, roles
  `+0x4a8` = 2 on the other), A stores `result` at `+0x48c` and B stores
  `result + 1`; otherwise each stores `result + own(+0x4a8) - 1`. Roles
  are copied to `+0x4a9` (needed at unfuse). The head/level byte `+0x3ec`
  of the `+0x4a8 == 1` actor is copied to both actors' `+0x48e`.

### State machine on +0x4a1 (per-actor byte; both actors advance in step)

| From | To | Where | Condition / effect |
|---|---|---|---|
| 0 | 1 | zz_005b2b8_ caller | match success; action 0x19 triggered on both |
| 1 | 2 | FUN_80062c7c phase 2→3 | action-0x19 approach completes (anim event via `zz_004cd24_`) |
| 2 | 3 | zz_005b2b8_ per-slot loop | BOTH actors at 2, partner alive+active: both → 3; `+0x6fa = 1` on both; shared facing = average of both `+0x72` yaws written to both (`+0x5a8/+0x5ac`); midpoint of both positions written to both (`+0x7a4/+0x7a8/+0x7ac`, ground-snapped; family-6 and result-0x513 special cases); `reset_actor_param_tier` on both |
| 3 | (phase) | FUN_80062c7c phase 3→4 | seeing own state == 3 advances the action phase; at phase 4 end the handler triggers action **0x1a** |
| — | 4 | FUN_80062e44 phase 0 | action-0x1a entry sets `+0x4a1 = 4`; velocities zeroed; launch prep from stored midpoint |
| 4 | 5 | FUN_80062e44 phase 1 | actor homes to the shared midpoint (+0x7a4…) with growing speed (+0x568); on arrival (dist² ≤ FLOAT_80437598) snaps to the midpoint, `+0x4a1 = 5` |
| 5 | 6 | zz_005b2b8_ per-slot loop | BOTH at 5 → both 6 (locked) |
| 6 | (phase) | FUN_80062e44 phase 2→3 | seeing own state == 6: launch velocity computed from the partner's `+0x668` (role-signed by `+0x4a8`), `+0x550 = 30`, `+0x552 = 0` |
| 6 | 7 | FUN_80062e44 phase 4 | phase countdown (+0x550) reaches 0 → `+0x4a1 = 7` |
| 7 | 0 | zz_005b2b8_ per-slot loop | BOTH at 7 → unfuse: `+0x4a1 = 0`, role restored `+0x4a0 = +0x4a9`, weapon bytes `+0x272/+0x273 = -1`, and **`zz_006a868_(actor, +0x48c, +0x48e)` re-initializes the actor as the stored RESULT borg** |
| any | 0 | zz_005c080_ (chunk_0007.c:3909) | actor cleanup clears `+0x4a1` on both partners |

Action-handler internals (chunk_0008.c:828-1010, and a twin pair at
:2423-2571 for the second role): the 0x19 approach phase is timed by the
local scratch `+0x550 = 60` countdown while seeking the partner's
position (`zz_00666c8_` target = partner `+0x20`); the 0x1a handler's
phases reuse `+0x550` (30 at lock, then a final countdown whose initial
value is set in the phase-3 tail — that one assignment was not read;
treat as unread, not guessed).

### The +0x6fb reconciliation (the T3 question, mostly answered)

`+0x6fb` has ONE role, visible end-to-end in `zz_005b2b8_`: it is the
per-borg arm/simultaneity window. It is set to 6 on a Y edge
(FUN_80069814), counted by the match logic above while nonzero, and
decremented once per frame at the tail of `zz_005b2b8_` across the six
borg slots (stride 0x1e00). Its expiry closes the window; it does NOT
drive fusion duration — fusion duration is the 0x19/0x1a actions' own
phase timers, and fusion end is the state-7 handshake above. The earlier
"dual-read" framing (aj) conflated the decrement site's location (same
function as the fusion loop) with a second semantic. What T3 is still
needed for is the CONTROL question (below), not the timer.

## Why activation is not implemented in this pass

1. **Identity swap has no port seam.** Unfuse re-initializes each actor
   AS THE RESULT BORG (spawn ids at +0x48c, i.e. the fused form persists
   as the actor's identity). In the port, `BorgRuntime.borgId` keys the
   command tables, hit tables, damage family, movement page, and the
   game's render/asset layer, all bound at spawn. A safe implementation
   needs a re-init seam (respawn-in-place) that does not exist yet;
   bolting one on inside a research pass would touch apps/game rendering
   assumptions.
2. **Control split is genuinely unresolved.** Corpus: both linked actors
   read the SAME command struct (`+0x4b0`; the 0x1a handler reads the
   partner's `+0x4b0 + 0x4c` float). Guides: control splits
   movement-vs-attacks per player (behavior-notes (an) item 3 flags the
   contradiction explicitly). Baking in the corpus reading risks the
   most visible behavior in the feature being wrong; this is exactly
   what T3 must log (per-player input words `+0x5b4/+0x5d4` on both
   actors during states 3-6).
3. **Match iteration order needs the port's per-player borg list to be
   ROM-shaped.** The ROM takes the FIRST pair in the player's borg-list
   order. The port's battle roster is side-based; a per-player ordered
   active-borg list exists implicitly (ownerPlayerId + spawn order) but
   has not been verified as the iteration the ROM uses when a player
   fields 3 borgs with two possible pairs.

## Implementation shape when the blockers clear

- In `battle.ts`, at the point where paired burst activation is resolved
  today (`tryActivateBurst` callers, ~line 953-990), insert
  `tryFusionMatch(player)` BEFORE the burst fallback — same order as
  `zz_005b2b8_`: attempt match over the player's active borgs using
  `fusionResultForPair` (fusionPairs.ts); on success set
  `fusionPartnerUid` both ways + `fusionState = 1` on both and DO NOT set
  burst flags; on failure fall through to the existing burst path.
- A `stepFusion` in battle.ts mirrors the per-slot loop transitions
  (2→3 with shared facing/midpoint, 5→6, 7→0) and a minimal 0x19/0x1a
  phase driver (approach-to-partner 60f, home-to-midpoint, locked,
  ending) — with every duration taken from the table above, and the one
  unread countdown left as a named TUNED constant until traced.
- Gate the whole path behind a `FUSION.ENABLED` constant (default false)
  until the identity-swap seam exists, so the match code can land and be
  selftested without changing live battles.

## Remaining trace questions (T3, narrowed)

1. Per-player input routing during states 3-6 (control split — the only
   true blocker above that is a ROM question).
2. The 0x1a phase-3 tail assignment to +0x550 (final countdown length).
3. Whether the 600f player burst timer also runs during fusion (the
   no-match branch sets it; the match branch does not — corpus says no,
   a trace can confirm cheaply while logging #1).
