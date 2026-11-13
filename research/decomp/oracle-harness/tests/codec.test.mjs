// codec.test.mjs — unit tests for the RomActor codec + coverage machinery.
// Run: node --test research/decomp/oracle-harness/tests/
import test from "node:test";
import assert from "node:assert/strict";
import path from "node:path";
import { fileURLToPath } from "node:url";
import { Codec, loadFieldMap, BlockedCodecError } from "../lib/codec.mjs";

const here = path.dirname(fileURLToPath(import.meta.url));
const fieldMap = loadFieldMap(path.join(here, "..", "actor-field-map.json"));

const BASE = 0x1000;
function makeCodec({ sentinel = 0xa5 } = {}) {
  const buf = new ArrayBuffer(0x10000);
  const u8 = new Uint8Array(buf);
  const dv = new DataView(buf);
  const codec = new Codec({
    u8, dv, fieldMap,
    regions: [{ name: "OBJ", base: BASE, size: 0x800 }],
    arenaSegments: [{ addr: 0x8000, size: 0x100 }],
    sentinel,
  });
  return { codec, u8, dv };
}

test("field map carries the damage-core RomActor fields with correct offsets", () => {
  const f = fieldMap.byInterface.RomActor;
  assert.equal(f.borgNumber.offset, 0x3e8);
  assert.equal(f.borgNumber.kind, "u16be");
  assert.equal(f.slot.offset, 0x3e4);
  assert.equal(f.team.offset, 0x88);
  assert.equal(f.controlWord.offset, 0x5e0);
  assert.equal(f.controlWord.kind, "u32");
});

test("u16be preserves big-endian byte order at the data boundary", () => {
  const { codec, u8 } = makeCodec();
  codec.beginCase();
  codec.encodeField(BASE, "borgNumber", 0x0615); // G RED
  assert.equal(u8[BASE + 0x3e8], 0x06); // family byte first
  assert.equal(u8[BASE + 0x3e9], 0x15); // variant byte second
});

test("sentinel poisoning fills scratch with the sentinel, never zero", () => {
  const { codec, u8 } = makeCodec();
  codec.beginCase();
  assert.equal(u8[BASE], 0xa5);
  assert.equal(u8[BASE + 0x7ff], 0xa5);
});

test("unmapped field is refused (blocked_codec), never guessed", () => {
  const { codec } = makeCodec();
  codec.beginCase();
  assert.throws(() => codec.encodeField(BASE, "ownershipFlags", 1, "RomPartState"), BlockedCodecError);
});

test("port_side field is refused", () => {
  const { codec } = makeCodec();
  codec.beginCase();
  assert.throws(() => codec.encodeField(BASE, "physicsRuntime", 1), BlockedCodecError);
});

test("unknown field is refused", () => {
  const { codec } = makeCodec();
  codec.beginCase();
  assert.throws(() => codec.encodeField(BASE, "noSuchField", 1), BlockedCodecError);
});

test("auditReads: declared read of an unwritten scratch byte is missing", () => {
  const { codec } = makeCodec();
  codec.beginCase();
  codec.wU8(BASE + 0x10, 7);
  const clean = codec.auditReads({ mustWrite: [[BASE + 0x10, 1]] });
  assert.equal(clean.missing, 0);
  const dirty = codec.auditReads({ mustWrite: [[BASE + 0x11, 1]] });
  assert.equal(dirty.missing, 1);
});

test("auditReads: arenaOk satisfied only inside an arena segment", () => {
  const { codec } = makeCodec();
  codec.beginCase();
  const ok = codec.auditReads({ arenaOk: [[0x8010, 4]] });
  assert.equal(ok.missing, 0);
  const bad = codec.auditReads({ arenaOk: [[0x9000, 4]] }); // outside every segment
  assert.equal(bad.missing, 4);
});

test("auditReads: live-bss style mustWrite is NOT satisfied by arena membership", () => {
  const { codec } = makeCodec();
  codec.beginCase();
  const r = codec.auditReads({ mustWrite: [[0x8010, 2]] }); // in arena, but never written
  assert.equal(r.missing, 2);
});

test("post-state byte-diff: stray write detected against the sentinel image", () => {
  const { codec, u8 } = makeCodec();
  codec.beginCase();
  codec.wU8(BASE + 0x20, 1);
  codec.snapshotExpected();
  u8[BASE + 0x300] = 0x00; // unmodeled store (would be invisible against a zero-filled arena)
  const d = codec.diffPostState([]);
  assert.deepEqual(d.strayWrites, [BASE + 0x300]);
});

