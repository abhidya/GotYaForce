# Bespoke Engine Port Plan (2026-07-06)

Goal: 1:1 port of every bespoke attack engine (all borgs, all moves) from boot.dol
to `packages/combat/src/families/*`. This document is the measured scope and batch
order. Machine-generated inputs:

- `research/tasks/bespoke-port-work-queue.json` — per-family detail: every bespoke
  phase table, its phase-function addresses, per-function instruction counts,
  ported/unported flags, and decomp chunk file for each function.
- `research/tasks/bespoke-port-batches.json` — families grouped into port batches
  by shared machine code (>=60% overlapping unported code shapes).

## What the investigation established

The earlier framing ("418 bespoke engines / 2106 leaves") was misleading. Code
fingerprinting of boot.dol (immediates + branch targets masked) shows:

1. The 418 bespoke `engine` addresses in `actionStreamTables.json` collapse to
   **58 unique code shapes, all 14–36 instructions long**. They are not machines —
   they are wrapper/leaf functions. 369 of 418 make no calls at all: they install a
   config block + phase-table pointer and return. The runtime then drives the
   machine via the phase-table dispatch (`(*PTR_xxx[+0x540])()` pattern), same as
   the already-ported families.
2. The real mechanics live in the **phase tables** (the `phaseTable` field already
   extracted per variant). The 418 bespoke variants reference 418 phase tables →
   1774 distinct phase-function addresses → **1161 unique code shapes** after
   cross-family dedup (~71k PPC instructions total, median 57 instrs/function).
3. Subtracting shapes already referenced by existing TS ports leaves
   **1123 unported phase-function shapes ≈ 69.5k PPC instructions**, spread over
   110 families → grouped into **60 port batches**. 333 of those shapes are used
   by more than one family (port once, register many).
4. Only 3 families are already fully covered at the phase level (COPY MAN,
   RED/VIOLET ATTACKER). The existing 159-borg registry covers borgs via shared
   engines + stream playback, but most of their bespoke B-variants still route to
   fallbacks.

Caveats on the numbers:
- Phase tables were read as "up to 8 consecutive code pointers"; adjacent tables in
  the pointer arrays can cause overread (tables reporting 8 phases are suspect).
  Each batch port must confirm true table length from the decomp (`_index.tsv` →
  chunk file) before transcribing.
- Function length = instructions until first `blr` (early returns undercount
  slightly). Good for sizing, not exact.

## Batch order

Phases ordered by borgs-unlocked per instruction ported. Full table in
`bespoke-port-batches.json`; headline batches:

### Phase 1 — multi-family machine clusters (6 batches, ~72 borgs, ~21k instrs)

| Batch | Borgs | Shapes | Instrs | Families |
|---|---|---|---|---|
| Girl cluster | 14 | 59 | 4.3k | BATTLE GIRL, WIRE GIRL, BARRIER GIRL, KILLER GIRL, CYBER GIRL SUPER, DB DELTA II, +2 |
| Robot cluster | 14 | 59 | 3.7k | CLAW/DRILL/BUILD/HAMMER/THUNDER/MAGNET ROBOT, +2 |
| Samurai cluster | 13 | 47 | 2.8k | NORMAL/DEMON SAMURAI, VAMPIRE KNIGHT, SONIC SAMURAI, SAMURAI SHOGUN, DB ZETA |
| Knight cluster | 12 | 104 | 6.3k | SWORD/SPIKE/AXE KNIGHT, DB GAMMA, ALIEN INSECT, SAPPHIRE KNIGHT, +1 |
| Wing cluster | 11 | 51 | 3.0k | WING SOLDIER, JET HERO, DEMON WING, BEAM WING BLUE, ANUBIS WING, DB SIGMA |
| Valkrie cluster | 8 | 15 | 1.0k | 6 VALKRIE variants (identical shape sets), DB LAMBDA, +1 |

### Phase 2 — mid-size families (3–6 borgs each; ~17 batches, ~65 borgs)

FLAME DRAGON, CYBER DEATH DRAGON, NINJA+DB ALPHA, GUNMAN+DB BETA II,
STAR/CYBER/METAL HERO + DB BETA, WITCH trio, ALIEN WORM, MACHINE RED/BLUE,
CYBER MACHINE SEIRYU, VICTORY KING, WIRE GUNNER, G RED, JELLY DIVER, ANGEL NURSE,
KUNG-FU+TAO MASTER, remaining 2-borg families.

### Phase 3 — long tail (~37 batches, 1–2 borgs each, mostly <1k instrs)

Singleton families (SHURIKEN NINJA … ROACH). Many are small (<600 instrs); several
Death Borg/vehicle families are trivial (3–5 shapes).

## Per-batch procedure (wave-B/C pattern, per bridge.ts conventions)

1. From `bespoke-port-work-queue.json`, take the batch's families: phase-table
   addresses, phase-fn addresses, and decomp chunk files
   (`research/decomp/ghidra-export/chunk_XXXX.c`, index `_index.tsv`).
2. Read the decomp for each phase fn; confirm true phase-table length and the
   config block the wrapper leaf installs (wrappers are 14–36 instrs — transcribe
   the config stores, they are the per-variant data).
3. Port the machine to `packages/combat/src/families/<cluster>.ts` as a
   `X_PHASE_TABLE`-style array of TS phase functions (existing model:
   `families/robot.ts:268`, `families/satellite.ts`). Cross-family shapes go in a
   `shared-*.ts` module parameterized by config.
4. Register borgs in `familyRegistry()` (`bridge.ts`) — reuse
   `withBespokeMelee()` / `makeSimpleRegistration()` composition where the family
   already has partial wiring.
5. Verify: `pnpm build` + `node scripts/run-rom-tests.mjs` (rom.selfcheck.ts);
   add per-machine phase-transition asserts. For flagship borgs, golden-trace
   compare via `scripts/trace-golden-record.mjs` / `trace-golden-analyze.mjs`.
6. Update the work-queue JSON flags (re-run the generator; it detects ported
   addresses from TS source automatically).

## Effort estimate

Wave-C shipped ~48 borgs of B-melee in one session using parallel subagents.
Phase 1 batches are comparable per-batch (3–6k instrs each). Realistic pace with
parallel agent porting: 1–3 batches per working session → **Phase 1 ≈ 3–5
sessions (72 borgs), full roster ≈ 15–25 sessions.** The 60-batch structure is
embarrassingly parallel; correctness risk concentrates in step 2 (config-block
extraction) and step 5 (verification), not transcription volume.
