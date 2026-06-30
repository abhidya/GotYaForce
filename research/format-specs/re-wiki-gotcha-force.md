# NeoGF RE Wiki — Gotcha Force format specs (transcribed)

> **Source:** Virtual-World-RE "RE" wiki — https://wiki.re.virtualworld.fr/index.php/Gotcha_Force
> and https://wiki.re.virtualworld.fr/index.php/Implementations
> **Fetched:** 2026-06-30 (NOT robots-blocked from this host — WebFetch succeeded).
> **Note on host:** The repo README and `data/README.md` reference the wiki as
> `re.wiki.virtualworld.fr`. That host **refused connection** (ECONNREFUSED) during this fetch.
> The working host is **`wiki.re.virtualworld.fr`** (the two labels are swapped). Use the working
> host. If a future fetch is blocked, the pages must be read manually in a browser.
> Content below was returned by an automated fetch+summarize and should be spot-checked against the
> live page before being treated as canonical (the summarizer may paraphrase).

---

## 1. File-format table (from /index.php/Gotcha_Force)

| Format | Content (per wiki) |
|--------|--------------------|
| ADX | Audio file |
| AFS | File packing other files (CRI top-level archive) |
| **ARC** | **HSD Files** |
| ARZ | Compressed file |
| BIN | Unknown |
| BNR | Banner file format |
| CHD | **DSP part** |
| DOL | Executable file |
| DPK | **DSP part** |
| IMG | Apploader file |
| MDT | Uncompressed packed files which contain dialogs |
| PTL | Particles settings |
| PZZ | Compressed archive |
| REF | Unknown (related to particles?) |
| SFD | MPEG Sofdec |
| TPL | Texture Palette Library |
| TSB | **DSP part** |
| TXG | **Particles images container** |

### Key correction vs PHASE0_RESEARCH.md §4

PHASE0 marked `chd`, `dpk`, `tsb` as "Unknown (model/scene?)" and `txg` as "texture group?
(Capcom Made in Japan stamps)". **The RE wiki instead labels CHD / DPK / TSB as "DSP part" (i.e.
audio / DSP-related, NOT geometry) and TXG as "Particles images container" (particle textures, NOT
the borg texture container).** This significantly narrows the model-format search: per the wiki,
the geometry lives under **ARC = HSD Files** (and inside `pzz` / `_mdl.arc`), and CHD/DPK/TSB are
likely audio-DSP rather than mesh/scene data. Treat this as a wiki claim to verify by magic-byte
sniff during disc extraction — it conflicts with the earlier spriters-resource forum framing that
lumped chd/dpk/tsb/txg in with the "unsolved model blocker."

### ARC note (verbatim sense)

"ARC" entries are designated **"HSD Files"**, referring to the **HAL Sysdolphin engine embedded in
the main executable**. (Consistent with PHASE0's identification of `_mdl.arc` as HSD-lineage. NB:
PHASE0's verification ledger records the stronger "HSD statically linked into boot.dol" claim as
**Refuted 0-3** — the wiki's "embedded in the main executable" phrasing restates exactly the claim
to remain skeptical of. Test HSDLib against a real `_mdl.arc` before relying on it.)

### Borg acquisition cinematics

`gets*` cinematic files are used when acquiring new Borgs; e.g. `gets06_mdl.arc` is for obtaining
Neo G Red and its color variants. Data Crystals are looted in battle and combined to earn new Borgs.

---

## 2. Borgs GET system (from /index.php/Implementations)

**Core mechanic:** When you eliminate the enemy borg of a given colour, that colour's GET counter
increments by a **random value between 1 and 16**. When the accumulated counter **reaches or exceeds
the borg's GET value threshold**, the player obtains the borg and **the counter resets to zero**.
**Abandoning or losing a battle reverts all counters to their pre-battle states.**

**GET value examples:**
- Gold Death Borg Alpha: **40**
- Galactic Emperor: **-1** (special case)

**No-GET-requirement borgs** (bypass the system entirely): Cyber Death Dragon, Machine Dragon, G Red.

**Worked implication:** A GET value of 40 cannot be reached in two consecutive battles even with
maximum increments (2 × 16 = 32), so some borgs require multiple battle attempts.

**Datasets:** the NeoGF repo ships regional GET-value datasets — see
`research/symbols/eu_borgs_GET_values.csv` (EU, credited to CrystalPixel) and
`research/symbols/NTSC_Borgs.csv` (USA borg stats). Use these as the source of truth for the
gacha/economy port (browser caps: 2000 borgs / 1000 data crystals per PHASE0).

---

## 3. NeoGF repo `doc/` folder (NOT robots-blocked — repo-local)

The NeoGF repo `doc/` folder contains:
- `README.md` — one line: "Documentation that could help".
- **`Virtual World RE - Files patching process 1.0.7.pdf`** (~915 KB). This is a **patching how-to**,
  not a binary-format spec. Could not be auto-transcribed here (no `pdftoppm` / PyPDF2 / pdfminer /
  PyMuPDF available in the Python 3.7.3 / Anaconda environment). Its workflow is the standard
  extract→edit→repack chain already documented in the per-tool READMEs:
  `gcmtool --unpack` (GCM/ISO) → `afstool --unpack` (AFS) → `pzztool -unpzz` (PZZ, auto-decompresses
  ARZ) → edit members (keep filename parts intact) → `pzztool -pzz` → `afstool --pack` →
  `gcmtool --pack`. **To read the PDF, open it manually or install a PDF text extractor**
  (e.g. `pip install pymupdf`) and re-transcribe here.

The richest repo-local format documentation is actually the **per-tool README.md files**
(`tools/NeoGF/{gcmtool,afstool,pzztool,mdttool,mottool,doltool}/README.md`), which document the
PZZ member-naming scheme, AFS TOC/FD rebuild config, MDT text layout, and DOL section/AR-patch model.
These are the gold and are not robots-blocked.

---

## 4. To-verify list (manual browser pass)

If/when read manually in a browser, double-check on the live wiki:
1. The exact file-format table cell text (this transcription is an automated summary).
2. Whether any **per-format binary header/offset spec** pages exist beyond the summary table
   (e.g. dedicated PZZ / ARZ / ARC structure pages linked from the main article).
3. The full **Implementations** page for any additional systems beyond the GET system
   (RNG seeding, counter storage addresses, full per-borg GET value table).
4. Confirm the CHD/DPK/TSB = "DSP part" and TXG = "Particles images container" labels against any
   sample files once a disc is extracted (magic-byte sniff).
