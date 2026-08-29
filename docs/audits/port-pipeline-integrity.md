# Port pipeline integrity

**Provenance.** Rescued 2026-08-29 from untracked session audits dated 2026-08-21
(`assembly-failure-rca-20260821`, `port-implementation-redteam`, `t2c-registry-current-audit`,
`oracle-phase1-current-audit`, `oracle-core-migration-audit`, `playability-architecture-audit`,
`assembly-green-recovery-manifest.json`), 2026-08-22 (`assembly-abi-resume-status`,
`assembly-abi-module-*`), and 2026-08-23 (`overnight-handoff`).

**Status.** Substantially superseded by [`docs/playable-port-design.md`](../playable-port-design.md),
which is the governing contract. This page keeps what that design does not: the measured
evidence behind it, the defects it does not cover, and the acceptance tests written for
each. Statuses re-checked 2026-08-29.

**Repository note.** Most implementation cited here lives in the *nested* OGhidra checkout
(`research/tools/OGhidra`), which has its own Git history. Commit SHAs are labelled with
their repo — GotYaForce, OGhidra, or `D:\rig` — because none of the three resolves in the
others.

---

## 1. Root cause: the assembly gate had no owner-definition ABI precedence

The 2026-08-21 RCA of two blocked units is the origin of the whole ABI workstream.

### `auto-c0018-018` attempt 3 — declaration conflict on `zz_00f0104_`

Iteration 2 linked individually at 16:19:12, then assembly failed at stage `merge` with one
conflict. Candidate digest
`e96ef43340ddd601613940fd3a7cd1aa2c778ffe1f5d43e64aeb41651ceaf4f4`. Window:
`auto-c0011-010`, `auto-c0034-018`, `auto-c0035-002`, `auto-c0029-013`, candidate.

| Where | Declaration |
| --- | --- |
| `port-units-staging/auto-c0029-013/gnt4_shim.h:127` | `extern int zz_00f0104_();` |
| `port-units-staging/auto-c0034-018/gnt4_shim.h:136` | `extern int zz_00f0104_();` |
| candidate's repaired header, line 163 | `extern void zz_00f0104_(int param_1, int param_2, int param_3);` |

All three call sites (`c0018 unit.c:117`, `c0029 unit.c:30`, `c0034 unit.c:176`) pass three
integer-shaped arguments and ignore the result. The **true owner** is in the queue already:
`auto-c0026-002`, `chunk_0026.c:685-722`, `void zz_00f0104_(int,uint,uint)` — ABI-compatible
with every observed call. The advisory knowledge registry (v49) had only a **revoked**
caller-derived entry, so it could not resolve the gate.

### `auto-c0035-006` attempt 4 — Wasm signature mismatch on `zz_00076d0_`

`wasm-ld: error: function signature mismatch: zz_00076d0_`. Candidate digest
`04243bba39c02497077e668df7eadda68fd489427d9d67772166689cf3524352`.

Both referencing units declared the **identical** generic `extern int zz_00076d0_();`
(c0034 header line 129, c0035 header line 132), so the *merge* passed — and then the two
call sites lowered to incompatible Wasm import types: c0034's `unit.c:36` passes
`(double)*(float *)(param_9 + 0x58)` first (infers f64); c0035's `unit.c:218` passes a
`param_1` of type `undefined8` first (maps to i64). The owner is `auto-c0000-006`,
`chunk_0000.c:1991-2033`, a 16-argument `void` prototype. The registry had **no entry at
all** for the symbol.

**The two manifestations are the same missing seam.** A generic `extern int f();` masks
incompatible call shapes until link; a *more precise* caller-derived declaration causes an
earlier textual conflict at merge. The gate compared declaration **text**, merged if
identical, and let the compiler and linker discover ABI disagreement — it never consulted
the unique direct definitions already sitting in `oracle-registry.json`.

**Recurrence proof, not a transient:** `assembly-gate.json` records this exact link
conflict at 05:37:21, 08:57:42 and 16:19:40 on 2026-08-21 over *changing* windows.

Also decisive: the targeted-symbol LLM question fired for c0035 was scoped to
`FUN_801336a4` and `FUN_80133cbc` and returned only two address macros. **It could not
possibly have repaired `zz_00076d0_`** — an assembly failure was routed into the *source*
retry pool.

### The prescribed repair (implemented; see §2)

1. Build a deterministic symbol → owner-prototype catalog from the queue's verbatim
   definitions.
2. At merge, replace generic/caller-derived declarations for shared internal callees that
   have exactly one owner definition.
3. Emit resolution evidence — symbol, owner unit and source range, definition and catalog
   digests, discarded variants, chosen prototype. **Never a silent winner.**
4. Fail closed on an absent or ambiguous owner, an owner/prelude contradiction, or
   incompatible duplicate definitions.
5. Include the ABI-catalog digest and version in the assembly world, so composition reds
   reopen exactly when their resolution changes.

