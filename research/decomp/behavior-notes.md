# Gotcha Force (GG4E / NTSC-U) — Behavior Decompilation Notes

Source: `user-data/GG4E/disc/sys/boot.dol` (3,888,928 bytes, GC DOL, big-endian PPC Gekko).
Symbol map: `research/symbols/GG4E-CSM-20220412.map` (5,897 symbols).
Tooling used: **Capstone 5.0.1** (`CS_ARCH_PPC`, `CS_MODE_32 | CS_MODE_BIG_ENDIAN`) for the bulk
disassembly, plus a hand-written manual decoder (`scratchpad/ppc.py`) for the Gekko FP /
paired-single opcodes Capstone silently skips (notably `fcmpu`, `fsubs`, `lfs`/`stfs` in some
forms, `ps_*`). No Ghidra / decomp-toolkit was available or installed.

This is **disassembly + structural inference**, not true C decompilation. Confidence is marked
per item. Raw dumps live alongside this file in `research/decomp/`.

---

## 1. Memory map (DOL header parsed; file-offset ↔ runtime-address)

| sec | kind | file off | runtime addr | size | runtime end |
|-----|------|----------|--------------|------|-------------|
| 0 | text | 0x000100 | 0x80003100 | 0x0024e0 | 0x800055e0 |
| 1 | text | 0x0025e0 | 0x800055e0 | 0x2aab80 | 0x802b0160 |
| 7 | data | 0x2ad160 | 0x802b0160 | 0x000020 | 0x802b0180 |
| 8 | data | 0x2ad180 | 0x802b0180 | 0x000020 | 0x802b01a0 |
| 9 | data | 0x2ad1a0 | 0x802b01a0 | 0x00acc0 | 0x802bae60 |
| 10 | data | 0x2b7e60 | 0x802bae60 | 0x0f42c0 | 0x803af120 |
| 11 | data | 0x3ac120 | 0x804335a0 | 0x002b20 | 0x804360c0 |
| 12 | data | 0x3aec40 | 0x80436a20 | 0x006ae0 | 0x8043d500 |

entry = 0x80003154 (`start`), bss = 0x803af140 size 0x8e3e8.

**Almost all executable code is in section 1** (0x800055e0 – 0x802b0160). The two tiny data
sections 7/8 (size 0x20 each) are the read-only and read-write **small-data (SDA) anchors**.

**SDA base register r2 = 0x8043ea20** (CONFIRMED). Derived from the invincibility write:
`lfs f0, -0x75d8(r2)` must resolve to the 60.0 constant, so `r2 = 0x80437448 + 0x75d8 = 0x8043ea20`.
Reading `-0x75d8(r2)` back yields exactly 60.0. (r13 SDA2 base not separately needed here.)
Helper: `scratchpad/dol.py` (`addr_to_off`, `read_u32`, `read_f32`).

### Seed-anchor validation — ALL PASS (Confirmed)
- `0x80437448` holds float **60.0** exactly. ✔
- `0x8005d4b0` = `d0030720` = `stfs f0, 0x720(r3)` — a valid instruction storing the timer. ✔
- `0x8005c7d8` = `d01f0720` = `stfs f0, 0x720(r31)` — store 0.0 to same field. ✔
- `0x80055c00` = `d01f0720` = `stfs f0, 0x720(r31)` — write-back inside the countdown. ✔

The disassembly is correctly aligned; all three anchors reference **struct offset 0x720**.

---

## 2. The symbol map is a GNT4 map — important caveat

The map (`GG4E-CSM-...map`) is dominated by **`gnt4-` / `gnt` / HSD / SDK** names. Of 5,897
symbols, ~1,281 are "named" but almost all are **engine-library / SDK** routines (Metro TRK
debugger, OS, AI/DSP audio, GX, PSMTX/PSVEC math, and the full HSD scene graph). Game-specific
Gotcha Force logic functions are **unnamed** (`zz_<addr>_`). So names help identify the *engine
plumbing*, not the gameplay code — gameplay had to be located via the seed anchors and structural
analysis.

