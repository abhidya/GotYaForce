#!/usr/bin/env node
import {createRequire} from 'node:module';
import {fileURLToPath,pathToFileURL} from 'node:url';
import path from 'node:path';
const root=fileURLToPath(new URL('../',import.meta.url));
const requireGame=createRequire(new URL('../apps/game/package.json',import.meta.url));
const {build}=createRequire(requireGame.resolve('vite'))('esbuild');
const outfile=path.join(root,'.tmp/battle-scene-teleport-selfcheck.mjs');
await build({absWorkingDir:root,entryPoints:['scripts/battle-scene-teleport.selfcheck.ts'],bundle:true,platform:'node',format:'esm',outfile,
 define:{'import.meta.env.BASE_URL':'"/"'}});
await (await import(pathToFileURL(outfile).href)).runTeleportSceneSelfcheck();
