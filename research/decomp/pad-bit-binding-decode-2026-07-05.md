# Pad-Button ↔ Command-Bit Binding — Static Decode

**Date:** 2026-07-05
**Scope:** Finish the B/X contextual-resolver pad-button↔bit binding by disassembling
`zz_0068b8c_` @0x80068b8c and its handlers directly from `boot.dol` (READ-ONLY;
no code files modified). Reconcile against the known GC pad layout and the
prior pass in `research/decomp/data/command-button-map.json`.

**Method:** `research/decomp/dol.py` (`data`, `addr_to_off`, `read_u32`, `read_f32`)
+ a hand-written PPC disassembler (`C:\Users\manny\AppData\Local\Temp\opencode\ppc_disasm.py`).
Every claim below is cross-checked against the Ghidra export and cites both a
`chunk_NNNN.c:line` and a DOL address. Honesty labels follow repo convention:
**DERIVED** = proven by static read of code/data; **INFERRED** = consistent but
not yet lit by a literal in this layer; **BLOCKED** = not reachable from this layer.

---

## 0. Headline result

**The physical GameCube pad-button → `actor+0x5d4` command-bit binding is now
DERIVED (statically proven), not INFERRED.** The per-source input descriptors at
`0x802d38f8..0x802d3964` carry the raw `PAD_BUTTON_*` bitmask as a big-endian
**u16 at descriptor offset 8**, and the handlers test it directly against
`actor+0x5b4` (the GC pad button word, masked `0xff1f7f`) / `actor+0x5bc`
(its press-edge). The port's assumed transform in
`packages/combat/src/command.ts` (`COMMAND_INPUT_BITS`) is **correct** and is
upgraded from "TUNED/un-dug" to confirmed.

Three prior-research claims are **corrected** here:

| # | Prior claim | Correction | Evidence |
|---|---|---|---|
| 1 | `PTR_FUN_802d3988` "has stride != 4 (interleaved with non-ptr values)" | **Stride IS 4.** `rlwinm r0,r0,2,0,29` (= `state<<2`) indexes `PTR_FUN_802d3988[state]`. The "interleaving" is just the **adjacent** target-lock table `PTR_FUN_802d39a0`. | `zz_0068b8c_` disasm §2; dump §1 |
| 2 | Descriptor "mask" field = `0x02000000` etc. | Those are the **u32 at offset 8**; the handler reads the **u16 high half** (offset 8 as `ushort`): `0x0200`=B, `0x0400`=X, … | `FUN_80068c14`/`zz_0068d04_` `lhz r0,8(r4)` §3 |
| 3 | `+0x5d4` bits `0x400`/`0x1000` come from `DAT_802d3940`/`DAT_802d3964` | **Wrong.** `DAT_802d3940`→bit `0x04`, `DAT_802d3964`→bit `0x2000`. Bits `0x400`/`0x800`/`0x1000` are set by the **charge-release booster** `zz_00686f0_` from tables `0x802d3970`/`0x802d397c`. | `chunk_0008.c:4682,4685,4719-4733` §4 |

---

## 1. The two adjacent tables at `0x802d3988` / `0x802d39a0`

Raw DOL dump (`dol.py read_u32`):

```
0x802d3970: 0x00000200   ┐ booster button-mask table (zz_00686f0_ puVar8)
0x802d3974: 0x00000200   │  slot0=B  slot1=B  slot2=X
0x802d3978: 0x00000400   ┘
0x802d397c: 0x00000400   ┐ booster +0x5d4-bit table (zz_00686f0_ puVar6)
0x802d3980: 0x00000800   │  slot0->0x400  slot1->0x800  slot2->0x1000
0x802d3984: 0x00001000   ┘
--- PTR_FUN_802d3988 : input-button state-machine (3 real entries, stride 4) ---
0x802d3988: 0x80068c14   state 0 -> FUN_80068c14  (edge/hold router)
0x802d398c: 0x80068c84   state 1 -> mid-entry of FUN_80068c14 (countdown-decay)
0x802d3990: 0x80068d04   state 2 -> zz_0068d04_   (the real +0x5b4 button test)
0x802d3994: 0x3a043804   << NOT a pointer: start of the next table's data >>
--- PTR_FUN_802d39a0 : target-lock-on state-machine (chunk_0009.c:1603) ---
0x802d39a0: 0x8006b850   state 0 -> target search/acquire
0x802d39a4: 0x8006ba60   state 1 -> live-target re-acquire
0x802d39a8: 0x8006bba4   state 2 -> target-lost clear
```

