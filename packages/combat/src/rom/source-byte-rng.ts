/** Exact authenticated800055fc byte generator. Caller supplies the real retained
 * owner and a non-consuming identity/reentry guard, never a seed or callback RNG. */
const nativeDescriptor = Reflect.getOwnPropertyDescriptor;
const active = new WeakSet<object>(), poisoned = new WeakSet<object>();
export function stepSourceByteRng(state: object, guard: () => void): number {
  const fail = (reason: string): never => {throw Error(`[source-byte-rng] ${reason}`);};
  if (active.has(state)) {poisoned.add(state); fail('same-state reentry');}
  active.add(state); poisoned.delete(state);
  const check = (): void => {guard(); if (poisoned.has(state)) fail('caught same-state reentry');};
  try {
  const load = (key: string): number => {
    check(); const p = Object.getOwnPropertyDescriptor(state, key); check();
    if (!p || !('value' in p) || !Number.isInteger(p.value) || p.value < 0 || p.value > 255)
      return fail(`${key}: own raw byte required`);
    return p.value as number;
  };
  const store = (key: string, value: number): void => {
    check(); const p = Object.getOwnPropertyDescriptor(state, key); check();
    if (!p || !('value' in p) || !p.writable) fail(`${key}: writable own byte required`);
    const live = nativeDescriptor(state, key);
    if (!live || !('value' in live) || !live.writable) fail(`${key}: writable own byte required`);
    (state as Record<string, unknown>)[key] = value; check();
  };
  const high = load('byte804360c7'), low = load('byte804360c6');
  const nextHigh = (((high * 256 + low) * 3) >> 8) & 255;
  const nextLow = (low + nextHigh) & 255;
  store('byte804360c7', nextHigh); store('byte804360c6', nextLow);
  return nextLow;
  } finally {active.delete(state); poisoned.delete(state);}
}
