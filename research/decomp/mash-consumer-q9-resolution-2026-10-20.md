# Q9 mash counter — consumer resolved at ROM level (2026-10-20)

Round-2 wiring pass, item #3. Q9 asked: *"What consumes the mash counter
+0x550 past the cap-4 comparison — extra hitbox activations, duration
extension, or something else?"*

**Verdict: the consumer is inside the same function that counts. The effect
is an early phase advance of the attacker's own attack-active state — the
"duration" branch of Q9's alternatives, applied to the attack, not to a
freeze. It is NOT extra hitbox activations.** Two long-standing mislabels
are corrected along the way. The port keeps `MASH.ENABLED = false`: the
ROM effect is now evidenced, but the port's swing state machine has no
evidenced mapping onto slot 23's phases, and inventing that mapping would
be a guess (details below). The port's existing counting scaffold also
diverges from the ROM counter in two concrete ways (below).

## The site, read in full

`FUN_8005d494` (chunk_0007.c:4678-4825) is state-table **slot 23** — the
melee attack-active/execution handler (behavior-notes (u): it re-arms the
invincibility timer `+0x720 = 60.0` on every call and resolves the attack
sub-move from the command-type selector `+0x591`). Its local phase byte is
`+0x544`. The mash fields are the handler's local scratch:

- **Phase 0 (entry):** `+0x550 = 0`, `+0x552 = 0` (chunk_0007.c:~4742);
  launch direction is computed from `+0x591` subtype tables.
- **Phase 1:** if the raw input word `+0x5b4 & 0x700 != 0`, set
  **`+0x552 = 1`** — an any-button latch, not a hitstop field. If the
  one-frame event flag `+0x1d10 == 1`, **`+0x550 += 1`**
  (chunk_0007.c:4810) — **with no cap at the increment**. The constant 4
  exists only in the comparison below; findings T's "cap 4" and the port's
  `PRESS_CAP` comment ("the counter itself stops at 4") are mislabels.
  (`+0x1d10` sits in the animation-channel byte block +0x1d0e/+0x1d0f/
  +0x1d10; no scalar store setting it to 1 was isolated in the corpus, so
  "player press edge" is the plausible-but-unproven reading — its events
  may be cue-stream-derived. Increments also only occur for command types
  `+0x591 ∉ {1,2}`.)
- **The consumer** (chunk_0007.c:4813-4818): if `+0x1d0f == -1` → phase 4;
  else if **`(4 < +0x550) || (+0x552 != 0) || zz_0066ac0_(actor, 0) == 0`**
  → **`+0x544 += 1`** (advance to phase 2). `zz_0066ac0_` decodes the
  stick-direction word (`+0x5b4 >> 16 & 0xf`, chunk_0008.c:3428ff) and
  returns 0 when NO direction is held — so the third path is stick
  release, not ground contact. For command types 1/2 the latch/stick
  path instead jumps straight to phase 3 (chunk_0007.c:4802-4808).
  Phase 2 starts the execute clip (`zz_004beb8_` sub-id `+0x1d0f + 4`)
  and commits facing; phase 3 waits on the anim-completion byte
  `+0x1d0e`; phase 4 exits via the return-to-neutral trampoline
  `zz_006a474_`.

So: five counted events during phase 1 — or a single press of any of the
three `0x700` buttons, or releasing the stick — end the pre-execute
phase 1 early and start the execute clip sooner. No hitbox is armed,
extended, or re-triggered by `+0x550` anywhere in the handler (hitbox
arming lives in the cue streams the clip starts, not in this function);
nothing outside the handler reads this instance of the fields.

## Why +0x550/+0x552 confused earlier passes

They are **generic per-action scratch fields**, reused by unrelated
handlers with unrelated semantics — e.g. the fusion action handlers
`FUN_80062c7c`/`FUN_80062e44` (chunk_0008.c:828-1010) use `+0x550` as their
own phase countdown (set 60/30/0) and clear `+0x552` at a phase entry;
chunk_0007.c alone contains dozens of other `+0x550` writes (0x2f, 0xf0,
8, decrements of 1 and 3, …). Any corpus-wide consumer claim for these
offsets is meaningless unless scoped to one handler. Scoped to slot 23,
the chain above is complete: writer, counter, latch, gate, and effect are
all in one function body.

## What this does NOT settle

1. **Gameplay reading of the phase advance.** Phase 1 has no timer of its
   own — it ends only via the gate (or the `+0x1d0f == -1` direct exit),
   so it reads as a hold/buffer window before the execute clip. Whether
   phase 1 itself carries an active hitbox cannot be settled from the
   handler's C: hitbox arming lives in the animation cue streams the
   clips start (`zz_004beb8_`), not in these functions. The guide-side
   observations (multi-hit moves gaining hits; freeze mash-to-recover,
   behavior-notes (an) item 5) are NOT explained by this site — for
   freeze, behavior-notes (bd) establishes the freeze timer `+0x71c` and
   its tick `FUN_8005a378` reads neither `+0x550` nor any mash input, so
   the freeze hypothesis has no static link and stands or falls on a
   decay-rate trace.
2. **Port mapping.** The port's melee swing (combat.ts) runs on its own
   TUNED startup/active/recovery structure, not on slot 23's `+0x544`
   phases. Wiring "mash advances the phase" requires first evidencing
   which port swing segment corresponds to slot-23 phase 1 per move
   family. The port's counting scaffold (combat.ts ATK-017 block) also
   diverges from the ROM counter it cites: it CLAMPS the count at
   `PRESS_CAP = 4`, so the ROM's `4 < +0x550` condition could never fire
   against it (the ROM counts uncapped and gates at 5+); and it counts
   only the attack button's edges, where the ROM's second path (`+0x552`)
   latches on ANY of the input bits `0x700`. Both are comment-level
   corrections in this pass; the scaffold stays consumer-less.

## Settling trace (what would close the port side)

T2 mash logging, per attack-mechanics-trace-plan.md: on one borg in slot
23 (`+0x6fe == 14`) executing a `+0x591 ∈ {4,5,6}` move and, separately,
a `+0x591 ∈ {1,2}` move, log per frame `+0x544`, `+0x550`, `+0x552`,
`+0x591`, `+0x1d0f`, `+0x1d10`, `+0x5b4`, plus hit-event / object-spawn
counts, under three input runs: (i) no further input, (ii) ≥ 5 `+0x1d10`
events in phase 1, (iii) a held `0x700`-mask button. Phase-1 frame counts
dropping in (ii)/(iii) with IDENTICAL total hits falsifies "extra hits";
more hits in (ii) would point the dig at the phase-0/phase-2 cue streams.
Separately, the freeze test: log `+0x71c` per frame frozen with zero
input vs maximal mashing — identical −1/frame decay kills the (an) §5
hypothesis; faster decay confirms it and measures the rate.

## Port changes made with this note

Comments only (no behavior change; `MASH.ENABLED` stays false): the
`MASH` block in `packages/combat/src/constants.ts` and the ATK-017
scaffold comment in `combat.ts` no longer describe an unknown consumer or
a capped ROM counter; they point here.
