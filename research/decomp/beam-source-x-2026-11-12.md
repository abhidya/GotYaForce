# Beam Gunner X: bounded browser lane

## Scope and verification

`pl0104`, exact command type 2 / action 2, ground variant 0 and air variant 4.
This change replaces the generic row-0/no-projectile path with the original
`800e19a8` row 1 sustained emitter. It does not port other users of that spawner,
other Beam Gunner attacks, the global stream VM, or the full collision engine.

Original GG4E ISO/DOL values were independently read in memory during this work.
No original assets or binary dumps are added. Source excerpts are in
`docs-site/public/chunks/`.

## Admission and resources

- Original command records: ground `80321408` bytes `[44,3,2,0]`, air
  `80321448` bytes `[45,3,2,4]`; variant3 record `80321438` uses `[45,3,2,3]`.
  Both Beam airborne variants dispatch cue45, preserving the exact source entry.
- Raw input path: `8010d450` (chunk 0030:2406–2597) preserves PAD buttons, adds
  left-stick direction nibble shifted 16, and C-stick nibble shifted 20.
  `8008bbc0` masks with `ff1f7f`. Actor `5bc = 5b4 & ~5b8`
  (chunk 0007:291); `8006de44` counts bits in `5bc & f0f00`.
- A/B/X/Y bits are `100/200/400/800`. Browser jump/attack/special/hyper bind to
  those face buttons in `apps/game/src/sim/adapter.ts`. Held inputs add nothing.
  Left-stick octants at `80433928` are `[2,10,8,9,1,5,4,6]`, right/up/left/down
  `2/8/1/4`; raw radial threshold is 30, inclusive. `800452a0` computes truncated
  f32 `atan2(y,x) * 10430.3779296875`. Shoulders and C-stick do not extend this move.
- Browser normalized axes lack original PAD bytes. Scaling normalized input by127
  before signed-byte quantization is an explicit input-device approximation.
- `800562b8` initializes the second stat segment into source cell2, not cell1.
  The browser HUD cell1 aliases that same object. Level0 row `802e025c` reads
  `(300,5,5,1,60,1,1,0,300)`: X max1, refill mode0, 300-frame debt. This lane uses
  the existing source refill math and consumes only at the authored release gate.
- Busy/dead frames still sample input edges; rejected presses are not buffered.
  No generic fallback is generated for this exact source action.

## Actor and stream timeline

Source actor handlers `80103714/801037f8/8010398c/80103aec`, chunk0028:4533–4703.
`804393c8 = 60.0` (bits42700000), count budget `3c = 60`. Phase2 first refunds
`min(popcount,remainingBudget)` then checks timer<=0; otherwise subtracts actor dt.
Releasing X does not stop the beam. Holding X does not refund it or retrigger it.

Bank `803209e0`, group4 slots0/1/2; clock in `beamStream.ts` is deliberately scoped.
The legacy flattened events omitted waits and prematurely released at frame6.
`8004cd24` tests the wait before animation advance; mode0/-1 waits for animation
end, mode8 counts down, mode bit0 (value1) is terminal, mode2 compares local animation time.

- Slot0 `80321070`: anim4/0, blend15, start0, EndFrame9; wait animation end;
  contact1; wait2; contact0; wait30; anim4/1 blend5 start0; terminal frame5.
- Slot1 `803210b4`: anim4/1, no blend, start6; contact1; waits animation end.
  Descriptor flags5 rewinds at9 with EndFrame11, so this is a live loop, not a
  terminal script. The actor timer replaces it with slot2.
- Slot2 `803210d4`: anim4/2 blend5 start0 EndFrame8; animation end followed by
  a separate terminal end wait. Completion is fifteen ticks after entry.
- Relative to admission t0 at neutral dt1: contact t25, contact clear t27,
  second animation t57, release t68 (input frame69). No mash: phase3 entry t129,
  recovery complete t144. With sixty extension events phase3 entry t189.

Original op3 `8004c488` replaces posture bits4..11 with its operand masked byff0:
slot0 sets airborne40, while slots1/2 clear it. This is applied without changing
the source action ownership bits. Part1 state/aux are zeroed. Op2 sets defaultGroup1
at slots0/2, zeroes6e8, and writes6e9=2 at t27/slot1 (otherwise0). The decoded
6e9 charging-art consumer `800967e0` remains an audiovisual gap. Source startStream
clears709; slot0 op0b010100 sets bit1. These flags are mirrored as scoped scratch
state, without inventing ammo/refill effects. The generic VM's opposite op0b
direction is not reused. Known709 consumers refresh contact/effect counters; they
are not integrated into this lane.

Blend clocks seed elapsed1 and use encoded blend+1 duration. These reconstructed
clocks remain tied to the bridge's neutral actor dt1; full source haste/freeze/
per-animation variable rate integration is outside this lane. The 240-frame host
safety ceiling is above the bounded neutral maximum, not the source release clock.

## Emitter, geometry, and pulse lifecycle

Spawner `800e19a8` takes row1 **and a pointer** to owner+6f7, not state-byte-as-row.
Source emitter functions are chunk0024:1580–2098. Row1 at `80317268`:

