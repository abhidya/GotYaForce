# G RED-family ordinary B projectile restoration

## Reachable failure and scope

Actual fresh ranged B for RED (`pl0615`), NEO (`pl0629`) and BLACK (`pl062a`)
correctly calls `800c3be0` rows43/101/102. Before this lane, the generic fallback
instead made all three a short-lived falling bullet: life6, speed50 and drop3.
The tested shots disappeared before reaching even a target500 units away.

This lane restores only those exact family/row pairs. Ordinary actor firing
clock, repeat/latch behavior and posture admission remain legacy; it is not a
claim that the complete normal-shot action is now 1:1.

## Original child contract

`research/decomp/ghidra-export/chunk_0020.c` contains allocation `800c3be0`,
initialization `800c3d2c`, flight `800c4088`, retirement `800c426c` and homing
`800c4540`. Fresh original DOL table80303138 has stride0x44. RED43 and BLACK102
are identical; NEO101 differs in local muzzleX and maximum visual length.

- Life300; speed80, acceleration0.5 and maximum160. No gravity. Initialization
  places the head one unit beyond the muzzle; motion starts on a later update.
- HIT0 maps to record15 for all three: sphere radius20, damage record0/HP20,
  flags1 and window0..−2. Collision scale is width40 divided by
  36.959999084472656, multiplied by owner modelScale. The elongated visual is
  not an elongated damage capsule.
- Local muzzle offset is [−106.800003,−3.5999999,30] for RED/BLACK and
  [−196.800003,−3.5999999,30] for NEO, relative to joint7. The freshly inspected
  static bind translation is [−106.55999755859375,166.96005249023438,
  0.000041961669921875] with identity basis for all three. This does not provide
  the animated joint transform.
- Maximum visual length1000 for RED/BLACK and500 for NEO; width40. Muzzle
  effect8 and sound185 are source identities, not permission to invent assets.
- Flight moves before incrementing speed. Retained homing turns at most
  0.349999994 degrees per update, clears within20 units or behind velocity,
  and requires captured owner d0 bit4. A selected target alone is insufficient.
- Tracking capture is source6ae60/6bda8: validated selected target within inclusive
  3D7000 units from actor root to target HIT center grants bit4. Fresh descriptor
  +80/+84 values are7000/7000 for all three, mapped to actor814/818; there is no
  model-scale multiplier. Nonzero actor6b8 clears the snapshot. Initial aim can
  still occur outside tracking range. Host centers and capture timing remain
  approximations.
- Contact maskA2 or terrain disables damage and retracts the tail by current
  speed per update. Bounds/expiry disables damage, keeps moving with the
  retained velocity and shrinks width by f32(0.9) until at most f32(0.05).
- Owner state greater than1 or a form mismatch before retirement disables HIT
  and visibility and dispatches immediate cleanup. There is no impact child.
- Helpers834b0/83524 consume incoming scale/speed modifiers. They are not
  ordinary projectile growth; absent consumers must not be fabricated.

## Target visibility admission

Final source review exposed an existing bridge omission. Original6a104 clears
the attacker3e5 bit from all six target5e6 masks and re-adds it to captured
targetcc when target83 is zero, before cues/ammo. The restoration binds this
only for ordinary action0/variant0 of the three families and preserves other
owners' bits. Initial admission deliberately does not use the high-control-bit
restriction belonging to repeat refresh6bf80.

Child initialization6ec84 then requires target83 nonzero or target5e6 containing
the owner bit. Rejection clears targeting and uses forward aim. Both positive
and negative cases are tested; no default visibility bit is invented.

## Fidelity boundaries

Static attachment, host target centers/eligibility, terrain, attraction83714,
notification833a4, allocator update scheduling and floating-point/trigonometric
implementation remain explicit adapter limits. Rendering is procedural, not
original model/texture parity. Source-backed child behavior does not repair the
legacy actor clock. No original assets were copied or uploaded, and publication
remains paused.

## Verification

Real fresh-B tests cover all nine family/range combinations at500/1000/2000,
initial one-unit placement, life300, speed80 then acceleration, per-family trail
caps versus fixed sphere size, non-damaging visual trails, contact and expiry
tails, owner death/form/action boundaries, empty ammo, real mine receivers, and
unrelated Powered/Beam ordinary-B exclusions. Additional pure adapter tests cover
inclusive7000 across model scales, captured target retention, out-of-range
initial aim,6b8 suppression, visibility and static attachment coordinates.

Two older mine tests injected generic projectile fields that the new source
state owns. Their fixtures now position real mines on the source head path;
HP1 damage, deferred explosion/refund and same-pass registration assertions
remain intact. No gameplay check was weakened to hide the integration change.

The procedural renderer check covers family trail lengths, width, head anchoring,
retirement visibility, paused-clock immutability and resource disposal. Source
review approved the final visibility correction. Final `verify:contributor` passed, including policy, TypeScript, UI/renderer,
ROM/full combat lifecycle, importer and production build (20.06 seconds). The
existing large-bundle warning remains. No original-console replay or actual
browser screenshot is claimed.
