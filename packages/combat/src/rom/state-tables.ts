// ROM-faithful state tables — port of PTR_LAB_802d36a8 (full body, indexed by +0x5da)
// and PTR_LAB_802d37a8 (upper body, indexed by +0x5db). Each entry is a per-state
// per-frame handler invoked by `FUN_80055568` (chunk_0006.c:7778 → stepActor).
//
// Handler addresses dumped from boot.dol (0x802d36a8 / 0x802d37a8); classification
// sourced from chunk_0007.c / chunk_0008.c corpus read. Constants read from boot.dol.
//
// STATUS: every state has at least a stub. The COMMON shape (stream-tick + optional
// physics + optional transition) is fully ported via factories; unique "custom"
// handlers are marked TODO and currently fall back to their closest-matching factory
// (so the dispatch table is complete and exercises the right stream mask / yaw source
// even before the unique logic lands).

import type { RomActor } from "./actor.js";
import { dispatchUpperBodyCue, dispatchFullBodyCue, runState61 } from "./dispatch.js";
import { integratePhysics } from "./physics.js";
import { startStream, tickStream, type StreamContext } from "./stream-vm.js";
import { romGroundIdleReturn } from "../families/shared-idle-return.js";

// Decoded from boot.dol this session.
export const ROM_STATE_FLOAT = {
  STREAM_RATE: -1.0,        // FLOAT_804374e8 — default action-stream playback rate
  AIM_GRAVITY: 1.0,         // FLOAT_80437510 — gravity during aim/upper-body states
  HALT_INVULN_A: 30.0,      // FLOAT_80437558 — FB76 invuln timer when +0x6cb==1
  HALT_INVULN_B: 60.0,      // FLOAT_80437564 — FB76 invuln timer otherwise
} as const;

export type StateHandler = (actor: RomActor, ctx: StreamContext) => void;

// ============================================================================
// Handler factories — the common shapes the corpus repeats across states.
// ============================================================================

/** The no-op handler (0x8005f238 = bare `blr`). The default for unused slots. */
export const noopHandler: StateHandler = (_a, _c) => {
  /* bare return */
};

/**
 * Factory for the common "tick part-mask stream" shape (FUN_8005f23c family).
 * On first entry (fbPhaseSlot==0) it starts the stream; per-frame it ticks.
 * The first-entry guard reads the part-state block's "stream-active" flags
 * (+0x1cec/+0x1ced/+0x1cee for mask 0xd, +0x1d0c/+0x1d0d/+0x1d0e for mask 0x2).
 */
export function tickStreamHandler(
  mask: number,
  group: number = 0,
  slot: number = 0,
  phaseSlotIndex: 0 | 1 | 2 | 3 = 0,
): StateHandler {
  return (actor, ctx) => {
    const part = actor.parts[phaseSlotIndex]!;
    if (part.active === 0) {
      startStream(actor, mask, group, slot, ROM_STATE_FLOAT.STREAM_RATE);
    } else {
      tickStream(actor, mask, ctx);
    }
  };
}

/**
 * Factory for "tick stream + integrate physics + optional cue transition" — the
 * shape shared by aim/move/guard upper-body states (0x8005fecc, 0x80061338, etc.).
 *
 * On entry: start the stream. Per-frame: tick the stream, run FUN_80067310 with the
 * given gravity + yaw source, decay the +0x568 attack-window timer; when it hits 0
 * dispatch `transitionCue` (via dispatchUpperBodyCue — callers select UB/FB).
 */
export function tickStreamWithPhysicsHandler(
  mask: number,
  slot: number,
  gravity: number,
  yawSource: "lockYaw" | "heading" | "activeYaw",
  opts: {
    phaseSlotIndex?: 0 | 1 | 2 | 3;
    attackWindowTimer?: number;
    transitionCue?: number;
    transitionKind?: "upperBody" | "fullBody";
  } = {},
): StateHandler {
  const phaseSlotIndex = opts.phaseSlotIndex ?? 1; // upper-body states use +0x544 (slot 1)
  return (actor, ctx) => {
    const part = actor.parts[phaseSlotIndex]!;
    const aw = actor as RomActor & { attackWindow?: number };
    if (part.active === 0) {
      startStream(actor, mask, 0, slot, ROM_STATE_FLOAT.STREAM_RATE);
      if (opts.attackWindowTimer !== undefined) aw.attackWindow = opts.attackWindowTimer;
    } else {
      tickStream(actor, mask, ctx);
      const yaw =
        yawSource === "lockYaw" ? actor.lockYaw : yawSource === "heading" ? actor.heading : actor.activeYaw;
      integratePhysics(gravity, actor, yaw);
      if (opts.transitionCue !== undefined && aw.attackWindow !== undefined) {
        aw.attackWindow -= actor.dt;
        if (aw.attackWindow <= 0) {
          if (opts.transitionKind === "fullBody") dispatchFullBodyCue(actor, opts.transitionCue);
          else dispatchUpperBodyCue(actor, opts.transitionCue);
        }
      }
    }
  };
}

