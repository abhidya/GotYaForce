# CPU AI decision brain — statically isolated (2026-07-06)

Supersedes `research/decomp/index/cpu-ai-evidence.md`'s "decision-brain not isolated /
Dolphin write-watch needed" conclusion: **the brain was found statically**. Every claim
below survived an independent adversarial re-verification pass (22/23 CONFIRMED; the one
REFUTED claim was an "unresolved" label the verifier managed to RESOLVE — see §6). Full
claim/evidence JSON: session workflow `wf_9213949b-b42` (dig `p3-cpu-ai`).

## 1. Input architecture: the per-actor virtual pad

Every actor carries an embedded virtual pad: `+0x5b4` u32 current buttons, `+0x5b8` prev,
`+0x5bc` pressed-edge, `+0x5c0` released-edge, `+0x5c9` connected, `+0x5ca/+0x5cb` s8
stick X/Y (chunk_0007.c:259-292; readers e.g. chunk_0009.c:155/173, chunk_0008.c:4904).

`FUN_80056900` @0x80056900 (chunk_0007.c:230-304) refreshes it once per frame per actor.
Source select via mode byte `+0x488`: 0 = copy from the cooked hardware pad mirror
`DAT_803c727c` (4 pads × 0x20; masked by `zz_008bbc0_` = `& 0xff1f7f`), 2 = zero the pad,
1 = skip hardware read; mode 3 = one-shot edge-swallow (control handoff). Then **if
`actor+0x3e6 != 0` and mode != 2 it calls the CPU AI root `zz_001c9d0_`** — the AI writes
the actor's virtual pad directly, bypassing ALL pad-source plumbing (which also finally
disambiguates it from the ruled-out `set_slot_action_handler` replay buffers).

CPU flag binding (confirms the cpu-ai-evidence.md lead): `FUN_800541ac` actor init,
chunk_0006.c:7087-7100 — pad-present mask bit clear (`PTR_DAT_80433930[2] & slotBit`) →
`+0x3e6=1, +0x488=1` (CPU); else human. Hardware mirror writer: `zz_010d450_` @0x8010d450
(chunk_0030.c:2406-2597) — raw PADStatus @DAT_803c72fc → buttons + stick-direction nibble
(bits 16-19 via `FUN_8008b73c(x,y,deadzone=0x1e)`), c-stick nibble (bits 20-23), analog
L/R edges (0x40/0x20).

## 2. The AI module (chunk_0002.c + chunk_0003.c:1-2300)

**Root: `zz_001c9d0_` @0x8001c9d0** (chunk_0002.c:3790-4013), per CPU actor per frame:
1. zero virtual pad + stick; `+0x33c` AI frame counter++
2. target maintenance `zz_00252bc_` (countdown `+0x32a`, forced re-pick on target death)
3. partner/fusion logic `zz_0026050_` + `zz_00262b4_` (NOTE: real Ghidra address of the
   latter is **0x80026250**, `_index.tsv`:490 — the name suffix lies)
4. behavior state machine: dispatch on class byte `+0x661` (= borg record byte 1,
   chunk_0009.c:979 — melee vs ranged handler variants) and AI state byte `+0x2e4`:
   states 0..6, 0xa (follow/no-enemy), 0xb — handlers `zz_001d058_`, `zz_001d5a0_`,
   `zz_001f69c_`, `zz_001fb28_`, `zz_00201f8_`, `zz_00203f4_`, `FUN_800209a4`,
   `zz_0020c0c_` (+ melee-class variants). Transition setters `zz_0020fd4_`(→0) …
   `zz_0021148_`(→6) at chunk_0002.c:6492-6595; may-attack predicate `zz_002115c_`.
5. pending-attack executor `zz_00234e4_` + per-borg quirk overlay `FUN_8002645c`
6. case 0xa inline: press 0x400 when linear distance ≤ FLOAT_80436e10 = **1000.0**

**Target selector `zz_002532c_`** @0x8002532c (chunk_0003.c:1362-1562): retarget timer
from `DAT_802cfaf4[rand&7]` = **{4,8,10,12,15,30,45,60} frames**; protect-ally mask
+0x58b, modes +0x30a (0 enemy / 1,2 ally), scenario byte +0x352 (7 targets CPUs, 6 targets
humans, 4 category-filtered); fallback `FUN_80025944` = nearest eligible over the 6-slot
actor table DAT_803c4e84 (stride 0x1e00) within FLOAT_80436e88 = 4e8 (**20000² squared
units**); writes `+0x300`, mirrors `+0x304`.

