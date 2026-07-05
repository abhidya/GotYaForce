#!/usr/bin/env node
/**
 * selfcheck-hud — STATIC checks for the in-battle HUD (BattleHud.ts / presentation.ts).
 *
 * Like selfcheck-menu-flow.mjs, this is honestly NOT a runtime/visual test: it never boots a
 * DOM, never runs three.js, never renders a frame, and never compares a screenshot against a
 * reference capture. It parses SOURCE TEXT with plain string/regex checks and asserts a few
 * structural invariants that "the battle HUD stays asset-backed, not ad-hoc raw text" depends
 * on:
 *
 *   (a) BattleHud.ts renders every DYNAMIC value (ally/enemy energy numbers, HP digits, ammo/
 *       X-ammo digits, labels, button letters, DEFEATED banner, player tag, teammate labels)
 *       through the bitmap font (setBitmapText from ../bitmapText.js), not a raw `textContent =`
 *       / `innerText =` / template-literal-into-a-text-node assignment. This is a grep-level
 *       check for the ABSENCE of raw-text-assignment patterns in the file, not a full parse —
 *       it would not catch a raw text node built through some indirection this script doesn't
 *       know to look for.
 *
 *   (b) every HUD asset path the module references (ASSETS.fontAscii, ASSETS.faceMarkerRoundel,
 *       borgBannerPath()'s template) resolves to a file that actually exists on disk under
 *       apps/game/public. This proves the referenced files exist, NOT that they are decoded
 *       correctly, that the atlas cell mapping is right (see assert-ascii-glyphs.mjs for that),
 *       or that the HUD looks correct next to the reference captures.
 *
 *   (c) presentation.ts's battleHudState() return expression actually assigns every field the
 *       HudState interface (BattleHud.ts) declares as required (non-optional), by a parse-level
 *       key scan of the interface block and the returned object literal's keys (including the
 *       conditional-spread `...(x !== undefined ? { x } : {})` pattern used for optional
 *       fields). This proves the two files' shapes agree TEXTUALLY; it does not run the
 *       function, does not check the runtime TYPES of the values, and would not catch a field
 *       that TypeScript's own structural checks wouldn't already catch at build time either
 *       (that's what `pnpm typecheck` is for — this script is a faster, narrower, no-build
 *       cross-check intended to fail loudly if the two files drift out of naming sync).
 *
 * What this script deliberately does NOT check: whether the HUD is actually legible over any
 * of the 40 stages' real lighting/fog extremes (that was checked once, manually, with a
 * throwaway preview harness — see the TUNED readability-guard comment block in styles.css next
 * to .gf-hud-text), whether the lock-on reticle's color/geometry match a real capture (that's
 * arrow_mdl geometry + measured tints in battleScene.ts, outside this script's scope), or
 * whether battleHudState() ever gets called with a real Battle object without throwing.
 */
import { readFileSync } from "node:fs";
import path from "node:path";
import { fileURLToPath } from "node:url";

const repoRoot = path.resolve(path.dirname(fileURLToPath(import.meta.url)), "..");
const hudPath = path.join(repoRoot, "apps/game/src/ui/hud/BattleHud.ts");
const presentationPath = path.join(repoRoot, "apps/game/src/sim/presentation.ts");
const assetsPath = path.join(repoRoot, "apps/game/src/ui/assets.ts");
const publicDir = path.join(repoRoot, "apps/game/public");

const failures = [];
const notes = [];

function fail(message) {
  failures.push(message);
}
function note(message) {
  notes.push(message);
}

const hudSrc = readFileSync(hudPath, "utf8");
const presentationSrc = readFileSync(presentationPath, "utf8");
const assetsSrc = readFileSync(assetsPath, "utf8");

// ---------------------------------------------------------------------------
// Check (a): dynamic HUD values render through the bitmap font, not raw text.
// ---------------------------------------------------------------------------

