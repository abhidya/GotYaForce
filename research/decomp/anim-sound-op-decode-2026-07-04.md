# Anim-driven sound decode (2026-07-04)

Question: which action-script stream opcode(s) trigger sounds, and where does the sound id
live? TWO results, both proven this session:

1. **Stream op 0x0e IS a playSound opcode with a literal id in its operand — but the GG4E
   boot.dol action-script banks NEVER use it** (0 occurrences across all 114 known banks /
   12031 stream slots; full op histogram below). Honest negative for stream-level extraction.
2. **The REAL carrier of per-move swing audio is the per-ANIM sound-event table at
   `actor+0x4e8`** (the "PATH B" combat-se-ids.json pointed at) — and it is STATIC boot.dol
   data joined to the anims the streams play, so it IS statically extractable after all.
   Format fully decoded + validated on G RED below; this is what the port now extracts and
   wires.

## Method

The borg action-script interpreter dispatches stream ops through the handler pointer table at
`0x802d0da0` (18 entries, ops 0x00..0x11). Every handler body was checked for calls into the
sound layer (`zz_00efb3c_` @0x800efb3c dispatcher, or wrappers `zz_00f036c_`/`zz_00f061c_`/
`zz_00f0104_`/`zz_00f0f84_` that reach it):

1. Handlers present in the decomp corpus were read directly (chunk_0006.c:1609-1938).
2. Handlers MISSING from the corpus (ops 0x02-0x07, 0x0b, 0x0c, 0x11) were verified by raw
   PPC `bl`-target scan of boot.dol over each handler's address range (scratchpad script,
   this session). One further level was scanned for every non-sound helper the handlers call.

## Result: full handler table sound audit

| op | handler | corpus | bl targets | sound layer? |
|----|-----------|--------|------------|--------------|
| 0x00/0x01 | 8004c298 | chunk_0006.c:1615 | 80048648 (anim start helper; deep-scan clean) | no |
| 0x02 | 8004c424 | not decompiled | (none) | no |
| 0x03 | 8004c488 | not decompiled | (none) | no |
| 0x04 | 8004c4dc | not decompiled | (none) | no |
| 0x05 | 8004c504 | not decompiled | (none) | no |
| 0x06 | 8004c52c | not decompiled | (none) | no |
| 0x07 | 8004c594 | not decompiled | (none) | no |
| 0x08 | 8004c5fc | chunk_0006.c:1683 | 8004d08c (deep-scan clean) | no |
| 0x09 | 8004c67c | chunk_0006.c:1710 | 80099e70 fireChild (deep-scan clean) | no |
| 0x0a | 8004c6b4 | chunk_0006.c:1727 | 8008ac80 armHit (deep-scan clean) | no |
| 0x0b | 8004c75c | not decompiled | (none) | no |
| 0x0c | 8004c7a4 | not decompiled | (none) | no |
| 0x0d | 8004c7fc | chunk_0006.c:1756 | 80048f9c blend helper (deep-scan clean) | no |
| **0x0e** | **8004c97c** | **chunk_0006.c:1826** | **800f036c, 800f061c — BOTH sound wrappers** | **YES — literal id** |
| 0x0f | 8004ca3c | chunk_0006.c:1865 | 800b2190 (clean), **800f07e8 — sound wrapper** | yes — table-driven, NO id in operand |
| 0x10 | 8004caa4 | chunk_0006.c:1885 | (none) | no |
| 0x11 | 8004cccc | not decompiled | (none) | no |

## Op 0x0e — playSound (defined by the engine, UNUSED by the data)

Handler `FUN_8004c97c` (chunk_0006.c:1826-1859). 4-byte record, `*streamPtr += 4`.

Operand layout:

| byte | meaning |
|------|---------|
| 0 | opcode 0x0e |
| 1 | part index 0..3 — handler gates on `partMask & (1 << byte1)` (chunk_0006.c:1835). Part 0 is the main body script; multi-part borgs address a specific part. |
| 2 | mode (see below) |
| 3 | **literal soundId** (u8) — passed straight into the wrapper, which passes it straight to dispatcher `zz_00efb3c_` (bank = id>>7, sample = id&0x7f; battle banks snd_com01/02). u8 range covers banks 0-1 only. |

Modes (byte 2), chunk_0006.c:1836-1856:

- **0** — `zz_00f036c_(actor, id)`: play `id` positionally at actor+0x20 (world pos), through
  `zz_00f04b4_` -> `zz_00efb3c_(id, screenSide, vol, pan, 0x2000)` (chunk_0026.c:790-866).
