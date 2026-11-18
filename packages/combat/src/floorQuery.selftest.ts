import { bestFloorFromCandidates, yAtTriangleXZ, type StageCollisionTriangle } from "@gf/physics";

function assert(ok: unknown, message: string): asserts ok {
  if (!ok) throw new Error(`[floorQuery] ${message}`);
}
/** Independent pre-optimization predicate order for exact output comparison. */
function reference(triangles: readonly StageCollisionTriangle[], x: number, z: number, maxY: number): number | null {
  let best: number | null = null;
  const finite = (p: {x:number;y:number;z:number}) => Number.isFinite(p.x) && Number.isFinite(p.y) && Number.isFinite(p.z);
  for (const t of triangles) {
    if (t.marker !== 0xcccccccc || !finite(t.normal) || t.normal.y < 0.5 || !t.vertices.every(finite)) continue;
    if (x < t.bounds2d.minX || x > t.bounds2d.maxX || z < t.bounds2d.minZ || z > t.bounds2d.maxZ) continue;
    const y = yAtTriangleXZ(t, x, z);
    if (y == null || y > maxY) continue;
    if (best == null || y > best) best = y;
  }
  return best;
}
export function runFloorQuerySelfTest(): void {
  const tris: StageCollisionTriangle[] = [];
  for (let i=0;i<200;i++) {
    const x=(i%20)*11-100,z=Math.floor(i/20)*13-60,y=(i%7)*3;
    tris.push({index:i,layerIndex:i%3,marker:i%17===0?0:0xcccccccc,
      vertices:[{x,y,z},{x:x+10,y,z},{x,y:y+1,z:z+12}],normal:{x:0,y:i%13===0?0:1,z:0},planeD:0,
      bounds2d:{minX:x,maxX:x+10,minZ:z,maxZ:z+12}});
  }
  // Invalid geometry must stay ignored, including NaN bounds/vertices.
  tris.push({...tris[1]!, index:201, normal:{x:NaN,y:1,z:0}});
  tris.push({...tris[2]!, index:202, vertices:[{x:NaN,y:0,z:0},...tris[2]!.vertices.slice(1)] as StageCollisionTriangle["vertices"]});
  for(let x=-110;x<=120;x+=3) for(let z=-70;z<=80;z+=5) for(const maxY of [-1,10,100]) {
    const expected=reference(tris,x,z,maxY),actual=bestFloorFromCandidates(tris,x,z,maxY);
    assert(Object.is(actual,expected), `floor mismatch at ${x},${z},${maxY}: ${actual} vs ${expected}`);
  }
  console.log("[floorQuery] ordered rejection preserves reference results PASS");
}
