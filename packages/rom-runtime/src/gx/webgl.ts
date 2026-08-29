// =============================================================================
// webgl.ts — the WebGL2 rasterizer behind the GX seam.
//
// CLAIM BAR, normative and repeated at every reporting surface:
// **framebuffer-equivalent, never pixel-identical**
// (docs/playable-port-design.md V3 non-fatal note 1). WebGL rasterization
// cannot match Flipper: the TEV combiner, GameCube fixed-point rasterization
// rules, EFB copy semantics, the 24-bit depth buffer's exact comparison
// behaviour and the texture filter kernels all differ. This backend aims to
// put the RIGHT GEOMETRY in the RIGHT PLACE with the right blend/depth/cull
// intent, and it names everything it approximates in `diagnostics`.
//
// AND, stated as plainly: this path has no trace verification behind it. No
// frame it produces has ever been compared against a real GameCube frame. Its
// status is SCAFFOLDING, not a renderer. See docs/gx-hle-host.md.
// =============================================================================

import {
  GXBlendFactor,
  GXBlendMode,
  GXCompare,
  GXCullMode,
  GXPrimitive,
  GXProjectionType,
  primitiveName,
} from "./enums.js";
import type { GxBackend } from "./backend.js";
import { GxRecordingBackend } from "./backend.js";
import type { GxPrimitive as GxPrimitiveData } from "./fifo.js";
import type { GxDrawState } from "./state.js";

const VERT = `#version 300 es
precision highp float;
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec4 aColor;
layout(location = 2) in vec2 aUv;
uniform mat4 uProj;
uniform mat4 uPosMtx;
out vec4 vColor;
out vec2 vUv;
void main() {
  vec4 eye = uPosMtx * vec4(aPos, 1.0);
  gl_Position = uProj * eye;
  vColor = aColor;
  vUv = aUv;
}`;

const FRAG = `#version 300 es
precision highp float;
in vec4 vColor;
in vec2 vUv;
uniform vec4 uMatColor;
out vec4 outColor;
void main() {
  outColor = vColor * uMatColor;
}`;

/**
 * Build the GL projection matrix from GX's 7-float coefficient form.
 *
 * Column-major for GL. Two deviations are made deliberately and reported:
 *  - GX clips z to [-w, 0] (NDC [-1, 0]); GL clips to [-w, w]. The third row
 *    is rewritten as `2*row2 + row3` to remap, which changes depth PRECISION
 *    distribution relative to the console even though the visible ordering is
 *    preserved.
 *  - GX's perspective form implies a right-handed eye space looking down -Z,
 *    which GL shares, so no handedness flip is applied.
 */
export function gxProjectionToGl(projection: Float32Array): Float32Array {
  const [type, a, b, c, d, e, f] = [
    projection[0] ?? 0,
    projection[1] ?? 1,
    projection[2] ?? 0,
    projection[3] ?? 1,
    projection[4] ?? 0,
    projection[5] ?? -1,
    projection[6] ?? -1,
  ];
  // Row-major first, for readability; transposed to column-major at the end.
  let m: number[];
  if (type === GXProjectionType.ORTHOGRAPHIC) {
    m = [a, 0, 0, b, 0, c, 0, d, 0, 0, e, f, 0, 0, 0, 1];
  } else {
    m = [a, 0, b, 0, 0, c, d, 0, 0, 0, e, f, 0, 0, -1, 0];
  }
  // z remap: row2' = 2*row2 + row3
  for (let i = 0; i < 4; i++) m[8 + i] = 2 * (m[8 + i] as number) + (m[12 + i] as number);
  const out = new Float32Array(16);
  for (let r = 0; r < 4; r++) for (let col = 0; col < 4; col++) out[col * 4 + r] = m[r * 4 + col] as number;
  return out;
}

/** Expand a GX 3x4 row-major matrix into a column-major GL mat4. */
export function gxMtx3x4ToGl(mtx: Float32Array): Float32Array {
  const out = new Float32Array(16);
  for (let r = 0; r < 3; r++) {
    for (let col = 0; col < 4; col++) out[col * 4 + r] = mtx[r * 4 + col] ?? 0;
  }
  out[15] = 1;
  return out;
}

function glCompare(gl: WebGL2RenderingContext, func: number): number {
  switch (func) {
    case GXCompare.NEVER:
      return gl.NEVER;
    case GXCompare.LESS:
      return gl.LESS;
    case GXCompare.EQUAL:
      return gl.EQUAL;
    case GXCompare.LEQUAL:
      return gl.LEQUAL;
    case GXCompare.GREATER:
      return gl.GREATER;
    case GXCompare.NEQUAL:
      return gl.NOTEQUAL;
    case GXCompare.GEQUAL:
      return gl.GEQUAL;
    default:
      return gl.ALWAYS;
  }
}

