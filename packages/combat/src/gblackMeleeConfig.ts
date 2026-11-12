/** Source data for the separately admitted G BLACK action1/variant0 chain.
 * 8018de68 -> config8036564c ->177dd8. Its null chain callback means auxFE
 * continues to the next slot; it must never invoke NEO's variant6 redirect.
 */
export const G_BLACK_NEUTRAL_MELEE_CONFIG = Object.freeze({
  borgNumber: 0x62a, seedSlot: 13, proximityRange: 150, timerFrames: 20,
  decel: Math.fround(.95), chainCallback: null, altChainCallback: null,
});
export type GBlackMeleeSlot = 13 | 14 | 15;
export interface GBlackMeleeGate {
  frame: number;
  contact?: number;
  aux?: number;
  clearDash?: boolean;
  flags6e8?: number;
  flags6e9?: number;
  clearContactFlags?: boolean;
  /** Functional18d1d8 -> fc208(type5), not a cosmetic callback. */
  groundWave?: boolean;
}
export interface GBlackMeleeStreamConfig {
  sourceAddress: number;
  animSlot: number;
  hitKind: number;
  statusId: number;
  /** Original playAnim mode1, start0, ratebyte0; inherited host rate remains1. */
  blendByte: number;
  endFrame: number;
  dashStrength: number;
  gates: readonly Readonly<GBlackMeleeGate>[];
}
/** Original motion AOBJ ends, not exported sample counts. All descriptors
 * clear looping and all AOBJ flags are0. Every stream ends with mode1/-1. */
export const G_BLACK_MELEE_STREAMS: Readonly<Record<GBlackMeleeSlot, GBlackMeleeStreamConfig>> = {
  13: {
    sourceAddress: 0x80366f98, animSlot: 24, hitKind: 31, statusId: 0,
    blendByte: 4, endFrame: 35, dashStrength: 24,
    gates: [
      { frame: 5, contact: 0, aux: 0, flags6e8: 2, flags6e9: 1 },
      { frame: 17, contact: -1, aux: -1, flags6e8: 2, flags6e9: 0, clearDash: true },
      { frame: 19, contact: -1, aux: -1, flags6e8: 3, flags6e9: 2, clearContactFlags: true },
    ],
  },
  14: {
    sourceAddress: 0x80366858, animSlot: 4, hitKind: 17, statusId: 0,
    blendByte: 5, endFrame: 40, dashStrength: 32,
    gates: [
      { frame: 7, contact: 0, aux: 0, flags6e8: 2, flags6e9: 1 },
      { frame: 11, contact: 0, aux: 0, flags6e8: 2, flags6e9: 2 },
      { frame: 15, contact: -1, aux: -2, flags6e8: 3, flags6e9: 2, clearDash: true, clearContactFlags: true },
    ],
  },
  15: {
    sourceAddress: 0x80366f34, animSlot: 23, hitKind: 30, statusId: 127,
    blendByte: 4, endFrame: 70, dashStrength: 24,
    gates: [
      { frame: 11, contact: 0, aux: 0, flags6e8: 2, flags6e9: 1 },
      { frame: 19, clearDash: true },
      { frame: 22, groundWave: true },
      { frame: 29, contact: -1, aux: 0, flags6e8: 2, flags6e9: 2 },
      { frame: 33, contact: -1, aux: 0, flags6e8: 3, flags6e9: 0, clearContactFlags: true },
    ],
  },
};
export function gblackMeleeStreamConfig(slot: number): GBlackMeleeStreamConfig | undefined {
  return slot === 13 || slot === 14 || slot === 15 ? G_BLACK_MELEE_STREAMS[slot] : undefined;
}
