#!/usr/bin/env node

import { createCanvas } from "@napi-rs/canvas";
import fs from "node:fs";
import path from "node:path";
import * as THREE from "three";

const root = path.resolve(import.meta.dirname, "..");
const modelDir = path.join(root, "apps/game/public/stages/stff/model");
const output = path.join(root, "research/decomp/data/title-prop-contact-sheet.png");
const modelIds = [47, 48, 49, 50, 51, 52, 53, 54, 55, 65];

function parseGlb(file) {
  const data = fs.readFileSync(file);
  if (data.readUInt32LE(0) !== 0x46546c67 || data.readUInt32LE(4) !== 2) {
    throw new Error(`${file} is not a GLB 2.0 file`);
  }
  let json;
  let bin;
  for (let off = 12; off < data.length; ) {
    const length = data.readUInt32LE(off);
    const type = data.readUInt32LE(off + 4);
    const chunk = data.subarray(off + 8, off + 8 + length);
    if (type === 0x4e4f534a) json = JSON.parse(chunk.toString("utf8").replace(/\0+$/u, ""));
    if (type === 0x004e4942) bin = chunk;
    off += 8 + length;
  }
  if (!json || !bin) throw new Error(`${file} has no JSON/BIN chunks`);
  return { json, bin };
}

function accessorValues(glb, accessorIndex) {
  const accessor = glb.json.accessors[accessorIndex];
  const view = glb.json.bufferViews[accessor.bufferView];
  const components = { SCALAR: 1, VEC2: 2, VEC3: 3, VEC4: 4 }[accessor.type];
  const bytes = { 5121: 1, 5123: 2, 5125: 4, 5126: 4 }[accessor.componentType];
  if (!components || !bytes) throw new Error(`unsupported accessor ${accessor.componentType}/${accessor.type}`);
  const stride = view.byteStride ?? components * bytes;
  const base = (view.byteOffset ?? 0) + (accessor.byteOffset ?? 0);
  const values = [];
  for (let row = 0; row < accessor.count; row += 1) {
    const entry = [];
    for (let component = 0; component < components; component += 1) {
      const off = base + row * stride + component * bytes;
      if (accessor.componentType === 5121) entry.push(glb.bin.readUInt8(off));
      if (accessor.componentType === 5123) entry.push(glb.bin.readUInt16LE(off));
      if (accessor.componentType === 5125) entry.push(glb.bin.readUInt32LE(off));
      if (accessor.componentType === 5126) entry.push(glb.bin.readFloatLE(off));
    }
    values.push(entry);
  }
  return values;
}

function nodeMatrix(node) {
  if (node.matrix) return new THREE.Matrix4().fromArray(node.matrix);
  const position = new THREE.Vector3().fromArray(node.translation ?? [0, 0, 0]);
  const quaternion = new THREE.Quaternion().fromArray(node.rotation ?? [0, 0, 0, 1]);
  const scale = new THREE.Vector3().fromArray(node.scale ?? [1, 1, 1]);
  return new THREE.Matrix4().compose(position, quaternion, scale);
}

function readTriangles(file) {
  const glb = parseGlb(file);
  const triangles = [];
  const scene = glb.json.scenes[glb.json.scene ?? 0];
  const visit = (nodeIndex, parentMatrix) => {
    const node = glb.json.nodes[nodeIndex];
    const world = parentMatrix.clone().multiply(nodeMatrix(node));
    if (node.mesh !== undefined) {
      for (const primitive of glb.json.meshes[node.mesh].primitives) {
        if ((primitive.mode ?? 4) !== 4 || primitive.attributes.POSITION === undefined) continue;
        const positions = accessorValues(glb, primitive.attributes.POSITION).map(([x, y, z]) =>
          new THREE.Vector3(x, y, z).applyMatrix4(world),
        );
        const indices = primitive.indices === undefined
          ? positions.map((_, index) => index)
          : accessorValues(glb, primitive.indices).map(([index]) => index);
        for (let i = 0; i + 2 < indices.length; i += 3) {
          triangles.push([positions[indices[i]], positions[indices[i + 1]], positions[indices[i + 2]]]);
        }
      }
    }
    for (const child of node.children ?? []) visit(child, world);
  };
  for (const node of scene.nodes ?? []) visit(node, new THREE.Matrix4());
  return {
    triangles,
    roots: (scene.nodes ?? []).map((index) => ({ index, node: glb.json.nodes[index] })),
    transforms: glb.json.nodes
      .map((node, index) => ({ index, name: node.name, translation: node.translation, rotation: node.rotation, scale: node.scale }))
      .filter((node) => node.translation || node.rotation || node.scale),
  };
}

