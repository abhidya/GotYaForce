/**
 * ts-inline-module — run real TypeScript sources in Node without a prior build.
 *
 * WHY THIS EXISTS. Three selfchecks (`selfcheck:menu-flow`, `selfcheck:game-session`,
 * `selfcheck:title-frontend`) execute app/package sources directly. They used to do it by
 * transpiling ONE file into a `data:` module and deleting or substituting its imports with a
 * hand-written regex per import statement, each regex pinned to the exact specifier and
 * named-binding list that import happened to have. A `data:` URL has no base, so any import
 * that escaped the regex became an opaque "Invalid relative URL" crash.
 *
 * All three rotted. `packages/core/src/index.ts` gained `export * from "./gcRuntime.js"`;
 * `gameSession.ts`'s `@gf/missions` import grew past the listed bindings;
 * `titlePropController.ts` gained `../../constants.js`. Each rotted SILENTLY into a crash
 * that reads like a module-resolution bug rather than a stale test — and a selfcheck that
 * cannot execute is worse than none, because it still looks like coverage in `package.json`.
 *
 * The fix is to stop rewriting source text by pattern and stop flattening a module graph
 * into one scope (which also collided on same-named private helpers). `emitInlineModuleGraph`
 * walks the real import graph from an entry file, transpiles each module to its own file in
 * a scratch directory, and rewrites ONLY the module specifiers:
 *
 *   - stubbed specifiers   -> a small generated module supplied by the caller (highest
 *                             precedence, so a browser-only seam can be cut out)
 *   - mapped bare packages -> the emitted file for the package's own real source
 *   - relative specifiers  -> the emitted file for that module (real source, really linked)
 *   - anything else        -> a hard error naming the file and the specifier
 *
 * That last line is the anti-rot property: a newly added dependency fails immediately with
 * "imports X, which has no source mapping or stub", instead of turning into a runtime
 * ReferenceError, or a check that quietly stops running.
 */

import fs from "node:fs";
import path from "node:path";
import { pathToFileURL } from "node:url";
import ts from "typescript";

const RELATIVE_SPECIFIER = /^\.{1,2}\//;

/** The module specifier of an import/re-export statement, or null. */
function moduleSpecifierOf(statement) {
  const isImport = ts.isImportDeclaration(statement);
  const isReExport = ts.isExportDeclaration(statement) && statement.moduleSpecifier !== undefined;
  if (!isImport && !isReExport) return null;
  const specifier = statement.moduleSpecifier;
  return specifier && ts.isStringLiteral(specifier) ? specifier : null;
}

/** Resolve a TS-style relative specifier (which points at the .js the build will emit). */
function resolveRelative(fromFile, specifier) {
  const base = path.resolve(path.dirname(fromFile), specifier);
  const candidates = [base.replace(/\.js$/, ".ts"), `${base}.ts`, path.join(base, "index.ts")];
  return candidates.find((candidate) => fs.existsSync(candidate)) ?? null;
}

function transpile(label, file, source) {
  const compiled = ts.transpileModule(source, {
    compilerOptions: { module: ts.ModuleKind.ES2022, target: ts.ScriptTarget.ES2022 },
    reportDiagnostics: true,
  });
  const diagnostics = compiled.diagnostics ?? [];
  if (diagnostics.length > 0) {
    const text = diagnostics.map((d) => ts.flattenDiagnosticMessageText(d.messageText, " ")).join("; ");
    throw new Error(`${label}: ${file} must transpile without diagnostics — ${text}`);
  }
  return compiled.outputText;
}

/**
 * Emit an importable ES-module graph for `entry` into `outDir`.
 *
 * @param {object} options
 * @param {string} options.label            name used in error messages (the selfcheck).
 * @param {string} options.entry            absolute path to the entry .ts file.
 * @param {string} options.outDir           scratch directory; recreated on every run.
 * @param {Record<string,string>} [options.packages]
 *        bare specifier -> absolute path of that package's real .ts entry. Use this when the
 *        selfcheck wants the REAL implementation linked in.
 * @param {Record<string,string>} [options.stubs]
 *        specifier -> JS source for a stand-in module. Use this for cross-package runtime
 *        values the check deliberately fakes, `"export {};"` for types-only dependencies,
 *        and for browser-only relative seams. Stubs win over every other resolution.
 * @returns {{ url: string, modules: string[] }} file URL to import, and the source files linked.
 */
