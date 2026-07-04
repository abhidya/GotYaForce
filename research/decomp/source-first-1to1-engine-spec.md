# Spec: Source-First 1:1 Game Engine

## Objective

Build the browser Gotcha Force engine toward 1:1 behavior using source/decomp/ROM evidence as the authority.

The immediate target is not "make every borg use G RED's mechanics"; it is to use G RED as the proven example of the desired standard:

- exact command records when a constructor `+0x4ec` table is decoded,
- source-backed button/context routing,
- runtime move bindings that expose what is exact vs tuned,
- animation selections backed by exported banks or documented fallbacks,
- tests/audits that refuse to call guessed behavior exact.

Success means each borg move is either implemented from source evidence or explicitly marked as tuned/blocked with the missing evidence named.

## Tech Stack

- TypeScript packages under `packages/*`
- Browser runtime under `apps/game`
- Source/decomp evidence under `research/decomp`, `research/asset-inventory`, and generated JSON in `packages/combat/src/data`
- Node scripts for extraction, audits, and validation

## Commands

```bash
rtk node scripts/audit-move-wiring.mjs
rtk node scripts/audit-move-unblockers.mjs
rtk node scripts/validate-borg-animation-actions.mjs --strict
rtk pnpm typecheck
rtk pnpm --filter @gotcha-force/combat test
```

Use narrower commands while iterating:

```bash
rtk node scripts/audit-move-wiring.mjs --borg pl0615
rtk node scripts/audit-move-wiring.mjs --borg pl0405
rtk node scripts/audit-move-wiring.mjs --borg pl0900
rtk node scripts/audit-move-wiring.mjs --borg pl0e01
rtk node scripts/audit-move-unblockers.mjs --borg pl0615
```

## Project Structure

- `packages/combat/src/combat.ts` - battle action execution, projectile/melee/special handling
- `packages/combat/src/moveRuntime.ts` - runtime move bindings and exact/tuned coverage flags
- `packages/combat/src/command.ts` - source-backed command type/subtype vocabulary
- `packages/combat/src/commandMoveTables.ts` - decoded constructor command table access
- `packages/combat/src/data/*.json` - generated source/wikidata/action profile inputs
- `apps/game/src/sim/borgPresentationAssets.ts` - animation bank resolution
- `scripts/audit-move-wiring.mjs` - user-facing gap audit
- `scripts/audit-move-unblockers.mjs` - source-level command/HIT unblocker audit
- `research/decomp/PORT-1TO1-STATUS.md` - top-level tracker

## Code Style

Prefer source-tiered logic that names confidence directly:

```ts
const commandRecords = commandMoveRecordsForBorgButton(id, button);
return {
  button,
  exactCommand: commandRecords.length > 0,
  commandRecords,
  hitboxStatus: exactHitbox ? "source-hit-record" : "generic-special-aoe",
};
```

Do not hide guesses behind exact-looking names. If behavior is inferred from wiki text or G RED similarity, label it `TUNED`, `OBSERVED_WIKI`, or `INFERRED`, not `DERIVED_ROM`.

## Testing Strategy

- Unit/selftests for each mechanics wave under `packages/combat/src/*.selftest.ts`
- Audit checks for global coverage after each wave:
  - `audit-move-wiring` should show lower exact-command/exact-hitbox/anim-map gaps only when evidence exists.
  - `audit-move-unblockers` should explain which source tables were consumed.
  - `validate-borg-animation-actions --strict` must stay at zero missing/fallback slots.
- Typecheck after TypeScript runtime changes.
- Add regression examples for G RED plus at least one non-G RED borg per generalized path.

## Boundaries

- Always: keep source evidence linked in comments or generated metadata.
- Always: preserve the distinction between exact, inferred, tuned, and blocked.
- Always: run the relevant audit after changing move/action/animation behavior.
- Ask first: adding dependencies, changing generated data formats, deleting legacy asset exports.
- Never: copy G RED move behavior to unrelated borgs without source evidence.
- Never: mark nurse heal, magnet pull, satellite behavior, status catalog, or exact per-move hitboxes as complete from wiki names alone.
- Never: revert unrelated dirty worktree files.

## Implementation Roadmap

1. **Command coverage wave**
   - Wire decoded command records deeper into `stepAttacks`.
   - Promote only borgs with exact constructor `+0x4ec` tables.
   - Acceptance: G RED remains green; every exact-table borg exposes command routing in runtime bindings and tests.

2. **HIT spawner/remap wave**
   - Consume literal HIT kinds first, then DOL byte/short kind tables from `audit-move-unblockers`.
   - Acceptance: exact hitbox count increases; `X hitbox is generic radius` decreases only for consumed source records.

3. **Unique mechanic wave**
   - Magnet pull, nurse heal, satellite beam/fly behavior, status effects.
   - Acceptance: each mechanic has either a source-derived implementation or a trace-blocked note with a reproduction preset.

4. **Per-borg physics/knockback wave**
   - Reconcile source `pl####data.bin` movement values and strength-indexed knockback tables into the port scale.
   - Acceptance: tuned global movement/knockback constants shrink; selftests cover at least G RED and a contrasting borg.

5. **Presentation fidelity wave**
   - Combat SE-bank extraction, PTL/REF effect mapping, 3D weapon meshes, remaining stage collision.
   - Acceptance: runtime uses extracted source assets where decoded; tuned visual placeholders are reduced and audited.

## Current Known Gaps

From the current audits:

- Exact command tables: `25/208` borgs.
- Move rows audited: `602`.
- Missing exact command table rows: `541`.
- Missing exact anim map rows: `569`.
- Missing exact X hitbox rows: `191`.
- Roster animation indexes: `208/208`, strict resolver currently zero missing/fallback.

Example status:

- `pl0615` G RED: best-covered reference borg. B Shot, B Attack, B Charge, and X command rows exist; X exact hitbox still generic.
- `pl0405`/`pl0409` Magnet Robot: moves exist, but magnet pull/scope behavior is generic/tuned.
- `pl0900` Angel Nurse: heal data exists, but active nurse healing remains disabled because the HP-write source path is not found.
- `pl0e01` Beam Satellite: moves exist, source motion bank is empty/static, beam behavior is generic projectile/special behavior.

## Success Criteria

- Every source-backed implementation has an audit row proving why it is exact.
- Every remaining non-1:1 behavior has a named blocker: missing static source, undecoded table, or required Dolphin trace.
- No global coverage count improves by relabeling guessed behavior as exact.
- G RED remains the reference-quality baseline while other borgs improve only through their own decoded evidence.

## Open Questions

1. Should the first implementation ticket be command coverage, HIT spawner/remap coverage, or a specific showcase mechanic such as Magnet Robot pull?
2. Are tuned-but-playable versions acceptable temporarily for unique mechanics, or should unique mechanics stay disabled until source proof exists?
3. Should stale status docs be updated as part of each implementation wave, or only after code/test verification?
