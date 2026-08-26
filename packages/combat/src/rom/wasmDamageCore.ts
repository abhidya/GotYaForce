// wasmDamageCore.ts — the ported GameCube damage unit, live in the browser.
//
// Loads the oracle-verified damage-core wasm (research/decomp/port-units/
// damage-core/unit.wasm — 4/4 functions byte-exact over 26,232 replayed cases,
// see research/decomp/data/oracle-results/damage-core.json) and exposes it
// behind the exact signatures of sourceDamage.ts, so the game can compute
// damage with the ROM's own compiled code instead of the TS reference.
//
// Everything here mirrors the proven oracle-harness path:
//  - arena segments applied at ORIGINAL GameCube addresses inside wasm linear
//    memory (the "one memory arena at original addresses" design);
//  - the three gnt4_PS* SDK imports shimmed in JS with fround single-precision,
//    byte-identical to the PoC shims the oracle ran under;
//  - actors encoded at the same scratch addresses and offsets the verified
//    replay used (specs/damage-core.spec.mjs encodeCase), so the wasm reads
//    exactly the struct layout it was verified against.
//
// Browser-only inputs: the caller fetches unit.wasm + arena.json (served from
// apps/game/public/rom/) and passes the bytes/JSON in — no filesystem here.

import type {
  SourceDamageActor,
  SourceDamageContext,
  SourceDamageTarget,
} from "../damage/sourceDamage";

// Scratch addresses — identical to the verified spec (damage-core.spec.mjs:46).
const REC = 0x80600000;
const ATT = 0x80601000;
const ATTB = 0x80602000;
const DEF = 0x80604000;
const DESC = 0x80606000;
const CAT = 0x80608000;
// bss live-state arrays the formula reads (same addresses as the ROM).
const HP_MIRROR = 0x803b069c; // s16[slot]
const ENERGY = 0x803b068c; // i32[team]

const f32buf = new Float32Array(1);
const fr = (x: number): number => {
  f32buf[0] = x;
  return f32buf[0];
};

export interface ArenaJson {
  segments: Array<{ addr: number; b64: string }>;
}

interface DamageCoreExports {
  /** Exported by the classic build; the threads relink IMPORTS env.memory instead. */
  memory?: WebAssembly.Memory;
  zz_003cd5c_(rec: number, att: number, def: number): number;
  zz_0066298_(borgNumberPtr: number): number;
  zz_003d344_(target: number, amount: number): number;
  _initialize?(): void;
}

/** How the instantiated unit's linear memory is provided — proof surface for
 * the step-8 threads relink (design v5 note 3): a threads-target module imports
 * a shared WebAssembly.Memory instead of exporting its own. */
export interface RomDamageMemoryInfo {
  imported: boolean;
  shared: boolean;
}

export interface RomDamageCore {
  computeBaseDamage(
    attacker: SourceDamageActor,
    defender: SourceDamageActor,
    basePower: number,
    ctx: SourceDamageContext,
  ): number;
  lookupTypeCategory(borgNumber: number): number;
  applyHpDamage(target: SourceDamageTarget, amount: number): void;
  /** How many times each SDK shim fired — diagnostics for the HUD/console. */
  readonly shimCounts: Record<string, number>;
  /** Total wasm calls served, for proving the ROM path is actually live. */
  readonly callCounts: Record<string, number>;
  /** Whether the module imported (shared) memory — the threads-relink proof. */
  readonly memoryInfo: RomDamageMemoryInfo;
}

function base64ToBytes(b64: string): Uint8Array {
  const bin = atob(b64);
  const out = new Uint8Array(bin.length);
  for (let i = 0; i < bin.length; i++) out[i] = bin.charCodeAt(i);
  return out;
}

/**
 * Read the env.memory import limits straight out of the binary import section
 * (wasm core spec §5.5.5/§5.5.7: section id 2; limits flags bit 0x1 = has-max,
 * bit 0x2 = shared). Browser-safe TS port of the oracle harness's
 * importedMemoryLimits (research/decomp/oracle-harness/lib/wasm.mjs) — the JS
 * API does not reflect memory limits, and instantiation must construct the
 * shared memory with EXACTLY the limits the relink declared so the link-check
 * proves the module got what it asked for. Returns null when the module
 * imports no env.memory (the exported-memory status quo).
 */
