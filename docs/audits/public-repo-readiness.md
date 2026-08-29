# Public-repository readiness

**Provenance.** Rescued 2026-08-29 from the untracked 2026-08-21 `public-repo-cleanup-audit`
(baseline: GotYaForce `8b785f73`, nested OGhidra `96aa026`), with the documentation
findings from the same day's `playability-architecture-audit`. Every classification was
re-checked against the tree on 2026-08-29 and is marked accordingly.

**Verdict, still current.** The checkout is not yet shaped like a reproducible public
repository. Public source and maintained documentation coexist with agent work products,
raw analysis-session transcripts, machine-local paths, duplicated Git ownership, and
opaque archives. Ignore rules prevent most local state from being *newly* committed; they
do not remove material that was already tracked.

**Cleanup must begin with an ownership and documentation contract, not a bulk delete.**

---

## 1. What has been fixed

| Finding | Status |
| --- | --- |
| Two tracked `.tmp/pzz-bake-members/**/*mot.bin` binaries (413,344 and 383,872 bytes) contradicting `.tmp/`'s documented scratch role | **FIXED** — `git ls-files .tmp` is empty. |
| Tracked `python-manager-26.3.msix` (47,047,851 bytes) | **FIXED** — no `.msix` tracked. |
| No `CONTRIBUTING.md`; no contributor navigation for clean setup, game build/test, adding a verified port, rebuilding assets, running an oracle, or troubleshooting a clean clone | **FIXED** — root `CONTRIBUTING.md` exists, and `docs-site/contributing/` now carries `index`, `setup`, `verification`, `porting`, `assets`, `troubleshooting`. |
| Licensing decision left implicit | **FIXED as a decision, not as a file** — `CONTRIBUTING.md` states plainly that the repository has no root license file and that permission to redistribute must not be assumed. There is still no `LICENSE`; that remains an owner call, but it is no longer silent. |
| `docs-site/.vitepress/config.ts` listed **Call Graph** twice (top level and under Architecture) | **FIXED** — one entry at `config.ts:43`. |
| CI ran no tests at all (`deploy-pages.yml` built only) | **FIXED** — `ci.yml` runs `pnpm verify:contributor`, `pnpm test:oracle`, `pnpm verify:docs`, and enforces that published decomp chunks match `research/`. |

---

## 2. What is still open

Counts re-measured 2026-08-29.

### 2.1 Agent process artifacts are still in the public index — OPEN

**44 files tracked under `.superpowers/sdd/`** (≈7.76 MB of briefs, reports, and review
diffs). These record how work was *delegated*, not how a contributor reproduces a result.
They were referenced from exactly two places outside that directory, both in
`research/decomp/PORT-1TO1-STATUS.md`.

Correct order: extract the decisions first (that is what
[`docs/audits/`](README.md) now is), replace those two citations with the durable
code/test commits, and only then remove `.superpowers/sdd` from the index in one
reviewable commit that mixes in no product change.

### 2.2 Raw session state is tracked as if it were content — OPEN

- **35 tracked files under `research/analysis_sessions/`** (568,847,440 bytes at audit
  time). The nested OGhidra index carried a further 40 files / 760,203,109 bytes; at least
  one 41,216,732-byte session was indexed by *both* repository layouts.
- Session JSON embeds prompts, whole source excerpts, machine paths, and logs. These are
  the repository's real "log dump" — not files named `*.log`.

Replace with a minimal reproducibility/attestation schema and generator **first**, then
untrack in separate root and OGhidra commits.

### 2.3 Ghidra database backups and opaque archives — OPEN

- **17 tracked files under `research/decomp/GotchaForce.rep.before_force_create/`**,
  including three 57–59 MB database files; another 58.8 MB database under
  `research/decomp/poc/pyghidra-backup/GotchaForce.rep/`. Existing ignore rules name
  ordinary `.rep/` state but do not undo files already indexed. These are GUI/database
  backups, not reviewable source. If any contain original program bytes they belong in the
  legal review, not just the size review.
- **Two tracked zips**: `Imgur Album Gotcha Force Manual NA.zip` (5,308,901 bytes) and
  `draft-1qf7j60-print-package.zip` (2,006,202 bytes). Not source. Remove, or replace with
  lawful upstream references plus checksums, unless license and reproducible purpose are
  documented.
- **Three tracked `*.gci` GameCube saves** at the repository root
  (`allborgsgotcha-force.28411.gci`, `gblack-galatic-emperor-save=gotcha-force.22132.gci`,
  `gotcha_force_100_usa.gci`). Same ownership question.

### 2.4 Nested repository ownership is porous — OPEN

`research/tools/OGhidra` has its own `.git`, yet the root index still tracks **1 file**
below it. A path must have one owner. The root should record an OGhidra revision — a
submodule, a lock file, or a documented clone command — not duplicate selected nested
files.

Give the nested history its own short contributor/agent document too: relative setup and
test commands, remote safety (`origin` is LLNL upstream; `fork` is the writable fork),
artifact schemas, and its public/private state boundary. It currently has none.

### 2.5 Root `AGENTS.md` is a private operations runbook in a public slot — OPEN

The root file is almost entirely private-machine operations: scheduled-task names,
absolute `D:\rig` and `D:\GotYaForce` paths, a named model and localhost admin endpoint,
VRAM thresholds, incident chronology, current branch routing, and machine-specific Python
paths. That is unsafe as the public contributor contract, and it also leaks into work
performed inside the separate OGhidra checkout.

