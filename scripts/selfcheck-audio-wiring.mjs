#!/usr/bin/env node
/**
 * selfcheck-audio-wiring — STATIC checks for the BGM/SFX wiring in apps/game/src/main.ts.
 *
 * Like selfcheck-menu-flow.mjs and selfcheck-hud.mjs, this is honestly NOT a runtime/audible
 * test: it never boots a DOM, never plays a sound, and never listens to output. It parses
 * SOURCE TEXT (main.ts, the base manifest, and the combat-SE manifest) with plain string/regex
 * checks and asserts a few structural invariants the audio pipeline depends on:
 *
 *   (a) every cue KEY referenced by AUDIO_CUES / COMBAT_SFX in main.ts (the confirm/back/edit
 *       menu cues, the menuBgm/battleBgm keys, and every combat-event -> se-family cue mapping)
 *       resolves to an actual entry in apps/game/public/audio/manifest.json or
 *       apps/game/public/audio/se/manifest.json (the two manifests initAudio() merges at
 *       runtime). A cue string that doesn't resolve to any manifest key would silently no-op
 *       at runtime (playSfx/playBgm swallow/throw on an unknown key depending on call site) —
 *       this check catches that at build time instead.
 *
 *   (b) the authored-swing-audio suppression is CONSISTENT in both directions between the two
 *       places that need to agree: AUTHORED_SWING_SLOTS (the onSlotEnter allowlist that plays
 *       BorgRuntime.meleeSounds instead of the generic slot cue) and playBattleEventSfx's own
 *       suppression check (which must skip the SAME set of cues on the sim-edge path, or the
 *       generic TUNED cue double-plays alongside the authored one). Both lists must contain
 *       exactly the same members, restricted to the slots combat.ts's meleeSounds bridge
 *       actually covers (melee, melee_alt, charge_shot, special — see combat.ts
 *       startMeleeAttack/startShotAttack/startSpecialAttack, all three of which assign
 *       b.meleeSounds from an exact-move leaf).
 *
 *   (c) the BGM phase map is TOTAL over the flow's screen-transition functions: every showX()
 *       that represents a distinct BGM "phase" either calls queueBgm(...) itself or is
 *       docmented as intentionally inheriting the previous screen's track (the ALLOWLIST below).
 *       This does not prove the RIGHT track plays — see AUDIO-PORT-STATUS.md for the TUNED
 *       track->phase rationale — only that no phase is silently unhandled.
 *
 * What this script deliberately does NOT check: whether the exported OGG files decode/play
 * correctly in a real browser, whether the manifest's durationSec/loop metadata is accurate
 * (see AUDIO-PORT-STATUS.md's export-duration-bug history for why that mattered once), whether
 * rate-limit windows (COMBAT_SFX_MIN_GAP_MS) are tuned well perceptually, or whether the
 * win/lose stinger tracks some BGM manifest entries could plausibly be (bgm06, bgm17-21 — short,
 * non-training-loop-length clips) are in fact stingers: there is no ROM/decomp evidence pinning
 * those clips to any event, so this port intentionally leaves them unwired rather than guess.
 */
import { readFileSync } from "node:fs";
import path from "node:path";
import { fileURLToPath } from "node:url";

const repoRoot = path.resolve(path.dirname(fileURLToPath(import.meta.url)), "..");
const mainTsPath = path.join(repoRoot, "apps/game/src/main.ts");
const baseManifestPath = path.join(repoRoot, "apps/game/public/audio/manifest.json");
const seManifestPath = path.join(repoRoot, "apps/game/public/audio/se/manifest.json");

const failures = [];
const notes = [];
function fail(message) {
  failures.push(message);
}
function note(message) {
  notes.push(message);
}

const mainSrc = readFileSync(mainTsPath, "utf8");
const baseManifest = JSON.parse(readFileSync(baseManifestPath, "utf8"));
const seManifest = JSON.parse(readFileSync(seManifestPath, "utf8"));

const manifestKeys = new Set();
for (const entry of [...baseManifest.files, ...seManifest.files]) {
  manifestKeys.add(entry.key);
  if (entry.cue) manifestKeys.add(entry.cue);
  for (const cue of entry.cues ?? []) manifestKeys.add(cue);
}

// ---------------------------------------------------------------------------
// Check (a): every cue string main.ts references resolves to a manifest key.
// ---------------------------------------------------------------------------

// AUDIO_CUES = { menuBgm: "bgm00", battleBgm: "bgm01", confirm: "se00_03", ... } — pull every
// quoted string value out of the object literal by brace-scanning from its declaration.
function extractObjectLiteralBody(src, declPattern) {
  const m = declPattern.exec(src);
  if (!m) return null;
  const openIdx = src.indexOf("{", m.index);
  if (openIdx === -1) return null;
  let depth = 0;
  let i = openIdx;
  for (; i < src.length; i += 1) {
    if (src[i] === "{") depth += 1;
    else if (src[i] === "}") {
      depth -= 1;
      if (depth === 0) break;
    }
  }
  return src.slice(openIdx, i + 1);
}

