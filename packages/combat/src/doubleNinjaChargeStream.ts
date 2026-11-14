/** Inert Double pl0003 charged g4s2/3 stream reconstruction. Descriptor
 * 8033af78+2 admits parts0/1 (mask3). Interpreter: chunk_0006.c,
 * 4c050/4cd24/4cff4. Values below are independently encoded behavior, not
 * original asset bytes. No Battle wiring, projectiles, ammo, HIT or audio.
 * Only normal playback, rate1, requested mask15 and layerOverride0 are
 * admitted. In particular 4cff4 tests (1 << effectiveMask), not a part bit;
 * layered playback, missing animations and part1 suppression are unsupported.
 */
export interface DoubleNinjaChargePart {
  part:0|1; frame:number; elapsed:number; endFrame:number;
  blendMode:0|1; blendElapsed:number; blendTotal:number;
  stopped:boolean; ended:boolean; completed:boolean;
  wait:'eleven'|'end-minus-one'|'main-end'|'four'|'recovery-end';
  animation:readonly[number,number]; motion:readonly[number,number];
}
export interface DoubleNinjaChargeStream {
  slot:2|3; recovery:boolean; parts:[DoubleNinjaChargePart,DoubleNinjaChargePart];
  contact:number; flags6e8:number; flags6e9:number;
  /** Target1d74/75, saved blend source1d76/77 and displayed1d94/95.
   * Both Double hand joints belong to part0; no rendered pose is produced. */
  hands:[number,number]; oldHands:[number,number]|null; displayedHands:[number,number];
  dashStrength:number; control:number;
}
export interface DoubleNinjaChargeStreamEvent {
  part:0|1; gate?:number; completed?:true; recovery?:true;
}
function part(part:0|1,slot:2|3):DoubleNinjaChargePart {
  return {part,frame:0,elapsed:0,endFrame:40,blendMode:0,blendElapsed:0,blendTotal:0,
    stopped:false,ended:false,completed:false,wait:'eleven',animation:[4,slot],motion:[4,slot]};
}
/** Main metadata ff/ff resolves descriptor defaults0/1 via4d244. */
export function createDoubleNinjaChargeStream(slot:2|3,control=0,layerOverride=0):DoubleNinjaChargeStream {
  if(layerOverride!==0)throw Error('Double charged stream supports layerOverride0 only');
  return {slot,recovery:false,parts:[part(0,slot),part(1,slot)],
    contact:0,flags6e8:0,flags6e9:0,hands:[0,1],oldHands:null,displayedHands:[0,1],dashStrength:0,
    // Authored control ffff is a no-change sentinel, not a write of ffff.
    control};
}
const f=Math.fround;
function writeHands(s:DoubleNinjaChargeStream,value:number):void {
  // Opcode7/4c594 changes target and display, never the saved blend source.
  s.hands=[value,value];s.displayedHands=[value,value];
}
function displayRecoveryHands(s:DoubleNinjaChargeStream):void {
  // 4a8cc selects new at weight<=.5, old otherwise. Descriptor+42 hands
  // (joints7/11) both belong to part0's first11 entries in descriptor+8c.
  const p=s.parts[0];
  const weight=p.blendMode?f(1-f(p.blendElapsed/p.blendTotal)):0;
  s.displayedHands=[...(weight<=.5?s.hands:(s.oldHands??s.hands))];
}
function advance(p:DoubleNinjaChargePart,dt:number):void {
  p.elapsed=f(p.elapsed+dt);
  if(p.blendMode){
    p.blendElapsed=f(p.blendElapsed+dt);
    if(p.blendElapsed>=p.blendTotal){
      p.frame=f(p.frame+f(p.blendElapsed-p.blendTotal));
      if(p.frame>=p.endFrame)p.stopped=true;
      p.blendMode=0;
    }
  }else{
    if(!p.stopped)p.frame=f(p.frame+dt);
    if(p.frame>=p.endFrame){p.stopped=true;p.ended=true;}
  }
}
/** Each part tests its OLD clock. A non-play continuation advances once;
 * a completion hold never advances. No arbitrary dispatch-count gates. */
export function tickDoubleNinjaChargeStream(s:DoubleNinjaChargeStream,dt:number):DoubleNinjaChargeStreamEvent[] {
  const events:DoubleNinjaChargeStreamEvent[]=[];
  for(const p of s.parts){
    if(p.completed)continue;
    let gate:number|undefined;
    switch(p.wait){
      case 'eleven':
        if(p.frame>=11){p.wait='end-minus-one';gate=11;
          if(p.part===0){s.flags6e8=1;writeHands(s,1);}}
        break;
      case 'end-minus-one':
        if(p.frame>=p.endFrame-1){p.wait='main-end';gate=p.endFrame-1;
          if(p.part===0)writeHands(s,4);}
        break;
      case 'four':
        if(p.frame>=4){p.wait='recovery-end';gate=4;
          if(p.part===0){s.contact=1;s.flags6e8=0;s.flags6e9=0;}}
        break;
      case 'main-end': case 'recovery-end':
        if(p.ended){p.completed=true;events.push({part:p.part,completed:true});continue;}
        break;
    }
    if(gate!==undefined)events.push({part:p.part,gate});
    advance(p,dt);
  }
  if(s.recovery)displayRecoveryHands(s);
  return events;
}
/** Source 4cff4 executes the continuation immediately, resetting both holds.
 * The admitted caller invokes this after main completion and the15-unit ramp.
 * No recovery animation update occurs on this release call. */
export function releaseDoubleNinjaChargeStream(s:DoubleNinjaChargeStream,dt:number):DoubleNinjaChargeStreamEvent[] {
  if(s.recovery||s.parts.some(p=>!p.completed||p.wait!=='main-end'))
    throw Error('Double charged recovery release requires both main completion holds');
  s.recovery=true;
  // 487ec/4b94c snapshots old target before4d244 loads recovery metadata
  // 01/ff, resolving to1/1. Initial4a8cc may still display the old4/4.
  s.oldHands=[...s.hands];s.hands=[1,1];
  for(const p of s.parts){
    p.animation=[3,s.slot===2?10:11];
    p.motion=p.part===1&&s.slot===3?[0,8]:[2,25];
    p.endFrame=p.part===1&&s.slot===3?60:15;
    p.frame=0;p.elapsed=0;p.blendMode=1;p.blendElapsed=dt;p.blendTotal=5;
    p.stopped=false;p.ended=false;p.completed=false;p.wait='four';
  }
  displayRecoveryHands(s);
  return [{part:0,recovery:true},{part:1,recovery:true}];
}