`PTR_FUN_802d3988` and `PTR_FUN_802d39a0` are **two separate tables**. The 6
addresses in the task brief split 3+3 across them. Only the first 3
(`0x80068c14`, `0x80068c84`, `0x80068d04`) are input-button handlers; the
target-lock 3 (`0x8006b850`, `0x8006ba60`, `0x8006bba4`) do **not** test
`+0x5b4` button bits — they manage the `actor+0x502` lock-on state and read
`actor+0x508`/`+0x504` (the locked target handle). See §5.

---

## 2. `zz_0068b8c_` @0x80068b8c — instruction trace (chunk_0008.c:4874-4886)

PPC disasm (size 0x88 per `GG4E-CSM-20220412.map:802`). Register fields
re-derived from raw opcodes; `r3`=actor, `r4`=descriptor, `r5`=state-byte buf,
`r6`=bit.

```
0x80068b8c  9421ffe0  stwu   r1,-32(r1)            ; prologue
0x80068b90  7c0802a6  mfspr  r0,LR
0x80068b94  3ce0802d  lis    r7,0x802d             ; r7 = 0x802d0000
0x80068b98  90010024  stw    r0,36(r1)
0x80068b9c  38e73988  addi   r7,r7,0x3988          ; r7 = 0x802d3988 (PTR_FUN_802d3988)
0x80068ba0  93e1001c  stw    r31,28(r1)
0x80068ba4  7cdf3378  or     r31,r6,r6             ; r31 = r6 = param_4 (the OR-bit)
0x80068ba8  93c10018  stw    r30,24(r1)
0x80068bac  7cbe2b78  or     r30,r5,r5             ; r30 = r5 = param_3 (state byte ptr)
0x80068bb0  93a10014  stw    r29,20(r1)
0x80068bb4  7c7d1b78  or     r29,r3,r3             ; r29 = r3 = param_1 (actor)
0x80068bb8  88050000  lbz    r0,0(r5)              ; r0 = *param_3   = state byte (param_3[0])
0x80068bbc  5400103a  rlwinm r0,r0,2,0,29          ; r0 = state << 2   *** STRIDE = 4 ***
0x80068bc0  7d87002e  lwzx   r12,r7,r0             ; r12 = PTR_FUN_802d3988[state]  (indexed lwz)
0x80068bc4  7d8903a6  mtctr  r12                   ; CTR = handler address
0x80068bc8  4e800421  bctrl                        ; call handler(actor=r3, desc=r4, state=r5)
;----- handler returns; r3 = param_3[0] state was advanced in-place -----
0x80068bcc  887e0003  lbz    r3,3(r30)             ; r3 = param_3[3]  (countdown/refire byte)
0x80068bd0  7c600775  extsb. r0,r3                 ; test != 0
0x80068bd4  4082000c  beq    ->0x80068be0          ; if ==0 skip the OR (button did not fire)
0x80068bd8  38600000  li     r3,0                  ; return 0
0x80068bdc  4800001c  b      epilogue
0x80068be0  3803ffff  addi   r0,r3,-1              ; countdown--
0x80068be4  38600001  li     r3,1                  ; return 1
0x80068be8  981e0003  stb    r0,3(r30)             ; param_3[3] = countdown-1
0x80068bec  801d05d4  lwz    r0,0x5d4(r29)         ; r0 = actor+0x5d4   (1492 = 0x5d4)
0x80068bf0  7c00fb78  or     r0,r0,r31             ; r0 |= param_4 (the bit, in r31)
0x80068bf4  901d05d4  stw    r0,0x5d4(r29)         ; actor+0x5d4 |= bit
0x80068bf8..0x80068c10  epilogue + blr
```

### Stride / indexing answer

- **Stride is 4.** `rlwinm r0,r0,2,0,29` rotates the state byte left by 2
  (×4) and masks bits 0–29, giving a byte offset `state*4` into the table.
  Then `lwzx r12,r7,r0` loads `PTR_FUN_802d3988[state]` as a word. There is
  **no interleaving** within `PTR_FUN_802d3988`; the apparent non-pointer
  words at `0x802d3994+` belong to the next table `PTR_FUN_802d39a0`.
