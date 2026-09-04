---
title: Verified Port Artifacts
---

# Verified port artifacts

A port moves through four distinct claims. Nothing may skip a step, and the word for each
step is load-bearing:

1. **Compiled** — source and imports are structurally valid, and for a wasm unit it links.
   This says **nothing** about behavior.
2. **Oracle-verified** — behavior matches an independent, evidence-bound check.
3. **Integrated** — production code selects the verified implementation.
4. **Playable** — a browser acceptance route exercises the intended game state.

Three pipelines produce port artifacts. They use different tooling and are at different
maturities.

## A. Matching decompilation (the current port route, since 2026-09-04)

Write C, compile it with a PowerPC compiler, diff the compiled object against the retail
GameCube image until it is byte-identical. Chosen over the wasm-unit pipeline in §B because
it is the only route that produces real, compilable, byte-exact source instead of a
mechanical transliteration — see `docs/static-recompilation-spike.md` and
`docs/matching-decompilation-spike.md`.

### Standard

| Verdict | Proven | Not proven |
|---|---|---|
| `MATCH` | The compiled candidate is byte-identical to the retail object (relocated operands masked and symbol-checked) | Anything about run-time behavior. No console, no capture, no execution at all |
| `MATCH_UNVERIFIED` | Nothing — a **held, not-counted** result | Rests on a data relocation the oracle cannot symbol-check, so it would match any global; never recorded in `src-match/` |

**Never total a `MATCH` with any wasm-unit tier below or any GX standard** — none of them
observe compiled bytes against retail, and this standard observes nothing else. See
`docs/verification-status.md` §5.5.

<ClaimTrail
  :steps="[
    { label: 'Matched functions', value: '405', status: 'verified' },
    { label: 'Matched instructions (of 701,464)', value: '1,773 (0.2528%)', status: 'verified' },
    { label: 'Corpus instructions compiler-blocked', value: '87.2%', status: 'observed' }
  ]"
/>

::: warning Two honest discounts
118 of the 405 matches are a single `blr` (`void f(void) {}`) — 29% of the functions, 6.7%
of the instructions. No global accessor is in the corpus at all (see the `MATCH_UNVERIFIED`
row above). Report this work by instructions, never by function count.
:::

### Verifying

```bash
python src-match/verify.py --control     # re-proves all 405 + 3 negative controls
python src-match/verify.py --sweep       # which compiler build/flags each one discriminates
MWCC_RS=<path>/mwcc.exe python research/tools/matching-decomp/census.py --check
python research/tools/matching-decomp/loop.py run --class shape-shared --no-llm
```

Full detail: `docs/matching-decompilation-spike.md`, `docs/matching-loop.md`,
`docs/matching-compiler-census.md`, `research/tools/matching-decomp/TOOLCHAIN.md`,
`src-match/README.md`.

## B. The wasm-unit pipeline (superseded as the route, kept as history)

Decompiled ROM C is sliced into compilable units, made to compile against a shim seed,
linked to WebAssembly, and then — separately — verified against the real console. The
normative document is `docs/playable-port-design.md` (v5, PASS verdict; **superseded in
part 2026-09-04** — see its own status note). Its driver (`finish-port --drive`) is
**obsolete on the current route and must not be relaunched**; the results below are real
and `damage-core` is still live in production, but this is no longer where new port work
happens.

### Tiers

| Tier | Proven | Not proven |
|---|---|---|
| `compile_only` | Compiles and links | **Anything about behavior.** Inventory, not progress |
| `oracle_green` | Full corpus replays byte-exact against an independent oracle, per call | Coverage beyond the replayed corpus |
| `boundary_green` | For a nonterminating spine, every captured callee boundary and spine-owned write is byte-exact to the cut | The same as `oracle_green`; it never upgrades into one. Nothing outside the declared owned regions; callees are stubs replaying captured values |
| `transcript_green` | For an ordinary returning function, the identical out-of-unit call transcript (set, order, arguments) **and** the identical return value, over N recorded cases | **No write-set comparison.** Strictly weaker than `oracle_green`, never upgrades into one, and is a per-**function** artifact rather than a unit tier |