The recommended split — **the safety rules are the part worth keeping public**:

Keep in a concise public root file: the product goal and module map; supported
setup/build/test commands from a clean checkout; the promotion invariant and the
definitions of *compiled*, *oracle-verified*, *integrated*, and *playable*; small-commit
and evidence requirements; legal boundaries (no disc image, ROM-derived dumps, secrets, or
proprietary SDK); and the safety rules that stay generally valid — never raw-kill the
managed port tree, settle verdicts through the journal API, preserve the OGhidra
fork/upstream remote distinction, no ad-hoc orchestration scripts, no product
heartbeat/telemetry.

Move to a private operations runbook: scheduled-task details, model loading, VRAM
thresholds, localhost endpoints, absolute paths, incident anecdotes, and operator
telemetry. [`docs/ops/`](../ops/) is where the rescued material of that kind now lives, and
it is the natural home if the split is made.

**Transient counts must be generated from canonical state, never hand-maintained in
`AGENTS.md`.**

### 2.6 Private-machine markers in tracked files — OPEN (not re-counted)

At audit time: **66 root-index files** (57 of them below `research/`) and **53
nested-index files** contained at least one of `D:\`, `C:\Users`, `manny`, or `AppData`.
Generated provenance and assembly gate detail embed absolute `D:\...` paths; committed
oracle results embedded absolute `D:\GotYaForce` paths. An external contributor cannot
reproduce the exact toolchain/artifact/evidence from public instructions alone, and
machine paths leak into public data.

### 2.7 Documentation status labels — PARTLY OPEN

Design and status prose contradicted each other because nothing said which document was
authoritative. The instruction is still worth following: **mark every design document
Current, Target, or Historical, with the schema/commit it applies to.** Named
contradictions at the time (in the nested OGhidra repo):
`scalable-verified-port-design.md` says compile alone never promotes;
`compile-fix-loop-design.md` deliberately places the rolling assembly gate *after* green;
`git-topology-design.md` describes a target topology explicitly not implemented. Root
`README.md` and `AGENTS.md` each restated a different one as current.

`docs/playable-port-design.md` has since become the single governing contract, which
resolves most of this — but the labelling rule still has no mechanical enforcement, and
`docs-site/roadmap/index.md` hard-coding counts while `docs-site/progress.md` reads
generated data is the same failure in miniature. **Keep one generated status surface with
commit, schema, and timestamp; never copy volatile counts into narrative pages.**

---

## 3. Explicitly not safe to bulk-delete

Recorded because a naive cleanup would destroy live state:

- Either `.git` directory (root, or nested OGhidra).
- Any registered Git worktree. `git worktree list --porcelain` proved
  `.claude/worktrees/*` and `.tmp/port-progress-worktree` are registered worktrees — the
  latter carries the `port-progress` journal lineage. Remove only through the normal
  worktree lifecycle.
- The whole `.tmp/` tree. The live journal worktree inside it makes recursive deletion
  unsafe; clean by named subdirectory only, after a process/ownership check.
- Current environment files, before credentials/config are migrated. The dated
  `.env.bak-*` backups are a secret-sprawl risk, not documentation — rotate credentials
  before deleting them.
- Live `research/decomp/generated/finish-game-port/` state. Root `.gitignore` deliberately
  re-includes only `knowledge-registry.json` from it.
- `.tools/` (≈249 MB of private local toolchain) — not public source, but current scripts
  may depend on it. Document a reproducible bootstrap before removing.
- The nested `.venv/` — recreate only after the Python install path is documented and
  locked.

Safe in principle (empty dirs, ignored logs, deterministic caches), still only in a
dedicated cleanup task after checking no process owns the path: empty `.agents/`; the
root `.codex-vite-517*` logs; `.pytest_cache/`, `__pycache__/`, `*.tsbuildinfo`, package
`dist/`, Gradle `.gradle/build/dist`; `docs-site/.vitepress/data/` and `dist/` once
`curate-data.mjs` plus the atlas build are proven to reproduce them; `apps/game/dist/`,
`node_modules/`, `.pnpm-store/` once the lockfile install/build is documented.

---

## 4. Acceptance checks for "this is a public repository"

A cleanup is acceptable when a fresh public checkout proves **all** of:

- root and nested `git status --short --ignored=matching` show only documented
  local/generated classes;
- no tracked path lives under `.tmp/`, `.superpowers/`, raw `analysis_sessions/`, Ghidra
  `.rep` backups, dependency/build caches, or local env files;
- no tracked file contains user names, absolute private-machine paths, secrets, raw
  prompts, heartbeat/liveness state, or controller log dumps — except a narrowly reviewed
  historical evidence fixture;
- all large or opaque tracked files are covered by a size allowlist plus license/provenance
  and reproduction metadata;
- OGhidra has one Git owner and its exact revision is reproducible from the product
  checkout;
- `pnpm install --frozen-lockfile`, typecheck, production game build, browser smoke, atlas
  curate/build/link check, and the documented nested Python tests all run from clean
  environments;
- generated commands leave only ignored outputs and reproduce checked-in manifests
  byte-for-byte, or with documented normalized fields;
- README/status claims are derived from the same executable gates and name the proving
  commit;
- contributor navigation exposes setup, verification, porting, assets, and troubleshooting
  without requiring private dashboards or local operator knowledge.

**Every commit in the cleanup should close an end-to-end path:** documentation points to a
command, the command produces a named artifact, an executable check verifies it, and a
clean checkout can reproduce the result without private machine folklore.
