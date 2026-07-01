#!/usr/bin/env node
import fs from "node:fs";
import path from "node:path";

const repoRoot = path.resolve(".");
const region = "GG4E";

const paths = {
  sourceRoot: path.join(repoRoot, "user-data", region, "afs_data", "root"),
  modelsRoot: path.join(repoRoot, "apps", "game", "public", "models"),
  borgData: path.join(repoRoot, "packages", "assets", "data", "borgs.json"),
  pzzMemberManifest: path.join(repoRoot, "research", "asset-inventory", "pzz-member-extraction-manifest.json"),
  outputDir: path.join(repoRoot, "research", "animation-actions"),
};

const outputJson = path.join(paths.outputDir, "borg-action-assets.json");
const outputMarkdown = path.join(paths.outputDir, "borg-action-assets.md");
const priorityBorgs = ["pl0615", "pl0109"];
const actionNames = [
  "idle",
  "walk/run",
  "jump",
  "fly/air",
  "dash",
  "shoot/gun",
  "beam",
  "melee/sword",
  "hit",
  "death",
  "spawn",
];

for (const input of [paths.sourceRoot, paths.modelsRoot, paths.borgData]) mustExist(input);

const metadata = readMetadata();
const pzzMemberManifest = readJsonIfExists(paths.pzzMemberManifest, { records: [] });
const pzzMembersByBorg = groupPzzMembersByBorg(pzzMemberManifest.records ?? []);
const records = discoverBorgIds(metadata).map((id) => buildRecord(id, metadata.get(id))).sort(compareRecords);
const inventory = {
  schema: "gotyaforce.borgActionAssetInventory.v1",
  generatedAt: new Date().toISOString(),
  generatedBy: rel(new URL(import.meta.url).pathname),
  scope: {
    purpose:
      "Inventory actual source/exported borg animation assets and propose action mapping candidates without handcoding gameplay behavior.",
    region,
    actionNames,
    priorityBorgs,
    constraints: [
      "Candidates are derived from exported clip labels, structural bank/slot metadata, source MOT files, and borg metadata.",
      "A candidate is not proof of gameplay semantics; it is an asset mapping lead for a 1:1 Gotcha Force port.",
      "This report does not edit runtime files and does not invent missing animation behavior.",
    ],
  },
  inputs: {
    sourceRoot: rel(paths.sourceRoot),
    modelsRoot: rel(paths.modelsRoot),
    borgData: rel(paths.borgData),
    relatedScriptsInspected: [
      "scripts/inventory-borg-assets.mjs",
      "scripts/export-all-borg-animations.mjs",
      "scripts/bake-all-borg-anims.mjs",
      "scripts/validate-borg-animation-actions.mjs",
      "scripts/extract-pzz-members.mjs",
    ],
    pzzMemberManifest: fs.existsSync(paths.pzzMemberManifest) ? rel(paths.pzzMemberManifest) : null,
  },
  summary: summarize(records),
  priority: records.filter((record) => priorityBorgs.includes(record.id)),
  records,
};

fs.mkdirSync(paths.outputDir, { recursive: true });
writeJson(outputJson, inventory);
fs.writeFileSync(`${outputMarkdown}.tmp`, renderMarkdown(inventory), "utf8");
fs.renameSync(`${outputMarkdown}.tmp`, outputMarkdown);

console.log("borg action asset inventory");
console.log(`records: ${inventory.summary.totalRecords}`);
console.log(`with source MOT: ${inventory.summary.withSourceMot}`);
console.log(`with anim_index: ${inventory.summary.withAnimIndex}`);
console.log(`exported clips from indexes: ${inventory.summary.indexedClipCount}`);
console.log(`source MOT structural clips: ${inventory.summary.sourceMotClipCount}`);
console.log(`PZZ member records joined: ${inventory.summary.pzzMemberRecordCount}`);
console.log(`priority: ${priorityBorgs.join(", ")}`);
console.log(`wrote ${rel(outputJson)}`);
console.log(`wrote ${rel(outputMarkdown)}`);

