// hsd-anim.ts — HAL Sysdolphin (HSD) animation evaluation, ported from HSDRaw /
// HSDRawViewer (C#) so the browser can sample FOBJ tracks and compose JOBJ local
// transforms with the SAME math the original GameCube game uses — not an
// approximation.
//
// This is the REFERENCE implementation. The current pipeline bakes clips via the
// C# tool (scripts/export-borg-animation-hsd.mjs, which calls the same
// FOBJ_Player.GetValue), so the baked JSON is already faithful; this module lets
// the web app re-derive a clip from raw FOBJ bytes without the C# toolchain and
// validate baked output.
//
// Full derivation with source line references:
//   research/format-specs/hsd-animation-semantics.md
//
// Ported from:
//   tools/HSDLib/HSDRaw/Tools/FOBJ_Decoder.cs        (key stream decode)
//   tools/HSDLib/HSDRaw/Tools/FOBJ_Player.cs         (GetState / GetValue / hermite)
//   tools/HSDLib/HSDRaw/Common/Animation/HSD_FOBJ.cs (enums, flag packing)
//   tools/HSDLib/HSDRawViewer/Rendering/Models/LiveJObj.cs  (SRT composition)
//   tools/HSDLib/HSDRawViewer/Rendering/Math3D.cs    (Euler matrix)
//
// Pure functions, no game-loop / no THREE dependency. All angles are radians.

// ---------------------------------------------------------------------------
// Enums (verbatim from HSD_FOBJ.cs)
// ---------------------------------------------------------------------------

/** GXInterpolationType — per-key interpolation opcode (low nibble of stream header). */
export enum InterpType {
  None = 0x00,
  Constant = 0x01, // HSD_A_OP_CON  — step/hold
  Linear = 0x02, // HSD_A_OP_LIN
  Spline0 = 0x03, // HSD_A_OP_SPL0 — hermite, incoming tangent 0
  Spline = 0x04, // HSD_A_OP_SPL  — hermite with explicit tangent
  Slope = 0x05, // HSD_A_OP_SLP  — tangent-only patch (no value/time)
  Key = 0x06, // HSD_A_OP_KEY  — value-only (no time), step/hold
}

/** JointTrackType — which transform channel an FOBJ drives. Radians for ROT. */
export enum JointTrackType {
  None = 0,
  RotX = 1,
  RotY = 2,
  RotZ = 3,
  Path = 4,
  TraX = 5,
  TraY = 6,
  TraZ = 7,
  ScaX = 8,
  ScaY = 9,
  ScaZ = 10,
  // 11..32: NODE/BRANCH/SETBYTE*/SETFLOAT* — not transform channels
  Ptcl = 40,
}

/** GXAnimDataFormat — packing of a value or tangent (high 3 bits of the flag byte). */
export enum AnimDataFormat {
  Float = 0x00, // HSD_A_FRAC_FLOAT — 4-byte IEEE float, as-is
  S16 = 0x20, // signed   16-bit, value = raw / scale
  U16 = 0x40, // unsigned 16-bit, value = raw / scale
  S8 = 0x60, // signed    8-bit, value = raw / scale
  U8 = 0x80, // unsigned  8-bit, value = raw / scale
}

// ---------------------------------------------------------------------------
// Keyframe + decoded track
// ---------------------------------------------------------------------------

/** One decoded keyframe (mirrors HSDRaw FOBJKey). frame is in animation frames. */
export interface FObjKey {
  frame: number;
  value: number;
  tan: number;
  interp: InterpType;
}

/**
 * Header describing how an FOBJ buffer is packed. Mirrors the ValueFlag /
 * TangentFlag bytes of HSD_FOBJ: bits 0-4 = log2(scale), bits 5-7 = format.
 */
export interface FObjHeader {
  trackType: JointTrackType;
  valueFormat: AnimDataFormat;
  valueScale: number;
  tanFormat: AnimDataFormat;
  tanScale: number;
}

/** A fully-decoded FOBJ track: header + keys, ready to sample. */
export interface FObjTrack {
  trackType: JointTrackType;
  keys: FObjKey[];
}

