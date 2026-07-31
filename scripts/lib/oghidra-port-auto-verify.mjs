import assert from "node:assert/strict";
import fs from "node:fs";
import path from "node:path";
import process from "node:process";
import { spawnSync } from "node:child_process";
import { pathToFileURL } from "node:url";

const PROFILE_BY_ADDRESS = {
  "0x8012b458": {
    candidateExport: "tryStepFun8012b458",
    oracleSources: [
      "packages/combat/src/families/eagle-jet.ts",
      "packages/combat/src/rom/actor.ts",
    ],
    targetBorgNumber: 0x61b,
  },
};

function canonicalScalar(value) {
  if (typeof value === "string" && /^0x[0-9a-f]+$/i.test(value)) {
    return Number.parseInt(value, 16);
  }
  if (typeof value === "string" && /^-?\d+(?:\.\d+)?$/.test(value)) {
    return Number(value);
  }
  return value;
}

function operations(payload) {
  const ir = payload.port_ir;
  if (!ir) return [];
  return ["entry", "update", "exit"].flatMap((section) =>
    Array.isArray(ir[section]) ? ir[section] : []);
}

function distinct(values) {
  return [...new Set(values)];
}

/**
 * Build boundary inputs from the artifact instead of maintaining a handwritten
 * list of expected scenarios. The target profile supplies only the runtime ABI
 * mapping and the concrete GotYaForce oracle.
 */
export function deriveBoundaryScenarios(payload, profile = PROFILE_BY_ADDRESS[payload.function?.address]) {
  if (!profile) return [];

  const ops = operations(payload);
  const branchValues = distinct(
    ops
      .filter((operation) =>
        ["branch_if_eq", "branch_if_ne"].includes(operation?.type))
      .map((operation) => canonicalScalar(operation.value))
      .filter((value) => typeof value === "number"),
  );
  const timerFloors = distinct(
    ops
      .filter((operation) => operation?.type === "branch_if_lte")
      .map((operation) => canonicalScalar(operation.rhs))
      .filter((value) => typeof value === "number"),
  );

  const borgNumber = branchValues.includes(profile.targetBorgNumber)
    ? profile.targetBorgNumber
    : branchValues[0] ?? profile.targetBorgNumber;
  const timerFloor = timerFloors[0] ?? 0;
  const dtValues = [0.25, 1, 2];
  const controlWords = [0, 3, 0xffffffff];
  const scenarios = [];

  for (const [index, dt] of dtValues.entries()) {
    const common = {
      borgNumber,
      dt,
      effectMode: 0x55 + index,
      cooldown: 9 + index,
      housekeeping: 7 + index,
      controlWord: controlWords[index],
    };
    scenarios.push({
      id: `entry-dt-${dt}`,
      source: "artifact-boundary-matrix",
      input: { ...common, phase: 0, timer: timerFloor + 10 + index },
    });

    for (const [boundary, timer] of [
      ["above", timerFloor + (2 * dt)],
      ["exact", timerFloor + dt],
      ["below", timerFloor + (dt / 2)],
    ]) {
      scenarios.push({
        id: `update-${boundary}-dt-${dt}`,
        source: "artifact-boundary-matrix",
        input: { ...common, phase: 1, timer },
      });
    }
  }
  return scenarios;
}

function portableCommand(command, args, cwd) {
  const normalizedRoot = path.resolve(cwd);
  const display = (value) => {
    const resolved = path.resolve(value);
    if (resolved === normalizedRoot || resolved.startsWith(`${normalizedRoot}${path.sep}`)) {
      return path.relative(normalizedRoot, resolved).replaceAll("\\", "/") || ".";
    }
    return value;
  };
  const executable = path.resolve(command) === path.resolve(process.execPath)
    ? "node"
    : display(command);
  return [executable, ...args.map(display)].join(" ");
}

function run(command, args, cwd) {
  const result = spawnSync(command, args, {
    cwd,
    encoding: "utf8",
    windowsHide: true,
  });
  return {
    command: portableCommand(command, args, cwd),
    passed: result.status === 0,
    exitCode: result.status,
    stdout: result.stdout,
    stderr: result.stderr,
  };
}

