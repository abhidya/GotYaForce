# Actor input testers: archived source evidence

## Result and limits

The dedicated fixed reader represents **all 307 instructions** in
`800699d8..80069ea4`: the ordered six-test wrapper, all six testers, and their
directly reached descriptor dispatch `80069dd0`. Both existing authenticated
local ProgramDB snapshots agree on every instruction, operand, digest and
physical trace. Every instruction, including prologues, epilogues, branches and
returns, is represented; none is assumed unreachable.

This is archived source evidence, not unchanged original-DOL identity, a live
input capture, runtime pointer/actor ownership, gameplay parity, production
integration or a complete actor tick. The active bodies `8005c080`, `80069ea4`
and `80069fe0` remain explicit boundaries. The linked actor reached through
`4a4` is not authenticated as a runtime owner by these instructions. No actor
pointer is followed and no runtime descriptor payload is read by the reader.

Artifacts:

- [Fixed reader](../tools/matching-decomp/read_archived_actor_input_testers_evidence.py).
- [Operand and refusal tests](../tools/matching-decomp/test_archived_actor_input_testers_evidence.py).
- C cross-reference: `ghidra-export/chunk_0009.c:220-489`.
- Symbol map: `research/symbols/GG4E-CSM-20220412.map:807-814`.

**The map has no `800699d8` row.** Its selected 176-byte span is supported by
the C entry/next marker and authenticated return at `80069a84`; no map extent
is invented. All seven remaining selected extents agree with the symbol map,
the next C marker, and the authenticated final `blr`.

The tools are read-only stdlib. The CLI takes a snapshot path only; there are
no address, width, raw-output or execution options. Shared readers and their
allowlists remain unchanged. Output consists of derived fields, hashes and
physical provenance, never raw executable bytes. No original or archived
instructions are executed.

## Authentication and fixed spans

Inputs are the existing local
`GotchaForce.rep.before_force_create/idata/00/~00000000.db/` snapshots:

- `db.3.gbf`: `7b50dd2d2e17b4bfcc89a64cde27010247d0cbf0f48bd5c059f50275f40458d0`.
- `db.4.gbf`: `1f86813d91ea8e2c4564f96622ec42555e1dba2c78aa81ad654e892140d019f8`.

Unchanged `read_archived_constants.inspect` authenticates the complete snapshot,
exact schemas, executable metadata, big-endian Gekko/Broadway language, address
map, empty File Bytes table, complete data5 digest and existing controls before
new reads. Unchanged `read_archived_command_evidence.mappings` validates the
exact text1/data3/data5 mappings and all-block nonoverlap. Each new range must
match its exact address/width tuple, root, alignment, byte width and SHA-256
before any instruction is decoded. Unsupported forms fail closed.

- Executable import-metadata SHA-256:
  `21454a8880c6254616662710d6ec626e43d853999da2cdfad700030960a94836`.
  Metadata alone does not prove unchanged executable bytes.
- File Bytes: version 0, root -1, count 0.
- Block size 16384, master root 1, image offset `80000000`.
- Text1 starts `800055e0`, length 2796416, block/subblock 1, chain root 21.
- Data5 digest:
  `989c794b17fc95de6e57810f5c89db23d585c85a15faafc994d9a5bd9a0e61b4`.
- All selected text reads use subblock type 2, starting/source offsets 0.

| Fixed span | Bytes / instructions | SHA-256 | Return PC |
| --- | --- | --- | --- |
| `800699d8..80069a88` | 176 / 44 | `c809fe8851e308079759e95d7cb982414ac6399dae30d964ee36ee00f0ba07fd` | `80069a84` |
| `80069a88..80069b10` | 136 / 34 | `c7859e78b66a2dc8fae3d67fa0fe35809f941b7da353bb344b4d60173beb8c0d` | `80069b0c` |
| `80069b10..80069b98` | 136 / 34 | `d314cddf30ff9cec52d98556ec16a0051b206c441c685e0e3db0eace3e1e113f` | `80069b94` |
| `80069b98..80069bf0` | 88 / 22 | `b1b819b1e9ff72f8e8154ac586bd3b362690f2fd099e3eb2ae73f0cc40e025cc` | `80069bec` |
| `80069bf0..80069c50` | 96 / 24 | `672733b12993bfdaf4141580b1c35f8914c4fb7f3e6139f877228278dba385fe` | `80069c4c` |
| `80069c50..80069cb0` | 96 / 24 | `64085e89f7385ffc9e08355146fe8c2ce9b61634ccca8bc8ea652174a28b37b2` | `80069cac` |
| `80069cb0..80069dd0` | 288 / 72 | `948dca24959a3810bd95deeddc2109e709a342b405a633f060df63e5746299ab` | `80069dcc` |
| `80069dd0..80069ea4` | 212 / 53 | `d47e5fab253284676c8062bab436402e6ba6e75cfcc3e3df2c8b86b1ead76830` | `80069ea0` |

