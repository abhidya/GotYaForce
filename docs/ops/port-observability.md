# Port observability — where the state is, and what cannot be seen

**Provenance.** Rescued 2026-08-29 from the untracked 2026-08-21 `dsh-port-observer-spec`
(a 34 KB implementation-ready specification for a read-only observer) and the
`game-evidence-spec-report`. The plugin scaffolding, marketplace commands, and Codex
packaging details from that spec were **dropped** — they describe a personal tool outside
this repository. What is kept is the part that is about GotYaForce: where port state
actually lives, how to normalize it without lying, and what is not observable at all.

**Status.** The state-file inventory is dated 2026-08-21 and was not re-enumerated on
2026-08-29; paths are stable but counts are not. The observability gap and the
normalization rules are unchanged in principle.

---

## 1. The four questions an observer has to answer

- What is the model doing: prompts, outputs, tool calls, timings, failures?
- What state is the autonomous port in: supervisor, unit, compile/repair/link/oracle/assembly,
  commit/push, blocked conditions?
- What changed: source files, generated C/Wasm artifacts, imports, game-facing code?
- What evidence says the game is **more playable** — verified oracle/smoke/build evidence,
  not compile-only counts?

It succeeds when it correlates those on one timeline, preserves provenance and uncertainty,
**exposes stale or contradictory state**, and performs no write or control action.

---

## 2. Where port state lives

| Purpose | Path | Notes |
| --- | --- | --- |
| Supervisor snapshot | `D:\rig\state\supervisor-state.json` | Mode, reason, driver PID, release verification, configured model/context, work counts. **A shutdown checkpoint, not live authority** — see [`rig-serving-and-gpu-handoff.md`](rig-serving-and-gpu-handoff.md) §5. |
| Manual gate | `D:\rig\state\manual-gate.json` | Read only. Never pause/resume through an observer. |
| Current run | `research/decomp/generated/finish-game-port/run-state.json` | Run ID/state, progress, counters, current unit, queue sample. |
| Current unit | `…/unit-state.json` | Legacy/current chunk-unit state; **may be stale** — never override newer run/journal timestamps with it. |
| LLM liveness | `…/llm-liveness.json` | Request activity, token estimates, speeds, status, model, run ID. No content. |
| Unit ledger | `…/wasm-units-state.json` | 1,396 unit records; status, tier, attempts, last stage, errors, model requests, oracle summary, commit/push, registry metadata, revocation. |
| **Canonical port journal** | `…/events.jsonl` | **The primary state-transition timeline and the transition authority.** |
| Progress journal mirror | `.tmp/port-progress-worktree/workflow-progress/events.jsonl` | The machine-journal branch view. Correlate; do not assume it is identical to the live journal. |
| Assembly state | `research/decomp/data/assembly-gate.json` | Largest N, runs, conflicts, last run, stage, pass/fail, units, timestamps. |
| Assembly artifacts | `…/finish-game-port/wasm-units/_assembly` | `assembly.wasm`, smoke loader, merged C/header inputs. Report hashes and sizes only. |
| Unit artifacts | `…/finish-game-port/wasm-units/<unit>` | `unit.c`, `gnt4_shim.h`, `unit.wasm`, `oracle.log`. No per-unit manifest is guaranteed. |
| Live LLM interaction log | `research/tools/OGhidra/logs/llm_interactions_lmstudio_nemotron3.json` | **Legacy name, current content** — see the rig page §2. |
| Historical activity | `…/finish-game-port/activity.jsonl` | 122.7 MB / 623,468 rows, mostly 2026-08-01 deltas. **Not a current feed; never full-scan it on refresh.** |

Observed journal event kinds: `driver_started/stopped`, `wasm_unit_started/build/green/red`,
`assembly_gate`, `assembly_gate_failed`, `verdict_revoked`, `unit_retryable/rejected/skipped`,
registry events, selection, provider pause/unavailable, and progress snapshots. A normalized
timeline must preserve the raw `kind`, run ID, unit, timestamp, and path/line or sequence
provenance.

Game-side evidence: `apps/game` (the Vite/TypeScript/Three.js app),
`scripts/smoke-browser-game.mjs` (a real playable-flow smoke that prints a terminal result
and cleans its own temp directory — **no durable run report is guaranteed**),
`apps/game/reference/captures` (stable reference PNGs; baselines, **not** proof of the
current build), and `apps/game/server.out.log` / `vite.out.log` / `vite.err.log` (freshness
and error evidence, not proof of a passing build).

---

## 3. The observability gap

**The port driver does not run through any harness that records its conversation.** It calls
the Unsloth OpenAI-compatible endpoint directly; its three `stream_callback` sites are no-op
lambdas, so live deltas are discarded. The custom interaction log contains prompt/response
records only when configured and only when a request reaches the relevant logging point —
at the time of the audit the current file held 682 `throttle_state` records and **no
prompt/response records at all**.

Consequences:

- An observer can show prompt token count, elapsed time, throughput, stage, compile error,
  and any bounded logged request/response that happens to exist.
- It must expose a machine-readable `contentAvailability = "unavailable"` with a reason when
  no durable prompt/response record exists. **Silence must be reported as silence**, not
  rendered as an empty conversation.
- Adding a bounded, redacted port event sink is a **separate** design change in OGhidra with
  its own spec, tests and approval. It is not an observer feature, and it must not become a
  product heartbeat.

