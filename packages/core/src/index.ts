// @gf/core — engine spine: main loop, fixed-timestep scheduler, and the ECS that
// every other system (render, physics, combat, ai, missions, ui, audio, save)
// hangs off of. Owns no game rules itself; it wires the subsystems together.
// (See PHASE0_RESEARCH.md §10 architecture diagram: CORE -> REN/PHY/CMB/AI/...)
export {};
