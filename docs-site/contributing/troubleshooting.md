---
title: Troubleshooting
---

# Troubleshooting a clean checkout

## Locked install fails

Confirm Node and pnpm match the repository contract:

```bash
node --version
pnpm --version
pnpm install --frozen-lockfile
```

Do not regenerate the lockfile merely to bypass an error. Report the first
failing package and platform.

## Atlas build cannot find models

For documentation-only work, skip the optional model copy:

```bash
GF_ATLAS_SKIP_MODELS=1 pnpm verify:docs
```

For a release build, regenerate/sync the model assets and run the full
`pnpm atlas:build` path.

## Browser smoke cannot launch Chrome

Run `pnpm --filter game build` first. The CDP smoke requires a locally
installed Chromium-compatible browser; this is separate from compile success.

## Generated files appear in Git

Run `git status --short --ignored=matching`, identify the owning generator,
and update a narrow ignore rule if the output is reproducible. Never recursively
delete `.tmp`, registered worktrees, live port state, or an unknown hidden
directory.
