# Audio Port Status

Purpose: keep audio fidelity honest while the 1:1 port is incomplete.

## Current Evidence

- `apps/game/public/audio/manifest.json` contains 33 BGM tracks, 5 generic `se00_00..04`
  SFX, and 46 sampled voice clips.
- Every exported manifest entry now records the source archive, AFS member index, source byte
  offset, source byte length, and SHA-1 of the source ADX member. Runtime code can inspect
  these fields through the optional `@gf/audio` manifest provenance fields.
- `scripts/export-audio-assets.mjs` expects the original `poq_adx_usa.afs` at
  `user-data/GG4E/disc/root/poq_adx_usa.afs`; that archive is present in this workspace.
  The exporter maps AFS members `0..32` as BGM, `33..37` as `se00_00..04`, and `38..2112`
  as voices. The existing web export still only includes a small SFX/voice subset.
- The five exported `se00_00..04` clips are not proven short menu/combat cues; several are
  multi-second clips. Treating them as confirm/hit/shot blips was the source of the obviously
  wrong audio feel.
- `research/decomp/behavior-notes.md` section `(v)` checked the apparent
  `AnimAudioEventLookup` lead and found it is a generic sort/template symbol, not a decoded
  frame-to-sound table. Hit-bin records also do not have a proven sound-id field yet.
- DOL evidence shows CRI/ADX/AFS plumbing (`mwPlyStartAfs`, `ADXF_GetFnameRangeEx`,
  `mwPlySetAudioSw`) but no decoded semantic table that maps menu/combat events to exact
  AFS member indices yet.

## Runtime Rule

- BGM still uses exported ADX material: `bgm00` for menus and `bgm01` for battle. Exact track
  semantics remain unproven.
- Menu confirm/back/edit SFX are muted because the only obvious samples are multi-second
  clips, not short menu blips.
- Combat SFX edge hooks exist, but the generic combat mapping is disabled by default. Enable
  `?tunedCombatSfx=1` only for debugging. This avoids presenting `se00_01`/`se00_04` as
  final 1:1 combat audio.
- Current rule: only BGM plays by default. Unknown menu and combat SFX stay silent until a trace
  maps a runtime event to an AFS member index.

## Next Proof Steps

1. Produce a full scratch index for all ADX members, especially voices `38..2112`, without
   automatically wiring them into runtime playback.
2. Trace in-game BGM and one-shot sound IDs around battle start, menu confirm/back, attack, hit,
   down, death, victory/loss, and results transitions.
3. Add cue aliases to `manifest.json` only after a traced sound ID maps to an exported member.