function importedMemoryLimits(u8: Uint8Array): { initial: number; maximum?: number; shared: boolean } | null {
  let p = 8; // magic + version
  const leb = (): number => {
    let r = 0;
    let s = 0;
    let b: number;
    do {
      b = u8[p++]!;
      r |= (b & 0x7f) << s;
      s += 7;
    } while (b & 0x80);
    return r >>> 0;
  };
  const utf8 = new TextDecoder();
  const name = (): string => {
    const n = leb();
    const v = utf8.decode(u8.subarray(p, p + n));
    p += n;
    return v;
  };
  const limits = (): { initial: number; maximum?: number; shared: boolean } => {
    const flags = leb();
    const initial = leb();
    const out: { initial: number; maximum?: number; shared: boolean } = {
      initial,
      shared: (flags & 0x2) !== 0,
    };
    if (flags & 0x1) out.maximum = leb();
    return out;
  };
  while (p < u8.length) {
    const id = u8[p]!;
    p += 1;
    const size = leb();
    const end = p + size;
    if (id !== 2) {
      p = end;
      continue;
    }
    const count = leb();
    for (let i = 0; i < count; i++) {
      const mod = name();
      const field = name();
      const kind = u8[p++]!;
      if (kind === 0x00) leb(); // func: typeidx
      else if (kind === 0x01) {
        p++; // table: reftype
        limits();
      } else if (kind === 0x02) {
        const lim = limits(); // memory
        if (mod === "env" && field === "memory") return lim;
      } else if (kind === 0x03) p += 2; // global: valtype + mut
      else throw new Error(`unknown import kind 0x${kind.toString(16)} in wasm import section`);
    }
    return null; // a module has at most one import section
  }
  return null;
}

/** The three SDK imports the unit needs, fround-exact like the oracle's shims. */
function makeShims(memCtx: { dv: DataView | null; counts: Record<string, number> }) {
  const count = (name: string) => {
    memCtx.counts[name] = (memCtx.counts[name] ?? 0) + 1;
  };
  return {
    gnt4_PSVECSubtract_bl: (a: number, b: number, out: number) => {
      count("gnt4_PSVECSubtract_bl");
      a >>>= 0; b >>>= 0; out >>>= 0;
      const dv = memCtx.dv!;
      for (let i = 0; i < 3; i++) {
        dv.setFloat32(out + i * 4, fr(dv.getFloat32(a + i * 4, true) - dv.getFloat32(b + i * 4, true)), true);
      }
    },
    gnt4_PSQUATDotProduct_bl: (a: number, b: number): number => {
      count("gnt4_PSQUATDotProduct_bl");
      a >>>= 0; b >>>= 0;
      const dv = memCtx.dv!;
      let s = 0;
      for (let i = 0; i < 3; i++) s = fr(s + fr(dv.getFloat32(a + i * 4, true) * dv.getFloat32(b + i * 4, true)));
      return s;
    },
    gnt4_PSQUATScale_bl: (s: number, v: number, out: number) => {
      count("gnt4_PSQUATScale_bl");
      v >>>= 0; out >>>= 0;
      const dv = memCtx.dv!;
      for (let i = 0; i < 3; i++) dv.setFloat32(out + i * 4, fr(fr(s) * dv.getFloat32(v + i * 4, true)), true);
    },
  };
}

/**
 * Instantiate the verified damage unit and return the game-facing API.
 *
 * @param wasmBytes bytes of port-units/damage-core/unit.wasm
 * @param arena     parsed arena.json (DOL-sourced segments)
 */
