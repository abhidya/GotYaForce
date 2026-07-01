#!/usr/bin/env node
import { mkdir, writeFile, readFile } from "node:fs/promises";
import path from "node:path";
import { unpack as unpackPzz } from "../packages/formats/src/pzz.ts";

const DEFAULT_REGION = "GG4E";
const borgDataPath = path.join("packages", "assets", "data", "borgs.json");

const familyTerms = {
  fire: ["fire", "flame", "burn", "blaze", "phoenix"],
  beam: ["beam", "laser", "plasma"],
  gun: ["gun", "bullet", "gatling", "revolver", "cannon", "tank", "arrow", "shuriken", "missile", "icbm", "bomb", "projectile", "shot"],
  sword: ["sword", "blade", "slash", "samurai", "knight", "axe", "hatchet", "chainsaw", "claw", "spike", "drill", "hammer"],
  trail: ["trail", "aura", "boost", "wing", "jet", "ghost", "shadow", "cyber"],
};

const options = parseArgs(process.argv.slice(2));
if (options.help) usage(0);

const repoRoot = path.resolve(".");
const assetRoot = path.join(repoRoot, "user-data", options.region, "afs_data", "root");
const outRoot = path.resolve(repoRoot, options.outRoot);
const manifestPath = path.resolve(repoRoot, options.manifest);
const borgMap = await readBorgMap();

const selected = [];
for (const borg of options.borgs) {
  const archivePath = path.join(assetRoot, `${borg}.pzz`);
  const archive = await readPzzArchive(archivePath, borg);
  for (const member of archive.members) {
    if (!memberMatches(member, options.members)) continue;
    selected.push({ borg, member });
  }
}

if (selected.length === 0) {
  console.log("extract-pzz-members: no members matched");
  process.exit(0);
}

await mkdir(outRoot, { recursive: true });
await mkdir(path.dirname(manifestPath), { recursive: true });
const manifestRecords = [];
for (const { borg, member } of selected) {
  const outPath = path.join(outRoot, member.inferredName);
  if (member.payload.length === 0) {
    console.log(`skip empty ${borg}#${member.memberId} ${member.inferredName}`);
    manifestRecords.push(buildManifestRecord(borg, member, null));
    continue;
  }
  await writeFile(outPath, member.payload);
  manifestRecords.push(buildManifestRecord(borg, member, outPath));
  console.log(
    `extract ${borg}#${member.memberId} ${member.inferredName} ` +
      `${member.flags.compressed ? "pzzp" : "raw"} ${member.payload.length} bytes -> ${rel(outPath)}`,
  );
}

const manifest = {
  generatedAt: new Date().toISOString(),
  script: "scripts/extract-pzz-members.mjs",
  region: options.region,
  assetRoot: rel(assetRoot),
  outRoot: rel(outRoot),
  selection: {
    borgs: options.borgs,
    members: [...options.members],
  },
  recordCount: manifestRecords.length,
  records: manifestRecords,
};
await writeFile(manifestPath, `${JSON.stringify(manifest, null, 2)}\n`);
console.log(`wrote manifest ${rel(manifestPath)} (${manifestRecords.length} record(s))`);

function parseArgs(args) {
  const parsed = {
    region: DEFAULT_REGION,
    outRoot: path.join("user-data", DEFAULT_REGION, "afs_data", "root"),
    manifest: path.join("research", "asset-inventory", "pzz-member-extraction-manifest.json"),
    borgs: [],
    members: new Set(["mot"]),
    help: false,
  };

  for (let i = 0; i < args.length; i += 1) {
    const arg = args[i];
    if (arg === "--help" || arg === "-h") {
      parsed.help = true;
    } else if (arg === "--region") {
      parsed.region = requiredValue(args, ++i, arg);
      parsed.outRoot = path.join("user-data", parsed.region, "afs_data", "root");
    } else if (arg.startsWith("--region=")) {
      parsed.region = arg.slice("--region=".length);
      parsed.outRoot = path.join("user-data", parsed.region, "afs_data", "root");
    } else if (arg === "--out-root") {
      parsed.outRoot = requiredValue(args, ++i, arg);
    } else if (arg.startsWith("--out-root=")) {
      parsed.outRoot = arg.slice("--out-root=".length);
    } else if (arg === "--manifest") {
      parsed.manifest = requiredValue(args, ++i, arg);
    } else if (arg.startsWith("--manifest=")) {
      parsed.manifest = arg.slice("--manifest=".length);
    } else if (arg === "--borg") {
      addBorgs(parsed.borgs, requiredValue(args, ++i, arg));
    } else if (arg.startsWith("--borg=")) {
      addBorgs(parsed.borgs, arg.slice("--borg=".length));
    } else if (arg === "--member") {
      addMembers(parsed.members, requiredValue(args, ++i, arg));
    } else if (arg.startsWith("--member=")) {
      addMembers(parsed.members, arg.slice("--member=".length));
    } else if (arg.startsWith("--")) {
      fail(`unknown option ${arg}`);
    } else {
      addBorgs(parsed.borgs, arg);
    }
  }

  if (parsed.borgs.length === 0 && !parsed.help) fail("pass at least one --borg <pl####>");
  return parsed;
}

