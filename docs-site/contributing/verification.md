---
title: Verification
---

# Verification

Run the narrowest check that proves the change, then the shared gate before a
pull request.

| Change | Focused command |
| --- | --- |
| Combat lifecycle | `pnpm --filter @gf/combat test:lifecycle` |
| Game TypeScript | `pnpm --filter game typecheck` |
| OGhidra artifact importer | `pnpm test:oghidra-port` |
| Browser route | `pnpm smoke:browser` |
| Atlas pages and internal links | `pnpm verify:docs` |

Shared gate:

```bash
pnpm verify:contributor
pnpm verify:docs
git status --short
```

Report the command, exit status, and relevant assertions. “Build succeeded” is
not evidence that a route is playable or that recovered mechanics are exact.