// ---------------------------------------------------------------------------
// Flag-byte decode (HSD_FOBJ.cs:212-258)
// ---------------------------------------------------------------------------

/** Decode a ValueFlag/TangentFlag byte into {format, scale}. scale = 1<<(flag&0x1F). */
export function decodeFlag(flag: number): { format: AnimDataFormat; scale: number } {
  const scale = 1 << (flag & 0x1f);
  const format = (flag & 0xe0) as AnimDataFormat;
  return { format, scale };
}

// ---------------------------------------------------------------------------
// Varint (BinaryReaderExt.ReadPacked, LEB128-style, little byte first)
// ---------------------------------------------------------------------------

/** Cursor over a little-endian FOBJ buffer with ReadPacked support. */
class StreamReader {
  private readonly view: DataView;
  private pos: number;
  constructor(buffer: ArrayBuffer | Uint8Array, byteOffset = 0, byteLength?: number) {
    if (buffer instanceof Uint8Array) {
      this.view = new DataView(buffer.buffer, buffer.byteOffset + byteOffset, byteLength ?? buffer.byteLength - byteOffset);
    } else {
      this.view = new DataView(buffer, byteOffset, byteLength);
    }
    this.pos = 0;
  }

  get position(): number {
    return this.pos;
  }
  get length(): number {
    return this.view.byteLength;
  }
  atEnd(): boolean {
    return this.pos >= this.view.byteLength;
  }

  /** LEB128 varint, 7 bits/byte, low byte first (BinaryReaderExt.ReadPacked). */
  readPacked(): number {
    let result = 0;
    let shift = 0;
    let parse: number;
    do {
      parse = this.view.getUint8(this.pos++);
      result |= (parse & 0x7f) << shift;
      shift += 7;
    } while ((parse & 0x80) !== 0);
    return result >>> 0;
  }

  /** Read one value/tangent in the given packed format (FOBJ_Decoder.ParseFloat). */
  readFloatScaled(format: AnimDataFormat, scale: number): number {
    switch (format) {
      case AnimDataFormat.Float: {
        const v = this.view.getFloat32(this.pos, true);
        this.pos += 4;
        return v;
      }
      case AnimDataFormat.S16: {
        const v = this.view.getInt16(this.pos, true);
        this.pos += 2;
        return v / scale;
      }
      case AnimDataFormat.U16: {
        const v = this.view.getUint16(this.pos, true);
        this.pos += 2;
        return v / scale;
      }
      case AnimDataFormat.S8: {
        const v = this.view.getInt8(this.pos);
        this.pos += 1;
        return v / scale;
      }
      case AnimDataFormat.U8: {
        const v = this.view.getUint8(this.pos);
        this.pos += 1;
        return v / scale;
      }
      default:
        return 0;
    }
  }
}

// ---------------------------------------------------------------------------
// Decode the keyframe stream (FOBJFrameDecoder.GetKeys, FOBJ_Decoder.cs:45)
// ---------------------------------------------------------------------------

/**
 * Decode a packed FOBJ key buffer into a list of FObjKey. PTCL tracks decode to
 * an empty key list (they are particle opcodes, not transform values).
 *
 * `startFrame` matches HSDRaw's startframe argument; non-zero shifts/bakes keys
 * back to frame 0 exactly as HSDRaw does. For pl****mot.bin borg clips startFrame
 * is 0 (the common case) and the fast path is taken.
 */
