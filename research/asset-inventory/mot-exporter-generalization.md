# MOT exporter generalization

Date: 2026-06-30
Worker: 09

## Scope

This note covers the single-borg HSD MOT exporter path:

- `scripts/export-borg-animation-hsd.mjs`
- `research/asset-inventory/borg-animation-export-plan.json`
- `research/format-specs/mot-animation-format.md`

Browser source and batch-exported animation outputs were not intentionally changed. A throwaway proof export was generated and removed after inspection.

## What was blocked

The export plan contains 4,321 discovered MOT clips across 102 borgs. Of those, 2,583 planned clips across 63 borgs were marked blocked by the current exporter assumption. The blocker is grouped by each MOT's first clip-blob offset:

| First blob | Borgs | Blocked clips |
|---:|---:|---:|
| `0x120` | 6 | 93 |
| `0x140` | 4 | 128 |
| `0x1A0` | 2 | 85 |
| `0x200` | 11 | 341 |
| `0x220` | 6 | 345 |
| `0x260` | 22 | 901 |
| `0x280` | 5 | 339 |
| `0x2A0` | 7 | 351 |

Important distinction: the exporter already accepted explicit non-`0x240` clip offsets for MOTs whose blob table boundary was still `0x240` (for example the plan's `pl0109 0x1D00` proof candidate). The unsafe assumption was not "clip offset must equal `0x240`"; it was "all table entries needed to find the next blob live before byte `0x240`, and blob bytes never begin before byte `0x240`."

## Exact cause

Before this patch, the generated C# helper in `scripts/export-borg-animation-hsd.mjs` sliced a requested HSD DAT blob like this:

```csharp
for (int t = 0; t < 0x240 && t + 3 < data.Length; t += 4) {
    uint v = U32(data, t);
    if (v > blobOff && v < next && v != 0xffffffff) next = v;
}
```

That works for the validated `pl0615`/`pl0000` shape where the first blob starts at `0x240`: the scan happens to cover all MOT master/bank table entries and stops before blob bytes.

It is unsafe for other MOT layouts:

- If the first blob starts after `0x240` (for example `pl030c` starts at `0x260`), the scan can miss valid bank-table entries between `0x240` and the true blob start. Any clip whose next physical blob offset only appears in that missed range can be sliced to the wrong end offset, often EOF or a later clip.
- If the first blob starts before `0x240` (for example `pl0500` starts at `0x120`), the scan reads into the first HSD DAT blob and can treat DAT header/data words as absolute MOT offsets. That can produce a bogus shorter blob length if an internal word is greater than the requested blob offset.

The batch plan therefore conservatively marked every MOT whose first blob was not `0x240` as unsafe for the current single-borg exporter.

## Patch

`scripts/export-borg-animation-hsd.mjs` now generates C# that derives blob boundaries from the MOT tables:

1. Read the six master-table entries.
2. Walk each bank table from its actual offset until `0xFFFFFFFF`.
3. Ignore empty slots (`0x00000000`).
4. Validate non-empty clip offsets are inside the MOT file.
5. Use the smallest collected clip offset greater than the requested explicit `blobOff` as the slice end, or EOF for the final blob.

This preserves the CLI shape and existing explicit-offset usage:

```bash
node scripts/export-borg-animation-hsd.mjs GG4E pl030c 0x260:anim_b00_s00_candidate.json
```

The no-spec default remains the existing pl0615-oriented pair (`0x240` and `0x1a40`) for backward compatibility.

## Verification

Commands run:

```bash
rtk node --check scripts/export-borg-animation-hsd.mjs
rtk node scripts/export-borg-animation-hsd.mjs GG4E pl030c 0x260:codex_proof_pl030c_0x260.json
rtk node -e "const fs=require('fs'); const p='apps/game/public/models/pl030c/codex_proof_pl030c_0x260.json'; const j=JSON.parse(fs.readFileSync(p,'utf8')); console.log(JSON.stringify({name:j.name,frameCount:j.frameCount,fps:j.fps,rotFormat:j.rotFormat,bones:j.bones.length},null,2));"
```

Proof export result:

```json
{
  "name": "pl030cmot_blob260_m0",
  "frameCount": 97,
  "fps": 60,
  "rotFormat": "quat_xyzw",
  "bones": 20
}
```

The proof export command emitted existing .NET/HSDLib warnings about package target frameworks and unresolved optional references, plus Node's `DEP0190` warning for `spawnSync(..., { shell: true })`. It still exited `0` and wrote parseable positive-frame animation JSON. The generated proof JSON and empty `apps/game/public/models/pl030c/` directory were removed after inspection.

## Remaining risks

- This only generalizes explicit blob-offset extraction. It does not change the no-spec default clip list, the `modelSkip` value (`0x100`), or `modelIndex` (`0`).
- It trusts the MOT master table count from the current format notes: six bank-table offsets at file start.
- It now fails early on malformed bank tables, missing terminators, or out-of-file clip pointers instead of attempting a best-effort fixed-window scan.
- The batch plan/markdown still describe the old current-exporter blocker until the batch inventory is regenerated with the patched exporter behavior.
