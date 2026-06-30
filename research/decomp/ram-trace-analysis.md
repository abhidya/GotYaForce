# Gotcha Force (GG4E / NTSC-U) — Live RAM Trace Analysis

Goal: turn two Dolphin battle save states into MEM1 images, diff them, and locate the live
"active borg" struct (position / rotation / HP / animation state) for behavior porting.

Inputs:
- `user-data/GG4E/traces/battle1_challenge.sav` (t1, 29,592,894 bytes)
- `user-data/GG4E/traces/battle1_challenge_t2.sav` (t2, 34,270,638 bytes)
- Both from a LIVE Challenge battle, **G RED active**. Between t1→t2 the player held FORWARD
  (G Red moved) and HP dropped (~188 → ~131).
- Symbol map: `research/symbols/GG4E-CSM-20220412.map`; borg HP table: `research/symbols/NTSC_Borgs.csv`
  (**G RED = pl0615, HP 200 @ Lv1 / 290 @ Lv10**).
- Validation anchor: float 60.0 at RAM `0x80437448` (bytes `42 70 00 00`).
- Cross-reference: `research/decomp/behavior-notes.md` (static boot.dol decompilation, same task).

Tooling: Python 3.7 + `lz4`, `numpy`. Scripts left in the session scratchpad.

---

## 1. MEM1 extraction — SUCCESS (method fully reverse-engineered)

The `.sav` is a **modern Dolphin save state** (version string `"Dolphin 2506a"`, STATE_VERSION 174).
It is **not** wrapped in any standard compression frame (no zstd/lz4-frame/zlib/xz magic anywhere).
The format was reconstructed from Dolphin's `State.cpp` / `State.h`:

| field | type | offset | t1 value |
|-------|------|--------|----------|
| `StateHeaderLegacy.game_id` | char[6] | 0x00 | `"GG4E08"` |
| `StateHeaderLegacy.lzo_size` | u32 LE | 0x08 | 0 (legacy/unused) |
| `StateHeaderLegacy.time` | double | 0x10 | — |
| `StateHeaderVersion.version_cookie` | u32 LE | 0x18 | `0xBAADBB6C` (= COOKIE_BASE `0xBAADBABE` + 174) |
| `StateHeaderVersion.version_string_length` | u32 LE | 0x1C | 13 |
| version string | char[13] | 0x20 | `"Dolphin 2506a"` |
| `StateExtendedBaseHeader.header_version` | u16 LE | 0x2D | 1 |
| `StateExtendedBaseHeader.compression_type` | u16 LE | 0x2F | **1 = LZ4** |
| `StateExtendedBaseHeader.payload_offset` | u32 LE | 0x31 | 0 |
| `StateExtendedBaseHeader.uncompressed_size` | u64 LE | 0x35 | **187,026,760** |

Payload starts at **0x3D** as a chunked LZ4 stream: repeated `[i32 LE compressed_len][raw LZ4 block]`.
Decompressing yields the full 187,026,760-byte emulator state (single chunk in both saves).

**Locating MEM1 inside the full state (robust method):** scan the decompressed buffer for the
GameCube boot signature — disc magic `0xC2339F3D` at RAM 0x8000001C, with `"GG4E"` at 0x80000000.
This appears exactly once. **MEM1 base = file offset 0x620637E** in both t1 and t2.

**Anchor validation — PASS:** at `mem1[0x437448:0x43744C]` both images read `42 70 00 00` (= 60.0f).
Disc header `"GG4E"` + maker `"08"` at MEM1[0] confirms it.

Outputs written (24 MB = 0x1800000 each):
- `user-data/GG4E/traces/mem1_t1.bin`
- `user-data/GG4E/traces/mem1_t2.bin`

Both map RAM 0x80000000 → file offset 0 of the .bin (so RAM addr = 0x80000000 + file offset).

---

## 2. Diff t1 vs t2

