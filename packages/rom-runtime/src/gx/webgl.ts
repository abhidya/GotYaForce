// =============================================================================
// webgl.ts — the WebGL2 rasterizer behind the GX seam.
//
// CLAIM BAR, normative and repeated at every reporting surface:
// **framebuffer-equivalent, never pixel-identical**
// (docs/playable-port-design.md V3 non-fatal note 1). WebGL rasterization
// cannot match Flipper: GameCube fixed-point rasterization rules, EFB copy
// semantics, the 24-bit depth buffer's exact comparison behaviour and the
// texture filter kernels all differ. The TEV combiner is now TRANSLATED rather
// than ignored — see tev.ts — but a translation is not the hardware: GX
// combines in a signed 10-bit fixed-point space with per-stage rounding, and
// this generates float math. This backend aims to put the RIGHT GEOMETRY in the
// RIGHT PLACE with the right combiner program, blend and depth intent, and it
// names everything it approximates in `diagnostics`.
//
// AND, stated as plainly: this path has no trace verification behind it. No
// frame it produces has ever been compared against a real GameCube frame. Its
// status is SCAFFOLDING, not a renderer. See docs/gx-hle-host.md.
// =============================================================================

import {
  GXAttnFn,
  GXBlendFactor,
  GXBlendMode,
  GXColorSrc,
  GXCompare,
  GXCullMode,
  GXCompType,
  GXDiffuseFn,
  GXPrimitive,
  GXProjectionType,
  GXTexGenSrc,
  GXTexGenType,
  GXTexWrapMode,
  GX_IDENTITY_MTX,
  GX_MAX_TEXMAP,
  GX_PTIDENTITY,
  GX_TEXMAP_NULL,
  primitiveName,
} from "./enums.js";
import type { GxBackend } from "./backend.js";
import { GxRecordingBackend } from "./backend.js";
import type { GxPrimitive as GxPrimitiveData } from "./fifo.js";
import type { GxDrawState, GxTexObj } from "./state.js";
import { generateTevShader, type GxTevShaderConfig } from "./tev.js";
import { decodeTextureFromMemory, texFormatName, type GxDecodedTexture } from "./texture.js";
import type { GcMemory } from "../memory.js";

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

const IDENTITY4 = Float32Array.from([1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1]);

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