function observeCandidate(step, input) {
  const actor = structuredClone(input);
  const effects = {
    retiredHitboxKinds: [],
    playedCues: [],
    preparedParts: [],
    fullBodyCues: [],
  };
  const host = {
    retireHitbox(_actor, kind) {
      effects.retiredHitboxKinds.push(kind);
    },
    playCue(_actor, cue) {
      effects.playedCues.push(cue);
    },
    preparePart(_actor, slot, value) {
      effects.preparedParts.push([slot, value]);
    },
    dispatchFullBodyCue(target, cue) {
      effects.fullBodyCues.push(cue);
      target.phase = 0;
    },
  };
  step(actor, host);
  return {
    state: {
      phase: actor.phase,
      timer: actor.timer,
      effectMode: actor.effectMode,
      cooldown: actor.cooldown,
      housekeeping: actor.housekeeping,
      controlWord: actor.controlWord >>> 0,
    },
    effects,
  };
}

function observeOracle(createRomActor, createEagleJetAction1Reference, input) {
  const actor = createRomActor();
  const playedCues = [];
  const step = createEagleJetAction1Reference({
    onPlayCue: (_actor, cue) => playedCues.push(cue),
  });
  actor.borgNumber = input.borgNumber;
  actor.fbPhaseSlots[0] = input.phase;
  actor.handlerTimer = input.timer;
  actor.dt = input.dt;
  actor.stateTimer = input.cooldown;
  actor.housekeeping73f = input.housekeeping;
  actor.controlWord = input.controlWord;
  actor.effectMode6e8 = input.effectMode;
  actor.cueTable = new Int8Array(256).fill(-1);
  actor.cueTable[0x1b * 2] = 0;
  const priorCue = actor.fbCue;

  step(actor);

  return {
    state: {
      phase: actor.fbPhaseSlots[0],
      timer: actor.handlerTimer,
      effectMode: actor.effectMode6e8,
      cooldown: actor.stateTimer,
      housekeeping: actor.housekeeping73f,
      controlWord: actor.controlWord >>> 0,
    },
    effects: {
      retiredHitboxKinds: actor.retiredHitboxKind === undefined
        ? []
        : [actor.retiredHitboxKind],
      playedCues,
      preparedParts: (actor.preparedPartSlots ?? []).map((slot) => [slot, 0]),
      fullBodyCues: actor.fbCue === priorCue ? [] : [actor.fbCue],
    },
  };
}

function writeJson(target, value) {
  fs.mkdirSync(path.dirname(target), { recursive: true });
  fs.writeFileSync(target, `${JSON.stringify(value, null, 2)}\n`, "utf8");
}

function removeOwnedTemp(root, target) {
  const ownedRoot = path.resolve(root, ".tmp", "oghidra-auto-verify");
  const resolved = path.resolve(target);
  if (resolved !== ownedRoot && !resolved.startsWith(`${ownedRoot}${path.sep}`)) {
    throw new Error(`refusing to remove non-verifier path: ${resolved}`);
  }
  fs.rmSync(resolved, { recursive: true, force: true });
}

