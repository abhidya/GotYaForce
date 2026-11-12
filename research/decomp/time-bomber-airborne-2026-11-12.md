# Time Bomber airborne X: reconstructed source evidence

Reconstructed summary, not the original report's byte identity. Original numeric facts were inspected on the authorized GG4E08 source; code/tests are revalidated separately.

Actual jump→X command80336218 is[45,1,0,3]. Variant3 shares80130c5c/phase table80335ce8:80130c98,80130d34,80130e50. It owns mask1/part0; lower-body locomotion continues. Group2 slot18 aliases803351e4, with END20/wait8/END9. Control10 selects15;20 overrides12. These stream aliases do not prove arbitrary host directional-state admission.

Source8006dee8 accepts relative yaw within±0x4800, clamps aim to±0x4000 and approaches by fixed0x800 per call. A missing target resolves to current heading, so targetless forward aim is valid. Out-of-cone windup redispatches ground variant0 or airborne variant4. Redispatch recaptures the currently selected target through8006a104, unlike normal retained-target windup. Recovery clears action bits and redispatches the current upper-body cue, rather than substituting a generic idle return.

Air fallback command80336220 is[45,3,0,4]. Phases80335cf4 select80131080/80131184/80130e50/801312b4. Group2 slot21 uses80335220 and tail80335240. Initial opcode01 mode1 advances animation during its4+1 blend and does not use opcode0d's immediate update. Tail group0 slot14 has a16-tick blend but explicit terminal frame15, not another15-frame wait afterwards.

Fallback owns source movement once per frame, projected on lockYaw+5ae, not target-facing+5ac. Release sets descriptor gravity6c=-0.699999988079071, not vertical velocity. Landing seeds16+dt on actor694; the scoped source timer decreases before input outside action ownership. A host floor clamp substitutes for an unavailable source surface-normal probe.

The bridge's part0 path composes existing host locomotion and restores that state on completion/interruption. This preserves playable movement but is not original lower-state execution. Tests exercise actual jump/input, paired trajectories, target changes, fallback/deferred initialization, one movement update, ammo, landing cooldown and interruption. Synthetic part-mask/cone fixtures supplement these tests; they are not console replay. Animated attachment, blending, source collision and visual parity remain incomplete.
