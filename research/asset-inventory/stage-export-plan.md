# Stage Export Plan

Generated: 2026-06-30T21:54:12.031Z

## Summary

- Region: GG4E
- Source direct stage pairs: 40/40
- Browser public stage folders: 19
- Browser stages with visual DAE pieces: 19
- Browser stages with complete DAE sequences: 19
- Source stages with any hit collision bins: 18
- Missing or partial exports: 21
- Safe missing exports with current tools: 21
- Proof candidate: st09

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
rtk node scripts/export-all-stages.mjs GG4E --export --stage st09,st23,st24,st25,st29,st2a,st2b,st2c,st2e,st40,st41,st42,st43,st44,st45,st49,st4a,st4b,st4c,st4e,stff
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
| st09 | ARC+PZZ | not exported | 3 source / 0 public | 1 source / 0 public | `rtk node scripts/export-all-stages.mjs GG4E --export --stage st09` |
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
| st23 | ARC+PZZ | not exported | no source hit | 0 source / 0 public | `rtk node scripts/export-all-stages.mjs GG4E --export --stage st23` |
| st24 | ARC+PZZ | not exported | no source hit | 0 source / 0 public | `rtk node scripts/export-all-stages.mjs GG4E --export --stage st24` |
| st25 | ARC+PZZ | not exported | no source hit | 0 source / 0 public | `rtk node scripts/export-all-stages.mjs GG4E --export --stage st25` |
| st29 | ARC+PZZ | not exported | no source hit | 0 source / 0 public | `rtk node scripts/export-all-stages.mjs GG4E --export --stage st29` |
| st2a | ARC+PZZ | not exported | no source hit | 0 source / 0 public | `rtk node scripts/export-all-stages.mjs GG4E --export --stage st2a` |
| st2b | ARC+PZZ | not exported | no source hit | 0 source / 0 public | `rtk node scripts/export-all-stages.mjs GG4E --export --stage st2b` |
| st2c | ARC+PZZ | not exported | no source hit | 0 source / 0 public | `rtk node scripts/export-all-stages.mjs GG4E --export --stage st2c` |
| st2e | ARC+PZZ | not exported | no source hit | 0 source / 0 public | `rtk node scripts/export-all-stages.mjs GG4E --export --stage st2e` |
| st40 | ARC+PZZ | not exported | no source hit | 0 source / 0 public | `rtk node scripts/export-all-stages.mjs GG4E --export --stage st40` |
| st41 | ARC+PZZ | not exported | no source hit | 0 source / 0 public | `rtk node scripts/export-all-stages.mjs GG4E --export --stage st41` |
| st42 | ARC+PZZ | not exported | no source hit | 0 source / 0 public | `rtk node scripts/export-all-stages.mjs GG4E --export --stage st42` |
| st43 | ARC+PZZ | not exported | no source hit | 0 source / 0 public | `rtk node scripts/export-all-stages.mjs GG4E --export --stage st43` |
| st44 | ARC+PZZ | not exported | no source hit | 0 source / 0 public | `rtk node scripts/export-all-stages.mjs GG4E --export --stage st44` |
| st45 | ARC+PZZ | not exported | no source hit | 0 source / 0 public | `rtk node scripts/export-all-stages.mjs GG4E --export --stage st45` |
| st49 | ARC+PZZ | not exported | no source hit | 0 source / 0 public | `rtk node scripts/export-all-stages.mjs GG4E --export --stage st49` |
| st4a | ARC+PZZ | not exported | no source hit | 0 source / 0 public | `rtk node scripts/export-all-stages.mjs GG4E --export --stage st4a` |
| st4b | ARC+PZZ | not exported | no source hit | 0 source / 0 public | `rtk node scripts/export-all-stages.mjs GG4E --export --stage st4b` |
| st4c | ARC+PZZ | not exported | no source hit | 0 source / 0 public | `rtk node scripts/export-all-stages.mjs GG4E --export --stage st4c` |
| st4e | ARC+PZZ | not exported | no source hit | 0 source / 0 public | `rtk node scripts/export-all-stages.mjs GG4E --export --stage st4e` |
| stff | ARC+PZZ | not exported | 3 source / 0 public | 0 source / 0 public | `rtk node scripts/export-all-stages.mjs GG4E --export --stage stff` |

