#!/usr/bin/env node
import { mkdir, writeFile } from "node:fs/promises";
import path from "node:path";
import { spawnSync } from "node:child_process";

const region = process.argv[2] ?? "GG4E";
const stageCode = (process.argv[3] ?? "00").toLowerCase();
const arcPath = path.resolve(`user-data/${region}/afs_data/root/st${stageCode}_mdl.arc`);
const outDir = path.resolve(`apps/game/public/stages/st${stageCode}/model`);
const workDir = path.resolve(`user-data/${region}/stage-exporter`);
const csproj = path.join(workDir, "stage-exporter.csproj");
const program = path.join(workDir, "Program.cs");

const source = String.raw`
using System;
using System.IO;
using System.Linq;
using HSDRaw;
using HSDRaw.Common;
using HSDRawViewer.Converters;
using HSDRawViewer.Tools.Animation;

class StageExporter {
  static void Main(string[] args) {
    if (args.Length < 2) throw new Exception("usage: stage-exporter <arc> <outDir>");
    var arc = args[0];
    var outDir = args[1];
    Directory.CreateDirectory(outDir);
    var data = File.ReadAllBytes(arc);
    var hsd = new HSDRawFile(data);
    var settings = new ModelExportSettings { ExportMesh = true, ExportTextures = true, ExportBindPose = true, Optimize = true };
    int model = 0, ok = 0, fail = 0;
    foreach (var root in hsd.Roots) {
      var sobj = new HSD_SOBJ(){ _s = root.Data._s };
      if (sobj.JOBJDescs?.Array == null) continue;
      foreach (var jd in sobj.JOBJDescs.Array) {
        if (jd?.RootJoint == null) { model++; continue; }
        var outPath = Path.Combine(outDir, $"model_{model:D2}.dae");
        try {
          ModelExporter.ExportFile(outPath, jd.RootJoint, settings, new JointMap());
          Console.WriteLine($"OK model_{model:D2}.dae");
          ok++;
        } catch (Exception e) {
          Console.WriteLine($"ERR model_{model:D2}: {e.GetType().Name} {e.Message}");
          fail++;
        }
        model++;
      }
    }
    Console.WriteLine($"stage-export ok={ok} fail={fail}");
    if (ok == 0) Environment.Exit(2);
  }
}
`;

const project = String.raw`<Project Sdk="Microsoft.NET.Sdk">
  <PropertyGroup>
    <OutputType>Exe</OutputType>
    <TargetFramework>net6.0-windows</TargetFramework>
    <Nullable>disable</Nullable>
    <UseWindowsForms>true</UseWindowsForms>
  </PropertyGroup>
  <ItemGroup>
    <ProjectReference Include="..\..\..\tools\HSDLib\HSDRawViewer\HSDRawViewer.csproj" />
  </ItemGroup>
</Project>
`;

await mkdir(workDir, { recursive: true });
await mkdir(outDir, { recursive: true });
await writeFile(program, source);
await writeFile(csproj, project);

const dotnet = path.resolve("dotnet-sdk-6.0.428-win-x64.exe");
const result = spawnSync("dotnet", ["run", "--project", csproj, "-c", "Release", "--", arcPath, outDir], {
  cwd: path.resolve("."),
  shell: true,
  stdio: "inherit",
});

process.exit(result.status ?? 1);
