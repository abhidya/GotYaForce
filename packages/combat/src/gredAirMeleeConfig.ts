/** Exact admitted action1/variant4 profiles. RED18e148/config80365744,
 * BLACK18e170/config80365760 and NEO18e198/config8036577c call178394 without
 * another wrapper shift. Family engine config persists across stream aliases.
 */
import {GRED_AIR_MELEE_CONFIG,type GredAirMeleeConfig} from './families/gred-air-melee-engine.js';

export type GRedAirMeleeFamily='red'|'black'|'neo';
export interface GRedAirMeleeGate {
  gate:number;contact?:number;aux?:number;dashStrength?:number;faceGate?:number;
  flags6e8?:number;flags6e9?:number;clearContactFlags?:boolean;
}
export interface GRedAirMeleeStreamProfile {
  streamAddress:number;animSlot:number;hitKind:number;hitRecords:readonly number[];
  statusId:number;statusArg:number;
  blendByte:number;endFrame:number;initialFlags6e8:number;equipment:boolean;
  /** Absent preserves the previous group byte, as authored by NEO33/34 FF. */
  initialGroup?:number;
  initialDash:number;
  /** Original g0s14 mode1/blend15/start0, end1, terminal elapsed15. */
  recovery?:boolean;
  gates:readonly Readonly<GRedAirMeleeGate>[];
}
export interface GRedAirMeleeProfile extends GRedAirMeleeStreamProfile {
  borgNumber:number;engine:Readonly<GredAirMeleeConfig>;
  continuations?:Readonly<Record<number,GRedAirMeleeStreamProfile>>;
}
export const G_BLACK_AIR_MELEE_CONFIG:Readonly<GredAirMeleeConfig>=Object.freeze({
  seedSlot:24,proximityRange:300,pursuitTimer:20,recoveryTimer:0,
  driftScale:Math.fround(.95),launchSpeed:60,transitionScale:.25,recoveryDamping:Math.fround(.9),
});
export const NEO_G_RED_AIR_MELEE_CONFIG:Readonly<GredAirMeleeConfig>=Object.freeze({
  seedSlot:33,proximityRange:300,pursuitTimer:20,recoveryTimer:4,
  driftScale:Math.fround(.9),launchSpeed:40,transitionScale:.25,recoveryDamping:Math.fround(.9),
});
/** Stream35 is the exact same original pointer as BLACK24. It does NOT carry
 * a BLACK engine configuration: NEO continuation remains speed40/brake4/.9. */
const BLACK_TERMINAL_STREAM:GRedAirMeleeStreamProfile={
  streamAddress:0x80366e74,animSlot:21,hitKind:6,hitRecords:[6,19],
  statusId:25,statusArg:255,
  blendByte:5,endFrame:50,initialFlags6e8:2,equipment:true,initialGroup:0,initialDash:0,
  gates:[
    {gate:13,contact:1,aux:0,flags6e8:2,flags6e9:0},
    {gate:14,contact:0,aux:0,flags6e8:2,flags6e9:1},
    {gate:19,dashStrength:-1,faceGate:0},
    {gate:23,contact:0,aux:0,flags6e8:2,flags6e9:2},
    {gate:27,contact:-1,aux:0,flags6e8:3,flags6e9:0,clearContactFlags:true},
  ],
};
const NEO_FIRST_STREAM:GRedAirMeleeStreamProfile={
  streamAddress:0x80366c00,animSlot:19,hitKind:24,hitRecords:[39],
  statusId:25,statusArg:255,
  blendByte:2,endFrame:30,initialFlags6e8:2,equipment:true,initialDash:24,recovery:true,
  gates:[
    {gate:3,contact:1,aux:0,flags6e8:2,flags6e9:0},
    {gate:5,contact:0,aux:0,flags6e8:2,flags6e9:1},
    {gate:14,contact:-1,aux:-1,flags6e8:2,flags6e9:2},
  ],
};
const NEO_SECOND_STREAM:GRedAirMeleeStreamProfile={
  ...NEO_FIRST_STREAM,streamAddress:0x80366c6c,animSlot:20,hitKind:25,hitRecords:[40],endFrame:45,
  gates:[...NEO_FIRST_STREAM.gates.slice(0,2),
    {gate:15,contact:-1,aux:-1,flags6e8:2,flags6e9:2}],
};
/** Original AOBJ ends, not baked frame counts. All play mode1/start0/rate0
 * (retained host rate1) and clear looping. RED/BLACK and NEO35 end directly;
 * NEO33/34 continue on accepted contact+retap or play their recovery clip.
 * None contains a functional child callback.
 */
export const GRED_AIR_MELEE_PROFILES:Readonly<Record<GRedAirMeleeFamily,GRedAirMeleeProfile>>={
  red:{
    borgNumber:0x615,engine:GRED_AIR_MELEE_CONFIG,streamAddress:0x80366edc,
    animSlot:22,hitKind:18,hitRecords:[26,27],blendByte:5,endFrame:30,initialFlags6e8:0,equipment:false,
    statusId:25,statusArg:255,
    initialGroup:0,initialDash:0,
    gates:[
      {gate:10,contact:1,aux:0},{gate:15,dashStrength:24,faceGate:1},
      {gate:20,dashStrength:-1,faceGate:0},{gate:26,contact:-1,aux:0,clearContactFlags:true},
    ],
  },
  black:{
    ...BLACK_TERMINAL_STREAM,borgNumber:0x62a,engine:G_BLACK_AIR_MELEE_CONFIG,
  },
  neo:{
    ...NEO_FIRST_STREAM,borgNumber:0x629,engine:NEO_G_RED_AIR_MELEE_CONFIG,
    continuations:{34:NEO_SECOND_STREAM,35:BLACK_TERMINAL_STREAM},
  },
};
export function gredAirMeleeStreamProfile(family:GRedAirMeleeFamily,slot:number):GRedAirMeleeStreamProfile|undefined {
  const profile=GRED_AIR_MELEE_PROFILES[family];
  return slot===profile.engine.seedSlot?profile:profile.continuations?.[slot];
}
