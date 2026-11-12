# G Crash motion arithmetic correction

Local continuation from50a93fab. Publication remains paused; no original assets
are copied into this lane.

## Reachable failure

Actual X input for G RED, NEO G RED and G BLACK selects type2/subtype0,
action2/variant0 row80365dd0. With stationary owner position and saved own
position both[0,10,0], the old phase0 moved Z by−161.5 for a targetZ170 and−950
for a targetZ1000. Continued carry compounded that target-dependent displacement.
This was a mistranslated motion calculation, not original retreat spacing.

## Four verified source corrections

1. Phase0 FUN8018e888 subtracts saved **own** position+5e8 from current position,
   scales that displacement by f32(.95), then adds it to current position.
   Existing beginFrame maintains targetCache5e8 as own history. Enemy location
   must not supply this displacement, and absence of an enemy must not skip it.
2. Phase2 FUN8018eb2c updates +38 (motion.x) with +3c (motion.y)×dt plus old+38,
   then caps it to+40 (motion.z). The original PPC fmadds has one final f32
   rounding. It does not double motion.y. With initial[0,10,60], normal updates
   accumulate10,20,...60.
3. Source45238 is cosine for horizontal speed;45204 is sine, negated for vertical
   velocity. The steering field is signed16-bit BAM, converted with original
   f32 constant80437078=0.0000958738019107841 (raw38c90fdb), not radians already.
   The old code reversed sine/cosine as well as misinterpreting its input units.
4. Phase3 FUN8018ec34 uses DOUBLE8043b108 raw4330000080000000 as the PPC signed
   integer-to-double conversion bias4503601774854144. It is not a gameplay
   subtraction of176. Steering becomes s16(trunc(f32(s16(steering)×f32(.9)))).

Original .95/.9 constants were verified as exact f32 values. Host Math.sin/cos
are not asserted bit-identical to original console math helpers. Phase-level
fixtures should distinguish algorithmic/cast correctness from full PPC parity.

## Boundaries

This is a narrow motion-math correction to an already reachable X route. Existing
stream/contact gates, gravity adapter, approximate81-frame whiff fallback,
terrain/target geometry, visuals and overall X lifecycle are not declared exact
by these fixes. Tests and final verification will be recorded when frozen.

## Focused verification

Independent tests pass for saved-own-position carry with absent/near/far targets
across all three family IDs; initial phase1 motion[0,10,60]; phase2 linear
acceleration/cap and a one-final-rounding regression; signed BAM cardinal/wrap
projection; signed/truncated recovery damping including zero invariance.
Six actual neutral-X traces compare target distances300/3000 within each of
pl0615, pl0629 and pl062a. Each same-ID pair has identical initial motion and
no target-distance fling. Different IDs' inherited vertical trajectories are not
assumed identical. Neutral RED/NEO/BLACK chain regressions and combat TypeScript
also pass. Source review found no discrepancy in the four scoped corrections.

Post-fix runtime probes additionally confirm stationary entry position[0,10,0]
at target distances170 and1000 for all three IDs and phase2 accumulator
0→10→20→30 while acceleration10/cap60 remain unchanged. Current inherited X
logic can still rise excessively and retain steering0; correcting these four
arithmetic errors does not validate the complete trajectory or original effects.

## Final verification

Full `verify:contributor` passed on the frozen code, including repository policy,
TypeScript, frontend/input/pause/session/Challenge gates, renderer resource tests,
ROM checks, full combat lifecycle with the six real-X traces, importer tests and
production Vite build. Only the existing bundle-size warning remains. Local-only
checkpoint: no publication/deployment, original asset transfer, console replay or
whole-game completion claim.
