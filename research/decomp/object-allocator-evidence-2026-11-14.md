# Object and descriptor allocator: bounded archive evidence

Date: 2026-11-14. Investigation base: `79db39a9b22ce90cc2e95f15d3df7177f39c7369`.

The [fixed reader](../tools/matching-decomp/read_archived_object_allocator_evidence.py)
authenticates **six code spans, 126 instructions and eight typed metadata
selections: 526 selected bytes in fourteen reads** after the unchanged archive
authenticator. The [tests](../tools/matching-decomp/test_archived_object_allocator_evidence.py)
provide an independent inverse encoder and frozen semantic schedules.

This is static archived ProgramDB evidence. It is not original-DOL identity,
execution, `MATCH`, live dispatch, successful runtime integration or playability.
No original code was executed. No shared reader/allowlist was changed. The
separate [projectile-spawn evidence](projectile-spawn-evidence-2026-11-14.md)
owns complete `8007db5c` and `80088aa0`; neither body is selected here.

## Selection was narrowed in stages

Every stage checked existing named C/index/map evidence before its archive
selection. Scratch probes under ignored `.tmp/object-allocator-evidence-20261114`
record the separate stages; they are discovery work, not the durable allowlist.
The final reader contains only literal addresses, widths, types and hashes.
Returned pointer/type values do not dynamically select any read.

1. Ordinary battle setup `8002844c`, `ghidra-export/chunk_0003.c:3670–3671`,
   calls `197854(1)` then `88398(arena+fe800,e0000,0)`. Adjacent index entries
   517–518 bound this setup; it has no community map row. This is mode-selection
   provenance, not authentication or execution of the setup instructions.
2. `197854`, chunk0048:1158–1177, selects `PTR_DAT_8036fa18[mode]`. The first
   stage reads **8036fa1c/4**, exactly the mode1 pointer cell. It separately
   reads object mode0/pool3 type **802da673/1** and capacity **802da67e/2**,
   from the typed `88398` configuration layout: eight type bytes followed by
   eight u16 capacities, row stride24. C lines5996–6072, adjacent index entries
   1945–1946 and map1058 independently identify that constructor.
3. Those three cells establish descriptor row0 base **8036f644**, object type3
   and capacity512. After reporting these values, the second selection is only
   descriptor row0 stride **8036f654/2** and init callback **8036f658/4**, plus
   type3 size **802da666/2**. The offsets are independently typed by
   `197950`/`197a0c`: descriptor row stride28, signed16 record stride at+10,
   callback at+14; object size lookup is `802da660+2*type`. No complete28-byte
   row was read. Arena offset+00, extent+04, active/free heads+08/+0c, initial
   count+12, release callback+18 and neighboring rows remain unread.
4. The callback is **nonnull80006f60**, not a null initializer. This function
   lacks a named C/index/map entry. The preceding named `80006f1c` has map
   size44, independently ending at06f60; the next named C/index/map start is
   `80006f78` (chunk0000:1491, index49, map47). This independently bounds
   **[80006f60,80006f78),24 bytes**, selected only after reporting the callback
   value. The six decoded instructions contain no branches or calls and end
   in `blr`, proving a complete straight-line returning callback in that
   window. This is **not** a map-named complete-function extent.
5. `88aa0` explicitly selects classification table `802da700[group]`.
   Requested group8 independently selects **802da708/1**. Actor83==0 remaps
   that request to signed slot3e4+9. Before reading **802da709/6**, the domain
   was checked in `800536b0`, chunk0006:6528–6555: it initializes actual3e4
   from0 and loops while index<6. Thus groups9..14 are selected for those six
   initialized main-actor slots only. No other group classifications are read.

Constructors `197854`, `197950`, `88398`, `8853c` and battle setup provide C
provenance only; their instructions are not newly authenticated here. In
particular, C `197950` does not overwrite callback14/18, so assuming null from
initialization would have hidden the real callback. An explicitly synthetic
pool fixture can establish initial lists/counts, but these selected metadata
fields do **not** authenticate a source descriptor arena capacity or initial
pool state. Allocation success must come from actual modeled pool operations,
not a supplied success flag or fabricated null callback/type4.

