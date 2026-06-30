#!/usr/bin/env node

import { createHash } from "node:crypto";
import { promises as fs } from "node:fs";
import path from "node:path";
import { fileURLToPath } from "node:url";

const repoRoot = path.resolve(path.dirname(fileURLToPath(import.meta.url)), "..");

const paths = {
  borgAnimationPlan: "research/asset-inventory/borg-animation-export-plan.json",
  weaponsEffectsProjectiles: "research/asset-inventory/weapons-effects-projectiles.json",
  particleEffectInventory: "research/asset-inventory/particle-effect-inventory.json",
  borgAssets: "research/asset-inventory/borg-assets.json",
  hitBinInventory: "research/asset-inventory/hit-bin-inventory.json",
  borgData: "packages/assets/data/borgs.json",
  modelManifest: "apps/game/public/models/library/manifest.json",
  modelRoot: "apps/game/public/models",
  afsRoot: "user-data/GG4E/afs_data/root",
  outputJson: "research/asset-inventory/weapon-attachment-map.json",
  outputMarkdown: "research/asset-inventory/weapon-attachment-map.md",
};

const targetFamilies = [
  "sword",
  "fire",
  "gun",
  "beam",
  "bulletProjectile",
  "muzzle",
  "impact",
  "trailAura",
];

const familyLabels = {
  sword: "Sword/blade",
  fire: "Fire/flame",
  gun: "Gun",
  beam: "Beam/laser",
  bulletProjectile: "Bullet/projectile",
  muzzle: "Muzzle/spawn",
  impact: "Impact/explosion",
  trailAura: "Trail/aura",
};

const confidenceRank = {
  High: 3,
  Medium: 2,
  Low: 1,
  Unknown: 0,
};

function abs(relPath) {
  return path.join(repoRoot, relPath);
}

function rel(absPath) {
  return path.relative(repoRoot, absPath).replaceAll(path.sep, "/");
}

async function readJson(relPath) {
  const text = await fs.readFile(abs(relPath), "utf8");
  return JSON.parse(text);
}

async function exists(relPath) {
  try {
    await fs.access(abs(relPath));
    return true;
  } catch {
    return false;
  }
}

async function readJsonIfExists(relPath, fallback) {
  if (!(await exists(relPath))) return fallback;
  return readJson(relPath);
}

function sha1(buffer) {
  return createHash("sha1").update(buffer).digest("hex");
}

function hex(value, width = 8) {
  if (value == null) return null;
  return `0x${Number(value >>> 0).toString(16).padStart(width, "0")}`;
}

function round(value, places = 3) {
  return Number.isFinite(value) ? Number(value.toFixed(places)) : value;
}

function unique(values) {
  return [...new Set(values.filter((value) => value != null && value !== ""))];
}

function pushLimited(array, value, limit = 12) {
  if (array.length < limit) array.push(value);
}

function confidenceMax(a = "Unknown", b = "Unknown") {
  return confidenceRank[b] > confidenceRank[a] ? b : a;
}

function compareConfidence(a, b) {
  return confidenceRank[b.confidence ?? "Unknown"] - confidenceRank[a.confidence ?? "Unknown"];
}

function normalizeFamily(family) {
  const key = String(family ?? "").toLowerCase();
  const out = [];

  if (key.includes("sword") || key.includes("blade")) out.push("sword");
  if (key.includes("fire") || key.includes("flame")) out.push("fire");
  if (key === "gun" || key.includes("gun")) out.push("gun");
  if (key.includes("bullet") || key.includes("projectile") || key.includes("arrow") || key.includes("missile")) {
    out.push("bulletProjectile");
  }
  if (key.includes("beam") || key.includes("laser")) out.push("beam");
  if (key.includes("muzzle")) out.push("muzzle");
  if (key.includes("impact") || key.includes("explosion") || key.includes("hit")) out.push("impact");
  if (key.includes("trail") || key.includes("aura")) out.push("trailAura");

  return unique(out);
}

function contextualFamilyKeys(raw, name, role) {
  const lowerName = name.toLowerCase();
  const lowerRole = String(role ?? "").toLowerCase();
  const sourceFamilies = Array.isArray(raw.families) ? raw.families : [];
  const context = [
    name,
    role,
    raw.reason,
    raw.sourceInventoryCandidate?.reason,
    raw.linkedBorgName,
    raw.linkedBorg?.name,
    ...sourceFamilies.map((entry) => entry.reason),
  ]
    .filter(Boolean)
    .join(" ")
    .toLowerCase();

  if (/^(hit[0-9a-f]+|comhit2?)\.bin$/i.test(name) || lowerName.endsWith("hit.bin") || lowerRole.includes("hit/impact")) {
    return ["impact"];
  }

  if (lowerName.endsWith("data.bin") || lowerRole.includes("borg data")) {
    return [];
  }

  const keys = new Set();
  for (const entry of sourceFamilies) {
    const family = String(entry.family ?? entry).toLowerCase();
    if (family.includes("sword") || family.includes("blade")) keys.add("sword");
    if (family.includes("fire") || family.includes("flame")) keys.add("fire");
    if (family.includes("beam") || family.includes("laser")) keys.add("beam");
    if (family.includes("muzzle")) keys.add("muzzle");
    if (family.includes("impact") || family.includes("explosion")) keys.add("impact");
    if (family.includes("trail") || family.includes("aura")) keys.add("trailAura");
    if (family.includes("gun") || family.includes("bullet")) {
      keys.add("bulletProjectile");
      if (/\b(gun|gunner|gunman|gatling|revolver|cannon|tank|rifle|pistol|blaster)\b/.test(context)) {
        keys.add("gun");
      }
    }
  }

  for (const family of normalizeFamily(raw.family)) keys.add(family);

  if (/arrow|shuriken|missile|icbm|bomb|bomber|projectile|bullet/i.test(context)) keys.add("bulletProjectile");
  if (/\b(gun|gunner|gunman|gatling|revolver|cannon|tank|rifle|pistol|blaster)\b/i.test(context)) keys.add("gun");
  if (/muzzle|shot|barrel/i.test(context)) keys.add("muzzle");
  if (/beam|laser|plasma/i.test(context)) keys.add("beam");
  if (/fire|flame|phoenix/i.test(context)) keys.add("fire");
  if (/sword|blade|slash|samurai|knight|axe|hatchet|chainsaw|claw|spike|drill|hammer/i.test(context)) keys.add("sword");

  if (lowerName === "arrow_mdl.arc") keys.add("bulletProjectile");

  return [...keys].filter((family) => targetFamilies.includes(family));
}

