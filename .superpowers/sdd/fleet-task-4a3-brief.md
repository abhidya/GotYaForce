# Fleet Task 4A3: Wire exact Girl family helper boundaries and classify

Complete Task 4A by wiring the already-implemented exact host primitives at every family-specific ROM call site.

## Requirements

- For Battle Girl, Wire Girl, Barrier Girl, Delta II, Killer/Shadow Girl, Cyber Girl, Spinner Girl, and Delta, trace every call to `zz_006d0dc_`, `zz_006d144_`, `FUN_800669d0`, `zz_006e514_`, `zz_00679d0_`, `zz_00677b0_`, and related air-steering/face helpers.
- Wire exact invocation order, parameters/aim types, signed BAM16 return/settle semantics, target-loss behavior, control-word gates, and phase transitions in `girl-cluster.ts`, `cyber-girl.ts`, `shared-series3-x.ts`, and shared melee paths.
- At every ground-snap boundary, consume the exact supported/unsupported return and saved-position revert result; do not merely call a generic clamp.
- Preserve the Task-4A/4A2 exact afterimage, pitch, scale, housekeeping, ammo, event-byte, and phase repairs.
- Add focused phase-boundary tests for every distinct helper invocation plus exhaustive real-handler/bridge live matrix and exclusions.
- Re-audit all eight Girl constructors and add schema-v2 classifications for every complete live slot; leave only specifically proven blockers partial.
- Regenerate coverage and run combat build, game typecheck, full ROM selfcheck, focused presentation test, default audit, expected strict failure, and task-owned diff check.

## Constraints

- ROM/Ghidra/data pages are authoritative; no generic approximation may support `ported`.
- Preserve unrelated concurrent changes and current Task-4A/4A2 edits. Do not stage or commit.
- Prefix commands with `rtk`; use `apply_patch` for edits.
- Report to `D:/GotYaForce/.superpowers/sdd/fleet-task-4a3-report.md`.