function readMetadata() {
  const parsed = readJson(paths.borgData);
  if (!parsed || !Array.isArray(parsed.borgs)) fail(`expected borgs array in ${rel(paths.borgData)}`);
  return new Map(
    parsed.borgs
      .filter((borg) => normalizeBorgId(borg.id))
      .map((borg) => [
        normalizeBorgId(borg.id),
        {
          name: borg.name ?? null,
          number: borg.number ?? null,
          energy: numberOrNull(borg.energy),
          tribe: borg.tribe ?? null,
          type: borg.type ?? null,
          rarity: borg.rarity ?? null,
          shot: numberOrNull(borg.shot),
          attack: numberOrNull(borg.attack),
          speed: numberOrNull(borg.speed),
          jump: borg.jump ?? null,
          model: borg.model ?? null,
          anim: borg.anim ?? null,
          hasModel: Boolean(borg.hasModel),
          hasAnim: Boolean(borg.hasAnim),
        },
      ]),
  );
}

function discoverBorgIds(metadata) {
  const ids = new Set(metadata.keys());

  for (const name of fs.readdirSync(paths.sourceRoot)) {
    const id = normalizeBorgId((name.match(/^(pl[0-9a-f]{4})/i) ?? [])[1]);
    if (id) ids.add(id);
  }

  for (const entry of fs.readdirSync(paths.modelsRoot, { withFileTypes: true })) {
    const id = normalizeBorgId(entry.name);
    if (entry.isDirectory() && id) ids.add(id);
  }

  return [...ids].sort();
}

function buildRecord(id, meta = null) {
  const sourceFiles = findSourceFiles(id);
  const pzzMembers = pzzMembersByBorg.get(id) ?? [];
  const modelDir = path.join(paths.modelsRoot, id);
  const exported = scanExportedAnimations(id, modelDir);
  const mot = sourceFiles.mot ? parseMot(sourceFiles.mot.pathAbs) : null;
  const clips = exported.index?.banks ?? [];
  const actionCandidates = Object.fromEntries(actionNames.map((action) => [action, candidatesFor(action, clips, meta)]));
  const actionCoverage = Object.fromEntries(
    actionNames.map((action) => [action, actionCandidates[action].length > 0 ? "candidate-exported" : "missing-exported-candidate"]),
  );

  return {
    id,
    priority: priorityBorgs.includes(id),
    metadata: meta ?? {
      name: null,
      number: null,
      energy: null,
      tribe: null,
      type: null,
      rarity: null,
      shot: null,
      attack: null,
      speed: null,
      jump: null,
      model: null,
      anim: null,
      hasModel: false,
      hasAnim: false,
    },
    sourceFiles: {
      modelArc: sourceFiles.modelArc,
      mot: sourceFiles.mot,
      archive: sourceFiles.archive,
      hitBin: sourceFiles.hitBin,
      dataBins: sourceFiles.dataBins,
      variants: sourceFiles.variants,
    },
    pzzSourceMembers: summarizePzzMembers(pzzMembers),
    sourceMot: mot,
    exportedAssets: {
      directory: fs.existsSync(modelDir) ? rel(modelDir) : null,
      modelFiles: exported.modelFiles,
      textureFiles: exported.textureFiles,
      animationFiles: exported.animationFiles,
      animIndex: exported.index
        ? {
            path: exported.index.path,
            bankCount: exported.index.bankCount,
            clipCount: clips.length,
          }
        : null,
      orphanAnimationFiles: exported.orphanAnimationFiles,
    },
    clips,
    actionCandidates,
    actionCoverage,
    notes: buildNotes(meta, sourceFiles, exported, clips, actionCandidates),
  };
}

function findSourceFiles(id) {
  const entries = fs.readdirSync(paths.sourceRoot).filter((name) => name.toLowerCase().startsWith(id));
  const info = entries
    .map((name) => fileInfo(path.join(paths.sourceRoot, name)))
    .sort((a, b) => a.path.localeCompare(b.path));
  const byBase = new Map(info.map((file) => [path.basename(file.path).toLowerCase(), file]));
  const variants = info.filter((file) => /^pl[0-9a-f]{4}[a-z]+_mdl\.arc$/i.test(path.basename(file.path)));
  return {
    modelArc: byBase.get(`${id}_mdl.arc`) ?? null,
    mot: byBase.get(`${id}mot.bin`) ?? null,
    archive: byBase.get(`${id}.pzz`) ?? null,
    hitBin: byBase.get(`${id}hit.bin`) ?? null,
    dataBins: info.filter((file) => /^pl[0-9a-f]{4}data\d*\.bin$/i.test(path.basename(file.path))),
    variants,
  };
}

