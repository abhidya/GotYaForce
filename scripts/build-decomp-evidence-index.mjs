#!/usr/bin/env node
import fs from "node:fs";
import path from "node:path";
import { fileURLToPath } from "node:url";

const repoRoot = path.resolve(path.dirname(fileURLToPath(import.meta.url)), "..");
const exportDir = path.join(repoRoot, "research", "decomp", "ghidra-export");
const indexFile = path.join(exportDir, "_index.tsv");
const outDir = path.join(repoRoot, "research", "decomp", "index");
const outJson = path.join(outDir, "function-evidence-index.json");
const outMd = path.join(outDir, "function-evidence-index.md");

const knownInferredNames = new Map([
  ["8002bb14", "battle_frame_target_action_dispatch"],
  ["8002cb20", "mutual_actor_contact_mask_update"],
  ["8002d7c4", "collision_hit_pair_pass_active_vs_borgs"],
  ["8002db58", "collision_hit_pair_pass_active_vs_secondary"],
  ["8002df08", "collision_hit_pair_pass_object_lists"],
  ["8002e2a8", "resolve_hitbox_target_effects_and_damage"],
  ["800300bc", "compute_knockback_launch_direction"],
  ["8003cd5c", "compute_base_damage_formula"],
  ["8003d344", "apply_hp_damage_subtract_clamp"],
  ["800541ac", "active_borg_spawn_init_from_slot_tables"],
  ["80057b78", "active_object_init_from_slot_tables"],
  ["800680d4", "dispatch_slot_action_update"],
  ["80068138", "reset_actor_param_tier"],
  ["8006817c", "apply_actor_param_tier_delta_127"],
  ["800681e4", "apply_actor_param_tier_delta_63"],
  ["8006826c", "refresh_actor_param_tier_table"],
  ["80066298", "lookup_type_category_table"],
  ["8006ab04", "start_forced_move_to_point"],
  ["8006abd4", "react_to_slot_target_object"],
  ["8006ace8", "start_status_reaction_by_side"],
  ["8010d880", "set_slot_action_handler"],
  ["801962c4", "challenge_force_slot_team_setup"],
  ["802807ac", "player_clear_swap_controller_timer"],
  ["80281c38", "death_swap_flow_candidate"],
  ["80297538", "team_player_lookup_band_head"],
  ["802a3938", "team_get_player"],
]);

const topicRules = [
  {
    topic: "challenge-menu-flow",
    modules: ["apps/game/src/main.ts", "apps/game/src/ui/screens", "packages/missions/src/challenge.ts"],
    patterns: [/PTR_DAT_80433934/, /DAT_80436378/, /PTR_DAT_80433930/, /0x15d9/, /0x1653/, /0xcb/],
  },
  {
    topic: "force-setup",
    modules: ["packages/missions/src/challenge.ts", "packages/combat/src/battle.ts", "apps/game/src/ui/screens/SelectForce.ts"],
    patterns: [/cTeam::GetPlayer/, /ClearSwapControllerTimer/, /0x3e4/, /0x3e5/, /0x5a/, /0xa0/, /0xf4/],
  },
  {
    topic: "battle-initialization",
    modules: ["packages/combat/src/battle.ts", "apps/game/src/sim/adapter.ts", "apps/game/src/main.ts"],
    patterns: [/param_9\[999\]/, /param_9 \+ 1000/, /param_9\[0x88\]/, /PTR_DAT_80433934/, /0x164c/],
  },
  {
    topic: "damage",
    modules: ["packages/combat/src/combat.ts", "packages/combat/src/constants.ts", "packages/combat/src/stats.ts"],
    patterns: [/0x1c6/, /0x1c8/, /0x42c/, /zz_003d344_/, /zz_003cd5c_/, /zz_0066298_/, /damage/i],
  },
  {
    topic: "knockback-targeting",
    modules: ["packages/combat/src/combat.ts", "packages/physics/src/index.ts", "apps/game/src/sim/battleScene.ts"],
    patterns: [/zz_00300bc_/, /lock/i, /target/i, /angle/i, /PSVEC/, /PSMTX/, /0x5aa/, /0x5ac/],
  },
  {
    topic: "movement-physics",
    modules: ["packages/combat/src/movement.ts", "packages/physics/src/index.ts", "apps/game/src/sim/battleScene.ts"],
    patterns: [/PSVEC/, /PSMTX/, /0x44/, /0x48/, /0x4c/, /0x568/, /0x56c/, /0x570/, /velocity/i],
  },
  {
    topic: "camera",
    modules: ["apps/game/src/main.ts", "apps/game/src/sim/battleScene.ts", "packages/render/src/index.ts"],
    patterns: [/Camera/, /cCameraManager/, /BaseCamera/, /lookAt/i, /0xa24/, /0xae4/],
  },
  {
    topic: "stage-load-collision",
    modules: ["apps/game/src/sim/adapter.ts", "apps/game/src/main.ts", "packages/formats/src/hit-bin.ts"],
    patterns: [/\bst[0-9a-f]{2}\b/i, /collision/i, /hit[0-9a-f]{3}\.bin/i, /set[0-9a-f]{4}\.arc/i],
  },
  {
    topic: "assets-animation",
    modules: ["packages/formats/src/hsd-anim.ts", "apps/game/src/sim/battleScene.ts", "apps/game/public/models"],
    patterns: [/HSD_/, /JObj/, /AObj/, /FObj/, /Anim/, /pl[0-9a-f]{4}/i, /_mdl\.arc/i, /\.mot\b/i],
  },
  {
    topic: "ui-hud",
    modules: ["apps/game/src/ui", "apps/game/src/ui/hud/BattleHud.ts", "packages/ui/src/index.ts"],
    patterns: [/HUD/i, /font/i, /face/i, /bn[0-9a-f]{4}/i, /0x803b069c/, /0x805f3850/],
  },
  {
    topic: "audio",
    modules: ["packages/audio/src/index.ts", "apps/game/src/main.ts"],
    patterns: [/PlatAudio/, /AIStartDMA/, /sndSeq/, /SFX/i, /ADX/i, /\.adx/i, /Audio/i],
  },
];

