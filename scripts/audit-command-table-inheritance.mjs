#!/usr/bin/env node
import fs from "node:fs";
import path from "node:path";
import { fileURLToPath } from "node:url";

const repoRoot = path.resolve(path.dirname(fileURLToPath(import.meta.url)), "..");
const indexPath = path.join(repoRoot, "research/decomp/ghidra-export/_index.tsv");
const decompRoot = path.join(repoRoot, "research/decomp/ghidra-export");
const commandTablesPath = path.join(repoRoot, "packages/combat/src/data/commandMoveTables.json");
const borgsPath = path.join(repoRoot, "packages/assets/data/borgs.json");

const commandTables = JSON.parse(fs.readFileSync(commandTablesPath, "utf8"));
const borgsData = JSON.parse(fs.readFileSync(borgsPath, "utf8"));
const directSourceConstructors = new Set(
  Object.values(commandTables.tables).map((table) => table.constructorAddress.toLowerCase()),
);

const indexRows = fs
  .readFileSync(indexPath, "utf8")
  .trim()
  .split(/\r?\n/)
  .slice(1)
  .map((line) => {
    const [address, name, chunkFile] = line.split("\t");
    return {
      address: `0x${address.toLowerCase()}`,
      rawAddress: address.toLowerCase(),
      name,
      chunkFile,
    };
  });

const functionsByAddress = new Map(indexRows.map((row) => [row.address, row]));
const functionsByName = new Map(indexRows.map((row) => [row.name, row]));
const chunkCache = new Map();

function chunkText(chunkFile) {
  if (!chunkCache.has(chunkFile)) {
    chunkCache.set(chunkFile, fs.readFileSync(path.join(decompRoot, chunkFile), "utf8"));
  }
  return chunkCache.get(chunkFile);
}

function functionBody(address) {
  const row = functionsByAddress.get(address.toLowerCase());
  if (!row) return "";
  const text = chunkText(row.chunkFile);
  const marker = `// ==== ${row.rawAddress}`;
  const start = text.indexOf(marker);
  if (start < 0) return "";
  const next = text.indexOf("// ====", start + marker.length);
  return next < 0 ? text.slice(start) : text.slice(start, next);
}

function functionCalls(body) {
  const names = new Set();
  for (const match of body.matchAll(/\b((?:zz|FUN)_[A-Za-z0-9_]+)\s*\(/g)) {
    if (functionsByName.has(match[1])) names.add(match[1]);
  }
  return [...names];
}

function lineFor(chunkFile, needle) {
  const lines = chunkText(chunkFile).split(/\r?\n/);
  const index = lines.findIndex((line) => line.includes(needle));
  return index < 0 ? null : index + 1;
}

function missingCommandTableGroups() {
  const groups = new Map();
  for (const borg of borgsData.borgs) {
    const id = String(borg.id).toLowerCase();
    const assignment = commandTables.borgs[id];
    if (assignment?.exactCommandTable) continue;
    const key = assignment.constructorAddress.toLowerCase();
    if (!groups.has(key)) groups.set(key, []);
    groups.get(key).push(`${id} ${borg.name}`);
  }
  return [...groups].sort((left, right) => right[1].length - left[1].length);
}

for (const [address, borgNames] of missingCommandTableGroups()) {
  const row = functionsByAddress.get(address);
  const body = functionBody(address);
  const calls = functionCalls(body)
    .map((name) => functionsByName.get(name))
    .map((call) => ({
      ...call,
      directSource: directSourceConstructors.has(call.address),
      line: lineFor(row.chunkFile, `${call.name}(`),
    }));
  const directWrite = /\+\s*0x4ec\)\s*=|\+\s*0x4b0\)\s*=/.test(body);

  console.log(`${address} ${borgNames.length} ${row?.name ?? "?"} ${row?.chunkFile ?? "?"} directWrite=${directWrite}`);
  console.log(`  borgs: ${borgNames.slice(0, 8).join(" | ")}`);
  console.log(
    `  calls: ${
      calls
        .slice(0, 14)
        .map(
          (call) =>
            `${call.address} ${call.name}${call.directSource ? " DIRECT_SOURCE" : ""}${
              call.line ? ` ${row.chunkFile}:${call.line}` : ""
            }`,
        )
        .join(" ; ") || "(none)"
    }`,
  );
}