See also the related driver defect in
[`../audits/port-pipeline-integrity.md`](../audits/port-pipeline-integrity.md) §7.6 — the
discarded stream also destroys recoverable header work on a mid-generation disconnect.

---

## 4. State-machine normalization rules

Project observed events into these phases; never rewrite source state.

```
supervisor: manual-paused -> loading -> running -> stopping -> releasing -> manual-paused
unit:       pending -> selected -> porting -> compile -> repair -> link -> oracle -> assembly
unit terminal evidence: verified | staged-unverified | retryable | structural-ineligible | revoked
delivery:   commit-created -> push-confirmed | push-failed | revoked-after-push
game:       source-changed -> built -> browser-smoke-passed -> current-capture-recorded
```

The rules are the load-bearing part:

- **`compile-only` is always `staged-unverified`, never playable progress.**
- **A `wasm_unit_green` followed by `assembly_gate_failed` renders as a failed promotion
  sequence and an alert — even if the ledger still says green.** (This is the ordering
  defect in `port-pipeline-integrity.md` §3; an observer must not launder it.)
- **A push that precedes a later assembly failure stays visible.** It is not collapsed into
  success.
- State/journal disagreement appears in an explicit `inconsistencies` list. **Journal events
  are the transition authority; ledger and state files are snapshots.**
- A missing transition may be synthesized only when marked `inferred: true` with explicit
  source evidence.
- **No build, smoke, oracle, or pixel result may be inferred from file existence alone.**
- Unknown evidence is labelled `unknown` / `unavailable`. It is never displayed as passed.

---

## 5. Stable reads and bounded resource use

Concrete numbers worth keeping, because they were measured against the real files:

- JSON/JSONL: `stat → bounded read → stat`; retry up to three times if size, mtime, or file
  ID changed mid-read.
- Port journal: small enough for one bounded parse today, but enforce a 16 MiB ceiling and a
  tail/index strategy beyond it.
- `activity.jsonl`: disabled by default. An explicit historical query may tail at most
  4 MiB or 10,000 lines. **Never scan 122.7 MB on refresh.**
- In-memory cache only — at most eight source revisions or 32 MiB, 30-second TTL, no disk
  cache, nothing retained after exit.
- Stream files when hashing; never load Wasm or images solely to render a text response.

Every adapter returns `ok` / `partial` / `stale` / `unavailable` / `invalid`, and one failed
source must not discard the rest of the snapshot. The failure cases that must be named
explicitly: a stale or malformed supervisor state contradicting the manual gate, driver PID,
or release state; an incomplete final JSONL record; journal and ledger disagreeing on
verdict, tier, revocation, or commit/push; run IDs or clocks that cannot be correlated;
assembly state missing, stale, or failed **after** a green event; absent current
build/smoke/capture evidence; and port LLM content unavailable because the stream is not
persisted.

---

## 6. Privacy defaults

Default output is metadata only: tool name, call ID suffix, duration, status, byte/token
counts, redacted error class. Message bodies, tool arguments, and tool results are omitted;
**reasoning content is never returned, even when content is explicitly requested.** Redact
bearer/basic authorization, API-key/token/password assignments, PEM blocks, credentials in
URLs, environment values, and high-entropy secrets; replace user-profile absolute prefixes
with `%USERPROFILE%`; mark every truncation with the original size.

Never read credential files, `.env`, process environment secrets, browser profiles, or
legacy LM Studio logs. A visual surface must not load remote fonts, scripts, analytics,
images, or telemetry.

---

## 7. Durable browser-smoke evidence — specified, not built

A companion spec defined an immutable evidence pair at
`<root>\runs\<commit>-<report-sha256>\` containing `report.json` and `route.png`, produced by
the existing smoke route (Title → Challenge → Normal → 1P → Load Box Data → Select Force →
briefing → unpaused battle HUD, plus the four pause-edge assertions).

The scope boundary is the useful part, and it matches
[`../audits/game-app-defect-ledger.md`](../audits/game-app-defect-ledger.md) §5: the
contract **explicitly excludes** battle settlement, Results, full playability, asset
fidelity, and any raw C/Wasm-in-product claim.

Its observer half is fail-closed: a fixed root, stable reads, strict schema, report and PNG
SHA-256 checks, a PNG signature check, realpath/lstat containment with no symlink or
junction escape, a **≤24-hour** timestamp, the exact current HEAD commit, and an
unambiguous newest-evidence rule. Logs and reference captures remain **non-success**
evidence. CI delivers the JSON and PNG as uploaded artifacts — **no image binaries in Git.**

Open questions, unresolved: which CI runner guarantees a writable evidence volume and which
root is approved; who owns retention and cleanup of successful evidence runs, and for how
long; whether 24 hours is the right staleness ceiling or whether evidence must also bind a
CI run ID; and whether the browser gate runs on every PR, nightly, or only on game-path
changes.

---

## 8. Boundaries an observer must not cross

Never: write product heartbeat or telemetry code; pause, resume, or kill the rig, driver,
model, or scheduled task; run `git push`/`fetch`/`pull`/`checkout`/`reset`/`commit`/`add`
or edit refs and the index; expose reasoning, secrets, unbounded prompts or results, binary
Wasm, or browser profiles; or **claim that compile-only status, file existence, or a
reference capture proves playability.**
