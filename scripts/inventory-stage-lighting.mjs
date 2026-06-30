#!/usr/bin/env node
import fs from "node:fs";
import path from "node:path";
import { fileURLToPath } from "node:url";

const repoRoot = path.resolve(path.dirname(fileURLToPath(import.meta.url)), "..");

const paths = {
  discRoot: path.join(repoRoot, "user-data", "GG4E", "afs_data", "root"),
  disc: path.join(repoRoot, "user-data", "GG4E", "disc"),
  browserStages: path.join(repoRoot, "apps", "game", "public", "stages"),
  formatSpecs: path.join(repoRoot, "research", "format-specs"),
  symbolMap: path.join(repoRoot, "research", "symbols", "GG4E-CSM-20220412.map"),
  bootDol: path.join(repoRoot, "user-data", "GG4E", "disc", "sys", "boot.dol"),
  browserMain: path.join(repoRoot, "apps", "game", "src", "main.ts"),
  outputDir: path.join(repoRoot, "research", "asset-inventory"),
};

const outputJson = path.join(paths.outputDir, "stage-lighting-render-state.json");
const outputMarkdown = path.join(paths.outputDir, "stage-lighting-render-state.md");

for (const input of [
  paths.discRoot,
  paths.disc,
  paths.browserStages,
  paths.formatSpecs,
  paths.symbolMap,
  paths.bootDol,
  paths.browserMain,
]) {
  mustExist(input);
}

const stageArcFiles = fs
  .readdirSync(paths.discRoot)
  .filter((name) => /^st[0-9a-f]{2}_mdl\.arc$/i.test(name))
  .sort((a, b) => a.localeCompare(b))
  .map((name) => path.join(paths.discRoot, name));

if (stageArcFiles.length === 0) fail(`no st##_mdl.arc files under ${rel(paths.discRoot)}`);

const stages = stageArcFiles.map((file) => analyzeStageArc(file));
const st00 = stages.find((stage) => stage.stageId === "st00");
if (!st00) fail("st00_mdl.arc was not found");

const report = {
  generatedAt: new Date().toISOString(),
  scanner: rel(fileURLToPath(import.meta.url)),
  purpose: "Inventory original Gotcha Force stage lighting/fog/material/camera render-state candidates.",
  inputs: {
    discRoot: rel(paths.discRoot),
    disc: rel(paths.disc),
    browserStages: rel(paths.browserStages),
    formatSpecs: fs
      .readdirSync(paths.formatSpecs)
      .filter((name) => name.endsWith(".md"))
      .sort()
      .map((name) => rel(path.join(paths.formatSpecs, name))),
    symbolMap: rel(paths.symbolMap),
    bootDol: fileInfo(paths.bootDol),
    browserMain: rel(paths.browserMain),
  },
  symbols: readRenderSymbols(),
  browserCurrentFakes: scanBrowserMain(),
  summary: summarizeStages(stages),
  st00,
  stages,
  recommendations: buildRecommendations(st00),
  unresolvedQuestions: [
    "Raw HSD MObj/PEDesc material and cull/blend/Z-mode offsets were not fully decoded here; use HSDRaw or a focused parser pass before importing those fields.",
    "Scene LObj flag bit names need confirmation against HSD headers or a small runtime HSD_LObjSetup capture; this report records raw flags and colors.",
    "Camera eye/interest descriptors look like original CObj/WObj data, but in-game battle camera may override them after scene load; confirm with the existing CObj breakpoints before replacing gameplay camera behavior.",
    "No broad Dolphin logs were run. If runtime proof is needed, use one-frame breakpoints on HSD_CObjSet*, HSD_LObjSetup, HSD_FogSet, HSD_SetMaterialColor, and HSD_StateSet* only.",
  ],
};

fs.mkdirSync(paths.outputDir, { recursive: true });
writeJson(outputJson, report);
fs.writeFileSync(`${outputMarkdown}.tmp`, renderMarkdown(report), "utf8");
fs.renameSync(`${outputMarkdown}.tmp`, outputMarkdown);

console.log("stage lighting/render-state inventory");
console.log(`stage arcs scanned: ${report.summary.stageArcCount}`);
console.log(`st00 models: ${st00.scene.jobjDescCount}`);
console.log(`st00 cameras: ${st00.scene.cameras.length}`);
console.log(`st00 lights: ${st00.scene.lights.length}`);
console.log(`st00 fog descriptors: ${st00.scene.fogs.length}`);
console.log(`st00 POBJ draw-state candidates: ${st00.drawState.pobjCount}`);
console.log(`st00 DAE materials: ${st00.exportedMaterialState.materialCount}`);
console.log(`wrote ${rel(outputJson)}`);
console.log(`wrote ${rel(outputMarkdown)}`);

function analyzeStageArc(file) {
  const hsd = readHsdDat(file);
  const stageId = path.basename(file, "_mdl.arc").toLowerCase();
  const root = hsd.roots.find((entry) => entry.name === "scene_data") ?? hsd.roots[0];
  if (!root) fail(`no roots in ${rel(file)}`);

  const scene = parseScene(hsd, root);
  const drawState = scanPObjDrawState(hsd);
  const exportedMaterialState = scanExportedStageMaterials(stageId);

  return {
    stageId,
    archiveName: path.basename(file),
    sourcePath: rel(file),
    sourceFile: fileInfo(file),
    hsd: {
      container: hsd.container,
      datBaseFileOffset: hex(hsd.base),
      fileSize: hsd.fileSize,
      dataBlockSize: hsd.dataBlockSize,
      relocCount: hsd.relocCount,
      rootCount: hsd.rootCount,
      externalRefCount: hsd.externalRefCount,
      rootTableFileOffset: hex(hsd.rootTableOffset),
      symbolTableFileOffset: hex(hsd.symbolTableOffset),
      layoutOk: hsd.base + hsd.fileSize === hsd.buffer.length,
      roots: hsd.roots.map((entry) => ({
        name: entry.name,
        dataOffset: hex(entry.dataOffset),
        fileOffset: hex(relToFileOffset(hsd, entry.dataOffset)),
      })),
    },
    scene,
    drawState,
    exportedMaterialState,
  };
}

