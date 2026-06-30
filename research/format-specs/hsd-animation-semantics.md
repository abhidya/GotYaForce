# HSD (HAL Sysdolphin) Animation-Apply Semantics

How HSDRaw / HSDRawViewer evaluate FOBJ animation tracks and compose a JOBJ
(joint) local transform, transcribed from the C# source so the web recreation
can match the original GameCube playback exactly rather than approximating.

Confidence legend: **[PROVEN]** = read directly from HSDRaw/HSDRawViewer source;
**[DERIVED]** = logically follows from the source but involves a math identity I
worked out (e.g. matrix transpose); **[UNVERIFIED]** = inferred, not confirmed in
source.

Source tree: `D:\GotYaForce\tools\HSDLib\`
(`HSDRaw` = format/decoder library, `HSDRawViewer` = renderer that composes
transforms).

---

## 1. Track container hierarchy [PROVEN]

```
HSD_AnimJoint (tree, mirrors the JOBJ tree 1:1 in pre-order)
  └─ AOBJ (HSD_AOBJ)                     // one animation object per joint
       ├─ Flags (ANIM_LOOP, NO_ANIM, …)
       ├─ EndFrame : float               // clip length, in frames
       └─ FObjDesc (HSD_FOBJDesc, linked list)
            └─ each node is one FOBJ track
                 ├─ TrackType : JointTrackType  (which channel: ROTX, TRAY, SCAZ…)
                 ├─ ValueFormat / ValueScale    (how values are packed)
                 ├─ TanFormat   / TanScale      (how tangents are packed)
                 └─ Buffer : byte[]             (the packed keyframe stream)
```

- `HSD_AnimJoint.cs` (offsets: Child 0x00, Next 0x04, AOBJ 0x08, Flags 0x10).
- `HSD_AOBJ.cs` (Flags 0x00, EndFrame 0x04, FObjDesc 0x08, ObjectReference 0x0C).
- `HSD_FOBJ.cs` / `HSD_FOBJDesc.cs` (TrackType 0x00, ValueFlag 0x01, TangentFlag
  0x02, Buffer ref 0x04). `HSD_FOBJDesc` is the linked-list variant with an extra
  `DataLength`/`Next` field; the key stream and flags are identical.

The AnimJoint tree is walked in the **same pre-order** as the model's JOBJ tree, so
track node *i* drives model joint *i*. The baker relies on this: it flattens both
trees and zips them by index (`export-borg-animation-hsd.mjs`,
`JointAnimManagerLite` + `Flatten`).

### JointTrackType enum [PROVEN] (`HSD_FOBJ.cs:90`)
```
HSD_A_J_NONE=0
HSD_A_J_ROTX=1  ROTY=2  ROTZ=3      // Euler rotation, RADIANS
HSD_A_J_PATH=4
HSD_A_J_TRAX=5  TRAY=6  TRAZ=7      // translation
HSD_A_J_SCAX=8  SCAY=9  SCAZ=10     // scale
HSD_A_J_NODE=11  BRANCH=12
HSD_A_J_SETBYTE0..9 = 13..22
HSD_A_J_SETFLOAT0..9 = 23..32
HSD_A_J_PTCL=40                     // particle trigger, NOT a transform
```
Only ROT/TRA/SCA (types 1–3, 5–10) are sampled as transform channels (see
`HSD_JOBJ.GetDefaultValue`, `HSD_JOBJ.cs:109`, and the `switch` in
`LiveJObj.ApplyAnimation`, `LiveJObj.cs:604`). PATH/NODE/BRANCH/SETBYTE/SETFLOAT
exist in the format but are not transform tracks. PTCL is a particle-spawn opcode
(handled specially in `FOBJ_Player` ctor, `FOBJ_Player.cs:99`) and produces **no**
keys.

There is **no quaternion joint track type** in HSD joint animation — rotation is
always three independent Euler-radian scalar tracks (ROTX/ROTY/ROTZ). The
`USE_QUATERNION` JOBJ flag affects how the *static* rotation is stored, not the
animation track format. (So the prompt's "quaternion variants" do not exist for
joint tracks; quaternion variants exist only conceptually for the baked output.)

---

## 2. Keyframe stream decode [PROVEN] (`FOBJ_Decoder.cs`)

The `Buffer` is a packed stream. Reading is **little-endian** (`ParseFloat` sets
`d.BigEndian = false`, line 137) even though GameCube discs are big-endian — the
FOBJ buffer is LE internally.

Integers use a LEB128-style varint, `BinaryReaderExt.ReadPacked()`
(`BinaryReaderExt.cs:248`): 7 bits/byte, low byte first, continue while high bit
set.

Decode loop (`FOBJFrameDecoder.GetKeys`, line 45):
```
clock = 0
while not end of buffer:
    header = ReadPacked()
    interpolation = header & 0x0F          // GXInterpolationType
    numKeys       = (header >> 4) + 1
    if interpolation == 0: break           // HSD_A_OP_NONE terminates
    repeat numKeys times:
        value=0, tan=0, time=0
        switch interpolation:
          CON  (0x1): value=ParseFloat(ValueFmt,ValueScale); time=ReadPacked()
          LIN  (0x2): value=ParseFloat(ValueFmt,ValueScale); time=ReadPacked()
          SPL0 (0x3): value=ParseFloat(ValueFmt,ValueScale); time=ReadPacked()
          SPL  (0x4): value=ParseFloat(ValueFmt,ValueScale);
                      tan  =ParseFloat(TanFmt,TanScale);  time=ReadPacked()
          SLP  (0x5): tan  =ParseFloat(TanFmt,TanScale)   // NO value, NO time
          KEY  (0x6): value=ParseFloat(ValueFmt,ValueScale) // NO time
        emit key{ frame=clock, value, tan, interp }
        clock += time     // SLP/KEY contribute time=0 (no time was read)
