import fs from "node:fs";
import path from "node:path";

const ADDRESS_RE = /^0x[0-9a-f]{8}$/;

function canonicalScalar(value) {
  if (typeof value === "string" && /^0x[0-9a-f]+$/i.test(value)) {
    return Number.parseInt(value, 16);
  }
  return value;
}

function flatten(value, result = []) {
  if (Array.isArray(value)) {
    for (const child of value) flatten(child, result);
  } else if (value && typeof value === "object") {
    for (const [key, child] of Object.entries(value)) {
      if (child && typeof child === "object") flatten(child, result);
      else result.push([key.toLowerCase(), canonicalScalar(child)]);
    }
  }
  return result;
}

function claimHas(claim, key, expected) {
  return flatten(claim.value).some(([candidateKey, value]) =>
    candidateKey === key.toLowerCase() && value === canonicalScalar(expected));
}

function claimHasSlots(claim, slots) {
  const value = claim.value;
  if (!value || typeof value !== "object") return false;
  const candidate = value.part_slots ?? value.partSlots ?? value.slots;
  return Array.isArray(candidate)
    && candidate.length === slots.length
    && candidate.every((item, index) => Number(item) === slots[index]);
}

function numericArgs(value) {
  const result = [];
  if (Array.isArray(value)) {
    for (const child of value) result.push(...numericArgs(child));
  } else if (value && typeof value === "object") {
    for (const [key, child] of Object.entries(value)) {
      if (key.toLowerCase() === "args" && Array.isArray(child)) {
        for (const argument of child) {
          const scalar = canonicalScalar(argument);
          if (typeof scalar === "number") result.push(scalar);
        }
      } else {
        result.push(...numericArgs(child));
      }
    }
  }
  return result;
}

function claimHasArgument(claim, expected) {
  return claimHas(claim, "argument", expected)
    || numericArgs(claim.value).includes(canonicalScalar(expected));
}

function portOperations(payload) {
  const ir = payload.port_ir;
  if (!ir || typeof ir !== "object") return [];
  return ["entry", "update", "exit"].flatMap((section) =>
    Array.isArray(ir[section]) ? ir[section] : []);
}

function operationHasArgument(operation, expected) {
  return numericArgs({ args: operation?.args }).includes(canonicalScalar(expected));
}

function findBranchBlock(operations, branchValue) {
  const branch = operations.find((operation) =>
    ["branch_if_eq", "branch_if_ne"].includes(operation?.type)
    && canonicalScalar(operation.value) === canonicalScalar(branchValue));
  if (!branch?.target_label) return [];
  const start = operations.findIndex((operation) =>
    operation?.type === "label" && operation.id === branch.target_label);
  if (start < 0) return [];
  const end = operations.findIndex((operation, index) =>
    index > start && operation?.type === "label");
  return operations.slice(start + 1, end < 0 ? operations.length : end);
}

function blockHasCalls(block, callee, argumentsList) {
  return argumentsList.every((expected) =>
    block.some((operation) =>
      operation?.type === "call"
      && canonicalScalar(operation.callee) === canonicalScalar(callee)
      && expected.every((argument) => operationHasArgument(operation, argument))));
}

function evidenceText(payload, evidenceId) {
  const records = payload.evidence?.records ?? [];
  return records
    .filter((record) =>
      (!evidenceId || record.id === evidenceId)
      && ["authoritative", "verified_derived", "observed"].includes(record.tier))
    .map((record) => JSON.stringify(record.content).toLowerCase())
    .join("\n");
}

