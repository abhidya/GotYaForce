// Bridge between the existing @gf/combat `BorgRuntime` (the canonical game state —
// HP, lock-on, ammo, gauges, status, projectiles, results telemetry) and the ROM
// `RomActor` runtime (the 1:1 ported state machine). The existing layer stays
// authoritative for everything EXCEPT the action/motion that a ported ROM family
// owns; the bridge syncs fields both ways each frame.
//
// INTEGRATION (3 lines, minimal surgery on the existing code):
//   battle.ts  before stepMovement/stepAttacks:
//     if (b.romDriver?.tick(b, dt, all, ctx)) continue;   // ROM owned this frame
//   combat.ts  X-special branch, before spawnSpecialProjectiles:
//     if (b.romDriver?.tryStartXSpecial(b, all, ctx)) return { projectiles: out };
//
// BorgRuntime keeps its vec3 `vel` model; RomActor uses the ROM's scalar hSpeed +
// yVel model. The bridge decomposes/recomposes each sync.

import type { BorgRuntime } from "./types.js";
import type { Vec3 } from "@gf/physics";
import type { RomActor } from "./rom/actor.js";
import { createRomActor } from "./rom/actor.js";
import {
  createRomStateTables,
  stepRomActor,
  type StateHandler,
} from "./rom/state-tables.js";
import type { StreamContext } from "./rom/stream-vm.js";
import {
  dispatchCommandRecord,
  dispatchUpperBodyCue,
  dispatchFullBodyCue,
} from "./rom/dispatch.js";
import { configureGRedFamily, type GRedFamilyCtx } from "./families/gred.js";
import { configureNinjaFamily } from "./families/ninja.js";
import { createSharedEngineRootAction, DEFAULT_CONFIGS } from "./families/shared-engine.js";
import { spawnRomProjectile } from "./projectiles.js";
import type { Projectile } from "./types.js";
import attackHitTablesData from "./data/attackHitTables.json" with { type: "json" };
import actionStreamTablesData from "./data/actionStreamTables.json" with { type: "json" };
import meleeAnimKindsData from "./data/meleeAnimKinds.json" with { type: "json" };
import familyCueTablesFullData from "./data/familyCueTablesFull.json" with { type: "json" };

const TAU = Math.PI * 2;
const BAM_FULL = 0x10000;

/** An armed hitbox window (from attackHitTables.json, looked up per kind). */
interface ArmedHit {
  activeStart: number;
  activeEnd: number;
  reach: number;
  damageRecordIndex: number;
  /** Uids already struck by this window (one hit per target per window). */
  struck: Set<string>;
}

// Lazy-loaded per-borg hit-table data (attackHitTables.json). Loaded once, cached.
const HIT_TABLES: Record<string, { kinds: Record<string, number[]>; records: Record<string, unknown> }> =
  (attackHitTablesData as { borgs: Record<string, { kinds: Record<string, number[]>; records: Record<string, unknown> }> }).borgs;
function hitTablesFor(borgId: string): { kinds: Record<string, number[]>; records: Record<string, unknown> } | null {
  return HIT_TABLES[borgId] ?? null;
}

// --- Pre-decoded stream events (meleeAnimKinds.json) ---
// The stream banks' bytecode is already decoded into frame-keyed events by
// scripts/gen-melee-anim-kinds.mjs. The bridge plays these back directly, bypassing
// the raw bytecode walker when familyStreamBank is null (which it is for all families
// until the bank-byte extractor lands). This gives every family working anim + hitbox
// arming from the ALREADY-DECODED data.

interface StreamEvent {
  op: string;
  frame?: number;
  kind?: number;
  statusId?: number;
  statusArg?: number;
  group?: number;
  slot?: number;
  mode?: number;
  blend?: boolean;
}