```

Note the consequence: an `SLP` (slope) record carries **only a tangent** and does
not advance the clock — it patches the incoming tangent of the key that follows.
A `KEY` record carries only a value and also does not advance the clock.

### Value/tangent packing [PROVEN] (`ParseFloat`, line 135; flag math `HSD_FOBJ.cs:212`)
`ValueFlag` byte: bits 0–4 = scale exponent (`ValueScale = 1 << (flag & 0x1F)`),
bits 5–7 = format. `TangentFlag` identical for tangents.

```
GXAnimDataFormat:
  HSD_A_FRAC_FLOAT = 0x00 → read 4-byte float, value as-is
  HSD_A_FRAC_S16   = 0x20 → read int16,  value = raw / scale
  HSD_A_FRAC_U16   = 0x40 → read uint16, value = raw / scale
  HSD_A_FRAC_S8    = 0x60 → read int8,   value = raw / scale
  HSD_A_FRAC_U8    = 0x80 → read uint8,  value = raw / scale
```
`scale` is the power-of-two divisor decoded from the flag's low 5 bits.

---

## 3. Sampling a value at frame t [PROVEN] (`FOBJ_Player.cs`)

This is the part the web app must match exactly. Two stages: build an
`FOBJAnimState` (the bracketing segment) via `GetState`, then evaluate via
`GetValue`.

### 3a. GetState(frame) — find the active segment (line 147)

Registers `p0,p1` (values), `d0,d1` (tangents), `t0,t1` (frames), plus `op`
(current interp) and `op_intrp` (interp that governs the *segment*, i.e. the
previous key's). The loop walks keys, shifting (p1→p0, d1→d0, t1→t0) as it
crosses each key, stopping when `t1 > frame` (unless the key is `SLP`, which is a
mid-segment tangent patch and does not terminate the search).

Per-interp register updates (line 182):
- **CON**: p0=p1; p1=key.value; (if prev op ≠ SLP: d0=d1; d1=0); t0=t1; t1=key.frame
- **LIN**: same as CON
- **SPL0**: p0=p1; d0=d1; p1=key.value; d1=0; t0=t1; t1=key.frame
- **SPL**: p0=p1; p1=key.value; d0=d1; d1=key.tan; t0=t1; t1=key.frame
- **SLP**: d0=d1; d1=key.tan   (only tangents move; p/t untouched)
- **KEY**: p0=key.value; p1=key.value

Clamp: if `frame >= last key frame`, return a degenerate state holding the last
key (p0=p1=value, d0=d1=tan), so sampling past the end holds the final pose.

### 3b. GetValue(frame) — evaluate the segment (line 250)
```
state = GetState(frame)
if frame <= state.t0: return state.p0
if frame >= state.t1: return state.p1
if t0==t1 or op_intrp ∈ {CON, KEY}: return state.p0      // step / hold

time  = frame - t0
fterm = t1 - t0
if op_intrp == LIN:  return Lerp(fterm, time, p0, p1)
if op_intrp ∈ {SPL, SPL0, SLP}:
                     return SplineGetHermite(1/fterm, time, p0, p1, d0, d1)
return p0
```

> **Important quirk [PROVEN]:** `GetValue` selects the interpolation by
> `op_intrp` — the interpolation type recorded on the segment's *governing* key —
> NOT by the current key. CON and KEY produce a **step/hold** (return p0). This is
> why the decoder's per-key `interp` must be preserved exactly; you cannot collapse
> everything to LINEAR.

### 3c. The exact interpolation math [PROVEN] (`AnimationInterpolationHelper`, line 444)

**Linear** (line 446):
```
Lerp(fterm, time, p0, p1):
    d0 = (p1 - p0) / fterm
    return d0 * time + p0
