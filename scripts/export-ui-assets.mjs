#!/usr/bin/env node
import { mkdir, readdir, readFile, rm, stat, writeFile } from "node:fs/promises";
import { existsSync } from "node:fs";
import path from "node:path";
import { spawnSync } from "node:child_process";
import crypto from "node:crypto";

const repoRoot = process.cwd();
const scriptPath = "scripts/export-ui-assets.mjs";
const region = process.argv.find((arg) => !arg.startsWith("--") && arg !== process.argv[0] && arg !== process.argv[1]) ?? "GG4E";
const sourceRootRel = `user-data/${region}/afs_data/root`;
const sourceRoot = abs(sourceRootRel);
const publicUiRel = "apps/game/public/ui";
const publicUiRoot = abs(publicUiRel);
const researchRootRel = "research/asset-inventory";
const planRel = `${researchRootRel}/ui-export-plan.json`;
const helperResultRel = `${researchRootRel}/ui-export-helper-results.json`;
const researchManifestRel = `${researchRootRel}/ui-export-manifest.json`;
const blockersRel = `${researchRootRel}/ui-export-blockers.md`;
const helperRootRel = `user-data/${region}/ui-exporter`;
const helperRoot = abs(helperRootRel);
const helperProjectRel = `${helperRootRel}/ui-exporter.csproj`;
const helperProgramRel = `${helperRootRel}/Program.cs`;

const categoryDefinitions = [
  {
    id: "main-menu",
    label: "main menu",
    pattern: /^(titles|as_icon|ascii|font_00|icon|diskerr|optn00_mdl|tl00_mdl|staff00_mdl)\.(tpl|bin|arc)$/i,
  },
  {
    id: "adventure-select",
    label: "Adventure select",
    pattern: /^(vsel00_mdl|vsel01_mdl|vs[0-9a-f]+|nwld[0-9]{2}_mdl|arrow_mdl)\.(arc|tpl)$/i,
  },
  {
    id: "force-setup",
    label: "force setup",
    pattern: /^(unitall_mdl|allbox|trialbox|box00_mdl|plcmndata|name00_mdl|mcmg00_mdl|gets|gets[0-9]{2}_mdl|mn[0-9a-f]{4}|rpot[0-9]{2}_mdl|trade00_mdl)\.(arc|bin|pzz|tpl)$/i,
  },
  {
    id: "mission-intro-load",
    label: "mission intro/load",
    pattern: /^(firstld|brif00_mdl|entry00_mdl|msg[0-9]+|mc_msg[0-9]+|nm_msg|sh_msg|tr_msg|face[0-9a-f]{4}(_mdl)?|eyecatch[0-9]+|acd_end)\.(pzz|arc|mdt|tpl)$/i,
  },
  {
    id: "battle-hud",
    label: "battle HUD",
    pattern: /^(bn[0-9a-f]{4}|face[0-9a-f]{4}(_mdl)?|font_00|ascii|mini_t|as_icon|arrow_mdl|comhit2?|cmn_data|dc[0-9]+|fmg00_mdl)\.(tpl|arc|bin|pzz)$/i,
  },
  {
    id: "portraits-banners-fonts",
    label: "portraits/banners/fonts",
    pattern: /^(bn[0-9a-f]{4}|mn[0-9a-f]{4}|face[0-9a-f]{4}(_mdl)?|font_00|ascii|mini_t|titles)\.(tpl|arc)$/i,
  },
];

const kindByExt = new Map([
  [".tpl", "tpl"],
  [".arc", "hsd"],
  [".txg", "txg"],
]);

function abs(file) {
  return path.resolve(repoRoot, file);
}

function rel(file) {
  return path.relative(repoRoot, path.resolve(file)).replaceAll(path.sep, "/");
}

function slash(file) {
  return file.replaceAll(path.sep, "/");
}

function outputAssetDir(kind, sourceName) {
  const stem = path.parse(sourceName).name.toLowerCase();
  return slash(path.join(publicUiRel, kind, stem));
}

function classifyAsset(name) {
  return categoryDefinitions.filter((category) => category.pattern.test(name)).map((category) => category.id);
}

function categoryLabel(id) {
  return categoryDefinitions.find((category) => category.id === id)?.label ?? id;
}

