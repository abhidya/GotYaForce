# ROM-faithful actor runtime — porting tracker

This folder (`packages/combat/src/rom/`) is the 1:1 port of the GG4E actor state-machine
system. It replaces the generic-archetype combat logic (the `projectile`/`aoe`/`melee`
`SpecialActionDef` paths in `combat.ts`) with the real ROM mechanics: per-family action
handlers, the shared physics integrator, the action-script stream VM, and the cue→state
dispatch chain.

## Why this exists

The generic archetypes cannot reproduce real move motion because **the motion lives in
per-family C state handlers**, not in shared data tables (proven 2026-07-05 — see
`research/decomp/action-vm-and-gcrash-decode-2026-07-05.md`). G Red's G Crash, Star
Hero's X dash, Sword Knight's specials, etc. are each unique 3-4 phase machines. A 1:1
port requires the actual handler code, transcribed per family.

## Architecture (the layers, ported bottom-up)

```
┌─────────────────────────────────────────────────────────────────────────┐
│ PER-FAMILY LAYER (ports incrementally)                                 │
│   rootAction dispatcher (actionIndex → handler)                        │
│   per-action handler (variant table → phase table)                     │
│   per-phase fn (stream tick + physics + contact check + transition)    │
│   G RED family: chunk_0047.c:777-970 (FUN_8018e888 chain) — REFERENCE  │
├─────────────────────────────────────────────────────────────────────────┤
│ SHARED ENGINE LAYER (ported once, this folder)                         │
│   dispatch.ts     cue→state (zz_006a6fc_/zz_006a750_), command (zz_006a104_) │
│   physics.ts      integrator (FUN_80067310) + projection helpers       │
│   stream-vm.ts    action-script interpreter (zz_004cd24_) — TODO       │
│   state tables    PTR_LAB_802d37a8/36a8 (~30-60 entries) — TODO        │
│   actor.ts        the +0xNNN struct map                                │
├─────────────────────────────────────────────────────────────────────────┤
│ DATA (already extracted fleet-wide by existing scripts)                │
│   commandMoveTables.json   per-button/subtype command records          │
│   actionStreamTables.json  per-(borg,action,variant) stream leaf       │
│   meleeAnimKinds.json      stream events (armHit/playAnim/wait ops)    │
│   attackHitTables.json     kind → hit record (windows, reach, bone)    │
│   familyDamageRecords.json kind → damage record                        │
│   borgSourceStats.json     per-borg HP/ammo/movement rows              │
│   borgMoveProperties.json  wiki NLP summaries (advisory only)          │
└─────────────────────────────────────────────────────────────────────────┘
```

## Status

| Layer | File | Status |
|---|---|---|
| Actor struct | `actor.ts` | **Done** — full +0xNNN field map |
| Physics | `physics.ts` | **Done** — FUN_80067310 + projection helpers. Yaw verified |
| Cue/command dispatch | `dispatch.ts` | **Done** — zz_006a6fc_/zz_006a750_/zz_006a104_/FUN_80065dfc |
| Action-stream VM | `stream-vm.ts` | **Done** — zz_004beb8_ + zz_004cd24_ + all 18 op handlers |
| State tables | `state-tables.ts` | **Done (stubs for custom)** — 64+64 slots; factories for common shapes |
| G RED family (X-special) | `families/gred.ts` | **Done** — 4-phase G Crash (launch→dash→descend→land) |
| **Shared-engine X machine** | `families/shared-x-special.ts` | **Done (2026-07-06)** — zz_00ff2bc_ @0x800ff2bc + 3 phases, config-parameterized {groundSlot, airSlot, onHit}. Families whose X routes here need only a config block |
| **NORMAL NINJA family (X-special)** | `families/ninja.ts` | **Done (2026-07-06)** — pl0000 + pl000a (SASUKE, same ctor/vtable/banks — descriptor-only delta) via the shared machine; on-hit backflip (10/15/−1, yaw+180°) + shuriken hook. `nn-family-decode-2026-07-06.md` |
| Bridge | `bridge.ts` | **Done** — BorgRuntime ↔ RomActor sync + 3-line combat.ts/battle.ts integration. Cue tables for BOTH families now FULL 48-row DERIVED dumps (0x802d3ff8 / 0x80365cf8; cues 44 AND 45 → state 61) |
| Damage | `bridge.ts` + `battle.ts` | **Done** — full `applyHit` damage-formula path wired via `hitResolver` callback (family damage records + force gauge + burst meters + source damage) |
| Anim | `bridge.ts` | **Done** — `onPlayAnim` → BorgRuntime.meleeAnimStream for renderer clip |
| Selfcheck | `rom.selfcheck.ts` | **Passing** — 22/22 tests (`pnpm selfcheck:rom`) |
| Cue table extractor | `scripts/extract-family-cue-tables.mjs` | **Partial** — 17/30 families (direct lis+addi pattern); G RED cue table hardcoded in bridge.ts; indirect-load families (lwz-based) TODO |
| G RED B-melee/dash/charge | — | **TODO** — actionIndex 0/1/3/4 of the G RED dispatcher (chunk_0047.c). NOTE (2026-07-06): G RED's command types 4/5 are mode-0xff DISABLED (descriptor 0x80365ac8+0xb8 = `01 00 00 01 ff ff`) — only type-3 B-charge is live; the action-4 table @0x80365e48 is dead data |
| NORMAL NINJA B-combo/lunge | — | **TODO** — actions 0/1 transcribed to phase granularity in `nn-family-decode-2026-07-06.md` §3 (incl. the SHARED 4-phase melee lunge zz_00fed6c_ @0x800fed6c — port once like shared-X); actions 3/4 are command-disabled for pl0000/pl000a |
| Remaining ~29 families | — | **TODO** — each family is ~0.5-1 session. CHECK FIRST whether the family's X routes to zz_00ff2bc_ (shared) — then it's just a config block + callback, not a full transcription |

