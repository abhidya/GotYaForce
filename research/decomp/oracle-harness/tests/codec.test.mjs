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
