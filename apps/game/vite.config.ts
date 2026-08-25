// Vite config for the Gotcha Force browser app.
import { defineConfig } from "vite";

// H1 cross-origin isolation (docs/playable-port-design.md, V4 AMENDMENTS H1):
// shared WebAssembly.Memory, SharedArrayBuffer, and Atomics.wait are gated on
// window.crossOriginIsolated === true, which browsers grant only when the
// document arrives with these response headers. Dev and preview servers send
// them directly here; production (GitHub Pages cannot set response headers)
// gets them from the vendored public/coi-serviceworker.js instead, registered
// first in index.html. Every asset the app loads is same-origin, so
// require-corp needs no crossorigin/CORP annotations anywhere.
const coiHeaders = {
  "Cross-Origin-Opener-Policy": "same-origin",
  "Cross-Origin-Embedder-Policy": "require-corp",
};

export default defineConfig(({ command }) => ({
  // Production is served from the GitHub Pages subpath /GotYaForce/game/.
  // Local dev keeps the default "/" base.
  base: command === "build" ? "/GotYaForce/game/" : "/",
  // three.js + KTX2/Basis transcoder assets are large; keep the warning honest.
  build: {
    target: "es2022",
    chunkSizeWarningLimit: 1500,
  },
  server: {
    headers: coiHeaders,
  },
  preview: {
    headers: coiHeaders,
  },
  // Web Workers (offline asset conversion, hot parsers) emit as ES modules.
  worker: {
    format: "es",
  },
}));