const ACTION_STREAM_BANKS: Record<string, { bank: string; group: number; seedSlot: number } | undefined> = (() => {
  const data = actionStreamTablesData as unknown as { borgs: Record<string, { actions: Record<string, { variants: Record<string, { bank: string; group: number; seedSlot: number } | undefined> }> }> };
  const out: Record<string, { bank: string; group: number; seedSlot: number } | undefined> = {};
  for (const [borgId, b] of Object.entries(data.borgs || {})) {
    const xLeaf = b.actions?.["2"]?.variants?.["0"];
    if (xLeaf) out[borgId] = { bank: xLeaf.bank, group: xLeaf.group, seedSlot: xLeaf.seedSlot ?? 0 };
  }
  return out;
})();

// eslint-disable-next-line @typescript-eslint/no-explicit-any
const MELEE_ANIM_BANKS: Record<string, any> = (meleeAnimKindsData as { banks?: Record<string, unknown> }).banks ?? {};

/** Look up the pre-decoded stream events for a borg's X-special. Returns null when
 *  the borg has no decoded action-stream data (uncommon — 156/208 borgs have it). */
function streamEventsFor(borgId: string): StreamEvent[] | null {
  const meta = ACTION_STREAM_BANKS[borgId];
  if (!meta) return null;
  const bank = MELEE_ANIM_BANKS[meta.bank];
  if (!bank) return null;
  // eslint-disable-next-line @typescript-eslint/no-explicit-any
  const group = bank.groups?.["g" + meta.group] as any;
  const slot = group?.["s" + meta.seedSlot] as { events?: StreamEvent[] } | undefined;
  return slot?.events ?? null;
}

/** BorgRuntime.rotY is in radians (atan2(x,z) convention, +Z forward); RomActor.heading
 *  is BAM16 (0..0xFFFF, 0 = +Z forward). */
function radToBam(rad: number): number {
  let bam = Math.round((rad / TAU) * BAM_FULL);
  bam &= 0xffff;
  if (bam >= 0x8000) bam -= 0x10000;
  return bam;
}
function bamToRad(bam: number): number {
  let s = bam & 0xffff;
  if (s & 0x8000) s -= 0x10000;
  return (s / BAM_FULL) * TAU;
}

/** Decompose BorgRuntime.vel (vec3) into RomActor's scalar hSpeed + yVel model. */
function decomposeVel(vel: Vec3): { hSpeed: number; yVel: number } {
  return { hSpeed: Math.hypot(vel.x, vel.z), yVel: vel.y };
}
/** Recompose RomActor's hSpeed (yaw-projected) + yVel back into BorgRuntime.vel. */
function recomposeVel(hSpeed: number, yVel: number, yawBam: number): Vec3 {
  const rad = bamToRad(yawBam);
  // Match physics.ts: pos.x += hSpeed × sin(yaw); pos.z += hSpeed × cos(yaw).
  // The sign of hSpeed carries direction (the ROM allows negative hSpeed for reverse).
  return { x: Math.sin(rad) * hSpeed, y: yVel, z: Math.cos(rad) * hSpeed };
}

/** Per-family registry. Maps borg-id → factory that wires the RomActor + cue table.
 *  Returns null for borgs whose family hasn't been ported yet (they keep the generic
 *  archetype logic). */
export interface FamilyRegistration {
  /** Configure a freshly-created RomActor for this borg-id (sets the family virtual,
   *  stamps the borg-number switch, etc.). */
  configure: (actor: RomActor, ctx: GRedFamilyCtx) => void;
  /** The cue→state table for this family (48 entries × 2 bytes). Extracted from
   *  boot.dol; hardcoded for G RED until the extractor script lands. */
  cueTable: Int8Array;
}

// Lazily built so the cue-table data consts below are initialized first (the
// registrations read cueTableForBorg at construction time).
let FAMILY_REGISTRY_CACHE: Record<string, FamilyRegistration> | null = null;
function familyRegistry(): Record<string, FamilyRegistration> {
  if (!FAMILY_REGISTRY_CACHE) {
    FAMILY_REGISTRY_CACHE = {
      // G RED family (ctor 0x8018ccfc) — cue table @0x80365cf8, full 48-row DOL dump.
      pl0615: makeGRedFamilyRegistration(),
      pl0629: makeGRedFamilyRegistration(),
      pl062a: makeGRedFamilyRegistration(),
      // NORMAL NINJA family (ctor 0x8006f4f8) — cue table @0x802d3ff8. SASUKE (pl000a)
      // shares the entire family: the ctor differs only in the +0x4b0 descriptor.
      pl0000: makeNinjaFamilyRegistration(),
      pl000a: makeNinjaFamilyRegistration(),
    };
  }
  return FAMILY_REGISTRY_CACHE;
}