if (!fs.existsSync(indexFile)) {
  throw new Error(`missing Ghidra export index: ${rel(indexFile)}`);
}

const indexRows = parseIndex(fs.readFileSync(indexFile, "utf8"));
const functionEntries = new Map(indexRows.map((row) => [row.address, { ...row }]));
const bodies = readBodies();

for (const [address, bodyInfo] of bodies) {
  const entry = functionEntries.get(address) ?? { address, symbolName: bodyInfo.currentName, chunkFile: bodyInfo.chunkFile };
  entry.currentName = bodyInfo.currentName;
  entry.chunkFile = bodyInfo.chunkFile;
  entry.lineStart = bodyInfo.lineStart;
  entry.lineEnd = bodyInfo.lineEnd;
  entry.lineCount = Math.max(0, bodyInfo.lineEnd - bodyInfo.lineStart + 1);
  entry.body = bodyInfo.body;
  functionEntries.set(address, entry);
}

const callableNames = new Map();
for (const entry of functionEntries.values()) {
  for (const name of [entry.currentName, entry.symbolName]) {
    addCallableAlias(callableNames, name, entry.address);
  }
}

const enriched = [];
for (const entry of [...functionEntries.values()].sort((a, b) => a.address.localeCompare(b.address))) {
  const body = entry.body ?? "";
  const topics = topicRules
    .filter((rule) => rule.patterns.some((pattern) => pattern.test(`${entry.currentName ?? ""}\n${body}`)))
    .map((rule) => rule.topic);
  const modules = unique(
    topicRules
      .filter((rule) => topics.includes(rule.topic))
      .flatMap((rule) => rule.modules),
  );

  enriched.push({
    address: `0x${entry.address}`,
    currentFunctionName: entry.currentName ?? entry.symbolName,
    symbolMapName: entry.symbolName,
    inferredName: inferName(entry, topics),
    inferredNameIsHint: true,
    chunkFile: entry.chunkFile,
    sourceRef: `${rel(path.join(exportDir, entry.chunkFile))}:${entry.lineStart ?? 1}`,
    lineStart: entry.lineStart ?? null,
    lineEnd: entry.lineEnd ?? null,
    lineCount: entry.lineCount ?? 0,
    callers: [],
    callees: collectCallees(body, entry.address, callableNames),
    globalReferences: collectGlobals(body),
    globalAccesses: collectGlobalAccesses(body),
    constants: collectConstants(body),
    strings: collectStrings(body),
    assets: collectAssets(body),
    topics,
    relatedWebModules: modules,
  });
}

const byAddress = new Map(enriched.map((entry) => [strip0x(entry.address), entry]));
for (const entry of enriched) {
  for (const callee of entry.callees) {
    const target = byAddress.get(strip0x(callee.address));
    if (target) target.callers.push({ address: entry.address, name: entry.currentFunctionName });
  }
}
for (const entry of enriched) {
  entry.callers.sort((a, b) => a.address.localeCompare(b.address));
  entry.callees.sort((a, b) => a.address.localeCompare(b.address));
}

