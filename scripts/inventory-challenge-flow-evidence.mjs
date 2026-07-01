#!/usr/bin/env node
import fs from "node:fs";
import path from "node:path";
import { fileURLToPath } from "node:url";

const repoRoot = path.resolve(path.dirname(fileURLToPath(import.meta.url)), "..");
const indexPath = path.join(repoRoot, "research", "decomp", "index", "function-evidence-index.json");
const outJson = path.join(repoRoot, "research", "decomp", "index", "challenge-flow-evidence.json");
const outMd = path.join(repoRoot, "research", "decomp", "index", "challenge-flow-evidence.md");

if (!fs.existsSync(indexPath)) {
  throw new Error(`missing function evidence index: ${rel(indexPath)}; run npm run index:decomp first`);
}

const functionIndex = JSON.parse(fs.readFileSync(indexPath, "utf8"));
const functions = new Map(functionIndex.functions.map((fn) => [fn.address.toLowerCase(), fn]));

const flowSteps = [
  {
    id: "main-menu-challenge-selection",
    label: "main menu -> Challenge Mode selection",
    anchors: selectByAddresses(["0x80195fbc", "0x801962c4", "0x80199da0"]),
    topicFallbacks: selectByTopic("challenge-menu-flow", 8, (fn) => fn.globalReferences.includes("DAT_80436378")),
    supportingArtifacts: artifactRefs(["research/asset-inventory/ui-hud-assets.md"]),
    requiredBeforePorting: [
      "Identify the selected menu mode state variable and transition value that enters Challenge.",
      "Confirm asset opens for title/menu objects/textures before replacing player-facing MainMenu.",
    ],
    currentWebEvidence: refsFor([
      ["apps/game/src/main.ts", "MainMenu -> (challenge)"],
      ["apps/game/src/ui/screens/MainMenu.ts", "The real game renders this as a 3D desk diorama"],
    ]),
  },
  {
    id: "force-setup",
    label: "Challenge selection -> force/player setup",
    anchors: selectByAddresses(["0x802a3938", "0x802807ac", "0x80281c38", "0x800541ac", "0x80057b78"]),
    topicFallbacks: selectByTopic("force-setup", 8, (fn) => fn.globalReferences.includes("PTR_DAT_80433934")),
    supportingArtifacts: artifactRefs(["research/asset-inventory/borg-assets.md", "research/animation-actions/borg-action-assets.md"]),
    requiredBeforePorting: [
      "Trace slot/team table writes for PTR_DAT_80433934 offsets 0x10, 0x20, 0x32, 0x3e, 0x5a, 0xa0, and 0xcb.",
      "Confirm the original ordered-force spawn/death swap path before changing Challenge roster behavior.",
    ],
    currentWebEvidence: refsFor([
      ["packages/missions/src/challenge.ts", "FIGHT ALONE"],
      ["apps/game/src/ui/screens/SelectForce.ts", "SELECT A FORCE"],
      ["apps/game/src/ui/screens/ForceBuilder.ts", "ForceBuilder"],
    ]),
  },
  {
    id: "stage-load-flow",
    label: "force setup -> stage/load flow",
    anchors: selectByTopic("stage-load-collision", 10),
    topicFallbacks: selectByTopic("assets-animation", 6, (fn) => fn.assets.some((asset) => /^st[0-9a-f]{2}$/i.test(asset))),
    supportingArtifacts: artifactRefs([
      "research/decomp/index/archive-load-xrefs.md",
      "research/traces/GG4E/challenge-battle1-memory-evidence.md",
      "research/asset-inventory/stage-code-evidence.md",
      "research/asset-inventory/stage-geometry-collision.md",
      "research/asset-inventory/stage-lighting-render-state.md",
    ]),
    requiredBeforePorting: [
      "Break/trace archive open path for Challenge battle 1 and record the selected st## ids.",
      "Only map arena names to st## after a DOL/load trace or direct data table proves the mapping.",
    ],
    currentWebEvidence: refsFor([
      ["apps/game/src/sim/adapter.ts", "DEFAULT_ARENA_STAGE"],
      ["apps/game/src/sim/adapter.ts", "normalized === \"challenge\""],
      ["apps/game/src/main.ts", "async function loadStage"],
    ]),
  },
  {
    id: "battle-initialization",
    label: "stage/load flow -> battle initialization",
    anchors: selectByAddresses(["0x800541ac", "0x80057b78", "0x8002e2a8"]),
    topicFallbacks: selectByTopic("battle-initialization", 8, (fn) => fn.globalReferences.includes("PTR_DAT_80433934")),
    supportingArtifacts: artifactRefs([
      "research/decomp/index/archive-load-xrefs.md",
      "research/traces/GG4E/challenge-battle1-memory-evidence.md",
      "research/decomp/data/type-category-remap-802f2e28.json",
    ]),
    requiredBeforePorting: [
      "Map active borg object fields copied from slot table into combat runtime shape.",
      "Preserve object+0x88 as slot/team state and object+1000 as the separate type-category source.",
    ],
    currentWebEvidence: refsFor([
      ["packages/combat/src/battle.ts", "export function createBattle"],
      ["apps/game/src/sim/adapter.ts", "convertBattleConfig"],
      ["apps/game/src/main.ts", "const battle = createBattle"],
    ]),
  },
  {
    id: "hud-gameplay",
    label: "battle initialization -> HUD/gameplay",
    anchors: selectByAddresses(["0x8003d344", "0x8003cd5c", "0x80066298", "0x800300bc"]),
    topicFallbacks: [
      ...selectByTopic("damage", 8),
      ...selectByTopic("knockback-targeting", 8, (fn) => fn.address !== "0x800300bc"),
    ],
    supportingArtifacts: artifactRefs([
      "research/decomp/data/type-multiplier-matrix-802c5d60.json",
      "research/asset-inventory/common-battle-data.md",
      "research/asset-inventory/weapons-effects-projectiles.md",
    ]),
    requiredBeforePorting: [
      "Port damage from zz_003cd5c_ only after table inputs and object+1000 category source are confirmed.",
      "Port knockback as computed direction from zz_00300bc_, not as flat tuned scalar.",
      "Keep HUD mirrors separate from authoritative HP fields.",
    ],
    currentWebEvidence: refsFor([
      ["packages/combat/src/combat.ts", "function applyHit"],
      ["packages/combat/src/constants.ts", "TUNED"],
      ["apps/game/src/ui/hud/BattleHud.ts", "BattleHud"],
    ]),
  },
  {
    id: "victory-defeat-progression",
    label: "HUD/gameplay -> victory/defeat/progression",
    anchors: selectByAddresses(["0x802807ac", "0x80281c38"]),
    topicFallbacks: [],
    supportingArtifacts: artifactRefs(["packages/missions/src/challenge.ts"]),
    requiredBeforePorting: [
      "Trace player swap/death transition around cPlayer::ClearSwapControllerTimer and adjacent functions.",
      "Confirm original Challenge win/loss branch and next-battle counter before replacing Results progression.",
    ],
    currentWebEvidence: refsFor([
      ["packages/missions/src/challenge.ts", "next(result: BattleResults)"],
      ["apps/game/src/main.ts", "function advanceRun"],
      ["apps/game/src/ui/screens/Results.ts", "Results"],
    ]),
  },
];

