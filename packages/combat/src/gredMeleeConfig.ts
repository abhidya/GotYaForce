/** G RED fresh grounded action1/variant0:18de34 ->177dd8/config80365634.
 * Same-family continuation is slots0/1/2. Both callbacks are null; the third
 * swing's aux0 terminates the chain. No opcode09/11 child callback exists here.
 */
import { GRED_ACTION1_VARIANT0_CONFIG } from './families/shared-melee-gred.js';
export const G_RED_NEUTRAL_MELEE_CONFIG = Object.freeze({
  borgNumber:0x615,seedSlot:GRED_ACTION1_VARIANT0_CONFIG.seedSlot,
  proximityRange:GRED_ACTION1_VARIANT0_CONFIG.proximityRange,
  timerFrames:GRED_ACTION1_VARIANT0_CONFIG.timerFrames,
  decel:GRED_ACTION1_VARIANT0_CONFIG.decel!,chainCallback:null,altChainCallback:null,
});
export type GRedMeleeSlot=0|1|2;
export interface GRedMeleeStreamConfig {
  sourceAddress:number;animSlot:number;hitKind:number;statusId:number;
  blendMode:1|2;blendByte:number;endFrame:number;dashStrength:number;initialContact:number;
  /** Raw0c014000 sets57b40; no synthetic launch or status meaning. */
  setFlags57b40?:boolean;
  gates:readonly {frame:number;contact?:number;aux?:number;clearDash?:boolean;
    flags6e8?:number;flags6e9?:number;clearContactFlags?:boolean}[];
}
/** Original AOBJ ends27/35/35, descriptor loop-clear flag1 and AOBJflags0.
 * All start atframe0; ratebyte0 retains the existing rate (host adapter binds1).
 * Mode2 waits are absolute animation frames; terminalmode1/-1 waits for end.
 */
export const G_RED_MELEE_STREAMS:Readonly<Record<GRedMeleeSlot,GRedMeleeStreamConfig>>={
  0:{sourceAddress:0x803666d8,animSlot:0,hitKind:1,statusId:0,
    blendMode:1,blendByte:5,endFrame:27,dashStrength:24,initialContact:0,
    gates:[{frame:5,contact:1,aux:0,flags6e8:0,flags6e9:0},
      {frame:10,contact:-1,aux:-1,flags6e8:0,flags6e9:0,clearDash:true,clearContactFlags:true}]},
  1:{sourceAddress:0x80366720,animSlot:1,hitKind:2,statusId:0,
    blendMode:2,blendByte:4,endFrame:35,dashStrength:24,initialContact:0,
    gates:[{frame:5,contact:1,aux:0,flags6e8:0,flags6e9:0},
      {frame:13,contact:-1,aux:-1,flags6e8:0,flags6e9:0,clearDash:true,clearContactFlags:true}]},
  // Status25/arg255 is forwarded to onArmHit. Original conditional43d/6f8/6f9
  // storage and downstream consumer remain unbound; it is not a defender debuff.
  2:{sourceAddress:0x803668b0,animSlot:15,hitKind:20,statusId:25,
    blendMode:1,blendByte:5,endFrame:35,dashStrength:32,initialContact:1,setFlags57b40:true,
    gates:[{frame:12,clearDash:true},
      {frame:19,contact:-1,aux:0,flags6e8:0,flags6e9:0,clearContactFlags:true}]},
};
export function gredMeleeStreamConfig(slot:number):GRedMeleeStreamConfig|undefined {
  return slot===0||slot===1||slot===2?G_RED_MELEE_STREAMS[slot]:undefined;
}
