// =============================================================================
// fifo.ts — the write-gather-pipe decoder: how vertices actually reach the GPU.
//
// THE CENTRAL FINDING OF THE GX INVENTORY, stated here because it shapes every
// design decision in this directory:
//
//   Gotcha Force's immediate-mode draw path is NOT a function call. The ROM
//   calls gnt4_GXBegin_bl(prim, vtxfmt, nverts) and then STORES the vertex
//   components directly to the GameCube's write-gather pipe at the
//   memory-mapped address 0xCC008000. In the decompiled corpus those stores
//   appear as `DAT_cc008000 = ...` / `DAT_cc008000._0_2_ = ...` — 1143 such
//   stores across the export. There is no GXEnd symbol at all (the SDK's
//   GXEnd is an empty macro), so a primitive ends when its vertex count is
//   satisfied, not on a call.
//
//   A host that intercepts only GX FUNCTION CALLS therefore sees GXBegin and
//   never sees a single vertex.
//
// CONSEQUENCE FOR THE COMPOSED MODULE (open, not solved — see
// docs/gx-hle-host.md): 0xCC008000 is hardware MMIO, and the composed module's
// linear memory is 0x807A0000 bytes, so a literal store to that address is out
// of bounds and traps. Lowering `DAT_cc008000` stores to the WGPipe import
// this decoder consumes is a REQUIRED assembly-gate amendment that does not
// exist yet. Until it lands, no real ROM unit can submit geometry, and this
// decoder is exercised only by the purpose-built fixture.
//
// This file is otherwise self-contained: it takes WGPipe writes plus the
// latched GxState, assembles vertices per the active VCD/VAT, and hands
// completed primitives to a backend.
// =============================================================================

import type { GcMemory } from "../memory.js";
import {
  GXAttr,
  GXAttrType,
  GXColorCompType,
  GXCompCnt,
  GXCompType,
  attrName,
  directComponentBytes,
  primitiveName,
} from "./enums.js";
import type { GxDrawState, GxState } from "./state.js";

/** One assembled primitive, ready for a backend. */
export interface GxPrimitive {
  /** The GX primitive byte the ROM passed to GXBegin. */
  primitive: number;
  /** Vertex format slot (GXBegin's second argument). */
  vtxfmt: number;
  vertexCount: number;
  /** xyz per vertex, already de-fixed-pointed. Always 3 wide (z=0 for XY). */
  positions: Float32Array;
  /** xyz per vertex, or null when the draw carried no normals. */
  normals: Float32Array | null;
  /** rgba 0-255 per vertex, or null. */
  colors: Uint8Array | null;
  /** st per vertex for TEX0, or null. */
  texcoords: Float32Array | null;
  /** Per-vertex position-matrix index (GX_VA_PNMTXIDX), or null. */
  posMtxIdx: Uint8Array | null;
  /** Pipeline state latched when GXBegin ran. */
  state: GxDrawState;
}

/** Where assembled primitives go. */
export interface GxPrimitiveSink {
  submit(primitive: GxPrimitive): void;
}

/** Thrown when the FIFO stream cannot be decoded. Never swallowed: a
 *  mis-decoded stream draws a wrong frame, which is the one outcome this
 *  whole seam exists to avoid. */
export class GxFifoError extends Error {
  constructor(message: string) {
    super(`GX FIFO: ${message}`);
    this.name = "GxFifoError";
  }
}

interface AttrPlan {
  attr: number;
  /** GXAttrType. */
  type: number;
  /** Bytes this attribute occupies in the DIRECT stream (or the index width). */
  bytes: number;
  /** VAT entry for DIRECT / indexed fetch. Null for the matrix-index attrs. */
  cnt: number;
  compType: number;
  frac: number;
}

/**
 * Decodes write-gather-pipe traffic into primitives.
 *
 * Byte-oriented on purpose: the ROM writes the pipe at 1, 2 and 4-byte widths
 * (Ghidra's `._0_1_` / `._0_2_` / plain forms) and the hardware simply
 * concatenates them big-endian into the command stream. Assembling into a byte
 * queue and then reading typed components out of it reproduces that exactly,
 * and it is why every read below is BIG-endian: the GameCube is big-endian and
 * the FIFO carries raw register-order bytes, unlike the little-endian linear
 * memory the rest of this runtime uses.
 */
export class GxFifo {
  #bytes: number[] = [];
  #state: GxState;
  #sink: GxPrimitiveSink;
  #mem: GcMemory | null;