test("post-state byte-diff: declared write-back with predicted bytes is clean; wrong prediction is a mismatch", () => {
  const { codec, u8 } = makeCodec();
  codec.beginCase();
  codec.wI16(BASE + 0x1c6, 100);
  codec.snapshotExpected();
  u8[BASE + 0x1c6] = 70; u8[BASE + 0x1c7] = 0; // simulated unit write-back (hp 100 -> 70)
  const ok = codec.diffPostState([{ addr: BASE + 0x1c6, bytes: [70, 0] }]);
  assert.equal(ok.strayWrites.length, 0);
  assert.equal(ok.writeBackMismatches.length, 0);
  const bad = codec.diffPostState([{ addr: BASE + 0x1c6, bytes: [71, 0] }]);
  assert.equal(bad.writeBackMismatches.length, 1);
});

test("tuple fields encode element-by-element at their own offsets", () => {
  const { codec, u8 } = makeCodec();
  codec.beginCase();
  codec.encodeField(BASE, "fbPhaseSlots", [1, 2, 3, 4]);
  assert.deepEqual([u8[BASE + 0x544], u8[BASE + 0x545], u8[BASE + 0x546], u8[BASE + 0x547]], [1, 2, 3, 4]);
});

test("struct-kind fields are refused by the scalar encoder (no invented layouts)", () => {
  const { codec } = makeCodec();
  codec.beginCase();
  assert.throws(() => codec.encodeField(BASE, "parts", []), BlockedCodecError);
});


test("synthetic part clock has no source pointer mapping and cannot overwrite continuation bytes", () => {
  const rec = fieldMap.byInterface.RomPartState.frameClock;
  assert.equal(rec.kind, "port_side");
  assert.equal(Object.hasOwn(rec, "offset"), false);
  assert.equal(Object.hasOwn(rec, "width"), false);
  // There is no field-hydration API: decode primitives are explicit post-state
  // assertions only. No mapped field may reinterpret source part+04 as a clock.
  const mapped = Object.values(fieldMap.byInterface.RomPartState)
    .filter(field => Number.isInteger(field.offset));
  assert.equal(mapped.some(field => field.offset <= 4 && field.offset + field.width > 4), false);
  const { codec, u8 } = makeCodec();
  codec.beginCase();
  codec.wU32(BASE + 4, 0x802bc084);
  const before = u8.slice(BASE, BASE + 0x20);
  const writesBefore = codec.writes.length;
  assert.throws(() => codec.encodeField(BASE, "frameClock", 1.5, "RomPartState"),
    error => error instanceof BlockedCodecError && /port_side/.test(error.message));
  assert.deepEqual(u8.slice(BASE, BASE + 0x20), before);
  assert.equal(codec.writes.length, writesBefore);
});

test("host stream cursors and active flags cannot overwrite source wait pointers or completion", () => {
  for (const field of ["streamPtr", "active"]) {
    const record = fieldMap.byInterface.RomPartState[field];
    assert.equal(record.kind, "port_side");
    assert.equal(Object.hasOwn(record, "offset"), false);
    assert.equal(Object.hasOwn(record, "width"), false);
  }
  const mapped = Object.values(fieldMap.byInterface.RomPartState)
    .filter(field => Number.isInteger(field.offset));
  for (const offset of [0, 0x1a]) {
    assert.equal(mapped.some(field => field.offset <= offset && field.offset + field.width > offset), false);
  }
  const { codec, u8 } = makeCodec();
  for (const completion of [0, 1]) {
    codec.beginCase();
    codec.wU32(BASE, 0x802bc080);
    codec.wU32(BASE + 4, 0x802bc084);
    codec.wU8(BASE + 0x1a, completion);
    const before = u8.slice(BASE, BASE + 0x20);
    const writesBefore = codec.writes.length;
    for (const [field, values] of [
      ["streamPtr", [-1, 0, 48, Number.MAX_SAFE_INTEGER]],
      ["active", [0, 1]],
    ]) {
      for (const value of values) {
        assert.throws(() => codec.encodeField(BASE, field, value, "RomPartState"),
          error => error instanceof BlockedCodecError && /port_side/.test(error.message));
        assert.deepEqual(u8.slice(BASE, BASE + 0x20), before);
        assert.equal(codec.writes.length, writesBefore);
      }
    }
  }
});