- **1** — anim-rate pitch-variant select: reads `*(float*)(actor+0xb4)` (the anim playback
  rate) and plays `id-1` when rate < 0.7 (`FLOAT_80437134`), `id` when 0.7 <= rate <= 2.0
  (`FLOAT_80437138`), `id+1` when rate > 2.0 — i.e. the ROM stores the NORMAL-speed sample at
  `id` and expects slow/fast neighbors at id∓1. Then `zz_00f036c_` as mode 0.
- **2, 3** — `zz_00f061c_(0.2 /*FLOAT_8043713c*/, actor, id)`: position pulled 20% toward the
  local listener anchor before the positional play (chunk_0026.c:902-927); falls back to plain
  `zz_00f036c_` when the actor isn't on the listener's screen slot.
- **>= 4** — no-op (the `(bVar1 != 4) && (bVar1 < 4)` guard at chunk_0006.c:1854).

Evidence chain to the dispatcher: `zz_00f036c_` (chunk_0026.c:790) -> `zz_00efb3c_(id,0,0x7f,
0x40,0x2000)` when actorless, else `zz_00f04b4_` (chunk_0026.c:854) -> `zz_00efb3c_`.
`zz_00f061c_` (chunk_0026.c:902) -> `zz_00f04b4_`/`zz_00f036c_`. Same dispatcher already
proven for the 11 code-literal combat SE ids (scripts/export-combat-se.py header).

Timing: like every stream op, the record executes when the interpreter's wait clock reaches it
(op 0x00 wait records; `zz_004cd24_` chunk_0006.c:1996), so the preceding wait's frame context
IS the sound's play frame — identical semantics to how armHit frames were extracted.

**Usage census (honest negative):** walking EVERY slot of every known action-script bank
(the 114 distinct family/shared banks bound at actor+0x1d80/+0x1d84 across the 191 resolved
roster borgs — 12031 slots) finds **zero** op 0x0e records. Full op histogram:
`0x00:13152 0x01:8476 0x02:9449 0x03:8768 0x04:24 0x05:12 0x06:247 0x07:245 0x08:573 0x09:18
0x0a:799 0x0b:785 0x0c:31 0x0d:525 0x0e:0 0x0f:48 0x10:57 0x11:781`. The walker is the same
one meleeAnimKinds.json self-validates with (871 hit-bearing slots, 190/191 borgs clean vs
hit.bin), so the walk itself is trusted. gen-melee-anim-kinds.mjs still decodes op 0x0e (as
`playSound`) in case other regions/banks use it, but on GG4E it emits nothing.

## PATH B — the per-anim sound-event table at actor+0x4e8 (the REAL swing audio)

Consumer: `zz_005b880_` (chunk_0007.c:3579-3624), called per frame from the actor anim
update. For each of the 4 anim parts (part state block = actor+0x1ad4 + part*0x40):

- `idx = *(s8*)(partState+0x37)`; -1 = this part's current anim has no sound events.
- events start at `*(actor+0x4e8) + idx*8` and are 8-byte records, list runs while the
  CURRENT record's byte+6 != 0xff (i.e. +6 is a continue/terminate flag).

Record layout (big-endian, consumed by `zz_005b98c_` chunk_0007.c:3632-3668):

| off | type | meaning |
|-----|------|---------|
| +0 | u16 | **frame** (anim-clock frame the sound fires on; 0 = anim start — sentinel compare vs `FLOAT_804373e4` = 0.0) |
| +2 | u8 | window flag: 0 = plain cur-frame compare, nonzero = windowed prev..cur compare (uses partState+0xc/+0x14 and s16 partState+0x24) |
| +3 | u8 | **mode** — IDENTICAL semantics to op 0x0e's byte2: 0 plain positional (`zz_00f036c_`), 1 anim-rate variant select id-1/id/id+1 (rate `actor+0xb4` vs 0.7/2.0 = `FLOAT_8043740c`/`FLOAT_80437410`), 2\|3 listener-lerped positional (`zz_00f061c_(0.2 /*FLOAT_80437404*/)`), >=4 no-op |
| +4 | u16 | **soundId** (u16 → full 0..0x17f dispatcher range; bank = id>>7, sample = id&0x7f) |
| +6 | u8 | continue flag (0xff = last record of this anim's list) |
| +7 | u8 | pad (0 in all sampled records) |

Where the pieces bind (all family-ctor stores, same recipe as the action-script banks):

- `actor+0x4e8` = the family's sound-event TABLE (e.g. G RED ctor `zz_018ccfc_`
  chunk_0046.c:4803: `PTR_DAT_8036556c` -> 0x80365878; the pl062a variant REBINDS it to
  0x803659a0 at chunk_0046.c:4813-4814 — per-borg ctor emulation is required, not per-family).
