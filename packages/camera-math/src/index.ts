// Pure-TS camera math: the source-owned HSD CObj state, COBJ animation system,
// and boot view-setup (zz_00059b8_ @0x800059b8), with no three.js dependency.
//
// This module lived in @gf/render, which forced every consumer — including
// @gf/combat, whose contract is "NO DOM, NO three.js" — to depend on the
// three.js package. It moves here so headless consumers (combat sim, Node
// selfchecks, test runners) get the camera math without the renderer.
export * from "./sourceCamera.js";
