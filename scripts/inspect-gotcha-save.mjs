#!/usr/bin/env node
// inspect-gotcha-save.mjs — Gotcha Force (GG4E) memory-card save (.gci) inspector
//
// Layout derived from the ROM decompile corpus (research/decomp/ghidra-export):
//   serializer/loader   chunk_0014.c (save state machine ~8008ec14 / 8008f1b8)
//   section CRC         zz_008e704_  (chunk_0013.c, 8008e704)
//   digest + scramble   zz_00916c4_ / zz_0091298_ / zz_0091608_ (chunk_0014.c)
//   box & force access  zz_017fe18_ (chunk_0045.c, 8017fe18)
//   shop/collection     zz_01cee38_ (chunk_0056.c, 801cee38)  — 12-byte log array
//   cost lookup         zz_0066168_ (chunk_0008.c, 80066168)  — 6 cost entries per variant = colors
// Full spec: research/format-specs/save-gci-format.md
//
// Usage: tools/node/node.exe scripts/inspect-gotcha-save.mjs [path/to/save.gci]

import fs from 'node:fs';
import path from 'node:path';
import url from 'node:url';

const ROOT = path.resolve(path.dirname(url.fileURLToPath(import.meta.url)), '..');
const gciPath = process.argv[2] ?? path.join(ROOT, 'gotcha_force_100_usa.gci');

const COLORS = ['normal', 'alt', 'gold', 'silver', 'crystal', 'black'];
const SPECIALS = [
  [0x0615, 'G RED'],
  [0x0629, 'NEO G RED'],
  [0x062a, 'G BLACK'],
  [0x0e04, 'GALACTIC EMPEROR'],
];

// ---------- roster (packages/assets/data/borgs.json: array of {id:"pl0615",...}) ----------
const borgList = JSON.parse(fs.readFileSync(path.join(ROOT, 'packages/assets/data/borgs.json'), 'utf8')).borgs;
const roster = new Map(); // numeric (family<<8|variant) -> borg record
for (const b of borgList) roster.set(parseInt(b.id.slice(2), 16), b);

// ---------- GCI container ----------
const file = fs.readFileSync(gciPath);
if (file.length !== 0x40 + 10 * 0x2000) console.warn(`WARN: unexpected file size ${file.length}`);
const data = file.subarray(0x40); // 0x14000 save image

// ---------- CRC (zz_008e704_): CRC-16 poly 0x1021 kept in bits 8..23 of a 24-bit
// register, init 0, next byte OR'd into bits 0..7, result (reg>>8)&0xFFFF.
// Stored big-endian at region[len]; recomputing over region+CRC must give 0.
function crc16(buf, start, len) {
  let reg = 0;
  for (let i = 0; i < len; i++) {
    reg = (reg | buf[start + i]) >>> 0;
    for (let b = 0; b < 8; b++) {
      reg = (reg << 1) >>> 0;
      if (reg & 0x1000000) reg = (reg ^ 0x102100) >>> 0;
    }
  }
  return (reg >>> 8) & 0xffff;
}

// ---------- minimal Shift-JIS decoder (ASCII + fullwidth alnum/space; enough for names) ----------
function sjis(buf) {
  let s = '';
  for (let i = 0; i < buf.length; i++) {
    const b = buf[i];
    if (b === 0) break;
    if (b === 0x81 && buf[i + 1] === 0x40) { s += ' '; i++; continue; }
    if (b === 0x82) {
      const c = buf[++i];
      if (c >= 0x60 && c <= 0x79) s += String.fromCharCode(65 + c - 0x60);       // Ａ-Ｚ
      else if (c >= 0x81 && c <= 0x9a) s += String.fromCharCode(97 + c - 0x81);  // ａ-ｚ
      else if (c >= 0x4f && c <= 0x58) s += String.fromCharCode(48 + c - 0x4f);  // ０-９
      else s += `\\u{82${c.toString(16)}}`;
      continue;
    }
    s += b >= 0x20 && b < 0x7f ? String.fromCharCode(b) : `\\x${b.toString(16).padStart(2, '0')}`;
  }
  return s;
}