**Boundary that must hold:** a unique verbatim definition is *structural* evidence. It may
choose an assembly ABI over caller guesses. It does **not** prove behaviour and must never
raise a unit or registry entry to `oracle_green`.

---

## 2. The finding that changed the design: a generic prototype is not caller evidence

**This is the most consequential measurement in the archive** and it nearly went the wrong
way.

The canonicalization spec as written required a pinned-Clang
`__builtin_types_compatible_p` probe of owner-vs-variant before any replacement, and
required `incompatible` to become **contested** rather than substituted. Applied to real
staged artifacts that rule produced:

- **239 unique-owner declaration variants across all 45 staged units**, of which the
  generic `extern int NAME();` — Ghidra's default guess — accounted for **201 (84%)**;
  specific declarations whose return type matched the owner, **23 (10%)**; specific
  declarations contradicting the owner, **15 (6%)**.
- Measured with the real pinned Clang over staged headers, **60 sampled symbols produced
  13 compatible against 59 incompatible — roughly 82% contested.**
- Sampled windows: **0 of 400 came out clean.**

In C, `int f()` is incompatible with `void f(int)`, so under a compatible-only rule the
dominant shape is always contested. *Applied exactly as specified, canonicalization would
not have unblocked the port. It would have converted most compositions from a link failure
into a contested refusal.*

**The amendment.** An unprototyped `extern int NAME();` carries **no parameter
information** — it is a placeholder, not a rival claim. Probing it as a competing
declaration is a category error; treating it as the *absence* of a declaration, superseded
by the owner prototype, cannot lose information. This is the RCA's own P2 finding, which
the spec had failed to carry into its section 3.

With the amendment the contested set drops **201 → 15 (6%)**, and two independent
measurements land on the same 15 symbols: self-contradictory decompiler output where the
owner says `void` and a caller declares and consumes a value. **Those deserve individual
investigation, not a silent cast.** Sampled windows went **0% → 88% clean**.

Refined rule that shipped: where a body consumes a `void` owner's result, the owner's
**defining unit** decides — inside the bundle the contradiction is real and contests; an
*import* keeps the owner's parameters with a value-returning result.

### The related warning that came out of the same work

An earlier pass measured how many call sites *use* a void-owner's return value — **83 of
1,391, 6%** — and concluded ~7% would be contested. **That measured the wrong thing:** the
gate probes owner/variant *declarations* and never looks at usage. The correct measurement
gave 82%. Two different quantities that both look like "how bad is this".

### Proof of fix

On the exact five-artifact window that failed 2026-08-21 with the `zz_00076d0_` signature
mismatch: schema-1 registry validated (10,954 functions / 1,396 units); owner snapshot of
82 bindings from the 827 symbols the window references, real Ghidra bytes, pinned Clang,
84 s; gate `pass` with 80 owners bound, 85 declarations canonicalized, 38 Clang probes;
emcc compile and link exit 0; `assembly.wasm` 8,857 bytes. Both blocking symbols carried
one identical owner prototype across all five units.

The c0018 window reproduced the same way: before, 1 conflict on `zz_00f0104_`, class
`collision_stub`, "2 divergent function_decl declarations"; after canonicalization, 0
conflicts and one surviving `extern void zz_00f0104_(int param_1,uint param_2,uint param_3);`.

**And the trap inside the fix.** Canonicalizing the c0035 window removed the link error and
produced **two new compile errors**, e.g.
`auto-c0011-010.c:203:11: error: assigning to 'int' from incompatible type 'void'` for
`iVar3 = FUN_800669d0(param_1,0xc0);`. The verbatim caller body assigns from a function
whose owner definition returns `void`; the generic `extern int f();` was what made that
compile. Naive substitution is not safe — which is exactly why the compatibility probe
exists.

---

## 3. Promotion ordering — the defect a regression test enforced by name

Recorded in the red-team and playability audits, and encoded as data in the recovery
manifest.

The driver committed, pushed, checkpointed, wrote `status="green"` and emitted
`wasm_unit_green` — and *only then* invoked the assembly gate.
`_maybe_run_assembly_gate` explicitly stated the gate "NEVER changes the unit's verdict",
caught all faults, and committed only telemetry. `SETTLED_STATUSES` included every green.
A regression test encoded the defect by name:
**`test_assembly_gate_failure_pages_but_never_costs_the_green`**.

The live execution trace, `auto-c0029-014`:

| Time (UTC) | Evidence | What happened |
| --- | --- | --- |
| 08:57:30 | `events.jsonl:1926-1927` | Unit linked individually; eight registry entries harvested immediately. |
| 08:57:38 | `events.jsonl:1928` | `wasm_unit_green` recorded commit `b9658664`, `pushed:true`, summary `compile-only (UNVERIFIED)`. |
| 08:57:42 | `events.jsonl:1930-1931` | *Only then* the five-unit gate failed at link on `zz_00076d0_`. |
| 08:57:43 | `events.jsonl:1933` | Selector advanced to the next unit. No revoke, quarantine, or block. |

