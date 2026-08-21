// codec.mjs — the RomActor codec + coverage machinery (oracle-workstream-plan.md §3.3).
//
// Direction: TS-domain values -> GC-address arena bytes (encode); decode exists only
// for post-state assertion. The field map is machine-extracted from
// packages/combat/src/rom/actor.ts (@romfield annotations) into actor-field-map.json —
// never hand-maintained here.
//
// Loud-gap mechanisms implemented (plan §3.3 / I-4):
//   1. sentinel poisoning  — scratch regions are filled with the sentinel byte
//      (default 0xA5), never zeroed, before each case;
//   2. write-set tracking  — every byte written through the codec is recorded; the
//      spec's declared read-set is audited against it per case;
//   3. unmapped refusal    — encoding a field whose map record is "unmapped" (or
//      absent, or port_side) throws BlockedCodecError -> verdict "blocked_codec";
//   4. post-state byte-diff — after the call, every scratch region is compared
//      byte-for-byte against encoded-input ∪ declared-write-back ∪ sentinel; any
//      other differing byte is a stray write (failure).
import fs from "node:fs";

export class BlockedCodecError extends Error {
  constructor(field, reason) {
    super(`blocked_codec: field ${field} ${reason}`);
    this.field = field;
  }
}

export function loadFieldMap(path) {
  const map = JSON.parse(fs.readFileSync(path, "utf8"));
  const byInterface = {};
  for (const [iface, body] of Object.entries(map.interfaces)) {
    const fields = {};
    for (const rec of body.fields) fields[rec.tsField] = rec;
    byInterface[iface] = fields;
  }
  return { raw: map, byInterface };
}

export class Codec {
  /**
   * @param u8/dv    linear-memory views
   * @param fieldMap loadFieldMap() result
   * @param regions  scratch regions [{name, base, size}] — poisoned + byte-diffed
   * @param sentinel poison byte (default 0xA5; probe passes use another value)
   */
  constructor({ u8, dv, fieldMap, regions, arenaSegments = [], sentinel = 0xa5 }) {
    this.u8 = u8;
    this.dv = dv;
    this.fieldMap = fieldMap;
    this.regions = regions.map((r) => ({ ...r, base: r.base >>> 0 }));
    this.arenaSegments = arenaSegments.map((s) => ({ addr: s.addr >>> 0, size: s.size }));
    this.sentinel = sentinel & 0xff;
    this.writes = []; // [addr, len] this case (absolute)
    this.expected = new Map(); // region name -> Uint8Array expected image
  }

  /** Begin a case: poison every scratch region and reset the write log. */
  beginCase() {
    for (const r of this.regions) this.u8.fill(this.sentinel, r.base, r.base + r.size);
    this.writes = [];
    this.expected = new Map();
  }

  _logWrite(addr, len) { this.writes.push([addr >>> 0, len]); }

  // ---- raw write primitives (all tracked) ----
  wU8(a, v) { a >>>= 0; this.u8[a] = v & 0xff; this._logWrite(a, 1); }
  wS8(a, v) { this.wU8(a, v); }
  wU16(a, v) { a >>>= 0; this.dv.setUint16(a, v & 0xffff, true); this._logWrite(a, 2); }
  wI16(a, v) { a >>>= 0; this.dv.setInt16(a, v | 0, true); this._logWrite(a, 2); }
  wU32(a, v) { a >>>= 0; this.dv.setUint32(a, v >>> 0, true); this._logWrite(a, 4); }
  wI32(a, v) { a >>>= 0; this.dv.setInt32(a, v | 0, true); this._logWrite(a, 4); }
  wF32(a, v) { a >>>= 0; this.dv.setFloat32(a, v, true); this._logWrite(a, 4); }
  /** Big-endian u16 — byte order preserved at the data boundary (borgNumber rule). */
  wU16BE(a, v) { a >>>= 0; this.u8[a] = (v >> 8) & 0xff; this.u8[a + 1] = v & 0xff; this._logWrite(a, 2); }
  wBytes(a, bytes) { a >>>= 0; this.u8.set(bytes, a); this._logWrite(a, bytes.length); }

  /** Encode one mapped RomActor-interface field at `base` from a TS value.
   *  Refuses unmapped/port_side/absent records (mechanism 3). */
  encodeField(base, tsField, value, iface = "RomActor") {
    const fields = this.fieldMap.byInterface[iface];
    const rec = fields ? fields[tsField] : undefined;
    if (!rec) throw new BlockedCodecError(tsField, `has no record in the field map (${iface})`);
    if (rec.kind === "unmapped") throw new BlockedCodecError(tsField, "is unmapped in actor.ts — annotate, never guess");
    if (rec.kind === "port_side") throw new BlockedCodecError(tsField, "is port_side (no ROM storage)");
    this._encodeScalar(base, rec, value, tsField);
  }

