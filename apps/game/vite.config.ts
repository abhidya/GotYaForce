// Vite config for the Gotcha Force browser app.
import { defineConfig } from "vite";

export default defineConfig({
  // three.js + KTX2/Basis transcoder assets are large; keep the warning honest.
  build: {
    target: "es2022",
    chunkSizeWarningLimit: 1500,
  },
  // Web Workers (offline asset conversion, hot parsers) emit as ES modules.
  worker: {
    format: "es",
  },
});
