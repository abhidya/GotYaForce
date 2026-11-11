# 1:1 port completion checklist

Snapshot: 2026-11-11. This is the current entry point for remaining work, not a
completion declaration. The active port route is **matching decompilation**.
Do not restart the retired `finish-port --drive` wasm-unit driver.

## What is measured now

- `src-match/matched.json` records **608 unique functions / 3,259 instructions**
  (562 game, 46 SDK): **0.4646%** of the recorded 701,464-instruction census.
  This is registry inventory, **not a fresh compiler/retail re-verification**.
- Historical 405-function and 583-function snapshots in the README and matching
  research notes describe earlier stages, not this registry inventory.
- Fresh family audit: **232 ported / 93 partial / 0 missing** across 325 action
  slots, 119 constructor families, 208 Borgs, and zero structural errors. These
  are implementation classifications, not a full-game parity measurement.
- The TypeScript recreation's subsystem tracker is
  [PORT-1TO1-STATUS](../research/decomp/PORT-1TO1-STATUS.md). Its historical DONE
  labels must not be summed with matching-decompilation counts.
- No full-game 1:1 result is established by the changes below.

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
| Re-verify registered matching C | User-supplied GG4E disc dump and pinned `mwcc-rs` fork | `python src-match/verify.py --control`; inspect every changed verdict, never delete failures to preserve a total |
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
  (10 tests), matching-loop selftest (63 checks), ROM suite, camera suite,
  Challenge VM (60 checks), disposal (3 tests), lifecycle, menu/session/title
  selfchecks, importer (9 tests), production game build, and atlas build with
  `GF_ATLAS_SKIP_MODELS=1`.
- Historical oracle fixture suite: 81 passed, 1 explicitly skipped because its
  private MEM1 captures are absent. This does not verify new matched C.
- `verify:contributor` is **not locally green**: its HUD stage requires three
  game image assets absent from this source-only checkout. The subsequent checks
  above were run separately. Browser smoke and asset-delivery parity were not run.
- Retail matching corpus verification is blocked by the absent user-supplied GCM
  and pinned compiler. No model, ROM, or proprietary SDK was downloaded.
