# Diver source-backed visual pulse

## Evidence

Read-only original-disc/DOL inspection on the rig (no assets copied): DOL SHA-256
`21454a8880c6254616662710d6ec626e43d853999da2cdfad700030960a94836`,
ISO DOL base `0x1f700`. Source `FUN_8012151c` initializes child +0xd4 to zero
and the table's initial scale to 0.01. `FUN_80121694`, chunk_0033.c, increments
phase by 3, wraps at 360, converts the f32 product of phase and the angle factor
to a truncated short, then calls `zz_0045204_`.

Original f32 constants read in place:

| Address | Value | Bits (where relevant) |
| --- | --- | --- |
| 0x80439a88 | 0 | |
| 0x80439a8c | 3 | |
| 0x80439a90 | 360 | |
| 0x80439a94 | 1 | |
| 0x80439a98 | 0.04769999906420708 | 0x3d436113 |
| 0x80439a9c | 182.04444885253906 | 0x43360b61 |
| 0x80439aa0 | 0.11110000312328339 | 0x3de38866 |

Wrapper `0x80045204` uses signed-16 `psq_l` via GQR5 (standard setup
`0x00070007`, scale zero), `fmuls` with FLOAT_80437078, then calls
`0x8023c9e8` (`gnt4_sin`) and rounds with `frsp`. FLOAT_80437078 is
0.0000958738019107841, bits `0x38c90fdb` (f32 pi/32768), at DOL offset
`0x3af298` / ISO offset `0x3ce998`.

The update sets X/Z to `1 + amplitudeXZ * sine` and Y to
`1 - amplitudeY * sine`, then multiplies by owner base scale. The browser keeps
these explicit f32 boundaries and signed-short conversion. Original instruction
`0x8012175c` (`ec03007a`) is `fmadds` for X/Z amplitude*sine+1;
`0x80121794` (`ec0100ba`) is `fmadds` for Y amplitude*(-sine)+1.
Each combined expression rounds once, with no intermediate product rounding;
owner scaling rounds afterward. Phase uses `fadds`/wrap `fsubs` (integer degrees
here remain exact); the degree product uses `fmuls` then `fctiwz`.
Fixed phase111/123 fixtures distinguish this from extra intermediate rounding
under the current bounded sine model. This arithmetic evidence is separate from
the unresolved source-libm equivalence. It uses JavaScript
Math.sin, **not a bit-exact implementation of the source fdlibm gnt4_sin**.
Source libm, chunk_0069.c:5394–5433, dispatches rem_pio2/kernel functions;
that exact implementation and its rounding parity are not claimed here.

## Runtime boundaries

Phase is owned by the existing simulation contact update, never renderer delta
time. Refresh only restores lifetime, preserving phase and identity. The scene
copies absolute XYZ scale and continues copying bone translation independently;
it does not inherit bone rotation/scale. Collision retains the existing
owner-base-scaled root/max-extent sphere, without the visual pulse.

The browser initializes phase 0 and table scale 0.01, then runs the active update
in the same simulation tick. Its first observed phase is therefore 3. No new
initialization delay or growth tween is invented. Source scheduler visibility
of the initialization frame is not established. Particle teardown, exact libm,
collision shape and full original-game visual parity remain outside this change.

## Verification

Actual player X for Jelly, Tar and Jack travels through Battle, immutable
observation, presentation adapter and Three scene. Tests cover the first browser
active update, positive and signed-short negative quarter cycles, all 120 phase
steps, repeated scene sync and varied render dt without simulation advancement,
owner size, independent collision radius, nonaliasing snapshots, and actual
recharged-X refresh without phase reset. Existing normal-bolt, fallback attack,
material selection, bone translation and cleanup controls remain in the suite.

Semantic negative-control bundles (ignored `.tmp` output only) freeze the phase
increment or replace the anisotropic result with a uniform scale. Both fail at
`pl0805 first active pulse reaches scene from actual X`. A separate renderer-only
uniform-scale mutation fails the absolute anisotropic propagation assertion.
These are behavioral failures, not compile/import failures.

After confirming the two original `fmadds` instructions, fixed phase111 and
phase123 tests pass with the combined-expression rounding. A semantic bundle
that restores the extra intermediate product rounding fails specifically at
`phase111 fmadds must not round intermediate product` (exit 1). Lifecycle,
actual-X scene selfcheck and workspace typecheck pass after this correction.
