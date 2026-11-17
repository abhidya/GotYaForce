# Projectile state3 cleanup: bounded archive evidence

Date: 2026-11-14. Investigation base:
`fa93569eee211c8a53cca725751132c2052db670` (preserved, no commit or push).

The [fixed reader](../tools/matching-decomp/read_archived_projectile_cleanup_evidence.py)
authenticates **nine fixed selections /1100 bytes**, including two scalar
cells and seven complete code bodies containing **273 instructions**. The
[tests](../tools/matching-decomp/test_archived_projectile_cleanup_evidence.py)
manually specify all operands, independently inverse-encode them, and cover
every selected bit. Both existing snapshots agree on all selected operands,
cells, mappings and physical spans.

This is **static archived ProgramDB evidence**, not original-DOL identity,
original execution, `MATCH`, live dispatch, runtime integration or playability.
The cleanup code really contains group/draw unlink, descriptor teardown and
object-pool return operations, but the JObj unreference implementation remains
an explicit unselected boundary. No existing reader, authenticator, shared
allowlist or shared decoder was changed.

## Selections and provenance recorded before reads

Initial scope was saved in ignored
`.tmp/projectile-cleanup-evidence-20261114/scope.json` before either archive
was opened. These six bodies and two cells were selected independently:

| Selection | Width | Independent basis |
| --- | --- | --- |
| `802d6fa4` | 4 | Previously authenticated root callback `8007dcec`: table `802d6f98` plus signed state3 times4. No neighboring state cell. |
| `8007e678` | 32 | `ghidra-export/chunk_0011.c:4626–4639` and `_index.tsv:1783–1784` identify candidate `8007e678`, next entry `8007e698`; C directly calls `88e50`. **No named map extent.** |
| `80088e50` | 328 | `chunk_0012.c:6544` onward, index1951, map1064 size `0x148`; direct call from independent candidate C. |
| `80089444` | 272 | `chunk_0013.c:247` onward, index1955, map1068 size `0x110`; direct draw-unlink call from `88e50` C. |
| `80006d80` | 72 | `chunk_0000.c:1372` onward, index43, map41 size `0x48`; direct descriptor-teardown call from `88e50` C. |
| `80197ad8` | 188 | `chunk_0048.c:1280` onward, index7236, map2481 size `0xbc`; direct call from `6d80` C. |
| `80089814` | 132 | `chunk_0013.c:440` onward, index1961, map1074 size `0x84`; final direct call from `88e50` C. |
| `8036f65c` | 4 | Previously authenticated battle descriptor root `8036f644`; descriptor0, C `197ad8` row stride `0x1c`, release offset `0x18`: literal `8036f644 + 0*0x1c + 0x18`. |

The release cell was first read alone after complete authentication. It was
**nonnull `80006ed8`** in both snapshots, not zero. This finding was reported
before any additional selection. No callback body was initially preselected.

Second-stage scope was then recorded in ignored `scope-stage2.json`, before
the callback body was accessed. Independently, committed
`chunk_0000.c:1457–1477` and `_index.tsv:47–48` give entry `80006ed8`, next
entry `80006f1c`; map45 explicitly names `80006ed8` with size `0x44`.
Those sources justify the single additional fixed **68-byte** selection
`[80006ed8,80006f1c)`. C describes rereading descriptor0c, conditionally
unreferencing its JObj, clearing0c after return and returning0. The already
reported scalar target is joined to this independently bounded body. No
following callback, arbitrary pointed-to body or Unref implementation is read.

The final reader checks both identity joins explicitly:
`802d6fa4 -> independently selected8007e678` and
`8036f65c -> independently selected80006ed8`. Returned pointers never choose
a read address or extent. Reused `8008aff0`, `80197bec` and `80197bd8`
identities/semantics are not reread. Data-table contents reached at runtime,
neighboring state cells, and `8024fd74` are outside this reader's selections.

## Authentication and payload identities

Unchanged `read_archived_constants.inspect` first authenticates the actual
complete SHA-256, all supported schemas, language/address map, metadata,
empty File Bytes table, and complete data5 identity/controls. Unchanged
`command.mappings` checks text1/data3/data5 mappings, subblocks and overlap
constraints. The exact typed text1/data3 mappings are checked again before
selected reads. Selected width and SHA-256 are checked before instructions
or scalar targets are interpreted.

Archives already exist under
`GotchaForce.rep.before_force_create/idata/00/~00000000.db/`:

| Snapshot | Bytes | Complete SHA-256 |
| --- | --- | --- |
| `db.3.gbf` | 57655296 | `7b50dd2d2e17b4bfcc89a64cde27010247d0cbf0f48bd5c059f50275f40458d0` |
| `db.4.gbf` | 58802176 | `1f86813d91ea8e2c4564f96622ec42555e1dba2c78aa81ad654e892140d019f8` |

File Bytes version0/root−1/count0; image offset `80000000`; block size16384;
master root1. Executable metadata SHA-256
`21454a8880c6254616662710d6ec626e43d853999da2cdfad700030960a94836`
is import metadata, **not an independently measured original-DOL hash**.
Full data5 SHA-256:
`989c794b17fc95de6e57810f5c89db23d585c85a15faafc994d9a5bd9a0e61b4`.

- text1: `[800055e0,802b0160)`, length2796416, block/subblock1, chain root21.
- data3: `[802bae60,803af120)`, length1000128, block/subblock5, chain root199.
- Both mappings: initialized subblock type2, starting/source offsets0.