export function decodeFObjKeys(buffer: ArrayBuffer | Uint8Array, header: FObjHeader, startFrame = 0): FObjKey[] {
  const keys: FObjKey[] = [];
  if (header.trackType === JointTrackType.Ptcl) return keys;

  const r = new StreamReader(buffer);
  let clock = 0;
  while (!r.atEnd()) {
    const headerByte = r.readPacked();
    const interp = (headerByte & 0x0f) as InterpType;
    const numKeys = (headerByte >> 4) + 1;
    if (interp === InterpType.None) break; // 0 terminates

    for (let i = 0; i < numKeys; i++) {
      let value = 0;
      let tan = 0;
      let time = 0;
      switch (interp) {
        case InterpType.Constant:
        case InterpType.Linear:
        case InterpType.Spline0:
          value = r.readFloatScaled(header.valueFormat, header.valueScale);
          time = r.readPacked();
          break;
        case InterpType.Spline:
          value = r.readFloatScaled(header.valueFormat, header.valueScale);
          tan = r.readFloatScaled(header.tanFormat, header.tanScale);
          time = r.readPacked();
          break;
        case InterpType.Slope:
          tan = r.readFloatScaled(header.tanFormat, header.tanScale);
          break; // no value, no time
        case InterpType.Key:
          value = r.readFloatScaled(header.valueFormat, header.valueScale);
          break; // no time
        default:
          throw new Error(`Unknown FOBJ interpolation type 0x${(interp as number).toString(16)}`);
      }
      keys.push({ frame: clock, value, tan, interp });
      clock += time; // Slope/Key contribute time=0
    }
  }

  if (startFrame !== 0) {
    // HSDRaw "hack for animations that don't start on frame 0": shift, drop the
    // negative region, then bake LINEAR keys from 0 up to the first real key.
    const shifted = keys.map((k) => ({ ...k, frame: k.frame - startFrame })).filter((k) => k.frame >= 0);
    const first = shifted[0];
    if (first && first.frame !== 0) {
      const player = new FObjPlayer({ trackType: header.trackType, keys });
      const baked: FObjKey[] = [];
      for (let f = 0; f < first.frame; f++) {
        baked.push({ frame: f, value: player.getValue(f - startFrame), tan: 0, interp: InterpType.Linear });
      }
      return baked.concat(shifted);
    }
    return shifted;
  }

  return keys;
}

// ---------------------------------------------------------------------------
// Interpolation math (AnimationInterpolationHelper, FOBJ_Player.cs:444)
// ---------------------------------------------------------------------------

/** Linear: HSDRaw Lerp(fterm=dt, time=s, p0, p1). */
export function lerp(dt: number, s: number, p0: number, p1: number): number {
  const slope = (p1 - p0) / dt;
  return slope * s + p0;
}

/**
 * Cubic Hermite, verbatim port of AnimationInterpolationHelper.SplineGetHermite.
 *
 * IMPORTANT: `invDt` is 1/(t1-t0) (the caller passes the reciprocal in HSDRaw),
 * `s` is (frame - t0). Tangents d0/d1 are in value-per-frame units. The float
 * expression order is preserved to stay bit-faithful with the original.
 */
export function splineHermite(invDt: number, s: number, p0: number, p1: number, d0: number, d1: number): number {
  const f1 = s * s;
  let f2 = invDt * invDt * f1 * s;
  const f3 = 3.0 * f1 * invDt * invDt;
  const f4 = f2 - f1 * invDt;
  f2 = 2.0 * f2 * invDt;
  return d1 * f4 + d0 * (s + (f4 - f1 * invDt)) + p0 * (1.0 + (f2 - f3)) + p1 * (-f2 + f3);
}

// ---------------------------------------------------------------------------
// Segment state + value sampling (FOBJ_Player.GetState / GetValue)
// ---------------------------------------------------------------------------

interface AnimState {
  p0: number;
  p1: number;
  d0: number;
  d1: number;
  t0: number;
  t1: number;
  /** interp of the CURRENT key */
  op: InterpType;
  /** interp GOVERNING the segment (the previous key's) — selects the math */
  opIntrp: InterpType;
}

/**
 * Samples a single FOBJ track at an arbitrary (possibly fractional) frame using
 * HSDRaw's exact CON/LIN/HERMITE evaluator. Construct once per track, then call
 * getValue(frame) repeatedly.
 */
export class FObjPlayer {
  readonly trackType: JointTrackType;
  readonly keys: FObjKey[];

  constructor(track: FObjTrack) {
    this.trackType = track.trackType;
    this.keys = track.keys;
  }

