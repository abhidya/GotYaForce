# Action-stream table extraction — audit (2026-07-04)

Generator: `scripts/gen-action-stream-tables.mjs` → `packages/combat/src/data/actionStreamTables.json`.
Recipe: `research/decomp/cue-script-stream-decode-2026-07-04.md` ("Fleet extraction recipe"),
implemented as concrete PPC emulation of each family's `+0x4b4` attack virtual per
(borg, `+0x580` actionIndex, `+0x581` variantIndex), capturing every
`zz_004beb8_(rate, actor, mask, group, slot)` stream call (r4=mask, r5=group, r6=slot) with
config-byte provenance, forking on unknown branches and labelling `(+0x5e0 & mask)` state-flag
forks (baseline = all clear; air = only 0x40 set).

## Coverage

- 208/208 roster borgs rooted (`+0x4b4` recovered from the ctor for all; fallback vector
  inference `pointerLabel-0x38` never ended up load-bearing).
- 117 distinct family roots walked.
- (actionIndex, variantIndex) pairs enumerated from commandMoveTables records whose cue maps
  (via the borg's `+0x4f0` cue table) to full-body state 61 — the only state whose
  `PTR_LAB_802d36a8` handler calls `(**(actor+0x4b4))()` (verified by scanning all 0x50 state
  slots); closure extended by chain callbacks and runtime `+0x581` redirects.
- **2198/2540 leaves resolved (86.5%)**; 342 unresolved, honestly bucketed:
  - 224 "no stream call reached (code-driven or shot-only action)" — e.g. EAGLE JET pl061b's
    a0/a1 (FUN_8012b188 writes joint angles directly, machine-borg turret behaviour), shot-cue
    actions handled by the upper-body/shot system.
  - 31 "leaf returns to neutral (zz_006a474_/zz_006a5a4_)" — real no-op variants (e.g.
    FLAME DRAGON pl0500 a1 = FUN_80075e80 clears `+0x5e0` bits and exits).
  - 21 "run capped" (fork/step budget exhausted before any stream call).
  - 10 "child/projectile spawn observed" (zz_0099e70_/zz_00e19a8_ fire instead of a stream).
  - 56 "ambiguous" — mostly the pl0a0x giant/gattai dash chain where one channel-0 call
    passes slot -1 (0xffffffff) alongside an unrecovered cursor slot.
- Join vs `meleeAnimKinds.json`: **2198/2198 (100%)** of resolved leaves have the bank present
  and every emitted slot (seedSlot, airSeedSlot, slotCandidates) within the group's slot table
  (walked to the -1 sentinel); 716 seed at a hit-bearing stream (charge windups and dash
  cursors legitimately seed no-hit streams; hits come from follow-ups/children).
- Group histogram of resolved leaves: g2 (dash) 723, g3 (melee) 708, g4 (charge/air) 704,
  g0 (runtime `+0x582` default group) 63. 674 leaves carry an `airSeedSlot`; 251 chain
  callbacks, 13 runtime `+0x581` redirect variants, 78 runtime slot-candidate sets,
  88 multi-channel overlays, 20 explicit combo follow-ups. 107/208 borgs fully resolved.

## Ground-truth validation (script exits non-zero on any mismatch)

1. **G RED family ctor 0x8018ccfc** — the report's "G RED pl0615" melee rows are byte-for-byte
   the **default** borg-id branch of FUN_8018dd9c (variant table 0x80365614), which in the DOL
   belongs to id **0x629 (NEO G RED)**; id 0x615 selects 0x803655d4 and 0x62a 0x803655f4
   (chunk_0047.c:283-291). Both validated:
   - **pl0629**: root 0x8018d24c, action table 0x80365588, a1 table 0x80365614 with
     v0 = zz_0177dd8_ cfg 0x80365664 g3 **s25** (chain cb 0x8018ded0 → v6), v1 = s29,
     v2 = s28, v3 = s30 (baseline of the `+0x5e0 & 0x2000` jump-redirect), v4 = s33,
     v6 (chain-only) = zz_0179280_ cfg 0x803657c4 g3 **s27**; charge a3 = zz_0179814_
     cfg 0x80365854 g4 **s2 ground / s2 air**. Seeds {25,27,28,29,30,33} + ladder s26 via
     `+0x6ea` auto-increment = the report's 25/26/27/28/29/30/33. Air a2 = g4 s1 (FUN_8018e888
     seeds `+0x6ea=1` specifically for id 0x629, chunk_0047.c:807-817).
   - **pl0615**: a1 table 0x803655d4 (seed-0 ladder: v0 g3 s0, v1 s4, v2 s3, v3 s5, v4 s12),
     air a2 = g4 **s0** (the report's air row — FUN_8018e888 default-id branch), charge
     g4 s2/s2.
2. **pl0200 Sword Knight**: root FUN_80073f3c, a1 variant table 0x802d4844 with
   v0 = zz_015809c_(actor,0) g3 **s0**, v1 = zz_0158688_(actor,3) g3 **s3**,
   v2 = zz_0158688_(actor,4) g3 **s4**; charge (a2, phase table 0x802d486c →
   zz_007454c_) g4 **s0 ground / s1 air** (`slot = (+0x5e0 & 0x40) ? 1 : 0`,
   chunk_0010.c:1687). Exactly the report's table. Bonus beyond the report: a0 dash
   g2 s0/s1/s2 and a1 v3/v4 = zz_0158a94_ g3 s5.

## Notable per-family oddities

- **Dash rams play two channels**: phase 0 arms mask 1 (slot = `+0x6ee` cursor, sometimes
  biased, e.g. FUN_8006fdf4's `+0x6ee + 6`) and mask 2 (fixed overlay slot), not mask 0xf
  (FUN_8006fb8c chunk_0009.c:4249-4250). Emitted as primary + `additionalStreams`.
- **Combo ladders inside one action**: pl0004's charge phase 0 seeds `+0x6ea=0`, plays s0,
  then inline-calls the next phase which plays s1 (FUN_80162804/zz_01628d4_,
  chunk_0042.c:756-841) — handled by per-path call sequencing (`pseq`), follow-ups emitted as
  `comboFollowUps`.
- **Runtime variant redirects**: FUN_8018e0f8-style leaves set `+0x581=5` and jump to the v5
  leaf when `(+0x5e0 & 0x2000)` (jump state) — the redirect target is walked as its own
  variant (`discoveredVia: runtime +0x581 redirect`), the flag-set stream also lands in
  `conditional`.
- **Borg-id-conditioned seeds inside shared handlers**: FUN_8018e888 (G RED family air-B)
  seeds `+0x6ea` = 1 for 0x629 / 4 for 0x62a / 0 otherwise; pl0100's family dash adds 0xe for
  id 0x108 (zz_00724c8_ chunk_0010.c:301-305). Handled by concrete borg-id emulation.
- **Interleaved action-script banks**: 0x8032744c's group-offset array starts 12 bytes into
  0x80327440's and both share slot tables. A "next table" bound therefore truncates slot
  counts (0x80327440 g3 is 8 slots, not 3); the join walks each slot table to its -1 sentinel
  instead. NOTE: `scripts/gen-melee-anim-kinds.mjs` `parseBank` still uses the next-table
  bound and silently drops streams from such banks (pl0402/pl0408's g3 s3..s7 exist but are
  missing from meleeAnimKinds.json).
- **Charge configs carry setup callbacks** (config word 4/5, e.g. G RED's 0x8018eda8/
  0x8018edc4) which the chain scanner correctly rejects (they don't store `+0x581`); the real
  chain overrides (FUN_8018ded0 → v6, FUN_8018dfac → v7) re-issue a command via zz_006a3d0_
  and then store the target variant.
- **pl0a0x (giant/gattai) dash chains** pass slot -1 on channel 0 alongside mask-4 calls —
  left unresolved rather than guessed (slot -1 semantics unproven).

## Emulator notes (for future maintenance)

- PPC subset with byte-granular actor/stack memory, provenance-carrying values (DOL source
  address, actor-offset + bias for runtime cursors, dispatch-index taint for `+0x580`/
  `+0x581`/`+0x540` jump tables), bounded forking on unknown branches, `+0x5e0` flag-mask
  labelling, and opaque-with-clobber treatment of irrelevant callees (prescan: callee
  transitively reaches zz_004beb8_, a bcctr dispatch, or stores to +0x580/581/6ea/6ee).
- r2/r13 small-data bases recovered from `__init_registers` at the DOL entry.
- Special-cased (call or tail-call): zz_004beb8_ (record stream), zz_006a3d0_ (command
  re-issue), zz_0099e70_/zz_00e19a8_ (child spawn), zz_006a474_/zz_006a5a4_ (neutral return).