| Selection | Width | SHA-256 |
| --- | --- | --- |
| `802d6fa4` | 4 | `a6c03f0cd98471891b5199d09bdedc269455f2281a76e92818c15baaef0ed389` |
| `8036f65c` | 4 | `6146361b1fa0fc8c864ab07ecfd5700f34b9dee55187fc418c57c1403c63a484` |
| `8007e678` | 32 | `3e7f2e5665b4173038c13f23df183d62e6483e1258dff141a07504568b6ef994` |
| `80088e50` | 328 | `c747b919f60eaad0d8b255db2b1fdc9ecb0bd22cea33c4930d1085dcdf34d3f4` |
| `80089444` | 272 | `662fe9d92fabf618cf21cc81fdcc266d090bda7b674bc9ad28266a89be6e2bf2` |
| `80006d80` | 72 | `af3ef03d2ff4dfbd26b5e33794ffac72543f7b6b70aaa2a0c7f7af14cdf13768` |
| `80197ad8` | 188 | `e3650544ce98694f5c3a5ca208c4dfe1479fbc02f46712a3a8a75d8d210c9082` |
| `80089814` | 132 | `1bb689f99364d17b27d89cf9d15ceb89ffde7be29dc90d4bba30b495975710dd` |
| `80006ed8` | 68 | `cedb8b8e89d09bc76af3e72117c07093a720afee20d40d3d397737a9353c2492` |

## Physical provenance and exact read trace

The unchanged obfuscated-chain reader produces these identical spans in both
snapshots. Offsets below are decimal. `89444` crosses a buffer boundary after
214 bytes, splitting one instruction across buffers; concatenation precedes
the payload hash and instruction decoding.

| Selection | Root /data buffer | Chain offset | Data offset | Physical offset | Bytes |
| --- | --- | --- | --- | --- | --- |
| `802d6fa4` | 199 /207 | 115012 | 366 | 3408244 | 4 |
| `8036f65c` | 199 /245 | 739324 | 2314 | 4032784 | 4 |
| `8007e678` | 21 /52 | 495768 | 4428 | 872786 | 32 |
| `80088e50` | 21 /54 | 538736 | 14640 | 915766 | 328 |
| `80089444`, first span | 21 /54 | 540260 | 16164 | 917290 | 214 |
| `80089444`, second span | 21 /55 | 540474 | 0 | 917510 | 58 |
| `80006d80` | 21 /22 | 6048 | 6048 | 382886 | 72 |
| `80197ad8` | 21 /122 | 1647864 | 10064 | 2025302 | 188 |
| `80089814` | 21 /55 | 541236 | 762 | 918272 | 132 |
| `80006ed8` | 21 /22 | 6392 | 6392 | 383230 | 68 |

Exact additional chain calls in the final reproducible reader, after unchanged
full authentication:

```
(199,115012,4,1000128)
(199,739324,4,1000128)
(21,495768,32,2796416)
(21,538736,328,2796416)
(21,540260,272,2796416)
(21,6048,72,2796416)
(21,1647864,188,2796416)
(21,541236,132,2796416)
(21,6392,68,2796416)
```

Tests compare this against the authenticator's complete preceding chain-call
trace, not merely an isolated list of new reads. The first discovery pass
read the descriptor scalar before the other stage1 selections, then the
independently approved stage2 callback; final reproducible ordering above is
fixed and consumes no cell value as a read selector.

## Source behavior and machine-register returns

All object/descriptor field offsets in this section are hexadecimal. In the
appendix every immediate/displacement is explicitly printed in decimal.

### State3 handler and group unlink

`8007e678` is an eight-instruction stack/LR wrapper. Its sole call at `7e684`
is `80088e50` with unchanged incoming child r3; epilogue and return `7e694`
preserve the callee's r3. It does not set state18, recurse to another state,
call `8aff0`, or return a fabricated boolean.

`88e50` saves child in r31, reads child1, sign-extends it, and compares to−1.
When group is−1, branch `88e78 ->88f74` skips group unlink, draw unlink and
all descriptor teardown, proceeding to object-pool return.

Otherwise it reads child4 as previous and child8 as next, then selects four
ordered cases. C names group heads at `803c706c` and tails at `803c6f6c`;
the instruction stream explicitly constructs those absolute bases.

1. Both null: write group head0, **reload signed child1**, then write group tail0.
2. Previous null, next nonnull: write group head=next, then next4=0.
3. Previous nonnull, next null: write group tail=previous, then previous8=0.
4. Both nonnull: previous8=next, then next4=previous.

No group-range clamp, membership validation, own-child8 clear or group1 reset
occurs. The final pool-return step later overwrites child4. This evidence does
not authenticate initial group-list data or prove a child belongs to a list.

After group unlink, load unsigned child2 and compare exactly4. Type4 skips
draw unlink and all descriptors. Other values call `89444(child)`, then loop
starting at i=0 over descriptors child[e0+4*i]. Each iteration loads its
pointer, calls `6d80` only if nonnull, advances the slot pointer by4 and i by1,
then **reloads signed child99** for the signed `i < count` branch at `88f70`.
There is no fixed-count cache, implicit clamp, descriptor-slot clear or count
reset. Zero/negative signed counts execute no descriptor iteration. On every
normally returning path, `88f74` restores child to r3 and `88f78` calls `89814`.
The epilogue preserves that helper's return.

### Draw unlink `89444`

Read child85 as signed8. If−1, conditional return `89450` exits immediately,
without loading104/108 or clearing100/85. Otherwise load previous104 and
next108. Classification tests occur in priority order bit0x40, bit0x20,
bit0x10, then unflagged. Selected head/tail locations are:

