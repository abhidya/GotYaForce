# @gf/test-fixtures

## ⚠️ Synthetic samples ONLY

This package holds **tiny, hand-built synthetic fixtures** used to exercise the
`@gf/formats` parsers (e.g. a 16-byte fake PZZ with two members, a minimal AFS TOC, a
1×1 TPL).

**Do NOT commit extracted disc data here — ever.** No bytes lifted from the game disc,
no real `_mdl.arc` / `.pzz` / `.afs` / `.adx` / `.tpl` dumps, not even "small" ones.
Real disc bytes stay strictly under `user-data/` and `research/disc/<REGION>/`, both of
which are gitignored (see the root `.gitignore`).

Why: repo hygiene/size, and to keep the repository free of game-data dumps. Fixtures
must be small enough to read at a glance and reproducible from a generator script.