Git corroborates: `origin/port-staging` resolved to `b9658664`; the failure commit
`8b785f73` ("gate N=5 FAIL") existed only locally. **The remote-visible truth was the
purportedly green artifact, not its failed composition result.**

`auto-c0029-014` was also *falsely implicated* — its queue entry never names
`zz_00076d0_` and the symbol does not occur in its artifact.

### The required invariant

> An artifact may be pushed to an inventory branch as `compiled_isolated`/`staged`, but it
> may not acquire `green`, `verified`, `promoted`, `integrated`, authoritative-registry
> status, or product progress credit until one atomic transaction proves: (1) isolated
> compile and import policy; (2) definition-derived ABI compatibility and link/instantiate
> against the dependency-closed candidate plus current final-build members at exact
> revisions; (3) behavioural oracle; (4) membership in a versioned final-build manifest;
> (5) actual product build consumption; and (6) deterministic browser gameplay replay. Any
> failed step records `composition_blocked`/`verification_blocked` and leaves the prior
> certified product manifest unchanged.

Use distinct, non-settled states — `compiled_unverified`, `assembly_blocked`, `oracle_red`,
`certified` — and reserve `green`, `integrated`, registry authority and product pushes for
certified artifacts the app consumes.

### The recovery manifest, and the principle inside it

`assembly-green-recovery-manifest.json` (schema 1, `mode: "review-only"`,
`execution_authorized: false`, generated 2026-08-21T12:48:39Z) is a machine-readable
revocation plan for **eleven** units promoted green despite their candidate's N=5 gate
having failed: `auto-c0018-018`, `auto-c0019-001`, `auto-c0019-002`, `auto-c0028-013`,
`-014`, `-015`, `-016`, `-017`, `auto-c0029-013`, `auto-c0035-002`, `auto-c0035-006`. Each
entry pins one `revoke-unit` invocation with a precomputed transition ID
(`sha256(canonical-json({schema:2,unit,reason,previous_record}))`), the exact event lines
and their SHA-256, the five-unit window, per-conflict `{class, symbol, units[]}`, and a
post-condition requiring ten canonical fields to be **absent** afterwards (`tier`,
`oracle_summary`, `commit`, `pushed`, `settle_reason`, `settled_via`,
`promotion_transaction_id`, `promotion_transition_id`, `candidate_sha256`,
`world_version`).

**The durable part is the one exclusion.** `auto-c0034-018` is deliberately *not* revoked,
because its own candidate gate passed (`stage=pass`, window
`auto-c0028-015/-016/-017`, `auto-c0035-002`, `auto-c0034-018`). Reason as written: *"own
candidate gate passed; presence in another candidate failing window is insufficient."*
That is the operational encoding of §4.

The manifest's remote refs (`main=ecdcb7e2…`, `port-staging=b9658664…`) are an **earlier**
snapshot than the rest of this page; do not cross-cite them as current.

---

## 4. Link-error attribution blames every unit in the window — OPEN

`conflicts_from_link_error(error_text, names)` passes the whole `units` list into
`_conflict_record` for every parsed diagnostic. The live ledger therefore claims all five
window units for `zz_00076d0_` when only `auto-c0034-018` and `auto-c0035-006` reference
it. Tests assert only class and symbol, never contributors.

Consequence: remediation and registry revocation cannot target the responsible
declarations or call sites; innocent units are quarantined in reports while the actual
incompatible caller ABI persists across rotating windows — and "largest N ever passed" can
rise merely because a bad pair aged out of a rolling window.

**Fix:** build a symbol → definition/declaration/call-site index before link (or use
compiled-object import/definition tables) and intersect a linker symbol with its owners.
Unknown attribution must say `owners_unknown`, not implicate everything. A regression using
the live five-unit shape must report exactly c0034-018 and c0035-006 with their normalized
signatures, and exclude c0029-014.

---

## 5. The advisory knowledge registry (T2c)

### What is correct and must be preserved

The per-unit trust model is substantially implemented, and its boundary is the part worth
keeping:

1. `compile_only` means **advisory evidence only** — it may be shown to an LLM as a
   comment, but cannot become an active declaration merely because an earlier unit
   compiled.
2. `oracle_green` alone may inject actively, and even then mutation or deletion is recorded
   as a deviation/conflict rather than silently suppressed.
3. A direct definition prototype is **structural** ownership evidence. It may choose an
   assembly ABI over caller guesses; it does not prove behaviour.
4. Same-tier, same-derivation disagreements are contested and withheld.
5. Revocation is *source-lifecycle* evidence: the entry is skipped and its tombstone
   explains prior injection. It must not erase the immutable fact that a verbatim function
   definition exists elsewhere in the corpus.

### The architectural split point 5 forces