function parseScene(hsd, root) {
  const sceneRel = root.dataOffset;
  const scenePointers = [0, 4, 8, 12].map((fieldOffset) => ({
    fieldOffset: hex(fieldOffset),
    dataOffset: hex(sceneRel + fieldOffset),
    fileOffset: hex(relToFileOffset(hsd, sceneRel + fieldOffset)),
    relocationMarked: hsd.relocSet.has(sceneRel + fieldOffset),
    targetDataOffset: hex(readU32(hsd, sceneRel + fieldOffset)),
    targetFileOffset: hex(relToFileOffset(hsd, readU32(hsd, sceneRel + fieldOffset))),
  }));

  const jobjDescTableRel = readU32(hsd, sceneRel);
  const jobjDescs = parseJObjDescTable(hsd, jobjDescTableRel);
  const cameras = parseCameras(hsd, readU32(hsd, sceneRel + 4));
  const lights = parseLights(hsd, readU32(hsd, sceneRel + 8));
  const fogs = parseFogs(hsd, readU32(hsd, sceneRel + 12));

  return {
    rootName: root.name,
    rootDataOffset: hex(root.dataOffset),
    rootFileOffset: hex(relToFileOffset(hsd, root.dataOffset)),
    interpretation: "HSD_SOBJ-like scene_data with 4 relocation-marked scene tables: JOBJDesc, CObj, LObj, Fog.",
    confidence: scenePointers.every((pointer) => pointer.relocationMarked) ? "high" : "medium",
    scenePointers,
    jobjDescTable: {
      dataOffset: hex(jobjDescTableRel),
      fileOffset: hex(relToFileOffset(hsd, jobjDescTableRel)),
      interpretation: "Null-terminated HSD_JOBJDesc pointer table; count matches exported model_XX.dae count when present.",
    },
    jobjDescCount: jobjDescs.length,
    jobjAnimationSummary: summarizeJObjAnimations(jobjDescs),
    jobjDescSamples: jobjDescs.slice(0, 8),
    cameras,
    lights,
    fogs,
    animationDescriptorCandidates: collectSceneAnimationCandidates(hsd, sceneRel, cameras, lights, fogs),
  };
}

function parseJObjDescTable(hsd, tableRel) {
  const result = [];
  for (let i = 0; i < 512; i += 1) {
    const fieldRel = tableRel + i * 4;
    if (fieldRel + 4 > hsd.dataBlockSize) break;
    const descRel = readU32(hsd, fieldRel);
    if (descRel === 0) break;
    if (!hsd.relocSet.has(fieldRel)) break;
    result.push({
      index: i,
      tableFieldDataOffset: hex(fieldRel),
      tableFieldFileOffset: hex(relToFileOffset(hsd, fieldRel)),
      descDataOffset: hex(descRel),
      descFileOffset: hex(relToFileOffset(hsd, descRel)),
      rootJoint: pointerField(hsd, descRel, 0x00),
      jointAnimations: pointerField(hsd, descRel, 0x04),
      materialAnimations: pointerField(hsd, descRel, 0x08),
      shapeAnimations: pointerField(hsd, descRel, 0x0c),
    });
  }
  return result;
}

function summarizeJObjAnimations(jobjDescs) {
  return {
    jointAnimationDescriptors: jobjDescs.filter((entry) => entry.jointAnimations.targetDataOffset !== null).length,
    materialAnimationDescriptors: jobjDescs.filter((entry) => entry.materialAnimations.targetDataOffset !== null).length,
    shapeAnimationDescriptors: jobjDescs.filter((entry) => entry.shapeAnimations.targetDataOffset !== null).length,
  };
}

function parseCameras(hsd, tableRel) {
  if (!isRel(hsd, tableRel)) return [];

  const descRel = readU32(hsd, tableRel);
  if (!isRel(hsd, descRel)) return [];

  const eye = pointerField(hsd, descRel, 0x18);
  const interest = pointerField(hsd, descRel, 0x1c);

  return [
    {
      index: 0,
      objectName: "scene_data.cameras[0].HSD_CObjDesc",
      source: sourceAt(hsd, descRel),
      entry: sourceAt(hsd, tableRel),
      confidence: "high",
      evidence: [
        "scene_data field[1] points to a CObj table entry",
        "descriptor carries 640x480 viewport/scissor, eye/interest WObj pointers, near/far/fov/aspect floats",
        "symbol map contains HSD_CObjLoad/SetCurrent/SetEyePosition/SetInterest/SetFov/SetNear/SetFar",
      ],
      raw: {
        flagsOrClass: hex(readU32(hsd, descRel)),
        projectionType: readU32(hsd, descRel + 0x04),
        viewportWidth: readU32(hsd, descRel + 0x08),
        viewportHeight: readU32(hsd, descRel + 0x0c),
        scissorWidth: readU32(hsd, descRel + 0x10),
        scissorHeight: readU32(hsd, descRel + 0x14),
        eyePointer: eye,
        interestPointer: interest,
        rollOrUnknown0: readF32(hsd, descRel + 0x20),
        unknown1: readF32(hsd, descRel + 0x24),
        near: readF32(hsd, descRel + 0x28),
        far: readF32(hsd, descRel + 0x2c),
        fovDegrees: readF32(hsd, descRel + 0x30),
        aspect: readF32(hsd, descRel + 0x34),
      },
      decoded: {
        projection: readU32(hsd, descRel + 0x04) === 1 ? "perspective" : "unknown",
        eye: parseWObj(hsd, eye.targetDataOffsetRaw),
        interest: parseWObj(hsd, interest.targetDataOffsetRaw),
        near: round(readF32(hsd, descRel + 0x28)),
        far: round(readF32(hsd, descRel + 0x2c)),
        fovDegrees: round(readF32(hsd, descRel + 0x30)),
        aspect: round(readF32(hsd, descRel + 0x34)),
      },
    },
  ];
}