- **State→handler mapping:** state 0 → `0x80068c14`, state 1 → `0x80068c84`
  (a mid-function countdown-decay entry inside `FUN_80068c14`), state 2 →
  `0x80068d04` (`zz_0068d04_`, the actual button tester).
- **Dispatch form:** `mtctr`/`bctrl` — an **indirect call** (matches Ghidra's
  `(*(code*)...)()`).
- **Which register holds `actor+0x5b4` when each handler is called:** the
  **actor base pointer is in `r3`** (param_1; the handler receives it
  unmodified because `zz_0068b8c_` only reads `r3`, never overwrites it before
  `bctrl`). The handler then loads the button word itself:
  `lwz r?,0x5b4(r3)` (raw pad) or `lwz r?,0x5bc(r3)` (press-edge). The
  descriptor base is `r4`; the state-byte buffer is `r5`; the OR-bit (`param_4`)
  is held in nonvolatile `r31` across the call.

### How a bit reaches `+0x5d4`

The handler does **not** OR the bit itself. It only (a) advances `param_3[0]`
state and (b) seeds `param_3[3]` (the refire countdown) **when the button
matches**. After `bctrl` returns, `zz_0068b8c_` reads `param_3[3]`; if nonzero
it decrements it and ORs `param_4` (the bit, `r31`) into `actor+0x5d4`
(`0x80068bec`–`0x80068bf4`). This is exactly the Ghidra body at
`chunk_0008.c:4879-4884`.

---

## 3. The 10 input-source descriptors @0x802d38f8..0x802d3964 (chunk_0008.c:4676-4685)

Each descriptor is **12 bytes** (6 big-endian u16). The handler reads it as
`short*` (`FUN_80068c14` `param_2[0..5]`) / byte-offset (`zz_0068d04_`):
`[0]`=mode, `[1]`=flags, `[2]`=edge seed, `[3]`=polled seed, `[4]`=button mask
state-0, `[5]`=button mask state-1. **The button mask is the u16 at byte
offset 8** (`lhz r0,8(r4)` in `FUN_80068c14`; `lhz r3,8(r3)` after
`add r3,r4,state*2` in `zz_0068d04_`).

The prior pass dumped the **u32** at offset 8 and saw `0x02000000` etc.; the
handler reads the **u16 high half**, which is the `PAD_BUTTON_*` constant.

| descriptor | → state buf | → +0x5d4 bit | u32@8 (prior dump) | **u16@8 = PAD mask** | button | mode/flags u16@0/@2 | seeds u16@4/@6 |
|---|---|---|---|---|---|---|---|
| `DAT_802d38f8` | actor+0x614 | **0x20** | 0x02000000 | **0x0200** | **B** | 0x0001 / 0x0000 | 0x0000 / 0x0001 |
| `DAT_802d3904` | actor+0x618 | **0x40** | 0x02000000 | **0x0200** | **B** | 0x0001 / 0x0000 | 0x0000 / 0x0001 |
| `DAT_802d3910` | actor+0x61c | **0x80** | 0x04000000 | **0x0400** | **X** | 0x0001 / 0x0000 | 0x0000 / 0x0001 |
| `DAT_802d391c` | actor+0x624 | **0x200** | 0x08000000 | **0x0800** | **Y** | 0x0001 / 0x0000 | 0x0000 / 0x0001 |
| `DAT_802d3928` | actor+0x600 | **0x01** | 0x01000000 | **0x0100** | **A** | 0x0001 / 0x0000 | 0x0000 / 0x0010 |
| `DAT_802d3934` | actor+0x604 | **0x02** | 0x01000000 | **0x0100** | **A** | 0x0001 / 0x0004 | 0x0000 / 0x0001 |
| `DAT_802d3940` | actor+0x608 | **0x04** | 0x00200000 | **0x0020** | **R** | 0x0001 / 0x0000 | 0x0000 / 0x0001 |
| `DAT_802d394c` | actor+0x60c | **0x08** | 0x00400000 | **0x0040** | **L** | 0x0001 / 0x0000 | 0x0000 / 0x0001 |
| `DAT_802d3958` | actor+0x610 | **0x10** | 0x00100000 | **0x0010** | **Z** | 0x0001 / 0x0000 | 0x0000 / 0x0001 |
| `DAT_802d3964` | actor+0x628 | **0x2000** | 0x000f0000 | **0x000f** | **DPAD** | 0x0001 / 0x0010 | 0x0000 / 0x0001 |

