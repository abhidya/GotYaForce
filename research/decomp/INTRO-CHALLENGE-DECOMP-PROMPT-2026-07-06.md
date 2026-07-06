# Hand-off prompt: continue decomp/deobfuscation — Intro + Challenge mode 1:1

Paste this whole thing as the opening message of a new session with file + shell access to this
repo. **Part 1 (Priorities 1-5) is a static corpus dig** — grep the existing decompile, read raw
ROM bytes, cross-reference against the port, no Dolphin needed. **Part 2 (Priorities 6-8) is
Dolphin-in-the-loop** — it needs a running Dolphin instance (the user's own disc/saves) and a
human or computer-use driver to press buttons through the scripted scenario; the harness records,
it doesn't play. Pick a lane based on what's available this session — Part 1 can run standalone.
It supersedes nothing; `research/decomp/HANDOFF-PROMPT.md` and `CHALLENGE-1TO1-PROMPT.md` are
earlier-phase versions of this same umbrella — most of their items are now DONE (see
`PORT-1TO1-STATUS.md`), this prompt picks up where the 2026-07-05 sessions left off.

---

## Context (2 minutes)

`D:\GotYaForce` is a from-scratch TypeScript/web port of **Gotcha Force** (GameCube, GG4E
NTSC-U). The port is playable end-to-end. The authoritative status tracker is
`research/decomp/PORT-1TO1-STATUS.md` — **read its top few session entries and §0 (executive
scorecard) and §4 (Challenge flow) before starting**, so you don't re-derive something already
DONE. The lab notebook is `research/decomp/behavior-notes.md` (append lettered sections, never
renumber).

Ground truth sources, all local:
- `research/decomp/ghidra-export/` — full decompile of `boot.dol`, 11,972 functions.
  `_index.tsv` maps address→name→chunk.
- `research/decomp/organized/` — the same corpus re-bucketed one-function-per-file by subsystem
  (`_map.tsv` for lookup); regenerate with `node scripts/reorg-decomp.mjs` if stale. Prefer this
  over reading whole chunk files.
- `research/decomp/dol.py` / `disasm.py` / `ppc.py` / `offsets.py` — raw-byte + PPC32 disassembly
  helpers for reading DOL data directly (float/table constants, opcodes not in the decompile).
  `scratchpad/ppc_disasm.py` was used for the stream-VM opcode disasm (see below) — same pattern.
- `research/decomp/data/*.json` — already-extracted raw ROM tables (damage, type matrix, spawn
  pools, knockback modes, movement physics, etc.) — check here before re-extracting anything.

**DERIVED vs TUNED discipline (non-negotiable):** DERIVED = confirmed from decompiled C, raw ROM
bytes, or a live trace, with the address cited. TUNED = an explicit labeled guess. Never silently
upgrade a TUNED value on a partial match. Every new finding: `behavior-notes.md` section
(address + evidence) **before** touching any TS code, then update `PORT-1TO1-STATUS.md`'s
relevant table row. This session is scoped to be **decomp/identification-first** — TS code
changes are welcome once a finding is solid enough to port (see the ROM-family-engine pattern
below), but don't force a port before the finding is actually confirmed.

## What's already done — don't re-derive

- **Intro/title state machine**: fully decoded and ported 1:1
  (`apps/game/src/ui/intro/titleVm.ts`, `research/decomp/tdc-archives-decode-2026-07-05.md`,
  `title-intro-remaining-decode-2026-07-05.md`). The desk scene, camera, both actors (G RED +
  Sasuke), and the script VM driving them are real ROM bytecode. Two residuals are open — see
  Priority 1/2 below.
- **Challenge flow tables**: stage rotation/family-roll, team generation, battle counts/energy,
  timer, win/lose/draw judge, 3-phase deploy, kill accounting, results scoring, Borg-GET drop
  pipeline — all DERIVED and wired (`PORT-1TO1-STATUS.md` §4, all rows DONE except one
  low-value pixel-trace caveat on arena-name texture binding).
- **The big cross-cutting architecture finding (2026-07-05)**: real per-borg move MOTION lives
  in unique per-family C state machines (`action-vm-and-gcrash-decode-2026-07-05.md`), not shared
  archetype data. A ROM-faithful runtime for this now exists at `packages/combat/src/rom/*`
  (foundation done, unit-tested — `pnpm selfcheck:rom`) with **one family ported** (G RED's
  X-special, `families/gred.ts`). This affects Challenge mode too, since Challenge battles run
  the same combat sim. See `packages/combat/src/rom/PORTING.md` for the per-family porting
  recipe — you'll reuse it for Priority 4 below.

## Priority 1 — Intro: resolve the anim-bank family-ctor binding (`+0x1d80`)

`title-intro-remaining-decode-2026-07-05.md` §1. `zz_0057ff8_(actor, 5, animId)` →
`zz_004beb8_(rate, actor, 0xf, groupSel=5, animId, ...)`, which indexes the actor's `+0x1d80`
anim-descriptor bank. That bank is bound by a **per-borg-family virtual constructor**:

```c
// chunk_0007.c:410  zz_0056ce0_
void zz_0056ce0_(int actor) {
  (**(code **)((&PTR_PTR_802d3224)[*(char*)(actor+1000)]     // borgId
              + (uint)*(byte*)(actor+0x3e9) * 4))();          // variant
}
```

`PTR_PTR_802d3224` is a per-borg-id table of family-ctor function pointers. Read the G RED ctor
(borgId `0x615`, already partially scaffolded as `configureGRedFamily` in
`packages/combat/src/families/gred.ts`) and the Normal Ninja ctor (borgId `0x000`, the other
title-intro actor's family, and the roster's most common baseline family) from
`ghidra-export/` — find each via `PTR_PTR_802d3224[borgId]` resolved through `dol.py`'s
pointer-table reader, then locate the target function in `_index.tsv`. Confirm what each ctor
writes to `+0x1d80`/`+0x1d84` (bank index → mot group mapping) — this tells you whether
`groupSel=5` really means "g0 battle bank" (the port's current TUNED assumption in
`ANIM_FILES_BY_ID`) or something else. Write up in a new dated decode doc, then update
`title-intro-remaining-decode-2026-07-05.md`'s status table.

## Priority 2 — Intro: `DAT_80390ad0` widget-table row stride

`title-intro-remaining-decode-2026-07-05.md` §5. `FUN_801dd7d4`
(`title_menu_spawn_base_widgets`) walks a ~98-row table of desk-diorama menu-option placements
(f32 X/Y/Z position + flags word + model id, confirmed by sample bytes in the doc). The exact
row stride (likely 0x10 or 0x14 bytes) isn't pinned down — read `FUN_801dd7d4`'s walk loop in
the corpus, confirm the stride and field order, then dump the full table via `dol.py` into
`research/decomp/data/title-widget-table.json`. This is what a future widget-render layer (the
port's `spawnTitleWidget`/`setTitleWidgetMode` sink methods currently just log) would consume.

## Priority 3 — Challenge: identify the CPU AI decision function(s)

`behavior-notes.md` point 8 (2026-07-03 session) and `research/decomp/index/cpu-ai-evidence.md`
have the leads but the AI brain is still **un-isolated** — the 6-entry
`set_slot_action_handler` table was traced and ruled OUT (it's replay input-stream buffers, not
the CPU brain). This matters for Challenge specifically because every non-P1 slot in every
Challenge battle is CPU-driven, and `PORT-1TO1-STATUS.md` flags "CPU AI approach/kite constants
still tuned for the old 22-speed world" as an open follow-up (not correctness-blocking, but a
feel gap). Static-only task: grep the corpus for writers to the CPU-slot pad-mirror (the actual
address needs re-deriving — start from `cpu-ai-evidence.md`'s leads and cross-reference against
known per-slot input-read call sites near the battle loop, `chunk_0006.c`/`chunk_0009.c` are
good starting points per prior sessions). **Identification only** — confirming live behavior
needs a Dolphin write-watch (out of scope here); the deliverable is a candidate function list
with call graph, ready for a future trace session to confirm.

## Priority 4 — Apply the per-family state-machine template to 1-2 more Challenge-relevant borgs

Per `packages/combat/src/rom/PORTING.md`'s recipe (read it first — it has the exact steps and a
worked G RED example): pick 1-2 families that show up early/often in Challenge rosters (Normal
Ninja `pl0000` is a good first pick since Priority 1 already has you reading its ctor) and port
their root-action dispatcher + phase chains the same way G RED's X-special was ported. Add a
`rom.selfcheck.ts` assert per family landed. This directly grows the "Tier D" bucket in
`PORT-1TO1-STATUS.md` §7 — update that table when a family lands.

