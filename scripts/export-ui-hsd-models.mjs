#!/usr/bin/env node
import { mkdir, rm, writeFile } from "node:fs/promises";
import { existsSync } from "node:fs";
import path from "node:path";
import { spawnSync } from "node:child_process";
import { fileURLToPath } from "node:url";

const repoRoot = path.resolve(path.dirname(fileURLToPath(import.meta.url)), "..");
const args = process.argv.slice(2);
const region = args[0] && !args[0].startsWith("--") ? args.shift() : "GG4E";
const sceneNames = args.length > 0 ? args : [
  "tl00",
  "optn00",
  "staff00",
  "box00",
  "entry00",
  "brif00",
  "vsel00",
  "vsel01",
  "rpot20",
  "rpot21",
  "rpot22",
  "rpot23",
];

const sourceRoot = path.join(repoRoot, "user-data", region, "afs_data", "root");
const exportRoot = path.join(repoRoot, "user-data", region, "gltf-export");
const workDir = path.join(repoRoot, "user-data", region, "ui-model-exporter");
const csproj = path.join(workDir, "ui-model-exporter.csproj");
const program = path.join(workDir, "Program.cs");

for (const sceneName of sceneNames) {
  if (!/^[a-z0-9]+$/i.test(sceneName)) {
    throw new Error(`refusing invalid scene name: ${sceneName}`);
  }
}

const source = String.raw`
using System;
using System.IO;
using System.Linq;
using HSDRaw;
using HSDRaw.Common;
using HSDRawViewer.Converters;
using HSDRawViewer.Tools.Animation;

class UiModelExporter {
  static HSDRawFile OpenHsd(string arcPath) {
    var data = File.ReadAllBytes(arcPath);
    try {
      return new HSDRawFile(data);
    } catch {
      if (data.Length > 0x100 && ReadU32(data, 0) == 0x100) {
        return new HSDRawFile(data.Skip(0x100).ToArray());
      }
      throw;
    }
  }

  static uint ReadU32(byte[] data, int offset) {
    return ((uint)data[offset] << 24) | ((uint)data[offset + 1] << 16) | ((uint)data[offset + 2] << 8) | data[offset + 3];
  }

  static int ExportArc(string arcPath, string outDir) {
    Directory.CreateDirectory(outDir);
    var hsd = OpenHsd(arcPath);
    var settings = new ModelExportSettings {
      ExportMesh = true,
      ExportTextures = true,
      ExportBindPose = true,
      Optimize = true
    };

    int model = 0;
    int ok = 0;
    int fail = 0;
    foreach (var root in hsd.Roots) {
      var sobj = new HSD_SOBJ(){ _s = root.Data._s };
      if (sobj.JOBJDescs?.Array == null) continue;
      foreach (var jd in sobj.JOBJDescs.Array) {
        if (jd?.RootJoint == null) {
          model++;
          continue;
        }
        var outPath = Path.Combine(outDir, $"model_{model:D2}.dae");
        try {
          ModelExporter.ExportFile(outPath, jd.RootJoint, settings, new JointMap());
          Console.WriteLine($"OK {Path.GetFileName(arcPath)} model_{model:D2}.dae");
          ok++;
        } catch (Exception e) {
          Console.WriteLine($"ERR {Path.GetFileName(arcPath)} model_{model:D2}: {e.GetType().Name} {e.Message}");
          fail++;
        }
        model++;
      }
    }
    Console.WriteLine($"SUMMARY {Path.GetFileName(arcPath)} models={model} ok={ok} fail={fail}");
    return ok > 0 ? 0 : 2;
  }

  static int Main(string[] args) {
    if (args.Length < 2 || args.Length % 2 != 0) {
      Console.Error.WriteLine("usage: ui-model-exporter <arcPath> <outDir> [<arcPath> <outDir>...]");
      return 2;
    }

    int failed = 0;
    for (int i = 0; i < args.Length; i += 2) {
      try {
        var status = ExportArc(args[i], args[i + 1]);
        if (status != 0) failed++;
      } catch (Exception e) {
        Console.WriteLine($"ERR {Path.GetFileName(args[i])}: {e.GetType().Name} {e.Message}");
        failed++;
      }
    }
    return failed == 0 ? 0 : 1;
  }
}
`;

const project = String.raw`<Project Sdk="Microsoft.NET.Sdk">
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

function assertInside(child, parent, label) {
  const resolvedChild = path.resolve(child);
  const resolvedParent = path.resolve(parent);
  if (resolvedChild !== resolvedParent && !resolvedChild.startsWith(`${resolvedParent}${path.sep}`)) {
    throw new Error(`refusing ${label} outside ${resolvedParent}: ${resolvedChild}`);
  }
}

async function main() {
  if (!existsSync(sourceRoot)) throw new Error(`missing source root ${sourceRoot}`);
  await mkdir(workDir, { recursive: true });
  await mkdir(exportRoot, { recursive: true });
  await writeFile(program, source, "utf8");
  await writeFile(csproj, project, "utf8");

  const runArgs = [];
  for (const sceneName of sceneNames) {
    const arcPath = path.join(sourceRoot, `${sceneName}_mdl.arc`);
    if (!existsSync(arcPath)) {
      console.log(`SKIP ${sceneName}: missing ${path.relative(repoRoot, arcPath).replaceAll(path.sep, "/")}`);
      continue;
    }
    const outDir = path.join(exportRoot, sceneName);
    assertInside(outDir, exportRoot, "export target");
    await rm(outDir, { recursive: true, force: true });
    await mkdir(outDir, { recursive: true });
    runArgs.push(arcPath, outDir);
  }

  if (runArgs.length === 0) throw new Error("no source archives found for requested scenes");

  const result = spawnSync("dotnet", ["run", "--project", csproj, "-c", "Release", "--", ...runArgs], {
    cwd: repoRoot,
    shell: true,
    stdio: "inherit",
  });

  process.exit(result.status ?? 1);
}

main().catch((error) => {
  console.error(`export-ui-hsd-models: ${error.stack ?? error.message}`);
  process.exit(1);
});