export async function createRomDamageCore(
  wasmBytes: ArrayBuffer | Uint8Array,
  arena: ArenaJson,
): Promise<RomDamageCore> {
  const memCtx: { dv: DataView | null; counts: Record<string, number> } = { dv: null, counts: {} };
  const shims = makeShims(memCtx);
  const bytesU8 =
    wasmBytes instanceof Uint8Array
      ? wasmBytes
      : new Uint8Array(wasmBytes);
  const module = await WebAssembly.compile(
    bytesU8.buffer.slice(bytesU8.byteOffset, bytesU8.byteOffset + bytesU8.byteLength) as ArrayBuffer,
  );
  // Threads-target path (step 8, design v5 note 3): the relinked module IMPORTS
  // env.memory as a shared WebAssembly.Memory — construct it host-side with the
  // module's own declared limits, mirroring the oracle harness's loadUnit
  // exactly. The exported-memory path (classic damage-core.wasm) is untouched
  // and remains the fallback for ?romwasm=1/default.
  let importedMemory: WebAssembly.Memory | null = null;
  const importsMemory = WebAssembly.Module.imports(module).some(
    (i) => i.module === "env" && i.name === "memory" && i.kind === "memory",
  );
  if (importsMemory) {
    const lim = importedMemoryLimits(bytesU8);
    if (!lim) throw new Error("module imports env.memory but the binary import section has no env.memory entry");
    importedMemory = new WebAssembly.Memory({
      initial: lim.initial,
      // shared memories require a maximum; a fixed-size arena declares max=min.
      maximum: lim.maximum ?? lim.initial,
      shared: lim.shared,
    });
  }
  const instance = await WebAssembly.instantiate(module, {
    env: new Proxy(shims as Record<string, unknown>, {
      get: (t, k) =>
        k === "memory" && importedMemory != null
          ? importedMemory
          : (t[k as string] ??
            (() => {
              throw new Error(`unshimmed import ${String(k)}`);
            })),
    }) as WebAssembly.ModuleImports,
  });
  const ex = instance.exports as unknown as DamageCoreExports;
  const mem = ex.memory ?? importedMemory;
  if (!mem) throw new Error("module neither exports nor imports a linear memory");
  const memoryInfo: RomDamageMemoryInfo = {
    imported: importedMemory != null,
    shared:
      importedMemory != null &&
      typeof SharedArrayBuffer !== "undefined" &&
      mem.buffer instanceof SharedArrayBuffer,
  };
  const u8 = new Uint8Array(mem.buffer);
  const dv = new DataView(mem.buffer);
  memCtx.dv = dv;

  // Arena at original GameCube addresses — the DOL-initialized tables the
  // formula reads (damage matrices, curves, float constants, struct pointers).
  for (const s of arena.segments) u8.set(base64ToBytes(s.b64), s.addr >>> 0);

  // DOL-initialized runtime-struct pointers, resolved by READING the arena.
  const STRUCT30 = dv.getUint32(0x80433930, true); // [0x32] challenge-mode byte
  const STRUCT34 = dv.getUint32(0x80433934, true); // [team*0x3c+0x114] energy max
  const STRUCT50 = dv.getUint32(0x80433950, true); // [team] side-rank byte

  const callCounts: Record<string, number> = {};
  const tally = (name: string) => {
    callCounts[name] = (callCounts[name] ?? 0) + 1;
  };

  const wU8 = (a: number, v: number) => { u8[a >>> 0] = v & 0xff; };
  const wU16 = (a: number, v: number) => dv.setUint16(a >>> 0, v & 0xffff, true);
  const wI16 = (a: number, v: number) => dv.setInt16(a >>> 0, v | 0, true);
  const wU32 = (a: number, v: number) => dv.setUint32(a >>> 0, v >>> 0, true);
  const wI32 = (a: number, v: number) => dv.setInt32(a >>> 0, v | 0, true);
  const wF32 = (a: number, v: number) => dv.setFloat32(a >>> 0, v, true);
  // borgNumber is stored big-endian in the ROM struct (family high, variant low).
  const wU16be = (a: number, v: number) => {
    u8[a >>> 0] = (v >> 8) & 0xff;
    u8[(a >>> 0) + 1] = v & 0xff;
  };

  // The two live actors always use fixed slots/teams derived from their own
  // fields, mirroring the spec: slot indexes the HP mirror, team the energy row.
  function encodeActor(base: number, a: SourceDamageActor, slot: number, container: number | null) {
    wU8(base + 0x00, 1); // live marker
    wU8(base + 0x18, a.isActive ? 1 : 0);
    wU8(base + 0x83, a.isBorg ? 0 : 1); // 0 = borg (ROM polarity)
    wU8(base + 0x88, a.team & 0xff);
    wU16(base + 0x1c4, a.maxHp);
    wU8(base + 0x3e4, slot & 0xff);
    wU8(base + 0x3e6, a.heroFlag & 0xff);
    wU16be(base + 0x3e8, a.borgNumber);
    wU8(base + 0x43a, a.handicap & 0xff);
    wU8(base + 0x6ca, a.comboRank & 0xff);
    wU8(base + 0x6fc, a.pairAttack & 0xff);
    if (container != null) wF32(container + 0xc4, a.power);
    else wF32(base + 0xb4, a.power);
  }

  function computeBaseDamage(
    attacker: SourceDamageActor,
    defender: SourceDamageActor,
    basePower: number,
    ctx: SourceDamageContext,
  ): number {
    tally("computeBaseDamage");
    // record
    wU16(REC + 0x00, basePower);
    wU8(REC + 0x06, ctx.attackerHpCurveIndex & 0xff);
    wU8(REC + 0x07, ctx.attackerForceCurveIndex & 0xff);
    wU16(REC + 0x10, ctx.flagsA);
    wU16(REC + 0x12, ctx.flagsB);
    // attacker container -> borg sub-object
    wU32(ATT + 0x90, ATTB);
    encodeActor(ATTB, attacker, 0, ATT);
    // defender: param_3 IS the borg
    encodeActor(DEF, defender, 1, null);
    wU32(DEF + 0x90, 0);
    wU32(DEF + 0x4ac, DESC);
    wU16(DEF + 0x59c, ctx.victimResistanceMask ?? 0);
    wU32(DEF + 0x5e0, ctx.victimSpawnProtection ? 0x4000000 : 0);
    wU8(DEF + 0x71a, 1);
    wU32(DEF + 0x5a0, ctx.victimStatusImmune ? 1 << 1 : 0);
    const sel = ctx.defenderDefenseCurveSelectors ?? [0, 0, 0];
    wU8(DESC + 0x9c, sel[0] & 0xff);
    wU8(DESC + 0x9d, sel[1] & 0xff);
    wU8(DESC + 0x9e, sel[2] & 0xff);
    // bss live state (slot 0 = attacker, 1 = defender)
    wI16(HP_MIRROR + 0 * 2, attacker.hp);
    wI16(HP_MIRROR + 1 * 2, defender.hp);
    for (const a of [attacker, defender]) {
      wI32(STRUCT34 + a.team * 0x3c + 0x114, 3200);
      wI32(ENERGY + a.team * 4, (32 - a.forceRatioIndex) * 100);
      wU8(STRUCT50 + a.team, a.sideRank & 0xff);
    }
    wU8(STRUCT30 + 0x32, ctx.cpuHalvingEnabled ? 0 : 2);
    wU8(STRUCT34 + 0x1f, 0);
    return ex.zz_003cd5c_(REC, ATT, DEF) | 0;
  }

  function lookupTypeCategory(borgNumber: number): number {
    tally("lookupTypeCategory");
    wU16be(CAT, borgNumber);
    return ex.zz_0066298_(CAT) | 0;
  }

  function applyHpDamage(target: SourceDamageTarget, amount: number): void {
    tally("applyHpDamage");
    wU16(DEF + 0x1c4, target.maxHp);
    wI16(DEF + 0x1c6, target.hp);
    wU8(DEF + 0x83, 0);
    wU8(DEF + 0x4a0, 0);
    wU8(STRUCT34 + 0x1f, 0);
    ex.zz_003d344_(DEF, amount);
    // The ROM writes pre-subtract HP to +0x1c8 and the clamped HP to +0x1c6;
    // ROM semantics: HP==0 is a no-op, including the prevHp mirror.
    const before = target.hp;
    const after = dv.getInt16(DEF + 0x1c6, true);
    if (before !== 0) {
      target.prevHp = dv.getInt16(DEF + 0x1c8, true);
      target.hp = after;
    }
  }

  return {
    computeBaseDamage,
    lookupTypeCategory,
    applyHpDamage,
    shimCounts: memCtx.counts,
    callCounts,
    memoryInfo,
  };
}