function parseLights(hsd, tableRel) {
  if (!isRel(hsd, tableRel)) return [];

  const lights = [];
  for (let i = 0; i < 16; i += 1) {
    const entryFieldRel = tableRel + i * 4;
    const entryRel = readU32(hsd, entryFieldRel);
    if (entryRel === 0) break;
    if (!hsd.relocSet.has(entryFieldRel) || !isRel(hsd, entryRel)) break;

    const descRel = readU32(hsd, entryRel);
    if (!isRel(hsd, descRel)) continue;
    const flags = readU32(hsd, descRel + 0x08);
    const color = readColor(hsd, descRel + 0x0c);
    const position = pointerField(hsd, descRel, 0x10);
    const interestOrParam = pointerField(hsd, descRel, 0x18);

    lights.push({
      index: i,
      objectName: `scene_data.lights[${i}].HSD_LObjDesc`,
      source: sourceAt(hsd, descRel),
      entry: sourceAt(hsd, entryRel),
      confidence: "high",
      evidence: [
        "scene_data field[2] is a null-terminated table of light entries",
        "entries point to descriptors with LObj-like flags, GXColor bytes, and optional WObj pointer",
        "symbol map contains HSD_LObjLoadDesc/HSD_LObjSetup/HSD_LObjSetColor/HSD_LObjGetPosition",
      ],
      raw: {
        classNamePointer: pointerField(hsd, descRel, 0x00),
        nextOrFlags0: hex(readU32(hsd, descRel + 0x04)),
        flags: hex(flags),
        color,
        positionPointer: position,
        interestOrParamPointer: interestOrParam,
      },
      decoded: {
        role: inferLightRole(flags, position.targetDataOffsetRaw),
        colorRgbHex: color.rgbHex,
        colorRgba: color.rgba,
        position: parseWObj(hsd, position.targetDataOffsetRaw),
        interestOrParam: parseWObj(hsd, interestOrParam.targetDataOffsetRaw),
      },
    });
  }

  return lights;
}

function parseFogs(hsd, tableRel) {
  if (!isRel(hsd, tableRel)) return [];
  const descRel = readU32(hsd, tableRel);
  if (!isRel(hsd, descRel)) return [];

  return [
    {
      index: 0,
      objectName: "scene_data.fogs[0].HSD_FogDesc",
      source: sourceAt(hsd, descRel),
      entry: sourceAt(hsd, tableRel),
      confidence: "high",
      evidence: [
        "scene_data field[3] points to a fog entry",
        "descriptor has fog type/enable-like words, start/end floats, and GXColor bytes",
        "symbol map contains HSD_FogLoadDesc/HSD_FogSet/GXSetFog",
      ],
      raw: {
        type: readU32(hsd, descRel),
        flagsOrEnabled: readU32(hsd, descRel + 0x04),
        start: readF32(hsd, descRel + 0x08),
        end: readF32(hsd, descRel + 0x0c),
        color: readColor(hsd, descRel + 0x10),
      },
      decoded: {
        type: readU32(hsd, descRel),
        start: round(readF32(hsd, descRel + 0x08)),
        end: round(readF32(hsd, descRel + 0x0c)),
        colorRgbHex: readColor(hsd, descRel + 0x10).rgbHex,
        colorRgba: readColor(hsd, descRel + 0x10).rgba,
      },
    },
  ];
}

function collectSceneAnimationCandidates(hsd, sceneRel, cameras, lights, fogs) {
  const candidates = [];
  const cameraTableRel = readU32(hsd, sceneRel + 4);
  const lightTableRel = readU32(hsd, sceneRel + 8);
  const fogTableRel = readU32(hsd, sceneRel + 12);

  if (isRel(hsd, cameraTableRel)) {
    candidates.push({
      owner: "scene_data.cameras[0]",
      kind: "CObj/WObj AObj or FObj descriptor candidate",
      confidence: "medium",
      source: sourceAt(hsd, cameraTableRel + 0x04),
      pointer: pointerField(hsd, cameraTableRel, 0x04),
      note: "Paired pointer beside the CObjDesc entry; not decoded here.",
    });
    candidates.push({
      owner: "scene_data.cameras[0]",
      kind: "Camera FObj/AObj track payload candidate",
      confidence: "low",
      source: sourceAt(hsd, cameraTableRel + 0x08),
      pointer: pointerField(hsd, cameraTableRel, 0x08),
      note: "Adjacent pointer leads into compact bytecode-like data; needs HSD_FObj parser confirmation.",
    });
  }

  for (const light of lights) {
    const entryRel = parseHex(light.entry.dataOffset);
    candidates.push({
      owner: light.objectName,
      kind: "LObj AObj/FObj descriptor candidate",
      confidence: "medium",
      source: sourceAt(hsd, entryRel + 0x04),
      pointer: pointerField(hsd, entryRel, 0x04),
      note: "Paired pointer beside LObjDesc entry; likely animation/track data when non-null.",
    });
  }

  if (isRel(hsd, fogTableRel)) {
    candidates.push({
      owner: fogs[0]?.objectName ?? "scene_data.fogs[0]",
      kind: "Fog AObj/FObj descriptor candidate",
      confidence: "medium",
      source: sourceAt(hsd, fogTableRel + 0x04),
      pointer: pointerField(hsd, fogTableRel, 0x04),
      note: "Paired pointer beside FogDesc entry; not decoded here.",
    });
  }

  return candidates.filter((candidate) => candidate.pointer.targetDataOffset !== null);
}

function scanPObjDrawState(hsd) {
  const pobjs = findPObjs(hsd);
  const flagCounts = new Map();
  const nDisplayCounts = new Map();
  for (const pobj of pobjs) {
    inc(flagCounts, pobj.flagsHex);
    inc(nDisplayCounts, String(pobj.displayListCount));
  }

  return {
    interpretation: "HSD_POBJ draw-state candidates found by confirmed VtxDescList + GX display-list signature.",
    confidence: "high",
    pobjCount: pobjs.length,
    flagCounts: mapToRecords(flagCounts, "flagsHex"),
    displayListCountHistogram: mapToRecords(nDisplayCounts, "displayListCount"),
    samples: pobjs.slice(0, 12),
  };
}

