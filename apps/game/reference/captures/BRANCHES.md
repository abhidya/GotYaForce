# Challenge-mode flow + win/lose branches (real captures, GG4E)

The full Challenge sequence our online recreation mirrors. Frames in this folder (`challenge-N-*.png`, `title-main-menu.png`).

## Flow
title/main-menu → CHALLENGE → **Select Difficulty (= energy budget: 1500/2000/2500)** → **Select Players (1P FIGHT ALONE / 2P TEAM UP)** → Load Box Data (skip) → **Select a Force** (COST vs budget) → **Edit Force** (30-slot, TOTAL COST/LIMIT/REMAIN) → **BATTLE n VS** → live battle → results.

## Branches (confirmed by playing both)
- **WIN** (`challenge-11-WIN-results.png`): results screen "WIN" + scoring — ATTACK, HIT RATIO, DODGE RATIO, ENEMY/PLAYER/ALLY BORGS DEFEATED, TOTAL COST, **GRAND TOTAL positive (e.g. 7000)**. PLAYER BORGS DEFEATED 0 = your borg survived. → **advances to the next battle (BATTLE 2, tougher: ENEMY 1860)**. Challenge = a run of consecutive battles.
- **LOSE** (`challenge-10-LOSE-results.png`): same results template, "LOSE" + **GRAND TOTAL negative (-300)**. → returns to **title screen** (no auto-retry).
- **In-battle PAUSE** (`challenge-12-pause-menu.png`): Start opens "1P PAUSE" → RESUME / QUIT.

## How the win was reached (matches the design)
1P "FIGHT ALONE" still gives you a **CPU ally**. Idle + keep your borg alive (retreat from the front) and the CPU ally clears the enemy force → WIN. So co-op assist is core: in our 1–4 player version, human players replace/augment that CPU ally.

## Runtime traces (RAM)  → ../../../user-data/GG4E/traces/
- `battle1_challenge.sav` / `_t2.sav` — mid-battle full-RAM snapshots (t1/t2 with movement+HP deltas).
- `battle1_start_checkpoint.sav` — **battle-1 start checkpoint** (re-loadable; win it by idling since the CPU helps).