// ---------- sections ----------
const SECTIONS = {
  header:      { off: 0x0000, len: 0x2040, scrambled: false },
  s1_options:  { off: 0x2084, len: 0x0040, scrambled: false },
  s2_box:      { off: 0x20c8, len: 0xabe4, scrambled: true },
  s3_force:    { off: 0xccb0, len: 0x2190, scrambled: true },
  s4_progress: { off: 0xee44, len: 0x4628, scrambled: false },
  s5_meta:     { off: 0x13470, len: 0x0258, scrambled: true },
};

console.log('=== GCI header ===');
console.log(`file      : ${gciPath}`);
console.log(`game code : ${file.toString('ascii', 0, 4)}${file.toString('ascii', 4, 6)}  file "${file.toString('ascii', 8, 0x28).replace(/\0.*$/, '')}"  blocks=${file.readUInt16BE(0x38)}`);

console.log('\n=== Section CRCs (zz_008e704_; residual over region+CRC must be 0) ===');
for (const [name, s] of Object.entries(SECTIONS)) {
  const residual = crc16(data, s.off, s.len + 2);
  console.log(
    `${name.padEnd(12)} img+0x${s.off.toString(16).padStart(5, '0')} len=0x${s.len.toString(16).padStart(5, '0')}` +
    ` storedCRC=0x${data.readUInt16BE(s.off + s.len).toString(16).padStart(4, '0')} -> ${residual === 0 ? 'OK' : 'FAIL residual 0x' + residual.toString(16)}`,
  );
}
console.log(`presence flags @0x2042..46: [${[...data.subarray(0x2042, 0x2047)].join(',')}] (options,box,force,progress,meta)`);

// ---------- descramble (zz_0091298_: whole section XOR'd with the single byte
// LUT1[digest0]^LUT2[digest1]; digests live at 0x2047/0x205B/0x206F).
// Key recovery without ROM LUTs:
//   s2/s3: unused space is zero-filled -> key = modal byte value.
//   s5: bytes +0x1D..0x1F are the high bytes of the seconds u32 (always 0) -> key = raw[+0x1d].
function modalByte(off, len) {
  const h = new Uint32Array(256);
  for (let i = 0; i < len; i++) h[data[off + i]]++;
  let best = 0;
  for (let i = 1; i < 256; i++) if (h[i] > h[best]) best = i;
  return best;
}
function descramble(name, key) {
  const s = SECTIONS[name];
  const out = Buffer.from(data.subarray(s.off, s.off + s.len));
  if (s.scrambled) for (let i = 0; i < out.length; i++) out[i] ^= key;
  return out;
}
const s2key = modalByte(SECTIONS.s2_box.off, SECTIONS.s2_box.len);
const s3key = modalByte(SECTIONS.s3_force.off, SECTIONS.s3_force.len);
const s5key = data[SECTIONS.s5_meta.off + 0x1d];
const s2 = descramble('s2_box', s2key);
const s3 = descramble('s3_force', s3key);
const s5 = descramble('s5_meta', s5key);
const s4 = descramble('s4_progress', 0);
console.log(`\nscramble keys: s2=0x${s2key.toString(16)} s3=0x${s3key.toString(16)} s5=0x${s5key.toString(16)}`);

// sanity: s5 timestamp must match the plaintext comment date
const [sec, min, hour, day, mon, year] = [0x1c, 0x20, 0x24, 0x28, 0x2c, 0x30].map((o) => s5.readInt32BE(o));
const stamp = `${String(mon + 1).padStart(2, '0')}/${String(day).padStart(2, '0')}/${year} ${String(hour).padStart(2, '0')}:${String(min).padStart(2, '0')}:${String(sec).padStart(2, '0')}`;
const comment2 = data.toString('ascii', 0x20, 0x40).replace(/\0+$/, '');
console.log(`descramble check: s5 timestamp "${stamp}" vs comment "${comment2}" -> ${stamp === comment2 ? 'MATCH' : 'MISMATCH (bad key?)'}`);