513,014 of 6,291,456 32-bit words changed across MEM1 (≈8%). Most churn is audio buffers,
particle systems, RNG, scene-graph/render scratch, and per-frame matrix pools — not gameplay
state. Filtering for gameplay signatures (world-scale floats that moved a forward delta; HP-like
ints that dropped ~50; the static-analysis-confirmed struct offsets) narrowed it as below.

---

## 3. Active-borg findings

### 3.1 World position — CONFIRMED (the strongest result)

The active player borg (G RED) moved forward exactly as the human reported. Its world transform
is unambiguous in the per-frame render/scene buffer:

| quantity | t1 | t2 | delta |
|----------|----|----|-------|
| **position X** | **2964.62** | **3000.11** | +35.5 |
| **position Y** | **10.00** | **10.00** | 0 (on ground plane) |
| **position Z** | **-962.60** | **-680.38** | **+282.2 (forward)** |

- Confirmed at RAM `0x80614DD8` (X), `0x80614DDC` (Y=10.0), `0x80614DE0` (Z), with a duplicate copy
  8 bytes later and a third in a sibling scene node at `0x80614ED8`. Bit-exact float values:
  t1 X=`0x453949EF`, Z=`0xC470A62F`; t2 X=`0x453B81B5`, Z=`0xC42A1829`. Y constant `0x41200000`.
- This region (`0x80614000–0x80616000`) is a **double-buffered per-frame scene-graph / matrix pool**
  (whole blocks flip between zero and full each frame), so these are the borg's *rendered* world
  coordinates at the snapshot instant — the authoritative position value, copied here from the
  gameplay object each frame.
- Scale = **1.5** (`0x3FC00000`, seen at `0x80614D70`).
- **Movement magnitude ≈284 units** in ~the snapshot interval, dominated by +Z — matches "held
  FORWARD". Net heading ≈ atan2(+35.5, +282) ≈ +7° off the +Z axis.

A second on-field actor (the **camera**) sits at `0x806A5300`: a clean persistent object with a
position-**history ring buffer** (`X 3430.5→3435.2, Y=70.0 const, Z -937.7→-936.6`, sliding down the
buffer each frame) and an embedded 3×3 look-at matrix (`0x806A53A4–0x806A53D0`, rows
`(0.993,0,0.122) / (0,1,0)-ish / (-0.122,0,0.993)` → a small yaw). It tracks toward the player
(camera ~3430/-937 → player ~3000/-680, directionally consistent). **This is the camera, not a borg**
(no HP/state fields; uses a position-history layout, not the 0x44-position borg layout below).

### 3.2 Cross-reference to the static decompilation (borg struct offsets)

`behavior-notes.md` + `borg-struct-offsets.txt` independently derived the **gameplay borg struct
layout** from boot.dol (anchored on the validated 0x720 invincibility field). Code-confirmed
offsets relevant here:

| struct offset | meaning (from code) | type |
|---------------|---------------------|------|
| 0x44 / 0x48 / 0x4c | **position x / y / z** | float (written via PSMTX/PSVEC math) |
| 0x58 / 0x5c / 0x60 | velocity-ish vector | float |
| 0x72, 0x5aa/0x5ac/0x5ae | **heading / facing** | s16 |
| 0x544 | **state-machine state** (death mediated here) | s32 |
| 0x5e0 | status bit flags | s32 |
| **0x720** | **invincibility timer** (counts down ~1.0/frame, cap 60) | float |
| 0x1dcc | per-frame decrement step (≈1.0) | float |

This is the data-side confirmation of the code-side claim: position **is** a contiguous float vec3
(matching the vec3 we see moving in RAM), and the invincibility "60.0" constant at 0x80437448 (which
we anchor-validated) is loaded into struct+0x720.

### 3.3 HP, rotation matrix, animation frame — NOT uniquely pinned from 2 frames (honest gap)

