# OGhidra ninja flying-lunge findings applied to the 1:1 port (2026-08-03)

Source session: `research/tools/OGhidra/analysis_sessions/session_1784598555_d3f63cbf/session.json`
(146,244 lines — the newest and largest banked session; qwen35b-a3-mtp). All numeric
constants below were read directly from `user-data/GG4E/disc/sys/boot.dol` sdata2
(section @0x80436a20) and the referenced Ghidra-exported function bodies before being
applied. This is an implementation pass: the phase routing, speed projection, and
exit gating are ROM-derived, while the remaining host-bound gates are listed
explicitly at the end.

## Selection rationale and an honesty note on repo maturity

The 2026-07-12 pass framed the OGhidra sessions as the highest-leverage unport debt:
~40 sessions banked, one consumed. Re-surveying the corpus for this pass established
that the combat tree has matured well past that framing: **every one of the 110
bespoke families in `research/tasks/bespoke-port-work-queue.json` already has a
dedicated module or cluster registration** (verified programmatically — all 208
borgIds resolve into `packages/combat/src/families/*.ts` + `bridge.ts`). There is no
longer a genuinely-MISSING family module to spin up; the wave of greenfield
`families/<name>.ts` files the 2026-07-12 template produced has closed.

The honest high-value move, then, is the same shape as the 2026-07-12 pass itself
**when it enriched already-registered families** (NORMAL TANK / LEOPARD action 0+2,
ARROW NINJA action 1, EAGLE ROBOT action 0): fill a documented action-level gap. The
highest-signal such gap is **NORMAL NINJA action 1 variant 3 — the flying lunge
`zz_00710d8_`**, which `ninja.ts:389` and `ninja-cluster.ts:433` both flagged as
"NOT ported this pass… labeled approximation" and let fall through to the shared
melee lunge. This pass ports it for real, DOL-verified.

A second honesty note on the session itself: `session_1784598555_d3f63cbf` analyzes
6,580 functions but its per-function behavior summaries for the ninja range are
generic wrapper/descriptor text (low combat signal), and the rich combat detail it
embeds is quoted from the existing `research/decomp/*.md` docs rather than freshly
derived. The session's actionable contribution here is its analysis of the action-1
dispatcher **FUN_80070604** (borg-switched variant dispatch), which corroborates the
variant routing. The phase-machine transcription below is taken from the decomp
(`chunk_0009.c`) and the DOL constants directly; the session is the index path, not
the authority.

## Newly confirmed behavior

### NORMAL NINJA / SASUKE action 1 variant 3 — FLYING LUNGE (`zz_00710d8_`, 0x800710d8)

- The handler is a three-phase homing air dive on phase table **`0x802d3c3c`**; it is
  NOT the shared melee lunge and is NOT the leap dive-slam (those are variants 0/1
  and 4 respectively).
- Variant routing DOL-verified byte-for-byte: `PTR_FUN_802d3bd4[3] = 0x800710d8`
  (pl0000) and `PTR_FUN_802d3be8[3] = 0x800710d8` (SASUKE) — **both** families route
  v3 to this handler. The phase table `0x802d3c3c` reads `[0x80071128, 0x80071288,
  0x800713e0]` = `[zz_0071128_, zz_0071288_, zz_00713e0_]`.
- Phase 0 (`zz_0071128_`, chunk_0009.c:5107): zeroes `+0x50/+0x48/+0x4c/+0x44`, the
  pose accumulators `+0x80/+0x7e/+0x7c`, seeds `+0x558 = 20.0` (`FLOAT_8043774c`),
  `+0x54e = 0`, `+0x745 = 0`, then streams group 3 slot **8** (NORMAL) or **9**
  (SASUKE 0x00a) at rate −1.0, post-incrementing `+0x6ea`.
- Phase 1 (`zz_0071288_`, chunk_0009.c:5163): homing dive. It builds an aim target
  from the descriptor bone anchor (`+0x4b0 + mainHandBone*0x30 + 0x8e0/8f0/900`)
  scaled by `FLOAT_8043775c (=100.0) × +0xb4`, solves the part pitch `+0x54e`, then
  projects `+0x44 = 30.0 × cos(+0x54e)` and `+0x48 = 30.0 × −sin(+0x54e)`
  (`FLOAT_80437708`). It integrates at rate 1.0 against `+0x5ac`, ticks the stream
  only while `+0x1cef == 0`, drains `+0x558`, and advances on `+0x558 ≤ 0` OR the
  `FUN_800668cc(250.0)` range gate, reseeding `+0x558 = 120.0` (`FLOAT_80437730`).
- Phase 2 (`zz_00713e0_`, chunk_0009.c:5211): recover/exit with a **SASUKE bounce**.
  When `borg == 0x00a AND (+0x1d9 & 0x30)`: `+0x44 = 8.0` (`FLOAT_80437764`),
  `+0x4c = 0`, `+0x48 = 20.0` (`FLOAT_8043774c`), `+0x50 = desc+0x6c`, `+0x745 = 1`,
  `+0x5ae -= 0x8000` (face away), `+0x1d10 = 0`. Then a `0.95` velocity drag
  (`FLOAT_80437744`, `zz_006ed8c_`) + integrate. The exit splits on the collision
  probe: **airborne OR stream-incomplete** → `zz_006a5a4_` air-variant return +
  `+0x694 = 1.0 + dt`; **grounded AND stream-complete** → `+0x50 = desc+0x6c`,
  `zz_006a750_(actor, 7)` upper-body cue, `+0x694 = 1.0 + dt`. A `+0x745`/`+0x1cee`
  hold gate delays the air exit while the timer is positive.
