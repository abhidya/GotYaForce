# Switching Ninja ordinary X: delayed field and deferred position exchange

Date: 2026-11-12. Scope begins from the inert, independently tested field/stream checkpoint `74a8682b`. This integration uses the checked-in decompilation and existing decoded numeric command, animation, HIT, family damage and ammunition tables. It does not publish original asset files, restart the retired wasm-unit driver, or establish instruction-level matching. The ordinary action now causes a real delayed exchange of positions rather than a generic radial burst or an inert visual.

## Admitted input and actor action

Only `pl0009` fresh ordinary X is admitted: command `8033ea78=[44,3,2,0]` on ground and `8033eab8=[45,3,2,4]` after an actual jump. The constructor is `801456d4`, command structure `8033e7c8`, root `8033eaf0`. Other contextual variants, other Ninja families and charged moves are not promoted by this change. Holding X through recovery or interruption does not invent a second press. Empty ammunition rejects entry; failed allocation at release advances to recovery without a payload. A source-owned failure cannot fall back to a generic AoE.

`ghidra-export/chunk_0038.c:900–1011` contains `147180/147280/14734c`:

1. Phase0 clears motion scalars and pose accumulators, aims with `6d144(c1)`, computes `motion=f32(f32(position−own5e8)×f32(.95))`, adds the motion to position, then probes `677b0`. It selects stream g4s4 or g4s5 from control40 and does not fall through.
2. Phase1 ticks the stream, aims, multiplies motion by f32(.95), adds it to position and probes. Authored positive part0 advances the actor phase and calls `6dbe0(actor,2,1,1)`. Only successful allocation and borg number9 call child constructor `1e29fc(owner,0)`. Motion length greater than3 produces the existing source afterimage.
3. Phase2 ticks, calls primary physics `67310(1,lockYaw)`, and probes. A landed negative part0 has priority and dispatches upper cue7. Otherwise completed part0 triggers ground idle or air return. Both exits clear action bits/housekeeping and set cooldown `f32(8+dt)`. There is no artificial20-frame B cooldown for this source action.

`switchingX.ts` binds those fields and callbacks. The ordinary bridge is responsible for input, own-position history, family dispatch, live capture and source animation epochs. Actor terrain probes remain the existing host swept-triangle approximation, not an original stage collision port.

## Stream and resource identities

Original streams g4s4=`8033dd96`, g4s5=`8033ddc6`. Metadata descriptors4/2 and4/3 map to MOT4/0 (end80) and MOT4/1 (end78). The actor callback passes **metadata4/2 or4/3**, not the resulting MOT indices. Play uses mode1, blend2, start0. Waits inspect the pre-advance animation clock. Absolute frame25 supplies the sole positive part0 release. The pure clock observes release on its28th update, ground completion83, air recovery descriptor0/14 on81 and terminal completion97. The Battle admission dispatch starts the stream without ticking it, so the corresponding release occurs on the29th input frame when entry is counted as1. Recovery0/14 maps to MOT0/24, end1, with blend15.

The X stat segment is mapped to source cell2, with browser cell1/HUD an alias: maximum1, refill type0, period180. `hasSourceXAmmo(pl0009)` selects the already implemented source all-at-once refill debt rather than a generic decrement. Admission checks availability, while the authored release performs one mode1 debit. Shared refill remains separate from animation time and honors its existing status/burst/pause rules.

## Child construction, placement and field lifetime

Source `ghidra-export/chunk_0058.c:5616–5940`: allocator `1e29fc`; owner validity `84000`; INIT `1e2b4c`; update `1e2cdc`; retire/free `1e2f58/1e2f94`; renderer `1e2fb4`.

The child stores owner/form identity, scales and allocation-time d0. The host computes d0bit4 from the retained capture's root-center distance5500. INIT deliberately samples the owner's **current retained c8 identity**, not the child's copied pointer or newly selected lock, and combines that with the child's allocation-time d0bit4:

- Non-null owner c8 plus captured bit4 places the field at that target's current center. INIT has no dead-target check and does not call projectile aim initialization6ec84.
- Otherwise place at owner root plus forward×2000, then clamp only X and Z to stage limits. The field does not fly, seek, ground-snap, bounce, or spawn a second child.

Original target center+64 and forward matrix are approximated by the host root and yaw. Position is sampled once at INIT and remains stationary thereafter.

INIT sets timer60, visible1, visual scale1, yaw0 and pitch−32768, then returns without decrement. Sixty subsequent dispatches decrement60→0. The61st tries `8ac80(HIT12)`; success sets subphase1, timer25 and initial inner/outer parameters. Thus there are25 registered collision passes, including activation, before retirement. A failed registration stays warning/retryable in the pure engine; production assumes allocation succeeds. Warning yaw and pitch advance by BAM0x444 per dispatch; X/Z visual scale is f32(.5×cos(pitch)+1.5). Source SDK cosine and matrix precision are not claimed.

On an accepted previous-pass contact, the following child update sets flags272bit1, disabling subsequent attack registration. It does not stop later victims in the **current** collision pass. Inner/outer counters keep running through the visible active duration. Expiry hides/unregisters, then release and free are separate dispatches. Owner death or a different active form invalidates pending/active fields before their next collision pass. Owner action interruption alone does not erase a launched field.

## HIT and family damage

Existing `attackHitTables.json` binds pl0009 HIT12 to record13: shape2, bone0, local offset[0,0,0], halfExtent[0,9150,0], radius270, collisionFlags1, damageRecordIndex12, open authored end. The production adapter uses a stationary vertical segment from root to root+[0,9150×collisionScale,0], radius270×collisionScale, against the host body-center/body-radius approximation. It does not use a giant sphere or the changing visual scale as collision geometry.