function extractQuotedValues(objLiteralSrc) {
  // Matches `key: "value"` (skips comments naively by only taking string literals after a colon).
  const re = /:\s*"([^"]+)"/g;
  const values = [];
  let m;
  while ((m = re.exec(objLiteralSrc))) values.push(m[1]);
  return values;
}

const audioCuesBody = extractObjectLiteralBody(mainSrc, /const AUDIO_CUES\s*=\s*/);
if (!audioCuesBody) {
  fail("main.ts: could not find `const AUDIO_CUES = {...}` — has this been renamed/restructured?");
} else {
  const cueValues = extractQuotedValues(audioCuesBody);
  if (cueValues.length === 0) {
    fail("main.ts: AUDIO_CUES parsed but no quoted cue values were found inside it");
  }
  for (const key of cueValues) {
    if (!manifestKeys.has(key)) {
      fail(`main.ts: AUDIO_CUES references "${key}", which is not a key in manifest.json or se/manifest.json`);
    }
  }
  note(`AUDIO_CUES: ${cueValues.length} cue values checked against ${manifestKeys.size} manifest keys`);
}

const combatSfxBody = extractObjectLiteralBody(mainSrc, /const COMBAT_SFX\s*:[^=]*=\s*/);
if (!combatSfxBody) {
  fail("main.ts: could not find `const COMBAT_SFX: ... = {...}` — has this been renamed/restructured?");
} else {
  const sfxValues = extractQuotedValues(combatSfxBody);
  if (sfxValues.length === 0) {
    fail("main.ts: COMBAT_SFX parsed but no quoted cue values were found inside it");
  }
  for (const key of sfxValues) {
    if (!manifestKeys.has(key)) {
      fail(`main.ts: COMBAT_SFX references "${key}", which is not a key in manifest.json or se/manifest.json`);
    }
  }
  note(`COMBAT_SFX: ${sfxValues.length} cue values checked against ${manifestKeys.size} manifest keys`);
}

// ---------------------------------------------------------------------------
// Check (b): AUTHORED_SWING_SLOTS <-> playBattleEventSfx suppression parity.
// ---------------------------------------------------------------------------

// AUTHORED_SWING_SLOTS: ReadonlySet<string> = new Set(["melee", "melee_alt", "charge_shot", ...]);
const authoredSlotsMatch = /AUTHORED_SWING_SLOTS[^=]*=\s*new Set\(\s*\[([^\]]*)\]\s*\)/.exec(mainSrc);
if (!authoredSlotsMatch) {
  fail("main.ts: could not find `const AUTHORED_SWING_SLOTS = new Set([...])`");
} else {
  const authoredSlots = new Set(
    [...authoredSlotsMatch[1].matchAll(/"([^"]+)"/g)].map((m) => m[1]),
  );

  // playBattleEventSfx's suppression is expected to share the SAME Set rather than re-list cue
  // names (see the comment in main.ts above playBattleEventSfx): either
  // `AUTHORED_SWING_SLOTS.has(cue)` (preferred — structurally cannot drift), or, if a future
  // edit reverts to literal comparisons, an explicit `cue === "x"` list that this script can
  // still cross-check name-by-name.
  const suppressionFnMatch = /function playBattleEventSfx[\s\S]*?\n\}/.exec(mainSrc);
  if (!suppressionFnMatch) {
    fail("main.ts: could not find `function playBattleEventSfx`");
  } else {
    const fnBody = suppressionFnMatch[0];
    const usesSharedSet = /AUTHORED_SWING_SLOTS\.has\(\s*cue\s*\)/.test(fnBody);
    const suppressedCues = new Set([...fnBody.matchAll(/cue === "([^"]+)"/g)].map((m) => m[1]));

    if (usesSharedSet) {
      note("playBattleEventSfx suppression uses AUTHORED_SWING_SLOTS.has(cue) directly — structurally in sync with onSlotEnter, no per-name parity check needed");
    } else if (suppressedCues.size === 0) {
      fail(
        "playBattleEventSfx: suppression is neither `AUTHORED_SWING_SLOTS.has(cue)` nor any `cue === \"...\"` checks — has the authored-audio suppression been removed?",
      );
    } else {
      for (const slot of authoredSlots) {
        if (!suppressedCues.has(slot)) {
          fail(
            `AUTHORED_SWING_SLOTS contains "${slot}" (onSlotEnter plays authored meleeSounds for it) but playBattleEventSfx's suppression check does not skip cue "${slot}" — the sim-edge generic cue can double-fire alongside the authored one`,
          );
        }
      }
      for (const cue of suppressedCues) {
        if (!authoredSlots.has(cue)) {
          note(
            `playBattleEventSfx suppresses cue "${cue}", which is not in AUTHORED_SWING_SLOTS — harmless (suppression check without a matching onSlotEnter allowlist entry is a no-op, never a double-fire), but worth confirming intentional`,
          );
        }
      }
      note(`AUTHORED_SWING_SLOTS = {${[...authoredSlots].join(", ")}}, suppression covers {${[...suppressedCues].join(", ")}}`);
    }
  }
}

