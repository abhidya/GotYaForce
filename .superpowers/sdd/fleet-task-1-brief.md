# Fleet Task 1: Build the fleet coverage gate

Create a deterministic audit that joins the 119 constructor roster, command/action tables, bridge registrations, and family action tables.

## Requirements

- Report every constructor family and every action slot reachable from its ROM command/root tables.
- Classify each slot as exactly one of `ported`, `inactive`, `delegated`, `partial`, or `missing`.
- Record evidence addresses or artifact references for `ported`, `inactive`, and `delegated`. Do not infer completeness solely from a non-null TypeScript handler.
- A `ported` classification must independently represent and validate root dispatch, variant dispatch/member coverage, phase transitions, constants, stream behavior, bridge wiring, and focused tests.
- A `delegated` classification must name a resolvable audited target slot that is itself complete, include evidence for the ROM delegation, and cannot form a cycle.
- A constructor-level classification must not promote all members unless its evidence explicitly covers every member and every live action variant used by those members.
- Emit deterministic JSON under `research/decomp/data/` and a concise Markdown summary under `research/decomp/`.
- Add root command `audit:family-state-machines`.
- Default succeeds when structurally valid; `--strict` fails while any live `partial` or `missing` slot remains.
- Detect unknown borg IDs, duplicate classifications, invalid indexes, and references to absent implementations.
- Add fixture-driven tests for conservative classification, strict failure, deterministic output, false `ported` rejection, cross-member/variant promotion rejection, nonexistent/incomplete/cyclic delegation rejection, and evidence-backed inactivity.
- Preserve unrelated files and do not edit gameplay behavior.

## Global constraints

- GG4E `boot.dol`, verified Ghidra decompilation, and extracted ROM tables are authoritative.
- A slot is complete only when root dispatch, variant dispatch, phase transitions, constants, stream behavior, bridge fields, and focused tests are represented.
- A null handler is acceptable only with ROM proof or faithful shared-engine delegation.
- Preserve generic behavior for unported families and unrelated user changes.
- No guessed constants or placeholder transitions may be labeled 1:1.

## Workspace/report

- Work in `D:/GotYaForce` on `codex/state-machine-fleet`.
- Touch only Task 1 audit files. Do not stage or commit during the fix loop.
- Prefix shell commands with `rtk`; use `apply_patch` for edits.
- Write/append the report at `D:/GotYaForce/.superpowers/sdd/fleet-task-1-report.md`.
