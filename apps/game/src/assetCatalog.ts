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
function reprefix(url: string): string {
  if (!/^https?:\/\//.test(url) && !url.startsWith("//")) return publicUrl(url);
  try {
    const parsed = new URL(url);
    return publicUrl(`${parsed.pathname}${parsed.search}`);
  } catch {
    return publicUrl(url);
  }
}

export function createGameAssetCatalog(): PublicAssetCatalog {
  const inner = createPublicAssetCatalog({
    fetchJson: (url) =>
      fetch(reprefix(url)).then((response) => {
        if (!response.ok) {
          throw new Error(`Failed to load asset JSON ${url}: ${response.status} ${response.statusText}`);
        }
        return response.json();
      }),
    fetchArrayBuffer: (url) =>
      fetch(reprefix(url)).then((response) => {
        if (!response.ok) {
          throw new Error(`Failed to load asset bytes ${url}: ${response.status} ${response.statusText}`);
        }
        return response.arrayBuffer();
      }),
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
