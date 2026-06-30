# Stage Export Plan

Generated: 2026-06-30T22:21:26.679Z

## Summary

- Region: GG4E
- Source direct stage pairs: 40/40
- Browser public stage folders: 35
- Browser stages with visual DAE pieces: 35
- Browser stages with complete DAE sequences: 35
- Source stages with any hit collision bins: 18
- Missing or partial exports: 5
- Safe missing exports with current tools: 5
- Proof candidate: st4a

Adventure-flow note: Runtime hard-codes st00 and 40 DAE pieces; extracted root has many st##_mdl.arc/st##.pzz pairs but no verified arena-name to stage-code table in source.

## Commands

Dry run:

```bash
rtk node scripts/export-all-stages.mjs GG4E --dry-run
```

One proof export:

```bash
rtk node scripts/export-all-stages.mjs GG4E --export --proof
```

All safe missing exports:

```bash
rtk node scripts/export-all-stages.mjs GG4E --export --stage st4a,st4b,st4c,st4e,stff
```

## Coverage Table

| Stage | Source | Browser visual | Hit bins | Set ARCs | Action |
| --- | --- | --- | --- | --- | --- |
| st00 | ARC+PZZ | 40 DAE complete | 3 source / 3 public | 4 source / 4 public | covered |
| st01 | ARC+PZZ | 78 DAE complete | 3 source / 3 public | 4 source / 4 public | covered |
| st02 | ARC+PZZ | 51 DAE complete | 3 source / 3 public | 4 source / 4 public | covered |
| st03 | ARC+PZZ | 43 DAE complete | 3 source / 3 public | 4 source / 4 public | covered |
| st04 | ARC+PZZ | 52 DAE complete | 3 source / 3 public | 4 source / 4 public | covered |
| st05 | ARC+PZZ | 28 DAE complete | 3 source / 3 public | 4 source / 4 public | covered |
| st06 | ARC+PZZ | 4 DAE complete | 3 source / 3 public | 4 source / 4 public | covered |
| st07 | ARC+PZZ | 4 DAE complete | 3 source / 3 public | 4 source / 4 public | covered |
| st08 | ARC+PZZ | 52 DAE complete | 3 source / 3 public | 4 source / 4 public | covered |
| st09 | ARC+PZZ | 9 DAE complete | 3 source / 3 public | 1 source / 1 public | covered |
| st0a | ARC+PZZ | 43 DAE complete | 3 source / 3 public | 4 source / 4 public | covered |
| st0b | ARC+PZZ | 28 DAE complete | 3 source / 3 public | 4 source / 4 public | covered |
| st0c | ARC+PZZ | 20 DAE complete | 3 source / 3 public | 4 source / 4 public | covered |
| st0d | ARC+PZZ | 17 DAE complete | 3 source / 3 public | 4 source / 4 public | covered |
| st0e | ARC+PZZ | 43 DAE complete | 3 source / 3 public | 4 source / 4 public | covered |
| st0f | ARC+PZZ | 13 DAE complete | 3 source / 3 public | 4 source / 4 public | covered |
| st10 | ARC+PZZ | 7 DAE complete | 3 source / 3 public | 0 source / 0 public | covered |
| st20 | ARC+PZZ | 40 DAE complete | no source hit | 0 source / 0 public | covered |
| st21 | ARC+PZZ | 78 DAE complete | no source hit | 0 source / 0 public | covered |
| st22 | ARC+PZZ | 51 DAE complete | no source hit | 0 source / 0 public | covered |
| st23 | ARC+PZZ | 43 DAE complete | no source hit | 0 source / 0 public | covered |
| st24 | ARC+PZZ | 52 DAE complete | no source hit | 0 source / 0 public | covered |
| st25 | ARC+PZZ | 28 DAE complete | no source hit | 0 source / 0 public | covered |
| st29 | ARC+PZZ | 9 DAE complete | no source hit | 0 source / 0 public | covered |
| st2a | ARC+PZZ | 43 DAE complete | no source hit | 0 source / 0 public | covered |
| st2b | ARC+PZZ | 28 DAE complete | no source hit | 0 source / 0 public | covered |
| st2c | ARC+PZZ | 20 DAE complete | no source hit | 0 source / 0 public | covered |
| st2e | ARC+PZZ | 43 DAE complete | no source hit | 0 source / 0 public | covered |
| st40 | ARC+PZZ | 40 DAE complete | no source hit | 0 source / 0 public | covered |
| st41 | ARC+PZZ | 78 DAE complete | no source hit | 0 source / 0 public | covered |
| st42 | ARC+PZZ | 51 DAE complete | no source hit | 0 source / 0 public | covered |
| st43 | ARC+PZZ | 43 DAE complete | no source hit | 0 source / 0 public | covered |
| st44 | ARC+PZZ | 52 DAE complete | no source hit | 0 source / 0 public | covered |
| st45 | ARC+PZZ | 28 DAE complete | no source hit | 0 source / 0 public | covered |
| st49 | ARC+PZZ | 9 DAE complete | no source hit | 0 source / 0 public | covered |
| st4a | ARC+PZZ | not exported | no source hit | 0 source / 0 public | `rtk node scripts/export-all-stages.mjs GG4E --export --stage st4a` |
| st4b | ARC+PZZ | not exported | no source hit | 0 source / 0 public | `rtk node scripts/export-all-stages.mjs GG4E --export --stage st4b` |
| st4c | ARC+PZZ | not exported | no source hit | 0 source / 0 public | `rtk node scripts/export-all-stages.mjs GG4E --export --stage st4c` |
| st4e | ARC+PZZ | not exported | no source hit | 0 source / 0 public | `rtk node scripts/export-all-stages.mjs GG4E --export --stage st4e` |
| stff | ARC+PZZ | not exported | 3 source / 0 public | 0 source / 0 public | `rtk node scripts/export-all-stages.mjs GG4E --export --stage stff` |