## Priority 5 (lower value, static, opportunistic) — reconcile comboHits vs. ladder-length

`PORT-1TO1-STATUS.md`'s 2026-07-04 per-combo-step session notes 58/208 borgs where the
asset-derived `comboHits` disagrees with the DOL-resolved ladder length. `comboLadderStepCountForBorgId(id)` (`packages/combat/src/actionStreamData.ts`) is already exported for this. Not
urgent, but if you have spare time after 1-4: sample a few disagreeing borgs, identify which
side is wrong and why (asset-export miscount vs. an unresolved/ambiguous DOL ladder), and log
the finding — don't blanket-fix without root-causing at least 3-4 examples.

---

## Part 2 — Dolphin-in-the-loop items (needs a human/computer-use driver)

These three are the genuinely trace-gated residuals for Intro + Challenge — static digs already
hit a wall on each (documented below), and the only way further is a live capture. All three
reuse the proven launch procedure from `attack-mechanics-trace-plan.md` (bottom section): boot
via `node scripts/launch-dolphin-gdb.mjs --save-state "<path>"` (GDB stub on port 5555), the
`gotcha_force_100_usa.gci` save at repo root (gitignored, user-owned) has every borg/mode
unlocked, wait ~20s for boot, then run the capture script while a driver performs the scripted
input. **Headless capture with no input records no change points — a battle/scene must be
actively driven.**

