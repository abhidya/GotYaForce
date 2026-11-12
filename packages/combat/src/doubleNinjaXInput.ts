/** Scoped pl0003 input686f0/69b98. Descriptor+18c=120, ordinary X is a
 * press edge. The retained true-ready charge payload is still legacy, not a
 * clone-arming implementation. Input clock768 is separate from animation dt. */
import type {BorgRuntime} from './types.js';
const f=Math.fround;
export function stepDoubleNinjaXInput(b:BorgRuntime,held:boolean,activeType5=false){
  const s=b.doubleNinjaXInput??={held:false,pressEdge:false,releasedReady:false,warmup:0,charge:0,pending:false};
  s.pressEdge=held&&!s.held;s.held=held;s.releasedReady=false;
  const rate=b.sourceAmmoRefillRate??1;
  // Source686f0 reads admitted snapshot584, not this frame's command result.
  // The generic retained action has no ROM driver snapshot, so keep its identity
  // for the complete special state and drop it on recovery/interruption.
  const legacyActive=b.doubleNinjaLegacyChargeActive===true&&b.state==='special';
  if(!legacyActive)delete b.doubleNinjaLegacyChargeActive;
  // Armed7c8 sets58ebit20 in original6f7c0. No live clone producer is restored
  // here; the explicit input-disable seam permits source-level fixtures only.
  if(activeType5||legacyActive||((b.sourceDoubleNinjaInputBlock58e??0)&0x20)!==0){s.warmup=s.charge=0;}
  else if(!held){s.releasedReady=s.charge>=120;s.warmup=0;s.charge=Math.max(0,f(s.charge-f(2*rate)));}
  else if(s.warmup<10){s.warmup=f(s.warmup+1);}
  else s.charge=Math.min(120,f(s.charge+f(rate*(b.burstPaired?10:1))));
  s.pending=true;return s;
}
