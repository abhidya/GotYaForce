// wasm.mjs — wasm-unit loading for the generic differential-oracle harness.
// Mechanics inherited from the proven PoC path (poc/wasm-port-poc/harness.mjs §1.1
// of oracle-workstream-plan.md): Proxy shim object that throws on any unshimmed
// import; DOL-sourced arena applied at original GameCube addresses; every pointer
// unsigned (>>> 0) because wasm i32 args arrive in JS signed and arena addresses
// are >= 0x80000000.
import fs from "node:fs";

/** fround via typed array (single-precision witness primitive shared with specs). */
const f32buf = new Float32Array(1);
export const fr = (x) => { f32buf[0] = x; return f32buf[0]; };

/**
 * Threads-target support (design v5 note 3 / step-8 subtask): a threads-target
 * module IMPORTS env.memory as a shared WebAssembly.Memory instead of exporting
 * its own. Node reflects import kinds but not memory limits without
 * --experimental-wasm-type-reflection, and the harness must stay flag-free and
 * dependency-free — so read the limits straight out of the binary import
 * section (wasm core spec §5.5.5/§5.5.7: section id 2; limits flags bit 0x1 =
 * has-max, bit 0x2 = shared). Returns {initial, maximum, shared} in pages, or
 * null when the module imports no env.memory (the exported-memory status quo).
 */
export function importedMemoryLimits(wasmBytes) {
  const u8 = new Uint8Array(wasmBytes.buffer, wasmBytes.byteOffset, wasmBytes.byteLength);
  let p = 8; // magic + version
  const leb = () => {
    let r = 0, s = 0, b;
    do { b = u8[p++]; r |= (b & 0x7f) << s; s += 7; } while (b & 0x80);
    return r >>> 0;
  };
  const name = () => { const n = leb(); const v = Buffer.from(u8.subarray(p, p + n)).toString("utf8"); p += n; return v; };
  const limits = () => {
    const flags = leb();
    const initial = leb();
    const maximum = (flags & 0x1) ? leb() : undefined;
    return { initial, maximum, shared: (flags & 0x2) !== 0 };
  };
  while (p < u8.length) {
    const id = u8[p++];
    const end = (() => { const size = leb(); return p + size; })();
    if (id !== 2) { p = end; continue; }
    const count = leb();
    for (let i = 0; i < count; i++) {
      const mod = name(), field = name();
      const kind = u8[p++];
      if (kind === 0x00) leb();                     // func: typeidx
      else if (kind === 0x01) { p++; limits(); }    // table: reftype + limits
      else if (kind === 0x02) {                     // memory: limits
        const lim = limits();
        if (mod === "env" && field === "memory") return lim;
      } else if (kind === 0x03) p += 2;             // global: valtype + mut
      else throw new Error(`unknown import kind 0x${kind.toString(16)} in wasm import section`);
    }
    return null; // a module has at most one import section
  }
  return null;
}

/**
 * Load a wasm unit + arena.
 * @param wasmPath  path to the unit wasm
 * @param arenaPath path to the DOL-sourced arena JSON ({segments:[{addr,b64}]})
 * @param makeShims (memCtx) => shim object; memCtx = {u8, dv, fr, counts}
 * @param flipByte  optional absolute address whose arena byte is XOR'd 0xff AFTER
 *                  arena apply — the deliberate-red rehearsal knob (plan §6 gate 6).
 */
export async function loadUnit({ wasmPath, arenaPath, makeShims, flipByte = null }) {
  const wasmBytes = fs.readFileSync(wasmPath);
  const module = await WebAssembly.compile(wasmBytes);
  const neededImports = WebAssembly.Module.imports(module).map((i) => `${i.module}.${i.name}`);
  const memCtx = { u8: null, dv: null, fr, counts: {} };
  // Threads-target path: the module imports env.memory (shared for a threads
  // build) — construct it host-side with the module's own declared limits so
  // instantiation link-checks against exactly what the relink asked for. The
  // exported-memory path below is untouched.
  let importedMemory = null;
  if (neededImports.includes("env.memory")) {
    const lim = importedMemoryLimits(wasmBytes);
    if (!lim) throw new Error("module imports env.memory but the binary import section has no env.memory entry");
    importedMemory = new WebAssembly.Memory({
      initial: lim.initial,
      // shared memories require a maximum; a fixed-size arena declares max=min.
      maximum: lim.maximum ?? lim.initial,
      shared: lim.shared,
    });
    memCtx.u8 = new Uint8Array(importedMemory.buffer);
    memCtx.dv = new DataView(importedMemory.buffer);
  }
  const shims = makeShims(memCtx);
  const instance = await WebAssembly.instantiate(module, {
    env: new Proxy(shims, {
      get: (t, k) => (k === "memory" && importedMemory != null)
        ? importedMemory
        : t[k] ?? ((...a) => { throw new Error(`unshimmed import ${String(k)}(${a})`); }),
    }),
  });
  const ex = instance.exports;
  const mem = ex.memory ?? importedMemory;
  memCtx.u8 = new Uint8Array(mem.buffer);
  memCtx.dv = new DataView(mem.buffer);

  const arena = JSON.parse(fs.readFileSync(arenaPath, "utf8"));
  for (const s of arena.segments) memCtx.u8.set(Buffer.from(s.b64, "base64"), s.addr >>> 0);
  if (flipByte != null) {
    const a = flipByte >>> 0;
    memCtx.u8[a] ^= 0xff;
  }
  return { ex, mem, u8: memCtx.u8, dv: memCtx.dv, wasmBytes, neededImports, shimCounts: memCtx.counts };
}
