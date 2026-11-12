#!/usr/bin/env node
import { createRequire } from "node:module";
import { fileURLToPath, pathToFileURL } from "node:url";
import path from "node:path";
const root = fileURLToPath(new URL("../", import.meta.url));
const gameRequire = createRequire(new URL("../apps/game/package.json", import.meta.url));
const { build } = createRequire(gameRequire.resolve("vite"))("esbuild");
const outfile = path.join(root, ".tmp/battle-scene-source-animation-selfcheck.mjs");
await build({ absWorkingDir: root, entryPoints: ["apps/game/src/sim/battleScene.sourceAnimation.selfcheck.ts"],
  bundle: true, platform: "node", format: "esm", outfile,
  define: { "import.meta.env.BASE_URL": '"/"' },
});
const { runSourceAnimationPlayheadSelfcheck } = await import(pathToFileURL(outfile).href);
await runSourceAnimationPlayheadSelfcheck();
