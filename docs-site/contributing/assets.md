---
title: Asset Workflows
---

# Asset workflows

Asset work begins with a lawfully obtained, user-supplied dump under ignored
`user-data/`. Never commit disc images, raw extracted archives, proprietary SDK
files, or local tool installations.

Common deterministic steps:

```bash
pnpm extract
pnpm sync:assets
pnpm runtime:assets
```

Each script names its required input when it is missing. Before committing,
record the source region and input hash, command, tool revision, output
manifest, and validation result. Commit reviewable derived assets only when
their provenance and repository policy allow redistribution.

Atlas text/data work can skip the large model copy:

```bash
GF_ATLAS_SKIP_MODELS=1 pnpm verify:docs
```

On PowerShell use `$env:GF_ATLAS_SKIP_MODELS='1'` for that process, then remove
the variable when finished.