  _encodeScalar(base, rec, value, tsField) {
    const a = base + rec.offset;
    switch (rec.kind) {
      case "u8": case "s8": this.wU8(a, value); break;
      case "u16": case "bam16": this.wU16(a, value); break;
      case "s16": this.wI16(a, value); break;
      case "u32": case "ptr": this.wU32(a, value >>> 0); break;
      case "s32": this.wI32(a, value); break;
      case "f32": this.wF32(a, value); break;
      case "u16be": this.wU16BE(a, value); break;
      case "vec3":
        this.wF32(a, value.x); this.wF32(a + 4, value.y); this.wF32(a + 8, value.z);
        break;
      case "tuple":
        for (let i = 0; i < rec.elems.length; i++) this._encodeScalar(base, rec.elems[i], value[i], tsField);
        break;
      default:
        throw new BlockedCodecError(tsField, `has kind ${rec.kind} the codec cannot encode`);
    }
  }

  /** Snapshot the current region contents as the expected post-state baseline
   *  (call after all encoding, before the wasm call). */
  snapshotExpected() {
    for (const r of this.regions) {
      this.expected.set(r.name, this.u8.slice(r.base, r.base + r.size));
    }
  }

  /** Audit the spec-declared read-set against the write log (mechanism 2).
   *  @param reads {mustWrite: [[addr,len],...], arenaOk: [[addr,len],...]}
   *    mustWrite — bytes the unit reads that the harness must have deliberately
   *      written this case (scratch objects AND live bss state); audited strictly
   *      against the write log.
   *    arenaOk — bytes the unit reads from DOL-sourced arena data (tables); satisfied
   *      by an arena segment or a write.
   *  Returns byte count declared-read-but-unwritten (+ first few addresses). */
  auditReads({ mustWrite = [], arenaOk = [] }) {
    // Build covered-byte lookup from the write log (write volume per case is small).
    const covered = new Set();
    for (const [a, l] of this.writes) for (let i = 0; i < l; i++) covered.add(a + i);
    let missing = 0;
    const missingAddrs = [];
    const check = (a0, l, allowArena) => {
      const a = a0 >>> 0;
      for (let i = 0; i < l; i++) {
        if (covered.has(a + i)) continue;
        if (allowArena && this._inArena(a + i)) continue;
        missing++;
        if (missingAddrs.length < 8) missingAddrs.push(a + i);
      }
    };
    for (const [a, l] of mustWrite) check(a, l, false);
    for (const [a, l] of arenaOk) check(a, l, true);
    return { missing, missingAddrs };
  }

  _inArena(addr) {
    // A declared read is satisfied without a harness write only if the byte is
    // DOL-sourced arena content (I-3). Scratch regions never qualify; neither does
    // untracked bss — live bss state must be written through the codec per case.
    for (const r of this.regions) if (addr >= r.base && addr < r.base + r.size) return false;
    for (const s of this.arenaSegments) if (addr >= s.addr && addr < s.addr + s.size) return true;
    return false;
  }

  /** Post-state byte-diff (mechanism 4). `writeBacks` = [{addr, bytes}] the spec
   *  declares (with reference-predicted values); every other differing byte is a
   *  stray write. Returns {strayWrites:[addr...], writeBackMismatches:[{addr,got,want}]}. */
  diffPostState(writeBacks = []) {
    const wb = new Map();
    for (const { addr, bytes } of writeBacks) {
      for (let i = 0; i < bytes.length; i++) wb.set((addr >>> 0) + i, bytes[i] & 0xff);
    }
    const strayWrites = [];
    const writeBackMismatches = [];
    for (const r of this.regions) {
      const exp = this.expected.get(r.name);
      for (let i = 0; i < r.size; i++) {
        const addr = r.base + i;
        const got = this.u8[addr];
        if (wb.has(addr)) {
          const want = wb.get(addr);
          if (got !== want && writeBackMismatches.length < 8) writeBackMismatches.push({ addr, got, want });
        } else if (got !== exp[i]) {
          if (strayWrites.length < 16) strayWrites.push(addr);
        }
      }
    }
    return { strayWrites, writeBackMismatches };
  }

  // ---- decode primitives (post-state assertion only, per §3.3 direction rule) ----
  rI16(a) { return this.dv.getInt16(a >>> 0, true); }
  rU16(a) { return this.dv.getUint16(a >>> 0, true); }
  rU32(a) { return this.dv.getUint32(a >>> 0, true); }
  rF32(a) { return this.dv.getFloat32(a >>> 0, true); }
}