function findPObjs(hsd) {
  const pobjs = [];
  for (const fieldRel of hsd.relocs) {
    const vtxDescRel = readU32(hsd, fieldRel);
    const attrs = parseVtxDescList(hsd, vtxDescRel);
    if (!attrs.some((attr) => attr.attr === 9 && attr.arrayPointer?.targetDataOffset !== null)) continue;

    const pobjRel = fieldRel - 0x08;
    if (pobjRel < 0) continue;
    const dlFieldRel = pobjRel + 0x10;
    if (!hsd.relocSet.has(dlFieldRel)) continue;
    const displayListRel = readU32(hsd, dlFieldRel);
    const displayListOpcode = firstGxOpcode(hsd, displayListRel);
    if (displayListOpcode === null) continue;

    pobjs.push({
      dataOffset: hex(pobjRel),
      fileOffset: hex(relToFileOffset(hsd, pobjRel)),
      vtxDescList: {
        dataOffset: hex(vtxDescRel),
        fileOffset: hex(relToFileOffset(hsd, vtxDescRel)),
        attrs: attrs.map((attr) => ({
          attr: attr.attr,
          attrName: gxAttrName(attr.attr),
          attrType: attr.attrType,
          compCnt: attr.compCnt,
          compType: attr.compType,
          frac: attr.frac,
          stride: attr.stride,
          arrayPointer: attr.arrayPointer,
        })),
      },
      flags: readU16(hsd, pobjRel + 0x0c),
      flagsHex: hex(readU16(hsd, pobjRel + 0x0c), 4),
      displayListCount: readU16(hsd, pobjRel + 0x0e),
      displayList: {
        pointerFieldDataOffset: hex(dlFieldRel),
        dataOffset: hex(displayListRel),
        fileOffset: hex(relToFileOffset(hsd, displayListRel)),
        firstOpcode: hex(displayListOpcode, 2),
        firstOpcodeName: gxPrimitiveName(displayListOpcode),
      },
    });
  }
  return pobjs.sort((a, b) => parseHex(a.dataOffset) - parseHex(b.dataOffset));
}

function parseVtxDescList(hsd, relOffset) {
  if (!isRel(hsd, relOffset)) return [];
  const attrs = [];
  for (let i = 0; i < 32; i += 1) {
    const entryRel = relOffset + i * 0x18;
    if (entryRel + 0x18 > hsd.dataBlockSize) return [];
    const attr = readU32(hsd, entryRel);
    if (attr === 0xff) return attrs;
    if (attr > 0xff) return [];
    const attrType = readU32(hsd, entryRel + 0x04);
    const compCnt = readU32(hsd, entryRel + 0x08);
    const compType = readU32(hsd, entryRel + 0x0c);
    const frac = readU8(hsd, entryRel + 0x10);
    const stride = readU16(hsd, entryRel + 0x12);
    if (attrType > 3 || compType > 5 || stride > 0x100) return [];
    attrs.push({
      attr,
      attrType,
      compCnt,
      compType,
      frac,
      stride,
      arrayPointer: pointerField(hsd, entryRel, 0x14),
    });
  }
  return [];
}

function firstGxOpcode(hsd, relOffset) {
  if (!isRel(hsd, relOffset)) return null;
  for (let i = 0; i < 0x20; i += 1) {
    const opcode = hsd.buffer[relToFileOffset(hsd, relOffset) + i];
    if (opcode === 0) continue;
    return isGxPrimitive(opcode) ? opcode : null;
  }
  return null;
}

function scanExportedStageMaterials(stageId) {
  const stageModelDir = path.join(paths.browserStages, stageId, "model");
  if (!fs.existsSync(stageModelDir)) {
    return {
      source: rel(stageModelDir),
      status: "missing-exported-model-dir",
      materialCount: 0,
      note: "No exported browser DAE material evidence was available.",
      files: [],
      distinctValues: {},
    };
  }

  const daeFiles = fs
    .readdirSync(stageModelDir)
    .filter((name) => name.toLowerCase().endsWith(".dae"))
    .sort((a, b) => a.localeCompare(b))
    .map((name) => path.join(stageModelDir, name));

  const files = daeFiles.map((file) => parseDaeMaterials(file));
  const materialCount = files.reduce((sum, file) => sum + file.materials.length, 0);
  const allMaterials = files.flatMap((file) => file.materials.map((material) => ({ ...material, file: file.path })));

  return {
    source: rel(stageModelDir),
    status: daeFiles.length > 0 ? "exported-dae-present" : "missing-dae",
    confidence: daeFiles.length > 0 ? "medium" : "low",
    interpretation:
      "Collada material values exported from original HSD stage ARC; useful material-color evidence, but raw HSD MObj/PEDesc offsets remain unresolved.",
    daeFileCount: daeFiles.length,
    materialCount,
    distinctValues: {
      ambient: distinctMaterialValues(allMaterials, "ambient"),
      diffuseColors: distinctMaterialValues(allMaterials, "diffuseColor"),
      diffuseTextures: distinctMaterialValues(allMaterials, "diffuseTexture"),
      specular: distinctMaterialValues(allMaterials, "specular"),
      emission: distinctMaterialValues(allMaterials, "emission"),
      transparency: distinctMaterialValues(allMaterials, "transparency"),
    },
    files: files.slice(0, 12),
    sampleMaterials: allMaterials.slice(0, 20),
  };
}

