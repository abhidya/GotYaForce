# Combat-feel gaps decode (2026-07-05)

Static-analysis pass over `research/decomp/ghidra-export/chunk_*.c` + `boot.dol` direct reads
(dol.py). Eight decode targets, ranked by feel impact. Every claim below is either quoted from
the decompiled C (chunk:line + DOL address) or an honest UNKNOWN. Constants were read from
`user-data/GG4E/disc/sys/boot.dol` via `research/decomp/dol.py` this session.

Cross-refs: behavior-notes.md §(ah)(aj)(ak)(al)(p), movement-hit-decode-2026-07-04.md,
damage formula = `zz_003cd5c_` @0x8003cd5c (chunk_0004.c:6672-6828), hit resolver =
`resolve_hitbox_target_effects_and_damage` @0x8002e2a8 (chunk_0003.c:~7490-8195).

**Headline discoveries this pass** (each detailed in its section):
1. The "level floats" ctx+0xc4 / victim+0xb4 are the actor **size-scale floats** — init found,
   whole chain closed (T5).
2. Hitstun IS **animation-completion-gated** (+0x1d0e), and the knockback **magnitude** system
   (two 16-entry speed tables + scale-ratio multiplier) is now fully read (T6).
3. +0x3e6 is the **CPU-controlled flag**, not "hero" (T2).
4. +0x6fc is the **side-wide burst flag** set on every living teammate; a **burst
   ally-passthrough** rule exists after all (overturns behavior-notes (al) negative) (T3).
5. The "guard /40 gate" is **not a guard state** — it is a per-borg data rule (blast-flagged
   moves vs blast-hardened heavy borgs, e.g. 5000-damage nukes → 125 vs fortresses) (T1).

---

## T6. ANIM-GATED HIT REACTIONS + knockback magnitude — DECODED (biggest feel gap)

### Verdict
Hitstun in the ROM is **animation-length-gated, not flat**. The reaction state machine plays a
fixed per-reaction anim id and releases the actor **only when the anim-completion flag
`actor+0x1d0e` goes nonzero**. The port's flat `MELEE.HITSTUN` (combat.ts:987 admits this) is the
wrong model; the knockback magnitude the port already ports (gauges.ts strength tables) is
confirmed and extended with the scale-ratio multiplier.

### Reaction pipeline (all read this session)
1. **Resolver writes pending-reaction state on the victim** (chunk_0003.c:7633-7641):
   `+0x6fd |= rec[0x0b]` (reactionFlags), `+0x702 = rec[0x0d]` (signed knockback-strength
   index, json name `reactionAnimVariant`), `+0x704 = hit record index`, `+0x71c = max(rec[0x08])`
   (status duration). Knockback yaw/pitch → `+0x284/+0x282` (zz_00300bc_, §p).
   Attacker scale snapshot: `victim+0x298 = attackerObj+0xc4` (chunk_0003.c:7798).
2. **Entry dispatcher `zz_005c290_` @0x8005c290** (chunk_0007.c:3987-4050), runs when
   `+0x6fd != 0`:
   - `+0x6fd & 0x80` → wake-up invincibility `+0x720 = 60.0` (FLOAT_80437448) and hit-type
     invincibility mask `+0x272 |= 0x43` (chunk_0007.c:3996-3999).
   - Calls per-command-type gate `PTR_FUN_802d3580[actor+0x591]`; **nonzero return = reaction
     suppressed (super-armor)** — see T1.
   - Generic path: enter action 0x2e (`zz_006a750_/zz_006a6fc_`, chunk_0007.c:4010-4011), then
     slot overrides (all +0x6fe-space, abs slot = value+9):
     * `+0x5e0 & 0x5000000 == 0x5000000` → slot 9 and `+0x702 = max(+0x702, 4)` (re-hit while
       already reacting escalates strength floor, chunk_0007.c:4012-4017).
     * `+0x1da & 8` (rec flagsA 0x400, set chunk_0003.c:7752) → slot 0x14.
     * `+0x1da & 0x10` (rec flagsA 0x2, set :7740) → slot 0x12 (knockdown family).
     * `+0x272 == 0 && +0x1da & 2` (launch bit) → slot 0xd or 0xe by `+0x5e0 & 0x40`.
     * `+0x599 != 0` (rec flagsA 0x800 heavy blow-away, set :7522) → slot 0x15
       (FUN_8005dffc, the long knockdown/get-up sequence).
   - Tail: `+0x6b6 = 300`, `+0x6b4 = 30` (post-reaction timers), `+0x5e0 |= 0x1000000`
     (in-reaction latch) (chunk_0007.c:4039-4042).
   - Light-hit path: idle gates call `zz_005f00c_` @0x8005f00c (chunk_0007.c:5744-5793) which
     builds slot 1..7 from `+0x6fd` bits (bit4/bit8→+1, bit0x20 w/o 0x10→+2, bit2 or
     `+0x5e0&0x2000040`→+4, bit0x40 falling-rehit→6); during command types 1-6 (except 3)
     light bits are masked (`bVar3 &= 0xfc`, :5787) — you can't be light-flinched mid-move.