**Every u16@8 mask is a literal `PAD_BUTTON_*` bit** under the standard GC
layout (`A=0x100 B=0x200 X=0x400 Y=0x800 Z=0x10 R=0x20 L=0x40 START=0x1000
DPAD=0x0f`). All 10 descriptors have `mode=1`, so they all route through the
`zz_0068d04_` polled path (state 2). The pad-word source is selected by
flag-bit-0 (`rlwinm. r0,r6,0,31,31` at `0x80068d80`): bit0==1 → `lwz r7,0x5b4(r3)`
(raw), bit0==0 → `lwz r7,0x5bc(r3)` (press-edge). **All 10 descriptors have
flag-bit-0 clear**, so they all test the **`+0x5bc` press-edge word** (=
`+0x5b4 & ~+0x5b8`, the rising edge — chunk_0007.c:291 /
`breakpoints-watchpoints.json:1047`). The button *identity* is unchanged
(the edge word is derived from `+0x5b4`); it just makes the command
**edge-triggered** ("pressed this frame") rather than level-triggered.

The other flag bits are gates, not pad-word selectors:
- flag-bit-2 (`0x80068d48`, `rlwinm. r0,r6,0,29,29`): gate on `+0x5e0 & 0x40`.
  Only `DAT_802d3934` (2nd A) sets this → A-alt fires only when `(+0x5e0 & 0x40)==0`.
- flag-bit-3 (`0x80068d64`): gate on `+0x5b4 & 0xf0000` (high direction byte).
  No descriptor sets this.
- flag-bit-4 (`0x80068d98`, `rlwinm. r0,r6,0,27,27`): select the "any-bit-of-mask
  set" test (`-(pad & mask)>>31`) instead of masked-equality. Only `DAT_802d3964`
  (DPAD) sets this, so DPAD fires on any of the 4 directions.

---

## 4. The booster pass `zz_00686f0_` @0x800686f0 (chunk_0008.c:4697-4793)

This is the source of the `+0x5d4` bits `0x400`/`0x800`/`0x1000` that the
command-type testers read but `zz_0068b8c_` never sets. It is the last call in
`zz_00685c0_` (chunk_0008.c:4686). It is a **charge-and-release** mechanic:

```c
puVar8 = (uint*)0x802d3970;   // button masks: B, B, X
puVar6 = (uint*)0x802d397c;   // +0x5d4 bits:  0x400, 0x800, 0x1000
for (slot=0; slot<3; slot++) {
  if (borg_move_table[slot+0xbb] == -1) continue;        // borg has no charge move here
  if (already_fired(+0x58e bit slot+3)) { decay; continue; }
  if ((actor+0x5b4 & puVar8[slot]) == 0) {                // button RELEASED this frame
     if (charge_threshold[slot] <= actor+0x648)           // charge banked long enough
        actor+0x5d4 |= puVar6[slot];                      // *** FIRE booster bit ***
     // decay +0x648
  } else {                                                // button HELD
     // accumulate charge into +0x648; set +0x654 "charging" flag;
     // cap at +0x4ac table; set +0x655 "fully charged" flag
  }
}
```

Booster binding (DOL dump, §1):

| slot | hold button (`+0x5b4`) | release → `+0x5d4` bit | command tester → type |
|---|---|---|---|
| 0 | **B** (0x200) | **0x400** | `zz_0069bf0_` → type 3 (Charged3) — chunk_0009.c:360 |
| 1 | **B** (0x200) | **0x800** | (no direct `+0x585` tester; subtype/downstream) |
| 2 | **X** (0x400) | **0x1000** | `zz_0069c50_`/`zz_0069cb0_` → type 5 (Ranged5) — chunk_0009.c:386 |

The two B slots (0x400, 0x800) share the same trigger button; which fires
depends on the per-borg charge-threshold table at
`*(actor+0x4ac) + slot*4 + 0x184` and the per-borg move-existence byte at
`*(actor+0x4b0) + slot + 0xbb`. A borg with only slot-0 defined fires only
`0x400`; one with slots 0+1 can tier into `0x800` at higher charge.