  // Active primitive, or null between GXBegin and its vertex budget running out.
  #prim: number | null = null;
  #vtxfmt = 0;
  #expected = 0;
  #plan: AttrPlan[] = [];
  #vertexBytes = 0;
  #decoded = 0;
  #snapshot: GxDrawState | null = null;
  #positions: number[] = [];
  #normals: number[] = [];
  #colors: number[] = [];
  #texcoords: number[] = [];
  #posMtxIdx: number[] = [];
  #haveNormals = false;
  #haveColors = false;
  #haveTexcoords = false;
  #havePosMtxIdx = false;

  /** Vertices dropped because the stream ended mid-primitive. Surfaced, never
   *  hidden: a nonzero value means the host and the ROM disagree about the
   *  vertex layout. */
  droppedBytes = 0;
  /** Primitives completed since construction. */
  primitiveCount = 0;

  constructor(state: GxState, sink: GxPrimitiveSink, mem: GcMemory | null = null) {
    this.#state = state;
    this.#sink = sink;
    this.#mem = mem;
  }

  /** GXBegin(prim, vtxfmt, nverts): latch state and plan the vertex layout. */
  begin(prim: number, vtxfmt: number, nverts: number): void {
    if (this.#prim !== null && this.#decoded < this.#expected) {
      throw new GxFifoError(
        `GXBegin(${primitiveName(prim)}) while ${primitiveName(this.#prim)} still wants ` +
          `${this.#expected - this.#decoded} more vertices — the ROM and the host disagree about the vertex layout`,
      );
    }
    this.#prim = prim & 0xff;
    this.#vtxfmt = vtxfmt & 7;
    this.#expected = nverts & 0xffff;
    this.#snapshot = this.#state.snapshot();
    this.#plan = this.#planVertex();
    this.#vertexBytes = this.#plan.reduce((sum, p) => sum + p.bytes, 0);
    this.#decoded = 0;
    this.#positions = [];
    this.#normals = [];
    this.#colors = [];
    this.#texcoords = [];
    this.#posMtxIdx = [];
    this.#haveNormals = false;
    this.#haveColors = false;
    this.#haveTexcoords = false;
    this.#havePosMtxIdx = false;
    this.#bytes.length = 0;
    if (this.#expected === 0) this.#finish();
  }

  /** True while a primitive is waiting on vertex data. */
  get inPrimitive(): boolean {
    return this.#prim !== null;
  }

  /** Bytes still buffered (should be 0 between primitives). */
  get pendingBytes(): number {
    return this.#bytes.length;
  }

  // --- WGPipe stores (the lowered `DAT_cc008000 = ...` writes) ---------------

  writeU8(value: number): void {
    this.#push([value & 0xff]);
  }
  writeU16(value: number): void {
    const v = value & 0xffff;
    this.#push([(v >>> 8) & 0xff, v & 0xff]);
  }
  writeU32(value: number): void {
    const v = value >>> 0;
    this.#push([(v >>> 24) & 0xff, (v >>> 16) & 0xff, (v >>> 8) & 0xff, v & 0xff]);
  }
  writeF32(value: number): void {
    const dv = new DataView(new ArrayBuffer(4));
    dv.setFloat32(0, value, false);
    this.#push([dv.getUint8(0), dv.getUint8(1), dv.getUint8(2), dv.getUint8(3)]);
  }

  #push(bytes: number[]): void {
    if (this.#prim === null) {
      // Stores outside a primitive are GX command traffic (register writes the
      // SDK emits inline). The host does not decode the command stream — it
      // takes its state from the entry-point adapters — so these are counted
      // and dropped rather than silently mixed into vertex data.
      this.droppedBytes += bytes.length;
      return;
    }
    for (const b of bytes) this.#bytes.push(b);
    this.#drain();
  }

  // --- vertex assembly -------------------------------------------------------