async function listSourceFiles() {
  const entries = await readdir(sourceRoot, { withFileTypes: true });
  const files = [];
  for (const entry of entries) {
    if (!entry.isFile()) continue;
    const file = path.join(sourceRoot, entry.name);
    const fileStat = await stat(file);
    files.push({
      name: entry.name,
      sourcePath: rel(file),
      absPath: file,
      ext: path.extname(entry.name).toLowerCase(),
      bytes: fileStat.size,
    });
  }
  return files.sort((a, b) => a.name.localeCompare(b.name));
}

async function sha1File(file) {
  return crypto.createHash("sha1").update(await readFile(abs(file))).digest("hex");
}

async function ensureCleanPublicUi() {
  const resolved = path.resolve(publicUiRoot);
  const expected = path.resolve(repoRoot, publicUiRel);
  if (resolved !== expected) throw new Error(`refusing to clean unexpected output path ${resolved}`);
  await rm(publicUiRoot, { recursive: true, force: true });
  await mkdir(publicUiRoot, { recursive: true });
}

function makePlan(files) {
  const candidates = [];
  const skipped = [];

  for (const file of files) {
    const categories = classifyAsset(file.name);
    const kind = kindByExt.get(file.ext);
    if (!kind) continue;

    if (file.ext === ".txg" && categories.length === 0) {
      skipped.push({
        sourcePath: file.sourcePath,
        kind,
        reason: "TXG source is not classified as an original UI/HUD/menu asset by the UI inventory patterns.",
      });
      continue;
    }

    if (categories.length === 0) continue;
    if (kind !== "tpl" && kind !== "hsd" && kind !== "txg") continue;

    candidates.push({
      kind,
      sourceName: file.name,
      sourcePath: file.sourcePath,
      outputDir: outputAssetDir(kind, file.name),
      categories,
      categoryLabels: categories.map(categoryLabel),
      sourceBytes: file.bytes,
    });
  }

  return {
    generatedBy: scriptPath,
    generatedAt: new Date().toISOString(),
    region,
    repoRoot,
    sourceRoot: sourceRootRel,
    publicUiRoot: publicUiRel,
    helperProject: helperProjectRel,
    helperProgram: helperProgramRel,
    commands: {
      export: `rtk node ${scriptPath} ${region}`,
      helper: `dotnet run --project ${slash(helperProjectRel)} -c Release -- ${planRel} ${helperResultRel}`,
    },
    categoryDefinitions: categoryDefinitions.map(({ id, label }) => ({ id, label })),
    assets: candidates,
    skipped,
  };
}

function makePublicManifest(plan, helperResults) {
  const resultBySource = new Map(helperResults.assets.map((asset) => [asset.sourcePath, asset]));
  const assets = plan.assets.map((asset) => {
    const result = resultBySource.get(asset.sourcePath);
    const outputs = (result?.outputs ?? []).map((output) => ({
      path: output.path,
      publicPath: `/${output.path.replace(/^apps\/game\/public\//, "")}`,
      width: output.width,
      height: output.height,
      format: output.format,
      paletteFormat: output.paletteFormat ?? null,
      bytes: output.bytes,
      sha1: output.sha1,
      imageIndex: output.imageIndex,
      hsdModelIndex: output.hsdModelIndex ?? null,
      hsdTextureIndex: output.hsdTextureIndex ?? null,
    }));

    return {
      sourcePath: asset.sourcePath,
      sourceName: asset.sourceName,
      sourceKind: asset.kind,
      sourceBytes: asset.sourceBytes,
      categories: asset.categories,
      categoryLabels: asset.categoryLabels,
      status: result?.status ?? "not-run",
      error: result?.error ?? null,
      outputs,
      provenance: {
        extractorRoot: plan.sourceRoot,
        conversionCommand: plan.commands.export,
        helperCommand: plan.commands.helper,
        decoder: result?.decoder ?? null,
      },
    };
  });

  const outputs = assets.flatMap((asset) => asset.outputs.map((output) => ({ ...output, sourcePath: asset.sourcePath })));
  return {
    generatedBy: scriptPath,
    generatedAt: new Date().toISOString(),
    region,
    sourceRoot: plan.sourceRoot,
    publicUiRoot: plan.publicUiRoot,
    counts: {
      sourceAssets: assets.length,
      exportedAssets: assets.filter((asset) => asset.outputs.length > 0).length,
      exportedImages: outputs.length,
      blockedAssets: assets.filter((asset) => asset.outputs.length === 0).length,
      skippedNonUiTxg: plan.skipped.filter((asset) => asset.kind === "txg").length,
    },
    assets,
  };
}