function parseDaeMaterials(file) {
  const text = fs.readFileSync(file, "utf8");
  const effects = [...text.matchAll(/<effect\b[^>]*?id="([^"]+)"[\s\S]*?<\/effect>/g)].map((match) => {
    const body = match[0];
    return {
      id: match[1],
      emission: readDaeColor(body, "emission"),
      ambient: readDaeColor(body, "ambient"),
      diffuseColor: readDaeColor(body, "diffuse"),
      diffuseTexture: readDaeTexture(body, "diffuse"),
      specular: readDaeColor(body, "specular"),
      transparent: readDaeColor(body, "transparent"),
      transparency: readDaeFloat(body, "transparency"),
      shininess: readDaeFloat(body, "shininess"),
    };
  });

  return {
    path: rel(file),
    bytes: fs.statSync(file).size,
    materials: effects,
  };
}

function scanBrowserMain() {
  const text = fs.readFileSync(paths.browserMain, "utf8");
  const lines = text.split(/\r?\n/);
  const wanted = [
    "new THREE.PerspectiveCamera",
    "camera.position.set",
    "new THREE.HemisphereLight",
    "new THREE.DirectionalLight",
    "material.side = THREE.DoubleSide",
    "material.metalness = 0",
    "scene.background",
    "scene.fog",
  ];
  const matches = [];
  for (const [index, line] of lines.entries()) {
    for (const term of wanted) {
      if (line.includes(term)) {
        matches.push({
          line: index + 1,
          term,
          code: line.trim(),
        });
      }
    }
  }

  return {
    path: rel(paths.browserMain),
    status: "read-only; browser source was not edited",
    findings: matches,
    concise: [
      "PerspectiveCamera uses hard-coded fov/near/far and position.",
      "HemisphereLight and two DirectionalLight objects are hand-tuned browser lighting.",
      "Stage/player materials are forced DoubleSide and metalness=0.",
      text.includes("scene.fog") ? "Browser sets fog in main.ts." : "Browser main.ts has no scene.fog assignment.",
    ],
  };
}

function readRenderSymbols() {
  const text = fs.readFileSync(paths.symbolMap, "utf8");
  const wanted =
    /gnt4-(GXSetFog|GXSetFogRangeAdj|HSD_Fog|HSD_LObj|HSD_CObj|HSD_SetMaterial|HSD_StateSet|HSD_SetupRenderMode|HSD_SetupChannel|HSD_DisableChannelLighting)/;
  return text
    .split(/\r?\n/)
    .filter((line) => wanted.test(line))
    .map((line) => {
      const [address, size, runtimeAddress, unknown, ...nameParts] = line.trim().split(/\s+/);
      return {
        address: `0x${address}`,
        size: `0x${size}`,
        runtimeAddress: `0x${runtimeAddress}`,
        symbol: nameParts.join(" "),
      };
    });
}

function summarizeStages(stages) {
  const rootShape = new Map();
  const jobjCounts = new Map();
  for (const stage of stages) {
    inc(rootShape, `${stage.scene.scenePointers.length} scene pointers / root ${stage.scene.rootName}`);
    inc(jobjCounts, String(stage.scene.jobjDescCount));
  }

  const hasPattern = stages.filter(
    (stage) =>
      stage.scene.scenePointers.length === 4 &&
      stage.scene.scenePointers.every((pointer) => pointer.relocationMarked) &&
      stage.scene.cameras.length >= 1 &&
      stage.scene.lights.length >= 1 &&
      stage.scene.fogs.length >= 1,
  );

  return {
    stageArcCount: stages.length,
    sameScenePointerPatternCount: hasPattern.length,
    sameScenePointerPattern:
      hasPattern.length === stages.length
        ? "all scanned stage arcs expose 4 scene_data tables with camera/light/fog candidates"
        : "some scanned stage arcs differ; inspect per-stage records",
    rootShape: mapToRecords(rootShape, "shape"),
    jobjDescCountHistogram: mapToRecords(jobjCounts, "jobjDescCount"),
    st00ComparedToOthers:
      hasPattern.length === stages.length
        ? "st00 follows the same scene_data root pattern as the other scanned stage arcs."
        : "st00 has the expected pattern, but at least one other stage did not.",
  };
}

function buildRecommendations(st00) {
  const camera = st00.scene.cameras[0]?.decoded;
  const fog = st00.scene.fogs[0]?.decoded;
  const lights = st00.scene.lights.map((light) => light.decoded);

  return [
    {
      replaces: "THREE.PerspectiveCamera(48, aspect, 1, 80000) and camera.position.set(950, 520, 1320)",
      originalEvidence: camera
        ? `Use CObj fov ${camera.fovDegrees}, near ${camera.near}, far ${camera.far}, aspect ${camera.aspect}; eye ${vecText(camera.eye?.position)} and interest ${vecText(camera.interest?.position)} need runtime camera-override confirmation.`
        : "No CObj candidate decoded.",
      confidence: camera ? "high for load-time CObj, medium for gameplay camera replacement" : "low",
    },
    {
      replaces: "HemisphereLight and two DirectionalLight browser fakes",
      originalEvidence:
        lights.length > 0
          ? `Use HSD LObj descriptors: ${lights
              .map((light, index) => `L${index} ${light.role} ${light.colorRgbHex}`)
              .join("; ")}.`
          : "No LObj candidates decoded.",
      confidence: lights.length > 0 ? "high" : "low",
    },
    {
      replaces: "absence of scene fog in apps/game/src/main.ts",
      originalEvidence: fog
        ? `Use HSD FogDesc type ${fog.type}, start ${fog.start}, end ${fog.end}, color ${fog.colorRgbHex}.`
        : "No FogDesc candidate decoded.",
      confidence: fog ? "high" : "low",
    },
    {
      replaces: "material.side = THREE.DoubleSide and material.metalness = 0 blanket overrides",
      originalEvidence:
        "Use original HSD MObj/PEDesc cull/blend/Z/alpha/material fields after raw offsets are decoded; exported DAE material colors/textures are available now as medium-confidence material evidence.",
      confidence: "medium",
    },
  ];
}