function fileNameFromPath(filePath) {
  return path.basename(filePath.replaceAll("\\", "/"));
}

function borgIdFromFileName(name) {
  const match = /^(?:pl|it)([0-9a-f]{4})/i.exec(name);
  return match ? `pl${match[1].toLowerCase()}` : null;
}

function itemAttachmentNameForBorg(borgId) {
  return `it${borgId.slice(2)}_mdl.arz`;
}

async function walkFiles(rootRel, predicate = () => true) {
  const rootAbs = abs(rootRel);
  const output = [];

  async function visit(current) {
    let entries;
    try {
      entries = await fs.readdir(current, { withFileTypes: true });
    } catch (error) {
      if (error.code === "ENOENT") return;
      throw error;
    }

    for (const entry of entries) {
      const child = path.join(current, entry.name);
      if (entry.isDirectory()) {
        await visit(child);
        continue;
      }
      if (!entry.isFile()) continue;
      const childRel = rel(child);
      if (predicate(childRel)) output.push(childRel);
    }
  }

  await visit(rootAbs);
  return output.sort((a, b) => a.localeCompare(b));
}

function makeAssetEvidence(source, raw) {
  const pathValue = raw.path;
  const name = raw.name ?? fileNameFromPath(pathValue);
  const linkedBorg =
    raw.linkedBorgId ??
    raw.linkedBorg?.id ??
    (raw.linkedBorg ? raw.linkedBorg.id : null) ??
    borgIdFromFileName(name);
  const linkedBorgName = raw.linkedBorgName ?? raw.linkedBorg?.name ?? null;
  const role = raw.fileType?.role ?? raw.role ?? raw.extension ?? path.extname(name).toLowerCase() ?? "file";
  const sourceFamilies = Array.isArray(raw.families) ? raw.families : [];
  const familyKeys = unique(contextualFamilyKeys(raw, name, role));

  return {
    source,
    path: pathValue,
    name,
    role,
    extension: (raw.fileType?.extension ?? raw.extension ?? path.extname(name).toLowerCase()) || null,
    sizeBytes: raw.sizeBytes ?? null,
    linkedBorgId: linkedBorg,
    linkedBorgName,
    confidence: raw.confidence ?? raw.sourceInventoryCandidate?.confidence ?? sourceFamilies[0]?.confidence ?? "Unknown",
    familyKeys,
    sourceFamilies: sourceFamilies.map((entry) => ({
      family: entry.family ?? String(entry),
      confidence: entry.confidence ?? raw.confidence ?? "Unknown",
      reason: entry.reason ?? raw.reason ?? raw.sourceInventoryCandidate?.reason ?? null,
    })),
    reason: raw.reason ?? raw.sourceInventoryCandidate?.reason ?? sourceFamilies[0]?.reason ?? null,
    needs: unique([...(raw.needs ?? []), ...(raw.sourceInventoryCandidate?.needs ?? [])]),
    blocker: raw.blocker ?? null,
  };
}

function collectAssetEvidence(weapons, particles) {
  const evidence = [];
  const weaponCandidates = Array.isArray(weapons.candidates)
    ? weapons.candidates
    : Object.values(weapons.candidates ?? {});

  for (const candidate of weaponCandidates) {
    const item = makeAssetEvidence("weapons-effects-projectiles", candidate);
    if (item.familyKeys.length > 0) evidence.push(item);
  }

  for (const asset of particles.assets ?? []) {
    const item = makeAssetEvidence("particle-effect-inventory", asset);
    if (item.familyKeys.length > 0) evidence.push(item);
  }

  return evidence.sort((a, b) => {
    const conf = compareConfidence(a, b);
    if (conf !== 0) return conf;
    return (b.sizeBytes ?? 0) - (a.sizeBytes ?? 0) || a.path.localeCompare(b.path);
  });
}

function sourceFilesForRecord(record) {
  const sourceFiles = record?.sourceFiles ?? {};
  return {
    archives: sourceFiles.archives ?? [],
    modelArcs: sourceFiles.modelArcs ?? [],
    motBins: sourceFiles.motBins ?? [],
    dataBins: sourceFiles.dataBins ?? [],
    hitBins: sourceFiles.hitBins ?? [],
    other: sourceFiles.other ?? [],
  };
}

