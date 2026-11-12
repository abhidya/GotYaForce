# Time Bomber isolated mine lifecycle recovery

This checkpoint reconstructs the tested pure lifecycle only. It does not connect a new playable B attack, alter current ammo behavior or certify original-console parity.

Original801304b8 is a post-action callback driven by raw B press edge5bc&0x200. It allocates cell0, calls800e058c(owner,2,10), and sets shared694 to4+dt even when empty.694 decreases only outside low-bit action ownership; X admission resets it. Source cell0 has initial/max10,type2,param0: no passive refill. Each mine retirement returns one current owner cell0 unit; same-actor form changes still refund current cell0, while another actor must not receive it.

Type2 at8031708c selects HIT15, durability1, lifetime180+(byteRNG800055fc&63), direction joint1/+Z, initial speed5, accelerationf32(-0.1), explosion19. Appearance10 at80317010 uses owner-local model3 and animated joint8. Animated pose, terrain/collision and source sine are injected seams, not fabricated original assets.

Phases are800e075c initialization,800e0a30 active,800e0db8 refund,800e0dec free. Initialization does not age or move. Active priority is previous contact, bounds, durability, decremented lifetime, motion,83714 silent collision,84170 wall detonation. Drift decelerates before moving and stops at the51st f32 update. Stop draws one further RNG byte for signed phase(byte&15)<<12. Subsequent bob adds0x180, computes centerY+40sin, then lowers centerY by0.125 when above terrain+150 without clamping. Normal retirement refunds next child update and frees one update later; owner invalidation before dispatch refunds immediately, silently.

Original frame80029434 runs actors before child group8: a new mine initializes that same frame, then first moves/ages next frame. Contact flags are written in the later collision pass, so contact explosion occurs next child update. HIT15 maps to record8(flags3,damage9,extent20): direct HP30 and a damageable receiver with durability1. Explosion19 has its independent HP20 record and attack ID. Neither guaranteed50 damage nor copying the mine victim cache is justified.

The recovered pure module tests RNG counts/lifetime endpoints180 and243, deferred initialization pose, deceleration, bob/floor ordering, signed wrap, termination priority and exactly-once refund/free events. Arithmetic is a semantic model, not a PowerPC instruction/FMA oracle. Initialization HIT allocation failure needs an explicit future adapter path; this module does not allocate HIT objects.

The gameplay adapter that was in progress when the workspace disappeared was uncommitted and had not passed its new tests. It is deliberately not part of this reconstructed baseline. Direct/receiving collision, owner gates, shared cooldown and resource-return wiring must be separately restored, reviewed and tested before a playable-B claim.