  /** Max key frame (>=1), mirrors FOBJ_Player.FrameCount. */
  get frameCount(): number {
    if (this.keys.length === 0) return 0;
    let max = 0;
    for (const k of this.keys) if (k.frame > max) max = k.frame;
    return max < 1 ? 1 : Math.trunc(max);
  }

  /** Build the active segment registers for `frame` (FOBJ_Player.GetState). */
  private getState(frame: number): AnimState {
    const keys = this.keys;
    const last = keys[keys.length - 1];

    // clamp past the end -> hold final key
    if (keys.length > 1 && last && frame >= last.frame) {
      return {
        t0: last.frame,
        t1: last.frame,
        p0: last.value,
        p1: last.value,
        d0: last.tan,
        d1: last.tan,
        op: last.interp,
        opIntrp: last.interp,
      };
    }

    let p0 = 0;
    let p1 = 0;
    let d0 = 0;
    let d1 = 0;
    let t0 = 0;
    let t1 = 0;
    let opIntrp: InterpType = InterpType.Constant;
    let op: InterpType = InterpType.Constant;

    for (let i = 0; i < keys.length; i++) {
      const key = keys[i];
      if (!key) break;
      opIntrp = op;
      op = key.interp;

      switch (op) {
        case InterpType.Constant:
        case InterpType.Linear:
          p0 = p1;
          p1 = key.value;
          if (opIntrp !== InterpType.Slope) {
            d0 = d1;
            d1 = 0;
          }
          t0 = t1;
          t1 = key.frame;
          break;
        case InterpType.Spline0:
          p0 = p1;
          d0 = d1;
          p1 = key.value;
          d1 = 0;
          t0 = t1;
          t1 = key.frame;
          break;
        case InterpType.Spline:
          p0 = p1;
          p1 = key.value;
          d0 = d1;
          d1 = key.tan;
          t0 = t1;
          t1 = key.frame;
          break;
        case InterpType.Slope:
          d0 = d1;
          d1 = key.tan;
          break;
        case InterpType.Key:
          p1 = key.value;
          p0 = key.value;
          break;
        case InterpType.None:
        default:
          break;
      }

      if (t1 > frame && key.interp !== InterpType.Slope) break;

      opIntrp = key.interp;
    }

    return { t0, t1, p0, p1, d0, d1, op, opIntrp };
  }

  /** Sample the track value at `frame` (FOBJ_Player.GetValue). */
  getValue(frame: number): number {
    if (this.keys.length === 0) return 0;
    const s = this.getState(frame);

    if (frame <= s.t0) return s.p0;
    if (frame >= s.t1) return s.p1;
    if (s.t0 === s.t1 || s.opIntrp === InterpType.Constant || s.opIntrp === InterpType.Key) return s.p0;

    const time = frame - s.t0;
    const dt = s.t1 - s.t0;

    if (s.opIntrp === InterpType.Linear) return lerp(dt, time, s.p0, s.p1);

    if (s.opIntrp === InterpType.Spline || s.opIntrp === InterpType.Spline0 || s.opIntrp === InterpType.Slope) {
      return splineHermite(1 / dt, time, s.p0, s.p1, s.d0, s.d1);
    }

    return s.p0;
  }
}

// ---------------------------------------------------------------------------
// JOBJ SRT composition (LiveJObj.RecalculateTransforms / ApplyAnimation,
// Math3D.CreateMatrix4FromEuler)
// ---------------------------------------------------------------------------

/** Per-joint animated SRT for one frame. Rotation is Euler radians (HSD order). */
export interface JointSrt {
  translation: [number, number, number];
  rotation: [number, number, number]; // Euler XYZ, radians
  scale: [number, number, number];
}

/** Default (static) SRT read from the JOBJ desc. */
export interface JointDefaults {
  tx: number;
  ty: number;
  tz: number;
  rx: number;
  ry: number;
  rz: number;
  sx: number;
  sy: number;
  sz: number;
}

/**
 * Apply a frame's tracks over the joint's static defaults (LiveJObj.ApplyAnimation).
 * Channels without a track keep the default. Returns animated SRT for `frame`.
 */
