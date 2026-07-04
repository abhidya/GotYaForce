#!/usr/bin/env node
import { mkdir, readdir, readFile, stat, writeFile } from "node:fs/promises";
import path from "node:path";
import { parseTplMetadata } from "../packages/formats/src/tpl.ts";

const repoRoot = process.cwd();
const scriptPath = "scripts/inventory-ui-hud-assets.mjs";
const outputDir = "research/asset-inventory";
const jsonOut = path.join(outputDir, "ui-hud-assets.json");
const mdOut = path.join(outputDir, "ui-hud-assets.md");

const paths = {
  afsRoot: "user-data/GG4E/afs_data/root",
  gameMain: "apps/game/src/main.ts",
  uiPackage: "apps/game/src/ui/index.ts",
  tplFormat: "packages/formats/src/tpl.ts",
  mdtFormat: "packages/formats/src/mdt.ts",
  arcSpec: "research/format-specs/arc-hsd-format.md",
  adventureFlowJson: "research/asset-inventory/adventure-flow-ai.json",
  publicRoot: "apps/game/public",
  publicModels: "apps/game/public/models",
  publicStages: "apps/game/public/stages",
  modelsExport: "user-data/GG4E/models-export",
  gltfExport: "user-data/GG4E/gltf-export",
  convertedRoot: "user-data/converted",
};

const categoryDefinitions = [
  {
    id: "main-menu",
    label: "main menu",
    intent: "Title, general menu, shared icon/font, and boot/error screen candidates.",
    pattern: /^(titles|as_icon|ascii|font_00|icon|diskerr|optn00_mdl|tl00_mdl|staff00_mdl)\.(tpl|bin|arc)$/i,
  },
  {
    id: "adventure-select",
    label: "Adventure select",
    intent: "Adventure/world/versus-select model and icon candidates.",
    pattern: /^(vsel00_mdl|vsel01_mdl|vs[0-9a-f]+|nwld[0-9]{2}_mdl|arrow_mdl)\.(arc|tpl)$/i,
  },
  {
    id: "force-setup",
    label: "force setup",
    intent: "Force-building, collection, box, GET, and unit-list candidates.",
    pattern: /^(unitall_mdl|allbox|trialbox|box00_mdl|plcmndata|name00_mdl|mcmg00_mdl|gets|gets[0-9]{2}_mdl|mn[0-9a-f]{4}|rpot[0-9]{2}_mdl|trade00_mdl)\.(arc|bin|pzz|tpl)$/i,
  },
  {
    id: "mission-intro-load",
    label: "mission intro/load",
    intent: "Briefing, entry, loading, message, eyecatch, and face-dialog candidates.",
    pattern: /^(firstld|brif00_mdl|entry00_mdl|msg[0-9]+|mc_msg[0-9]+|nm_msg|sh_msg|tr_msg|face[0-9a-f]{4}(_mdl)?|eyecatch[0-9]+|acd_end)\.(pzz|arc|mdt|tpl)$/i,
  },
  {
    id: "battle-hud",
    label: "battle HUD",
    intent: "HUD banners, portraits, mini text, targeting arrow, and common battle data.",
    pattern: /^(bn[0-9a-f]{4}|face[0-9a-f]{4}(_mdl)?|font_00|ascii|mini_t|as_icon|arrow_mdl|comhit2?|cmn_data|dc[0-9]+|fmg00_mdl)\.(tpl|arc|bin|pzz)$/i,
  },
  {
    id: "portraits-banners-fonts",
    label: "portraits/banners/fonts",
    intent: "Reusable visual families needed by menus, force setup, dialogs, and battle HUD.",
    pattern: /^(bn[0-9a-f]{4}|mn[0-9a-f]{4}|face[0-9a-f]{4}(_mdl)?|font_00|ascii|mini_t|titles)\.(tpl|arc)$/i,
  },
];

function abs(file) {
  return path.resolve(repoRoot, file);
}

function rel(file) {
  let normalized = file;
  if (normalized.startsWith("/")) {
    const windowsPath = normalized.match(/^\/([A-Za-z]:\/.*)$/);
    if (windowsPath) normalized = windowsPath[1];
  }
  return path.relative(repoRoot, normalized).replaceAll(path.sep, "/");
}

function relJoin(...parts) {
  return path.join(...parts).replaceAll(path.sep, "/");
}

async function readText(file) {
  return readFile(abs(file), "utf8");
}

async function tryReadText(file) {
  try {
    return await readText(file);
  } catch {
    return "";
  }
}