### Priority 6 — Intro: actor→JOBJ→rootTranslation walk for the desk spawn coords

Where it's stuck: `scripts/read-title-spawn-coords.mjs` (built 2026-07-05) confirmed
`groupSel=5` and the live borg-id table (`0615 000A ffff...` = slot0 G RED / slot1 Sasuke) at
the anim-trigger breakpoint, but found the front-end state table `state+0x1604+slot*0xc`
reads all-zero post-intro (the menu transition re-zeroes it — it's only live DURING the desk
intro window) and the actor struct itself (`0x00..0x100`) has no position floats.
`scripts/scan-mem1-backpointers.mjs` then proved the desk actor has **zero pointers** in its own
struct range toward the model/JOBJ heap — the rendered joint tree isn't actor-referenced, it
hangs off the HSD scene graph (the `tl00` tree), reachable only from a **global render root**,
not from the actor.
- **Task:** find the global scene-graph root pointer (the `tl00` SOBJ/JOBJ tree entry point —
  `research/decomp/tl00-scene-camera-2026-07-04.md` already found the authored camera/lights the
  same way, via the `HSD_SOBJ` camera array; the desk JOBJ root should be reachable the same
  path) and walk root→child JOBJs to the two desk-actor sub-trees, reading each root joint's
  translation (HSD JOBJ world matrix, translation column) live during the ~54s post-boot intro
  window (per the 2026-07-05 second-boot capture).
- **Scenario:** fresh boot (no save-state — the intro only plays from a real cold boot), GDB
  attach, breakpoint at the same anim-trigger site `read-title-spawn-coords.mjs` uses, then walk
  outward from the render root instead of the actor.
- **Pass/fail:** two f32 xyz triples (G RED, Sasuke) that explain the visually-correct desk
  layout — replaces the TUNED `stageBaseForSlot` constant in the port.
