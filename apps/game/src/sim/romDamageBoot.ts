// romDamageBoot.ts — boot the ported GameCube damage unit into the live game.
//
// Fetches the oracle-verified damage-core wasm + DOL arena (apps/game/public/rom/),
// runs a fidelity gate — the wasm and the TS port must agree on a spread of real
// inputs BEFORE the swap — and only then installs the ROM implementation into
// sourceDamage's override seam. From that moment every damage computation in the
// game runs the ROM's own compiled code.
//
// FAILURE MODE (decided 2026-08-29; docs/playable-port-design.md §"Stage C — Play").
// The design states this unit's integration pattern verbatim as
//
//     ... -> boot-time fidelity gate (wasm vs TS on the real input domain) ->
//     live, WITH FALLBACK TO TS ON ANY FAILURE -> production smoke asserts the
//     ROM path served play.
//
// so a boot failure runs DEGRADED, not hard-failed: the TS port is the very
// reference the wasm is gated against (byte-exact over 26,232 replayed oracle
// cases), so the game stays correct-by-the-reference and a single bad asset
// cannot become a total product outage. What a failure loses is the CLAIM that
// the ROM's own compiled code served the session — and that claim is the thing
// the design makes the production smoke responsible for.
//
// What was wrong before was never the fallback; it was the SILENCE. A 404'd
// wasm in a player build downgraded the core forever behind one console.warn.
// So the degraded state is now a first-class, published fact:
//
//   * `window.__romDamageStatus`               — machine-readable status object
//   * `document.documentElement.dataset.gfRomDamage` — "booting" | the state id
//   * a persistent on-screen badge (main.ts)   — a human cannot miss it
//   * `console.error` on a real failure        — the browser smoke treats any
//                                                console.error as fatal, so the
//                                                gate the design names actually
//                                                fires.
//
// `window.__romDamage` keeps its ORIGINAL contract untouched: it is set if and
// only if the ROM core is installed and serving, so `Boolean(window.__romDamage)`
// remains the single source of truth for "the ROM path is live".
//
// Default ON (the 1:1 port is the product); `?romwasm=0` is the deliberate
// operator opt-out and is reported as its own state, never as a failure.

import {
  computeBaseDamage as tsComputeBaseDamage,
  lookupTypeCategory as tsLookupTypeCategory,
  applyHpDamage as tsApplyHpDamage,
  defaultSourceDamageActor,
  defaultSourceDamageContext,
  setRomDamageImplementation,
  sourceDamageCurveCounts,
  type SourceDamageActor,
  type SourceDamageTarget,
} from "@gf/combat";
import { createRomDamageCore, type RomDamageCore } from "@gf/combat";
import { publicUrl } from "../publicUrl";

/**
 * Which build of the verified unit to fetch (step 8, playable-port-design v5):
 *  - "default": damage-core.wasm — the classic exported-memory build.
 *  - "threads": damage-core.threads.wasm — the threads-target relink
 *    (-sSHARED_MEMORY=1 -sIMPORTED_MEMORY=1), which imports a shared
 *    WebAssembly.Memory and therefore needs cross-origin isolation.
 * Selected by ?romwasm=threads; the default stays the exported-memory module
 * until switching it is a separately reviewed decision.
 */
export type RomWasmVariant = "default" | "threads";

const ROM_WASM_PATH: Record<RomWasmVariant, string> = {
  default: "/rom/damage-core.wasm",
  threads: "/rom/damage-core.threads.wasm",
};

/**
 * Which core is computing damage, as a fact the app publishes rather than a
 * line in the console nobody reads.
 *
 *  - "booting"          the boot is still in flight; nothing decided yet.
 *  - "rom-live"         the ROM's own compiled code is installed and serving.
 *  - "ts-port-forced"   `?romwasm=0`: the operator asked for the TS port. This
 *                       is an expected, deliberate state — NOT a failure.
 *  - "ts-port-degraded" a FAILURE. The ROM core could not be installed (asset
 *                       missing, instantiate threw, or the fidelity gate found
 *                       a divergence) and the session is running on the TS port
 *                       without the ROM-served claim.
 */
