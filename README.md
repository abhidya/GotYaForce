# gotcha-force-web

A browser recreation of the GameCube game **Gotcha Force** (ガチャフォース), targeting
region **GG4E / NTSC-U** first. TypeScript + Vite + three.js monorepo.

## Start here

Read **[`research/PHASE0_RESEARCH.md`](research/PHASE0_RESEARCH.md)** first. It is the
Phase-0 technical research and design plan: format table, tool matrix, asset-recovery
plan, gameplay-systems RE plan, repository structure (section 15), and the
browser-recreation architecture (section 10) this scaffold implements.

Key finding from the research: **~70% of the asset pipeline is plumbing over existing
tools; the one unsolved blocker is the 3D model/skeleton/animation format** (the
`_mdl.arc` "HSD Files" container and the `chd/dpk/tsb/txg` family). That parser is the
project's critical path — see `packages/formats/src/mdl-arc.ts`.

## Layout

- `apps/game/` — Vite + TypeScript browser app (three.js renderer).
- `packages/*` — engine packages (`core`, `assets`, `formats`, `render`, `physics`,
  `combat`, `ai`, `missions`, `ui`, `audio`, `save`, `tools`, `test-fixtures`).
- `scripts/*` — driver scripts that orchestrate the existing Python tools
  (extract → convert → manifest).
- `research/` — Phase-0 research + transcribed specs (owned separately).

## Building

**Node.js (>= 20) and pnpm must be installed** — they are not assumed present on the
authoring machine, and nothing here has been `install`ed. Once Node is available:

```sh
pnpm install
pnpm --filter game dev
```

Other scripts: `pnpm build`, `pnpm typecheck`, `pnpm extract|convert|manifest`.

## Disc data

The Gotcha Force disc image is **user-supplied and never committed**. Place your own
dump under `user-data/` (gitignored). Per-region hashes/FST/magic maps go in
`research/disc/<REGION>/` (also gitignored). Generate all hashes yourself — the
research doc fabricates none.
