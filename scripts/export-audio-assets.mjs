#!/usr/bin/env node
import { createHash } from "node:crypto";
import { createReadStream, createWriteStream } from "node:fs";
import { open, mkdtemp, mkdir, readdir, rm, stat, writeFile } from "node:fs/promises";
import { tmpdir } from "node:os";
import path from "node:path";
import { pipeline } from "node:stream/promises";
import { fileURLToPath } from "node:url";
import { spawn } from "node:child_process";

const ROOT = path.resolve(path.dirname(fileURLToPath(import.meta.url)), "..");
const DEFAULT_SOURCE = path.join(ROOT, "user-data", "GG4E", "disc", "root", "poq_adx_usa.afs");
const DEFAULT_OUT = path.join(ROOT, "apps", "game", "public", "audio");
const AFS_MAGIC = "AFS\0";
const EXPECTED_MEMBER_COUNT = 2115;
const FIRST_VOICE_INDEX = 38;
const LAST_ADX_INDEX = 2112;
const SKIPPED_MEDIA_INDICES = new Set([2113, 2114]);
const BGM_KEYS = [
  "bgm00",
  "bgm01",
  "bgm01x",
  "bgm02",
  "bgm03",
  "bgm04",
  "bgm05",
  "bgm06",
  "bgm07",
  "bgm08",
  "bgm09",
  "bgm10",
  "bgm11",
  "bgm12",
  "bgm13",
  "bgm14",
  "bgm15",
  "bgm16",
  "bgm16x",
  "bgm17",
  "bgm18",
  "bgm19",
  "bgm20",
  "bgm21",
  "bgm22",
  "bgm23",
  "bgm24",
  "bgm25",
  "bgm26",
  "bgm27",
  "bgm28",
  "bgm29",
  "bgm30",
];

main().catch((error) => {
  console.error(error instanceof Error ? error.message : error);
  process.exitCode = 1;
});

async function main() {
  const options = parseArgs(process.argv.slice(2));
  const members = await parseAfsTable(options.source);
  const cues = buildCuePlan(members, options);

  console.log(`AFS: ${path.relative(ROOT, options.source)}`);
  console.log(`members: ${members.length} (${cues.length} ADX cues planned, ${SKIPPED_MEDIA_INDICES.size} non-ADX skipped)`);
  console.log(`output: ${path.relative(ROOT, options.outDir)}`);

  if (!options.export) {
    console.log("dry-run: pass --export to convert audio and rewrite manifest.json");
    printCueSummary(cues);
    return;
  }

  await ensureFfmpeg();
  await mkdir(options.outDir, { recursive: true });
  const tempDir = await mkdtemp(path.join(tmpdir(), "gf-audio-"));

  try {
    for (const cue of cues) {
      await exportCue(options.source, tempDir, cue, options.force);
    }
  } finally {
    await rm(tempDir, { recursive: true, force: true });
  }

  const manifest = await buildManifestFromFiles(options.outDir);
  const manifestPath = path.join(options.outDir, "manifest.json");
  await writeFile(manifestPath, `${JSON.stringify(manifest, null, 2)}\n`);
  console.log(`wrote ${path.relative(ROOT, manifestPath)} (${manifest.files.length} files)`);
}

function parseArgs(args) {
  const options = {
    export: false,
    force: false,
    includeVoices: "existing",
    source: DEFAULT_SOURCE,
    outDir: DEFAULT_OUT,
  };

  for (let index = 0; index < args.length; index += 1) {
    const arg = args[index];
    switch (arg) {
      case "--export":
        options.export = true;
        break;
      case "--force":
        options.force = true;
        break;
      case "--all-voices":
        options.includeVoices = "all";
        break;
      case "--no-voices":
        options.includeVoices = "none";
        break;
      case "--existing-voices":
        options.includeVoices = "existing";
        break;
      case "--source":
        options.source = path.resolve(requiredValue(args, ++index, arg));
        break;
      case "--out":
        options.outDir = path.resolve(requiredValue(args, ++index, arg));
        break;
      case "--help":
        printHelp();
        process.exit(0);
      default:
        throw new Error(`Unknown argument: ${arg}`);
    }
  }

  return options;
}

function requiredValue(args, index, flag) {
  const value = args[index];
  if (!value || value.startsWith("--")) {
    throw new Error(`${flag} requires a value`);
  }
  return value;
}