## Exact Per-Stage Commands

### st4a
```bash
rtk node scripts/export-all-stages.mjs GG4E --export --stage st4a
# equivalent single-stage raw copy tool, which also rewrites apps/game/public/stages/manifest.json:
rtk node scripts/export-stage-assets.mjs GG4E 4a
# legacy visual exporter; retained for comparison, not used by the batch orchestrator:
rtk node scripts/export-stage-hsd.mjs GG4E 4a
rtk node scripts/export-all-stages.mjs GG4E --export --stage st4a
```

### st4b
```bash
rtk node scripts/export-all-stages.mjs GG4E --export --stage st4b
# equivalent single-stage raw copy tool, which also rewrites apps/game/public/stages/manifest.json:
rtk node scripts/export-stage-assets.mjs GG4E 4b
# legacy visual exporter; retained for comparison, not used by the batch orchestrator:
rtk node scripts/export-stage-hsd.mjs GG4E 4b
rtk node scripts/export-all-stages.mjs GG4E --export --stage st4b
```

### st4c
```bash
rtk node scripts/export-all-stages.mjs GG4E --export --stage st4c
# equivalent single-stage raw copy tool, which also rewrites apps/game/public/stages/manifest.json:
rtk node scripts/export-stage-assets.mjs GG4E 4c
# legacy visual exporter; retained for comparison, not used by the batch orchestrator:
rtk node scripts/export-stage-hsd.mjs GG4E 4c
rtk node scripts/export-all-stages.mjs GG4E --export --stage st4c
```

### st4e
```bash
rtk node scripts/export-all-stages.mjs GG4E --export --stage st4e
# equivalent single-stage raw copy tool, which also rewrites apps/game/public/stages/manifest.json:
rtk node scripts/export-stage-assets.mjs GG4E 4e
# legacy visual exporter; retained for comparison, not used by the batch orchestrator:
rtk node scripts/export-stage-hsd.mjs GG4E 4e
rtk node scripts/export-all-stages.mjs GG4E --export --stage st4e
```

### stff
```bash
rtk node scripts/export-all-stages.mjs GG4E --export --stage stff
# equivalent single-stage raw copy tool, which also rewrites apps/game/public/stages/manifest.json:
rtk node scripts/export-stage-assets.mjs GG4E ff
# legacy visual exporter; retained for comparison, not used by the batch orchestrator:
rtk node scripts/export-stage-hsd.mjs GG4E ff
rtk node scripts/export-all-stages.mjs GG4E --export --stage stff
```