- 0x40: r13−21280 /r13−21288, indexed by low nibble times4.
- 0x20: r13−21296 /r13−21304, indexed by low nibble times4.
- 0x10: absolute `803c6f54` /`803c6f3c`, indexed by low nibble times4.
- Unflagged: r13−21264 /r13−21272, indexed by signed85 times4.

The r13-relative displacements are the directly proved operands; their C
symbol names do not independently establish a live r13 value. If flags
combine, the first matching test wins. There is no range sanitization.

The four link cases parallel group unlink: both null writes head0 then tail0;
head removal writes head=next then next104=0; tail removal writes tail=previous
then previous108=0; interior removal writes previous108=next then
next104=previous. Only after the selected case, store child100=0 then
child85=0xff, in that order. Own104/108 remain untouched. No call occurs in
this helper, and both early and final returns preserve incoming child r3.

### Descriptor wrapper, real callback and descriptor release

`6d80` saves descriptor in r31 and loads descriptor0c into r3. If zero, it
skips Unref. Otherwise call `8024fd74` at `6da0`, and **only after that call
returns** write descriptor0c=0. It then restores descriptor to r3 and calls
`197ad8` at `6db0`. It does not treat a null descriptor as valid: it loads0c
before reaching the null guard inside `197ad8`.

`197ad8` saves descriptor in r29 with record-setting `or.`. Null input skips
to the epilogue and preserves r3=0. For nonnull input, load signed descriptor8,
capture that type in r30, load the descriptor-table base at r13−21024, and
form row = base + type*28 in r31. Load row18 into r12, compare0, and when
nonnull execute `mtctr r12` at `197b1c`, `bctrl` at `197b20`. **Incoming r3
still equals the descriptor at this indirect call.** No descriptor-list or
free-count write has yet occurred. The row and signed type are captured
before the callback; the descriptor's list links are loaded after it returns.

For the independently selected battle descriptor0 row, row18 is genuinely
`80006ed8`. That callback saves the descriptor, **rereads descriptor0c**, and
conditionally calls `8024fd74` at `6ef8`; only after a successful return does
it clear0c. Both branches meet at `6f04`, set **r3=0** at `6f08`, and return
at `6f18`. The actual callback is not absent and cannot be silently replaced
with null.

In the normal sequential `6d80 ->197ad8 ->6ed8` path, a nonzero0c first causes
Unref in `6d80`, then the explicit0c clear. The callback rereads that zero
and returns0 without a second Unref. An initially zero0c also reaches and
executes the callback. Direct callback invocation with nonzero0c still has
the unresolved Unref boundary. These are conditional instruction-order facts,
not proof that Unref's body succeeds or cannot fault.

After callback return (or null callback), `197ad8` loads descriptor0 as
previous and descriptor4 as next. If previous is nonnull, previous4=next;
otherwise row8=next. If next is nonnull, next0=previous. Then load old row0c
free-list head, store descriptor0=old head, store row0c=descriptor, and clear
active descriptor9. Descriptor4 is not cleared. Call reused `197bec(type)`
to load signed16 free count, move the result to r4, restore captured signed
type to r3, add1 to r4 and call reused `197bd8(type,count+1)` to store low16.
No saturation or validation is present.

Reused allocator-helper evidence proves `197bd8` first multiplies r3 by28
and leaves that result in r3, so a normal nonnull `197ad8` return is
**low32(captured signed type*28)**, not the captured type, callback result
or descriptor pointer. Descriptor0 therefore returns0. `6d80` preserves
that r3 result. Its caller
`88e50` does not use it as an object identity; it eventually restores the
saved child before object-pool return.

If an Unref boundary cannot complete, retain only actual preceding effects.
For example, group/draw unlink may already have happened before descriptor
teardown; descriptor0c is not cleared before Unref; descriptor unlink/count
and object-pool return do not occur merely because they appear later in C.

### Object-pool return `89814`

Load and sign-extend child3, index the free-pool tail array at `803c718c`.
If old tail is null, store tail=child, reload signed child3, then store head
at `803c716c`=child. Otherwise write oldTail4=child, reload signed child3,
then write tail=child. Reload signed child3 again, index unsigned16 counts
at `803c71ac` with type*2, load with `lhzx`, add1, and store low16 with
`sthx`. Only after the count store, write child0=0 and then child4=0.

The helper does not overwrite r3. Thus successful state3 cleanup returns the
**original child pointer** via `89814 ->88e50 ->7e678`. The instruction stream
clears active0 but **does not reset state18**, descriptor slots, child99,
child8 or the object's payload. A repeated call has no built-in duplicate-free
guard. Pool initialization, allocation provenance, valid bounds, actual
scheduler behavior and future reuse are not established by this static read.

## Independent fixtures, refusals and verification

The test module's semantic operands are manually authored, not populated by
loading the archive, a decoder or reader output. Its independent PPC inverse
reproduces all seven body hashes and both scalar hashes. All **8736 one-bit
instruction controls** reject or decode distinctly and inverse-encode to
the exact changed word. All **8800 selected-payload bit changes** fail their
hashes before interpretation. Exact control-flow verification covers all
**56 branches/calls/returns**, including `89450` conditional return and
`197b20` indirect call, with every BO/BI/BH/AA/LK field.

