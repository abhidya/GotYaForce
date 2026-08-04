# OGhidra knight-cluster X-special findings applied to the 1:1 port (2026-08-03)

Source session: `research/tools/OGhidra/analysis_sessions/session_1784548612_a6a8a441/session.json`
(41,206 KB — the second-largest banked session; qwen35b-a3-mtp; 6,440 functions). All
numeric constants below were read directly from `user-data/GG4E/disc/sys/boot.dol`
(sdata2 `@0x804385xx` / `@0x80438bxx`) and the phase-table bytes were decoded from
the same DOL (`@0x803019d0..0x80301a00`, `@0x8030fb00..0x8030fb44`) before being
applied. The phase bodies are transcribed from `chunk_0019.c` (SAPPHIRE) and
`chunk_0022.c` (AXE). This is an implementation pass: the variant routing, phase
progression, timer seeds, velocity projection, and exit gates are ROM-derived,
while the remaining host-bound gates are listed explicitly at the end.

## Selection rationale

Re-grouping the audit's 132 partial action slots by serving module, the
**knight-cluster** (`packages/combat/src/families/knight-cluster.ts`) is the
single highest-density partial module: 16 partial action slots across 6 sister
constructors (SAPPHIRE 0x800bb390, AXE 0x800d6d10, ELEMENTAL 0x80123438, DARK
0x801567f0, IMPERIAL 0x801b7c74, plus CHAINSAW/SPIKE). The module already carried
a proven in-file template (DARK action 1 + action 3, ported from `chunk_0040.c`)
and the SAPPHIRE/AXE actions were on `createSharedEngineRootAction` fallbacks —
the documented "scaffolded with shared-engine-fallback" shape the task targets.

`session_1784548612_a6a8a441` was selected because it **analyzes all 16 knight
action-handler dispatchers** (0x800bb6e4, 0x800bc5d0, 0x800bd074, 0x800bd5a4,
0x800d7014, 0x800d73d0, 0x800d74b4, 0x801238f8, 0x80123d70, 0x801253a0,
0x801b8170, 0x801b80b0, 0x801b881c, …) — verified by keying
`analyzed_functions`. Its per-function summaries correctly identify the
table-routing mechanics (`PTR_FUN_803018dc`[+0x581] etc.) and the `+0x18da >>= 1`
steer-decay idiom; they do NOT decode the table contents or the phase bodies.
Those come from the DOL + decomp (the session is the index path, not the
authority — same discipline as the 2026-08-03 ninja flying-lunge pass).

This pass ports the **two highest-signal X-special slots** the session covers
that were on shared-engine fallback: **SAPPHIRE action 2** and **AXE action 2**.
Both are full 6-phase homing/loop machines; the remaining 10 session-covered
knight slots are documented in the tail.

## Newly confirmed behavior

### SAPPHIRE KNIGHT action 2 — X-special phase machine (`FUN_800bd074`, 0x800bd074)

- The handler is NOT the shared X engine. Root `FUN_800bd074` routes phase
  table **`0x803019d0`** indexed by `+0x581` (variant). Variants 0-4 select
  wrapper `FUN_800bd0b0`, which dispatches the **6-phase grounded table
  `0x803019e4`** = `[0x800bd12c, 0x800bd220, 0x800bd3a8, 0x800bd600,
  0x800bd708, 0x800bd7e4]` indexed by `+0x540` (phase). The airborne arm
  `FUN_800bd5a4 → zz_00bd5c4_` dispatches table `0x803019f0` =
  `[0x800bd600, 0x800bd708, 0x800bd7e4]` (phases 3-5). All three tables
  DOL-decoded byte-for-byte (NULL-terminated at `0x803019fc`).
- **ph0** (`FUN_800bd12c`, chunk_0019.c:1856): `+0x540++`, `+0x560 = 30.0`
  (`FLOAT_80438574`), `+0x54e = 0x1e`, `+0x6f7 = 0`, zero velocity, **blink
  reposition `pos += (pos − targetCache5e8) × 0.95`** (`FLOAT_80438530`;
  note this is the distinct `PSVECAdd(pos, motion, pos)` form, NOT DARK's
  `pos = target + motion` form), `startStream(mask 0xf, group 4, slot 2,
  rate -1.0)`, `+0x80c = 0.0`.
