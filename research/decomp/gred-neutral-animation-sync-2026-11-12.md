# G RED-family neutral-combo pose synchronization

Local continuation from `7cd9dfa5`. No original assets are added; publication
remains paused.

## Evidence and scope

The source-derived neutral-combo clocks already drive simulation for G RED
(action1/v0, slots0→1→2), NEO G RED (25→26→variant6/27) and G BLACK (13→14→15).
Their evidence and exact stream/descriptor addresses are recorded in
`gred-neutral-chain-2026-11-12.md`, `neo-melee-chain-2026-11-12.md`, and
`gblack-neutral-chain-2026-11-12.md`. Original animation handling is traced through
487ec/4892c and clocks49f10/4a00c/4a0e0. This lane does not change their timing.

Previously only G Crash published its source animation frame to the renderer;
neutral attacks rendered independently despite source-clock collision timing.
The bridge now samples the admitted neutral clock too. Each real playAnim gets a
unique epoch, including combo transitions and NEO recovery. Mode1's held frame0,
mode2's advancing blend, fractional frames and terminal poses follow simulation.
New B admission and existing exit/interruption/morph paths clear stale ownership.
All admitted B/X routes share the epoch counter, preventing cached clip collisions.

The existing metadata hop still chooses exported motion references. Neutral clips
resolve to group1 slots1/2/16 (RED),1/2/19 (NEO),25/5/24 (BLACK). NEO's recovery
uses the existing group0slot24 resolution. Exact clips use the existing source-frame
renderer. Missing exact clips keep ordinary fallback playback; no generic fallback
is falsely treated as source-owned.

## Validation and limitations

Actual B-input Battle tests cover all three families' mode1 holds, intermediate
frame7, same-clip replay and combo epochs, natural completion and death. NEO also
checks mode2's frame2 advance and separate finisher/recovery epochs. Existing damage,
contact/retap, mine, groundwave, landing and negative-input assertions remain.

CPU Three.js scene tests cover all nine neutral motion refs using synthetic clips:
held frame0, fractional3.5 sampling, and no render-delta drift. Existing cached-action,
async completion, fallback, pause and cleanup tests remain active. This is not a
browser screenshot comparison or console replay. Source crossfade interpolation,
original animation assets, collision bone transforms, hitstop/burst rate rules and
terrain remain outside this bounded synchronization change.

Manifest-resolved local baked clips were checked read-only: RED frame counts are
28/36/36, NEO28/36/41 plus recovery2, BLACK36/41/71, all fps60. These span the
admitted original end frames27/35/35,27/35/40/1 and35/40/70. The renderer still uses
actual track sample times, not an added hardcoded60 conversion. Existing inherited
ratebyte0→host rate1 and stripped-root-motion approximations remain explicit.

## Final checkpoint

Independent actual-input suites for all three families pass, as do the existing
G Crash regressions. Full `verify:contributor` passed on the frozen code, including
TypeScript, frontend/input/session/Challenge, all renderer checks, ROM and combat
lifecycle, importer tests and production build. Only the existing bundle-size
warning remains. No browser visual replay or deployment was performed.
