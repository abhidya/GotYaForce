// =============================================================================
// sourceDeath.ts — ROM-faithful 1:1 port of the GG4E death/kill-event pipeline.
//
// Ports two decompiled functions, byte-for-byte against the source:
//   - zz_005bbc0_ (borg_death_entry) @0x8005bbc0 — chunk_0007.c:3716-3751
//     the borg death state transition (the victory/defeat path entry).
//   - zz_002f8dc_ (kill_event_energy_and_score_accounting) @0x8002f8dc —
//     chunk_0003.c:8212-8331 the force-energy + score accounting on a kill.
//
// CHALLENGE-FLOW GATE (research/decomp/index/challenge-flow-evidence.md):
//   - "Confirm the original Challenge win/loss branch and next-battle counter before
//      replacing Results progression" (:214). The depletion check inside
//      kill_event_energy_and_score_accounting (sideEnergy < 1 → zero + record) IS that
//      win/loss branch; this port reproduces it faithfully.
//   - "Confirm the original ordered-force spawn/death swap path before changing Challenge
//      roster behavior" (:81). borg_death_entry's slot-swap call (zz_008b640_, gated on
//      the active slot == dying slot) IS the death-swap path entry; cited here.
//
// DOL-DUMPED CONSTANTS: the three death-state-timer floats read by the death-entry helper
// zz_005c028_ (FLOAT_80437428=1.0, FLOAT_80437438=30.0, FLOAT_8043743c=20.0) are confirmed
// by direct DOL read (scripts/gen-knockback-strength-tables.mjs companion dump verified
// the same addresses via the runtimeToFileOffset DOL-reader pattern). The +100 team-score
// grant and the per-side stride 0x3c / per-actor offsets are cited inline from the source.
//
// SELF-CONTAINED: depends on nothing but these typed inputs. It does NOT import combat.ts
// / battle.ts / BorgRuntime, so it can be unit-ported and audited in isolation, then wired
// into the death/kill path via the integration spec at the bottom of this file.
// =============================================================================

// -----------------------------------------------------------------------------
// DEATH-STATE-TIMER FLOATS (zz_005c028_, chunk_0007.c:3873-3891) — DOL-confirmed.
// -----------------------------------------------------------------------------
/** FLOAT_80437428 = 1.0 — death-timer override (stateTimer when +0x591==7 OR +0x663!=0). */
const DEATH_TIMER_OVERRIDE = 1;
/** FLOAT_80437438 = 30.0 — death-timer when death-type (+0x6fe) has bit (dt-1)&4 set. */
const DEATH_TIMER_TYPE_SET = 30;
/** FLOAT_8043743c = 20.0 — death-timer when death-type has bit (dt-1)&4 clear. */
const DEATH_TIMER_TYPE_CLEAR = 20;

/** Death state value written to actor+0x18 (chunk_0007.c:3728). 1 = active, 2 = death. */
export const DEATH_STATE_VALUE = 2;
/** Control-word bit set on death (chunk_0007.c:3732): +0x5e0 |= 0x80000000. */
export const DEATH_CONTROL_WORD_BIT = 0x80000000;
/** Status-word bits OR'd on death (chunk_0007.c:3746): +0x272 |= 0x443. */
export const DEATH_STATUS_WORD_BITS = 0x443;
/** Cue dispatched to both upper-body + full-body cue tables on death (chunk_0007.c:3743). */
export const DEATH_CUE = 0x2f;
/** Team-score grant per cross-team kill (chunk_0003.c:8292): DAT_80436154[team] += 100. */
export const KILL_TEAM_SCORE_GRANT = 100;

// -----------------------------------------------------------------------------
// ACTOR + STATE TYPES — minimal, each field cited to its object+0xNNN offset.
// -----------------------------------------------------------------------------

/** Minimal dying-actor view for borg_death_entry. Every field maps 1:1 to a ROM offset
 *  written inside zz_005bbc0_. Use defaultDeathActor() for a neutral baseline. */