3. **Reaction handlers hold the actor until anim completes** — the gate is
   `if (*(char*)(actor+0x1d0e) == 0) keep-waiting` in every one:
   - FUN_8005db44 @0x8005db44 (chunk_0007.c:4892-4920): stagger. Phase 0: face away from
     knockback yaw (`+0x72 = +0x284 - 0x8000`), request anim **group 0x80 slot 0xd** via
     `zz_004beb8_(rate=-1.0 default, actor, 0xf, 0x80, 0xd, ...)`, seed velocity via
     `zz_005ec20_`. Phase 1: wait `+0x1d0e`, integrate slide (`zz_005ecb0_/zz_005ee0c_`).
     Exit: `+0x272 = 0`, `zz_006a474_` (return to neutral).
   - FUN_8005dc24 @0x8005dc24 (:4926-4954): same, anim slot **0xe**, restores gravity
     `+0x50 = page[+0x6c]`, slides via FUN_80067310 while waiting.
   - FUN_8005dd10 @0x8005dd10 (:4960-5025): knockdown/get-up — anim **0x13+dirBucket** (entered
     from +0x6fe==0xf) or **0x17+dirBucket**, dir bucket from `zz_0046510_(+0x284-0x8000-+0x72,2)`
     with yaw offsets `DAT_802d3628` = [0, -0x4000, 0, +0x4000]; down-height timer +0x568 seeded
     `10.0 + anim length s16 +0x1b38`; velocity damped ×0.94/frame (FLOAT_8043747c) until
     `+0x1d0e`.
   - FUN_8005df2c @0x8005df2c (:5031-5057): anim **0xd** with gravity restore, wait `+0x1d0e`.
4. **Knockback magnitude — `zz_005ec20_` @0x8005ec20** (chunk_0007.c:5546-5573), NEW full read:
   ```
   idx   = clamp(|victim+0x702|, 0..15)
   ratio = victim+0x298 / victim+0xc4        // attackerScale / victimScale (!)
   +0x44 (h-speed) = ratio * DAT_802dd8a0[idx]
   +0x4c (h-accel) = -speed / 20.0           // FLOAT_80437490 — stops in 20 frames
   +0x48 = +0x50 = 0.0
   ```
   `DAT_802dd8a0` (ROM read) = **[0, 7, 14, ..., 105] = idx × 7.0**.
   Launch variant `FUN_8005ed38` @0x8005ed38 (:5606-5639):
   `idx = clamp(|+0x702| + (+0x6fd&0x80 ? 2 : 0), 0..15)`, speed = `DAT_802d3664[idx]`
   (**= (idx+1) × 8.0**, ROM read), split by stored pitch `+0x282`
   (`+0x44 = s·cos(-pitch)`, `+0x48 = s·sin(-pitch)`), decel −0.1 (FLOAT_804374cc),
   gravity −1.2 (FLOAT_80437470).
   The **scale-ratio multiplier is NOT in the port** (gauges.ts has the tables but no
   `+0x298/+0xc4` ratio): a giant hitting a small borg launches it proportionally farther,
   and vice versa.

### Port wiring recipe
- Replace flat hitstun with: reaction slot → anim id (0xd/0xe/0x13+d/0x17+d in the reaction
  bank group, flag 0x80/0x81) → per-borg anim length from the extracted animation banks; release
  on anim end. Playback rate arg is −1.0 (= default rate).
- Multiply ported knockback speeds by `attackerScale / victimScale` (both default 1.0 today, so
  a no-op until T5 scale is live — wire them together).
- Keep `+0x6b4 = 30` / `+0x6b6 = 300` post-reaction timers in mind for the combo/rehit feel
  (they gate re-entry, chunk_0007.c:4039-4040; +0x6b4 also gates zz_005f114_ :5804-5810).

UNKNOWN: the exact anim-bank group byte for reaction slots (0x80|group addressing per
borg-animation-banks.md) → confirm the group index against the extracted banks before wiring
lengths (the ids 0xd/0xe/0x13/0x17 are slot indexes inside the flag-0x80 bank).

---

