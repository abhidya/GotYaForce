# Actor attribute-refresh evidence: 80055dcc

## Result and source boundary

Both existing local ProgramDB snapshots authenticate the same complete
280-byte (`0x118`) function at `[80055dcc, 80055ee4)`. All 70 instructions,
including the link-register save/restore and final return, are represented by
the fixed reader. This is archived code evidence, not proof of unchanged
original-DOL bytes, live floating-point state, retail actor data or gameplay
parity.

The helper performs these actor-facing effects in order:

1. Copy control-word bit 6 to actor byte `+87`.
2. Retain the `+4b0` descriptor and actor `+b4` scale, then compute and store
   five separate single-precision products.
3. Reload the `+4ac` pointer before each of three scalar limit copies.
4. Perform fifteen sequential scalar load/store pairs from `+850..+888`
   to `+814..+84c`.
5. Call actual `8004d08c` once, after all 24 actor-facing stores above.

The C export places this helper in both spawn hydration and ordinary lifecycle
execution. These callsites are source references, not additional instruction
spans authenticated by this reader:

- `ghidra-export/chunk_0006.c:7113-7116`: spawn `800541ac` calls `80055f90`,
  `8005614c`, **`80055dcc` at line 7115**, then `80068004`.
- `ghidra-export/chunk_0006.c:7786-7789`: ordinary `80055568` stores `+578=2`,
  then calls `80055dcc`, `8005568c` and `80059068`, before prehook and state
  dispatch. This helper is an unconditional prefix, not the entire tick.
- `ghidra-export/chunk_0006.c:7438-7444`: ordinary `80054cbc` calls `80056900`
  and then `80055568`.
- Function body: `ghidra-export/chunk_0006.c:8091-8125`.
- Symbol extent: `research/symbols/GG4E-CSM-20220412.map:689` records
  `80055dcc`, size `00000118`; the next function starts at `80055ee4`.

## Authenticated archive identity

Inputs are under
`research/decomp/GotchaForce.rep.before_force_create/idata/00/~00000000.db/`:

| Snapshot | Whole-file SHA-256 |
| --- | --- |
| `db.3.gbf` | `7b50dd2d2e17b4bfcc89a64cde27010247d0cbf0f48bd5c059f50275f40458d0` |
| `db.4.gbf` | `1f86813d91ea8e2c4564f96622ec42555e1dba2c78aa81ad654e892140d019f8` |

The fixed reader
`research/tools/matching-decomp/read_archived_actor_attribute_evidence.py`
first calls unchanged `read_archived_constants.inspect`. That authenticates
the supplied bytes against the whole-file allowlist, validates GBF structure
and exact schemas, program name `boot.dol`, big-endian Gekko/Broadway language,
Ghidra `12.1.2` metadata, address map, empty File Bytes table, full data5 digest
and existing constant controls. It then reuses
`read_archived_command_evidence.mappings` to require exact text1/data3/data5
block and subblock identities, including rejection of all-block overlaps.
Only after those guards does it read and hash this function.

- Executable SHA-256 in import metadata:
  `21454a8880c6254616662710d6ec626e43d853999da2cdfad700030960a94836`.
  Metadata is not independent authentication of unchanged original bytes.
- File Bytes table: version `0`, root `-1`, count `0`.
- GBF block size `16384`, master root `1`, image offset `80000000`.
- Memory block: `MAIN_.text1`, key `1`, encoded start
  `20000000000055e0`, resolved start `800055e0`, length `2796416`.
- Subblock: key `1`, parent `1`, type `2`, length `2796416`, starting offset
  `0`, chain root `21`, source offset `0`.
- Full data5 authentication SHA-256:
  `989c794b17fc95de6e57810f5c89db23d585c85a15faafc994d9a5bd9a0e61b4`.

The function SHA-256 is
`7f60ab140ba8c7261c2ad34d87e1f41962e0c870e435a5c0efc12f216e6fb4a2`.
Both snapshots have this identical physical trace:

| Field | Value |
| --- | --- |
| Start / exclusive end | `80055dcc` / `80055ee4` |
| Byte width / instruction count | `280` / `70` |
| Root buffer / data buffer | `21` / `42` |
| Logical chain offset | `329708` |
| Data-buffer-relative offset | `2148` |
| Physical file offset | `706666` |
| Span length | `280` |
| Obfuscated | `true` |

Offsets in that physical-trace table are decimal. PCs and actor/descriptor
field offsets below are hexadecimal. The reader emits hashes, trace metadata
and derived instruction fields, never raw executable ranges. Its `constants`
list is empty. Inherited data5 authentication controls are not new constant
dependencies of `80055dcc`.

