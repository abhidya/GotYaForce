import type { BufferGeometry, Material, Object3D, Texture } from "three";

/**
 * Release resources owned exclusively by this tree (for example, an unloaded stage).
 * Deduplicates shared resources within the tree. Do not use on a cached model clone
 * while its source or siblings still need its shared geometry/materials/textures.
 * Does not remove children or dispose scene backgrounds, environments, or skeletons.
 */
export function disposeObject3D(root: Object3D): void {
  const geometries = new Set<BufferGeometry>();
  const materials = new Set<Material>();
  const textures = new Set<Texture>();
  const collectTexture = (value: unknown): void => {
    if (Array.isArray(value)) {
      for (const item of value) collectTexture(item);
    } else if (value && typeof value === "object" && (value as Texture).isTexture) {
      textures.add(value as Texture);
    }
  };
  root.traverse((object) => {
    const drawable = object as Object3D & { geometry?: BufferGeometry; material?: Material | Material[] };
    if (drawable.geometry) geometries.add(drawable.geometry);
    const assigned = drawable.material;
    for (const material of assigned ? (Array.isArray(assigned) ? assigned : [assigned]) : []) {
      if (materials.has(material)) continue;
      materials.add(material);
      for (const value of Object.values(material)) collectTexture(value);
      const uniforms = (material as Material & { uniforms?: Record<string, { value: unknown }> }).uniforms;
      if (uniforms) for (const uniform of Object.values(uniforms)) collectTexture(uniform.value);
    }
  });
  for (const texture of textures) texture.dispose();
  for (const material of materials) material.dispose();
  for (const geometry of geometries) geometry.dispose();
}