## T5. ACTOR "LEVEL"/HANDICAP floats — DECODED (they are the size-scale floats)

### Verdict
The damage-formula floats `ctx+0xc4` (attacker, step 2 `dmg *= 1 + 0.5·(x−1)`) and
`victim+0xb4` (step 13 `dmg *= 1/(1 + 0.5·(x−1))`) are **the actor size-scale floats**, not a
separate level stat. The (ak) "STILL NOT FOUND" is closed.

### The chain (all cited)
- **Init** `zz_0056180_` @0x80056180 (chunk_0006.c:8250-8293), called from borg battle init:
  `+0x74a = 0x10` (tier 16 = 1.0), tier clamps `+0x74d/+0x74c = page[0xa1]/page[0xa2]`,
  `refresh_actor_param_tier_table` (chunk_0008.c:4493-4518) writes `+0xb8` (target scale) from
  tier row `[sizeScale, animRate, velScale]`; then `+0xb4 = +0xb8` (snap) and
  **`+0xc4 = +0xc0 = +0x58/+0x5c/+0x60 = +0xb4`** (chunk_0006.c:8272, 8287-8292). The
  alternate branch (revive/carry-over, flags +0x489/+0x48a/+0x500) restores
  `+0xb4 = +0x400 / cmd[+0x4c]` clamped to +0xb8 (:8280-8284).
- **Per-frame lerp** (chunk_0007.c:3689-3710, zz_005bab8_ region): `+0xb4` steps toward `+0xb8`
  by ±0.05/frame (FLOAT_80437420, ROM read) unless frozen (+0x7c9), and **mirrors into +0x58/
  +0x5c/+0x60/+0xc0/+0xc4** every step (:3705-3709). So +0xc4 == +0xb4 == render scale.
- **Runtime writers**: tier deltas (`apply_actor_param_tier_delta_63/127` chunk_0008.c:4417-4481,
  hit-applied via rec, self-buff +4 tiers/1200f per movement doc); grow/shrink status
  (+0x70c/+0x70e paths); scale-multiply helper `zz_002caa8_` @0x8002caa8
  (chunk_0003.c:6432-6449: `+0xb4 *= k; +0xc4 = +0xb4`); resolver-applied projectile
  grow/shrink (T1). Menu-only setters: zz_0058044_ (=1.0, chunk_0007.c:1127-1145),
  garage display scaling (chunk_0007.c:1292, 1400-1980 — display objects, not battle).
- **Why the formula reads two different objects**: `zz_003cd5c_(rec, iVar19, victim)` gets
  `iVar19 = *(hitboxObj+0x20)` = the attacking OBJECT (chunk_0003.c:7511, 7948). Projectiles
  **inherit the owner's scale quadruple at spawn** (child-init copies of +0xb4/+0xb8/+0xc0/+0xc4:
  chunk_0006.c:2472-2478, 2690-2696, 2868-2874, 3127-3133, 3389-3395, 3662-3668) — so a buffed/
  grown attacker's already-in-flight shots keep the bonus, matching the burst-at-hit-time lore.
- **Down-gauge interaction** (chunk_0003.c:7996-8006): while `+0x5e0 & 0x1000000`, down-gauge
  damage only applies if `dmg ≥ downCur·(1 − 0.5·(victimScale−1))` — big victims resist
  re-downing. (Resolves (ak)'s gauges.ts conflict: it IS the victim's scale float.)

### Level byte relationship — honest negative
No corpus path feeds the LEVEL byte `+0x3ec` into tier/scale. Level feeds: HP/ammo stat-row
select via `DAT_804339e8` (chunk_0006.c:8177-8179, chunk_0007.c:63), **force cost**
`zz_0066168_` @0x80066168 (chunk_0008.c:2900-2905: `s16 PTR_DAT_802dd3b4[family][(level +
variant·6)]`), a UI byte `+0x17d = DAT_80433640[level]` (chunk_0002.c:2688-2691; ROM bytes
[2,2,2,2,2,4,0,0,0,0,0,2] for levels 0-11), and stat-row via zz_0066198_. If leveled borgs are
bigger in-game, the writer is not in the readable export — **UNKNOWN; default 1.0 is correct
for level-agnostic battles**.

### Handicap byte +0x43a — init DECODED
`zz_0056180_` chunk_0006.c:8263-8265: `+0x438/+0x439/+0x43a = PTR_DAT_80433934[slot+0x20 /
+0x32 / +0x3e]` — per-slot battle-config bytes (+0x43a = handicap index into
PTR_DAT_804335f8/80433618 tables, formula steps 8/15). Who writes config +0x3e (VS-menu
handicap): UNKNOWN (menu code unread). Default 0 = table[0]. NOTE the port's
`HANDICAP_DEFAULT_INDEX = 3` (damageFormula.ts:36,183-186) **adds +3 to the index** — the ROM
indexes `table[+0x43a]` directly with 0 default; verify the extracted table's neutral slot
really is index 3 before trusting the port's offset convention.