async function statPath(file) {
  try {
    const s = await stat(abs(file));
    return {
      path: rel(file),
      exists: true,
      type: s.isDirectory() ? "directory" : s.isFile() ? "file" : "other",
      bytes: s.isFile() ? s.size : null,
    };
  } catch {
    return { path: rel(file), exists: false, type: null, bytes: null };
  }
}

async function listDirFiles(dir) {
  try {
    const entries = await readdir(abs(dir), { withFileTypes: true });
    const files = [];
    for (const entry of entries) {
      if (!entry.isFile()) continue;
      const file = relJoin(dir, entry.name);
      const s = await stat(abs(file));
      files.push({
        name: entry.name,
        path: file,
        absPath: abs(file),
        ext: path.extname(entry.name).toLowerCase(),
        bytes: s.size,
      });
    }
    return files.sort((a, b) => a.name.localeCompare(b.name));
  } catch {
    return [];
  }
}

async function listRecursive(root) {
  const out = [];
  async function walk(current) {
    let entries;
    try {
      entries = await readdir(current, { withFileTypes: true });
    } catch {
      return;
    }

    for (const entry of entries) {
      const full = path.join(current, entry.name);
      if (entry.isDirectory()) {
        await walk(full);
      } else if (entry.isFile()) {
        const s = await stat(full);
        out.push({
          path: rel(full),
          absPath: full,
          name: entry.name,
          ext: path.extname(entry.name).toLowerCase(),
          bytes: s.size,
        });
      }
    }
  }

  await walk(abs(root));
  return out.sort((a, b) => a.path.localeCompare(b.path));
}

function sample(values, limit = 12) {
  return [...values].sort((a, b) => String(a).localeCompare(String(b))).slice(0, limit);
}

function countBy(values, keyFn) {
  const counts = new Map();
  for (const value of values) {
    const key = keyFn(value);
    counts.set(key, (counts.get(key) ?? 0) + 1);
  }
  return Object.fromEntries([...counts.entries()].sort(([a], [b]) => String(a).localeCompare(String(b))));
}

function findLine(text, needle) {
  if (!needle) return null;
  const lines = text.split(/\r?\n/);
  const index = lines.findIndex((line) => line.includes(needle));
  return index === -1 ? null : index + 1;
}

function refWithLine(file, text, needle) {
  const line = findLine(text, needle);
  return line ? `${rel(file)}:${line}` : rel(file);
}

function classifyAsset(name) {
  return categoryDefinitions
    .filter((category) => category.pattern.test(name))
    .map((category) => category.id);
}

function readCString(buffer, offset, maxLength = 256) {
  if (offset < 0 || offset >= buffer.length) return null;
  const bytes = [];
  for (let i = offset; i < buffer.length && bytes.length < maxLength; i += 1) {
    const value = buffer[i];
    if (value === 0) break;
    if (value < 0x20 || value > 0x7e) return null;
    bytes.push(value);
  }
  return bytes.length ? Buffer.from(bytes).toString("ascii") : "";
}

function hexBytes(buffer, length = 16) {
  return [...buffer.subarray(0, Math.min(length, buffer.length))]
    .map((byte) => byte.toString(16).padStart(2, "0"))
    .join(" ");
}

function parseTpl(buffer) {
  return parseTplMetadata(buffer);
}

function parseHsdDat(buffer, base, container) {
  if (base + 0x20 > buffer.length) return null;
  const fileSize = buffer.readUInt32BE(base);
  const dataBlockSize = buffer.readUInt32BE(base + 0x04);
  const relocCount = buffer.readUInt32BE(base + 0x08);
  const rootCount = buffer.readUInt32BE(base + 0x0c);
  const externalRefCount = buffer.readUInt32BE(base + 0x10);

  if (fileSize <= 0 || base + fileSize > buffer.length) return null;
  const relocTableOffset = base + 0x20 + dataBlockSize;
  const rootTableOffset = relocTableOffset + relocCount * 4;
  const externalRefTableOffset = rootTableOffset + rootCount * 8;
  const symbolTableOffset = externalRefTableOffset + externalRefCount * 8;
  if (relocTableOffset > base + fileSize || rootTableOffset > base + fileSize || symbolTableOffset > base + fileSize) {
    return null;
  }

  const rootNames = [];
  for (let i = 0; i < Math.min(rootCount, 64); i += 1) {
    const entryOffset = rootTableOffset + i * 8;
    if (entryOffset + 8 > base + fileSize) break;
    const dataOffset = buffer.readUInt32BE(entryOffset);
    const stringOffset = buffer.readUInt32BE(entryOffset + 4);
    rootNames.push({
      index: i,
      dataOffset,
      stringOffset,
      name: readCString(buffer, symbolTableOffset + stringOffset),
    });
  }

  return {
    parseStatus: "ok",
    container,
    datOffset: base,
    fileSize,
    dataBlockSize,
    relocCount,
    rootCount,
    externalRefCount,
    rootNames,
  };
}