function renderMarkdown(report) {
  const st00 = report.st00;
  const camera = st00.scene.cameras[0];
  const fog = st00.scene.fogs[0];
  const lines = [];

  lines.push("# Stage Lighting And Render State Inventory");
  lines.push("");
  lines.push(`Generated: \`${report.generatedAt}\``);
  lines.push(`Scanner: \`${report.scanner}\``);
  lines.push("");
  lines.push("## Inputs");
  lines.push("");
  lines.push(`- Disc root: \`${report.inputs.discRoot}\``);
  lines.push(`- Browser stages: \`${report.inputs.browserStages}\``);
  lines.push(`- Format specs: ${report.inputs.formatSpecs.map((item) => `\`${item}\``).join(", ")}`);
  lines.push(`- Symbol map: \`${report.inputs.symbolMap}\``);
  lines.push(`- Boot DOL: \`${report.inputs.bootDol.path}\` (${report.inputs.bootDol.bytes} bytes)`);
  lines.push("");
  lines.push("## Summary");
  lines.push("");
  lines.push(`- Stage ARC files scanned: ${report.summary.stageArcCount}`);
  lines.push(`- Same scene pointer pattern: ${report.summary.sameScenePointerPatternCount}/${report.summary.stageArcCount}`);
  lines.push(`- st00 JOBJDesc/model count: ${st00.scene.jobjDescCount}`);
  lines.push(`- st00 camera candidates: ${st00.scene.cameras.length}`);
  lines.push(`- st00 light candidates: ${st00.scene.lights.length}`);
  lines.push(`- st00 fog candidates: ${st00.scene.fogs.length}`);
  lines.push(`- st00 POBJ draw-state candidates: ${st00.drawState.pobjCount}`);
  lines.push(`- st00 exported DAE materials: ${st00.exportedMaterialState.materialCount}`);
  lines.push("");
  lines.push("## st00 Scene Evidence");
  lines.push("");
  lines.push(
    `\`${st00.sourcePath}\` root \`${st00.scene.rootName}\` is at data offset \`${st00.scene.rootDataOffset}\` / file offset \`${st00.scene.rootFileOffset}\`. Its four relocation-marked fields point to JOBJDesc, CObj, LObj, and Fog table candidates.`,
  );
  lines.push("");
  lines.push("| Field | Target data offset | Target file offset | Interpretation |");
  lines.push("|---:|---:|---:|---|");
  const fieldNames = ["JOBJDesc table", "CObj/camera table", "LObj/light table", "Fog table"];
  for (const [index, pointer] of st00.scene.scenePointers.entries()) {
    lines.push(
      `| ${index} | \`${pointer.targetDataOffset}\` | \`${pointer.targetFileOffset}\` | ${fieldNames[index]} |`,
    );
  }
  lines.push("");

  if (camera) {
    lines.push("## Camera");
    lines.push("");
    lines.push(`Source: \`${camera.source.path}\` data \`${camera.source.dataOffset}\` / file \`${camera.source.fileOffset}\`.`);
    lines.push("");
    lines.push("| Field | Value |");
    lines.push("|---|---:|");
    lines.push(`| Projection | ${camera.decoded.projection} |`);
    lines.push(`| Viewport/scissor | ${camera.raw.viewportWidth}x${camera.raw.viewportHeight} / ${camera.raw.scissorWidth}x${camera.raw.scissorHeight} |`);
    lines.push(`| Eye | ${md(vecText(camera.decoded.eye?.position))} |`);
    lines.push(`| Interest | ${md(vecText(camera.decoded.interest?.position))} |`);
    lines.push(`| Near | ${camera.decoded.near} |`);
    lines.push(`| Far | ${camera.decoded.far} |`);
    lines.push(`| FOV degrees | ${camera.decoded.fovDegrees} |`);
    lines.push(`| Aspect | ${camera.decoded.aspect} |`);
    lines.push("");
  }

  lines.push("## Lights");
  lines.push("");
  lines.push("| Index | Role | Flags | Color | Position | Source |");
  lines.push("|---:|---|---:|---|---|---|");
  for (const light of st00.scene.lights) {
    lines.push(
      `| ${light.index} | ${md(light.decoded.role)} | \`${light.raw.flags}\` | \`${light.decoded.colorRgbHex}\` ${md(JSON.stringify(light.decoded.colorRgba))} | ${md(vecText(light.decoded.position?.position))} | \`${light.source.dataOffset}\` / \`${light.source.fileOffset}\` |`,
    );
  }
  lines.push("");

  if (fog) {
    lines.push("## Fog");
    lines.push("");
    lines.push(`Source: \`${fog.source.path}\` data \`${fog.source.dataOffset}\` / file \`${fog.source.fileOffset}\`.`);
    lines.push("");
    lines.push("| Field | Value |");
    lines.push("|---|---:|");
    lines.push(`| Type | ${fog.decoded.type} |`);
    lines.push(`| Start | ${fog.decoded.start} |`);
    lines.push(`| End | ${fog.decoded.end} |`);
    lines.push(`| Color | \`${fog.decoded.colorRgbHex}\` ${md(JSON.stringify(fog.decoded.colorRgba))} |`);
    lines.push("");
  }

  lines.push("## Materials And Draw State");
  lines.push("");
  lines.push(
    `The scanner found ${st00.drawState.pobjCount} HSD_POBJ draw-state candidates in \`${st00.archiveName}\` by the confirmed VtxDescList + GX display-list signature. These include raw POBJ flags and display-list counts; raw MObj/PEDesc material offsets remain unresolved.`,
  );
  lines.push("");
  lines.push("| POBJ data | POBJ file | Flags | Display lists | First opcode |");
  lines.push("|---:|---:|---:|---:|---|");
  for (const sample of st00.drawState.samples.slice(0, 8)) {
    lines.push(
      `| \`${sample.dataOffset}\` | \`${sample.fileOffset}\` | \`${sample.flagsHex}\` | ${sample.displayListCount} | ${sample.displayList.firstOpcodeName} \`${sample.displayList.firstOpcode}\` |`,
    );
  }
  lines.push("");
  lines.push(
    `Exported Collada material evidence exists in \`${st00.exportedMaterialState.source}\`: ${st00.exportedMaterialState.daeFileCount} DAE files, ${st00.exportedMaterialState.materialCount} materials.`,
  );
  lines.push("");
  lines.push("- Distinct ambient values: " + renderDistinct(st00.exportedMaterialState.distinctValues.ambient));
  lines.push("- Distinct diffuse textures: " + renderDistinct(st00.exportedMaterialState.distinctValues.diffuseTextures));
  lines.push("- Distinct specular values: " + renderDistinct(st00.exportedMaterialState.distinctValues.specular));
  lines.push("- Distinct transparency values: " + renderDistinct(st00.exportedMaterialState.distinctValues.transparency));
  lines.push("");

  lines.push("## Browser Fakes To Replace");
  lines.push("");
  for (const item of report.browserCurrentFakes.concise) lines.push(`- ${item}`);
  lines.push("");
  lines.push("| Line | Code |");
  lines.push("|---:|---|");
  for (const finding of report.browserCurrentFakes.findings) {
    lines.push(`| ${finding.line} | \`${md(finding.code)}\` |`);
  }
  lines.push("");

  lines.push("## Replacement Targets");
  lines.push("");
  for (const recommendation of report.recommendations) {
    lines.push(`- Replace \`${recommendation.replaces}\`: ${recommendation.originalEvidence} Confidence: ${recommendation.confidence}.`);
  }
  lines.push("");

  lines.push("## Other Stage Pattern");
  lines.push("");
  lines.push(report.summary.st00ComparedToOthers);
  lines.push("");
  lines.push("| Stage | JOBJDesc | Cameras | Lights | Fogs | POBJ | DAE materials |");
  lines.push("|---|---:|---:|---:|---:|---:|---:|");
  for (const stage of report.stages) {
    lines.push(
      `| \`${stage.stageId}\` | ${stage.scene.jobjDescCount} | ${stage.scene.cameras.length} | ${stage.scene.lights.length} | ${stage.scene.fogs.length} | ${stage.drawState.pobjCount} | ${stage.exportedMaterialState.materialCount} |`,
    );
  }
  lines.push("");

  lines.push("## Runtime Symbols");
  lines.push("");
  lines.push("Relevant render-state symbols in the map:");
  lines.push("");
  for (const symbol of report.symbols.slice(0, 40)) {
    lines.push(`- \`${symbol.address}\` size \`${symbol.size}\` ${symbol.symbol}`);
  }
  if (report.symbols.length > 40) lines.push(`- ... ${report.symbols.length - 40} more entries in JSON.`);
  lines.push("");

  lines.push("## Unresolved Questions");
  lines.push("");
  for (const question of report.unresolvedQuestions) lines.push(`- ${question}`);
  lines.push("");

  return `${lines.join("\n")}\n`;
}

