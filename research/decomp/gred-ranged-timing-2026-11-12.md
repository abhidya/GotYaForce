# G RED-family ordinary firing clock and repeats

## Scope and original behavior

This lane concerns fresh grounded action0/variant0 and repeated ordinary B for
RED, NEO and BLACK. The previous fallback fired at B+4 while authored contactP0
was zero, then returned idle at B+5 through a synthetic wall-contact signal.
All three consequently ignored their different original repeat delays. The
source projectile restored separately in5865dd2f is preserved.

Original18d350/18d438/18d534 form the three phases, with shot helper18dcb0.
Startup aimtimer30 decreases only if yaw alignment fails. Only a nonzero authored
P0 permits firing; missing raw stream banks do not. Firing debits cell0 once,
spawns c3be0 rows43/101/102 and installs repeat timer12/8/16 and aimtimer20.
Retap first validates available ammo without consuming it, refreshes the target
through6bf80, and restarts phase1. Actual firing owns the debit. Failure exits.

B press edge produces5d4bit20 for one update; held B is not a repeat or a
movement exit. A press edge produces bit1 for16 updates including detection.
Source5d8 analog-direction buffering is a wider state machine using thresholds
0x14/0x34 and20-update buffering, and must remain a stated adapter limitation
unless implemented separately.

## Authored stream clock

Shared g2s0 at80366638 is contiguous with g2s1 at8036665c. It does not terminate
between them. Opcode0d selects three directionally blended clips and advances
animation on the same parser call, unlike opcode01.

- Startup slots [positive1,middle0,negative2], frame0/blend5, mode6; middle
  resolves to MOT3/0 ending11. It sets P0=0, flag6e8=1 and face0.
- Gate3 applies equipment04/defaultFF. Ended wait0/−1 falls into s1.
- Repeat slots [7,6,8], frame0/blend0; middle MOT3/11 ends35. Side ends are36/35.
  It sets P0=1 and flag6e8=1. Gate4 sets P0=−1. Terminal mode9/count16 is a
  countdown freezing animation, not a wait for elapsed frame16.
- Repeat restart uses frame4/blend1 while P0 is nonnegative, otherwise defaults.
  Dynamic blend ratio is abs(signed1dfc)/16384. Middle clip owns clock; side
  clips affect presentation.

Independent standalone expectations, initialization call0 with no engine pauses:
- dt1: mode6 blend ends4, equipment gate8, s1/P0+16, P0−20, completion36.
- dt0.5: blend ends10, equipment17, s1/P0+33, P0−41, completion73.

Phase2 tests timer<=0 before decrementing it. With a buffered retap and aligned
aim, earliest dt1 repeated-shot gaps are14/10/18 for RED/NEO/BLACK. These are
source engine conditions, not an unconditional promise for all player inputs.

## Cleanup and limits

Idle18cef8 resets selector6ee to zero for a fresh entry. Cleanup18d668 clears
control bits3, calls6a474 and6a668(20). Here20 is an idle animation transition,
not an unconditional new20-update attack lockout:6a668 only writes694 when the
already-cleared control bits3 are set.

Existing aim/terrain adapters, host charge/admission behavior, analog-direction
buffering and centered-clip presentation versus original three-clip blending
remain explicit fidelity boundaries. No original assets are copied, and no
publication/deployment is authorized for this local work.

## Implementation boundaries and verification

The admitted actor now retains its captured UID until repeat6bf80 refresh.
Projectile allocation uses that UID rather than silently redirecting the first
shot after a mid-startup target switch. Child capture-range flags are still
calculated at spawn; original full snapshot timing remains a limitation.

Fresh exact grounded admission clears stale host control40 because the original
selector would otherwise choose subtype3. It does not clear40 on later ticks;
source airborne handoff still leads to the existing approximate variant3.
Cleanup mirrors current B-held state back to the generic input latch so the
next genuine press is not swallowed. These are narrow host reconciliation steps.

The source clock remains rate1 in the host. Only centered clips are rendered;
side-clip weights are not reproduced. Equipment [4,255] remains a raw shadow,
carry dust is omitted and the idle transition20 is recorded without its full
presentation/reset consumers. Browser stick exit uses threshold0x34/127 rather
than the complete original analog buffer. No full ordinary-action parity is
claimed.

Independent real-input tests pass across all three families for startup and
source samples, phase1 non-latching, repeated-shot gaps14/10/18, held-only input,
ammo exhaustion, target capture and refresh, death, A-buffer lifetime, immediate
next admission and charge handoffs. Seeded stale40 tests verify entry-only
reconciliation. Pure engine/clock tests include dt1 and dt0.5 gate counts and
source ordering. Earlier projectile and carry fixtures now await actual
source fire/completion instead of obsolete fixed ticks.

Six synthetic renderer cases verify MOT3/0 and3/11 source clock ownership and
paused rendering for all three families, without original assets. Final
`verify:contributor` passed: policy, TypeScript, UI/renderer, ROM, full combat
lifecycle, importer and production build (19.66 seconds). Existing large-bundle
warning remains. No actual browser screenshot or console replay was performed.
Nothing was published or deployed.