// ---- Fleet-wide DERIVED cue tables (familyCueTablesFull.json, 2026-07-06) ----
// 119/119 family ctors' 48×2 cue→state tables dumped from boot.dol at each ctor's
// +0x4f0 binding, byte-validated against the two hand-verified dumps (family 0 +
// G RED, nn-family-decode-2026-07-06.md §A11). Rows 44 AND 45 → state 61 in ALL 119
// families (the universal root-action trampoline). Three ctors carry per-borg
// memberOverrides (variant sub-families binding a different table).

interface CueTableFamilyEntry {
  cueTable: string;
  members: string[];
  rows: number[][] | null;
  memberOverrides?: Record<string, { cueTable: string; rows: number[][] | null }>;
}
const CUE_TABLE_FAMILIES = (familyCueTablesFullData as unknown as {
  families: Record<string, CueTableFamilyEntry>;
}).families;

/** borgId → family ctor address (actionStreamTables.json). */
const BORG_CTOR: Record<string, string | undefined> = (() => {
  const data = actionStreamTablesData as unknown as { borgs: Record<string, { constructorAddress?: string }> };
  const out: Record<string, string | undefined> = {};
  for (const [borgId, b] of Object.entries(data.borgs || {})) out[borgId] = b.constructorAddress;
  return out;
})();

/** The borg's REAL ROM cue table (per-borg override → family rows), as the Int8Array
 *  shape dispatch.ts consumes. Null when the borg has no extracted family entry. */
export function cueTableForBorg(borgId: string): Int8Array | null {
  const ctor = BORG_CTOR[borgId];
  if (!ctor) return null;
  const fam = CUE_TABLE_FAMILIES[ctor];
  if (!fam) return null;
  const rows = fam.memberOverrides?.[borgId]?.rows ?? fam.rows;
  if (!rows) return null;
  const t = new Int8Array(96);
  for (let i = 0; i < 48 && i < rows.length; i++) {
    t[i * 2] = rows[i]![0]!;
    t[i * 2 + 1] = rows[i]![1]!;
  }
  return t;
}

function makeGRedFamilyRegistration(): FamilyRegistration {
  return {
    configure: (actor, ctx) => {
      const id = actor.borgNumber === 0x629 ? "pl0629" : actor.borgNumber === 0x62a ? "pl062a" : "pl0615";
      configureGRedFamily(actor, id as "pl0615" | "pl0629" | "pl062a", ctx);
    },
    cueTable: cueTableForBorg("pl0615")!,
  };
}

function makeNinjaFamilyRegistration(): FamilyRegistration {
  return {
    configure: (actor, ctx) => {
      const id = actor.borgNumber === 0x00a ? "pl000a" : "pl0000";
      configureNinjaFamily(actor, id as "pl0000" | "pl000a", ctx);
    },
    cueTable: cueTableForBorg("pl0000")!,
  };
}

/** Returns true if a ROM family driver is registered for this borg-id. With the
 *  shared-engine fallback, borgs with decoded action-stream data also get a driver. */
export function hasRomFamilyDriver(borgId: string): boolean {
  return borgId in familyRegistry() || borgId in ACTION_STREAM_BANKS;
}

function makeDefaultCueTable(): Int8Array {
  const t = new Int8Array(96).fill(-1);
  t[44 * 2] = 61;
  t[44 * 2 + 1] = 0;
  t[7 * 2] = 6;
  t[7 * 2 + 1] = 6;
  return t;
}

/** Host-provided hit resolver — called by the bridge when an armed hitbox's active
 *  window intersects an enemy. The host (battle.ts) implements this using the real
 *  `applyHit` + the profiles map + the damage records + burst/energy context, giving
 *  full damage-formula fidelity without the bridge needing to import the combat stack. */