function readHsdDat(file) {
  const buffer = fs.readFileSync(file);
  if (buffer.length < 0x20) fail(`too small for HSD DAT: ${rel(file)}`);

  let base = 0;
  let container = "bare HSD DAT";
  if (buffer.length >= 0x120 && buffer.readUInt32BE(0) === 0x100 && buffer.readUInt32BE(0x100) === buffer.length - 0x100) {
    base = 0x100;
    container = "wrapped HSD DAT";
  }

  const fileSize = buffer.readUInt32BE(base);
  const dataBlockSize = buffer.readUInt32BE(base + 4);
  const relocCount = buffer.readUInt32BE(base + 8);
  const rootCount = buffer.readUInt32BE(base + 0x0c);
  const externalRefCount = buffer.readUInt32BE(base + 0x10);
  const dataOffset = base + 0x20;
  const relocTableOffset = dataOffset + dataBlockSize;
  const rootTableOffset = relocTableOffset + relocCount * 4;
  const externalRefTableOffset = rootTableOffset + rootCount * 8;
  const symbolTableOffset = externalRefTableOffset + externalRefCount * 8;

  if (base + fileSize > buffer.length) fail(`HSD fileSize exceeds file size: ${rel(file)}`);
  if (symbolTableOffset > buffer.length) fail(`HSD tables exceed file size: ${rel(file)}`);

  const relocs = [];
  for (let i = 0; i < relocCount; i += 1) relocs.push(buffer.readUInt32BE(relocTableOffset + i * 4));

  const roots = [];
  for (let i = 0; i < rootCount; i += 1) {
    const data = buffer.readUInt32BE(rootTableOffset + i * 8);
    const stringOffset = buffer.readUInt32BE(rootTableOffset + i * 8 + 4);
    const stringStart = symbolTableOffset + stringOffset;
    const stringEnd = buffer.indexOf(0, stringStart);
    roots.push({
      dataOffset: data,
      name: buffer.slice(stringStart, stringEnd === -1 ? stringStart : stringEnd).toString("ascii"),
    });
  }

  return {
    file,
    buffer,
    base,
    container,
    fileSize,
    dataBlockSize,
    relocCount,
    rootCount,
    externalRefCount,
    dataOffset,
    relocTableOffset,
    rootTableOffset,
    symbolTableOffset,
    relocs,
    relocSet: new Set(relocs),
    roots,
  };
}

function parseWObj(hsd, relOffset) {
  if (!isRel(hsd, relOffset)) return null;
  return {
    source: sourceAt(hsd, relOffset),
    flags: hex(readU32(hsd, relOffset)),
    position: [round(readF32(hsd, relOffset + 0x04)), round(readF32(hsd, relOffset + 0x08)), round(readF32(hsd, relOffset + 0x0c))],
  };
}

function pointerField(hsd, structRel, fieldOffset) {
  const fieldRel = structRel + fieldOffset;
  if (!isRel(hsd, fieldRel) || !hsd.relocSet.has(fieldRel)) {
    return {
      fieldDataOffset: hex(fieldRel),
      fieldFileOffset: hex(relToFileOffset(hsd, fieldRel)),
      relocationMarked: false,
      targetDataOffset: null,
      targetDataOffsetRaw: null,
      targetFileOffset: null,
    };
  }
  const targetRel = readU32(hsd, fieldRel);
  return {
    fieldDataOffset: hex(fieldRel),
    fieldFileOffset: hex(relToFileOffset(hsd, fieldRel)),
    relocationMarked: true,
    targetDataOffset: hex(targetRel),
    targetDataOffsetRaw: targetRel,
    targetFileOffset: hex(relToFileOffset(hsd, targetRel)),
  };
}

