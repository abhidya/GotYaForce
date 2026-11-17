# Archived opcode01 setup-command instruction evidence

2026-11-13. Local, read-only ProgramDB inspection on the active matching route.
No original DOL, emulator, running game, process, capture, download, or publication
was used. This adds no matched functions or playable-parity claim.

## Provenance and exact scope

Reader: `research/tools/matching-decomp/read_archived_setup_command_evidence.py`.
Both authenticated snapshots under
`research/decomp/GotchaForce.rep.before_force_create/idata/00/~00000000.db/`
produce the same selected words, range hashes, and mapping facts:

- `db.3.gbf`: SHA-256 `7b50dd2d2e17b4bfcc89a64cde27010247d0cbf0f48bd5c059f50275f40458d0`.
- `db.4.gbf`: SHA-256 `1f86813d91ea8e2c4564f96622ec42555e1dba2c78aa81ad654e892140d019f8`.
- Parser `8004c050..8004c298`, 584 bytes: SHA-256
  `1161d002aab162ea3506cd8a088d941fb362861f51cfae3f35ac6b57547d3ab0`.
- Opcode01 `8004c298..8004c424`, 396 bytes: SHA-256
  `42c560d248bf6cdff40bb3e0f93a73b6ce65af55eaef0fd4874a521daa6a2188`.
- Setup gate `80048648..8004871c`, 212 bytes: SHA-256
  `0eb26bc9a603d933ffcaf3e9065583d3127cb603be56c29d887566f9211a2ad9`.
- Existing 72-byte dispatch table at `802d0da0`: SHA-256
  `fdf7c34d3ce203b91e168f8ea7ce7873e7140b5dbf1a6d5cb1710cbe868d260e`.
  Entry 1 at `802d0da4` is `8004c298`.

All ends are exclusive. The decompiler export places the next displayed function
at `8004c5fc`, but the instruction return at `8004c420` is `4e800020` (`blr`).
Manual inspection identified separate entry-like instruction sequences starting
at `8004c424` and later addresses, not reachable from opcode01's checked control
flow. The final reader deliberately excludes that neighboring region. The
export's apparent 868-byte span must not be called opcode01's instruction extent.

Text mapping is `MAIN_.text1`, block/subblock key 1, start `800055e0`, length
2,796,416, chain root 21. Parser/handler spans use data buffer 39; setup uses 38.
The existing table mapping is `MAIN_.data3`, key 5, start `802bae60`, length
1,000,128, chain root 199, data buffer 205. CLI output preserves bounded physical
span provenance without emitting raw ranges.

Snapshot metadata says `boot.dol`, Ghidra 12.1.2, executable SHA-256
`21454a8880c6254616662710d6ec626e43d853999da2cdfad700030960a94836`
(property type 2). File Bytes table has zero records (root -1). Metadata and
agreement between archived ProgramDB snapshots do **not** establish that these
bytes are unchanged original-DOL bytes, nor establish live-runtime parity.
The reader retains the existing snapshot, schema, mapping, full-data5 hash and
constant controls. No constant target or independent control was added.

## Instruction-backed conclusions

Names such as mode, transition, target and accumulator below are source/host
interpretations. Register moves, memory offsets, relative branches and ordering
are checked instruction facts. Full selected-word annotations are in the reader.

- Parser `8004c070 ffe00890` copies incoming f1 to f31. At the top of **every**
  dispatch `8004c098 fc20f890` copies f31 back to f1. r6/r7 are likewise restored
  from saved r25/r26 at c0a8/c0ac. The parser does not carry a previous handler's
  modified f1 or resolved integer overrides into the next command. This matters
  when a preceding command clobbers volatile floating-point registers.
- Handler c2b4 loads the old local cursor; c2c0 adds eight and c2cc stores it
  through r5 before reading any command operands. Negative incoming f1 selects
  the signed halfword at old cursor +6. This is a local handler cursor advance,
  not evidence for host buffer safety or transaction behavior.
- Negative mode override is resolved from unsigned byte +3 at c304 **before**
  negative transition override is resolved from unsigned byte +4 at c310.
  The setup call receives transition in r7 and mode in r8.
- Handler f31 survives setup calls as its own working float. If still negative,
  c37c/c380/c384 replace it with the selected channel frame plus object offset.
  Subsequent selected channels reuse that value unless it remains negative,
  in which case they recompute. This is different from parser-level lifetime:
  the next command starts again with the parser's original f1.
- For each selected channel, c330/c334 first copy target +8 to prior target +12.
  Then prior status +29 gates addition of signed prior duration to accumulator
  +16. The setup gate is called at c3a4. After it returns, status +29 is set to 1,
  then target +8 becomes the post-call accumulator +16 plus post-call frame.
  A setup gate that returns early does not skip these caller-side writes.
- After a completed opcode01 call, c0c0 compares the dispatched opcode to 1,
  c0c8 clears r27, and c0e0 branches past the terminal fallback when r27 is zero.
  Terminal wait installation still follows. Suppression depends on completion,
  not whether a selected channel actually performed a setup dispatch.
- Setup requires both readiness pointers +1d88/+1d8c nonzero. For channel 1,
  the conjunction of marker +578 == 1 and marker +1db3 == 1 returns early.
  The signed byte blocked mask +1d9a is tested against `1 << channel`.
  A set bit calls `8004a41c` with r4=0 and returns without the unblocked follow-up.
  Otherwise mode-indexed dispatch runs; channel 1 then resets +6d8 and calls
  `8004d08c`. These are gate/dispatch facts, not proof of the called functions'
  complete effects.
- Byte +5 equal to zero branches over the tail conversion. Nonzero byte +5
  reaches `8004c3f8 c022870c` (`lfs f1,-30964(r2)`). With the previously recorded
  r2 basis `8043ea20`, that derives `8043712c`; the constant is still unsupported.
  No value was recovered or added, and the decompiler's unusual tail expression
  is not accepted as a semantic substitute.

Source comparison: `ghidra-export/chunk_0006.c` functions `8004c050`/`8004c298`
and `chunk_0005.c` function `80048648`. Their parameter lists and removed-block
warnings are not independently trusted ABI or control-flow proof. The exact-word
checks above resolve the f1 lifetime and ordering without relying on those lists.

## Validation and limits

Focused command:
`python -m unittest discover -s research/tools/matching-decomp -p test_archived_setup_command_evidence.py`
passes 8 synthetic-only tests: spoofed authentication, schema propagation,
allowlist scope, table width/entry, range width/digest/word mismatch, alignment and
bounds, independent fmr/default field checks and signed branch target decoding.
Both snapshot CLI runs pass with the final narrowed 396-byte handler range.
No raw archived payload fixtures or arbitrary address CLI. Repository aggregate
results are recorded in the source-owned dispatch plan, not treated as original
execution evidence.

Host finite-value checks, command-length and index bounds, budget exhaustion,
unsupported-opcode refusal, mode bounds, and failure diagnostics are defensive host
contracts. They are not proved by these target instructions and must remain
explicitly separated from archive instruction evidence.
