/** Canonical, explicitly supplied battle-global cells. These interfaces add no
 * defaults, copied records, roster inference or source constructor. Team rows
 * are the SAME teamRows103 objects already used by cue0/normal actor control.
 * Row byte names use hexadecimal offsets from80433934+f4+3c*i. */
import type {BurstMeterState} from '../types.js';
export interface SourceBattleTeamRow extends Pick<BurstMeterState, 'charged'> {
  byte0?: number; byte1?: number; byte2?: number; byte3?: number;
  byte4?: number; byte5?: number; byte6?: number; byte7?: number; byte8?: number; byte9?: number;
  byte10?: number;
  threshold30?: number;
  /** Existing BurstMeterState owner for row+32, not a new raw halfword. */
  meter?: number;
}
export interface SourceBattleOuterGlobalFields {
  byte15d4?: number; byte66?: number; halfD6?: number;
  /** Borrowed SlotTableState names on this SAME80433934 owner. */
  activeMask?: number; slotTeam?: readonly number[];
  teamRows103?: readonly SourceBattleTeamRow[];
}
/** Existing ChallengeFlowState spelling for80433930+2. Explicit owner ingress,
 * not the challenge VM's constructor or a default controller selection. */
export interface SourceBattleSystemGlobals {controllerMask?: number}