function usage(code) {
  const stream = code === 0 ? process.stdout : process.stderr;
  stream.write(`usage: node scripts/extract-pzz-members.mjs --borg pl0008[,pl000c] [options]

Extracts members from Gotcha Force PZZ archives using the decoded PZZP stream.

Options:
  --region <GG4E>          source region (default GG4E)
  --borg <id[,id...]>      one or more borg PZZ archives to extract
  --member <kind[,kind]>   mot, data, hit, model, texture, all (default mot)
  --out-root <path>        destination root (default user-data/<region>/afs_data/root)
  --manifest <path>        JSON manifest path (default research/asset-inventory/pzz-member-extraction-manifest.json)
`);
  process.exit(code);
}

function addBorgs(target, value) {
  for (const raw of value.split(",")) {
    const borg = raw.trim().toLowerCase();
    if (!borg) continue;
    if (!/^pl[0-9a-f]{4}$/i.test(borg)) fail(`invalid borg id ${raw}`);
    if (!target.includes(borg)) target.push(borg);
  }
}

function addMembers(target, value) {
  if (target.size === 1 && target.has("mot")) target.clear();
  for (const raw of value.split(",")) {
    const member = raw.trim().toLowerCase();
    if (!member) continue;
    if (!["mot", "data", "hit", "model", "texture", "all"].includes(member)) fail(`invalid member kind ${raw}`);
    target.add(member);
  }
}

function requiredValue(args, index, flag) {
  const value = args[index];
  if (!value || value.startsWith("--")) fail(`${flag} requires a value`);
  return value;
}

function fail(message) {
  console.error(`extract-pzz-members: ${message}`);
  process.exit(1);
}

async function readPzzArchive(archivePath, stem) {
  const buffer = await readFile(archivePath);
  let archive;
  try {
    archive = unpackPzz(buffer);
  } catch (error) {
    fail(`invalid PZZ archive ${rel(archivePath)}: ${error.message}`);
  }

  const members = archive.members.map((member) => {
    const payload = Buffer.from(member.payload);
    const inferredName = inferBorgMemberName(stem, member.index, payload);
    return {
      index: member.index,
      memberId: member.memberId,
      inferredName,
      tableWord: member.tableWord,
      blockCount: member.blockCount,
      dataOffset: member.dataOffset,
      flags: { compressed: member.compressed },
      compression: member.compression,
      rawBytes: member.rawPayload.byteLength,
      payload,
    };
  });

  if (!archive.validatesAgainstFileSize) fail(`PZZ block sum mismatch for ${rel(archivePath)}`);
  return { path: archivePath, members };
}

async function readBorgMap() {
  try {
    const raw = await readFile(path.join(repoRoot, borgDataPath), "utf8");
    const data = JSON.parse(raw);
    return new Map((data.borgs || []).map((borg) => [String(borg.id).toLowerCase(), borg]));
  } catch {
    return new Map();
  }
}

