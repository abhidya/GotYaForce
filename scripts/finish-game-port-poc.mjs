#!/usr/bin/env node

import fs from "node:fs";
import http from "node:http";
import path from "node:path";
import process from "node:process";
import { spawn, spawnSync } from "node:child_process";
import { fileURLToPath } from "node:url";

import {
  appendAutomaticVerification,
  verifyGeneratedCandidate,
} from "./lib/oghidra-port-auto-verify.mjs";
import { extractEagleJetFacts, importArtifact } from "./lib/oghidra-port-import.mjs";

const root = path.resolve(path.dirname(fileURLToPath(import.meta.url)), "..");
const forceCheckpointResume = process.argv.slice(2).includes("--resume-qwen-checkpoint");
const refreshArtifact = process.argv.slice(2).includes("--refresh-artifact") || forceCheckpointResume;
const canonicalArtifact = path.join(
  root,
  "research",
  "decomp",
  "generated",
  "8012b458.port.json",
);
const runRoot = path.join(root, "research", "decomp", "generated", "finish-game-port-poc");
const refreshedArtifact = path.join(runRoot, "8012b458.port.json");
const artifactPath = refreshArtifact
  ? refreshedArtifact
  : (fs.existsSync(refreshedArtifact) ? refreshedArtifact : canonicalArtifact);
const generatedPath = path.join(
  root,
  "packages",
  "combat",
  "src",
  "generated",
  "oghidra",
  "fn_8012b458.generated.ts",
);
const registryPath = path.join(
  root,
  "packages",
  "combat",
  "src",
  "generated",
  "oghidra",
  "promotion-registry.generated.ts",
);
const reportPath = path.join(runRoot, "8012b458-import-report.md");
const verificationPath = path.join(runRoot, "8012b458-auto-verification.json");
const statePath = path.join(runRoot, "run-state.json");
const controlPath = path.join(runRoot, "control.json");
const checkpointEvidencePath = path.join(runRoot, "8012b458.port.evidence.json");
const previousState = fs.existsSync(statePath)
  ? JSON.parse(fs.readFileSync(statePath, "utf8"))
  : null;
const checkpointResponses = fs.existsSync(runRoot)
  ? fs.readdirSync(runRoot)
    .filter((name) => /^8012b458\.port\.raw-attempt-\d+\.txt$/.test(name))
    .map((name) => path.join(runRoot, name))
    .sort()
  : [];
const failedStageStartedAt = Date.parse(previousState?.stages?.local_model?.started_at ?? "");
const resumeFreshCheckpoint = refreshArtifact
  && (
    forceCheckpointResume
    || (
      previousState?.status === "failed"
      && previousState?.current_stage === "local_model"
    )
  )
  && fs.existsSync(checkpointEvidencePath)
  && checkpointResponses.some((responsePath) =>
    forceCheckpointResume || fs.statSync(responsePath).mtimeMs >= failedStageStartedAt);
const totalStages = refreshArtifact ? 8 : 7;
const stagePlan = [
  ...(refreshArtifact
    ? [{
      id: "local_model",
      label: forceCheckpointResume
        ? "Score and resume retained local-Qwen responses"
        : "Generate a fresh artifact with local Qwen and live Ghidra",
    }]
    : []),
  { id: "artifact", label: "Validate local-Qwen artifact provenance" },
  { id: "generate", label: "Generate the production candidate" },
  { id: "automatic_verify", label: "Compile and run artifact-derived differential tests" },
  { id: "promote", label: "Promote the verified candidate into the production runtime" },
  { id: "combat", label: "Build combat and run the complete ROM replay suite" },
  { id: "web_build", label: "Build the production browser game" },
  { id: "browser", label: "Launch Chrome and execute the production browser bundle" },
];
let currentStage = 0;

fs.mkdirSync(runRoot, { recursive: true });
if (process.env.OGHIDRA_GUI_CONTROLLED !== "1" || !fs.existsSync(controlPath)) {
  fs.writeFileSync(
    controlPath,
    `${JSON.stringify({ command: "run", updated_at: new Date().toISOString() }, null, 2)}\n`,
    "utf8",
  );
}

