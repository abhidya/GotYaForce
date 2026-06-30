# Gotcha Force — 1-to-1 UI Fidelity Spec (GG4E)

> **Rule for ALL UI work:** reproduce the original game's screens using the EXTRACTED REAL ASSETS below.
> Do NOT invent layouts, bars, buttons, fonts, or colors. If a screen's exact layout is unknown,
> mark it `LAYOUT: needs reference capture` and stop — do not improvise a design.
> Source art lives in `apps/game/public/ui/` (extracted from the disc; provenance in `public/ui/provenance.json`).

## Status of the current implementation (what to fix)
`src/main.ts` (~line 649, `ui.innerHTML = ...`) currently INVENTS the UI:
- HUD energy bars are hardcoded `<div class="bar"><span style="width:72%">` — **fake**. Must be the real GF-energy meter art driven by real values.
- "Create room" / "Join room" / force-builder use custom HTML/CSS buttons — **not the game's screens**.
- Real asset images are used but arranged in a made-up layout.
**Target:** each screen below rebuilt to match the original, using the listed real assets.

## Control scheme (CONFIRMED — from extracted in-game controls screen `ui/hsd/nwld00_mdl/texture_000`)
Original GameCube mapping → our keyboard/gamepad binding (keep 1-to-1 semantics):
| Action (JP label) | GC input | Web binding (proposed) |
|---|---|---|
| 移動 Move | Control stick | WASD / left stick |
| ステップ・かいひ Step/dodge | stick + ? | Shift / B-face |
| ジャンプ Jump | **A** | Space / A |
| こうげき Attack | **B** | J / X |
| 特殊攻撃 Special attack | **Y** | K / Y |
| ロックオン Lock-on | **R** | L / RT |
| ロックオンきりかえ Switch lock-on | **Z** | Tab / RB |
| みかた ロックオン Ally lock-on | (modifier) | — |

## Screen inventory → real assets (extracted)
Asset counts by category (from `public/ui/manifest.json`): portraits/banners/fonts 503 · battle HUD 301 · force setup 223 · mission intro/load 95 · main menu 8 · Adventure select 7.

| Screen | Real source assets (public/ui/...) | Notes / LAYOUT status |
|---|---|---|
| Boot splash | `tpl/titles/image_00_I4.png` (Sofdec/ADX logos) | shown at boot; exact |
| Title screen | `tpl/eyecatch*/` , `tpl/titles/` | LAYOUT: needs reference capture |
| Main menu | `hsd/optn00_mdl/texture_000_CI4.png` (384×224), `tpl/font_00/` | LAYOUT: needs reference capture |
| Adventure/Story select | `hsd/nwld00_mdl`, `nwld01_mdl`, `nwld02_mdl` (592×400 world screens) | LAYOUT: needs reference capture |
| Mission intro / load | `tpl/acd_end/` (640×448), `tpl/eyecatch*` | full-screen images, exact |
| Force / team setup | `hsd/box00_mdl/` (the Gotcha box), `hsd/gets00_mdl/` (GET strip 448×64), `hsd/entry00_mdl/`, `hsd/brif00_mdl/` | LAYOUT: needs reference capture |
| Borg portraits (menus) | `hsd/face****_mdl/` (per-borg face models) | one per borg, keyed by borg code |
| In-battle HUD — name banner | `tpl/bn<code>/image_00_CI4.png` (448×64 per borg) | top of HUD; real per-borg name plate |
| In-battle HUD — mini icon | `tpl/mn<code>/image_00_CI4.png` | borg mini icon |
| In-battle HUD — GF-energy meters | **battle-HUD category assets (301)** — find the real meter sprite (gauge frame + fill) | currently FAKE; replace with real gauge art driven by force energy totals |
| Results / podium | `hsd/rpot20_mdl`..`rpot23_mdl` (640×448) | end-of-battle |

> The `bn<code>`/`mn<code>` mapping uses the borg UI code (see `borgUiCode()` in main.ts). Energy meter values come from `packages/assets/data/borgs.json` (`energy` per borg) summed over the force, per the real rule (your green meter = remaining force cost, enemy red meter = theirs).

## LIVE-CAPTURE FINDINGS (2026-06-30 — observed in the real game via Dolphin, windowed)

These are the ACTUAL layouts of the original game. Implement to match these, not invented designs.

## ⭐ CHALLENGE MODE — the canonical flow for our online recreation (REAL CAPTURES)
Our 1–4 player energy-budget game is modeled on **Challenge mode** (NOT Story). Real native-res screenshots are in `apps/game/reference/captures/` — build each screen to match its image:

