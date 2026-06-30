#!/usr/bin/env node
// extract-user-disc.mjs — orchestrates user-disc extraction: gcmtool -> afstool -> pzztool (+ARZ).
//
// Drives the EXISTING Python tools (NeoGF; cloned into ./tools by another step). This is a
// STUB: it documents the exact sequence and validates inputs; the spawn wiring is TODO.
//
// Usage:
//   node scripts/extract-user-disc.mjs <REGION> <path-to-iso>
//   # REGION is GG4E (USA) | GG4J (Japan) | GG4P (PAL)
//   # e.g.  node scripts/extract-user-disc.mjs GG4E user-data/GotchaForce_GG4E.iso
//
// The ISO is USER-SUPPLIED and never committed. Extracts land under user-data/ (gitignored);
// hashes/FST/magic maps land under research/disc/<REGION>/ (gitignored). Fabricate no hashes.
//
// --- Exact command sequence (PHASE0_RESEARCH.md §5) -----------------------------------
//
//   # 1. Hashes FIRST, per region -> research/disc/<REGION>/<REGION>.hashes
//   sha1sum  GotchaForce_<REGION>.iso
//   md5sum   GotchaForce_<REGION>.iso
//   crc32    GotchaForce_<REGION>.iso          # or: rhash --crc32
//
//   # 2. Header / Disc ID (4-char game code at offset 0) -> confirm GG4E/GG4J/GG4P
//   xxd -l 0x20 GotchaForce_<REGION>.iso
//
//   # 3. Unpack disc (NeoGF gcmtool — GF-aware, preferred)
//   python gcmtool.py -u GotchaForce_<REGION>.iso ./extract_<REGION>
//   #   alt: nod extract ... ./extract_<REGION>
//   #   alt: wit EXTRACT ... --DEST ./extract_<REGION>
//
//   # 4. Inspect sys/ and record main.dol hash (DOLs differ across regions)
//   ls -l ./extract_<REGION>/sys/             # boot.bin, bi2.bin, apploader.img, main.dol
//   sha1sum ./extract_<REGION>/sys/main.dol
//
//   # 5. FST tree + file counts by extension
//   find ./extract_<REGION>/files -type f | sed 's/.*\.//' | sort | uniq -c | sort -rn
//
//   # 6. Magic-byte sniff -> research/disc/<REGION>/magic.txt (bucket chd/dpk/tsb/txg)
//   for f in $(find ./extract_<REGION>/files -type f); do
//     printf '%s: ' "$f"; xxd -l 8 "$f" | head -1; done > research/disc/<REGION>/magic.txt
//
//   # 7. DOL analysis (decomp-toolkit); symbol map is GG4E-only
//   dtk dol info ./extract_<REGION>/sys/main.dol
//   dtk dol split ./extract_<REGION>/sys/main.dol --map GG4E-CSM-20220412.map   # USA only
//
//   # Then, per AFS member: afstool unpack; per PZZ: pzztool unpack; pzztool -d for ARZ.
//
// On Windows use `python` + Git Bash equivalents, or a .cmd wrapper:  extract-user-disc.cmd
// On POSIX a thin shell wrapper works:                               extract-user-disc.sh

const [region, isoPath] = process.argv.slice(2);

if (!region || !isoPath) {
  console.error("usage: node scripts/extract-user-disc.mjs <GG4E|GG4J|GG4P> <path-to-iso>");
  process.exit(1);
}

// TODO: validate region in {GG4E,GG4J,GG4P}; confirm iso exists under user-data/.
// TODO: hash the ISO (sha1/md5/crc32) -> research/disc/<region>/<region>.hashes (no fabrication).
// TODO: spawn gcmtool -> afstool -> pzztool (+ -d ARZ) per the sequence above.
// TODO: emit FST tree + extension counts + magic.txt.
console.log(`[stub] would extract ${region} from ${isoPath} per PHASE0 §5 — not yet implemented.`);
