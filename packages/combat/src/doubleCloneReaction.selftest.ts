import {classifyDoubleCloneReaction, type DoubleCloneReactionInput} from './doubleCloneReaction.js';

function assert(value:unknown,message:string):asserts value {
  if (!value) throw Error(`[doubleCloneReaction] ${message}`);
}
const fixture = (patch:Partial<DoubleCloneReactionInput> = {}):DoubleCloneReactionInput => ({
  control5e0:0,flags6fd:2,flags1da:1,heavy599:0,downGauge6c6:0,
  borg3e8:3,descriptorClass591:0,pairedState4a0:0,alive:true,
  ordinaryCollisionTail:true,frameAggregationComplete:true,alreadyReacting:false,
  entry540:0,phase544:0,immediateDispatchPermitted:true,recoveryTerrain5ef08:false,...patch,
});
export function runDoubleCloneReactionSelfTest():void {
  // Exhaustive raw6fd: all directions/force/balance combinations, both1da bit0
  // values, both prior source bits, both admission boundaries, every probe result.
  for (let flags6fd=0; flags6fd<256; flags6fd++) {
    for (const flags1da of [0,1]) for (const downGauge6c6 of [-1,0,1,32767]) {
      for (const control5e0 of [0,0x40,0x02000000,0x02000040]) {
        for (const recoveryTerrain5ef08 of [false,true,null]) {
          const input = Object.freeze(fixture({flags6fd,flags1da,downGauge6c6,control5e0,recoveryTerrain5ef08}));
          const result = classifyDoubleCloneReaction(input);
          const label = JSON.stringify(input);
          if ((flags6fd & 0x40) !== 0) {
            assert(result.type === 'unsupported',`rehit excluded: ${label}`); continue;
          }
          const admitted = flags1da === 1 && flags6fd !== 0 &&
            (downGauge6c6 <= 0 || ((flags6fd & 2) !== 0 && (flags6fd & 0x80) !== 0));
          if (!admitted) {
            assert(result.type === 'preserve' && !result.enteredReaction &&
              result.resetBitAfterDispatch === ((control5e0 & 0x02000000) !== 0),
            `no admission preserves existing bit: ${label}`); continue;
          }
          const standardReset = (flags6fd & 2) !== 0 || control5e0 !== 0;
          if (!standardReset && recoveryTerrain5ef08 === null) {
            assert(result.type === 'unsupported',`unknown terrain is not false: ${label}`); continue;
          }
          const reset = standardReset || recoveryTerrain5ef08 === true;
          assert(result.type !== 'unsupported' && result.enteredReaction &&
            result.resetBitAfterDispatch === reset && result.type === (reset ? 'reset' : 'preserve'),
          `admitted phase0 bit proof: ${label}`);
        }
      }
    }
  }
  // Every nonordinary1da combination stays unsupported, including healing with
  // positive gauge, a reset-producing raw hit, or simultaneous override bits.
  for (let flags1da=2; flags1da<256; flags1da++) {
    for (const flags6fd of [0,1,2,0x82,0xa6]) for (const downGauge6c6 of [0,10]) {
      assert(classifyDoubleCloneReaction(fixture({flags1da,flags6fd,downGauge6c6})).type === 'unsupported',
        `override1da=${flags1da} cannot inherit ordinary reset`);
    }
  }
  const excluded:Partial<DoubleCloneReactionInput>[] = [
    {borg3e8:2},{descriptorClass591:1},{descriptorClass591:3},{descriptorClass591:6},
    {alive:false},{pairedState4a0:1},{pairedState4a0:2},{ordinaryCollisionTail:false},
    {frameAggregationComplete:false},{alreadyReacting:true},{entry540:1},{phase544:1},
    {entry540:-1},{phase544:255},{immediateDispatchPermitted:false},
    {control5e0:0x01000000},{control5e0:0x04000000},{control5e0:0x08000000},
    {control5e0:0x10000000},{control5e0:0x80000000},{control5e0:0x05000000},
    {control5e0:NaN},{control5e0:-1},{control5e0:0x100000000},{control5e0:1.5},
    {flags6fd:-1},{flags6fd:256},{flags6fd:NaN},{flags1da:256},{flags1da:0.5},
    {downGauge6c6:NaN},{downGauge6c6:Infinity},{downGauge6c6:0.5},
    {downGauge6c6:-32769},{downGauge6c6:32768},{heavy599:256},
  ];
  for (const patch of excluded) {
    assert(classifyDoubleCloneReaction(fixture(patch)).type === 'unsupported',
      `explicit admissibility gate ${JSON.stringify(patch)}`);
  }
  for (let heavy599=1; heavy599<256; heavy599++) {
    assert(classifyDoubleCloneReaction(fixture({heavy599})).type === 'unsupported','heavy override');
  }
  // Deferred scheduling cannot authorize phase0; no admission never calls it.
  const untouched = classifyDoubleCloneReaction(fixture({flags6fd:2,downGauge6c6:1,
    control5e0:0x02000000,immediateDispatchPermitted:false}));
  assert(untouched.type === 'preserve' && untouched.resetBitAfterDispatch && !untouched.enteredReaction,
    'positive gauge plus6fd2 alone does not clear an existing bit or enter reaction');
  const unknown = classifyDoubleCloneReaction(fixture({flags6fd:1,recoveryTerrain5ef08:null}));
  assert(unknown.type === 'unsupported' && !('resetBitAfterDispatch' in unknown),
    'unsupported must not expose an invented control bit');
  // Ordinary nonreaction control low bits must not invent a force/down threshold.
  for (const control5e0 of [1,2,4,8,0x100,0x10000,0x20000]) {
    const light = classifyDoubleCloneReaction(fixture({control5e0,flags6fd:1}));
    assert(light.type === 'preserve' && light.enteredReaction && !light.resetBitAfterDispatch,
      'unrelated control bits do not reset clone');
  }
}