async function inspectDataBin(relPath) {
  const buffer = await fs.readFile(abs(relPath));
  const wordCount = Math.floor(buffer.length / 4);
  const firstWords = [];
  const firstNonZeroWords = [];
  const floatRange = { min: Infinity, max: -Infinity, count: 0 };

  let nonZeroWordCount = 0;
  for (let i = 0; i < wordCount; i += 1) {
    const offset = i * 4;
    const word = buffer.readUInt32BE(offset);
    if (i < 24) firstWords.push(hex(word));
    if (word !== 0) {
      nonZeroWordCount += 1;
      pushLimited(firstNonZeroWords, { index: i, offset: hex(offset, 4), value: hex(word) }, 24);
    }

    const asFloat = buffer.readFloatBE(offset);
    if (Number.isFinite(asFloat) && Math.abs(asFloat) <= 100000 && asFloat !== 0) {
      floatRange.min = Math.min(floatRange.min, asFloat);
      floatRange.max = Math.max(floatRange.max, asFloat);
      floatRange.count += 1;
    }
  }

  return {
    path: relPath,
    bytes: buffer.length,
    sha1: sha1(buffer),
    parseStatus: "raw inspection only; field names need caller/runtime correlation",
    wordCount,
    nonZeroWordCount,
    firstWords,
    firstNonZeroWords,
    floatLikeRange: {
      min: Number.isFinite(floatRange.min) ? round(floatRange.min) : null,
      max: Number.isFinite(floatRange.max) ? round(floatRange.max) : null,
      count: floatRange.count,
    },
  };
}

function summarizeHitBin(hitFile) {
  if (!hitFile) return null;
  return {
    path: hitFile.path,
    valid: hitFile.valid,
    category: hitFile.category,
    parseStatus: "0x20 remap header plus 32 x 0xF4 actor records; record fields are not semantically labelled",
    layout: hitFile.layout,
    remap: {
      activeCount: hitFile.remap?.activeCount ?? null,
      uniqueActiveCount: hitFile.remap?.uniqueActiveCount ?? null,
      maxValue: hitFile.remap?.maxValue ?? null,
      sampleEntries: hitFile.remap?.sampleEntries?.slice(0, 16) ?? [],
    },
    records: {
      nonZeroRecordCount: hitFile.records?.nonZeroRecordCount ?? null,
      zeroRecordCount: hitFile.records?.zeroRecordCount ?? null,
      maxNonZeroRecordIndex: hitFile.records?.maxNonZeroRecordIndex ?? null,
      firstWordHistogram: hitFile.records?.firstWordHistogram?.slice(0, 8) ?? [],
      floatLikeRange: hitFile.records?.floatLikeRange ?? null,
      sampleRecords: hitFile.records?.sampleRecords?.slice(0, 4) ?? [],
    },
    unknowns: hitFile.unknowns ?? [],
  };
}

function extractAttributes(source) {
  const attrs = {};
  const regex = /([A-Za-z_][A-Za-z0-9_.:-]*)="([^"]*)"/g;
  let match;
  while ((match = regex.exec(source))) attrs[match[1]] = match[2];
  return attrs;
}

function parseMatrix(line) {
  const match = /<matrix[^>]*>([^<]+)<\/matrix>/.exec(line);
  if (!match) return null;
  const values = match[1].trim().split(/\s+/).map(Number);
  return values.length === 16 && values.every(Number.isFinite) ? values : null;
}

function multiply4(a, b) {
  const out = Array(16).fill(0);
  for (let row = 0; row < 4; row += 1) {
    for (let col = 0; col < 4; col += 1) {
      for (let k = 0; k < 4; k += 1) out[row * 4 + col] += a[row * 4 + k] * b[k * 4 + col];
    }
  }
  return out;
}

function matrixTranslation(matrix) {
  return {
    x: round(matrix[3]),
    y: round(matrix[7]),
    z: round(matrix[11]),
  };
}

function identity4() {
  return [1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1];
}

