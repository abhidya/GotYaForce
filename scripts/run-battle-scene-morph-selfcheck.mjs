#!/usr/bin/env node
import { createRequire } from "node:module";
import { execFileSync } from "node:child_process";
import { fileURLToPath, pathToFileURL } from "node:url";
import path from "node:path";

const root = fileURLToPath(new URL("../", import.meta.url));
// Use the game's installed Vite/esbuild toolchain, not an undeclared global CLI.
const gameRequire = createRequire(new URL("../apps/game/package.json", import.meta.url));
const { build } = createRequire(gameRequire.resolve("vite"))("esbuild");
const sourcePath = "apps/game/src/sim/battleScene.ts";
const baseRef = process.env.ANIMATION_MORPH_TEST_BASE_REF;
const outfile = path.join(root, ".tmp/battle-scene-morph-selfcheck.mjs");
await build({
  absWorkingDir: root,
  entryPoints: ["apps/game/src/sim/battleScene.morph.selfcheck.ts"],
  bundle: true,
  platform: "node",
  format: "esm",
  define: { "import.meta.env.BASE_URL": '"/"' },
  outfile,
  plugins: baseRef ? [{
    name: "historical-battle-scene",
    setup(builder) {
      builder.onLoad({ filter: /[/\\]battleScene\.ts$/ }, () => ({
        contents: execFileSync("git", ["show", `${baseRef}:${sourcePath}`], { cwd: root, encoding: "utf8" }),
        loader: "ts",
        resolveDir: path.join(root, path.dirname(sourcePath)),
      }));
    },
  }] : [],
});
const { runBattleSceneMorphSelfcheck, runBattleSceneAnimationRaceSelfcheck, runBattleSceneRetirementSelfcheck, runBattleSceneLoadFailureSelfcheck } = await import(pathToFileURL(outfile).href);
await runBattleSceneMorphSelfcheck();
console.log("battleScene morph selfcheck: PASS");
await runBattleSceneAnimationRaceSelfcheck();
await runBattleSceneRetirementSelfcheck();
await runBattleSceneLoadFailureSelfcheck((trigger) => new Promise((resolve, reject) => {
  const timer = setTimeout(() => {
    process.removeListener("unhandledRejection", onRejection);
    reject(new Error("Expected the model-load error to remain observable"));
  }, 1000);
  function onRejection(error) {
    clearTimeout(timer);
    resolve(error);
  }
  process.once("unhandledRejection", onRejection);
  trigger();
}));

await import("./run-battle-scene-size-selfcheck.mjs");
