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
  const shims = makeShims(memCtx);
  const instance = await WebAssembly.instantiate(module, {
    env: new Proxy(shims, {
      get: (t, k) => t[k] ?? ((...a) => { throw new Error(`unshimmed import ${String(k)}(${a})`); }),
    }),
  });
  const ex = instance.exports;
  const mem = ex.memory;
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
