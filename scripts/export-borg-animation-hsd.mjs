#!/usr/bin/env node
import fs from "node:fs";
import { mkdir, writeFile } from "node:fs/promises";
import path from "node:path";
import { spawnSync } from "node:child_process";

const REGIONS = new Set(["GG4E", "GG4J", "GG4P"]);

const region = process.argv[2] ?? "GG4E";
const borgId = (process.argv[3] ?? "pl0615").toLowerCase();
const specs = process.argv.slice(4);

if (!REGIONS.has(region)) fail(`unsupported region "${region}"`);
if (!/^pl[0-9a-f]{4}[a-z]?$/i.test(borgId)) fail(`invalid borg id "${borgId}"`);

const repoRoot = path.resolve(".");
const rootDir = path.join(repoRoot, "user-data", region, "afs_data", "root");
const motPath = path.join(rootDir, `${borgId}mot.bin`);
const modelPath = path.join(rootDir, `${borgId}_mdl.arc`);
const outDir = path.join(repoRoot, "apps", "game", "public", "models", borgId);
const workDir = path.join(repoRoot, "user-data", region, "borg-animation-exporter");
const csproj = path.join(workDir, "borg-animation-exporter.csproj");
const program = path.join(workDir, "Program.cs");

mustExist(motPath);
mustExist(modelPath);
mustExist(path.join(repoRoot, "tools", "HSDLib", "HSDRawViewer", "HSDRawViewer.csproj"));

const clipSpecs = specs.length
  ? specs.map(parseSpec)
  : [
      { offset: 0x240, name: "anim_b00_idle.json" },
      { offset: 0x1a40, name: "anim_b00_clip1.json" },
    ];

await mkdir(workDir, { recursive: true });
await mkdir(outDir, { recursive: true });
await writeFile(program, getSource());
await writeFile(csproj, getProject());

for (const clip of clipSpecs) {
  const outPath = path.join(outDir, clip.name);
  const result = spawnSync(
    "dotnet",
    ["run", "--project", csproj, "-c", "Release", "--", motPath, modelPath, "0x100", clip.offset.toString(16), "0", outPath],
    { cwd: repoRoot, shell: true, stdio: "inherit" },
  );
  if ((result.status ?? 1) !== 0) process.exit(result.status ?? 1);
  console.log(`${borgId} ${hex(clip.offset)} -> ${path.relative(repoRoot, outPath)}`);
}

function parseSpec(value) {
  const [rawOffset, rawName] = value.split(":");
  if (!rawOffset) fail(`bad clip spec "${value}", expected offset[:name]`);
  const offset = Number.parseInt(rawOffset.replace(/^0x/i, ""), 16);
  if (!Number.isFinite(offset) || offset <= 0) fail(`bad clip offset "${rawOffset}"`);
  const name = rawName?.trim() || `anim_b00_${rawOffset.replace(/^0x/i, "").toLowerCase()}.json`;
  if (!/^[a-z0-9_.-]+\.json$/i.test(name)) fail(`bad output name "${name}"`);
  return { offset, name };
}

function mustExist(file) {
  if (!fs.existsSync(file)) fail(`missing ${path.relative(repoRoot, file)}`);
}

function hex(value) {
  return `0x${value.toString(16)}`;
}

function fail(message) {
  console.error(`export-borg-animation-hsd: ${message}`);
  process.exit(1);
}

function getProject() {
  return String.raw`<Project Sdk="Microsoft.NET.Sdk">
  <PropertyGroup>
    <OutputType>Exe</OutputType>
    <TargetFramework>net6.0-windows</TargetFramework>
    <UseWindowsForms>true</UseWindowsForms>
    <Nullable>disable</Nullable>
  </PropertyGroup>
  <ItemGroup>
    <ProjectReference Include="..\..\..\tools\HSDLib\HSDRawViewer\HSDRawViewer.csproj" />
    <Reference Include="IONET"><HintPath>..\..\..\tools\HSDLib\HSDRawViewer\lib\IONET.dll</HintPath></Reference>
  </ItemGroup>
</Project>
`;
}