- A steep-downward target on phase 0 redirects to the **leap dive-slam** instead:
  `FUN_800667a0` pitch baseline minus `DOUBLE_804376f0 (=176.0)` compared against
  `FLOAT_80437758 (=−8192.0)`; if steeper, `+0x581 = 4` and the leap wrapper
  `zz_0070698_` runs.

### DOL-read constants (sdata2 section @0x80436a20)

| Symbol | Value | Role |
| --- | --- | --- |
| `FLOAT_804376e4` | 0.0 | zero scalar / threshold |
| `FLOAT_804376e8` | 1.0 | `FUN_80067310` rate + ph2 `+0x694` exit seed |
| `FLOAT_80437708` | 30.0 | ph1 hSpeed/yVel magnitude |
| `FLOAT_80437730` | 120.0 | ph1→ph2 `+0x558` reseed |
| `FLOAT_80437744` | 0.95 | ph2 velocity drag (`zz_006ed8c_`) |
| `FLOAT_8043774c` | 20.0 | ph0 `+0x558` seed / SASUKE bounce `+0x48` |
| `FLOAT_80437758` | −8192.0 | leap-redirect pitch gate (BAM) |
| `FLOAT_8043775c` | 100.0 | ph1 aim-target quat scale factor |
| `FLOAT_80437760` | 250.0 | ph1 advance range gate |
| `FLOAT_80437764` | 8.0 | SASUKE bounce `+0x44` |
| `DOUBLE_804376f0` | 176.0 | leap-redirect pitch baseline |

(All values cross-validated against the known-true neighbors `FLOAT_804376e0 = −1.0`,
`FLOAT_8043770c = 60.0`, `FLOAT_80437710 = 0.98`, `FLOAT_80437774 = 0.97` already
cited by `ninja-cluster.ts`.)

## Port location and verification

- `packages/combat/src/families/ninja-cluster.ts` — new `NINJA_FLYING_LUNGE` const
  block, `flyingLungePitch` helper, and `normalFlyingLunge` (3-phase machine);
  variant-3 wired in `createNormalNinjaRootAction`'s `contextualB`.
- `packages/combat/src/families/ninja.ts` — stale "v3 unported" comment corrected
  to point at the new port (its `configureNinjaFamily` is superseded by
  `configureNormalNinjaFamily` and is no longer the live registration target).
- `packages/combat/src/rom/rom.selfcheck.ts` is unchanged; the focused asserts live
  in `ninja-cluster.ts`'s `runNinjaClusterSelfTests` (21 new asserts covering ph0
  setup for both borgs, the leap redirect, ph1 homing + range gate advance, the
  SASUKE bounce, and the grounded exit).

No `bridge.ts` change: `pl0000`/`pl000a` already register
`configureNormalNinjaFamily`, which now routes variant 3 to the new machine. The
existing cue-table and registrations pick it up unchanged.

Verification at capture time: `pnpm -r run build` clean, `pnpm selfcheck:rom` →
`ALL PASS` (2,245 ok asserts, +21 from this pass; the suite long since grew past
the old "610+" baseline), `pnpm --filter @gf/combat typecheck` clean.

## Claims downgraded to TUNED / host-bound (honesty check)

The following phase-0/phase-1/phase-2 ingredients are **not** modeled 1:1 and are
marked TUNED in the port comments; the phase transitions and observable motion do
not depend on them:

- **`FUN_80066838(+0x86c row)` ph0 speed gate** — host-bound (the +0x86c rows are
  runtime-populated by the renderer). Its slow branch (`+0x541=1 / +0xcc=0 /
  +0x5ae/+0x5ac=+0x72`) is cosmetic visibility and is omitted.
- **`FUN_800667a0` ph0 leap-redirect pitch gate** — host-bound (descriptor bone
  geometry). The DOL constants (`DOUBLE_804376f0 = 176.0`, `FLOAT_80437758 =
  −8192.0`) are read and cited, but the gate is approximated by a steep-below
  target Y delta (> 250 below → leap).
- **ph1 aim target from descriptor bone anchors** (`+0x4b0 + mainHandBone*0x30 +
  0x8e0/8f0/900`) — host-bound (renderer bone matrices). The port uses
  `partAimAnchors[mainHandBone]` when present, else falls back to the host lock
  target.
- **`+0x1d9` SASUKE bounce input latch** — host-set; surfaced via a
  `flyingBounce1d9` scratch field (default absent → no bounce).
- **session function summaries for the ninja range** — generic wrapper text, NOT
  trusted for phase-machine detail; the machine is transcribed from the decomp +
  DOL only, with the session's `FUN_80070604` dispatcher analysis as corroboration.

## Remaining host-bound gates (residuals)

The remaining precision limit is geometric/host-owned, not missing state-machine
knowledge: the host owns the renderer per-frame bone matrices that drive the ph1
homing target and the `+0x86c`/`FUN_800667a0` gates, and the `+0x1d9` bounce latch
is authored by input/stream decode the bridge does not yet surface. The port
approximates all of these from live target geometry + scratch flags so the phase
transitions, speed projection, SASUKE bounce scalars, and grounded-vs-air exit
routing are testable and faithful, while the exact bone-relative aim and the input
latch timing remain residuals.
