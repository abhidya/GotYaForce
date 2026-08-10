# NEXT STEPS — folding the POC findings into the port workflow (2026-08-09)

POC verdict: PASS (see POC-RESULTS-2026-08-09.md). This is the sequenced plan to turn
the POC into the production port pipeline. Items marked [OWNER] need an explicit yes.

## Phase A — pipeline rewire (the workflow changes the POC proved)

1. **Stage-3 model = thinking model.** Route compile-fix calls to Qwen3.6-27B-MTP
   (thinking enabled). Keep the muted 35B as fallback/second sampler. Evidence:
   27B oracle-green on first linked build; 35B 1-of-3.
   [OWNER] context size for the 27B: 262k spills KV to CPU (~50 min/call). The port
   prompts are ≤8k tokens; load at 32-65k to stay on-GPU. Conflicts with "max
   context" preference — needs the owner's call on speed vs headroom.
2. **Port the model_loop.py hardening into port_driver.py:**
   - streaming with in-band SSE-error raising (never silently drop `data:{"error":…}`)
   - cancel-on-abandon: on client kill/timeout, force-cancel the server generation
     (zombie requests hog the single slot — observed 79 min)
   - preflight context check: assert served context ≥ prompt+output budget before
     dispatch (JIT reload silently resets to 4096; the status field lies both ways)
   - post-link import whitelist: undefined symbols other than the SDK seam
     (gnt4_*) fail the unit loudly (caught a linked-but-dead 35B unit)
3. **Output discipline = new modules only** (wasm units + generated scaffold), never
   surgical edits to living files. The old protocol's last 53 rejections were all
   edit-protocol violations; the POC needed zero.
4. **Gates per unit:** emcc link → import whitelist → oracle corpus diff. Commit per
   green unit ("commit-per-match", Snowboard Kids pattern). Never trust link success.
5. **Work queue = game-gap driven** (per HANDOFF §2 gaps), not chunk order.

## Phase B — scale the arena + unit pattern

1. **SDK classification pass** over _index.tsv: gnt4_/GX/OS/HSD/TRK/DVD → shim
   registry (TS implementations), never ported. (POC proved the seam: 4.02
   calls/case overhead, byte-exact.)
2. **Generalize gen_arena.py**: today it hardcodes the damage-table regions; teach it
   region manifests (addr ranges + element widths) so each new unit only declares
   its data dependencies. Byte-swap stays at generation time.
3. **Generalize the scaffold header**: GC_xxx macros + prototypes emitted from
   _index.tsv instead of hand-listing. CONCAT44/cntlzw/ABS/stdbool live in one
   shared gnt4_shim.h (POC-validated definitions).
4. **Oracle registry**: map wasm units to reference implementations
   (sourceDamage/sourceKnockback/sourceCollision, challengeFlowVm, selftests; later
   Dolphin traces for units with no TS port). A unit without an oracle gets a
   corpus-replay oracle built FIRST or stays out of the queue.
5. **First production targets** (oracle-rich, game-gap aligned): knockback
   (sourceKnockback.ts), collision (sourceCollision.ts), then the hit-resolution
   loop in chunk_0003 (bridges toward "a battle resolves" gating).
6. **Browser integration**: unit loader keyed on the 2 GB arena module
   (poc-run.js pattern), behind a build flag until parity is proven per unit.

## Phase C — repairs the POC surfaced

1. [OWNER pending yes] **Oracle table fix, staged Option A**: regenerate float JSONs
   bit-true (f32 exact), file-by-file, POC harness as the regression gate
   (expected: 20,000/20,000 after). Discussed + recommended 2026-08-09.
2. **Stock browser smoke is red**: scripts/smoke-browser-game.mjs cannot boot the
   GH-Pages-base dist. Fix = map the /GotYaForce/game/ prefix (POC smoke does) or
   build a root-base dist for smoke. Then [OWNER] the behavioral smoke gate
   ("a battle resolves") from the handoff open list.
3. **Oracle gate deviations** (immunity//40 guard missing defender-is-borg check;
   hp>maxHp clamp) — comment-only clarifications in sourceDamage.ts, or guarded
   fixes. [OWNER] behavior vs comments.

## Phase D — infra wrap-up

1. Re-enable checklist (all currently held for the experiment):
   `rig gate resume` (or dashboard button) → Enable+Start scheduled tasks
   "Palworld - Python watchdog (port supervisor)" and
   "\CustomCard\CustomCard ComfyUI Queue Worker" → control.json back to `run`.
   NOTE: watchdog now honors the manual gate (new code goes live on enable).
2. Parked: LM Studio retirement / embeddings → unsloth (D:\rig\tasks\
   remove-lmstudio-migrate-embeddings.md). Rig toast crash chip (spawned).
3. Reconcile rig HANDOFF "ud-iq3_s" note vs actual served variants; add the
   per-model context pin to unsloth-control.ps1 config if the owner adopts A.1.
4. [OWNER] the standing open decisions from HANDOFF §6 that the POC verdict now
   unblocks: adopt §4 trunk (POC says yes), R17 valve obsolete, OMR priority flip
   criteria restatement.
