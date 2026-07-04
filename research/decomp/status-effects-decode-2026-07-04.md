# Status-effect + tier-buff decode (2026-07-04)

Decode agent report (boot.dol pointer-table dumps + ghidra export). Everything below is
quoted from the corpus; scratch scripts: `scratchpad/dump-cue-state.mjs`, `dump-gred-tables.mjs`.

## A) Tier-buff attribution — the +4/1200f "acceleration" self-buff is STAR HERO / PLANET HERO's X special

The candidate **pl0004 ACCELERATION NINJA is REFUTED**: its ctor is 0x80162128, ptrLabel
0x8034c718, commandStruct 0x8034c8a0 — a different module. The module owning zz_011230c_ is
the **hero family module** (ctor 0x8010f5ac), shared by **pl0804 STAR HERO** and **pl080c
PLANET HERO** (both bind ctor 0x8010f5ac, ptrLabel 0x80326ae8, root 0x80327058).

Chain, each link verified:

1. **Ctor binding**: family ctors copy a 16-word descriptor into actor+0x4b4..+0x4f0
   (pattern proven by G RED ctor zz_018ccfc_, chunk_0046.c:4790-4805). Hero descriptor at
   **0x80326ab0** → **actor+0x4b4 = FUN_8010f86c**, **actor+0x4c8 = FUN_8010f790**.
2. **Action dispatch**: FUN_8010f86c (chunk_0030.c:4035) → `PTR_FUN_80326af0[actor+0x580]`;
   entry **2 = FUN_801121c0**.
3. **Variant dispatch**: FUN_801121c0 (chunk_0031.c:522) → `PTR_FUN_80326c04[actor+0x581]`:
   **all 5 entries = FUN_801121fc**.
4. **Phase dispatch**: FUN_801121fc → `PTR_FUN_80434530[actor+0x540]`: [0] = FUN_80112278
   (startup: spawns the kind-0xf dash hit via `zz_004beb8_(…,0xf,4,…)`, chunk_0031.c:551-569),
   [1] = zz_011230c_ (per-frame dash update).
5. **Command trigger**: pl0804's command table (ctor_8010f5ac_root_80327058_cmd_80326cf0)
   maps actionIndex 2 exclusively to **command type 2 = X button** for all 6 subtypes.

### Buff semantics (zz_011230c_, chunk_0031.c:576-617)

The X special is a ramming dash (velocity scaled by FLOAT_80439678, kind-0xf hitbox live).
When contact flag **actor+0x1cef goes positive** (dash connected, via `zz_004cd24_(actor,0xf)`):
if not already buffed (`+0x144 <= 0`), set **+0x144 = 0x4b0 (1200 frames)**,
`apply_actor_param_tier_delta_127(actor, +4)` (tier 16→20 = velocity ×2.366), play cue 0xa5,
+0x146 = 30, despawn kind-0xf hitboxes. Contact while already buffed just ends the dash.
Wall contact (+0x1cee) ends the dash without buff.

**Revert**: FUN_8010f790 (chunk_0030.c:4004-4026) decrements +0x144; at 0 →
`apply_actor_param_tier_delta_127(actor, -4)`. Runs every frame via descriptor slot
actor+0x4c8, invoked by the shared per-actor status pass zz_0059068_ (chunk_0007.c:2099).

### Complete tier-delta call-site table (exhaustive)

