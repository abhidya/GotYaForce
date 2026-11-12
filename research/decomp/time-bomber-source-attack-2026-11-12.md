# Time Bomber ground X: reconstructed source evidence

This evidence summary was reconstructed after the earlier workspace became inaccessible. It is not a byte-identical recovery of that report. No original game assets are included. Source numeric facts below come from the authorized GG4E08 disc inspection; regenerated code and tests require fresh validation.

## Ground neutral action

Root80130788/action801307c4/variant0 selects80130844 and phase table80335cdc:8013088c initialization,801309b8 windup,801313bc release,80130ad0 recovery. Mask15 uses group2 slot12, stream803351e4. Its initial animation metadata31/30/32 resolves to original MOT slots1/0/2, END20; tail35/34/36 resolves to7/6/8, END9. The relative wait is8 frames. Original END20/9 must not be replaced by inclusive baked sample counts21/10.

Opcode0d mode6 uses override4+1 blend frames, with an immediate parser update. At dt1 an aligned shot releases on input frame4. The source facing helper8006d0dc uses descriptorAE=0x0c00 (3072); the windup timer20 decrements only while facing is not ready. Initialization and recovery carry previous own displacement by f32(0.95), not target displacement. Release consumes one source cell2 and calls800fe668(actor,2,2); it does not emit a repeated barrage. The HUD X cell aliases source cell2, max3/refill300.

## Projectile and explosion

Type2 row8031efc0 defines HIT17, explosion19, lifetime300, steering interval4, durability1, turn3 degrees, target-surface release range200, initial speed20, maximum60 and acceleration8. Construction and initialization do not move or age. Flight updates accelerate before movement. Lifetime1 moves to0; the next update retires without explosion. Contact or terrain detonates; owner death/form mismatch and bounds retire silently.

The captured target identity is stable. Admission range6000 controls ongoing tracking, not initial aim. Launch/flight positions refresh against that captured actor, without reacquisition. Host target radius and collision geometry remain approximations.

Attachment row8031ef68 is owner-local model3, joint7, local offset[-90,-6,31.610000610351562]. The verified static joint7 bind gives the approximate launch offset[-178.58972215652508,130.12603759765625,31.60999780971141]. This is not an animated attachment implementation.

Explosion19 uses common HIT179/remap246/damage26, HP20, model22 followed by23 and ring18. Row802da364 has hold4, scale0.01→1.25, growth0.1 with limits0.02..9, acceleration0 and cue12. Damage26 has down100, balance100, combo50, strength0, impact0, reactionFlags2, variant4, direction1, flagsA0x60, flagsB0, pitch32, rehit0. The reused Gatling explosion clock is structural reuse, not reuse of Gatling damage.

## Verification boundary

Actual-input tests cover neutral admission, firing/recovery clocks, facing delay, one-charge debt/refill, hold/repress/empty, target capture, range boundaries, terrain/contact explosions and owner retirement. Pure projectile tests cover frame math. Renderer tests cover source bank identity, curves, pause, replacement and disposal. Static muzzle, centered animation rather than full blends, host collision, actor6b8 inhibition and original-console/visual comparison remain unfinished. No complete 1:1 claim follows from these checks.
