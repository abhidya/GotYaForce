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

/**
 * Prefix an absolute path with the Vite base URL.
 *
 * Absolute URLs (`http://`, `https://`, `data:`, `blob:`) pass through
 * unchanged — only same-origin path-absolute URLs (e.g. `/models/...`) and
 * relative paths (e.g. `audio/bgm/bgm00.ogg`) get the BASE_URL prefix.
 */
export function publicUrl(path: string): string {
  if (path.startsWith("data:") || path.startsWith("http") || path.startsWith("blob:")) return path;
  return path.startsWith("/") ? `${BASE_URL}${path.slice(1)}` : `${BASE_URL}${path}`;
}
