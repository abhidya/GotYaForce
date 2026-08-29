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

Two pipelines produce port artifacts. They use different tooling and are at different
maturities.

## A. The wasm-unit pipeline (current frontier)

Decompiled ROM C is sliced into compilable units, made to compile against a shim seed,
linked to WebAssembly, and then — separately — verified against the real console. The
normative document is `docs/playable-port-design.md` (v5, PASS verdict).

### Tiers

| Tier | Proven | Not proven |
|---|---|---|
| `compile_only` | Compiles and links | **Anything about behavior.** Inventory, not progress |
| `oracle_green` | Full corpus replays byte-exact against an independent oracle, per call | Coverage beyond the replayed corpus |
| `boundary_green` | For a nonterminating spine, every captured callee boundary and spine-owned write is byte-exact to the cut | The same as `oracle_green`; it never upgrades into one |

`boundary_green` currently exists as design, the `run-spine.mjs` harness, and synthetic test
fixtures. No real spine capture exists and the driver cannot yet record the tier.

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
```

Capture a fresh corpus from the real game (needs a lawfully obtained disc and the bundled
Dolphin with its GDB stub):

```bash
python research/tools/dolphin-trace/capture_oracle.py launch --save-state <state.sav> --wait 90
python research/tools/dolphin-trace/capture_oracle.py capture \
  --plan research/tools/dolphin-trace/plans/<unit>.<fn>.json --n 120 --out <out.jsonl>
python research/tools/dolphin-trace/capture_oracle.py stop
```

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

## B. The OGhidra artifact importer

The earlier single-function path, still used and still tested. Use the checked-in fixture to
exercise the deterministic importer without private Ghidra state or a local model:

```bash
pnpm test:oghidra-port
pnpm import:oghidra-port --artifact scripts/fixtures/oghidra-eagle-jet-artifact.json
```

The test must exit zero. The import command writes a generated candidate, report, and
automatic verification record; review `git status` and retain only intentional evidence. A
fallback exits `2` and is **not** a promotion.

## Rules that hold for both

- Never hand-edit autonomous queue verdicts. Every settle, revoke, or carry goes through a
  journal-emitting code path; the state file and the event log have already disagreed once
  because someone edited state directly.
- Never treat compile-only staging as integration.
- Report the command, its exit status, and the assertions it checked. "Build succeeded" is
  not evidence that a route is playable or that recovered mechanics are exact.
