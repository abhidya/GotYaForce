# Deploy — how GotYaForce is published

> Rewritten 2026-08-29. The previous version of this file planned a Vercel + external
> WebSocket-host split that was never built: there is no `vercel.json` in the repo, no
> `VITE_WS_URL` reference in any source file, and no deployed WebSocket host. The project
> ships from **GitHub Pages** instead. That plan is recorded at the bottom as history.

## What is actually deployed

One GitHub Pages site, built and published by
[`.github/workflows/deploy-pages.yml`](.github/workflows/deploy-pages.yml):

| URL | Content | Source |
| --- | --- | --- |
| `https://abhidya.github.io/GotYaForce/` | VitePress research atlas | `docs-site/` |
| `https://abhidya.github.io/GotYaForce/game/` | The playable browser game | `apps/game/` |

The workflow runs on every push to `main` that touches `docs-site/**`, `research/**`,
`apps/game/**`, or the workflow itself, and on `workflow_dispatch`. It:

1. `pnpm install --frozen-lockfile`
2. `node docs-site/scripts/curate-data.mjs` — regenerates `docs-site/.vitepress/data/*.json`
   from `research/`
3. `pnpm build` in `docs-site` with `GH_PAGES_BASE=/GotYaForce/`
4. `pnpm --filter game build`
5. Stages the atlas at the artifact root and the game under `game/`, drops a `.nojekyll`
   in both, and uploads via `actions/upload-pages-artifact` → `actions/deploy-pages`

Nothing is committed back to the repo by the deploy; `dist/` stays gitignored.

## The two constraints that shape the build

### 1. Subpath base

The game is served from `/GotYaForce/game/`, not from a domain root.
`apps/game/vite.config.ts` sets `base: "/GotYaForce/game/"` for `command === "build"` and
keeps `/` for dev. Any runtime `fetch()` or dynamically constructed asset URL must go
through the app's `publicUrl` helper rather than an absolute `/...` path — an absolute path
resolves to the domain root on Pages and 404s.

The atlas has the same shape one level up: `docs-site/.vitepress/config.ts` reads
`GH_PAGES_BASE` (default `/GotYaForce/`).

### 2. Cross-origin isolation

`SharedArrayBuffer`, shared `WebAssembly.Memory`, and `Atomics.wait` — which the
threads-target ROM wasm build needs — are gated on `crossOriginIsolated === true`, which
browsers grant only for documents served with `Cross-Origin-Opener-Policy: same-origin` and
`Cross-Origin-Embedder-Policy: require-corp`.

- **Dev and `vite preview`:** the headers are sent directly by the Vite server
  (`server.headers` / `preview.headers` in `apps/game/vite.config.ts`).
- **Production:** GitHub Pages cannot set response headers, so the app registers the
  vendored `apps/game/public/coi-serviceworker.js` first thing in `index.html`; the service
  worker re-serves the document with the headers and reloads once. Every asset the app
  loads is same-origin, so `require-corp` needs no `crossorigin`/CORP annotations.

`scripts/smoke-browser-game.mjs` has a COI phase that asserts
`window.crossOriginIsolated === true` in both serving modes.

## Verifying a deploy before pushing

```bash
pnpm --filter game build          # production build with the Pages base
pnpm --filter game preview        # serves dist/ with the COI headers
pnpm smoke:browser                # headless playable-route gate
pnpm verify:docs                  # atlas build; VitePress fails on broken internal links
```

`pnpm smoke:browser` drives the real route in headless Chrome. Useful switches:

```bash
GF_SMOKE_ROM_HIT=1 pnpm smoke:browser                        # assert the ROM wasm damage core is live
GF_SMOKE_ROMWASM=threads GF_SMOKE_ROM_HIT=1 pnpm smoke:browser  # the shared-memory relink under COI
```

## Asset size

`apps/game/public/` (models, stages, UI, audio, fx, ROM wasm) is tens of megabytes.
Borg models are already lazy-loaded on demand. If the Pages artifact limit becomes a
problem, trim to the Challenge-relevant Borg set first — the loader path already supports
a partial library through the model-library manifest.

## Multiplayer — not deployed

`apps/game/server.mjs` is a standalone `ws` room server (`pnpm --filter game dev:server`,
default port 5174). It is a **prototype that nothing currently connects to**: no file under
`apps/game/src` opens a `WebSocket`, and no `VITE_WS_URL` is read anywhere. Treat online
play as unimplemented, not as configuration that is merely missing a host.

If it is revived, the constraint that motivated the original plan still holds — static
hosts (Pages, Vercel's static output) cannot hold a persistent WebSocket, so the room
server needs its own always-on host (Render / Railway / Fly.io / PartyKit) and the client
needs a build-time endpoint variable.

---

## History: the superseded Vercel plan (2026-06-30)

The original plan split the Vite SPA onto Vercel and `server.mjs` onto a WebSocket-friendly
host, wiring the two with a build-time `VITE_WS_URL`, and left open whether to commit
`packages/*/dist` or build the workspace in the Vercel build command. None of it shipped:
GitHub Pages, already in use for the research atlas, absorbed the game as a subpath and the
netcode wave never landed. Recorded here so the decision is not silently re-made.
