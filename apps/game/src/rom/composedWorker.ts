// composedWorker.ts — the dedicated-worker entry the game boots the composed
// ROM module into.
//
// It exists in the app (rather than being imported from @gf/rom-runtime's own
// worker-entry) because Vite resolves worker scripts from a `new URL(...,
// import.meta.url)` literal, which needs a real file inside the app's module
// graph. The body is the package's install call and nothing else.
//
// Imported from the package's worker module DIRECTLY, not from its barrel: the
// barrel re-exports the damage adapters, which pull in @gf/combat, which the
// worker never touches. Measured: through the barrel this chunk builds at
// 1,683 kB, almost all of it code the composed module cannot call; imported
// directly it is 7.7 kB.
import { installRomRuntimeWorker } from "@gf/rom-runtime/src/worker";

installRomRuntimeWorker(self as unknown as DedicatedWorkerGlobalScope);
