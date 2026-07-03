#!/usr/bin/env node
// Convert runtime Collada exports to the production browser model format: GLB.
//
// The HSDRaw/IONET exporter emits DAE. The live browser path must not load DAE
// directly; this script converts every checked runtime DAE under apps/game/public
// into an adjacent GLB and validates the result.

import fs from "node:fs";
import path from "node:path";
import { fileURLToPath, pathToFileURL } from "node:url";

import { createCanvas, Image, ImageData } from "@napi-rs/canvas";
import { DOMParser } from "@xmldom/xmldom";
import * as THREE from "three";
import { GLTFExporter } from "three/examples/jsm/exporters/GLTFExporter.js";
import { ColladaLoader } from "three/examples/jsm/loaders/ColladaLoader.js";
import { validateBytes } from "gltf-validator";

const repoRoot = process.cwd();
const roots = parseRoots(process.argv.slice(2));
installNodeDomForThree();

const ACCESSOR_COMPONENTS = {
  SCALAR: 1,
  VEC2: 2,
  VEC3: 3,
  VEC4: 4,
  MAT2: 4,
  MAT3: 9,
  MAT4: 16,
};

let converted = 0;
let skipped = 0;
const failures = [];

for (const root of roots) {
  for (const daePath of walkDaeFiles(path.resolve(repoRoot, root))) {
    const glbPath = daePath.replace(/\.dae$/i, ".glb");
    try {
      if (isUpToDate(daePath, glbPath)) {
        skipped += 1;
        continue;
      }
      await convertDaeToGlb(daePath, glbPath);
      converted += 1;
      console.log(`GLB ${rel(glbPath)}`);
    } catch (error) {
      failures.push(`${rel(daePath)}: ${error instanceof Error ? error.message : String(error)}`);
    }
  }
}

if (failures.length > 0) {
  console.error(`failed to convert ${failures.length} DAE file(s):`);
  for (const failure of failures.slice(0, 25)) console.error(`  ${failure}`);
  if (failures.length > 25) console.error(`  ... ${failures.length - 25} more`);
  process.exit(1);
}

console.log(`runtime GLB conversion complete: ${converted} converted, ${skipped} up to date`);

function parseRoots(args) {
  if (args.length === 0) {
    return [
      path.join("apps", "game", "public", "models"),
      path.join("apps", "game", "public", "stages"),
      path.join("apps", "game", "public", "ui", "scenes"),
    ];
  }
  return args;
}

async function convertDaeToGlb(daePath, glbPath) {
  const manager = new THREE.LoadingManager();
  let started = false;
  const loaded = new Promise((resolve, reject) => {
    manager.onStart = () => {
      started = true;
    };
    manager.onLoad = resolve;
    manager.onError = (url) => reject(new Error(`failed to load linked asset ${url}`));
  });

  const loader = new ColladaLoader(manager);
  const baseUrl = pathToFileURL(path.dirname(daePath) + path.sep).href;
  const daeText = fs.readFileSync(daePath, "utf8").replace(/^\uFEFF/, "").trimStart();
  const parsed = await withFilteredThreeLogs(() => loader.parse(daeText, baseUrl));
  if (started) await loaded;
  sanitizeSceneForGltf(parsed.scene);
  const skinSkeletonRoots = collectSkinSkeletonRoots(parsed.scene);

  const exporter = new GLTFExporter();
  const output = await withFilteredThreeLogs(() =>
    exporter.parseAsync(parsed.scene, {
      binary: true,
      trs: true,
      animations: parsed.scene.animations ?? [],
    }),
  );
  const glb = patchGlbJson(Buffer.from(output), skinSkeletonRoots);
  await validateGlb(glb, daePath);

  fs.writeFileSync(`${glbPath}.tmp`, glb);
  fs.renameSync(`${glbPath}.tmp`, glbPath);
}

function sanitizeSceneForGltf(scene) {
  scene.traverse((object) => {
    sanitizeVector(object.position, 0);
    sanitizeQuaternion(object.quaternion);
    sanitizeVector(object.scale, 1);
    sanitizeMatrix(object.matrix);
    sanitizeMatrix(object.matrixWorld);
    object.updateMatrix();

    if (object instanceof THREE.SkinnedMesh) {
      for (const inverse of object.skeleton.boneInverses) sanitizeMatrix(inverse);
    }
  });
}

function sanitizeVector(vector, fallback) {
  for (const key of ["x", "y", "z"]) {
    if (!Number.isFinite(vector[key])) vector[key] = fallback;
  }
}

