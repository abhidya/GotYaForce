// Minimal ambient declarations for the Node built-ins used ONLY by selfcheck.ts.
// The repo has no @types/node installed and the combat package sets compilerOptions.types
// to [] to stay DOM/Node-agnostic. The real runtime is Node (tools/node/node.exe); these
// declarations exist solely so `tsc --noEmit` passes for the self-test harness. They are NOT
// part of the sim's public surface — combat's core modules use no Node APIs.

declare module "node:fs" {
  export function readFileSync(path: string, encoding: "utf8"): string;
}

declare module "node:url" {
  export function fileURLToPath(url: string | URL): string;
}

declare module "node:path" {
  export function dirname(p: string): string;
  export function resolve(...segments: string[]): string;
}

// `process` global (only the members selfcheck touches).
declare const process: {
  argv: string[];
  exit(code?: number): never;
};