function parseHsdArc(buffer) {
  const bare = parseHsdDat(buffer, 0, "bare-hsd-dat");
  if (bare && bare.fileSize === buffer.length) return bare;

  if (buffer.length > 0x120) {
    const wrapperOffset = buffer.readUInt32BE(0);
    if (wrapperOffset === 0x100) {
      const wrapped = parseHsdDat(buffer, 0x100, "wrapped-hsd-dat");
      if (wrapped) {
        return {
          ...wrapped,
          wrapper: {
            datOffset: wrapperOffset,
            field04: buffer.readUInt32BE(0x04),
            field08: buffer.readUInt32BE(0x08),
          },
        };
      }
    }
  }

  return {
    parseStatus: "not recognized as HSD DAT",
    firstBytesHex: hexBytes(buffer),
  };
}

function parseMdt(buffer) {
  const printable = [];
  let current = "";
  for (const byte of buffer) {
    if (byte >= 0x20 && byte <= 0x7e) {
      current += String.fromCharCode(byte);
    } else {
      if (current.length >= 6) printable.push(current);
      current = "";
    }
    if (printable.length >= 8) break;
  }
  if (current.length >= 6 && printable.length < 8) printable.push(current);

  return {
    parseStatus: "raw-only",
    firstBytesHex: hexBytes(buffer),
    printableAsciiSamples: printable,
    blocker: "MDT text decode needs NeoGF mdttool port/integration before browser-ready message JSON.",
  };
}

function parseBinary(buffer) {
  return {
    parseStatus: "raw-only",
    firstBytesHex: hexBytes(buffer),
  };
}

async function parseAsset(file) {
  const buffer = await readFile(file.absPath);
  if (file.ext === ".tpl") return { tpl: parseTpl(buffer) };
  if (file.ext === ".arc" || file.name.toLowerCase().endsWith("_mdl.arc")) return { hsd: parseHsdArc(buffer) };
  if (file.ext === ".mdt") return { mdt: parseMdt(buffer) };
  if (file.ext === ".bin") return { binary: parseBinary(buffer) };
  if (file.ext === ".pzz") return { archive: { parseStatus: "source-pzz", firstBytesHex: hexBytes(buffer) } };
  return { binary: parseBinary(buffer) };
}

function stemsForSource(name) {
  const parsed = path.parse(name);
  const stem = parsed.name.toLowerCase();
  const stems = new Set([stem]);
  if (stem.endsWith("_mdl")) stems.add(stem.slice(0, -4));
  return [...stems].filter(Boolean);
}

function findConvertedOutputs(source, convertedFiles) {
  const stems = stemsForSource(source.name);
  const extensions = new Set([".dae", ".png", ".ktx2", ".webp", ".json", ".glb", ".gltf", ".obj"]);
  return convertedFiles
    .filter((file) => extensions.has(file.ext))
    .filter((file) => {
      const lowerPath = file.path.toLowerCase().replaceAll("\\", "/");
      const lowerName = path.parse(file.name).name.toLowerCase();
      const segments = lowerPath.split("/");
      return stems.some((stem) => lowerName === stem || lowerName.startsWith(`${stem}_`) || segments.includes(stem));
    })
    .map((file) => ({ path: file.path, bytes: file.bytes }))
    .sort((a, b) => a.path.localeCompare(b.path));
}

function blockersForAsset(asset) {
  const blockers = [];
  const lower = asset.name.toLowerCase();
  if (asset.ext === ".tpl") blockers.push("TPL decode to PNG/KTX2 is not implemented in @gf/formats yet.");
  if (lower.endsWith("_mdl.arc") || asset.ext === ".arc") blockers.push("HSD model export exists for stages/borgs, but this UI/archive is not exported into public runtime yet.");
  if (asset.ext === ".mdt") blockers.push("MDT text needs NeoGF mdttool port/integration to JSON.");
  if (asset.ext === ".bin") blockers.push("BIN layout/schema is unidentified for UI placement/control data.");
  if (asset.ext === ".pzz") blockers.push("PZZ archive must be unpacked/listed before UI load sequencing can be mapped.");
  if (asset.convertedOutputs.length === 0) blockers.push("No matching browser-ready converted output found.");
  return [...new Set(blockers)];
}

