import {createRomActor} from './rom/actor.js';
import {prepareSwitchingX,stepSwitchingX,startSwitchingXStream,tickSwitchingXStreamPart} from './switchingX.js';
import type {StreamContext} from './rom/stream-vm.js';
function check(value:unknown,message:string):asserts value{if(!value)throw Error(`[switchingX] ${message}`);}
export function runSwitchingXSelfTest():void{
  for(const air of [false,true]){
    const a=createRomActor();a.borgNumber=9;a.dt=1;a.weaponPartMask=15;a.controlWord=1|(air?0x40:0);
    a.pos={x:100,y:10,z:0};a.targetCache5e8={x:90,y:10,z:0};
    const animations:number[][]=[],shots:number[][]=[],debits:number[][]=[];
    const ctx:StreamContext={onPlayAnim:(_a,g,s)=>{animations.push([g,s]);},
      onAllocateResource:(_a,slot,count,mode)=>{debits.push([slot,count,mode??0]);return true;},
      onFamilyProjectile:(_a,address,row)=>{shots.push([address,row]);}};
    const s=prepareSwitchingX(a,null,null);
    (a as typeof a&{onStartStream?:(group:number,slot:number,mask:number)=>boolean}).onStartStream=(g,slot,m)=>startSwitchingXStream(a,g,slot,m,ctx);
    (a as typeof a&{onTickStreamPart?:(i:number)=>boolean}).onTickStreamPart=i=>tickSwitchingXStreamPart(a,i,ctx);
    stepSwitchingX(a,ctx);
    check(a.pos.x===Math.fround(100+Math.fround(10*Math.fround(.95))),'own history f32 phase0 carry');
    check(animations[0]?.[0]===4&&animations[0]?.[1]===(air?3:2),'source metadata, not raw MOT slot');
    check(s.stream?.slot===(air?5:4),'source ground/air stream selected');
    for(let i=0;i<27;i++)stepSwitchingX(a,ctx);
    check(shots.length===0,'no child before absolute release25 and blend2');
    stepSwitchingX(a,ctx);
    check(Number(shots.length)===1&&shots[0]![0]===0x801e29fc&&shots[0]![1]===0,'one authored release');
    check(debits.length===1&&debits[0]!.join(',')==='2,1,1','source cell2 single debit mode1');
    check(s.fireCount===1&&s.callbackCount===1,'single release bookkeeping');
  }
  {
    const a=createRomActor();a.borgNumber=9;a.fbPhaseSlots[0]=1;a.contactP0=1;
    const s=prepareSwitchingX(a,null,null);let count=0;
    const ctx:StreamContext={onAllocateResource:()=>false,onFamilyProjectile:()=>{count++;}};
    stepSwitchingX(a,ctx);
    check(s.resourceDenied&&count===0&&a.fbPhaseSlots[0]===2,'failed debit advances recovery without fake payload');
  }
  console.log('[switchingX] PASS: source own motion, descriptors, release debit and denied payload');
}