async function inspectDae(relPath) {
  const text = await fs.readFile(abs(relPath), "utf8");
  const lines = text.split(/\r?\n/);
  const nodes = new Map();
  const stack = [];

  for (const line of lines) {
    const nodeMatch = /<node\b([^>]*)>/.exec(line);
    if (nodeMatch) {
      const attrs = extractAttributes(nodeMatch[1]);
      const id = attrs.id ?? attrs.name ?? attrs.sid;
      if (id) {
        const parentId = stack.length > 0 ? stack[stack.length - 1] : null;
        const node = {
          id,
          sid: attrs.sid ?? null,
          name: attrs.name ?? id,
          type: attrs.type ?? null,
          parentId,
          children: [],
          matrix: null,
        };
        nodes.set(id, node);
        if (parentId && nodes.has(parentId)) nodes.get(parentId).children.push(id);
        stack.push(id);
      }
    }

    const matrix = parseMatrix(line);
    if (matrix && stack.length > 0) {
      const current = nodes.get(stack[stack.length - 1]);
      if (current) current.matrix = matrix;
    }

    if (line.includes("</node>") && stack.length > 0) stack.pop();
  }

  const objectBindings = new Map();
  const nameArrayRegex = /<Name_array\b[^>]*id="([^"]+)-joints-array"[^>]*>([^<]*)<\/Name_array>/g;
  let match;
  while ((match = nameArrayRegex.exec(text))) {
    const objectId = match[1];
    const joints = match[2].trim().split(/\s+/).filter(Boolean);
    for (const joint of joints) {
      const list = objectBindings.get(joint) ?? [];
      list.push(objectId);
      objectBindings.set(joint, list);
    }
  }

  for (const id of nodes.keys()) {
    const objectMatch = /^Joint_([0-9]+)_Object_/.exec(id);
    if (objectMatch) {
      const joint = `JOBJ_${objectMatch[1]}`;
      const list = objectBindings.get(joint) ?? [];
      list.push(id);
      objectBindings.set(joint, list);
    }
  }

  const world = new Map();
  function worldMatrix(id) {
    if (world.has(id)) return world.get(id);
    const node = nodes.get(id);
    if (!node) return identity4();
    const local = node.matrix ?? identity4();
    const parent = node.parentId ? worldMatrix(node.parentId) : identity4();
    const value = multiply4(parent, local);
    world.set(id, value);
    return value;
  }

  const jointNodes = [...nodes.values()].filter((node) => node.type === "JOINT" || /^JOBJ_[0-9]+$/.test(node.id));
  for (const node of jointNodes) {
    node.worldPosition = matrixTranslation(worldMatrix(node.id));
    node.objectBindings = unique(objectBindings.get(node.id) ?? []);
    node.jointChildren = node.children.filter((childId) => {
      const child = nodes.get(childId);
      return child && (child.type === "JOINT" || /^JOBJ_[0-9]+$/.test(child.id));
    });
  }

  const positions = jointNodes.map((node) => node.worldPosition).filter(Boolean);
  const maxAbsX = Math.max(1, ...positions.map((position) => Math.abs(position.x)));
  const maxDistance = Math.max(
    1,
    ...positions.map((position) => Math.hypot(position.x, position.y, position.z)),
  );

  const candidates = jointNodes
    .map((node) => {
      const nameText = `${node.id} ${node.name} ${node.sid ?? ""}`;
      const semanticName = /(hand|wrist|weapon|sword|blade|gun|muzzle|barrel|emit|socket|attach)/i.test(nameText);
      const leaf = node.jointChildren.length === 0;
      const distance = Math.hypot(node.worldPosition.x, node.worldPosition.y, node.worldPosition.z);
      const lateral = Math.abs(node.worldPosition.x);
      const objectBindingCount = node.objectBindings.length;
      let score = 0;
      if (semanticName) score += 8;
      if (leaf) score += 3;
      if (lateral / maxAbsX > 0.55) score += 2;
      if (distance / maxDistance > 0.65) score += 2;
      score += Math.min(4, objectBindingCount) * 0.75;

      const reasons = [];
      if (semanticName) reasons.push("node name contains attachment/weapon term");
      if (leaf) reasons.push("leaf JOBJ in exported skeleton");
      if (lateral / maxAbsX > 0.55) reasons.push("laterally distal compared with this skeleton");
      if (distance / maxDistance > 0.65) reasons.push("far from root compared with this skeleton");
      if (objectBindingCount > 0) reasons.push(`${objectBindingCount} geometry/controller binding(s) reference this joint`);
      if (!semanticName) reasons.push("DAE node name is generic JOBJ, so role needs trace or visual confirmation");

      return {
        nodeId: node.id,
        nodeName: node.name,
        confidence: semanticName ? "High" : score >= 6 ? "Medium" : "Low",
        score: round(score, 2),
        roleCandidate: semanticName
          ? "semantic weapon/socket candidate"
          : leaf && lateral / maxAbsX > 0.55
            ? "distal limb attachment candidate"
            : leaf && objectBindingCount > 0
              ? "rigid/object-bound leaf candidate"
              : objectBindingCount > 2
                ? "object cluster attachment candidate"
                : "generic skeleton candidate",
        worldPosition: node.worldPosition,
        parentId: node.parentId,
        childJointCount: node.jointChildren.length,
        objectBindingCount,
        objectBindings: node.objectBindings.slice(0, 12),
        reason: reasons.join("; "),
      };
    })
    .filter((candidate) => candidate.score >= 3.5)
    .sort((a, b) => b.score - a.score || a.nodeId.localeCompare(b.nodeId))
    .slice(0, 10);

  return {
    path: relPath,
    jointCount: jointNodes.length,
    genericJobjNamesOnly: jointNodes.every((node) => /^JOBJ_[0-9]+$/.test(node.name)),
    objectBindingCount: [...objectBindings.values()].reduce((sum, list) => sum + list.length, 0),
    attachmentBoneCandidates: candidates,
  };
}

async function discoverDaeInspections(modelManifest) {
  const daePaths = await walkFiles(paths.modelRoot, (file) => file.toLowerCase().endsWith(".dae"));
  const byBorg = new Map();
  const manifestById = new Map((modelManifest ?? []).map((entry) => [String(entry.id).toLowerCase(), entry]));

  for (const daePath of daePaths) {
    const id = /(?:^|\/)(pl[0-9a-f]{4})(?:\/|\.dae)/i.exec(daePath)?.[1]?.toLowerCase();
    if (!id) continue;
    const inspection = await inspectDae(daePath);
    inspection.manifest = manifestById.has(id)
      ? {
          present: true,
          bones: manifestById.get(id).bones,
          meshes: manifestById.get(id).meshes,
          tris: manifestById.get(id).tris,
        }
      : { present: false };
    const list = byBorg.get(id) ?? [];
    list.push(inspection);
    byBorg.set(id, list);
  }

  for (const list of byBorg.values()) {
    list.sort((a, b) => {
      const aLibrary = a.path.includes("/library/") ? 0 : 1;
      const bLibrary = b.path.includes("/library/") ? 0 : 1;
      return aLibrary - bLibrary || a.path.localeCompare(b.path);
    });
  }

  return byBorg;
}

