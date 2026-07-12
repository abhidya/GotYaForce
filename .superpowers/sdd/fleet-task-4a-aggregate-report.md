# Fleet Task 4A aggregate report

Requirements are in `fleet-task-4a-brief.md`, `fleet-task-4a2-brief.md`, and `fleet-task-4a3-brief.md`. Detailed evidence and verification are in their corresponding reports.

Final candidate result:

- All eight Girl constructor roots and the complete 182-live-route member/action/variant matrix are implemented and exclusion-tested.
- Exact shared ranged/melee/Cyber/series-3 phase/event/ammo behavior, afterimage/pose state, descriptor-rate pitch/yaw, scale factors, floor support/snap/revert, and family helper call boundaries are executable.
- Seven constructor/action slots are newly classified `ported` after review demotion.
- Coverage: 119 constructors / 325 slots; 20 ported, 234 partial, 71 missing.
- Anchor-dependent X slots remain partial because ROM `+0x8e0/+0x8f0/+0x900` part rows have no authoritative renderer-node identity or renderer-to-runtime transform feed. Root-position fallback is not used for certification.

Reported verification: combat build PASS; game typecheck PASS; full ROM selfcheck PASS; focused presentation selfcheck PASS; default audit PASS; strict audit expected FAIL for remaining fleet gaps; diff check PASS.

Review correction: the seven action-1 entries for Battle, Wire, Barrier, Killer/Shadow,
Cyber, Spinner, and Delta were demoted because `zz_006e514_` shares the unproven renderer
part-row anchor. The remaining promoted Girl keys are `0x800c04c0:0`, `0x80106e3c:0`,
`0x80107e7c:0`, `0x8019c380:0`, `0x80134078:0`, `0x8012f204:0`, and Cyber Girl
`0x8012f204:2`.

The afterimage presentation is the exact subtype-1 child: efct-bank id 69, config
`0x802fc758`, 20-frame scale track `0x802fc588`, alpha track `0x802fc5b8`, owner base
scale, 50-unit scaled backward offset, discrete random BAM yaw, and render state `0x1e`.
Final correction: the backward offset uses owner `+0x5ae` lock yaw, not heading. State
`0x1e` is consumed as the `FUN_80047aa4` X/Y/Z-rotation plus authored-scale bitfield.
