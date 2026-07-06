// The ROM's universal idle-return helpers — 1:1 ports of chunk_0009.c.
//
// Every family machine's end-of-move exit funnels into one of these three. The
// valkrie verify pass (commit 7e582ace) proved the earlier per-family
// transcriptions wrong (full-body cue 0 + upper cue 6/7 was a copied convention,
// not decomp fact), so the verified behavior lives here once and family ports
// call these instead of re-transcribing.
//
// Callers are responsible for their own teardown prelude (+0x73f = 0 and/or
// +0x5e0 &= ~3) — the ROM call sites do that before the bl, and the masks below
// intentionally preserve bits 0..1 exactly like the ROM helpers do.
//
// FLOAT_8043762c = 0.0 (the shared zero); FLOAT_80437648 = 30.0 (DOL-read,
// verified during the valkrie batch).

import type { RomActor } from "../rom/actor.js";
import { dispatchUpperBodyCue } from "../rom/dispatch.js";

/** FLOAT_80437648 = 30.0 — the (controlWord & 3) == 3 freeze-release +0x694 floor. */
const KNOCKOUT_TIMER_FLOOR = 30.0;

/** zz_006a474_ @ chunk_0009.c:708-729 — ground idle return.
 *  Masks the control word, zeroes the motion state (+0x44/+0x48/+0x4c/+0x50),
 *  and dispatches upper-body cue 0 ONLY (via zz_006a750_). The +0x1d9c/+0x1db2/
 *  +0x4a1/+0x71b/+0x80c housekeeping bytes and the +0x7c/+0x7e/+0x80 aim-rate
 *  accumulators are not surfaced on RomActor — labeled no-ops. */
export function romGroundIdleReturn(actor: RomActor): void {
  actor.controlWord &= 0xff0003; // +0x5e0 &= 0xff0003
  actor.gravityCoeff = 0;        // +0x50 = FLOAT_8043762c
  actor.yVel = 0;                // +0x48 = 0
  actor.hDecel = 0;              // +0x4c = 0
  actor.hSpeed = 0;              // +0x44 = 0
  dispatchUpperBodyCue(actor, 0); // zz_006a750_(a, 0)
}

/** zz_006a4f4_ @ chunk_0009.c:735-746 — air idle return.
 *  Masks the control word and dispatches upper-body cue 0x12 (row 18 → state 24).
 *  +0x1d9c/+0x71b clears are not surfaced — labeled no-ops. */
export function romAirIdleReturn(actor: RomActor): void {
  actor.controlWord &= 0xff0843;   // +0x5e0 &= 0xff0843
  dispatchUpperBodyCue(actor, 0x12); // zz_006a750_(a, 0x12)
}

/** zz_006a5a4_ @ chunk_0009.c:770-797 — airborne knock-out / air-fall return.
 *  Dispatches upper-body cue 6. The (+0x5e0 & 3) == 3 arm (freeze release) floors
 *  the +0x694 state timer at 30 frames and calls zz_005c080_ (freeze-release
 *  bookkeeping — unported, labeled no-op @0x8005c080). +0x590 = 1, +0x690 = 0,
 *  +0x71b = 0 and the +0x1d9b stream-authored launch block (+0x5ae = +0x1db0 +
 *  +0x72; +0x44 = +0x1dac) are not surfaced on RomActor — labeled no-ops. */
export function romAirKnockoutReturn(actor: RomActor): void {
  if ((actor.controlWord & 3) === 3) {
    actor.controlWord &= 0xff0040; // +0x5e0 &= 0xff0040
    if (actor.stateTimer <= 0) {
      actor.stateTimer = KNOCKOUT_TIMER_FLOOR; // +0x694 floor, FLOAT_80437648
    }
    // zz_005c080_(actor) — freeze-release (labeled no-op).
  } else {
    actor.controlWord &= 0xff0041; // +0x5e0 &= 0xff0041
  }
  dispatchUpperBodyCue(actor, 6);  // zz_006a750_(a, 6)
}
