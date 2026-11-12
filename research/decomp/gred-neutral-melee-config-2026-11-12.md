# G RED neutral melee configuration

Local follow-up to `7f414d10`. Original numeric values were read in place from
the authorized GG4E executable. No original binary or asset is added or uploaded.
Publication remains paused.

## Verified correction

Original actor615/action1/variant0 dispatches through `8018de34` to shared melee
engine `80177dd8` using configuration `80365634`:

- seed slot0
- proximity150
- timer20
- deceleration0.949999988079071 (float32 0.95)
- chain callback0 and alternate callback0

The existing common placeholder used seed0, proximity100, timer30 and default
deceleration1. Only the G RED neutral ground-opener dispatch now selects a
separate exact configuration. Other borg IDs/variants retain their prior code;
that preserves scope, not a claim their placeholder behavior is correct.

The original wrapper and config consumers `80177e28` through `801780e4` verify
that these fields control the phase timer, approach/proximity and deceleration.
The host bridge uses dt1; the existing shared engine multiplication matches that
fixed-step branch. Variable-dt, animated HIT timing, target geometry and broader
shared-engine completeness remain outside this correction.

## NEO investigation, not fixed here

Family action dispatcher `8018dd9c` selects separate variant tables for actor615,
62a and629. NEO variant0 uses wrapper `8018de9c`, config `80365664`, seed25 and
chain callback `8018ded0`. That callback redispatches action1 then selects
variant6, whose original handler uses a different five-phase engine `80179280`.
The current shared port lacks that engine and source chain input/contact/stream
bit mappings. NEO slots0 and25 alias the same stream address `803666d8`; a
seed-only change would not fix the meaningful combo divergence.

This change therefore does not advertise NEO support or silently reuse the
G RED handler for NEO's finisher. Those existing gaps remain explicitly open.

## Validation

Five independent scenario groups pass: decoded fields/phase0 stream, timer and
inclusive proximity boundary, deceleration/recovery, scoped root dispatch, and
fresh real B admission. Tests distinguish direct phase fixtures from real-input
coverage. NEO/G BLACK and other G RED variants retain their previous values.
The existing fresh G RED melee-to-mine suite passes unchanged. Combat typecheck
and diff check pass. Full `verify:contributor` passes, including the complete
lifecycle suite and production build. Log: `gred-config-contributor-final.log`
in the reconstruction workspace parent. Existing large-bundle warning remains.
No publication or deployment was attempted.

No original-console replay or browser visual comparison was performed. The source
constants are exact, but existing host physics arithmetic/geometry and shared
phase adapters remain bounded rather than instruction-level equivalents.