**Attack choosers `zz_0021f7c_` / `FUN_80022b80`** (chunk_0002.c:7078-7331 / 7499-):
32-slice weighted roulette (`rand&0x1f`) over six per-borg weights at borg record
(+0x4b0) **+0xf0..+0x104 floats, params +0x10e..+0x113**; store button CODE (0x200 or
0x400) in +0x33e/+0x340 + category +0x353 + param +0x30b, queue via `zz_002347c_`
(latches only when +0x30b ∈ {2,3}; else caller falls through to direct-press).

**Attack executor `zz_00234e4_`** @0x800234e4 (chunk_0003.c:136-263): while latch +0x373,
press queued code +0x370 into +0x5b4 through a 3-phase charge machine (+0x374), gated by
weapon-ready mask `+0x655 & (1<<category)`, stored range +0x378, line-of-sight
`zz_003e978_`, and a hardcoded borg-id exception list.

**Steering motor `zz_0024d1c_`** @0x80024d1c: writes stick +0x5ca/+0x5cb (mode 1 scales by
FLOAT_80436ea4 = **0.8**) and ORs the direction nibble `FUN_8008b73c(x,y,0x1e)<<16` into
+0x5b4 — the exact encoding the hardware ingest produces. `FUN_80024dec`: desired stick =
sin/cos(bearing-to-target − reference yaw +0x5b0) × FLOAT_80436e60 = **54.0**.
`FUN_80024f64`: terrain probe ahead in FLOAT_80436e20 = **500**-unit steps → press 0x100
(jump/boost) when ground ahead is higher. `FUN_80025a84`: lock-cycle presser — nearest
candidate from the 4-entry table at `*(PTR_DAT_80433934+0xbc)+0x144` (+4 entries when
Y ≥ FLOAT_80436e84 = **4800** = airborne set), compares +0x508, presses 0x20/0x10 with a
30-frame debounce. Partner/fusion: `zz_0026050_` scans per-side roster DAT_803c6dec,
sets mutual link +0x360/+0x364, then holds 0x800.

**Per-borg quirks `FUN_8002645c`** (chunk_0003.c:2077-): switch on borg id (0x106, 0x201,
0x205, 0x302, 0x404, 0x501, 0x505, 0x620, …) injecting 0x200/0x400 presses on RNG timers;
`FUN_800251d0` additionally auto-holds 0x400 while ammo timer +0x784 > 0, invoked only for
borg ids 0x603/0x60b/0x60d/0x60f under class 7. Boss coupling: any opposing borg 0xe04
forces scenario 0xa (chunk_0002.c:3818-3822) and 0xe04 itself skips the AI entirely.

## 3. Difficulty + cadence (port-ready DERIVED tables)

Init `zz_001c80c_` @0x8001c80c (from FUN_800541ac chunk_0006.c:7120 + respawn
chunk_0009.c:985): zeroes AI scratch; mission-script block (PTR_DAT_80433934[0x15dd])
seeds +0x339/+0x352/… per slot; otherwise cleared — and **AI level +0x439 < 1 sets flag
0x10 in +0x339, which blocks attack initiation entirely** (weakest CPUs never start
attacks via the roulette path).

Difficulty bytes `+0x438/+0x439/+0x43a` copied by `zz_0056180_` from match state
(PTR_DAT_80433934[slot+0x20/+0x32/+0x3e]). They index:
- idle-duration: `(&PTR_u_VTRPNLJ_802cb2f0)[+0x438]` row `[+0x439*8 + rand&7]` → +0x328.
  Pointers @0x802cb2f0 = {802ca4f0, 802ca4f0, 802ca5f0, 802ca6f0, 802ca7f0, 802ca8f0};
  e.g. @0x802ca4f0: lvl0 {86,84,82,80,78,76,74,0} … lvl3 {46..34,0} (higher level =
  shorter waits)
- second cadence `(&PTR_DAT_802cc138)[+0x438]` → +0x320; all six pointers → identical row
  data (@0x802cb338: lvl0 {602..616}, lvl1 {180..187}, lvl2 {170..177}, lvl3 {160..167})
- retarget: DAT_802cfaf4 = {4,8,10,12,15,30,45,60}