function scanExportedAnimations(id, modelDir) {
  if (!fs.existsSync(modelDir) || !fs.statSync(modelDir).isDirectory()) {
    return {
      modelFiles: [],
      textureFiles: [],
      animationFiles: [],
      orphanAnimationFiles: [],
      index: null,
    };
  }

  const files = fs
    .readdirSync(modelDir)
    .filter((name) => fs.statSync(path.join(modelDir, name)).isFile())
    .sort((a, b) => a.localeCompare(b));
  const modelFiles = files.filter((name) => /\.(dae|glb|gltf)$/i.test(name)).map((name) => fileInfo(path.join(modelDir, name)));
  const textureFiles = files.filter((name) => /\.(png|jpg|jpeg|tpl)$/i.test(name)).map((name) => fileInfo(path.join(modelDir, name)));
  const animationFiles = files.filter((name) => /^anim_.*\.json$/i.test(name)).map((name) => fileInfo(path.join(modelDir, name)));
  const indexPath = path.join(modelDir, "anim_index.json");
  const index = fs.existsSync(indexPath) ? readAnimIndex(id, indexPath) : null;
  const indexedFiles = new Set((index?.banks ?? []).map((clip) => clip.file));
  return {
    modelFiles,
    textureFiles,
    animationFiles,
    orphanAnimationFiles: animationFiles.filter((file) => !indexedFiles.has(path.basename(file.path))),
    index,
  };
}

function readAnimIndex(id, indexPath) {
  const parsed = readJson(indexPath);
  if (!Array.isArray(parsed.banks)) fail(`expected banks array in ${rel(indexPath)}`);
  const dir = path.dirname(indexPath);
  const banks = parsed.banks
    .map((bank) => ({
      file: bank.file,
      path: rel(path.join(dir, bank.file)),
      group: numberOrNull(bank.group),
      slot: numberOrNull(bank.slot),
      label: bank.label ?? null,
      frames: numberOrNull(bank.frames),
      animJoints: numberOrNull(bank.animJoints),
      rootSpanX: numberOrNull(bank.rootSpanX),
      rootSpanY: numberOrNull(bank.rootSpanY),
      rootSpanZ: numberOrNull(bank.rootSpanZ),
      exists: fs.existsSync(path.join(dir, bank.file)),
    }))
    .sort(compareClips);
  return {
    path: rel(indexPath),
    borg: parsed.borg ?? id,
    bankCount: numberOrNull(parsed.bankCount) ?? banks.length,
    banks,
  };
}

function parseMot(motPath) {
  const data = fs.readFileSync(motPath);
  const banks = [];
  const issues = [];
  if (data.length < 24) {
    return { path: rel(motPath), bytes: data.length, bankCount: 0, clipCount: 0, banks, issues: ["too small for MOT master table"] };
  }

  for (let bankIndex = 0; bankIndex < 6; bankIndex++) {
    const tableOffset = data.readUInt32BE(bankIndex * 4);
    const bank = { index: bankIndex, tableOffset: hex(tableOffset), slotCount: 0, emptySlotCount: 0, clipCount: 0 };
    if (tableOffset === 0) {
      banks.push(bank);
      continue;
    }
    if (tableOffset + 4 > data.length) {
      issues.push(`bank ${bankIndex} table offset ${hex(tableOffset)} outside file`);
      banks.push(bank);
      continue;
    }
    for (let cursor = tableOffset, slot = 0; cursor + 4 <= data.length && slot <= 1024; cursor += 4, slot++) {
      const value = data.readUInt32BE(cursor);
      if (value === 0xffffffff) {
        bank.slotCount = slot;
        break;
      }
      if (value === 0) bank.emptySlotCount += 1;
      else if (value < data.length) bank.clipCount += 1;
      else issues.push(`bank ${bankIndex} slot ${slot} points outside file: ${hex(value)}`);
      if (slot === 1024) issues.push(`bank ${bankIndex} scan stopped after 1024 slots`);
    }
    banks.push(bank);
  }
  return {
    path: rel(motPath),
    bytes: data.length,
    bankCount: banks.filter((bank) => bank.tableOffset !== "0x0").length,
    clipCount: banks.reduce((sum, bank) => sum + bank.clipCount, 0),
    banks,
    issues,
  };
}