| Caller | chunk:line | Delta | Duration | Attribution |
|---|---|---|---|---|
| zz_011230c_ @0x8011230c | chunk_0031.c:590 | +4 | 1200f (timer +0x144) | **STAR HERO / PLANET HERO X special** (DERIVED, every link table-dumped) |
| FUN_8010f790 @0x8010f790 | chunk_0030.c:4018 | −4 | revert of the above | same module |
| zz_005bab8_ @0x8005bab8 | chunk_0007.c:3684 | −(actor+0x74e) | timer +0x750 expiry | engine-generic auto-revert of hit-applied deltas |
| battle_frame_target_action_dispatch @0x8002bb14 | chunk_0003.c:6248 (via `_63`) | ±rec byte+0x05 per contact frame | 900f (+0x750 set by `_63`, chunk_0008.c:4475) | **hit-inflicted grow/shrink** from damage-record flagsA bits 4/8; census: PATRA WITCH (#5,+1)/ISIS WITCH (#6,+2) grow; BASTET WITCH (#5,−1)/SEKHMET WITCH (#6,−2) shrink |
| reset_actor_param_tier @0x80068138 | chunk_0008.c:4396-4404 | reset to 0x10 | — | engine init/reset |

No other callers exist (honest negative). `_63` (±0x3f-clamping, +0x74e-accumulating) has
exactly one caller: chunk_0003.c:6248.

## B) Haste/slow hit writers — all in resolve_hitbox_target_effects_and_damage @0x8002e2a8

All triggers read the **0x18-stride damage record** (`*(hitbox+0x2c) + hitbox[0x11]*0x18`,
chunk_0003.c:7514) — NOT the 0x50-stride hit.bin record. Fields: **+0x10 = flagsA (u16)**,
**+0x12 = flagsB (u16)**, **+0x05 = comboScoreValue** (dual-role: status magnitude),
**+0x08 = hitStrength** (actually freeze/hitstop frames).

| Condition (record field) | Guards | Write | Duration/decay |
|---|---|---|---|
| **flagsB & 0x400** — contact-slow aura (7653-7677) | target is borg (+0x83==0); NOT (target+0x59e & 0x400); target borg-id not 0x805/0x80d/0x80e (divers exempt); not burst (+0x6fc) or fusion-carried (+0x4a0) | `target+0x70c = rec+0x05` only if ≥ current (max wins) | **no timer — cleared every frame** (chunk_0003.c:5949); persists only while overlapping |
| **flagsB & 0x800** — contact-haste aura (7679-7684) | NOT (target+0x59e & 0x400) | `target+0x70d = 1` (fixed ×1.25) | cleared every frame (5950) |
| **flagsB & 0x0004** — slow-on-hit (8099-8107) | rec+0x09 != 0xff, no resist, target borg, not burst/fused | `target+0x70e = 2` (×0.4); s16 timer +0x710 = 900f; fx `zz_013f300_(t,0)` when fresh | timer −1/frame in FUN_8005a378 (chunk_0007.c:2839-2844) |
| **flagsB & 0x0008** — haste-on-hit (8138-8145) | same gates but applies even to burst targets | `target+0x70f = 2` (×1.5); s16 +0x712 = 900f; fx `zz_013f300_(t,1)` | FUN_8005a378 (2846-2851) |
| **flagsA & 0x0004** — grow (7772-7776) | NOT (target+0x59c & 4); target borg, not burst | `target+0x1da \|= 0x20`; `DAT_8043612c[slot] += rec+0x05` | applied via tier-delta-63; auto-revert 900f (+0x750) |
| **flagsA & 0x0008** — shrink (7758-7770, only when bit 4 clear) | NOT (target+0x59c & 8) | `target+0x1da \|= 0x40`; `DAT_8043612c[slot] -= rec+0x05` | same |
| **rec+0x08 (hitStrength)** — freeze/hitstop (7621-7625, 7633-7640) | normal-reaction hits ((flagsB & 0xfc0)==0) | `+0x71c = max(current, rec+0x08)` on **both attacker and target** | u8, −1/frame (2881-2893); timescale ×0.03 (FLOAT_804373dc) while >0 |

**Immunity words**: +0x59c/+0x59e are **static per-borg masks loaded from the data.bin page
at +0xa8/+0xaa** (chunk_0007.c:24-25). A matching bit blocks the status and usually fires the
resist spark zz_002f8d0_; shared bit 0x400 of +0x59e blocks both aura types. A fired resist
(local_48) suppresses the whole 8090-8157 status/knockback block (deflect path instead).

**Consumption**: FUN_8005a378 (chunk_0007.c:2817-2898) rebuilds timescale +0x5f4 per frame =
1.0 × (burst? ×1.5) × haste[+0x70d] × haste[+0x70f] × slow[+0x70c] × slow[+0x70e]
(slow skipped for burst/fused/flag-0x1000000 actors), overridden to 0.03 while +0x71c>0.
Haste table DAT_802dd58c {0.1, 1.25, 1.5, 1.75}; slow table DAT_802dd57c {0, 0.7, 0.4, 0.2}.

### Record-data census (attackHitTables-referenced records only)

- Slow-on-hit (flagsB&4): **pl0b06 SLOW VALKRIE** #7. Haste-on-hit (flagsB&8): **pl0b00
  QUICK VALKRIE, pl0b03 WIND VALKRIE** #7 (support borgs buff allies by shooting them).
- Slow aura (flagsB&0x400): **pl0805 JELLY DIVER lvl1 (×0.7), pl080e JACK lvl2 (×0.4),
  pl080d TAR DIVER lvl3 (×0.2)** — exactly these three ids are hard-coded exempt from
  receiving it.
- Grow/shrink: the witches (table above).
- **Data-quality caveat (honest)**: many high-index records (pl0303 #2-4, most pl04xx/pl06xx
  #17-24) have contradictory flag combos (grow+shrink+slow+haste, magnitudes 128/147/255) —
  likely table-extent overshoot in familyDamageRecords.json, not real design data. Trust
  low-index/clean cases; sanity-filter records with both flagsA bits 4|8 set.

### Port recipe for applyHit

`rec = familyDamageRecords[family].records[hitbox.damageRecordIndex]`. Discrete statuses:
flagsB&4 → slowLevel=2/timer=900; flagsB&8 → hasteLevel=2/timer=900. Aura statuses are
per-contact-frame (level cleared each frame): flagsB&0x400 → slowLevel=max(cur,
rec.comboScoreValue); flagsB&0x800 → hasteLevel=1. Grow/shrink: accumulate ±rec.comboScoreValue
per contact frame into the ±0x3f-clamped tier path with a 900f revert. Freeze:
rec.hitStrength frames of ×0.03 timescale on both parties. Immunity: data.bin page u16 +0xa8
vs flagsA, +0xaa vs flagsB. Note +0x05's dual role: only a combo score on records without
status flags.
