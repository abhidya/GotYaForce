import {stepSourceByteRng} from './source-byte-rng.js';
import {consumeSourceActorVoiceRngInvocation, checkSourceActorVoiceRngInvocation,
  type SourceActorCommandAdmissionRuntime} from './actor-command-admission.js';
function check(value: boolean, message: string): void {if (!value) throw Error(message);}
function rejects(run: () => unknown, fragment: string): void {
  let error = ''; try {run();} catch (e) {error = String(e);}
  check(error.includes(fragment), `expected ${fragment}, got ${error}`);
}
export function runSelfTest(): void {
  for (let high = 0; high < 256; high++) for (let low = 0; low < 256; low++) {
    const state = {byte804360c7: high, byte804360c6: low};
    const expectedHigh = Math.floor(((high * 256 + low) * 3) / 256) % 256;
    const expectedLow = (low + expectedHigh) % 256;
    check(stepSourceByteRng(state, () => {}) === expectedLow, 'exact return');
    check(state.byte804360c7 === expectedHigh && state.byte804360c6 === expectedLow, 'exact stores');
  }
  const state = {byte804360c7: 1, byte804360c6: 50};
  check(stepSourceByteRng(state, () => {}) === 53, 'shared first sequence');
  check(stepSourceByteRng(state, () => {}) === 62, 'shared second sequence');
  const readonlyLow = {byte804360c7: 1, byte804360c6: 50};
  Object.defineProperty(readonlyLow, 'byte804360c6', {writable: false});
  rejects(() => stepSourceByteRng(readonlyLow, () => {}), 'writable');
  check(readonlyLow.byte804360c7 === 3 && readonlyLow.byte804360c6 === 50, 'high prefix retained');
  const missingLow = {byte804360c7: 1};
  rejects(() => stepSourceByteRng(missingLow, () => {}), 'own raw byte');
  check(missingLow.byte804360c7 === 1, 'both captures precede writes');
  let once = false;
  const recursive = {byte804360c7: 1, byte804360c6: 50};
  rejects(() => stepSourceByteRng(recursive, () => {
    if (!once) {once = true; try {stepSourceByteRng(recursive, () => {});} catch { /* caught attack */ }}
  }), 'caught same-state');
  check(recursive.byte804360c7 === 1, 'caught recursion cannot advance');
  const late = {byte804360c7: 1, byte804360c6: 50};
  const original = Object.getOwnPropertyDescriptor;
  let observedHigh = 0, setterCalls = 0;
  Object.getOwnPropertyDescriptor = ((owner: object, key: PropertyKey) => {
    const result = original(owner, key);
    if (owner === late && key === 'byte804360c7' && ++observedHigh === 2)
      Object.defineProperty(late, key, {get: () => 1, set: () => {setterCalls++;}, configurable: true});
    return result;
  }) as typeof original;
  try {rejects(() => stepSourceByteRng(late, () => {}), 'writable');}
  finally {Object.getOwnPropertyDescriptor = original;}
  check(setterCalls === 0 && late.byte804360c6 === 50, 'terminal native check prevents late accessor write');
  const fake = {} as SourceActorCommandAdmissionRuntime, id = Symbol('not active');
  rejects(() => consumeSourceActorVoiceRngInvocation(fake, id, 0x800ea324), 'missing');
  rejects(() => checkSourceActorVoiceRngInvocation(fake, id, 0x800ea190), 'no consumed');
}