function candidatesFor(action, clips, meta) {
  const ranked = [];
  for (const clip of clips) {
    const score = scoreClip(action, clip, meta);
    if (score.score <= 0) continue;
    ranked.push({
      ...clip,
      action,
      confidence: score.confidence,
      score: score.score,
      evidence: score.evidence,
    });
  }
  return ranked.sort((a, b) => b.score - a.score || compareClips(a, b)).slice(0, 12);
}

function scoreClip(action, clip, meta) {
  const label = String(clip.label ?? "");
  const name = String(meta?.name ?? "");
  const tribe = String(meta?.tribe ?? "");
  const type = String(meta?.type ?? "");
  const text = `${name} ${tribe} ${type}`.toLowerCase();
  const shot = meta?.shot ?? 0;
  const attack = meta?.attack ?? 0;
  const evidence = [];
  let score = 0;

  const add = (points, note) => {
    score += points;
    evidence.push(note);
  };

  if (action === "idle" && label === "idle") add(100, "exported label is idle");
  if (action === "walk/run" && /^move(_s\d+)?$/.test(label)) add(label === "move" ? 100 : 70, `exported label is ${label}`);
  if (action === "jump" && /^jump_/.test(label)) add(100, `exported label is ${label}`);
  if (action === "fly/air" && /^(fly_transition|boost)$/.test(label)) add(label === "fly_transition" ? 100 : 80, `exported label is ${label}`);
  if (action === "dash" && /^dash_/.test(label)) add(100, `exported label is ${label}`);
  if (action === "dash" && label === "boost") add(70, "exported label is boost");
  if (action === "hit" && /^(hit_react|guard)_s\d+$/.test(label)) add(label.startsWith("hit_react") ? 100 : 70, `exported label is ${label}`);
  if (action === "death" && /^(death|win_or_death)$/.test(label)) add(label === "death" ? 100 : 75, `exported label is ${label}`);
  if (action === "spawn" && label === "pose_short") add(100, "exported label is pose_short");
  if (action === "spawn" && label === "idle") add(35, "idle can be a weak spawn placeholder candidate when no pose clip is chosen");

  if (action === "melee/sword" && /^attack_lunge_s\d+$/.test(label)) add(95, `exported lunge attack label is ${label}`);
  if (action === "melee/sword" && /^attack_s\d+$/.test(label) && (attack > 0 || /sword|knight|ninja|blade|melee|short range/.test(text))) {
    add(65, `attack clip plus melee-leaning metadata (${metadataBrief(meta)})`);
  }

  if (action === "shoot/gun" && /^attack_s\d+$/.test(label) && (shot > 0 || /gun|shoot|shot|long range|cannon|tank/.test(text))) {
    add(70, `attack clip plus ranged metadata (${metadataBrief(meta)})`);
  }
  if (action === "shoot/gun" && /^special_s\d+$/.test(label) && (shot > 0 || /gun|beam|cannon|tank|long range/.test(text))) {
    add(55, `special clip plus ranged metadata (${metadataBrief(meta)})`);
  }

  if (action === "beam" && /^special_s\d+$/.test(label) && /beam|laser|satellite|cannon/.test(text)) {
    add(90, `special clip plus beam/cannon metadata (${metadataBrief(meta)})`);
  }
  if (action === "beam" && /^attack_s\d+$/.test(label) && /beam|laser/.test(text)) {
    add(60, `attack clip plus beam metadata (${metadataBrief(meta)})`);
  }

  return {
    score,
    confidence: score >= 95 ? "high" : score >= 65 ? "medium" : score > 0 ? "low" : "none",
    evidence,
  };
}