## Whole-snapshot authentication and mappings

Both existing snapshots agree on every selected value, instruction operand,
hash, mapping and physical span:

| Snapshot | Whole-file SHA-256 |
| --- | --- |
| db.3.gbf | `7b50dd2d2e17b4bfcc89a64cde27010247d0cbf0f48bd5c059f50275f40458d0` |
| db.4.gbf | `1f86813d91ea8e2c4564f96622ec42555e1dba2c78aa81ad654e892140d019f8` |

Unchanged `read_archived_constants.inspect` verifies the actual whole-file
hash, schemas, language/address map, empty File Bytes table and existing data5
identity/controls before selections. Unchanged `command.mappings` verifies
text1/data3/data5 identities, subblocks and overlap constraints. File Bytes is
version0/root−1/count0; image offset80000000; block size16384/master root1.
Stored executable SHA-256 metadata
`21454a8880c6254616662710d6ec626e43d853999da2cdfad700030960a94836`
is not an independently measured original-DOL hash.

- text1: `[800055e0,802b0160)`, length2796416, block/subblock1, chain root21.
- data3: `[802bae60,803af120)`, length1000128, block/subblock5, chain root199.
- Both selected mappings are initialized subblock type2, zero starting/source
  offsets. Only the exact fourteen additional selections are made.
- Global resolution of r13−21024 to80436380 uses the previously recorded
  r13=`8043b5a0` basis, not fresh startup authentication or live register proof.

## Fixed code extents

| Entry | End exclusive | Bytes / instructions | Independent bounds | SHA-256 |
| --- | --- | --- | --- | --- |
| 80088d98 | 80088e50 | 184 /46 | chunk0012:6517–6540, index1950–1951, map1063 | `a134e40d302eb33d6ebc1c3dd371228809562bdc533d833bebf095b19180ab44` |
| 80197bec | 80197c00 | 20 /5 | chunk0048:1346–1352, index7239–7240, map2484 | `cdcbfde48212824dc444a6b18aab2c256ffdcb4fec35ad9a18b332b9529c0995` |
| 80197bd8 | 80197bec | 20 /5 | chunk0048:1335–1342, index7238–7239, map2483 | `8a8dd5a501652fd1370ed64d05ed17044aada0fa4bf21eecf6b6f13f0809eaea` |
| 80197a0c | 80197ad8 | 204 /51 | chunk0048:1244–1276, index7235–7236, map2480 | `96222c5bda44dae9f8bb740618f6f8c5d08d455044410156499752c80db51a82` |
| 80006d4c | 80006d80 | 52 /13 | chunk0000:1356–1367, index42–43, map40 | `ac9afd93b2bee5eca79b75684fcff6a276cadb29e4509e2d0db46a38c42dc3e2` |
| 80006f60 | 80006f78 | 24 /6 | bounded gap described above; no named extent | `0070931fd4199aa0583862fedea3296041d962fd44af91ecdc761c907a85f6a0` |

Every instruction is represented, including operand direction, widths,
signedness, record bits, branch targets and the terminal return. Direct
non-call branches stay within their selected complete bodies. Direct calls
and the one indirect-call site are separately fixed. Unsupported/reserved
forms fail closed; no raw instruction or payload dump is emitted.

## Selected metadata values

