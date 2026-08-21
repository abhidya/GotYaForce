---
title: Verified Port Artifacts
---

# Verified port artifacts

A port moves through four distinct claims:

1. **Compiled:** source and imports are structurally valid.
2. **Oracle-verified:** behavior matches an independent evidence-bound check.
3. **Integrated:** production code selects the verified implementation.
4. **Playable:** a browser acceptance route exercises the intended game state.

Use the checked-in fixture to test the deterministic importer without private
Ghidra state or a local model:

```bash
pnpm test:oghidra-port
pnpm import:oghidra-port --artifact scripts/fixtures/oghidra-eagle-jet-artifact.json
```

The test must exit zero. The import command writes a generated candidate,
report, and automatic verification record; review `git status` and retain only
intentional evidence. A fallback exits `2` and is not a promotion.

Never hand-edit autonomous queue verdicts or treat compile-only staging as
integration. Runtime operators must use the journaled maintenance interface
documented by the port tooling.