function summarizeMotAttackCandidates(animationBorg) {
  const clips = animationBorg?.clips ?? [];
  return clips
    .filter((clip) => {
      const text = `${clip.candidateLabel ?? ""} ${clip.destinationPath ?? ""} ${(clip.confirmedExportPaths ?? []).join(" ")}`;
      return clip.bankIndex === 1 || clip.bankIndex === 2 || /attack|shot|slash|fire|beam|gun|muzzle/i.test(text);
    })
    .map((clip) => {
      const exportedAttackName = [
        clip.destinationPath,
        ...(clip.confirmedExportPaths ?? []),
      ].some((value) => /attack|shot|slash|fire|beam|gun|muzzle/i.test(String(value)));
      return {
        bankIndex: clip.bankIndex,
        slotIndex: clip.slotIndex,
        clipIndexInBank: clip.clipIndexInBank,
        sourceBlobOffset: clip.sourceBlobOffset,
        blobLengthBytes: clip.blobLengthBytes,
        candidateLabel: clip.candidateLabel,
        destinationPath: clip.destinationPath,
        status: clip.status,
        confirmedExportPaths: clip.confirmedExportPaths ?? [],
        attackInference:
          clip.bankIndex === 1
            ? "bank 1 action/attack candidate; pl0615 bank1 slot21 is exported as attack_arm_candidate"
            : clip.bankIndex === 2
              ? "bank 2 secondary/special-action candidate; semantics unresolved"
              : "name/export label contains attack-like term",
        needsRuntimeTrace: true,
        runtimeTraceReason: exportedAttackName
          ? "export name gives an attack lead, but spawn frame, effect id, projectile path, and attachment bone still need runtime trace"
          : "static MOT table gives bank/slot/offset only; gameplay trace must label attack semantic and spawned asset",
      };
    })
    .sort((a, b) => a.bankIndex - b.bankIndex || a.slotIndex - b.slotIndex);
}

function buildBorgRecord({
  id,
  metadata,
  assetRecord,
  animationBorg,
  daeInspections,
  hitFile,
  dataInspections,
  evidence,
}) {
  const sourceFiles = sourceFilesForRecord(assetRecord);
  const familySummary = {};
  for (const family of targetFamilies) {
    const familyEvidence = evidence.filter((item) => item.familyKeys.includes(family));
    if (familyEvidence.length === 0) continue;
    familySummary[family] = {
      confidence: familyEvidence.reduce((current, item) => confidenceMax(current, item.confidence), "Unknown"),
      evidenceCount: familyEvidence.length,
      topReasons: unique(familyEvidence.map((item) => item.reason).filter(Boolean)).slice(0, 4),
      topAssets: familyEvidence.slice(0, 8).map((item) => ({
        path: item.path,
        role: item.role,
        confidence: item.confidence,
        source: item.source,
        reason: item.reason,
      })),
    };
  }

  const archiveNames = unique([
    ...sourceFiles.archives.map((file) => file.path),
    ...sourceFiles.modelArcs.map((file) => file.path),
    ...sourceFiles.motBins.map((file) => file.path),
    ...sourceFiles.dataBins.map((file) => file.path),
    ...sourceFiles.hitBins.map((file) => file.path),
    ...evidence
      .filter((item) => [".pzz", ".arz", ".arc"].includes(item.extension))
      .map((item) => item.path),
  ]);

  const itemAttachmentCandidates = evidence.filter((item) => /^it[0-9a-f]{4}_mdl\.arz$/i.test(item.name));
  const attackClipCandidates = summarizeMotAttackCandidates(animationBorg);
  const hitInspection = summarizeHitBin(hitFile);
  const attachmentBoneCandidates = (daeInspections ?? []).flatMap((inspection) =>
    inspection.attachmentBoneCandidates.map((candidate) => ({
      ...candidate,
      daePath: inspection.path,
      daeGenericJobjNamesOnly: inspection.genericJobjNamesOnly,
    })),
  );

  return {
    id,
    name: metadata?.name ?? assetRecord?.name ?? id,
    number: metadata?.number ?? assetRecord?.number ?? null,
    tribe: metadata?.tribe ?? assetRecord?.tribe ?? "Unknown",
    type: metadata?.type ?? assetRecord?.type ?? null,
    stats: {
      energy: metadata?.energy ?? assetRecord?.energy ?? null,
      hp: metadata?.hp ?? null,
      shot: metadata?.shot ?? null,
      attack: metadata?.attack ?? null,
      speed: metadata?.speed ?? null,
      jump: metadata?.jump ?? null,
      rarity: metadata?.rarity ?? null,
    },
    families: familySummary,
    archiveNames,
    itemAttachmentCandidates: itemAttachmentCandidates.map((item) => ({
      path: item.path,
      confidence: item.confidence,
      families: item.familyKeys,
      reason: item.reason,
      blocker: item.blocker,
    })),
    sourceFiles,
    dataBinInspection: dataInspections,
    hitBinInspection: hitInspection,
    modelExport: {
      hasDae: (daeInspections ?? []).length > 0,
      daeInspections: daeInspections ?? [],
    },
    mot: animationBorg
      ? {
          motPath: animationBorg.motPath ?? sourceFiles.motBins[0]?.path ?? null,
          banks: animationBorg.banks ?? [],
          clipCount: animationBorg.clipCount ?? 0,
          existingExports: animationBorg.existingExports ?? [],
          attackClipCandidates,
        }
      : {
          motPath: sourceFiles.motBins[0]?.path ?? null,
          banks: [],
          clipCount: 0,
          existingExports: [],
          attackClipCandidates: [],
        },
    attachmentBoneCandidates: attachmentBoneCandidates
      .sort((a, b) => b.score - a.score || a.nodeId.localeCompare(b.nodeId))
      .slice(0, 12),
    assetEvidence: evidence.map((item) => ({
      source: item.source,
      path: item.path,
      role: item.role,
      extension: item.extension,
      sizeBytes: item.sizeBytes,
      confidence: item.confidence,
      families: item.familyKeys,
      reason: item.reason,
      needs: item.needs,
      blocker: item.blocker,
    })),
    runtimeTraceNeeded: attackClipCandidates.length > 0,
    runtimeTraceReasons: unique(
      [
        ...attackClipCandidates.map((clip) => clip.runtimeTraceReason),
        hitInspection ? "pl####hit.bin records are parsed structurally but not mapped to actions or bones" : null,
        attachmentBoneCandidates.length > 0 &&
        attachmentBoneCandidates.every((candidate) => candidate.daeGenericJobjNamesOnly)
          ? "DAE exposes generic JOBJ node names, not semantic hand/weapon/muzzle bone names"
          : null,
      ].filter(Boolean),
    ),
  };
}