## Exact actor memory order

`A` is actor base `r3`. `D` is the descriptor loaded from `A+4b0` into `r4`.
`P` denotes the pointer separately reloaded from `A+4ac` for each limit.

### Control byte, retained descriptor and retained scale

| PC | Derived operation |
| --- | --- |
| `80055de0` | `lwz r0, A+5e0` |
| `80055de4` | `rlwinm r0,r0,26,31,31`, `Rc=0`: extract bit 6 into bit 0 |
| `80055de8` | `stb r0, A+87` |
| `80055dec` | `lwz r4, A+4b0`, retaining `D` for all five products |
| `80055df0` | `lfs f1, A+b4`, retaining scale for all five products |

Neither descriptor selection nor model scale is reloaded between products.
Each descriptor scalar is loaded only when reached, after the preceding
actor store. An eager five-field snapshot would not preserve that order.

| Descriptor source | Actor destination | `lfs f0,D+source` | `fmuls f0,f0,f1` | `stfs f0,A+destination` |
| --- | --- | --- | --- | --- |
| `+4c` | `+668` | `80055df4` | `80055df8` | `80055dfc` |
| `+44` | `+66c` | `80055e00` | `80055e04` | `80055e08` |
| `+48` | `+670` | `80055e0c` | `80055e10` | `80055e14` |
| `+54` | `+674` | `80055e18` | `80055e1c` | `80055e20` |
| `+50` | `+770` | `80055e24` | `80055e28` | `80055e2c` |

### Three limits, with three pointer reloads

| Parameter source | Actor destination | `lwz r4,A+4ac` | `lfs f0,P+source` | `stfs f0,A+destination` |
| --- | --- | --- | --- | --- |
| `+74` | `+678` | `80055e30` | `80055e34` | `80055e38` |
| `+78` | `+67c` | `80055e3c` | `80055e40` | `80055e44` |
| `+7c` | `+680` | `80055e48` | `80055e4c` | `80055e50` |

`A+4ac` is distinct from the retained `A+4b0` descriptor. The pointer is not
cached across the three copies, and no model-scale multiply applies to these
limits. The actual instructions are floating loads/stores, despite the C
export's `undefined4` assignments.

### Fifteen prepared row scalars

Every row below is one complete `lfs f0,A+source` followed by
`stfs f0,A+destination` before the next source is read. There is no aggregate
row snapshot or raw integer block copy.

| Source | Destination | Load PC | Store PC |
| --- | --- | --- | --- |
| `+850` | `+814` | `80055e54` | `80055e58` |
| `+854` | `+818` | `80055e5c` | `80055e60` |
| `+858` | `+81c` | `80055e64` | `80055e68` |
| `+85c` | `+820` | `80055e6c` | `80055e70` |
| `+860` | `+824` | `80055e74` | `80055e78` |
| `+864` | `+828` | `80055e7c` | `80055e80` |
| `+868` | `+82c` | `80055e88` | `80055e8c` |
| `+86c` | `+830` | `80055e90` | `80055e94` |
| `+870` | `+834` | `80055e98` | `80055e9c` |
| `+874` | `+838` | `80055ea0` | `80055ea4` |
| `+878` | `+83c` | `80055ea8` | `80055eac` |
| `+87c` | `+840` | `80055eb0` | `80055eb4` |
| `+880` | `+844` | `80055eb8` | `80055ebc` |
| `+884` | `+848` | `80055ec0` | `80055ec4` |
| `+888` | `+84c` | `80055ec8` | `80055ecc` |

The gap at `80055e84` is a conditional branch to `80055ed0`, with `BO=4`,
`BI=0`, `AA=0`, `LK=0`. It tests CR0.LT false (`bge`). The prologue has already
set `r4=0` at `80055dd4` and performed signed `cmpi` with immediate `9`,
`BF=0`, `L=0` at `80055ddc`. No instruction between that compare and this
branch updates CR0. The mask instruction has `Rc=0`, and the floating
multiplies are non-record forms. Consequently, on normal function entry
CR0.LT is true and the branch is not taken. There is no actor-controlled
short-copy path: all fifteen pairs execute before the callee.

### Final callee and return

At `80055ed0`, `bl 8004d08c` passes the same actor in `r3`. It is the sole
call in the function. Only after that callee returns does the epilogue load
saved LR from stack `+14`, restore it with `mtlr r0` at `80055ed8`, restore
the 16-byte stack frame and execute `blr` at `80055ee0`. The paired prologue
`mflr r0` is at `80055dd0`; both SPR forms name LR (`8`) and have `Rc=0`.

