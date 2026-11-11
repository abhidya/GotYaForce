#!/usr/bin/env node
// Cross-package integration fixture is outside the game's production rootDir.
import { execFileSync } from "node:child_process";
import { createRequire } from "node:module";
import { fileURLToPath, pathToFileURL } from "node:url";
import path from "node:path";
const root = fileURLToPath(new URL("../", import.meta.url));
const gameRequire = createRequire(new URL("../apps/game/package.json", import.meta.url));
const { build } = createRequire(gameRequire.resolve("vite"))("esbuild");
const outfile = path.join(root, ".tmp/battle-scene-size-selfcheck.mjs");
await build({ absWorkingDir: root, entryPoints: ["scripts/battle-scene-size.selfcheck.ts"],
  bundle: true, platform: "node", format: "esm", outfile,
  define: { "import.meta.env.BASE_URL": '"/"' },
  plugins: process.env.SIZE_TEST_BASE_REF ? [{
    name: "historical-size-wiring",
    setup(builder) {
      builder.onLoad({ filter: /[/\\](bridge|battleScene)\.ts$/ }, ({ path: filename }) => ({
        contents: execFileSync("git", ["show", `${process.env.SIZE_TEST_BASE_REF}:${path.relative(root, filename)}`], { cwd: root, encoding: "utf8" }),
        loader: "ts", resolveDir: path.dirname(filename),
      }));
    },
  }] : [],
});
const { runBattleSceneSizeSelfcheck } = await import(pathToFileURL(outfile).href);
await runBattleSceneSizeSelfcheck();