```

**Hermite** (line 452) — this is the load-bearing one. Note `fterm` here is
`1/(t1-t0)` (the caller passes the reciprocal), `time = frame - t0`:
```
SplineGetHermite(fterm, time, p0, p1, d0, d1):   // fterm == 1/(t1-t0)
    f1 = time * time
    f2 = fterm * fterm * f1 * time            // (time^3)/(dt^2)
    f3 = 3 * f1 * fterm * fterm               // 3*time^2/dt^2
    f4 = f2 - f1 * fterm                       // time^3/dt^2 - time^2/dt
    f2 = 2 * f2 * fterm                         // 2*time^3/dt^3
    return  d1 * f4
          + d0 * (time + (f4 - f1 * fterm))
          + p0 * (1 + (f2 - f3))
          + p1 * (-f2 + f3)
```
This is the standard cubic Hermite basis expressed with `s = time`,
`dt = t1 - t0`:
- p1 coefficient `(-f2+f3) = 3(s/dt)^2 - 2(s/dt)^3 = h01(u)` with `u = s/dt`
- p0 coefficient `1+(f2-f3) = 1 - 3u^2 + 2u^3 = h00(u)`
- d0 coefficient `s + (f4 - s^2/dt) = s - 2s^2/dt + s^3/dt^2 = dt·(u - 2u^2 + u^3) = dt·h10(u)`
- d1 coefficient `f4 = s^3/dt^2 - s^2/dt = dt·(u^3 - u^2) = dt·h11(u)`

i.e. `H(u) = h00·p0 + dt·h10·d0 + h01·p1 + dt·h11·d1`, the canonical unit Hermite
with tangents scaled by the segment length `dt`. **Tangents d0/d1 are in
value-per-frame units.** Replicate the float expression verbatim to be bit-faithful.

---

## 4. Composing the JOBJ local transform [PROVEN] (`LiveJObj.cs:296`)

Per-channel animated SRT (defaults from the JOBJ desc, overridden by any present
track) is built in `ApplyAnimation` (line 604): for each `FOBJ_Player`, write its
sampled value into the matching Translation/Rotation(Euler)/Scale component.
Channels with no track keep the JOBJ's static default (`SetDefaultSRT`, line 259:
T=(TX,TY,TZ), R=(RX,RY,RZ), S=(SX,SY,SZ)).

The local matrix (line 299):
```csharp
LocalTransform = Matrix4.CreateScale(Scale)
               * Math3D.CreateMatrix4FromEuler(Rotation.Xyz)
               * Matrix4.CreateTranslation(Translation);
```

**OpenTK convention is row-vector / row-major (`v' = v * M`).** So the on-screen
application order is Scale, then Rotation, then Translation — i.e. mathematically
**M_local = T · R · S** (column-vector convention). A point is scaled, then
rotated, then translated. [DERIVED from OpenTK row-vector semantics]

World transform (line 329):
```csharp
WorldTransform = LocalTransform * Parent.WorldTransform;   // row-vector: child-then-parent
```
In column-vector terms `M_world = M_parent · M_local` — standard parent-after-child.
Root joint (`Parent == null`): `WorldTransform = LocalTransform`.

**Scale-compensate** (line 307): if the JOBJ has `MTX_SCALE_COMPENSATE`, the
translation is pre-multiplied by the parent's extracted scale and an inverse-scale
matrix is inserted between local and parent. Borg models in Gotcha Force have not
been observed to set this flag; **[UNVERIFIED]** for this game — treat as a risk if
a model looks wrong only at scaled joints.

Billboarding (types in flag bits 9–11), IK (EFFECTOR/JOINT flags), and physics
(`PhysicsEnabled`) further mutate WorldTransform but are camera/solver-dependent and
out of scope for baked clip playback.

### 4a. Euler rotation matrix [PROVEN] (`Math3D.CreateMatrix4FromEuler`, line 108)