// setBitmapText(...) calls are the sanctioned path for putting characters on screen.
const setBitmapTextCalls = [...hudSrc.matchAll(/setBitmapText\s*\(\s*(\w+)/g)].map((m) => m[1]);
if (setBitmapTextCalls.length === 0) {
  fail("BattleHud.ts: no setBitmapText(...) calls found — expected the HUD to render its dynamic values through the bitmap font");
} else {
  note(`BattleHud.ts: ${setBitmapTextCalls.length} setBitmapText() call sites (nodes: ${[...new Set(setBitmapTextCalls)].join(", ")})`);
}

// Raw-text-assignment patterns that would bypass the bitmap font for a dynamic value.
// (el(...) `text:` props are fine for STATIC non-numeric chrome the game itself draws as
// plain DOM, e.g. aria labels — the check here is scoped to the classic runtime-text-mutation
// APIs, which every dynamic HUD readout in this file avoids in favor of setBitmapText.)
const RAW_TEXT_ASSIGNMENT_RE = /\.(?:textContent|innerText|innerHTML)\s*=/g;
const rawTextHits = [...hudSrc.matchAll(RAW_TEXT_ASSIGNMENT_RE)].map((m) => m[0]);
if (rawTextHits.length > 0) {
  fail(`BattleHud.ts: found raw text-assignment call(s) that bypass the bitmap font: ${rawTextHits.join(", ")}`);
} else {
  note("BattleHud.ts: no raw textContent/innerText/innerHTML assignments found");
}

// Every hudText(...)-constructed span (the module's own helper for a bitmap-text node) must
// be routed through setBitmapText at least once somewhere in the file, or it would only ever
// render blank — a cheap grep-level check that every "gf-hud-text ..." class token created by
// hudText(...) also appears as a class-string argument to bitmapText(...)/hudText(...) AND is
// later passed as the first arg to some setBitmapText(...) call. We approximate the latter by
// requiring the variable name returned by hudText(...) to also appear as a setBitmapText(...)
// first argument somewhere in the file.
const hudTextVars = [...hudSrc.matchAll(/const\s+(\w+)\s*=\s*hudText\(/g)].map((m) => m[1]);
for (const varName of hudTextVars) {
  const usedInSetBitmapText = new RegExp(`setBitmapText\\(\\s*${varName}\\b`).test(hudSrc);
  if (!usedInSetBitmapText) {
    fail(`BattleHud.ts: hudText() node "${varName}" is never passed to setBitmapText(...) — it would render blank`);
  }
}
note(`BattleHud.ts: ${hudTextVars.length} hudText() node(s) checked, all routed through setBitmapText`);

// ---------------------------------------------------------------------------
// Check (b): every HUD asset path referenced actually exists on disk.
// ---------------------------------------------------------------------------

function assetConstPath(constName) {
  const re = new RegExp(`${constName}\\s*:\\s*"([^"]+)"`);
  const m = re.exec(assetsSrc);
  return m ? m[1] : null;
}

function checkPublicPath(label, publicPath) {
  if (!publicPath) {
    fail(`${label}: could not resolve a path to check (asset constant not found in assets.ts)`);
    return;
  }
  const onDisk = path.join(publicDir, publicPath.replace(/^\//, ""));
  try {
    readFileSync(onDisk);
    note(`${label}: ${publicPath} exists on disk`);
  } catch {
    fail(`${label}: ${publicPath} does not exist at ${path.relative(repoRoot, onDisk)}`);
  }
}

// fontAscii — used by bitmapText.ts (imported transitively by BattleHud.ts's dynamic text).
checkPublicPath("ASSETS.fontAscii", assetConstPath("fontAscii"));

// faceMarkerRoundel — used directly by BattleHud.ts for the floating teammate roundel.
if (!/ASSETS\.faceMarkerRoundel/.test(hudSrc)) {
  fail("BattleHud.ts: expected a reference to ASSETS.faceMarkerRoundel (teammate plate roundel) but found none");
} else {
  checkPublicPath("ASSETS.faceMarkerRoundel", assetConstPath("faceMarkerRoundel"));
}

// borgBannerPath(id) — used for the optional showBanner name plate. Spot-check the template
// resolves for a borg id known to exist in the public UI export (pl0000 -> code 0000).
if (!/borgBannerPath/.test(hudSrc)) {
  fail("BattleHud.ts: expected a reference to borgBannerPath (per-borg name banner) but found none");
} else {
  const bannerTemplateMatch = /borgBannerPath\(id: string\): string \{\s*return `([^`]+)`/.exec(assetsSrc);
  if (!bannerTemplateMatch) {
    fail("assets.ts: could not find borgBannerPath()'s template string to spot-check");
  } else {
    const sample = bannerTemplateMatch[1].replace("${borgUiCode(id)}", "0000");
    checkPublicPath("borgBannerPath('pl0000') sample", sample);
  }
}

// as_icon: this HUD deliberately does NOT reference it (see PORT-1TO1-STATUS.md section 3 /
// this file's header comment). Assert that non-use at the CODE level (an actual ASSETS.asIcon
// property access or a literal "as_icon" asset path string) — not the doc-comment mentions of
// "as_icon" that explain the decision, which would otherwise self-trigger this check. A future
// edit that quietly wires it in should update the documented rationale + this expectation
// together.
const AS_ICON_CODE_USE_RE = /ASSETS\.asIcon\b|["'`][^"'`]*as_icon[^"'`]*["'`]/;
const nonCommentHudSrc = hudSrc
  .split("\n")
  .filter((line) => !/^\s*\*|^\s*\/\//.test(line))
  .join("\n");
if (AS_ICON_CODE_USE_RE.test(nonCommentHudSrc)) {
  fail(
    "BattleHud.ts: found an as_icon code reference outside comments — if this is an intentional change, " +
      "update the documented rationale (BattleHud.ts header + research/decomp/PORT-1TO1-STATUS.md section 3) " +
      "and this selfcheck's expectation together",
  );
} else {
  note("BattleHud.ts: as_icon is not referenced in code (documented decision — see header comment)");
}

// ---------------------------------------------------------------------------
// Check (c): battleHudState()'s return literal covers every required HudState field.
// ---------------------------------------------------------------------------

const interfaceMatch = /export interface HudState \{([\s\S]*?)\n\}/.exec(hudSrc);
if (!interfaceMatch) {
  fail("BattleHud.ts: could not find `export interface HudState { ... }` to parse");
} else {
  const body = interfaceMatch[1];
  // Split on top-level property lines: "  name: type;" or "  name?: type;" — skip lines that
  // are pure comments. A property is REQUIRED when its name has no "?" before the colon.
  const propLineRe = /^\s*(?:\/\/.*)?$|^\s*\/?\*.*$/;
  const fields = [];
  for (const rawLine of body.split("\n")) {
    if (propLineRe.test(rawLine)) continue;
    const m = /^\s*(\w+)(\??):/.exec(rawLine);
    if (m) fields.push({ name: m[1], optional: m[2] === "?" });
  }
  if (fields.length === 0) {
    fail("BattleHud.ts: HudState interface body parsed but yielded zero fields — parser likely broken, update this selfcheck");
  } else {
    const required = fields.filter((f) => !f.optional).map((f) => f.name);
    const optional = fields.filter((f) => f.optional).map((f) => f.name);
    note(`BattleHud.ts: HudState has ${required.length} required field(s), ${optional.length} optional field(s)`);

    const returnMatch = /export function battleHudState\([\s\S]*?\n  return \{([\s\S]*?)\n  \};\n\}/.exec(presentationSrc);
    if (!returnMatch) {
      fail("presentation.ts: could not find battleHudState()'s `return { ... };` block to parse");
    } else {
      const returnBody = returnMatch[1];
      // Direct keys: "name:" or shorthand "name," / "name\n". Also catch conditional-spread
      // optional keys: "...(x !== undefined ? { x } : {})" contributes key `x`.
      const directKeys = new Set([...returnBody.matchAll(/(?:^|\n)\s*(\w+)\s*[:,]/g)].map((m) => m[1]));
      const spreadKeys = new Set([...returnBody.matchAll(/\?\s*\{\s*(\w+)\s*\}\s*:\s*\{\}\)/g)].map((m) => m[1]));
      const allKeys = new Set([...directKeys, ...spreadKeys]);

      for (const name of required) {
        if (!allKeys.has(name)) {
          fail(`presentation.ts: battleHudState() return literal is missing required HudState field "${name}"`);
        }
      }
      const missingOptional = optional.filter((name) => !allKeys.has(name));
      if (missingOptional.length > 0) {
        note(`presentation.ts: optional HudState field(s) not sourced by battleHudState() (fine — they're optional): ${missingOptional.join(", ")}`);
      }
      note(`presentation.ts: battleHudState() return literal supplies ${allKeys.size} key(s)`);
    }
  }
}

// ---------------------------------------------------------------------------
// Report
// ---------------------------------------------------------------------------

console.log("selfcheck-hud: static checks for apps/game/src/ui/hud/BattleHud.ts + presentation.ts's battleHudState()");
for (const n of notes) console.log(`  note: ${n}`);

if (failures.length > 0) {
  console.error(`\nselfcheck-hud FAILED (${failures.length}):`);
  for (const f of failures) console.error(`  - ${f}`);
  process.exit(1);
}

console.log("\nselfcheck-hud PASS (static/parse-level check only — see file header for what this does not prove)");