const cellWidth = 360;
const cellHeight = 260;
const views = [
  { label: "XY", axes: ["x", "y", "z"] },
  { label: "XZ", axes: ["x", "z", "y"] },
  { label: "ZY", axes: ["z", "y", "x"] },
];
const canvas = createCanvas(cellWidth * views.length, cellHeight * modelIds.length);
const ctx = canvas.getContext("2d");
ctx.fillStyle = "#f4f0e8";
ctx.fillRect(0, 0, canvas.width, canvas.height);
ctx.font = "bold 18px sans-serif";
ctx.lineJoin = "round";

for (let row = 0; row < modelIds.length; row += 1) {
  const id = modelIds[row];
  const parsed = readTriangles(path.join(modelDir, `model_${String(id).padStart(2, "0")}.glb`));
  const triangles = parsed.triangles;
  const bounds = new THREE.Box3();
  for (const point of triangles.flat()) bounds.expandByPoint(point);
  const center = bounds.getCenter(new THREE.Vector3());
  const size = bounds.getSize(new THREE.Vector3());
  console.log(JSON.stringify({ id, triangles: triangles.length, center: center.toArray(), size: size.toArray(), roots: parsed.roots, transforms: parsed.transforms }));
  for (let column = 0; column < views.length; column += 1) {
    const { label, axes } = views[column];
    const ox = column * cellWidth;
    const oy = row * cellHeight;
    ctx.strokeStyle = "#b8afa0";
    ctx.strokeRect(ox + 0.5, oy + 0.5, cellWidth - 1, cellHeight - 1);
    ctx.fillStyle = "#241f1a";
    ctx.fillText(`stff model ${id} · ${label} · ${triangles.length} tris`, ox + 12, oy + 24);
    if (triangles.length === 0) continue;
    const points = triangles.flat();
    const us = points.map((point) => point[axes[0]]);
    const vs = points.map((point) => point[axes[1]]);
    const ds = points.map((point) => point[axes[2]]);
    const minU = Math.min(...us), maxU = Math.max(...us);
    const minV = Math.min(...vs), maxV = Math.max(...vs);
    const minD = Math.min(...ds), maxD = Math.max(...ds);
    const scale = Math.min((cellWidth - 28) / Math.max(1, maxU - minU), (cellHeight - 52) / Math.max(1, maxV - minV));
    const project = (point) => [
      ox + cellWidth / 2 + (point[axes[0]] - (minU + maxU) / 2) * scale,
      oy + 36 + (cellHeight - 44) / 2 - (point[axes[1]] - (minV + maxV) / 2) * scale,
    ];
    const ordered = [...triangles].sort((a, b) =>
      a.reduce((sum, point) => sum + point[axes[2]], 0) - b.reduce((sum, point) => sum + point[axes[2]], 0),
    );
    for (const tri of ordered) {
      const depth = tri.reduce((sum, point) => sum + point[axes[2]], 0) / 3;
      const shade = Math.round(80 + 130 * ((depth - minD) / Math.max(1e-6, maxD - minD)));
      ctx.beginPath();
      const [a, b, c] = tri.map(project);
      ctx.moveTo(a[0], a[1]); ctx.lineTo(b[0], b[1]); ctx.lineTo(c[0], c[1]); ctx.closePath();
      ctx.fillStyle = `rgb(${shade},${Math.max(35, shade - 18)},${Math.max(25, shade - 28)})`;
      ctx.fill();
      ctx.strokeStyle = "rgba(25,20,15,0.16)";
      ctx.lineWidth = 0.45;
      ctx.stroke();
    }
  }
}

fs.writeFileSync(output, canvas.toBuffer("image/png"));
console.log(`wrote ${path.relative(root, output)} (${canvas.width}x${canvas.height})`);