- **If it dead-ends again:** this is presentation-only (not a correctness gap — every gameplay
  aspect of the intro is already runtime-confirmed per `48800910`'s commit message). Don't sink
  more than one session into it before parking it again.

### Priority 7 — T8: status-effect id catalog (existing preset, just needs a driver)

Already scoped with a ready preset — `attack-mechanics-trace-plan.md` T8, harness command:
```bash
node scripts/trace-attack-mechanics.mjs --preset T8 --frames 1800 \
  --scenario "status-move hits: freeze/shock/poison/shrink"
```
This is the one remaining genuinely-blocked item on the whole combat ledger (`PORT-1TO1-STATUS.md`'s
finish-line handoff: "T8 — status per-id CATALOG... VERIFIED not in the static corpus"). Get hit
by known status-inflicting families (wiki: Ice/Thunder/Acid attackers) in Versus and log the
victim fields listed in the trace plan (`+0x71a` status id, `+0x71c` timer, `+0x70c/+0x70e`
shrink/grow, etc.) per the plan's pass/fail (id/timer/effect triple reproduces 2/2). Port the
result into `status.ts`'s status-id table once confirmed.

### Priority 8 — Challenge: confirm the CPU-AI candidate function(s) from Priority 3

Two-phase: do Priority 3 (static identification) first if it hasn't run yet. Once you have a
candidate writer function for the CPU-slot pad-mirror, set a GDB breakpoint on it (same
`launch-dolphin-gdb.mjs` + `dolphin-gdb-trace.mjs` pattern as the T-series presets, no existing
named preset for this one — extend `trace-attack-mechanics.mjs` with a new preset or use
`dolphin-gdb-trace.mjs` directly) during a live Challenge battle with CPU opponents, and confirm
it actually drives kite/approach decisions (correlate breakpoint hits/argument values against
the CPU borg's observed movement). This directly resolves the "CPU AI approach/kite constants
still tuned for the old 22-speed world" note in `PORT-1TO1-STATUS.md`.

---

## Tooling notes (so you don't re-discover these)

- Search corpus by function/data name or address in `_index.tsv` (11,972 entries) or
  `organized/_map.tsv` (bucketed). Don't read whole chunk files if you can open the one small
  per-function file in `organized/`.
- Raw ROM bytes (floats, tables, opcodes) via `research/decomp/dol.py`'s `addr_to_off`/
  `read_u32`/`read_f32` against `user-data/GG4E/disc/sys/boot.dol`. For unfamiliar bytecode,
  `scratchpad/ppc_disasm.py` decoded the last 8 stream-VM opcodes this way (see
  `action-vm-and-gcrash-decode-2026-07-05.md` §A for the exact calling-convention pattern it
  found — every handler follows the same `lwz r6,0(r5)` / part-bit test / advance-stream shape,
  useful if you hit more undecoded opcodes).
- `scripts/extract-family-cue-tables.mjs` is the existing per-family cue-table extractor
  (17/30 families resolved automatically) — its `lis+addi` pattern-matching approach is a good
  template if Priority 4 needs a similar per-family constant extraction.
- Verify any TS change with `pnpm -r run build` (root) and, if touching `packages/combat/src/rom/*`,
  `pnpm selfcheck:rom`.

## Working style

- Part 1 (static): if a finding turns out to be genuinely trace-gated (like the intro's actor
  spawn-position table, `+0x1604`, already known to be runtime-only), document it as such and
  move on to Part 2 or another Part-1 priority — don't try to fake a value.
- Part 2 (Dolphin): confirm a human/computer-use driver is actually available before starting —
  a headless capture with no input records nothing. Save-state at scenario start, log at 60 Hz,
  store JSONL under `user-data/dolphin-trace/attack-mechanics/` per the logging template in
  `attack-mechanics-trace-plan.md`, then add a matching replay case to
  `packages/combat/src/selfcheck.ts` or `scripts/selfcheck-1p-challenge.mjs` that diffs the
  logged metric against the TS sim.
- Every finding, either part: behavior-notes.md / a new dated decode doc (address + evidence) →
  `PORT-1TO1-STATUS.md` row update → (only if solid) TS port + selfcheck.
- Ask before wiring an unconfirmed mapping into gameplay-affecting code. Don't ask before
  grepping, reading raw ROM bytes, or reading local research material — that's all already
  yours.

## First message to send after reading this

State whether you're running Part 1 (static) or Part 2 (Dolphin-in-the-loop, confirm a driver is
available) this session, which Priority you're starting on (default within Part 1: **Priority 1**,
since it also seeds Priority 4 by requiring the Normal Ninja ctor read; default within Part 2:
**Priority 7**, since it has a ready-made preset and no dependency on Part 1), and proceed.
