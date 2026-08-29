/**
 * Vite BASE_URL — `/GotYaForce/game/` in production, `/` in dev.
 *
 * Vite's `base` config rewrites JS/CSS bundle URLs automatically, but runtime
 * `fetch()` calls and dynamically-constructed asset URLs are NOT rewritten —
 * they need an explicit prefix so paths like `/models/pl0615/model_00.glb`
 * resolve to `${origin}/GotYaForce/game/models/...` on GitHub Pages subpaths
 * instead of `${origin}/models/...` (404).
 */
export const BASE_URL = import.meta.env.BASE_URL;

/** URL schemes that already address a complete resource and must pass through untouched. */
const ABSOLUTE_PREFIXES = ["data:", "http", "blob:"] as const;

/**
 * Prefix an absolute path with the Vite base URL.
 *
 * Absolute URLs (`http://`, `https://`, `data:`, `blob:`) pass through
 * unchanged — only same-origin path-absolute URLs (e.g. `/models/...`) and
 * relative paths (e.g. `audio/bgm/bgm00.ogg`) get the BASE_URL prefix.
 */
export function publicUrl(path: string): string {
  const alreadyAbsolute = ABSOLUTE_PREFIXES.some((prefix) => path.startsWith(prefix));
  const relative = path.startsWith("/") ? path.slice(1) : path;
  return alreadyAbsolute ? path : `${BASE_URL}${relative}`;
}
