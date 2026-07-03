#!/usr/bin/env node
// Validation for the per-borg voice-cue wiring (behavior-notes.md (az)).
//
// apps/game is a Vite app (no importable node dist) and presentation.ts pulls three.js via its
// type graph, so we can't import battleVoiceCues/voiceKeyForBorgId directly. Instead this script
// re-implements the tiny family->voice-key derivation (kept byte-identical to
// apps/game/src/sim/presentation.ts voiceKeyForBorgId) and proves the load-bearing claim: every
// roster borg's derived voice key resolves to a REAL extracted voice asset in the manifest. If
// the derivation in presentation.ts changes, update the mirror below.
//
//   tools/node/node.exe scripts/run-voice-cues-tests.mjs

import { readFileSync } from "node:fs";
import { dirname, resolve } from "node:path";
import { fileURLToPath } from "node:url";

const repoRoot = resolve(dirname(fileURLToPath(import.meta.url)), "..");
const manifest = JSON.parse(readFileSync(resolve(repoRoot, "apps/game/public/audio/manifest.json"), "utf8"));
const roster = JSON.parse(readFileSync(resolve(repoRoot, "packages/assets/data/borgs.json"), "utf8")).borgs;

let checks = 0;
let failures = 0;
const ok = (cond, label) => {
  checks++;
  if (!cond) {
    failures++;
    console.error(`FAIL: ${label}`);
  }
};

// Mirror of presentation.ts voiceKeyForBorgId (keep in sync).
function voiceKeyForBorgId(borgId, variant) {
  if (!/^pl[0-9a-fA-F]{4}$/.test(borgId)) return null;
  const family = borgId.slice(2, 4).toLowerCase();
  return `pl${family}_00_0${variant}`;
}

const voiceKeys = new Set(manifest.files.filter((f) => f.type === "voice").map((f) => f.key));

// 1) Manifest shape: 46 voice cues (23 families x 2 variants).
ok(voiceKeys.size === 46, `manifest has 46 voice cues (got ${voiceKeys.size})`);

// 2) Spot checks against known families.
ok(voiceKeyForBorgId("pl0615", 0) === "pl06_00_00", "pl0615 (G RED, family 06) variant 0 -> pl06_00_00");
ok(voiceKeyForBorgId("pl0615", 1) === "pl06_00_01", "pl0615 variant 1 -> pl06_00_01");
ok(voiceKeyForBorgId("pl070a", 0) === "pl07_00_00", "pl070a (VLAD, family 07) variant 0 -> pl07_00_00");
ok(voiceKeyForBorgId("pl0008", 1) === "pl00_00_01", "pl0008 (family 00) variant 1 -> pl00_00_01");
ok(voiceKeyForBorgId("nope", 0) === null, "a non-pl#### id yields null (no cue)");

// 3) Core claim: EVERY roster borg's derived voice keys (both variants) exist in the manifest.
let covered = 0;
const missing = [];
for (const b of roster) {
  const k0 = voiceKeyForBorgId(b.id, 0);
  const k1 = voiceKeyForBorgId(b.id, 1);
  const has0 = !!k0 && voiceKeys.has(k0);
  const has1 = !!k1 && voiceKeys.has(k1);
  if (has0 && has1) covered++;
  else missing.push(`${b.id}(${b.name}) -> ${k0}/${k1}`);
}
ok(missing.length === 0, `all ${roster.length} roster borgs resolve BOTH voice variants (missing: ${missing.slice(0, 8).join(", ")})`);
ok(covered === roster.length, `roster voice coverage ${covered}/${roster.length}`);

if (failures > 0) {
  console.error(`voiceCues.validation: ${checks - failures}/${checks} checks passed, ${failures} FAILED`);
  process.exit(1);
}
console.log(`voiceCues.validation: ${checks}/${checks} checks passed (roster voice coverage ${covered}/${roster.length})`);
process.exit(0);