The live registry revokes definition-derived prototypes together with the unit verdict.
That is correct for an advisory/behavioural registry — and it makes the registry
**unsuitable as the assembly owner catalog**, because structural ownership exists whether
or not the owner unit has been ported, staged, revoked, or behaviourally verified. A
separate digest-bound structural owner catalog is the correct assembly input, carrying
`behavioral_authority=false` and never altering T2c or oracle tier.

### Measured state, 2026-08-21 (historical)

Registry v49, 250 entries: 249 prototypes, 1 `dat_typing`; **250/250 `compile_only`, 0
`oracle_green`**; 134 active, 116 revoked; 124 entries carrying 132 conflict records, all
revocation tombstones; **0 contested**.

Against the assembly ledger's 64 records over 54 unique symbols: **41 symbols absent from
the registry, 13 present only as revoked tombstones, 0 active, 0 contested.** Of the 45
unique `collision_stub` symbols, the Phase-0 registry had exactly one verbatim owner for
41, and none for the four SDK seam symbols (`gnt4_PSMTXConcat_bl`, `gnt4_PSMTXTrans_bl`,
`gnt4_PSVECAdd_bl`, `gnt4_PSVECSubtract_bl`).

A contested count of zero therefore meant *"no disagreement has been folded through this
path"*, not *"cross-unit ABI agreement has been proven"* — every active entry had exactly
one source and all 33 visible `registry_harvested` events reported `agreed: 0`.

### Still open

- **The F6 holdout falsifier is data-only.** Deterministic 10% holdout assignment and
  `holdout_sources` exist; no windowed agreement rate, minimum sample, disagreement
  threshold, dashboard row, or symbol-class freeze exists. Until it does, advisory
  injection cannot be called self-falsifying.
- **Registry advice is published before composition.** Harvest occurs before commit and
  before the gate, so a composition-failing unit's entries are co-pushed and can warm later
  units, with no rollback path. Stage registry deltas in memory and commit them only inside
  the successful certification transaction.
- **`record_surviving_deviations` marks an oracle-green/oracle-green deviation only with
  `green_green=True`** and does not set `contested=True`, so later authoritative injection
  can continue.
- **244 stored definition-derived declarations end in `;;`.** Accepted by C as an extra
  empty declaration, hidden by normalization, but non-canonical stored evidence. Repair
  with an idempotent versioned migration through the journal/co-commit path — never by
  hand-editing the live file.

---

## 6. Oracle evidence integrity

### Phase 1 result integrity — FIXED

The original defect: *a result JSON counted as a verdict merely by existing.* Two of three
tracked results silently pointed at superseded Wasm.

Landed as GotYaForce `026ae25f`.
`research/decomp/oracle-harness/lib/result-integrity.mjs` recomputes every recorded
identity — Wasm, spec, replay corpus, field map and its `actor.ts` source, harness content,
harness revision — and returns `current` / `superseded` / `invalid` / `rejected`,
fail-closed. `pnpm test:oracle` runs codec, zero-case, result-binding, clean replay,
deliberate-red, and determinism as one command with no Dolphin, network, or model
dependency, and **is wired into `ci.yml`**.

**Standing rule this encodes: a result file is evidence, never a verdict. Only
`{valid:true, status:"current"}` may count.** Do not assert *why* a stale result is
refused; the reason legitimately moves as the driver rebuilds units (see the note in
`research/decomp/oracle-harness/tests/result-integrity.test.mjs`).

### The arena is bound to real console RAM — FIXED

Landed as GotYaForce `76ac287f`. Before it, the oracle arena was **13,312 bytes with zero
provenance** underneath every verification claim. All **14 segments** are now byte-identical
against two independent Dolphin MEM1 captures.

**The trap inside that work, worth keeping:** the arena is little-endian (wasm) while real
RAM is big-endian PowerPC, so the comparison is an **element-wise swapped copy at each
segment's own width** — 2 B for s16 rows, 4 B for f32 and pointer tables, 8 B for f64
constants, none for the char table. Compared *without* per-segment width it reports **1%
agreement**, and even a float `1.0` looks wrong. The first reasoned explanation of that 1%
was an arena bug; measurement showed it was endianness.

Chain closed: `damageFormula.json`'s six constants agree with the arena **and** with
console RAM, so damage-core is ROM-grounded end to end.

### The differential-oracle route converts zero new units — OPEN, architectural

`run-unit.mjs` requires full export coverage (`allPass = fnsClean && uncovered.length === 0`).
Only `port`-grade functions qualify for differential specs. Measured 2026-08-23:

- **202 of 1,036** functions in the 133-unit `differential_vs_ts` bucket are port-grade.
- Exactly **two** units have every function port-grade — `collision-core` and
  `knockback-core` — **and both were already green**.
- **0 of 49 staged units qualify.**

Meanwhile `_check_unverified_buildup` had fired **37 times** (`verified: 1, staged: 32`,
fraction 0.05 → 0.0303) **with nobody receiving the page.** A pager that fires into nowhere
is not a control.