function summarizeSharedAssets(evidence) {
  const byPath = new Map();
  for (const item of evidence.filter((entry) => !entry.linkedBorgId)) {
    const entry =
      byPath.get(item.path) ??
      {
        path: item.path,
        roles: [],
        sources: [],
        extension: item.extension,
        sizeBytes: item.sizeBytes,
        families: [],
        confidence: "Unknown",
        reasons: [],
        needs: [],
        blockers: [],
      };
    entry.roles = unique([...entry.roles, item.role]);
    entry.sources = unique([...entry.sources, item.source]);
    entry.families = unique([...entry.families, ...item.familyKeys]);
    entry.confidence = confidenceMax(entry.confidence, item.confidence);
    entry.reasons = unique([...entry.reasons, item.reason].filter(Boolean));
    entry.needs = unique([...entry.needs, ...item.needs]);
    entry.blockers = unique([...entry.blockers, item.blocker].filter(Boolean));
    byPath.set(item.path, entry);
  }

  return [...byPath.values()]
    .map((item) => ({
      ...item,
      role: item.roles.join(", "),
      reason: item.reasons[0] ?? null,
      blocker: item.blockers[0] ?? null,
    }))
    .sort((a, b) => {
      const conf = compareConfidence(a, b);
      if (conf !== 0) return conf;
      return a.path.localeCompare(b.path);
    });
}

function buildFamilyGroups(borgs, sharedAssets) {
  const families = {};
  for (const family of targetFamilies) {
    const familyBorgs = borgs.filter((borg) => borg.families[family]);
    const byTribeMap = new Map();
    for (const borg of familyBorgs) {
      const entry =
        byTribeMap.get(borg.tribe) ??
        {
          tribe: borg.tribe,
          borgCount: 0,
          borgs: [],
        };
      entry.borgCount += 1;
      entry.borgs.push({
        id: borg.id,
        name: borg.name,
        confidence: borg.families[family].confidence,
        evidenceCount: borg.families[family].evidenceCount,
        attackClipCandidateCount: borg.mot.attackClipCandidates.length,
        hasDaeAttachmentCandidates: borg.attachmentBoneCandidates.length > 0,
        topAssets: borg.families[family].topAssets.slice(0, 4),
      });
      byTribeMap.set(borg.tribe, entry);
    }

    const byTribe = [...byTribeMap.values()]
      .map((entry) => ({
        ...entry,
        borgs: entry.borgs.sort((a, b) => {
          const conf = compareConfidence(a, b);
          if (conf !== 0) return conf;
          return a.id.localeCompare(b.id);
        }),
      }))
      .sort((a, b) => b.borgCount - a.borgCount || a.tribe.localeCompare(b.tribe));

    families[family] = {
      label: familyLabels[family],
      borgCount: familyBorgs.length,
      byTribe,
      sharedAssets: sharedAssets.filter((asset) => asset.families.includes(family)),
    };
  }
  return families;
}

function buildRuntimeTraceQueue(borgs) {
  const rows = [];
  for (const borg of borgs) {
    const familyKeys = Object.keys(borg.families);
    for (const clip of borg.mot.attackClipCandidates) {
      rows.push({
        borgId: borg.id,
        borgName: borg.name,
        tribe: borg.tribe,
        families: familyKeys,
        bankIndex: clip.bankIndex,
        slotIndex: clip.slotIndex,
        sourceBlobOffset: clip.sourceBlobOffset,
        candidateLabel: clip.candidateLabel,
        confirmedExportPaths: clip.confirmedExportPaths,
        priority: clip.confirmedExportPaths.length > 0 ? "High" : familyKeys.length > 0 ? "Medium" : "Low",
        needsRuntimeTrace: true,
        traceGoal: "label attack semantic, spawned asset/effect id, spawn frame, projectile path, and attachment bone",
        reason: clip.runtimeTraceReason,
      });
    }
  }

  return rows.sort((a, b) => {
    const conf = confidenceRank[b.priority] - confidenceRank[a.priority];
    if (conf !== 0) return conf;
    return a.borgId.localeCompare(b.borgId) || a.bankIndex - b.bankIndex || a.slotIndex - b.slotIndex;
  });
}

