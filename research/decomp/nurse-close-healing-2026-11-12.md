# Nurse close allied X healing

Scope: ground, close-range allied X for Angel Nurse (`pl0900`), Angel Rescue
(`pl0908`), and Nao (`pl090d`). This is a bounded browser implementation, not a
claim that the complete Nurse move set or collision system matches the original.
Far-target and airborne X branches remain unsupported and must not spend ammo or
fall through to a generic damaging attack.

## Original evidence

- `docs-site/public/chunks/chunk_0011.c`: root `80079a40` → `8007bb34` →
  `8007bb6c`; phase table `802d6668` selects `8007bbe0`, `8007be08`,
  `8007c414`, `8007c4b8`, `8007c7a4` for the close-ground route.
- `8007bbe0` selects close at distance strictly below 500 and the authored
  vertical band (93.69000244140625 margin). It consumes source resource cell 2
  once, through `006dbe0(actor,2,1,1)`.
- Bank `802c2660`, group 4 slot 2 parks at animation frame 6. `004cff4`
  resumes the contiguous slot 3 stream without restarting animation. HIT kind 4
  resolves hit row 6, active at animation frames 9–10. Auxiliary 6 and a
  60-tick wait lead to auxiliary 8 and group 4 slot 4 recovery.
- GG4E08 local-disc audit verified each Nurse's motion ends: group 4 animation
  slots 0/1/2/3 = 100/26/36/16. No original asset files were copied into this PR.
- Family damage table `802d6930`: close rows 4/8 restore 200/400 HP respectively;
  flagsA=3, flagsB=16, down=100, balance=0, combo=0, hitStrength=0,
  reactionFlags=1, direction=4, pitch=24.
- `zz_0055dcc_` (`chunk_0006.c`) computes target height `+668` from the
  command descriptor's float `+4c` times model scale `+b4`. The numeric roster
  heights (208 entries) were read in place from the user's GG4E08 executable.

## Healing contact is not just an HP increase

`chunk_0003.c:7529–7531` rejects healing immunity before contact side effects.
Lines 7955–7972 use negative record HP, quartered toward zero across teams,
without attack/defense damage multipliers. Nonzero drain timers become one.
The ordinary clamping helper (`8003d344`, `chunk_0004.c:6839–6858`) prevents
revival and caps at maximum HP. Damage totals and vampire banking require
strictly positive damage, but successful full-HP contacts retain hit counters,
gauges, hitstop, and reactions.

The descriptor's bit 128 registers the attack in list `177c`
(`chunk_0013.c:1068–1079`). The secondary collision pass against body list
`117c` (`chunk_0003.c:7338–7357`) permits allies. The flagsB16 ally exclusion
belongs to a different active-projectile collision pass and must not be applied
to this route.

## Known limits

- Animated joint matrices and source hit-shape history are not yet reproduced by
  the browser's root/body collision approximation.
- Healing's forced source reaction type 0x12 is represented by the host launch/down
  reaction. Exact original reaction animation and duration remain unverified.
- The source companion drain timer `+6b8` has no host field; only the represented
  hit-drain timer can be reset faithfully.
- Far, invalid-target fallback and airborne Nurse X source branches are not
  implemented here. This restriction describes the port, not the original game.
- Tests are deterministic host regressions against source-derived expectations,
  not a full frame-by-frame original-console comparison.

## Verification

- Corrected negative control bundles the same held-Z → X tests against the old
  main code without changing the working runtime. All three Nurses damage a
  nearby ally from 100 to 92 HP on ground and air instead of healing.
- New actual-input tests pass for all three ground-close variants: +200/+400,
  cap, no revival, interruption, held/tap/repress, busy-edge suppression,
  empty magazine, one debit and refill, post-admission vertical miss, and
  unsupported far/air/enemy admissions.
- Source clock tests cover fractional time, park at 6, continuation without
  restart, contact frames 9–10, 60-tick hold, recovery end 16, strict distance
  boundary 500, and decoded target-height boundaries.
- `pnpm typecheck`, combat lifecycle, and `pnpm --filter game build` pass.
- Contributor aggregate reaches the existing missing-three-HUD-assets blocker
  in this sparse checkout. All later stages were run separately and pass.
- Matching tooling: 52 tests pass. Oracle: 81 pass, zero fail, one expected
  private-snapshot skip. Neither is a complete Nurse console-comparison test.
- Visual comparison and exact original bone collision remain outstanding.
  Deployment status is recorded in the pull request, not inferred from build.

