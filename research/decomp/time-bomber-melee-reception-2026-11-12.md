# G RED source-owned melee reception by Time Bomber mines

Local follow-up to `6d696130`; no publication, original asset upload, or global
collision-engine synchronization is part of this lane.

## Supported source join and real input

G RED `pl0615` ground opener group3/slot0 resolves to HITkind1, finite
frames10–12, damage record2: HP30, flagsA1/flagsB0. The single attack record
has bone1, offset[0,0,70], extents[100,20,0], radius1. Its derived maximum
reach is170. This is a decoded action/script/HIT join, not a lowest-kind guess.

A fresh close B enters the source-owned action1 (`createSharedMeleeGRed`,
`80177dd8`), schedules group3/slot0 and actually arms HIT1. The bridge labels
this `charge_shot`/`special`, but those host labels do not mean action3's charge
handler is executing. Tests must preserve the driver and exercise fresh B.

NEO G RED is excluded: its decoded opener is group3/slot25, whereas the current
shared bridge path schedules slot0. Generic fallback melee, combo continuation,
air attacks, unbounded windows, and other source-special melee are also excluded.
This lane does not change action dispatch or correct unrelated animation labels.

## Scheduling

An active bridge HIT record emits a frame-local sample with stable per-arming
identity. Battle resolves it against mines only after the child lifecycle
update. Immediate durability mutation in actor work would make a mine explode
a frame too soon. Source `8002db58`/`8002fd7c` uses registered collision lists
and does not retroactively cancel registered contacts because later collisions
changed HP/action state. Host actor-step capture is staging, not literal
original registration timing.

## Fidelity limits

Source `8008a65c` uses actor+1cdc animation time and an animation-ID snapshot
(`chunk_0013.c` 1125–1249). The existing bridge instead counts integer updates
since HIT arming. The tested armed-HIT ticks10–12 are host timing, not verified console
timing; no equivalence of blend, start frame, rate or dt is claimed. The receiver uses a declared host forward/XZ/vertical volume with
derived maximum reach, not exact animated HIT geometry. Existing fighter hit
geometry and damage behavior are unchanged. Static mine attachments and bounded
receiver owner/team/burst gates remain as documented in the mine gameplay
report. Reflections, linked-owner rules and special-status effects are incomplete.
Per-arming identity and deferred mine retirement do not establish console parity.

## Validation

Four independent scenario groups pass:
- Fresh real B creates the source-owned G RED attack; multiple input-created mines
  are damaged in either mine-list order. Detonation and refund occur on the
  subsequent child updates, not during actor processing.
- Observed HIT arming anchors the boundary checks: ticks10,11,12 connect;
  tick9 and recovery ticks13/18 do not. Rear, high and distant fixtures miss.
- A clearly labeled zero-HP sample fixture preserves a mine to check same-arm
  deduplication and fresh-arm identity. Natural HP30/HP1 destruction is tested
  separately. No alternate driver or fabricated attack-state admission is used.
- NEO G RED, Sword Knight, actual airborne admission and later generic held-B
  fallback do not acquire unsupported receiving behavior.

Focused tests, combat typecheck and diff check pass. Full `verify:contributor`
passes, including all lifecycle tests and production build. Final log:
`melee-mine-contributor-final-2.log` in the reconstruction workspace parent.
The earlier boundary-counting fixture failure is superseded. Existing large-bundle
warning remains. Browser screenshots and original console comparisons are
outstanding. No remote publication or deployment was attempted.
