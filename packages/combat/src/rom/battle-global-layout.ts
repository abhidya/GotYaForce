/** Canonical, explicitly supplied battle-global cells. These interfaces add no
 * defaults, copied records, roster inference or source constructor. Team rows
 * are the SAME teamRows103 objects already used by cue0/normal actor control.
 * Row byte names use hexadecimal offsets from80433934+f4+3c*i. */
import type {BurstMeterState} from '../types.js';
export interface SourceBattleTeamRow extends Pick<BurstMeterState, 'charged'> {
  byte0?: number; byte1?: number; byte2?: number; byte3?: number;
  byte4?: number; byte5?: number; byte6?: number; byte7?: number; byte8?: number; byte9?: number;
  byte10?: number;
  /** Raw unsigned storage for source lha/sth row+18; reached lazily. */
  half18?: number;
  /** Source row+38 pointer word.80027764 copies live slots2/1 then null/null;
   * this is NOT a leader table. Canonical pointer identities, no dereference. */
  pointer38?: symbol | null;
  threshold30?: number;
  /** Existing BurstMeterState owner for row+32, not a new raw halfword. */
  meter?: number;
}
export interface SourceBattleOuterGlobalFields {
  /** Actual post89554 counter, not host time or frame-entry tick. */
  wordB0?:number;
  byteC0?:number;byteC1?:number;byteC2?:number;byteC3?:number;byte15db?:number;
  byte15d4?: number; byte66?: number; halfD6?: number;
  /** SAME unsigned80433934+d9 cell already used by actor-matrix/ceiling. */
  byteD9?: number;
  /** SAME unsigned80433934+eb cell returned by recorded matched8008b480. */
  byteEB?: number;
  /** Borrowed SlotTableState names on this SAME80433934 owner. */
  activeMask?: number; slotTeam?: readonly number[];
  teamRows103?: readonly SourceBattleTeamRow[];
}
/** Existing ChallengeFlowState spelling for80433930+2. Explicit owner ingress,
 * not the challenge VM's constructor or a default controller selection. */
export interface SourceBattleSystemGlobals {
  controllerMask?:number;byte40?:number;byte29?:number;
  pointer14?:symbol|null;pointer18?:symbol|null;pointer1c?:symbol|null;pointer20?:symbol|null;
  byte0c?:number;byte0d?:number;byte0e?:number;byte0f?:number;
}