function groupBlockers(manifest, plan, helperResults) {
  const groups = new Map();
  const add = (id, title, finding, record) => {
    if (!groups.has(id)) groups.set(id, { id, title, finding, records: [] });
    if (record) groups.get(id).records.push(record);
  };

  for (const asset of manifest.assets) {
    if (asset.outputs.length > 0) continue;
    const key =
      asset.sourceKind === "tpl"
        ? "tpl"
        : asset.sourceKind === "hsd"
          ? "hsd"
          : asset.sourceKind === "txg"
            ? "txg"
            : "other";
    const title =
      key === "tpl"
        ? "Standalone TPL textures"
        : key === "hsd"
          ? "HSD-derived UI archive textures"
          : key === "txg"
            ? "TXG UI texture groups"
            : "Other UI assets";
    const finding =
      key === "tpl"
        ? "At least one UI TPL candidate did not decode through HSDRaw GXImageConverter."
        : key === "hsd"
          ? "At least one UI HSD archive produced no decodable embedded textures through the standard SOBJ/JOBJ/DOBJ/TOBJ walk."
          : key === "txg"
            ? "At least one UI TXG candidate did not decode through the TXG header path."
            : "At least one candidate did not produce browser-ready textures.";
    add(key, title, finding, {
      sourcePath: asset.sourcePath,
      status: asset.status,
      error: asset.error ?? "no outputs",
      categories: asset.categoryLabels,
    });
  }

  for (const skipped of plan.skipped.filter((asset) => asset.kind === "txg")) {
    add(
      "txg-non-ui",
      "TXG source classification",
      "The current extract has TXG data, but no TXG file is classified as original UI/HUD/menu by the UI inventory patterns, so it is not exported into public/ui.",
      {
        sourcePath: skipped.sourcePath,
        status: "skipped",
        error: skipped.reason,
        categories: [],
      },
    );
  }

  if (helperResults.status !== "ok") {
    add("helper", "Helper command", "The generated HSDLib helper returned a non-zero exit code.", {
      sourcePath: helperProjectRel,
      status: helperResults.status,
      error: helperResults.error ?? `exit ${helperResults.exitCode}`,
      categories: [],
    });
  }

  return [...groups.values()];
}

