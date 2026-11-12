# NEO G RED airborne B chain

Local continuation from `93c2fbaf`; publication remains paused. Original assets
are inspected in place and are not added. This lane requires the complete chain,
not a seed-only NEO profile.

## Verified original route

Action1/variant4 table80365614 selects wrapper18e198 and engine178394 with
config8036577c: seed33, range300, pursuit20, brake4, carryf32(.9), speed40,
transition.25, dampingf32(.9). Exact jump then close B selects row80365dc8
`[45,3,1,4]`. Type1 and subtype4 are distinct. Descriptor AC2560/AE3072,
gravity−1, range rows1000/1200/1300 and aim joint3 are verified.

The reachable chain is33→34→35. Slot35 aliases BLACK slot24's stream80366e74,
but MUST retain NEO engine settings, captured target and phase4 state.
Source178908 latches contact and B retap before ticking the stream, then tests
negative auxiliary contact. Continuation clears both latches, increments the
stream cursor, starts the next stream, resets speed to40*cos/−sin only if the
new dash byte is positive, and returns before aim/damping/physics/ground probe.
It does not rerun phase0, reset timers or recapture the target.

## Main and recovery clocks

Slots33/34 play metadata3/19 and3/20, resolving to motion1/20 and1/21, original
ends30/45. Both mode1, blend2, start0, retained rate0. Startup opcode03 supplies
dash24/face1 and controlFFFF (preserve); opcode02 groupFF preserves the current
default group. Gates3 contact1;5 contact0/6e9=1;14 for33 or15 for34 contact−1,
aux−1/6e9=2. These negative auxiliary gates permit hit-and-retap continuation.

On main end, both play recovery metadata0/14, end1, mode1 blend15/start0,
contact/aux0,6e8=3/6e9=0,dash−1/face0,709clear1f. Terminal waits for elapsed15.
New play seeds blendElapsed=dt, elapsed0/frame0; there is no same-call animation
advance. Recovery must invalidate old HIT windows and receive a new animation
instance. The final35 stream has BLACK's end50/gates and auxiliary0, so there is
no fourth strike. None of these streams has a functional opcode11 callback.

## Hit records and presentation

Slot33 HIT24→record39→damage29/HP5, active7..10; slot34 HIT25→record40→damage30/HP5,
active7..9. Both are shape2/bone7, flags1/refresh0, offset and extent[0,0,100],
radius50: static local capsule endpoints0→200 along Z. Final35 uses HIT6 records6
and19 exactly as audited for BLACK, including renewed shared history at17.
Original bone transforms and swept geometry remain replaced by the explicit
instantaneous root/yaw adapter.

Existing clips have31/46/51 samples and recovery2 at60fps, consistent with
original ends30/45/50/1. Original post/equipment effects, RNG, host geometry and
nonunit yaw/cooldown/watchdog limitations remain; no complete parity is claimed.

Implementation and independent tests are complete locally. No publication, deployment
or original-console replay is claimed.

Raw HIT startup bytes are0a1819ff/0a1919ff for33/34 and0a0619ff for35,
confirming status25/arg255 on all three. These metadata values are now explicit
per-stream profile fields; downstream status-effect behavior remains unbound.

## Focused verification

Independent clock traces pass for all three slots at dt1 and.5. At dt1, slots33/34
enter recovery on calls33/48 and finish on49/64; slot35 ends on56 without recovery.
Tests assert elapsed0 on recovery play, negative auxiliary windows, no fourth
stream and preservation of NEO config through the terminal BLACK alias. Existing
RED/BLACK clock tests remain separate regression coverage.

Actual-input tests pass for hit-plus-retap33→34→35, four braking dispatches,
no movement on the continuation call, retained target/timer/config, new animation
instances, final shared hit waves and no fourth strike. Held/stick/miss/invincible
negative controls and a late retap after recovery begins are covered. Geometry,
no-floor and survival fixtures are explicitly labeled rather than console parity.

## Final checkpoint

Full `verify:contributor` passes on frozen code, including repository policy,
TypeScript, frontend/session/input/Challenge, renderer checks, ROM/combat lifecycle,
importer tests and production build. Existing RED/BLACK air-B, neutral chains and
all family X regressions remain green. Renderer checks now cover all three NEO
chain motion references using synthetic clips, while existing async/recovery and
cleanup checks remain active. The final exact HIT metadata assertion also passes.
Only the existing bundle-size warning remains.

Independent source review approved config persistence, allowed stream guards,
startup group preservation, continuation ordering, recovery HIT invalidation and
new animation epochs. Root capsule/sweep/terrain/aim, effects, cooldown and watchdog
limits remain as documented. This is a local functional lane, not complete-game
parity or live deployment. No assets were added or publication attempted.