## What works RIGHT NOW

Pressing X on G RED (pl0615) in-game:
1. **Launches G Red upward** at Y=+4.0 (FLOAT_8043b158) — the "fly up"
2. **Repositions** 5% from lock target (FLOAT_8043b124 = 0.95)
3. **Plays g04_s00** (the 81-frame fist-chambered pose) via `meleeAnimStream`
4. **Arms kind-15 hitbox** with decoded active windows (frames 8-16 close-body, 53-64 extended-fist)
5. **Deals damage** through the full `applyHit` formula (family damage record + source damage + force gauge)
6. **On hit: dashes forward** at magnitude 60 XZ / 10 Y (FLOAT_8043b148/_15c)
7. **Descends** with angle-steered physics, **lands**, returns to idle

All other borgs keep the existing generic-archetype combat logic unchanged (romDriver = null).

## Per-family porting template (the recipe every family follows)

For each family module (e.g. `families/gred.ts`):

1. **Read the ctor** in `research/decomp/ghidra-export/chunk_00NN.c` (find it via
   `borgs[id].constructorAddress` in commandMoveTables.json). The ctor writes:
   - `+0x4b4` = root action dispatcher (e.g. `zz_018d24c_`)
   - `+0x4f0` = cue→state table address (48 entries)
   - `+0x4ec` = command-move table (already extracted)
   - `+0x4b0` = family descriptor (per-borg data page)

2. **Port the root action dispatcher** — it reads `+0x580` (actionIndex) and jumps to
   the per-action handler via a function-pointer table (G RED: 5 entries at PTR_zz_018d288).
   Each entry is a phase-table driver.

3. **Port each action handler's phase functions.** Shape is uniform (proven across G RED,
   Star Hero, Sword Knight — see cue-script-stream-decode §3):
   ```ts
   function gredXPhase0(actor: RomActor): void {
     actor.fbPhaseSlots[0]++;               // enter phase
     // ... per-variant setup (borg-number switch) ...
     actor.hSpeed = 0; actor.yVel = 4.0; actor.hDecel = 0; actor.gravityCoeff = 0;
     // reposition: motion = (pos - target) × 0.95; pos += motion
     startStream(actor, 0xf, 4, actor.streamSlot);  // stream-vm.ts
   }
   function gredXPhase1(actor: RomActor): void {
     advanceStream(actor, 0xf);             // stream-vm.ts (zz_004cd24_)
     integratePhysics(1.0, actor, actor.lockYaw);  // physics.ts
     if (actor.contactP0 > 0) {             // hit connected (op 0x02 set this)
       actor.fbPhaseSlots[0]++;             // → phase 2
       actor.motion = { x: 0, y: 10, z: 60 };  // dash impulse (FLOAT_8043b148/_15c)
     }
   }
   // ... phase 2, phase 3 ...
   const PHASE_TABLE = [gredXPhase0, gredXPhase1, gredXPhase2, gredXPhase3];
   function gredXHandler(actor: RomActor): void { PHASE_TABLE[actor.fbPhaseSlots[0]]?.(actor); }
   ```

4. **Register the family** — wire `rootAction`, `cueTable`, and the action-index table
   into the actor at spawn. The existing `borgCatalog.ts` already maps borg-id → ctor
   address; this layer adds ctor-address → family module.

## The motion constants (DERIVED from boot.dol 2026-07-05)

G RED family `FUN_8018e888` chain — full table in
`research/decomp/action-vm-and-gcrash-decode-2026-07-05.md`. Sample:
- launch Y impulse = 4.0 (FLOAT_8043b158)
- relpos scale = 0.95 (FLOAT_8043b124)
- gravity during move = 1.0 (FLOAT_8043b130)
- hit-transition dash XZ = 60.0 (FLOAT_8043b148), Y = 10.0 (FLOAT_8043b15c)

Every other family's constants are extractable the same way (read the FLOAT_8043xxxx
operands in that family's handler, resolve via `research/decomp/dol.py`).

## Bridge to @gf/combat BorgRuntime

The ROM runtime is NOT a separate battle sim — it composes with the existing one. The
existing `BorgRuntime` (HP, gauges, lock-on, weapon cells, status, projectiles, results
telemetry) stays. The ROM runtime replaces only the **movement integration** (movement.ts)
and the **attack-action driving** (combat.ts's stepAttacks/stepMovement) for borgs whose
family has been ported. The bridge adapter (TODO file `bridge.ts`) copies fields between
`BorgRuntime` and `RomActor` each frame:
- BorgRuntime.pos/vel/rotY ↔ RomActor.pos/hSpeed+yVel/heading
- BorgRuntime.cooldowns["xSpecialPhase"] ↔ RomActor.fbPhaseSlots
- BorgRuntime.alive/hp/state ↔ (owned by existing layer; ROM runtime reads only)

Borgs without a ported family keep the existing generic-archetype behavior unchanged
(the `SpecialActionDef` path); the registry returns null for them.

## Honest scope to completion

- VM + state tables: ~1 session each
- G RED reference family: ~1 session
- Each subsequent family: ~0.5-1 session (mechanical transcription + constants extraction)
- ~30 families total → ~15-25 sessions of focused porting

The foundation here (actor + physics + dispatch) is reviewable and unit-testable now;
each family that lands is independently shippable behind a registry flag.