function buildNotes(meta, sourceFiles, exported, clips, actionCandidates) {
  const notes = [];
  if (!sourceFiles.mot && meta?.hasAnim) notes.push("metadata expects an anim file, but no loose source MOT was found");
  if (sourceFiles.mot && !exported.index) notes.push("source MOT exists, but no exported anim_index.json was found");
  if (exported.index && exported.index.bankCount !== clips.length) notes.push("anim_index bankCount differs from parsed bank rows");
  const missingActions = actionNames.filter((action) => actionCandidates[action].length === 0);
  if (missingActions.length > 0) notes.push(`no exported candidate for: ${missingActions.join(", ")}`);
  if (exported.orphanAnimationFiles.length > 0) notes.push(`${exported.orphanAnimationFiles.length} exported anim JSON files are not listed in anim_index.json`);
  return notes;
}

function summarize(records) {
  const actionCoverage = Object.fromEntries(
    actionNames.map((action) => [action, records.filter((record) => record.actionCandidates[action].length > 0).length]),
  );
  return {
    totalRecords: records.length,
    priorityRecords: records.filter((record) => record.priority).length,
    withSourceModel: records.filter((record) => record.sourceFiles.modelArc).length,
    withSourceMot: records.filter((record) => record.sourceFiles.mot).length,
    withExportedModel: records.filter((record) => record.exportedAssets.modelFiles.length > 0).length,
    withAnimIndex: records.filter((record) => record.exportedAssets.animIndex).length,
    indexedClipCount: records.reduce((sum, record) => sum + record.clips.length, 0),
    sourceMotClipCount: records.reduce((sum, record) => sum + (record.sourceMot?.clipCount ?? 0), 0),
    pzzMemberRecordCount: records.reduce((sum, record) => sum + record.pzzSourceMembers.recordCount, 0),
    withPzzArchiveMembers: records.filter((record) => record.pzzSourceMembers.recordCount > 0).length,
    withPzzMotionBank: records.filter((record) => record.pzzSourceMembers.hasMotionBank).length,
    withPzzHitData: records.filter((record) => record.pzzSourceMembers.hasHitData).length,
    withPzzModel: records.filter((record) => record.pzzSourceMembers.hasModel).length,
    withPzzTexture: records.filter((record) => record.pzzSourceMembers.hasTexture).length,
    actionCoverage,
  };
}

function renderMarkdown(inventory) {
  const lines = [];
  lines.push("# Borg Action Animation Asset Inventory");
  lines.push("");
  lines.push(`Generated: ${inventory.generatedAt}`);
  lines.push(`Script: \`${inventory.generatedBy}\``);
  lines.push("");
  lines.push("This is an inventory pipeline, not gameplay behavior. Action rows are candidates backed by exported/source assets.");
  lines.push("");
  lines.push("## Summary");
  lines.push("");
  lines.push("| Metric | Count |");
  lines.push("|---|---:|");
  lines.push(`| Borg records | ${inventory.summary.totalRecords} |`);
  lines.push(`| Source models | ${inventory.summary.withSourceModel} |`);
  lines.push(`| Source MOT files | ${inventory.summary.withSourceMot} |`);
  lines.push(`| Exported models | ${inventory.summary.withExportedModel} |`);
  lines.push(`| Exported anim indexes | ${inventory.summary.withAnimIndex} |`);
  lines.push(`| Exported indexed clips | ${inventory.summary.indexedClipCount} |`);
  lines.push(`| Source MOT structural clips | ${inventory.summary.sourceMotClipCount} |`);
  lines.push(`| PZZ member records joined | ${inventory.summary.pzzMemberRecordCount} |`);
  lines.push(`| Borgs with PZZ member records | ${inventory.summary.withPzzArchiveMembers} |`);
  lines.push(`| Borgs with PZZ motion-bank members | ${inventory.summary.withPzzMotionBank} |`);
  lines.push(`| Borgs with PZZ hit-data members | ${inventory.summary.withPzzHitData} |`);
  lines.push(`| Borgs with PZZ model members | ${inventory.summary.withPzzModel} |`);
  lines.push(`| Borgs with PZZ texture members | ${inventory.summary.withPzzTexture} |`);
  lines.push("");
  lines.push("## Action Coverage");
  lines.push("");
  lines.push("| Action | Borgs with exported candidate |");
  lines.push("|---|---:|");
  for (const action of actionNames) {
    lines.push(`| ${code(action)} | ${inventory.summary.actionCoverage[action]} |`);
  }
  lines.push("");
  lines.push("## Priority Borgs");
  lines.push("");
  for (const record of inventory.priority) renderBorg(lines, record, true);
  lines.push("## All Borgs");
  lines.push("");
  lines.push("| Borg | Name | Source MOT | PZZ MOT | Anim index | Clips | Missing exported action candidates |");
  lines.push("|---|---|---:|---:|---:|---:|---|");
  for (const record of inventory.records) {
    const missing = actionNames.filter((action) => record.actionCandidates[action].length === 0);
    lines.push(
      `| ${code(record.id)} | ${md(record.metadata.name ?? "")} | ${yes(record.sourceFiles.mot)} | ${yes(record.pzzSourceMembers.hasMotionBank)} | ${yes(record.exportedAssets.animIndex)} | ${record.clips.length} | ${md(missing.join(", ") || "none")} |`,
    );
  }
  lines.push("");
  lines.push("## Reproduce");
  lines.push("");
  lines.push("```bash");
  lines.push("rtk node scripts/inventory-borg-action-assets.mjs");
  lines.push("```");
  lines.push("");
  return `${lines.join("\n").trimEnd()}\n`;
}

