/** Offline composition of the archive, descriptor, AObj, FObj and JObj owners.
 * Callers choose public roots and explicitly attach each root to its joint;
 * this does not infer a model skeleton or choose a game's animation. It does
 * not model RObj/DObj animation, source matrices, rendering or real-time use.
 * Each scalar callback is bound to its destination joint. Failures retain
 * earlier owner effects, as in the constituent bounded runtimes.
 */
import {createSourceAnimationArchiveHydrationRuntime} from './animation-archive-hydration.js';
import {createSourceArchivePublicRuntime} from './archive-public.js';
import {createSourceArchiveJointSetupRuntime} from './archive-joint-setup.js';
import {createSourceFObjScalarCallbackRuntime} from './fobj-callback.js';
import {createSourceFObjDescriptorRuntime} from './fobj-descriptor.js';
import {createSourceAllocatedAObjDescriptorRuntime} from './allocated-aobj-descriptor.js';
import {createSourceJObjAddAnimationRuntime} from './jobj-add-animation.js';
import {createSourceJObjAnimationRuntime, type SourceJObjAnimationEffects} from './jobj-animation.js';
import {createSourceJointAnimationFeedbackRuntime} from './joint-animation-feedback.js';
import {createSourceAObjLifecycleRuntime} from './aobj-lifecycle.js';
import {createSourceJObjTrackOrderRuntime} from './jobj-track-order.js';
import {interpretSourceAObj, requestSourceAObj} from './aobj-clock.js';

export function createSourceAnimationPoseRuntime() {
  const archives = createSourceArchivePublicRuntime();
  const joints = createSourceJObjAnimationRuntime();
  const feedback = createSourceJointAnimationFeedbackRuntime(joints);
  const fobjs = createSourceFObjScalarCallbackRuntime(null);
  const fobjDescriptors = createSourceFObjDescriptorRuntime(fobjs);
  const aobjDescriptors = createSourceAllocatedAObjDescriptorRuntime({feedback, fobjs: fobjDescriptors, removal: fobjs});
  const lifecycle = createSourceAObjLifecycleRuntime({feedback, fobjs, descriptors: aobjDescriptors});
  const order = createSourceJObjTrackOrderRuntime({joints, feedback, fobjs: {getFObj(_aobj, node) {return fobjs.getNode(node);}}});
  const attachment = createSourceJObjAddAnimationRuntime({joints, lifecycle, order});
  const setup = createSourceArchiveJointSetupRuntime({archives, attachment, tail: {
    continueAttachedSetupTail() {throw Error('[animation-pose-runtime] setup tail is not implemented');},
  }});
  const importer = createSourceAnimationArchiveHydrationRuntime({archives, fobjData: fobjs,
    fobjs: fobjDescriptors, aobjs: aobjDescriptors, joints: attachment, setup});
  const effects: SourceJObjAnimationEffects = {
    interpretAObj(id, _joint, callback) {
      interpretSourceAObj(id === null ? null : feedback.getAObj(id), callback, fobjs.effects, joints.endCallbacks.counts);
    },
    animateRObjs(id) {if (id !== null) throw Error('[animation-pose-runtime] RObj animation is not implemented');},
    animateDObjs(id) {if (id !== null) throw Error('[animation-pose-runtime] DObj animation is not implemented');},
  };
  return {
    hydrate: importer.hydrateAnimationArchive,
    createJoint: joints.createJoint,
    getJoint: joints.getJoint,
    attach(joint: symbol, descriptor: symbol) {
      attachment.addAnimation(joint, descriptor);
      joints.getBinding(joint).classUpdate50 = fobjs.createCallback((_owner, track, value) => {
        joints.updateScalar(joint, track, value);
      });
    },
    request(joint: symbol, frame: number) {
      const id = joints.getBinding(joint).aobj7c;
      requestSourceAObj(id === null ? null : feedback.getAObj(id), frame, fobjs.effects);
    },
    animate(joint: symbol) {joints.animateJoint(joint, effects);},
  };
}