export interface SourceDeathActor {
  /** +0x83: borg eligibility byte. ==0 means "is a borg" (gates kill_event accounting). */
  eligibility83: number;
  /** +0x18: state byte. zz_005bbc0_ writes 2 (death); 1 = active. */
  state18: number;
  /** +0x19/+0x1a/+0x1b: adjacent state bytes, zeroed on death. */
  state19: number;
  state1a: number;
  state1b: number;
  /** +0x5e0: control word (bitfield). OR'd with 0x80000000 on death. */
  controlWord5e0: number;
  /** +0x8c4: cleared to 0 on death. */
  clear8c4: number;
  /** +0x710/+0x712: u16 pairs cleared to 0 on death. */
  clear710: number;
  clear712: number;
  /** +0x6fe: death-type byte. zz_005bbc0_ sets it to 7 when ((dt-1)&4)!=0. */
  deathType6fe: number;
  /** +0x272: status word (u16). OR'd with 0x443 on death. */
  statusWord272: number;
  /** +0x558: state-timer float, set by the death-entry helper zz_005c028_. */
  stateTimer558: number;
  /** +0x591/+0x663: bytes read by zz_005c028_ to pick the death-timer float. */
  byte591: number;
  byte663: number;
  /** +0x1da: control-word mirror (the arg to zz_005efc4_; read by zz_00300bc_ mirror gate). */
  controlWord1da: number;
  /** +0x3e4: slot index byte. */
  slot3e4: number;
  /** +0x3e5: visibility bit (cleared in the global visibility mask on death). */
  visibilityBit3e5: number;
  // --- kill_event fields (chunk_0003.c:8212-8331) ---
  /** +0x88: team byte. */
  team88: number;
  /** +0x3e6: hero/CPU flag (signed char). !=0 = CPU. */
  heroFlag3e6: number;
  /** +0x1ea: kill-target flag (gates the killsRemaining decrement). */
  killTargetFlag1ea: number;
  /** +0x4aa: cost value (s16) — the force-energy value subtracted on death. */
  cost4aa: number;
  /** +0x434: kill count (attacker side, incremented on a cross-team kill). */
  kills434: number;
  /** +0x435: death count (victim side, incremented unconditionally). */
  deaths435: number;
  /** +0x420: cost-won accumulator (attacker). */
  costWon420: number;
  /** +0x424: cost-lost accumulator (victim). */
  costLost424: number;
}

/** Per-side state (stride 0x3c inside the battle-work struct PTR_DAT_80433934). */
export interface SourceSideState {
  /** team * 0x3c + 0x118: side force-energy pool (the victory/defeat resource). */
  energy118: number;
  /** team * 0x3c + 0xf6: side flag (mode 2+ energy-subtract conditional). */
  flagF6: number;
  /** team * 0x3c + 0x108: side flag (mode 0 energy-subtract gate). */
  flag108: number;
  /** team * 0x3c + 0x109: kill-counting-enabled flag (versus-only). */
  flag109: number;
  /** team * 0x3c + 0x10a: kills-remaining countdown (versus-only, s8). */
  killsRemaining10a: number;
}

/** The global battle-work struct (PTR_DAT_80433934) fields touched by these functions. */
export interface SourceBattleWork {
  /** [team] → per-side state. */
  sides: SourceSideState[];
  /** +0xb4: last-killer pointer (recorded on the depletion/killsRemaining trigger). */
  lastKillerB4: SourceDeathActor | null;
  /** +0xb8: last-victim pointer. */
  lastVictimB8: SourceDeathActor | null;
  /** +0x1f: global suppress flag — when !=0, suppresses killer/victim pointer recording. */
  suppressFlag1f: number;
  /** +0xea: global visibility mask (cleared of the dying borg's bit on death). */
  visibilityMaskea: number;
  /** +0xee: active slot byte (the slot-swap gate: activeSlot == dying.slot3e4). */
  activeSlotEe: number;
  /** +0xd2: visibility gate byte (zz_005bbc0_ calls zz_005bccc_ only when the bit is clear). */
  visibilityGateD2: number;
}

/** Per-team score array (DAT_80436154[team]), +100 per cross-team kill. */
export type TeamScoreMap = Record<number, number>;

/** Result of the kill-event accounting (for audit/self-test). */
export interface KillEventResult {
  /** Force energy subtracted from the victim's side pool (0 if the gate blocked it). */
  energySubtracted: number;
  /** Whether the victim's side pool dropped below 1 (the victory/defeat trigger fired). */
  sideDepleted: boolean;
  /** Whether the versus-only killsRemaining counter was decremented. */
  killsRemainingDecremented: boolean;
  /** Whether the killer was credited (cross-team, borg killer). */
  killerCredited: boolean;
  /** Roster events emitted (event type 3 = enemy died, 4 = ally died). */
  rosterEvents: RosterEvent[];
}

/** One roster notification (chunk_0003.c:8296-8329). */
export interface RosterEvent {
  /** The slot that received the event (team, for ally vs enemy classification). */
  receiverTeam: number;
  receiverIsVictim: boolean;
  /** 3 = enemy of victim died, 4 = ally of victim died. */
  eventType: 3 | 4;
  /** victim.slot3e4 (the slot index of the dead borg). */
  victimSlot: number;
}

// =============================================================================
// zz_005bbc0_ — borg_death_entry @0x8005bbc0 (chunk_0007.c:3716-3751)
//
// The death state transition. Writes the death-state byte (+0x18=2), the death control-
// word bit (+0x5e0 |= 0x80000000), zeroes adjacent fields, OR's the status word
// (+0x272 |= 0x443), resolves the death-type byte (+0x6fe), seeds the death state-timer
// (+0x558 via zz_005c028_), clears the visibility bit, dispatches cue 0x2f, and calls the
// death-state sub-entry zz_005bccc_ when the visibility gate passes.
// =============================================================================