function printHelp() {
  console.log(`usage: node scripts/export-audio-assets.mjs [--export] [options]

Options:
  --export           Convert ADX cues and rewrite apps/game/public/audio/manifest.json
  --force            Reconvert even when the target OGG already exists
  --all-voices       Export every ADX voice member (AFS 38..2112) as voice0000..voice2074
  --existing-voices  Export only voice files already present in public/audio/voice (default)
  --no-voices        Export BGM and SFX only
  --source <path>    AFS source path (default: user-data/GG4E/disc/root/poq_adx_usa.afs)
  --out <path>       Public audio output directory (default: apps/game/public/audio)
`);
}

async function parseAfsTable(sourcePath) {
  const sourceStats = await stat(sourcePath);
  const file = await open(sourcePath, "r");
  let header;
  try {
    header = Buffer.alloc(8);
    await readExactly(file, header, 0);
    const count = header.readUInt32LE(4);
    const tableBytes = 8 + count * 8;
    header = Buffer.alloc(tableBytes);
    await readExactly(file, header, 0);
  } finally {
    await file.close();
  }

  const magic = header.toString("ascii", 0, 4);
  if (magic !== AFS_MAGIC) {
    throw new Error(`Not an AFS archive: ${sourcePath}`);
  }

  const count = header.readUInt32LE(4);
  if (count !== EXPECTED_MEMBER_COUNT) {
    throw new Error(`Unexpected AFS member count ${count}; expected ${EXPECTED_MEMBER_COUNT}`);
  }

  const tableBytes = 8 + count * 8;
  if (header.length < tableBytes) {
    throw new Error("AFS table is truncated");
  }

  const members = [];
  for (let index = 0; index < count; index += 1) {
    const tableOffset = 8 + index * 8;
    members.push({
      index,
      offset: header.readUInt32LE(tableOffset),
      size: header.readUInt32LE(tableOffset + 4),
    });
  }

  for (const member of members) {
    if (member.offset + member.size > sourceStats.size) {
      throw new Error(`AFS member ${member.index} exceeds archive bounds`);
    }
  }
  return members;
}

async function readExactly(file, buffer, position) {
  let offset = 0;
  while (offset < buffer.length) {
    const result = await file.read({
      buffer,
      offset,
      length: buffer.length - offset,
      position: position + offset,
    });
    if (result.bytesRead === 0) {
      throw new Error("AFS table is truncated");
    }
    offset += result.bytesRead;
  }
}

function buildCuePlan(members, options) {
  const cues = [];
  for (const member of members) {
    if (SKIPPED_MEDIA_INDICES.has(member.index) || member.index > LAST_ADX_INDEX) {
      continue;
    }

    const named = nameForMember(member.index, options);
    if (!named) {
      continue;
    }

    cues.push({
      ...member,
      ...named,
      outPath: path.join(options.outDir, named.type, `${named.key}.ogg`),
    });
  }
  return cues;
}

function nameForMember(index, options) {
  if (index < BGM_KEYS.length) {
    const key = BGM_KEYS[index];
    if (!key) {
      throw new Error(`Missing BGM key for AFS member ${index}`);
    }
    return { key, type: "bgm" };
  }
  if (index >= 33 && index <= 37) {
    return { key: `se00_${String(index - 33).padStart(2, "0")}`, type: "sfx" };
  }
  if (index >= FIRST_VOICE_INDEX && index <= LAST_ADX_INDEX) {
    if (options.includeVoices === "none") {
      return undefined;
    }
    const voiceIndex = index - FIRST_VOICE_INDEX;
    const sampledKey = sampledVoiceKey(voiceIndex);
    if (options.includeVoices === "existing" && !sampledKey) {
      return undefined;
    }
    return { key: sampledKey ?? `voice${String(voiceIndex).padStart(4, "0")}`, type: "voice" };
  }
  return undefined;
}

function sampledVoiceKey(voiceIndex) {
  const perCharacterStride = 90;
  const character = Math.floor(voiceIndex / perCharacterStride);
  const clip = voiceIndex % perCharacterStride;
  if (character > 0x16 || clip > 1) {
    return undefined;
  }
  return `pl${character.toString(16).padStart(2, "0")}_00_${String(clip).padStart(2, "0")}`;
}

function printCueSummary(cues) {
  const counts = cues.reduce(
    (summary, cue) => {
      summary[cue.type] += 1;
      return summary;
    },
    { bgm: 0, sfx: 0, voice: 0 },
  );
  console.log(`planned: ${counts.bgm} BGM, ${counts.sfx} SFX, ${counts.voice} voice`);
}

