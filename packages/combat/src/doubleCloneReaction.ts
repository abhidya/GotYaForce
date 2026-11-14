/** Inert first-entry Double Ninja reaction/reset classifier. No Battle wiring.
 * Evidence: chunk_0003.c:6221–6263 (collision tail); chunk_0007.c:
 * 3930–4077 (5c15c/5c290), 4159–4212 (5c694), 4233–4607 (handlers),
 * 5644–5795 (5ee0c/5ef08/5f00c). Fresh original table802d35a4:
 * 1=5c810,2=5c95c,3/4=5ca80,5/6=5cc00,7=5ce14,8=5d0a8.
 * Double descriptor8033af78+4 selects class591=0, gate5c4a4→5f00c.
 * This models only bit0x02000000, not the other control/state/animation writes.
 */
export interface DoubleCloneReactionInput {
  /** Capture BEFORE host hit/down/control mutation, not from a host reaction name. */
  readonly control5e0: number;
  /** Raw accumulated bytes AFTER the entire source collision frame. */
  readonly flags6fd: number;
  readonly flags1da: number;
  readonly heavy599: number;
  /** Final collision-frame signed short BEFORE source3d3e8 or any host stagger reset. */
  readonly downGauge6c6: number;
  readonly borg3e8: number;
  readonly descriptorClass591: number;
  readonly pairedState4a0: number;
  readonly alive: boolean;
  /** Active ordinary primary actor, no global status/forced-move/secondary branch. */
  readonly ordinaryCollisionTail: boolean;
  readonly frameAggregationComplete: boolean;
  readonly alreadyReacting: boolean;
  readonly entry540: number;
  readonly phase544: number;
  /** Actual (actor3e5 & globald2)===0, not an assumed scheduler opportunity. */
  readonly immediateDispatchPermitted: boolean;
  /** Result of the source5ef08 probe called by5ee0c; null means unknown. */
  readonly recoveryTerrain5ef08: boolean | null;
}
export type DoubleCloneReactionResult =
  | {type:'unsupported';reason:string}
  | {type:'reset';enteredReaction:true;resetBitAfterDispatch:true;
      reason:'standard-5-to-8'|'recovery-terrain'}
  | {type:'preserve';enteredReaction:boolean;resetBitAfterDispatch:boolean;
      reason:'no-admission'|'standard-1-to-4'};

const RESET_BIT = 0x02000000;
const byte = (n:number):boolean => Number.isInteger(n) && n >= 0 && n <= 0xff;

/** Pure proof of the bit at the reaction boundary, not a command to clear arm7c8.
 * A no-admission result leaves the EXISTING bit intact, even when it is set.
 * Thus `preserve` alone does NOT prove clone survival. The eventual owner6f88c
 * post-hook must consume the bit at its real boundary and preserve offset7b0.
 * Unsupported results expose no invented bit value and must not mutate an actor.
 */
export function classifyDoubleCloneReaction(input:DoubleCloneReactionInput):DoubleCloneReactionResult {
  const unsupported = (reason:string):DoubleCloneReactionResult => ({type:'unsupported',reason});
  if (!Number.isInteger(input.control5e0) || input.control5e0 < 0 || input.control5e0 > 0xffffffff ||
    !byte(input.flags6fd) || !byte(input.flags1da) || !byte(input.heavy599) ||
    !Number.isInteger(input.downGauge6c6) || input.downGauge6c6 < -32768 || input.downGauge6c6 > 32767) {
    return unsupported('invalid-source-fields');
  }
  if (input.frameAggregationComplete !== true) return unsupported('incomplete-collision-frame');
  if (input.borg3e8 !== 3 || input.descriptorClass591 !== 0 || input.alive !== true ||
    input.pairedState4a0 !== 0 || input.ordinaryCollisionTail !== true) {
    return unsupported('actor-or-tail-outside-scope');
  }
  // Existing reaction, freeze/other upper states, and death are not first-entry proofs.
  if (input.alreadyReacting !== false || (input.control5e0 & 0x9d000000) !== 0 ||
    input.entry540 !== 0 || input.phase544 !== 0) return unsupported('not-ordinary-first-entry');
  if ((input.flags1da & 0xfe) !== 0) return unsupported('status-or-healing-override');
  if (input.heavy599 !== 0) return unsupported('heavy-override');
  if ((input.flags6fd & 0x40) !== 0) return unsupported('falling-rehit-history');

  // Tail1da bit0 encloses this path.5c290 itself also requires6fd!=0.
  const admitted = (input.flags1da & 1) !== 0 && input.flags6fd !== 0 &&
    (input.downGauge6c6 < 1 || (input.flags6fd & 0x82) === 0x82);
  if (!admitted) return {type:'preserve',enteredReaction:false,
    resetBitAfterDispatch:(input.control5e0 & RESET_BIT) !== 0,reason:'no-admission'};
  if (input.immediateDispatchPermitted !== true) return unsupported('deferred-dispatch');

  //5f00c lower direction bits only choose among1..4 or5..8; no host threshold.
  //5c694→5c15c clears the bit first, then phase0 handlers5..8 set it again.
  if ((input.flags6fd & 2) !== 0 || (input.control5e0 & 0x02000040) !== 0) {
    return {type:'reset',enteredReaction:true,resetBitAfterDispatch:true,reason:'standard-5-to-8'};
  }
  //1..4 all run5ee0c after their phase0 setup. Unknown terrain is not false.
  if (input.recoveryTerrain5ef08 === true) {
    return {type:'reset',enteredReaction:true,resetBitAfterDispatch:true,reason:'recovery-terrain'};
  }
  if (input.recoveryTerrain5ef08 !== false) return unsupported('unknown-recovery-terrain');
  return {type:'preserve',enteredReaction:true,resetBitAfterDispatch:false,reason:'standard-1-to-4'};
}
