/**
 * Game-side wrapper around `@gf/assets` `createPublicAssetCatalog` that re-prefixes
 * every URL the catalog builds with the Vite BASE_URL.
 *
 * Why: the underlying catalog resolves paths against `document.baseURI`. On GitHub
 * Pages that is `${origin}/GotYaForce/game/`, BUT the catalog uses path-absolute
 * inputs (`/models/...`, `/stages/...`, `/ui/...`), and `new URL("/foo", base)`
 * collapses back to `${origin}/foo` (path-absolute URLs replace the base path
 * entirely). Every JSON fetch and every URL handed back to the caller (model
 * manifests, stage model URLs, UI scene model paths) lands at `${origin}/...`
 * — a 404 on GitHub Pages.
 *
 * The fix is to reprefix the catalog's resolved absolute URLs with BASE_URL: pull
 * the pathname back out and run it through `publicUrl`. Dev (`BASE_URL = "/"`) is
 * a no-op; production (`BASE_URL = "/GotYaForce/game/"`) restores the subpath.
 */
import {
  createPublicAssetCatalog,
  type PublicAssetCatalog,
} from "@gf/assets";

import { publicUrl } from "./publicUrl.js";

/**
 * Re-prefix a catalog-built URL with BASE_URL. Catalog URLs always resolve
 * absolute against the page origin, so pull the pathname out and route through
 * publicUrl. Non-http inputs (already-relative paths, data: URLs) pass through.
 */
/** Absolute (http(s):// or protocol-relative) catalog URLs need their pathname pulled back
 *  out before re-prefixing; anything already relative goes straight through publicUrl. */
const ABSOLUTE_URL = /^https?:\/\//;

function reprefix(url: string): string {
  let pathAndQuery = url;
  if (ABSOLUTE_URL.test(url) || url.startsWith("//")) {
    try {
      const parsed = new URL(url);
      pathAndQuery = `${parsed.pathname}${parsed.search}`;
    } catch {
      // Not parseable as a URL after all; publicUrl handles it as a plain path.
    }
  }
  return publicUrl(pathAndQuery);
}

/** Fetch a catalog URL through the BASE_URL re-prefix, failing loudly on a non-2xx so a
 *  404'd manifest surfaces as an error instead of a JSON parse failure further downstream. */
async function fetchOk(url: string, what: string): Promise<Response> {
  const response = await fetch(reprefix(url));
  if (!response.ok) {
    throw new Error(`Failed to load asset ${what} ${url}: ${response.status} ${response.statusText}`);
  }
  return response;
}

export function createGameAssetCatalog(): PublicAssetCatalog {
  const inner = createPublicAssetCatalog({
    fetchJson: (url) => fetchOk(url, "JSON").then((response) => response.json()),
    fetchArrayBuffer: (url) => fetchOk(url, "bytes").then((response) => response.arrayBuffer()),
  });

  return {
    loadModelManifest: inner.loadModelManifest,
    async loadModelLibraryPaths() {
      const map = await inner.loadModelLibraryPaths();
      const out = new Map<string, string>();
      for (const [id, url] of map) out.set(id, reprefix(url));
      return out;
    },
    loadStageManifest: inner.loadStageManifest,
    loadStageRenderState: inner.loadStageRenderState,
    async loadStageAssets<T = unknown>(stageId: string) {
      const assets = await inner.loadStageAssets<T>(stageId);
      return { ...assets, modelUrls: assets.modelUrls.map(reprefix) };
    },
    loadUiSceneManifest: inner.loadUiSceneManifest,
    async loadUiSceneModelPaths(sceneId, options) {
      return (await inner.loadUiSceneModelPaths(sceneId, options)).map(reprefix);
    },
    stageAssetUrl(stageId, path) {
      return reprefix(inner.stageAssetUrl(stageId, path));
    },
    uiAssetUrl(path) {
      return reprefix(inner.uiAssetUrl(path));
    },
  };
}
