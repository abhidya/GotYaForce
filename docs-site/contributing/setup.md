---
title: Clean Setup
---

# Clean setup

## Requirements

- Git
- Node.js 20 or newer
- Corepack and pnpm 9
- A modern WebGL-capable browser for interactive testing

## Install and verify

```bash
git clone https://github.com/abhidya/GotYaForce.git
cd GotYaForce
corepack enable
pnpm install --frozen-lockfile
pnpm verify:contributor
```

Success means the workspace type-check, combat lifecycle tests, importer tests,
and production game build all exit zero. The install must not require a disc
image, private environment variables, or a local inference server.

## Run locally

```bash
pnpm dev
```

Open the URL printed by Vite. For atlas work, run `pnpm atlas:dev` instead.