const state = {
  run_schema: 1,
  run_mode: forceCheckpointResume ? "resume" : (refreshArtifact ? "fresh" : "replay"),
  total_stages: totalStages,
  objective: "Finish the GotYaForce browser port autonomously",
  scope: {
    kind: "vertical_slice",
    function_address: "0x8012b458",
    production_family: "Eagle Jet",
  },
  queue: [
    {
      address: "0x8012b458",
      family: "Eagle Jet",
      status: "queued",
    },
  ],
  local_model: null,
  session: process.env.OGHIDRA_ACTIVE_SESSION
    ? {
      path: process.env.OGHIDRA_ACTIVE_SESSION,
      role: "advisory",
      vectors_required: false,
    }
    : {
      path: null,
      role: "none",
      vectors_required: false,
    },
  status: "running",
  started_at: new Date().toISOString(),
  updated_at: new Date().toISOString(),
  current_stage: null,
  stages: Object.fromEntries(stagePlan.map(({ id, label }) => [
    id,
    { label, status: "pending" },
  ])),
  promotion: {
    address: "0x8012b458",
    status: "not_started",
    rolled_back: false,
  },
};

function saveState() {
  state.updated_at = new Date().toISOString();
  fs.writeFileSync(statePath, `${JSON.stringify(state, null, 2)}\n`, "utf8");
}

function setQueueStatus(status) {
  state.queue[0].status = status;
  saveState();
}

class StopRequestedError extends Error {}

function readControl() {
  try {
    return JSON.parse(fs.readFileSync(controlPath, "utf8"));
  } catch {
    return { command: "run" };
  }
}

async function waitForRunPermission() {
  let announcedPause = false;
  while (true) {
    const command = readControl().command ?? "run";
    if (command === "stop_after_stage") {
      throw new StopRequestedError("stop requested after the current stage");
    }
    if (command !== "pause_after_stage") {
      if (announcedPause) {
        state.status = "running";
        saveState();
        process.stdout.write("        RESUMED\n");
      }
      return;
    }
    if (!announcedPause) {
      announcedPause = true;
      state.status = "paused";
      state.current_stage = null;
      saveState();
      process.stdout.write("        PAUSED — waiting at a safe stage boundary\n");
    }
    await new Promise((resolve) => setTimeout(resolve, 500));
  }
}

async function startStage(id, label) {
  await waitForRunPermission();
  currentStage += 1;
  state.status = "running";
  state.current_stage = id;
  state.stages[id] = {
    label,
    status: "running",
    started_at: new Date().toISOString(),
  };
  saveState();
  process.stdout.write(`[${currentStage}/${totalStages}] ${label} ...\n`);
}

function passStage(id, detail) {
  state.stages[id] = {
    ...state.stages[id],
    status: "passed",
    detail,
    finished_at: new Date().toISOString(),
  };
  state.current_stage = null;
  saveState();
  process.stdout.write(`        PASS — ${detail}\n`);
}

function failStage(id, error) {
  state.stages[id] = {
    ...state.stages[id],
    status: "failed",
    error: error instanceof Error ? error.message : String(error),
    finished_at: new Date().toISOString(),
  };
  state.status = "failed";
  saveState();
}

function tail(text, length = 5000) {
  return text.length <= length ? text : text.slice(-length);
}

function pnpmInvocation(args) {
  const npmExecPath = process.env.npm_execpath;
  if (npmExecPath) {
    const isJavaScriptEntrypoint = /\.(?:c?js|mjs)$/i.test(npmExecPath);
    return {
      command: isJavaScriptEntrypoint ? process.execPath : npmExecPath,
      args: isJavaScriptEntrypoint ? [npmExecPath, ...args] : args,
      display: `pnpm ${args.join(" ")}`,
    };
  }
  return {
    command: process.platform === "win32" ? "pnpm.cmd" : "pnpm",
    args,
    display: `pnpm ${args.join(" ")}`,
  };
}

function runPnpm(args) {
  const invocation = pnpmInvocation(args);
  const result = spawnSync(invocation.command, invocation.args, {
    cwd: root,
    encoding: "utf8",
    windowsHide: true,
  });
  if (result.status !== 0) {
    throw new Error(
      `${invocation.display} failed with exit ${result.status}\n`
      + tail(`${result.stdout}\n${result.stderr}`),
    );
  }
  return {
    command: invocation.display,
    exitCode: result.status,
    summary: tail(result.stdout.trim(), 1000),
  };
}