function summarizeTplAssets(assets) {
  const tplAssets = assets.filter((asset) => asset.parse.tpl?.parseStatus === "ok");
  const images = tplAssets.flatMap((asset) => asset.parse.tpl.images.map((image) => ({ asset, image })));
  return {
    fileCount: tplAssets.length,
    imageCount: images.length,
    formatCounts: countBy(images, ({ image }) => image.format ?? "unknown"),
    dimensionCounts: countBy(images, ({ image }) => `${image.width ?? "?"}x${image.height ?? "?"}`),
    samples: sample(
      images.map(({ asset, image }) => `${asset.name}: ${image.width}x${image.height} ${image.format}`),
      18,
    ),
  };
}

function familyForPrefix(assets, prefix) {
  const files = assets.filter((asset) => new RegExp(`^${prefix}[0-9a-f]{4}\\.tpl$`, "i").test(asset.name));
  const ids = files.map((asset) => asset.name.slice(prefix.length, prefix.length + 4).toLowerCase()).sort();
  return {
    prefix,
    count: files.length,
    ids,
    byHighByte: countBy(ids, (id) => id.slice(0, 2)),
    tpl: summarizeTplAssets(files),
    samples: sample(files.map((asset) => asset.name), 20),
  };
}

function buildFamilies(assets) {
  const banners = familyForPrefix(assets, "bn");
  const menuThumbnails = familyForPrefix(assets, "mn");
  const bannerIds = new Set(banners.ids);
  const menuIds = new Set(menuThumbnails.ids);
  const faceFiles = assets.filter((asset) => /^face[0-9a-f]{4}(_mdl)?\.(tpl|arc)$/i.test(asset.name));
  const faceRecords = faceFiles.map((asset) => {
    const match = /^face([0-9a-f]{2})([0-9a-f]{2})(_mdl)?\.(tpl|arc)$/i.exec(asset.name);
    return {
      name: asset.name,
      character: match?.[1]?.toLowerCase() ?? "??",
      slot: match?.[2]?.toLowerCase() ?? "??",
      kind: asset.ext === ".tpl" ? "portrait-texture" : "portrait-model",
      bytes: asset.bytes,
    };
  });
  const fontFiles = assets.filter((asset) => /^(font_00|ascii|mini_t|titles)\.tpl$/i.test(asset.name));

  return {
    banners: {
      ...banners,
      menuThumbnailPairing: {
        pairedCount: banners.ids.filter((id) => menuIds.has(id)).length,
        missingMenuThumbnailIds: banners.ids.filter((id) => !menuIds.has(id)),
      },
    },
    menuThumbnails: {
      ...menuThumbnails,
      bannerPairing: {
        pairedCount: menuThumbnails.ids.filter((id) => bannerIds.has(id)).length,
        missingBannerIds: menuThumbnails.ids.filter((id) => !bannerIds.has(id)),
      },
    },
    portraits: {
      fileCount: faceFiles.length,
      tplCount: faceFiles.filter((asset) => asset.ext === ".tpl").length,
      modelArcCount: faceFiles.filter((asset) => asset.ext === ".arc").length,
      byCharacter: countBy(faceRecords, (record) => record.character),
      bySlot: countBy(faceRecords, (record) => record.slot),
      records: faceRecords.sort((a, b) => a.name.localeCompare(b.name)),
      tpl: summarizeTplAssets(faceFiles.filter((asset) => asset.ext === ".tpl")),
    },
    fontsAndSharedText: {
      count: fontFiles.length,
      files: fontFiles.map((asset) => ({
        name: asset.name,
        path: asset.path,
        bytes: asset.bytes,
        tpl: asset.parse.tpl ?? null,
        blockers: asset.blockers,
      })),
      tpl: summarizeTplAssets(fontFiles),
    },
  };
}

