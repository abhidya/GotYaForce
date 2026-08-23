// arena-rom-binding.test.mjs — the arena is real GameCube RAM, and stays that way.
// Run: node --test research/decomp/oracle-harness/tests/
//
// The arena is the static memory image every differential oracle reads (damage
// tables, remap rows, float constants, runtime struct pointers). It carried no
// provenance, so nothing would notice if it drifted away from the console.
//
// gen_arena_rom_provenance.py established the binding once against Dolphin-captured
// MEM1 images and recorded, per segment, the element width and the sha256 of the
// bytes AS THEY APPEAR IN REAL RAM. These tests re-check that binding from the
// tracked arena alone — the MEM1 captures live under user-data/, are gitignored and
// private, and are never required here.
//
// The endianness subtlety this encodes: the arena is little-endian (the port runs on
// wasm), real RAM is big-endian PowerPC, so the arena is an ELEMENT-WISE swapped
// copy at each segment's own width. Compared without that width, arena and RAM agree
// on ~1% of bytes and look catastrophically broken; compared with it, every segment
// is byte-identical.
import test from "node:test";
import assert from "node:assert/strict";
import fs from "node:fs";
import path from "node:path";
import { createHash } from "node:crypto";
import { fileURLToPath } from "node:url";
import { REPO_ROOT } from "../lib/result-integrity.mjs";

const here = path.dirname(fileURLToPath(import.meta.url));
const provenancePath = path.join(here, "..", "arena-rom-provenance.json");
const arenaPath = path.join(REPO_ROOT, "research", "decomp", "poc", "wasm-port-poc", "arena.json");
const MEM1_BASE = 0x80000000;

const sha256 = (buf) => createHash("sha256").update(buf).digest("hex");
const provenance = JSON.parse(fs.readFileSync(provenancePath, "utf8"));
const arenaRaw = fs.readFileSync(arenaPath);
const arena = JSON.parse(arenaRaw.toString("utf8"));

/** Reverse bytes within each width-sized element. */
function swapElements(buf, width) {
  if (width === 1) return Buffer.from(buf);
  const out = Buffer.allocUnsafe(buf.length);
  for (let i = 0; i < buf.length; i += width) {
    for (let k = 0; k < width; k++) out[i + k] = buf[i + width - 1 - k];
  }
  return out;
}

test("the provenance describes the arena that is actually in the tree", () => {
  assert.equal(provenance.provenance_schema, 1);
  assert.equal(
    provenance.describes.sha256,
    sha256(arenaRaw),
    "arena.json changed without regenerating arena-rom-provenance.json — " +
      "rerun gen_arena_rom_provenance.py against the MEM1 captures",
  );
});

test("every arena segment is bound to ROM — none unaccounted for", () => {
  const bound = new Set(provenance.segments.map((s) => s.addr));
  const present = arena.segments.map((s) => s.addr);
  assert.equal(present.length, provenance.segments.length);
  for (const addr of present) {
    assert.ok(bound.has(addr), `arena segment 0x${addr.toString(16)} has no ROM binding`);
  }
});

test("each segment reproduces the exact bytes captured from console RAM", () => {
  const byAddr = new Map(arena.segments.map((s) => [s.addr, Buffer.from(s.b64, "base64")]));
  let totalBytes = 0;
  for (const seg of provenance.segments) {
    const le = byAddr.get(seg.addr);
    assert.ok(le, `arena lost segment 0x${seg.addr.toString(16)}`);
    assert.equal(le.length, seg.size, `segment 0x${seg.addr.toString(16)} changed size`);
    assert.equal(le.length % seg.elem_width, 0, "size must be a whole number of elements");
    assert.equal(
      sha256(swapElements(le, seg.elem_width)),
      seg.rom_be_sha256,
      `segment ${seg.addr_hex} (${seg.note}) no longer matches the bytes captured ` +
        `from real GameCube RAM at ${seg.elem_width}-byte element width`,
    );
    totalBytes += seg.size;
  }
  assert.equal(totalBytes, 13312, "the verified arena is 13,312 bytes");
});

test("a one-byte corruption of any segment is caught", () => {
  // The binding is only worth having if it fails when it should.
  for (const seg of provenance.segments) {
    const le = Buffer.from(arena.segments.find((s) => s.addr === seg.addr).b64, "base64");
    const tampered = Buffer.from(le);
    tampered[0] ^= 0xff;
    assert.notEqual(
      sha256(swapElements(tampered, seg.elem_width)),
      seg.rom_be_sha256,
      `corrupting segment ${seg.addr_hex} went undetected`,
    );
  }
});

test("the recorded element width is the one that matches, not an arbitrary label", () => {
  const byAddr = new Map(arena.segments.map((s) => [s.addr, Buffer.from(s.b64, "base64")]));
  for (const seg of provenance.segments) {
    if (seg.width_ambiguous) continue; // symmetric data (an all-zero constant) matches at every width
    const le = byAddr.get(seg.addr);
    for (const w of [8, 4, 2, 1]) {
      if (w === seg.elem_width || le.length % w !== 0) continue;
      assert.notEqual(
        sha256(swapElements(le, w)),
        seg.rom_be_sha256,
        `segment ${seg.addr_hex} also matches at ${w}-byte width but is not marked ambiguous`,
      );
    }
  }
});

// Deep check: only runs where the private Dolphin captures exist. Absent them the
// test above is already the binding; this one re-derives it from the raw images.
test("direct re-verification against the MEM1 captures, when present", (t) => {
  const traces = path.join(REPO_ROOT, "user-data", "GG4E", "traces");
  const sources = provenance.rom_sources
    .map((s) => ({ ...s, file: path.join(traces, s.name) }))
    .filter((s) => fs.existsSync(s.file));
  if (sources.length === 0) {
    t.skip("MEM1 captures are private local inputs and are not present");
    return;
  }
  const byAddr = new Map(arena.segments.map((s) => [s.addr, Buffer.from(s.b64, "base64")]));
  for (const src of sources) {
    const image = fs.readFileSync(src.file);
    assert.equal(sha256(image), src.sha256, `${src.name} is not the capture the binding was made from`);
    for (const seg of provenance.segments) {
      const offset = seg.addr - MEM1_BASE;
      const window = image.subarray(offset, offset + seg.size);
      assert.deepEqual(
        swapElements(byAddr.get(seg.addr), seg.elem_width),
        window,
        `segment ${seg.addr_hex} diverges from ${src.name}`,
      );
    }
  }
});