Conclusion: **Phase 4 (Dolphin trace-recorded oracles) is the only route** for the ~86% of
units with no TypeScript reference — the phase the plan explicitly left unscoped.
Prerequisites already exist on the rig: working captures, a symbol map, and two 24 MB MEM1
images.

Related, still open: `research/decomp/data/oracle-commands.json` still contains exactly one
entry, `damage-core`, which is already green — so the running verification queue has no
candidate. Its own notes still say the driver overlay is inert "until Phase 2 lands", which
is stale prose; the overlay landed.

### Legacy verdict migration for the three core units — SPECIFIED, not landed

`damage-core`, `knockback-core` and `collision-core` were green from a pre-tier era.
Static migration was **refused for all three**; each is "conditional PASS" only after a
fresh replay inside a locked, journal-first transaction.

| Unit | Why static migration was refused | Sanctioned replay |
| --- | --- | --- |
| `damage-core` | Its tracked Phase-1 result is *intentionally* superseded; the ignored `oracle.log` is mutable. | Generic sidecar / current result-integrity path. |
| `knockback-core` | No generic sidecar, spec, or result, and no durable ProgressJournal green receipt. | Pinned historical harness, labelled `historical_harness_replay`. |
| `collision-core` | Tier and artifact digest are already journal-bound, but there is no modern pass replay/receipt. | Pinned historical harness, same label. |

The rules that survive regardless of when this lands:

- **Merely finding a PASS string, a result JSON, or an old `wasm_unit_green` record is a
  refusal.** The ignored `oracle.log` is mutable; a fabricated old PASS log while the
  runner fails must refuse.
- `damage-core`'s historical harness **does not set a failing exit code**, so pattern
  enforcement is load-bearing: exit 0 with one absent per-function pattern must refuse.
- Historical-harness receipts are labelled narrowly and **do not increment generic Phase-2
  coverage**.
- No T2c decision may be promoted by the migration — the live registry has **zero** entries
  sourced from any of the three units, so registry promotion is an expected byte-stable
  no-op. A test must fail if migration creates an oracle-tier entry from nothing.
- All three core artifacts inhabit the older float/`undefined8` ABI island. Upgrading their
  verdicts must not be read as assembly compatibility with the current generated inventory.

Artifact bindings recorded at audit time, still useful as integrity targets:

| Unit | Original green commit (GotYaForce) | `unit.wasm` SHA-256 |
| --- | --- | --- |
| `damage-core` | `b2f8d88ae9e3159928b59cbb30d50dccd3554cde` | `3de9a52a61ecfcd416fd89dae049e9e42f214100bca51b31ef0cafdbcb1e25f5` |
| `knockback-core` | `61c27e2817a9d18e3b4e002234cb06ad9583c4c9` | `1c1465fee75dfc197d06ec50c7794e23841e032dc677fd2eb0752c50542625f5` |
| `collision-core` | `f6b8b65d202671ac397c104d3ed13f1bccbfbb52` | `85b767c32cae39d7c8e6a08908ba1b11c8a200a88667fdf496a94f654b708698` |

Each original commit contains exactly four committed files — `gnt4_shim.h`,
`provenance.json`, `unit.c`, `unit.wasm`. The fifth local file, `oracle.log`, is covered by
`.gitignore`'s `*.log` and is **never** historical Git authority.

### Where to run a replay — the topology rule

When product `main` and the artifact lineage diverge (they did: 15 commits only on the
artifact lineage, 7 only on `origin/main`, from common base `8987031e`), the replay must
run in a **temporary detached worktree at the exact reviewed commit** — attached to no
branch, so it cannot move a product or artifact ref — with output to a task-owned directory
outside the worktree.

Six alternatives were considered and each refused for a specific reason: merging
`origin/main` into local `main` moves the artifact lineage and the next push carries the
merge to `origin/port-staging`; creating a local `port-staging` is an unnecessary ref write;
reusing `.tmp/port-progress-worktree` violates journal authority; cherry-picking into the
artifact checkout leaves copied harness files unbound to the recorded `harness.git_rev`,
making the receipt misleading; a `git archive` extract under `D:\GotYaForce` resolves the
parent checkout's revision when the runner calls `git rev-parse HEAD`; and attaching to a
branch is strictly weaker than a detached full-SHA worktree.

Mechanics that matter:

- **`git -c core.autocrlf=false worktree add --detach <path> <sha>`** — otherwise replay
  identities do not match canonical Git blob bytes or the Linux CI lane. Do **not** create
  a branch.
- Set `TEMP`/`TMP`/`TMPDIR` to a `D:`-backed directory. `C:` had under 1 GB free.
- Do **not** set `ORACLE_WASM` (the canonical worktree path already holds the published
  bytes) and do **not** overwrite the tracked
  `research/decomp/data/oracle-results/damage-core.json`.
- **Any preflight mismatch is a refusal, not a prompt to fetch, reset, merge, clean, or
  force.** Never `git worktree remove --force` an unexpectedly dirty replay worktree —
  leave it, inspect, report.