  #planVertex(): AttrPlan[] {
    const plan: AttrPlan[] = [];
    for (const { attr, type } of this.#state.activeAttributes()) {
      if (attr === GXAttr.PNMTXIDX || (attr >= GXAttr.TEX0MTXIDX && attr <= GXAttr.TEX7MTXIDX)) {
        // Matrix-index attributes are always a single DIRECT byte.
        plan.push({ attr, type: GXAttrType.DIRECT, bytes: 1, cnt: 0, compType: GXCompType.U8, frac: 0 });
        continue;
      }
      const vat = this.#state.vatEntry(this.#vtxfmt, attr);
      if (!vat) {
        throw new GxFifoError(
          `${attrName(attr)} is in the vertex descriptor but has no GXSetVtxAttrFmt entry in format ${this.#vtxfmt} — ` +
            `refusing to guess its size (a wrong size desynchronizes the whole stream)`,
        );
      }
      if (type === GXAttrType.INDEX8 || type === GXAttrType.INDEX16) {
        plan.push({
          attr,
          type,
          bytes: type === GXAttrType.INDEX8 ? 1 : 2,
          cnt: vat.cnt,
          compType: vat.type,
          frac: vat.frac,
        });
        continue;
      }
      if (type !== GXAttrType.DIRECT) {
        throw new GxFifoError(`${attrName(attr)}: unimplemented GXAttrType ${type}`);
      }
      const bytes = directComponentBytes(attr, vat.cnt, vat.type);
      if (bytes === null) {
        throw new GxFifoError(
          `${attrName(attr)}: unimplemented DIRECT format cnt=${vat.cnt} type=${vat.type} — ` +
            `the host cannot size this component group and will not guess`,
        );
      }
      plan.push({ attr, type, bytes, cnt: vat.cnt, compType: vat.type, frac: vat.frac });
    }
    return plan;
  }

  #drain(): void {
    while (this.#prim !== null && this.#decoded < this.#expected && this.#bytes.length >= this.#vertexBytes) {
      const vertex = this.#bytes.splice(0, this.#vertexBytes);
      this.#decodeVertex(new DataView(Uint8Array.from(vertex).buffer));
      this.#decoded += 1;
    }
    if (this.#prim !== null && this.#decoded >= this.#expected) this.#finish();
  }

  #decodeVertex(dv: DataView): void {
    let offset = 0;
    for (const plan of this.#plan) {
      if (plan.type === GXAttrType.INDEX8 || plan.type === GXAttrType.INDEX16) {
        const index = plan.type === GXAttrType.INDEX8 ? dv.getUint8(offset) : dv.getUint16(offset, false);
        offset += plan.bytes;
        this.#decodeIndexed(plan, index);
        continue;
      }
      this.#decodeDirect(plan, dv, offset);
      offset += plan.bytes;
    }
  }

  /** Read one DIRECT component group straight out of the FIFO bytes. */
  #decodeDirect(plan: AttrPlan, dv: DataView, offset: number): void {
    const scale = 1 / Math.pow(2, plan.frac);
    const scalar = (i: number): number => {
      switch (plan.compType) {
        case GXCompType.U8:
          return dv.getUint8(offset + i) * scale;
        case GXCompType.S8:
          return dv.getInt8(offset + i) * scale;
        case GXCompType.U16:
          return dv.getUint16(offset + i * 2, false) * scale;
        case GXCompType.S16:
          return dv.getInt16(offset + i * 2, false) * scale;
        case GXCompType.F32:
          return dv.getFloat32(offset + i * 4, false);
        default:
          throw new GxFifoError(`${attrName(plan.attr)}: unimplemented component type ${plan.compType}`);
      }
    };
    this.#store(plan, scalar, dv, offset, false);
  }

  /**
   * Fetch one component group through the attribute's GXSetArray binding.
   * Reads the shared arena at the ORIGINAL GC address — the same memory the
   * ROM would have read — so an indexed draw and a direct draw of the same
   * geometry produce the same vertices.
   *
   * ENDIANNESS: LITTLE, unlike the FIFO stream above. This is not an
   * inconsistency, it is the port's two distinct byte orders:
   *  - the ARENA is byte-swapped to wasm-native little-endian when it is
   *    built from the DOL (verified: apps/game/public/rom/arena.json stores
   *    the 1.0f constant at 0x80436f78 as `00 00 80 3f`), which is what lets
   *    ported C read it with ordinary little-endian loads;
   *  - the FIFO is a register-order byte stream that never lived in memory,
   *    so it keeps the console's big-endian order.
   */
  #decodeIndexed(plan: AttrPlan, index: number): void {
    const binding = this.#state.arrays.get(plan.attr);
    if (!binding) {
      throw new GxFifoError(
        `${attrName(plan.attr)} is INDEX${plan.type === GXAttrType.INDEX8 ? "8" : "16"} but GXSetArray was never called for it`,
      );
    }
    const mem = this.#mem;
    if (!mem) {
      throw new GxFifoError(`${attrName(plan.attr)}: indexed fetch needs the shared arena, which this FIFO was not given`);
    }
    const base = (binding.base + index * binding.stride) >>> 0;
    const bytes = directComponentBytes(plan.attr, plan.cnt, plan.compType);
    if (bytes === null) throw new GxFifoError(`${attrName(plan.attr)}: unimplemented indexed format`);
    const raw = mem.readBytes(base, bytes);
    const dv = new DataView(raw.buffer, raw.byteOffset, raw.byteLength);
    const scale = 1 / Math.pow(2, plan.frac);
    const scalar = (i: number): number => {
      switch (plan.compType) {
        case GXCompType.U8:
          return dv.getUint8(i) * scale;
        case GXCompType.S8:
          return dv.getInt8(i) * scale;
        case GXCompType.U16:
          return dv.getUint16(i * 2, true) * scale;
        case GXCompType.S16:
          return dv.getInt16(i * 2, true) * scale;
        case GXCompType.F32:
          return dv.getFloat32(i * 4, true);
        default:
          throw new GxFifoError(`${attrName(plan.attr)}: unimplemented component type ${plan.compType}`);
      }
    };
    this.#store(plan, scalar, dv, 0, true);
  }

  #store(
    plan: AttrPlan,
    scalar: (i: number) => number,
    dv: DataView,
    offset: number,
    littleEndian: boolean,
  ): void {
    const attr = plan.attr;
    if (attr === GXAttr.PNMTXIDX) {
      this.#havePosMtxIdx = true;
      this.#posMtxIdx.push(dv.getUint8(offset));
      return;
    }
    if (attr >= GXAttr.TEX0MTXIDX && attr <= GXAttr.TEX7MTXIDX) return; // latched, not per-vertex geometry
    if (attr === GXAttr.POS) {
      const n = plan.cnt === GXCompCnt.POS_XY ? 2 : 3;
      this.#positions.push(scalar(0), scalar(1), n === 3 ? scalar(2) : 0);
      return;
    }
    if (attr === GXAttr.NRM) {
      this.#haveNormals = true;
      this.#normals.push(scalar(0), scalar(1), scalar(2));
      return;
    }
    if (attr === GXAttr.CLR0 || attr === GXAttr.CLR1) {
      this.#haveColors = true;
      this.#colors.push(...this.#decodeColor(plan.compType, dv, offset, littleEndian));
      return;
    }
    if (attr >= GXAttr.TEX0 && attr <= GXAttr.TEX7) {
      if (attr === GXAttr.TEX0) {
        this.#haveTexcoords = true;
        this.#texcoords.push(scalar(0), plan.cnt === GXCompCnt.TEX_S ? 0 : scalar(1));
      }
      return;
    }
    throw new GxFifoError(`${attrName(attr)}: no vertex-assembly rule`);
  }

  #decodeColor(
    type: number,
    dv: DataView,
    offset: number,
    littleEndian: boolean,
  ): [number, number, number, number] {
    switch (type) {
      case GXColorCompType.RGB565: {
        const v = dv.getUint16(offset, littleEndian);
        return [((v >> 11) & 0x1f) * 8, ((v >> 5) & 0x3f) * 4, (v & 0x1f) * 8, 255];
      }
      case GXColorCompType.RGB8:
        return [dv.getUint8(offset), dv.getUint8(offset + 1), dv.getUint8(offset + 2), 255];
      case GXColorCompType.RGBX8:
        return [dv.getUint8(offset), dv.getUint8(offset + 1), dv.getUint8(offset + 2), 255];
      case GXColorCompType.RGBA4: {
        const v = dv.getUint16(offset, littleEndian);
        return [((v >> 12) & 0xf) * 17, ((v >> 8) & 0xf) * 17, ((v >> 4) & 0xf) * 17, (v & 0xf) * 17];
      }
      case GXColorCompType.RGBA6: {
        const b0 = dv.getUint8(offset);
        const b1 = dv.getUint8(offset + 1);
        const b2 = dv.getUint8(offset + 2);
        const v = (b0 << 16) | (b1 << 8) | b2;
        const q = (x: number): number => Math.round((x & 0x3f) * (255 / 63));
        return [q(v >> 18), q(v >> 12), q(v >> 6), q(v)];
      }
      case GXColorCompType.RGBA8:
        return [dv.getUint8(offset), dv.getUint8(offset + 1), dv.getUint8(offset + 2), dv.getUint8(offset + 3)];
      default:
        throw new GxFifoError(`unimplemented colour component type ${type}`);
    }
  }

  #finish(): void {
    const prim = this.#prim;
    const snapshot = this.#snapshot;
    this.#prim = null;
    this.#snapshot = null;
    if (prim === null || snapshot === null) return;
    if (this.#bytes.length > 0) {
      // Leftover bytes mean the ROM wrote more per vertex than the host
      // decoded — a layout disagreement. Report it rather than absorb it.
      this.droppedBytes += this.#bytes.length;
      this.#bytes.length = 0;
    }
    this.primitiveCount += 1;
    this.#sink.submit({
      primitive: prim,
      vtxfmt: this.#vtxfmt,
      vertexCount: this.#decoded,
      positions: Float32Array.from(this.#positions),
      normals: this.#haveNormals ? Float32Array.from(this.#normals) : null,
      colors: this.#haveColors ? Uint8Array.from(this.#colors) : null,
      texcoords: this.#haveTexcoords ? Float32Array.from(this.#texcoords) : null,
      posMtxIdx: this.#havePosMtxIdx ? Uint8Array.from(this.#posMtxIdx) : null,
      state: snapshot,
    });
  }
}
