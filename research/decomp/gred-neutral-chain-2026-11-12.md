# G RED neutral melee chain

Local continuation from e5f30611. Publication remains paused.

## Verified original route and host mismatch

A real close B press resolves action1/variant0, but the prior host starts only
slot0 and retires before original animation completion. Its legacy scratch fields
receive held B rather than a fresh press, lack accepted-contact feedback and do
not consume the signed stream aux rearm flags. Real hit plus release/repress did
not reach slot1. This is a functional chain gap, not merely a cosmetic slot label.

Original wrapper8018de34 shifts signed18da once then calls engine80177dd8 with
config80365634: seed0, range150, timer20, f32(.95), both callbacks null. The chain
is0→1→2. Slot1's aux is−1, unlike NEO slot26's−2; even a cleared low bit would not
justify a NEO finisher redirect when the callback is null. Slot2 ends with aux0.

## Streams, clocks and HIT records

Original data was inspected in place; no disc assets are added by this lane.
Loose HIT AFS1068 agrees with PZZ587/member2; motion AFS2791 was checked.

- Slot0 at803666d8: HIT1/status0, g3s0, mode1/blend5/start0/rate0,
  initial contact0/aux0, dash24, face1; frame5 sets contact1;
  frame10 sets contact−1/aux−1 and clears dash/face/contact flags.
- Slot1 at80366720: HIT2/status0, g3s1, mode2/blend4/start0/rate0;
  otherwise the same pattern with its second gate at13 and aux−1.
- Slot2 at803668b0: opcode0c sets flags57b bit40; HIT20/status25,
  g3s15 mode1/blend5/start0/rate0, contact1/aux0, dash32/face1;
  frame12 clears dash/face; frame19 contact−1/aux0 clears contact flags.

All three initially set contact shadow709 bit1 and terminate with mode1/−1.
All op02 flags6e8/6e9 are0. There are no opcode09/11 child callbacks or recovery
animation. Original motion bank1 slots1/2/16 have raw ends27/35/35, AOBJflags0;
g3s0/1/15 descriptors clear looping. Ratebyte0 preserves inherited rate; host
admission is bounded to rate1. Positive mode2 waits are absolute animation frames.

HIT1 remaps **hit record1, damage row2**, active10..12, shape0/bone1/flags1,
offset[0,0,70], extent[100,20,0]. HIT2 remaps record2/damage3, active12..15,
shape0/bone1/flags1, offset[0,0,100], extent[100,20,20]. HIT20 maps records38/29,
both damage25 and active8..11, shape0/bone0/flags1, offsets[0,70,70] and
[0,140,70], extent[80,0,0]. The simultaneous third-hit records share one attack
identity and must not independently double-hit a victim.

Status25 is not a proven defender debuff. Original opcode8004c6b4 writes actor
43d=0x81,6f8=25,6f9=FF only when signed43d<3 and previous6f8 differs, on part mask1.
Its downstream consumer is not established here. Preserve metadata/shadow without
inventing status gameplay. Damage row25 itself has HP30, flagsA1 and refresh0;
actual HP still goes through the existing damage calculation.

## Scoped mine timing migration

The existing mine receiver remains limited to the real G RED opener HIT1/damage2.
Its window must follow source animation10..12, not elapsed updates since arming.
Tests should preserve delayed mine retirement, per-activation identity, order
independence and geometry controls while replacing incorrect arm+10 assertions.
No new mine reception from later swings is inferred by this lane.

## Limits and verification status

Implementation and independent tests are in progress. Host root/envelope collision,
terrain and target adapters are not original animated geometry; fixed-rate and
scheduler limitations remain. No original-console replay or live deployment is
claimed. Full verification will be recorded after the runtime is frozen.

## Implemented local scope and focused verification

Fresh grounded pl0615 action1/variant0 now uses the admitted source chain engine,
slot-specific configuration and clock, accepted-contact latch and fresh B edges.
Other variants remain on their previous routes. Third-hit paired records use the
shared activation identity. Opener-only mine samples use animation10..12 with
stable activation IDs and deferred reception after child updates.

Independent pure-clock and actual Battle tests pass. Real input progresses0→1→2,
observes animations3/0,3/1,3/15 and forwards HIT/status/arg tuples1/0/255,
2/0/255 and20/25/255. Held input, missed/invincible targets and stick-only input
do not substitute for the required hit and fresh press. Terminal/recovery and
interruption are checked. No fourth swing or NEO variant6 is inferred.

Mine regression tests now read the admitted animation clock instead of assuming
arm+10. Longer source startup required keeping a live mine away until the stated
active-frame geometry fixture; otherwise it legitimately interrupted the attacker.
Negative geometry tests explicitly prove the active window was reached, avoiding
a vacuous pass caused by early interruption. Delayed explosion/refund, activation
identity and reversed mine ordering remain covered.

A narrow raw-shadow correction also preserves709 bit1/set and1f/clear for NEO's
shared slot25/REDslot0 stream and its slot26 counterpart. There is no new gameplay
consumer or visual-effect claim from that tracking fix. Status25/255 forwarding
does not bind the original conditional43d/6f8/6f9 storage or downstream consumer.
Original geometry, target/floor adapters, inherited rate1 and console comparison
remain limitations. The full contributor check is running at this checkpoint.

## Final local checkpoint

Full `verify:contributor` completed successfully on the frozen implementation:
repository policy, TypeScript, frontend/session/input/pause/Challenge gates,
renderer/resource suites, ROM and full combat lifecycle, importer checks and
production Vite build. Six independent RED clock traces cover dt1/.5; real-input
RED chain and source-frame mine suites pass alongside NEO/G BLACK regressions.
Only the existing production bundle-size warning remains. No assets were added,
and nothing was published or deployed. No defensible whole-game completion
percentage follows from this single verified three-swing lane.
