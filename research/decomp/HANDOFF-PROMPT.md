# Hand-off prompt: fix the GotchaForce web port against the real ROM decomp

Paste this whole thing as the opening message of a new session (Claude Code / Cowork / any
agent with file + shell access to this repo) to continue the work.

---

## Context

This repo (`D:\GotYaForce`) is a from-scratch TypeScript/web port of **Gotcha Force**, a GameCube
fighting game (GG4E, NTSC-U). The port lives in `packages/*` (combat, physics, ai, render, ui,
audio, assets, core, save, formats) and `apps/game` (the actual playable web app, Vite-based).
`packages/assets/data/borgs.json` and `stages.json` are the parsed roster/stage data.

Large parts of the port were originally built by guessing reasonable-feeling values (TUNED
constants) because nobody had reverse-engineered the actual GameCube binary. That changed this
session: we stood up Ghidra with the community `Ghidra-GameCube-Loader` extension against the
real `user-data/GG4E/disc/sys/boot.dol`, and — critically — **bulk-decompiled the entire binary**
(11,972 functions) to `research/decomp/ghidra-export/` so it's a searchable reference instead of
something you re-derive by hand. Read `research/decomp/ghidra-export/README.md` first — it
explains the corpus format and has a table of every function/table confirmed so far.

**Ground rule that matters more than any individual finding:** this repo uses a DERIVED vs.
TUNED confidence convention in code comments (see `packages/combat/src/constants.ts`'s header).
DERIVED = confirmed from the ROM (decompiled C, live memory trace, or raw binary data — cite the
address/evidence). TUNED = a reasonable guess, explicitly labeled as such. **Never silently
upgrade a TUNED value based on a guess or partial match** — wrong-but-confident data is worse
than honestly-labeled TUNED data, because it stops looking like something that needs checking.
When you find something new, update `research/decomp/behavior-notes.md` (append a new lettered
section, don't renumber existing ones) with the address/evidence before touching any TS code.

## What's already confirmed (don't re-derive these)

Full detail in `research/decomp/behavior-notes.md` sections (h) through (l). Summary:

- HP field, subtract-and-clamp, and a "linked object" HP-mirror mechanic: `zz_003d344_` @
  `0x8003d344`. Ported in `packages/combat/src/combat.ts`.
- `object+0x88` mismatch branch exists in `zz_002e2a8_`, but a later export re-read (§m) shows
  `+0x88` is match slot/team state copied from `PTR_DAT_80433934[slot+0xcb]`, not the five-value
  `borgs.json.type` display string. `DAMAGE.TYPE_MISMATCH_DIVISOR` is documented but not applied
  from display type in `combat.ts`.
- The *real* base-damage formula is `zz_003cd5c_` @ `0x8003cd5c` — a multi-stage multiplicative
  formula (base power, HP-ratio scaling, attacker "rank" table, defender category tables), not
  the linear `BASE + stat*PER_STAT` currently TUNED in `constants.ts`. Not ported — see "Priority
  1" below.
- Knockback is a computed 3D **direction** (`zz_00300bc_` @ `0x800300bc`, 5 vector-source modes),
  not a flat scalar. `MELEE.KNOCKBACK`/`HITSTUN` etc. are still flat TUNED placeholders.
- A genuine type-effectiveness system: `research/decomp/data/type-category-remap-802f2e28.json`
  (raw ROM table, byte->byte category normalization) feeding
  `research/decomp/data/type-multiplier-matrix-802c5d60.json` (a real 20x20 float matrix read
  directly out of the ROM's data section — mostly neutral 1.0, 26 cells with real ±5-25%
  modifiers). **Not wired to any borg yet** — see "Priority 1".
- "Defense" is not a percentage in the ROM at all; `DAMAGE.DEF_PER_STAT`/`MIN_MULT` are an
  intentional simplification of a table-driven system, documented as such — don't try to
  "discover" a defense percentage, there isn't one.

## Priority 1 — resolve `object+1000` category/source mapping (highest value, well-scoped)

The blocker on using the real type matrix: which borg maps to which of the 20 categories.
`behavior-notes.md` sections (l)/(m) have the corrected state: the earlier `Number`/`0x3c`-stride
hypothesis was tested and refuted, and `object+0x88` is slot/team state. The real subtle type
matrix uses `object+1000`, which is copied from `PTR_DAT_80433934[slot*2 + 0x10]` in active spawn
paths; resolving what populates that slot table is the next target.

1. Grep the export for writers to `PTR_DAT_80433934 + slot*2 + 0x10`, `slot+0xa0`, and
   `slot+0x20/0x32/0x3e`, starting from `chunk_0048.c` and `chunk_0006.c`.
2. Trace those writers back to roster/mission selection data, then persist the discovered
   `slot/borg -> object+1000 -> canonical category` evidence into `research/decomp/data/`.
3. Once confirmed, wire the real 20x20 matrix into combat as a separate derived multiplier.
   Do not use `borgs.json.type` or `object+0x88` for this mapping.

## Priority 2 — real base-damage formula

`zz_003cd5c_` (`0x8003cd5c`) is only partially decoded (see behavior-notes.md §j/§k). To finish:
grep it out of `research/decomp/ghidra-export/chunk_0004.c` (search `_index.tsv` for the address
first), and name the remaining `FLOAT_804...` constants and the `PTR_DAT_804335e0`-family small
tables by reading their raw values the same way the type matrix was read (see
`research/decomp/data/*.json` for the pattern — reuse `dol.py`'s section/offset helpers). Only
replace `MELEE.DMG_BASE`/`DMG_PER_STAT`/`SHOT.DMG_BASE`/`DMG_PER_STAT` in `constants.ts` once the
full formula and all its table inputs are confirmed — a half-ported multiplicative formula is
worse than the current honest linear TUNED model.

## Priority 3 — knockback direction

`zz_00300bc_` (`0x800300bc`) computes launch direction from 5 modes. Finish decoding the
angle-offset table it reads (indexed by `param_1[0x11]`, a per-move byte) and port the direction
calc into `packages/physics`/`packages/combat` so knockback pushes borgs in the ROM-accurate
direction instead of a fixed vector.

## Priority 4 — the broader ask: UI, map mechanics, assets

The user's actual goal is fixing the **whole web port**, not just combat math. The bulk-decompile
corpus (`research/decomp/ghidra-export/`) covers the *entire* binary, so the same
grep-the-corpus-then-cross-reference approach applies to any other system:

- **UI/HUD state**: search the corpus for functions referencing known HUD memory addresses
  (`0x803b069c` and friends, from `behavior-notes.md` §f — note §k found this address is also
  read as a lookup table elsewhere, so verify context before assuming "HUD" in every hit) and
  cross-reference against `packages/ui` and `apps/game/src/ui`.
- **Map/stage mechanics**: `packages/assets/data/stages.json` and whatever reads stage bounds/
  collision in `apps/game/src/sim` — grep the corpus for stage-loading functions (search
  `_index.tsv` for names near known stage-related symbols in the community `.map` file) and
  compare against what the port currently assumes for bounds/collision.
- **Asset/animation ID mapping**: `research/format-specs/hit-bin-format.md` and the various
  `scripts/inspect-*`/`scripts/inventory-*` scripts already probe raw asset files
  (`plxxxxhit.bin`, `comhit.bin`, etc.) — the `puVar17` per-move data pointer identified in
  §j/§k of behavior-notes.md is the best lead yet for finally cracking that format; cross-reference
  field offsets found in `zz_003cd5c_` (`puVar17[0]`, `puVar17[7]`, `puVar17[8]` bit flags) against
  the raw `.bin` file layouts these scripts already parse.
- For anything not yet touched, the workflow is always: **grep `research/decomp/ghidra-export/`
  for the relevant function/data by name or address -> read it -> cross-reference against the
  specific `packages/*` or `apps/game` file that currently guesses that behavior -> update code
  AND `behavior-notes.md` together, never one without the other.**

## Tooling notes (so you don't re-discover these)

- The Ghidra project is at `research/decomp/GotchaForce` (open via Ghidra's Project Manager, not
  by opening `boot.dol` directly). The bulk-export script that generated the corpus is
  `DumpAllDecompiledJ.java` (Java, not Jython/PyGhidra — this Ghidra install has no Jython
  extension installed; Java scripts run fine from Ghidra's Script Manager).
- Raw ROM data (as opposed to function code) is read directly from `user-data/GG4E/disc/sys/boot.dol`
  using the section-table parser already in `research/decomp/dol.py` (`addr_to_off`, `read_u32`,
  `read_f32` — extend with `read_s16`/pointer-following as needed, see
  `research/decomp/data/*.json` generation for the pattern).
- Full matching decompilation (byte-identical recompilation) is intentionally not pursued.
  It is NOT a blocker — it's the wrong tool for this project. Matching decomp only pays off
  when the goal is recompiling the original binary (preservation projects, native ports); this
  port targets TypeScript and never recompiles PowerPC, so even a complete matching toolchain
  would add nothing over the bulk-decompile-and-grep corpus, which already answers every
  "what does the ROM do here" question the port needs.
- After any code change in `packages/combat` (or elsewhere), verify with a scratch TypeScript
  compile — the repo's own `pnpm`-managed `node_modules/typescript` symlink is broken in at least
  one prior sandbox environment; if `tsc -b` fails with an I/O error on the symlink, copy the
  changed files into a scratch dir with a fresh local `npm install typescript` and compile there
  instead of concluding the code itself is broken.

## First message to send after reading this

State which Priority you're starting on and why, then proceed. Don't ask for permission to grep
the corpus or read `dol.py`-style raw data — that's all local, already-owned research material.
Do ask before wiring an unconfirmed mapping into gameplay-affecting code.
