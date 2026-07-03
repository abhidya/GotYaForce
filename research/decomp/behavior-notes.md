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

### (f) Damage calc — HP field CONFIRMED (2026-07-01, live capture); formula still open

**HP display field — Confirmed by two independent methods.** A 16-bit unsigned int mirrored at
five fixed addresses tracks the on-screen HP gauge:

- `0x803b069c`, `0x805dbf86`, `0x805f3850`, `0x805f3858`, `0x805f385c`
  (the last three tightly clustered: `+0`, `+8`, `+12` bytes apart).

Evidence:
1. **Static, offline** — a 6-save-state MEM1 diff (`user-data/GG4E/traces/*` extended with a
   fresh live session's before/after-damage and before/after-death saves) found this exact
   5-address set moving `196 → 180 → 171` in lockstep across the session, stable everywhere
   else — i.e. it only changes at the labeled damage events, nowhere else in ~2M bytes of
   session-wide churn.
2. **Live, in-game** — Dolphin's Cheats Manager (Cheat Search, 16-bit unsigned int, value =
   on-screen HP gauge, iteratively refiltered across two hits) converged to the **identical
   5-address set** independently, in a separate play session from the static one above.

Because this exact address set is unchanged across two unrelated sessions/saves, it is a
**fixed/global mirror** (almost certainly a HUD/status-display copy of the active borg's HP),
not a field inside the dynamically-allocated per-borg struct this section originally went
hunting for (the one anchored on `base+0x044` position / `base+0x544` state / `base+0x720`
timer — that struct's base is still not pinned, see §3/§3.4). Functionally this is enough to
*read* live HP for porting/verification purposes even though it may not be the single
"authoritative" copy the game logic itself mutates first.

**Still open: the actual mitigation formula.** Locating the field is not the same as knowing
the arithmetic. To solve for real coefficients (replacing `packages/combat/src/constants.ts`'s
`DAMAGE`/`MELEE`/`SHOT` TUNED block), take 2-3 more controlled hits with the attacker's
`attack`/`shot` stat and the defender's `defense` stat known (from `packages/assets/data/borgs.json`
or `research/symbols/NTSC_Borgs.csv`), reading this same 5-address HP set before/after each hit.
With HP deltas for a few different attacker/defender stat pairs, the linear formula's
coefficients can be fit directly — no further live debugging/disassembly needed for this part.

**Recovery plan for the formula itself (still available if stat-pair fitting is inconclusive):**
`research/traces/GG4E-dol-trace-playbook.md` + `research/traces/GG4E/breakpoints-watchpoints.json`
define a GDB-based capture (`"damage"`/`"melee"` breakpoint groups) that backtraces the exact
write instruction to this HP field, exposing the literal arithmetic instructions rather than an
empirically-fit approximation. Now that the field address is known, that trace no longer needs
the `hp-field` runtime-derived watchpoint (the biggest unknown before) — it can watch these five
addresses directly.

Once either path lands, promote `packages/combat/src/constants.ts`'s `DAMAGE`/`MELEE`/`SHOT`
fields from TUNED to DERIVED and cite the evidence here.

**Stat-pair fitting attempted (2026-07-01) — result: contradicts the simple-stat-scaling model.**
Real, human-observed single/near-single-hit HP deltas were collected in live Challenge-mode play
(defender always G RED, `pl0615`, defense=3 — held constant across all samples):

| Attacker | Stat | Hit type | HP delta | Confidence |
|---|---|---|---|---|
| Death Borg Gamma (`pl0206`) | attack=2 | melee (confirmed 1 hit) | -3 | high |
| Death Borg Delta III (`pl030d`) | attack=2 | melee, 2 hits | -7 total (~3.5/hit) | medium |
| Death Borg Delta II (`pl0303`) | shot=3 | 1 bullet ("I think") | -4 | medium |
| Death Borg Beta II (`pl0105`) | shot=2 | 1-2 bullets | -8 | low |
| Death Borg Delta (`pl030c`) | attack=1 | melee | -11 | low — pre-hit HP unconfirmed, likely bad sample |
| G RED vs G RED (Versus mode) | attack=4 | sword swing | **-53** | high (isolated 1v1, no other combatants) |

The two attack=2 samples (Gamma, Delta III) agree well with each other (~3-3.5), but attack=4
(G RED) does **15x** that, not the ~2x a linear `base + attack×coefficient` formula would predict.
This is not attributable to hit-count miscounting alone.

**Why, per external sourcing:** the Virtual World R.E. community wiki
(<https://wiki.re.virtualworld.fr/index.php/Borg_-_data_file>, the longest-running dedicated
Gotcha Force RE project) documents the same `plxxxxdata.bin` offsets this project already
extracts (`defense`/`shot`/`attack`/`speed` at 420-423) and explicitly labels them **"valeur du
menu -> collection -> vue borg uniquement"** — i.e. these fields are collection-menu display
values, not confirmed inputs to the live combat formula. That is consistent with (and a plausible
explanation for) the contradiction above: real per-move damage may be a value baked into
`plxxxxhit.bin`'s per-action records, independent of the simple 0-10 box stat.

**`plxxxxhit.bin` remains undecoded community-wide, not just in this project.** Their
`Implementations` page (<https://wiki.re.virtualworld.fr/index.php/Implementations>) confirms
`plxxxxhit.bin` (`hit.bin`, position 002 in every borg's `.pzz`) is a real, always-present file,
but there is no wiki page decoding its record fields — no damage/hitbox semantics published
anywhere the wiki links, including the Melee/HSD community references it points to
(UnclePunch's [HSD-Documentation](https://github.com/UnclePunch/Training-Mode/wiki/HSD-Documentation),
PsiLupan's [FRAY](https://github.com/PsiLupan/FRAY) Melee decompile). This project's own
`research/format-specs/hit-bin-format.md` independently reached the same wall (container format
known: 32-slot remap + 0xF4-byte records; field semantics unknown). Spot-checking the specific
borgs above found the four low-tier Death Borg variants (Gamma/Delta/DeltaII/BetaII) have only
3 populated hit.bin records each, two of which are all-zero and one byte-for-byte identical
across all four — suggesting their real attack data isn't even in their own `hit.bin` but in the
shared `comhit.bin`/`comhit2.bin` tables, which use a much larger (0x400-byte) and differently-
keyed remap area not yet matched to a confirmed indexing scheme (a per-borg-`number` byte index
gives a plausible-looking but unconfirmed partial hit: BetaIII(80)->29, Gamma(81)->30,
DeltaII(84)->31 — sequential values, but only 3 of 8 borgs tested resolved, so this is a lead,
not a finding).

**Recommended next step, now more tractable than before:** run the GDB trace
(`scripts/dolphin-gdb-trace.mjs`) with a **write watchpoint directly on the confirmed HP
addresses** (`0x803b069c` or the `0x805f3850/58/5c` cluster) instead of the unresolved
`hp-field` runtime pointer that blocked the original attempt. One hit is enough to catch the
write and backtrace to the real damage-computation function — this reads the actual arithmetic
out of disassembly rather than fitting an approximation to noisy live samples, and sidesteps the
whole undecoded-hit.bin problem.

### (h) HP field and damage application — CONFIRMED live, via Dolphin's own debugger (2026-07-01)

The plan above was executed manually, by hand, in Dolphin's built-in debugger (Debugging UI:
Memory view write-breakpoint + Code/Registers panels) rather than the GDB script — same idea,
GUI-driven instead of scripted. Two separate breakpoint hits, on two different HP mirror
addresses, both landed on real, readable PowerPC disassembly:

**Hit 1 — HUD mirror refresh (confirms `object+0x1C6` is the real HP field, not a guess):**
```
8002bbe8  lha  r0, 0x1C6(r23)     ; r23 = 0x805dbdc0 (stable across the hit — a persistent
                                  ;   battle-context/target pointer, not reallocated per-frame)
8002bbec  sth  r0, 0(r30)         ; r30 == 0x803b069c (our first-discovered HUD address) — this
                                  ;   instruction is a plain copy from the real field to the display mirror
```
`0x805dbdc0 + 0x1C6 = 0x805dbf86` — exactly one of the 5 addresses from the original MEM1-diff /
Cheat Search discovery (see §f). That address is genuinely referenced by the game's own code at
this exact offset — this is no longer inference from RAM diffing, it's read directly from a
live disassembler.

**Hit 2 — the actual damage-application code**, found by setting a new write breakpoint directly
on `0x805dbf86` (i.e. `object+0x1C6`) instead of the HUD mirror:
```
8003d37c  lha  r6, 0x1C8(r3)      ; r6 = 0x9f (159) — a second field on the same object,
                                  ;   2 bytes after HP; role not yet identified (maybe max HP
                                  ;   or a display-cache value — it wasn't used in this subtract)
8003d380  lha  r0, 0x1C6(r3)      ; r0 = current HP
8003d384  sub  r0, r0, r4         ; r4 = 7 — CONFIRMED raw per-hit damage value, read directly
                                  ;   out of the register at the moment of subtraction
8003d388  sth  r0, 0x1C6(r3)      ; store new HP  (r3 = 0x805dbdc0, same object as Hit 1)
8003d38c  lha  r4, 0x1C6(r3)      ; reload new HP
8003d390  extsh. r0, r4
8003d394  bge- ->0x8003D3A4       ; branch if new HP >= 0
8003d398  li   r0, 0
8003d39c  sth  r0, 0x1C6(r3)      ; clamp HP to 0 if it went negative
8003d3a0  b    ->0x8003D3A4
8003d3a4  lha  r4, 0x1C4(r3)      ; a third field, 2 bytes before HP — compared against
8003d3a8  cmpw r4, r0             ;   the new HP value (upper-bound clamp candidate, maybe max HP)
8003d3ac  ble- ->0x8003D3B4
8003d3b0  sth  r0, 0x1C6(r3)
```

**Confirmed, not guessed:**
- `object + 0x1C6` (s16) is the real HP field. `object + 0x1C4` and `object + 0x1C8` are
  neighboring fields on the same struct (candidates: max HP and a display-cache/previous-HP
  value respectively — not yet distinguished).
- Damage application is a plain `HP -= raw_damage; clamp to >= 0 (and possibly <= some field at
  +0x1C4)`. No multiplicative defense term appears in *this* function — mitigation, if any, was
  already baked into `r4` by whatever code computed it before calling this routine.
- One real instance: a Death Borg Gamma hit produced `r4 = 7` as the raw damage value applied.
  This is a harder data point than any of the eyeballed before/after HP readings in §f above —
  it's the literal value the CPU subtracted, not a screen reading that could span multiple hits.

**Still open:** this function receives `r4` (the damage amount) already computed — the
attack/defense arithmetic that produced `7` happens in the *caller*, not here. The next step to
close this out fully is tracing one level further back (Step Out was used to reach the caller at
`PC ≈ 0x8002f1dc`; the actual multiply/mitigation math should be a few instructions before the
`bl` into this subtraction routine). Until that's captured, treat `r4`'s value as confirmed
per-instance ground truth but the general formula (how attack/shot/defense stats produce a given
`r4`) as still open.

**Action item:** promote `WAKE_UP_INVINCIBILITY_FRAMES`-style treatment for this — update
`packages/combat/src/constants.ts`'s damage comment block to note the confirmed HP offset
(`+0x1C6`) and subtract-and-clamp mechanism as DERIVED, while keeping the exact
attack/defense-to-`r4` coefficients as TUNED until the caller-side trace above is done.

### (i) Type-tag match modifier + damage-accumulator fields — CONFIRMED live, same session (2026-07-01)

Continuing the Step-Out trace from §h toward the caller at `PC ≈ 0x8002f1dc`, two more real
findings came out of the same live Dolphin debugging session:

**Type/tag mismatch quarters damage.** A single byte at `object+0x88` is read from both the
attacker and the defender object and compared. On a mismatch, the branch routes through:
```
srawi r0, r4, 2      ; arithmetic shift right 2 == divide by 4 (rounds toward -inf)
addze r0, r0         ; +1 if the shifted-out bits were non-zero and r4 was negative — the
                     ;   standard PPC idiom for a *rounded* signed divide-by-4, not a floor
```
applied to `r4` (the same raw-damage register that gets subtracted from HP in §h) before the
subtract executes. On a match, `r4` passes through unmodified. This is read directly from
disassembly + register panels (r4 observed going from an un-quartered value to a quartered one
across the `srawi`/`addze` pair) — **DERIVED**, not inferred from combat-log arithmetic.

**What is NOT confirmed:** which per-borg field the byte at `object+0x88` actually holds. No
static data file we've found (`plxxxxdata.bin`'s HexWorkshop bookmarks in `tools/NeoGF/data/`,
the Virtual World R.E. wiki) documents a categorical byte at that struct offset, and it was not
directly cross-referenced against a known borg's `type` string during this session (the
breakpoint at the read site did not retrigger before the session moved on — see the "bp is not
triggering" thread). `borgs.json`'s `type` field (`Almighty Type` / `Short range type` /
`Support type` / `Speed type` / `Long range type`, 5 categories) is the only categorical
per-borg tag available in the already-parsed data, so it's used as the best-available **TUNED
hypothesis** for what `+0x88` encodes — plausible (5 types is a clean fit for a small tag byte,
and it would retroactively explain contradictory stat-based damage readings in §f as
type-mismatch quartering rather than stat weirdness) but not verified. Confirming it requires
either reading `+0x88` live for two borgs with a known `type` mismatch, or finding the field in
the static per-borg block.

**Damage-statistics accumulators (not gameplay-relevant, informational only):** two more fields
were touched by the same code path, `object+0x42C` and `object+0x41C`, consistent with running
damage-dealt/damage-taken counters (e.g. for post-battle stats or achievements) rather than
anything that feeds back into the HP subtraction. Not ported — no gameplay behavior depends on
them as far as this trace shows.

**Superseded by §m:** do **not** use `borgs.json.type` as the `+0x88` stand-in. A later direct
Ghidra-export pass found active spawn paths assigning `object+0x88` from match slot/team state,
not the five-value display type.

### (j) Ghidra + GameCubeLoader stood up, damage-formula caller traced to source (2026-07-01)

Following the tool-testing session (research/tools/re-tooling-guide.md), Ghidra 12.1.2 +
Cuyler36/Ghidra-GameCube-Loader were installed for real (not just researched) and used to import
`user-data/GG4E/disc/sys/boot.dol` directly — MD5 `876ef5d9d3b0d6df6684805074fe31bc`, 5803
functions / 5897 symbols resolved immediately from `tools/NeoGF/data/GG4E-CSM-20220412.map` on
import. This replaces hand-reading disassembly with the actual decompiler, and immediately paid
off on the two open items from §h/§i:

**§i's type-mismatch mechanism is now confirmed at the source level, not just disassembly.**
The single caller of the HP-subtract function (`zz_003d344_`, decompiled in full below) is inside
a large per-borg update function at `0x8002e2a8`. Its damage-computation block (~0x8002f0xx)
decompiles to:
```c
uVar10 = -(uint)*puVar17;
if (pcVar16[0x88] != pcVar18[0x88]) {
  uVar10 = ((int)uVar10 >> 2) + (uint)((int)uVar10 < 0 && (uVar10 & 3) != 0);
}
```
`pcVar16` = attacker object, `pcVar18` = defender/self object. This is a byte-for-byte match of
§i's disassembly read (`srawi r0,r4,2` + `addze` = rounded /4), now confirmed in clean C at the
exact offset `+0x88`, with **no other candidate offset or table lookup involved** — it really is
a plain inequality check between one byte on each object. What's *still* not confirmed is what
game data populates that byte for a given borg (see §i) — Ghidra confirms the mechanism and
offset, not the semantic source. The `*(uint*)(pcVar16+0x42c) = ...+uVar10` line right after
matches §i's damage-accumulator finding at `+0x42c` too.

**The real base-damage formula function is now located, and it's substantially richer than the
TUNED linear model.** Two branches feed `uVar10` before the type-check above:
- If a flag byte on the move-data pointer (`puVar17[8] & 2`) is set: `uVar10 = -(uint)*puVar17`
  (the move's first field, a `ushort`, used directly).
- Otherwise: `uVar10 = zz_003cd5c_(puVar17, iVar19, pcVar18)` — a real formula function,
  signature `int zz_003cd5c_(ushort *param_1, int param_2, char *param_3)`. `param_1` is the
  **same per-move data pointer** (`puVar17`) passed into the caller from the current
  attack/move context — this is very plausibly the pointer into `plxxxxhit.bin`/`comhit.bin`'s
  per-move records that the wider community (Virtual World R.E. wiki, `tools/NeoGF`) has never
  decoded (see `research/format-specs/hit-bin-format.md`). Inside, roughly:
  ```c
  fVar1 = (float)*param_1;                              // move's base power field, as float
  if (BASELINE < fVar1) {
    // ... immunity/bit-flag check against param_3 (defender) first ...
    pcVar13 = *(char **)(param_2 + 0x90);                // attacker's equipped-move/sub-object
    dVar14 = fVar1 + fVar1 * K1 * (*(float*)(param_2+0xc4) - K2);   // scales by an attacker
                                                                     // FLOAT stat at +0xc4
    // further modifiers gated on pcVar13 flags (+0x18, +0x6fc, +0x3e6, +0x88) and a
    // multiplier looked up from a small table (PTR_DAT_804335e0) indexed by a bit-derived value
  }
  ```
  This is a multiplicative formula (`power * (1 + coefficient * (statFloat - baseline))`) with at
  least one more table-driven multiplier stage, not the `BASE + stat*PER_STAT` linear shape
  currently TUNED in `constants.ts`. Fully resolving it (naming `+0xc4`, `+0x90`'s sub-struct,
  the `PTR_DAT_804335e0` table, and the named float constants) is real work beyond one sitting,
  but the function is now a known, navigable address (`zz_003cd5c_`) instead of an unresolved
  runtime pointer — the "Still open" item from §h is now "located, not yet fully decoded."

**Action item:** keep `DAMAGE.DEF_PER_STAT`/`MIN_MULT`/`DMG_BASE`/`DMG_PER_STAT` TUNED (the real
formula is confirmed more complex than a linear model, so a coefficient fit wouldn't be
correct); the type-mismatch mechanism/offset can be described as DERIVED-and-source-confirmed
rather than "hypothesis" now, though the *meaning* of the `+0x88` byte is still open. Next
session: decompile `zz_003cd5c_` in full and identify `PTR_DAT_804335e0`'s table contents (likely
5-8 entries — plausibly the type-advantage or rank multiplier table).

### (k) Full-binary bulk decompile persisted (2026-07-01)

Rather than keep pulling one function at a time through the Ghidra GUI, wrote and ran a Ghidra
script (`DumpAllDecompiledJ.java`, source kept in the user's `ghidra_scripts` dir) inside the
already-analyzed `GotchaForce` project that decompiles **every** function in the program and
dumps the C to disk. Result: `research/decomp/ghidra-export/` — 11,972 functions across 80
`chunk_NNNN.c` files plus `_index.tsv` (address/name/chunk-file lookup). See that folder's
`README.md` for how to grep it. This replaces "click through Ghidra by hand" with "grep the
corpus" for any future function of interest — the practical version of a "1:1 source-of-truth
mapping". (Byte-matched recompilation is deliberately skipped, not blocked: it only serves
projects that rebuild the original binary, which a TypeScript port never does.)

Following up on §j's two open call sites using the corpus:

- **`zz_00300bc_` (`0x800300bc`)**, called right before the damage formula, is NOT a
  hitstun/knockback magnitude as guessed — it computes a launch **direction** (yaw/pitch, as two
  shorts) by picking one of five vector sources based on a mode parameter (relative position
  between attacker/victim, a "linked object" position, distance-gated fallback vectors, etc.),
  then applies a per-attack angular offset read from a small array indexed by
  `param_1[0x11]`. So knockback in the real game is a full computed 3D direction, not the flat
  scalar `KNOCKBACK` constants currently TUNED in `constants.ts` — a real port of this would need
  the direction calc, not just a bigger number.
- **`zz_0066298_` (`0x80066298`)**, called from inside the base-damage formula (`zz_003cd5c_`),
  is a genuine 2D lookup table: `table[b0][b1]` where `b0`/`b1` are two bytes read from
  `object+1000` on each borg. This is a **different field** from the `object+0x88` byte used in
  §j/§i's simple mismatch-quarters-damage path — meaning the real game has two separate
  type-interaction systems layered together (a coarse binary match/mismatch check, and a finer
  category×index multiplier table), not the single `type` field currently used as the TS port's
  stand-in. The table's actual contents (`PTR_DAT_802f2e28`) haven't been read yet.

**Action item:** none of constants.ts changed as a result of this — it would be worse to guess at
implementing the two-system type chart or the direction-based knockback without the actual table
values and full angle math, so both stay TUNED/flat pending a follow-up session that reads
`PTR_DAT_802f2e28`'s contents and fully decodes `zz_00300bc_`'s angle-offset table.

**One more relevant data point from finishing `zz_003cd5c_`'s tail:** the `object+0x88` byte is
reused later in the same formula as a small-integer *index* into another per-defender table
(`PTR_DAT_80433950[pcVar10[0x88]]`), not just as the equality check from §j. Later export review
(§m) shows this byte is match slot/team state in active spawn paths, so it should not be modeled
as `borgs.json.type`. The rest of the formula's tail is several more table lookups (attacker
"rank" tables selected by a `-iVar4` index, defender tables keyed by `pcVar10[0x43a]` and
`pcVar10[0x6ca]`) plus the same HP-ratio scaling pattern seen twice — i.e. the real "defense"
effect is spread across multiple rank/category table lookups rather than a single stat-driven
percentage, which is why `DAMAGE.DEF_PER_STAT`/`MIN_MULT` (a flat percentage model) stay explicitly
TUNED rather than being upgraded — the real mechanism doesn't have a percentage to extract at all.

### (l) Real type-matchup data tables extracted from the ROM (2026-07-01)

Read the actual binary data (not just the code that indexes it) behind `zz_0066298_`'s lookup:

- `research/decomp/data/type-category-remap-802f2e28.json` — the raw jagged table at
  `0x802f2e28`: 15 rows (lengths vary 6-44 entries), mostly an identity mapping (row *i* ->
  value *i*) with sparse redirects into shared "bucket" categories. This normalizes whatever raw
  2-byte field lives at `object+1000` down to a canonical 0-19 category before the real lookup.
- `research/decomp/data/type-multiplier-matrix-802c5d60.json` — the actual payoff: a real 20x20
  row-major float matrix (`attackerCategory*20 + defenderCategory`), read directly out of the
  ROM's data section. 26 of 400 cells are non-1.0 (range ~0.75-1.25), the rest neutral. This is a
  genuine, subtle secondary type-interaction bonus/penalty, separate from and layered on top of
  the coarse 4x quarter-damage mismatch check in `zz_002e2a8_` (object+0x88 equality, §i/§j).

**What's still missing to make this usable in the port:** which borg/tribe maps to which of the
20 canonical categories. That mapping lives in whatever per-borg static table populates the
2-byte field at `object+1000` at borg-load time — not yet located. Until that's found, this data
is real but not yet wireable to `borgs.json` IDs. Do not guess a mapping and wire it up; wrong
category assignment would silently misapply real bonuses/penalties to the wrong borgs, which is
worse than the current flat TUNED model.

