#!/usr/bin/env node
import { readFile, writeFile } from "node:fs/promises";
import path from "node:path";
import { fileURLToPath } from "node:url";

const repoRoot = path.resolve(path.dirname(fileURLToPath(import.meta.url)), "..");
const source = path.join(repoRoot, "apps", "game", "src", "ui", "styles.css");
const target = path.join(repoRoot, "apps", "game", "src", "ui", "styles.generated.ts");

const css = await readFile(source, "utf8");
const body = `/**
 * Injectable copy of styles.css. Keep in sync with scripts/sync-ui-css.mjs.
 */

export const GF_UI_CSS = ${JSON.stringify(css)};
`;

await writeFile(target, body, "utf8");
console.log(`synced ${path.relative(repoRoot, target).replaceAll(path.sep, "/")}`);