| # | Screen | Reference image | What it establishes |
|---|---|---|---|
| 1 | Main menu | `captures/challenge-1-main-menu.png` | 3D desk diorama; CHALLENGE selected (red-gear cursor) |
| 2 | **Select Difficulty = energy budget** | `captures/challenge-2-select-difficulty.png` | three gears: **NORMAL = GF ENERGY 1500**, **TUFF = 2000**, **INSANE = 2500**. This IS "choose your energy". |
| 3 | **Select # players** | `captures/challenge-3-select-players.png` | **FIGHT ALONE (1P)** vs **TEAM UP (2P co-op)**. Original 1–2; our build extends to **1–4 online**. |
| 4 | Load Box Data | `captures/challenge-4-load-box-data.png` | load collected borgs from memory card; START=SKIP |
| 5 | **Select a Force** | `captures/challenge-5-select-a-force.png` | pick a saved force; borg model + `COST 300` vs budget; `X = EDIT FORCE` |
| 6 | **Edit Force = the builder** | `captures/challenge-6-edit-force.png` | left = borg grid to add; right = **30-slot force ring**; panel = **`TOTAL COST 300 / LIMIT 1500 / REMAIN 1200`**. Total must stay ≤ LIMIT (the chosen budget). |

**Canonical force-build rule (confirmed):** pick a difficulty → that sets the **LIMIT** (energy budget) → build a force in up to **30 slots** → **TOTAL COST** must stay ≤ LIMIT, **REMAIN = LIMIT − TOTAL COST**. This is exactly what the web force-builder must reproduce (the in-repo builder already enforces budget; match this screen's TOTAL/LIMIT/REMAIN panel + 30-slot model). Our online flow: lobby picks the shared energy LIMIT (like Select Difficulty) → each of 1–4 players builds a force under it (Edit Force) → co-op battle.



### Boot/flow (CONFIRMED)
Sofdec/ADX logos → attract (a borg flies toward camera over a blue grid + GOTCHA FORCE logo) → **Start** advances to Title (logo on a desk) → **Start** → **Main Menu**. STORY → memory-card LOAD screen ("No save data… START GAME / REPLACE MEMORY CARD") → story intro narration → per-mission: intro dialogue → **VS / briefing** → **battle**.

### Main menu (CONFIRMED)
A 3D desk diorama (kid's room). Each MODE is a physical object on the desk; the **selected** item sits front-center, enlarged, ringed by a red gear cursor. Moving the stick/d-pad rotates the desk and changes selection. Items seen: **STORY** (front-center default), **VERSUS**, **ACTION**, **CHALLENGE**, **EDIT FORCE** (green gear — the force builder), **TRADE**, **COLLECTION**, **OPTION**. Confirm = A. This is NOT a flat list — it's the rotating-desk scene. (Faithful approach: render the desk scene with the extracted `optn00`/menu assets, or at minimum reproduce the object-ring selection model.)

### Story intro / dialogue cards (CONFIRMED)
Full-bleed illustrated panels (e.g. "The day after a meteorite fell toward Sahari town…" over a night-town image) and character dialogue cards: top banner with **"!" icon + line title** (e.g. *"The name is G Red!"*), a cream speech bubble with orange body text (key terms colored — "Death Force" in pink), the speaking borg rendered on the right, the protagonist on the left, a map diorama center, and **GF ENERGY <n>** shown top-right (G Red = 300, matches borgs.json). Controls legend bottom-right.

### Pre-battle VS / briefing (CONFIRMED)
Player face icon (left) **Vs.** enemy emblem (right, Death Force = white disc + red dot), each with a green (player) / red (enemy) bar; a windowed arena preview with the objective ribbon **"DEFEAT ENEMY GOTCHA BORGS!"**; bottom button legend: **CHOOSE** (stick), **BACK = B (red)**, **CONFIRM = A (green)**. → A starts the battle.

### IN-BATTLE HUD (CONFIRMED — replaces the faked HUD in main.ts)
This is the exact thing to rebuild. Observed layout:
- **Top-left — the GF-energy meters (the two bars):** a **green bar labelled "<energy> ALLY"** (e.g. `300 ALLY`) stacked directly above a **red bar labelled "ENEMY <energy>"** (e.g. `ENEMY 540`). Both have **zigzag/torn ends**, a small numeric energy tab on the bar, and DEPLETE as each side's borgs are defeated (value = remaining sum of that force's borg energy). A yellow **"!"** alert icon sits just right of the bars in some states. → The web app's hardcoded `width:72%` divs must be replaced by these two labelled bars driven by `sum(borg.energy for alive borgs)` per side from `borgs.json`.
- **Bottom-left:** a **green circular gauge with a number** (e.g. `200`) = the active borg's HP/boost gauge.
- **Bottom-right:** weapon/attack prompts — a **B** button on a red arc with an **ammo count** (e.g. `5`) and a cyan reload/charge bar, and an **X** button with a circular **cooldown** ring (special). Maps to attack/special with ammo+cooldown state.
- **Lock-on reticle** appears over the locked target (lock-on = R, switch = Z, per controls screen).
- Camera = third-person behind the active borg; arena is the tiny-scale human-world environment (desk/ground, leaves, soda can, game cartridge as scenery).

### Results (NOT yet captured)
`reference/results.png` still to grab (end-of-battle podium uses `ui/hsd/rpot20_mdl`..`rpot23_mdl`). Capture when convenient.

> Note: literal reference PNGs could not be auto-saved this session (Dolphin/automation screenshot paths weren't recoverable). The layouts above are transcribed from live observation and are sufficient to implement against; drop pixel-exact PNGs into `apps/game/reference/` later (Dolphin F9 with the render focused) if needed.