function makeBlockerMarkdown(manifest, plan, helperResults) {
  const blockers = groupBlockers(manifest, plan, helperResults);
  const lines = [];
  const add = (line = "") => lines.push(line);

  add("# UI Asset Export Blockers");
  add();
  add(`Generated by \`${scriptPath}\` at \`${manifest.generatedAt}\`.`);
  add();
  add("## Command Evidence");
  add();
  add(`- Export command: \`${plan.commands.export}\``);
  add(`- Helper command: \`${plan.commands.helper}\``);
  add(`- Helper status: \`${helperResults.status}\`${helperResults.exitCode == null ? "" : `, exit \`${helperResults.exitCode}\``}`);
  add(`- Source root: \`${plan.sourceRoot}\``);
  add(`- Output root: \`${plan.publicUiRoot}\``);
  add();
  add("## Export Summary");
  add();
  add(`- Source candidates: ${manifest.counts.sourceAssets}`);
  add(`- Exported image files: ${manifest.counts.exportedImages}`);
  add(`- Assets with at least one exported image: ${manifest.counts.exportedAssets}`);
  add(`- Assets blocked or empty: ${manifest.counts.blockedAssets}`);
  add();

  if (blockers.length === 0) {
    add("No conversion blockers were observed for the scanned UI texture candidates.");
    return `${lines.join("\n")}\n`;
  }

  add("## Blockers");
  add();
  for (const blocker of blockers) {
    add(`### ${blocker.title}`);
    add();
    add(blocker.finding);
    add();
    add("| Source file | Status | Evidence | Categories |");
    add("| --- | --- | --- | --- |");
    for (const record of blocker.records) {
      add(
        `| \`${record.sourcePath}\` | \`${record.status}\` | ${escapeMd(record.error)} | ${
          record.categories.length ? record.categories.map((category) => `\`${category}\``).join(", ") : "n/a"
        } |`,
      );
    }
    add();
  }

  return `${lines.join("\n")}\n`;
}

function escapeMd(value) {
  return String(value ?? "").replaceAll("|", "\\|").replaceAll("\n", " ");
}

async function writeJson(file, value) {
  await mkdir(path.dirname(abs(file)), { recursive: true });
  await writeFile(abs(file), `${JSON.stringify(value, null, 2)}\n`, "utf8");
}

async function writeHelper() {
  await mkdir(helperRoot, { recursive: true });
  await writeFile(abs(helperProjectRel), helperProjectSource(), "utf8");
  await writeFile(abs(helperProgramRel), helperProgramSource(), "utf8");
}

function helperProjectSource() {
  return `<Project Sdk="Microsoft.NET.Sdk">
  <PropertyGroup>
    <OutputType>Exe</OutputType>
    <TargetFramework>net6.0</TargetFramework>
    <Nullable>disable</Nullable>
  </PropertyGroup>
  <ItemGroup>
    <ProjectReference Include="..\\..\\..\\tools\\HSDLib\\HSDRaw\\HSDRaw.csproj" />
    <PackageReference Include="SixLabors.ImageSharp" Version="3.1.8" />
  </ItemGroup>
</Project>
`;
}

function helperProgramSource() {
  return String.raw`using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Security.Cryptography;
using System.Text.Json;
using HSDRaw;
using HSDRaw.Common;
using HSDRaw.GX;
using HSDRaw.Tools;
using SixLabors.ImageSharp;
using SixLabors.ImageSharp.PixelFormats;

class Plan {
  public string repoRoot { get; set; }
  public string publicUiRoot { get; set; }
  public List<AssetPlan> assets { get; set; } = new();
}

class AssetPlan {
  public string kind { get; set; }
  public string sourceName { get; set; }
  public string sourcePath { get; set; }
  public string outputDir { get; set; }
  public List<string> categories { get; set; } = new();
}

class HelperResults {
  public string status { get; set; } = "ok";
  public string generatedAt { get; set; } = DateTime.UtcNow.ToString("O");
  public string decoder { get; set; } = "tools/HSDLib/HSDRaw GXImageConverter";
  public List<AssetResult> assets { get; set; } = new();
}

class AssetResult {
  public string sourcePath { get; set; }
  public string kind { get; set; }
  public string status { get; set; }
  public string error { get; set; }
  public string decoder { get; set; }
  public List<OutputRecord> outputs { get; set; } = new();
}

class OutputRecord {
  public string path { get; set; }
  public int imageIndex { get; set; }
  public int width { get; set; }
  public int height { get; set; }
  public string format { get; set; }
  public string paletteFormat { get; set; }
  public long bytes { get; set; }
  public string sha1 { get; set; }
  public int? hsdModelIndex { get; set; }
  public int? hsdTextureIndex { get; set; }
}

class Program {
  static int Main(string[] args) {
    if (args.Length != 2) {
      Console.Error.WriteLine("usage: ui-exporter <plan.json> <results.json>");
      return 2;
    }

    var options = new JsonSerializerOptions { PropertyNameCaseInsensitive = true, WriteIndented = true };
    var planPath = Path.GetFullPath(args[0]);
    var resultPath = Path.GetFullPath(args[1]);
    var plan = JsonSerializer.Deserialize<Plan>(File.ReadAllText(planPath), options);
    if (plan == null) throw new Exception("failed to parse plan");

    var results = new HelperResults();
    foreach (var asset in plan.assets) {
      var result = new AssetResult {
        sourcePath = asset.sourcePath,
        kind = asset.kind,
        decoder = "tools/HSDLib/HSDRaw GXImageConverter"
      };
      try {
        if (asset.kind == "tpl") ConvertTpl(plan, asset, result);
        else if (asset.kind == "hsd") ConvertHsd(plan, asset, result);
        else if (asset.kind == "txg") ConvertTxg(plan, asset, result);
        else throw new Exception($"unsupported kind {asset.kind}");

        result.status = result.outputs.Count > 0 ? "exported" : "no-decodable-textures";
        if (result.outputs.Count == 0 && result.error == null) result.error = "decoder found no texture payloads";
      } catch (Exception ex) {
        result.status = "blocked";
        result.error = ex.GetType().Name + ": " + ex.Message;
      }
      results.assets.Add(result);
    }

    Directory.CreateDirectory(Path.GetDirectoryName(resultPath));
    File.WriteAllText(resultPath, JsonSerializer.Serialize(results, options) + Environment.NewLine);
    Console.WriteLine($"ui-exporter assets={results.assets.Count} exportedImages={results.assets.Sum(a => a.outputs.Count)}");
    return 0;
  }

  static void ConvertTpl(Plan plan, AssetPlan asset, AssetResult result) {
    var data = File.ReadAllBytes(Path.Combine(plan.repoRoot, asset.sourcePath));
    if (data.Length < 12) throw new Exception("too small for TPL header");
    var magic = U32(data, 0);
    if (magic != 0x0020af30) throw new Exception($"unexpected TPL magic 0x{magic:X8}");

    var imageCount = CheckedCount(U32(data, 4), 256, "TPL image count");
    var tableOffset = CheckedOffset(U32(data, 8), data.Length, "TPL image table");

    for (int i = 0; i < imageCount; i++) {
      var entryOffset = tableOffset + i * 8;
      Require(entryOffset + 8 <= data.Length, "TPL image table entry outside file");
      var textureHeaderOffset = CheckedOffset(U32(data, entryOffset), data.Length, "TPL texture header");
      var paletteHeaderOffsetRaw = U32(data, entryOffset + 4);
      Require(textureHeaderOffset + 12 <= data.Length, "TPL texture header outside file");

      int height = U16(data, textureHeaderOffset);
      int width = U16(data, textureHeaderOffset + 2);
      var format = (GXTexFmt)U32(data, textureHeaderOffset + 4);
      var dataOffset = CheckedOffset(U32(data, textureHeaderOffset + 8), data.Length, "TPL image data");
      var imageSize = GXImageConverter.GetImageSize(format, width, height);
      Require(dataOffset + imageSize <= data.Length, "TPL image data outside file");
      var imageData = data.Skip(dataOffset).Take(imageSize).ToArray();

      byte[] bgra;
      string paletteFormat = null;
      if (GXImageConverter.IsPalettedFormat(format)) {
        var paletteHeaderOffset = CheckedOffset(paletteHeaderOffsetRaw, data.Length, "TPL palette header");
        Require(paletteHeaderOffset + 12 <= data.Length, "TPL palette header outside file");
        int colorCount = U16(data, paletteHeaderOffset);
        if (colorCount <= 0) colorCount = format == GXTexFmt.CI4 ? 16 : 256;
        var palFmt = (GXTlutFmt)U32(data, paletteHeaderOffset + 4);
        var paletteOffset = CheckedOffset(U32(data, paletteHeaderOffset + 8), data.Length, "TPL palette data");
        var paletteSize = colorCount * 2;
        Require(paletteOffset + paletteSize <= data.Length, "TPL palette data outside file");
        var paletteData = data.Skip(paletteOffset).Take(paletteSize).ToArray();
        bgra = GXImageConverter.DecodeTPL(format, width, height, imageData, palFmt, colorCount, paletteData);
        paletteFormat = palFmt.ToString();
      } else {
        bgra = GXImageConverter.DecodeTPL(format, width, height, imageData);
      }

      var outputPath = Path.Combine(plan.repoRoot, asset.outputDir, $"image_{i:D2}_{format}.png");
      result.outputs.Add(SaveImage(plan, outputPath, bgra, width, height, format.ToString(), paletteFormat, i, null, null));
    }
  }

  static void ConvertTxg(Plan plan, AssetPlan asset, AssetResult result) {
    var data = File.ReadAllBytes(Path.Combine(plan.repoRoot, asset.sourcePath));
    if (data.Length < 8) throw new Exception("too small for TXG offset table");
    var entryCount = CheckedCount(U32(data, 0), 128, "TXG entry count");
    var offsets = new List<int>();
    for (int i = 0; i < entryCount; i++) {
      var tableOffset = 4 + i * 4;
      Require(tableOffset + 4 <= data.Length, "TXG offset table outside file");
      var value = U32(data, tableOffset);
      if (value != 0xffffffff) offsets.Add(CheckedOffset(value, data.Length, "TXG texture entry"));
    }

    for (int i = 0; i < offsets.Count; i++) {
      var offset = offsets[i];
      Require(offset + 32 <= data.Length, "TXG texture header outside file");
      var imageCount = U32(data, offset);
      if (imageCount != 1) throw new Exception($"TXG entry {i} has unsupported imageCount {imageCount}");
      var format = (GXTexFmt)U32(data, offset + 4);
      int width = (int)U32(data, offset + 12);
      int height = (int)U32(data, offset + 16);
      var dataOffset = CheckedOffset(U32(data, offset + 24), data.Length, "TXG image data");
      var paletteOffsetWord = U32(data, offset + 28);
      if (GXImageConverter.IsPalettedFormat(format) || paletteOffsetWord != 0xffffffff) {
        throw new Exception($"TXG entry {i} uses a palette path that this exporter has not validated");
      }
      var imageSize = GXImageConverter.GetImageSize(format, width, height);
      Require(dataOffset + imageSize <= data.Length, "TXG image data outside file");
      var imageData = data.Skip(dataOffset).Take(imageSize).ToArray();
      var bgra = GXImageConverter.DecodeTPL(format, width, height, imageData);
      var outputPath = Path.Combine(plan.repoRoot, asset.outputDir, $"image_{i:D2}_{format}.png");
      result.outputs.Add(SaveImage(plan, outputPath, bgra, width, height, format.ToString(), null, i, null, null));
    }
  }

  static void ConvertHsd(Plan plan, AssetPlan asset, AssetResult result) {
    var source = Path.Combine(plan.repoRoot, asset.sourcePath);
    var data = File.ReadAllBytes(source);
    HSDRawFile hsd;
    try {
      hsd = new HSDRawFile(data);
    } catch {
      if (data.Length > 0x100 && U32(data, 0) == 0x100) {
        hsd = new HSDRawFile(data.Skip(0x100).ToArray());
      } else {
        throw;
      }
    }

    var seen = new HashSet<string>();
    int textureIndex = 0;
    int modelIndex = 0;
    foreach (var root in hsd.Roots) {
      var sobj = new HSD_SOBJ() { _s = root.Data._s };
      if (sobj.JOBJDescs?.Array == null) continue;
      foreach (var jd in sobj.JOBJDescs.Array) {
        if (jd?.RootJoint == null) {
          modelIndex++;
          continue;
        }
        foreach (var jobj in jd.RootJoint.TreeList) {
          if (jobj.Dobj == null) continue;
          foreach (var dobj in jobj.Dobj.List) {
            if (dobj.Mobj?.Textures == null) continue;
            foreach (var tobj in dobj.Mobj.Textures.List) {
              if (tobj.ImageData == null || tobj.ImageData.ImageData == null) continue;
              var bgra = tobj.GetDecodedImageData();
              if (bgra == null || bgra.Length == 0) continue;
              int width = tobj.ImageData.Width;
              int height = tobj.ImageData.Height;
              var format = tobj.ImageData.Format.ToString();
              var paletteFormat = tobj.TlutData?.Format.ToString();
              var key = Sha1(bgra) + $":{width}x{height}:{format}:{paletteFormat}";
              if (!seen.Add(key)) continue;
              var outputPath = Path.Combine(plan.repoRoot, asset.outputDir, $"texture_{textureIndex:D3}_{format}.png");
              result.outputs.Add(SaveImage(plan, outputPath, bgra, width, height, format, paletteFormat, textureIndex, modelIndex, textureIndex));
              textureIndex++;
            }
          }
        }
        modelIndex++;
      }
    }
  }

  static OutputRecord SaveImage(Plan plan, string outputPath, byte[] bgra, int width, int height, string format, string paletteFormat, int imageIndex, int? hsdModelIndex, int? hsdTextureIndex) {
    Directory.CreateDirectory(Path.GetDirectoryName(outputPath));
    using (var image = Image.LoadPixelData<Bgra32>(bgra, width, height)) {
      image.SaveAsPng(outputPath);
    }
    var info = new FileInfo(outputPath);
    return new OutputRecord {
      path = Rel(plan.repoRoot, outputPath),
      imageIndex = imageIndex,
      width = width,
      height = height,
      format = format,
      paletteFormat = paletteFormat,
      bytes = info.Length,
      sha1 = Sha1(File.ReadAllBytes(outputPath)),
      hsdModelIndex = hsdModelIndex,
      hsdTextureIndex = hsdTextureIndex
    };
  }

  static string Rel(string root, string file) {
    var rootUri = new Uri(Path.GetFullPath(root) + Path.DirectorySeparatorChar);
    var fileUri = new Uri(Path.GetFullPath(file));
    return Uri.UnescapeDataString(rootUri.MakeRelativeUri(fileUri).ToString()).Replace('\\', '/');
  }

  static string Sha1(byte[] data) {
    using var sha = SHA1.Create();
    return Convert.ToHexString(sha.ComputeHash(data)).ToLowerInvariant();
  }

  static ushort U16(byte[] data, int offset) {
    return (ushort)((data[offset] << 8) | data[offset + 1]);
  }

  static uint U32(byte[] data, int offset) {
    return ((uint)data[offset] << 24) | ((uint)data[offset + 1] << 16) | ((uint)data[offset + 2] << 8) | data[offset + 3];
  }

  static int CheckedOffset(uint value, int length, string label) {
    if (value > int.MaxValue || value >= length) throw new Exception($"{label} offset 0x{value:X} outside file");
    return (int)value;
  }

  static int CheckedCount(uint value, int max, string label) {
    if (value > max) throw new Exception($"{label} {value} exceeds max {max}");
    return (int)value;
  }

  static void Require(bool condition, string message) {
    if (!condition) throw new Exception(message);
  }
}
`;
}

async function main() {
  if (!existsSync(sourceRoot)) {
    throw new Error(`missing ${sourceRootRel}; run the project extraction first`);
  }

  await ensureCleanPublicUi();
  await mkdir(abs(researchRootRel), { recursive: true });

  const sourceFiles = await listSourceFiles();
  const plan = makePlan(sourceFiles);
  await writeJson(planRel, plan);
  await writeHelper();

  const helperArgs = ["run", "--project", abs(helperProjectRel), "-c", "Release", "--", abs(planRel), abs(helperResultRel)];
  const helperRun = spawnSync("dotnet", helperArgs, {
    cwd: repoRoot,
    encoding: "utf8",
  });

  let helperResults;
  if (existsSync(abs(helperResultRel))) {
    helperResults = JSON.parse(await readFile(abs(helperResultRel), "utf8"));
    helperResults.exitCode = helperRun.status ?? 1;
    helperResults.stdout = helperRun.stdout?.trim() ?? "";
    helperResults.stderr = helperRun.stderr?.trim() ?? "";
    helperResults.status = (helperRun.status ?? 1) === 0 ? "ok" : "failed";
  } else {
    helperResults = {
      status: "failed",
      exitCode: helperRun.status ?? 1,
      error: "helper did not write a result JSON",
      stdout: helperRun.stdout?.trim() ?? "",
      stderr: helperRun.stderr?.trim() ?? "",
      assets: [],
    };
  }

  await writeJson(helperResultRel, helperResults);

  const manifest = makePublicManifest(plan, helperResults);
  await writeJson(`${publicUiRel}/manifest.json`, {
    generatedBy: manifest.generatedBy,
    generatedAt: manifest.generatedAt,
    region: manifest.region,
    counts: manifest.counts,
    assets: manifest.assets.map((asset) => ({
      sourcePath: asset.sourcePath,
      sourceKind: asset.sourceKind,
      categoryLabels: asset.categoryLabels,
      status: asset.status,
      outputs: asset.outputs,
    })),
  });
  await writeJson(`${publicUiRel}/provenance.json`, manifest);
  await writeJson(researchManifestRel, {
    ...manifest,
    planPath: planRel,
    helperResultPath: helperResultRel,
    skipped: plan.skipped,
    helper: {
      project: helperProjectRel,
      program: helperProgramRel,
      stdout: helperResults.stdout ?? "",
      stderr: helperResults.stderr ?? "",
      exitCode: helperResults.exitCode ?? null,
    },
  });
  await writeFile(abs(blockersRel), makeBlockerMarkdown(manifest, plan, helperResults), "utf8");

  const publicManifestHash = await sha1File(`${publicUiRel}/manifest.json`);
  console.log("ui asset export");
  console.log(`source candidates: ${manifest.counts.sourceAssets}`);
  console.log(`exported images: ${manifest.counts.exportedImages}`);
  console.log(`blocked/empty assets: ${manifest.counts.blockedAssets}`);
  console.log(`wrote ${publicUiRel}/manifest.json sha1=${publicManifestHash}`);
  console.log(`wrote ${publicUiRel}/provenance.json`);
  console.log(`wrote ${researchManifestRel}`);
  console.log(`wrote ${blockersRel}`);

  if ((helperRun.status ?? 1) !== 0) {
    process.exit(helperRun.status ?? 1);
  }
}

main().catch((error) => {
  console.error(`export-ui-assets: ${error.stack ?? error.message}`);
  process.exit(1);
});