With `sx=sin(X)…cz=cos(Z)`, OpenTK row-major storage:
```
M11=cy·cz            M12=cy·sz            M13=-sy
M21=cz·sx·sy−cx·sz   M22=sz·sx·sy+cx·cz   M23=sx·cy
M31=cz·cx·sy+sx·sz   M32=sz·cx·sy−sx·cz   M33=cx·cy
```
As a column-vector rotation matrix (transpose of the above, since OpenTK is
row-vector) this equals **R = Rx · Ry · Rz** — i.e. apply Rz first, then Ry, then
Rx to a column vector (intrinsic X-Y-Z / extrinsic Z-Y-X). [DERIVED — verified by
expanding Rx·Ry·Rz and matching the transpose, e.g. column-vector
m[0][2]=cz·cx·sy+sx·sz = the source's M31.]

**Euler order to replicate: build Rz then Ry then Rx and multiply Rx·Ry·Rz (column
vector), OR feed THREE.Euler with order `"ZYX"`.** Angles are radians.

---

## 5. The baker's Euler→quaternion is consistent [PROVEN/DERIVED]

`scripts/export-borg-animation-hsd.mjs` `EulerToQuat` builds the column-vector
matrix:
```
m00=cy·cz  m01=cz·sx·sy−cx·sz  m02=cz·cx·sy+sx·sz
m10=cy·sz  m11=sz·sx·sy+cx·cz  m12=sz·cx·sy−sx·cz
m20=−sy    m21=sx·cy           m22=cx·cy
```
This is **exactly the transpose** of `Math3D.CreateMatrix4FromEuler` (baker
`m00`=HSD `M11`, baker `m01`=HSD `M21`, baker `m02`=HSD `M31`, …). Since HSDRawViewer
stores rotation as a row-vector matrix and the baker reads it as a column-vector
matrix, the transpose is the **correct** conversion — the resulting quaternion
represents the same physical rotation HSDRawViewer renders. The matrix-to-quaternion
extraction is the standard Shepperd/Mike-Day method. **The baked quaternions are
faithful.** [DERIVED]

---

## 6. Is the existing baked path faithful? [PROVEN — yes, with one caveat]

The C# baker (`export-borg-animation-hsd.mjs`, embedded `Program.cs`) samples each
channel with `FOBJ_Player.GetValue(f)` for every integer frame `f` in
`[0, frames)`. `FOBJ_Player.GetValue` **is** HSDRaw's real CON/LIN/HERMITE
evaluator (Section 3). So:

- **Interpolation is correct, not naive.** Hermite/spline easing is evaluated by
  the real `SplineGetHermite` at each integer frame. The baker is NOT linear-
  sampling a hermite track. The `idle`/`move`/etc. JSONs already carry the right
  eased values at every frame.
- **Caveat — resolution, not correctness:** the baker emits one key per integer
  frame and the web app (`main.ts buildClip`, line 458) plays them through
  `THREE.QuaternionKeyframeTrack` (slerp) / `VectorKeyframeTrack` (lerp) at
  `time=frame/60`. Between two baked integer frames, THREE does linear/slerp, not
  the original hermite. At 60 fps clip / 60 fps render this is a no-op (samples
  land on keys); only slow-motion or frame-blending would expose the sub-frame
  approximation. **Acceptable; documented.**
- `FrameCount` = `max(AOBJ.EndFrame+1, max key frame +1)`
  (`JointAnimManagerLite`), so the clip includes the terminal pose frame.

**Conclusion:** the TS module in `packages/formats/src/hsd-anim.ts` is the
**reference / validation implementation** of HSD sampling + SRT composition. It is
not needed to fix the baked clips (they are correct); it exists so the web app can
(a) re-derive a clip from raw FOBJ bytes without the C# toolchain, and (b) validate
that any future baked JSON matches HSD semantics exactly.

---

## 7. Root motion / top JOBJ [PROVEN data, design note]

The root joint (`JOBJ_0`, AnimJoint index 0) is animated like any other: if its
AOBJ has TRAX/TRAY/TRAZ tracks, the baker writes them into `bones[0].pos` and
`main.ts` applies them to `JOBJ_0.position` on the model.

Measured (pl0615 / G Red):
- `idle`, `move`: root `JOBJ_0` translation span = (0,0,0) — **no root motion**.
- `boost_forward`: root `JOBJ_0` Z span = **0 → 300** — the clip translates the
  whole model 300 units forward in model-local space.

HSD itself has no separate "root motion" concept — the root JOBJ translation *is*
applied to the model, moving the rendered mesh. The original game's gameplay code
reads/zeroes the root delta to drive the entity, but that is engine logic outside
the HSD data.

**Recommendation for the web app:** the player rig (entity position) and the model
should not both consume the root translation, or boosting will double-translate /
slide. Two clean options:
1. **Strip root translation at bake time** for locomotion clips and let the
   player-rig/gameplay code own forward movement (simplest, matches how the game
   logically separates "animation pose" from "world position"), OR
2. Apply root translation to the model but subtract the same per-frame delta from
   the rig, so net world motion is driven once.

Currently the web app does neither (it applies root pos straight to the model), so
`boost_forward` will visibly slide the mesh 300u relative to the rig. This is the
**single biggest remaining fidelity risk** — see the TS module's
`stripRootTranslation` helper and the `RootMotionPolicy` note.
