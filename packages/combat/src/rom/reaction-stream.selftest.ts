import {createRomActor,type RomActor,type RomPartState} from './actor.js';
import {startStream,tickStream,resetStreamParts,updateReactionStream,REACTION_STREAM_LIMITS} from './stream-vm.js';
function check(ok:boolean,message:string):void {if(!ok)throw Error(`[reaction-stream] ${message}`);}
function bank():Uint8Array {
  const bytes=new Uint8Array(160),view=new DataView(bytes.buffer);
  for(let group=0;group<3;group++){
    const base=16+group*8;view.setInt16(group*2,base);
    for(let slot=0;slot<2;slot++){
      const start=48+(group*2+slot)*16;view.setInt16(base+slot*2,start-base);
      bytes.set([0,1,0,2,9,0,0,group*10+slot,0,0,255,255],start);
    }
  }
  return bytes;
}
export function runReactionStreamSelfTest():void {
  const a=createRomActor();a.sharedStreamBank=bank();a.dt=.5;
  const events:number[]=[];const ctx={onFireChild:(_:RomActor,v:number)=>{events.push(v);}};
  for(const group of [0x80,0x81,0x82]){
    startStream(a,15,group,0);tickStream(a,15,ctx);
    a.parts[1]!.prevTarget=group===0x80?REACTION_STREAM_LIMITS.light:REACTION_STREAM_LIMITS.other;
    const before=a.parts[0]!.streamPtr;
    check(updateReactionStream(a,group-256,0,ctx)==='continued','signed-byte identity at inclusive threshold');
    check(a.parts[0]!.streamPtr===before&&a.parts[0]!.frameClock===1,'continuation retains fractional countdown');
    updateReactionStream(a,group,0,ctx);
    check(a.parts[0]!.streamPtr===before,'one half-tick remains');
    updateReactionStream(a,group,0,ctx);
    check(a.parts[0]!.streamPtr===-1,'four fractional updates finish real stream');
    a.parts[1]!.prevTarget=(group===0x80?REACTION_STREAM_LIMITS.light:REACTION_STREAM_LIMITS.other)+.25;
    check(updateReactionStream(a,group,0,ctx)==='restarted','each group uses its own exact threshold');
  }
  startStream(a,15,0x81,0);tickStream(a,15,ctx);const n=events.length;
  check(updateReactionStream(a,0x81,1,ctx)==='restarted','changed slot restarts');
  check(a.parts[0]!.frameClock===0,'restart resets countdown clock');
  for(let i=0;i<3;i++)tickStream(a,15,ctx);check(events.length===n,'old countdown cannot leak into new slot');
  tickStream(a,15,ctx);check(events.at(-1)===11,'new slot executes');
  check(updateReactionStream(a,0x82,1,ctx)==='restarted','changed group restarts');
  a.parts[1]!.prevTarget=REACTION_STREAM_LIMITS.other+.5;
  check(updateReactionStream(a,0x82,1,ctx)==='restarted','same identity above threshold restarts');
  check(a.parts[1]!.prevTarget===0,'restart clears source comparison field');
  // The decision belongs to part1, not part0 or the actor frame clock.
  a.parts[0]!.prevTarget=10000;a.parts[1]!.prevTarget=0;a.parts[1]!.frameClock=10000;
  check(updateReactionStream(a,0x82,1,ctx)==='continued','only source1cfc governs comparison');
  resetStreamParts(a);const interrupted=events.length;
  check(updateReactionStream(a,0x82,1,ctx)==='continued'&&a.parts[0]!.streamPtr===-1,'interrupt retains identity but cannot resurrect cleared stream');
  check(events.length===interrupted,'interruption emits no child');
  a.sharedStreamBank=null;
  check(updateReactionStream(a,0x81,0,ctx)==='restarted'&&a.parts[0]!.streamPtr===-1,'absent bank delegates existing reset behavior');
  const host=a as RomActor & {onStartStream?:()=>boolean};host.onStartStream=()=>true;
  updateReactionStream(a,0x81,0,ctx);
  check(a.parts[0]!.streamPtr===Number.MAX_SAFE_INTEGER,'existing absent-bank host sentinel preserved');
  const b=createRomActor();b.sharedStreamBank=bank();startStream(b,15,0x80,0);
  check(updateReactionStream(b,0x80,0,ctx)==='continued','other actor identity remains independent');
  const retained=createRomActor();retained.sharedStreamBank=bank();retained.dt=1;
  startStream(retained,15,0x81,1);retained.sharedStreamBank=null;
  updateReactionStream(retained,0x81,1,ctx);updateReactionStream(retained,0x81,1,ctx);
  check(events.at(-1)===11&&retained.parts[0]!.streamPtr===-1,'continuation retains original byte backing after actor bank removal');
  const fresh=createRomActor();fresh.sharedStreamBank=bank();let rejected=false;
  try{updateReactionStream(fresh,0x81,0,ctx);}catch{rejected=true;}
  check(rejected&&fresh.parts[0]!.streamPtr===-1,'unknown source identity fails before mutation');
  b.parts[1]!.prevTarget=NaN;const untouched=b.parts[0]!.streamPtr;rejected=false;
  try{updateReactionStream(b,0x81,0,ctx);}catch{rejected=true;}
  check(rejected&&b.parts[0]!.streamPtr===untouched,'unsupported source clock rejects before mutation');
  b.parts[1]!.prevTarget=Number.MAX_VALUE;rejected=false;
  try{updateReactionStream(b,0x81,0,ctx);}catch{rejected=true;}
  check(rejected&&b.parts[0]!.streamPtr===untouched,'finite JS clock overflowing source float32 rejects before mutation');
  b.parts[1]!.prevTarget=0;
  const identity=b.parts[1] as RomPartState & {group:number;slot:number};
  for(const [group,slot] of [[256,0],[-129,0],[128,256],[128,-129],[128,1.5]]){
    identity.group=group!;identity.slot=slot!;rejected=false;
    try{updateReactionStream(b,0x81,0,ctx);}catch{rejected=true;}
    check(rejected&&b.parts[0]!.streamPtr===untouched,'out-of-byte metadata rejects before mutation');
  }
  identity.group=-128;identity.slot=0;
  check(updateReactionStream(b,0x80,0,ctx)==='continued','signed stored group compares as source byte');
  const p=b.parts[1] as RomPartState & {rate?:number};
  updateReactionStream(b,0x81,1,ctx);check(p.rate===REACTION_STREAM_LIMITS.rate,'source restart playback rate');
  console.log('[reaction-stream] PASS: identity/threshold, fractional continuation, rearm, interruption, isolation and absent banks');
}