export function applyAnimation(defaults: JointDefaults, tracks: readonly FObjPlayer[], frame: number): JointSrt {
  const srt: JointSrt = {
    translation: [defaults.tx, defaults.ty, defaults.tz],
    rotation: [defaults.rx, defaults.ry, defaults.rz],
    scale: [defaults.sx, defaults.sy, defaults.sz],
  };
  for (const t of tracks) {
    const v = t.getValue(frame);
    switch (t.trackType) {
      case JointTrackType.RotX:
        srt.rotation[0] = v;
        break;
      case JointTrackType.RotY:
        srt.rotation[1] = v;
        break;
      case JointTrackType.RotZ:
        srt.rotation[2] = v;
        break;
      case JointTrackType.TraX:
        srt.translation[0] = v;
        break;
      case JointTrackType.TraY:
        srt.translation[1] = v;
        break;
      case JointTrackType.TraZ:
        srt.translation[2] = v;
        break;
      case JointTrackType.ScaX:
        srt.scale[0] = v;
        break;
      case JointTrackType.ScaY:
        srt.scale[1] = v;
        break;
      case JointTrackType.ScaZ:
        srt.scale[2] = v;
        break;
      default:
        break; // None/Path/Ptcl/etc. — not transform channels
    }
  }
  return srt;
}

/**
 * 4x4 matrix as a flat 16-element array, COLUMN-MAJOR (m[col*4 + row]) — the
 * layout THREE.Matrix4.fromArray and WebGL expect. (HSDRawViewer uses OpenTK
 * row-vector storage internally; we emit the column-vector equivalent, i.e. the
 * transpose, so downstream column-vector math composes correctly.)
 */
export type Mat4 = readonly number[];

/**
 * HSD Euler -> rotation matrix. Column-vector form R = Rx·Ry·Rz (intrinsic XYZ /
 * extrinsic ZYX). This is the transpose of Math3D.CreateMatrix4FromEuler's
 * row-major storage. Returned column-major.
 */
export function eulerToMat4(rx: number, ry: number, rz: number): number[] {
  const sx = Math.sin(rx);
  const cx = Math.cos(rx);
  const sy = Math.sin(ry);
  const cy = Math.cos(ry);
  const sz = Math.sin(rz);
  const cz = Math.cos(rz);

  // column-vector rotation matrix entries m[row][col]
  const m00 = cy * cz;
  const m01 = cz * sx * sy - cx * sz;
  const m02 = cz * cx * sy + sx * sz;
  const m10 = cy * sz;
  const m11 = sz * sx * sy + cx * cz;
  const m12 = sz * cx * sy - sx * cz;
  const m20 = -sy;
  const m21 = sx * cy;
  const m22 = cx * cy;

  // column-major flat: [col0(rows0..3), col1, col2, col3]
  return [m00, m10, m20, 0, m01, m11, m21, 0, m02, m12, m22, 0, 0, 0, 0, 1];
}

/** Quaternion [x,y,z,w] for an HSD Euler rotation (matches the C# baker). */
export function eulerToQuat(rx: number, ry: number, rz: number): [number, number, number, number] {
  const sx = Math.sin(rx);
  const cx = Math.cos(rx);
  const sy = Math.sin(ry);
  const cy = Math.cos(ry);
  const sz = Math.sin(rz);
  const cz = Math.cos(rz);

  const m00 = cy * cz;
  const m01 = cz * sx * sy - cx * sz;
  const m02 = cz * cx * sy + sx * sz;
  const m10 = cy * sz;
  const m11 = sz * sx * sy + cx * cz;
  const m12 = sz * cx * sy - sx * cz;
  const m20 = -sy;
  const m21 = sx * cy;
  const m22 = cx * cy;

  const tr = m00 + m11 + m22;
  let qx: number;
  let qy: number;
  let qz: number;
  let qw: number;
  if (tr > 0) {
    const s = Math.sqrt(tr + 1.0) * 2;
    qw = 0.25 * s;
    qx = (m21 - m12) / s;
    qy = (m02 - m20) / s;
    qz = (m10 - m01) / s;
  } else if (m00 > m11 && m00 > m22) {
    const s = Math.sqrt(1.0 + m00 - m11 - m22) * 2;
    qw = (m21 - m12) / s;
    qx = 0.25 * s;
    qy = (m01 + m10) / s;
    qz = (m02 + m20) / s;
  } else if (m11 > m22) {
    const s = Math.sqrt(1.0 + m11 - m00 - m22) * 2;
    qw = (m02 - m20) / s;
    qx = (m01 + m10) / s;
    qy = 0.25 * s;
    qz = (m12 + m21) / s;
  } else {
    const s = Math.sqrt(1.0 + m22 - m00 - m11) * 2;
    qw = (m10 - m01) / s;
    qx = (m02 + m20) / s;
    qy = (m12 + m21) / s;
    qz = 0.25 * s;
  }
  return [qx, qy, qz, qw];
}

