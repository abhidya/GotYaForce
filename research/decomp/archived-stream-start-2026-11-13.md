# Archived stream bootstrap and reset evidence (2026-11-13)

## Scope and provenance

`read_archived_stream_start_evidence.py` is a stdlib-only, read-only reader for
exactly two fixed instruction ranges. It reuses `read_archived_constants.inspect`
for snapshot SHA authentication, exact schemas, metadata/address-map checks,
full data5 digest and existing constants/controls, and
`read_archived_wait_evidence.text_mapping` for exact text mapping and overlap
rejection. It adds no constant target/control, dependency, arbitrary-address CLI,
raw-range export, or vendor-code execution. Selected instruction words and their
limited decoded fields are evidence, not a general PPC disassembler.

Inputs under `research/decomp/GotchaForce.rep.before_force_create/idata/00/~00000000.db/`:

- `db.3.gbf`: SHA256 `7b50dd2d2e17b4bfcc89a64cde27010247d0cbf0f48bd5c059f50275f40458d0`.
- `db.4.gbf`: SHA256 `1f86813d91ea8e2c4564f96622ec42555e1dba2c78aa81ad654e892140d019f8`.

Both authenticate independently and produce the same two range hashes:

- Bootstrap `zz_004beb8_`, `[8004beb8,8004c020)`, 360 bytes:
  `af8c9bb8f3fa6387ee864411f266f0757d936550f2ac0cfa50bfc3b2e35390a2`.
- Reset `zz_004c020_`, `[8004c020,8004c050)`, 48 bytes:
  `06c4624d1c2173dc6d487e2f4bec33c32b892011cddc144b09542c4a7e470629`.

Mapping in both: `MAIN_.text1`, block/subblock key 1, start `800055e0`,
length 2796416, buffer chain root 21. Both ranges occupy data buffer 39:
bootstrap chain offset 288984, data offset 10558, physical offset 665924;
reset chain offset 289344, data offset 10918, physical offset 666284.
Both spans are marked obfuscated by the existing parser.

These are matching archived ProgramDB bytes, not proof of fresh original DOL
bytes or live-runtime parity. Executable SHA256 metadata is
`21454a8880c6254616662710d6ec626e43d853999da2cdfad700030960a94836`;
import metadata is not proof of unchanged original executable bytes. The
`File Bytes` table has version 0, root -1 and count 0, so it supplies no stored
original-file payload to close that provenance gap. The reader preserves those
metadata and File Bytes caveats in its JSON output.

## Bootstrap facts and their interpretation

Source cross-reference: `research/decomp/ghidra-export/chunk_0006.c:1431–1530`.
The reader reports 17 selected bootstrap instruction facts, with exact word
checks after checking the complete range hash:

- `8004bee4` loads byte `+579`, `bee8` sign-extends it, and `beec` ANDs
  it with the requested channel mask. Treating that byte as unsigned would lose
  the source's sign-extension behavior.
- Shared-bank group indexing: `bf40` is `rlwinm r0,r28,1,24,30`, equivalent
  to `(group & 0x7f) << 1`; `bf44` is signed-halfword `lhax`; `bf48` adds
  that displacement to the selected bank base.
- The source chooses the bank from the original selector's bit 7. Only the
  original selector zero takes the default `+582` byte path. `bf90` loads
  that byte, `bf94` sign-extends it, and `bf98` adds it to the zero group.
  It does not reselect the bank after defaulting. This control-flow statement
  is from the cited source plus authenticated range, not from a branch decoder.
- Family group indexing: `bf9c` is `rlwinm r0,r28,1,0,30` (the `slwi r0,r28,1`
  alias); `bfa0` loads a signed halfword; `bfa4` adds it to the family base.
- Slot indexing: `bfa8` is `slwi r0,r29,1`, `bfb0` is a signed-halfword load,
  and `bfbc` forms the final parser pointer in r22. That pointer is formed
  before selected channel group/action stores at `bfcc` (`+18`) and `bfd4`
  (`+19`), and the ensuing reset call shown by the source.
- PPC shifts and adds have 32-bit wraparound semantics. A bounded signed cursor
  displacement used locally by the host reconstruction is a representation of
  that displacement, not evidence of an additional PPC conversion instruction.

The source additionally resets all four channels and marks them finished when
its selected bank is absent. This is source control-flow evidence; the narrow
reader does not emulate the routine or prove host memory ownership/bounds.

## Reset store order

`8004c020` is `lfs f0,-31020(r2)`. In the existing source mapping that is
`FLOAT_804370f4`, already an established constant-reader target. Both snapshots'
existing constant result is `00000000` (float +0), returned as `reset_zero` without
adding a new constant target or control. `c024` is `li r0,0`.

The nine stores, in instruction order, are:

1. `c028`: `stfs f0,0x0c(r3)`, previous.
2. `c02c`: `stfs f0,0x10(r3)`, accumulator.
3. `c030`: `stfs f0,0x08(r3)`, target.
4. `c034`: `stb r0,0x1d(r3)`, status.
5. `c038`: `stb r0,0x1e(r3)`, event.
6. `c03c`: `stw r0,0x04(r3)`, next.
7. `c040`: `stw r0,0x00(r3)`, current.
8. `c044`: `stfs f0,0x14(r3)`, wait.
9. `c048`: `stb r0,0x1a(r3)`, finished.

Thus reset does not clear group/action at `+18/+19`. These labels describe the
reconstruction's fields; the instruction evidence establishes offsets, store
widths, source registers and order. The float constant is archived evidence,
not a claim about a captured live r2 register.

## Reproduction and validation

From the repository root:

```sh
PYTHONDONTWRITEBYTECODE=1 python -m unittest discover \
  -s research/tools/matching-decomp -p test_archived_stream_start_evidence.py -v
PYTHONDONTWRITEBYTECODE=1 python research/tools/matching-decomp/read_archived_stream_start_evidence.py \
  'research/decomp/GotchaForce.rep.before_force_create/idata/00/~00000000.db/db.3.gbf'
PYTHONDONTWRITEBYTECODE=1 python research/tools/matching-decomp/read_archived_stream_start_evidence.py \
  'research/decomp/GotchaForce.rep.before_force_create/idata/00/~00000000.db/db.4.gbf'
```

Validation: 10 synthetic tests passed; both authenticated reader CLIs passed.
Tests cover exact mapping and overlap/lineage guards, synthetic signed D forms,
integer register fields and reserved-bit rejection, rotation fields, selected
word facts/reset order, unknown-range/alignment/bounds/short-read/hash/word
rejection, authentication-before-parser and schema-error propagation, existing
4 MiB chain bound, and no constant/control expansion. No archived payload
fixtures are embedded in the tests. No heavy aggregate, live rig access,
proprietary execution, installation, download, upload or publication was used.