### Key consequence: the engine is HAL **HSD (Sysdolphin)** — same family as Melee / Kirby Air Ride
The map contains the complete HSD object suite (addresses NTSC-U):
- `HSD_JObjMakeMatrix` @ 0x8024d224, `HSD_JObjSetupMatrix_` @ 0x8024f5c8, `JObjAnimAll` @ 0x8024ebc8,
  `HSD_JObjAnim` @ 0x8024ea64, `HSD_JObjDispAll` @ 0x8024f07c (joints / skeleton).
- `HSD_AObjInterpretAnim` @ 0x80243bd0, `HSD_AObjReqAnim` @ 0x80243b90 (animation objects).
- `HSD_FObjInterpretAnim` @ 0x80249ac4, `FObjLoadData` @ 0x802489f4 (keyframe/curve tracks — FObj).
- `HSD_DObj*` / `HSD_MObj*` / `HSD_TObj*` (display/material/texture objects).
- `cPoseAccumulator::GetNodeMatrix` @ 0x8022caf8, `cCameraManager`, PSMTX/PSVEC/QUAT math.

**This strongly supports the project's HSD lead and is directly relevant to the unsolved 3D model
format**: the model/animation data is HSD-structured (JObj tree + DObj/MObj + FObj keyframe
tracks). The public HSD documentation and the Melee decomp can be used as a reference port instead
of reverse-engineering the format cold. (Confidence: **Confirmed** the library is HSD; the on-disc
model files being HSD-`.dat`-style is **Likely** and worth a separate verification pass.)

---

## 3. Active-borg / character struct (located via the 0x720 invincibility writes)

The borg instance pointer is passed in **r3** and saved to **r30/r31** in the per-frame
functions. The invincibility timer is at **+0x720**. Harvesting every base-relative load/store
across the borg state machine (0x8005cc00–0x8005ec04, see `borg-struct-offsets.txt`) plus
engine-wide pattern scans yields the layout below.

### Inferred struct layout (offsets from borg base)

| offset | type | evidence | meaning (confidence) |
|--------|------|----------|----------------------|
| 0x044 / 0x048 / 0x04c | f32 ×3 (vec3) | accessed as a group 1081× engine-wide; very high R/W traffic | **position / translation vec3** (Likely). 0x048 also scaled by a constant on death (shrink). |
| 0x058 / 0x05c / 0x060 | f32 ×3 | adjacent float cluster, R/W in state machine | secondary vec3 — **velocity or target/aim vec3** (Speculative) |
| 0x06c | f32 | read-only in handlers | a scalar (radius/scale?) (Speculative) |
| 0x072 | s16 | 23 reads / 8 writes; `0x72(r) += 0x4000`-style rotates | **heading / facing yaw** (fixed-point angle, 0x10000 = 360°) (Likely) |
| 0x07c–0x080 | s16 | written in pairs | aux angles / target heading (Speculative) |
| 0x0b4 | f32 | 11 reads | a per-frame scalar (Speculative) |
| 0x190 | u8 | flag | (Speculative) |
| 0x272 | s16 | cleared when 0x720 hits 0 | **invincibility/active flag** tied to the timer (Likely) |
| 0x284 | s16 | 14 reads | a base index / id used in heading math (Speculative) |
| 0x544 | s8 | **344 accesses engine-wide**; primary `switch` selector | **main state / action enum** (Confirmed central) |
| 0x550 / 0x552 | s16 | R/W in state machine | sub-state / timers (Speculative) |
| 0x568 / 0x56c / 0x570 | f32 ×3 | float cluster | another vec3 (aim/knockback?) (Speculative) |
| 0x591 | s8 | 7 reads, drives branches | **input/command or attack-type selector** (Likely) |
| 0x5aa / 0x5ac / 0x5ae | s16 | heading-derived (`0x72 + …`) | computed facing / muzzle angles (Likely) |
| 0x5e0 | u32 | 20 R / 20 W; `oris 0x200` etc. | **status bit-flags word** (Confirmed it is a flags word) |
| 0x6b4 | s16 | gates a velocity scale | state/anim sub-flag (Speculative) |
| 0x720 | **f32** | the 3 seed anchors | **wake-up / hit invincibility timer** (Confirmed) |
| 0x1cf0 | s8 | read, `== 1/2` branches | rendering/visibility or facing mode (Speculative) |
| 0x1d0e / 0x1d0f / 0x1d10 | s8 | several reads | input button/state bytes (Speculative) |
| 0x1dcc | f32 | the per-frame subtrahend in the countdown | **timer decrement / game-speed step** (Confirmed role) |
| 0x1dc8 / 0x1dd4 / 0x1d9c… | f32 | float params near 0x1dcc | physics/animation tuning scalars (Speculative) |