function glBlendFactor(gl: WebGL2RenderingContext, factor: number, isSource: boolean): number {
  switch (factor) {
    case GXBlendFactor.ZERO:
      return gl.ZERO;
    case GXBlendFactor.ONE:
      return gl.ONE;
    // GX names the factor by which channel it READS; on the source side
    // GX_BL_SRCCLR means "the destination colour" and vice versa. This is the
    // SDK's documented asymmetry and getting it backwards is a classic bug.
    case GXBlendFactor.SRCCLR:
      return isSource ? gl.DST_COLOR : gl.SRC_COLOR;
    case GXBlendFactor.INVSRCCLR:
      return isSource ? gl.ONE_MINUS_DST_COLOR : gl.ONE_MINUS_SRC_COLOR;
    case GXBlendFactor.SRCALPHA:
      return gl.SRC_ALPHA;
    case GXBlendFactor.INVSRCALPHA:
      return gl.ONE_MINUS_SRC_ALPHA;
    case GXBlendFactor.DSTALPHA:
      return gl.DST_ALPHA;
    case GXBlendFactor.INVDSTALPHA:
      return gl.ONE_MINUS_DST_ALPHA;
    default:
      return gl.ONE;
  }
}

/** GX primitive byte -> (GL mode, index expansion). */
function glPrimitive(
  gl: WebGL2RenderingContext,
  primitive: number,
  vertexCount: number,
): { mode: number; indices: Uint16Array | null } | null {
  switch (primitive) {
    case GXPrimitive.TRIANGLES:
      return { mode: gl.TRIANGLES, indices: null };
    case GXPrimitive.TRIANGLESTRIP:
      return { mode: gl.TRIANGLE_STRIP, indices: null };
    case GXPrimitive.TRIANGLEFAN:
      return { mode: gl.TRIANGLE_FAN, indices: null };
    case GXPrimitive.LINES:
      return { mode: gl.LINES, indices: null };
    case GXPrimitive.LINESTRIP:
      return { mode: gl.LINE_STRIP, indices: null };
    case GXPrimitive.POINTS:
      return { mode: gl.POINTS, indices: null };
    case GXPrimitive.QUADS: {
      // GL has no quads: expand each group of 4 into two triangles. This is
      // an exact expansion for planar convex quads, which is what GX quads
      // are, but it fixes the diagonal — a non-planar quad rasterizes
      // slightly differently than Flipper's own split.
      const quads = Math.floor(vertexCount / 4);
      const indices = new Uint16Array(quads * 6);
      for (let q = 0; q < quads; q++) {
        const base = q * 4;
        indices.set([base, base + 1, base + 2, base, base + 2, base + 3], q * 6);
      }
      return { mode: gl.TRIANGLES, indices };
    }
    default:
      return null;
  }
}

/**
 * WebGL2 backend.
 *
 * Deliberately small: one program, one dynamic buffer, per-primitive state
 * application. It is a foundation for the seam, not an optimized renderer —
 * batching, TEV translation and texture upload are named in `diagnostics` and
 * in docs/gx-hle-host.md as missing rather than approximated.
 */
export class GxWebglBackend implements GxBackend {
  readonly recorder = new GxRecordingBackend();
  readonly diagnostics: string[] = [];
  readonly gl: WebGL2RenderingContext;

  #program: WebGLProgram;
  #vao: WebGLVertexArrayObject;
  #posBuf: WebGLBuffer;
  #colBuf: WebGLBuffer;
  #uvBuf: WebGLBuffer;
  #indexBuf: WebGLBuffer;
  #uProj: WebGLUniformLocation;
  #uPosMtx: WebGLUniformLocation;
  #uMatColor: WebGLUniformLocation;
  #seenDiagnostics = new Set<string>();

