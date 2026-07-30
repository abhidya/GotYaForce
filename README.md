<div align="center">
  <img src="docs-site/public/favicon.svg" width="88" height="88" alt="GotYaForce logo">

  <h1>GotYaForce</h1>

  <p>
    An evidence-first browser recreation of <strong>Gotcha Force</strong>,
    built from the GameCube original one system at a time.
  </p>

  <p>
    <a href="https://abhidya.github.io/GotYaForce/">Research Atlas</a>
    ·
    <a href="research/decomp/PORT-1TO1-STATUS.md">Port Status</a>
    ·
    <a href="research/PHASE0_RESEARCH.md">Technical Research</a>
  </p>

  <p>
    <img src="https://img.shields.io/badge/status-work_in_progress-f59e0b" alt="Status: work in progress">
    <img src="https://img.shields.io/badge/TypeScript-5.6-3178c6?logo=typescript&logoColor=white" alt="TypeScript 5.6">
    <img src="https://img.shields.io/badge/three.js-r169-black?logo=threedotjs" alt="three.js r169">
    <img src="https://img.shields.io/badge/target-GG4E_%2F_NTSC--U-ff6fb1" alt="Target: GG4E / NTSC-U">
  </p>
</div>

> [!IMPORTANT]
> GotYaForce is a playable research port, not a finished replacement for the original game.
> Challenge mode runs from menus through results, but many Borg-specific actions still use
> partial or generic behavior while their ROM state machines are being transcribed.

## What is working

- Start-to-finish 1-player Challenge flow with force building, battles, results, and Gotcha Box drops
- Real models for all 208 Borgs; 185 currently have animated bakes
- Visual geometry and collision for all 40 exported stage variants
- ROM-derived damage, ammo, knockback, targeting, scoring, drop, and action-stream systems
- Real UI, music, voice, combat-audio, lighting, and effect assets where attribution is verified
- A searchable research atlas covering functions, data tables, Borgs, stages, mechanics, and evidence

### Port snapshot

| Area | Current state |
| --- | --- |
| Challenge mode | Playable end to end; approximately 85% ROM-derived |
| Borg models | 208 / 208 static, 185 / 208 animated |
| Stages | 40 / 40 visual and collision exports |
| HUD | Approximately 90%; Power Burst meter remains trace-blocked |
| Family action state machines | 20 ported, 234 partial, 71 missing across 325 action slots |
| Family coverage audit | 119 constructor families, 208 roster entries, 0 structural errors |

These numbers describe evidence coverage, not a single overall completion percentage. The
canonical tracker is [`research/decomp/PORT-1TO1-STATUS.md`](research/decomp/PORT-1TO1-STATUS.md);
the generated family audit lives in
[`research/decomp/family-state-machine-coverage.md`](research/decomp/family-state-machine-coverage.md).

## Quick start

### Requirements

- Node.js 20 or newer
- pnpm 9
- A modern browser with WebGL support

```bash
git clone https://github.com/abhidya/GotYaForce.git
cd GotYaForce
corepack enable
pnpm install --frozen-lockfile
pnpm dev
```

Open the local URL printed by Vite, normally `http://localhost:5173`.

### Controls

| Action | Keyboard | Standard gamepad |
| --- | --- | --- |
| Move | `WASD` or arrow keys | Left stick |
| Jump / A | `Space` or `J` | A |
| Attack / B | `K` or `B` | B |
| Special / X | `L` or `X` | X |
| Hyper / Y | `Y` or `H` | Y |
| Dash | `Shift` | Stick-snap movement |
| Next / previous target | `R` or `Tab` / `Q` | Right / left trigger |
| Ally lock | `Z` | Left shoulder |

## How the port is built

GotYaForce is not a clean-room reinterpretation of a wiki description. Mechanics are promoted
to ROM-derived only when they can be tied back to decompiled PowerPC code, DOL bytes, decoded
tables, extracted assets, or controlled Dolphin traces.

```text
boot.dol + disc assets + traces
              │
              ▼
   decompilation and evidence maps
              │
              ▼
  deterministic extract/convert scripts
              │
              ▼
 TypeScript runtime + focused self-checks
              │
              ▼
        browser recreation
```

The actor runtime mirrors the original cue dispatch, action tables, phase handlers, stream VM,
and physics integration. Families can land independently; Borgs without a completed family port
continue through the generic combat path instead of being falsely labeled exact. See the
[`ROM porting guide`](packages/combat/src/rom/PORTING.md) for the implementation model.

### Local-LLM port artifacts