/**
 * 1:1 port of zz_005bbc0_. Performs the death state transition on `target`.
 *
 *   target  — the dying borg (param_1). Mutated in place with the death-state writes.
 *   battle  — the battle-work struct (visibility mask clear + slot-swap gate). The slot-
 *             swap helper zz_008b640_ and the death sub-entry zz_005bccc_ are invoked via
 *             the optional callbacks when their gates pass (cited partial: their full
 *             internal behavior is out of scope for the death-state WRITES, which are the
 *             faithful core here).
 *
 * FAITHFUL WRITES (chunk_0007.c:3728-3746):
 *   +0x18 = 2 (death); +0x19/+0x1a/+0x1b = 0
 *   +0x5e0 |= 0x80000000
 *   +0x8c4 = 0; +0x710 = 0; +0x712 = 0
 *   +0x6fe = 7 when ((deathType - 1) & 4) != 0  (else unchanged)
 *   +0x272 |= 0x443
 *   +0x558 = deathTimer (via zz_005c028_, ported inline below)
 *   global visibility mask &= ~target.visibilityBit3e5
 *   cue 0x2f dispatched to upper-body + full-body
 */
export function borgDeathEntry(
  target: SourceDeathActor,
  battle: SourceBattleWork,
  callbacks?: {
    onCueDispatch?: (actor: SourceDeathActor, cue: number) => void;
    onSlotSwap?: () => void;
    onDeathSubEntry?: (actor: SourceDeathActor) => void;
  },
): void {
  // (chunk_0007.c:3723-3724) zz_005f00c_ / zz_005efc4_: pre-death cleanup helpers. Their
  // internal writes are out of scope (cited deps); the death-state writes below are the
  // faithful core. Callers needing the cleanup wire onCueDispatch-style hooks separately.

  // (chunk_0007.c:3725-3727) death-type override: if ((deathType - 1) & 4) != 0 → 7.
  // `- 1U & 4` treats (deathType - 1) as unsigned before masking bit 2.
  if ((((target.deathType6fe - 1) >>> 0) & 4) !== 0) {
    target.deathType6fe = 7;
  }

  // (chunk_0007.c:3728-3731) state byte = 2 (death); adjacent state bytes zeroed.
  target.state18 = DEATH_STATE_VALUE;
  target.state19 = 0;
  target.state1a = 0;
  target.state1b = 0;

  // (chunk_0007.c:3732) control word |= 0x80000000 (the death bit).
  target.controlWord5e0 = (target.controlWord5e0 | DEATH_CONTROL_WORD_BIT) >>> 0;

  // (chunk_0007.c:3733-3735) cleared fields.
  target.clear8c4 = 0;
  target.clear710 = 0;
  target.clear712 = 0;

  // (chunk_0007.c:3736) global visibility mask: clear the dying borg's bit.
  // PTR_DAT_80433934[0xea] &= ~target.visibilityBit3e5 (+0x3e5).
  battle.visibilityMaskea = battle.visibilityMaskea & ~target.visibilityBit3e5;

  // (chunk_0007.c:3737-3742) slot-swap gate: if zz_008b480_() (mode check) and the active
  // slot (+0xee) == the dying borg's slot (+0x3e4), call zz_008b640_ (the death-swap).
  if (battle.activeSlotEe === target.slot3e4) {
    callbacks?.onSlotSwap?.();
  }

  // (chunk_0007.c:3743-3744) cue 0x2f dispatched to upper-body (zz_006a750_) + full-body
  // (zz_006a6fc_) cue tables — the death animation/state transition cue.
  callbacks?.onCueDispatch?.(target, DEATH_CUE);
  callbacks?.onCueDispatch?.(target, DEATH_CUE);

  // (chunk_0007.c:3745 → zz_005c028_) death state-timer: seed +0x558 from the death-type
  // and two gate bytes (+0x591, +0x663). Ported inline (zz_005c028_, chunk_0007.c:3873-3891):
  //   if +0x591 == 7 → 1.0; else if ((deathType-1)&4)==0 → 20.0 else 30.0; if +0x663 != 0 → 1.0.
  target.stateTimer558 = resolveDeathTimer(target);

  // (chunk_0007.c:3746) status word |= 0x443.
  target.statusWord272 = (target.statusWord272 | DEATH_STATUS_WORD_BITS) & 0xffff;

  // (chunk_0007.c:3747-3749) death sub-entry zz_005bccc_ — called only when the visibility
  // gate passes: (target.visibilityBit3e5 & battle.visibilityGateD2) == 0.
  if ((target.visibilityBit3e5 & battle.visibilityGateD2) === 0) {
    callbacks?.onDeathSubEntry?.(target);
  }
}

/** Port of zz_005c028_ @0x8005c028 (chunk_0007.c:3873-3891): resolve the death state-timer. */
function resolveDeathTimer(target: SourceDeathActor): number {
  // (chunk_0007.c:3876-3878) +0x591 == 7 → FLOAT_80437428 (1.0) override.
  if (target.byte591 === 7) return DEATH_TIMER_OVERRIDE;
  // (chunk_0007.c:3880-3885) death-type select: ((dt-1)&4)==0 → 20.0 (FLOAT_8043743c),
  //   else 30.0 (FLOAT_80437438).
  const byType = (((target.deathType6fe - 1) >>> 0) & 4) === 0
    ? DEATH_TIMER_TYPE_CLEAR
    : DEATH_TIMER_TYPE_SET;
  // (chunk_0007.c:3886-3890) +0x663 != 0 → FLOAT_80437428 (1.0) final override.
  return target.byte663 !== 0 ? DEATH_TIMER_OVERRIDE : byType;
}

