# Port Strategy Research — 2026-08-09

Status: **owner review requested; no changes made.** Sources: two verification agents
(web research with URLs; local inventory with file:line citations), the 2026-08-08
audit/proposal docs, and the full attempt history of the pipeline. Companion docs:
`port-supervisor-design-2026-08-08.md`, `port-pipeline-proposal-2026-08-08-evening.md`.

---

## 1. The finding that reframes everything

**The game is already roughly half recreated and it runs.** `pnpm dev` boots a real
app: title intro → main menu → complete 1-2 player CHALLENGE mode with a live combat
sim (damage, knockback, collision, ammo, targeting, scoring — all ROM-derived), 208
borgs of roster data, 40 stages, ~24 MB of extracted ROM tables, and 34 in-source
self-test suites. Weighted gameplay surface: **~45-55% of the shipped game.**

Almost none of that came from the whole-program pipeline we spent tonight fixing.
`whole-program-manifest.json`: 11,980 functions, **16 integrated — all boot/CRT
stubs** (memset, memcpy, hardware-init no-op, boot camera). The pipeline's
contribution to the playable game is 0.13% of functions and one boot module.

The playable game came from the **family track**: 75 per-family state-machine files
(~2 MB) in `packages/combat/src/families/`, each a NEW file with dense ROM-address
provenance (2,351 `0x80xxxxxx` citations across 143 TS files), self-tests, and a
hand-maintained bridge (`bridge.ts`, 132 address citations). Plus 1:1 VM ports
(challengeFlowVm 43 addrs, globalMenuDispatcher 61) and ROM-data extractors (30
scripts, 15 generated modules).

**The family track is the product engine. The whole-program pipeline has been trying
to re-derive, chunk by chunk, what that track already does better — and last night's
28-attempt milestone failure was the collision between the two:** the pipeline tried
to force a fresh port into `challengeFlowVm.ts`, a file the family-style track had
already finished.

## 2. What we tried (condensed attempt history)

Tonight's pipeline hardening (all shipped, all working): supervisor rebuilt (windowless
Python watchdog, kill-before-unload, self-healing provider pauses — 4 automatic
recoveries overnight incl. a real player join), refinement-ops analysis (model never
transcribes addresses), full-source prompts (12k clamp had hidden 44% of the milestone
unit), grounded prompts (6,580 summaries were arriving as `{}`), directed repair
feedback, no-countdown retry design, batch push. Result: infrastructure failures went
to zero; the milestone unit then failed 8 more times on the *same substantive wall* —
it was re-porting an already-ported subsystem and could neither rewrite the existing
file (forbidden) nor satisfy a reachability gate demanding names the codebase
rightfully doesn't contain.

## 3. What the successful projects teach (web research, cited in agent report)

1. **Pick ONE trunk.** No successful project maintained a hand-written app and a
   ported codebase as peers. PC ports made the decomp the app (sm64-port, Ship of
   Harkinian, Perfect Dark); Metroid Prime's Metaforce made the hand-written
   recreation the trunk with the matching decomp as reference/oracle. Two-program
   integration hell — our exact failure — is the documented cost of not choosing.
2. **Never port the SDK.** Every GC decomp separates game code from Dolphin
   SDK/MSL/middleware and shims the platform behind one narrow boundary (GX display
   lists, audio, input, file I/O). Likely 20-40% of our 11,980 functions should be
   *mapped to shims*, not ported.
3. **Objective gates beat typecheck.** Projects that scaled used byte-exact matching
   (melee/objdiff), pixel-diff (Chromatron), or completable-game testing. LLMs claim
   behavioral correctness they don't have; the gate must measure, not ask.
4. **LLM loops work when externally harnessed** (Snowboard Kids 2: 25%→45% matched in
   3 weeks): external difficulty scorer picks the next unit (never the model), commit
   immediately per verified unit, invest in gate error messages over prompts, expect a
   ~20% long tail needing hand work, model tier matters at the frontier.
