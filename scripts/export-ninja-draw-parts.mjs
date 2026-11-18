#!/usr/bin/env node
// Export selected extra roots from a user-provided, decompressed Ninja b_mdl ARC.
// Each model gets a separate directory: HSDRawViewer may reuse texture names.
import { access, copyFile, mkdir, mkdtemp, readFile, readdir, rm, writeFile } from 'node:fs/promises';
import { constants } from 'node:fs';
import os from 'node:os';
import path from 'node:path';
import { fileURLToPath } from 'node:url';
import { spawnSync } from 'node:child_process';

const root = fileURLToPath(new URL('../', import.meta.url));
const [archive, destination, ...requested] = process.argv.slice(2);
if (!archive || !destination || requested.length === 0 || requested.some(x => !/^[1-9]\d*$/.test(x) || +x > 255) || new Set(requested).size !== requested.length) {
  console.error('Usage: node scripts/export-ninja-draw-parts.mjs <decompressed-b_mdl.arc> <new-output-directory> <model-index> [model-index ...]');
  process.exit(2);
}
const input = path.resolve(archive), output = path.resolve(destination);
await access(input, constants.R_OK);
try { await access(output); throw Error(`Output already exists: ${output}`); }
catch (error) { if (error.code !== 'ENOENT') throw error; }
const viewerDir = path.join(root, 'tools/HSDLib/HSDRawViewer/bin/Release/net6.0-windows');
for (const name of ['HSDRaw.dll', 'HSDRawViewer.dll', 'IONET.dll']) await access(path.join(viewerDir, name), constants.R_OK);
const scratch = await mkdtemp(path.join(os.tmpdir(), 'gotyaforce-draw-export-'));
const xml = value => value.replaceAll('&', '&amp;').replaceAll('<', '&lt;').replaceAll('>', '&gt;').replaceAll('"', '&quot;');
const refs = ['HSDRaw', 'HSDRawViewer', 'IONET'].map(name => `<Reference Include="${name}"><HintPath>${xml(path.join(viewerDir, `${name}.dll`))}</HintPath></Reference>`).join('');
const project = `<Project Sdk="Microsoft.NET.Sdk"><PropertyGroup><OutputType>Exe</OutputType><TargetFramework>net6.0-windows</TargetFramework><UseWindowsForms>true</UseWindowsForms></PropertyGroup><ItemGroup>${refs}</ItemGroup></Project>`;
const source = String.raw`using System;using System.IO;using System.Linq;using System.Collections.Generic;using HSDRaw;using HSDRaw.Common;using HSDRawViewer.Converters;using HSDRawViewer.Tools.Animation;
class Exporter{static int Main(string[] a){var bytes=File.ReadAllBytes(a[0]);if(bytes.Length<=256)throw new Exception("ARC header missing");var file=new HSDRawFile(bytes.Skip(256).ToArray());var wanted=a.Skip(2).Select(int.Parse).ToHashSet();var seen=new HashSet<int>();int i=0;foreach(var root in file.Roots){var sobj=new HSD_SOBJ(){_s=root.Data._s};if(sobj.JOBJDescs?.Array==null)continue;foreach(var jd in sobj.JOBJDescs.Array){if(wanted.Contains(i)){if(jd?.RootJoint==null)throw new Exception($"model {i} has no root");var dir=Path.Combine(a[1],$"part_{i:D2}");Directory.CreateDirectory(dir);var settings=new ModelExportSettings{ExportMesh=true,ExportTextures=true,ExportBindPose=true,Optimize=true};ModelExporter.ExportFile(Path.Combine(dir,$"model_{i:D2}.dae"),jd.RootJoint,settings,new JointMap());seen.Add(i);}i++;}}if(!wanted.SetEquals(seen))throw new Exception("requested model index absent");return 0;}}`;
function run(command, args) {
  const result = spawnSync(command, args, {cwd: root, stdio: 'inherit', shell: false});
  if (result.error) throw result.error;
  if (result.status !== 0) throw Error(`${command} failed with status ${result.status}`);
}
try {
  await writeFile(path.join(scratch, 'export.csproj'), project);
  await writeFile(path.join(scratch, 'Program.cs'), source);
  run('dotnet', ['build', path.join(scratch, 'export.csproj'), '-c', 'Release', '--nologo']);
  const bin = path.join(scratch, 'bin/Release/net6.0-windows');
  for (const name of await readdir(viewerDir)) if (name.toLowerCase().endsWith('.dll')) await copyFile(path.join(viewerDir, name), path.join(bin, name));
  await mkdir(output, {recursive: false});
  run('dotnet', [path.join(bin, 'export.dll'), input, output, ...requested]);
  const dirs = requested.map(x => path.join(output, `part_${x.padStart(2, '0')}`));
  run(process.execPath, [path.join(root, 'scripts/convert-runtime-models-to-glb.mjs'), ...dirs]);
  for (let i = 0; i < requested.length; i++) {
    const glb = path.join(dirs[i], `model_${requested[i].padStart(2, '0')}.glb`);
    const header = await readFile(glb); if (header.subarray(0, 4).toString('ascii') !== 'glTF') throw Error(`Invalid GLB: ${glb}`);
  }
  console.log(`Exported ${requested.length} model roots to ${output}. Attachments are not automatically wired into gameplay.`);
} finally { await rm(scratch, {recursive: true, force: true}); }
