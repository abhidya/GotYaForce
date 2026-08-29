// mot.ts — MOT animation (motion) container parser. Big-endian. Still a stub.
//
// Status: container layout solved upstream (NeoGF `mottool` parses the CONTAINER ONLY —
// no bones, no keyframes); the keyframe/bone-track decode inside a MOT is still unreversed.
//
// What CHANGED, and why this is no longer on the critical path: the old header here said the
// tracks "must be correlated with the model skeleton once mdl-arc is cracked." `mdl-arc` was
// cracked on 2026-06-30 — `_mdl.arc` is HSD DAT (see `mdl-arc.ts` and
// `research/format-specs/arc-hsd-format.md`) — and the animation that the game actually plays
// rides the HSD path, not this one: HSD FOBJ tracks composed onto the JOBJ tree. That path is
// implemented twice over. `hsd-anim.ts` in this package is a TypeScript port of HSDRaw's
// `FOBJ_Player.GetValue` and JOBJ transform composition (the reference implementation), and
// `scripts/export-borg-animation-hsd.mjs` bakes clips offline through the same C# math. 185
// Borgs currently ship animated on that pipeline.
//
// So MOT decode is a completeness question for the remaining `.mot` source banks, not a
// blocker on anything the browser needs. If it is picked up: port the container from mottool
// first, then reverse the track payload; export target is glTF animation.
export {};