- A standalone replay is topology proof only. **Its result must not be reused later as the
  migration receipt** — the migration runs a fresh replay inside the locked transaction.

---

## 7. Standing defect classes in the driver

Recorded 2026-08-21 to 2026-08-23. These are in the nested OGhidra repo; none was
re-verified on 2026-08-29.

### 7.1 Reverification does not verify the committed bytes

`_reverify_unit_inner` claims to run against the committed artifact but reads
`staging_root/<name>/unit.wasm` directly, and binds only the provenance export-name hash.
Provenance carries no commit-object digest for the wasm, header, or source. **A user or
concurrent process can replace staged `unit.wasm` after its staging commit without changing
`provenance.json`, and reverify will oracle, commit and push the replacement.** On oracle
failure the record stays green/compile-only and the same spec is permanently skipped; on
pass, promotion re-runs neither the import gate, nor whole-closure assembly, nor the app
gate.

**Fix:** resolve the source artifact with `git show <staging_commit>:<path>` (or a clean
detached worktree), verify SHA-256 for wasm/source/header/provenance, and bind the oracle
result to wasm SHA + spec SHA + harness revision + corpus SHA. Oracle-red must transition to
*quarantined*, leave every green/staged/certified selector, and be reopenable only when one
of those bound inputs changes.

### 7.2 The world version does not hash the inputs that determine a result

`compute_world_version` includes serving config, emcc version, OGhidra HEAD, a manual prompt
integer, and registry version — and omits the unit's extraction/source bytes, queue entry,
ranges, exports, allowlist, header seed, transform code and output, full prompt and sampling
settings, oracle sidecar/spec/corpus, product revision, and uncommitted OGhidra changes.

Consequence in both directions: a real source/header/queue/oracle fix can leave a red
permanently unschedulable, while an unrelated OGhidra commit reopens every red.

### 7.3 Assembly retry identity is not assembly-specific

`_fail` labels composition failures `pipeline-control` and skips diagnosis, but the selector
still models every `red_retryable` through the same world/relevant-registry gate — so an
unrelated *source* registry entry can reopen a composition red and trigger a targeted source
question. That is exactly what happened to `auto-c0035-006`.

Bind assembly retry to: candidate/source digest, exact conflict symbols and variants, the
precise object set, window artifact digests, assembly implementation revision, and the
relevant ABI-catalog digest. **Never launch diagnosis or targeted-symbol LLM work solely
from an assembly failure.**

### 7.4 "Verbatim / byte-faithful C" is false at both boundaries

`extract_verbatim` decodes UTF-8 with `errors="replace"`, uses universal-newline
`read_text`, then hashes the re-encoded text. `materialize_unit_c` applies a D5 source
transform and stores the result in a variable named `verbatim`, despite the system prompt
promising the C cannot be edited. Assembly decodes with `utf-8-sig` and rewrites LF while
commenting that bytes are copied verbatim; its test compares normalized text, not bytes.

**Provenance hashes therefore cannot prove a committed source is the exact Ghidra export
slice.** Preserve raw slices and raw SHA-256 before any decode; store separate
`source_raw_sha`, `canonical_source_sha`, and `build_input_sha` with an explicit transform
record; a CRLF + BOM + invalid-UTF-8 fixture must round-trip byte-identically or fail
loudly.

### 7.5 The post-link import scanner is a regex, not a parser

`scan_disallowed_imports` searches raw bytes for `env.` followed by 2–40 printable
characters and claims false negatives are impossible. It ignores non-`env` modules,
truncates or bleeds long names, and does not validate section structure. Use
`WebAssembly.Module.imports` or wasm-tools.

### 7.6 Streaming output is discarded

Every LLM lane uses a no-op stream callback, and the only test asserts that feeding an
`assistant_delta` returns `None`. If the connection dies after useful tokens, `_compile_fix`
receives no recoverable answer, spends another model call on the same problem, and external
progress appears frozen. Retain a bounded, attempt-scoped partial stream **outside product
history** (rig state or an ignored workdir) and classify disconnects as transient rather
than blaming the unit. Do not solve this with heartbeat commits in the product repo.

### 7.7 Ordinary world-changed retries do not consume the captured post-mortem

`_compile_fix` builds its prompt only from current C, header, and errors. Rounds and
fingerprints are captured, but only targeted/diagnosis questions receive
`assemble_post_mortem`. On attempt 2 after a legitimate world change, the prompt should
carry prior normalized persistent diagnostics and failed forms, and identical failed
declarations must not be resurrected without new evidence.

### 7.8 Queue eligibility ignores runtime-semantic dependencies

`port_queue_fill.skip_reason` excludes only SDK-prefixed and non-C-identifier names.
`port_unit_generator.py` emits every external callee as a guessed `extern int name();` and
defines `code` as an unprototyped function, while acknowledging that address→wasm-table
dispatch is a later stage — yet still making every unit compile-only eligible.

