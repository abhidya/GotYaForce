# Family state-machine coverage

Deterministic audit of the GG4E constructor roster, ROM command/root tables, bridge registrations, and family action tables.

- Constructor families: 119
- Borg roster entries: 208
- Action slots: 325
- Ported: 20; delegated: 0; inactive: 0; partial: 234; missing: 71
- Structural errors: 0

Default mode checks structural validity. Strict mode additionally fails while partial or missing live slots remain. See `data/family-state-machine-coverage.json` for slot evidence.