function sanitizeQuaternion(quaternion) {
  if (
    Number.isFinite(quaternion.x) &&
    Number.isFinite(quaternion.y) &&
    Number.isFinite(quaternion.z) &&
    Number.isFinite(quaternion.w)
  ) {
    return;
  }
  quaternion.identity();
}

function sanitizeMatrix(matrix) {
  const elements = matrix.elements;
  for (let i = 0; i < elements.length; i += 1) {
    if (!Number.isFinite(elements[i])) elements[i] = i % 5 === 0 ? 1 : 0;
  }
  elements[3] = 0;
  elements[7] = 0;
  elements[11] = 0;
  elements[15] = 1;
}

async function withFilteredThreeLogs(fn) {
  const originalLog = console.log;
  const originalWarn = console.warn;
  const filter = (write) =>
    (...args) => {
      const first = String(args[0] ?? "");
      if (
        first.startsWith("THREE.ColladaLoader: File version") ||
        first.startsWith("GLTFExporter: Use MeshStandardMaterial") ||
        first.startsWith('GLTFExporter: Attribute "skinIndex"')
      ) {
        return;
      }
      write(...args);
    };
  console.log = filter(originalLog);
  console.warn = filter(originalWarn);
  try {
    return await fn();
  } finally {
    console.log = originalLog;
    console.warn = originalWarn;
  }
}

function collectSkinSkeletonRoots(scene) {
  const roots = [];
  scene.updateMatrixWorld(true);
  scene.traverse((object) => {
    if (!(object instanceof THREE.SkinnedMesh) || !object.skeleton?.bones?.length) return;
    const commonRoot = commonAncestorOfNodes(object.skeleton.bones);
    if (!commonRoot?.name || !object.name) return;
    roots.push({ meshName: object.name, rootName: commonRoot.name });
  });
  return roots;
}

function commonAncestorOfNodes(nodes) {
  let common = nodes[0] ?? null;
  for (const node of nodes) {
    common = commonAncestor(common, node);
    if (!common) return null;
  }
  return common;
}

function commonAncestor(left, right) {
  const leftAncestors = new Set();
  for (let node = left; node; node = node.parent) leftAncestors.add(node);
  for (let node = right; node; node = node.parent) {
    if (leftAncestors.has(node)) return node;
  }
  return null;
}

function patchGlbJson(glb, roots) {
  if (glb.readUInt32LE(0) !== 0x46546c67) return glb;

  const chunks = readGlbChunks(glb);
  const jsonChunk = chunks[0];
  if (!jsonChunk || jsonChunk.type !== 0x4e4f534a) return glb;

  const json = JSON.parse(jsonChunk.data.toString("utf8").trimEnd());
  if (!Array.isArray(json.nodes)) json.nodes = [];

  const nodeByName = new Map();
  for (let i = 0; i < json.nodes.length; i += 1) {
    const name = json.nodes[i]?.name;
    if (typeof name === "string" && !nodeByName.has(name)) nodeByName.set(name, i);
  }

  let changed = sanitizeJson(json);
  changed = sanitizeBinaryAccessors(json, chunks.slice(1)) || changed;
  if (Array.isArray(json.skins)) {
    for (const root of roots) {
      const rootIndex = nodeByName.get(root.rootName);
      if (rootIndex === undefined) continue;
      for (let nodeIndex = 0; nodeIndex < json.nodes.length; nodeIndex += 1) {
        const node = json.nodes[nodeIndex];
        if (node?.name !== root.meshName || !Number.isInteger(node.skin)) continue;
        const skin = json.skins[node.skin];
        if (!skin || skin.skeleton === rootIndex) continue;
        skin.skeleton = rootIndex;
        changed = true;
      }
    }
  }

  return changed ? writeGlbChunks(json, chunks.slice(1)) : glb;
}

