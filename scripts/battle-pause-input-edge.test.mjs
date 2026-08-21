import assert from "node:assert/strict";
import fs from "node:fs";
import path from "node:path";
import test from "node:test";
import ts from "typescript";
import { fileURLToPath, pathToFileURL } from "node:url";

const root = path.resolve(path.dirname(fileURLToPath(import.meta.url)), "..");
const sourcePath = path.join(root, "apps", "game", "src", "inputEdge.ts");
const source = fs.readFileSync(sourcePath, "utf8");
const output = ts.transpileModule(source, {
  compilerOptions: {
    module: ts.ModuleKind.ES2022,
    target: ts.ScriptTarget.ES2022,
  },
  fileName: sourcePath,
  reportDiagnostics: true,
});
assert.deepEqual(output.diagnostics, [], "input-edge helper must transpile without diagnostics");

const ownedRoot = path.join(root, ".tmp", "battle-pause-input-edge-test");
fs.mkdirSync(ownedRoot, { recursive: true });
const runDir = fs.mkdtempSync(path.join(ownedRoot, "run-"));
let createInputEdgeLatch;
try {
  const modulePath = path.join(runDir, "inputEdge.mjs");
  fs.writeFileSync(modulePath, output.outputText);
  ({ createInputEdgeLatch } = await import(pathToFileURL(modulePath).href));
} finally {
  fs.rmSync(runDir, { recursive: true, force: true });
}

test("a press opens once and must be released before it can open again", () => {
  const edge = createInputEdgeLatch();
  assert.equal(edge.poll(false), false);
  assert.equal(edge.poll(true), true);
  assert.equal(edge.poll(true), false);
  assert.equal(edge.poll(false), false);
  assert.equal(edge.poll(true), true);
});

test("a held briefing confirmation can be consumed by the new battle", () => {
  const edge = createInputEdgeLatch();
  edge.consume(true);
  assert.equal(edge.poll(true), false, "held Enter must not immediately pause the battle");
  assert.equal(edge.poll(false), false);
  assert.equal(edge.poll(true), true, "a fresh Enter press must still pause normally");
});
