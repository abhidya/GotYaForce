# Actor transform-history evidence: 8005685c

## Result and scope

Both already-local `db.3.gbf` and `db.4.gbf` authenticate the same complete
164-byte (`0xa4`) function at `[8005685c, 80056900)`, including its final return.
All 41 instructions are decoded into derived fields. There are no omitted
instructions, calls, function-specific constant loads, or additional source
spans. This is archived ProgramDB evidence, not original-DOL, live-state,
exception-model, or gameplay-parity proof.

The key source conclusions are:

1. All unconditional position, rotation, pre-rotation and scalar history stores
   occur before loading the linked pointer at source `+cc`.
2. Each three-short rotation copy is a raw 32-bit word load/store followed by
   an unsigned 16-bit load/store. The word destinations `+76` and `+1d6a` are
   halfword-aligned, not word-aligned. These are not three independent signed
   short loads or rotation arithmetic.
3. Scalar `+6d0 -> +6d4` uses `lfs/stfs`, despite the C export's `undefined4`
   assignments. Do not describe it as a raw integer copy or infer arbitrary
   NaN-payload preservation from the decompilation.
4. Nonzero target `+83` skips both mask reads. Otherwise target `+5e6` is read
   before source `+3e5`, both bytes are sign-extended, and their bitwise AND
   decides whether to return.
5. The eligible aim copy is source `+518/+51c/+520 -> +524/+528/+52c`.
   The linked target supplies eligibility bytes, not the copied aim values.

References:

- C export: `research/decomp/ghidra-export/chunk_0007.c:196-223`.
- Symbol extent: `research/symbols/GG4E-CSM-20220412.map:694` records
  `8005685c`, size `000000a4`; the next export begins at `80056900`.
- Fixed reader: `research/tools/matching-decomp/read_archived_transform_history_evidence.py`.
- Synthetic tests: `research/tools/matching-decomp/test_archived_transform_history_evidence.py`.

## Archive authentication and physical trace

Local inputs, both under
`research/decomp/GotchaForce.rep.before_force_create/idata/00/~00000000.db/`:

| Snapshot | Whole-file SHA-256 |
| --- | --- |
| `db.3.gbf` | `7b50dd2d2e17b4bfcc89a64cde27010247d0cbf0f48bd5c059f50275f40458d0` |
| `db.4.gbf` | `1f86813d91ea8e2c4564f96622ec42555e1dba2c78aa81ad654e892140d019f8` |

The reader reuses `read_archived_constants.inspect` before constructing its
own parser. This checks the complete snapshot digest against the existing
allowlist, GBF layout and exact table schemas, the `boot.dol` program name,
Gekko/Broadway big-endian language, Ghidra `12.1.2` metadata, address map,
empty File Bytes table, full data5 digest and existing controls. It then
reuses `read_archived_command_evidence.mappings` for the exact text1/data3/data5
block and subblock identities, including overlap rejection. No mapping or
authentication guard was weakened for this function.

- Executable SHA-256 recorded in metadata:
  `21454a8880c6254616662710d6ec626e43d853999da2cdfad700030960a94836`.
  This is import metadata, not independent authentication of unchanged DOL bytes.
- File Bytes table: version `0`, root `-1`, count `0`.
- GBF block size `16384`; master root `1`; table roots: Program `2`, Property
  Table `9`, ADDRESS MAP `10`, Memory Blocks `13`, Sub Memory Blocks `12`.
- Image offset: `80000000`.
- Memory block: `MAIN_.text1`, key `1`, encoded start
  `20000000000055e0`, resolved start `800055e0`, length `2796416`.
- Subblock: key `1`, parent `1`, type `2`, length `2796416`, starting offset
  `0`, chain root `21`, source offset `0`.
- Inherited full data5 control SHA-256:
  `989c794b17fc95de6e57810f5c89db23d585c85a15faafc994d9a5bd9a0e61b4`.

The one allowed text range has SHA-256
`9ad43b6e8ed1d405fa3c2e0fc0803871f93353c6ebf6f7ae7585d07211bf41a6`.
Both snapshots have exactly this physical trace:

| Field | Value |
| --- | --- |
| Address / exclusive end | `8005685c` / `80056900` |
| Byte width | `164` |
| Root buffer / data buffer | `21` / `42` |
| Logical chain offset | `332412` |
| Data-buffer-relative offset | `4852` |
| Physical file offset | `709370` |
| Span length | `164` |
| Obfuscated | `true` |

No executable bytes, raw ranges or arbitrary-address interface are emitted.
The JSON output's `constants` list is empty. The pre-existing data5 reads are
archive authentication controls, not constant dependencies of this function.

## Exact load/store and conditional order

`S` denotes source actor base `r3`. `T` is the linked pointer loaded from
`S+cc` into `r4`. All field offsets and PCs below are hexadecimal. These are
derived instruction facts, not executable-word dumps. `r4` ceases to hold the
pointer when the target mask is loaded into it at `800568cc`.

### Position history, before any linked-target read

| PC | Operation |
| --- | --- |
| `8005685c` | `lwz r4, S+2c` |
| `80056860` | `lwz r0, S+30` |
| `80056864` | `stw r4, S+5e8` |
| `80056868` | `stw r0, S+5ec` |
| `8005686c` | `lwz r0, S+34` |
| `80056870` | `stw r0, S+5f0` |
| `80056874` | `lwz r4, S+20` |
| `80056878` | `lwz r0, S+24` |
| `8005687c` | `stw r4, S+2c` |
| `80056880` | `stw r0, S+30` |
| `80056884` | `lwz r0, S+28` |
| `80056888` | `stw r0, S+34` |