export function emitInlineModuleGraph({ label, entry, outDir, packages = {}, stubs = {} }) {
  fs.rmSync(outDir, { recursive: true, force: true });
  fs.mkdirSync(outDir, { recursive: true });

  const emitted = new Map();
  const emittedStubs = new Map();
  const usedStubs = new Set();
  const usedPackages = new Set();
  const names = new Set();

  function uniqueName(hint) {
    const base = hint.replace(/[^A-Za-z0-9_.-]/g, "_");
    let name = `${base}.js`;
    let n = 1;
    while (names.has(name)) name = `${base}.${n++}.js`;
    names.add(name);
    return name;
  }

  function emitStub(specifier) {
    const existing = emittedStubs.get(specifier);
    if (existing) return existing;
    const name = uniqueName(`stub_${specifier}`);
    emittedStubs.set(specifier, name);
    fs.writeFileSync(path.join(outDir, name), `${stubs[specifier]}\n`, "utf8");
    return name;
  }

  function emitModule(file) {
    const existing = emitted.get(file);
    if (existing) return existing;
    const name = uniqueName(path.basename(file, ".ts"));
    // Registered BEFORE recursing so an import cycle terminates. gameSession and
    // globalMenuDispatcher genuinely form one (the dispatcher imports a type back).
    emitted.set(file, name);

    const source = fs.readFileSync(file, "utf8");
    const parsed = ts.createSourceFile(file, source, ts.ScriptTarget.ES2022, true, ts.ScriptKind.TS);
    const edits = [];
    for (const statement of parsed.statements) {
      const specifier = moduleSpecifierOf(statement);
      if (!specifier) continue;
      const text = specifier.text;
      let target;
      // Precedence: an explicit stub wins over everything, including a relative specifier
      // that would otherwise resolve to real source. That is what makes it possible to cut a
      // browser-only seam (a DOM input bus, a WebGL loader) out of an otherwise-real graph.
      if (stubs[text] !== undefined) {
        usedStubs.add(text);
        target = `./${emitStub(text)}`;
      } else if (packages[text] !== undefined) {
        usedPackages.add(text);
        target = `./${emitModule(packages[text])}`;
      } else if (RELATIVE_SPECIFIER.test(text)) {
        const dependency = resolveRelative(file, text);
        if (!dependency) {
          throw new Error(`${label}: ${file} imports ${JSON.stringify(text)}, which resolves to no .ts source`);
        }
        target = `./${emitModule(dependency)}`;
      } else {
        throw new Error(
          `${label}: ${path.relative(process.cwd(), file)} imports ${JSON.stringify(text)}, which has no ` +
            "source mapping or stub. Add it to this selfcheck's `packages` (to link the real module) or " +
            "`stubs` (to fake it) — do not let the dependency go unaccounted for.",
        );
      }
      // Rewrite only the text INSIDE the quotes; everything else is left byte-for-byte.
      edits.push([specifier.getStart(parsed) + 1, specifier.getEnd() - 1, target]);
    }

    let rewritten = source;
    for (const [start, end, target] of edits.reverse()) {
      rewritten = `${rewritten.slice(0, start)}${target}${rewritten.slice(end)}`;
    }
    fs.writeFileSync(path.join(outDir, name), transpile(label, file, rewritten), "utf8");
    return name;
  }

  const entryName = emitModule(entry);

  const unusedStubs = Object.keys(stubs).filter((s) => !usedStubs.has(s));
  const unusedPackages = Object.keys(packages).filter((s) => !usedPackages.has(s));
  if (unusedStubs.length > 0 || unusedPackages.length > 0) {
    throw new Error(
      `${label}: declared dependencies that the graph never imports — ` +
        `stubs=${JSON.stringify(unusedStubs)} packages=${JSON.stringify(unusedPackages)}. ` +
        "Drop them so this selfcheck keeps describing the real dependency set.",
    );
  }

  return {
    url: pathToFileURL(path.join(outDir, entryName)).href,
    modules: [...emitted.keys()],
  };
}
