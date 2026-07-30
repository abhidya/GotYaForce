// Generated POC candidate from a deterministically validated local-LLM artifact.
// Untrusted integration scaffold: this file is not imported by production code.

export interface EagleJetPocActor {
  borgNumber: number;
  phase: number;
  timer: number;
  dt: number;
  effectMode: number;
  controlWord: number;
}

export interface EagleJetPocHost {
  retireHitbox(actor: EagleJetPocActor, kind: number): void;
  playCue(actor: EagleJetPocActor, cue: number): void;
  preparePart(actor: EagleJetPocActor, slot: number, value: number): void;
  cleanup(actor: EagleJetPocActor, cooldown: number): void;
}

export function stepFun8012b458(actor: EagleJetPocActor, host: EagleJetPocHost): void {
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
    return;
  }
  actor.timer -= actor.dt;
  if (actor.timer <= 0) host.cleanup(actor, 0x10);
}
