# Address-mapped constants from the archived ProgramDB

A read-only, format-based inspection recovered six previously unresolved constants
from both local Ghidra program snapshots. A second independent parser reproduced
all values and mappings without importing the first parser. This removes the
lack of locally address-mapped byte evidence for these constants. It does not
establish original-game replay, instruction matching, or unchanged retail bytes.

## Exact results

All addresses and byte strings below are hexadecimal. Values use PowerPC
big-endian interpretation.

| Address | Type | Stored bits | Exact value |
| --- | --- | --- | --- |
| 804370f0 | float32 | 3f800000 | 1 |
| 804370f4 | float32 | 00000000 | positive zero |
| 804370f8 | float64 | 4330000080000000 | 4503601774854144 = 2^52 + 2^31 |
| 80437128 | float32 | bf800000 | -1 |
| 8043d1fc | float32 | 3f800000 | 1 |
| 8043d310 | float64 | 3fe0000000000000 | 0.5 |

Four independently recorded original-DOL control values also match:
8043d1f8 = positive zero (00000000), 804374e4 = 2 (40000000),
804374b0 = 5 (40a00000), and 80437464 = -1 (bf800000).
Prior evidence is recorded in the [AObj clock audit](double-source-owned-dispatch-plan-2026-11-12.md#original-aobj-clock-and-callback-audit)
and [reaction-stream continuation audit](double-source-owned-dispatch-plan-2026-11-12.md#implemented-prerequisite-reaction-stream-continuation).
The controls check mapping, byte order and both physical data nodes. They do not
substitute for deriving each new target through the tables.

## Snapshot provenance

The two files were read without mutation from
`GotchaForce.rep.before_force_create/idata/00/~00000000.db/`:

| File | SHA-256 |
| --- | --- |
| db.3.gbf | 7b50dd2d2e17b4bfcc89a64cde27010247d0cbf0f48bd5c059f50275f40458d0 |
| db.4.gbf | 1f86813d91ea8e2c4564f96622ec42555e1dba2c78aa81ad654e892140d019f8 |

Both program snapshots identify `boot.dol`, language
`PowerPC:BE:32:Gekko_Broadway`, image offset `80000000`, and recorded executable
SHA-256 `21454a8880c6254616662710d6ec626e43d853999da2cdfad700030960a94836`.
Property Table root 9 records the executable hash and creation with Ghidra
12.1.2 as string properties (type 2). The version describes the recorded producer,
not a locally installed or executed Ghidra runtime.

The entire initialized `MAIN_.data5` block is byte-identical between snapshots:
27,360 bytes, SHA-256
`989c794b17fc95de6e57810f5c89db23d585c85a15faafc994d9a5bd9a0e61b4`.
No original block payload, capture, executable, or Ghidra distribution was
uploaded or added by this audit.

The File Bytes table is empty: root -1, record count 0. It cannot reconstruct
and hash the original imported file. Program metadata associates this database
with the executable hash, but does not prove the stored memory was never patched
after import. Agreement between saved snapshots and the prior controls likewise
does not prove that stronger claim. Treat these results as verified archived
ProgramDB bytes, not a newly verified unchanged original DOL.

## Structural derivation

The parser follows documented database relationships; it does not search for
expected scalar patterns or infer values from neighboring constants.

1. GBF magic is `2f30312c34292c2a`, version 1, block size 16,384. Logical buffer
   `i` occupies physical block `i + 1`; each has a five-byte flag/ID prefix.
   Free flags, logical IDs, lengths and reads are checked.
2. DBParms identifies master-table root 1. Primary schemas resolve Program
   root 2, ADDRESS MAP v1/root 10, Memory Blocks v3/root 13 and Sub Memory
   Blocks v3/root 12. The indexed auxiliary tables are not substituted.
3. Program's variable-key table stores `Image Offset` as hexadecimal `80000000`.
   Address-map entry 0 is undeleted `ram`, segment 0. All target blocks use the
   relocatable address-key type, which requires adding the image offset.
4. Memory block key 7 is `MAIN_.data5`: encoded start
   `2000000000436a20` resolves to `80436a20`; length is `6ae0`. Every target
   uniquely falls inside this block.
5. Subblock key 7 belongs to parent block 7, starts at offset 0, has length
   `6ae0`, and is type 2 (initialized BUFFER), source buffer 263. It is not an
   uninitialized, mapped or File Bytes subblock.
6. Chain 263 uses XOR-obfuscated indexed storage and data nodes 264 and 265.
   Indexed data-node capacity is 16,378 bytes, not the 16,384-byte physical block
   size. The documented XOR mask restarts at each child data node, indexed by
   the child-relative offset modulo 128.
7. Each target's full width fits in its memory block, subblock, chain and data
   node. Exact physical locations below agree between both files.

| Address | Chain offset | Data node | Offset within node data | Physical GBF offset |
| --- | --- | --- | --- | --- |
| 804370f0 | 6d0 | 264 | 6d0 | 4246d6 |
| 804370f4 | 6d4 | 264 | 6d4 | 4246da |
| 804370f8 | 6d8 | 264 | 6d8 | 4246de |
| 80437128 | 708 | 264 | 708 | 42470e |
| 8043d1fc | 67dc | 265 | 27e2 | 42a7e8 |
| 8043d310 | 68f0 | 265 | 28f6 | 42a8fc |

Node numbers 263/264/265 in the prose and table are decimal. Offsets and addresses
are hexadecimal. Stored GBF bytes at these positions are obfuscated; the scalar
bits above are the documented decoded result, not a direct raw-file float read.

## Reproduction and limits

Run the source-only checker against a local snapshot:

```sh
python3 research/tools/matching-decomp/read_archived_constants.py \
  'research/decomp/GotchaForce.rep.before_force_create/idata/00/~00000000.db/db.3.gbf'
python3 research/tools/matching-decomp/read_archived_constants.py \
  'research/decomp/GotchaForce.rep.before_force_create/idata/00/~00000000.db/db.4.gbf'
```

It reports only fixed target values and provenance metadata. It does not write
raw memory, modify the database, install Ghidra, call an emulator, access the rig
or publish code. The deliberately bounded reader rejects unsupported formats
rather than guessing. Its tests use synthetic tables and byte buffers, not game
assets or copied original blocks.

Run the synthetic regression tests with:

```sh
PYTHONDONTWRITEBYTECODE=1 python3 -m unittest discover \
  -s research/tools/matching-decomp -p 'test_archived_constants.py' -v
```

All 14 tests pass. They cover header/schema/bounds failures, address mapping,
indexed and nonindexed storage, per-child XOR restart and physical offsets.
One arithmetic test exhausts all 65,536 signed16 inputs: interpreting
`CONCAT44(0x43300000, (n & 0xffffffff) ^ 0x80000000)` as a double and subtracting
the recovered `4330000080000000` value yields exactly `n`, both before and after
float32 conversion. This is a synthetic arithmetic identity, not evidence of
original instruction execution or a completed setup/stream port.

Format references were read from official Ghidra source at pinned commit
`42db038f3c88c6bd7e9bedbb919138111f8b77fd`:

- [LocalBufferFile.java](https://github.com/NationalSecurityAgency/ghidra/blob/42db038f3c88c6bd7e9bedbb919138111f8b77fd/Ghidra/Framework/DB/src/main/java/db/buffers/LocalBufferFile.java), header and buffer prefix.
- [TableRecord.java](https://github.com/NationalSecurityAgency/ghidra/blob/42db038f3c88c6bd7e9bedbb919138111f8b77fd/Ghidra/Framework/DB/src/main/java/db/TableRecord.java), master schemas.
- [VarKeyRecordNode.java](https://github.com/NationalSecurityAgency/ghidra/blob/42db038f3c88c6bd7e9bedbb919138111f8b77fd/Ghidra/Framework/DB/src/main/java/db/VarKeyRecordNode.java), Program and property table records.
- [ChainedBuffer.java](https://github.com/NationalSecurityAgency/ghidra/blob/42db038f3c88c6bd7e9bedbb919138111f8b77fd/Ghidra/Framework/DB/src/main/java/db/ChainedBuffer.java), indexed storage and per-node XOR.
- [ProgramDB.java](https://github.com/NationalSecurityAgency/ghidra/blob/42db038f3c88c6bd7e9bedbb919138111f8b77fd/Ghidra/Framework/SoftwareModeling/src/main/java/ghidra/program/database/ProgramDB.java), image-offset key and hexadecimal conversion.
- [AddressMapDB.java](https://github.com/NationalSecurityAgency/ghidra/blob/42db038f3c88c6bd7e9bedbb919138111f8b77fd/Ghidra/Framework/SoftwareModeling/src/main/java/ghidra/program/database/map/AddressMapDB.java), relocatable address decoding.
- [MemoryMapDBAdapterV3.java](https://github.com/NationalSecurityAgency/ghidra/blob/42db038f3c88c6bd7e9bedbb919138111f8b77fd/Ghidra/Framework/SoftwareModeling/src/main/java/ghidra/program/database/mem/MemoryMapDBAdapterV3.java), memory/subblock schemas and types.

That source revision is not established as the exact producer revision. The
relevant schema versions, node layouts, types and decoded control values were
validated against both actual snapshots. No downloaded vendor code was executed.

This evidence does not change gameplay behavior by itself. Subsequent bounded
ports can explicitly cite the archived constants and retain the evidence limit;
original replay, numeric-environment parity and live clone activation still need
separate validation.
