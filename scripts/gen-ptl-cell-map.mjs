#!/usr/bin/env node
// gen-ptl-cell-map.mjs — resolve the battle particle bank's texId -> visual definition.
//
// NAME NOTE: this script was commissioned as "parse the ptcl00.ptl bank" (the working
// hypothesis in research/decomp/impact-effect-id-decode-2026-07-04.md §1d). Parsing the
// ROM's actual consumer refuted that hypothesis: texIds do NOT index ptcl00.ptl.
//
// PROVEN CHAIN (research/decomp/ptl-format-notes-2026-07-04.md):
//   zz_0042878_ @80042878 (chunk_0005.c:113-141) loads AFS file 0x2b9 = efct.pzz to
//     base+0x7a3c00; member0 (efct00.tpl, 0x8040 -> 0x8800 block-aligned) sits first, so
//     DAT_803bb378 = base+0x7ac400 = member1 = efct00_mdl.arc (byte-identical to the
//     standalone disc file, verified by cmp).
//   zz_0042954_ @80042954 allocates the bank object DAT_803bb374 and calls
//     zz_0040eb4_ -> zz_0006c88_ @80006c88 (chunk_0000.c:1312) = gnt4_HSD_ArchiveParse
//     on that buffer; bank+0x10 = the archive's public root ("scene_data", an HSD SOBJ).
//   zz_0006fb4_ @80006fb4 (chunk_0000.c:1511), the draw-path texId consumer:
//     jobjDescArray = *(bank+0x10)->word0;  desc = jobjDescArray[texId];
//     gnt4_HSD_JObjLoadJoint(desc->word0 /* root JOBJ */).
//   => texId is an INDEX INTO THE scene_data JOBJDesc ARRAY of efct00_mdl.arc.
//      That array has 157 entries (texIds 0..156), covering the max observed texId 146.
//
// The entries are NOT textured sprites: the archive contains ZERO image descriptors
// (no TOBJ anywhere; no TEX0 vertex attribute anywhere). Each entry is a small 3D
// vector mesh (GX triangle strips/triangles/quads) with optional per-vertex RGBA colors,
// a material constant color, and a PE blend mode (mostly srcAlpha+ONE = additive).
// ptcl00.ptl (20 entries, offset-table format) is a SEPARATE point-sprite emitter bank
// and is documented — but not consumed by this chain — in the ptl-format notes.
//
// Output: apps/game/src/sim/data/efctBankMeshes.json
//   { _meta, entries: { [texId]: { jobjs: [...], hasMatAnim } } }
// Each jobj: { parent, flags, t/r/s (only when non-identity), dobjs: [...] }
// Each dobj: { dif: [r,g,b,a] u8, alpha: float, blend: "add"|"alpha", renderFlags,
//              mesh: { positions: [...xyz], colors: [...rgba u8] | null, indices } }
//
// Validation baked in (fails loudly):
//   - entry count >= 147 (max impact texId 146 must resolve)
//   - texId 21 (impact id 0 flash): POS-only radial mesh
//   - texIds 2/3 (id-1 player burst): same disc geometry, rim colors blue vs pink
//   - texId 146 (id 2-7 ring layer): flat in XY (|z| < 0.001 of extent)
import { createHash } from "node:crypto";
import { mkdir, readFile, writeFile } from "node:fs/promises";
import path from "node:path";
import { fileURLToPath } from "node:url";

const repoRoot = path.resolve(path.dirname(fileURLToPath(import.meta.url)), "..");
const region = "GG4E";
const arcRel = `user-data/${region}/afs_data/root/efct00_mdl.arc`;
const outRel = "apps/game/src/sim/data/efctBankMeshes.json";

const buf = await readFile(path.join(repoRoot, arcRel));
const dv = new DataView(buf.buffer, buf.byteOffset, buf.byteLength);
const u32 = (o) => dv.getUint32(o);
const u16 = (o) => dv.getUint16(o);
const f32 = (o) => dv.getFloat32(o);
const u8 = (o) => buf[o];

// ---- HSD DAT container ----------------------------------------------------
const DATA = 0x20;
const fileSize = u32(0);
const dataSize = u32(4);
const relocCount = u32(8);
const rootCount = u32(12);
if (fileSize !== buf.length) throw new Error(`DAT fileSize ${fileSize} != file length ${buf.length}`);
if (rootCount !== 1) throw new Error(`expected 1 root, got ${rootCount}`);
const relocOff = DATA + dataSize;
// The reloc table is the authoritative "this data-offset holds a pointer" set — used to
// distinguish real child/next/desc pointers from zero-initialized scalar fields.
const relocSet = new Set();
for (let i = 0; i < relocCount; i++) relocSet.add(u32(relocOff + i * 4));
const rootOff = relocOff + relocCount * 4;
const strOff = rootOff + 8;
const rootData = u32(rootOff);
const rootName = buf.slice(strOff + u32(rootOff + 4), buf.indexOf(0, strOff + u32(rootOff + 4))).toString();
if (rootName !== "scene_data") throw new Error(`root symbol ${rootName} != scene_data`);