- `actor+0x1d88` / `+0x1d8c` = family/shared ANIM-DESCRIPTOR banks (chunk_0046.c:4810-4811;
  G RED 0x80367460 / 0x802bb698). Lookup `zz_004d1f4_` (chunk_0006.c:2210): same s16
  group-offset -> s16 slot-offset scheme as the action-script banks, keyed by the playAnim
  op's (group, slot) — group bit7 selects the shared bank. THIS is the join: the action
  stream plays anim (g, s); the descriptor record for (g, s) carries the sound-list index.
- Descriptor record (consumed by `zz_004d244_` chunk_0006.c:2232): per-part sub-records at
  +4/+0xc/+0x14/+0x1c; **byte +8+part*8 = the part's sound-list start index** into the
  +0x4e8 table (0xff = none). (Other descriptor bytes: +0 clip id -> partState+0x32,
  +4/+5 -> +0x2a/+0x2b, +6 flags, +7 -> u16 +0x26, part-0 extras +9/+0x11.. blend params.)

### Validation (G RED, pl0615)

Every playAnim target of the family bank's group-3 (melee) hit-bearing streams resolves
through descriptor bank 0x80367460 to a well-formed 1-record sound list in table 0x80365878:
soundId **0x24** (heavy sword whoosh) or **0x0b** (light whoosh) at frames 4-21, windowFlag 1,
mode 0, cont 0xff, pad 0 — exactly a per-swing whoosh at windup, a few frames before each
kind's hit.bin active window. Shared-bank movement anims that carry no sounds read idx 0xff
(e.g. g0s14). Both ids resolve to audible TSB entries in snd_com01.

## Op 0x0f — table-driven voice/cry (id NOT in the operand)

Handler `FUN_8004ca3c` (chunk_0006.c:1865-1877). 4-byte record: byte1 = part index (same
gate), byte2 must be 0, byte3 unused. Calls `zz_00b2190_(actor, 2)` (non-sound, deep-scan
clean — FX/state helper) then `zz_00f07e8_(actor)` (chunk_0026.c:972-987), which plays
`s16 DAT_80434410[v & 0x7f]` where `v = PTR_DAT_8031b7f4[*(char*)(actor+0x3e8)][*(u8*)(actor
+0x3e9)]` — i.e. a per-borg (family byte / index byte) VOICE table lookup; bit7 of the table
byte selects the listener-lerped wrapper `zz_00f061c_(0.2, ...)`. The sound id is **not**
extractable from the stream operand — it rides the borg-id-indexed table. Not wired this
session; the existing per-family voice-cue presentation (behavior-notes (az)) covers the
audible effect. Decoding the DAT_80434410/PTR_DAT_8031b7f4 tables is a separate follow-up.

## Extraction + port wiring (this session)

- `scripts/gen-melee-anim-kinds.mjs`:
  - decodes stream op 0x0e into `{op:"playSound", ...}` events (emits nothing on GG4E — see
    the census above — but the decode is correct and future-proof);
  - ctor emulation now also captures `+0x1d88`/`+0x1d8c`/`+0x4e8`, and each stored stream's
    playAnim/blendAnim events are joined to their PATH-B sound lists; per-borg
    `borgs[id].animSounds["g{G}s{S}" | "shared:g{G}s{S}"] = [{frame, id, mode, part}]`
    (part-deduped by frame/id/mode — parts often share a list).
- `packages/combat/src/actionStreamData.ts` exposes the swing anim's sounds on
  ComboStep/ExactMoveLeaf (`sounds`); combat.ts hands the current swing's list to the
  renderer via `BorgRuntime.meleeSounds` (same bridge pattern as meleeAnimStream).
- `scripts/export-combat-se.py --export --ids <hex,...>` exports the census'd anim-event ids
  on top of the 11 code-literal ones.
- DERIVED: the id, its anim frame, and the sample audio. TUNED: the port plays the mode-1
  base id only (no anim-rate variant select — the port's anim rate is not the ROM's +0xb4
  clock), positional modes 0/2/3 all play flat, and the frame delay is scheduled off the
  slot-enter edge at 60fps rather than the ROM part-anim clock.
