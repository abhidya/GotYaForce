// ROM-faithful port of the CPU AI's combat WAYPOINT picker — FUN_8002400c @0x8002400c,
// the scenario-0/4/6/7 core of the waypoint master zz_0023bf4_ @0x80023bf4. Source:
// ai-state-handlers decode 2026-07-06 (workflow wf_2d3592b3-0d4), claims
// `waypoint-master`/`waypoint-orbit-core` — dual-lens verified (the verifier corrections
// folded in: scenario-10 skips the arena clamp, jitter step sizes are 0x400 BAM = 5.625°).
//
// The ROM writes the move-to point actor+0x2e8/+0x2ec/+0x2f0; the movement state machine
// (rom-movement.ts, zz_001d058_) then walks the borg TOWARD THE WAYPOINT — not directly
// at the target. The waypoint for normal combat is a point on a ring of PER-BORG radius
// R = borg record (+0x4b0) +0x114 around the TARGET, at a bearing = atan2(self − target)
// plus a PER-CLASS jitter drawn from one of three 16-entry BAM tables:
//   - class 3 (FLANKER): DAT_802ca4b0 — ≈±180° offsets → the waypoint lands BEHIND the
//     target (the flanker personality).
//   - class 2/5 or borg 0x500 (AMBUSHER MIX): DAT_802ca4d0 — 50% front-side ±45°,
//     50% far-side ±45°.
//   - all other classes (FRONTAL): DAT_802ca490 — ±45° around the self side.
// classByte = borg record byte 1 (the +0x661 dispatch class); both extracted per borg
// into data/romAiParams.json (classByte / engageRadius).
//
// NOT ported here (labeled): the terrain/LOS fixup FUN_800241c0 (wall-hit replacement +
// ground-height snap — needs the collision mesh, host-side), the reachable-ground ring
// search FUN_800245d0, and the scripted scenarios 1/2/3/5/8/9/10 (mission-script anchors,
// escort formations, sky perches — Challenge scripts don't populate them in this port).

import romAiParamsData from "../data/romAiParams.json" with { type: "json" };

const TABLES = (romAiParamsData as unknown as {
  orbitAngleTables: {
    frontal_802ca490: number[];
    flanker_802ca4b0: number[];
    ambusher_802ca4d0: number[];
  };
}).orbitAngleTables;

const BAM_TO_RAD = (Math.PI * 2) / 0x10000;

export interface WaypointPick {
  x: number;
  y: number;
  z: number;
}

/**
 * FUN_8002400c — normal-combat approach waypoint. `rand` is the caller's LCG draw
 * (the ROM uses one zz_00055fc_ draw, masked &0xf for the table index).
 */
export function pickCombatWaypoint(
  self: { x: number; y: number; z: number },
  target: { x: number; y: number; z: number },
  classByte: number,
  borgNumber: number,
  engageRadius: number,
  rand: number,
): WaypointPick {
  // Borgs 0xd06/0xd07 (satellite riders): waypoint = target position exactly.
  if (borgNumber === 0xd06 || borgNumber === 0xd07) {
    return { x: target.x, y: target.y, z: target.z };
  }
  // Base bearing = atan2(self − target): points from the target TOWARD self, so a zero
  // jitter puts the waypoint on the target's ring on the borg's own side (frontal).
  const baseBam = Math.round(Math.atan2(self.x - target.x, self.z - target.z) / BAM_TO_RAD) & 0xffff;
  const idx = rand & 0xf;
  let jitter: number;
  if (classByte === 3) {
    jitter = TABLES.flanker_802ca4b0[idx]!; // behind the target
  } else if (classByte === 2 || classByte === 5 || borgNumber === 0x500) {
    jitter = TABLES.ambusher_802ca4d0[idx]!;
  } else {
    jitter = TABLES.frontal_802ca490[idx]!;
  }
  const angle = ((baseBam + jitter) & 0xffff) * BAM_TO_RAD;
  // R = per-borg engage radius (record +0x114). x = sin, z = cos (the ROM's projection
  // convention, matching rom/physics.ts). y = target.y (fixup FUN_800241c0 unported).
  return {
    x: target.x + engageRadius * Math.sin(angle),
    y: target.y,
    z: target.z + engageRadius * Math.cos(angle),
  };
}

/** Per-borg waypoint inputs from the extracted params (classByte + engageRadius). */
export function waypointParamsFor(borgId: string): { classByte: number; engageRadius: number } | null {
  const rec = (romAiParamsData as unknown as {
    borgs: Record<string, { classByte?: number; engageRadius?: number }>;
  }).borgs[borgId];
  if (!rec || typeof rec.classByte !== "number") return null;
  const radius = rec.engageRadius ?? 0;
  return { classByte: rec.classByte, engageRadius: radius > 0 ? radius : 800.0 };
}
