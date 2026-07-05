# Action-script VM + G Crash state machine decode (2026-07-05)

Question: the port generic-archetypes X-specials (projectile/aoe/melee). To port the real
source mechanics we needed (a) the 10 undecoded action-script stream opcodes and (b) the
per-family state handler that drives G RED's X-special "G Crash" motion. Both decoded this
session from `research/decomp/ghidra-export/*.c` + `user-data/GG4E/disc/sys/boot.dol`.

## Section A — Stream VM opcodes 0x02-0x07, 0x0b, 0x0c fully decoded

The interpreter is `zz_004cd24_` @ `chunk_0006.c:1996`, dispatching on the 18-entry handler
table `PTR_FUN_802d0da0`. The anim-sound decode doc had marked 0x02-0x07, 0x0b, 0x0c, 0x11 as
"not decompiled" but op 0x11 (`FUN_8004cccc`) IS in `chunk_0006.c:1973`. The remaining 8 were
disassembled from boot.dol with `scratchpad/ppc_disasm.py` (PPC32 decoder; corpus at
0x8004c424..0x8004c7fc).

**Calling convention for every handler:** `void handler(int actor /*r3*/, uint partMask /*r4*/, int *streamPtrPtr /*r5*/)`. The first action is always `lwz r6, 0(r5)` (load stream ptr), a
`rlwinm. r0, r4, 0, N, N` (test one bit of partMask — which bit selects the opcode's
part-gating), then `addi r0, r6, <size>; stw r0, 0(r5)` (advance stream by record size), and
`bclr` if the part bit is clear. Record layout is `[op, b1, b2, b3, ...]`.