---

## 5. Handler roles

### `FUN_80068c14` @0x80068c14 (PTR_FUN_802d3988[0]) — edge/hold router
Reads `desc u16@0` (mode). All 10 descriptors have `mode==1`, so this always
sets `param_3[0]=2` (advance to state 2), seeds `param_3[1]=0x7f` (the polled
countdown), and **tail-calls `zz_0068d04_`** (`bl 0x80068d04` at `0x80068c44`).
Its non-mode-1 branch (`0x80068c4c`) tests `actor+0x5bc & desc.u16@8`
(`lwz r3,0x5bc(r3)`; `lhz r0,8(r4)`; `and.`) — the press-edge path — but is
dead for these 10 descriptors.

### `zz_0068d04_` @0x80068d04 (PTR_FUN_802d3988[2]) — the real button tester
Decrements `param_3[1]`; when the polled countdown expires it:
1. reads `desc u16@2` flags and applies `+0x5e0`/`+0x5b4&0xf0000` gates,
2. loads the pad word: `lwz r7,0x5b4(r3)` (raw) or `lwz r7,0x5bc(r3)` (edge),
3. loads the mask: `lhz r3,8(state-indexed r3)` from descriptor,
4. `and r3,r7,r3` and the masked-equality / any-bit test,
5. on match: sets `param_3[0]=0`, seeds `param_3[3]=desc.u16@6` (refire
   countdown) — which `zz_0068b8c_` then consumes to OR the bit into `+0x5d4`.

### `0x80068c84` (PTR_FUN_802d3988[1]) — countdown-decay mid-entry
Not a separate function; it is the post-call entry inside `FUN_80068c14` that
decrements `param_3[1]` while in state 1 (`lbz r6,1(r5)`; `addi r6,r6,-1`;
`stb r6,1(r5)`). Reached when a prior frame left the source in state 1.

### `FUN_8006b850`/`FUN_8006ba60`/`0x8006bba4` (PTR_FUN_802d39a0[0..2]) — target-lock, NOT buttons
These belong to the `actor+0x502` lock-on state machine
(chunk_0009.c:1603 `(&PTR_FUN_802d39a0)[param_1[0x502]]()`). They read
`actor+0x508`/`+0x504` (locked target handle), `actor+0x88` (team), and the
`DAT_803c1d7c` actor list — they do **not** test `actor+0x5b4`. Disasm heads
confirm: `FUN_8006b850` reads `actor+0x73f` and walks `DAT_803c1d7c`;
`FUN_8006ba60` reads `actor+0x508`/`+0x504`; `0x8006bba4` clears
`actor+0x502`/`+0x504`/`+0x508` on target loss. They are **out of scope** for
the pad-button binding (they consume the R/cycle-target intent downstream, not
the raw pad word).

---

## 6. FINAL binding table — pad button → `+0x5b4` bit → `+0x5d4` command bit