Family table `8033eb08` record12 supplies HP30, flagsA0x11 (including the defining0x10 exchange effect), refresh0 and the existing decoded gauge/reaction data. HP calculation, status application, gauge accumulation, telemetry and burst credit use the existing combat resolver. Valid same-pass additional victims may take ordinary damage even though the owner's outgoing reservation can be made only once. Same-owner reception, target registration, ordinary invincibility, family immunityA0x10 and the existing burst/team gates remain explicit. No impact explosion or secondary projectile is fabricated.

## Exchange staging and forced movement

The defining effect is not a synchronous assignment of positions. Original `chunk_0003.c:7685–7714` stages vectors; all active-borg/object/secondary collision passes complete before `chunk_0003.c:6214–6302` dispatches forced movement.

A valid exchange requires actor class83==0 on owner and victim, victim59cbit10 clear, owner outgoing1d9bit4 clear, and victim incoming1dabit4 clear. This is **directional** deduplication, not a single 'already exchanged' flag. A→B then B→C is allowed; B's single destination slot is overwritten with C's original position. A→B then A→C, or C→B, is blocked. Reservations reset for each collision pass.

Destinations snapshot positions before damage/reaction dispatch:

- owner destination = victim xyz, with Y += victim support6d0 − owner support6d0;
- victim destination = owner xyz, with Y += owner support6d0 − victim support6d0.

The runtime support seam defaults0 because animated original support anchors are not present. `sourceSupportHeight6d0` allows explicit geometry fixtures. This is not a claim that all borgs have equal original supports.

After every projectile has resolved, each living participant independently starts `6ab04(destination,kind2)`. A participant killed in the same pass does not move; the surviving participant can still move to its staged destination. An existing moveKind7c9 rejects only that participant. Reservations are not reassigned after rejection. Protection is activated at this point, not inside the hit loop, preserving same-pass collisions.

`6ab04` (`chunk_0009.c:1056–1090`) sets moveKind2, control1000, clears71b, sets272=ffff, saves the old main/sub cues and selects cue0x23 without resetting phase registers. The original `64548` (`chunk_0008.c:1734–1784`) runs once on each **next** normal actor update, independently of animation dt:

1. phase0→1, timer2, protect;
2. timer1;
3. phase1→2, timer2, move;
4. timer1;
5. clear kind/1000/protection and finish. If source control lowbits are zero, restore saved cues and suspended phase/stream. Otherwise choose the original action-cancel/idle-return branch.

`3f7d4` (`chunk_0004.c:8393–8503`) clamps destination XZ to stage outer limits. Kind2 copies Y unchanged; wall and floor placement checks belong to kind1 and must not be borrowed. It copies final position into both previous-position2c and own-motion-history5e8. The port mirrors these histories and does not reset facing or velocity at activation or relocation.

Incoming exchange replaces the normal hurt reaction. Its collision damage, status writes, gauges and accounting remain, but velocity overwrite, stagger entry, down-gauge reset and balance-break invincibility must not be invented by that reaction. The bounded resolver defers incoming reactions after reservation and restores the pre-pass incoming motion/state when committing; later ordinary contacts still resolve damage before protection starts. A resisted or otherwise unreserved additional victim retains its normal reaction.

## Explicit remaining boundaries

- Generic Battle ordering is still actor movement/attacks followed by child/projectile passes. This is not the original global scheduler or complete contact-class pipeline.
- Original postcollision status-slot/object-reaction priorities and interactions with an ordinary hurt reaction that was already applied earlier in the host pass are not fully represented. The targeted incoming reservation path is deferred; no global damage-pipeline rewrite is claimed.
- Source661's original ground/air class selector is approximated by the host grounded flag at forced-move cancellation. Zero-lowbit suspended actions preserve their ROM cues, phases and stream in the isolated forced-move adapter. The inherited host bridge still treats zero lowbits as completed; helper tests do not establish end-to-end resumption parity.
- Target center, support heights, body geometry, yaw matrix, SDK normalization/cosine and stage probing remain the stated bounded adapters. No dynamic original joint transforms, source clipping or instruction-equivalent floating point is claimed.
- The field renderer reuses existing checked-in bank150/151/152 meshes and materials. It samples source yaw, scale and alpha without a render-time simulation clock. This static adapter is not proof of GX or original animation equivalence. No original texture/model/animation files are added or uploaded by this change.
- Only ordinary pl0009 X is promoted. Other actor variants, charged moves and unrelated legacy family handlers retain their prior status.

## Validation

- `switchingX.selftest.ts`: source own-history f32 motion, ground/air metadata/stream selection, absolute release and single cell2 debit, denied allocation without fake payload.
- `switchingXStream.selftest.ts`: release28, original clip endpoints, air recovery and stable completion.
- `switchingField.selftest.ts`: INIT/no-fallthrough,60+61 warning boundary, retry,25 collision passes, prior-contact registration suppression, immutable observations, expiry and owner invalidation.
- `switchingXBattle.selftest.ts`: actual ground/air input, ammunition/refill/edges, source animation, natural deferred exchange, support adjustment/history, same-pass multi-victim handling, target capture, miss lifetime, interruption/death/resistance/participant guards and family isolation.
- `romCollision.selftest.ts`: replaces the stale assertion that pl0009 is an unadmitted non-probing legacy path with actual X entry/windup source677b0 calls.
- Combat lifecycle passed during integration; final contributor, renderer and build results are owned by the aggregate validation and should be reported for the final committed revision.