function runPortExporter(arguments_, environment = {}) {
  const oghidraRoot = path.join(root, "research", "tools", "OGhidra");
  const python = path.join(oghidraRoot, ".venv", "Scripts", "python.exe");
  const activeSession = process.env.OGHIDRA_ACTIVE_SESSION;
  const exporterArguments = (
    activeSession
    && fs.existsSync(activeSession)
    && !arguments_.includes("--session")
  )
    ? [...arguments_, "--session", activeSession]
    : arguments_;
  const result = spawnSync(
    python,
    ["main.py", "export-port", ...exporterArguments],
    {
      cwd: oghidraRoot,
      encoding: "utf8",
      env: {
        ...process.env,
        OGHIDRA_PORT_LIVENESS_PATH: path.join(runRoot, "llm-liveness.json"),
        ...environment,
      },
      windowsHide: true,
      timeout: 30 * 60 * 1000,
    },
  );
  return result;
}

function requireSuccessfulExport(result, label) {
  if (result.status === 0) return tail(result.stdout.trim(), 1000);
  throw new Error(
    `${label} failed with exit ${result.status}\n`
    + tail(`${result.stdout}\n${result.stderr}`),
  );
}

function scoreAndReplayQwenResponses(responsePaths, responseModel) {
  const temporaryRoot = path.join(root, ".tmp", "finish-game-port-checkpoint-replay");
  fs.mkdirSync(temporaryRoot, { recursive: true });
  const scored = [];
  try {
    for (const responsePath of responsePaths) {
      const attempt = path.basename(responsePath).match(/attempt-(\d+)/)?.[1] ?? "unknown";
      const candidatePath = path.join(temporaryRoot, `attempt-${attempt}.json`);
      const replay = runPortExporter([
        "--address", "0x8012b458",
        "--output", candidatePath,
        "--evidence-file", checkpointEvidencePath,
        "--model-response", responsePath,
        "--response-provider", "custom_api",
        "--response-model", responseModel,
        "--response-mode", "json_schema",
      ]);
      if (replay.status !== 0) continue;
      const candidate = JSON.parse(fs.readFileSync(candidatePath, "utf8"));
      const facts = extractEagleJetFacts(candidate);
      scored.push({
        attempt: Number(attempt),
        responsePath,
        score: Object.values(facts).filter(Boolean).length,
      });
    }
    scored.sort((left, right) => right.score - left.score || right.attempt - left.attempt);
    const selected = scored[0];
    if (!selected) throw new Error("no retained Qwen response passed deterministic validation");
    const result = runPortExporter([
      "--address", "0x8012b458",
      "--output", artifactPath,
      "--evidence-file", checkpointEvidencePath,
      "--model-response", selected.responsePath,
      "--response-provider", "custom_api",
      "--response-model", responseModel,
      "--response-mode", "json_schema",
    ]);
    const summary = requireSuccessfulExport(result, "selected Qwen checkpoint replay");
    return `selected retained Qwen attempt ${selected.attempt} (${selected.score}/12 required facts); ${summary}`;
  } finally {
    const resolved = path.resolve(temporaryRoot);
    const expected = path.resolve(root, ".tmp", "finish-game-port-checkpoint-replay");
    if (resolved !== expected) throw new Error(`refusing to remove unexpected checkpoint path: ${resolved}`);
    fs.rmSync(resolved, { recursive: true, force: true });
  }
}