function makeMarkdown(report) {
  const lines = [];
  lines.push("# Weapon Attachment Map");
  lines.push("");
  lines.push(`Generated: ${report.generatedAt}`);
  lines.push("");
  lines.push("## Summary");
  lines.push("");
  lines.push(`- Borgs with weapon/projectile/effect evidence: ${report.summary.mappedBorgCount}`);
  lines.push(`- Shared/global asset candidates: ${report.summary.sharedAssetCount}`);
  lines.push(`- Borgs with DAE attachment-node candidates: ${report.summary.borgsWithDaeAttachmentCandidates}`);
  lines.push(`- MOT attack/action clip candidates needing runtime trace: ${report.summary.runtimeTraceAttackClipCount}`);
  lines.push("");
  lines.push("Family coverage:");
  lines.push("");
  for (const family of targetFamilies) {
    lines.push(`- ${familyLabels[family]}: ${report.families[family].borgCount} borg(s)`);
  }

  lines.push("");
  lines.push("## Family Leads By Tribe");
  for (const family of targetFamilies) {
    const group = report.families[family];
    lines.push("");
    lines.push(`### ${group.label}`);
    if (group.borgCount === 0 && group.sharedAssets.length === 0) {
      lines.push("");
      lines.push("No candidates found.");
      continue;
    }

    if (group.byTribe.length > 0) {
      lines.push("");
      lines.push("| Tribe | Borgs | Representative leads |");
      lines.push("|---|---:|---|");
      for (const tribe of group.byTribe.slice(0, 12)) {
        const borgs = tribe.borgs
          .slice(0, 8)
          .map((borg) => `${borg.id} ${borg.name} (${borg.confidence})`)
          .join("<br>");
        lines.push(`| ${tribe.tribe} | ${tribe.borgCount} | ${borgs} |`);
      }
    }

    if (group.sharedAssets.length > 0) {
      lines.push("");
      lines.push("Shared/global leads:");
      for (const asset of group.sharedAssets.slice(0, 8)) {
        lines.push(`- \`${asset.path}\` (${asset.role}, ${asset.confidence})`);
      }
    }
  }

  lines.push("");
  lines.push("## Attachment Bone Candidates");
  lines.push("");
  lines.push(
    "DAE exports usually expose generic `JOBJ_*` names. The candidates below are therefore structural: leaf/distal joints and object-bound joints, not confirmed hand/muzzle socket names.",
  );
  lines.push("");
  lines.push("| Borg | DAE | Candidate nodes | Notes |");
  lines.push("|---|---|---|---|");
  for (const borg of report.borgs.filter((entry) => entry.attachmentBoneCandidates.length > 0).slice(0, 24)) {
    const nodes = borg.attachmentBoneCandidates
      .slice(0, 5)
      .map((candidate) => `${candidate.nodeId} (${candidate.roleCandidate}, ${candidate.confidence})`)
      .join("<br>");
    const dae = unique(borg.attachmentBoneCandidates.map((candidate) => candidate.daePath)).join("<br>");
    lines.push(`| ${borg.id} ${borg.name} | \`${dae}\` | ${nodes} | generic JOBJ names require visual/runtime confirmation |`);
  }

  lines.push("");
  lines.push("## MOT Attack Clips Needing Runtime Trace");
  lines.push("");
  lines.push(
    "Every row below needs runtime trace before code should bind an effect or projectile to a bone. Static MOT data gives bank/slot/offset, but not the spawned asset id, spawn frame, or socket.",
  );
  lines.push("");
  lines.push("| Priority | Borg | Families | Clip | Offset | Reason |");
  lines.push("|---|---|---|---|---|---|");
  for (const row of report.runtimeTraceQueue.slice(0, 80)) {
    lines.push(
      `| ${row.priority} | ${row.borgId} ${row.borgName} | ${row.families.join(", ")} | bank ${row.bankIndex} slot ${row.slotIndex} | ${row.sourceBlobOffset} | ${row.reason} |`,
    );
  }
  if (report.runtimeTraceQueue.length > 80) {
    lines.push(`| ... | ... | ... | ... | ... | ${report.runtimeTraceQueue.length - 80} more rows in JSON |`);
  }

  lines.push("");
  lines.push("## Data/Hit Findings");
  lines.push("");
  lines.push("- `pl####data.bin` files were inspected as raw 432-byte big-endian word tables; field names are still unknown.");
  lines.push("- `pl####hit.bin` files use a 0x20-byte remap header plus 32 actor records of 0xF4 bytes, but record fields are not mapped to actions or bones.");
  lines.push("- `it####_mdl.arz` item-model archives are strong attachment leads when linked to weapon-like borgs, but ARZ decompression is still a blocker for model export.");
  lines.push("- `efct.*`, `ptcl00.*`, `hit*.bin`, and `comhit*.bin` remain shared/global effect and impact leads rather than borg-specific sockets.");
  lines.push("");

  return `${lines.join("\n")}\n`;
}

