import type { Vec3 } from "./index.js";

/** Legacy tuned half-extents from origin. Kept for existing callers/selfchecks. */
export interface SymmetricStageBounds {
  x: number;
  z: number;
}

/** Real stage-space X/Z rectangle decoded from STIH hit bins. */
export interface RectStageBounds {
  minX: number;
  maxX: number;
  minZ: number;
  maxZ: number;
}

export type StageBounds = SymmetricStageBounds | RectStageBounds;

export function normalizeStageBounds(bounds: StageBounds): RectStageBounds {
  if ("minX" in bounds) return bounds;
  return {
    minX: -bounds.x,
    maxX: bounds.x,
    minZ: -bounds.z,
    maxZ: bounds.z,
  };
}

export interface StageCollisionCell {
  index: number;
  triangleIndices: number[];
}

export interface StageCollisionTriangle {
  index: number;
  layerIndex: number | null;
  marker: number;
  vertices: [Vec3, Vec3, Vec3];
  normal: Vec3;
  planeD: number;
  bounds2d: RectStageBounds;
}

export interface StageCollision {
  triangles: StageCollisionTriangle[];
  grid?: {
    origin: { x: number; z: number };
    cellSize: { x: number; z: number };
    gridCells: { x: number; z: number; total: number };
    cells: StageCollisionCell[];
  };
}

export interface StageHitGridLike {
  header: {
    origin: { x: number; z: number };
    cellSize: { x: number; z: number };
    gridCells: { x: number; z: number; total: number };
    bounds2d: RectStageBounds;
  };
  cells: readonly { index: number; recordIndices: readonly number[] }[];
  triangles: readonly {
    index: number;
    marker: number;
    vertices: [Vec3, Vec3, Vec3];
    normal: Vec3;
    planeD: number;
    bounds2d: RectStageBounds;
  }[];
}

export interface StageCollisionLayer {
  grid: StageHitGridLike;
  layerIndex?: number | null;
}

export interface StageCollisionResources {
  bounds: RectStageBounds;
  collision: StageCollision;
}

export function stageCollisionFromHitGrids(layers: readonly StageCollisionLayer[]): StageCollisionResources | null {
  const first = layers[0]?.grid;
  if (!first) return null;

  const triangles: StageCollisionTriangle[] = [];
  const mergedCells = Array.from({ length: first.header.gridCells.total }, (_, index) => ({
    index,
    triangleIndices: [] as number[],
  }));
  let canMergeCells = true;

  for (let layerPosition = 0; layerPosition < layers.length; layerPosition += 1) {
    const layer = layers[layerPosition];
    if (!layer) continue;
    const base = triangles.length;
    const layerIndex = layer.layerIndex ?? layerPosition;

    for (const tri of layer.grid.triangles) {
      triangles.push({
        index: triangles.length,
        layerIndex,
        marker: tri.marker,
        vertices: tri.vertices,
        normal: tri.normal,
        planeD: tri.planeD,
        bounds2d: tri.bounds2d,
      });
    }

    if (!sameHitGridHeader(first, layer.grid)) {
      canMergeCells = false;
      continue;
    }

    for (const cell of layer.grid.cells) {
      const target = mergedCells[cell.index];
      if (!target) continue;
      target.triangleIndices.push(...cell.recordIndices.map((recordIndex) => base + recordIndex));
    }
  }

  return {
    bounds: { ...first.header.bounds2d },
    collision: {
      triangles,
      ...(canMergeCells
        ? {
            grid: {
              origin: first.header.origin,
              cellSize: first.header.cellSize,
              gridCells: first.header.gridCells,
              cells: mergedCells,
            },
          }
        : {}),
    },
  };
}

export function floorSurfaceYAt(
  collision: StageCollision | null,
  x: number,
  z: number,
  maxSurfaceY: number,
): number | null {
  if (!collision || collision.triangles.length === 0) return null;
  const primary = candidateTriangles(collision, x, z);
  const primaryBest = bestFloorFromCandidates(primary, x, z, maxSurfaceY);
  if (primaryBest != null || primary.length === collision.triangles.length) return primaryBest;
  return bestFloorFromCandidates(collision.triangles, x, z, maxSurfaceY);
}

