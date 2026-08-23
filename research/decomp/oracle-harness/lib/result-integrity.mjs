// result-integrity.mjs — Phase 1 evidence-integrity gate.
//
// Oracle workstream plan §3.2 / Phase 1: a tracked result JSON is EVIDENCE, never
// a verdict. Its presence on disk proves nothing; what makes it count as current
// pass coverage is that every identity it recorded still recomputes to the same
// value against the working tree. If the wasm was rebuilt, the spec edited, the
// fixture regenerated, the field map or its source drifted, or the harness itself
// changed, the evidence is `superseded` and can never be counted again.
//
// Fail-closed: a result that is malformed, that omits an identity its own corpus
// mode requires, or that names an artifact no longer readable, is `invalid` — not
// silently skipped, and never `current`.
//
// Status vocabulary:
//   current    — every AVAILABLE recorded identity recomputes equal
//   superseded — at least one identity recomputes to a different value
//   invalid    — malformed, missing a required identity, or artifact unreadable
//
// "Available" is load-bearing and deliberate: results written before an identity
// field existed cannot be retroactively bound to it, so an absent OPTIONAL field
// is not a mismatch. Fields every result must carry (unit, verdict, result_schema,
// wasm.sha256, spec_sha256, and — in replay mode — corpus.file and corpus.sha256)
// are REQUIRED: absent means `invalid`, never `current`.
import fs from "node:fs";
import path from "node:path";
import { fileURLToPath } from "node:url";
import { createHash } from "node:crypto";

const here = path.dirname(fileURLToPath(import.meta.url));
export const HARNESS_DIR = path.resolve(here, "..");
export const REPO_ROOT = path.resolve(HARNESS_DIR, "..", "..", "..");

const sha256 = (buf) => createHash("sha256").update(buf).digest("hex");

/** sha256 of a file's bytes, or null if it cannot be read. */
function shaOfFile(p) {
  try {
    return sha256(fs.readFileSync(p));
  } catch {
    return null;
  }
}

/**
 * Resolve a path recorded by a possibly-foreign checkout.
 *
 * Results record absolute wasm paths (the driver substitutes {wasm}), so a result
 * written on one machine names a path that does not exist on another. Re-anchor by
 * the repo-relative suffix when the recorded absolute path is unreadable, so the
 * validator stays clean-checkout reproducible instead of calling every foreign
 * result `invalid`.
 */
export function resolveRecordedPath(recorded, root = REPO_ROOT) {
  if (typeof recorded !== "string" || recorded === "") return null;
  const native = recorded.split(/[\\/]/).join(path.sep);
  if (fs.existsSync(native)) return native;
  const norm = recorded.split("\\").join("/");
  // Re-anchor on the first repo-rooted segment we recognize.
  for (const anchor of ["research/", "packages/", "apps/"]) {
    const i = norm.indexOf(anchor);
    if (i >= 0) {
      const candidate = path.join(root, norm.slice(i).split("/").join(path.sep));
      if (fs.existsSync(candidate)) return candidate;
    }
  }
  return null;
}

/**
 * Validate one result object against the working tree.
 *
 * @param {object} result parsed result JSON
 * @param {{root?: string, harnessDir?: string}} [opts]
 * @returns {{status: "current"|"superseded"|"invalid", reasons: string[], checked: string[]}}
 */