export type RomHitResolver = (
  attacker: BorgRuntime,
  victim: BorgRuntime,
  damageRecordIndex: number,
  knockbackMult: number,
) => void;

/** Host-provided ground clamp — called after the ROM physics step to snap the borg
 *  to the stage floor. Without this the ROM integrator (no collision awareness) lets
 *  borgs fall through the ground. */
export type RomGroundClamp = (pos: { x: number; y: number; z: number }, velY: number) => { y: number; velY: number; grounded: boolean };

/** The bridge sidecar attached to BorgRuntime (via the `romDriver` field). Owns the
 *  RomActor + state tables + per-frame sync. Activates when a ported family exists. */
export class RomDriverBridge {
  readonly actor: RomActor;
  private readonly tables: { fullBody: StateHandler[]; upperBody: StateHandler[] };
  /** Armed hitbox records for the current special. */
  private armedHits: ArmedHit[] = [];
  private streamFrame = 0;
  /** Pre-decoded stream events from meleeAnimKinds.json. Played back each tick to
   *  drive anim changes + hitbox arming at the decoded ROM frames. */
  private streamEvents: StreamEvent[] | null = null;
  /** Max frames the special runs before auto-completing (from the decoded stream length). */
  private specialMaxFrames = 30;
  private readonly ctx: StreamContext;
  /** Host-provided hit resolver (battle.ts). When null, hits are recorded but no
   *  damage is applied — the bridge logs the connection for debugging. */
  hitResolver: RomHitResolver | null = null;
  /** Host-provided ground clamp (battle.ts). */
  groundClamp: RomGroundClamp | null = null;
  /** Stage bounds for position clamping during the ROM special (prevents drift
   *  to stage edges since stepMovement's bounds clamp is skipped). */
  bounds: { minX: number; maxX: number; minZ: number; maxZ: number } | null = null;
  /** Off-mesh check: returns false when (x,z) has no collision triangle. The bridge
   *  reverts the borg to its pre-step XZ in that case, preventing wall-through drift. */
  offMeshCheck: ((x: number, z: number) => boolean) | null = null;
  /** Projectiles spawned by the ROM stream's fireChild op (op 0x09) during the
   *  current special. Drained by battle.ts after each tick. */
  private pendingProjectiles: Projectile[] = [];

  /** Drain projectiles spawned by the ROM stream's fireChild op. Called by battle.ts
   *  after each romDriver.tick(). */
  drainProjectiles(): Projectile[] {
    const drained = this.pendingProjectiles;
    this.pendingProjectiles = [];
    return drained;
  }
  /** True while the ROM state machine is mid-special. */
  private specialActive = false;
  private runtime: BorgRuntime | null = null;

  private constructor(actor: RomActor, ctx: StreamContext) {
    this.actor = actor;
    this.tables = createRomStateTables();
    // Wrap the host ctx so we can intercept armHit/playAnim for bridge-level bookkeeping.
    const host = ctx;
    const wrapped: StreamContext = {
      onArmHit: (a, kind, statusId, statusArg) => {
        host.onArmHit?.(a, kind, statusId, statusArg);
        this.onArmHit(kind);
      },
      onPlayAnim: (a, group, slot, blend) => {
        host.onPlayAnim?.(a, group, slot, blend);
        this.onPlayAnim(group, slot);
      },
      onFireChild: (a, variant) => {
        host.onFireChild?.(a, variant);
        this.onFireChild(variant);
      },
    };
    if (host.onIndirect) wrapped.onIndirect = host.onIndirect;
    this.ctx = wrapped;
  }