const report = {
  generatedAt: new Date().toISOString(),
  generatedBy: rel(fileURLToPath(import.meta.url)),
  sourceIndex: rel(indexPath),
  principle:
    "Do not replace player-facing Challenge flow with fake menus/stages/mechanics. Each step below must be driven by original functions, data tables, asset opens, traces, or behavior.",
  flowSteps: flowSteps.map((step) => ({
    ...step,
    anchors: compactFunctions(step.anchors),
    topicFallbacks: compactFunctions(dedupFunctions(step.topicFallbacks).filter((fn) => !step.anchors.includes(fn)).slice(0, 12)),
  })),
};

fs.writeFileSync(outJson, `${JSON.stringify(report, null, 2)}\n`);
fs.writeFileSync(outMd, renderMarkdown(report));

console.log("challenge flow evidence");
console.log(`steps: ${report.flowSteps.length}`);
console.log(`wrote ${rel(outJson)}`);
console.log(`wrote ${rel(outMd)}`);

function selectByAddresses(addresses) {
  return addresses.map((address) => functions.get(address.toLowerCase())).filter(Boolean);
}

function selectByTopic(topic, limit, predicate = () => true) {
  return functionIndex.functions
    .filter((fn) => fn.topics.includes(topic))
    .filter(predicate)
    .sort((a, b) => {
      const scoreA = bScore(a);
      const scoreB = bScore(b);
      if (scoreB !== scoreA) return scoreB - scoreA;
      return a.address.localeCompare(b.address);
    })
    .slice(0, limit);
}