  constructor(gl: WebGL2RenderingContext) {
    this.gl = gl;
    this.#program = this.#link(VERT, FRAG);
    const vao = gl.createVertexArray();
    const posBuf = gl.createBuffer();
    const colBuf = gl.createBuffer();
    const uvBuf = gl.createBuffer();
    const indexBuf = gl.createBuffer();
    if (!vao || !posBuf || !colBuf || !uvBuf || !indexBuf) throw new Error("GX WebGL backend: buffer allocation failed");
    this.#vao = vao;
    this.#posBuf = posBuf;
    this.#colBuf = colBuf;
    this.#uvBuf = uvBuf;
    this.#indexBuf = indexBuf;
    const proj = gl.getUniformLocation(this.#program, "uProj");
    const posMtx = gl.getUniformLocation(this.#program, "uPosMtx");
    const matColor = gl.getUniformLocation(this.#program, "uMatColor");
    if (!proj || !posMtx || !matColor) throw new Error("GX WebGL backend: uniform lookup failed");
    this.#uProj = proj;
    this.#uPosMtx = posMtx;
    this.#uMatColor = matColor;

    gl.bindVertexArray(this.#vao);
    gl.bindBuffer(gl.ARRAY_BUFFER, this.#posBuf);
    gl.enableVertexAttribArray(0);
    gl.vertexAttribPointer(0, 3, gl.FLOAT, false, 0, 0);
    gl.bindBuffer(gl.ARRAY_BUFFER, this.#colBuf);
    gl.enableVertexAttribArray(1);
    gl.vertexAttribPointer(1, 4, gl.UNSIGNED_BYTE, true, 0, 0);
    gl.bindBuffer(gl.ARRAY_BUFFER, this.#uvBuf);
    gl.enableVertexAttribArray(2);
    gl.vertexAttribPointer(2, 2, gl.FLOAT, false, 0, 0);
    gl.bindVertexArray(null);

    this.#note(
      "claim bar: framebuffer-equivalent, never pixel-identical — TEV, EFB copy semantics, " +
        "fixed-point rasterization rules and filter kernels are not reproduced",
    );
  }

  #link(vertexSource: string, fragmentSource: string): WebGLProgram {
    const gl = this.gl;
    const compile = (type: number, source: string): WebGLShader => {
      const shader = gl.createShader(type);
      if (!shader) throw new Error("GX WebGL backend: shader allocation failed");
      gl.shaderSource(shader, source);
      gl.compileShader(shader);
      if (!gl.getShaderParameter(shader, gl.COMPILE_STATUS)) {
        throw new Error(`GX WebGL backend: shader compile failed: ${gl.getShaderInfoLog(shader) ?? ""}`);
      }
      return shader;
    };
    const program = gl.createProgram();
    if (!program) throw new Error("GX WebGL backend: program allocation failed");
    gl.attachShader(program, compile(gl.VERTEX_SHADER, vertexSource));
    gl.attachShader(program, compile(gl.FRAGMENT_SHADER, fragmentSource));
    gl.linkProgram(program);
    if (!gl.getProgramParameter(program, gl.LINK_STATUS)) {
      throw new Error(`GX WebGL backend: link failed: ${gl.getProgramInfoLog(program) ?? ""}`);
    }
    return program;
  }

  /** Record an approximation once. Deduplicated so the list stays readable
   *  without ever suppressing a NEW kind of deviation. */
  #note(message: string): void {
    if (this.#seenDiagnostics.has(message)) return;
    this.#seenDiagnostics.add(message);
    this.diagnostics.push(message);
    this.recorder.diagnostics.push(message);
  }

  beginFrame(): void {
    const gl = this.gl;
    this.recorder.beginFrame();
    gl.viewport(0, 0, gl.drawingBufferWidth, gl.drawingBufferHeight);
    gl.disable(gl.SCISSOR_TEST);
    gl.clearColor(0, 0, 0, 1);
    gl.clearDepth(1);
    gl.depthMask(true);
    gl.clear(gl.COLOR_BUFFER_BIT | gl.DEPTH_BUFFER_BIT);
  }

  endFrame(): void {
    this.recorder.endFrame();
    this.gl.flush();
  }

  submit(primitive: GxPrimitiveData): void {
    this.recorder.submit(primitive);
    const gl = this.gl;
    const shape = glPrimitive(gl, primitive.primitive, primitive.vertexCount);
    if (!shape) {
      // Loud, not silent: an undrawn primitive is a hole in the frame.
      this.#note(`unimplemented primitive ${primitiveName(primitive.primitive)} — ${primitive.vertexCount} vertices NOT drawn`);
      return;
    }
    if (primitive.posMtxIdx) {
      this.#note(
        "GX_VA_PNMTXIDX present: per-vertex position matrices are NOT applied — the draw uses the " +
          "GXSetCurrentMtx matrix for every vertex, so skinned geometry will be wrong",
      );
    }
    if (primitive.state.chanEnabled) {
      this.#note(
        "GXSetChanCtrl enabled lighting for this channel, but GX per-vertex lighting is NOT evaluated — " +
          "the draw is unlit (no light objects, no diffuse/attenuation functions)",
      );
    }
    if (primitive.state.numTevStages > 1) {
      this.#note(
        `${primitive.state.numTevStages} TEV stages requested but the TEV combiner is NOT translated — ` +
          "only the vertex colour reaches the framebuffer",
      );
    }
    if (primitive.state.tevTexMap !== 0xff) {
      this.#note(
        `TEV stage 0 selects texmap ${primitive.state.tevTexMap} but texture sampling is NOT implemented — ` +
          "the draw is vertex-colour only",
      );
    }
    this.#applyState(primitive.state);

    const count = primitive.vertexCount;
    const colors = primitive.colors ?? new Uint8Array(count * 4).fill(255);
    const uvs = primitive.texcoords ?? new Float32Array(count * 2);

    gl.useProgram(this.#program);
    gl.uniformMatrix4fv(this.#uProj, false, gxProjectionToGl(primitive.state.projection));
    gl.uniformMatrix4fv(this.#uPosMtx, false, gxMtx3x4ToGl(primitive.state.posMtx));
    // GXSetChanCtrl's mat_src decides whether the material colour register
    // participates at all. Folding it in when the ROM selected GX_SRC_VTX
    // would tint every 2D draw in the game.
    const mc = primitive.state.matSrcVertex ? [255, 255, 255, 255] : Array.from(primitive.state.matColor);
    gl.uniform4f(
      this.#uMatColor,
      (mc[0] ?? 255) / 255,
      (mc[1] ?? 255) / 255,
      (mc[2] ?? 255) / 255,
      (mc[3] ?? 255) / 255,
    );

    gl.bindVertexArray(this.#vao);
    gl.bindBuffer(gl.ARRAY_BUFFER, this.#posBuf);
    gl.bufferData(gl.ARRAY_BUFFER, primitive.positions, gl.DYNAMIC_DRAW);
    gl.bindBuffer(gl.ARRAY_BUFFER, this.#colBuf);
    gl.bufferData(gl.ARRAY_BUFFER, colors, gl.DYNAMIC_DRAW);
    gl.bindBuffer(gl.ARRAY_BUFFER, this.#uvBuf);
    gl.bufferData(gl.ARRAY_BUFFER, uvs, gl.DYNAMIC_DRAW);

    if (shape.indices) {
      gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, this.#indexBuf);
      gl.bufferData(gl.ELEMENT_ARRAY_BUFFER, shape.indices, gl.DYNAMIC_DRAW);
      gl.drawElements(shape.mode, shape.indices.length, gl.UNSIGNED_SHORT, 0);
    } else {
      gl.drawArrays(shape.mode, 0, count);
    }
    gl.bindVertexArray(null);
  }

  #applyState(state: GxDrawState): void {
    const gl = this.gl;
    switch (state.cullMode) {
      case GXCullMode.NONE:
        gl.disable(gl.CULL_FACE);
        break;
      case GXCullMode.ALL:
        gl.enable(gl.CULL_FACE);
        gl.cullFace(gl.FRONT_AND_BACK);
        break;
      case GXCullMode.FRONT:
        gl.enable(gl.CULL_FACE);
        // GX_CULL_FRONT culls the front face as GX defines winding, which is
        // the opposite of GL's default; the front-face winding is set below.
        gl.cullFace(gl.FRONT);
        break;
      default:
        gl.enable(gl.CULL_FACE);
        gl.cullFace(gl.BACK);
        break;
    }
    gl.frontFace(gl.CW); // GX treats clockwise as front-facing.

    if (state.zCompareEnable) {
      gl.enable(gl.DEPTH_TEST);
      gl.depthFunc(glCompare(gl, state.zFunc));
    } else {
      gl.disable(gl.DEPTH_TEST);
    }
    gl.depthMask(state.zUpdate);

    if (state.blendMode === GXBlendMode.BLEND) {
      gl.enable(gl.BLEND);
      gl.blendFunc(glBlendFactor(gl, state.blendSrc, true), glBlendFactor(gl, state.blendDst, false));
    } else if (state.blendMode === GXBlendMode.SUBTRACT) {
      gl.enable(gl.BLEND);
      gl.blendEquation(gl.FUNC_REVERSE_SUBTRACT);
      gl.blendFunc(gl.ONE, gl.ONE);
    } else {
      if (state.blendMode === GXBlendMode.LOGIC) {
        this.#note("GX_BM_LOGIC blend mode has no WebGL equivalent — the draw is rendered unblended");
      }
      gl.disable(gl.BLEND);
      gl.blendEquation(gl.FUNC_ADD);
    }
    gl.colorMask(state.colorUpdate, state.colorUpdate, state.colorUpdate, state.alphaUpdate);
  }

  dispose(): void {
    const gl = this.gl;
    gl.deleteBuffer(this.#posBuf);
    gl.deleteBuffer(this.#colBuf);
    gl.deleteBuffer(this.#uvBuf);
    gl.deleteBuffer(this.#indexBuf);
    gl.deleteVertexArray(this.#vao);
    gl.deleteProgram(this.#program);
    this.recorder.dispose();
  }
}