  /** Attach a bridge to a freshly-spawned BorgRuntime. Returns the bridge, or null if
   *  the borg has no ported family (caller keeps generic archetypes). */
  static attach(runtime: BorgRuntime, hostCtx: StreamContext): RomDriverBridge | null {
    const reg = familyRegistry()[runtime.borgId];
    const actor = createRomActor();
    // Every borg gets its REAL family cue table when extracted (119/119 families);
    // the hand-rolled default remains only as a last-resort fallback.
    actor.cueTable = reg?.cueTable ?? cueTableForBorg(runtime.borgId) ?? makeDefaultCueTable();
    if (reg) {
      reg.configure(actor, hostCtx);
    } else {
      const streamMeta = ACTION_STREAM_BANKS[runtime.borgId];
      if (!streamMeta) return null;
      actor.rootAction = createSharedEngineRootAction({
        xSpecial: DEFAULT_CONFIGS.dashAttack(streamMeta.seedSlot ?? 0),
      });
    }
    const bridge = new RomDriverBridge(actor, hostCtx);
    actor.borgNumber = borgIdToNumber(runtime.borgId);
    actor.team = runtime.team;
    return bridge;
  }

  /** Copy BorgRuntime → RomActor (before the ROM step). During an active special,
   *  velocity is NOT synced — the ROM handler owns it (syncIn would overwrite the
   *  phase machine's impulses with stale BorgRuntime.vel from before the special). */
  syncIn(runtime: BorgRuntime, all: readonly BorgRuntime[]): void {
    const a = this.actor;
    a.pos.x = runtime.pos.x;
    a.pos.y = runtime.pos.y;
    a.pos.z = runtime.pos.z;
    a.heading = radToBam(runtime.rotY);
    // Only sync velocity on the FIRST entry frame (specialActive was just set).
    // Subsequent ticks: ROM handler owns velocity; skip the copy.
    if (!this.specialActive) {
      a.lockYaw = a.heading;
      a.activeYaw = a.heading;
      const { hSpeed, yVel } = decomposeVel(runtime.vel);
      a.hSpeed = hSpeed;
      a.yVel = yVel;
    }
    a.dt = 1;
    a.timescale = 1;
    a.tierScale = 1;
    a.maxFall = -9999;
    (a as RomActor & { grounded?: boolean }).grounded = runtime.grounded;
    const lockUid = runtime.lockTarget;
    if (lockUid) {
      const target = all.find((b) => b.uid === lockUid);
      if (target) {
        (a as RomActor & { lockTarget?: { x: number; y: number; z: number } | null }).lockTarget = {
          x: target.pos.x, y: target.pos.y, z: target.pos.z,
        };
      }
    }
  }

  /** Copy RomActor → BorgRuntime (after the ROM step). */
  syncOut(runtime: BorgRuntime): void {
    const a = this.actor;
    runtime.pos.x = a.pos.x;
    runtime.pos.y = a.pos.y;
    runtime.pos.z = a.pos.z;
    runtime.rotY = bamToRad(a.heading);
    const vel = recomposeVel(a.hSpeed, a.yVel, a.activeYaw);
    runtime.vel.x = vel.x;
    runtime.vel.y = vel.y;
    runtime.vel.z = vel.z;
  }