function bScore(fn) {
  return fn.callers.length * 3 + fn.callees.length * 2 + fn.globalReferences.length + fn.assets.length * 2;
}

function compactFunctions(items) {
  return dedupFunctions(items).map((fn) => ({
    address: fn.address,
    currentFunctionName: fn.currentFunctionName,
    inferredName: fn.inferredName,
    sourceRef: fn.sourceRef,
    callers: fn.callers.slice(0, 12),
    callees: fn.callees.slice(0, 12),
    globalReferences: fn.globalReferences.slice(0, 20),
    globalAccesses: fn.globalAccesses.slice(0, 20),
    constants: fn.constants.slice(0, 30),
    strings: fn.strings.slice(0, 20),
    assets: fn.assets.slice(0, 20),
    topics: fn.topics,
    relatedWebModules: fn.relatedWebModules,
  }));
}

function dedupFunctions(items) {
  const seen = new Set();
  const out = [];
  for (const item of items) {
    if (!item || seen.has(item.address)) continue;
    seen.add(item.address);
    out.push(item);
  }
  return out;
}

function refsFor(pairs) {
  return pairs.map(([file, needle]) => {
    const full = path.join(repoRoot, file);
    if (!fs.existsSync(full)) return { file, needle, sourceRef: null };
    const text = fs.readFileSync(full, "utf8");
    const line = text.split(/\r?\n/).findIndex((candidate) => candidate.includes(needle)) + 1;
    return {
      file,
      needle,
      sourceRef: line > 0 ? `${file}:${line}` : null,
    };
  });
}

function artifactRefs(files) {
  return files.map((file) => ({ path: file, exists: fs.existsSync(path.join(repoRoot, file)) }));
}

function renderMarkdown(report) {
  const lines = [];
  lines.push("# Challenge Flow Evidence Map");
  lines.push("");
  lines.push(`Generated: ${report.generatedAt}`);
  lines.push("");
  lines.push("## Principle");
  lines.push("");
  lines.push(report.principle);
  lines.push("");
  for (const step of report.flowSteps) {
    lines.push(`## ${step.label}`);
    lines.push("");
    lines.push("### Original Function Anchors");
    lines.push("");
    if (step.anchors.length) {
      lines.push("| Address | Current name | Inferred hint | Topics | Source |");
      lines.push("| --- | --- | --- | --- | --- |");
      for (const fn of step.anchors) {
        lines.push(`| ${fn.address} | \`${fn.currentFunctionName}\` | \`${fn.inferredName ?? ""}\` | ${fn.topics.join(", ")} | \`${fn.sourceRef}\` |`);
      }
    } else {
      lines.push("No original C function anchor is confirmed by the current index for this step.");
    }
    lines.push("");
    if (step.supportingArtifacts.length) {
      lines.push("### Supporting Artifacts");
      lines.push("");
      for (const artifact of step.supportingArtifacts) {
        lines.push(`- \`${artifact.path}\`${artifact.exists ? "" : " (missing)"}`);
      }
      lines.push("");
    }
    if (step.topicFallbacks.length) {
      lines.push("### Topic Fallback Candidates");
      lines.push("");
      for (const fn of step.topicFallbacks.slice(0, 8)) {
        lines.push(`- ${fn.address} \`${fn.currentFunctionName}\` at \`${fn.sourceRef}\`; globals ${fn.globalReferences.slice(0, 5).join(", ") || "none"}.`);
      }
      lines.push("");
    }
    lines.push("### Current Web Evidence");
    lines.push("");
    for (const ref of step.currentWebEvidence) {
      lines.push(`- \`${ref.sourceRef ?? ref.file}\` contains \`${ref.needle}\`.`);
    }
    lines.push("");
    lines.push("### Required Before Player-Facing Port");
    lines.push("");
    for (const item of step.requiredBeforePorting) lines.push(`- ${item}`);
    lines.push("");
  }
  return `${lines.join("\n")}\n`;
}

function rel(file) {
  return path.relative(repoRoot, file).replaceAll("\\", "/");
}