/** Multiply two column-major 4x4 matrices: result = a · b (column-vector convention). */
function mul4(a: number[], b: number[]): number[] {
  const out = new Array<number>(16).fill(0);
  for (let col = 0; col < 4; col++) {
    for (let row = 0; row < 4; row++) {
      let sum = 0;
      for (let k = 0; k < 4; k++) {
        // a[k*4+row] * b[col*4+k]
        sum += (a[k * 4 + row] ?? 0) * (b[col * 4 + k] ?? 0);
      }
      out[col * 4 + row] = sum;
    }
  }
  return out;
}

/**
 * Compose a JOBJ local transform from animated SRT, column-major.
 *
 * HSDRawViewer: LocalTransform = CreateScale(S) * Euler(R) * CreateTranslation(T)
 * in OpenTK row-vector convention, i.e. mathematically M = T · R · S (a point is
 * scaled, then rotated, then translated). We build that column-major.
 *
 * Does NOT handle MTX_SCALE_COMPENSATE (not observed on Gotcha Force borgs); see
 * the spec doc if a scaled joint looks wrong.
 */
export function composeLocalMatrix(srt: JointSrt): number[] {
  const [tx, ty, tz] = srt.translation;
  const [rx, ry, rz] = srt.rotation;
  const [sx, sy, sz] = srt.scale;

  // scale (column-major)
  const S = [sx, 0, 0, 0, 0, sy, 0, 0, 0, 0, sz, 0, 0, 0, 0, 1];
  const R = eulerToMat4(rx, ry, rz);
  // translation (column-major: translation in last column)
  const T = [1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, tx, ty, tz, 1];

  // M = T · R · S
  return mul4(mul4(T, R), S);
}

// ---------------------------------------------------------------------------
// Root motion
// ---------------------------------------------------------------------------

/**
 * Whether the root JOBJ (index 0) carries any translation track. HSD applies the
 * root translation to the rendered mesh; gameplay code is expected to own world
 * position separately. If both the model and the player rig consume this, the
 * borg double-translates (e.g. pl0615 boost_forward slides Z 0->300).
 *
 * Pass the root joint's decoded tracks. Returns true if TRAX/TRAY/TRAZ exist with
 * non-constant motion.
 */
export function rootHasTranslationMotion(rootTracks: readonly FObjPlayer[]): boolean {
  for (const t of rootTracks) {
    if (t.trackType === JointTrackType.TraX || t.trackType === JointTrackType.TraY || t.trackType === JointTrackType.TraZ) {
      if (t.keys.length > 1) {
        const first = t.getValue(0);
        for (let f = 1; f <= t.frameCount; f++) {
          if (Math.abs(t.getValue(f) - first) > 1e-4) return true;
        }
      }
    }
  }
  return false;
}

/**
 * Strip translation tracks from a root joint's track set so the model stays in
 * place and the player rig / gameplay owns forward movement. The original game
 * separates "animation pose" from "world position"; for locomotion clips the web
 * app should drive movement from the rig, not the baked root translation.
 */
export function stripRootTranslation(rootTracks: readonly FObjPlayer[]): FObjPlayer[] {
  return rootTracks.filter(
    (t) => t.trackType !== JointTrackType.TraX && t.trackType !== JointTrackType.TraY && t.trackType !== JointTrackType.TraZ,
  );
}