function sanitizeBinaryAccessors(json, dataChunks) {
  if (!Array.isArray(json.accessors) || !Array.isArray(json.bufferViews)) return false;
  const binChunks = dataChunks.filter((chunk) => chunk.type === 0x004e4942);
  const normalAccessors = meshAttributeAccessors(json, "NORMAL");
  let changed = false;

  for (let accessorIndex = 0; accessorIndex < json.accessors.length; accessorIndex += 1) {
    const accessor = json.accessors[accessorIndex];
    if (accessor?.componentType !== 5126 || !Number.isInteger(accessor.bufferView)) continue;
    const bufferView = json.bufferViews[accessor.bufferView];
    const bin = binChunks[bufferView?.buffer ?? 0]?.data;
    const components = ACCESSOR_COMPONENTS[accessor.type] ?? 0;
    if (!bufferView || !bin || components <= 0 || !Number.isInteger(accessor.count)) continue;

    const componentSize = 4;
    const stride = bufferView.byteStride ?? components * componentSize;
    const baseOffset = (bufferView.byteOffset ?? 0) + (accessor.byteOffset ?? 0);
    let accessorChanged = false;

    for (let element = 0; element < accessor.count; element += 1) {
      const elementOffset = baseOffset + element * stride;
      if (normalAccessors.has(accessorIndex) && components === 3) {
        accessorChanged = sanitizeNormal(bin, elementOffset) || accessorChanged;
        continue;
      }
      for (let component = 0; component < components; component += 1) {
        const offset = elementOffset + component * componentSize;
        if (offset + componentSize > bin.length) continue;
        const value = bin.readFloatLE(offset);
        const canonical = canonicalAccessorValue(accessor.type, component, value);
        if (Object.is(value, canonical)) continue;
        bin.writeFloatLE(canonical, offset);
        accessorChanged = true;
      }
    }

    if (accessorChanged) {
      delete accessor.min;
      delete accessor.max;
      changed = true;
    }
  }

  return changed;
}

function meshAttributeAccessors(json, semantic) {
  const accessors = new Set();
  for (const mesh of json.meshes ?? []) {
    for (const primitive of mesh.primitives ?? []) {
      const accessor = primitive.attributes?.[semantic];
      if (Number.isInteger(accessor)) accessors.add(accessor);
    }
  }
  return accessors;
}

function sanitizeNormal(bin, offset) {
  if (offset + 12 > bin.length) return false;
  let x = bin.readFloatLE(offset);
  let y = bin.readFloatLE(offset + 4);
  let z = bin.readFloatLE(offset + 8);
  if (!Number.isFinite(x)) x = 0;
  if (!Number.isFinite(y)) y = 0;
  if (!Number.isFinite(z)) z = 0;
  const length = Math.hypot(x, y, z);
  if (length < 1e-8) {
    bin.writeFloatLE(0, offset);
    bin.writeFloatLE(1, offset + 4);
    bin.writeFloatLE(0, offset + 8);
    return true;
  }
  const nx = x / length;
  const ny = y / length;
  const nz = z / length;
  if (Math.abs(nx - x) < 1e-6 && Math.abs(ny - y) < 1e-6 && Math.abs(nz - z) < 1e-6) return false;
  bin.writeFloatLE(nx, offset);
  bin.writeFloatLE(ny, offset + 4);
  bin.writeFloatLE(nz, offset + 8);
  return true;
}

function canonicalAccessorValue(type, component, value) {
  if (!Number.isFinite(value)) return 0;
  if (type === "MAT4") {
    if (component === 3 || component === 7 || component === 11) return 0;
    if (component === 15) return 1;
  }
  return value;
}

function sanitizeJson(value) {
  let changed = false;
  if (Array.isArray(value)) {
    for (let i = 0; i < value.length; i += 1) {
      if (value[i] === null) {
        value[i] = 0;
        changed = true;
      } else {
        changed = sanitizeJson(value[i]) || changed;
      }
    }
    return changed;
  }
  if (!value || typeof value !== "object") return false;
  for (const [key, child] of Object.entries(value)) {
    if (child === null) {
      delete value[key];
      changed = true;
    } else {
      changed = sanitizeJson(child) || changed;
    }
  }
  return changed;
}

function readGlbChunks(glb) {
  const chunks = [];
  for (let offset = 12; offset + 8 <= glb.length;) {
    const length = glb.readUInt32LE(offset);
    const type = glb.readUInt32LE(offset + 4);
    const start = offset + 8;
    const end = start + length;
    chunks.push({ type, data: glb.subarray(start, end) });
    offset = end;
  }
  return chunks;
}

function writeGlbChunks(json, chunks) {
  const jsonData = paddedBuffer(Buffer.from(JSON.stringify(json)), 0x20);
  const chunkBuffers = [
    writeGlbChunk(0x4e4f534a, jsonData),
    ...chunks.map((chunk) => writeGlbChunk(chunk.type, chunk.data)),
  ];
  const totalLength = 12 + chunkBuffers.reduce((sum, chunk) => sum + chunk.length, 0);
  const header = Buffer.alloc(12);
  header.writeUInt32LE(0x46546c67, 0);
  header.writeUInt32LE(2, 4);
  header.writeUInt32LE(totalLength, 8);
  return Buffer.concat([header, ...chunkBuffers], totalLength);
}

