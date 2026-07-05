---
title: Disc / ISO Layout
---

# Disc / ISO layout

Filesystem, AFS TOC, hashes, and magic-by-extension forensics for the GG4E
NTSC-U disc.

**Source:** `research/disc/GG4E/` (16 forensics files)

## Forensics index

| File | What |
|---|---|
| `header.bin` / `parse_header.py` | Disc header parse |
| `fst.bin` / `parse_fst.py` | Filesystem table |
| `fst-counts.txt` | File counts by directory |
| `magic-by-ext.txt` | Magic numbers grouped by extension |
| `crc32.txt` / `md5.txt` / `sha1.txt` | Hash manifests |
| `afs_internal.txt` / `afs_subfile_magics.txt` | AFS archive internals |
| `_files_manifest.tsv` | Full file manifest |

## Pipeline

```text
disc.iso ──► DVD/FST ──► AFS archives ──► .arc (HSD DAT) ──► JOBJ / TPL / MOT
```

ADX audio streams are encrypted; key recovered via `degod` / `guessadx`
brute-force (see `research/PHASE0_RESEARCH.md`).