| Cell / width | Meaning | Value | SHA-256 |
| --- | --- | --- | --- |
| 8036fa1c /4 | mode1 descriptor row root | 8036f644 | `9013485b6a5daf0c7505ce80059edadf81f64480ebe7c725e1e71ec34f576aa6` |
| 802da673 /1 | signed pool3 type | 3 | `084fed08b978af4d7d196a7446a86b58009e636b611db16211b65a9aadff29c5` |
| 802da67e /2 | unsigned pool3 capacity | 512 | `99be5efb88ca2013bd8e4eb035fd42d5245468fe9afa70d8ba9c1c419a48c4e8` |
| 8036f654 /2 | signed descriptor0 stride | 44 (2c) | `59b94638773b642b87af5d2478ec16fbeb99d878d318561ce058787ce46bb46e` |
| 8036f658 /4 | descriptor0 allocation callback | 80006f60 | `7c9a350375faea6aeb1a90130cee6f8b49293167cabd747aa6d5520705b85a3f` |
| 802da666 /2 | unsigned object type3 size | 740 (2e4) | `12edb515547ea77eb8d10532d4901e878a52732d60408d9960513e6946c5e3d5` |
| 802da708 /1 | group8 classification byte | 16 | `c555eab45d08845ae9f10d452a99bfcb06f74a50b988fe7e48dd323789b88ee3` |
| 802da709 /6 | group9..14 classification bytes | 16,16,16,16,16,16 | `39dda76eea065c7cb80b4b9b82c279acd5e5aa5f145114a96dddf5e00c4fc46b` |

## Physical provenance

Offsets below are decimal. Every selected payload uses obfuscated ProgramDB
storage decoded by the unchanged chain reader. Both snapshots have these exact
same physical spans; no selection crosses a data-buffer boundary.

| Selection | Root / data buffer | Chain offset | Data offset | Physical offset | Bytes |
| --- | --- | --- | --- | --- | --- |
| 80088d98 | 21 /54 | 538552 | 14456 | 915582 | 184 |
| 80197bec | 21 /122 | 1648140 | 10340 | 2025578 | 20 |
| 80197bd8 | 21 /122 | 1648120 | 10320 | 2025558 | 20 |
| 80197a0c | 21 /122 | 1647660 | 9860 | 2025098 | 204 |
| 80006d4c | 21 /22 | 5996 | 5996 | 382834 | 52 |
| 80006f60 | 21 /22 | 6528 | 6528 | 383366 | 24 |
| 8036fa1c | 199 /245 | 740284 | 3274 | 4033744 | 4 |
| 802da673 | 199 /207 | 129043 | 14397 | 3422275 | 1 |
| 802da67e | 199 /207 | 129054 | 14408 | 3422286 | 2 |
| 8036f654 | 199 /245 | 739316 | 2306 | 4032776 | 2 |
| 8036f658 | 199 /245 | 739320 | 2310 | 4032780 | 4 |
| 802da666 | 199 /207 | 129030 | 14384 | 3422262 | 2 |
| 802da708 | 199 /207 | 129192 | 14546 | 3422424 | 1 |
| 802da709 | 199 /207 | 129193 | 14547 | 3422425 | 6 |

## Ordered allocation facts

All PCs and object-field offsets in this section are hexadecimal.

### Object pop80088d98

1. `88dc0` loads pool free head using pool×4; null returns through88e30 with
   no count, link, type-size or memset effects.
2. `88dd8` uses **lhzx** on `803c71ac+2*pool`, so object free count is u16.
   `88ddc` subtracts1 and `88de0` stores low16 with **sthx**. It does not test
   this count for positivity after finding a nonnull head.
3. `88de4` loads popped object+04, `88dec` stores that pointer as free head.
   When null, `88e00` clears the corresponding `803c718c` free tail. Count is
   already decremented before either source link load/store.
4. `88e04` saves type byte+02. `88e14` sign-extends it, `88e1c` doubles the
   index, `88e20` loads the u16 size from802da660. `88e24` calls8000540c with
   `(poppedObject,0,size)`. For the selected type3, size is740, not a guessed
   common actor size.
5. `88e28` restores byte+02; `88e2c` writes byte+03=pool. `88e34` moves the
   retained popped identity into r3 for return. This is an existing object
   record, not a newly fabricated successful object.

8000540c remains a named memset call boundary. Logical all-byte zeroing is a
valid explicitly non-aliased owned-storage modeling contract, but this reader
does not authenticate libc's internal store ordering, fault ordering or alias
behavior. A canonical byte-backed object's links and other fields must really
be cleared, not retained in parallel host-only fields after memset.

