# Archived actor movement-followup evidence, 2026-11-13

## Scope and verification

`research/tools/matching-decomp/read_archived_movement_followup_evidence.py`
authenticates the two existing allowlisted ProgramDB snapshots through the
unchanged constants reader. It validates exact memory/subblock mappings, hashes
two fixed instruction spans, checks selected instruction words and reads three
fixed scalar targets. It emits provenance, instruction facts and scalar values,
not raw instruction ranges. There is no arbitrary-address CLI, vendor-code
execution, source download, installation, emulator, process/rig access or upload.

The reader and its 12 synthetic-only tests passed on 2026-11-13. Both snapshots
under `GotchaForce.rep.before_force_create/idata/00/~00000000.db/` passed:

| Snapshot | SHA256 |
| --- | --- |
| db.3.gbf | 7b50dd2d2e17b4bfcc89a64cde27010247d0cbf0f48bd5c059f50275f40458d0 |
| db.4.gbf | 1f86813d91ea8e2c4564f96622ec42555e1dba2c78aa81ad654e892140d019f8 |

| Function/span start | Bytes | SHA256 |
| --- | ---: | --- |
| 80048648 | 212 | 0eb26bc9a603d933ffcaf3e9065583d3127cb603be56c29d887566f9211a2ad9 |
| 8004d08c | 360 | ba2fb11f03cbfae5126e2f32f33bae5fe2b01840191bd77d8e7348a507ae97e7 |

Program name, language, metadata, empty File Bytes table and the complete
`MAIN_.data5` hash are checked by the original authenticated machinery. The
text mapping is block/subblock key1, start800055e0, length2796416, chain21.
The scalar mapping is block/subblock key7, start80436a20, length27360, chain263.
Both snapshots return identical facts and values. Agreement is archived
ProgramDB evidence, not proof of unchanged original-DOL bytes or live runtime
parity. The recorded executable SHA remains import metadata.

Decompiled references are `ghidra-export/chunk_0005.c:4232` and
`ghidra-export/chunk_0006.c:2156`. Instruction order below corrects several
decompiler hoists/reassociations. Stack/prologue saves are omitted from the
actor-facing contract.

## Exact constants

| Address | Type | Bits | Value | Chain offset | Physical GBF offset |
| --- | --- | --- | --- | --- | --- |
| 80437104 | f32 | 3f000000 | 0.5 | 6e4 | 4246ea |
| 80437134 | f32 | 3f333333 | 0.699999988079071044921875 | 714 | 42471a |
| 8043714c | f32 | 40a00000 | 5 | 72c | 424732 |

All three values are in obfuscated chain263/data buffer264; chain and buffer
numbers are decimal, addresses/offsets hexadecimal. These are new fixed targets
local to this reader, not independently recorded original-DOL controls. The
existing twelve-target constant reader and its four control values are unchanged.
The existing values804370f0=1,804370f4=positive zero and
804370f8=`4330000080000000` (f64:2^52+2^31) are reused, not guessed.

## Caller48648: when the followup happens

The source preserves r3 actor and r4 channel, then:

1. Load actor+1d88. Null returns without loading1d8c.
2. Load actor+1d8c. Null returns.
3. Only for channel1, load byte578. Only if that is1, load byte1db3.
   Both1 suppress the call entirely.
4. Load byte1d9a, sign-extend it, and test the PowerPC `slw(1, channel)` bit.
   A set bit calls4a41c(actor,0,channel) and returns. That path has no6d8 store
   and no4d08c call.
5. Otherwise read the selected mode-table target at802d0d70+mode*4 and call
   actual setup. Mode-zero target4871c is independently established by
   `archived-ready-setup-2026-11-13.md`.
6. After setup returns, test the retained channel. Only channel1 loads1.0,
   stores actor+6d8 at486fc, and calls4d08c at48700.

A failure at the followup boundary must retain completed setup and the6d8=1
store. A followup implementation cannot substitute for setup, supply fake
success, run on the alternate branch or move the6d8 store after the call.
The bounded host's four supported channels are not a claim to emulate arbitrary
PowerPC shift counts or raw mode-table indices.

