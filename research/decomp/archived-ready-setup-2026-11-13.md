# Archived mode-zero setup evidence, 2026-11-13

## Scope and verification

`research/tools/matching-decomp/read_archived_ready_setup_evidence.py` authenticates
both existing allowlisted ProgramDB snapshots via the existing constants reader,
checks exact memory/subblock mappings, and emits fixed range hashes, provenance
and selected instruction facts only. It neither executes vendor code nor emits
raw ranges. There is no arbitrary-address interface and no new constant target.

Both `db.3.gbf` and `db.4.gbf` under
`research/decomp/GotchaForce.rep.before_force_create/idata/00/~00000000.db/`
passed the reader on 2026-11-13, including the four-byte mode-table slot. The eight
synthetic unit tests passed. Composed runtime and aggregate validation are recorded
in `double-source-owned-dispatch-plan-2026-11-12.md`. Archived ProgramDB agreement
is not original-DOL or live-runtime parity.

## Fixed ranges

| Start | Bytes | SHA256 |
| --- | ---: | --- |
| 802d0d70 | 4 | b69bfd3e17f88dc64ebe0e5d8c02bb836ac61a4e64f32b8e016106d18076f36a |
| 80006f98 | 28 | f60303935eb09bd98a7dc923acee50f14334cc5f73b27ced28c6d436dd00eda1 |
| 8004871c | 208 | ed37e8d151614f6a73f92005849ef40d58ee6dd328e75914c862c4c6c9db29e4 |
| 8004a754 | 220 | 6029f652ed9d3b61961394341db00103e356b05aba56ad30d86c31f014e02fec |
| 8004d548 | 244 | f6d1ded4ca75a50c1df6bb8129391153a259d31bf80816e9c43a97306df249a0 |
| 8004adc8 | 192 | feef7d2deb1076d9da60cb2c3a5f129b0fe3016c4f8ffd9d1450c7405b36c919 |
| 8004af94 | 76 | d184495d0aa2ea059570c526d67319d358b4d1414c03d81e32b7ce9b553b7bf0 |

## Actual mode-zero path

Mode-table slot zero is `8004871c`. The calling ABI retains f1 as frame,
r3 actor, r4 channel, r5 group and r6 action. Mode zero does not consume the
transition argument. Resolve `4d1f4` before storing group28 and action29, then
invoke `4d244`. Next read flags2a and the existing zero constant; store bank31
from flags' top bit, byte2f=0, float20=0, float18=0, float1c=0, byte36=0,
float10=0, float14=frame, float08=0, float0c=frame. Reload float0c before
calling `4a754` with bank index zero and setup argument zero.

`4a754` writes byte35 before reading bank31 and selecting actor1d78/1d7c into
part00. It clears byte2e, calls `4d548`, stores the return byte to38, and writes
2e=1 if that byte is nonzero. It snapshots the range via `4b8f4`, then reloads
actor4b0 and its joint byte for each iteration of actual `4aae0` with flags=1.
Null-bank-only completion is not evidence of working non-null archive setup.

## Descriptor bank reads and retained slots

`4d548` reads part00 first. A null bank returns -1 without writing part04.
Otherwise it reads selector2a exactly once, masks the low seven bits, and reads
the selected group. A missing group reads bank[0], retains that slot, reads its
value and writes part04, setting fallback result1. An existing group reads
signed action2b, retains group+action*4, reads it, writes part04, then reloads
part04 for the null test. If null, reload part00 before reading bank[0], retain
the fallback slot, read its value and write part04.

Both paths reload part04 for the tag test. A tagged value is cleared and stored
to part04 before allocation. After allocation, reload part04, load allocated+c
and the payload size, then parse. Store the allocation into the retained slot
before storing it to part04. This order must not be replaced with early reads,
cloned state, callback-supplied success, or rollback after a later refusal.

## Bind-pose prefix: decompiler ordering correction

`6f98` computes `0x803bb4c0 + sign_extend(actor.byte97) * 0xc30` modulo32.
A bounded host model needs a live actor byte and an explicit owned decoded
pose-region binding at the resulting address, rather than a resolver that can
invent a pose table.

The decompiled C hoists four global values. Actual instructions do not:

1. `4ae04`: call6f98.
2. `4ae08`: read part+4; `4ae10`: read descriptor+c and retain first archive.
3. `4ae18`: snapshot unsigned public count, **before any pose translation**.
4. `4ae1c`: load pose+c; `4ae20`: load pose+1c.
5. `4ae24`: compare unsigned count against index.
6. `4ae28`: load pose+2c; save translations on the stack.
7. `4ae38`: branch to4af94 if count > index.

Only the out-of-count fallthrough loads globals802b0bc8/cc/d0/d4 at
4ae4c/50/54/58. No global values are read by this evidence reader. An in-count
implementation must not require those global loads, and must not defer the
public-count read until after pose reads. Out-of-count reset remains a separate
unsupported branch.

At4af94, use the retained first archive for public-name lookup. After that call,
reload part+4 and descriptor+c for public-address lookup. Call real JObjAddAnim
at4afc4, then load actual joint+AObj7c at4afc8. Attachment, tail and capture
must retain their own supported boundaries and actual ownership checks.

## Part-one boundary

Part1 remains unsupported for ready completion: `48648` stores actor6d8 = 1 and
calls4d08c after setup. Decompiled `chunk_0006.c` shows additional conditionals,
transform reads and constants outside the authenticated constant scope. This
reader does not add4d08c or those constants. A refusal reached at that call
boundary must preserve earlier setup effects and the preceding6d8 store.