/** Factory for the immediate-cue-transition handlers (FUN_80060c48 / 0x80062b1c). */
export function transitionHandler(cueId: number, kind: "upperBody" | "fullBody" = "upperBody"): StateHandler {
  return (actor) => {
    if (kind === "fullBody") dispatchFullBodyCue(actor, cueId);
    else dispatchUpperBodyCue(actor, cueId);
  };
}

// ============================================================================
// Custom handlers — unique logic per state. Ported incrementally; stubs below fall
// back to the closest factory shape so the table is complete.
// ============================================================================

/** FB47 / 0x80065cb4 — vtable dispatch at actor+0x4e4 (mirrors state 61's +0x4b4).
 *  Used by tag-team/partner states. */
function fb47Handler(actor: RomActor, ctx: StreamContext): void {
  const vt = (actor as RomActor & { vtableE4?: ((a: RomActor) => void) | null }).vtableE4;
  if (vt) {
    vt(actor);
  } else {
    // No-callback fallback: zz_006a838_ — engine halt/reset path.
    dispatchFullBodyCue(actor, 0);
  }
  void ctx;
}

/** FB76 / 0x80060b60 — full-body halt: stops the actor, sets invuln timer, clears
 *  velocity, dispatches idle. */
function fb76HaltHandler(actor: RomActor, ctx: StreamContext): void {
  tickStream(actor, 0xf, ctx);
  const flyer = (actor as RomActor & { flyer?: boolean }).flyer === true;
  const inv = actor as RomActor & { invulnTimer?: number };
  inv.invulnTimer = flyer ? ROM_STATE_FLOAT.HALT_INVULN_B : ROM_STATE_FLOAT.HALT_INVULN_A;
  actor.hSpeed = 0;
  actor.yVel = 0;
  actor.hDecel = 0;
  actor.gravityCoeff = 0;
  // zz_006a474_ — stop/land tail (decomp-verified: upper cue 0 only + velocity
  // zeroing; shared-idle-return.ts — the old full-0 + upper-6 mapping was refuted).
  romGroundIdleReturn(actor);
}

// ============================================================================
// The tables. Indexed by state value (0..63). Mirrors the boot.dol pointer tables.
// Entries marked TODO(port) are stubs that match the stream-mask + yaw source from
// the corpus decode but defer the unique constants/branches.
// ============================================================================

function buildFullBodyTable(): StateHandler[] {
  const t: StateHandler[] = new Array(80).fill(noopHandler);
  // [0] noop idle
  t[1] = tickStreamHandler(0xd, 0, 0, 0);
  t[2] = tickStreamHandler(0xd, 0, 1, 0);
  t[3] = tickStreamHandler(0xd, 0, 0, 0);
  t[4] = tickStreamHandler(0xd, 0, 0x1f, 0);
  t[5] = tickStreamHandler(0xd, 0, 2, 0);
  // [6] slot = +0x5e7+4 (per-borg byte) — TODO(port) read actor byte
  // [7] slot branches by +0x590 — TODO(port)
  t[8] = tickStreamHandler(0xd, 0, 8, 0);
  // [9] phaseMachine(3, mask 0xd) — TODO(port)
  t[13] = tickStreamHandler(0xd, 0, 0, 0); // slot = +0x57c+0x1b — TODO
  t[14] = tickStreamHandler(0xd, 0, 0, 0);
  t[15] = tickStreamHandler(0xd, 0, 0, 0);
  t[16] = tickStreamHandler(0xd, 0, 10, 0);
  t[17] = tickStreamHandler(0xd, 0, 0xb, 0);
  t[18] = tickStreamHandler(0xd, 0, 0xc, 0);
  t[22] = tickStreamHandler(0xd, 0, 0, 0);
  // [23] phaseMachine(2 starts, mask 0xd) — TODO(port)
  t[24] = tickStreamHandler(0xd, 0, 0x22, 0);
  t[25] = t[2]!; // tailcall → state 2
  t[26] = t[3]!; // → state 3
  t[27] = t[4]!; // → state 4
  t[28] = t[13]!; // → state 13
  t[29] = t[14]!; // → state 14
  t[30] = t[15]!; // → state 15
  t[40] = tickStreamHandler(0xd, 0, 10, 0);
  t[41] = tickStreamHandler(0xd, 0, 0xb, 0);
  t[42] = tickStreamHandler(0xd, 0, 0xc, 0);
  t[44] = tickStreamHandler(0xd, 0, 0, 0);
  t[45] = tickStreamHandler(0xd, 0, 0, 0);
  t[46] = tickStreamHandler(0xd, 0, 0, 0);
  t[47] = fb47Handler;
  // [56] phaseMachine(2 starts, mask 0xd) — TODO(port)
  t[61] = (a, _c) => runState61(a);
  t[62] = noopHandler;
  t[63] = noopHandler;
  t[65] = tickStreamHandler(0x2, 0, 0, 1);
  // [66-79] mask-2 upper-body mirrors — ported as the UB table below (these are aliases)
  t[76] = fb76HaltHandler;
  return t;
}