function runFreshLocalModelExport() {
  if (resumeFreshCheckpoint) {
    const configuredModel = fs.existsSync(canonicalArtifact)
      ? JSON.parse(fs.readFileSync(canonicalArtifact, "utf8")).producer?.model_name
      : null;
    const initializedModel = previousState?.stages?.local_model?.error
      ?.match(/\[Custom API\] Initialized:.* model=([^\s]+)/)?.[1];
    const responseModel = initializedModel
      ?? configuredModel
      ?? "unsloth/Qwen3.6-35B-A3B-MTP-GGUF";
    const eligibleResponses = checkpointResponses.filter((responsePath) =>
      forceCheckpointResume || fs.statSync(responsePath).mtimeMs >= failedStageStartedAt);
    return scoreAndReplayQwenResponses(eligibleResponses, responseModel);
  }

  const generationStartedAt = Date.now();
  let effectiveModel = fs.existsSync(canonicalArtifact)
    ? JSON.parse(fs.readFileSync(canonicalArtifact, "utf8")).producer?.model_name
    : "unsloth/Qwen3.6-35B-A3B-MTP-GGUF";
  let result = runPortExporter([
    "--address", "0x8012b458",
    "--ghidra-backend", "http",
    "--output", artifactPath,
  ]);
  const failureOutput = `${result.stdout}\n${result.stderr}`;
  if (
    result.status !== 0
    && failureOutput.includes("model_not_found")
    && failureOutput.includes("Switch model by request")
  ) {
    const configuredModel = fs.existsSync(canonicalArtifact)
      ? JSON.parse(fs.readFileSync(canonicalArtifact, "utf8")).producer?.model_name
      : null;
    const baseModel = configuredModel?.split(":", 1)[0];
    if (baseModel && baseModel !== configuredModel) {
      effectiveModel = baseModel;
      result = runPortExporter(
        [
          "--address", "0x8012b458",
          "--ghidra-backend", "http",
          "--output", artifactPath,
          "--model", baseModel,
        ],
      );
      if (result.status === 0) {
        return `selected loaded local-model ID ${baseModel}; ${
          requireSuccessfulExport(result, "fresh local-Qwen export")
        }`;
      }
    }
  }
  if (result.status !== 0) {
    const currentResponses = fs.readdirSync(runRoot)
      .filter((name) => /^8012b458\.port\.raw-attempt-\d+\.txt$/.test(name))
      .map((name) => path.join(runRoot, name))
      .filter((responsePath) => fs.statSync(responsePath).mtimeMs >= generationStartedAt);
    if (currentResponses.length > 0) {
      return scoreAndReplayQwenResponses(currentResponses, effectiveModel);
    }
  }
  return requireSuccessfulExport(result, "fresh local-Qwen export");
}

function promotionSource(enabled) {
  return `// Managed by scripts/finish-game-port-poc.mjs.
// A port is enabled only after automatic compilation and differential verification pass.

export const OGHIDRA_PROMOTED_PORTS = {
  "0x8012b458": ${enabled ? "true" : "false"},
} as const;
`;
}

function contentType(file) {
  const extension = path.extname(file).toLowerCase();
  return {
    ".css": "text/css; charset=utf-8",
    ".html": "text/html; charset=utf-8",
    ".js": "text/javascript; charset=utf-8",
    ".json": "application/json; charset=utf-8",
    ".png": "image/png",
    ".svg": "image/svg+xml",
    ".wasm": "application/wasm",
  }[extension] ?? "application/octet-stream";
}

function startStaticServer(dist) {
  const resolvedDist = path.resolve(dist);
  const server = http.createServer((request, response) => {
    const requestPath = decodeURIComponent(new URL(request.url ?? "/", "http://localhost").pathname);
    const relative = requestPath === "/" ? "index.html" : requestPath.replace(/^\/+/, "");
    let target = path.resolve(resolvedDist, relative);
    if (target !== resolvedDist && !target.startsWith(`${resolvedDist}${path.sep}`)) {
      response.writeHead(403).end("Forbidden");
      return;
    }
    if (!fs.existsSync(target) || fs.statSync(target).isDirectory()) {
      target = path.join(resolvedDist, "index.html");
    }
    response.writeHead(200, { "content-type": contentType(target) });
    fs.createReadStream(target).pipe(response);
  });
  return new Promise((resolve, reject) => {
    server.once("error", reject);
    server.listen(0, "127.0.0.1", () => {
      const address = server.address();
      if (!address || typeof address === "string") {
        reject(new Error("could not allocate browser-smoke port"));
        return;
      }
      resolve({ server, url: `http://127.0.0.1:${address.port}/` });
    });
  });
}

function findBrowser() {
  const candidates = process.platform === "win32"
    ? [
      "C:\\Program Files\\Google\\Chrome\\Application\\chrome.exe",
      "C:\\Program Files (x86)\\Google\\Chrome\\Application\\chrome.exe",
      "C:\\Program Files\\Microsoft\\Edge\\Application\\msedge.exe",
    ]
    : [
      "/usr/bin/google-chrome",
      "/usr/bin/chromium",
      "/usr/bin/chromium-browser",
    ];
  return candidates.find((candidate) => fs.existsSync(candidate)) ?? null;
}

