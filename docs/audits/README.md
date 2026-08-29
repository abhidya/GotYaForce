# Audit findings — rescued session notes

**Provenance.** Between 2026-08-21 and 2026-08-23 a series of read-only audits were
written into an untracked `.superpowers/` scratch directory. On 2026-08-29 that
directory was cleared and archived to
`D:\GotYaForce-archives\superpowers-session-notes-20260829.zip` (49 entries). Most of
those findings existed nowhere else. The durable content was migrated here on
2026-08-29, grouped by subject; the originals are not tracked and are not the
authority for anything below.

These documents are **findings**, not design. The governing design contract is
[`docs/playable-port-design.md`](../playable-port-design.md); the operating runbook is
[`AGENTS.md`](../../AGENTS.md). Where an audit conclusion has since been folded into
either of those, the audit page says so and defers.

## The pages

| Page | Subject |
| --- | --- |
| [`port-pipeline-integrity.md`](port-pipeline-integrity.md) | The C→Wasm port driver: promotion ordering, the assembly gate, cross-unit ABI, the advisory knowledge registry, oracle evidence integrity. |
| [`game-app-defect-ledger.md`](game-app-defect-ledger.md) | `apps/game` and the ported TypeScript combat libraries: the 2026-08-22 bug hunt and its still-open remainder. |
| [`research-data-provenance.md`](research-data-provenance.md) | Whether the tracked generated data under `research/decomp/data/` is reproducible from its declared inputs. |
| [`public-repo-readiness.md`](public-repo-readiness.md) | What still blocks this checkout from being shaped like a reproducible public repository. |
| [`../ops/rig-serving-and-gpu-handoff.md`](../ops/rig-serving-and-gpu-handoff.md) | Machine-side: the serving slot, the LM Studio residue, and the GPU-lease defect in the external-workload handoff. |
| [`../ops/port-observability.md`](../ops/port-observability.md) | Where port state actually lives on disk, how to normalize it truthfully, and what is not observable at all. |

## Status vocabulary

Every finding carries one of:

- **OPEN** — re-checked against the tree on the date given and still true.
- **FIXED** — re-checked and confirmed resolved; the evidence for the fix is named.
- **UNVERIFIED** — recorded as found; not re-checked on the migration date. Treat the
  claim as dated evidence, not as current state.
- **DROPPED** — noted here only because it was in the archive and was deliberately not
  carried forward. The reason is given.

A finding is never marked FIXED on the strength of the original author saying it was
fixed. It is marked FIXED only when the current tree was inspected.

## What was deliberately not migrated

- **14 `*-review-package.diff` files (≈11.7 MB, two of them ≈5 MB each).** These are
  code-review packages — a snapshot diff handed to a reviewer for one delegated task.
  Every one of them is superseded by the committed code it was reviewing. They carry no
  finding that is not either in the commit or in one of the reports above.
- **`assembly-green-recovery-manifest.json`.** A point-in-time recovery worklist keyed to
  unit-state hashes that have since moved; the durable conclusion it supported is in
  [`port-pipeline-integrity.md`](port-pipeline-integrity.md).
- **Per-task delegation briefs** (`*-brief.md`) whose entire content is "here is the task,
  here are the boundaries". Where a brief carried a real constraint that is not in the
  resulting report, that constraint was folded into the matching page instead.
- **Session-scoped handoff notes** — the "here is where I stopped, resume here" class.
  Their durable residue (traps, measured numbers) was folded in; the resumption
  bookkeeping was not.
