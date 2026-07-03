# ATK-016: Dolphin trace harness for attack mechanics

## Purpose
Turn `attack-mechanics-trace-plan.md` (T1-T10) into a runnable logging harness so the
Dolphin sessions produce machine-diffable JSONL instead of ad-hoc notes. This is the ticket
that unblocks every BLOCKED ticket above.

## Evidence
- Existing tooling to extend: `scripts/dolphin-gdb-trace.mjs` (per-frame RAM logging),
  `dolphin-hp-logger.py`, actor chain `*(u32*)0x803C4E84` stride 0x1e00
  (behavior-notes (z)/(aa)).
- Field/offset lists: per-trace "Memory to log" sections in
  `research/decomp/attack-mechanics-trace-plan.md`.

## Dependencies
None (pure tooling; human runs the sessions).

## Files to edit
- new `scripts/trace-attack-mechanics.mjs` (or extend dolphin-gdb-trace.mjs with a
  `--preset T1..T10` flag)
- `research/decomp/attack-mechanics-trace-plan.md` (append the exact command per trace)

## Required behavior
- Preset per trace id: the offset list from the plan compiled into watch entries
  (actor-relative offsets resolved through the 0x803C4E84 chain; command-struct pointer
  chased through +0x4b0 for T1).
- Output JSONL to `user-data/dolphin-trace/attack-mechanics/T<n>-<slug>.jsonl` with a meta
  line (borg ids, preset, timestamp passed in by the runner).
- A `--summarize` mode that prints per-field change points (frame, old, new) so a human can
  read a session without a spreadsheet.

## Fallbacks allowed
- If the gdb-stub approach can't chase the +0x4b0 pointer per frame, log the pointer and
  post-process; note the limitation in the script header.

## Tests to add
- Dry-run mode against a canned JSONL fixture (no Dolphin needed) exercising --summarize.

## Do not change
- packages/* — this is scripts-only.

## Done when
`node scripts/trace-attack-mechanics.mjs --preset T1 --dry-run` produces the documented
format; plan doc lists the run commands; one real T1 session has been captured by the user
(or the script header documents exactly how to).