## Minimal disabled-state contract

The actual entry does **not** hoist the0.5 constant load:

1. At4d090, load byte actor+3e8; if equal5, branch directly to4d1e4.
2. Otherwise at4d09c, load byte+661, sign-extend and test nonzero. Nonzero
   branches directly to4d1e4.
3. Otherwise at4d0a8, load uint+5e0 and test bit0x40. A clear bit branches
   directly to4d1e4.
4. At4d1e4, load authenticated positive zero; at4d1e8 store it to+6d0; return.

These three early paths do not read+71d, descriptor+4b0, transform storage,
position+24, scales+b4/+6d8, fields66c/670 or the three new constants. Existing
RomActor storage represents+3e8 as the high byte of big-endian `borgNumber`,
not its low byte. The only actor write is+6d0 (`stepHeight`).

## Signed-byte override

After all three gates pass, load+71d exactly once at4d0b4, sign-extend and test.
If it is nonzero:

1. Sign-extend the retained byte and subtract1. Raw80 means-128, then-129;
   rawff means-1, then-2. This is not an unsigned-byte formula.
2. Form the standard43300000/xoris8000 conversion on the stack. Load the
   existing f64 bias804370f8, then new f32 constant8043714c=5, then the stacked
   conversion and actor+b4 (4d0e4).
3. `fsubs` at4d0e8 produces the exact small integer `signedByte-1`.
4. `fmuls` at4d0ec rounds5 times that integer to f32; `fmuls` at4d0f0 rounds
   that result times the already loaded+b4 scale to f32.
5. Store+6d0 once at4d0f4 and return. There is no nonnegative clamp.

This path does not consume descriptor, transform, position,66c/670 or6d8.
Byte1 with a negative scale can produce-0, which is stored without alteration.

## Normal branch: complete ordered actor memory contract

This branch requires+71d to be zero. The instructions retain register values
across later reads; replacing them with fresh reads, cloned snapshots or a
preflight of all required fields changes the observable failure/store order.

### Initial candidate

1. 4d0fc: load actor+4b0 and retain this descriptor for the list starting+22.
2. 4d100: load actor+670 into f4 once. Every list candidate later uses this
   entry-time snapshot, even though decompiled C appears to reload the field.
3. 4d104: load actor+920 (equivalently actor+8f0+1*30, world-matrix Y1).
4. 4d10c: load0.5 into f2. At4d110, store the loaded+920 value to+6d0.
5. 4d114: load actor+66c into f1. At4d118, reload+6d0 into f0.
6. 4d11c: `fnmsubs f0,f1,f2,f0` computes the negative of the fused
   multiply-subtract, with one single-precision rounding. Store it at4d120.

The first+6d0 store must survive a subsequent unsupported66c or arithmetic
case. There is no per-iteration670 read and no descriptor-list dereference yet.

### First descriptor joint

1. 4d124: reload actor+4b0. This descriptor supplies+f, while the list still
   uses the initially retained descriptor.
2. 4d128: load actor+24 (baseY) into f3.
3. 4d12c: load descriptor+f. At4d130, reload+6d0 into f0 **before** loading
   the selected transform.
4. Sign-extend the byte, multiply by0x30 and form the modulo32 source address.
   At4d140 load actor+8f0+signedIndex*30 into f1.
5. 4d144: `fsubs f1,f1,f3`, then4d148: `fmadds f1,f1,f2,f3`.
   Thus the delta rounds first; the0.5 multiply plus retained baseY rounds
   once as a fused operation.
6. Compare the candidate with the retained pre-transform+6d0. Store the
   candidate at4d154 only when it is strictly less.

The root byte has no-1 sentinel; rawff is a negative source address index.
The bounded host may explicitly refuse negative/out-of-owned-storage addresses,
but must do so when reached and retain the two earlier stores.

### Up to four list joints

