# Callback 800715f8 and ammo 8006dbe0: bounded archive evidence

## Independently fixed selection, before archive reads

The scope is exactly two 224-byte complete function bodies and four f32
constants, 464 selected bytes total, after the unchanged whole-snapshot
ProgramDB authenticator. This is static evidence, not original execution,
`MATCH`, a hardware observation, or playability.

- `ghidra-export/chunk_0009.c:5295–5338`, `_index.tsv:1492–1493` and
  `../symbols/GG4E-CSM-20220412.map:895–896` independently bound callback
  `[800715f8,800716d8)`, map size `e0`.
- `ghidra-export/chunk_0009.c:2866–2906`, `_index.tsv:1413–1414` and
  `../symbols/GG4E-CSM-20220412.map:850–851` independently bound helper
  `[8006dbe0,8006dcc0)`, map size `e0`.
- The callback's named scalar `FLOAT_80437748`, `FLOAT_804376e4`,
  `FLOAT_80437768`, `FLOAT_804376e0` references at C lines5307–5316
  independently justify four separate 4-byte selections. No adjacent constant
  or table is selected. Their values are not inferred from legacy code.
- `80437658` (+0, f32) and `804376a0` (2^52+2^31, f64) are reused from
  `actor-status-timers-evidence-2026-11-13.md`, not new targeted reads.

The two function addresses are literal selections justified by the C/index/map,
not followed archive pointers. `8007db5c`, projectile data/assets, phase tables,
and magnitude/model code are outside this selection. No original executable,
retired port driver, live telemetry or estimator implementation is run/imported.

## Authentication and provenance

Reader: `../tools/matching-decomp/read_archived_callback_ammo_evidence.py`.
Tests: `../tools/matching-decomp/test_archived_callback_ammo_evidence.py`.
The reader imports unchanged shared authenticators, does not expand any shared
allowlist, and exposes only one positional snapshot filename. Each complete
body's SHA-256 is checked before decoding. Every selected instruction is
represented, including operand direction, signedness, branch fields and the
terminal return. Unknown/reserved forms fail closed.

Both locally available snapshots agree on all selected evidence, mappings,
physical spans and complete instruction schedules:

| Snapshot | Whole-snapshot SHA-256 |
| --- | --- |
| db.3.gbf | `7b50dd2d2e17b4bfcc89a64cde27010247d0cbf0f48bd5c059f50275f40458d0` |
| db.4.gbf | `1f86813d91ea8e2c4564f96622ec42555e1dba2c78aa81ad654e892140d019f8` |

The unchanged `read_archived_constants.inspect` checks whole-file identity,
supported schemas/language/address map, empty File Bytes table, complete data5
identity and its existing controls first. Unchanged
`read_archived_command_evidence.mappings` then verifies text1/data3/data5
block/subblock identities and overlap constraints. Only text1 and data5 are used
for the six additional literal selections.

- Executable SHA-256 **import metadata**:
  `21454a8880c6254616662710d6ec626e43d853999da2cdfad700030960a94836`.
  This is not independent proof of unchanged original executable bytes.
- File Bytes table: version0, root−1, count0. GBF block size16384, master root1,
  image offset `80000000`.
- Text1: `[800055e0,802b0160)`, length2796416, chain root21.
- Data5: `[80436a20,8043d500)`, length27360, root263, full SHA-256
  `989c794b17fc95de6e57810f5c89db23d585c85a15faafc994d9a5bd9a0e61b4`.
- Address resolution below uses previously recorded r2=`8043ea20`; this is not
  fresh startup authentication or a claim about live processor state.

| Fixed span | Bytes / instructions | SHA-256 |
| --- | --- | --- |
| `[800715f8,800716d8)` | 224 / 56 | `7735b73fbd6b3149290d56bad8eed6be6202d6afbcb315708646b0717bbda4a8` |
| `[8006dbe0,8006dcc0)` | 224 / 56 | `0b2e322f452d317b5f515e0ebd95f821a10cdbee5db9cdbd07678c8d251eed31` |

All physical offsets in this table are decimal, and every selected span uses
obfuscated ProgramDB storage decoded by the existing reader:

| Selection | Root / data buffer | Chain offset | Data offset | Physical offset | Bytes |
| --- | --- | --- | --- | --- | --- |
| 800715f8 | 21 / 49 | 442392 | 186 | 819392 | 224 |
| 8006dbe0 | 21 / 48 | 427520 | 1692 | 804514 | 224 |
| 80437748 | 263 / 264 | 3368 | 3368 | 4345134 | 4 |
| 804376e4 | 263 / 264 | 3268 | 3268 | 4345034 | 4 |
| 80437768 | 263 / 264 | 3400 | 3400 | 4345166 | 4 |
| 804376e0 | 263 / 264 | 3264 | 3264 | 4345030 | 4 |

| Constant | f32 bits | Value | SHA-256 |
| --- | --- | --- | --- |
| 80437748 | `41200000` | 10 | `b9e69238a01189ddad0c70c62fc04d362b55ee6eefaa558dd13fc45ac1d665be` |
| 804376e4 | `00000000` | +0 | `df3f619804a92fdb4057192dc43dd748ea778adc52bc498ce80524c014b81119` |
| 80437768 | `41700000` | 15 | `6684130864793326a78b61833fd87b8235a4a62157e3d50ac29ed8a2abaf83c1` |
| 804376e0 | `bf800000` | −1 | `b705efea49cb3296c6f0417c21fe14f10adb140333fd79d7cfc3318904f887ea` |

## Ordered callback facts

PCs and field offsets below are hexadecimal. These statements describe the
archived instructions, not decompiler expression ordering or an implementation
claim.

1. `7160c` loads actor `1d0f` with `lbz`. `71610` sign-extends the byte with
   record (`extsb.`); `71614` branches on equality to zero to `71648`. Every
   nonzero signed byte, including a negative value, reaches the following
   writes. The actual owner is the retained stream's `part1.state1b`.
2. `71618` loads signed heading72 with `lha`. `71620` adds `0x10000` and
   `71628` adds `−0x8000` before `71630` stores the low16 bits to lockYaw5ae.
   This stored value is heading−`0x8000` modulo65536. Interleaved constant
   loads at `7161c,71624,7162c,71634` obtain10,+0,15,−1 respectively.
   Observable actor stores are **5ae,44,4c,48,50**, in that order:
   `71630` yaw, `71638` hSpeed44=10, `7163c` hDecel4c=+0,
   `71640` yVel48=15, `71644` gravityCoeff50=−1.
3. `71648..71654` set actor, slot2, amount1, consume1.
   `71658` calls `8006dbe0`. `7165c` compares the return to zero, and
   `71660` branches to epilogue `716c4` on zero. Consequently an insufficient
   count returns **after** any backflip writes and **before** the borg load.
4. Only after a nonzero helper return does `71664` load signed actor3e8.
   `71668` repeats sign-extension and records the zero test. Type0 calls
   `8007db5c(actor,0)` at `71678`; type3 calls variant1 at `71690`;
   type10 calls variant3 at `716c0`. Other signed types perform no spawn call.
5. On type3, **after the variant1 call returns**, `71694` loads7c8 and
   `71698` applies signed-byte `extsb.`. Nonzero calls variant2 at `716a8`;
   zero returns. The byte's owner is the existing Double owner `arm7c8`.
   A boundary at the first projectile call must not read7c8 early or claim a
   completed spawn. The terminal callback return is `716d4`.

## Ordered ammo facts

`8006dbe0` is a genuine count/mirror/debit/refill operation. There is no
capacity/max load, unlimited-ammo rule, allocator call, default-success shim
or fallback count in this complete body.

1. `6dbe0` computes `(slot << 3)` in32-bit register arithmetic. `6dbe8`
   adds the actor address to form r4. `6dbec` loads **signed16** current774;
   `6dbf0` compares it with signed32 amount r5. If current<amount,
   `6dbf8` sets return0 and goes to `6dcb8`, with no actor field writes.
2. Otherwise `6dc00` tests consume r6. Zero returns1 via `6dc08`, also
   without actor writes. This check occurs after the count comparison.
3. A consume first stores the retained original current to mirror776 at
   `6dc10`. `6dc14` then **reloads** signed current774, `6dc18` subtracts
   amount (`subf r0,r5,r0`), and `6dc1c` stores the low16 bits back to774.
   Only then does `6dc20` load **signed16** refillType790.