// =============================================================================
// zz_002f8dc_ — kill_event_energy_and_score_accounting @0x8002f8dc
// (chunk_0003.c:8212-8331)
//
// The force-energy + score accounting on a kill. Subtracts the victim's cost from its
// side energy pool (with a mode/team/CPU conditional), decrements the versus-only
// killsRemaining counter, fires the depletion (victory/defeat) trigger, credits the
// killer's per-actor + team-score counters, and notifies the 6-slot roster.
// =============================================================================

/**
 * 1:1 port of zz_002f8dc_. Performs the kill-event energy/score accounting.
 *
 *   killer  — the dealing-blow actor (param_1). May be non-borg (+0x83 != 0).
 *   victim  — the dying actor (param_2). Must be a borg (+0x83 == 0) else early-return.
 *   battle  — the battle-work struct (side pools + last-killer/victim recording).
 *   teamScore — the per-team score map (DAT_80436154), +100 per cross-team kill.
 *   roster  — the 6 roster slots for the notification loop (chunk_0003.c:8296-8329).
 *
 * FAITHFUL ACCOUNTING (chunk_0003.c:8224-8294):
 *   - victim.cost = s16 +0x4aa
 *   - sideEnergy[victim.team] -= cost  (conditional, see shouldSubtractEnergy)
 *   - killsRemaining[victim.team]--    (VERSUS-ONLY: challengeMode == 0 path)
 *   - if sideEnergy < 1 → 0 + record killer/victim  (the depletion / victory trigger)
 *   - victim.deaths++, victim.costLost += cost
 *   - if killer is borg AND killer.team != victim.team:
 *       killer.kills++, killer.costWon += cost, teamScore[killer.team] += 100
 *
 * Returns a KillEventResult summarizing the effects (for audit/self-test). Mutates the
 * side pools, actor counters, and teamScore in place, matching the ROM's in-place writes.
 */
export function killEventEnergyAndScoreAccounting(
  killer: SourceDeathActor,
  victim: SourceDeathActor,
  battle: SourceBattleWork,
  teamScore: TeamScoreMap,
  challengeMode: number,
  roster?: ReadonlyArray<{ active: number; team: number; uid: string }>,
  victimUid?: string,
): KillEventResult {
  // (chunk_0003.c:8224-8226) eligibility gate: victim must be a borg (+0x83 == 0).
  if (victim.eligibility83 !== 0) {
    return {
      energySubtracted: 0,
      sideDepleted: false,
      killsRemainingDecremented: false,
      killerCredited: false,
      rosterEvents: [],
    };
  }

  const cost = victim.cost4aa; // (chunk_0003.c:8227) iVar3 = (int)*(short*)(victim + 0x4aa)
  const victimSide = battle.sides[victim.team88] ?? emptySide();
  let energySubtracted = 0;
  let killsRemainingDecremented = false;
  let recordedVictim = false; // bVar2: tracks whether kill-count already recorded the pair

  // --- Force-energy accounting (chunk_0003.c:8228-8257) ---
  if (challengeMode !== 0) {
    // Challenge mode (!= 0): conditional subtract, then SKIP kill-count (goto depletion).
    if (shouldSubtractEnergyChallenge(challengeMode, victim.team88, victim.heroFlag3e6, victimSide)) {
      victimSide.energy118 -= cost;
      energySubtracted = cost;
    }
    // goto LAB_8002fa4c — skips the versus-only kill-count block.
  } else {
    // Versus (mode 0): subtract gated by side.flag108 (+0x108).
    if (victimSide.flag108 !== 0) {
      // CPU team-0 skips the subtract (chunk_0003.c:8253-8254) but still falls through to
      // the kill-count block (unlike the Challenge goto).
      if (!(victim.team88 === 0 && victim.heroFlag3e6 !== 0)) {
        victimSide.energy118 -= cost;
        energySubtracted = cost;
      }
    }
    // --- Versus-only kill-count tracking (chunk_0003.c:8258-8273, LAB_8002f944) ---
    if (victimSide.flag109 !== 0 && victim.killTargetFlag1ea !== 0 && victimSide.killsRemaining10a > 0) {
      victimSide.killsRemaining10a -= 1;
      killsRemainingDecremented = true;
      if (battle.suppressFlag1f === 0) {
        if (killer.eligibility83 === 0) battle.lastKillerB4 = killer; // (chunk_0003.c:8265-8267)
        recordedVictim = true;
        battle.lastVictimB8 = victim; // (chunk_0003.c:8269)
      }
    }
  }

  // --- Depletion / victory-defeat trigger (chunk_0003.c:8274-8285, LAB_8002fa4c) ---
  let sideDepleted = false;
  if (victimSide.energy118 < 1) {
    victimSide.energy118 = 0;
    sideDepleted = true;
    if (battle.suppressFlag1f === 0 && !recordedVictim) {
      if (killer.eligibility83 === 0) battle.lastKillerB4 = killer; // (chunk_0003.c:8279-8281)
      battle.lastVictimB8 = victim; // (chunk_0003.c:8282)
    }
  }

  // --- Victim death counters (chunk_0003.c:8286-8287) — UNCONDITIONAL ---
  victim.deaths435 += 1;
  victim.costLost424 += cost;

  // --- Attacker kill counters (chunk_0003.c:8288-8293): killer is borg AND not suicide ---
  let killerCredited = false;
  if (killer.eligibility83 === 0 && killer.team88 !== victim.team88) {
    killer.kills434 += 1;
    killer.costWon420 += cost;
    // (chunk_0003.c:8292) DAT_80436154[killer.team] += 100.
    teamScore[killer.team88] = (teamScore[killer.team88] ?? 0) + KILL_TEAM_SCORE_GRANT;
    killerCredited = true;
  }

  // --- Roster notification (chunk_0003.c:8295-8329): 6 slots, event 3 (enemy) / 4 (ally) ---
  const rosterEvents: RosterEvent[] = [];
  if (roster) {
    for (const slot of roster) {
      if (slot.active === 0) continue;
      if (slot.team === victim.team88) {
        // (chunk_0003.c:8300-8313) same team as victim: ally-died event, skip the victim itself.
        if (victimUid !== undefined && slot.uid === victimUid) continue;
        rosterEvents.push({
          receiverTeam: slot.team,
          receiverIsVictim: false,
          eventType: 4,
          victimSlot: victim.slot3e4,
        });
      } else {
        // (chunk_0003.c:8315-8325) different team: enemy-died event.
        rosterEvents.push({
          receiverTeam: slot.team,
          receiverIsVictim: false,
          eventType: 3,
          victimSlot: victim.slot3e4,
        });
      }
    }
  }

  return { energySubtracted, sideDepleted, killsRemainingDecremented, killerCredited, rosterEvents };
}