export async function verifyGeneratedCandidate({
  root,
  artifactPath,
  generatedPath,
  verificationPath,
  fallback = false,
}) {
  const resolvedRoot = path.resolve(root);
  const payload = JSON.parse(fs.readFileSync(artifactPath, "utf8"));
  const profile = PROFILE_BY_ADDRESS[payload.function.address];
  const tempParent = path.join(resolvedRoot, ".tmp", "oghidra-auto-verify");
  fs.mkdirSync(tempParent, { recursive: true });
  const temp = fs.mkdtempSync(path.join(tempParent, `${payload.function.address.slice(2)}-`));
  const candidateOut = path.join(temp, "candidate");
  const oracleOut = path.join(temp, "oracle");
  const tsc = path.join(resolvedRoot, "node_modules", "typescript", "bin", "tsc");

  const candidateCompile = run(
    process.execPath,
    [
      tsc,
      "--target", "ES2022",
      "--module", "NodeNext",
      "--moduleResolution", "NodeNext",
      "--outDir", candidateOut,
      path.resolve(generatedPath),
    ],
    resolvedRoot,
  );

  const result = {
    verification_schema: 1,
    function_address: payload.function.address,
    artifact_body_hash: payload.function.body_hash,
    candidate: path.relative(resolvedRoot, path.resolve(generatedPath)).replaceAll("\\", "/"),
    scenario_source: "artifact-boundary-matrix",
    handwritten_scenarios: 0,
    compile: candidateCompile,
    oracle: profile
      ? "existing GotYaForce family implementation"
      : null,
    behavior: {
      status: "blocked",
      passed: 0,
      failed: 0,
      scenarios: [],
      blocker: null,
    },
    status: "blocked",
  };

  try {
    if (!candidateCompile.passed) {
      result.behavior.blocker = "generated TypeScript did not compile";
      result.status = "failed";
      writeJson(verificationPath, result);
      return result;
    }
    if (fallback) {
      result.behavior.blocker = "fallback candidates are compile-checked but not behavior-verified";
      writeJson(verificationPath, result);
      return result;
    }
    if (!profile) {
      result.behavior.blocker = `no automatic behavior oracle profile for ${payload.function.address}`;
      writeJson(verificationPath, result);
      return result;
    }

    const oracleCompile = run(
      process.execPath,
      [
        tsc,
        "--target", "ES2022",
        "--module", "NodeNext",
        "--moduleResolution", "NodeNext",
        "--outDir", oracleOut,
        "--rootDir", path.join(resolvedRoot, "packages", "combat", "src"),
        ...profile.oracleSources.map((source) => path.join(resolvedRoot, source)),
      ],
      resolvedRoot,
    );
    result.oracle_compile = oracleCompile;
    if (!oracleCompile.passed) {
      result.behavior.blocker = "existing GotYaForce oracle did not compile";
      result.status = "failed";
      writeJson(verificationPath, result);
      return result;
    }

    const candidateModulePath = path.join(
      candidateOut,
      `${path.basename(generatedPath, path.extname(generatedPath))}.js`,
    );
    const candidateModule = await import(
      `${pathToFileURL(candidateModulePath).href}?run=${Date.now()}`
    );
    const oracleFamily = await import(
      `${pathToFileURL(path.join(oracleOut, "families", "eagle-jet.js")).href}?run=${Date.now()}`
    );
    const oracleActor = await import(
      `${pathToFileURL(path.join(oracleOut, "rom", "actor.js")).href}?run=${Date.now()}`
    );
    const step = candidateModule[profile.candidateExport];
    assert.equal(typeof step, "function", `candidate export ${profile.candidateExport} is missing`);

    const scenarios = deriveBoundaryScenarios(payload, profile);
    for (const scenario of scenarios) {
      const expected = observeOracle(
        oracleActor.createRomActor,
        oracleFamily.createEagleJetAction1Reference,
        scenario.input,
      );
      const actual = observeCandidate(step, scenario.input);
      let passed = true;
      let error = null;
      try {
        assert.deepEqual(actual, expected);
      } catch (comparisonError) {
        passed = false;
        error = comparisonError instanceof Error
          ? comparisonError.message
          : String(comparisonError);
      }
      result.behavior.scenarios.push({
        ...scenario,
        expected,
        actual,
        passed,
        error,
      });
    }
    result.behavior.passed = result.behavior.scenarios.filter((scenario) => scenario.passed).length;
    result.behavior.failed = result.behavior.scenarios.length - result.behavior.passed;
    result.behavior.status = result.behavior.failed === 0 ? "passed" : "failed";
    result.status = result.behavior.status;
    writeJson(verificationPath, result);
    return result;
  } catch (error) {
    result.behavior.blocker = error instanceof Error ? error.message : String(error);
    result.status = "failed";
    writeJson(verificationPath, result);
    return result;
  } finally {
    removeOwnedTemp(resolvedRoot, temp);
  }
}

export function appendAutomaticVerification(reportPath, verificationPath, verification) {
  const marker = "\n## Automatic compilation and behavior verification\n";
  const existing = fs.readFileSync(reportPath, "utf8");
  const base = existing.split(marker)[0].trimEnd();
  const compile = verification.compile.passed ? "passed" : "failed";
  const behavior = verification.behavior.status;
  const total = verification.behavior.scenarios.length;
  const section = `

## Automatic compilation and behavior verification

- Generated TypeScript compilation: **${compile}**
- Automatic behavior comparison: **${behavior}**
- Generated scenarios: ${total}
- Handwritten scenarios: ${verification.handwritten_scenarios}
- Passed scenarios: ${verification.behavior.passed}/${total}
- Independent oracle: ${verification.oracle ?? "unavailable"}
- Machine-readable result: \`${verificationPath}\`
`;
  fs.writeFileSync(reportPath, `${base}${section}`, "utf8");
}
