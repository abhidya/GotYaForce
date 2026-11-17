# Archived stream command 0x10 evidence

The bounded stdlib-only reader `research/tools/matching-decomp/read_archived_command_evidence.py`
authenticates both existing allowlisted ProgramDB snapshots and reproduces the same
selected command evidence. It reuses the constants reader's exact schema, executable
metadata, empty File Bytes, address-map, full data5 hash and four independent control
checks. It additionally requires exact text1, data3 and data5 block/subblock mappings,
fixed range hashes and selected instruction words. There is no arbitrary-address CLI,
LLVM dependency, game execution or full raw-range/disassembly output.

## Provenance and boundaries

These are archived Ghidra ProgramDB bytes, not a newly read original DOL. The empty
File Bytes table and recorded executable SHA256 do not prove the imported memory
remained unchanged. Agreement between two snapshots is useful corroboration, not
independent original-DOL evidence or runtime proof. The new unsigned conversion bias
is the twelfth constants target and an `EXPECTED_TARGETS` entry, not a fifth original-DOL
control. The original four controls are unchanged.

`docs/static-recompilation-spike.md:178` records r2 as `0x8043ea20`. With that recorded
base, the selected `lfd f1,-30944(r2)` at `0x8004cb0c` addresses `0x80437140`.
Startup r2 was not freshly verified by this work; this dependency is also explicit
in the reader output. Scratch cross-checking used the already installed LLVM PPC
disassembler; the reusable reader only checks fixed words and returns selected
annotations, with no decoder dependency.

## Fixed ranges and physical lineage

All three mappings have a single type-2 subblock, starting offset zero and source
offset zero. Both snapshots give identical spans:

| Evidence | Block / subblock | Block start and length | Chain / data buffer | Chain / data offset | Physical offset |
| --- | --- | --- | --- | --- | --- |
| 72-byte dispatcher at `0x802d0da0` | 5 / 5, MAIN_.data3 | `0x802bae60`, `0xf42c0` | 199 / 205 | 89920 / 8030 | 3383140 |
| Entry 16 at `0x802d0de0` | 5 / 5 | same | 199 / 205 | 89984 / 8094 | 3383204 |
| 552-byte handler at `0x8004caa4` | 1 / 1, MAIN_.text1 | `0x800055e0`, 2796416 | 21 / 39 | 292036 / 13610 | 668976 |
| 8-byte bias at `0x80437140` | 7 / 7, MAIN_.data5 | `0x80436a20`, 27360 | 263 / 264 | 1824 / 1824 | 4343590 |

Entry 16 resolves to `0x8004caa4`. The handler ends at exclusive `0x8004cccc`.
The range SHA256 values are:

- Dispatcher: `fdf7c34d3ce203b91e168f8ea7ce7873e7140b5dbf1a6d5cb1710cbe868d260e`.
- Handler: `3f978a468ff1f6ff295694c851e4858ca611b1d4877b0bb17962cf03f7273254`.
- Bias: `2b2979f362d94c89fe17a6e01637f14332de063fe7a544bdc5facfc046f4169f`.

## Supported interpretation

The entry advances the cursor by four bytes and reads byte 2 as the mode. For mode
1, the four unrolled low-mask-bit tests select slots 0 through 3. Byte 3 is loaded
unsigned, concatenated beneath the high word `0x43300000`, loaded as f64, and has the
bias `0x4330000000000000` (2^52) subtracted with `fsubs`. Stores at object offsets
`0x1ce4`, `0x1d04`, `0x1d24` and `0x1d44` correspond to the selected slots'
`accumulator10` fields. The result is the byte's nonnegative f32 value. Synthetic
arithmetic tests exhaust all 256 possible byte values; these tests are not execution
of the original handler.

For mode 2, the count-register loop executes twice with two slot tests per iteration,
covering the same low four mask bits. The paired stores address `0x1b04` and `0x1b44`,
then advance the base by `0x80`, covering four `mirror30` fields at stride `0x40`.
For a selected slot, byte 3 equal to 1 writes zero, 2 writes one, and 3 applies XOR 1
to the existing byte. XOR preserves all higher bits: this is not boolean negation.
Byte 3 equal to zero or at least four leaves the field unchanged. Unselected slots
are untouched. The comparison/branch words and representative paired-loop writes
are included in the selected instruction facts; the full range hash pins omitted
instructions too.

Modes 0 and 3 and playback bootstrap remain unimplemented by this scoped work.
This evidence does not establish end-to-end stream playback or game playability.

## Reproduction and focused checks

From the repository root:

```sh
python -m unittest discover -s research/tools/matching-decomp -p 'test_archived*.py' -v
python research/tools/matching-decomp/read_archived_command_evidence.py 'research/decomp/GotchaForce.rep.before_force_create/idata/00/~00000000.db/db.3.gbf'
python research/tools/matching-decomp/read_archived_command_evidence.py 'research/decomp/GotchaForce.rep.before_force_create/idata/00/~00000000.db/db.4.gbf'
```

All 31 focused archive tests passed. Both command CLI outputs matched after removing
only the snapshot name and snapshot SHA256. Tests cover authentication propagation,
mapping rejection, range alignment/bounds/hash/width guards, selected-word mismatch,
output scope, preserved independent controls, and exhaustive unsigned-byte conversion.
These focused evidence checks require no heavy aggregate, network access, installs,
rig operations or uploads.