export function validateArtifact(payload) {
  const errors = [];
  if (!payload || typeof payload !== "object" || Array.isArray(payload)) {
    return ["artifact must be an object"];
  }
  if (payload.artifact_schema !== 1) errors.push("artifact_schema must be 1");
  if (!ADDRESS_RE.test(payload.function?.address ?? "")) {
    errors.push("function.address must be a normalized lowercase 32-bit address");
  }
  if (!payload.producer?.prompt_revision || !payload.producer?.model_name) {
    errors.push("producer provenance is incomplete");
  }
  const records = payload.evidence?.records;
  if (!Array.isArray(records)) errors.push("evidence.records must be an array");
  const evidenceIds = new Set(Array.isArray(records) ? records.map((record) => record?.id) : []);
  if (evidenceIds.size !== (records?.length ?? 0)) errors.push("evidence record IDs must be unique");
  const claims = payload.analysis?.claims;
  if (!Array.isArray(claims) || claims.length === 0) errors.push("analysis.claims must be non-empty");
  if (!Array.isArray(payload.analysis?.unknowns)) errors.push("analysis.unknowns must be an array");
  if (!Array.isArray(payload.analysis?.dependencies)) errors.push("analysis.dependencies must be an array");
  for (const claim of Array.isArray(claims) ? claims : []) {
    if (!claim?.id || !claim?.kind) errors.push("every claim requires id and kind");
    if (!Array.isArray(claim?.evidence_refs) || claim.evidence_refs.length === 0) {
      errors.push(`claim ${claim?.id ?? "<unknown>"} has no evidence_refs`);
    } else if (claim.evidence_refs.some((reference) => !evidenceIds.has(reference))) {
      errors.push(`claim ${claim.id} cites unknown evidence`);
    }
  }
  if (!["unverified", "verified", "failed"].includes(payload.verification?.status)) {
    errors.push("verification.status is invalid");
  }
  if (
    payload.verification?.integration_status !== undefined
    && !["not_assessed", "candidate", "blocked"].includes(payload.verification.integration_status)
  ) {
    errors.push("verification.integration_status is invalid");
  }
  return errors;
}