function buildCategorySummaries(assets) {
  return categoryDefinitions.map((definition) => {
    const categoryAssets = assets.filter((asset) => asset.categories.includes(definition.id));
    const converted = categoryAssets.filter((asset) => asset.convertedOutputs.length > 0);
    const uniqueBlockers = [...new Set(categoryAssets.flatMap((asset) => asset.blockers))].sort();
    return {
      id: definition.id,
      label: definition.label,
      intent: definition.intent,
      sourceCount: categoryAssets.length,
      sourceBytes: categoryAssets.reduce((sum, asset) => sum + asset.bytes, 0),
      convertedCount: converted.length,
      sourceExtensionCounts: countBy(categoryAssets, (asset) => asset.ext || "(none)"),
      tpl: summarizeTplAssets(categoryAssets),
      blockers: uniqueBlockers,
      samples: sample(categoryAssets.map((asset) => asset.name), 18),
      convertedSamples: sample(converted.map((asset) => `${asset.name} -> ${asset.convertedOutputs[0].path}`), 12),
    };
  });
}

function publicRuntimeCounts(files) {
  return {
    fileCount: files.length,
    daeCount: files.filter((file) => file.ext === ".dae").length,
    pngCount: files.filter((file) => file.ext === ".png").length,
    jsonCount: files.filter((file) => file.ext === ".json").length,
    byTopDirectory: countBy(files, (file) => file.path.split("/").slice(0, 3).join("/")),
  };
}

function makeMarkdown(inventory) {
  const lines = [];
  const add = (line = "") => lines.push(line);
  const md = (value) => String(value ?? "").replace(/\|/g, "\\|");

  add("# Original Adventure UI/HUD/Menu Asset Inventory");
  add();
  add(`Generated by \`${inventory.generatedBy}\` at \`${inventory.generatedAt}\`.`);
  add("Scope: source-original Adventure UI/HUD/menu assets only. Browser source was inspected read-only and not edited.");
  add();
  add("## Summary");
  add();
  add(`- Source candidates: ${inventory.summary.sourceCandidateCount} files (${inventory.summary.sourceCandidateBytes} bytes) under \`${inventory.inputs.assetRoot.path}\`.`);
  add(`- TPL textures: ${inventory.summary.tpl.fileCount} files, ${inventory.summary.tpl.imageCount} images; common formats: ${Object.entries(inventory.summary.tpl.formatCounts).map(([format, count]) => `${format} ${count}`).join(", ") || "none"}.`);
  add(`- HSD model archives: ${inventory.summary.hsdArchiveCount}; MDT message files: ${inventory.summary.mdtFileCount}; raw BIN/PZZ layout or archive files: ${inventory.summary.rawDataFileCount}.`);
  add(`- Matching converted UI/menu outputs: ${inventory.summary.convertedUiCandidateCount}. Public runtime currently has ${inventory.conversionStatus.publicRuntime.daeCount} DAE and ${inventory.conversionStatus.publicRuntime.pngCount} PNG files, but they are stage/borg exports, not these original UI groups.`);
  add(`- Current browser UI evidence: \`${inventory.currentRuntime.fakeUiEvidence.map((item) => item.ref).join("`, `")}\`.`);
  add();
  add("## Groups");
  add();
  add("| Group | Source | Converted | TPL images | Blockers | Samples |");
  add("| --- | ---: | ---: | ---: | --- | --- |");
  for (const group of inventory.categories) {
    add(`| ${md(group.label)} | ${group.sourceCount} | ${group.convertedCount} | ${group.tpl.imageCount} | ${md(group.blockers.join("; ") || "none")} | ${group.samples.map((name) => `\`${name}\``).join(", ")} |`);
  }
  add();
  add("## Visual Families");
  add();
  add(`- Banner TPLs: ${inventory.families.banners.count} \`bn####.tpl\` files, usually ${Object.keys(inventory.families.banners.tpl.dimensionCounts).join(", ") || "unknown"}; paired with ${inventory.families.banners.menuThumbnailPairing.pairedCount} \`mn####.tpl\` ids.`);
  add(`- Menu thumbnail TPLs: ${inventory.families.menuThumbnails.count} \`mn####.tpl\` files; missing banner ids: ${inventory.families.menuThumbnails.bannerPairing.missingBannerIds.join(", ") || "none"}.`);
  add(`- Face assets: ${inventory.families.portraits.tplCount} portrait TPLs and ${inventory.families.portraits.modelArcCount} face model archives across ${Object.keys(inventory.families.portraits.byCharacter).length} character groups.`);
  add(`- Fonts/shared text: ${inventory.families.fontsAndSharedText.files.map((file) => `\`${file.name}\``).join(", ") || "none"}.`);
  add();
  add("## Key Assets");
  add();
  add("| Asset | Groups | Parse | Converted | Blockers |");
  add("| --- | --- | --- | --- | --- |");
  for (const asset of inventory.keyAssets) {
    const parse = asset.parse.tpl?.images?.[0]
      ? `${asset.parse.tpl.imageCount} TPL image(s), ${asset.parse.tpl.images[0].width}x${asset.parse.tpl.images[0].height} ${asset.parse.tpl.images[0].format}`
      : asset.parse.hsd?.parseStatus === "ok"
        ? `${asset.parse.hsd.container}, roots ${asset.parse.hsd.rootNames.map((root) => root.name).filter(Boolean).join(", ") || asset.parse.hsd.rootCount}`
        : asset.parse.mdt
          ? asset.parse.mdt.parseStatus
          : asset.parse.binary
            ? asset.parse.binary.parseStatus
            : asset.parse.archive?.parseStatus ?? "raw";
    add(`| \`${asset.name}\` | ${asset.categories.map((id) => md(inventory.categoryLabels[id] ?? id)).join(", ")} | ${md(parse)} | ${asset.convertedOutputs.length ? asset.convertedOutputs.map((file) => `\`${file.path}\``).join("<br>") : "none"} | ${md(asset.blockers.join("; "))} |`);
  }
  add();
  add("## Already Converted");
  add();
  if (inventory.conversionStatus.convertedUiAssets.length === 0) {
    add("- No matching browser-ready converted output was found for the original UI/HUD/menu candidates.");
  } else {
    for (const asset of inventory.conversionStatus.convertedUiAssets) {
      add(`- \`${asset.name}\`: ${asset.convertedOutputs.map((file) => `\`${file.path}\``).join(", ")}`);
    }
  }
  add(`- Related non-public conversion context: ${inventory.conversionStatus.relatedConvertedContext.samples.map((item) => `\`${item}\``).join(", ") || "none"}.`);
  add();
  add("## Blockers");
  add();
  for (const blocker of inventory.blockers) {
    add(`- ${blocker.area}: ${blocker.finding} Refs: ${blocker.refs.map((ref) => `\`${ref}\``).join(", ")}.`);
  }
  add();
  add("## Preparation Path");
  add();
  for (const step of inventory.preparationPath) {
    add(`- ${step.step}: ${step.action}`);
  }
  add();
  add("## Verification");
  add();
  add("- Re-run scanner: `rtk node scripts/inventory-ui-hud-assets.mjs`.");
  add("- JSON parse check: `rtk node -e \"JSON.parse(require('fs').readFileSync('research/asset-inventory/ui-hud-assets.json','utf8')); console.log('json ok')\"`.");
  add("- No browser source edit is performed by this inventory.");
  add();

  return `${lines.join("\n")}\n`;
}