`boundary_green` was first reached on 2026-08-30 by `run_main_game_loop` (274/274 calls,
`research/decomp/data/oracle-results/spine-run-main-game-loop.boundary.json`). The driver
still cannot record either weaker tier in unit state — both are per-artifact standards.

::: tip How much of the ROM can ever be verified
**652 of 10,954 functions (6.0 %)** can carry an `oracle_green` write-comparison spec at
all; **8,197 (74.8 %)** are reachable by `transcript_green`; **2,105 (19.2 %)** by neither.
Units with full export coverage: **378 of 1,396 (27.1 %)**. Those are *eligibility*
ceilings, not results. The measurement is
`research/decomp/data/verification-tier-survey.json` and the honest reading of it is
`docs/verification-status.md`.
:::

::: warning A green build is not a working port
`auto-c0035-002` compiles, links, and passed an N=5 assembly gate. Replayed against its
reference it is byte-exact on 6,250 of 20,000 cases. By design a FAIL flags
`oracle_divergent` and changes no tier, so it is *still recorded as a green `compile_only`
unit*. Read the tier, never the colour.
:::

### Verifying a unit

Replay an existing corpus (no emulator needed):

```bash
node research/decomp/oracle-harness/run-unit.mjs --unit <name>
node research/decomp/oracle-harness/run-spine.mjs --capture <capture.jsonl>
node research/decomp/oracle-harness/run-transcript.mjs --help
```

Capture a fresh corpus from the real game (needs a lawfully obtained disc and the bundled
Dolphin with its GDB stub):

```bash
python research/tools/dolphin-trace/capture_oracle.py launch --save-state <state.sav> --wait 90
python research/tools/dolphin-trace/capture_oracle.py capture \
  --plan research/tools/dolphin-trace/plans/<unit>.<fn>.json --n 120 --out <out.jsonl>
python research/tools/dolphin-trace/capture_oracle.py stop
```

For a function with no capturable write set, capture the callee-boundary transcript
instead (`research/tools/dolphin-trace/capture_transcript.py`). It refuses a function that
would produce an empty transcript rather than emitting a corpus that can only pass
vacuously.

The driver verbs (`verify-unit`, `verify-sweep`, `reverify-unit`, `assembly-gate`,
`settle-unit`, …) live in the **OGhidra** checkout, which is not vendored into this
repository. The root `README.md` lists them with their exact invocation.

### When a unit is proven wrong

The fault may be in the decompilation, not the port.
`research/decomp/corpus-correction-loop.md` is the sanctioned path: correct
`research/decomp/ghidra-export/chunk_NNNN.c` in place with a provenance comment, revoke the
verdict **through the journal**, and let the driver rebuild the unit from corrected source.
`unit.c` is regenerated output; the chunk is the source of truth.

### Relinking a verified unit

A threads-target relink changes module bytes, so `docs/threads-relink-reverify.md` suspends
the unit's verified status until its full corpus replays byte-equal against the relinked
module. A compile-only threads build is inventory, not progress.

## C. The OGhidra artifact importer

The earlier single-function path, still used and still tested. Use the checked-in fixture to
exercise the deterministic importer without private Ghidra state or a local model:

```bash
pnpm test:oghidra-port
pnpm import:oghidra-port --artifact scripts/fixtures/oghidra-eagle-jet-artifact.json
```

The test must exit zero. The import command writes a generated candidate, report, and
automatic verification record; review `git status` and retain only intentional evidence. A
fallback exits `2` and is **not** a promotion.

## Rules that hold for all three

- Never hand-edit autonomous queue verdicts. Every settle, revoke, or carry goes through a
  journal-emitting code path; the state file and the event log have already disagreed once
  because someone edited state directly.
- Never treat compile-only staging as integration.
- Report the command, its exit status, and the assertions it checked. "Build succeeded" is
  not evidence that a route is playable or that recovered mechanics are exact.