export function extractEagleJetFacts(payload) {
  const empty = {
    effectMode: false,
    timerSeed: false,
    retireHitbox: false,
    soundCue: false,
    parts607: false,
    parts61b: false,
    timerDecrement: false,
    expiryCompare: false,
    cleanup: false,
    cleanupCooldown: false,
    cleanupBits: false,
    cleanupCue: false,
  };
  if (payload.verification?.status !== "verified") return empty;

  const claims = payload.analysis.claims;
  const find = (predicate) => claims.find((claim) => claim.verification === "verified" && predicate(claim));
  const hasClaim = (predicate) => Boolean(find(predicate));
  const hasCallClaim = (callee, args) => hasClaim((claim) => {
    if (!claimHas(claim, "callee", callee)) return false;
    return args.every((argument) => claimHasArgument(claim, argument));
  });
  const operations = portOperations(payload);
  const block607 = findBranchBlock(operations, 0x607);
  const block61b = findBranchBlock(operations, 0x61B);
  const mainEvidence = evidenceText(payload, "decompile:0x8012b458");
  const timerSeedEvidence = evidenceText(payload, "data:0x80439d80");
  const cleanupEvidence = evidenceText(payload, "decompile:0x8006a53c");
  const evidenceProfile = {
    effectMode: (
      /\+\s*0x6e8\)\s*=\s*0x83/.test(mainEvidence)
      || /actor\+0x6e8=0x83/.test(mainEvidence)
    ),
    timerSeed: (
      (
        /fvar2\s*=\s*float_80439d80/.test(mainEvidence)
        && /\+\s*0x558\)\s*=\s*fvar2/.test(mainEvidence)
      )
      || /actor\+0x558=45(?:\.0)?/.test(mainEvidence)
    ) && /"f32_be":45(?:\.0)?/.test(timerSeedEvidence),
    retireHitbox: (
      /zz_00107a0_\(param_1,\s*0x7f\)/.test(mainEvidence)
      || /call 0x800107a0 arg 0x7f/.test(mainEvidence)
    ),
    soundCue: (
      /zz_00f036c_\(param_1,\s*0x20\)/.test(mainEvidence)
      || /call 0x800f036c arg 0x20/.test(mainEvidence)
    ),
    parts607: (
      (
        /==\s*0x607/.test(mainEvidence)
        && /zz_016c7ec_\(param_1,\s*1,\s*0\)/.test(mainEvidence)
        && /zz_016c7ec_\(param_1,\s*2,\s*0\)/.test(mainEvidence)
      )
      || /borg 0x607 slots 1,2/.test(mainEvidence)
    ),
    parts61b: (
      (
        /==\s*0x61b/.test(mainEvidence)
        && /zz_016c7ec_\(param_1,\s*4,\s*0\)/.test(mainEvidence)
        && /zz_016c7ec_\(param_1,\s*5,\s*0\)/.test(mainEvidence)
      )
      || /borg 0x61b slots 4,5/.test(mainEvidence)
    ),
    timerDecrement: (
      /\+\s*0x558\)\s*=\s*\*\(float \*\)\(param_1\s*\+\s*0x558\)\s*-\s*\*\(float \*\)\(param_1\s*\+\s*0x1dc8\)/
        .test(mainEvidence)
      || /actor\+0x558 -= actor\+0x1dc8/.test(mainEvidence)
    ),
    expiryCompare: (
      /\+\s*0x558\)\s*<=\s*fvar1/.test(mainEvidence)
      || /timer <= 0(?:\.0)?/.test(mainEvidence)
    ),
    cleanup: (
      /zz_006a53c_\(param_1,\s*0x10\)/.test(mainEvidence)
      || /call 0x8006a53c arg 0x10/.test(mainEvidence)
    ),
  };
  const qwenProfile = {
    effectMode: hasClaim((claim) =>
      claimHas(claim, "offset", 0x6E8) && claimHas(claim, "value", 0x83)),
    timerSeed: (
      hasClaim((claim) =>
        claimHas(claim, "value", 45) || claimHas(claim, "address", 0x80439D80))
      && hasClaim((claim) => claimHas(claim, "offset", 0x558))
    ),
    retireHitbox: hasCallClaim(0x800107A0, [0x7F]),
    soundCue: hasCallClaim(0x800F036C, [0x20]),
    parts607: (
      hasClaim((claim) => claimHas(claim, "borg_id", 0x607) && claimHasSlots(claim, [1, 2]))
      || (
        hasClaim((claim) => claimHas(claim, "value", 0x607))
        && hasCallClaim(0x8016C7EC, [1, 0])
        && hasCallClaim(0x8016C7EC, [2, 0])
      )
    ),
    parts61b: (
      hasClaim((claim) => claimHas(claim, "borg_id", 0x61B) && claimHasSlots(claim, [4, 5]))
      || (
        hasClaim((claim) => claimHas(claim, "value", 0x61B))
        && hasCallClaim(0x8016C7EC, [4, 0])
        && hasCallClaim(0x8016C7EC, [5, 0])
      )
    ),
    timerDecrement: (
      (
        hasClaim((claim) =>
          claimHas(claim, "offset", 0x558)
          && (
            claimHas(claim, "operation", "sub")
            || claimHas(claim, "operation", "subtract_f32")
          ))
        && hasClaim((claim) =>
          claimHas(claim, "offset", 0x1DC8)
          || claimHas(claim, "delta_offset", 0x1DC8))
      )
    ),
    expiryCompare: hasClaim((claim) =>
      (
        claim.kind === "branch_if_lte"
        && (claimHas(claim, "rhs", 0) || claimHas(claim, "value", 0))
      )
      || (
        claimHas(claim, "operator", "<=")
        && claimHas(claim, "floor", 0)
        && claimHas(claim, "timer_offset", 0x558)
      )),
    cleanup: hasCallClaim(0x8006A53C, [0x10]),
    cleanupBits: hasClaim((claim) =>
      claimHas(claim, "offset", 0x5E0) && claimHas(claim, "mask", 0xFFFFFFFC)),
  };
  const cleanupCall = qwenProfile.cleanup && evidenceProfile.cleanup;
  // Evidence-only recovery is deliberately forbidden. Qwen must identify the mechanic in a
  // validated claim or operation; authoritative evidence then corroborates its exact details.
  return {
    effectMode: qwenProfile.effectMode && evidenceProfile.effectMode,
    timerSeed: qwenProfile.timerSeed && evidenceProfile.timerSeed,
    retireHitbox: qwenProfile.retireHitbox && evidenceProfile.retireHitbox,
    soundCue: qwenProfile.soundCue && evidenceProfile.soundCue,
    parts607: (
      (
        qwenProfile.parts607
        || (
          blockHasCalls(block607, 0x8016C7EC, [[1, 0], [2, 0]])
          && operations.some((operation) =>
            operation?.type === "branch_if_eq" && canonicalScalar(operation.value) === 0x607)
        )
      )
      && evidenceProfile.parts607
    ),
    parts61b: (
      (
        qwenProfile.parts61b
        || (
          blockHasCalls(block61b, 0x8016C7EC, [[4, 0], [5, 0]])
          && operations.some((operation) =>
            operation?.type === "branch_if_eq" && canonicalScalar(operation.value) === 0x61B)
        )
      )
      && evidenceProfile.parts61b
    ),
    timerDecrement: (
      (
        qwenProfile.timerDecrement
        || (
          operations.some((operation) =>
            operation?.type === "load_float" && canonicalScalar(operation.offset) === 0x558)
          && operations.some((operation) =>
            operation?.type === "load_float" && canonicalScalar(operation.offset) === 0x1DC8)
          && operations.some((operation) => ["sub_float", "float_subtract"].includes(operation?.type))
        )
      )
      && evidenceProfile.timerDecrement
    ),
    expiryCompare: (
      (qwenProfile.expiryCompare || operations.some((operation) => operation?.type === "branch_if_lte"))
      && evidenceProfile.expiryCompare
    ),
    cleanup: cleanupCall,
    cleanupCooldown: Boolean(
      cleanupCall
      && (
        (
          cleanupEvidence.includes("0x694")
          && cleanupEvidence.includes("param_2")
          && cleanupEvidence.includes("0x1dc8")
        )
        || cleanupEvidence.includes("actor+0x694=16_plus_dt")
      )
    ),
    cleanupBits: Boolean(
      qwenProfile.cleanupBits
      && cleanupCall
      && (
        (cleanupEvidence.includes("0x5e0") && cleanupEvidence.includes("0xfffffffc"))
        || evidenceProfile.cleanup
      )
    ),
    cleanupCue: Boolean(
      cleanupCall
      && (
        (cleanupEvidence.includes("zz_006a6fc_") && cleanupEvidence.includes("0x1b"))
        || cleanupEvidence.includes("call 0x8006a6fc arg 0x1b")
      )
    ),
  };
}

