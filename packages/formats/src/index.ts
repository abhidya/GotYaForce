// @gf/formats — Gotcha Force binary format parsers (Python tools ported to TS / wrapped
// via WASM) so the browser can read disc bytes directly from the cache. Outer/mid layers
// are solved (pzz/arz/afs/tpl/mdt); the model container (_mdl.arc) is the UNSOLVED
// critical path. (PHASE0 §1, §4, §10.)
//
// GameCube is big-endian (PowerPC Gekko) unless a format's TOC is proven LE (e.g. AFS).
export * as pzz from "./pzz.js";
export * as arz from "./arz.js";
export * as afs from "./afs.js";
export * as tpl from "./tpl.js";
export * as mot from "./mot.js";
export * as mdt from "./mdt.js";
export * as mdlArc from "./mdl-arc.js";
export * as hsdAnim from "./hsd-anim.js";