export type RomDamageState = "booting" | "rom-live" | "ts-port-forced" | "ts-port-degraded";

export interface RomDamageStatus {
  state: RomDamageState;
  /** True for "rom-live" and nothing else — mirrors `Boolean(window.__romDamage)`. */
  romCoreLive: boolean;
  /** Which wasm build was requested, or null when no boot was attempted. */
  variant: RomWasmVariant | null;
  /** Gate detail, HTTP statuses, or the error text — whatever explains `state`. */
  detail: string;
  /** Memory model of the installed module. Null unless "rom-live". */
  memory: { imported: boolean; shared: boolean } | null;
}

export interface RomDamageBootResult extends RomDamageStatus {
  core?: RomDamageCore;
}

const DATASET_KEY = "gfRomDamage";

let currentStatus: RomDamageStatus = {
  state: "booting",
  romCoreLive: false,
  variant: null,
  detail: "boot not started",
  memory: null,
};

/** Defensive copy of the published status. Never throws, always populated. */
function romDamageStatus(): RomDamageStatus {
  return { ...currentStatus, memory: currentStatus.memory ? { ...currentStatus.memory } : null };
}

/**
 * Publish `status` on every surface at once, so no consumer can observe a
 * stale one: the DOM dataset (assertable without evaluating script), the
 * `window.__romDamageStatus` seam, and the console at the right severity.
 *
 * A degraded state logs `console.error` DELIBERATELY: scripts/smoke-browser-game.mjs
 * fails the run on any console.error, which is what turns "the design says the
 * production smoke is the gate" into a gate that actually fires.
 */
function publish(status: RomDamageStatus): RomDamageStatus {
  currentStatus = status;
  const root = globalThis.document?.documentElement;
  if (root) root.dataset[DATASET_KEY] = status.state;
  (globalThis as Record<string, unknown>).__romDamageStatus = romDamageStatus();
  if (status.state === "ts-port-degraded") {
    console.error(
      `[rom-wasm] DEGRADED — the ROM damage core is NOT serving this session; ` +
        `damage is being computed by the TS port instead: ${status.detail}`,
    );
  } else if (status.state === "ts-port-forced") {
    console.info(`[rom-wasm] TS port active by request (?romwasm=0) — ${status.detail}`);
  }
  return status;
}

// Mark the seam as undecided the moment this module is imported, so "the boot
// has not answered yet" is distinguishable from "the boot answered badly".
publish(currentStatus);

/** The `?romwasm` values that select something real. */
const ROM_WASM_FLAGS = ["0", "1", "default", "threads"] as const;
type RomWasmFlag = (typeof ROM_WASM_FLAGS)[number];

function isRomWasmFlag(value: string): value is RomWasmFlag {
  return (ROM_WASM_FLAGS as readonly string[]).includes(value);
}

/**
 * Resolve `?romwasm=<flag>` into a boot decision.
 *
 * A typo'd flag is REJECTED rather than silently treated as the default: a
 * debug switch that quietly does nothing is worse than no switch, because the
 * operator reads the resulting run as if the switch had applied. "1" and
 * "default" both name the exported-memory build (the historical alias, cited
 * in packages/combat wasmDamageCore.ts).
 */
function resolveRomWasmFlag(raw: string | null): { boot: boolean; variant: RomWasmVariant } {
  if (raw === null) return { boot: true, variant: "default" };
  if (!isRomWasmFlag(raw)) {
    throw new Error(
      `unknown ?romwasm value ${JSON.stringify(raw)} — expected one of ${ROM_WASM_FLAGS.join(", ")}`,
    );
  }
  if (raw === "0") return { boot: false, variant: "default" };
  return { boot: true, variant: raw === "threads" ? "threads" : "default" };
}

/** Deterministic PRNG so the fidelity gate checks the same cases every boot. */
function mulberry32(seed: number): () => number {
  let a = seed >>> 0;
  return () => {
    a = (a + 0x6d2b79f5) >>> 0;
    let t = a;
    t = Math.imul(t ^ (t >>> 15), t | 1);
    t ^= t + Math.imul(t ^ (t >>> 7), t | 61);
    return ((t ^ (t >>> 14)) >>> 0) / 4294967296;
  };
}