Range/steering constants (all read from the DOL): wake radius² 250000 (=500²,
FLOAT_80436df8), press-0x400 range 1000 (FLOAT_80436e10), probe step / default range 500
(FLOAT_80436e20), per-borg ranges 800/1200/600 (FLOAT_80436e28/_ea8/_eb8), stick magnitude
54 × scale 0.8 (FLOAT_80436e60/_ea4), airborne threshold 4800 (FLOAT_80436e84), search
radius² 4e8 (FLOAT_80436e88), ally-proximity block 250 (FLOAT_80436e9c).

Weapon pipeline join: `zz_00686f0_` (chunk_0008.c:4697-4793) checks HELD masks
0x802d3970 = {0x200,0x200,0x400} against +0x5b4 and sets autofire bits
0x802d397c = {0x400,0x800,0x1000} into +0x5d4 — the AI's synthesized presses drive
exactly the human weapon pipeline.

## 4. Call graph (battle loop → AI)

`zz_00527d8_` main loop (chunk_0006.c:5790) → pad ingest `zz_010d450_` each iteration;
battle frame `zz_0029434_` → `zz_0053a2c_` → per-actor `FUN_80054070` → phase table
`PTR_FUN_802d3264` @0x802d3264 = {800541ac, 8005475c, 80054d54, 8005514c, 800547dc,
80054c78, 80054cbc, 80054cf0}; phases 6/7 (`FUN_80054cbc`/`FUN_80054cf0`) call
`FUN_80056900` (input refresh → AI) then `FUN_80055568` (state-machine step consuming the
virtual pad).

## 5. Dolphin confirmation plan (for the future trace session — Priority 8)

1. BP 0x8001c9d0: once per frame per CPU slot only (r3=actor; check +0x3e4/+0x3e6==1)
2. BP 0x8002532c: log +0x300 after return; spacing should match {4,8,10,12,15,30,45,60}
3. BP 0x80024d1c: f1/f2 = desired stick; correlate vs camera yaw *(s16*)(actor+0x5b0)
4. write-watch actor+0x5b4 (actor = DAT_803c4e84 + slot*0x1e00): CPU-slot writers should
   all resolve inside 0x8001c9d0..0x80026600 or FUN_80056900's zeroing path
5. watch +0x2e4 state transitions and +0x374 charge phases while +0x370 nonzero
6. watch +0x438/+0x439 across Challenge difficulties (should shorten +0x328 idle waits)
   (correct the zz_00262b4_ BP to its real address 0x80026250)

## 6. Verifier resolutions + remaining opens

- **+0x5b0 reference yaw = camera yaw + 180°** (REFUTED-the-unresolved-label: writers at
  chunk_0001.c:797 & 3089, `= *(short*)(cam+0x72) − 0x8000` from the orbit-camera object;
  corroborated by +0x5ae = +0x5b0 − 0x8000 in chunk_0007.c:6904). The CPU's virtual stick
  is CAMERA-RELATIVE — same frame as human input.
- **DAT_80433928 direction-mask table IS statically dumpable**: bytes @0x80433928 =
  {02,0a,08,09,01,05,04,06} (8-direction nibble combos over bits 1/2/4/8); the
  0x80433920..30 block also carries DOL-initial values of PTR_DAT_80433930 → 0x803c6ce0
  and PTR_DAT_80433934 → 0x803c5420 — these "runtime" pointer blocks are statically
  seeded, which may make more tables dumpable than previously assumed.
- Open: button-bit → in-game action naming (cross-check behavior-notes (ao) before naming
  in code); the six per-borg attack-weight columns' location in the decoded stat-row
  layout; full +0x352 scenario value table; individual state-handler decode
  (approach/strafe/retreat specifics).

## 7. Port implications

The port can replace its heuristic CPU AI (approach/kite constants "tuned for the old
22-speed world") with a faithful state machine: per-frame virtual-pad synthesis (zero pad
→ retarget-on-cadence → steer camera-relative stick (54×0.8) → terrain-probe jump →
weighted-roulette attack selection with range+LOS gating through the 3-phase charge
machine → difficulty-indexed idle cadence; level-0 attack block). Emit synthetic
PlayerInput into the same per-actor input slot the human path uses — do NOT model the AI
as reading the pad mirror. TUNED→DERIVED upgrades available now: retarget frames table,
1000-unit press range, per-borg 500/600/800/1200 ranges, 20000-unit search radius,
500-unit wake radius, stick 54×0.8, idle cadence tables, airborne 4800 threshold.
