# Projectile spawn 8007db5c: bounded archive evidence

## Fixed selection and authentication

This is static archived ProgramDB evidence, not original execution, MATCH,
runtime integration, live dispatch, or playability. The scope is exactly two
complete bodies and four individual variant1 fields: six reads, 832 bytes.
No additional allocator cells/helpers, projectile lifecycle bodies, assets,
adjacent rows, complete tables or pointer referents are selected.

Independent sources fixed each selection **before** targeted archive reads:

- `ghidra-export/chunk_0011.c:4210–4263`, `_index.tsv:1778–1779` and
  `../symbols/GG4E-CSM-20220412.map:979` establish
  `[8007db5c,8007dcec)`, map size190, 400 bytes/100 instructions.
- `ghidra-export/chunk_0012.c:6364–6445`, `_index.tsv:1948–1949` and
  `../symbols/GG4E-CSM-20220412.map:1061–1062` establish
  `[80088aa0,80088c40)`, map size1a0, 416 bytes/104 instructions.
- The spawn C independently supplies byte variant, stride38, family source
  `802d6d96`, signed joint source `802d6d6a`, vector source
  `-7fd29294 = 802d6d6c`, and signed offset flag source `802d6d94`.
  Actual715f8's already-authenticated type3 branch selects variant1.
  Thus row base `802d6d68 + 1*38 = 802d6da0`. Exact fields are
  family+2e=`802d6dce`/2 bytes, joint+2=`802d6da2`/**1 byte**,
  vector+4=`802d6da4`/12 bytes and flag+2c=`802d6dcc`/1 byte.
  The arithmetic was checked before reading. No complete row is needed.

Reader: `../tools/matching-decomp/read_archived_projectile_spawn_evidence.py`.
Tests: `../tools/matching-decomp/test_archived_projectile_spawn_evidence.py`.
Both preserve all existing authenticators/allowlists. Whole-snapshot SHA,
schemas, language/address maps, empty File Bytes table and complete data5
identity are authenticated first by unchanged `read_archived_constants`;
unchanged command mapping checks then authenticate text1/data3/data5.
Only six literal selections follow. SHA-256 is checked before decoding.
Every selected instruction has all admitted operands represented. Unknown or
reserved forms fail closed. The CLI accepts a snapshot path only.

| Snapshot | Whole-file SHA-256 |
| --- | --- |
| db.3.gbf | `7b50dd2d2e17b4bfcc89a64cde27010247d0cbf0f48bd5c059f50275f40458d0` |
| db.4.gbf | `1f86813d91ea8e2c4564f96622ec42555e1dba2c78aa81ad654e892140d019f8` |

Both snapshots agree on all selected instruction schedules, values, mappings
and physical spans. File Bytes table is version0, root−1, count0; block size16384,
master root1, image offset80000000. Executable SHA-256
`21454a8880c6254616662710d6ec626e43d853999da2cdfad700030960a94836`
is **import metadata**, not independent proof of unchanged original DOL bytes.

Text1 `[800055e0,802b0160)` has length2796416/root21. Data3
`[802bae60,803af120)` has length1000128/root199. The unchanged authenticator
also checks data5's full SHA
`989c794b17fc95de6e57810f5c89db23d585c85a15faafc994d9a5bd9a0e61b4`.

| Selection | Width | Value / interpretation | SHA-256 |
| --- | --- | --- | --- |
| 8007db5c | 400 | complete spawn body | `d759aaf2c9b38c2924ac451e7b29c4d67ef37c2d01492fc5654f04821eeaa0dc` |
| 80088aa0 | 416 | complete allocator caller | `800882bf558ba7e7f9e955e1884be71e0c9aad8870807bf7dc0876f56baaeab6` |
| 802d6dce | 2 | signed family3 | `583c7dfb7b3055d99465544032a571e10a134b1b6f769422bbb71fd7fa167a5d` |
| 802d6da2 | 1 | signed joint11 | `e7cf46a078fed4fafd0b5e3aff144802b853f8ae459a4f0c14add3314b7cc3a6` |
| 802d6da4 | 12 | f32 vector[55,+0,+0] | `f2c4bfd9a4763155499b7a93f506ddae33df56d5c4653e547547bdec2987ea19` |
| 802d6dcc | 1 | signed flag0 | `6e340b9cffb37a989ca544e6bb780a2c78901d3fb33738768511a30617afa01d` |

All physical/chain offsets below are decimal; the storage is obfuscated and
interpreted by the unchanged ProgramDB reader, not raw executable extraction.

| Selection | Root / data buffer | Chain offset | Data offset | Physical offset | Bytes |
| --- | --- | --- | --- | --- | --- |
| 8007db5c | 21 / 52 | 492924 | 1584 | 869942 | 400 |
| 80088aa0 | 21 / 54 | 537792 | 13696 | 914822 | 416 |
| 802d6dce | 199 / 206 | 114542 | 16274 | 3407768 | 2 |
| 802d6da2 | 199 / 206 | 114498 | 16230 | 3407724 | 1 |
| 802d6da4 | 199 / 206 | 114500 | 16232 | 3407726 | 12 |
| 802d6dcc | 199 / 206 | 114540 | 16272 | 3407766 | 1 |

## Ordered spawn facts

Addresses and field offsets below are hexadecimal. These are instruction-order
facts, not decompiler expression ordering or evidence of runtime integration.

1. `7db80` masks variant to low8 bits; `7db88` multiplies by38. `7db90`
   reads signed actor3e8 before `7db98` reads signed row+2e. Mismatch branches
   at7dba0 to epilogue7dccc without allocation.
2. `7dba4..7dbb0` set arguments pool3/group8/insertion0/descriptor-count1.
   `7dbb4` calls80088aa0 with the original actor. `7dbb8` records the returned
   pointer's zero test. Null branches to the epilogue at7dbbc.
3. Nonnull child stores occur in this exact order: `0=1`, `10=15`,
   `11=variant`, `c=8007dcec`, `10c=8007e698`, `8c=owner`; then owner copies
   `90,94,96,97,88,c8,cc,b8,b4`, followed by child`58,5c,60`, then`c0,c4,d0`.
   The94 load is unsigned16. b8/b4/58/5c/60/c0/c4 use actual lfs/stfs.
   Ownerb4 is reloaded independently before each of childb4,58,5c,60, rather
   than captured once. Callback addresses are stored identities, not followed
   code reads or implemented lifecycle claims.
4. `7dc70` loads row+2, `7dc74` sign-extends, `7dc78` multiplies by30 and
   `7dc7c..7dc80` compute owner+8d4+joint*30. `7dc84` calls8020b7a8 with
   this matrix, row+4 and child+20. Variant1 therefore uses actual joint11
   and vector[55,0,0]. A genuine joint matrix is required; owner position
   substitution or a dummy spawned flag cannot establish this operation.
5. Only after matrix multiplication does7dc88 load row+2c;7dc8c sign-extends
   with record. A nonzero byte calls8020ba54 at7dca0 with child20,owner7b0,
   child20. Variant1's authenticated zero flag skips this add.
6. Tail7dca4/7dca8 loads owner518 and51c **before** child144/148 stores.
   Then owner520→child14c, owner1afc→child150, owner1afd→child151. These
   bytes are source fields, not invented target identifiers. Return7dce8.

The SDK routines are reused, not reread: matrix-vector8020b7a8/84 bytes,
SHA`0e86b49668bd9172bfd1256aa2842a4326032efab48cb6b8df58523a63992e78`,
from `terrain-orientation-evidence-2026-11-13.md`; vector-add8020ba54/36 bytes,
SHA`c7b35d4075874e063982faa1d7d086e5d5ec4d70aed2b56c619b5e440e18e1ab`,
from `double-action-envelope-evidence-2026-11-14.md`.

## Ordered allocator-caller facts

1. `88ab4` compares signed descriptor count to8; `88ac8` enters capacity
   query only when count≤8. Above8 returns null. `88ad8` calls80197bec(0);
   `88adc` compares its signed return against requested count. Insufficient
   capacity returns null. These are real source gates, not permission to
   manufacture a capacity shortage to avoid the allocation path.
2. `88af0` calls80088d98(pool). Its recorded null result skips remaining
   work. Success first stores requested group byte atchild1 andff atchild85.
   Group−1 skips all table/link/descriptor handling.
3. Otherwise group<38, nonnull owner, signed owner83==0, and `(group&7)==0`
   jointly select remapping. Only then88b34 loads signed owner3e4;88b3c/b40
   compute group+signed-slot+1. For this call group8 becomes signed-slot+9.
   `88b48` stores final group byte;88b54 reads byte802da700[group] and88b58
   stores it tochild83. No contents of that table are authenticated here.
4. insertion0 reads old803c706c[group] at88b70, replaces it with child at
   88b74, then writes child4=0. If old was null,803c6f6c[group]=child and
   child8=0. Otherwise child8=old and old4=child. Nonzero insertion reverses
   the head/tail roles and4/8 links, as represented by88ba4..88be0.
5. Only after list mutation88be4 loads unsigned child2. Type4 skips descriptor
   creation. Other types loop exactly eight iterations, index0..7: if index
   is less than signed requested count,88c04 calls80006d4c and88c08 stores
   its r3 to child+e0+index*4. Otherwise88c10 stores0 there. Count byte99
   is stored only after the loop at88c24. Return pointer moves to r3 at88c28;
   terminal return88c3c.

This reader leaves80197bec,80088d98,80006d4c and their dependent pool/setup
semantics explicit boundaries. It does not assert a null descriptor callback,
free-list shape, pool size/type, eligible group value or successful allocation.
Those need independently bounded evidence and canonical mutable runtime state.
No positive spawn claim can be obtained merely by injecting a successful
allocator return or avoiding all dependencies with nulls.

## Checks

`python -m unittest discover -s research/tools/matching-decomp -p
 'test_archived_projectile_spawn_evidence.py' -v` passes **17 tests**.

- Independently authored inverse fixtures encode all204 operand rows to the
  fixed body hashes, then compare every decoder output field.
- All6,528 single-instruction bit mutations either reject or remain distinct
  and independently invert to their exact changed word.
- All6,656 selected-payload bit mutations refuse before interpretation.
- Exact selection inventory, row arithmetic, signedness, repeated loads,
  metadata/transform/tail order, allocator links and loop fields are checked.
- Mapping/width/type/duplicate/address/CLI failures precede targeted reads;
  whole-file, schema and selected-payload tampering refuse.
- Both existing snapshots authenticate. The traced read inventory is exactly
  the unchanged authenticator reads plus the six fixed selections above.
- Exact physical spans, complete body coverage and absence of raw code/range
  payload output are checked. No network fetch, installs, original executable,
  live telemetry, estimator import, commits or pushes occurred.

Local diagnostic reports are under ignored
`.tmp/projectile-spawn-evidence-20261114/`; they are not source artifacts and
are not required by synthetic tests.