export function validateResult(result, opts = {}) {
  const root = opts.root ?? REPO_ROOT;
  const harnessDir = opts.harnessDir ?? HARNESS_DIR;
  const reasons = [];
  const checked = [];
  let invalid = false;

  const bad = (why) => { invalid = true; reasons.push(why); };
  const drift = (why) => { reasons.push(why); };

  if (result === null || typeof result !== "object" || Array.isArray(result)) {
    return { status: "invalid", reasons: ["result is not a JSON object"], checked };
  }
  if (result.result_schema !== 1) bad(`unsupported result_schema ${JSON.stringify(result.result_schema)}`);
  if (typeof result.unit !== "string" || !/^[\w-]+$/.test(result.unit)) bad("missing or malformed unit name");
  const VERDICTS = new Set(["pass", "fail", "partial", "blocked_codec"]);
  if (!VERDICTS.has(result.verdict)) bad(`missing or unknown verdict ${JSON.stringify(result.verdict)}`);

  // A stub written by the harness's crash path records a verdict and nothing else.
  // It is real evidence of a failed run, but it carries no identities to recompute,
  // so it can never be `current`.
  const isStub = result.wasm === undefined && result.spec_sha256 === undefined;
  if (isStub) {
    return {
      status: invalid ? "invalid" : "superseded",
      reasons: reasons.concat(["stub result: no recorded identities to recompute"]),
      checked,
    };
  }

  // ---- wasm (required) ----
  if (result.wasm === null || typeof result.wasm !== "object" || typeof result.wasm.sha256 !== "string") {
    bad("wasm.sha256 is missing — a result not bound to its artifact proves nothing");
  } else {
    const wasmPath = resolveRecordedPath(result.wasm.path, root);
    if (!wasmPath) {
      bad(`wasm artifact not readable at recorded path ${result.wasm.path}`);
    } else {
      const now = shaOfFile(wasmPath);
      checked.push("wasm");
      if (now !== result.wasm.sha256) {
        drift(`wasm rebuilt: recorded ${result.wasm.sha256.slice(0, 12)} != current ${String(now).slice(0, 12)}`);
      }
    }
  }

  // ---- spec (required) ----
  if (typeof result.spec_sha256 !== "string") {
    bad("spec_sha256 is missing");
  } else {
    const specPath = path.join(harnessDir, "specs", `${result.unit}.spec.mjs`);
    const now = shaOfFile(specPath);
    if (now === null) {
      bad(`spec module not readable at ${specPath}`);
    } else {
      checked.push("spec");
      if (now !== result.spec_sha256) {
        drift(`spec edited: recorded ${result.spec_sha256.slice(0, 12)} != current ${now.slice(0, 12)}`);
      }
    }
  }

  // ---- corpus ----
  const corpus = result.corpus;
  if (corpus === null || typeof corpus !== "object") {
    bad("corpus block is missing");
  } else if (corpus.mode === "replay") {
    // A replay fixture is a tracked file: it is stale-able, so its hash is required.
    if (typeof corpus.file !== "string" || typeof corpus.sha256 !== "string") {
      bad("replay corpus must record both file and sha256");
    } else {
      const fixturePath = resolveRecordedPath(corpus.file, root);
      if (!fixturePath) {
        bad(`replay fixture not readable at ${corpus.file}`);
      } else {
        const now = shaOfFile(fixturePath);
        checked.push("corpus");
        if (now !== corpus.sha256) {
          drift(`replay fixture regenerated: recorded ${corpus.sha256.slice(0, 12)} != current ${String(now).slice(0, 12)}`);
        }
      }
    }
  } else if (corpus.mode === "generate") {
    // Generated corpora have no artifact to hash; the seed/n pair plus the spec hash
    // (checked above) is the whole identity. Assert it is well-formed rather than
    // silently accepting a corpus that cannot be reconstructed.
    if (!Number.isInteger(corpus.seed) || !Number.isInteger(corpus.n) || corpus.n < 0) {
      bad("generate corpus must record integer seed and non-negative n");
    } else {
      checked.push("corpus");
    }
  } else {
    bad(`unknown corpus mode ${JSON.stringify(corpus.mode)}`);
  }

  // ---- field map (optional: absent in results predating the field) ----
  const fm = result.field_map;
  if (fm !== undefined) {
    if (fm === null || typeof fm !== "object" || typeof fm.sha256 !== "string" || typeof fm.source_sha256 !== "string") {
      bad("field_map block is present but malformed");
    } else {
      const mapPath = path.join(harnessDir, "actor-field-map.json");
      const nowMap = shaOfFile(mapPath);
      if (nowMap === null) {
        bad(`actor-field-map.json not readable at ${mapPath}`);
      } else {
        checked.push("field_map");
        if (nowMap !== fm.sha256) {
          drift(`field map regenerated: recorded ${fm.sha256.slice(0, 12)} != current ${nowMap.slice(0, 12)}`);
        }
      }
      const srcPath = path.join(root, "packages", "combat", "src", "rom", "actor.ts");
      let nowSrc = null;
      try {
        // Normalized line endings: a CRLF checkout must not defeat the binding.
        const text = fs.readFileSync(srcPath).toString("utf8").split("\r\n").join("\n");
        nowSrc = sha256(Buffer.from(text, "utf8"));
      } catch { /* handled below */ }
      if (nowSrc === null) {
        bad(`field-map source not readable at ${srcPath}`);
      } else {
        checked.push("field_map_source");
        if (nowSrc !== fm.source_sha256) {
          drift(`field-map source drifted: recorded ${fm.source_sha256.slice(0, 12)} != current ${nowSrc.slice(0, 12)}`);
        }
      }
    }
  }

  // ---- harness (content optional; git_rev is provenance evidence only) ----
  // git_rev names the commit the run happened on and moves with every unrelated
  // commit, so it is NOT an integrity input — binding to it would mark every result
  // superseded on the next commit. Harness CONTENT is the real identity.
  const harness = result.harness;
  if (harness !== undefined) {
    if (harness === null || typeof harness !== "object" || typeof harness.entry !== "string") {
      bad("harness block is present but malformed");
    } else if (typeof harness.sha256 === "string") {
      const entryPath = resolveRecordedPath(harness.entry, root);
      const now = entryPath ? shaOfFile(entryPath) : null;
      if (now === null) {
        bad(`harness entry not readable at ${harness.entry}`);
      } else {
        checked.push("harness");
        if (now !== harness.sha256) {
          drift(`harness changed: recorded ${harness.sha256.slice(0, 12)} != current ${now.slice(0, 12)}`);
        }
      }
    }
  }

  if (invalid) return { status: "invalid", reasons, checked };
  return { status: reasons.length ? "superseded" : "current", reasons, checked };
}

/**
 * The single question the driver and the promotion path may ask.
 *
 * True only when the run passed, the evidence still binds to the working tree, and
 * the run was not a deliberate-red rehearsal. Everything else — including a result
 * file that exists and says "pass" — is not current pass coverage.
 */
export function countsAsPassCoverage(result, opts = {}) {
  const v = validateResult(result, opts);
  const ok = v.status === "current" && result?.verdict === "pass" && result?.rehearsal === undefined;
  return { ok, status: v.status, reasons: v.reasons, checked: v.checked };
}

/** Read + validate a result file. A missing file is `invalid`, never a pass. */
export function validateResultFile(filePath, opts = {}) {
  let parsed;
  try {
    parsed = JSON.parse(fs.readFileSync(filePath, "utf8"));
  } catch (e) {
    return { status: "invalid", reasons: [`unreadable or malformed result file: ${e.message}`], checked: [] };
  }
  return validateResult(parsed, opts);
}