function glWrap(gl: WebGL2RenderingContext, wrap: number): number {
  switch (wrap) {
    case GXTexWrapMode.REPEAT:
      return gl.REPEAT;
    case GXTexWrapMode.MIRROR:
      return gl.MIRRORED_REPEAT;
    default:
      return gl.CLAMP_TO_EDGE;
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

// =============================================================================
// Vertex-stage generation: texgen and the colour channels
// =============================================================================

interface VertexConfig {
  numTexGens: number;
  numChans: number;
  texGens: GxDrawState["texGens"];
  chanCtrl: GxDrawState["chanCtrl"];
  hasNormals: boolean;
  hasColors: boolean;
}

/**
 * Generate the vertex shader.
 *
 * TEXGEN is corpus-grounded in its wiring (which source feeds which generator,
 * and which matrix row it multiplies through — see GXTexGenSrc / GXTexGenType
 * in enums.ts, both read out of gnt4_GXSetTexCoordGen2_bl's own dispatch).
 *
 * LIGHTING is [SDK]: the decompiled SDK only packs light objects into XF
 * registers, so the illumination model below — ambient plus per-light
 * `attenuation * diffuse * colour`, clamped, times the material colour — comes
 * from the documented GX channel pipeline, not from this corpus. The light
 * OBJECT LAYOUT it reads is corpus-settled (see GX_LIGHT_OBJ_BYTES).
 */
function generateVertexShader(config: VertexConfig): { source: string; diagnostics: string[] } {
  const diagnostics: string[] = [];
  const n = Math.max(0, Math.min(config.numTexGens, 8));
  const outs = Array.from({ length: n }, (_, i) => `out vec3 vTexCoord${i};`).join("\n");

  const texgenBody: string[] = [];
  for (let i = 0; i < n; i++) {
    const gen = config.texGens[i];
    if (!gen) {
      texgenBody.push(`  vTexCoord${i} = vec3(0.0, 0.0, 1.0);`);
      continue;
    }
    let src: string | null = null;
    if (gen.src >= GXTexGenSrc.TEX0 && gen.src <= GXTexGenSrc.TEX7) {
      if (gen.src !== GXTexGenSrc.TEX0) {
        diagnostics.push(
          `texgen ${i} sources GX_TG_TEX${gen.src - GXTexGenSrc.TEX0}, but the FIFO decoder only assembles TEX0 — ` +
            `the generator read TEX0's coordinates instead`,
        );
      }
      src = "vec4(aTex0, 0.0, 1.0)";
    } else if (gen.src === GXTexGenSrc.POS) {
      src = "vec4(aPos, 1.0)";
    } else if (gen.src === GXTexGenSrc.NRM) {
      if (!config.hasNormals) {
        diagnostics.push(`texgen ${i} sources GX_TG_NRM but the draw carried no normals — generated from zero`);
      }
      src = "vec4(aNrm, 1.0)";
    } else {
      diagnostics.push(
        `texgen ${i} sources ${GXTexGenSrc[gen.src] ?? `0x${gen.src.toString(16)}`}, which this host does not ` +
          `generate — the coordinate was left at (0,0)`,
      );
      texgenBody.push(`  vTexCoord${i} = vec3(0.0, 0.0, 1.0);`);
      continue;
    }
    if (gen.type !== GXTexGenType.MTX2x4 && gen.type !== GXTexGenType.MTX3x4) {
      diagnostics.push(
        `texgen ${i} uses function ${gen.type} (bump/SRTG), which this host does not evaluate — ` +
          `the coordinate was generated by the matrix path instead`,
      );
    }
    const q = gen.type === GXTexGenType.MTX3x4 ? `dot(uTexMtxRow2[${i}], ${src})` : "1.0";
    texgenBody.push(`  vTexCoord${i} = vec3(dot(uTexMtxRow0[${i}], ${src}), dot(uTexMtxRow1[${i}], ${src}), ${q});`);
    if (gen.postMtx !== GX_PTIDENTITY) {
      diagnostics.push(
        `texgen ${i} names post-transform matrix ${gen.postMtx}, which this host does not apply — ` +
          `the identity was used`,
      );
    }
    if (gen.normalize) {
      diagnostics.push(`texgen ${i} asks for a normalized source, which this host does not apply`);
    }
  }

  const chanBody: string[] = [];
  for (let c = 0; c < 2; c++) {
    const ctrl = config.chanCtrl[c];
    const dst = `vChan${c}`;
    if (!ctrl || c >= Math.max(config.numChans, 1)) {
      // A channel the ROM did not declare produces opaque white, so a TEV
      // stage that reads it multiplies by one rather than blacking out.
      chanBody.push(`  ${dst} = vec4(1.0);`);
      continue;
    }
    const matExpr = ctrl.matSrc === GXColorSrc.VERTEX ? "aColor0" : `uMatColor[${c}]`;
    if (ctrl.matSrc === GXColorSrc.VERTEX && !config.hasColors) {
      diagnostics.push(
        `channel ${c} takes its material colour from the VERTEX (GXSetChanCtrl mat_src = GX_SRC_VTX) but the ` +
          `draw carried no CLR0 attribute — white was substituted`,
      );
    }
    if (!ctrl.enabled) {
      chanBody.push(`  ${dst} = ${matExpr};`);
      continue;
    }
    if (!config.hasNormals) {
      diagnostics.push(
        `channel ${c} has lighting ENABLED but the draw carried no normals — the diffuse term was ` +
          `evaluated against a zero normal`,
      );
    }
    const ambExpr = ctrl.ambSrc === GXColorSrc.VERTEX ? "aColor0" : `uAmbColor[${c}]`;
    chanBody.push(`  {`);
    chanBody.push(`    vec3 illum = ${ambExpr}.rgb;`);
    chanBody.push(`    float ialpha = ${ambExpr}.a;`);
    for (let li = 0; li < 8; li++) {
      if ((ctrl.lightMask & (1 << li)) === 0) continue;
      chanBody.push(`    illum += gxLight(${li}, eyePos, eyeNrm, ${ctrl.diffFn}, ${ctrl.attnFn});`);
    }
    chanBody.push(`    ${dst} = vec4(${matExpr}.rgb * clamp(illum, 0.0, 1.0), ${matExpr}.a * clamp(ialpha, 0.0, 1.0));`);
    chanBody.push(`  }`);
  }

  const source = `#version 300 es
precision highp float;
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec4 aColor0;
layout(location = 2) in vec2 aTex0;
layout(location = 3) in vec3 aNrm;
uniform mat4 uProj;
uniform mat4 uPosMtx;
uniform mat4 uNrmMtx;
uniform vec4 uTexMtxRow0[8];
uniform vec4 uTexMtxRow1[8];
uniform vec4 uTexMtxRow2[8];
uniform vec4 uMatColor[2];
uniform vec4 uAmbColor[2];
uniform vec4 uLightColor[8];
uniform vec4 uLightPos[8];
uniform vec4 uLightDir[8];
uniform vec4 uLightAngle[8];
uniform vec4 uLightDist[8];
out vec4 vChan0;
out vec4 vChan1;
${outs}

// The documented GX per-light term. [SDK] — see the file header.
vec3 gxLight(int i, vec3 eyePos, vec3 nrm, int diffFn, int attnFn) {
  vec3 toLight = uLightPos[i].xyz - eyePos;
  float dist2 = dot(toLight, toLight);
  float dist = sqrt(max(dist2, 1e-12));
  vec3 ldir = toLight / dist;
  float attn = 1.0;
  if (attnFn == ${GXAttnFn.SPOT}) {
    // The light object stores the NEGATED direction (corpus: GXInitLightDir
    // writes -dir at object offset 0x34), so this dots against it directly.
    float cosA = max(dot(ldir, normalize(uLightDir[i].xyz + vec3(1e-9))), 0.0);
    float ang = uLightAngle[i].x + uLightAngle[i].y * cosA + uLightAngle[i].z * cosA * cosA;
    float den = uLightDist[i].x + uLightDist[i].y * dist + uLightDist[i].z * dist2;
    attn = max(ang, 0.0) / max(den, 1e-6);
  } else if (attnFn == ${GXAttnFn.SPEC}) {
    float cosA = max(dot(nrm, ldir), 0.0);
    float ang = uLightAngle[i].x + uLightAngle[i].y * cosA + uLightAngle[i].z * cosA * cosA;
    float den = uLightDist[i].x + uLightDist[i].y * cosA + uLightDist[i].z * cosA * cosA;
    attn = max(ang, 0.0) / max(den, 1e-6);
  }
  float diff = 1.0;
  if (diffFn == ${GXDiffuseFn.SIGN}) diff = dot(nrm, ldir);
  else if (diffFn == ${GXDiffuseFn.CLAMP}) diff = max(dot(nrm, ldir), 0.0);
  return attn * diff * uLightColor[i].rgb;
}

void main() {
  vec4 eye = uPosMtx * vec4(aPos, 1.0);
  vec3 eyePos = eye.xyz;
  vec3 eyeNrm = normalize((uNrmMtx * vec4(aNrm, 0.0)).xyz + vec3(1e-9));
  gl_Position = uProj * eye;
${chanBody.join("\n")}
${texgenBody.join("\n")}
}
`;
  return { source, diagnostics };
}

// =============================================================================
// The backend
// =============================================================================

interface CachedProgram {
  program: WebGLProgram;
  uniforms: Map<string, WebGLUniformLocation>;
  sampledTexMaps: number[];
}

interface CachedTexture {
  texture: WebGLTexture;
  decoded: GxDecodedTexture;
}

/**
 * WebGL2 backend.
 *
 * One generated program per distinct TEV/texgen/channel configuration, cached
 * by shader source; one dynamic buffer set; per-primitive state application. It
 * is a foundation for the seam, not an optimized renderer — batching and EFB
 * modelling are named in `diagnostics` and in docs/gx-hle-host.md as missing
 * rather than approximated.
 */
export class GxWebglBackend implements GxBackend {
  readonly recorder = new GxRecordingBackend();
  readonly diagnostics: string[] = [];
  readonly gl: WebGL2RenderingContext;
  /** The shared arena, needed to decode texture images at their GC addresses.
   *  Null means textures cannot be decoded, which is reported per draw rather
   *  than silently producing untextured geometry. */
  readonly mem: GcMemory | null;

  #vao: WebGLVertexArrayObject;
  #posBuf: WebGLBuffer;
  #colBuf: WebGLBuffer;
  #uvBuf: WebGLBuffer;
  #nrmBuf: WebGLBuffer;
  #indexBuf: WebGLBuffer;
  #seenDiagnostics = new Set<string>();
  #programs = new Map<string, CachedProgram>();
  #textures = new Map<string, CachedTexture>();
  /** Program cache misses, so a report can show the shader count is bounded. */
  programCount = 0;
  /** Textures decoded and uploaded, and their total decoded byte size. */
  textureCount = 0;
  textureBytes = 0;

  constructor(gl: WebGL2RenderingContext, mem: GcMemory | null = null) {
    this.gl = gl;
    this.mem = mem;
    const vao = gl.createVertexArray();
    const posBuf = gl.createBuffer();
    const colBuf = gl.createBuffer();
    const uvBuf = gl.createBuffer();
    const nrmBuf = gl.createBuffer();
    const indexBuf = gl.createBuffer();
    if (!vao || !posBuf || !colBuf || !uvBuf || !nrmBuf || !indexBuf) {
      throw new Error("GX WebGL backend: buffer allocation failed");
    }
    this.#vao = vao;
    this.#posBuf = posBuf;
    this.#colBuf = colBuf;
    this.#uvBuf = uvBuf;
    this.#nrmBuf = nrmBuf;
    this.#indexBuf = indexBuf;

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
    gl.bindBuffer(gl.ARRAY_BUFFER, this.#nrmBuf);
    gl.enableVertexAttribArray(3);
    gl.vertexAttribPointer(3, 3, gl.FLOAT, false, 0, 0);
    gl.bindVertexArray(null);

    this.#note(
      "claim bar: framebuffer-equivalent, never pixel-identical — the TEV is translated to a " +
        "generated shader but GX's signed 10-bit fixed-point combine, EFB copy semantics, " +
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
        throw new Error(
          `GX WebGL backend: shader compile failed: ${gl.getShaderInfoLog(shader) ?? ""}\n--- source ---\n${source}`,
        );
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

  // --- textures --------------------------------------------------------------

  /**
   * Decode and upload a texture object, or return the cached upload.
   *
   * Returns null when the texture cannot be produced, having said WHY in the
   * diagnostics. A null here means the sampling stage reports an unbound map
   * rather than the frame quietly losing its texture.
   */
  #texture(obj: GxTexObj, state: GxDrawState): CachedTexture | null {
    const key = `${obj.imageAddr}:${obj.format}:${obj.width}:${obj.height}:${obj.tlutAddr ?? -1}`;
    const hit = this.#textures.get(key);
    if (hit) return hit;
    const mem = this.mem;
    if (!mem) {
      this.#note(
        "a draw bound a texture but the backend was constructed without the shared arena, so no image " +
          "data is readable — textures cannot be decoded at all in this configuration",
      );
      return null;
    }
    let tlutBytes: Uint8Array | null = null;
    let tlutFormat = obj.tlutFormat;
    if (obj.tlutAddr !== null) {
      try {
        tlutBytes = mem.readBytes(obj.tlutAddr >>> 0, Math.max(obj.tlutEntries, 1) * 2);
      } catch {
        this.#note(`the palette at 0x${(obj.tlutAddr >>> 0).toString(16)} is not readable in the arena`);
      }
    } else if (state.textures.some((t) => t === obj)) {
      tlutFormat = obj.tlutFormat;
    }
    let decoded: GxDecodedTexture;
    try {
      decoded = decodeTextureFromMemory(mem, obj.imageAddr, obj.format, obj.width, obj.height, tlutBytes, tlutFormat);
    } catch (error) {
      this.#note(
        `texture ${texFormatName(obj.format)} ${obj.width}x${obj.height} at ` +
          `0x${(obj.imageAddr >>> 0).toString(16)} could NOT be decoded: ` +
          `${error instanceof Error ? error.message : String(error)}`,
      );
      return null;
    }
    for (const d of decoded.diagnostics) this.#note(`texture 0x${(obj.imageAddr >>> 0).toString(16)}: ${d}`);
    const gl = this.gl;
    const texture = gl.createTexture();
    if (!texture) throw new Error("GX WebGL backend: texture allocation failed");
    gl.bindTexture(gl.TEXTURE_2D, texture);
    gl.pixelStorei(gl.UNPACK_ALIGNMENT, 1);
    gl.texImage2D(
      gl.TEXTURE_2D,
      0,
      gl.RGBA,
      decoded.width,
      decoded.height,
      0,
      gl.RGBA,
      gl.UNSIGNED_BYTE,
      decoded.rgba,
    );
    gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_WRAP_S, glWrap(gl, obj.wrapS));
    gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_WRAP_T, glWrap(gl, obj.wrapT));
    // Only the base level is uploaded, so both filters collapse to the
    // non-mipmapped pair. A ROM asking for a mip filter gets the base level.
    const mag = obj.magFilter === 0 ? gl.NEAREST : gl.LINEAR;
    const min = obj.minFilter === 0 ? gl.NEAREST : gl.LINEAR;
    gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MAG_FILTER, mag);
    gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MIN_FILTER, min);
    if (obj.mipmap) {
      this.#note("a texture object declares mipmaps, but only the base level is decoded and uploaded");
    }
    const entry: CachedTexture = { texture, decoded };
    this.#textures.set(key, entry);
    this.textureCount += 1;
    this.textureBytes += decoded.rgba.length;
    return entry;
  }

  // --- draw ------------------------------------------------------------------

  submit(primitive: GxPrimitiveData): void {
    this.recorder.submit(primitive);
    const gl = this.gl;
    const state = primitive.state;
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
    if (state.scissor[2] !== 0 && (state.scissor[0] !== 0 || state.scissor[1] !== 0)) {
      this.#note(
        `GXSetScissor(${state.scissor.join(", ")}) is latched but NOT applied — the draw is not clipped to it`,
      );
    }

    // --- resolve which texmaps have a real, decoded texture -----------------
    const bound: boolean[] = new Array<boolean>(GX_MAX_TEXMAP).fill(false);
    const uploads: Array<CachedTexture | null> = new Array<CachedTexture | null>(GX_MAX_TEXMAP).fill(null);
    const wanted = new Set<number>();
    const stageCount = Math.max(1, Math.min(state.numTevStages, 16));
    for (let i = 0; i < stageCount; i++) {
      const s = state.tevStages[i];
      if (s && s.texMap !== GX_TEXMAP_NULL) wanted.add(s.texMap & 7);
    }
    for (const map of wanted) {
      const obj = state.textures[map];
      if (!obj) {
        this.#note(
          `a TEV stage selects GX_TEXMAP${map} but GXLoadTexObj never bound a texture object to that slot`,
        );
        continue;
      }
      const up = this.#texture(obj, state);
      if (up) {
        bound[map] = true;
        uploads[map] = up;
      }
    }

    // --- generate / fetch the program ---------------------------------------
    const tevConfig: GxTevShaderConfig = {
      numTevStages: state.numTevStages,
      stages: state.tevStages,
      swapTable: state.swapTable,
      alphaCompare: state.alphaCompare,
      numTexGens: state.numTexGens,
      numChans: state.numChans,
      boundTexMaps: bound,
    };
    const tev = generateTevShader(tevConfig);
    const vs = generateVertexShader({
      numTexGens: state.numTexGens,
      numChans: state.numChans,
      texGens: state.texGens,
      chanCtrl: state.chanCtrl,
      hasNormals: primitive.normals !== null,
      hasColors: primitive.colors !== null,
    });
    for (const d of tev.diagnostics) this.#note(d);
    for (const d of vs.diagnostics) this.#note(d);

    const key = `${vs.source} ${tev.fragmentSource}`;
    let cached = this.#programs.get(key);
    if (!cached) {
      const program = this.#link(vs.source, tev.fragmentSource);
      cached = { program, uniforms: new Map(), sampledTexMaps: tev.sampledTexMaps };
      this.#programs.set(key, cached);
      this.programCount += 1;
    }
    const uniform = (name: string): WebGLUniformLocation | null => {
      const c = cached as CachedProgram;
      if (c.uniforms.has(name)) return c.uniforms.get(name) ?? null;
      const loc = gl.getUniformLocation(c.program, name);
      if (loc) c.uniforms.set(name, loc);
      return loc;
    };

    this.#applyState(state);
    gl.useProgram(cached.program);

    // --- uniforms -----------------------------------------------------------
    const uProj = uniform("uProj");
    if (uProj) gl.uniformMatrix4fv(uProj, false, gxProjectionToGl(state.projection));
    const uPosMtx = uniform("uPosMtx");
    if (uPosMtx) gl.uniformMatrix4fv(uPosMtx, false, gxMtx3x4ToGl(state.posMtx));
    const uNrmMtx = uniform("uNrmMtx");
    if (uNrmMtx) gl.uniformMatrix4fv(uNrmMtx, false, state.nrmMtx ? gxMtx3x4ToGl(state.nrmMtx) : IDENTITY4);

    // Texture matrices, flattened to three rows of four so a texgen can pick
    // its own row set without a per-generator mat4 upload.
    const row0 = new Float32Array(32);
    const row1 = new Float32Array(32);
    const row2 = new Float32Array(32);
    for (let i = 0; i < 8; i++) {
      const gen = state.texGens[i];
      const mtx = gen ? (state.texMtx.get(gen.mtx) ?? null) : null;
      if (!mtx) {
        // No matrix loaded at that row: identity, which passes the source
        // coordinate through unchanged.
        row0.set([1, 0, 0, 0], i * 4);
        row1.set([0, 1, 0, 0], i * 4);
        row2.set([0, 0, 1, 0], i * 4);
        if (gen && gen.mtx !== GX_IDENTITY_MTX) {
          this.#note(
            `texgen ${i} names texture matrix row ${gen.mtx} but GXLoadTexMtxImm never loaded it — identity was used`,
          );
        }
        continue;
      }
      row0.set(mtx.subarray(0, 4), i * 4);
      row1.set(mtx.subarray(4, 8), i * 4);
      row2.set(mtx.subarray(8, 12), i * 4);
    }
    const uRow0 = uniform("uTexMtxRow0");
    if (uRow0) gl.uniform4fv(uRow0, row0);
    const uRow1 = uniform("uTexMtxRow1");
    if (uRow1) gl.uniform4fv(uRow1, row1);
    const uRow2 = uniform("uTexMtxRow2");
    if (uRow2) gl.uniform4fv(uRow2, row2);

    const matColors = new Float32Array(8);
    const ambColors = new Float32Array(8);
    for (let c = 0; c < 2; c++) {
      const m = state.matColors[c];
      const a = state.ambColors[c];
      for (let i = 0; i < 4; i++) {
        matColors[c * 4 + i] = (m?.[i] ?? 255) / 255;
        ambColors[c * 4 + i] = (a?.[i] ?? 0) / 255;
      }
    }
    const uMat = uniform("uMatColor");
    if (uMat) gl.uniform4fv(uMat, matColors);
    const uAmb = uniform("uAmbColor");
    if (uAmb) gl.uniform4fv(uAmb, ambColors);

    const lightColor = new Float32Array(32);
    const lightPos = new Float32Array(32);
    const lightDir = new Float32Array(32);
    const lightAngle = new Float32Array(32);
    const lightDist = new Float32Array(32);
    for (let i = 0; i < 8; i++) {
      const l = state.lights[i];
      if (!l) continue;
      for (let k = 0; k < 4; k++) lightColor[i * 4 + k] = (l.color[k] ?? 0) / 255;
      for (let k = 0; k < 3; k++) {
        lightPos[i * 4 + k] = l.position[k] ?? 0;
        lightDir[i * 4 + k] = l.negDirection[k] ?? 0;
        lightAngle[i * 4 + k] = l.angleAttn[k] ?? 0;
        lightDist[i * 4 + k] = l.distAttn[k] ?? 0;
      }
    }
    const setV4 = (name: string, data: Float32Array): void => {
      const loc = uniform(name);
      if (loc) gl.uniform4fv(loc, data);
    };
    setV4("uLightColor", lightColor);
    setV4("uLightPos", lightPos);
    setV4("uLightDir", lightDir);
    setV4("uLightAngle", lightAngle);
    setV4("uLightDist", lightDist);
    setV4("uKonst", state.tevKColors);
    setV4("uTevReg", state.tevRegs);

    // --- samplers -----------------------------------------------------------
    for (const map of cached.sampledTexMaps) {
      const up = uploads[map];
      const loc = uniform(`uTex${map}`);
      if (!loc) continue;
      gl.activeTexture(gl.TEXTURE0 + map);
      gl.bindTexture(gl.TEXTURE_2D, up ? up.texture : null);
      gl.uniform1i(loc, map);
    }

    // --- geometry -----------------------------------------------------------
    const count = primitive.vertexCount;
    const colors = primitive.colors ?? new Uint8Array(count * 4).fill(255);
    const uvs = primitive.texcoords ?? new Float32Array(count * 2);
    const normals = primitive.normals ?? new Float32Array(count * 3);

    gl.bindVertexArray(this.#vao);
    gl.bindBuffer(gl.ARRAY_BUFFER, this.#posBuf);
    gl.bufferData(gl.ARRAY_BUFFER, primitive.positions, gl.DYNAMIC_DRAW);
    gl.bindBuffer(gl.ARRAY_BUFFER, this.#colBuf);
    gl.bufferData(gl.ARRAY_BUFFER, colors, gl.DYNAMIC_DRAW);
    gl.bindBuffer(gl.ARRAY_BUFFER, this.#uvBuf);
    gl.bufferData(gl.ARRAY_BUFFER, uvs, gl.DYNAMIC_DRAW);
    gl.bindBuffer(gl.ARRAY_BUFFER, this.#nrmBuf);
    gl.bufferData(gl.ARRAY_BUFFER, normals, gl.DYNAMIC_DRAW);

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
      gl.blendEquation(gl.FUNC_ADD);
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

  /** How much shader/texture work this backend did — reported so a green frame
   *  cannot hide an empty program cache. */
  summary(): { programs: number; textures: number; textureBytes: number } {
    return { programs: this.programCount, textures: this.textureCount, textureBytes: this.textureBytes };
  }

  dispose(): void {
    const gl = this.gl;
    gl.deleteBuffer(this.#posBuf);
    gl.deleteBuffer(this.#colBuf);
    gl.deleteBuffer(this.#uvBuf);
    gl.deleteBuffer(this.#nrmBuf);
    gl.deleteBuffer(this.#indexBuf);
    gl.deleteVertexArray(this.#vao);
    for (const p of this.#programs.values()) gl.deleteProgram(p.program);
    for (const t of this.#textures.values()) gl.deleteTexture(t.texture);
    this.#programs.clear();
    this.#textures.clear();
    this.recorder.dispose();
  }
}

// Re-exported so a consumer that only imports the backend still sees the
// component type the FIFO decoder uses for texture coordinates.
export { GXCompType };
