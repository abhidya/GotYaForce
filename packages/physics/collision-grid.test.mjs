import { test } from 'node:test';
import assert from 'node:assert/strict';
import { candidateTrianglesForSegment } from './dist/collision.js';

const v = (x, z = 5) => ({x, y: 0, z});
const triangles = [0, 1].map(index => ({index, layerIndex:0, marker:0xcccccccc,
  vertices:[v(0),v(0),v(0)], normal:v(1,0), planeD:0,
  bounds2d:{minX:0,maxX:80,minZ:0,maxZ:10}}));
const collision = {triangles, grid:{origin:{x:0,z:0}, cellSize:{x:10,z:10},
  gridCells:{x:8,z:1,total:8}, cells:Array.from({length:8},(_,index)=>({index,
    triangleIndices:index===3?[0]:index===7?[1]:[]}))}};

test('grid traversal includes middle cells when a segment crosses its border', () => {
  for (const [a,b] of [[v(-10),v(75)],[v(75),v(-10)],[v(-10),v(90)],[v(90),v(-10)]]) {
    assert.ok(candidateTrianglesForSegment(collision,a,b).some(t=>t.index===0));
  }
});
test('in-grid segments retain their normal candidate set', () => {
  assert.deepEqual(candidateTrianglesForSegment(collision,v(25),v(35)).map(t=>t.index),[0]);
});

test('out-of-grid movement resolves an intermediate Battle wall', async () => {
  const {resolveStageMotionCollision} = await import('../combat/dist/movement.js');
  const wall = {...triangles[0],vertices:[{x:35,y:-100,z:-10},{x:35,y:100,z:-10},{x:35,y:0,z:20}],
    normal:{x:1,y:0,z:0}, bounds2d:{minX:35,maxX:35,minZ:-10,maxZ:20}};
  const stage={...collision,triangles:[wall,triangles[1]]};
  const previous=v(-10), current=v(75), velocity=v(85,0);
  resolveStageMotionCollision(stage,previous,current,velocity);
  assert.ok(current.x < 35, `crossed wall at x=${current.x}`);
});