const P = (o) => u32(DATA + o); // raw word at data offset
const PP = (o) => (relocSet.has(o) ? u32(DATA + o) : 0); // pointer-checked deref

// ---- scene_data (SOBJ) -> JOBJDesc array (texId index space) ---------------
const descArr = PP(rootData);
if (!descArr) throw new Error("scene_data has no JOBJDesc array");
const descs = [];
for (let i = 0; ; i++) {
  const p = P(descArr + i * 4);
  if (p === 0) break;
  descs.push(p);
}
if (descs.length < 147) throw new Error(`JOBJDesc count ${descs.length} < 147 (max impact texId 146)`);

// ---- GX vertex attribute + display-list decode ------------------------------
const ATYPE = { 0: "NONE", 1: "DIRECT", 2: "INDEX8", 3: "INDEX16" };
function readAttrList(a) {
  const list = [];
  for (let i = 0; i < 16; i++) {
    const name = P(a);
    if (name === 0xff) break;
    const atype = ATYPE[P(a + 4)];
    const attr = {
      name,
      atype,
      cnt: P(a + 8),
      ctype: P(a + 12),
      frac: u8(DATA + a + 16),
      stride: u16(DATA + a + 18),
      base: PP(a + 20),
    };
    if (!atype || atype === "DIRECT" || atype === "NONE") {
      throw new Error(`unsupported attr type for attr ${name}: ${P(a + 4)}`);
    }
    if (name !== 9 && name !== 10 && name !== 11) throw new Error(`unexpected vertex attr ${name}`);
    list.push(attr);
    a += 0x18;
  }
  return list;
}
function readPos(attr, idx) {
  const o = DATA + attr.base + idx * attr.stride;
  if (attr.ctype !== 4) throw new Error(`POS comp type ${attr.ctype} unsupported (expected f32)`);
  return [f32(o), f32(o + 4), f32(o + 8)];
}
function readColor(attr, idx) {
  const o = DATA + attr.base + idx * attr.stride;
  if (attr.ctype !== 5) throw new Error(`CLR0 format ${attr.ctype} unsupported (expected GX_RGBA8)`);
  return [u8(o), u8(o + 1), u8(o + 2), u8(o + 3)];
}
const round = (v) => Math.round(v * 100) / 100;

/** Decode one POBJ display list into an indexed triangle mesh. */
function decodePobj(pobj) {
  const attrs = readAttrList(PP(pobj + 8));
  const nDisp = u16(DATA + pobj + 0xe);
  const dl = PP(pobj + 0x10);
  const posAttr = attrs.find((a) => a.name === 9);
  const clrAttr = attrs.find((a) => a.name === 11);
  if (!posAttr) throw new Error("POBJ without POS attribute");
  const vertKey = new Map(); // "posIdx|clrIdx" -> unified index
  const positions = [];
  const colors = clrAttr ? [] : null;
  const indices = [];
  const unify = (pi, ci) => {
    const key = `${pi}|${ci}`;
    let idx = vertKey.get(key);
    if (idx === undefined) {
      idx = positions.length / 3;
      vertKey.set(key, idx);
      positions.push(...readPos(posAttr, pi).map(round));
      if (colors) colors.push(...readColor(clrAttr, ci));
    }
    return idx;
  };
  let p = DATA + dl;
  const end = p + nDisp * 0x20;
  while (p < end) {
    const op = u8(p);
    if (op === 0) break; // GX NOP padding at list end
    const prim = op & 0xf8;
    const count = u16(p + 1);
    p += 3;
    const verts = [];
    for (let v = 0; v < count; v++) {
      let pi = 0;
      let ci = 0;
      for (const a of attrs) {
        const idx = a.atype === "INDEX8" ? u8(p) : u16(p);
        p += a.atype === "INDEX8" ? 1 : 2;
        if (a.name === 9) pi = idx;
        else if (a.name === 11) ci = idx;
        // NRM (10) indices are consumed but not emitted (all FX draw unlit).
      }
      verts.push(unify(pi, ci));
    }
    if (prim === 0x90) {
      // GX_TRIANGLES
      for (let i = 0; i + 2 < count; i += 3) indices.push(verts[i], verts[i + 1], verts[i + 2]);
    } else if (prim === 0x98) {
      // GX_TRIANGLESTRIP (alternate winding)
      for (let i = 0; i + 2 < count; i++) {
        if (i % 2 === 0) indices.push(verts[i], verts[i + 1], verts[i + 2]);
        else indices.push(verts[i + 1], verts[i], verts[i + 2]);
      }
    } else if (prim === 0xa0) {
      // GX_TRIANGLEFAN
      for (let i = 1; i + 1 < count; i++) indices.push(verts[0], verts[i], verts[i + 1]);
    } else if (prim === 0x80) {
      // GX_QUADS
      for (let i = 0; i + 3 < count; i += 4) {
        indices.push(verts[i], verts[i + 1], verts[i + 2], verts[i], verts[i + 2], verts[i + 3]);
      }
    } else {
      throw new Error(`unsupported GX primitive 0x${prim.toString(16)}`);
    }
  }
  return { positions, colors, indices };
}