Full harvested table: `research/decomp/borg-struct-offsets.txt`. HP was **not** positively
identified — no `hp/damage/life` symbols exist and no single halfword decrement-to-death pattern
was isolated in the time budget. State 0x544 is the death/respawn driver; HP is **Likely** one of
the unmarked s16 fields near 0x550/0x5aa but this is **unconfirmed** — do not port a guessed HP
offset.

---

## 4. Per-function analysis

### (a) Invincibility timer — fully decompiled (Confirmed)

**Set to 60.0 — `0x8005d494`** (per-state handler entry; the function whose dispatch is `switch
(borg[0x544])`). First thing it does:
```
0x8005d494  stwu r1,-0x10(r1); mflr; ...
0x8005d49c  lfs  f0, -0x75d8(r2)      ; f0 = 60.0   (const @ 0x80437448)
0x8005d4b0  stfs f0, 0x720(r3)        ; borg.invinc_timer = 60.0
0x8005d4b4  lbz  r4, 0x544(r3)        ; switch(state) ...
```
So entering this state sets ~60 frames (~1 s @ 60 fps) of invincibility.

**Clear to 0 — `0x8005c7d8`**: `lfs f0,-0x75dc(r2)` (=0.0) then `stfs f0,0x720(r31)` — a state
that ends invincibility immediately.

**Countdown — `0x80055c00`** (CONFIRMED, fully decoded; raw in `invincibility-disasm.txt`):
```
f2 = borg[0x720]                      ; current timer
f1 = 0.0                              ; const -0x77d0(r2)
if (f2 > 0.0) {
    f0 = f2 - borg[0x1dcc]            ; timer -= per-frame step  (0x80055c00 = the stfs)
    borg[0x720] = f0
    if (f0 <= 0.0) {                  ; clamp
        borg[0x720] = 0.0
        borg[0x272] = 0               ; clear invincibility flag (s16)
    }
}
```
**Port-ready.** Algorithm: per-frame, if timer>0 subtract the global step (`borg[0x1dcc]`, ≈1.0
per frame) and clamp at 0, clearing the linked flag. The "60" is frames, not seconds.

### (b) Borg main state machine — `0x8005cc00` (`zz_005cc00_`) and `0x8005d494`
Inputs: r3 = borg*. Dispatches on `borg[0x544]` (signed). Each case manipulates heading
(`0x72`, `0x5aa/5ac/5ae`), sets status bits in `0x5e0`, and calls shared helpers (below). The
0x8005cc00 case handles a counter at `0x544` incrementing and writing flags. `0x8005d494`
handles cases 0/1/2/4 with movement and the invincibility set. (Disassembled head in
`borg-statemachine-head.txt`.) Confidence: structure **Confirmed**, exact per-state meaning
**Likely/Speculative**.

### (c) Shared borg helpers (called with r3=borg throughout the state machine)
- `0x800670dc` (`zz_00670dc_`) — called with `(borg, s16 angle)`; **Likely a heading/turn setter**.
- `0x80066ec0` (`zz_0066ec0_`) — `(borg, int mode)`; **Likely an animation/action request** (mode
  constants 2,0x10,0xf passed). 
- `0x80066f1c` (`zz_0066f1c_`) — `(borg)`; called after the above; **Likely "apply/advance current
  action"**.
- `0x8005f188` (`zz_005f188_`), `0x8004cd24` (`zz_004cd24_`), `0x80046510` (`zz_0046510_`,
  arithmetic on angles), `0x800677b0` (`zz_00677b0_`, returns bool) — secondary helpers.
These are the highest-value unnamed functions to decompile next for animation/movement.

