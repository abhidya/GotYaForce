# Stage Export Plan

Generated: 2026-06-30T22:25:23.414Z

## Summary

- Region: GG4E
- Source direct stage pairs: 40/40
- Browser public stage folders: 40
- Browser stages with visual DAE pieces: 40
- Browser stages with complete DAE sequences: 40
- Source stages with any hit collision bins: 18
- Missing or partial exports: 0
- Safe missing exports with current tools: 0
- Proof candidate: none

Adventure-flow note: Runtime hard-codes st00 and 40 DAE pieces; extracted root has many st##_mdl.arc/st##.pzz pairs but no verified arena-name to stage-code table in source.

## Commands

Dry run:

```bash
rtk node scripts/export-all-stages.mjs GG4E --dry-run
```

One proof export:

```bash
# no safe proof candidate
```

All safe missing exports:

```bash
# no safe missing exports
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
| st4a | ARC+PZZ | 43 DAE complete | no source hit | 0 source / 0 public | covered |
| st4b | ARC+PZZ | 28 DAE complete | no source hit | 0 source / 0 public | covered |
| st4c | ARC+PZZ | 20 DAE complete | no source hit | 0 source / 0 public | covered |
| st4e | ARC+PZZ | 43 DAE complete | no source hit | 0 source / 0 public | covered |
| stff | ARC+PZZ | 83 DAE complete | 3 source / 3 public | 0 source / 0 public | covered |

## Exact Per-Stage Commands

No missing or partial stage exports remain.