const [rootFiles, publicFiles, modelExportFiles, gltfExportFiles, convertedFiles, gameMainText, uiPackageText, tplText, mdtText, arcSpecText] =
  await Promise.all([
    listDirFiles(paths.afsRoot),
    listRecursive(paths.publicRoot),
    listRecursive(paths.modelsExport),
    listRecursive(paths.gltfExport),
    listRecursive(paths.convertedRoot),
    tryReadText(paths.gameMain),
    tryReadText(paths.uiPackage),
    tryReadText(paths.tplFormat),
    tryReadText(paths.mdtFormat),
    tryReadText(paths.arcSpec),
  ]);

const convertedSearchFiles = [...publicFiles, ...modelExportFiles, ...gltfExportFiles, ...convertedFiles];
const candidateFiles = rootFiles.filter((file) => classifyAsset(file.name).length > 0);
const assets = [];

for (const file of candidateFiles) {
  const convertedOutputs = findConvertedOutputs(file, convertedSearchFiles);
  const parse = await parseAsset(file);
  const categories = classifyAsset(file.name);
  const asset = {
    name: file.name,
    path: file.path,
    bytes: file.bytes,
    ext: file.ext,
    categories,
    parse,
    convertedOutputs,
  };
  asset.blockers = blockersForAsset(asset);
  asset.readiness = convertedOutputs.length > 0 && asset.blockers.length === 0 ? "browser-ready" : "source-inventory-ready";
  assets.push(asset);
}

assets.sort((a, b) => a.name.localeCompare(b.name));