// Real borg domain (DOL remap table 0x802f2e28 row lengths, family 0..15). The
// wasm reads the contiguous DOL rows, so an out-of-domain variant over-reads
// into the NEXT family's row while the TS port clamps to 0 — a divergence that
// exists only for borgs that don't exist. The oracle's own exhaustive category
// test was these same 232 real pairs.
const REMAP_ROW_LEN = [14, 12, 16, 14, 14, 24, 44, 14, 16, 14, 12, 8, 8, 8, 6, 8];
function randBorgNumber(rnd: () => number): number {
  const family = Math.floor(rnd() * 16);
  const variant = Math.floor(rnd() * REMAP_ROW_LEN[family]!);
  return (family << 8) | variant;
}

function randActor(rnd: () => number): SourceDamageActor {
  const a = defaultSourceDamageActor(randBorgNumber(rnd));
  a.team = Math.floor(rnd() * 4);
  a.heroFlag = rnd() < 0.5 ? 0 : 1;
  a.pairAttack = rnd() < 0.15 ? 1 : 0;
  a.power = 1;
  a.maxHp = 100 + Math.floor(rnd() * 190);
  a.hp = 1 + Math.floor(rnd() * a.maxHp);
  a.handicap = Math.floor(rnd() * 7);
  a.comboRank = Math.floor(rnd() * 8);
  a.forceRatioIndex = Math.floor(rnd() * 32);
  a.sideRank = Math.floor(rnd() * 32);
  return a;
}

/** wasm vs TS on `n` deterministic cases; any disagreement blocks the swap. */
function fidelityGate(core: RomDamageCore, n: number): { ok: boolean; detail: string } {
  const rnd = mulberry32(0x6f42);
  const counts = sourceDamageCurveCounts();
  for (let i = 0; i < n; i++) {
    const att = randActor(rnd);
    const def = randActor(rnd);
    // Side energy and side rank are PER-TEAM bss slots (one value per team):
    // same-team actors must agree, or the wasm reads the shared slot while the
    // TS port reads each actor's own field — an impossible in-game input.
    if (att.team === def.team) {
      def.forceRatioIndex = att.forceRatioIndex;
      def.sideRank = att.sideRank;
    }
    const heroA = att.heroFlag ? 1 : 0;
    const heroD = def.heroFlag ? 1 : 0;
    const ctx = {
      ...defaultSourceDamageContext(),
      flagsA: rnd() < 0.2 ? 0x1000 : 0,
      flagsB: rnd() < 0.2 ? 0x4000 : 0,
      attackerHpCurveIndex: Math.floor(rnd() * counts.attHp[heroA]!),
      attackerForceCurveIndex: Math.floor(rnd() * counts.attForce[heroA]!),
      defenderDefenseCurveSelectors: [
        Math.floor(rnd() * counts.defRank[heroD]!),
        Math.floor(rnd() * counts.defHp[heroD]!),
        Math.floor(rnd() * counts.defForce[heroD]!),
      ] as [number, number, number],
      cpuHalvingEnabled: rnd() < 0.5,
    };
    // Cover FRACTIONAL basePower, not just integers: in real combat
    // combat.ts forms basePower as record.hpDamage * damageScale, and
    // damageScale is routinely fractional (combo steps 1.08/1.22, charge tiers,
    // projectile scales). An integer-only gate would certify wasm==TS while they
    // diverge on exactly the inputs that occur in play (the ROM record field is
    // u16, so the fraction is truncated on hardware and in the wasm).
    const scale = [1, 1, 1.08, 1.22, 0.5, 1.5][Math.floor(rnd() * 6)]!;
    const basePower = (1 + Math.floor(rnd() * 400)) * scale;
    const w = core.computeBaseDamage(att, def, basePower, ctx);
    const t = tsComputeBaseDamage(att, def, basePower, ctx);
    if (w !== t) {
      return { ok: false, detail: `computeBaseDamage diverged on case ${i}: wasm=${w} ts=${t}` };
    }
    const cat = randBorgNumber(rnd);
    if (core.lookupTypeCategory(cat) !== tsLookupTypeCategory(cat)) {
      return { ok: false, detail: `lookupTypeCategory diverged on 0x${cat.toString(16)}` };
    }
    const hpT: SourceDamageTarget = { hp: att.hp, maxHp: att.maxHp };
    const hpW: SourceDamageTarget = { hp: att.hp, maxHp: att.maxHp };
    const amount = Math.floor(rnd() * 300) - 20;
    tsApplyHpDamage(hpT, amount);
    core.applyHpDamage(hpW, amount);
    if (hpT.hp !== hpW.hp || hpT.prevHp !== hpW.prevHp) {
      return {
        ok: false,
        detail: `applyHpDamage diverged on case ${i}: wasm=${hpW.hp}/${hpW.prevHp} ts=${hpT.hp}/${hpT.prevHp}`,
      };
    }
  }
  return { ok: true, detail: `${n} cases agreed across all three functions` };
}