/**
 * Challenge-mode energy-subtract conditional (chunk_0003.c:8229-8248).
 *   mode == 1: subtract unless (team == 0 AND CPU).
 *   mode 2+:   flagF6==0 → subtract if CPU; flagF6!=0 → subtract if player.
 */
function shouldSubtractEnergyChallenge(
  mode: number,
  team: number,
  heroFlag: number,
  side: SourceSideState,
): boolean {
  if (mode === 1) {
    return team !== 0 || heroFlag === 0;
  }
  // mode 2+
  if (side.flagF6 === 0) {
    return heroFlag !== 0;
  }
  return heroFlag === 0;
}

// =============================================================================
// Neutral factories.
// =============================================================================

function emptySide(): SourceSideState {
  return { energy118: 0, flagF6: 0, flag108: 0, flag109: 0, killsRemaining10a: 0 };
}

/** Neutral baseline battle-work (one side per team, no suppression, empty pointers). */
export function defaultSourceBattleWork(sideCount = 2): SourceBattleWork {
  return {
    sides: Array.from({ length: sideCount }, () => emptySide()),
    lastKillerB4: null,
    lastVictimB8: null,
    suppressFlag1f: 0,
    visibilityMaskea: 0xff,
    activeSlotEe: 0,
    visibilityGateD2: 0,
  };
}

/** Neutral baseline actor (team 0, borg, alive, zero cost). */
export function defaultDeathActor(team = 0, overrides: Partial<SourceDeathActor> = {}): SourceDeathActor {
  return {
    eligibility83: 0,
    state18: 1,
    state19: 0,
    state1a: 0,
    state1b: 0,
    controlWord5e0: 0,
    clear8c4: 0,
    clear710: 0,
    clear712: 0,
    deathType6fe: 1,
    statusWord272: 0,
    stateTimer558: 0,
    byte591: 0,
    byte663: 0,
    controlWord1da: 0,
    slot3e4: 0,
    visibilityBit3e5: 1,
    team88: team,
    heroFlag3e6: 0,
    killTargetFlag1ea: 0,
    cost4aa: 0,
    kills434: 0,
    deaths435: 0,
    costWon420: 0,
    costLost424: 0,
    ...overrides,
  };
}

// =============================================================================
// SELF-TESTS — runSourceDeathSelfTests(assert). assert shape: (cond, msg) => void.
// =============================================================================

export type SourceDeathAssert = (cond: boolean, msg: string) => void;