function renderBorg(lines, record, expanded) {
  lines.push(`### ${record.id} ${record.metadata.name ?? ""}`.trim());
  lines.push("");
  lines.push(`- Source model: ${record.sourceFiles.modelArc ? code(record.sourceFiles.modelArc.path) : "none"}`);
  lines.push(`- Source MOT: ${record.sourceFiles.mot ? code(record.sourceFiles.mot.path) : "none"}`);
  lines.push(`- PZZ source members: ${record.pzzSourceMembers.recordCount} (${Object.entries(record.pzzSourceMembers.kinds).map(([kind, count]) => `${kind} ${count}`).join(", ") || "none"})`);
  lines.push(`- Exported anim index: ${record.exportedAssets.animIndex ? code(record.exportedAssets.animIndex.path) : "none"}`);
  lines.push(`- Exported indexed clips: ${record.clips.length}`);
  lines.push(`- Source MOT structural clips: ${record.sourceMot?.clipCount ?? 0}`);
  lines.push("");
  lines.push("| Action | Candidate clips | Evidence |");
  lines.push("|---|---|---|");
  for (const action of actionNames) {
    const candidates = record.actionCandidates[action];
    lines.push(
      `| ${code(action)} | ${candidates.length > 0 ? candidates.slice(0, expanded ? 5 : 2).map(formatCandidate).join("<br>") : "none"} | ${md(candidates[0]?.evidence?.join("; ") ?? "")} |`,
    );
  }
  if (record.notes.length > 0) {
    lines.push("");
    lines.push(`Notes: ${md(record.notes.join("; "))}`);
  }
  lines.push("");
}

function formatCandidate(candidate) {
  return `${code(candidate.label ?? candidate.file)} ${code(`g${candidate.group}s${candidate.slot}`)} ${candidate.frames ?? "?"}f`;
}

function fileInfo(file) {
  return {
    path: rel(file),
    bytes: fs.statSync(file).size,
    pathAbs: file,
  };
}

function metadataBrief(meta) {
  if (!meta) return "no metadata";
  return [meta.name, meta.tribe, meta.type, `shot ${meta.shot ?? "?"}`, `attack ${meta.attack ?? "?"}`]
    .filter(Boolean)
    .join(", ");
}

function compareRecords(a, b) {
  const ap = priorityBorgs.indexOf(a.id);
  const bp = priorityBorgs.indexOf(b.id);
  if (ap !== -1 || bp !== -1) return (ap === -1 ? 99 : ap) - (bp === -1 ? 99 : bp);
  return a.id.localeCompare(b.id);
}

function compareClips(a, b) {
  return (a.group ?? 99) - (b.group ?? 99) || (a.slot ?? 999) - (b.slot ?? 999) || String(a.file).localeCompare(String(b.file));
}

function normalizeBorgId(value) {
  if (typeof value !== "string") return null;
  const lower = value.toLowerCase();
  return /^pl[0-9a-f]{4}$/.test(lower) ? lower : null;
}

