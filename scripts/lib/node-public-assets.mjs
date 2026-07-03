import { readFileSync } from "node:fs";
import path from "node:path";

import { createPublicAssetCatalog } from "../../packages/assets/dist/index.js";

export function createNodePublicAssetCatalog(repoRoot) {
  const publicRoot = path.join(repoRoot, "apps", "game", "public");
  const toPublicFile = (url) => path.join(publicRoot, new URL(url).pathname.replace(/^\/+/, ""));
  return createPublicAssetCatalog({
    baseUrl: "https://gotcha-force.local/",
    fetchJson: async (url) => JSON.parse(readFileSync(toPublicFile(url), "utf8")),
    fetchArrayBuffer: async (url) => {
      const bytes = readFileSync(toPublicFile(url));
      return bytes.buffer.slice(bytes.byteOffset, bytes.byteOffset + bytes.byteLength);
    },
  });
}

export function readPublicStageCatalog(repoRoot) {
  return JSON.parse(readFileSync(path.join(repoRoot, "apps", "game", "public", "stages", "manifest.json"), "utf8"));
}