**19 tests pass**, including both snapshots, every operand, source ordering,
independent extents/identity joins, reused-helper identities, exact full read
traces/physical spans, split-buffer handling, full-file/schema/mapping refusal,
width/type/address/duplicate controls, every control-flow metadata mutation,
selected-payload tampering and arbitrary-CLI refusal. Initial discovery
identified two forms outside the reused decoder's admitted set: signed-loop
conditional branch BO12/BI0 and equality conditional return BO12/BI2. They
were represented locally with all operand/reserved bits controlled; the shared
decoder was not changed. No snapshot or selected-data authentication failed.

Completed locally, without installation, external fetch, original execution,
estimator/runtime import or raw payload output:

```
python -m unittest discover -s research/tools/matching-decomp -p test_archived_projectile_cleanup_evidence.py -v
python research/tools/matching-decomp/read_archived_projectile_cleanup_evidence.py research/decomp/GotchaForce.rep.before_force_create/idata/00/~00000000.db/db.3.gbf
python research/tools/matching-decomp/read_archived_projectile_cleanup_evidence.py research/decomp/GotchaForce.rep.before_force_create/idata/00/~00000000.db/db.4.gbf
```

Derived reports remain ignored:

| Report | SHA-256 |
| --- | --- |
| `.tmp/projectile-cleanup-evidence-20261114/db3.json` | `e7d2ac38e2e6ca3a930f431fbe809663ea42fc6e6f1508cec813544872e7198a` |
| `.tmp/projectile-cleanup-evidence-20261114/db4.json` | `118f6d7a254e4b21a47062394eb05291e47967777312d98995500b03df4f4d31` |

Additional regression checks pass: **111 projectile evidence tests**
(`test_archived_projectile*_evidence.py`, including these19) and **12 existing
object-allocator evidence tests**. Shared authenticator/reader files have no
diff from the investigation base. All document source/report hashes were
recomputed and checked against their files.

These focused evidence tests do not replace contributor/docs verification or
runtime/playability acceptance. Runtime integration is separate work.

## Complete instruction operands

Each section gives every instruction in source order, with no gaps. Addresses
are hexadecimal. Operand numbers are decimal, including displacements and
immediates; branch targets are hexadecimal. `mflr/mtlr` fix SPR8/Rc0;
`mtctr` fixes SPR9/Rc0; indexed loads/stores fix reserved Rc0; compare forms
fix their unrepresented reserved bits; branch-register XO is16 for LR and528
for CTR. All other variable instruction bits appear as named operands.

### `8007e678`: 8 instructions /32 bytes

| PC | Complete operands |
| --- | --- |
| `8007e678` | `stwu rS=1, rA=1, displacement=-16` |
| `8007e67c` | `mflr rD=0` |
| `8007e680` | `stw rS=0, rA=1, displacement=20` |
| `8007e684` | `bl target=80088e50, AA=0, LK=1` |
| `8007e688` | `lwz rD=0, rA=1, displacement=20` |
| `8007e68c` | `mtlr rS=0` |
| `8007e690` | `addi rD=1, rA=1, immediate=16` |
| `8007e694` | `blr BO=20, BI=0, BH=0, LK=0` |

### `80088e50`: 82 instructions /328 bytes

