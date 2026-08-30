# Research data provenance and reproducibility

**Provenance.** Rescued 2026-08-29 from untracked session audits: the 2026-08-23 data
reproducibility sweep appended to `game-webapp-libraries-audit`, the 2026-08-21
`oracle-schema-fixture-audit`, and the 2026-08-23 overnight handoff.

**Status.** The oracle-registry schema gap is **FIXED**. The two non-reproducing data
files are **OPEN** and are owner decisions. Re-checked 2026-08-29.

---

## 1. The sweep

Every tracked generated data file under the combat/research trees names a source but only
**4 of 26 bind a source hash**. The other 22 name an input
(`user-data/GG4E/disc/sys/boot.dol`, afs_data members) without being bound to it. The
three files that do record `bootDolSha1` all agree with each other and with the local disc
(`91b32873d62ae25c0a9b08d665e1e8c19ae38a5f`).

To find out whether the unbound files were actually reproducible, all 17 runnable
generators were re-run and their output compared byte-for-byte against the committed file,
then the working tree was reverted and verified clean.

**15 of 17 reproduce.** Ten byte-identical, including `commandMoveTables.json` (3.5 MB,
"208/208 roster borgs exact"), `attackHitTables.json`, `meleeAnimKinds.json` (9.8 MB),
`damageFormula.json`, and `shotVariantKinds.json`. Five more differ only by a regeneration
`generatedAt` timestamp or by line endings.

**Two do not.** Both are real findings, and they fail in opposite directions.

---

## 2. `actionStreamTables.json` is STALE, not corrupt — OPEN

Regenerating produces materially different data: `joinHitStreams` goes **736 → 1839** and
`hitStream` flags flip, across **1104 changed lines** of a 2.5 MB file that drives live
combat stream behaviour.

**Root cause, settled by evidence.** `scripts/gen-action-stream-tables.mjs` does not read
only the DOL. It consumes two other *generated* files as inputs —
`commandMoveTables.json` and `meleeAnimKinds.json`. Its `hitStream` rule (line ~1875) is a
presence test against the second:

```js
melee.banks?.[leafOut.bank]?.groups?.[`g${group}`]?.[`s${seedSlot}`] !== undefined
```

Commit dates give the ordering, re-confirmed on 2026-08-29:

| File | Last commit | Date |
| --- | --- | --- |
| `packages/combat/src/data/actionStreamTables.json` | `ba65ef5c` | **2026-07-04** |
| `packages/combat/src/data/meleeAnimKinds.json` | `01e0cd8e` | **2026-07-12** |

Its input was last written **eight days later**, adding 561,584 lines against 32,655
deletions — an ~18× expansion of exactly the `banks[].groups[]` structure that rule probes.
More populated slots means more leaves where the lookup is no longer `undefined`, which is
precisely why `joinHitStreams` rises 736 → 1839.

**The committed file is stale with respect to its own declared input; the generator did not
regress.** Nobody re-ran the dependent generator after the input grew.

Refreshing it is still an owner call, because it rewrites 1104 lines of live combat data
and would change gameplay behaviour. But it is now an informed one rather than a guess.

**Structural fix required either way:** `meleeAnimKinds → actionStreamTables` needs a
**declared build order** so it cannot silently rot again.

---

## 3. `romAiParams.json` is AHEAD of its generator — OPEN

The opposite case. Regenerating **destroys** hand-curated content: **709 lines removed
against 209 added**, including the `aiHandlerDecode` evidence annotation — the
verifier-corrected OR for the `zz_0021db0_` attack gate.

Strongly suggests the committed file was hand-curated after generation, so its
`generatedBy` provenance is **not currently true**. Its generator is
`scripts/extract-rom-ai-params.py`; last data commit `b5fe248f` (2026-07-06).

Nothing was changed. Do not "fix" this by regenerating — that deletes reviewed evidence.
Either fold the curation back into the generator, or change the file's provenance field to
say it is curated and record what was curated.

---

## 4. Why this class of defect is invisible

For both files the recorded provenance does not describe the committed bytes, and **the
missing source-hash binding is exactly what conceals that.** A `generatedBy` string is not
provenance. Provenance is: the generator identity, the content hash of every input
(including generated inputs), and the content hash of the output.

The general rule the sweep argues for: preserve durable evidence as a small schema —
source revision/hash, tool revision, lawful input hash, command/config with secrets
removed, oracle cases/result, output hashes, and the product commit that consumes it.

### 4.1 The first file built to that rule — `verification-tier-survey.json` (2026-08-30)

The same defect class was found in a worse form: the **verification-tier ceiling** — the
numbers that decide what the port pipeline is even attempting — existed **only as the
stdout of `research/tools/OGhidra/tools/survey_plan_tiers.py`**, a script in the
unvendored tool checkout. They were transcribed into design documents by hand and were
neither diffable nor re-derivable from a clone.