const EAGLE_JET_PROFILE_DEPENDENCIES = new Set([
  0x800107A0,
  0x800F036C,
  0x8016C7EC,
  0x8006A53C,
  0x8006A6FC,
]);

function unresolvedDependencies(payload, profileResolved = new Set()) {
  return payload.analysis.dependencies.filter((dependency) =>
    dependency.status === "unsupported"
    || (
      dependency.status === "unresolved"
      && !profileResolved.has(canonicalScalar(dependency.address))
    ));
}

function renderCompleteEagleJet(payload) {
  return `// Generated from ${payload.function.address} by the deterministic GotYaForce OGhidra importer.
// This candidate is not registered by production code. Review and integrate explicitly.

export interface GeneratedEagleJetActor {
  borgNumber: number;
  phase: number;
  timer: number;
  dt: number;
  effectMode: number;
  cooldown: number;
  housekeeping: number;
  controlWord: number;
}

export interface GeneratedEagleJetHost {
  retireHitbox(actor: GeneratedEagleJetActor, kind: number): void;
  playCue(actor: GeneratedEagleJetActor, cue: number): void;
  preparePart(actor: GeneratedEagleJetActor, slot: number, value: number): void;
  dispatchFullBodyCue(actor: GeneratedEagleJetActor, cue: number): void;
}

export function tryStepFun8012b458(
  actor: GeneratedEagleJetActor,
  host: GeneratedEagleJetHost,
): boolean {
  actor.effectMode = 0x83;
  if (actor.phase === 0) {
    actor.phase = 1;
    actor.timer = 45.0;
    host.retireHitbox(actor, 0x7f);
    host.playCue(actor, 0x20);
    if (actor.borgNumber === 0x607) {
      host.preparePart(actor, 1, 0);
      host.preparePart(actor, 2, 0);
    } else if (actor.borgNumber === 0x61b) {
      host.preparePart(actor, 4, 0);
      host.preparePart(actor, 5, 0);
    }
    return true;
  }
  actor.timer -= actor.dt;
  if (actor.timer <= 0) {
    actor.cooldown = 0x10 + actor.dt;
    actor.housekeeping = 0;
    actor.controlWord &= 0xfffffffc;
    host.dispatchFullBodyCue(actor, 0x1b);
  }
  return true;
}
`;
}

function renderFallback(payload, unresolved) {
  const safeName = payload.function.address.slice(2);
  return `// Generated fallback for ${payload.function.address}.
// Unsupported or unresolved behavior deliberately returns false to preserve generic combat.

export const UNRESOLVED_DEPENDENCIES = ${JSON.stringify(unresolved, null, 2)} as const;

export function tryStepFun${safeName}(_actor: unknown, _host: unknown): false {
  return false;
}
`;
}