| PC | Complete operands |
| --- | --- |
| `80088e50` | `stwu rS=1, rA=1, displacement=-32` |
| `80088e54` | `mflr rD=0` |
| `80088e58` | `stw rS=0, rA=1, displacement=36` |
| `80088e5c` | `stw rS=31, rA=1, displacement=28` |
| `80088e60` | `or rS=3, rA=31, rB=3, Rc=0` |
| `80088e64` | `stw rS=30, rA=1, displacement=24` |
| `80088e68` | `stw rS=29, rA=1, displacement=20` |
| `80088e6c` | `lbz rD=3, rA=3, displacement=1` |
| `80088e70` | `extsb rS=3, rA=0, Rc=0` |
| `80088e74` | `cmpi BF=0, L=0, rA=0, immediate=-1` |
| `80088e78` | `bc BO=12, BI=2, target=80088f74, AA=0, LK=0` |
| `80088e7c` | `lwz rD=5, rA=31, displacement=4` |
| `80088e80` | `lwz rD=6, rA=31, displacement=8` |
| `80088e84` | `cmpli BF=0, L=0, rA=5, immediate=0` |
| `80088e88` | `bc BO=4, BI=2, target=80088ec4, AA=0, LK=0` |
| `80088e8c` | `cmpli BF=0, L=0, rA=6, immediate=0` |
| `80088e90` | `bc BO=4, BI=2, target=80088ec4, AA=0, LK=0` |
| `80088e94` | `addis rD=4, rA=0, immediate=-32708` |
| `80088e98` | `addis rD=3, rA=0, immediate=-32708` |
| `80088e9c` | `rlwinm rS=0, rA=0, SH=2, MB=0, ME=29, Rc=0` |
| `80088ea0` | `addi rD=5, rA=0, immediate=0` |
| `80088ea4` | `addi rD=4, rA=4, immediate=28780` |
| `80088ea8` | `addi rD=3, rA=3, immediate=28524` |
| `80088eac` | `stwx rS=5, rA=4, rB=0` |
| `80088eb0` | `lbz rD=0, rA=31, displacement=1` |
| `80088eb4` | `extsb rS=0, rA=0, Rc=0` |
| `80088eb8` | `rlwinm rS=0, rA=0, SH=2, MB=0, ME=29, Rc=0` |
| `80088ebc` | `stwx rS=5, rA=3, rB=0` |
| `80088ec0` | `b target=80088f2c, AA=0, LK=0` |
| `80088ec4` | `cmpli BF=0, L=0, rA=5, immediate=0` |
| `80088ec8` | `bc BO=4, BI=2, target=80088ef4, AA=0, LK=0` |
| `80088ecc` | `cmpli BF=0, L=0, rA=6, immediate=0` |
| `80088ed0` | `bc BO=12, BI=2, target=80088ef4, AA=0, LK=0` |
| `80088ed4` | `extsb rS=3, rA=0, Rc=0` |
| `80088ed8` | `addis rD=3, rA=0, immediate=-32708` |
| `80088edc` | `rlwinm rS=0, rA=4, SH=2, MB=0, ME=29, Rc=0` |
| `80088ee0` | `addi rD=0, rA=0, immediate=0` |
| `80088ee4` | `addi rD=3, rA=3, immediate=28780` |
| `80088ee8` | `stwx rS=6, rA=3, rB=4` |
| `80088eec` | `stw rS=0, rA=6, displacement=4` |
| `80088ef0` | `b target=80088f2c, AA=0, LK=0` |
| `80088ef4` | `cmpli BF=0, L=0, rA=5, immediate=0` |
| `80088ef8` | `bc BO=12, BI=2, target=80088f24, AA=0, LK=0` |
| `80088efc` | `cmpli BF=0, L=0, rA=6, immediate=0` |
| `80088f00` | `bc BO=4, BI=2, target=80088f24, AA=0, LK=0` |
| `80088f04` | `extsb rS=3, rA=0, Rc=0` |
| `80088f08` | `addis rD=3, rA=0, immediate=-32708` |
| `80088f0c` | `rlwinm rS=0, rA=4, SH=2, MB=0, ME=29, Rc=0` |
| `80088f10` | `addi rD=0, rA=0, immediate=0` |
| `80088f14` | `addi rD=3, rA=3, immediate=28524` |
| `80088f18` | `stwx rS=5, rA=3, rB=4` |
| `80088f1c` | `stw rS=0, rA=5, displacement=8` |
| `80088f20` | `b target=80088f2c, AA=0, LK=0` |
| `80088f24` | `stw rS=6, rA=5, displacement=8` |
| `80088f28` | `stw rS=5, rA=6, displacement=4` |
| `80088f2c` | `lbz rD=0, rA=31, displacement=2` |
| `80088f30` | `cmpi BF=0, L=0, rA=0, immediate=4` |
| `80088f34` | `bc BO=12, BI=2, target=80088f74, AA=0, LK=0` |
| `80088f38` | `or rS=31, rA=3, rB=31, Rc=0` |
| `80088f3c` | `bl target=80089444, AA=0, LK=1` |
| `80088f40` | `or rS=31, rA=30, rB=31, Rc=0` |
| `80088f44` | `addi rD=29, rA=0, immediate=0` |
| `80088f48` | `b target=80088f64, AA=0, LK=0` |
| `80088f4c` | `lwz rD=3, rA=30, displacement=224` |
| `80088f50` | `cmpli BF=0, L=0, rA=3, immediate=0` |
| `80088f54` | `bc BO=12, BI=2, target=80088f5c, AA=0, LK=0` |
| `80088f58` | `bl target=80006d80, AA=0, LK=1` |
| `80088f5c` | `addi rD=30, rA=30, immediate=4` |
| `80088f60` | `addi rD=29, rA=29, immediate=1` |
| `80088f64` | `lbz rD=0, rA=31, displacement=153` |
| `80088f68` | `extsb rS=0, rA=0, Rc=0` |
| `80088f6c` | `cmp BF=0, L=0, rA=29, rB=0` |
| `80088f70` | `bc BO=12, BI=0, target=80088f4c, AA=0, LK=0` |
| `80088f74` | `or rS=31, rA=3, rB=31, Rc=0` |
| `80088f78` | `bl target=80089814, AA=0, LK=1` |
| `80088f7c` | `lwz rD=0, rA=1, displacement=36` |
| `80088f80` | `lwz rD=31, rA=1, displacement=28` |
| `80088f84` | `lwz rD=30, rA=1, displacement=24` |
| `80088f88` | `lwz rD=29, rA=1, displacement=20` |
| `80088f8c` | `mtlr rS=0` |
| `80088f90` | `addi rD=1, rA=1, immediate=32` |
| `80088f94` | `blr BO=20, BI=0, BH=0, LK=0` |

### `80089444`: 68 instructions /272 bytes

