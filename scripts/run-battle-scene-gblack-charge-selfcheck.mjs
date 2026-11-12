#!/usr/bin/env node
import {createRequire} from 'node:module';
import {fileURLToPath,pathToFileURL} from 'node:url';
import path from 'node:path';
const root=fileURLToPath(new URL('../',import.meta.url));
const gameRequire=createRequire(new URL('../apps/game/package.json',import.meta.url));
const {build}=createRequire(gameRequire.resolve('vite'))('esbuild');
const outfile=path.join(root,'.tmp/battle-scene-gblack-charge-selfcheck.mjs');
await build({absWorkingDir:root,entryPoints:['scripts/battle-scene-gblack-charge.selfcheck.ts'],bundle:true,
 platform:'node',format:'esm',outfile,define:{'import.meta.env.BASE_URL':'"/"'}});
const {runGBlackChargeSceneSelfcheck}=await import(pathToFileURL(outfile).href);
await runGBlackChargeSceneSelfcheck();
