import { createRevolverShot, stepRevolverShot, revolverMuzzle, REVOLVER_SHOT_CONTRACT } from './revolverProjectile.js';
export function runSelfTest(): void {
    const ok = (b: unknown, m: string) => {
        if (!b)
            throw Error(`[revolverProjectile] ${m}`);
    };
    const near = (a: number, b: number, m: string) => ok(Math.abs(a - b) < 1e-6, `${m}: ${a} != ${b}`);
    const p = { x: 0, y: 0, z: 0 }, t = { uid: 'a', pos: { x: 0, y: 0, z: 2000 }, scale: 1, radius: 20 };
    const no = createRevolverShot(0, p, 0, null);
    near(no.pos.z, 0, 'constructor never advances');
    near(no.life, 600, 'constructor retains lifetime');
    near(no.vel.z, 60, 'source speed');
    near(no.gravity, Math.fround(.3), 'source gravity');
    ok(REVOLVER_SHOT_CONTRACT.model === 0x400b && REVOLVER_SHOT_CONTRACT.ownerLocalModel === 11 &&
        REVOLVER_SHOT_CONTRACT.referenceMode === 2, 'source identities');
    for (const row of [0, 1, 13, 14] as const) {
        const muzzle = revolverMuzzle(row, p, 0, 2);
        near(muzzle.x, ((row === 0 || row === 13) ? -185.59277391433716 : 185.59280443191528) * 2,
            'static joint muzzle');
        near(createRevolverShot(row, p, 0, null, 2).scale, 2, 'row scale');
    }
    const turnedMuzzle = revolverMuzzle(0, p, Math.PI / 2);
    near(turnedMuzzle.x, 22.99999614616, 'muzzle owner yaw');
    const tracked = createRevolverShot(1, p, 0, t, 2);
    ok(tracked.vel.y > 0, 'low ballistic pitch');
    near(tracked.vel.x, 0, 'pitch does not reacquire target yaw');
    near(Math.hypot(tracked.launchBasis.forward.x, tracked.launchBasis.forward.y,
        tracked.launchBasis.forward.z), 1, 'effect captures unit orientation');
    const compensated = createRevolverShot(1, p, 0, null, 1, true, .4);
    ok(Math.abs(compensated.vel.y) < .01, 'root pitch compensated without target');
    const one = createRevolverShot(1, p, 0, t, 1, false);
    ok(one.targetUid === null, 'admission disabled tracking clears captured handle');
    ok(one.gravity !== Math.fround(.3), 'admission disabled tracking adjusts gravity once');
    near(one.pos.z, 0, 'one-shot gravity adjustment does not move');
    const lateral = { ...t, pos: { x: 1000, y: -1000, z: 2000 } };
    const flight = stepRevolverShot(tracked, lateral).state;
    near(Math.atan2(flight.vel.x, flight.vel.z), Math.fround(Math.PI / 180), 'one degree lateral cap');
    near(flight.pos.z, tracked.vel.z * Math.cos(Math.fround(Math.PI / 180)), 'horizontal advances before solve');
    const h = Math.hypot(tracked.vel.x, tracked.vel.z), time = Math.hypot(lateral.pos.x - flight.pos.x,
        lateral.pos.z - flight.pos.z) / h;
    const desired = 2 * (time * tracked.vel.y - (lateral.pos.y + 40 - tracked.pos.y)) / (time * time);
    const expected = tracked.gravity + Math.max(-Math.fround(.15), Math.min(Math.fround(.15), Math.max(0,
        Math.min(7.5, desired)) - tracked.gravity));
    near(flight.gravity, expected, 'gravity uses advanced position and captured scale offset');
    near(flight.pos.y, tracked.vel.y - expected / 2, 'vertical integration');
    near(flight.vel.y, tracked.vel.y - expected, 'vertical velocity restored after full normalization');
    ok(stepRevolverShot(tracked, { ...t, uid: 'replacement' }).state.targetUid === null, 'no target replacement');
    ok(stepRevolverShot(tracked, null).alive, 'target loss is not death');
    const close = { ...t, pos: { x: 0, y: 0, z: 45 } };
    ok(stepRevolverShot(tracked, close).state.targetUid === null, 'surface distance25 detaches');
    ok(stepRevolverShot(tracked, { ...close, pos: { x: 0, y: 0, z: 45.01 } }).state.targetUid === 'a',
        'outside surface distance retains');
    let alive = no;
    for (let i = 0; i < 599; i++)
        alive = stepRevolverShot(alive, null).state;
    ok(alive.alive && alive.life === 1, '599 updates survive');
    alive = stepRevolverShot(alive, null).state;
    ok(!alive.alive && alive.life === 0, '600th expires');
    const degenerate = stepRevolverShot({ ...tracked, vel: { x: 0, y: 0, z: 0 } }, t).state;
    ok(Number.isFinite(degenerate.vel.z) && Number.isFinite(degenerate.gravity), 'zero horizontal speed safeguarded');
    const tiny = stepRevolverShot({ ...tracked, yaw: 0, vel: { x: 1e-8, y: 0, z: 0 } }, t).state;
    near(tiny.pos.x, 0, 'tiny speed uses actor heading rather than stale velocity');
    const behind = stepRevolverShot({ ...tracked, vel: { x: 0, y: 0, z: 60 } }, { ...t, pos: { x: 0, y: 0,
        z: -2000 } }).state;
    ok(behind.pos.x > 0, 'antipodal target uses source positive Y turn axis');
    const zeroTime = createRevolverShot(0, p, 0, { ...t, pos: p }, 1, false);
    ok(Number.isFinite(zeroTime.gravity), 'zero time gravity safeguarded');
    near(tracked.pos.z, 0, 'step does not mutate input');
    near(tracked.life, 600, 'step retains input lifetime');
}
