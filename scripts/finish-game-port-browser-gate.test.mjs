import assert from "node:assert/strict";
import fs from "node:fs";
import path from "node:path";
import test from "node:test";
import { fileURLToPath } from "node:url";

import {
  MAINTAINED_BROWSER_SMOKE_COMMAND,
  assertMaintainedBrowserGateSource,
  runMaintainedProductionBrowserSmoke,
} from "./lib/production-browser-smoke.mjs";

const root = path.resolve(path.dirname(fileURLToPath(import.meta.url)), "..");

test("POC invokes the maintained strict production-browser route", () => {
  const calls = [];
  const result = runMaintainedProductionBrowserSmoke((args) => {
    calls.push(args);
    return { command: `pnpm ${args.join(" ")}`, exitCode: 0 };
  });

  assert.deepEqual(MAINTAINED_BROWSER_SMOKE_COMMAND, ["smoke:browser"]);
  assert.deepEqual(calls, [["smoke:browser"]]);
  assert.equal(result.browser, "maintained strict smoke");
  assert.equal(result.command, "pnpm smoke:browser");
  assert.match(result.readiness, /boot-ready/);
  assert.match(result.readiness, /battle HUD/);
});

test("POC gate rejects a nonzero maintained smoke exit", () => {
  assert.throws(
    () => runMaintainedProductionBrowserSmoke(() => ({ command: "pnpm smoke:browser", exitCode: 7 })),
    /exited 7/,
  );
});

test("POC gate cannot regress to the obsolete loaded-only readiness contract", () => {
  const poc = fs.readFileSync(path.join(root, "scripts", "finish-game-port-poc.mjs"), "utf8");
  const smoke = fs.readFileSync(path.join(root, "scripts", "smoke-browser-game.mjs"), "utf8");

  assert.throws(
    () => assertMaintainedBrowserGateSource('if (!/data-gf-runtime="loaded"/.test(dom)) throw new Error();'),
    /obsolete loaded-only readiness contract/,
  );
  assertMaintainedBrowserGateSource(poc);
  assert.match(smoke, /dataset\.gfRuntime === "boot-ready"/);
  assert.match(smoke, /window\.__gf\?\.navigation\?\.screen === "title"/);
  assert.match(smoke, /window\.__gf\?\.navigation\?\.screen === "battle"/);
  assert.match(smoke, /document\.querySelector\("\.gf-hud"\)/);
});