const categoryLabels = Object.fromEntries(categoryDefinitions.map((category) => [category.id, category.label]));
const categories = buildCategorySummaries(assets);
const families = buildFamilies(assets);
const convertedUiAssets = assets.filter((asset) => asset.convertedOutputs.length > 0);
const relatedConvertedContext = convertedSearchFiles
  .filter((file) => /\.(dae|png|json)$/i.test(file.name))
  .filter((file) => /\/(box00|st0[0-2]|pl[0-9a-f]{4})\//i.test(file.path.replaceAll("\\", "/")))
  .map((file) => file.path)
  .sort();

const keyAssetNames = new Set([
  "titles.tpl",
  "as_icon.tpl",
  "font_00.tpl",
  "icon.bin",
  "vsel00_mdl.arc",
  "vsel01_mdl.arc",
  "unitall_mdl.arc",
  "allbox.bin",
  "plcmndata.bin",
  "firstld.pzz",
  "brif00_mdl.arc",
  "entry00_mdl.arc",
  "msg00.mdt",
  "msg01.mdt",
  "mc_msg00.mdt",
  "sh_msg.mdt",
  "tr_msg.mdt",
  "bn0000.tpl",
  "mn0000.tpl",
  "face0001.tpl",
  "face0000_mdl.arc",
  "arrow_mdl.arc",
  "comhit.bin",
  "mini_t.tpl",
]);

const refs = {
  gameStartsArena: refWithLine(paths.gameMain, gameMainText, 'let screen: Screen = "arena"'),
  gameInlineUi: refWithLine(paths.gameMain, gameMainText, "ui.innerHTML ="),
  gameFakeHud: refWithLine(paths.gameMain, gameMainText, "No CPU actors spawned"),
  gameAdventureOnly: refWithLine(paths.gameMain, gameMainText, "Only Adventure is enabled"),
  gameEnemyText: refWithLine(paths.gameMain, gameMainText, "Enemy force:"),
  uiPackage: refWithLine(paths.uiPackage, uiPackageText, "menus, HUD, and front-end layout"),
  tplTodo: refWithLine(paths.tplFormat, tplText, "TODO: implement decode"),
  mdtTodo: refWithLine(paths.mdtFormat, mdtText, "TODO: port mdttool"),
  arcExport: refWithLine(paths.arcSpec, arcSpecText, "FULL EXPORT PIPELINE WORKING"),
};

const summary = {
  sourceCandidateCount: assets.length,
  sourceCandidateBytes: assets.reduce((sum, asset) => sum + asset.bytes, 0),
  convertedUiCandidateCount: convertedUiAssets.length,
  hsdArchiveCount: assets.filter((asset) => asset.parse.hsd).length,
  mdtFileCount: assets.filter((asset) => asset.ext === ".mdt").length,
  rawDataFileCount: assets.filter((asset) => asset.ext === ".bin" || asset.ext === ".pzz").length,
  categoryCounts: Object.fromEntries(categories.map((category) => [category.id, category.sourceCount])),
  tpl: summarizeTplAssets(assets),
};

const inventory = {
  generatedBy: scriptPath,
  generatedAt: new Date().toISOString(),
  scope: "Original Adventure UI/HUD/menu asset inventory and preparation blockers. No browser source edits and no fake UI proposal.",
  inputs: {
    assetRoot: await statPath(paths.afsRoot),
    currentRuntimeReadOnly: await statPath(paths.gameMain),
    uiPackage: await statPath(paths.uiPackage),
    formatNotes: await Promise.all([statPath(paths.tplFormat), statPath(paths.mdtFormat), statPath(paths.arcSpec)]),
    conversionRoots: await Promise.all([statPath(paths.publicRoot), statPath(paths.modelsExport), statPath(paths.gltfExport), statPath(paths.convertedRoot)]),
    priorAdventureInventory: await statPath(paths.adventureFlowJson),
  },
  categoryLabels,
  summary,
  categories,
  families,
  keyAssets: assets.filter((asset) => keyAssetNames.has(asset.name.toLowerCase())),
  assets,
  conversionStatus: {
    convertedUiAssets: convertedUiAssets.map((asset) => ({
      name: asset.name,
      path: asset.path,
      categories: asset.categories,
      convertedOutputs: asset.convertedOutputs,
    })),
    relatedConvertedContext: {
      note: "Existing model/stage conversion proves the model pipeline is active, but these are not original UI/HUD/menu candidates unless matched above.",
      count: relatedConvertedContext.length,
      samples: sample(relatedConvertedContext, 20),
    },
    publicRuntime: publicRuntimeCounts(publicFiles),
  },
  currentRuntime: {
    path: rel(paths.gameMain),
    readOnlyFinding: "Current runtime renders a hand-written DOM menu/HUD shell and starts directly in arena; this inventory does not edit it.",
    fakeUiEvidence: [
      { ref: refs.gameStartsArena, finding: "Screen starts in arena instead of original title/menu flow." },
      { ref: refs.gameInlineUi, finding: "Menu/HUD is generated as inline DOM/CSS." },
      { ref: refs.gameFakeHud, finding: "HUD explicitly says CPU/original gameplay actors are not verified." },
      { ref: refs.gameAdventureOnly, finding: "Only Adventure shell is enabled in current fake menu." },
      { ref: refs.gameEnemyText, finding: "Enemy force appears as text, not original HUD/briefing assets." },
    ],
  },
  blockers: [
    {
      id: "tpl-decode",
      area: "TPL textures",
      finding: "Standard TPL headers parse, but @gf/formats still has no decoder to emit PNG/KTX2 for titles, banners, portraits, thumbnails, or fonts.",
      refs: [refs.tplTodo, "user-data/GG4E/afs_data/root/titles.tpl", "user-data/GG4E/afs_data/root/bn0000.tpl", "user-data/GG4E/afs_data/root/face0001.tpl"].filter(Boolean),
    },
    {
      id: "ui-hsd-export",
      area: "UI/select/briefing model archives",
      finding: "HSD export pipeline exists for other assets, but vsel00/vsel01/brif00/entry00/face archives are not exported into browser public assets.",
      refs: [refs.arcExport, "user-data/GG4E/afs_data/root/vsel00_mdl.arc", "user-data/GG4E/afs_data/root/brif00_mdl.arc", "user-data/GG4E/afs_data/root/entry00_mdl.arc"].filter(Boolean),
    },
    {
      id: "mdt-text",
      area: "Mission/menu text",
      finding: "msg*.mdt files are present, but the repo still needs an MDT text decoder/NeoGF mdttool integration before original copy can drive UI.",
      refs: [refs.mdtTodo, "user-data/GG4E/afs_data/root/msg00.mdt", "user-data/GG4E/afs_data/root/sh_msg.mdt"].filter(Boolean),
    },
    {
      id: "layout-bins",
      area: "UI layout/control data",
      finding: "icon.bin, allbox.bin, trialbox.bin, plcmndata.bin, and comhit*.bin are raw-only until their schemas are mapped.",
      refs: ["user-data/GG4E/afs_data/root/icon.bin", "user-data/GG4E/afs_data/root/allbox.bin", "user-data/GG4E/afs_data/root/comhit.bin"].filter(Boolean),
    },
    {
      id: "fake-runtime-ui",
      area: "Browser runtime UI",
      finding: "apps/game/src/main.ts contains hand-written DOM/CSS menu/HUD placeholders; those should not be extended as Adventure UI/HUD replacements.",
      refs: [refs.gameInlineUi, refs.gameFakeHud, refs.gameAdventureOnly].filter(Boolean),
    },
  ],
  preparationPath: [
    {
      step: "1. Texture manifest",
      action: "Decode the parsed TPL families to browser PNG/KTX2 and preserve source dimensions/formats in a UI texture manifest.",
    },
    {
      step: "2. Model archive export",
      action: "Batch-export vsel00/vsel01/brif00/entry00/face archives with the HSDRaw path used for stages/borgs, staged outside runtime source first.",
    },
    {
      step: "3. Text extraction",
      action: "Port or invoke NeoGF mdttool for msg*.mdt to produce message JSON before binding menus or briefings.",
    },
    {
      step: "4. Layout/schema pass",
      action: "Map icon.bin/allbox/trialbox/plcmndata/comhit schemas enough to place original sprites and HUD elements accurately.",
    },
    {
      step: "5. Runtime replacement gate",
      action: "Only replace the current fake DOM menu/HUD after the source assets above have converted outputs and verified screen-state mapping.",
    },
  ],
};

await mkdir(abs(outputDir), { recursive: true });
await writeFile(abs(jsonOut), `${JSON.stringify(inventory, null, 2)}\n`, "utf8");
await writeFile(abs(mdOut), makeMarkdown(inventory), "utf8");

console.log("ui/hud/menu asset inventory");
console.log(`source candidates: ${inventory.summary.sourceCandidateCount}`);
console.log(`tpl files: ${inventory.summary.tpl.fileCount}`);
console.log(`hsd archives: ${inventory.summary.hsdArchiveCount}`);
console.log(`converted UI candidates: ${inventory.summary.convertedUiCandidateCount}`);
console.log(`wrote ${rel(jsonOut)}`);
console.log(`wrote ${rel(mdOut)}`);