## Exact Per-Stage Commands

### st09
```bash
rtk node scripts/export-all-stages.mjs GG4E --export --stage st09
# equivalent single-stage raw copy tool, which also rewrites apps/game/public/stages/manifest.json:
rtk node scripts/export-stage-assets.mjs GG4E 09
# legacy visual exporter; retained for comparison, not used by the batch orchestrator:
rtk node scripts/export-stage-hsd.mjs GG4E 09
rtk node scripts/export-all-stages.mjs GG4E --export --stage st09
```

### st23
```bash
rtk node scripts/export-all-stages.mjs GG4E --export --stage st23
# equivalent single-stage raw copy tool, which also rewrites apps/game/public/stages/manifest.json:
rtk node scripts/export-stage-assets.mjs GG4E 23
# legacy visual exporter; retained for comparison, not used by the batch orchestrator:
rtk node scripts/export-stage-hsd.mjs GG4E 23
rtk node scripts/export-all-stages.mjs GG4E --export --stage st23
```

### st24
```bash
rtk node scripts/export-all-stages.mjs GG4E --export --stage st24
# equivalent single-stage raw copy tool, which also rewrites apps/game/public/stages/manifest.json:
rtk node scripts/export-stage-assets.mjs GG4E 24
# legacy visual exporter; retained for comparison, not used by the batch orchestrator:
rtk node scripts/export-stage-hsd.mjs GG4E 24
rtk node scripts/export-all-stages.mjs GG4E --export --stage st24
```

### st25
```bash
rtk node scripts/export-all-stages.mjs GG4E --export --stage st25
# equivalent single-stage raw copy tool, which also rewrites apps/game/public/stages/manifest.json:
rtk node scripts/export-stage-assets.mjs GG4E 25
# legacy visual exporter; retained for comparison, not used by the batch orchestrator:
rtk node scripts/export-stage-hsd.mjs GG4E 25
rtk node scripts/export-all-stages.mjs GG4E --export --stage st25
```

### st29
```bash
rtk node scripts/export-all-stages.mjs GG4E --export --stage st29
# equivalent single-stage raw copy tool, which also rewrites apps/game/public/stages/manifest.json:
rtk node scripts/export-stage-assets.mjs GG4E 29
# legacy visual exporter; retained for comparison, not used by the batch orchestrator:
rtk node scripts/export-stage-hsd.mjs GG4E 29
rtk node scripts/export-all-stages.mjs GG4E --export --stage st29
```

### st2a
```bash
rtk node scripts/export-all-stages.mjs GG4E --export --stage st2a
# equivalent single-stage raw copy tool, which also rewrites apps/game/public/stages/manifest.json:
rtk node scripts/export-stage-assets.mjs GG4E 2a
# legacy visual exporter; retained for comparison, not used by the batch orchestrator:
rtk node scripts/export-stage-hsd.mjs GG4E 2a
rtk node scripts/export-all-stages.mjs GG4E --export --stage st2a
```

### st2b
```bash
rtk node scripts/export-all-stages.mjs GG4E --export --stage st2b
# equivalent single-stage raw copy tool, which also rewrites apps/game/public/stages/manifest.json:
rtk node scripts/export-stage-assets.mjs GG4E 2b
# legacy visual exporter; retained for comparison, not used by the batch orchestrator:
rtk node scripts/export-stage-hsd.mjs GG4E 2b
rtk node scripts/export-all-stages.mjs GG4E --export --stage st2b
```

### st2c
```bash
rtk node scripts/export-all-stages.mjs GG4E --export --stage st2c
# equivalent single-stage raw copy tool, which also rewrites apps/game/public/stages/manifest.json:
rtk node scripts/export-stage-assets.mjs GG4E 2c
# legacy visual exporter; retained for comparison, not used by the batch orchestrator:
rtk node scripts/export-stage-hsd.mjs GG4E 2c
rtk node scripts/export-all-stages.mjs GG4E --export --stage st2c
```