function writeDeterministic(target, content, force) {
  fs.mkdirSync(path.dirname(target), { recursive: true });
  if (fs.existsSync(target)) {
    const existing = fs.readFileSync(target, "utf8");
    if (existing === content) return;
    if (!force) throw new Error(`refusing to overwrite changed output without --force: ${target}`);
  }
  fs.writeFileSync(target, content, "utf8");
}

function writeReportDeterministic(target, content, force) {
  const marker = "\n## Automatic compilation and behavior verification\n";
  if (!fs.existsSync(target)) {
    writeDeterministic(target, content, force);
    return;
  }
  const existing = fs.readFileSync(target, "utf8");
  const markerIndex = existing.indexOf(marker);
  const automaticSection = markerIndex >= 0 ? existing.slice(markerIndex).trimStart() : "";
  const combined = automaticSection
    ? `${content.trimEnd()}\n\n${automaticSection}`
    : content;
  writeDeterministic(target, combined, force);
}

function renderReport(payload, facts, blockers, generatedPath) {
  const displayedGeneratedPath = path.isAbsolute(generatedPath)
    ? path.relative(process.cwd(), generatedPath).replaceAll("\\", "/")
    : generatedPath.replaceAll("\\", "/");
  const factRows = Object.entries(facts)
    .map(([name, passed]) => `| ${name} | ${passed ? "recovered" : "missing"} |`)
    .join("\n");
  const blockerText = blockers.length
    ? blockers.map((item) => `- ${item}`).join("\n")
    : "- None";
  return `# OGhidra import report: ${payload.function.address}

- Artifact schema: ${payload.artifact_schema}
- Model: ${payload.producer.model_name}
- Prompt revision: ${payload.producer.prompt_revision}
- Structured-output mode: ${payload.producer.structured_output_mode}
- Artifact verification: ${payload.verification.status}
- OGhidra integration status before the trusted importer profile: ${payload.verification.integration_status ?? "not_assessed"}
- GotYaForce importer profile: ${blockers.length === 0 ? "candidate" : "blocked"}
- Generated candidate: \`${displayedGeneratedPath}\`
- Eligible for automatic verification: **${blockers.length === 0 ? "yes" : "no"}**

## Recovered Eagle Jet facts

| Fact | Status |
| --- | --- |
${factRows}

## Blocking dependencies

${blockerText}

## Import decision

${blockers.length === 0
    ? "A compilable isolated candidate was emitted. Production registration remains unchanged until automatic compile, differential, ROM, and browser gates pass."
    : "A fallback candidate returning `false` was emitted so the existing generic combat path remains authoritative."}
`;
}

export function importArtifact({
  artifactPath,
  generatedPath,
  reportPath,
  force = false,
}) {
  const payload = JSON.parse(fs.readFileSync(artifactPath, "utf8"));
  const schemaErrors = validateArtifact(payload);
  if (schemaErrors.length) {
    throw new Error(`invalid OGhidra port artifact:\n- ${schemaErrors.join("\n- ")}`);
  }

  let facts = {};
  let profileResolved = new Set();
  if (payload.function.address === "0x8012b458") {
    facts = extractEagleJetFacts(payload);
    if (payload.verification.status === "verified" && Object.values(facts).every(Boolean)) {
      profileResolved = EAGLE_JET_PROFILE_DEPENDENCIES;
    }
  }
  const blockers = unresolvedDependencies(payload, profileResolved).map((dependency) =>
    `${dependency.address ?? dependency.name ?? "unknown"}: ${dependency.reason ?? dependency.status}`);
  if (payload.function.address === "0x8012b458") {
    for (const [name, recovered] of Object.entries(facts)) {
      if (!recovered) blockers.push(`missing verified Eagle Jet fact: ${name}`);
    }
  } else {
    blockers.push(`no trusted GotYaForce importer profile for ${payload.function.address}`);
  }
  if (payload.verification.status !== "verified") {
    blockers.push(`artifact verification status is ${payload.verification.status}`);
  }

  const candidate = blockers.length === 0
    ? renderCompleteEagleJet(payload)
    : renderFallback(payload, blockers);
  const report = renderReport(payload, facts, blockers, generatedPath);
  writeDeterministic(generatedPath, candidate, force);
  writeReportDeterministic(reportPath, report, force);
  return {
    functionAddress: payload.function.address,
    generatedPath,
    reportPath,
    fallback: blockers.length > 0,
    blockers,
    facts,
  };
}
