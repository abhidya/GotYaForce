// mdl-arc.ts — *** CRITICAL-PATH BLOCKER: the unsolved model format. ***
//
// `_mdl.arc` (e.g. deck00_mdl.arc, box00_mdl.arc) holds borg geometry + skeleton +
// material + animation. NO PARSER EXISTS ANYWHERE — this is the project. (PHASE0 §1, §12.)
//
// What is known:
//  - Identified on the NeoGF RE wiki as ARC = "HSD Files" (HAL Sysdolphin lineage).
//    Confidence: Likely (identification) / Unknown (parse). Big-endian.
//  - The HSD STATIC-LINK shortcut (HSD linked into boot.dol, making HSDLib/Melee tooling
//    directly applicable) was REFUTED 0-3. Treat HSD as a hypothesis to TEST against real
//    `_mdl.arc` / `plxxxx.pzz/000`, NOT an established path. Time-box the HSDLib go/no-go.
//  - Related undocumented family to triage by magic byte: chd / dpk / tsb / txg.
//
// Export target: glTF/GLB (geometry + skin + AnimationClip), validated by rendering one
// borg in three.js against a Dolphin screenshot. This module gates Phases 5-6 of the roadmap.
//
// TODO (the actual research): identify ARC structure -> meshes -> skeleton -> weights
//   -> materials; correlate animation tracks from mot.ts; emit glTF.
export {};