| PC | Complete operands |
| --- | --- |
| `80089444` | `lbz rD=0, rA=3, displacement=133` |
| `80089448` | `extsb rS=0, rA=6, Rc=0` |
| `8008944c` | `cmpi BF=0, L=0, rA=6, immediate=-1` |
| `80089450` | `bclr BO=12, BI=2, BH=0, LK=0` |
| `80089454` | `rlwinm rS=6, rA=0, SH=0, MB=25, ME=25, Rc=1` |
| `80089458` | `lwz rD=7, rA=3, displacement=260` |
| `8008945c` | `lwz rD=8, rA=3, displacement=264` |
| `80089460` | `bc BO=12, BI=2, target=8008947c, AA=0, LK=0` |
| `80089464` | `rlwinm rS=6, rA=0, SH=2, MB=26, ME=29, Rc=0` |
| `80089468` | `addi rD=4, rA=13, immediate=-21280` |
| `8008946c` | `addi rD=5, rA=13, immediate=-21288` |
| `80089470` | `add rD=4, rA=4, rB=0, Rc=0` |
| `80089474` | `add rD=5, rA=5, rB=0, Rc=0` |
| `80089478` | `b target=800894d8, AA=0, LK=0` |
| `8008947c` | `rlwinm rS=6, rA=0, SH=0, MB=26, ME=26, Rc=1` |
| `80089480` | `bc BO=12, BI=2, target=8008949c, AA=0, LK=0` |
| `80089484` | `rlwinm rS=6, rA=0, SH=2, MB=26, ME=29, Rc=0` |
| `80089488` | `addi rD=4, rA=13, immediate=-21296` |
| `8008948c` | `addi rD=5, rA=13, immediate=-21304` |
| `80089490` | `add rD=4, rA=4, rB=0, Rc=0` |
| `80089494` | `add rD=5, rA=5, rB=0, Rc=0` |
| `80089498` | `b target=800894d8, AA=0, LK=0` |
| `8008949c` | `rlwinm rS=6, rA=0, SH=0, MB=27, ME=27, Rc=1` |
| `800894a0` | `bc BO=12, BI=2, target=800894c4, AA=0, LK=0` |
| `800894a4` | `addis rD=5, rA=0, immediate=-32708` |
| `800894a8` | `addis rD=4, rA=0, immediate=-32708` |
| `800894ac` | `rlwinm rS=6, rA=6, SH=2, MB=26, ME=29, Rc=0` |
| `800894b0` | `addi rD=5, rA=5, immediate=28500` |
| `800894b4` | `addi rD=0, rA=4, immediate=28476` |
| `800894b8` | `add rD=4, rA=5, rB=6, Rc=0` |
| `800894bc` | `add rD=5, rA=0, rB=6, Rc=0` |
| `800894c0` | `b target=800894d8, AA=0, LK=0` |
| `800894c4` | `rlwinm rS=6, rA=0, SH=2, MB=0, ME=29, Rc=0` |
| `800894c8` | `addi rD=4, rA=13, immediate=-21264` |
| `800894cc` | `addi rD=5, rA=13, immediate=-21272` |
| `800894d0` | `add rD=4, rA=4, rB=0, Rc=0` |
| `800894d4` | `add rD=5, rA=5, rB=0, Rc=0` |
| `800894d8` | `cmpli BF=0, L=0, rA=7, immediate=0` |
| `800894dc` | `bc BO=4, BI=2, target=800894f8, AA=0, LK=0` |
| `800894e0` | `cmpli BF=0, L=0, rA=8, immediate=0` |
| `800894e4` | `bc BO=4, BI=2, target=800894f8, AA=0, LK=0` |
| `800894e8` | `addi rD=0, rA=0, immediate=0` |
| `800894ec` | `stw rS=0, rA=4, displacement=0` |
| `800894f0` | `stw rS=0, rA=5, displacement=0` |
| `800894f4` | `b target=80089540, AA=0, LK=0` |
| `800894f8` | `cmpli BF=0, L=0, rA=7, immediate=0` |
| `800894fc` | `bc BO=4, BI=2, target=80089518, AA=0, LK=0` |
| `80089500` | `cmpli BF=0, L=0, rA=8, immediate=0` |
| `80089504` | `bc BO=12, BI=2, target=80089518, AA=0, LK=0` |
| `80089508` | `stw rS=8, rA=4, displacement=0` |
| `8008950c` | `addi rD=0, rA=0, immediate=0` |
| `80089510` | `stw rS=0, rA=8, displacement=260` |
| `80089514` | `b target=80089540, AA=0, LK=0` |
| `80089518` | `cmpli BF=0, L=0, rA=7, immediate=0` |
| `8008951c` | `bc BO=12, BI=2, target=80089538, AA=0, LK=0` |
| `80089520` | `cmpli BF=0, L=0, rA=8, immediate=0` |
| `80089524` | `bc BO=4, BI=2, target=80089538, AA=0, LK=0` |
| `80089528` | `stw rS=7, rA=5, displacement=0` |
| `8008952c` | `addi rD=0, rA=0, immediate=0` |
| `80089530` | `stw rS=0, rA=7, displacement=264` |
| `80089534` | `b target=80089540, AA=0, LK=0` |
| `80089538` | `stw rS=8, rA=7, displacement=264` |
| `8008953c` | `stw rS=7, rA=8, displacement=260` |
| `80089540` | `addi rD=4, rA=0, immediate=0` |
| `80089544` | `addi rD=0, rA=0, immediate=-1` |
| `80089548` | `stw rS=4, rA=3, displacement=256` |
| `8008954c` | `stb rS=0, rA=3, displacement=133` |
| `80089550` | `blr BO=20, BI=0, BH=0, LK=0` |

### `80006d80`: 18 instructions /72 bytes

| PC | Complete operands |
| --- | --- |
| `80006d80` | `stwu rS=1, rA=1, displacement=-16` |
| `80006d84` | `mflr rD=0` |
| `80006d88` | `stw rS=0, rA=1, displacement=20` |
| `80006d8c` | `stw rS=31, rA=1, displacement=12` |
| `80006d90` | `or rS=3, rA=31, rB=3, Rc=0` |
| `80006d94` | `lwz rD=3, rA=3, displacement=12` |
| `80006d98` | `cmpli BF=0, L=0, rA=3, immediate=0` |
| `80006d9c` | `bc BO=12, BI=2, target=80006dac, AA=0, LK=0` |
| `80006da0` | `bl target=8024fd74, AA=0, LK=1` |
| `80006da4` | `addi rD=0, rA=0, immediate=0` |
| `80006da8` | `stw rS=0, rA=31, displacement=12` |
| `80006dac` | `or rS=31, rA=3, rB=31, Rc=0` |
| `80006db0` | `bl target=80197ad8, AA=0, LK=1` |
| `80006db4` | `lwz rD=0, rA=1, displacement=20` |
| `80006db8` | `lwz rD=31, rA=1, displacement=12` |
| `80006dbc` | `mtlr rS=0` |
| `80006dc0` | `addi rD=1, rA=1, immediate=16` |
| `80006dc4` | `blr BO=20, BI=0, BH=0, LK=0` |

