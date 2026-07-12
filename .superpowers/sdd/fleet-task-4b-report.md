# Fleet Task 4B report — Cyber Machine constructor cluster

## Result

Audited constructor `0x800cc454` and all 80 live member/action/variant routes for
`pl0602`, `pl060a`, `pl060c`, and `pl060e`. The root and variant dispatch are now exact.
All four actions remain explicitly partial. Action 2's state-side routing and writes are
verified, but its mandatory armed-channel renderer/model-node consumers are not modeled.

Coverage remains **20 ported / 234 partial / 71 missing**.

## Authoritative evidence bank

- Constructor/root: `0x800cc454` -> `FUN_800cc798` (`0x800cc798`), action table
  `0x8030cd18`.
- Action 0: `FUN_800cc7d4`; variant table `0x8030cd28` =
  `[0x800cc854, 0x800ccc54, 0x800ccc54, 0x800ccc54, 0x800ccf78]`;
  phase tables `0x8030cd3c`, `0x8030cd48`, `0x8030cd54`.
- Action 1: `FUN_800cd4cc`; variant table `0x8030cd60` =
  `[0x800cd514, 0x800cd988, 0x800cd988, 0x800cdbf8, 0x800cdbf8]`;
  phase tables `0x8030cd74`, `0x8030cd88`, `0x8030cd94`.
- Action 2: `FUN_800ce5dc` for v0-v4, with no stream call. Phase 0 increments
  `+0x540`, allocates `(slot=2,count=1,mode=1)`, and conditionally calls
  `zz_016cc24_(actor,2)`. Phase 1 clears `+0x73f`, clears `+0x5e0 & 3`, calls
  `zz_006a668_(actor,1)`, and writes `+0x694 = 50 + dt`. `zz_006a668_` resets and
  arms shot channels; it does not directly spawn a projectile child.
- Action 3: `FUN_800ce138`; variant table `0x8030cda8` maps v0-v4 to
  `FUN_800ce184`; phase table `0x8030cdbc`.
- Sources: `research/decomp/ghidra-export/chunk_0021.c`,
  `research/decomp/ghidra-export/chunk_0009.c`, GG4E `boot.dol`, and
  `packages/combat/src/data/actionStreamTables.json`.

## Changed files

- `packages/combat/src/families/cyber-machine.ts`
  - corrected all action-0/action-1 variant aliases;
  - removed the invented action-4 slot and wired the live action-3 leaf boundary;
  - corrected dash target-cache/motion and final timer seeds;
  - made X allocation failure suppress the effect child;
  - implemented the proven X housekeeping, shot-channel setup, cue dispatch, and cooldown;
  - removed synthetic post-shot cue dispatch.
- `packages/combat/src/rom/actor.ts`
  - surfaced exact `+0x1d9c/+0x1db2/+0x1db3` shot-channel state and distinct
    per-part `+0x1aec/+0x1af0/+0x1af4` timing records.
- `packages/combat/src/rom/rom.selfcheck.ts`
  - added exhaustive 80-route validation and X success/denial assertions, including
    exact `zz_006a6fc_` transition/reset behavior and final `+0x36=0/+0x37=0xff`
    bytes on every armed shot block.
- `packages/combat/src/families/shared-aimed-shot-x.ts`
  - completed `zz_0048d54_`'s post-descriptor record tail writes; `+0x37=0xff`
    intentionally overrides the byte copied by `zz_004d244_`;
  - moved timing writes out of the `+0x1bd4` raw descriptor block into the separate
    per-part timing record, preventing corruption at raw offsets `+0x18/+0x1c/+0x20`.
- `research/decomp/data/family-state-machine-classifications.reviewed.json`
  - leaves constructor `0x800cc454`, action 2 partial; no unsupported promotion remains.
- Generated coverage JSON and Markdown were refreshed by the audit.

## Remaining blockers

- Action 0 still depends on exact direction selection, command reissue, contact/input gates,
  target visibility, ground collision, and afterimage integration across its phase tables.
- Action 1 variants 0-2 retain incomplete target-distance/face/contact semantics; variants
  3-4 now route to the correct `0x800cdbf8` leaf but intentionally do not execute the old
  incorrect `0x800cd988` approximation.
- Action 2 still requires the mandatory `zz_004a754_` armed-channel call for every armed
  part and `FUN_8004a8cc` model-node/quaternion-position updates. The current renderer
  does not consume those operations, so the action cannot be classified as a 1:1 port.
- Action 3 requires the `actor+0x4a4` paired actor, paired mode/state mutation, movement and
  collision helpers, and stream event `zz_00e19a8_`. Until those are modeled, the live route
  is exposed but remains partial and does not claim completion.

## Verification

- `pnpm --filter @gf/combat build`
- `pnpm selfcheck:rom`
- `pnpm audit:family-state-machines`
- `git diff --check`

The non-strict audit passes structurally at `20/234/71`. The strict audit exits nonzero
as designed because fleet-wide partial/missing slots remain.