// ---- JOBJ / DOBJ / MOBJ walk ------------------------------------------------
const JOBJ_PTCL = 0x20;
const JOBJ_SPLINE = 0x4000;
function decodeDobjs(jobj) {
  const dobjs = [];
  let dobj = PP(jobj + 0x10);
  let guard = 0;
  while (dobj && guard++ < 64) {
    const mobj = PP(dobj + 8);
    let material = { dif: [255, 255, 255, 255], alpha: 1, blend: "alpha", renderFlags: 0 };
    if (mobj) {
      const renderFlags = P(mobj + 4);
      const mat = PP(mobj + 0xc);
      const pe = PP(mobj + 0x14);
      let blend = "alpha";
      if (pe) {
        // HSD_PEDesc: +4 type, +5 src factor, +6 dst factor (GX_BM_BLEND=1,
        // GX_BL_SRCALPHA=4, GX_BL_ONE=1, GX_BL_INVSRCALPHA=5). Bank census: only
        // (1,4,1)=additive and (1,4,5)=alpha appear.
        const type = u8(DATA + pe + 4);
        const src = u8(DATA + pe + 5);
        const dst = u8(DATA + pe + 6);
        blend = type === 1 && src === 4 && dst === 1 ? "add" : "alpha";
      }
      material = {
        dif: mat ? [u8(DATA + mat + 4), u8(DATA + mat + 5), u8(DATA + mat + 6), u8(DATA + mat + 7)] : [255, 255, 255, 255],
        alpha: mat ? Math.round(f32(DATA + mat + 0xc) * 1000) / 1000 : 1,
        blend,
        renderFlags,
      };
    }
    const meshes = [];
    let pobj = PP(dobj + 0xc);
    let g2 = 0;
    while (pobj && g2++ < 64) {
      meshes.push(decodePobj(pobj));
      pobj = PP(pobj + 4);
    }
    // Merge a DOBJ's POBJs (same material) into one mesh.
    const merged = { positions: [], colors: meshes.some((m) => m.colors) ? [] : null, indices: [] };
    for (const m of meshes) {
      const base = merged.positions.length / 3;
      merged.positions.push(...m.positions);
      if (merged.colors) {
        if (m.colors) merged.colors.push(...m.colors);
        else for (let i = 0; i < m.positions.length / 3; i++) merged.colors.push(255, 255, 255, 255);
      }
      merged.indices.push(...m.indices.map((i) => i + base));
    }
    dobjs.push({ ...material, mesh: merged });
    dobj = PP(dobj + 4);
  }
  return dobjs;
}
function decodeJobjTree(rootJobj) {
  const out = [];
  const visit = (jobj, parent, depth) => {
    if (!jobj || depth > 16 || out.length > 64) return;
    const flags = P(jobj + 4);
    const node = { parent, flags };
    const r = [f32(DATA + jobj + 0x14), f32(DATA + jobj + 0x18), f32(DATA + jobj + 0x1c)];
    const s = [f32(DATA + jobj + 0x20), f32(DATA + jobj + 0x24), f32(DATA + jobj + 0x28)];
    const t = [f32(DATA + jobj + 0x2c), f32(DATA + jobj + 0x30), f32(DATA + jobj + 0x34)];
    if (r.some((v) => v !== 0)) node.r = r.map(round);
    if (s.some((v) => v !== 1)) node.s = s.map(round);
    if (t.some((v) => v !== 0)) node.t = t.map(round);
    // PTCL/SPLINE jobjs reinterpret +0x10; none appear in this bank but guard anyway.
    node.dobjs = flags & (JOBJ_PTCL | JOBJ_SPLINE) ? [] : decodeDobjs(jobj);
    const self = out.length;
    out.push(node);
    const child = PP(jobj + 8);
    const next = PP(jobj + 0xc);
    if (child) visit(child, self, depth + 1);
    if (next && depth > 0) visit(next, parent, depth);
  };
  visit(rootJobj, -1, 0);
  return out;
}

const entries = {};
let totalTris = 0;
for (const [texId, desc] of descs.entries()) {
  const jobjs = decodeJobjTree(PP(desc));
  const hasMatAnim = PP(desc + 8) !== 0;
  for (const j of jobjs) for (const d of j.dobjs) totalTris += d.mesh.indices.length / 3;
  entries[texId] = { jobjs, ...(hasMatAnim ? { hasMatAnim } : {}) };
}

