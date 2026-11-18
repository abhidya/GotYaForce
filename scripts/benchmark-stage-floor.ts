import {readFileSync} from 'node:fs';import {performance} from 'node:perf_hooks';
import {parseStageHitGrid} from '../packages/formats/src/hit-bin.js';
import {stageCollisionFromHitGrids,floorSurfaceYAt} from '../packages/physics/src/collision.js';
const layers=[0,1,2].map(i=>({layerIndex:i,grid:parseStageHitGrid(readFileSync(`apps/game/public/stages/st00/collision/hit00${i}.bin`))}));const c=stageCollisionFromHitGrids(layers)!.collision;const points=Array.from({length:8000},(_,i)=>({x:(i*7919%22000)-11000,z:(i*4441%22000)-11000,y:i%2?100:1000}));
function run(){let sum=0,miss=0;const t=performance.now();for(const p of points){let y=floorSurfaceYAt(c,p.x,p.z,p.y);if(y===null)miss++;else sum+=y;}return{ms:performance.now()-t,sum,miss}};run();console.log(JSON.stringify([run(),run(),run()]));