function buildUpperBodyTable(): StateHandler[] {
  const t: StateHandler[] = new Array(71).fill(noopHandler);
  // [0] noop
  t[1] = tickStreamHandler(0x2, 0, 0, 1);
  // [2-15] custom mask-2 active-tick handlers (attack-windup, aim, guard) — TODO(port)
  //       stubbed with tickStreamWithPhysics so dispatch + integration both run.
  for (let s = 2; s <= 15; s++) {
    t[s] = tickStreamWithPhysicsHandler(0x2, 0, ROM_STATE_FLOAT.AIM_GRAVITY, "lockYaw", { phaseSlotIndex: 1 });
  }
  t[6] = tickStreamWithPhysicsHandler(0x2, 0, ROM_STATE_FLOAT.AIM_GRAVITY, "lockYaw", {
    phaseSlotIndex: 1, attackWindowTimer: 0, transitionCue: 6, transitionKind: "upperBody",
  });
  t[16] = tickStreamWithPhysicsHandler(0x2, 10, ROM_STATE_FLOAT.AIM_GRAVITY, "lockYaw", {
    phaseSlotIndex: 1, transitionCue: 0x10, transitionKind: "upperBody",
  });
  t[17] = tickStreamWithPhysicsHandler(0x2, 0xb, ROM_STATE_FLOAT.AIM_GRAVITY, "heading", {
    phaseSlotIndex: 1, transitionCue: 0x11, transitionKind: "upperBody",
  });
  // [18-21] custom aim/yaw/guard — TODO(port); stubbed.
  for (let s = 18; s <= 21; s++) {
    t[s] = tickStreamWithPhysicsHandler(0x2, 0, ROM_STATE_FLOAT.AIM_GRAVITY, "lockYaw", { phaseSlotIndex: 1 });
  }
  t[22] = tickStreamWithPhysicsHandler(0x2, 0, ROM_STATE_FLOAT.AIM_GRAVITY, "activeYaw", { phaseSlotIndex: 1 });
  for (let s = 23; s <= 31; s++) {
    t[s] = tickStreamWithPhysicsHandler(0x2, 0, ROM_STATE_FLOAT.AIM_GRAVITY, "lockYaw", { phaseSlotIndex: 1 });
  }
  // [32, 48, 57, 58, 59] partner/phase machines — TODO(port)
  for (let s = 32; s <= 60; s++) {
    if (!t[s]) t[s] = tickStreamWithPhysicsHandler(0x2, 0, ROM_STATE_FLOAT.AIM_GRAVITY, "lockYaw", { phaseSlotIndex: 1 });
  }
  t[44] = transitionHandler(0xd);
  t[60] = tickStreamHandler(0xf, 0, 0, 1);
  t[62] = (a, _c) => {
    // zz_005c694_ — TODO(port): the camera/lock-update helper. Stubbed to noop.
    void a;
  };
  t[63] = (a, _c) => {
    // zz_005bccc_ — TODO(port): the death state handler. Stubbed to noop.
    void a;
  };
  // [64-70] unverifiable from corpus (inside FUN_80060864 range); stubbed noop.
  return t;
}

/** Build the complete state-table pair consumed by `stepActor`. */
export function createRomStateTables(): { fullBody: StateHandler[]; upperBody: StateHandler[] } {
  return { fullBody: buildFullBodyTable(), upperBody: buildUpperBodyTable() };
}

/** Re-export of the stepActor signature with the ROM state tables wired. */
export function stepRomActor(actor: RomActor, tables: ReturnType<typeof createRomStateTables>, ctx: StreamContext): void {
  actor.preState?.(actor);
  const ub = tables.upperBody[actor.ubState];
  if (ub) ub(actor, ctx);
  const fb = tables.fullBody[actor.fbState];
  if (fb) fb(actor, ctx);
  actor.postState?.(actor);
}
