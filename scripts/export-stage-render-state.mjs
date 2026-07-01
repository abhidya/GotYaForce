#!/usr/bin/env node
import fs from "node:fs";
import path from "node:path";
import { fileURLToPath } from "node:url";

const repoRoot = path.resolve(path.dirname(fileURLToPath(import.meta.url)), "..");

const DEFAULT_STAGE_ID = "st00";
const DEFAULT_INPUT = path.join("research", "asset-inventory", "stage-lighting-render-state.json");
const DEFAULT_PUBLIC_STAGES = path.join("apps", "game", "public", "stages");

const options = parseArgs(process.argv.slice(2));
if (options.help) usage(0);

const inputPath = path.resolve(repoRoot, options.input);
const publicStagesRoot = path.resolve(repoRoot, options.publicStages);

const inventory = readJson(inputPath);
const stageIds = options.all ? publicStageIds(publicStagesRoot) : [options.stageId];
const written = [];

for (const stageId of stageIds) {
  const stage = findStage(inventory, stageId);
  if (!stage) fail(`stage ${stageId} is not present in ${rel(inputPath)}`);

  const outputPath = path.resolve(publicStagesRoot, stageId, "render-state.json");
  const manifestPath = path.resolve(publicStagesRoot, stageId, "manifest.json");
  const manifest = readJsonIfExists(manifestPath);
  if (!manifest.ok) fail(`stage manifest did not parse: ${rel(manifestPath)} (${manifest.error})`);

  const renderState = buildRenderState({ inventory, stage, stageId, manifest: manifest.value, inputPath, manifestPath });
  verifyExactCopies(renderState, stage);
  writeJson(outputPath, renderState);
  written.push({ stageId, outputPath, renderState });
}

for (const entry of written) {
  console.log(
    `export-stage-render-state: wrote ${rel(entry.outputPath)} camera ${entry.renderState.camera.objectName} lights ${entry.renderState.lights.length} fog ${entry.renderState.fog.objectName}`,
  );
}
console.log(`export-stage-render-state: wrote ${written.length} stage render-state file${written.length === 1 ? "" : "s"}`);

function parseArgs(args) {
  const parsed = {
    stageId: DEFAULT_STAGE_ID,
    input: DEFAULT_INPUT,
    publicStages: DEFAULT_PUBLIC_STAGES,
    all: false,
    help: false,
  };

  for (let i = 0; i < args.length; i += 1) {
    const arg = args[i];
    if (arg === "--help" || arg === "-h") {
      parsed.help = true;
    } else if (arg === "--stage") {
      parsed.stageId = normalizeStageId(requiredValue(args, ++i, arg));
    } else if (arg.startsWith("--stage=")) {
      parsed.stageId = normalizeStageId(arg.slice("--stage=".length));
    } else if (arg === "--input") {
      parsed.input = requiredValue(args, ++i, arg);
    } else if (arg.startsWith("--input=")) {
      parsed.input = arg.slice("--input=".length);
    } else if (arg === "--public-stages") {
      parsed.publicStages = requiredValue(args, ++i, arg);
    } else if (arg.startsWith("--public-stages=")) {
      parsed.publicStages = arg.slice("--public-stages=".length);
    } else if (arg === "--all") {
      parsed.all = true;
    } else if (arg.startsWith("--")) {
      fail(`unknown option "${arg}"`);
    } else {
      parsed.stageId = normalizeStageId(arg);
    }
  }

  return parsed;
}

function usage(code) {
  const stream = code === 0 ? process.stdout : process.stderr;
  stream.write(`usage: node scripts/export-stage-render-state.mjs [stage] [options]

Exports browser-consumable camera, light, and fog JSON from
research/asset-inventory/stage-lighting-render-state.json.

Options:
  --stage <st##>          stage id to export (default: st00)
  --all                   export every stage listed in public stages manifest
  --input <path>          research render-state inventory JSON
  --public-stages <path>  browser public stages root
`);
  process.exit(code);
}

