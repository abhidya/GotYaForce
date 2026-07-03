# Audio Port Status

Purpose: keep audio fidelity honest while the 1:1 port is incomplete.

## Current Evidence

- `apps/game/public/audio/manifest.json` contains 33 BGM tracks, 5 `se00_00..04` SFX, and 46
  sampled voice clips. Every entry records source archive, AFS member index, source byte
  offset/length, and SHA-1 of the source ADX member (readable through the optional `@gf/audio`
  manifest provenance fields).
- **Export-duration bug found and fixed (2026-07-02).** The previous `se00_*` and most voice OGGs
  did not match their ADX sources: e.g. `se00_00.ogg` was 12.0s while the ADX header for AFS
  member 33 gives 59,520 samples @ 44.1kHz = **1.35s** (block-count arithmetic on the 33,534-byte
  member agrees). 41 of 84 exported files (all 5 SFX + 36 of 46 voices) mismatched their source
  durations; all 33 BGM tracks were fine. Re-running `scripts/export-audio-assets.mjs --export
  --force` fixed all 84 (verified: every manifest `durationSec` now matches its ADX header within
  0.15s). Real SE durations: `se00_00` 1.35s, `se00_01` 1.86s, `se00_02` 1.07s, `se00_03` 0.47s,
  `se00_04` 0.64s.
- **This invalidates the old runtime rule's rationale.** Menu/combat SFX were previously muted
  because the SE clips appeared to be 3–12s "loops/jingles". They are actually short one-shot
  cues. Which SE plays for which in-game event is still NOT ROM-traced — the mapping below is
  TUNED — but the "wrong-length asset" objection is gone.
- `research/game-design/poq-adx-member-index.json` is the full scratch index of all 2115
  `poq_adx_usa.afs` members (offset, size, ADX channels/sample-rate/sample-count/duration,
  exporter range label, exported key where applicable). This closes "Next Proof Steps" #1 from
  the previous revision of this doc. It is an index, not semantic proof: the `voice-range` block
  (members 38..2112, mostly 0.2–2s mono 44.1kHz clips) is not proven to be voices-only.
- `research/decomp/behavior-notes.md` §(v): no recoverable ROM per-action audio-event table
  (`AnimAudioEventLookup` is a generic sort-template symbol; hit.bin/comhit.bin records have no
  identified sound-id field). §(g): CRI/ADX/AFS plumbing confirmed in the DOL
  (`mwPlyStartAfs`, `ADXF_GetFnameRangeEx`, `mwPlySetAudioSw`) but no decoded semantic table
  mapping events to AFS member indices.
- `afs_data.afs` (455MB main data archive) was scanned for embedded sound banks (2026-07-02):
  no MusyX/DSP/AGSC/RSTM magics and no filename table were found in any of its 2857 members
  (the recurring `STIH` magic is the hit.bin family). So the exported `poq_adx_usa.afs` material
  is the only recoverable sampled audio; the sequenced/DSP SFX path referenced by
  `sndSeqContinue` in the DOL has no extractable asset bank identified yet.

## Runtime Rule (current)

- BGM: `bgm00` menus, `bgm01` battle, wired in `apps/game/src/main.ts` (`AUDIO_CUES`). Exact
  track semantics remain unproven; no per-stage/per-mode BGM table exists, so battle keeps a
  single track. No ROM loop points are documented anywhere, so BGM loops whole-track
  (manifest `loop: true`), which is honest-but-approximate.
- Combat + menu SFX are ON by default since the duration fix. `?noCombatSfx=1` disables battle
  SFX for debugging (this replaces the old opt-in `?tunedCombatSfx=1`, whose muting rationale
  was the now-fixed 12s exports).
- Voices (46 exported `pl{family}_00_{00,01}` clips) remain UNWIRED: no traced clip semantics.
- Determinism: audio never feeds back into the sim. Battle cues are emitted from two
  render/app-layer observers only — sim-state snapshots diffed around `battle.step()`
  (`snapshotBattleAudio`/`emitBattleAudioEdges` in `main.ts`) and the edge-triggered
  `BorgAssets.onSlotEnter` hook in `battleScene.ts`. Both routes share one per-event
  rate-limit map (`playCombatSfx`), which also dedupes the overlap between them.

## Event → File Map (TUNED, not DERIVED)

No traced sound IDs exist, so assignments were guided by waveform analysis of the decoded PCM
(envelope shape, attack/decay, zero-crossing rate — see `main.ts` comment above `COMBAT_SFX`):

| Event | Trigger source | Cue | File | Real dur |
| --- | --- | --- | --- | --- |
| Melee swing (each slot entry, incl. `melee_alt` alternation) | slot edge + sim edge | `se00_03` | `audio/sfx/se00_03.ogg` | 0.47s |
| Damage taken (local borg or its lock target; hp drop / hit state) | sim edge | `se00_03` | same | 0.47s |
| Shot fired (all weapon families — no per-family SFX assets exist) | sim edge + slot edge | `se00_04` | `audio/sfx/se00_04.ogg` | 0.64s |
| Charge-shot release (`chargeFrames` drains on the shot step) | sim edge | `se00_02` | `audio/sfx/se00_02.ogg` | 1.07s |
| Special attack | sim edge + slot edge | `se00_02` | same | 1.07s |
| Knockdown (`down`) | sim edge + slot edge | `se00_00` | `audio/sfx/se00_00.ogg` | 1.35s |
| Dash (`dash`, `dash_fwd/back/left/right`) | slot edge | `se00_00` | same | 1.35s |
| Death / explosion | sim edge + slot edge | `se00_01` | `audio/sfx/se00_01.ogg` | 1.86s |
| Lock-on target acquired/switched (local borg) | sim edge | `se00_04` | `audio/sfx/se00_04.ogg` | 0.64s |
| HUD low-energy alert (ally gauge crosses 25%, matches visual alert) | sim edge | `se00_02` | `audio/sfx/se00_02.ogg` | 1.07s |
| Menu confirm | menu handlers | `se00_03` | `audio/sfx/se00_03.ogg` | 0.47s |
| Menu back / edit | menu handlers | `se00_04` | `audio/sfx/se00_04.ogg` | 0.64s |
| Menu BGM | screen transitions | `bgm00` | `audio/bgm/bgm00.ogg` | 97s loop |
| Battle BGM | `enterBattle` | `bgm01` | `audio/bgm/bgm01.ogg` | 88s loop |

Deliberately unwired (no plausible asset — leaving silent beats reintroducing wrong-asset bugs):
jump, land, footsteps, charge HOLD loop (only the release is audible; no loopable charge sample
exists), menu cursor-move (no central cursor handler; no distinct blip asset), per-weapon-family
shot variants, melee finisher distinction (no distinct sim event), announcer/character voices.

## Next Proof Steps

1. ~~Produce a full scratch index for all ADX members~~ — DONE:
   `research/game-design/poq-adx-member-index.json` (2115 members).
2. Trace in-game BGM and one-shot sound IDs around battle start, menu confirm/back, attack, hit,
   down, death, victory/loss, and results transitions (emulator trace of `mwPlyStartAfs` /
   `ADXF_GetFnameRangeEx` arguments would pin AFS member indices to events).
3. Identify the sequenced-SFX asset path behind `sndSeqContinue` (the real per-move combat SFX
   are probably DSP/sequenced, not ADX streams; no bank was found in `afs_data.afs` members'
   headers, so they may be embedded inside DOL-referenced data or nested archives).
4. Replace the TUNED table above cue-by-cue as traced IDs land; keep this doc's map in sync with
   `COMBAT_SFX`/`AUDIO_CUES` in `apps/game/src/main.ts`.
