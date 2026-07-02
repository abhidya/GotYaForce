#!/usr/bin/env node
/**
 * assert-ascii-glyphs.mjs — regression check for the HUD bitmap-font mapping.
 *
 * The real `ascii.tpl` atlas (exported to apps/game/public/ui/tpl/ascii/
 * image_00_IA4.png and apps/game/public/ui/hud/font_ascii_atlas.png) is a
 * 128x128 sheet of 8px cells with this layout:
 *   row  0     : blank
 *   row  1     : hex header row "0123456789ABCDEF"  (thin)
 *   rows 2..7  : THIN ASCII block, chars 0x20..0x7E
 *   row  8     : blank
 *   row  9     : hex header row "0123456789ABCDEF"  (bold)
 *   rows 10..15: BOLD ASCII block, chars 0x20..0x7E
 *
 * A past regression mapped chars with no row offset (block assumed at row 0),
 * which rendered "ENEMY" as "%.%-9". This script maps a test string through
 * the same formula as apps/game/src/ui/bitmapText.ts and verifies each mapped
 * cell against ground truth inside the atlas itself:
 *   - digits/hex letters must match the hex header rows pixel-for-pixel-ish,
 *   - the space cell and the two gap rows must be blank,
 *   - the old (offset-less) mapping must NOT match, proving the test has teeth.
 *
 * Run: node scripts/assert-ascii-glyphs.mjs
 */

import { readFileSync } from "node:fs";
import { inflateSync } from "node:zlib";
import { fileURLToPath } from "node:url";
import { dirname, join } from "node:path";

// --- constants mirrored from apps/game/src/ui/bitmapText.ts ----------------
const CELL = 8;
const COLS = 16;
const THIN_ROW_OFFSET = 2;
const BOLD_ROW_OFFSET = 10;
const THIN_HEADER_ROW = 1;
const BOLD_HEADER_ROW = 9;
const BLANK_ROWS = [0, 8];

function atlasCell(char, bold) {
  const code = char.charCodeAt(0);
  if (code < 0x20 || code > 0x7e) return null;
  const idx = code - 0x20;
  return {
    col: idx % COLS,
    row: Math.floor(idx / COLS) + (bold ? BOLD_ROW_OFFSET : THIN_ROW_OFFSET),
  };
}

// --- minimal PNG decode (8-bit depth; gray/rgb/palette/gray+a/rgba) ---------
function decodePng(buf) {
  if (buf.readUInt32BE(0) !== 0x89504e47) throw new Error("not a PNG");
  let pos = 8;
  let width = 0;
  let height = 0;
  let bitDepth = 0;
  let colorType = 0;
  let palette = null;
  let trns = null;
  const idat = [];
  while (pos < buf.length) {
    const len = buf.readUInt32BE(pos);
    const type = buf.toString("ascii", pos + 4, pos + 8);
    const data = buf.subarray(pos + 8, pos + 8 + len);
    if (type === "IHDR") {
      width = data.readUInt32BE(0);
      height = data.readUInt32BE(4);
      bitDepth = data[8];
      colorType = data[9];
      if (data[12] !== 0) throw new Error("interlaced PNG unsupported");
    } else if (type === "PLTE") palette = Buffer.from(data);
    else if (type === "tRNS") trns = Buffer.from(data);
    else if (type === "IDAT") idat.push(Buffer.from(data));
    else if (type === "IEND") break;
    pos += 12 + len;
  }
  if (bitDepth !== 8) throw new Error(`bit depth ${bitDepth} unsupported`);
  const channels = { 0: 1, 2: 3, 3: 1, 4: 2, 6: 4 }[colorType];
  if (!channels) throw new Error(`color type ${colorType} unsupported`);
  const raw = inflateSync(Buffer.concat(idat));
  const stride = width * channels;
  const out = Buffer.alloc(height * stride);
  const paeth = (a, b, c) => {
    const p = a + b - c;
    const pa = Math.abs(p - a);
    const pb = Math.abs(p - b);
    const pc = Math.abs(p - c);
    return pa <= pb && pa <= pc ? a : pb <= pc ? b : c;
  };
  for (let y = 0; y < height; y++) {
    const filter = raw[y * (stride + 1)];
    const line = raw.subarray(y * (stride + 1) + 1, (y + 1) * (stride + 1));
    for (let x = 0; x < stride; x++) {
      const left = x >= channels ? out[y * stride + x - channels] : 0;
      const up = y > 0 ? out[(y - 1) * stride + x] : 0;
      const ul = y > 0 && x >= channels ? out[(y - 1) * stride + x - channels] : 0;
      let v = line[x];
      if (filter === 1) v += left;
      else if (filter === 2) v += up;
      else if (filter === 3) v += (left + up) >> 1;
      else if (filter === 4) v += paeth(left, up, ul);
      out[y * stride + x] = v & 0xff;
    }
  }
  // alpha accessor
  const alphaAt = (x, y) => {
    const i = y * stride + x * channels;
    switch (colorType) {
      case 0:
      case 2:
        return 255; // no alpha channel
      case 3: {
        const pi = out[i];
        return trns && pi < trns.length ? trns[pi] : 255;
      }
      case 4:
        return out[i + 1];
      case 6:
        return out[i + 3];
      default:
        return 255;
    }
  };
  return { width, height, alphaAt };
}