---

## T3. PAIR-ATTACK flag +0x6fc — DECODED (side-wide burst flag; pair is the trigger, not the flag)

### Verdict
`+0x6fc` is **"Power Burst active"**, set simultaneously on **every living actor of the side**
— it is not per-pair and not only on the button pressers. The ×2.0 damage (formula step 3,
FLOAT_80436f9c = 2.0 ROM-read) keys on the **attacker's** flag at hit-resolution time; ×0.5
incoming keys on the defender's (or its fusion parent's) flag (chunk_0004.c:6705-6707,
6761-6763).

### Trigger logic (`zz_005b2b8_` body, chunk_0007.c:3407-3493)
Per side each frame:
- Collect candidates: alive (+0x18==1), armed `+0x6fb != 0` (the 6-frame Y-press window,
  FUN_80069814 → +0x6fb = 6), not fused (+0x4a0==0, +0x4a1==0) (:3412-3423).
- If side-config byte `PTR_DAT_80433934[side·0x3c + 0xf5] == 1` → **one armed candidate
  suffices**; otherwise **≥ 2 armed candidates are required** (:3424, 3464 `else if (1 < iVar10)`)
  — i.e. in the normal config two teammates must press Y within the same 6-frame window: the
  wiki's "pair attack". Byte +0xf5's setter: UNKNOWN (probably "side has a single player slot").
- First try the **fusion pair table** (`zz_005b678_` :3500+, families 5/6 only, behavior-notes
  (aj)). If a fusion pair matches → fusion path (+0x4a1 machine), **no +0x6fc**.
- Else **burst**: side flag `[+0x104] = 1`, side timers `[+0x10c] = [+0x10e] = 600` (10 s), and
  for EVERY living side actor: `+0x6fc = 1`, `+0x6fa = 1`, `FUN_800061a8(actor, 3)` (:3429-3445),
  then side SE/announcer `zz_0067f54_(side, 2, playerMask)`.
- `+0x6fb` decrements per-slot in the same function's tail (:3473-3490).

### Other +0x6fc consumers (census)
- **Ally-passthrough — NEW, overturns (al)'s negative**: hit-eligibility filter `zz_002fd7c_`
  @0x8002fd7c (chunk_0003.c:8519-8525): if defender-actor has +0x6fc set, attacker is a borg on
  the **same side**, attacker record `flagsB & 0x10` clear, and the defender record has no
  barrier bits → **hit skipped entirely**. Teammates cannot hit a bursting ally (107/1530
  records carry the flagsB-0x10 exemption).
- Speed ×1.5 while set (timescale rebuild chunk_0007.c:2866, FLOAT_804373d8 — movement doc).
- Down-gauge doubling at hit (chunk_0003.c:7546-7549, same 2.0 constant).
- Status/shrink/grab immunity gates while set (chunk_0003.c:7667, 7761, 7780, 8098).
- AI/dispatch checks (chunk_0003.c:42/63/1891/1985, chunk_0009.c:1175, chunk_0012.c:3345).
- Cleared at spawn init (chunk_0006.c:7458).

### UNKNOWN (trace-gated)
The burst **end** path — the side timer `[+0x10c/+0x10e] = 600` decrement site and the
`+0x6fc = 0` clear — is not visible in the export (no other literal write to +0x6fc exists).
The per-frame head of zz_005b2b8_ (:3379-3397) clears related per-actor flags (+0x37e, +0x462
bit0, +0x3ef) when `[+0x104]` is 0, so the flag DOES go down; where the timer ticks is likely in
an unexported maintenance function. Port currently drains a per-player meter (−5/frame,
burst.ts:104) — a live trace should reconcile 600-frame side timer vs meter drain, and the port
should set burst on **all living teammates** (today only the activator gets `burstActive`,
burst.ts:89), which changes both the ×2/×0.5 damage scope and ally-passthrough scope.

---

## T4. FORCE-GAUGE ratio input — DECODED; port formula correct but unwired + 2 curve gates differ

### Verdict
The comeback-curve selector input is the **side's GF/force energy gauge** — the shared team
pool that pays for deaths — not any per-borg gauge.