// ---------- header comment ----------
console.log('\n=== Save comment (plaintext, header +0x00) ===');
console.log(`"${data.toString('ascii', 0, 0x20).replace(/\0+$/, '')}" / "${comment2}"`);

// ---------- section 5: metadata ----------
console.log('\n=== Section 5: save metadata (0x258 bytes @img+0x13470) ===');
console.log(`player name  : "${sjis(s5.subarray(0, 0x1a))}"  (Shift-JIS @+0x00)`);
console.log(`last save    : ${stamp}   save count: ${s5.readInt32BE(0x44)}`);
console.log(`console/card id @+0x48: ${s5.subarray(0x48, 0x50).toString('hex')}`);
console.log(`gotcha acquisition counter @+0x50: ${s5.readUInt32BE(0x50)}`);
// per-borg color bitmask arrays (206 bytes each; bit N = color N obtained)
function colorArrayStats(base) {
  let owned = 0, bits = new Array(6).fill(0);
  for (let i = 0; i < 206; i++) {
    const v = s5[base + i];
    if (v) owned++;
    for (let b = 0; b < 6; b++) if (v & (1 << b)) bits[b]++;
  }
  return { owned, bits };
}
const a1 = colorArrayStats(0x58);
const a2 = colorArrayStats(0x158);
console.log(`per-borg color bitmask A @+0x58 : ${a1.owned}/206 borgs flagged; per-color counts [${a1.bits.join(',')}] (normal,alt,gold,silver,crystal,black)`);
console.log(`per-borg color bitmask B @+0x158: ${a2.owned}/206 borgs flagged; per-color counts [${a2.bits.join(',')}]`);

// ---------- section 2: Gotcha Box + acquisition log + GF energy ----------
console.log('\n=== Section 2: Gotcha Box (0xABE4 bytes @img+0x20C8) ===');
// box: 2000 cells x 16 bytes @+0x0000; empty cell id = 0xFFFF
// cell: +0 u16 id (family<<8|variant), +2 u8 color, +3 u8 level, +4 u32 acqSeq, +8 u32 exp, +C u32 unk
const box = [];
let ffCells = 0, zeroCells = 0, junk = [];
for (let i = 0; i < 2000; i++) {
  const o = i * 16;
  const id = s2.readUInt16BE(o);
  if (id === 0xffff) { ffCells++; continue; }
  const row = s2.subarray(o, o + 16);
  if (row.every((b) => b === 0) && !roster.has(0)) { zeroCells++; continue; }
  const e = { cell: i, id, color: s2[o + 2], level: s2[o + 3], acq: s2.readUInt32BE(o + 4), exp: s2.readUInt32BE(o + 8), unk: s2.readUInt32BE(o + 12) };
  if (!roster.has(id) || e.color > 5) { junk.push({ i, hex: row.toString('hex') }); continue; }
  box.push(e);
}
console.log(`box count u16 @sec2+0xABE0: ${s2.readUInt16BE(0xabe0)}  (ROM checks it vs 2000 = box full)`);
console.log(`log count u16 @sec2+0xABE2: ${s2.readUInt16BE(0xabe2)}`);
console.log(`box cells       : ${box.length} occupied, ${ffCells} empty (id=0xFFFF), ${junk.length} unparseable of 2000` +
  `  ${box.length === s2.readUInt16BE(0xabe0) ? '(matches count field)' : '(MISMATCH vs count field!)'}`);