- HIT kind10; joint1; loop selector0; global model `8054` (bank84); effect -1.
- maxscale3; local offset `(0,25,350)`; pitch/yaw0; aim dot `.9238790273666382`.
- Constants: `80438dc8=0`, dcc15, dd0 `.0000958738019107841`, dd4=1,
  dd8=-1, ddc10, de0=15100, de8double4503601774854144, df0=1.
- Original model0 HSD preorder joint1 has identity rotation/scale and world
  translation `(0,109.79737567901611,0)`; root translation is included. Static
  preorder correspondence is the existing model conversion convention, not an
  independently verified original runtime joint cache.

Constructor: no growth or collision. Each active update increments age; scale is
`min(3,age/15*3)`. The owner's current model scale participates every frame.
Collision auto-aim uses the admitted target, only inside the source dot cone;
it never adopts a replacement lock. Start/end points are attachment transformed
local z10 and z15110 multiplied by beam scale. Actor seeking consumes the stored
+524 point: visible captured target refreshes globally before movement, invisible
or lost targets retain the last point (`8005685c`).

Child pulse cadence: countdown starts0, subtracts live owner dt and resets1 on
allocation. Each pulse has its own attack ID, fixed spawn-time radius, and victim
set. HIT10 remaps to record9; source shape0/radius30; damage record9 at family table
`803214e0`: HP3/down100/balance4/combo1, strength1, impact1, flagsA1, flagsB0,
reaction flags2/variant8, direction mode4, pitch trim24, rehit interval0.

Critical missing-function recovery: original pulse table includes `80139c50`, a
40-byte function absent from the decompiler corpus. Binary inspection confirms it
sets phase2 and copies the **live endpoint pointer** at +148 into position. Thus:

1. `80139bbc` initializes at the current start pointer, a sphere.
2. Next update `80139c50` moves to the parent's live endpoint. `80139cc0` updates
   its transform; `8003a5e4` turns previous/current positions into swept shape2.
3. Following update `80139c78` clears hitboxes; later cleanup frees the object.

The same victim cannot reconnect to the same pulse across its sphere and sweep;
different fresh pulses can connect. All admissible victims are considered, not
only the first target in roster order. Pending pulses finish even if the parent
begins its tail or early visual teardown. No terrain clipping or flying-bullet
consumption has been inferred: these source parent/pulse update bodies contain no
such test.

Normal stop reads live owner state0 and starts tail from current beam scale.
The tail subtracts maxscale/10 each update and produces no new pulses. Death or
form replacement also forces the tail, using the prior owner-scaled +c0 rather
than the normal stop branch's explicit +c0=148 assignment. The current host retains a scale-zero
observation for one last pending sweep if necessary, then removes the emitter.

## Presentation

Renderer consumes detached observations only. Draw `800e2298` recomputes the owner
attachment independently of collision auto-aim, uniformly scales by beam scale,
and multiplies XY by parity `[1,1.2000000476837158]` (`80433bc0`). Tail draw shrinks
uniformly without alpha fade, despite the unrelated retained actor +60 channel.
Global bank84 is used, not an owner-local model84 or generic bolt; effect -1 means
no fabricated launch effect. Animated skeletal matrices are unavailable: both
runtime and presentation use the decoded static joint plus root yaw. Body/part
pitch is computed for actor aiming but not fabricated into the static bind matrix.

## Explicit remaining approximations

- Target roots and the existing host body sphere replace original articulated
  target collision centers. Capsule overlap uses JS vector arithmetic; it is not
  PPC floating-point or complete source pair-dispatch parity.
- The shared damage/reaction adapter remains in use. It does not model the
  original defensive collision-descriptor gate at victim+1da mask0x02
  (chunk0003:7799-7827,7946-7953). This is not a generic first-hit-per-frame
  latch: ordinary damage does not set it. Distinct overlapping pulses must not
  be suppressed merely because another pulse hit in the same frame. Defensive
  descriptor/status interactions remain unverified; no arbitrary beam cooldown
  hides that gap. See `collision-hit-gate-audit-2026-11-12.md`.
- Destroyed owners normally remain in the battle roster for attribution. A truly
  missing owner uses the existing orphan-attacker damage path with record HP3,
  not full original attacker state. Independent pulses are not silently dropped.
- Audio loop14/release cue195 (c3) and effect allocator pressure are not integrated.
- Original source may combine body/part animation pose, per-frame target anchor
  eligibility, and object-slot reuse differently; no claim of complete game parity.

## Validation

`beamBattle.selftest.ts` exercises actual Battle inputs, exact command admission,
release/recovery clocks, ammo alias and debt, edge extension/budget, sustained
emission and tail, target retention, pulse sphere/sweep/multiple victims, interruption,
and neighboring-family isolation. Scene selfcheck exercises global84 scale/basis,
parity/tail and disposal without advancing gameplay during render.

Final local checks passed: TypeScript, full combat lifecycle, ROM checks, Beam /
Revolver / Powered / Gatling renderer checks, all remaining contributor stages,
and game build. The contributor aggregate stopped at the three existing missing
sparse-checkout HUD images; later stages were run separately. Matching negative
controls passed 52 tests; oracle passed 81 with zero failures and one expected
private-capture skip. Docs build remains blocked locally by absent
`research/asset-inventory/borg-assets.json`. Browser GPU and audible validation
were not performed; these checks do not establish complete original-game parity.