// combat.ts's meleeSounds bridge covers exactly {melee (startMeleeAttack), charge_shot
// (startShotAttack charge release), special (startSpecialAttack)} — cross-check AUTHORED_SWING_SLOTS
// against the anim slots those three sim functions actually set on b.anim/b.state, so a future
// fourth meleeSounds call site can't land without this selfcheck flagging the gap.
const combatTsPath = path.join(repoRoot, "packages/combat/src/combat.ts");
let combatSrc = "";
try {
  combatSrc = readFileSync(combatTsPath, "utf8");
} catch {
  note(`could not read ${combatTsPath} — skipping the combat.ts meleeSounds cross-check`);
}
if (combatSrc) {
  const meleeSoundsAssignments = (combatSrc.match(/b\.meleeSounds\s*=/g) ?? []).length;
  // Every current call site: startMeleeAttack, startShotAttack (charge release), startSpecialAttack.
  const EXPECTED_MELEE_SOUNDS_SITES = 3;
  if (meleeSoundsAssignments !== EXPECTED_MELEE_SOUNDS_SITES) {
    note(
      `packages/combat/src/combat.ts assigns b.meleeSounds in ${meleeSoundsAssignments} place(s) (expected ${EXPECTED_MELEE_SOUNDS_SITES}: startMeleeAttack/startShotAttack/startSpecialAttack) — if this changed, re-check AUTHORED_SWING_SLOTS/playBattleEventSfx cover every site's rendered anim slot`,
    );
  }
}

// ---------------------------------------------------------------------------
// Check (c): BGM phase map is total over the flow's showX()/enterBattle() functions.
// ---------------------------------------------------------------------------

// Screens that intentionally do NOT call queueBgm — they inherit whatever track the previous
// screen queued, because they are sub-steps of the same BGM "phase" (documented reasoning below,
// matches the flow comment block at the top of main.ts and AUDIO-PORT-STATUS.md).
const BGM_INHERITS_ALLOWLIST = {
  showDifficulty: "sub-step of the pre-battle menu phase; inherits menuBgm from showMenu/showTitleIntro",
  showPlayers: "sub-step of the pre-battle menu phase; inherits menuBgm",
  showLoadBoxData: "sub-step of the pre-battle menu phase; inherits menuBgm",
  showSelectForce: "sub-step of the pre-battle menu phase; inherits menuBgm",
  showForceBuilder: "sub-step of the pre-battle menu phase; inherits menuBgm",
  showResults: "post-battle screen; deliberately keeps battleBgm playing under the results readout (no ROM-traced results stinger track — see AUDIO-PORT-STATUS.md)",
  showGets: "post-battle screen; deliberately keeps battleBgm playing under the GET list (same rationale as showResults)",
  showLoadingMessage: "boot/error utility screen, not a flow phase",
};

function extractFunctionBodies(src, namePattern) {
  const results = [];
  const re = new RegExp(`function\\s+(${namePattern})\\s*\\(`, "g");
  let match;
  while ((match = re.exec(src))) {
    const name = match[1];
    const openBraceIdx = src.indexOf("{", match.index);
    if (openBraceIdx === -1) continue;
    let depth = 0;
    let i = openBraceIdx;
    for (; i < src.length; i += 1) {
      if (src[i] === "{") depth += 1;
      else if (src[i] === "}") {
        depth -= 1;
        if (depth === 0) break;
      }
    }
    results.push({ name, body: src.slice(openBraceIdx, i + 1) });
  }
  return results;
}

const showFunctions = extractFunctionBodies(mainSrc, "show\\w+");
const enterBattleFn = extractFunctionBodies(mainSrc, "enterBattle");
const allPhaseFunctions = [...showFunctions, ...enterBattleFn];

if (allPhaseFunctions.length === 0) {
  fail("main.ts: no showX()/enterBattle() functions found — flow shape has changed; update this selfcheck");
}

for (const { name, body } of allPhaseFunctions) {
  const queuesBgm = /queueBgm\s*\(/.test(body);
  if (!queuesBgm && !BGM_INHERITS_ALLOWLIST[name]) {
    fail(
      `main.ts: ${name}() does not call queueBgm(...) and is not on BGM_INHERITS_ALLOWLIST — either wire a BGM transition or document why it intentionally inherits the previous track`,
    );
  } else if (!queuesBgm) {
    note(`${name}(): inherits previous BGM — ${BGM_INHERITS_ALLOWLIST[name]}`);
  } else {
    note(`${name}(): queues its own BGM`);
  }
}

// ---------------------------------------------------------------------------
// Report
// ---------------------------------------------------------------------------

console.log(
  `selfcheck-audio-wiring: checked ${manifestKeys.size} manifest keys, ${allPhaseFunctions.length} flow phase functions`,
);
for (const n of notes) console.log(`  note: ${n}`);

if (failures.length > 0) {
  console.error(`\nselfcheck-audio-wiring FAILED (${failures.length}):`);
  for (const f of failures) console.error(`  - ${f}`);
  process.exit(1);
}

console.log("\nselfcheck-audio-wiring PASS (static wiring check only — see file header for what this does not prove)");
