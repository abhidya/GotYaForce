# Bespoke Port Queue — Re-fingerprint Delta (2026-08-03)

Re-ran the bespoke-engine port-work-queue fingerprint against current source.
The 2026-07-06 baseline claimed **1123 unported phase-function shapes (~69.5k
PPC instrs)** across 110 families / 60 batches. A large port wave (≈80 new
family modules, 2026-07-12 → 2026-08-03) has retired a large fraction of that.
Refreshed figures below. Headline unit is **unported PPC instructions** (the
actual transcription debt); shape/address counts are given alongside with their
unit relationship spelled out in §5.

## 1. Headline numbers

| Metric (address-level, exactly reproducible) | OLD 2026-07-06 | NEW 2026-08-03 | Δ |
|---|---:|---:|---:|
| Total phase-function addresses | 1774 | 1774 | 0 |
| Ported addresses | 270 | **677** | +407 |
| Unported addresses | 1504 | **1097** | −407 |
| **Unported instructions (deduped)** | **83 902** | **57 872** | **−26 030 (−31%)** |

| Metric (C-body-fingerprint shapes, reconstructed — see §4) | OLD | NEW | plan PPC unit |
|---|---:|---:|---:|
| Total shapes | 1401 | 1401 | 1161 |
| Unported shapes | 1179 | **813** | 1123 |

| Batches | OLD | NEW |
|---|---:|---:|
| Total | 60 | 60 |
| Fully retired (0 unported) | 0 | **18** |
| Remaining | 60 | **42** |

In the plan's original PPC-shape unit the unported count falls from **1123 → a
projected ≈660 shapes** (scaling the address-level −31% onto the 1161 PPC-shape
base). The authoritative reproducible number is the address-level one above:
**57 872 unported instructions across 1097 distinct addresses.**

## 2. Top-5 families where the real debt still lives (unported instrs)

| # | Family | Unported addrs | Unported instrs |
|---|---|---:|---:|
| 1 | ANGEL NURSE | 45 | 2685 |
| 2 | STAR HERO | 42 | 2628 |
| 3 | POP HONEY | 37 | 2570 |
| 4 | DEATH BORG THETA | 38 | 2548 |
| 5 | BASTET WITCH | 50 | 2513 |

(6–10: PATRA WITCH 2480, BUG WITCH 2216, GUARD WITCH 2061, MACHINE RED 1977,
ELEMENTAL KNIGHT 1764.) Note: families can be *registered* in `bridge.ts`
(e.g. ANGEL NURSE via the lightweight `nurse-wizard-idol.ts` module) yet still
show full bespoke-phase debt — registration wires the borg to shared/fallback
engines; the **bespoke** phase functions remain unported. This is real debt, not
a detection miss (see §4).

## 3. Batches now fully retired (18)

Samurai cluster (NORMAL/DEMON SAMURAI, VAMPIRE KNIGHT, SONIC SAMURAI, SAMURAI
SHOGUN, DB ZETA — was 47 shapes); Valkrie cluster (7 variants + DB LAMBDA — 15);
VICTORY KING (6); DB NU / DEATH EYE (4); COPY MAN (3); PHOENIX DRAGON (9);
COSMIC DRAGON (26); BLUE STRIKER / ORANGE FIGHTER (5); SIRIUS (10);
ACCELERATION NINJA (9); VICTORY JET (4); GOLD HERO (27); BEAM SATELLITE (5);
DEATH SAUCER (5); ANTARES (6); DB MU (4); DB CHI (3); ROACH (3).

These 18 batches carried **10 293 instructions** in the original fingerprint-dedup
batch units (the bulk: Samurai 2832, Gold Hero 1586, Cosmic Dragon 1112). The
remaining ~15.7k of the 26 030-instruction reduction came from **partial
progress** inside the 42 still-open batches (e.g. the Girl/Robot/Knight clusters
are mostly-but-not-fully ported). **42 batches remain**, dominated by the
witch/nurse cluster, the STAR/METAL hero family, MACHINE RED, and the long tail
of singletons.

## 4. Methodology — what was repaired

**The original generator does not exist in the repo.** `bespoke-engine-port-plan.md`
references `scripts/.../classify_fleet` + a "fingerprinting driver", but
`git log --diff-filter=D` shows neither was ever committed (the work-queue JSON
landed in `7e582ace` with no script alongside, and no later deletion exists).
The boot.dol PPC-disassembly pipeline that produced the plan's
"inmediates + branch targets masked" shape fingerprint is therefore
**unreproducible** here. Path taken: **(b) fresh fingerprinting pass that emits
the same JSON shape** — `scripts/gen-bespoke-port-queue.mjs`.