// --- cell helpers ------------------------------------------------------------
function cellMask(png, col, row) {
  const bits = [];
  for (let y = 0; y < CELL; y++) {
    for (let x = 0; x < CELL; x++) {
      bits.push(png.alphaAt(col * CELL + x, row * CELL + y) > 32 ? 1 : 0);
    }
  }
  return bits;
}

function inkCount(mask) {
  return mask.reduce((a, b) => a + b, 0);
}

function similarity(a, b) {
  let same = 0;
  for (let i = 0; i < a.length; i++) if (a[i] === b[i]) same++;
  return same / a.length;
}

// --- assertions ---------------------------------------------------------------
const here = dirname(fileURLToPath(import.meta.url));
const atlases = [
  join(here, "..", "apps", "game", "public", "ui", "tpl", "ascii", "image_00_IA4.png"),
  join(here, "..", "apps", "game", "public", "ui", "hud", "font_ascii_atlas.png"),
];

const HEADER_CHARS = "0123456789ABCDEF"; // header rows spell these, col == index
let failures = 0;

function check(label, ok, detail = "") {
  if (ok) {
    console.log(`  ok   ${label}`);
  } else {
    failures++;
    console.error(`  FAIL ${label}${detail ? ` — ${detail}` : ""}`);
  }
}

for (const path of atlases) {
  console.log(`atlas: ${path}`);
  const png = decodePng(readFileSync(path));
  check("atlas is 128x128", png.width === 128 && png.height === 128, `${png.width}x${png.height}`);

  // Gap rows must be blank (row 0 and row 8).
  for (const row of BLANK_ROWS) {
    let ink = 0;
    for (let col = 0; col < COLS; col++) ink += inkCount(cellMask(png, col, row));
    check(`row ${row} is blank`, ink === 0, `${ink} ink px`);
  }

  for (const [bold, headerRow, name] of [
    [false, THIN_HEADER_ROW, "thin"],
    [true, BOLD_HEADER_ROW, "bold"],
  ]) {
    // The space glyph must map to a blank cell.
    const sp = atlasCell(" ", bold);
    check(`${name} ' ' cell is blank`, inkCount(cellMask(png, sp.col, sp.row)) === 0);

    // Every header char (0-9 A-F) must map to a cell matching the header row.
    for (let i = 0; i < HEADER_CHARS.length; i++) {
      const ch = HEADER_CHARS[i];
      const mapped = atlasCell(ch, bold);
      const got = cellMask(png, mapped.col, mapped.row);
      const want = cellMask(png, i, headerRow);
      const sim = similarity(got, want);
      check(
        `${name} '${ch}' -> cell(${mapped.col},${mapped.row}) matches header`,
        inkCount(got) > 0 && sim >= 0.85,
        `similarity ${sim.toFixed(2)}, ink ${inkCount(got)}`,
      );
    }

    // Teeth: the OLD buggy mapping (no row offset) must NOT reproduce 'A'.
    const buggyRow = Math.floor(("A".charCodeAt(0) - 0x20) / COLS); // no offset
    const buggyCol = ("A".charCodeAt(0) - 0x20) % COLS;
    const buggy = cellMask(png, buggyCol, buggyRow);
    const trueA = cellMask(png, 10, headerRow); // header 'A'
    check(`${name} offset-less mapping of 'A' is wrong (regression tripwire)`, similarity(buggy, trueA) < 0.95);
  }
}

if (failures > 0) {
  console.error(`\n${failures} assertion(s) failed`);
  process.exit(1);
}
console.log("\nall glyph-mapping assertions passed");