const report = {
  generatedAt: new Date().toISOString(),
  generatedBy: rel(fileURLToPath(import.meta.url)),
  source: {
    ghidraExportDir: rel(exportDir),
    indexFile: rel(indexFile),
    functionCount: enriched.length,
  },
  warning:
    "inferredName values are local hints only. Verify with callers/callees, constants, globals, strings/assets, traces, or behavior before porting.",
  topicCounts: countTopics(enriched),
  knownAnchors: [...knownInferredNames.entries()].map(([address, inferredName]) => {
    const entry = byAddress.get(address);
    return {
      address: `0x${address}`,
      currentFunctionName: entry?.currentFunctionName ?? null,
      inferredName,
      sourceRef: entry?.sourceRef ?? null,
      callers: entry?.callers.slice(0, 24) ?? [],
      callees: entry?.callees.slice(0, 24) ?? [],
      globalReferences: entry?.globalReferences ?? [],
      topics: entry?.topics ?? [],
      relatedWebModules: entry?.relatedWebModules ?? [],
    };
  }),
  functions: enriched.map(({ body: _body, ...entry }) => entry),
};

fs.mkdirSync(outDir, { recursive: true });
fs.writeFileSync(outJson, `${JSON.stringify(report, null, 2)}\n`);
fs.writeFileSync(outMd, renderMarkdown(report));

console.log("decomp evidence index");
console.log(`functions: ${report.source.functionCount}`);
console.log(`topics: ${Object.keys(report.topicCounts).length}`);
console.log(`wrote ${rel(outJson)}`);
console.log(`wrote ${rel(outMd)}`);

function parseIndex(text) {
  return text
    .trim()
    .split(/\r?\n/)
    .slice(1)
    .map((line) => {
      const [address, symbolName, chunkFile] = line.split("\t");
      return { address: address.toLowerCase(), symbolName, chunkFile };
    })
    .filter((row) => /^[0-9a-f]{8}$/.test(row.address) && row.chunkFile);
}

function readBodies() {
  const out = new Map();
  for (const chunkFile of unique(indexRows.map((row) => row.chunkFile)).sort()) {
    const full = path.join(exportDir, chunkFile);
    const lines = fs.readFileSync(full, "utf8").split(/\r?\n/);
    let current = null;
    for (let i = 0; i < lines.length; i += 1) {
      const match = /^\/\/ ==== ([0-9a-fA-F]{8})  (.*?) ====$/.exec(lines[i]);
      if (match) {
        if (current) finishBody(out, current, i);
        current = {
          address: match[1].toLowerCase(),
          currentName: match[2],
          chunkFile,
          lineStart: i + 1,
          bodyLines: [lines[i]],
        };
      } else if (current) {
        current.bodyLines.push(lines[i]);
      }
    }
    if (current) finishBody(out, current, lines.length);
  }
  return out;
}

function finishBody(out, current, endLineIndex) {
  out.set(current.address, {
    address: current.address,
    currentName: current.currentName,
    chunkFile: current.chunkFile,
    lineStart: current.lineStart,
    lineEnd: endLineIndex,
    body: current.bodyLines.join("\n"),
  });
}

function collectCallees(body, ownAddress, names) {
  if (!body) return [];
  const calls = new Map();
  const re = /\b([A-Za-z_][A-Za-z0-9_]*)\s*\(/g;
  let match;
  while ((match = re.exec(body))) {
    const name = match[1];
    const address = names.get(name);
    if (!address || address === ownAddress) continue;
    calls.set(address, { address: `0x${address}`, name });
  }
  return [...calls.values()];
}

function addCallableAlias(names, name, address) {
  if (typeof name !== "string" || !name) return;
  const aliases = [name, name.replace(/[^A-Za-z0-9_]+/g, "_").replace(/^_+|_+$/g, "")];
  for (const alias of unique(aliases)) {
    if (/^[A-Za-z_][A-Za-z0-9_]*$/.test(alias) && !names.has(alias)) names.set(alias, address);
  }
}

function collectGlobals(body) {
  return unique(body.match(/\b(?:PTR_)?(?:DAT|FLOAT|DOUBLE|PTR_FUN)_[0-9a-fA-F]+\b/g) ?? []).slice(0, 80);
}

function collectGlobalAccesses(body) {
  const accesses = [];
  const re =
    /\b(?:PTR_)?(?:DAT|FLOAT|DOUBLE|PTR_FUN)_[0-9a-fA-F]+(?:\s*\[[^\]\r\n]{1,80}\]|\s*\+\s*(?:0x[0-9a-fA-F]+|\d+))?/g;
  let match;
  while ((match = re.exec(body))) accesses.push(match[0].replace(/\s+/g, " "));
  return unique(accesses).slice(0, 120);
}