That script reuses the **frozen inventory** (every phase-function address,
instruction length, family grouping, phase-table address, decomp chunk file)
verbatim from the 2026-07-06 `bespoke-port-work-queue.json`. The inventory is
immutable — the decomp corpus (`chunk_*.c`, 80 files) is unchanged — so only the
**ported detection** had to be recomputed:

- **Augmented address harvest** (beyond the plan's bare `0x80xxxxxx` literal
  rule). Ported modules cite phase functions overwhelmingly as Ghidra names —
  `FUN_80xxxxxx` and `zz_<hex>_` — not as hex literals. All three forms are now
  harvested from `packages/combat/src/families/*.ts`, `packages/combat/src/rom/*.ts`,
  and `packages/combat/src/bridge.ts`, normalized to `0x80xxxxxx`, and
  intersected with the inventory address set. 86 TS files scanned; 2000 cited
  addresses; **677** are inventory phase functions (vs the JSON's stale 270).
- **C-body-fingerprint shape reconstruction** (cross-check only). Since the PPC
  fingerprint is gone, shapes were rebuilt from the decomp C corpus: each
  function body is normalized (hex/decimal literals and `FUN_/zz_/DOUBLE_/…`
  references masked) and hashed. This yields **1401 shapes** from 1708/1774
  bodies (66 unparseable → treated as singletons) — ~15% more granular than the
  plan's 1161 PPC-shapes (the C unit normalizes less aggressively than masked
  PPC). The OLD unported figure (1179 C-shapes) lands within 5% of the plan's
  1123, validating the reconstruction is in the right zone.
- **Phase-table-citation rule tested and rejected.** Per task step 4, a rule
  marking every fn in any cited table as ported was tried. It jumps ported to
  1048 addrs / 37 287 unported instrs but produces **354 fully-ported phase
  tables vs the slot audit's 191** — many table addresses are cited in
  documentary comments for fallback/shared paths, not bespoke porting. It is
  reported in the generator output only as an **optimistic upper bound**.

The address-only detection is the calibrated primary: its **227 fully-ported
phase tables** is the closest match to the independent slot audit.

## 5. Unit reconciliation (shape vs address vs slot)

The plan's "1123" and the audit's "partial=132" are **different units** — they
must not be compared directly:

- **Address** — distinct phase-function memory location (deduped across
  families). 1774 total, 1097 unported now. Exactly reproducible; the headline.
- **Shape** — distinct code body after fingerprint dedup (several addresses can
  share one shape). 1401 C-shapes (1161 in the plan's PPC unit). Always ≤
  address count.
- **Slot** — distinct `(borg, action, variant)` dispatch entry in
  `family-state-machine-classifications.reviewed.json`: **ported=191,
  partial=132, missing=2** (325 slots). Many slots share one shape/address
  (cross-family code reuse), so slot counts are the coarsest grain.

Phase-table coverage (a slot proxy, one level finer than the audit) under the
new detection: **227 tables fully ported, 153 partial, 208 untouched**. The
fully-ported count (227) sits just above the audit's ported slots (191) and the
partial count (153) just above the audit's partial slots (132) — consistent, the
excess because a phase table can back several member/variant slots. This is the
corroboration the task asked for: the refreshed queue and the independently
regenerated audit agree to within expected unit drift.

## 6. Caveats (carried from the plan, still in force)

- Phase-table overread: tables read as "up to 8 consecutive pointers" can
  over-count phases. Ports correct true length per decomp (e.g.
  acceleration-ninja.ts notes "work-queue overread 8 → 3"). The inventory is
  not re-corrected here; the `len`/phase counts are the 2026-07-06 reads.
- Function length = instructions to first `blr` (early returns undercount
  slightly). Sizing, not exact.
- Lightweight-registered families (module exists, borg in `bridge.ts`, but only
  ctor/bank cited — no bespoke phase fns) correctly read as bespoke-unported.

## 7. Re-run

```
node scripts/gen-bespoke-port-queue.mjs
```

Reads the frozen inventory + decomp corpus + current TS; rewrites
`research/tasks/bespoke-port-work-queue.json` (refreshed `done` flags +
per-family counts) and `research/tasks/bespoke-port-batches.json` (refreshed
per-batch unported addr-union counts). Idempotent: the OLD baseline is read
from `git HEAD` so repeated runs do not drift.
