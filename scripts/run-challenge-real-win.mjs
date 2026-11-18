#!/usr/bin/env node
// Integrates real app/session, mission VM and combat; opponents are defeated by
// test intervention, so this is not a player playthrough or visual validation.
import { createRequire } from 'node:module';
import { mkdtemp, rm } from 'node:fs/promises';
import { tmpdir } from 'node:os';
import path from 'node:path';
import { fileURLToPath, pathToFileURL } from 'node:url';
const root = path.resolve(path.dirname(fileURLToPath(import.meta.url)), '..');
const require = createRequire(path.join(root, 'packages/combat/scripts/run-lifecycle-tests.mjs'));
const { build } = require('esbuild');
const dir = await mkdtemp(path.join(tmpdir(), 'gf-challenge-win-'));
try {
 const outfile=path.join(dir,'test.mjs');
 await build({absWorkingDir:root,entryPoints:['scripts/challenge-real-win.selfcheck.ts'],outfile,bundle:true,platform:'node',format:'esm',
  alias:Object.fromEntries(['physics','render','combat','missions','assets','core','formats','rom-runtime','camera-math','audio'].map(n=>['@gf/'+n,path.join(root,'packages',n,'src/index.ts')]))});
 await import(pathToFileURL(outfile).href);
} finally { await rm(dir,{recursive:true,force:true}); }
