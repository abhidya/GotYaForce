// composedWorker.ts — the dedicated-worker entry the game boots the composed
// ROM module into.
//
// It exists in the app (rather than being imported from @gf/rom-runtime's own
// worker-entry) because Vite resolves worker scripts from a `new URL(...,
// import.meta.url)` literal, which needs a real file inside the app's module
// graph. The body is the package's install call and nothing else.
import { installRomRuntimeWorker } from "@gf/rom-runtime";

installRomRuntimeWorker(self as unknown as DedicatedWorkerGlobalScope);