4. Type1 branches to `6dc7c`. Types below1 are compared against0:
   negative types skip timer work, while type0 reaches `6dc48`. Types above1
   are compared against4: types2/3 reach `6dcac`, types≥4 skip timer work.
   Skipped timer work still returns success1 at `6dcb4`.
5. Type0 **reloads** signed post-debit current774 at `6dc48` and compares
   against0 at `6dc4c`. A nonzero count skips timer work. Only count0 loads
   **signed16** refillParam792 at `6dc54`. It constructs
   `0x43300000:(signedParam XOR 0x80000000)` in stack memory, loads the
   reused f64 constant at `6dc64`, performs **fsubs** at `6dc70`, then
   stores the result to timer778 at `6dc74`. This conversion is exact for
   every signed16 parameter under the stated ordinary finite arithmetic.
6. Type1 loads signed refillParam792 at `6dc7c` and forms the same
   conversion. Crucially, `6dc94` loads existing timer778 **before**
   `6dc98` loads the constructed f64. `6dc9c` performs **fsubs** to obtain
   the f32 parameter. `6dca0` performs **fadds** oldTimer+parameter, with
   single-precision rounding, and `6dca4` stores timer778. It is not a
   binary64 addition silently substituted for the source single operation.
7. Types2/3 load the reused positive-zero constant at `6dcac` and write
   timer778 at `6dcb0`. There is no parameter or old-timer load on this path.
8. `6dcb4` sets success1. `6dcb8` restores the stack; `6dcbc` returns.

For callback slot2 the same retained status slot/cell owns:
current784, mirror786, timer788, refillType7a0 and refillParam7a2.
The current value is never synthesized to force an insufficient-count exit.
Mirror/debit stores precede any later missing timer input or projectile boundary
and must remain visible. Register subtraction and halfword storage, plus the
later signed reload, should not be replaced by an unrelated clamped ammo API.

## Reproduction and controls

From the repository root, with the two already present snapshots:

```sh
python3 -m unittest discover -s research/tools/matching-decomp \
  -p test_archived_callback_ammo_evidence.py -v
python3 research/tools/matching-decomp/read_archived_callback_ammo_evidence.py \
  'research/decomp/GotchaForce.rep.before_force_create/idata/00/~00000000.db/db.3.gbf'
python3 research/tools/matching-decomp/read_archived_callback_ammo_evidence.py \
  'research/decomp/GotchaForce.rep.before_force_create/idata/00/~00000000.db/db.4.gbf'
```

Validation on2026-11-14: **18 tests passed**, including4 real-archive tests;
none skipped. The independent frozen semantic fixture reencodes all112
instructions to both selected body hashes. All3,584 single-bit instruction
controls either refuse or preserve the changed bit in a distinguishable,
independently reencoded operand schedule. All3,712 one-bit mutations across
all464 selected payload bytes are refused. The suite checks exact physical
spans, six-read traces after the unchanged authenticator, mapping/type/extent
refusals before reads, signed field/store/reload order, constant meaning,
terminal returns, internal branches, call destinations, schema and whole-file
tampering, and absence of arbitrary address/dump options.

Local reports are `.tmp/callback-ammo-evidence-20261114/db.3.json`,
`db.4.json`, and `tests.log`. They contain derived operands, provenance and
hashes, not raw instruction payloads or original executable files. Optional
archive tests skip when inputs are absent; they do not fetch inputs.

## Claim ceiling and remaining boundaries

This evidence is archived ProgramDB static evidence. It proves neither
unchanged original-DOL bytes, original instruction execution, processor-control
state, live callback dispatch, matching decompilation, hardware exactness,
runtime integration nor real playability. The separate runtime/composed tests
must establish their own narrower implementation and integration claims.

No read or implementation of `8007db5c` is provided. For a selected successful
projectile call, the real allocator, projectile rows, field/pointer stores,
joint transform and lifecycle remain an explicit boundary. No spawned boolean
or asset/collision result is invented. General magnitude numerical-model
provenance/licensing is independent of this work and remains unchanged.