function degraded(variant: RomWasmVariant, detail: string): RomDamageStatus {
  return publish({ state: "ts-port-degraded", romCoreLive: false, variant, detail, memory: null });
}

/**
 * Honour `?romwasm=<flag>`: either boot the ROM damage core, or record the
 * deliberate TS-port opt-out. Never throws — every outcome is published as a
 * status instead, including a rejected flag (which degrades rather than
 * silently pretending the switch selected the default).
 */
export async function installRomDamageCore(
  rawFlag: string | null,
  fidelityCases = 256,
): Promise<RomDamageBootResult> {
  let decision: { boot: boolean; variant: RomWasmVariant };
  try {
    decision = resolveRomWasmFlag(rawFlag);
  } catch (error) {
    return degraded("default", error instanceof Error ? error.message : String(error));
  }
  if (!decision.boot) {
    return publish({
      state: "ts-port-forced",
      romCoreLive: false,
      variant: null,
      detail: "?romwasm=0 — the ROM damage core was not booted",
      memory: null,
    });
  }
  return bootRomDamage(fidelityCases, decision.variant);
}

/**
 * Fetch, instantiate, fidelity-check, and install the ROM damage core.
 * Never throws: a failure publishes "ts-port-degraded" and leaves the TS
 * implementation active (see the FAILURE MODE note at the top of this file).
 */
async function bootRomDamage(
  fidelityCases: number,
  variant: RomWasmVariant,
): Promise<RomDamageBootResult> {
  try {
    const [wasmRes, arenaRes] = await Promise.all([
      fetch(publicUrl(ROM_WASM_PATH[variant])),
      fetch(publicUrl("/rom/arena.json")),
    ]);
    if (!wasmRes.ok || !arenaRes.ok) {
      return degraded(
        variant,
        `rom assets unavailable (${ROM_WASM_PATH[variant]} -> ${wasmRes.status}, /rom/arena.json -> ${arenaRes.status})`,
      );
    }
    const core = await createRomDamageCore(await wasmRes.arrayBuffer(), await arenaRes.json());
    const gate = fidelityGate(core, fidelityCases);
    if (!gate.ok) {
      return { ...degraded(variant, `fidelity gate FAILED: ${gate.detail}`), core };
    }
    setRomDamageImplementation(core);
    // Expose for proof/diagnostics: window.__romDamage.callCounts shows the ROM
    // path serving real gameplay (smoke scripts and humans both read this);
    // __romDamage.memoryInfo proves which memory model the module linked with.
    // CONTRACT: this global exists if and only if the ROM core is installed.
    (globalThis as Record<string, unknown>).__romDamage = core;
    const mem = core.memoryInfo;
    console.info(
      `[rom-wasm] damage-core LIVE (${variant}: memory ${mem.imported ? "imported" : "exported"}${mem.shared ? " shared" : ""}) — ${gate.detail}`,
    );
    return {
      ...publish({
        state: "rom-live",
        romCoreLive: true,
        variant,
        detail: `${variant}: ${gate.detail}`,
        memory: { imported: mem.imported, shared: mem.shared },
      }),
      core,
    };
  } catch (error) {
    return degraded(variant, error instanceof Error ? `${error.name}: ${error.message}` : String(error));
  }
}
