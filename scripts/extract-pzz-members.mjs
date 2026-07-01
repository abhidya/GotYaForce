#!/usr/bin/env node
import { mkdir, writeFile, readFile } from "node:fs/promises";
import path from "node:path";

const BLOCK_SIZE = 0x800;
const COMPRESSED_FLAG = 0x40000000;
const BLOCK_COUNT_MASK = 0x3fffffff;
const DEFAULT_REGION = "GG4E";

class GrowBuffer {
  constructor(initialSize) {
    this.buffer = Buffer.allocUnsafe(Math.max(0x1000, initialSize));
    this.length = 0;
  }

  ensure(extraBytes) {
    const needed = this.length + extraBytes;
    if (needed <= this.buffer.length) return;
    let nextLength = this.buffer.length;
    while (nextLength < needed) nextLength *= 2;
    const next = Buffer.allocUnsafe(nextLength);
    this.buffer.copy(next, 0, 0, this.length);
    this.buffer = next;
  }

  pushByte(value) {
    this.ensure(1);
    this.buffer[this.length] = value;
    this.length += 1;
  }

  copyFromSelf(distance, count) {
    const start = this.length - distance;
    if (start < 0) fail(`invalid PZZP back-reference distance ${distance}`);
    this.ensure(count);
    for (let i = 0; i < count; i += 1) {
      this.buffer[this.length] = this.buffer[start + i];
      this.length += 1;
    }
  }

  toBuffer() {
    return this.buffer.subarray(0, this.length);
  }
}

const options = parseArgs(process.argv.slice(2));
if (options.help) usage(0);

const repoRoot = path.resolve(".");
const assetRoot = path.join(repoRoot, "user-data", options.region, "afs_data", "root");
const outRoot = path.resolve(repoRoot, options.outRoot);

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
for (const { borg, member } of selected) {
  const outPath = path.join(outRoot, member.inferredName);
  if (member.payload.length === 0) {
    console.log(`skip empty ${borg}#${member.memberId} ${member.inferredName}`);
    continue;
  }
  await writeFile(outPath, member.payload);
  console.log(
    `extract ${borg}#${member.memberId} ${member.inferredName} ` +
      `${member.flags.compressed ? "pzzp" : "raw"} ${member.payload.length} bytes -> ${rel(outPath)}`,
  );
}

function parseArgs(args) {
  const parsed = {
    region: DEFAULT_REGION,
    outRoot: path.join("user-data", DEFAULT_REGION, "afs_data", "root"),
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
  if (buffer.length < BLOCK_SIZE) fail(`archive too small: ${rel(archivePath)}`);
  const count = buffer.readUInt32BE(0);
  if (!Number.isInteger(count) || count <= 0 || count > 512 || 4 + count * 4 > BLOCK_SIZE) {
    fail(`invalid PZZ member table in ${rel(archivePath)}`);
  }

  const members = [];
  let cursor = BLOCK_SIZE;
  let sumBlocks = 0;
  for (let index = 0; index < count; index += 1) {
    const tableWord = buffer.readUInt32BE(4 + index * 4);
    const compressed = (tableWord & COMPRESSED_FLAG) !== 0;
    const blockCount = tableWord & BLOCK_COUNT_MASK;
    const paddedBytes = blockCount * BLOCK_SIZE;
    const raw = blockCount === 0 ? Buffer.alloc(0) : buffer.subarray(cursor, cursor + paddedBytes);
    const payload = compressed && raw.length > 0 ? decompressPzzpStream(raw) : raw;
    const inferredName = inferBorgMemberName(stem, index, payload);
    members.push({
      index,
      memberId: String(index).padStart(3, "0"),
      inferredName,
      tableWord,
      blockCount,
      dataOffset: cursor,
      flags: { compressed },
      payload,
    });
    cursor += paddedBytes;
    sumBlocks += blockCount;
  }

  const expectedSize = (sumBlocks + 1) * BLOCK_SIZE;
  if (expectedSize !== buffer.length) fail(`PZZ block sum mismatch for ${rel(archivePath)}`);
  return { path: archivePath, members };
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

function decompressPzzpStream(buffer) {
  const out = new GrowBuffer(Math.max(buffer.length * 3, 0x1000));
  const evenLength = buffer.length & ~1;
  let cursor = 0;
  let control = 0;
  let bit = -1;

  while (cursor + 2 <= evenLength) {
    if (bit < 0) {
      control = buffer.readUInt16BE(cursor);
      cursor += 2;
      bit = 15;
      continue;
    }

    const compressedToken = (control & (1 << bit)) !== 0;
    bit -= 1;
    if (!compressedToken) {
      out.pushByte(buffer[cursor]);
      out.pushByte(buffer[cursor + 1]);
      cursor += 2;
      continue;
    }

    const token = buffer.readUInt16BE(cursor);
    const distance = (token & 0x7ff) * 2;
    cursor += 2;
    if (distance === 0) return out.toBuffer();

    let byteCount = (token >> 11) * 2;
    if (byteCount === 0) {
      if (cursor + 2 > evenLength) fail("PZZP long back-reference is missing its extension word");
      byteCount = buffer.readUInt16BE(cursor) * 2;
      cursor += 2;
    }
    out.copyFromSelf(distance, byteCount);
  }

  fail("PZZP stream ended before terminator");
}

function rel(absPath) {
  return path.relative(repoRoot, absPath).replaceAll(path.sep, "/");
}