async function dumpBrowserDom(browser, url, profileDir) {
  return await new Promise((resolve, reject) => {
    const child = spawn(
      browser,
      [
        "--headless=new",
        "--disable-gpu",
        "--disable-dev-shm-usage",
        "--no-first-run",
        "--no-default-browser-check",
        `--user-data-dir=${profileDir}`,
        "--virtual-time-budget=10000",
        "--dump-dom",
        url,
      ],
      { cwd: root, windowsHide: true },
    );
    let stdout = "";
    let stderr = "";
    child.stdout.on("data", (chunk) => {
      stdout += chunk.toString();
    });
    child.stderr.on("data", (chunk) => {
      stderr += chunk.toString();
    });
    const timer = setTimeout(() => {
      child.kill();
      reject(new Error(`headless browser timed out\n${tail(stderr)}`));
    }, 45000);
    child.once("error", (error) => {
      clearTimeout(timer);
      reject(error);
    });
    child.once("close", (code) => {
      clearTimeout(timer);
      if (code !== 0) {
        reject(new Error(`headless browser exited ${code}\n${tail(stderr)}`));
        return;
      }
      resolve({ stdout, stderr });
    });
  });
}

function removeOwnedBrowserTemp(target) {
  const ownedRoot = path.resolve(root, ".tmp", "finish-game-port-browser");
  const resolved = path.resolve(target);
  if (resolved !== ownedRoot && !resolved.startsWith(`${ownedRoot}${path.sep}`)) {
    throw new Error(`refusing to remove non-controller path: ${resolved}`);
  }
  fs.rmSync(resolved, { recursive: true, force: true });
}

async function browserSmoke() {
  const browser = findBrowser();
  if (!browser) throw new Error("Chrome/Edge not found for production browser smoke");
  const dist = path.join(root, "apps", "game", "dist");
  const { server, url } = await startStaticServer(dist);
  const tempParent = path.join(root, ".tmp", "finish-game-port-browser");
  fs.mkdirSync(tempParent, { recursive: true });
  const profile = fs.mkdtempSync(path.join(tempParent, "profile-"));
  try {
    const result = await dumpBrowserDom(browser, url, profile);
    if (!/data-gf-runtime="loaded"/.test(result.stdout)) {
      throw new Error(
        "browser bundle loaded without the data-gf-runtime readiness signal\n"
        + tail(result.stdout),
      );
    }
    return {
      browser: path.basename(browser),
      url,
      readiness: "data-gf-runtime=loaded",
    };
  } finally {
    await new Promise((resolve) => server.close(resolve));
    removeOwnedBrowserTemp(profile);
  }
}

const originalRegistry = fs.readFileSync(registryPath, "utf8");
let promoted = false;