- **HP (int/float):** searching all of MEM1 for the reported ~188→131 drop:
  - Only **one** int16 in the whole game heap drops 184→139 (`0x804F00D4`), but it sits inside a
    fully-churned high-entropy stream buffer (audio/anim) — **coincidental, rejected**.
  - No int32 anywhere reads exactly 188→131; the nearest heap int32 drop is `0x805DC474` 300→248.
  - No HP-percentage float (ratio decreasing 0.1–0.35) clusters cleanly with the player position.
  - Conclusion: the gameplay HP field is **not** a clean aligned int adjacent to the rendered
    position. It lives in the gameplay borg struct (a different allocation from the render buffer),
    consistent with the static analysis also failing to isolate HP/damage from code (§4f there).
    G RED's max HP is 200–290 (CSV), so current HP ~188→131 is a mid-battle value, not a table constant.
- **Rotation:** the rendered transform carries an orthonormal 3×3 (scale 1.5 baked in); the gameplay
  facing is the s16 heading at struct+0x72 / 0x5aa per the code. Exact heading bits not isolated
  because the gameplay struct base is unconfirmed (below).
- **Animation id/frame:** driven by the HSD AObj/FObj/JObj pipeline (static §4d), selected per-state
  via helper `0x80066EC0`. No standalone scalar frame counter was isolable next to the render position.

### 3.4 Why the gameplay struct base couldn't be uniquely fixed

A blind 2-frame diff cannot uniquely resolve the borg-array base: brute-scanning for the
code-confirmed signature (world-scale float at +0x44, a 0–60 float at +0x720, a small int at +0x544)
returns >1,000 false positives because skinned **mesh vertex arrays** in 0x8068–0x806A and the
**matrix scratch pool** in 0x80614–0x80616 collide with that pattern. Disambiguating requires the
runtime **borg-list global pointer** (the address the state-machine functions at 0x8005CC00 load
r3 from) — that comes from tracing the load in code or from a live DME watch, not from two frames.

---

## 4. Recommended follow-up to lock HP / anim / struct base (for the human)

The MEM1 images are now valid 24 MB dumps; use them with **Dolphin Memory Engine** (or a 3rd save):

1. Load the save in Dolphin, open Memory Engine.
2. Watch the confirmed position floats live: search Float `2964.6` (or current X) — single-result
   lock gives the **render position address**; the gameplay struct's 0x44 will track it 1:1.
3. With the battle paused vs. taking a hit, **Next Scan** on Float for the HP-bar ratio and on
   Int16/Int32 for HP — the 188→131 drop will isolate the real HP field; its address minus the
   gameplay position (at field 0x44) gives the **struct base**, then read 0x544/0x720/0x72 to confirm.
4. Once the base is known, capture a 3rd frame and re-diff against these two to confirm 0x720 counts.

This is the same gap flagged from the code side (`behavior-notes.md` §4f, §6): **do not port guessed
HP/damage offsets** — lock them with a live watch first.

---

## 5. Summary of confidence

| item | status |
|------|--------|
| MEM1 extraction + LZ4 chunk format + base 0x620637E | **Confirmed** (anchor `42 70 00 00` @ 0x437448 passes) |
| Active-borg world position 2964.62/10.0/-962.60 → 3000.11/10.0/-680.38 | **Confirmed** (RAM 0x80614DD8) |
| Forward movement (+282 Z, +35 X) matches "held FORWARD" | **Confirmed** |
| Render scale 1.5; camera at 0x806A5300 tracking player | **Likely** |
| Position is float vec3 at struct+0x44/48/4c; invinc float at +0x720 | **Confirmed** (cross-ref boot.dol) |
| Gameplay struct base; HP/anim-frame exact offsets | **Unconfirmed** — needs live DME watch (§4) |

Artifacts: `user-data/GG4E/traces/mem1_t1.bin`, `mem1_t2.bin` (24 MB each, RAM=0x80000000+offset).