The separate [movement-followup evidence](archived-movement-followup-2026-11-13.md)
describes `8004d08c`'s gates, signed marker override and retained-world-matrix
path. This caller contains no matrix refresh, setup, animation, history or
clock call between its stores and `8004d08c`. A callee zero-height early
return does not skip or undo any of the preceding attribute stores. The
callee's own constants and arithmetic remain its separate source stage.

## Numeric and ownership implications

The five products use separate `fmuls` instructions, not fused operations or
binary64 multiplication instructions. With finite binary32 operands, the
exact product fits binary64 precision and exponent range: at most 48
significant bits and magnitudes between `2^-298` and less than `2^256` for
nonzero products. A host binary64 multiply followed by one nearest-even f32
round therefore implements this stage under the explicitly admitted
round-to-nearest, gradual-underflow domain. Rounded overflow must still be
refused if the host contract admits only finite f32 results. Signed zeros
and subnormals must not be discarded by truthiness or clamping.

The three limits and fifteen prepared scalars use `lfs/stfs`. Within a finite
f32 domain those copies preserve values and zero signs. They do not establish
arbitrary NaN payload preservation, signaling-NaN behavior, enabled-exception
behavior or live FPSCR rounding/non-IEEE state. None of those states is
captured by this archive. This function introduces no paired-single/GQR
dependency, divide, reciprocal estimate, trigonometry or quaternion stage.

A source-ordered host model should validate fields at their reached reads
and writes. Failure at a later descriptor scalar, limit, row source or row
destination retains earlier completed stores, and refusal inside actual
`8004d08c` retains this entire prefix plus the callee's completed effects.
That is a bounded host-contract consequence of the observed ordering, not
a claim to reproduce hardware exceptions, concurrent guest writes or fault
recovery. Owner identity checks and synchronous call discipline likewise
belong to the host admission contract, not to extra instructions in this
function.

The `+4b0` identity and its fields must be the actual descriptor already used
by joint mapping and movement. The actor owns the live `+b4` scale and output
fields. In particular, existing movement fields `+66c/+670` must receive the
products before the actual movement operation reads them, and existing
action-speed source fields `+868/+874/+880` cannot be replaced with stale
copies in a new row array. The `+4ac` parameter identity and its three limits
remain explicit inputs; neither legacy movement defaults nor `+4b0` can
stand in for them.

Synthetic construction of these owners tests the helper's admitted source
stage. It does not supply retail `4b0` scalar provenance, `4ac` parameter
selection, prepared `850..888` values or actual production actor creation.
It also does not complete spawn, ordinary `55568`/`54070` execution, source
ownership exclusion or original-input replay.

## Reproduction and evidence tests

From `research/tools/matching-decomp`:

```sh
PYTHONDONTWRITEBYTECODE=1 python3 -m unittest \
  test_archived_actor_attribute_evidence test_archived_actor_traversal_evidence \
  test_archived_command_evidence test_archived_wait_evidence \
  test_archived_constants test_archived_world_matrix_evidence -v
```

**103 tests passed**: 22 synthetic/adversarial reader tests, 9 local-archive
tests, and 72 tests of the reused parser, mapping and decoder modules. The
local-archive tests require both named snapshots; they skip when those
private inputs are absent. Synthetic fixtures do not contain copied archived
executable ranges.

The new tests cover strict integer bounds, the fixed allowlist and duplicate
entries, root/alignment/range refusal before reading, exact width/hash before
decoding, complete decoding or refusal, split SPR fields and unsupported LR
variants, single versus double/fused multiplication, operand identities,
signed offsets, branches, authentication failures before parsing, malformed
or aliased mappings before span reads, and absence of address/width/raw or
execution CLI options. The actual archive checks account for every one of
the 70 instruction positions, all pointer reloads and ordered field copies,
the unchanged entry compare, sole final callee and exact physical trace.

Both CLI invocations also passed, from the repository root:

```sh
python3 research/tools/matching-decomp/read_archived_actor_attribute_evidence.py 'research/decomp/GotchaForce.rep.before_force_create/idata/00/~00000000.db/db.3.gbf'
python3 research/tools/matching-decomp/read_archived_actor_attribute_evidence.py 'research/decomp/GotchaForce.rep.before_force_create/idata/00/~00000000.db/db.4.gbf'
```

These results verify the bounded reader and archived facts. Runtime numerical,
composition, mutation and repository acceptance results are separate from
this evidence claim.
