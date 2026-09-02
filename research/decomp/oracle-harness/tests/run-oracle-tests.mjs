#!/usr/bin/env node
import fs from "node:fs";
import path from "node:path";
import { spawnSync } from "node:child_process";
import { fileURLToPath } from "node:url";

const here = path.dirname(fileURLToPath(import.meta.url));
const root = path.resolve(here, "..", "..", "..", "..");
const scratchParent = path.join(root, ".tmp", "oracle-tests");
fs.mkdirSync(scratchParent, { recursive: true });
const scratch = fs.mkdtempSync(path.join(scratchParent, "run-"));

try {
  const result = spawnSync(process.execPath, [
    "--test",
    "--test-concurrency=1",
    path.join(here, "codec.test.mjs"),
    path.join(here, "zero-case-guard.test.mjs"),
    path.join(here, "result-integrity.test.mjs"),
    path.join(here, "arena-rom-binding.test.mjs"),
    path.join(here, "replay-gate.test.mjs"),
    path.join(here, "spine-harness.test.mjs"),
    path.join(here, "transcript-harness.test.mjs"),
    path.join(here, "gx-callstream-harness.test.mjs"),
    path.join(here, "dispatch-harness.test.mjs"),
  ], {
    cwd: root,
    env: {
      ...process.env,
      ORACLE_TEST_TMP_ROOT: scratch,
      TEMP: scratch,
      TMP: scratch,
      TMPDIR: scratch,
    },
    encoding: "utf8",
    stdio: "inherit",
  });
  process.exitCode = result.status ?? 1;
} finally {
  fs.rmSync(scratch, { recursive: true, force: true });
}
