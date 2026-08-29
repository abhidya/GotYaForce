// =============================================================================
// composed.ts — wiring a REAL composed module (assembly-gate output with the
// G2/H3 dispatch companion) onto the H2 host bridge.
//
// The gate links a window of ported units into one module plus the dispatch
// companion. That module has exactly two kinds of out-of-window edge:
//
//   1. TABLE MISS — an address-keyed indirect call whose GC address is not in
//      the companion's table. The companion routes it to the declared import
//      `__gf_dispatch_miss(u32 gc_addr, i32 argptr)`, which worker.ts binds
//      straight to the Atomics bridge. This edge is already H2-shaped.
//
//   2. DIRECT CALL TO AN UNLINKED CALLEE — a linked function calling an
//      out-of-window symbol by name. emcc leaves those as ordinary function
//      imports (`env.zz_0085e00_`, `env.gnt4_PSVECMag_bl`, …) with their TRUE
//      C signatures. H2 is explicit that these are bridge edges too ("every
//      out-of-window callee becomes a declared wasm import, bound to a bridge
//      that performs a synchronous Atomics-based RPC"), but they do NOT share
//      the companion's uniform (i32 argptr) -> i32 shape.
//
// This file closes edge 2. It reads each imported function's real signature
// out of the module's own type/import sections and (in worker.ts) synthesizes
// a per-import TRAMPOLINE that marshals the call into a dispatch frame in the
// shared linear memory and hands it to the same bridge stub the miss import
// uses. After that, EVERY out-of-window call — missed indirect or direct —
// crosses through the declared bridge and lands in the ledger. An import that
// cannot be bound is a loud composition error, never a silent no-op.
//
// Address authority: the gate's own convention. `zz_<7 hex>_` spells its GC
// address with the leading `8` nibble dropped (zz_01b98ec_ == 0x801b98ec);
// `FUN_<8 hex>` spells it in full. SDK shim symbols (`gnt4_*`) have NO GC
// address — they are host-side stand-ins for library code — so they get a
// SYNTHETIC key in a reserved range that can never collide with GC memory.
// The synthetic keys are ledger/registry keys only and are never dereferenced.
// =============================================================================

/** wasm value types (core spec §5.3.1). */
export enum WasmType {
  I32 = 0x7f,
  I64 = 0x7e,
  F32 = 0x7d,
  F64 = 0x7c,
}

export interface ImportedFunctionSignature {
  /** Import module name (always "env" for gate output). */
  module: string;
  /** Import field name — the out-of-window symbol. */
  field: string;
  /** Parameter value types, in order. */
  params: number[];
  /** Result value types (wasm MVP: 0 or 1). */
  results: number[];
}

export interface MemoryLimits {
  initial: number;
  maximum: number | undefined;
  shared: boolean;
}

export interface ModuleShape {
  memory: MemoryLimits | null;
  functions: ImportedFunctionSignature[];
}

/**
 * Reserved key range for symbols with no GC address (the `gnt4_*` SDK shim
 * family). Chosen below the 0x80000000 GC window so a synthetic key can never
 * be mistaken for — or collide with — a real ROM address.
 */
export const SYNTHETIC_ADDR_BASE = 0x7f00_0000;
export const SYNTHETIC_ADDR_MASK = 0x00ff_ffff;

/**
 * Base of the runtime's dispatch-frame scratch region in the composed
 * module's linear memory, and how it is divided.
 *
 * Placement rationale (recorded because it is an assumption, not a proof):
 * the gate links with `-sINITIAL_MEMORY=2155479040 -sALLOW_MEMORY_GROWTH=0`,
 * i.e. a fixed 0x807A0000-byte linear memory whose TOP is the flat GC arena at
 * original addresses (0x80000000 …). emscripten's static data and shadow
 * stack sit in the first few hundred KB; the ROM window starts at 0x80000000.
 * 0x40000000 is a gigabyte clear of both, and always in bounds because the
 * memory cannot grow or shrink. `assertScratchRegionClear` checks the region
 * really is untouched at boot instead of assuming it.
 */