### Runtime chain (all cited)
- **Init** (chunk_0000.c:1031-1083): per-side max `PTR_DAT_80433934[side·0x3c + 0x114]` = Σ of
  each contributing player's team cost `zz_000673c_` (which sums per-borg
  `zz_0066168_(spawnId, level)` costs), **rounded down to a multiple of 10** (:1076-1079), then
  `[+0x118] (current) = [+0x11c] = [+0x114]`.
- **Per-frame mirror** (battle_frame_target_action_dispatch, chunk_0003.c:5900-5910):
  `DAT_803b068c[side] = side[+0x118]` for the 4 side blocks (0x118/0x154/0x190/0x1cc).
- **Depletion on death** `zz_002f8dc_` @0x8002f8dc (chunk_0003.c:8212-8331): `side[+0x118] -=
  victim+0x4aa` with mode/CPU routing (:8228-8257); floor 0 → records battle-end kill pointers
  (:8275-8285). Victim cost `+0x4aa` init: `zz_0055f90_` chunk_0006.c:8186-8193 =
  `zz_0066168_(id, level)`, **×2/3 if CPU-controlled** (FLOAT_8043729c = 0.6666667 ROM-read),
  0 if flag +0x486.
- **Formula index** (chunk_0004.c:6733-6737 attacker, 6796-6800 defender):
  `idx = 32 − (mirror[side] << 5) / side[+0x114]`, clamped high to 31 (no explicit low clamp —
  cur==max gives 0). Curve tables PTR_PTR_804335f0/80433610 selected by rec byte 7 /
  pldata[0x9e].
- **Magnitude**: borg records use curve 0 almost exclusively (census: 1380/1530 records force
  curve 0; selector triples pldata 9c/9d/9e mostly 0/1/2). Curve 0 set 0: 1.00 at full gauge →
  **1.16 outgoing at empty**; defender curve 0: 1.00 → **0.93 incoming** — total comeback swing
  ≈ ×1.25.

### Port comparison (packages/combat/src/damageFormula.ts) — discrepancies, not fixed here
1. `attackerForceRatioIndex/defenderForceRatioIndex` exist with the right meaning but **no
   caller wires them** — battle.ts never feeds the team energy ratio. Recipe: idx =
   `clampIndex(32 - Math.trunc(teamEnergy*32/teamEnergyMax), 32)` per side, using the
   round-to-10 max.
2. **Attacker/defender HP-curve skip gate missing**: ROM skips the HP-ratio multiplier entirely
   when the (mirror) HP value ≥ 201 (`if ((int)uVar9 < 0xc9)`, chunk_0004.c:6718 and 6781). The
   port clamps idx to 0 instead — equivalent ONLY because every extracted curve[0] == 1.0
   (verified this session); keep the gate in mind if curves are ever re-extracted.
3. **CPU-side halvings missing** (formula steps 5/12, chunk_0004.c:6713-6716 / 6769-6772): in
   modes 0/1, a CPU-controlled (+0x3e6, see T2) attacker on side 0 deals ×0.5 and a CPU victim
   on side 0 takes ×0.5. Port has no equivalent.
4. **Step 17 missing**: `victim +0x5e0 & 0x4000000 → ×0.5` (chunk_0004.c:6807-6809). The bit's
   writer wasn't chased this pass — UNKNOWN which state sets it (candidate: a spawn/drop-in
   protection); harmless while unmodeled but should be documented in the file header.
5. Defender post-hit HP index: ROM uses `mirror − rec.hpDamage(raw u16)` floored at 0
   (chunk_0004.c:6773-6779); port uses `victim.hp − recordBase` where recordBase is
   damageScale-multiplied — divergence when damageScale ≠ 1.
6. `blockDivisorActive` should be data-driven (see T1), not a caller flag.
7. Naming: `pairNerf_80436f9c` is the ×2.0 pair BONUS (value 2.0); heroTable is the CPU table —
   rename when convenient.

---

## T1. GUARD / REFLECT — DECODED as three separate mechanisms; there is NO guard state

### Verdict
The open "guard /40 gate" note conflated three real, now-decoded mechanisms. There is **no
hold-to-block state** in the borg state machine (the earlier "Likely block/guard-start" slot-8
reading is retracted below).

### 1. The /40 divisor = blast-vs-heavy-armor DATA rule (fully decoded)
`zz_003cd5c_` chunk_0004.c:6814-6817: `victim is a borg && (rec.flagsA & 0x1000) &&
(victim+0x59c & 0x1000) → dmg /= 40.0` (FLOAT_80437028 = 40.0 ROM-read).
- `+0x59c` has exactly ONE writer in the corpus: borg init chunk_0007.c:24 =
  **pl####data.bin u16@0xa8** — a static per-borg resistance mask. Census
  (borg-gauge-init-pldata.json): 29/198 borgs carry bit 0x1000 — the dragons (pl0500-050a),
  tanks/fortress family 6 (pl0600-060f), pl0a04/pl0a09, fortresses pl0e00-0e05, pl0f05; the big
  bodies carry the full 0x1f1c mask.