export function candidateTriangles(collision: StageCollision, x: number, z: number): StageCollisionTriangle[] {
  const grid = collision.grid;
  if (!grid) return collision.triangles;
  const cx = Math.floor((x - grid.origin.x) / grid.cellSize.x);
  const cz = Math.floor((z - grid.origin.z) / grid.cellSize.z);
  if (cx < 0 || cz < 0 || cx >= grid.gridCells.x || cz >= grid.gridCells.z) return [];
  const cell = grid.cells[cz * grid.gridCells.x + cx];
  if (!cell || cell.triangleIndices.length === 0) return [];
  const out: StageCollisionTriangle[] = [];
  for (const index of cell.triangleIndices) {
    const tri = collision.triangles[index];
    if (tri) out.push(tri);
  }
  return out;
}

export function candidateTrianglesForSegment(collision: StageCollision, a: Vec3, b: Vec3): StageCollisionTriangle[] {
  const grid = collision.grid;
  if (!grid) return collision.triangles;
  const indices = new Set<number>();
  addNeighborCellTriangles(indices, collision, a.x, a.z);
  addNeighborCellTriangles(indices, collision, b.x, b.z);
  if (indices.size === 0) return collision.triangles;
  const out: StageCollisionTriangle[] = [];
  for (const index of indices) {
    const tri = collision.triangles[index];
    if (tri) out.push(tri);
  }
  return out;
}

export function bestFloorFromCandidates(
  triangles: readonly StageCollisionTriangle[],
  x: number,
  z: number,
  maxSurfaceY: number,
): number | null {
  let best: number | null = null;
  for (const tri of triangles) {
    if (tri.marker !== 0xcccccccc) continue;
    if (!isFiniteVec(tri.normal)) continue;
    if (tri.normal.y < 0.5) continue;
    if (!tri.vertices.every(isFiniteVec)) continue;
    if (x < tri.bounds2d.minX || x > tri.bounds2d.maxX || z < tri.bounds2d.minZ || z > tri.bounds2d.maxZ) continue;
    const y = yAtTriangleXZ(tri, x, z);
    if (y == null || y > maxSurfaceY) continue;
    if (best == null || y > best) best = y;
  }
  return best;
}

export function yAtTriangleXZ(tri: { vertices: [Vec3, Vec3, Vec3] }, x: number, z: number): number | null {
  const [a, b, c] = tri.vertices;
  const denom = (b.z - c.z) * (a.x - c.x) + (c.x - b.x) * (a.z - c.z);
  if (Math.abs(denom) < 1e-5) return null;
  const wa = ((b.z - c.z) * (x - c.x) + (c.x - b.x) * (z - c.z)) / denom;
  const wb = ((c.z - a.z) * (x - c.x) + (a.x - c.x) * (z - c.z)) / denom;
  const wc = 1 - wa - wb;
  if (wa < -1e-4 || wb < -1e-4 || wc < -1e-4) return null;
  return wa * a.y + wb * b.y + wc * c.y;
}

export function isFiniteVec(v: Vec3): boolean {
  return Number.isFinite(v.x) && Number.isFinite(v.y) && Number.isFinite(v.z);
}

function addNeighborCellTriangles(out: Set<number>, collision: StageCollision, x: number, z: number): void {
  const grid = collision.grid;
  if (!grid) return;
  const cx = Math.floor((x - grid.origin.x) / grid.cellSize.x);
  const cz = Math.floor((z - grid.origin.z) / grid.cellSize.z);
  for (let dz = -1; dz <= 1; dz += 1) {
    for (let dx = -1; dx <= 1; dx += 1) {
      const nx = cx + dx;
      const nz = cz + dz;
      if (nx < 0 || nz < 0 || nx >= grid.gridCells.x || nz >= grid.gridCells.z) continue;
      const cell = grid.cells[nz * grid.gridCells.x + nx];
      if (!cell) continue;
      for (const index of cell.triangleIndices) out.add(index);
    }
  }
}

function sameHitGridHeader(a: StageHitGridLike, b: StageHitGridLike): boolean {
  return (
    a.header.cellSize.x === b.header.cellSize.x &&
    a.header.cellSize.z === b.header.cellSize.z &&
    a.header.gridCells.x === b.header.gridCells.x &&
    a.header.gridCells.z === b.header.gridCells.z &&
    a.header.origin.x === b.header.origin.x &&
    a.header.origin.z === b.header.origin.z
  );
}