function buildRenderState({ inventory, stage, stageId, manifest, inputPath, manifestPath }) {
  const scene = stage.scene;
  if (!scene) fail(`stage ${stage.stageId ?? stageId} has no scene record`);
  if (!Array.isArray(scene.cameras) || scene.cameras.length === 0) fail("no camera evidence found");
  if (!Array.isArray(scene.lights) || scene.lights.length === 0) fail("no light evidence found");
  if (!Array.isArray(scene.fogs) || scene.fogs.length === 0) fail("no fog evidence found");

  const camera = scene.cameras[0];
  const fog = scene.fogs[0];

  return {
    stageId: stage.stageId ?? stageId,
    generatedBy: "scripts/export-stage-render-state.mjs",
    source: {
      renderStateInventory: rel(inputPath),
      inventoryGeneratedAt: inventory.generatedAt ?? null,
      inventoryScanner: inventory.scanner ?? null,
      stageManifest: rel(manifestPath),
      stageManifestId: manifest.id ?? null,
      stageRenderStatus: manifest.renderStatus ?? null,
      archiveName: stage.archiveName ?? null,
      sourcePath: stage.sourcePath ?? null,
    },
    camera: exportCamera(camera),
    lights: scene.lights.map(exportLight),
    fog: exportFog(fog),
  };
}

function findStage(inventory, stageId) {
  return inventory[stageId] ?? inventory.stages?.find((stage) => stage.stageId === stageId) ?? null;
}

function publicStageIds(publicStagesRoot) {
  const manifestPath = path.join(publicStagesRoot, "manifest.json");
  const manifest = readJsonIfExists(manifestPath);
  if (!manifest.ok) fail(`public stage manifest did not parse: ${rel(manifestPath)} (${manifest.error})`);
  const ids = manifest.value?.stages?.map((stage) => stage.id).filter(Boolean) ?? [];
  if (ids.length === 0) fail(`public stage manifest contains no stages: ${rel(manifestPath)}`);
  return ids.map(normalizeStageId);
}

function exportCamera(camera) {
  return {
    index: camera.index,
    objectName: camera.objectName,
    confidence: camera.confidence,
    source: clone(camera.source),
    entry: clone(camera.entry),
    evidence: clone(camera.evidence),
    projection: camera.decoded.projection,
    eye: clone(camera.decoded.eye),
    interest: clone(camera.decoded.interest),
    near: camera.decoded.near,
    far: camera.decoded.far,
    fovDegrees: camera.decoded.fovDegrees,
    aspect: camera.decoded.aspect,
    raw: {
      flagsOrClass: camera.raw.flagsOrClass,
      projectionType: camera.raw.projectionType,
      viewportWidth: camera.raw.viewportWidth,
      viewportHeight: camera.raw.viewportHeight,
      scissorWidth: camera.raw.scissorWidth,
      scissorHeight: camera.raw.scissorHeight,
      rollOrUnknown0: camera.raw.rollOrUnknown0,
      unknown1: camera.raw.unknown1,
      near: camera.raw.near,
      far: camera.raw.far,
      fovDegrees: camera.raw.fovDegrees,
      aspect: camera.raw.aspect,
    },
  };
}

function exportLight(light) {
  return {
    index: light.index,
    objectName: light.objectName,
    confidence: light.confidence,
    source: clone(light.source),
    entry: clone(light.entry),
    evidence: clone(light.evidence),
    role: light.decoded.role,
    flags: light.raw.flags,
    color: {
      rawHex: light.raw.color.rawHex,
      rgbHex: light.decoded.colorRgbHex,
      rgba: clone(light.decoded.colorRgba),
      normalized: clone(light.raw.color.normalized),
    },
    position: clone(light.decoded.position),
    interestOrParam: clone(light.decoded.interestOrParam),
    raw: {
      classNamePointer: clone(light.raw.classNamePointer),
      nextOrFlags0: light.raw.nextOrFlags0,
      flags: light.raw.flags,
      color: clone(light.raw.color),
      positionPointer: clone(light.raw.positionPointer),
      interestOrParamPointer: clone(light.raw.interestOrParamPointer),
    },
  };
}

function exportFog(fog) {
  return {
    index: fog.index,
    objectName: fog.objectName,
    confidence: fog.confidence,
    source: clone(fog.source),
    entry: clone(fog.entry),
    evidence: clone(fog.evidence),
    type: fog.decoded.type,
    flagsOrEnabled: fog.raw.flagsOrEnabled,
    start: fog.decoded.start,
    end: fog.decoded.end,
    color: {
      rawHex: fog.raw.color.rawHex,
      rgbHex: fog.decoded.colorRgbHex,
      rgba: clone(fog.decoded.colorRgba),
      normalized: clone(fog.raw.color.normalized),
    },
    raw: clone(fog.raw),
  };
}