function writeGlbChunk(type, data) {
  const header = Buffer.alloc(8);
  header.writeUInt32LE(data.length, 0);
  header.writeUInt32LE(type, 4);
  return Buffer.concat([header, data], header.length + data.length);
}

function paddedBuffer(buffer, padByte) {
  const paddedLength = (buffer.length + 3) & ~3;
  if (paddedLength === buffer.length) return buffer;
  return Buffer.concat([buffer, Buffer.alloc(paddedLength - buffer.length, padByte)], paddedLength);
}

async function validateGlb(glb, sourcePath) {
  const report = await validateBytes(new Uint8Array(glb));
  if (report.issues.numErrors > 0) {
    const messages = report.issues.messages
      .filter((message) => message.severity === 0)
      .slice(0, 5)
      .map((message) => `${message.code ?? "GLTF_ERROR"}${message.pointer ? ` ${message.pointer}` : ""}: ${message.message}`)
      .join("; ");
    throw new Error(`invalid GLB from ${rel(sourcePath)}: ${messages || `${report.issues.numErrors} error(s)`}`);
  }
}

function isUpToDate(source, dest) {
  if (!fs.existsSync(dest)) return false;
  return fs.statSync(dest).mtimeMs >= fs.statSync(source).mtimeMs;
}

function* walkDaeFiles(root) {
  if (!fs.existsSync(root)) return;
  for (const entry of fs.readdirSync(root, { withFileTypes: true }).sort((a, b) => a.name.localeCompare(b.name))) {
    const full = path.join(root, entry.name);
    if (entry.isDirectory()) {
      yield* walkDaeFiles(full);
    } else if (entry.isFile() && entry.name.toLowerCase().endsWith(".dae")) {
      yield full;
    }
  }
}

function installNodeDomForThree() {
  class NodeImage extends Image {
    #listeners = new Map();

    addEventListener(type, fn) {
      const list = this.#listeners.get(type) ?? [];
      list.push(fn);
      this.#listeners.set(type, list);
    }

    removeEventListener(type, fn) {
      const list = this.#listeners.get(type) ?? [];
      this.#listeners.set(
        type,
        list.filter((listener) => listener !== fn),
      );
    }

    dispatch(type, event = {}) {
      for (const fn of this.#listeners.get(type) ?? []) fn.call(this, event);
    }

    set src(value) {
      try {
        if (String(value).startsWith("data:")) {
          super.src = value;
        } else {
          const filePath = String(value).startsWith("file:") ? fileURLToPath(String(value)) : String(value);
          super.src = fs.readFileSync(filePath);
        }
        queueMicrotask(() => this.dispatch("load"));
      } catch (error) {
        queueMicrotask(() => this.dispatch("error", error));
      }
    }

    get src() {
      return "";
    }
  }

  class NodeFileReader {
    result = null;
    onload = null;
    onloadend = null;

    addEventListener(type, fn) {
      this[`on${type}`] = fn;
    }

    async readAsArrayBuffer(blob) {
      this.result = await blob.arrayBuffer();
      this.onloadend?.({ target: this });
      this.onload?.({ target: this });
    }

    async readAsDataURL(blob) {
      const bytes = Buffer.from(await blob.arrayBuffer());
      this.result = `data:${blob.type};base64,${bytes.toString("base64")}`;
      this.onloadend?.({ target: this });
      this.onload?.({ target: this });
    }
  }

  const CanvasClass = createCanvas(1, 1).constructor;

  globalThis.DOMParser = DOMParser;
  globalThis.FileReader = NodeFileReader;
  globalThis.HTMLCanvasElement = CanvasClass;
  globalThis.HTMLImageElement = NodeImage;
  globalThis.ImageData = ImageData;
  globalThis.document = {
    createElement(name) {
      return createNodeElement(name, NodeImage);
    },
    createElementNS(_namespace, name) {
      return createNodeElement(name, NodeImage);
    },
  };
}

function createNodeElement(name, NodeImage) {
  if (name === "canvas") return createCanvas(1, 1);
  if (name === "img") return new NodeImage();
  throw new Error(`unsupported DOM element requested during GLB conversion: ${name}`);
}

function rel(file) {
  return path.relative(repoRoot, file).replaceAll("\\", "/");
}
