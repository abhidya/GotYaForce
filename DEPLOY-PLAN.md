# Deploy plan — Gotcha Force web (Challenge mode, 1–4P online)

## Architecture (the key constraint)
Vercel serverless does NOT host a persistent WebSocket server. So we split:

| Piece | Host | How |
|---|---|---|
| **Client** (Vite/three.js static SPA) | **Vercel** | `vite build` → static `dist/`, served from CDN |
| **Netcode** (`server.mjs`, `ws`) | **Separate WS-friendly host** | Render / Railway / Fly.io free tier (persistent Node + WS) |

Client connects to the WS host via a build-time env var **`VITE_WS_URL`** (falls back to `ws://localhost:5174` in dev). The netcode-wave client change must read `import.meta.env.VITE_WS_URL`.

(Alternative considered: **PartyKit** — Cloudflare Durable Objects, purpose-built for multiplayer; deploy `server.mjs` logic as a PartyKit room. Cleanest single-vendor realtime if we don't want a second host. Decide at Wave 3.)

## Vercel build for the pnpm monorepo
Fresh clone has no `packages/*/dist` (gitignored). Vercel build must build the workspace packages first, then the app:
- **Install:** `pnpm install` (or npm) at repo root.
- **Build:** build `@gf/physics`→`@gf/combat`→`@gf/missions` (tsc) then `vite build` in `apps/game`.
- **Output dir:** `apps/game/dist`.

`vercel.json` (root) — set `buildCommand`, `outputDirectory`, `installCommand`. (Created in Wave 4 once the local `vite build` is green.)

Decision pending Wave 2/3: either (a) commit the package `dist/` (user prefers assets-in-repo, simplest for Vercel), or (b) build packages in the Vercel build command. Lean toward a root build script `scripts/build-web.mjs` that does packages→app, referenced by `vercel.json`.

## Asset size note
The model library + UI assets (`apps/game/public/`) are large (tens of MB of glTF/PNG/anim JSON). Fine for Vercel static hosting, but watch the deployment size limit; if needed, lazy-load borg models on demand (already the pattern) and consider trimming to the Challenge-relevant borg set for the first deploy.

## Wave-4 steps (after local play works)
1. `vite build` locally green (fix any prod-only issues: base path, asset URLs).
2. Pick WS host (Render/Railway/PartyKit); deploy `server.mjs`; get its `wss://` URL.
3. Set `VITE_WS_URL` to that URL; `vercel deploy` (or the Vercel MCP) the client.
4. Smoke test: load the Vercel URL, run a Challenge battle solo, then a 2-tab co-op session against the deployed WS host. Confirm before declaring done.