export const SCRATCH_BASE = 0x4000_0000;
/** Frames the HOST may use to drive exports (indices 0 … HOST_FRAME_SLOTS-1). */
export const HOST_FRAME_SLOTS = 8;
/** Frames the worker's import trampolines may nest through. */
export const TRAMPOLINE_FRAME_SLOTS = 32;

/** Byte address of host frame slot `index`. */
export function hostFrameAddr(index: number, frameSize: number): number {
  if (index < 0 || index >= HOST_FRAME_SLOTS) {
    throw new RangeError(`host frame slot ${index} out of range 0..${HOST_FRAME_SLOTS - 1}`);
  }
  return SCRATCH_BASE + index * frameSize;
}

/** Byte address of the worker's trampoline frame region. */
export function trampolineFrameBase(frameSize: number): number {
  return SCRATCH_BASE + HOST_FRAME_SLOTS * frameSize;
}

/** Total bytes the scratch region occupies. */
export function scratchByteLength(frameSize: number): number {
  return (HOST_FRAME_SLOTS + TRAMPOLINE_FRAME_SLOTS) * frameSize;
}

const ZZ_SYMBOL = /^zz_([0-9a-fA-F]{7})_$/;
const FUN_SYMBOL = /^FUN_([0-9a-fA-F]{8})$/;

export type AddressSource = "zz-marker" | "fun-marker" | "synthetic-sdk";

export interface SymbolAddress {
  symbol: string;
  gcAddr: number;
  source: AddressSource;
}

/** FNV-1a 32-bit — deterministic across runs and machines, unlike any hash
 *  derived from iteration order, so a symbol's synthetic key is stable. */
function fnv1a(text: string): number {
  let h = 0x811c9dc5;
  for (let i = 0; i < text.length; i++) {
    h ^= text.charCodeAt(i);
    h = Math.imul(h, 0x01000193) >>> 0;
  }
  return h >>> 0;
}

/**
 * The gate's symbol→GC-address convention, plus the reserved synthetic range
 * for address-less SDK shims. Never throws: an unrecognized name is given a
 * synthetic key and reported as such, so the caller can decide whether an
 * un-addressed import is acceptable rather than the resolver deciding silently.
 */
export function gcAddressForSymbol(symbol: string): SymbolAddress {
  const zz = ZZ_SYMBOL.exec(symbol);
  if (zz) {
    return { symbol, gcAddr: ((0x8 << 28) | parseInt(zz[1]!, 16)) >>> 0, source: "zz-marker" };
  }
  const fun = FUN_SYMBOL.exec(symbol);
  if (fun) {
    return { symbol, gcAddr: parseInt(fun[1]!, 16) >>> 0, source: "fun-marker" };
  }
  return {
    symbol,
    gcAddr: (SYNTHETIC_ADDR_BASE | (fnv1a(symbol) & SYNTHETIC_ADDR_MASK)) >>> 0,
    source: "synthetic-sdk",
  };
}

/**
 * Read the module's import section: the shared `env.memory` limits plus every
 * imported FUNCTION with its resolved signature. Dependency-free binary
 * parsing (wasm core spec §5.5.5/§5.5.7) so the worker bundle stays
 * self-contained — the same technique as the oracle harness's
 * `importedMemoryLimits` (research/decomp/oracle-harness/lib/wasm.mjs),
 * extended to resolve type indices against the type section.
 */