### st2e
```bash
rtk node scripts/export-all-stages.mjs GG4E --export --stage st2e
# equivalent single-stage raw copy tool, which also rewrites apps/game/public/stages/manifest.json:
rtk node scripts/export-stage-assets.mjs GG4E 2e
# legacy visual exporter; retained for comparison, not used by the batch orchestrator:
rtk node scripts/export-stage-hsd.mjs GG4E 2e
rtk node scripts/export-all-stages.mjs GG4E --export --stage st2e
```

### st40
```bash
rtk node scripts/export-all-stages.mjs GG4E --export --stage st40
# equivalent single-stage raw copy tool, which also rewrites apps/game/public/stages/manifest.json:
rtk node scripts/export-stage-assets.mjs GG4E 40
# legacy visual exporter; retained for comparison, not used by the batch orchestrator:
rtk node scripts/export-stage-hsd.mjs GG4E 40
rtk node scripts/export-all-stages.mjs GG4E --export --stage st40
```

### st41
```bash
rtk node scripts/export-all-stages.mjs GG4E --export --stage st41
# equivalent single-stage raw copy tool, which also rewrites apps/game/public/stages/manifest.json:
rtk node scripts/export-stage-assets.mjs GG4E 41
# legacy visual exporter; retained for comparison, not used by the batch orchestrator:
rtk node scripts/export-stage-hsd.mjs GG4E 41
rtk node scripts/export-all-stages.mjs GG4E --export --stage st41
```

### st42
```bash
rtk node scripts/export-all-stages.mjs GG4E --export --stage st42
# equivalent single-stage raw copy tool, which also rewrites apps/game/public/stages/manifest.json:
rtk node scripts/export-stage-assets.mjs GG4E 42
# legacy visual exporter; retained for comparison, not used by the batch orchestrator:
rtk node scripts/export-stage-hsd.mjs GG4E 42
rtk node scripts/export-all-stages.mjs GG4E --export --stage st42
```

### st43
```bash
rtk node scripts/export-all-stages.mjs GG4E --export --stage st43
# equivalent single-stage raw copy tool, which also rewrites apps/game/public/stages/manifest.json:
rtk node scripts/export-stage-assets.mjs GG4E 43
# legacy visual exporter; retained for comparison, not used by the batch orchestrator:
rtk node scripts/export-stage-hsd.mjs GG4E 43
rtk node scripts/export-all-stages.mjs GG4E --export --stage st43
```

### st44
```bash
rtk node scripts/export-all-stages.mjs GG4E --export --stage st44
# equivalent single-stage raw copy tool, which also rewrites apps/game/public/stages/manifest.json:
rtk node scripts/export-stage-assets.mjs GG4E 44
# legacy visual exporter; retained for comparison, not used by the batch orchestrator:
rtk node scripts/export-stage-hsd.mjs GG4E 44
rtk node scripts/export-all-stages.mjs GG4E --export --stage st44
```

### st45
```bash
rtk node scripts/export-all-stages.mjs GG4E --export --stage st45
# equivalent single-stage raw copy tool, which also rewrites apps/game/public/stages/manifest.json:
rtk node scripts/export-stage-assets.mjs GG4E 45
# legacy visual exporter; retained for comparison, not used by the batch orchestrator:
rtk node scripts/export-stage-hsd.mjs GG4E 45
rtk node scripts/export-all-stages.mjs GG4E --export --stage st45
```

### st49
```bash
rtk node scripts/export-all-stages.mjs GG4E --export --stage st49
# equivalent single-stage raw copy tool, which also rewrites apps/game/public/stages/manifest.json:
rtk node scripts/export-stage-assets.mjs GG4E 49
# legacy visual exporter; retained for comparison, not used by the batch orchestrator:
rtk node scripts/export-stage-hsd.mjs GG4E 49
rtk node scripts/export-all-stages.mjs GG4E --export --stage st49
```

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