The eight physical spans are identical in both snapshots. They use obfuscated
storage, root buffer 21 and data buffer 47. Decimal offsets:

| Entry | Chain offset | Data offset | Physical offset | Length |
| --- | --- | --- | --- | --- |
| `800699d8` | 410616 | 1166 | 787604 | 176 |
| `80069a88` | 410792 | 1342 | 787780 | 136 |
| `80069b10` | 410928 | 1478 | 787916 | 136 |
| `80069b98` | 411064 | 1614 | 788052 | 88 |
| `80069bf0` | 411152 | 1702 | 788140 | 96 |
| `80069c50` | 411248 | 1798 | 788236 | 96 |
| `80069cb0` | 411344 | 1894 | 788332 | 288 |
| `80069dd0` | 411632 | 2182 | 788620 | 212 |

## Ordered wrapper and genuine no-input result

`800699d8` calls, in order:

| Call PC | Target |
| --- | --- |
| `800699ec` | `80069cb0` |
| `80069a04` | `80069c50` |
| `80069a1c` | `80069bf0` |
| `80069a34` | `80069b98` |
| `80069a4c` | `80069b10` |
| `80069a64` | `80069a88` |

Each later call is reached only if every earlier return is zero. Any of the
first five nonzero results is normalized to 1 and branches to the epilogue.
After the sixth call, `neg r0,r3; or r0,r0,r3; rlwinm r3,r0,1,31,31` extracts
bit 31 of the modulo-32-bit OR, yielding 0 for zero and 1 for any nonzero word.
It is not an unconditional zero return or a synthetic success callback.

Every tester's first actor-memory access is a separate store of **zero to
`595`**, at `69cc8`, `69c60`, `69c00`, `69ba8`, `69b20`, and `69a98` in wrapper
order. These are observable source stores even if the old value is already
zero. A genuine no-input chain with `4a0=0`, no blocking `58e` bits and
`5d4=0` reaches all six stores, returns zero, does not read `748`, and does not
reach a descriptor or linked actor. Missing unrelated owners must not become
eager obstacles to this source path.

## Exact helper schedules

All offsets below are hexadecimal. A load occurs only after earlier reached
conditions; stores are retained if a later boundary cannot be completed.

### `80069cb0`: first tester, mode-2 success and linked boundary

1. Store `595=0` (`69cc8`), load `4a0` (`69ccc`), sign-extend with record bit.
   Zero returns 0 before `5e0` or any later field is read.
2. Load `5e0` (`69ce0`), test mask 2. Only if set, load `584` (`69cec`) and
   compare to 5. Equality returns 0. This equality load is unsigned `lbz`,
   which is equivalent to the C char equality for constant 5.
3. Load `593` (`69d00`), sign-extend with record bit. The branch is **signed
   greater than zero**, not raw-byte nonzero. A byte from `80..ff` is negative.
   Positive skips both following masks and the `593` store.
4. For signed `593<=0`, load `58e` (`69d0c`); mask `20` set returns 0. Otherwise
   load `5d4` (`69d20`); mask `1000` clear returns 0. If both pass, store
   `593=6` (`69d38`). No `585` write occurs here.
5. **Reload** `4a0` (`69d3c`), compare to 2. Equality returns 1 at `69d48`,
   before `4a4`, `585`, descriptor, or active callee work. This is a real
   short-circuit success, whether `593` was already positive or just set to 6.
6. Otherwise load `4a4` once (`69d50`). Load linked `3e6`, sign-extend and test
   zero. Nonzero skips linked `593` and takes the active path. For zero, load
   linked `593` from the **same retained pointer**, sign-extend, and test
   signed greater than zero. Nonpositive returns 1; positive takes active.
   Runtime support may stop at this linked-owner boundary without pretending
   either predicate has been evaluated.
7. Active path stores own `585=5` (`69d7c`), own `595=1` (`69d84`), then calls
   `69dd0` (`69d88`). Zero returns 0. A nonzero result reloads `4a4` (`69d94`),
   stores linked `585=5` then linked `584=5`, loads linked `5e0`, applies `ori`
   immediate 3, stores linked `5e0`, and returns 1. Do not reuse the earlier
   linked pointer across the call or invent these effects when the call is a
   boundary.

### `80069c50`, `80069bf0`, `80069b98`: ordered masks and stores

After the initial `595=0`, load `58e` and reject the specified disabled bit.
Only on passing, load `5d4` and require the input bit. Then perform the listed
stores and call `69dd0`. Its word return is propagated unchanged.

| Target | `58e` reject mask | `5d4` required mask | Reached stores | Call PC |
| --- | --- | --- | --- | --- |
| `69c50` | `20` | `1000` | `585=5` at `69c94`, then `595=1` at `69c98` | `69c9c` |
| `69bf0` | `08` | `0400` | `585=3` at `69c34`, then `595=1` at `69c38` | `69c3c` |
| `69b98` | `04` | `0080` | `585=2` at `69bd8`; no second `595` store | `69bdc` |

