import {createRomActor} from './actor.js';
import {createSourceActorInputPrefixRuntime} from './actor-input-prefix.js';
import {createSourceInputAngleRuntime} from './source-input-angle.js';
function check(ok: boolean, why: string): void {if (!ok) throw Error(`[actor-input-axis-test] ${why}`);}
function equal(a: unknown, b: unknown, why: string): void {check(Object.is(a,b),`${why}: got${a}, expected${b}`);}
function rejects(run: () => unknown, fragment: string): void {
  let error=''; try {run();} catch(e) {error=String(e);} check(error.includes(fragment),`expected${fragment}, got${error||'success'}`);
}
function fixture(initial: Record<string,number> = {}) {
  const id=Symbol('axis'), actual=Object.assign(createRomActor(),{statusWord5bc:0});
  actual.inputHeld5d8=0xabcd; actual.inputEdge5d4=0xffffffff;
  const borg={downGaugeBase:100,downGauge:0,paramTier:{tier:16,deltaAccum:0,timerFrames:0},sourceArrowMash749:99};
  const world={getActualActor:()=>actual}, gauges={getActualActor:()=>actual,getActualBorg:()=>borg};
  const processor={gqr4:0x60006,gqr0:0,gqr5:0x70007,fpscrControl:0};
  const data={scale8043707c:10430.3779296875,pi8043cd78:Math.PI,negativeHalfPi8043cd88:-Math.PI/2,
    halfPi8043cd90:Math.PI/2,direction80433928:[2,10,8,9,1,5,4,6]};
  const angular=createSourceInputAngleRuntime({processor,data});
  const runtime=createSourceActorInputPrefixRuntime({world,gauges,processor,angular});
  runtime.bindActor(id,{ushort5b8:0,stickX5ca:0,stickY5cb:0,byte5fc:0,byte5fd:0,byte5fe:0,byte5ff:0,...initial});
  return {id,actual,borg,world,gauges,processor,data,angular,runtime,binding:runtime.getActorBinding(id),run:()=>runtime.updateActor(id)};
}
export function runActorInputAxisSelfTests(): void {
  // Independent caller oracle: state transitions depend on returned byte, not
  // guessed browser directions. Test below/at/between/beyond both thresholds.
  for (const [dx,dy,mask] of [[1,0,2],[0,1,8],[-1,0,1],[0,-1,4]] as const) {
    for (const magnitude of [0,1,19,20,21,51,52,53,127,128]) {
      if (magnitude===128 && (dx>0||dy>0)) continue;
      for (const flags of [0,1,2,3]) for (const held of [0,1,2,4,8,15,0x10,0xabcd,0xffff]) {
        const x=fixture({stickX5ca:dx*magnitude,stickY5cb:dy*magnitude,byte5fc:flags});
        x.actual.inputHeld5d8=held;
        let wantHeld=held, wantFlags=flags, timer=0;
        if (!(flags&1) && magnitude>=20) {wantFlags|=1;wantHeld=(wantHeld&0xfff0)|mask;timer=mask&12?3:2;}
        if (!(flags&2) && magnitude>=52) {wantFlags|=2;wantHeld&=0xff0f;wantHeld|=(wantHeld&mask)<<4;timer=20;}
        rejects(x.run,'800685f8');
        equal(x.binding.byte5fc,wantFlags,'axis latch bits'); equal(x.actual.inputHeld5d8,wantHeld,'source clear/reload/AND expression');
        equal(x.binding.byte5fd,timer?timer-1:0,'new direction timer decremented in same call');
        equal(x.borg.sourceArrowMash749,0,'actual subsequent popcount'); equal(x.actual.inputEdge5d4,0,'only after completed68980');
      }
    }
  }
  {
    const x=fixture({stickX5ca:52}); x.actual.inputHeld5d8=0;
    rejects(x.run,'800685f8'); equal(x.actual.inputHeld5d8,0x22,'firstgate contributes low bit used by second');
    const y=fixture({stickX5ca:52,byte5fc:1}); y.actual.inputHeld5d8=0;
    rejects(y.run,'800685f8'); equal(y.actual.inputHeld5d8,0,'second does not synthesize unlatched lowbit');
  }
  // Explicit caller-provided table can legitimately yield zero or a wider byte.
  for (const byte of [0,1,0x80,0xff]) {
    const x=fixture({stickX5ca:52}); x.data.direction80433928[0]=byte;
    x.actual.inputHeld5d8=0; rejects(x.run,'800685f8');
    equal(x.binding.byte5fc,byte?3:0,'real zero result skips stores');
    const afterFirst=byte, afterClear=afterFirst&0xff0f;
    equal(x.actual.inputHeld5d8,byte?afterClear|((afterClear&byte)<<4):0,'byte width retained, no nibble default');
  }
  for (const fault of ['held','timer']) {
    const x=fixture({stickX5ca:20});
    Object.defineProperty(fault==='held'?x.actual:x.binding,fault==='held'?'inputHeld5d8':'byte5fd',{writable:false});
    rejects(x.run,'non-writable'); equal(x.binding.byte5fc,1,'late first-direction failure retains latch');
    equal(x.actual.inputHeld5d8,fault==='held'?0xabcd:0xabc2,'late timer failure retains source low-nibble result');
    equal(x.actual.inputEdge5d4,0xffffffff,'no edge clear before fullinput return'); equal(x.borg.sourceArrowMash749,99,'no late popcount');
  }
  {
    const x=fixture({stickX5ca:52,byte5fc:1}); Object.defineProperty(x.binding,'byte5fd',{writable:false});
    rejects(x.run,'non-writable'); equal(x.binding.byte5fc,3,'second latch retained');
    equal(x.actual.inputHeld5d8,0xab0d,'second preserves genuine H&mask zero');
    const y=fixture({stickX5ca:52,stickY5cb:52}); rejects(y.run,'80239a78');
    equal(y.binding.byte5fc,0,'diagonal does not fabricate returned direction'); equal(y.actual.inputHeld5d8,0xabcd,'diagonal no held writes');
  }
  {
    const x=fixture({stickX5ca:20}); x.processor.gqr5=0;
    rejects(x.run,'GQR5'); equal(x.binding.byte5fc,0,'unsupported store profile before direction result');
    x.processor.gqr5=0x70007; x.processor.fpscrControl=1;
    rejects(x.run,'FPSCR'); equal(x.actual.inputEdge5d4,0xffffffff,'unsupported rounding cannot reach input writes');
  }
  {
    const x=fixture();
    rejects(()=>createSourceActorInputPrefixRuntime({world:x.world,gauges:x.gauges,processor:x.processor,angular:{...x.angular}}),'genuine');
    rejects(()=>createSourceActorInputPrefixRuntime({world:x.world,gauges:x.gauges,processor:{...x.processor},angular:x.angular}),'same explicit processor');
    rejects(()=>createSourceActorInputPrefixRuntime({world:x.world,gauges:x.gauges,angular:x.angular}),'same explicit processor');
  }
  for (const owner of ['actual','borg','binding','processor','data'] as const) {
    const x=fixture({stickX5ca:20});
    x.data.direction80433928=x[owner] as unknown as number[];
    rejects(x.run,'owner alias'); equal(x.binding.byte5fc,0,'late shared-storage alias refused before source writes');
    equal(x.actual.inputEdge5d4,0xffffffff,'alias does not partially consume input stores');
  }
  console.log('[actor-input-axis] PASS: bounded real axis returns, exact caller gate/reload stores, both thresholds, partial failures and unchanged missing-option boundaries; diagonal/fulltick/input provenance remain unsupported');
}
