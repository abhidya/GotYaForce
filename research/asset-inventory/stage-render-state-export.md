# Stage Render State Export

This pass turns the extracted HSD stage lighting evidence into a browser-side
JSON artifact for `st00`.

## Command

```bash
rtk node scripts/export-stage-render-state.mjs
```

Default input:

- `research/asset-inventory/stage-lighting-render-state.json`

Default output:

- `apps/game/public/stages/st00/render-state.json`

The exporter also reads `apps/game/public/stages/st00/manifest.json` for
provenance metadata only. It does not edit stage manifests or browser source.

## Export Contract

`render-state.json` contains only copied stage render-state evidence:

- `camera` comes from `st00.scene.cameras[0]`.
- `lights` comes from every entry in `st00.scene.lights`.
- `fog` comes from `st00.scene.fogs[0]`.

The browser-facing fields are direct copies from the research JSON decoded/raw
values. The script has no fallback camera, fog, or light constants, and it exits
before writing if the required evidence is missing or if copied values do not
match the research JSON.

## st00 Values

- Camera: perspective, eye `[10087.730469, 9489.730469, 9746.232422]`,
  interest `[578.34082, -1718.759033, 452.259888]`, near `10`, far `80000`,
  FOV `43.191872`, aspect `1.333333`.
- Lights: ambient/global `#d8d0c2` with flags `0x40000`; positioned
  diffuse/specular `#fff0e6` with flags `0xd0000`, position
  `[-385.512512, 956.0448, -377.986603]`, interest/param `[0, 0, 0]`.
- Fog: type `2`, flags/enabled word `0`, start `900`, end `40000`, color
  `#fff6e5`.
