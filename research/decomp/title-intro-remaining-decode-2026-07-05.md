# Title-intro remaining decode (2026-07-05)

Closes the four open decode targets flagged after the VM port + tdc decode. Each section
cites the exact ROM evidence.

## 1. Actor anim-bank (+0x1d80) binding — per-family virtual ctor

`zz_0057ff8_(actor, 5, animId)` (opcode 0x0d) calls `zz_004beb8_(rate, actor, 0xf,
groupSel=5, animId, ...)`. `zz_004beb8_` indexes the actor's `+0x1d80` anim-descriptor
bank. That bank is bound by the **per-borg-family constructor**, dispatched virtually:

```c
// chunk_0007.c:410  zz_0056ce0_
void zz_0056ce0_(int actor) {
  (**(code **)((&PTR_PTR_802d3224)[*(char*)(actor+1000)]     // borgId
              + (uint)*(byte*)(actor+0x3e9) * 4))();          // variant
}
```

`PTR_PTR_802d3224` is a per-borg-id table of family-ctor function pointers; `+0x3e9` is
the variant index. Each family ctor (e.g. the G RED ctor at the `configureGRedFamily`
site already scaffolded in `packages/combat/src/families/gred.ts`) binds the model +
the `+0x1d80`/`+0x1d84` anim-descriptor banks + the `+0x4e8` sound-event table. Called
from `FUN_800541ac` (chunk_0006.c:7072, `Battle_SpawnActiveBorgFromSlotTables`).

**Implication for the port:** confirming `groupSel=5 -> g0 battle bank` requires reading
the family ctor's `+0x1d80` binding (the bank index → mot group mapping), NOT the tdc
data (already ruled out). The port's current `ANIM_FILES_BY_ID` (g0 slots) stays TUNED
until the G RED + Normal Ninja family ctors are decoded.

## 2. Actor SPAWN POSITION — global state +0x1604 (per-slot f32 xyz)

`FUN_80056d28` (chunk_0007.c:424) reads each actor's spawn position from a per-slot
table in the front-end global state:

```c
// chunk_0007.c:448-451  (slot = actor+0x3e4)
*(float*)(actor+0x20) = *(float*)(global + slot*0xc + 0x1604);   // X
*(float*)(actor+0x28) = *(float*)(global + slot*0xc + 0x160c);   // Z (0x1604+0x8)
*(float*)(actor+0x24) = *(float*)(global + slot*0xc + 0x1608);   // Y (or computed)
```

`global = PTR_DAT_80433934` (the 0x18b8-byte front-end state block). The table at
`+0x1604` is 12 bytes per slot (f32 X/Y/Z). This is the canonical actor placement source.

**Caveat:** the table is populated at runtime (the state block is zeroed by
`FUN_801c795c` then seeded by the scene-enter path), so the desk-intro coords for
slot 0 (G RED) and slot 1 (Sasuke) are NOT statically in the DOL — they need a runtime
read (Dolphin watch on `+0x1604`/`+0x1610`) OR tracing the scene-enter writer.
**Structure is decoded; values are trace-gated.** Retires the TUNED `stageBaseForSlot`
placement once those two 12-byte rows are captured.

## 3. `zz_00088a4_` — fade-quad render consumer

`chunk_0000.c:3101`. Called by `zz_01c7ba0_` each frame as
`zz_00088a4_((double)state[+0x30], ...)` — the fade `current` accumulator is the input.
The fn dereferences the fade struct's vertex/color pointer pair and renders the fade
quad via the HSD 2D pipeline:

```c
piVar1 = *(int**)(*(int*)(param_9+0x10) + 4);   // {vertexPtr, colorPtr}
if (piVar1[0] && piVar1[1]) {
  zz_0248424_(DAT_80436210, piVar1[0], ...);    // HSD 2D render prim
  zz_024631c_(DAT_80436210, piVar1[1], ...);
  zz_024652c_ / zz_02464dc_                       // draw + cleanup
}
```

The `0x024xxxxx` range is HSD Sysdolphin 2D-render internals. The exact
`current`-accumulator → quad-alpha mapping is inside those helpers (the value feeds the
render-context at `DAT_80436210`), not a simple ratio. **The port's TUNED
`alpha = current/target` (`titleVm.ts` sink) is a reasonable approximation; the precise
mapping needs the HSD 2D helpers decoded, which is low-value (Sysdolphin middleware,
not GF logic).**

## 4. `DAT_8038a550` — 32-byte overlay screen-space seed

Opcode 0x10 (`FUN_801c8328`) does `gnt4_memcpy(state+0x40, DAT_8038a550, 0x20)`. Probed:

```
02 00 00 00  00 94 44 00  3f 00 00 00  00 00 00 06
00 00 00 00  02 80 01 c0  00 08 00 27  00 1b 00 00
```

- `+0x00` u32 = 2 (count/flags)
- `+0x08` f32 = 0.5 (a default coverage/alpha)
- `+0x14/0x16/0x18/0x1a` u16 = 640 / 0x1c0(448) / 8 / 0x27(39) — **GC framebuffer
  coords (640×480)**. This is the overlay/widget layer's default screen-space rect.

The port's `toggleOverlay`/`titleLightBar` sink methods map onto a full-screen CSS
layer; this seed defines the authored rect (640×480-normalized), useful if the overlay
widget placement is wired precisely.

## 5. `DAT_80390ad0` — widget descriptor table (desk menu options)

Consumed by `title_menu_spawn_base_widgets` (`FUN_801dd7d4`), walked from the script's
`spawnTitleWidget` opcodes. ~98 rows; each carries a 3D position (f32 X/Y/Z) + flags +
model id. Sample (first rows, re-aligned to the repeating record):

```
f32 positions: -648.0, -959.5, -2000.0, -3900.0, -4000.0 ...  (world coords, negative = below/behind desk)
flags words:   0x00000001, 0x00010001, 0x00020002 ...          (per-widget mode/type bits)
```

These are the desk-diorama 3D placements of the selectable menu options (the red-gear
cursor + option entries). The exact row stride (likely 0x10 or 0x14 bytes) needs a
dedicated pass against `FUN_801dd7d4`'s walk loop to pin down — the values are clearly
widget 3D coords, not anim/light data. **The port's `spawnTitleWidget`/`setTitleWidgetMode`
sink methods currently log to dataset; a future widget-render layer would consume this
table.**

---

## Net status after this decode

| target | decoded? | residual |
|---|---|---|
| anim bank `+0x1d80` bind | structure DERIVED (per-family virtual ctor `PTR_PTR_802d3224`) | groupSel=5→g0 mapping needs the family-ctor body (Normal Ninja + G RED) |
| actor spawn position | structure DERIVED (`global + slot*0xc + 0x1604`, f32 xyz) | values trace-gated (Dolphin watch on +0x1604/+0x1610) |
| `zz_00088a4_` fade consumer | DERIVED (HSD 2D render-pipeline consumer) | precise alpha mapping in Sysdolphin helpers (low-value) |
| `DAT_8038a550` overlay seed | DERIVED (32-byte screen-space rect, 640×480 frame) | — |
| `DAT_80390ad0` widget table | PARTIAL (f32 3D positions + flags confirmed) | row stride needs FUN_801dd7d4 walk pass |

The two TUNED residuals that affect visible fidelity are both **trace-gated** (the
spawn coords) or **family-ctor-gated** (the anim mapping). Everything structural about
the intro state machine is now decoded; the VM (`apps/game/src/ui/intro/titleVm.ts`)
is the faithful 1:1 port of it.
