import {createDoubleCloneLifecycle, guardDoubleCloneOwner, tickDoubleCloneLifecycle,
  type DoubleCloneLifecycleHooks, type DoubleCloneLifecycleState} from './doubleCloneLifecycle.js';
function assert(value: unknown, message: string): asserts value {
  if (!value) throw Error(`[doubleCloneLifecycle] ${message}`);
}
function fixture() {
  const owner = {borg3e8:3,invalid662:0,arm7c8:0,offset7b0:{x:150,y:2,z:-3},action:2};
  const source = {borg3e8:3,borg94:3,player96:2,owner90:owner};
  let allocations=0;
  const state=createDoubleCloneLifecycle(source,0,()=>{allocations++;return true;});
  assert(state,'Double allocation succeeds while unarmed');
  const calls:string[]=[];
  const hooks:DoubleCloneLifecycleHooks={
    initialize141b90:s=>calls.push(`init:${s.phase18}`),
    retire89444:s=>calls.push(`retire-a:${s.phase18}:${s.visibility82}`),
    retire8aff0:s=>calls.push(`retire-b:${s.phase18}:${s.visibility82}`),
    free88e50:()=>calls.push('free'),
  };
  return {owner,source,state,calls,hooks,allocations,tick:()=>tickDoubleCloneLifecycle(state,hooks)};
}
export function runDoubleCloneLifecycleSelfTest(): void {
  {
    const t=fixture();
    assert(t.allocations===1 && t.state.owner90===t.owner,'one child links to the original owner');
    t.tick();
    assert(t.calls.join('|')==='init:1' && t.state.visibility82===0,'unarmed child initializes but stays hidden');
    for(const arm of [1,2,-1,255]) {
      t.owner.arm7c8=arm;t.tick();
      assert(Number(t.state.visibility82)===0x43,'all nonzero arm bytes use captured player96+0x41');
    }
    t.owner.arm7c8=0;t.tick();
    assert(t.state.visibility82===0 && t.state.phase18===1,'clearing arm hides rather than destroys the child');
    t.owner.arm7c8=1;t.source.player96=8;t.source.borg94=9;t.tick();
    assert(Number(t.state.visibility82)===0x43 && t.state.capturedBorg94===3,'allocation metadata is captured, not refreshed');
    for(const action of [0,2,3,5,9]) {
      t.owner.action=action;
      for(let i=0;i<500;i++) t.tick();
    }
    assert(t.owner.arm7c8===1 && t.owner.offset7b0.x===150 && t.owner.offset7b0.y===2 &&
      t.owner.offset7b0.z===-3,'ordinary action changes and elapsed dispatches never clear arm or mutate offset');
    assert(t.calls.join('|')==='init:1','persistent child has no independent timer or repeated allocation/init');
    assert(!('hp' in t.state) && !('timer' in t.state) && !('offset7b0' in t.state),'child stores lifecycle, not independent combat/offset state');
  }
  for(const phase of [0,1]) for(const cause of ['invalid','borg'] as const) {
    const t=fixture();t.state.phase18=phase;t.state.visibility82=0x43;
    if(cause==='invalid')t.owner.invalid662=1;else t.owner.borg3e8=10;
    assert(t.tick().type==='continue' && t.state.phase18===3,'invalid owner enters phase2 then advances to3 without freeing');
    assert(t.calls.join('|')==='retire-a:2:0|retire-b:2:0','guard hides and retires in order; phase2 only increments');
    assert(!guardDoubleCloneOwner(t.state,t.hooks) && t.calls.length===2,'phase3 does not repeat invalidation hooks');
    t.owner.invalid662=0;t.owner.borg3e8=3;
    assert(!guardDoubleCloneOwner(t.state,t.hooks) && t.state.phase18===3,'owner returning does not resurrect a retired child');
    assert(t.tick().type==='disposed' && t.calls.join('|')==='retire-a:2:0|retire-b:2:0|free','following phase3 dispatch frees once; caller removes scheduling');
  }
  {
    const t=fixture();t.owner.arm7c8=1;t.tick();
    assert(t.state.visibility82===0x43,'phase0 immediately falls through to visibility');
    const u=fixture();u.hooks.initialize141b90=()=>{u.owner.arm7c8=2;};u.tick();
    assert(u.state.visibility82===0x43,'visibility reads live owner after initialization hook');
  }
  {
    const t=fixture();let calls=0;
    t.source.borg3e8=10;
    assert(createDoubleCloneLifecycle(t.source,0,()=>{calls++;return true;})===null && calls===0,'non-Double skips allocator');
    t.source.borg3e8=3;
    assert(createDoubleCloneLifecycle(t.source,0,()=>{calls++;return false;})===null && Number(calls)===1,'allocator failure creates no child');
    t.source.borg94=10;
    const mismatch=createDoubleCloneLifecycle(t.source,0,()=>true);
    assert(mismatch && tickDoubleCloneLifecycle(mismatch,t.hooks).type==='continue' && mismatch.phase18===3,'guard compares captured94 to owner3e8, not allocation type');
  }
  {
    const t=fixture();t.state.phase18=2;t.state.visibility82=0x43;t.owner.invalid662=1;
    assert(t.tick().type==='continue' && Number(t.state.phase18)===3,'preexisting phase2 advances by one');
    assert(t.calls.length===0 && t.state.visibility82===0x43,'141c5c does not clear visibility or invoke cleanup');
    assert(t.tick().type==='disposed' && t.calls.join('|')==='free','phase3 frees without repeating retirement');
  }
  {
    const t=fixture();t.state.phase18=4;t.owner.invalid662=1;
    assert(!guardDoubleCloneOwner(t.state,t.hooks),'signed phases greater than1 skip re-retirement');
    assert(t.tick().type==='unsupported' && t.calls.length===0,'unknown phase is explicit, not fabricated cleanup');
    t.state.phase18=255;
    assert(guardDoubleCloneOwner(t.state,t.hooks),'phase255 is signed-1 and does not bypass guard');
    const wrapped:DoubleCloneLifecycleState={...t.state,phase18:1,capturedPlayer96:255};
    t.owner.invalid662=0;t.owner.arm7c8=1;
    tickDoubleCloneLifecycle(wrapped,t.hooks);
    assert(wrapped.visibility82===0x40,'visibility assignment wraps as source byte');
  }
}