for (const j of junk.slice(0, 5)) console.log(`  junk cell ${j.i}: ${j.hex}`);
const hitRate = box.length ? (100 * box.filter((e) => roster.has(e.id)).length) / box.length : 0;
console.log(`roster-id hit rate: ${hitRate.toFixed(1)}%  distinct ids: ${new Set(box.map((e) => e.id)).size}`);
const hist = (arr, key) => {
  const m = new Map();
  for (const e of arr) m.set(e[key], (m.get(e[key]) ?? 0) + 1);
  return [...m.entries()].sort((a, b) => a[0] - b[0]).map(([k, v]) => `${k}:${v}`).join('  ');
};
console.log(`level histogram : ${hist(box, 'level')}`);
console.log(`color histogram : ${hist(box, 'color')}   (0=normal 1=alt 2=gold 3=silver 4=crystal 5=black)`);
const boxIds = new Set(box.map((e) => e.id));
const missing = [...roster.keys()].filter((id) => !boxIds.has(id));
console.log(`roster coverage : ${roster.size - missing.length}/${roster.size} distinct roster borgs in box`);
if (missing.length && missing.length <= 30)
  console.log(`  not in box: ${missing.map((id) => `${roster.get(id).id}(${roster.get(id).name})`).join(', ')}`);
console.log(`exp>0 entries   : ${box.filter((e) => e.exp > 0).length};  max acqSeq: ${Math.max(0, ...box.map((e) => e.acq))} (vs counter ${s5.readUInt32BE(0x50)})`);
console.log('sample cells:');
for (const e of box.slice(0, 6))
  console.log(`  cell ${String(e.cell).padStart(4)}: 0x${e.id.toString(16).padStart(4, '0')} ${(roster.get(e.id)?.name ?? '???').padEnd(18)} ${COLORS[e.color].padEnd(7)} lvl=${e.level} acq#=${e.acq} exp=${e.exp}`);

// acquisition log: 1000 records x 12 bytes @+0x7D00 (zz_01cee38_ scans 500x0x18 = 2 recs/iter)
// rec: +0 u16 id (0xFFFF empty), +2 u8 color, +3 u8 unk, +4 u32 acqSeq, +8 u32 unk
let logRecs = [];
for (let r = 0; r < 1000; r++) {
  const o = 0x7d00 + r * 12;
  const id = s2.readUInt16BE(o);
  if (id === 0xffff) continue;
  logRecs.push({ r, id, color: s2[o + 2], b3: s2[o + 3], acq: s2.readUInt32BE(o + 4), u8: s2.readUInt32BE(o + 8) });
}
console.log(`acquisition log @+0x7D00: ${logRecs.length}/1000 records used; roster-id hits ${logRecs.filter((e) => roster.has(e.id)).length}`);
if (logRecs.length)
  console.log(`  byte+3 value distribution: ${hist(logRecs, 'b3')}   color distribution: ${hist(logRecs, 'color')}`);

// specials in box/log
console.log('special ids:');
for (const [id, nm] of SPECIALS) {
  const inBox = box.filter((e) => e.id === id).length;
  const inLog = logRecs.filter((e) => e.id === id).length;
  console.log(`  0x${id.toString(16).padStart(4, '0')} ${nm.padEnd(17)}: box x${inBox}, log x${inLog}`);
}