### `80069b10`: bit-40 path and retained disabled byte

After `595=0`, load `5d4` and require mask `40`. Load `748` (`69b38`); equality
with 1 returns 0. Then load `58e` **once** into r4 (`69b4c`). Mask 2 set returns
0. Test mask 1 of the retained r4; if set, skip `7d2`. Otherwise load `7d2`
(`69b68`) and require mask 8. A passing branch stores `585=1` (`69b80`), calls
`69dd0` (`69b84`) and propagates its return. Do not introduce a second `58e`
load just because the C export repeats the expression.

### `80069a88`: bit-20 selection and explicit reloads

After `595=0`, load `5d4` and require mask `20`. Load `748` (`69ab0`). Equality
with 2 skips the first `58e` load and selects `585=1`. Otherwise load `58e`
(`69abc`); mask 1 selects `585=1`, clear selects `585=0`. The stores are at
`69acc` and `69ad4` respectively.

Then **reload `585`** (`69ad8`), **reload `58e`** (`69ae0`), sign-extend the
retained `585` (`69ae4`), and calculate the mask using `slw` (`69ae8`). An AND
with the newly loaded `58e` returns 0 if nonzero; otherwise call `69dd0`
(`69afc`) and propagate its return. The two `748` tests are `lbz` plus equality
to 1/2, with no `extsb`; the equality result is unchanged by signedness.

## `80069dd0`: same descriptor, sentinel and active boundaries

1. Load `585` (`69de4`) **before** loading `4b0` (`69de8`). Sign-extend the
   retained byte to r5, add it to the descriptor pointer, load byte at `+b8`
   (`69df4`), sign-extend it and compare against -1. Sentinel `ff` returns 0
   through `69e04/69e08`, before any `5e0` load. No `595` store belongs to this
   sentinel branch; the caller's earlier stores remain.
2. Otherwise load `5e0` (`69e0c`), test mask 3. If zero, jump directly to the
   second descriptor read at `69e44`.
3. If nonzero, load `57a` (`69e18`), compute `slw` of 1 using **retained first
   signed `585` in r5** (`69e20`), sign-extend the loaded `57a` (`69e24`), then
   AND and test. Zero returns 0. Nonzero reaches the real `8005c080` call at
   `69e38`. Its body is not represented here. Only **after** it returns does
   the source store `595=1` at `69e40`.
4. At `69e44`, reload `585` **before** reloading `4b0` (`69e48`), sign-extend
   the fresh index, add to the fresh pointer, load `+b8` (`69e54`) and
   sign-extend the new descriptor byte. Do not cache either the pointer or
   descriptor value from the sentinel test.
5. Signed value 1 reaches `80069ea4` at `69e78`. Signed value 0 reaches
   `80069fe0` at `69e84`. Every other signed byte returns 0 at `69e8c`. The
   branch sequence first compares against 1, then against 0 on the less-than
   arm; it is not an unsigned range test. The source propagates either active
   callee's return, but these active bodies remain boundaries here.

The source descriptor address is `4b0 + b8 + signed8(585)`. For an existing
explicit owner whose byte array starts at descriptor `+8c`, this is
`raw8c[2c + signed8(585)]`; ordinary helper selectors 0, 1, 2, 3 and 5 lie
within `b8..bd` / `raw8c[2c..31]`. The source imposes **no six-action index
limit**. Direct dispatch must preserve signed indexing and admit only cells
within explicitly owned storage. That ownership/range constraint is an
implementation admission boundary, not a new source branch or proof of live
descriptor data. Charge's existing slots `bb..bd` overlap this same descriptor;
a copied competing descriptor is not evidence of source identity.

At both `slw` sites, the encoded operation is word-shift-left by the low six
bits of its register count; counts 32..63 yield zero. A host language's usual
32-bit shift often masks only five bits, so directly using it for all signed
bytes would be incorrect. The ordinary stored 0/1 selectors need no exotic
shift, but signed direct-call inputs and observable reloads must not silently
change the instruction's lowering. No source instruction is executed to
establish the archive result.

## Validation

From the repository root:

```sh
python -m unittest discover -s research/tools/matching-decomp \
  -p test_archived_actor_input_testers_evidence.py -v
```

Result: **14 tests passed**, including both real local archives, every one of
307 manually enumerated operand records, all return PCs and call targets,
physical traces, C markers and honest map coverage. Synthetic tests reject
unknown snapshots, malformed schema, mapping/root/overlap changes, wrong
width/digest, duplicate allowlist tuples, unsupported/reserved forms and
arbitrary CLI reads. Authentication failures precede new decode calls. Tests
also prove the existing shared readers still refuse these new spans.

The exact independent operand expectations are in `EXPECTED` in the test file;
they are explicit static fields, not generated at test time by the decoder.
This validates archived source extraction. It does not certify the separate
host implementation, full function behavior of active callees, or live parity.
