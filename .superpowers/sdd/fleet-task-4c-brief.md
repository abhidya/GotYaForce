# Fleet Task 4C: Machine Red and Machine Blue constructor clusters

## Scope

Audit and complete the evidence-backed state-machine boundaries for the two related machine constructors:

- `0x800c91bc`: `pl0600`, `pl0608`, `pl0616`, `pl061c`; live actions 0, 1, 2
- `0x800ce730`: `pl0601`, `pl0609`, `pl0617`, `pl061d`; live actions 0, 1, 2, 3, 4

These families currently use shared/robot-derived registration. Reuse behavior only where boot.dol address identity or the decompiled call graph proves it. Behavioral resemblance is insufficient.

## Authoritative evidence

- GG4E `boot.dol`
- Ghidra decompilation/export and organized functions under `research/decomp/`
- Relevant OGHidra analysis sessions under `research/tools/OGhidra/analysis_sessions/`
- `commandMoveTables.json`, `actionStreamTables.json`, and generated fleet coverage

## Required work

1. Bank exact root/action/variant/phase tables, constants, stream behavior, and host calls for both constructors.
2. Audit the current shared registration and family modules against that evidence. Correct every live member/action/variant route and remove inferred or synthetic behavior.
3. Implement exact state-side behavior and proven host boundaries. Leave any slot `partial` when essential target, collision, renderer/model-node, paired-actor, event, or projectile semantics remain unmapped.
4. Add exhaustive route tests for all live member/action/variant combinations plus focused transition/constant assertions for each distinct leaf.
5. Update reviewed classifications only for independently supportable complete slots and regenerate coverage.
6. Write `.superpowers/sdd/fleet-task-4c-report.md` with evidence addresses, changes, verification, blockers, and before/after counts.

## Acceptance

- No guessed constants, simplified phase tables, placeholder coordinates, or behavioral aliases labeled ported.
- Combat build, game typecheck if host/bridge changes, focused checks, full ROM self-check, fleet audit, and diff check pass.
- Strict audit may fail only for remaining documented partial/missing fleet slots.
- Do not commit or modify unrelated dirty files or Task 4A review diffs.