  /** Called from combat.ts's X-special branch. Returns true if the ROM family handled
   *  the press (caller skips spawnSpecialProjectiles). Arms the multi-frame phase
   *  machine; subsequent `tick` calls advance it. */
  tryStartXSpecial(runtime: BorgRuntime, all: readonly BorgRuntime[]): boolean {
    if (this.specialActive) return false;
    this.runtime = runtime;
    this.armedHits = [];
    this.streamFrame = 0;
    // Load pre-decoded stream events for the choreography (anim + hitbox arming).
    this.streamEvents = streamEventsFor(runtime.borgId);
    // Determine the special's duration from the decoded stream (default 30 frames).
    this.specialMaxFrames = 30;
    if (this.streamEvents) {
      const maxFrame = this.streamEvents.reduce((m, e) => Math.max(m, e.frame ?? 0), 0);
      this.specialMaxFrames = Math.max(this.specialMaxFrames, maxFrame + 5);
    }
    // Fire frame-0 events immediately (armHit + playAnim).
    this.dispatchEvent(0);
    this.streamFrame = 1;
    // Don't change runtime.state/anim — let stepAttacks/stepMovement handle those.
    // The bridge layers hitbox/anim ON TOP of normal movement, not replacing it.
    runtime.cooldowns["romSpecialActive"] = 1;
    this.specialActive = true;
    // For G RED family (custom handler): also run the ROM physics for the launch arc.
    // The custom handler sets velocities that stepMovement will integrate.
    if (this.actor.rootAction) {
      const preX = runtime.pos.x;
      const preZ = runtime.pos.z;
      this.syncIn(runtime, all);
      dispatchCommandRecord(this.actor, { cueId: 44, stateMode: 3, actionIndex: 2, variantIndex: 0 });
      stepRomActor(this.actor, this.tables, this.ctx);
      this.syncOut(runtime);
      // The shared-X blink-away reposition (phase 0's pos += (pos−target)×0.95) can
      // teleport past the arena walls near stage edges — the ROM's own step runs the
      // ground/wall collide (zz_00677b0_) right after; the port applies the host's
      // bounds clamp + off-mesh revert here (same policy tick() documents).
      if (this.bounds) {
        runtime.pos.x = Math.min(this.bounds.maxX, Math.max(this.bounds.minX, runtime.pos.x));
        runtime.pos.z = Math.min(this.bounds.maxZ, Math.max(this.bounds.minZ, runtime.pos.z));
      }
      if (this.offMeshCheck && !this.offMeshCheck(runtime.pos.x, runtime.pos.z)) {
        runtime.pos.x = preX;
        runtime.pos.z = preZ;
      }
    }
    return true;
  }

  /** Called from battle.ts before stepMovement/stepAttacks. Returns true ONLY when the
   *  ROM driver needs to exclusively own the borg's motion (G RED's G Crash fly-up
   *  arc). For shared-engine borgs, returns false — stepMovement + stepAttacks run
   *  normally, and the bridge's tick handles ONLY the stream events (anim/hitbox/damage)
   *  on top. This prevents the AI drift caused by skipping navigation during specials. */
  tick(runtime: BorgRuntime, _dt: number, all: readonly BorgRuntime[]): boolean {
    if (!this.specialActive) return false;
    this.runtime = runtime;
    // Play pre-decoded stream events for this frame (anim + hitbox arming).
    this.dispatchEvent(this.streamFrame);
    this.streamFrame++;
    // Resolve armed hitbox windows against nearby enemies (damage).
    this.resolveHits(runtime, all);
    // Drain any fireChild-spawned projectiles.
    // (battle.ts drains via drainProjectiles after tick returns)
    // Check completion: if the special's frame count exceeded the stream length,
    // end the special. The stream length comes from the decoded anim bank (typically
    // 15-81 frames depending on the move).
    if (this.streamFrame >= this.specialMaxFrames) {
      this.specialActive = false;
      this.armedHits = [];
      this.streamEvents = null;
      runtime.cooldowns["romSpecialActive"] = 0;
      runtime.cooldowns["special"] = 90;
    }
    // Return false → stepMovement + stepAttacks run normally. The bridge's
    // hitbox/anim/damage are layered ON TOP of normal movement, not replacing it.
    return false;
  }

  /** Called by the stream VM when a playAnim op fires. Sets the BorgRuntime's anim
   *  label + meleeAnimStream ref so the renderer (borgPresentationAssets) plays the
   *  decoded (group, slot) clip. For G RED's G Crash this is (4, 0) = g04_s00. */
  private onPlayAnim(group: number, slot: number): void {
    if (this.runtime) {
      this.runtime.anim = "special";
      this.runtime.meleeAnimStream = { group, slot };
    }
  }

  /** Called by the stream VM when an armHit op fires. Looks up the kind's hit records
   *  from attackHitTables.json and arms them — each record carries its active window
   *  (frame range), reach, and damage record. The bridge checks them each tick. */
  private onArmHit(kind: number): void {
    if (!this.runtime) return;
    const tables = hitTablesFor(this.runtime.borgId);
    if (!tables) return;
    const recordIndices = tables.kinds[String(kind)];
    if (!recordIndices) return;
    this.armedHits = recordIndices.map((idx) => {
      const rec = tables.records[String(idx)] as {
        activeStart: number; activeEnd: number; halfExtent: number[]; damageRecordIndex: number;
      } | undefined;
      if (!rec) return null;
      return {
        activeStart: rec.activeStart,
        activeEnd: rec.activeEnd,
        reach: rec.halfExtent?.[0] ?? 50,
        damageRecordIndex: rec.damageRecordIndex,
        struck: new Set<string>(),
      } satisfies ArmedHit;
    }).filter((h): h is ArmedHit => h !== null);
    this.streamFrame = 0;
  }