Closed by `research/decomp/data/build_tier_survey.py` →
`research/decomp/data/verification-tier-survey.json`, which is the first generated file
here to satisfy §4's rule in full: it binds the sha256 of the oracle registry, a rolled
sha256 over all 80 decompiled-C chunk files the survey actually reads, and the sha256 of
each of the four classification-logic files in the tool checkout, plus that checkout's
commit. It also ships the missing half of the rule — a **`--check` mode** that re-derives
the survey and exits non-zero if the tree no longer produces the committed numbers, so
staleness is detectable rather than inferred. The reading of those numbers is
[`docs/verification-status.md`](../verification-status.md).

Status: **FIXED** for this file. The pattern is the one the two OPEN files above need.

---

## 5. Oracle registry schema — FIXED

The Phase-0 discovery registry `research/decomp/data/oracle-registry.json` (8.3 MB;
10,954 function records across 1,396 units; oracle buckets `133 differential_vs_ts`,
`319 state_diff`, `58 citations_no_family`, `886 trace_only`) originally had **no explicit
schema or version field at any level**. `meta` carried only `generated_by`, `inputs`, and
`conventions`. The audit's decision was blunt: do not bless `generated_by` or
field-presence inference as a schema — the format would remain inferred from field
presence, which is exactly what the assembly ABI spec's fail-closed contract prohibits.

**Confirmed fixed 2026-08-29:** the file now opens with `"oracle_registry_schema": 1`, and
`research/decomp/data/oracle_registry_schema.py` (37.5 KB) plus
`research/decomp/data/test_oracle_registry_schema.py` (24.6 KB) exist alongside the
builder.

The validation contract the audit specified, for reference when the adapter is extended —
for every owner it uses, validate: unique `name` among function records; string `unit` and
`chunk_file`; two positive ordered integer `line_range` values; string `return_type` and
list-of-string `params`; the source path remains under the approved decompile-corpus root;
the cited bytes contain exactly one direct definition of `name`; the parsed definition
prototype equals `return_type + name + params`; a stable double-read of registry bytes and
cited source bytes; and SHA-256 of the exact cited bytes recorded in the owner evidence.

A **related, still-open** gap: `build_unit_priority.py` reads `meta.generated_at`, which
the builder has never emitted, so `unit-priority.json` carries
`"source_generated_at": null`. The registry records neither its input digests nor a
generation timestamp, so a consumer cannot detect staleness from the schema alone.

**Do not confuse this file with the advisory knowledge registry**
(`research/decomp/generated/finish-game-port/knowledge-registry.json`, `registry_schema: 1`
plus a monotonic `version`). Different schema, different authority — see
[`port-pipeline-integrity.md`](port-pipeline-integrity.md).

---

## 6. Fixture policy for cross-repo test data — DECIDED

A live question when the assembly ABI work needed regression fixtures: may the byte-exact
GotYaForce candidate/artifact payloads be published inside the nested OGhidra repository?

**Decision: no, use synthetic public fixtures plus a private exact lane.** This is a
conservative repository-policy decision, not a legal conclusion. The evidence:

- OGhidra's code is under its LLNL license; that covers the OGhidra work, not a
  relicensing of third-party Gotcha Force-derived payloads.
- The GotYaForce README states original characters, names and assets belong to their
  rightsholders, and that no disc image, encryption keys, or proprietary SDK is
  distributed; it requires a legally obtained user-supplied disc dump.
- The clearest in-repo fixture policy (`packages/test-fixtures/README.md`) says fixtures
  are tiny, hand-built, synthetic, readable, and generator-reproducible, with no lifted
  game-disc bytes. Existing OGhidra port tests already follow it.
- **No inspected policy or notice affirmatively grants redistribution rights** for the
  exact candidate trees, and the GotYaForce root has no license file.

The shape: public synthetic fixtures reproduce the failure *mechanics* (a 3-argument and a
16-argument owner prototype, malformed/zero-owner/two-owner cases, a five-unit window in
which only two objects reference the contested symbol) and carry the historical
unit/window labels, source coordinates and expected canonical prototype as **RCA
metadata** — never asserting that the synthetic payload hash equals the historical
candidate hash. An opt-in private loader
(`OGHIDRA_ASSEMBLY_ABI_PRIVATE_FIXTURE_ROOT`) may claim reproduction of the historical
full-window hashes; absent the variable, public tests still run fully.

**A caveat that outlived the decision:** the two failed candidate payloads
(`e96ef43340ddd601613940fd3a7cd1aa2c778ffe1f5d43e64aeb41651ceaf4f4` for `auto-c0018-018`,
`04243bba39c02497077e668df7eadda68fd489427d9d67772166689cf3524352` for `auto-c0035-006`)
are **not present byte-exact anywhere in the tree**. Canonical state preserves their
directory hashes; the live staging directories hash differently. A private exact
regression therefore also needs an authoritative recovery source — the hashes alone cannot
recreate the payloads.