Set count0, then test count<4 at4d18c **before** each descriptor-list byte load.
The list addresses are retainedDescriptor+22,+2a,+32,+3a; there is no fifth read.
Load the current byte at4d194, sign-extend and compare with-1. Only-1 ends the
list. Other negative bytes remain negative indices, not alternate sentinels.

For each nonsentinel byte:

1. 4d164: reload+6d0 before transform access.
2. 4d170: load world-matrix Y at actor+8f0+signedIndex*30.
3. 4d174: subtract the **entry-time670 snapshot**, rounding to f32.
4. Compare to the retained pre-transform+6d0. Store the candidate only if
   strictly less, at4d180.
5. Increment count and the retained list pointer by8, then test the count.

### Relative result, multiply association and clamp

1. 4d1a4: reload+6d0;4d1a8: reload actor+24. Do not reuse the earlier baseY.
2. Load0.7f, perform `fsubs` at4d1b0, load positive zero, then store the
   relative displacement to+6d0 at4d1b8.
3. 4d1bc: load actor+6d8 into f1, **then**4d1c0: reload+6d0 into f3.
4. 4d1c4: `fmuls f1,f2,f1` rounds0.7f times the scale **first**.
5. 4d1c8: `fmuls f1,f3,f1` rounds relative displacement times that product.
   Store+6d0 at4d1cc.
6. Reload+6d0 at4d1d0; compare with positive zero. Only a strictly negative
   result receives a final+0 store at4d1dc. Negative zero survives.

The decompiled left-associated `value * 0.7f * scale` is not equivalent.
A finite f32 witness is value=`3dcccccd` (0.1f), scale=`3fc00000` (1.5):
the instructions produce`3dd70a3d`; the decompiled association produces
`3dd70a3e`. A late scale failure preserves the earlier displacement store.

## Floating-point and ownership limits

The new instruction facts distinguish`fsubs`,`fmuls`,`fmadds`,`fnmsubs` and
ordered`fcmpo`. For the existing nearest-even/gradual-underflow host model,
the negative fused step is `-fma(66c,0.5,-previous6d0)`, not
`fma(-66c,0.5,previous6d0)`: exact cancellation has a different zero sign.
Do not separately round the product before either fused step. The source
constants and instruction forms do not establish the live FPSCR rounding mode,
non-IEEE mode, enabled exceptions or NaN payload behavior.

The strict-less branches use CR0.LT; an unordered comparison also skips the
store if execution continues. This is not permission to treat a finite-only
host model as an exception/NaN emulator. Its nonfinite, rounded-overflow,
unowned-address and unsupported-record refusals remain explicit model limits.

World-matrix Ys are actor+8f0+index*30. They are not bind-pose translations,
local JObj translations or guessed aim anchors. Direct association of actual
RomActor state with existing mapping/wait/setup identities is a bounded host
association, not proof of production hydration. Shared marker71d, descriptor4b0,
movement6d8 and actor6d0 must stay in their actual owning records. No parallel
copy may silently replace a live source field.

This audit verifies the archived instruction/scalar evidence and reader only.
Focused implementation and composed-runtime test results belong with the
implementation report; it does not claim aggregate, browser, emulator,
original-game replay or production integration validation.

## Reproduction

From the repository root:

```sh
python -m unittest discover -s research/tools/matching-decomp -p test_archived_movement_followup_evidence.py -v
python research/tools/matching-decomp/read_archived_movement_followup_evidence.py 'research/decomp/GotchaForce.rep.before_force_create/idata/00/~00000000.db/db.3.gbf'
python research/tools/matching-decomp/read_archived_movement_followup_evidence.py 'research/decomp/GotchaForce.rep.before_force_create/idata/00/~00000000.db/db.4.gbf'
```

The JSON output contains fixed facts and provenance only. The tests construct
synthetic inputs and verify authentication failures, fixed scope, range/scalar
bounds, byte/hash mismatches, signed branches, source memory order, floating
operand fields and caller postamble targets without storing archived payloads.