- `flagsA & 0x1000` records: only 2 real ones in familyDamageRecords.json —
  **hpDamage 5000** records at 0x802fb248[2] (pl0c05) and 0x802fc350[2] (pl0c04) (the other 30
  hits are over-extended garbage rows). 5000/40 = **125** — exactly the SDA lore "the nuke
  one-shots everything except fortresses, which just take damage".
- flagsA 0x1000 also **bypasses the same-team ×0.25** (6811-6813) and **skips combo score**
  (chunk_0003.c:7934) — blast hits teammates at full damage and awards nothing.
- Port recipe: drop `blockDivisorActive`; gate on `(record.flagsA & 0x1000) &&
  (victimProfile.stateBits_a8 & 0x1000)` with the pldata@0xa8 mask added to borg data.
  The rest of the +0x59c bits are per-effect immunities consumed in the resolver
  (0x2 :7529 skip-whole-hit vs rec flagsA 0x2; 0x4/0x8 :7772/7760 tier-delta immunities;
  0x10 :7688 magnet; 0x100 :7784 balance-break; 0x200 :7725; 0x400 :7751; 0x800 :7521
  heavy-blow-away immunity — each `else zz_002f8d0_` arm sets the "resisted" local that
  reroutes the reaction).

### 2. Reflect/deflect = defender-RECORD flags acting on incoming projectiles
Resolver chunk_0003.c:7552-7584, keyed on the **defender's** damage record flagsB when the
attacker object is a projectile (+0x83 == 0x10):
- bit 0x40: `attackerProj+0xb1 |= 1; +0xbc = 4.0 · +0x44` (FLOAT_80436fa0) — speed ×4
  repel/deflect channel.