Concrete dead end: `auto-c0033-005`'s source stores `&LAB_80123808` into the emulated actor
(`chunk_0033.c:1571-1595`, especially `:1580`). A header can silence the undeclared-label
error; it cannot turn a native C code address into the stable linear-memory callback pointer
the game later dispatches. **The runtime dependency does not exist.**

Tag address-taken labels, indirect calls, function-pointer fields, and unresolved canonical
callees statically; such units become `dependency_blocked` on a named runtime capability and
are ineligible for green or LLM header repair.

*(Partially addressed 2026-08-23: `allowed_extra_imports` came from a regex requiring a
following `(`, so `*(code **)(puVar1 + 0xc) = zz_01a4e90_;` was missed and the gate demanded
the model define a body living in another chunk. Fixed at the generator, the live unit gate,
and the assembly gate — the last because fixing only the unit gate made the two asymmetric,
which `_emcc_link_many`'s docstring forbids. **Explicitly not validated in production**: no
unit has yet passed *because* of those commits.)*

### 7.9 Tests are doubles at exactly the boundaries that fail

Per-unit tests write `b"\x00asm"` and fake git and oracle; the assembly pass test writes the
same invalid four bytes with a fake linker and smoke; verification fixtures are fake. No
suite calls real emcc + wasm-ld + Node + a Git remote + Vite + Chrome as one flow. At the
time, the venv suite reported **165 passed** while the live artifact still failed
composition after push and had no app consumer.

The generalized lesson, independently reached twice in the ABI module work: **a green
internal suite is not evidence.** 133/133 and 280/330 greens each hid P0-class defects that
were found only by probing the adapter seam from outside.

### 7.10 Public reproduction is machine-bound

The driver hard-codes a private Node fallback; queue tools default to `D:\GotYaForce`;
committed oracle results embedded absolute `D:\GotYaForce` paths. Builds assume a vendored
`research/tools/emsdk` and Git Bash at fixed Windows locations. `oracle.log` is globally
ignored, so a reviewer cannot audit the log that supposedly supports a verdict.

---

## 8. Operational traps in this pipeline

The set most likely to bite again. Traps about the machine itself are in
[`../ops/rig-serving-and-gpu-handoff.md`](../ops/rig-serving-and-gpu-handoff.md).

1. **An ABI refusal is a property of the WINDOW, not a verdict on the unit.**
   `auto-c0035-001` failed `owner_variant_abi_incompatible`, then went green on retry with
   zero conflicts once the four pinned partners rotated; `auto-c0029-014` cleared after five
   consecutive failures. The real cost is churn — a full LLM generation plus a gate burned
   per attempt — not permanent loss. Do not conclude a unit is permanently blocked from one
   such refusal.
2. **The partner window self-reinforces.** Assembly partners are chosen as
   `prior[-max(0, n - 1):]` — the last N−1 prior units, deterministically. With no green
   since 13:45 the window froze on `auto-c0028-013/-014/-016/-017`, which declare the
   recurring problem symbols including `FUN_80047aa4`. A stall makes the stall worse.
3. **The D5-migrate install deadlock.** The 2026-08-21 D5-6 migration revoked 12 units with
   `via: "d5-migrate"`, writing only `{at, reason, previous_status, previous_tier,
   transform_sites}`. The artifact-install replacement path (`port_wasm_units.py`, ~line
   2836) requires `via == "revoke-unit"` plus `transition_id`, `previous_record_sha256`, and
   `previous_commit` — fields the migration never wrote. Affected:
   `auto-c0001-003/-004/-007/-010/-011/-012/-014`, `auto-c0011-004/-011/-012`,
   `auto-c0019-000`, `auto-c0034-018`. **Each unit rebuilds, passes the N=5 gate clean, and
   is then refused at install — burning a full port cycle per attempt.**
4. **The SDK shim seed is incomplete, and the guard does not protect it.**
   `gnt4_shim_seed.h` declares **6** `gnt4_*` functions; staged units declare **17**. The 13
   missing are invented per unit, so units disagree and the N-unit link fails. Six symbols
   conflict:

   | Symbol | Disagreement |
   | --- | --- |
   | `gnt4_PSMTXConcat_bl` | `double` vs `undefined8` — a real f64/i64 ABI split |
   | `gnt4_PSMTXTrans_bl` | `undefined8` vs `void` |
   | `gnt4_PSVECAdd_bl` | `undefined8` vs `void` — **is in the seed; the model rewrote it** |
   | `gnt4_PSVECSubtract_bl` | `undefined8` vs `void` — **is in the seed; the model rewrote it** |
   | `gnt4_PSMTXRotRad_bl` | parameter names only (harmless) |
   | `gnt4_PSVECMag_bl` | parameter names only (harmless) |

   `auto-c0029-000` commented **out** the seed's `gnt4_PSQUATScale_bl` because the symbol's
   address was assigned to an `undefined8`, then disagreed with four siblings still
   declaring it. **The header guard rejects `gnt4_` definitions but not declaration edits**,
   so the compile-fix loop can mutate seed declarations. Signatures must come from a real
   libogc/SDK reference, not recollection — getting `gnt4_PSMTXConcat_bl`'s return type
   wrong silently miscompiles every caller.
