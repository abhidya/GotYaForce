#!/usr/bin/env node
// Regression for a real st00 wall triangle, not proof that all visual props
// have collision or that the original game's body shape is reproduced.
import assert from 'node:assert/strict';
import {createNodePublicAssetCatalog} from './lib/node-public-assets.mjs';
import {resolveStageMotionCollision} from '../packages/combat/dist/movement.js';

const {collision} = await createNodePublicAssetCatalog(process.cwd()).loadStageAssets('st00');
assert.ok(collision, 'first-stage collision did not load');
const tri = collision.triangles[686];
assert.ok(tri && tri.marker === 0xcccccccc, 'expected first-stage collision triangle missing');
const y = 610;
const crossings = [];
for (let i=0;i<3;i++) {
  const a=tri.vertices[i], b=tri.vertices[(i+1)%3];
  if ((a.y-y)*(b.y-y)<=0 && a.y!==b.y) {
    const k=(y-a.y)/(b.y-a.y);
    crossings.push({x:a.x+(b.x-a.x)*k,z:a.z+(b.z-a.z)*k});
  }
}
assert.equal(crossings.length,2,'fixture no longer intersects wall at test height');
const x=(crossings[0].x+crossings[1].x)/2, z=(crossings[0].z+crossings[1].z)/2;
const h=Math.hypot(tri.normal.x,tri.normal.z);
assert.ok(h>0,'wall has no horizontal normal');
const nx=tri.normal.x/h,nz=tri.normal.z/h;
const previous={x:x+20*nx,y,z:z+20*nz};
const destination={x:x-20*nx,y,z:z-20*nz};
const position={...destination}, velocity={x:-40*nx,y:0,z:-40*nz};
resolveStageMotionCollision(collision,previous,position,velocity);
assert.ok(Math.hypot(position.x-previous.x,position.z-previous.z)<39,'movement crossed first-stage wall');
const control={...destination};
resolveStageMotionCollision({triangles:[]},previous,control,{x:-40*nx,y:0,z:-40*nz});
assert.deepEqual(control,destination,'empty-geometry negative control must not block');
console.log('first-stage wall selfcheck PASS (one actual collision triangle, not browser play)');