function verifyExactCopies(renderState, stage) {
  const camera = stage.scene.cameras[0];
  const fog = stage.scene.fogs[0];

  assertSame("camera.projection", renderState.camera.projection, camera.decoded.projection);
  assertSame("camera.eye", renderState.camera.eye, camera.decoded.eye);
  assertSame("camera.interest", renderState.camera.interest, camera.decoded.interest);
  assertSame("camera.near", renderState.camera.near, camera.decoded.near);
  assertSame("camera.far", renderState.camera.far, camera.decoded.far);
  assertSame("camera.fovDegrees", renderState.camera.fovDegrees, camera.decoded.fovDegrees);
  assertSame("camera.aspect", renderState.camera.aspect, camera.decoded.aspect);

  assertSame("lights.length", renderState.lights.length, stage.scene.lights.length);
  for (const [index, light] of stage.scene.lights.entries()) {
    const exported = renderState.lights[index];
    assertSame(`lights[${index}].role`, exported.role, light.decoded.role);
    assertSame(`lights[${index}].flags`, exported.flags, light.raw.flags);
    assertSame(`lights[${index}].color.rgbHex`, exported.color.rgbHex, light.decoded.colorRgbHex);
    assertSame(`lights[${index}].color.rgba`, exported.color.rgba, light.decoded.colorRgba);
    assertSame(`lights[${index}].color.normalized`, exported.color.normalized, light.raw.color.normalized);
    assertSame(`lights[${index}].position`, exported.position, light.decoded.position);
    assertSame(`lights[${index}].interestOrParam`, exported.interestOrParam, light.decoded.interestOrParam);
  }

  assertSame("fog.type", renderState.fog.type, fog.decoded.type);
  assertSame("fog.flagsOrEnabled", renderState.fog.flagsOrEnabled, fog.raw.flagsOrEnabled);
  assertSame("fog.start", renderState.fog.start, fog.decoded.start);
  assertSame("fog.end", renderState.fog.end, fog.decoded.end);
  assertSame("fog.color.rgbHex", renderState.fog.color.rgbHex, fog.decoded.colorRgbHex);
  assertSame("fog.color.rgba", renderState.fog.color.rgba, fog.decoded.colorRgba);
  assertSame("fog.color.normalized", renderState.fog.color.normalized, fog.raw.color.normalized);
}

function assertSame(label, actual, expected) {
  if (JSON.stringify(actual) !== JSON.stringify(expected)) {
    fail(`${label} was not copied exactly from research JSON`);
  }
}

function readJson(file) {
  try {
    return JSON.parse(fs.readFileSync(file, "utf8"));
  } catch (error) {
    fail(`could not read JSON ${rel(file)}: ${error.message}`);
  }
}

function readJsonIfExists(file) {
  try {
    return { ok: true, value: JSON.parse(fs.readFileSync(file, "utf8")), error: null };
  } catch (error) {
    if (error.code === "ENOENT") return { ok: false, value: null, error: "missing" };
    return { ok: false, value: null, error: error.message };
  }
}

function writeJson(file, value) {
  fs.mkdirSync(path.dirname(file), { recursive: true });
  fs.writeFileSync(`${file}.tmp`, `${JSON.stringify(value, null, 2)}\n`, "utf8");
  fs.renameSync(`${file}.tmp`, file);
}

function clone(value) {
  return value === undefined ? null : JSON.parse(JSON.stringify(value));
}

function normalizeStageId(value) {
  const normalized = String(value).trim().toLowerCase();
  if (!/^st[0-9a-f]{2}$/.test(normalized)) fail(`invalid stage id "${value}"`);
  return normalized;
}

function requiredValue(args, index, flag) {
  const value = args[index];
  if (!value || value.startsWith("--")) fail(`${flag} requires a value`);
  return value;
}

function rel(file) {
  return path.relative(repoRoot, file).replaceAll(path.sep, "/");
}

function fail(message) {
  console.error(`export-stage-render-state: ${message}`);
  process.exit(1);
}