function numberOrNull(value) {
  return Number.isFinite(value) ? value : null;
}

function readJson(file) {
  return JSON.parse(fs.readFileSync(file, "utf8"));
}

function readJsonIfExists(file, fallback) {
  if (!fs.existsSync(file)) return fallback;
  return readJson(file);
}

function groupPzzMembersByBorg(records) {
  const grouped = new Map();
  for (const record of records) {
    const id = normalizeBorgId(record.borgId);
    if (!id) continue;
    const list = grouped.get(id) ?? [];
    list.push(record);
    grouped.set(id, list);
  }
  for (const list of grouped.values()) {
    list.sort((a, b) => String(a.memberId).localeCompare(String(b.memberId)));
  }
  return grouped;
}

function summarizePzzMembers(records) {
  const kinds = {};
  const actionHints = new Set();
  const familyHints = new Set();
  for (const record of records) {
    const kind = record.inferredKind ?? "unknown";
    kinds[kind] = (kinds[kind] ?? 0) + 1;
    for (const hint of record.actionHints ?? []) actionHints.add(hint);
    for (const hint of record.familyHints ?? []) familyHints.add(hint);
  }
  const keyMembers = selectKeyPzzMembers(records);
  return {
    manifest: fs.existsSync(paths.pzzMemberManifest) ? rel(paths.pzzMemberManifest) : null,
    recordCount: records.length,
    kinds: Object.fromEntries(Object.entries(kinds).sort((a, b) => b[1] - a[1] || a[0].localeCompare(b[0]))),
    hasMotionBank: records.some((record) => record.inferredKind === "motion-bank" && record.payloadBytes > 0),
    hasHitData: records.some((record) => record.inferredKind === "hit-collision-data" && record.payloadBytes > 0),
    hasModel: records.some((record) => record.inferredKind === "hsd-model" && record.payloadBytes > 0),
    hasTexture: records.some((record) => record.inferredKind === "texture" && record.payloadBytes > 0),
    actionHints: [...actionHints].sort(),
    familyHints: [...familyHints].sort(),
    keyMembers: keyMembers.map((record) => ({
      memberId: record.memberId,
      inferredName: record.inferredName,
      inferredKind: record.inferredKind,
      payloadBytes: record.payloadBytes,
      compressed: record.compressed,
      actionHints: record.actionHints ?? [],
    })),
  };
}

function selectKeyPzzMembers(records) {
  const selected = [];
  const wanted = new Set(["borg-data", "hit-collision-data", "motion-bank", "hsd-model", "texture"]);
  const seen = new Set();
  for (const record of records) {
    if (!wanted.has(record.inferredKind) || seen.has(record.inferredKind)) continue;
    selected.push(record);
    seen.add(record.inferredKind);
  }
  return selected;
}

function writeJson(file, value) {
  const cleaned = stripPrivate(value);
  fs.writeFileSync(`${file}.tmp`, `${JSON.stringify(cleaned, null, 2)}\n`, "utf8");
  fs.renameSync(`${file}.tmp`, file);
}

function stripPrivate(value) {
  if (Array.isArray(value)) return value.map(stripPrivate);
  if (!value || typeof value !== "object") return value;
  return Object.fromEntries(
    Object.entries(value)
      .filter(([key]) => key !== "pathAbs")
      .map(([key, item]) => [key, stripPrivate(item)]),
  );
}

function mustExist(file) {
  if (!fs.existsSync(file)) fail(`missing input: ${rel(file)}`);
}

function md(value) {
  return String(value ?? "").replaceAll("|", "\\|").replaceAll("\n", " ");
}

function code(value) {
  return `\`${md(value)}\``;
}

function yes(value) {
  return value ? "yes" : "no";
}

function hex(value) {
  return `0x${value.toString(16)}`;
}

function rel(file) {
  let normalized = file;
  if (normalized.startsWith("/")) {
    const windowsPath = normalized.match(/^\/([A-Za-z]:\/.*)$/);
    if (windowsPath) normalized = windowsPath[1];
  }
  return path.relative(repoRoot, normalized).split(path.sep).join("/");
}

function fail(message) {
  console.error(`inventory-borg-action-assets: ${message}`);
  process.exit(1);
}