function buildManifestRecord(borg, member, outPath) {
  const borgMeta = borgMap.get(borg);
  return {
    sourceArchive: `user-data/${options.region}/afs_data/root/${borg}.pzz`,
    borgId: borg,
    borgName: borgMeta?.name ?? null,
    memberId: member.memberId,
    memberIndex: member.index,
    inferredName: member.inferredName,
    inferredKind: inferKind(member.inferredName),
    outputPath: outPath ? rel(outPath) : null,
    skipped: outPath === null,
    compressed: member.flags.compressed,
    tableWord: hex(member.tableWord),
    blockCount: member.blockCount,
    dataOffset: member.dataOffset,
    rawBytes: member.rawBytes,
    payloadBytes: member.payload.length,
    compression: summarizeCompression(member.compression),
    familyHints: inferFamilyHints(borgMeta, member.inferredName),
    actionHints: inferActionHints(member.inferredName),
  };
}

function inferKind(name) {
  const lower = name.toLowerCase();
  if (lower.endsWith("data.bin")) return "borg-data";
  if (lower.endsWith("hit.bin")) return "hit-collision-data";
  if (lower.endsWith("mot.bin")) return "motion-bank";
  if (lower.endsWith("_mdl.arc")) return "hsd-model";
  if (lower.endsWith(".tpl")) return "texture";
  if (lower.includes(".empty")) return "empty-slot";
  return path.extname(lower).slice(1) || "binary";
}

function inferFamilyHints(borgMeta, inferredName) {
  const haystack = `${inferredName} ${borgMeta?.name ?? ""} ${borgMeta?.tribe ?? ""} ${borgMeta?.type ?? ""}`.toLowerCase();
  return Object.entries(familyTerms)
    .filter(([, terms]) => terms.some((term) => haystack.includes(term)))
    .map(([family]) => family);
}

function inferActionHints(name) {
  const kind = inferKind(name);
  if (kind === "motion-bank") return ["animation clips", "attack timing candidates"];
  if (kind === "hit-collision-data") return ["hitboxes", "damage/action metadata candidates"];
  if (kind === "hsd-model") return ["attachment/model visuals"];
  if (kind === "texture") return ["texture visuals"];
  if (kind === "borg-data") return ["actor stats/raw data"];
  return [];
}

function summarizeCompression(meta) {
  if (!meta) return null;
  return {
    sourceBytes: meta.sourceBytes,
    producedBytes: meta.producedBytes,
    consumedBytes: meta.consumedBytes,
    trailingBytes: meta.trailingBytes,
    terminated: meta.terminated,
    terminatorOffset: meta.terminatorOffset,
    tokenCount: meta.tokenCount,
    literalPairs: meta.literalPairs,
    backRefs: meta.backRefs,
    longBackRefs: meta.longBackRefs,
    firstControlWord: meta.firstControlWord,
  };
}

function hex(value) {
  return `0x${Number(value).toString(16).padStart(8, "0")}`;
}

function inferBorgMemberName(stem, index, payload) {
  if (index === 0) return `${stem}data.bin`;
  if (index === 1) return `${stem}.slot001.empty`;
  if (index === 2) return `${stem}hit.bin`;
  if (index === 3) return `${stem}mot.bin`;
  if (index === 4) return `${stem}_mdl.arc`;
  if (index === 5) return `${stem}b_mdl.arc`;
  if (index === 6) return `${stem}g_mdl.arc`;
  if (index === 7) return `${stem}s_mdl.arc`;
  if (index === 8) return `${stem}c_mdl.arc`;
  if (index === 9) return `${stem}k_mdl.arc`;
  if (payload.length > 0 && payload.readUInt32BE(0) === 0x0020af30) {
    return `${stem}.slot${String(index).padStart(3, "0")}.tpl`;
  }
  return `${stem}.slot${String(index).padStart(3, "0")}.bin`;
}

function memberMatches(member, selectedKinds) {
  if (selectedKinds.has("all")) return true;
  const name = member.inferredName.toLowerCase();
  return (
    (selectedKinds.has("mot") && name.endsWith("mot.bin")) ||
    (selectedKinds.has("data") && name.endsWith("data.bin")) ||
    (selectedKinds.has("hit") && name.endsWith("hit.bin")) ||
    (selectedKinds.has("model") && name.endsWith("_mdl.arc")) ||
    (selectedKinds.has("texture") && name.endsWith(".tpl"))
  );
}

function rel(absPath) {
  return path.relative(repoRoot, absPath).replaceAll(path.sep, "/");
}
