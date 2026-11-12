/** Actor +518 is refreshed globally before movement, while +c8/+cc retain the
 * admitted target identity. Projectile tracking still reads current target roots.
 * Root centers and static aim-joint height are bounded host approximations. */
import type { BorgRuntime } from './types.js';
import { tierSizeScale } from './timescale.js';
export function livingAttackTarget(target: BorgRuntime | undefined | null): target is BorgRuntime {
    return !!target && target.alive && target.hp > 0 && target.state !== 'death';
}
export function actorAimTarget(target: BorgRuntime | undefined | null) {
    return livingAttackTarget(target) ? {
        uid: target.uid,
        pos: { ...(target.sourceFramePose?.pos ?? target.pos) },
        scale: target.sourceFramePose?.scale ?? tierSizeScale(target),
    } : null;
}
/** Two passes are required: no actor can observe another after it already moved. */
export function refreshSourceAttackTargets(all: readonly BorgRuntime[], frame: number): void {
    const byUid = new Map(all.map(target => [target.uid, target]));
    for (const target of all)
        target.sourceFramePose = {
            frame, pos: { ...target.pos }, scale: tierSizeScale(target),
        };
    for (const owner of all) {
        // zz_005685c_: captured +cc controls +524 refresh; retain last point
        // after target loss or visibility rejection. Never acquire the new lock.
        const beam = owner.beamAim;
        if (beam) {
            const target = beam.targetUid ? byUid.get(beam.targetUid) : undefined;
            if (!livingAttackTarget(target)) beam.targetUid = null;
            else if ((target.targetEligibility83 ?? 0) !== 0 ||
                (((target.targetVisibilityMask5e6 ?? 0) & (1 << all.indexOf(owner))) !== 0))
                beam.pos = { ...(target.sourceFramePose?.pos ?? target.pos) };
        }
        for (const aim of [owner.arrowAttack, owner.gatlingSavedAim, owner.timeBomberSavedAim, owner.poweredNormalAim, owner.revolverAttack]) {
            if (!aim)
                continue;
            const target = aim.targetUid ? actorAimTarget(byUid.get(aim.targetUid)) : null;
            if (target)
                aim.pos = { ...target.pos };
            else {
                aim.targetUid = null;
                // Source no-target +518 uses absolute heading coordinates and joint3 Y.
                // Only Powered normal consumes the resulting point without a target.
                aim.pos = aim === owner.poweredNormalAim ? {
                    x: 20000 * Math.sin(owner.rotY),
                    y: owner.pos.y + tierSizeScale(owner) * 124.89293384552002,
                    z: 20000 * Math.cos(owner.rotY),
                } : { ...owner.pos };
            }
        }
    }
}
