// The port POC must use the maintained production-browser contract rather than
// carrying a second, weaker readiness probe that can drift from the game.

export const MAINTAINED_BROWSER_SMOKE_COMMAND = Object.freeze(["smoke:browser"]);

export function assertMaintainedBrowserGateSource(source) {
  if (/data-gf-runtime="loaded"/.test(source)) {
    throw new Error("POC browser gate must not use the obsolete loaded-only readiness contract");
  }
  if (!/runMaintainedProductionBrowserSmoke\(runPnpm\)/.test(source)) {
    throw new Error("POC browser gate must invoke the maintained strict production-browser route");
  }
}

/**
 * Run the authoritative production browser route used by the game release gate.
 * `runPnpm` is injected so the POC and its regression test share the exact command.
 */
export function runMaintainedProductionBrowserSmoke(runPnpm) {
  const result = runPnpm([...MAINTAINED_BROWSER_SMOKE_COMMAND]);
  if (result.exitCode !== 0) {
    throw new Error(`maintained production browser smoke exited ${result.exitCode}`);
  }
  return {
    browser: "maintained strict smoke",
    command: result.command,
    readiness: "boot-ready title -> Challenge -> battle HUD + pause-edge route",
  };
}