The research checkout includes an evidence-first OGhidra exporter and a deterministic
GotYaForce importer. OGhidra collects the selected function, disassembly, direct callees,
cross-references, and raw constants; Pydantic validates the model output before it can reach
TypeScript.

```powershell
# From research/tools/OGhidra, with GhidraMCP and the configured local model running
.\.venv\Scripts\python.exe main.py export-port `
  --address 0x8012b458 `
  --ghidra-backend http `
  --output port_artifacts/8012b458.port.json

# From the GotYaForce root
pnpm import:oghidra-port `
  --artifact research/decomp/generated/8012b458.port.json

# Rebuild, compile, and compare the generated function with the reference
pnpm verify:oghidra-port
```

An unverified artifact, missing fact, or unresolved dependency generates an isolated function
that returns `false`; the existing generic combat path remains authoritative. A verified import
still requires human review before production registration. Raw model responses, evidence,
prompts, and validation reports are retained beside each artifact. The importer exits with code
`2` when it deliberately emits this fallback, making the blocked result visible to CI.

The current Eagle Jet proof of concept runs Qwen 3.6 35B-A3B against live Ghidra evidence for
`0x8012b458`. Its retained claims pass 61/61 deterministic checks; one incorrect model claim is
recorded and pruned, all 12 importer facts are recovered from authoritative evidence, and the
generated function matches the reference across five runtime scenarios. See the
[`artifact`](research/decomp/generated/8012b458.port.json),
[`validation report`](research/decomp/generated/8012b458.port.validation.json),
[`import report`](research/decomp/generated/8012b458-import-report.md), and
[`generated candidate`](packages/combat/src/generated/oghidra/fn_8012b458.generated.ts).

## Repository map

| Path | Purpose |
| --- | --- |
| [`apps/game`](apps/game) | Vite, TypeScript, and three.js browser game |
| [`packages/combat`](packages/combat) | Battle simulation and ROM-faithful actor runtime |
| [`packages/missions`](packages/missions) | Challenge flow, scoring, stages, and Gotcha Box logic |
| [`packages/assets`](packages/assets) | Borg catalogs and generated asset metadata |
| [`packages/render`](packages/render) | three.js loading and rendering helpers |
| [`scripts`](scripts) | Extraction, conversion, generation, audit, and self-check tools |
| [`research`](research) | Decompilation evidence, format specs, traces, and port trackers |
| [`docs-site`](docs-site) | VitePress research atlas |

## Useful commands

```bash
# Game
pnpm dev
pnpm build
pnpm typecheck

# High-value regression checks
pnpm selfcheck:game-session
pnpm selfcheck:1p
pnpm selfcheck:challenge-stages
pnpm selfcheck:rom
pnpm audit:family-state-machines

# Research atlas
pnpm atlas:dev
pnpm atlas:build

# OGhidra artifact importer
pnpm test:oghidra-port
pnpm import:oghidra-port --artifact <artifact.json>
pnpm verify:oghidra-port
```

The family audit defaults to structural validation. It is expected to report partial and missing
slots until the port is complete; strict completeness is a finish-line gate.

## Disc data and generated assets

The repository targets the US release (`GG4E`, NTSC-U). A disc image is never required for the
normal browser-development loop and must not be committed. Extraction and regeneration workflows
expect a legally obtained, user-supplied dump under `user-data/`, which is gitignored.

The HSD asset pipeline runs offline:

```text
GameCube archives → HSDRaw / project scripts → Collada or GLB + textures → browser assets
```

There is intentionally no runtime TypeScript parser for wrapped Borg `.arc` model archives.
Format notes and provenance are documented in
[`research/format-specs/arc-hsd-format.md`](research/format-specs/arc-hsd-format.md).

## Contributing

The highest-value contributions are small and evidence-backed:

1. Pick one family and one action index from the
   [coverage audit](research/decomp/family-state-machine-coverage.md).
2. Trace its constructor, dispatcher, variant table, phase functions, helpers, and constants.
3. Preserve unresolved host behavior as an explicit blocker.
4. Add boundary assertions for every transition.
5. Run the ROM self-check and family audit before opening a pull request.

Please do not replace unknown behavior with plausible constants and call it 1:1. In this project,
an honest `TUNED`, `PARTIAL`, or `BLOCKED` label is better than an unsupported exactness claim.

## Legal

Gotcha Force, its characters, names, and original assets are property of their respective
rightsholders. This is an unofficial preservation and reverse-engineering project and is not
affiliated with or endorsed by Capcom or Nintendo. No disc image, encryption keys, or proprietary
SDK is distributed by this project.