// ---- validation against the impact-effect decode ---------------------------
function firstMesh(texId) {
  for (const j of entries[texId].jobjs) if (j.dobjs.length) return j.dobjs[0].mesh;
  throw new Error(`texId ${texId} has no mesh`);
}
{
  // texId 21 — impact id 0 "swelling flash": POS-only radial spike mesh.
  const m = firstMesh(21);
  if (m.colors !== null) throw new Error("texId 21 expected POS-only mesh");
  const maxR = Math.max(...m.positions.map(Math.abs));
  if (maxR < 30 || maxR > 200) throw new Error(`texId 21 radius ${maxR} out of expected range`);
  // texIds 2/3 — impact id 1 per-player burst particle: identical disc geometry,
  // rim colors blue (P1) vs pink (P2), shared white core.
  const m2 = firstMesh(2);
  const m3 = firstMesh(3);
  if (JSON.stringify(m2.positions) !== JSON.stringify(m3.positions)) {
    throw new Error("texIds 2/3 expected identical geometry");
  }
  const rim = (m, i) => m.colors.slice(i * 4, i * 4 + 4).join(",");
  const rims2 = new Set();
  const rims3 = new Set();
  for (let i = 0; i < m2.colors.length / 4; i++) {
    rims2.add(rim(m2, i));
    rims3.add(rim(m3, i));
  }
  if (!rims2.has("0,0,255,64")) throw new Error("texId 2 missing blue rim color 0,0,255,64");
  if (!rims3.has("255,0,128,64")) throw new Error("texId 3 missing pink rim color 255,0,128,64");
  if (!rims2.has("255,255,255,255") || !rims3.has("255,255,255,255")) {
    throw new Error("texIds 2/3 missing shared white core color");
  }
  // texId 146 — impact ids 2..7 ring layer: flat in the XY plane.
  const m146 = firstMesh(146);
  let maxZ = 0;
  let maxXY = 0;
  for (let i = 0; i < m146.positions.length; i += 3) {
    maxXY = Math.max(maxXY, Math.abs(m146.positions[i]), Math.abs(m146.positions[i + 1]));
    maxZ = Math.max(maxZ, Math.abs(m146.positions[i + 2]));
  }
  if (maxZ > maxXY * 0.001) throw new Error(`texId 146 not flat (maxZ ${maxZ} vs extent ${maxXY})`);
}

const out = {
  _meta: {
    generator: "scripts/gen-ptl-cell-map.mjs",
    date: new Date().toISOString().slice(0, 10),
    source: {
      archive: arcRel,
      sha1: createHash("sha1").update(buf).digest("hex"),
      rootSymbol: rootName,
      jobjDescCount: descs.length,
    },
    chain:
      "damage record u8+0x09 -> effect table 0x802c7ed0 -> variant defs PTR_DAT_802c8154 " +
      "(texId per layer) -> zz_0006fb4_ @80006fb4: texId indexes the scene_data JOBJDesc " +
      "array of efct00_mdl.arc (= efct.pzz member1, bank DAT_803bb374 built by zz_0042954_ " +
      "@80042954 / zz_0006c88_ @80006c88 HSD_ArchiveParse). Entries are untextured " +
      "vertex-colored GX meshes; the file contains no TOBJ/TEX0 data at all. " +
      "ptcl00.ptl is a SEPARATE 20-entry emitter bank, NOT this index space.",
    spec: "research/decomp/ptl-format-notes-2026-07-04.md",
    units: "ROM world units (1:1 with sim positions)",
    fields: {
      jobjs: "flattened JOBJ tree; parent=-1 is the root; r/s/t omitted when identity",
      dobjs: "dif = material diffuse RGBA (u8), alpha = material alpha float, blend = add|alpha (PE desc), renderFlags = raw MOBJ u32",
      mesh: "positions xyz f32 (rounded 0.01), colors RGBA u8 per vertex or null, indices = triangles",
      hasMatAnim: "entry carries an HSD material-animation bank (color/alpha AOBJ tracks; NOT decoded — the boot.dol per-layer keyframe tracks drive the port's scale/alpha instead)",
    },
    totalTriangles: totalTris,
    validation: "texId 21 POS-only radial flash; texIds 2/3 same disc, blue vs pink rim; texId 146 flat XY ring; count>=147",
  },
  entries,
};

const outAbs = path.join(repoRoot, outRel);
await mkdir(path.dirname(outAbs), { recursive: true });
await writeFile(outAbs, JSON.stringify(out));
const stat = JSON.stringify(out).length;
console.log(`gen-ptl-cell-map: ${descs.length} entries, ${totalTris} triangles, ${(stat / 1024).toFixed(0)} KB -> ${outRel}`);