**Lead for closing this gap (not finished — next session's starting point):** found the
assignment site, `chunk_0006.c:7055` in the export corpus:
`*(undefined2*)(param_9+1000) = *(undefined2*)(PTR_DAT_80433934 + param_9[999]*2 + 0x10)`.
So `object+1000` is copied at load time from a master table at `0x80433934`, indexed by a
single byte read from `object+999` (very plausibly the borg's raw roster/species ID). Reading
`0x80433934` directly out of the ROM shows it holding what look like real pointers (e.g.
`0x803c5420`, `0x803c5400`, decreasing through a small data region), not a flat struct array as
the `+0x114`/`+0x3c`-stride arithmetic seen elsewhere in the code would suggest — the two usages
haven't been reconciled yet (possibly two differently-typed views of the same base, or two
different nearby symbols). Next step: resolve what `0x80433934` (and the `0x803c4e60-0x803c5420`
region it points into) actually holds, and read `object+999` for a couple of borgs with known
identities (a live `dolphin-memory-engine` read during a real match, same technique as
`scripts/dolphin-hp-logger.py`) to anchor at least one confirmed (borg name -> byte value) pair.

**Promising shortcut spotted, then TESTED AND REFUTED (2026-07-01, same day):** hypothesized
`tools/NeoGF/data/NTSC_Borgs.csv`'s `Number` column (matches `borgs.json`'s `number`) was the byte
read into `object+999`. Tested it directly against the ROM and it does not hold — reading
`PTR_DAT_80433934`-relative tables using `Number` as the index produced garbage (values like
128/255, out-of-range for the remap table, no clustering by `Tribe`). While correcting the read
formula (see below) also found that the actual source field, `object+0x3e4`, is fed into
`param+0x3e5 = 1 << cVar1` (a bitmask) in its re-init helper (`zz_00537a8_`) — the shape of a
small **slot/team index (0-7)**, not a per-species roster ID at all. So this whole chain
(`+0x3e4` -> `+999` -> `+1000`/`+0x88` table reads) is very likely indexed by *which battle slot
the object occupies*, not *which borg it is*. The real per-species source (if `object+0x88`'s
value differs between two different borgs in the same slot across matches, which live capture
would need to confirm) must be set from somewhere else, later, at actual character-select/spawn
time — not found yet.

**Correct table-read formulas** (superseding the earlier wrong `0x3c`-stride guess), found in
`zz_00537a8_`'s caller and neighbors (`ghidra-export/chunk_0006.c` ~line 6535-6545): all three
are **flat arrays based directly off `PTR_DAT_80433934`** (not a struct-array with a header, as
previously guessed) — `object+1000` (short) <- `PTR_DAT_80433934[slotIndex*2 + 0x10]`;
`object+0x3ec` (byte) <- `PTR_DAT_80433934[slotIndex + 0xa0]`; **`object+0x88` (the confirmed
type-mismatch byte!) <- `PTR_DAT_80433934[slotIndex + 0xcb]`**. That last one is worth keeping:
it's now proven, at the source level, that `+0x88` is not manually set per-borg-species at all in
*this* code path — it's read from a small per-slot table. Whether a *different* code path (actual
per-borg spawn/load, not this slot re-init) overwrites it with a real species-specific value is
the open question — this function may just be a "clear a slot back to a safe default" helper that
runs before the real borg data gets loaded into it.

**Superseded by §m for `object+0x88`:** a live scan is still useful for anchoring object bases, but
it is no longer the fastest way to answer whether `+0x88` is borg display type. Direct export reads
show active spawn paths copying `+0x88` from `PTR_DAT_80433934[slot+0xcb]`.

### (m) Ghidra-export re-read: `object+0x88` is slot/team state, not borg display type (2026-07-01)

Directly grepping the persisted export after the live-scanner experiment found enough static
evidence to retire the `borgs.json.type -> object+0x88` proxy:

- `chunk_0006.c:7057` (`FUN_800541ac`, active borg spawn/init path) assigns
  `param_9[0x88] = PTR_DAT_80433934[param_9[0x3e4] + 0xcb]` after setting `param_9[999] =
  param_9[0x3e4]` and `object+1000` from the same slot-indexed table.
- `chunk_0007.c:921` (`FUN_80057b78`, another active object init path) repeats the same assignment:
  `*(undefined *)(param_9 + 0x88) = PTR_DAT_80433934[*(char *)(param_9 + 0x3e4) + 0xcb]`.
- `chunk_0048.c:3128`, `3471`, and `3741` do the same copy for UI/preview-style objects using
  `param_9+0x96` as the selected slot.
- `chunk_0048.c:266-312` fills `PTR_DAT_80433934[slot+0xcb]` with `0`, `1`, or `0xff` from
  match/team allocation logic. Earlier initializers (`chunk_0002.c:647`, `726`) set it to
  `slot & 1`. This is the shape of side/team/force state, not a per-species roster type.

So `object+0x88` is still a real ROM byte used by damage/statistics code, but the port must not
map it from the five display strings in `borgs.json.type`. The real subtle type/category matrix
remains the separate `object+1000 -> zz_0066298_ -> type-multiplier-matrix-802c5d60` path from
§l. Next implementation work should focus on resolving `object+1000`/slot roster data and the
full `zz_003cd5c_` formula, not on live-confirming `+0x88` against display type.

### (n) `object+1000` write-path and spawn-ID byte packing resolved (2026-07-01)

Directly answers the Priority-1 open question from `HANDOFF-PROMPT.md` ("resolving what
populates that slot table is the next target"). Full chain, all statically confirmed from the
export + a direct raw-ROM table read (`dol.py`-style, no live capture needed):

- `build_challenge_battle_setup` (`0x801962c4`, `ghidra-export/chunk_0048.c:243`) is the roster
  builder for challenge/force battles. Per slot, it calls `zz_0196eb8_(group)` (`0x80196eb8`,
  `chunk_0048.c:685`) to pick a uniformly-random 16-bit value from a `-1`-terminated array
  reached via `(&PTR_DAT_80380804)[group]`, and stores the result at
  `PTR_DAT_80433934[slotByteOffset*0x348 + 0x1e8]` (the slot's roster-entry table).
- Later in the same function (`chunk_0048.c:377`), that roster-entry value is copied into the
  slot-indexed table read by live gameplay: `*(short *)(PTR_DAT_80433934 + slot*2 + 0x10) =
  *(short *)(PTR_DAT_80433934 + slotRosterOffset + 0x1e8)`. This is the exact write to
  `PTR_DAT_80433934[slot*2+0x10]` that active-object init (`chunk_0006.c` etc.) later copies into
  `object+1000` — closing the loop from "random pool pick" to "the field `zz_0066298_` reads for
  type-category lookup."
- **The 80-entry pool table itself is real roster data, not code**: read directly from
  `boot.dol` at `0x80380804` (80 pointers, one per challenge/mission "group") -> each points to a
  `-1`(`0xffff`)-terminated `short[]` of spawn IDs. Dumped in full to
  `research/decomp/data/spawn-pools-80380804.json`.
- **Spawn-ID byte packing confirmed**: every ID in every one of the 80 pools decomposes cleanly
  as `family = id >> 8` (high byte), `variant = id & 0xff` (low byte) — e.g. group 1 = `[0,1,2,3,4,5]`
  (family 0, variants 0-5), group 5 = `[1024,1026,1028,1029,1031,1033]` (family 4, variants
  `0,2,4,5,7,9`). The union of `family` across all 80 pools is exactly `{0..15}` (16 values) —
  and this is exactly the `(param_1[0], param_1[1])` pair `zz_0066298_` reads from `object+1000`.
  So: `object+1000`'s high byte is the borg's spawn-time *family* (the `b0` row selector into the
  remap table), and the low byte is the *variant-within-family* index (the `b1` column selector).
- **The `0x802f2e28` remap table actually has 16 rows, not 14**: a direct pointer-table read
  (`0x802f2e28`..`0x802f2e64`, 16 valid consecutive pointers, index 16 onward is garbage/invalid)
  confirms two more rows exist past the previously-extracted 14 (`family 14 -> [18]*6`,
  `family 15 -> [19,19,19,19,19,11,19,19]`) that the earlier extraction pass missed, matching the
  16-value family union above exactly. Row length is `(nextRowPtr - thisRowPtr) / 2`, cross-checked
  against `boot.dol` directly. `research/decomp/data/type-category-remap-802f2e28.json` has been
  corrected/extended to 16 rows.
- **Still open** (do not wire without this): which of `borgs.json`'s 208 entries (keyed by
  `plNNNN`/`number`) corresponds to which `family*256+variant` spawn ID. The `number` field is
  almost certainly a separate "GET Data No." collection/gallery index (`pl0000` -> `number: 15`
  doesn't decompose validly against the 16-row/6-44-length family table), not the internal spawn
  ID. The 80 mission pools only sample *subsets* of each family's roster (gaps in variant indices
  are expected, not evidence of a smaller family), so they can't be inverted into a full
  `plNNNN -> family/variant` table by themselves. `borgs.json`'s 20 `tribe` values (Machine Borg
  35, Death Borg 34, Dragon Borg 18, ... down to Idol Borg 1) also outnumber the 16 confirmed
  family bytes, so `tribe` is not a 1:1 stand-in for `family` either — some tribes likely share a
  family byte for type-effectiveness purposes, or a few tribes (very small counts: Idol/Nurse/
  Demon/Bug) are non-selectable/story-only and excluded from the spawn-ID family space entirely.
  **Next step to close Priority 1 fully**: find the per-`plNNNN` static definition table (stats +
  tribe + spawn family/variant, probably near wherever `borgs.json` stat fields like defense/
  attack/speed were originally sourced) — that table, not the mission pools, is what assigns each
  playable borg its `family*256+variant` ID. Do not guess this from tribe order; find the table.

### (o) `zz_003cd5c_` base-damage formula — constants pinned, structure mapped (2026-07-01)

Full read of `0x8003cd5c` (`ghidra-export/chunk_0004.c:6672-6828`), `int
zz_003cd5c_(ushort *param_1, int param_2, char *param_3)` — `param_1` = per-move data pointer
(the `puVar17` from earlier sessions), `param_2` = attacker object, `param_3` = defender object.
All numeric constants below are raw values read directly out of `boot.dol` (not guessed):

- **Base power**: `*param_1` (a raw `ushort`, the move's power stat) is converted to float via the
  classic `(double)CONCAT44(0x43300000, rawInt) - 2^52` bit-trick (confirmed:
  `DOUBLE_80436fb0 == 4503599627370496.0` exactly `== 2^52`). So the formula starts from the
  move's power value, unmodified — no hidden base offset.
- **Zero-power guard**: `FLOAT_80436f68 == 0.0` — if power isn't `> 0`, the function returns 0
  immediately (no damage for 0-power moves/hitless effects).
- **Attacker "stat" scaling**: `dVar14 = power + power*0.5*(attackerFloatStat@+0xc4 - 1.0)`
  (`FLOAT_80436f7c == 0.5`, `FLOAT_80436f78 == 1.0` exactly) — i.e. `power * (1 + 0.5*(stat-1))`
  where `stat` is a float read from attacker's linked-object `+0xc4`, baseline `1.0` = neutral.
  This is a genuine multiplicative stat scale, but the "stat" here is a float field on a *linked
  sub-object*, not directly `borgs.json.attack` (0-10 int) — the int-stat -> this float's mapping
  is still unresolved.
- **"Boost" flag**: object `+0x6fc` byte, when set on the attacker, doubles damage
  (`FLOAT_80436f9c == 2.0`); the same byte on the defender halves incoming damage
  (`FLOAT_80436f7c == 0.5`, reused). Symmetric buff/debuff flag, not yet named.
- **"Rank"/handicap lookup, NOT a raw attack-stat table**: `PTR_DAT_804335e0` is an array of 2
  table pointers, selected by the sign of a per-object signed byte `+0x3e6`
  (`(-cVar2|cVar2)>>0x1d & 4`, i.e. selector is `0` or `4`). The selected table is then indexed
  by `PTR_DAT_80433950[object+0x88]` (the **team/slot byte translated through another small
  table**, not the raw team byte and *not* an attack-stat index). Dumped both tables directly
  from ROM: selector 0 -> `[1.02,1.02,1.01,1.01,1.01,1.01,1.0,1.0,1.0,1.0,0.99,0.99,...]`,
  selector 4 -> `[0.92,0.92,0.91,0.91,0.91,0.91,0.90,0.90,0.90,0.90,0.89,0.89,...]` (both at
  `0x802c4ba0`/`0x802c4c20`). Value range (0.88-1.02) and team-byte indexing strongly suggest a
  **difficulty/handicap damage-output multiplier per player slot**, not a per-borg attack-stat
  curve. This means `borgs.json`'s 0-10 `attack`/`shot` int stats are **not consumed by this
  formula the way `constants.ts`'s `TUNED` `MELEE.DMG_PER_STAT` assumes** — if those stats affect
  damage at all in the real game, it must be through the move-power value itself (`*param_1`)
  varying per borg/move, not a runtime multiplier keyed off a stat number. Not yet confirmed
  either way; flagging so nobody "finishes" this formula by plugging `attack` into the wrong slot.
- **HP-ratio scaling** (confirms the `+0x1c4` claim in `constants.ts`'s header comment, now with
  exact indexing): `hpMirror = (&DAT_803b069c)[defenderLinked+0x3e4]` (yes — `0x803b069c`, the
  already-confirmed live HP-mirror address family from `s4f`, here read through a small
  per-object slot-select byte at `+0x3e4`). If `hpMirror < 201`: `ratio = (hpMirror<<5) /
  maxHp@+0x1c4` (fixed-point /32), clamped to `[1,31]`, then inverted (`32 - ratio`) so **lower
  current HP -> larger index**. That index (0-31) plus a per-move byte (`param_1+3` for the
  attacker branch, `param_1+7`/`(int)param_1+7` for the defender branch) indexes a 2D float table
  (`PTR_PTR_804335e8`/`...f0` families) — i.e. a genuine "comeback"/low-HP damage-scaling table,
  keyed by *both* current HP ratio and a per-move byte, not a flat percentage. Table contents not
  yet dumped (would need the per-move byte's valid range first — see Priority 2 follow-up below).
- **Type-category multiplier** (only applied when both attacker and defender pass validity
  checks): `local_34 = *(short*)(attackerLinked+1000); iVar4 = zz_0066298_(&local_34);` and same
  for defender (`iVar5`), then `dVar14 *= matrix[iVar5*20 + iVar4]` i.e.
  **`matrix[defenderCategory*20 + attackerCategory]`** — the matrix is indexed
  defender-major/attacker-minor, the reverse of the earlier (unverified) guess in
  `type-multiplier-matrix-802c5d60.json`'s original description. Corrected in that file.
- **Same-team (friendly-fire) divisor — this is NOT a "type mismatch"**: `if (attackerLinked+0x88
  == defenderRootLinked+0x88) dVar14 *= 0.25` (`FLOAT_80437024 == 0.25` exactly). Given `+0x88` is
  confirmed (s4m) to be the match slot/team byte, this branch fires when **attacker and defender
  are on the same team** — i.e. it's a friendly-fire damage reducer (25% damage to teammates in
  Force battles), not type-effectiveness. `constants.ts`'s `DAMAGE.TYPE_MISMATCH_DIVISOR` is
  mislabeled — same numeric value (4x divisor = 0.25 multiplier), wrong mechanic name. Renamed to
  `DAMAGE.SAME_TEAM_HIT_DIVISOR` with a corrected comment; **not wired into `combat.ts`** because
  the current sim never calls `applyHit` against a same-team target at all (`isEnemyAlive`/
  `o.team === pr.team` filters exclude teammates from every hit-resolution loop) — the port
  doesn't model friendly fire yet, which is itself a real behavior gap worth a separate decision,
  not something to silently bolt on.
- **A second, harsher block/reflect divisor found**: `if (defender+0x83==0 && move flags &
  0x1000 && (defender+0x59c & 0x1000)) dVar14 /= 40.0` (`FLOAT_80437028 == 40.0` exactly) — a
  ~2.5%-damage-through state, likely a guard/shield/reflect mechanic gated by matching move-flag
  and target-state bits. Not named or ported; needs the `+0x59c`/move-flag-0x1000 meaning traced
  before it's portable.
- **What's still missing before this formula can replace the TUNED linear model**: (1) the
  attacker-float-stat-at-`+0xc4` <-> `borgs.json.attack`/`.shot` correspondence (or proof they're
  unrelated), (2) the per-move-byte domains at `param_1+3`/`param_1+7`/`pcVar13[0x43a]` (needed to
  size/dump the remaining lookup tables), (3) Priority 1b (the `plNNNN -> family/variant`
  roster table). Do not port a partial version of this — see the `constants.ts` header rule.

### (p) `zz_00300bc_` knockback DIRECTION — fully decoded, all 5 modes + angle-offset "table" (2026-07-01)

Priority 3 from `HANDOFF-PROMPT.md`. Full body read from `ghidra-export/chunk_0003.c:8540-8627`
(`void zz_00300bc_(int param_1,int param_2,int param_3)`). Raw dump persisted at
`research/decomp/data/knockback-direction-800300bc.json`.

**Call site found** (the corpus has no direct-name caller because Ghidra didn't attribute a
literal `bl` target label in the decompiled text near it, so it had to be found by reading the
one function known to call it): `resolve_hitbox_target_effects_and_damage` (`0x8002e2a8`,
`chunk_0003.c:7945`):
```c
zz_00300bc_(param_1, param_2, (int)*(char *)(puVar17 + 7));
```
This pins down every previously-open question:
- `param_1`/`param_2` in `zz_00300bc_` are the **same hit-context/target wrapper objects**
  `resolve_hitbox_target_effects_and_damage` itself received — not new objects. `param_1+0x20` =
  attacker object, `param_1+0x24` = attacker's linked/partner object, `param_2+0x20` = defender
  object, `param_2+0x24` = defender's linked/partner object (matches `iVar19`/`pcVar16`/`iVar15`/
  wiring already confirmed for the caller in §j/§o).
- **The mode selector (`param_3`) is `puVar17[7]` as a signed byte** — a field on the *same*
  per-move hit-record (`puVar17`, stride `0x18`, indexed by `param_1[0x11]`) already used by
  `zz_003cd5c_` for base power/flags. This is a different field from `puVar17[0]` (power) and
  `puVar17[8]` (flag bits) documented in §o/§j. So the "5 modes" are an authored per-move choice,
  not runtime-computed.

**The 5 modes** (branch structure: `param_3==2`, `param_3==0`, `param_3==1` (the `-1<param_3` arm
inside the `<2` branch), `param_3==4`, `param_3==3` (the final `<4` catch-all) — confirmed
exhaustive, negative `param_3` is an unreached decompiler artifact per the two
`/* WARNING: Removing unreachable block */` markers, not a real 6th mode):

| mode | source vectors | fallback |
|---|---|---|
| 0 | `attackerObj[0x20..0x2c] - attackerObj[0x2c..0x38]` (float vec3 sub) | if `|v| <= 0.0`: `attackerObj+0x38/0x3c/0x40` |
| 1 | `defenderObj[0x20] - attackerObj[0x20]` (straight attacker→target vector) | none |
| 2 | `param_1[0x30] - param_1[0x3c]` (context-object fields, not resolved sub-objects) | if `|v| <= 0.0`: `attackerObj+0x38/0x3c/0x40` (same fallback as mode 0) |
| 3 | `param_2[100] - param_1[100]` (offset `0x64`, on the raw context wrappers) — the "linked object" mode from the README table | none |
| 4 | cascading 3-way: `attackerObj+0x83==0` -> `attackerObj+0x8dc/0x8ec/0x8fc`; else attacker's linked obj (`param_1+0x24`) `+0x83==0` -> that object's `+0x8dc/0x8ec/0x8fc`; else -> `attackerObj+0x11c/0x12c/0x13c` | n/a (the cascade itself is the fallback chain) |

**Degenerate-vector guard** (applies after any of the 5 modes): if
`|x*x+y*y+z*z| < FLOAT_80436fc0` (confirmed **0.01** by direct ROM read, i.e. `|v| < ~0.1`), the
vector is replaced with the fixed `(0.0, 0.0, -1.0)` (`FLOAT_80436f68`=0.0, `FLOAT_80436f74`=-1.0,
both confirmed by direct ROM read of `boot.dol`).

**Yaw/pitch conversion**: `FUN_800452a0(a,b) = (short)(int)(atan2(a,b) * FLOAT_8043707c)`, and
`FLOAT_8043707c` reads as **10430.3779296875**, confirmed exactly equal to `65536/(2*pi)` to float
precision — the standard radians-to-BAM16 angle conversion (`0x10000` = 360°, same convention
already established for borg heading at struct `+0x72` in §3). Yaw = `atan2(x, z)` stored at
`defenderObj+0x284`; pitch = `atan2(y, |x*x+z*z|)` **negated** and stored at `defenderObj+0x282`
(note: the horizontal term is squared, not square-rooted — reproduced exactly from the decompiled
C rather than "corrected" to a textbook `atan2(y, sqrt(x²+z²))`, since it's unknown whether this
asymmetry is load-bearing for pitch feel; see caveats in the JSON dump).

**The "angle-offset table" from `HANDOFF-PROMPT.md` is now fully decoded — it is not a separate
fixed ROM table at all.** It's two more bytes on the *same* per-move hit-record used for the mode
selector: after computing base yaw/pitch, the function re-reads `record[0x14]` and `record[0x15]`
(signed bytes) and adds each, scaled by `*-0x100` (i.e. placed in the high byte of the 16-bit
angle field — 1 LSB = 256 BAM units = 1.40625°), to yaw and pitch respectively. Because this lives
in the per-move authored data (part of the still-undecoded `plxxxxhit.bin`/`comhit.bin` record
format, `research/format-specs/hit-bin-format.md`), there is no fixed DOL address to dump its
*contents* from — the mechanism (two signed-byte trims, `*256` scale, added post-conversion) is
fully DERIVED; the actual per-move trim *values* are runtime/per-move data, same status as the
move's base-power field already documented as unresolved in §o.

