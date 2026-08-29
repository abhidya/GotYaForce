// =============================================================================
// backend.ts — where assembled GX primitives go, and the headless backend.
//
// The GX host is split so the DECODE side (adapters + state + FIFO) can be
// asserted without a GPU, and the RASTER side (webgl.ts) can be swapped. Both
// backends implement GxBackend; the recording backend is what headless
// assertions read, the WebGL backend is what produces a framebuffer.
// =============================================================================

import { primitiveName } from "./enums.js";
import type { GxPrimitive, GxPrimitiveSink } from "./fifo.js";

export interface GxBackend extends GxPrimitiveSink {
  /** Called at the start of each host-driven frame. */
  beginFrame(): void;
  /** Called at the end of each host-driven frame. */
  endFrame(): void;
  /** Release GPU resources, if any. */
  dispose(): void;
  /**
   * Anything the backend could not reproduce faithfully. NEVER empty just
   * because rendering "looked fine": every approximation the backend makes is
   * expected to name itself here, because the difference between a frame that
   * is right and a frame that merely renders is exactly this list.
   */
  readonly diagnostics: readonly string[];
}

/** A compact record of one submitted primitive, for assertions and reports. */
export interface GxPrimitiveRecord {
  frame: number;
  primitive: string;
  primitiveByte: number;
  vertexCount: number;
  hasNormals: boolean;
  hasColors: boolean;
  hasTexcoords: boolean;
  /** First vertex, post-decode, in GX object space — the cheapest assertion
   *  that the FIFO decoded what the ROM wrote. */
  firstVertex: [number, number, number] | null;
  /** First vertex colour as rgba, when the draw carried colours. */
  firstColor: [number, number, number, number] | null;
  currentMtxId: number;
  projectionType: number;
  cullMode: number;
  texMap: number;
}

/**
 * Headless backend: records everything, rasterizes nothing.
 *
 * This is the backend the decode-side assertions run against, and it is also
 * what the WebGL backend delegates its bookkeeping to, so a headless assertion
 * and a rendered frame are provably looking at the same primitive stream.
 */
export class GxRecordingBackend implements GxBackend {
  readonly records: GxPrimitiveRecord[] = [];
  readonly diagnostics: string[] = [];
  /** Every primitive kept in full, for a backend that wants to draw them. */
  readonly primitives: GxPrimitive[] = [];
  frame = 0;
  vertexTotal = 0;

  beginFrame(): void {
    this.frame += 1;
  }

  endFrame(): void {
    /* nothing to present */
  }

  submit(primitive: GxPrimitive): void {
    this.primitives.push(primitive);
    this.vertexTotal += primitive.vertexCount;
    const p = primitive.positions;
    const c = primitive.colors;
    this.records.push({
      frame: this.frame,
      primitive: primitiveName(primitive.primitive),
      primitiveByte: primitive.primitive,
      vertexCount: primitive.vertexCount,
      hasNormals: primitive.normals !== null,
      hasColors: c !== null,
      hasTexcoords: primitive.texcoords !== null,
      firstVertex: p.length >= 3 ? [p[0] as number, p[1] as number, p[2] as number] : null,
      firstColor:
        c && c.length >= 4 ? [c[0] as number, c[1] as number, c[2] as number, c[3] as number] : null,
      currentMtxId: primitive.state.currentMtxId,
      projectionType: primitive.state.projectionType,
      cullMode: primitive.state.cullMode,
      texMap: primitive.state.tevTexMap,
    });
  }

  dispose(): void {
    /* nothing to release */
  }

  /** JSON-safe summary for the smoke phase and window.__gf reporting. */
  summary(): {
    frames: number;
    primitives: number;
    vertices: number;
    byPrimitive: Record<string, number>;
    diagnostics: string[];
  } {
    const byPrimitive: Record<string, number> = {};
    for (const r of this.records) byPrimitive[r.primitive] = (byPrimitive[r.primitive] ?? 0) + 1;
    return {
      frames: this.frame,
      primitives: this.records.length,
      vertices: this.vertexTotal,
      byPrimitive,
      diagnostics: [...this.diagnostics],
    };
  }
}