### `80197ad8`: 47 instructions /188 bytes

| PC | Complete operands |
| --- | --- |
| `80197ad8` | `stwu rS=1, rA=1, displacement=-32` |
| `80197adc` | `mflr rD=0` |
| `80197ae0` | `stw rS=0, rA=1, displacement=36` |
| `80197ae4` | `stw rS=31, rA=1, displacement=28` |
| `80197ae8` | `stw rS=30, rA=1, displacement=24` |
| `80197aec` | `stw rS=29, rA=1, displacement=20` |
| `80197af0` | `or rS=3, rA=29, rB=3, Rc=1` |
| `80197af4` | `bc BO=12, BI=2, target=80197b78, AA=0, LK=0` |
| `80197af8` | `lbz rD=5, rA=29, displacement=8` |
| `80197afc` | `lwz rD=4, rA=13, displacement=-21024` |
| `80197b00` | `extsb rS=5, rA=5, Rc=0` |
| `80197b04` | `mulli rD=0, rA=5, immediate=28` |
| `80197b08` | `or rS=5, rA=30, rB=5, Rc=0` |
| `80197b0c` | `add rD=31, rA=4, rB=0, Rc=0` |
| `80197b10` | `lwz rD=12, rA=31, displacement=24` |
| `80197b14` | `cmpli BF=0, L=0, rA=12, immediate=0` |
| `80197b18` | `bc BO=12, BI=2, target=80197b24, AA=0, LK=0` |
| `80197b1c` | `mtctr rS=12` |
| `80197b20` | `bctrl BO=20, BI=0, BH=0, LK=1` |
| `80197b24` | `lwz rD=4, rA=29, displacement=0` |
| `80197b28` | `lwz rD=3, rA=29, displacement=4` |
| `80197b2c` | `cmpli BF=0, L=0, rA=4, immediate=0` |
| `80197b30` | `bc BO=12, BI=2, target=80197b3c, AA=0, LK=0` |
| `80197b34` | `stw rS=3, rA=4, displacement=4` |
| `80197b38` | `b target=80197b40, AA=0, LK=0` |
| `80197b3c` | `stw rS=3, rA=31, displacement=8` |
| `80197b40` | `cmpli BF=0, L=0, rA=3, immediate=0` |
| `80197b44` | `bc BO=12, BI=2, target=80197b4c, AA=0, LK=0` |
| `80197b48` | `stw rS=4, rA=3, displacement=0` |
| `80197b4c` | `lwz rD=4, rA=31, displacement=12` |
| `80197b50` | `addi rD=0, rA=0, immediate=0` |
| `80197b54` | `or rS=30, rA=3, rB=30, Rc=0` |
| `80197b58` | `stw rS=4, rA=29, displacement=0` |
| `80197b5c` | `stw rS=29, rA=31, displacement=12` |
| `80197b60` | `stb rS=0, rA=29, displacement=9` |
| `80197b64` | `bl target=80197bec, AA=0, LK=1` |
| `80197b68` | `or rS=3, rA=4, rB=3, Rc=0` |
| `80197b6c` | `or rS=30, rA=3, rB=30, Rc=0` |
| `80197b70` | `addi rD=4, rA=4, immediate=1` |
| `80197b74` | `bl target=80197bd8, AA=0, LK=1` |
| `80197b78` | `lwz rD=0, rA=1, displacement=36` |
| `80197b7c` | `lwz rD=31, rA=1, displacement=28` |
| `80197b80` | `lwz rD=30, rA=1, displacement=24` |
| `80197b84` | `lwz rD=29, rA=1, displacement=20` |
| `80197b88` | `mtlr rS=0` |
| `80197b8c` | `addi rD=1, rA=1, immediate=32` |
| `80197b90` | `blr BO=20, BI=0, BH=0, LK=0` |

### `80089814`: 33 instructions /132 bytes

