// worker-entry.ts — dedicated-worker entry point for the composed-module
// runtime. Bundle this file as the worker script (esbuild for the self-test;
// Vite's `new Worker(new URL("./worker-entry.ts", import.meta.url), { type:
// "module" })` for app integration).
import { installRomRuntimeWorker } from "./worker.js";

installRomRuntimeWorker(self as unknown as DedicatedWorkerGlobalScope);