async function ensureFfmpeg() {
  await run("ffmpeg", ["-hide_banner", "-version"]);
  await run("ffprobe", ["-hide_banner", "-version"]);
}

async function exportCue(sourcePath, tempDir, cue, force) {
  await mkdir(path.dirname(cue.outPath), { recursive: true });
  if (!force && (await exists(cue.outPath))) {
    return;
  }

  const adxPath = path.join(tempDir, `${cue.key}.adx`);
  await pipeline(
    createReadStream(sourcePath, { start: cue.offset, end: cue.offset + cue.size - 1 }),
    createWriteStream(adxPath),
  );
  await run("ffmpeg", ["-hide_banner", "-loglevel", "error", "-y", "-i", adxPath, "-c:a", "libvorbis", "-q:a", "5", cue.outPath]);
}

async function buildManifestFromFiles(outDir) {
  const entries = [];
  for (const type of ["bgm", "sfx", "voice"]) {
    const dir = path.join(outDir, type);
    if (!(await exists(dir))) {
      continue;
    }

    const files = (await readdir(dir)).filter((file) => file.toLowerCase().endsWith(".ogg")).sort(naturalCompare);
    for (const file of files) {
      const fullPath = path.join(dir, file);
      const key = path.basename(file, ".ogg");
      const durationSec = await probeDuration(fullPath);
      entries.push({
        key,
        type,
        path: `audio/${type}/${file}`,
        durationSec,
        loop: type === "bgm" ? durationSec >= 5 : false,
        bytes: (await stat(fullPath)).size,
        sha1: await sha1File(fullPath),
      });
    }
  }

  const totalBytes = entries.reduce((sum, entry) => sum + entry.bytes, 0);
  const counts = entries.reduce(
    (summary, entry) => {
      summary[entry.type] += 1;
      return summary;
    },
    { bgm: 0, sfx: 0, voice: 0 },
  );

  return {
    generated: new Date().toISOString().slice(0, 10),
    source: "Gotcha Force (GG4E) poq_adx_usa.afs - CRI ADX decoded with ffmpeg",
    format: "OGG Vorbis",
    counts,
    totalBytes,
    totalMB: Number((totalBytes / 1024 / 1024).toFixed(2)),
    notes: "BGM/SFX names follow poq_adx_usa.afs index mapping. Voice cues are generic/sample keys until a traced in-game voice table is available. AFS 2113..2114 are MPEG/Sofdec-like members and are excluded.",
    files: entries.map(({ bytes, sha1, ...entry }) => entry),
    hashes: Object.fromEntries(entries.map((entry) => [entry.key, { bytes: entry.bytes, sha1: entry.sha1 }])),
  };
}

async function probeDuration(filePath) {
  const output = await run("ffprobe", ["-v", "error", "-show_entries", "format=duration", "-of", "default=noprint_wrappers=1:nokey=1", filePath], {
    capture: true,
  });
  const duration = Number.parseFloat(output.trim());
  return Number.isFinite(duration) ? Number(duration.toFixed(3)) : 0;
}

async function sha1File(filePath) {
  const hash = createHash("sha1");
  for await (const chunk of createReadStream(filePath)) {
    hash.update(chunk);
  }
  return hash.digest("hex");
}

function run(command, args, options = {}) {
  return new Promise((resolve, reject) => {
    const child = spawn(command, args, { stdio: options.capture ? ["ignore", "pipe", "pipe"] : "ignore" });
    let stdout = "";
    let stderr = "";

    if (child.stdout) {
      child.stdout.setEncoding("utf8");
      child.stdout.on("data", (chunk) => {
        stdout += chunk;
      });
    }
    if (child.stderr) {
      child.stderr.setEncoding("utf8");
      child.stderr.on("data", (chunk) => {
        stderr += chunk;
      });
    }

    child.on("error", reject);
    child.on("exit", (code) => {
      if (code === 0) {
        resolve(stdout);
        return;
      }
      reject(new Error(`${command} ${args.join(" ")} failed with exit ${code}${stderr ? `: ${stderr}` : ""}`));
    });
  });
}

async function exists(filePath) {
  try {
    await stat(filePath);
    return true;
  } catch (error) {
    if (error && error.code === "ENOENT") {
      return false;
    }
    throw error;
  }
}

function naturalCompare(left, right) {
  return left.localeCompare(right, undefined, { numeric: true, sensitivity: "base" });
}
