import assert from "node:assert/strict";
import { readFileSync } from "node:fs";
import test from "node:test";
import ts from "typescript";
import * as THREE from "three";

const source = readFileSync(new URL("./disposeObject3D.ts", import.meta.url), "utf8");
const compiled = ts.transpileModule(source, {
  compilerOptions: { target: ts.ScriptTarget.ES2022, module: ts.ModuleKind.ES2022 },
});
const { disposeObject3D } = await import(`data:text/javascript;base64,${Buffer.from(compiled.outputText).toString("base64")}`);
const countDisposals = (resource) => {
  let count = 0;
  resource.addEventListener("dispose", () => { count += 1; });
  return () => count;
};

test("shared geometries, material arrays, and textures are released exactly once per tree", () => {
  const texture = new THREE.Texture();
  const geometry = new THREE.BoxGeometry();
  const first = new THREE.MeshStandardMaterial({ map: texture, normalMap: texture });
  const second = new THREE.MeshBasicMaterial({ map: texture });
  const resources = [texture, geometry, first, second];
  const counts = resources.map(countDisposals);
  const root = new THREE.Group();
  root.add(new THREE.Mesh(geometry, [first, second]), new THREE.Mesh(geometry, first));
  disposeObject3D(root);
  assert.deepEqual(counts.map((count) => count()), [1, 1, 1, 1]);
  assert.equal(root.children.length, 2, "caller owns scene removal");
});

test("shader texture uniforms and arrays are deduplicated; external resources stay alive", () => {
  const texture = new THREE.Texture();
  const external = new THREE.Texture();
  const shader = new THREE.ShaderMaterial({ uniforms: {
    single: { value: texture }, array: { value: [texture, texture] }, scalar: { value: 1 },
  } });
  const root = new THREE.Scene();
  root.background = external;
  root.add(new THREE.Points(new THREE.BufferGeometry(), shader));
  const count = countDisposals(texture);
  const outsideCount = countDisposals(external);
  disposeObject3D(root);
  assert.equal(count(), 1);
  assert.equal(outsideCount(), 0);
});

test("empty groups have no disposable resources", () => {
  assert.doesNotThrow(() => disposeObject3D(new THREE.Group()));
});