function collectConstants(body) {
  const all = body.match(/\b(?:0x[0-9a-fA-F]+|\d+\.\d+|\d+)\b/g) ?? [];
  return unique(all).slice(0, 80);
}

function collectStrings(body) {
  const strings = [];
  for (const match of body.matchAll(/"([^"\r\n]{2,160})"/g)) strings.push(match[1]);
  for (const match of body.matchAll(/\bs_[A-Za-z0-9_.$-]+_[0-9a-fA-F]{8}\b/g)) strings.push(match[0]);
  return unique(strings).slice(0, 80);
}

function collectAssets(body) {
  return unique(
    body.match(
      /\b(?:st[0-9a-f]{2}|pl[0-9a-f]{4}[a-z]?|[A-Za-z0-9_/-]+(?:_mdl\.arc|\.pzz|\.arc|\.tpl|\.bin|\.adx|\.afs|\.mot|\.mdt))\b/gi,
    ) ?? [],
  ).slice(0, 80);
}

function inferName(entry, topics) {
  const known = knownInferredNames.get(entry.address);
  if (known) return known;
  const current = entry.currentName ?? entry.symbolName ?? "";
  if (current && !/^(?:zz_|FUN_)/.test(current)) return current;
  if (topics.length) return `${topics[0]}_candidate_${entry.address}`;
  return null;
}

function countTopics(entries) {
  const counts = {};
  for (const entry of entries) {
    for (const topic of entry.topics) counts[topic] = (counts[topic] ?? 0) + 1;
  }
  return Object.fromEntries(Object.entries(counts).sort(([a], [b]) => a.localeCompare(b)));
}

function renderMarkdown(report) {
  const lines = [];
  lines.push("# Ghidra Function Evidence Index");
  lines.push("");
  lines.push(`Generated: ${report.generatedAt}`);
  lines.push("");
  lines.push("## Warning");
  lines.push("");
  lines.push(report.warning);
  lines.push("");
  lines.push("## Summary");
  lines.push("");
  lines.push(`- Functions indexed: ${report.source.functionCount}`);
  lines.push(`- Source corpus: \`${report.source.ghidraExportDir}\``);
  lines.push(`- JSON: \`${rel(outJson)}\``);
  lines.push("");
  lines.push("## Topic Counts");
  lines.push("");
  lines.push("| Topic | Functions | Related web modules |");
  lines.push("| --- | ---: | --- |");
  for (const [topic, count] of Object.entries(report.topicCounts)) {
    const modules = unique(
      topicRules.filter((rule) => rule.topic === topic).flatMap((rule) => rule.modules),
    );
    lines.push(`| ${topic} | ${count} | ${modules.map((module) => `\`${module}\``).join("<br>")} |`);
  }
  lines.push("");
  lines.push("## Known Porting Anchors");
  lines.push("");
  lines.push("| Address | Current name | Inferred hint | Topics | Source |");
  lines.push("| --- | --- | --- | --- | --- |");
  for (const anchor of report.knownAnchors) {
    lines.push(
      `| ${anchor.address} | \`${anchor.currentFunctionName ?? ""}\` | \`${anchor.inferredName}\` | ${anchor.topics.join(", ")} | \`${anchor.sourceRef ?? ""}\` |`,
    );
  }
  lines.push("");
  lines.push("## Usage");
  lines.push("");
  lines.push("- Query by address to get current name, chunk/line, callers/callees, globals, constants, strings/assets, and related web modules.");
  lines.push("- Treat `inferredName` as a navigation hint only; original-game evidence remains call graph, constants/tables, asset opens, traces, and behavior.");
  lines.push("- For Challenge flow, start from `challenge-menu-flow`, `force-setup`, and `battle-initialization` topics before replacing browser player-facing behavior.");
  lines.push("");
  return `${lines.join("\n")}\n`;
}

function unique(values) {
  return [...new Set(values.filter((value) => value != null && value !== ""))];
}

function strip0x(address) {
  return String(address).replace(/^0x/i, "").toLowerCase();
}

function rel(file) {
  return path.relative(repoRoot, file).replaceAll("\\", "/");
}
