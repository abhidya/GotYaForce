# Beam pulses receiving on Time Bomber mines

Local follow-up to `1b9c3088`; publication remains paused. No original assets are
added. This extends the bounded mine collision adapter, not the global collision
engine or all weapon reception paths.

## Evidence and scope

The source active-versus-secondary pass `8002db58` admits Beam Gunner's pulse
attack to the mine receiver. Beam HIT10/remap9 has attack-only descriptor flags1;
mine HIT15/remap8 has descriptor flags3. The beam damage record at `803214e0`
has HP3, flagsA1 and flagsB0. Positive ordinary damage can deplete the mine's
single durability unit. Shape2 with damage flagsA1 processes all intersecting
receivers rather than selecting only one nearest hit.

The existing beam pulse lifecycle mirrors `80139bbc` initialization at the start
point, the recovered `80139c50` live-endpoint sweep, and `80139c78` retirement.
Each pulse owns an attack identity across its sphere and sweep. Later pulses have
new identities; the emitter UID is not the pulse attack identity. The source
parent/pulse path has no ordinary flying-projectile consumption or terrain stop.

The implementation uses a stable per-pulse attack UID for mine receiver history
and records the mine in the pulse victim set. Every eligible intersecting mine
is considered. Contact does not consume the emitter, retire the mine early, or
invent borg hit-confirm/gauge effects. The mine detonates on its next child
update and returns its held resource on the subsequent retirement update.

## Limits

Existing static attachments and host sphere/capsule geometry remain approximate.
The mine receiver retains its bounded owner/team/burst checks; linked-owner,
reflection and special-status behavior is incomplete. Beam attack-only flags do
not justify adding a reciprocal mine attack against the beam. Melee and tether
receiving paths remain unsupported. This is not console-replay or full-game
parity proof, and no new original visual assets are supplied.

## Validation

- Four independent real-input scenario groups pass: multi-mine sweep and list
  order, initialization/pulse identity, geometry/receiver gates, pending pulse
  and visual-tail behavior. Real Beam Gunner X and Time Bomber B create objects;
  collision positions are labeled synthetic geometry fixtures.
- Natural HP3 beam damage destroys HP1 mines, with delayed explosions/refunds.
  A separately labeled zero-HP record fixture preserves a mine across phases
  to check init/sweep deduplication and fresh-pulse independence.
- Negative controls cover vertical misses, same-owner drifting mine, retired
  mine, healing and team-filter metadata. A paired same-owner bob positive
  prevents an overly broad self-contact filter from passing unnoticed.
- Pending pulses complete after owner death. Natural visual tail creates no new
  pulses. Mine-only contacts do not fabricate fighter hit-confirm telemetry.
- Full `verify:contributor` passes, including production build and existing
  frontend, rendering, ROM and combat tests. Final focused tests and combat
  typecheck pass after the last additional positive control.
- Existing beam renderer selfcheck passes. No browser screenshot or console
  replay validation was performed. Existing large-bundle warning remains.

Logs: `beam-mine-contributor-final.log` and `beam-mine-lifecycle-final.log` in
this local reconstruction workspace's parent directory. No remote publication
or deployment was attempted.