function sourceAt(hsd, relOffset) {
  return {
    path: rel(hsd.file),
    archiveName: path.basename(hsd.file),
    dataOffset: hex(relOffset),
    fileOffset: hex(relToFileOffset(hsd, relOffset)),
  };
}

function readColor(hsd, relOffset) {
  const value = readU32(hsd, relOffset);
  const rgba = [(value >>> 24) & 0xff, (value >>> 16) & 0xff, (value >>> 8) & 0xff, value & 0xff];
  return {
    rawHex: hex(value, 8),
    rgba,
    rgbHex: `#${rgba
      .slice(0, 3)
      .map((part) => part.toString(16).padStart(2, "0"))
      .join("")}`,
    normalized: rgba.map((part) => round(part / 255)),
  };
}

function readDaeColor(body, tag) {
  const match = new RegExp(`<${tag}>[\\s\\S]*?<color\\b[^>]*>([^<]+)</color>[\\s\\S]*?</${tag}>`).exec(body);
  return match ? normalizeSpaces(match[1]) : null;
}

function readDaeTexture(body, tag) {
  const match = new RegExp(`<${tag}>[\\s\\S]*?<texture\\b[^>]*texture="([^"]+)"`).exec(body);
  return match ? match[1] : null;
}

function readDaeFloat(body, tag) {
  const match = new RegExp(`<${tag}>[\\s\\S]*?<float\\b[^>]*>([^<]+)</float>[\\s\\S]*?</${tag}>`).exec(body);
  return match ? Number(match[1]) : null;
}

function distinctMaterialValues(materials, key) {
  const counts = new Map();
  for (const material of materials) {
    const value = material[key];
    if (value === null || value === undefined || value === "") continue;
    inc(counts, String(value));
  }
  return mapToRecords(counts, "value").slice(0, 24);
}

function inferLightRole(flags, positionRel) {
  if (positionRel === null && (flags & 0x00040000) !== 0) return "ambient/global color candidate";
  if (positionRel !== null && (flags & 0x000d0000) !== 0) return "positioned diffuse/specular light candidate";
  if (positionRel !== null) return "positioned light candidate";
  return "light candidate";
}

function readU32(hsd, relOffset) {
  return hsd.buffer.readUInt32BE(relToFileOffset(hsd, relOffset));
}

function readU16(hsd, relOffset) {
  return hsd.buffer.readUInt16BE(relToFileOffset(hsd, relOffset));
}

function readU8(hsd, relOffset) {
  return hsd.buffer[relToFileOffset(hsd, relOffset)];
}

function readF32(hsd, relOffset) {
  return hsd.buffer.readFloatBE(relToFileOffset(hsd, relOffset));
}

function relToFileOffset(hsd, relOffset) {
  return hsd.dataOffset + relOffset;
}

function isRel(hsd, relOffset) {
  return Number.isInteger(relOffset) && relOffset >= 0 && relOffset + 4 <= hsd.dataBlockSize;
}

function isGxPrimitive(opcode) {
  return [0x80, 0x90, 0x98, 0xa0, 0xa8, 0xb0, 0xb8].includes(opcode);
}

function gxPrimitiveName(opcode) {
  return (
    {
      0x80: "GX_QUADS",
      0x90: "GX_TRIANGLES",
      0x98: "GX_TRIANGLESTRIP",
      0xa0: "GX_TRIANGLEFAN",
      0xa8: "GX_LINES",
      0xb0: "GX_LINESTRIP",
      0xb8: "GX_POINTS",
    }[opcode] ?? "unknown"
  );
}

function gxAttrName(attr) {
  return (
    {
      0: "PNMTXIDX",
      9: "POS",
      10: "NRM",
      11: "CLR0",
      12: "CLR1",
      13: "TEX0",
      14: "TEX1",
      0xff: "NULL",
    }[attr] ?? `ATTR_${attr}`
  );
}

function mapToRecords(map, keyName) {
  return [...map.entries()]
    .map(([key, count]) => ({ [keyName]: key, count }))
    .sort((a, b) => b.count - a.count || String(a[keyName]).localeCompare(String(b[keyName])));
}

function inc(map, key) {
  map.set(key, (map.get(key) ?? 0) + 1);
}

function renderDistinct(records) {
  if (!records || records.length === 0) return "none";
  return records
    .slice(0, 8)
    .map((record) => `\`${record.value}\` (${record.count})`)
    .join(", ");
}

function vecText(vec) {
  return Array.isArray(vec) ? `[${vec.join(", ")}]` : "not present";
}

function normalizeSpaces(value) {
  return value.trim().replace(/\s+/g, " ");
}

function round(value) {
  return Number.isFinite(value) ? Number(value.toFixed(6)) : value;
}

function parseHex(value) {
  return Number.parseInt(String(value).replace(/^0x/, ""), 16);
}

function hex(value, width = 0) {
  if (value === null || value === undefined) return null;
  return `0x${Number(value).toString(16).padStart(width, "0")}`;
}

function fileInfo(file) {
  return {
    path: rel(file),
    bytes: fs.statSync(file).size,
  };
}

function writeJson(file, value) {
  fs.writeFileSync(`${file}.tmp`, `${JSON.stringify(value, null, 2)}\n`, "utf8");
  fs.renameSync(`${file}.tmp`, file);
}

function rel(file) {
  return path.relative(repoRoot, file).replaceAll(path.sep, "/");
}

function md(value) {
  return String(value ?? "").replaceAll("|", "\\|");
}

function mustExist(file) {
  if (!fs.existsSync(file)) fail(`missing input: ${rel(file)}`);
}

function fail(message) {
  console.error(`inventory-stage-lighting: ${message}`);
  process.exit(1);
}