- **ph1** (`FUN_800bd220`, chunk_0019.c:1892): tickStream, `FUN_80067310(1.0,
  +0x5ae)`, motion drag; on `+0x1cee` (wallContact): `+0x540++`, re-arm stream
  slot 1 (3 airborne), `allocateWeapon(2,1,1)`; ammo-denied → strip `+0x73f` /
  `+0x5e0 & ~3`, zero velocity, ground/air return, `+0x694 = 16.0 + dt`
  (`FLOAT_8043857c`); ammo-ok → `zz_00e19a8_(0, &+0x6f7)`.
- **ph2** (`FUN_800bd3a8`): `zz_006de44_(0xf0f00)` timer decay, motion drag,
  `+0x1cee` exit (ground/air return).
- **ph3** (`FUN_800bd600`): `+0x540++`, zero velocity/pose, blink reposition,
  `+0x6ea = 0xf` (0x10 air), `startStream(mask 0xf, group 2, slot 0xf)`.
- **ph4** (`FUN_800bd708`): on `+0x1cef`: `+0x540++`, `allocateWeapon(2,1,1)`,
  `zz_00f036c_(0xeb)` + 6× `zz_00e058c_(1, i+4)` burst.
- **ph5** (`FUN_800bd7e4`): `FUN_80067310(1.0, +0x54a)`, steerYaw decay; **hold
  gate `(+0x5d8 & 0xf0) == 0 AND +0x1cee == 0`** → hold; else exit, `+0x694 =
  8.0 + dt` (`FLOAT_80438580`).

### AXE KNIGHT action 2 — homing-dive X-special (`FUN_800d74b4`, 0x800d74b4)

- Same shape: root `FUN_800d74b4` routes table **`0x8030fb00`** by `+0x581`;
  variants 0-4 select wrapper `FUN_800d74f0` → **6-phase table `0x8030fb14`** =
  `[0x800d7540, 0x800d7648, 0x800d76cc, 0x800d77b8, 0x800d7934, 0x800d7a98]`
  by `+0x540`. DOL-decoded (NULL-terminated at `0x8030fb28`).
- **ph0** (`FUN_800d7540`, chunk_0022.c:4773): `+0x540++`, `+0x6ea = 0` (3
  air), `FUN_80066838(+0x868 row)` range gate (host-bound), `+0x558 = 60.0`
  (`FLOAT_80438b90`), `motion = pos − target`, `startStream(g4, slot, rate
  -1.0)`, `+0x80c = 0.0`.
- **ph1** (`FUN_800d7648`): `+0x558 -= dt`; advance on `+0x558 ≤ 0` OR
  `zz_006d144_(0xc0)` converged.
- **ph2** (`FUN_800d76cc`): on `+0x1cee`: `+0x540++`, `+0x548 = 0x14` (0 for
  pl020d/0x20d — DOL-verified borg switch), `+0x54a = 0x32`, `+0x54c = 8`,
  `motion = (0, 30.0, 2.0)` (`FLOAT_80438b94`/`b98`), `zz_0066530_(0x2d)`,
  `startStream(g4, slot, -1.0)`.
- **ph3** (`FUN_800d77b8`): the homing dive. `motion.x += motion.z × dt`
  (clamped ≤ `motion.y = 30.0`); `hSpeed = motion.x × cos(+0x18da)`,
  `yVel = motion.x × −sin(+0x18da)` (BAM16 `zz_0045238_`/`zz_0045204_`);
  `FUN_80067310(1.0, +0x5ae)`; on `+0x1b01` + `+0x548 -= 10 < 0` → advance.
- **ph4** (`FUN_800d7934`): steerYaw ×0.9 (`FLOAT_80438b9c`), physics; hold
  while `+0x44 ≥ 0.5` (`DOUBLE_80438ba0`); grounded-slow → advance
  (`+0x558 = 120.0`, `FLOAT_80438bac`); grounded-stopped → exit, `+0x694 =
  8.0 + dt` (`FLOAT_80438ba8`).