- bit 0x80: `+0xb1 |= 2; +0xbc = 0.5 · +0x44` — slow to half.
- bit 0x100: `+0xb1 |= 4; proj scale +0xb8 ×2.0 clamped ≤ 8.0` (FLOAT_80436fa4).
- bit 0x200: `+0xb1 |= 8; +0xb8 ×0.5 clamped ≥ 0.2` (FLOAT_80436fa8).
Any of these suppresses the normal hit-mark path (bVar3) and spawns deflect effect id 4/8
(zz_00db250_, :8084-8086, 8159). Eligibility filter zz_002fd7c_ :8449-8452 makes such records
**projectile-only** (non-projectile attackers can't hit them at all) — these are the
Barrier Girl / Guard Witch / knight-shield hurtboxes (behavior-notes (am) "shields are physical
blockers"). 160/1530 records carry bits 0x3c0. The consumer of +0xb1/+0xbc (how the projectile
applies the new speed/heading) is in the projectile step fns — not chased: **PARTIAL**.
- Related: rec **flagsA bit 2** = full-hit skip vs +0x59c bit 2 (:7529-7531) and
  flagsB & 0xc00 = "only hits borgs/0x20-objects" (:8453-8454).

### 3. Super-armor = per-command-type reaction suppression (retraction of "guard-start")
`zz_005c290_` gates through `PTR_FUN_802d3580[actor+0x591]`; handlers for +0x591 == 4
(FUN_8005c5d0 @0x8005c5d0, chunk_0007.c:4120-4132) and == 5 (FUN_8005c638 :4138-4155) **return 1
= swallow the reaction** (unless thrown +0x1da&0x10 / heavy +0x599), granting the 0x80-flag
invincibility and playing a **voice cue** — `zz_00ea2c8_(actor, 4)` @0x800ea2c8
(chunk_0025.c:1821-1876) is a VOICE/SE dispatcher (zz_00dbf04_ + DAT_80319d99 table), NOT a
guard state. So command types 4/5 (per §3 the B-charge/X-special classes) have inherent
super-armor: damage still applies, reaction doesn't. The idle-slot promotions
(+0x6fe = 0xf/0x10/0x11, FUN_8005c4c8/FUN_8005c530 :4067-4103) are air/parity **reaction-slot
selections** (gated on +0x5e0 & 0x40), not guard entries.

---

## T2. HERO flag actor+0x3e6 — DECODED: it is the CPU-CONTROLLED flag

### Writers (complete census — grep every `0x3e6` in the corpus)
- Battle spawn (chunk_0006.c:7087-7101): `+0x3e6 = ((PTR_DAT_80433930[2] & +0x3e5) == 0)`,
  mirrored to +0x488 (1/0) and +0x3f3. `+0x3e5 = 1 << playerIndex` (chunk_0006.c:6572) and
  `PTR_DAT_80433930[2]` is the **active human-player bitmask** (proved by the force-gauge init
  chunk_0000.c:1044-1054 testing bits 1/2/4/8 per player slot). So **+0x3e6 = 1 ⇔ no human
  controls this actor**.
- Menu/garage spawns force 0 (chunk_0007.c:933, 1267 = FUN_80057b78 / FUN_80058244).

### Readers (what "CPU" changes)
- **Damage formula**: selects table set [1] vs [0] for every rank/curve/handicap stage
  (chunk_0004.c:6708-6712, 6759-6766 — the `(-c|c)>>0x1d & 4` idiom), and the mode-0/1
  side-0 ×0.5 halvings (steps 5/12) — CPU allies on the player's side hit and get hit softer.
- **Input**: `dispatch_slot_action_update` @0x800680d4 (chunk_0008.c:4373-4385) skips the
  controller-driven slot handler when set — the actor runs on AI instead.
- **Force economy**: death cost ×2/3 (chunk_0006.c:8188-8193); which side's gauge pays on death
  routes on it per mode (zz_002f8dc_ chunk_0003.c:8231-8256).
- **AI target selection** treats player vs CPU targets differently (chunk_0003.c:1438, 1529,
  1542, 1931, 3184) and battle SE/announcer paths (chunk_0003.c:8059, chunk_0015.c:5136/5306,
  chunk_0022.c:3139 via owner +0x90).
- Fusion role arithmetic (chunk_0007.c:3545-3567), pair partner checks (chunk_0009.c:430).
- Spawn UI byte +0x3f3 (story mode 2 → 0).
Port note: `heroTable` in damageFormula.ts should be driven by "is CPU" (1 for CPU actors), and
the missing side-0 halvings (T4 item 3) belong to the same feature.

---

## T7. KNOCKBACK MODES 0/2/3/4 — DECODED semantics + census; two vector identities PARTIAL

`zz_00300bc_` @0x800300bc (chunk_0003.c:8540-8627, §p) — mode = rec byte 0x0e
(`knockbackDirMode`, read as **signed** char). NEW this pass: the "wrapper objects" are the
**hitbox objects** themselves (layout proved by FUN_8008a65c chunk_0013.c:1125-1213: +0x20 owner
actor, +0x24 linked/root actor, +0x28 hit.bin record, +0x2c damage table, **+0x30/0x34/0x38
world pos, +0x3c/0x40/0x44 prev pos**, +0x60 bone-matrix ptr, +0x48/+0x4a window, +0x11 damage
index).

| mode | census (1530 recs) | source vector | identity status |
|---|---|---|---|
| 0 | 220 | attackerACTOR pos(+0x20..28) − prevPos(+0x2c..34); fallback actor +0x38/+0x3c/+0x40 | pos/prevPos Confirmed (zz_005ee0c_ chunk_0007.c:5658-5659 uses the same pairs as per-frame motion); +0x38 fallback = Likely the actor's velocity/aim vec3 — **PARTIAL** |
| 1 | 55 | defenderActor pos − attackerActor pos | Confirmed (already ported) |
| 2 | 308 | hitbox pos(+0x30) − hitbox prevPos(+0x3c) = **hitbox travel direction** | Confirmed via chunk_0013 layout |
| 3 | 9 | defenderHitbox+0x64 − attackerHitbox+0x64 | +0x64 = field after the bone-matrix ptr (+0x60); likely bone-world anchor — **PARTIAL/UNKNOWN** |
| 4 | 822 (dominant) | cascade: attackerObj +0x8dc/+0x8ec/+0x8fc → linked obj same → attackerObj +0x11c/+0x12c/+0x13c | stride-0x10 triples = **column 2 (forward axis) of 3×4 matrices at +0x8d4 (muzzle transform — cf. slot-33 handler's page+0x8d4 use) and +0x114 (root transform)**: mode 4 = "muzzle/actor forward axis" — Derived, high confidence |
| other | ~116 rows | values 5..255 come from over-extended extraction rows (junk); 255 = −1 signed | treat any mode ∉ 0..4 as data noise; −1 rows never resolve (unreachable-arm per §p) |

Degenerate-vector guard (<0.01 sq-len → (0,0,−1)), BAM conversion, +0x284/+0x282 writes, and the
linked-object mirror are unchanged from §p. Magnitude consumers now decoded (T6).

---

## T8. PER-MOVE ANGLE TRIMS — DECODED (mechanism §p + NEW value census)

Record bytes 0x14/0x15 (`knockbackYawTrim`/`knockbackPitchTrim`, signed) are added to the
computed yaw/pitch as `trim × −0x100` (1 unit = 256 BAM = **1.40625°**, sign inverted by the
×−256; pitch is itself stored negated, so positive pitch-trim values pitch the launch UP in the
FUN_8005ed38 `sin(−pitch)` sense — assert the net sign in one live trace before locking UI-level
signs). Census over familyDamageRecords.json (1530 records):
- 98 distinct nonzero (yaw,pitch) pairs; **(0, 24) on 893 records** — the standard ≈33.75°
  upward launch trim; then (0,40)=67, (0,32)=58, (0,48)=31, (0,56)=27, (0,16)=24, (0,−64)=21.
- Yaw trims are rare and mostly ±128 (=180°, "launch away-side", 18 records as (−128,12)).
Port recipe: knockback direction = mode vector → yaw/pitch → add trims — the data is already in
familyDamageRecords.json; nothing further to extract.

---

## Extra constants dumped this session (boot.dol direct reads)
```
FLOAT_80436f94=2.5  FLOAT_80436fb8=1.5  FLOAT_80436fbc=3.5   (impact-variant size thresholds vs victim radius +0x7fc, zz_002fc18_ chunk_0003.c:8337-8364; rec byte 0x0a bit 0x80 enables size-scaled variant)
FLOAT_80436fa0=4.0  FLOAT_80436fa4=8.0  FLOAT_80436fa8=0.2   (deflect ×4 / grow clamp 8 / shrink clamp 0.2)
FLOAT_80436fac=60.0                                          (gauge-regen delay seeds +0x684/+0x688/+0x68c)
FLOAT_8043729c=2/3   FLOAT_80437420=0.05  FLOAT_80437490=20.0
FLOAT_80437470=-1.2  FLOAT_804374cc=-0.1  FLOAT_8043747c=0.94  FLOAT_80437474=0.99
FLOAT_80437464=-1.0 (anim-rate arg = default)  FLOAT_80437478=10.0 (down-height seed)
DAT_802dd8a0[16] = idx*7.0 (ground knockback speeds)   DAT_802d3664[16] = (idx+1)*8.0 (launch)
DAT_802d3628[4]  = [0,-0x4000,0,0x4000] (get-up direction yaw offsets)
DAT_80433640[12] = [2,2,2,2,2,4,0,0,0,0,0,2] (per-level UI byte, levels 0-11)
FLOAT_8043740c=0.7 FLOAT_80437410=2.0 (fusion size-window check, chunk_0007.c:3647)
```

## Per-target verdict summary
1. GUARD/REFLECT — **DECODED** (no guard state; /40 = blast-flag × heavy-armor-data rule;
   deflect/grow/shrink = defender-record flagsB on projectiles; super-armor = +0x591 gates;
   +0xb1/+0xbc projectile-apply site PARTIAL).
2. HERO +0x3e6 — **DECODED** (CPU-controlled flag; writer + full reader census).
3. PAIR +0x6fc — **DECODED** (side-wide burst flag on all living teammates; ≥2 armed pressers
   required unless side byte +0xf5==1; ×2 keys on it at hit time; ally-passthrough found;
   burst-END clear site UNKNOWN/trace-gated).
4. FORCE-GAUGE — **DECODED** (input = side energy +0x118/+0x114, mirror DAT_803b068c; port
   formula shape right but unwired; 7 listed discrepancies incl. missing CPU halvings and the
   ≥201-HP skip gate).
5. LEVEL/HANDICAP floats — **DECODED** (they are the size-scale floats; init zz_0056180_;
   projectiles inherit; level→size link NOT found = honest negative; handicap +0x43a init found,
   menu writer UNKNOWN).
6. ANIM-GATED REACTIONS — **DECODED** (anim-completion-gated via +0x1d0e; full slot/anim map;
   knockback magnitude = scale-ratio × 16-entry ×7/×8 tables; reaction-bank group byte
   confirmation pending).
7. KNOCKBACK MODES — **DECODED** semantics + census (mode 4 = muzzle forward axis dominates;
   mode 0/2 = actor/hitbox motion; mode 3 + mode-0 fallback identities PARTIAL).
8. ANGLE TRIMS — **DECODED** (record bytes 0x14/0x15 ×1.40625°; census: (0,24)≈33.75° up on 58%
   of records; net sign assertion trace-gated).
