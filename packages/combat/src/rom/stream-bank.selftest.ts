import { createRomActor, type RomActor } from './actor.js';
import { startStream, tickStream, resetStreamParts, resolveStreamOffset } from './stream-vm.js';
function check(ok:boolean, message:string):void {if(!ok)throw Error(`[stream-bank] ${message}`);}
function bank(variant:number, group=0, base=8, offset=4):Uint8Array {
  const bytes=new Uint8Array(64);
  const view=new DataView(bytes.buffer);
  view.setInt16(group*2,base);view.setInt16(base,offset);
  // Wait one extra tick, then real fireChild followed by terminal.
  bytes.set([0,1,0,2,9,0,0,variant,0,0,255,255],base+offset);
  return bytes;
}
export function runStreamBankSelfTest():void {
  const a=createRomActor();a.dt=1;
  a.familyStreamBank=bank(11);a.sharedStreamBank=bank(22,1,16,8);
  const events:number[]=[];const ctx={onFireChild:(_:RomActor,v:number)=>{events.push(v);}};
  startStream(a,1,0,0);startStream(a,2,0x81,0);
  check(a.parts[0]!.streamPtr===12&&a.parts[1]!.streamPtr===24,'bank-relative group and slot offsets');
  tickStream(a,3,ctx);check(events.length===0,'both parts suspend at wait');
  a.familyStreamBank=bank(33);a.sharedStreamBank=null;
  tickStream(a,3,ctx);
  check(events.join(',')==='11,22','mixed parts retain original bank through continuation and actor bank replacement');
  check(a.parts[0]!.streamPtr===-1&&a.parts[1]!.streamPtr===-1,'both scripts terminate');
  startStream(a,2,0,0);tickStream(a,2,ctx);tickStream(a,2,ctx);
  check(events.join(',')==='11,22,33','rearm selects replacement family backing for formerly shared part');
  a.sharedStreamBank=bank(44,1,16,8);startStream(a,2,0x81,0);
  resetStreamParts(a);a.parts[1]!.streamPtr=24;tickStream(a,2,ctx);
  check(events.length===3&&a.parts[1]!.frameClock===0,'reset discards provenance; manually restored offset fails closed');
  startStream(a,2,0x81,0);a.sharedStreamBank=null;startStream(a,2,0x81,0);
  check(a.parts[1]!.streamPtr===-1,'absent selected bank clears selected part');
  a.parts[1]!.streamPtr=24;tickStream(a,2,ctx);check(events.length===3,'absent-bank reset cannot reuse stale shared provenance');
  const host=a as RomActor & {onStartStream?:()=>boolean};host.onStartStream=()=>true;
  startStream(a,2,0x81,0);tickStream(a,2,ctx);
  check(a.parts[1]!.streamPtr===Number.MAX_SAFE_INTEGER&&events.length===3,'absent decoded-host sentinel never reads family bank');
  const fresh=createRomActor();fresh.familyStreamBank=bank(55);fresh.parts[0]!.streamPtr=12;
  tickStream(fresh,1,ctx);tickStream(fresh,1,ctx);check(events.length===3,'unbound manual offsets fail closed');
  fresh.familyStreamBank=new Uint8Array(1);
  check(resolveStreamOffset(fresh,0,0)===-1,'truncated group table rejected');
  fresh.familyStreamBank=bank(66);check(resolveStreamOffset(fresh,0,-1)===-1,'negative slot rejected');
  const rearmed=createRomActor();rearmed.dt=1;
  rearmed.familyStreamBank=bank(100);rearmed.sharedStreamBank=bank(101,1);
  // Leave one tick cached from an old two-tick wait; the new bank waits four.
  rearmed.sharedStreamBank[8+4+3]=4;
  startStream(rearmed,1,0,0);tickStream(rearmed,1,ctx);
  const countBeforeRearm=events.length;
  startStream(rearmed,1,0x81,0);tickStream(rearmed,1,ctx);
  check(events.length===countBeforeRearm,'rearm discards old countdown instead of firing new bank early');
  tickStream(rearmed,1,ctx);tickStream(rearmed,1,ctx);
  check(events.length===countBeforeRearm,'new bank retains its own full countdown');
  tickStream(rearmed,1,ctx);check(events.at(-1)===101,'new countdown completes on fourth tick');
  const sharedOnly=createRomActor();sharedOnly.familyStreamBank=null;sharedOnly.sharedStreamBank=bank(88,1);
  startStream(sharedOnly,1,0x81,0);tickStream(sharedOnly,1,ctx);tickStream(sharedOnly,1,ctx);
  check(events.at(-1)===88,'shared script executes without a family bank');
  const subarray=bank(99,1);const backing=new Uint8Array(96);backing.set(subarray,12);
  sharedOnly.sharedStreamBank=backing.subarray(12,76);
  startStream(sharedOnly,1,0x81,0);tickStream(sharedOnly,1,ctx);tickStream(sharedOnly,1,ctx);
  check(events.at(-1)===99,'pointer offsets are relative to selected byte view, not backing buffer');
  // Signed slot displacement: group table at16 points backward to byte8.
  const signed=new Uint8Array(40);const view=new DataView(signed.buffer);view.setInt16(2,16);view.setInt16(16,-8);
  signed.set([9,0,0,77,0,0,255,255],8);fresh.sharedStreamBank=signed;
  startStream(fresh,1,0x81,0);tickStream(fresh,1,ctx);check(events.at(-1)===77,'signed slot displacement executes selected shared bytes');
  console.log('[stream-bank] PASS: mixed banks, continuation, rearm, reset, missing banks and pointer provenance');
}
