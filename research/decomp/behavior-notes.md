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
mapping" for a proprietary binary we can't byte-match without Nintendo's CodeWarrior compiler.

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
