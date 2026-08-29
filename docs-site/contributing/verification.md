---
title: Verification
---

# Verification

Run the narrowest check that proves the change, then the shared gate before a pull request.

## Focused checks

| Change | Focused command |
| --- | --- |
| Combat lifecycle | `pnpm --filter @gf/combat test:lifecycle` |
| Game TypeScript | `pnpm --filter game typecheck` |
| ROM systems | `pnpm selfcheck:rom` |
| Challenge flow | `pnpm selfcheck:1p` · `pnpm selfcheck:challenge-stages` |
| HUD | `pnpm selfcheck:hud` |
| Family action tables | `pnpm audit:family-state-machines` |
| OGhidra artifact importer | `pnpm test:oghidra-port` |
| Oracle-harness evidence | `pnpm test:oracle` |
| Browser route | `pnpm smoke:browser` |
| Atlas pages and internal links | `pnpm verify:docs` |

## Browser smoke gates

`pnpm smoke:browser` drives the real playable route in headless Chrome. It asserts battle
actors are actually playing animation clips (the guard added after the 2026-08 animation
freeze) and, in its final phase, that `window.crossOriginIsolated === true` in both serving
modes.

```bash
pnpm smoke:browser                                              # playable route + animation liveness + COI
GF_SMOKE_ROM_HIT=1 pnpm smoke:browser                           # + the ROM wasm damage core must be LIVE
GF_SMOKE_ROMWASM=threads GF_SMOKE_ROM_HIT=1 pnpm smoke:browser  # + the shared-memory relink under COI
pnpm smoke:rom-runtime                                          # @gf/rom-runtime self-test phase
```

## Shared gate

```bash
pnpm verify:contributor
pnpm test:oracle
pnpm verify:docs
git status --short
```

This is what CI runs. `verify:contributor` chains repo-policy tests, workspace typecheck, the
browser POC gate, combat lifecycle tests, the importer test, and a production game build.
`verify:docs` regenerates atlas data and lets VitePress reject broken internal links; CI then
fails if the regenerated copies under `docs-site/public/chunks/` differ from what is
committed.

## Reporting

Report the command, its exit status, and the relevant assertions. "Build succeeded" is not
evidence that a route is playable or that recovered mechanics are exact — and for a wasm port
unit, a green build is not evidence of anything at all beyond linkage. See
[verified ports](./porting) for the tier vocabulary.