try {
  if (refreshArtifact) {
    await startStage(
      "local_model",
      forceCheckpointResume
        ? "Score and resume retained local-Qwen responses"
        : "Generate a fresh artifact with local Qwen and live Ghidra",
    );
    const summary = runFreshLocalModelExport();
    setQueueStatus("model_generated");
    passStage("local_model", summary || "local Qwen artifact generated");
  }

  await startStage("artifact", "Validate local-Qwen artifact provenance");
  const artifact = JSON.parse(fs.readFileSync(artifactPath, "utf8"));
  if (!/Qwen3\.6-35B-A3B/i.test(artifact.producer?.model_name ?? "")) {
    throw new Error(`unexpected model provenance: ${artifact.producer?.model_name ?? "missing"}`);
  }
  if (artifact.verification?.status !== "verified") {
    throw new Error(`artifact status is ${artifact.verification?.status ?? "missing"}`);
  }
  state.local_model = artifact.producer.model_name;
  setQueueStatus("evidence_verified");
  passStage("artifact", `${artifact.producer.model_name}; ${artifact.verification.checks.length} evidence checks`);

  await startStage("generate", "Generate the production candidate");
  const imported = importArtifact({
    artifactPath,
    generatedPath,
    reportPath,
    force: true,
  });
  if (imported.fallback) {
    throw new Error(`importer emitted fallback: ${imported.blockers.join("; ")}`);
  }
  setQueueStatus("generated");
  passStage("generate", `${Object.keys(imported.facts).length} verified facts; no blockers`);

  await startStage("automatic_verify", "Compile and run artifact-derived differential tests");
  const verification = await verifyGeneratedCandidate({
    root,
    artifactPath,
    generatedPath,
    verificationPath,
    fallback: imported.fallback,
  });
  appendAutomaticVerification(
    reportPath,
    path.relative(root, verificationPath).replaceAll("\\", "/"),
    verification,
  );
  if (verification.status !== "passed") {
    throw new Error(
      `automatic verification ${verification.status}: `
      + (verification.behavior.blocker ?? `${verification.behavior.failed} mismatches`),
    );
  }
  setQueueStatus("behavior_verified");
  passStage(
    "automatic_verify",
    `compile passed; ${verification.behavior.passed}/${verification.behavior.scenarios.length} generated scenarios; 0 handwritten`,
  );

  await startStage("promote", "Promote the verified candidate into the production runtime");
  fs.writeFileSync(registryPath, promotionSource(true), "utf8");
  promoted = true;
  state.promotion.status = "promoted";
  setQueueStatus("integrated");
  saveState();
  passStage("promote", "0x8012b458 enabled in the generated production registry");

  await startStage("combat", "Build combat and run the complete ROM replay suite");
  const combatBuild = runPnpm(["--filter", "@gf/combat", "build"]);
  const romCheck = runPnpm(["selfcheck:rom"]);
  if (!romCheck.summary.includes("[rom.selfcheck] ALL PASS")) {
    throw new Error("ROM selfcheck exited successfully without its ALL PASS sentinel");
  }
  passStage("combat", `${combatBuild.command}; ROM selfcheck ALL PASS`);

  await startStage("web_build", "Build the production browser game");
  const webBuild = runPnpm(["--filter", "game", "build"]);
  passStage("web_build", `${webBuild.command}; production bundle emitted`);

  await startStage("browser", "Launch Chrome and execute the production browser bundle");
  const browser = await browserSmoke();
  passStage("browser", `${browser.browser}; ${browser.readiness}`);

  state.status = "completed";
  state.queue[0].status = "integrated";
  state.current_stage = null;
  state.completed_at = new Date().toISOString();
  saveState();
  fs.writeFileSync(
    controlPath,
    `${JSON.stringify({ command: "completed", updated_at: new Date().toISOString() }, null, 2)}\n`,
    "utf8",
  );
  process.stdout.write("\nAUTONOMOUS PORT POC: PASS\n");
  process.stdout.write(`${JSON.stringify({
    status: state.status,
    localModel: state.local_model,
    functionAddress: state.scope.function_address,
    productionPromotion: state.promotion.status,
    generatedScenarios: state.stages.automatic_verify.detail,
    combat: state.stages.combat.status,
    webBuild: state.stages.web_build.status,
    browser: state.stages.browser.detail,
    progressState: path.relative(root, statePath).replaceAll("\\", "/"),
  }, null, 2)}\n`);
} catch (error) {
  if (error instanceof StopRequestedError) {
    state.status = "stopped";
    state.queue[0].status = "stopped";
    state.current_stage = null;
    state.stopped_at = new Date().toISOString();
    if (promoted) {
      fs.writeFileSync(registryPath, originalRegistry, "utf8");
      state.promotion.status = "rolled_back";
      state.promotion.rolled_back = true;
    }
    saveState();
    process.stderr.write("Port run stopped at a safe stage boundary.\n");
    process.exitCode = 2;
  } else {
  const stage = state.current_stage ?? "controller";
  failStage(stage, error);
  state.queue[0].status = "blocked";
  if (promoted) {
    fs.writeFileSync(registryPath, originalRegistry, "utf8");
    state.promotion.status = "rolled_back";
    state.promotion.rolled_back = true;
    saveState();
    process.stderr.write("Promotion rolled back after downstream failure.\n");
  }
  process.stderr.write(`${error instanceof Error ? error.stack ?? error.message : String(error)}\n`);
  process.exitCode = 1;
  }
}
