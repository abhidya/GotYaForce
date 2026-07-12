# Gotcha Force Research Atlas

Static site (VitePress + Vue) deployed to GitHub Pages at
**https://abhidya.github.io/GotYaForce/**.

All data is curated from `research/` source files — no hand-written JSON.

## Local dev

```bash
cd docs-site
pnpm install
node ../docs-site/scripts/curate-data.mjs   # regenerate data from research/
pnpm dev
```

The curate step also copies extracted Borg model and animation assets from
`apps/game/public/models` into `docs-site/public/models` so Borg detail pages can
render the real GLB and baked animation clips. For text/data-only local work, run
with `GF_ATLAS_SKIP_MODELS=1` to skip that heavier asset copy.

## Build

```bash
node scripts/curate-data.mjs   # reads research/, writes .vitepress/data/*.json
pnpm build                     # outputs .vitepress/dist/
```

## Data flow

```
research/**/*.json  ──┐
research/**/*.md    ──┼──► scripts/curate-data.mjs ──► .vitepress/data/*.json
research/**/*.csv   ──┘                                       │
                                                              ▼
                                          .vitepress/theme/components/*.vue
                                                              │
                                                              ▼
                                                       VitePress build
                                                              │
                                                              ▼
                                          .vitepress/dist/  (deployed)
```

Never edit `.vitepress/data/*.json` by hand. Edit the curate script or the
upstream `research/` files, then re-run the script.

## GitHub Pages

Push to `main` triggers `.github/workflows/deploy-pages.yml`, which:

1. Installs docs-site deps
2. Runs `curate-data.mjs` against the checked-out `research/`
3. Builds VitePress with `GH_PAGES_BASE=/GotYaForce/`
4. Uploads `dist/` and deploys via `actions/deploy-pages`

## Adding a new page

1. Drop a `.md` file under the appropriate section folder.
2. Wire it into `.vitepress/config.ts` nav and sidebar.
3. Use the global components: `StatusBadge`, `MetricCard`, `ProgressMatrix`,
   `EvidenceCard`, `AtlasTable`, `ClaimTrail`, `HeroDashboard`.

## Adding a new data source

Edit `scripts/curate-data.mjs`. Read from `research/`, emit JSON to
`.vitepress/data/`. The build picks it up automatically.