### Descriptor count and allocation80197a0c

- `197bec` multiplies pool by28, adds row offset18 and uses **lhax**. Its
  return is signed16; `197bd8` writes low16 with **sthx** at that same cell.
  This is independent of the object's u16 free count.
- `197a30/34` capture the descriptor row address before calling197bec.
  `197a3c` records the returned count; `197a40` skips allocation if not
  positive. The selected positive path calls197bd8(count−1) at197a4c.
- `197a50` reads row.free+0c; `197a5c` reads descriptor.next+00;
  `197a60` updates row.free. Then `197a64` clears descriptor.next+00,
  `197a68` sets byte+09=1, and `197a6c` sets byte+0a=0.
- `197a70` reads old row.active+08; `197a78` saves it to descriptor.prev+04.
  If nonnull, `197a80` reloads the old active pointer and `197a84` sets its
  next+00 to the new descriptor. `197a88` installs row.active=new descriptor.
- Only **after** these count/list/flag effects does197a8c load callback+14.
  The nonnull branch passes the descriptor in r3, loads CTR at197a9c and
  calls through CTR at197aa0. An unsupported callback would be a boundary
  here with all preceding effects retained, not a rolled-back allocation.
- A nonzero callback result calls197ad8 at197ab0 and clears retained r30.
  That cleanup body/release lifecycle is not read here. The selected actual
  callback returns zero, so this cleanup is unreachable on its normal return.
- `197abc` returns retained r30 in r3. The callback's own r3=0 return does not
  replace the descriptor identity returned by197a0c.

### Actual nonnull callback80006f60 and wrapper80006d4c

The selected callback executes exactly:

1. `06f60`: r0=0.
2. `06f64`, `06f68`, `06f6c`: word stores zero to descriptor+20,+24,+28,
   in that order. These are the last twelve bytes of the44-byte record.
3. `06f70`: r3=0. `06f74`: unconditional return. No nested calls or branches.

`06d54` prepares pool0 in r3; `06d5c` calls197a0c. If its returned r3 is
nonnull, `06d6c` writes zero to descriptor+0c. No later instruction changes
r3 before `06d7c` returns. **The wrapper returns the descriptor pointer despite
the C decompiler's `void` declaration.** The write to+0c occurs after the
callback20/24/28 stores and after197a0c returns, not as an initial blanket
zeroing of the descriptor.

## Verification and claim ceiling

Commands, all completed locally without installs or original execution:

```
python -m unittest discover -s research/tools/matching-decomp -p test_archived_object_allocator_evidence.py -v
python research/tools/matching-decomp/read_archived_object_allocator_evidence.py research/decomp/GotchaForce.rep.before_force_create/idata/00/~00000000.db/db.3.gbf
python research/tools/matching-decomp/read_archived_object_allocator_evidence.py research/decomp/GotchaForce.rep.before_force_create/idata/00/~00000000.db/db.4.gbf
```

Twelve tests pass, including all126 independently re-encoded instruction
operands/hashes,4032 one-bit decoder controls,4208 selected-payload bit
mutations, precise14-read traces after unchanged authentication, physical span
checks, schema/digest/mapping/type/width/duplicate/refusal controls, ordered
count/list/callback/return checks, independent C/index/map bounds and CLI scope.
Tests export `EXPECTED`, `BODIES` and `PAYLOADS` for independent downstream
controls; these are static fixtures, not generated from the reader under test.
Derived complete reports are `.tmp/object-allocator-evidence-20261114/db3.json`
and `db4.json`; scratch initial selections remain visibly separate.

Positive allocation is now evidenced through actual object pop/memset/list
insertion (88aa0 in the separate spawn note), descriptor pop/active insertion,
real nonnull initialization callback and returned pointer. A runtime still has
to implement and test those operations on genuinely owned canonical records.
Synthetic initial state is not source setup execution. Flight, collisions,
rendering, descriptor release, other object types/pools/groups and estimator
work remain outside this evidence slice.