export function runSourceDeathSelfTests(assert: SourceDeathAssert): void {
  // ---------- zz_005bbc0_ — borg_death_entry faithful state writes ---------------------
  const dead = defaultDeathActor(0, {
    deathType6fe: 6, // (6-1)&4 = 5&4 = 4 != 0 → overridden to 7
    controlWord5e0: 0x40,
    statusWord272: 0x100,
    visibilityBit3e5: 0x02,
    byte591: 0,
    byte663: 0,
  });
  const battle = defaultSourceBattleWork(2);
  battle.visibilityMaskea = 0xff;
  battle.visibilityGateD2 = 0;
  battle.activeSlotEe = 0;
  const cues: number[] = [];
  let slotSwap = 0;
  let subEntry = 0;
  borgDeathEntry(dead, battle, {
    onCueDispatch: (_a, cue) => cues.push(cue),
    onSlotSwap: () => { slotSwap += 1; },
    onDeathSubEntry: () => { subEntry += 1; },
  });

  // +0x18 = 2 (death); +0x19/+0x1a/+0x1b = 0.
  assert(dead.state18 === DEATH_STATE_VALUE, `+0x18 === 2 (death) — got ${dead.state18}`);
  assert(dead.state19 === 0 && dead.state1a === 0 && dead.state1b === 0, "adjacent state bytes zeroed");
  // +0x5e0 |= 0x80000000 (preserving existing bits).
  assert((dead.controlWord5e0 & DEATH_CONTROL_WORD_BIT) !== 0, "+0x5e0 death bit set");
  assert((dead.controlWord5e0 & 0x40) !== 0, "+0x5e0 preserved existing bits (0x40)");
  // +0x6fe override: deathType 6 → 7.
  assert(dead.deathType6fe === 7, `deathType 6 → 7 (overridden) — got ${dead.deathType6fe}`);
  // +0x272 |= 0x443.
  assert((dead.statusWord272 & DEATH_STATUS_WORD_BITS) === DEATH_STATUS_WORD_BITS, "+0x272 |= 0x443");
  assert((dead.statusWord272 & 0x100) !== 0, "+0x272 preserved existing bits (0x100)");
  // cleared fields.
  assert(dead.clear8c4 === 0 && dead.clear710 === 0 && dead.clear712 === 0, "+0x8c4/+0x710/+0x712 cleared");
  // visibility mask cleared of the dying bit.
  assert((battle.visibilityMaskea & 0x02) === 0, "global visibility mask cleared of dying bit");
  // cue 0x2f dispatched twice (upper + full body).
  assert(cues.length === 2 && cues.every((c) => c === DEATH_CUE), `cue 0x2f dispatched twice (got ${JSON.stringify(cues)})`);
  // slot-swap fired (activeSlot == dying slot 0).
  assert(slotSwap === 1, "slot-swap fired (active slot == dying slot)");
  // death sub-entry fired (visibility gate clear).
  assert(subEntry === 1, "death sub-entry fired (visibility gate clear)");

  // death-type NOT overridden when ((dt-1)&4) == 0 (dt = 1,2,3,4).
  const normalDead = defaultDeathActor(0, { deathType6fe: 2 });
  borgDeathEntry(normalDead, defaultSourceBattleWork(2));
  assert(normalDead.deathType6fe === 2, `deathType 2 unchanged ((2-1)&4 == 0) — got ${normalDead.deathType6fe}`);

  // death-timer (zz_005c028_): dt=2 (type-clear) → 20.0; dt=6 (type-set) → 30.0; +0x663!=0 → 1.0.
  const tClear = defaultDeathActor(0, { deathType6fe: 2, byte591: 0, byte663: 0 });
  borgDeathEntry(tClear, defaultSourceBattleWork(2));
  assert(tClear.stateTimer558 === DEATH_TIMER_TYPE_CLEAR, `death timer dt-clear === 20 (got ${tClear.stateTimer558})`);
  const tSet = defaultDeathActor(0, { deathType6fe: 6, byte591: 0, byte663: 0 });
  borgDeathEntry(tSet, defaultSourceBattleWork(2));
  assert(tSet.stateTimer558 === DEATH_TIMER_TYPE_SET, `death timer dt-set === 30 (got ${tSet.stateTimer558})`);
  const tOverride = defaultDeathActor(0, { deathType6fe: 6, byte663: 1 });
  borgDeathEntry(tOverride, defaultSourceBattleWork(2));
  assert(tOverride.stateTimer558 === DEATH_TIMER_OVERRIDE, `death timer +0x663 override === 1 (got ${tOverride.stateTimer558})`);

  // ---------- zz_002f8dc_ — kill_event energy/score accounting ------------------------
  // Baseline: versus (mode 0), flag108 set, cross-team kill, victim cost 500.
  const killer = defaultDeathActor(1, { eligibility83: 0, cost4aa: 0 }); // team 1
  const victim = defaultDeathActor(0, { cost4aa: 500, killTargetFlag1ea: 1 }); // team 0, cost 500
  const bw = defaultSourceBattleWork(2);
  bw.sides[0]!.energy118 = 1000;
  bw.sides[0]!.flag108 = 1; // enable energy subtract in mode 0
  bw.sides[0]!.flag109 = 1; // enable kill-counting
  bw.sides[0]!.killsRemaining10a = 3;
  const scores: TeamScoreMap = { 0: 0, 1: 0 };
  const res = killEventEnergyAndScoreAccounting(killer, victim, bw, scores, 0);

  // sideEnergy[victim.team=0] -= 500 → 500.
  assert(bw.sides[0]!.energy118 === 500, `victim side energy 1000-500 === 500 (got ${bw.sides[0]!.energy118})`);
  assert(res.energySubtracted === 500, "energySubtracted === 500");
  // killsRemaining decremented (versus, flag109 set, killTarget flag set, >0): 3 → 2.
  assert(bw.sides[0]!.killsRemaining10a === 2 && res.killsRemainingDecremented, "killsRemaining 3 → 2 (versus-only)");
  // victim death counters.
  assert(victim.deaths435 === 1 && victim.costLost424 === 500, "victim deaths++ and costLost += 500");
  // killer credited (cross-team borg): kills++, costWon += 500, teamScore[1] += 100.
  assert(killer.kills434 === 1 && killer.costWon420 === 500, "killer kills++ and costWon += 500");
  assert(scores[1] === KILL_TEAM_SCORE_GRANT, `teamScore[1] === 100 (got ${scores[1]})`);
  assert(res.killerCredited, "killerCredited === true");
  // killer/victim recorded (no suppress).
  assert(bw.lastVictimB8 === victim, "lastVictim recorded");

  // --- Depletion trigger: sideEnergy drops below 1 → zeroed + record ---
  const killer2 = defaultDeathActor(1);
  const victim2 = defaultDeathActor(0, { cost4aa: 1000, killTargetFlag1ea: 1 });
  const bw2 = defaultSourceBattleWork(2);
  bw2.sides[0]!.energy118 = 500;
  bw2.sides[0]!.flag108 = 1;
  const res2 = killEventEnergyAndScoreAccounting(killer2, victim2, bw2, { 0: 0, 1: 0 }, 0);
  assert(bw2.sides[0]!.energy118 === 0, `depleted side zeroed (500-1000 → 0, got ${bw2.sides[0]!.energy118})`);
  assert(res2.sideDepleted, "sideDepleted === true (victory/defeat trigger)");

  // --- Suicide (same team): killer NOT credited ---
  const suikiller = defaultDeathActor(0); // team 0 (same as victim)
  const suivictim = defaultDeathActor(0, { cost4aa: 100 });
  const bwSui = defaultSourceBattleWork(2);
  bwSui.sides[0]!.energy118 = 1000;
  bwSui.sides[0]!.flag108 = 1;
  const resSui = killEventEnergyAndScoreAccounting(suikiller, suivictim, bwSui, { 0: 0, 1: 0 }, 0);
  assert(!resSui.killerCredited && suikiller.kills434 === 0, "same-team kill: killer NOT credited (no suicide score)");

  // --- Challenge mode 1: CPU team-0 victim does NOT deplete side energy ---
  const ck = defaultDeathActor(1);
  const cv = defaultDeathActor(0, { cost4aa: 500, heroFlag3e6: 1 }); // CPU team-0
  const cbw = defaultSourceBattleWork(2);
  cbw.sides[0]!.energy118 = 1000;
  const cres = killEventEnergyAndScoreAccounting(ck, cv, cbw, { 0: 0, 1: 0 }, 1);
  assert(cbw.sides[0]!.energy118 === 1000 && cres.energySubtracted === 0,
    "challenge mode 1: CPU team-0 victim does NOT subtract side energy");
  assert(!cres.killsRemainingDecremented, "challenge mode: killsRemaining NOT decremented (versus-only)");

  // --- Challenge mode 1: player team-0 victim DOES deplete ---
  const pk = defaultDeathActor(1);
  const pv = defaultDeathActor(0, { cost4aa: 500, heroFlag3e6: 0 }); // player team-0
  const pbw = defaultSourceBattleWork(2);
  pbw.sides[0]!.energy118 = 1000;
  const pres = killEventEnergyAndScoreAccounting(pk, pv, pbw, { 0: 0, 1: 0 }, 1);
  assert(pbw.sides[0]!.energy118 === 500 && pres.energySubtracted === 500,
    "challenge mode 1: player team-0 victim subtracts side energy");

  // --- Eligibility gate: non-borg victim early-returns (no accounting) ---
  const nbk = defaultDeathActor(1);
  const nbv = defaultDeathActor(0, { eligibility83: 1, cost4aa: 500 });
  const nbw = defaultSourceBattleWork(2);
  nbw.sides[0]!.energy118 = 1000;
  nbw.sides[0]!.flag108 = 1;
  const nbres = killEventEnergyAndScoreAccounting(nbk, nbv, nbw, { 0: 0, 1: 0 }, 0);
  assert(nbw.sides[0]!.energy118 === 1000 && nbres.energySubtracted === 0 && nbv.deaths435 === 0,
    "non-borg victim: early-return, no accounting");

  // --- Roster notification: ally-died (event 4) vs enemy-died (event 3) ---
  const rk = defaultDeathActor(1);
  const rv = defaultDeathActor(0, { cost4aa: 100, slot3e4: 2 });
  const rbw = defaultSourceBattleWork(2);
  rbw.sides[0]!.energy118 = 1000;
  rbw.sides[0]!.flag108 = 1;
  const roster = [
    { active: 1, team: 0, uid: "ally0" },   // ally of victim → event 4
    { active: 1, team: 0, uid: "victim" },  // the victim itself → skipped
    { active: 1, team: 1, uid: "enemy0" },  // enemy of victim → event 3
    { active: 0, team: 0, uid: "inactive" },// inactive → skipped
  ];
  const rres = killEventEnergyAndScoreAccounting(rk, rv, rbw, { 0: 0, 1: 0 }, 0, roster, "victim");
  const allyEvt = rres.rosterEvents.find((e) => e.eventType === 4);
  const enemyEvt = rres.rosterEvents.find((e) => e.eventType === 3);
  assert(allyEvt !== undefined && allyEvt.receiverTeam === 0 && allyEvt.victimSlot === 2,
    "roster: ally-died event 4 emitted to same-team slot");
  assert(enemyEvt !== undefined && enemyEvt.receiverTeam === 1 && enemyEvt.victimSlot === 2,
    "roster: enemy-died event 3 emitted to other-team slot");
  assert(rres.rosterEvents.length === 2, `roster: 2 events (victim + inactive skipped) — got ${rres.rosterEvents.length}`);
}