5. **The compile-fix reply truncates at a budget ceiling, not a model failure.** Units whose
   `gnt4_shim.h` grows past ~10 KB red out under `COMPILE_FIX_MAX_TOKENS=4096`. Symptoms
   mimic carelessness — an unterminated `/*`, a line cut mid-token at `extern void zz_00` —
   but it is a ceiling. The 27B model on the 1080 Ti runs ~2.5 tok/s, so raising 4096 → 6144
   pushes worst-case generation toward ~40 minutes per iteration. **The better fix is to
   stop making the model re-emit the whole header.**
6. **emcc does not propagate wasm-ld's message.** It reports only that its subcommand
   "failed (returned 1)". Two 2026-08-23 commits improved *truncation* of build errors; they
   do **not** make link failures diagnosable, because the problem is a missing capture, not
   a truncation. The gate's `conflicts` field already names the cause structurally by
   comparing unit declarations rather than parsing the error. Recovering linker text
   requires capturing the wasm-ld invocation separately.
7. **A stuck `porting` record is reconciled, never hand-edited.** `_reconcile_interrupted`
   runs at driver startup and requeues with a journal transition; its docstring calls that
   "the normal path, not an exception". A stale `wasm-units.lock` whose holder is genuinely
   dead is reclaimed automatically. See also the settle-through-journal rule in
   [`AGENTS.md`](../../AGENTS.md).
8. **`_preflight_dialect` refused every real staged file.** A declaration site's span walks
   back to the previous statement terminator, so the first declaration in a container
   swallows any leading `#include` / `#ifndef`. Every real staged `gnt4_shim.h` and `unit.c`
   leads with directives; all four real files probed were refused. Either the site scanner
   starts the span after the last directive, or preflight ignores directives outside the
   declarator.
9. **Owner-snapshot cost.** The snapshot must be built with the real pinned Clang (else
   `parser_tool_identity_mismatch`), and the declarator parser spawns a process per parse:
   **10,954 functions × 2 parses is on the order of hours.** It needs caching keyed by
   registry digest plus parser identity, or the gate cannot run per unit.
10. **Nine fixture-vs-reality assumptions** each caused a refusal against real data and are
    worth re-checking in any new parser: the top-50 `ranked_units` shortlist read as a
    per-unit index; `gap_partial_slots` summed rather than maxed; `oracle_kind` conflated
    with the oracle buckets; a `;` inside a comment ending a declaration; a declaration span
    swallowing the macro prelude; `#define ABS(x)` read as a call; `typedef void (code)();`
    making `void` a callee; a prototype and its definition in one file counted as ambiguity;
    an appended prototype for a symbol the unit defines as a pointer-table macro, which
    preprocesses to `void ((code *)0x801336a4)(int);`.
11. **The `_check_unverified_buildup` pager fires into nowhere** — 37 unheard pages by
    2026-08-23.
12. **Address coordinates come from the chunk marker and `_index.tsv`**, not from hex digits
    embedded in a stable `zz_` label. All eight marker-wins anomalies are accepted and
    tested; no symbol is renamed, excluded, or re-addressed on that basis.
13. **The most-repeated methodological warning in the archive**, from the author of the
    overnight handoff: *"Every conclusion above that survived was measured. Every one I
    reasoned to first was wrong."* Named instances: the arena "1% mismatch" (endianness),
    "10 newly-permitted symbols" (actually 2 — the unit's own exports had not been
    subtracted), the total-stall framing of the ABI gate (window-scoped, not terminal), and
    the ABI amendment itself, which evidence narrowed three separate times.

---

## 9. Release-blocking exit criteria

Do not call this pipeline playable, green, or safe to push until the five Critical
acceptance tests are mandatory and passing. The first corrected live transition must show:
assembly, browser and oracle pass on an exact digest **before** one artifact push; no
unresolved non-SDK import; a real `/apps/game` call; consistent state, journal and registry;
and failure-before-push for the preserved `zz_00076d0_` fixture.

The RCA's own acceptance list, still the right shape for the ABI seam: owner-catalog
resolution with no oracle-tier claim; ambiguous-owner fail-closed; the c0018 regression
reaching link and smoke with canonical `void zz_00f0104_(int,uint,uint)` while the binding
stays `e96ef433…` and **zero LLM calls** are made; the c0035 regression with one canonical
16-argument prototype, binding `04243bba…`, no targeted or diagnosis call; precise
attribution naming 2 of 5 objects; composition-retry isolation (an unrelated
knowledge-registry bump must **not** reopen; an owner-ABI or assembly-implementation change
must); no false settlement; the behaviour boundary held; the full OGhidra safety suite
passing from a `D:`-backed temp directory; and live proof after a reviewed resume with
`git ls-remote` verification of both remote tips.