async function main() {
  const [
    animationPlan,
    weapons,
    particles,
    borgAssets,
    hitInventory,
    borgData,
    modelManifest,
  ] = await Promise.all([
    readJson(paths.borgAnimationPlan),
    readJson(paths.weaponsEffectsProjectiles),
    readJson(paths.particleEffectInventory),
    readJson(paths.borgAssets),
    readJson(paths.hitBinInventory),
    readJson(paths.borgData),
    readJsonIfExists(paths.modelManifest, []),
  ]);

  const borgMetadata = new Map((borgData.borgs ?? []).map((borg) => [String(borg.id).toLowerCase(), borg]));
  const borgAssetRecords = new Map((borgAssets.records ?? []).map((record) => [String(record.id).toLowerCase(), record]));
  const animationBorgs = new Map((animationPlan.borgs ?? []).map((borg) => [String(borg.id).toLowerCase(), borg]));
  const hitByBorg = new Map((hitInventory.files?.player ?? []).map((file) => [String(file.linkedBorgId).toLowerCase(), file]));
  const daeByBorg = await discoverDaeInspections(modelManifest);

  const evidence = collectAssetEvidence(weapons, particles);
  const evidenceByBorg = new Map();
  const sharedAssets = summarizeSharedAssets(evidence);

  for (const item of evidence) {
    if (!item.linkedBorgId) continue;
    const id = item.linkedBorgId.toLowerCase();
    const list = evidenceByBorg.get(id) ?? [];
    list.push(item);
    evidenceByBorg.set(id, list);
  }

  for (const [id, record] of borgAssetRecords) {
    const expectedItem = itemAttachmentNameForBorg(id);
    const itemPath = `${paths.afsRoot}/${expectedItem}`;
    if (!(await exists(itemPath))) continue;
    const metadata = borgMetadata.get(id) ?? record;
    const familyKeys = normalizeFamily(`${metadata?.name ?? ""} ${metadata?.tribe ?? ""} ${metadata?.type ?? ""}`);
    if (familyKeys.length === 0) continue;
    const list = evidenceByBorg.get(id) ?? [];
    if (!list.some((item) => item.path === itemPath)) {
      list.push({
        source: "item/effect archive names",
        path: itemPath,
        name: expectedItem,
        role: "compressed item/attachment model",
        extension: ".arz",
        sizeBytes: null,
        linkedBorgId: id,
        linkedBorgName: metadata?.name ?? null,
        confidence: familyKeys.includes("sword") || familyKeys.includes("gun") ? "High" : "Medium",
        familyKeys,
        sourceFamilies: familyKeys.map((family) => ({
          family,
          confidence: "Medium",
          reason: "it####_mdl.arz name matches linked borg id",
        })),
        reason: "it####_mdl.arz name matches linked borg id and is a likely item/attachment model archive",
        needs: ["ARZ decompression/list integration before model export"],
        blocker: "ARZ decompression is required before attachment model export",
      });
      evidenceByBorg.set(id, list);
    }
  }

  const dataInspectionCache = new Map();
  async function dataInspectionsFor(record, id) {
    const sourceFiles = sourceFilesForRecord(record);
    const pathsToInspect = unique([
      ...sourceFiles.dataBins.map((file) => file.path),
      `${paths.afsRoot}/${id}data.bin`,
    ]);
    const out = [];
    for (const relPath of pathsToInspect) {
      if (!(await exists(relPath))) continue;
      if (!dataInspectionCache.has(relPath)) {
        dataInspectionCache.set(relPath, await inspectDataBin(relPath));
      }
      out.push(dataInspectionCache.get(relPath));
    }
    return out;
  }

  const mappedIds = unique([
    ...evidenceByBorg.keys(),
    ...[...daeByBorg.keys()].filter((id) => evidenceByBorg.has(id)),
  ]).sort();

  const borgs = [];
  for (const id of mappedIds) {
    const metadata = borgMetadata.get(id);
    const assetRecord = borgAssetRecords.get(id);
    const itemEvidence = (evidenceByBorg.get(id) ?? []).sort((a, b) => {
      const conf = compareConfidence(a, b);
      if (conf !== 0) return conf;
      return a.path.localeCompare(b.path);
    });
    borgs.push(
      buildBorgRecord({
        id,
        metadata,
        assetRecord,
        animationBorg: animationBorgs.get(id),
        daeInspections: daeByBorg.get(id) ?? [],
        hitFile: hitByBorg.get(id),
        dataInspections: await dataInspectionsFor(assetRecord, id),
        evidence: itemEvidence,
      }),
    );
  }

  borgs.sort((a, b) => a.tribe.localeCompare(b.tribe) || a.id.localeCompare(b.id));

  const families = buildFamilyGroups(borgs, sharedAssets);
  const runtimeTraceQueue = buildRuntimeTraceQueue(borgs);

  const report = {
    schema: "weapon-attachment-map.v1",
    generatedAt: new Date().toISOString(),
    generatedBy: "scripts/map-weapon-attachments.mjs",
    inputs: paths,
    notes: [
      "This is an evidence map, not runtime binding behavior.",
      "DAE node names are usually generic JOBJ labels; structural attachment candidates are intentionally conservative.",
      "All MOT attack/action candidates still need runtime trace before spawning browser projectiles/effects.",
    ],
    summary: {
      mappedBorgCount: borgs.length,
      sharedAssetCount: sharedAssets.length,
      familyBorgCounts: Object.fromEntries(targetFamilies.map((family) => [family, families[family].borgCount])),
      borgsWithDaeAttachmentCandidates: borgs.filter((borg) => borg.attachmentBoneCandidates.length > 0).length,
      runtimeTraceAttackClipCount: runtimeTraceQueue.length,
      sourceEvidenceCount: evidence.length,
      dataBinInspectedCount: borgs.reduce((sum, borg) => sum + borg.dataBinInspection.length, 0),
      hitBinInspectedCount: borgs.filter((borg) => borg.hitBinInspection).length,
    },
    sharedAssets,
    families,
    borgs,
    runtimeTraceQueue,
  };

  await fs.mkdir(abs(path.dirname(paths.outputJson)), { recursive: true });
  await fs.writeFile(abs(paths.outputJson), `${JSON.stringify(report, null, 2)}\n`);
  await fs.writeFile(abs(paths.outputMarkdown), makeMarkdown(report));

  console.log(`wrote ${paths.outputJson}`);
  console.log(`wrote ${paths.outputMarkdown}`);
  console.log(`mapped ${report.summary.mappedBorgCount} borgs`);
  console.log(`runtime trace attack clips: ${report.summary.runtimeTraceAttackClipCount}`);
}

main().catch((error) => {
  console.error(error);
  process.exitCode = 1;
});