  /** Called by the stream VM when a fireChild op (0x09) fires. Spawns a ROM-data-driven
   *  projectile using the decoded variant table (DAT_802f3dda). The projectile gets
   *  real speed/drop/lifetime from the variant, replacing the TUNED spawnSpecialProjectiles
   *  path. Collected in pendingProjectiles; battle.ts drains them after tick. */
  private onFireChild(variant: number): void {
    if (!this.runtime) return;
    const yawRad = (this.actor.activeYaw / 0x10000) * Math.PI * 2;
    const proj = spawnRomProjectile(this.runtime, variant, yawRad);
    if (proj) this.pendingProjectiles.push(proj);
  }

  /** Fire any stream events scheduled for the given frame (from meleeAnimKinds.json).
   *  This drives the anim + hitbox arming at the exact ROM frame numbers, bypassing
   *  the raw bytecode walker when the bank bytes aren't loaded. */
  private dispatchEvent(frame: number): void {
    if (!this.streamEvents) return;
    for (const ev of this.streamEvents) {
      const evFrame = ev.frame ?? 0;
      if (evFrame !== frame) continue;
      switch (ev.op) {
        case "armHit":
          if (ev.kind !== undefined && ev.kind > 0) {
            this.ctx.onArmHit?.(this.actor, ev.kind, ev.statusId ?? 0, ev.statusArg ?? 255);
          }
          break;
        case "playAnim":
        case "blendAnim":
          if (ev.group !== undefined && ev.slot !== undefined) {
            this.ctx.onPlayAnim?.(this.actor, ev.group, ev.slot, ev.op === "blendAnim");
          }
          break;
      }
    }
  }

  /** Per-frame hit check: if any armed hitbox's active window is live this frame,
   *  resolve hits against nearby enemies via the host's applyHit callback. */
  private resolveHits(runtime: BorgRuntime, all: readonly BorgRuntime[]): void {
    if (this.armedHits.length === 0) return;
    this.streamFrame += 1;
    for (const hit of this.armedHits) {
      if (this.streamFrame < hit.activeStart || this.streamFrame > hit.activeEnd) continue;
      for (const target of all) {
        if (!target.alive || target.team === runtime.team) continue;
        if (hit.struck.has(target.uid)) continue;
        const dx = target.pos.x - runtime.pos.x;
        const dz = target.pos.z - runtime.pos.z;
        const dist = Math.hypot(dx, dz);
        if (dist <= hit.reach) {
          hit.struck.add(target.uid);
          // Route through the host's full applyHit path for damage-formula fidelity.
          if (this.hitResolver) {
            this.hitResolver(runtime, target, hit.damageRecordIndex, 1.0);
          } else {
            // Fallback (no resolver wired): direct HP subtraction so hits are still visible.
            target.hp = Math.max(0, target.hp - 20);
            target.lastHitAttackerTeam = runtime.team;
            target.lastHitAttackerOwner = runtime.ownerPlayer;
          }
        }
      }
    }
  }

  /** Force-clear (e.g. on hit-interrupt). The existing hit reaction will set state to
   *  "hit"/"down" which overrides whatever the ROM driver was doing. */
  interrupt(): void {
    this.specialActive = false;
    this.armedHits = [];
    if (this.actor.fbState === 61) {
      dispatchFullBodyCue(this.actor, 0);
      dispatchUpperBodyCue(this.actor, 6);
    }
  }
}

/** Convert a pl#### borg id to the ROM's internal borg number (the +0x3e8 u16). */
function borgIdToNumber(borgId: string): number {
  const m = /^pl([0-9a-f]{4})$/i.exec(borgId);
  return m ? parseInt(m[1]!, 16) : 0;
}
