# State-machine fleet 1:1 rewrite plan

## Objective

Replace generic or incomplete combat fallbacks with evidence-backed GG4E state machines for every borg family, while distinguishing live action slots from command-disabled or dead ROM data.

## Global constraints

- GG4E `boot.dol`, verified Ghidra decompilation, and extracted ROM tables are authoritative. Wiki prose and inferred behavior are not sufficient evidence.
- A slot is complete only when its root dispatch, variant dispatch, phase transitions, constants, stream behavior, bridge fields, and focused tests are represented.
- A `null` handler is acceptable only when the command table proves the slot is disabled, the ROM table entry is null, or execution is deliberately delegated to an already-port-faithful shared engine. The reason and evidence address must be recorded.
- Preserve generic behavior for unported families until their complete machine is enabled.
- Preserve unrelated user changes in `docs-site/` and all pre-existing worktree edits.
- Each implementation batch must pass `pnpm --filter @gf/combat build`, the focused ROM self-checks, and `pnpm selfcheck:rom` before it is accepted.
- No guessed constants or placeholder transitions may be labeled 1:1.

## Tasks

### Task 1: Build the fleet coverage gate

Create a deterministic audit that joins the 119 constructor roster, command/action tables, bridge registrations, and family action tables. It must report each family/action slot as ported, intentionally inactive/delegated with evidence, or missing/partial. Add a machine-readable artifact and a concise human summary. The audit must fail only on structural inconsistencies initially; a strict flag must fail when incomplete live slots remain.

### Task 2: Complete shared robot-family machines

Use verified constructor/action/phase tables to finish the shared robot action engines and wire all family variants that point to them. Include focused transition and constant assertions for every distinct table variant.

### Task 3: Complete shared aimed-shot and morph families

Port the remaining live action slots for both users of `shared-aimed-shot-x.ts`, composing existing morph behavior only where the ROM dispatch proves the seam.

### Task 4: Complete shared girl and machine families

Finish live action slots still marked incomplete in cyber-girl, cyber-machine, robot-derived, and related shared family registrations. Reuse existing verified shared engines by ROM address identity, not by behavioral resemblance.

### Task 5: Complete ninja and melee families

Transcribe the documented NORMAL NINJA actions 0/1, then finish remaining sword/melee shared slots and explicitly classify disabled slots.

### Task 6: Complete remaining bespoke families

Process every live slot remaining in the fleet audit in constructor-address batches. Each batch must bank exact evidence before TypeScript changes and add per-family transition tests.

### Task 7: Enforce fleet completeness

Run the strict fleet audit, resolve every live missing/partial slot, update `PORTING.md` from generated counts, run the complete verification suite, and perform a whole-branch review.