// ---------- section 3: force + member pool + player name ----------
console.log('\n=== Section 3: Force data (0x2190 bytes @img+0xCCB0) ===');
console.log(`player name copy @+0x2174: "${sjis(s3.subarray(0x2174, 0x2190))}"`);
console.log(`u16 @+0x2170: ${s3.readUInt16BE(0x2170)}   member pool count @+0x2172: ${s3.readInt16BE(0x2172)} / 200`);
const pool = [];
for (let i = 0; i < 200; i++) {
  const o = 0x870 + i * 0x20;
  const id = s3.readUInt16BE(o);
  if (id === 0xffff || s3.subarray(o, o + 0x20).every((b) => b === 0)) {
    if (id !== 0xffff && !roster.has(0)) continue;
  }
  if (id === 0xffff) continue;
  if (s3.subarray(o, o + 0x20).every((b) => b === 0)) continue;
  pool.push({ i, id, color: s3[o + 2], level: s3[o + 3], acq: s3.readUInt32BE(o + 4), exp: s3.readUInt32BE(o + 8), f12: s3.readUInt32BE(o + 12), f16: s3.readUInt16BE(o + 16), inLineup: s3.readUInt16BE(o + 18) });
}
console.log(`pool entries: ${pool.length} (0x20 bytes each @+0x870); roster-id hits ${pool.filter((e) => roster.has(e.id)).length}`);
console.log(`pool level histogram: ${hist(pool, 'level')}`);
console.log(`pool color histogram: ${hist(pool, 'color')}`);
for (const [id, nm] of SPECIALS) {
  const hits = pool.filter((e) => e.id === id);
  if (hits.length) console.log(`  pool has 0x${id.toString(16)} ${nm}: ${hits.map((h) => `idx${h.i}(c${h.color},L${h.level},exp${h.exp})`).join(' ')}`);
}
let costSum = 0;
for (const e of pool) costSum += roster.get(e.id)?.energy ?? 0;
console.log(`pool base-cost sum (roster energy): ${costSum}`);

console.log('force slots (20 x 0x6C @+0x0000):');
for (let f = 0; f < 20; f++) {
  const fo = f * 0x6c;
  const st = s3.subarray(fo, fo + 0x6c);
  if (st.every((b) => b === 0)) continue;
  const lineup = [];
  for (let m = 0; m < 30; m++) {
    const idx = st.readInt16BE(0x30 + m * 2);
    if (idx < 0) continue;
    const e = pool.find((p) => p.i === idx);
    lineup.push(e ? `${roster.get(e.id)?.name ?? '0x' + e.id.toString(16)}(${COLORS[e.color] ?? e.color},L${e.level},exp${e.exp})` : `<idx${idx}>`);
  }
  console.log(`  force ${f}: name="${sjis(st.subarray(0, 0x1e))}" lineupCount=${st[0x29]} totalCost=${st.readUInt32BE(0x2c)}`);
  console.log(`    lineup: ${lineup.join(', ') || '(empty)'}`);
}
console.log('full force roster (pool), first 25:');
for (const e of pool.slice(0, 25))
  console.log(`  [${String(e.i).padStart(3)}] 0x${e.id.toString(16).padStart(4, '0')} ${(roster.get(e.id)?.name ?? '???').padEnd(18)} ${(COLORS[e.color] ?? e.color + '').padEnd(7)} lvl=${e.level} exp=${e.exp} acq#=${e.acq}`);
if (pool.length > 25) console.log(`  ... ${pool.length - 25} more`);

// ---------- section 4: story progress (structure mostly UNKNOWN) ----------
console.log('\n=== Section 4: story progress (0x4628 bytes @img+0xEE44, plaintext) ===');
const present = data[0x2045] !== 0;
console.log(`present flag: ${present}`);
// GF energy: zz_0181c30_ returns *(u32*)(s4+0x78) unless mode (*(u32*)(s4+0x40)) == 2, then 2200 (0x898)
const mode = s4.readUInt32BE(0x40);
console.log(`mode u32 @+0x40 : ${mode}${mode === 2 ? '  (mode 2 -> lineup budget forced to 2200)' : ''}`);
console.log(`GF energy @+0x78: ${s4.readUInt32BE(0x78)}  (u32; lineup capacity budget, zz_0181c30_)`);
console.log(`u32 @+0x74      : ${s4.readUInt32BE(0x74)}  (DATA_INFERRED: max GF energy attained?)`);
console.log(`head bytes +0x00..0x07: ${s4.subarray(0, 8).toString('hex')}  (per-save differs; candidate chapter/playthrough counters; byte+6 = ${s4[6]})`);
console.log(`u16 @+0x4520: 0x${s4.readUInt16BE(0x4520).toString(16)} (${s4.readUInt16BE(0x4520)}) — borg id used by shop/collection UI cursor`);
console.log(`nonzero bytes: ${[...s4].filter((b) => b !== 0).length}/${s4.length}`);