### (d) Animation application — HSD pipeline (Confirmed library, not yet traced to borg)
Per-frame animation is driven by the HSD AObj/FObj/JObj functions (section 2). The chain is the
standard HSD one: `HSD_AObjInterpretAnim` advances an animation's frame and evaluates its FObj
keyframe tracks (`HSD_FObjInterpretAnim`), which drive JObj transforms; `HSD_JObjAnim` /
`JObjAnimAll` apply them, `HSD_JObjMakeMatrix` builds each joint's local matrix, `HSD_JObjDispAll`
renders. The borg's per-state code selects *which* animation via the helper at 0x80066ec0 and a
frame/anim id field. **Port note:** reuse a known HSD/Melee animation reference rather than
re-deriving FObj curve interpretation.

### (e) Movement / flight physics (Likely — via HSD/PS vector math, not scalar)
No simple `pos += vel` scalar triple exists in the borg code; position (0x44/0x48/0x4c) is updated
through the paired-single / `PSMTXMultVec` / `PSVECAdd` math path (those symbols are present and
heavily called). Gravity/dash constants live in the SDA float pool and the `0x1dXX` struct block.
This area needs a focused follow-up; current confidence is **Speculative** on exact formulas.

### (f) Damage calc — NOT isolated (honest gap)
No damage/HP symbols; HP offset unconfirmed (see §3). Death is mediated by state `0x544`. Needs a
dedicated pass tracing what writes the death state.

### (g) Audio / music triggers (Confirmed library entry points)
Engine uses GC **AI/DSP streaming** + sequence audio: `AIInit`/`AIStartDMA`/`AISetStreamPlayState`
/`AISetStreamVolLeft` (0x802146xx–0x80214xxx), `sndSeqContinue` @ 0x801c7b68,
`THPSimpleAudioStop` @ 0x8008e7a0, `PlatAudio::IsSFXPlaying` @ 0x80018c58,
`__OSInitAudioSystem`/`__OSStopAudioSystem`. `AnimAudioEventLookup` (`nlQSort<AnimAudioEventLookup>`
@ 0x801a7640) shows **animations carry audio-event tables** (footstep/SFX keyed to anim frames).
Gameplay SFX/music triggers route through `PlatAudio` and these AI/seq calls; the specific
trigger sites are unnamed and not yet traced.

---

## 5. Prioritized port list (most port-worthy first)

1. **Invincibility timer (0x720) + countdown @ 0x80055c00** — fully decompiled, exact, trivial to
   port. Confirms the `(timer, decrement, flag-clear, clamp)` pattern reused by other timers.
2. **Borg state machine dispatch on 0x544** (`0x8005cc00`, `0x8005d494`) — the spine of all borg
   behavior; everything else hangs off it. Port the `switch` skeleton + the field meanings in §3.
3. **Animation request/apply helpers** `0x80066ec0` + `0x80066f1c` (+ `0x800670dc` heading) —
   small, called everywhere, define how a state picks/advances an animation and facing. Decompile
   these next.
4. **HSD AObj→FObj→JObj animation evaluation** (`HSD_AObjInterpretAnim`, `HSD_FObjInterpretAnim`,
   `HSD_JObjMakeMatrix`) — don't re-derive; map the borg's anim ids onto an HSD reference impl.
   This is the bridge to the unsolved model-format problem.
5. **Movement / heading math helper `0x80046510`** (angle arithmetic) + the PS-vector position
   update path — needed for dash/flight feel; partially understood, needs one more focused pass.

---

## 6. Honesty / limitations
- Capstone correctly disassembles integer/branch PPC but **drops Gekko FP and paired-single ops**;
  those were hand-decoded (`scratchpad/ppc.py`). The integer control flow and all load/store
  offsets (the load-bearing part for struct layout) are reliable.
- No decompiler (Ghidra/dtk) was available, so §4 is disassembly-grounded inference, not C output.
- The symbol map is a GNT4/engine map: it names **engine/SDK** code, **not** Gotcha Force gameplay.
  Every gameplay claim here is anchored on the validated 0x720 seeds + structural evidence, with
  per-item confidence. **HP/damage exact offsets and movement formulas remain unconfirmed — do not
  port guessed values for those.**

Artifacts: `borg-struct-offsets.txt`, `borg-statemachine-head.txt`, `invincibility-disasm.txt`
(this dir). Scripts: `scratchpad/dol.py`, `disasm.py`, `ppc.py`, `offsets.py`.