5. **Static recompilation is real on GameCube now** (DolRecomp shipped a completable
   Kirby natively, July 2026) — but its browser runtime (GX→WebGPU) doesn't exist,
   output is an opaque blob, and it abandons the TypeScript-recreation goal. Watch it;
   don't chase it. A recomp build could later serve as a behavioral *oracle*.

## 4. Design options

**A. Keep the whole-program chunk pipeline as-is** (port 80 chunks into the app).
Rejected by evidence: 0.13% yield, and its one deep engagement re-derived finished
work and lost 28 attempts to integration hell.

**B. Whole-program pipeline → new compilable module** (owner's 2026-08-09 direction:
new-file-only output, no edits to living code, reachability deferred to an
integration stage). Solves every mechanical failure from the RCA. Still inherits
option A's strategic flaw if aimed at chunks: it would keep producing ROM-faithful
modules for subsystems the family track already covers, growing a parallel corpus
whose integration is deferred rather than solved.

**C. Repoint the pipeline at the family track's actual gaps** (recommended, subsumes
B's mechanics). The recreation stays the trunk (Metaforce model). The pipeline keeps
B's new-module discipline but its WORK ITEMS come from the product's own audit
scripts instead of chunk order:
   - **12 unbridged family files** (exist, unwired — cheapest real fidelity),
   - **71 missing + 234 partial action slots** across 325 (the dominant combat-fidelity
     gap, and exactly the per-family state-machine work the LLM track already proved
     good at),
   - then VERSUS wiring, per-frame Challenge VM hosting, the last 23 animated borgs.
   SDK/MSL functions get classified and mapped to the existing host shims, never
   ported. Chunk analysis remains useful as *evidence supply* (grouping + grounding
   for family work), not as the work queue.

## 5. Recommendations (in order)

1. **Adopt C.** Redefine the ledger's work items: family/action-slot gaps from
   `audit:family-state-machines` + `audit:move-wiring` become the queue; chunk
   analyses become supporting evidence attached to those items.
2. **New-module output discipline everywhere** (from B): the model only creates
   files; bridging/wiring is its own reviewed work item type; export-name mappings
   recorded in the ledger (the R17 valve).
3. **Behavioral gate before more porting**: extend `smoke:browser` to drive
   `window.__gf` through boot → challenge → battle → assert the battle *resolves*.
   Then add per-unit behavioral checks (replay + state diff) as the real oracle.
   Nothing tonight would have caught a wrong-but-compiling port.
4. **SDK classification pass**: mark hardware/SDK/MSL functions in the manifest as
   shim-mapped, shrinking the denominator honestly (expect thousands of functions).
5. **Progress denominator becomes action slots + families, not functions** — the
   function count (16/11,980) says the port barely started; the game says it's half
   done. Track what's true.
6. Keep everything tonight's hardening bought: the supervisor, no-countdown retries,
   full-source prompts, grounding — they apply unchanged to family-gap work items.

## 6. Pros / cons of the recommendation

**Pros:** aims the (now-reliable) pipeline at the gaps that change the game a player
sees; eliminates both integration failure modes permanently (new files only, no name
gates); matches the proven per-family pattern already in the repo; matches every
successful project's trunk decision; progress becomes measurable in gameplay terms.
**Cons / risks:** the 80-chunk "whole program port" framing is retired as the goal —
functions outside family/menu/system gaps get ported only when a gap pulls them in;
work-item redefinition touches driver selection (a real build, ~1-2 sessions);
behavioral gates require harness work before their value shows; the family audits
become load-bearing and need their own accuracy check.

## 7. Open questions for the owner

1. Approve option C (repoint at family/action-slot gaps, new-module discipline)?
2. Approve the behavioral smoke gate as the next build item ahead of more porting?
3. SDK classification pass: approve marking hardware/SDK functions shim-mapped?
4. The five inert menu modes: VERSUS first (reuses the battle path) — approve as a
   work item after the above?