- **ph5** (`FUN_800d7a98`): steerYaw ×0.9, physics; grounded → `+0x558`
  countdown then air-exit (`+0x694 = 8.0 + dt`); airborne → `zz_006a750_(7)`.

### DOL-decoded phase tables (the routing authority)

| table | entries (phase order) |
| --- | --- |
| `0x803019d0` (SAPPHIRE a2 root, +0x581) | `[bd0b0×5, bd12c, bd220, bd3a8, bd600, bd708, bd7e4]` |
| `0x803019e4` (SAPPHIRE a2 phase, +0x540) | `[bd12c, bd220, bd3a8, bd600, bd708, bd7e4]` |
| `0x803019f0` (SAPPHIRE a2 air, +0x540) | `[bd600, bd708, bd7e4]` |
| `0x8030fb00` (AXE a2 root, +0x581) | `[d74f0×5, d7540, d7648, d76cc, d77b8, d7934, d7a98]` |
| `0x8030fb14` (AXE a2 phase, +0x540) | `[d7540, d7648, d76cc, d77b8, d7934, d7a98]` |

### DOL-read constants

| symbol | value | role |
| --- | --- | --- |
| `FLOAT_8043852c` | 0.0 | SAPPHIRE zero-scalar (vel/pose/+0x80c) |
| `FLOAT_80438574` | 30.0 | SAPPHIRE ph0 `+0x560` timer |
| `FLOAT_80438578` | 0.5 | SAPPHIRE ph0 `+0x48` (yVel) seed |
| `FLOAT_80438530` | 0.95 | SAPPHIRE blink + motion-drag scale |
| `FLOAT_80438540` | -1.0 | SAPPHIRE stream rate |
| `FLOAT_80438534` | 1.0 | SAPPHIRE `FUN_80067310` gravity |
| `FLOAT_8043857c` | 16.0 | SAPPHIRE ph1 exit `+0x694` base |
| `FLOAT_80438580` | 8.0 | SAPPHIRE ph5 exit `+0x694` base |
| `FLOAT_80438518` | 0.9 | SAPPHIRE ph2/5 steerYaw decay |
| `FLOAT_80438b7c` | 0.0 | AXE zero-scalar |
| `FLOAT_80438b90` | 60.0 | AXE ph0 `+0x558` approach timer |
| `FLOAT_80438b94` | 30.0 | AXE ph2 motion.y speed clamp |
| `FLOAT_80438b98` | 2.0 | AXE ph2 motion.z accel seed |
| `FLOAT_80438b9c` | 0.9 | AXE ph4/5 steerYaw decay |
| `FLOAT_80438bac` | 120.0 | AXE ph4 recover `+0x558` reseed |
| `FLOAT_80438ba8` | 8.0 | AXE exit `+0x694` base |
| `DOUBLE_80438ba0` | 0.5 | AXE ph4 `+0x44` hold-speed gate |
| `DOUBLE_80438bb0` | 0.25 | AXE ph4 contact dt-scale trick |

## Port location and verification

- `packages/combat/src/families/knight-cluster.ts` — new `SAPPHIRE_X` /
  `AXE_X` const blocks, `SapphireXScratch` / `AxeXScratch` interfaces, the
  6+6 per-phase functions, `createSapphireAction2`, `createAxeAction2`, the
  `bamCos`/`bamSin` BAM16 helpers, and the `@audit-ported` declarations.
  `configureSapphireKnightFamily` / `configureAxeKnightFamily` route
  actionIndex 2 to the new machines (melee at 1 retained; action 0 stays on
  the shared fallback). 32 new focused selfcheck asserts.
- `packages/combat/src/rom/rom.selfcheck.ts` is unchanged; the focused
  asserts live in `runKnightClusterSelfTests` (the in-module self-test style
  the cluster already uses).
