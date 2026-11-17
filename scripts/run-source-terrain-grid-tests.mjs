#!/usr/bin/env node
// Execute the strict source-grid contract against current source, not stale dist.
import { createRequire } from 'node:module';
import path from 'node:path';
import { fileURLToPath } from 'node:url';

const root = path.resolve(path.dirname(fileURLToPath(import.meta.url)), '..');
const require = createRequire(path.join(root, 'packages/combat/package.json'));
const { build } = require('esbuild');
const result = await build({
  absWorkingDir: root,
  stdin: {
    contents: "import {runSourceTerrainGridSelfTest} from './packages/formats/src/source-terrain-grid.selftest.ts'; runSourceTerrainGridSelfTest(); console.log('[source-terrain-grid] PASS: strict source-owned layer/list/record contracts');",
    resolveDir: root,
    sourcefile: 'source-terrain-grid-selfcheck-entry.mjs',
  },
  bundle: true,
  platform: 'node',
  format: 'esm',
  write: false,
  logLevel: 'warning',
});
await import(`data:text/javascript;base64,${Buffer.from(result.outputFiles[0].text).toString('base64')}`);
