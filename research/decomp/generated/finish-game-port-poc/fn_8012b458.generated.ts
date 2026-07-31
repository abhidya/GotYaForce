// Generated from 0x8012b458 by the deterministic GotYaForce OGhidra importer.
// This candidate is not registered by production code. Review and integrate explicitly.

export interface GeneratedEagleJetActor {
  borgNumber: number;
  phase: number;
  timer: number;
  dt: number;
  effectMode: number;
  cooldown: number;
  housekeeping: number;
  controlWord: number;
}

export interface GeneratedEagleJetHost {
  retireHitbox(actor: GeneratedEagleJetActor, kind: number): void;
  playCue(actor: GeneratedEagleJetActor, cue: number): void;
  preparePart(actor: GeneratedEagleJetActor, slot: number, value: number): void;
  dispatchFullBodyCue(actor: GeneratedEagleJetActor, cue: number): void;
}

export function tryStepFun8012b458(
  actor: GeneratedEagleJetActor,
  host: GeneratedEagleJetHost,
): boolean {
  actor.effectMode = 0x83;
  if (actor.phase === 0) {
    actor.phase = 1;
    actor.timer = 45.0;
    host.retireHitbox(actor, 0x7f);
    host.playCue(actor, 0x20);
    if (actor.borgNumber === 0x607) {
      host.preparePart(actor, 1, 0);
      host.preparePart(actor, 2, 0);
    } else if (actor.borgNumber === 0x61b) {
      host.preparePart(actor, 4, 0);
      host.preparePart(actor, 5, 0);
    }
    return true;
  }
  actor.timer -= actor.dt;
  if (actor.timer <= 0) {
    actor.cooldown = 0x10 + actor.dt;
    actor.housekeeping = 0;
    actor.controlWord &= 0xfffffffc;
    host.dispatchFullBodyCue(actor, 0x1b);
  }
  return true;
}