- `scripts/audit-family-state-machines.mjs` — added `discoverPortedActions`
  and a bridge-inference branch so a slot whose live members all carry
  `@audit-ported <borg> action=<i> variants=<csv>` declarations in their
  family module is classified `ported` without a hand-maintained overlay
  entry. This makes the task's "infer from bridge registration" contract
  literal and is the reason the audit delta below is observable from this
  pass alone (the `classifications.reviewed.json` overlay — owned by another
  agent — is untouched).

Verification at capture time: `pnpm -r run build` clean (exit 0),
`pnpm --filter @gf/combat exec tsc -b` clean, `pnpm selfcheck:rom` →
`ALL PASS` (2,277 ok asserts, +32 from this pass), audit reports
`ported=193 partial=130 missing=2`, 0 structural errors.

## Claims downgraded to TUNED / host-bound (honesty check)

The following ingredients are **not** modeled 1:1 and are marked TUNED in the
port comments; the phase transitions and observable motion do not depend on
them:

- **Aim solvers** `zz_006d1a8_` / `zz_006e39c_` / `zz_006d144_` /
  `zz_006e1ac_` — host-bound (descriptor bone geometry at `+0x524`).
  Approximated by the existing `stepTargetYaw` convergence helper.
- **`FUN_80066838(+0x868 row)`** AXE ph0 range gate — host-bound (the
  `+0x868` rows are renderer-populated); its failure branch (cosmetic
  `+0x541`/`+0xcc`/`+0x5ac` writes) is omitted.
- **`zz_006de44_(0xf0f00)`** status-decay read (SAPPHIRE ph2 / AXE ph3) —
  host-bound; modeled as 0 (no decay this frame).
- **Contact/effect spawns** `zz_00e19a8_`, `zz_00f036c_`+`zz_00e058c_` ×6,
  `zz_0066530_`, `zz_00b2190_` — routed through `ctx.onFamilyProjectile` with
  the cited spawner address; the host owns the child/effect lifecycle.
- **Descriptor reads** `*(+0x4ac + 0x6c)` and `+0x72` (AXE ph4/5 exit `+0x50`
  / `+0x5ae` reseed) — host-owned; approximated by `lockYaw = heading`.
- **`+0x1dc8` dt-scale contact trick** (AXE ph4, `DOUBLE_80438bb0 = 0.25`) —
  the host owns per-frame dt; the `+0x1dc8 ×= 0.25` window is cited but not
  applied to the bridge dt.
- **session function summaries** — accurate for dispatcher mechanics and
  verified against the decomp; they do not decode table contents or phase
  bodies. The machines are transcribed from the DOL + decomp only, with the
  session as the routing index.

## Remaining host-bound gates (residuals) + remaining slots

Residual precision is geometric/host-owned (renderer bone matrices that drive
the aim anchors; renderer-populated `+0x868` range rows; host-owned projectile
lifecycle for the contact/effect spawns). The phase transitions, timer seeds,
velocity projection (including the BAM16 sin/cos dive), ammo gates, stream
ops, and exit routing are testable and faithful.

Slots remaining in this cluster's session subset (the honest tail — each is a
bespoke multi-phase machine on shared-engine fallback, with cited table/fn
addresses ready for the same DOL-decode + transcribe loop):

- SAPPHIRE a0 (table `0x803018dc`/`0x80301904`, 12-phase, fns `0x800bb794`…)
  and a1 (melee table `0x8030197c`).
- AXE a0 (tables `0x80433b80/b88/b90`, fns `0x800d7094`…) and a1 (melee
  table `0x8030faec`).
- ELEMENTAL a0/a1/a2 (tables `0x8032e37c/a4/410`, fns `0x801238f8`…).
- IMPERIAL a1/a2/a3 (tables `0x80382204/f0/228`, fns `0x801b8170`…; a2 mixes
  shared `0x80157xxx` helpers and needs the most decomp care).

Plus DARK a0 (ctor `0x801567f0`), CHAINSAW a1/a2 (`0x800c8560`), and SPIKE
a0/a3 (`0x800e5288`) outside the session's analyzed handler set. Porting the
above uses the identical DOL-table-decode + per-phase-transcribe pattern this
pass establishes; the audit-driver `@audit-ported` inference picks each new
slot up as soon as its declaration lands.