| PC | Complete operands |
| --- | --- |
| `80089814` | `lbz rD=0, rA=3, displacement=3` |
| `80089818` | `addis rD=4, rA=0, immediate=-32708` |
| `8008981c` | `addi rD=4, rA=4, immediate=29068` |
| `80089820` | `extsb rS=0, rA=0, Rc=0` |
| `80089824` | `rlwinm rS=0, rA=0, SH=2, MB=0, ME=29, Rc=0` |
| `80089828` | `lwzx rD=5, rA=4, rB=0` |
| `8008982c` | `cmpli BF=0, L=0, rA=5, immediate=0` |
| `80089830` | `bc BO=4, BI=2, target=80089854, AA=0, LK=0` |
| `80089834` | `stwx rS=3, rA=4, rB=0` |
| `80089838` | `addis rD=4, rA=0, immediate=-32708` |
| `8008983c` | `addi rD=4, rA=4, immediate=29036` |
| `80089840` | `lbz rD=0, rA=3, displacement=3` |
| `80089844` | `extsb rS=0, rA=0, Rc=0` |
| `80089848` | `rlwinm rS=0, rA=0, SH=2, MB=0, ME=29, Rc=0` |
| `8008984c` | `stwx rS=3, rA=4, rB=0` |
| `80089850` | `b target=80089868, AA=0, LK=0` |
| `80089854` | `stw rS=3, rA=5, displacement=4` |
| `80089858` | `lbz rD=0, rA=3, displacement=3` |
| `8008985c` | `extsb rS=0, rA=0, Rc=0` |
| `80089860` | `rlwinm rS=0, rA=0, SH=2, MB=0, ME=29, Rc=0` |
| `80089864` | `stwx rS=3, rA=4, rB=0` |
| `80089868` | `lbz rD=6, rA=3, displacement=3` |
| `8008986c` | `addis rD=4, rA=0, immediate=-32708` |
| `80089870` | `addi rD=5, rA=4, immediate=29100` |
| `80089874` | `addi rD=0, rA=0, immediate=0` |
| `80089878` | `extsb rS=6, rA=4, Rc=0` |
| `8008987c` | `rlwinm rS=4, rA=6, SH=1, MB=0, ME=30, Rc=0` |
| `80089880` | `lhzx rD=4, rA=5, rB=6` |
| `80089884` | `addi rD=4, rA=4, immediate=1` |
| `80089888` | `sthx rS=4, rA=5, rB=6` |
| `8008988c` | `stb rS=0, rA=3, displacement=0` |
| `80089890` | `stw rS=0, rA=3, displacement=4` |
| `80089894` | `blr BO=20, BI=0, BH=0, LK=0` |

### `80006ed8`: 17 instructions /68 bytes

| PC | Complete operands |
| --- | --- |
| `80006ed8` | `stwu rS=1, rA=1, displacement=-16` |
| `80006edc` | `mflr rD=0` |
| `80006ee0` | `stw rS=0, rA=1, displacement=20` |
| `80006ee4` | `stw rS=31, rA=1, displacement=12` |
| `80006ee8` | `or rS=3, rA=31, rB=3, Rc=0` |
| `80006eec` | `lwz rD=3, rA=3, displacement=12` |
| `80006ef0` | `cmpli BF=0, L=0, rA=3, immediate=0` |
| `80006ef4` | `bc BO=12, BI=2, target=80006f04, AA=0, LK=0` |
| `80006ef8` | `bl target=8024fd74, AA=0, LK=1` |
| `80006efc` | `addi rD=0, rA=0, immediate=0` |
| `80006f00` | `stw rS=0, rA=31, displacement=12` |
| `80006f04` | `lwz rD=0, rA=1, displacement=20` |
| `80006f08` | `addi rD=3, rA=0, immediate=0` |
| `80006f0c` | `lwz rD=31, rA=1, displacement=12` |
| `80006f10` | `mtlr rS=0` |
| `80006f14` | `addi rD=1, rA=1, immediate=16` |
| `80006f18` | `blr BO=20, BI=0, BH=0, LK=0` |

## Complete source-file hashes

All paths are repository-relative. These distinguish source revision identities
from selected payload hashes; source files remain separate from archive bytes.

| Source | SHA-256 |
| --- | --- |
| `research/decomp/ghidra-export/chunk_0000.c` | `3703c76669a1cfcef1bb7eba56ca9a1c182d90c4b62343d9b8593fc8e11453fb` |
| `research/decomp/ghidra-export/chunk_0011.c` | `07ece988a66b1f5cf6f99bd92fce27d5cce80af3ff4d1fe91269bd70f66e11a6` |
| `research/decomp/ghidra-export/chunk_0012.c` | `da56862a07c8bf22619353d3b671707cf1d702c501051a3e08812f594bb6c7f6` |
| `research/decomp/ghidra-export/chunk_0013.c` | `93e3ffb2e9bee78cbee942dc35e3fa58266b1dafb749d3be92fa28f1b61fd4bc` |
| `research/decomp/ghidra-export/chunk_0048.c` | `7c1c1e9d3808796d1b9fe360bf62e7d558e131797463d2aa3c416592f67f255b` |
| `research/decomp/ghidra-export/_index.tsv` | `da07bdec2e01aa836786e81f909268120e1a99a3f42f9f724d2472ef40738c98` |
| `research/symbols/GG4E-CSM-20220412.map` | `7dadd7e766ca73bc0db66a9920f22e349d1c91a3d6525de3f791404f275f237d` |
| `research/tools/matching-decomp/read_archived_constants.py` | `24330635afc70c5364bc07b02c303206c7cf07b12f955b6c9dc7765be2276e25` |
| `research/tools/matching-decomp/read_archived_command_evidence.py` | `f5723928b61c0a8a70d01e182dd2b09020cfc28334bd45e8beb3623af81c9d9b` |
| `research/tools/matching-decomp/read_archived_actor_normal_evidence.py` | `acbce56a139df957a7bfd3a2033b065131dc09c2ac4baed05f3d454f56048f29` |
| `research/tools/matching-decomp/read_archived_projectile_callback_evidence.py` | `a300c8231f57f4ee36baafc98aa24e384e8297e55bbcb10bd84f0a5d76c350cd` |
| `research/tools/matching-decomp/read_archived_object_allocator_evidence.py` | `1f72ddcd854a1534edfe8a83795b1ca189a0c183e5e9ed831d5630bf168bce17` |
| `research/tools/matching-decomp/read_archived_projectile_cleanup_evidence.py` | `85db21a1fe5bb0629ffd2379e92ff5d5ba4e02a7214d48392a67cc3fef4ef7e6` |
| `research/tools/matching-decomp/test_archived_projectile_cleanup_evidence.py` | `c1b21e874f485e35782a30f449187364191a0ab37c6b016b8ebe210f793fe82b` |