/* =============================================================================
 * INTEGRATION SPEC — how combat.ts / battle.ts should delegate the death transition
 * and kill-event accounting to sourceDeath.ts instead of the current enterDeath path.
 *
 * STATUS: sourceDeath.ts is a clean-room 1:1 port of zz_005bbc0_ (death state writes) +
 * zz_002f8dc_ (energy/score accounting). combat.ts and battle.ts are NOT edited per the
 * task. The current enterDeath(victim) in combat.ts does a DERIVED state flip ("death" +
 * alive=false); sourceDeath.ts ports the ROM's actual writes (+0x18=2, +0x5e0|=0x80000000,
 * +0x272|=0x443, death-type, state-timer, visibility clear, cue 0x2f) which the DERIVED
 * path collapses. The kill-event accounting (energy depletion + team score + roster
 * notification) is currently NOT in combat.ts at all — battle.ts's win/loss check would
 * delegate here.
 *
 * WIRING (drop-in for combat.ts enterDeath + the battle.ts win/loss accounting):
 *
 *   import {
 *     borgDeathEntry, killEventEnergyAndScoreAccounting,
 *     defaultDeathActor, defaultSourceBattleWork, type SourceDeathActor,
 *   } from "./sourceDeath.js";
 *
 *   // DEATH TRANSITION (replaces enterDeath):
 *   const target: SourceDeathActor = actorFromRuntime(victim);   // map BorgRuntime → offsets
 *   borgDeathEntry(target, battleWork, {
 *     onCueDispatch: (a, cue) => cueTableDispatch(a, cue),       // zz_006a750_/zz_006a6fc_
 *     onSlotSwap: () => swapToNextSlot(victim.slot),             // zz_008b640_ (Challenge)
 *     onDeathSubEntry: (a) => deathStateSubEntry(a),             // zz_005bccc_
 *   });
 *   // Then mirror target.state18/deathType6fe/... back onto BorgRuntime.
 *
 *   // KILL-EVENT ACCOUNTING (on the frame the victim's HP hits 0):
 *   const result = killEventEnergyAndScoreAccounting(
 *     actorFromRuntime(killer), actorFromRuntime(victim),
 *     battleWork, teamScores, challengeModeByte,
 *     rosterSlots, victim.uid,
 *   );
 *   if (result.sideDepleted) triggerWinLoss(victim.team);  // the victory/defeat branch
 *
 * REMAINING (honest TODOs, cited):
 *   - actorFromRuntime: BorgRuntime does not yet carry +0x6fe (deathType), +0x272
 *     (statusWord), +0x4aa (cost), +0x434/+0x435 (kills/deaths), +0x420/+0x424
 *     (costWon/lost). These ROM offsets need BorgRuntime fields (or a parallel results
 *     struct) before the port can run on live actors. Default neutral values are used in
 *     the self-tests.
 *   - SourceBattleWork.sides[].flagF6/flag108/flag109/killsRemaining10a: the per-side
 *     battle-work flags are not yet on BattleState. challengeMode comes from
 *     combat-config; the rest default to 0 (no energy subtract, no kill-counting) until
 *     the battle-work struct is ported.
 *   - The roster notification ring-buffer advance (chunk_0003.c:8305-8310) is a compiler
 *     artifact for (queueHead + 1) % 8; this port returns the events and lets the caller
 *     own the ring buffer rather than modeling the byte wrap inline.
 *   - zz_005f00c_ / zz_005efc4_ (pre-death cleanup) and zz_005bccc_ internals are cited
 *     deps, invoked via callbacks. The death STATE WRITES (+0x18/+0x5e0/+0x272/+0x6fe/
 *     +0x558) are the faithful core ported here.
 * ========================================================================== */
