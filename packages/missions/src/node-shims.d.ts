// Minimal ambient declarations for the Node built-ins used by selfcheck.ts.
//
// This package has no @types/node dependency (it is pure data+logic and ships
// no runtime Node usage outside the optional selfcheck harness). These shims
// declare just the few APIs selfcheck.ts touches so the package typechecks in
// isolation. If @types/node is added to the workspace, delete this file.

declare module "node:fs" {
  export function readFileSync(path: string, encoding: "utf8"): string;
  export function existsSync(path: string): boolean;
}

declare module "node:url" {
  export function fileURLToPath(url: string | URL): string;
}

declare module "node:path" {
  export function dirname(path: string): string;
  export function resolve(...paths: string[]): string;
}

interface ImportMeta {
  readonly url: string;
}
