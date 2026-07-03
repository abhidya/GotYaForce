import fs from "node:fs";
import path from "node:path";
import { fileURLToPath } from "node:url";

const repoRoot = path.resolve(path.dirname(fileURLToPath(import.meta.url)), "..");
const options = { maxHits: 12, showStack: false };
const args = [];
for (const arg of process.argv.slice(2)) {
  if (arg === "--stack") {
    options.showStack = true;
  } else if (arg.startsWith("--hits=")) {
    const parsed = Number.parseInt(arg.slice("--hits=".length), 10);
    if (Number.isInteger(parsed) && parsed > 0) options.maxHits = parsed;
  } else {
    args.push(arg);
  }
}

if (args.length === 0) {
  console.error("Usage: node scripts/summarize-asset-trace.mjs <trace.json> [trace2.json ...]");
  process.exitCode = 1;
} else {
  const audioIndex = loadAudioIndex();
  for (const pattern of args) {
    for (const tracePath of expandArg(pattern)) {
      summarizeTrace(tracePath, audioIndex, options);
    }
  }
}

function loadAudioIndex() {
  const indexPath = path.join(repoRoot, "research", "game-design", "poq-adx-member-index.json");
  if (!fs.existsSync(indexPath)) return new Map();
  const data = JSON.parse(fs.readFileSync(indexPath, "utf8"));
  return new Map((data.members ?? []).map((member) => [member.index, member]));
}

function expandArg(arg) {
  if (!arg.includes("*")) return [arg];
  const normalized = path.resolve(arg);
  const dir = path.dirname(normalized);
  const filePattern = path.basename(normalized)
    .replace(/[.+?^${}()|[\]\\]/g, "\\$&")
    .replaceAll("\\*", ".*");
  const regex = new RegExp(`^${filePattern}$`, "i");
  if (!fs.existsSync(dir)) return [];
  return fs.readdirSync(dir)
    .filter((name) => regex.test(name))
    .map((name) => path.join(dir, name))
    .sort();
}

function summarizeTrace(tracePath, audioIndex, options) {
  const trace = JSON.parse(fs.readFileSync(tracePath, "utf8"));
  const hits = trace.hits ?? [];
  console.log(`# ${path.relative(process.cwd(), tracePath)}`);
  console.log(`hits=${hits.length} errors=${(trace.errors ?? []).length}`);
  if (trace.errors?.length) {
    for (const error of trace.errors.slice(0, 5)) {
      console.log(`error ${error.where ?? "unknown"}: ${error.message ?? error.stop ?? JSON.stringify(error)}`);
    }
  }

  const counts = new Map();
  for (const hit of hits) {
    const id = hit.breakpoint?.ids?.[0] ?? hit.watchpoint?.id ?? "unknown";
    const key = `${id} <= ${hit.lr ?? "no-lr"}`;
    counts.set(key, (counts.get(key) ?? 0) + 1);
  }
  for (const [key, count] of [...counts.entries()].sort((a, b) => b[1] - a[1]).slice(0, 20)) {
    console.log(`${count.toString().padStart(4, " ")} ${key}`);
  }

  console.log("");
  for (const hit of hits.slice(0, options.maxHits)) {
    printHit(hit, audioIndex, options);
  }
}

function printHit(hit, audioIndex, options) {
  const id = hit.breakpoint?.ids?.join(",") ?? hit.watchpoint?.id ?? "unknown";
  const symbol = hit.breakpoint?.symbols?.join(",") ?? "";
  console.log(`hit ${hit.index} pc=${hit.pc} lr=${hit.lr} id=${id}${symbol ? ` symbol=${symbol}` : ""}`);

  const regs = ["r3", "r4", "r5", "r6", "r7", "r8", "r9", "r10", "r31"];
  const regParts = regs.map((name) => `${name}=${formatReg(hit.regs?.[name]?.value)}`);
  console.log(`  regs ${regParts.join(" ")}`);

  const strings = pointerStrings(hit);
  if (strings.length) console.log(`  strings ${strings.join(" | ")}`);

  const candidates = audioCandidates(hit, audioIndex);
  if (candidates.length) {
    const visible = candidates.slice(0, 12);
    const suffix = candidates.length > visible.length ? ` | +${candidates.length - visible.length} more` : "";
    console.log(`  audioCandidates ${visible.join(" | ")}${suffix}`);
  }

  const lowerId = id.toLowerCase();
  if (options.showStack || lowerId.includes("afs") || lowerId.includes("mwply")) {
    const stack = stackWords(hit);
    if (stack.length) console.log(`  stack ${stack.slice(0, 16).join(" ")}`);
  }
}

function formatReg(value) {
  if (!Number.isInteger(value)) return "null";
  return `0x${(value >>> 0).toString(16).padStart(8, "0")}(${value >>> 0})`;
}

function pointerStrings(hit) {
  const out = [];
  for (const [reg, pointer] of Object.entries(hit.pointers ?? {})) {
    const decoded = decodePrintable(pointer.bytes?.raw);
    if (decoded && /[A-Za-z0-9_./\\-]{3,}/.test(decoded)) out.push(`${reg}@${pointer.address}="${decoded}"`);
  }
  return out;
}

function audioCandidates(hit, audioIndex) {
  const out = [];
  for (const name of ["r3", "r4", "r5", "r6", "r7", "r8", "r9", "r10"]) {
    pushAudioCandidate(out, audioIndex, name, hit.regs?.[name]?.value);
  }
  for (const [index, value] of stackWordsRaw(hit).entries()) {
    pushAudioCandidate(out, audioIndex, `stack[${index}]`, value);
  }
  return out;
}

function pushAudioCandidate(out, audioIndex, source, value) {
  if (!Number.isInteger(value)) return;
  const unsigned = value >>> 0;
  if (unsigned === 0) return;
  const member = audioIndex.get(unsigned);
  if (!member) return;
  const key = member.exportedKey ? ` key=${member.exportedKey}` : "";
  const duration = Number.isFinite(member.durationSec) ? ` ${member.durationSec}s` : "";
  out.push(`${source}=member${unsigned}${key} range=${member.range ?? "?"}${duration}`);
}

function stackWords(hit) {
  return stackWordsRaw(hit).map((value, index) => `[${index}]=0x${value.toString(16).padStart(8, "0")}(${value})`);
}

function stackWordsRaw(hit) {
  const raw = hit.pointers?.r1?.bytes?.raw;
  if (!raw || raw.length < 8) return [];
  const bytes = hexToBytes(raw);
  const words = [];
  for (let i = 0; i + 3 < Math.min(bytes.length, 0x80); i += 4) {
    words.push(((bytes[i] << 24) | (bytes[i + 1] << 16) | (bytes[i + 2] << 8) | bytes[i + 3]) >>> 0);
  }
  return words;
}

function decodePrintable(raw) {
  if (!raw) return "";
  const bytes = hexToBytes(raw);
  const chars = [];
  for (const byte of bytes) {
    if (byte === 0) break;
    if (byte < 0x20 || byte > 0x7e) {
      if (chars.length < 3) return "";
      break;
    }
    chars.push(String.fromCharCode(byte));
  }
  return chars.join("");
}

function hexToBytes(raw) {
  const bytes = [];
  for (let i = 0; i + 1 < raw.length; i += 2) {
    bytes.push(Number.parseInt(raw.slice(i, i + 2), 16));
  }
  return bytes;
}