Thus old `+2c/+30/+34` is retained at `+5e8/+5ec/+5f0` before current
`+20/+24/+28` replaces it. Each vector sequence loads X and Y before storing
either, then loads Z after the X and Y stores. Neither a per-component
load/store interleave nor an up-front three-component snapshot captures the
exact access order.

### Raw paired-short histories and scalar history

| PC | Operation |
| --- | --- |
| `8005688c` | `lwz r0, S+70` |
| `80056890` | `stw r0, S+76` |
| `80056894` | `lhz r0, S+74` |
| `80056898` | `sth r0, S+7a` |
| `8005689c` | `lwz r0, S+1d64` |
| `800568a0` | `stw r0, S+1d6a` |
| `800568a4` | `lhz r0, S+1d68` |
| `800568a8` | `sth r0, S+1d6e` |
| `800568ac` | `lfs f0, S+6d0` |
| `800568b0` | `stfs f0, S+6d4` |

For each short triple, the first two 16-bit patterns travel together in one
32-bit memory instruction. The third pattern is zero-extended by `lhz` and
written with `sth`; the stored 16 bits are unchanged. A signed short host
representation is valid only if it preserves these bits. There is no `lha`,
BAM conversion, angle normalization or arithmetic in these copies.

A checked host model should preserve instruction boundaries: failure while
validating the paired word must not become a successful first-short write,
and a later halfword failure must not roll back a completed word store. This
is a host modeling consequence of the instruction ordering, not evidence
about hardware alignment exceptions, cache transactions or exception replay.
Likewise, the archive does not establish live FPSCR behavior for the floating
scalar load/store; finite-value modeling should remain distinguished from
arbitrary bit-pattern and exception parity.

### Late linked-target and visibility guards

| PC | Operation |
| --- | --- |
| `800568b4` | `lwz r4, S+cc` |
| `800568b8` | `cmpli`: `BF=0`, `L=0`, `rA=4`, immediate `0` |
| `800568bc` | `bclr`: `BO=12`, `BI=2`, `BH=0`, `LK=0` |
| `800568c0` | `lbz r0, T+83` |
| `800568c4` | `extsb. r0, r0` (`Rc=1`) |
| `800568c8` | `bc`: `BO=4`, `BI=2`, `AA=0`, `LK=0`, target `800568e4` |
| `800568cc` | `lbz r4, T+5e6` |
| `800568d0` | `lbz r0, S+3e5` |
| `800568d4` | `extsb r4, r4` (`Rc=0`) |
| `800568d8` | `extsb r0, r0` (`Rc=0`) |
| `800568dc` | `and. r0, r4, r0` (`Rc=1`) |
| `800568e0` | `bclr`: `BO=12`, `BI=2`, `BH=0`, `LK=0` |

The two conditional returns test CR0.EQ without testing/decrementing CTR or
updating LR. The first returns on a null linked pointer. If non-null, any
nonzero signed value of target `+83` branches directly to the source aim copy,
without reading either visibility-mask byte. Only a zero target `+83` takes
the target-mask-then-source-mask path. Sign-extending both bytes before AND
does not change whether their low-byte intersection is zero.

Null or ineligible targets leave the aim history untouched. They do not undo
the position, short or scalar history writes that precede the pointer read.
The function has no earlier source-null check and no whole-object validation.

### Eligible source aim copy and final return

| PC | Operation |
| --- | --- |
| `800568e4` | `lwz r4, S+518` |
| `800568e8` | `lwz r0, S+51c` |
| `800568ec` | `stw r4, S+524` |
| `800568f0` | `stw r0, S+528` |
| `800568f4` | `lwz r0, S+520` |
| `800568f8` | `stw r0, S+52c` |
| `800568fc` | `blr` |

This again has X/Y loads, X/Y stores, then the Z load/store. No target
position or target aim is loaded. There is no call to another function and no
read from a constant pool, `r2` or `r13` anywhere in the authenticated span.

## Validation

Focused tests only, run from `research/tools/matching-decomp`:

```sh
PYTHONDONTWRITEBYTECODE=1 python -m unittest \
  test_archived_transform_history_evidence \
  test_archived_actor_traversal_evidence \
  test_archived_command_evidence test_archived_wait_evidence \
  test_archived_constants test_archived_world_matrix_evidence -v
```

Result: **96 tests passed**, comprising 24 new transform-history tests and
72 tests of the directly reused parser, mapping and decoder modules.

The new suite exercises exact fixed extent/hash, integer-only parameters,
wrong/duplicate allowlists, root/alignment/bounds refusal before reads,
short/long widths independently of digest, authentication and mapping failures
before span reads, selected load/store/branch/return fields, signed
displacements, unsigned short tails, raw-output exclusion, unsupported-form
refusal and absence of an address/width CLI. The successful synthetic inspect
case checks that only the one fixed span and no new constants are requested.
Fixtures are synthetic and contain no copied archive byte ranges.

Both CLI invocations against the named archives passed complete authentication
and yielded identical 41-instruction lists, hashes and physical traces. The
reader emits all instructions in the fixed span or refuses, rather than
silently omitting unsupported forms. No full repository aggregate, runtime
suite, remote/rig inspection, new acquisition, install, upload, source transfer
or publication was performed for this evidence task.
