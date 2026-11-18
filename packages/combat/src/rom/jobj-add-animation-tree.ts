/** Bounded null-material/null-shape HSD_JObjAddAnimAll, 8024dd44.
 * Visits actual JObj and AnimJoint owners in source child/sibling order and
 * delegates each reached node to the existing single-joint attachment owner.
 * This is offline; original animation archives and live presentation are not
 * connected. A visit budget is a host bound, not original error behavior.
 */
import type {SourceJObjAnimationRuntime} from './jobj-animation.js';
import type {SourceJObjAddAnimationRuntime} from './jobj-add-animation.js';

export function createSourceJObjAddAnimationTreeRuntime(
  joints: Pick<SourceJObjAnimationRuntime, 'getJoint'>,
  animation: Pick<SourceJObjAddAnimationRuntime, 'getDescriptor' | 'addAnimation'>,
  maxVisits = 4096,
) {
  if (!Number.isSafeInteger(maxVisits) || maxVisits < 1) throw Error('[jobj-add-animation-tree] invalid visit budget');
  let busy = false, poisoned = false;
  const capture = (owner: object, key: string): ((...args: never[]) => unknown) => {
    const p = Object.getOwnPropertyDescriptor(owner, key);
    if (!p || !('value' in p) || typeof p.value !== 'function') throw Error(`[jobj-add-animation-tree] ${key}: own method required`);
    return (...args: never[]) => {
      const value = Reflect.apply(p.value, owner, args);
      if (poisoned) throw Error('[jobj-add-animation-tree] caught reentry');
      if (value instanceof Promise) throw Error('[jobj-add-animation-tree] synchronous method required');
      return value;
    };
  };
  const getJoint = capture(joints, 'getJoint'), getDescriptor = capture(animation, 'getDescriptor');
  const add = capture(animation, 'addAnimation');
  const field = (record: unknown, key: string): unknown => {
    if (!record || typeof record !== 'object') throw Error('[jobj-add-animation-tree] owner record required');
    const p = Object.getOwnPropertyDescriptor(record, key);
    if (!p || !('value' in p)) throw Error(`[jobj-add-animation-tree] ${key}: own data required`);
    return p.value;
  };
  const pointer = (value: unknown): symbol | null => {
    if (value !== null && typeof value !== 'symbol') throw Error('[jobj-add-animation-tree] expected owned symbol or null');
    return value;
  };
  const jointLink = (id: symbol, key: string) => pointer(field(getJoint(id as never), key));
  const descriptorLink = (id: symbol | null, key: string) => id === null ? null : pointer(field(getDescriptor(id as never), key));
  return Object.freeze({
    addAnimationTree(root: symbol | null, descriptor: symbol | null): void {
      if (busy) {poisoned = true; throw Error('[jobj-add-animation-tree] reentry unsupported');}
      if (root === null) return;
      pointer(root); pointer(descriptor); busy = true; poisoned = false;
      try {
        type Frame = {joint: symbol; desc: symbol | null; phase: 'enter' | 'advance'};
        const stack: Frame[] = [{joint: root, desc: descriptor, phase: 'enter'}];
        let visits = 0;
        while (stack.length) {
          const frame = stack.pop()!;
          if (frame.phase === 'advance') {
            const sibling = jointLink(frame.joint, 'sibling08');
            const next = descriptorLink(frame.desc, 'next04');
            if (sibling !== null) {
              stack.push({joint: sibling, desc: next, phase: 'advance'});
              stack.push({joint: sibling, desc: next, phase: 'enter'});
            }
            continue;
          }
          if (++visits > maxVisits) throw Error('[jobj-add-animation-tree] visit budget exceeded');
          if (add(frame.joint as never, frame.desc as never) !== undefined)
            throw Error('[jobj-add-animation-tree] attachment must return void');
          const flags = field(getJoint(frame.joint as never), 'flags14');
          if (typeof flags !== 'number' || !Number.isInteger(flags) || flags < 0 || flags > 0xffffffff)
            throw Error('[jobj-add-animation-tree] flags14: uint32 required');
          if ((flags & 0x1000) !== 0) continue;
          const child = jointLink(frame.joint, 'child10');
          const childDesc = descriptorLink(frame.desc, 'child00');
          if (child !== null) {
            stack.push({joint: child, desc: childDesc, phase: 'advance'});
            stack.push({joint: child, desc: childDesc, phase: 'enter'});
          }
        }
      } finally {busy = false;}
    },
  });
}