function getSource() {
  return String.raw`
using System;
using System.IO;
using System.Linq;
using System.Text;
using System.Collections.Generic;
using HSDRaw;
using HSDRaw.Common;
using HSDRaw.Common.Animation;
using HSDRaw.Tools;
using HSDRawViewer.Converters;
using HSDRawViewer.Tools.Animation;

class BorgAnimationExporter {
    static uint U32(byte[] d, int o) => (uint)((d[o] << 24) | (d[o + 1] << 16) | (d[o + 2] << 8) | d[o + 3]);

    static SortedSet<uint> ReadMotBlobOffsets(byte[] data) {
        if (data.Length < 24) throw new Exception("MOT file is too small for the master table");
        var offsets = new SortedSet<uint>();
        for (int bankIndex = 0; bankIndex < 6; bankIndex++) {
            uint tableOff = U32(data, bankIndex * 4);
            if (tableOff == 0 || tableOff == 0xffffffff) continue;
            if (tableOff > (uint)(data.Length - 4)) throw new Exception($"bank {bankIndex} table offset 0x{tableOff:X} outside mot file");

            bool terminated = false;
            for (int cursor = (int)tableOff, slotIndex = 0; cursor + 3 < data.Length; cursor += 4, slotIndex++) {
                uint v = U32(data, cursor);
                if (v == 0xffffffff) {
                    terminated = true;
                    break;
                }
                if (v != 0) {
                    if (v >= data.Length) throw new Exception($"bank {bankIndex} slot {slotIndex} points outside mot file: 0x{v:X}");
                    offsets.Add(v);
                }
                if (slotIndex > 1024) throw new Exception($"bank {bankIndex} table scan stopped after 1024 slots without terminator");
            }
            if (!terminated) throw new Exception($"bank {bankIndex} table has no terminator");
        }
        if (offsets.Count == 0) throw new Exception("no MOT clip offsets found");
        return offsets;
    }

    static byte[] ExtractBlob(byte[] data, uint blobOff) {
        uint next = uint.MaxValue;
        foreach (uint v in ReadMotBlobOffsets(data)) {
            if (v > blobOff && v < next) next = v;
        }
        if (next == uint.MaxValue) next = (uint)data.Length;
        if (next <= blobOff) throw new Exception($"bad blob length for offset 0x{blobOff:X}");
        int len = checked((int)(next - blobOff));
        byte[] b = new byte[len];
        Array.Copy(data, (int)blobOff, b, 0, len);
        return b;
    }

    static List<HSD_JOBJ> Flatten(HSD_JOBJ root) {
        var list = new List<HSD_JOBJ>();
        void Rec(HSD_JOBJ j) {
            list.Add(j);
            foreach (var c in j.Children) Rec(c);
        }
        Rec(root);
        return list;
    }

    static float[] EulerToQuat(float X, float Y, float Z) {
        double sx = Math.Sin(X), cx = Math.Cos(X), sy = Math.Sin(Y), cy = Math.Cos(Y), sz = Math.Sin(Z), cz = Math.Cos(Z);
        double m00 = cy * cz, m01 = cz * sx * sy - cx * sz, m02 = cz * cx * sy + sx * sz;
        double m10 = cy * sz, m11 = sz * sx * sy + cx * cz, m12 = sz * cx * sy - sx * cz;
        double m20 = -sy,     m21 = sx * cy,              m22 = cx * cy;
        double tr = m00 + m11 + m22;
        double qw, qx, qy, qz;
        if (tr > 0) {
            double s = Math.Sqrt(tr + 1.0) * 2;
            qw = 0.25 * s; qx = (m21 - m12) / s; qy = (m02 - m20) / s; qz = (m10 - m01) / s;
        } else if (m00 > m11 && m00 > m22) {
            double s = Math.Sqrt(1.0 + m00 - m11 - m22) * 2;
            qw = (m21 - m12) / s; qx = 0.25 * s; qy = (m01 + m10) / s; qz = (m02 + m20) / s;
        } else if (m11 > m22) {
            double s = Math.Sqrt(1.0 + m11 - m00 - m22) * 2;
            qw = (m02 - m20) / s; qx = (m01 + m10) / s; qy = 0.25 * s; qz = (m12 + m21) / s;
        } else {
            double s = Math.Sqrt(1.0 + m22 - m00 - m11) * 2;
            qw = (m10 - m01) / s; qx = (m02 + m20) / s; qy = (m12 + m21) / s; qz = 0.25 * s;
        }
        return new float[] { (float)qx, (float)qy, (float)qz, (float)qw };
    }

    static void Main(string[] args) {
        if (args.Length != 6) throw new Exception("usage: exporter <mot.bin> <model.arc> <modelSkipHex> <blobOffHex> <modelIndex> <out.json>");
        string motPath = args[0];
        string modelArc = args[1];
        int modelSkip = Convert.ToInt32(args[2], 16);
        uint blobOff = Convert.ToUInt32(args[3], 16);
        int modelIndex = int.Parse(args[4]);
        string outJson = args[5];

        byte[] modelBytes = File.ReadAllBytes(modelArc);
        var mf = new HSDRawFile(modelSkip > 0 ? modelBytes.Skip(modelSkip).ToArray() : modelBytes);
        HSD_JOBJ modelRoot = null;
        int mi = 0;
        foreach (var r in mf.Roots) {
            var sobj = new HSD_SOBJ() { _s = r.Data._s };
            if (sobj.JOBJDescs?.Array == null) continue;
            foreach (var jd in sobj.JOBJDescs.Array) {
                if (jd?.RootJoint == null) continue;
                if (mi == modelIndex) modelRoot = jd.RootJoint;
                mi++;
            }
        }
        if (modelRoot == null) throw new Exception($"model index {modelIndex} not found");
        var modelJoints = Flatten(modelRoot);

        byte[] mot = File.ReadAllBytes(motPath);
        if (blobOff >= mot.Length) throw new Exception($"blob offset 0x{blobOff:X} outside mot file");
        var af = new HSDRawFile(ExtractBlob(mot, blobOff));
        if (modelIndex >= af.Roots.Count) throw new Exception($"anim root {modelIndex} missing");
        var aj = af.Roots[modelIndex].Data as HSD_AnimJoint;
        if (aj == null) throw new Exception("selected root is not HSD_AnimJoint");

        var jm = new JointAnimManagerLite(aj);
        int jointCount = Math.Min(modelJoints.Count, jm.Nodes.Count);
        int frames = Math.Max(1, (int)Math.Round(jm.FrameCount));

        var sb = new StringBuilder();
        sb.Append("{\n");
        sb.Append($"\"name\":\"{Path.GetFileNameWithoutExtension(motPath)}_blob{blobOff:X}_m{modelIndex}\",\n");
        sb.Append($"\"frameCount\":{frames},\"fps\":60,\"rotFormat\":\"quat_xyzw\",\n");
        sb.Append("\"bones\":[\n");
        for (int i = 0; i < jointCount; i++) {
            var mj = modelJoints[i];
            var node = jm.Nodes[i];
            float rTX = mj.TX, rTY = mj.TY, rTZ = mj.TZ;
            float rRX = mj.RX, rRY = mj.RY, rRZ = mj.RZ;
            float rSX = mj.SX == 0 ? 1 : mj.SX, rSY = mj.SY == 0 ? 1 : mj.SY, rSZ = mj.SZ == 0 ? 1 : mj.SZ;

            FOBJ_Player Track(JointTrackType t) => node.Tracks.FirstOrDefault(p => p.JointTrackType == t);
            var pTX = Track(JointTrackType.HSD_A_J_TRAX); var pTY = Track(JointTrackType.HSD_A_J_TRAY); var pTZ = Track(JointTrackType.HSD_A_J_TRAZ);
            var pRX = Track(JointTrackType.HSD_A_J_ROTX); var pRY = Track(JointTrackType.HSD_A_J_ROTY); var pRZ = Track(JointTrackType.HSD_A_J_ROTZ);
            var pSX = Track(JointTrackType.HSD_A_J_SCAX); var pSY = Track(JointTrackType.HSD_A_J_SCAY); var pSZ = Track(JointTrackType.HSD_A_J_SCAZ);

            var pos = new StringBuilder(); var rot = new StringBuilder(); var scl = new StringBuilder();
            for (int f = 0; f < frames; f++) {
                float tx = pTX != null ? pTX.GetValue(f) : rTX;
                float ty = pTY != null ? pTY.GetValue(f) : rTY;
                float tz = pTZ != null ? pTZ.GetValue(f) : rTZ;
                float rx = pRX != null ? pRX.GetValue(f) : rRX;
                float ry = pRY != null ? pRY.GetValue(f) : rRY;
                float rz = pRZ != null ? pRZ.GetValue(f) : rRZ;
                float sx = pSX != null ? pSX.GetValue(f) : rSX;
                float sy = pSY != null ? pSY.GetValue(f) : rSY;
                float sz = pSZ != null ? pSZ.GetValue(f) : rSZ;
                var q = EulerToQuat(rx, ry, rz);
                if (f > 0) { pos.Append(','); rot.Append(','); scl.Append(','); }
                pos.Append($"{tx:G6},{ty:G6},{tz:G6}");
                rot.Append($"{q[0]:G6},{q[1]:G6},{q[2]:G6},{q[3]:G6}");
                scl.Append($"{sx:G6},{sy:G6},{sz:G6}");
            }
            sb.Append("{");
            sb.Append($"\"i\":{i},");
            sb.Append($"\"pos\":[{pos}],");
            sb.Append($"\"rot\":[{rot}],");
            sb.Append($"\"scl\":[{scl}]");
            sb.Append("}");
            if (i < jointCount - 1) sb.Append(",");
            sb.Append("\n");
        }
        sb.Append("]\n}\n");
        Directory.CreateDirectory(Path.GetDirectoryName(outJson));
        File.WriteAllText(outJson, sb.ToString());
        Console.WriteLine($"wrote {outJson} frames={frames} bones={jointCount}");
    }
}

class AnimNodeLite { public List<FOBJ_Player> Tracks = new List<FOBJ_Player>(); }

class JointAnimManagerLite {
    public List<AnimNodeLite> Nodes = new List<AnimNodeLite>();
    public float FrameCount = 0;
    public JointAnimManagerLite(HSD_AnimJoint joint) {
        foreach (var j in joint.TreeList) {
            var n = new AnimNodeLite();
            if (j.AOBJ != null && j.AOBJ.FObjDesc != null) {
                FrameCount = Math.Max(FrameCount, j.AOBJ.EndFrame + 1);
                foreach (var fd in j.AOBJ.FObjDesc.List) {
                    var p = new FOBJ_Player(fd);
                    if (p.Keys != null && p.Keys.Count > 0) FrameCount = Math.Max(FrameCount, p.Keys.Max(e => e.Frame + 1));
                    n.Tracks.Add(p);
                }
            }
            Nodes.Add(n);
        }
    }
}
`;
}
