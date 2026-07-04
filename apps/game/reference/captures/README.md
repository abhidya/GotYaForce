# Real-game reference captures (Gotcha Force GG4E, via Dolphin)

Native-res frames from the actual game. The `challenge-*` files trace the CHALLENGE-mode
flow (the basis for our online energy-budget multiplayer). Raw `GG4E08_*` files are the
originals (timestamped); the `challenge-N-*` files are the same frames renamed in flow order.

## CHALLENGE mode flow (what we are recreating)
1. `challenge-1-main-menu.png` — main menu (3D desk diorama), CHALLENGE selected (red-gear cursor).
2. `challenge-2-select-difficulty.png` — **SELECT DIFFICULTY = the energy budget**: NORMAL=GF ENERGY 1500, TUFF=2000, INSANE=2500. (This is the "choose your energy" step.)
3. `challenge-3-select-players.png` — **SELECT NUMBER OF PLAYERS**: FIGHT ALONE (1P) or TEAM UP (2P co-op). Original Challenge branch = 1P/2P; 3P/4P are out of scope for now.
4. `challenge-4-load-box-data.png` — LOAD BOX DATA (load collected borgs from memory card; START=SKIP).
5. `challenge-5-select-a-force.png` — **SELECT A FORCE**: pick a saved force; shows the borg model + `COST 300` vs budget; `X = EDIT FORCE`.
6. `challenge-6-edit-force.png` — **EDIT FORCE = the force builder**: left = borg grid to add; right = 30-slot force ring; panel shows `TOTAL COST 300 / LIMIT 1500 / REMAIN 1200`. Total must stay under LIMIT (the chosen energy budget).

## Other captures
- `GG4E08_..._13-52-24.png`, `..._13-57-33.png` — earlier session (title/main-menu / Story in-battle HUD area).
- `GG4E08_..._14-44-*.png` — main-menu navigation frames.

## Controls (mapped in Dolphin for capture)
A=J, B=K, X=L, Y=I, Start=Enter, D-Pad=arrows, Stick=WASD. (In-game: A=jump, B=attack, X=special, R=switch lock-on, Z=ally lock-on.)
