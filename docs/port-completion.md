# 1:1 port completion checklist

Snapshot: 2026-11-11. This is the current entry point for remaining work, not a
completion declaration. The active port route is **matching decompilation**.
Do not restart the retired `finish-port --drive` wasm-unit driver.

## What is measured now

- `src-match/matched.json` records **682 unique functions / 4,003 instructions**
  (634 game, 48 SDK): **0.5707%** of the recorded 701,464-instruction census.
  Freshly re-verified on the Windows rig: **682/682 functions + 8/8 controls**.
- Historical 405-function and 583-function snapshots in the README and matching
  research notes describe earlier stages, not this registry inventory.
- Fresh family audit: **232 ported / 93 partial / 0 missing** across 325 action
  slots, 119 constructor families, 208 Borgs, and zero structural errors. These
  are implementation classifications, not a full-game parity measurement.
- The TypeScript recreation's subsystem tracker is
  [PORT-1TO1-STATUS](../research/decomp/PORT-1TO1-STATUS.md). Its historical DONE
  labels must not be summed with matching-decompilation counts.
- No full-game 1:1 result is established by the changes below.

## Sequential matching lanes

1. **Baseline verification: complete.** The original 608 entries and eight controls
   passed using the user-supplied GG4E image and existing pinned compiler.
2. **Absolute-global recovery: complete for this bounded pass.** Correct standard
   ELF IDs and halfword offsets, prove symbol+addend and actual linked bits, and
   re-enable the seeder. Added **66 functions / 642 instructions** without model
   calls. All 674 entries and eight controls pass. A repeat over the remaining
   4,537 functions of at most 128 instructions found zero extra matches:
   4,221 seeder refusals and 316 compiler/C mismatches remain.
3. **Non-rotating masks: complete for this bounded pass.** Model all 1,024
   PowerPC mask ranges, including wrapped ranges. Added **8 functions / 102
   instructions**. All 682 entries and eight controls pass. Remaining bounded
   queue: 4,198 seeder refusals and 331 compiler/C mismatches.
4. **Signed high-bit mask ordering: corrected for direct mask operands.** Restore
   signed register interpretation on the target without casting floating-point,
   unsigned, or equality comparisons. A bounded dry run recovered **zero** new
   functions; coverage is unchanged. The pinned compiler emitted identical code
   before/after the cast for the tested sign predicate, so this is a source
   interpretation correction, not a demonstrated codegen recovery.
5. **Next: one remaining compiler/seeder limitation**, with affected-function and
   full-registry proof. This is not a whole-game finish.

The coverage denominator stays 701,464 instructions. Neither a completed lane nor
682/682 registry checks means unregistered code or gameplay is 100% complete.

## This increment

1. **Matching oracle:** verify branch relocation type and addend, and never let
   another relocation borrow a checked offset. Interior symbol targets remain
   unverified. [Negative controls and limits](matching-loop.md).
2. **Acceleration Ninja:** preserve signed action-0 yaw and action-3 turn decay,
   including float32 rounding before integer truncation. Evidence:
   `research/decomp/ghidra-export/chunk_0042.c:675-680,961-967`.
   The family selfcheck has 61 passing assertions, including 14 new cases;
   restoring the old expressions fails eight cases. Physics remains incomplete.
3. **Camera organization:** finish the existing `@gf/camera-math` separation.
   Combat imports the pure package, rendering keeps a compatibility re-export,
   and both consume one implementation rather than duplicated camera code.
   The render manifest now agrees with the committed lockfile.
4. **Clean-build repairs:** provide the stage disposal export already used by the
   game, and replace the Challenge recording-test sink's nonexistent pool JSON
   with committed generated pool data. Preserve weighted duplicate entries.
   Camera, Challenge VM, disposal, and ROM selfchecks now run in the contributor gate.

## Remaining work, in dependency order

| Work | Evidence needed | Acceptance gate |
| --- | --- | --- |
| Preserve registered matching C | All 682 entries verified on user-supplied GG4E and pinned fork | `python src-match/verify.py --control`; inspect every changed verdict, never delete failures to preserve a total |
| Recover compiler-blocked functions | Reproduce compiler diagnostics on current fork; historical queues are in [matching-loop](matching-loop.md) | Compiler regression tests, then byte-exact retail comparisons with relocation checks |
| Close Ninja physics gap | Compare `FUN_80067310` and host call timing with committed source and controlled traces | Dedicated helper/host tests; do not blindly use `integratePhysics`, which applies extra upper speed clamps |
| Close remaining action state machines | Re-run `pnpm audit:family-state-machines`, select one partial action, trace its phase/dispatch/constants | Boundary tests plus ROM selfcheck; leave unknown host behavior explicitly partial |
| Fusion activation | Existing pair data is not activation behavior; follow the trace-gated fusion design | Controlled activation/partner/control/exit traces before wiring gameplay |
| Product-level 1:1 acceptance | Original-game captures for each covered behavior and a deterministic browser run | Inputs, state effects, non-ongoing battle result, Results/next action, no unexpected fallback or missing assets |

Compiler or trace blockers are dependencies, not permission to substitute plausible
behavior. Keep `TUNED`, `PARTIAL`, and `MATCH_UNVERIFIED` distinctions intact.

## Repeatable checks

```bash
pnpm install --frozen-lockfile
python3 -m unittest discover -s research/tools/matching-decomp -p 'test_*.py'
python3 research/tools/matching-decomp/loop.py selftest
pnpm verify:contributor
pnpm test:oracle
pnpm verify:docs
pnpm selfcheck:rom
```

Synthetic oracle tests do not need a disc or compiler. The loop selftest explicitly
skips its end-to-end group without those inputs. Full browser/atlas gates also need
the complete checkout, including their tracked serving assets; a source-only sparse
checkout cannot establish asset delivery or visual parity.

## Validation for this increment

- Passed: frozen install, repo policy, TypeScript build, matching negative controls
  (31 tests), matching-loop selftest (71 checks), ROM suite, camera suite,
  Challenge VM (60 checks), disposal (3 tests), lifecycle, menu/session/title
  selfchecks, importer (9 tests), production game build, and atlas build with
  `GF_ATLAS_SKIP_MODELS=1`.
- Historical oracle fixture suite: 81 passed, 1 explicitly skipped because its
  private MEM1 captures are absent. This does not verify new matched C.
- The source-only local contributor gate stopped at absent HUD assets; subsequent
  checks ran separately. The full-checkout GitHub contributor workflow passed on
  commit `96b3707c712fbedefef038929d6636e5f54d972d` after the absolute-global lane.
  Browser smoke and visual parity remain unmeasured.
- Windows retail verification: **690 ok, 0 failed** (682 functions + eight controls).
  Independent extractor/comparator selftest passed; pinned compiler fork integrity
  passed all eight checks. No compiler modification was needed.
- Compiler SHA-256:
  `6bb0af011a5897e790e280a2caa8e439a3055cb3df55153809f1d3f2df2a5486`.
  Existing user-supplied disc read in place. No ROM, proprietary SDK, model, or
  game asset was downloaded or added by this work.

Mask expression tests prove bit selection, not every surrounding C expression.
Direct signed high-bit mask ordering now uses a target `int` cast; its meaning
relies on the target's two's-complement conversion behavior. Compound expressions
still need compiler/retail proof. The correction adds no claimed matching coverage.
