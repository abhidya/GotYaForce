# G BLACK airborne B

Local continuation from `3b07aaef`; publication remains paused. No original assets
are added. NEO airborne B remains excluded pending its separate continuation audit.

## Original evidence

BLACK action1/variant4 table803655f4 selects wrapper8018e170 and the already tested
178394 five-phase engine with config80365760. Its seed is24, range300, pursuit20,
brake0, carryf32(.95), speed60, transition.25 and dampingf32(.9). Descriptor AC2560,
AE3072, gravity−1 and ranges1000/1200/1300 match the available adapter; the aim joint
selected by family descriptor+10 is3. Actual jump then close B selects original
row80365dc8 `[45,3,1,4]`, retaining type1 and subtype4 separately.

Stream24 at80366e74 arms HIT6/status25/255 and plays metadata3/21, motion1/22,
mode1 blend5 (total6), start0/rate retained. Original AOBJ end50 matches the existing
51-sample,60fps clip. Startup contact/aux0, flags6e8=2/6e9=0, dash0/face1 and709bit1.
Gates:13 contact1;14 contact0/6e9=1;19 dash−1/face0;23 6e9=2;27 contact−1,
6e8=3/6e9=0/709clear1f; terminal waits for animation end. There is no negative
auxiliary byte, continuation or indirect callback. RED's frame15 dash24 reset
must not be inherited.

HIT6 remaps to records6 and19, both flags1, damage7/HP50, refresh0:
- Record6: shape2, bone7, active15..19, offset[0,0,140], extent[0,0,140], radius50.
- Record19: shape0, bone1, active only17, offset[0,−40,50], sphere radius120.

Original3b170 (chunk0004:5784–5787) transforms offset−extent and offset+extent
through the animated bone matrix. Static capsule endpoints are therefore local
[0,0,0] and[0,0,280], with radius50*owner+c0. The host can preserve this capsule
shape while using root/yaw instead of the unavailable bone transform. Original
3b304 additionally incorporates swept motion; the instantaneous adapter does not.
The sphere's center likewise uses root/yaw instead of animated bone1.

Activation of record19 at17 renews the shared actor26c identity while record6 is
still active. Both volumes must share the renewed victim history, allowing a new
wave but not two simultaneous hits on one victim. RED's disjoint15..16/19..21
windows must retain their previous two-wave behavior.

## Explicit scope boundaries

NEO uses config8036577c/seed33 and negative auxiliary contact values permitting
retap continuation to34. It is not enabled by adding a single BLACK profile.
BLACK post18cf54 consumes6e9 at14/23 into AF1/FF and sound7f; presentation/equipment
shadows and these effects remain unbound, alongside92dcc FX/RNG. Source geometry,
terrain, nonunit-dt yaw, inherited cooldown and watchdog limitations remain.

Implementation and verification are complete locally. No original-console parity,
browser visual comparison, publication or deployment is claimed.

## Implementation and focused checks

Only exact airborne BLACK action1/v4 is newly admitted. RED keeps its existing
profile; NEO remains excluded. The pure five-phase engine is unchanged. Profile
selection supplies BLACK's separate gates, animation, HIT records and range300.
Collision uses the verified static capsule/sphere dimensions with the explicit
root/yaw transform approximation. Activation is processed for the full HIT list
before collision, sharing a fresh history when frame17 activates record19.

Independent real-input tests pass for BLACK admission, conditional clocks,
range300 pursuit, brake0, authored gravity and landing gates, source sampling,
completion/death and neighboring isolation. Capsule-only, sphere-only and overlap
fixtures verify wave15/17 renewal and one contact per shared wave; vertical and
outside-volume negatives remain misses. Survival/immunity resets and geometry,
range and floor fixtures are labeled. RED's prior tests pass unchanged except its
obsolete BLACK exclusion now checks the distinct BLACK profile; NEO stays absent.
Independent BLACK clock traces pass at dt1 and.5, including no RED positive dash.

The explicit equipment mode3 is tracked, but the FF-resolved equipment-default
shadow remains null/unbound rather than requiring a new unverified value. No
functional behavior depends on it. AF/sound/effect consumers remain omitted.

## Final checkpoint

Full `verify:contributor` passes on frozen code: repository policy, TypeScript,
frontend/session/input/Challenge gates, renderer checks including BLACK motion1/22,
ROM and all combat lifecycle regressions, importer tests and production build.
Only the existing bundle-size warning remains. Independent source review found no
blocking discrepancy in config, gates, static geometry or shared hit identity.
No original assets were added, and no publication or deployment was attempted.