**Linked-object mirror**: if `defenderObj+0x1da & 2`, and the *attacker's* linked object
(`param_2+0x24`, confirmed a different pointer than `param_1+0x24`) has `+0x83==0`, the same
just-computed yaw/pitch are copied onto that linked object too (a paired/partner borg inherits
the primary target's launch direction under a specific effect-flag condition).

**Action item**: this confirms, DERIVED, that knockback in the real game is a full 3D direction
computed per-hit from one of 5 authored vector-source modes plus a per-move angular trim — not a
flat scalar. The actual knockback **magnitude/velocity** (how far/hard the object is launched
once this direction is known) is a **separate, still-unconfirmed** mechanism — this function only
ever writes angle fields (`+0x284`/`+0x282`), never a speed/force value. `MELEE.KNOCKBACK`/
`HITSTUN` in `constants.ts` should be split: the **direction** portion can be upgraded away from
flat-vector TUNED behavior using this decode; the **magnitude** stays TUNED until a separate trace
finds what consumes `+0x284`/`+0x282` to produce an actual velocity impulse.

### (q) Manual "lock-on" / enemy-targeting — searched thoroughly, CONCLUSION: no such system exists (2026-07-01)

Goal (per `HANDOFF-PROMPT.md`): find the real algorithm behind `packages/combat/src/combat.ts`'s
`acquireLock()`/`cycleLock()` (currently TUNED — nearest enemy in a forward view-cone, scored by
`distance*(1+angle)`) and either port the real thing or, if genuinely absent, say so and leave the
heuristic as-is. Conclusion after an exhaustive pass: **there is no button-triggered scan-and-select
enemy-lock mechanic anywhere in the decompiled corpus.** Every "target" field in the ROM is
hit-*reactive* (records who last hit whom, for reaction animations/cues), never scan-*selective*.
This confirms and closes out the three concrete leads `HANDOFF-PROMPT.md` listed.

**Lead 1 — the borg state-machine dispatch (`0x8005cc00`/`0x8005d494`).** Read in full
(`zz_005cc00_`, `chunk_0007.c` around the `zz_005cc00_` header). Its only "target-shaped" data use is
`param_1+0x284` compared against `param_1+0x72` (facing yaw, §3) to compute a turn delta — but
`+0x284` here is *not* an enemy position/direction; tracing every writer of `object+0x284` in the
whole corpus (`grep "0x284) = "` across all chunks) finds exactly one non-knockback writer
(`chunk_0006.c:8070`, `*(short*)(param_1+0x284) = *(short*)(param_1+0x5ae) + 0x2000`, copying the
borg's *own* already-computed muzzle/facing angle `+0x5ae`) plus the knockback-angle writes already
documented in §p (`zz_00300bc_` writes `defenderObj+0x284/+0x282`, a different object than the one
`zz_005cc00_` reads). So `zz_005cc00_`'s use of `+0x284` is "turn toward my last knockback-angle /
copied-facing value," not "turn toward a locked enemy." No target-selection call appears anywhere
in this function.

**Lead 2 — 6-actor table (`DAT_803c4e84`, stride 0x1e00) scanned with distance/angle math gated by
input.** The only two loops over this table in the entire corpus are both inside
`battle_frame_target_action_dispatch` (`0x8002bb14`, `chunk_0003.c:5844-6211`, already indexed in
`research/decomp/index/cpu-ai-evidence.md`): the first (lines 5912-5967) resets per-slot
target/effect globals every frame; the second (lines 5987-6211) computes pairwise
distance-based *push-apart weighting* between overlapping actors (feeds `zz_002caa8_`, a
separation/knockback-blend helper, not a target-lock). Neither loop reads a controller-button
field, and a full-corpus grep for the other ~195 occurrences of `DAT_803c4e84` found every one of
them is a single-slot indexed lookup `(&DAT_803c4e84)[slot]`, never a second independent scanning
loop elsewhere. There is no "press R, scan the 6-slot table for nearest enemy in a cone" function.

**Lead 3 — `object+2000`/`object+0x7d1` (`last_enemy_slot`/`last_enemy_slot_timer`) writers.**
Grepped every write to the backing global `DAT_803b06a8` (the slot-indexed "target object pointer"
array these fields alias) across the whole corpus — exactly two writers exist, both already
identified: (1) `battle_frame_target_action_dispatch` zeroes it every frame
(`chunk_0003.c:5956`), and (2) `resolve_hitbox_target_effects_and_damage` (`0x8002e2a8`) sets it to
the attacker's pointer (`chunk_0003.c:7718`) — already confirmed by the user's own prior check to
be gated behind a per-move flag bit, i.e. a move-specific mark/grapple effect, not general
targeting. `react_to_slot_target_object` (0x8006abd4) and `start_status_reaction_by_side`
(0x8006ace8, chunk_0009.c:1162 — same family, side-variant of the same reaction) are the only
*readers*, and both are alert/notice-animation entry points (confirmed by re-reading
`react_to_slot_target_object` in full: it just enters a status/action state and plays a cue, no
scan). `start_forced_move_to_point` (0x8006ab04) was also checked as a related target-vector
consumer: it receives an already-computed world vector and walks toward it — no scanning of its
own. The companion globals `DAT_803b06c0/c4/c8` ("slot_world_target_vec3") have all their writes
inside the same `resolve_hitbox_target_effects_and_damage` hit-resolution path (copying whichever
object was just involved in a hit), same hit-reactive family.

**Broader sweep (beyond the 3 named leads):** no `PAD`/`SI`-prefixed symbol in `_index.tsv` reads
button state in a targeting-adjacent way (`PADClampCircle` at `0x80212a14`, the one PAD-family hit
near gameplay code, is analog-stick deadzone clamping for rumble-motor processing in
`chunk_0030.c:2442`, unrelated). All ~400 `gnt4_PSVECSquareMag_bl`/`gnt4_PSVECMag_bl` distance-check
call sites across the highest-traffic chunks were sampled; the ones that do keep a running
"nearest" are capsule/segment collision geometry (two pre-supplied line segments, no team filter,
no 6-slot loop) and box-face collision classification, never an actor-vs-actor enemy scan.
`set_slot_action_handler` (`0x8010d880`) and `dispatch_slot_action_update` (`0x800680d4`) — the
final dispatch stage after target/effect resolution — were read in full and are trivial
handler-table wiring with no target logic. `research/decomp/index/cpu-ai-evidence.md`'s own
"Porting Notes" (written by an earlier pass on this same question) independently reached the same
conclusion: *"Do not implement CPU AI as nearest-enemy-only long term... current evidence covers
shared target/effect/action dispatch used by CPU and player-controlled actors"* — i.e. no dedicated
selection brain has ever been isolated in this corpus, by any pass.

**Conclusion, and what this means for the port:** Gotcha Force's "targeting" is entirely
*hit-reactive* bookkeeping (a slot remembers "what/who last hit me" for exactly one reaction
animation), not a player-driven view-cone scan-and-lock-and-cycle system. There is no ROM algorithm
to port in place of `acquireLock()`/`cycleLock()`. **Action item:** `packages/combat/src/combat.ts`'s
lock-on remains explicitly TUNED — not because it wasn't investigated, but because the confirmed
answer is "the real game doesn't have this as a discrete system to derive a formula from." Updated
the header comments in `combat.ts` and `constants.ts`'s `LOCK` block to record this as a checked,
closed question (cite this section) rather than an open TODO, so nobody re-derives it later
believing it's still unknown. If projectile *homing* target selection (as opposed to manual
lock-on) is investigated in a future session, that is a separate question — this section only
covers manual player lock-on/cycle, per the original ask.

### (r) Animation-selection helpers `0x80066ec0`/`0x80066f1c`/`0x800670dc` are heading/turn
interpolation, NOT animation request/apply — correcting §5 item 3 (2026-07-01)

§5's prioritized port list (and §4c) guessed `0x80066ec0` ("Likely an animation/action request")
and `0x80066f1c` ("Likely apply/advance current action") from mode constants (2, 0xf, 0x10) passed
at their call sites, without reading the function bodies. Pulling both out of the Ghidra export
corpus (`ghidra-export/chunk_0008.c`, confirmed via `grep _index.tsv`) shows this guess was wrong:

```c
// 0x80066ec0 (zz_0066ec0_) — full body:
void zz_0066ec0_(int param_1,int param_2) {
  if (param_2 == 0) return;
  *(short *)(param_1 + 0x7e) = (short)((int)*(short *)(param_1 + 0x5aa) / param_2);
}

// 0x80066f1c (zz_0066f1c_) — full body (abbreviated):
undefined4 zz_0066f1c_(int param_1) {
  if (*(short *)(param_1 + 0x7e) == 0) { *(undefined2*)(param_1+0x5aa) = 0; return 1; }
  // else: apply the per-tick delta (param_1+0x7e) to heading (param_1+0x72),
  // decrement the remaining turn amount (param_1+0x5aa), detect overshoot/completion,
  // snap-clamp to the target heading and zero out +0x7e/+0x5aa when done, return 1.
  ...
}
```

`+0x7e` is a per-tick turn-rate delta, `+0x5aa` is the remaining heading delta to a target angle
(already inferred as "computed facing/muzzle angle" in §3's struct table), and `+0x72` is the
already-confirmed heading/facing yaw field (§3). So `zz_0066ec0_(borg, steps)` divides the
remaining turn by a step count to get a per-frame increment, and `zz_0066f1c_(borg)` applies one
increment per call and reports completion — a classic "turn N degrees over M frames" interpolator,
not an animation-bank selector. `0x800670dc` (`zz_00670dc_`) is a related but more complex heading
function operating on the same `+0x72`/`+0x5e0`/etc. fields with `PSVEC`/`PSQUAT` calls, confirming
the same "facing/turn" role guessed in §4c, not animation. Grepping every caller of all three
(`chunk_0007.c`/`chunk_0008.c`) shows them exclusively intermixed with heading/turn-state code
(fields `0x72`, `0x5aa`, `0x5ac`, `0x5ae`, `0x1cf0`, `0x1d10`) in the per-state dispatch around
`0x8005d494`/`0x8005d9d8` — never near an animation-id or anim-frame field. **DERIVED** (full
function bodies read, not guessed from call-site constants).

**Practical effect on this port**: `packages/combat/src/combat.ts`'s existing `b.anim = "idle"` /
`"melee"` / `"shoot"` / `"special"` / `"hit"` / `"down"` / `"death"` / `"wake"` string-tag approach
(state transition directly names the animation slot) was never actually blocked by these three
functions being "unported" — they govern smooth heading rotation, a separate concern from which
clip plays. This closes the §5 item 3 action item without a behavioral port: there is no
mode-to-(group,slot) dispatch table hiding in these functions to port. The real "which clip for
which state" logic lives in the animation-bank (group,slot) addressing scheme documented in
`research/format-specs/borg-animation-banks.md`, not in these helpers.

**What this session actually fixed for animation playback** (the live G Red / `pl0615` bug —
"G Red" here means `pl0615`, borgs.json name literally "G RED", the game's box-art mascot and
`apps/game/src/main.ts`'s `DEFAULT_LEAD`; NOT `pl0000` "NORMAL NINJA", which despite being the
roster's first entry is a different, unrelated borg):
`scripts/bake-all-borg-anims.mjs`'s heuristic `label()` function classified every group-4 bank as
generic `special_s<N>`, including **group 4 slot 0**, which `borg-animation-banks.md`'s own
decomp cross-reference table already identified as **high-confidence knockdown** (matching the
prior human-labeled `down_candidate` anchor — see that file's "Decomp cross-reference" section).
Because slot 0 sorts first, `apps/game/src/main.ts`'s `PREFERRED_LABELS` override for `pl0615`
(and pl0008/pl000c/pl0105/pl0109) pointed their `special` slot at `special_s0` — i.e. **G Red's
Y-button special attack was silently playing his own knockdown/down animation**, while the `down`
combat state (`combat.ts`'s `enterDown()`/`b.anim = "down"`) had no real match at all in
`SLOT_LABELS.down` and fell back to a hit-reaction or death clip instead. Fixed by: (1) relabeling
group-4 slot-0 banks from `special_s0` to `down_s0` in the baker script (for future re-bakes) and
directly in all 101 already-baked `apps/game/public/models/*/anim_index.json` files that had it
(bone/keyframe data unchanged, only the semantic `label` string), (2) adding a `down_s0` pattern to
`SLOT_LABELS.down` in `main.ts` so the `down` state now resolves to the real knockdown clip instead
of a hit/death fallback, and (3) repointing the 5 borgs' `PREFERRED_LABELS.special` overrides
(`pl0615`, `pl0008`, `pl000c`, `pl0105`, `pl0109`) at each borg's `special_s1` bank (confirmed
present in each one's `anim_index.json`) instead of the mislabeled `special_s0`, plus explicit
`down: ["down_s0"]` overrides for the same 5 borgs. Which of `special_s1..s4` is "the" Y-button
special (vs. some other special-move variant) is **not** individually decomp-confirmed — that
choice among the remaining `special_sN` banks stays TUNED, same status `borg-animation-banks.md`
already documents for group-4 slots 1+ in general.

### (s) TUNED-constants audit — `packages/combat`/`physics`/`ai` — most stay TUNED, one real lead found (2026-07-01)

Systematic pass over every `TUNED` field in `packages/combat/src/constants.ts`'s `MOVE`/`JUMP`/
`DASH`/`MELEE`/`SHOT`/`SPECIAL`/`STATE`/`LOCK`/`AI` blocks, checking each against the bulk-decompile
corpus the same way `WAKE_UP_INVINCIBILITY_FRAMES` (struct+0x720) was originally derived. Also
checked `packages/physics/src` and `packages/ai/src`: **neither has any TUNED gameplay constants to
audit** — `physics/src/index.ts` is pure allocation-light Vec3/scalar math (no gravity, speed, or
timing constants live there; those all live in `combat/src/constants.ts`'s `JUMP`/`MOVE`/`DASH`
blocks, already covered below), and `packages/ai/src/index.ts` is an empty stub (`export {}`) — no
AI package code exists yet to audit; `constants.ts`'s `AI` block (`MELEE_RANGE`/`RANGED_RANGE`/
`RANGE_SLACK`/`RETARGET_FRAMES`) is consumed directly by whatever calls into `combat.ts`, not a
separate `packages/ai` implementation.

**One real, address-cited finding — a genuine 60-frame "hit reaction" timer family, NOT safe to
port as MELEE.HITSTUN/SHOT.HITSTUN without more work:** `resolve_hitbox_target_effects_and_damage`
(`0x8002e2a8`, `chunk_0003.c:7995/8009-8010`) sets THREE fields to the exact same confirmed-by-ROM-
read constant `60.0` (`FLOAT_80436fac`, verified via a corrected-path `dol.py` read = 60.0 exactly)
on every non-lethal hit against a living target (gated only on `pcVar18[0x1c6] != 0`, i.e. the
confirmed HP field being nonzero post-hit):
```c
*(float *)(pcVar18 + 0x688) = FLOAT_80436fac;   // chunk_0003.c:7995
...
*(float *)(pcVar18 + 0x684) = FLOAT_80436fac;   // chunk_0003.c:8009
*(float *)(pcVar18 + 0x68c) = fVar6;            // chunk_0003.c:8010 (fVar6 == FLOAT_80436fac here)
```
All three (`+0x684`, `+0x688`, `+0x68c`) are decremented every frame by the SAME confirmed
`+0x1dcc` per-frame step already used by the invincibility timer at `+0x720` (`chunk_0006.c:
7984-8008`, `zz_005568c_` @ `0x8005568c`), clamped at 0 — i.e. structurally identical to the
already-ported `(timer, decrement, clamp)` pattern. This is genuine, address-cited ROM evidence of
*a* 60-frame timer set on hit.

**Why this is NOT promoted to DERIVED for `MELEE.HITSTUN`/`SHOT.HITSTUN` (yet):** two things block
calling this "hitstun" with confidence: (1) `+0x68c` is read back in a completely different function
(`zz_005f00c_`, `0x8005f00c`, `chunk_0007.c:5770`) as one of several inputs to a byte of *input/attack
flags* (`bVar3`), gated behind unrelated bits (`+0x6fd`, `+0x6ff`, `+0x591`) — it is consumed
alongside flag logic that looks like attack-command gating, not a simple "can this borg act"
lockout check. (2) The SAME hit path also increments a genuinely separate 0-99 combo counter
(`+0x6c8`/`+0x6c9`) that rolls into a capped rank byte (`+0x6ca`, capped at `0x3e`=62) driven by two
different per-move-record bytes (`puVar17+2`, `puVar17+4/5`) — i.e. there is a real stagger/combo-
rank system layered on top of the 60.0 timer, and nothing in this trace shows the borg's main state
enum (`+0x544`) being written anywhere in this block. Without confirming which of `+0x544`
(state), `+0x684/688/68c` (timer trio), or the combo/rank byte actually gates "victim can't act for
N frames," porting `60` as `MELEE.HITSTUN`/`SHOT.HITSTUN` would be exactly the "wrong-but-confident"
outcome this repo's convention forbids — a flinch/reaction-timer value dressed up as a confirmed
hitstun duration. **Left TUNED**, with this section cited as the concrete next-step lead (start
from `zz_005f00c_`'s callers and find what reads `bVar3`'s output, or trace every reader of
`+0x544` inside the `0x8005cc00`/`0x8005d494` dispatch to see if a hit forces a specific state
number).

**Everything else audited — confirmed NOT findable in the corpus this pass, left TUNED with
reasons (so future sessions don't re-grep the same dead ends):**

- **`DASH.IFRAMES`/`DASH.COOLDOWN`/`DASH.SPEED`/`DASH.DURATION`**: grepped every write to `+0x720`
  (the confirmed invincibility field) across all 80 chunks — besides the known 60.0 write, only two
  other constants are ever written there: `120.0` (`chunk_0007.c:5495`, `FUN_8005e868`) and a
  conditional `30.0`/`60.0` (`chunk_0007.c:6788/6791`, `FUN_80060b60`). Both functions were read in
  full: `FUN_8005e868` is a scripted spawn/drop-in landing-arc handler (parametric trajectory via
  `zz_0045204_`, gated on state values 0-5, all velocity writes scaled by the same `+0xb4` factor —
  an intro cutscene-style arc, not a player-triggered dash), and `FUN_80060b60` is a respawn/reset
  helper that also zeroes `+0x272`. Cross-checked every function writing both `+0x544` (state) and
  `+0x60` (candidate Y/velocity field) together for a short-burst "dash" shape — only the spawn-arc
  function matched. **No dash/step/dodge state was identified anywhere in the corpus.** Not
  findable this pass; stays TUNED.
- **`JUMP.VELOCITY`/`JUMP.GRAVITY`/`JUMP.MAX_FALL`/`JUMP.BOOST_*`**: searched for a per-frame
  constant-subtraction pattern against a Y-velocity field (gravity accumulation) and for a one-time
  positive-Y-velocity write gated on a "jump" state. The only `+0x60`-field decrement pattern found
  (`chunk_0055.c:2735`, `chunk_0056.c:2797`) is on an object whose neighboring offsets (`+0x146`,
  `+0x1a`, `+0x18`, `+0x70`) don't match the borg struct at all — almost certainly a different
  object type (particle/effect) colliding on the same small offset by coincidence, not a gravity
  accumulator on the borg. `JUMP.GROUND_Y=10` remains the only DERIVED field here (already cited,
  from `ram-trace-analysis.md` §3.1, live-trace Y=10.0 exactly). No gravity/jump-velocity constant
  found; stays TUNED.
- **`MELEE.COOLDOWN`/`SHOT.FIRE_COOLDOWN`/`SPECIAL.COOLDOWN`/`MELEE.DURATION`/`SPECIAL.DURATION`**:
  the `0x8005cc00`/`0x8005d494` dispatch's individual state-number semantics (which numeric case is
  "melee attack" vs. "special" vs. "walk") are still not mapped — §3/§4b already flag this as
  Speculative, and this pass didn't change that. Without knowing which `+0x544` case is which
  attack type, there's no way to isolate an attack-specific cooldown constant from the general
  per-state counters. Stays TUNED; mapping `+0x544`'s case numbers to gameplay meanings is the
  actual blocker (see §5 item 2, already prioritized above this audit).
- **`STATE.DOWN_DURATION`/`DEATH_DURATION`/`SPAWN_DURATION`**: same blocker — these are specific
  `+0x544` state durations, and state-number semantics remain unmapped. Stays TUNED.
- **`LOCK.RANGE`/`LOCK.CONE`**: already fully closed out by §(q) — exhaustively searched and
  confirmed **there is no manual lock-on/targeting system in the ROM to derive a range or cone
  from at all** (every target-shaped field is hit-reactive bookkeeping, not scan-and-select). Not
  re-investigated here; §(q)'s conclusion stands. Stays TUNED, correctly documented as a closed
  question rather than an open one.
- **`AI.MELEE_RANGE`/`RANGED_RANGE`/`RANGE_SLACK`/`RETARGET_FRAMES`**: no `packages/ai` code exists
  (see above) and no CPU-controlled "decide when to retarget" cadence was found; consistent with
  `research/decomp/index/cpu-ai-evidence.md`'s own prior conclusion (quoted in §q) that CPU and
  player-controlled actors share the same low-level dispatch with no isolated "AI brain" function.
  Stays TUNED.
- **`DAMAGE.KNOCKDOWN_DMG`**: traced `zz_003d344_` (the confirmed HP-subtract function) fully — its
  return value is a death flag (HP hit exactly 0), not a damage-magnitude comparison; its caller
  (`resolve_hitbox_target_effects_and_damage`) branches on that death flag to decide whether to
  apply the `+0x684/688/68c` hit-timer trio above, not to pick "knockdown vs. hitstun." No fixed
  damage-threshold comparison (e.g. "if raw damage >= 40, force knockdown") exists anywhere in
  either function. Not findable this pass; stays TUNED.

**Net effect on `constants.ts`**: no fields promoted from TUNED to DERIVED this pass (the one real
lead, the `+0x684/688/68c` timer trio, is documented above and in `constants.ts`'s `MELEE`/`SHOT`
comments as a lead, not applied as a value, per the "never port a half-confirmed formula" rule).
This is itself the honest outcome of the audit: `WAKE_UP_INVINCIBILITY_FRAMES`, HP handling, and
`DAMAGE.SAME_TEAM_HIT_DIVISOR`/`BLOCK_OR_REFLECT_DIVISOR` (already DERIVED) were re-checked against
this pass's findings and nothing regressed — the `+0x1dcc`/`+0x720` pattern they rely on is
reconfirmed by seeing it reused identically for the `+0x684/688/68c` trio.

---

### (t) Weapon/projectile visual FX audit — real ROM textures already wired; no per-move effect-ID
field exists to replace `projectileVisualKindForProfile`'s heuristic; upgraded it to a broader
real-asset-evidence table instead (2026-07-01)

Audited `packages/combat/src/combat.ts`'s `spawnProjectile()`/`projectileVisualKindForProfile()`
and the render-side FX in `apps/game/src/sim/battleScene.ts` (there is no `packages/render`; battle
rendering lives directly in `apps/game/src/sim`) against everything already sitting in
`research/combat-assets/` and `research/asset-inventory/*` (built by `scripts/inventory-combat-
assets.mjs`, `scripts/map-weapon-attachments.mjs`, `scripts/inspect-hit-bins.mjs`, and friends —
all already-run, outputs already on disk, no new scans needed this pass).

**What was already real and wired (not a gap — confirmed by reading `battleScene.ts`):**
- Projectile sprites, muzzle/hit sparks, and the death/hit impact-puff atlas all use genuine
  ROM-extracted textures, not placeholder colors: `apps/game/public/fx/{energy_dot,flame_core,
  muzzle_flash,hit_spark,efct00_atlas}.png`, sourced 1:1 from `ptcl00.txg#5/#1/#6/#2` and
  `efct00.tpl#0` per `research/combat-assets/combat-asset-inventory.md`'s "Browser-ready original
  texture exports" lists. `battleScene.ts`'s `PROJECTILE_TEXTURE_URLS`/`IMPACT_ATLAS_URL`/
  `HIT_SPARK_URL` already point at these real files (not synthesized canvases), and
  `spawnHitSpark()`/`spawnImpact()` already fire on hit-state transitions and projectile
  despawn respectively. This part of the ask was already done; nothing to port here.

**What is a genuine, confirmed-absent gap (not fixed this pass, needs asset-pipeline work, not
gameplay-code work):** real weapon/projectile **3D meshes** (guns, swords, bomb/missile bodies)
are not loaded anywhere in `apps/game/public` — only each borg's own body model
(`apps/game/public/models/<id>/model_00.dae`) exists. The actual weapon geometry lives in
`it####_mdl.arz` item-model archives in `user-data/GG4E/afs_data/root` (confirmed present on
disk, e.g. `it0100_mdl.arz` for pl0100 REVOLVER GUNMAN's revolver), but `weapon-attachment-
map.md`'s own "Needs extraction/conversion scripts" section lists ARZ decompression + HSD-model
export as still-unstarted (76 candidate files). So projectiles/weapons currently render as 2D
billboarded sprites using real particle textures, not the real 3D weapon/projectile meshes —
correctly scoped as future asset-pipeline work, not silently faked.

**`projectileVisualKindForProfile()`'s name-regex heuristic — confirmed there is no real per-move
effect/particle-ID field to replace it with, so it was upgraded in kind, not in confidence tier:**
Checked `research/format-specs/hit-bin-format.md` directly for the effect-ID field the task brief
hypothesized might live on the same per-move data pointer as the already-decoded damage/knockback
fields (`puVar17[0]`=power, `puVar17[2]`/`[4]`/`[5]`=combo/rank bytes, `puVar17[3]`/`[7]`=HP-ratio
table index (attacker/defender variants, §o), `puVar17[7]`=knockback-mode selector (§p),
`puVar17[8]`=flag bits (§j/§o), `puVar17[0x11]`=per-move record stride index (§p),
`puVar17[0x14]`/`[0x15]`=knockback angle trim (§p)). None of these are a visual-asset/effect ID —
they're all damage or knockback-direction fields, cross-checked against `hit-bin-format.md`'s own
"Still Unknown" list, which explicitly states the actor/common `0xF4`-byte hit-bin records'
"effect IDs" field is unmapped ("Actor/common 0xF4 field meanings: flags, action IDs, damage,
hitbox shape, bone/attachment IDs, **effect IDs**, and timing" — still listed as unknown). So there
is no ROM-confirmed field this port could cite to replace the heuristic with a DERIVED lookup.

Instead of leaving the bare `${id} ${name}`-regex as the only source, wired in
`research/asset-inventory/weapon-attachment-map.json` (the systematic per-borg PZZ/model/mot
asset-family scan already run by `scripts/map-weapon-attachments.mjs`, covering all 211 borgs with
confidence-weighted `fire`/`beam`/`gun`/`bulletProjectile`/`muzzle` family tags) as a **first-choice
TUNED lookup**, generated into a compact `packages/combat/src/data/projectileVisualFamilies.json`
via the new `scripts/gen-projectile-visual-families.mjs` (104/211 borgs get a confident family
signal this way — e.g. `pl0615` G RED -> muzzle, `pl0502` PHOENIX DRAGON -> flame, `pl0104` BEAM
GUNNER -> energy, matching their real weapon type far better than name-string guessing alone).
The original name-regex remains as an explicit LAST-RESORT fallback in
`projectileVisualKindForProfile()` for the ~107 borgs with no confident family signal in that
table — per the task brief, it is not removed, just demoted to fallback and clearly commented as
such. **Both paths stay TUNED** — the asset-family table is real per-borg evidence (actual asset
filenames/sizes/associations, not just an English string), which is a meaningfully better-grounded
guess than the regex, but it is still not a decoded ROM effect-ID field, so it must not be
mislabeled DERIVED.

**Files touched:** `packages/combat/src/combat.ts` (`projectileVisualKindForProfile`),
`packages/combat/src/data/projectileVisualFamilies.json` (new, generated),
`scripts/gen-projectile-visual-families.mjs` (new, generator).

---

### (u) Borg state-machine dispatch CRACKED — real structure is a 35-entry function-pointer table on `object+0x6fe`/`+0x591`/`+0x540`, NOT a switch on `+0x544` (2026-07-01)

**This closes §5 item 2 and the "+0x544 state-number semantics" blocker every parallel session has
hit.** Full read of `zz_005cc00_` (`0x8005cc00`, `chunk_0007.c:4373`) and `FUN_8005d494`
(`0x8005d494`, `chunk_0007.c:4678`), plus everything around them in `chunk_0007.c` lines
~3670-5540, per `HANDOFF-PROMPT.md`'s Priority list. **The premise in the handoff doc and in §3/§4b
was wrong in one specific, important way**: `object+0x544` is NOT the top-level state selector
dispatched by a switch at these two addresses. Both functions are individual *leaf handlers* — small
3-phase sub-state machines local to whichever high-level state is currently active — and `+0x544`
(plus `+0x545`/`+0x546`/`+0x547`, a 4-byte cluster) is a **per-state local phase/sub-counter that
every leaf handler resets to 0 on entry and reuses for its own internal sequencing**, not a
global game-wide enum. The real global state selector is a **different field**, confirmed below.

**The real dispatch site** (found by grepping every use of `(*(code *)(&PTR_FUN_...)` in
`chunk_0007.c` — there are exactly three, all cited below): `zz_005c694_` (`0x8005c694`,
`chunk_0007.c:4161`) runs once per frame per active borg and contains the literal dispatch:
```c
(*(code *)(&PTR_FUN_802d35a4)[*(char *)(param_1 + 0x6fe)])(param_1);
```
i.e. **`object+0x6fe` (signed byte) is the real per-frame state selector**, indexing a genuine
function-pointer jump table in `.data`, not a switch statement in the decompiled C (which is why
grepping for `switch` or a big `if/else` chain on `+0x544` never found the "spine" — it isn't
shaped like one in the source; Ghidra recovers it as a computed call through a table, exactly the
PPC idiom for `foo[state](obj)`). A second, closely related dispatch exists at
`chunk_0007.c:4000` inside `zz_005c290_` (`0x8005c290`):
`(*(code *)(&PTR_FUN_802d3580)[*(char *)(param_1 + 0x591)])(param_1)`, and a third at
`chunk_0007.c:3781` inside `zz_005bccc_` (`0x8005bccc`):
`(*(code *)(&PTR_FUN_802d3570)[*(char *)(param_1 + 0x540)])(param_1)`.

**All three tables are literally the same 35-entry array, just read through three different base
addresses (`0x802d3570` `<` `0x802d3580` `<` `0x802d35a4`) with three different index fields
(`+0x540`, `+0x591`, `+0x6fe` respectively).** Confirmed by directly reading the raw pointer array
out of `boot.dol` (`dol.py`-style section-table parser, this session's scratch script): the array
is 35 consecutive code pointers running from `0x802d3570` to `0x802d35f8` inclusive (functions
`0x8005be08` through `0x8005e868`), followed immediately at `0x802d35fc` by non-code data
(`DAT_802d35fc`=`0xc000`, `DAT_802d3600`=`0x4000`, `DAT_802d3604`=0, `DAT_802d3608`=20.0f, ... —
these are the small lookup tables already referenced by name/offset in §o/`FUN_8005d494`/
`FUN_8005dd10`, confirming the table boundary). Because the three index fields address the same
array at different offsets (`0x802d3580 - 0x802d3570 = 0x10` = 4 slots; `0x802d35a4 - 0x802d3570 =
0x34` = 13 slots), the relationship is: **`table_slot = +0x540_value = +0x591_value + 4 =
+0x6fe_value + 9`**. So a borg whose `+0x6fe == 0` is at the same handler as `+0x591 == 4` or
`+0x540 == 9` — they are three views of one underlying "which handler runs this frame" cursor, each
valid only over the sub-range its call site actually uses (`+0x540` spans the full slots 0-34,
`+0x591` spans slots 4-34 i.e. its own index 0-30, `+0x6fe` spans slots 9-34 i.e. its own index
0-25). `zz_005ec04_` (`0x8005ec04`, `chunk_0007.c:5531`, already noted in §3/§4b as "state cleared
to 0" but not previously connected to the table) is the **state-transition primitive**:
`zz_005ec04_(borg, N)` sets `object+0x6fe = N` (selecting the new handler, in `+0x6fe`-relative
terms) and zeroes `object+0x544..0x547` (resetting the new handler's local phase counter to a
clean start) — this is the literal "enter state N" operation used throughout the corpus (e.g.
`zz_005cc00_` calls `zz_005ec04_(param_1, 10)` when its local phase falls through, i.e. "done with
this handler, transition to `+0x6fe`-space slot 10 = absolute table-slot 19 = `FUN_8005ce14`").

**Full 35-slot table, addresses, and per-slot role from reading every handler body in full** (roles
marked Confirmed where the exact mechanism was read directly from decompiled C; Likely where a
gameplay label is inferred from field reuse/call shape, not a live-traced confirmation — see the
honesty breakdown after the table):

| slot | `+0x540` | `+0x591` | `+0x6fe` | address | role (confidence) |
|---|---|---|---|---|---|
| 0 | 0 | n/a | n/a | `0x8005be08` | spawn drop-in phase 0: counts down `+0x558` timer, sets `+0x541` flag near the end (Confirmed shape; Likely = "falling/materializing" sub-phase) |
| 1 | 1 | n/a | n/a | `0x8005bec8` | spawn drop-in phase 1: bumps `+0x540`, resets `+0x558`, calls `dispatch_slot_action_update(borg,2)` (Confirmed shape) |
| 2 | 2 | n/a | n/a | `0x8005bf6c` | spawn drop-in phase 2: counts `+0x558` down again, on completion clears `+0x71b/0x490/0x489/0x48a`, calls `zz_008aff0_` — "landing impact / become controllable" (Likely) |
| 3 | 3 | n/a | n/a | `0x8005bfec` | not independently read this session (present in the raw pointer table but not cross-checked against `_index.tsv` under a distinct name) — **not yet confirmed** |
| 4 | 4 | 0 | n/a | `0x8005c4a4` | one-line wrapper: calls `zz_005f00c_(borg)` — **Likely idle/neutral-stance handler** (lowest `+0x591` index; `+0x591` is the already-Confirmed §3 attack/command-type selector, so index 0 there plausibly means "no command") |
| 5 | 5 | 1 | n/a | `0x8005c4c8` | idle variant: same `zz_005f00c_` call, plus a guard-flag check promoting to slot 28 (`+0x6fe=0x11`) on a bit-0x40 test (Likely: idle-with-guard-available) |
| 6 | 6 | 2 | n/a | `0x8005c530` | idle variant: same shape, promotes to slot 24 or 25 (`+0x6fe=0xf`/`0x10`) via a parity check — plausibly a **left/right guard-entry pair** (Speculative on which side, Confirmed on the promotion mechanism) |
| 7 | 7 | 3 | n/a | `0x8005c5ac` | idle variant, `zz_005f00c_` only, no promotion (Likely: a third idle/neutral flavor) |
| 8 | 8 | 4 | n/a | `0x8005c5d0` | returns bool; on success clears invincibility-adjacent flags and enters "action 4" via `zz_00ea2c8_(borg,4)` — **Likely block/guard-start handler** (gated on `+0x1da` bit 0x10 and `+0x599`==0) |
| 9 | 9 | 5 | 0 | `0x8005c7f0` | one-liner: `zz_006a474_(borg)` — **Likely "return to idle" trampoline** (this exact call recurs as the common "go back to neutral" tail in many other slots below) |
| 10 | 10 | 6 | 1 | `0x8005c810` | 3-phase local FSM (`+0x544` -1→0→1) computing a turn-in-place direction bucket via `zz_0046510_(delta,2)`, waits on completion flag `+0x1d0e`, exits via `zz_006a474_` — **Likely one of a walk/turn-direction handler family (slots 9-13/17)** |
| 11 | 11 | 7 | 2 | `0x8005c95c` | same shape as slot 10, different `zz_005f188_` action-request sub-id (`+5` not `+9`) — sibling direction handler |
| 12 | 12 | 8 | 3 | `0x8005ca80` | same shape again, additionally uses `zz_004516c_` (local vector-distance check) to bias the direction bucket — third sibling in the same family |
| 13 | 13 | 9 | 4 | `0x8005c7f0` | **duplicate pointer** — same one-line idle/return trampoline as slot 9 (confirmed by two independent raw-ROM reads, not a transcription error); `+0x6fe` values 0 and 4 behave identically |
| 14 | 14 | 10 | 5 | `0x8005c810` | duplicate pointer to slot 10's handler |
| 15 | 15 | 11 | 6 | `0x8005c95c` | duplicate pointer to slot 11's handler |
| 16 | 16 | 12 | 7 | `0x8005ca80` | duplicate pointer to slot 12's handler |
| 17 | 17 | 13 | 8 | `0x8005ca80` | second duplicate of slot 12's handler (slots 12/16/17 all point at the same code — three distinct index values intentionally sharing one handler body) |
| 18 | 18 | 14 | 9 | `0x8005cc00` | **`zz_005cc00_`**, the function named in `HANDOFF-PROMPT.md`. 3-phase local FSM; on entry (phase -1→0) sets a status-flag bit (`+0x5e0 |= 0x2000000`), computes a facing-turn target via `zz_0046510_`, and calls `zz_005f188_(borg,-0x7f,cVar+5)` — an action/animation-request call (the same helper, with varying small integers, recurs across this whole cluster; very likely the "play this specific sub-animation index" call that `research/format-specs/borg-animation-banks.md`'s group/slot addressing is downstream of). Falls through via `zz_005ec04_(borg,10)` to slot **19** when its local phase is outside -1..1. **Likely an attack-startup or directional-turn-then-commit handler** — not confirmed as specifically "melee attack" without a live input correlation. |
| 19 | 19 | 15 | 10 | `0x8005ce14` | similarly-shaped 3-phase FSM but computes the turn via `FUN_800452a0` (atan2-style angle math on `+0x44`/`+0x48` velocity) instead of the simpler `zz_0046510_` bucket — reached from slot 18's fallthrough; **Likely a follow-up phase of the same attack/turn sequence**, e.g. "commit to attack direction" |
| 20 | 20 | 16 | 11 | `0x8005d0a8` | same 3-phase shape as the slot-10/11/12 family (turn bucket via `zz_0046510_`, waits on `+0x1d0e`) but falls through via `zz_005ec04_(borg,10)` — i.e. its only exit target is "go to `+0x6fe`-space slot 10" = absolute slot 19. **Likely a short one-off action that always returns to the slot-19 turn/attack-commit handler.** |
| 21 | 21 | 17 | 12 | `0x8005d224` | one-liner: conditionally resets invincibility timer to the confirmed 60.0 constant, then **tail-calls `zz_005cc00_` directly** (slot 18) — a thin wrapper variant of slot 18, plausibly selected when the same FSM should run but with a fresh invincibility grant (Likely: a hit-reaction-adjacent entry into the same attack FSM) |
| 22 | 22 | 18 | 13 | `0x8005d258` | 4-phase FSM (`+0x544` 0/1/2/3+), heavy `zz_004beb8_` animation-request calls in the `0x82`xx sub-id family, ends via `zz_005ec04_(borg,0xb)` — i.e. transitions to `+0x6fe`-space slot 11 = absolute slot 20. **Likely a longer attack/special windup that hands off to the short slot-20 handler.** |
| 23 | 23 | 19 | 14 | `0x8005d494` | **`FUN_8005d494`**, the other function named in `HANDOFF-PROMPT.md`. Richest handler read this session: writes the confirmed invincibility field `object+0x720` to the confirmed `60.0` constant (`FLOAT_80437448`, same address as the §a wake-up-invincibility seed anchor) as the **very first statement of every call**, not just on entry — meaning invincibility is re-armed every single frame this handler runs, not granted once. A 4-way branch on local phase (`==2`, `>1`, `==0`, `<0`, else) follows; the `==0` branch reads `object+0x591` (the confirmed §3 attack/command-type selector) and branches into small direction tables `DAT_80433820`/`DAT_80433828` (indexed by a computed 0-3ish value) when `+0x591` is 4/5/6, or a different fixed-offset facing calc when `+0x591` is 1/2. This is the shape of "resolve which attack sub-move based on command type, commit a direction, and grant invincibility." **Likely the core melee-attack-active/execution handler**, and the per-frame invincibility re-arm is itself a real, address-cited, portable mechanism (see Action Item below) independent of whether "melee attack" is the exactly correct label. |
| 24 | 24 | 20 | 15 | `0x8005d9d8` | 3-phase FSM, scales velocity by a damping constant (`FLOAT_80437474`) on entry to phase 1, falls through via `zz_005ec04_(borg,10)` — **Likely attack-recovery/end-lag handler** (velocity-damping shape matches "attack over, decelerate") |
| 25 | 25 | 21 | 16 | `0x8005db44` | short 2-phase FSM: sets a status bit (`+0x5e0 |= 0x10000000`), snaps facing to face away from the last knockback-angle target (`+0x72 = +0x284 - 0x8000`, using the §p/§q-confirmed `+0x284` field), animation sub-id `0xd` — **Likely a knockback/hit-reaction entry handler** |
| 26 | 26 | 22 | 17 | `0x8005dc24` | near-identical to slot 25 but sub-id `0xe` and additionally restores `+0x50` from a per-borg-type data table (`+0x4ac`-indirect `+0x6c`) — sibling hit-reaction variant |
| 27 | 27 | 23 | 18 | `0x8005dd10` | 3-phase FSM with a `+0x568` countdown timer (same field family as the §3-noted `+0x568/0x56c/0x570` drop/recovery-arc cluster), animation sub-id `0x13` or `0x17` selected by whether raw `+0x6fe == 0xf` (absolute slot 24) — **Likely hit-reaction recovery / knockdown-adjacent** |
| 28 | 28 | 24 | 19 | `0x8005dd10` | duplicate pointer to slot 27's handler |
| 29 | 29 | 25 | 20 | `0x8005df2c` | short 2-phase FSM, same `+0x568`-timer family, animation sub-id `0xd` — sibling of slots 25/26 |
| 30 | 30 | 26 | 21 | `0x8005dffc` | long 4-phase handler, heavy use of all three `+0x568/0x56c/0x570` "drop/recovery arc" fields plus turn-rate fields `+0x7e/0x7c` — **Likely a full knockdown/getting-up sequence** (consistent with §r's finding that a group-4-slot-0 animation bank is a confirmed knockdown pose) |
| 31 | 31 | 27 | 22 | `0x8005e31c` | 4-phase FSM explicitly reading a per-borg-type parameter block (`param+0x4ac`-indirect `+0x3f/0x40/0x41/0x4c/0x50/0x68/0x6c`), sets `+0x590 = 2` near the end of phase 3 — **Likely a scripted/authored per-borg landing or special-move-body sequence** |
| 32 | 32 | 28 | 23 | `0x8005e5a8` | rich handler, sets `+0x7de = 1` unconditionally every call, phases gated by a `+0x550` countdown, calls `FUN_8005ef08`/`zz_00677b0_`; on final countdown **explicitly calls `zz_005ec04_(borg, 5)`**, confirmed to transition to `+0x6fe`-space slot 5 = absolute slot 14 = `0x8005c810` (a walk/turn-direction-family handler, slot 10's twin) — a **Confirmed exact transition target**: this handler's terminal state change goes to the walk/direction family, not to idle, consistent with "recovering from a big action back into normal movement" |
| 33 | 33 | 29 | 24 | `0x8005e868` | long multi-phase handler (`+0x544` 0/1/2/4-ish, with an explicit fallthrough gap at 3) doing paired-single matrix math (`gnt4_PSMTXMultVec_bl`) against a per-borg-type transform (`+0x4ac`-indirect `+0x8d4`), plus arc-shaped Y-velocity assignment via `zz_0045204_`/`zz_0045238_` (the same sin/cos-style helpers used in the §p-confirmed knockback-direction code) — **Likely a scripted spawn/entrance or big-special-move body**, ends by clearing invincibility-adjacent flags and calling `zz_006a5a4_`/`zz_006a474_` (the same "return to idle/neutral" trampolines seen elsewhere) |

Table columns note: `+0x591`/`+0x6fe` "n/a" markers above mean that particular index field's call
site (`zz_005c290_`/`zz_005c694_`) is not the one that reaches that slot in the traced call graph
this session — the underlying array slot still exists and is still reachable via `+0x540` (or via
direct `zz_005cc00_`-style tail calls, as slot 21 reaches slot 18). This does not mean the slot is
unreachable in the game, only that this session did not trace a `+0x591`/`+0x6fe` path into it.

**What is Confirmed vs Likely vs Speculative, stated plainly:**
- **Confirmed** (read directly from decompiled C plus a raw ROM pointer-table read, both cited
  above): the three-tables-are-one-35-entry-array structure; the exact base-address/index-field
  relationship (`+0x540 = +0x591+4 = +0x6fe+9`); `zz_005ec04_`'s exact effect (`+0x6fe=N`,
  `+0x544..547=0`); the table's exact length (35 entries, `0x802d3570`-`0x802d35f8`, confirmed by
  the immediately following slot being non-code data already named elsewhere in the corpus); every
  individual handler's internal control-flow shape (phase counts, which struct fields each one
  touches); slot 23's (`0x8005d494`) invincibility-timer write being unconditional per-call, not
  gated to entry; slot 32's exact transition target (`zz_005ec04_(borg,5)` -> slot 14).
- **Likely** (inferred from field reuse and call shape, not a live-traced confirmation): the
  human-readable *gameplay label* attached to each slot (idle/walk/attack/hitstun/knockdown/etc in
  the table above). These labels are informed guesses from which already-Confirmed fields (`+0x720`
  invincibility, `+0x284` knockback-angle-target from §p/§q, `+0x568/56c/570` drop/recovery-arc
  cluster from §3, `+0x591` attack/command-type selector from §3) each handler reads or writes,
  cross-referenced against the handler's shape (does it wait on a completion flag then transition,
  does it drive a countdown timer, etc). **Do not treat the state names in the table as DERIVED** —
  only the addresses, indices, and code-level mechanisms are DERIVED; the labels are explicitly
  Likely/Speculative and should be re-checked against a live Dolphin trace (watch `+0x6fe` while
  performing a specific action — walk, melee, get hit — the same technique already used
  successfully for HP in §h) before any future session treats them as ground truth.
- **Not found this session, and the concrete next step**: which absolute `+0x6fe` value the game
  enters on taking a hit or dying. `resolve_hitbox_target_effects_and_damage` (`0x8002e2a8`, the
  confirmed damage-application function from §h/§i/§o) was grepped in full for any write to
  `+0x6fe`, `+0x540`, or `+0x544` in `chunk_0003.c` and **has none** — it only sets HP and the
  `+0x684/688/68c` timer trio (§s). This means the connection from "took damage" to "which table
  slot handles the hit reaction" is not direct; it must run through whatever reads the
  `+0x684/688/68c` timers (§s already names `zz_005f00c_`, `0x8005f00c`, as the next lead), and
  that function — not the damage resolver — is the one that would actually call `zz_005ec04_` to
  switch `+0x6fe` into the hit-reaction family (Likely slots 25-30 above). Tracing `zz_005f00c_`'s
  full body and its own callers is the concrete next step to fully close the hitstun/knockdown
  state-number question.

**Per-state timer/duration fields analogous to the confirmed 60-frame invincibility pattern**: one
clean instance found, and it reuses the already-known field. Slot 23 (`0x8005d494`,
Likely-melee-attack-active handler) writes the confirmed `object+0x720` invincibility timer to the
confirmed `60.0` constant (`FLOAT_80437448`, same constant/address as the §a wake-up-invincibility
seed anchor) **every single frame the handler is active**, not once on entry. Because `+0x720`
decrements by `~1.0`/frame and clamps at 0 (§a's already-ported algorithm), and this handler
re-writes it to 60 every frame, the practical effect is **"invincible for the entire duration this
handler is active, plus ~60 more frames after it exits"** — a real, portable mechanism distinct
from the wake-up-invincibility use of the same timer/constant. No other slot was found writing a
fixed countdown constant to a *new* timer field the way slot 23 does to `+0x720`; the `+0x550`/
`+0x552` fields used as countdowns in several slots (25/32/33) are initialized from *computed*
values (a per-borg-type table lookup, or `+0x3f`/`+0x40`-family fields) rather than a single fixed
ROM constant, so they are not "confirm one number and port it" the way
`WAKE_UP_INVINCIBILITY_FRAMES` was — they are per-move/per-borg data, same open status as the
`plxxxxhit.bin` record fields from §o.

**Action item / what got ported to `constants.ts`**: the "attack-active handler re-arms the
60-frame invincibility timer every active frame" mechanism from slot 23 is real, address-cited, and
DERIVED as a boolean mechanism (not a numeric guess) — added to `packages/combat/src/constants.ts`'s
`STATE` block as `MELEE_IFRAME_REFRESH_PER_FRAME = true` with a citation to this section. The
specific `STATE.MELEE_COOLDOWN`/`SPECIAL.COOLDOWN`/`STATE.DOWN_DURATION`/`DEATH_DURATION`/
`SPAWN_DURATION` placeholders **stay TUNED** — this session found *which handler* is Likely
melee-attack-active (slot 23) and *that* it grants continuous i-frames, but did not find a fixed
authored duration constant for how long slot 23 (or the knockdown-family slots 27-30) stays active
before falling through; those durations are gated by animation-completion flags (`+0x1d0e`,
`+0x1d0f`) and per-borg-type data-table fields (`+0x4ac`-indirect), not a single named ROM constant
the way `60.0` was for invincibility. Porting a guessed frame-count for those would be exactly the
"wrong-but-confident" outcome this repo's convention forbids, so they stay TUNED with this section
cited as the concrete next step (trace `+0x1d0e`/`+0x1d0f`'s writers — almost certainly an
animation-frame-complete flag set by the HSD animation pipeline from §4d — to recover the real
per-animation duration, which is the actual portable value, not one constant per state).

**Practical guidance for future AI/animation/cooldown work (the point of this whole section):**
watch `object+0x6fe` (not `+0x544`) to know "what is this borg doing right now" — `+0x544` only
tells you *how far into* the current `+0x6fe` state's local sequence you are, and resets to 0 on
every transition, so it is useless as a cross-state identifier on its own. This is almost certainly
why every prior parallel pass got stuck: `+0x544` looked like "the" state field because it's read
first in both functions named in the handoff doc, but it is scoped per-handler, not global. To
identify a specific gameplay state live (e.g. "which slot is melee attack for borg X"), watch
`+0x6fe` in Dolphin's debugger while performing that action — the table above gives a Likely
starting guess for where to look (slot 23/`+0x6fe==14` for melee-active, slots 27-30/
`+0x6fe==18..21` for knockdown/hit-reaction family, slot 9 or 13/`+0x6fe==0` or `4` for idle) but
should be confirmed live before code depends on the exact number for a specific borg or move.

---

### (v) Combat had ZERO audio wiring — the "wrong asset / wrong timing" bug report's real cause
(2026-07-01)

Investigated the user bug report "the port has the wrong audio assets" / "playing at the wrong
times." Full survey of `packages/audio/src/index.ts` (the `GotchaAudioManager` — a thin
`HTMLAudioElement` wrapper over a manifest of `bgm`/`sfx`/`voice` keys, no Howler/WebAudio, no
built-in timing logic — playback timing is entirely the caller's responsibility) and every call
site in `apps/game/src` (the only file that imports `@gf/audio` is `apps/game/src/main.ts`).

**Finding: `packages/combat/src/combat.ts` has zero audio calls and zero import of `@gf/audio`.**
Every state transition (`enterHit`, `enterDown`, `enterDeath`, `stepAttacks`'s melee/shot/special
branches) only mutates `b.state`/`b.anim`/`b.cooldowns` — no sound hook exists at the sim layer.
`apps/game/src/main.ts`'s only audio call sites (grep-confirmed, ~20 of them) are exclusively
menu-navigation SFX (`playConfirmSfx`/`playBackSfx`/`playEditSfx`, keyed to `AUDIO_CUES.confirm/
back/edit` = `se00_00/01/02`) and 2 BGM tracks (`menuBgm`/`battleBgm`), all fired from menu/screen-
transition code, never from combat. So the user-visible symptom ("wrong asset, wrong timing") is
the natural way a player would describe "the game makes no attack/hit/death sounds during a
fight, only menu blips and background music" — not a subtler mistiming of an existing hook.

**Checked whether `AnimAudioEventLookup` (§4g, `nlQSort<AnimAudioEventLookup>` @ 0x801a7640) is a
usable per-anim-frame (frame, sound-id) table, per the hypothesis in HANDOFF-PROMPT.md — it is
NOT.** Read the full decompiled body in `research/decomp/ghidra-export/chunk_0050.c:4282-4290`:
it is a one-line forwarding call, `nlQSort<AnimAudioEventLookup>(...) { zz_01a7560_(param_1,
param_2,1,param_3); }`. `AnimAudioEventLookup` is a demangled C++ **template type name** attached
by the toolchain to a generic sort-template instantiation, not evidence of a decoded audio-event
table — `zz_01a7560_` (`chunk_0050.c:4240-4264`) is itself a generic object-allocation helper
(`zz_008893c_(2, 0x39, ...)`, allocates object type `0x39`, copies 5 words into fixed struct
offsets `+0x144/+0x148/+0x14c/+0x150/+0x154`) called from at least 3 other unrelated sites with
different literal params — shared plumbing, not audio-specific logic. No `(frame, sound-id)` pair
array or per-clip walk exists in this function. **Confirmed dead end, not a lead**: there is no
recoverable ROM per-animation audio-event table behind this symbol name.

Also checked `research/format-specs/hit-bin-format.md`'s "Still Unknown" list (per-move `0xF4`-byte
records) and `scripts/inspect-hit-bins.mjs` — no sound/SFX-ID field has been identified in the
hit.bin/comhit.bin record format either (only "effect IDs" is listed as unknown, and nothing ties
it to an audio asset specifically). And checked the animation-bank pipeline (`anim_index.json`,
`scripts/bake-all-borg-anims.mjs`, `research/format-specs/borg-animation-banks.md`, all touched by
the G-Red animation fix in §4r) — it is purely bone/keyframe visual data; zero audio-event fields
exist anywhere in that pipeline. **Net: there is no ROM-derived per-action audio table to port.**
Combined with `apps/game/public/audio/manifest.json`'s own notes (only 5 generic `se00_00..04`
SFX samples exist, decoded from `poq_adx_usa.afs` block 0, no combat-specific SFX subfolder was
ever extracted) and `research/combat-assets/combat-asset-inventory.md`'s explicit statement
("Audio cue semantics are not mapped; listed audio is exported source material only" — repeated
per-borg), this is a **"never extracted," not "extracted wrong"** situation: no naming mismatch
existed because no combat-specific audio asset extraction was ever attempted.

**Fix applied (TUNED, explicitly not DERIVED — no ROM per-action sound-ID data exists to derive
from):** added an edge-triggered animation-slot-transition hook so combat states actually trigger
*something* audible, using the same architectural pattern already proven for VFX in
`apps/game/src/sim/battleScene.ts`'s `spawnHitSpark()` (which already detects `slot === "hit" &&
lastSeenSlot !== "hit"` to fire hit-spark VFX exactly once per hit-state-entry, not every frame).
- `BattleScene`'s `BorgAssets` interface (`battleScene.ts`) gained an optional
  `onSlotEnter?(borgId, slot, uid): void` hook, called in `sync()` exactly once per animation-slot
  transition (`slotChanged = actor.lastSeenSlot !== slot`) — covers melee/shoot/special/hit/down/
  death/spawn/jump/dash uniformly, fired on state-enter, not on every frame and not repeatedly
  while a state persists (the correct trigger semantics per the bug report — "wrong times" would
  include "playing every frame" or "never playing," and edge-triggering fixes both failure modes).
- `apps/game/src/main.ts` supplies this hook (`onSlotEnter: (_borgId, slot) => playCombatSfx(slot)`
  at the `new BattleScene(...)` call site) and a new `COMBAT_SFX: Partial<Record<AnimSlot,
  string>>` map + `playCombatSfx()` wrapper around the existing (reused, not duplicated) `playSfx`
  module function. Mapping: `melee`/`shoot` -> `se00_04` (~3.0s, the shortest available sample
  suitable as a one-shot stinger), `special`/`hit`/`down`/`death` -> `se00_01` (~3.0s, the other
  short sample). **Deliberately excluded** `se00_00`/`se00_02`/`se00_03` from combat use — all
  three are exactly 12.0s (manifest.json-confirmed durations), clearly loop/jingle-length assets,
  not one-shot hit-length stingers; reusing them for melee/hit would just trade "no sound" for "a
  wrong-length sound," the same class of bug being fixed.
- This is an honest **TUNED placeholder wiring**, not a claim of ROM accuracy: every borg's
  melee/shot/special/hit/down/death now shares the same 2 generic stingers (no per-borg or
  per-move specificity), because no ROM-confirmed per-action sound-ID table was recoverable in
  this session (see the `AnimAudioEventLookup` dead-end above). Do not "discover" per-move SFX IDs
  by guessing further from `hit.bin`/`comhit.bin` fields already ruled out above without new
  binary evidence.

**Still a known gap, not fixed this pass:** footstep-on-move and jump/land SFX were not wired —
`slotForBorg()`'s `move`/`jump`/`fly`/`dash*` slots fire `onSlotEnter` the same as any other slot
(so the hook exists), but `COMBAT_SFX` intentionally has no entries for them: footsteps are a
per-frame-cadence loop concern (needs a stride/frame-cadence signal this sim doesn't track, not a
single state-enter edge), and no generic "footstep"/"land" sample exists in the current 5-file
`se00_*` set to wire in dishonestly. Left as a clearly-scoped follow-up rather than reusing an
unrelated sample.

**Files touched:** `apps/game/src/sim/battleScene.ts` (`BorgAssets.onSlotEnter`, `sync()`),
`apps/game/src/main.ts` (`COMBAT_SFX`, `playCombatSfx`, `BattleScene` construction). No changes to
`packages/combat/src/combat.ts` or `packages/audio/src/index.ts` — both were already correctly
scoped (sim has no side effects; audio manager is generic name-based playback), the gap was
entirely in the missing wiring between them in the app layer.

---

### (w) `object+1000` borg category mapping is complete enough for the type matrix (2026-07-01)

Follow-up to sections (l), (n), and (o). The missing practical bridge for wiring the real
`type-multiplier-matrix-802c5d60.json` was whether browser borg ids can be treated as the same
two-byte spawn id copied into `object+1000`.

Validation pass over the current roster confirms that they can:

- Parse every `packages/assets/data/borgs.json` id as `pl{family}{variant}` in hex.
- Use `family` as the row into `research/decomp/data/type-category-remap-802f2e28.json`.
- Use `variant` as the column in that row.
- All 208 borg ids resolve to a canonical category; missing count is 0.
- Category distribution across the full roster:
  `0:11, 1:8, 2:15, 3:11, 4:35, 5:18, 6:6, 7:7, 8:7, 9:3, 10:1, 11:6, 12:4, 13:6, 14:6, 15:6, 16:10, 17:8, 18:6, 19:34`.

This matches the mechanism established in (n): the spawn id format is `(family << 8 | variant)`,
`zz_0066298_` reads the two bytes from `object+1000`, and the remap table returns a canonical
0-19 category. Since `borgs.json` ids encode the same family/variant bytes (`pl0615` -> family
0x06, variant 0x15, etc.), the browser port now has a derived, per-borg source for the ROM type
category. No display-type string and no `object+0x88` slot/team byte are involved.

**Port status:** safe to wire the real type multiplier as a separate multiplicative factor:
`matrix[defenderCategory][attackerCategory]`, exactly as corrected in (o). This does NOT make the
whole `zz_003cd5c_` base-damage formula derived yet; the base attack/shot coefficients, defense
percentage stand-in, HP-ratio scaling, rank/handicap table, and block/reflect gate still remain
the open parts called out in (o). The type matrix is just the now-confirmed category multiplier
piece.

---

### (x) Challenge select-screen menu-object motion (2026-07-01)

`chunk_0048.c` anchors the Challenge menu object set:

- `0x801999c8 spawn_challenge_menu_object_set` spawns banner/object rows and clears
  `challenge_work[0x1653]`, the active object counter.
- `0x80199dc0` / `0x80199ea8` give object-0's 10-frame phase timings and two-frame flicker
  during the selected/banner settle.
- `0x8019a3f0` / `0x8019a8f0` initialize and update slot/card objects with a 15-frame entrance
  timer at `object+0x1c`.
- `0x80199da0 is_global_menu_mode_5` hides these objects while the global menu mode is 5.

**Port status:** browser Challenge difficulty/player screens now share `challengeMenuMotion.ts`,
which drives DOM menu objects with a 60 Hz frame counter, 10-frame title/selection pulse, 15-frame
option fly-in, 10/15-frame reverse hide on confirm/back, and input gating until all intro/exit
objects finish. This is not the exact world-space float-table placement yet; it ports the proved
state/timing behavior while capture CSS still owns pixel placement.

**Asset note:** `vsel00_mdl.arc` / `vsel01_mdl.arc` are exported and present under
`apps/game/public/ui/scenes/vsel00` and `vsel01` (165 DAE models each). A broad "foreground bbox"
filter was tested and rejected because it exposed shared menu-text/controller quads (for example
the `CPU` texture from `Texture_0_CI4_RGB5A3.png`) over the difficulty screen. Next asset pass
should map exact model indices from the object spawn tables instead of fitting a large filtered
subset.

---

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
2. ~~**Borg state machine dispatch on 0x544** (`0x8005cc00`, `0x8005d494`)~~ — **DONE, and the
   premise was wrong**: there is no switch on `+0x544`. The real dispatch is a 35-entry
   function-pointer table (`0x802d3570`-`0x802d35f8`) indexed by `object+0x6fe` (primary,
   per-frame selector, dispatched from `zz_005c694_`/`0x8005c694`) with two aliasing views
   (`+0x591` from `zz_005c290_`, `+0x540` from `zz_005bccc_`); `+0x544..0x547` is a per-handler
   local phase counter reset by the transition primitive `zz_005ec04_`, not a global state enum.
   Full table, per-slot addresses, and Likely gameplay labels in §u — see that section before
   re-deriving any of this.
3. ~~**Animation request/apply helpers** `0x80066ec0` + `0x80066f1c` (+ `0x800670dc` heading)~~ —
   **DONE, and the original guess was wrong**: these three are a heading/turn-rate interpolator
   ("turn N degrees over M frames"), not animation selection — see §4r. No mode-to-(group,slot)
   dispatch table exists to port here; the real per-state clip choice lives in the animation-bank
   (group,slot) scheme in `research/format-specs/borg-animation-banks.md`, where §4r also fixed a
   real bug (group-4 slot-0 mislabeled as `special_s0` instead of the knockdown pose `down_s0`,
   which made G Red's/several borgs' special attack silently play their own knockdown animation).
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

---

### (y) Control model is LOCK-ON-RELATIVE (player-observed 2026-07-01, verify vs traces)

Source: direct player testimony during golden-trace setup — NOT yet ROM-confirmed. Flagged
here because it changes how movement traces must be interpreted and recorded, and it likely
explains why several movement constants (esp. DASH, TURN) never fit a world/camera-relative
model. To be verified against a golden trace (record the locked enemy's position alongside the
player's; decompose motion into toward/away/around the enemy).

The player is normally **auto-locked onto an enemy**, and stick input is interpreted relative to
that enemy, not the camera or world:
- **Up/forward** = approach the locked enemy AND rotates facing toward them (heading is slaved to
  the lock vector — heading @ +0x72 is NOT a free DOF while locked).
- **Down/back** = retreat directly away. This is the ONLY pure translation with no turn coupling,
  so it is the correct input for isolating raw ground-walk speed (`MOVE.GROUND_*`).
- **Left/Right** = a **dodge dash / step** (not a lateral walk). These are the DASH samples; the
  analyzer must treat left/right as dash events, not steady-speed runs.
- **Forward + Left/Right** = circle-strafe around the enemy.
- **Jump: tap A = jump; hold A = fly/boost** (matches JUMP.VELOCITY vs BOOST_THRUST split).

Consequences for the trace harness:
1. `scripts/trace-golden-analyze.mjs` currently infers "steady ground speed" from full-stick runs
   — valid only for the BACK-walk segment. Left/right full-stick = dash, not walk. Recipe and
   analyzer phase-detection updated accordingly (see golden-trace-runbook.md).
2. Golden capture should also record the locked enemy's struct (position) so motion can be
   decomposed in the lock frame; world-space deltas alone conflate approach/turn/strafe.
3. This corroborates the standing "lock-on is central; no manual scan-select mechanic" finding
   (combat.ts lock-on header + §q) — lock is the default state that shapes all movement.

---

### (z) Deterministic pointer chain to player 0's active borg — CONFIRMED (2026-07-01)

DERIVED from the corpus (store-site + read-site proof). Lets a live reader (Dolphin Memory
Engine) locate the REAL gameplay borg struct every frame with no RAM scanning, stable across
pauses/deaths/borg-switch. Ported in `scripts/dme_borg.py`; recorder `scripts/dme_record_chain.py`.

Chain (all big-endian MEM1):
```
T    = *(u32*) 0x80433934                 # battle/slot table ptr (0/!MEM1 => no battle)
slot = *(s8*)  (T + 0xC0)                 # player 0's active-borg slot (clamp <0||>5 -> 0)
base = *(u32*) (0x803C4E84 + slot*4)      # player 0 active borg struct pointer
```
Then all confirmed fields hang off base: +0x44/48/4c pos, +0x58/5c/60 vel, +0x72 heading,
+0x544 state, +0x720 invuln, +0x3e4 slot index, +0x88 team (0 = player/ally), +0 alive flag.

Evidence (chunk:line in `research/decomp/ghidra-export/`):
- **Store site** `zz_005809c_` @ 0x8005809c (chunk_0007.c:1149) writes each borg pointer into the
  6-entry array at 0x803C4E84, records slot at borg+0x3e4, stride 0x1e00 between borgs.
- **Player→slot** `zz_000bef4_` @ 0x8000bef4 (chunk_0001.c:558) uses `PTR_DAT_80433934[player+0xc0]`.
- **Direct player-0 fetch** chunk_0001.c:4202/4301: `(&DAT_803c4e84)[(s8)PTR_DAT_80433934[0xc0]]`.
- Array head `DAT_803c4e84` == player 0 active borg after per-frame update; single-player fast
  path `base = *(u32*)0x803C4E84`.
Validation gates for the live reader: state in [-1,64], pos in world range, borg+0x3e4 == slot,
+0x88 == 0. Avoid `DAT_804360dc` (spectator/camera cycle index, NOT player control).

This finally supersedes the fragile live approaches tried this session (position value-scan and
invuln-countdown scan both drowned in render-buffer/false-positive noise; render-pool addresses
at 0x8068xxxx tracked position but did not persist). The pointer chain is the stable foundation.

**IMPORTANT AMENDMENT (later same night, live-verified in 4P versus): the chain resolves but
does NOT carry live position in 4-player versus mode — see §(aa).**

---

### (aa) 4P-versus live-capture findings — chain structs hold NO position; live world position
is only in per-frame scratch data (2026-07-01, driven-input verification via computer-use)

Setup: real 4P versus battle (user save `2v2 gred cotrolled players no cpu.sav`), single Dolphin
2606-97 instance, DME reads, inputs driven programmatically (P1 keyboard: arrows + X=A) so every
test was input-labeled ground truth.

Findings (all live-verified, repeatable):
1. The §(z) chain resolves correctly (T ok, slot 0, `0x803C4E84` array populated with SIX
   contiguous objects at exactly stride 0x1E00 — layout matches the store site perfectly). BUT
   in this mode all six objects have `+0x44/48/4c == (0,0,0)` at all times, `+0x544 == 0`,
   `+0x720 == 0`, even while all four borgs visibly fight. The only responsive fields found in
   a full 0x1E00 float scan during driven input are frame/sub-frame counters (`+0x1ADC` block:
   x=z+1 counting 1.0/frame, y cycling 0..59) and small animation values (`+0x44` shows a
   0..24.5 sawtooth during DASHES only). These objects appear to be slot/bookkeeping objects
   in this mode, not the on-field actors — OR field state lives at other offsets entirely.
2. An input-correlated full-MEM1 scan (drive still/walk/still/walk square wave; keep floats
   that move ONLY in walk windows) returns 74 columns, ALL of which are transient scratch:
   GX viewport dims (320x224 quadrants at 0x803c1084), a scratch transform pool at 0x803c1100
   (translation column carries REAL world coords ~(-1106,224,-2997)..(400,22,-2218) but cycles
   through different scene objects every frame), per-move effect accumulators (0x8044cfd4),
   and mirrored copies at 0x8152xxxx/0x8153xxxx/0x81546xxx. No stable position column exists
   that moves only with P1 input.
3. Conclusion: in 4P versus, the persistent on-field borg state either lives in a different
   allocation not reachable via `0x803C4E84`, or positions are stored in a form my float-triple
   scans don't match (fixed-point? embedded deeper?). The world scale IS thousands of units
   (scratch matrix translations), consistent with earlier modes.

Next step (decisive, cheap, NOT another scan): set a WRITE WATCHPOINT on the scratch matrix
translation `0x803c112c` (or a mirrored copy) via the Dolphin GDB stub, capture the writer PC,
and read the writer function in the corpus — its source pointer chain IS the real per-actor
world transform. Reload the `2v2` save state after the GDB session. Alternatively trace who
consumes the §(z) pool objects (`zz_005809c_` callers in chunk_0056/0058) to find the field-
actor allocation for versus mode.

Working tooling from this session (all functional): `scripts/dme_lib.py`, `dme_borg.py`
(chain reader), `dme_record_chain.py`, `dme_capture_session.py`, `dme_find_by_motion.py`,
`dme_find_by_invuln.py`, plus computer-use-driven input recipes (P1: arrows + X). The analyzer
`scripts/trace-golden-analyze.mjs` is self-test-proven and waiting on a genuine position trace.

---

### (ab) BREAKTHROUGH: per-player camera view-matrix chain CONFIRMED live; the borg-position
door is one static trace away (2026-07-01 late, GDB matrix-catch + corpus read + DME verify)

Method that finally worked: Z0 breakpoints on `PSMTXCopy` @ 0x8020af28 / `PSMTXConcat` @
0x8020af5c (this build's stub REJECTS Z2 write watchpoints — empty reply), filtering for
destination == the per-frame scratch matrix `DAT_803c1100`. (`scripts/gdb-catch-matrix-src.mjs`;
run via `launch-dolphin-gdb.mjs`.) Caught sources, then read the calling code in the corpus.

CONFIRMED chain (live-verified via DME, all four slots):
```
V   = *(u32*)0x80433930            # viewport/render table (sibling of the 0x80433934 table)
mtx = *(u32*)(V + 0x14 + p*4)      # player p in 0..3 -> per-player VIEW matrix (3x4 row-major)
                                    # resolved: 0x803c7744 / 7b28 / 7f0c / 82f0 (static, stride 0x3E4)
camera world translation at mtx+0x0C/+0x1C/+0x2C
```
Evidence: `zz_008c440_` @ 0x8008c440 (chunk_0013.c) does
`PSMTXCopy(*(float**)(PTR_DAT_80433930 + param_9*4 + 0x14), &DAT_803c1100)` then installs it on
the HSD camera object `DAT_80436214` (+0x54). Verified live: the four pointers resolve exactly
to the caught matrices; translations are world-scale and change between game states.

The three viewport functions in chunk_0013.c:
- `zz_008c440_` @ 0x8008c440 — installs a PRE-BUILT per-player view matrix (battle viewports).
- `zz_008c88c_` @ 0x8008c88c — builds a FIXED view via `C_MTXLookAt(dst, &DAT_802da7bc eye,
  &DAT_802da7d4, &DAT_802da7c8)` (menu camera; matches June's traced static vectors).
- `zz_008c9d4_` @ 0x8008c9d4 — another fixed-vector LookAt from `DAT_802b0c84..0ca4` (special/
  results camera; its scratch source was heap 0x8044d49c).

REMAINING (the one static trace left): find who BUILDS/WRITES the per-player battle matrices at
0x803c7744(+0x3E4*p) each frame — that builder calls C_MTXLookAt (or equivalent) with a live
eye + INTEREST vector, and the interest is derived from the borg's real position, i.e. the
builder's load chain exposes the live actor object for this mode. Search: corpus refs to
0x803c7744 / 80433930-table writes / remaining `gnt4_C_MTXLookAt_bl` callers that use non-static
vectors; or GDB-break on C_MTXLookAt during battle (NOT during menus) and read r4/r6 vectors +
callstack. The eye/interest source structs ARE the per-player camera+target state (and §3.1's
runtime camera object 0x806A5300 is almost certainly one of them).

Session hazards worth remembering: this Dolphin build (2606-97) has a flaky stub — Z2
unsupported, and long breakpoint sessions wedge (stops cease; game left paused even after
release). The June GDB results were on build 2506a. For the next GDB pass, consider pinning
the older build in a separate folder, or keep sessions short (<30s) and relaunch per pass.

---

### (ac) Camera system fully cracked — actor array RE-CONFIRMED live; position candidate is
actor+0x20 vec3 in 4P mode (2026-07-01 ~10:30PM, static corpus trace from §ab's leads)

The per-frame camera update is `zz_000bda4_` @ 0x8000bda4 (chunk_0001.c:464): loops **12 camera
objects** at `0x803c73b0 + i*0x3E4` and pairs each with its target actor via
```c
actor = (&DAT_803c4e84)[ camera[0x2E5] ];   // camera's target-slot byte -> borg array (§z!)
```
then dispatches `zz_000c5f8_(cam, actor)` → per-mode policy from the **camera-mode function
table @ 0x802c38cc** (mode byte = cam+0x18; 20 entries, all in chunk_0001: mode0=FUN_8000c660,
1=FUN_8000c918, 2=FUN_8000c988, 3-12=thunks in FUN_8000d560, 13/14=zz_000d658_,
15=FUN_8000e28c, 16=FUN_8000eaf4, 18=FUN_8000eee8, 19=FUN_8000f36c) → finalize
`FUN_8000c314(cam)` which runs `C_MTXLookAt(cam+0x394, eye=cam+0x2E8, up=cam+0x330,
interest=cam+0x300)`.

**Camera object layout** (static array base 0x803c73b0, stride 0x3E4, 12 entries):
+0x00 active flag; +0x11 alt-path flag; +0x18 mode byte; +0x19 init flag; +0x2E4 bound flag;
+0x2E5 target actor slot (index into 0x803C4E84); +0x2E8 eye vec3; +0x2F4 prev eye; +0x300
interest vec3; +0x30C prev interest; +0x330 up vec3; +0x33C direction; +0x394 view matrix
(3x4; the §ab per-player matrices 0x803c7744+p*0x3E4 are exactly base+0x394).

**This re-confirms the §z borg array 0x803C4E84 as the LIVE actor list even in 4P mode** —
the camera reads real per-frame fields off those objects: +0x18 (>0 alive check),
+0xb4 (float the camera lerps toward), +0x72/+0x5b0 (headings), +0x3e5 (viewport mask byte),
+0x3f1, +0x43d (x7 reads), +0x4a1, +0x582, +0x5e0, +0x668, +0x6d0. The §aa observation that
+0x44/48/4c stay zero in this mode therefore means the POSITION lives at a different offset
here, not that the objects are inert. Camera handlers read a **vec3 at actor+0x20/0x24/0x28**
— the prime live-position candidate for this mode (to be DME-verified by driving P1).

Verification plan (fast): read `*(u32*)0x803C4E84 + slot` actors, sample +0x20 vec3 while
driving P1; also read camera+0x2E5 per camera to learn the true player→slot assignment
(P1's camera is the one whose viewport is top-left; its +0x2E5 names P1's slot).

**VERIFIED LIVE + FIRST REAL TRAJECTORY CAPTURED (same night, ~10:20PM):**
- Camera→slot mapping confirmed 1:1 in 4P versus: cam0→slot0 … cam3→slot3, all mode=1.
- All four actors carry live world positions at **+0x20/+0x24/+0x28** (spawns read
  (-1000,0,-1200), (800,0,1400), (-800,0,-1400), (1400,0,800) — the four 2v2 corners).
- **P1 chain (4P versus): `actor = *(u32*)0x803C4E84; pos = actor+0x20 vec3; heading =
  actor+0x72 s16`.** Recorded a driven backward-walk golden
  (`user-data/dolphin-trace/golden/recipe-pos20-pl0615-chain.jsonl`, 119 frames, clean):
  perfectly smooth trajectory from spawn with CONSTANT per-frame delta (dx,dz)=(-16.9,-14.1),
  i.e. **ground walk speed = 22.0 world-units/frame** (G Red, backward walk, single capture —
  provisional DERIVED-by-trace; reproduce once more before touching constants.ts per the
  standing rule). Heading BAM16 sweeps smoothly during the turn-coupled walk — usable for
  TURN_RATE fitting too.
- The +0x20 vec3 y-component stayed 0 through jumps; +0x24/+0xb4/+0x30 also flat in a jump
  probe — BUT the probe's control failed (walk didn't register either in that pass; input
  reached the game earlier, then stopped — round likely ended). **Vertical offset = the one
  open detail.** Next session: verify input registers (drive walk, watch +0x20 move), then
  rerun the labeled full-struct scan (script pattern in session log) — the field that arcs
  during tap-A jumps is the vertical; also try actor+0x8c8 & the +0x50 region.
- Ops note: keyboard input to Dolphin requires the render window focused via a click that
  actually lands (title-bar clicks sometimes focus without giving the game pad focus);
  verify with the +0x20 control before trusting any capture window.

### (ad) Mode-1 goal-eye algorithm extracted — sub-table 0x802c3894 dumped, follow policy is
FUN_8000cdc0; the min-distance/decay constants belong to the mode-2 approach (2026-07-02)

**Sub-table dump (PTR_caseD_4_802c3894, 6 entries, read from boot.dol .data):**

| idx | ptr        | function     | role |
|-----|------------|--------------|------|
| 0   | 0x8000b780 | (no export)  | not in ghidra-export/_index.tsv; unreached in gameplay (see below) |
| 1   | 0x8000cb8c | FUN_8000cb8c | mode-1 gameplay dispatcher (state machine over cam+0x2E6) |
| 2   | 0x8000cdc0 | FUN_8000cdc0 | **no-lock follow — the primary gameplay goal-eye** |
| 3   | 0x8000cf28 | FUN_8000cf28 | lock-on follow (rotates trail toward lock target actor+0x50C) |
| 4   | 0x8000d11c | FUN_8000d11c | lock/unlock transition (distance-scaled blend weights) |
| 5   | 0x8000d318 | FUN_8000d318 | actor+0x7C9 special (timered, decays back to state 2) |

`FUN_8000c918` (mode 1) indexes this table by **actor+0x3F1**, but a corpus-wide grep shows
+0x3F1 is only ever written 0 (reset) or 1 (`FUN_8000c660` init, `FUN_8000cf28` lock loss), so
gameplay always enters `FUN_8000cb8c`, which re-dispatches the SAME table by **cam+0x2E6**:
0→2 promote; no lock target (actor+0x508==0) → state 2; lock target → state 3; target-behind
check (rotate both dirs into heading frame via `zz_00453fc_`, compare z) gates 4→3; actor+0x7C9
→ state 5. The mode table @ 0x802c38cc re-dumped: [0]=0x8000c660, [1]=0x8000c918,
[2]=0x8000c988, [3]=0x8000d644, [4]/[5]=0x8000d5a0, [6]=0x8000d5f4, [7]=0x8000d600,
[8]=0x8000d60c. Cinematic tables also dumped: PTR_FUN_804335b0 (zz_000d46c_ path, entry 0 =
FUN_8000d560) and DAT_802c3900 (kill/victory cams, e.g. FUN_8000d990).

**Primary follow (mode-1 state 2): `FUN_8000cdc0` @ 0x8000cdc0 + shared `FUN_8000fc2c` @
0x8000fc2c**, per frame (all on the §ac camera object):
1. `FUN_8000fc2c`: height offset eases `cam+0x350 = (actor[+0x88C + slot*4] * cam+0x354 +
   cam+0x350) * 0.5`; **interest** = `(actor.x, (actor+0x6D0 + cam+0x350 + prevInterestY +
   actor.y) * 0.5, actor.z)` (FLOAT_80436ac4=0.5); **distance** cam+0x348 = horizontal
   `|goalEye(+0x318) - actorPos|` clamped to per-borg band `[actor+0x894, actor+0x898] *
   cam+0x354` (slot 1 uses +0x89C/+0x8A0; ×FLOAT_80436ad0=1.3 in 1P/2P splitscreen); beyond
   max it eases with FLOAT_80436b38=0.8.
2. pitch cam+0x70 := 0x600 BAM (re-written every frame, confirming §ac's init value).
3. trail dir = `goalEye - interest`, y forced 0; if |dir| ≤ FLOAT_80436ad8=0.001,
   `FUN_800452e4` @ 0x800452e4 rebuilds it as `(sin(cam+0x72), 0, cos(cam+0x72))` BAM16;
   else normalize.
4. desired = interest + dir*dist; desiredY = interest.y + dist * tan(0x600) (`zz_004526c_` @
   0x8004526c = tan(BAM16); FLOAT_80437078 = 2π/65536).
5. goal-eye blend: XZ `(4*prev + desired)/5` (FLOAT_80436acc=4 / FLOAT_80436ae8=5); Y
   `(9*prev + desired)/10` (**FLOAT_80436af0=9 / FLOAT_80436adc=10 — new extractions**).
6. **re-projection**: eye(+0x2E8) = interest + normalize(goalEye - interest) * dist.
7. correctives: `FUN_800101c8` @ 0x800101c8 recomputes dist/pitch/heading (atan2 BAM via
   FUN_800452a0), clamps pitch to ±0x3000 × clamp(0.3·1.5·distToLock/actor+0x668, 0.3, 1)
   (the 0x43300000 double-magic decodes to ±0x3000), publishes **actor+0x5B0 = cam heading
   - 0x8000** (the behind-angle used by init/fallbacks); `FUN_8000fffc` @ 0x8000fffc
   re-clamps distance to the band; both re-blend with (3*prev+new)/4 (FLOAT_80436b74=3,
   FLOAT_80436b0c=0.25) when they fire. `FUN_8001063c`→`zz_0010664_` = stage-AABB inside test.

**Lock-on (state 3, `FUN_8000cf28`)**: trail dir rotated toward `interest - lockTargetPos
(+0x324 ← actor+0x50C)` by ≤ FLOAT_80436af4=0.589 rad/frame (`FUN_80045460` axis-angle),
goal-eye blend weights 2/3 prev + 1/3 new (FLOAT_80436af8/afc), same re-projection. State 4
scales the new-weight by distance (FLOAT_80436b00..b10). Not ported (web port has no lock-on).

**Mode-2 approach (`FUN_8000c988` @ 0x8000c988, mode table [2]) — the actual home of the
"min distance"/"decay" floats**: init captures trail = eye - interest (ε-fallback to
actor+0x5B0), y=0; per frame `dist = dist <= 80 ? 80 : dist * 0.9` (FLOAT_80436ae0=80,
FLOAT_80436ae4=0.9), trail yawed **+0x200 BAM/frame** (`zz_00453fc_('y',…,0x200)` —
instruction immediate), tracked eyeY (+0x3C) rises **+4/frame** (FLOAT_80436acc reused) to cap
`interest.y + 10 * actor+0x668` (FLOAT_80436adc reused ×), eye = `(4*prevEye + interest +
trail*dist)/5`. It's a spiral-in/orbit camera; the mode-2 setter wasn't located in the export
(no `cam+0x18 = 2` write; `zz_0010514_` checks mode==2 for viewport bank +6 swaps, so it does
occur on gameplay cams). FLOAT_80436ae4 also appears in `zz_0010980_` as a fade-alpha decay —
unrelated to distance.

**Port status (apps/game/src/sim/camera.ts, 2026-07-02):** FUN_8000cdc0 steps 1-6 ported as
the primary policy (constants via gen-camera-mode1-constants.mjs; FLOAT_80436af0/adc newly
generated); FUN_8000c988 ported as the battle-entry approach replacing the instant snap
(consumes 80/0.9/0x200/+4; exit-at-band is TUNED — ROM exit unknown). Still TUNED: per-borg
band/height data (+0x894..+0x8A0, +0x6D0, +0x668 — trace band 466.5..504.9 substitutes),
multi-actor widen, wall-guard; correctives FUN_800101c8/FUN_8000fffc unported. Helpers:
`zz_0045204_`/`zz_0045238_` @ 0x80045204/0x80045238 = sin/cos(BAM16); DOUBLE_80436ab0/ab8
(0.5/3.0) are just the PPC frsqrte Newton iteration, not tunables.


### (ae) Challenge flow end-to-end: battle judge, timer freeze, winner mask, rotation + generation tables (2026-07-03)

Battle-end judge is `zz_00297c8_` @0x800297c8 (chunk_0003.c:4488-4615). Winner mask
`PTR_DAT_80433934[0x1f]`: bit0 = side 0 won, bit1 = side 1 won, **4 = timeout with no
winner** (flag mirror [0x17a]), 8 = a fourth result (mirror [0x1b6], writer not found).
Per-side blocks stride 0x3c (side0 base +0xf4, side1 +0x130): remaining-energy s32 at
+0x118/+0x154, remaining-count byte at [0x10a]/[0x146], rule-enable flags [0x108]/[0x109]
(and side1 [0x144]/[0x145]), win counters u16 +0x110/+0x14c.

- Mode split on `PTR_DAT_80433930[0x32]` (0 = versus/challenge family, 1/2 = mission):
  in mode 0, a side LOSES when its count byte or energy hits 0 (rule flags select which);
  timeout ([0x15df] set, [0x50]==0, timer +0x4c < 1) awards the win by flag [0x10b]
  (chunk_0003.c:4519-4529). In mode !=0, energy-only, and timeout with no winner writes
  mask=4 = DRAW (chunk_0003.c:4547-4553).
- **Timer freeze flag [0x50]**: countdown `zz_0029b58_` @0x80029b58 (chunk_0003.c:4621-4642)
  only decrements +0x4c when battle-state [0x45]==4 AND [0x50]==0. Writers: Versus menu
  chunk_0044.c:366-373 (limit selected -> seconds*60, [0x50]=0; no-limit -> 0xea24,
  [0x50]=1), mission chunk_0046.c:1242-1250, **Challenge chunk_0048.c:390-392 writes
  +0x48=+0x4c=18000 AND [0x50]=1** -> original Challenge battles can NEVER time out.
  Ported as `BattleConfig.timerFrozen` (packages/combat) + challenge.ts passes true.
- Per-side result flags are EQUALITY tests: `[0xc4+n] = ([0x1f] == 1 << side)` and
  `[0x102]/[0x13e]/[0x17a]/[0x1b6] = ([0x1f] == 1/2/4/8)` (chunk_0003.c:4556-4604), so a
  draw (3 or 4) displays as LOSE for every player. Results UI needs only WIN/LOSE.
- Challenge post-battle branch `FUN_801969a0` @0x801969a0 (chunk_0048.c:466-506): advance
  only when `([0x1f] & 1<<playerSide) && [0x1f] <= 2` (i.e. mask==1); mask 3 (mutual
  simultaneous destruction) or 4 exits to state 6 = the same failure screen as a loss
  (`zz_01f5ae0_(3)`, chunk_0048.c:618-637); full clear = state 5, `zz_01f5ae0_(difficulty)`.
  Battle counter DAT_80436378[8]; total battles `(&DAT_804356d0)[difficulty]` = **5/10/15**
  (extracted). Energy limits `DAT_8036f554` = **1500/2000/2500** (matches live captures).
- Challenge state table PTR_FUN_8036f560 (extracted from DOL): 0=init 0x80195fbc,
  1=menu poll 0x80196030, 2=box-load 0x80196188, 3=battle setup 0x801962c4, 4=in-battle
  0x8019688c (sub-table PTR_FUN_8036f580: 0x801968cc load-wait, 0x80196948 run,
  0x801969a0 post-battle), 5=clear 0x80196a9c, 6=fail 0x80196cec, 7=exit 0x80196d64.
- **Stage rotation** `zz_0196dac_` @0x80196dac (chunk_0048.c:643-663): stage byte [0x1c] =
  uniform pick from the 11-entry pool `DAT_8036f548` = st00-st05, st08, st0a, st0b, st0c,
  st0e, re-rolled while equal to the previous battle's stage; [0x1d] = rand%3;
  [0x1e] = rand % variantCount (the DAT_802da5d0 table already in challenge-reference.ts).
- **Enemy/ally team generation** (build_challenge_battle_setup, chunk_0048.c:302-361):
  per difficulty & battle index — CPU ally count/budget from PTR_DAT_8036f40c/8036f4b8,
  enemy count/budget from PTR_DAT_8036f434/8036f53c, pool ids from PTR_DAT_8036f360/3e4
  (battleIdx*4 + rand%4), member drawn by zz_0196eb8_ from PTR_DAT_80380804 lists; each
  rolled borg charges floor(cost*2/3) against the budget (chunk_0048.c:351). All values
  extracted to research/decomp/data/challenge-battle-tables-8036f360.json.

### (af) Death/spawn flow: kill-event accounting, 3-phase deploy, symbol-map misattribution (2026-07-03)

- **`cPlayer::ClearSwapControllerTimer` @0x802807ac and `zz_0281c38_` @0x80281c38 are NOT
  gameplay code.** Their bodies are a Huffman/bitstream video-codec decoder (vtable
  dispatch, code tables DAT_8041cfa0/cfa4, zero match-state access). The CSM symbol map is
  a cross-game import (it contains literal `gnt4-*` symbols, `Bowser::DrawShadow`,
  `LooseBallAnims::GetDesperationInfo`) — treat cPlayer/cTeam names as UNRELIABLE unless
  the body is verified. challenge-flow-evidence.md's 'death_swap_flow_candidate' anchor is
  withdrawn by this note.
- **Death accounting happens at the kill event**, not after the death animation:
  `zz_002f8dc_` @0x8002f8dc (chunk_0003.c:8212-8330) subtracts the victim's cost
  (u16 victim+0x4aa) from the side energy `+side*0x3c+0x118`, decrements the side count
  [0x10a], records last-kill pointers +0xb4/+0xb8, bumps victim losses (+0x435/+0x424)
  and attacker kills (+0x434/+0x420) and team score `(&DAT_80436154)[side] += 100`.
  Cost init: +0x4aa = `zz_0066168_(borgId)` (chunk_0006.c:8186), same lookup the
  Challenge budget uses.
- Death entry `zz_005bbc0_` @0x8005bbc0 (chunk_0007.c:3716-3751): immediately clears
  active status (+0x18=2), sets 0x5e0|=0x80000000, clears the side deploy mask bit
  [0xea], plays reaction cue id 9, then runs death anim phases via the SAME
  PTR_FUN_802d3570 table indexed by +0x540.
- **Spawn/deploy is a 3-phase timer on +0x558** (state table slots 0-2, extracted table
  at 0x802d3570 confirmed s4u addresses): FUN_8005be08 counts 20.0 -> 0 at 1.0/frame
  (descent; drop-visual toggle at 6.0 left), FUN_8005bec8 = 1 frame (sets 15.0, plays
  ally reaction cue id 8), FUN_8005bf6c counts 15.0 -> 0 (pose), then clears spawn flags.
  Total deploy lock ~ **36 frames**. Phase constants FLOAT_80437428=1.0, _30=6.0,
  _34=15.0, _38=30.0, _3c=20.0 (DOL-extracted). Phase-0 init 20.0/30.0 chosen by
  `zz_005c028_` (chunk_0007.c:3871-3891) on +0x6fe.
- Respawn-reset helper FUN_80060b60 @0x80060b60 (chunk_0007.c:6778-6804) writes +0x720 =
  30.0 (FLOAT_80437558) if +0x6cb==1 else 60.0 (FLOAT_80437564) — not in the 35-slot
  table; its dispatch context is still unproven, so SPAWN_INVINCIBILITY stays TUNED with
  these as the candidate real values.

### (ag) Real per-borg HP/ammo table + gauge init + damage records extracted (2026-07-03)

- **HP source found**: `zz_0055f90_` @0x80055f90 (chunk_0006.c:8167-8232) writes max/cur
  HP (+0x1c4/+0x1c6/+0x1c8) from `(&PTR_DAT_802f2988)[family(+0x3e8)] +
  (subIdx(+0x3ee) + variant(+0x3e9)*0x14 + DAT_804339e8[level(+0x3ec)]) * 0x12`, u16[0]
  of the row. Same row's u16[1..] feed ammo/charge fields +0x774/+0x776/+0x78c/+0x790
  (chunk_0007.c:60-94). Extracted for every roster family/variant to
  research/decomp/data/borg-hp-stat-rows-802f2988.json.
  **Cross-verified against live capture**: G RED (pl0615) level row (DAT_804339e8[0]=2)
  = HP 200 and ammo 5 — exactly the captured HUD values (UI-FIDELITY-SPEC.md).
- Gauge init (chunk_0007.c:47-52): balance max/cur (+0x6be/+0x6c2) = u16@0 of the
  pl####data.bin page (+0x4ac), down gauge (+0x6c6/+0x6c4) = u16@2; +0x59c = u16@0xa8;
  +0x204/+0x208 = u32@0x98. All 199 exported to
  research/decomp/data/borg-gauge-init-pldata.json.
- Damage-record tables (0x18 stride; consumed via hitbox record u16+0x04) extracted to
  research/decomp/data/damage-records-802d46e0.json (borg family 9 records @0x802d46e0,
  generic 12 @0x802c4760). Field map per the (ae)-adjacent hit-record census: hpDamage,
  downGaugeDamage, balanceGaugeDamage, comboScoreValue, curve indices, hitStrength,
  impact effect id, reaction flags, knockback dir mode + yaw/pitch trim, rehit interval.


### (ah) `zz_003cd5c_` damage formula FULLY decoded — every table extracted (2026-07-03)

Complete pipeline (chunk_0004.c:6672-6828), all stages in order. `rec` = the 0x18 damage
record (see (ag)), `hero = (+0x3e6 != 0)` selects table set [1] vs [0]:

1. `dmg = rec.hpDamage`; 0 if <= 0.0, or if victim status-immune
   (victim+0x5a0 & 1<<victim[0x71a]) (chunk_0004.c:6693-6699).
2. Attacker level/power: `dmg *= 1 + 0.5*(ctx+0xc4 - 1.0)` (6702-6703).
3. Attacker pair-attack bonus: if attacker+0x6fc -> `dmg *= 2.0` (FLOAT_80436f9c=2.0!)
   — +0x6fc is set by the pair-attack system (zz_005b2b8_), so this is the co-op
   pair-attack DOUBLE damage, not a nerf (6705-6707).
4. Attacker side-rank: `dmg *= PTR_DAT_804335e0[hero][PTR_DAT_80433950[side]]` — 32-float
   table 1.02..0.94. Challenge writes the side rank bytes from DAT_804356e4:
   NORMAL (0,31), TUFF (10,5), INSANE (28,4) (chunk_0048.c:404-405) (6710-6712).
5. Hero-on-side-0 nerf in modes 0/1: `dmg *= 0.5` (6713-6716).
6. Attacker HP-ratio curve: idx = clamp(32 - curHP*32/min(maxHP,200), <=31) using the HP
   mirror (&DAT_803b069c)[slot]; `dmg *= PTR_PTR_804335e8[hero][rec.attackerHpCurveIndex][idx]`
   (6717-6732). Borg-family records all use curve 0 = flat 1.0.
7. Attacker force-gauge curve: idx from side energy (&DAT_803b068c)[side] vs max
   (+side*0x3c+0x114); `dmg *= PTR_PTR_804335f0[hero][rec.forceGaugeCurveIndex][idx]` (6733-6740).
8. Attack handicap: `dmg *= PTR_DAT_804335f8[hero][attacker+0x43a]` (6741).
9. Type matrix (already ported): `dmg *= matrix802c5d60[defCat][atkCat]` via zz_0066298_
   categories (6742-6749).
10. Defender (or its parent if sub-object): pair flag -> *0.5? NO — defender +0x6fc ->
    `dmg *= 0.5` (6761-6763: FLOAT_80436f7c) — pair-attackers TAKE half damage.
11. Defense rank curve: `dmg *= PTR_PTR_80433600[hero][pldata[0x9c]][PTR_DAT_80433950[side]]`
    — per-borg curve selector byte from pl####data.bin +0x9c (6764-6768).
12. Hero-victim-on-side-0 halving in modes 0/1 (6769-6772).
13. Defense stat: `dmg *= 1.0 / (1 + 0.5*(victim+0xb4 - 1.0))` (6773-6776).
14. Defender HP-ratio curve on POST-HIT HP (mirror - rec.hpDamage), selector pldata[0x9d]
    (6777-6795); defender force-gauge curve, selector pldata[0x9e] (6796-6803).
15. Defense handicap `PTR_DAT_80433618[hero][victim+0x43a]` (6803).
16. Combo falloff: unless rec.flagsB & 0x4000, `dmg *= DAT_802c7ca0[victim+0x6ca]` =
    [1.0, 0.8, 0.5, 0.25, 0.1, 0.05, 0.02...] — successive combo hits decay hard (6804-6806).
17. Defender state 0x5e0 & 0x4000000 -> *0.5 (6807-6809).
18. Same team && !(flagsA & 0x1000): *0.25 (6811-6813); (flagsA & 0x1000) && victim+0x59c
    & 0x1000: /40.0 (6814-6817); floor at 1.0 -> int (6818-6821).

ALL tables extracted to research/decomp/data/damage-formula-tables-804335e0.json
(+ per-borg defense curve selectors from pl data). Remaining unknowns for a full port:
actor level floats ctx+0xc4 / victim+0xb4 init sites (level system; 1.0 at base level) and
per-borg +0x43a handicap byte init (0 default). With those defaulted to 1.0/0, the formula
is computable from extracted data end-to-end.

### (ai) Attack-mechanics audit: findings package for the wiki-taxonomy port plan (2026-07-03)

Full audit of the wiki "Attacks" taxonomy against the corpus + assets + current TS port,
persisted as a standalone findings package (this section is a pointer, not the content):

- `research/decomp/attack-mechanics-findings.md` — mechanic-by-mechanic audit (A-X).
- `research/decomp/data/attack-mechanics-ledger.json` — machine-readable ledger.
- `research/decomp/attack-mechanics-open-questions.md` — ranked open questions Q1-Q12.
- `research/decomp/attack-mechanics-trace-plan.md` — Dolphin traces T1-T10.
- `research/decomp/data/attack-profile-port-schema.json` — proposed port data schema.
- `research/tasks/attack-port/ATK-001..017` — cheap-agent tickets.

Headline NEW corpus leads (single-pass reads with quoted code; addresses cited in the
findings doc — verify before treating as Confirmed): attack-command decision layer
(FUN_800699d8 @0x800699d8, actor+0x585/+0x586 -> command struct at +0x4b0 -> +0x591);
complete ammo/refill system (3 weapon cells +0x774/+0x77c/+0x784, fire gate zz_006dbe0_
@0x8006dbe0, refill zz_006dcc0_ @0x8006dcc0, grant zz_006de10_ @0x8006de10, max==0 =
infinite); status framework (+0x71a id / +0x71c timer / +0x5a0 immunity, shrink +0x70c,
grow +0x70e); Power Burst chain (Y-gate FUN_80069814 -> +0x6fb=6 -> zz_005b2b8_ ->
+0x6fc/+0x6fa; +0x6fc = the (ah) "pair-attack" flag, also boosts ammo refill); mash counter
(+0x550 cap 4 in FUN_8005d494). Key resolved question: the wiki's hidden damage
resistance/falloff IS the already-ported comboRankScale_802c7ca0 — never add a second
layer. Key negatives: no OHKO damage path; no DoT loop; no proj-vs-proj logic in the
generic collision passes (per-type dispatch PTR_FUN_802da740 unread); no stick-rotation
accumulator; no +0x6fc-gated speed modifier; no burst meter accumulator in the hit path.
Known conflict to resolve before use: +0x768 read as ammo refill rate (chunk_0009.c:2923)
AND as a scale-related float (chunk_0007.c:2868-2876) — see open-questions Q7.

### (aj) Power Burst fusion system decoded — pair table, in-place link, +0x4a1 state machine (2026-07-03)

Corpus read (single-pass, quoted code; wiki-mechanics-queue.md W1). Full report in the
audit session; essentials:

- **Pair table** `DAT_802d352c`: indexed by FAMILY byte (+0x3e8), 4-byte pointer entries.
  **Bounds correction vs the raw dump**: the table is exactly 17 entries (families 0-16,
  0x802d352c..0x802d356c) — the next word 0x802d3570 is the already-confirmed 35-slot
  state-handler table (s4u), so any "pairs" read at index >= 17 are overflow into code
  pointers, not data. Only families 5 and 6 have non-null pair-list pointers
  (0x802d3420, 0x802d3480). Pair list: `listPtr + variant(+0x3e9)*4`, entries
  (s16 partnerSpawnId, s16 resultSpawnId), terminated by partnerId == -1.
- **Match path** (`zz_005b678_` chunk_0007.c:3518-3574): NO new actor is spawned — the two
  source actors are linked bidirectionally (+0x4a4 = partner ptr) and transformed in place:
  result spawn id written to +0x48c (with +1 / role arithmetic per player slot +0x4a8),
  head byte +0x3ec copied to +0x48e, roles to +0x4a9. Caller (chunk_0007.c:3450-3460)
  clears link state (zz_005c15c_), sets **+0x4a1 = 1** on both, and triggers action 0x19
  via zz_006a750_ (chunk_0009.c:859-880 — writes action id +0x5e4/anim byte +0x5db from a
  per-actor action table at +0x4f0; returns 0 if the actor lacks that action).
- **Fusion state machine on +0x4a1** (chunk_0007.c:3170-3272): 1 -> 2 (ready) -> 3 (bound,
  both must be 2) -> 5 -> 6 (locked, both must be 5); 7 = ending, both at 7 -> unfuse
  (restore +0x4a0/+0x4a9, finalize via zz_006a868_ from stored +0x48c/+0x48e).
- **Burst timer**: +0x6fb decrements in the per-slot loop (chunk_0007.c:3473-3490); its
  expiry drives the burst/fusion end path. (Note: the audit's earlier reading of +0x6fb as
  only a "6-frame arm window" needs reconciling — trace T3 should log +0x6fb end-to-end.)
- **Control**: both linked actors read the SAME +0x4b0 command struct during fusion; no
  per-part dual-input routing was found (the wiki's "parts controlled by their own
  players" is NOT corpus-confirmed — mark taxonomy-only pending trace).
- Negatives: no +0x18 deactivation during fusion; no part-destroyed early-unfuse check
  found.

### (ak) Borg level system — level-byte writers found, formula floats still uninitialized-in-corpus (2026-07-03)

Corpus read (single-pass, quoted code; wiki-mechanics-queue.md W6):

- **Level byte +0x3ec writers**: spawn-time from the roster/state table
  `PTR_DAT_80433934[subtype + 0xa0]` (chunk_0006.c:6541 zz_00536b0_; :7056 FUN_800541ac;
  chunk_0007.c:920 FUN_80057b78), plus a direct setter `zz_005814c_` @chunk_0007.c:1193
  (writes +0x3ea/+1000/+0x3ed/+0x3ec) called from story-mode progression
  (chunk_0056.c:1612/1637/1649-1650, chunk_0058.c:1347). No per-battle EXP accumulator was
  found — story flow sets the level directly at checkpoints.
- **Damage-formula level floats +0xc4 (attacker ctx) / +0xb4 (victim)**: STILL NOT FOUND as
  writes — reads confirmed at chunk_0004.c:6702-6703/6776 only. The (ah) "remaining
  unknown" stands. Likely inline/init-table code not isolated yet; next lead is the actor
  construction path around the same PTR_DAT_80433934 reads.
- **DAT_804339e8 (level -> stat-row offset) dumped** (32 bytes): [2,2,8,6,0,4,0,0,0,0,0,1,
  0,1,0,0,1,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1] — sparse; levels 0-5 spread across row offsets
  {2,2,8,6,0,4}, higher levels mostly 0/1. Single-pass dump; re-verify before persisting to
  research/decomp/data/.
- **Down-gauge level scaling site**: chunk_0003.c:7997-8002 — down-gauge damage scaled by
  `0.5 * (float@+0xb4 - 1.0)` where the pointer is the VICTIM (pcVar18). CONFLICT NOTE:
  gauges.ts's doc comment says down damage scales with ATTACKER level; this read says the
  +0xb4 float on the victim object. Single-pass vs prior census — do not change gauges.ts
  until re-read or traced (T9/T4 can log it).
- **+0x768 init**: the only write found (chunk_0076.c:2337, FUN_8027e48c) is a bulk init on
  what looks like a different (graphics/audio) struct — supports open-questions Q7's
  suspicion that the chunk_0007 "scale" reader and the chunk_0009 "refill rate" reader may
  be on different object types. Q7 stays open; refill-rate init remains unknown.

### (al) Healing, magnet/pull, self-hit exclusion, burst-passthrough negative (2026-07-03)

Corpus read (single-pass, quoted code; wiki-mechanics-queue.md W2-W5):

- **Healing CONFIRMED as a dedicated HP-increment path**, not a damage-formula effect:
  battle_frame_target_action_dispatch (chunk_0003.c:6318-6323) — when the borg's spawn id
  (+1000) is 0x702 or 0x70a (family 7 = Nurse variants), `+0x1c6 += (&DAT_803b0638)[slot*2]`,
  clamped to max +0x1c4. A companion check at :6237 looks for peer ids 0x701/0x708. The
  grep census found this is the ONLY += write to +0x1c6 in the corpus. The accumulator
  DAT_803b0638's writers were not fully traced — what fills it (heal-beam hits? passive?)
  is the open half. Healing is NOT ammo-gated (no zz_006dbe0_ path from these sites).
- **Magnet/pull CONFIRMED multi-frame**: hit-record byte puVar17[8] & 0x10 stores world
  target vectors to (&DAT_803b06c0/c4/c8)[slot*0xc] (chunk_0003.c:7687-7708) consumed by
  start_forced_move_to_point (chunk_0009.c:1064 family), with +0x5e0 |= 0x1000 marking
  forced-move. This upgrades the (q)-era "hit-reactive bookkeeping" reading: it is the
  authored pull/tether channel.
- **Self-hit exclusion is unconditional**: both collision passes gate on the object's
  owner pointer +0x1e4 != target (chunk_0003.c:7088/7090 and 7231/7233); no record flag
  bypass found. Wiki self-damage (ICBM-style) therefore must arrive via a child object
  with different ownership, or not at all — unresolved.
- **Burst ally-passthrough NOT found — and a constant-value correction**: the agent-read
  "burst 0.25 divisor" at chunk_0003.c:7546-7549 multiplies by FLOAT_80436f9c, which is
  already ROM-confirmed = 2.0 exactly ((o)); i.e. that site is burst-attacker DOUBLING
  (applied in the gauge/hit-resolution path when attacker +0x6fc set), consistent with the
  formula's step 3. No code path skips a hit for allied/self attackers during burst; the
  wiki passthrough claim stays WIKI_TAXONOMY_ONLY (trace T3/T10 can test it live).

### (am) Guide-mining cross-check: stat-row column layout decoded; observational mechanics anchors (2026-07-03)

Player guides (GameFAQs move list/strategy guides via search extracts — direct fetch
blocked; Speed Demos Archive page fetched directly) were mined as OBSERVED-BEHAVIOR
taxonomy. All claims paraphrased. Two products:

**1. Stat-row column layout decoded via anchor cross-check.** The 9-u16 rows in
`research/decomp/data/borg-hp-stat-rows-802f2988.json` (source zz_0055f90_, (ag)) read as:
`[HP, w0cur, w0max, w0refillType, w0refillParam, w1cur, w1max, w1refillType, w1refillParam]`.
Four independent guide anchors match exactly at default row[2]:
- pl0500 FLAME DRAGON [1000, 5,5,1,300, 1,1,1,300] — guide: B ammo 5, X ammo 1. Both
  weapons refillType 1 (gradual, matches the (al)-era refill enum), param 300.
- pl0503 CYBER DEATH DRAGON [2500, 5,5,0,300, 8,8,0,300] — guide: X ammo 8.
- pl0505 DEATH HEAD [500, 10,10,0,180, 1,1,0,180] — guide (level-glitch lore): 10 B ammo.
- pl0615 G RED [200, 5,5,0,180, ...] — the (ag) live anchor, refillType 0 (all-at-once).
Also: SDA's measured DEATH ICBM HP 118 sits exactly at pl0d06 row[11] (rows step +2 from
96) — the guide number lies on the extracted lattice, further validating both. The
refillParam=180/300 reading as "refill timer frames (3s/5s)" is a strong data-level
inference, NOT code-derived — verify in trace T7 before promoting.

**2. Observational mechanics (upgrade several taxonomy items to observed-behavior):**
- **Passive contact damage EXISTS** (upgrades findings mechanic L from wiki-only):
  speedrunners report big borgs (e.g. the plasma dragon) stepping on allies and thereby
  granting them hit-invincibility — i.e. contact hits are real hits that trigger the
  i-frame machinery. Also "hitting allies to make them invincible" is deliberate speedrun
  tech — friendly-fire hits granting invincibility windows (consistent with the
  balance-break stagger i-frames already ported).
- **Self-damage is move-scripted suicide, not owner-collision**: the Death ICBM detonates
  and dies as part of its own move. Consistent with (al)'s finding that owner exclusion is
  unconditional — no collision-level self-hit needed; the move kills its owner directly.
  Resolves the W4 puzzle's direction: look for a self-kill in the ICBM move handler, not a
  collision flag.
- **OHKO reading confirmed directionally**: the ICBM blast outright kills low-HP borgs
  (satellites, prototypes) but only damages fortresses/high-HP borgs — i.e. "OHKO" is big
  hpDamage vs HP pools, matching the CHECKED_CLOSED no-OHKO-path finding.
- **Shields are physical blockers**: knight-family shields block breath attacks
  positionally (the two-shield knight blocks more than one-shield knights) — barrier/guard
  is at least partly hitbox/object-level, relevant to W7 and the /40 divisor question.
- **Hyper meter fills from damage dealt AND received** (manual/guides), fill rate varies
  by attack; **burst damage bonus evaluates at HIT time, not fire time** (a projectile
  fired before activation gets the bonus if it lands during burst) — consistent with
  +0x6fc being read inside the damage resolver, and a good T3 test vector.
- **X doubles as flight control on flyer borgs** (dive; A/hold = rise) — the B/X
  contextual resolver must account for per-borg X overloading, not just "X = special".
- **Cyber Death Dragon mid-air X fires a dual shot** when multiple X ammo remain — an
  air-context ranged variant (relevant to command subtype 4 = air/elevated, (ai)).
- **Post-hit damage resistance "lasts several seconds"** per speedrunners — cross-
  validates the 60-frame combo/falloff windows (mechanic U) at the feel level.

### (an) Guide-corpus extraction: borg-ID encoding validated; (al) healing finding CORRECTED to vampire lifesteal; five-context melee taxonomy (2026-07-03)

Source: user-supplied text of the GameFAQs guides (Voltrox747 move list + glitch FAQ,
Sabre929 borg list, Fury_Hikari walkthrough, t3h_chosen_1 ninja guide). All content
below is extracted FACTS (numbers/mechanics), paraphrased — treat as OBSERVED_GUIDE
tier: reliable player measurements, never DERIVED. Full curated anchor data:
research/decomp/data/guide-anchors-movelist.json.

**1. The 20th-Force glitch codes ARE the two-byte spawn ids — roster-validated.**
The glitch FAQ's force-code binary encoding (sum of 2^(force-1)) produces the game's
borg id. Cross-checked against packages/assets/data/borgs.json: Sword Knight code {10}
= 0x200 (family 02 variant 00), Normal Knight {2,4,10} = 0x20a = pl020a NORMAL KNIGHT
(exact roster match), Imperial Knight {1,4,10} = 0x209 = pl0209 (exact), Demon Samurai
{1,9,10,11} = 0x701 = pl0701 (exact), Vampire Knight {2,9,10,11} = 0x702 = pl0702
(exact), Vlad {2,4,9,10,11} = 0x70a = pl070a (exact). The FAQ's per-borg code list is
therefore a COMPLETE independent id→borg mapping usable for validation.

**2. CORRECTION to (al): the HP-increment path at chunk_0003.c:6318-6323 is VAMPIRE
LIFESTEAL, not nurse healing.** The gated ids 0x702/0x70a are Vampire Knight/Vlad —
the guide-documented lifesteal borgs ("regains health with any melee attack") who ALSO
"constantly lose HP at ~2-3/sec". So: (a) DAT_803b0638[slot] accumulates that slot's
dealt melee damage for HP regain (lifesteal), and (b) a periodic HP-DRAIN loop must
exist for these borgs — revising (al)'s and the status sweep's "no DoT/periodic drain"
negative (the drain writer was simply not found; re-grep with the vampire path as the
anchor). The companion check at :6237 gates ids 0x701/0x708 = Demon/Akuma Samurai —
the guide-documented "swords grow in length as enemies die" mechanic, i.e. that site
is the sword-growth trigger, not a heal-peer check.
**Nurse healing is a separate mechanism**: X-attack targeted heal with fixed amounts —
Death Borg Theta 37 HP (id 0x906 by code {2,3,9,12} — family 09 = nurse family),
Angel Nurse 50 (pl0900), Angel Rescue 100 (pl0908), Nao (pl090d) heals ally or enemy.
ATK-019 rewritten accordingly.

**3. Five-context melee taxonomy (mechanics D-K refinement).** The move list documents
melee variants as a UNIVERSAL five-way split: standing, ground dash, landing (from a
jump), normal air, air dash — plus per-borg extras: "above enemy" specials (sword-drop
stabs: Normal Ninja/Sasuke/Double Ninja/Death Borg Alpha; Sapphire/Ruby Knight
above-enemy lance stab) and a flyer set (hovering, dashing, diving). Transformed forms
(Gold/Metal Hero, Panther/Titan/Eagle/Victory robots) swap the whole moveset; some
moves differ per form. This is the concrete context vocabulary for the resolver
(ATK-004 enum is compatible; add above_enemy already present, flyer contexts map to
fly state) and for trace T2's capture matrix.

**4. Move-attribute vocabulary (candidate hit-record flag semantics):** CN =
cancellable into other attacks; SB = breaks through shields; MH = hits continuously
while in contact (matches the rehit-interval mechanism, chunk_0013.c:1175-1182); WV =
emits a wave projectile alongside the swing. Guide also documents per-move "Recharge:
Yes/No" for projectiles = regenerates without emptying first — i.e. the per-move
gradual vs all-at-once flag, cross-validating the stat-row refillType column ((am));
a scripted sweep of guide Recharge flags vs extracted refillType per borg is a cheap
validation task.

**5. Status/effect observations with numbers:** poison (Poison/Venom Worm) = +20/+26
damage-over-time on top of the hit; freeze (Ice/Blizzard Dragon) = frozen state whose
duration SHORTENS with button/stick mashing (mash-to-recover — connects the (am) mash
counter to status recovery as a second consumer candidate); Chrono Samurai = time stop
(enemies stagger-locked, max 115 observed on Neo G); Pop Honey = aim-scramble spin;
Switching Ninja = position swap; Death Borg Omicron/Bug Witch = transform victim
(temporary); Patra/Isis = enlarge (stat up), Bastet/Sekhmet = shrink (stat down);
Barrier Girl self-barrier absorbs ~80, Guard Witch enemy-blocking barrier ~200, Shield
Witch ~280; Thunder Robot = damage tether between allies; Wire/Arrow tether mechanics;
dragons' stomp contact damage listed as an explicit per-dragon "Special" move with
values (22/44) — contact damage is AUTHORED PER-BORG data, not an engine-wide rule
(mechanic L refinement).
**Fusion forms**: Machine Dragon combined X charge measured 2280 on a Sirius; the
dual-control split is attacks vs movement per player (contradicts the corpus reading
of one shared command struct — trace target).
**Self-damage**: Death ICBM/Walking Bomb/Death Bomb explode on CONTACT (collision-
triggered suicide, no button) — consistent with (al)'s unconditional owner exclusion:
the mover dies by its own scripted detonation, not by being hit.

**6. Level/color byte encoding (glitch FAQ, matches zz_005814c_'s +0x3ea u16 +
+0x3ec byte writers from (ak)):** stored value = (colorVariant << 8) | level, with
color variants 0=normal, 1=alt, 2=gold, 3=silver, 4=crystal, 5=black; level byte
1-255. Levels beyond the authored row range read neighboring rows (matches the (ag)
row arithmetic and the SDA mutation lore). Also: EXP rule per Fury_Hikari — every
participating borg gets 2 exp per battle (1 on loss/quit); per-borg exp-to-level
varies (10/20/40).

**7. Damage anchors**: the move list's per-move damage values were measured against a
LEVEL 7 Neo G Red (or Blizzard Dragon for stagger-prone moves) — usable as end-to-end
damage-formula validation vectors once level floats are wired (e.g. G Red B shot = 17,
melee ground combo = 70, Neo G Red X = 70; Death ICBM ~500 vs large borgs; Beam
Satellite X = 476 vs Blizzard Dragon pre-stagger). Bomb-type X of ICBM Tank = 584.

### (ao) Official NA instruction manual scanned and read — controls/HUD semantics, tier CONFIRMED_MANUAL (2026-07-03)

Source: user-supplied scan of the North American instruction manual ("Imgur Album Gotcha
Force Manual NA.zip" at repo root; extracted pages read in-session, pages 4-6 are the
payload). Tier: CONFIRMED_MANUAL — official Capcom documentation of player-facing
behavior; stronger than fan guides for control/UI semantics, still not numeric ROM
truth. Paraphrased facts:

- **B contextual rule is OFFICIAL**: far from the enemy = open fire; close = battle
  (melee) attack; and the TARGET CURSOR changes yellow -> red to indicate battle mode.
  The melee/ranged threshold is therefore HUD-observable — trace T1 gains a visual
  calibration signal for FLOAT_8043762c (watch the cursor color flip vs logged
  distance). Feeds mechanic A/B and ATK-003.
- **Separate B and X ammo counters are OFFICIAL** ("B Bullets" / "X Bullets" HUD
  meters) — binding the ROM's weapon cells: weapon 0 = B-attack ammo, weapon 1 =
  X-attack ammo. ATK-009 follow-up unlocked: the port's X/special should consume
  weapon cell 1 (today specials are cooldown-only).
- **Charge Gauge OFFICIAL**: hold B to fill; at max, release for a super Charge
  Attack (the port's chargeable-shot model matches; HUD gauge exists).
- **Y = Power Burst**: press when the burst gauge is at MAX; friends pressing at the
  same time get simultaneous power bursts — reading the (aj) +0x6fb = 6 arm window as
  the co-op simultaneity tolerance (reconcile in T3). Burst meter officially "fills as
  the player inflicts and receives damage" (StrategyWiki interface page corroborates).
- **L AND R both switch targets** (port models only R); **Z = HOLD to lock onto your
  partner** (port models Z as press-to-cycle ally lock — semantics differ);
  **A while blown away = jump away from danger** — an AIR RECOVERY mechanic the port
  lacks entirely (new queue item W14); **stick double-tap = evade dash** (port
  triggers dodge differently — W15); A hold = booster jump rise, with a Jump Gauge
  showing multi-level jumps.
- Versus rule setup: GF-energy limit adjustable (Y raises it), X toggles computer
  attacks on/off, X changes the computer force — mode-setup semantics for battle.ts
  config, not combat math.
- Extracted manual pages live in the session scratchpad only; the zip stays at repo
  root (user-owned scan, do not commit extracted images).

### (ap) Japanese Wikipedia extraction: Gundam-vs lineage, auto-shield rule, level cap, flight models (2026-07-03)

Source: user-supplied machine translation of the Japanese Wikipedia article (CC-BY-SA;
paraphrased facts only). Tier: OBSERVED_WIKI — secondary-source claims, some possibly
editor interpretation; use as taxonomy/anchors, never numeric truth.

- **Design lineage (interpretive lens)**: the game is by the Gundam-vs.-series planner
  (Atsushi Tomita) and explicitly based on that series' control/system model; some of
  its systems (charge attacks, indestructible shields) were later re-imported into
  Gundam SEED Union vs. Z.A.F.T. When a mechanic here is ambiguous, the Gundam-vs
  convention (knockdown/juggle rules, boost economy, auto-aim melee/shot split) is a
  reasonable interpretation PRIOR — never evidence, but useful for framing traces.
- **Two attack buttons with AUTOMATIC shot-vs-melee selection** (restated as the core
  difference from Gundam vs.' three buttons) — third independent confirmation of
  mechanic A. Some borgs bind one button to fly/transform instead; some have no melee
  at all or shoot regardless of range (per-borg binding table, consistent with the
  +0x4ec action-table reading and W12).
- **AUTO-SHIELD RULE (new, feeds W7)**: shields have INFINITE durability, take no
  damage, require no input — a frontal hit while NOT attacking is blocked
  automatically. This is a concrete candidate semantic for the /40 "block divisor"
  gate (record flagsA & 0x1000 + victim +0x59c & 0x1000, formula step 18): +0x59c
  (from pl data u16@0xa8) as "has shield" and the state condition as "not attacking,
  hit from front". Trace vector: knight vs pea-shooter, log damage while idle-facing
  vs while mid-swing. Distinct from the Witch/Barrier-Girl OBJECT barriers, which have
  finite HP (80/200/280 anchors, (an)).
- **Level system**: +1 exp per battle appearance, +1 more on victory; LEVEL CAP 10
  (vs Fury_Hikari's "2 per participation, 1 on loss" — minor accounting discrepancy,
  both cap-10 compatible). Level-up raises HP, ammo, and shortens charge/reload time.
  Feeds ATK-020: valid level range is 1-10 for normal play (glitch levels beyond are
  out-of-range row reads); "charge/reload time scales with level" is another candidate
  consumer for the unresolved refill-rate source (Q7).
- **Three flight models** (movement fidelity, new queue item W17): (1) winged borgs:
  unlimited-duration button-flight, constantly moving forward, stick steers left/right
  only, altitude locked during flight; (2) air-class borgs: permanently airborne,
  stick climbs/descends, jump button accelerates; (3) boost borgs: the existing
  boost-jump model. The port's single FLY_MULT model matches none of these exactly.
- **Tribe-affinity corroboration for the type matrix**: the article states explicit
  tribe-vs-tribe modifiers (gun slightly weaker vs girl; musha slightly stronger vs
  knight; angel slightly stronger vs demon; tank stronger-attack/weaker-defense vs
  flying) — matching the ported 20x20 matrix's sparse ±5-25% cells ((l)/(w)). A cheap
  validation: check the extracted matrix cells for exactly these four asymmetries
  using the category remap.
- **X Charge (JP name for Power Burst)**: consumes the battle-accumulated gauge to
  strengthen "the team" for a limited time (equivalent to Hyper Combination in the
  contemporaries) — team-wide phrasing is loose secondary-source wording; the
  per-actor +0x6fc model stands until T3 says otherwise. Combination requires
  specific pairs + X Charge; in 2P the fused body's controls are split between
  players (consistent with the guide's attacks-vs-movement split, still conflicting
  with the corpus shared-command-struct reading — T3 item).
- Misc: hidden per-enemy-type drop points accumulate toward borg/crystal rewards
  (meta-game); ~18h first lap; boss battles vs the giant leader use GF energy to
  grow the player borg giant (story finale mechanic — out of combat-port scope).

### (aq) 100%-completion save added (gotcha_force_100_usa.gci) — trace enabler + save-format datamine (2026-07-03)

User added a user-owned 100% NTSC-U save at repo root: `gotcha_force_100_usa.gci`
(validated: GG4E08, "GG4E_GOTCHA_FORCE_USA", 0x40 GCI header + exactly 10 x 8192-byte
blocks — matching the manual's 10-block requirement ((ao)); internal comment dated
2025-01-15). Two uses:

1. **Trace enabler**: every borg needed by the attack-mechanics trace plan (fusion
   pairs for T3, status borgs for T8, solid/piercing projectile borgs for T5/T6,
   gradual/all-at-once/deploy borgs for T7, per-record hitStrength probes for T9) is
   unlocked. This save is now the STANDARD starting save for T1-T10 — noted in
   attack-mechanics-trace-plan.md.
2. **Save-format datamine (in flight)**: the Gotcha Box collection should persist the
   per-borg (colorVariant<<8 | level) u16 ((an) §6) plus EXP — decoding it can pin
   level/exp storage without a live trace and gives packages/save (currently a stub)
   its format spec. Agent dispatched: locate box/force arrays via roster-id patterns
   (family<<8|variant vs borgs.json), cross-reference the ROM's CARD/serializer code,
   document checksum. Deliverables: scripts/inspect-gotcha-save.mjs +
   research/format-specs/save-gci-format.md.

The .gci stays at repo root uncommitted (user-owned save data — same policy as the
.sav files and disc image; add to .gitignore if not already covered).

**(aq) addendum:** two more independent saves added at repo root (all validated GG4E08,
10 blocks): `allborgsgotcha-force.28411.gci` (internal date 2023-03-04, all-borgs) and
`gblack-galatic-emperor-save=gotcha-force.22132.gci` (2011-11-17, advertised as
containing the two unobtainable borgs). Decode upgraded to three-way DIFFERENTIAL
analysis (identical bytes = format/defaults; differing = state) with checksum
verification across all three. Special-id predictions from the validated glitch
encoding: Neo G Red 0x0629, G BLACK 0x062a, GALACTIC EMPEROR 0x0e04 (G Red 0x0615
already roster-confirmed) — finding 0x062a/0x0e04 only in the 2011 save doubles as
box-array + id-table validation. All *.gci gitignored.

### (ar) User-supplied secondary RE survey — mostly redundant, three usable leads (2026-07-03)

A user-supplied research report (AI-survey style; treat every claim as
UNVERIFIED_SECONDARY) restated known ground (Sysdolphin lineage §2, Melee-map reuse,
Dolphin watchpoint method §h, m2c/HSDRaw; its "wake-up invincibility 60.0 @0x80437448"
example is this notebook's own §(a) with slightly garbled instruction addresses).
Extracted leads worth keeping:
1. **Mode-conditional wake-up invincibility (TESTABLE)**: claims the wake-up i-frame
   path is bypassed in Challenge/Story via a conditional branch before the +0x720
   write, so CPU pressure works in single-player. Unverified; possibly related to the
   (af) respawn-reset conditional (+0x6cb==1 -> 30.0 else 60.0, FUN_80060b60). Check:
   grep conditional guards around every +0x720 = 60.0 write vs the mode byte
   (PTR_DAT_80433930[0x32] family) — or T4 trace: wake up a CPU in Versus vs Challenge
   and watch +0x720.
2. **Blender SysDolphin addon imports CameraSet nodes as animated cameras** — direct
   tooling lead for the camera workstream (apps/game camera is OrbitControls, known
   non-1:1) and any title-sequence port; complements the existing HSDRaw pipeline.
3. **NeoGF toolchain** (gcmtool/afstool/pzztool/mottool/mdttool/doltool, Python) —
   community equivalents of this repo's extraction scripts; cross-reference if a
   format edge case (e.g. the POBJ "out of struct range" case) resists the current
   pipeline. Also: AObj F-curve tracks are Hermite-interpolated — verify
   packages/formats/src/hsd-anim.ts replicates tangents, not linear lerp (fidelity
   check for animation timing).

### (as) Three targeted hunts: mode-conditional respawn i-frames RESOLVED, nurse-heal entry found, knockback magnitude still open (2026-07-03)

Corpus greps (single-pass agent) + same-session verification reads:

- **Respawn invincibility is mode-conditional in DURATION, not bypassed** (refines the
  (ar) survey claim). ROM float dump re-verified THIS session: FLOAT_80437558 = 30.0,
  FLOAT_80437564 = 60.0 — confirming (af)'s mapping and correcting the grep agent's
  swapped reading. FUN_80060b60: `+0x6cb == 1 -> +0x720 = 30.0, else 60.0`
  (chunk_0007.c:6787-6791). NEW: the +0x6cb writer is chunk_0007.c:2625-2638 — set
  once per actor (when active and unset) to 1 under a mission-mode-ish condition,
  else 2; the exact condition expression still needs a careful read (agent elided
  it). So story/mission actors get HALF the respawn protection of versus actors —
  a portable, testable rule once the writer's condition is quoted. The balance-break
  grant (zz_005c290_, chunk_0007.c:3997) stays unconditional 60.0. No "bypass" exists.
- **Nurse X-heal entry point found**: chunk_0006.c:3374-3379 — spawn ids 0x900/0x90d/
  0x908 (Angel Nurse / Nao / Angel Rescue; note DEATH BORG THETA 0x906 is NOT in this
  check — its 37-HP heal must ride another path) install FUN_8004ecb0 as the object
  callback. Read this session: FUN_8004ecb0 (chunk_0006.c:3405-3411) is a trampoline
  — `(*(&PTR_FUN_802d1130)[obj+0x18])(obj)` — i.e. the heal logic sits behind ANOTHER
  dispatch table at 0x802d1130, dumpable exactly like 0x802d3570/0x802da740. Next
  step queued. CORRECTION to the agent's report: its "partner heal via zz_002f8dc_"
  is a misread — zz_002f8dc_ is the kill-event accounting ((af)); the call at
  chunk_0003.c:8055 with the partner pointer is kill-credit routing, not healing.
- **Knockback magnitude consumer: STILL NOT FOUND** (honest negative). The agent's
  "found" quote is zz_00300bc_ itself — the already-decoded angle WRITER ((p)) — and
  it misread the per-move yaw/pitch TRIM bytes (record +0x14/+0x15) as a magnitude
  source. One unverified lead survives: velocity-field writes near a +0xb4 read at
  chunk_0006.c:2579-2585 and 7257-7263 (careful: (ah) identifies +0xb4 as the
  defender level/defense float — plausible misattribution). Needs a careful re-read;
  trace T9 remains the reliable path.

### (at) PTR_FUN_802da740 dumped: 12 handlers — REINTERPRETED as the hitbox SHAPE-KIND evaluator table (2026-07-03)

Corpus dig (single-pass agent; table dump verified against boot.dol). The 12-pointer
table at 0x802da740 (0x8003a4b8..0x8003ca48, all bodies in chunk_0004.c:5316-6600,
boundary confirmed by non-code data after entry 11) dispatches on the byte the
chunk_0013.c:1172 caller reads from the HIT-RECORD — i.e. this is most plausibly the
**shapeKind evaluator table** for the 0x50-byte hit-bin records (hit-bin-format.md's
u8 +0x00 "hitbox shape dispatch"), NOT per-projectile behavior. The handlers compute
geometry only (vertex frames, face normals, spans, radial points); collision PAIRING
stays in the chunk_0003.c passes — consistent with the (al)-era negative.

Shape-kind candidates (agent labels, single-pass; verify before schema use):
0 simple point/capsule (optional bounce via owner flags 0x81) · 1 bouncing with
WALL-CONTACT SELF-KILL (`obj+0x13 = 1`, chunk_0004.c:5400 — detonate-on-terrain) ·
2 rigid 8-vertex/6-normal polyhedron · 3 truncated 3-normal variant (Likely barrier/
shield plane) · 4 expanding bidirectional pulse (front/back span from owner velocity)
· 5 guided/homing frame (state machine 2/3/5) · 6 homing 4-point · 7 beam/trail
6-point · 8 spinning 6-radial disc (60-degree step via FLOAT_80437020) · 9 shuriken
6-radial with proximity pre-check · 10 straight-line penetrator span · 11 proximity
sphere with squared-distance AOE falloff (chunk_0004.c:6563-6583 — the best candidate
carrier for ICBM/Walking-Bomb contact detonation, W4/W11).

Practical yields: (a) the hit-bin shapeKind byte now has candidate semantics — feeds
the hitbox port (ATK-005/X mapping) and the trace T2 capture (log shapeKind per move);
(b) obj+0x13 as a self-kill byte and shape 11's proximity-AOE shape give the suicide
borgs a concrete mechanism path; (c) projectile-vs-projectile/solidity is NOT here —
Q6 narrows to the chunk_0003.c collision passes' list pairing and per-move flags.
CAVEATS: agent-reported struct offsets partially conflict with the (al)-era object
struct reading (e.g. +0x28 owner vs +0x20) — a reconciliation read is needed before
any of this reaches a ticket as DERIVED.

### (au) Save-file format DECODED — serializer found in ROM, CRC + scrambling cracked, per-borg level/color/exp storage proven (2026-07-03)

Full spec: research/format-specs/save-gci-format.md; inspector:
scripts/inspect-gotcha-save.mjs (argv = .gci path). Highlights (container layout is
DERIVED_ROM — the serializer was located verbatim in chunk_0014.c):

- Image = banner/comment + 5 CRC'd sections: options / Gotcha Box (2000 x 16-byte
  cells + 1000 x 12-byte acquisition log) / 20 force slots + 200-entry member pool /
  story progress (GF energy u32 at s4+0x78; cap constant 0x898 = 2200 via
  zz_0181c30_) / profile (Shift-JIS player name, save counters, two 206-byte per-borg
  color-catalog bitmasks).
- Integrity: CRC-16 poly 0x1021 (zz_008e704_), residual-0 — validates 6/6 regions on
  ALL THREE saves. Sections 2/3/5 are XOR-scrambled with a keyed-digest-derived byte;
  recovered per save and verified. Re-signing edited saves needs the ROM digest/LUT
  tables (documented as the remaining blocker).
- **Borg record = u16 id (family<<8|variant; 0xFFFF empty), u8 color 0-5, u8 level
  (0-BASED), u32 acquisitionSeq, u32 exp.** Cross-save differential proof: the same
  acquisition-lineage Neo G Red appears L3/exp99 (2023 save) -> L6/exp214 (2025) —
  per-borg EXP thresholds are now empirically derivable from save data (feeds the
  (ap) level system; W6/ATK-020 follow-up).
- Predictions CONFIRMED: G BLACK = 0x062A and GALACTIC EMPEROR = 0x0E04 found exactly
  in the 2011 save's pool; starter code hardcodes 0x615/0x629; roster-id hit rate
  100% across every parsed entry of all three saves (borgs.json 208 ids).
- Premise corrections recorded: 20 force slots (not 10), only slot 0 used by story;
  the u16 at box+0xABE0 is the BOX COUNT, not GF energy; levels store 0-based and
  stay low even on 100% saves (leveling concentrates in ~15 used borgs).
- Cost table zz_0066168_ indexes 6 cost entries per variant = 6 colors — color
  variants have their own costs (new mechanic detail).

### (av) Wiki per-move infobox taxonomy + AR box anchor + LEVEL->ROW MAPPING SOLVED empirically (2026-07-03)

Source: user-supplied wiki borg pages (CC-BY-SA; facts paraphrased), Borg Modifier AR
page, Data Crystals page, Codejunkies AR list. Tier OBSERVED_WIKI unless noted.

- **LEVEL -> STAT-ROW MAPPING (4-point exact cross-validation, this session)**: wiki
  lvl-1/lvl-10 values vs extracted rows: pl0615 G RED 200/5 = row[2], 290/8 = row[11];
  pl0102 GATLING GUNNER 250/100 (+X ammo 4 = weapon cell 1 [4,4] — another B/X cell
  binding hit) = row[2], 295 = row[11]. **Empirical rule for "Normal Level-up
  Schedule" borgs: rowIndex = displayLevel + 1 = savedLevel(0-based) + 2.** This is
  the rule ATK-020's selection needed; the (ag) row formula's subIdx/+0x3ec split
  producing it still deserves one code-side confirmation (DAT_804339e8's sparse values
  don't directly equal level+1 — subIdx must carry part of it). The wiki category
  "Borgs Following the Normal Level-up Schedule" implies DEVIATING schedules exist
  (ninja-guide lore: Sasuke/Shijima gain ammo with level; Death Borgs grow fast) —
  per-borg schedule = which rows the level walk visits.
- **Per-move wiki infobox fields are exactly the port schema's blocked fields**:
  Solidity (Solid/Nonsolid), Penetration (None / Borgs / Total), Refill Type
  (All at once / Gradual), Explodes (Y/N), Effect, lvl-1/lvl-10 ammo — the community
  has this cataloged across ~248 pages. Verified samples: G Red Beam Gun = Nonsolid /
  Penetration: Borgs / All-at-once / 5-8 ammo (refill type matches extracted w0type=0);
  melee + charge + X = Penetration: Total (matches the melee-total-penetration
  taxonomy); Gatling Gunner grenade = SOLID + Explodes. **Penetration is a 3-class
  per-move enum {None, Borgs, Total}** — the target semantics for ATK-008's policy
  field and the T5/T6 traces. HARVEST PLAN: direct fandom fetch 402s; the efficient
  path is a MediaWiki Special:Export XML dump of the borg pages (user-suppliable),
  then a cheap agent parses all Moves tables into guide-anchors data.
- **Borg Modifier AR code (NTSC): 16-bit write of a borg id to RAM 0x80587F10** — a
  live anchor into the Gotcha Box memory image (bottom-right cell id; PAL variant
  0x80591550). Useful for save<->RAM structure mapping and Dolphin-side box editing;
  also yet another independent confirmation of the id encoding (page's own G Black
  example = 0x062a). Codejunkies encrypted codes (inf HP/ammo/GF, one-hit kills,
  collection complete) decryptable via GCNCrypt (game id 245 NTSC) if their addresses
  are ever wanted — low priority, our RAM anchors are better.
- **Data crystals**: code = colorLetter + 3-digit borg number + piece letter A-E;
  90/206 borgs need 2-5 pieces; per-borg dataCrystals count on wiki pages (G Red 1,
  Gatling Gunner 2). Collection metadata — cross-references the save's acquisition
  log; not combat-mechanics.

### (aw) Full wiki harvest: 459 per-move records extracted and cross-validated against ROM rows (2026-07-03)

Using the user's own wiki session (cookies supplied in-session; kept in scratchpad only,
never committed), all 242 content pages were fetched via the MediaWiki API as wikitext
and the structured templates parsed into
**research/decomp/data/wiki-borg-moves.json** (extracted field values only; source
CC-BY-SA with attribution in the provenance block). Contents: 207 borg pages (205
roster-id-matched), BorgInfoBox fields (number/cost/crystals/tribe/type/rarity/
lv1-lv10 HP/stats/jump type/level-up schedule) + 459 moves from BorgMoveBox/
BorgMoveSimple templates with per-move Solidity / Penetration (None-Borgs-Total) /
RefillType / lv1-lv10 Ammo / Explodes / Effect.

Embedded cross-validation vs the extracted ROM stat rows:
- **HP lv1/lv10 vs rows[2]/[11]: 200/203 exact** — the (av) level->row rule
  (rowIndex = displayLevel + 1) is near-universal; the 3 mismatches are the
  non-normal-schedule candidates (listed in the JSON) and the concrete lead for the
  per-borg schedule question.
- **B-shot RefillType vs w0 type byte: 113/117** — wiki "All at Once" = type 0, wiki
  "Gradual"/"Over time" = type 1 confirmed at scale. One mismatch pairs a wiki
  "Over Time" with ROM type 2 (pl0f05) — first behavioral hint that type 2 is a
  gradual VARIANT (the unread refill mode from (al)-era ammo work).
- **B-shot lv1 ammo vs w0 max: 119/128** — 9 mismatches recorded verbatim for
  adjudication (several look like the wiki counting burst volleys vs ammo units).

Practical yields: ATK-007/ATK-008 now have per-move solidity/penetration data for the
whole roster (taxonomy tier OBSERVED_WIKI — trace T5/T6 still decides engine truth);
the effects column seeds the status-id mapping (Q8/T8); the mechanics pages' wikitext
(Attacks, Level, Stages, Power Burst, Missions, etc.) was harvested to the session
scratchpad for reference — re-harvest with fresh cookies if needed later (raw bulk
wikitext intentionally not committed; the extracted dataset is the artifact).
