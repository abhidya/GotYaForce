#!/usr/bin/env node
// Export the two non-roster pl06xx morph models from their authoritative PZZ member-5
// `b_mdl.arc` archives, using the same HSDRaw ModelExporter as stage/UI exports.
import { mkdir, writeFile } from "node:fs/promises";
import path from "node:path";
import { spawnSync } from "node:child_process";

const repoRoot = path.resolve(".");
const region = process.argv[2] ?? "GG4E";
const forms = [
  { id: "pl0605", source: "pl0604b_mdl.arc" },
  { id: "pl0614", source: "pl0613b_mdl.arc" },
];
const workDir = path.join(repoRoot, "user-data", region, "internal-morph-model-exporter");
const csproj = path.join(workDir, "internal-morph-model-exporter.csproj");
const program = path.join(workDir, "Program.cs");

await mkdir(workDir, { recursive: true });
await writeFile(program, source());
await writeFile(csproj, project());

for (const form of forms) {
  const arc = path.join(repoRoot, "user-data", region, "afs_data", "root", form.source);
  const out = path.join(repoRoot, "apps", "game", "public", "models", form.id);
  await mkdir(out, { recursive: true });
  const result = spawnSync("dotnet", ["run", "--project", csproj, "-c", "Release", "--", arc, out], {
    cwd: repoRoot, shell: true, stdio: "inherit",
  });
  if ((result.status ?? 1) !== 0) process.exit(result.status ?? 1);
}

function project() {
  return String.raw`<Project Sdk="Microsoft.NET.Sdk"><PropertyGroup><OutputType>Exe</OutputType><TargetFramework>net6.0-windows</TargetFramework><Nullable>disable</Nullable><UseWindowsForms>true</UseWindowsForms></PropertyGroup><ItemGroup><ProjectReference Include="..\..\..\tools\HSDLib\HSDRawViewer\HSDRawViewer.csproj" /></ItemGroup></Project>`;
}

function source() {
  return String.raw`using System; using System.IO; using System.Linq; using HSDRaw; using HSDRaw.Common; using HSDRawViewer.Converters; using HSDRawViewer.Tools.Animation;
class Exporter { static void Main(string[] a) { var data=File.ReadAllBytes(a[0]); var hsd=new HSDRawFile(data.Skip(0x100).ToArray()); Directory.CreateDirectory(a[1]); var settings=new ModelExportSettings { ExportMesh=true, ExportTextures=true, ExportBindPose=true, Optimize=true }; int i=0;
foreach(var root in hsd.Roots) { var sobj=new HSD_SOBJ(){_s=root.Data._s}; if(sobj.JOBJDescs?.Array==null) continue; foreach(var jd in sobj.JOBJDescs.Array) { if(jd?.RootJoint==null){i++;continue;} ModelExporter.ExportFile(Path.Combine(a[1],$"model_{i:D2}.dae"),jd.RootJoint,settings,new JointMap()); i++; } } if(i==0) Environment.Exit(2); } }`;
}