| pad button | `+0x5b4` bit (PAD_BUTTON_*) | `+0x5d4` command bit | source fn / descriptor | command consumer | label |
|---|---|---|---|---|---|
| **B** (tap) | 0x200 | **0x20** | `zz_0068b8c_`/`DAT_802d38f8` | `zz_0069a88_` → type 1 (contextual: +0x748/+0x58e) | **DERIVED** |
| **B** (tap, 2nd facet) | 0x200 | **0x40** | `zz_0068b8c_`/`DAT_802d3904` | `zz_0069b10_` → type 1 (gated +0x748/+0x58e/+0x7d2) | **DERIVED** |
| **B** (charge-release) | 0x200 | **0x400** | `zz_00686f0_` slot 0 | `zz_0069bf0_` → type 3 (sets +0x595) | **DERIVED** |
| **B** (charge-release hi) | 0x200 | **0x800** | `zz_00686f0_` slot 1 | (no `+0x585` tester; subtype downstream) | **DERIVED** |
| **X** (tap) | 0x400 | **0x80** | `zz_0068b8c_`/`DAT_802d3910` | `zz_0069b98_` → type 2 | **DERIVED** |
| **X** (charge-release) | 0x400 | **0x1000** | `zz_00686f0_` slot 2 | `zz_0069c50_`/`zz_0069cb0_` → type 5 (sets +0x595) | **DERIVED** |
| **Y** | 0x800 | **0x200** | `zz_0068b8c_`/`DAT_802d391c` | `FUN_80069814` → `+0x6fb=6` (Power Burst arm) | **DERIVED** (was already DERIVED) |
| **A** | 0x100 | **0x01** | `zz_0068b8c_`/`DAT_802d3928` | downstream (movement/jump; not a `+0x585` type) | **DERIVED** |
| **A** (alt, `+0x5e0&0x40==0` gated) | 0x100 | **0x02** | `zz_0068b8c_`/`DAT_802d3934` | `FUN_80069860` → action 0x1c (chunk_0009.c:127) | **DERIVED** |
| **R** | 0x020 | **0x04** | `zz_0068b8c_`/`DAT_802d3940` | downstream (target-cycle/lock; `PTR_FUN_802d39a0` chain) | **DERIVED** (intent), **INFERRED** (consumer) |
| **L** | 0x040 | **0x08** | `zz_0068b8c_`/`DAT_802d394c` | downstream (guard/dash subsystem) | **DERIVED** (intent), **INFERRED** (consumer) |
| **Z** | 0x010 | **0x10** | `zz_0068b8c_`/`DAT_802d3958` | downstream (transform/special subsystem) | **DERIVED** (intent), **INFERRED** (consumer) |
| **DPAD** (any of U/D/L/R) | 0x000f | **0x2000** | `zz_0068b8c_`/`DAT_802d3964` | downstream (dash/direction; also feeds `+0x5d8` via `zz_0068980_`) | **DERIVED** |
| **START** | 0x1000 | — (none) | not bound | pause/menu handled at pad layer; no descriptor tests 0x1000 | **INFERRED** |

**Cross-check vs the Y/burst path (already DERIVED):** `FUN_80069814`
chunk_0009.c:110 tests `+0x5d4 & 0x200` and arms `+0x6fb=6`. The descriptor
`DAT_802d391c` (→ bit 0x200) tests `+0x5b4 & 0x0800` = **Y**. ✓ Confirmed.

**Cross-check vs the known GC pad bits:** every descriptor u16@8 mask
(`0x100/0x200/0x400/0x800/0x10/0x20/0x40/0x0f`) matches the standard
`PAD_BUTTON_*` layout exactly. `actor+0x5b4` low word **is** the GC pad button
word (masked `0xff1f7f` upstream at the slot-input layer,
`breakpoints-watchpoints.json:1168`); bits 16–23 are a separate remapped
direction/stick encoding (chunk_0008.c:3438 `>>0x10 & 0xf`).

---

## 7. Port-file change needed (`packages/combat/src/`)

The port's existing model is **correct**; the change is (a) provenance upgrade
and (b) one fidelity fix. No behavioral schema changes are required for the
attack-command path.

### 7a. `command.ts` — `COMMAND_INPUT_BITS` (line 146-159)

The six constants are all correct and now **DERIVED** (were "TUNED/un-dug"):
`MELEE_A=0x20`, `MELEE_B=0x40`, `SECONDARY=0x80`, `CHARGED=0x400`,
`RANGED=0x1000`, `BURST=0x200`. **No value changes.** Update the doc-comment
block (lines 142-145) and the per-line comments to cite the new evidence:
- `MELEE_A`/`MELEE_B`: "`DAT_802d38f8`/`DAT_802d3904` both test `+0x5b4 & 0x0200`
  (**B**); proven via `lhz r0,8(r4)` in `FUN_80068c14`/`zz_0068d04_` @0x80068d04."
- `CHARGED`: "`zz_00686f0_` slot 0, charge-release of **B** (mask table
  `0x802d3970`)."
- `RANGED`: "`zz_00686f0_` slot 2, charge-release of **X**."
- `SECONDARY`/`BURST`: "`DAT_802d3910` (X, 0x0400)" / "`DAT_802d391c` (Y, 0x0800)."