| op | size | part bit | Operand effect (DERIVED — every store confirmed in the disasm) |
|----|------|----------|---------------------------------------------------------------|
| 0x02 | 8 | bit 0 (part 0 only) | b2 → actor+0x1cef (part-0 state+0x1b), b3 → +0x1cf0, b4 → +0x6e8, b5 → +0x6e9. b1 selects a follow-up on actor+0x582: b1==-2 toggles (+0x582 ^= 1), b1==-1 leaves it, else +0x582 = b1. **The +0x1cef write is the "contact/hit-connected" flag the G Crash phase-1 handler reads (see Section B).** |
| 0x03 | 8 | bit 1 | b1 → +0x1d0f (part-1 state+0x1b), b2 → +0x1d10. If halfword b6..b7 (u16) != 0xffff: reads word +0x5e0, clears bits 20..27 (`rlwinm 0,28,19`), then ORs in `(u16 b6..b7) & 0xff00` (mask `rlwinm 0,20,27`). So op 0x03 sets a byte-nibble in the +0x5e0 control word that downstream state handlers gate on (e.g. FUN_8018e888 line 798 tests `+0x5e0 & 0xa0`). |
| 0x04 | 4 | bit 2 | b1 → +0x1d2f (part-2 state+0x1b), b2 → +0x1d30. Per-part flag setter. |
| 0x05 | 4 | bit 3 | b1 → +0x1d4f (part-3 state+0x1b), b2 → +0x1d50. Per-part flag setter. |
| 0x06 | 2 (post-lhau) | any of bits 0..3 | Reads a u16 (`lhau r8, 2(r7)`) — the halfword is the per-part TARGET value. For each part bit set in partMask, writes 1 to +0x1cf2 (part 0) / +0x1d12 (part 1) / +0x1d32 (part 2) / +0x1d52 (part 3). These are the per-part "go" flags consumed by the part-anim blenders. |
| 0x07 | 4 | bit 0 | b2 → conditional sthx (halfword store); on no-target path reads `*(*(actor+0x4b0) + 0xbe)` and `+0xbf` (the family descriptor's two "default hand" bytes) and stores them to +0x1d74/+0x1d75; then copies +0x1d74→+0x1d8c and +0x1d75→+0x1d8d. **Hand/weapon-swap op**: switches which weapon model is attached per part for the duration of the move. |
| 0x0b | 4 | bit 1 | b2 is a bitmask over actor+0x709. If b1 == 0: `+0x709 \|= b2` (set bits). Else: `+0x709 &= ~b2` (clear bits). +0x709 is a generic per-actor flag byte (movement / FX-gating). |
| 0x0c | 4 | bit 0 | b2 is a bitmask over actor+0x57a AND +0x57b. If b1 == 0: `+0x57b \|= b2`. Else: clear b2 from BOTH +0x57a and +0x57b. +0x57a/+0x57b are flag bytes consumed by the state dispatcher (`chunk_0009.c:4097/4100` writes them for state transitions). |

**Conclusion A:** NONE of these 8 opcodes directly writes velocity (no stores to +0x44/+0x48/+0x4c
or +0x38). They are **per-part STATE / FLAG / WEAPON-SWAP setters** that configure the actor's
sub-state machines, FX flags, and hit-contact latches. The actual MOTION (velocity, position
integration) is in the **per-family state handlers** (Section B), NOT in the action-stream
bytecode. The stream is the choreography (anim + hitbox timing + state flags); the family
handler is the physics driver.

This is why generic-archetype porting cannot reproduce real move motion: the motion is in C
code unique to each borg family, not in shared data tables.

## Section B — G RED "G Crash" X-special is a 4-phase family state machine

Source: `chunk_0047.c:777-970`. Reached via the cue chain (`cue-script-stream-decode-2026-07-04.md`):
command type 2 (X) → `+0x4f0` cue table entry 44 → state `[61, 0]` → `FUN_80065dfc`
→ `(**(code**)(actor+0x4b4))()` → G RED root `zz_018d24c_` actionIndex-2 entry
**`FUN_8018e888`**. Air-B shares this handler (same actionIndex 2). Phase table is
`0x80365844`; `+0x540` is the phase index. Each phase fn increments `+0x540` to advance.

### Phase 0 — `FUN_8018e888` (launch / start the stream)

```c
// +0x540++ (enter phase 0)
uVar5 = FUN_80066838(*(float*)(actor + (borgNumber % 3)*0xc + 0x86c), actor);
if (uVar5 < 1) { +0x541 = 1; +0xcc = 0; +0x5ac = +0x5ae; }   // not airborne → take off
if (+0xcc == 0) {
  if ((+0x5e0 & 0xa0) == 0) +0x5ac = +0x72;     // yaw = current facing
  else                         +0x5ac = +0x5ae;   // yaw = lock yaw
}
zz_006d144_(actor, 0xc1);                         // helper
sVar2 = *(short*)(actor + 0x3e8);                 // borg number (0x615 G RED, 0x629 NEO, 0x62a BLACK)
fVar3 = FLOAT_8043b110;  // = 0.0
if (sVar2 == 0x629)      { +0x6ea = 1;  set +0x50/+0x48/+0x4c/+0x44 = 0.0;  +0x80/+0x7e/+0x7c = 0; }
else if (sVar2 != 0x62a) { // G RED (0x615) branch
  +0x6ea = 0;
  fVar4 = FLOAT_8043b158;  // = 4.0
  +0x4c = 0.0; +0x44 = 0.0; +0x48 = 4.0; +0x50 = 0.0;   // Y-axis impulse = 4.0
}
else /* 0x62a */         { +0x6ea = 4;  set all = 0.0; +0x80/+0x7e/+0x7c = 0; }
// Reposition: +0x38 = pos - targetPos;  +0x38 *= 0.95 (FLOAT_8043b124);  pos += +0x38
gnt4_PSVECSubtract(pos+0x20, +0x5e8, +0x38);
gnt4_PSQUATScale(0.95, +0x38, +0x38);
gnt4_PSVECAdd(pos+0x20, +0x38, +0x20);
zz_00677b0_(actor);                               // collision clamp
zz_004beb8_(-1.0, actor, 0xf, 4, +0x6ea, -1, -1); // start g4 s<+0x6ea> stream (G RED: g4 s0)
```

Net effect for G RED: impulse (0, **+4.0**, 0); the borg is repositioned 5% closer to the lock
target (the `0.95 × (pos − target)` write adds BACK to pos, so net pos = pos + 0.95·(pos−target)
— i.e. **pushed 95% further from the target**, giving the "leaps away then dashes in" windup
spacing); stream `g4 s0` (kind-15 hitbox) starts.

### Phase 1 — `FUN_8018ea54` (airborne physics + hit check)

```c
zz_004cd24_(actor, 0xf);                          // advance the stream one tick
zz_006d144_(actor, 0xc1);
if (+0x1d10 != 0) zz_006e1ac_(actor, 0xc1, 1);    // per-part FX
FUN_80067310(FLOAT_8043b130 /*=1.0*/, actor, +0x5ae);  // gravity = 1.0, integrate yaw +0x5ae
// pos += scaled velocity delta (+0x38)
gnt4_PSQUATScale(0.95, +0x38, +0x38);
gnt4_PSVECAdd(pos+0x20, +0x38, +0x20);
zz_00677b0_(actor);
if (+0x1cef > 0) {                                // HIT CONNECTED (op 0x02 sets +0x1cef)
  +0x540++;                                       // → phase 2
  +0x38 = FLOAT_8043b110 /*=0.0*/;
  +0x3c = FLOAT_8043b15c /*=10.0*/;               // Y velocity = 10.0
  +0x40 = FLOAT_8043b148 /*=60.0*/;               // XZ dash magnitude = 60.0
}
```

### Phase 2 — `FUN_8018eb2c` (descend with angle-steered XZ)

```c
zz_004cd24_(actor, 0xf);
// +0x38 (vertical delta) accumulates: +0x38 += +0x3c × +0x1dc8 (timescale), clamped to +0x40
// XZ velocity from sin/cos of +0x18da (a yaw angle that phase 3 ticks):
*(float*)(actor+0x44) = +0x38 × zz_0045238_(+0x18da);   // sin → X
*(float*)(actor+0x48) = +0x38 × -zz_0045204_(+0x18da);  // -cos → Z
FUN_80067310(1.0, actor, +0x5ae);
zz_00677b0_(actor);
if (+0x1cef < 0) {                                // hit ended / target down
  +0x540++;                                       // → phase 3
  +0x558 = FLOAT_8043b160 /*=120.0*/;             // landing timer
  +0x50 = *(*(+0x4ac) + 0x6c);                    // copy a family-data byte
}
```

### Phase 3 — `FUN_8018ec34` (land + return to idle)

```c
zz_004cd24_(actor, 0xf);
// tick the steering angle: +0x18da = (+0x18da − 176.0) × 0.9   (DOUBLE_8043b108, FLOAT_8043b100)
FUN_80067310(1.0, actor, +0x5ae);
if (zz_00677b0_(actor) == 0) {                    // grounded
  if (borgNumber == 0x615) { if (+0x1cee == 0) return; }  // G RED waits for wall-contact flag
  else { /* non-G-RED: count down +0x558 by timescale; return early if still > 0 */ }
  // clear X-special flags and return to neutral
  +0x6f6 = 0; +0x73f = 0; +0x5e0 &= ~3; zz_006a5a4_(actor);   // → idle
}
```

### Motion constants (DERIVED from boot.dol, all floats read this session)

| Symbol | Address | Value | Role |
|---|---|---|---|
| FLOAT_8043b110 | 0x8043b110 | **0.0** | base XZ velocity (zero — G Crash's launch is purely vertical) |
| FLOAT_8043b158 | 0x8043b158 | **4.0** | phase-0 Y impulse (the "fly up") |
| FLOAT_8043b124 | 0x8043b124 | **0.95** | relpos scale (borg pushed to 95% of pos-target vector) |
| FLOAT_8043b130 | 0x8043b130 | **1.0** | gravity during phases 1-3 |
| FLOAT_8043b148 | 0x8043b148 | **60.0** | phase-1→2 hit-transition XZ dash magnitude |
| FLOAT_8043b15c | 0x8043b15c | **10.0** | phase-1→2 hit-transition Y velocity |
| FLOAT_8043b160 | 0x8043b160 | **120.0** | phase-2 landing timer seed |
| FLOAT_8043b100 | 0x8043b100 | **0.9** | phase-3 angle decay |
| DOUBLE_8043b108 | 0x8043b108 | **176.0** | phase-3 angle base offset |
| FLOAT_8043b120 | 0x8043b120 | **-1.0** | stream playback rate passed to zz_004beb8_ |
| FLOAT_80439678 | 0x80439678 | **0.95** | (Star Hero X-dash velocity scale — separate family, status doc) |

## Section C — The complete G Crash motion picture

Reconciling with the user's description ("fly up in the air with fire on his fist, then launches
forward with his fist"):

1. **Frame 0 (phase 0):** G Red gets vertical impulse Y=+4.0 (the "fly up"), is repositioned
   5% further from his lock target (windup spacing), and starts the g4 s0 choreography stream.
   The kind-15 hitbox is armed at frame 0 of the stream; the played anim `g04_s00` is the
   81-frame "fist chambered overhead" pose (the action-stream decode proves g4 s0 — NOT
   `special_s1` — is what the command-table X-record runs; the renderer-side
   `borgPresentationAssets.ts` override to `special_s1` is a TUNED mismatch).
2. **Frames 1..N (phase 1):** gravity (1.0) integrates, G Red arcs upward then falls while the
   kind-15 hitbox is live (records 33 @ frames 8-16 close-body, 21 @ frames 53-64 extended-fist;
   the latter is the "fist reached full extension" window).
3. **On hit connect (`+0x1cef > 0`):** G Red dashes forward at magnitude 60.0 with Y=10.0 — the
   "launches forward with his fist". Phase 2 begins.
4. **Phase 2-3:** angle-steered descent, lands, returns to idle.

**Why the port's G Crash is broken:** `combat.ts` `startSpecialAttack` for `archetype === "projectile"`
calls `spawnSpecialProjectiles` which spawns a single forward-velocity "energy" bolt and never
touches the actor's velocity, never advances a 4-phase state machine, and never reads the kind-15
hit windows. The X-special cooldown gates re-presses but no motion happens. Visually G Red plays
his `special_s1` clip (26 frames, stationary) and an energy bolt flies out — the user's
"missing his crash attack" and "doesn't match source".

## Section D — Porting recipe (the real-mechanics port the user asked for)

The motion is per-family code. To port G Crash 1:1 the work is:

1. **New `SpecialDriver` interface in @gf/combat** keyed by `(borgId, button)` returning either
   the existing generic archetype OR a per-family driver. The G RED family driver covers
   pl0615/pl0629/pl062a (and any other family that shares ctor `0x8018ccfc`).
2. **Port `FUN_8018e888..FUN_8018ec34` as a 4-phase state machine** on `BorgRuntime`:
   - Add `xSpecialPhase: 0|1|2|3`, `xSpecialTimer`, `xSpecialAngle` to `BorgRuntime.cooldowns`.
   - Phase 0 (`startSpecialAttack` for the G RED family): set `b.vel.y = 4.0` (impulse),
     reposition `b.pos` along `(b.pos − targetPos) × 0.05` (the 5%-further windup), arm the
     kind-15 hitbox via the existing melee-hit-resolution path (reuse `startMeleeAttack`'s
     active-window machinery with the kind-15 record windows), play anim `g4 s0` (the renderer
     override for pl0615 special should switch back to `g04_s00`/`down_s0` now that the source
     is decoded), set `xSpecialPhase = 1`.
   - Phase 1 (per-frame while `xSpecialPhase === 1`): apply gravity 1.0, integrate; if the
     kind-15 hit connected this frame (track via a per-swing `hitConnected` flag like melee),
     set `xSpecialPhase = 2`, `b.vel = {0, 10, 60}` in the lock-target's direction.
   - Phase 2: steer XZ by a ticking yaw angle; on hit-end (`+0x1cef < 0` equivalent) advance
     to phase 3 with timer 120.
   - Phase 3: tick angle by `(angle − 176) × 0.9`; on ground contact clear flags, return to idle.
3. **The kind-15 hit windows** (`attackHitTables.json` pl0615 kinds[15] = [33, 21]) drive the
   damage/hitstun via the existing melee-hit path — no new hitbox code needed, just route the
   X-special through `startMeleeAttack`'s resolver with the kind-15 leaf substituted for the
   ground-ladder step.
4. **Constants**: lift `G_CRASH = { LAUNCH_Y: 4.0, RELPOS_SCALE: 0.95, GRAVITY: 1.0,
   HIT_DASH_XZ: 60.0, HIT_DASH_Y: 10.0, LAND_TIMER: 120.0, ANGLE_DECAY: 0.9, ANGLE_BASE: 176.0 }`
   into `constants.ts` as DERIVED (every value read from boot.dol this session).
5. **Other families**: each borg family with a unique X-special handler (Star Hero's ramming
   dash `FUN_801121fc` family, Sword Knight's, etc.) needs its own driver ported the same way.
   The generic `archetype: "projectile"` stays as the fallback for families whose handlers
   haven't been ported yet.

The action-stream bytecode itself does NOT need a runtime interpreter port — its motion ops are
state/flag setters (Section A), and the real motion lives in the per-family C state machines.
The streams' value is the choreography (anim + hitbox-arm timing + the contact-flag writes the
state machine polls); those are already decoded into `meleeAnimKinds.json` + `attackHitTables.json`.

## Files touched / referenced

- `research/decomp/ghidra-export/chunk_0006.c:1683,1885,1973,1996` — op 0x08, op 0x10, op 0x11,
  interpreter `zz_004cd24_`.
- `research/decomp/ghidra-export/chunk_0047.c:777-970` — G RED X-special 4-phase state machine
  (`FUN_8018e888`, `_ea54`, `_eb2c`, `_ec34`).
- `research/decomp/ghidra-export/chunk_0031.c:551-617` — Star Hero X dash (the OTHER decoded
  X-special family; same pattern, different params).
- `user-data/GG4E/disc/sys/boot.dol` — all motion constants read via `research/decomp/dol.py`'s
  `addr_to_off` + `struct.unpack`.
- Scratch disassembler: `scratchpad/ppc_disasm.py` (PPC32 decoder for the 8 missing handlers).