export function readModuleShape(wasmBytes: ArrayBuffer | Uint8Array): ModuleShape {
  const u8 = wasmBytes instanceof Uint8Array ? wasmBytes : new Uint8Array(wasmBytes);
  let p = 8; // magic + version
  const leb = (): number => {
    let r = 0;
    let s = 0;
    let b: number;
    do {
      b = u8[p++] ?? 0;
      r |= (b & 0x7f) << s;
      s += 7;
    } while (b & 0x80);
    return r >>> 0;
  };
  const name = (): string => {
    const n = leb();
    const v = new TextDecoder().decode(u8.subarray(p, p + n));
    p += n;
    return v;
  };
  const limits = (): MemoryLimits => {
    const flags = leb();
    const initial = leb();
    const maximum = flags & 0x1 ? leb() : undefined;
    return { initial, maximum, shared: (flags & 0x2) !== 0 };
  };

  const types: Array<{ params: number[]; results: number[] }> = [];
  const shape: ModuleShape = { memory: null, functions: [] };

  while (p < u8.length) {
    const id = u8[p++] ?? 0;
    const size = leb();
    const end = p + size;
    if (id === 1) {
      // Type section — needed to resolve imported functions' type indices.
      const count = leb();
      for (let i = 0; i < count; i++) {
        const form = u8[p++] ?? 0;
        if (form !== 0x60) throw new Error(`unexpected type form 0x${form.toString(16)} in wasm type section`);
        const paramCount = leb();
        const params: number[] = [];
        for (let j = 0; j < paramCount; j++) params.push(u8[p++] ?? 0);
        const resultCount = leb();
        const results: number[] = [];
        for (let j = 0; j < resultCount; j++) results.push(u8[p++] ?? 0);
        types.push({ params, results });
      }
    } else if (id === 2) {
      const count = leb();
      for (let i = 0; i < count; i++) {
        const mod = name();
        const field = name();
        const kind = u8[p++] ?? 0;
        if (kind === 0x00) {
          const typeIndex = leb();
          const signature = types[typeIndex];
          if (!signature) throw new Error(`import ${mod}.${field} references missing type ${typeIndex}`);
          shape.functions.push({ module: mod, field, params: signature.params, results: signature.results });
        } else if (kind === 0x01) {
          p++; // element type
          limits();
        } else if (kind === 0x02) {
          const lim = limits();
          if (mod === "env" && field === "memory") shape.memory = lim;
        } else if (kind === 0x03) {
          p += 2; // valtype + mutability
        } else {
          throw new Error(`unknown import kind 0x${kind.toString(16)} in wasm import section`);
        }
      }
      // Types precede imports in a valid module, and there is at most one of
      // each, so the shape is complete once the import section is consumed.
      return shape;
    }
    p = end;
  }
  return shape;
}

export interface BridgedImportBinding extends SymbolAddress {
  params: number[];
  results: number[];
}

/**
 * Plan the bridge bindings for a composed module: every imported function
 * EXCEPT the companion's own miss hook (which worker.ts binds directly).
 * Duplicate address keys are a hard error — two symbols sharing a ledger key
 * would silently merge their crossings and their adapters.
 */
export function planBridgedImports(shape: ModuleShape, missImport = "__gf_dispatch_miss"): BridgedImportBinding[] {
  const bindings: BridgedImportBinding[] = [];
  const seen = new Map<number, string>();
  for (const fn of shape.functions) {
    if (fn.field === missImport) continue;
    const resolved = gcAddressForSymbol(fn.field);
    const clash = seen.get(resolved.gcAddr);
    if (clash) {
      throw new Error(
        `bridged-import address collision at 0x${resolved.gcAddr.toString(16)}: ${clash} and ${fn.field}`,
      );
    }
    seen.set(resolved.gcAddr, fn.field);
    bindings.push({ ...resolved, params: fn.params, results: fn.results });
  }
  return bindings;
}

/** Value-type name for diagnostics and provenance. */
export function wasmTypeName(type: number): string {
  switch (type) {
    case WasmType.I32:
      return "i32";
    case WasmType.I64:
      return "i64";
    case WasmType.F32:
      return "f32";
    case WasmType.F64:
      return "f64";
    default:
      return `type_0x${type.toString(16)}`;
  }
}