Optionally add a `NON_ATTACK_INPUT_BITS` export documenting the now-decoded but
non-attack bits for downstream porting:
```ts
// DERIVED zz_0068b8c_ descriptors; consumed by movement/lock/dash, not +0x585.
export const NON_ATTACK_INPUT_BITS = {
  A_TAP:   0x01,  // DAT_802d3928, +0x5b4 & 0x0100 (A)
  A_ALT:   0x02,  // DAT_802d3934, A, gated +0x5e0&0x40==0 -> FUN_80069860 action 0x1c
  R:       0x04,  // DAT_802d3940, +0x5b4 & 0x0020 (R) -> target cycle
  L:       0x08,  // DAT_802d394c, +0x5b4 & 0x0040 (L) -> guard/dash
  Z:       0x10,  // DAT_802d3958, +0x5b4 & 0x0010 (Z) -> transform/special
  DPAD:    0x2000,// DAT_802d3964, +0x5b4 & 0x000f (any DPAD) -> dash/direction
  B_CHARGE_HI: 0x800, // zz_00686f0_ slot 1, B high-charge tier
} as const;
```

### 7b. `commandDispatch.ts` — `commandInputWord` (line 63-71)

One fidelity fix: a **B tap sets both `0x20` and `0x40`** in the ROM (two
descriptors both watch B). The port currently sets only `MELEE_A`. Mirror the
ROM:
```ts
export function commandInputWord(state: CommandButtonState): number {
  let word = 0;
  if (state.attackHeld) {
    word |= COMMAND_INPUT_BITS.MELEE_A;   // DAT_802d38f8 -> 0x20
    word |= COMMAND_INPUT_BITS.MELEE_B;   // DAT_802d3904 -> 0x40 (same B press)
  }
  if (state.specialHeld)        word |= COMMAND_INPUT_BITS.SECONDARY;     // X  -> 0x80
  if (state.chargeRelease)      word |= COMMAND_INPUT_BITS.CHARGED;       // B  -> 0x400
  if (state.xChargeRelease)     word |= COMMAND_INPUT_BITS.RANGED;        // X  -> 0x1000
  if (state.burstHeld)          word |= COMMAND_INPUT_BITS.BURST;         // Y  -> 0x200
  return word;
}
```
This does not change `resolveCommandType` output (both bits still resolve to
`Melee1`), but it makes the word faithful for any future downstream consumer
that distinguishes the two B facets (the ROM's `zz_0069a88_` vs `zz_0069b10_`
proximity/dash gating reads them separately).

Update the file-header comment (lines 14-17): the pad→bit transform is **no
longer "the one TUNED link… still un-dug"** — it is now DERIVED from the
descriptor u16@8 masks + `zz_00686f0_` booster tables. Replace with a one-line
citation of this note.

### 7c. `commandSchema.selftest.ts`

`ATK-003` cases at lines 335-338 remain valid; add one assertion that
`commandInputWord({attackHeld:true,...})` now sets **both** `MELEE_A|MELEE_B`
(`0x60`), to lock the fidelity fix.

### 7d. `command-button-map.json` (data file)

Correct three entries in `inputWordBuild.bitAssignments`:
- `{"bit":"0x400","descriptor":"DAT_802d3940"}` → `{"bit":"0x04",...}` (R)
- `{"bit":"0x1000","descriptor":"DAT_802d3964"}` → `{"bit":"0x2000",...}` (DPAD)
- add the booster entries: `0x400`/`0x800`/`0x1000` ← `zz_00686f0_` tables
  `0x802d3970`/`0x802d397c` (B/B/X charge-release).

And in `summary`/`portNote`: the "PHYSICAL-BUTTON labels = still inferred" caveat
is **resolved** — button labels are now DERIVED from the descriptor masks.

---

## 8. What is still BLOCKED / not proven here

- **START (0x1000 in `+0x5b4`):** preserved by the `0xff1f7f` mask but no
  descriptor or booster tests it; it never reaches `+0x5d4`. Pause/menu handling
  lives at the pad layer above `+0x5b4`. **INFERRED** as the pause button.
- **Exact consumer of `+0x5d4` bits `0x04`/`0x08`/`0x10` (R/L/Z) and `0x01`/
  `0x02` (A):** the bits are DERIVED-set; their downstream non-attack consumers
  (target-cycle, guard/dash, transform, jump) are INFERRED from role and need a
  separate trace through the movement/lock-on subsystems (not the attack
  decision chain).
- **Analog trigger depth / stick magnitude:** the `+0x5b4` high byte (bits
  16–23, the `0xff0000` part of the mask) and the `+0x5d8` direction word built
  by `zz_0068980_` (chunk_0008.c:4797-4868) are out of scope for the button
  binding.
